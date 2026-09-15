#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_DEF_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_DEF_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Dz1TcpSerialMsgDef.h"


typedef void (*Dz1TcpSerialClientException)(void *exceptionArg, Dz1Error *reason);

typedef struct Dz1TcpSerialClientDef
{
	s32_t  dummy;
} Dz1TcpSerialClientDef;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientDef *Dz1TcpSerialClientDef_new(s32_t dummy, Dz1Error *err);
static __inline__ Dz1TcpSerialClientDef *Dz1TcpSerialClientDef_gen(Dz1Error *err) { return Dz1TcpSerialClientDef_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientDef_del(Dz1TcpSerialClientDef *p);
static __inline__ void Dz1TcpSerialClientDef_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientDef **p = (Dz1TcpSerialClientDef **)ptr;
	Dz1TcpSerialClientDef_del(*p); *p = NULL;
}

#endif
