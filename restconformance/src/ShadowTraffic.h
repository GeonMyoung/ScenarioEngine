#pragma once
#include "HttpClientAdapter.h"
namespace rest {
inline constexpr const char *ShadowProviderCase="centerClient2micro_shadow_v1";
inline constexpr const char *ShadowRequestCase="microServer2center_shadow_v1";
inline constexpr const char *ShadowPath="/data";
inline bool shadowCase(const std::string &s){return s==ShadowProviderCase||s==ShadowRequestCase;}
std::string shadowFixture();
std::string shadowErrorBody();
HttpFields shadowQuery(const Json &);
std::string shadowQueryJson(const HttpFields &);
size_t validateShadowResponse(const HttpResponse &);
void validateShadowError(const HttpResponse &);
std::string validateShadowRequest(const HttpRequest &,const HttpFields &);
}
