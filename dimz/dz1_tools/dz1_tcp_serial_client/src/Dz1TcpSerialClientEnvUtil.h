#ifndef DZ1_TCP_SERIAL_CLIENT_ENV_UTIL_H_LOCAL
#define DZ1_TCP_SERIAL_CLIENT_ENV_UTIL_H_LOCAL

#include "Dz1TcpSerialClientEnv.h"

DZ1_CPPLINK Dz1Error Dz1TcpSerialClientPort_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialMsg *msg);
DZ1_CPPLINK Dz1Error Dz1TcpSerialClientPort_pinGen_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialClientPort *s,
																 Dz1TcpSerialMsgPresent present, Dz1SerialPinState pin);
DZ1_CPPLINK Dz1Error Dz1TcpSerialClientPort_portGen_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialMsgPresent present,
																  Dz1TcpSerialClientPort *s);

#endif