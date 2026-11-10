#pragma once
#include "UticProvider.h"
#include "VdsRequester.h"
#include "SmartTraffic.h"
#include "NticTraffic.h"
#include "ShadowTraffic.h"
#include "WeatherTraffic.h"
namespace rest {
struct MethodItem { std::string key,title; unsigned expected; std::string check; bool standardRequired=false; };
struct MethodConfig {
    std::string scenario,credential,baseUrl,fixture;
    std::string nticPath=NticPath;
    HttpFields shadowParams;
    WeatherOptions weatherOptions;
    std::string evidenceDirectory;
    unsigned evidenceWaitSeconds=30;
    bool provider=false,xml=false,smart=false,ntic=false,shadow=false,weather=false,dataAbsentConfirmed=false;
    unsigned repetitions=10,timeout=30,connectTimeout=5,badRequest=400,unauthorized=401,noData=200,noDataError=404;
    unsigned missingPathStatus=404,serverErrorStatus=500;
    Config server;
    std::vector<MethodItem> items;
    static MethodConfig parse(const std::string &,const std::string &);
};
std::vector<MethodItem> methodItems(const std::string &);
std::string methodBasis(const MethodConfig &,const MethodItem &);
std::string unobservedScope(const MethodConfig &,const MethodItem &);
std::string methodUI(const std::string &);
std::string effectiveConfiguration(const MethodConfig &,const std::string &);
void saveAcceptedConfiguration(const MethodConfig &,const std::string &,unsigned index);
void invalidateAcceptedConfiguration(const std::string &);
Result runMethod(const MethodConfig &,std::atomic<bool> &,const Sink &);
}
