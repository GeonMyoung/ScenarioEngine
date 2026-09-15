#ifndef DZ1_SOCKET_ACCEPTOR_H
#define DZ1_SOCKET_ACCEPTOR_H

#include <dz1_socket.h>

typedef enum 
{
	Dz1TcpSocketAcceptorBehavior_continue,
	Dz1TcpSocketAcceptorBehavior_term,
	Dz1TcpSocketAcceptorBehavior_max
} Dz1TcpSocketAcceptorBehavior;
#define Dz1TcpSocketAcceptorBehavior_exception	Dz1TcpSocketAcceptorBehavior_max

#define DZ1_SOCK_ACCEPTOR_ERR_OUT(errp, ret)	\
	do { ERR_OUT(errp); (ret) = Dz1TcpSocketAcceptorBehavior_exception; } while(0)

#define DZ1_SOCK_ACCEPTOR_ERRSET_OUT(errp, code, ret)	\
	do { ERR_SET_OUT(errp, code); (ret) = Dz1TcpSocketAcceptorBehavior_exception; } while(0)

typedef Dz1Error (*Dz1TcpSocketAcceptorInitFunc)(void **uRsc, void *uArg, Dz1TcpServerSocket *s);
// Dz1TcpClientSocket *s should be NULL.
// other then Acceptor will close
// Dz1SockAddr *local and *peer is stack variable address
// so if u need to use lather then clone it
typedef Dz1TcpSocketAcceptorBehavior(*Dz1TcpSocketAcceptorForwardFunc)(void *uArg, void *uRsc,
											Dz1TcpClientSocket **s, Dz1SockAddr *local, Dz1SockAddr *peer, Dz1Error *errp);
typedef Dz1TcpSocketAcceptorBehavior (*Dz1TcpSocketAcceptorTimeoutFunc)(void *uArg, void *uRsc, Dz1TcpServerSocket *s);
typedef void (*Dz1TcpSocketAcceptorExceptionFunc)(void *uArg, void *uRsc, Dz1TcpServerSocket *s, Dz1Error *reason);

// idleTime_ms = 0 -> No idle timeout, acceptTime_ms = 0 -> No accept timeout
// Cleanup Function should do cleaning up resources while accepting process
// userParam is not deleted event Acceptor is terminated
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1TcpSocketAcceptor_start(Dz1TcpServerSocket *sock, bool_t autoClose,
														 u32_t idleTime_ms, u32_t acceptTime_ms,
														 Dz1TcpSocketAcceptorInitFunc init,
														 Dz1TcpSocketAcceptorForwardFunc f,
														 Dz1TcpSocketAcceptorExceptionFunc e,
														 Dz1TcpSocketAcceptorTimeoutFunc to,
														 Dz1CancelFunc cleanup,
														 void **userParam,
														 Dz1DelFunc userParamDel,
														 Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TcpSocketAcceptor_stop(u32_t id);
static __inline__ void Dz1TcpSocketAcceptor_cancel(void *ptr)
{
	u32_t *id = (u32_t *)ptr;
	Dz1TcpSocketAcceptor_stop(*id); *id = -1;
}


typedef Dz1Error					 (*Dz1UniSocketAcceptor_initF)(void **uRsc, void *uArg, Dz1SockAddr *local, Dz1UniServerSocket *s);
typedef Dz1TcpSocketAcceptorBehavior (*Dz1UniSocketAcceptor_fwdF)(void *uArg, void *uRsc, Dz1UniClientSocket **s, Dz1SockAddr *local, Dz1SockAddr *peer, Dz1Error *errp);
typedef Dz1TcpSocketAcceptorBehavior (*Dz1UniSocketAcceptor_timeoutF)(void *uArg, void *uRsc, Dz1UniServerSocket *s);
typedef void						 (*Dz1UniSocketAcceptor_errF)(void *uArg, void *uRsc, Dz1UniServerSocket *s, Dz1Error *reason);

DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1UniSocketAcceptor_start(Dz1UniServerSocket **sock, bool_t autoClose, Dz1SockAddr *local, 
														 u32_t idleTime_ms, u32_t acceptTime_ms,
														 Dz1UniSocketAcceptor_initF		 init,
														 Dz1UniSocketAcceptor_fwdF		 f,
														 Dz1UniSocketAcceptor_errF		 e,
														 Dz1UniSocketAcceptor_timeoutF	 to,
														 Dz1CancelFunc					 cleanup,
														 void **uArg, Dz1CancelFunc uArgDel, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1UniSocketAcceptor_stop(u32_t id);
static __inline__ void			 Dz1UniSocketAcceptor_startCancel(void *ptr)
{
	u32_t *id = (u32_t *)ptr;
	if (id != NULL && *id != (u32_t)-1) Dz1UniSocketAcceptor_stop(*id);
	*id = -1;
}

#endif
