////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorMsgDefault
GitsnDsrcEmulatorMsgDefault *GitsnDsrcEmulatorMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorMsgDefault *__internal_ret = (GitsnDsrcEmulatorMsgDefault *)Dz1Calloc(sizeof(GitsnDsrcEmulatorMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorMsgDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDsrcEmulatorMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDsrcEmulatorMsgDefault_purge(GitsnDsrcEmulatorMsgDefault *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->dummy);
}

void GitsnDsrcEmulatorMsgDefault_del(GitsnDsrcEmulatorMsgDefault *p)
{
	if (p == NULL) return;
	GitsnDsrcEmulatorMsgDefault_purge(p);
	Dz1Free(p);
}

void GitsnDsrcEmulatorMsgDefault_dump(GitsnDsrcEmulatorMsgDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); 
	}
}
// GitsnDsrcEmulatorMsgDefault
////////////////////////////////////////////////////////////////////////////////

