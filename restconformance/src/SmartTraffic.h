#pragma once
#include "HttpClientAdapter.h"
namespace rest {
inline constexpr const char *SmartProviderCase="microClient2center_smart_v1";
inline constexpr const char *SmartRequestCase="centerServer2micro_smart_v1";
inline constexpr const char *SmartPath="/v1/adxc/smt-l-raws";
inline bool smartCase(const std::string &s){return s==SmartProviderCase||s==SmartRequestCase;}
std::string defaultSmartFixture();
size_t validateSmartResponse(const HttpResponse &);
}
