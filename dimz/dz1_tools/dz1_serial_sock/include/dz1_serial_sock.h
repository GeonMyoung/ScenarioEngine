#ifndef DZ1_SERIAL_SOCK_H
#define DZ1_SERIAL_SOCK_H

#include <dz1_socket.h>

DZ1_CPPLINK Dz1TcpClientSocket *Dz1SerialSock_new(int port, u32_t baud, Dz1Error *err);

#endif
