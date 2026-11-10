#pragma once
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <mutex>
#include <regex>
#include <string>
#include <vector>

// Public presentation only. Never modify protocol bytes, business fields,
// result enums, or the original diagnostic evidence.
namespace interface_log {
inline std::string quote(const std::string &s){std::string out="\"";const char *hex="0123456789abcdef";for(unsigned char c:s){if(c=='"'||c=='\\'){out+='\\';out+=c;}else if(c<32){out+="\\u00";out+=hex[c>>4];out+=hex[c&15];}else out+=c;}return out+'"';}
inline std::string verdict(const std::string &s){return s=="SUCCESS"?"성공":s=="FAIL"?"실패":s=="STOPPED"?"중지":s=="NOT_RUN"?"미실행":s=="ERROR"?"수행 오류":s;}
inline void replace(std::string &s,const std::string &from,const std::string &to){size_t p=0;while((p=s.find(from,p))!=std::string::npos){s.replace(p,from.size(),to);p+=to.size();}}
inline std::string text(std::string s){
    replace(s,"UT 센터","통합교통관제시스템");replace(s,"SUT","시험 대상");replace(s,"profile","적용 기준");
    for(const auto &key:{"MainScenario","runId=","processId=","sha256=","Traceback",".cpp:",".py:"})if(s.find(key)!=std::string::npos)return "상세 진단을 별도 기록했습니다. 해당 시험의 판정 근거와 결과를 확인하세요.";
    if(std::regex_search(s,std::regex("(^|[ =\\\"(])[A-Za-z]:[\\\\/]")))return "자료 또는 실행 환경을 확인하지 못했습니다. 설정을 확인하고 필요한 경우 상세 진단을 확인하세요.";
    replace(s,"SUCCESS","성공");replace(s,"STOPPED","중지");replace(s,"NOT_RUN","미실행");
    return s;
}
inline std::string phase(const std::string &s){
    if(!s.empty()&&s[0]=='['){auto end=s.find(']');if(end!=std::string::npos){auto tag=s.substr(1,end-1);for(auto p:{"시험 안내","준비","진행","송신","수신","판정 근거","결과"})if(tag==p)return tag;if(tag=="시험 시작"||tag=="확인 기준")return "시험 안내";if(tag=="확인"||tag=="증적"||tag=="결과 확인"||tag=="검증 증적")return "판정 근거";if(tag=="절차")return "진행";if(tag=="최종 판정"||tag=="항목 결과"||tag=="기록 저장")return "결과";}}
    if(s.find("시험 대상:")==0||s.find("적용 기준:")==0)return "시험 안내";
    if(s.find("시험 준비:")==0)return "준비";
    auto has=[&](const char *v){return s.find(v)!=std::string::npos;};
    if(has("송신")&&(has("메시지")||has("프레임")))return "송신";
    if(has("수신")&&(has("메시지")||has("프레임")))return "수신";
    if(has("시험 시작")||has("시험 안내")||has("시험 구성")||has("연계정보")||has("검증 기준")||has("확인 기준")||has("요구사항"))return "시험 안내";
    if(has("결과")||has("최종 판정")||has("항목 실패")||has("중지:")||has("미실행:")||has("자동 관측검사 통과")||has("자동 검증 완료"))return "결과";
    if(has("기대")||has("실제")||has("대조")||has("검사")||has("확인")||has("증적"))return "판정 근거";
    if(has("준비")||has("설정")||has("대기"))return "준비";
    return "진행";
}
inline std::string line(const std::string &message,const std::string &forced=""){
    auto s=text(message);auto p=forced.empty()?phase(s):forced;
    if(!s.empty()&&s[0]=='['){auto end=s.find(']');if(end!=std::string::npos&&end<60){auto old=s.substr(1,end-1);s=s.substr(end+1);if(old.find("메시지 #")!=std::string::npos)s=old.substr(old.find("메시지 #"))+" · "+s;}}
    while(!s.empty()&&s[0]==' ')s.erase(0,1);
    return "["+p+"] "+s;
}
template<class J> J str(const std::string &s){J v;v.kind=J::String;v.text=s;return v;}
template<class J> std::string dump(const J &j){switch(j.kind){case J::Null:return "null";case J::Bool:return j.boolean?"true":"false";case J::Number:return j.text;case J::String:return quote(j.text);case J::Array:{std::string s="[";for(auto &v:j.array){if(s.size()>1)s+=',';s+=dump(v);}return s+"]";}default:{std::string s="{";for(auto &v:j.object){if(s.size()>1)s+=',';s+=quote(v.first)+":"+dump(v.second);}return s+"}";}}}
template<class J> std::string get(const J &j,const std::string &key){auto v=j.get(key);return v&&v->kind==J::String?v->text:"";}
template<class J> J publicData(J value,const std::string &protocol,const std::string &title,const std::string &stage){
    if(value.kind!=J::Object){J wrapper;wrapper.kind=J::Object;wrapper.object["내용"]=value;value=wrapper;}
    // Only known envelope metadata is suppressed. Payload dictionaries are not
    // traversed: a business field named id/hash is still actual test data.
    for(auto k:{"schemaVersion","runId","case","test","testName","scenario","processId","testIdx","configSha256","sourceSha256","bodySha256","monotonicUs","실행 ID","설계 ID","관측 연결 번호"})value.object.erase(k);
    for(auto it=value.object.begin();it!=value.object.end();){auto key=it->first;if(key.find("SHA-")!=std::string::npos||key.find("해시")!=std::string::npos||key=="sourceFile"||key=="파일 경로"||key=="증적 파일 경로")it=value.object.erase(it);else ++it;}
    if(auto round=value.get("회차"))if(round->kind==J::Number&&round->text=="0"){value.object.erase("회차");value.object["준비 안내"]=str<J>("반복 시험 전의 초기 자료입니다.");}
    if(auto evidence=value.get("확인한 증거")){if(evidence->kind==J::Array&&!evidence->array.empty()){J count;count.kind=J::Number;count.text=std::to_string(evidence->array.size());value.object["추가 대조 기록 수"]=count;}value.object.erase("확인한 증거");}
    if(auto review=value.get("증적 검토")){auto label=review->text;if(label=="추가 자동 대조 미확인")label="미수행 (선택사항)";value.object["추가 기록 대조"]=str<J>(label);value.object.erase("증적 검토");}
    if(auto v=value.get("최종 판정"))if(v->kind==J::String)value.object["최종 판정"]=str<J>(verdict(v->text));
    if(auto v=value.get("verdict")){value.object["판정"]=str<J>(verdict(v->text));value.object.erase("verdict");}
    bool message=value.get("메시지 순번")||value.get("관측 순번");std::string effectiveStage=stage;
    if(message){auto direction=get(value,"구분");if(direction.empty())direction=get(value,"방향");if(direction.find("송신")==0)effectiveStage="송신";else if(direction.find("수신")==0)effectiveStage="수신";}
    if(get(value,"자료 구분").find("결과")!=std::string::npos)effectiveStage="결과";
    if(!value.get("자료 구분"))value.object["자료 구분"]=str<J>(message?"송수신 데이터":stage=="결과"?"시험 결과":stage=="시험 안내"?"시험 안내":"시험 근거");
    value.object["인터페이스"]=str<J>(protocol);value.object["단계"]=str<J>(effectiveStage);
    if(!title.empty()&&title!="MainScenario"&&title.find("test_")!=0)value.object["시험"]=str<J>(title);
    return value;
}
inline std::string guide(const std::string &title,const std::string &target,const std::string &flow,const std::string &criteria,const std::string &scope){
    return "{\"자료 구분\":\"시험 안내\",\"시험\":"+quote(title)+",\"시험 대상\":"+quote(target)+",\"진행 절차\":"+quote(flow)+",\"판정 기준\":"+quote(criteria)+",\"확인 범위\":"+quote(scope)+"}";
}
inline void journal(unsigned index,const std::string &test,const std::string &log,const std::string &sender,const std::string &data){
    static std::mutex mutex;std::lock_guard<std::mutex> lock(mutex);
    std::ofstream f(std::filesystem::current_path()/"interface-user-log.jsonl",std::ios::binary|std::ios::app);
    f<<"{\"testIdx\":"<<index<<",\"testName\":"<<quote(test)<<",\"log\":"<<quote(log)<<",\"sender\":"<<quote(sender);if(!data.empty())f<<",\"data\":"<<data;f<<"}\n";
}
}
