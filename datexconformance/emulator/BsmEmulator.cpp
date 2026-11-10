#include "DatexWire.h"
#include "DatexSelectionPlan.h"
#include <dz1_cleanup.h>
#include <dz1_thread.h>
#include <windows.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace datex;
namespace {
std::atomic<bool> stopped{false};
BOOL WINAPI control(DWORD event) {
    if (event == CTRL_C_EVENT || event == CTRL_BREAK_EVENT || event == CTRL_CLOSE_EVENT) {
        stopped = true;
        return TRUE;
    }
    return FALSE;
}
Tick after(unsigned seconds) { return std::chrono::steady_clock::now() + std::chrono::seconds(seconds); }
bool timeout(const std::exception &e) { return std::string(e.what()) == "응답/관찰 시간 초과"; }
std::string readFile(const std::filesystem::path &path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) throw Failure("Cannot read configuration");
    std::ostringstream text;
    text << f.rdbuf();
    auto s = text.str();
    if (s.compare(0, 3, "\xef\xbb\xbf") == 0) s.erase(0, 3);
    return s;
}
std::string hex(const Bytes &bytes) {
    static const char *digits = "0123456789abcdef";
    std::string s;
    for (auto b : bytes) { s += digits[b >> 4]; s += digits[b & 15]; }
    return s;
}
struct Log {
    std::ofstream file;
    std::string mode, role, profile, plannedTest;
    std::vector<Message> messages;
    unsigned processed = 0;
    Log(const std::filesystem::path &path, std::string m, std::string r, std::string p,
        std::vector<Message> ms) : mode(m), role(r), profile(p), messages(std::move(ms)) {
        if (path.has_parent_path()) std::filesystem::create_directories(path.parent_path());
        if (std::filesystem::exists(path)) throw Failure("Log already exists; use a new path");
        file.open(path, std::ios::binary);
        if (!file) throw Failure("Cannot create evidence log");
    }
    void event(const std::string &name, const std::string &extra = "") {
        auto now = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        file << "{\"monotonicUs\":" << now << ",\"mode\":" << quote(mode)
             << ",\"role\":" << quote(role) << ",\"plannedTest\":" << quote(plannedTest) << ",\"event\":" << quote(name) << extra << "}\n";
        file.flush();
        if (!file) throw Failure("Evidence write failed");
    }
    Sink sink() {
        Sink s;
        s.state = [&](const std::string &test, const std::string &state) {
            event("state", ",\"test\":" + quote(test) + ",\"state\":" + quote(state));
        };
        s.info = [&](const std::string &test, const std::string &info) {
            event("info", ",\"test\":" + quote(test) + ",\"message\":" + quote(info));
            if (info == "LISTENING") std::cout << "LISTENING" << std::endl;
        };
        s.packet = [&](const std::string &test, bool rx, const PacketRecord &r, int type,
                       const Bytes &safeWire, bool redacted) {
            event("packet", ",\"test\":" + quote(test) + ",\"direction\":" + quote(rx ? "RX" : "TX") +
                ",\"packetTimeUs\":" + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(r.received.time_since_epoch()).count()) +
                ",\"packetNumber\":" + std::to_string(r.number) + ",\"pdu\":" + std::to_string(type) +
                ",\"redacted\":" + (redacted ? "true" : "false") + ",\"wireHex\":" + quote(hex(safeWire)));
        };
        s.validation = [&](const std::string &, const std::string &message, const Bytes &raw, const Bytes &json) {
            ++processed;
            auto found = std::find_if(messages.begin(), messages.end(), [&](const Message &m) { return message == m.name; });
            if (found == messages.end()) throw Failure("Decoded message is outside emulator profile");
            const std::string eventName = profile == "bsm" ? "bsm" : "payload";
            event(eventName + (mode == "emulator" ? "_processed" : "_decoded"),
                ",\"message\":" + quote(message) + ",\"psid\":" + std::to_string(found->psid) +
                ",\"messageId\":" + std::to_string(found->type) + ",\"rawHex\":" + quote(hex(raw)) +
                ",\"decodedJson\":" + quote(std::string(json.begin(), json.end())));
        };
        s.result = [&](const Result &r) {
            event("result", ",\"test\":" + quote(r.test) + ",\"verdict\":" + quote(verdictName(r.verdict)) +
                ",\"detail\":" + quote(r.detail));
            std::cout << r.test << " " << verdictName(r.verdict) << ": " << r.detail << std::endl;
        };
        return s;
    }
};
void serviceFred(Session &s, const Received &r) {
    if (r.message->pdu->present == Iso14827PDUsPresent_fred && !r.message->pdu->x.fred)
        s.send(fred(r.message->pktNbr));
}
Received response(Session &s, const PacketRecord &request, const Config &cfg,
                  const std::function<Pdu()> &recreate, const std::string &fault, Log &log) {
    for (unsigned attempt = 0; attempt < 3; ++attempt) {
        auto until = after(cfg.response);
        try {
            for (;;) {
                auto r = s.receive(until);
                auto p = r.message->pdu;
                if (p->present == Iso14827PDUsPresent_fred) { serviceFred(s, r); continue; }
                if (p->present == Iso14827PDUsPresent_ack && p->x.ack->pktNbr == request.number) return r;
                if (p->present == Iso14827PDUsPresent_nak && p->x.nak->pktNbr == request.number)
                    throw Failure("Request rejected by counterpart");
                throw Failure("Response does not match outstanding request");
            }
        } catch (const Failure &e) {
            if (!timeout(e) || attempt == 2) throw;
            log.event("retry", ",\"packetNumber\":" + std::to_string(request.number));
            if (fault == "changed-retry") s.send(recreate()); else s.resend(request);
        }
    }
    throw Failure("No response");
}
void requireAccept(const Received &r, Iso14827AcceptTypePresent kind) {
    auto p = r.message->pdu;
    if (p->present != Iso14827PDUsPresent_ack || !p->x.ack->acceptType ||
        p->x.ack->acceptType->present != kind) throw Failure("Unexpected Accept type");
}

