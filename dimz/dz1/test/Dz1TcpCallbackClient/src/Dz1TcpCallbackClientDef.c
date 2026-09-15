#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackClientDef.h"

Dz1TcpCallbackClientDef *Dz1TcpCallbackClientDef_new(u32_t dumb, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackClientDef *__internal_ret = (Dz1TcpCallbackClientDef *)Dz1Calloc(sizeof(Dz1TcpCallbackClientDef), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientDef_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->dumb = dumb;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientDef_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackClientDef_del(Dz1TcpCallbackClientDef *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

