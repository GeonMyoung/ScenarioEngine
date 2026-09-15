////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdqc_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcShapeOptEntry
Dz1TdqcShapeOptEntry *Dz1TdqcShapeOptEntry_new(Dz1Str instance, 
											   Dz1Str api_prefix, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcShapeOptEntry *__internal_ret = (Dz1TdqcShapeOptEntry *)Dz1Calloc(sizeof(Dz1TdqcShapeOptEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (instance && (__internal_ret->instance = Dz1Str_clone(instance, errp)) == NULL) ERR_OUT(errp);
		else if (api_prefix && (__internal_ret->api_prefix = Dz1Str_clone(api_prefix, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqcShapeOptEntry_copy(Dz1TdqcShapeOptEntry *dst, Dz1TdqcShapeOptEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->instance && (dst->instance = Dz1Str_clone(src->instance, errp)) == NULL) ERR_OUT(errp);
	else if (src->api_prefix && (dst->api_prefix = Dz1Str_clone(src->api_prefix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqcShapeOptEntry *Dz1TdqcShapeOptEntry_clone(Dz1TdqcShapeOptEntry *src, Dz1Error *err)
{
	Dz1TdqcShapeOptEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqcShapeOptEntry *)Dz1Calloc(sizeof(Dz1TdqcShapeOptEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&dst);
		if (Dz1TdqcShapeOptEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqcShapeOptEntry_purge(Dz1TdqcShapeOptEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->instance);
	Dz1Str_del(p->api_prefix);
}

void Dz1TdqcShapeOptEntry_del(Dz1TdqcShapeOptEntry *p)
{
	if (p == NULL) return;
	Dz1TdqcShapeOptEntry_purge(p);
	Dz1Free(p);
}

void Dz1TdqcShapeOptEntry_dump(Dz1TdqcShapeOptEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("instance = ")); Dz1Str_dump(p->instance, tab); 
		Dz1Thread_tprintf(tab, Dz1T("api_prefix = ")); Dz1Str_dump(p->api_prefix, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TdqcShapeOptEntry_cmp(Dz1TdqcShapeOptEntry *a, Dz1TdqcShapeOptEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->instance == NULL && b->instance == NULL) ret = 0;
	else if (a->instance == NULL /*&& b->instance != NULL*/) ret = -1;
	else if (/*a->instance != NULL &&*/ b->instance == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->instance, b->instance)) != 0) { }
	return ret;
}
// Dz1TdqcShapeOptEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcShapeOptList
static Dz1Error Dz1TdqcShapeOptList_add(Dz1TdqcShapeOptList *p, Dz1TdqcShapeOptEntry *data)
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

static bool_t Dz1TdqcShapeOptList_remove(Dz1TdqcShapeOptList *p, Dz1TdqcShapeOptEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqcShapeOptEntry *Dz1TdqcShapeOptList_extract(Dz1TdqcShapeOptList *p, Dz1TdqcShapeOptEntry *key)
{
	return (Dz1TdqcShapeOptEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqcShapeOptListMkArrArg
{
	Dz1TdqcShapeOptEntry **arr;
	unsigned int idx;
} Dz1TdqcShapeOptListMkArrArg;

static Dz1Error _Dz1TdqcShapeOptList_get_array(void *ptr, Dz1TdqcShapeOptEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcShapeOptListMkArrArg *arg = (Dz1TdqcShapeOptListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqcShapeOptEntry **Dz1TdqcShapeOptList_get_array(Dz1TdqcShapeOptList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqcShapeOptEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqcShapeOptEntry **)Dz1Calloc(sizeof(Dz1TdqcShapeOptEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqcShapeOptListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqcShapeOptList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqcShapeOptList_travelForward(Dz1TdqcShapeOptList *p, Dz1Error (*func)(void *ptr, Dz1TdqcShapeOptEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqcShapeOptList_travelBackward(Dz1TdqcShapeOptList *p, Dz1Error (*func)(void *ptr, Dz1TdqcShapeOptEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqcShapeOptEntry *Dz1TdqcShapeOptList_find(Dz1TdqcShapeOptList *p, Dz1TdqcShapeOptEntry *key)
{
	return (Dz1TdqcShapeOptEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqcShapeOptList_count(Dz1TdqcShapeOptList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqcShapeOptList *Dz1TdqcShapeOptList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcShapeOptList *ret = (Dz1TdqcShapeOptList *)Dz1Calloc(sizeof(Dz1TdqcShapeOptList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcShapeOptList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqcShapeOptEntry_cmp,
				(Dz1DelFunc)Dz1TdqcShapeOptEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqcShapeOptList_count;
			ret->travel = Dz1TdqcShapeOptList_travelForward;
			ret->travelForward = Dz1TdqcShapeOptList_travelForward;
			ret->travelBackward = Dz1TdqcShapeOptList_travelBackward;
			ret->get_array = Dz1TdqcShapeOptList_get_array;
			ret->add = Dz1TdqcShapeOptList_add;
			ret->remove = Dz1TdqcShapeOptList_remove;
			ret->find = Dz1TdqcShapeOptList_find;
			ret->extract = Dz1TdqcShapeOptList_extract;
			ret->cmp = Dz1TdqcShapeOptEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcShapeOptList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqcShapeOptList_clone(void *ptr, Dz1TdqcShapeOptEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcShapeOptList *p = (Dz1TdqcShapeOptList *)ptr;
	Dz1TdqcShapeOptEntry *cloned = Dz1TdqcShapeOptEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqcShapeOptList *Dz1TdqcShapeOptList_clone(Dz1TdqcShapeOptList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcShapeOptList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqcShapeOptList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcShapeOptList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqcShapeOptList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcShapeOptList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqcShapeOptList_purge(Dz1TdqcShapeOptList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqcShapeOptList_del(Dz1TdqcShapeOptList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqcShapeOptList_dump(void *ptr, Dz1TdqcShapeOptEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqcShapeOptEntry_dump(p, tab);
	return err;
}

void Dz1TdqcShapeOptList_dump(Dz1TdqcShapeOptList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqcShapeOptList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqcShapeOptList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcShape
Dz1TdqcShape *Dz1TdqcShape_new(Dz1Str name, 
							   ObjectInfo *src_obj/*_ref*/, 
							   ObjectInfo *dst_obj/*_ref*/, 
							   Dz1TdqTblShape *target, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcShape *__internal_ret = (Dz1TdqcShape *)Dz1Calloc(sizeof(Dz1TdqcShape), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqcShape_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->memb_opt = Dz1TdqcShapeOptList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->src_obj = src_obj;
			__internal_ret->dst_obj = dst_obj;
			__internal_ret->target = target;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcShape_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqcShape_copy(Dz1TdqcShape *dst, Dz1TdqcShape *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->memb_opt && (dst->memb_opt = Dz1TdqcShapeOptList_clone(src->memb_opt, errp)) == NULL) ERR_OUT(errp);
	else if (src->target && (dst->target = Dz1TdqTblShape_clone(src->target, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->src_obj = src->src_obj;
		dst->dst_obj = src->dst_obj;
		dst->is_qurty_shape = src->is_qurty_shape;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqcShape *Dz1TdqcShape_clone(Dz1TdqcShape *src, Dz1Error *err)
{
	Dz1TdqcShape *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqcShape *)Dz1Calloc(sizeof(Dz1TdqcShape), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqcShape_delAndSetNull, (void *)&dst);
		if (Dz1TdqcShape_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcShape_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqcShape_purge(Dz1TdqcShape *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1TdqcShapeOptList_del(p->memb_opt);
	Dz1TdqTblShape_del(p->target);
}

void Dz1TdqcShape_del(Dz1TdqcShape *p)
{
	if (p == NULL) return;
	Dz1TdqcShape_purge(p);
	Dz1Free(p);
}

void Dz1TdqcShape_dump(Dz1TdqcShape *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("src_obj = ")); ObjectInfo_dump(p->src_obj, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("dst_obj = ")); ObjectInfo_dump(p->dst_obj, tab); 
		Dz1Thread_tprintf(tab, Dz1T("memb_opt = ")); Dz1TdqcShapeOptList_dump(p->memb_opt, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("target = ")); Dz1TdqTblShape_dump(p->target, tab); 
		Dz1Thread_tprintf(tab, Dz1T("is_qurty_shape = ")); Dz1Bool_dump(&p->is_qurty_shape, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TdqcShape_cmp(Dz1TdqcShape *a, Dz1TdqcShape *b)
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
// Dz1TdqcShape
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcShapeList
static Dz1Error Dz1TdqcShapeList_add(Dz1TdqcShapeList *p, Dz1TdqcShape *data)
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

static bool_t Dz1TdqcShapeList_remove(Dz1TdqcShapeList *p, Dz1TdqcShape *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqcShape *Dz1TdqcShapeList_extract(Dz1TdqcShapeList *p, Dz1TdqcShape *key)
{
	return (Dz1TdqcShape *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqcShapeListMkArrArg
{
	Dz1TdqcShape **arr;
	unsigned int idx;
} Dz1TdqcShapeListMkArrArg;

static Dz1Error _Dz1TdqcShapeList_get_array(void *ptr, Dz1TdqcShape *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcShapeListMkArrArg *arg = (Dz1TdqcShapeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqcShape **Dz1TdqcShapeList_get_array(Dz1TdqcShapeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqcShape **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqcShape **)Dz1Calloc(sizeof(Dz1TdqcShape *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqcShapeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqcShapeList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqcShapeList_travelForward(Dz1TdqcShapeList *p, Dz1Error (*func)(void *ptr, Dz1TdqcShape *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqcShapeList_travelBackward(Dz1TdqcShapeList *p, Dz1Error (*func)(void *ptr, Dz1TdqcShape *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqcShape *Dz1TdqcShapeList_find(Dz1TdqcShapeList *p, Dz1TdqcShape *key)
{
	return (Dz1TdqcShape *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqcShapeList_count(Dz1TdqcShapeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqcShapeList *Dz1TdqcShapeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcShapeList *ret = (Dz1TdqcShapeList *)Dz1Calloc(sizeof(Dz1TdqcShapeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcShapeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqcShape_cmp,
				(Dz1DelFunc)Dz1TdqcShape_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqcShapeList_count;
			ret->travel = Dz1TdqcShapeList_travelForward;
			ret->travelForward = Dz1TdqcShapeList_travelForward;
			ret->travelBackward = Dz1TdqcShapeList_travelBackward;
			ret->get_array = Dz1TdqcShapeList_get_array;
			ret->add = Dz1TdqcShapeList_add;
			ret->remove = Dz1TdqcShapeList_remove;
			ret->find = Dz1TdqcShapeList_find;
			ret->extract = Dz1TdqcShapeList_extract;
			ret->cmp = Dz1TdqcShape_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcShapeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqcShapeList_clone(void *ptr, Dz1TdqcShape *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcShapeList *p = (Dz1TdqcShapeList *)ptr;
	Dz1TdqcShape *cloned = Dz1TdqcShape_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqcShapeList *Dz1TdqcShapeList_clone(Dz1TdqcShapeList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcShapeList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqcShapeList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcShapeList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqcShapeList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcShapeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqcShapeList_purge(Dz1TdqcShapeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqcShapeList_del(Dz1TdqcShapeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqcShapeList_dump(void *ptr, Dz1TdqcShape *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqcShape_dump(p, tab);
	return err;
}

void Dz1TdqcShapeList_dump(Dz1TdqcShapeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqcShapeList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqcShapeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcTblInstance
Dz1TdqcTblInstance *Dz1TdqcTblInstance_new(Dz1Str name, 
										   Dz1TdqcShape *shape/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcTblInstance *__internal_ret = (Dz1TdqcTblInstance *)Dz1Calloc(sizeof(Dz1TdqcTblInstance), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqcTblInstance_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->fks = Dz1TdqFKList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->shape = shape;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcTblInstance_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqcTblInstance_copy(Dz1TdqcTblInstance *dst, Dz1TdqcTblInstance *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->fks && (dst->fks = Dz1TdqFKList_clone(src->fks, errp)) == NULL) ERR_OUT(errp);
	else if (src->prefix && (dst->prefix = Dz1Str_clone(src->prefix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->shape = src->shape;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqcTblInstance *Dz1TdqcTblInstance_clone(Dz1TdqcTblInstance *src, Dz1Error *err)
{
	Dz1TdqcTblInstance *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqcTblInstance *)Dz1Calloc(sizeof(Dz1TdqcTblInstance), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqcTblInstance_delAndSetNull, (void *)&dst);
		if (Dz1TdqcTblInstance_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcTblInstance_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqcTblInstance_purge(Dz1TdqcTblInstance *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1TdqFKList_del(p->fks);
	Dz1Str_del(p->prefix);
}

void Dz1TdqcTblInstance_del(Dz1TdqcTblInstance *p)
{
	if (p == NULL) return;
	Dz1TdqcTblInstance_purge(p);
	Dz1Free(p);
}

int Dz1TdqcTblInstance_cmp(Dz1TdqcTblInstance *a, Dz1TdqcTblInstance *b)
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
// Dz1TdqcTblInstance
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcTblInstanceList
static Dz1Error Dz1TdqcTblInstanceList_add(Dz1TdqcTblInstanceList *p, Dz1TdqcTblInstance *data)
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

static bool_t Dz1TdqcTblInstanceList_remove(Dz1TdqcTblInstanceList *p, Dz1TdqcTblInstance *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqcTblInstance *Dz1TdqcTblInstanceList_extract(Dz1TdqcTblInstanceList *p, Dz1TdqcTblInstance *key)
{
	return (Dz1TdqcTblInstance *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqcTblInstanceListMkArrArg
{
	Dz1TdqcTblInstance **arr;
	unsigned int idx;
} Dz1TdqcTblInstanceListMkArrArg;

static Dz1Error _Dz1TdqcTblInstanceList_get_array(void *ptr, Dz1TdqcTblInstance *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcTblInstanceListMkArrArg *arg = (Dz1TdqcTblInstanceListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqcTblInstance **Dz1TdqcTblInstanceList_get_array(Dz1TdqcTblInstanceList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqcTblInstance **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqcTblInstance **)Dz1Calloc(sizeof(Dz1TdqcTblInstance *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqcTblInstanceListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqcTblInstanceList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqcTblInstanceList_travelForward(Dz1TdqcTblInstanceList *p, Dz1Error (*func)(void *ptr, Dz1TdqcTblInstance *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqcTblInstanceList_travelBackward(Dz1TdqcTblInstanceList *p, Dz1Error (*func)(void *ptr, Dz1TdqcTblInstance *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqcTblInstance *Dz1TdqcTblInstanceList_find(Dz1TdqcTblInstanceList *p, Dz1TdqcTblInstance *key)
{
	return (Dz1TdqcTblInstance *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqcTblInstanceList_count(Dz1TdqcTblInstanceList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqcTblInstanceList *Dz1TdqcTblInstanceList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcTblInstanceList *ret = (Dz1TdqcTblInstanceList *)Dz1Calloc(sizeof(Dz1TdqcTblInstanceList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcTblInstanceList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqcTblInstance_cmp,
				(Dz1DelFunc)Dz1TdqcTblInstance_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqcTblInstanceList_count;
			ret->travel = Dz1TdqcTblInstanceList_travelForward;
			ret->travelForward = Dz1TdqcTblInstanceList_travelForward;
			ret->travelBackward = Dz1TdqcTblInstanceList_travelBackward;
			ret->get_array = Dz1TdqcTblInstanceList_get_array;
			ret->add = Dz1TdqcTblInstanceList_add;
			ret->remove = Dz1TdqcTblInstanceList_remove;
			ret->find = Dz1TdqcTblInstanceList_find;
			ret->extract = Dz1TdqcTblInstanceList_extract;
			ret->cmp = Dz1TdqcTblInstance_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcTblInstanceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqcTblInstanceList_clone(void *ptr, Dz1TdqcTblInstance *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcTblInstanceList *p = (Dz1TdqcTblInstanceList *)ptr;
	Dz1TdqcTblInstance *cloned = Dz1TdqcTblInstance_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqcTblInstanceList *Dz1TdqcTblInstanceList_clone(Dz1TdqcTblInstanceList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcTblInstanceList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqcTblInstanceList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcTblInstanceList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqcTblInstanceList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcTblInstanceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqcTblInstanceList_purge(Dz1TdqcTblInstanceList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqcTblInstanceList_del(Dz1TdqcTblInstanceList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqcTblInstanceList_dump(void *ptr, Dz1TdqcTblInstance *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqcTblInstance_dump(p, tab);
	return err;
}

void Dz1TdqcTblInstanceList_dump(Dz1TdqcTblInstanceList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqcTblInstanceList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqcTblInstanceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcTblInstanceSeq
static Dz1Error Dz1TdqcTblInstanceSeq_add(Dz1TdqcTblInstanceSeq *p, Dz1TdqcTblInstance *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqcTblInstanceSeqMkArrArg
{
	Dz1TdqcTblInstance **arr;
	unsigned int idx;
} Dz1TdqcTblInstanceSeqMkArrArg;

static Dz1Error _Dz1TdqcTblInstanceSeq_get_array(void *ptr, Dz1TdqcTblInstance *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcTblInstanceSeqMkArrArg *arg = (Dz1TdqcTblInstanceSeqMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqcTblInstance **Dz1TdqcTblInstanceSeq_get_array(Dz1TdqcTblInstanceSeq *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqcTblInstance **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqcTblInstance **)Dz1Calloc(sizeof(Dz1TdqcTblInstance *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqcTblInstanceSeqMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqcTblInstanceSeq_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqcTblInstanceSeq_travelForward(Dz1TdqcTblInstanceSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqcTblInstance *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqcTblInstanceSeq_travelBackward(Dz1TdqcTblInstanceSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqcTblInstance *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqcTblInstanceSeq_count(Dz1TdqcTblInstanceSeq *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqcTblInstanceSeq *Dz1TdqcTblInstanceSeq_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcTblInstanceSeq *ret = (Dz1TdqcTblInstanceSeq *)Dz1Calloc(sizeof(Dz1TdqcTblInstanceSeq), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcTblInstanceSeq_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqcTblInstanceSeq_count;
			ret->travel = Dz1TdqcTblInstanceSeq_travelForward;
			ret->travelForward = Dz1TdqcTblInstanceSeq_travelForward;
			ret->travelBackward = Dz1TdqcTblInstanceSeq_travelBackward;
			ret->get_array = Dz1TdqcTblInstanceSeq_get_array;
			ret->add = Dz1TdqcTblInstanceSeq_add;
			ret->cmp = Dz1TdqcTblInstance_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcTblInstanceSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqcTblInstanceSeq_clone(void *ptr, Dz1TdqcTblInstance *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcTblInstanceSeq *p = (Dz1TdqcTblInstanceSeq *)ptr;
	Dz1TdqcTblInstance *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqcTblInstanceSeq *Dz1TdqcTblInstanceSeq_clone(Dz1TdqcTblInstanceSeq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcTblInstanceSeq *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqcTblInstanceSeq_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcTblInstanceSeq_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqcTblInstanceSeq_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcTblInstanceSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqcTblInstanceSeq_purge(Dz1TdqcTblInstanceSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqcTblInstanceSeq_del(Dz1TdqcTblInstanceSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqcTblInstanceSeq_dump(void *ptr, Dz1TdqcTblInstance *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqcTblInstance_dump(p, tab);
	return err;
}

void Dz1TdqcTblInstanceSeq_dump(Dz1TdqcTblInstanceSeq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqcTblInstanceSeq_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqcTblInstanceSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcQuery
Dz1TdqcQuery *Dz1TdqcQuery_new(Dz1Str name, 
							   ObjectInfo *src_obj/*_ref*/, 
							   ObjectInfo *dst_obj/*_ref*/, 
							   Dz1TdqQryRow *sel, 
							   Dz1TdqQueryTblSpec *from, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcQuery *__internal_ret = (Dz1TdqcQuery *)Dz1Calloc(sizeof(Dz1TdqcQuery), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqcQuery_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->groupby = Dz1TdqQryRefCols_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->memb_opt = Dz1TdqcShapeOptList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->src_obj = src_obj;
			__internal_ret->dst_obj = dst_obj;
			__internal_ret->sel = sel;
			__internal_ret->from = from;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcQuery_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqcQuery_copy(Dz1TdqcQuery *dst, Dz1TdqcQuery *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->sel && (dst->sel = Dz1TdqQryRow_clone(src->sel, errp)) == NULL) ERR_OUT(errp);
	else if (src->from && (dst->from = Dz1TdqQueryTblSpec_clone(src->from, errp)) == NULL) ERR_OUT(errp);
	else if (src->groupby && (dst->groupby = Dz1TdqQryRefCols_clone(src->groupby, errp)) == NULL) ERR_OUT(errp);
	else if (src->memb_opt && (dst->memb_opt = Dz1TdqcShapeOptList_clone(src->memb_opt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->src_obj = src->src_obj;
		dst->dst_obj = src->dst_obj;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqcQuery *Dz1TdqcQuery_clone(Dz1TdqcQuery *src, Dz1Error *err)
{
	Dz1TdqcQuery *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqcQuery *)Dz1Calloc(sizeof(Dz1TdqcQuery), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqcQuery_delAndSetNull, (void *)&dst);
		if (Dz1TdqcQuery_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcQuery_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqcQuery_purge(Dz1TdqcQuery *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1TdqQryRow_del(p->sel);
	Dz1TdqQueryTblSpec_del(p->from);
	Dz1TdqQryRefCols_del(p->groupby);
	Dz1TdqcShapeOptList_del(p->memb_opt);
}

void Dz1TdqcQuery_del(Dz1TdqcQuery *p)
{
	if (p == NULL) return;
	Dz1TdqcQuery_purge(p);
	Dz1Free(p);
}

void Dz1TdqcQuery_dump(Dz1TdqcQuery *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("src_obj = ")); ObjectInfo_dump(p->src_obj, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("dst_obj = ")); ObjectInfo_dump(p->dst_obj, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sel = ")); Dz1TdqQryRow_dump(p->sel, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("from = ")); Dz1TdqQueryTblSpec_dump(p->from, tab); 
		Dz1Thread_tprintf(tab, Dz1T("groupby = ")); Dz1TdqQryRefCols_dump(p->groupby, tab); 
		Dz1Thread_tprintf(tab, Dz1T("memb_opt = ")); Dz1TdqcShapeOptList_dump(p->memb_opt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TdqcQuery_cmp(Dz1TdqcQuery *a, Dz1TdqcQuery *b)
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
// Dz1TdqcQuery
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcQueryList
static Dz1Error Dz1TdqcQueryList_add(Dz1TdqcQueryList *p, Dz1TdqcQuery *data)
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

static bool_t Dz1TdqcQueryList_remove(Dz1TdqcQueryList *p, Dz1TdqcQuery *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqcQuery *Dz1TdqcQueryList_extract(Dz1TdqcQueryList *p, Dz1TdqcQuery *key)
{
	return (Dz1TdqcQuery *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqcQueryListMkArrArg
{
	Dz1TdqcQuery **arr;
	unsigned int idx;
} Dz1TdqcQueryListMkArrArg;

static Dz1Error _Dz1TdqcQueryList_get_array(void *ptr, Dz1TdqcQuery *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcQueryListMkArrArg *arg = (Dz1TdqcQueryListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqcQuery **Dz1TdqcQueryList_get_array(Dz1TdqcQueryList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqcQuery **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqcQuery **)Dz1Calloc(sizeof(Dz1TdqcQuery *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqcQueryListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqcQueryList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqcQueryList_travelForward(Dz1TdqcQueryList *p, Dz1Error (*func)(void *ptr, Dz1TdqcQuery *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqcQueryList_travelBackward(Dz1TdqcQueryList *p, Dz1Error (*func)(void *ptr, Dz1TdqcQuery *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqcQuery *Dz1TdqcQueryList_find(Dz1TdqcQueryList *p, Dz1TdqcQuery *key)
{
	return (Dz1TdqcQuery *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqcQueryList_count(Dz1TdqcQueryList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqcQueryList *Dz1TdqcQueryList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcQueryList *ret = (Dz1TdqcQueryList *)Dz1Calloc(sizeof(Dz1TdqcQueryList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcQueryList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqcQuery_cmp,
				(Dz1DelFunc)Dz1TdqcQuery_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqcQueryList_count;
			ret->travel = Dz1TdqcQueryList_travelForward;
			ret->travelForward = Dz1TdqcQueryList_travelForward;
			ret->travelBackward = Dz1TdqcQueryList_travelBackward;
			ret->get_array = Dz1TdqcQueryList_get_array;
			ret->add = Dz1TdqcQueryList_add;
			ret->remove = Dz1TdqcQueryList_remove;
			ret->find = Dz1TdqcQueryList_find;
			ret->extract = Dz1TdqcQueryList_extract;
			ret->cmp = Dz1TdqcQuery_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcQueryList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqcQueryList_clone(void *ptr, Dz1TdqcQuery *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcQueryList *p = (Dz1TdqcQueryList *)ptr;
	Dz1TdqcQuery *cloned = Dz1TdqcQuery_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqcQueryList *Dz1TdqcQueryList_clone(Dz1TdqcQueryList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcQueryList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqcQueryList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcQueryList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqcQueryList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcQueryList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqcQueryList_purge(Dz1TdqcQueryList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqcQueryList_del(Dz1TdqcQueryList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqcQueryList_dump(void *ptr, Dz1TdqcQuery *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqcQuery_dump(p, tab);
	return err;
}

void Dz1TdqcQueryList_dump(Dz1TdqcQueryList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqcQueryList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqcQueryList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcOrderEntryPresent
static struct Dz1TdqcOrderEntryPresentMapA
{
	str_t str;
	Dz1TdqcOrderEntryPresent v;
} Dz1TdqcOrderEntryPresentMapA[] =
{
	{ (char *)"shp", Dz1TdqcOrderEntryPresent_shp },
	{ (char *)"tbl", Dz1TdqcOrderEntryPresent_tbl },
	{ (char *)"qry", Dz1TdqcOrderEntryPresent_qry },
	{ NULL, Dz1TdqcOrderEntryPresent_max }
};

str_t Dz1TdqcOrderEntryPresentStrA(Dz1TdqcOrderEntryPresent v)
{
	struct Dz1TdqcOrderEntryPresentMapA *i = NULL;
	for (i = Dz1TdqcOrderEntryPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqcOrderEntryPresent Dz1TdqcOrderEntryPresentFromStrA(str_t str)
{
	struct Dz1TdqcOrderEntryPresentMapA *i = NULL;
	for (i = Dz1TdqcOrderEntryPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqcOrderEntryPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqcOrderEntryPresentMapW
{
	wstr_t str;
	Dz1TdqcOrderEntryPresent v;
} Dz1TdqcOrderEntryPresentMapW[] =
{
	{ (wchar_t *)L"shp", Dz1TdqcOrderEntryPresent_shp },
	{ (wchar_t *)L"tbl", Dz1TdqcOrderEntryPresent_tbl },
	{ (wchar_t *)L"qry", Dz1TdqcOrderEntryPresent_qry },
	{ NULL, Dz1TdqcOrderEntryPresent_max }
};

wstr_t Dz1TdqcOrderEntryPresentStrW(Dz1TdqcOrderEntryPresent v)
{
	struct Dz1TdqcOrderEntryPresentMapW *i = NULL;
	for (i = Dz1TdqcOrderEntryPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqcOrderEntryPresent Dz1TdqcOrderEntryPresentFromStrW(wstr_t str)
{
	struct Dz1TdqcOrderEntryPresentMapW *i = NULL;
	for (i = Dz1TdqcOrderEntryPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqcOrderEntryPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TdqcOrderEntryPresent *Dz1TdqcOrderEntryPresent_new(Dz1TdqcOrderEntryPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcOrderEntryPresent *__internal_ret = (Dz1TdqcOrderEntryPresent *)Dz1Calloc(sizeof(Dz1TdqcOrderEntryPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TdqcOrderEntryPresent_dump(Dz1TdqcOrderEntryPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TdqcOrderEntryPresentStr(*v));
}
// Dz1TdqcOrderEntryPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcOrderEntry
Dz1TdqcOrderEntry *Dz1TdqcOrderEntry_new(Dz1TdqcOrderEntryPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcOrderEntry *ret = (Dz1TdqcOrderEntry *)Dz1Calloc(sizeof(Dz1TdqcOrderEntry), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqcOrderEntry_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TdqcOrderEntryPresent_shp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.shp = (Dz1TdqcShape *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqcOrderEntryPresent_tbl:
			// _U_cst_clone
			if (ptr != NULL) ret->x.tbl = (Dz1TdqcTblInstance *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqcOrderEntryPresent_qry:
			// _U_cst_clone
			if (ptr != NULL) ret->x.qry = (Dz1TdqcQuery *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqcOrderEntryPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcOrderEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqcOrderEntry_copy(Dz1TdqcOrderEntry *ret, Dz1TdqcOrderEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TdqcOrderEntryPresent_shp:
			// _U_cst_clone
			ret->x.shp = src->x.shp;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqcOrderEntryPresent_tbl:
			// _U_cst_clone
			ret->x.tbl = src->x.tbl;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqcOrderEntryPresent_qry:
			// _U_cst_clone
			ret->x.qry = src->x.qry;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqcOrderEntry *Dz1TdqcOrderEntry_clone(Dz1TdqcOrderEntry *src, Dz1Error *err)
{
	Dz1TdqcOrderEntry *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TdqcOrderEntry *)Dz1Calloc(sizeof(Dz1TdqcOrderEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqcOrderEntry_delAndSetNull, (void *)&ret);
		if (Dz1TdqcOrderEntry_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcOrderEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqcOrderEntry_purge(Dz1TdqcOrderEntry *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TdqcOrderEntryPresent_shp:
		break;
	case Dz1TdqcOrderEntryPresent_tbl:
		break;
	case Dz1TdqcOrderEntryPresent_qry:
		break;
	default:
		break;
	}
}

void Dz1TdqcOrderEntry_del(Dz1TdqcOrderEntry *p)
{
	if (!p) return;
	Dz1TdqcOrderEntry_purge(p);
	Dz1Free(p);
}

void Dz1TdqcOrderEntry_dump(Dz1TdqcOrderEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TdqcOrderEntryPresent_shp:
		Dz1Thread_printf(Dz1T("shp = ")); Dz1TdqcShape_dump(p->x.shp, tab); 
		break;
	case Dz1TdqcOrderEntryPresent_tbl:
		Dz1Thread_printf(Dz1T("tbl = ")); Dz1TdqcTblInstance_dump(p->x.tbl, tab); 
		break;
	case Dz1TdqcOrderEntryPresent_qry:
		Dz1Thread_printf(Dz1T("qry = ")); Dz1TdqcQuery_dump(p->x.qry, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TdqcOrderEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcOrderList
static Dz1Error Dz1TdqcOrderList_add(Dz1TdqcOrderList *p, Dz1TdqcOrderEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqcOrderListMkArrArg
{
	Dz1TdqcOrderEntry **arr;
	unsigned int idx;
} Dz1TdqcOrderListMkArrArg;

static Dz1Error _Dz1TdqcOrderList_get_array(void *ptr, Dz1TdqcOrderEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcOrderListMkArrArg *arg = (Dz1TdqcOrderListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqcOrderEntry **Dz1TdqcOrderList_get_array(Dz1TdqcOrderList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqcOrderEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqcOrderEntry **)Dz1Calloc(sizeof(Dz1TdqcOrderEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqcOrderListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqcOrderList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqcOrderList_travelForward(Dz1TdqcOrderList *p, Dz1Error (*func)(void *ptr, Dz1TdqcOrderEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqcOrderList_travelBackward(Dz1TdqcOrderList *p, Dz1Error (*func)(void *ptr, Dz1TdqcOrderEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqcOrderList_count(Dz1TdqcOrderList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqcOrderList *Dz1TdqcOrderList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcOrderList *ret = (Dz1TdqcOrderList *)Dz1Calloc(sizeof(Dz1TdqcOrderList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcOrderList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1TdqcOrderEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqcOrderList_count;
			ret->travel = Dz1TdqcOrderList_travelForward;
			ret->travelForward = Dz1TdqcOrderList_travelForward;
			ret->travelBackward = Dz1TdqcOrderList_travelBackward;
			ret->get_array = Dz1TdqcOrderList_get_array;
			ret->add = Dz1TdqcOrderList_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcOrderList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqcOrderList_clone(void *ptr, Dz1TdqcOrderEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqcOrderList *p = (Dz1TdqcOrderList *)ptr;
	Dz1TdqcOrderEntry *cloned = Dz1TdqcOrderEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqcOrderList *Dz1TdqcOrderList_clone(Dz1TdqcOrderList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcOrderList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqcOrderList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcOrderList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqcOrderList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcOrderList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqcOrderList_purge(Dz1TdqcOrderList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqcOrderList_del(Dz1TdqcOrderList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqcOrderList_dump(void *ptr, Dz1TdqcOrderEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqcOrderEntry_dump(p, tab);
	return err;
}

void Dz1TdqcOrderList_dump(Dz1TdqcOrderList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqcOrderList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqcOrderList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MdefcModuleList
static Dz1Error Dz1MdefcModuleList_add(Dz1MdefcModuleList *p, Dz1MdefcModule *data)
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

static bool_t Dz1MdefcModuleList_remove(Dz1MdefcModuleList *p, Dz1MdefcModule *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MdefcModule *Dz1MdefcModuleList_extract(Dz1MdefcModuleList *p, Dz1MdefcModule *key)
{
	return (Dz1MdefcModule *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MdefcModuleListMkArrArg
{
	Dz1MdefcModule **arr;
	unsigned int idx;
} Dz1MdefcModuleListMkArrArg;

static Dz1Error _Dz1MdefcModuleList_get_array(void *ptr, Dz1MdefcModule *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcModuleListMkArrArg *arg = (Dz1MdefcModuleListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MdefcModule **Dz1MdefcModuleList_get_array(Dz1MdefcModuleList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MdefcModule **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MdefcModule **)Dz1Calloc(sizeof(Dz1MdefcModule *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MdefcModuleListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MdefcModuleList_get_array, (void *)&arg);
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

static Dz1Error Dz1MdefcModuleList_travelForward(Dz1MdefcModuleList *p, Dz1Error (*func)(void *ptr, Dz1MdefcModule *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MdefcModuleList_travelBackward(Dz1MdefcModuleList *p, Dz1Error (*func)(void *ptr, Dz1MdefcModule *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MdefcModule *Dz1MdefcModuleList_find(Dz1MdefcModuleList *p, Dz1MdefcModule *key)
{
	return (Dz1MdefcModule *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MdefcModuleList_count(Dz1MdefcModuleList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MdefcModuleList *Dz1MdefcModuleList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MdefcModuleList *ret = (Dz1MdefcModuleList *)Dz1Calloc(sizeof(Dz1MdefcModuleList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MdefcModuleList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MdefcModule_cmp,
				(Dz1DelFunc)Dz1MdefcModule_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MdefcModuleList_count;
			ret->travel = Dz1MdefcModuleList_travelForward;
			ret->travelForward = Dz1MdefcModuleList_travelForward;
			ret->travelBackward = Dz1MdefcModuleList_travelBackward;
			ret->get_array = Dz1MdefcModuleList_get_array;
			ret->add = Dz1MdefcModuleList_add;
			ret->remove = Dz1MdefcModuleList_remove;
			ret->find = Dz1MdefcModuleList_find;
			ret->extract = Dz1MdefcModuleList_extract;
			ret->cmp = Dz1MdefcModule_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MdefcModuleList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MdefcModuleList_purge(Dz1MdefcModuleList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MdefcModuleList_del(Dz1MdefcModuleList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MdefcModuleList_dump(void *ptr, Dz1MdefcModule *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MdefcModule_dump(p, tab);
	return err;
}

void Dz1MdefcModuleList_dump(Dz1MdefcModuleList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MdefcModuleList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MdefcModuleList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcArg
Dz1TdqcArg *Dz1TdqcArg_new(Dz1Str mod_inc_path, 
						   Dz1Str dst_path_c, 
						   Dz1Str dst_path_h, 
						   Dz1Str fn_postfix, 
						   bool_t output_src, 
						   bool_t output_hdr, 
						   Dz1Str target_file, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcArg *__internal_ret = (Dz1TdqcArg *)Dz1Calloc(sizeof(Dz1TdqcArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqcArg_delAndSetNull, (void *)&__internal_ret);
		
		if (mod_inc_path && (__internal_ret->mod_inc_path = Dz1Str_clone(mod_inc_path, errp)) == NULL) ERR_OUT(errp);
		else if (dst_path_c && (__internal_ret->dst_path_c = Dz1Str_clone(dst_path_c, errp)) == NULL) ERR_OUT(errp);
		else if (dst_path_h && (__internal_ret->dst_path_h = Dz1Str_clone(dst_path_h, errp)) == NULL) ERR_OUT(errp);
		else if (fn_postfix && (__internal_ret->fn_postfix = Dz1Str_clone(fn_postfix, errp)) == NULL) ERR_OUT(errp);
		else if (target_file && (__internal_ret->target_file = Dz1Str_clone(target_file, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->output_src = output_src;
			__internal_ret->output_hdr = output_hdr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TdqcArg_purge(Dz1TdqcArg *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->mod_inc_path);
	Dz1Str_del(p->dst_path_c);
	Dz1Str_del(p->dst_path_h);
	Dz1Str_del(p->fn_postfix);
	Dz1Str_del(p->target_file);
}

void Dz1TdqcArg_del(Dz1TdqcArg *p)
{
	if (p == NULL) return;
	Dz1TdqcArg_purge(p);
	Dz1Free(p);
}

// Dz1TdqcArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqcTarget
Dz1TdqcTarget *Dz1TdqcTarget_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqcTarget *__internal_ret = (Dz1TdqcTarget *)Dz1Calloc(sizeof(Dz1TdqcTarget), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqcTarget_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->src = Dz1MdefcModuleList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->incs = Dz1TdqNameList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->shapes = Dz1TdqcShapeList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->tables = Dz1TdqcTblInstanceList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->tblseq = Dz1TdqcTblInstanceSeq_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->queries = Dz1TdqcQueryList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->ord = Dz1TdqcOrderList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqcTarget_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TdqcTarget_purge(Dz1TdqcTarget *p)
{
	if (p == NULL) return;
	Dz1MdefcModuleList_del(p->src);
	Dz1TdqNameList_del(p->incs);
	Dz1TdqcShapeList_del(p->shapes);
	Dz1TdqcTblInstanceList_del(p->tables);
	Dz1TdqcTblInstanceSeq_del(p->tblseq);
	Dz1TdqcQueryList_del(p->queries);
	Dz1TdqcOrderList_del(p->ord);
}

void Dz1TdqcTarget_del(Dz1TdqcTarget *p)
{
	if (p == NULL) return;
	Dz1TdqcTarget_purge(p);
	Dz1Free(p);
}

void Dz1TdqcTarget_dump(Dz1TdqcTarget *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("incs = ")); Dz1TdqNameList_dump(p->incs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("shapes = ")); Dz1TdqcShapeList_dump(p->shapes, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tblseq = ")); Dz1TdqcTblInstanceSeq_dump(p->tblseq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("queries = ")); Dz1TdqcQueryList_dump(p->queries, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ord = ")); Dz1TdqcOrderList_dump(p->ord, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqcTarget
////////////////////////////////////////////////////////////////////////////////

