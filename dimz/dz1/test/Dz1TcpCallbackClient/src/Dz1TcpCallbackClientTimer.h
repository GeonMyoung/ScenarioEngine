#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_TIMER_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_TIMER_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Dz1TcpCallbackClientDef.h"

typedef struct Dz1TcpCallbackClientTimer
{
	u32_t        id;
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
} Dz1TcpCallbackClientTimer;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientTimer *Dz1TcpCallbackClientTimer_new(u32_t id, 
																				 Dz1SockAddr *peer, 
																				 Dz1SockAddr *local, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientTimer_del(Dz1TcpCallbackClientTimer *p);
static __inline__ void Dz1TcpCallbackClientTimer_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackClientTimer **p = (Dz1TcpCallbackClientTimer **)ptr;
	Dz1TcpCallbackClientTimer_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientTimer_dump(Dz1TcpCallbackClientTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpCallbackClientTimer_cmp(Dz1TcpCallbackClientTimer *a, Dz1TcpCallbackClientTimer *b);

#endif
