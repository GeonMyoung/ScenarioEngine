////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnOpenApiDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiConnectionEventType
static struct GitsnOpenApiConnectionEventTypeMapA
{
	str_t str;
	GitsnOpenApiConnectionEventType v;
} GitsnOpenApiConnectionEventTypeMapA[] =
{
	{ (char *)"response_sent", GitsnOpenApiConnectionEventType_response_sent },
	{ (char *)"peer_closed", GitsnOpenApiConnectionEventType_peer_closed },
	{ (char *)"server_idle_timeout", GitsnOpenApiConnectionEventType_server_idle_timeout },
	{ (char *)"connection_close", GitsnOpenApiConnectionEventType_connection_close },
	{ (char *)"transport_error", GitsnOpenApiConnectionEventType_transport_error },
	{ NULL, GitsnOpenApiConnectionEventType_max }
};

str_t GitsnOpenApiConnectionEventTypeStrA(GitsnOpenApiConnectionEventType v)
{
	struct GitsnOpenApiConnectionEventTypeMapA *i = NULL;
	for (i = GitsnOpenApiConnectionEventTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnOpenApiConnectionEventType GitsnOpenApiConnectionEventTypeFromStrA(str_t str)
{
	struct GitsnOpenApiConnectionEventTypeMapA *i = NULL;
	for (i = GitsnOpenApiConnectionEventTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnOpenApiConnectionEventType_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnOpenApiConnectionEventTypeMapW
{
	wstr_t str;
	GitsnOpenApiConnectionEventType v;
} GitsnOpenApiConnectionEventTypeMapW[] =
{
	{ (wchar_t *)L"response_sent", GitsnOpenApiConnectionEventType_response_sent },
	{ (wchar_t *)L"peer_closed", GitsnOpenApiConnectionEventType_peer_closed },
	{ (wchar_t *)L"server_idle_timeout", GitsnOpenApiConnectionEventType_server_idle_timeout },
	{ (wchar_t *)L"connection_close", GitsnOpenApiConnectionEventType_connection_close },
	{ (wchar_t *)L"transport_error", GitsnOpenApiConnectionEventType_transport_error },
	{ NULL, GitsnOpenApiConnectionEventType_max }
};

wstr_t GitsnOpenApiConnectionEventTypeStrW(GitsnOpenApiConnectionEventType v)
{
	struct GitsnOpenApiConnectionEventTypeMapW *i = NULL;
	for (i = GitsnOpenApiConnectionEventTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnOpenApiConnectionEventType GitsnOpenApiConnectionEventTypeFromStrW(wstr_t str)
{
	struct GitsnOpenApiConnectionEventTypeMapW *i = NULL;
	for (i = GitsnOpenApiConnectionEventTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnOpenApiConnectionEventType_max;
}
#endif // UNIX_SYSTEM

GitsnOpenApiConnectionEventType *GitsnOpenApiConnectionEventType_new(GitsnOpenApiConnectionEventType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiConnectionEventType *__internal_ret = (GitsnOpenApiConnectionEventType *)Dz1Calloc(sizeof(GitsnOpenApiConnectionEventType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// GitsnOpenApiConnectionEventType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiConnectionEvent
GitsnOpenApiConnectionEvent *GitsnOpenApiConnectionEvent_new(GitsnOpenApiConnectionEventType event_type, 
															 u32_t session_id, 
															 u32_t response_sequence, 
															 u32_t configured_timeout_ms, 
															 u64_t response_sent_monotonic_ms, 
															 u64_t connection_closed_monotonic_ms, 
															 u64_t elapsed_ms, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiConnectionEvent *__internal_ret = (GitsnOpenApiConnectionEvent *)Dz1Calloc(sizeof(GitsnOpenApiConnectionEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiConnectionEvent_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->event_type = event_type;
		__internal_ret->session_id = session_id;
		__internal_ret->response_sequence = response_sequence;
		__internal_ret->configured_timeout_ms = configured_timeout_ms;
		__internal_ret->response_sent_monotonic_ms = response_sent_monotonic_ms;
		__internal_ret->connection_closed_monotonic_ms = connection_closed_monotonic_ms;
		__internal_ret->elapsed_ms = elapsed_ms;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiConnectionEvent_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnOpenApiConnectionEvent_copy(GitsnOpenApiConnectionEvent *dst, GitsnOpenApiConnectionEvent *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->event_type = src->event_type;
		dst->session_id = src->session_id;
		dst->response_sequence = src->response_sequence;
		dst->configured_timeout_ms = src->configured_timeout_ms;
		dst->response_sent_monotonic_ms = src->response_sent_monotonic_ms;
		dst->connection_closed_monotonic_ms = src->connection_closed_monotonic_ms;
		dst->elapsed_ms = src->elapsed_ms;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnOpenApiConnectionEvent *GitsnOpenApiConnectionEvent_clone(GitsnOpenApiConnectionEvent *src, Dz1Error *err)
{
	GitsnOpenApiConnectionEvent *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnOpenApiConnectionEvent *)Dz1Calloc(sizeof(GitsnOpenApiConnectionEvent), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiConnectionEvent_delAndSetNull, (void *)&dst);
		if (GitsnOpenApiConnectionEvent_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiConnectionEvent_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnOpenApiConnectionEvent_purge(GitsnOpenApiConnectionEvent *p)
{
	if (p == NULL) return;
}

void GitsnOpenApiConnectionEvent_del(GitsnOpenApiConnectionEvent *p)
{
	if (p == NULL) return;
	GitsnOpenApiConnectionEvent_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiConnectionEvent_dump(GitsnOpenApiConnectionEvent *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("event_type = %s(%d)\n"), GitsnOpenApiConnectionEventTypeStr(p->event_type), p->event_type);
		Dz1Thread_tprintf(tab, Dz1T("session_id = ")); Dz1u32_dump(&p->session_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("response_sequence = ")); Dz1u32_dump(&p->response_sequence, tab); 
		Dz1Thread_tprintf(tab, Dz1T("configured_timeout_ms = ")); Dz1u32_dump(&p->configured_timeout_ms, tab); 
		Dz1Thread_tprintf(tab, Dz1T("response_sent_monotonic_ms = ")); Dz1u64_dump(&p->response_sent_monotonic_ms, tab); 
		Dz1Thread_tprintf(tab, Dz1T("connection_closed_monotonic_ms = ")); Dz1u64_dump(&p->connection_closed_monotonic_ms, tab); 
		Dz1Thread_tprintf(tab, Dz1T("elapsed_ms = ")); Dz1u64_dump(&p->elapsed_ms, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiConnectionEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDataEntry
GitsnOpenApiDataEntry *GitsnOpenApiDataEntry_new(str_t key_utf8, 
												 str_t value_utf8, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiDataEntry *__internal_ret = (GitsnOpenApiDataEntry *)Dz1Calloc(sizeof(GitsnOpenApiDataEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (key_utf8 && (__internal_ret->key_utf8 = dz1_built_in_str_clone(key_utf8, errp)) == NULL) ERR_OUT(errp);
		else if (value_utf8 && (__internal_ret->value_utf8 = dz1_built_in_str_clone(value_utf8, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDataEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnOpenApiDataEntry_copy(GitsnOpenApiDataEntry *dst, GitsnOpenApiDataEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->key_utf8 && (dst->key_utf8 = dz1_built_in_str_clone(src->key_utf8, errp)) == NULL) ERR_OUT(errp);
	else if (src->value_utf8 && (dst->value_utf8 = dz1_built_in_str_clone(src->value_utf8, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnOpenApiDataEntry *GitsnOpenApiDataEntry_clone(GitsnOpenApiDataEntry *src, Dz1Error *err)
{
	GitsnOpenApiDataEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnOpenApiDataEntry *)Dz1Calloc(sizeof(GitsnOpenApiDataEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataEntry_delAndSetNull, (void *)&dst);
		if (GitsnOpenApiDataEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDataEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnOpenApiDataEntry_purge(GitsnOpenApiDataEntry *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->key_utf8);
	dz1_built_in_str_del(p->value_utf8);
}

void GitsnOpenApiDataEntry_del(GitsnOpenApiDataEntry *p)
{
	if (p == NULL) return;
	GitsnOpenApiDataEntry_purge(p);
	Dz1Free(p);
}

// GitsnOpenApiDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDataList
static Dz1Error GitsnOpenApiDataList_add(GitsnOpenApiDataList *p, GitsnOpenApiDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static GitsnOpenApiDataEntry *GitsnOpenApiDataList_extract(GitsnOpenApiDataList *p, GitsnOpenApiDataEntry *ptr)
{
	return (GitsnOpenApiDataEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct GitsnOpenApiDataListMkArrArg
{
	GitsnOpenApiDataEntry **arr;
	unsigned int idx;
} GitsnOpenApiDataListMkArrArg;

static Dz1Error _GitsnOpenApiDataList_get_array(void *ptr, GitsnOpenApiDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnOpenApiDataListMkArrArg *arg = (GitsnOpenApiDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static GitsnOpenApiDataEntry **GitsnOpenApiDataList_get_array(GitsnOpenApiDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	GitsnOpenApiDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (GitsnOpenApiDataEntry **)Dz1Calloc(sizeof(GitsnOpenApiDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnOpenApiDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _GitsnOpenApiDataList_get_array, (void *)&arg);
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

static Dz1Error GitsnOpenApiDataList_travelForward(GitsnOpenApiDataList *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error GitsnOpenApiDataList_travelBackward(GitsnOpenApiDataList *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int GitsnOpenApiDataList_count(GitsnOpenApiDataList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

GitsnOpenApiDataList *GitsnOpenApiDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiDataList *ret = (GitsnOpenApiDataList *)Dz1Calloc(sizeof(GitsnOpenApiDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)GitsnOpenApiDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = GitsnOpenApiDataList_count;
			ret->travel = GitsnOpenApiDataList_travelForward;
			ret->travelForward = GitsnOpenApiDataList_travelForward;
			ret->travelBackward = GitsnOpenApiDataList_travelBackward;
			ret->get_array = GitsnOpenApiDataList_get_array;
			ret->add = GitsnOpenApiDataList_add;
			ret->extract = GitsnOpenApiDataList_extract;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _GitsnOpenApiDataList_clone(void *ptr, GitsnOpenApiDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnOpenApiDataList *p = (GitsnOpenApiDataList *)ptr;
	GitsnOpenApiDataEntry *cloned = GitsnOpenApiDataEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

GitsnOpenApiDataList *GitsnOpenApiDataList_clone(GitsnOpenApiDataList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiDataList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnOpenApiDataList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_GitsnOpenApiDataList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnOpenApiDataList_purge(GitsnOpenApiDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void GitsnOpenApiDataList_del(GitsnOpenApiDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _GitsnOpenApiDataList_dump(void *ptr, GitsnOpenApiDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_dumptab(tab); GitsnOpenApiDataEntry_dump(p, tab);
	return err;
}

void GitsnOpenApiDataList_dump(GitsnOpenApiDataList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _GitsnOpenApiDataList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDataIndex
static Dz1Error GitsnOpenApiDataIndex_add(GitsnOpenApiDataIndex *p, GitsnOpenApiDataEntry *data)
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

static bool_t GitsnOpenApiDataIndex_remove(GitsnOpenApiDataIndex *p, GitsnOpenApiDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static GitsnOpenApiDataEntry *GitsnOpenApiDataIndex_extract(GitsnOpenApiDataIndex *p, GitsnOpenApiDataEntry *key)
{
	return (GitsnOpenApiDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct GitsnOpenApiDataIndexMkArrArg
{
	GitsnOpenApiDataEntry **arr;
	unsigned int idx;
} GitsnOpenApiDataIndexMkArrArg;

static Dz1Error _GitsnOpenApiDataIndex_get_array(void *ptr, GitsnOpenApiDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnOpenApiDataIndexMkArrArg *arg = (GitsnOpenApiDataIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static GitsnOpenApiDataEntry **GitsnOpenApiDataIndex_get_array(GitsnOpenApiDataIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	GitsnOpenApiDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (GitsnOpenApiDataEntry **)Dz1Calloc(sizeof(GitsnOpenApiDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnOpenApiDataIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _GitsnOpenApiDataIndex_get_array, (void *)&arg);
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

static Dz1Error GitsnOpenApiDataIndex_travelForward(GitsnOpenApiDataIndex *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error GitsnOpenApiDataIndex_travelBackward(GitsnOpenApiDataIndex *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static GitsnOpenApiDataEntry *GitsnOpenApiDataIndex_find(GitsnOpenApiDataIndex *p, GitsnOpenApiDataEntry *key)
{
	return (GitsnOpenApiDataEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int GitsnOpenApiDataIndex_count(GitsnOpenApiDataIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _GitsnOpenApiDataIndex_cmp(GitsnOpenApiDataEntry *a, GitsnOpenApiDataEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->key_utf8 == NULL && b->key_utf8 == NULL) ret = 0;
	else if (a->key_utf8 == NULL /*&& b->key_utf8 != NULL*/) ret = -1;
	else if (/*a->key_utf8 != NULL &&*/ b->key_utf8 == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->key_utf8, b->key_utf8)) != 0) { }
	return ret;
}

GitsnOpenApiDataIndex *GitsnOpenApiDataIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiDataIndex *ret = (GitsnOpenApiDataIndex *)Dz1Calloc(sizeof(GitsnOpenApiDataIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_GitsnOpenApiDataIndex_cmp, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = GitsnOpenApiDataIndex_count;
			ret->travel = GitsnOpenApiDataIndex_travelForward;
			ret->travelForward = GitsnOpenApiDataIndex_travelForward;
			ret->travelBackward = GitsnOpenApiDataIndex_travelBackward;
			ret->get_array = GitsnOpenApiDataIndex_get_array;
			ret->add = GitsnOpenApiDataIndex_add;
			ret->remove = GitsnOpenApiDataIndex_remove;
			ret->find = GitsnOpenApiDataIndex_find;
			ret->extract = GitsnOpenApiDataIndex_extract;
			ret->cmp = _GitsnOpenApiDataIndex_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDataIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _GitsnOpenApiDataIndex_clone(void *ptr, GitsnOpenApiDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GitsnOpenApiDataIndex *p = (GitsnOpenApiDataIndex *)ptr;
	GitsnOpenApiDataEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

GitsnOpenApiDataIndex *GitsnOpenApiDataIndex_clone(GitsnOpenApiDataIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiDataIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnOpenApiDataIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_GitsnOpenApiDataIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDataIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnOpenApiDataIndex_purge(GitsnOpenApiDataIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void GitsnOpenApiDataIndex_del(GitsnOpenApiDataIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _GitsnOpenApiDataIndex_dump(void *ptr, GitsnOpenApiDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); GitsnOpenApiDataEntry_dump(p, tab);
	return err;
}

void GitsnOpenApiDataIndex_dump(GitsnOpenApiDataIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _GitsnOpenApiDataIndex_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiDataIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDatas
GitsnOpenApiDatas *GitsnOpenApiDatas_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiDatas *__internal_ret = (GitsnOpenApiDatas *)Dz1Calloc(sizeof(GitsnOpenApiDatas), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiDatas_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->storage = GitsnOpenApiDataList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->index = GitsnOpenApiDataIndex_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDatas_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnOpenApiDatas_copy(GitsnOpenApiDatas *dst, GitsnOpenApiDatas *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->storage && (dst->storage = GitsnOpenApiDataList_clone(src->storage, errp)) == NULL) ERR_OUT(errp);
	else if (src->index && (dst->index = GitsnOpenApiDataIndex_clone(src->index, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnOpenApiDatas *GitsnOpenApiDatas_clone(GitsnOpenApiDatas *src, Dz1Error *err)
{
	GitsnOpenApiDatas *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnOpenApiDatas *)Dz1Calloc(sizeof(GitsnOpenApiDatas), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiDatas_delAndSetNull, (void *)&dst);
		if (GitsnOpenApiDatas_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDatas_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnOpenApiDatas_purge(GitsnOpenApiDatas *p)
{
	if (p == NULL) return;
	GitsnOpenApiDataList_del(p->storage);
	GitsnOpenApiDataIndex_del(p->index);
}

void GitsnOpenApiDatas_del(GitsnOpenApiDatas *p)
{
	if (p == NULL) return;
	GitsnOpenApiDatas_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiDatas_dump(GitsnOpenApiDatas *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("storage = ")); GitsnOpenApiDataList_dump(p->storage, tab); 
	}
}
// GitsnOpenApiDatas
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiResult
GitsnOpenApiResult *GitsnOpenApiResult_new(s32_t code, Dz1ElasticBuf *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiResult *__internal_ret = (GitsnOpenApiResult *)Dz1Calloc(sizeof(GitsnOpenApiResult), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiResult_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->code = code;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiResult_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnOpenApiResult_purge(GitsnOpenApiResult *p)
{
	if (p == NULL) return;
	Dz1ElasticBuf_del(p->data);
	Dz1Str_del(p->content_type);
	GitsnOpenApiDatas_del(p->headers);
	GitsnOpenApiDatas_del(p->request_headers);
}

void GitsnOpenApiResult_del(GitsnOpenApiResult *p)
{
	if (p == NULL) return;
	GitsnOpenApiResult_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiResult_dump(GitsnOpenApiResult *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("code = ")); Dz1s32_dump(&p->code, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1ElasticBuf_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("content_type = ")); Dz1Str_dump(p->content_type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiResult
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDownloadResult
GitsnOpenApiDownloadResult *GitsnOpenApiDownloadResult_new(s32_t code, 
														   u64_t bytes_written, 
														   Dz1Str content_type, 
														   Dz1Str sha256_hex, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiDownloadResult *__internal_ret = (GitsnOpenApiDownloadResult *)Dz1Calloc(sizeof(GitsnOpenApiDownloadResult), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiDownloadResult_delAndSetNull, (void *)&__internal_ret);
		
		if (content_type && (__internal_ret->content_type = Dz1Str_clone(content_type, errp)) == NULL) ERR_OUT(errp);
		else if (sha256_hex && (__internal_ret->sha256_hex = Dz1Str_clone(sha256_hex, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->code = code;
			__internal_ret->bytes_written = bytes_written;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiDownloadResult_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnOpenApiDownloadResult_purge(GitsnOpenApiDownloadResult *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->content_type);
	Dz1Str_del(p->sha256_hex);
}

void GitsnOpenApiDownloadResult_del(GitsnOpenApiDownloadResult *p)
{
	if (p == NULL) return;
	GitsnOpenApiDownloadResult_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiDownloadResult_dump(GitsnOpenApiDownloadResult *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("code = ")); Dz1s32_dump(&p->code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bytes_written = ")); Dz1u64_dump(&p->bytes_written, tab); 
		Dz1Thread_tprintf(tab, Dz1T("content_type = ")); Dz1Str_dump(p->content_type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sha256_hex = ")); Dz1Str_dump(p->sha256_hex, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiDownloadResult
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpReqMethod
static struct GitsnOpenApiHttpReqMethodMapA
{
	str_t str;
	GitsnOpenApiHttpReqMethod v;
} GitsnOpenApiHttpReqMethodMapA[] =
{
	{ (char *)"GET", GitsnOpenApiHttpReqMethod_GET },
	{ (char *)"POST", GitsnOpenApiHttpReqMethod_POST },
	{ NULL, GitsnOpenApiHttpReqMethod_max }
};

str_t GitsnOpenApiHttpReqMethodStrA(GitsnOpenApiHttpReqMethod v)
{
	struct GitsnOpenApiHttpReqMethodMapA *i = NULL;
	for (i = GitsnOpenApiHttpReqMethodMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnOpenApiHttpReqMethod GitsnOpenApiHttpReqMethodFromStrA(str_t str)
{
	struct GitsnOpenApiHttpReqMethodMapA *i = NULL;
	for (i = GitsnOpenApiHttpReqMethodMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnOpenApiHttpReqMethod_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnOpenApiHttpReqMethodMapW
{
	wstr_t str;
	GitsnOpenApiHttpReqMethod v;
} GitsnOpenApiHttpReqMethodMapW[] =
{
	{ (wchar_t *)L"GET", GitsnOpenApiHttpReqMethod_GET },
	{ (wchar_t *)L"POST", GitsnOpenApiHttpReqMethod_POST },
	{ NULL, GitsnOpenApiHttpReqMethod_max }
};

wstr_t GitsnOpenApiHttpReqMethodStrW(GitsnOpenApiHttpReqMethod v)
{
	struct GitsnOpenApiHttpReqMethodMapW *i = NULL;
	for (i = GitsnOpenApiHttpReqMethodMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnOpenApiHttpReqMethod GitsnOpenApiHttpReqMethodFromStrW(wstr_t str)
{
	struct GitsnOpenApiHttpReqMethodMapW *i = NULL;
	for (i = GitsnOpenApiHttpReqMethodMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnOpenApiHttpReqMethod_max;
}
#endif // UNIX_SYSTEM

GitsnOpenApiHttpReqMethod *GitsnOpenApiHttpReqMethod_new(GitsnOpenApiHttpReqMethod *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpReqMethod *__internal_ret = (GitsnOpenApiHttpReqMethod *)Dz1Calloc(sizeof(GitsnOpenApiHttpReqMethod), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// GitsnOpenApiHttpReqMethod
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpReq
GitsnOpenApiHttpReq *GitsnOpenApiHttpReq_new(GitsnOpenApiHttpReqMethod method, 
											 str_t target_utf8, 
											 str_t prot, 
											 u16_t ver_maj, 
											 u16_t ver_min, 
											 GitsnOpenApiDatas *header, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpReq *__internal_ret = (GitsnOpenApiHttpReq *)Dz1Calloc(sizeof(GitsnOpenApiHttpReq), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpReq_delAndSetNull, (void *)&__internal_ret);
		
		if (target_utf8 && (__internal_ret->target_utf8 = dz1_built_in_str_clone(target_utf8, errp)) == NULL) ERR_OUT(errp);
		else if (prot && (__internal_ret->prot = dz1_built_in_str_clone(prot, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->method = method;
			__internal_ret->ver_maj = ver_maj;
			__internal_ret->ver_min = ver_min;
			__internal_ret->header = header;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpReq_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnOpenApiHttpReq_copy(GitsnOpenApiHttpReq *dst, GitsnOpenApiHttpReq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->target_utf8 && (dst->target_utf8 = dz1_built_in_str_clone(src->target_utf8, errp)) == NULL) ERR_OUT(errp);
	else if (src->args && (dst->args = GitsnOpenApiDatas_clone(src->args, errp)) == NULL) ERR_OUT(errp);
	else if (src->prot && (dst->prot = dz1_built_in_str_clone(src->prot, errp)) == NULL) ERR_OUT(errp);
	else if (src->header && (dst->header = GitsnOpenApiDatas_clone(src->header, errp)) == NULL) ERR_OUT(errp);
	else if (src->body && (dst->body = Dz1Binary_clone(src->body, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->method = src->method;
		dst->ver_maj = src->ver_maj;
		dst->ver_min = src->ver_min;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnOpenApiHttpReq *GitsnOpenApiHttpReq_clone(GitsnOpenApiHttpReq *src, Dz1Error *err)
{
	GitsnOpenApiHttpReq *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnOpenApiHttpReq *)Dz1Calloc(sizeof(GitsnOpenApiHttpReq), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpReq_delAndSetNull, (void *)&dst);
		if (GitsnOpenApiHttpReq_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpReq_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnOpenApiHttpReq_purge(GitsnOpenApiHttpReq *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->target_utf8);
	GitsnOpenApiDatas_del(p->args);
	dz1_built_in_str_del(p->prot);
	GitsnOpenApiDatas_del(p->header);
	Dz1Binary_del(p->body);
}

void GitsnOpenApiHttpReq_del(GitsnOpenApiHttpReq *p)
{
	if (p == NULL) return;
	GitsnOpenApiHttpReq_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiHttpReq_dump(GitsnOpenApiHttpReq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("method = %s(%d)\n"), GitsnOpenApiHttpReqMethodStr(p->method), p->method);
		Dz1Thread_tprintf(tab, Dz1T("target_utf8 = ")); dz1_built_in_str_dump(p->target_utf8, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("args = ")); GitsnOpenApiDatas_dump(p->args, tab); 
		Dz1Thread_tprintf(tab, Dz1T("prot = ")); dz1_built_in_str_dump(p->prot, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ver_maj = ")); Dz1u16_dump(&p->ver_maj, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ver_min = ")); Dz1u16_dump(&p->ver_min, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("header = ")); GitsnOpenApiDatas_dump(p->header, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("body = ")); Dz1Binary_dump(p->body, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiHttpReq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpRsp
GitsnOpenApiHttpRsp *GitsnOpenApiHttpRsp_new(str_t prot, 
											 u16_t ver_maj, 
											 u16_t ver_min, 
											 u32_t code, 
											 str_t code_txt_utf8, 
											 GitsnOpenApiDatas *header, 
											 Dz1ElasticBuf *body, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpRsp *__internal_ret = (GitsnOpenApiHttpRsp *)Dz1Calloc(sizeof(GitsnOpenApiHttpRsp), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpRsp_delAndSetNull, (void *)&__internal_ret);
		
		if (prot && (__internal_ret->prot = dz1_built_in_str_clone(prot, errp)) == NULL) ERR_OUT(errp);
		else if (code_txt_utf8 && (__internal_ret->code_txt_utf8 = dz1_built_in_str_clone(code_txt_utf8, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->ver_maj = ver_maj;
			__internal_ret->ver_min = ver_min;
			__internal_ret->code = code;
			__internal_ret->header = header;
			__internal_ret->body = body;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpRsp_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnOpenApiHttpRsp_copy(GitsnOpenApiHttpRsp *dst, GitsnOpenApiHttpRsp *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->prot && (dst->prot = dz1_built_in_str_clone(src->prot, errp)) == NULL) ERR_OUT(errp);
	else if (src->code_txt_utf8 && (dst->code_txt_utf8 = dz1_built_in_str_clone(src->code_txt_utf8, errp)) == NULL) ERR_OUT(errp);
	else if (src->header && (dst->header = GitsnOpenApiDatas_clone(src->header, errp)) == NULL) ERR_OUT(errp);
	else if (src->body && (dst->body = Dz1ElasticBuf_clone(src->body, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->ver_maj = src->ver_maj;
		dst->ver_min = src->ver_min;
		dst->code = src->code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnOpenApiHttpRsp *GitsnOpenApiHttpRsp_clone(GitsnOpenApiHttpRsp *src, Dz1Error *err)
{
	GitsnOpenApiHttpRsp *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnOpenApiHttpRsp *)Dz1Calloc(sizeof(GitsnOpenApiHttpRsp), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpRsp_delAndSetNull, (void *)&dst);
		if (GitsnOpenApiHttpRsp_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpRsp_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnOpenApiHttpRsp_purge(GitsnOpenApiHttpRsp *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->prot);
	dz1_built_in_str_del(p->code_txt_utf8);
	GitsnOpenApiDatas_del(p->header);
	Dz1ElasticBuf_del(p->body);
}

void GitsnOpenApiHttpRsp_del(GitsnOpenApiHttpRsp *p)
{
	if (p == NULL) return;
	GitsnOpenApiHttpRsp_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiHttpRsp_dump(GitsnOpenApiHttpRsp *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("prot = ")); dz1_built_in_str_dump(p->prot, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ver_maj = ")); Dz1u16_dump(&p->ver_maj, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ver_min = ")); Dz1u16_dump(&p->ver_min, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = ")); Dz1u32_dump(&p->code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code_txt_utf8 = ")); dz1_built_in_str_dump(p->code_txt_utf8, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("header = ")); GitsnOpenApiDatas_dump(p->header, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("body = ")); Dz1ElasticBuf_dump(p->body, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiHttpRsp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpMsgPresent
static struct GitsnOpenApiHttpMsgPresentMapA
{
	str_t str;
	GitsnOpenApiHttpMsgPresent v;
} GitsnOpenApiHttpMsgPresentMapA[] =
{
	{ (char *)"req", GitsnOpenApiHttpMsgPresent_req },
	{ (char *)"rsp", GitsnOpenApiHttpMsgPresent_rsp },
	{ (char *)"ws_payload", GitsnOpenApiHttpMsgPresent_ws_payload },
	{ NULL, GitsnOpenApiHttpMsgPresent_max }
};

str_t GitsnOpenApiHttpMsgPresentStrA(GitsnOpenApiHttpMsgPresent v)
{
	struct GitsnOpenApiHttpMsgPresentMapA *i = NULL;
	for (i = GitsnOpenApiHttpMsgPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnOpenApiHttpMsgPresent GitsnOpenApiHttpMsgPresentFromStrA(str_t str)
{
	struct GitsnOpenApiHttpMsgPresentMapA *i = NULL;
	for (i = GitsnOpenApiHttpMsgPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GitsnOpenApiHttpMsgPresent_max;
}
#ifndef UNIX_SYSTEM
static struct GitsnOpenApiHttpMsgPresentMapW
{
	wstr_t str;
	GitsnOpenApiHttpMsgPresent v;
} GitsnOpenApiHttpMsgPresentMapW[] =
{
	{ (wchar_t *)L"req", GitsnOpenApiHttpMsgPresent_req },
	{ (wchar_t *)L"rsp", GitsnOpenApiHttpMsgPresent_rsp },
	{ (wchar_t *)L"ws_payload", GitsnOpenApiHttpMsgPresent_ws_payload },
	{ NULL, GitsnOpenApiHttpMsgPresent_max }
};

wstr_t GitsnOpenApiHttpMsgPresentStrW(GitsnOpenApiHttpMsgPresent v)
{
	struct GitsnOpenApiHttpMsgPresentMapW *i = NULL;
	for (i = GitsnOpenApiHttpMsgPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GitsnOpenApiHttpMsgPresent GitsnOpenApiHttpMsgPresentFromStrW(wstr_t str)
{
	struct GitsnOpenApiHttpMsgPresentMapW *i = NULL;
	for (i = GitsnOpenApiHttpMsgPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GitsnOpenApiHttpMsgPresent_max;
}
#endif // UNIX_SYSTEM

GitsnOpenApiHttpMsgPresent *GitsnOpenApiHttpMsgPresent_new(GitsnOpenApiHttpMsgPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpMsgPresent *__internal_ret = (GitsnOpenApiHttpMsgPresent *)Dz1Calloc(sizeof(GitsnOpenApiHttpMsgPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void GitsnOpenApiHttpMsgPresent_dump(GitsnOpenApiHttpMsgPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), GitsnOpenApiHttpMsgPresentStr(*v));
}
// GitsnOpenApiHttpMsgPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpMsg
GitsnOpenApiHttpMsg *GitsnOpenApiHttpMsg_new(GitsnOpenApiHttpMsgPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiHttpMsg *ret = (GitsnOpenApiHttpMsg *)Dz1Calloc(sizeof(GitsnOpenApiHttpMsg), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpMsg_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case GitsnOpenApiHttpMsgPresent_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.req = (GitsnOpenApiHttpReq *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnOpenApiHttpMsgPresent_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rsp = (GitsnOpenApiHttpRsp *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnOpenApiHttpMsgPresent_ws_payload:
			// _U_imp_clone
			if (ptr != NULL) ret->x.ws_payload = (Dz1Binary *)ptr;
			ERR_CLEAR(errp);
			break;
		case GitsnOpenApiHttpMsgPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t GitsnOpenApiHttpMsg_copy(GitsnOpenApiHttpMsg *ret, GitsnOpenApiHttpMsg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case GitsnOpenApiHttpMsgPresent_req:
			// _U_cst_clone
			if (src->x.req && (ret->x.req = GitsnOpenApiHttpReq_clone(src->x.req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case GitsnOpenApiHttpMsgPresent_rsp:
			// _U_cst_clone
			if (src->x.rsp && (ret->x.rsp = GitsnOpenApiHttpRsp_clone(src->x.rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case GitsnOpenApiHttpMsgPresent_ws_payload:
			// _U_imp_clone
			if (src->x.ws_payload && (ret->x.ws_payload = Dz1Binary_clone(src->x.ws_payload, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnOpenApiHttpMsg *GitsnOpenApiHttpMsg_clone(GitsnOpenApiHttpMsg *src, Dz1Error *err)
{
	GitsnOpenApiHttpMsg *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (GitsnOpenApiHttpMsg *)Dz1Calloc(sizeof(GitsnOpenApiHttpMsg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiHttpMsg_delAndSetNull, (void *)&ret);
		if (GitsnOpenApiHttpMsg_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiHttpMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GitsnOpenApiHttpMsg_purge(GitsnOpenApiHttpMsg *p)
{
	if (!p) return;
	switch(p->present)
	{
	case GitsnOpenApiHttpMsgPresent_req:
		GitsnOpenApiHttpReq_del(p->x.req);
		break;
	case GitsnOpenApiHttpMsgPresent_rsp:
		GitsnOpenApiHttpRsp_del(p->x.rsp);
		break;
	case GitsnOpenApiHttpMsgPresent_ws_payload:
		Dz1Binary_del(p->x.ws_payload);
		break;
	default:
		break;
	}
}

void GitsnOpenApiHttpMsg_del(GitsnOpenApiHttpMsg *p)
{
	if (!p) return;
	GitsnOpenApiHttpMsg_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiHttpMsg_dump(GitsnOpenApiHttpMsg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case GitsnOpenApiHttpMsgPresent_req:
		Dz1Thread_printf(Dz1T("req = ")); GitsnOpenApiHttpReq_dump(p->x.req, tab); 
		break;
	case GitsnOpenApiHttpMsgPresent_rsp:
		Dz1Thread_printf(Dz1T("rsp = ")); GitsnOpenApiHttpRsp_dump(p->x.rsp, tab); 
		break;
	case GitsnOpenApiHttpMsgPresent_ws_payload:
		Dz1Thread_printf(Dz1T("ws_payload = ")); Dz1Binary_dump(p->x.ws_payload, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// GitsnOpenApiHttpMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiMsg
GitsnOpenApiMsg *GitsnOpenApiMsg_new(u32_t session_id, GitsnOpenApiHttpMsg *ctx, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiMsg *__internal_ret = (GitsnOpenApiMsg *)Dz1Calloc(sizeof(GitsnOpenApiMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiMsg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->session_id = session_id;
		__internal_ret->ctx = ctx;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GitsnOpenApiMsg_copy(GitsnOpenApiMsg *dst, GitsnOpenApiMsg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ctx && (dst->ctx = GitsnOpenApiHttpMsg_clone(src->ctx, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->session_id = src->session_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GitsnOpenApiMsg *GitsnOpenApiMsg_clone(GitsnOpenApiMsg *src, Dz1Error *err)
{
	GitsnOpenApiMsg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GitsnOpenApiMsg *)Dz1Calloc(sizeof(GitsnOpenApiMsg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiMsg_delAndSetNull, (void *)&dst);
		if (GitsnOpenApiMsg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiMsg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GitsnOpenApiMsg_purge(GitsnOpenApiMsg *p)
{
	if (p == NULL) return;
	GitsnOpenApiHttpMsg_del(p->ctx);
}

void GitsnOpenApiMsg_del(GitsnOpenApiMsg *p)
{
	if (p == NULL) return;
	GitsnOpenApiMsg_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiMsg_dump(GitsnOpenApiMsg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("session_id = ")); Dz1u32_dump(&p->session_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ctx.")); GitsnOpenApiHttpMsg_dump(p->ctx, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GitsnOpenApiMsg
////////////////////////////////////////////////////////////////////////////////

