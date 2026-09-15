////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestScenarioMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestScenarioMsgDefault
TrafficSignalControllerTestScenarioMsgDefault *TrafficSignalControllerTestScenarioMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerTestScenarioMsgDefault *__internal_ret = (TrafficSignalControllerTestScenarioMsgDefault *)Dz1Calloc(sizeof(TrafficSignalControllerTestScenarioMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestScenarioMsgDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestScenarioMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void TrafficSignalControllerTestScenarioMsgDefault_purge(TrafficSignalControllerTestScenarioMsgDefault *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->dummy);
}

void TrafficSignalControllerTestScenarioMsgDefault_del(TrafficSignalControllerTestScenarioMsgDefault *p)
{
	if (p == NULL) return;
	TrafficSignalControllerTestScenarioMsgDefault_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerTestScenarioMsgDefault_dump(TrafficSignalControllerTestScenarioMsgDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); 
	}
}
// TrafficSignalControllerTestScenarioMsgDefault
////////////////////////////////////////////////////////////////////////////////

