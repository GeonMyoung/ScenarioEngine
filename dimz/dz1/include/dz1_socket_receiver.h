#ifndef DZ1_SOCKET_RECEIVER_H
#define DZ1_SOCKET_RECEIVER_H

#include <dz1_socket.h>

typedef enum
{
	Dz1SocketReceierBehavior_continue,
	Dz1SocketReceierBehavior_term,
	Dz1SocketReceierBehavior_max
} Dz1SocketReceierBehavior;
#define Dz1SocketReceierBehavior_exception Dz1SocketReceierBehavior_max

#define DZ1_SOCK_REVC_EXCEPTION(errp, ret)					do { ERR_OUT(errp); ret = Dz1SocketReceierBehavior_exception; } while(0)
#define DZ1_SOCK_REVC_ERR_SET_EXCEPTION(errp, eval, ret)	do { ERR_SET_OUT(errp, eval); ret = Dz1SocketReceierBehavior_exception; } while(0)


// Issue Dz1TcpSocketReceiverForwardFunc when Receiver got data from socket
// Issue Dz1TcpSocketReceiverTimeoutFunc when Receiver got timeout
// Issue Dz1TcpSocketReceiverExceptionFunc when Receiver got exception
//		exception case
//			error occur while socket waiting
//			timeout handler return Dz1SocketReceierBehavior_exception
//			forwarder return Dz1SocketReceierBehavior_exception
typedef Dz1Error				 (*Dz1TcpSocketReceiverInitFunc)(void **ret, void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s);
typedef Dz1SocketReceierBehavior (*Dz1TcpSocketReceiverForwardFunc)(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s, u8_t *data, size_t size, Dz1Error *errp);
typedef Dz1SocketReceierBehavior (*Dz1TcpSocketReceiverTimeoutFunc)(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s, Dz1Error *errp);
typedef void					 (*Dz1TcpSocketReceiverExceptionFunc)(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s, Dz1Error *reason);

// Dz1TcpClientSocket *sock will be NULL if u set TRUE to autoClose and *sock will be closed after Receiver Terminate
// if autoClose set FALSE, *sock does not be NULL and not closed after Receiver Terminate
// cleanup function should cleaning up resources while receiving process(initialized by init callback function)
// if userParamDel is NULL, userParam is not deleted when Receiver is Terminated
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpSocketReceiver_start(Dz1SockAddr *peer, Dz1SockAddr *local,
														size_t bufSize, u32_t idleTime_ms,
														Dz1TcpClientSocket **sock, bool_t autoClose,
														Dz1TcpSocketReceiverInitFunc init,
														Dz1TcpSocketReceiverForwardFunc f,
														Dz1TcpSocketReceiverExceptionFunc e,
														Dz1TcpSocketReceiverTimeoutFunc to,
														Dz1CancelFunc cleanup,
														void **userParam, Dz1DelFunc userParamDel, Dz1Error *err);

// Issue Dz1UdpSocketReceiverForwardFunc when Receiver got data from socket
// Issue Dz1UdpSocketReceiverTimeoutFunc when Receiver got timeout
// Issue Dz1UdpSocketReceiverExceptionFunc when Receiver got exception
//		exception case
//			error occur while socket waiting
//			timeout handler return Dz1SocketReceierBehavior_exception
//			forwarder return Dz1SocketReceierBehavior_exception
typedef Dz1Error				 (*Dz1UdpSocketReceiverInitFunc)(void **ret, void *uArg, Dz1SockAddr *local, Dz1UdpSocket *s);
typedef Dz1SocketReceierBehavior (*Dz1UdpSocketReceiverForwardFunc)(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UdpSocket *s, u8_t *data, size_t size, Dz1Error *errp);
typedef Dz1SocketReceierBehavior (*Dz1UdpSocketReceiverTimeoutFunc)(void *uArg, void *uRsc, Dz1SockAddr *local, Dz1UdpSocket *s, Dz1Error *errp);
typedef void					 (*Dz1UdpSocketReceiverExceptionFunc)(void *uArg, void *uRsc, Dz1SockAddr *local, Dz1UdpSocket *s, Dz1Error *reason);

// Dz1UdpClientSocket *sock will be NULL if u set TRUE to autoClose and *sock will be closed after Receiver Terminate
// if autoClose set FALSE, *sock does not be NULL and not closed after Receiver Terminate
// cleanup function should cleaning up resources while receiving process(initialized by init callback function)
// if userParamDel is NULL, userParam is not deleted when Receiver is Terminated
DZ1_CPPLINK DZ1_DLLPORT int Dz1UdpSocketReceiver_start(Dz1SockAddr *local, size_t bufSize, u32_t idleTime_ms,
														Dz1UdpSocket **sock, bool_t autoClose,
														Dz1UdpSocketReceiverInitFunc init,
														Dz1UdpSocketReceiverForwardFunc f,
														Dz1UdpSocketReceiverExceptionFunc e,
														Dz1UdpSocketReceiverTimeoutFunc to,
														Dz1CancelFunc cleanup,
														void **userParam, Dz1DelFunc userParamDel, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SocketReceiver_stop(u32_t id);
#define Dz1TcpSocketReceiver_stop		Dz1SocketReceiver_stop
#define Dz1UdpSocketReceiver_stop		Dz1SocketReceiver_stop

static __inline__ void Dz1SocketReceiver_startCancel(void *ptr)
{
	int *id = (int *)ptr;
	if (*id != -1) Dz1SocketReceiver_stop(*id);
	*id = -1;
}

typedef Dz1Error				 (*Dz1UniSocketReceiver_InitF)(	  void **ret, void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniClientSocket *s);
typedef Dz1SocketReceierBehavior (*Dz1UniSocketReceiver_fwdF)(	  void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniClientSocket *s, u8_t *data, size_t size, Dz1Error *status);
typedef Dz1SocketReceierBehavior (*Dz1UniSocketReceiver_tineoutF)(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniClientSocket *s, Dz1Error *errp);
typedef void					 (*Dz1UniSocketReceiver_errF)(	  void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniClientSocket *s, Dz1Error *reason);

DZ1_CPPLINK DZ1_DLLPORT int		 Dz1UniSocketReceiver_start(Dz1UniClientSocket **sock, bool_t autoClose,
															Dz1SockAddr *peer, Dz1SockAddr *local,
															size_t bufSize, u32_t idleTime_ms,
															Dz1UniSocketReceiver_InitF init,
															Dz1UniSocketReceiver_fwdF f,
															Dz1UniSocketReceiver_errF e,
															Dz1UniSocketReceiver_tineoutF to,
															Dz1CancelFunc cleanup,
															void **uArg, Dz1DelFunc uArgDel, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1UniSocketReceiver_stop(u32_t id);
static __inline__ void			 Dz1UniSocketReceiver_startCancel(void *ptr)
{
	int *id = (int *)ptr;
	if (*id != -1) Dz1SocketReceiver_stop(*id);
	*id = -1;
}

#endif
