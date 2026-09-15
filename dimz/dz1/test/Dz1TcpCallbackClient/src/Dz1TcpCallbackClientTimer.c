#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackClientTimer.h"

Dz1TcpCallbackClientTimer *Dz1TcpCallbackClientTimer_new(u32_t id, 
														 Dz1SockAddr *peer, 
														 Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackClientTimer *__internal_ret = (Dz1TcpCallbackClientTimer *)Dz1Calloc(sizeof(Dz1TcpCallbackClientTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientTimer_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->id = id;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackClientTimer_del(Dz1TcpCallbackClientTimer *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void Dz1TcpCallbackClientTimer_dump(Dz1TcpCallbackClientTimer *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "id = "); Dz1u32_dump(&p->id, tab);

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1TcpCallbackClientTimer_cmp(Dz1TcpCallbackClientTimer *a, Dz1TcpCallbackClientTimer *b)
{
	int ret = 0;
	if ((ret = (int)((a->id) - (b->id))) != 0) return ret;
	else if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) return ret;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) return ret;
	else return ret;
}

