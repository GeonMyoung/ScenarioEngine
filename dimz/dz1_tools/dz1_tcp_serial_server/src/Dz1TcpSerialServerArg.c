//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerArg.h"

Dz1TcpSerialServerArg *Dz1TcpSerialServerArg_new(Dz1TcpSerialServerConfig *config, 
												 Dz1TcpSerialServerException exceptionProc, 
												 void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerArg *__internal_ret = (Dz1TcpSerialServerArg *)Dz1Calloc(sizeof(Dz1TcpSerialServerArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerArg_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->config = config;
		__internal_ret->exceptionProc = exceptionProc;
		__internal_ret->exceptionArg = exceptionArg;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerArg_del(Dz1TcpSerialServerArg *p)
{
	if (p == NULL) return;
	if (p->config) Dz1TcpSerialServerConfig_del(p->config);
	Dz1Free(p);
}

