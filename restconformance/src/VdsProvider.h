#pragma once
#include "RestCore.h"
#include "HttpClientAdapter.h"
namespace rest {
inline constexpr const char *VdsCase = "microClient2center_v1";
inline constexpr const char *VdsPath = "/v1/adxc/vds-l-raws";
struct VdsConfig {
    std::string baseUrl, bearerToken;
    unsigned repetitions=10, connectTimeout=5, requestTimeout=30;
    static VdsConfig parse(const std::string &);
};
using VdsResponse=HttpResponse;
std::string configureVdsUI();
size_t validateVdsResponse(const VdsResponse &);
VdsResponse getVds(const VdsConfig &, std::atomic<bool> &, const std::string &, unsigned);
Result runVds(const VdsConfig &, std::atomic<bool> &, const Sink &);
}
