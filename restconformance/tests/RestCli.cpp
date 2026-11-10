#include "RestCore.h"
#include "VdsProvider.h"
#include "VdsRequester.h"
#include "UticProvider.h"
#include "RestMethod.h"
#include "RestReview.h"
#include <filesystem>
#include <fstream>
#include <dz1_cleanup.h>
#include <dz1_thread.h>
#include <dz1_socket.h>
#include <dz1_socket_callback.h>
#include <iostream>
#include <thread>
#include <windows.h>
#include <dbghelp.h>
#include <shellapi.h>
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "dbghelp.lib")
static LONG crash(EXCEPTION_POINTERS *e) {
    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);
    STACKFRAME64 f = {};
    f.AddrPC.Offset = e->ContextRecord->Rip;
    f.AddrPC.Mode = AddrModeFlat;
    f.AddrFrame.Offset = e->ContextRecord->Rbp;
    f.AddrFrame.Mode = AddrModeFlat;
    f.AddrStack.Offset = e->ContextRecord->Rsp;
    f.AddrStack.Mode = AddrModeFlat;
    for (int i = 0; i < 12; ++i) {
        char storage[sizeof(SYMBOL_INFO) + 512] = {};
        auto sym = (SYMBOL_INFO *)storage;
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym->MaxNameLen = 511;
        DWORD64 off = 0;
        SymFromAddr(process, f.AddrPC.Offset, &off, sym);
        std::cerr << sym->Name << " + " << off << "\n";
        if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, GetCurrentThread(), &f, e->ContextRecord, NULL,
                         SymFunctionTableAccess64, SymGetModuleBase64, NULL))
            break;
    }
    return EXCEPTION_EXECUTE_HANDLER;
}


