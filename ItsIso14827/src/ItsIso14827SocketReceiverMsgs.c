////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827SocketReceiverMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIsoSocketReceiverReceived
ItsIsoSocketReceiverReceived *ItsIsoSocketReceiverReceived_new(ItsIso14827SessionKey *key, 
															   Dz1Binary *packet, 
															   time_t stamp, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIsoSocketReceiverReceived *__internal_ret = (ItsIsoSocketReceiverReceived *)Dz1Calloc(sizeof(ItsIsoSocketReceiverReceived), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIsoSocketReceiverReceived_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->key = key;
		__internal_ret->packet = packet;
		__internal_ret->stamp = stamp;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIsoSocketReceiverReceived_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIsoSocketReceiverReceived_purge(ItsIsoSocketReceiverReceived *p)
{
	if (p == NULL) return;
	ItsIso14827SessionKey_del(p->key);
	Dz1Binary_del(p->packet);
}

void ItsIsoSocketReceiverReceived_del(ItsIsoSocketReceiverReceived *p)
{
	if (p == NULL) return;
	ItsIsoSocketReceiverReceived_purge(p);
	Dz1Free(p);
}

void ItsIsoSocketReceiverReceived_dump(ItsIsoSocketReceiverReceived *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("key = ")); ItsIso14827SessionKey_dump(p->key, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("packet = ")); Dz1Binary_dump(p->packet, tab); 
		Dz1Thread_tprintf(tab, Dz1T("stamp = ")); time_dump(&p->stamp, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIsoSocketReceiverReceived
////////////////////////////////////////////////////////////////////////////////

