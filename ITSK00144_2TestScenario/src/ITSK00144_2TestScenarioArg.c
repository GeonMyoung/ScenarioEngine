////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestScenarioArg.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442TestScenarioArg
ITSK001442TestScenarioArg *ITSK001442TestScenarioArg_new(void *tMain, 
														 Dz1Str testScenario, 
														 ITSK001442TestScenarioException exceptionProc, 
														 void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001442TestScenarioArg *__internal_ret = (ITSK001442TestScenarioArg *)Dz1Calloc(sizeof(ITSK001442TestScenarioArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001442TestScenarioArg_delAndSetNull, (void *)&__internal_ret);
		
		if (testScenario && (__internal_ret->testScenario = Dz1Str_clone(testScenario, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tMain = tMain;
			__internal_ret->exceptionProc = exceptionProc;
			__internal_ret->exceptionArg = exceptionArg;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001442TestScenarioArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001442TestScenarioArg_purge(ITSK001442TestScenarioArg *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testScenario);
}

void ITSK001442TestScenarioArg_del(ITSK001442TestScenarioArg *p)
{
	if (p == NULL) return;
	ITSK001442TestScenarioArg_purge(p);
	Dz1Free(p);
}

// ITSK001442TestScenarioArg
////////////////////////////////////////////////////////////////////////////////

