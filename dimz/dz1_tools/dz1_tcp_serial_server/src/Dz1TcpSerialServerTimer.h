#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_TIMER_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_TIMER_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerDef.h"


typedef struct Dz1TcpSerialServerTimer
{
	u32_t  id;
} Dz1TcpSerialServerTimer;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerTimer *Dz1TcpSerialServerTimer_new(u32_t id, Dz1Error *err);
static __inline__ Dz1TcpSerialServerTimer *Dz1TcpSerialServerTimer_gen(Dz1Error *err) { return Dz1TcpSerialServerTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerTimer_del(Dz1TcpSerialServerTimer *p);
static __inline__ void Dz1TcpSerialServerTimer_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerTimer **p = (Dz1TcpSerialServerTimer **)ptr;
	Dz1TcpSerialServerTimer_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerTimer_dump(Dz1TcpSerialServerTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpSerialServerTimer_cmp(Dz1TcpSerialServerTimer *a, Dz1TcpSerialServerTimer *b);

#endif
