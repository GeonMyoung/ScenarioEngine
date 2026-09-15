////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestScenarioEnv.h"

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
		Dz1Thread_tprintf(tab, Dz1T("rx_buf = ")); Dz1ElasticBuf_dump(p->rx_buf, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("rx_stream = ")); Dz1Stream_dump(p->rx_stream, tab); 
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
		Dz1Thread_tprintf(tab, Dz1T("rx_buf = ")); Dz1ElasticBuf_dump(p->rx_buf, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("rx_stream = ")); Dz1Stream_dump(p->rx_stream, tab); 
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
// ITSK00144_2ScenarioServerRole
ITSK00144_2ScenarioServerRole *ITSK00144_2ScenarioServerRole_new(u16_t local_port, 
																 bool_t test_rsp_link_unit_status, 
																 bool_t test_rsp_status, 
																 bool_t test_rsp_list, 
																 bool_t test_rsp_update_list, 
																 bool_t test_rsp_reset, 
																 bool_t test_session_maintain, 
																 s64_t hb_duration, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ScenarioServerRole *__internal_ret = (ITSK00144_2ScenarioServerRole *)Dz1Calloc(sizeof(ITSK00144_2ScenarioServerRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ScenarioServerRole_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->test_rsp_link_unit_status = test_rsp_link_unit_status;
		__internal_ret->test_rsp_status = test_rsp_status;
		__internal_ret->test_rsp_list = test_rsp_list;
		__internal_ret->test_rsp_update_list = test_rsp_update_list;
		__internal_ret->test_rsp_reset = test_rsp_reset;
		__internal_ret->test_session_maintain = test_session_maintain;
		__internal_ret->hb_duration = hb_duration;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ScenarioServerRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2ScenarioServerRole_copy(ITSK00144_2ScenarioServerRole *dst, ITSK00144_2ScenarioServerRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->id && (dst->id = I2XTrafficSafetyDeviceSerialNo_clone(src->id, errp)) == NULL) ERR_OUT(errp);
	else if (src->received && (dst->received = Dz1Binary_clone(src->received, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_rsp_link_unit_status = src->test_rsp_link_unit_status;
		dst->test_rsp_status = src->test_rsp_status;
		dst->test_rsp_list = src->test_rsp_list;
		dst->test_rsp_update_list = src->test_rsp_update_list;
		dst->test_rsp_reset = src->test_rsp_reset;
		dst->test_session_maintain = src->test_session_maintain;
		dst->hb_duration = src->hb_duration;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2ScenarioServerRole *ITSK00144_2ScenarioServerRole_clone(ITSK00144_2ScenarioServerRole *src, Dz1Error *err)
{
	ITSK00144_2ScenarioServerRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2ScenarioServerRole *)Dz1Calloc(sizeof(ITSK00144_2ScenarioServerRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ScenarioServerRole_delAndSetNull, (void *)&dst);
		if (ITSK00144_2ScenarioServerRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ScenarioServerRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2ScenarioServerRole_purge(ITSK00144_2ScenarioServerRole *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceSerialNo_del(p->id);
	Dz1Binary_del(p->received);
}

void ITSK00144_2ScenarioServerRole_del(ITSK00144_2ScenarioServerRole *p)
{
	if (p == NULL) return;
	ITSK00144_2ScenarioServerRole_purge(p);
	Dz1Free(p);
}

void ITSK00144_2ScenarioServerRole_dump(ITSK00144_2ScenarioServerRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1u16_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_link_unit_status = ")); Dz1Bool_dump(&p->test_rsp_link_unit_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_status = ")); Dz1Bool_dump(&p->test_rsp_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_list = ")); Dz1Bool_dump(&p->test_rsp_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_update_list = ")); Dz1Bool_dump(&p->test_rsp_update_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsp_reset = ")); Dz1Bool_dump(&p->test_rsp_reset, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hb_duration = ")); Dz1s64_dump(&p->hb_duration, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("id = ")); I2XTrafficSafetyDeviceSerialNo_dump(p->id, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("received = ")); Dz1Binary_dump(p->received, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2ScenarioServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioLinkUnitRole
ITSK00144_2ScenarioLinkUnitRole *ITSK00144_2ScenarioLinkUnitRole_new(Dz1Str peer_ip, 
																	 u16_t peer_port, 
																	 bool_t test_req_link_unit_status, 
																	 bool_t test_req_status, 
																	 bool_t test_req_list, 
																	 bool_t test_req_update_list, 
																	 bool_t test_req_reset, 
																	 bool_t test_session_maintain, 
																	 bool_t test_tim, 
																	 bool_t test_map, 
																	 s64_t hb_duration, 
																	 I2XTrafficSafetyDeviceSerialNo *id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ScenarioLinkUnitRole *__internal_ret = (ITSK00144_2ScenarioLinkUnitRole *)Dz1Calloc(sizeof(ITSK00144_2ScenarioLinkUnitRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ScenarioLinkUnitRole_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->test_req_link_unit_status = test_req_link_unit_status;
			__internal_ret->test_req_status = test_req_status;
			__internal_ret->test_req_list = test_req_list;
			__internal_ret->test_req_update_list = test_req_update_list;
			__internal_ret->test_req_reset = test_req_reset;
			__internal_ret->test_session_maintain = test_session_maintain;
			__internal_ret->test_tim = test_tim;
			__internal_ret->test_map = test_map;
			__internal_ret->hb_duration = hb_duration;
			__internal_ret->id = id;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ScenarioLinkUnitRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2ScenarioLinkUnitRole_copy(ITSK00144_2ScenarioLinkUnitRole *dst, ITSK00144_2ScenarioLinkUnitRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->id && (dst->id = I2XTrafficSafetyDeviceSerialNo_clone(src->id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->test_req_link_unit_status = src->test_req_link_unit_status;
		dst->test_req_status = src->test_req_status;
		dst->test_req_list = src->test_req_list;
		dst->test_req_update_list = src->test_req_update_list;
		dst->test_req_reset = src->test_req_reset;
		dst->test_session_maintain = src->test_session_maintain;
		dst->test_tim = src->test_tim;
		dst->test_map = src->test_map;
		dst->hb_duration = src->hb_duration;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2ScenarioLinkUnitRole *ITSK00144_2ScenarioLinkUnitRole_clone(ITSK00144_2ScenarioLinkUnitRole *src, Dz1Error *err)
{
	ITSK00144_2ScenarioLinkUnitRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2ScenarioLinkUnitRole *)Dz1Calloc(sizeof(ITSK00144_2ScenarioLinkUnitRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ScenarioLinkUnitRole_delAndSetNull, (void *)&dst);
		if (ITSK00144_2ScenarioLinkUnitRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ScenarioLinkUnitRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2ScenarioLinkUnitRole_purge(ITSK00144_2ScenarioLinkUnitRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->peer_ip);
	I2XTrafficSafetyDeviceSerialNo_del(p->id);
}

void ITSK00144_2ScenarioLinkUnitRole_del(ITSK00144_2ScenarioLinkUnitRole *p)
{
	if (p == NULL) return;
	ITSK00144_2ScenarioLinkUnitRole_purge(p);
	Dz1Free(p);
}

void ITSK00144_2ScenarioLinkUnitRole_dump(ITSK00144_2ScenarioLinkUnitRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1u16_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_link_unit_status = ")); Dz1Bool_dump(&p->test_req_link_unit_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_status = ")); Dz1Bool_dump(&p->test_req_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_list = ")); Dz1Bool_dump(&p->test_req_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_update_list = ")); Dz1Bool_dump(&p->test_req_update_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_req_reset = ")); Dz1Bool_dump(&p->test_req_reset, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tim = ")); Dz1Bool_dump(&p->test_tim, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hb_duration = ")); Dz1s64_dump(&p->hb_duration, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("id = ")); I2XTrafficSafetyDeviceSerialNo_dump(p->id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2ScenarioLinkUnitRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioPresent
static struct ITSK00144_2ScenarioPresentMapA
{
	str_t str;
	ITSK00144_2ScenarioPresent v;
} ITSK00144_2ScenarioPresentMapA[] =
{
	{ (char *)"serverRole", ITSK00144_2ScenarioPresent_serverRole },
	{ (char *)"linkUnitRole", ITSK00144_2ScenarioPresent_linkUnitRole },
	{ NULL, ITSK00144_2ScenarioPresent_max }
};

str_t ITSK00144_2ScenarioPresentStrA(ITSK00144_2ScenarioPresent v)
{
	struct ITSK00144_2ScenarioPresentMapA *i = NULL;
	for (i = ITSK00144_2ScenarioPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ScenarioPresent ITSK00144_2ScenarioPresentFromStrA(str_t str)
{
	struct ITSK00144_2ScenarioPresentMapA *i = NULL;
	for (i = ITSK00144_2ScenarioPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ScenarioPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2ScenarioPresentMapW
{
	wstr_t str;
	ITSK00144_2ScenarioPresent v;
} ITSK00144_2ScenarioPresentMapW[] =
{
	{ (wchar_t *)L"serverRole", ITSK00144_2ScenarioPresent_serverRole },
	{ (wchar_t *)L"linkUnitRole", ITSK00144_2ScenarioPresent_linkUnitRole },
	{ NULL, ITSK00144_2ScenarioPresent_max }
};

wstr_t ITSK00144_2ScenarioPresentStrW(ITSK00144_2ScenarioPresent v)
{
	struct ITSK00144_2ScenarioPresentMapW *i = NULL;
	for (i = ITSK00144_2ScenarioPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ScenarioPresent ITSK00144_2ScenarioPresentFromStrW(wstr_t str)
{
	struct ITSK00144_2ScenarioPresentMapW *i = NULL;
	for (i = ITSK00144_2ScenarioPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ScenarioPresent_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2ScenarioPresent *ITSK00144_2ScenarioPresent_new(ITSK00144_2ScenarioPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ScenarioPresent *__internal_ret = (ITSK00144_2ScenarioPresent *)Dz1Calloc(sizeof(ITSK00144_2ScenarioPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ITSK00144_2ScenarioPresent_dump(ITSK00144_2ScenarioPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ITSK00144_2ScenarioPresentStr(*v));
}
// ITSK00144_2ScenarioPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Scenario
ITSK00144_2Scenario *ITSK00144_2Scenario_new(ITSK00144_2ScenarioPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2Scenario *ret = (ITSK00144_2Scenario *)Dz1Calloc(sizeof(ITSK00144_2Scenario), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Scenario_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ITSK00144_2ScenarioPresent_serverRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.serverRole = (ITSK00144_2ScenarioServerRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2ScenarioPresent_linkUnitRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.linkUnitRole = (ITSK00144_2ScenarioLinkUnitRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2ScenarioPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Scenario_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ITSK00144_2Scenario_copy(ITSK00144_2Scenario *ret, ITSK00144_2Scenario *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ITSK00144_2ScenarioPresent_serverRole:
			// _U_cst_clone
			if (src->x.serverRole && (ret->x.serverRole = ITSK00144_2ScenarioServerRole_clone(src->x.serverRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2ScenarioPresent_linkUnitRole:
			// _U_cst_clone
			if (src->x.linkUnitRole && (ret->x.linkUnitRole = ITSK00144_2ScenarioLinkUnitRole_clone(src->x.linkUnitRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2Scenario *ITSK00144_2Scenario_clone(ITSK00144_2Scenario *src, Dz1Error *err)
{
	ITSK00144_2Scenario *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ITSK00144_2Scenario *)Dz1Calloc(sizeof(ITSK00144_2Scenario), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Scenario_delAndSetNull, (void *)&ret);
		if (ITSK00144_2Scenario_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Scenario_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ITSK00144_2Scenario_purge(ITSK00144_2Scenario *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ITSK00144_2ScenarioPresent_serverRole:
		ITSK00144_2ScenarioServerRole_del(p->x.serverRole);
		break;
	case ITSK00144_2ScenarioPresent_linkUnitRole:
		ITSK00144_2ScenarioLinkUnitRole_del(p->x.linkUnitRole);
		break;
	default:
		break;
	}
}

void ITSK00144_2Scenario_del(ITSK00144_2Scenario *p)
{
	if (!p) return;
	ITSK00144_2Scenario_purge(p);
	Dz1Free(p);
}

void ITSK00144_2Scenario_dump(ITSK00144_2Scenario *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ITSK00144_2ScenarioPresent_serverRole:
		Dz1Thread_printf(Dz1T("serverRole = ")); ITSK00144_2ScenarioServerRole_dump(p->x.serverRole, tab); 
		break;
	case ITSK00144_2ScenarioPresent_linkUnitRole:
		Dz1Thread_printf(Dz1T("linkUnitRole = ")); ITSK00144_2ScenarioLinkUnitRole_dump(p->x.linkUnitRole, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// ITSK00144_2Scenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioEvent
static struct ITSK00144_2ScenarioEventMapA
{
	str_t str;
	ITSK00144_2ScenarioEvent v;
} ITSK00144_2ScenarioEventMapA[] =
{
	{ (char *)"start", ITSK00144_2ScenarioEvent_start },
	{ (char *)"auth", ITSK00144_2ScenarioEvent_auth },
	{ (char *)"heartbeat", ITSK00144_2ScenarioEvent_heartbeat },
	{ (char *)"data", ITSK00144_2ScenarioEvent_data },
	{ (char *)"data2", ITSK00144_2ScenarioEvent_data2 },
	{ (char *)"validate", ITSK00144_2ScenarioEvent_validate },
	{ (char *)"trigger", ITSK00144_2ScenarioEvent_trigger },
	{ (char *)"disconnected", ITSK00144_2ScenarioEvent_disconnected },
	{ NULL, ITSK00144_2ScenarioEvent_max }
};

str_t ITSK00144_2ScenarioEventStrA(ITSK00144_2ScenarioEvent v)
{
	struct ITSK00144_2ScenarioEventMapA *i = NULL;
	for (i = ITSK00144_2ScenarioEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ScenarioEvent ITSK00144_2ScenarioEventFromStrA(str_t str)
{
	struct ITSK00144_2ScenarioEventMapA *i = NULL;
	for (i = ITSK00144_2ScenarioEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ScenarioEvent_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2ScenarioEventMapW
{
	wstr_t str;
	ITSK00144_2ScenarioEvent v;
} ITSK00144_2ScenarioEventMapW[] =
{
	{ (wchar_t *)L"start", ITSK00144_2ScenarioEvent_start },
	{ (wchar_t *)L"auth", ITSK00144_2ScenarioEvent_auth },
	{ (wchar_t *)L"heartbeat", ITSK00144_2ScenarioEvent_heartbeat },
	{ (wchar_t *)L"data", ITSK00144_2ScenarioEvent_data },
	{ (wchar_t *)L"data2", ITSK00144_2ScenarioEvent_data2 },
	{ (wchar_t *)L"validate", ITSK00144_2ScenarioEvent_validate },
	{ (wchar_t *)L"trigger", ITSK00144_2ScenarioEvent_trigger },
	{ (wchar_t *)L"disconnected", ITSK00144_2ScenarioEvent_disconnected },
	{ NULL, ITSK00144_2ScenarioEvent_max }
};

wstr_t ITSK00144_2ScenarioEventStrW(ITSK00144_2ScenarioEvent v)
{
	struct ITSK00144_2ScenarioEventMapW *i = NULL;
	for (i = ITSK00144_2ScenarioEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ScenarioEvent ITSK00144_2ScenarioEventFromStrW(wstr_t str)
{
	struct ITSK00144_2ScenarioEventMapW *i = NULL;
	for (i = ITSK00144_2ScenarioEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ScenarioEvent_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2ScenarioEvent *ITSK00144_2ScenarioEvent_new(ITSK00144_2ScenarioEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ScenarioEvent *__internal_ret = (ITSK00144_2ScenarioEvent *)Dz1Calloc(sizeof(ITSK00144_2ScenarioEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ITSK00144_2ScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioServerState
static struct ITSK00144_2ScenarioServerStateMapA
{
	str_t str;
	ITSK00144_2ScenarioServerState v;
} ITSK00144_2ScenarioServerStateMapA[] =
{
	{ (char *)"initial", ITSK00144_2ScenarioServerState_initial },
	{ (char *)"wait_test_rsp_link_status", ITSK00144_2ScenarioServerState_wait_test_rsp_link_status },
	{ (char *)"wait_test_rsp_status", ITSK00144_2ScenarioServerState_wait_test_rsp_status },
	{ (char *)"wait_test_rsp_list", ITSK00144_2ScenarioServerState_wait_test_rsp_list },
	{ (char *)"wait_test_rsp_update_list", ITSK00144_2ScenarioServerState_wait_test_rsp_update_list },
	{ (char *)"wait_test_rsp_reset", ITSK00144_2ScenarioServerState_wait_test_rsp_reset },
	{ (char *)"complete", ITSK00144_2ScenarioServerState_complete },
	{ NULL, ITSK00144_2ScenarioServerState_max }
};

str_t ITSK00144_2ScenarioServerStateStrA(ITSK00144_2ScenarioServerState v)
{
	struct ITSK00144_2ScenarioServerStateMapA *i = NULL;
	for (i = ITSK00144_2ScenarioServerStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ScenarioServerState ITSK00144_2ScenarioServerStateFromStrA(str_t str)
{
	struct ITSK00144_2ScenarioServerStateMapA *i = NULL;
	for (i = ITSK00144_2ScenarioServerStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ScenarioServerState_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2ScenarioServerStateMapW
{
	wstr_t str;
	ITSK00144_2ScenarioServerState v;
} ITSK00144_2ScenarioServerStateMapW[] =
{
	{ (wchar_t *)L"initial", ITSK00144_2ScenarioServerState_initial },
	{ (wchar_t *)L"wait_test_rsp_link_status", ITSK00144_2ScenarioServerState_wait_test_rsp_link_status },
	{ (wchar_t *)L"wait_test_rsp_status", ITSK00144_2ScenarioServerState_wait_test_rsp_status },
	{ (wchar_t *)L"wait_test_rsp_list", ITSK00144_2ScenarioServerState_wait_test_rsp_list },
	{ (wchar_t *)L"wait_test_rsp_update_list", ITSK00144_2ScenarioServerState_wait_test_rsp_update_list },
	{ (wchar_t *)L"wait_test_rsp_reset", ITSK00144_2ScenarioServerState_wait_test_rsp_reset },
	{ (wchar_t *)L"complete", ITSK00144_2ScenarioServerState_complete },
	{ NULL, ITSK00144_2ScenarioServerState_max }
};

wstr_t ITSK00144_2ScenarioServerStateStrW(ITSK00144_2ScenarioServerState v)
{
	struct ITSK00144_2ScenarioServerStateMapW *i = NULL;
	for (i = ITSK00144_2ScenarioServerStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ScenarioServerState ITSK00144_2ScenarioServerStateFromStrW(wstr_t str)
{
	struct ITSK00144_2ScenarioServerStateMapW *i = NULL;
	for (i = ITSK00144_2ScenarioServerStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ScenarioServerState_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2ScenarioServerState *ITSK00144_2ScenarioServerState_new(ITSK00144_2ScenarioServerState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ScenarioServerState *__internal_ret = (ITSK00144_2ScenarioServerState *)Dz1Calloc(sizeof(ITSK00144_2ScenarioServerState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ITSK00144_2ScenarioServerState_dump(ITSK00144_2ScenarioServerState *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ITSK00144_2ScenarioServerStateStr(*v));
}
// ITSK00144_2ScenarioServerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ScenarioClientState
static struct ITSK00144_2ScenarioClientStateMapA
{
	str_t str;
	ITSK00144_2ScenarioClientState v;
} ITSK00144_2ScenarioClientStateMapA[] =
{
	{ (char *)"initial", ITSK00144_2ScenarioClientState_initial },
	{ (char *)"wait_req", ITSK00144_2ScenarioClientState_wait_req },
	{ (char *)"complete", ITSK00144_2ScenarioClientState_complete },
	{ NULL, ITSK00144_2ScenarioClientState_max }
};

str_t ITSK00144_2ScenarioClientStateStrA(ITSK00144_2ScenarioClientState v)
{
	struct ITSK00144_2ScenarioClientStateMapA *i = NULL;
	for (i = ITSK00144_2ScenarioClientStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ScenarioClientState ITSK00144_2ScenarioClientStateFromStrA(str_t str)
{
	struct ITSK00144_2ScenarioClientStateMapA *i = NULL;
	for (i = ITSK00144_2ScenarioClientStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ScenarioClientState_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2ScenarioClientStateMapW
{
	wstr_t str;
	ITSK00144_2ScenarioClientState v;
} ITSK00144_2ScenarioClientStateMapW[] =
{
	{ (wchar_t *)L"initial", ITSK00144_2ScenarioClientState_initial },
	{ (wchar_t *)L"wait_req", ITSK00144_2ScenarioClientState_wait_req },
	{ (wchar_t *)L"complete", ITSK00144_2ScenarioClientState_complete },
	{ NULL, ITSK00144_2ScenarioClientState_max }
};

wstr_t ITSK00144_2ScenarioClientStateStrW(ITSK00144_2ScenarioClientState v)
{
	struct ITSK00144_2ScenarioClientStateMapW *i = NULL;
	for (i = ITSK00144_2ScenarioClientStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2ScenarioClientState ITSK00144_2ScenarioClientStateFromStrW(wstr_t str)
{
	struct ITSK00144_2ScenarioClientStateMapW *i = NULL;
	for (i = ITSK00144_2ScenarioClientStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2ScenarioClientState_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2ScenarioClientState *ITSK00144_2ScenarioClientState_new(ITSK00144_2ScenarioClientState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ScenarioClientState *__internal_ret = (ITSK00144_2ScenarioClientState *)Dz1Calloc(sizeof(ITSK00144_2ScenarioClientState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ITSK00144_2ScenarioClientState_dump(ITSK00144_2ScenarioClientState *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ITSK00144_2ScenarioClientStateStr(*v));
}
// ITSK00144_2ScenarioClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK001442TestScenarioEnv
ITSK001442TestScenarioEnv *ITSK001442TestScenarioEnv_new(void *tSelf, 
														 void *tMain, 
														 Dz1JsonSpec *spec, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK001442TestScenarioEnv *__internal_ret = (ITSK001442TestScenarioEnv *)Dz1Calloc(sizeof(ITSK001442TestScenarioEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK001442TestScenarioEnv_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tSelf = tSelf;
		__internal_ret->tMain = tMain;
		__internal_ret->spec = spec;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK001442TestScenarioEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ITSK001442TestScenarioEnv_purge(ITSK001442TestScenarioEnv *p)
{
	if (p == NULL) return;
	Dz1JsonSpec_del(p->spec);
	ITSK00144_2Session_del(p->session);
	ITSK00144_2Scenario_del(p->scenario);
	Dz1Str_del(p->current_test);
}

void ITSK001442TestScenarioEnv_del(ITSK001442TestScenarioEnv *p)
{
	if (p == NULL) return;
	ITSK001442TestScenarioEnv_purge(p);
	Dz1Free(p);
}

void ITSK001442TestScenarioEnv_dump(ITSK001442TestScenarioEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("tMain = %p\n"), p->tMain);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("spec = ")); Dz1JsonSpec_dump(p->spec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("session.")); ITSK00144_2Session_dump(p->session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("scenario.")); ITSK00144_2Scenario_dump(p->scenario, tab); 
		Dz1Thread_tprintf(tab, Dz1T("received_seq = ")); Dz1u8_dump(&p->received_seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("send_seq = ")); Dz1u8_dump(&p->send_seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("current_test = ")); Dz1Str_dump(p->current_test, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_run = ")); Dz1Bool_dump(&p->is_run, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = ")); Dz1s32_dump(&p->state, tab); 
		Dz1Thread_tprintf(tab, Dz1T("flags = ")); Dz1u32_dump(&p->flags, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK001442TestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

