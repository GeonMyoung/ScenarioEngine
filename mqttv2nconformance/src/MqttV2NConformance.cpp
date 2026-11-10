#include "MqttV2NBridge.h"
#include "NotificationQueue.h"
#include <cstdio>
#include <set>
#include "RestThread.h"
#include "../../interfaceconformance/include/UserLog.h"
#include <MqttV2NConformance.h>
#include <ScenarioEngineWebSockMsg.h>
#include <dz1_asn1.h>

namespace {
std::mutex mqttRegistryMutex;
std::set<void *> mqttRegistry;
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
    void *task=nullptr;
    void *host=nullptr;
    void (*exception)(void *,Dz1Error *)=nullptr;
    void *exceptionArg=nullptr;
    unsigned index=0;
    std::string scenario;
    std::string method;
    std::atomic<bool> mainStarted{false},mainFinished{false};
    bool configured=false;
    std::atomic<bool> stop{false},running{false};
    rest::ManagedThread worker;
    g4mqtt::NotificationQueue notifications;
    void join(){stop=true;if(worker.joinable())worker.join();running=false;}
    void shutdown(){stop=true;notifications.close();if(worker.joinable())worker.join();running=false;}
    ~Context(){shutdown();}
    void state(const std::string &name,const std::string &value){
        if(name=="MainScenario"){if(value=="START")mainStarted=true;if(value=="FINISH")mainFinished=true;}
        Dz1Error e={};
        auto c=ScenarioEngineNotifyStateContext_new(text(name),time(nullptr),text(value),&e);
        if(!c)return;
        auto a=ScenarioEngineNotifyStateArg_gen(&e);
        if(!a){ScenarioEngineNotifyStateContext_del(c);return;}
        a->testIdx=index;a->context=c;
        notifications.post(State,index,a,(Dz1DelFunc)ScenarioEngineNotifyStateArg_del,name=="MainScenario"&&value=="FINISH");
    }
    void info(const std::string &name,const std::string &message,const std::string &type="",const std::string &data="",const std::string &sender="시험 시스템"){
        Dz1Error e={};auto c=ScenarioEngineNotifyInfoContext_gen(&e);if(!c)return;
        auto publicMessage=interface_log::line(message);
        if(interface_log::text(message)!=message){std::ofstream diagnostic("mqttv2n-native-diagnostics.jsonl",std::ios::binary|std::ios::app);diagnostic<<"{\"message\":"<<interface_log::quote(message)<<"}\n";}
        c->time=time(nullptr);c->testName=Dz1Str_clone(text(name),&e);c->sender=systemText(sender,&e);c->log=systemText(publicMessage,&e);
        if(!data.empty()){c->data=Dz1Binary_new(reinterpret_cast<u8_t *>(const_cast<char *>(data.data())),static_cast<u32_t>(data.size()),&e);c->dataType=Dz1Str_clone(text(type),&e);if(e.code||!c->data||!c->dataType){ScenarioEngineNotifyInfoContext_del(c);info(name,"시험 데이터 표시 자료를 전달하지 못했습니다. 별도 송수신 증적을 확인하세요.");return;}}
        auto a=ScenarioEngineNotifyInfoArg_gen(&e);
        if(!a){ScenarioEngineNotifyInfoContext_del(c);return;}
        a->testIdx=index;a->context=c;
        notifications.post(Info,index,a,(Dz1DelFunc)ScenarioEngineNotifyInfoArg_del);
    }
    void run(){
        try{
            mainStarted=false;mainFinished=false;
            g4mqtt::run(scenario,method,stop,[&](const rest::Json &event){
                auto kind=g4mqtt::field(event,"kind"),name=g4mqtt::field(event,"testName");
                if(kind=="state")state(name,g4mqtt::field(event,"value"));
                else if(kind=="info")info(name,g4mqtt::field(event,"log"),"JSON",g4mqtt::field(event,"data"),g4mqtt::field(event,"sender"));
                else throw rest::Failure("알 수 없는 MQTT worker 알림입니다.");
            });
            notifications.flush(stop);
        }catch(const std::exception &e){info("MainScenario",e.what());if(!mainStarted)state("MainScenario","START");if(!mainFinished){state("MainScenario",stop?"STOPPED":"FAIL");state("MainScenario","FINISH");}}
        running=false;
    }
};
Dz1Error init(void **resource,void *self,str_t,unsigned,void *arg,void *){
    *resource=arg;Dz1Task_postSimple(self,DZ1_TASK_QUEUE_NONE,Initial);return Dz1Error{};
}
void cleanup(void *p){if(p)static_cast<Context *>(p)->shutdown();}
void destroy(void *p){auto c=static_cast<Context *>(p);if(c){{std::lock_guard<std::mutex> lock(mqttRegistryMutex);mqttRegistry.erase(c->task);}delete c;}}
void exception(void *arg,void *,void *,Dz1Error *e){auto c=static_cast<Context *>(arg);if(c->exception)c->exception(c->exceptionArg,e);}
Dz1TaskProcStatus initial(void *arg,void *,void *,void **,Dz1Error *e){
    auto c=static_cast<Context *>(arg);c->notifications.start(c->host,c->stop);auto value=systemText(g4mqtt::configureUI(c->scenario),e);
    if(!value)return Dz1TaskProcStatus_error;
    *e=Dz1Task_post(c->host,DZ1_TASK_QUEUE_NONE,UI,(void **)&value,(Dz1DelFunc)Dz1Str_del,nullptr,nullptr,nullptr,nullptr);
    if(e->code)Dz1Str_del(value);return Dz1TaskProcStatus_processed;
}
Dz1TaskProcStatus setup(void *arg,void *,void *,void **message,Dz1Error *e){
    auto c=static_cast<Context *>(arg);
    if(c->running||(c->mainStarted&&!c->notifications.idle())){Dz1Error_set(e,EBUSY);return Dz1TaskProcStatus_processed;}
    try{
        auto raw=static_cast<char *>(Dz1TaskSigMsg_getData(*message));if(!raw)throw rest::Failure("설정 누락");
        auto method=utf8(raw);rest::Json::parse(method);g4mqtt::acceptConfiguration(c->scenario,method,c->index+1);
        if(c->worker.joinable())c->worker.join();
        
        c->method=std::move(method);c->configured=true;++c->index;
        c->info("MainScenario","MQTT 시험 설정을 적용했습니다. 메시지별 입력 토픽·Client ID·컨테이너 설정을 확인하세요.");Dz1Error_set(e,0);
    }catch(const std::exception &error){c->configured=false;try{g4mqtt::invalidateSelection(c->scenario,c->index);}catch(...){}c->info("MainScenario",error.what());Dz1Error_set(e,EINVAL);}
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
    auto c=static_cast<Context *>(arg);if(c->running){c->info("MainScenario","시험 중지를 요청했습니다. 수집한 송수신 기록을 보존합니다.");c->join();}Dz1Error_set(e,0);return Dz1TaskProcStatus_processed;
}
}
extern "C" void *MqttV2NConformance_new(void *host,Dz1Str scenario,void (*onError)(void *,Dz1Error *),void *onErrorArg,Dz1Error *error){
    Dz1Error local={};if(!error)error=&local;
    if(!host||!scenario||!g4mqtt::known(scenario)){Dz1Error_set(error,EINVAL);return nullptr;}
    auto context=new Context;context->host=host;context->scenario=scenario;context->exception=onError;context->exceptionArg=onErrorArg;
    Context *owned=context;
    auto task=Dz1Task_new(text("MqttV2NConformance"),256,(void **)&context,destroy,compare,init,exception,cleanup,error);
    if(!task){delete context;return nullptr;}
    for(auto handler:{std::make_pair(Initial,initial),std::make_pair(Setup,setup),std::make_pair(Start,start),std::make_pair(Stop,stop)}){
        *error=Dz1Task_regMsg(task,DZ1_TASK_MSG_EXACT(handler.first),handler.second);
        if(error->code){Dz1Task_del(task);return nullptr;}
    }
    {std::lock_guard<std::mutex> lock(mqttRegistryMutex);owned->task=task;mqttRegistry.insert(task);}
    return task;
}

extern "C" bool_t MqttV2NConformance_isTask(void *task){std::lock_guard<std::mutex> lock(mqttRegistryMutex);return mqttRegistry.count(task)?TRUE:FALSE;}
