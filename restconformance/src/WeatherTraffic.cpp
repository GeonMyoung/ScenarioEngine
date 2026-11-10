#include "WeatherTraffic.h"
#include "StandardFields.h"
#include <map>

namespace rest { namespace {
const Json &member(const Json &j,const char *key,Json::Kind kind){auto p=j.get(key);if(!p||p->kind!=kind)throw Failure(std::string("기상정보 필수 필드/자료형 오류: ")+key);return *p;}
Json parseBody(const HttpResponse &r){
    auto media=r.contentType;std::transform(media.begin(),media.end(),media.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
    media=media.substr(0,media.find(';'));while(!media.empty()&&media.back()==' ')media.pop_back();
    if(media!="application/json")throw Failure("기상정보 Content-Type 불일치: application/json 필요");
    if(r.body.empty()||r.body.size()>1024*1024)throw Failure("기상정보 응답 본문 크기 오류");
    standard::characters(r.body);return Json::parse(r.body,1024*1024);
}
double number(const Json &j,const std::string &name,int p,int s){
    if(j.kind!=Json::Number)throw Failure(name+": 자료형 불일치, 숫자 필요");standard::decimal(j.text,p,s,name);
    auto a=j.text.substr(0,j.text.find_first_of("eE"));return a.find_first_of("123456789")==std::string::npos?0:std::stod(j.text);
}
double bounded(const Json &j,const std::string &name,double low,double high){double n=number(j,name,10,0);if(n<low||n>high)throw Failure(name+": 정수 유효값 범위 오류");return n;}
std::string headerCode(const Json &root){
    auto &h=member(member(root,"response",Json::Object),"header",Json::Object);
    auto &code=member(h,"resultCode",Json::String);auto &msg=member(h,"resultMsg",Json::String);
    if(code.text.size()!=2||code.text.find_first_not_of("0123456789")!=std::string::npos)throw Failure("기상정보 resultCode는 2자리 문자열이어야 합니다.");
    standard::text(msg.text,100,"기상정보 resultMsg");return code.text;
}
std::string queryValue(const WeatherOptions &o,const std::string &name){for(auto &q:o.query)if(q.first==name)return q.second;throw Failure("기상정보 조회변수 누락: "+name);}
std::string intText(const std::string &s,const std::string &name,long long low,long long high){
    size_t start=(!s.empty()&&(s[0]=='-'||s[0]=='+'))?1:0;
    if(s.empty()||s.size()>11||start==s.size()||s.find_first_not_of("0123456789",start)!=std::string::npos)throw Failure(name+": 정수 조회변수 형식 오류");
    auto n=std::stoll(s);if(n<low||n>high)throw Failure(name+": 조회변수 범위 오류");return std::to_string(n);
}
std::map<std::string,std::string> values(const HttpFields &qs,const std::string &keyName){
    std::map<std::string,std::string> m;
    for(auto &q:qs){if(m.count(q.first))throw Failure("기상정보 중복 조회변수");m[q.first]=q.second;}
    for(auto key:{"pageNo","numOfRows","base_date","base_time","nx","ny"})if(!m.count(key))throw Failure(std::string("기상정보 필수 조회변수 누락: ")+key);
    for(auto &q:m)if(q.first!=keyName&&q.first!="pageNo"&&q.first!="numOfRows"&&q.first!="dataType"&&q.first!="base_date"&&q.first!="base_time"&&q.first!="nx"&&q.first!="ny")throw Failure("기상정보 미정의 조회변수");
    if(!m.count("dataType")||m["dataType"]!="JSON")throw Failure("기상정보 dataType=JSON이 필요합니다. 생략 시 XML입니다.");
    m["pageNo"]=intText(m["pageNo"],"pageNo",1,9999);m["numOfRows"]=intText(m["numOfRows"],"numOfRows",1,9999);
    m["nx"]=intText(m["nx"],"nx",-2147483648LL,2147483647LL);m["ny"]=intText(m["ny"],"ny",-2147483648LL,2147483647LL);
    if(m["base_date"].size()!=8||m["base_time"].size()!=4)throw Failure("기상정보 base_date/base_time 길이 오류");
    standard::timestamp(m["base_date"]+m["base_time"]+"00","기상정보 조회일시");return m;
}
}
WeatherOptions weatherOptions(const Json &j){
    WeatherOptions o;
    for(auto key:{"api_path","service_key_name"})if(auto v=j.get(key)){if(v->kind!=Json::String)throw Failure("기상 API 설정 자료형 오류");if(!v->text.empty())(std::string(key)=="api_path"?o.path:o.keyName)=v->text;}
    if(o.path!=WeatherPath&&o.path!="/1360000/VilageFcstInfoService_2.0/getUltraSrtFcst")throw Failure("기상 API 경로는 getUltraSrtNcst 또는 getUltraSrtFcst를 사용하세요.");
    if(o.keyName!="serviceKey"&&o.keyName!="ServiceKey")throw Failure("기상 인증변수명은 serviceKey 또는 ServiceKey를 사용하세요.");
    for(auto entry:{std::make_pair("pageNo","1"),std::make_pair("numOfRows","10"),std::make_pair("base_date","20260924"),std::make_pair("base_time","0600"),std::make_pair("nx","55"),std::make_pair("ny","127")}){
        std::string v=entry.second;if(auto p=j.get(entry.first)){if(p->kind!=Json::String&&p->kind!=Json::Number)throw Failure(std::string(entry.first)+": 조회변수 설정 자료형 오류");if(!p->text.empty())v=p->text;}o.query.push_back({entry.first,v});
    }
    o.query.push_back({"dataType","JSON"});auto canonical=values(o.query,o.keyName);for(auto &q:o.query)q.second=canonical[q.first];return o;
}
HttpFields weatherQuery(const WeatherOptions &o,const std::string &credential,const std::string &test){
    auto q=o.query;if(test!="test_missing_credential")q.push_back({o.keyName,test=="test_wrong_credential"?"INVALID-"+credential:credential});
    if(test=="test_invalid_request")for(auto &p:q)if(p.first=="nx")p.second="invalid";return q;
}
std::string weatherPublicQuery(const HttpFields &qs){std::string s="{";for(auto &q:qs){if(q.first=="serviceKey"||q.first=="ServiceKey")continue;if(s.size()>1)s+=",";s+=quote(q.first)+":"+quote(q.second);}return s+"}";}
std::string weatherFixture(const WeatherOptions &o,bool empty){
    auto date=queryValue(o,"base_date"),time=queryValue(o,"base_time")+"00",page=queryValue(o,"pageNo"),size=queryValue(o,"numOfRows");
    auto total=empty?0:(std::stoul(page)-1)*std::stoul(size)+1;
    auto row="{\"baseDate\":"+quote(date)+",\"updateDt\":"+quote(time)+",\"nx\":"+intText(queryValue(o,"nx"),"nx",-2147483648LL,2147483647LL)+",\"ny\":"+intText(queryValue(o,"ny"),"ny",-2147483648LL,2147483647LL)+",\"t1h\":23.5,\"rn1\":\"0\",\"sky\":1,\"uuu\":-1.2,\"vvv\":2.3,\"reh\":65.0,\"pty\":0,\"lgt\":\"0\",\"vec\":\"180\",\"wsd\":2.5,\"adstrdCode\":"+quote(date)+",\"fcstTime\":"+quote(time)+"}";
    return "{\"response\":{\"header\":{\"resultCode\":\"00\",\"resultMsg\":\"NORMAL_SERVICE\"},\"body\":{\"dataType\":\"JSON\",\"items\":{\"item\":["+(empty?std::string():row)+"]},\"pageNo\":"+page+",\"numOfRows\":"+size+",\"totalCount\":"+std::to_string(total)+"}}}";
}
std::string weatherResultCode(const std::string &test){
    if(test=="test_no_data_error"||test=="test_no_data_error_response")return "03";
    if(test=="test_invalid_request"||test=="test_response_parameter_error")return "10";
    if(test=="test_missing_credential")return "20";if(test=="test_wrong_credential")return "30";
    if(test=="test_missing_path"||test=="test_response_service_error")return "12";
    if(test=="test_response_server_error")return "01";return {};
}
std::string weatherErrorBody(const std::string &code){return "{\"response\":{\"header\":{\"resultCode\":"+quote(code)+",\"resultMsg\":\""+(code=="03"?"NODATA_ERROR":"WEATHER_SERVICE_ERROR")+"\"}}}";}
size_t validateWeatherResponse(const HttpResponse &r){
    if(r.status!=200)throw Failure("기상정보 정상 응답 HTTP 코드 불일치");auto root=parseBody(r);if(headerCode(root)!="00")throw Failure("기상정보 정상 업무 결과코드 불일치: 00 필요");
    auto &b=member(member(root,"response",Json::Object),"body",Json::Object);if(member(b,"dataType",Json::String).text!="JSON")throw Failure("기상정보 응답 dataType 불일치");
    double page=bounded(member(b,"pageNo",Json::Number),"pageNo",1,9999),size=bounded(member(b,"numOfRows",Json::Number),"numOfRows",1,9999),total=bounded(member(b,"totalCount",Json::Number),"totalCount",0,9999999999.0);
    auto &items=member(member(b,"items",Json::Object),"item",Json::Array);
    if(items.array.size()!=std::min(size,std::max(0.0,total-(page-1)*size)))throw Failure("기상정보 응답 페이지 메타데이터와 실제 자료 건수가 다릅니다.");
    for(auto &row:items.array){
        if(row.kind!=Json::Object)throw Failure("기상정보 레코드는 객체여야 합니다.");
        for(auto k:{"baseDate","updateDt","nx","ny","t1h","rn1","sky","uuu","vvv","reh","pty","lgt","vec","wsd","adstrdCode","fcstTime"})if(!row.get(k))throw Failure(std::string("기상정보 필수 필드 누락: ")+k);
        for(auto k:{"baseDate","adstrdCode"}){auto &v=member(row,k,Json::String);if(v.text.size()!=8)throw Failure(std::string(k)+": YYYYMMDD 형식 오류");standard::timestamp(v.text+"000000",k);}
        for(auto k:{"updateDt","fcstTime"}){auto &v=member(row,k,Json::String);if(v.text.size()!=6)throw Failure(std::string(k)+": hhmmss 형식 오류");standard::timestamp("20000101"+v.text,k);}
        bounded(*row.get("nx"),"nx",-199999999,1800000001);bounded(*row.get("ny"),"ny",-900000000,900000001);
        for(auto k:{"t1h","uuu","vvv","reh","wsd"})number(*row.get(k),k,4,1);
        for(auto k:{"rn1","lgt","vec"})standard::text(member(row,k,Json::String).text,std::string(k)=="rn1"?10:3,k);
        auto sky=bounded(*row.get("sky"),"sky",0,9);if(sky!=1&&sky!=3&&sky!=4)throw Failure("sky: 코드 1/3/4 이외의 값");bounded(*row.get("pty"),"pty",0,7);
    }
    return items.array.size();
}
void validateWeatherPage(const HttpResponse &r,const WeatherOptions &o){auto root=parseBody(r);auto &b=member(member(root,"response",Json::Object),"body",Json::Object);if(number(member(b,"pageNo",Json::Number),"pageNo",4,0)!=std::stoul(queryValue(o,"pageNo"))||number(member(b,"numOfRows",Json::Number),"numOfRows",4,0)!=std::stoul(queryValue(o,"numOfRows")))throw Failure("기상정보 응답 페이지 조건이 요청과 다릅니다.");}
void validateWeatherError(const HttpResponse &r,const std::string &expected){
    auto root=parseBody(r);auto actual=headerCode(root);if(actual!=expected)throw Failure("기상정보 업무 결과코드 불일치: 기대 "+expected+" / 수신 "+actual);
    auto &response=member(root,"response",Json::Object);if(auto b=response.get("body")){if(b->kind!=Json::Object)throw Failure("기상 오류 body 자료형 오류");if(auto items=b->get("items")){auto &rows=member(*items,"item",Json::Array);if(!rows.array.empty())throw Failure("기상 오류응답에 정상 자료가 있습니다.");}}
}
std::string validateWeatherRequest(const HttpRequest &r,const WeatherOptions &o,const std::string &credential){
    if(r.method!="GET"||r.path!=o.path)return "기상정보 GET 또는 URL 경로 불일치";if(r.bodyBytes||r.bodyDeclared)return "기상정보 GET 요청에 본문이 있습니다.";
    try{auto actual=values(r.query,o.keyName);if(!actual.count(o.keyName)||actual[o.keyName]!=credential)return "기상정보 인증키 누락 또는 불일치";actual.erase(o.keyName);if(actual!=values(o.query,o.keyName))return "기상정보 조회조건이 준비한 시험 설정과 다릅니다.";}
    catch(const std::exception &e){return e.what();}return {};
}
}
