////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorDef
GitsnDsrcEmulatorDef *GitsnDsrcEmulatorDef_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorDef *__internal_ret = (GitsnDsrcEmulatorDef *)Dz1Calloc(sizeof(GitsnDsrcEmulatorDef), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorDef_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDsrcEmulatorDef_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDsrcEmulatorDef_purge(GitsnDsrcEmulatorDef *p)
{
	if (p == NULL) return;
}

void GitsnDsrcEmulatorDef_del(GitsnDsrcEmulatorDef *p)
{
	if (p == NULL) return;
	GitsnDsrcEmulatorDef_purge(p);
	Dz1Free(p);
}

// GitsnDsrcEmulatorDef
////////////////////////////////////////////////////////////////////////////////

