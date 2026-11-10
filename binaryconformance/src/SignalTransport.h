#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include "SignalCodec.h"
namespace signalbinary {
using Clock=std::chrono::steady_clock;
struct IoFailure:rest::Failure {Bytes partial;bool sending;IoFailure(const std::string &message,Bytes b,bool s):rest::Failure(message),partial(std::move(b)),sending(s){}};
struct IoStopped:rest::Stopped {Bytes partial;bool sending;IoStopped(Bytes b,bool s):partial(std::move(b)),sending(s){}};
struct SocketRuntime {SocketRuntime();~SocketRuntime();};
class Channel {
    SOCKET socket_=INVALID_SOCKET;
    void wait(short events,Clock::time_point until,std::atomic<bool> &) const;
public:
    Channel()=default;explicit Channel(SOCKET s):socket_(s){}
    Channel(const Channel &)=delete;Channel &operator=(const Channel &)=delete;
    Channel(Channel &&other) noexcept:socket_(other.socket_){other.socket_=INVALID_SOCKET;}
    Channel &operator=(Channel &&other) noexcept {close();socket_=other.socket_;other.socket_=INVALID_SOCKET;return *this;}
    ~Channel(){close();}
    void close();void shutdown();
    static Channel connect(const std::string &,unsigned port,unsigned timeoutMs,std::atomic<bool> &);
    static Channel listen(const std::string &,unsigned port);
    Channel accept(unsigned timeoutMs,std::atomic<bool> &);
    void send(const Bytes &,unsigned timeoutMs,std::atomic<bool> &,unsigned chunkBytes=0);
    Bytes receive(unsigned timeoutMs,std::atomic<bool> &);
    bool readable(unsigned timeoutMs,std::atomic<bool> &);
};
void pauseUntil(Clock::time_point,std::atomic<bool> &);
}
