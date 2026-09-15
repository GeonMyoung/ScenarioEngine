#ifndef DZ1_TCP_SERIAL_SERVER_H
#define DZ1_TCP_SERIAL_SERVER_H

#include <Dz1TcpSerialServerDef.h>

DZ1_CPPLINK void *Dz1TcpSerialServer_new(Dz1TcpSerialServerConfig *cfg,
										 Dz1TcpSerialServerException exceptionProc, void *exceptionArg,
										 Dz1Error *err);
DZ1_CPPLINK void Dz1TcpSerialServer_del(void *task);

#endif
