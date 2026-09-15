////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1JsonStructDef.h"

////////////////////////////////////////////////////////////////////////////////
// NewLineMap
NewLineMap *NewLineMap_new(Dz1JsonNewLine mode, Dz1Str str, size_t len, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	NewLineMap *__internal_ret = (NewLineMap *)Dz1Calloc(sizeof(NewLineMap), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(NewLineMap_delAndSetNull, (void *)&__internal_ret);
		
		if (str && (__internal_ret->str = Dz1Str_clone(str, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->mode = mode;
			__internal_ret->len = len;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (NewLineMap_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void NewLineMap_purge(NewLineMap *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->str);
}

void NewLineMap_del(NewLineMap *p)
{
	if (p == NULL) return;
	NewLineMap_purge(p);
	Dz1Free(p);
}

// NewLineMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecRefList
static Dz1Error Dz1JsonSpecRefList_add(Dz1JsonSpecRefList *p, Dz1JsonSpecEntry *data)
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

static bool_t Dz1JsonSpecRefList_remove(Dz1JsonSpecRefList *p, Dz1JsonSpecEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1JsonSpecEntry *Dz1JsonSpecRefList_extract(Dz1JsonSpecRefList *p, Dz1JsonSpecEntry *key)
{
	return (Dz1JsonSpecEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1JsonSpecRefListMkArrArg
{
	Dz1JsonSpecEntry **arr;
	unsigned int idx;
} Dz1JsonSpecRefListMkArrArg;

static Dz1Error _Dz1JsonSpecRefList_get_array(void *ptr, Dz1JsonSpecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonSpecRefListMkArrArg *arg = (Dz1JsonSpecRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1JsonSpecEntry **Dz1JsonSpecRefList_get_array(Dz1JsonSpecRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1JsonSpecEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1JsonSpecEntry **)Dz1Calloc(sizeof(Dz1JsonSpecEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonSpecRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1JsonSpecRefList_get_array, (void *)&arg);
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

static Dz1Error Dz1JsonSpecRefList_travelForward(Dz1JsonSpecRefList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1JsonSpecRefList_travelBackward(Dz1JsonSpecRefList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1JsonSpecEntry *Dz1JsonSpecRefList_find(Dz1JsonSpecRefList *p, Dz1JsonSpecEntry *key)
{
	return (Dz1JsonSpecEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1JsonSpecRefList_count(Dz1JsonSpecRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1JsonSpecRefList *Dz1JsonSpecRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecRefList *ret = (Dz1JsonSpecRefList *)Dz1Calloc(sizeof(Dz1JsonSpecRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpecRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1JsonSpecEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1JsonSpecRefList_count;
			ret->travel = Dz1JsonSpecRefList_travelForward;
			ret->travelForward = Dz1JsonSpecRefList_travelForward;
			ret->travelBackward = Dz1JsonSpecRefList_travelBackward;
			ret->get_array = Dz1JsonSpecRefList_get_array;
			ret->add = Dz1JsonSpecRefList_add;
			ret->remove = Dz1JsonSpecRefList_remove;
			ret->find = Dz1JsonSpecRefList_find;
			ret->extract = Dz1JsonSpecRefList_extract;
			ret->cmp = Dz1JsonSpecEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1JsonSpecRefList_clone(void *ptr, Dz1JsonSpecEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonSpecRefList *p = (Dz1JsonSpecRefList *)ptr;
	Dz1JsonSpecEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1JsonSpecRefList *Dz1JsonSpecRefList_clone(Dz1JsonSpecRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1JsonSpecRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpecRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1JsonSpecRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonSpecRefList_purge(Dz1JsonSpecRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1JsonSpecRefList_del(Dz1JsonSpecRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1JsonSpecRefList_dump(void *ptr, Dz1JsonSpecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1JsonSpecEntry_dump(p, tab);
	return err;
}

void Dz1JsonSpecRefList_dump(Dz1JsonSpecRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1JsonSpecRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonSpecRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecUndefinedEntry
Dz1JsonSpecUndefinedEntry *Dz1JsonSpecUndefinedEntry_new(Dz1Str name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecUndefinedEntry *__internal_ret = (Dz1JsonSpecUndefinedEntry *)Dz1Calloc(sizeof(Dz1JsonSpecUndefinedEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecUndefinedEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->refs = Dz1JsonSpecRefList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecUndefinedEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonSpecUndefinedEntry_purge(Dz1JsonSpecUndefinedEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1JsonSpecRefList_del(p->refs);
}

void Dz1JsonSpecUndefinedEntry_del(Dz1JsonSpecUndefinedEntry *p)
{
	if (p == NULL) return;
	Dz1JsonSpecUndefinedEntry_purge(p);
	Dz1Free(p);
}

int Dz1JsonSpecUndefinedEntry_cmp(Dz1JsonSpecUndefinedEntry *a, Dz1JsonSpecUndefinedEntry *b)
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
// Dz1JsonSpecUndefinedEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecUndefinedList
static Dz1Error Dz1JsonSpecUndefinedList_add(Dz1JsonSpecUndefinedList *p, Dz1JsonSpecUndefinedEntry *data)
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

static bool_t Dz1JsonSpecUndefinedList_remove(Dz1JsonSpecUndefinedList *p, Dz1JsonSpecUndefinedEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1JsonSpecUndefinedEntry *Dz1JsonSpecUndefinedList_extract(Dz1JsonSpecUndefinedList *p, Dz1JsonSpecUndefinedEntry *key)
{
	return (Dz1JsonSpecUndefinedEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1JsonSpecUndefinedListMkArrArg
{
	Dz1JsonSpecUndefinedEntry **arr;
	unsigned int idx;
} Dz1JsonSpecUndefinedListMkArrArg;

static Dz1Error _Dz1JsonSpecUndefinedList_get_array(void *ptr, Dz1JsonSpecUndefinedEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonSpecUndefinedListMkArrArg *arg = (Dz1JsonSpecUndefinedListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1JsonSpecUndefinedEntry **Dz1JsonSpecUndefinedList_get_array(Dz1JsonSpecUndefinedList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1JsonSpecUndefinedEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1JsonSpecUndefinedEntry **)Dz1Calloc(sizeof(Dz1JsonSpecUndefinedEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonSpecUndefinedListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1JsonSpecUndefinedList_get_array, (void *)&arg);
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

static Dz1Error Dz1JsonSpecUndefinedList_travelForward(Dz1JsonSpecUndefinedList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecUndefinedEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1JsonSpecUndefinedList_travelBackward(Dz1JsonSpecUndefinedList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecUndefinedEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1JsonSpecUndefinedEntry *Dz1JsonSpecUndefinedList_find(Dz1JsonSpecUndefinedList *p, Dz1JsonSpecUndefinedEntry *key)
{
	return (Dz1JsonSpecUndefinedEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1JsonSpecUndefinedList_count(Dz1JsonSpecUndefinedList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1JsonSpecUndefinedList *Dz1JsonSpecUndefinedList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecUndefinedList *ret = (Dz1JsonSpecUndefinedList *)Dz1Calloc(sizeof(Dz1JsonSpecUndefinedList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpecUndefinedList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1JsonSpecUndefinedEntry_cmp,
				(Dz1DelFunc)Dz1JsonSpecUndefinedEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1JsonSpecUndefinedList_count;
			ret->travel = Dz1JsonSpecUndefinedList_travelForward;
			ret->travelForward = Dz1JsonSpecUndefinedList_travelForward;
			ret->travelBackward = Dz1JsonSpecUndefinedList_travelBackward;
			ret->get_array = Dz1JsonSpecUndefinedList_get_array;
			ret->add = Dz1JsonSpecUndefinedList_add;
			ret->remove = Dz1JsonSpecUndefinedList_remove;
			ret->find = Dz1JsonSpecUndefinedList_find;
			ret->extract = Dz1JsonSpecUndefinedList_extract;
			ret->cmp = Dz1JsonSpecUndefinedEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecUndefinedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonSpecUndefinedList_purge(Dz1JsonSpecUndefinedList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1JsonSpecUndefinedList_del(Dz1JsonSpecUndefinedList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1JsonSpecUndefinedList_dump(void *ptr, Dz1JsonSpecUndefinedEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1JsonSpecUndefinedEntry_dump(p, tab);
	return err;
}

void Dz1JsonSpecUndefinedList_dump(Dz1JsonSpecUndefinedList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1JsonSpecUndefinedList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonSpecUndefinedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonFifoUngetE
Dz1JsonFifoUngetE *Dz1JsonFifoUngetE_new(u32_t c32, 
										 Dz1JsonFifoUngetE *next/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonFifoUngetE *__internal_ret = (Dz1JsonFifoUngetE *)Dz1Calloc(sizeof(Dz1JsonFifoUngetE), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonFifoUngetE_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->c32 = c32;
		__internal_ret->next = next;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonFifoUngetE_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonFifoUngetE_purge(Dz1JsonFifoUngetE *p)
{
	if (p == NULL) return;
}

void Dz1JsonFifoUngetE_del(Dz1JsonFifoUngetE *p)
{
	if (p == NULL) return;
	Dz1JsonFifoUngetE_purge(p);
	Dz1Free(p);
}

// Dz1JsonFifoUngetE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonFifo
Dz1JsonFifo *Dz1JsonFifo_new(str_t ingress_charset, 
							 Dz1JsonConv *conv, 
							 Dz1ElasticBuf *ingress_buf, 
							 Dz1Stream *pop_stream, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonFifo *__internal_ret = (Dz1JsonFifo *)Dz1Calloc(sizeof(Dz1JsonFifo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonFifo_delAndSetNull, (void *)&__internal_ret);
		
		if (ingress_charset && (__internal_ret->ingress_charset = dz1_built_in_str_clone(ingress_charset, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->conv = conv;
			__internal_ret->ingress_buf = ingress_buf;
			__internal_ret->pop_stream = pop_stream;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonFifo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonFifo_purge(Dz1JsonFifo *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->ingress_charset);
	Dz1JsonConv_del(p->conv);
	Dz1ElasticBuf_del(p->ingress_buf);
	Dz1Stream_del(p->pop_stream);
	Dz1JsonFifoUngetE_del(p->ungetc_head);
}

void Dz1JsonFifo_del(Dz1JsonFifo *p)
{
	if (p == NULL) return;
	Dz1JsonFifo_purge(p);
	Dz1Free(p);
}

void Dz1JsonFifo_dump(Dz1JsonFifo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ingress_charset = ")); dz1_built_in_str_dump(p->ingress_charset, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("conv = %p\n"), p->conv);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("ingress_buf = ")); Dz1ElasticBuf_dump(p->ingress_buf, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("pop_stream = ")); Dz1Stream_dump(p->pop_stream, tab); 
		// Normal member
		// Dz1JsonFifoUngetE : api = E0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("ungetc_head = %p\n"), p->ungetc_head);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonFifo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonNumberParse
static struct Dz1JsonNumberParseMapA
{
	str_t str;
	Dz1JsonNumberParse v;
} Dz1JsonNumberParseMapA[] =
{
	{ (char *)"undef", Dz1JsonNumberParse_undef },
	{ (char *)"decimal", Dz1JsonNumberParse_decimal },
	{ (char *)"exponent", Dz1JsonNumberParse_exponent },
	{ (char *)"exp_digit", Dz1JsonNumberParse_exp_digit },
	{ (char *)"hex", Dz1JsonNumberParse_hex },
	{ (char *)"oct", Dz1JsonNumberParse_oct },
	{ (char *)"binary", Dz1JsonNumberParse_binary },
	{ NULL, Dz1JsonNumberParse_max }
};

str_t Dz1JsonNumberParseStrA(Dz1JsonNumberParse v)
{
	struct Dz1JsonNumberParseMapA *i = NULL;
	for (i = Dz1JsonNumberParseMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonNumberParse Dz1JsonNumberParseFromStrA(str_t str)
{
	struct Dz1JsonNumberParseMapA *i = NULL;
	for (i = Dz1JsonNumberParseMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonNumberParse_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonNumberParseMapW
{
	wstr_t str;
	Dz1JsonNumberParse v;
} Dz1JsonNumberParseMapW[] =
{
	{ (wchar_t *)L"undef", Dz1JsonNumberParse_undef },
	{ (wchar_t *)L"decimal", Dz1JsonNumberParse_decimal },
	{ (wchar_t *)L"exponent", Dz1JsonNumberParse_exponent },
	{ (wchar_t *)L"exp_digit", Dz1JsonNumberParse_exp_digit },
	{ (wchar_t *)L"hex", Dz1JsonNumberParse_hex },
	{ (wchar_t *)L"oct", Dz1JsonNumberParse_oct },
	{ (wchar_t *)L"binary", Dz1JsonNumberParse_binary },
	{ NULL, Dz1JsonNumberParse_max }
};

wstr_t Dz1JsonNumberParseStrW(Dz1JsonNumberParse v)
{
	struct Dz1JsonNumberParseMapW *i = NULL;
	for (i = Dz1JsonNumberParseMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonNumberParse Dz1JsonNumberParseFromStrW(wstr_t str)
{
	struct Dz1JsonNumberParseMapW *i = NULL;
	for (i = Dz1JsonNumberParseMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonNumberParse_max;
}
#endif // UNIX_SYSTEM

Dz1JsonNumberParse *Dz1JsonNumberParse_new(Dz1JsonNumberParse *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonNumberParse *__internal_ret = (Dz1JsonNumberParse *)Dz1Calloc(sizeof(Dz1JsonNumberParse), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonNumberParse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonLexerState
static struct Dz1JsonLexerStateMapA
{
	str_t str;
	Dz1JsonLexerState v;
} Dz1JsonLexerStateMapA[] =
{
	{ (char *)"no_lexing", Dz1JsonLexerState_no_lexing },
	{ (char *)"number_lexing", Dz1JsonLexerState_number_lexing },
	{ (char *)"string_lexing", Dz1JsonLexerState_string_lexing },
	{ (char *)"symbol_lexing", Dz1JsonLexerState_symbol_lexing },
	{ NULL, Dz1JsonLexerState_max }
};

str_t Dz1JsonLexerStateStrA(Dz1JsonLexerState v)
{
	struct Dz1JsonLexerStateMapA *i = NULL;
	for (i = Dz1JsonLexerStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonLexerState Dz1JsonLexerStateFromStrA(str_t str)
{
	struct Dz1JsonLexerStateMapA *i = NULL;
	for (i = Dz1JsonLexerStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonLexerState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonLexerStateMapW
{
	wstr_t str;
	Dz1JsonLexerState v;
} Dz1JsonLexerStateMapW[] =
{
	{ (wchar_t *)L"no_lexing", Dz1JsonLexerState_no_lexing },
	{ (wchar_t *)L"number_lexing", Dz1JsonLexerState_number_lexing },
	{ (wchar_t *)L"string_lexing", Dz1JsonLexerState_string_lexing },
	{ (wchar_t *)L"symbol_lexing", Dz1JsonLexerState_symbol_lexing },
	{ NULL, Dz1JsonLexerState_max }
};

wstr_t Dz1JsonLexerStateStrW(Dz1JsonLexerState v)
{
	struct Dz1JsonLexerStateMapW *i = NULL;
	for (i = Dz1JsonLexerStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonLexerState Dz1JsonLexerStateFromStrW(wstr_t str)
{
	struct Dz1JsonLexerStateMapW *i = NULL;
	for (i = Dz1JsonLexerStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonLexerState_max;
}
#endif // UNIX_SYSTEM

Dz1JsonLexerState *Dz1JsonLexerState_new(Dz1JsonLexerState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonLexerState *__internal_ret = (Dz1JsonLexerState *)Dz1Calloc(sizeof(Dz1JsonLexerState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonLexerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonLexer
Dz1JsonLexer *Dz1JsonLexer_new(Dz1ElasticBuf *buf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonLexer *__internal_ret = (Dz1JsonLexer *)Dz1Calloc(sizeof(Dz1JsonLexer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonLexer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->buf = buf;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonLexer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonLexer_purge(Dz1JsonLexer *p)
{
	if (p == NULL) return;
	Dz1ElasticBuf_del(p->buf);
	Dz1JsonToken_del(p->token);
}

void Dz1JsonLexer_del(Dz1JsonLexer *p)
{
	if (p == NULL) return;
	Dz1JsonLexer_purge(p);
	Dz1Free(p);
}

void Dz1JsonLexer_dump(Dz1JsonLexer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), Dz1JsonLexerStateStr(p->state), p->state);
		Dz1Thread_tprintf(tab, Dz1T("flags = ")); Dz1u32_dump(&p->flags, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("buf = ")); Dz1ElasticBuf_dump(p->buf, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("token = ")); Dz1JsonToken_dump(p->token, tab); 
		Dz1Thread_tprintf(tab, Dz1T("temp = ")); Dz1u32_dump(&p->temp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("t_len = ")); Dz1u32_dump(&p->t_len, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dbgs = ")); Dz1u32_dump(&p->dbgs, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonLexer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackPrimitiveState
static struct Dz1JsonStackPrimitiveStateMapA
{
	str_t str;
	Dz1JsonStackPrimitiveState v;
} Dz1JsonStackPrimitiveStateMapA[] =
{
	{ (char *)"init", Dz1JsonStackPrimitiveState_init },
	{ NULL, Dz1JsonStackPrimitiveState_max }
};

str_t Dz1JsonStackPrimitiveStateStrA(Dz1JsonStackPrimitiveState v)
{
	struct Dz1JsonStackPrimitiveStateMapA *i = NULL;
	for (i = Dz1JsonStackPrimitiveStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackPrimitiveState Dz1JsonStackPrimitiveStateFromStrA(str_t str)
{
	struct Dz1JsonStackPrimitiveStateMapA *i = NULL;
	for (i = Dz1JsonStackPrimitiveStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackPrimitiveState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonStackPrimitiveStateMapW
{
	wstr_t str;
	Dz1JsonStackPrimitiveState v;
} Dz1JsonStackPrimitiveStateMapW[] =
{
	{ (wchar_t *)L"init", Dz1JsonStackPrimitiveState_init },
	{ NULL, Dz1JsonStackPrimitiveState_max }
};

wstr_t Dz1JsonStackPrimitiveStateStrW(Dz1JsonStackPrimitiveState v)
{
	struct Dz1JsonStackPrimitiveStateMapW *i = NULL;
	for (i = Dz1JsonStackPrimitiveStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackPrimitiveState Dz1JsonStackPrimitiveStateFromStrW(wstr_t str)
{
	struct Dz1JsonStackPrimitiveStateMapW *i = NULL;
	for (i = Dz1JsonStackPrimitiveStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackPrimitiveState_max;
}
#endif // UNIX_SYSTEM

Dz1JsonStackPrimitiveState *Dz1JsonStackPrimitiveState_new(Dz1JsonStackPrimitiveState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackPrimitiveState *__internal_ret = (Dz1JsonStackPrimitiveState *)Dz1Calloc(sizeof(Dz1JsonStackPrimitiveState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonStackPrimitiveState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackPrimitive
Dz1JsonStackPrimitive *Dz1JsonStackPrimitive_new(Dz1JsonStackPrimitiveState state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackPrimitive *__internal_ret = (Dz1JsonStackPrimitive *)Dz1Calloc(sizeof(Dz1JsonStackPrimitive), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackPrimitive_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->state = state;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackPrimitive_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonStackPrimitive_copy(Dz1JsonStackPrimitive *dst, Dz1JsonStackPrimitive *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->state = src->state;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonStackPrimitive *Dz1JsonStackPrimitive_clone(Dz1JsonStackPrimitive *src, Dz1Error *err)
{
	Dz1JsonStackPrimitive *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonStackPrimitive *)Dz1Calloc(sizeof(Dz1JsonStackPrimitive), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackPrimitive_delAndSetNull, (void *)&dst);
		if (Dz1JsonStackPrimitive_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackPrimitive_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonStackPrimitive_purge(Dz1JsonStackPrimitive *p)
{
	if (p == NULL) return;
}

void Dz1JsonStackPrimitive_del(Dz1JsonStackPrimitive *p)
{
	if (p == NULL) return;
	Dz1JsonStackPrimitive_purge(p);
	Dz1Free(p);
}

void Dz1JsonStackPrimitive_dump(Dz1JsonStackPrimitive *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("state = %s(%d)\n"), Dz1JsonStackPrimitiveStateStr(p->state), p->state);
	}
}
// Dz1JsonStackPrimitive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackStructState
static struct Dz1JsonStackStructStateMapA
{
	str_t str;
	Dz1JsonStackStructState v;
} Dz1JsonStackStructStateMapA[] =
{
	{ (char *)"init", Dz1JsonStackStructState_init },
	{ (char *)"parsing_lstart", Dz1JsonStackStructState_parsing_lstart },
	{ (char *)"parsing_pair", Dz1JsonStackStructState_parsing_pair },
	{ (char *)"parsing_comma", Dz1JsonStackStructState_parsing_comma },
	{ (char *)"parsing_lend", Dz1JsonStackStructState_parsing_lend },
	{ NULL, Dz1JsonStackStructState_max }
};

str_t Dz1JsonStackStructStateStrA(Dz1JsonStackStructState v)
{
	struct Dz1JsonStackStructStateMapA *i = NULL;
	for (i = Dz1JsonStackStructStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackStructState Dz1JsonStackStructStateFromStrA(str_t str)
{
	struct Dz1JsonStackStructStateMapA *i = NULL;
	for (i = Dz1JsonStackStructStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackStructState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonStackStructStateMapW
{
	wstr_t str;
	Dz1JsonStackStructState v;
} Dz1JsonStackStructStateMapW[] =
{
	{ (wchar_t *)L"init", Dz1JsonStackStructState_init },
	{ (wchar_t *)L"parsing_lstart", Dz1JsonStackStructState_parsing_lstart },
	{ (wchar_t *)L"parsing_pair", Dz1JsonStackStructState_parsing_pair },
	{ (wchar_t *)L"parsing_comma", Dz1JsonStackStructState_parsing_comma },
	{ (wchar_t *)L"parsing_lend", Dz1JsonStackStructState_parsing_lend },
	{ NULL, Dz1JsonStackStructState_max }
};

wstr_t Dz1JsonStackStructStateStrW(Dz1JsonStackStructState v)
{
	struct Dz1JsonStackStructStateMapW *i = NULL;
	for (i = Dz1JsonStackStructStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackStructState Dz1JsonStackStructStateFromStrW(wstr_t str)
{
	struct Dz1JsonStackStructStateMapW *i = NULL;
	for (i = Dz1JsonStackStructStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackStructState_max;
}
#endif // UNIX_SYSTEM

Dz1JsonStackStructState *Dz1JsonStackStructState_new(Dz1JsonStackStructState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackStructState *__internal_ret = (Dz1JsonStackStructState *)Dz1Calloc(sizeof(Dz1JsonStackStructState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonStackStructState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackStruct
Dz1JsonStackStruct *Dz1JsonStackStruct_new(Dz1JsonStackStructState state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackStruct *__internal_ret = (Dz1JsonStackStruct *)Dz1Calloc(sizeof(Dz1JsonStackStruct), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackStruct_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->state = state;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackStruct_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonStackStruct_copy(Dz1JsonStackStruct *dst, Dz1JsonStackStruct *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->state = src->state;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonStackStruct *Dz1JsonStackStruct_clone(Dz1JsonStackStruct *src, Dz1Error *err)
{
	Dz1JsonStackStruct *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonStackStruct *)Dz1Calloc(sizeof(Dz1JsonStackStruct), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackStruct_delAndSetNull, (void *)&dst);
		if (Dz1JsonStackStruct_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackStruct_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonStackStruct_purge(Dz1JsonStackStruct *p)
{
	if (p == NULL) return;
}

void Dz1JsonStackStruct_del(Dz1JsonStackStruct *p)
{
	if (p == NULL) return;
	Dz1JsonStackStruct_purge(p);
	Dz1Free(p);
}

void Dz1JsonStackStruct_dump(Dz1JsonStackStruct *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("state = %s(%d)\n"), Dz1JsonStackStructStateStr(p->state), p->state);
	}
}
// Dz1JsonStackStruct
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackUnionState
static struct Dz1JsonStackUnionStateMapA
{
	str_t str;
	Dz1JsonStackUnionState v;
} Dz1JsonStackUnionStateMapA[] =
{
	{ (char *)"init", Dz1JsonStackUnionState_init },
	{ (char *)"parsing_lstart", Dz1JsonStackUnionState_parsing_lstart },
	{ (char *)"parsing_pair", Dz1JsonStackUnionState_parsing_pair },
	{ (char *)"parsing_lend", Dz1JsonStackUnionState_parsing_lend },
	{ NULL, Dz1JsonStackUnionState_max }
};

str_t Dz1JsonStackUnionStateStrA(Dz1JsonStackUnionState v)
{
	struct Dz1JsonStackUnionStateMapA *i = NULL;
	for (i = Dz1JsonStackUnionStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackUnionState Dz1JsonStackUnionStateFromStrA(str_t str)
{
	struct Dz1JsonStackUnionStateMapA *i = NULL;
	for (i = Dz1JsonStackUnionStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackUnionState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonStackUnionStateMapW
{
	wstr_t str;
	Dz1JsonStackUnionState v;
} Dz1JsonStackUnionStateMapW[] =
{
	{ (wchar_t *)L"init", Dz1JsonStackUnionState_init },
	{ (wchar_t *)L"parsing_lstart", Dz1JsonStackUnionState_parsing_lstart },
	{ (wchar_t *)L"parsing_pair", Dz1JsonStackUnionState_parsing_pair },
	{ (wchar_t *)L"parsing_lend", Dz1JsonStackUnionState_parsing_lend },
	{ NULL, Dz1JsonStackUnionState_max }
};

wstr_t Dz1JsonStackUnionStateStrW(Dz1JsonStackUnionState v)
{
	struct Dz1JsonStackUnionStateMapW *i = NULL;
	for (i = Dz1JsonStackUnionStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackUnionState Dz1JsonStackUnionStateFromStrW(wstr_t str)
{
	struct Dz1JsonStackUnionStateMapW *i = NULL;
	for (i = Dz1JsonStackUnionStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackUnionState_max;
}
#endif // UNIX_SYSTEM

Dz1JsonStackUnionState *Dz1JsonStackUnionState_new(Dz1JsonStackUnionState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackUnionState *__internal_ret = (Dz1JsonStackUnionState *)Dz1Calloc(sizeof(Dz1JsonStackUnionState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonStackUnionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackUnion
Dz1JsonStackUnion *Dz1JsonStackUnion_new(Dz1JsonStackUnionState state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackUnion *__internal_ret = (Dz1JsonStackUnion *)Dz1Calloc(sizeof(Dz1JsonStackUnion), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackUnion_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->state = state;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackUnion_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonStackUnion_copy(Dz1JsonStackUnion *dst, Dz1JsonStackUnion *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->state = src->state;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonStackUnion *Dz1JsonStackUnion_clone(Dz1JsonStackUnion *src, Dz1Error *err)
{
	Dz1JsonStackUnion *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonStackUnion *)Dz1Calloc(sizeof(Dz1JsonStackUnion), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackUnion_delAndSetNull, (void *)&dst);
		if (Dz1JsonStackUnion_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackUnion_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonStackUnion_purge(Dz1JsonStackUnion *p)
{
	if (p == NULL) return;
}

void Dz1JsonStackUnion_del(Dz1JsonStackUnion *p)
{
	if (p == NULL) return;
	Dz1JsonStackUnion_purge(p);
	Dz1Free(p);
}

void Dz1JsonStackUnion_dump(Dz1JsonStackUnion *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("state = %s(%d)\n"), Dz1JsonStackUnionStateStr(p->state), p->state);
	}
}
// Dz1JsonStackUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackArrayState
static struct Dz1JsonStackArrayStateMapA
{
	str_t str;
	Dz1JsonStackArrayState v;
} Dz1JsonStackArrayStateMapA[] =
{
	{ (char *)"init", Dz1JsonStackArrayState_init },
	{ (char *)"parsing_bstart", Dz1JsonStackArrayState_parsing_bstart },
	{ (char *)"parsing_object", Dz1JsonStackArrayState_parsing_object },
	{ (char *)"parsing_comma", Dz1JsonStackArrayState_parsing_comma },
	{ (char *)"parsing_bend", Dz1JsonStackArrayState_parsing_bend },
	{ NULL, Dz1JsonStackArrayState_max }
};

str_t Dz1JsonStackArrayStateStrA(Dz1JsonStackArrayState v)
{
	struct Dz1JsonStackArrayStateMapA *i = NULL;
	for (i = Dz1JsonStackArrayStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackArrayState Dz1JsonStackArrayStateFromStrA(str_t str)
{
	struct Dz1JsonStackArrayStateMapA *i = NULL;
	for (i = Dz1JsonStackArrayStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackArrayState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonStackArrayStateMapW
{
	wstr_t str;
	Dz1JsonStackArrayState v;
} Dz1JsonStackArrayStateMapW[] =
{
	{ (wchar_t *)L"init", Dz1JsonStackArrayState_init },
	{ (wchar_t *)L"parsing_bstart", Dz1JsonStackArrayState_parsing_bstart },
	{ (wchar_t *)L"parsing_object", Dz1JsonStackArrayState_parsing_object },
	{ (wchar_t *)L"parsing_comma", Dz1JsonStackArrayState_parsing_comma },
	{ (wchar_t *)L"parsing_bend", Dz1JsonStackArrayState_parsing_bend },
	{ NULL, Dz1JsonStackArrayState_max }
};

wstr_t Dz1JsonStackArrayStateStrW(Dz1JsonStackArrayState v)
{
	struct Dz1JsonStackArrayStateMapW *i = NULL;
	for (i = Dz1JsonStackArrayStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackArrayState Dz1JsonStackArrayStateFromStrW(wstr_t str)
{
	struct Dz1JsonStackArrayStateMapW *i = NULL;
	for (i = Dz1JsonStackArrayStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackArrayState_max;
}
#endif // UNIX_SYSTEM

Dz1JsonStackArrayState *Dz1JsonStackArrayState_new(Dz1JsonStackArrayState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackArrayState *__internal_ret = (Dz1JsonStackArrayState *)Dz1Calloc(sizeof(Dz1JsonStackArrayState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonStackArrayState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackArray
Dz1JsonStackArray *Dz1JsonStackArray_new(Dz1JsonStackArrayState state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackArray *__internal_ret = (Dz1JsonStackArray *)Dz1Calloc(sizeof(Dz1JsonStackArray), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackArray_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->state = state;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackArray_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonStackArray_copy(Dz1JsonStackArray *dst, Dz1JsonStackArray *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->state = src->state;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonStackArray *Dz1JsonStackArray_clone(Dz1JsonStackArray *src, Dz1Error *err)
{
	Dz1JsonStackArray *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonStackArray *)Dz1Calloc(sizeof(Dz1JsonStackArray), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackArray_delAndSetNull, (void *)&dst);
		if (Dz1JsonStackArray_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackArray_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonStackArray_purge(Dz1JsonStackArray *p)
{
	if (p == NULL) return;
}

void Dz1JsonStackArray_del(Dz1JsonStackArray *p)
{
	if (p == NULL) return;
	Dz1JsonStackArray_purge(p);
	Dz1Free(p);
}

void Dz1JsonStackArray_dump(Dz1JsonStackArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("state = %s(%d)\n"), Dz1JsonStackArrayStateStr(p->state), p->state);
	}
}
// Dz1JsonStackArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackPairState
static struct Dz1JsonStackPairStateMapA
{
	str_t str;
	Dz1JsonStackPairState v;
} Dz1JsonStackPairStateMapA[] =
{
	{ (char *)"init", Dz1JsonStackPairState_init },
	{ (char *)"parsing_name", Dz1JsonStackPairState_parsing_name },
	{ (char *)"parsing_colon", Dz1JsonStackPairState_parsing_colon },
	{ (char *)"parsing_object", Dz1JsonStackPairState_parsing_object },
	{ NULL, Dz1JsonStackPairState_max }
};

str_t Dz1JsonStackPairStateStrA(Dz1JsonStackPairState v)
{
	struct Dz1JsonStackPairStateMapA *i = NULL;
	for (i = Dz1JsonStackPairStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackPairState Dz1JsonStackPairStateFromStrA(str_t str)
{
	struct Dz1JsonStackPairStateMapA *i = NULL;
	for (i = Dz1JsonStackPairStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackPairState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonStackPairStateMapW
{
	wstr_t str;
	Dz1JsonStackPairState v;
} Dz1JsonStackPairStateMapW[] =
{
	{ (wchar_t *)L"init", Dz1JsonStackPairState_init },
	{ (wchar_t *)L"parsing_name", Dz1JsonStackPairState_parsing_name },
	{ (wchar_t *)L"parsing_colon", Dz1JsonStackPairState_parsing_colon },
	{ (wchar_t *)L"parsing_object", Dz1JsonStackPairState_parsing_object },
	{ NULL, Dz1JsonStackPairState_max }
};

wstr_t Dz1JsonStackPairStateStrW(Dz1JsonStackPairState v)
{
	struct Dz1JsonStackPairStateMapW *i = NULL;
	for (i = Dz1JsonStackPairStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackPairState Dz1JsonStackPairStateFromStrW(wstr_t str)
{
	struct Dz1JsonStackPairStateMapW *i = NULL;
	for (i = Dz1JsonStackPairStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackPairState_max;
}
#endif // UNIX_SYSTEM

Dz1JsonStackPairState *Dz1JsonStackPairState_new(Dz1JsonStackPairState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackPairState *__internal_ret = (Dz1JsonStackPairState *)Dz1Calloc(sizeof(Dz1JsonStackPairState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonStackPairState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackPair
Dz1JsonStackPair *Dz1JsonStackPair_new(Dz1JsonStackPairState state, 
									   Dz1JsonSpecEntry *par_type/*_ref*/, 
									   void *par_ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackPair *__internal_ret = (Dz1JsonStackPair *)Dz1Calloc(sizeof(Dz1JsonStackPair), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackPair_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->state = state;
		__internal_ret->par_type = par_type;
		__internal_ret->par_ptr = par_ptr;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackPair_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonStackPair_copy(Dz1JsonStackPair *dst, Dz1JsonStackPair *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->state = src->state;
		dst->par_type = src->par_type;
		dst->par_ptr = src->par_ptr;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonStackPair *Dz1JsonStackPair_clone(Dz1JsonStackPair *src, Dz1Error *err)
{
	Dz1JsonStackPair *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonStackPair *)Dz1Calloc(sizeof(Dz1JsonStackPair), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackPair_delAndSetNull, (void *)&dst);
		if (Dz1JsonStackPair_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackPair_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonStackPair_purge(Dz1JsonStackPair *p)
{
	if (p == NULL) return;
}

void Dz1JsonStackPair_del(Dz1JsonStackPair *p)
{
	if (p == NULL) return;
	Dz1JsonStackPair_purge(p);
	Dz1Free(p);
}

void Dz1JsonStackPair_dump(Dz1JsonStackPair *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), Dz1JsonStackPairStateStr(p->state), p->state);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("par_type = ")); Dz1JsonSpecEntry_dump(p->par_type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("par_ptr = %p\n"), p->par_ptr);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonStackPair
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackObjState
static struct Dz1JsonStackObjStateMapA
{
	str_t str;
	Dz1JsonStackObjState v;
} Dz1JsonStackObjStateMapA[] =
{
	{ (char *)"init", Dz1JsonStackObjState_init },
	{ (char *)"parsing_lstart", Dz1JsonStackObjState_parsing_lstart },
	{ (char *)"parsing_object", Dz1JsonStackObjState_parsing_object },
	{ (char *)"parsing_lend", Dz1JsonStackObjState_parsing_lend },
	{ NULL, Dz1JsonStackObjState_max }
};

str_t Dz1JsonStackObjStateStrA(Dz1JsonStackObjState v)
{
	struct Dz1JsonStackObjStateMapA *i = NULL;
	for (i = Dz1JsonStackObjStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackObjState Dz1JsonStackObjStateFromStrA(str_t str)
{
	struct Dz1JsonStackObjStateMapA *i = NULL;
	for (i = Dz1JsonStackObjStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackObjState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonStackObjStateMapW
{
	wstr_t str;
	Dz1JsonStackObjState v;
} Dz1JsonStackObjStateMapW[] =
{
	{ (wchar_t *)L"init", Dz1JsonStackObjState_init },
	{ (wchar_t *)L"parsing_lstart", Dz1JsonStackObjState_parsing_lstart },
	{ (wchar_t *)L"parsing_object", Dz1JsonStackObjState_parsing_object },
	{ (wchar_t *)L"parsing_lend", Dz1JsonStackObjState_parsing_lend },
	{ NULL, Dz1JsonStackObjState_max }
};

wstr_t Dz1JsonStackObjStateStrW(Dz1JsonStackObjState v)
{
	struct Dz1JsonStackObjStateMapW *i = NULL;
	for (i = Dz1JsonStackObjStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackObjState Dz1JsonStackObjStateFromStrW(wstr_t str)
{
	struct Dz1JsonStackObjStateMapW *i = NULL;
	for (i = Dz1JsonStackObjStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackObjState_max;
}
#endif // UNIX_SYSTEM

Dz1JsonStackObjState *Dz1JsonStackObjState_new(Dz1JsonStackObjState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackObjState *__internal_ret = (Dz1JsonStackObjState *)Dz1Calloc(sizeof(Dz1JsonStackObjState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonStackObjState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackObj
Dz1JsonStackObj *Dz1JsonStackObj_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackObj *__internal_ret = (Dz1JsonStackObj *)Dz1Calloc(sizeof(Dz1JsonStackObj), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackObj_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackObj_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonStackObj_copy(Dz1JsonStackObj *dst, Dz1JsonStackObj *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->state = src->state;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonStackObj *Dz1JsonStackObj_clone(Dz1JsonStackObj *src, Dz1Error *err)
{
	Dz1JsonStackObj *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonStackObj *)Dz1Calloc(sizeof(Dz1JsonStackObj), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackObj_delAndSetNull, (void *)&dst);
		if (Dz1JsonStackObj_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackObj_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonStackObj_purge(Dz1JsonStackObj *p)
{
	if (p == NULL) return;
}

void Dz1JsonStackObj_del(Dz1JsonStackObj *p)
{
	if (p == NULL) return;
	Dz1JsonStackObj_purge(p);
	Dz1Free(p);
}

void Dz1JsonStackObj_dump(Dz1JsonStackObj *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("state = %s(%d)\n"), Dz1JsonStackObjStateStr(p->state), p->state);
	}
}
// Dz1JsonStackObj
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackDataPresent
static struct Dz1JsonStackDataPresentMapA
{
	str_t str;
	Dz1JsonStackDataPresent v;
} Dz1JsonStackDataPresentMapA[] =
{
	{ (char *)"pr", Dz1JsonStackDataPresent_pr },
	{ (char *)"st", Dz1JsonStackDataPresent_st },
	{ (char *)"un", Dz1JsonStackDataPresent_un },
	{ (char *)"ar", Dz1JsonStackDataPresent_ar },
	{ (char *)"pair", Dz1JsonStackDataPresent_pair },
	{ (char *)"obj", Dz1JsonStackDataPresent_obj },
	{ NULL, Dz1JsonStackDataPresent_max }
};

str_t Dz1JsonStackDataPresentStrA(Dz1JsonStackDataPresent v)
{
	struct Dz1JsonStackDataPresentMapA *i = NULL;
	for (i = Dz1JsonStackDataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackDataPresent Dz1JsonStackDataPresentFromStrA(str_t str)
{
	struct Dz1JsonStackDataPresentMapA *i = NULL;
	for (i = Dz1JsonStackDataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackDataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonStackDataPresentMapW
{
	wstr_t str;
	Dz1JsonStackDataPresent v;
} Dz1JsonStackDataPresentMapW[] =
{
	{ (wchar_t *)L"pr", Dz1JsonStackDataPresent_pr },
	{ (wchar_t *)L"st", Dz1JsonStackDataPresent_st },
	{ (wchar_t *)L"un", Dz1JsonStackDataPresent_un },
	{ (wchar_t *)L"ar", Dz1JsonStackDataPresent_ar },
	{ (wchar_t *)L"pair", Dz1JsonStackDataPresent_pair },
	{ (wchar_t *)L"obj", Dz1JsonStackDataPresent_obj },
	{ NULL, Dz1JsonStackDataPresent_max }
};

wstr_t Dz1JsonStackDataPresentStrW(Dz1JsonStackDataPresent v)
{
	struct Dz1JsonStackDataPresentMapW *i = NULL;
	for (i = Dz1JsonStackDataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonStackDataPresent Dz1JsonStackDataPresentFromStrW(wstr_t str)
{
	struct Dz1JsonStackDataPresentMapW *i = NULL;
	for (i = Dz1JsonStackDataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonStackDataPresent_max;
}
#endif // UNIX_SYSTEM

Dz1JsonStackDataPresent *Dz1JsonStackDataPresent_new(Dz1JsonStackDataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackDataPresent *__internal_ret = (Dz1JsonStackDataPresent *)Dz1Calloc(sizeof(Dz1JsonStackDataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1JsonStackDataPresent_dump(Dz1JsonStackDataPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1JsonStackDataPresentStr(*v));
}
// Dz1JsonStackDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackData
Dz1JsonStackData *Dz1JsonStackData_new(Dz1JsonStackDataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStackData *ret = (Dz1JsonStackData *)Dz1Calloc(sizeof(Dz1JsonStackData), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackData_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1JsonStackDataPresent_pr:
			// _U_cst_clone
			if (ptr != NULL) ret->x.pr = (Dz1JsonStackPrimitive *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonStackDataPresent_st:
			// _U_cst_clone
			if (ptr != NULL) ret->x.st = (Dz1JsonStackStruct *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonStackDataPresent_un:
			// _U_cst_clone
			if (ptr != NULL) ret->x.un = (Dz1JsonStackUnion *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonStackDataPresent_ar:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ar = (Dz1JsonStackArray *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonStackDataPresent_pair:
			// _U_cst_clone
			if (ptr != NULL) ret->x.pair = (Dz1JsonStackPair *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonStackDataPresent_obj:
			// _U_cst_clone
			if (ptr != NULL) ret->x.obj = (Dz1JsonStackObj *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonStackDataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1JsonStackData_copy(Dz1JsonStackData *ret, Dz1JsonStackData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1JsonStackDataPresent_pr:
			// _U_cst_clone
			if (src->x.pr && (ret->x.pr = Dz1JsonStackPrimitive_clone(src->x.pr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1JsonStackDataPresent_st:
			// _U_cst_clone
			if (src->x.st && (ret->x.st = Dz1JsonStackStruct_clone(src->x.st, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1JsonStackDataPresent_un:
			// _U_cst_clone
			if (src->x.un && (ret->x.un = Dz1JsonStackUnion_clone(src->x.un, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1JsonStackDataPresent_ar:
			// _U_cst_clone
			if (src->x.ar && (ret->x.ar = Dz1JsonStackArray_clone(src->x.ar, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1JsonStackDataPresent_pair:
			// _U_cst_clone
			if (src->x.pair && (ret->x.pair = Dz1JsonStackPair_clone(src->x.pair, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1JsonStackDataPresent_obj:
			// _U_cst_clone
			if (src->x.obj && (ret->x.obj = Dz1JsonStackObj_clone(src->x.obj, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonStackData *Dz1JsonStackData_clone(Dz1JsonStackData *src, Dz1Error *err)
{
	Dz1JsonStackData *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1JsonStackData *)Dz1Calloc(sizeof(Dz1JsonStackData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonStackData_delAndSetNull, (void *)&ret);
		if (Dz1JsonStackData_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStackData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonStackData_purge(Dz1JsonStackData *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1JsonStackDataPresent_pr:
		Dz1JsonStackPrimitive_del(p->x.pr);
		break;
	case Dz1JsonStackDataPresent_st:
		Dz1JsonStackStruct_del(p->x.st);
		break;
	case Dz1JsonStackDataPresent_un:
		Dz1JsonStackUnion_del(p->x.un);
		break;
	case Dz1JsonStackDataPresent_ar:
		Dz1JsonStackArray_del(p->x.ar);
		break;
	case Dz1JsonStackDataPresent_pair:
		Dz1JsonStackPair_del(p->x.pair);
		break;
	case Dz1JsonStackDataPresent_obj:
		Dz1JsonStackObj_del(p->x.obj);
		break;
	default:
		break;
	}
}

void Dz1JsonStackData_del(Dz1JsonStackData *p)
{
	if (!p) return;
	Dz1JsonStackData_purge(p);
	Dz1Free(p);
}

void Dz1JsonStackData_dump(Dz1JsonStackData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1JsonStackDataPresent_pr:
		Dz1Thread_printf(Dz1T("pr = ")); Dz1JsonStackPrimitive_dump(p->x.pr, tab); 
		break;
	case Dz1JsonStackDataPresent_st:
		Dz1Thread_printf(Dz1T("st = ")); Dz1JsonStackStruct_dump(p->x.st, tab); 
		break;
	case Dz1JsonStackDataPresent_un:
		Dz1Thread_printf(Dz1T("un = ")); Dz1JsonStackUnion_dump(p->x.un, tab); 
		break;
	case Dz1JsonStackDataPresent_ar:
		Dz1Thread_printf(Dz1T("ar = ")); Dz1JsonStackArray_dump(p->x.ar, tab); 
		break;
	case Dz1JsonStackDataPresent_pair:
		Dz1Thread_printf(Dz1T("pair = ")); Dz1JsonStackPair_dump(p->x.pair, tab); 
		break;
	case Dz1JsonStackDataPresent_obj:
		Dz1Thread_printf(Dz1T("obj = ")); Dz1JsonStackObj_dump(p->x.obj, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1JsonStackData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStack
Dz1JsonStack *Dz1JsonStack_new(Dz1JsonStackData *data, Dz1JsonVarBind *dst_var, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonStack *__internal_ret = (Dz1JsonStack *)Dz1Calloc(sizeof(Dz1JsonStack), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonStack_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->data = data;
		__internal_ret->dst_var = dst_var;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonStack_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonStack_purge(Dz1JsonStack *p)
{
	if (p == NULL) return;
	Dz1JsonStackData_del(p->data);
	Dz1JsonVarBind_del(p->dst_var);
	Dz1JsonVarBind_del(p->ret_var);
}

void Dz1JsonStack_del(Dz1JsonStack *p)
{
	if (p == NULL) return;
	Dz1JsonStack_purge(p);
	Dz1Free(p);
}

// Dz1JsonStack
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonOutputEntry
Dz1JsonOutputEntry *Dz1JsonOutputEntry_new(Dz1JsonOutputEntry *next/*_ref*/, 
										   void *result, 
										   Dz1JsonObjDelF result_del, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonOutputEntry *__internal_ret = (Dz1JsonOutputEntry *)Dz1Calloc(sizeof(Dz1JsonOutputEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonOutputEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->next = next;
		__internal_ret->result = result;
		__internal_ret->result_del = result_del;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonOutputEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonOutputEntry_copy(Dz1JsonOutputEntry *dst, Dz1JsonOutputEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->next = src->next;
		dst->result = src->result;
		dst->result_del = src->result_del;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonOutputEntry *Dz1JsonOutputEntry_clone(Dz1JsonOutputEntry *src, Dz1Error *err)
{
	Dz1JsonOutputEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonOutputEntry *)Dz1Calloc(sizeof(Dz1JsonOutputEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonOutputEntry_delAndSetNull, (void *)&dst);
		if (Dz1JsonOutputEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonOutputEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonOutputEntry_dump(Dz1JsonOutputEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Recursive member
		// Cascade dump
		{	// cascade dump
			int _cnt;
			Dz1JsonOutputEntry *i = NULL;
			Dz1Thread_tprintf(tab++, Dz1T("cascade {\n"));
			for (i = p->next, _cnt = 1; i; i = i->next, _cnt++)
			{
				Dz1Thread_tprintf(tab, Dz1T("next[%d] = "), _cnt);
				Dz1JsonOutputEntry_dump(i, tab);
			}
			Dz1Thread_tprintf(--tab, Dz1T("}\n"));
		}
		Dz1Thread_tprintf(tab, Dz1T("result = %p\n"), p->result);
		Dz1Thread_tprintf(tab, Dz1T("result_del = %p\n"), p->result_del);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonOutputEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonOutputFifo
Dz1JsonOutputFifo *Dz1JsonOutputFifo_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonOutputFifo *__internal_ret = (Dz1JsonOutputFifo *)Dz1Calloc(sizeof(Dz1JsonOutputFifo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonOutputFifo_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonOutputFifo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonOutputFifo_copy(Dz1JsonOutputFifo *dst, Dz1JsonOutputFifo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->head && (dst->head = Dz1JsonOutputEntry_clone(src->head, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->tail = src->tail;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonOutputFifo *Dz1JsonOutputFifo_clone(Dz1JsonOutputFifo *src, Dz1Error *err)
{
	Dz1JsonOutputFifo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonOutputFifo *)Dz1Calloc(sizeof(Dz1JsonOutputFifo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonOutputFifo_delAndSetNull, (void *)&dst);
		if (Dz1JsonOutputFifo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonOutputFifo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonOutputFifo_dump(Dz1JsonOutputFifo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		// Normal member
		Dz1Thread_printf(Dz1T("head = ")); Dz1JsonOutputEntry_dump(p->head, tab); 
	}
}
// Dz1JsonOutputFifo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonEnv
Dz1JsonEnv *Dz1JsonEnv_new(Dz1JsonLexer *lexer, 
						   Dz1JsonSpec *spec/*_ref*/, 
						   Dz1JsonSpecEntry *root_spe/*_ref*/, 
						   Dz1JsonFifo *ingress, 
						   Dz1JsonOutputFifo *egress, 
						   Dz1JsonConv *stringify_conv, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonEnv *__internal_ret = (Dz1JsonEnv *)Dz1Calloc(sizeof(Dz1JsonEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonEnv_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->lexer = lexer;
		__internal_ret->spec = spec;
		__internal_ret->root_spe = root_spe;
		__internal_ret->ingress = ingress;
		__internal_ret->egress = egress;
		__internal_ret->stringify_conv = stringify_conv;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonEnv_purge(Dz1JsonEnv *p)
{
	if (p == NULL) return;
	Dz1JsonLexer_del(p->lexer);
	Dz1JsonFifo_del(p->ingress);
	Dz1JsonOutputFifo_del(p->egress);
	Dz1JsonStack_del(p->stk);
	Dz1JsonConv_del(p->stringify_conv);
	Dz1ElasticBuf_del(p->stringify_buf);
}

void Dz1JsonEnv_del(Dz1JsonEnv *p)
{
	if (p == NULL) return;
	Dz1JsonEnv_purge(p);
	Dz1Free(p);
}

void Dz1JsonEnv_dump(Dz1JsonEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("lexer = ")); Dz1JsonLexer_dump(p->lexer, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("root_spe = ")); Dz1JsonSpecEntry_dump(p->root_spe, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("ingress = ")); Dz1JsonFifo_dump(p->ingress, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("egress = ")); Dz1JsonOutputFifo_dump(p->egress, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("stk = ")); Dz1JsonStack_dump(p->stk, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("stringify_conv = %p\n"), p->stringify_conv);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("stringify_buf = ")); Dz1ElasticBuf_dump(p->stringify_buf, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonEnv
////////////////////////////////////////////////////////////////////////////////

