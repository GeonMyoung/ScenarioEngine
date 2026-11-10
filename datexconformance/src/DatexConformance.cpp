#include "../../interfaceconformance/include/UserLog.h"
#include "DatexCore.h"
#include "DatexThread.h"
#include "DatexNarrative.h"
#include "DatexDataView.h"
#include "DatexMessageView.h"
#include <DatexConformance.h>
#include <ScenarioEngineWebSockMsg.h>
#include <dz1_asn1.h>
#include <filesystem>
#include <process.h>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace {
constexpr unsigned Start = 0x0f000001, Stop = 0x0f000002, Setup = 0x0f000003;
constexpr unsigned State = 0x00f00001, Info = 0x00f00002, UI = 0x00f00006, Initial = 0xf0000011;
constexpr unsigned ValidateRequest = 0x00f00004, ValidateResponse = 0x00f00005;
std::mutex registryMutex;
std::set<void *> registry;
int timerCompare(void *a, void *b) {
    return a == b ? 0 : std::less<void *>{}(a, b) ? -1 : 1;
}
char *mut(const std::string &s) {
    return const_cast<char *>(s.c_str());
}
Dz1Str systemText(const std::string &s, Dz1Error *e) {
    Dz1Asn1UTF8Str u = {(u8_t *)s.data(), datex::codecSize(s.size())};
    return Dz1Asn1UTF8Str_toStr(&u, e);
}
std::string fromSystem(char *s) {
    Dz1Error e = {};
    auto u = Dz1Asn1UTF8Str_newFromStr(s, &e);
    if (!u)
        throw datex::Failure("설정 문자 인코딩 오류");
    std::string r((char *)u->data, u->size);
    Dz1Asn1UTF8Str_del(u);
    return r;
}

