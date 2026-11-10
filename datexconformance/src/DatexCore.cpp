#include "DatexCore.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>

namespace datex {
const std::vector<Case> &cases() {
    static const std::vector<Case> c = {{"centerClient2rse_v2",
                                         "RSE BSM 정보제공시험",
                                         Role::Client,
                                         "1.0.15784.1.0.2",
                                         {{"bsm", 82050, 20}}},
                                        {"rseServer2center_v2",
                                         "통합교통관제시스템 BSM 정보요청시험",
                                         Role::Server,
                                         "1.0.15784.1.0.2",
                                         {{"bsm", 82050, 20}}},
                                        {"rseClient2center_v2",
                                         "통합교통관제시스템 MAP/RSA/TIM 정보제공시험",
                                         Role::Client,
                                         "1.0.15784.1.0.1",
                                         {{"map", 82056, 18}, {"rsa", 82053, 27}, {"tim", 82054, 31}}},
                                        {"centerServer2rse_v2",
                                         "RSE MAP/RSA/TIM 정보요청시험",
                                         Role::Server,
                                         "1.0.15784.1.0.1",
                                         {{"map", 82056, 18}, {"rsa", 82053, 27}, {"tim", 82054, 31}}},
                                        {"signalserverServer2center_v2",
                                         "통합교통관제시스템 SPaT/TLSM 정보요청시험",
                                         Role::Server,
                                         "1.0.14827.1.1.0",
                                         {{"spat", 82055, 19}, {"tls", 0, 50}}},
                                        {"centerClient2signalserver_v2", "신호정보 수집서버 SPaT·TLSM 정보제공시험",
                                         Role::Client, "1.0.14827.1.1.0", {{"spat", 82055, 19}, {"tls", 0, 50}}, "신호정보 수집서버"},
                                        {"vehicleServer2center_v2", "통합교통관제시스템의 자율주행차량 BSM 정보요청시험",
                                         Role::Server, "1.0.15784.1.0.2", {{"bsm", 82050, 20}}, "통합교통관제시스템"},
                                        {"centerClient2vehicle_v2", "자율주행차량 BSM 정보제공시험",
                                         Role::Client, "1.0.15784.1.0.2", {{"bsm", 82050, 20}}, "자율주행차량"},
                                        {"vehicleClient2center_v2", "통합교통관제시스템의 자율주행차량 SPaT/RSA/TIM 정보제공시험",
                                         Role::Client, "1.0.14827.1.1.0",
                                         {{"spat", 82055, 19}, {"rsa", 82053, 27, "1.0.15784.1.0.1"},
                                          {"tim", 82054, 31, "1.0.15784.1.0.1"},
                                          {"tim_speed", 82054, 31, "1.0.15784.1.0.1", 1},
                                          {"tim_lane", 82054, 31, "1.0.15784.1.0.1", 2}}, "통합교통관제시스템"},
                                        {"centerServer2vehicle_v2", "자율주행차량 SPaT/RSA/TIM 정보요청시험",
                                         Role::Server, "1.0.14827.1.1.0",
                                         {{"spat", 82055, 19}, {"rsa", 82053, 27, "1.0.15784.1.0.1"},
                                          {"tim", 82054, 31, "1.0.15784.1.0.1"},
                                          {"tim_speed", 82054, 31, "1.0.15784.1.0.1", 1},
                                          {"tim_lane", 82054, 31, "1.0.15784.1.0.1", 2}}, "자율주행차량"},
                                        {"vehicleServer2rse_v2", "RSE BSM 정보요청시험", Role::Server, "1.0.15784.1.0.2", {{"bsm", 82050, 20}}, "RSE"},
                                        {"vehicleClient2rse_v2", "RSE SPaT·MAP·RSA·TIM 정보제공시험", Role::Client, "1.0.14827.1.1.0", {{"spat", 82055, 19}, {"map", 82056, 18, "1.0.15784.1.0.1"}, {"rsa", 82053, 27, "1.0.15784.1.0.1"}, {"tim", 82054, 31, "1.0.15784.1.0.1"}, {"tim_speed", 82054, 31, "1.0.15784.1.0.1", 1}, {"tim_lane", 82054, 31, "1.0.15784.1.0.1", 2}, {"tim_regional", 82054, 31, "1.0.15784.1.0.1", 3}}, "RSE"},
                                        {"rseClient2vehicle_v2", "자율주행차량 BSM 정보제공시험", Role::Client, "1.0.15784.1.0.2", {{"bsm", 82050, 20}}, "자율주행차량"},
                                        {"rseServer2vehicle_v2", "자율주행차량 SPaT·MAP·RSA·TIM 정보요청시험", Role::Server, "1.0.14827.1.1.0", {{"spat", 82055, 19}, {"map", 82056, 18, "1.0.15784.1.0.1"}, {"rsa", 82053, 27, "1.0.15784.1.0.1"}, {"tim", 82054, 31, "1.0.15784.1.0.1"}, {"tim_speed", 82054, 31, "1.0.15784.1.0.1", 1}, {"tim_lane", 82054, 31, "1.0.15784.1.0.1", 2}, {"tim_regional", 82054, 31, "1.0.15784.1.0.1", 3}}, "자율주행차량"}};
    return c;
}
const Case &findCase(const std::string &id) {
    for (auto &c : cases())
        if (id == c.id)
            return c;
    throw Failure("등록되지 않은 신규 DATEX case: " + id);
}
Case messageCase(const Case &c, const Message &m) {
    Case result = c;
    result.oid = m.oid ? m.oid : c.oid;
    result.messages = {m};
    return result;
}
Case subscriptionCase(const Case &c, const std::string &oid) {
    Case result = c;
    result.messages.clear();
    for (auto m : c.messages) {
        auto effective = messageCase(c, m);
        if (oid == effective.oid) {
            result.oid = effective.oid;
            result.messages.push_back(m);
        }
    }
    if (result.messages.empty()) throw Failure("지원하지 않는 구독 OID: " + oid);
    return result;
}
namespace {
class Parser {
    const std::string &s;
    size_t p = 0;
    unsigned depth = 0;
    size_t maximumBytes;
    unsigned maximumDepth;
    void ws() {
        while (p < s.size() && (s[p] == ' ' || s[p] == '\r' || s[p] == '\n' || s[p] == '\t'))
            ++p;
    }
    bool take(char c) {
        ws();
        if (p < s.size() && s[p] == c) {
            ++p;
            return true;
        }
        return false;
    }
    void need(char c) {
        if (!take(c))
            throw Failure("JSON 구문 오류");
    }
    unsigned hex4() {
        unsigned n = 0;
        for (int i = 0; i < 4; ++i) {
            if (p >= s.size())
                throw Failure("JSON unicode 오류");
            char c = s[p++];
            unsigned v = c >= '0' && c <= '9'   ? c - '0'
                         : c >= 'a' && c <= 'f' ? c - 'a' + 10
                         : c >= 'A' && c <= 'F' ? c - 'A' + 10
                                                : 99;
            if (v > 15)
                throw Failure("JSON unicode 오류");
            n = n * 16 + v;
        }
        return n;
    }
    static void utf8(std::string &out, unsigned cp) {
        if (cp < 128)
            out += char(cp);
        else if (cp < 2048) {
            out += char(0xc0 | (cp >> 6));
            out += char(0x80 | (cp & 63));
        } else if (cp < 65536) {
            out += char(0xe0 | (cp >> 12));
            out += char(0x80 | ((cp >> 6) & 63));
            out += char(0x80 | (cp & 63));
        } else {
            out += char(0xf0 | (cp >> 18));
            out += char(0x80 | ((cp >> 12) & 63));
            out += char(0x80 | ((cp >> 6) & 63));
            out += char(0x80 | (cp & 63));
        }
    }
    std::string str() {
        need('"');
        std::string out;
        while (p < s.size()) {
            unsigned char c = s[p++];
            if (c == '"')
                return out;
            if (c < 32)
                throw Failure("JSON 제어문자");
            if (c != '\\') {
                out += char(c);
                continue;
            }
            if (p == s.size())
                break;
            c = s[p++];
            switch (c) {
            case '"':
            case '\\':
            case '/':
                out += char(c);
                break;
            case 'b':
                out += '\b';
                break;
            case 'f':
                out += '\f';
                break;
            case 'n':
                out += '\n';
                break;
            case 'r':
                out += '\r';
                break;
            case 't':
                out += '\t';
                break;
            case 'u': {
                unsigned cp = hex4();
                if (cp >= 0xd800 && cp <= 0xdbff) {
                    if (p + 2 > s.size() || s.substr(p, 2) != "\\u")
                        throw Failure("JSON surrogate 오류");
                    p += 2;
                    unsigned lo = hex4();
                    if (lo < 0xdc00 || lo > 0xdfff)
                        throw Failure("JSON surrogate 오류");
                    cp = 0x10000 + ((cp - 0xd800) << 10) + (lo - 0xdc00);
                } else if (cp >= 0xdc00 && cp <= 0xdfff)
                    throw Failure("JSON surrogate 오류");
                utf8(out, cp);
                break;
            }
            default:
                throw Failure("JSON escape 오류");
            }
        }
        throw Failure("JSON 문자열 종료 누락");
    }
    Json value() {
        ws();
        if (++depth > maximumDepth)
            throw Failure("JSON 중첩 제한");
        Json j;
        if (p >= s.size())
            throw Failure("JSON 값 누락");
        char c = s[p];
        if (c == '{') {
            ++p;
            j.kind = Json::Object;
            if (!take('}')) {
                do {
                    std::string k = str();
                    need(':');
                    if (!j.object.emplace(k, value()).second)
                        throw Failure("JSON 중복 항목: " + k);
                } while (take(','));
                need('}');
            }
        } else if (c == '[') {
            ++p;
            j.kind = Json::Array;
            if (!take(']')) {
                do {
                    j.array.push_back(value());
                } while (take(','));
                need(']');
            }
        } else if (c == '"') {
            j.kind = Json::String;
            j.text = str();
        } else if (s.compare(p, 4, "true") == 0) {
            p += 4;
            j.kind = Json::Bool;
            j.boolean = true;
        } else if (s.compare(p, 5, "false") == 0) {
            p += 5;
            j.kind = Json::Bool;
        } else if (s.compare(p, 4, "null") == 0) {
            p += 4;
        } else {
            size_t a = p;
            if (s[p] == '-')
                ++p;
            if (p == s.size() || s[p] < '0' || s[p] > '9')
                throw Failure("JSON 숫자 오류");
            if (s[p] == '0')
                ++p;
            else
                while (p < s.size() && s[p] >= '0' && s[p] <= '9')
                    ++p;
            if (p < s.size() && s[p] == '.') {
                ++p;
                size_t d = p;
                while (p < s.size() && s[p] >= '0' && s[p] <= '9')
                    ++p;
                if (d == p)
                    throw Failure("JSON 소수 오류");
            }
            if (p < s.size() && (s[p] == 'e' || s[p] == 'E')) {
                ++p;
                if (p < s.size() && (s[p] == '+' || s[p] == '-'))
                    ++p;
                size_t d = p;
                while (p < s.size() && s[p] >= '0' && s[p] <= '9')
                    ++p;
                if (d == p)
                    throw Failure("JSON 지수 오류");
            }
            j.kind = Json::Number;
            j.text = s.substr(a, p - a);
        }
        --depth;
        return j;
    }

