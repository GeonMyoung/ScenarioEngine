#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "dz1_syslog_timer.h"

Dz1SysLogTimer *Dz1SysLogTimer_new(s32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SysLogTimer *__internal_ret = (Dz1SysLogTimer *)Dz1Calloc(sizeof(Dz1SysLogTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SysLogTimer_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->id = id;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SysLogTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SysLogTimer_del(Dz1SysLogTimer *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1SysLogTimer_dump(Dz1SysLogTimer *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("id = "); Dz1s32_dump(&p->id, tab);
}

int Dz1SysLogTimer_cmp(Dz1SysLogTimer *a, Dz1SysLogTimer *b)
{
	int ret = 0;
	if ((ret = (int)((a->id) - (b->id))) != 0) return ret;
	else return ret;
}

