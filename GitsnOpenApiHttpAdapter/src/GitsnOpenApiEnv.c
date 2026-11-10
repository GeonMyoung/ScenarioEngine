////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnOpenApiEnv.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpState
static struct GitsnOpenApiHttpStateMapA
{
	str_t str;
	GitsnOpenApiHttpState v;
} GitsnOpenApiHttpStateMapA[] =
{
	{ (char *)"header", GitsnOpenApiHttpState_header },
	{ (char *)"body", GitsnOpenApiHttpState_body },
	{ NULL, GitsnOpenApiHttpState_max }
};

str_t GitsnOpenApiHttpStateStrA(GitsnOpenApiHttpState v)
{
	struct GitsnOpenApiHttpStateMapA *i = NULL;
	for (i = GitsnOpenApiHttpStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnOpenApiHttpState GitsnOpenApiHttpStateFromStrA(str_t str)
{
	struct GitsnOpenApiHttpStateMapA *i = NULL;
	for (i = GitsnOpenApiHttpStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnOpenApiHttpState_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnOpenApiHttpStateMapW
{
	wstr_t str;
	GitsnOpenApiHttpState v;
} GitsnOpenApiHttpStateMapW[] =
{
	{ (wchar_t *)L"header", GitsnOpenApiHttpState_header },
	{ (wchar_t *)L"body", GitsnOpenApiHttpState_body },
	{ NULL, GitsnOpenApiHttpState_max }
};

wstr_t GitsnOpenApiHttpStateStrW(GitsnOpenApiHttpState v)
{
	struct GitsnOpenApiHttpStateMapW *i = NULL;
	for (i = GitsnOpenApiHttpStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnOpenApiHttpState GitsnOpenApiHttpStateFromStrW(wstr_t str)
{
	struct GitsnOpenApiHttpStateMapW *i = NULL;
	for (i = GitsnOpenApiHttpStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnOpenApiHttpState_max;
}
#endif // UNIX_SYSTEM

GitsnOpenApiHttpState *GitsnOpenApiHttpState_new(GitsnOpenApiHttpState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpState *__internal_ret = (GitsnOpenApiHttpState *)Dz1Calloc(sizeof(GitsnOpenApiHttpState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// GitsnOpenApiHttpState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpLines
static Dz1Error GitsnOpenApiHttpLines_add(GitsnOpenApiHttpLines *p, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static str_t GitsnOpenApiHttpLines_extract(GitsnOpenApiHttpLines *p, str_t ptr)
{
	return (str_t )Dz1Fifo_extract(p->storage, ptr);
}

typedef struct GitsnOpenApiHttpLinesMkArrArg
{
	str_t *arr;
	unsigned int idx;
} GitsnOpenApiHttpLinesMkArrArg;

static Dz1Error _GitsnOpenApiHttpLines_get_array(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnOpenApiHttpLinesMkArrArg *arg = (GitsnOpenApiHttpLinesMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static str_t *GitsnOpenApiHttpLines_get_array(GitsnOpenApiHttpLines *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	str_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (str_t *)Dz1Calloc(sizeof(str_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnOpenApiHttpLinesMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _GitsnOpenApiHttpLines_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error GitsnOpenApiHttpLines_travelForward(GitsnOpenApiHttpLines *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error GitsnOpenApiHttpLines_travelBackward(GitsnOpenApiHttpLines *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int GitsnOpenApiHttpLines_count(GitsnOpenApiHttpLines *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

GitsnOpenApiHttpLines *GitsnOpenApiHttpLines_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpLines *ret = (GitsnOpenApiHttpLines *)Dz1Calloc(sizeof(GitsnOpenApiHttpLines), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpLines_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)dz1_built_in_str_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = GitsnOpenApiHttpLines_count;
			ret->travel = GitsnOpenApiHttpLines_travelForward;
			ret->travelForward = GitsnOpenApiHttpLines_travelForward;
			ret->travelBackward = GitsnOpenApiHttpLines_travelBackward;
			ret->get_array = GitsnOpenApiHttpLines_get_array;
			ret->add = GitsnOpenApiHttpLines_add;
			ret->extract = GitsnOpenApiHttpLines_extract;
			ret->cmp = dz1_built_in_str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpLines_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _GitsnOpenApiHttpLines_clone(void *ptr, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnOpenApiHttpLines *p = (GitsnOpenApiHttpLines *)ptr;
	str_t cloned = dz1_built_in_str_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

GitsnOpenApiHttpLines *GitsnOpenApiHttpLines_clone(GitsnOpenApiHttpLines *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpLines *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnOpenApiHttpLines_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpLines_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_GitsnOpenApiHttpLines_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpLines_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnOpenApiHttpLines_purge(GitsnOpenApiHttpLines *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void GitsnOpenApiHttpLines_del(GitsnOpenApiHttpLines *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _GitsnOpenApiHttpLinesA_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); dz1_built_in_strA_dump(p, tab);
	return err;
}

void GitsnOpenApiHttpLinesA_dump(GitsnOpenApiHttpLines *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _GitsnOpenApiHttpLinesA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _GitsnOpenApiHttpLinesA_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); dz1_built_in_strA_fdump(arg->fp, p, tab);
	return err;
}

void GitsnOpenApiHttpLinesA_fdump(FILE *fp, GitsnOpenApiHttpLines *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _GitsnOpenApiHttpLinesA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _GitsnOpenApiHttpLinesW_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); dz1_built_in_strW_dump(p, tab);
	return err;
}

void GitsnOpenApiHttpLinesW_dump(GitsnOpenApiHttpLines *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _GitsnOpenApiHttpLinesW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _GitsnOpenApiHttpLinesW_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); dz1_built_in_strW_fdump(arg->fp, p, tab);
	return err;
}

void GitsnOpenApiHttpLinesW_fdump(FILE *fp, GitsnOpenApiHttpLines *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _GitsnOpenApiHttpLinesW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// GitsnOpenApiHttpLines
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpParser
GitsnOpenApiHttpParser *GitsnOpenApiHttpParser_new(Dz1ElasticBuf *rx_buf, 
												   ssize_t body_size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpParser *__internal_ret = (GitsnOpenApiHttpParser *)Dz1Calloc(sizeof(GitsnOpenApiHttpParser), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpParser_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->hdr_lines = GitsnOpenApiHttpLines_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->rx_buf = rx_buf;
			__internal_ret->body_size = body_size;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpParser_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnOpenApiHttpParser_purge(GitsnOpenApiHttpParser *p)
{
	if (p == NULL) return;
	Dz1ElasticBuf_del(p->rx_buf);
	GitsnOpenApiHttpLines_del(p->hdr_lines);
	Dz1ElasticBuf_del(p->body);
	GitsnOpenApiHttpReq_del(p->req);
}

void GitsnOpenApiHttpParser_del(GitsnOpenApiHttpParser *p)
{
	if (p == NULL) return;
	GitsnOpenApiHttpParser_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiHttpParser_dump(GitsnOpenApiHttpParser *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), GitsnOpenApiHttpStateStr(p->state), p->state);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("rx_buf = %p\n"), p->rx_buf);
		Dz1Thread_tprintf(tab, Dz1T("hdr_lines = ")); GitsnOpenApiHttpLines_dump(p->hdr_lines, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("body = %p\n"), p->body);
		// _imp_dump
		// _imp_dump : scalar
		Dz1Thread_tprintf(tab, Dz1T("body_size = ")); ssize_t_dump(&p->body_size, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("req = ")); GitsnOpenApiHttpReq_dump(p->req, tab); 
		Dz1Thread_tprintf(tab, Dz1T("close_after_response = ")); Dz1Bool_dump(&p->close_after_response, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiHttpParser
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiSession
GitsnOpenApiSession *GitsnOpenApiSession_new(u32_t id, 
											 Dz1SockAddr *peer, 
											 Dz1SockAddr *local, 
											 Dz1TcpClientSocket *sock, 
											 GitsnOpenApiHttpParser *parser, 
											 Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiSession *__internal_ret = (GitsnOpenApiSession *)Dz1Calloc(sizeof(GitsnOpenApiSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->parser = parser;
		__internal_ret->tx_fifo = tx_fifo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnOpenApiSession_purge(GitsnOpenApiSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	GitsnOpenApiHttpParser_del(p->parser);
	Dz1SockUtilTxFifo_del(p->tx_fifo);
}

void GitsnOpenApiSession_del(GitsnOpenApiSession *p)
{
	if (p == NULL) return;
	GitsnOpenApiSession_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiSession_dump(GitsnOpenApiSession *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
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
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("parser = ")); GitsnOpenApiHttpParser_dump(p->parser, tab); 
		Dz1Thread_tprintf(tab, Dz1T("closing = ")); Dz1Bool_dump(&p->closing, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("tx_fifo = ")); Dz1SockUtilTxFifo_dump(p->tx_fifo, tab); 
		Dz1Thread_tprintf(tab, Dz1T("response_pending = ")); Dz1Bool_dump(&p->response_pending, tab); 
		Dz1Thread_tprintf(tab, Dz1T("response_call = %p\n"), p->response_call);
		Dz1Thread_tprintf(tab, Dz1T("idle_timer_armed = ")); Dz1Bool_dump(&p->idle_timer_armed, tab); 
		Dz1Thread_tprintf(tab, Dz1T("response_sequence = ")); Dz1u32_dump(&p->response_sequence, tab); 
		Dz1Thread_tprintf(tab, Dz1T("last_response_sent_ms = ")); Dz1u64_dump(&p->last_response_sent_ms, tab); 
		Dz1Thread_tprintf(tab, Dz1T("close_event_type = %s(%d)\n"), GitsnOpenApiConnectionEventTypeStr(p->close_event_type), p->close_event_type);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int GitsnOpenApiSession_cmp(GitsnOpenApiSession *a, GitsnOpenApiSession *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// GitsnOpenApiSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiSessionTable
static Dz1Error GitsnOpenApiSessionTable_add(GitsnOpenApiSessionTable *p, GitsnOpenApiSession *data)
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

static bool_t GitsnOpenApiSessionTable_remove(GitsnOpenApiSessionTable *p, GitsnOpenApiSession *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static GitsnOpenApiSession *GitsnOpenApiSessionTable_extract(GitsnOpenApiSessionTable *p, GitsnOpenApiSession *key)
{
	return (GitsnOpenApiSession *)Dz1AATree_extract(p->storage, key);
}

typedef struct GitsnOpenApiSessionTableMkArrArg
{
	GitsnOpenApiSession **arr;
	unsigned int idx;
} GitsnOpenApiSessionTableMkArrArg;

static Dz1Error _GitsnOpenApiSessionTable_get_array(void *ptr, GitsnOpenApiSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnOpenApiSessionTableMkArrArg *arg = (GitsnOpenApiSessionTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static GitsnOpenApiSession **GitsnOpenApiSessionTable_get_array(GitsnOpenApiSessionTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	GitsnOpenApiSession **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (GitsnOpenApiSession **)Dz1Calloc(sizeof(GitsnOpenApiSession *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnOpenApiSessionTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _GitsnOpenApiSessionTable_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error GitsnOpenApiSessionTable_travelForward(GitsnOpenApiSessionTable *p, Dz1Error (*func)(void *ptr, GitsnOpenApiSession *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error GitsnOpenApiSessionTable_travelBackward(GitsnOpenApiSessionTable *p, Dz1Error (*func)(void *ptr, GitsnOpenApiSession *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static GitsnOpenApiSession *GitsnOpenApiSessionTable_find(GitsnOpenApiSessionTable *p, GitsnOpenApiSession *key)
{
	return (GitsnOpenApiSession *)Dz1AATree_find(p->storage, key);
}

static unsigned int GitsnOpenApiSessionTable_count(GitsnOpenApiSessionTable *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

GitsnOpenApiSessionTable *GitsnOpenApiSessionTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiSessionTable *ret = (GitsnOpenApiSessionTable *)Dz1Calloc(sizeof(GitsnOpenApiSessionTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiSessionTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)GitsnOpenApiSession_cmp,
				(Dz1DelFunc)GitsnOpenApiSession_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = GitsnOpenApiSessionTable_count;
			ret->travel = GitsnOpenApiSessionTable_travelForward;
			ret->travelForward = GitsnOpenApiSessionTable_travelForward;
			ret->travelBackward = GitsnOpenApiSessionTable_travelBackward;
			ret->get_array = GitsnOpenApiSessionTable_get_array;
			ret->add = GitsnOpenApiSessionTable_add;
			ret->remove = GitsnOpenApiSessionTable_remove;
			ret->find = GitsnOpenApiSessionTable_find;
			ret->extract = GitsnOpenApiSessionTable_extract;
			ret->cmp = GitsnOpenApiSession_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiSessionTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnOpenApiSessionTable_purge(GitsnOpenApiSessionTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void GitsnOpenApiSessionTable_del(GitsnOpenApiSessionTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _GitsnOpenApiSessionTable_dump(void *ptr, GitsnOpenApiSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); GitsnOpenApiSession_dump(p, tab);
	return err;
}

void GitsnOpenApiSessionTable_dump(GitsnOpenApiSessionTable *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _GitsnOpenApiSessionTable_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiSessionTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiSessions
GitsnOpenApiSessions *GitsnOpenApiSessions_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiSessions *__internal_ret = (GitsnOpenApiSessions *)Dz1Calloc(sizeof(GitsnOpenApiSessions), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiSessions_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->table = GitsnOpenApiSessionTable_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiSessions_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnOpenApiSessions_purge(GitsnOpenApiSessions *p)
{
	if (p == NULL) return;
	GitsnOpenApiSessionTable_del(p->table);
}

void GitsnOpenApiSessions_del(GitsnOpenApiSessions *p)
{
	if (p == NULL) return;
	GitsnOpenApiSessions_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiSessions_dump(GitsnOpenApiSessions *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("table = ")); GitsnOpenApiSessionTable_dump(p->table, tab); 
		Dz1Thread_tprintf(tab, Dz1T("alloc_id = ")); Dz1u32_dump(&p->alloc_id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiSessions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiEnv
GitsnOpenApiEnv *GitsnOpenApiEnv_new(void *tSelf, 
									 u32_t acceptor, 
									 GitsnOpenApiSessions *sessions, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiEnv *__internal_ret = (GitsnOpenApiEnv *)Dz1Calloc(sizeof(GitsnOpenApiEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiEnv_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tSelf = tSelf;
		__internal_ret->acceptor = acceptor;
		__internal_ret->sessions = sessions;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnOpenApiEnv_purge(GitsnOpenApiEnv *p)
{
	if (p == NULL) return;
	GitsnOpenApiSessions_del(p->sessions);
}

void GitsnOpenApiEnv_del(GitsnOpenApiEnv *p)
{
	if (p == NULL) return;
	GitsnOpenApiEnv_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiEnv_dump(GitsnOpenApiEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("acceptor = ")); Dz1u32_dump(&p->acceptor, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("sessions = ")); GitsnOpenApiSessions_dump(p->sessions, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiEnv
////////////////////////////////////////////////////////////////////////////////

