////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827SocketReceiverDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SocketReceiverArg
ItsIso14827SocketReceiverArg *ItsIso14827SocketReceiverArg_new(u32_t parentQueueID, 
															   u32_t sid, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SocketReceiverArg *__internal_ret = (ItsIso14827SocketReceiverArg *)Dz1Calloc(sizeof(ItsIso14827SocketReceiverArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SocketReceiverArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->parentQueueID = parentQueueID;
		__internal_ret->sid = sid;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SocketReceiverArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SocketReceiverArg_purge(ItsIso14827SocketReceiverArg *p)
{
	if (p == NULL) return;
}

void ItsIso14827SocketReceiverArg_del(ItsIso14827SocketReceiverArg *p)
{
	if (p == NULL) return;
	ItsIso14827SocketReceiverArg_purge(p);
	Dz1Free(p);
}

void ItsIso14827SocketReceiverArg_dump(ItsIso14827SocketReceiverArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("parentQueueID = ")); Dz1u32_dump(&p->parentQueueID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sid = ")); Dz1u32_dump(&p->sid, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827SocketReceiverArg
////////////////////////////////////////////////////////////////////////////////

