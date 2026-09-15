#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "Dz1TcpCallbackClientEnv.h"

static struct Dz1TcpCallbackSessionLifeMapA
{
	str_t str;
	Dz1TcpCallbackSessionLife v;
} Dz1TcpCallbackSessionLifeMapA[] =
{
	{ "immediateDie", Dz1TcpCallbackSessionLife_immediateDie },
	{ "negotiationAndDie", Dz1TcpCallbackSessionLife_negotiationAndDie },
	{ "sendAndDie", Dz1TcpCallbackSessionLife_sendAndDie },
	{ "tenSecond", Dz1TcpCallbackSessionLife_tenSecond },
	{ "halfHour", Dz1TcpCallbackSessionLife_halfHour },
	{ "immotal0", Dz1TcpCallbackSessionLife_immotal0 },
	{ "immotal1", Dz1TcpCallbackSessionLife_immotal1 },
	{ "immotal2", Dz1TcpCallbackSessionLife_immotal2 },
	{ "immotal3", Dz1TcpCallbackSessionLife_immotal3 },
	{ "immotal4", Dz1TcpCallbackSessionLife_immotal4 },
	{ "immotal5", Dz1TcpCallbackSessionLife_immotal5 },
	{ NULL, Dz1TcpCallbackSessionLife_max }
};

