#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_ARG_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_ARG_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialClientDef.h"


typedef struct Dz1TcpSerialClientArg
{
	Dz1SockAddr                 *serverAddr;
	Dz1TcpSerialClientException  exceptionProc;
	void                        *exceptionArg;
} Dz1TcpSerialClientArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientArg *Dz1TcpSerialClientArg_new(Dz1SockAddr *serverAddr, 
																		 Dz1TcpSerialClientException exceptionProc, 
																		 void *exceptionArg, Dz1Error *err);
static __inline__ Dz1TcpSerialClientArg *Dz1TcpSerialClientArg_gen(Dz1Error *err) { return Dz1TcpSerialClientArg_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientArg_del(Dz1TcpSerialClientArg *p);
static __inline__ void Dz1TcpSerialClientArg_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientArg **p = (Dz1TcpSerialClientArg **)ptr;
	Dz1TcpSerialClientArg_del(*p); *p = NULL;
}

#endif
