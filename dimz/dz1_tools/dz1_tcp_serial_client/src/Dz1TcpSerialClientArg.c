//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialClientArg.h"

Dz1TcpSerialClientArg *Dz1TcpSerialClientArg_new(Dz1SockAddr *serverAddr, 
												 Dz1TcpSerialClientException exceptionProc, 
												 void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientArg *__internal_ret = (Dz1TcpSerialClientArg *)Dz1Calloc(sizeof(Dz1TcpSerialClientArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientArg_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->serverAddr = serverAddr;
		__internal_ret->exceptionProc = exceptionProc;
		__internal_ret->exceptionArg = exceptionArg;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientArg_del(Dz1TcpSerialClientArg *p)
{
	if (p == NULL) return;
	if (p->serverAddr) Dz1SockAddr_del(p->serverAddr);
	Dz1Free(p);
}

