#include "VdsProvider.h"
#include <algorithm>
#include "StandardFields.h"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <windows.h>

namespace rest {
namespace {
std::string input(const Json &j,const char *key) {
    auto p=j.get(key);
    if(!p||p->kind!=Json::String||p->text.empty()||p->text.size()>8192||p->text.find_first_of("\r\n")!=std::string::npos||p->text.find('\0')!=std::string::npos)
        throw Failure(std::string("입력 오류: ")+key);
    return p->text;
}
unsigned number(const Json &j,const char *key,unsigned fallback) {
    auto p=j.get(key); if(!p||(p->kind==Json::String&&p->text.empty()))return fallback;
    if(p->kind!=Json::String&&p->kind!=Json::Number)throw Failure(std::string("정수 입력 오류: ")+key);
    if(p->text.empty()||p->text.size()>4||p->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure(std::string("정수 입력 오류: ")+key);
    auto n=std::stoul(p->text);if(!n||n>3600)throw Failure(std::string("입력 범위 오류: ")+key);return static_cast<unsigned>(n);
}
void save(const std::filesystem::path &path,const std::string &value) {
    std::ofstream f(path,std::ios::binary); f<<value; f.close();if(!f)throw Failure("증적 파일 저장 실패");
}
}
VdsConfig VdsConfig::parse(const std::string &s) {
    auto j=Json::parse(s);VdsConfig c;
    c.baseUrl=input(j,"sut_base_url");c.bearerToken=input(j,"bearer_token");
    if(c.baseUrl.back()=='/')c.baseUrl.pop_back();
    auto start=c.baseUrl.rfind("http://",0)==0?7u:c.baseUrl.rfind("https://",0)==0?8u:0u;
    if(!start||c.baseUrl.size()<=start||c.baseUrl.find_first_of("/?#@ \\\t",start)!=std::string::npos)throw Failure("UT 센터 주소에는 http(s)://호스트:포트만 입력하세요.");
    if(c.bearerToken.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~+/=")!=std::string::npos)throw Failure("Bearer 토큰 형식 오류");
    c.repetitions=number(j,"repetitions",10);c.connectTimeout=number(j,"connect_timeout_s",5);c.requestTimeout=number(j,"request_timeout_s",30);
    if(c.repetitions<10)throw Failure("정보제공시험 반복수는 최소 10회입니다.");
    if(c.connectTimeout>c.requestTimeout)throw Failure("접속 제한시간이 전체 응답 제한시간보다 큽니다.");
    auto selected=j.get("test_normal_vds");if(!selected||selected->kind!=Json::Bool||!selected->boolean)throw Failure("VDS 정보제공시험을 선택하세요.");
    return c;
}
std::string configureVdsUI() {
    return R"JSON({"scenarios":[{"key":"test_normal_vds","title":"UT 센터 VDS 원시정보 이력 제공시험"}],"configuration":[{"type":"Div","option":{"direction":"col"},"components":[{"type":"FieldSet","option":{"label":"UT 센터 API 접속 설정"},"components":[{"type":"Input","option":{"name":"sut_base_url","label":"시험 대상 UT 센터 주소 (http(s)://호스트:포트)","type":"text","value":"http://127.0.0.1:55311"}},{"type":"Input","option":{"name":"bearer_token","label":"API 접근용 Bearer 토큰","type":"password"}},{"type":"Input","option":{"name":"repetitions","label":"단일 정보교환 반복 횟수 (최소 10회)","type":"number","value":"10"}},{"type":"Input","option":{"name":"connect_timeout_s","label":"접속 제한시간 (초, 시험환경 설정)","type":"number","value":"5"}},{"type":"Input","option":{"name":"request_timeout_s","label":"응답 제한시간 (초, 시험환경 설정)","type":"number","value":"30"}}]},{"type":"FieldSet","option":{"label":"시험 항목"},"components":[{"type":"Input","option":{"name":"test_normal_vds","label":"UT 센터 VDS 원시정보 이력 제공시험","type":"checkbox"}}]}]}]})JSON";
}
size_t validateVdsResponse(const VdsResponse &r) {
    if(r.status!=200)throw Failure("정상 GET의 HTTP 상태 코드 불일치: 기대 200 / 수신 "+std::to_string(r.status));
    auto type=r.contentType;std::transform(type.begin(),type.end(),type.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
    type=type.substr(0,type.find(';'));while(!type.empty()&&type.back()==' ')type.pop_back();
    if(type!="application/json")throw Failure("응답 Content-Type 불일치: application/json 필요");
    if(r.body.empty()||r.body.size()>1024*1024||!MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,r.body.data(),static_cast<int>(r.body.size()),nullptr,0))throw Failure("응답 본문 크기 또는 UTF-8 인코딩 오류");
    auto j=Json::parse(r.body,1024*1024);if(j.kind!=Json::Array)throw Failure("VDS 응답 최상위는 JSON 배열이어야 합니다.");
    struct Field { const char *name;Json::Kind type;bool required;int width;int scale; };
    const Field fields[]={
        {"collectDate",Json::String,true,14,0},{"stnId",Json::String,true,12,0},{"laneNo",Json::Number,true,1,0},
        {"vol",Json::Number,true,7,0},{"spd",Json::Number,true,5,2},{"occ",Json::Number,true,5,2},
        {"volS",Json::Number,false,7,0},{"volM",Json::Number,false,7,0},{"volL",Json::Number,false,7,0},
        {"errCode",Json::Number,true,1,0},{"linkId",Json::String,true,12,0},{"vdsId",Json::String,true,12,0},{"stnLocation",Json::String,true,50,0}};
    for(size_t n=0;n<j.array.size();++n){
        auto &row=j.array[n];if(row.kind!=Json::Object)throw Failure("VDS 배열 항목은 객체여야 합니다.");
        for(const auto &f:fields){auto p=row.get(f.name);auto where="VDS["+std::to_string(n)+"]."+f.name;
            if(!p){if(f.required)throw Failure(where+": 필수 필드 누락");continue;}
            if(p->kind!=f.type)throw Failure(where+": 자료형 불일치");
            if(p->kind==Json::Number)standard::decimal(p->text,f.width,f.scale,where);
            else if(std::string(f.name)=="collectDate")standard::timestamp(p->text,where);
            else standard::text(p->text,f.width,where);
        }
    }
    return j.array.size();
}
Result runVds(const VdsConfig &c,std::atomic<bool> &stop,const Sink &sink) {
    Result result;result.runId=std::to_string(std::chrono::system_clock::now().time_since_epoch().count())+"-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+"-"+VdsCase;
    auto directory=std::filesystem::current_path()/"rest-results"/result.runId;std::filesystem::create_directories(directory);
    std::ofstream events(directory/"events.jsonl",std::ios::binary);
    auto record=[&](const std::string &event,const std::string &detail){events<<"{\"runId\":"<<quote(result.runId)<<",\"event\":"<<quote(event)<<detail<<"}\n";events.flush();if(!events)throw Failure("HTTP 증적 기록 실패");};
    unsigned nonempty=0;
    try{
        if(sink.state)sink.state("test_normal_vds","START");
        record("prepared",",\"method\":\"GET\",\"path\":"+quote(VdsPath)+",\"query\":[],\"bodyBytes\":0,\"authorizationRedacted\":true");
        for(unsigned n=1;n<=c.repetitions;++n){
            if(stop)throw Stopped();
            auto request="GET "+std::string(VdsPath)+" HTTP/1.1\r\nAccept: application/json\r\nAuthorization: Bearer [REDACTED]\r\nX-Test-Run-Id: "+result.runId+"\r\nX-Test-Exchange: "+std::to_string(n)+"\r\n\r\n";
            save(directory/("request-"+std::to_string(n)+".txt"),request);
            record("request",",\"exchange\":"+std::to_string(n));
            auto r=getVds(c,stop,result.runId,n);
            save(directory/("response-"+std::to_string(n)+".json"),r.body);
            record("response",",\"exchange\":"+std::to_string(n)+",\"status\":"+std::to_string(r.status)+",\"contentType\":"+quote(r.contentType)+",\"bodySha256\":"+quote(sha256(r.body))+",\"bodyBytes\":"+std::to_string(r.body.size()));
            auto rows=validateVdsResponse(r);if(rows)++nonempty;++result.exchanges;
            record("validated",",\"exchange\":"+std::to_string(n)+",\"recordCount\":"+std::to_string(rows));
            if(sink.info)sink.info("VDS 정상 GET·JSON 응답 검사 "+std::to_string(n)+"/"+std::to_string(c.repetitions)+"회, "+std::to_string(rows)+"건");
        }
        result.verdict=nonempty==c.repetitions?"SUCCESS":"EVIDENCE_PENDING";
        result.detail=nonempty==c.repetitions?"정상 GET 10회 이상, HTTP 200·JSON 배열·VDS 필수 필드와 DTO 자료형 검사 완료":"빈 배열 응답 포함: 구조는 유효하나 정상 VDS 자료 제공 확인 필요";
    }catch(const Stopped &e){result.verdict="STOPPED";result.detail=e.what();}
    catch(const std::exception &e){result.verdict="FAIL";result.detail=e.what();}
    record("result",",\"verdict\":"+quote(result.verdict)+",\"detail\":"+quote(result.detail));
    result.reportPath=(directory/"result.json").u8string();
    save(directory/"result.json","{\"schemaVersion\":1,\"runId\":"+quote(result.runId)+",\"case\":"+quote(VdsCase)+",\"designId\":\"SC11\",\"test\":\"normal_vds\",\"automaticVerdict\":"+quote(result.verdict)+",\"detail\":"+quote(result.detail)+",\"requestedExchanges\":"+std::to_string(c.repetitions)+",\"completedExchanges\":"+std::to_string(result.exchanges)+",\"nonemptyExchanges\":"+std::to_string(nonempty)+",\"validationProfile\":\"OpenAPI DTO types + Part3 required fields\",\"remainingContractChecks\":[\"standard numeric widths/precision and timestamp/string mapping\",\"invalid request and no-data error contract\",\"smart intersection operation\"]}\n");
    return result;
}
}
