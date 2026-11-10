#include "DatexCore.h"
#include "DatexDataView.h"
#include "DatexMessageView.h"
#include "DatexSelectionPlan.h"
#include <fstream>
#include "DatexWire.h"
#include "DatexSamples.h"
extern "C" int DatexTrafficConversionRegression(unsigned char *, unsigned);
extern "C" Dz1Binary *DatexPayload_timProfile(unsigned char *, size_t, unsigned);
extern "C" int DatexPayload_checkTimProfile(unsigned char *, size_t, unsigned);
extern "C" Dz1Binary *DatexPayload_json(unsigned, unsigned char *, size_t);
extern "C" Dz1Binary *DatexPayload_timRegionalFixture(unsigned char *, size_t, unsigned);
extern "C" Dz1Binary *DatexPayload_timRegionalSummary(unsigned char *, size_t);
extern "C" int DatexPayload_validate(unsigned, unsigned char *, size_t);
extern "C" int DatexSignalEnvelopeRegression(unsigned char *, unsigned, unsigned);
#include <iostream>
#include <cstdlib>
#include <dz1_cleanup.h>
#include <dz1_thread.h>
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
static LONG crash(EXCEPTION_POINTERS *e) {
    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);
    STACKFRAME64 f = {};
    f.AddrPC.Offset = e->ContextRecord->Rip;
    f.AddrPC.Mode = AddrModeFlat;
    f.AddrFrame.Offset = e->ContextRecord->Rbp;
    f.AddrFrame.Mode = AddrModeFlat;
    f.AddrStack.Offset = e->ContextRecord->Rsp;
    f.AddrStack.Mode = AddrModeFlat;
    for (int i = 0; i < 12; ++i) {
        char storage[sizeof(SYMBOL_INFO) + 512] = {};
        auto sym = (SYMBOL_INFO *)storage;
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym->MaxNameLen = 511;
        DWORD64 off = 0;
        SymFromAddr(process, f.AddrPC.Offset, &off, sym);
        std::cerr << sym->Name << " + " << off << "\n";
        if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, GetCurrentThread(), &f, e->ContextRecord, NULL,
                         SymFunctionTableAccess64, SymGetModuleBase64, NULL))
            break;
    }
    return EXCEPTION_EXECUTE_HANDLER;
}
using namespace datex;
static void require(bool value, const char *what) {
    if (!value)
        throw std::runtime_error(what);
}
template <class F> static void rejects(F f, const char *name) {
    bool failed = false;
    try {
        f();
    } catch (const Failure &) {
        failed = true;
    }
    require(failed, name);
}
void tcpLifecycleTests();
void initiationTests();
static void tcpConfigurationTests() {
    for (const auto &c : cases()) for (bool mode : {false, true}) {
        const bool active = (c.role == Role::Client) != mode;
        std::string prefix = "{\"my_domain\":\"TESTER\",\"peer_domain\":\"PEER\",\"user\":\"u\",\"pass\":\"p\",\"test_session\":true,\"use_initiate\":" + std::string(mode ? "true" : "false");
        auto full = Config::parse(c, prefix + ",\"peer_ip\":\"127.0.0.1\",\"peer_port\":41001,\"local_port\":41002}");
        require(full.port == (active ? 41001u : 41002u), "selected TCP port follows initiation mode");
        require(full.tcpConnects(c) == active, "actual TCP role matches independent expectation");
        auto minimal = Config::parse(c, prefix + (active ? ",\"peer_ip\":\"127.0.0.1\",\"peer_port\":41001}" : ",\"local_port\":41002}"));
        require(minimal.port == full.port, "inactive endpoint settings are optional");
        rejects([&] { Config::parse(c, prefix + (active ? ",\"local_port\":41002}" : ",\"peer_ip\":\"127.0.0.1\",\"peer_port\":41001}")); }, "wrong-direction-only endpoint is rejected");
        auto ui = configureUI(c);
        for (const auto *key : {"peer_ip", "peer_port", "local_port", "use_initiate"}) require(ui.find(key) != std::string::npos, "both endpoint settings are available in web UI");
    }
    std::cout << "PASS TCP configuration: 14 cases x 2 modes, distinct endpoint ports, optional unused fields and missing required fields\n";
}
void loopbackTests();
void adapterTests();
void stopTests();
void userLogTests();
void linkedDataAdapterTests();
void allMessageAdapterTests();
void publicationAcceptanceTests();
void auditRegressionTests();
void abnormalSessionTests();
static void linkedDataTests() {
    std::set<std::string> checked;
    Config cfg; cfg.myDomain="actual-sender"; cfg.peerDomain="actual-receiver";
    std::ofstream examples("linked-data-native-samples.jsonl",std::ios::binary);
    for (const auto &c : cases()) for (auto m : c.messages) {
        if (!checked.insert(m.name).second) continue;
        auto sent=packet(cfg,publication(c,m,77,303),901);
        auto wire=encode(sent.get());
        auto records=inspectLinkedData(c,wire,std::string("normal_")+m.name);
        require(records.size()==1 && records[0].message==m.name, "observed payload matched selected message");
        auto &record=records[0];
        require(record.subscription==77 && record.publication==303, "actual subscription/publication preserved");
        require(!record.decodedJson.empty() && !record.raw.empty(), "actual raw payload and decoded content retained");
        auto summary=linkedDataSummary(record);
        std::string text;for (const auto &line:summary) text+=line+"\n";
        require(text.find("표시 변환")==std::string::npos && text.find("요약을 생성하지")==std::string::npos, "all message profiles have a usable summary");
        if (std::string(m.name)=="bsm") require(text.find("차량 식별자 0x41 0x42 0x43 0x44")!=std::string::npos && text.find("속도 10")!=std::string::npos,"BSM actual values");
        if (std::string(m.name)=="spat") require(text.find("교차로 ID 100")!=std::string::npos && text.find("신호군 ID 4")!=std::string::npos,"SPaT actual values");
        if (std::string(m.name)=="tls") {
            require(text.find("신호등 ID 1234")!=std::string::npos,"TLSM actual ID");
            auto changed=record;auto at=changed.decodedJson.find("1234");changed.decodedJson.replace(at,4,"98765");
            auto newSummary=linkedDataSummary(changed);require(newSummary.front().find("98765")!=std::string::npos,"summary follows changed data, not canned samples");
        }
        if (std::string(m.name)=="tim_regional") require(text.find("SPEED 50")!=std::string::npos && text.find("BeltId_0001")!=std::string::npos,"actual nested KOR text and link ID");
        examples << "{\"message\":" << quote(m.name) << ",\"summary\":" << quote(text) << ",\"decodedJson\":" << quote(record.decodedJson) << ",\"regionalJson\":" << quote(record.regionalJson) << "}\n";
    }
    std::string large=R"({"padding":")" + std::string(70000,'x') + R"(","coreData":{"speed":37}})";
    LinkedData full;full.message="bsm";full.decodedJson=large;
    require(linkedDataSummary(full)[1].find("속도 37")!=std::string::npos,"large decoded data is not constrained by config-size limits");
    rejects([&] { Json::parse(large); },"configuration size limit unchanged");
    require(checked.size()==9,"all nine message profiles summarized");
    const auto &bsm=findCase("centerClient2rse_v2");
    auto bad=packet(cfg,publication(bsm,bsm.messages.front(),77,303,"invalidPublicationMsgContent"),902);
    auto errors=inspectLinkedData(bsm,encode(bad.get()),"invalidPublicationMsgContent");
    require(errors.size()==1 && errors[0].decodedJson.empty() && !errors[0].raw.empty() && !errors[0].note.empty(),"malformed actual data preserved without fabricated values");
    LinkedData zeros;zeros.message="bsm";zeros.decodedJson=R"({"coreData":{"speed":0,"lat":null,"id":"NEW-ID"}})";
    auto summary=linkedDataSummary(zeros);
    require(summary[0].find("NEW-ID")!=std::string::npos && summary[1].find("속도 0")!=std::string::npos && summary[1].find("위도 미제공")!=std::string::npos,"zero distinct from missing");
    std::cout << "PASS linked data: nine profiles, actual IDs and values, nested KOR, malformed content, missing/zero distinctions\n";
}
static void allMessageViewTests() {
    Config cfg;cfg.myDomain="TESTER";cfg.peerDomain="SUT";cfg.user="test-user";cfg.password="UNIQUE-SECRET-PASSWORD";
    const auto &c=findCase("centerClient2rse_v2");
    std::vector<Pdu> messages;
    auto initiator=pdu(Iso14827PDUsPresent_initiate);Dz1Error err={};initiator->x.initiate=Iso14827Initiate_gen(&err);
    initiator->x.initiate->sender=Dz1Asn1UTF8Str_new((u8_t*)"A",1,&err);initiator->x.initiate->dest=Dz1Asn1UTF8Str_new((u8_t*)"B",1,&err);
    messages.push_back(std::move(initiator));messages.push_back(login(cfg,cfg.password));
    messages.push_back(fred());messages.push_back(fred(27));
    auto term=pdu(Iso14827PDUsPresent_term);term->x.term=Iso14827Terminate_serverRequested;messages.push_back(std::move(term));
    auto logout=pdu(Iso14827PDUsPresent_logout);logout->x.logout=Iso14827Logout_clientRequested;messages.push_back(std::move(logout));
    messages.push_back(subscribe(c,77));messages.push_back(subscribe(c,77,15));messages.push_back(cancel(77));
    messages.push_back(publication(c,c.messages.front(),77,303));
    auto transfer=pdu(Iso14827PDUsPresent_transferDone);transfer->x.transferDone=Iso14827TransferDone_gen(&err);transfer->x.transferDone->filename=Dz1Asn1UTF8Str_new((u8_t*)"test.bin",8,&err);transfer->x.transferDone->isSuccess=TRUE;messages.push_back(std::move(transfer));
    messages.push_back(accept(23,Iso14827AcceptTypePresent_login));
    messages.push_back(reject(23,Iso14827RejectTypePresent_login,Iso14827RejectLogin_invalidPassword));
    messages.push_back(reject(0,Iso14827RejectTypePresent_pubData,Iso14827RejectPubDataReason_invalidPublicationMsgContent,77,303));
    unsigned n=0;
    for(auto &p:messages){auto msg=packet(cfg,std::move(p),++n);auto wire=encode(msg.get());
        auto view=completeMessageView(c,wire,"normal_bsm");auto parsed=Json::parseData(view.details);auto auth=parsed.get("ISO 14827 C2CAuthMsg");
        require(view.details.find('\n')==std::string::npos && view.details.find('\r')==std::string::npos,"complete details remain one JSONL record");
        require(auth && auth->get("packetNumber")->text==std::to_string(n),"actual protocol packet number preserved");
        require(auth->get("pdu")->get("body")->kind!=Json::Null,"all ten PDU body choices represented");
        require(view.details.find(cfg.password)==std::string::npos && view.details.find(dataHex(Bytes(cfg.password.begin(),cfg.password.end())))==std::string::npos,"password hidden in content and raw hex");
    }
    auto authLogin=packet(cfg,login(cfg,cfg.password),700);
    Dz1Asn1OctetStr_del(authLogin->authInfo);authLogin->authInfo=Dz1Asn1OctetStr_new((u8_t*)"PRIVATE-TOKEN",13,&err);
    auto hidden=completeMessageView(c,encode(authLogin.get()),"session").details;
    require(hidden.find("PRIVATE-TOKEN")==std::string::npos && hidden.find("505249564154452d544f4b454e")==std::string::npos,"auth material redacted");
    std::string longValue;for(int i=0;i<15000;++i)longValue+="실제값";
    auto original=message_view::object({{"내용",quote(longValue)}});auto parts=messageParts("\"관측 순번\":17",original);std::string restored;
    for(auto &part:parts){auto j=Json::parseData(part.json);restored+=j.get("분할 데이터")->text;}
    require(parts.size()>1 && restored==original,"all large-message parts are preserved on UTF-8 boundaries");
    std::cout<<"PASS all message views: ten PDU types, header/body, password/auth redaction and large-message reconstruction\n";
}
static void selectionTests() {
    unsigned total=0;
    for(const auto &c:cases()) {
        const auto keys=availableTests(c);std::string list="[";
        for(auto i=keys.rbegin();i!=keys.rend();++i){if(list.size()>1)list+=',';list+=quote("test_"+*i);}list+=']';
        const auto document=[&](const std::string &v){return "{\"case\":"+quote(c.id)+",\"tests\":"+v+"}";};
        const auto all=selectionPlan(c,document(list));require(all.size()==keys.size(),"all selections present");
        for(size_t i=0;i<all.size();++i){
            require(all[i].test==keys[i],"fixed UI order independent of selection input order");
            require(all[i].counterpart.role!=c.role,"opposite peer role");
            require(all[i].requestData==(keys[i]!="session"&&keys[i]!="login_retry"),"session-only vs data-request operation");
            if(keys[i].compare(0,7,"normal_")==0){
                require(keys[i]==std::string("normal_")+all[i].counterpart.messages[0].name,"exact fixture per selected message");
                auto m=all[i].counterpart.messages[0];require(std::string(all[i].counterpart.oid)==(m.oid?m.oid:c.oid),"per-message subscription OID");
            }
        }
        auto single=selectionPlan(c,document("["+quote("test_"+keys.back())+"]"));require(single.size()==1&&single[0].test==keys.back(),"single item");
        auto subset=selectionPlan(c,document("["+quote("test_"+keys.back())+",\"test_session\"]"));require(subset.size()==2&&subset[0].test=="session"&&subset[1].test==keys.back(),"selected subset only");
        rejects([&]{selectionPlan(c,document("[]"));},"empty selection rejected");
        rejects([&]{selectionPlan(c,document("[\"test_session\",\"session\"]"));},"duplicate selection rejected");
        rejects([&]{selectionPlan(c,document("[\"test_missing\"]"));},"unknown selection rejected");
        total+=(unsigned)keys.size();
    }
    require(total==152,"selection preserves existing catalog");
    std::cout<<"PASS selection plans: 14 configurations, 152 items, single/subset/all, roles, OIDs, invalid selections\n";
}
int main(int argc, char **argv) {
    SetUnhandledExceptionFilter(crash);
    Dz1Cleanup_init();
    Dz1Error initError = {};
    Dz1Thread_init(DZ1_THREAD_LOG_BASIS, &initError);
    try {
        if (argc > 1 && std::string(argv[1]) == "--tcp-lifecycle") { tcpLifecycleTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--initiation") { tcpConfigurationTests(); initiationTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--audit-regression") { auditRegressionTests(); adapterTests(); stopTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--state-contract") { adapterTests(); abnormalSessionTests(); stopTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--abnormal-session") { abnormalSessionTests(); stopTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--publication-acceptance") { publicationAcceptanceTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--selection") { selectionTests(); linkedDataAdapterTests(); stopTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--all-messages") { allMessageViewTests(); allMessageAdapterTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--linked-data") { linkedDataTests(); linkedDataAdapterTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--user-logs") { userLogTests(); return 0; }
        if (argc > 1 && std::string(argv[1]) == "--signal-provider") {
            const auto &c = findCase("centerClient2signalserver_v2");
            require(c.role == Role::Client && availableTests(c).size() == 9, "signal provider tester role and items");
            require(configureUI(c).find("TLSM 정보제공 시험") != std::string::npos, "TLSM provider label");
            auto out = publicationBundle(c, c.messages, 1, 1);
            unsigned decoded = 0;
            Sink sink;
            sink.validation = [&](const std::string &, const std::string &name, const Bytes &, const Bytes &body) {
                auto value = Json::parse(std::string(body.begin(), body.end()));
                require(name == "spat" ? value.get("intersections") != nullptr : value.get("trafficLightID") != nullptr, "decoded message root");
                ++decoded;
            };
            for (const auto &m : c.messages) validatePayload(c, m, publicationData(out->x.publication).front(), &sink, m.name);
            require(decoded == 2, "SPaT and TLSM decoded from one extension response");
            auto missing = c.messages.front(); missing.type = 31;
            rejects([&] { validatePayload(c, missing, publicationData(out->x.publication).front()); }, "missing message kind rejected");
            auto mixed = c.messages; mixed.back().oid = "1.0.15784.1.0.1";
            rejects([&] { publicationBundle(c, mixed, 1, 1); }, "mixed OIDs require separate subscriptions");
            std::cout << "PASS signal provider roles, combined SPaT/TLSM decoding, message/OID rejection\n";
            return 0;
        }
        if (argc > 1 && std::string(argv[1]) == "--tim-regional") {
            require(DatexPayload_validate(31, (unsigned char *)fixtures::tim, sizeof(fixtures::tim)), "TIM without optional regional remains valid");
            require(!DatexPayload_checkTimProfile((unsigned char *)fixtures::tim, sizeof(fixtures::tim), 3), "regional test requires a decoded KOR extension");
            for (unsigned fault = 0; fault <= 4; ++fault) {
                auto input = DatexPayload_timRegionalFixture((unsigned char *)fixtures::tim, sizeof(fixtures::tim), fault);
                require(input != nullptr, "regional fixture outer encoding");
                bool valid = DatexPayload_validate(31, input->data, input->size) != 0;
                require(valid == (fault == 0 || fault == 4), "malformed nested open type rejected despite valid outer TIM");
                auto summary = DatexPayload_timRegionalSummary(input->data, input->size);
                require((summary != nullptr) == valid, "summary follows decoder result");
                if (summary) {
                    auto value = Json::parse(std::string((char *)summary->data, summary->size));
                    require(value.get("travelerInformationKor")->text == (fault == 0 ? "1" : "0"), "actual TravelerInformation-KOR decoding");
                    require(value.get("geographicalPathKor")->text == (fault == 0 ? "1" : "0"), "actual GeographicalPath-KOR decoding");
                    require(value.get("opaqueOtherRegions")->text == (fault == 0 ? "0" : "2"), "unknown region is not claimed decoded");
                    Dz1Binary_del(summary);
                }
                Dz1Binary_del(input);
            }
            const char *ids[] = {"vehicleServer2rse_v2", "vehicleClient2rse_v2", "rseClient2vehicle_v2", "rseServer2vehicle_v2"};
            unsigned total = 0;
            for (auto id : ids) {
                const auto &c = findCase(id);
                total += (unsigned)availableTests(c).size();
                for (const auto &m : c.messages) {
                    auto p = publication(c, m, 1, 1);
                    validatePayload(c, m, publicationData(p->x.publication).front());
                }
            }
            require(total == 48, "all F2F roles and message envelopes");
            std::cout << "PASS nested KOR decoding, malformed inner data, absent/other-region handling, four F2F message envelopes (48 items)\n";
            return 0;
        }
        if (argc > 1 && std::string(argv[1]) == "--remaining-contracts") {
            const auto &vehicle = findCase("vehicleClient2center_v2");
            require(std::string(messageCase(vehicle, vehicle.messages[0]).oid) == "1.0.14827.1.1.0", "vehicle SPaT envelope");
            require(std::string(messageCase(vehicle, vehicle.messages[1]).oid) == "1.0.15784.1.0.1", "vehicle RSA envelope");
            const auto &signal = findCase("signalserverServer2center_v2");
            for (auto m : signal.messages) {
                auto out = publication(signal, m, 1, 1);
                auto data = publicationData(out->x.publication).front()->type->x.msg->data;
                require(DatexSignalEnvelopeRegression(data->data, data->size, m.type) == 1, "ExtentionCommPDU AID=2, format=1 and actual MessageFrame");
                validatePayload(signal, m, publicationData(out->x.publication).front());
            }
            auto tls = DatexPayload_json(50, (unsigned char *)fixtures::tls, sizeof(fixtures::tls));
            require(tls != nullptr, "TLSM JSON root");
            auto json = Json::parse(std::string((char *)tls->data, tls->size));
            Dz1Binary_del(tls);
            require(json.get("trafficLightID")->text == "1234", "TLSM ID preserved");
            require(json.get("trafficLightStatus")->array.at(0).get("remainingTime")->text == "8", "TLSM KOR layout preserved");
            for (unsigned kind : {1u, 2u}) {
                auto tim = DatexPayload_timProfile((unsigned char *)fixtures::tim, sizeof(fixtures::tim), kind);
                require(tim != nullptr, "TIM directive fixture");
                require(DatexPayload_checkTimProfile(tim->data, tim->size, kind) == 1, "TIM mandatory directive fields");
                require(DatexPayload_checkTimProfile(tim->data, tim->size, 3-kind) == 0, "wrong directive ID rejected");
                auto encodedJson = DatexPayload_json(31, tim->data, tim->size);
                require(encodedJson != nullptr, "TIM directive JSON");
                auto parsed = Json::parse(std::string((char *)encodedJson->data, encodedJson->size));
                require(parsed.get("packetID")->text.size() == 18, "binary packet ID including NULs preserved as hex");
                Dz1Binary_del(encodedJson); Dz1Binary_del(tim);
            }
            require(!DatexPayload_checkTimProfile((unsigned char *)fixtures::tim, sizeof(fixtures::tim), 1), "generic TIM is not a speed directive");
            std::cout << "PASS remaining case/OID contracts, signal envelope, TLSM KOR JSON, TIM speed/lane core and negative profiles\n";
            return 0;
        }
        if (argc > 1 && std::string(argv[1]) == "--traffic-payload") {
            const auto &traffic = findCase("rseClient2center_v2");
            auto bundle = publicationBundle(traffic, traffic.messages, 1, 1);
            unsigned decoded = 0;
            Sink sink;
            sink.validation = [&](const auto &, const auto &, const auto &, const Bytes &json) {
                require(Json::parse(std::string(json.begin(), json.end())).kind == Json::Object, "payload JSON");
                ++decoded;
            };
            for (const auto &m : traffic.messages)
                validatePayload(traffic, m, publicationData(bundle->x.publication).front(), &sink, m.name);
            require(decoded == 3, "all three payloads in a single CommTxPDU list");
            auto wrongType = traffic.messages.front();
            wrongType.type = 20;
            auto invalidType = publication(traffic, wrongType, 1, 1);
            rejects([&] { validatePayload(traffic, traffic.messages.front(), publicationData(invalidType->x.publication).front()); }, "metadata mismatch must fail despite valid MAP bytes");
            auto wrongPsid = traffic.messages.front();
            wrongPsid.psid = 82055;
            auto invalidPsid = publication(traffic, wrongPsid, 1, 1);
            rejects([&] { validatePayload(traffic, traffic.messages.front(), publicationData(invalidPsid->x.publication).front()); }, "SPaT PSID cannot pass MAP validation");
            require(DatexTrafficConversionRegression((unsigned char *)fixtures::tim, unsigned(sizeof(fixtures::tim))) == 1, "ASN.1 to JSON model field preservation");
            std::cout << "PASS traffic payload bundle, PSID/type rejection, and ASN.1 field conversion regression\n";
            return 0;
        }
        if (argc > 1 && std::string(argv[1]) == "--adapter") {
            adapterTests();
            return 0;
        }
        if (argc > 1 && std::string(argv[1]) == "--stop") {
            stopTests();
            return 0;
        }
        std::cerr << "core tests start\n";
        auto &c = findCase("centerClient2rse_v2");
        const std::string config =
            R"({"my_domain":"test","peer_domain":"sut","user":"u","pass":"p","peer_ip":"127.0.0.1","peer_port":355,"test_session":true})";
        auto cfg = Config::parse(c, config);
        require(cfg.heartbeat == 60 && cfg.response == 40 && cfg.maintain == 300 && cfg.receive == 120,
                "defaults");
        rejects([&] { Config::parse(c, config.substr(0, config.size() - 1) + ",\"hb_dur\":0}"); },
                "zero rejected");
        rejects([&] { Json::parse("{\"a\":1,\"a\":2}"); }, "duplicate JSON key");
        rejects([&] { Json::parse("{}x"); }, "trailing JSON");
        for (auto &item : cases()) {
            auto ui = Json::parse(configureUI(item));
            require(ui.kind == Json::Object, "UI JSON");
        }
        auto now = std::chrono::steady_clock::now();
        PeriodTracker p(10);
        p.receive(now);
        p.receive(now + std::chrono::seconds(9));
        p.receive(now + std::chrono::seconds(20));
        require(p.sufficient(), "inclusive bounds");
        PeriodTracker late(10);
        late.receive(now);
        rejects([&] { late.receive(now + std::chrono::milliseconds(11001)); }, "late bound");
        PeriodTracker early(10);
        early.receive(now);
        rejects([&] { early.receive(now + std::chrono::milliseconds(8999)); }, "early bound");
        PeriodTracker phase(10, true);
        phase.receive(now);
        phase.receive(now + std::chrono::seconds(3));
        require(!phase.sufficient(), "partial initial cycle");
        phase.receive(now + std::chrono::seconds(13));
        require(phase.sufficient(), "steady cycle");
        PacketRecord a{7, {1}, {2}, {3}, now}, b = a;
        require(compareRetry(a, b).same(), "equal retry");
        b.number++;
        require(!compareRetry(a, b).same(), "number changed");
        b = a;
        b.timestamp = {9};
        require(!compareRetry(a, b).same(), "timestamp changed");
        b = a;
        b.content = {9};
        require(!compareRetry(a, b).same(), "content changed");
        std::cerr << "codec tests start\n";
        auto loginPdu = login(cfg, cfg.password);
        std::cerr << "login ready\n";
        auto original = packet(cfg, std::move(loginPdu), 42);
        std::cerr << "packet ready\n";
        auto wire = encode(original.get());
        require(frameSize(wire) == wire.size(), "BER frame boundary");
        for (size_t i = 1; i < wire.size(); ++i) {
            Bytes part(wire.begin(), wire.begin() + i);
            require(frameSize(part) == 0, "TCP fragmentation");
        }
        std::cerr << "decode tests start\n";
        auto received = decode(wire);
        require(received->pktNbr == 42, "codec roundtrip");
        require(octetText(received->pdu->x.login->pass) == "p", "credentials roundtrip");
        std::cerr << "record tests start\n";
        auto r1 = record(original.get(), wire, now), r2 = record(received.get(), wire, now);
        require(compareRetry(r1, r2).same(), "wire retry comparison");
        received->pdu->x.login->timeout++;
        auto changed = encode(received.get());
        require(!compareRetry(r1, record(received.get(), changed, now)).same(), "Login content mutation");
        std::cerr << "sample tests start\n";
        auto &mapCase = findCase("centerServer2rse_v2");
        auto pub = publication(mapCase, mapCase.messages[0], 1, 1);
        validatePayload(mapCase, mapCase.messages[0], publicationData(pub->x.publication).front());
        auto bsm = publication(c, c.messages[0], 1, 1);
        validatePayload(c, c.messages[0], publicationData(bsm->x.publication).front());
        for (auto &item : cases())
            for (auto m : item.messages) {
                auto msg = publication(item, m, 1, 1);
                validatePayload(item, m, publicationData(msg->x.publication).front());
            }
        loopbackTests();
        adapterTests();
        stopTests();
        std::cout
            << "PASS configuration, UI, timing boundaries, retry mutations, BER framing, BSM/MAP samples\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << "\n";
        return 1;
    }
}
