//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialClientTimer.h"

Dz1TcpSerialClientTimer *Dz1TcpSerialClientTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialClientTimer *__internal_ret = (Dz1TcpSerialClientTimer *)Dz1Calloc(sizeof(Dz1TcpSerialClientTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientTimer_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->id = id;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialClientTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialClientTimer_del(Dz1TcpSerialClientTimer *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1TcpSerialClientTimer_dump(Dz1TcpSerialClientTimer *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab);
}

int Dz1TcpSerialClientTimer_cmp(Dz1TcpSerialClientTimer *a, Dz1TcpSerialClientTimer *b)
{
	int ret = 0;
	if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) return ret;
	else return ret;
}

