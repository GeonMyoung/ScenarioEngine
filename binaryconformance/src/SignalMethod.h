#pragma once
#include "SignalCodec.h"
namespace signalbinary {
inline constexpr const char *ReceiverCase="signalServer2center_binary_v1";
inline constexpr const char *ProviderCase="centerClient2signal_binary_v1";
struct CaseDef {const char *id;unsigned message;bool provider;const char *source;const char *destination;};
const CaseDef *definition(const std::string &);
struct Item {std::string key,title,mode;unsigned message;bool core=false;};
struct Config {
    std::string scenario,ip="127.0.0.1",raw;
    bool provider=false;unsigned message=0;std::string source,destination;Profile profile;
    unsigned period=1000,periodTolerance=200;
    unsigned port=55414,repetitions=10,timeout=5000,initialLimit=1000,firstSequence=0,heartbeatPeriod=60000,heartbeatTolerance=1000,heartbeatSamples=2,changeDelay=1000,writeChunk=0;
    std::vector<Item> selected;
    static Config parse(const std::string &,const std::string &);
};
struct Result {std::string verdict="FAIL",detail,path,runId;unsigned exchanges=0,messages=0;};
std::vector<Item> items(bool provider);
std::vector<Item> items(const std::string &scenario);
std::string configureUI(const std::string &);
std::string effectiveConfiguration(const Config &);
void saveAcceptedConfiguration(const Config &,unsigned);
void invalidateAcceptedConfiguration(const std::string &);
Result run(const Config &,std::atomic<bool> &,const rest::Sink &);
}
