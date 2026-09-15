#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackServerMsgs.h"

Dz1TcpCallbackServerMsgDefault *Dz1TcpCallbackServerMsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackServerMsgDefault *__internal_ret = (Dz1TcpCallbackServerMsgDefault *)Dz1Calloc(sizeof(Dz1TcpCallbackServerMsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerMsgDefault_delAndSetNull, (void *)&__internal_ret);

		if (dummy && (__internal_ret->dummy = Dz1u32_clone(dummy, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackServerMsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackServerMsgDefault_del(Dz1TcpCallbackServerMsgDefault *p)
{
	if (p == NULL) return;
	if (p->dummy) Dz1Free(p->dummy);
	Dz1Free(p);
}

void Dz1TcpCallbackServerMsgDefault_dump(Dz1TcpCallbackServerMsgDefault *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->dummy == NULL) Dz1Thread_printf("dummy = NULL\n");
	else {Dz1Thread_printf("dummy = "); Dz1u32_dump(p->dummy, tab); }
}

Dz1TcpCallbackServerMsgConnected *Dz1TcpCallbackServerMsgConnected_new(Dz1SockAddr *peer, 
																	   Dz1SockAddr *local, 
																	   Dz1TcpClientSocket *sock, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackServerMsgConnected *__internal_ret = (Dz1TcpCallbackServerMsgConnected *)Dz1Calloc(sizeof(Dz1TcpCallbackServerMsgConnected), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerMsgConnected_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackServerMsgConnected_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackServerMsgConnected_del(Dz1TcpCallbackServerMsgConnected *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->sock) Dz1TcpClientSocket_del(p->sock);
	Dz1Free(p);
}

void Dz1TcpCallbackServerMsgConnected_dump(Dz1TcpCallbackServerMsgConnected *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	if (p->sock == NULL) Dz1Thread_tprintf(tab, "sock = NULL\n");
	else { Dz1Thread_tprintf(tab, "sock = %p\n", p->sock); /* no way to dump */ }

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpCallbackServerMsgReceived *Dz1TcpCallbackServerMsgReceived_new(Dz1SockAddr *peer, 
																	 Dz1SockAddr *local, 
																	 Dz1Binary *packet, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackServerMsgReceived *__internal_ret = (Dz1TcpCallbackServerMsgReceived *)Dz1Calloc(sizeof(Dz1TcpCallbackServerMsgReceived), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerMsgReceived_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->packet = packet;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackServerMsgReceived_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackServerMsgReceived_del(Dz1TcpCallbackServerMsgReceived *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->packet) Dz1Binary_del(p->packet);
	Dz1Free(p);
}

void Dz1TcpCallbackServerMsgReceived_dump(Dz1TcpCallbackServerMsgReceived *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	if (p->packet == NULL) Dz1Thread_tprintf(tab, "packet = NULL\n");
	else { Dz1Thread_tprintf(tab, "packet = "); Dz1Binary_dump(p->packet, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpCallbackServerMsgSent *Dz1TcpCallbackServerMsgSent_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackServerMsgSent *__internal_ret = (Dz1TcpCallbackServerMsgSent *)Dz1Calloc(sizeof(Dz1TcpCallbackServerMsgSent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerMsgSent_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackServerMsgSent_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackServerMsgSent_del(Dz1TcpCallbackServerMsgSent *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void Dz1TcpCallbackServerMsgSent_dump(Dz1TcpCallbackServerMsgSent *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, "}\n");
}

