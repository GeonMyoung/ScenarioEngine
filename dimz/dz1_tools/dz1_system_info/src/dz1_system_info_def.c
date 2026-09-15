////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_system_info_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SystemInfo
Dz1SystemInfo *Dz1SystemInfo_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SystemInfo *__internal_ret = (Dz1SystemInfo *)Dz1Calloc(sizeof(Dz1SystemInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SystemInfo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SystemInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SystemInfo_purge(Dz1SystemInfo *p)
{
	if (p == NULL) return;
}

void Dz1SystemInfo_del(Dz1SystemInfo *p)
{
	if (p == NULL) return;
	Dz1SystemInfo_purge(p);
	Dz1Free(p);
}

// Dz1SystemInfo
////////////////////////////////////////////////////////////////////////////////

