#ifndef DZ1_INET_FTP_MSG_UTIL_H
#define DZ1_INET_FTP_MSG_UTIL_H

#include "dz1_inet_ftp_control_pi_msg.h"

DZ1_CPPLINK ssize_t Dz1InetFtpCPIMsg_encode(u8_t **_dst, Dz1InetFtpCPIMsg *src, Dz1Error *err);

DZ1_CPPLINK ssize_t Dz1InetFtpCPIMsg_decode(Dz1InetFtpCPIMsg **_dst, u8_t *src, size_t size, bool_t *isComplete, Dz1Error *err);

DZ1_CPPLINK ssize_t Dz1InetFtpSockAddr_dec(Dz1SockAddr *dst, u8_t *src, size_t size, Dz1Error *errp);

#endif