  public:
    explicit Parser(const std::string &src, size_t bytes = 65536, unsigned levels = 24)
        : s(src), maximumBytes(bytes), maximumDepth(levels) {}
    Json parse() {
        if (s.size() > maximumBytes)
            throw Failure("설정 크기 제한");
        Json j = value();
        ws();
        if (p != s.size())
            throw Failure("JSON 후행 데이터");
        return j;
    }
};
std::string stringValue(const Json &j, const char *name, bool required = true) {
    auto p = j.get(name);
    if (!p || p->kind == Json::Null) {
        if (required)
            throw Failure(std::string("필수 입력: ") + name);
        return {};
    }
    if (p->kind != Json::String || p->text.find('\0') != std::string::npos || p->text.size() > 1024)
        throw Failure(std::string("문자열 입력 오류: ") + name);
    if (required && p->text.empty())
        throw Failure(std::string("필수 입력: ") + name);
    return p->text;
}
unsigned integer(const Json &j, const char *name, unsigned fallback, unsigned max) {
    auto p = j.get(name);
    if (!p || p->kind == Json::Null || (p->kind == Json::String && p->text.empty()))
        return fallback;
    if (p->kind != Json::String && p->kind != Json::Number)
        throw Failure(std::string("정수 입력 오류: ") + name);
    if (p->text.empty())
        throw Failure("빈 정수");
    std::uint64_t n = 0;
    for (char c : p->text) {
        if (c < '0' || c > '9')
            throw Failure(std::string("양의 정수 필요: ") + name);
        n = n * 10 + (c - '0');
        if (n > max)
            throw Failure(std::string("입력 범위 초과: ") + name);
    }
    if (n == 0)
        throw Failure(std::string("0은 허용하지 않습니다: ") + name);
    return unsigned(n);
}
} // namespace
Json Json::parse(const std::string &s) {
    return Parser(s).parse();
}
Json Json::parseData(const std::string &s) {
    return Parser(s, 8 * 1024 * 1024, 64).parse();
}
const Json *Json::get(const std::string &key) const {
    auto i = object.find(key);
    return i == object.end() ? nullptr : &i->second;
}
std::string quote(const std::string &s) {
    std::string r = "\"";
    const char *hex = "0123456789abcdef";
    for (unsigned char c : s) {
        if (c == '"' || c == '\\') {
            r += '\\';
            r += char(c);
        } else if (c < 32) {
            r += "\\u00";
            r += hex[c >> 4];
            r += hex[c & 15];
        } else
            r += char(c);
    }
    return r + '"';
}
std::vector<std::string> availableTests(const Case &c) {
    std::vector<std::string> t = {"session"};
    for (auto m : c.messages)
        t.push_back(std::string("normal_") + m.name);
    if (c.role == Role::Client)
        t.insert(t.end(), {"invalid_login", "duplicate_login", "abnormal_session", "invalid_subscription",
                           "publication_retry", "cancel"});
    else
        t.insert(t.end(), {"login_retry", "subscription_retry", "unknownSubscription",
                           "unknownPublicationNbr", "unknownPublicationMsgId", "invalidPublicationMsgId",
                           "invalidPublicationMsgContent", "repeatedPublicationNbr"});
    return t;
}
Config Config::parse(const Case &c, const std::string &json) {
    Json j = Json::parse(json);
    if (j.kind != Json::Object)
        throw Failure("설정은 JSON 객체여야 합니다.");
    Config r;
    r.myDomain = stringValue(j, "my_domain");
    r.peerDomain = stringValue(j, "peer_domain");
    r.user = stringValue(j, "user");
    r.password = stringValue(j, "pass");
    if (auto mode = j.get("use_initiate")) {
        if (mode->kind != Json::Bool) throw Failure("개시요청 사용 설정은 boolean이어야 합니다.");
        r.useInitiate = mode->boolean;
    }
    const bool connects = r.tcpConnects(c);
    r.host = stringValue(j, "peer_ip", connects);
    r.port = integer(j, connects ? "peer_port" : "local_port", 0, 65535);
    if (!r.port)
        throw Failure("포트가 필요합니다.");
    r.heartbeat = integer(j, "hb_dur", 60, 65535);
    r.response = integer(j, "rsp_timeout", 40, 255);
    r.maintain = integer(j, "fred_maintain_s", 300, 86400);
    r.receive = integer(j, "receive_s", 120, 86400);
    r.period = integer(j, "period_s", 15, 86400);
    r.connectTimeout = integer(j, "connect_timeout_s", 40, 600);
    r.invalidPassword = stringValue(j, "invalid_pass", false);
    if (r.invalidPassword.empty())
        r.invalidPassword = r.password + "_invalid";
    for (auto &t : availableTests(c)) {
        auto v = j.get("test_" + t);
        if (v) {
            if (v->kind != Json::Bool)
                throw Failure("시험 선택은 boolean이어야 합니다.");
            if (v->boolean)
                r.tests.insert(t);
        }
    }
    if (r.tests.empty())
        throw Failure("하나 이상의 시험을 선택하세요.");
    if (r.tests.count("invalid_login") && r.invalidPassword == r.password)
        throw Failure("무효 비밀번호는 정상 비밀번호와 달라야 합니다.");
    return r;
}
std::string testTitle(const Case &c, const std::string &test) {
    const bool client = c.role == Role::Client;
    const std::map<std::string, std::string> labels = {
        {"session", "정상 세션 설정 시험"},
        {"normal_bsm", std::string(c.targetLabel ? c.targetLabel : (client ? "RSE" : "통합교통관제시스템")) +
                           (client ? " BSM 정보제공 시험" : " BSM 정보요청 시험")},
        {"normal_map", client ? "MAP 정보제공 시험" : "MAP 정보요청 시험"},
        {"normal_rsa", client ? "RSA 정보제공 시험" : "RSA 정보요청 시험"},
        {"normal_tim", client ? "TIM 정보제공 시험" : "TIM 정보요청 시험"},
        {"normal_tim_regional", client ? "TIM 국내 확장정보 제공 시험" : "TIM 국내 확장정보 요청 시험"},
        {"normal_tim_speed", client ? "TIM 제한속도 변경 정보제공 시험" : "TIM 제한속도 변경 정보요청 시험"},
        {"normal_tim_lane", client ? "TIM 차로변경 정보제공 시험" : "TIM 차로변경 정보요청 시험"},
        {"normal_spat", client ? "SPaT 정보제공 시험" : "SPaT 정보요청 시험"}, {"normal_tls", client ? "TLSM 정보제공 시험" : "TLSM 정보요청 시험"},
        {"invalid_login", "잘못된 로그인 거부 시험"},
        {"duplicate_login", "중복 로그인 거부 시험"},
        {"abnormal_session", "비정상 세션 감지 시험"},
        {"invalid_subscription", "잘못된 정보요청 거부 시험"},
        {"publication_retry", "정보제공 메시지 재전송 시험"},
        {"login_retry", "로그인 메시지 재전송 시험"},
        {"subscription_retry", "정보요청 메시지 재전송 시험"},
        {"cancel", "주기 정보제공 및 구독취소 시험"},
        {"unknownSubscription", "미등록 구독 정보제공 메시지 거부 시험"},
        {"unknownPublicationNbr", "잘못된 발행번호 거부 시험"},
        {"unknownPublicationMsgId", "알 수 없는 정보제공 메시지 식별자 거부 시험"},
        {"invalidPublicationMsgId", "구독과 다른 정보제공 메시지 식별자 거부 시험"},
        {"invalidPublicationMsgContent", "잘못된 정보제공 내용 거부 시험"},
        {"repeatedPublicationNbr", "중복 발행번호 거부 시험"}};
    return labels.at(test);
}
std::string configureUI(const Case &c) {
    const bool client = c.role == Role::Client;
    std::string r = "{\"scenarios\":[";
    bool itemFirst = true;
    for (auto t : availableTests(c)) {
        if (!itemFirst)
            r += ',';
        itemFirst = false;
        r += "{\"key\":" + quote("test_" + t) + ",\"title\":" + quote(testTitle(c, t)) + "}";
    }
    r += "],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"col\"},\"components\":[{"
         "\"type\":\"FieldSet\",\"option\":{\"label\":\"접속 및 세션 설정\"},\"components\":[";
    bool first = true;
    auto field = [&](std::string name, std::string label, std::string type, std::string value = "") {
        if (!first)
            r += ',';
        first = false;
        r += "{\"type\":\"Input\",\"option\":{\"name\":" + quote(name) + ",\"label\":" + quote(label) +
             ",\"type\":" + quote(type);
        if (!value.empty())
            r += ",\"value\":" + quote(value);
        r += "}}";
    };
    field("my_domain",
          client ? "시험 시스템 (ISO 14827 Client · 정보 요청) Domain Name" : "시험 시스템 (ISO 14827 Server · 정보 제공) Domain Name",
          "text");
    field("peer_domain",
          client ? "시험 대상 시스템 (ISO 14827 Server · 정보 제공) Domain Name"
                 : "시험 대상 시스템 (ISO 14827 Client · 정보 요청) Domain Name",
          "text");
    const std::string outgoing = client ? "일반 연결에서 사용" : "개시요청 사용 시 적용";
    const std::string incoming = client ? "개시요청 사용 시 적용" : "일반 연결에서 사용";
    field("peer_ip", "시험대상 IP 주소 (" + outgoing + ")", "text");
    field("peer_port", "시험대상 수신 대기 포트 (" + outgoing + ")", "number");
    field("local_port", "시험시스템 수신 대기 포트 (" + incoming + ")", "number");
    field("user", "사용자 이름", "text");
    field("pass", "비밀번호", "password");
    field("hb_dur", "HeartbeatDurationMax (초)", "number", "60");
    field("rsp_timeout", "응답 제한 시간 (초)", "number", "40");
    field("connect_timeout_s", "접속 대기 시간 (초)", "number", "40");
    field("use_initiate", "개시요청 사용 (선택: ISO Server가 TCP 접속 후 Initiate / 해제: ISO Client가 TCP 접속 후 Login)", "checkbox");
    if (client) {
        field("invalid_pass", "무효 로그인 시험용 비밀번호 (선택)", "password");
        field("fred_maintain_s", "FrED 교환 유지시간 (초)", "number", "300");
        field("receive_s", "취소 전 수신시간 (초)", "number", "120");
        field("period_s", "등록 구독 요청 주기 (초)", "number", "15");
    }
    r += " ]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"시험 항목\"},\"components\":[";
    first = true;
    for (auto t : availableTests(c)) {
        field("test_" + t, testTitle(c, t), "checkbox");
    }
    return r + "]}]}]}";
}
RetryComparison compareRetry(const PacketRecord &a, const PacketRecord &b) {
    return {a.number == b.number, a.hasTimestamp && b.hasTimestamp && a.timestamp == b.timestamp,
            a.content == b.content};
}
std::string RetryComparison::json() const {
    return std::string("{\"packetNumberEqual\":") + (number ? "true" : "false") +
           ",\"timestampEqual\":" + (timestamp ? "true" : "false") +
           ",\"contentEqual\":" + (content ? "true" : "false") + "}";
}
PeriodTracker::PeriodTracker(unsigned p, bool initialShort) : period_(p), initialShort_(initialShort) {
    if (!p)
        throw Failure("주기는 양수여야 합니다.");
}
RetryTiming compareRetryTiming(const PacketRecord &first, const PacketRecord &second, unsigned responseSeconds) {
    RetryTiming timing;
    timing.elapsedUs = std::chrono::duration_cast<std::chrono::microseconds>(second.received-first.received).count();
    timing.expectedUs = std::int64_t(responseSeconds)*1000000;
    timing.earlyAllowanceUs = std::min<std::int64_t>(100000,timing.expectedUs/10);
    return timing;
}
std::string RetryTiming::json() const {
    return "{\"elapsedUs\":"+std::to_string(elapsedUs)+",\"expectedUs\":"+std::to_string(expectedUs)+
        ",\"earlyAllowanceUs\":"+std::to_string(earlyAllowanceUs)+",\"lateAllowanceUs\":"+std::to_string(lateAllowanceUs)+
        ",\"withinWindow\":"+(within()?"true":"false")+"}";
}
void PeriodTracker::receive(Tick now, bool retry) {
    if (retry)
        return;
    if (count_) {
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(now - last_).count();
        auto base = std::int64_t(period_) * 1000000;
        if (!(initialShort_ && count_ == 1 && us >= 0 && us < base * 9 / 10)) {
            if (us < base * 9 / 10 || us > base * 11 / 10)
                throw Failure("Publication 주기 ±10% 범위 위반");
            ++intervals_;
        }
    }
    ++count_;
    last_ = now;
}
bool PeriodTracker::overdue(Tick now) const {
    return count_ && now - last_ > std::chrono::milliseconds(std::uint64_t(period_) * 1100);
}
const char *verdictName(Verdict v) {
    switch (v) {
    case Verdict::Pass:
        return "SUCCESS";
    case Verdict::Fail:
        return "FAIL";
    case Verdict::Error:
        return "ERROR";
    case Verdict::Stopped:
        return "STOPPED";
    default:
        return "ERROR";
    }
}
} // namespace datex
