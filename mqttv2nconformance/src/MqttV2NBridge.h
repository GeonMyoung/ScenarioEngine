#pragma once
#include "RestCore.h"
#include <filesystem>
#include <winsock2.h>
#include <windows.h>
#include <fstream>
#include <thread>
#include "MqttCredentials.h"

namespace g4mqtt {
inline std::string field(const rest::Json &j,const std::string &key){auto p=j.get(key);return p&&p->kind==rest::Json::String?p->text:"";}
inline std::wstring wide(const std::string &s){int n=MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,s.data(),(int)s.size(),nullptr,0);if(!n)throw rest::Failure("설정에 포함된 경로를 읽을 수 없습니다.");std::wstring v(n,0);MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,s.data(),(int)s.size(),v.data(),n);return v;}
inline std::wstring arg(const std::string &s){std::wstring out=L"\"";unsigned slash=0;for(auto c:wide(s)){if(c==L'\\'){++slash;continue;}out.append(c==L'"'?slash*2+1:slash,L'\\');slash=0;out+=c;}out.append(slash*2,L'\\');return out+L"\"";}
inline std::filesystem::path executableDirectory(){wchar_t path[32768];auto n=GetModuleFileNameW(nullptr,path,32768);if(!n||n==32768)throw rest::Failure("실행 환경의 위치를 확인하지 못했습니다.");return std::filesystem::path(path).parent_path();}
inline rest::Json runtime(){return rest::Json::parse(rest::readTextFile((executableDirectory()/"mqttv2n-runtime.json").u8string()));}
inline std::filesystem::path runtimePath(const rest::Json &r,const std::string &key){auto p=std::filesystem::u8path(field(r,key));return p.is_absolute()?p:executableDirectory()/p;}
inline std::string configureUI(const std::string &scenario){auto r=runtime();return rest::readTextFile((runtimePath(r,"module")/"registration"/(scenario+".ui.json")).u8string());}
inline bool known(const std::string &s){
    return s=="centerSubscriber2vehicle_mqtt_v1" || s=="vehiclePublisher2center_mqtt_v1" ||
           s=="vehicleSubscriber2center_mqtt_v1" || s=="centerPublisher2vehicle_mqtt_v1" ||
           s=="vehicleSubscriber2center_spat_mqtt_v1" || s=="vehicleSubscriber2center_tlsm_mqtt_v1" ||
           s=="vehicleSubscriber2center_tim_mqtt_v1";
}
inline void invalidateSelection(const std::string &scenario,unsigned index){
    auto path=std::filesystem::current_path()/"mqttv2n-selection.json";std::ofstream f(path,std::ios::binary);f<<"{\"valid\":false,\"case\":"<<rest::quote(scenario)<<",\"processId\":"<<GetCurrentProcessId()<<",\"testIdx\":"<<index<<"}";
}
inline void acceptConfiguration(const std::string &scenario,const std::string &raw,unsigned index){
    invalidateSelection(scenario,index);auto r=runtime();auto dir=std::filesystem::current_path();
    auto input=dir/("mqttv2n-setup-"+std::to_string(index)+".json");{std::ofstream f(input,std::ios::binary);f<<protectedConfiguration(raw);}
    auto python=runtimePath(r,"python").u8string();auto script=(runtimePath(r,"module")/"runtime"/"configuration.py").u8string();
    auto receipt=dir/"mqttv2n-selection.json";
    auto command=arg(python)+L" -E -s -B -X utf8 "+arg(script)+L" --case "+arg(scenario)+L" --config "+arg(input.u8string())+L" --receipt "+arg(receipt.u8string())+L" --owner "+std::to_wstring(GetCurrentProcessId())+L" --index "+std::to_wstring(index);
    STARTUPINFOW si={sizeof(si)};PROCESS_INFORMATION pi={};
    if(!CreateProcessW(wide(python).c_str(),command.data(),nullptr,nullptr,FALSE,CREATE_NO_WINDOW,nullptr,nullptr,&si,&pi))throw rest::Failure("설정 검사 실행환경을 준비하지 못했습니다.");
    CloseHandle(pi.hThread);auto waited=WaitForSingleObject(pi.hProcess,15000);DWORD code=0;
    if(waited!=WAIT_OBJECT_0){TerminateProcess(pi.hProcess,2);WaitForSingleObject(pi.hProcess,2000);CloseHandle(pi.hProcess);throw rest::Failure("설정 검사 제한시간을 초과했습니다.");}
    GetExitCodeProcess(pi.hProcess,&code);CloseHandle(pi.hProcess);
    auto result=rest::Json::parse(rest::readTextFile(receipt.u8string()),2000000);auto valid=result.get("valid");
    if(code||!valid||valid->kind!=rest::Json::Bool||!valid->boolean)throw rest::Failure(field(result,"error").empty()?"시험 설정을 확인하세요.":field(result,"error"));
}
inline void run(const std::string &scenario,const std::string &raw,std::atomic<bool> &stop,
                const std::function<void(const rest::Json &)> &emit){
    auto r=runtime();auto work=std::filesystem::current_path();auto id=std::to_string(GetCurrentProcessId())+"-"+std::to_string(GetTickCount64());
    auto dir=work/"mqttv2n-results"/id;std::filesystem::create_directories(dir.parent_path());
    auto config=work/("mqttv2n-config-"+id+".json");{std::ofstream f(config,std::ios::binary);f<<protectedConfiguration(raw);}
    auto cancel=work/"mqttv2n-stop";if(std::filesystem::exists(cancel))std::filesystem::remove(cancel);
    auto python=runtimePath(r,"python").u8string();auto worker=(runtimePath(r,"module")/"runtime"/"worker.py").u8string();
    std::wstring command=arg(python)+L" -E -s -B -X utf8 "+arg(worker)+L" --case "+arg(scenario)+L" --config "+arg(config.u8string())+L" --output "+arg(dir.u8string())+L" --work "+arg(work.u8string());
    STARTUPINFOW si={sizeof(si)};PROCESS_INFORMATION pi={};
    if(!CreateProcessW(wide(python).c_str(),command.data(),nullptr,nullptr,FALSE,CREATE_NO_WINDOW,nullptr,nullptr,&si,&pi))throw rest::Failure("시험 실행 환경을 시작하지 못했습니다. 간편 실행 묶음을 새 폴더에 모두 풀었는지 확인하세요.");
    CloseHandle(pi.hThread);std::string pending;std::uintmax_t position=0;bool terminal=false,stopSent=false;ULONGLONG stopAt=0;
    try{
        for(;;){
            if(stop&&!stopSent){std::ofstream f(cancel);f<<"stop";stopSent=true;stopAt=GetTickCount64();}
            bool exited=WaitForSingleObject(pi.hProcess,0)==WAIT_OBJECT_0;
            std::ifstream f(dir/"events.jsonl",std::ios::binary);if(f){f.seekg(position);std::string next((std::istreambuf_iterator<char>(f)),{});position+=next.size();pending+=next;}
            for(size_t n;(n=pending.find('\n'))!=std::string::npos;){auto line=pending.substr(0,n);pending.erase(0,n+1);if(line.empty())continue;auto e=rest::Json::parse(line,2000000);
                if(terminal)throw rest::Failure("시험 결과 전달 순서에 문제가 발생했습니다. 상세 진단을 확인하세요.");emit(e);if(field(e,"kind")=="state"&&field(e,"testName")=="MainScenario"&&field(e,"value")=="FINISH")terminal=true;
            }
            if(exited)break;
            if(stopSent&&GetTickCount64()-stopAt>20000){TerminateProcess(pi.hProcess,3);WaitForSingleObject(pi.hProcess,2000);throw rest::Stopped();}
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        DWORD exitCode=0;GetExitCodeProcess(pi.hProcess,&exitCode);if(!terminal||!pending.empty()||exitCode)throw rest::Failure("시험 결과를 모두 전달하기 전에 실행이 종료됐습니다. 상세 진단을 확인하세요.");
    }catch(...){if(WaitForSingleObject(pi.hProcess,0)!=WAIT_OBJECT_0){TerminateProcess(pi.hProcess,4);WaitForSingleObject(pi.hProcess,2000);}CloseHandle(pi.hProcess);throw;}
    CloseHandle(pi.hProcess);
}
}
