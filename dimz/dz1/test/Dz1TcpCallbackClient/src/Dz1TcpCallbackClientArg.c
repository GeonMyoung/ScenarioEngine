#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackClientArg.h"

Dz1TcpCallbackClientArg *Dz1TcpCallbackClientArg_new(Dz1TcpCallbackClientException exceptionProc, void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackClientArg *__internal_ret = (Dz1TcpCallbackClientArg *)Dz1Calloc(sizeof(Dz1TcpCallbackClientArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientArg_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->exceptionProc = exceptionProc;
		__internal_ret->exceptionArg = exceptionArg;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackClientArg_del(Dz1TcpCallbackClientArg *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

