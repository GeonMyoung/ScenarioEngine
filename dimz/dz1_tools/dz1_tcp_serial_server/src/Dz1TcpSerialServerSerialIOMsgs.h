#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_SERIAL_I_O_MSGS_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_SERIAL_I_O_MSGS_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerDef.h"
#include "Dz1TcpSerialMsgDef.h"


typedef struct Dz1TcpSerialServerMsgRecv
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	Dz1Binary   *stream;
} Dz1TcpSerialServerMsgRecv;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerMsgRecv *Dz1TcpSerialServerMsgRecv_new(Dz1SockAddr *peer, 
																				 Dz1SockAddr *local, 
																				 Dz1Binary *stream, Dz1Error *err);
static __inline__ Dz1TcpSerialServerMsgRecv *Dz1TcpSerialServerMsgRecv_gen(Dz1Error *err) { return Dz1TcpSerialServerMsgRecv_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerMsgRecv_del(Dz1TcpSerialServerMsgRecv *p);
static __inline__ void Dz1TcpSerialServerMsgRecv_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerMsgRecv **p = (Dz1TcpSerialServerMsgRecv **)ptr;
	Dz1TcpSerialServerMsgRecv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerMsgRecv_dump(Dz1TcpSerialServerMsgRecv *p, int tab);

typedef struct Dz1TcpSerialServerMsgPin
{
	Dz1SockAddr       *peer;
	Dz1SockAddr       *local;
	Dz1SerialPinState  v;
} Dz1TcpSerialServerMsgPin;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerMsgPin *Dz1TcpSerialServerMsgPin_new(Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1SerialPinState v, Dz1Error *err);
static __inline__ Dz1TcpSerialServerMsgPin *Dz1TcpSerialServerMsgPin_gen(Dz1Error *err) { return Dz1TcpSerialServerMsgPin_new(NULL, NULL, Dz1SerialPinState_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerMsgPin_del(Dz1TcpSerialServerMsgPin *p);
static __inline__ void Dz1TcpSerialServerMsgPin_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerMsgPin **p = (Dz1TcpSerialServerMsgPin **)ptr;
	Dz1TcpSerialServerMsgPin_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerMsgPin_dump(Dz1TcpSerialServerMsgPin *p, int tab);

typedef struct Dz1TcpSerialServerMsgException
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
} Dz1TcpSerialServerMsgException;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerMsgException *Dz1TcpSerialServerMsgException_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *err);
static __inline__ Dz1TcpSerialServerMsgException *Dz1TcpSerialServerMsgException_gen(Dz1Error *err) { return Dz1TcpSerialServerMsgException_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerMsgException_del(Dz1TcpSerialServerMsgException *p);
static __inline__ void Dz1TcpSerialServerMsgException_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerMsgException **p = (Dz1TcpSerialServerMsgException **)ptr;
	Dz1TcpSerialServerMsgException_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerMsgException_dump(Dz1TcpSerialServerMsgException *p, int tab);

#endif