str_t Dz1TcpCallbackSessionLifeStrA(Dz1TcpCallbackSessionLife v)
{
	struct Dz1TcpCallbackSessionLifeMapA *i = NULL;
	for (i = Dz1TcpCallbackSessionLifeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpCallbackSessionLife Dz1TcpCallbackSessionLifeFromStrA(str_t str)
{
	struct Dz1TcpCallbackSessionLifeMapA *i = NULL;
	for (i = Dz1TcpCallbackSessionLifeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1TcpCallbackSessionLife_max;
}

static struct Dz1TcpCallbackSessionLifeMapW
{
	wstr_t str;
	Dz1TcpCallbackSessionLife v;
} Dz1TcpCallbackSessionLifeMapW[] =
{
	{ L"immediateDie", Dz1TcpCallbackSessionLife_immediateDie },
	{ L"negotiationAndDie", Dz1TcpCallbackSessionLife_negotiationAndDie },
	{ L"sendAndDie", Dz1TcpCallbackSessionLife_sendAndDie },
	{ L"tenSecond", Dz1TcpCallbackSessionLife_tenSecond },
	{ L"halfHour", Dz1TcpCallbackSessionLife_halfHour },
	{ L"immotal0", Dz1TcpCallbackSessionLife_immotal0 },
	{ L"immotal1", Dz1TcpCallbackSessionLife_immotal1 },
	{ L"immotal2", Dz1TcpCallbackSessionLife_immotal2 },
	{ L"immotal3", Dz1TcpCallbackSessionLife_immotal3 },
	{ L"immotal4", Dz1TcpCallbackSessionLife_immotal4 },
	{ L"immotal5", Dz1TcpCallbackSessionLife_immotal5 },
	{ NULL, Dz1TcpCallbackSessionLife_max }
};

wstr_t Dz1TcpCallbackSessionLifeStrW(Dz1TcpCallbackSessionLife v)
{
	struct Dz1TcpCallbackSessionLifeMapW *i = NULL;
	for (i = Dz1TcpCallbackSessionLifeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TcpCallbackSessionLife Dz1TcpCallbackSessionLifeFromStrW(wstr_t str)
{
	struct Dz1TcpCallbackSessionLifeMapW *i = NULL;
	for (i = Dz1TcpCallbackSessionLifeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1TcpCallbackSessionLife_max;
}

Dz1TcpCallbackSessionLife *Dz1TcpCallbackSessionLife_new(Dz1TcpCallbackSessionLife *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackSessionLife *__internal_ret = (Dz1TcpCallbackSessionLife *)Dz1Calloc(sizeof(Dz1TcpCallbackSessionLife), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1TcpCallbackSessionLife_dump(Dz1TcpCallbackSessionLife *v, int tab)
{
	if (v == NULL) Dz1Thread_printf("NULL\n");
	else Dz1Thread_printf("%s\n", Dz1TcpCallbackSessionLifeStrA(*v));
}

Dz1TcpCallbackSession *Dz1TcpCallbackSession_new(Dz1SockAddr *peer, 
												 Dz1SockAddr *local, 
												 Dz1TcpClientSocket *sock, 
												 Dz1SocketBuf *rx_buf, 
												 Dz1SocketFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackSession *__internal_ret = (Dz1TcpCallbackSession *)Dz1Calloc(sizeof(Dz1TcpCallbackSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackSession_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->rx_buf = rx_buf;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackSession_del(Dz1TcpCallbackSession *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	if (p->sock) Dz1TcpClientSocket_del(p->sock);
	if (p->rx_buf) Dz1SocketBuf_del(p->rx_buf);
	if (p->tx_fifo) Dz1SocketFifo_del(p->tx_fifo);
	Dz1Free(p);
}

void Dz1TcpCallbackSession_dump(Dz1TcpCallbackSession *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, "peer = NULL\n");
	else { Dz1Thread_tprintf(tab, "peer = "); Dz1SockAddr_dump(p->peer, tab); }

	if (p->local == NULL) Dz1Thread_tprintf(tab, "local = NULL\n");
	else { Dz1Thread_tprintf(tab, "local = "); Dz1SockAddr_dump(p->local, tab); }

	if (p->sock == NULL) Dz1Thread_tprintf(tab, "sock = NULL\n");
	else { Dz1Thread_tprintf(tab, "sock = %p\n", p->sock); }

	if (p->rx_buf == NULL) Dz1Thread_tprintf(tab, "rx_buf = NULL\n");
	else { Dz1Thread_tprintf(tab, "rx_buf = "); Dz1SocketBuf_dump(p->rx_buf, tab); }

	if (p->tx_fifo == NULL) Dz1Thread_tprintf(tab, "tx_fifo = NULL\n");
	else { Dz1Thread_tprintf(tab, "tx_fifo = "); Dz1SocketFifo_dump(p->tx_fifo, tab); }

	Dz1Thread_tprintf(tab, "echoID = "); Dz1u32_dump(&p->echoID, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1TcpCallbackSession_cmp(Dz1TcpCallbackSession *a, Dz1TcpCallbackSession *b)
{
	int ret = 0;
	if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) return ret;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1TcpCallbackSessionList_add(Dz1TcpCallbackSessionList *p, Dz1TcpCallbackSession *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static void Dz1TcpCallbackSessionList_remove(Dz1TcpCallbackSessionList *p, Dz1TcpCallbackSession *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1TcpCallbackSession *Dz1TcpCallbackSessionList_extract(Dz1TcpCallbackSessionList *p, Dz1TcpCallbackSession *key)
{
	return (Dz1TcpCallbackSession *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TcpCallbackSessionListMkArrArg
{
	Dz1TcpCallbackSession **arr;
	unsigned int idx;
} Dz1TcpCallbackSessionListMkArrArg;

static Dz1Error _Dz1TcpCallbackSessionList_get_array(void *ptr, Dz1TcpCallbackSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpCallbackSessionListMkArrArg *arg = (Dz1TcpCallbackSessionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TcpCallbackSession **Dz1TcpCallbackSessionList_get_array(Dz1TcpCallbackSessionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TcpCallbackSession **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TcpCallbackSession **)Dz1Calloc(sizeof(Dz1TcpCallbackSession *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpCallbackSessionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1TcpCallbackSessionList_delAndSetNull, (void *)&ret);

		*errp = p->travel(p, _Dz1TcpCallbackSessionList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error Dz1TcpCallbackSessionList_travelForward(Dz1TcpCallbackSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpCallbackSession *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TcpCallbackSessionList_travelBackward(Dz1TcpCallbackSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpCallbackSession *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TcpCallbackSession *Dz1TcpCallbackSessionList_find(Dz1TcpCallbackSessionList *p, Dz1TcpCallbackSession *key)
{
	return (Dz1TcpCallbackSession *)Dz1AATree_find(p->storage, key);
}

static Dz1TcpCallbackSession *Dz1TcpCallbackSessionList_getHead(Dz1TcpCallbackSessionList *p)
{
	return (Dz1TcpCallbackSession *)Dz1AATree_getHead(p->storage);
}

static unsigned int Dz1TcpCallbackSessionList_count(Dz1TcpCallbackSessionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

void _Dz1TcpCallbackSessionList_dump(Dz1TcpCallbackSession *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "entry = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "entry = ");
		Dz1TcpCallbackSession_dump(p, tab);
	}
}

Dz1TcpCallbackSessionList *Dz1TcpCallbackSessionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackSessionList *ret = (Dz1TcpCallbackSessionList *)Dz1Calloc(sizeof(Dz1TcpCallbackSessionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackSessionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TcpCallbackSession_cmp,
				(Dz1DelFunc)Dz1TcpCallbackSession_del,
				(Dz1DumpFunc)_Dz1TcpCallbackSessionList_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1TcpCallbackSessionList_add;
			ret->remove = Dz1TcpCallbackSessionList_remove;
			ret->extract = Dz1TcpCallbackSessionList_extract;
			ret->get_array = Dz1TcpCallbackSessionList_get_array;
			ret->travel = Dz1TcpCallbackSessionList_travelForward;
			ret->travelForward = Dz1TcpCallbackSessionList_travelForward;
			ret->travelBackward = Dz1TcpCallbackSessionList_travelBackward;
			ret->find = Dz1TcpCallbackSessionList_find;
			ret->getHead = Dz1TcpCallbackSessionList_getHead;
			ret->count = Dz1TcpCallbackSessionList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpCallbackSessionList_del(Dz1TcpCallbackSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

void Dz1TcpCallbackSessionList_dump(Dz1TcpCallbackSessionList *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->storage)
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1AATree_dump(p->storage, tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

Dz1TcpCallbackClientCmd *Dz1TcpCallbackClientCmd_new(Dz1SockAddr *server_addr, 
													 u32_t max_conn, 
													 bool_t use_ssl, 
													 bool_t stress_mode, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackClientCmd *__internal_ret = (Dz1TcpCallbackClientCmd *)Dz1Calloc(sizeof(Dz1TcpCallbackClientCmd), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientCmd_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->server_addr = server_addr;
		__internal_ret->max_conn = max_conn;
		__internal_ret->use_ssl = use_ssl;
		__internal_ret->stress_mode = stress_mode;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientCmd_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpCallbackClientCmd *Dz1TcpCallbackClientCmd_clone(Dz1TcpCallbackClientCmd *src, Dz1Error *err)
{
	Dz1TcpCallbackClientCmd *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpCallbackClientCmd *)Dz1Calloc(sizeof(Dz1TcpCallbackClientCmd), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientCmd_delAndSetNull, (void *)&ret);

		if (src->server_addr && (ret->server_addr = Dz1SockAddr_clone(src->server_addr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->max_conn = src->max_conn;
			ret->use_ssl = src->use_ssl;
			ret->stress_mode = src->stress_mode;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientCmd_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpCallbackClientCmd_del(Dz1TcpCallbackClientCmd *p)
{
	if (p == NULL) return;
	if (p->server_addr) Dz1SockAddr_del(p->server_addr);
	Dz1Free(p);
}

void Dz1TcpCallbackClientCmd_dump(Dz1TcpCallbackClientCmd *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->server_addr == NULL) Dz1Thread_tprintf(tab, "server_addr = NULL\n");
	else { Dz1Thread_tprintf(tab, "server_addr = "); Dz1SockAddr_dump(p->server_addr, tab); }

	Dz1Thread_tprintf(tab, "max_conn = "); Dz1u32_dump(&p->max_conn, tab);

	Dz1Thread_tprintf(tab, "use_ssl = "); Dz1Bool_dump(&p->use_ssl, tab);

	Dz1Thread_tprintf(tab, "stress_mode = "); Dz1Bool_dump(&p->stress_mode, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

Dz1TcpCallbackClientEnv *Dz1TcpCallbackClientEnv_new(void *tSelf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpCallbackClientEnv *__internal_ret = (Dz1TcpCallbackClientEnv *)Dz1Calloc(sizeof(Dz1TcpCallbackClientEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientEnv_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->sessions = Dz1TcpCallbackSessionList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else
		{
			__internal_ret->tSelf = tSelf;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpCallbackClientEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpCallbackClientEnv_del(Dz1TcpCallbackClientEnv *p)
{
	if (p == NULL) return;
	if (p->sessions) Dz1TcpCallbackSessionList_del(p->sessions);
	if (p->cmd) Dz1TcpCallbackClientCmd_del(p->cmd);
	Dz1Free(p);
}

void Dz1TcpCallbackClientEnv_dump(Dz1TcpCallbackClientEnv *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->tSelf == NULL) Dz1Thread_tprintf(tab, "tSelf = NULL\n");
	else Dz1Thread_tprintf(tab, "tSelf = %p\n", p->tSelf);

	if (p->sessions == NULL) Dz1Thread_tprintf(tab, "sessions = NULL\n");
	else { Dz1Thread_tprintf(tab, "sessions = "); Dz1TcpCallbackSessionList_dump(p->sessions, tab); }

	if (p->cmd == NULL) Dz1Thread_tprintf(tab, "cmd = NULL\n");
	else { Dz1Thread_tprintf(tab, "cmd = "); Dz1TcpCallbackClientCmd_dump(p->cmd, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

