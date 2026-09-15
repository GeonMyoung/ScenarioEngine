////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineMsgDefault
ScenarioEngineMsgDefault *ScenarioEngineMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ScenarioEngineMsgDefault *__internal_ret = (ScenarioEngineMsgDefault *)Dz1Calloc(sizeof(ScenarioEngineMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ScenarioEngineMsgDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ScenarioEngineMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ScenarioEngineMsgDefault_purge(ScenarioEngineMsgDefault *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->dummy);
}

void ScenarioEngineMsgDefault_del(ScenarioEngineMsgDefault *p)
{
	if (p == NULL) return;
	ScenarioEngineMsgDefault_purge(p);
	Dz1Free(p);
}

void ScenarioEngineMsgDefault_dump(ScenarioEngineMsgDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); 
	}
}
// ScenarioEngineMsgDefault
////////////////////////////////////////////////////////////////////////////////

