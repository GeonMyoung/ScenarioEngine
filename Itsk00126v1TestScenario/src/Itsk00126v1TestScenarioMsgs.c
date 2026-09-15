////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1TestScenarioMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1TestScenarioMsgDefault
Itsk00126V1TestScenarioMsgDefault *Itsk00126V1TestScenarioMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126V1TestScenarioMsgDefault *__internal_ret = (Itsk00126V1TestScenarioMsgDefault *)Dz1Calloc(sizeof(Itsk00126V1TestScenarioMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126V1TestScenarioMsgDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126V1TestScenarioMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126V1TestScenarioMsgDefault_purge(Itsk00126V1TestScenarioMsgDefault *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->dummy);
}

void Itsk00126V1TestScenarioMsgDefault_del(Itsk00126V1TestScenarioMsgDefault *p)
{
	if (p == NULL) return;
	Itsk00126V1TestScenarioMsgDefault_purge(p);
	Dz1Free(p);
}

void Itsk00126V1TestScenarioMsgDefault_dump(Itsk00126V1TestScenarioMsgDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); 
	}
}
// Itsk00126V1TestScenarioMsgDefault
////////////////////////////////////////////////////////////////////////////////

