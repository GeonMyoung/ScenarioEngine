#include "UticProvider.h"
#include <algorithm>
#include <filesystem>
#include <fstream>

namespace rest {
namespace {
std::string field(const Json &j,const char *key){
    auto p=j.get(key);if(!p||p->kind!=Json::String||p->text.empty()||p->text.size()>4096||p->text.find_first_of("\r\n")!=std::string::npos||p->text.find('\0')!=std::string::npos)throw Failure(std::string("필수 문자열 입력 오류: ")+key);return p->text;
}
unsigned number(const Json &j,const char *key,unsigned fallback){
    auto p=j.get(key);if(!p||(p->kind==Json::String&&p->text.empty()))return fallback;
    if((p->kind!=Json::String&&p->kind!=Json::Number)||p->text.empty()||p->text.size()>4||p->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure(std::string("정수 입력 오류: ")+key);
    auto n=std::stoul(p->text);if(!n||n>3600)throw Failure(std::string("입력 범위 오류: ")+key);return static_cast<unsigned>(n);
}
void save(const std::filesystem::path &p,const std::string &s){std::ofstream f(p,std::ios::binary);f<<s;f.close();if(!f)throw Failure("UTIC 증적 저장 실패");}
}
UticProviderConfig UticProviderConfig::parse(const std::string &s){
    auto j=Json::parse(s);UticProviderConfig c;c.baseUrl=field(j,"sut_base_url");c.apiKey=field(j,"api_key");
    if(c.baseUrl.back()=='/')c.baseUrl.pop_back();
    auto prefix=c.baseUrl.rfind("http://",0)==0?7u:c.baseUrl.rfind("https://",0)==0?8u:0u;
    if(!prefix||c.baseUrl.size()<=prefix||c.baseUrl.find_first_of("/?#@ \\\t",prefix)!=std::string::npos)throw Failure("UTIC 주소에는 http(s)://호스트:포트만 입력하세요.");
    c.repetitions=number(j,"repetitions",10);c.connectTimeout=number(j,"connect_timeout_s",5);c.requestTimeout=number(j,"request_timeout_s",30);
    if(c.repetitions<10)throw Failure("정보제공시험 반복수는 최소 10회입니다.");
    if(c.connectTimeout>c.requestTimeout)throw Failure("접속 제한시간이 전체 응답 제한시간보다 큽니다.");
    auto selected=j.get("test_provide_utic");if(!selected||selected->kind!=Json::Bool||!selected->boolean)throw Failure("UTIC 돌발정보 제공시험을 선택하세요.");
    return c;
}
std::string configureUticProviderUI(){
    return R"JSON({"scenarios":[{"key":"test_provide_utic","title":"UTIC 돌발정보 제공시험"}],"configuration":[{"type":"Div","option":{"direction":"col"},"components":[{"type":"FieldSet","option":{"label":"시험 대상 UTIC API 접속 설정"},"components":[{"type":"Input","option":{"name":"sut_base_url","label":"시험 대상 UTIC 주소 (http(s)://호스트:포트)","type":"text","value":"http://127.0.0.1:55328"}},{"type":"Input","option":{"name":"api_key","label":"UTIC API 요청 key","type":"password"}},{"type":"Input","option":{"name":"repetitions","label":"단일 정보교환 반복 횟수 (최소 10회)","type":"number","value":"10"}},{"type":"Input","option":{"name":"connect_timeout_s","label":"접속 제한시간 (초, 시험환경 설정)","type":"number","value":"5"}},{"type":"Input","option":{"name":"request_timeout_s","label":"응답 제한시간 (초, 시험환경 설정)","type":"number","value":"30"}}]},{"type":"FieldSet","option":{"label":"시험 항목"},"components":[{"type":"Input","option":{"name":"test_provide_utic","label":"UTIC 돌발정보 제공시험","type":"checkbox"}}]}]}]})JSON";
}
size_t validateUticResponse(const HttpResponse &r){
    if(r.status!=200)throw Failure("정상 GET의 HTTP 상태 코드 불일치: 기대 200 / 수신 "+std::to_string(r.status));
    auto type=r.contentType;std::transform(type.begin(),type.end(),type.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
    type=type.substr(0,type.find(';'));while(!type.empty()&&type.back()==' ')type.pop_back();
    if(type!="application/xml"&&type!="text/xml")throw Failure("응답 Content-Type 불일치: XML 필요");
    return parseUticXml(r.body,true).size();
}
Result runUticProvider(const UticProviderConfig &c,std::atomic<bool> &stop,const Sink &sink){
    Result result;result.runId=std::to_string(std::chrono::system_clock::now().time_since_epoch().count())+"-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+"-"+UticProviderCase;
    auto dir=std::filesystem::current_path()/"rest-results"/result.runId;std::filesystem::create_directories(dir);std::ofstream trace(dir/"events.jsonl",std::ios::binary);
    auto record=[&](const std::string &event,const std::string &extra=""){trace<<"{\"runId\":"<<quote(result.runId)<<",\"event\":"<<quote(event)<<",\"monotonicUs\":"<<std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()<<extra<<"}\n";trace.flush();if(!trace)throw Failure("UTIC 증적 기록 실패");};
    unsigned nonempty=0;
    try{
        if(sink.state)sink.state("test_provide_utic","START");
        record("prepared",",\"method\":\"GET\",\"path\":"+quote(UticPath)+",\"queryNames\":[\"key\"],\"queryKeyRedacted\":true,\"bodyBytes\":0");
        for(unsigned n=1;n<=c.repetitions;++n){
            if(stop)throw Stopped();
            save(dir/("request-"+std::to_string(n)+".txt"),"GET "+std::string(UticPath)+"?key=[REDACTED]\r\nAccept: application/xml\r\nX-Test-Run-Id: "+result.runId+"\r\nX-Test-Exchange: "+std::to_string(n)+"\r\n");
            record("request",",\"exchange\":"+std::to_string(n));
            auto r=httpGet(c.baseUrl+UticPath,c.connectTimeout,c.requestTimeout,stop,{{"X-Test-Run-Id",result.runId},{"X-Test-Exchange",std::to_string(n)}},{{"key",c.apiKey}},true);
            save(dir/("response-"+std::to_string(n)+".xml"),r.body);
            record("response",",\"exchange\":"+std::to_string(n)+",\"status\":"+std::to_string(r.status)+",\"contentType\":"+quote(r.contentType)+",\"bodySha256\":"+quote(sha256(r.body))+",\"bodyBytes\":"+std::to_string(r.body.size()));
            auto rows=validateUticResponse(r);if(rows)++nonempty;++result.exchanges;
            record("validated",",\"exchange\":"+std::to_string(n)+",\"recordCount\":"+std::to_string(rows));
            if(sink.info)sink.info("UTIC 정상 GET·돌발정보 XML 응답 검사 "+std::to_string(n)+"/"+std::to_string(c.repetitions)+"회, "+std::to_string(rows)+"건");
        }
        result.verdict=nonempty==c.repetitions?"SUCCESS":"EVIDENCE_PENDING";
        result.detail=nonempty==c.repetitions?"정상 GET 10회 이상, HTTP 200·UTIC XML 구조·필수 필드 검사 완료":"돌발정보 없는 XML 응답 포함: 정상 자료 제공 확인 필요";
    }catch(const Stopped &e){result.verdict="STOPPED";result.detail=e.what();}
    catch(const std::exception &e){result.verdict="FAIL";result.detail=e.what();}
    record("result",",\"verdict\":"+quote(result.verdict)+",\"detail\":"+quote(result.detail));result.reportPath=(dir/"result.json").u8string();
    save(dir/"result.json","{\"schemaVersion\":1,\"runId\":"+quote(result.runId)+",\"case\":"+quote(UticProviderCase)+",\"designId\":\"SC28\",\"test\":\"provide_utic\",\"automaticVerdict\":"+quote(result.verdict)+",\"detail\":"+quote(result.detail)+",\"requestedExchanges\":"+std::to_string(c.repetitions)+",\"completedExchanges\":"+std::to_string(result.exchanges)+",\"nonemptyExchanges\":"+std::to_string(nonempty)+",\"remainingContractChecks\":[\"production key/IP authentication\",\"invalid request and no-data error contract\",\"unresolved standard/API field mapping\"]}\n");
    return result;
}
}
