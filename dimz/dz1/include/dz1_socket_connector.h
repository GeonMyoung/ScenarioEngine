#ifndef DZ1_SOCKET_COMMECTOR_H
#define DZ1_SOCKET_COMMECTOR_H

#include <dz1_socket.h>
#define DZ1_TCP_CONNECTOR_RETRY_FOREVER			-1
#define DZ1_TCP_CONNECTOR_TRY_ONCE				0
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpClientSocket *Dz1TcpSocketConnector_func(Dz1SockAddr *dst, Dz1SockAddr *local,
																		u32_t period_sec, int retry, bool_t wait_and_connect,
																		Dz1Error *err);

typedef void (*Dz1TcpSocketConnectorCallback)(void *ptr, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket **s, Dz1Error *reason);

// 성공 시 callback function에 (*s)값이 NULL이 아님
// 실패 시 callback function에 (*s)값이 NULL
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1TcpSocketConnectorThread_create(Dz1SockAddr *dst,
																 u32_t period_sec, int retry, bool_t wait_and_connect,
																 Dz1TcpSocketConnectorCallback callback, void *callback_param,
																 u32_t thread_log_bits, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TcpSocketConnectorThread_join(u32_t id);

#define Dz1TcpSocketConnectorThread_start(dstp, periods, retry, bool_waitnconn, cb, cbp, loglv, errp)	\
	Dz1TcpSocketConnectorThread_create((dstp), (periods), (retry), (bool_waitnconn), (cb), (cbp), (loglv), (errp))
#define Dz1TcpSocketConnectorThread_stop(id)								Dz1TcpSocketConnectorThread_join((id))
#endif
