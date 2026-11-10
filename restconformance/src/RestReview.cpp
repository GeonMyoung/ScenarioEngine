#include "RestReview.h"
#include <windows.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <set>

namespace rest { namespace {
const char *Profile="REST-REVIEW-LINK-001";
std::string str(const Json &j,const char *key){auto v=j.get(key);if(!v||v->kind!=Json::String)throw Failure("검토 결과의 필수 문자열이 없습니다.");return v->text;}
unsigned number(const Json &j,const char *key){auto v=j.get(key);if(!v||v->kind!=Json::Number||v->text.empty()||v->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure("검토 결과의 숫자 형식이 다릅니다.");return static_cast<unsigned>(std::stoul(v->text));}
const std::vector<Json> &array(const Json &j,const char *key){auto v=j.get(key);if(!v||v->kind!=Json::Array)throw Failure("검토 결과의 항목 목록이 없습니다.");return v->array;}
std::string dump(const Json &j){
    if(j.kind==Json::String)return quote(j.text);if(j.kind==Json::Number)return j.text;
    if(j.kind==Json::Bool)return j.boolean?"true":"false";if(j.kind==Json::Null)return "null";
    std::string out=j.kind==Json::Array?"[":"{";bool first=true;
    if(j.kind==Json::Array)for(const auto &v:j.array){if(!first)out+=",";first=false;out+=dump(v);}
    else for(const auto &v:j.object){if(!first)out+=",";first=false;out+=quote(v.first)+":"+dump(v.second);}
    return out+(j.kind==Json::Array?"]":"}");
}
void saveNew(const std::filesystem::path &p,const std::string &value){
    if(std::filesystem::exists(p))throw Failure("검토 결과 파일이 이미 있습니다.");
    std::ofstream f(p,std::ios::binary);f<<value;f.close();if(!f)throw Failure("검토 결과 파일을 저장하지 못했습니다.");
}
std::filesystem::path executableDirectory(){std::wstring path(32768,L'\0');auto n=GetModuleFileNameW(nullptr,path.data(),static_cast<DWORD>(path.size()));if(!n||n==path.size())throw Failure("실행 위치 확인 실패");path.resize(n);return std::filesystem::path(path).parent_path();}
std::wstring arg(const std::wstring &value){
    std::wstring out=L"\"";size_t slashes=0;
    for(wchar_t c:value){if(c==L'\\'){++slashes;continue;}if(c==L'\"'){out.append(slashes*2+1,L'\\');out+=c;}else{out.append(slashes,L'\\');out+=c;}slashes=0;}
    out.append(slashes*2,L'\\');return out+L"\"";
}
struct Handle {
    HANDLE h=nullptr;explicit Handle(HANDLE value=nullptr):h(value){}~Handle(){if(h&&h!=INVALID_HANDLE_VALUE)CloseHandle(h);}
    Handle(const Handle &)=delete;Handle &operator=(const Handle &)=delete;
};
struct Attributes {
    std::vector<unsigned char> storage;LPPROC_THREAD_ATTRIBUTE_LIST list=nullptr;HANDLE handles[2]={};
    Attributes(HANDLE log,HANDLE input){handles[0]=log;handles[1]=input;SIZE_T size=0;InitializeProcThreadAttributeList(nullptr,1,0,&size);storage.resize(size);list=reinterpret_cast<LPPROC_THREAD_ATTRIBUTE_LIST>(storage.data());
        if(!InitializeProcThreadAttributeList(list,1,0,&size)){list=nullptr;throw Failure("검토 실행 준비 실패");}
        if(!UpdateProcThreadAttribute(list,0,PROC_THREAD_ATTRIBUTE_HANDLE_LIST,handles,sizeof(handles),nullptr,nullptr)){DeleteProcThreadAttributeList(list);list=nullptr;throw Failure("검토 실행 준비 실패");}}
    ~Attributes(){if(list)DeleteProcThreadAttributeList(list);}
};
void runWorker(const MethodConfig &c,const Result &r,const std::filesystem::path &out,std::atomic<bool> &stop){
    auto root=executableDirectory();auto runtime=Json::parse(readTextFile((root/"rest-review-runtime.json").u8string()));
    if(number(runtime,"schemaVersion")!=1||str(runtime,"worker")!="rest-review/engine_review_worker.py")throw Failure("검토 도구 설정이 올바르지 않습니다.");
    auto python=std::filesystem::u8path(str(runtime,"pythonExecutable"));auto worker=root/"rest-review"/"engine_review_worker.py";
    if(!python.is_absolute()){if(python.generic_u8string()!="python/python.exe")throw Failure("Unsupported relative review runtime");python=root/python;}
    if(!python.is_absolute()||!std::filesystem::is_regular_file(python)||!std::filesystem::is_regular_file(worker))throw Failure("검토 실행 파일을 찾지 못했습니다.");
    auto command=arg(python.wstring())+L" -I -X utf8 "+arg(worker.wstring())+L" --report "+arg(std::filesystem::u8path(r.reportPath).wstring())+
        L" --sut "+arg(std::filesystem::u8path(c.evidenceDirectory).wstring())+L" --output "+arg(out.wstring())+L" --wait-seconds "+std::to_wstring(c.evidenceWaitSeconds);
    SECURITY_ATTRIBUTES security={sizeof(security),nullptr,TRUE};
    Handle log(CreateFileW((out.parent_path()/"review-worker.log").c_str(),GENERIC_WRITE,FILE_SHARE_READ,&security,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,nullptr));
    Handle input(CreateFileW(L"NUL",GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,&security,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr));
    if(log.h==INVALID_HANDLE_VALUE||input.h==INVALID_HANDLE_VALUE)throw Failure("검토 실행 기록을 준비하지 못했습니다.");
    Attributes attributes(log.h,input.h);STARTUPINFOEXW startup={};startup.StartupInfo.cb=sizeof(startup);startup.StartupInfo.dwFlags=STARTF_USESTDHANDLES;
    startup.StartupInfo.hStdInput=input.h;startup.StartupInfo.hStdOutput=log.h;startup.StartupInfo.hStdError=log.h;startup.lpAttributeList=attributes.list;
    Handle job(CreateJobObjectW(nullptr,nullptr));JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits={};limits.BasicLimitInformation.LimitFlags=JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    if(!job.h||!SetInformationJobObject(job.h,JobObjectExtendedLimitInformation,&limits,sizeof(limits)))throw Failure("검토 중지 기능을 준비하지 못했습니다.");
    if(stop)throw Stopped();
    PROCESS_INFORMATION process={};
    if(!CreateProcessW(python.c_str(),command.data(),nullptr,nullptr,TRUE,CREATE_NO_WINDOW|CREATE_SUSPENDED|EXTENDED_STARTUPINFO_PRESENT,nullptr,root.c_str(),&startup.StartupInfo,&process))throw Failure("검토 실행을 시작하지 못했습니다. Windows="+std::to_string(GetLastError()));
    Handle processHandle(process.hProcess),threadHandle(process.hThread);
    if(!AssignProcessToJobObject(job.h,process.hProcess)||ResumeThread(process.hThread)==static_cast<DWORD>(-1)){auto error=GetLastError();TerminateProcess(process.hProcess,2);WaitForSingleObject(process.hProcess,3000);throw Failure("검토 실행을 준비하지 못했습니다. Windows="+std::to_string(error));}
    auto deadline=std::chrono::steady_clock::now()+std::chrono::seconds(c.evidenceWaitSeconds+15);
    while(WaitForSingleObject(process.hProcess,50)==WAIT_TIMEOUT){
        if(stop||std::chrono::steady_clock::now()>deadline){TerminateJobObject(job.h,3);WaitForSingleObject(process.hProcess,3000);if(stop)throw Stopped();throw Failure("검토 실행 제한시간을 초과했습니다.");}
    }
    DWORD code=0;if(!GetExitCodeProcess(process.hProcess,&code)||code!=0)throw Failure("검토 실행을 완료하지 못했습니다. Exit="+std::to_string(code));
}
std::string fallback(const MethodConfig &c,const Result &r,const Json &original,const std::string &hash,const std::string &status,const std::string &reason){
    auto final=status=="STOPPED"&&r.verdict=="SUCCESS"?std::string("STOPPED"):r.verdict;
    std::string items;
    for(const auto &item:array(original,"items")){
        if(!items.empty())items+=",";auto automatic=str(item,"verdict");auto itemFinal=automatic=="SUCCESS"&&status=="STOPPED"?std::string("STOPPED"):automatic;
        items+="{\"test\":"+quote(str(item,"test"))+",\"automaticVerdict\":"+quote(automatic)+",\"reviewStatus\":"+quote(status)+",\"finalVerdict\":"+quote(itemFinal)+",\"completedExchanges\":"+std::to_string(number(item,"completedExchanges"))+",\"basis\":"+quote(str(item,"basis"))+",\"unobserved\":"+quote(str(item,"unobserved"))+",\"evidence\":[]}";
    }
    return "{\"schemaVersion\":1,\"assessmentScope\":\"ENGINE_OBSERVABLE\",\"integrationProfile\":"+quote(Profile)+",\"runId\":"+quote(r.runId)+",\"case\":"+quote(c.scenario)+",\"automaticResultSha256\":"+quote(hash)+",\"automaticVerdict\":"+quote(r.verdict)+",\"reviewStatus\":"+quote(status)+",\"finalVerdict\":"+quote(final)+",\"reason\":"+quote(reason)+",\"items\":["+items+"],\"review\":null}";
}
void checkLinked(const Json &j,const MethodConfig &c,const Result &r,const Json &original,const std::string &hash){
    if(number(j,"schemaVersion")!=1||str(j,"assessmentScope")!="ENGINE_OBSERVABLE"||str(j,"integrationProfile")!=Profile||str(j,"runId")!=r.runId||str(j,"case")!=c.scenario||str(j,"automaticVerdict")!=r.verdict||str(j,"automaticResultSha256")!=hash)throw Failure("현재 실행과 검토 결과의 연결이 다릅니다.");
    auto status=str(j,"reviewStatus");auto expected=status=="FAIL"?"FAIL":"SUCCESS";
    if((status!="PASS"&&status!="FAIL"&&status!="NOT_CONFIRMED")||str(j,"finalVerdict")!=expected)throw Failure("검토 판정 조합이 잘못됐습니다.");
    const auto &items=array(j,"items"),&before=array(original,"items");if(items.size()!=before.size())throw Failure("검토된 시험 항목 수가 다릅니다.");
    for(size_t n=0;n<items.size();++n)if(str(items[n],"test")!=str(before[n],"test")||str(items[n],"automaticVerdict")!=str(before[n],"verdict")||number(items[n],"completedExchanges")!=number(before[n],"completedExchanges")||str(items[n],"reviewStatus")!=status||str(items[n],"finalVerdict")!="SUCCESS")throw Failure("검토된 시험 항목의 연결이 다릅니다.");
    if(status=="PASS"){
        auto review=j.get("review");if(!review||str(*review,"reviewProfile")!="REST-REVIEW-003"||str(*review,"runId")!=r.runId||str(*review,"reportSha256")!=hash||str(*review,"developmentVerification")!="PASS"||number(*review,"verifiedItems")!=c.items.size()||number(*review,"verifiedExchanges")!=r.exchanges)throw Failure("검토 통과의 근거가 현재 실행과 다릅니다.");
    }
}
std::string label(const std::string &s){return s=="SUCCESS"||s=="PASS"?"통과":s=="FAIL"?"불일치":s=="STOPPED"?"중지":s=="NOT_RUN"?"미실행":s=="SKIPPED"?"검토 미수행":"추가 자동 대조 미확인";}
} // namespace
ReviewResult completeEvidenceReview(const MethodConfig &c,const Result &r,std::atomic<bool> &stop,const Sink &sink){
    auto originalText=readTextFile(r.reportPath);auto original=Json::parse(originalText,1024*1024);auto hash=sha256(originalText);
    auto directory=std::filesystem::u8path(r.reportPath).parent_path();auto output=directory/"review-link.json";
    std::string linked;
    if(r.verdict!="SUCCESS")linked=fallback(c,r,original,hash,"SKIPPED","송수신 시험의 실패·중지·미실행 결과를 유지합니다.");
    else if(stop)linked=fallback(c,r,original,hash,"STOPPED","증적 검토를 중지했습니다. 자동 관측 결과와 수집한 증거는 보존합니다.");
    else if(c.evidenceDirectory.empty())linked=fallback(c,r,original,hash,"NOT_REQUESTED","엔진이 직접 관측한 범위로 자동 판정을 완료했습니다. 대상 내부 처리 기록의 추가 대조는 수행하지 않았으며 사후 자료 제출을 요구하지 않습니다.");
    else{
        if(sink.info)sink.info("증적 확인: 송수신을 완료했습니다. 대상의 준비자료·수신·처리 기록을 기다린 뒤 같은 시험 실행의 증거를 대조합니다.");
        try{
            auto workerResult=directory/"review-worker-result.json";runWorker(c,r,workerResult,stop);
            if(stop)throw Stopped();linked=readTextFile(workerResult.u8string());auto value=Json::parse(linked,1024*1024);checkLinked(value,c,r,original,hash);
            if(readTextFile(r.reportPath)!=originalText)throw Failure("자동 결과가 검토 중 변경됐습니다.");
        }catch(const Stopped &){linked=fallback(c,r,original,hash,"STOPPED","증적 검토를 중지했습니다. 자동 관측 결과와 수집한 증거는 보존합니다.");}
        catch(const std::exception &e){std::ofstream diagnostic(directory/"review-diagnostic.txt",std::ios::binary);diagnostic<<e.what();linked=fallback(c,r,original,hash,"UNAVAILABLE","추가 자동 대조를 완료하지 못했습니다. 엔진의 송수신·규격 자동 판정은 유지하고 미확인 사실을 기록합니다.");}
    }
    saveNew(output,linked);auto value=Json::parse(linked,1024*1024);ReviewResult result{str(value,"reviewStatus"),str(value,"finalVerdict"),output.u8string()};
    for(const auto &item:array(value,"items")){
        auto key=str(item,"test");auto found=std::find_if(c.items.begin(),c.items.end(),[&](const auto &i){return i.key==key;});
        auto evidence=item.get("evidence");auto detail="{\"자료 구분\":\"증적 검토 결과\",\"실행 ID\":"+quote(r.runId)+",\"시험\":"+quote(found==c.items.end()?key:found->title)+",\"자동 관측 판정\":"+quote(label(str(item,"automaticVerdict")))+",\"증적 검토\":"+quote(label(str(item,"reviewStatus")))+",\"최종 판정\":"+quote(label(str(item,"finalVerdict")))+",\"확인한 교환 수\":"+std::to_string(number(item,"completedExchanges"))+",\"판정 범위\":\"엔진 자동 관측 범위\",\"직접 관측하지 않은 내용\":"+quote(str(item,"unobserved"))+",\"근거 조항\":"+quote(str(item,"basis"))+",\"확인한 증거\":"+(evidence?dump(*evidence):"[]")+",\"검토 안내\":"+quote(str(value,"reason"))+",\"원본 결과 SHA-256\":"+quote(hash)+"}";
        if(sink.itemData)sink.itemData(key,"추가 자동 대조: "+label(result.status)+". "+str(value,"reason"),"JSON",detail);
        auto final=str(item,"finalVerdict");if(sink.state&&final!="NOT_RUN")sink.state(key,final);
    }
    auto summary="{\"자료 구분\":\"전체 증적 검토 결과\",\"실행 ID\":"+quote(r.runId)+",\"자동 관측 판정\":"+quote(label(r.verdict))+",\"증적 검토\":"+quote(label(result.status))+",\"최종 판정\":"+quote(label(result.finalVerdict))+",\"검토 안내\":"+quote(str(value,"reason"))+",\"선택 항목 수\":"+std::to_string(c.items.size())+",\"원본 결과 SHA-256\":"+quote(hash)+"}";
    if(sink.itemData)sink.itemData("MainScenario","최종 확인: "+label(result.finalVerdict)+". "+str(value,"reason"),"JSON",summary);
    return result;
}
} // namespace rest
