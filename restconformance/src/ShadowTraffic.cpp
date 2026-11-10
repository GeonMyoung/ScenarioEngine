#include "ShadowTraffic.h"
#include "StandardFields.h"
#include <map>

namespace rest { namespace {
Json body(const HttpResponse &r){
    auto media=r.contentType;std::transform(media.begin(),media.end(),media.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
    media=media.substr(0,media.find(';'));while(!media.empty()&&media.back()==' ')media.pop_back();
    if(media!="application/json")throw Failure("음영구간 정보 Content-Type 불일치: application/json 필요");
    if(r.body.empty()||r.body.size()>1024*1024)throw Failure("음영구간 정보 응답 본문 크기 오류");
    standard::characters(r.body);return Json::parse(r.body,1024*1024);
}
std::string integerText(const std::string &s){
    size_t start=(!s.empty()&&(s[0]=='-'||s[0]=='+'))?1:0;
    if(s.empty()||start==s.size()||s.find_first_not_of("0123456789",start)!=std::string::npos)throw Failure("정수 조회변수 형식 오류");
    auto first=s.find_first_not_of('0',start);if(first==std::string::npos)return "0";
    return (s[0]=='-'?"-":"")+s.substr(first);
}
std::map<std::string,std::string> queryValues(const HttpFields &query){
    std::map<std::string,std::string> values;
    for(const auto &q:query){
        if(values.count(q.first))throw Failure("중복 조회변수: "+q.first);
        if(q.first!="since"&&q.first!="latest"&&q.first!="node_link")throw Failure("정의되지 않은 조회변수: "+q.first);
        if(q.second.size()>4096)throw Failure("조회변수 길이 제한 초과");
        auto value=q.first=="node_link"?q.second:integerText(q.second);
        if(q.first=="latest"&&(value[0]=='-'||value.size()>3||std::stoul(value)>500))throw Failure("latest 조회변수 범위 오류: 0~500 필요");
        standard::characters(value);values[q.first]=value;
    }
    if(!values.count("since"))values["since"]="0";
    if(!values.count("latest"))values["latest"]="0";
    return values;
}
void integerField(const Json &v,unsigned maximum,const std::string &where){
    if(v.kind!=Json::Number)throw Failure(where+": 자료형 불일치, INTEGER 필요");
    standard::decimal(v.text,5,0,where);
    // decimal() proves integrality exactly before any bounded conversion.
    auto significand=v.text.substr(0,v.text.find_first_of("eE"));
    bool zero=significand.find_first_of("123456789")==std::string::npos;
    double number=zero?0:std::stod(v.text);
    if(number<0||number>maximum)throw Failure(where+": 유효값 범위 오류 (0~"+std::to_string(maximum)+")");
}
}
std::string shadowFixture(){return R"JSON([{"time":"20260724132000","node_link":12345,"lane_no":1,"lane_speed":42,"lane_volume":18,"lane_density":9}])JSON";}
std::string shadowErrorBody(){return R"JSON({"detail":[{"loc":["query","latest"],"msg":"Input should be less than or equal to 500","type":"less_than_equal"}]})JSON";}
HttpFields shadowQuery(const Json &j){
    HttpFields query;
    for(auto key:{"since","node_link","latest"})if(auto p=j.get(key)){
        if(p->kind==Json::Null||(p->kind==Json::String&&p->text.empty()))continue;
        if((p->kind!=Json::String&&p->kind!=Json::Number)||(std::string(key)=="node_link"&&p->kind!=Json::String))throw Failure(std::string(key)+": 조회변수 입력 자료형 오류");
        query.push_back({key,p->text});
    }
    queryValues(query);return query;
}
std::string shadowQueryJson(const HttpFields &q){std::string s="{";for(auto &v:q){if(s.size()>1)s+=",";s+=quote(v.first)+":"+quote(v.second);}return s+"}";}
std::string validateShadowRequest(const HttpRequest &r,const HttpFields &expected){
    if(r.method!="GET")return "음영구간 정보 method 불일치: GET 필요";
    if(r.path!=ShadowPath)return "음영구간 정보 URL 경로 불일치: /data 필요";
    if(r.bodyBytes||r.bodyDeclared)return "음영구간 정보 GET 요청에 본문이 있습니다.";
    try{if(queryValues(r.query)!=queryValues(expected))return "음영구간 정보 조회변수와 준비한 시험 조건이 다릅니다.";}
    catch(const std::exception &e){return std::string("음영구간 정보 ")+e.what();}
    return {};
}
size_t validateShadowResponse(const HttpResponse &r){
    if(r.status!=200)throw Failure("음영구간 정보 정상 응답 HTTP 코드 불일치");
    auto root=body(r);if(root.kind!=Json::Array)throw Failure("음영구간 정보 응답은 채택한 표준 예시의 JSON 배열이어야 합니다.");
    for(size_t n=0;n<root.array.size();++n){
        const auto &row=root.array[n];auto where="음영구간 정보["+std::to_string(n)+"].";
        if(row.kind!=Json::Object)throw Failure(where+"레코드는 JSON 객체여야 합니다.");
        for(auto key:{"time","node_link","lane_no","lane_speed","lane_volume","lane_density"})if(!row.get(key))throw Failure(where+key+": 필수 필드 누락");
        const auto &time=*row.get("time");if(time.kind!=Json::String)throw Failure(where+"time: 자료형 불일치");
        standard::timestamp(time.text,where+"time");
        for(auto key:{"node_link","lane_no","lane_speed","lane_volume","lane_density"})integerField(*row.get(key),(std::string(key)=="node_link"||std::string(key)=="lane_volume")?99999:350,where+key);
    }
    return root.array.size();
}
void validateShadowError(const HttpResponse &r){
    if(r.status!=422)throw Failure("음영구간 조회변수 오류 HTTP 코드 불일치: 명세 422 필요");
    auto root=body(r);if(root.kind!=Json::Object)throw Failure("422 오류응답은 JSON 객체여야 합니다.");
    // OpenAPI HTTPValidationError does not mark detail as required.
    if(auto detail=root.get("detail")){
        if(detail->kind!=Json::Array)throw Failure("422 detail 자료형 불일치");
        for(auto &entry:detail->array){
            if(entry.kind!=Json::Object)throw Failure("422 detail 항목은 객체여야 합니다.");
            auto loc=entry.get("loc"),msg=entry.get("msg"),type=entry.get("type");
            if(!loc||loc->kind!=Json::Array||!msg||msg->kind!=Json::String||!type||type->kind!=Json::String)throw Failure("422 오류응답 loc/msg/type 필수 필드 또는 자료형 오류");
            for(auto &part:loc->array)if(part.kind!=Json::String){
                if(part.kind!=Json::Number)throw Failure("422 loc 항목은 문자열 또는 정수여야 합니다.");
                standard::decimal(part.text,1000000,0,"422 loc");
            }
        }
    }
}
}
