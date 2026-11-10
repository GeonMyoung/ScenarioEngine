#pragma once
#include "HttpClientAdapter.h"
namespace rest {
inline constexpr const char *NticProviderCase="centerClient2ntic_v1";
inline constexpr const char *NticRequestCase="nticServer2center_v1";
inline constexpr const char *NticPath="/vdsInfo";
inline bool nticCase(const std::string &s){return s==NticProviderCase||s==NticRequestCase;}
std::string nticFixture(bool empty=false);
std::string nticErrorBody(const std::string &code);
std::string nticResultCode(const std::string &test);
size_t validateNticResponse(const HttpResponse &);
void validateNticError(const HttpResponse &,const std::string &expected);
std::string validateNticRequest(const HttpRequest &,const std::string &credential,const std::string &path);
}
