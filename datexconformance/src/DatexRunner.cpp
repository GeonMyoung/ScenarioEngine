#include "DatexWire.h"
#include "DatexThread.h"
#include "DatexNarrative.h"
#include <algorithm>

namespace datex {
namespace {
Tick after(unsigned seconds) {
    return std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
}
void service(Session &s, Received &r) {
    if (r.message->pdu->present == Iso14827PDUsPresent_fred && r.message->pdu->x.fred == 0)
        s.send(fred(r.message->pktNbr));
}
void verifyRetry(const PacketRecord &first, const PacketRecord &second, unsigned responseSeconds,
                 const Sink &sink, const std::string &test, const std::string &name) {
    auto same = compareRetry(first,second);
    auto timing = compareRetryTiming(first,second,responseSeconds);
    sink.info(test,same.json());
    sink.info(test,"재전송 시간 관측 "+timing.json());
    userInfo(sink,test,"증적", "원본/재전송 패킷 번호 "+std::to_string(first.number)+"/"+std::to_string(second.number)+
        ", 번호 "+(same.number?"일치":"불일치")+", 타임스탬프 "+(same.timestamp?"일치":"불일치")+
        ", 내용 "+(same.content?"일치":"불일치")+". 수신 간격 "+std::to_string(timing.elapsedUs/1000)+
        "ms, 응답 제한시간 "+std::to_string(timing.expectedUs/1000)+"ms, 허용 구간 "+
        std::to_string((timing.expectedUs-timing.earlyAllowanceUs)/1000)+"~"+
        std::to_string((timing.expectedUs+timing.lateAllowanceUs)/1000)+"ms.");
    if(!same.same()) throw Failure(name+" 재전송 동일성 위반");
    if(!timing.within()) throw Failure("재전송 시점이 허용 구간을 벗어났습니다: "+std::to_string(timing.elapsedUs)+"us");
}
Received wanted(Session &s, Tick until, Iso14827PDUsPresent type) {
    for (;;) {
        auto r = s.receive(until);
        if (r.message->pdu->present == type)
            return r;
        if (r.message->pdu->present == Iso14827PDUsPresent_fred) {
            service(s, r);
            continue;
        }
        throw Failure("예상하지 않은 프로토콜 메시지");
    }
}
Received response(Session &s, const PacketRecord &request, unsigned timeout) {
    for (unsigned attempt = 0; attempt < 2; ++attempt) {
        auto until = after(timeout);
        try {
            for (;;) {
                auto r = s.receive(until);
                auto p = r.message->pdu;
                if (p->present == Iso14827PDUsPresent_fred) {
                    service(s, r);
                    continue;
                }
                if (p->present == Iso14827PDUsPresent_ack && p->x.ack && p->x.ack->pktNbr == request.number)
                    return r;
                if (p->present == Iso14827PDUsPresent_nak && p->x.nak && p->x.nak->pktNbr == request.number)
                    return r;
                throw Failure("요청에 대응하지 않는 응답");
            }
        } catch (const Failure &e) {
            if (std::string(e.what()) != "응답/관찰 시간 초과" || attempt)
                throw;
            s.resend(request);
        }
    }
    throw Failure("응답 없음");
}
void accepted(const Received &r, Iso14827AcceptTypePresent type, unsigned sid = 0) {
    auto p = r.message->pdu;
    if (p->present != Iso14827PDUsPresent_ack || !p->x.ack || !p->x.ack->acceptType ||
        p->x.ack->acceptType->present != type)
        throw Failure("유효한 Accept가 필요합니다.");
    if (type == Iso14827AcceptTypePresent_registeredSubscription &&
        p->x.ack->acceptType->x.registeredSubscription != sid)
        throw Failure("Accept 구독 번호 불일치");
    if (type == Iso14827AcceptTypePresent_login && oidText(p->x.ack->acceptType->x.login) != "2.1.1")
        throw Failure("협상된 코덱이 BER이 아닙니다.");
}
void rejected(const Received &r, Iso14827RejectTypePresent type, int reason) {
    auto p = r.message->pdu;
    if (p->present != Iso14827PDUsPresent_nak || !p->x.nak || !p->x.nak->type ||
        p->x.nak->type->present != type)
        throw Failure("실제 Reject 응답이 필요합니다.");
    int got =
        type == Iso14827RejectTypePresent_login ? p->x.nak->type->x.login : p->x.nak->type->x.subscription;
    if (got != reason)
        throw Failure("Reject 사유 불일치: expected=" + std::to_string(reason) +
                      " actual=" + std::to_string(got));
}
void clientOpening(Session &s, const Config &c) {
    if (!c.useInitiate) return;
    auto r = s.receive(after(c.connectTimeout), false);
    if (r.message->pdu->present != Iso14827PDUsPresent_initiate || !r.message->pdu->x.initiate)
        throw Failure("개시요청 사용 설정에서는 Login 전에 Initiate가 필요합니다.");
    auto i = r.message->pdu->x.initiate;
    if (utf8Text(i->sender) != c.peerDomain || utf8Text(i->dest) != c.myDomain)
        throw Failure("Initiate 도메인 불일치");
}
void clientLogin(Session &s, const Config &c) {
    clientOpening(s, c);
    auto req = s.send(login(c, c.password));
    accepted(response(s, req, c.response), Iso14827AcceptTypePresent_login);
    s.established();
}
void duplicateLogin(Session &first, const Case &c, const Config &cfg, std::atomic<bool> &stop,
                    const Sink &sink, const std::string &test, Session *listener) {
    first.alive();
    std::atomic<bool> done{false};
    std::exception_ptr heartbeatError;
    ManagedThread keeper([&] {
        try {
            while (!done.load()) {
                try {
                    auto r = first.receive(std::chrono::steady_clock::now() + std::chrono::milliseconds(100));
                    if (r.message->pdu->present != Iso14827PDUsPresent_fred)
                        throw Failure("중복 로그인 중 첫 세션의 예상하지 않은 메시지");
                    service(first, r);
                } catch (const Failure &e) {
                    if (std::string(e.what()) != "응답/관찰 시간 초과")
                        throw;
                }
            }
        } catch (...) {
            heartbeatError = std::current_exception();
        }
    });
    try {
        Session second(c, cfg, stop, sink, test);
        if (cfg.tcpConnects(c)) second.open();
        else {
            if (!listener) throw Failure("중복 로그인 수신 대기 정보 누락");
            userInfo(sink, test, "절차", "첫 세션을 유지하며 정보제공 측의 두 번째 TCP 접속과 Initiate를 기다립니다.");
            second.adopt(listener->acceptPeer(after(cfg.connectTimeout)));
        }
        clientOpening(second, cfg);
        auto req = second.send(login(cfg, cfg.password));
        rejected(response(second, req, cfg.response), Iso14827RejectTypePresent_login,
                 Iso14827RejectLogin_sessionExist);
    } catch (...) {
        done = true;
        keeper.join();
        throw;
    }
    done = true;
    keeper.join();
    if (heartbeatError)
        std::rethrow_exception(heartbeatError);
    first.alive();
}
void checkLogin(const Received &r, const Config &c) {
    auto l = r.message->pdu->x.login;
    if (!l || utf8Text(l->sender) != c.peerDomain || utf8Text(l->dest) != c.myDomain)
        throw Failure("Login 도메인 불일치");
    if (octetText(l->user) != c.user || octetText(l->pass) != c.password)
        throw Failure("Login 계정 불일치");
    if (l->hbDur != int(c.heartbeat) || l->timeout != int(c.response))
        throw Failure("SUT Login의 H/R이 시험환경 기대값과 다릅니다.");
    const auto expected = c.useInitiate ? Iso14827LoginInitiator_serverInitiated : Iso14827LoginInitiator_clientInitiated;
    if (l->initiator != expected) throw Failure("Login 개시 유형이 선택한 연결 방식과 다릅니다.");
    unsigned count = 0; Dz1Error error = {};
    auto rules = l->encRules ? l->encRules->get_array(l->encRules, &count, &error) : nullptr;
    bool ber = false;
    for (unsigned k = 0; k < count; ++k) if (oidText(rules[k]) == "2.1.1") ber = true;
    Dz1Free(rules);
    if (!ber) throw Failure("Login 인코딩 제안에 지원하는 BER(2.1.1)이 없습니다.");
}
void serverLogin(Session &s, const Config &c, bool retry, const Sink &sink, const std::string &test) {
    if (c.useInitiate) s.send(initiate(c));
    auto first = wanted(s, after(c.connectTimeout), Iso14827PDUsPresent_login);
    try { checkLogin(first, c); }
    catch (const Failure &) {
        s.send(reject(first.message->pktNbr, Iso14827RejectTypePresent_login, Iso14827RejectLogin_other));
        throw;
    }
    userInfo(sink, test, "확인", std::string("Login 개시 유형 ") + (c.useInitiate ? "serverInitiated" : "clientInitiated") + " 및 BER(2.1.1) 제안을 확인했습니다.");
    if (retry) {
        userInfo(sink, test, "절차", "로그인 요청을 받았습니다. 수용 응답을 보류하고 동일한 로그인 요청이 재전송되는지 기다립니다.");
        auto second = wanted(s, after(c.response + 2), Iso14827PDUsPresent_login);
        verifyRetry(first.observation,second.observation,c.response,sink,test,"Login");
        userInfo(sink, test, "확인", "로그인 재전송의 번호·시각·전체 내용이 원본과 일치합니다. 수용 응답을 보냅니다.");
        s.send(accept(second.message->pktNbr, Iso14827AcceptTypePresent_login));
    } else
        s.send(accept(first.message->pktNbr, Iso14827AcceptTypePresent_login));
    s.established();
}
unsigned checkSubscription(Session &s, const Received &req, const Case &c, const Sink &sink, const std::string &test) {
    auto refuse = [&](int reason, const std::string &why) {
        s.send(reject(req.message->pktNbr,Iso14827RejectTypePresent_subscription,reason));
        userInfo(sink,test,"거부 응답", "잘못된 정보요청에 거부 응답을 보냈습니다. 대응 패킷 번호 "+
            std::to_string(req.message->pktNbr)+", 사유 "+std::string(Iso14827RejectSubscriptionStrA((Iso14827RejectSubscription)reason))+". "+why);
        throw Failure(why);
    };
    auto sub=req.message->pdu->x.subscription;
    if(!sub || !sub->serial || !sub->type || sub->type->present!=Iso14827SubscriptionTypePresent_data)
        refuse(Iso14827RejectSubscription_invalidSubscriptionContent,"Subscription 형식 오류");
    auto d=sub->type->x.data;
    if(!d || !d->msg || !d->msg->oid || !d->guarantee)
        refuse(Iso14827RejectSubscription_invalidSubscriptionContent,"Subscription 필수 내용/Guarantee 조건 불일치");
    if(oidText(d->msg->oid)!=c.oid)
        refuse(Iso14827RejectSubscription_unknownSubscriptionMsgId,"지원하지 않는 Subscription OID");
    if(d->fmt!=Iso14827SubscriptionDataFormat_dataPacket)
        refuse(Iso14827RejectSubscription_publishFormatNotSupported,"Subscription 데이터 패킷 형식 불일치");
    if(!d->mode || d->mode->present!=Iso14827SubscriptionDataModePresent_single)
        refuse(Iso14827RejectSubscription_invalidMode,"Subscription 단일 정보요청 모드 불일치");
    return sub->serial;
}
unsigned serverSubscription(Session &s, const Case &c, const Config &cfg, bool retry, const Sink &sink,
                            const std::string &test) {
    userInfo(sink, test, "절차", "대상의 정보요청을 기다립니다. 단일 제공 요청, 연계정보 식별자와 수신 확인 요구 조건을 확인합니다.");
    auto req = wanted(s, after(cfg.connectTimeout), Iso14827PDUsPresent_subscription);
    unsigned sid = checkSubscription(s,req,c,sink,test);
    if (retry) {
        userInfo(sink, test, "절차", "정보요청을 받았습니다. 수용 응답을 보류하고 동일한 요청의 재전송을 기다립니다.");
        auto second = wanted(s, after(cfg.response + 2), Iso14827PDUsPresent_subscription);
        checkSubscription(s,second,c,sink,test);
        try { verifyRetry(req.observation,second.observation,cfg.response,sink,test,"Subscription"); }
        catch(const Failure &) {
            s.send(reject(second.message->pktNbr,Iso14827RejectTypePresent_subscription,
                Iso14827RejectSubscription_invalidSubscriptionContent));
            userInfo(sink,test,"거부 응답","재전송 조건을 충족하지 못한 정보요청에 거부 응답을 보냈습니다.");
            throw;
        }
        userInfo(sink, test, "확인", "정보요청 재전송의 번호·시각·전체 내용이 원본과 일치합니다. 수용 응답을 보냅니다.");
        s.send(accept(second.message->pktNbr, Iso14827AcceptTypePresent_singleSubscription));
    } else
        s.send(accept(req.message->pktNbr, Iso14827AcceptTypePresent_singleSubscription));
    userInfo(sink, test, "확인", "정보요청 조건을 확인하고 수용했습니다. 구독번호 " + std::to_string(sid) + "로 제공 정보와 요청을 대응합니다.");
    return sid;
}
std::vector<Iso14827PublicationData *> checkPublication(Session &s, const Received &r, const Case &c,
                                                        const Message &m, unsigned sid, bool validate = true,
                                                        bool acknowledge = true, const Sink *sink = nullptr,
                                                        const std::string &test = "") {
    auto pub = r.message->pdu->x.publication;
    if (!pub || !pub->guaranteed)
        throw Failure("Publication Guarantee=true가 필요합니다.");
    std::vector<Iso14827PublicationData *> data;
    try {
        data = publicationData(pub);
    } catch (...) {
        s.send(reject(r.message->pktNbr, Iso14827RejectTypePresent_publication,
                      Iso14827RejectPublication_invalidPublishFormat));
        throw;
    }
    if (acknowledge)
        s.send(accept(r.message->pktNbr, Iso14827AcceptTypePresent_publication));
    for (auto d : data) {
        if (d->subscriptionSerial != sid) {
            s.send(reject(0, Iso14827RejectTypePresent_pubData,
                          Iso14827RejectPubDataReason_unknownSubscription, d->subscriptionSerial, d->serial));
            throw Failure("Publication 구독 번호 불일치");
        }
        if (validate)
            try {
                validatePayload(c, m, d, sink, test);
            } catch (...) {
                s.send(reject(0, Iso14827RejectTypePresent_pubData,
                              Iso14827RejectPubDataReason_invalidPublicationMsgContent, d->subscriptionSerial,
                              d->serial));
                throw;
            }
    }
    return data;
}
void clientNormal(Session &s, const Case &c, const Config &cfg, const Message &m, bool retry,
                  const Sink &sink, const std::string &test) {
    const unsigned sid = 1;
    userInfo(sink, test, "절차", messageLabel(m.name) + "의 단일 제공을 요청하고 수용 응답을 기다립니다.");
    auto req = s.send(subscribe(messageCase(c, m), sid));
    accepted(response(s, req, cfg.response), Iso14827AcceptTypePresent_singleSubscription);
    userInfo(sink, test, "절차", "정보요청이 수용되었습니다. " + messageLabel(m.name) + "를 수신하여 메시지 식별정보와 ASN.1 디코딩을 확인합니다.");
    auto first = wanted(s, after(cfg.response), Iso14827PDUsPresent_publication);
    checkPublication(s, first, c, m, sid, true, !retry, retry ? nullptr : &sink, test);
    userInfo(sink, test, "확인", messageLabel(m.name) + "를 수신했고 메시지 식별·내용의 ASN.1 디코딩을 완료했습니다. 수신 전문 " + std::to_string(first.observation.wire.size()) + "바이트, 구독번호 " + std::to_string(sid) + ".");
    if (retry) {
        userInfo(sink, test, "절차", "정보제공 수용 응답을 보류했습니다. 대상이 같은 정보를 재전송하는지 기다립니다.");
        auto second = wanted(s, after(cfg.response + 2), Iso14827PDUsPresent_publication);
        verifyRetry(first.observation,second.observation,cfg.response,sink,test,"Publication");
        checkPublication(s, second, c, m, sid);
        userInfo(sink, test, "확인", "정보제공 재전송의 번호·시각·전체 내용이 원본과 일치합니다. 수용 응답을 보냈습니다.");
    }
    s.alive();
}
void cancelTest(Session &s, const Case &c, const Config &cfg, const Sink &sink, const std::string &test) {
    const unsigned sid = 1;
    userInfo(sink, test, "절차", messageLabel(c.messages.front().name) + "의 주기 제공을 요청합니다. 요청 주기 " + std::to_string(cfg.period) + "초, 취소 전 관찰 " + std::to_string(cfg.receive) + "초입니다.");
    auto req = s.send(subscribe(c, sid, cfg.period));
    accepted(response(s, req, cfg.response), Iso14827AcceptTypePresent_registeredSubscription, sid);
    auto start = std::chrono::steady_clock::now(), end = start + std::chrono::seconds(cfg.receive);
    PeriodTracker periods(cfg.period, true);
    std::map<unsigned, PacketRecord> seen;
    auto nextProgress = start + std::chrono::seconds(30);
    bool echo = false;
    while (std::chrono::steady_clock::now() < end) {
        auto now = std::chrono::steady_clock::now();
        if (now >= nextProgress) {
            userInfo(sink, test, "진행", "주기 제공 관찰 " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now - start).count()) + "/" + std::to_string(cfg.receive) + "초 경과. 새 정보 " + std::to_string(periods.count()) + "회 수신·디코딩 확인.");
            nextProgress = now + std::chrono::seconds(30);
        }
        try {
            auto r = s.receive(std::min(end, after(1)));
            if (r.message->pdu->present == Iso14827PDUsPresent_fred) {
                service(s, r);
                continue;
            }
            if (r.message->pdu->present != Iso14827PDUsPresent_publication)
                throw Failure("주기 수신 중 예상하지 않은 메시지");
            checkPublication(s, r, c, c.messages.front(), sid);
            auto prev = seen.find(r.observation.number);
            bool duplicate = prev != seen.end();
            if (duplicate && !compareRetry(prev->second, r.observation).same())
                throw Failure("동일 번호의 내용이 변경됨");
            periods.receive(r.observation.received, duplicate);
            seen[r.observation.number] = r.observation;
            if (seen.size() > 256)
                seen.erase(seen.begin());
        } catch (const Failure &e) {
            if (std::string(e.what()) != "응답/관찰 시간 초과")
                throw;
        }
        if (periods.overdue(std::chrono::steady_clock::now()))
            throw Failure("Publication 주기 상한 초과/발행 누락");
    }
    if (!periods.sufficient())
        throw Failure("정상 Publication 최소 2회/주기 증거 부족");
    sink.info(test, "취소 전 정상 발행 수=" + std::to_string(periods.count()));
    userInfo(sink, test, "확인", "취소 전 " + std::to_string(cfg.receive) + "초 동안 새 정보 " + std::to_string(periods.count()) + "회의 수신·디코딩과 주기 조건을 확인했습니다.");
    userInfo(sink, test, "절차", "구독 취소를 요청하고 취소 수용 응답을 기다립니다.");
    auto cancellation = s.send(cancel(sid));
    Tick cancelAccepted{};
    auto until = after(cfg.response * 2);
    bool retried = false;
    while (cancelAccepted == Tick{}) {
        try {
            auto r = s.receive(std::min(until, after(cfg.response)));
            auto p = r.message->pdu;
            if (p->present == Iso14827PDUsPresent_publication) {
                s.send(accept(r.message->pktNbr, Iso14827AcceptTypePresent_publication));
                seen[r.observation.number] = r.observation;
                if (seen.size() > 256)
                    seen.erase(seen.begin());
                sink.info(test, "취소 수용 전 Publication: 내용 처리 제외");
                continue;
            }
            if (p->present == Iso14827PDUsPresent_fred) {
                service(s, r);
                continue;
            }
            if (p->present != Iso14827PDUsPresent_ack || p->x.ack->pktNbr != cancellation.number)
                throw Failure("취소 수용 응답 불일치");
            auto type = p->x.ack->acceptType->present;
            if (type != Iso14827AcceptTypePresent_singleSubscription &&
                type != Iso14827AcceptTypePresent_registeredSubscription)
                throw Failure("취소 응답 종류 불일치");
            cancelAccepted = r.observation.received;
        } catch (const Failure &e) {
            if (std::string(e.what()) != "응답/관찰 시간 초과" || retried)
                throw;
            retried = true;
            s.resend(cancellation);
        }
    }
    userInfo(sink, test, "절차", "구독 취소가 수용되었습니다. 이후 " + std::to_string(cfg.period) + "초 동안 새 정보 제공이 중단되는지 관찰합니다. 취소 이전 정보의 동일 재전송은 새 제공으로 세지 않습니다.");
    end = cancelAccepted + std::chrono::seconds(cfg.period);
    while (std::chrono::steady_clock::now() < end) {
        try {
            auto r = s.receive(std::min(end, after(1)));
            auto p = r.message->pdu;
            if (p->present == Iso14827PDUsPresent_fred) {
                service(s, r);
                echo = true;
                continue;
            }
            if (p->present != Iso14827PDUsPresent_publication)
                throw Failure("취소 후 예상하지 않은 메시지");
            auto items = publicationData(p->x.publication);
            for (auto d : items) {
                if (d->subscriptionSerial != sid)
                    continue;
                auto prev = seen.find(r.observation.number);
                if (prev == seen.end() || !compareRetry(prev->second, r.observation).same())
                    throw Failure("취소 수용 후 새로운 Publication 수신");
                sink.info(test, "취소 전 패킷의 동일 재전송: 업무 처리 제외");
            }
            s.send(accept(r.message->pktNbr, Iso14827AcceptTypePresent_publication));
        } catch (const Failure &e) {
            if (std::string(e.what()) != "응답/관찰 시간 초과")
                throw;
        }
    }
    /* An explicit exchange also guards against stale/pre-cancel heartbeat events. */
    userInfo(sink, test, "확인", "취소 수용 후 한 주기 동안 새 정보 제공이 없었습니다.");
    s.alive();
}
int errorReason(const std::string &t) {
    if (t == "unknownSubscription")
        return Iso14827RejectPubDataReason_unknownSubscription;
    if (t == "unknownPublicationNbr")
        return Iso14827RejectPubDataReason_unknownPublicationNbr;
    if (t == "unknownPublicationMsgId")
        return Iso14827RejectPubDataReason_unknownPublicationMsgId;
    if (t == "invalidPublicationMsgId")
        return Iso14827RejectPubDataReason_invalidPublicationMsgId;
    if (t == "invalidPublicationMsgContent")
        return Iso14827RejectPubDataReason_invalidPublicationMsgContent;
    if (t == "repeatedPublicationNbr")
        return Iso14827RejectPubDataReason_repeatedPublicationNbr;
    throw Failure("오류 시험명 불일치");
}
void observePublicationAcceptance(Session &s, const Config &cfg, const Received &ack,
                                  unsigned sid, const Sink &sink, const std::string &test) {
    // A bounded absence check, using the configured response timeout. FrED alone
    // must not end the observation before a delayed application rejection arrives.
    const auto end = ack.observation.received + std::chrono::seconds(cfg.response);
    bool maintained = false;
    userInfo(sink, test, "절차", "Publication의 Accept를 확인했습니다. 연결을 유지하며 " +
        std::to_string(cfg.response) + "초 동안 rejectPublicationData가 발생하는지 관찰합니다. 구독번호 " +
        std::to_string(sid) + ", 발행번호 1.");
    while (std::chrono::steady_clock::now() < end) {
        try {
            auto r = s.receive(end);
            auto p = r.message->pdu;
            if (p->present == Iso14827PDUsPresent_fred) {
                service(s, r);
                if (p->x.fred == 0) maintained = true;
                continue;
            }
            if (p->present == Iso14827PDUsPresent_nak && p->x.nak && p->x.nak->type &&
                p->x.nak->type->present == Iso14827RejectTypePresent_pubData) {
                auto d = p->x.nak->type->x.pubData;
                throw Failure("정상 정보에 대한 rejectPublicationData 수신: 구독번호 " +
                    std::to_string(d ? d->subSerial : 0) + ", 발행번호 " +
                    std::to_string(d ? d->pubSerial : 0) + ", 거부 사유 " +
                    std::to_string(d ? d->reason : -1));
            }
            throw Failure("정상 Publication 수용 후 예상하지 않은 프로토콜 메시지");
        } catch (const Failure &e) {
            if (std::string(e.what()) != "응답/관찰 시간 초과") throw;
        }
    }
    if (!maintained) s.alive();
    userInfo(sink, test, "확인", "수신 확인 응답 이후 관찰 구간에서 rejectPublicationData가 없고 연결이 유지되었습니다. 이어서 정상 종료 절차까지 확인합니다.");
}
void serverInvalid(Session &s, const Case &c, const Config &cfg, const std::string &test, const Sink &sink) {
    auto sid = serverSubscription(s, c, cfg, false, sink, test);
    unsigned serial = 1;
    if (test == "repeatedPublicationNbr") {
        auto first = s.send(publication(c, c.messages.front(), sid, serial));
        accepted(response(s, first, cfg.response), Iso14827AcceptTypePresent_publication);
    }
    userInfo(sink, test, "절차", rejectionMeaning(test) + "를 의도적으로 제공합니다. 대상의 수신 확인 응답과 오류에 대응하는 거부 응답을 기다립니다.");
    auto sent = s.send(publication(c, c.messages.front(), sid, serial, test));
    auto end = after(cfg.response * 2);
    bool gotReject = false, acked = false;
    bool retry = false;
    while (!gotReject || !acked) {
        Received r;
        try {
            r = s.receive(retry || acked ? end : std::min(end, after(cfg.response)));
        } catch (const Failure &e) {
            if (std::string(e.what()) != "응답/관찰 시간 초과" || retry || acked)
                throw;
            retry = true;
            s.resend(sent);
            continue;
        }
        auto p = r.message->pdu;
        if (p->present == Iso14827PDUsPresent_fred) {
            service(s, r);
            continue;
        }
        if (p->present == Iso14827PDUsPresent_ack) {
            if (p->x.ack->pktNbr != sent.number)
                throw Failure("발행 ACK 번호 불일치");
            accepted(r, Iso14827AcceptTypePresent_publication);
            acked = true;
            continue;
        }
        if (p->present != Iso14827PDUsPresent_nak || !p->x.nak || !p->x.nak->type ||
            p->x.nak->type->present != Iso14827RejectTypePresent_pubData)
            throw Failure("PublicationData Reject가 필요합니다.");
        auto d = p->x.nak->type->x.pubData;
        if (p->x.nak->pktNbr != 0 || !d ||
            d->subSerial != (test == "unknownSubscription" ? sid + 999 : sid) ||
            d->pubSerial != (test == "unknownPublicationNbr" ? 999 : serial) ||
            d->reason != errorReason(test))
            throw Failure("Publication 거부 식별자/사유 불일치");
        userInfo(sink, test, "확인", "대상이 해당 오류 사유로 거부했습니다. 거부 응답의 구독번호·발행번호가 시험 정보에 대응합니다.");
        gotReject = true;
    }
    s.alive();
}
} // namespace
std::vector<Result> run(const Case &c, const Config &cfg, std::atomic<bool> &stop, const Sink &sink) {
    std::vector<Result> results;
    // Keep queued reconnects alive between independently evaluated server sessions.
    std::unique_ptr<Session> listener;
    unsigned selectedIndex = 0;
    for (const auto &test : availableTests(c)) {
        if (!cfg.tests.count(test))
            continue;
        if (stop.load())
            break;
        std::string stage = "접속";
        Sink itemSink = sink;
        itemSink.userInfo = [&](const std::string &key, const std::string &phase, const std::string &text) {
            if (phase == "절차") stage = text;
            userInfo(sink, key, phase, text);
        };
        const auto &progress = itemSink;
        sink.state("test_" + test, "START");
        userInfo(progress, test, "시험 시작", std::to_string(++selectedIndex) + "/" + std::to_string(cfg.tests.size()) + " · " + testTitle(c, test));
        userInfo(progress, test, "확인 기준", testCriteria(c, cfg, test));
        sink.info(test, "신규 시험 시작: " + std::string(c.id) + " / " + test + " (독립 세션)");
        Result result{test, Verdict::Pass, "프로토콜 조건 확인"};
        bool connected = false;
        std::unique_ptr<Session> session;
        try {
            userInfo(progress, test, "절차", cfg.tcpConnects(c) ? "시험 시스템이 대상 " + cfg.host + ":" + std::to_string(cfg.port) + "에 접속합니다. 접속 제한 " + std::to_string(cfg.connectTimeout) + "초." : "시험 시스템이 포트 " + std::to_string(cfg.port) + "에서 대상의 접속을 기다립니다. 접속 대기 " + std::to_string(cfg.connectTimeout) + "초.");
            session.reset(new Session(c, cfg, stop, progress, test));
            auto &s = *session;
            if (!cfg.tcpConnects(c)) {
                if (!listener) {
                    listener.reset(new Session(c, cfg, stop, sink, test));
                    listener->openListener();
                }
                s.adopt(listener->acceptPeer(after(cfg.connectTimeout)));
            } else {
                s.open();
            }
            connected = true;
            userInfo(progress, test, "확인", "시험 대상과 TCP 연결이 성립했습니다.");
            userInfo(progress, test, "절차", cfg.useInitiate
                ? "개시요청 사용: 정보제공 측(ISO Server)이 TCP에 접속한 뒤 Initiate → 정보요청 측(ISO Client)의 Login(serverInitiated) → Accept 순서로 시작합니다."
                : "일반 연결: 정보요청 측(ISO Client)이 TCP에 접속한 뒤 Login(clientInitiated) → 정보제공 측(ISO Server)의 Accept 순서로 시작합니다.");
            if (c.role == Role::Client) {
                if (test == "invalid_login") {
                    userInfo(progress, test, "절차", "잘못된 비밀번호로 로그인을 시도합니다. 비밀번호 오류 사유의 거부 응답이 정상적인 시험 결과입니다.");
                    clientOpening(s, cfg);
                    auto sent = s.send(login(cfg, cfg.invalidPassword));
                    rejected(response(s, sent, cfg.response), Iso14827RejectTypePresent_login,
                             Iso14827RejectLogin_invalidPassword);
                } else {
                    userInfo(progress, test, "절차", "로그인을 요청하고 수용 응답과 통신 인코딩 합의를 확인합니다.");
                    clientLogin(s, cfg);
                    userInfo(progress, test, "확인", "로그인이 수용되었습니다. 연결 확인 메시지 교환을 진행할 수 있습니다.");
                    if (test == "session")
                        s.alive(2);
                    else if (test == "duplicate_login") {
                        userInfo(progress, test, "절차", "기존 연결을 유지하면서 두 번째 연결로 같은 계정의 로그인을 시도합니다. 중복 세션 거부와 기존 연결 유지를 확인합니다.");
                        duplicateLogin(s, c, cfg, stop, progress, test, listener.get());
                    } else if (test == "invalid_subscription") {
                        userInfo(progress, test, "절차", "지원하지 않는 정보 식별자로 요청합니다. 해당 식별자 오류에 대한 거부 응답을 기다립니다.");
                        auto req = s.send(subscribe(c, 1, 0, "1.0.15784.99.99.99"));
                        auto r = response(s, req, cfg.response);
                        auto p = r.message->pdu;
                        if (p->present != Iso14827PDUsPresent_nak ||
                            p->x.nak->type->present != Iso14827RejectTypePresent_subscription)
                            throw Failure("Subscription Reject 필요");
                        auto why = p->x.nak->type->x.subscription;
                        if (why != Iso14827RejectSubscription_unknownSubscriptionMsgId &&
                            why != Iso14827RejectSubscription_invalidSubscriptionMsgId)
                            throw Failure("Subscription 거부 사유 불일치");
                        s.alive();
                    } else if (test == "publication_retry")
                        clientNormal(s, c, cfg, c.messages.front(), true, progress, test);
                    else if (test == "cancel")
                        cancelTest(s, c, cfg, progress, test);
                    else if (test == "abnormal_session") {
                        s.alive();
                        userInfo(progress, test, "절차", "연결 확인 메시지를 교환하며 " + std::to_string(cfg.maintain) + "초 동안 정상 연결을 유지합니다.");
                        if (cfg.maintain < 300) userInfo(progress, test, "시험 조건", "설정한 유지시간이 시험방법의 300초보다 짧습니다. 이번 실행은 해당 최소 유지시간 충족 증적으로 사용할 수 없습니다.");
                        auto maintainStart = std::chrono::steady_clock::now();
                        auto nextProgress = maintainStart + std::chrono::seconds(30);
                        auto end = after(cfg.maintain);
                        while (std::chrono::steady_clock::now() < end) {
                            auto now = std::chrono::steady_clock::now();
                            if (now >= nextProgress) {
                                userInfo(progress, test, "진행", "정상 연결 유지 " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now - maintainStart).count()) + "/" + std::to_string(cfg.maintain) + "초 경과. 연결 확인 메시지 교환을 계속 관찰합니다.");
                                nextProgress = now + std::chrono::seconds(30);
                            }
                            try {
                                auto r = s.receive(std::min(end, after(1)));
                                if (r.message->pdu->present != Iso14827PDUsPresent_fred)
                                    throw Failure("정상 유지 중 예상하지 않은 메시지");
                                service(s, r);
                            } catch (const Failure &e) {
                                if (std::string(e.what()) != "응답/관찰 시간 초과")
                                    throw;
                            }
                        }
                        s.alive();
                        userInfo(progress, test, "확인", "설정한 정상 연결 유지 구간을 완료했습니다.");
                        userInfo(progress, test, "절차", "시험 시스템의 송신을 중단합니다. 최대 무수신 시간 " + std::to_string(cfg.heartbeat) + "초가 지난 뒤 대상이 연결을 종료하는지 관찰합니다. 관찰 기한은 송신 중단 후 " + std::to_string(cfg.heartbeat + cfg.response) + "초입니다. 시험 시스템이 먼저 종료하지 않습니다.");
                        auto silence = s.lastTransmit();
                        const auto lastNormalReceive = s.lastReceive();
                        const auto observationEnd = silence + std::chrono::seconds(cfg.heartbeat + cfg.response);
                        s.heartbeat(false);
                        s.established(false); // Observation requires silence, including on a failed observation.
                        bool closed = false;
                        Tick observedAt{};
                        while (!closed) {
                            try {
                                auto r = s.receive(
                                    observationEnd, false);
                                throw Failure("무수신 종료 중 추가 데이터 교환 발생");
                            } catch (const Failure &e) {
                                if (std::string(e.what()) == "응답/관찰 시간 초과") {
                                    observedAt = std::chrono::steady_clock::now();
                                    break;
                                }
                                if (std::string(e.what()) != "CONNECTION_CLOSED")
                                    throw;
                                observedAt = std::chrono::steady_clock::now();
                                if (observedAt - silence <
                                    std::chrono::seconds(cfg.heartbeat))
                                    throw Failure("H 경과 전 조기 연결 종료");
                                if (observedAt > observationEnd)
                                    throw Failure("관찰 기한 경과 후 연결 종료");
                                closed = true;
                            }
                        }
                        const auto micros = [](Tick time) { return std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count(); };
                        const auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(observedAt - silence).count();
                        result.observationsJson = "{\"silenceStartedAtUs\":" + std::to_string(micros(silence)) +
                            ",\"lastNormalReceiveAtUs\":" + std::to_string(micros(lastNormalReceive)) +
                            ",\"observedAtUs\":" + std::to_string(micros(observedAt)) +
                            ",\"elapsedMilliseconds\":" + std::to_string(elapsedMs) +
                            ",\"heartbeatSeconds\":" + std::to_string(cfg.heartbeat) +
                            ",\"observationLimitSeconds\":" + std::to_string(cfg.heartbeat + cfg.response) +
                            ",\"tcpClosed\":" + (closed ? "true" : "false") + "}";
                        sink.info(test, "무수신 종료 관측 " + result.observationsJson);
                        result.verdict = Verdict::Pass;
                        result.detail = closed
                            ? "송신 중단 후 " + std::to_string(elapsedMs) + "ms에 대상 TCP 종료 관측. H 이상 및 H+R 이내 종료 조건 충족"
                            : "정상 유지·송신 중단·관찰 절차 완료. TCP 종료 미관측 사실을 기록하고 사후 제출 절차 없이 정상 시험 완료로 성공 처리";
                        userInfo(progress, test, "확인", closed
                            ? "송신 중단 후 " + std::to_string(elapsedMs) + "ms에 대상이 연결을 종료했습니다. 최대 무수신 시간 이후이며 관찰 기한 이내입니다. 시험 기준에 따라 적합입니다."
                            : "설정한 정상 유지·송신 중단·관찰 절차를 완료했습니다. TCP 연결 종료는 관측되지 않았으며 이 사실을 결과에 기록합니다. 별도 자료 제출 절차 없이 성공으로 처리합니다.");
                    } else {
                        bool found = false;
                        for (auto m : c.messages)
                            if (test == std::string("normal_") + m.name) {
                                clientNormal(s, c, cfg, m, false, progress, test);
                                found = true;
                            }
                        if (!found)
                            throw Failure("시험 구현 매핑 오류");
                    }
                    if (test != "abnormal_session")
                        s.closeGracefully();
                }
            } else {
                userInfo(progress, test, "절차", "대상의 로그인 요청을 기다립니다. 시스템 식별정보·시험 계정·최대 무수신 시간·응답 제한 시간을 확인합니다.");
                serverLogin(s, cfg, test == "login_retry", progress, test);
                userInfo(progress, test, "확인", "대상의 로그인 조건을 확인하고 수용했습니다.");
                if (test == "session" || test == "login_retry")
                    s.alive(2);
                else if (test == "subscription_retry") {
                    auto sid = serverSubscription(s, c, cfg, true, progress, test);
                    auto sent = s.send(publication(c, c.messages.front(), sid, 1));
                    accepted(response(s, sent, cfg.response), Iso14827AcceptTypePresent_publication);
                    s.alive();
                } else if (test.compare(0, 7, "normal_") == 0) {
                    for (auto m : c.messages)
                        if (test == std::string("normal_") + m.name) {
                            auto selected = messageCase(c, m);
                            auto sid = serverSubscription(s, selected, cfg, false, progress, test);
                            userInfo(progress, test, "절차", messageLabel(m.name) + "를 제공하고 대상의 수신 확인 응답을 기다립니다.");
                            auto out = publication(c, m, sid, 1);
                            validatePayload(c, m, publicationData(out->x.publication).front());
                            auto sent = s.send(std::move(out));
                            auto ack = response(s, sent, cfg.response);
                            accepted(ack, Iso14827AcceptTypePresent_publication);
                            observePublicationAcceptance(s, cfg, ack, sid, progress, test);
                        }
                    result.detail = "정상 요청/Publication Accept 확인. 응답 제한 시간 동안 rejectPublicationData 없음 및 FrED 유지 확인";
                } else
                    serverInvalid(s, c, cfg, test, progress);
                s.closeGracefully();
            }
        } catch (const Stopped &e) {
            result.verdict = Verdict::Stopped;
            result.detail = e.what();
        } catch (const std::exception &e) {
            result.verdict = connected ? Verdict::Fail : Verdict::Error;
            result.detail = e.what();
        }
        const auto failureStage = stage;
        if (session && result.verdict != Verdict::Pass) {
            try { session->closeAfterFailure(); }
            catch (const std::exception &e) { sink.info(test, std::string("Cleanup diagnostic: ") + e.what()); }
        }
        session.reset(); // Release TCP before finalizing this item or starting the next one.
        result.userDetail = resultDescription(c, result, failureStage);
        if (sink.finalize) sink.finalize(result);
        sink.result(result);
        results.push_back(result);
        if (result.verdict == Verdict::Stopped)
            break;
    }
    return results;
}
} // namespace datex
