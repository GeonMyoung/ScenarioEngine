////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorMsgDefault
ITSK001442EmulatorMsgDefault *ITSK001442EmulatorMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001442EmulatorMsgDefault *__internal_ret = (ITSK001442EmulatorMsgDefault *)Dz1Calloc(sizeof(ITSK001442EmulatorMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001442EmulatorMsgDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001442EmulatorMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001442EmulatorMsgDefault_purge(ITSK001442EmulatorMsgDefault *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->dummy);
}

void ITSK001442EmulatorMsgDefault_del(ITSK001442EmulatorMsgDefault *p)
{
	if (p == NULL) return;
	ITSK001442EmulatorMsgDefault_purge(p);
	Dz1Free(p);
}

void ITSK001442EmulatorMsgDefault_dump(ITSK001442EmulatorMsgDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); 
	}
}
// ITSK001442EmulatorMsgDefault
////////////////////////////////////////////////////////////////////////////////

