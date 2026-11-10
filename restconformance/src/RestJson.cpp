#include "RestCore.h"
#include <sstream>
namespace rest {
namespace {
class Parser {
    const std::string &s;
    size_t p = 0;
    unsigned depth = 0;
    size_t maxBytes;
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
        if (++depth > 24)
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
    explicit Parser(const std::string &src, size_t limit) : s(src), maxBytes(limit) {}
    Json parse() {
        if (s.size() > maxBytes)
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
Json Json::parse(const std::string &s, size_t maxBytes) {
    return Parser(s,maxBytes).parse();
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

Config Config::parse(const std::string &source) {
    const auto j = Json::parse(source);
    if (j.kind != Json::Object) throw Failure("설정은 JSON 객체여야 합니다.");
    Config c;
    c.apiKey = stringValue(j, "api_key");
    auto bind = stringValue(j,"bind_ip",false);
    if (!bind.empty()) c.bindIp = bind;
    c.fixturePath = stringValue(j,"response_xml_file",false);
    c.port = integer(j,"local_port",55307,65535);
    c.repetitions = integer(j,"repetitions",10,1000);
    c.requestTimeout = integer(j,"request_timeout_s",30,3600);
    auto selected = j.get("test_normal_utic");
    if (!selected || selected->kind != Json::Bool || !selected->boolean)
        throw Failure("UT 센터 돌발정보 요청시험을 선택하세요.");
    return c;
}
std::string configureUI() {
    return R"JSON({"scenarios":[{"key":"test_normal_utic","title":"UT 센터 돌발정보 요청시험"}],"configuration":[{"type":"Div","option":{"direction":"col"},"components":[{"type":"FieldSet","option":{"label":"UTIC 정보제공 접점 설정"},"components":[{"type":"Input","option":{"name":"bind_ip","label":"시험시스템 수신 대기 IP 주소","type":"text","value":"127.0.0.1"}},{"type":"Input","option":{"name":"local_port","label":"시험시스템 HTTP 수신 대기 포트","type":"number","value":"55307"}},{"type":"Input","option":{"name":"api_key","label":"UT 센터 요청에 사용할 시험용 key","type":"password"}},{"type":"Input","option":{"name":"response_xml_file","label":"응답 XML 파일 경로 (미입력 시 기본 시험 자료)","type":"text"}},{"type":"Input","option":{"name":"repetitions","label":"단일 정보교환 반복 횟수 (기본 10회)","type":"number","value":"10"}},{"type":"Input","option":{"name":"request_timeout_s","label":"회당 요청·응답 전송 대기시간 (초, 시험환경 설정)","type":"number","value":"30"}}]},{"type":"FieldSet","option":{"label":"시험 항목"},"components":[{"type":"Input","option":{"name":"test_normal_utic","label":"UT 센터 돌발정보 요청시험","type":"checkbox"}}]}]}]})JSON";
}
}
