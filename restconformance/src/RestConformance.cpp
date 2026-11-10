#include "../../interfaceconformance/include/UserLog.h"
#include "RestCore.h"
#include "VdsProvider.h"
#include "VdsRequester.h"
#include "UticProvider.h"
#include "RestMethod.h"
#include "RestUserLog.h"
#include "RestReview.h"
#include <cstdio>
#include "RestThread.h"
#include <RestConformance.h>
#include <ScenarioEngineWebSockMsg.h>
#include <dz1_asn1.h>

namespace {
constexpr unsigned Start=0x0f000001, Stop=0x0f000002, Setup=0x0f000003;
constexpr unsigned State=0x00f00001, Info=0x00f00002, UI=0x00f00006, Initial=0xf0000011;
char *text(const std::string &s) { return const_cast<char *>(s.c_str()); }
Dz1Str systemText(const std::string &s,Dz1Error *e) {
    Dz1Asn1UTF8Str u={reinterpret_cast<u8_t *>(const_cast<char *>(s.data())),static_cast<u32_t>(s.size())};
    return Dz1Asn1UTF8Str_toStr(&u,e);
}
std::string utf8(char *s) {
    Dz1Error e={}; auto u=Dz1Asn1UTF8Str_newFromStr(s,&e);
    if(!u) throw rest::Failure("설정 문자열 변환 실패");
    std::string out(reinterpret_cast<char *>(u->data),u->size); Dz1Asn1UTF8Str_del(u); return out;
}
int compare(void *a,void *b){return a==b?0:std::less<void *>{}(a,b)?-1:1;}
struct Context {
    void *host=nullptr;
    void (*exception)(void *,Dz1Error *)=nullptr;
    void *exceptionArg=nullptr;
    unsigned index=0;
    std::string scenario;
    rest::MethodConfig method;
    rest::Config config;
    rest::VdsConfig vdsConfig;
    bool vds=false, vdsRequest=false,uticProvider=false;
    rest::UticProviderConfig uticProviderConfig;
    rest::VdsRequestConfig vdsRequestConfig;
    const char *testKey() const {return uticProvider?"test_provide_utic":vdsRequest?"test_request_vds":vds?"test_normal_vds":"test_normal_utic";}
    bool configured=false;
    std::atomic<bool> stop{false},running{false};
    rest::ManagedThread worker;
    void join(){stop=true;if(worker.joinable())worker.join();running=false;}
    ~Context(){join();}
    void state(const std::string &name,const std::string &value){
        Dz1Error e={};
        auto c=ScenarioEngineNotifyStateContext_new(text(name),time(nullptr),text(value),&e);
        if(!c)return;
        auto a=ScenarioEngineNotifyStateArg_gen(&e);
        if(!a){ScenarioEngineNotifyStateContext_del(c);return;}
        a->testIdx=index;a->context=c;
        if(Dz1Task_post(host,DZ1_TASK_QUEUE_NONE,State,(void **)&a,(Dz1DelFunc)ScenarioEngineNotifyStateArg_del,nullptr,nullptr,nullptr,nullptr).code)
            ScenarioEngineNotifyStateArg_del(a);
    }
    void info(const std::string &name,const std::string &message,const std::string &type="",const std::string &rawData=""){
        std::string title=name=="MainScenario"?"전체 시험":"시험 준비";for(const auto &item:method.items)if(item.key==name)title=item.title;
        auto log=interface_log::line(message);std::string data=rawData,sender="시험 시스템";
        if(type=="JSON"&&!data.empty())try{auto value=rest::Json::parse(data,2000000);auto who=value.get("발송 주체");if(who&&who->kind==rest::Json::String)sender=who->text;auto shown=interface_log::publicData(value,"REST/API",title,interface_log::phase(message));log=interface_log::line(message,interface_log::get(shown,"단계"));data=interface_log::dump(shown);}catch(...){}
        interface_log::journal(index,name,log,sender,data);
        Dz1Error e={};auto c=ScenarioEngineNotifyInfoContext_gen(&e);if(!c)return;
        c->time=time(nullptr);c->testName=Dz1Str_clone(text(name),&e);c->sender=systemText(sender,&e);c->log=systemText(log,&e);
        if(!data.empty()){c->data=Dz1Binary_new(reinterpret_cast<u8_t *>(const_cast<char *>(data.data())),static_cast<u32_t>(data.size()),&e);c->dataType=Dz1Str_clone(text(type),&e);if(e.code||!c->data||!c->dataType){ScenarioEngineNotifyInfoContext_del(c);info(name,"시험 데이터 표시 자료를 전달하지 못했습니다. 별도 송수신 증적을 확인하세요.");return;}}
        auto a=ScenarioEngineNotifyInfoArg_gen(&e);
        if(!a){ScenarioEngineNotifyInfoContext_del(c);return;}
        a->testIdx=index;a->context=c;
        if(Dz1Task_post(host,DZ1_TASK_QUEUE_NONE,Info,(void **)&a,(Dz1DelFunc)ScenarioEngineNotifyInfoArg_del,nullptr,nullptr,nullptr,nullptr).code)
            ScenarioEngineNotifyInfoArg_del(a);
    }
    void run(){
        try{
            state("MainScenario","START");
            rest::Sink sink;
            sink.state=[&](const auto &name,const auto &value){state(name,value);};
            sink.info=[&](const auto &message){info("MainScenario",message);};
            sink.itemInfo=[&](const auto &name,const auto &message){info(name,message);};
            sink.itemData=[&](const auto &name,const auto &message,const auto &type,const auto &data){info(name,message,type,data);};
            auto result=rest::runMethod(method,stop,sink);
            info("MainScenario",rest::userRunSummary(method,result));
            auto reviewed=rest::completeEvidenceReview(method,result,stop,sink);
            state("MainScenario",reviewed.finalVerdict);state("MainScenario","FINISH");
        }catch(const std::exception &e){info("MainScenario",rest::userError(e.what()));state("MainScenario","FAIL");state("MainScenario","FINISH");}
        running=false;
    }
};
Dz1Error init(void **resource,void *self,str_t,unsigned,void *arg,void *){
    *resource=arg;Dz1Task_postSimple(self,DZ1_TASK_QUEUE_NONE,Initial);return Dz1Error{};
}
void cleanup(void *p){if(p)static_cast<Context *>(p)->join();}
void destroy(void *p){delete static_cast<Context *>(p);}
void exception(void *arg,void *,void *,Dz1Error *e){auto c=static_cast<Context *>(arg);if(c->exception)c->exception(c->exceptionArg,e);}
Dz1TaskProcStatus initial(void *arg,void *,void *,void **,Dz1Error *e){
    auto c=static_cast<Context *>(arg);auto value=systemText(rest::methodUI(c->scenario),e);
    if(!value)return Dz1TaskProcStatus_error;
    *e=Dz1Task_post(c->host,DZ1_TASK_QUEUE_NONE,UI,(void **)&value,(Dz1DelFunc)Dz1Str_del,nullptr,nullptr,nullptr,nullptr);
    if(e->code)Dz1Str_del(value);return Dz1TaskProcStatus_processed;
}
Dz1TaskProcStatus setup(void *arg,void *,void *,void **message,Dz1Error *e){
    auto c=static_cast<Context *>(arg);
    if(c->running){Dz1Error_set(e,EBUSY);return Dz1TaskProcStatus_processed;}
    try{
        auto raw=static_cast<char *>(Dz1TaskSigMsg_getData(*message));if(!raw)throw rest::Failure("설정 누락");
        auto configuration=utf8(raw);auto method=rest::MethodConfig::parse(c->scenario,configuration);
        if(c->worker.joinable())c->worker.join();
        rest::saveAcceptedConfiguration(method,configuration,c->index+1);c->method=std::move(method);c->configured=true;++c->index;
        c->info("MainScenario",rest::userSetupSummary(c->method));Dz1Error_set(e,0);
    }catch(const std::exception &error){c->configured=false;try{rest::invalidateAcceptedConfiguration(c->scenario);}catch(...){}c->info("MainScenario",rest::userError(error.what()));Dz1Error_set(e,EINVAL);}
    return Dz1TaskProcStatus_processed;
}
Dz1TaskProcStatus start(void *arg,void *,void *,void **,Dz1Error *e){
    auto c=static_cast<Context *>(arg);
    if(!c->configured||c->running){Dz1Error_set(e,EINVAL);return Dz1TaskProcStatus_processed;}
    try{if(c->worker.joinable())c->worker.join();c->running=true;c->stop=false;c->configured=false;c->worker.start([c]{c->run();});Dz1Error_set(e,0);}
    catch(...){c->running=false;Dz1Error_set(e,EFAULT);}
    return Dz1TaskProcStatus_processed;
}
Dz1TaskProcStatus stop(void *arg,void *,void *,void **,Dz1Error *e){
    auto c=static_cast<Context *>(arg);c->join();c->info("MainScenario","시험을 중지했습니다. 완료한 교환 기록은 보존되며, 남은 항목은 다시 선택해 실행할 수 있습니다.");Dz1Error_set(e,0);return Dz1TaskProcStatus_processed;
}
}
extern "C" void *RestConformance_new(void *host,Dz1Str scenario,void (*onError)(void *,Dz1Error *),void *onErrorArg,Dz1Error *error){
    Dz1Error local={};if(!error)error=&local;
    if(!host||!scenario||(std::string(scenario)!="uticServer2center_v1"&&std::string(scenario)!=rest::VdsCase&&std::string(scenario)!=rest::VdsRequestCase&&std::string(scenario)!=rest::UticProviderCase&&!rest::smartCase(scenario)&&!rest::nticCase(scenario)&&!rest::shadowCase(scenario)&&!rest::weatherCase(scenario))){Dz1Error_set(error,EINVAL);return nullptr;}
    auto context=new Context;context->host=host;context->scenario=scenario;context->uticProvider=std::string(scenario)==rest::UticProviderCase;context->vds=std::string(scenario)==rest::VdsCase;context->vdsRequest=std::string(scenario)==rest::VdsRequestCase;context->exception=onError;context->exceptionArg=onErrorArg;
    auto task=Dz1Task_new(text("RestConformance"),256,(void **)&context,destroy,compare,init,exception,cleanup,error);
    if(!task){delete context;return nullptr;}
    for(auto handler:{std::make_pair(Initial,initial),std::make_pair(Setup,setup),std::make_pair(Start,start),std::make_pair(Stop,stop)}){
        *error=Dz1Task_regMsg(task,DZ1_TASK_MSG_EXACT(handler.first),handler.second);
        if(error->code){Dz1Task_del(task);return nullptr;}
    }
    return task;
}
