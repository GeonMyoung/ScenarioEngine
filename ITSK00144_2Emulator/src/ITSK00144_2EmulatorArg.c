////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorArg.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorArg
ITSK001442EmulatorArg *ITSK001442EmulatorArg_new(ITSK001442EmulatorException exceptionProc, 
												 void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001442EmulatorArg *__internal_ret = (ITSK001442EmulatorArg *)Dz1Calloc(sizeof(ITSK001442EmulatorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001442EmulatorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->exceptionProc = exceptionProc;
		__internal_ret->exceptionArg = exceptionArg;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001442EmulatorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001442EmulatorArg_purge(ITSK001442EmulatorArg *p)
{
	if (p == NULL) return;
}

void ITSK001442EmulatorArg_del(ITSK001442EmulatorArg *p)
{
	if (p == NULL) return;
	ITSK001442EmulatorArg_purge(p);
	Dz1Free(p);
}

// ITSK001442EmulatorArg
////////////////////////////////////////////////////////////////////////////////

