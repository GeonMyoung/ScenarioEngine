////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorEnv.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ClientSession
ITSK00144_2ClientSession *ITSK00144_2ClientSession_new(Dz1SockAddr *peer, 
													   Dz1SockAddr *local, 
													   Dz1TcpClientSocket *sock, 
													   Dz1ElasticBuf *rx_buf, 
													   Dz1Stream *rx_stream, 
													   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ClientSession *__internal_ret = (ITSK00144_2ClientSession *)Dz1Calloc(sizeof(ITSK00144_2ClientSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ClientSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ClientSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK00144_2ClientSession_purge(ITSK00144_2ClientSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void ITSK00144_2ClientSession_del(ITSK00144_2ClientSession *p)
{
	if (p == NULL) return;
	ITSK00144_2ClientSession_purge(p);
	Dz1Free(p);
}

void ITSK00144_2ClientSession_dump(ITSK00144_2ClientSession *p, int tab)
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
int ITSK00144_2ClientSession_cmp(ITSK00144_2ClientSession *a, ITSK00144_2ClientSession *b)
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
// ITSK00144_2ClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ServerSession
ITSK00144_2ServerSession *ITSK00144_2ServerSession_new(u32_t acceptor, 
													   Dz1SockAddr *peer, 
													   Dz1SockAddr *local, 
													   Dz1TcpClientSocket *sock, 
													   Dz1ElasticBuf *rx_buf, 
													   Dz1Stream *rx_stream, 
													   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ServerSession *__internal_ret = (ITSK00144_2ServerSession *)Dz1Calloc(sizeof(ITSK00144_2ServerSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ServerSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->acceptor = acceptor;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ServerSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK00144_2ServerSession_purge(ITSK00144_2ServerSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void ITSK00144_2ServerSession_del(ITSK00144_2ServerSession *p)
{
	if (p == NULL) return;
	ITSK00144_2ServerSession_purge(p);
	Dz1Free(p);
}

void ITSK00144_2ServerSession_dump(ITSK00144_2ServerSession *p, int tab)
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
int ITSK00144_2ServerSession_cmp(ITSK00144_2ServerSession *a, ITSK00144_2ServerSession *b)
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
// ITSK00144_2ServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2SessionPresent
static struct ITSK00144_2SessionPresentMapA
{
	str_t str;
	ITSK00144_2SessionPresent v;
} ITSK00144_2SessionPresentMapA[] =
{
	{ (char *)"client", ITSK00144_2SessionPresent_client },
	{ (char *)"server", ITSK00144_2SessionPresent_server },
	{ NULL, ITSK00144_2SessionPresent_max }
};

str_t ITSK00144_2SessionPresentStrA(ITSK00144_2SessionPresent v)
{
	struct ITSK00144_2SessionPresentMapA *i = NULL;
	for (i = ITSK00144_2SessionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2SessionPresent ITSK00144_2SessionPresentFromStrA(str_t str)
{
	struct ITSK00144_2SessionPresentMapA *i = NULL;
	for (i = ITSK00144_2SessionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2SessionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2SessionPresentMapW
{
	wstr_t str;
	ITSK00144_2SessionPresent v;
} ITSK00144_2SessionPresentMapW[] =
{
	{ (wchar_t *)L"client", ITSK00144_2SessionPresent_client },
	{ (wchar_t *)L"server", ITSK00144_2SessionPresent_server },
	{ NULL, ITSK00144_2SessionPresent_max }
};

wstr_t ITSK00144_2SessionPresentStrW(ITSK00144_2SessionPresent v)
{
	struct ITSK00144_2SessionPresentMapW *i = NULL;
	for (i = ITSK00144_2SessionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2SessionPresent ITSK00144_2SessionPresentFromStrW(wstr_t str)
{
	struct ITSK00144_2SessionPresentMapW *i = NULL;
	for (i = ITSK00144_2SessionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2SessionPresent_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2SessionPresent *ITSK00144_2SessionPresent_new(ITSK00144_2SessionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2SessionPresent *__internal_ret = (ITSK00144_2SessionPresent *)Dz1Calloc(sizeof(ITSK00144_2SessionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ITSK00144_2SessionPresent_dump(ITSK00144_2SessionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ITSK00144_2SessionPresentStr(*v));
}
// ITSK00144_2SessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Session
ITSK00144_2Session *ITSK00144_2Session_new(ITSK00144_2SessionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2Session *ret = (ITSK00144_2Session *)Dz1Calloc(sizeof(ITSK00144_2Session), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Session_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ITSK00144_2SessionPresent_client:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client = (ITSK00144_2ClientSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2SessionPresent_server:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server = (ITSK00144_2ServerSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2SessionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Session_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ITSK00144_2Session_purge(ITSK00144_2Session *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ITSK00144_2SessionPresent_client:
		ITSK00144_2ClientSession_del(p->x.client);
		break;
	case ITSK00144_2SessionPresent_server:
		ITSK00144_2ServerSession_del(p->x.server);
		break;
	default:
		break;
	}
}

void ITSK00144_2Session_del(ITSK00144_2Session *p)
{
	if (!p) return;
	ITSK00144_2Session_purge(p);
	Dz1Free(p);
}

void ITSK00144_2Session_dump(ITSK00144_2Session *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ITSK00144_2SessionPresent_client:
		Dz1Thread_printf(Dz1T("client = ")); ITSK00144_2ClientSession_dump(p->x.client, tab); 
		break;
	case ITSK00144_2SessionPresent_server:
		Dz1Thread_printf(Dz1T("server = ")); ITSK00144_2ServerSession_dump(p->x.server, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// ITSK00144_2Session
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorEnv
ITSK001442EmulatorEnv *ITSK001442EmulatorEnv_new(void *tSelf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001442EmulatorEnv *__internal_ret = (ITSK001442EmulatorEnv *)Dz1Calloc(sizeof(ITSK001442EmulatorEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001442EmulatorEnv_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tSelf = tSelf;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001442EmulatorEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001442EmulatorEnv_purge(ITSK001442EmulatorEnv *p)
{
	if (p == NULL) return;
	ITSK00144_2Session_del(p->session);
}

void ITSK001442EmulatorEnv_del(ITSK001442EmulatorEnv *p)
{
	if (p == NULL) return;
	ITSK001442EmulatorEnv_purge(p);
	Dz1Free(p);
}

void ITSK001442EmulatorEnv_dump(ITSK001442EmulatorEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("session.")); ITSK00144_2Session_dump(p->session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("received_seq = ")); Dz1u8_dump(&p->received_seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("send_seq = ")); Dz1u8_dump(&p->send_seq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK001442EmulatorEnv
////////////////////////////////////////////////////////////////////////////////

