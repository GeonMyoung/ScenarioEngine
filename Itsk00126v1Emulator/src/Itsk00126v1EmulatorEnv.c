////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1EmulatorEnv.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ClientSession
Itsk00126v1ClientSession *Itsk00126v1ClientSession_new(Dz1SockAddr *peer, 
													   Dz1SockAddr *local, 
													   Dz1TcpClientSocket *sock, 
													   Dz1ElasticBuf *rx_buf, 
													   Dz1Stream *rx_stream, 
													   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v1ClientSession *__internal_ret = (Itsk00126v1ClientSession *)Dz1Calloc(sizeof(Itsk00126v1ClientSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v1ClientSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1ClientSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126v1ClientSession_purge(Itsk00126v1ClientSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void Itsk00126v1ClientSession_del(Itsk00126v1ClientSession *p)
{
	if (p == NULL) return;
	Itsk00126v1ClientSession_purge(p);
	Dz1Free(p);
}

void Itsk00126v1ClientSession_dump(Itsk00126v1ClientSession *p, int tab)
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
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("sock = %p\n"), p->sock);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("rx_buf = %p\n"), p->rx_buf);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("rx_stream = %p\n"), p->rx_stream);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("tx_fifo = ")); Dz1SockUtilTxFifo_dump(p->tx_fifo, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Itsk00126v1ClientSession_cmp(Itsk00126v1ClientSession *a, Itsk00126v1ClientSession *b)
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
	return ret;
}
// Itsk00126v1ClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ServerSession
Itsk00126v1ServerSession *Itsk00126v1ServerSession_new(u32_t acceptor, 
													   Dz1SockAddr *peer, 
													   Dz1SockAddr *local, 
													   Dz1TcpClientSocket *sock, 
													   Dz1ElasticBuf *rx_buf, 
													   Dz1Stream *rx_stream, 
													   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v1ServerSession *__internal_ret = (Itsk00126v1ServerSession *)Dz1Calloc(sizeof(Itsk00126v1ServerSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v1ServerSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->acceptor = acceptor;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1ServerSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126v1ServerSession_purge(Itsk00126v1ServerSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void Itsk00126v1ServerSession_del(Itsk00126v1ServerSession *p)
{
	if (p == NULL) return;
	Itsk00126v1ServerSession_purge(p);
	Dz1Free(p);
}

void Itsk00126v1ServerSession_dump(Itsk00126v1ServerSession *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("acceptor = ")); Dz1u32_dump(&p->acceptor, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("sock = %p\n"), p->sock);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("rx_buf = %p\n"), p->rx_buf);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("rx_stream = %p\n"), p->rx_stream);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("tx_fifo = ")); Dz1SockUtilTxFifo_dump(p->tx_fifo, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Itsk00126v1ServerSession_cmp(Itsk00126v1ServerSession *a, Itsk00126v1ServerSession *b)
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
	return ret;
}
// Itsk00126v1ServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1SessionPresent
static struct Itsk00126v1SessionPresentMapA
{
	str_t str;
	Itsk00126v1SessionPresent v;
} Itsk00126v1SessionPresentMapA[] =
{
	{ (char *)"client", Itsk00126v1SessionPresent_client },
	{ (char *)"server", Itsk00126v1SessionPresent_server },
	{ NULL, Itsk00126v1SessionPresent_max }
};

str_t Itsk00126v1SessionPresentStrA(Itsk00126v1SessionPresent v)
{
	struct Itsk00126v1SessionPresentMapA *i = NULL;
	for (i = Itsk00126v1SessionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v1SessionPresent Itsk00126v1SessionPresentFromStrA(str_t str)
{
	struct Itsk00126v1SessionPresentMapA *i = NULL;
	for (i = Itsk00126v1SessionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v1SessionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v1SessionPresentMapW
{
	wstr_t str;
	Itsk00126v1SessionPresent v;
} Itsk00126v1SessionPresentMapW[] =
{
	{ (wchar_t *)L"client", Itsk00126v1SessionPresent_client },
	{ (wchar_t *)L"server", Itsk00126v1SessionPresent_server },
	{ NULL, Itsk00126v1SessionPresent_max }
};

wstr_t Itsk00126v1SessionPresentStrW(Itsk00126v1SessionPresent v)
{
	struct Itsk00126v1SessionPresentMapW *i = NULL;
	for (i = Itsk00126v1SessionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v1SessionPresent Itsk00126v1SessionPresentFromStrW(wstr_t str)
{
	struct Itsk00126v1SessionPresentMapW *i = NULL;
	for (i = Itsk00126v1SessionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v1SessionPresent_max;
}
#endif // UNIX_SYSTEM

Itsk00126v1SessionPresent *Itsk00126v1SessionPresent_new(Itsk00126v1SessionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v1SessionPresent *__internal_ret = (Itsk00126v1SessionPresent *)Dz1Calloc(sizeof(Itsk00126v1SessionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v1SessionPresent_dump(Itsk00126v1SessionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v1SessionPresentStr(*v));
}
// Itsk00126v1SessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1Session
Itsk00126v1Session *Itsk00126v1Session_new(Itsk00126v1SessionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v1Session *ret = (Itsk00126v1Session *)Dz1Calloc(sizeof(Itsk00126v1Session), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v1Session_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Itsk00126v1SessionPresent_client:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client = (Itsk00126v1ClientSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v1SessionPresent_server:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server = (Itsk00126v1ServerSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v1SessionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1Session_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Itsk00126v1Session_purge(Itsk00126v1Session *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Itsk00126v1SessionPresent_client:
		Itsk00126v1ClientSession_del(p->x.client);
		break;
	case Itsk00126v1SessionPresent_server:
		Itsk00126v1ServerSession_del(p->x.server);
		break;
	default:
		break;
	}
}

void Itsk00126v1Session_del(Itsk00126v1Session *p)
{
	if (!p) return;
	Itsk00126v1Session_purge(p);
	Dz1Free(p);
}

void Itsk00126v1Session_dump(Itsk00126v1Session *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Itsk00126v1SessionPresent_client:
		Dz1Thread_printf(Dz1T("client = ")); Itsk00126v1ClientSession_dump(p->x.client, tab); 
		break;
	case Itsk00126v1SessionPresent_server:
		Dz1Thread_printf(Dz1T("server = ")); Itsk00126v1ServerSession_dump(p->x.server, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Itsk00126v1Session
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorEnv
Itsk00126V1EmulatorEnv *Itsk00126V1EmulatorEnv_new(void *tSelf, 
												   Dz1JsonSpec *spec, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126V1EmulatorEnv *__internal_ret = (Itsk00126V1EmulatorEnv *)Dz1Calloc(sizeof(Itsk00126V1EmulatorEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126V1EmulatorEnv_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tSelf = tSelf;
		__internal_ret->spec = spec;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126V1EmulatorEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126V1EmulatorEnv_purge(Itsk00126V1EmulatorEnv *p)
{
	if (p == NULL) return;
	Dz1JsonSpec_del(p->spec);
	Itsk00126v1Session_del(p->session);
	Dz1Str_del(p->local_center_id);
}

void Itsk00126V1EmulatorEnv_del(Itsk00126V1EmulatorEnv *p)
{
	if (p == NULL) return;
	Itsk00126V1EmulatorEnv_purge(p);
	Dz1Free(p);
}

void Itsk00126V1EmulatorEnv_dump(Itsk00126V1EmulatorEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("spec = ")); Dz1JsonSpec_dump(p->spec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("session.")); Itsk00126v1Session_dump(p->session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("local_center_id = ")); Dz1Str_dump(p->local_center_id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126V1EmulatorEnv
////////////////////////////////////////////////////////////////////////////////