int main(int argc,char **argv){
    int wideCount=0;auto wide=CommandLineToArgvW(GetCommandLineW(),&wideCount);std::vector<std::string> args;std::vector<char *> pointers;
    if(!wide)return 2;for(int i=0;i<wideCount;++i){int n=WideCharToMultiByte(CP_UTF8,0,wide[i],-1,nullptr,0,nullptr,nullptr);std::string v(n,0);WideCharToMultiByte(CP_UTF8,0,wide[i],-1,v.data(),n,nullptr,nullptr);v.pop_back();args.push_back(v);}LocalFree(wide);for(auto &v:args)pointers.push_back(v.data());argc=wideCount;argv=pointers.data();
    SetConsoleOutputCP(CP_UTF8);
    SetUnhandledExceptionFilter(crash);
    std::string configPath,methodCase;bool inspect=false;
    unsigned stopAfter=0;
    bool vds=false,vdsRequest=false,uticProvider=false,validateSmart=false,validateVds=false,validateUtic=false,validateNtic=false,validateShadow=false,validateShadowError=false,validateWeather=false;
    for(int i=1;i<argc;++i){
        std::string key=argv[i];
        if(key=="--ui-case"&&i+1<argc){try{std::cout<<rest::methodUI(argv[++i]);return 0;}catch(const std::exception &e){std::cerr<<e.what();return 2;}}
        if(key=="--inspect-case"&&i+1<argc){inspect=true;methodCase=argv[++i];continue;}
        if(key=="--validate-shadow"){validateShadow=true;continue;}
        if(key=="--validate-shadow-error"){validateShadowError=true;continue;}
        if(key=="--validate-weather"){validateWeather=true;continue;}
        if(key=="--validate-ntic"){validateNtic=true;continue;}
        if(key=="--validate-smart"){validateSmart=true;continue;}
        if(key=="--validate-vds"){validateVds=true;continue;}
        if(key=="--validate-utic"){validateUtic=true;continue;}
        if(key=="--utic-provider"){uticProvider=true;continue;}
        if(key=="--vds-request"){vdsRequest=true;continue;}
        if(key=="--vds"){vds=true;continue;}
        if(key=="--help"){std::cout<<"--config FILE [--stop-after-ms N]\n";return 0;}
        if(i+1==argc)return 2;
        if(key=="--method-case")methodCase=argv[++i];
        else if(key=="--config")configPath=argv[++i];
        else if(key=="--stop-after-ms")stopAfter=static_cast<unsigned>(std::stoul(argv[++i]));
        else return 2;
    }
    if(configPath.empty())return 2;
    if(inspect){try{auto raw=rest::readTextFile(configPath);auto c=rest::MethodConfig::parse(methodCase,raw);std::cout<<rest::effectiveConfiguration(c,raw);return 0;}catch(const std::exception &e){std::cerr<<e.what();return 2;}}
    if(validateShadowError){try{rest::validateShadowError({422,"application/json",rest::readTextFile(configPath)});return 0;}catch(const std::exception &e){std::cerr<<e.what()<<std::endl;return 2;}}
    if(validateWeather||validateShadow||validateSmart||validateVds||validateUtic||validateNtic){try{rest::HttpResponse r={200,validateUtic?"application/xml":"application/json",rest::readTextFile(configPath)};auto n=validateWeather?rest::validateWeatherResponse(r):validateShadow?rest::validateShadowResponse(r):validateNtic?rest::validateNticResponse(r):validateSmart?rest::validateSmartResponse(r):validateVds?rest::validateVdsResponse(r):rest::validateUticResponse(r);std::cout<<"PASS "<<n<<std::endl;return 0;}catch(const std::exception &e){std::cerr<<e.what()<<std::endl;return 2;}}
    Dz1Cleanup_init();Dz1Error e={};Dz1Thread_init(0,&e);
    if(e.code||!Dz1Socket_init())return 2;
    e=Dz1SocketCallback2_init();if(e.code)return 2;
    int code=2;
    std::atomic<bool> stop{false},done{false};
    std::thread timer;
    try{
        rest::MethodConfig method;rest::UticProviderConfig uticProviderConfig;rest::Config config;rest::VdsConfig vdsConfig;rest::VdsRequestConfig vdsRequestConfig;
        if(!methodCase.empty())method=rest::MethodConfig::parse(methodCase,rest::readTextFile(configPath));else if(uticProvider)uticProviderConfig=rest::UticProviderConfig::parse(rest::readTextFile(configPath));else if(vdsRequest)vdsRequestConfig=rest::VdsRequestConfig::parse(rest::readTextFile(configPath));else if(vds)vdsConfig=rest::VdsConfig::parse(rest::readTextFile(configPath));else config=rest::Config::parse(rest::readTextFile(configPath));
        if(stopAfter)timer=std::thread([&]{auto until=std::chrono::steady_clock::now()+std::chrono::milliseconds(stopAfter);while(!done&&std::chrono::steady_clock::now()<until)std::this_thread::sleep_for(std::chrono::milliseconds(10));if(!done)stop=true;});
        std::ofstream notifications("notifications.jsonl",std::ios::binary);
        rest::Sink sink;sink.info=[](const auto &s){std::cout<<s<<std::endl;};sink.diagnostic=sink.info;
        sink.state=[&](const auto &name,const auto &value){notifications<<"{\"type\":\"state\",\"test\":"<<rest::quote(name)<<",\"value\":"<<rest::quote(value)<<"}\n";notifications.flush();};
        sink.itemData=[&](const auto &name,const auto &message,const auto &type,const auto &data){notifications<<"{\"type\":\"info\",\"test\":"<<rest::quote(name)<<",\"message\":"<<rest::quote(message)<<",\"dataType\":"<<rest::quote(type)<<",\"data\":"<<data<<"}\n";notifications.flush();};
        if(!methodCase.empty())sink.state("MainScenario","START");
        auto result=!methodCase.empty()?rest::runMethod(method,stop,sink):uticProvider?rest::runUticProvider(uticProviderConfig,stop,sink):vdsRequest?rest::runVdsRequest(vdsRequestConfig,stop,sink):vds?rest::runVds(vdsConfig,stop,sink):rest::run(config,stop,sink);
        std::cout<<result.verdict<<" "<<result.detail<<"\nREPORT "<<result.reportPath<<std::endl;
        auto final=result.verdict;
        if(!methodCase.empty()){auto reviewed=rest::completeEvidenceReview(method,result,stop,sink);final=reviewed.finalVerdict;sink.state("MainScenario",final);sink.state("MainScenario","FINISH");std::cout<<"REVIEW "<<reviewed.status<<"\nFINAL "<<final<<"\nREVIEW_REPORT "<<reviewed.path<<std::endl;}
        code=(final=="SUCCESS")?0:final=="STOPPED"?3:2;
    }catch(const std::exception &error){std::cerr<<error.what()<<std::endl;}
    done=true;if(timer.joinable())timer.join();
    Dz1SocketCallback2_initCancel(nullptr);Dz1Socket_cleanup();
    return code;
}
