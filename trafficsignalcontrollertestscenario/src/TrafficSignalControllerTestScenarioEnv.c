////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestScenarioEnv.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerSession
TrafficSignalControllerSession *TrafficSignalControllerSession_new(u32_t acceptor, 
																   Dz1SockAddr *peer, 
																   Dz1SockAddr *local, 
																   Dz1TcpClientSocket *sock, 
																   Dz1ElasticBuf *rx_buf, 
																   Dz1Stream *rx_stream, 
																   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerSession *__internal_ret = (TrafficSignalControllerSession *)Dz1Calloc(sizeof(TrafficSignalControllerSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->acceptor = acceptor;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void TrafficSignalControllerSession_purge(TrafficSignalControllerSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void TrafficSignalControllerSession_del(TrafficSignalControllerSession *p)
{
	if (p == NULL) return;
	TrafficSignalControllerSession_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerSession_dump(TrafficSignalControllerSession *p, int tab)
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
// TrafficSignalControllerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerScenario
TrafficSignalControllerScenario *TrafficSignalControllerScenario_new(TrafficSignalControllerTestMsgFrame *received, 
																	 bool_t result, 
																	 Dz1Str ip, 
																	 u16_t port, 
																	 u8_t cross_id, 
																	 Dz1Str req_str, 
																	 u8_t eam_type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerScenario *__internal_ret = (TrafficSignalControllerScenario *)Dz1Calloc(sizeof(TrafficSignalControllerScenario), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerScenario_delAndSetNull, (void *)&__internal_ret);
		
		if (ip && (__internal_ret->ip = Dz1Str_clone(ip, errp)) == NULL) ERR_OUT(errp);
		else if (req_str && (__internal_ret->req_str = Dz1Str_clone(req_str, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->received = received;
			__internal_ret->result = result;
			__internal_ret->port = port;
			__internal_ret->cross_id = cross_id;
			__internal_ret->eam_type = eam_type;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerScenario_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerScenario_copy(TrafficSignalControllerScenario *dst, TrafficSignalControllerScenario *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->received && (dst->received = TrafficSignalControllerTestMsgFrame_clone(src->received, errp)) == NULL) ERR_OUT(errp);
	else if (src->ip && (dst->ip = Dz1Str_clone(src->ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->req_str && (dst->req_str = Dz1Str_clone(src->req_str, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->result = src->result;
		dst->port = src->port;
		dst->cross_id = src->cross_id;
		dst->eam_type = src->eam_type;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerScenario *TrafficSignalControllerScenario_clone(TrafficSignalControllerScenario *src, Dz1Error *err)
{
	TrafficSignalControllerScenario *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerScenario *)Dz1Calloc(sizeof(TrafficSignalControllerScenario), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerScenario_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerScenario_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerScenario_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerScenario_purge(TrafficSignalControllerScenario *p)
{
	if (p == NULL) return;
	TrafficSignalControllerTestMsgFrame_del(p->received);
	Dz1Str_del(p->ip);
	Dz1Str_del(p->req_str);
}

void TrafficSignalControllerScenario_del(TrafficSignalControllerScenario *p)
{
	if (p == NULL) return;
	TrafficSignalControllerScenario_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerScenario_dump(TrafficSignalControllerScenario *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("received = ")); TrafficSignalControllerTestMsgFrame_dump(p->received, tab); 
		Dz1Thread_tprintf(tab, Dz1T("result = ")); Dz1Bool_dump(&p->result, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ip = ")); Dz1Str_dump(p->ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("port = ")); Dz1u16_dump(&p->port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("req_str = ")); Dz1Str_dump(p->req_str, tab); 
		Dz1Thread_tprintf(tab, Dz1T("eam_type = ")); Dz1u8_dump(&p->eam_type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerScenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerScenarioEvent
static struct TrafficSignalControllerScenarioEventMapA
{
	str_t str;
	TrafficSignalControllerScenarioEvent v;
} TrafficSignalControllerScenarioEventMapA[] =
{
	{ (char *)"start", TrafficSignalControllerScenarioEvent_start },
	{ (char *)"auth", TrafficSignalControllerScenarioEvent_auth },
	{ (char *)"trigger", TrafficSignalControllerScenarioEvent_trigger },
	{ (char *)"data", TrafficSignalControllerScenarioEvent_data },
	{ (char *)"validate", TrafficSignalControllerScenarioEvent_validate },
	{ (char *)"disconnected", TrafficSignalControllerScenarioEvent_disconnected },
	{ NULL, TrafficSignalControllerScenarioEvent_max }
};

str_t TrafficSignalControllerScenarioEventStrA(TrafficSignalControllerScenarioEvent v)
{
	struct TrafficSignalControllerScenarioEventMapA *i = NULL;
	for (i = TrafficSignalControllerScenarioEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerScenarioEvent TrafficSignalControllerScenarioEventFromStrA(str_t str)
{
	struct TrafficSignalControllerScenarioEventMapA *i = NULL;
	for (i = TrafficSignalControllerScenarioEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerScenarioEvent_max;
}
#ifndef UNIX_SYSTEM
static struct TrafficSignalControllerScenarioEventMapW
{
	wstr_t str;
	TrafficSignalControllerScenarioEvent v;
} TrafficSignalControllerScenarioEventMapW[] =
{
	{ (wchar_t *)L"start", TrafficSignalControllerScenarioEvent_start },
	{ (wchar_t *)L"auth", TrafficSignalControllerScenarioEvent_auth },
	{ (wchar_t *)L"trigger", TrafficSignalControllerScenarioEvent_trigger },
	{ (wchar_t *)L"data", TrafficSignalControllerScenarioEvent_data },
	{ (wchar_t *)L"validate", TrafficSignalControllerScenarioEvent_validate },
	{ (wchar_t *)L"disconnected", TrafficSignalControllerScenarioEvent_disconnected },
	{ NULL, TrafficSignalControllerScenarioEvent_max }
};

wstr_t TrafficSignalControllerScenarioEventStrW(TrafficSignalControllerScenarioEvent v)
{
	struct TrafficSignalControllerScenarioEventMapW *i = NULL;
	for (i = TrafficSignalControllerScenarioEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerScenarioEvent TrafficSignalControllerScenarioEventFromStrW(wstr_t str)
{
	struct TrafficSignalControllerScenarioEventMapW *i = NULL;
	for (i = TrafficSignalControllerScenarioEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerScenarioEvent_max;
}
#endif // UNIX_SYSTEM

TrafficSignalControllerScenarioEvent *TrafficSignalControllerScenarioEvent_new(TrafficSignalControllerScenarioEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerScenarioEvent *__internal_ret = (TrafficSignalControllerScenarioEvent *)Dz1Calloc(sizeof(TrafficSignalControllerScenarioEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TrafficSignalControllerScenarioEvent_dump(TrafficSignalControllerScenarioEvent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TrafficSignalControllerScenarioEventStr(*v));
}
// TrafficSignalControllerScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerScenarioState
static struct TrafficSignalControllerScenarioStateMapA
{
	str_t str;
	TrafficSignalControllerScenarioState v;
} TrafficSignalControllerScenarioStateMapA[] =
{
	{ (char *)"initial", TrafficSignalControllerScenarioState_initial },
	{ (char *)"wait_test", TrafficSignalControllerScenarioState_wait_test },
	{ (char *)"complete", TrafficSignalControllerScenarioState_complete },
	{ NULL, TrafficSignalControllerScenarioState_max }
};

str_t TrafficSignalControllerScenarioStateStrA(TrafficSignalControllerScenarioState v)
{
	struct TrafficSignalControllerScenarioStateMapA *i = NULL;
	for (i = TrafficSignalControllerScenarioStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerScenarioState TrafficSignalControllerScenarioStateFromStrA(str_t str)
{
	struct TrafficSignalControllerScenarioStateMapA *i = NULL;
	for (i = TrafficSignalControllerScenarioStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerScenarioState_max;
}
#ifndef UNIX_SYSTEM
static struct TrafficSignalControllerScenarioStateMapW
{
	wstr_t str;
	TrafficSignalControllerScenarioState v;
} TrafficSignalControllerScenarioStateMapW[] =
{
	{ (wchar_t *)L"initial", TrafficSignalControllerScenarioState_initial },
	{ (wchar_t *)L"wait_test", TrafficSignalControllerScenarioState_wait_test },
	{ (wchar_t *)L"complete", TrafficSignalControllerScenarioState_complete },
	{ NULL, TrafficSignalControllerScenarioState_max }
};

wstr_t TrafficSignalControllerScenarioStateStrW(TrafficSignalControllerScenarioState v)
{
	struct TrafficSignalControllerScenarioStateMapW *i = NULL;
	for (i = TrafficSignalControllerScenarioStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerScenarioState TrafficSignalControllerScenarioStateFromStrW(wstr_t str)
{
	struct TrafficSignalControllerScenarioStateMapW *i = NULL;
	for (i = TrafficSignalControllerScenarioStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerScenarioState_max;
}
#endif // UNIX_SYSTEM

TrafficSignalControllerScenarioState *TrafficSignalControllerScenarioState_new(TrafficSignalControllerScenarioState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerScenarioState *__internal_ret = (TrafficSignalControllerScenarioState *)Dz1Calloc(sizeof(TrafficSignalControllerScenarioState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// TrafficSignalControllerScenarioState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestScenarioEnv
TrafficSignalControllerTestScenarioEnv *TrafficSignalControllerTestScenarioEnv_new(void *tSelf, 
																				   void *tMain, 
																				   Dz1JsonSpec *spec, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerTestScenarioEnv *__internal_ret = (TrafficSignalControllerTestScenarioEnv *)Dz1Calloc(sizeof(TrafficSignalControllerTestScenarioEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestScenarioEnv_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tSelf = tSelf;
		__internal_ret->tMain = tMain;
		__internal_ret->spec = spec;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestScenarioEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void TrafficSignalControllerTestScenarioEnv_purge(TrafficSignalControllerTestScenarioEnv *p)
{
	if (p == NULL) return;
	Dz1JsonSpec_del(p->spec);
	TrafficSignalControllerSession_del(p->session);
	TrafficSignalControllerScenario_del(p->scenario);
}

void TrafficSignalControllerTestScenarioEnv_del(TrafficSignalControllerTestScenarioEnv *p)
{
	if (p == NULL) return;
	TrafficSignalControllerTestScenarioEnv_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerTestScenarioEnv_dump(TrafficSignalControllerTestScenarioEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("tMain = %p\n"), p->tMain);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("spec = ")); Dz1JsonSpec_dump(p->spec, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("session = ")); TrafficSignalControllerSession_dump(p->session, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("scenario = ")); TrafficSignalControllerScenario_dump(p->scenario, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = ")); Dz1s32_dump(&p->state, tab); 
		Dz1Thread_tprintf(tab, Dz1T("flags = ")); Dz1u32_dump(&p->flags, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_run = ")); Dz1Bool_dump(&p->is_run, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_r29 = ")); Dz1Bool_dump(&p->is_r29, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerTestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

