#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_TIMER_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_TIMER_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialClientDef.h"


typedef struct Dz1TcpSerialClientTimer
{
	u32_t  id;
} Dz1TcpSerialClientTimer;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientTimer *Dz1TcpSerialClientTimer_new(u32_t id, Dz1Error *err);
static __inline__ Dz1TcpSerialClientTimer *Dz1TcpSerialClientTimer_gen(Dz1Error *err) { return Dz1TcpSerialClientTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientTimer_del(Dz1TcpSerialClientTimer *p);
static __inline__ void Dz1TcpSerialClientTimer_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientTimer **p = (Dz1TcpSerialClientTimer **)ptr;
	Dz1TcpSerialClientTimer_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientTimer_dump(Dz1TcpSerialClientTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpSerialClientTimer_cmp(Dz1TcpSerialClientTimer *a, Dz1TcpSerialClientTimer *b);

#endif
