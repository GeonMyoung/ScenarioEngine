////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_qry_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryTblCol
Dz1TdqQryTblCol *Dz1TdqQryTblCol_new(Dz1TdqQueryTblName *tbl/*_ref*/, 
									 Dz1Str col_name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryTblCol *__internal_ret = (Dz1TdqQryTblCol *)Dz1Calloc(sizeof(Dz1TdqQryTblCol), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqQryTblCol_delAndSetNull, (void *)&__internal_ret);
		
		if (col_name && (__internal_ret->col_name = Dz1Str_clone(col_name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tbl = tbl;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryTblCol_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqQryTblCol_copy(Dz1TdqQryTblCol *dst, Dz1TdqQryTblCol *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->col_name && (dst->col_name = Dz1Str_clone(src->col_name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->tbl = src->tbl;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqQryTblCol *Dz1TdqQryTblCol_clone(Dz1TdqQryTblCol *src, Dz1Error *err)
{
	Dz1TdqQryTblCol *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqQryTblCol *)Dz1Calloc(sizeof(Dz1TdqQryTblCol), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqQryTblCol_delAndSetNull, (void *)&dst);
		if (Dz1TdqQryTblCol_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryTblCol_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqQryTblCol_purge(Dz1TdqQryTblCol *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->col_name);
}

void Dz1TdqQryTblCol_del(Dz1TdqQryTblCol *p)
{
	if (p == NULL) return;
	Dz1TdqQryTblCol_purge(p);
	Dz1Free(p);
}

void Dz1TdqQryTblCol_dump(Dz1TdqQryTblCol *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("tbl = ")); Dz1TdqQueryTblName_dump(p->tbl, tab); 
		Dz1Thread_tprintf(tab, Dz1T("col_name = ")); Dz1Str_dump(p->col_name, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqQryTblCol
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryExprCol
Dz1TdqQryExprCol *Dz1TdqQryExprCol_new(Dz1TdqSqlTypeSpec *type, 
									   Dz1Str expression, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryExprCol *__internal_ret = (Dz1TdqQryExprCol *)Dz1Calloc(sizeof(Dz1TdqQryExprCol), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqQryExprCol_delAndSetNull, (void *)&__internal_ret);
		
		if (expression && (__internal_ret->expression = Dz1Str_clone(expression, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->type = type;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryExprCol_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqQryExprCol_copy(Dz1TdqQryExprCol *dst, Dz1TdqQryExprCol *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->type && (dst->type = Dz1TdqSqlTypeSpec_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else if (src->expression && (dst->expression = Dz1Str_clone(src->expression, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqQryExprCol *Dz1TdqQryExprCol_clone(Dz1TdqQryExprCol *src, Dz1Error *err)
{
	Dz1TdqQryExprCol *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqQryExprCol *)Dz1Calloc(sizeof(Dz1TdqQryExprCol), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqQryExprCol_delAndSetNull, (void *)&dst);
		if (Dz1TdqQryExprCol_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryExprCol_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqQryExprCol_purge(Dz1TdqQryExprCol *p)
{
	if (p == NULL) return;
	Dz1TdqSqlTypeSpec_del(p->type);
	Dz1Str_del(p->expression);
}

void Dz1TdqQryExprCol_del(Dz1TdqQryExprCol *p)
{
	if (p == NULL) return;
	Dz1TdqQryExprCol_purge(p);
	Dz1Free(p);
}

void Dz1TdqQryExprCol_dump(Dz1TdqQryExprCol *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("type.")); Dz1TdqSqlTypeSpec_dump(p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("expression = ")); Dz1Str_dump(p->expression, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqQryExprCol
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryColPresent
static struct Dz1TdqQryColPresentMapA
{
	str_t str;
	Dz1TdqQryColPresent v;
} Dz1TdqQryColPresentMapA[] =
{
	{ (char *)"tcol", Dz1TdqQryColPresent_tcol },
	{ (char *)"ecol", Dz1TdqQryColPresent_ecol },
	{ NULL, Dz1TdqQryColPresent_max }
};

str_t Dz1TdqQryColPresentStrA(Dz1TdqQryColPresent v)
{
	struct Dz1TdqQryColPresentMapA *i = NULL;
	for (i = Dz1TdqQryColPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqQryColPresent Dz1TdqQryColPresentFromStrA(str_t str)
{
	struct Dz1TdqQryColPresentMapA *i = NULL;
	for (i = Dz1TdqQryColPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqQryColPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqQryColPresentMapW
{
	wstr_t str;
	Dz1TdqQryColPresent v;
} Dz1TdqQryColPresentMapW[] =
{
	{ (wchar_t *)L"tcol", Dz1TdqQryColPresent_tcol },
	{ (wchar_t *)L"ecol", Dz1TdqQryColPresent_ecol },
	{ NULL, Dz1TdqQryColPresent_max }
};

wstr_t Dz1TdqQryColPresentStrW(Dz1TdqQryColPresent v)
{
	struct Dz1TdqQryColPresentMapW *i = NULL;
	for (i = Dz1TdqQryColPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqQryColPresent Dz1TdqQryColPresentFromStrW(wstr_t str)
{
	struct Dz1TdqQryColPresentMapW *i = NULL;
	for (i = Dz1TdqQryColPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqQryColPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TdqQryColPresent *Dz1TdqQryColPresent_new(Dz1TdqQryColPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryColPresent *__internal_ret = (Dz1TdqQryColPresent *)Dz1Calloc(sizeof(Dz1TdqQryColPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TdqQryColPresent_dump(Dz1TdqQryColPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TdqQryColPresentStr(*v));
}
// Dz1TdqQryColPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryCol
Dz1TdqQryCol *Dz1TdqQryCol_new(Dz1TdqQryColPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryCol *ret = (Dz1TdqQryCol *)Dz1Calloc(sizeof(Dz1TdqQryCol), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqQryCol_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TdqQryColPresent_tcol:
			// _U_cst_clone
			if (ptr != NULL) ret->x.tcol = (Dz1TdqQryTblCol *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqQryColPresent_ecol:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ecol = (Dz1TdqQryExprCol *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqQryColPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryCol_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqQryCol_copy(Dz1TdqQryCol *ret, Dz1TdqQryCol *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TdqQryColPresent_tcol:
			// _U_cst_clone
			if (src->x.tcol && (ret->x.tcol = Dz1TdqQryTblCol_clone(src->x.tcol, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqQryColPresent_ecol:
			// _U_cst_clone
			if (src->x.ecol && (ret->x.ecol = Dz1TdqQryExprCol_clone(src->x.ecol, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqQryCol *Dz1TdqQryCol_clone(Dz1TdqQryCol *src, Dz1Error *err)
{
	Dz1TdqQryCol *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TdqQryCol *)Dz1Calloc(sizeof(Dz1TdqQryCol), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqQryCol_delAndSetNull, (void *)&ret);
		if (Dz1TdqQryCol_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryCol_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqQryCol_purge(Dz1TdqQryCol *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TdqQryColPresent_tcol:
		Dz1TdqQryTblCol_del(p->x.tcol);
		break;
	case Dz1TdqQryColPresent_ecol:
		Dz1TdqQryExprCol_del(p->x.ecol);
		break;
	default:
		break;
	}
}

void Dz1TdqQryCol_del(Dz1TdqQryCol *p)
{
	if (!p) return;
	Dz1TdqQryCol_purge(p);
	Dz1Free(p);
}

void Dz1TdqQryCol_dump(Dz1TdqQryCol *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TdqQryColPresent_tcol:
		Dz1Thread_printf(Dz1T("tcol = ")); Dz1TdqQryTblCol_dump(p->x.tcol, tab); 
		break;
	case Dz1TdqQryColPresent_ecol:
		Dz1Thread_printf(Dz1T("ecol = ")); Dz1TdqQryExprCol_dump(p->x.ecol, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TdqQryCol
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryColumn
Dz1TdqQryColumn *Dz1TdqQryColumn_new(u32_t order, 
									 Dz1TdqQryCol *src, 
									 Dz1Str alias, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryColumn *__internal_ret = (Dz1TdqQryColumn *)Dz1Calloc(sizeof(Dz1TdqQryColumn), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqQryColumn_delAndSetNull, (void *)&__internal_ret);
		
		if (alias && (__internal_ret->alias = Dz1Str_clone(alias, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->order = order;
			__internal_ret->src = src;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryColumn_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqQryColumn_copy(Dz1TdqQryColumn *dst, Dz1TdqQryColumn *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->src && (dst->src = Dz1TdqQryCol_clone(src->src, errp)) == NULL) ERR_OUT(errp);
	else if (src->alias && (dst->alias = Dz1Str_clone(src->alias, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->order = src->order;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqQryColumn *Dz1TdqQryColumn_clone(Dz1TdqQryColumn *src, Dz1Error *err)
{
	Dz1TdqQryColumn *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqQryColumn *)Dz1Calloc(sizeof(Dz1TdqQryColumn), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqQryColumn_delAndSetNull, (void *)&dst);
		if (Dz1TdqQryColumn_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryColumn_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqQryColumn_purge(Dz1TdqQryColumn *p)
{
	if (p == NULL) return;
	Dz1TdqQryCol_del(p->src);
	Dz1Str_del(p->alias);
}

void Dz1TdqQryColumn_del(Dz1TdqQryColumn *p)
{
	if (p == NULL) return;
	Dz1TdqQryColumn_purge(p);
	Dz1Free(p);
}

int Dz1TdqQryColumn_cmp(Dz1TdqQryColumn *a, Dz1TdqQryColumn *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->order, &b->order)) != 0) { }
	return ret;
}
// Dz1TdqQryColumn
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryRow
static Dz1Error Dz1TdqQryRow_add(Dz1TdqQryRow *p, Dz1TdqQryColumn *data)
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

static bool_t Dz1TdqQryRow_remove(Dz1TdqQryRow *p, Dz1TdqQryColumn *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqQryColumn *Dz1TdqQryRow_extract(Dz1TdqQryRow *p, Dz1TdqQryColumn *key)
{
	return (Dz1TdqQryColumn *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqQryRowMkArrArg
{
	Dz1TdqQryColumn **arr;
	unsigned int idx;
} Dz1TdqQryRowMkArrArg;

static Dz1Error _Dz1TdqQryRow_get_array(void *ptr, Dz1TdqQryColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqQryRowMkArrArg *arg = (Dz1TdqQryRowMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqQryColumn **Dz1TdqQryRow_get_array(Dz1TdqQryRow *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqQryColumn **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqQryColumn **)Dz1Calloc(sizeof(Dz1TdqQryColumn *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQryRowMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqQryRow_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqQryRow_travelForward(Dz1TdqQryRow *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqQryRow_travelBackward(Dz1TdqQryRow *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqQryColumn *Dz1TdqQryRow_find(Dz1TdqQryRow *p, Dz1TdqQryColumn *key)
{
	return (Dz1TdqQryColumn *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqQryRow_count(Dz1TdqQryRow *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqQryRow *Dz1TdqQryRow_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryRow *ret = (Dz1TdqQryRow *)Dz1Calloc(sizeof(Dz1TdqQryRow), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQryRow_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqQryColumn_cmp,
				(Dz1DelFunc)Dz1TdqQryColumn_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqQryRow_count;
			ret->travel = Dz1TdqQryRow_travelForward;
			ret->travelForward = Dz1TdqQryRow_travelForward;
			ret->travelBackward = Dz1TdqQryRow_travelBackward;
			ret->get_array = Dz1TdqQryRow_get_array;
			ret->add = Dz1TdqQryRow_add;
			ret->remove = Dz1TdqQryRow_remove;
			ret->find = Dz1TdqQryRow_find;
			ret->extract = Dz1TdqQryRow_extract;
			ret->cmp = Dz1TdqQryColumn_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryRow_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqQryRow_clone(void *ptr, Dz1TdqQryColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqQryRow *p = (Dz1TdqQryRow *)ptr;
	Dz1TdqQryColumn *cloned = Dz1TdqQryColumn_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqQryRow *Dz1TdqQryRow_clone(Dz1TdqQryRow *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryRow *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqQryRow_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQryRow_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqQryRow_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryRow_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqQryRow_purge(Dz1TdqQryRow *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqQryRow_del(Dz1TdqQryRow *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqQryRow_dump(void *ptr, Dz1TdqQryColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqQryColumn_dump(p, tab);
	return err;
}

void Dz1TdqQryRow_dump(Dz1TdqQryRow *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqQryRow_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqQryRow
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryRefCols
static Dz1Error Dz1TdqQryRefCols_add(Dz1TdqQryRefCols *p, Dz1TdqQryColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqQryRefColsMkArrArg
{
	Dz1TdqQryColumn **arr;
	unsigned int idx;
} Dz1TdqQryRefColsMkArrArg;

static Dz1Error _Dz1TdqQryRefCols_get_array(void *ptr, Dz1TdqQryColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqQryRefColsMkArrArg *arg = (Dz1TdqQryRefColsMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqQryColumn **Dz1TdqQryRefCols_get_array(Dz1TdqQryRefCols *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqQryColumn **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqQryColumn **)Dz1Calloc(sizeof(Dz1TdqQryColumn *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQryRefColsMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqQryRefCols_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqQryRefCols_travelForward(Dz1TdqQryRefCols *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqQryRefCols_travelBackward(Dz1TdqQryRefCols *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqQryRefCols_count(Dz1TdqQryRefCols *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqQryRefCols *Dz1TdqQryRefCols_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryRefCols *ret = (Dz1TdqQryRefCols *)Dz1Calloc(sizeof(Dz1TdqQryRefCols), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQryRefCols_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqQryRefCols_count;
			ret->travel = Dz1TdqQryRefCols_travelForward;
			ret->travelForward = Dz1TdqQryRefCols_travelForward;
			ret->travelBackward = Dz1TdqQryRefCols_travelBackward;
			ret->get_array = Dz1TdqQryRefCols_get_array;
			ret->add = Dz1TdqQryRefCols_add;
			ret->cmp = Dz1TdqQryColumn_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryRefCols_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqQryRefCols_clone(void *ptr, Dz1TdqQryColumn *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqQryRefCols *p = (Dz1TdqQryRefCols *)ptr;
	Dz1TdqQryColumn *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqQryRefCols *Dz1TdqQryRefCols_clone(Dz1TdqQryRefCols *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQryRefCols *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqQryRefCols_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQryRefCols_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqQryRefCols_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQryRefCols_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqQryRefCols_purge(Dz1TdqQryRefCols *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqQryRefCols_del(Dz1TdqQryRefCols *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqQryRefCols_dump(void *ptr, Dz1TdqQryColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqQryColumn_dump(p, tab);
	return err;
}

void Dz1TdqQryRefCols_dump(Dz1TdqQryRefCols *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqQryRefCols_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqQryRefCols
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblJoin
static struct Dz1TdqQueryTblJoinMapA
{
	str_t str;
	Dz1TdqQueryTblJoin v;
} Dz1TdqQueryTblJoinMapA[] =
{
	{ (char *)"inner", Dz1TdqQueryTblJoin_inner },
	{ (char *)"left", Dz1TdqQueryTblJoin_left },
	{ (char *)"right", Dz1TdqQueryTblJoin_right },
	{ (char *)"outer", Dz1TdqQueryTblJoin_outer },
	{ NULL, Dz1TdqQueryTblJoin_max }
};

str_t Dz1TdqQueryTblJoinStrA(Dz1TdqQueryTblJoin v)
{
	struct Dz1TdqQueryTblJoinMapA *i = NULL;
	for (i = Dz1TdqQueryTblJoinMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqQueryTblJoin Dz1TdqQueryTblJoinFromStrA(str_t str)
{
	struct Dz1TdqQueryTblJoinMapA *i = NULL;
	for (i = Dz1TdqQueryTblJoinMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqQueryTblJoin_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqQueryTblJoinMapW
{
	wstr_t str;
	Dz1TdqQueryTblJoin v;
} Dz1TdqQueryTblJoinMapW[] =
{
	{ (wchar_t *)L"inner", Dz1TdqQueryTblJoin_inner },
	{ (wchar_t *)L"left", Dz1TdqQueryTblJoin_left },
	{ (wchar_t *)L"right", Dz1TdqQueryTblJoin_right },
	{ (wchar_t *)L"outer", Dz1TdqQueryTblJoin_outer },
	{ NULL, Dz1TdqQueryTblJoin_max }
};

wstr_t Dz1TdqQueryTblJoinStrW(Dz1TdqQueryTblJoin v)
{
	struct Dz1TdqQueryTblJoinMapW *i = NULL;
	for (i = Dz1TdqQueryTblJoinMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqQueryTblJoin Dz1TdqQueryTblJoinFromStrW(wstr_t str)
{
	struct Dz1TdqQueryTblJoinMapW *i = NULL;
	for (i = Dz1TdqQueryTblJoinMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqQueryTblJoin_max;
}
#endif // UNIX_SYSTEM

Dz1TdqQueryTblJoin *Dz1TdqQueryTblJoin_new(Dz1TdqQueryTblJoin *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQueryTblJoin *__internal_ret = (Dz1TdqQueryTblJoin *)Dz1Calloc(sizeof(Dz1TdqQueryTblJoin), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1TdqQueryTblJoin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblName
Dz1TdqQueryTblName *Dz1TdqQueryTblName_new(Dz1TdqTblInstance *instance/*_ref*/, 
										   Dz1Str alias, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQueryTblName *__internal_ret = (Dz1TdqQueryTblName *)Dz1Calloc(sizeof(Dz1TdqQueryTblName), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblName_delAndSetNull, (void *)&__internal_ret);
		
		if (alias && (__internal_ret->alias = Dz1Str_clone(alias, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->instance = instance;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryTblName_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqQueryTblName_copy(Dz1TdqQueryTblName *dst, Dz1TdqQueryTblName *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->alias && (dst->alias = Dz1Str_clone(src->alias, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->instance = src->instance;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqQueryTblName *Dz1TdqQueryTblName_clone(Dz1TdqQueryTblName *src, Dz1Error *err)
{
	Dz1TdqQueryTblName *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqQueryTblName *)Dz1Calloc(sizeof(Dz1TdqQueryTblName), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblName_delAndSetNull, (void *)&dst);
		if (Dz1TdqQueryTblName_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryTblName_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqQueryTblName_purge(Dz1TdqQueryTblName *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->alias);
}

void Dz1TdqQueryTblName_del(Dz1TdqQueryTblName *p)
{
	if (p == NULL) return;
	Dz1TdqQueryTblName_purge(p);
	Dz1Free(p);
}

// Dz1TdqQueryTblName
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblEntry
Dz1TdqQueryTblEntry *Dz1TdqQueryTblEntry_new(Dz1TdqQueryTblName *tbl, 
											 Dz1TdqQueryTblJoin mode, 
											 Dz1Str match_on, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQueryTblEntry *__internal_ret = (Dz1TdqQueryTblEntry *)Dz1Calloc(sizeof(Dz1TdqQueryTblEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (match_on && (__internal_ret->match_on = Dz1Str_clone(match_on, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tbl = tbl;
			__internal_ret->mode = mode;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryTblEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqQueryTblEntry_copy(Dz1TdqQueryTblEntry *dst, Dz1TdqQueryTblEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->tbl && (dst->tbl = Dz1TdqQueryTblName_clone(src->tbl, errp)) == NULL) ERR_OUT(errp);
	else if (src->match_on && (dst->match_on = Dz1Str_clone(src->match_on, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->mode = src->mode;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqQueryTblEntry *Dz1TdqQueryTblEntry_clone(Dz1TdqQueryTblEntry *src, Dz1Error *err)
{
	Dz1TdqQueryTblEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqQueryTblEntry *)Dz1Calloc(sizeof(Dz1TdqQueryTblEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblEntry_delAndSetNull, (void *)&dst);
		if (Dz1TdqQueryTblEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryTblEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqQueryTblEntry_purge(Dz1TdqQueryTblEntry *p)
{
	if (p == NULL) return;
	Dz1TdqQueryTblName_del(p->tbl);
	Dz1Str_del(p->match_on);
}

void Dz1TdqQueryTblEntry_del(Dz1TdqQueryTblEntry *p)
{
	if (p == NULL) return;
	Dz1TdqQueryTblEntry_purge(p);
	Dz1Free(p);
}

// Dz1TdqQueryTblEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblSeq
static Dz1Error Dz1TdqQueryTblSeq_add(Dz1TdqQueryTblSeq *p, Dz1TdqQueryTblEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqQueryTblSeqMkArrArg
{
	Dz1TdqQueryTblEntry **arr;
	unsigned int idx;
} Dz1TdqQueryTblSeqMkArrArg;

static Dz1Error _Dz1TdqQueryTblSeq_get_array(void *ptr, Dz1TdqQueryTblEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqQueryTblSeqMkArrArg *arg = (Dz1TdqQueryTblSeqMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqQueryTblEntry **Dz1TdqQueryTblSeq_get_array(Dz1TdqQueryTblSeq *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqQueryTblEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqQueryTblEntry **)Dz1Calloc(sizeof(Dz1TdqQueryTblEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQueryTblSeqMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqQueryTblSeq_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqQueryTblSeq_travelForward(Dz1TdqQueryTblSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqQueryTblEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqQueryTblSeq_travelBackward(Dz1TdqQueryTblSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqQueryTblEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqQueryTblSeq_count(Dz1TdqQueryTblSeq *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqQueryTblSeq *Dz1TdqQueryTblSeq_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQueryTblSeq *ret = (Dz1TdqQueryTblSeq *)Dz1Calloc(sizeof(Dz1TdqQueryTblSeq), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblSeq_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1TdqQueryTblEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqQueryTblSeq_count;
			ret->travel = Dz1TdqQueryTblSeq_travelForward;
			ret->travelForward = Dz1TdqQueryTblSeq_travelForward;
			ret->travelBackward = Dz1TdqQueryTblSeq_travelBackward;
			ret->get_array = Dz1TdqQueryTblSeq_get_array;
			ret->add = Dz1TdqQueryTblSeq_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryTblSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqQueryTblSeq_clone(void *ptr, Dz1TdqQueryTblEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqQueryTblSeq *p = (Dz1TdqQueryTblSeq *)ptr;
	Dz1TdqQueryTblEntry *cloned = Dz1TdqQueryTblEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqQueryTblSeq *Dz1TdqQueryTblSeq_clone(Dz1TdqQueryTblSeq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQueryTblSeq *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqQueryTblSeq_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblSeq_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqQueryTblSeq_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryTblSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqQueryTblSeq_purge(Dz1TdqQueryTblSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqQueryTblSeq_del(Dz1TdqQueryTblSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqQueryTblSeq_dump(void *ptr, Dz1TdqQueryTblEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqQueryTblEntry_dump(p, tab);
	return err;
}

void Dz1TdqQueryTblSeq_dump(Dz1TdqQueryTblSeq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqQueryTblSeq_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqQueryTblSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblSpec
Dz1TdqQueryTblSpec *Dz1TdqQueryTblSpec_new(Dz1TdqQueryTblName *basis, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQueryTblSpec *__internal_ret = (Dz1TdqQueryTblSpec *)Dz1Calloc(sizeof(Dz1TdqQueryTblSpec), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblSpec_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->join_tbls = Dz1TdqQueryTblSeq_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->basis = basis;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryTblSpec_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqQueryTblSpec_copy(Dz1TdqQueryTblSpec *dst, Dz1TdqQueryTblSpec *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->basis && (dst->basis = Dz1TdqQueryTblName_clone(src->basis, errp)) == NULL) ERR_OUT(errp);
	else if (src->join_tbls && (dst->join_tbls = Dz1TdqQueryTblSeq_clone(src->join_tbls, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqQueryTblSpec *Dz1TdqQueryTblSpec_clone(Dz1TdqQueryTblSpec *src, Dz1Error *err)
{
	Dz1TdqQueryTblSpec *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqQueryTblSpec *)Dz1Calloc(sizeof(Dz1TdqQueryTblSpec), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblSpec_delAndSetNull, (void *)&dst);
		if (Dz1TdqQueryTblSpec_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryTblSpec_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqQueryTblSpec_purge(Dz1TdqQueryTblSpec *p)
{
	if (p == NULL) return;
	Dz1TdqQueryTblName_del(p->basis);
	Dz1TdqQueryTblSeq_del(p->join_tbls);
}

void Dz1TdqQueryTblSpec_del(Dz1TdqQueryTblSpec *p)
{
	if (p == NULL) return;
	Dz1TdqQueryTblSpec_purge(p);
	Dz1Free(p);
}

void Dz1TdqQueryTblSpec_dump(Dz1TdqQueryTblSpec *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("basis = ")); Dz1TdqQueryTblName_dump(p->basis, tab); 
		Dz1Thread_tprintf(tab, Dz1T("join_tbls = ")); Dz1TdqQueryTblSeq_dump(p->join_tbls, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqQueryTblSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQuery
Dz1TdqQuery *Dz1TdqQuery_new(Dz1Str name, 
							 Dz1TdqQryRow *sel, 
							 Dz1TdqQueryTblSpec *from, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQuery *__internal_ret = (Dz1TdqQuery *)Dz1Calloc(sizeof(Dz1TdqQuery), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqQuery_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->groupby = Dz1TdqQryRefCols_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->sel = sel;
			__internal_ret->from = from;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQuery_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqQuery_copy(Dz1TdqQuery *dst, Dz1TdqQuery *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->sel && (dst->sel = Dz1TdqQryRow_clone(src->sel, errp)) == NULL) ERR_OUT(errp);
	else if (src->from && (dst->from = Dz1TdqQueryTblSpec_clone(src->from, errp)) == NULL) ERR_OUT(errp);
	else if (src->groupby && (dst->groupby = Dz1TdqQryRefCols_clone(src->groupby, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqQuery *Dz1TdqQuery_clone(Dz1TdqQuery *src, Dz1Error *err)
{
	Dz1TdqQuery *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqQuery *)Dz1Calloc(sizeof(Dz1TdqQuery), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqQuery_delAndSetNull, (void *)&dst);
		if (Dz1TdqQuery_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQuery_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqQuery_purge(Dz1TdqQuery *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1TdqQryRow_del(p->sel);
	Dz1TdqQueryTblSpec_del(p->from);
	Dz1TdqQryRefCols_del(p->groupby);
}

void Dz1TdqQuery_del(Dz1TdqQuery *p)
{
	if (p == NULL) return;
	Dz1TdqQuery_purge(p);
	Dz1Free(p);
}

void Dz1TdqQuery_dump(Dz1TdqQuery *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sel = ")); Dz1TdqQryRow_dump(p->sel, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("from = ")); Dz1TdqQueryTblSpec_dump(p->from, tab); 
		Dz1Thread_tprintf(tab, Dz1T("groupby = ")); Dz1TdqQryRefCols_dump(p->groupby, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TdqQuery_cmp(Dz1TdqQuery *a, Dz1TdqQuery *b)
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
// Dz1TdqQuery
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryList
static Dz1Error Dz1TdqQueryList_add(Dz1TdqQueryList *p, Dz1TdqQuery *data)
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

static bool_t Dz1TdqQueryList_remove(Dz1TdqQueryList *p, Dz1TdqQuery *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqQuery *Dz1TdqQueryList_extract(Dz1TdqQueryList *p, Dz1TdqQuery *key)
{
	return (Dz1TdqQuery *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqQueryListMkArrArg
{
	Dz1TdqQuery **arr;
	unsigned int idx;
} Dz1TdqQueryListMkArrArg;

static Dz1Error _Dz1TdqQueryList_get_array(void *ptr, Dz1TdqQuery *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqQueryListMkArrArg *arg = (Dz1TdqQueryListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqQuery **Dz1TdqQueryList_get_array(Dz1TdqQueryList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqQuery **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqQuery **)Dz1Calloc(sizeof(Dz1TdqQuery *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQueryListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqQueryList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqQueryList_travelForward(Dz1TdqQueryList *p, Dz1Error (*func)(void *ptr, Dz1TdqQuery *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqQueryList_travelBackward(Dz1TdqQueryList *p, Dz1Error (*func)(void *ptr, Dz1TdqQuery *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqQuery *Dz1TdqQueryList_find(Dz1TdqQueryList *p, Dz1TdqQuery *key)
{
	return (Dz1TdqQuery *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqQueryList_count(Dz1TdqQueryList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqQueryList *Dz1TdqQueryList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQueryList *ret = (Dz1TdqQueryList *)Dz1Calloc(sizeof(Dz1TdqQueryList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQueryList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqQuery_cmp,
				(Dz1DelFunc)Dz1TdqQuery_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqQueryList_count;
			ret->travel = Dz1TdqQueryList_travelForward;
			ret->travelForward = Dz1TdqQueryList_travelForward;
			ret->travelBackward = Dz1TdqQueryList_travelBackward;
			ret->get_array = Dz1TdqQueryList_get_array;
			ret->add = Dz1TdqQueryList_add;
			ret->remove = Dz1TdqQueryList_remove;
			ret->find = Dz1TdqQueryList_find;
			ret->extract = Dz1TdqQueryList_extract;
			ret->cmp = Dz1TdqQuery_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqQueryList_clone(void *ptr, Dz1TdqQuery *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqQueryList *p = (Dz1TdqQueryList *)ptr;
	Dz1TdqQuery *cloned = Dz1TdqQuery_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqQueryList *Dz1TdqQueryList_clone(Dz1TdqQueryList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqQueryList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqQueryList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQueryList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqQueryList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqQueryList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqQueryList_purge(Dz1TdqQueryList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqQueryList_del(Dz1TdqQueryList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqQueryList_dump(void *ptr, Dz1TdqQuery *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqQuery_dump(p, tab);
	return err;
}

void Dz1TdqQueryList_dump(Dz1TdqQueryList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqQueryList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqQueryList
////////////////////////////////////////////////////////////////////////////////

