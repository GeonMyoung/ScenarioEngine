#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "dz1_syslog_arg.h"

Dz1SysLogArg *Dz1SysLogArg_new(s32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SysLogArg *__internal_ret = (Dz1SysLogArg *)Dz1Calloc(sizeof(Dz1SysLogArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SysLogArg_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SysLogArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SysLogArg_del(Dz1SysLogArg *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

