#pragma once
#include <atomic>
#include <chrono>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdint>

namespace rest {
struct Failure : std::runtime_error { using std::runtime_error::runtime_error; };
struct Stopped : Failure { Stopped() : Failure("시험이 중지되었습니다.") {} };
struct Json {
    enum Kind { Null, Bool, Number, String, Object, Array } kind = Null;
    bool boolean = false;
    std::string text;
    std::map<std::string, Json> object;
    std::vector<Json> array;
    static Json parse(const std::string &, size_t maxBytes=65536);
    const Json *get(const std::string &) const;
};
std::string quote(const std::string &);
std::string sha256(const std::string &);
std::string readTextFile(const std::string &);
std::string defaultFixture();
struct Incident { std::map<std::string,std::string> fields; };
std::vector<Incident> parseUticXml(const std::string &xml, bool allowEmpty=false);
struct Config {
    std::string bindIp = "127.0.0.1", apiKey, fixturePath;
    unsigned port = 55307, repetitions = 10, requestTimeout = 30;
    static Config parse(const std::string &);
};
std::string configureUI();
struct HttpRequest {
    unsigned session = 0;
    std::string method, path;
    std::string body; // Complete received request body, including invalid GET bodies.
    std::vector<std::pair<std::string,std::string>> query;
    size_t bodyBytes = 0;
    bool bodyDeclared = false;
    std::vector<std::string> authorization; // In-memory only, never serialize token values.
};
struct Sink {
    std::function<void(const std::string &,const std::string &,const std::string &,const std::string &)> itemData;
    std::function<void(const std::string &)> diagnostic; // Local tools only; never forwarded as a user message.
    std::function<void(const std::string &,const std::string &)> itemInfo;
    std::function<void(const std::string &,const std::string &)> state;
    std::function<void(const std::string &)> info;
};
struct Result { std::string verdict, detail, runId, reportPath; unsigned exchanges = 0; };
std::string validateRequest(const Config &, const HttpRequest &);
Result run(const Config &, std::atomic<bool> &, const Sink &);
}
