#include <winsock2.h>
#include <ws2tcpip.h>
#include "DatexWire.h"
#include "DatexNarrative.h"
#include "DatexSamples.h"
#include <TechnicalRegulation2MsgStructAPI.h>
#include <TechnicalRegulation1MsgStructAPI.h>
extern "C" Dz1Binary *DatexPayload_timRegionalSummary(unsigned char *, size_t);
extern "C" int DatexPayload_validate(unsigned, unsigned char *, size_t);
extern "C" int DatexPayload_messageId(unsigned char *, size_t);
extern "C" Dz1Binary *DatexPayload_timProfile(unsigned char *, size_t, unsigned);
extern "C" int DatexPayload_checkTimProfile(unsigned char *, size_t, unsigned);
extern "C" Dz1Binary *DatexPayload_json(unsigned, unsigned char *, size_t);
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <mutex>

namespace datex {
namespace {
struct MemoryDelete {
    void operator()(void *p) const {
        Dz1Free(p);
    }
};
char *mut(const std::string &s) {
    return const_cast<char *>(s.c_str());
}
template <class T> T *checked(T *p) {
    if (!p)
        throw Failure("메모리 또는 메시지 생성 실패");
    return p;
}
void ok(Dz1Error e) {
    if (e.code)
        throw Failure("코덱 오류: " + std::to_string(e.code));
}
Dz1Asn1UTF8Str *utf8(const std::string &s) {
    Dz1Error e = {};
    return checked(Dz1Asn1UTF8Str_new((u8_t *)s.data(), codecSize(s.size()), &e));
}
Dz1Asn1OctetStr *octets(const std::string &s) {
    Dz1Error e = {};
    return checked(Dz1Asn1OctetStr_new((u8_t *)s.data(), codecSize(s.size()), &e));
}
Dz1Asn1OID *oid(const std::string &s) {
    Dz1Error e = {};
    return checked(Dz1Asn1OID_newFromStr(mut(s), &e));
}
Iso14827TestMsgStructAPI *apiTable(const Case &c) {
    if (std::string(c.oid).find("1.0.14827.") == 0)
        return TechnicalRegulation1_PolicePrj4C2CMsgSet;
    return std::string(c.oid) == "1.0.15784.1.0.1" ? TechnicalRegulation2MsgTx_itsk
                                                   : TechnicalRegulation2MsgRx_itsk;
}
Iso14827EndAppMsg *eam(const std::string &name, const Bytes &data) {
    auto size = codecSize(data.size());
    Dz1Error e = {};
    auto p = checked(Iso14827EndAppMsg_gen(&e));
    p->oid = oid(name);
    p->data = checked(Dz1Asn1Any_new((u8_t *)data.data(), size, &e));
    return p;
}
Bytes sample(const Case &c, const Message &m) {
    if (m.oid && std::string(m.oid) != c.oid)
        return sample(messageCase(c, m), m);
    const unsigned char *raw = nullptr;
    size_t size = 0;
#define FIXTURE(n)                                                                                           \
    if (std::string(m.name) == #n) {                                                                         \
        raw = fixtures::n;                                                                                   \
        size = sizeof(fixtures::n);                                                                          \
    }
    Bytes generated;
    if (m.businessProfile) {
        auto profile = DatexPayload_timProfile((unsigned char *)fixtures::tim, sizeof(fixtures::tim), m.businessProfile);
        if (!profile) throw Failure("TIM 통행지시 샘플 생성 실패");
        generated.assign(profile->data, profile->data + profile->size);
        Dz1Binary_del(profile); raw = generated.data(); size = generated.size();
    } else FIXTURE(bsm)
    else FIXTURE(map) else FIXTURE(rsa) else FIXTURE(tim) else FIXTURE(spat) else FIXTURE(tls)
#undef FIXTURE
        if (!raw) throw Failure("시험 샘플 없음");
    Dz1Error e = {};
    void *list = nullptr;
    auto type = [&]() {
        auto v = (s64_t *)checked(Dz1Calloc(sizeof(s64_t), 1, &e));
        *v = m.type;
        return v;
    };
    auto bytes = [&]() { return checked(Dz1Asn1OctetStr_new((u8_t *)raw, (u32_t)size, &e)); };
    time_t begin = time(nullptr), end = begin + 300;
    if (std::string(c.oid) == "1.0.15784.1.0.1") {
        auto p = checked(Dz1CommTxPDUResponse_gen(&e));
        list = p;
        auto item = checked(Dz1CommTxPDU_gen(&e));
        item->index = 1;
        item->psid = m.psid;
        item->priority = 1;
        item->channel = 1;
        item->txInterval = 1;
        item->payloadType = type();
        item->payload = bytes();
        item->deliveryStart = checked(Dz1TimeVal_newFromTime(&begin, &e));
        item->deliveryStop = checked(Dz1TimeVal_newFromTime(&end, &e));
        ok(p->add(p, item));
    } else if (std::string(c.oid) == "1.0.15784.1.0.2") {
        auto p = checked(Dz1CommRxPDUResponse_gen(&e));
        list = p;
        auto item = checked(Dz1CommRxPDU_gen(&e));
        item->psid = m.psid;
        item->channel = 1;
        item->rcpi = 1;
        item->peerAddress = octets("test-peer");
        item->payloadType = type();
        item->payload = bytes();
        ok(p->add(p, item));
    } else {
        auto p = checked(Dz1ExtentionCommPDUResponse_gen(&e));
        list = p;
        auto item = checked(Dz1ExtentionCommPDU_gen(&e));
        item->index = 1;
        item->aid = 2;
        item->payloadType = type();
        *item->payloadType = 1; // P3 ExtentionCommPDU: embedded UPER MessageFrame, not a PSID.
        item->payload = bytes();
        item->deliveryStart = checked(Dz1TimeVal_newFromTime(&begin, &e));
        item->deliveryStop = checked(Dz1TimeVal_newFromTime(&end, &e));
        ok(p->add(p, item));
    }
    auto api = Iso14827TestMsgSet_findAPI(apiTable(c), mut(c.oid), nullptr);
    auto b = api->struct_encode(list, Dz1Asn1Codec_ber, &e);
    api->struct_delAndSetNull(&list);
    if (!b)
        throw Failure("시험 샘플 인코딩 실패");
    Bytes out(b->data, b->data + b->size);
    Dz1Binary_del(b);
    return out;
}
void payload(unsigned psid, unsigned expected, Dz1Asn1OctetStr *data) {
    if (!data || !DatexPayload_validate(expected, data->data, data->size))
        throw Failure("PSID/MessageFrame/payload decoding failed: " + std::to_string(psid));
}
size_t tlvEnd(const Bytes &b, size_t at, unsigned depth) {
    if (depth > 32)
        throw Failure("BER 중첩 제한");
    if (at >= b.size())
        return 0;
    unsigned char tag = b[at++];
    if ((tag & 31) == 31) {
        unsigned n = 0;
        do {
            if (at == b.size())
                return 0;
            if (++n > 5)
                throw Failure("BER 태그 제한");
        } while (b[at++] & 128);
    }
    if (at == b.size())
        return 0;
    unsigned char l = b[at++];
    size_t len = 0;
    if (l == 128) {
        if (!(tag & 32))
            throw Failure("BER indefinite primitive");
        for (;;) {
            if (at + 2 > b.size())
                return 0;
            if (!b[at] && !b[at + 1])
                return at + 2;
            at = tlvEnd(b, at, depth + 1);
            if (!at)
                return 0;
        }
    }
    if (l & 128) {
        unsigned n = l & 127;
        if (!n || n > 4)
            throw Failure("BER 길이 제한");
        if (at + n > b.size())
            return 0;
        while (n--)
            len = (len << 8) | b[at++];
    } else
        len = l;
    if (len > 8 * 1024 * 1024)
        throw Failure("DATEX 프레임 크기 제한");
    return len > b.size() - at ? 0 : at + len;
}
} // namespace
std::string utf8Text(Dz1Asn1UTF8Str *p) {
    return p && p->data ? std::string((char *)p->data, p->size) : std::string();
}
std::string octetText(Dz1Asn1OctetStr *p) {
    return p && p->data ? std::string((char *)p->data, p->size) : std::string();
}
std::string oidText(Dz1Asn1OID *p) {
    char out[256] = {};
    if (!p)
        return {};
    Dz1Asn1OID_printable(p, out, sizeof(out), nullptr);
    return out;
}
size_t frameSize(const Bytes &b) {
    return tlvEnd(b, 0, 0);
}
Bytes privacyWire(Iso14827C2CAuthMsg *message, const Bytes &wire, bool &redacted) {
    const bool password = message->pdu && message->pdu->present == Iso14827PDUsPresent_login && message->pdu->x.login;
    const bool auth = message->authInfo && message->authInfo->size &&
        !(message->authInfo->size == 1 && message->authInfo->data[0] == ' ');
    redacted = password || auth;
    if (!redacted) return wire;
    Dz1Error e = {};
    Packet copy(checked(Iso14827C2CAuthMsg_clone(message, &e)), Iso14827C2CAuthMsg_del);
    if (password) { Dz1Asn1OctetStr_del(copy->pdu->x.login->pass); copy->pdu->x.login->pass = octets("[redacted]"); }
    if (auth) { Dz1Asn1OctetStr_del(copy->authInfo); copy->authInfo = octets("[redacted]"); }
    return encode(copy.get());
}
static void observe(const Sink &sink, const std::string &test, bool rx, Iso14827C2CAuthMsg *message,
                    const PacketRecord &r) {
    if (!sink.packet) return;
    bool redacted = false;
    auto safe = privacyWire(message, r.wire, redacted);
    sink.packet(test, rx, r, message->pdu->present, safe, redacted);
}

Pdu pdu(Iso14827PDUsPresent t) {
    Dz1Error e = {};
    Pdu p(checked(Iso14827PDUs_gen(&e)), Iso14827PDUs_del);
    p->present = t;
    return p;
}
Packet packet(const Config &c, Pdu p, unsigned number) {
    Dz1Error e = {};
    Packet m(checked(Iso14827C2CAuthMsg_gen(&e)), Iso14827C2CAuthMsg_del);
    m->authInfo = octets(" ");
    m->pktNbr = number;
    m->priority = 1;
    m->pdu = p.release();
    m->hdrOpt = checked(Iso14827HdrOpt_gen(&e));
    m->hdrOpt->sender = utf8(c.myDomain);
    m->hdrOpt->dest = utf8(c.peerDomain);
    m->hdrOpt->t = checked(Iso14827Time_get(nullptr, ISO14827TIME_FLAG_UTC, &e));
    return m;
}
Bytes encode(Iso14827C2CAuthMsg *m) {
    Dz1Error e = {};
    u8_t *raw = nullptr;
    auto n = Iso14827C2CAuthMsg_encodeDatex(m, &raw, Dz1Asn1Codec_ber, &e);
    if (n <= 0 || !raw)
        throw Failure("DATEX BER 인코딩 실패");
    Bytes b(raw, raw + n);
    Dz1Free(raw);
    return b;
}
Packet decode(Bytes &b) {
    Dz1Error e = {};
    Iso14827C2CAuthMsg *p = nullptr;
    auto n = Iso14827C2CAuthMsg_decodeDatex(&p, b.data(), b.size(), Dz1Asn1Codec_ber, &e);
    Packet m(p, Iso14827C2CAuthMsg_del);
    if (n != ssize_t(b.size()) || !p || e.code)
        throw Failure("DATEX BER/CRC 디코딩 실패");
    return m;
}
PacketRecord record(Iso14827C2CAuthMsg *m, const Bytes &b, Tick now) {
    PacketRecord r;
    r.number = m->pktNbr;
    r.hasTimestamp = m->hdrOpt && m->hdrOpt->t;
    r.wire = b;
    r.received = now;
    Dz1Error e = {};
    Packet clone(checked(Iso14827C2CAuthMsg_clone(m, &e)), Iso14827C2CAuthMsg_del);
    clone->pktNbr = 0;
    Config empty;
    auto stamp = packet(empty, fred(), 0);
    Iso14827HdrOpt_del(stamp->hdrOpt);
    stamp->hdrOpt = checked(Iso14827HdrOpt_gen(&e));
    if (clone->hdrOpt && clone->hdrOpt->t) {
        stamp->hdrOpt->t = checked(Iso14827Time_clone(clone->hdrOpt->t, &e));
        Iso14827Time_del(clone->hdrOpt->t);
        clone->hdrOpt->t = nullptr;
    }
    r.timestamp = encode(stamp.get());
    r.content = encode(clone.get());
    return r;
}
Pdu fred(unsigned n) {
    auto p = pdu(Iso14827PDUsPresent_fred);
    p->x.fred = n;
    return p;
}
Pdu initiate(const Config &c) {
    Dz1Error e = {};
    auto p = pdu(Iso14827PDUsPresent_initiate);
    auto i = p->x.initiate = checked(Iso14827Initiate_gen(&e));
    i->sender = utf8(c.myDomain);
    i->dest = utf8(c.peerDomain);
    return p;
}
Pdu login(const Config &c, const std::string &pass) {
    Dz1Error e = {};
    auto p = pdu(Iso14827PDUsPresent_login);
    auto l = p->x.login = checked(Iso14827Login_gen(&e));
    l->sender = utf8(c.myDomain);
    l->dest = utf8(c.peerDomain);
    l->user = octets(c.user);
    l->pass = octets(pass);
    l->hbDur = c.heartbeat;
    l->timeout = c.response;
    l->initiator = c.useInitiate ? Iso14827LoginInitiator_serverInitiated : Iso14827LoginInitiator_clientInitiated;
    l->datagramSize = 0;
    ok(l->encRules->add(l->encRules, oid("2.1.1")));
    return p;
}
Pdu accept(unsigned n, Iso14827AcceptTypePresent t, unsigned sid) {
    Dz1Error e = {};
    auto p = pdu(Iso14827PDUsPresent_ack);
    p->x.ack = checked(Iso14827Accept_gen(&e));
    p->x.ack->pktNbr = n;
    auto a = p->x.ack->acceptType = checked(Iso14827AcceptType_gen(&e));
    a->present = t;
    if (t == Iso14827AcceptTypePresent_login)
        a->x.login = oid("2.1.1");
    else if (t == Iso14827AcceptTypePresent_registeredSubscription)
        a->x.registeredSubscription = sid;
    return p;
}
Pdu reject(unsigned n, Iso14827RejectTypePresent t, int why, unsigned sid, unsigned pub) {
    Dz1Error e = {};
    auto p = pdu(Iso14827PDUsPresent_nak);
    auto nak = p->x.nak = checked(Iso14827Reject_gen(&e));
    nak->pktNbr = n;
    nak->type = checked(Iso14827RejectType_gen(&e));
    nak->type->present = t;
    switch (t) {
    case Iso14827RejectTypePresent_login:
        nak->type->x.login = Iso14827RejectLogin(why);
        break;
    case Iso14827RejectTypePresent_subscription:
        nak->type->x.subscription = Iso14827RejectSubscription(why);
        break;
    case Iso14827RejectTypePresent_publication:
        nak->type->x.publication = Iso14827RejectPublication(why);
        break;
    case Iso14827RejectTypePresent_pubData:
        nak->type->x.pubData =
            checked(Iso14827RejectPubData_new(sid, pub, Iso14827RejectPubDataReason(why), &e));
        break;
    default:
        throw Failure("Reject 종류 오류");
    }
    return p;
}
Pdu subscribe(const Case &c, unsigned sid, unsigned period, const std::string &alternate) {
    Dz1Error e = {};
    auto p = pdu(Iso14827PDUsPresent_subscription);
    auto sub = p->x.subscription = checked(Iso14827Subscription_gen(&e));
    sub->serial = sid;
    sub->type = checked(Iso14827SubscriptionType_gen(&e));
    sub->type->present = Iso14827SubscriptionTypePresent_data;
    auto d = sub->type->x.data = checked(Iso14827SubscriptionData_gen(&e));
    d->persistent = FALSE;
    d->status = Iso14827SubscriptionDataStatus_NEW;
    d->fmt = Iso14827SubscriptionDataFormat_dataPacket;
    d->priority = 5;
    d->guarantee = TRUE;
    d->mode = checked(Iso14827SubscriptionDataMode_gen(&e));
    if (period) {
        d->mode->present = Iso14827SubscriptionDataModePresent_periodic;
        auto r = d->mode->x.periodic = checked(Iso14827Registered_gen(&e));
        r->present = Iso14827RegisteredPresent_continuous;
        auto co = r->x.continuous = checked(Iso14827RegisteredContinuous_gen(&e));
        co->updateDelay = period;
        co->start = checked(Iso14827TimeFromTime(nullptr, time(nullptr), ISO14827TIME_FLAG_UTC, &e));
        co->end = checked(Iso14827TimeFromTime(nullptr, time(nullptr) + 86401, ISO14827TIME_FLAG_UTC, &e));
    } else
        d->mode->present = Iso14827SubscriptionDataModePresent_single;
    d->msg = eam(alternate.empty() ? c.oid : alternate, Bytes{5, 0});
    return p;
}
Pdu cancel(unsigned sid) {
    Dz1Error e = {};
    auto p = pdu(Iso14827PDUsPresent_subscription);
    auto s = p->x.subscription = checked(Iso14827Subscription_gen(&e));
    s->serial = sid;
    s->type = checked(Iso14827SubscriptionType_gen(&e));
    s->type->present = Iso14827SubscriptionTypePresent_reason;
    s->type->x.reason = Iso14827SubscriptionCancel_dataNotNeeded;
    return p;
}
Pdu publication(const Case &c, const Message &m, unsigned sid, unsigned serial, const std::string &error) {
    if (m.oid && std::string(m.oid) != c.oid)
        return publication(messageCase(c, m), m, sid, serial, error);
    Dz1Error e = {};
    auto p = pdu(Iso14827PDUsPresent_publication);
    auto pub = p->x.publication = checked(Iso14827Publication_gen(&e));
    pub->guaranteed = TRUE;
    pub->fmt = checked(Iso14827PublishFormat_gen(&e));
    pub->fmt->present = Iso14827PublishFormatPresent_dataList;
    pub->fmt->x.dataList = checked(Iso14827PublicationDataList_gen(&e));
    auto d = checked(Iso14827PublicationData_gen(&e));
    d->subscriptionSerial = error == "unknownSubscription" ? sid + 999 : sid;
    d->serial = error == "unknownPublicationNbr" ? 999 : serial;
    d->isLated = FALSE;
    d->type = checked(Iso14827PublicationType_gen(&e));
    d->type->present = Iso14827PublicationTypePresent_msg;
    std::string name = c.oid;
    if (error == "unknownPublicationMsgId")
        name = "1.0.15784.99.99.99";
    if (error == "invalidPublicationMsgId")
        name = name == "1.0.15784.1.0.1" ? "1.0.15784.1.0.2" : "1.0.15784.1.0.1";
    auto bytes = error == "invalidPublicationMsgContent" ? Bytes{5, 0} : sample(c, m);
    d->type->x.msg = eam(name, bytes);
    ok(pub->fmt->x.dataList->add(pub->fmt->x.dataList, d));
    return p;
}
Pdu publicationBundle(const Case &c, const std::vector<Message> &messages, unsigned sid,
                      unsigned serial, const std::string &error) {
    if (messages.empty())
        throw Failure("발행할 메시지가 없습니다.");
    if (messages.size() == 1 || !error.empty())
        return publication(c, messages.front(), sid, serial, error);
    if (std::string(c.oid) == "1.0.14827.1.1.0") {
        Dz1Error e = {};
        auto api = Iso14827TestMsgSet_findAPI(apiTable(c), mut(c.oid), nullptr);
        auto combined = checked(Dz1ExtentionCommPDUResponse_gen(&e));
        void *combinedData = combined;
        try {
            for (const auto &m : messages) {
                if (std::string(messageCase(c, m).oid) != c.oid)
                    throw Failure("서로 다른 OID의 신호정보는 별도 구독으로 제공해야 합니다.");
                auto bytes = sample(c, m);
                Dz1Binary input = {bytes.data(), codecSize(bytes.size())};
                void *decoded = api->struct_decode(&input, Dz1Asn1Codec_ber, &e);
                if (!decoded) throw Failure("신호정보 샘플 목록 디코딩 실패");
                try {
                    auto list = (Dz1ExtentionCommPDUResponse *)decoded;
                    unsigned count = 0;
                    auto items = list->get_array(list, &count, &e);
                    std::unique_ptr<void, MemoryDelete> hold(items);
                    if (!items || count != 1) throw Failure("신호정보 샘플 항목 수 오류");
                    auto item = checked(Dz1ExtentionCommPDU_clone(items[0], &e));
                    item->index = combined->count(combined) + 1;
                    auto added = combined->add(combined, item);
                    if (added.code) { Dz1ExtentionCommPDU_del(item); ok(added); }
                } catch (...) { api->struct_delAndSetNull(&decoded); throw; }
                api->struct_delAndSetNull(&decoded);
            }
            auto encoded = api->struct_encode(combined, Dz1Asn1Codec_ber, &e);
            if (!encoded) throw Failure("신호정보 발행 목록 인코딩 실패");
            Bytes body(encoded->data, encoded->data + encoded->size);
            Dz1Binary_del(encoded);
            auto out = publication(c, messages.front(), sid, serial);
            auto data = publicationData(out->x.publication).front();
            Iso14827EndAppMsg_del(data->type->x.msg);
            data->type->x.msg = nullptr;
            data->type->x.msg = eam(c.oid, body);
            api->struct_delAndSetNull(&combinedData);
            return out;
        } catch (...) { api->struct_delAndSetNull(&combinedData); throw; }
    }
    if (std::string(c.oid) != "1.0.15784.1.0.1")
        throw Failure("복수 메시지 발행은 CommTxPDU 또는 ExtentionCommPDU 프로파일에만 적용합니다.");
    Dz1Error e = {};
    auto api = Iso14827TestMsgSet_findAPI(apiTable(c), mut(c.oid), nullptr);
    auto combined = checked(Dz1CommTxPDUResponse_gen(&e));
    void *combinedData = combined;
    try {
        for (auto &m : messages) {
            auto bytes = sample(c, m);
            Dz1Binary input = {bytes.data(), codecSize(bytes.size())};
            void *decoded = api->struct_decode(&input, Dz1Asn1Codec_ber, &e);
            if (!decoded) throw Failure("발행 샘플 목록 디코딩 실패");
            try {
                auto list = (Dz1CommTxPDUResponse *)decoded;
                unsigned count = 0;
                auto items = list->get_array(list, &count, &e);
                std::unique_ptr<void, MemoryDelete> hold(items);
                if (!items || count != 1) throw Failure("발행 샘플 항목 수 오류");
                auto item = checked(Dz1CommTxPDU_clone(items[0], &e));
                item->index = combined->count(combined) + 1;
                auto added = combined->add(combined, item);
                if (added.code) { Dz1CommTxPDU_del(item); ok(added); }
            } catch (...) { api->struct_delAndSetNull(&decoded); throw; }
            api->struct_delAndSetNull(&decoded);
        }
        auto encoded = api->struct_encode(combined, Dz1Asn1Codec_ber, &e);
        if (!encoded) throw Failure("발행 목록 인코딩 실패");
        Bytes body(encoded->data, encoded->data + encoded->size);
        Dz1Binary_del(encoded);
        auto out = publication(c, messages.front(), sid, serial);
        auto data = publicationData(out->x.publication).front();
        Iso14827EndAppMsg_del(data->type->x.msg);
        data->type->x.msg = nullptr;
        data->type->x.msg = eam(c.oid, body);
        api->struct_delAndSetNull(&combinedData);
        return out;
    } catch (...) { api->struct_delAndSetNull(&combinedData); throw; }
}
std::vector<Iso14827PublicationData *> publicationData(Iso14827Publication *p) {
    if (!p || !p->fmt || p->fmt->present != Iso14827PublishFormatPresent_dataList || !p->fmt->x.dataList)
        throw Failure("Publication dataList 형식 오류");
    unsigned n = 0;
    Dz1Error e = {};
    auto a = p->fmt->x.dataList->get_array(p->fmt->x.dataList, &n, &e);
    if (!a || !n)
        throw Failure("빈 Publication 목록");
    std::vector<Iso14827PublicationData *> r(a, a + n);
    Dz1Free(a);
    return r;
}
void validatePayload(const Case &c, const Message &m, Iso14827PublicationData *d, const Sink *sink,
                     const std::string &test) {
    if (m.oid && std::string(m.oid) != c.oid) {
        validatePayload(messageCase(c, m), m, d, sink, test);
        return;
    }
    if (!d || !d->type || d->type->present != Iso14827PublicationTypePresent_msg || !d->type->x.msg)
        throw Failure("Publication 업무 메시지 누락");
    auto msg = d->type->x.msg;
    if (oidText(msg->oid) != c.oid || !msg->data)
        throw Failure("Publication OID/내용 오류");
    Dz1Error e = {};
    auto api = Iso14827TestMsgSet_findAPI(apiTable(c), mut(c.oid), nullptr);
    if (!api)
        throw Failure("메시지 API 없음");
    Dz1Binary bin = {msg->data->data, msg->data->size};
    auto data = api->struct_decode(&bin, Dz1Asn1Codec_ber, &e);
    if (!data)
        throw Failure("EAM 디코딩 실패");
    bool found = false;
    auto verify = [&](Dz1Asn1OctetStr *input) {
        payload(m.psid, m.type, input);
        if (m.type == 31 && sink && sink->info) {
            auto regional = DatexPayload_timRegionalSummary(input->data, input->size);
            if (!regional) throw Failure("TIM regional UPER decoding failed");
            std::string decoded((char *)regional->data, regional->size);
            Dz1Binary_del(regional);
            sink->info(test, "TIM_REGIONAL_DECODE " + decoded);
        }
        if (m.businessProfile && !DatexPayload_checkTimProfile(input->data, input->size, m.businessProfile))
            throw Failure("TIM 통행지시 필수 프로파일 불일치");
        if (sink && sink->validation) {
            auto json = DatexPayload_json(m.type, input->data, input->size);
            if (!json)
                throw Failure("payload JSON 변환 실패");
            Bytes raw(input->data, input->data + input->size), data(json->data, json->data + json->size);
            Dz1Binary_del(json);
            sink->validation(test, m.name, raw, data);
        }
    };
    try {
        if (std::string(c.oid) == "1.0.15784.1.0.1") {
            auto list = (Dz1CommTxPDUResponse *)data;
            unsigned n = 0;
            auto a = list->get_array(list, &n, &e);
            std::unique_ptr<void, MemoryDelete> hold(a);
            if (!a)
                throw Failure("목록 읽기 실패");
            for (unsigned i = 0; i < n; ++i)
                if (a[i]->psid == int(m.psid)) {
                    if (a[i]->payloadType && *a[i]->payloadType != m.type)
                        throw Failure("CommTxPDU payloadType/MessageFrame 식별자 불일치");
                    verify(a[i]->payload);
                    found = true;
                }
        } else if (std::string(c.oid) == "1.0.15784.1.0.2") {
            auto list = (Dz1CommRxPDUResponse *)data;
            unsigned n = 0;
            auto a = list->get_array(list, &n, &e);
            std::unique_ptr<void, MemoryDelete> hold(a);
            if (!a)
                throw Failure("목록 읽기 실패");
            for (unsigned i = 0; i < n; ++i)
                if (a[i]->psid == int(m.psid)) {
                    verify(a[i]->payload);
                    found = true;
                }
        } else {
            auto list = (Dz1ExtentionCommPDUResponse *)data;
            unsigned n = 0;
            auto a = list->get_array(list, &n, &e);
            std::unique_ptr<void, MemoryDelete> hold(a);
            if (!a)
                throw Failure("목록 읽기 실패");
            for (unsigned i = 0; i < n; ++i) {
                if (a[i]->aid != 2 || (a[i]->payloadType && *a[i]->payloadType != 1) || !a[i]->payload)
                    throw Failure("ExtentionCommPDU AID/인코딩 구분 오류");
                if (DatexPayload_messageId(a[i]->payload->data, a[i]->payload->size) == int(m.type)) {
                    verify(a[i]->payload);
                    found = true;
                }
            }
        }
    } catch (...) {
        api->struct_delAndSetNull(&data);
        throw;
    }
    api->struct_delAndSetNull(&data);
    if (!found)
        throw Failure("요청한 메시지가 Publication에 없습니다: " + std::string(m.name));
}

struct Session::Impl {
    const Case &c;
    const Config &config;
    std::atomic<bool> &stop;
    const Sink &sink;
    std::string test;
    SOCKET socket = INVALID_SOCKET, listener = INVALID_SOCKET;
    Bytes buffer;
    unsigned serial = 1;
    std::uint64_t sessionId;
    bool active = false, hb = true, transportUsable = true, closing = false;
    size_t lastAttemptBytes = 0;
    Tick lastRx = std::chrono::steady_clock::now(), lastTx = lastRx, bufferedAt = lastRx;
    std::set<unsigned> pendingEcho;
    Impl(const Case &c, const Config &conf, std::atomic<bool> &s, const Sink &out, const std::string &t)
        : c(c), config(conf), stop(s), sink(out), test(t) {
        static std::atomic<std::uint64_t> nextSession{0};
        sessionId = ++nextSession;
        static std::once_flag once;
        static int error = 0;
        std::call_once(once, [] {
            WSADATA w;
            error = WSAStartup(MAKEWORD(2, 2), &w);
        });
        if (error)
            throw Failure("Winsock 초기화 실패");
    }
    ~Impl() {
        if (socket != INVALID_SOCKET)
            closesocket(socket);
        if (listener != INVALID_SOCKET)
            closesocket(listener);
    }
    void observeUndecoded(const Bytes &raw) {
        if (!sink.packet || raw.empty()) return;
        Bytes safe = raw; bool masked = false;
        for (const auto &secret : {config.password, config.invalidPassword}) {
            if (secret.empty()) continue;
            auto pos = safe.begin();
            while ((pos = std::search(pos, safe.end(), secret.begin(), secret.end())) != safe.end()) {
                std::fill(pos, pos + secret.size(), static_cast<unsigned char>('*'));
                pos += secret.size(); masked = true;
            }
        }
        PacketRecord observed; observed.sessionId = sessionId; observed.received = bufferedAt;
        observed.wire = safe; observed.hasTimestamp = false;
        sink.packet(test, true, observed, -1, safe, masked);
    }
    void check() {
        if (stop.load())
            throw Stopped();
    }
    bool ready(SOCKET s, bool write, Tick deadline) {
        check();
        if (std::chrono::steady_clock::now() >= deadline)
            return false;
        fd_set f;
        FD_ZERO(&f);
        FD_SET(s, &f);
        timeval tv = {0, 50000};
        int n = select(0, write ? nullptr : &f, write ? &f : nullptr, nullptr, &tv);
        if (n == SOCKET_ERROR) {
            transportUsable = false;
            throw Failure("소켓 대기 실패");
        }
        return n > 0;
    }
    void nonblocking(SOCKET s) {
        u_long on = 1;
        if (ioctlsocket(s, FIONBIO, &on))
            throw Failure("소켓 설정 실패");
    }
    void sendRaw(const Bytes &bytes) {
        size_t sent = 0;
        lastAttemptBytes = 0;
        auto until = std::chrono::steady_clock::now() + std::chrono::seconds(config.response);
        while (sent < bytes.size()) {
            check();
            if (std::chrono::steady_clock::now() >= until)
                throw Failure("송신 시간 초과");
            if (!ready(socket, true, until))
                continue;
            int n = ::send(socket, (char *)bytes.data() + sent, int(bytes.size() - sent), 0);
            if (n == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
                continue;
            if (n <= 0)
                throw Failure("소켓 송신 실패");
            sent += n;
            lastAttemptBytes = sent;
        }
        lastTx = std::chrono::steady_clock::now();
    }
};
Session::Session(const Case &c, const Config &conf, std::atomic<bool> &stop, const Sink &sink,
                 const std::string &test)
    : impl_(new Impl(c, conf, stop, sink, test)) {}
Session::~Session() = default;
void Session::openListener() {
    auto &x = *impl_;
    if (x.listener != INVALID_SOCKET)
        throw Failure("수신 대기 소켓이 이미 열려 있습니다.");
    x.listener = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (x.listener == INVALID_SOCKET)
        throw Failure("수신 소켓 생성 실패");
    BOOL exclusive = TRUE;
    setsockopt(x.listener, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char *)&exclusive, sizeof(exclusive));
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((u_short)x.config.port);
    if (bind(x.listener, (sockaddr *)&addr, sizeof(addr)) || ::listen(x.listener, 4))
        throw Failure("포트 바인딩 실패");
    x.nonblocking(x.listener);
    x.sink.info(x.test, "LISTENING");
}
void Session::open() {
    auto &x = *impl_;
    auto until = std::chrono::steady_clock::now() + std::chrono::seconds(x.config.connectTimeout);
    if (!x.config.tcpConnects(x.c)) {
        openListener();
        x.socket = SOCKET(acceptPeer(until));
    } else {
        sockaddr_in addr = {};
        addr.sin_family = AF_INET;
        addr.sin_port = htons((u_short)x.config.port);
        if (inet_pton(AF_INET, x.config.host.c_str(), &addr.sin_addr) != 1)
            throw Failure("IPv4 주소 형식 오류");
        x.socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (x.socket == INVALID_SOCKET)
            throw Failure("송신 소켓 생성 실패");
        x.nonblocking(x.socket);
        int n = connect(x.socket, (sockaddr *)&addr, sizeof(addr));
        if (n && WSAGetLastError() != WSAEWOULDBLOCK)
            throw Failure("접속 실패");
        while (n) {
            if (std::chrono::steady_clock::now() >= until)
                throw Failure("접속 시간 초과");
            if (x.ready(x.socket, true, until)) {
                int err = 0, len = sizeof(err);
                getsockopt(x.socket, SOL_SOCKET, SO_ERROR, (char *)&err, &len);
                if (err)
                    throw Failure("접속 거절");
                break;
            }
        }
    }
    x.lastRx = x.lastTx = std::chrono::steady_clock::now();
    x.sink.info(x.test, x.config.tcpConnects(x.c) ? "TCP_CONNECTED" : "TCP_ACCEPTED");
}
std::uintptr_t Session::acceptPeer(Tick deadline) {
    auto &x = *impl_;
    while (std::chrono::steady_clock::now() < deadline) {
        if (!x.ready(x.listener, false, deadline))
            continue;
        auto s = ::accept(x.listener, nullptr, nullptr);
        if (s != INVALID_SOCKET) {
            x.nonblocking(s);
            return std::uintptr_t(s);
        }
    }
    throw Failure("시험대상 접속 대기 시간 초과");
}
void Session::adopt(std::uintptr_t s) {
    impl_->socket = SOCKET(s);
    impl_->nonblocking(impl_->socket);
    impl_->lastRx = impl_->lastTx = std::chrono::steady_clock::now();
    impl_->sink.info(impl_->test, "TCP_ACCEPTED");
}
PacketRecord Session::send(Pdu p) {
    auto &x = *impl_;
    auto m = packet(x.config, std::move(p), x.serial++);
    auto b = encode(m.get());
    try { x.sendRaw(b); }
    catch (...) {
        x.transportUsable = false;
        auto failed = record(m.get(), b, std::chrono::steady_clock::now());
        failed.sessionId = x.sessionId; failed.sendCompleted = false; failed.sentBytes = x.lastAttemptBytes;
        observe(x.sink, x.test, false, m.get(), failed); throw;
    }
    auto r = record(m.get(), b, x.lastTx);
    r.sessionId = x.sessionId; r.sentBytes = x.lastAttemptBytes;
    observe(x.sink, x.test, false, m.get(), r);
    x.sink.info(x.test, "TX packet=" + std::to_string(r.number) + " type=" + std::to_string(m->pdu->present));
    return r;
}
void Session::resend(const PacketRecord &r) {
    try { impl_->sendRaw(r.wire); }
    catch (...) {
        impl_->transportUsable = false;
        auto failed = r; failed.received = std::chrono::steady_clock::now(); failed.retransmitted = true;
        failed.sendCompleted = false; failed.sentBytes = impl_->lastAttemptBytes;
        auto wire = r.wire; auto m = decode(wire); observe(impl_->sink, impl_->test, false, m.get(), failed); throw;
    }
    if (impl_->sink.packet) {
        Bytes bytes = r.wire;
        auto m = decode(bytes);
        auto transmitted = r;
        transmitted.received = impl_->lastTx;
        transmitted.retransmitted = true;
        transmitted.sentBytes = impl_->lastAttemptBytes;
        observe(impl_->sink, impl_->test, false, m.get(), transmitted);
    }
    impl_->sink.info(impl_->test, "TX identical retry packet=" + std::to_string(r.number));
    userInfo(impl_->sink, impl_->test, "진행", "응답을 확인하지 못해 같은 메시지를 재전송했습니다. 대상의 대응 응답을 다시 기다립니다.");
}
Received Session::receive(Tick deadline, bool maintain) {
    auto &x = *impl_;
    for (;;) {
        x.check();
        auto now = std::chrono::steady_clock::now();
        size_t n = 0;
        try { n = frameSize(x.buffer); } catch (...) { x.transportUsable = false; x.observeUndecoded(x.buffer); throw; }
        if (n) {
            const bool late = x.active && maintain && x.bufferedAt - x.lastRx > std::chrono::seconds(x.config.heartbeat);
            Bytes raw(x.buffer.begin(), x.buffer.begin() + n);
            x.buffer.erase(x.buffer.begin(), x.buffer.begin() + n);
            Packet m(nullptr, Iso14827C2CAuthMsg_del);
            try { m = decode(raw); } catch (...) { x.transportUsable = false; x.observeUndecoded(raw); throw; }
            auto rec = record(m.get(), raw, x.bufferedAt);
            rec.sessionId = x.sessionId;
            observe(x.sink, x.test, true, m.get(), rec);
            if (late) { x.active = false; throw Failure("HeartbeatDurationMax 초과 후 데이터 수신"); }
            x.lastRx = x.bufferedAt;
            if (m->hdrOpt && m->hdrOpt->sender && utf8Text(m->hdrOpt->sender) != x.config.peerDomain)
                throw Failure("상대 도메인 불일치");
            if (m->hdrOpt && m->hdrOpt->dest && utf8Text(m->hdrOpt->dest) != x.config.myDomain)
                throw Failure("수신 도메인 불일치");
            x.sink.info(x.test, "RX packet=" + std::to_string(rec.number) +
                                    " type=" + std::to_string(m->pdu->present));
            return {std::move(m), std::move(rec)};
        }
        if (x.active && maintain && now - x.lastRx > std::chrono::seconds(x.config.heartbeat)) {
            x.active = false;
            throw Failure("HeartbeatDurationMax 초과: 세션 무수신");
        }
        if (now >= deadline)
            throw Failure("응답/관찰 시간 초과");
        if (x.active && maintain && x.hb && x.c.role == Role::Client &&
            now - x.lastTx >= std::chrono::milliseconds(std::uint64_t(x.config.heartbeat) * 1000 / 3)) {
            auto r = send(fred());
            x.pendingEcho.insert(r.number);
        }
        if (!x.ready(x.socket, false, deadline))
            continue;
        unsigned char b[8192];
        int got = recv(x.socket, (char *)b, sizeof(b), 0);
        if (got == 0) { x.transportUsable = false; x.observeUndecoded(x.buffer); throw Failure("CONNECTION_CLOSED"); }
        if (got < 0) {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
                continue;
            x.transportUsable = false;
            throw Failure("소켓 수신 실패");
        }
        x.bufferedAt = std::chrono::steady_clock::now();
        x.buffer.insert(x.buffer.end(), b, b + got);
        if (x.buffer.size() > 8 * 1024 * 1024)
            throw Failure("수신 버퍼 제한");
    }
}
void Session::established(bool yes) {
    impl_->active = yes;
}
void Session::heartbeat(bool yes) {
    impl_->hb = yes;
}
Tick Session::lastReceive() const {
    return impl_->lastRx;
}
Tick Session::lastTransmit() const {
    return impl_->lastTx;
}
void Session::alive(unsigned count) {
    auto &x = *impl_;
    userInfo(x.sink, x.test, "절차", "연결 확인 메시지(FrED) " + std::to_string(count) + "회 교환으로 연결 유지를 확인합니다.");
    for (unsigned i = 0; i < count;) {
        auto end = std::chrono::steady_clock::now() + std::chrono::seconds(x.config.heartbeat);
        unsigned request = 0;
        if (x.c.role == Role::Client)
            request = send(fred()).number;
        for (;;) {
            auto r = receive(end);
            auto p = r.message->pdu;
            if (p->present != Iso14827PDUsPresent_fred)
                throw Failure("FrED 유지 중 예상하지 않은 메시지");
            if (x.c.role == Role::Server && p->x.fred == 0) {
                send(fred(r.message->pktNbr));
                ++i;
                break;
            }
            if (x.c.role == Role::Client && p->x.fred == request) {
                ++i;
                break;
            }
            if (p->x.fred == 0)
                send(fred(r.message->pktNbr));
        }
    }
    userInfo(x.sink, x.test, "확인", "연결 확인 메시지 " + std::to_string(count) + "회 교환을 완료했습니다.");
}
void Session::closeGracefully() {
    auto &x = *impl_;
    x.closing = true;
    x.hb = false;
    userInfo(x.sink, x.test, "절차", "상대와 종료 메시지를 교환해 연결을 정리합니다. 응답이 없으면 같은 종료 메시지를 한 번 재전송합니다.");
    auto p = pdu(x.c.role == Role::Client ? Iso14827PDUsPresent_logout : Iso14827PDUsPresent_term);
    if (x.c.role == Role::Client) p->x.logout = Iso14827Logout_clientRequested;
    else p->x.term = Iso14827Terminate_serverRequested;
    const auto sent = send(std::move(p));
    for (unsigned attempt = 0; attempt < 2; ++attempt) {
        auto end = std::chrono::steady_clock::now() + std::chrono::seconds(x.config.response);
        try {
            for (;;) {
                auto r = receive(end);
                auto reply = r.message->pdu;
                if (x.c.role == Role::Client && reply->present == Iso14827PDUsPresent_fred && reply->x.fred == sent.number) {
                    x.active = false;
                    return;
                }
                if (x.c.role == Role::Server) {
                    if (reply->present == Iso14827PDUsPresent_nak && reply->x.nak && reply->x.nak->type &&
                        reply->x.nak->type->present == Iso14827RejectTypePresent_pubData)
                        throw Failure("Publication 종료 중 rejectPublicationData 수신");
                    if (reply->present == Iso14827PDUsPresent_logout) {
                        if (reply->x.logout != Iso14827Logout_serverRequested) throw Failure("Logout 종료 사유 불일치");
                        send(fred(r.message->pktNbr));
                        x.active = false;
                        return;
                    }
                }
                if (reply->present == Iso14827PDUsPresent_fred && !reply->x.fred) send(fred(r.message->pktNbr));
            }
        } catch (const Failure &e) {
            if (std::string(e.what()) != "응답/관찰 시간 초과" || attempt) throw;
            resend(sent);
        }
    }
}
void Session::closeAfterFailure() {
    auto &x = *impl_;
    // ISO 7.4.3 forbids further exchange after the maximum no-receive period.
    const bool healthy = x.active && x.transportUsable && x.socket != INVALID_SOCKET &&
        std::chrono::steady_clock::now() - x.lastRx < std::chrono::seconds(x.config.heartbeat);
    if (!x.stop.load() && healthy && !x.closing) {
        userInfo(x.sink, x.test, "진행", "시험 조건을 충족하지 못했습니다. 원래 실패 사유를 유지하고, 통신 가능한 세션의 종료 절차를 진행합니다.");
        try {
            closeGracefully();
            userInfo(x.sink, x.test, "확인", "실패 후 종료 메시지 교환을 완료했습니다. 시험 실패 판정은 유지합니다.");
        } catch (const std::exception &e) {
            x.sink.info(x.test, std::string("Failure cleanup: ") + e.what());
            userInfo(x.sink, x.test, "진행", "실패 후 종료 메시지 교환을 완료하지 못해 연결을 정리합니다. 원래 실패 사유를 결과에 유지합니다.");
        }
    } else {
        userInfo(x.sink, x.test, "진행", "추가 종료 메시지 교환 없이 연결을 정리합니다. 연결 상태·무수신 제한·중지 여부와 기존 종료 시도를 반영했습니다.");
    }
    x.active = false;
}
} // namespace datex
