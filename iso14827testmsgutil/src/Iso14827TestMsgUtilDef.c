////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827TestMsgUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestMsgUtil
Iso14827TestMsgUtil *Iso14827TestMsgUtil_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestMsgUtil *__internal_ret = (Iso14827TestMsgUtil *)Dz1Calloc(sizeof(Iso14827TestMsgUtil), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestMsgUtil_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestMsgUtil_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827TestMsgUtil_purge(Iso14827TestMsgUtil *p)
{
	if (p == NULL) return;
}

void Iso14827TestMsgUtil_del(Iso14827TestMsgUtil *p)
{
	if (p == NULL) return;
	Iso14827TestMsgUtil_purge(p);
	Dz1Free(p);
}

// Iso14827TestMsgUtil
////////////////////////////////////////////////////////////////////////////////

