#include "RestCore.h"
#include <windows.h>
#include "StandardFields.h"
#include <xmllite.h>
#include <shlwapi.h>
#include <wrl/client.h>
#include <openssl/sha.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>
#include <cmath>
#include <set>
#pragma comment(lib, "xmllite.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "ole32.lib")

namespace rest {
namespace {
std::string utf8(const wchar_t *value, unsigned length) {
    if (!length) return {};
    int n = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, value, int(length), nullptr, 0, nullptr, nullptr);
    if (n <= 0) throw Failure("XML UTF-8 변환 실패");
    std::string out(n, '\0');
    WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, value, int(length), out.data(), n, nullptr, nullptr);
    return out;
}
unsigned characters(const std::string &value) {
    return static_cast<unsigned>(standard::characters(value));
}
bool date(const std::string &s) {
    std::smatch match;
    static const std::regex compact("^([0-9]{4})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})$");
    static const std::regex korean("^([0-9]{4})년 ([0-9]{1,2})월 ([0-9]{1,2})일 ([0-9]{1,2})시 ([0-9]{1,2})분$");
    if (!std::regex_match(s, match, compact) && !std::regex_match(s, match, korean)) return false;
    int y = std::stoi(match[1]), m = std::stoi(match[2]), d = std::stoi(match[3]);
    int h = std::stoi(match[4]), minute = std::stoi(match[5]);
    int second = match.size() > 6 ? std::stoi(match[6]) : 0;
    if (y < 1 || m < 1 || m > 12 || h > 23 || minute > 59 || second > 59) return false;
    const int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int limit = days[m - 1] + (m == 2 && (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) ? 1 : 0);
    return d >= 1 && d <= limit;
}
void validate(const Incident &incident) {
    const std::map<std::string,unsigned> required = {
        {"incidentId",12},{"incidenteTypeCd",10},{"incidenteSubTypeCd",10},
        {"addressJibun",100},{"addressJibunCd",20},{"addressNew",100},{"linkId",10},
        {"incidenteTrafficCd",10},{"incidenteGradeCd",10},
        {"incidentTitle",500},{"incidentRegionCd",2},{"startDate",40},{"endDate",40},
        {"lane",10},{"roadName",50},{"controlType",2},{"lineLinkId",1000},{"important",5},{"updateDate",40}};
    for (const auto &rule : required) {
        auto i = incident.fields.find(rule.first);
        if (i == incident.fields.end() || i->second.empty()) throw Failure("UTIC 필수 필드 누락: " + rule.first);
        standard::text(i->second,rule.second,"UTIC."+rule.first);
    }
    for (auto name : {"locationDataX","locationDataY"}) {
        auto i=incident.fields.find(name);
        if(i==incident.fields.end()||i->second.empty())throw Failure(std::string("UTIC 필수 필드 누락: ")+name);
        standard::decimal(i->second,15,9,std::string("UTIC.")+name);
    }
    // M/O '-' is not made mandatory. Check these fields when supplied.
    for(const auto &rule:std::map<std::string,unsigned>{{"sourceCode",5},{"locationTypeCd",5},{"locationData",3000}}){
        auto i=incident.fields.find(rule.first);
        if(i!=incident.fields.end())standard::text(i->second,rule.second,"UTIC."+rule.first,false);
    }
    auto location=incident.fields.find("locationTypeCd");
    if(location!=incident.fields.end()&&!location->second.empty()&&
       !std::set<std::string>{"C0101","C0102","C1013"}.count(location->second))
        throw Failure("UTIC.locationTypeCd: 좌표유형 코드 오류");
    for (auto name : {"startDate","endDate","updateDate"})
        if (!date(incident.fields.at(name))) throw Failure(std::string("UTIC 일시 형식 오류: ") + name);
    if (!std::set<std::string>{"1","2","3","4","5","6"}.count(incident.fields.at("incidenteTypeCd")))
        throw Failure("UTIC 돌발유형 코드 오류");
    if (!std::set<std::string>{"A0501","A0502","A0503"}.count(incident.fields.at("incidenteTrafficCd")))
        throw Failure("UTIC 소통등급 코드 오류");
    if (!std::set<std::string>{"A0401","A0402","A0403"}.count(incident.fields.at("incidenteGradeCd")))
        throw Failure("UTIC 돌발등급 코드 오류");
    if (!std::set<std::string>{"0","1","2"}.count(incident.fields.at("controlType")))
        throw Failure("UTIC 통제형태 코드 오류");
    if (!std::set<std::string>{"00","01"}.count(incident.fields.at("important")))
        throw Failure("UTIC 중요도 코드 오류");
}
}
std::string sha256(const std::string &data) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    if (!SHA256(reinterpret_cast<const unsigned char *>(data.data()), data.size(), digest))
        throw Failure("SHA-256 계산 실패");
    const char *hex = "0123456789abcdef";
    std::string out;
    for (auto byte : digest) { out += hex[byte >> 4]; out += hex[byte & 15]; }
    return out;
}
std::string readTextFile(const std::string &path) {
    auto p = std::filesystem::u8path(path);
    if (std::filesystem::file_size(p) > 1024 * 1024) throw Failure("XML 자료는 1 MiB 이하로 지정하세요.");
    std::ifstream f(p, std::ios::binary);
    if (!f) throw Failure("XML 자료 파일을 열 수 없습니다.");
    std::ostringstream out; out << f.rdbuf();
    auto data = out.str();
    if (data.compare(0,3,"\xef\xbb\xbf") == 0) data.erase(0,3);
    return data;
}
std::vector<Incident> parseUticXml(const std::string &xml, bool allowEmpty) {
    if (xml.empty() || xml.size() > 1024 * 1024 || xml.find('\0') != std::string::npos)
        throw Failure("XML 자료 크기 또는 문자열 오류");
    characters(xml);
    Microsoft::WRL::ComPtr<IStream> stream;
    stream.Attach(SHCreateMemStream(reinterpret_cast<const BYTE *>(xml.data()), static_cast<UINT>(xml.size())));
    Microsoft::WRL::ComPtr<IXmlReader> reader;
    if (!stream || FAILED(CreateXmlReader(__uuidof(IXmlReader), reinterpret_cast<void **>(reader.GetAddressOf()), nullptr)))
        throw Failure("XML 읽기 도구 생성 실패");
    if (FAILED(reader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)) ||
        FAILED(reader->SetInput(stream.Get()))) throw Failure("XML 읽기 설정 실패");
    std::vector<Incident> records;
    Incident current;
    std::string field;
    bool root = false, inRecord = false;
    XmlNodeType type;
    HRESULT status;
    while ((status = reader->Read(&type)) == S_OK) {
        unsigned depth = 0; reader->GetDepth(&depth);
        // XmlLite reports EndElement depth before removing that element.
        if (type == XmlNodeType_EndElement && depth) --depth;
        const wchar_t *name = nullptr; unsigned length = 0;
        if (type == XmlNodeType_Element || type == XmlNodeType_EndElement) {
            reader->GetLocalName(&name, &length);
            auto tag = utf8(name,length);
            const wchar_t *ns = nullptr; unsigned nsLength = 0;
            reader->GetNamespaceUri(&ns,&nsLength);
            if (nsLength) throw Failure("UTIC XML은 네임스페이스 없는 필드 형식을 사용합니다.");
            if (type == XmlNodeType_Element) {
                if (depth == 0) {
                    if (root || tag != "result") throw Failure("UTIC XML 최상위 result 구조 오류");
                    root = true;
                } else if (depth == 1) {
                    if (!root || tag != "record" || inRecord || reader->IsEmptyElement()) throw Failure("UTIC XML record 구조 오류");
                    current = {}; inRecord = true;
                } else if (depth == 2 && inRecord) {
                    if (!current.fields.emplace(tag, "").second) throw Failure("UTIC XML 필드 중복: " + tag);
                    field = reader->IsEmptyElement() ? "" : tag;
                } else throw Failure("UTIC XML 필드는 단일 텍스트 구조여야 합니다.");
            } else if (depth == 2) field.clear();
            else if (depth == 1) {
                validate(current);
                records.push_back(std::move(current));
                if (records.size() > 1000) throw Failure("시험 XML record 개수 초과");
                inRecord = false;
            }
        } else if (type == XmlNodeType_Text || type == XmlNodeType_CDATA || type == XmlNodeType_Whitespace) {
            const wchar_t *value = nullptr; unsigned count = 0; reader->GetValue(&value,&count);
            auto text = utf8(value,count);
            if (!field.empty()) current.fields[field] += text;
            else if (text.find_first_not_of(" \t\r\n") != std::string::npos) throw Failure("UTIC XML 필드 밖의 텍스트");
        }
    }
    if (FAILED(status) || !root || inRecord || (!allowEmpty && records.empty())) throw Failure("UTIC XML 구문 또는 정상 record 오류");
    return records;
}
std::string defaultFixture() {
    return u8R"XML(<?xml version="1.0" encoding="UTF-8"?>
<result><record>
<incidentId>202609230001</incidentId><incidenteTypeCd>1</incidenteTypeCd><incidenteSubTypeCd>101</incidenteSubTypeCd>
<addressJibun>서울특별시 중구 태평로1가</addressJibun><addressJibunCd>1114010300</addressJibunCd><addressNew>서울특별시 중구 세종대로</addressNew>
<linkId>1234567890</linkId><locationDataX>126.978400000</locationDataX><locationDataY>37.566500000</locationDataY><locationTypeCd>C0101</locationTypeCd><locationData></locationData>
<incidenteTrafficCd>A0503</incidenteTrafficCd><incidenteGradeCd>A0401</incidenteGradeCd><incidentTitle>적합성 시험용 돌발정보</incidentTitle><incidentRegionCd>11</incidentRegionCd>
<startDate>2026년 09월 23일 09시 00분</startDate><endDate>2026년 09월 23일 10시 00분</endDate><lane>2</lane><roadName>세종대로</roadName><sourceCode>UTIC</sourceCode>
<controlType>1</controlType><lineLinkId>1234567890</lineLinkId><important>01</important><updateDate>2026년 09월 23일 09시 01분</updateDate>
</record></result>
)XML";
}
}
