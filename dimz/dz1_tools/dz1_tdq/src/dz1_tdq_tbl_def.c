////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_tbl_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqIndexEntry
Dz1TdqIndexEntry *Dz1TdqIndexEntry_new(Dz1Str suffix_name, bool_t unique, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqIndexEntry *__internal_ret = (Dz1TdqIndexEntry *)Dz1Calloc(sizeof(Dz1TdqIndexEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqIndexEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (suffix_name && (__internal_ret->suffix_name = Dz1Str_clone(suffix_name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->unique = unique;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqIndexEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqIndexEntry_copy(Dz1TdqIndexEntry *dst, Dz1TdqIndexEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->suffix_name && (dst->suffix_name = Dz1Str_clone(src->suffix_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->own_cols && (dst->own_cols = Dz1TdqRowRef_clone(src->own_cols, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->unique = src->unique;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqIndexEntry *Dz1TdqIndexEntry_clone(Dz1TdqIndexEntry *src, Dz1Error *err)
{
	Dz1TdqIndexEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqIndexEntry *)Dz1Calloc(sizeof(Dz1TdqIndexEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqIndexEntry_delAndSetNull, (void *)&dst);
		if (Dz1TdqIndexEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqIndexEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqIndexEntry_purge(Dz1TdqIndexEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->suffix_name);
	Dz1TdqRowRef_del(p->own_cols);
}

void Dz1TdqIndexEntry_del(Dz1TdqIndexEntry *p)
{
	if (p == NULL) return;
	Dz1TdqIndexEntry_purge(p);
	Dz1Free(p);
}

int Dz1TdqIndexEntry_cmp(Dz1TdqIndexEntry *a, Dz1TdqIndexEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->suffix_name == NULL && b->suffix_name == NULL) ret = 0;
	else if (a->suffix_name == NULL /*&& b->suffix_name != NULL*/) ret = -1;
	else if (/*a->suffix_name != NULL &&*/ b->suffix_name == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->suffix_name, b->suffix_name)) != 0) { }
	return ret;
}
// Dz1TdqIndexEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqIndexList
static Dz1Error Dz1TdqIndexList_add(Dz1TdqIndexList *p, Dz1TdqIndexEntry *data)
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

static bool_t Dz1TdqIndexList_remove(Dz1TdqIndexList *p, Dz1TdqIndexEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqIndexEntry *Dz1TdqIndexList_extract(Dz1TdqIndexList *p, Dz1TdqIndexEntry *key)
{
	return (Dz1TdqIndexEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqIndexListMkArrArg
{
	Dz1TdqIndexEntry **arr;
	unsigned int idx;
} Dz1TdqIndexListMkArrArg;

static Dz1Error _Dz1TdqIndexList_get_array(void *ptr, Dz1TdqIndexEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqIndexListMkArrArg *arg = (Dz1TdqIndexListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqIndexEntry **Dz1TdqIndexList_get_array(Dz1TdqIndexList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqIndexEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqIndexEntry **)Dz1Calloc(sizeof(Dz1TdqIndexEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqIndexListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqIndexList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqIndexList_travelForward(Dz1TdqIndexList *p, Dz1Error (*func)(void *ptr, Dz1TdqIndexEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqIndexList_travelBackward(Dz1TdqIndexList *p, Dz1Error (*func)(void *ptr, Dz1TdqIndexEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqIndexEntry *Dz1TdqIndexList_find(Dz1TdqIndexList *p, Dz1TdqIndexEntry *key)
{
	return (Dz1TdqIndexEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqIndexList_count(Dz1TdqIndexList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqIndexList *Dz1TdqIndexList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqIndexList *ret = (Dz1TdqIndexList *)Dz1Calloc(sizeof(Dz1TdqIndexList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqIndexList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqIndexEntry_cmp,
				(Dz1DelFunc)Dz1TdqIndexEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqIndexList_count;
			ret->travel = Dz1TdqIndexList_travelForward;
			ret->travelForward = Dz1TdqIndexList_travelForward;
			ret->travelBackward = Dz1TdqIndexList_travelBackward;
			ret->get_array = Dz1TdqIndexList_get_array;
			ret->add = Dz1TdqIndexList_add;
			ret->remove = Dz1TdqIndexList_remove;
			ret->find = Dz1TdqIndexList_find;
			ret->extract = Dz1TdqIndexList_extract;
			ret->cmp = Dz1TdqIndexEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqIndexList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqIndexList_clone(void *ptr, Dz1TdqIndexEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqIndexList *p = (Dz1TdqIndexList *)ptr;
	Dz1TdqIndexEntry *cloned = Dz1TdqIndexEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqIndexList *Dz1TdqIndexList_clone(Dz1TdqIndexList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqIndexList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqIndexList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqIndexList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqIndexList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqIndexList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqIndexList_purge(Dz1TdqIndexList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqIndexList_del(Dz1TdqIndexList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqIndexList_dump(void *ptr, Dz1TdqIndexEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqIndexEntry_dump(p, tab);
	return err;
}

void Dz1TdqIndexList_dump(Dz1TdqIndexList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqIndexList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqIndexList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblShape
Dz1TdqTblShape *Dz1TdqTblShape_new(Dz1Str name, 
								   Dz1TdqRow *row, 
								   Dz1TdqRowRef *pk, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqTblShape *__internal_ret = (Dz1TdqTblShape *)Dz1Calloc(sizeof(Dz1TdqTblShape), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->indexes = Dz1TdqIndexList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->row = row;
			__internal_ret->pk = pk;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblShape_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqTblShape_copy(Dz1TdqTblShape *dst, Dz1TdqTblShape *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->row && (dst->row = Dz1TdqRow_clone(src->row, errp)) == NULL) ERR_OUT(errp);
	else if (src->pk && (dst->pk = Dz1TdqRowRef_clone(src->pk, errp)) == NULL) ERR_OUT(errp);
	else if (src->indexes && (dst->indexes = Dz1TdqIndexList_clone(src->indexes, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqTblShape *Dz1TdqTblShape_clone(Dz1TdqTblShape *src, Dz1Error *err)
{
	Dz1TdqTblShape *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqTblShape *)Dz1Calloc(sizeof(Dz1TdqTblShape), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&dst);
		if (Dz1TdqTblShape_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblShape_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqTblShape_purge(Dz1TdqTblShape *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1TdqRow_del(p->row);
	Dz1TdqRowRef_del(p->pk);
	Dz1TdqIndexList_del(p->indexes);
}

void Dz1TdqTblShape_del(Dz1TdqTblShape *p)
{
	if (p == NULL) return;
	Dz1TdqTblShape_purge(p);
	Dz1Free(p);
}

void Dz1TdqTblShape_dump(Dz1TdqTblShape *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("row = ")); Dz1TdqRow_dump(p->row, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("pk = ")); Dz1TdqRowRef_dump(p->pk, tab); 
		Dz1Thread_tprintf(tab, Dz1T("indexes = ")); Dz1TdqIndexList_dump(p->indexes, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TdqTblShape_cmp(Dz1TdqTblShape *a, Dz1TdqTblShape *b)
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
// Dz1TdqTblShape
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblShapeList
static Dz1Error Dz1TdqTblShapeList_add(Dz1TdqTblShapeList *p, Dz1TdqTblShape *data)
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

static bool_t Dz1TdqTblShapeList_remove(Dz1TdqTblShapeList *p, Dz1TdqTblShape *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqTblShape *Dz1TdqTblShapeList_extract(Dz1TdqTblShapeList *p, Dz1TdqTblShape *key)
{
	return (Dz1TdqTblShape *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqTblShapeListMkArrArg
{
	Dz1TdqTblShape **arr;
	unsigned int idx;
} Dz1TdqTblShapeListMkArrArg;

static Dz1Error _Dz1TdqTblShapeList_get_array(void *ptr, Dz1TdqTblShape *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqTblShapeListMkArrArg *arg = (Dz1TdqTblShapeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqTblShape **Dz1TdqTblShapeList_get_array(Dz1TdqTblShapeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqTblShape **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqTblShape **)Dz1Calloc(sizeof(Dz1TdqTblShape *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqTblShapeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqTblShapeList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqTblShapeList_travelForward(Dz1TdqTblShapeList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblShape *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqTblShapeList_travelBackward(Dz1TdqTblShapeList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblShape *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqTblShape *Dz1TdqTblShapeList_find(Dz1TdqTblShapeList *p, Dz1TdqTblShape *key)
{
	return (Dz1TdqTblShape *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqTblShapeList_count(Dz1TdqTblShapeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqTblShapeList *Dz1TdqTblShapeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqTblShapeList *ret = (Dz1TdqTblShapeList *)Dz1Calloc(sizeof(Dz1TdqTblShapeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqTblShapeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqTblShape_cmp,
				(Dz1DelFunc)Dz1TdqTblShape_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqTblShapeList_count;
			ret->travel = Dz1TdqTblShapeList_travelForward;
			ret->travelForward = Dz1TdqTblShapeList_travelForward;
			ret->travelBackward = Dz1TdqTblShapeList_travelBackward;
			ret->get_array = Dz1TdqTblShapeList_get_array;
			ret->add = Dz1TdqTblShapeList_add;
			ret->remove = Dz1TdqTblShapeList_remove;
			ret->find = Dz1TdqTblShapeList_find;
			ret->extract = Dz1TdqTblShapeList_extract;
			ret->cmp = Dz1TdqTblShape_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblShapeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqTblShapeList_clone(void *ptr, Dz1TdqTblShape *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqTblShapeList *p = (Dz1TdqTblShapeList *)ptr;
	Dz1TdqTblShape *cloned = Dz1TdqTblShape_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqTblShapeList *Dz1TdqTblShapeList_clone(Dz1TdqTblShapeList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqTblShapeList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqTblShapeList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqTblShapeList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqTblShapeList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblShapeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqTblShapeList_purge(Dz1TdqTblShapeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqTblShapeList_del(Dz1TdqTblShapeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqTblShapeList_dump(void *ptr, Dz1TdqTblShape *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqTblShape_dump(p, tab);
	return err;
}

void Dz1TdqTblShapeList_dump(Dz1TdqTblShapeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqTblShapeList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqTblShapeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqNameEntry
Dz1TdqNameEntry *Dz1TdqNameEntry_new(u32_t order, Dz1Str name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqNameEntry *__internal_ret = (Dz1TdqNameEntry *)Dz1Calloc(sizeof(Dz1TdqNameEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqNameEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->order = order;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqNameEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqNameEntry_copy(Dz1TdqNameEntry *dst, Dz1TdqNameEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->order = src->order;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqNameEntry *Dz1TdqNameEntry_clone(Dz1TdqNameEntry *src, Dz1Error *err)
{
	Dz1TdqNameEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqNameEntry *)Dz1Calloc(sizeof(Dz1TdqNameEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqNameEntry_delAndSetNull, (void *)&dst);
		if (Dz1TdqNameEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqNameEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqNameEntry_purge(Dz1TdqNameEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
}

void Dz1TdqNameEntry_del(Dz1TdqNameEntry *p)
{
	if (p == NULL) return;
	Dz1TdqNameEntry_purge(p);
	Dz1Free(p);
}

void Dz1TdqNameEntry_dump(Dz1TdqNameEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("order = ")); Dz1u32_dump(&p->order, tab); 
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TdqNameEntry_cmp(Dz1TdqNameEntry *a, Dz1TdqNameEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->order, &b->order)) != 0) { }
	return ret;
}
// Dz1TdqNameEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqNameList
static Dz1Error Dz1TdqNameList_add(Dz1TdqNameList *p, Dz1TdqNameEntry *data)
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

static bool_t Dz1TdqNameList_remove(Dz1TdqNameList *p, Dz1TdqNameEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqNameEntry *Dz1TdqNameList_extract(Dz1TdqNameList *p, Dz1TdqNameEntry *key)
{
	return (Dz1TdqNameEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqNameListMkArrArg
{
	Dz1TdqNameEntry **arr;
	unsigned int idx;
} Dz1TdqNameListMkArrArg;

static Dz1Error _Dz1TdqNameList_get_array(void *ptr, Dz1TdqNameEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqNameListMkArrArg *arg = (Dz1TdqNameListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqNameEntry **Dz1TdqNameList_get_array(Dz1TdqNameList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqNameEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqNameEntry **)Dz1Calloc(sizeof(Dz1TdqNameEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqNameListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqNameList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqNameList_travelForward(Dz1TdqNameList *p, Dz1Error (*func)(void *ptr, Dz1TdqNameEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqNameList_travelBackward(Dz1TdqNameList *p, Dz1Error (*func)(void *ptr, Dz1TdqNameEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqNameEntry *Dz1TdqNameList_find(Dz1TdqNameList *p, Dz1TdqNameEntry *key)
{
	return (Dz1TdqNameEntry *)Dz1AATree_find(p->storage, key);
}

static Dz1TdqNameEntry *Dz1TdqNameList_getHead(Dz1TdqNameList *p)
{
	return (Dz1TdqNameEntry *)Dz1AATree_getHead(p->storage);
}

static Dz1TdqNameEntry *Dz1TdqNameList_getTail(Dz1TdqNameList *p)
{
	return (Dz1TdqNameEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int Dz1TdqNameList_count(Dz1TdqNameList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqNameList *Dz1TdqNameList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqNameList *ret = (Dz1TdqNameList *)Dz1Calloc(sizeof(Dz1TdqNameList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqNameList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqNameEntry_cmp,
				(Dz1DelFunc)Dz1TdqNameEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqNameList_count;
			ret->travel = Dz1TdqNameList_travelForward;
			ret->travelForward = Dz1TdqNameList_travelForward;
			ret->travelBackward = Dz1TdqNameList_travelBackward;
			ret->get_array = Dz1TdqNameList_get_array;
			ret->add = Dz1TdqNameList_add;
			ret->remove = Dz1TdqNameList_remove;
			ret->find = Dz1TdqNameList_find;
			ret->extract = Dz1TdqNameList_extract;
			ret->getHead = Dz1TdqNameList_getHead;
			ret->getTail = Dz1TdqNameList_getTail;
			ret->cmp = Dz1TdqNameEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqNameList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqNameList_clone(void *ptr, Dz1TdqNameEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqNameList *p = (Dz1TdqNameList *)ptr;
	Dz1TdqNameEntry *cloned = Dz1TdqNameEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqNameList *Dz1TdqNameList_clone(Dz1TdqNameList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqNameList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqNameList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqNameList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqNameList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqNameList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqNameList_purge(Dz1TdqNameList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqNameList_del(Dz1TdqNameList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqNameList_dump(void *ptr, Dz1TdqNameEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqNameEntry_dump(p, tab);
	return err;
}

void Dz1TdqNameList_dump(Dz1TdqNameList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqNameList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqNameList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqForeignKeyMode
static struct Dz1TdqForeignKeyModeMapA
{
	str_t str;
	Dz1TdqForeignKeyMode v;
} Dz1TdqForeignKeyModeMapA[] =
{
	{ (char *)"no_action", Dz1TdqForeignKeyMode_no_action },
	{ (char *)"cascade", Dz1TdqForeignKeyMode_cascade },
	{ (char *)"set_null", Dz1TdqForeignKeyMode_set_null },
	{ (char *)"set_default", Dz1TdqForeignKeyMode_set_default },
	{ (char *)"restrict", Dz1TdqForeignKeyMode_restrict },
	{ NULL, Dz1TdqForeignKeyMode_max }
};

str_t Dz1TdqForeignKeyModeStrA(Dz1TdqForeignKeyMode v)
{
	struct Dz1TdqForeignKeyModeMapA *i = NULL;
	for (i = Dz1TdqForeignKeyModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqForeignKeyMode Dz1TdqForeignKeyModeFromStrA(str_t str)
{
	struct Dz1TdqForeignKeyModeMapA *i = NULL;
	for (i = Dz1TdqForeignKeyModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqForeignKeyMode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqForeignKeyModeMapW
{
	wstr_t str;
	Dz1TdqForeignKeyMode v;
} Dz1TdqForeignKeyModeMapW[] =
{
	{ (wchar_t *)L"no_action", Dz1TdqForeignKeyMode_no_action },
	{ (wchar_t *)L"cascade", Dz1TdqForeignKeyMode_cascade },
	{ (wchar_t *)L"set_null", Dz1TdqForeignKeyMode_set_null },
	{ (wchar_t *)L"set_default", Dz1TdqForeignKeyMode_set_default },
	{ (wchar_t *)L"restrict", Dz1TdqForeignKeyMode_restrict },
	{ NULL, Dz1TdqForeignKeyMode_max }
};

wstr_t Dz1TdqForeignKeyModeStrW(Dz1TdqForeignKeyMode v)
{
	struct Dz1TdqForeignKeyModeMapW *i = NULL;
	for (i = Dz1TdqForeignKeyModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqForeignKeyMode Dz1TdqForeignKeyModeFromStrW(wstr_t str)
{
	struct Dz1TdqForeignKeyModeMapW *i = NULL;
	for (i = Dz1TdqForeignKeyModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqForeignKeyMode_max;
}
#endif // UNIX_SYSTEM

Dz1TdqForeignKeyMode *Dz1TdqForeignKeyMode_new(Dz1TdqForeignKeyMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqForeignKeyMode *__internal_ret = (Dz1TdqForeignKeyMode *)Dz1Calloc(sizeof(Dz1TdqForeignKeyMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1TdqForeignKeyMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqFKEntry
Dz1TdqFKEntry *Dz1TdqFKEntry_new(Dz1Str suffix_name, 
								 Dz1TdqTblInstance *peer_tbl/*_ref*/, 
								 Dz1Str peer_idx_suffix_opt, 
								 Dz1TdqForeignKeyMode on_update, 
								 Dz1TdqForeignKeyMode on_delete, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqFKEntry *__internal_ret = (Dz1TdqFKEntry *)Dz1Calloc(sizeof(Dz1TdqFKEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqFKEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (suffix_name && (__internal_ret->suffix_name = Dz1Str_clone(suffix_name, errp)) == NULL) ERR_OUT(errp);
		else if (peer_idx_suffix_opt && (__internal_ret->peer_idx_suffix_opt = Dz1Str_clone(peer_idx_suffix_opt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_tbl = peer_tbl;
			__internal_ret->on_update = on_update;
			__internal_ret->on_delete = on_delete;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqFKEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqFKEntry_copy(Dz1TdqFKEntry *dst, Dz1TdqFKEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->suffix_name && (dst->suffix_name = Dz1Str_clone(src->suffix_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->own_cols && (dst->own_cols = Dz1TdqRowRef_clone(src->own_cols, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_idx_suffix_opt && (dst->peer_idx_suffix_opt = Dz1Str_clone(src->peer_idx_suffix_opt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_tbl = src->peer_tbl;
		dst->on_update = src->on_update;
		dst->on_delete = src->on_delete;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqFKEntry *Dz1TdqFKEntry_clone(Dz1TdqFKEntry *src, Dz1Error *err)
{
	Dz1TdqFKEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqFKEntry *)Dz1Calloc(sizeof(Dz1TdqFKEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqFKEntry_delAndSetNull, (void *)&dst);
		if (Dz1TdqFKEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqFKEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqFKEntry_purge(Dz1TdqFKEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->suffix_name);
	Dz1TdqRowRef_del(p->own_cols);
	Dz1Str_del(p->peer_idx_suffix_opt);
}

void Dz1TdqFKEntry_del(Dz1TdqFKEntry *p)
{
	if (p == NULL) return;
	Dz1TdqFKEntry_purge(p);
	Dz1Free(p);
}

int Dz1TdqFKEntry_cmp(Dz1TdqFKEntry *a, Dz1TdqFKEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->suffix_name == NULL && b->suffix_name == NULL) ret = 0;
	else if (a->suffix_name == NULL /*&& b->suffix_name != NULL*/) ret = -1;
	else if (/*a->suffix_name != NULL &&*/ b->suffix_name == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->suffix_name, b->suffix_name)) != 0) { }
	return ret;
}
// Dz1TdqFKEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqFKList
static Dz1Error Dz1TdqFKList_add(Dz1TdqFKList *p, Dz1TdqFKEntry *data)
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

static bool_t Dz1TdqFKList_remove(Dz1TdqFKList *p, Dz1TdqFKEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqFKEntry *Dz1TdqFKList_extract(Dz1TdqFKList *p, Dz1TdqFKEntry *key)
{
	return (Dz1TdqFKEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqFKListMkArrArg
{
	Dz1TdqFKEntry **arr;
	unsigned int idx;
} Dz1TdqFKListMkArrArg;

static Dz1Error _Dz1TdqFKList_get_array(void *ptr, Dz1TdqFKEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqFKListMkArrArg *arg = (Dz1TdqFKListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqFKEntry **Dz1TdqFKList_get_array(Dz1TdqFKList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqFKEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqFKEntry **)Dz1Calloc(sizeof(Dz1TdqFKEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqFKListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqFKList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqFKList_travelForward(Dz1TdqFKList *p, Dz1Error (*func)(void *ptr, Dz1TdqFKEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqFKList_travelBackward(Dz1TdqFKList *p, Dz1Error (*func)(void *ptr, Dz1TdqFKEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqFKEntry *Dz1TdqFKList_find(Dz1TdqFKList *p, Dz1TdqFKEntry *key)
{
	return (Dz1TdqFKEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqFKList_count(Dz1TdqFKList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqFKList *Dz1TdqFKList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqFKList *ret = (Dz1TdqFKList *)Dz1Calloc(sizeof(Dz1TdqFKList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqFKList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqFKEntry_cmp,
				(Dz1DelFunc)Dz1TdqFKEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqFKList_count;
			ret->travel = Dz1TdqFKList_travelForward;
			ret->travelForward = Dz1TdqFKList_travelForward;
			ret->travelBackward = Dz1TdqFKList_travelBackward;
			ret->get_array = Dz1TdqFKList_get_array;
			ret->add = Dz1TdqFKList_add;
			ret->remove = Dz1TdqFKList_remove;
			ret->find = Dz1TdqFKList_find;
			ret->extract = Dz1TdqFKList_extract;
			ret->cmp = Dz1TdqFKEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqFKList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqFKList_clone(void *ptr, Dz1TdqFKEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqFKList *p = (Dz1TdqFKList *)ptr;
	Dz1TdqFKEntry *cloned = Dz1TdqFKEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqFKList *Dz1TdqFKList_clone(Dz1TdqFKList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqFKList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqFKList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqFKList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqFKList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqFKList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqFKList_purge(Dz1TdqFKList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqFKList_del(Dz1TdqFKList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqFKList_dump(void *ptr, Dz1TdqFKEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqFKEntry_dump(p, tab);
	return err;
}

void Dz1TdqFKList_dump(Dz1TdqFKList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqFKList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqFKList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblInstance
Dz1TdqTblInstance *Dz1TdqTblInstance_new(Dz1Str name, 
										 Dz1TdqTblShape *shape/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqTblInstance *__internal_ret = (Dz1TdqTblInstance *)Dz1Calloc(sizeof(Dz1TdqTblInstance), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqTblInstance_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->fks = Dz1TdqFKList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->shape = shape;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblInstance_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqTblInstance_copy(Dz1TdqTblInstance *dst, Dz1TdqTblInstance *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->fks && (dst->fks = Dz1TdqFKList_clone(src->fks, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->shape = src->shape;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqTblInstance *Dz1TdqTblInstance_clone(Dz1TdqTblInstance *src, Dz1Error *err)
{
	Dz1TdqTblInstance *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqTblInstance *)Dz1Calloc(sizeof(Dz1TdqTblInstance), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqTblInstance_delAndSetNull, (void *)&dst);
		if (Dz1TdqTblInstance_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblInstance_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqTblInstance_purge(Dz1TdqTblInstance *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1TdqFKList_del(p->fks);
}

void Dz1TdqTblInstance_del(Dz1TdqTblInstance *p)
{
	if (p == NULL) return;
	Dz1TdqTblInstance_purge(p);
	Dz1Free(p);
}

int Dz1TdqTblInstance_cmp(Dz1TdqTblInstance *a, Dz1TdqTblInstance *b)
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
// Dz1TdqTblInstance
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblInstanceList
static Dz1Error Dz1TdqTblInstanceList_add(Dz1TdqTblInstanceList *p, Dz1TdqTblInstance *data)
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

static bool_t Dz1TdqTblInstanceList_remove(Dz1TdqTblInstanceList *p, Dz1TdqTblInstance *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqTblInstance *Dz1TdqTblInstanceList_extract(Dz1TdqTblInstanceList *p, Dz1TdqTblInstance *key)
{
	return (Dz1TdqTblInstance *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqTblInstanceListMkArrArg
{
	Dz1TdqTblInstance **arr;
	unsigned int idx;
} Dz1TdqTblInstanceListMkArrArg;

static Dz1Error _Dz1TdqTblInstanceList_get_array(void *ptr, Dz1TdqTblInstance *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqTblInstanceListMkArrArg *arg = (Dz1TdqTblInstanceListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqTblInstance **Dz1TdqTblInstanceList_get_array(Dz1TdqTblInstanceList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqTblInstance **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqTblInstance **)Dz1Calloc(sizeof(Dz1TdqTblInstance *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqTblInstanceListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqTblInstanceList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqTblInstanceList_travelForward(Dz1TdqTblInstanceList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqTblInstanceList_travelBackward(Dz1TdqTblInstanceList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqTblInstance *Dz1TdqTblInstanceList_find(Dz1TdqTblInstanceList *p, Dz1TdqTblInstance *key)
{
	return (Dz1TdqTblInstance *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqTblInstanceList_count(Dz1TdqTblInstanceList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqTblInstanceList *Dz1TdqTblInstanceList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqTblInstanceList *ret = (Dz1TdqTblInstanceList *)Dz1Calloc(sizeof(Dz1TdqTblInstanceList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqTblInstanceList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqTblInstance_cmp,
				(Dz1DelFunc)Dz1TdqTblInstance_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqTblInstanceList_count;
			ret->travel = Dz1TdqTblInstanceList_travelForward;
			ret->travelForward = Dz1TdqTblInstanceList_travelForward;
			ret->travelBackward = Dz1TdqTblInstanceList_travelBackward;
			ret->get_array = Dz1TdqTblInstanceList_get_array;
			ret->add = Dz1TdqTblInstanceList_add;
			ret->remove = Dz1TdqTblInstanceList_remove;
			ret->find = Dz1TdqTblInstanceList_find;
			ret->extract = Dz1TdqTblInstanceList_extract;
			ret->cmp = Dz1TdqTblInstance_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblInstanceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqTblInstanceList_clone(void *ptr, Dz1TdqTblInstance *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqTblInstanceList *p = (Dz1TdqTblInstanceList *)ptr;
	Dz1TdqTblInstance *cloned = Dz1TdqTblInstance_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqTblInstanceList *Dz1TdqTblInstanceList_clone(Dz1TdqTblInstanceList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqTblInstanceList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqTblInstanceList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqTblInstanceList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqTblInstanceList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblInstanceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqTblInstanceList_purge(Dz1TdqTblInstanceList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqTblInstanceList_del(Dz1TdqTblInstanceList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqTblInstanceList_dump(void *ptr, Dz1TdqTblInstance *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqTblInstance_dump(p, tab);
	return err;
}

void Dz1TdqTblInstanceList_dump(Dz1TdqTblInstanceList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqTblInstanceList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqTblInstanceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblInstanceSeq
static Dz1Error Dz1TdqTblInstanceSeq_add(Dz1TdqTblInstanceSeq *p, Dz1TdqTblInstance *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqTblInstanceSeqMkArrArg
{
	Dz1TdqTblInstance **arr;
	unsigned int idx;
} Dz1TdqTblInstanceSeqMkArrArg;

static Dz1Error _Dz1TdqTblInstanceSeq_get_array(void *ptr, Dz1TdqTblInstance *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqTblInstanceSeqMkArrArg *arg = (Dz1TdqTblInstanceSeqMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqTblInstance **Dz1TdqTblInstanceSeq_get_array(Dz1TdqTblInstanceSeq *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqTblInstance **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqTblInstance **)Dz1Calloc(sizeof(Dz1TdqTblInstance *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqTblInstanceSeqMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqTblInstanceSeq_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqTblInstanceSeq_travelForward(Dz1TdqTblInstanceSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqTblInstanceSeq_travelBackward(Dz1TdqTblInstanceSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqTblInstanceSeq_count(Dz1TdqTblInstanceSeq *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqTblInstanceSeq *Dz1TdqTblInstanceSeq_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqTblInstanceSeq *ret = (Dz1TdqTblInstanceSeq *)Dz1Calloc(sizeof(Dz1TdqTblInstanceSeq), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqTblInstanceSeq_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqTblInstanceSeq_count;
			ret->travel = Dz1TdqTblInstanceSeq_travelForward;
			ret->travelForward = Dz1TdqTblInstanceSeq_travelForward;
			ret->travelBackward = Dz1TdqTblInstanceSeq_travelBackward;
			ret->get_array = Dz1TdqTblInstanceSeq_get_array;
			ret->add = Dz1TdqTblInstanceSeq_add;
			ret->cmp = Dz1TdqTblInstance_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblInstanceSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqTblInstanceSeq_clone(void *ptr, Dz1TdqTblInstance *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqTblInstanceSeq *p = (Dz1TdqTblInstanceSeq *)ptr;
	Dz1TdqTblInstance *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqTblInstanceSeq *Dz1TdqTblInstanceSeq_clone(Dz1TdqTblInstanceSeq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqTblInstanceSeq *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqTblInstanceSeq_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqTblInstanceSeq_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqTblInstanceSeq_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqTblInstanceSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqTblInstanceSeq_purge(Dz1TdqTblInstanceSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqTblInstanceSeq_del(Dz1TdqTblInstanceSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqTblInstanceSeq_dump(void *ptr, Dz1TdqTblInstance *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqTblInstance_dump(p, tab);
	return err;
}

void Dz1TdqTblInstanceSeq_dump(Dz1TdqTblInstanceSeq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqTblInstanceSeq_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqTblInstanceSeq
////////////////////////////////////////////////////////////////////////////////

