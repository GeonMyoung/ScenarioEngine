#pragma once
#include "HttpClientAdapter.h"
namespace rest {
inline constexpr const char *UticProviderCase="centerClient2utic_v1";
inline constexpr const char *UticPath="/guide/imsOpenData.do";
struct UticProviderConfig {
    std::string baseUrl,apiKey;
    unsigned repetitions=10,connectTimeout=5,requestTimeout=30;
    static UticProviderConfig parse(const std::string &);
};
std::string configureUticProviderUI();
size_t validateUticResponse(const HttpResponse &);
Result runUticProvider(const UticProviderConfig &,std::atomic<bool> &,const Sink &);
}
