#ifndef DZ1_INET_TELNET_H
#define DZ1_INET_TELNET_H

#include <dz1_error.h>
#include <dz1_socket.h>
#include <dz1_inet_telnet_msg.h>

DZ1_CPPLINK ssize_t Dz1InetTelnetPI_decode(Dz1InetTelnetMsg **_ret, u8_t *data, size_t size, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1InetTelnetPI_encode(u8_t **ret, Dz1InetTelnetMsg *src, Dz1Error *err);

DZ1_CPPLINK Dz1Error Dz1InetTelnetPI_sendCMD(Dz1TcpClientSocket *s, Dz1InetTelnetCmdPresent cmd);
DZ1_CPPLINK Dz1Error Dz1InetTelnetPI_sendNego(Dz1TcpClientSocket *s, Dz1InetTelnetCmdPresent nego, Dz1InetTelnetOptPresent opt);
DZ1_CPPLINK Dz1Error Dz1InetTelnetPI_sendBytes(Dz1TcpClientSocket *s, u8_t *data, u32_t size);

#endif

