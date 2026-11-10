#include "VdsRequester.h"
#include "HttpAdapter.h"
#include <filesystem>
#include <fstream>
#include <algorithm>

namespace rest {
namespace {
std::string field(const Json &j,const char *key,bool required=false){
    auto p=j.get(key);if(!p){if(required)throw Failure(std::string("필수 입력: ")+key);return {};}
    if(p->kind!=Json::String||p->text.find_first_of("\r\n")!=std::string::npos||p->text.find('\0')!=std::string::npos||p->text.size()>8192||(required&&p->text.empty()))throw Failure(std::string("문자열 입력 오류: ")+key);
    return p->text;
}
unsigned number(const Json &j,const char *key,unsigned fallback,unsigned max){
    auto p=j.get(key);if(!p||(p->kind==Json::String&&p->text.empty()))return fallback;
    if((p->kind!=Json::String&&p->kind!=Json::Number)||p->text.empty()||p->text.size()>5||p->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure(std::string("정수 입력 오류: ")+key);
    auto n=std::stoul(p->text);if(!n||n>max)throw Failure(std::string("입력 범위 오류: ")+key);return static_cast<unsigned>(n);
}
void save(const std::filesystem::path &p,const std::string &s){std::ofstream f(p,std::ios::binary);f<<s;f.close();if(!f)throw Failure("VDS 증적 저장 실패");}
}
std::string defaultVdsFixture(){
    return R"JSON([{"collectDate":"20260924120000","stnId":"STN000000001","laneNo":1,"vol":24,"spd":52.35,"occ":12.5,"volS":20,"volM":3,"volL":1,"errCode":0,"linkId":"LNK000000001","vdsId":"VDS000000001","stnLocation":"시험 지점"}])JSON";
}
VdsRequestConfig VdsRequestConfig::parse(const std::string &raw){
    auto j=Json::parse(raw);if(j.kind!=Json::Object)throw Failure("설정은 JSON 객체여야 합니다.");
    VdsRequestConfig c;auto ip=field(j,"bind_ip");if(!ip.empty())c.server.bindIp=ip;
    c.server.port=number(j,"local_port",55332,65535);c.server.repetitions=number(j,"repetitions",10,1000);
    c.server.requestTimeout=number(j,"request_timeout_s",30,3600);c.server.fixturePath=field(j,"response_json_file");
    c.bearerToken=field(j,"bearer_token",true);
    if(c.bearerToken.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~+/=")!=std::string::npos)throw Failure("Bearer 토큰 형식 오류");
    if(c.server.repetitions<10)throw Failure("정보요청시험 반복수는 최소 10회입니다.");
    auto selected=j.get("test_request_vds");if(!selected||selected->kind!=Json::Bool||!selected->boolean)throw Failure("미시교통정보 플랫폼 VDS 정보요청시험을 선택하세요.");
    return c;
}
std::string configureVdsRequestUI(){
    return R"JSON({"scenarios":[{"key":"test_request_vds","title":"미시교통정보 플랫폼 VDS 원시정보 이력 요청시험"}],"configuration":[{"type":"Div","option":{"direction":"col"},"components":[{"type":"FieldSet","option":{"label":"시험시스템 UT 센터 API 설정"},"components":[{"type":"Input","option":{"name":"bind_ip","label":"시험시스템 수신 대기 IP 주소","type":"text","value":"127.0.0.1"}},{"type":"Input","option":{"name":"local_port","label":"시험시스템 HTTP 수신 대기 포트","type":"number","value":"55332"}},{"type":"Input","option":{"name":"bearer_token","label":"시험 대상 요청에 사용할 Bearer 토큰","type":"password"}},{"type":"Input","option":{"name":"response_json_file","label":"응답 JSON 파일 경로 (미입력 시 기본 시험 자료)","type":"text"}},{"type":"Input","option":{"name":"repetitions","label":"단일 정보교환 반복 횟수 (최소 10회)","type":"number","value":"10"}},{"type":"Input","option":{"name":"request_timeout_s","label":"회당 요청·전송 대기시간 (초, 시험환경 설정)","type":"number","value":"30"}}]},{"type":"FieldSet","option":{"label":"시험 항목"},"components":[{"type":"Input","option":{"name":"test_request_vds","label":"미시교통정보 플랫폼 VDS 원시정보 이력 요청시험","type":"checkbox"}}]}]}]})JSON";
}
std::string validateVdsRequest(const VdsRequestConfig &c,const HttpRequest &r){
    if(r.method!="GET")return "HTTP method 불일치: GET 요청이 필요합니다.";
    if(r.path!=VdsPath)return "VDS 요청 URL 경로 불일치";
    if(!r.query.empty())return "VDS 단일 GET에 정의되지 않은 query가 있습니다.";
    if(r.bodyBytes||r.bodyDeclared)return "VDS 단일 GET에 예상하지 않은 본문이 있습니다.";
    if(r.authorization.size()!=1)return "Authorization 헤더는 한 번만 포함되어야 합니다.";
    auto auth=r.authorization.front();auto space=auth.find(' ');auto scheme=auth.substr(0,space);
    std::transform(scheme.begin(),scheme.end(),scheme.begin(),[](unsigned char v){return static_cast<char>(std::tolower(v));});
    if(space==std::string::npos||scheme!="bearer"||auth.substr(space+1)!=c.bearerToken)return "Bearer 인증값 불일치";
    return {};
}
Result runVdsRequest(const VdsRequestConfig &c,std::atomic<bool> &stop,const Sink &sink){
    Result result;result.runId=std::to_string(std::chrono::system_clock::now().time_since_epoch().count())+"-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+"-"+VdsRequestCase;
    auto dir=std::filesystem::current_path()/"rest-results"/result.runId;std::filesystem::create_directories(dir);std::ofstream trace(dir/"events.jsonl",std::ios::binary);
    auto record=[&](const std::string &event,const std::string &extra=""){
        trace<<"{\"runId\":"<<quote(result.runId)<<",\"event\":"<<quote(event)<<",\"monotonicUs\":"<<std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()<<extra<<"}\n";trace.flush();if(!trace)throw Failure("VDS 증적 기록 실패");};
    std::string body,hash;size_t rows=0;
    try{
        body=c.server.fixturePath.empty()?defaultVdsFixture():readTextFile(c.server.fixturePath);
        rows=validateVdsResponse({200,"application/json",body});if(!rows)throw Failure("정상 요청시험에는 VDS 레코드가 포함된 응답 자료가 필요합니다.");
        hash=sha256(body);save(dir/"response.json",body);record("prepared",",\"bodySha256\":"+quote(hash)+",\"recordCount\":"+std::to_string(rows));
        HttpAdapter transport(c.server,true);transport.start();record("listening",",\"port\":"+std::to_string(c.server.port));
        if(sink.state)sink.state("test_request_vds","START");if(sink.info)sink.info("LISTENING");
        for(unsigned n=1;n<=c.server.repetitions;++n){
            auto request=transport.receive(stop,c.server.requestTimeout);auto reason=validateVdsRequest(c,request);
            record("request",",\"exchange\":"+std::to_string(n)+",\"method\":"+quote(request.method)+",\"path\":"+quote(request.path)+",\"queryCount\":"+std::to_string(request.query.size())+",\"bodyBytes\":"+std::to_string(request.bodyBytes)+",\"authorizationRedacted\":true,\"authorizationCount\":"+std::to_string(request.authorization.size())+",\"accepted\":"+(reason.empty()?"true":"false"));
            if(!reason.empty()){
                // Harness diagnostic, not an invented production error-response contract.
                transport.respond(request,400,"Invalid test request\n","text/plain; charset=UTF-8",result.runId,n,stop,c.server.requestTimeout);throw Failure(reason);
            }
            transport.respond(request,200,body,"application/json;charset=UTF-8",result.runId,n,stop,c.server.requestTimeout);++result.exchanges;
            record("response_sent",",\"exchange\":"+std::to_string(n)+",\"status\":200,\"bodySha256\":"+quote(hash)+",\"bodyBytes\":"+std::to_string(body.size()));
            if(sink.info)sink.info("미시교통정보 플랫폼 정상 GET·VDS 응답 전송 "+std::to_string(n)+"/"+std::to_string(c.server.repetitions)+"회 완료");
        }
        result.verdict="EVIDENCE_PENDING";result.detail="정상 요청·VDS 응답 전송 완료. 미시교통정보 플랫폼의 수신·분석·처리 증거 대조 필요";
    }catch(const Stopped &e){result.verdict="STOPPED";result.detail=e.what();}
    catch(const std::exception &e){result.verdict="FAIL";result.detail=e.what();}
    record("result",",\"verdict\":"+quote(result.verdict)+",\"detail\":"+quote(result.detail));result.reportPath=(dir/"result.json").u8string();
    save(dir/"result.json","{\"schemaVersion\":1,\"runId\":"+quote(result.runId)+",\"case\":"+quote(VdsRequestCase)+",\"designId\":\"SC32\",\"test\":\"request_vds\",\"automaticVerdict\":"+quote(result.verdict)+",\"detail\":"+quote(result.detail)+",\"requestedExchanges\":"+std::to_string(c.server.repetitions)+",\"completedExchanges\":"+std::to_string(result.exchanges)+",\"recordCount\":"+std::to_string(rows)+",\"responseSha256\":"+quote(hash)+",\"evidenceReview\":null}\n");
    return result;
}
}
