#ifndef DZ1_INET_FTP_DTP_H
#define DZ1_INET_FTP_DTP_H

#include <dz1_sock_addr.h>
#include <dz1_socket.h>
#include "dz1_inet_ftp_env.h"

DZ1_CPPLINK u32_t Dz1InetFtpDTP_start(void *tParent, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock,
									  Dz1InetFtpDTPSpec *spec, Dz1InetFtpTransfer *job, Dz1Error *err);

DZ1_CPPLINK void Dz1InetFtpDTP_stop(u32_t id);

#endif

