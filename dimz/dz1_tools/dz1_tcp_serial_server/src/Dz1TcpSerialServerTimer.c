//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerTimer.h"

Dz1TcpSerialServerTimer *Dz1TcpSerialServerTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerTimer *__internal_ret = (Dz1TcpSerialServerTimer *)Dz1Calloc(sizeof(Dz1TcpSerialServerTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerTimer_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->id = id;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerTimer_del(Dz1TcpSerialServerTimer *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialServerTimer_dump(Dz1TcpSerialServerTimer *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab);
}

int Dz1TcpSerialServerTimer_cmp(Dz1TcpSerialServerTimer *a, Dz1TcpSerialServerTimer *b)
{
	int ret = 0;
	if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) return ret;
	else return ret;
}

