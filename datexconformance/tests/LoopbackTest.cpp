#include "DatexNarrative.h"
#include <fstream>
#include <winsock2.h>
#include "DatexWire.h"
#include "DatexThread.h"
#include <dz1_thread.h>
#include <DatexConformance.h>
#include <ScenarioEngineWebSockMsg.h>
#include <condition_variable>
#include <future>
#include <iostream>
#include <thread>

using namespace datex;
namespace {
Tick deadline(unsigned s = 3) {
    return std::chrono::steady_clock::now() + std::chrono::seconds(s);
}
unsigned port() {
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);
    auto s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in a = {};
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    bind(s, (sockaddr *)&a, sizeof(a));
    int n = sizeof(a);
    getsockname(s, (sockaddr *)&a, &n);
    unsigned p = ntohs(a.sin_port);
    closesocket(s);
    return p;
}
Config settings(unsigned p, const std::string &test) {
    Config c;
    c.host = "127.0.0.1";
    c.port = p;
    c.myDomain = "test";
    c.peerDomain = "sut";
    c.user = "u";
    c.password = "p";
    c.invalidPassword = "wrong";
    c.heartbeat = 6;
    c.response = 1;
    c.maintain = 1;
    c.receive = 3;
    c.period = 1;
    c.connectTimeout = 3;
    c.tests.insert(test);
    return c;
}
Received recvType(Session &s, Iso14827PDUsPresent type) {
    for (;;) {
        auto r = s.receive(deadline());
        if (r.message->pdu->present == type)
            return r;
        if (r.message->pdu->present == Iso14827PDUsPresent_fred && r.message->pdu->x.fred == 0)
            s.send(fred(r.message->pktNbr));
        else
            throw Failure("mock: unexpected PDU");
    }
}
void serverPeer(const Case &c, const Config &cfg, std::atomic<bool> &stop, const Sink &sink,
                const std::string &test, const std::string &fault) {
    Session s(c, cfg, stop, sink, test);
    s.open();
    if (cfg.useInitiate) {
        auto initConfig = cfg;
        if (fault == "bad_initiate_sender") initConfig.myDomain = "WRONG";
        if (fault == "bad_initiate_dest") initConfig.peerDomain = "WRONG";
        if (fault == "missing_initiate") { std::this_thread::sleep_for(std::chrono::seconds(cfg.connectTimeout+1)); return; }
        s.send(initiate(initConfig));
    }
    auto first = recvType(s, Iso14827PDUsPresent_login);
    if (first.message->pdu->x.login->initiator != (cfg.useInitiate ? Iso14827LoginInitiator_serverInitiated : Iso14827LoginInitiator_clientInitiated))
        throw Failure("mock: Login initiator mismatch");
    if (test == "invalid_login") {
        s.send(reject(first.message->pktNbr, Iso14827RejectTypePresent_login,
                      fault == "wrong_reason" ? Iso14827RejectLogin_other
                                              : Iso14827RejectLogin_invalidPassword));
        return;
    }
    s.send(accept(first.message->pktNbr, Iso14827AcceptTypePresent_login));
    s.established();
    bool subscribed = false, canceled = false;
    unsigned sid = 1, serial = 1;
    Tick next{};
    PacketRecord original;
    bool hasOriginal = false, retried = false;
    if (test == "duplicate_login") {
        s.alive();
        Session extra(c, cfg, stop, sink, test);
        if (cfg.useInitiate) extra.open();
        else extra.adopt(s.acceptPeer(deadline()));
        if (cfg.useInitiate) extra.send(initiate(cfg));
        auto duplicate = recvType(extra, Iso14827PDUsPresent_login);
        if (fault == "delayed") {
            auto end = deadline(3);
            while (std::chrono::steady_clock::now() < end) {
                try {
                    auto r = s.receive(
                        std::min(end, std::chrono::steady_clock::now() + std::chrono::milliseconds(100)));
                    if (r.message->pdu->present != Iso14827PDUsPresent_fred)
                        throw Failure("mock: non-heartbeat during duplicate login delay");
                    if (!r.message->pdu->x.fred)
                        s.send(fred(r.message->pktNbr));
                } catch (const Failure &e) {
                    if (std::string(e.what()) != "응답/관찰 시간 초과")
                        throw;
                }
            }
        }
        extra.send(
            reject(duplicate.message->pktNbr, Iso14827RejectTypePresent_login,
                   fault == "wrong_reason" ? Iso14827RejectLogin_other : Iso14827RejectLogin_sessionExist));
    }
    auto limit = deadline(14);
    while (!stop && std::chrono::steady_clock::now() < limit) {
        auto now = std::chrono::steady_clock::now();
        if (subscribed && !canceled && test == "cancel" && now >= next) {
            original = s.send(publication(c, c.messages.front(), sid, serial++));
            hasOriginal = true;
            next = now + std::chrono::seconds(cfg.period);
        }
        try {
            auto r = s.receive(test == "cancel" && !canceled && subscribed ? std::min(next, deadline(1))
                                                                           : deadline(1), fault != "no_close");
            auto p = r.message->pdu;
            if (p->present == Iso14827PDUsPresent_fred) {
                if (!p->x.fred)
                    s.send(fred(r.message->pktNbr));
            } else if (p->present == Iso14827PDUsPresent_logout) {
                s.send(fred(r.message->pktNbr));
                return;
            } else if (p->present == Iso14827PDUsPresent_ack) {
            } else if (p->present == Iso14827PDUsPresent_subscription) {
                auto sub = p->x.subscription;
                sid = sub->serial;
                if (sub->type->present == Iso14827SubscriptionTypePresent_reason) {
                    canceled = true;
                    if (fault == "old_retry")
                        original = s.send(publication(c, c.messages.front(), sid, serial++));
                    s.send(accept(r.message->pktNbr, Iso14827AcceptTypePresent_registeredSubscription, sid));
                    if (fault == "after_cancel")
                        s.send(publication(c, c.messages.front(), sid, serial++));
                    else if (fault == "old_retry")
                        s.resend(original);
                } else if (test == "invalid_subscription")
                    s.send(reject(r.message->pktNbr, Iso14827RejectTypePresent_subscription,
                                  fault == "wrong_reason"
                                      ? Iso14827RejectSubscription_other
                                      : Iso14827RejectSubscription_unknownSubscriptionMsgId));
                else {
                    subscribed = true;
                    bool reg =
                        sub->type->x.data->mode->present == Iso14827SubscriptionDataModePresent_periodic;
                    s.send(accept(r.message->pktNbr,
                                  reg ? Iso14827AcceptTypePresent_registeredSubscription
                                      : Iso14827AcceptTypePresent_singleSubscription,
                                  sid));
                    if (reg)
                        next = std::chrono::steady_clock::now();
                    else {
                        auto offered=publication(c,c.messages.front(),sid,serial++);
                        if(fault=="multi_tim" || fault=="multi_identical") {
                            auto extra=c.messages.front();
                            if(fault=="multi_tim") { extra.name="tim_speed"; extra.businessProfile=1; }
                            offered=publicationBundle(c,{c.messages.front(),extra},sid,1);
                            for(auto d:publicationData(offered->x.publication)) validatePayload(c,c.messages.front(),d);
                        }
                        original=s.send(std::move(offered));
                        if(fault=="early_retry") { s.resend(original); retried=true; }
                        hasOriginal = true;
                    }
                }
            } else
                throw Failure("mock server: unexpected message");
        } catch (const Failure &e) {
            if (test == "abnormal_session" && fault == "no_close" && std::string(e.what()) == "CONNECTION_CLOSED")
                return; // Tester cleanup after reporting the unobservable logical-session outcome.
            if (test == "abnormal_session" && std::string(e.what()).find("HeartbeatDurationMax 초과") == 0)
                return;
            if (std::string(e.what()) != "응답/관찰 시간 초과")
                throw;
            if (test == "abnormal_session" && fault == "extra_data" &&
                std::chrono::steady_clock::now() - s.lastReceive() >= std::chrono::seconds(2)) {
                s.send(fred());
                continue;
            }
            if (test == "abnormal_session" && fault != "no_close" &&
                std::chrono::steady_clock::now() - s.lastReceive() >=
                    std::chrono::seconds(fault == "early_close" ? 2 : cfg.heartbeat))
                return;
            if (test == "publication_retry" && hasOriginal && !retried) {
                if (fault == "changed_retry")
                    s.send(publication(c, c.messages.front(), sid, serial++));
                else
                    s.resend(original);
                retried = true;
            }
        }
    }
    if (!stop)
        throw Failure("mock server timed out");
}
void clientPeer(const Case &c, const Config &cfg, std::atomic<bool> &stop, const Sink &sink,
                const std::string &test, const std::string &fault) {
    Session s(c, cfg, stop, sink, test);
    s.open();
    if (cfg.useInitiate) {
        auto init = recvType(s, Iso14827PDUsPresent_initiate);
        if (utf8Text(init.message->pdu->x.initiate->sender) != cfg.peerDomain || utf8Text(init.message->pdu->x.initiate->dest) != cfg.myDomain)
            throw Failure("mock: Initiate domains mismatch");
    }
    auto offered = login(cfg, cfg.password);
    if (fault == "wrong_initiator") offered->x.login->initiator = cfg.useInitiate ? Iso14827LoginInitiator_clientInitiated : Iso14827LoginInitiator_serverInitiated;
    if (fault == "unsupported_encoding") {
        auto enc = offered->x.login->encRules;
        unsigned count = 0; Dz1Error err = {}; auto array = enc->get_array(enc, &count, &err);
        // Replace the offered OID with 1.2.3, independently of negotiation code.
        if (count != 1) throw Failure("mock: unexpected encoding count");
        if (array[0]->cnt != 3) throw Failure("mock: unexpected OID size");
        array[0]->data[0] = 1; array[0]->data[1] = 2; array[0]->data[2] = 3;
        Dz1Free(array);
    }
    auto l = s.send(std::move(offered));
    if (test == "login_retry") {
        try {
            auto r = s.receive(std::chrono::steady_clock::now() + std::chrono::milliseconds(fault == "early_retry" ? 150 : cfg.response*1000), false);
            throw Failure("mock: first Login unexpectedly answered");
        } catch (const Failure &e) {
            if (std::string(e.what()) != "응답/관찰 시간 초과")
                throw;
        }
        if (fault == "changed_retry")
            s.send(login(cfg, cfg.password));
        else
            s.resend(l);
    }
    recvType(s, Iso14827PDUsPresent_ack);
    s.established();
    if (test != "session" && test != "login_retry") {
        auto requested=subscribe(c,1,fault=="bad_sub_mode"?1:0,fault=="bad_sub_oid"?"1.2.3.999":"");
        if(fault=="bad_sub_guarantee") requested->x.subscription->type->x.data->guarantee=FALSE;
        if(fault=="bad_sub_format") requested->x.subscription->type->x.data->fmt=Iso14827SubscriptionDataFormat_ftp;
        auto req = s.send(std::move(requested));
        if (test == "subscription_retry") {
            try {
                auto r = s.receive(std::chrono::steady_clock::now() + std::chrono::milliseconds(fault == "early_retry" ? 150 : cfg.response*1000));
                throw Failure("mock: first subscription unexpectedly answered");
            } catch (const Failure &e) {
                if (std::string(e.what()) != "응답/관찰 시간 초과")
                    throw;
            }
            if (fault == "changed_retry")
                s.send(subscribe(c, 2));
            else
                s.resend(req);
        }
        recvType(s, Iso14827PDUsPresent_ack);
        bool repeated = test == "repeatedPublicationNbr";
        for (unsigned i = 0; i < (repeated ? 2u : 1u); ++i) {
            auto pub = recvType(s, Iso14827PDUsPresent_publication);
            auto data = publicationData(pub.message->pdu->x.publication);
            if (fault == "broken_transport") return;
            if (fault == "heartbeat_expire") { std::this_thread::sleep_for(std::chrono::milliseconds(cfg.heartbeat*1000+300)); return; }
            if (fault != "no_publication_accept" && fault != "cleanup_no_ack")
                s.send(accept(pub.message->pktNbr, Iso14827AcceptTypePresent_publication));
            if (test.compare(0, 7, "normal_") == 0 || test == "subscription_retry")
                validatePayload(c, c.messages.front(), data[0]);
            else if (!repeated || i == 1) {
                int why = Iso14827RejectPubDataReason_other;
                const std::vector<std::string> names = {
                    "unknownSubscription",     "unknownPublicationNbr",        "unknownPublicationMsgId",
                    "invalidPublicationMsgId", "invalidPublicationMsgContent", "repeatedPublicationNbr"};
                for (unsigned k = 0; k < names.size(); ++k)
                    if (test == names[k])
                        why = int(k) + 1;
                if (fault == "wrong_reason")
                    why = 0;
                if (fault != "missing_reject")
                    s.send(reject(0, Iso14827RejectTypePresent_pubData, why, data[0]->subscriptionSerial,
                                  data[0]->serial));
            }
            if (fault == "normal_reject" || fault == "normal_delayed_reject") {
                if (fault == "normal_delayed_reject") {
                    s.send(fred());
                    std::this_thread::sleep_for(std::chrono::milliseconds(350));
                }
                s.send(reject(0, Iso14827RejectTypePresent_pubData,
                    Iso14827RejectPubDataReason_invalidPublicationMsgContent,
                    data[0]->subscriptionSerial, data[0]->serial));
            }
        }
    }
    s.send(fred());
    auto limit = deadline(8);
    unsigned closeCount = 0;
    while (!stop) {
        auto r = s.receive(limit);
        auto p = r.message->pdu;
        if (p->present == Iso14827PDUsPresent_fred) {
            if (!p->x.fred)
                s.send(fred(r.message->pktNbr));
            else if (test == "session" || test == "login_retry")
                s.send(fred());
        } else if (p->present == Iso14827PDUsPresent_publication && (fault == "no_publication_accept" || fault == "cleanup_no_ack")) {
            s.send(fred());
        } else if (p->present == Iso14827PDUsPresent_term) {
            if (fault == "cleanup_no_ack" || (fault == "drop_first_close" && closeCount++ == 0)) { s.send(fred()); continue; }
            if (fault == "normal_close_reject")
                s.send(reject(0, Iso14827RejectTypePresent_pubData,
                    Iso14827RejectPubDataReason_invalidPublicationMsgContent, 1, 1));
            auto out = pdu(Iso14827PDUsPresent_logout);
            out->x.logout = Iso14827Logout_serverRequested;
            auto logout = s.send(std::move(out));
            for (;;) {
                auto echo = recvType(s, Iso14827PDUsPresent_fred);
                if (echo.message->pdu->x.fred == logout.number) break;
            }
            return;
        } else
            throw Failure("mock client: unexpected PDU");
    }
}
void scenario(const std::string &id, const std::string &test, const std::string &fault, Verdict expected, bool useInitiate = false) {
    Case target = findCase(id), peer = target;
    peer.role = target.role == Role::Client ? Role::Server : Role::Client;
    if (test.compare(0, 7, "normal_") == 0) {
        for (auto m : peer.messages)
            if (test == std::string("normal_") + m.name) {
                peer = messageCase(peer, m);
                break;
            }
    }
    Config cfg = settings(port(), test), other = cfg;
    cfg.useInitiate = other.useInitiate = useInitiate;
    if (fault == "heartbeat_expire") { cfg.heartbeat = other.heartbeat = 1; cfg.response = other.response = 2; }
    if (fault == "delayed") {
        cfg.heartbeat = other.heartbeat = 3;
        cfg.response = other.response = 2;
    }
    other.myDomain = cfg.peerDomain;
    other.peerDomain = cfg.myDomain;
    std::atomic<bool> stop{false}, peerStop{false};
    std::promise<void> listening;
    std::atomic<bool> signaled{false};
    std::exception_ptr peerError;
    Sink sink;
    sink.state = [](const std::string &, const std::string &) {};
    sink.result = [](const Result &) {};
    sink.info = [&](const std::string &, const std::string &text) {
        if (text == "LISTENING" && !signaled.exchange(true))
            listening.set_value();
    };
    std::vector<std::string> userLogs;
    Sink runnerSink = sink;
    std::vector<std::string> tcpEvents;
    runnerSink.info = [&](const std::string &key, const std::string &text) {
        if (text == "TCP_CONNECTED" || text == "TCP_ACCEPTED") tcpEvents.push_back(text);
        sink.info(key, text);
    };
    unsigned sentLogin=0, acceptedLogin=0, rejectedLogin=0;
    std::vector<PacketRecord> termination;
    unsigned sentSubscriptionRejects=0; int sentSubscriptionReason=-1; unsigned rejectedPacket=0;
    runnerSink.packet=[&](const std::string&,bool received,const PacketRecord &record,int type,const Bytes &bytes,bool) {
        if (received) return;
        if (type == Iso14827PDUsPresent_login) ++sentLogin;
        if (type == Iso14827PDUsPresent_term || type == Iso14827PDUsPresent_logout) termination.push_back(record);
        if (type == Iso14827PDUsPresent_ack) {
            auto copy=bytes; auto p=decode(copy);
            if (p->pdu->x.ack->acceptType->present==Iso14827AcceptTypePresent_login) ++acceptedLogin;
        }
        if(type!=Iso14827PDUsPresent_nak) return;
        auto copy=bytes; auto packet=decode(copy);auto nak=packet->pdu->x.nak;
        if (nak && nak->type && nak->type->present == Iso14827RejectTypePresent_login) ++rejectedLogin;
        if(nak && nak->type && nak->type->present==Iso14827RejectTypePresent_subscription) {
            ++sentSubscriptionRejects;sentSubscriptionReason=nak->type->x.subscription;rejectedPacket=nak->pktNbr;
        }
    };
    runnerSink.userInfo = [&](const std::string &, const std::string &phase, const std::string &text) {
        userLogs.push_back("[" + phase + "] " + text);
    };
    std::vector<Result> results;
    std::promise<void> peerFinished;
    auto peerDone = peerFinished.get_future();
    auto peerWork = [&] {
        try {
            if (peer.role == Role::Server)
                serverPeer(peer, other, peerStop, sink, test, fault);
            else
                clientPeer(peer, other, peerStop, sink, test, fault);
        } catch (...) {
            peerError = std::current_exception();
        }
        peerFinished.set_value();
    };
    // Independent expected listener: DATEX Server normally, DATEX Client for Initiate.
    if ((peer.role == Role::Server) != useInitiate) {
        ManagedThread worker(peerWork);
        if (listening.get_future().wait_for(std::chrono::seconds(3)) != std::future_status::ready) {
            peerStop = true;
            worker.join();
            throw Failure("mock listener unavailable");
        }
        results = run(target, cfg, stop, runnerSink);
        if (expected == Verdict::Pass) peerDone.wait_for(std::chrono::seconds(1));
        peerStop = true;
        worker.join();
    } else {
        ManagedThread runner([&] { results = run(target, cfg, stop, runnerSink); });
        if (listening.get_future().wait_for(std::chrono::seconds(3)) != std::future_status::ready) {
            stop = true;
            runner.join();
            throw Failure("runner listener unavailable");
        }
        ManagedThread worker(peerWork);
        runner.join();
        if (expected == Verdict::Pass) peerDone.wait_for(std::chrono::seconds(1));
        peerStop = true;
        worker.join();
    }
    const std::string expectedTcp = ((target.role == Role::Client) != useInitiate) ? "TCP_CONNECTED" : "TCP_ACCEPTED";
    if (tcpEvents.empty() || std::any_of(tcpEvents.begin(), tcpEvents.end(), [&](const std::string &value) { return value != expectedTcp; }))
        throw Failure("Unexpected TCP connection direction");
    if (fault == "wrong_initiator" || fault == "unsupported_encoding")
        if (acceptedLogin || rejectedLogin != 1 || !termination.empty()) throw Failure("Invalid Login must be rejected without establishing or terminating a session");
    if (fault == "bad_initiate_sender" || fault == "bad_initiate_dest" || fault == "missing_initiate")
        if (sentLogin) throw Failure("Login must not be sent before a valid Initiate");
    if (fault == "no_publication_accept" && (termination.size()!=1 || results[0].detail!="응답/관찰 시간 초과"))
        throw Failure("Healthy failed Publication needs Terminate without replacing the original timeout");
    if (fault == "broken_transport" || fault == "heartbeat_expire")
        if (!termination.empty()) throw Failure("No termination datagram after transport/heartbeat failure");
    if (fault == "cleanup_no_ack" || fault == "drop_first_close")
        if (termination.size()!=2 || !compareRetry(termination[0],termination[1]).same())
            throw Failure("Teardown retries must be bounded to one identical retransmission");
    if(fault.compare(0,8,"bad_sub_")==0) {
        int reason=fault=="bad_sub_oid"?Iso14827RejectSubscription_unknownSubscriptionMsgId:
            fault=="bad_sub_format"?Iso14827RejectSubscription_publishFormatNotSupported:
            fault=="bad_sub_mode"?Iso14827RejectSubscription_invalidMode:Iso14827RejectSubscription_invalidSubscriptionContent;
        if(sentSubscriptionRejects!=1 || rejectedPacket!=2 || sentSubscriptionReason!=reason)
            throw Failure("Invalid Subscription must receive one correctly correlated Reject with the expected reason");
    }
    if (results.size() != 1 || results[0].verdict != expected) {
        std::string detail = results.empty() ? "no result" : results[0].detail;
        throw Failure(id + " / " + test + " / " + fault + ": " + detail);
    }
    if (test == "abnormal_session" && expected == Verdict::Pass) {
        auto evidence = Json::parse(results[0].observationsJson);
        if (evidence.get("tcpClosed")->boolean != (fault != "no_close"))
            throw Failure("Abnormal-session closure evidence mismatch");
        auto elapsed = std::stoll(evidence.get("elapsedMilliseconds")->text);
        if (elapsed < cfg.heartbeat * 1000 ||
            (fault != "no_close" && elapsed > (cfg.heartbeat + cfg.response) * 1000))
            throw Failure("Abnormal-session evidence is outside timing bounds");
    }
    if (expected == Verdict::Pass) {
        if (peerError)
            std::rethrow_exception(peerError);
    }
    if (userLogs.size() < 4 || results[0].userDetail.empty()) throw Failure("User procedure/evidence/result narration missing");
    for (const auto &line : userLogs)
        for (const auto &bad : {"TX packet=", "RX packet=", "TIM_REGIONAL_DECODE", "LISTENING", "expected=", "_v2", "{\"number\""})
            if (line.find(bad) != std::string::npos) throw Failure("Internal diagnostics exposed in user progress");
    if (expected == Verdict::Fail && results[0].userDetail.find("확인 기준 미충족") == std::string::npos)
        throw Failure("User failure explanation missing");
    if (test.compare(0, 7, "normal_") == 0 && target.role == Role::Server && expected == Verdict::Pass &&
        results[0].userDetail.find("rejectPublicationData 없음") == std::string::npos)
        throw Failure("Requester protocol acceptance criterion missing");
    std::ofstream log("user-log-loopback.jsonl", std::ios::app);
    for (const auto &line : userLogs) log << "{\"test\":" << quote(test) << ",\"fault\":" << quote(fault) << ",\"message\":" << quote(line) << "}\n";
    log << "{\"result\":" << quote(results[0].userDetail) << "}\n";
    std::cout << "PASS loopback " << id << " " << test << " " << fault << "\n";
}
} // namespace
void tcpLifecycleTests() {
    auto c = findCase("centerClient2rse_v2");
    const auto listeningPort = port();
    for (int attempt = 0; attempt < 2; ++attempt) {
        auto cfg = settings(listeningPort, "session"); cfg.useInitiate = true; cfg.connectTimeout = 30;
        std::atomic<bool> stop{false}; std::promise<void> listening; std::vector<Result> result;
        Sink sink; sink.state=[](const std::string &,const std::string &){};
        sink.result=[](const Result &){};
        sink.info=[&](const std::string &,const std::string &text){if(text=="LISTENING")listening.set_value();};
        ManagedThread runner([&]{result=run(c,cfg,stop,sink);});
        if(listening.get_future().wait_for(std::chrono::seconds(3))!=std::future_status::ready){stop=true;runner.join();throw Failure("Server Initiate receiver did not listen");}
        const auto start=std::chrono::steady_clock::now();stop=true;runner.join();
        if(result.size()!=1 || result.front().verdict!=Verdict::Stopped || std::chrono::steady_clock::now()-start>std::chrono::seconds(1))throw Failure("Inbound Initiate wait must stop promptly and release the listener");
    }
    auto active = findCase("rseServer2center_v2"); auto cfg=settings(port(),"session");cfg.useInitiate=true;cfg.connectTimeout=1;
    std::atomic<bool> stop{false};Sink sink;sink.state=[](const std::string &,const std::string &){};sink.info=[](const std::string &,const std::string &){};sink.result=[](const Result &){};
    auto result=run(active,cfg,stop,sink);
    if(result.size()!=1 || result[0].verdict!=Verdict::Error)throw Failure("Unreachable Initiate receiver must report a connection error");
    std::cout<<"PASS Initiate TCP lifecycle: stop while waiting, immediate port reuse, unreachable receiver error\n";
}
void initiationTests() {
    for (bool mode : {false, true}) {
        for (const auto &c : cases()) scenario(c.id, "session", "", Verdict::Pass, mode);
        for (const auto &t : {"invalid_login", "duplicate_login", "publication_retry", "cancel"})
            scenario("centerClient2rse_v2", t, "", Verdict::Pass, mode);
        for (const auto &t : {"login_retry", "subscription_retry", "normal_bsm"})
            scenario("rseServer2center_v2", t, "", Verdict::Pass, mode);
        for (const auto &f : {"wrong_initiator", "unsupported_encoding"}) scenario("rseServer2center_v2", "session", f, Verdict::Fail, mode);
    }
    for (const auto &f : {"bad_initiate_sender", "bad_initiate_dest", "missing_initiate"})
        scenario("centerClient2rse_v2", "session", f, Verdict::Fail, true);
    for (const auto &f : {"no_publication_accept", "cleanup_no_ack", "broken_transport", "heartbeat_expire"})
        scenario("rseServer2center_v2", "normal_bsm", f, Verdict::Fail, true);
    scenario("rseServer2center_v2", "session", "drop_first_close", Verdict::Pass, true);
    scenario("centerClient2rse_v2", "abnormal_session", "no_close", Verdict::Pass, true);
    std::cout << "PASS initiation modes, negotiation and failure cleanup regressions\n";
}
void abnormalSessionTests() {
    for (const auto &c : cases()) if (c.role == Role::Client)
        scenario(c.id, "abnormal_session", "", Verdict::Pass);
    scenario("centerClient2rse_v2", "abnormal_session", "early_close", Verdict::Fail);
    scenario("centerClient2rse_v2", "abnormal_session", "extra_data", Verdict::Fail);
    scenario("centerClient2rse_v2", "abnormal_session", "no_close", Verdict::Pass);
    std::cout << "PASS abnormal-session 7 roles, normal timeout closure, early closure, extra data, no observable closure\n";
}
void publicationAcceptanceTests() {
    unsigned messages = 0;
    for (const auto &c : cases()) if (c.role == Role::Server)
        for (const auto &m : c.messages) {
            scenario(c.id, std::string("normal_") + m.name, "", Verdict::Pass);
            ++messages;
        }
    for (auto fault : {"normal_reject", "normal_delayed_reject", "normal_close_reject", "no_publication_accept"})
        scenario("rseServer2center_v2", "normal_bsm", fault, Verdict::Fail);
    scenario("rseServer2center_v2", "invalidPublicationMsgContent", "", Verdict::Pass);
    scenario("rseServer2center_v2", "invalidPublicationMsgContent", "missing_reject", Verdict::Fail);
    scenario("rseServer2center_v2", "invalidPublicationMsgContent", "wrong_reason", Verdict::Fail);
    std::cout << "PASS publication acceptance: " << messages << " normal messages; immediate/delayed/closing rejection, missing Accept, required malformed-content rejection\n";
}
void loopbackTests() {
    const std::string client = "centerClient2rse_v2", server = "rseServer2center_v2";
    scenario(client, "normal_bsm", "", Verdict::Pass);
    scenario(client, "session", "", Verdict::Pass);
    scenario(client, "invalid_login", "", Verdict::Pass);
    scenario(client, "invalid_login", "wrong_reason", Verdict::Fail);
    scenario(client, "duplicate_login", "", Verdict::Pass);
    scenario(client, "duplicate_login", "delayed", Verdict::Pass);
    scenario(client, "duplicate_login", "wrong_reason", Verdict::Fail);
    scenario(client, "abnormal_session", "", Verdict::Pass);
    scenario(client, "abnormal_session", "early_close", Verdict::Fail);
    scenario(client, "invalid_subscription", "", Verdict::Pass);
    scenario(client, "invalid_subscription", "wrong_reason", Verdict::Fail);
    scenario(client, "publication_retry", "", Verdict::Pass);
    scenario(client, "publication_retry", "changed_retry", Verdict::Fail);
    scenario(client, "cancel", "", Verdict::Pass);
    scenario(client, "cancel", "after_cancel", Verdict::Fail);
    scenario(client, "cancel", "old_retry", Verdict::Pass);
    scenario(server, "normal_bsm", "", Verdict::Pass);
    scenario(server, "login_retry", "", Verdict::Pass);
    scenario(server, "login_retry", "changed_retry", Verdict::Fail);
    scenario(server, "subscription_retry", "", Verdict::Pass);
    scenario(server, "subscription_retry", "changed_retry", Verdict::Fail);
    for (auto t : {"unknownSubscription", "unknownPublicationNbr", "unknownPublicationMsgId",
                   "invalidPublicationMsgId", "invalidPublicationMsgContent", "repeatedPublicationNbr"})
        scenario(server, t, "", Verdict::Pass);
    scenario(server, "invalidPublicationMsgContent", "wrong_reason", Verdict::Fail);
    for (auto t : {"normal_map", "normal_rsa", "normal_tim"})
        scenario("centerServer2rse_v2", t, "", Verdict::Pass);
    for (auto t : {"normal_spat", "normal_tls"})
        scenario("signalserverServer2center_v2", t, "", Verdict::Pass);
}

