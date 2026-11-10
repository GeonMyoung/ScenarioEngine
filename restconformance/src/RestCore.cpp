#include "RestCore.h"
#include "HttpAdapter.h"
#include <filesystem>
#include <fstream>
#include <set>

namespace rest {
std::string validateRequest(const Config &config, const HttpRequest &request) {
    if (request.method != "GET") return "HTTP method 불일치: GET 요청이 필요합니다.";
    if (request.path != "/guide/imsOpenData.do") return "UTIC 요청 URL 경로 불일치";
    unsigned keys = 0;
    bool matched = false;
    for (const auto &q : request.query) {
        if (q.first == "key") { ++keys; matched = q.second == config.apiKey; }
    }
    if (keys != 1) return "UTIC key 요청변수는 한 번만 포함되어야 합니다.";
    if (!matched) return "UTIC key 요청변수 값 불일치";
    if (request.bodyBytes) return "단일 GET 정보요청에 예상하지 않은 본문이 있습니다.";
    return {};
}
Result run(const Config &config, std::atomic<bool> &stop, const Sink &sink) {
    Result result;
    const auto clock = std::chrono::steady_clock::now().time_since_epoch().count();
    result.runId = std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + "-" + std::to_string(clock) + "-uticServer2center_v1";
    auto directory = std::filesystem::current_path() / "rest-results" / result.runId;
    std::filesystem::create_directories(directory);
    std::ofstream trace(directory / "events.jsonl", std::ios::binary);
    if (!trace) throw Failure("시험 증적 파일을 만들 수 없습니다.");
    auto record = [&](const std::string &event, const std::string &extra = "") {
        auto tick = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        auto wall = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        trace << "{\"runId\":" << quote(result.runId) << ",\"monotonicUs\":" << tick
              << ",\"utcUnixMs\":" << wall << ",\"event\":" << quote(event) << extra << "}\n";
        trace.flush();
        if (!trace) throw Failure("시험 증적 기록 실패");
    };
    std::string body, bodyHash;
    size_t incidentCount = 0;
    try {
        body = config.fixturePath.empty() ? defaultFixture() : readTextFile(config.fixturePath);
        incidentCount = parseUticXml(body).size();
        bodyHash = sha256(body);
        std::ofstream fixture(directory / "response.xml", std::ios::binary);
        fixture << body;
        fixture.close();
        if (!fixture) throw Failure("XML 응답 자료 저장 실패");
        record("prepared", ",\"bodySha256\":" + quote(bodyHash) + ",\"incidentCount\":" + std::to_string(incidentCount));
        HttpAdapter transport(config);
        transport.start();
        record("listening", ",\"ip\":" + quote(config.bindIp) + ",\"port\":" + std::to_string(config.port));
        if (sink.info) sink.info("LISTENING");
        if (sink.state) sink.state("test_normal_utic","START");
        for (unsigned n = 1; n <= config.repetitions; ++n) {
            auto request = transport.receive(stop,config.requestTimeout);
            auto reason = validateRequest(config,request);
            record("request", ",\"exchange\":" + std::to_string(n) + ",\"session\":" + std::to_string(request.session) +
                ",\"method\":" + quote(request.method) + ",\"path\":" + quote(request.path) +
                ",\"queryKeyRedacted\":true,\"queryCount\":" + std::to_string(request.query.size()) +
                ",\"accepted\":" + (reason.empty() ? "true" : "false"));
            if (!reason.empty()) {
                // Diagnostic response from this test harness, not a claimed UTIC error contract.
                transport.respond(request,400,"Invalid test request\n","text/plain; charset=UTF-8",
                                  result.runId,n,stop,config.requestTimeout);
                throw Failure(reason);
            }
            transport.respond(request,200,body,"application/xml; charset=UTF-8",result.runId,n,stop,config.requestTimeout);
            ++result.exchanges;
            record("response_sent", ",\"exchange\":" + std::to_string(n) + ",\"session\":" + std::to_string(request.session) +
                ",\"status\":200,\"bodyBytes\":" + std::to_string(body.size()) + ",\"bodySha256\":" + quote(bodyHash));
            if (sink.info) sink.info("정상 GET 요청·XML 응답 " + std::to_string(n) + "/" + std::to_string(config.repetitions) + "회 완료");
        }
        result.verdict = "EVIDENCE_PENDING";
        result.detail = "정상 요청·XML 응답 전송 완료. UT 센터의 수신·분석·처리 로그 대조 필요";
    } catch (const Stopped &e) {
        result.verdict = "STOPPED"; result.detail = e.what();
    } catch (const std::exception &e) {
        result.verdict = "FAIL"; result.detail = e.what();
    }
    record("result", ",\"verdict\":" + quote(result.verdict) + ",\"detail\":" + quote(result.detail));
    auto reportPath = directory / "result.json";
    result.reportPath = reportPath.u8string();
    std::ofstream report(reportPath, std::ios::binary);
    report << "{\"schemaVersion\":1,\"runId\":" << quote(result.runId)
           << ",\"case\":\"uticServer2center_v1\",\"test\":\"normal_utic\",\"automaticVerdict\":" << quote(result.verdict)
           << ",\"detail\":" << quote(result.detail) << ",\"requestedExchanges\":" << config.repetitions
           << ",\"completedExchanges\":" << result.exchanges << ",\"standardConditionsMet\":" << (config.repetitions >= 10 ? "true" : "false")
           << ",\"requestTimeoutSeconds\":" << config.requestTimeout << ",\"incidentCount\":" << incidentCount
           << ",\"responseSha256\":" << quote(bodyHash) << ",\"evidenceReview\":null}\n";
    report.close();
    if (!report) throw Failure("시험 결과 파일 저장 실패");
    return result;
}
}
