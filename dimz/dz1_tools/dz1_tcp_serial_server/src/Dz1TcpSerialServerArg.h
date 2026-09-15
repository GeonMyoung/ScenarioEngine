#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_ARG_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_ARG_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerDef.h"


typedef struct Dz1TcpSerialServerArg
{
	Dz1TcpSerialServerConfig    *config;
	Dz1TcpSerialServerException  exceptionProc;
	void                        *exceptionArg;
} Dz1TcpSerialServerArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerArg *Dz1TcpSerialServerArg_new(Dz1TcpSerialServerConfig *config, 
																		 Dz1TcpSerialServerException exceptionProc, 
																		 void *exceptionArg, Dz1Error *err);
static __inline__ Dz1TcpSerialServerArg *Dz1TcpSerialServerArg_gen(Dz1Error *err) { return Dz1TcpSerialServerArg_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerArg_del(Dz1TcpSerialServerArg *p);
static __inline__ void Dz1TcpSerialServerArg_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerArg **p = (Dz1TcpSerialServerArg **)ptr;
	Dz1TcpSerialServerArg_del(*p); *p = NULL;
}

#endif
