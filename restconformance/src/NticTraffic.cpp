#include "NticTraffic.h"
#include "StandardFields.h"
#include <algorithm>

namespace rest { namespace {
Json body(const HttpResponse &r){
    auto media=r.contentType;std::transform(media.begin(),media.end(),media.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
    media=media.substr(0,media.find(';'));while(!media.empty()&&media.back()==' ')media.pop_back();
    if(media!="application/json")throw Failure("NTIC Content-Type 불일치: application/json 필요");
    if(r.body.empty()||r.body.size()>1024*1024)throw Failure("NTIC 응답 본문 크기 오류");
    standard::characters(r.body);
    auto root=Json::parse(r.body,1024*1024);if(root.kind!=Json::Object)throw Failure("NTIC 응답은 items를 포함하는 JSON 객체여야 합니다.");
    return root;
}
std::string resultCode(const Json &j,bool required){
    auto v=j.get("resultCode");
    if(!v){if(required)throw Failure("NTIC resultCode 필수 필드 누락");return {};}
    if(v->kind!=Json::String||v->text.empty()||v->text.size()>4||v->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure("NTIC resultCode 자료형 또는 형식 오류");
    return v->text;
}
void message(const Json &j,bool required){
    auto v=j.get("resultMsg");
    if(!v){if(required)throw Failure("NTIC resultMsg 필수 필드 누락");return;}
    if(v->kind!=Json::String||v->text.empty())throw Failure("NTIC resultMsg 자료형 또는 빈 값 오류");
}
}
std::string nticFixture(bool empty){
    if(empty)return R"JSON({"resultCode":"0","resultMsg":"SUCCESS","totalCount":"0","items":[]})JSON";
    return R"JSON({"resultCode":"0","resultMsg":"SUCCESS","totalCount":"1","items":[{"vdsId":"VDS0000001","linkIds":"1400006000","laneNo":1,"colctedDate":"20260807173900","speed":62.50,"volume":9,"occupancy":1.50}]})JSON";
}
std::string nticResultCode(const std::string &test){
    if(test=="test_invalid_request"||test=="test_response_400")return "4002";
    if(test=="test_missing_credential"||test=="test_wrong_credential")return "4005";
    if(test=="test_missing_path"||test=="test_response_404")return "4004";
    if(test=="test_response_500")return "4009";
    return {};
}
std::string nticErrorBody(const std::string &code){
    if(code.empty())return R"JSON({"resultMsg":"Requested information is unavailable"})JSON";
    return "{\"resultCode\":"+quote(code)+",\"resultMsg\":\"Request could not be completed\",\"totalCount\":\"0\",\"items\":[]}";
}
size_t validateNticResponse(const HttpResponse &r){
    if(r.status!=200)throw Failure("NTIC 정상 응답 HTTP 상태 코드 불일치");
    auto root=body(r);auto code=resultCode(root,false);if(!code.empty()&&code!="0")throw Failure("NTIC 응답결과코드 불일치: 기대 0 / 수신 "+code);
    message(root,false);auto items=root.get("items");
    if(!items||items->kind!=Json::Array)throw Failure("NTIC items 필수 배열 누락 또는 자료형 오류");
    if(auto count=root.get("totalCount")){
        if(count->kind!=Json::String||count->text.empty()||count->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure("NTIC totalCount 자료형 또는 형식 오류");
        auto first=count->text.find_first_not_of('0');auto value=first==std::string::npos?"0":count->text.substr(first);
        if(value!=std::to_string(items->array.size()))throw Failure("NTIC totalCount와 실제 items 건수가 다릅니다.");
    }
    for(size_t n=0;n<items->array.size();++n){
        const auto &row=items->array[n];auto where="NTIC["+std::to_string(n)+"].";
        if(row.kind!=Json::Object)throw Failure(where+"레코드는 JSON 객체여야 합니다.");
        for(auto key:{"vdsId","linkIds","laneNo","colctedDate","speed","volume","occupancy"})if(!row.get(key))throw Failure(where+key+": 필수 필드 누락");
        for(auto key:{"vdsId","linkIds","colctedDate"}){
            const auto &v=*row.get(key);if(v.kind!=Json::String)throw Failure(where+key+": 자료형 불일치");
            if(std::string(key)=="colctedDate")standard::timestamp(v.text,where+key);
            else standard::text(v.text,std::string(key)=="vdsId"?10:20,where+key);
        }
        for(auto key:{"laneNo","speed","volume","occupancy"}){
            const auto &v=*row.get(key);if(v.kind!=Json::Number)throw Failure(where+key+": 자료형 불일치, 표준 NUMBER 필요");
            auto lane=std::string(key)=="laneNo";standard::decimal(v.text,lane?2:5,lane?0:2,where+key);
        }
    }
    return items->array.size();
}
void validateNticError(const HttpResponse &r,const std::string &expected){
    auto root=body(r);auto actual=resultCode(root,true);message(root,true);
    if(actual!=expected)throw Failure("NTIC 응답결과코드 불일치: 기대 "+expected+" / 수신 "+actual);
    if(auto items=root.get("items"))if(items->kind!=Json::Array||!items->array.empty())throw Failure("NTIC 오류응답에 정상 정보가 포함돼 있습니다.");
}
std::string validateNticRequest(const HttpRequest &r,const std::string &credential,const std::string &path){
    if(r.method!="GET")return "NTIC method 불일치: GET 필요";
    if(r.path!=path)return "NTIC URL 경로 불일치";
    if(r.bodyBytes||r.bodyDeclared)return "NTIC GET 요청에 본문이 있습니다.";
    unsigned keys=0,formats=0;
    for(const auto &q:r.query){
        if(q.first=="apiKey"){++keys;if(q.second!=credential)return "NTIC apiKey 인증정보 불일치";}
        else if(q.first=="getType"){++formats;if(q.second!="json")return "NTIC getType query는 json이어야 합니다.";}
        else return "NTIC 미정의 query 항목";
    }
    if(keys!=1)return "NTIC apiKey 인증정보 누락 또는 중복";
    if(formats!=1)return "NTIC getType query 누락 또는 중복";
    return {};
}
}
