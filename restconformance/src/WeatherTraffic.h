#pragma once
#include "HttpClientAdapter.h"
namespace rest {
inline constexpr const char *WeatherProviderCase="centerClient2weather_v1";
inline constexpr const char *WeatherRequestCase="weatherServer2center_v1";
inline constexpr const char *WeatherPath="/1360000/VilageFcstInfoService_2.0/getUltraSrtNcst";
inline bool weatherCase(const std::string &s){return s==WeatherProviderCase||s==WeatherRequestCase;}
struct WeatherOptions {std::string path=WeatherPath,keyName="serviceKey";HttpFields query;};
WeatherOptions weatherOptions(const Json &);
std::string weatherFixture(const WeatherOptions &,bool empty=false);
std::string weatherResultCode(const std::string &test);
std::string weatherErrorBody(const std::string &code);
HttpFields weatherQuery(const WeatherOptions &,const std::string &credential,const std::string &test);
std::string weatherPublicQuery(const HttpFields &);
size_t validateWeatherResponse(const HttpResponse &);
void validateWeatherPage(const HttpResponse &,const WeatherOptions &);
void validateWeatherError(const HttpResponse &,const std::string &expected);
std::string validateWeatherRequest(const HttpRequest &,const WeatherOptions &,const std::string &credential);
}
