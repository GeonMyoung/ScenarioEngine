#pragma once
#include "RestCore.h"
namespace rest {
struct HttpResponse { unsigned status=0; std::string contentType,body; };
using HttpFields=std::vector<std::pair<std::string,std::string>>;
HttpResponse httpGet(const std::string &url,unsigned connectTimeout,unsigned requestTimeout,
                     std::atomic<bool> &stop,const HttpFields &headers,const HttpFields &query,bool xml);
}