// This client derives error responses from incoming messages, never from a test name.
void receivingClient(Session *listener, const Case &c, const Config &cfg, const Sink &sink, Log &log,
                  bool requestData, unsigned duration, const std::string &fault) {
    Session s(c, cfg, stopped, sink, log.role + "-client");
    if (cfg.tcpConnects(c)) s.open();
    else s.adopt(listener->acceptPeer(after(cfg.connectTimeout)));
    if (cfg.useInitiate) {
        auto r = s.receive(after(cfg.connectTimeout), false);
        auto p = r.message->pdu;
        if (p->present != Iso14827PDUsPresent_initiate || !p->x.initiate ||
            utf8Text(p->x.initiate->sender) != cfg.peerDomain || utf8Text(p->x.initiate->dest) != cfg.myDomain)
            throw Failure("Expected valid supplier Initiate before Login");
        log.event("initiate_received");
    }
    auto loginPacket = s.send(login(cfg, cfg.password));
    auto ack = response(s, loginPacket, cfg, [&] { return login(cfg, cfg.password); }, fault, log);
    requireAccept(ack, Iso14827AcceptTypePresent_login);
    if (oidText(ack.message->pdu->x.ack->acceptType->x.login) != "2.1.1") throw Failure("BER not negotiated");
    s.established();
    log.event("login_accepted");
    constexpr unsigned sid = 1;
    const auto subscribed = subscriptionCase(c, c.oid);
    if (requestData) {
        auto sub = s.send(subscribe(c, sid));
        auto a = response(s, sub, cfg, [&] { return subscribe(c, sid); }, fault, log);
        requireAccept(a, Iso14827AcceptTypePresent_singleSubscription);
        log.event("subscription_accepted", ",\"subscriptionSerial\":1");
    }
    std::map<unsigned, PacketRecord> seenPackets;
    std::set<unsigned> seenPublications;
    auto until = after(duration);
    s.send(fred());
    while (!stopped && std::chrono::steady_clock::now() < until) {
        Received r;
        try { r = s.receive(std::min(until, after(1))); }
        catch (const Failure &e) { if (timeout(e)) continue; throw; }
        auto p = r.message->pdu;
        if (p->present == Iso14827PDUsPresent_fred) { serviceFred(s, r); continue; }
        if (p->present == Iso14827PDUsPresent_term) {
            auto logout = pdu(Iso14827PDUsPresent_logout);
            logout->x.logout = Iso14827Logout_serverRequested;
            auto sent = s.send(std::move(logout));
            auto end = after(cfg.response);
            for (;;) {
                auto reply = s.receive(end, false);
                if (reply.message->pdu->present == Iso14827PDUsPresent_fred &&
                    reply.message->pdu->x.fred == sent.number) break;
                serviceFred(s, reply);
            }
            log.event("session_closed", ",\"reason\":\"server_requested\"");
            return;
        }
        if (p->present != Iso14827PDUsPresent_publication) throw Failure("Unexpected PDU at receiving client");
        auto duplicate = seenPackets.find(r.observation.number);
        if (duplicate != seenPackets.end()) {
            if (!compareRetry(duplicate->second, r.observation).same()) throw Failure("Changed duplicate datagram");
            s.send(accept(r.message->pktNbr, Iso14827AcceptTypePresent_publication));
            log.event("identical_publication_retry", ",\"packetNumber\":" + std::to_string(r.observation.number));
            continue;
        }
        auto items = publicationData(p->x.publication);
        if (p->x.publication->guaranteed) s.send(accept(r.message->pktNbr, Iso14827AcceptTypePresent_publication));
        for (auto d : items) {
            int reason = -1;
            if (!requestData || d->subscriptionSerial != sid) reason = Iso14827RejectPubDataReason_unknownSubscription;
            else if (seenPublications.count(d->serial)) reason = Iso14827RejectPubDataReason_repeatedPublicationNbr;
            else if (d->serial != 1) reason = Iso14827RejectPubDataReason_unknownPublicationNbr;
            else if (!d->type || d->type->present != Iso14827PublicationTypePresent_msg || !d->type->x.msg)
                reason = Iso14827RejectPubDataReason_invalidPublicationMsgContent;
            else {
                auto oid = oidText(d->type->x.msg->oid);
                if (oid != c.oid)
                    reason = oid == "1.0.15784.1.0.1" || oid == "1.0.15784.1.0.2" || oid == "1.0.14827.1.1.0"
                        ? Iso14827RejectPubDataReason_invalidPublicationMsgId
                        : Iso14827RejectPubDataReason_unknownPublicationMsgId;
                else {
                    try {
                        bool found = false;
                        for (const auto &m : subscribed.messages) {
                            try { validatePayload(subscribed, m, d, &sink, m.name); found = true; }
                            catch (const Failure &error) {
                                if (std::string(error.what()).find("요청한 메시지가 Publication에 없습니다:") != 0) throw;
                            }
                        }
                        if (!found) throw Failure("No supported payload in Publication");
                    } catch (const Failure &) { reason = Iso14827RejectPubDataReason_invalidPublicationMsgContent; }
                }
            }
            if (reason >= 0) {
                if (fault == "wrong-reject") reason = Iso14827RejectPubDataReason_other;
                s.send(reject(0, Iso14827RejectTypePresent_pubData, reason, d->subscriptionSerial, d->serial));
                log.event("publication_rejected", ",\"reason\":" + std::to_string(reason) +
                    ",\"subscriptionSerial\":" + std::to_string(d->subscriptionSerial) +
                    ",\"publicationSerial\":" + std::to_string(d->serial));
            } else {
                seenPublications.insert(d->serial);
                log.event("application_processed", ",\"packetNumber\":" + std::to_string(r.observation.number) +
                    ",\"subscriptionSerial\":" + std::to_string(d->subscriptionSerial) +
                    ",\"publicationSerial\":" + std::to_string(d->serial));
            }
        }
        seenPackets.emplace(r.observation.number, r.observation);
        if (seenPackets.size() > 256) seenPackets.erase(seenPackets.begin());
        s.send(fred());
    }
    if (stopped) throw Stopped();
    throw Failure("Emulator duration expired without orderly session end");
}

