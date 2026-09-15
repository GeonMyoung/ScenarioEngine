#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackClientMsgs.h"

Dz1TcpCallbackClientMsgDefault *Dz1TcpCallbackClientMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackClientMsgDefault *__internal_ret = (Dz1TcpCallbackClientMsgDefault *)Dz1Calloc(sizeof(Dz1TcpCallbackClientMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientMsgDefault_delAndSetNull, (void *)&__internal_ret);

		if (dummy && (__internal_ret->dummy = Dz1u32_clone(dummy, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackClientMsgDefault_del(Dz1TcpCallbackClientMsgDefault *p)
{
	if (p == NULL) return;
	if (p->dummy) Dz1Free(p->dummy);
	Dz1Free(p);
}

void Dz1TcpCallbackClientMsgDefault_dump(Dz1TcpCallbackClientMsgDefault *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->dummy == NULL) Dz1Thread_printf("dummy = NULL\n");
	else {Dz1Thread_printf("dummy = "); Dz1u32_dump(p->dummy, tab); }
}

Dz1TcpCallbackClientMsgReceived *Dz1TcpCallbackClientMsgReceived_new(Dz1SockAddr *peer, 
																	 Dz1SockAddr *local, 
																	 Dz1Binary *packet, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackClientMsgReceived *__internal_ret = (Dz1TcpCallbackClientMsgReceived *)Dz1Calloc(sizeof(Dz1TcpCallbackClientMsgReceived), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientMsgReceived_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->packet = packet;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientMsgReceived_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackClientMsgReceived_del(Dz1TcpCallbackClientMsgReceived *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->packet) Dz1Binary_del(p->packet);
	Dz1Free(p);
}

void Dz1TcpCallbackClientMsgReceived_dump(Dz1TcpCallbackClientMsgReceived *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); }

	if (p->packet == NULL) Dz1Thread_tprintf(tab, "packet = NULL\n");
	else { Dz1Thread_tprintf(tab, "packet = "); Dz1Binary_dump(p->packet, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpCallbackClientMsgSent *Dz1TcpCallbackClientMsgSent_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackClientMsgSent *__internal_ret = (Dz1TcpCallbackClientMsgSent *)Dz1Calloc(sizeof(Dz1TcpCallbackClientMsgSent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientMsgSent_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientMsgSent_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackClientMsgSent_del(Dz1TcpCallbackClientMsgSent *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void Dz1TcpCallbackClientMsgSent_dump(Dz1TcpCallbackClientMsgSent *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

