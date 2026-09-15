////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDSRCMsgTestScenarioEnv.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgClientSession
GitsnDSRCMsgClientSession *GitsnDSRCMsgClientSession_new(Dz1SockAddr *peer, 
														 Dz1SockAddr *local, 
														 Dz1TcpClientSocket *sock, 
														 Dz1ElasticBuf *rx_buf, 
														 Dz1Stream *rx_stream, 
														 Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgClientSession *__internal_ret = (GitsnDSRCMsgClientSession *)Dz1Calloc(sizeof(GitsnDSRCMsgClientSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgClientSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgClientSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDSRCMsgClientSession_purge(GitsnDSRCMsgClientSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void GitsnDSRCMsgClientSession_del(GitsnDSRCMsgClientSession *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgClientSession_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgClientSession_dump(GitsnDSRCMsgClientSession *p, int tab)
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
int GitsnDSRCMsgClientSession_cmp(GitsnDSRCMsgClientSession *a, GitsnDSRCMsgClientSession *b)
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
// GitsnDSRCMsgClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgServerSession
GitsnDSRCMsgServerSession *GitsnDSRCMsgServerSession_new(u32_t acceptor, 
														 Dz1SockAddr *peer, 
														 Dz1SockAddr *local, 
														 Dz1TcpClientSocket *sock, 
														 Dz1ElasticBuf *rx_buf, 
														 Dz1Stream *rx_stream, 
														 Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgServerSession *__internal_ret = (GitsnDSRCMsgServerSession *)Dz1Calloc(sizeof(GitsnDSRCMsgServerSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgServerSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->acceptor = acceptor;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgServerSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDSRCMsgServerSession_purge(GitsnDSRCMsgServerSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void GitsnDSRCMsgServerSession_del(GitsnDSRCMsgServerSession *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgServerSession_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgServerSession_dump(GitsnDSRCMsgServerSession *p, int tab)
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
int GitsnDSRCMsgServerSession_cmp(GitsnDSRCMsgServerSession *a, GitsnDSRCMsgServerSession *b)
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
// GitsnDSRCMsgServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgSessionPresent
static struct GitsnDSRCMsgSessionPresentMapA
{
	str_t str;
	GitsnDSRCMsgSessionPresent v;
} GitsnDSRCMsgSessionPresentMapA[] =
{
	{ (char *)"client", GitsnDSRCMsgSessionPresent_client },
	{ (char *)"server", GitsnDSRCMsgSessionPresent_server },
	{ NULL, GitsnDSRCMsgSessionPresent_max }
};

str_t GitsnDSRCMsgSessionPresentStrA(GitsnDSRCMsgSessionPresent v)
{
	struct GitsnDSRCMsgSessionPresentMapA *i = NULL;
	for (i = GitsnDSRCMsgSessionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgSessionPresent GitsnDSRCMsgSessionPresentFromStrA(str_t str)
{
	struct GitsnDSRCMsgSessionPresentMapA *i = NULL;
	for (i = GitsnDSRCMsgSessionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgSessionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnDSRCMsgSessionPresentMapW
{
	wstr_t str;
	GitsnDSRCMsgSessionPresent v;
} GitsnDSRCMsgSessionPresentMapW[] =
{
	{ (wchar_t *)L"client", GitsnDSRCMsgSessionPresent_client },
	{ (wchar_t *)L"server", GitsnDSRCMsgSessionPresent_server },
	{ NULL, GitsnDSRCMsgSessionPresent_max }
};

wstr_t GitsnDSRCMsgSessionPresentStrW(GitsnDSRCMsgSessionPresent v)
{
	struct GitsnDSRCMsgSessionPresentMapW *i = NULL;
	for (i = GitsnDSRCMsgSessionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgSessionPresent GitsnDSRCMsgSessionPresentFromStrW(wstr_t str)
{
	struct GitsnDSRCMsgSessionPresentMapW *i = NULL;
	for (i = GitsnDSRCMsgSessionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgSessionPresent_max;
}
#endif // UNIX_SYSTEM

GitsnDSRCMsgSessionPresent *GitsnDSRCMsgSessionPresent_new(GitsnDSRCMsgSessionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgSessionPresent *__internal_ret = (GitsnDSRCMsgSessionPresent *)Dz1Calloc(sizeof(GitsnDSRCMsgSessionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void GitsnDSRCMsgSessionPresent_dump(GitsnDSRCMsgSessionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), GitsnDSRCMsgSessionPresentStr(*v));
}
// GitsnDSRCMsgSessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgSession
GitsnDSRCMsgSession *GitsnDSRCMsgSession_new(GitsnDSRCMsgSessionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgSession *ret = (GitsnDSRCMsgSession *)Dz1Calloc(sizeof(GitsnDSRCMsgSession), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgSession_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case GitsnDSRCMsgSessionPresent_client:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client = (GitsnDSRCMsgClientSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnDSRCMsgSessionPresent_server:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server = (GitsnDSRCMsgServerSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnDSRCMsgSessionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgSession_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnDSRCMsgSession_purge(GitsnDSRCMsgSession *p)
{
	if (!p) return;
	switch(p->present)
	{
	case GitsnDSRCMsgSessionPresent_client:
		GitsnDSRCMsgClientSession_del(p->x.client);
		break;
	case GitsnDSRCMsgSessionPresent_server:
		GitsnDSRCMsgServerSession_del(p->x.server);
		break;
	default:
		break;
	}
}

void GitsnDSRCMsgSession_del(GitsnDSRCMsgSession *p)
{
	if (!p) return;
	GitsnDSRCMsgSession_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgSession_dump(GitsnDSRCMsgSession *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case GitsnDSRCMsgSessionPresent_client:
		Dz1Thread_printf(Dz1T("client = ")); GitsnDSRCMsgClientSession_dump(p->x.client, tab); 
		break;
	case GitsnDSRCMsgSessionPresent_server:
		Dz1Thread_printf(Dz1T("server = ")); GitsnDSRCMsgServerSession_dump(p->x.server, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// GitsnDSRCMsgSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgScenario
GitsnDSRCMsgScenario *GitsnDSRCMsgScenario_new(u16_t local_port, 
											   bool_t test_map, 
											   bool_t test_spat, 
											   bool_t test_bsm, 
											   bool_t test_eva, 
											   bool_t test_pvd, 
											   bool_t test_rsa, 
											   bool_t test_rtcm, 
											   bool_t test_srm, 
											   bool_t test_ssm, 
											   bool_t test_tim, 
											   bool_t test_psm, 
											   bool_t test_sdsm, 
											   bool_t test_tls, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgScenario *__internal_ret = (GitsnDSRCMsgScenario *)Dz1Calloc(sizeof(GitsnDSRCMsgScenario), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgScenario_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->test_map = test_map;
		__internal_ret->test_spat = test_spat;
		__internal_ret->test_bsm = test_bsm;
		__internal_ret->test_eva = test_eva;
		__internal_ret->test_pvd = test_pvd;
		__internal_ret->test_rsa = test_rsa;
		__internal_ret->test_rtcm = test_rtcm;
		__internal_ret->test_srm = test_srm;
		__internal_ret->test_ssm = test_ssm;
		__internal_ret->test_tim = test_tim;
		__internal_ret->test_psm = test_psm;
		__internal_ret->test_sdsm = test_sdsm;
		__internal_ret->test_tls = test_tls;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgScenario_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnDSRCMsgScenario_copy(GitsnDSRCMsgScenario *dst, GitsnDSRCMsgScenario *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->local_port = src->local_port;
		dst->test_map = src->test_map;
		dst->test_spat = src->test_spat;
		dst->test_bsm = src->test_bsm;
		dst->test_eva = src->test_eva;
		dst->test_pvd = src->test_pvd;
		dst->test_rsa = src->test_rsa;
		dst->test_rtcm = src->test_rtcm;
		dst->test_srm = src->test_srm;
		dst->test_ssm = src->test_ssm;
		dst->test_tim = src->test_tim;
		dst->test_psm = src->test_psm;
		dst->test_sdsm = src->test_sdsm;
		dst->test_tls = src->test_tls;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnDSRCMsgScenario *GitsnDSRCMsgScenario_clone(GitsnDSRCMsgScenario *src, Dz1Error *err)
{
	GitsnDSRCMsgScenario *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnDSRCMsgScenario *)Dz1Calloc(sizeof(GitsnDSRCMsgScenario), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgScenario_delAndSetNull, (void *)&dst);
		if (GitsnDSRCMsgScenario_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgScenario_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnDSRCMsgScenario_purge(GitsnDSRCMsgScenario *p)
{
	if (p == NULL) return;
}

void GitsnDSRCMsgScenario_del(GitsnDSRCMsgScenario *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgScenario_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgScenario_dump(GitsnDSRCMsgScenario *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1u16_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_spat = ")); Dz1Bool_dump(&p->test_spat, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_bsm = ")); Dz1Bool_dump(&p->test_bsm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_eva = ")); Dz1Bool_dump(&p->test_eva, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pvd = ")); Dz1Bool_dump(&p->test_pvd, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsa = ")); Dz1Bool_dump(&p->test_rsa, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rtcm = ")); Dz1Bool_dump(&p->test_rtcm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_srm = ")); Dz1Bool_dump(&p->test_srm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_ssm = ")); Dz1Bool_dump(&p->test_ssm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tim = ")); Dz1Bool_dump(&p->test_tim, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_psm = ")); Dz1Bool_dump(&p->test_psm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sdsm = ")); Dz1Bool_dump(&p->test_sdsm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tls = ")); Dz1Bool_dump(&p->test_tls, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgScenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgScenarioEvent
static struct GitsnDSRCMsgScenarioEventMapA
{
	str_t str;
	GitsnDSRCMsgScenarioEvent v;
} GitsnDSRCMsgScenarioEventMapA[] =
{
	{ (char *)"start", GitsnDSRCMsgScenarioEvent_start },
	{ (char *)"auth", GitsnDSRCMsgScenarioEvent_auth },
	{ (char *)"trigger", GitsnDSRCMsgScenarioEvent_trigger },
	{ (char *)"data", GitsnDSRCMsgScenarioEvent_data },
	{ (char *)"validate", GitsnDSRCMsgScenarioEvent_validate },
	{ (char *)"disconnected", GitsnDSRCMsgScenarioEvent_disconnected },
	{ NULL, GitsnDSRCMsgScenarioEvent_max }
};

str_t GitsnDSRCMsgScenarioEventStrA(GitsnDSRCMsgScenarioEvent v)
{
	struct GitsnDSRCMsgScenarioEventMapA *i = NULL;
	for (i = GitsnDSRCMsgScenarioEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgScenarioEvent GitsnDSRCMsgScenarioEventFromStrA(str_t str)
{
	struct GitsnDSRCMsgScenarioEventMapA *i = NULL;
	for (i = GitsnDSRCMsgScenarioEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgScenarioEvent_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnDSRCMsgScenarioEventMapW
{
	wstr_t str;
	GitsnDSRCMsgScenarioEvent v;
} GitsnDSRCMsgScenarioEventMapW[] =
{
	{ (wchar_t *)L"start", GitsnDSRCMsgScenarioEvent_start },
	{ (wchar_t *)L"auth", GitsnDSRCMsgScenarioEvent_auth },
	{ (wchar_t *)L"trigger", GitsnDSRCMsgScenarioEvent_trigger },
	{ (wchar_t *)L"data", GitsnDSRCMsgScenarioEvent_data },
	{ (wchar_t *)L"validate", GitsnDSRCMsgScenarioEvent_validate },
	{ (wchar_t *)L"disconnected", GitsnDSRCMsgScenarioEvent_disconnected },
	{ NULL, GitsnDSRCMsgScenarioEvent_max }
};

wstr_t GitsnDSRCMsgScenarioEventStrW(GitsnDSRCMsgScenarioEvent v)
{
	struct GitsnDSRCMsgScenarioEventMapW *i = NULL;
	for (i = GitsnDSRCMsgScenarioEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgScenarioEvent GitsnDSRCMsgScenarioEventFromStrW(wstr_t str)
{
	struct GitsnDSRCMsgScenarioEventMapW *i = NULL;
	for (i = GitsnDSRCMsgScenarioEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgScenarioEvent_max;
}
#endif // UNIX_SYSTEM

GitsnDSRCMsgScenarioEvent *GitsnDSRCMsgScenarioEvent_new(GitsnDSRCMsgScenarioEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgScenarioEvent *__internal_ret = (GitsnDSRCMsgScenarioEvent *)Dz1Calloc(sizeof(GitsnDSRCMsgScenarioEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void GitsnDSRCMsgScenarioEvent_dump(GitsnDSRCMsgScenarioEvent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), GitsnDSRCMsgScenarioEventStr(*v));
}
// GitsnDSRCMsgScenarioEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgScenarioState
static struct GitsnDSRCMsgScenarioStateMapA
{
	str_t str;
	GitsnDSRCMsgScenarioState v;
} GitsnDSRCMsgScenarioStateMapA[] =
{
	{ (char *)"initial", GitsnDSRCMsgScenarioState_initial },
	{ (char *)"wait_data", GitsnDSRCMsgScenarioState_wait_data },
	{ (char *)"complete", GitsnDSRCMsgScenarioState_complete },
	{ NULL, GitsnDSRCMsgScenarioState_max }
};

str_t GitsnDSRCMsgScenarioStateStrA(GitsnDSRCMsgScenarioState v)
{
	struct GitsnDSRCMsgScenarioStateMapA *i = NULL;
	for (i = GitsnDSRCMsgScenarioStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgScenarioState GitsnDSRCMsgScenarioStateFromStrA(str_t str)
{
	struct GitsnDSRCMsgScenarioStateMapA *i = NULL;
	for (i = GitsnDSRCMsgScenarioStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgScenarioState_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnDSRCMsgScenarioStateMapW
{
	wstr_t str;
	GitsnDSRCMsgScenarioState v;
} GitsnDSRCMsgScenarioStateMapW[] =
{
	{ (wchar_t *)L"initial", GitsnDSRCMsgScenarioState_initial },
	{ (wchar_t *)L"wait_data", GitsnDSRCMsgScenarioState_wait_data },
	{ (wchar_t *)L"complete", GitsnDSRCMsgScenarioState_complete },
	{ NULL, GitsnDSRCMsgScenarioState_max }
};

wstr_t GitsnDSRCMsgScenarioStateStrW(GitsnDSRCMsgScenarioState v)
{
	struct GitsnDSRCMsgScenarioStateMapW *i = NULL;
	for (i = GitsnDSRCMsgScenarioStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDSRCMsgScenarioState GitsnDSRCMsgScenarioStateFromStrW(wstr_t str)
{
	struct GitsnDSRCMsgScenarioStateMapW *i = NULL;
	for (i = GitsnDSRCMsgScenarioStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnDSRCMsgScenarioState_max;
}
#endif // UNIX_SYSTEM

GitsnDSRCMsgScenarioState *GitsnDSRCMsgScenarioState_new(GitsnDSRCMsgScenarioState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgScenarioState *__internal_ret = (GitsnDSRCMsgScenarioState *)Dz1Calloc(sizeof(GitsnDSRCMsgScenarioState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void GitsnDSRCMsgScenarioState_dump(GitsnDSRCMsgScenarioState *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), GitsnDSRCMsgScenarioStateStr(*v));
}
// GitsnDSRCMsgScenarioState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestScenarioEnv
GitsnDSRCMsgTestScenarioEnv *GitsnDSRCMsgTestScenarioEnv_new(void *tSelf, 
															 void *tMain, 
															 Dz1JsonSpec *spec, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDSRCMsgTestScenarioEnv *__internal_ret = (GitsnDSRCMsgTestScenarioEnv *)Dz1Calloc(sizeof(GitsnDSRCMsgTestScenarioEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgTestScenarioEnv_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->dfs = GitsnTestDataFrames_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tSelf = tSelf;
			__internal_ret->tMain = tMain;
			__internal_ret->spec = spec;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDSRCMsgTestScenarioEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDSRCMsgTestScenarioEnv_purge(GitsnDSRCMsgTestScenarioEnv *p)
{
	if (p == NULL) return;
	Dz1JsonSpec_del(p->spec);
	GitsnDSRCMsgSession_del(p->session);
	GitsnDSRCMsgScenario_del(p->scenario);
	GitsnTestDataFrames_del(p->dfs);
	Dz1Str_del(p->current_test);
}

void GitsnDSRCMsgTestScenarioEnv_del(GitsnDSRCMsgTestScenarioEnv *p)
{
	if (p == NULL) return;
	GitsnDSRCMsgTestScenarioEnv_purge(p);
	Dz1Free(p);
}

void GitsnDSRCMsgTestScenarioEnv_dump(GitsnDSRCMsgTestScenarioEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("tMain = %p\n"), p->tMain);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("spec = ")); Dz1JsonSpec_dump(p->spec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("session.")); GitsnDSRCMsgSession_dump(p->session, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("scenario = ")); GitsnDSRCMsgScenario_dump(p->scenario, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_run = ")); Dz1Bool_dump(&p->is_run, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = ")); Dz1s32_dump(&p->state, tab); 
		Dz1Thread_tprintf(tab, Dz1T("flags = ")); Dz1u32_dump(&p->flags, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dfs = ")); GitsnTestDataFrames_dump(p->dfs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("current_test = ")); Dz1Str_dump(p->current_test, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDSRCMsgTestScenarioEnv
////////////////////////////////////////////////////////////////////////////////

