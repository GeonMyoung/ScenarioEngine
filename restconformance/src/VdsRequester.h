#pragma once
#include "VdsProvider.h"
namespace rest {
inline constexpr const char *VdsRequestCase="centerServer2micro_v1";
struct VdsRequestConfig {
    Config server;
    std::string bearerToken;
    static VdsRequestConfig parse(const std::string &);
};
std::string defaultVdsFixture();
std::string configureVdsRequestUI();
std::string validateVdsRequest(const VdsRequestConfig &, const HttpRequest &);
Result runVdsRequest(const VdsRequestConfig &, std::atomic<bool> &, const Sink &);
}
