#ifndef DZ1_TCP_SOCKET_SERVER_RECEIVER_H
#define DZ1_TCP_SOCKET_SERVER_RECEIVER_H

#include <dz1_sock_addr.h>
#include <dz1_socket.h>
DZ1_CPPLINK u32_t Dz1TcpSocketServerReceiver_start(u32_t parentQueueID,
												   Dz1SockAddr *peer, Dz1SockAddr *local,
												   Dz1TcpClientSocket *sock, Dz1Error *err);

DZ1_CPPLINK void Dz1TcpSocketServerReceiver_stop(u32_t id);

static __inline__ void Dz1TcpSocketServerReceiver_startCancel(void *ptr)
{
	u32_t *id = (u32_t *)ptr;
	Dz1TcpSocketServerReceiver_stop(*id); *id = -1;
}

#endif
