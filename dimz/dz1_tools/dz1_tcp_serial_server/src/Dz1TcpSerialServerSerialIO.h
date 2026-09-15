#ifndef DZ1_TCP_SERIAL_SERVER_SERIAL_IO_H_LOCAL
#define DZ1_TCP_SERIAL_SERVER_SERIAL_IO_H_LOCAL

#include <Dz1TcpSerialMsgDef.h>

#include "Dz1TcpSerialServerEnv.h"

DZ1_CPPLINK Dz1Error Dz1TcpSerialServer_serialIO(Dz1TcpSerialServerSession *session, Dz1TcpSerialMsg *pkt,
												 u32_t myQueueID,
												 void *uArg, void *uRsc, void *timer);
DZ1_CPPLINK Dz1Error Dz1TcpSerialServerSerialIO_init(void *tSelf);

DZ1_CPPLINK Dz1TcpSerialServerSerial *Dz1TcpSerialServerSerialIO_openNullModem(Dz1SockAddr *peer, Dz1SockAddr *local,
																			   u32_t myQueueID, Dz1TcpSerialServerPreset *cfg);
DZ1_CPPLINK Dz1Error Dz1TcpSerialServerSerialIO_write(Dz1TcpSerialServerSession *session, Dz1Binary *stream,
													  void *uArg, void *uRsc, void *timer);

#endif