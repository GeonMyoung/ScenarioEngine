////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_row_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqNullOpt
Dz1TdqNullOpt *Dz1TdqNullOpt_new(Dz1Str dflt_val, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqNullOpt *__internal_ret = (Dz1TdqNullOpt *)Dz1Calloc(sizeof(Dz1TdqNullOpt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqNullOpt_delAndSetNull, (void *)&__internal_ret);
		
		if (dflt_val && (__internal_ret->dflt_val = Dz1Str_clone(dflt_val, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqNullOpt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqNullOpt_copy(Dz1TdqNullOpt *dst, Dz1TdqNullOpt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->dflt_val && (dst->dflt_val = Dz1Str_clone(src->dflt_val, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqNullOpt *Dz1TdqNullOpt_clone(Dz1TdqNullOpt *src, Dz1Error *err)
{
	Dz1TdqNullOpt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqNullOpt *)Dz1Calloc(sizeof(Dz1TdqNullOpt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqNullOpt_delAndSetNull, (void *)&dst);
		if (Dz1TdqNullOpt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqNullOpt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqNullOpt_purge(Dz1TdqNullOpt *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->dflt_val);
}

void Dz1TdqNullOpt_del(Dz1TdqNullOpt *p)
{
	if (p == NULL) return;
	Dz1TdqNullOpt_purge(p);
	Dz1Free(p);
}

void Dz1TdqNullOpt_dump(Dz1TdqNullOpt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dflt_val = ")); Dz1Str_dump(p->dflt_val, tab); 
	}
}
// Dz1TdqNullOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumn
Dz1TdqColumn *Dz1TdqColumn_new(Dz1Str name, 
							   Dz1TdqSqlTypeSpec *sql_type, 
							   Dz1TdqNullOpt *null_opt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumn *__internal_ret = (Dz1TdqColumn *)Dz1Calloc(sizeof(Dz1TdqColumn), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->sql_type = sql_type;
			__internal_ret->null_opt = null_opt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumn_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqColumn_copy(Dz1TdqColumn *dst, Dz1TdqColumn *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->sql_type && (dst->sql_type = Dz1TdqSqlTypeSpec_clone(src->sql_type, errp)) == NULL) ERR_OUT(errp);
	else if (src->null_opt && (dst->null_opt = Dz1TdqNullOpt_clone(src->null_opt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqColumn *Dz1TdqColumn_clone(Dz1TdqColumn *src, Dz1Error *err)
{
	Dz1TdqColumn *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqColumn *)Dz1Calloc(sizeof(Dz1TdqColumn), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&dst);
		if (Dz1TdqColumn_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumn_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqColumn_purge(Dz1TdqColumn *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1TdqSqlTypeSpec_del(p->sql_type);
	Dz1TdqNullOpt_del(p->null_opt);
}

void Dz1TdqColumn_del(Dz1TdqColumn *p)
{
	if (p == NULL) return;
	Dz1TdqColumn_purge(p);
	Dz1Free(p);
}

int Dz1TdqColumn_cmp(Dz1TdqColumn *a, Dz1TdqColumn *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// Dz1TdqColumn
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnList
static Dz1Error Dz1TdqColumnList_add(Dz1TdqColumnList *p, Dz1TdqColumn *data)
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

static bool_t Dz1TdqColumnList_remove(Dz1TdqColumnList *p, Dz1TdqColumn *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqColumn *Dz1TdqColumnList_extract(Dz1TdqColumnList *p, Dz1TdqColumn *key)
{
	return (Dz1TdqColumn *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqColumnListMkArrArg
{
	Dz1TdqColumn **arr;
	unsigned int idx;
} Dz1TdqColumnListMkArrArg;

static Dz1Error _Dz1TdqColumnList_get_array(void *ptr, Dz1TdqColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqColumnListMkArrArg *arg = (Dz1TdqColumnListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqColumn **Dz1TdqColumnList_get_array(Dz1TdqColumnList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqColumn **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqColumn **)Dz1Calloc(sizeof(Dz1TdqColumn *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqColumnList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqColumnList_travelForward(Dz1TdqColumnList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqColumnList_travelBackward(Dz1TdqColumnList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqColumn *Dz1TdqColumnList_find(Dz1TdqColumnList *p, Dz1TdqColumn *key)
{
	return (Dz1TdqColumn *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqColumnList_count(Dz1TdqColumnList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqColumnList *Dz1TdqColumnList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumnList *ret = (Dz1TdqColumnList *)Dz1Calloc(sizeof(Dz1TdqColumnList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqColumn_cmp,
				(Dz1DelFunc)Dz1TdqColumn_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqColumnList_count;
			ret->travel = Dz1TdqColumnList_travelForward;
			ret->travelForward = Dz1TdqColumnList_travelForward;
			ret->travelBackward = Dz1TdqColumnList_travelBackward;
			ret->get_array = Dz1TdqColumnList_get_array;
			ret->add = Dz1TdqColumnList_add;
			ret->remove = Dz1TdqColumnList_remove;
			ret->find = Dz1TdqColumnList_find;
			ret->extract = Dz1TdqColumnList_extract;
			ret->cmp = Dz1TdqColumn_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumnList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqColumnList_clone(void *ptr, Dz1TdqColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqColumnList *p = (Dz1TdqColumnList *)ptr;
	Dz1TdqColumn *cloned = Dz1TdqColumn_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqColumnList *Dz1TdqColumnList_clone(Dz1TdqColumnList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumnList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqColumnList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqColumnList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumnList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqColumnList_purge(Dz1TdqColumnList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqColumnList_del(Dz1TdqColumnList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqColumnList_dump(void *ptr, Dz1TdqColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqColumn_dump(p, tab);
	return err;
}

void Dz1TdqColumnList_dump(Dz1TdqColumnList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqColumnList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqColumnList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnRefList
static Dz1Error Dz1TdqColumnRefList_add(Dz1TdqColumnRefList *p, Dz1TdqColumn *data)
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

static bool_t Dz1TdqColumnRefList_remove(Dz1TdqColumnRefList *p, Dz1TdqColumn *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqColumn *Dz1TdqColumnRefList_extract(Dz1TdqColumnRefList *p, Dz1TdqColumn *key)
{
	return (Dz1TdqColumn *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqColumnRefListMkArrArg
{
	Dz1TdqColumn **arr;
	unsigned int idx;
} Dz1TdqColumnRefListMkArrArg;

static Dz1Error _Dz1TdqColumnRefList_get_array(void *ptr, Dz1TdqColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqColumnRefListMkArrArg *arg = (Dz1TdqColumnRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqColumn **Dz1TdqColumnRefList_get_array(Dz1TdqColumnRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqColumn **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqColumn **)Dz1Calloc(sizeof(Dz1TdqColumn *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqColumnRefList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqColumnRefList_travelForward(Dz1TdqColumnRefList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqColumnRefList_travelBackward(Dz1TdqColumnRefList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqColumn *Dz1TdqColumnRefList_find(Dz1TdqColumnRefList *p, Dz1TdqColumn *key)
{
	return (Dz1TdqColumn *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqColumnRefList_count(Dz1TdqColumnRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqColumnRefList *Dz1TdqColumnRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumnRefList *ret = (Dz1TdqColumnRefList *)Dz1Calloc(sizeof(Dz1TdqColumnRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqColumn_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqColumnRefList_count;
			ret->travel = Dz1TdqColumnRefList_travelForward;
			ret->travelForward = Dz1TdqColumnRefList_travelForward;
			ret->travelBackward = Dz1TdqColumnRefList_travelBackward;
			ret->get_array = Dz1TdqColumnRefList_get_array;
			ret->add = Dz1TdqColumnRefList_add;
			ret->remove = Dz1TdqColumnRefList_remove;
			ret->find = Dz1TdqColumnRefList_find;
			ret->extract = Dz1TdqColumnRefList_extract;
			ret->cmp = Dz1TdqColumn_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumnRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqColumnRefList_clone(void *ptr, Dz1TdqColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqColumnRefList *p = (Dz1TdqColumnRefList *)ptr;
	Dz1TdqColumn *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqColumnRefList *Dz1TdqColumnRefList_clone(Dz1TdqColumnRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumnRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqColumnRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqColumnRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumnRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqColumnRefList_purge(Dz1TdqColumnRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqColumnRefList_del(Dz1TdqColumnRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqColumnRefList_dump(void *ptr, Dz1TdqColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqColumn_dump(p, tab);
	return err;
}

void Dz1TdqColumnRefList_dump(Dz1TdqColumnRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqColumnRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqColumnRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnSeq
static Dz1Error Dz1TdqColumnSeq_add(Dz1TdqColumnSeq *p, Dz1TdqColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqColumnSeqMkArrArg
{
	Dz1TdqColumn **arr;
	unsigned int idx;
} Dz1TdqColumnSeqMkArrArg;

static Dz1Error _Dz1TdqColumnSeq_get_array(void *ptr, Dz1TdqColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqColumnSeqMkArrArg *arg = (Dz1TdqColumnSeqMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqColumn **Dz1TdqColumnSeq_get_array(Dz1TdqColumnSeq *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqColumn **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqColumn **)Dz1Calloc(sizeof(Dz1TdqColumn *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnSeqMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqColumnSeq_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqColumnSeq_travelForward(Dz1TdqColumnSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqColumnSeq_travelBackward(Dz1TdqColumnSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqColumnSeq_count(Dz1TdqColumnSeq *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqColumnSeq *Dz1TdqColumnSeq_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumnSeq *ret = (Dz1TdqColumnSeq *)Dz1Calloc(sizeof(Dz1TdqColumnSeq), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnSeq_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1TdqColumn_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqColumnSeq_count;
			ret->travel = Dz1TdqColumnSeq_travelForward;
			ret->travelForward = Dz1TdqColumnSeq_travelForward;
			ret->travelBackward = Dz1TdqColumnSeq_travelBackward;
			ret->get_array = Dz1TdqColumnSeq_get_array;
			ret->add = Dz1TdqColumnSeq_add;
			ret->cmp = Dz1TdqColumn_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumnSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqColumnSeq_clone(void *ptr, Dz1TdqColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqColumnSeq *p = (Dz1TdqColumnSeq *)ptr;
	Dz1TdqColumn *cloned = Dz1TdqColumn_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqColumnSeq *Dz1TdqColumnSeq_clone(Dz1TdqColumnSeq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumnSeq *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqColumnSeq_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnSeq_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqColumnSeq_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumnSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqColumnSeq_purge(Dz1TdqColumnSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqColumnSeq_del(Dz1TdqColumnSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqColumnSeq_dump(void *ptr, Dz1TdqColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqColumn_dump(p, tab);
	return err;
}

void Dz1TdqColumnSeq_dump(Dz1TdqColumnSeq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqColumnSeq_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqColumnSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnRefSeq
static Dz1Error Dz1TdqColumnRefSeq_add(Dz1TdqColumnRefSeq *p, Dz1TdqColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqColumnRefSeqMkArrArg
{
	Dz1TdqColumn **arr;
	unsigned int idx;
} Dz1TdqColumnRefSeqMkArrArg;

static Dz1Error _Dz1TdqColumnRefSeq_get_array(void *ptr, Dz1TdqColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqColumnRefSeqMkArrArg *arg = (Dz1TdqColumnRefSeqMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqColumn **Dz1TdqColumnRefSeq_get_array(Dz1TdqColumnRefSeq *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqColumn **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqColumn **)Dz1Calloc(sizeof(Dz1TdqColumn *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnRefSeqMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqColumnRefSeq_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqColumnRefSeq_travelForward(Dz1TdqColumnRefSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqColumnRefSeq_travelBackward(Dz1TdqColumnRefSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqColumnRefSeq_count(Dz1TdqColumnRefSeq *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqColumnRefSeq *Dz1TdqColumnRefSeq_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumnRefSeq *ret = (Dz1TdqColumnRefSeq *)Dz1Calloc(sizeof(Dz1TdqColumnRefSeq), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnRefSeq_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqColumnRefSeq_count;
			ret->travel = Dz1TdqColumnRefSeq_travelForward;
			ret->travelForward = Dz1TdqColumnRefSeq_travelForward;
			ret->travelBackward = Dz1TdqColumnRefSeq_travelBackward;
			ret->get_array = Dz1TdqColumnRefSeq_get_array;
			ret->add = Dz1TdqColumnRefSeq_add;
			ret->cmp = Dz1TdqColumn_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumnRefSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqColumnRefSeq_clone(void *ptr, Dz1TdqColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqColumnRefSeq *p = (Dz1TdqColumnRefSeq *)ptr;
	Dz1TdqColumn *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqColumnRefSeq *Dz1TdqColumnRefSeq_clone(Dz1TdqColumnRefSeq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqColumnRefSeq *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqColumnRefSeq_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnRefSeq_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqColumnRefSeq_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqColumnRefSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqColumnRefSeq_purge(Dz1TdqColumnRefSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqColumnRefSeq_del(Dz1TdqColumnRefSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqColumnRefSeq_dump(void *ptr, Dz1TdqColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqColumn_dump(p, tab);
	return err;
}

void Dz1TdqColumnRefSeq_dump(Dz1TdqColumnRefSeq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqColumnRefSeq_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqColumnRefSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqRow
Dz1TdqRow *Dz1TdqRow_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqRow *__internal_ret = (Dz1TdqRow *)Dz1Calloc(sizeof(Dz1TdqRow), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqRow_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->index = Dz1TdqColumnList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->seq = Dz1TdqColumnRefSeq_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqRow_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqRow_copy(Dz1TdqRow *dst, Dz1TdqRow *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->index && (dst->index = Dz1TdqColumnList_clone(src->index, errp)) == NULL) ERR_OUT(errp);
	else if (src->seq && (dst->seq = Dz1TdqColumnRefSeq_clone(src->seq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqRow *Dz1TdqRow_clone(Dz1TdqRow *src, Dz1Error *err)
{
	Dz1TdqRow *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqRow *)Dz1Calloc(sizeof(Dz1TdqRow), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqRow_delAndSetNull, (void *)&dst);
		if (Dz1TdqRow_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqRow_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqRow_purge(Dz1TdqRow *p)
{
	if (p == NULL) return;
	Dz1TdqColumnList_del(p->index);
	Dz1TdqColumnRefSeq_del(p->seq);
}

void Dz1TdqRow_del(Dz1TdqRow *p)
{
	if (p == NULL) return;
	Dz1TdqRow_purge(p);
	Dz1Free(p);
}

// Dz1TdqRow
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqRowRef
Dz1TdqRowRef *Dz1TdqRowRef_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqRowRef *__internal_ret = (Dz1TdqRowRef *)Dz1Calloc(sizeof(Dz1TdqRowRef), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqRowRef_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->index = Dz1TdqColumnRefList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->seq = Dz1TdqColumnRefSeq_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqRowRef_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqRowRef_copy(Dz1TdqRowRef *dst, Dz1TdqRowRef *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->index && (dst->index = Dz1TdqColumnRefList_clone(src->index, errp)) == NULL) ERR_OUT(errp);
	else if (src->seq && (dst->seq = Dz1TdqColumnRefSeq_clone(src->seq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqRowRef *Dz1TdqRowRef_clone(Dz1TdqRowRef *src, Dz1Error *err)
{
	Dz1TdqRowRef *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqRowRef *)Dz1Calloc(sizeof(Dz1TdqRowRef), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqRowRef_delAndSetNull, (void *)&dst);
		if (Dz1TdqRowRef_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqRowRef_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqRowRef_purge(Dz1TdqRowRef *p)
{
	if (p == NULL) return;
	Dz1TdqColumnRefList_del(p->index);
	Dz1TdqColumnRefSeq_del(p->seq);
}

void Dz1TdqRowRef_del(Dz1TdqRowRef *p)
{
	if (p == NULL) return;
	Dz1TdqRowRef_purge(p);
	Dz1Free(p);
}

// Dz1TdqRowRef
////////////////////////////////////////////////////////////////////////////////

