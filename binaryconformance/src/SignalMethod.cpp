#include "../../interfaceconformance/include/UserLog.h"
#include "SignalTransport.h"
#include "SignalMethod.h"
#include "ExtendedCodec.h"
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <set>

namespace signalbinary { namespace {
using rest::Failure;using rest::quote;
unsigned number(const Json &j,const char *name,unsigned fallback,unsigned low,unsigned high){auto p=j.get(name);if(!p||(p->kind==Json::String&&p->text.empty()))return fallback;if((p->kind!=Json::String&&p->kind!=Json::Number)||p->text.empty()||p->text.size()>9||p->text.find_first_not_of("0123456789")!=std::string::npos)throw Failure(std::string(name)+": 정수 설정 오류");auto n=std::stoul(p->text);if(n<low||n>high)throw Failure(std::string(name)+": 설정 범위 오류");return static_cast<unsigned>(n);}
std::string string(const Json &j,const char *name,const std::string &fallback){auto p=j.get(name);if(!p||(p->kind==Json::String&&p->text.empty()))return fallback;if(p->kind!=Json::String||p->text.size()>256||p->text.find_first_of("\r\n\0",0,3)!=std::string::npos)throw Failure(std::string(name)+": 문자열 설정 오류");return p->text;}
bool boolean(const Json &j,const std::string &name,bool fallback=false){auto p=j.get(name);if(!p)return fallback;if(p->kind!=Json::Bool)throw Failure(name+": 선택값 오류");return p->boolean;}
void save(const std::filesystem::path &p,const std::string &s){std::ofstream f(p,std::ios::binary);f<<s;f.close();if(!f)throw Failure("Binary 시험 기록 저장 실패");}
std::string hash(const Bytes &b){return rest::sha256(std::string(b.begin(),b.end()));}
unsigned elapsed(Clock::time_point start){return static_cast<unsigned>(std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count());}
std::string basis(const Config &c,const Item &i){return i.core?(c.provider?"제4부 제4장 4.1.1 정보제공시험 / 접속 후 제공·수신 응답 반복은 채택 절차":"양측 범위에 따른 정보수신 추가 설계 / 제4부 정보제공시험의 상대 역할"):"추가 검증 / 채택한 Binary 운용 기준";}
std::string unobserved(const Config &c){return c.provider?"대상의 원천 자료·실제 변경 발생시각·ACK/NACK 내부 처리 로그는 직접 관측하지 않았습니다.":"수신 응답으로 수용·거부를 확인하며 대상의 내부 업무 반영 로그는 직접 관측하지 않았습니다.";}
struct Evidence {
    const Config &config;const rest::Sink &sink;std::string runId;std::filesystem::path directory;std::ofstream events;unsigned total=0,number=0,dataNumber=0;const Item *item=nullptr;unsigned iteration=0;std::string phase;
    Evidence(const Config &c,const rest::Sink &s,const std::string &id,const std::filesystem::path &d):config(c),sink(s),runId(id),directory(d),events(d/"events.jsonl",std::ios::binary){}
    void event(const std::string &name,const std::string &extra=""){events<<"{\"runId\":"<<quote(runId)<<",\"event\":"<<quote(name)<<",\"monotonicUs\":"<<std::chrono::duration_cast<std::chrono::microseconds>(Clock::now().time_since_epoch()).count();if(item)events<<",\"test\":"<<quote(item->key)<<",\"iteration\":"<<iteration<<",\"phase\":"<<quote(phase);events<<extra<<"}\n";events.flush();if(!events)throw Failure("Binary 시험 이벤트 기록 실패");}
    void log(const std::string &s){if(item&&sink.itemInfo)sink.itemInfo(item->key,s);else if(sink.info)sink.info(s);}
    // Keep each JSON attachment below the observed notification boundary after
    // JSON escaping and SDK base64 encoding, not just before encoding.
    void data(const std::string &message,const std::string &raw,bool partitioned=false){
        if(!sink.itemData)return;auto key=item?item->key:"MainScenario";
        if(raw.size()<=7000||partitioned){sink.itemData(key,message,"JSON",raw);return;}
        ++dataNumber;std::vector<std::string> parts;for(size_t pos=0;pos<raw.size();){auto end=std::min(pos+4096,raw.size());while(end<raw.size()&&(static_cast<unsigned char>(raw[end])&0xc0)==0x80)--end;parts.push_back(raw.substr(pos,end-pos));pos=end;}
        for(size_t i=0;i<parts.size();++i)sink.itemData(key,message+" (분할 "+std::to_string(i+1)+"/"+std::to_string(parts.size())+")","JSON","{\"자료 구분\":\"긴 시험 자료\",\"자료 순번\":"+std::to_string(dataNumber)+",\"회차\":"+std::to_string(iteration)+",\"분할 번호\":"+std::to_string(i+1)+",\"전체 분할 수\":"+std::to_string(parts.size())+",\"분할 데이터\":"+quote(parts[i])+"}");
    }
    void message(const Bytes &raw,bool sending,bool partial=false){
        ++number;++total;std::string kind="정보 프레임",decoded="null",validation="미완성";unsigned msg=raw.empty()?0:raw[0],seq=0;bool ack=raw.size()==5&&raw[1]==0&&raw[2]==5;
        if(ack){kind=raw[4]==1?"ACK":raw[4]==0?"NACK":"잘못된 수신 응답";seq=raw[3];decoded="{\"수신 결과\":"+std::to_string(raw[4])+"}";validation="응답 전문";}
        else if(raw.size()>=5){seq=raw[4];try{auto f=frame(raw,config.profile);if(f.payload.empty()&&(msg==70||msg==71||msg==72)){kind=infoName(msg)+" Heartbeat";decoded="[]";}else if(f.flag==2)decoded=dump(decode(msg,f.payload,config.profile));else kind="분할 정보 프레임";validation="프레임 형식 확인";}catch(const std::exception &e){validation=e.what();}}
        auto detail="{\"메시지 유형\":"+quote(kind)+",\"관측\":"+quote(partial?(sending?"부분 전송":"부분 수신"):(sending?"전송 완료":"수신 완료"))+",\"메시지 번호\":"+std::to_string(msg)+",\"순서 번호\":"+std::to_string(seq)+",\"실제 바이트 수\":"+std::to_string(raw.size())+",\"원문 HEX\":"+quote(hex(raw))+",\"형식 검사\":"+quote(validation)+",\"디코딩 자료\":"+decoded+"}";
        const auto tester=config.provider?config.destination:config.source,target=config.provider?config.source:config.destination;
        const auto sender=sending?tester:target,receiver=sending?target:tester;
        auto prefix="{\"연계정보\":"+quote(infoName(item->message))+",\"회차\":"+std::to_string(iteration)+",\"단계\":"+quote(phase)+",\"메시지 순번\":"+std::to_string(number)+",\"구분\":"+quote(sending?"송신":"수신")+",\"송수신 기준\":\"시험 시스템\",\"발송 주체\":"+quote(sender)+",\"수신 주체\":"+quote(receiver);
        event("message",",\"direction\":"+quote(sending?"send":"receive")+",\"ordinal\":"+std::to_string(number)+",\"partial\":"+(partial?"true":"false")+",\"hex\":"+quote(hex(raw))+",\"sha256\":"+quote(hash(raw)));
        std::ofstream out(directory/("test-data-"+item->key+".jsonl"),std::ios::binary|std::ios::app);
        auto emit=[&](const std::string &value){out<<value<<"\n";data((iteration?std::to_string(iteration)+"회 ":"준비 · ")+phase+" / "+(sending?"송신 ":"수신 ")+kind+" "+std::to_string(raw.size())+"바이트 · "+sender+" → "+receiver,value,true);};
        if(detail.size()<=7000)emit(prefix+",\"상세\":"+detail+"}");else{std::vector<std::string> parts;for(size_t p=0;p<detail.size();){auto end=std::min(p+4096,detail.size());while(end<detail.size()&&(static_cast<unsigned char>(detail[end])&0xc0)==0x80)--end;parts.push_back(detail.substr(p,end-p));p=end;}for(size_t p=0;p<parts.size();++p)emit(prefix+",\"분할 번호\":"+std::to_string(p+1)+",\"전체 분할 수\":"+std::to_string(parts.size())+",\"분할 데이터\":"+quote(parts[p])+"}");}
        out.close();if(!out)throw Failure("Binary 메시지 기록 실패");
    }
    void sent(Channel &c,const Bytes &b,std::atomic<bool> &stop){try{c.send(b,config.timeout,stop,config.writeChunk);message(b,true);}catch(const IoStopped &e){if(!e.partial.empty())message(e.partial,true,true);throw;}catch(const IoFailure &e){if(!e.partial.empty())message(e.partial,true,true);event("transport_failure",",\"direction\":\"send\",\"detail\":"+quote(e.what()));throw;}}
    Bytes received(Channel &c,unsigned timeout,std::atomic<bool> &stop){try{auto b=c.receive(timeout,stop);message(b,false);return b;}catch(const IoStopped &e){if(!e.partial.empty())message(e.partial,false,true);throw;}catch(const IoFailure &e){if(!e.partial.empty())message(e.partial,false,true);event("transport_failure",",\"direction\":\"receive\",\"detail\":"+quote(e.what()));throw;}}
};
void publicAck(const Bytes &raw,unsigned message,unsigned sequence,bool accepted,const Profile &profile,Evidence &e){
    bool ok=true;std::string reason;try{validateAck(raw,message,sequence,accepted,profile);}catch(const std::exception &x){ok=false;reason=x.what();}
    auto actual=raw.size()==5?(raw[4]==1?"수용 (ACK)":raw[4]==0?"거부 (NACK)":"정의되지 않은 응답값"):"응답 형식 불일치";
    auto expectedSequence=profile.ackSequence=="echo"?sequence:1;
    e.data("수신 응답의 기대값·실제값 대조","{\"자료 구분\":\"시험 근거\",\"회차\":"+std::to_string(e.iteration)+",\"기대 응답\":"+quote(accepted?"수용 (ACK)":"거부 (NACK)")+",\"실제 응답\":"+quote(actual)+",\"기대 대응 번호\":"+std::to_string(expectedSequence)+",\"실제 대응 번호\":"+(raw.size()==5?std::to_string(raw[3]):"null")+",\"결과\":"+quote(ok?"확인":"불일치")+"}");
    if(!ok)throw Failure(reason);
}
std::string itemCriterion(const Config &c,const Item &i){
    if(i.mode=="bad_lrc")return "LRC가 잘못된 자료에 대해 대상이 거부 응답(NACK)을 회신해야 합니다.";
    if(i.mode=="bad_payload")return "데이터 길이가 잘못된 자료에 대해 대상이 거부 응답(NACK)을 회신해야 합니다.";
    if(i.mode=="bad_sequence")return "분할 순서번호 오류에 NACK을 회신하고, 올바른 순서번호의 끝 프레임으로 조립을 마친 뒤 같은 연결에서 다음 회차를 진행합니다.";
    if(i.mode=="heartbeat")return "자료 없는 TOD Heartbeat를 "+std::to_string(c.heartbeatPeriod)+"ms 주기, ±"+std::to_string(c.heartbeatTolerance)+"ms 허용오차로 관측합니다. 수신 응답 적용은 합의한 설정을 따릅니다.";
    if(i.mode=="periodic")return "형식·필드 및 수신 응답을 확인하고 "+std::to_string(c.period)+"ms 주기, ±"+std::to_string(c.periodTolerance)+"ms 허용오차를 대조합니다.";
    std::string value=c.provider?"대상이 제공한 형식·필드를 검사한 뒤 시험 시스템이 수용 응답(ACK)을 보냅니다.":"유효 자료를 보낸 뒤 대상의 수용 응답(ACK)과 대응 순서번호를 확인합니다.";
    if(i.mode=="change")value+=" 변경 전후 자료가 달라야 합니다.";
    if(i.mode=="multiple")value+=" 서로 다른 자료 식별값이 2개 이상이어야 합니다.";
    if(i.mode=="split")value+=" 분할 순서와 전체 자료 조립을 확인합니다.";
    if(i.mode=="empty")value="자료 없음 조건에서 데이터 없는 Heartbeat 및 설정한 수신 응답을 확인합니다.";
    return value;
}
Json receiveInformation(Channel &channel,Assembler &assembler,unsigned expected,unsigned minRows,unsigned timeout,Evidence &e,std::atomic<bool> &stop,bool emptyOnly=false){
    auto start=Clock::now();for(unsigned fragments=0;fragments<2;++fragments){auto used=elapsed(start);if(used>=timeout)throw Failure("정보 제공 제한시간 초과");auto raw=e.received(channel,timeout-used,stop);unsigned msg=raw.empty()?expected:raw[0],seq=raw.size()>4?raw[4]:assembler.next;
        try{auto f=frame(raw,e.config.profile);if(f.message!=expected)throw Failure("현재 시험과 다른 메시지 번호가 수신됐습니다.");bool complete=false;auto rows=assembler.accept(f,e.config.profile,complete);if(complete&&(rows.kind!=Json::Array||informationCount(msg,rows)<minRows))throw Failure("정보 레코드 수가 준비 조건보다 적습니다.");if(complete&&minRows>1&&distinctInformationCount(msg,rows)<minRows)throw Failure("복수 정보 시험에는 서로 다른 자료 식별값이 필요합니다.");if(emptyOnly&&(!complete||f.flag!=2||!f.payload.empty()))throw Failure("자료 없음 조건에는 데이터 없는 단독 Heartbeat가 필요합니다.");if(!emptyOnly||e.config.profile.heartbeatAck)e.sent(channel,acknowledgement(msg,seq,true,e.config.profile),stop);if(complete){e.event("information",",\"message\":"+std::to_string(msg)+",\"records\":"+dump(rows)+",\"elapsedMs\":"+std::to_string(elapsed(start)));e.data("프레임 조립과 표준 필드 검사를 완료했습니다.","{\"자료 구분\":\"조립 정보\",\"회차\":"+std::to_string(e.iteration)+",\"연계정보\":"+quote(infoName(msg))+",\"레코드\":"+dump(rows)+"}");return rows;}}
        catch(const rest::Stopped &){throw;}catch(const IoFailure &){throw;}catch(const std::exception &){e.sent(channel,acknowledgement(msg,seq,false,e.config.profile),stop);throw;}
    }throw Failure("분할 정보의 종료가 없습니다.");
}
void sendInformation(Channel &channel,unsigned message,unsigned &seq,const Json &rows,const std::string &mode,Evidence &e,std::atomic<bool> &stop){
    if(mode=="empty"){auto b=packet(message,2,seq,{},e.config.profile);e.sent(channel,b,stop);if(e.config.profile.heartbeatAck)publicAck(e.received(channel,e.config.timeout,stop),message,seq,true,e.config.profile,e);seq=(seq+1)&255;return;}
    auto bytes=encode(message,rows,e.config.profile);std::vector<Bytes> frames;
    if(mode=="split"||mode=="bad_sequence"){
        size_t split=bytes.size()/2;frames.push_back(packet(message,0,seq,Bytes(bytes.begin(),bytes.begin()+split),e.config.profile));seq=(seq+1)&255;
        frames.push_back(packet(message,1,mode=="bad_sequence"?(seq+1)&255:seq,Bytes(bytes.begin()+split,bytes.end()),e.config.profile));seq=(seq+1)&255;
    }else{if(mode=="bad_payload")bytes.pop_back();frames.push_back(packet(message,2,seq,bytes,e.config.profile));seq=(seq+1)&255;if(mode=="bad_lrc")frames.back().back()^=1;}
    for(size_t i=0;i<frames.size();++i){const auto &f=frames[i];bool expected=mode=="bad_sequence"?i==0:(mode!="bad_lrc"&&mode!="bad_payload");e.sent(channel,f,stop);auto response=e.received(channel,e.config.timeout,stop);publicAck(response,message,f[4],expected,e.config.profile,e);e.event("ack_validated",",\"accepted\":"+(expected?std::string("true"):"false")+",\"sequence\":"+std::to_string(f[4]));}
    if(mode=="bad_sequence"){
        auto correctSequence=(seq+255)&255;auto &wrong=frames.back();
        auto corrected=packet(message,1,correctSequence,Bytes(wrong.begin()+5,wrong.end()-1),e.config.profile);
        e.log("순서번호 오류의 거부 응답을 확인했습니다. 같은 연결에서 올바른 끝 프레임으로 현재 정보 조립을 마칩니다.");
        e.event("fragment_recovery");e.sent(channel,corrected,stop);
        publicAck(e.received(channel,e.config.timeout,stop),message,correctSequence,true,e.config.profile,e);
        e.event("fragment_recovered");
    }
}
}
const CaseDef *definition(const std::string &scenario){
    static const CaseDef cases[]={
        {ReceiverCase,0,false,"신호운영시스템","통합교통관제시스템"},{ProviderCase,0,true,"신호운영시스템","통합교통관제시스템"},
        {"signalClient2center_bsm_binary_v1",67,true,"통합교통관제시스템","신호운영시스템"},{"centerServer2signal_bsm_binary_v1",67,false,"통합교통관제시스템","신호운영시스템"},
        {"routeServer2center_binary_v1",71,false,"신호운영시스템","통합교통관제시스템"},{"centerClient2route_binary_v1",71,true,"신호운영시스템","통합교통관제시스템"},
        {"signalClient2center_incident_binary_v1",72,true,"통합교통관제시스템","신호운영시스템"},{"centerServer2signal_incident_binary_v1",72,false,"통합교통관제시스템","신호운영시스템"}};
    for(auto &c:cases)if(scenario==c.id)return &c;return nullptr;
}
std::vector<Item> items(const std::string &scenario){
    auto d=definition(scenario);if(!d)throw Failure("지원하지 않는 Binary 시험");if(!d->message)return items(d->provider);
    std::string role=d->provider?d->source:d->destination,verb=d->provider?"제공":"수신",name=infoName(d->message),base=std::string(d->provider?"test_provide_":"test_receive_")+(d->message==67?"bsm":d->message==71?"route":"incident");
    std::vector<Item> out={{base,role+" "+name+" "+verb+"시험","normal",d->message,true}};
    if(d->message==67)out.push_back({base+"_periodic",role+" [추가] 차량운행정보 1초 주기 "+verb+"시험","periodic",67});
    else out.push_back({base+"_change",role+" [추가] 사건에 따른 "+name+" 변경 "+verb+"시험","change",d->message});
    out.push_back({base+"_split",role+" [추가] "+name+" 분할 "+verb+"시험","split",d->message});out.push_back({base+"_multiple",role+" [추가] 복수 "+name+" "+verb+"시험","multiple",d->message});
    if(d->message!=67)out.push_back({base+"_empty",role+" [추가] "+name+" 자료 없음 Heartbeat "+verb+"시험","empty",d->message});
    if(!d->provider)for(auto mode:{"bad_lrc","bad_payload","bad_sequence"})out.push_back({base+"_reject_"+mode,role+" [추가] "+name+" "+(std::string(mode)=="bad_lrc"?"LRC":std::string(mode)=="bad_payload"?"데이터 길이":"순서번호")+" 오류 거부시험",mode,d->message});return out;
}
std::vector<Item> items(bool provider){
    std::string role=provider?"신호운영시스템":"통합교통관제시스템",verb=provider?"제공":"수신",prefix=provider?"test_provide_":"test_receive_";
    std::vector<Item> out={{prefix+"all_status",role+" 전체 교차로 상태 정보"+verb+"시험","normal",68,true},{prefix+"alter_status",role+" 변경 교차로 상태 정보"+verb+"시험","change",69,true},{prefix+"tod",role+" 교차로 TOD 정보"+verb+"시험","normal",70,true},{prefix+"split_status",role+" [추가] 분할 교차로 상태 정보"+verb+"시험","split",68},{prefix+"multiple_status",role+" [추가] 복수 교차로 상태 정보"+verb+"시험","multiple",68},{prefix+"tod_heartbeat",role+" [추가] TOD Heartbeat "+verb+"시험","heartbeat",70}};
    if(!provider){out.push_back({"test_reject_bad_lrc",role+" [추가] LRC 오류정보 거부시험","bad_lrc",68});out.push_back({"test_reject_bad_payload",role+" [추가] 데이터 길이 오류정보 거부시험","bad_payload",68});out.push_back({"test_reject_bad_sequence",role+" [추가] 순서번호 오류정보 거부시험","bad_sequence",68});}return out;
}
Config Config::parse(const std::string &scenario,const std::string &raw){
    auto d=definition(scenario);if(!d)throw Failure("지원하지 않는 TCP Binary 시험");auto j=Json::parse(raw);if(j.kind!=Json::Object)throw Failure("시험 설정은 객체여야 합니다.");Config c;c.scenario=scenario;c.provider=d->provider;c.message=d->message;c.source=d->source;c.destination=d->destination;c.raw=raw;
    c.ip=string(j,c.provider?"sut_ip":"bind_ip","127.0.0.1");c.port=number(j,"tcp_port",c.provider?55435:55414,1,65535);c.repetitions=number(j,"repetitions",10,10,1000);c.timeout=number(j,"socket_timeout_ms",5000,100,300000);c.initialLimit=number(j,"initial_limit_ms",1000,100,300000);c.firstSequence=number(j,"first_sequence",0,0,255);c.heartbeatPeriod=number(j,"heartbeat_period_ms",60000,20,600000);c.heartbeatTolerance=number(j,"heartbeat_tolerance_ms",1000,1,30000);c.heartbeatSamples=number(j,"heartbeat_samples",2,2,10);c.changeDelay=number(j,"change_delay_ms",1000,0,10000);c.writeChunk=number(j,"tcp_write_chunk_bytes",0,0,65535);
    c.period=number(j,"period_ms",1000,20,600000);c.periodTolerance=number(j,"period_tolerance_ms",200,1,30000);if(c.periodTolerance>=c.period)throw Failure("주기 허용오차는 검사 주기보다 작아야 합니다.");
    c.profile.checksum=string(j,"lrc_mode","xor8");c.profile.ackSequence=string(j,"ack_seq_mode","echo");c.profile.encoding=string(j,"char_encoding","UTF-8");c.profile.heartbeatAck=boolean(j,"heartbeat_ack",true);
    if(c.profile.checksum!="xor8"&&c.profile.checksum!="sum8")throw Failure("LRC 방식은 xor8 또는 sum8을 선택하세요.");if(c.profile.ackSequence!="echo"&&c.profile.ackSequence!="fixed1")throw Failure("ACK 순서번호는 echo 또는 fixed1을 선택하세요.");if(c.profile.encoding!="UTF-8"&&c.profile.encoding!="CP949")throw Failure("문자 인코딩은 UTF-8 또는 CP949를 선택하세요.");
    if(c.heartbeatTolerance>=c.heartbeatPeriod)throw Failure("Heartbeat 허용오차는 검사 주기보다 작아야 합니다.");for(auto &i:items(c.scenario))if(boolean(j,i.key))c.selected.push_back(i);if(c.selected.empty())throw Failure("시험 항목을 하나 이상 선택하세요.");return c;
}
std::string effectiveConfiguration(const Config &c){
    auto j=Json::parse(c.raw);
    auto text=[&](const std::string &k,const std::string &v){j.object[k]=Json::parse(quote(v));};
    auto number=[&](const std::string &k,unsigned v){j.object[k]=Json::parse(std::to_string(v));};
    text(c.provider?"sut_ip":"bind_ip",c.ip);text("lrc_mode",c.profile.checksum);text("ack_seq_mode",c.profile.ackSequence);text("char_encoding",c.profile.encoding);
    number("tcp_port",c.port);number("repetitions",c.repetitions);number("socket_timeout_ms",c.timeout);number("initial_limit_ms",c.initialLimit);number("first_sequence",c.firstSequence);
    number("heartbeat_period_ms",c.heartbeatPeriod);number("heartbeat_tolerance_ms",c.heartbeatTolerance);number("heartbeat_samples",c.heartbeatSamples);number("change_delay_ms",c.changeDelay);number("tcp_write_chunk_bytes",c.writeChunk);number("period_ms",c.period);number("period_tolerance_ms",c.periodTolerance);
    j.object["heartbeat_ack"]=Json::parse(c.profile.heartbeatAck?"true":"false");
    for(auto &item:items(c.scenario))j.object[item.key]=Json::parse(std::any_of(c.selected.begin(),c.selected.end(),[&](const auto &v){return v.key==item.key;})?"true":"false");
    return dump(j);
}
namespace {
void acceptedFile(const std::string &data){
    auto path=std::filesystem::current_path()/"binary-selection.json",tmp=std::filesystem::current_path()/"binary-selection.json.tmp";save(tmp,data);
    if(!MoveFileExW(tmp.c_str(),path.c_str(),MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH))throw Failure("적용 설정 기록을 저장하지 못했습니다.");
}
}
void saveAcceptedConfiguration(const Config &c,unsigned index){
    std::string tests="[";for(auto &item:c.selected){if(tests.size()>1)tests+=",";tests+=quote(item.key);}tests+="]";
    acceptedFile("{\"schemaVersion\":1,\"valid\":true,\"processId\":"+std::to_string(GetCurrentProcessId())+",\"testIdx\":"+std::to_string(index)+",\"case\":"+quote(c.scenario)+",\"tests\":"+tests+",\"configuration\":"+c.raw+",\"effectiveConfiguration\":"+effectiveConfiguration(c)+"}");
}
void invalidateAcceptedConfiguration(const std::string &scenario){acceptedFile("{\"schemaVersion\":1,\"valid\":false,\"processId\":"+std::to_string(GetCurrentProcessId())+",\"case\":"+quote(scenario)+"}");}
std::string configureUI(const std::string &scenario){
    auto def=definition(scenario);if(!def)throw Failure("지원하지 않는 Binary 시험");bool provider=def->provider;Json ui=Json::parse(R"JSON({"scenarios":[],"configuration":[{"type":"Div","option":{"direction":"col"},"components":[]}]})JSON");auto &groups=ui.object["configuration"].array[0].object["components"].array;
    auto group=[&](const std::string &label){groups.push_back(Json::parse("{\"type\":\"FieldSet\",\"option\":{\"label\":"+quote(label)+"},\"components\":[]}"));};
    auto input=[&](const std::string &name,const std::string &label,const std::string &value,const std::string &type="text"){auto s="{\"type\":\"Input\",\"option\":{\"name\":"+quote(name)+",\"label\":"+quote(label)+",\"type\":"+quote(type);if(type!="checkbox")s+=",\"value\":"+quote(value);s+="}}";groups.back().object["components"].array.push_back(Json::parse(s));};
    group(std::string(provider?"시험 대상 ":"시험 시스템 ")+def->source+" TCP 서버 접점");input(provider?"sut_ip":"bind_ip",provider?"대상 서버 IPv4 주소":"수신 대기 IPv4 주소","127.0.0.1");input("tcp_port","TCP 포트",provider?"55435":"55414","number");input("repetitions","정보교환 반복 횟수 (최소 10)","10","number");input("socket_timeout_ms","접속·수신 응답 제한시간 (ms)","5000","number");input("initial_limit_ms","접속 후 최초 정보 수신 제한시간 (ms, 기준 1000)","1000","number");
    group("상대 시스템과 맞출 운용 기준 (미정 규칙의 개발 설정)");input("lrc_mode","LRC 계산 (xor8 / sum8)","xor8");input("ack_seq_mode","ACK 순서번호 (echo / fixed1)","echo");input("char_encoding","고정 문자열 인코딩 (UTF-8 / CP949)","UTF-8");input("first_sequence","연결 시작 순서번호 (0~255)","0","number");if(def->message!=67)input("heartbeat_ack","자료 없는 Heartbeat에도 수신 응답을 사용합니다","","checkbox");
    if(!def->message){group("TOD Heartbeat 및 변경 사건 조건");input("heartbeat_period_ms","Heartbeat 주기 (ms, 설계서 기준 60000)","60000","number");input("heartbeat_tolerance_ms","Heartbeat 측정 허용오차 (ms, 시험 환경값)","1000","number");input("heartbeat_samples","Heartbeat 확인 횟수 (최소 2)","2","number");}
    if(def->message==67){group("차량운행정보 제공 주기");input("period_ms","정보 제공 주기 (ms, 표준 기준 1000)","1000","number");input("period_tolerance_ms","주기 측정 허용오차 (ms, 시험 환경값)","200","number");}
    else{if(def->message)group("사건 발생 조건");input("change_delay_ms","시험 시스템의 변경 사건 대기시간 (ms)","1000","number");}
    for(bool core:{true,false}){group(core?"정보교환 확인":"추가 운용 검증");for(auto &i:items(scenario))if(i.core==core){input(i.key,i.title,"","checkbox");ui.object["scenarios"].array.push_back(Json::parse("{\"key\":"+quote(i.key)+",\"title\":"+quote(i.title)+"}"));}}
    return dump(ui);
}
Result run(const Config &c,std::atomic<bool> &stop,const rest::Sink &sink){
    // Keep the full run identity in records, without repeating a long case name
    // in paths beneath a portable launcher's per-session directory.
    Result result;result.runId=std::to_string(std::chrono::system_clock::now().time_since_epoch().count())+"-"+c.scenario;auto dir=std::filesystem::current_path()/"binary-results"/rest::sha256(result.runId).substr(0,24);std::filesystem::create_directories(dir);result.path=(dir/"result.json").u8string();Evidence e(c,sink,result.runId,dir);SocketRuntime network;
    save(dir/"config.json",c.raw);save(std::filesystem::current_path()/"binary-run.json","{\"runId\":"+quote(result.runId)+",\"case\":"+quote(c.scenario)+",\"configSha256\":"+quote(rest::sha256(c.raw))+"}");
    if(sink.state)sink.state("MainScenario","START");e.log(std::string("시험 대상: ")+(c.provider?c.source+"(TCP Server)":c.destination+"(TCP Client)")+". 데이터는 표준의 바이트 폭, 통신은 경6 설계서 및 표시한 개발 기준으로 확인합니다.");e.log(std::string("적용 기준: Big-Endian, ")+(c.message==67?"BSM 64바이트 레코드·IEEE 754 부동소수. ":c.message==71?"표준의 가변 차량/경유 구조·20바이트 경유순번. 큰 정수는 손실 없는 10진 문자열로 표시합니다. ":c.message==72?"표준 돌발상황 필드·가변 통제 링크. ":"상태 교차로번호 1바이트, TOD 교차로번호 4바이트. ")+"LRC="+c.profile.checksum+", ACK 순서번호="+c.profile.ackSequence+", CHAR="+c.profile.encoding+". 미정 운용 규칙을 공식 명세로 확정한 결과가 아닙니다.");
    Channel listener;bool aborted=false;Json summaries;summaries.kind=Json::Array;
    try{if(!c.provider){listener=Channel::listen(c.ip,c.port);e.event("listening",",\"port\":"+std::to_string(c.port));if(sink.diagnostic)sink.diagnostic("LISTENING");}}catch(const std::exception &x){aborted=true;result.detail=x.what();}
    for(auto &item:c.selected){
        e.item=&item;e.number=0;e.iteration=0;e.phase="준비";
        unsigned completed=0,wanted=item.mode=="heartbeat"?c.heartbeatSamples:c.repetitions,connections=0;
        bool sessionClosed=false;Channel channel;
        std::string verdict="NOT_RUN",reason="이전 항목 중단으로 미실행";
        if(!aborted){
            if(sink.state)sink.state(item.key,"START");
            e.data("시험 안내: "+item.title,interface_log::guide(item.title,c.provider?c.source:c.destination,
                "한 번 접속·자료 준비 → 같은 연결에서 설정 횟수만큼 정보와 수신 응답 교환 → 세션 정리 → 판정",
                basis(c,item)+" · "+itemCriterion(c,item)+" · 계획 "+std::to_string(wanted)+"회 · 기대 정보 "+infoName(item.message),unobserved(c)));
            e.log(item.title+". "+basis(c,item)+". "+unobserved(c));
            try{
                e.event("item_start",",\"requested\":"+std::to_string(wanted));
                e.phase="접속 준비";
                e.log(c.provider?"대상 서버에 한 번 접속한 뒤 같은 연결에서 정보를 받습니다.":"대상의 TCP 접속을 한 번 수락한 뒤 같은 연결에서 정보를 제공합니다.");
                channel=c.provider?Channel::connect(c.ip,c.port,c.timeout,stop):listener.accept(c.timeout,stop);
                connections=1;e.event("connected");unsigned seq=c.firstSequence;Assembler assembler(seq);
                e.log("연결됐습니다. 별도 정보조회 요청 전문이 없는 연계이므로 데이터 제공 측이 전송을 시작하고, 명세의 수신 응답을 교환합니다.");
                if(item.mode=="periodic"){
                    auto last=Clock::now(),due=last;
                    e.log("차량운행정보 "+std::to_string(c.period)+"ms 주기로 "+std::to_string(wanted)+"회 확인합니다. 1000ms 이외의 값은 개발 시간 조건입니다.");
                    for(unsigned n=1;n<=wanted;++n){
                        e.iteration=n;e.phase="주기 정보교환";unsigned actual=0;
                        if(c.provider){receiveInformation(channel,assembler,67,1,n==1?c.initialLimit:c.period+c.periodTolerance+c.timeout,e,stop);actual=elapsed(last);last=Clock::now();}
                        else{if(n>1){due+=std::chrono::milliseconds(c.period);pauseUntil(due,stop);}auto instant=Clock::now();actual=elapsed(last);sendInformation(channel,67,seq,fixture(67,n),"normal",e,stop);last=instant;}
                        if(n>1){if(actual+c.periodTolerance<c.period||actual>c.period+c.periodTolerance)throw Failure("차량운행정보 간격이 설정한 주기·허용오차를 벗어났습니다.");e.event("period_validated",",\"intervalMs\":"+std::to_string(actual));}
                        ++completed;++result.exchanges;e.event("exchange_complete");
                        e.log(std::to_string(n)+"/"+std::to_string(wanted)+"회 정보와 수신 응답 교환을 완료했습니다.");
                    }
                }else if(item.mode=="heartbeat"){
                    e.phase="최초 TOD 준비";
                    if(c.provider)receiveInformation(channel,assembler,70,1,c.initialLimit,e,stop);else sendInformation(channel,70,seq,fixture(70),"normal",e,stop);
                    e.log("TOD 제공 후 같은 연결에서 Heartbeat "+std::to_string(c.heartbeatPeriod)+"ms 주기를 "+std::to_string(wanted)+"회 확인합니다. 60000ms 이외의 값은 변경된 개발 시간 조건입니다.");
                    auto last=Clock::now(),due=last;
                    for(unsigned n=1;n<=wanted;++n){
                        e.iteration=n;e.phase="Heartbeat";unsigned actual=0;
                        if(c.provider){auto raw=e.received(channel,c.heartbeatPeriod+c.heartbeatTolerance+c.timeout,stop);actual=elapsed(last);last=Clock::now();auto f=frame(raw,c.profile);bool done=false;auto rows=assembler.accept(f,c.profile,done);if(f.message!=70||f.flag!=2||!f.payload.empty()||!done||!rows.array.empty())throw Failure("TOD Heartbeat는 데이터 없는 단독 프레임이어야 합니다.");if(c.profile.heartbeatAck)e.sent(channel,acknowledgement(70,f.sequence,true,c.profile),stop);}
                        else{due+=std::chrono::milliseconds(c.heartbeatPeriod);pauseUntil(due,stop);auto raw=packet(70,2,seq,{},c.profile);actual=elapsed(last);e.sent(channel,raw,stop);last=Clock::now();if(c.profile.heartbeatAck)publicAck(e.received(channel,c.timeout,stop),70,seq,true,c.profile,e);seq=(seq+1)&255;}
                        if(actual+c.heartbeatTolerance<c.heartbeatPeriod||actual>c.heartbeatPeriod+c.heartbeatTolerance)throw Failure("TOD Heartbeat 간격이 설정한 주기·허용오차를 벗어났습니다.");
                        e.event("heartbeat_validated",",\"intervalMs\":"+std::to_string(actual));++completed;++result.exchanges;e.event("exchange_complete");
                        e.log(std::to_string(n)+"/"+std::to_string(wanted)+"회 Heartbeat 교환을 완료했습니다. 관측 간격 "+std::to_string(actual)+"ms.");
                    }
                }else{
                    Json baseline;
                    if(item.mode=="change"){
                        unsigned baselineMessage=item.message==69?68:item.message;e.phase="변경 전 정보 준비";
                        if(c.provider)baseline=receiveInformation(channel,assembler,baselineMessage,1,c.initialLimit,e,stop);
                        else{baseline=fixture(baselineMessage);sendInformation(channel,baselineMessage,seq,baseline,"normal",e,stop);}
                        e.log("변경 전 정보를 준비했습니다. 이 준비 교환은 반복 횟수에 포함하지 않습니다.");
                    }
                    for(unsigned n=1;n<=wanted;++n){
                        if(stop)throw rest::Stopped();e.iteration=n;e.phase="정보교환";
                        e.log(std::to_string(n)+"/"+std::to_string(wanted)+"회: 연결을 유지하며 "+(c.provider?"대상 제공 정보와 수신 응답을 교환합니다.":"정보를 제공하고 대상의 수신 응답을 확인합니다."));
                        if(item.mode=="change"){
                            e.phase="변경 상태";
                            if(!c.provider)pauseUntil(Clock::now()+std::chrono::milliseconds(c.changeDelay),stop);
                            e.event("change_condition");
                        }
                        if(c.provider){
                            auto before=assembler.next;
                            auto rows=receiveInformation(channel,assembler,item.message,item.mode=="empty"?0:item.mode=="multiple"?2:1,
                                n==1&&item.mode!="change"?c.initialLimit:c.timeout,e,stop,item.mode=="empty");
                            if(item.mode=="change"){if(dump(rows)==dump(baseline))throw Failure("변경 정보가 직전에 받은 정보와 같습니다.");baseline=rows;}
                            if(item.mode=="split"&&assembler.next!=((before+2)&255))throw Failure("두 프레임 분할 제공 조건이 확인되지 않았습니다.");
                        }else sendInformation(channel,item.message,seq,fixture(item.message,item.mode=="change"?n:0,item.mode=="multiple"?2:1),item.mode,e,stop);
                        e.event("exchange_complete");++completed;++result.exchanges;
                    }
                }
                verdict="SUCCESS";reason="한 연결에서 설정 횟수의 정보·수신 응답 교환과 자동 검사를 완료했습니다. "+unobserved(c);
            }catch(const rest::Stopped &x){verdict="STOPPED";reason=x.what();aborted=true;result.verdict=verdict;result.detail=reason;}
            catch(const std::exception &x){verdict="FAIL";reason=x.what();aborted=true;result.verdict=verdict;result.detail=reason;}
            if(connections){
                channel.shutdown();channel.close();sessionClosed=true;e.phase="세션 정리";
                e.event("session_closed",",\"completed\":"+std::to_string(completed)+",\"verdict\":"+quote(verdict));
                e.log(std::string(verdict=="SUCCESS"?"설정한 교환을 마쳐":"시험이 중단되어")+" TCP 세션을 정리했습니다. 완료 "+std::to_string(completed)+"/"+std::to_string(wanted)+"회.");
            }
        }
        Json row=Json::parse("{\"test\":"+quote(item.key)+",\"title\":"+quote(item.title)+",\"mode\":"+quote(item.mode)+",\"message\":"+std::to_string(item.message)+",\"basis\":"+quote(basis(c,item))+",\"verdict\":"+quote(verdict)+",\"requestedExchanges\":"+std::to_string(wanted)+",\"completedExchanges\":"+std::to_string(completed)+",\"connections\":"+std::to_string(connections)+",\"sessionClosed\":"+(sessionClosed?"true":"false")+",\"messageCount\":"+std::to_string(e.number)+",\"detail\":"+quote(reason)+"}");
        summaries.array.push_back(row);e.event("item_result",",\"verdict\":"+quote(verdict)+",\"completed\":"+std::to_string(completed));
        e.data(verdict=="SUCCESS"?"자동 관측 검사 완료":verdict=="NOT_RUN"?"미실행":"시험 중단: "+reason,
            "{\"자료 구분\":\"Binary 시험 결과\",\"최종 판정\":"+quote(verdict)+",\"계획한 교환\":"+std::to_string(wanted)+",\"완료한 교환\":"+std::to_string(completed)+",\"접속 횟수\":"+std::to_string(connections)+",\"세션 정리\":"+quote(sessionClosed?"완료":"연결 전")+",\"메시지 수\":"+std::to_string(e.number)+",\"판정 범위\":\"엔진 자동 관측 범위\",\"직접 관측하지 않은 내용\":"+quote(unobserved(c))+",\"설명\":"+quote(reason)+"}");
        if(verdict!="NOT_RUN"&&sink.state)sink.state(item.key,verdict);
    }
    e.item=nullptr;if(!aborted){result.verdict="SUCCESS";result.detail="선택 항목의 TCP Binary 자동 검증을 완료했습니다.";}result.messages=e.total;
    bool hasHeartbeat=std::any_of(c.selected.begin(),c.selected.end(),[](const Item &i){return i.mode=="heartbeat";});bool hasPeriodic=std::any_of(c.selected.begin(),c.selected.end(),[](const Item &i){return i.mode=="periodic";});
    auto report="{\"schemaVersion\":2,\"sessionPolicy\":\"single_connection_per_item\",\"exchangeInitiation\":\"provider_push\",\"profile\":"+quote(c.message?"BINARY-TRAFFIC-001":"BINARY-SIGNAL-001")+",\"assessmentScope\":\"ENGINE_OBSERVABLE\",\"case\":"+quote(c.scenario)+",\"runId\":"+quote(result.runId)+",\"configSha256\":"+quote(rest::sha256(c.raw))+",\"sutRole\":"+quote(c.provider?"provider":"receiver")+",\"automaticVerdict\":"+quote(result.verdict)+",\"completedExchanges\":"+std::to_string(result.exchanges)+",\"messages\":"+std::to_string(result.messages)+",\"periodMs\":"+std::to_string(c.period)+",\"standardPeriodicTiming\":"+(hasPeriodic?(c.period==1000?"true":"false"):"null")+",\"heartbeatPeriodMs\":"+std::to_string(c.heartbeatPeriod)+",\"standardHeartbeatTiming\":"+(hasHeartbeat?(c.heartbeatPeriod==60000?"true":"false"):"null")+",\"items\":"+dump(summaries)+"}";save(dir/"result.json",report);e.event("result",",\"verdict\":"+quote(result.verdict));e.log(result.detail+" 총 "+std::to_string(result.exchanges)+"회 교환, 송수신 "+std::to_string(result.messages)+"개 프레임을 기록했습니다.");if(sink.state){sink.state("MainScenario",result.verdict);sink.state("MainScenario","FINISH");}return result;
}
}
