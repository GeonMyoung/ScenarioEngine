#include "VdsProvider.h"
#include <GitsnOpenApi.h>
#include <curl/curl.h>
#include <memory>
#include <mutex>

namespace rest {
namespace {
int progress(void *context,curl_off_t,curl_off_t received,curl_off_t,curl_off_t) {
    return *static_cast<std::atomic<bool> *>(context) || received>1024*1024;
}
void require(bool ok,const char *message) { if(!ok)throw Failure(message); }
}
HttpResponse httpGet(const std::string &url,unsigned connectTimeout,unsigned requestTimeout,std::atomic<bool> &stop,const HttpFields &headerFields,const HttpFields &queryFields,bool xml) {
    static std::once_flag initialized;
    std::call_once(initialized,[]{Dz1Error e={}; if(!GitsnOpenApiReqSys_init(&e)&&e.code!=EEXIST)throw Failure("HTTP 클라이언트 초기화 실패");});
    if(stop)throw Stopped();
    Dz1Error e={};
    std::unique_ptr<GitsnOpenApiReq,decltype(&GitsnOpenApiReq_del)> request(
        GitsnOpenApiReq_newWithTimeouts(connectTimeout,requestTimeout,&e),GitsnOpenApiReq_del);
    require(request.get()!=nullptr,"HTTP 요청 핸들 생성 실패");
    auto curl=static_cast<CURL *>(request.get());
    require(curl_easy_setopt(curl,CURLOPT_XFERINFOFUNCTION,progress)==CURLE_OK,"HTTP 중지 설정 실패");
    require(curl_easy_setopt(curl,CURLOPT_XFERINFODATA,&stop)==CURLE_OK,"HTTP 중지 설정 실패");
    require(curl_easy_setopt(curl,CURLOPT_NOPROGRESS,0L)==CURLE_OK,"HTTP 중지 설정 실패");
    require(curl_easy_setopt(curl,CURLOPT_MAXFILESIZE_LARGE,static_cast<curl_off_t>(1024*1024))==CURLE_OK,"HTTP 크기 설정 실패");
    require(curl_easy_setopt(curl,CURLOPT_PROTOCOLS_STR,"http,https")==CURLE_OK,"HTTP 프로토콜 설정 실패");
    require(curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,0L)==CURLE_OK,"HTTP 리다이렉트 설정 실패");
    if(url.rfind("https://",0)==0)
        require(GitsnOpenApiReq_enableNativeCaStore(request.get(),&e)!=FALSE,"HTTPS 인증서 저장소 설정 실패");
    std::vector<GitsnOpenApiDataEntry> headers,queryEntries;
    for(const auto &h:headerFields)headers.push_back({const_cast<char *>(h.first.c_str()),const_cast<char *>(h.second.c_str())});
    headers.push_back({nullptr,nullptr});
    for(const auto &q:queryFields)queryEntries.push_back({const_cast<char *>(q.first.c_str()),const_cast<char *>(q.second.c_str())});
    std::vector<GitsnOpenApiDataEntry *> query;
    for(auto &q:queryEntries)query.push_back(&q);
    query.push_back(nullptr);
    std::unique_ptr<GitsnOpenApiResult,decltype(&GitsnOpenApiResult_del)> response(
        (xml?GitsnOpenApiReq_getXml:GitsnOpenApiReq_getJson)(request.get(),const_cast<char *>(url.c_str()),headers.data(),query.data(),&e),GitsnOpenApiResult_del);
    if(stop)throw Stopped();
    if(e.code||!response)throw Failure("HTTP 응답 수신 실패 (연결·시간 제한·전송 상태 확인, 코드 "+std::to_string(e.code)+")");
    HttpResponse r;r.status=static_cast<unsigned>(response->code);
    r.contentType=response->content_type?response->content_type:"";
    if(response->data){
        auto length=Dz1ElasticBuf_getDataSize(response->data,&e);
        require(!e.code&&length>=0,"HTTP 본문 크기 읽기 실패");
        if(length){
            const auto bytes=Dz1ElasticBuf_flatten(response->data,&e);
            require(!e.code&&bytes!=nullptr,"HTTP 본문 읽기 실패");
            r.body.assign(reinterpret_cast<char *>(bytes->data),bytes->size);
        }
    }
    return r;
}
VdsResponse getVds(const VdsConfig &c,std::atomic<bool> &stop,const std::string &runId,unsigned n){
    return httpGet(c.baseUrl+VdsPath,c.connectTimeout,c.requestTimeout,stop,
                   {{"Authorization","Bearer "+c.bearerToken},{"X-Test-Run-Id",runId},{"X-Test-Exchange",std::to_string(n)}},{},false);
}
}
