#ifndef DZ1_SOCKET_H
#define DZ1_SOCKET_H

#include <dz1_timeval.h>
#include <dz1_sock_addr.h>

DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1Socket_init(void);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Socket_cleanup(void);
static __inline__ void			 Dz1Socket_initCancel(void *ptr) { Dz1Socket_cleanup(); }

#ifndef UNIX_SYSTEM						// WIN32, C++ Builder

typedef int socklen_t;
typedef unsigned short in_port_t;

#define MSG_NOSIGNAL		0

#include <winsock2.h>

#ifndef ECONNREFUSED
#define ECONNREFUSED		WSAECONNREFUSED
#endif // UNIX_SYSTEM

#ifndef __BORLANDC__
#pragma comment(lib, "ws2_32.lib")
#endif

#else	// UNIX_SYSTEM					// Linux, Solaris, AIX, etc...

#ifdef MAC_OS_X
#define MSG_NOSIGNAL		0
#endif	// MAC_OS_X

typedef int SOCKET;
#define INVALID_SOCKET		-1
#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE INVALID_SOCKET
#endif	// INVALID_HANDLE_VALUE

#endif	// UNIX_SYSTEM

typedef enum
{
	Dz1SocketWaitFlag_in = 0x1,
	Dz1SocketWaitFlag_out = 0x2,
	Dz1SocketWaitFlag_inout = 0x3,
	Dz1SocketWaitFlag_except = 0x4,
	Dz1SocketWaitFlag_exceptin = 0x5,
	Dz1SocketWaitFlag_exceptout = 0x6,
	Dz1SocketWaitFlag_all = 0x7,
} Dz1SocketWaitFlag;

///////////////////////////////////////////////////////////////////////////////
// TCP Client Socket
#define DZ1_TCP_SOCK_FLAG_COMPLETE			0x00000001
#define DZ1_TCP_SOCK_FLAG_URGENT			0x00000002