namespace {
struct Harness {
    void *module = nullptr;
    std::mutex mutex;
    std::condition_variable changed;
    bool ui = false, done = false;
    bool unsupportedComplete = false;
    std::vector<std::pair<std::string,std::string>> notifiedStates;
    bool prematureFinish = false;
    int validationMode = 0;
    unsigned validationRequests=0;
    ScenarioEngineResponseMessageValidate *heldResponse=nullptr;
    ~Harness(){if(heldResponse)ScenarioEngineResponseMessageValidate_del(heldResponse);}
    std::string mainState;
    std::vector<std::string> userLogs;
    std::vector<std::string> attachments;
};
int timerCompare(void *a, void *b) {
    return a == b ? 0 : std::less<void *>{}(a, b) ? -1 : 1;
}
Dz1Error harnessInit(void **resource, void *, str_t, unsigned, void *arg, void *) {
    *resource = arg;
    return Dz1Error{};
}
Dz1TaskProcStatus harnessMessage(void *arg, void *, void *, void **message, Dz1Error *error) {
    auto h = (Harness *)arg;
    auto data = Dz1TaskSigMsg_getData(*message);
    auto type = Dz1TaskSigMsg_getType(*message);
    if (type == 0x00f00006) {
        auto json = Json::parse((char *)data);
        std::lock_guard<std::mutex> lock(h->mutex);
        h->ui = json.get("configuration") && json.get("scenarios");
        h->changed.notify_all();
    } else if (type == 0x00f00001) {
        auto event = (ScenarioEngineNotifyStateArg *)data;
        std::lock_guard<std::mutex> lock(h->mutex);
        h->notifiedStates.emplace_back(event->context->testName,event->context->state);
        if (std::string(event->context->state) == "COMPLETE") h->unsupportedComplete = true;
        if (std::string(event->context->testName) == "MainScenario") {
            if (std::string(event->context->state) == "FINISH")
                h->done = true;
            else
                h->mainState = event->context->state;
        }
        else if (std::string(event->context->state) == "FINISH")
            h->prematureFinish = true;
        h->changed.notify_all();
    } else if (type == 0x00f00002) {
        auto event = (ScenarioEngineNotifyInfoArg *)data;
        if (event->context->data && event->context->dataType && std::string(event->context->dataType)=="JSON") {
            std::lock_guard<std::mutex> lock(h->mutex);
            h->attachments.emplace_back((char *)event->context->data->data,event->context->data->size);
        }
        auto text = Dz1Asn1UTF8Str_newFromStr(event->context->log, error);
        if (text) {
            std::lock_guard<std::mutex> lock(h->mutex);
            h->userLogs.emplace_back((char *)text->data, text->size);
            Dz1Asn1UTF8Str_del(text);
        }
    } else if (type == 0x00f00004) {
        ++h->validationRequests;
        if(h->validationMode==2) { Dz1Error_set(error,0);return Dz1TaskProcStatus_processed; }
        auto request = (ScenarioEngineValidateContextArg *)data;
        auto ctx = ScenarioEngineValidateContext_clone(request->context, error);
        auto response = ScenarioEngineResponseMessageValidate_gen(error);
        response->testIdx = h->validationMode >= 3 ? 0 : request->testIdx;
        if (h->validationMode == 9) response->testIdx = request->testIdx + 1;
        response->validate = ctx;
        response->result = Dz1Str_clone((char *)(h->validationMode == 4 ? "FAIL" : "SUCCESS"), error);
        ctx->code = h->validationMode == 1 ? ScenarioEngineProcessStatusCode_OUT_OF_RANGE
                                          : ScenarioEngineProcessStatusCode_OK;
        if (h->validationMode == 5) {
            Dz1Str_del(ctx->desc);
            ctx->desc = Dz1Str_clone((char *)"DATEX validation stale-run:test_normal_bsm", error);
        }
        if (h->validationMode == 6) ++ctx->time;
        if (h->validationMode == 7) ctx->raw->data[0] ^= 1;
        if (h->validationMode == 8) ctx->data->data[0] ^= 1;
        if(h->validationMode==10 && h->validationRequests==1) {
            h->heldResponse=response;
            Dz1Error_set(error,0);return Dz1TaskProcStatus_processed;
        }
        if(h->validationMode==11 && h->validationRequests==2) ctx->code=ScenarioEngineProcessStatusCode_OUT_OF_RANGE;
        if(h->validationMode==12 && h->validationRequests==2) {
            ScenarioEngineResponseMessageValidate_del(response);
            Dz1Error_set(error,0);return Dz1TaskProcStatus_processed;
        }
        DatexConformance_validation(h->module, response, error);
        if(h->validationMode==15) DatexConformance_validation(h->module,response,error);
        ScenarioEngineResponseMessageValidate_del(response);
        if(h->heldResponse) {
            DatexConformance_validation(h->module,h->heldResponse,error);
            ScenarioEngineResponseMessageValidate_del(h->heldResponse);h->heldResponse=nullptr;
        }
    }
    Dz1Error_set(error, 0);
    return Dz1TaskProcStatus_processed;
}
void adapterScenario(int mode, const std::string &expected, const std::string &id = "centerClient2rse_v2",
                     const std::string &test = "normal_bsm", const std::string &fixture = "") {
    Harness h;
    h.validationMode = mode;
    Dz1Error error = {};
    void *ptr = &h;
    auto mainTask = Dz1Task_new((char *)"DatexTestHost", 128, &ptr, nullptr, timerCompare, harnessInit,
                                nullptr, nullptr, &error);
    for (unsigned type : {0x00f00001u, 0x00f00002u, 0x00f00004u, 0x00f00006u})
        Dz1Task_regMsg(mainTask, DZ1_TASK_MSG_EXACT(type), harnessMessage);
    const auto originalLog = DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_DEBUG | DZ1_THREAD_LOG_TASK_DEBUG;
    Dz1Task_start(mainTask, originalLog);
    h.module = DatexConformance_new(mainTask, (char *)id.c_str(), nullptr, nullptr, &error);
    if (!h.module)
        throw Failure("adapter creation");
    Dz1Task_start(h.module, 0);
    {
        std::unique_lock<std::mutex> lock(h.mutex);
        if (!h.changed.wait_for(lock, std::chrono::seconds(3), [&] { return h.ui; }))
            throw Failure("UI_CONFIGURE missing");
    }
    Dz1ThreadLogLevel quietLevel = 0;
    Dz1Thread_getLogLevel(Dz1Task_getThread(mainTask), &quietLevel);
    if (quietLevel & (DZ1_THREAD_LOG_DEBUG | DZ1_THREAD_LOG_TASK_DEBUG)) throw Failure("DATEX transport debug suppression missing");
    Config cfg = settings(port(), "normal_bsm"), peerCfg = cfg;
    peerCfg.myDomain = "sut";
    peerCfg.peerDomain = "test";
    auto peer = findCase(id);
    peer.role = Role::Server;
    for (auto m : peer.messages)
        if (test == std::string("normal_") + m.name) {
            peer.messages = {m};
            break;
        }
    std::atomic<bool> peerStop{false}, ready{false};
    Sink sink;
    sink.info = [&](const std::string &, const std::string &text) {
        if (text == "LISTENING")
            ready = true;
    };
    sink.state = [](auto &, auto &) {};
    sink.result = [](const Result &) {};
    std::exception_ptr peerError;
    ManagedThread worker([&] {
        try {
            serverPeer(peer, peerCfg, peerStop, sink, test, fixture);
        } catch (...) {
            peerError = std::current_exception();
        }
    });
    auto limit = deadline();
    while (!ready && std::chrono::steady_clock::now() < limit)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::string json = "{\"my_domain\":\"test\",\"peer_domain\":\"sut\",\"user\":\"u\",\"pass\":\"p\",\"peer_"
                       "ip\":\"127.0.0.1\",\"peer_port\":" +
                       std::to_string(cfg.port) + ",\"hb_dur\":6,\"rsp_timeout\":1,\"test_" + test +
                       "\":true,\"receive_s\":3,\"period_s\":1}";
    auto setupError = Dz1Task_call(h.module, DZ1_TASK_QUEUE_NONE, 0x0f000003, (void *)json.c_str(), nullptr,
                                   nullptr, nullptr);
    if (!setupError.code) {
        std::ifstream selectedFile("datex-selection.json",std::ios::binary);
        std::string selectedText((std::istreambuf_iterator<char>(selectedFile)),std::istreambuf_iterator<char>());
        auto selected=Json::parse(selectedText);
        if(!selected.get("valid")->boolean || selected.get("case")->text!=id || selected.get("tests")->array.size()!=1 || selected.get("tests")->array[0].text!="test_"+test)
            throw Failure("Actual platform selection snapshot mismatch");
        Dz1Task_call(h.module, DZ1_TASK_QUEUE_NONE, 0x0f000001, nullptr, nullptr, nullptr, nullptr);
    }
    {
        std::unique_lock<std::mutex> lock(h.mutex);
        h.changed.wait_for(lock, std::chrono::seconds(10), [&] { return h.done; });
    }
    peerStop = true;
    worker.join();
    Dz1Task_del(h.module);
    Dz1ThreadLogLevel restoredLog = 0;
    Dz1Thread_getLogLevel(Dz1Task_getThread(mainTask), &restoredLog);
    if (restoredLog != originalLog) throw Failure("Host diagnostic level was not restored");
    Dz1Task_del(mainTask);
    if (setupError.code || !h.done || h.mainState != expected)
        throw Failure("adapter validation mode " + std::to_string(mode) + " result=" + h.mainState);
    if (h.prematureFinish)
        throw Failure("Only MainScenario may finish the platform report");
    if (h.unsupportedComplete) throw Failure("ScenarioEngine must never emit COMPLETE");
    std::vector<std::string> actualStates;
    for (const auto &entry:h.notifiedStates) if(entry.first=="test_"+test) actualStates.push_back(entry.second);
    if(actualStates != std::vector<std::string>{"START",expected}) throw Failure("Detailed test must report START then one final outcome");
    if (peerError)
        std::rethrow_exception(peerError);
    std::string all;
    for (const auto &line : h.userLogs) {
        if (line.find("[수신 데이터]") != std::string::npos && line.find('\n') != std::string::npos) throw Failure("Data notifications must avoid the deployed SDK multiline serialization defect");
        all += line + "\n";
    }
    if (all.find("[시험 안내]") == std::string::npos || all.find("[판정 근거]") == std::string::npos ||
        (test.compare(0,7,"normal_")==0 && all.find("[결과]") == std::string::npos) || all.find("[결과]") == std::string::npos)
        throw Failure("SDK progress/result narration missing");
    for (const auto &bad : {"TX packet=", "RX packet=", "type=", "LISTENING", "_v2", "datex-results", "EVIDENCE_PENDING", "TIM_REGIONAL_DECODE"})
        if (all.find(bad) != std::string::npos) throw Failure("SDK user log leaked internal representation");
    if ((mode == 2 || (mode >= 5 && mode <= 9) || mode==12) && all.find("플랫폼 규격 판정 응답은 확인되지 않았습니다.") == std::string::npos)
        throw Failure("Missing-platform-verdict explanation missing");
    if (expected == "FAIL" && all.find("규격 판정이 부적합") == std::string::npos)
        throw Failure("External rejection explanation missing");
    if(!fixture.empty()) {
        if(h.validationRequests!=2) throw Failure("Every payload needs its own validation request");
        const std::string expectedSummary=mode==11?"적합 1건, 부적합 1건, 미회신 0건":
            mode==12?"적합 1건, 부적합 0건, 미회신 1건":"적합 2건, 부적합 0건, 미회신 0건";
        if(all.find(expectedSummary)==std::string::npos)throw Failure("Per-message aggregate evidence mismatch");
    }
    if (h.attachments.empty()) throw Failure("All-message attachments missing");
    unsigned login=0,fred=0,publication=0,logout=0; unsigned sequence=0, messageCount=0;
    for (const auto &raw : h.attachments) {
        auto data=Json::parseData(raw);
        auto kind=data.get("자료 구분");
        if (!kind) throw Failure("Attachment category missing");
        if (kind->text != "송수신 데이터") continue;
        ++messageCount;
        if (!data.get("관측 순번")) throw Failure("Wire attachment observation sequence missing");
        if (std::stoul(data.get("관측 순번")->text) != ++sequence) throw Failure("Missing or reordered message");
        auto detail=data.get("상세"); if (!detail) throw Failure("Unexpected split in small fixture");
        auto auth=detail->get("ISO 14827 C2CAuthMsg"); if(!auth)throw Failure("Auth message structure missing");
        const auto &name=auth->get("pdu")->get("name")->text;
        login+=name.find("Login")!=std::string::npos; fred+=name.find("FrED")!=std::string::npos;
        publication+=name.find("Publication")!=std::string::npos; logout+=name.find("Logout")!=std::string::npos;
        if(name.find("Login")!=std::string::npos && auth->get("pdu")->get("body")->get("pass")->text!="[비밀번호 가림]")throw Failure("Login password exposed");
    }
    if(test=="invalid_login") { if(login!=1 || messageCount!=2)throw Failure("Invalid login TX/RX missing"); }
    else if(login!=1 || !fred || !publication || logout!=1)throw Failure("Session/data/close messages not all displayed");
    if(test=="publication_retry" && publication!=2)throw Failure("Repeated identical Publication must be shown twice");
    if(test=="normal_bsm" && messageCount!=10)throw Failure("Normal exchange must display all ten frames");
    if(test=="cancel" && publication<3)throw Failure("Periodic messages were sampled or hidden");
    std::ofstream delivered("all-message-adapter-"+test+"-"+std::to_string(mode)+".jsonl",std::ios::binary);
    for(const auto &raw:h.attachments)delivered<<raw<<"\n";
    std::ofstream narrative("user-log-adapter-" + std::to_string(mode) + ".txt", std::ios::binary);
    narrative << all;
    std::cout << "PASS adapter UI/SETUP/START/VALIDATE mode=" << mode << " state=" << h.mainState << "\n";
}
} // namespace
void stopTests() {
    Harness h;
    Dz1Error error = {};
    void *ptr = &h;
    auto host = Dz1Task_new((char *)"DatexStopTest", 128, &ptr, nullptr, timerCompare, harnessInit, nullptr,
                            nullptr, &error);
    for (unsigned type : {0x00f00001u, 0x00f00002u, 0x00f00006u})
        Dz1Task_regMsg(host, DZ1_TASK_MSG_EXACT(type), harnessMessage);
    Dz1Task_start(host, 0);
    h.module = DatexConformance_new(host, (char *)"rseServer2center_v2", nullptr, nullptr, &error);
    Dz1Task_start(h.module, 0);
    std::string json = "{\"my_domain\":\"test\",\"peer_domain\":\"sut\",\"user\":\"u\","
                       "\"pass\":\"p\",\"local_port\":" +
                       std::to_string(port()) + ",\"connect_timeout_s\":30,\"test_session\":true}";
    bool good = true;
    for (int run = 0; run < 2; ++run) {
        {
            std::lock_guard<std::mutex> lock(h.mutex);
            h.done = false;
            h.mainState.clear();
        }
        auto result = Dz1Task_call(h.module, DZ1_TASK_QUEUE_NONE, 0x0f000003, (void *)json.c_str(), nullptr,
                                   nullptr, nullptr);
        if (result.code) {
            good = false;
            break;
        }
        Dz1Task_call(h.module, DZ1_TASK_QUEUE_NONE, 0x0f000001, nullptr, nullptr, nullptr, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto begin = std::chrono::steady_clock::now();
        Dz1Task_call(h.module, DZ1_TASK_QUEUE_NONE, 0x0f000002, nullptr, nullptr, nullptr, nullptr);
        std::unique_lock<std::mutex> lock(h.mutex);
        h.changed.wait_for(lock, std::chrono::seconds(2), [&] { return h.done; });
        good = good && h.done && h.mainState == "STOPPED" &&
               std::chrono::steady_clock::now() - begin < std::chrono::seconds(2);
    }
    auto old = h.module;
    Dz1Task_del(h.module);
    good = good && !DatexConformance_validation(old, nullptr, &error);
    Dz1Task_del(host);
    if (!good)
        throw Failure("STOP/re-SETUP cleanup or verdict failure");
    std::cout << "PASS stop and restart: bounded cancellation, port reuse, registry cleanup\n";
}

void adapterTests() {
    adapterScenario(0, "SUCCESS");
    adapterScenario(1, "FAIL");
    adapterScenario(2, "SUCCESS");
    adapterScenario(3, "SUCCESS"); // Deployed reply without testIdx.
    adapterScenario(4, "FAIL"); // Top-level failure must win over echoed input code=OK.
    for (int mode : {5, 6, 7, 8, 9})
        adapterScenario(mode, "SUCCESS"); // Stale replies remain ignored; completed protocol has no post-evidence stage.
    for (auto test : {"normal_map", "normal_rsa", "normal_tim"})
        adapterScenario(0, "SUCCESS", "rseClient2center_v2", test);
}

void userLogTests() {
    unsigned covered = 0;
    for (const auto &c : cases()) for (const auto &test : availableTests(c)) {
        if (testTitle(c, test).empty() || testCriteria(c, Config{}, test).empty()) throw Failure("Missing catalog narration");
        ++covered;
    }
    if (covered != 152) throw Failure("DATEX item coverage changed");
    adapterScenario(0, "SUCCESS");
    adapterScenario(1, "FAIL");
    adapterScenario(2, "SUCCESS");
    scenario("rseServer2center_v2", "normal_bsm", "", Verdict::Pass);
    scenario("centerClient2rse_v2", "publication_retry", "", Verdict::Pass);
    scenario("centerClient2rse_v2", "publication_retry", "changed_retry", Verdict::Fail);
    scenario("centerClient2rse_v2", "cancel", "", Verdict::Pass);
    scenario("centerClient2rse_v2", "cancel", "after_cancel", Verdict::Fail);
    scenario("centerClient2rse_v2", "abnormal_session", "", Verdict::Pass);
    scenario("rseServer2center_v2", "login_retry", "", Verdict::Pass);
    scenario("rseServer2center_v2", "subscription_retry", "", Verdict::Pass);
    scenario("rseServer2center_v2", "invalidPublicationMsgContent", "wrong_reason", Verdict::Fail);
    stopTests();
    std::cout << "PASS user logs: 152 catalog items, role/evidence distinction, final verdicts, retries, cancellation, failure, stop\n";
}

void linkedDataAdapterTests() {
    adapterScenario(0,"SUCCESS");
    adapterScenario(1,"FAIL");
    adapterScenario(2,"SUCCESS");
    adapterScenario(0,"SUCCESS","centerClient2rse_v2","cancel");
    std::cout << "PASS linked-data SDK delivery, unchanged external verdicts, periodic first/last display\n";
}

void allMessageAdapterTests() {
    adapterScenario(0,"SUCCESS");
    adapterScenario(1,"FAIL");
    adapterScenario(2,"SUCCESS");
    adapterScenario(0,"SUCCESS","centerClient2rse_v2","cancel");
    adapterScenario(0,"SUCCESS","centerClient2rse_v2","publication_retry");
    adapterScenario(0,"SUCCESS","centerClient2rse_v2","invalid_login");
    for(bool badCrc:{false,true}) {
        Config cfg=settings(port(),"session"),remote=cfg;
        remote.myDomain=badCrc?cfg.peerDomain:"WRONG-SENDER";remote.peerDomain=cfg.myDomain;
        SOCKET listener=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        sockaddr_in address={};address.sin_family=AF_INET;address.sin_addr.s_addr=htonl(INADDR_LOOPBACK);address.sin_port=htons((u_short)cfg.port);
        if(bind(listener,(sockaddr*)&address,sizeof(address)) || listen(listener,1))throw Failure("malformed test listener");
        std::exception_ptr peerError;
        ManagedThread peer([&]{SOCKET client=INVALID_SOCKET;try {
            client=::accept(listener,nullptr,nullptr);DWORD timeout=3000;setsockopt(client,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));
            char input[4096];if(recv(client,input,sizeof(input),0)<=0)throw Failure("malformed test login");
            auto response=packet(remote,accept(1,Iso14827AcceptTypePresent_login),42);auto wire=encode(response.get());
            if(badCrc)wire.back()^=1;
            if(::send(client,(const char*)wire.data(),(int)wire.size(),0)!=(int)wire.size())throw Failure("malformed test send");
        }catch(...){peerError=std::current_exception();}if(client!=INVALID_SOCKET)closesocket(client);});
        unsigned observed=0;int receivedType=-2;Sink sink;
        sink.info=[](auto&,auto&){};sink.state=[](auto&,auto&){};sink.result=[](const Result&){};
        sink.packet=[&](const std::string&,bool rx,const PacketRecord&,int type,const Bytes &wire,bool){++observed;if(rx){receivedType=type;if(wire.empty())throw Failure("failure frame bytes lost");}};
        std::atomic<bool> stop{false};auto result=run(findCase("centerClient2rse_v2"),cfg,stop,sink);
        peer.join();closesocket(listener);if(peerError)std::rethrow_exception(peerError);
        if(result.size()!=1 || result[0].verdict!=Verdict::Fail || observed!=2 || receivedType!=(badCrc?-1:Iso14827PDUsPresent_ack))throw Failure("Rejected/undecodable RX must be observed before failure");
    }
    std::cout<<"PASS all-message delivery, repeats, NAK, CRC failure and wrong-domain reception\n";
}

