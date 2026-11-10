#pragma once
#include "RestMethod.h"
#include <fstream>
namespace rest {
std::string userCaseDefinition(const MethodConfig &,const MethodItem &);
std::string userSetupSummary(const MethodConfig &);
std::string userError(const std::string &reason);
std::string userRunSummary(const MethodConfig &,const Result &);
class RestUserLog {
    const MethodConfig &config;
    const Sink &sink;
    std::ofstream record;
    void write(const std::string &test,const std::string &stage,const std::string &message,const std::string &data="");
    std::string sample(const std::string &body) const;
public:
    RestUserLog(const MethodConfig &,const Sink &,const std::string &directory);
    void begin();
    void listening();
    void item(const MethodItem &,unsigned index);
    void request(const MethodItem &,unsigned iteration,const std::string &path);
    void message(const MethodItem &,unsigned iteration,const std::string &direction,const std::string &summary,const std::string &data);
    void exchange(const MethodItem &,unsigned iteration,unsigned status,const std::string &media,size_t bytes,size_t count,const std::string &body);
    void result(const MethodItem &,const std::string &verdict,unsigned completed,const std::string &reason,unsigned attempted,unsigned actualStatus,const std::string &data="");
};
}
