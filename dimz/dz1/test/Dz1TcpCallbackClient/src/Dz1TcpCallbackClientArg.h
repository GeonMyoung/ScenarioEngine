#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_ARG_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_ARG_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Dz1TcpCallbackClientDef.h"

typedef struct Dz1TcpCallbackClientArg
{
	Dz1TcpCallbackClientException  exceptionProc;
	void                          *exceptionArg;
} Dz1TcpCallbackClientArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientArg *Dz1TcpCallbackClientArg_new(Dz1TcpCallbackClientException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientArg_del(Dz1TcpCallbackClientArg *p);
static __inline__ void Dz1TcpCallbackClientArg_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackClientArg **p = (Dz1TcpCallbackClientArg **)ptr;
	Dz1TcpCallbackClientArg_del(*p); *p = NULL;
}

#endif