void auditRegressionTests() {
    PacketRecord first,second;first.received=Tick{}+std::chrono::seconds(10);
    for(std::int64_t us:{899999,900000,1000000,3000000,3000001}) {
        second.received=first.received+std::chrono::microseconds(us);
        if(compareRetryTiming(first,second,1).within()!=(us>=900000 && us<=3000000))throw Failure("Retry timing boundary mismatch");
    }
    second.received=first.received+std::chrono::seconds(40);
    if(compareRetryTiming(first,second,40).earlyAllowanceUs!=100000)throw Failure("Retry allowance must be capped at 100ms");
    for(auto fault:{"bad_sub_oid","bad_sub_guarantee","bad_sub_format","bad_sub_mode"})
        scenario("rseServer2center_v2","normal_bsm",fault,Verdict::Fail);
    for(auto test:{"login_retry","subscription_retry","publication_retry"}) {
        const auto id=std::string(test)=="publication_retry"?"centerClient2rse_v2":"rseServer2center_v2";
        scenario(id,test,"early_retry",Verdict::Fail);
        scenario(id,test,"",Verdict::Pass);
    }
    adapterScenario(10,"SUCCESS","rseClient2center_v2","normal_tim","multi_tim");
    adapterScenario(11,"FAIL","rseClient2center_v2","normal_tim","multi_tim");
    adapterScenario(12,"SUCCESS","rseClient2center_v2","normal_tim","multi_tim");
    adapterScenario(13,"SUCCESS","rseClient2center_v2","normal_tim","multi_identical");
    adapterScenario(15,"SUCCESS","rseClient2center_v2","normal_tim","multi_tim");
    std::cout<<"PASS audit regressions: four correlated Subscription rejections; early and valid retries; timing boundaries; multiple payloads, reversed/duplicate/missing/mixed verdicts\n";
}
