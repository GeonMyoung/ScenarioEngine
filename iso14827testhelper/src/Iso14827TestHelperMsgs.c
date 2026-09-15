////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827TestHelperMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperMsgDefault
Iso14827TestHelperMsgDefault *Iso14827TestHelperMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperMsgDefault *__internal_ret = (Iso14827TestHelperMsgDefault *)Dz1Calloc(sizeof(Iso14827TestHelperMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperMsgDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827TestHelperMsgDefault_purge(Iso14827TestHelperMsgDefault *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->dummy);
}

void Iso14827TestHelperMsgDefault_del(Iso14827TestHelperMsgDefault *p)
{
	if (p == NULL) return;
	Iso14827TestHelperMsgDefault_purge(p);
	Dz1Free(p);
}

void Iso14827TestHelperMsgDefault_dump(Iso14827TestHelperMsgDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); 
	}
}
// Iso14827TestHelperMsgDefault
////////////////////////////////////////////////////////////////////////////////