typedef struct Dz1TcpClientSocket
{
	void *specific;
	Dz1DelFunc specific_del;

	int (*wait)(struct Dz1TcpClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err);
	ssize_t (*send)(struct Dz1TcpClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
	ssize_t (*recv)(struct Dz1TcpClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
	SOCKET	(*getOSHandle)(struct Dz1TcpClientSocket *p);
} Dz1TcpClientSocket;

#define										 Dz1TcpClientSocket_open(dp, lp, top, ep) _Dz1TcpClientSocket_open((dp), (lp), (top), (ep), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpClientSocket *_Dz1TcpClientSocket_open(Dz1SockAddr *dst, Dz1SockAddr *local, struct timeval *to, Dz1Error *err, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1TcpClientSocket_close(Dz1TcpClientSocket *p);
static __inline__ void						 Dz1TcpClientSocket_closeAndSetNull(void *ptr)
{
	Dz1TcpClientSocket **p = (Dz1TcpClientSocket **)ptr;
	Dz1TcpClientSocket_close(*p); *p = NULL;
}
#define Dz1TcpClientSocket_del				 Dz1TcpClientSocket_close
#define Dz1TcpClientSocket_delAndSetNull	 Dz1TcpClientSocket_closeAndSetNull

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpClientSocket	*Dz1TcpClientSocket_encapsulation(void **specific, Dz1DelFunc specific_del,
																			  int (*wait)(Dz1TcpClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err),
																			  ssize_t (*send)(Dz1TcpClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err),
																			  ssize_t (*recv)(Dz1TcpClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err),
																			  SOCKET (*getOSHandle)(Dz1TcpClientSocket *p), Dz1Error *err);
// TCP Client Socket
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TCP Server Socket
typedef struct Dz1TcpServerSocket
{
	void *specific;
	Dz1DelFunc specific_del;

	int (*wait)(struct Dz1TcpServerSocket *p, struct timeval *to, Dz1Error *err);
	Dz1TcpClientSocket *(*accept)(struct Dz1TcpServerSocket *p, Dz1SockAddr *local, Dz1SockAddr *peer, struct timeval *to, Dz1Error *err);
} Dz1TcpServerSocket;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpServerSocket	*Dz1TcpServerSocket_open(Dz1SockAddr *local, u16_t *o_port, int backlog, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1TcpServerSocket_close(Dz1TcpServerSocket *p);
static __inline__ void						 Dz1TcpServerSocket_closeAndSetNull(void *ptr)
{
	Dz1TcpServerSocket **p = (Dz1TcpServerSocket **)ptr;
	Dz1TcpServerSocket_close(*p); *p = NULL;
}

#define Dz1TcpServerSocket_del				Dz1TcpServerSocket_close
#define Dz1TcpServerSocket_delAndSetNull	Dz1TcpServerSocket_closeAndSetNull
// TCP Server Socket
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UDP Socket
#define DZ1_UDP_SOCK_FLAG_COMPLETE			0x00000001

typedef struct Dz1UdpSocket
{
	void *specific;
	Dz1DelFunc specific_del;

	int		 (*wait)(struct Dz1UdpSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err);
	ssize_t	 (*send)(struct Dz1UdpSocket *, Dz1SockAddr *dst, uint8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
	ssize_t  (*recv)(struct Dz1UdpSocket *p, Dz1SockAddr *src, uint8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
	SOCKET	 (*getOSHandle)(struct Dz1TcpClientSocket *p);
} Dz1UdpSocket;

#define									 Dz1UdpSocket_open(peerp, localp, tv_timeoutp, errp)	_Dz1UdpSocket_open((peerp), (localp), (tv_timeoutp), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1UdpSocket   *_Dz1UdpSocket_open(Dz1SockAddr *peer, Dz1SockAddr *local, struct timeval *to, Dz1Error *err, const char *__file__, int __line__);
// #define									 Dz1UdpSocket_openAsServer(ver, io_port_p, to_p, ep)	_Dz1UdpSocket_openAsServer(ver, io_port_p, to_p, ep, __FILE__, __LINE__)
// DZ1_CPPLINK DZ1_DLLPORT Dz1UdpSocket   *_Dz1UdpSocket_openAsServer(Dz1SocketVer ver, u16_t *in_out_port, struct timeval *to, Dz1Error *err, const char *__file__, int __line__);
// DZ1_CPPLINK DZ1_DLLPORT Dz1UdpSocket    *Dz1UdpSocket_accept(Dz1UdpSocket *sock_svr, struct timeval *to, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1UdpSocket_close(Dz1UdpSocket *p);
static __inline__ void					 Dz1UdpSocket_closeAndSetNull(void *ptr)
{
	Dz1UdpSocket **p = (Dz1UdpSocket **)ptr;
	Dz1UdpSocket_close(*p); *p = NULL;
}
#define Dz1UdpSocket_del				 Dz1UdpSocket_close
#define Dz1UdpSocket_delAndSetNull		 Dz1UdpSocket_closeAndSetNull
// UDP Socket
///////////////////////////////////////////////////////////////////////////////

typedef enum Dz1UniSocketType
{
	Dz1UniSocketType_stream		= SOCK_STREAM,
	Dz1UniSocketType_dgram		= SOCK_DGRAM,
	Dz1UniSocketType_raw		= SOCK_RAW
} Dz1UniSocketType;

///////////////////////////////////////////////////////////////////////////////
// Unified Client Socket
#define DZ1_UNI_SOCK_FLAG_COMPLETE			0x00000001
typedef struct Dz1UniClientSocket
{
	void *specific;
	Dz1DelFunc specific_del;

	int (*wait)(struct Dz1UniClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err);
	ssize_t (*send)(struct Dz1UniClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
	ssize_t (*recv)(struct Dz1UniClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
	SOCKET	(*getOSHandle)(struct Dz1UniClientSocket *p, Dz1Error *err);
} Dz1UniClientSocket;

#define										 Dz1UniClientSocket_open(dp, lp, type, top, ep) _Dz1UniClientSocket_open(dp, lp, type, top, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1UniClientSocket *_Dz1UniClientSocket_open(Dz1SockAddr *dst, Dz1SockAddr *local, Dz1UniSocketType type, struct timeval *to, Dz1Error *err, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1UniClientSocket_close(Dz1UniClientSocket *p);
static __inline__ void						 Dz1UniClientSocket_closeAndSetNull(void *ptr)
{
	Dz1UniClientSocket **p = (Dz1UniClientSocket **)ptr;
	Dz1UniClientSocket_close(*p); *p = NULL;
}
#define Dz1UniClientSocket_del				 Dz1UniClientSocket_close
#define Dz1UniClientSocket_delAndSetNull	 Dz1UniClientSocket_closeAndSetNull

typedef int		 (*Dz1UniClientSocket_waitF)(Dz1UniClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err);
typedef ssize_t	 (*Dz1UniClientSocket_sendF)(Dz1UniClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
typedef ssize_t	 (*Dz1UniClientSocket_recvF)(Dz1UniClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err);
typedef SOCKET	 (*Dz1UniClientSocket_getfdF)(Dz1UniClientSocket *p, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1UniClientSocket	*Dz1UniClientSocket_encapsulation(void **specific, Dz1DelFunc specific_del, 
																			  Dz1UniClientSocket_waitF wait_f,
																			  Dz1UniClientSocket_sendF send_f,
																			  Dz1UniClientSocket_recvF recv_f,
																			  Dz1UniClientSocket_getfdF getOsHandle_f,
																			  Dz1Error *err);
// Unified Client Socket
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Unified Server Socket
typedef struct Dz1UniServerSocket
{
	void *specific;
	Dz1DelFunc specific_del;

	int (*wait)(struct Dz1UniServerSocket *p, struct timeval *to, Dz1Error *err);
	Dz1UniClientSocket *(*accept)(struct Dz1UniServerSocket *p, Dz1SockAddr *local, Dz1SockAddr *peer, struct timeval *to, Dz1Error *err);
} Dz1UniServerSocket;

#define										 Dz1UniServerSocket_open(lp, oport, type, bl, ep) _Dz1UniServerSocket_open(lp, oport, type, bl, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1UniServerSocket *_Dz1UniServerSocket_open(Dz1SockAddr *local, u16_t *o_port, Dz1UniSocketType type, int backlog, Dz1Error *err, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1UniServerSocket_close(Dz1UniServerSocket *p);
static __inline__ void						 Dz1UniServerSocket_closeAndSetNull(void *ptr)
{
	Dz1UniServerSocket **p = (Dz1UniServerSocket **)ptr;
	Dz1UniServerSocket_close(*p); *p = NULL;
}

#define Dz1UniServerSocket_del				 Dz1UniServerSocket_close
#define Dz1UniServerSocket_delAndSetNull	 Dz1UniServerSocket_closeAndSetNull
// Unified Server Socket
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT int _GetSockError(void);

#endif
