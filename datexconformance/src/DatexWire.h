#pragma once
#include "DatexCore.h"
#include <Iso14827dz1_assist.h>
#include <memory>

namespace datex {
using Pdu = std::unique_ptr<Iso14827PDUs, decltype(&Iso14827PDUs_del)>;
using Packet = std::unique_ptr<Iso14827C2CAuthMsg, decltype(&Iso14827C2CAuthMsg_del)>;
Pdu pdu(Iso14827PDUsPresent type);
Packet packet(const Config &, Pdu, unsigned number);
Bytes encode(Iso14827C2CAuthMsg *);
Packet decode(Bytes &wire);
Bytes privacyWire(Iso14827C2CAuthMsg *, const Bytes &, bool &redacted);
PacketRecord record(Iso14827C2CAuthMsg *, const Bytes &, Tick);
size_t frameSize(const Bytes &);
std::string oidText(Dz1Asn1OID *);
std::string utf8Text(Dz1Asn1UTF8Str *);
std::string octetText(Dz1Asn1OctetStr *);
Pdu initiate(const Config &);
Pdu login(const Config &, const std::string &password);
Pdu fred(unsigned number = 0);
Pdu accept(unsigned packetNumber, Iso14827AcceptTypePresent type, unsigned sid = 0);
Pdu reject(unsigned packetNumber, Iso14827RejectTypePresent type, int reason, unsigned sid = 0,
           unsigned pub = 0);
Pdu subscribe(const Case &, unsigned sid, unsigned period = 0, const std::string &overrideOid = "");
Pdu cancel(unsigned sid);
Pdu publication(const Case &, const Message &, unsigned sid, unsigned serial, const std::string &error = "");
Pdu publicationBundle(const Case &, const std::vector<Message> &, unsigned sid, unsigned serial,
                      const std::string &error = "");
std::vector<Iso14827PublicationData *> publicationData(Iso14827Publication *);
void validatePayload(const Case &, const Message &, Iso14827PublicationData *, const Sink *sink = nullptr,
                     const std::string &test = "");

struct Received {
    Packet message{nullptr, Iso14827C2CAuthMsg_del};
    PacketRecord observation;
};
class Session {
    struct Impl;
    std::unique_ptr<Impl> impl_;

  public:
    Session(const Case &, const Config &, std::atomic<bool> &, const Sink &, const std::string &test);
    ~Session();
    Session(const Session &) = delete;
    void open();
    void openListener();
    void adopt(std::uintptr_t socket);
    std::uintptr_t acceptPeer(Tick deadline);
    PacketRecord send(Pdu);
    void resend(const PacketRecord &);
    Received receive(Tick deadline, bool maintain = true);
    void established(bool yes = true);
    void heartbeat(bool yes);
    void alive(unsigned exchanges = 1);
    void closeGracefully();
    void closeAfterFailure();
    Tick lastReceive() const;
    Tick lastTransmit() const;
};
} // namespace datex