int loginProblem(const Received &r, const Config &cfg) {
    if (r.message->pdu->present != Iso14827PDUsPresent_login || !r.message->pdu->x.login)
        throw Failure("Expected Login");
    auto l = r.message->pdu->x.login;
    if (utf8Text(l->sender) != cfg.peerDomain || utf8Text(l->dest) != cfg.myDomain)
        return Iso14827RejectLogin_unknownDomainName;
    if (octetText(l->user) != cfg.user || octetText(l->pass) != cfg.password)
        return Iso14827RejectLogin_invalidPassword;
    if (l->initiator != (cfg.useInitiate ? Iso14827LoginInitiator_serverInitiated : Iso14827LoginInitiator_clientInitiated))
        return Iso14827RejectLogin_other;
    unsigned count = 0; Dz1Error error = {};
    auto rules = l->encRules ? l->encRules->get_array(l->encRules, &count, &error) : nullptr;
    bool supported = false;
    for (unsigned n = 0; n < count; ++n) if (oidText(rules[n]) == "2.1.1") supported = true;
    Dz1Free(rules);
    if (!supported) return Iso14827RejectLogin_other;
    return -1;
}
struct Pending { PacketRecord packet; Tick due; unsigned retries = 0; };
void providingServer(Session *listener, const Case &c, Config cfg, const Sink &sink, Log &log, unsigned duration,
               const std::string &fault, bool multiTim = false) {
    Session s(c, cfg, stopped, sink, log.role + "-server");
    if (cfg.tcpConnects(c)) s.open();
    else s.adopt(listener->acceptPeer(after(cfg.connectTimeout)));
    if (cfg.useInitiate) { s.send(initiate(cfg)); log.event("initiate_sent"); }
    auto first = s.receive(after(cfg.connectTimeout), false);
    int problem = loginProblem(first, cfg);
    if (problem >= 0) {
        if (fault == "wrong-reject") problem = Iso14827RejectLogin_other;
        s.send(reject(first.message->pktNbr, Iso14827RejectTypePresent_login, problem));
        log.event("login_rejected", ",\"reason\":" + std::to_string(problem));
        return;
    }
    auto l = first.message->pdu->x.login;
    if (l->hbDur <= 0 || l->timeout <= 0) throw Failure("Invalid Login time parameters");
    cfg.heartbeat = unsigned(l->hbDur);
    cfg.response = unsigned(l->timeout);
    s.send(accept(first.message->pktNbr, Iso14827AcceptTypePresent_login));
    s.established();
    log.event("login_accepted", ",\"heartbeatMaxSeconds\":" + std::to_string(cfg.heartbeat) +
        ",\"responseSeconds\":" + std::to_string(cfg.response));
    bool active = false, periodic = false, canceled = false, firstHeartbeat = false;
    // This plan controls only the extra TCP stimulus; rejection derives from an existing session.
    bool additionalInitiate = cfg.useInitiate && log.plannedTest == "test_duplicate_login";
    Case provided = c;
    unsigned sid = 0, serial = 1, period = 0;
    Tick next{};
    std::map<unsigned, Pending> pending;
    std::map<unsigned, std::pair<PacketRecord, PacketRecord>> requests;
    requests.emplace(first.observation.number, std::make_pair(first.observation, PacketRecord{}));
    auto publish = [&] {
        auto messages=provided.messages;
        if(multiTim && messages.size()==1 && std::string(messages.front().name)=="tim") {
            auto extra=messages.front();extra.name="tim_speed";extra.businessProfile=1;messages.push_back(extra);
        }
        auto sent = s.send(publicationBundle(provided, messages, sid, serial++,
            fault == "bad-content" ? "invalidPublicationMsgContent" : ""));
        pending[sent.number] = {sent, after(cfg.response), 0};
        log.event(log.profile == "bsm" ? "bsm_published" : "payload_published", ",\"packetNumber\":" + std::to_string(sent.number) +
            ",\"subscriptionSerial\":" + std::to_string(sid)+",\"payloadCount\":"+std::to_string(messages.size()));
    };
    auto until = after(duration);
    while (!stopped && std::chrono::steady_clock::now() < until) {
        auto now = std::chrono::steady_clock::now();
        if (active && periodic && !canceled && now >= next) {
            publish();
            next += std::chrono::seconds(period * (fault == "slow-period" ? 2 : 1));
        }
        for (auto &entry : pending) {
            auto &p = entry.second;
            if (canceled) continue; // Accept late ACKs for pre-cancel packets, but issue no new retries.
            if (now < p.due) continue;
            if (p.retries++ >= 2) throw Failure("Publication ACK retry limit");
            if (fault == "changed-retry") s.send(publicationBundle(provided, provided.messages, sid, serial++));
            else s.resend(p.packet);
            p.due = after(cfg.response);
            log.event("publication_retried", ",\"packetNumber\":" + std::to_string(p.packet.number));
        }
        // Duplicate-login connections are handled without interrupting the original session.
        if (!active && (listener || (additionalInitiate && firstHeartbeat))) {
            try {
                Session other(c, cfg, stopped, sink, "duplicate-connection");
                if (listener) other.adopt(listener->acceptPeer(std::chrono::steady_clock::now() + std::chrono::milliseconds(1)));
                else { additionalInitiate = false; other.open(); }
                if (cfg.useInitiate) other.send(initiate(cfg));
                auto request = other.receive(after(cfg.response), false);
                auto reason = loginProblem(request, cfg);
                if (reason < 0) reason = Iso14827RejectLogin_sessionExist;
                if (fault == "wrong-reject") reason = Iso14827RejectLogin_other;
                other.send(reject(request.message->pktNbr, Iso14827RejectTypePresent_login, reason));
                log.event("duplicate_login_rejected", ",\"reason\":" + std::to_string(reason));
            } catch (const Failure &e) {
                if (std::string(e.what()) != "시험대상 접속 대기 시간 초과") throw;
            }
        }
        Received r;
        try { r = s.receive(std::min(until, std::chrono::steady_clock::now() + std::chrono::milliseconds(25))); }
        catch (const Failure &e) {
            if (timeout(e)) continue;
            if (std::string(e.what()).find("HeartbeatDurationMax 초과") == 0) {
                log.event("session_closed", ",\"reason\":\"heartbeat_timeout\",\"lastReceiveUs\":" +
                    std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(s.lastReceive().time_since_epoch()).count()) +
                    ",\"heartbeatSeconds\":" + std::to_string(cfg.heartbeat));
                return;
            }
            throw;
        }
        auto p = r.message->pdu;
        if (p->present == Iso14827PDUsPresent_fred) { serviceFred(s, r); firstHeartbeat = true; continue; }
        if (p->present == Iso14827PDUsPresent_logout) {
            s.send(fred(r.message->pktNbr));
            log.event("session_closed", ",\"reason\":\"client_requested\"");
            return;
        }
        if (p->present == Iso14827PDUsPresent_ack) {
            if (!p->x.ack || !p->x.ack->acceptType ||
                p->x.ack->acceptType->present != Iso14827AcceptTypePresent_publication ||
                !pending.erase(p->x.ack->pktNbr)) throw Failure("Unexpected Publication Accept");
            log.event("publication_accepted", ",\"packetNumber\":" + std::to_string(p->x.ack->pktNbr));
            continue;
        }
        if (p->present == Iso14827PDUsPresent_nak) {
            log.event("peer_reject");
            continue;
        }
        if (p->present != Iso14827PDUsPresent_subscription) throw Failure("Unexpected PDU at RSE");
        auto duplicate = requests.find(r.observation.number);
        if (duplicate != requests.end()) {
            if (!compareRetry(duplicate->second.first, r.observation).same()) throw Failure("Changed request retry");
            if (!duplicate->second.second.wire.empty()) s.resend(duplicate->second.second);
            continue;
        }
        auto sub = p->x.subscription;
        if (!sub || !sub->serial || !sub->type) throw Failure("Malformed Subscription");
        PacketRecord reply;
        if (sub->type->present == Iso14827SubscriptionTypePresent_reason) {
            if (!active || sub->serial != sid || sub->type->x.reason != Iso14827SubscriptionCancel_dataNotNeeded)
                throw Failure("Cancellation does not match subscription");
            canceled = true;
            reply = s.send(accept(r.message->pktNbr, Iso14827AcceptTypePresent_registeredSubscription, sid));
            log.event("subscription_canceled", ",\"subscriptionSerial\":" + std::to_string(sid));
            if (fault == "after-cancel") publish();
        } else if (sub->type->present == Iso14827SubscriptionTypePresent_data) {
            auto d = sub->type->x.data;
            if (!d || !d->msg || !d->mode) throw Failure("Incomplete Subscription");
            bool known = true;
            Case requested = c;
            try { requested = subscriptionCase(c, oidText(d->msg->oid)); }
            catch (const Failure &) { known = false; }
            if (!known) {
                reply = s.send(reject(r.message->pktNbr, Iso14827RejectTypePresent_subscription,
                    fault == "wrong-reject" ? Iso14827RejectSubscription_other :
                    Iso14827RejectSubscription_unknownSubscriptionMsgId));
                log.event("subscription_rejected");
            } else {
                if (!d->guarantee || d->fmt != Iso14827SubscriptionDataFormat_dataPacket)
                    throw Failure("Unsupported format/Guarantee profile");
                provided = requested;
                sid = sub->serial;
                periodic = d->mode->present == Iso14827SubscriptionDataModePresent_periodic;
                if (periodic) {
                    auto reg = d->mode->x.periodic;
                    if (!reg || reg->present != Iso14827RegisteredPresent_continuous || !reg->x.continuous ||
                        reg->x.continuous->updateDelay <= 0) throw Failure("Unsupported periodic subscription");
                    period = unsigned(reg->x.continuous->updateDelay);
                } else if (d->mode->present != Iso14827SubscriptionDataModePresent_single)
                    throw Failure("Only single/periodic subscriptions are supported");
                reply = s.send(accept(r.message->pktNbr, periodic ? Iso14827AcceptTypePresent_registeredSubscription :
                    Iso14827AcceptTypePresent_singleSubscription, sid));
                active = true;
                canceled = false;
                serial = 1;
                publish();
                next = std::chrono::steady_clock::now() + std::chrono::seconds(period * (fault == "slow-period" ? 2 : 1));
            }
        } else throw Failure("Unsupported Subscription choice");
        requests.emplace(r.observation.number, std::make_pair(r.observation, reply));
    }
    if (stopped) throw Stopped();
    throw Failure("Emulator duration expired without orderly session end");
}
} // namespace

