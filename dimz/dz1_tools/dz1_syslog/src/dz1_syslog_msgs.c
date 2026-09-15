#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "dz1_syslog_msgs.h"

Dz1SysLogMsg *Dz1SysLogMsg_new(u32_t dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SysLogMsg *__internal_ret = (Dz1SysLogMsg *)Dz1Calloc(sizeof(Dz1SysLogMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SysLogMsg_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SysLogMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SysLogMsg_del(Dz1SysLogMsg *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1SysLogMsg_dump(Dz1SysLogMsg *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("dummy = "); Dz1u32_dump(&p->dummy, tab);
}

