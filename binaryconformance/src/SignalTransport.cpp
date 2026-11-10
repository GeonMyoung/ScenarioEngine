#include "SignalTransport.h"
#include <algorithm>
#include <thread>
#pragma comment(lib,"Ws2_32.lib")

namespace signalbinary { namespace {
sockaddr_in address(const std::string &ip,unsigned port){sockaddr_in a={};a.sin_family=AF_INET;a.sin_port=htons(static_cast<u_short>(port));if(!port||port>65535||InetPtonA(AF_INET,ip.c_str(),&a.sin_addr)!=1)throw rest::Failure("TCP IPv4 주소 또는 포트 입력 오류");return a;}
void nonblocking(SOCKET s){u_long yes=1;if(ioctlsocket(s,FIONBIO,&yes))throw rest::Failure("TCP 소켓 준비 실패");int n=1;setsockopt(s,IPPROTO_TCP,TCP_NODELAY,reinterpret_cast<char *>(&n),sizeof(n));}
}
SocketRuntime::SocketRuntime(){WSADATA w;if(WSAStartup(MAKEWORD(2,2),&w))throw rest::Failure("TCP 통신 초기화 실패");}
SocketRuntime::~SocketRuntime(){WSACleanup();}
void Channel::close(){if(socket_!=INVALID_SOCKET){closesocket(socket_);socket_=INVALID_SOCKET;}}
void Channel::shutdown(){if(socket_!=INVALID_SOCKET)::shutdown(socket_,SD_BOTH);}
void pauseUntil(Clock::time_point until,std::atomic<bool> &stop){while(Clock::now()<until){if(stop)throw rest::Stopped();std::this_thread::sleep_for(std::chrono::milliseconds(10));}if(stop)throw rest::Stopped();}
void Channel::wait(short events,Clock::time_point until,std::atomic<bool> &stop) const {
    for(;;){if(stop)throw rest::Stopped();auto remaining=std::chrono::duration_cast<std::chrono::milliseconds>(until-Clock::now()).count();if(remaining<=0)throw rest::Failure("TCP 대기 제한시간을 초과했습니다.");
        WSAPOLLFD fd={socket_,events,0};auto n=WSAPoll(&fd,1,static_cast<INT>(std::min<long long>(remaining,50)));if(n==SOCKET_ERROR)throw rest::Failure("TCP 연결 상태를 확인하지 못했습니다.");if(n>0){if(fd.revents&POLLNVAL)throw rest::Failure("TCP 연결이 닫혔습니다.");if(fd.revents&(events|POLLERR|POLLHUP))return;}}
}
Channel Channel::connect(const std::string &ip,unsigned port,unsigned timeout,std::atomic<bool> &stop){
    auto a=address(ip,port);Channel c(::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP));if(c.socket_==INVALID_SOCKET)throw rest::Failure("TCP 소켓 생성 실패");nonblocking(c.socket_);
    if(::connect(c.socket_,reinterpret_cast<sockaddr *>(&a),sizeof(a))==SOCKET_ERROR){auto error=WSAGetLastError();if(error!=WSAEWOULDBLOCK&&error!=WSAEINPROGRESS)throw rest::Failure("시험 대상 TCP 서버에 접속하지 못했습니다.");c.wait(POLLOUT,Clock::now()+std::chrono::milliseconds(timeout),stop);int actual=0,size=sizeof(actual);if(getsockopt(c.socket_,SOL_SOCKET,SO_ERROR,reinterpret_cast<char *>(&actual),&size)||actual)throw rest::Failure("시험 대상 TCP 연결이 거부되었거나 실패했습니다.");}return c;
}
Channel Channel::listen(const std::string &ip,unsigned port){
    auto a=address(ip,port);Channel c(::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP));if(c.socket_==INVALID_SOCKET)throw rest::Failure("TCP 수신 소켓 생성 실패");BOOL exclusive=TRUE;setsockopt(c.socket_,SOL_SOCKET,SO_EXCLUSIVEADDRUSE,reinterpret_cast<char *>(&exclusive),sizeof(exclusive));
    if(::bind(c.socket_,reinterpret_cast<sockaddr *>(&a),sizeof(a))||::listen(c.socket_,8))throw rest::Failure("TCP 수신 주소·포트를 열지 못했습니다. 포트 사용 상태를 확인하세요.");nonblocking(c.socket_);return c;
}
Channel Channel::accept(unsigned timeout,std::atomic<bool> &stop){auto until=Clock::now()+std::chrono::milliseconds(timeout);for(;;){wait(POLLIN,until,stop);auto s=::accept(socket_,nullptr,nullptr);if(s!=INVALID_SOCKET){Channel c(s);nonblocking(s);return c;}if(WSAGetLastError()!=WSAEWOULDBLOCK)throw rest::Failure("TCP 접속 수락에 실패했습니다.");}}
void Channel::send(const Bytes &b,unsigned timeout,std::atomic<bool> &stop,unsigned chunk){size_t offset=0;auto until=Clock::now()+std::chrono::milliseconds(timeout);
    try{while(offset<b.size()){wait(POLLOUT,until,stop);auto count=std::min<size_t>(b.size()-offset,chunk?chunk:65535);auto n=::send(socket_,reinterpret_cast<const char *>(b.data()+offset),static_cast<int>(count),0);if(n>0)offset+=n;else if(n==0||WSAGetLastError()!=WSAEWOULDBLOCK)throw rest::Failure("TCP 전송 중 연결이 종료됐습니다.");}}
    catch(const rest::Stopped &){throw IoStopped(Bytes(b.begin(),b.begin()+offset),true);}catch(const std::exception &e){throw IoFailure(e.what(),Bytes(b.begin(),b.begin()+offset),true);}
}
Bytes Channel::receive(unsigned timeout,std::atomic<bool> &stop){Bytes b;size_t needed=3;auto until=Clock::now()+std::chrono::milliseconds(timeout);
    try{while(b.size()<needed){wait(POLLIN,until,stop);unsigned char chunk[4096];auto n=recv(socket_,reinterpret_cast<char *>(chunk),static_cast<int>(std::min<size_t>(sizeof(chunk),needed-b.size())),0);if(n>0){b.insert(b.end(),chunk,chunk+n);if(b.size()==3){needed=unsigned(b[1])*256+b[2];if(needed<5)throw rest::Failure("수신 SIZE가 최소 프레임 길이보다 작습니다.");}}else if(n==0)throw rest::Failure("완전한 프레임을 받기 전에 TCP 연결이 종료됐습니다.");else if(WSAGetLastError()!=WSAEWOULDBLOCK)throw rest::Failure("TCP 데이터 수신 오류");}return b;}
    catch(const rest::Stopped &){throw IoStopped(b,false);}catch(const std::exception &e){throw IoFailure(e.what(),b,false);}
}
bool Channel::readable(unsigned ms,std::atomic<bool> &stop){auto until=Clock::now()+std::chrono::milliseconds(ms);while(Clock::now()<until){if(stop)throw rest::Stopped();WSAPOLLFD fd={socket_,POLLIN,0};auto n=WSAPoll(&fd,1,10);if(n==SOCKET_ERROR)throw rest::Failure("TCP 상태 확인 오류");if(n>0){unsigned char x;int got=recv(socket_,reinterpret_cast<char *>(&x),1,MSG_PEEK);if(got>0)return true;if(got==0)return false;}}return false;}
}