int main(int argc, char **argv) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCtrlHandler(control, TRUE);
    std::map<std::string, std::string> args;
    for (int i = 1; i < argc; ++i) {
        std::string key = argv[i];
        if (key == "--help") {
            std::cout << "DATEX emulator and local verification driver\n"
                         "--profile bsm|traffic|signal --case CASE --message all|comma-separated-names\n"
                         "--mode emulator|tester --role rse|center|vehicle|signalserver --config FILE --log FILE\n"
                         "--request single|session --duration SECONDS --sessions COUNT\n"
                         "--plan FILE: follow selected testName list in UI order (emulator only)\n"
                         "--multi-tim true|false: publish two valid TIM payloads in a normal TIM provider session\n"
                         "--fault none|wrong-reject|changed-retry|bad-content|after-cancel|slow-period\n"
                         "Tester role selects the SUT: rse=centerClient2rse_v2, center=rseServer2center_v2.\n";
            return 0;
        }
        if (key.rfind("--", 0) != 0 || i + 1 == argc || args.count(key)) { std::cerr << "Invalid arguments\n"; return 2; }
        args[key] = argv[++i];
    }
    std::unique_ptr<Log> log;
    try {
        for (auto &a : args)
            if (!std::set<std::string>{"--mode","--role","--config","--log","--request","--duration","--sessions","--fault","--profile","--message","--case","--plan","--multi-tim"}.count(a.first))
                throw Failure("Unknown argument: " + a.first);
        auto mode = args.at("--mode"), role = args.at("--role");
        if ((mode != "tester" && mode != "emulator") || (role != "rse" && role != "center" && role != "vehicle" && role != "signalserver")) throw Failure("Invalid mode/role");
        const auto profile = args.count("--profile") ? args["--profile"] : "bsm";
        if (profile != "bsm" && profile != "traffic" && profile != "signal") throw Failure("Unknown profile");
        if (!args.count("--case") && role != "rse" && role != "center") throw Failure("Vehicle/signal role requires --case");
        const auto &target = findCase(args.count("--case") ? args["--case"] :
            profile == "bsm" ? (role == "rse" ? "centerClient2rse_v2" : "rseServer2center_v2") :
            (role == "center" ? "rseClient2center_v2" : "centerServer2rse_v2"));
        std::vector<SelectionStep> plan;
        if (args.count("--plan")) {
            if (mode != "emulator" || args.count("--message") || args.count("--request") || args.count("--sessions"))
                throw Failure("--plan requires emulator mode and replaces message/request/sessions options");
            plan = selectionPlan(target, readFile(std::filesystem::u8path(args["--plan"])));
        }
        Case c = target;
        const auto message = args.count("--message") ? args["--message"] : "all";
        if (message == "all" && plan.empty() && mode == "emulator") {
            c.messages.erase(std::remove_if(c.messages.begin(), c.messages.end(), [](const Message &m) { return m.businessProfile != 0; }), c.messages.end());
        }
        if (message != "all") {
            c.messages.clear();
            std::istringstream names(message);
            std::string name;
            while (std::getline(names, name, ',')) {
                auto found = std::find_if(target.messages.begin(), target.messages.end(), [&](const Message &m) { return name == m.name; });
                if (found == target.messages.end()) throw Failure("Message is outside the selected profile");
                c.messages.push_back(*found);
            }
            if (c.messages.empty()) throw Failure("Empty message selection");
            c.oid = messageCase(target, c.messages.front()).oid;
        }
        if (mode == "emulator") c.role = c.role == Role::Client ? Role::Server : Role::Client;
        const auto multiTimOption=args.count("--multi-tim")?args["--multi-tim"]:"false";
        if(multiTimOption!="true" && multiTimOption!="false") throw Failure("--multi-tim must be true or false");
        const bool multiTim=multiTimOption=="true";
        if(multiTim && (mode!="emulator" || c.role!=Role::Server || profile!="traffic"))
            throw Failure("--multi-tim requires a traffic information-providing emulator");
        auto cfg = Config::parse(c, readFile(std::filesystem::u8path(args.at("--config"))));
        unsigned duration = args.count("--duration") ? unsigned(std::stoul(args["--duration"])) : 600;
        unsigned sessions = args.count("--sessions") ? unsigned(std::stoul(args["--sessions"])) : 1;
        if (!duration || duration > 86400 || !sessions || sessions > 1000) throw Failure("Invalid duration/sessions");
        if (!plan.empty()) sessions = static_cast<unsigned>(plan.size());
        const auto fault = args.count("--fault") ? args["--fault"] : "none";
        if (!std::set<std::string>{"none","wrong-reject","changed-retry","bad-content","after-cancel","slow-period"}.count(fault))
            throw Failure("Unknown fault mode");
        const auto request = args.count("--request") ? args["--request"] : "single";
        if (request != "single" && request != "session") throw Failure("Unknown request mode");
        Dz1Cleanup_init();
        Dz1Error e = {};
        Dz1Thread_init(DZ1_THREAD_LOG_BASIS, &e);
        if (e.code) throw Failure("SDK initialization failed");
        log.reset(new Log(std::filesystem::u8path(args.at("--log")), mode, role, profile, c.messages));
        auto sink = log->sink();
        log->event("started", ",\"multiTim\":" + std::string(multiTim?"true":"false") + ",\"fault\":" + quote(fault) + ",\"profile\":" + quote(profile) +
            ",\"oid\":" + quote(c.oid) + ",\"case\":" + quote(c.id));
        int code = 0;
        if (mode == "tester") {
            auto results = run(c, cfg, stopped, sink);
            for (auto &r : results)
                if (r.verdict != Verdict::Pass) code = 1;
            log->event("finished", ",\"tests\":" + std::to_string(results.size()) + ",\"exitCode\":" + std::to_string(code));
        } else {
            std::unique_ptr<Session> listener;
            if (!cfg.tcpConnects(c)) {
                listener.reset(new Session(c, cfg, stopped, sink, role + "-listener"));
                listener->openListener();
            }
            for (unsigned n = 0; n < sessions && !stopped; ++n) {
                const Case &sessionCase = plan.empty() ? c : plan[n].counterpart;
                const bool requestData = plan.empty() ? request == "single" : plan[n].requestData;
                log->plannedTest = plan.empty() ? "" : "test_" + plan[n].test;
                log->event("session_start", ",\"session\":" + std::to_string(n + 1) + ",\"message\":" + quote(sessionCase.messages.front().name) + ",\"oid\":" + quote(sessionCase.oid) + ",\"requestData\":" + (requestData ? "true" : "false"));
                try {
                    if (c.role == Role::Server) providingServer(listener.get(), sessionCase, cfg, sink, *log, duration, fault, multiTim);
                    else receivingClient(listener.get(), sessionCase, cfg, sink, *log, requestData, duration, fault);
                } catch (const Stopped &) { throw; }
                catch (const std::exception &error) {
                    if (plan.empty()) throw;
                    code = 1;
                    log->event("session_error", ",\"message\":" + quote(error.what()));
                }
                log->event("session_end", ",\"session\":" + std::to_string(n + 1));
            }
            log->event("finished", (profile == "bsm" ? ",\"processedBsm\":" : ",\"processedPayloads\":") + std::to_string(log->processed) + ",\"exitCode\":" + std::to_string(code));
            std::cout << "EMULATOR COMPLETE " << role << (profile == "bsm" ? " processedBSM=" : " processedPayloads=") << log->processed << std::endl;
        }
        return code;
    } catch (const std::exception &e) {
        if (log) { try { log->event("error", ",\"message\":" + quote(e.what())); } catch (...) {} }
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 2;
    }
}
