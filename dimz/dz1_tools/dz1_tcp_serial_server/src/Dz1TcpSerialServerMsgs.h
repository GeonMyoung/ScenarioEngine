#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_MSGS_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_MSGS_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerDef.h"


typedef struct Dz1TcpSerialServerMsgDefault
{
	u32_t *dummy;
} Dz1TcpSerialServerMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerMsgDefault *Dz1TcpSerialServerMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ Dz1TcpSerialServerMsgDefault *Dz1TcpSerialServerMsgDefault_gen(Dz1Error *err) { return Dz1TcpSerialServerMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerMsgDefault_del(Dz1TcpSerialServerMsgDefault *p);
static __inline__ void Dz1TcpSerialServerMsgDefault_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerMsgDefault **p = (Dz1TcpSerialServerMsgDefault **)ptr;
	Dz1TcpSerialServerMsgDefault_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerMsgDefault_dump(Dz1TcpSerialServerMsgDefault *p, int tab);

#endif
