#pragma once
#include "DatexCore.h"

// Presentation only. Diagnostic detail and wire evidence remain unchanged.
namespace datex {
inline std::string systemLabel(const Case &c, bool target) {
    const std::string id(c.id);
    const auto split = id.find('2');
    std::string key = target && split != std::string::npos ? id.substr(split + 1) : id.substr(0, split);
    const auto suffix = key.find(target ? "_v" : (c.role == Role::Client ? "Client" : "Server"));
    if (suffix != std::string::npos) key.resize(suffix);
    static const std::map<std::string, std::string> labels = {
        {"center", "통합교통관제시스템"}, {"rse", "RSE"},
        {"vehicle", "자율주행차량"}, {"signalserver", "신호정보 수집서버"}};
    const auto found = labels.find(key);
    return found == labels.end() ? (target ? "시험 대상 시스템" : "시험 시스템") : found->second;
}
inline void userInfo(const Sink &sink, const std::string &test, const std::string &phase,
                     const std::string &text) {
    if (sink.userInfo) sink.userInfo(test, phase, text);
}
inline std::string messageLabel(const std::string &name) {
    static const std::map<std::string, std::string> labels = {
        {"bsm", "BSM 차량 기본안전정보"}, {"map", "MAP 도로·교차로 형상정보"},
        {"rsa", "RSA 도로상황정보"}, {"tim", "TIM 여행자정보"},
        {"tim_speed", "TIM 제한속도 변경정보"}, {"tim_lane", "TIM 차로변경정보"},
        {"tim_regional", "TIM 국내 확장정보"}, {"spat", "SPaT 신호현시정보"},
        {"tls", "TLSM 신호등 상태정보"}};
    auto i = labels.find(name);
    return i == labels.end() ? "연계정보" : i->second;
}
inline std::string linkedInformation(const Case &c, const std::string &test = "") {
    if (test.compare(0, 7, "normal_") == 0) return messageLabel(test.substr(7));
    std::string value;
    for (const auto &m : c.messages) {
        if (!value.empty()) value += ", ";
        value += messageLabel(m.name);
    }
    return value;
}
inline std::string rejectionMeaning(const std::string &test) {
    static const std::map<std::string, std::string> labels = {
        {"unknownSubscription", "등록되지 않은 구독에 대한 정보"},
        {"unknownPublicationNbr", "유효하지 않은 발행번호의 정보"},
        {"unknownPublicationMsgId", "알 수 없는 메시지 식별자의 정보"},
        {"invalidPublicationMsgId", "구독한 종류와 다른 메시지의 정보"},
        {"invalidPublicationMsgContent", "내용 형식이 잘못된 정보"},
        {"repeatedPublicationNbr", "이미 처리한 발행번호의 정보"}};
    auto i = labels.find(test);
    return i == labels.end() ? "잘못된 정보" : i->second;
}
inline std::string testCriteria(const Case &c, const Config &cfg, const std::string &test) {
    if (test.compare(0, 7, "normal_") == 0)
        return c.role == Role::Client
            ? "요청한 " + linkedInformation(c, test) + "의 메시지 식별·ASN.1 디코딩·통신 절차를 확인합니다. 수신한 각 메시지에 대한 플랫폼의 명시적 부적합은 실패로 반영합니다. 미회신은 사실을 기록하고 정상 절차 완료로 성공 처리하며 사후 자료 제출은 요구하지 않습니다."
            : "정상 " + linkedInformation(c, test) + "에 대한 Publication Accept를 받고, 이후 응답 제한 시간 " + std::to_string(cfg.response) + "초 동안 rejectPublicationData가 없어야 합니다. 연결 유지와 정상 종료까지 확인되면 시험 기준에 따라 정상 처리로 판정합니다.";
    if (test == "session") return "로그인과 수용 응답이 성립하고, 연결 확인 메시지(FrED)를 2회 정상 교환해야 합니다.";
    if (test == "invalid_login") return "잘못된 비밀번호로 로그인하면 비밀번호 오류 사유로 거부해야 합니다. 연결 종료만으로는 통과하지 않습니다.";
    if (test == "duplicate_login") return "기존 연결을 유지한 채 같은 계정으로 다시 로그인하면 중복 세션 사유로 거부하고, 기존 연결은 유지해야 합니다.";
    if (test == "invalid_subscription") return "지원하지 않는 종류의 정보를 요청하면 메시지 식별자 오류 사유로 거부하고 연결을 유지해야 합니다.";
    if (test == "abnormal_session") return "연결을 " + std::to_string(cfg.maintain) + "초 유지한 뒤 송신을 중단합니다. " + std::to_string(cfg.heartbeat) + "초부터 " + std::to_string(cfg.heartbeat + cfg.response) + "초까지 대상의 종료 동작을 관찰합니다. 조기 종료·추가 데이터 교환은 부적합입니다. TCP 종료 관측 여부를 기록하고 정상 절차 완료 시 별도 자료 제출 없이 성공으로 처리합니다.";
    if (test == "cancel") return std::to_string(cfg.receive) + "초 동안 최소 2회 수신하고, 초기 응답에 따른 짧은 첫 간격은 허용하되, 이후 제공 간격이 요청 주기 " + std::to_string(cfg.period) + "초의 ±10% 이내인지 확인합니다. 취소 수용 후 한 주기 동안 새 정보가 없어야 하며 연결은 유지해야 합니다.";
    if (test == "login_retry" || test == "subscription_retry" || test == "publication_retry")
        return "수용 응답을 보류해 재전송을 유도합니다. 번호·타임스탬프·내용의 동일성과 재전송 시점을 확인하고 수용 후 연결을 유지해야 합니다. 기준 R=" + std::to_string(cfg.response) + "초, 조기 수신 허용은 R의 10%와 100ms 중 작은 값, 지연 허용은 2초입니다. 허용치는 관측 오차를 위한 구현 기준입니다.";
    return rejectionMeaning(test) + "를 의도적으로 제공합니다. 대상이 수신 확인 응답과 함께 해당 오류에 맞는 거부 사유·구독번호·발행번호를 회신하고 연결을 유지해야 합니다.";
}
inline std::string failureExplanation(const std::string &detail) {
    if (detail.find("rejectPublicationData") != std::string::npos) return "정상 정보의 수신 확인 응답 이후 데이터 거부 응답(rejectPublicationData)을 받았습니다. 해당 구독번호·발행번호와 거부 사유를 송수신 메시지에서 확인하세요.";
    if (detail == "외부 payload 규격 판정 실패") return "플랫폼의 메시지 규격 판정이 부적합으로 회신되었습니다. 메시지 검증 결과에서 해당 필드를 확인하세요.";
    if (detail.find("포트 바인딩") != std::string::npos) return "시험 시스템의 수신 대기 포트를 열 수 없습니다. 동일 포트를 사용하는 프로그램과 포트 설정을 확인하세요.";
    if (detail.find("접속") != std::string::npos) return "시험 대상과 연결하지 못했습니다. 접속 주체, 대상 실행 상태, 주소·포트와 방화벽 설정을 확인하세요.";
    if (detail.find("CONNECTION_CLOSED") != std::string::npos || detail.find("소켓") != std::string::npos) return "절차 완료 전에 연결이 끊어졌거나 송수신할 수 없었습니다. 같은 시각의 대상 연결 기록과 네트워크 상태를 확인하세요.";
    if (detail.find("H 경과 전") != std::string::npos) return "설정한 최대 무수신 시간이 지나기 전에 연결이 종료되었습니다. 대상의 종료 시각과 사유를 확인하세요.";
    if (detail.find("관찰 기한 경과 후") != std::string::npos) return "대상의 연결 종료가 설정한 관찰 기한을 벗어났습니다. 송신 중단 시각과 종료 시각을 비교하세요.";
    if (detail.find("무수신 종료 중 추가 데이터") != std::string::npos) return "무수신 종료 관찰 중 대상이 추가 메시지를 보냈습니다. 종료 절차와 해당 송수신 기록을 확인하세요.";
    if (detail.find("HeartbeatDurationMax") != std::string::npos) return "최대 무수신 시간 안에 대상의 메시지를 확인하지 못했습니다. 연결 확인 메시지의 송수신 기록과 양쪽 시간 설정을 확인하세요.";
    if (detail.find("시간 초과") != std::string::npos || detail == "응답 없음") return "대기 시간 안에 필요한 응답을 확인하지 못했습니다. 대상의 수신·응답 기록과 응답 제한 시간 설정을 확인하세요.";
    if (detail.find("재전송 동일성") != std::string::npos || detail == "동일 번호의 내용이 변경됨") return "재전송된 메시지의 번호·시각·내용 중 일치하지 않는 값이 있습니다. 원본과 재전송 증적을 비교하세요.";
    if (detail.find("재전송 시점") != std::string::npos) return "재전송이 설정한 응답 제한시간 기준보다 너무 이르거나 늦었습니다. 재전송 증적의 실제 수신 간격과 허용 구간을 확인하세요.";
    if (detail.find("개시") != std::string::npos) return "선택한 연결 방식과 Login의 개시 유형 또는 Initiate 교환 순서가 다릅니다. 양쪽의 개시요청 사용 설정과 송수신 기록을 확인하세요.";
    if (detail.find("인코딩 제안") != std::string::npos) return "대상의 Login에 시험 시스템이 지원하는 BER(2.1.1)이 포함되지 않았습니다. 합의한 인코딩 제안 목록을 확인하세요.";
    if (detail.find("계정") != std::string::npos) return "대상이 보낸 로그인 정보가 시험 설정과 다릅니다. 양쪽 시험 계정 설정을 확인하세요.";
    if (detail.find("도메인") != std::string::npos) return "송신·수신 시스템 식별정보가 시험 설정과 다릅니다. 양쪽 Domain Name 설정을 확인하세요.";
    if (detail.find("H/R") != std::string::npos) return "대상의 로그인에 포함된 최대 무수신 시간 또는 응답 제한 시간이 시험 설정과 다릅니다. 양쪽 시간 설정을 맞추세요.";
    if (detail.find("Reject") != std::string::npos || detail.find("거부") != std::string::npos) return "이 오류 조건에 필요한 거부 응답 또는 거부 사유·대응 식별정보가 확인되지 않았습니다. 제시된 확인 기준과 대상의 회신을 비교하세요.";
    if (detail.find("Accept") != std::string::npos || detail.find("ACK") != std::string::npos || detail.find("대응하지") != std::string::npos) return "보낸 요청에 맞는 수용 응답 또는 대응 번호를 확인하지 못했습니다. 요청과 응답의 종류·식별정보를 비교하세요.";
    if (detail.find("디코딩") != std::string::npos || detail.find("decoding") != std::string::npos || detail.find("BER") != std::string::npos) return "메시지를 적용 규격에 따라 디코딩하지 못했습니다. 수신 원문과 메시지 형식·인코딩을 확인하세요.";
    if ((detail.find("취소 후") != std::string::npos || detail.find("취소 수용 후") != std::string::npos)) return "구독 취소 수용 뒤에도 새 정보가 제공되었습니다. 취소 수용 시각과 이후 발행 기록을 확인하세요.";
    if (detail.find("주기") != std::string::npos || detail.find("표본") != std::string::npos || detail.find("Publication 2회") != std::string::npos) return "주기 제공의 수신 횟수 또는 간격이 확인 기준을 충족하지 못했습니다. 요청 주기와 실제 수신 시각을 확인하세요.";
    if (detail.find("Publication") != std::string::npos || detail.find("Subscription") != std::string::npos || detail.find("프로파일") != std::string::npos || detail.find("MessageFrame") != std::string::npos || detail.find("PDU") != std::string::npos) return "요청한 연계정보의 종류·식별정보 또는 내용 형식이 확인 기준과 다릅니다. 구독 요청과 제공된 메시지를 비교하세요.";
    if (detail.find("FrED") != std::string::npos) return "연결 확인 메시지를 정상 교환하지 못했습니다. 대상의 연결 유지 기록을 확인하세요.";
    return "이 단계의 확인을 완료하지 못했습니다. 직전 절차와 확인 기준에 해당하는 송수신 증적을 확인하세요. 상세 진단 기록은 시험 기록에 보관됩니다.";
}
inline std::string resultDescription(const Case &c, const Result &r, const std::string &stage = "") {
    if (r.verdict == Verdict::Stopped) return "중지 — 사용자의 중지 요청으로 확인을 마치지 못했습니다. 완료되지 않은 절차는 다시 시험해야 합니다.";
    if (r.verdict == Verdict::Fail || r.verdict == Verdict::Error)
        return std::string(r.verdict == Verdict::Error ? "시험 수행 오류" : "확인 기준 미충족") + " — " + failureExplanation(r.detail) + (stage.empty() ? "" : " 확인하던 절차: " + stage);
    if (r.test.compare(0, 7, "normal_") == 0) return c.role == Role::Server
        ? linkedInformation(c, r.test) + "의 정상 정보 제공과 Publication Accept, 관찰 구간 내 rejectPublicationData 없음, 연결 유지와 정상 종료를 확인했습니다. 시험 기준에 따라 정상 처리로 판정합니다."
        : linkedInformation(c, r.test) + "의 정보요청·수신·ASN.1 디코딩과 연결 유지를 확인했습니다.";
    if (r.test == "session") return "로그인 수용과 연결 확인 메시지 2회 교환을 확인했습니다.";
    if (r.test == "abnormal_session") return r.observationsJson.find("\"tcpClosed\":false") != std::string::npos
        ? "정상 유지·송신 중단·관찰 절차를 완료했습니다. TCP 종료는 관측되지 않았습니다. 별도 자료 제출 절차 없이 정상 시험 완료로 성공 처리합니다."
        : "정상 연결 유지 후 송신을 중단했고, 최대 무수신 시간 이상·관찰 기한 이내에 대상의 TCP 연결 종료를 확인했습니다. 시험 기준에 따라 적합입니다.";
    if (r.test == "invalid_login") return "잘못된 비밀번호에 대한 로그인 거부와 해당 거부 사유를 확인했습니다.";
    if (r.test == "duplicate_login") return "중복 로그인 거부 사유와 기존 연결의 유지를 확인했습니다.";
    if (r.test == "invalid_subscription") return "지원하지 않는 정보요청에 대한 거부 사유와 연결 유지를 확인했습니다.";
    if (r.test == "cancel") return "취소 전 주기 제공, 취소 수용, 취소 후 한 주기 동안 새 정보 없음과 연결 유지를 확인했습니다.";
    if (r.test == "login_retry" || r.test == "subscription_retry" || r.test == "publication_retry") return "원본과 재전송의 번호·시각·전체 내용이 일치하고, 수용 후 연결이 유지됨을 확인했습니다.";
    return "의도적으로 제공한 오류에 대한 수신 확인 응답, 해당 거부 사유·대응 식별정보와 연결 유지를 확인했습니다.";
}
} // namespace datex
