#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_ARG_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_ARG_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Dz1TcpCallbackServerDef.h"


typedef struct Dz1TcpCallbackServerArg
{
	u16_t                          port;
	Dz1TcpCallbackServerException  exceptionProc;
	void                          *exceptionArg;
} Dz1TcpCallbackServerArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerArg *Dz1TcpCallbackServerArg_new(u16_t port, 
																			 Dz1TcpCallbackServerException exceptionProc, 
																			 void *exceptionArg, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerArg *Dz1TcpCallbackServerArg_gen(Dz1Error *err) { return Dz1TcpCallbackServerArg_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerArg_del(Dz1TcpCallbackServerArg *p);
static __inline__ void Dz1TcpCallbackServerArg_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackServerArg **p = (Dz1TcpCallbackServerArg **)ptr;
	Dz1TcpCallbackServerArg_del(*p); *p = NULL;
}

#endif
