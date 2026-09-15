#ifndef ITS_ISO_SERVER_SOCKET_RECEIVER_H_LOCAL
#define ITS_ISO_SERVER_SOCKET_RECEIVER_H_LOCAL

#include <dz1_sock_addr.h>
#include <dz1_socket.h>
#include <dz1_socket_receiver.h>

DZ1_CPPLINK u32_t ItsIsoSocketReceiver_start(void *tParent,
												   Dz1SockAddr *peer, Dz1SockAddr *local,
												   Dz1TcpClientSocket *sock, u32_t sid, Dz1Error *err);
DZ1_CPPLINK void ItsIsoSocketReceiver_stop(u32_t thID);

#endif