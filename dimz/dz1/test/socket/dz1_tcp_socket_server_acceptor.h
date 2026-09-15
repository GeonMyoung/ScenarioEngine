#ifndef DZ1_TCP_SOCKET_SERVER_ACCEPTOR_H
#define DZ1_TCP_SOCKET_SERVER_ACCEPTOR_H

#include <dz1_sock_addr.h>

// Post CONNECTED Message to TASK
DZ1_CPPLINK u32_t Dz1TcpSocketServerAcceptor_start(u32_t parentQueueID, Dz1SockAddr *server, Dz1Error *err);

// Close socket immediately
DZ1_CPPLINK u32_t Dz1TcpSocketServerAcceptor2_start(u32_t parentQueueID, Dz1SockAddr *server, Dz1Error *err);

// Post CONNECTED2 Message to TASK
DZ1_CPPLINK u32_t Dz1TcpSocketServerAcceptor3_start(u32_t parentQueueID, Dz1SockAddr *server, Dz1Error *err);

DZ1_CPPLINK void Dz1TcpSocketServerAcceptor_stop(u32_t thid);

#endif