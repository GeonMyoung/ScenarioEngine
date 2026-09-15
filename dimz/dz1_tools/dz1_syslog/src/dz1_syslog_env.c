#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "dz1_syslog_env.h"

Dz1SysLogEnv *Dz1SysLogEnv_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SysLogEnv *__internal_ret = (Dz1SysLogEnv *)Dz1Calloc(sizeof(Dz1SysLogEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SysLogEnv_delAndSetNull, (void *)&__internal_ret);

		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SysLogEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1SysLogEnv_del(Dz1SysLogEnv *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1SysLogEnv_dump(Dz1SysLogEnv *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("dummy = "); Dz1s32_dump(&p->dummy, tab);
}

