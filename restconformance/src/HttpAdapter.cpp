#include "HttpAdapter.h"
#include <GitsnOpenApi.h>
#include "GitsnOpenApiMsg.h"
#include <condition_variable>
#include <deque>
#include <mutex>
#include <algorithm>

namespace rest {
namespace {
void require(Dz1Error e, const char *what) {
    if (e.code) throw Failure(std::string(what) + " (" + std::to_string(e.code) + ")");
}
}
struct HttpAdapter::Impl {
    Config config;
    bool captureAuthorization;
    void *task = nullptr;
    std::mutex lock;
    std::condition_variable changed;
    std::deque<HttpRequest> requests;
    std::map<unsigned,unsigned> sent;
    std::string error;
    explicit Impl(const Config &c,bool capture) : config(c),captureAuthorization(capture) {}
    static void received(void *ptr, GitsnOpenApiMsg **message) {
        auto &self = *static_cast<Impl *>(ptr);
        try {
            if (!message || !*message || !(*message)->ctx ||
                (*message)->ctx->present != GitsnOpenApiHttpMsgPresent_req) return;
            auto q = (*message)->ctx->x.req;
            if (!q) throw Failure("HTTP 요청 정보가 없습니다.");
            HttpRequest r;
            r.session = (*message)->session_id;
            r.method = q->method == GitsnOpenApiHttpReqMethod_GET ? "GET" :
                       q->method == GitsnOpenApiHttpReqMethod_POST ? "POST" : "UNKNOWN";
            r.path = q->target_utf8 ? q->target_utf8 : "";
            r.bodyBytes = q->body ? q->body->size : 0;
            if(r.bodyBytes)r.body.assign(reinterpret_cast<const char *>(q->body->data),r.bodyBytes);
            if (q->args && q->args->storage) {
                unsigned count = 0;
                Dz1Error e = {};
                auto entries = q->args->storage->get_array(q->args->storage, &count, &e);
                require(e, "HTTP query 읽기 실패");
                if (count > 64) { if (entries) Dz1Free(entries); throw Failure("HTTP query 항목 수 초과"); }
                for (unsigned i = 0; i < count; ++i)
                    r.query.emplace_back(entries[i]->key_utf8 ? entries[i]->key_utf8 : "",
                                         entries[i]->value_utf8 ? entries[i]->value_utf8 : "");
                if (entries) Dz1Free(entries);
            }
            if (self.captureAuthorization && q->header && q->header->storage) {
                unsigned count=0; Dz1Error e={};
                auto entries=q->header->storage->get_array(q->header->storage,&count,&e);
                require(e,"HTTP header read failed");
                for(unsigned i=0;i<count;++i){
                    std::string key=entries[i]->key_utf8?entries[i]->key_utf8:"";
                    std::transform(key.begin(),key.end(),key.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
                    if(key=="authorization")r.authorization.emplace_back(entries[i]->value_utf8?entries[i]->value_utf8:"");
                    if(key=="transfer-encoding")r.bodyDeclared=true;
                    if(key=="content-length"){
                        std::string value=entries[i]->value_utf8?entries[i]->value_utf8:"";
                        if(value.empty()||value.find_first_not_of('0')!=std::string::npos)r.bodyDeclared=true;
                    }
                }
                if(entries)Dz1Free(entries);
            }
            std::lock_guard<std::mutex> guard(self.lock);
            if (self.requests.size() >= 64) throw Failure("대기 중 HTTP 요청 수 초과");
            self.requests.push_back(std::move(r));
            self.changed.notify_all();
        } catch (const std::exception &e) {
            std::lock_guard<std::mutex> guard(self.lock);
            self.error = e.what();
            self.changed.notify_all();
        }
    }
    static void connection(void *ptr, GitsnOpenApiConnectionEvent *event) {
        if (!event) return;
        auto &self = *static_cast<Impl *>(ptr);
        std::lock_guard<std::mutex> guard(self.lock);
        if (event->event_type == GitsnOpenApiConnectionEventType_response_sent)
            ++self.sent[event->session_id];
        self.changed.notify_all();
    }
    static void exception(void *ptr, Dz1Error *e) {
        auto &self = *static_cast<Impl *>(ptr);
        std::lock_guard<std::mutex> guard(self.lock);
        self.error = "HTTP 어댑터 오류 (" + std::to_string(e ? e->code : -1) + ")";
        self.changed.notify_all();
    }
};
HttpAdapter::HttpAdapter(const Config &c,bool capture) : impl(new Impl(c,capture)) {}
HttpAdapter::~HttpAdapter() {
    if (impl->task) GitsnOpenApi_del(impl->task);
}
void HttpAdapter::start() {
    Dz1Error e = {};
    Dz1SockAddr address = {};
    require(Dz1SockAddr_setAddrStr(&address, const_cast<char *>(impl->config.bindIp.c_str())), "수신 주소 오류");
    require(Dz1SockAddr_setPort(&address, static_cast<unsigned short>(impl->config.port)), "수신 포트 오류");
    GitsnOpenApiServerOptions options = {};
    options.server_idle_timeout_ms = impl->config.requestTimeout * 1000;
    options.advertise_keep_alive = FALSE;
    options.connection_cb = Impl::connection;
    options.connection_cb_arg = impl.get();
    impl->task = GitsnOpenApi_newWithOptions(&address, const_cast<char *>(impl->captureAuthorization?"UT center VDS conformance server":"UTIC conformance server"),
        Impl::received, impl.get(), Impl::exception, impl.get(), &options, &e);
    require(e, "HTTP 서버 생성 실패");
    if (!impl->task) throw Failure("HTTP 서버 생성 실패");
    require(Dz1Task_start(impl->task, 0), "HTTP 수신 대기 시작 실패");
}
HttpRequest HttpAdapter::receive(std::atomic<bool> &stop, unsigned timeoutSeconds) {
    auto until = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds);
    std::unique_lock<std::mutex> guard(impl->lock);
    for (;;) {
        if (stop) throw Stopped();
        if (!impl->error.empty()) throw Failure(impl->error);
        if (!impl->requests.empty()) {
            auto r = std::move(impl->requests.front());
            impl->requests.pop_front();
            return r;
        }
        if (std::chrono::steady_clock::now() >= until) throw Failure(impl->captureAuthorization?"미시교통정보 플랫폼 정보요청 대기 시간 초과":"UT 센터 정보요청 대기 시간 초과");
        impl->changed.wait_for(guard, std::chrono::milliseconds(50));
    }
}
void HttpAdapter::respond(const HttpRequest &request, unsigned status, const std::string &body,
                           const std::string &contentType, const std::string &runId, unsigned exchange,
                           std::atomic<bool> &stop, unsigned timeoutSeconds) {
    Dz1Error e = {};
    auto response = GitsnOpenApiHttpRsp_new(const_cast<char *>("HTTP"),1,1,status,
        const_cast<char *>(status==200?"OK":status==204?"No Content":status==401?"Unauthorized":status==403?"Forbidden":status==404?"Not Found":status==422?"Unprocessable Entity":status==500?"Internal Server Error":"Bad Request"),nullptr,nullptr,&e);
    if (!response) throw Failure("HTTP 응답 생성 실패");
    GitsnOpenApiMsg *queued = nullptr;
    GitsnOpenApiHttpMsg *context = nullptr;
    try {
        require(e, "HTTP 응답 생성 실패");
        if (!response->header) response->header = GitsnOpenApiDatas_new(&e);
        require(e, "HTTP header 생성 실패");
        if (!GitsnOpenApiDatas_appendEntryStrU(response->header, const_cast<char *>("Content-Type"),
                                              const_cast<char *>(contentType.c_str()), &e)) require(e, "Content-Type 생성 실패");
        auto number = std::to_string(exchange);
        GitsnOpenApiDatas_appendEntryStrU(response->header, const_cast<char *>("X-Scenario-Run"), const_cast<char *>(runId.c_str()), &e);
        require(e, "증적 header 생성 실패");
        GitsnOpenApiDatas_appendEntryStrU(response->header, const_cast<char *>("X-Scenario-Exchange"), const_cast<char *>(number.c_str()), &e);
        require(e, "증적 header 생성 실패");
        if (!response->body) response->body = _Dz1ElasticBuf_new(4096, FALSE, &e, const_cast<char *>(__FILE__), __LINE__);
        require(e, "HTTP body 생성 실패");
        if (!Dz1ElasticBuf_pushStrA(response->body, const_cast<char *>(body.c_str()), &e)) require(e, "HTTP body 생성 실패");
        context = GitsnOpenApiHttpMsg_new(GitsnOpenApiHttpMsgPresent_rsp,response,&e);
        require(e, "HTTP 응답 문맥 생성 실패");
        if (!context) throw Failure("HTTP 응답 문맥 생성 실패");
        response = nullptr;
        queued = GitsnOpenApiMsg_new(request.session,context,&e);
        require(e, "HTTP 응답 메시지 생성 실패");
        if (!queued) throw Failure("HTTP 응답 메시지 생성 실패");
        context = nullptr;
        unsigned expected;
        { std::lock_guard<std::mutex> guard(impl->lock); expected = impl->sent[request.session] + 1; }
        // Transfer an owned message; wait for response_sent instead of a blocking
        // peer-EOF call, so STOP remains responsive even when the peer stays open.
        auto posted = Dz1Task_post(impl->task, DZ1_TASK_QUEUE_NONE, GITSN_OPEN_API_DO_RESPONSE_ASYNC,
            (void **)&queued, (Dz1DelFunc)GitsnOpenApiMsg_del, nullptr, nullptr, nullptr, nullptr);
        require(posted, "HTTP 응답 전달 실패");
        queued = nullptr;
        auto until = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds);
        std::unique_lock<std::mutex> guard(impl->lock);
        while (impl->sent[request.session] < expected) {
            if (stop) throw Stopped();
            if (!impl->error.empty()) throw Failure(impl->error);
            if (std::chrono::steady_clock::now() >= until) throw Failure("HTTP 응답 전송 완료 대기 시간 초과");
            impl->changed.wait_for(guard, std::chrono::milliseconds(50));
        }
    } catch (...) {
        if (queued) GitsnOpenApiMsg_del(queued);
        if (context) GitsnOpenApiHttpMsg_del(context);
        GitsnOpenApiHttpRsp_del(response);
        throw;
    }
    GitsnOpenApiHttpRsp_del(response);
}
}
