////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDSRCMsgTestScenarioMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestScenarioMsgDefault
GitsnDSRCMsgTestScenarioMsgDefault *GitsnDSRCMsgTestScenarioMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgTestScenarioMsgDefault *__internal_ret = (GitsnDSRCMsgTestScenarioMsgDefault *)Dz1Calloc(sizeof(GitsnDSRCMsgTestScenarioMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgTestScenarioMsgDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgTestScenarioMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDSRCMsgTestScenarioMsgDefault_purge(GitsnDSRCMsgTestScenarioMsgDefault *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->dummy);
}

void GitsnDSRCMsgTestScenarioMsgDefault_del(GitsnDSRCMsgTestScenarioMsgDefault *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgTestScenarioMsgDefault_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgTestScenarioMsgDefault_dump(GitsnDSRCMsgTestScenarioMsgDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); 
	}
}
// GitsnDSRCMsgTestScenarioMsgDefault
////////////////////////////////////////////////////////////////////////////////

