#pragma once
#include "RestCore.h"
#include <memory>
namespace rest {
// Transport is independent of UTIC field validation and SDK platform notifications.
class HttpAdapter {
    struct Impl;
    std::unique_ptr<Impl> impl;
public:
    explicit HttpAdapter(const Config &, bool captureAuthorization=false);
    ~HttpAdapter();
    HttpAdapter(const HttpAdapter &) = delete;
    void start();
    HttpRequest receive(std::atomic<bool> &, unsigned timeoutSeconds);
    void respond(const HttpRequest &, unsigned status, const std::string &body,
                 const std::string &contentType, const std::string &runId, unsigned exchange,
                 std::atomic<bool> &, unsigned timeoutSeconds);
};
}
