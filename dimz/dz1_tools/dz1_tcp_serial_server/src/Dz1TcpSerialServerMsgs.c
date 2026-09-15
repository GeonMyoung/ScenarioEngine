//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerMsgs.h"

Dz1TcpSerialServerMsgDefault *Dz1TcpSerialServerMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerMsgDefault *__internal_ret = (Dz1TcpSerialServerMsgDefault *)Dz1Calloc(sizeof(Dz1TcpSerialServerMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgDefault_delAndSetNull, (void *)&__internal_ret);

		if (dummy && (__internal_ret->dummy = Dz1u32_clone(dummy, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerMsgDefault_del(Dz1TcpSerialServerMsgDefault *p)
{
	if (p == NULL) return;
	if (p->dummy) Dz1Free(p->dummy);
	Dz1Free(p);
}

void Dz1TcpSerialServerMsgDefault_dump(Dz1TcpSerialServerMsgDefault *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	if (p->dummy == NULL) Dz1Thread_printf(Dz1T("dummy = NULL\n"));
	else {Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); }
}

