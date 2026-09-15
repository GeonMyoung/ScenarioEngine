////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "txt_replace_env.h"

////////////////////////////////////////////////////////////////////////////////
// TxtReplaceEntry
TxtReplaceEntry *TxtReplaceEntry_new(str_t symbol, str_t replace, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TxtReplaceEntry *__internal_ret = (TxtReplaceEntry *)Dz1Calloc(sizeof(TxtReplaceEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TxtReplaceEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (symbol && (__internal_ret->symbol = dz1_built_in_str_clone(symbol, errp)) == NULL) ERR_OUT(errp);
		else if (replace && (__internal_ret->replace = dz1_built_in_str_clone(replace, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TxtReplaceEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void TxtReplaceEntry_purge(TxtReplaceEntry *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->symbol);
	dz1_built_in_str_del(p->replace);
}

void TxtReplaceEntry_del(TxtReplaceEntry *p)
{
	if (p == NULL) return;
	TxtReplaceEntry_purge(p);
	Dz1Free(p);
}

void TxtReplaceEntry_dump(TxtReplaceEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("symbol = ")); dz1_built_in_str_dump(p->symbol, tab); 
		Dz1Thread_tprintf(tab, Dz1T("replace = ")); dz1_built_in_str_dump(p->replace, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int TxtReplaceEntry_cmp(TxtReplaceEntry *a, TxtReplaceEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->symbol == NULL && b->symbol == NULL) ret = 0;
	else if (a->symbol == NULL /*&& b->symbol != NULL*/) ret = -1;
	else if (/*a->symbol != NULL &&*/ b->symbol == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->symbol, b->symbol)) != 0) { }
	return ret;
}
// TxtReplaceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TxtReplaceList
static Dz1Error TxtReplaceList_add(TxtReplaceList *p, TxtReplaceEntry *data)
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

static bool_t TxtReplaceList_remove(TxtReplaceList *p, TxtReplaceEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static TxtReplaceEntry *TxtReplaceList_extract(TxtReplaceList *p, TxtReplaceEntry *key)
{
	return (TxtReplaceEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct TxtReplaceListMkArrArg
{
	TxtReplaceEntry **arr;
	unsigned int idx;
} TxtReplaceListMkArrArg;

static Dz1Error _TxtReplaceList_get_array(void *ptr, TxtReplaceEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	TxtReplaceListMkArrArg *arg = (TxtReplaceListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static TxtReplaceEntry **TxtReplaceList_get_array(TxtReplaceList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	TxtReplaceEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (TxtReplaceEntry **)Dz1Calloc(sizeof(TxtReplaceEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TxtReplaceListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _TxtReplaceList_get_array, (void *)&arg);
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

static Dz1Error TxtReplaceList_travelForward(TxtReplaceList *p, Dz1Error (*func)(void *ptr, TxtReplaceEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error TxtReplaceList_travelBackward(TxtReplaceList *p, Dz1Error (*func)(void *ptr, TxtReplaceEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static TxtReplaceEntry *TxtReplaceList_find(TxtReplaceList *p, TxtReplaceEntry *key)
{
	return (TxtReplaceEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int TxtReplaceList_count(TxtReplaceList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

TxtReplaceList *TxtReplaceList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TxtReplaceList *ret = (TxtReplaceList *)Dz1Calloc(sizeof(TxtReplaceList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TxtReplaceList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)TxtReplaceEntry_cmp,
				(Dz1DelFunc)TxtReplaceEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = TxtReplaceList_count;
			ret->travel = TxtReplaceList_travelForward;
			ret->travelForward = TxtReplaceList_travelForward;
			ret->travelBackward = TxtReplaceList_travelBackward;
			ret->get_array = TxtReplaceList_get_array;
			ret->add = TxtReplaceList_add;
			ret->remove = TxtReplaceList_remove;
			ret->find = TxtReplaceList_find;
			ret->extract = TxtReplaceList_extract;
			ret->cmp = TxtReplaceEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TxtReplaceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TxtReplaceList_purge(TxtReplaceList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void TxtReplaceList_del(TxtReplaceList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _TxtReplaceList_dump(void *ptr, TxtReplaceEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); TxtReplaceEntry_dump(p, tab);
	return err;
}

void TxtReplaceList_dump(TxtReplaceList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _TxtReplaceList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TxtReplaceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TxtReplaceEnv
TxtReplaceEnv *TxtReplaceEnv_new(str_t leadin, str_t leadout, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TxtReplaceEnv *__internal_ret = (TxtReplaceEnv *)Dz1Calloc(sizeof(TxtReplaceEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TxtReplaceEnv_delAndSetNull, (void *)&__internal_ret);
		
		if (leadin && (__internal_ret->leadin = dz1_built_in_str_clone(leadin, errp)) == NULL) ERR_OUT(errp);
		else if (leadout && (__internal_ret->leadout = dz1_built_in_str_clone(leadout, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->list = TxtReplaceList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TxtReplaceEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void TxtReplaceEnv_purge(TxtReplaceEnv *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->leadin);
	dz1_built_in_str_del(p->leadout);
	TxtReplaceList_del(p->list);
}

void TxtReplaceEnv_del(TxtReplaceEnv *p)
{
	if (p == NULL) return;
	TxtReplaceEnv_purge(p);
	Dz1Free(p);
}

void TxtReplaceEnv_dump(TxtReplaceEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("leadin = ")); dz1_built_in_str_dump(p->leadin, tab); 
		Dz1Thread_tprintf(tab, Dz1T("leadout = ")); dz1_built_in_str_dump(p->leadout, tab); 
		Dz1Thread_tprintf(tab, Dz1T("list = ")); TxtReplaceList_dump(p->list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TxtReplaceEnv
////////////////////////////////////////////////////////////////////////////////

