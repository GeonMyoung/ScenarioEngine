////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestScenarioArg.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestScenarioArg
TrafficSignalControllerTestScenarioArg *TrafficSignalControllerTestScenarioArg_new(void *tMain, 
																				   Dz1Str testScenario, 
																				   TrafficSignalControllerTestScenarioException exceptionProc, 
																				   void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerTestScenarioArg *__internal_ret = (TrafficSignalControllerTestScenarioArg *)Dz1Calloc(sizeof(TrafficSignalControllerTestScenarioArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestScenarioArg_delAndSetNull, (void *)&__internal_ret);
		
		if (testScenario && (__internal_ret->testScenario = Dz1Str_clone(testScenario, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tMain = tMain;
			__internal_ret->exceptionProc = exceptionProc;
			__internal_ret->exceptionArg = exceptionArg;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestScenarioArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void TrafficSignalControllerTestScenarioArg_purge(TrafficSignalControllerTestScenarioArg *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testScenario);
}

void TrafficSignalControllerTestScenarioArg_del(TrafficSignalControllerTestScenarioArg *p)
{
	if (p == NULL) return;
	TrafficSignalControllerTestScenarioArg_purge(p);
	Dz1Free(p);
}

// TrafficSignalControllerTestScenarioArg
////////////////////////////////////////////////////////////////////////////////

