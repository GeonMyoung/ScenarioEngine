////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_timer.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTimer
Dz1InetFtpTimer *Dz1InetFtpTimer_new(Dz1SockAddr *peer, 
									 Dz1SockAddr *local, 
									 u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpTimer *__internal_ret = (Dz1InetFtpTimer *)Dz1Calloc(sizeof(Dz1InetFtpTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpTimer_purge(Dz1InetFtpTimer *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
}

void Dz1InetFtpTimer_del(Dz1InetFtpTimer *p)
{
	if (p == NULL) return;
	Dz1InetFtpTimer_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpTimer_dump(Dz1InetFtpTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); 
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1InetFtpTimer_cmp(Dz1InetFtpTimer *a, Dz1InetFtpTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->peer == NULL && b->peer == NULL) ret = 0;
	else if (a->peer == NULL /*&& b->peer != NULL*/) ret = -1;
	else if (/*a->peer != NULL &&*/ b->peer == NULL) ret = 1;
	else if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) { }
	else if (a->local == NULL && b->local == NULL) ret = 0;
	else if (a->local == NULL /*&& b->local != NULL*/) ret = -1;
	else if (/*a->local != NULL &&*/ b->local == NULL) ret = 1;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// Dz1InetFtpTimer
////////////////////////////////////////////////////////////////////////////////

