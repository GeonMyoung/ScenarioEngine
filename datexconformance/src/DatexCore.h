#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace datex {
using Bytes = std::vector<unsigned char>;
using Tick = std::chrono::steady_clock::time_point;
struct Failure : std::runtime_error {
    using std::runtime_error::runtime_error;
};
inline std::uint32_t codecSize(std::size_t size) {
    if (size > UINT32_MAX)
        throw Failure("메시지 길이가 코덱의 허용 범위를 초과했습니다.");
    return static_cast<std::uint32_t>(size);
}
struct Stopped : Failure {
    Stopped() : Failure("시험이 중지되었습니다.") {}
};
enum class Role { Client, Server };
struct Message {
    const char *name;
    unsigned psid;
    unsigned type;
    const char *oid = nullptr;
    unsigned businessProfile = 0;
};
struct Case {
    const char *id;
    const char *title;
    Role role;
    const char *oid;
    std::vector<Message> messages;
    const char *targetLabel = nullptr;
};
Case messageCase(const Case &, const Message &);
Case subscriptionCase(const Case &, const std::string &oid);
const std::vector<Case> &cases();
const Case &findCase(const std::string &id);

/* Small strict JSON value used only for this module's configuration/evidence.
   Duplicate keys, fractional integer inputs and trailing data are rejected. */
struct Json {
    enum Kind { Null, Bool, Number, String, Object, Array } kind = Null;
    bool boolean = false;
    std::string text;
    std::map<std::string, Json> object;
    std::vector<Json> array;
    static Json parse(const std::string &source);
    static Json parseData(const std::string &source);
    const Json *get(const std::string &key) const;
};
std::string quote(const std::string &value);
struct Config {
    std::string host, myDomain, peerDomain, user, password, invalidPassword;
    bool useInitiate = false;
    unsigned port = 0, heartbeat = 60, response = 40, maintain = 300;
    unsigned receive = 120, period = 15, connectTimeout = 40;
    std::set<std::string> tests;
    bool tcpConnects(const Case &c) const { return (c.role == Role::Client) != useInitiate; }
    static Config parse(const Case &, const std::string &json);
};
std::string configureUI(const Case &c);
std::string testTitle(const Case &, const std::string &);
std::vector<std::string> availableTests(const Case &c);

struct PacketRecord {
    std::uint32_t number = 0;
    Bytes timestamp, content, wire;
    Tick received;
    bool hasTimestamp = true;
    std::uint64_t sessionId = 0;
    bool retransmitted = false;
    bool sendCompleted = true;
    size_t sentBytes = 0;
};
struct RetryComparison {
    bool number = false, timestamp = false, content = false;
    bool same() const {
        return number && timestamp && content;
    }
    std::string json() const;
};
RetryComparison compareRetry(const PacketRecord &, const PacketRecord &);
struct RetryTiming {
    std::int64_t elapsedUs = 0, expectedUs = 0, earlyAllowanceUs = 0, lateAllowanceUs = 2000000;
    bool within() const { return elapsedUs >= expectedUs - earlyAllowanceUs && elapsedUs <= expectedUs + lateAllowanceUs; }
    std::string json() const;
};
RetryTiming compareRetryTiming(const PacketRecord &, const PacketRecord &, unsigned responseSeconds);

class PeriodTracker {
    unsigned period_;
    bool initialShort_;
    Tick last_{};
    unsigned count_ = 0, intervals_ = 0;

  public:
    explicit PeriodTracker(unsigned period, bool initialShort = false);
    void receive(Tick now, bool retransmission = false);
    bool overdue(Tick now) const;
    bool sufficient() const {
        return count_ >= 2 && intervals_ >= 1;
    }
    unsigned count() const {
        return count_;
    }
};

enum class Verdict { Pass, Fail, Error, Stopped };
struct Result {
    std::string test;
    Verdict verdict;
    std::string detail;
    std::string userDetail;
    std::string observationsJson;
};
const char *verdictName(Verdict v);
struct Sink {
    // Human-readable progress is separate from internal diagnostic info.
    std::function<void(const std::string &, const std::string &, const std::string &)> userInfo;
    std::function<void(const std::string &, const std::string &)> state;
    std::function<void(const std::string &, const std::string &)> info;
    std::function<void(const Result &)> result;
    std::function<void(const std::string &, const std::string &, const Bytes &, const Bytes &)> validation;
    std::function<void(const std::string &, bool, const PacketRecord &, int, const Bytes &, bool)> packet;
    // Finalize one item's verdict before notifying its result and starting the next item.
    std::function<void(Result &)> finalize;
};
/* Implemented by the codec/transport layer; all mutable state belongs to a run. */
std::vector<Result> run(const Case &, const Config &, std::atomic<bool> &stop, const Sink &);
} // namespace datex
