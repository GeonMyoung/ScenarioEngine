#pragma once
#include "RestMethod.h"
namespace rest {
class RestEvidence {
    const MethodConfig &config;
    std::function<void(unsigned,const std::string &,const std::string &,const std::string &)> emit;
    unsigned requests=0,responses=0,messageNumber=0;
    void message(unsigned,const std::string &,const std::string &,const std::string &);
public:
    RestEvidence(const MethodConfig &c,decltype(emit) send):config(c),emit(std::move(send)){}
    void request(unsigned,const std::string &method,const std::string &path,const HttpFields &query,bool credentialPresent,size_t bodyBytes,bool declared=false,const std::string &body="");
    void response(unsigned,unsigned status,const std::string &media,const std::string &body);
    std::string finish(const std::string &verdict,unsigned completed) const;
    std::string json(const std::string &verdict,unsigned completed) const;
};
}
