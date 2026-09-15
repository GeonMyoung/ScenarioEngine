////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorEnv.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorClientSession
GitsnDsrcEmulatorClientSession *GitsnDsrcEmulatorClientSession_new(Dz1SockAddr *peer, 
																   Dz1SockAddr *local, 
																   Dz1TcpClientSocket *sock, 
																   Dz1ElasticBuf *rx_buf, 
																   Dz1Stream *rx_stream, 
																   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorClientSession *__internal_ret = (GitsnDsrcEmulatorClientSession *)Dz1Calloc(sizeof(GitsnDsrcEmulatorClientSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorClientSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDsrcEmulatorClientSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDsrcEmulatorClientSession_purge(GitsnDsrcEmulatorClientSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void GitsnDsrcEmulatorClientSession_del(GitsnDsrcEmulatorClientSession *p)
{
	if (p == NULL) return;
	GitsnDsrcEmulatorClientSession_purge(p);
	Dz1Free(p);
}

void GitsnDsrcEmulatorClientSession_dump(GitsnDsrcEmulatorClientSession *p, int tab)
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
int GitsnDsrcEmulatorClientSession_cmp(GitsnDsrcEmulatorClientSession *a, GitsnDsrcEmulatorClientSession *b)
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
// GitsnDsrcEmulatorClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorServerSession
GitsnDsrcEmulatorServerSession *GitsnDsrcEmulatorServerSession_new(u32_t acceptor, 
																   Dz1SockAddr *peer, 
																   Dz1SockAddr *local, 
																   Dz1TcpClientSocket *sock, 
																   Dz1ElasticBuf *rx_buf, 
																   Dz1Stream *rx_stream, 
																   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorServerSession *__internal_ret = (GitsnDsrcEmulatorServerSession *)Dz1Calloc(sizeof(GitsnDsrcEmulatorServerSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorServerSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->acceptor = acceptor;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->rx_stream = rx_stream;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDsrcEmulatorServerSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDsrcEmulatorServerSession_purge(GitsnDsrcEmulatorServerSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->rx_buf);
	Dz1Stream_del(p->rx_stream);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void GitsnDsrcEmulatorServerSession_del(GitsnDsrcEmulatorServerSession *p)
{
	if (p == NULL) return;
	GitsnDsrcEmulatorServerSession_purge(p);
	Dz1Free(p);
}

void GitsnDsrcEmulatorServerSession_dump(GitsnDsrcEmulatorServerSession *p, int tab)
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
int GitsnDsrcEmulatorServerSession_cmp(GitsnDsrcEmulatorServerSession *a, GitsnDsrcEmulatorServerSession *b)
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
// GitsnDsrcEmulatorServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorSessionPresent
static struct GitsnDsrcEmulatorSessionPresentMapA
{
	str_t str;
	GitsnDsrcEmulatorSessionPresent v;
} GitsnDsrcEmulatorSessionPresentMapA[] =
{
	{ (char *)"client", GitsnDsrcEmulatorSessionPresent_client },
	{ (char *)"server", GitsnDsrcEmulatorSessionPresent_server },
	{ NULL, GitsnDsrcEmulatorSessionPresent_max }
};

str_t GitsnDsrcEmulatorSessionPresentStrA(GitsnDsrcEmulatorSessionPresent v)
{
	struct GitsnDsrcEmulatorSessionPresentMapA *i = NULL;
	for (i = GitsnDsrcEmulatorSessionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDsrcEmulatorSessionPresent GitsnDsrcEmulatorSessionPresentFromStrA(str_t str)
{
	struct GitsnDsrcEmulatorSessionPresentMapA *i = NULL;
	for (i = GitsnDsrcEmulatorSessionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnDsrcEmulatorSessionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnDsrcEmulatorSessionPresentMapW
{
	wstr_t str;
	GitsnDsrcEmulatorSessionPresent v;
} GitsnDsrcEmulatorSessionPresentMapW[] =
{
	{ (wchar_t *)L"client", GitsnDsrcEmulatorSessionPresent_client },
	{ (wchar_t *)L"server", GitsnDsrcEmulatorSessionPresent_server },
	{ NULL, GitsnDsrcEmulatorSessionPresent_max }
};

wstr_t GitsnDsrcEmulatorSessionPresentStrW(GitsnDsrcEmulatorSessionPresent v)
{
	struct GitsnDsrcEmulatorSessionPresentMapW *i = NULL;
	for (i = GitsnDsrcEmulatorSessionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnDsrcEmulatorSessionPresent GitsnDsrcEmulatorSessionPresentFromStrW(wstr_t str)
{
	struct GitsnDsrcEmulatorSessionPresentMapW *i = NULL;
	for (i = GitsnDsrcEmulatorSessionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnDsrcEmulatorSessionPresent_max;
}
#endif // UNIX_SYSTEM

GitsnDsrcEmulatorSessionPresent *GitsnDsrcEmulatorSessionPresent_new(GitsnDsrcEmulatorSessionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorSessionPresent *__internal_ret = (GitsnDsrcEmulatorSessionPresent *)Dz1Calloc(sizeof(GitsnDsrcEmulatorSessionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void GitsnDsrcEmulatorSessionPresent_dump(GitsnDsrcEmulatorSessionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), GitsnDsrcEmulatorSessionPresentStr(*v));
}

int GitsnDsrcEmulatorSessionPresent_cmp(GitsnDsrcEmulatorSessionPresent *a, GitsnDsrcEmulatorSessionPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// GitsnDsrcEmulatorSessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorSession
GitsnDsrcEmulatorSession *GitsnDsrcEmulatorSession_new(GitsnDsrcEmulatorSessionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorSession *ret = (GitsnDsrcEmulatorSession *)Dz1Calloc(sizeof(GitsnDsrcEmulatorSession), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorSession_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case GitsnDsrcEmulatorSessionPresent_client:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client = (GitsnDsrcEmulatorClientSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnDsrcEmulatorSessionPresent_server:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server = (GitsnDsrcEmulatorServerSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnDsrcEmulatorSessionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDsrcEmulatorSession_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnDsrcEmulatorSession_purge(GitsnDsrcEmulatorSession *p)
{
	if (!p) return;
	switch(p->present)
	{
	case GitsnDsrcEmulatorSessionPresent_client:
		GitsnDsrcEmulatorClientSession_del(p->x.client);
		break;
	case GitsnDsrcEmulatorSessionPresent_server:
		GitsnDsrcEmulatorServerSession_del(p->x.server);
		break;
	default:
		break;
	}
}

void GitsnDsrcEmulatorSession_del(GitsnDsrcEmulatorSession *p)
{
	if (!p) return;
	GitsnDsrcEmulatorSession_purge(p);
	Dz1Free(p);
}

void GitsnDsrcEmulatorSession_dump(GitsnDsrcEmulatorSession *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case GitsnDsrcEmulatorSessionPresent_client:
		Dz1Thread_printf(Dz1T("client = ")); GitsnDsrcEmulatorClientSession_dump(p->x.client, tab); 
		break;
	case GitsnDsrcEmulatorSessionPresent_server:
		Dz1Thread_printf(Dz1T("server = ")); GitsnDsrcEmulatorServerSession_dump(p->x.server, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int GitsnDsrcEmulatorSession_cmp(GitsnDsrcEmulatorSession *a, GitsnDsrcEmulatorSession *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL && b != NULL) ret = -1;
	else if (a != NULL && b == NULL) ret = 1;
	else if (a->present != b->present) ret = (int)(a->present - b->present);
	else
	{
		switch(a->present)
		{
		case GitsnDsrcEmulatorSessionPresent_client:
			if (a->x.client == NULL && b->x.client == NULL) ret = 0;
			else if (a->x.client == NULL /*&& b->x.client != NULL*/) ret = -1;
			else if (/*a->x.client != NULL &&*/ b->x.client == NULL) ret = 1;
			else if ((ret = GitsnDsrcEmulatorClientSession_cmp(a->x.client, b->x.client)) != 0) { }
			break;
		case GitsnDsrcEmulatorSessionPresent_server:
			if (a->x.server == NULL && b->x.server == NULL) ret = 0;
			else if (a->x.server == NULL /*&& b->x.server != NULL*/) ret = -1;
			else if (/*a->x.server != NULL &&*/ b->x.server == NULL) ret = 1;
			else if ((ret = GitsnDsrcEmulatorServerSession_cmp(a->x.server, b->x.server)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// GitsnDsrcEmulatorSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorEnv
GitsnDsrcEmulatorEnv *GitsnDsrcEmulatorEnv_new(void *tSelf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorEnv *__internal_ret = (GitsnDsrcEmulatorEnv *)Dz1Calloc(sizeof(GitsnDsrcEmulatorEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorEnv_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tSelf = tSelf;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDsrcEmulatorEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDsrcEmulatorEnv_purge(GitsnDsrcEmulatorEnv *p)
{
	if (p == NULL) return;
	GitsnDsrcEmulatorSession_del(p->session);
}

void GitsnDsrcEmulatorEnv_del(GitsnDsrcEmulatorEnv *p)
{
	if (p == NULL) return;
	GitsnDsrcEmulatorEnv_purge(p);
	Dz1Free(p);
}

void GitsnDsrcEmulatorEnv_dump(GitsnDsrcEmulatorEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("session.")); GitsnDsrcEmulatorSession_dump(p->session, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnDsrcEmulatorEnv
////////////////////////////////////////////////////////////////////////////////

