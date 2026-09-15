////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Arg.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Arg
ItsIso14827Arg *ItsIso14827Arg_new(ItsIso14827Exception exceptionProc, 
								   void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827Arg *__internal_ret = (ItsIso14827Arg *)Dz1Calloc(sizeof(ItsIso14827Arg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827Arg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->exceptionProc = exceptionProc;
		__internal_ret->exceptionArg = exceptionArg;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827Arg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827Arg_purge(ItsIso14827Arg *p)
{
	if (p == NULL) return;
}

void ItsIso14827Arg_del(ItsIso14827Arg *p)
{
	if (p == NULL) return;
	ItsIso14827Arg_purge(p);
	Dz1Free(p);
}

// ItsIso14827Arg
////////////////////////////////////////////////////////////////////////////////

