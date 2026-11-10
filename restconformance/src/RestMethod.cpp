#include "RestMethod.h"
#include "RestUserLog.h"
#include "RestEvidence.h"
#include "HttpAdapter.h"
#include <filesystem>
#include <fstream>
#include <memory>
#include <regex>
#include <windows.h>

namespace rest {
namespace {
std::string dump(const Json &j){
    if(j.kind==Json::String)return quote(j.text);if(j.kind==Json::Number)return j.text;
    if(j.kind==Json::Bool)return j.boolean?"true":"false";if(j.kind==Json::Null)return "null";
    std::string s=j.kind==Json::Array?"[":"{";bool first=true;
    if(j.kind==Json::Array){for(auto &v:j.array){if(!first)s+=",";first=false;s+=dump(v);}}
    else for(auto &v:j.object){if(!first)s+=",";first=false;s+=quote(v.first)+":"+dump(v.second);}
    return s+(j.kind==Json::Array?"]":"}");
}
bool xmlCase(const std::string &s){return s==UticProviderCase||s=="uticServer2center_v1";}
bool providerCase(const std::string &s){return s==UticProviderCase||s==VdsCase||s==SmartProviderCase||s==NticProviderCase||s==ShadowProviderCase||s==WeatherProviderCase;}
std::string normalKey(const std::string &s){return s==WeatherProviderCase?"test_normal_weather":s==WeatherRequestCase?"test_request_weather":s==ShadowProviderCase?"test_normal_shadow":s==ShadowRequestCase?"test_request_shadow":s==NticProviderCase?"test_normal_ntic":s==NticRequestCase?"test_request_ntic":s==SmartProviderCase?"test_normal_smart":s==SmartRequestCase?"test_request_smart":s==UticProviderCase?"test_provide_utic":s==VdsCase?"test_normal_vds":s==VdsRequestCase?"test_request_vds":"test_normal_utic";}
std::string baseUI(const std::string &s){return s==WeatherProviderCase?configureUticProviderUI():s==WeatherRequestCase?configureUI():s==ShadowProviderCase?configureUticProviderUI():s==ShadowRequestCase?configureUI():s==NticProviderCase?configureUticProviderUI():s==NticRequestCase?configureUI():s==SmartProviderCase?configureVdsUI():s==SmartRequestCase?configureVdsRequestUI():s==UticProviderCase?configureUticProviderUI():s==VdsCase?configureVdsUI():s==VdsRequestCase?configureVdsRequestUI():configureUI();}
unsigned statusInput(const Json &j,const char *key,unsigned fallback,std::initializer_list<unsigned> allowed){
    auto p=j.get(key);if(!p||(p->kind==Json::String&&p->text.empty()))return fallback;
    if((p->kind!=Json::String&&p->kind!=Json::Number)||p->text.size()!=3||p->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure(std::string("응답 코드 입력 오류: ")+key);
    auto value=static_cast<unsigned>(std::stoul(p->text));for(auto a:allowed)if(value==a)return value;throw Failure(std::string("지원하지 않는 기대 응답 코드: ")+key);
}
bool selected(const Json &j,const std::string &key){auto p=j.get(key);if(!p)return false;if(p->kind!=Json::Bool)throw Failure("시험 선택값은 boolean이어야 합니다.");return p->boolean;}
void save(const std::filesystem::path &p,const std::string &s){std::ofstream f(p,std::ios::binary);f<<s;f.close();if(!f)throw Failure("REST 시험 증적 저장 실패");}
size_t records(const HttpResponse &r,bool xml,bool smart,bool ntic,bool shadow,bool weather,bool empty){
    if(weather){auto n=validateWeatherResponse(r);if(!empty&&!n)throw Failure("정상 응답에 기상정보가 없습니다.");return n;}
    if(shadow){auto n=validateShadowResponse(r);if(!empty&&!n)throw Failure("정상 응답에 음영구간 미시교통정보가 없습니다.");return n;}
    if(ntic){auto n=validateNticResponse(r);if(!empty&&!n)throw Failure("정상 응답에 NTIC 차량검지정보가 없습니다.");return n;}
    if(smart){auto n=validateSmartResponse(r);if(!empty&&!n)throw Failure("정상 응답에 스마트교차로 정보가 없습니다.");return n;}
    if(xml){auto n=validateUticResponse(r);if(!empty&&!n)throw Failure("정상 응답에 돌발정보가 없습니다.");return n;}
    auto n=validateVdsResponse(r);if(!empty&&!n)throw Failure("정상 응답에 VDS 정보가 없습니다.");return n;
}
void vdsError(const HttpResponse &r){
    if(r.body.empty()||r.body.size()>1024*1024||!MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,r.body.data(),static_cast<int>(r.body.size()),nullptr,0))throw Failure("VDS 오류 응답 UTF-8 또는 본문 크기 오류");
    auto media=r.contentType;std::transform(media.begin(),media.end(),media.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
    media=media.substr(0,media.find(';'));while(!media.empty()&&media.back()==' ')media.pop_back();
    if(media!="application/json")throw Failure("VDS 오류 응답 Content-Type은 application/json이어야 합니다.");
    auto body=Json::parse(r.body,1024*1024);if(body.kind!=Json::Object)throw Failure("VDS 오류 응답은 JSON 객체여야 합니다.");
    for(auto key:{"code","message","time","path"}){auto p=body.get(key);if(p&&p->kind!=Json::String)throw Failure(std::string("VDS 오류 응답 자료형 불일치: ")+key);}
    auto request=body.get("request");if(request&&request->kind!=Json::Object)throw Failure("VDS 오류 응답 request 자료형 불일치");
    auto t=body.get("time");
    if(t){
        std::smatch m;static const std::regex date(R"(^([0-9]{4})-([0-9]{2})-([0-9]{2})[Tt]([0-9]{2}):([0-9]{2}):([0-9]{2})(\.[0-9]+)?([Zz]|[+-]([0-9]{2}):([0-9]{2}))$)");
        if(!std::regex_match(t->text,m,date))throw Failure("VDS 오류 응답 time date-time 형식 불일치");
        int y=std::stoi(m[1]),month=std::stoi(m[2]),day=std::stoi(m[3]);const int days[]={31,28,31,30,31,30,31,31,30,31,30,31};
        if(month<1||month>12||day<1||day>days[month-1]+(month==2&&(y%400==0||(y%4==0&&y%100!=0)))||std::stoi(m[4])>23||std::stoi(m[5])>59||std::stoi(m[6])>60||(m[9].matched&&(std::stoi(m[9])>23||std::stoi(m[10])>59)))throw Failure("VDS 오류 응답 time 범위 오류");
    }
}
std::string requestReason(const MethodConfig &c,const HttpRequest &r){
    if(r.bodyDeclared)return "GET 요청에 본문 전송 선언이 있습니다.";
    if(c.weather)return validateWeatherRequest(r,c.weatherOptions,c.credential);
    if(c.shadow)return validateShadowRequest(r,c.shadowParams);
    if(c.ntic)return validateNticRequest(r,c.credential,c.nticPath);
    if(c.xml){Config t=c.server;t.apiKey=c.credential;auto error=validateRequest(t,r);if(!error.empty())return error;if(r.query.size()!=1)return "정의되지 않은 query 항목";return {};}
    VdsRequestConfig v;v.server=c.server;v.bearerToken=c.credential;
    if(c.smart){if(r.path!=SmartPath)return "스마트교차로 URL 경로 불일치";auto adapted=r;adapted.path=VdsPath;return validateVdsRequest(v,adapted);}
    return validateVdsRequest(v,r);
}
}
std::vector<MethodItem> methodItems(const std::string &s){
    if(weatherCase(s)){
        std::string t=s==WeatherProviderCase?"기상청":"통합교통관제시스템";
        if(s==WeatherProviderCase)return {
            {normalKey(s),t+" 기상정보 정상 제공시험",200,"normal",true},
            {"test_invalid_request",t+" 잘못된 조회변수 오류응답 시험",200,"weather-error",true},
            {"test_no_data_error",t+" 자료 부재 오류응답 시험",200,"absence-error",true},
            {"test_missing_credential",t+" [추가] 인증키 누락 오류응답 시험",200,"weather-error"},
            {"test_wrong_credential",t+" [추가] 인증키 불일치 오류응답 시험",200,"weather-error"},
            {"test_missing_path",t+" [추가] 미존재 경로 오류응답 시험",404,"weather-error"},
            {"test_no_data",t+" [추가] 빈 정상응답 시험",200,"empty"}};
        return {{normalKey(s),t+" 기상정보 정상 요청시험",200,"normal",true},
            {"test_no_data_error_response",t+" 자료 부재 오류응답 조건의 요청시험",200,"absence-error",true},
            {"test_response_parameter_error",t+" [추가] 조회변수 오류응답 조건의 요청시험",200,"weather-error"},
            {"test_response_service_error",t+" [추가] 경로 오류응답 조건의 요청시험",404,"weather-error"},
            {"test_response_server_error",t+" [추가] 서버 오류응답 조건의 요청시험",500,"weather-error"},
            {"test_empty_response",t+" [추가] 빈 정상응답 조건의 요청시험",200,"empty"},
            {"test_malformed_response",t+" [추가] 손상 응답 조건의 요청시험",200,"malformed"}};
    }
    if(shadowCase(s)){
        std::string t=s==ShadowProviderCase?"음영구간 미시교통정보 플랫폼":"통합교통관제시스템";
        if(s==ShadowProviderCase)return {
            {normalKey(s),t+" 음영구간 미시교통정보 정상 제공시험",200,"normal",true},
            {"test_invalid_request",t+" 잘못된 조회변수 오류응답 시험",422,"shadow-error",true},
            {"test_no_data_error",t+" 자료 부재 오류응답 시험",404,"absence-error",true},
            {"test_missing_path",t+" [추가] 미존재 경로 오류응답 시험",404,"status"},
            {"test_no_data",t+" [추가] 빈 정상응답 시험",200,"empty"}};
        return {{normalKey(s),t+" 음영구간 미시교통정보 정상 요청시험",200,"normal",true},
            {"test_no_data_error_response",t+" 자료 부재 오류응답 조건의 요청시험",404,"absence-error",true},
            {"test_response_422",t+" [추가] 조회변수 오류응답 조건의 요청시험",422,"shadow-error"},
            {"test_response_404",t+" [추가] 경로 오류응답 조건의 요청시험",404,"error"},
            {"test_response_500",t+" [추가] 서버 오류응답 조건의 요청시험",500,"error"},
            {"test_empty_response",t+" [추가] 빈 정상응답 조건의 요청시험",200,"empty"},
            {"test_malformed_response",t+" [추가] 손상 응답 조건의 요청시험",200,"malformed"}};
    }
    if(nticCase(s)){
        std::string t=s==NticProviderCase?"NTIC":"통합교통관제시스템";
        if(s==NticProviderCase)return {
            {normalKey(s),t+" 차량검지정보 정상 제공시험",200,"normal",true},
            {"test_invalid_request",t+" 잘못된 조회변수 오류응답 시험",400,"ntic-error",true},
            {"test_no_data_error",t+" 자료 부재 오류응답 시험",404,"absence-error",true},
            {"test_missing_credential",t+" [추가] 인증키 누락 거부시험",401,"ntic-error"},
            {"test_wrong_credential",t+" [추가] 인증키 불일치 거부시험",401,"ntic-error"},
            {"test_missing_path",t+" [추가] 미존재 경로 오류응답 시험",404,"ntic-error"},
            {"test_no_data",t+" [추가] 빈 정상응답 시험",200,"empty"}};
        return {{normalKey(s),t+" NTIC 차량검지정보 정상 요청시험",200,"normal",true},
            {"test_no_data_error_response",t+" 자료 부재 오류응답 조건의 요청시험",404,"absence-error",true},
            {"test_response_400",t+" [추가] 조회변수 오류응답 조건의 요청시험",400,"ntic-error"},
            {"test_response_404",t+" [추가] 경로 오류응답 조건의 요청시험",404,"ntic-error"},
            {"test_response_500",t+" [추가] 서버 오류응답 조건의 요청시험",500,"ntic-error"},
            {"test_empty_response",t+" [추가] 빈 정상응답 조건의 요청시험",200,"empty"},
            {"test_malformed_response",t+" [추가] 손상 응답 조건의 요청시험",200,"malformed"}};
    }
    auto target=s==UticProviderCase?"UTIC":(s==VdsCase||s==SmartProviderCase)?"통합교통관제시스템":(s==VdsRequestCase||s==SmartRequestCase)?"미시교통정보 플랫폼":"통합교통관제시스템";
    std::string t=std::string(target)+" "+(xmlCase(s)?"돌발정보":smartCase(s)?"스마트교차로 1분 교통정보":"VDS 원시정보 이력");
    if(providerCase(s))return {
        {normalKey(s),t+" 정상 정보제공 시험",200,"normal",true},
        {"test_invalid_request",t+" 잘못된 요청 오류응답 시험",400,(xmlCase(s)||smartCase(s))?"status":"error-schema",true},
        {"test_no_data_error",t+" 자료 부재 오류응답 시험",404,"absence-error",true},
        {"test_missing_credential",t+" [추가] 자격정보 누락 거부시험",401,"status"},
        {"test_wrong_credential",t+" [추가] 자격정보 불일치 거부시험",401,"status"},
        {"test_missing_path",t+" [추가] 미존재 경로 거부시험",404,"status"},
        {"test_no_data",t+" [추가] 빈 정상응답 시험 (200/204)",200,"empty"}};
    return {{normalKey(s),t+" 정상 정보요청 시험",200,"normal",true},
        {"test_no_data_error_response",t+" 자료 부재 오류응답 조건의 요청시험",404,"absence-error",true},
        {"test_response_400",t+" [추가] HTTP 400 오류응답 조건의 요청시험",400,(xmlCase(s)||smartCase(s))?"error":"error-schema"},
        {"test_response_404",t+" [추가] HTTP 404 오류응답 조건의 요청시험",404,"error"},
        {"test_response_500",t+" [추가] HTTP 500 오류응답 조건의 요청시험",500,(xmlCase(s)||smartCase(s))?"error":"error-schema"},
        {"test_empty_response",t+" [추가] 빈 정상응답 조건의 요청시험 (200)",200,"empty"},
        {"test_malformed_response",t+" [추가] 손상 응답 조건의 요청시험 (200)",200,"malformed"}};
}
std::string methodBasis(const MethodConfig &c,const MethodItem &i){
    if(!i.standardRequired)return "추가 검증: 표준의 독립 필수 시험 항목으로 집계하지 않음";
    if(c.provider){
        if(i.check=="normal")return "제4부 제4장 1.2.1 평가내용 1)·2)";
        if(i.check=="absence-error")return "제4부 제4장 1.2.1 시험방법 3) 및 사전조건 확인";
        return "제4부 제4장 1.2.1 시험방법 3)·평가내용 3)";
    }
    return i.check=="absence-error"?"제4부 제4장 1.1.1 시험방법 3)·평가내용 1)·2)·3)":"제4부 제4장 1.1.1 평가내용 1)·2), 미처리 시 3)";
}
std::string unobservedScope(const MethodConfig &c,const MethodItem &item){
    if(!c.provider)return "대상의 실제 응답 수신·분석·업무 반영 결과는 시험기에서 직접 관측하지 않았습니다.";
    if(item.check=="normal")return "대상의 내부 준비자료와 응답 값의 일치는 시험기에서 직접 관측하지 않았습니다.";
    if(item.check=="absence-error")return "대상의 실제 자료 0건 여부는 준비 확인 조건으로 사용하며 내부 조회 결과는 직접 관측하지 않았습니다.";
    return "대상의 내부 처리 과정은 직접 관측하지 않았습니다.";
}
MethodConfig MethodConfig::parse(const std::string &scenario,const std::string &raw){
    if(scenario!=VdsCase&&scenario!=UticProviderCase&&scenario!=VdsRequestCase&&scenario!="uticServer2center_v1"&&!smartCase(scenario)&&!nticCase(scenario)&&!shadowCase(scenario)&&!weatherCase(scenario))throw Failure("지원하지 않는 REST case");
    auto j=Json::parse(raw);if(j.kind!=Json::Object)throw Failure("설정은 JSON 객체여야 합니다.");
    MethodConfig c;c.scenario=scenario;c.xml=xmlCase(scenario);c.provider=providerCase(scenario);c.smart=smartCase(scenario);c.ntic=nticCase(scenario);c.weather=weatherCase(scenario);if(c.weather)c.weatherOptions=rest::weatherOptions(j);c.shadow=shadowCase(scenario);if(c.shadow)c.shadowParams=shadowQuery(j);
    if(c.ntic){auto p=j.get("api_path");if(p&&!(p->kind==Json::String&&p->text.empty())){if(p->kind!=Json::String||(p->text!="/vdsInfo"&&p->text!="//vdsInfo"))throw Failure("NTIC 경로는 /vdsInfo 또는 //vdsInfo로 지정하세요.");c.nticPath=p->text;}}
    if(auto path=j.get("evidence_directory")){
        if(path->kind!=Json::String||path->text.size()>2048||path->text.find_first_of("\r\n")!=std::string::npos||path->text.find('\0')!=std::string::npos)throw Failure("대상 증적 폴더 입력 오류");
        c.evidenceDirectory=path->text;
        if(!c.evidenceDirectory.empty()&&!std::filesystem::u8path(c.evidenceDirectory).is_absolute())throw Failure("대상 증적 폴더는 절대 경로로 입력하세요.");
    }
    if(auto wait=j.get("evidence_wait_s")){
        if(!((wait->kind==Json::String&&wait->text.empty()))){
            if((wait->kind!=Json::String&&wait->kind!=Json::Number)||wait->text.empty()||wait->text.size()>3||wait->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure("증적 대기시간 입력 오류");
            c.evidenceWaitSeconds=static_cast<unsigned>(std::stoul(wait->text));if(!c.evidenceWaitSeconds||c.evidenceWaitSeconds>600)throw Failure("증적 대기시간은 1~600초로 입력하세요.");
        }
    }
    c.badRequest=c.weather?statusInput(j,"bad_request_status",200,{200,400,422}):statusInput(j,"bad_request_status",c.shadow?422:400,{400,422});
    c.unauthorized=c.weather?statusInput(j,"unauthorized_status",200,{200,401,403}):statusInput(j,"unauthorized_status",401,{401,403});c.noData=statusInput(j,"no_data_status",200,{200,204});
    c.noDataError=c.weather?statusInput(j,"no_data_error_status",200,{200,400,404,410,422}):statusInput(j,"no_data_error_status",404,{400,404,410,422});
    if(c.weather){c.missingPathStatus=statusInput(j,"missing_path_status",404,{200,404});c.serverErrorStatus=statusInput(j,"server_error_status",500,{200,500});}c.dataAbsentConfirmed=selected(j,"confirm_data_absent");
    if(c.shadow&&c.badRequest!=422)throw Failure("음영구간 API에 정의된 조회변수 오류응답 코드 422를 사용하세요.");
    if(scenario==VdsCase&&c.badRequest!=400)throw Failure("VDS API에 정의된 잘못된 요청 응답 코드 400을 사용하세요.");
    for(auto item:methodItems(scenario))if(selected(j,item.key)){
        if(c.weather){if(item.key=="test_response_parameter_error")item.expected=c.badRequest;if(item.key=="test_missing_path"||item.key=="test_response_service_error")item.expected=c.missingPathStatus;if(item.key=="test_response_server_error")item.expected=c.serverErrorStatus;}
        if(item.key=="test_invalid_request")item.expected=c.badRequest;
        if(item.key=="test_missing_credential"||item.key=="test_wrong_credential")item.expected=c.unauthorized;
        if(item.check=="absence-error")item.expected=c.noDataError;
        if(item.key=="test_no_data"){item.expected=c.noData;item.check=c.noData==200?"empty":"status";}
        c.items.push_back(item);
    }
    if(c.items.empty())throw Failure("시험 항목을 하나 이상 선택하세요.");
    if(c.provider&&unsigned(selected(j,"test_no_data"))+unsigned(selected(j,"test_no_data_error"))+unsigned(selected(j,normalKey(scenario)))>1)throw Failure("자료 부재 오류·빈 정상응답·정상 제공은 각각 다른 사전조건으로 별도 실행하세요.");
    if(c.provider&&selected(j,"test_no_data_error")&&!c.dataAbsentConfirmed)throw Failure("자료 부재 시험은 같은 유효 API에 대상 자료가 없는 상태를 준비하고 확인해야 합니다.");
    // Reuse existing transport/config validation without forcing selection in the UI.
    auto forced=j;Json yes;yes.kind=Json::Bool;yes.boolean=true;forced.object[normalKey(scenario)]=yes;if(c.smart)forced.object[c.provider?"test_normal_vds":"test_request_vds"]=yes;if(c.ntic||c.weather){forced.object[c.provider?"test_provide_utic":"test_normal_utic"]=yes;auto p=j.get("response_json_file");if(p)forced.object["response_xml_file"]=*p;}if(c.shadow){
        // Reuse only legacy address/time/port validation; no credential is sent.
        forced.object["api_key"]=Json::parse(quote("transport-validation-only"));
        forced.object[c.provider?"test_provide_utic":"test_normal_utic"]=yes;
        if(auto p=j.get("response_json_file"))forced.object["response_xml_file"]=*p;
    }auto config=dump(forced);
    if(scenario==UticProviderCase||scenario==NticProviderCase||scenario==ShadowProviderCase||scenario==WeatherProviderCase){auto v=UticProviderConfig::parse(config);c.baseUrl=v.baseUrl;c.credential=v.apiKey;c.repetitions=v.repetitions;c.connectTimeout=v.connectTimeout;c.timeout=v.requestTimeout;}
    else if(scenario==VdsCase||scenario==SmartProviderCase){auto v=VdsConfig::parse(config);c.baseUrl=v.baseUrl;c.credential=v.bearerToken;c.repetitions=v.repetitions;c.connectTimeout=v.connectTimeout;c.timeout=v.requestTimeout;}
    else if(scenario==VdsRequestCase||scenario==SmartRequestCase){auto v=VdsRequestConfig::parse(config);c.server=v.server;c.credential=v.bearerToken;}
    else{c.server=Config::parse(config);c.credential=c.server.apiKey;}
    if(!c.provider){c.repetitions=c.server.repetitions;c.timeout=c.server.requestTimeout;c.fixture=c.server.fixturePath;}
    if(c.weather)validateWeatherResponse({200,"application/json",weatherFixture(c.weatherOptions)});
    if(c.shadow)c.credential.clear();
    if(c.repetitions<10)throw Failure("각 시험 항목은 최소 10회 교환해야 합니다.");
    if(!c.provider){auto b=c.fixture.empty()?(c.weather?weatherFixture(c.weatherOptions):c.shadow?shadowFixture():c.ntic?nticFixture():c.xml?defaultFixture():c.smart?defaultSmartFixture():defaultVdsFixture()):readTextFile(c.fixture);records({200,c.xml?"application/xml":"application/json",b},c.xml,c.smart,c.ntic,c.shadow,c.weather,false);}
    return c;
}
std::string methodUI(const std::string &scenario){
    auto base=baseUI(scenario);
    if(weatherCase(scenario)){
        auto replace=[&](const std::string &from,const std::string &to){size_t p=0;while((p=base.find(from,p))!=std::string::npos){base.replace(p,from.size(),to);p+=to.size();}};
        replace("UTIC","기상청");replace("UT 센터","통합교통관제시스템");replace("돌발정보","기상정보");replace("response_xml_file","response_json_file");replace("XML","JSON");replace("55328","55330");replace("55307","55309");replace("요청 key","요청 serviceKey (디코딩된 원문)");replace("시험용 key","시험용 serviceKey (디코딩된 원문)");
    }
    if(shadowCase(scenario)){
        auto replace=[&](const std::string &from,const std::string &to){size_t p=0;while((p=base.find(from,p))!=std::string::npos){base.replace(p,from.size(),to);p+=to.size();}};
        replace("UTIC","음영구간 미시교통정보 플랫폼");replace("UT 센터","통합교통관제시스템");replace("돌발정보","음영구간 미시교통정보");
        replace("response_xml_file","response_json_file");replace("XML","JSON");replace("55328","55331");replace("55307","55310");
    }
    if(nticCase(scenario)){
        auto replace=[&](const std::string &from,const std::string &to){size_t p=0;while((p=base.find(from,p))!=std::string::npos){base.replace(p,from.size(),to);p+=to.size();}};
        replace("UTIC","NTIC");replace("UT 센터","통합교통관제시스템");replace("돌발정보","차량검지정보");
        replace("response_xml_file","response_json_file");replace("XML","JSON");replace("55328","55329");replace("55307","55308");
        replace("요청 key","요청 apiKey");replace("시험용 key","시험용 apiKey");
    }
    if(smartCase(scenario)){
        auto replace=[&](const std::string &from,const std::string &to){size_t p=0;while((p=base.find(from,p))!=std::string::npos){base.replace(p,from.size(),to);p+=to.size();}};
        replace("VDS 원시정보 이력","스마트교차로 1분 교통정보");replace("55311","55341");replace("55332","55342");
    }
    auto ui=Json::parse(base);auto catalog=methodItems(scenario);auto &entries=ui.object["scenarios"].array;entries.clear();
    auto &groups=ui.object["configuration"].array[0].object["components"].array;
    if(weatherCase(scenario)){
        auto &inputs=groups[0].object["components"].array;
        for(auto p:{std::make_pair("api_path",WeatherPath),std::make_pair("service_key_name","serviceKey"),std::make_pair("pageNo","1"),std::make_pair("numOfRows","10"),std::make_pair("base_date","20260924"),std::make_pair("base_time","0600"),std::make_pair("nx","55"),std::make_pair("ny","127")}){
            std::string label=std::string(p.first)=="api_path"?"기상 API 경로 (초단기실황/초단기예보)":std::string(p.first)=="service_key_name"?"인증변수명 (serviceKey 또는 ServiceKey)":std::string(p.first)=="base_date"?"발표일자 base_date (YYYYMMDD)":std::string(p.first)=="base_time"?"발표시각 base_time (hhmm)":std::string(p.first)=="pageNo"?"조회 페이지 pageNo":std::string(p.first)=="numOfRows"?"페이지당 건수 numOfRows":std::string(p.first)=="nx"?"예보지점 X 좌표 nx":"예보지점 Y 좌표 ny";
            inputs.push_back(Json::parse("{\"type\":\"Input\",\"option\":{\"name\":"+quote(p.first)+",\"label\":"+quote(label)+",\"type\":\"text\",\"value\":"+quote(p.second)+"}}"));
        }
    }
    if(shadowCase(scenario)){
        auto &inputs=groups[0].object["components"].array;
        inputs.erase(std::remove_if(inputs.begin(),inputs.end(),[](const Json &v){auto o=v.get("option");auto n=o?o->get("name"):nullptr;return n&&n->text=="api_key";}),inputs.end());
        for(auto pair:{std::make_pair("since","since: 직전 응답의 총 데이터 값 (정수, 빈 값은 생략)"),std::make_pair("node_link","node_link: 노드링크 필터 (문자열, 빈 값은 생략)"),std::make_pair("latest","latest: 최근 자료 건수 (0~500, 빈 값은 생략)")})
            inputs.push_back(Json::parse("{\"type\":\"Input\",\"option\":{\"name\":"+quote(pair.first)+",\"label\":"+quote(pair.second)+",\"type\":\"text\",\"value\":\"\"}}"));
    }
    if(nticCase(scenario))groups[0].object["components"].array.push_back(Json::parse(R"JSON({"type":"Input","option":{"name":"api_path","label":"NTIC API 경로 (계약에 맞춰 /vdsInfo 또는 //vdsInfo)","type":"text","value":"/vdsInfo"}})JSON"));
    auto primary=groups.back(),additional=groups.back();groups.pop_back();
    primary.object["option"].object["label"]=Json::parse(quote("기능·오류상황 관련 시험 (협의하여 선택)"));
    additional.object["option"].object["label"]=Json::parse(quote("추가 조건별 시험 (협의하여 선택)"));
    primary.object["components"].array.clear();additional.object["components"].array.clear();
    MethodConfig preview;preview.scenario=scenario;preview.provider=providerCase(scenario);preview.xml=xmlCase(scenario);preview.smart=smartCase(scenario);preview.ntic=nticCase(scenario);preview.shadow=shadowCase(scenario);preview.weather=weatherCase(scenario);
    for(auto &item:catalog){
        auto definition=Json::parse(userCaseDefinition(preview,item));
        auto description=definition.get("입력 조건")->text+" "+definition.get("HTTP 응답 기준")->text+". "+definition.get("응답 기준 출처")->text;
        entries.push_back(Json::parse("{\"key\":"+quote(item.key)+",\"title\":"+quote(item.title)+",\"description\":"+quote(description)+"}"));
        auto &checks=(item.standardRequired?primary:additional).object["components"].array;
        checks.push_back(Json::parse("{\"type\":\"Input\",\"option\":{\"name\":"+quote(item.key)+",\"label\":"+quote(item.title)+",\"type\":\"checkbox\"}}"));
    }
    groups.push_back(std::move(primary));groups.push_back(std::move(additional));
    if(providerCase(scenario)&&!weatherCase(scenario)){
        Json group=Json::parse(R"JSON({"type":"FieldSet","option":{"label":"응답 판정 기준 (명세 우선, 미정 항목은 채택 기본값)"},"components":[]})JSON");
        for(auto entry:{std::make_pair("bad_request_status","잘못된 요청 기대 코드: 400 또는 422"),std::make_pair("unauthorized_status","자격정보 오류 기대 코드: 401 또는 403"),std::make_pair("no_data_status","추가 빈 정상응답 코드: 200 또는 204")}){
            if(shadowCase(scenario)&&std::string(entry.first)=="unauthorized_status")continue;
            auto value=std::string(entry.first)=="bad_request_status"?(shadowCase(scenario)?"422":"400"):std::string(entry.first)=="unauthorized_status"?"401":"200";
            if(shadowCase(scenario)&&std::string(entry.first)=="bad_request_status")entry.second="잘못된 조회변수 기대 코드: API 명세 422";
            if(scenario==VdsCase&&std::string(entry.first)=="bad_request_status")entry.second="잘못된 요청 기대 코드: API 명세 400";
            group.object["components"].array.push_back(Json::parse("{\"type\":\"Input\",\"option\":{\"name\":"+quote(entry.first)+",\"label\":"+quote(entry.second)+",\"type\":\"number\",\"value\":"+quote(value)+"}}"));}
        groups.insert(groups.end()-2,std::move(group));
    }
    if(weatherCase(scenario)){
        auto g=Json::parse(R"JSON({"type":"FieldSet","option":{"label":"업무 오류별 HTTP 상태 (명세 미정, 프로젝트 설정)"},"components":[]})JSON");
        for(auto p:{std::make_pair("bad_request_status","200"),std::make_pair("unauthorized_status","200"),std::make_pair("missing_path_status","404"),std::make_pair("server_error_status","500"),std::make_pair("no_data_status","200")}){
            std::string label=std::string(p.first)=="bad_request_status"?"조회변수 오류 HTTP 코드 (200/400/422)":std::string(p.first)=="unauthorized_status"?"인증 오류 HTTP 코드 (200/401/403)":std::string(p.first)=="missing_path_status"?"경로 오류 HTTP 코드 (200/404)":std::string(p.first)=="server_error_status"?"서버 오류 HTTP 코드 (200/500)":"추가 빈 정상응답 HTTP 코드 (200/204)";
            g.object["components"].array.push_back(Json::parse("{\"type\":\"Input\",\"option\":{\"name\":"+quote(p.first)+",\"label\":"+quote(label)+",\"type\":\"number\",\"value\":"+quote(p.second)+"}}"));
        }groups.insert(groups.end()-2,std::move(g));
    }
    Json absence=Json::parse(R"JSON({"type":"FieldSet","option":{"label":"자료 부재 오류응답 조건"},"components":[{"type":"Input","option":{"name":"no_data_error_status","label":"자료 부재 오류응답 HTTP 코드 (시험 profile, 표준 고정값 아님)","type":"number","value":"404"}}]})JSON");
    if(weatherCase(scenario))absence.object["components"].array[0].object["option"].object["value"]=Json::parse(quote("200"));
    if(providerCase(scenario))absence.object["components"].array.push_back(Json::parse(R"JSON({"type":"Input","option":{"name":"confirm_data_absent","label":"같은 유효 API에서 대상 자료가 없는 상태를 준비했습니다 (대상 증적 별도 확인)","type":"checkbox"}})JSON"));
    groups.insert(groups.end()-2,std::move(absence));
    groups.insert(groups.end()-2,Json::parse(R"JSON({"type":"FieldSet","option":{"label":"대상 기록 자동 대조 (선택)"},"components":[{"type":"Input","option":{"name":"evidence_directory","label":"대상 증적 폴더 (엔진 실행 PC의 절대 경로, 선택)","type":"text","value":""}},{"type":"Input","option":{"name":"evidence_wait_s","label":"송수신 후 대상 증적 준비 대기시간 (1~600초)","type":"number","value":"30"}}]})JSON"));
    return dump(ui);
}
std::string effectiveConfiguration(const MethodConfig &c,const std::string &raw){
    auto j=Json::parse(raw);
    auto text=[&](const std::string &k,const std::string &v){j.object[k]=Json::parse(quote(v));};
    auto number=[&](const std::string &k,unsigned v){j.object[k]=Json::parse(std::to_string(v));};
    auto flag=[&](const std::string &k,bool v){j.object[k]=Json::parse(v?"true":"false");};
    number("repetitions",c.repetitions);number("request_timeout_s",c.timeout);number("bad_request_status",c.badRequest);number("unauthorized_status",c.unauthorized);number("no_data_status",c.noData);number("no_data_error_status",c.noDataError);number("evidence_wait_s",c.evidenceWaitSeconds);text("evidence_directory",c.evidenceDirectory);flag("confirm_data_absent",c.dataAbsentConfirmed);
    if(c.provider){text("sut_base_url",c.baseUrl);number("connect_timeout_s",c.connectTimeout);}else{text("bind_ip",c.server.bindIp);number("local_port",c.server.port);text(c.xml?"response_xml_file":"response_json_file",c.fixture);}
    if(!c.shadow)text(c.xml||c.ntic||c.weather?"api_key":"bearer_token",c.credential);
    if(c.ntic)text("api_path",c.nticPath);
    if(c.shadow){for(auto k:{"since","node_link","latest"})text(k,"");for(auto &q:c.shadowParams)text(q.first,q.second);}
    if(c.weather){text("api_path",c.weatherOptions.path);text("service_key_name",c.weatherOptions.keyName);for(auto &q:c.weatherOptions.query)text(q.first,q.second);number("missing_path_status",c.missingPathStatus);number("server_error_status",c.serverErrorStatus);}
    for(auto &item:methodItems(c.scenario))flag(item.key,std::any_of(c.items.begin(),c.items.end(),[&](const auto &v){return v.key==item.key;}));
    return dump(j);
}
namespace {
void acceptedFile(const std::string &data){
    auto path=std::filesystem::current_path()/"rest-selection.json",tmp=std::filesystem::current_path()/"rest-selection.json.tmp";save(tmp,data);
    if(!MoveFileExW(tmp.c_str(),path.c_str(),MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH))throw Failure("적용 설정 기록을 저장하지 못했습니다.");
}
}
void saveAcceptedConfiguration(const MethodConfig &c,const std::string &raw,unsigned index){
    std::string tests="[";for(auto &item:c.items){if(tests.size()>1)tests+=",";tests+=quote(item.key);}tests+="]";
    acceptedFile("{\"schemaVersion\":1,\"valid\":true,\"processId\":"+std::to_string(GetCurrentProcessId())+",\"testIdx\":"+std::to_string(index)+",\"case\":"+quote(c.scenario)+",\"tests\":"+tests+",\"configuration\":"+raw+",\"effectiveConfiguration\":"+effectiveConfiguration(c,raw)+"}");
}
void invalidateAcceptedConfiguration(const std::string &scenario){acceptedFile("{\"schemaVersion\":1,\"valid\":false,\"processId\":"+std::to_string(GetCurrentProcessId())+",\"case\":"+quote(scenario)+"}");}
Result runMethod(const MethodConfig &c,std::atomic<bool> &stop,const Sink &sink){
    Result result;result.runId=std::to_string(std::chrono::system_clock::now().time_since_epoch().count())+"-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+"-"+c.scenario;
    bool hasStandard=std::any_of(c.items.begin(),c.items.end(),[](const auto &i){return i.standardRequired;});
    auto profile=c.weather?"WEATHER-STANDARD-001":c.shadow?"SHADOW-STANDARD-001":c.ntic?"NTIC-STANDARD-001":c.smart?"SMART-STANDARD-001":"REST-DATA-003";
    auto dir=std::filesystem::current_path()/"rest-results"/sha256(result.runId).substr(0,24);std::filesystem::create_directories(dir);std::ofstream trace(dir/"events.jsonl",std::ios::binary);
    auto event=[&](const std::string &name,const std::string &extra=""){trace<<"{\"runId\":"<<quote(result.runId)<<",\"event\":"<<quote(name)<<",\"monotonicUs\":"<<std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()<<extra<<"}\n";trace.flush();if(!trace)throw Failure("REST 증적 기록 실패");};
    RestUserLog userLog(c,sink,dir.u8string());userLog.begin();
    std::string path=c.weather?c.weatherOptions.path:c.shadow?ShadowPath:c.ntic?c.nticPath:c.xml?UticPath:c.smart?SmartPath:VdsPath,media=c.xml?"application/xml":"application/json";
    std::string body=c.weather?weatherFixture(c.weatherOptions):c.shadow?shadowFixture():c.ntic?nticFixture():c.xml?defaultFixture():c.smart?defaultSmartFixture():defaultVdsFixture();if(!c.provider&&!c.fixture.empty())body=readTextFile(c.fixture);
    std::unique_ptr<HttpAdapter> server;std::string summaries;bool aborted=false;unsigned exchange=0,itemIndex=0;
    try{if(!c.provider){server.reset(new HttpAdapter(c.server,true));server->start();event("listening",",\"port\":"+std::to_string(c.server.port));if(sink.diagnostic)sink.diagnostic("LISTENING");userLog.listening();}}
    catch(const std::exception &e){result.verdict="FAIL";result.detail=e.what();aborted=true;}
    for(const auto &item:c.items){
        std::ofstream messages(dir/("test-data-"+item.key+".jsonl"),std::ios::binary);
        std::ofstream textData(dir/("test-data-"+item.key+".txt"),std::ios::binary);
        if(!messages||!textData)throw Failure("시험 메시지 기록 파일을 만들 수 없습니다.");
        RestEvidence evidence(c,[&](unsigned n,const std::string &direction,const std::string &summary,const std::string &data){
            messages<<data<<"\n";messages.flush();
            textData<<n<<"/"<<c.repetitions<<"회 "<<direction<<": "<<summary<<"\n"<<data<<"\n";textData.flush();
            if(!messages||!textData)throw Failure("시험 메시지 기록 실패");
            userLog.message(item,n,direction,summary,data);
        });
        std::string prepared=(item.check=="absence-error"||item.check=="empty"||item.key=="test_no_data")?(c.weather?weatherFixture(c.weatherOptions,true):c.ntic?nticFixture(true):c.xml?"<result/>":"[]"):body;
        auto preparedFile="prepared-"+item.key+".body";save(dir/preparedFile,prepared);
        auto basis=methodBasis(c,item);std::string classification=item.standardRequired?"standard_requirement":"supplementary";
        auto countPrepared=records({200,media,prepared},c.xml,c.smart,c.ntic,c.shadow,c.weather,true);
        event("precondition",",\"test\":"+quote(item.key)+",\"requestMode\":\"single\",\"endpoint\":"+quote(c.provider?c.baseUrl:c.server.bindIp+":"+std::to_string(c.server.port))+",\"owner\":"+quote(c.provider?"tester_reference":"test_system")+",\"path\":"+quote(path)+",\"dataState\":"+quote(countPrepared?"available":"absent")+",\"recordCount\":"+std::to_string(countPrepared)+",\"sourceFile\":"+quote(preparedFile)+",\"sourceSha256\":"+quote(sha256(prepared))+",\"operatorConfirmed\":"+(c.dataAbsentConfirmed?"true":"false")+",\"basis\":"+quote(basis));
        std::string verdict="NOT_RUN",detail="이전 항목 중단으로 미실행";unsigned completed=0,attempted=0,actualStatus=0;++itemIndex;
        if(!aborted){
            if(sink.state)sink.state(item.key,"START");
            userLog.item(item,itemIndex);
            try{
                event("item_start",",\"test\":"+quote(item.key)+",\"expectedStatus\":"+std::to_string(item.expected)+",\"validation\":"+quote(item.check)+",\"profile\":"+quote(profile));
                for(unsigned n=0;n<c.repetitions;++n){
                    if(stop)throw Stopped();++exchange;attempted=n+1;actualStatus=0;
                    std::string extra=",\"test\":"+quote(item.key)+",\"exchange\":"+std::to_string(exchange)+",\"iteration\":"+std::to_string(n+1)+",\"expectedStatus\":"+std::to_string(item.expected)+",\"validation\":"+quote(item.check);
                    if(c.provider){
                        HttpFields headers={{"X-Test-Run-Id",result.runId},{"X-Test-Exchange",std::to_string(exchange)}},query;
                        std::string requestPath=path,credential=c.credential;
                        if(item.key=="test_wrong_credential")credential="INVALID-"+credential;
                        if(!c.weather&&!c.shadow&&item.key!="test_missing_credential"){if(c.xml||c.ntic)query.push_back({c.ntic?"apiKey":"key",credential});else headers.push_back({"Authorization","Bearer "+credential});}
                        if(c.weather)query=weatherQuery(c.weatherOptions,c.credential,item.key);
                        if(c.shadow){query=c.shadowParams;if(item.key=="test_invalid_request"){query.erase(std::remove_if(query.begin(),query.end(),[](const auto &v){return v.first=="latest";}),query.end());query.push_back({"latest","501"});}}
                        if(c.ntic)query.push_back({"getType",item.key=="test_invalid_request"?"unsupported":"json"});
                        if(item.key=="test_invalid_request"&&!c.ntic&&!c.shadow&&!c.weather){if(c.xml)query.push_back({"key",credential});else query.push_back({"unsupported","1"});}
                        if(item.key=="test_missing_path")requestPath+="/not-found";
                        userLog.request(item,n+1,requestPath);
                        event("request",extra+",\"method\":\"GET\",\"path\":"+quote(requestPath)+(c.weather?",\"queryParameters\":"+weatherPublicQuery(query):c.shadow?",\"queryParameters\":"+shadowQueryJson(query):"")+",\"queryCount\":"+std::to_string(query.size())+",\"credentialsRedacted\":true");
                        evidence.request(n+1,"GET",requestPath,query,!c.shadow&&item.key!="test_missing_credential",0);
                        auto r=httpGet(c.baseUrl+requestPath,c.connectTimeout,c.timeout,stop,headers,query,c.xml);
                        actualStatus=r.status;size_t rowCount=0;
                        evidence.response(n+1,r.status,r.contentType,r.body);
                        save(dir/("response-"+std::to_string(exchange)+".body"),r.body);
                        event("response",extra+",\"status\":"+std::to_string(r.status)+",\"bodySha256\":"+quote(sha256(r.body))+",\"contentType\":"+quote(r.contentType));
                        if(r.status!=item.expected)throw Failure("HTTP 응답 코드 불일치: 기대 "+std::to_string(item.expected)+" / 수신 "+std::to_string(r.status));
                        if(c.weather&&(item.check=="weather-error"||item.check=="absence-error"))validateWeatherError(r,weatherResultCode(item.key));
                        else if(item.check=="shadow-error")validateShadowError(r);
                        else if(item.check=="ntic-error")validateNticError(r,nticResultCode(item.key));
                        else if(item.check=="normal")rowCount=records(r,c.xml,c.smart,c.ntic,c.shadow,c.weather,false);
                        else if(item.check=="error-schema"||(item.check=="absence-error"&&!c.xml&&!c.smart&&!c.ntic&&!c.shadow&&!c.weather&&r.status==400))vdsError(r);
                        else if(item.check=="empty"&&(rowCount=records(r,c.xml,c.smart,c.ntic,c.shadow,c.weather,true))!=0)throw Failure("자료 부재 시험에서 비어 있지 않은 자료 수신");
                        else if(item.expected==204&&!r.body.empty())throw Failure("HTTP 204 응답에 본문이 있습니다.");
                        if(c.weather&&(item.check=="normal"||item.check=="empty"))validateWeatherPage(r,c.weatherOptions);
                        userLog.exchange(item,n+1,r.status,r.contentType,r.body.size(),rowCount,r.body);
                    }else{
                        userLog.request(item,n+1,path);
                        auto q=server->receive(stop,c.timeout);auto reason=requestReason(c,q);
                        bool auth=c.weather?std::any_of(q.query.begin(),q.query.end(),[&](const auto &v){return v.first==c.weatherOptions.keyName;}):(c.xml||c.ntic)?std::any_of(q.query.begin(),q.query.end(),[&](const auto &v){return v.first==(c.ntic?"apiKey":"key");}):!q.authorization.empty();
                        save(dir/("request-"+std::to_string(exchange)+".body"),q.body);
                        evidence.request(n+1,q.method,q.path,q.query,auth,q.bodyBytes,q.bodyDeclared,q.body);
                        event("request",extra+",\"method\":"+quote(q.method)+",\"path\":"+quote(q.path)+(c.weather?",\"queryParameters\":"+weatherPublicQuery(q.query):c.shadow?",\"queryParameters\":"+shadowQueryJson(q.query):"")+",\"queryCount\":"+std::to_string(q.query.size())+",\"bodyBytes\":"+std::to_string(q.bodyBytes)+",\"accepted\":"+(reason.empty()?"true":"false")+",\"credentialsRedacted\":true");
                        if(!reason.empty()){event("request_rejected",extra+",\"reason\":"+quote(reason));save(dir/("response-"+std::to_string(exchange)+".body"),"Invalid request");server->respond(q,400,"Invalid request", "text/plain",result.runId,exchange,stop,c.timeout);evidence.response(n+1,400,"text/plain","Invalid request");throw Failure(reason);}
                        if(item.check=="normal"||item.check=="empty"||item.check=="absence-error")event("data_lookup",extra+",\"path\":"+quote(path)+",\"recordCount\":"+std::to_string(countPrepared)+",\"sourceSha256\":"+quote(sha256(prepared)));
                        std::string supplied=item.check=="absence-error"?"DATA_NOT_FOUND: Requested information is unavailable":item.check=="normal"?prepared:item.check=="empty"?(c.weather?weatherFixture(c.weatherOptions,true):c.ntic?nticFixture(true):c.xml?"<result/>":"[]"):item.check=="malformed"?(c.xml?"<result><record>":"[{"):"Request could not be completed";
                        bool jsonError=item.check=="error-schema"||(item.check=="absence-error"&&!c.xml&&!c.smart&&!c.ntic&&!c.shadow&&!c.weather&&item.expected==400);
                        if(jsonError)supplied="{\"code\":\""+std::to_string(item.expected)+"\",\"message\":\"Request could not be completed\",\"time\":\"2026-09-24T00:00:00Z\",\"path\":"+quote(path)+"}";
                        if(c.weather&&(item.check=="weather-error"||item.check=="absence-error"))supplied=weatherErrorBody(weatherResultCode(item.key));
                        if(c.shadow&&item.check=="shadow-error")supplied=shadowErrorBody();
                        if(c.ntic&&(item.check=="ntic-error"||item.check=="absence-error"))supplied=nticErrorBody(nticResultCode(item.key));
                        save(dir/("response-"+std::to_string(exchange)+".body"),supplied);
                        server->respond(q,item.expected,supplied,((item.check=="error"||item.check=="absence-error")&&!jsonError&&!c.ntic&&!c.weather)?"text/plain":media,result.runId,exchange,stop,c.timeout);
                        actualStatus=item.expected;
                        evidence.response(n+1,item.expected,((item.check=="error"||item.check=="absence-error")&&!jsonError&&!c.ntic&&!c.weather)?"text/plain":media,supplied);
                        userLog.exchange(item,n+1,item.expected,((item.check=="error"||item.check=="absence-error")&&!jsonError&&!c.ntic&&!c.weather)?"text/plain":media,supplied.size(),0,supplied);
                        event("response_sent",extra+",\"status\":"+std::to_string(item.expected)+",\"bodySha256\":"+quote(sha256(supplied)));
                    }
                    ++completed;++result.exchanges;
                }
                verdict="SUCCESS";
                detail=c.provider?"응답 코드·본문의 자동 검사 완료. "+unobservedScope(c,item):"요청 유효성·응답 전송의 자동 검사 완료. "+unobservedScope(c,item);
            }catch(const Stopped &e){verdict="STOPPED";detail=e.what();result.verdict=verdict;result.detail=detail;aborted=true;}
            catch(const std::exception &e){verdict="FAIL";detail=e.what();result.verdict=verdict;result.detail=detail;aborted=true;}
        }
        event("item_result",",\"test\":"+quote(item.key)+",\"verdict\":"+quote(verdict)+",\"completedExchanges\":"+std::to_string(completed)+",\"detail\":"+quote(detail));
        auto displayData=evidence.finish(verdict,completed);
        textData<<displayData<<"\n";textData.flush();
        auto displayJson=evidence.json(verdict,completed);
        displayJson.pop_back();displayJson+=",\"판정 범위\":\"엔진 자동 관측 범위\",\"시험 구분\":"+quote(item.standardRequired?"시험방법의 기능·오류상황 관련 항목":"추가 조건별 검증")+",\"근거 조항\":"+quote(basis)+",\"직접 관측하지 않은 내용\":"+quote(unobservedScope(c,item))+",\"상세시험 조건\":"+userCaseDefinition(c,item)+"}";
        save(dir/("test-data-"+item.key+".json"),displayJson);
        userLog.result(item,verdict,completed,detail,attempted,actualStatus,displayJson);
        // FINISH closes the platform report; Context::run sends it once for
        // MainScenario after every selected item and evidence message is sent.
        // Keep START until the final automatic outcome is emitted by RestReview.
        // Unexecuted items have no START/terminal notification.
        if(!summaries.empty())summaries+=",";summaries+="{\"test\":"+quote(item.key)+",\"classification\":"+quote(classification)+",\"basis\":"+quote(basis)+",\"expectedStatus\":"+std::to_string(item.expected)+",\"validation\":"+quote(item.check)+",\"verdict\":"+quote(verdict)+",\"completedExchanges\":"+std::to_string(completed)+",\"detail\":"+quote(detail)+",\"unobserved\":"+quote(unobservedScope(c,item))+"}";
    }
    if(!aborted){result.verdict="SUCCESS";result.detail="선택 항목의 송수신·규격 자동 검증 완료. 직접 관측하지 않은 대상 내부 동작은 판정 범위에 포함하지 않습니다.";}
    event("result",",\"verdict\":"+quote(result.verdict));result.reportPath=(dir/"result.json").u8string();
    save(dir/"result.json","{\"schemaVersion\":4,\"assessmentProfile\":\"REST-AUTO-001\",\"assessmentScope\":\"ENGINE_OBSERVABLE\",\"methodProfile\":\"REST-EVIDENCE-002\",\"standardAssessment\":"+quote(hasStandard?"AUTOMATIC_SCOPE_ONLY":"NOT_APPLICABLE")+",\"sutRole\":"+quote(c.provider?"provider":"requester")+",\"runId\":"+quote(result.runId)+",\"case\":"+quote(c.scenario)+",\"profile\":"+quote(profile)+",\"apiPath\":"+quote(path)+(c.weather?",\"queryParameters\":"+weatherPublicQuery(c.weatherOptions.query)+",\"serviceKeyName\":"+quote(c.weatherOptions.keyName):c.shadow?",\"queryParameters\":"+shadowQueryJson(c.shadowParams):"")+",\"automaticVerdict\":"+quote(result.verdict)+",\"requestedRepetitions\":"+std::to_string(c.repetitions)+",\"completedExchanges\":"+std::to_string(result.exchanges)+",\"items\":["+summaries+"]}\n");
    return result;
}
}
