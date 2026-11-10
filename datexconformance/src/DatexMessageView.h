#pragma once
#include "DatexDataView.h"

namespace datex {
namespace message_view {
inline std::string object(std::initializer_list<std::pair<std::string,std::string>> fields) {
    std::string out="{";
    for(const auto &field:fields){if(out.size()>1)out+=',';out+=quote(field.first)+":"+field.second;}
    return out+"}";
}
template<class T> std::string number(T value){return std::to_string(value);}
template<class T> std::string optional(T *value){return value?number(*value):"null";}
inline std::string boolean(bool value){return value?"true":"false";}
inline bool validUtf8(const std::string &s) {
    for(size_t i=0;i<s.size();){unsigned c=static_cast<unsigned char>(s[i++]);
        if(c<128)continue;
        unsigned extra,cp,minimum;
        if(c>=0xc2 && c<=0xdf){extra=1;cp=c&31;minimum=0x80;}
        else if(c>=0xe0 && c<=0xef){extra=2;cp=c&15;minimum=0x800;}
        else if(c>=0xf0 && c<=0xf4){extra=3;cp=c&7;minimum=0x10000;}else return false;
        if(i+extra>s.size())return false;
        while(extra--){unsigned b=static_cast<unsigned char>(s[i++]);if((b&0xc0)!=0x80)return false;cp=(cp<<6)|(b&63);}
        if(cp<minimum || cp>0x10ffff || (cp>=0xd800 && cp<=0xdfff))return false;
    }return true;
}
inline std::string text(Dz1Asn1UTF8Str *value){
    if(!value)return "null";
    auto s=utf8Text(value);
    if(validUtf8(s))return quote(s);
    return object({{"표현",quote("잘못된 UTF-8: 전체 바이트 표시")},{"hex",quote(dataHex(Bytes(s.begin(),s.end())))}});
}
inline std::string compact(const std::string &value) {
    std::string out;bool inString=false,escape=false;
    for(char c:value){
        if(inString){out+=c;if(escape)escape=false;else if(c=='\\')escape=true;else if(c=='"')inString=false;}
        else if(c!=' ' && c!='\r' && c!='\n' && c!='\t'){out+=c;if(c=='"')inString=true;}
    }return out;
}
inline std::string decodedData(const std::string &value) {
    if(value.empty())return "null";
    try { if(!validUtf8(value))throw Failure("UTF-8"); Json::parseData(value);return compact(value); }
    catch(const Failure &){return object({{"표시 안내",quote("디코딩 자료를 JSON으로 표시하지 못해 전체 UTF-8 바이트를 보관합니다.")},{"hex",quote(dataHex(Bytes(value.begin(),value.end())))}});}

}
template<class T> std::string binary(T *value){
    if(!value)return "null";
    Bytes bytes=value->size?Bytes(value->data,value->data+value->size):Bytes{};
    const bool printable=std::all_of(bytes.begin(),bytes.end(),[](unsigned char c){return c>=32 && c<127;});
    return object({{"hex",quote(dataHex(bytes))},{"bytes",number(value->size)},
        {"text",printable?quote(std::string(bytes.begin(),bytes.end())):"null"}});
}
inline std::string oid(Dz1Asn1OID *value){return value?quote(oidText(value)):"null";}
template<class E> std::string enumeration(E value,const char *name){return object({{"code",number(static_cast<int>(value))},{"name",name?quote(name):"null"}});}
#define DATEX_ENUM(type,value) enumeration(value,type##StrA(value))
inline std::string time(Iso14827Time *v) {
    if(!v)return "null";
    std::string frac="null";
    if(v->frac){auto f=v->frac;switch(f->present){
    case Iso14827TimeFracPresent_deci:frac=object({{"deci",number(f->x.deci)}});break;
    case Iso14827TimeFracPresent_centi:frac=object({{"centi",number(f->x.centi)}});break;
    case Iso14827TimeFracPresent_milli:frac=object({{"milli",number(f->x.milli)}});break;
    default:break;}}
    return object({{"year",optional(v->year)},{"month",optional(v->month)},{"day",optional(v->day)},
        {"hour",number(v->h)},{"minute",number(v->m)},{"second",number(v->s)},{"fraction",frac},
        {"zone",v->zone?object({{"modH",number(v->zone->modH)},{"modM",number(v->zone->modM)}}):"null"}});
}
inline std::string header(Iso14827HdrOpt *v) {
    if(!v)return "null";
    return object({{"origin",text(v->origin)},{"originAddr",binary(v->originAddr)},
        {"sender",text(v->sender)},{"senderAddr",binary(v->senderAddr)},{"dest",text(v->dest)},{"destAddr",binary(v->destAddr)},
        {"time",time(v->t)},{"cost",v->cost?object({{"currency",binary(v->cost->currency)},
        {"factor",number(v->cost->factor)},{"qty",number(v->cost->qty)}}):"null"}});
}
inline std::string registration(Iso14827Registered *v) {
    if(!v)return "null";
    if(v->present==Iso14827RegisteredPresent_continuous && v->x.continuous){auto c=v->x.continuous;return object({{"continuous",object({{"updateDelay",number(c->updateDelay)},{"start",time(c->start)},{"end",time(c->end)}})}});}
    if(v->present==Iso14827RegisteredPresent_daily && v->x.daily){auto d=v->x.daily;return object({{"daily",object({{"updateDelay",number(d->updateDelay)},{"daysOfWeek",number(d->daysOfWeek)},{"startDate",time(d->startDate)},{"endDate",time(d->endDate)},{"startTime",time(d->startTime)},{"duration",optional(d->duration)}})}});}
    return "null";
}
inline std::string mode(Iso14827SubscriptionDataMode *v){
    if(!v)return "null";
    switch(v->present){
    case Iso14827SubscriptionDataModePresent_single:return object({{"single",optional(v->x.single)}});
    case Iso14827SubscriptionDataModePresent_eventDriven:return object({{"eventDriven",registration(v->x.eventDriven)}});
    case Iso14827SubscriptionDataModePresent_periodic:return object({{"periodic",registration(v->x.periodic)}});
    default:return "null";}
}
inline std::string endMessage(Iso14827EndAppMsg *v){return v?object({{"oid",oid(v->oid)},{"data",binary(v->data)}}):"null";}
inline std::string subscription(Iso14827SubscriptionType *v){
    if(!v)return "null";
    if(v->present==Iso14827SubscriptionTypePresent_reason)return object({{"cancelReason",DATEX_ENUM(Iso14827SubscriptionCancel,v->x.reason)}});
    if(v->present!=Iso14827SubscriptionTypePresent_data || !v->x.data)return "null";
    auto d=v->x.data;
    return object({{"data",object({{"persistent",boolean(d->persistent)},{"status",DATEX_ENUM(Iso14827SubscriptionDataStatus,d->status)},
        {"mode",mode(d->mode)},{"format",DATEX_ENUM(Iso14827SubscriptionDataFormat,d->fmt)},{"priority",number(d->priority)},
        {"guarantee",boolean(d->guarantee)},{"message",endMessage(d->msg)}})}});
}
inline std::string publication(Iso14827Publication *v){
    if(!v)return "null";
    std::string format="null";
    if(v->fmt && v->fmt->present==Iso14827PublishFormatPresent_filename)format=object({{"filename",text(v->fmt->x.filename)}});
    else if(v->fmt && v->fmt->present==Iso14827PublishFormatPresent_dataList && v->fmt->x.dataList){
        unsigned n=0;Dz1Error err={};auto rows=v->fmt->x.dataList->get_array(v->fmt->x.dataList,&n,&err);
        std::string data="[";
        for(unsigned i=0;i<n && rows;++i){auto d=rows[i];if(i)data+=',';
            std::string content="null";
            if(d->type){if(d->type->present==Iso14827PublicationTypePresent_msg)content=object({{"message",endMessage(d->type->x.msg)}});
                else if(d->type->present==Iso14827PublicationTypePresent_mgmt)content=object({{"management",DATEX_ENUM(Iso14827PublicationMgmt,d->type->x.mgmt)}});}
            data+=object({{"subscriptionSerial",number(d->subscriptionSerial)},{"publicationSerial",number(d->serial)},{"isLated",boolean(d->isLated)},{"content",content}});
        }
        Dz1Free(rows);format=object({{"dataList",data+"]"}});
    }
    return object({{"guaranteed",boolean(v->guaranteed)},{"format",format}});
}
inline std::string accept(Iso14827Accept *v){
    if(!v)return "null";
    std::string type="null";
    if(v->acceptType){auto t=v->acceptType;switch(t->present){
    case Iso14827AcceptTypePresent_login:type=object({{"loginCodec",oid(t->x.login)}});break;
    case Iso14827AcceptTypePresent_singleSubscription:type=object({{"singleSubscription",optional(t->x.singleSubscription)}});break;
    case Iso14827AcceptTypePresent_registeredSubscription:type=object({{"registeredSubscription",number(t->x.registeredSubscription)}});break;
    case Iso14827AcceptTypePresent_publication:type=object({{"publication",optional(t->x.publication)}});break;
    default:break;}}
    return object({{"acknowledgedPacketNumber",number(v->pktNbr)},{"acceptType",type}});
}
inline std::string reject(Iso14827Reject *v){
    if(!v)return "null";
    std::string reason="null";
    if(v->type){auto t=v->type;switch(t->present){
    case Iso14827RejectTypePresent_login:reason=object({{"login",DATEX_ENUM(Iso14827RejectLogin,t->x.login)}});break;
    case Iso14827RejectTypePresent_subscription:reason=object({{"subscription",DATEX_ENUM(Iso14827RejectSubscription,t->x.subscription)}});break;
    case Iso14827RejectTypePresent_publication:reason=object({{"publication",DATEX_ENUM(Iso14827RejectPublication,t->x.publication)}});break;
    case Iso14827RejectTypePresent_pubData:if(t->x.pubData){auto d=t->x.pubData;reason=object({{"publicationData",object({{"subscriptionSerial",number(d->subSerial)},{"publicationSerial",number(d->pubSerial)},{"reason",DATEX_ENUM(Iso14827RejectPubDataReason,d->reason)}})}});}break;
    default:break;}}
    return object({{"rejectedPacketNumber",number(v->pktNbr)},{"reason",reason},{"alternativeRequest",subscription(v->altReq)}});
}
inline std::string pduName(Iso14827PDUs *p){
    if(!p)return "분석 불가";
    switch(p->present){
    case Iso14827PDUsPresent_initiate:return "Initiate (접속 개시)";
    case Iso14827PDUsPresent_login:return "Login (로그인)";
    case Iso14827PDUsPresent_fred:return p->x.fred?"FrED (연결 확인 응답)":"FrED (연결 확인 요청)";
    case Iso14827PDUsPresent_term:return "Terminate (종료 요청)";
    case Iso14827PDUsPresent_logout:return "Logout (로그아웃)";
    case Iso14827PDUsPresent_subscription:return p->x.subscription && p->x.subscription->type && p->x.subscription->type->present==Iso14827SubscriptionTypePresent_reason?"Subscription Cancel (구독 취소)":"Subscription (정보요청)";
    case Iso14827PDUsPresent_publication:return "Publication (정보제공)";
    case Iso14827PDUsPresent_transferDone:return "TransferDone (전송 완료)";
    case Iso14827PDUsPresent_ack:return "Accept / ACK (수용)";
    case Iso14827PDUsPresent_nak:return "Reject / NAK (거부)";
    default:return "알 수 없는 PDU";}
}
inline std::string body(Iso14827PDUs *p){
    if(!p)return "null";
    switch(p->present){
    case Iso14827PDUsPresent_initiate:{auto v=p->x.initiate;return v?object({{"sender",text(v->sender)},{"dest",text(v->dest)}}):"null";}
    case Iso14827PDUsPresent_login:{auto v=p->x.login;if(!v)return "null";
        std::string codecs="[";unsigned n=0;Dz1Error err={};auto rows=v->encRules?v->encRules->get_array(v->encRules,&n,&err):nullptr;
        for(unsigned i=0;i<n && rows;++i){if(i)codecs+=',';codecs+=oid(rows[i]);}Dz1Free(rows);
        return object({{"sender",text(v->sender)},{"dest",text(v->dest)},{"user",binary(v->user)},
            {"pass",quote("[비밀번호 가림]")},{"encodingRules",codecs+"]"},{"heartbeatDurationMax",number(v->hbDur)},
            {"responseTimeout",number(v->timeout)},{"initiator",DATEX_ENUM(Iso14827LoginInitiator,v->initiator)},{"datagramSize",number(v->datagramSize)}});}
    case Iso14827PDUsPresent_fred:return object({{"replyToPacketNumber",number(p->x.fred)}});
    case Iso14827PDUsPresent_term:return object({{"reason",DATEX_ENUM(Iso14827Terminate,p->x.term)}});
    case Iso14827PDUsPresent_logout:return object({{"reason",DATEX_ENUM(Iso14827Logout,p->x.logout)}});
    case Iso14827PDUsPresent_subscription:{auto s=p->x.subscription;return s?object({{"subscriptionSerial",number(s->serial)},{"type",subscription(s->type)}}):"null";}
    case Iso14827PDUsPresent_publication:return publication(p->x.publication);
    case Iso14827PDUsPresent_transferDone:{auto v=p->x.transferDone;return v?object({{"filename",text(v->filename)},{"isSuccess",boolean(v->isSuccess)}}):"null";}
    case Iso14827PDUsPresent_ack:return accept(p->x.ack);
    case Iso14827PDUsPresent_nak:return reject(p->x.nak);
    default:return "null";}
}
#undef DATEX_ENUM
} // namespace message_view

struct MessageView {std::string name,details;};
inline MessageView completeMessageView(const Case &c,const Bytes &safeWire,const std::string &test) {
    using namespace message_view;
    Bytes bytes=safeWire;
    auto m=decode(bytes);
    bool masked=false; auto protectedBytes=privacyWire(m.get(),bytes,masked);
    if(masked)m=decode(protectedBytes);
    auto name=pduName(m->pdu);
    auto auth=object({{"authInfo",binary(m->authInfo)},{"packetNumber",number(m->pktNbr)},{"priority",number(m->priority)},
        {"header",header(m->hdrOpt)},{"pdu",object({{"name",quote(name)},{"body",body(m->pdu)}})}});
    std::string applications="[";
    if(m->pdu && m->pdu->present==Iso14827PDUsPresent_publication){
        try{auto decoded=inspectLinkedData(c,safeWire,test);
            for(const auto &row:decoded){if(applications.size()>1)applications+=',';
                applications+=object({{"정보 종류",quote(messageLabel(row.message))},{"message",quote(row.message)},
                    {"subscriptionSerial",number(row.subscription)},{"publicationSerial",number(row.publication)},
                    {"payloadHex",quote(dataHex(row.raw))},{"decoded",decodedData(row.decodedJson)},
                    {"regional",decodedData(row.regionalJson)},{"안내",quote(row.note)}});
            }
        }catch(const Failure &){applications+=object({{"안내",quote("업무 데이터의 표시용 분석을 완료하지 못했습니다. C2CAuthMsg 내용과 원문 전체를 확인하세요.")}});}
    }
    return {name,object({{"ISO 14827 C2CAuthMsg",auth},{"연계정보",applications+"]"},{"원문 HEX",quote(dataHex(protectedBytes))}})};
}
struct MessagePart {size_t index,total;std::string json;};
inline std::vector<MessagePart> messageParts(const std::string &metadata,const std::string &detail) {
    constexpr size_t limit=12000;
    if(detail.size()<=limit)return {{1,1,"{"+metadata+",\"상세\":"+detail+"}"}};
    std::vector<std::string> chunks;
    for(size_t start=0;start<detail.size();){size_t end=std::min(start+limit,detail.size());
        while(end<detail.size() && (static_cast<unsigned char>(detail[end])&0xc0)==0x80)--end;
        chunks.push_back(detail.substr(start,end-start));start=end;}
    std::vector<MessagePart> parts;
    for(size_t i=0;i<chunks.size();++i)parts.push_back({i+1,chunks.size(),"{"+metadata+",\"분할 번호\":"+std::to_string(i+1)+",\"전체 분할 수\":"+std::to_string(chunks.size())+",\"분할 안내\":\"동일 메시지의 상세 JSON을 순서대로 연결하면 전체를 복원할 수 있습니다. 생략 없음.\",\"분할 데이터\":"+quote(chunks[i])+"}"});
    return parts;
}
} // namespace datex
