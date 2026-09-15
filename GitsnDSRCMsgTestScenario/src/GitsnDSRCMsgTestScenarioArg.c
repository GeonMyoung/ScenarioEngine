////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDSRCMsgTestScenarioArg.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestScenarioArg
GitsnDSRCMsgTestScenarioArg *GitsnDSRCMsgTestScenarioArg_new(void *tMain, 
															 Dz1Str testScenario, 
															 GitsnDSRCMsgTestScenarioException exceptionProc, 
															 void *exceptionArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgTestScenarioArg *__internal_ret = (GitsnDSRCMsgTestScenarioArg *)Dz1Calloc(sizeof(GitsnDSRCMsgTestScenarioArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgTestScenarioArg_delAndSetNull, (void *)&__internal_ret);
		
		if (testScenario && (__internal_ret->testScenario = Dz1Str_clone(testScenario, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tMain = tMain;
			__internal_ret->exceptionProc = exceptionProc;
			__internal_ret->exceptionArg = exceptionArg;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgTestScenarioArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDSRCMsgTestScenarioArg_purge(GitsnDSRCMsgTestScenarioArg *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testScenario);
}

void GitsnDSRCMsgTestScenarioArg_del(GitsnDSRCMsgTestScenarioArg *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgTestScenarioArg_purge(p);
	Dz1Free(p);
}

// GitsnDSRCMsgTestScenarioArg
////////////////////////////////////////////////////////////////////////////////

