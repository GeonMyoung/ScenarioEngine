//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerSerialIOMsgs.h"

Dz1TcpSerialServerMsgRecv *Dz1TcpSerialServerMsgRecv_new(Dz1SockAddr *peer, 
														 Dz1SockAddr *local, 
														 Dz1Binary *stream, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerMsgRecv *__internal_ret = (Dz1TcpSerialServerMsgRecv *)Dz1Calloc(sizeof(Dz1TcpSerialServerMsgRecv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgRecv_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->stream = stream;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerMsgRecv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerMsgRecv_del(Dz1TcpSerialServerMsgRecv *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->stream) Dz1Binary_del(p->stream);
	Dz1Free(p);
}

void Dz1TcpSerialServerMsgRecv_dump(Dz1TcpSerialServerMsgRecv *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, Dz1T("peer = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, Dz1T("local = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	if (p->stream == NULL) Dz1Thread_tprintf(tab, Dz1T("stream = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("stream = ")); Dz1Binary_dump(p->stream, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialServerMsgPin *Dz1TcpSerialServerMsgPin_new(Dz1SockAddr *peer, 
													   Dz1SockAddr *local, 
													   Dz1SerialPinState v, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerMsgPin *__internal_ret = (Dz1TcpSerialServerMsgPin *)Dz1Calloc(sizeof(Dz1TcpSerialServerMsgPin), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgPin_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->v = v;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerMsgPin_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerMsgPin_del(Dz1TcpSerialServerMsgPin *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void Dz1TcpSerialServerMsgPin_dump(Dz1TcpSerialServerMsgPin *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, Dz1T("peer = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, Dz1T("local = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("v = %s(%d)\n"), Dz1SerialPinStateStr(p->v), p->v);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialServerMsgException *Dz1TcpSerialServerMsgException_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerMsgException *__internal_ret = (Dz1TcpSerialServerMsgException *)Dz1Calloc(sizeof(Dz1TcpSerialServerMsgException), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgException_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerMsgException_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerMsgException_del(Dz1TcpSerialServerMsgException *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void Dz1TcpSerialServerMsgException_dump(Dz1TcpSerialServerMsgException *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, Dz1T("peer = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, Dz1T("local = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

