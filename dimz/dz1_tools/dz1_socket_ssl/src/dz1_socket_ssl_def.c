////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_socket_ssl_def.h"

////////////////////////////////////////////////////////////////////////////////
// dz1_socket_ssl
dz1_socket_ssl *dz1_socket_ssl_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	dz1_socket_ssl *__internal_ret = (dz1_socket_ssl *)Dz1Calloc(sizeof(dz1_socket_ssl), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(dz1_socket_ssl_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (dz1_socket_ssl_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void dz1_socket_ssl_purge(dz1_socket_ssl *p)
{
	if (p == NULL) return;
}

void dz1_socket_ssl_del(dz1_socket_ssl *p)
{
	if (p == NULL) return;
	dz1_socket_ssl_purge(p);
	Dz1Free(p);
}

// dz1_socket_ssl
////////////////////////////////////////////////////////////////////////////////

