////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_arg.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpArg
Dz1InetFtpArg *Dz1InetFtpArg_new(str_t localCharSetName, 
								 Dz1InetFtpException func, 
								 void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpArg *__internal_ret = (Dz1InetFtpArg *)Dz1Calloc(sizeof(Dz1InetFtpArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpArg_delAndSetNull, (void *)&__internal_ret);
		
		if (localCharSetName && (__internal_ret->localCharSetName = dz1_built_in_str_clone(localCharSetName, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->func = func;
			__internal_ret->ptr = ptr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpArg_purge(Dz1InetFtpArg *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->localCharSetName);
}

void Dz1InetFtpArg_del(Dz1InetFtpArg *p)
{
	if (p == NULL) return;
	Dz1InetFtpArg_purge(p);
	Dz1Free(p);
}

// Dz1InetFtpArg
////////////////////////////////////////////////////////////////////////////////

