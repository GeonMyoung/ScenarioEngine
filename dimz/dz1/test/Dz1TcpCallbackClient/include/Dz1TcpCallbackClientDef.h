#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_DEF_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_DEF_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "libdz1_support.h"

typedef void (*Dz1TcpCallbackClientException)(void *exceptionArg, Dz1Error *reason);

typedef struct Dz1TcpCallbackClientDef
{
	u32_t  dumb;
} Dz1TcpCallbackClientDef;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientDef *Dz1TcpCallbackClientDef_new(u32_t dumb, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientDef_del(Dz1TcpCallbackClientDef *p);
static __inline__ void Dz1TcpCallbackClientDef_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackClientDef **p = (Dz1TcpCallbackClientDef **)ptr;
	Dz1TcpCallbackClientDef_del(*p); *p = NULL;
}

#endif
