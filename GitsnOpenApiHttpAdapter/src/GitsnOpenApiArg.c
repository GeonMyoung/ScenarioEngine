////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnOpenApiArg.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiArg
GitsnOpenApiArg *GitsnOpenApiArg_new(Dz1SockAddr *listen_addr, 
									 str_t servant_name_u8, 
									 GitsnOpenApiCallback http_cb, 
									 void *http_cb_ptr, 
									 GitsnOpenApiException exceptionProc, 
									 void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiArg *__internal_ret = (GitsnOpenApiArg *)Dz1Calloc(sizeof(GitsnOpenApiArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiArg_delAndSetNull, (void *)&__internal_ret);
		
		if (servant_name_u8 && (__internal_ret->servant_name_u8 = dz1_built_in_str_clone(servant_name_u8, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->listen_addr = listen_addr;
			__internal_ret->http_cb = http_cb;
			__internal_ret->http_cb_ptr = http_cb_ptr;
			__internal_ret->exceptionProc = exceptionProc;
			__internal_ret->exceptionArg = exceptionArg;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnOpenApiArg_purge(GitsnOpenApiArg *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->listen_addr);
	dz1_built_in_str_del(p->servant_name_u8);
}

void GitsnOpenApiArg_del(GitsnOpenApiArg *p)
{
	if (p == NULL) return;
	GitsnOpenApiArg_purge(p);
	Dz1Free(p);
}

// GitsnOpenApiArg
////////////////////////////////////////////////////////////////////////////////

