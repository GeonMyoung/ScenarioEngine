////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1TestScenarioArg.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1TestScenarioArg
Itsk00126V1TestScenarioArg *Itsk00126V1TestScenarioArg_new(void *tMain, 
														   Dz1Str testScenario, 
														   Itsk00126V1TestScenarioException exceptionProc, 
														   void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126V1TestScenarioArg *__internal_ret = (Itsk00126V1TestScenarioArg *)Dz1Calloc(sizeof(Itsk00126V1TestScenarioArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126V1TestScenarioArg_delAndSetNull, (void *)&__internal_ret);
		
		if (testScenario && (__internal_ret->testScenario = Dz1Str_clone(testScenario, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tMain = tMain;
			__internal_ret->exceptionProc = exceptionProc;
			__internal_ret->exceptionArg = exceptionArg;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126V1TestScenarioArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126V1TestScenarioArg_purge(Itsk00126V1TestScenarioArg *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testScenario);
}

void Itsk00126V1TestScenarioArg_del(Itsk00126V1TestScenarioArg *p)
{
	if (p == NULL) return;
	Itsk00126V1TestScenarioArg_purge(p);
	Dz1Free(p);
}

// Itsk00126V1TestScenarioArg
////////////////////////////////////////////////////////////////////////////////