struct Context {
    void *mainTask = nullptr;
    void *self = nullptr;
    const datex::Case *scenario = nullptr;
    void (*exception)(void *, Dz1Error *) = nullptr;
    void *exceptionArg = nullptr;
    datex::Config config;
    std::string appliedConfiguration = "{}";
    bool configured = false;
    bool hostLogChanged = false;
    u32_t hostLogThread = 0;
    Dz1ThreadLogLevel savedHostLog = 0;
    void quietTransportDiagnostics() {
        hostLogThread = Dz1Task_getThread((Dz1Task *)mainTask);
        if (!Dz1Thread_getLogLevel(hostLogThread, &savedHostLog).code) {
            const auto quiet = savedHostLog & ~(DZ1_THREAD_LOG_DEBUG | DZ1_THREAD_LOG_TASK_DEBUG);
            hostLogChanged = !Dz1Thread_setLogLevel(hostLogThread, quiet).code;
        }
        Dz1Thread_clrLogLevel(Dz1Thread_self(), DZ1_THREAD_LOG_DEBUG | DZ1_THREAD_LOG_TASK_DEBUG);
    }
    unsigned index = 0;
    std::string validationRunId;
    std::atomic<bool> stop{false}, running{false};
    datex::ManagedThread worker;
    struct Check {
        datex::Bytes raw;
        datex::Bytes json;
        std::string correlation;
        time_t time = 0;
        bool done = false, ok = false;
    };
    std::mutex checksMutex;
    std::condition_variable checksChanged;
    struct CheckGroup { std::vector<Check> messages; bool finalized = false; };
    std::map<std::string, CheckGroup> checks;
    std::string selectedTestNames(bool selected) const {
        std::string out = "[";
        for (const auto &test : datex::availableTests(*scenario)) if ((config.tests.count(test) != 0) == selected) {
            if (out.size() > 1) out += ',';
            out += datex::quote("test_" + test);
        }
        return out + ']';
    }
    void writeSelection(bool valid) const {
        std::ofstream file("datex-selection.json", std::ios::binary | std::ios::trunc);
        if (!file) throw datex::Failure("시험 선택 기록 생성 실패");
        file << "{\"case\":" << datex::quote(scenario->id) << ",\"processId\":" << _getpid()
             << ",\"testIndex\":" << index << ",\"valid\":" << (valid ? "true" : "false")
             << ",\"tests\":" << (valid ? selectedTestNames(true) : "[]")
             << ",\"configuration\":" << (valid ? appliedConfiguration : "null") << "}";
        file.close();
        if (!file) throw datex::Failure("시험 선택 기록 저장 실패");
    }
    void join() {
        stop = true;
        if (worker.joinable())
            worker.join();
        running = false;
    }
    ~Context() {
        join();
        if (hostLogChanged) Dz1Thread_setLogLevel(hostLogThread, savedHostLog);
        std::lock_guard<std::mutex> lock(registryMutex);
        registry.erase(self);
    }
    void validate(const std::string &test, const datex::Bytes &raw, const datex::Bytes &json) {
        auto rawSize = datex::codecSize(raw.size()), jsonSize = datex::codecSize(json.size());
        const std::string key = "test_" + test;
        const auto requestedAt = time(nullptr);
        std::string correlation;
        {
            std::lock_guard<std::mutex> lock(checksMutex);
            auto &group = checks[key];
            if (group.finalized) throw datex::Failure("완료된 시험에 대한 새 메시지 검증 요청");
            correlation = "DATEX validation " + validationRunId + ":" + key + ":message-" + std::to_string(group.messages.size()+1);
            group.messages.push_back(Check{raw,json,correlation,requestedAt});
        }
        Dz1Error err = {};
        auto ctx = ScenarioEngineValidateContext_gen(&err);
        if (!ctx)
            throw datex::Failure("검증 요청 생성 실패");
        ctx->testName = Dz1Str_clone(mut(key), &err);
        ctx->time = requestedAt;
        ctx->code = ScenarioEngineProcessStatusCode_OK;
        ctx->raw = Dz1Binary_new((u8_t *)raw.data(), rawSize, &err);
        ctx->data = Dz1Binary_new((u8_t *)json.data(), jsonSize, &err);
        ctx->desc = systemText(correlation, &err);
        auto arg = ScenarioEngineValidateContextArg_gen(&err);
        if (!arg) {
            ScenarioEngineValidateContext_del(ctx);
            throw datex::Failure("검증 요청 생성 실패");
        }
        arg->testIdx = index;
        arg->context = ctx;
        if (err.code ||
            Dz1Task_post(mainTask, DZ1_TASK_QUEUE_NONE, ValidateRequest, (void **)&arg,
                         (Dz1DelFunc)ScenarioEngineValidateContextArg_del, nullptr, nullptr, nullptr, nullptr)
                .code) {
            ScenarioEngineValidateContextArg_del(arg);
            throw datex::Failure("검증 요청 전송 실패");
        }
    }
    void finalizeValidation(datex::Result &result, const datex::Sink &sink) {
        if (scenario->role != datex::Role::Client || result.test.compare(0,7,"normal_") != 0 || result.verdict != datex::Verdict::Pass) return;
        datex::userInfo(sink,result.test,"결과 확인","수신한 메시지별 규격 판정 응답을 확인합니다. 이 항목의 최종 판정 후 다음 시험을 진행합니다.");
        std::unique_lock<std::mutex> lock(checksMutex);
        auto found=checks.find("test_"+result.test);
        const auto end=std::chrono::steady_clock::now()+std::chrono::seconds(config.response);
        auto allDone=[&] {
            if(found==checks.end()) return true;
            for(const auto &check:found->second.messages) if(!check.done) return false;
            return true;
        };
        while(!allDone() && !stop && std::chrono::steady_clock::now()<end)
            checksChanged.wait_for(lock,std::chrono::milliseconds(50));
        unsigned total=0,accepted=0,rejected=0;
        std::string perMessage="[";
        if(found!=checks.end()) {
            found->second.finalized=true;
            for(const auto &check:found->second.messages) {
                ++total;
                accepted+=check.done && check.ok;
                rejected+=check.done && !check.ok;
                if(total>1) perMessage+=',';
                perMessage+="{\"messageIndex\":"+std::to_string(total)+",\"status\":"+
                    datex::quote(!check.done?"not_received":check.ok?"accepted":"rejected")+"}";
            }
        }
        perMessage+=']';
        const auto missing=total-accepted-rejected;
        const std::string status=rejected?"rejected":!total?"not_received":missing?(accepted?"partially_received":"not_received"):"accepted";
        result.observationsJson="{\"platformValidation\":"+datex::quote(status)+",\"messageCount\":"+std::to_string(total)+
            ",\"acceptedCount\":"+std::to_string(accepted)+",\"rejectedCount\":"+std::to_string(rejected)+
            ",\"notReceivedCount\":"+std::to_string(missing)+",\"messages\":"+perMessage+"}";
        lock.unlock();
        if(stop) { result.verdict=datex::Verdict::Stopped; result.detail="중지됨"; }
        else if(rejected) { result.verdict=datex::Verdict::Fail; result.detail="외부 payload 규격 판정 실패"; }
        else if(missing || !total) result.detail="프로토콜/UPER 확인 완료. 플랫폼 규격 판정 응답 일부 또는 전체 미확인. 사후 제출 없이 정상 완료로 성공 처리";
        else result.detail="프로토콜/UPER 및 수신한 모든 메시지의 플랫폼 규격 판정 적합";
        datex::userInfo(sink,result.test,"검증 증적","수신 메시지 "+std::to_string(total)+"건의 규격 판정: 적합 "+
            std::to_string(accepted)+"건, 부적합 "+std::to_string(rejected)+"건, 미회신 "+std::to_string(missing)+"건.");
        result.userDetail=result.verdict==datex::Verdict::Pass
            ? "적합 — "+datex::resultDescription(*scenario,result)+(missing || !total
                ? " 플랫폼 규격 판정 응답은 확인되지 않았습니다. 미회신 건수를 기록하고 정상 절차 완료로 성공 처리하며 별도 자료 제출은 요구하지 않습니다."
                : " 수신한 모든 메시지의 플랫폼 규격 판정도 적합으로 회신되었습니다.")
            : datex::resultDescription(*scenario,result);
    }
    void state(const std::string &name, const std::string &value) {
        Dz1Error e = {};
        auto c = ScenarioEngineNotifyStateContext_new(mut(name), time(nullptr), mut(value), &e);
        if (!c)
            return;
        auto a = ScenarioEngineNotifyStateArg_gen(&e);
        if (!a) {
            ScenarioEngineNotifyStateContext_del(c);
            return;
        }
        a->testIdx = index;
        a->context = c;
        if (Dz1Task_post(mainTask, DZ1_TASK_QUEUE_NONE, State, (void **)&a,
                         (Dz1DelFunc)ScenarioEngineNotifyStateArg_del, nullptr, nullptr, nullptr, nullptr)
                .code)
            ScenarioEngineNotifyStateArg_del(a);
    }
    void info(const std::string &name, const std::string &text, const std::string &rawJson = "", const std::string &sender = "") {
        auto publicText=interface_log::line(text);std::string json=rawJson;
        auto title=name=="MainScenario"?std::string(scenario->title):datex::testTitle(*scenario,name.compare(0,5,"test_")==0?name.substr(5):name);
        if(!json.empty())try{auto shown=interface_log::publicData(datex::Json::parseData(json),"DATEX",title,interface_log::phase(text));publicText=interface_log::line(text,interface_log::get(shown,"단계"));json=interface_log::dump(shown);}catch(...){}
        interface_log::journal(index,name,publicText,sender.empty()?datex::systemLabel(*scenario,false):sender,json);
        Dz1Error e = {};
        auto c = ScenarioEngineNotifyInfoContext_gen(&e);
        if (!c) { if (!json.empty()) throw datex::Failure("송수신 메시지 알림 생성 실패"); return; }
        c->time = time(nullptr);
        c->testName = Dz1Str_clone(mut(name), &e);
        c->sender = systemText(sender.empty() ? datex::systemLabel(*scenario, false) : sender, &e);
        c->log = systemText(publicText, &e);
        if (!json.empty()) {
            c->data = Dz1Binary_new((u8_t *)json.data(), datex::codecSize(json.size()), &e);
            c->dataType = Dz1Str_clone(mut("JSON"), &e);
            if (e.code || !c->data || !c->dataType || !c->log) {
                ScenarioEngineNotifyInfoContext_del(c);
                throw datex::Failure("송수신 메시지 첨부 생성 실패");
            }
        }
        auto a = ScenarioEngineNotifyInfoArg_gen(&e);
        if (!a) {
            ScenarioEngineNotifyInfoContext_del(c);
            if (!json.empty()) throw datex::Failure("송수신 메시지 알림 생성 실패");
            return;
        }
        a->testIdx = index;
        a->context = c;
        if (Dz1Task_post(mainTask, DZ1_TASK_QUEUE_NONE, Info, (void **)&a,
                         (Dz1DelFunc)ScenarioEngineNotifyInfoArg_del, nullptr, nullptr, nullptr, nullptr)
                .code)
            { ScenarioEngineNotifyInfoArg_del(a); if (!json.empty()) throw datex::Failure("송수신 메시지 알림 전달 실패"); }
    }
    void run() {
        running = true;
        try {
            {
                std::lock_guard<std::mutex> lock(checksMutex);
                checks.clear();
            }
            const auto runId = std::to_string(time(nullptr)) + "-" + std::to_string(index) + "-" +
                               std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
                               "-" + scenario->id;
            validationRunId = runId;
            std::filesystem::path dir = std::filesystem::current_path() / "datex-results";
            std::filesystem::create_directories(dir);
            std::ofstream trace(dir / (runId + ".events.jsonl"), std::ios::binary);
            const auto runStarted = std::chrono::steady_clock::now();
            std::mutex traceMutex, dataMutex;
            std::ofstream dataTrace(dir / (runId + ".linked-data.jsonl"), std::ios::binary);
            if (!dataTrace) throw datex::Failure("연계정보 증적 파일 생성 실패");
            struct DataSample {
                std::string first, last;
                std::vector<std::string> lines;
                unsigned count = 0;
            };
            std::map<std::string, std::map<std::string, DataSample>> linkedData;
            std::ofstream messages(dir / (runId + ".all-messages.jsonl"), std::ios::binary);
            std::ofstream notifications(dir / (runId + ".message-notifications.jsonl"), std::ios::binary);
            if (!messages || !notifications) throw datex::Failure("전체 메시지 기록 생성 실패");
            std::mutex messagesMutex;
            std::map<std::string, std::pair<unsigned,unsigned>> messageCounts;
            std::uint64_t messageSequence = 0;
            if (!trace)
                throw datex::Failure("실행 증적 파일을 생성할 수 없습니다.");
            state("MainScenario", "START");
            info("MainScenario", "[시험 시작] " + std::string(scenario->title) + ". 선택한 " + std::to_string(config.tests.size()) + "개 항목을 화면의 시험 목록 순서대로 확인합니다. 미선택 " + std::to_string(datex::availableTests(*scenario).size() - config.tests.size()) + "개 항목은 실행하지 않습니다.");
            info("MainScenario", scenario->role == datex::Role::Client
                ? "[시험 구성] 대상은 ISO 14827 Server로 정보를 제공합니다. 시험 시스템은 ISO 14827 Client로 정보를 요청·수신합니다."
                : "[시험 구성] 대상은 ISO 14827 Client로 정보를 요청합니다. 시험 시스템은 ISO 14827 Server로 요청을 수용하고 정보를 제공합니다.");
            info("MainScenario", config.tcpConnects(*scenario) ? "[시험 구성] TCP 접속은 시험 시스템이 시작하고 시험 대상이 수신 대기합니다." : "[시험 구성] TCP 접속은 시험 대상이 시작하고 시험 시스템이 수신 대기합니다.");
            info("MainScenario", "[연계정보] " + datex::linkedInformation(*scenario));
            info("MainScenario", "[적용 조건] DATEX / TCP. 최대 무수신 시간 " + std::to_string(config.heartbeat) + "초, 응답 제한 시간 " + std::to_string(config.response) + "초. 송수신 원문과 판정 기록은 시험 증적으로 보관합니다.");
            datex::Sink sink;
            sink.state = [&](const std::string &test, const std::string &s) { state(test, s); };
            sink.info = [&](const std::string &test, const std::string &text) {
                std::lock_guard<std::mutex> lock(traceMutex);
                auto us = std::chrono::duration_cast<std::chrono::microseconds>(
                              std::chrono::steady_clock::now().time_since_epoch())
                              .count();
                trace << "{\"monotonicUs\":" << us << ",\"test\":" << datex::quote(test)
                      << ",\"message\":" << datex::quote(text) << "}\n";
                trace.flush();
                if (!trace)
                    throw datex::Failure("실행 증적 기록 실패");
            };
            sink.userInfo = [&](const std::string &test, const std::string &phase, const std::string &text) {
                if(phase=="확인 기준")info("test_"+test,"[시험 안내] "+datex::testTitle(*scenario,test),interface_log::guide(datex::testTitle(*scenario,test),datex::systemLabel(*scenario,true),"접속·시험 조건 준비 → 요청/제공 및 수용·거부 응답 관측 → 시간·자료 대조 → 판정",text,"해당 항목의 프로토콜 조건과 수신 데이터의 디코딩을 확인합니다. 대상 내부 처리 로그를 직접 관측했다고 확대하지 않습니다."));
                info("test_" + test, "[" + phase + "] " + (phase == "시험 시작" ? "" : datex::testTitle(*scenario, test) + " · ") + text);
                std::lock_guard<std::mutex> lock(traceMutex);
                auto us = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::steady_clock::now().time_since_epoch()).count();
                trace << "{\"monotonicUs\":" << us << ",\"test\":" << datex::quote(test)
                      << ",\"kind\":\"user\",\"phase\":" << datex::quote(phase)
                      << ",\"message\":" << datex::quote(text) << "}\n";
                trace.flush();
                if (!trace) throw datex::Failure("사용자 진행 기록 저장 실패");
            };
            sink.finalize = [&](datex::Result &result) { finalizeValidation(result,sink); };
            sink.result = [&](const datex::Result &result) {
                auto detail=result.userDetail.empty()?(result.verdict==datex::Verdict::Pass?"선택한 관측 조건을 충족했습니다.":"필요한 관측 조건을 충족하지 못했습니다. 진행 기록을 확인하세요."):result.userDetail;
                info("test_"+result.test,"[결과] "+datex::testTitle(*scenario,result.test),"{\"자료 구분\":\"시험 결과\",\"판정\":"+datex::quote(interface_log::verdict(datex::verdictName(result.verdict)))+",\"판정 기준\":"+datex::quote(datex::testCriteria(*scenario,config,result.test))+",\"실제 확인\":"+datex::quote(detail)+",\"확인 범위\":\"해당 항목의 프로토콜·자료·시간 관측 범위입니다. 대상 내부 처리 로그를 직접 관측한 결과로 확대하지 않습니다.\"}");
                datex::userInfo(sink,result.test,result.test.compare(0,7,"normal_")==0?"최종 판정":"항목 결과",
                    (result.verdict==datex::Verdict::Pass && result.userDetail.find("적합 — ")!=0
                        ? (result.test=="abnormal_session" && result.observationsJson.find("\"tcpClosed\":false")!=std::string::npos
                            ? "성공(관찰 절차 완료·TCP 종료 미관측) — " : "적합 — ") : "")+result.userDetail);
                sink.info(result.test,std::string(datex::verdictName(result.verdict))+": "+result.detail);
                state("test_"+result.test,datex::verdictName(result.verdict));
            };
            sink.validation = [&](const std::string &test, const std::string &, const datex::Bytes &raw,
                                  const datex::Bytes &json) { validate(test, raw, json); };
            sink.packet = [&](const std::string &test, bool received, const datex::PacketRecord &packet,
                              int type, const datex::Bytes &wire, bool redacted) {
                {
                std::lock_guard<std::mutex> lock(traceMutex);
                const char *hex = "0123456789abcdef";
                std::string text;
                text.reserve(wire.size() * 2);
                for (auto b : wire) {
                    text += hex[b >> 4];
                    text += hex[b & 15];
                }
                auto us =
                    std::chrono::duration_cast<std::chrono::microseconds>(packet.received.time_since_epoch())
                        .count();
                trace << "{\"monotonicUs\":" << us << ",\"test\":" << datex::quote(test)
                      << ",\"direction\":" << datex::quote(received ? "RX" : "TX")
                      << ",\"packetNumber\":" << packet.number << ",\"pdu\":" << type
                      << ",\"redacted\":" << (redacted ? "true" : "false")
                      << ",\"wireHex\":" << datex::quote(text) << "}\n";
                trace.flush();
                if (!trace)
                    throw datex::Failure("패킷 증적 기록 실패");
                }
                {
                    std::lock_guard<std::mutex> lock(messagesMutex);
                    const auto sequence = ++messageSequence;
                    auto &counts = messageCounts[test];
                    if (received) ++counts.second; else ++counts.first;
                    datex::MessageView view;
                    try { view = datex::completeMessageView(*scenario, wire, test); }
                    catch (const std::exception &) { view.name = "분석 불가 / 미완성 수신 전문";
                        view.details = "{\"안내\":\"C2CAuthMsg로 해석하지 못한 실제 수신 바이트입니다. 전문 형식과 최종 판정을 확인하세요.\",\"원문 HEX\":" + datex::quote(datex::dataHex(wire)) + "}"; }
                    const auto sender = datex::systemLabel(*scenario, received);
                    const auto receiver = datex::systemLabel(*scenario, !received);
                    const std::string metadata = "\"관측 순번\":" + std::to_string(sequence) + ",\"시험 항목\":" + datex::quote(datex::testTitle(*scenario,test)) +
                        ",\"발송 주체\":" + datex::quote(sender) + ",\"수신 주체\":" + datex::quote(receiver) +
                        ",\"방향\":" + datex::quote(received ? "수신: 대상 → 시험 시스템" : "송신: 시험 시스템 → 대상") +
                        ",\"전송 상태\":" + datex::quote(received ? (type < 0 ? "해석 불가 수신 바이트" : "수신 완료") : (packet.sendCompleted ? "소켓 송신 완료" : "송신 시도 실패/중단")) +
                        ",\"송신 확인 바이트\":" + (received ? std::string("null") : std::to_string(packet.sentBytes)) +
                        ",\"관측 연결 번호\":" + std::to_string(packet.sessionId) + ",\"메시지\":" + datex::quote(view.name) +
                        ",\"패킷 번호\":" + (type < 0 ? std::string("null") : std::to_string(packet.number)) +
                        ",\"송신 재전송\":" + (packet.retransmitted ? "true" : "false") +
                        ",\"시험 시작 후 경과(ms)\":" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(packet.received - runStarted).count()) +
                        ",\"관측 원문 크기\":" + std::to_string(packet.wire.size()) + ",\"인증값 가림\":" + (redacted ? "true" : "false") +
                        ",\"원문 안내\":" + datex::quote(!received && !packet.sendCompleted ? "송신하려던 전체 전문입니다. 실제로 소켓에 전달한 바이트 수는 송신 확인 바이트를 참조하세요. 비밀번호·인증값은 가림 처리합니다." : redacted ? "비밀번호·인증값을 가린 표시용 전문입니다. 가림 때문에 길이·CRC는 실제 송수신 바이트와 다를 수 있습니다." : "관측한 메시지 전체 바이트입니다.");
                    messages << "{\"test\":" << datex::quote(test) << ',' << metadata << ",\"상세\":" << view.details << "}\n";
                    messages.flush();
                    if (!messages) throw datex::Failure("전체 메시지 저장 실패");
                    for (const auto &part : datex::messageParts(metadata,view.details)) {
                        auto title = "[" + std::string(received ? "수신" : "송신") + " 메시지 #" + std::to_string(sequence) + "] " + sender + " → " + receiver + " · " + datex::testTitle(*scenario,test) + " · " + view.name +
                            (type < 0 ? "" : " · 패킷 " + std::to_string(packet.number)) + (packet.retransmitted ? " · 재전송" : "") + (!received && !packet.sendCompleted ? " · 송신 미완료" : "") +
                            (part.total > 1 ? " · 분할 " + std::to_string(part.index) + "/" + std::to_string(part.total) : "");
                        info("test_" + test, title, part.json, sender);
                        notifications << "{\"test\":" << datex::quote(test) << ",\"sender\":" << datex::quote(sender) << ",\"log\":" << datex::quote(title) << ",\"data\":" << part.json << "}\n";
                    }
                    notifications.flush();
                    if (!notifications) throw datex::Failure("전체 메시지 알림 기록 실패");
                }
                if (type != Iso14827PDUsPresent_publication) return;
                std::vector<datex::LinkedData> records;
                try { records = datex::inspectLinkedData(*scenario, wire, test); }
                catch (const std::exception &) {
                    datex::LinkedData unavailable;
                    unavailable.note = "이 전문의 내용을 표시용 데이터로 분석하지 못했습니다. 송수신 원문은 기록했으며, 시험 판정은 항목 결과에서 확인하세요.";
                    records.push_back(std::move(unavailable));
                }
                std::lock_guard<std::mutex> lock(dataMutex);
                for (const auto &record : records) {
                    auto key = std::string(received ? "RX:" : "TX:") + record.message + ":" + record.oid;
                    auto &sample = linkedData[test][key];
                    ++sample.count;
                    sample.lines = datex::linkedDataSummary(record);
                    const auto label = record.message.empty() ? "연계정보" : datex::messageLabel(record.message);
                    sample.lines.insert(sample.lines.begin(), std::string(received ? "대상 → 시험 시스템" : "시험 시스템 → 대상") + " · " + label + "; 구독번호 " + std::to_string(record.subscription) + ", 발행번호 " + std::to_string(record.publication) + ", 메시지 " + std::to_string(record.raw.size()) + "바이트. 아래 수치·시간·좌표는 단위 변환하지 않은 표준 원값입니다.");
                    sample.lines.push_back("연계 식별자 " + (record.oid.empty() ? "미확인" : record.oid) + "; 메시지 관측 " + std::to_string(sample.count) + "건(재전송 포함).");
                    std::string summary = "[";
                    for (const auto &line : sample.lines) { if (summary.size() > 1) summary += ','; summary += datex::quote(line); }
                    summary += ']';
                    auto us = std::chrono::duration_cast<std::chrono::microseconds>(packet.received.time_since_epoch()).count();
                    const std::string metadata = "\"direction\":" + datex::quote(received ? "RX" : "TX") + ",\"message\":" + datex::quote(record.message) + ",\"packetNumber\":" + std::to_string(packet.number) + ",\"packetTimeUs\":" + std::to_string(us) + ",\"subscriptionSerial\":" + std::to_string(record.subscription) + ",\"publicationSerial\":" + std::to_string(record.publication) + ",\"oid\":" + datex::quote(record.oid) + ",\"summary\":" + summary;
                    sample.last = "{" + metadata + "}";
                    if (sample.first.empty()) sample.first = sample.last;
                    dataTrace << "{\"test\":" << datex::quote(test) << ',' << metadata
                        << ",\"decodedJson\":" << datex::quote(record.decodedJson)
                        << ",\"regionalJson\":" << datex::quote(record.regionalJson)
                        << ",\"rawHex\":" << datex::quote(datex::dataHex(record.raw)) << "}\n";

                }
                dataTrace.flush();
                if (!dataTrace) throw datex::Failure("연계정보 증적 기록 실패");
            };
            auto results = datex::run(*scenario, config, stop, sink);
            bool fail = false;
            std::ofstream report(dir / (runId + ".json"), std::ios::binary);
            if (!report)
                throw datex::Failure("결과 파일 생성 실패");
            report << "{\"schemaVersion\":1,\"runId\":" << datex::quote(runId)
                   << ",\"case\":" << datex::quote(scenario->id)
                   << ",\"sessionOpening\":" << datex::quote(config.useInitiate ? "serverInitiated" : "clientInitiated")
                   << ",\"testerTcpRole\":" << datex::quote(config.tcpConnects(*scenario) ? "connect" : "listen")
                   << ",\"heartbeatMaxSeconds\":" << config.heartbeat
                   << ",\"responseTimeoutSeconds\":" << config.response
                   << ",\"fredMaintainSeconds\":" << config.maintain
                   << ",\"receiveSeconds\":" << config.receive << ",\"periodSeconds\":" << config.period
                   << ",\"standardConditionsMet\":"
                   << ((config.tests.count("abnormal_session") && config.maintain < 300) ? "false" : "true")
                   << ",\"selectedTests\":" << selectedTestNames(true)
                   << ",\"notSelectedTests\":" << selectedTestNames(false)
                   << ",\"results\":[";
            bool first = true;
            for (auto &r : results) {
                fail |= r.verdict == datex::Verdict::Fail || r.verdict == datex::Verdict::Error ||
                        r.verdict == datex::Verdict::Stopped;
                if (!first)
                    report << ',';
                first = false;
                report << "{\"test\":" << datex::quote(r.test)
                       << ",\"verdict\":" << datex::quote(datex::verdictName(r.verdict))
                       << ",\"detail\":" << datex::quote(r.detail)
                       << ",\"userDetail\":" << datex::quote(r.userDetail)
                       << ",\"observations\":" << (r.observationsJson.empty() ? "null" : r.observationsJson) << ",\"linkedData\":[";
                auto samples = linkedData.find(r.test);
                bool firstData = true;
                if (samples != linkedData.end()) for (const auto &entry : samples->second) {
                    if (!firstData) report << ',';
                    firstData = false;
                    report << "{\"observedCount\":" << entry.second.count << ",\"first\":" << entry.second.first << ",\"last\":" << entry.second.last << "}";
                }
                report << "],\"sentMessages\":" << messageCounts[r.test].first << ",\"receivedMessages\":" << messageCounts[r.test].second << "}";
            }
            if (results.size() != config.tests.size())
                fail = true;
            report << "],\"automaticVerdict\":"
                   << datex::quote(stop      ? "STOPPED"
                                   : fail    ? "FAIL"
                                             : "SUCCESS")
                   << ",\"allMessagesFile\":" << datex::quote(runId + ".all-messages.jsonl")
                   << ",\"messageCount\":" << messageSequence
                   << ",\"linkedDataFile\":" << datex::quote(runId + ".linked-data.jsonl") << "}\n";
            report.close();
            if (!report)
                throw datex::Failure("결과 저장 실패");
            unsigned passed = 0, failed = 0, errors = 0, stopped = 0;
            for (const auto &r : results) {
                passed += r.verdict == datex::Verdict::Pass;
                failed += r.verdict == datex::Verdict::Fail;
                errors += r.verdict == datex::Verdict::Error;
                stopped += r.verdict == datex::Verdict::Stopped;
            }
            info("MainScenario", "[시험 결과] 선택 " + std::to_string(config.tests.size()) + "개 중 성공 " + std::to_string(passed) + "개, 기준 미충족 " + std::to_string(failed) + "개, 수행 오류 " + std::to_string(errors) + "개, 중지 " + std::to_string(stopped) + "개, 미실행 " + std::to_string(config.tests.size() - results.size()) + "개입니다.");
            info("MainScenario", "[기록 저장] 항목별 판정, 적용 조건과 송수신 증적을 저장했습니다.");
            state("MainScenario", stop ? "STOPPED" : fail ? "FAIL" : "SUCCESS");
            state("MainScenario", "FINISH");
        } catch (const std::exception &e) {
            std::ofstream diagnostic("datex-run-errors.log", std::ios::app);
            diagnostic << time(nullptr) << " " << e.what() << "\n";
            info("MainScenario", "[시험 수행 오류] 시험 실행 또는 결과 기록을 완료하지 못했습니다. 시험 기록 폴더의 쓰기 권한·남은 공간과 상세 진단 기록을 확인한 뒤 다시 실행하세요. 이번 실행을 적합으로 판단하지 않습니다.");
            state("MainScenario", "FAIL");
            state("MainScenario", "FINISH");
        }
        running = false;
    }
};
Dz1Error init(void **resource, void *self, str_t, unsigned, void *argument, void *) {
    auto c = (Context *)argument;
    c->self = self;
    *resource = c;
    Dz1Task_postSimple(self, DZ1_TASK_QUEUE_NONE, Initial);
    Dz1Error e = {};
    return e;
}
void cleanup(void *resource) {
    if (resource)
        ((Context *)resource)->join();
}
void destroy(void *p) {
    delete (Context *)p;
}
void onException(void *arg, void *, void *, Dz1Error *e) {
    auto c = (Context *)arg;
    if (c->exception)
        c->exception(c->exceptionArg, e);
}
Dz1TaskProcStatus initial(void *arg, void *, void *, void **, Dz1Error *err) {
    auto c = (Context *)arg;
    try {
        c->quietTransportDiagnostics();
        auto json = datex::configureUI(*c->scenario);
        Dz1Str value = systemText(json, err);
        if (!value)
            return Dz1TaskProcStatus_error;
        *err = Dz1Task_post(c->mainTask, DZ1_TASK_QUEUE_NONE, UI, (void **)&value, (Dz1DelFunc)Dz1Str_del,
                            nullptr, nullptr, nullptr, nullptr);
        if (err->code)
            Dz1Str_del(value);
    } catch (...) {
        Dz1Error_set(err, EINVAL);
    }
    return Dz1TaskProcStatus_processed;
}
Dz1TaskProcStatus setup(void *arg, void *, void *, void **message, Dz1Error *err) {
    auto c = (Context *)arg;
    if (c->running) {
        Dz1Error_set(err, EBUSY);
        return Dz1TaskProcStatus_processed;
    }
    try {
        c->writeSelection(false);
        auto raw = (char *)Dz1TaskSigMsg_getData(*message);
        if (!raw)
            throw datex::Failure("설정 누락");
        const auto configuration = fromSystem(raw);
        auto conf = datex::Config::parse(*c->scenario, configuration);
        if (c->worker.joinable())
            c->worker.join();
        c->config = std::move(conf);
        c->appliedConfiguration = configuration;
        c->configured = true;
        ++c->index;
        c->writeSelection(true);
        c->info("MainScenario", "[준비 완료] " + std::string(c->scenario->title) + "의 설정을 적용했습니다. 선택한 시험은 " + std::to_string(c->config.tests.size()) + "개입니다. 대상의 접속·시간 설정을 맞춘 뒤 시험을 시작하세요.");
        Dz1Error_set(err, 0);
    } catch (const std::exception &e) {
        c->configured = false;
        c->info("MainScenario", "[설정 확인 필요] " + std::string(e.what()) + " · 해당 입력값을 수정하고 설정을 다시 적용하세요.");
        Dz1Error_set(err, EINVAL);
    }
    return Dz1TaskProcStatus_processed;
}
Dz1TaskProcStatus start(void *arg, void *, void *, void **, Dz1Error *err) {
    auto c = (Context *)arg;
    if (!c->configured || c->running) {
        Dz1Error_set(err, EINVAL);
        return Dz1TaskProcStatus_processed;
    }
    try {
        if (c->worker.joinable())
            c->worker.join();
        c->running = true;
        c->stop = false;
        c->worker.start([c] { c->run(); });
        c->configured = false;
        Dz1Error_set(err, 0);
    } catch (...) {
        c->running = false;
        Dz1Error_set(err, EFAULT);
    }
    return Dz1TaskProcStatus_processed;
}
Dz1TaskProcStatus stop(void *arg, void *, void *, void **, Dz1Error *err) {
    auto c = (Context *)arg;
    c->join();
    c->info("MainScenario", "[중지 처리 완료] 실행 중인 시험의 연결을 정리했습니다. 완료된 항목의 기록은 유지되며 미완료 항목은 다시 실행할 수 있습니다.");
    Dz1Error_set(err, 0);
    return Dz1TaskProcStatus_processed;
}
Dz1TaskProcStatus validation(void *arg, void *, void *, void **message, Dz1Error *err) {
    auto c = (Context *)arg;
    auto response = (ScenarioEngineResponseMessageValidate *)Dz1TaskSigMsg_getData(*message);
    auto v = response ? response->validate : nullptr;
    // The deployed platform omits testIdx (decoded as zero). Require the echoed
    // per-run correlation and complete request content, including for indexed replies.
    if (response && (response->testIdx == c->index || response->testIdx == 0) && v &&
        v->testName && v->raw && v->data && v->desc) {
        std::lock_guard<std::mutex> lock(c->checksMutex);
        auto i = c->checks.find(v->testName);
        if (i != c->checks.end() && !i->second.finalized) {
            for (auto &check : i->second.messages) {
                if (!check.done && check.time == v->time && check.correlation == v->desc &&
                    check.raw.size() == v->raw->size && std::equal(check.raw.begin(),check.raw.end(),v->raw->data) &&
                    check.json.size() == v->data->size && std::equal(check.json.begin(),check.json.end(),v->data->data)) {
                    check.done=true;
                    check.ok=response->result && (std::string(response->result)=="SUCCESS" || std::string(response->result)=="OK") &&
                        v->code==ScenarioEngineProcessStatusCode_OK;
                    c->checksChanged.notify_all();
                    break;
                }
            }
        }
    }
    Dz1Error_set(err, 0);
    return Dz1TaskProcStatus_processed;
}
} // namespace
extern "C" void *DatexConformance_new(void *mainTask, Dz1Str scenario, void (*exception)(void *, Dz1Error *),
                                      void *exceptionArg, Dz1Error *error) {
    Dz1Error local = {};
    if (!error)
        error = &local;
    Context *c = nullptr;
    void *task = nullptr;
    try {
        if (!mainTask || !scenario)
            throw datex::Failure("초기화 인자 누락");
        c = new Context;
        c->mainTask = mainTask;
        c->scenario = &datex::findCase(scenario);
        c->exception = exception;
        c->exceptionArg = exceptionArg;
        auto owned = c;
        task = Dz1Task_new(mut("DatexConformance"), 1024, (void **)&c, destroy, timerCompare, init,
                           onException, cleanup, error);
        if (!task) {
            delete c;
            return nullptr;
        }
        owned->self = task;
        {
            std::lock_guard<std::mutex> lock(registryMutex);
            registry.insert(task);
        }
        for (auto item :
             {std::make_pair(Initial, initial), std::make_pair(Setup, setup), std::make_pair(Start, start),
              std::make_pair(Stop, stop), std::make_pair(ValidateResponse, validation)}) {
            *error = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(item.first), item.second);
            if (error->code) {
                Dz1Task_del(task);
                return nullptr;
            }
        }
        Dz1Error_set(error, 0);
        return task;
    } catch (...) {
        if (task)
            Dz1Task_del(task);
        else
            delete c;
        Dz1Error_set(error, EINVAL);
        return nullptr;
    }
}
extern "C" bool_t DatexConformance_isTask(void *task) {
    std::lock_guard<std::mutex> lock(registryMutex);
    return registry.count(task) ? TRUE : FALSE;
}
extern "C" bool_t DatexConformance_validation(void *task, void *data, Dz1Error *error) {
    std::lock_guard<std::mutex> lock(registryMutex);
    if (!registry.count(task))
        return FALSE;
    auto cloned =
        ScenarioEngineResponseMessageValidate_clone((ScenarioEngineResponseMessageValidate *)data, error);
    if (cloned) {
        *error = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE, ValidateResponse, (void **)&cloned,
                              (Dz1DelFunc)ScenarioEngineResponseMessageValidate_del, nullptr, nullptr,
                              nullptr, nullptr);
        if (error->code)
            ScenarioEngineResponseMessageValidate_del(cloned);
    }
    return TRUE;
}
