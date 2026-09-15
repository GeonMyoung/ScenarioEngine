#ifndef DZ1_TCP_SERIAL_SERVER_ENV_UTIL_H_LOCAL
#define DZ1_TCP_SERIAL_SERVER_ENV_UTIL_H_LOCAL

#include <Dz1TcpSerialMsgDef.h>

#include "Dz1TcpSerialServerEnv.h"

DZ1_CPPLINK void		Dz1TcpSerialServerSession_cleanup(Dz1TcpSerialServerSession *p);
static __inline__ void	Dz1TcpSerialServerSession_cleanupAndSetNull(void *ptr)
{
	Dz1TcpSerialServerSession **p = (Dz1TcpSerialServerSession **)ptr;
	Dz1TcpSerialServerSession_cleanup(*p); *p = NULL;
}


DZ1_CPPLINK Dz1Error	Dz1TcpSerialServerSerial_write(Dz1TcpSerialServerSerial *p, u8_t *data, size_t size);
DZ1_CPPLINK Dz1Error	Dz1TcpSerialServerSerial_writeDone(Dz1TcpSerialServerSerial *p);
DZ1_CPPLINK Dz1Error	Dz1TcpSerialServerSerial_setRTS(Dz1TcpSerialServerSerial *p, Dz1SerialPinState v);

DZ1_CPPLINK Dz1Error	Dz1TcpSerialServerSerial_getCTS(Dz1TcpSerialServerSerial *p, Dz1SerialPinState *v);

DZ1_CPPLINK Dz1Error	Dz1TcpSerialServerSerial_setDTR(Dz1TcpSerialServerSerial *p, Dz1SerialPinState v);

DZ1_CPPLINK Dz1Error	Dz1TcpSerialServerSerial_getDSR(Dz1TcpSerialServerSerial *p, Dz1SerialPinState *v);

DZ1_CPPLINK void		Dz1TcpSerialServerSerial_cleanup(Dz1TcpSerialServerSerial *p);
static __inline__ void	Dz1TcpSerialServerSerial_cleanupAndSetNull(void *ptr)
{
	Dz1TcpSerialServerSerial **p = (Dz1TcpSerialServerSerial **)ptr;
	Dz1TcpSerialServerSerial_cleanup(*p); *p = NULL;
}

#endif