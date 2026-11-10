#include "SignalMethod.h"
#include <windows.h>
#include <fstream>
#include <iostream>
#include <thread>
int runMain(int argc,char **argv){
    SetConsoleOutputCP(CP_UTF8);std::string config,scenario,hex,operation;unsigned message=68,stopAfter=0;signalbinary::Profile profile;
    for(int i=1;i<argc;++i){std::string k=argv[i];if(i+1>=argc)return 2;auto v=argv[++i];if(k=="--config")config=v;else if(k=="--case")scenario=v;else if(k=="--hex")hex=v;else if(k=="--operation")operation=v;else if(k=="--message")message=std::stoul(v);else if(k=="--stop-after-ms")stopAfter=std::stoul(v);else if(k=="--lrc")profile.checksum=v;else if(k=="--encoding")profile.encoding=v;else if(k=="--ack-seq")profile.ackSequence=v;else return 2;}
    std::atomic<bool> stop{false},done{false};std::thread timer;int status=2;
    try{
        if(!operation.empty()){
            if(operation=="encode"){auto rows=config.empty()?signalbinary::fixture(message):rest::Json::parse(rest::readTextFile(config),1024*1024);std::cout<<signalbinary::hex(signalbinary::packet(message,2,0,signalbinary::encode(message,rows,profile),profile));return 0;}
            if(operation=="decode"){auto f=signalbinary::frame(signalbinary::unhex(hex),profile);std::cout<<signalbinary::dump(signalbinary::decode(f.message,f.payload,profile));return 0;}
            if(operation=="ui"){std::cout<<signalbinary::configureUI(scenario);return 0;}
            if(operation=="inspect"){std::cout<<signalbinary::effectiveConfiguration(signalbinary::Config::parse(scenario,rest::readTextFile(config)));return 0;}return 2;
        }
        auto c=signalbinary::Config::parse(scenario,rest::readTextFile(config));
        if(stopAfter)timer=std::thread([&]{auto until=std::chrono::steady_clock::now()+std::chrono::milliseconds(stopAfter);while(!done&&std::chrono::steady_clock::now()<until)std::this_thread::sleep_for(std::chrono::milliseconds(10));if(!done)stop=true;});
        std::ofstream notes("notifications.jsonl",std::ios::binary);rest::Sink sink;sink.info=[](const auto &s){std::cout<<s<<std::endl;};sink.diagnostic=sink.info;
        sink.itemInfo=[&](const auto &,const auto &s){std::cout<<s<<std::endl;};sink.state=[&](const auto &test,const auto &value){notes<<"{\"type\":\"state\",\"test\":"<<rest::quote(test)<<",\"value\":"<<rest::quote(value)<<"}\n";notes.flush();};
        sink.itemData=[&](const auto &test,const auto &message,const auto &,const auto &data){notes<<"{\"type\":\"info\",\"test\":"<<rest::quote(test)<<",\"message\":"<<rest::quote(message)<<",\"data\":"<<data<<"}\n";notes.flush();};
        auto r=signalbinary::run(c,stop,sink);std::cout<<"REPORT "<<r.path<<"\nFINAL "<<r.verdict<<std::endl;status=r.verdict=="SUCCESS"?0:r.verdict=="STOPPED"?3:2;
    }catch(const std::exception &e){std::cerr<<e.what()<<std::endl;}done=true;if(timer.joinable())timer.join();return status;
}
int wmain(int argc,wchar_t **wide){
    std::vector<std::string> args;std::vector<char *> argv;args.reserve(argc);argv.reserve(argc);
    for(int i=0;i<argc;++i){int size=WideCharToMultiByte(CP_UTF8,WC_ERR_INVALID_CHARS,wide[i],-1,nullptr,0,nullptr,nullptr);if(size<=0)return 2;std::string value(size,'\0');WideCharToMultiByte(CP_UTF8,WC_ERR_INVALID_CHARS,wide[i],-1,value.data(),size,nullptr,nullptr);value.pop_back();args.push_back(std::move(value));}
    for(auto &value:args)argv.push_back(value.data());return runMain(argc,argv.data());
}
