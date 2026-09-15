////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorArg.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorArg
GitsnDsrcEmulatorArg *GitsnDsrcEmulatorArg_new(GitsnDsrcEmulatorException exceptionProc, 
											   void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorArg *__internal_ret = (GitsnDsrcEmulatorArg *)Dz1Calloc(sizeof(GitsnDsrcEmulatorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->exceptionProc = exceptionProc;
		__internal_ret->exceptionArg = exceptionArg;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDsrcEmulatorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDsrcEmulatorArg_purge(GitsnDsrcEmulatorArg *p)
{
	if (p == NULL) return;
}

void GitsnDsrcEmulatorArg_del(GitsnDsrcEmulatorArg *p)
{
	if (p == NULL) return;
	GitsnDsrcEmulatorArg_purge(p);
	Dz1Free(p);
}

// GitsnDsrcEmulatorArg
////////////////////////////////////////////////////////////////////////////////

