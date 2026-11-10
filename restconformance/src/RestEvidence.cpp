#include "RestEvidence.h"
#include <algorithm>
#include <sstream>
#include <windows.h>

namespace rest {
namespace {
std::string replace(std::string s,const std::string &from,const std::string &to){if(from.empty())return s;size_t p=0;while((p=s.find(from,p))!=std::string::npos){s.replace(p,from.size(),to);p+=to.size();}return s;}
std::string encoded(const std::string &s){const char *hex="0123456789ABCDEF";std::string out;for(unsigned char c:s){if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c=='-'||c=='_'||c=='.'||c=='~')out+=char(c);else{out+='%';out+=hex[c>>4];out+=hex[c&15];}}return out;}
std::string xmlText(const std::string &s){return replace(replace(replace(s,"&","&amp;"),"<","&lt;"),">","&gt;");}
std::string xml(const std::string &s){return replace(replace(xmlText(s),"\"","&quot;"),"'","&apos;");}
std::string redact(std::string s,const std::string &credential){
    if(credential.empty())return s;
    for(const auto &secret:{"INVALID-"+credential,credential})if(!secret.empty()){
        std::vector<std::string> values={secret,encoded(secret),xml(secret),xmlText(secret),quote(secret).substr(1,quote(secret).size()-2)};
        auto lower=encoded(secret);for(size_t i=0;i+2<lower.size();++i)if(lower[i]=='%'){lower[i+1]=static_cast<char>(std::tolower(static_cast<unsigned char>(lower[i+1])));lower[i+2]=static_cast<char>(std::tolower(static_cast<unsigned char>(lower[i+2])));i+=2;}values.push_back(lower);
        for(const auto &value:values)s=replace(s,value,"[비공개]");
    }
    return s;
}
std::string pretty(const Json &j,const std::string &key,unsigned depth=0){
    if(j.kind==Json::String)return quote(redact(j.text,key));if(j.kind==Json::Number)return j.text;if(j.kind==Json::Bool)return j.boolean?"true":"false";if(j.kind==Json::Null)return "null";
    bool array=j.kind==Json::Array;std::string out=array?"[":"{";unsigned n=0;
    if(array)for(auto &v:j.array){if(n++)out+=",";out+=pretty(v,key,depth+1);}
    else for(auto &v:j.object){if(n++)out+=",";out+=quote(redact(v.first,key))+":"+pretty(v.second,key,depth+1);}
    return out+(array?"]":"}");
}
// All bytes are represented; oversized display messages are split, never clipped.
std::string bodyJson(const std::string &body,const std::string &credential){
    if(body.empty())return quote("(본문 없음)");
    try{return pretty(Json::parse(body,1024*1024),credential);}catch(...){}
    auto clean=redact(body,credential);
    if(!MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,clean.data(),static_cast<int>(clean.size()),nullptr,0)){
        const char *digits="0123456789ABCDEF";std::string hex;
        for(unsigned char c:clean){if(!hex.empty())hex+=' ';hex+=digits[c>>4];hex+=digits[c&15];}
        return "{\"표현\":\"UTF-8로 읽을 수 없어 전체 바이트를 16진수로 표시합니다.\",\"바이트\":"+quote(hex)+"}";
    }
    return quote(clean);
}
std::string missing(const std::string &verdict){return verdict=="NOT_RUN"?"이 항목은 실행하지 않아 송수신 데이터가 없습니다.":"송수신 데이터가 수집되기 전에 중지되었거나 요청을 받지 못했습니다.";}
}
void RestEvidence::message(unsigned iteration,const std::string &direction,const std::string &summary,const std::string &detail){
    ++messageNumber;
    const std::string provider=config.weather?"기상청":config.shadow?"음영구간 미시교통정보 플랫폼":config.ntic?"국가교통정보센터(NTIC)":config.xml?"UTIC":"통합교통관제시스템";
    const std::string requester=(config.weather||config.shadow||config.ntic||config.xml)?"통합교통관제시스템":"미시교통정보 플랫폼";
    bool response=direction.find("응답")!=std::string::npos;
    auto prefix="{\"연계정보\":"+quote(config.weather?"기상정보 / JSON":config.shadow?"음영구간 미시교통정보 / JSON":config.ntic?"NTIC 차량검지정보 / JSON":config.xml?"UTIC 돌발정보 / XML":config.smart?"스마트교차로 1분 교통정보 / JSON":"VDS 차로별 원시정보 이력 / JSON")+
        ",\"회차\":"+std::to_string(iteration)+",\"반복 횟수\":"+std::to_string(config.repetitions)+
        ",\"메시지 순번\":"+std::to_string(messageNumber)+",\"구분\":"+quote(direction)+",\"발송 주체\":"+quote(response?provider:requester)+",\"수신 주체\":"+quote(response?requester:provider);
    // Limit each transport notification, not the amount of evidence. UTF-8 code
    // points remain whole, and all parts carry the same logical message number.
    constexpr size_t partBytes=12000;
    if(detail.size()<=partBytes){emit(iteration,direction,summary,prefix+",\"상세\":"+detail+"}");return;}
    std::vector<std::string> parts;
    for(size_t pos=0;pos<detail.size();){
        size_t end=std::min(pos+partBytes,detail.size());
        while(end<detail.size()&&(static_cast<unsigned char>(detail[end])&0xc0)==0x80)--end;
        parts.push_back(detail.substr(pos,end-pos));pos=end;
    }
    for(size_t i=0;i<parts.size();++i){
        auto label=" (분할 "+std::to_string(i+1)+"/"+std::to_string(parts.size())+")";
        emit(iteration,direction,summary+label,prefix+",\"분할 번호\":"+std::to_string(i+1)+",\"전체 분할 수\":"+std::to_string(parts.size())+
            ",\"분할 안내\":\"같은 메시지의 상세 JSON을 순서대로 나누어 표시합니다. 생략한 내용은 없습니다.\",\"분할 데이터\":"+quote(parts[i])+"}");
    }
}
void RestEvidence::request(unsigned n,const std::string &method,const std::string &path,const HttpFields &query,bool credentialPresent,size_t bodyBytes,bool declared,const std::string &body){
    ++requests;std::string vars="[";bool first=true;
    for(const auto &q:query){if(!first)vars+=",";first=false;vars+="{\"이름\":"+quote(redact(q.first,config.credential))+",\"값\":"+quote((q.first=="key"||q.first=="apiKey"||q.first=="serviceKey"||q.first=="ServiceKey")?"[비공개]":redact(q.second,config.credential))+"}";}
    vars+="]";
    auto detail="{\"상태\":"+quote(config.provider?"요청 전송 시도":"수신 완료")+
        ",\"메서드\":"+quote(redact(method,config.credential))+",\"URL 경로\":"+quote(redact(path,config.credential))+
        ",\"요청변수\":"+vars+",\"인증정보\":"+quote(credentialPresent?"포함(값 비공개)":"없음")+
        ",\"본문 크기\":"+std::to_string(bodyBytes)+",\"본문 전송 선언\":"+(declared?"true":"false")+
        ",\"본문\":"+(declared&&body.empty()?quote("전송 선언은 있으나 본문은 수집되지 않았습니다."):bodyJson(body,config.credential))+"}";
    message(n,config.provider?"송신 요청":"수신 요청",config.provider?"요청을 전송합니다. 응답 수신 여부를 이어서 확인합니다.":"대상의 요청 메시지를 수신했습니다.",detail);
}
void RestEvidence::response(unsigned n,unsigned status,const std::string &media,const std::string &body){
    ++responses;
    auto detail="{\"상태\":"+quote(config.provider?"수신 완료":"전송 완료")+
        ",\"HTTP 상태 코드\":"+std::to_string(status)+",\"Content-Type\":"+quote(media.empty()?"미표시":redact(media,config.credential))+
        ",\"본문 크기\":"+std::to_string(body.size())+",\"본문\":"+bodyJson(body,config.credential)+"}";
    message(n,config.provider?"수신 응답":"송신 응답","HTTP "+std::to_string(status)+" / 본문 "+std::to_string(body.size())+"바이트. 전체 메시지를 기록했습니다.",detail);
}
std::string RestEvidence::finish(const std::string &verdict,unsigned completed) const{
    std::string out="연계정보: "+std::string(config.weather?"기상정보 / JSON":config.shadow?"음영구간 미시교통정보 / JSON":config.ntic?"NTIC 차량검지정보 / JSON":config.xml?"UTIC 돌발정보 / XML":config.smart?"스마트교차로 1분 교통정보 / JSON":"VDS 차로별 원시정보 이력 / JSON")+
        "\n확인한 교환: "+std::to_string(completed)+"/"+std::to_string(config.repetitions)+"회\n요청 메시지: "+std::to_string(requests)+
        "건\n응답 메시지: "+std::to_string(responses)+"건\n각 회차의 송신·수신 메시지를 별도로 모두 기록했습니다. 동일 내용도 묶거나 생략하지 않습니다.\n";
    if(!requests&&!responses)out+=missing(verdict);
    else if(requests>responses)out+="응답이 확인되지 않은 요청이 있습니다. 전송 시도를 응답 수신 완료로 판정하지 않습니다.";
    return out;
}
std::string RestEvidence::json(const std::string &verdict,unsigned completed) const{
    auto out="{\"연계정보\":"+quote(config.weather?"기상정보 / JSON":config.shadow?"음영구간 미시교통정보 / JSON":config.ntic?"NTIC 차량검지정보 / JSON":config.xml?"UTIC 돌발정보 / XML":config.smart?"스마트교차로 1분 교통정보 / JSON":"VDS 차로별 원시정보 이력 / JSON")+
        ",\"확인한 교환\":"+quote(std::to_string(completed)+"/"+std::to_string(config.repetitions)+"회")+
        ",\"요청 메시지 수\":"+std::to_string(requests)+",\"응답 메시지 수\":"+std::to_string(responses)+
        ",\"기록 안내\":\"각 회차의 송신·수신 메시지를 별도로 모두 기록했습니다. 인증값은 가리며, 긴 메시지는 분할 번호 순서대로 표시합니다.\"";
    if(!requests&&!responses)out+=",\"미수집 사유\":"+quote(missing(verdict));
    else if(requests>responses)out+=",\"응답 미확인 요청 수\":"+std::to_string(requests-responses);
    return out+"}";
}
}
