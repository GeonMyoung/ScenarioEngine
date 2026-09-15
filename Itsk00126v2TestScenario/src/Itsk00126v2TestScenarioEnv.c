////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v2TestScenarioEnv.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ClientSession
Itsk00126v2ClientSession *Itsk00126v2ClientSession_new(Dz1SockAddr *peer, 
													   Dz1SockAddr *local, 
													   Dz1TcpClientSocket *sock, 
													   Dz1ElasticBuf *rx_buf, 
													   Dz1Stream *rx_stream, 
													   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ClientSession *__internal_ret = (Itsk00126v2ClientSession *)Dz1Calloc(sizeof(Itsk00126v2ClientSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ClientSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ClientSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126v2ClientSession_purge(Itsk00126v2ClientSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void Itsk00126v2ClientSession_del(Itsk00126v2ClientSession *p)
{
	if (p == NULL) return;
	Itsk00126v2ClientSession_purge(p);
	Dz1Free(p);
}

void Itsk00126v2ClientSession_dump(Itsk00126v2ClientSession *p, int tab)
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
int Itsk00126v2ClientSession_cmp(Itsk00126v2ClientSession *a, Itsk00126v2ClientSession *b)
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
// Itsk00126v2ClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ServerSession
Itsk00126v2ServerSession *Itsk00126v2ServerSession_new(u32_t acceptor, 
													   Dz1SockAddr *peer, 
													   Dz1SockAddr *local, 
													   Dz1TcpClientSocket *sock, 
													   Dz1ElasticBuf *rx_buf, 
													   Dz1Stream *rx_stream, 
													   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ServerSession *__internal_ret = (Itsk00126v2ServerSession *)Dz1Calloc(sizeof(Itsk00126v2ServerSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ServerSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->acceptor = acceptor;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ServerSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126v2ServerSession_purge(Itsk00126v2ServerSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void Itsk00126v2ServerSession_del(Itsk00126v2ServerSession *p)
{
	if (p == NULL) return;
	Itsk00126v2ServerSession_purge(p);
	Dz1Free(p);
}

void Itsk00126v2ServerSession_dump(Itsk00126v2ServerSession *p, int tab)
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
int Itsk00126v2ServerSession_cmp(Itsk00126v2ServerSession *a, Itsk00126v2ServerSession *b)
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
// Itsk00126v2ServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2SessionPresent
static struct Itsk00126v2SessionPresentMapA
{
	str_t str;
	Itsk00126v2SessionPresent v;
} Itsk00126v2SessionPresentMapA[] =
{
	{ (char *)"client", Itsk00126v2SessionPresent_client },
	{ (char *)"server", Itsk00126v2SessionPresent_server },
	{ NULL, Itsk00126v2SessionPresent_max }
};

str_t Itsk00126v2SessionPresentStrA(Itsk00126v2SessionPresent v)
{
	struct Itsk00126v2SessionPresentMapA *i = NULL;
	for (i = Itsk00126v2SessionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2SessionPresent Itsk00126v2SessionPresentFromStrA(str_t str)
{
	struct Itsk00126v2SessionPresentMapA *i = NULL;
	for (i = Itsk00126v2SessionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2SessionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2SessionPresentMapW
{
	wstr_t str;
	Itsk00126v2SessionPresent v;
} Itsk00126v2SessionPresentMapW[] =
{
	{ (wchar_t *)L"client", Itsk00126v2SessionPresent_client },
	{ (wchar_t *)L"server", Itsk00126v2SessionPresent_server },
	{ NULL, Itsk00126v2SessionPresent_max }
};

wstr_t Itsk00126v2SessionPresentStrW(Itsk00126v2SessionPresent v)
{
	struct Itsk00126v2SessionPresentMapW *i = NULL;
	for (i = Itsk00126v2SessionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2SessionPresent Itsk00126v2SessionPresentFromStrW(wstr_t str)
{
	struct Itsk00126v2SessionPresentMapW *i = NULL;
	for (i = Itsk00126v2SessionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2SessionPresent_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2SessionPresent *Itsk00126v2SessionPresent_new(Itsk00126v2SessionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2SessionPresent *__internal_ret = (Itsk00126v2SessionPresent *)Dz1Calloc(sizeof(Itsk00126v2SessionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2SessionPresent_dump(Itsk00126v2SessionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2SessionPresentStr(*v));
}
// Itsk00126v2SessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2Session
Itsk00126v2Session *Itsk00126v2Session_new(Itsk00126v2SessionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2Session *ret = (Itsk00126v2Session *)Dz1Calloc(sizeof(Itsk00126v2Session), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2Session_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Itsk00126v2SessionPresent_client:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client = (Itsk00126v2ClientSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2SessionPresent_server:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server = (Itsk00126v2ServerSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2SessionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2Session_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Itsk00126v2Session_purge(Itsk00126v2Session *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Itsk00126v2SessionPresent_client:
		Itsk00126v2ClientSession_del(p->x.client);
		break;
	case Itsk00126v2SessionPresent_server:
		Itsk00126v2ServerSession_del(p->x.server);
		break;
	default:
		break;
	}
}

void Itsk00126v2Session_del(Itsk00126v2Session *p)
{
	if (!p) return;
	Itsk00126v2Session_purge(p);
	Dz1Free(p);
}

void Itsk00126v2Session_dump(Itsk00126v2Session *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Itsk00126v2SessionPresent_client:
		Dz1Thread_printf(Dz1T("client = ")); Itsk00126v2ClientSession_dump(p->x.client, tab); 
		break;
	case Itsk00126v2SessionPresent_server:
		Dz1Thread_printf(Dz1T("server = ")); Itsk00126v2ServerSession_dump(p->x.server, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Itsk00126v2Session
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioClientRole
Itsk00126v2ScenarioClientRole *Itsk00126v2ScenarioClientRole_new(Dz1Str peer_ip, 
																 u16_t peer_port, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ScenarioClientRole *__internal_ret = (Itsk00126v2ScenarioClientRole *)Dz1Calloc(sizeof(Itsk00126v2ScenarioClientRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ScenarioClientRole_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ScenarioClientRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2ScenarioClientRole_copy(Itsk00126v2ScenarioClientRole *dst, Itsk00126v2ScenarioClientRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2ScenarioClientRole *Itsk00126v2ScenarioClientRole_clone(Itsk00126v2ScenarioClientRole *src, Dz1Error *err)
{
	Itsk00126v2ScenarioClientRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2ScenarioClientRole *)Dz1Calloc(sizeof(Itsk00126v2ScenarioClientRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ScenarioClientRole_delAndSetNull, (void *)&dst);
		if (Itsk00126v2ScenarioClientRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ScenarioClientRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2ScenarioClientRole_purge(Itsk00126v2ScenarioClientRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->peer_ip);
}

void Itsk00126v2ScenarioClientRole_del(Itsk00126v2ScenarioClientRole *p)
{
	if (p == NULL) return;
	Itsk00126v2ScenarioClientRole_purge(p);
	Dz1Free(p);
}

void Itsk00126v2ScenarioClientRole_dump(Itsk00126v2ScenarioClientRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1u16_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2ScenarioClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioServerRole
Itsk00126v2ScenarioServerRole *Itsk00126v2ScenarioServerRole_new(bool_t local_port, 
																 Dz1Str iot_im_device_id, 
																 bool_t test_iot_im_device_sttus_info, 
																 bool_t test_iot_device_list_response_info, 
																 bool_t test_iot_device_sttus_info, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ScenarioServerRole *__internal_ret = (Itsk00126v2ScenarioServerRole *)Dz1Calloc(sizeof(Itsk00126v2ScenarioServerRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ScenarioServerRole_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->local_port = local_port;
			__internal_ret->test_iot_im_device_sttus_info = test_iot_im_device_sttus_info;
			__internal_ret->test_iot_device_list_response_info = test_iot_device_list_response_info;
			__internal_ret->test_iot_device_sttus_info = test_iot_device_sttus_info;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ScenarioServerRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2ScenarioServerRole_copy(Itsk00126v2ScenarioServerRole *dst, Itsk00126v2ScenarioServerRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_iot_im_device_sttus_info = src->test_iot_im_device_sttus_info;
		dst->test_iot_device_list_response_info = src->test_iot_device_list_response_info;
		dst->test_iot_device_sttus_info = src->test_iot_device_sttus_info;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2ScenarioServerRole *Itsk00126v2ScenarioServerRole_clone(Itsk00126v2ScenarioServerRole *src, Dz1Error *err)
{
	Itsk00126v2ScenarioServerRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2ScenarioServerRole *)Dz1Calloc(sizeof(Itsk00126v2ScenarioServerRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2ScenarioServerRole_delAndSetNull, (void *)&dst);
		if (Itsk00126v2ScenarioServerRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2ScenarioServerRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2ScenarioServerRole_purge(Itsk00126v2ScenarioServerRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
}

void Itsk00126v2ScenarioServerRole_del(Itsk00126v2ScenarioServerRole *p)
{
	if (p == NULL) return;
	Itsk00126v2ScenarioServerRole_purge(p);
	Dz1Free(p);
}

void Itsk00126v2ScenarioServerRole_dump(Itsk00126v2ScenarioServerRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1Bool_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_iot_im_device_sttus_info = ")); Dz1Bool_dump(&p->test_iot_im_device_sttus_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_iot_device_list_response_info = ")); Dz1Bool_dump(&p->test_iot_device_list_response_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_iot_device_sttus_info = ")); Dz1Bool_dump(&p->test_iot_device_sttus_info, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2ScenarioServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioPresent
static struct Itsk00126v2ScenarioPresentMapA
{
	str_t str;
	Itsk00126v2ScenarioPresent v;
} Itsk00126v2ScenarioPresentMapA[] =
{
	{ (char *)"clientRole", Itsk00126v2ScenarioPresent_clientRole },
	{ (char *)"serverRole", Itsk00126v2ScenarioPresent_serverRole },
	{ NULL, Itsk00126v2ScenarioPresent_max }
};

str_t Itsk00126v2ScenarioPresentStrA(Itsk00126v2ScenarioPresent v)
{
	struct Itsk00126v2ScenarioPresentMapA *i = NULL;
	for (i = Itsk00126v2ScenarioPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ScenarioPresent Itsk00126v2ScenarioPresentFromStrA(str_t str)
{
	struct Itsk00126v2ScenarioPresentMapA *i = NULL;
	for (i = Itsk00126v2ScenarioPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ScenarioPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2ScenarioPresentMapW
{
	wstr_t str;
	Itsk00126v2ScenarioPresent v;
} Itsk00126v2ScenarioPresentMapW[] =
{
	{ (wchar_t *)L"clientRole", Itsk00126v2ScenarioPresent_clientRole },
	{ (wchar_t *)L"serverRole", Itsk00126v2ScenarioPresent_serverRole },
	{ NULL, Itsk00126v2ScenarioPresent_max }
};

wstr_t Itsk00126v2ScenarioPresentStrW(Itsk00126v2ScenarioPresent v)
{
	struct Itsk00126v2ScenarioPresentMapW *i = NULL;
	for (i = Itsk00126v2ScenarioPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ScenarioPresent Itsk00126v2ScenarioPresentFromStrW(wstr_t str)
{
	struct Itsk00126v2ScenarioPresentMapW *i = NULL;
	for (i = Itsk00126v2ScenarioPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ScenarioPresent_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2ScenarioPresent *Itsk00126v2ScenarioPresent_new(Itsk00126v2ScenarioPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ScenarioPresent *__internal_ret = (Itsk00126v2ScenarioPresent *)Dz1Calloc(sizeof(Itsk00126v2ScenarioPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2ScenarioPresent_dump(Itsk00126v2ScenarioPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2ScenarioPresentStr(*v));
}
// Itsk00126v2ScenarioPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2Scenario
Itsk00126v2Scenario *Itsk00126v2Scenario_new(Itsk00126v2ScenarioPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2Scenario *ret = (Itsk00126v2Scenario *)Dz1Calloc(sizeof(Itsk00126v2Scenario), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2Scenario_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Itsk00126v2ScenarioPresent_clientRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clientRole = (Itsk00126v2ScenarioClientRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2ScenarioPresent_serverRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.serverRole = (Itsk00126v2ScenarioServerRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2ScenarioPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2Scenario_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Itsk00126v2Scenario_copy(Itsk00126v2Scenario *ret, Itsk00126v2Scenario *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Itsk00126v2ScenarioPresent_clientRole:
			// _U_cst_clone
			if (src->x.clientRole && (ret->x.clientRole = Itsk00126v2ScenarioClientRole_clone(src->x.clientRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v2ScenarioPresent_serverRole:
			// _U_cst_clone
			if (src->x.serverRole && (ret->x.serverRole = Itsk00126v2ScenarioServerRole_clone(src->x.serverRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2Scenario *Itsk00126v2Scenario_clone(Itsk00126v2Scenario *src, Dz1Error *err)
{
	Itsk00126v2Scenario *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Itsk00126v2Scenario *)Dz1Calloc(sizeof(Itsk00126v2Scenario), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2Scenario_delAndSetNull, (void *)&ret);
		if (Itsk00126v2Scenario_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2Scenario_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Itsk00126v2Scenario_purge(Itsk00126v2Scenario *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Itsk00126v2ScenarioPresent_clientRole:
		Itsk00126v2ScenarioClientRole_del(p->x.clientRole);
		break;
	case Itsk00126v2ScenarioPresent_serverRole:
		Itsk00126v2ScenarioServerRole_del(p->x.serverRole);
		break;
	default:
		break;
	}
}

void Itsk00126v2Scenario_del(Itsk00126v2Scenario *p)
{
	if (!p) return;
	Itsk00126v2Scenario_purge(p);
	Dz1Free(p);
}

void Itsk00126v2Scenario_dump(Itsk00126v2Scenario *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Itsk00126v2ScenarioPresent_clientRole:
		Dz1Thread_printf(Dz1T("clientRole = ")); Itsk00126v2ScenarioClientRole_dump(p->x.clientRole, tab); 
		break;
	case Itsk00126v2ScenarioPresent_serverRole:
		Dz1Thread_printf(Dz1T("serverRole = ")); Itsk00126v2ScenarioServerRole_dump(p->x.serverRole, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Itsk00126v2Scenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioEvent
static struct Itsk00126v2ScenarioEventMapA
{
	str_t str;
	Itsk00126v2ScenarioEvent v;
} Itsk00126v2ScenarioEventMapA[] =
{
	{ (char *)"start", Itsk00126v2ScenarioEvent_start },
	{ (char *)"auth", Itsk00126v2ScenarioEvent_auth },
	{ (char *)"trigger", Itsk00126v2ScenarioEvent_trigger },
	{ (char *)"data", Itsk00126v2ScenarioEvent_data },
	{ (char *)"disconnected", Itsk00126v2ScenarioEvent_disconnected },
	{ NULL, Itsk00126v2ScenarioEvent_max }
};

str_t Itsk00126v2ScenarioEventStrA(Itsk00126v2ScenarioEvent v)
{
	struct Itsk00126v2ScenarioEventMapA *i = NULL;
	for (i = Itsk00126v2ScenarioEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ScenarioEvent Itsk00126v2ScenarioEventFromStrA(str_t str)
{
	struct Itsk00126v2ScenarioEventMapA *i = NULL;
	for (i = Itsk00126v2ScenarioEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ScenarioEvent_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2ScenarioEventMapW
{
	wstr_t str;
	Itsk00126v2ScenarioEvent v;
} Itsk00126v2ScenarioEventMapW[] =
{
	{ (wchar_t *)L"start", Itsk00126v2ScenarioEvent_start },
	{ (wchar_t *)L"auth", Itsk00126v2ScenarioEvent_auth },
	{ (wchar_t *)L"trigger", Itsk00126v2ScenarioEvent_trigger },
	{ (wchar_t *)L"data", Itsk00126v2ScenarioEvent_data },
	{ (wchar_t *)L"disconnected", Itsk00126v2ScenarioEvent_disconnected },
	{ NULL, Itsk00126v2ScenarioEvent_max }
};

wstr_t Itsk00126v2ScenarioEventStrW(Itsk00126v2ScenarioEvent v)
{
	struct Itsk00126v2ScenarioEventMapW *i = NULL;
	for (i = Itsk00126v2ScenarioEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ScenarioEvent Itsk00126v2ScenarioEventFromStrW(wstr_t str)
{
	struct Itsk00126v2ScenarioEventMapW *i = NULL;
	for (i = Itsk00126v2ScenarioEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ScenarioEvent_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2ScenarioEvent *Itsk00126v2ScenarioEvent_new(Itsk00126v2ScenarioEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ScenarioEvent *__internal_ret = (Itsk00126v2ScenarioEvent *)Dz1Calloc(sizeof(Itsk00126v2ScenarioEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2ScenarioEvent_dump(Itsk00126v2ScenarioEvent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2ScenarioEventStr(*v));
}
// Itsk00126v2ScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioServerState
static struct Itsk00126v2ScenarioServerStateMapA
{
	str_t str;
	Itsk00126v2ScenarioServerState v;
} Itsk00126v2ScenarioServerStateMapA[] =
{
	{ (char *)"initial", Itsk00126v2ScenarioServerState_initial },
	{ (char *)"wait_test_iot_im_device_sttus_info", Itsk00126v2ScenarioServerState_wait_test_iot_im_device_sttus_info },
	{ (char *)"wait_test_iot_device_list_response_info", Itsk00126v2ScenarioServerState_wait_test_iot_device_list_response_info },
	{ (char *)"wait_test_iot_device_sttus_info", Itsk00126v2ScenarioServerState_wait_test_iot_device_sttus_info },
	{ (char *)"complete", Itsk00126v2ScenarioServerState_complete },
	{ NULL, Itsk00126v2ScenarioServerState_max }
};

str_t Itsk00126v2ScenarioServerStateStrA(Itsk00126v2ScenarioServerState v)
{
	struct Itsk00126v2ScenarioServerStateMapA *i = NULL;
	for (i = Itsk00126v2ScenarioServerStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ScenarioServerState Itsk00126v2ScenarioServerStateFromStrA(str_t str)
{
	struct Itsk00126v2ScenarioServerStateMapA *i = NULL;
	for (i = Itsk00126v2ScenarioServerStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ScenarioServerState_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2ScenarioServerStateMapW
{
	wstr_t str;
	Itsk00126v2ScenarioServerState v;
} Itsk00126v2ScenarioServerStateMapW[] =
{
	{ (wchar_t *)L"initial", Itsk00126v2ScenarioServerState_initial },
	{ (wchar_t *)L"wait_test_iot_im_device_sttus_info", Itsk00126v2ScenarioServerState_wait_test_iot_im_device_sttus_info },
	{ (wchar_t *)L"wait_test_iot_device_list_response_info", Itsk00126v2ScenarioServerState_wait_test_iot_device_list_response_info },
	{ (wchar_t *)L"wait_test_iot_device_sttus_info", Itsk00126v2ScenarioServerState_wait_test_iot_device_sttus_info },
	{ (wchar_t *)L"complete", Itsk00126v2ScenarioServerState_complete },
	{ NULL, Itsk00126v2ScenarioServerState_max }
};

wstr_t Itsk00126v2ScenarioServerStateStrW(Itsk00126v2ScenarioServerState v)
{
	struct Itsk00126v2ScenarioServerStateMapW *i = NULL;
	for (i = Itsk00126v2ScenarioServerStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ScenarioServerState Itsk00126v2ScenarioServerStateFromStrW(wstr_t str)
{
	struct Itsk00126v2ScenarioServerStateMapW *i = NULL;
	for (i = Itsk00126v2ScenarioServerStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ScenarioServerState_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2ScenarioServerState *Itsk00126v2ScenarioServerState_new(Itsk00126v2ScenarioServerState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ScenarioServerState *__internal_ret = (Itsk00126v2ScenarioServerState *)Dz1Calloc(sizeof(Itsk00126v2ScenarioServerState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2ScenarioServerState_dump(Itsk00126v2ScenarioServerState *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2ScenarioServerStateStr(*v));
}
// Itsk00126v2ScenarioServerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ScenarioClientState
static struct Itsk00126v2ScenarioClientStateMapA
{
	str_t str;
	Itsk00126v2ScenarioClientState v;
} Itsk00126v2ScenarioClientStateMapA[] =
{
	{ (char *)"initial", Itsk00126v2ScenarioClientState_initial },
	{ (char *)"complete", Itsk00126v2ScenarioClientState_complete },
	{ NULL, Itsk00126v2ScenarioClientState_max }
};

str_t Itsk00126v2ScenarioClientStateStrA(Itsk00126v2ScenarioClientState v)
{
	struct Itsk00126v2ScenarioClientStateMapA *i = NULL;
	for (i = Itsk00126v2ScenarioClientStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ScenarioClientState Itsk00126v2ScenarioClientStateFromStrA(str_t str)
{
	struct Itsk00126v2ScenarioClientStateMapA *i = NULL;
	for (i = Itsk00126v2ScenarioClientStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ScenarioClientState_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2ScenarioClientStateMapW
{
	wstr_t str;
	Itsk00126v2ScenarioClientState v;
} Itsk00126v2ScenarioClientStateMapW[] =
{
	{ (wchar_t *)L"initial", Itsk00126v2ScenarioClientState_initial },
	{ (wchar_t *)L"complete", Itsk00126v2ScenarioClientState_complete },
	{ NULL, Itsk00126v2ScenarioClientState_max }
};

wstr_t Itsk00126v2ScenarioClientStateStrW(Itsk00126v2ScenarioClientState v)
{
	struct Itsk00126v2ScenarioClientStateMapW *i = NULL;
	for (i = Itsk00126v2ScenarioClientStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2ScenarioClientState Itsk00126v2ScenarioClientStateFromStrW(wstr_t str)
{
	struct Itsk00126v2ScenarioClientStateMapW *i = NULL;
	for (i = Itsk00126v2ScenarioClientStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2ScenarioClientState_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2ScenarioClientState *Itsk00126v2ScenarioClientState_new(Itsk00126v2ScenarioClientState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2ScenarioClientState *__internal_ret = (Itsk00126v2ScenarioClientState *)Dz1Calloc(sizeof(Itsk00126v2ScenarioClientState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2ScenarioClientState_dump(Itsk00126v2ScenarioClientState *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2ScenarioClientStateStr(*v));
}
// Itsk00126v2ScenarioClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V2TestScenarioEnv
Itsk00126V2TestScenarioEnv *Itsk00126V2TestScenarioEnv_new(void *tSelf, 
														   void *tMain, 
														   Dz1JsonSpec *spec, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126V2TestScenarioEnv *__internal_ret = (Itsk00126V2TestScenarioEnv *)Dz1Calloc(sizeof(Itsk00126V2TestScenarioEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126V2TestScenarioEnv_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tSelf = tSelf;
		__internal_ret->tMain = tMain;
		__internal_ret->spec = spec;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126V2TestScenarioEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Itsk00126V2TestScenarioEnv_purge(Itsk00126V2TestScenarioEnv *p)
{
	if (p == NULL) return;
	Dz1JsonSpec_del(p->spec);
	Itsk00126v2Session_del(p->session);
	Itsk00126v2Scenario_del(p->scenario);
	Dz1Str_del(p->current_test);
}

void Itsk00126V2TestScenarioEnv_del(Itsk00126V2TestScenarioEnv *p)
{
	if (p == NULL) return;
	Itsk00126V2TestScenarioEnv_purge(p);
	Dz1Free(p);
}

void Itsk00126V2TestScenarioEnv_dump(Itsk00126V2TestScenarioEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("tMain = %p\n"), p->tMain);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("spec = ")); Dz1JsonSpec_dump(p->spec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("session.")); Itsk00126v2Session_dump(p->session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("scenario.")); Itsk00126v2Scenario_dump(p->scenario, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_run = ")); Dz1Bool_dump(&p->is_run, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = ")); Dz1s32_dump(&p->state, tab); 
		Dz1Thread_tprintf(tab, Dz1T("flags = ")); Dz1u32_dump(&p->flags, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("current_test = ")); Dz1Str_dump(p->current_test, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126V2TestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

