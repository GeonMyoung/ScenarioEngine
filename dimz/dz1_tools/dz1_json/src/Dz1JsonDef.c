////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1JsonDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonNewLine
static struct Dz1JsonNewLineMapA
{
	str_t str;
	Dz1JsonNewLine v;
} Dz1JsonNewLineMapA[] =
{
	{ (char *)"continuous", Dz1JsonNewLine_continuous },
	{ (char *)"cr", Dz1JsonNewLine_cr },
	{ (char *)"lf", Dz1JsonNewLine_lf },
	{ (char *)"crlf", Dz1JsonNewLine_crlf },
	{ NULL, Dz1JsonNewLine_max }
};

str_t Dz1JsonNewLineStrA(Dz1JsonNewLine v)
{
	struct Dz1JsonNewLineMapA *i = NULL;
	for (i = Dz1JsonNewLineMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonNewLine Dz1JsonNewLineFromStrA(str_t str)
{
	struct Dz1JsonNewLineMapA *i = NULL;
	for (i = Dz1JsonNewLineMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonNewLine_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonNewLineMapW
{
	wstr_t str;
	Dz1JsonNewLine v;
} Dz1JsonNewLineMapW[] =
{
	{ (wchar_t *)L"continuous", Dz1JsonNewLine_continuous },
	{ (wchar_t *)L"cr", Dz1JsonNewLine_cr },
	{ (wchar_t *)L"lf", Dz1JsonNewLine_lf },
	{ (wchar_t *)L"crlf", Dz1JsonNewLine_crlf },
	{ NULL, Dz1JsonNewLine_max }
};

wstr_t Dz1JsonNewLineStrW(Dz1JsonNewLine v)
{
	struct Dz1JsonNewLineMapW *i = NULL;
	for (i = Dz1JsonNewLineMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonNewLine Dz1JsonNewLineFromStrW(wstr_t str)
{
	struct Dz1JsonNewLineMapW *i = NULL;
	for (i = Dz1JsonNewLineMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonNewLine_max;
}
#endif // UNIX_SYSTEM

Dz1JsonNewLine *Dz1JsonNewLine_new(Dz1JsonNewLine *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonNewLine *__internal_ret = (Dz1JsonNewLine *)Dz1Calloc(sizeof(Dz1JsonNewLine), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonNewLine
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonNewLineInfo
Dz1JsonNewLineInfo *Dz1JsonNewLineInfo_new(Dz1Str str, size_t len, u32_t tab, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonNewLineInfo *__internal_ret = (Dz1JsonNewLineInfo *)Dz1Calloc(sizeof(Dz1JsonNewLineInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonNewLineInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (str && (__internal_ret->str = Dz1Str_clone(str, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->len = len;
			__internal_ret->tab = tab;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonNewLineInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonNewLineInfo_purge(Dz1JsonNewLineInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->str);
}

void Dz1JsonNewLineInfo_del(Dz1JsonNewLineInfo *p)
{
	if (p == NULL) return;
	Dz1JsonNewLineInfo_purge(p);
	Dz1Free(p);
}

// Dz1JsonNewLineInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonTokenType
static struct Dz1JsonTokenTypeMapA
{
	str_t str;
	Dz1JsonTokenType v;
} Dz1JsonTokenTypeMapA[] =
{
	{ (char *)"comma", Dz1JsonTokenType_comma },
	{ (char *)"dot", Dz1JsonTokenType_dot },
	{ (char *)"white_space", Dz1JsonTokenType_white_space },
	{ (char *)"lst_start", Dz1JsonTokenType_lst_start },
	{ (char *)"lst_end", Dz1JsonTokenType_lst_end },
	{ (char *)"blk_start", Dz1JsonTokenType_blk_start },
	{ (char *)"blk_end", Dz1JsonTokenType_blk_end },
	{ (char *)"colon", Dz1JsonTokenType_colon },
	{ (char *)"plus", Dz1JsonTokenType_plus },
	{ (char *)"minus", Dz1JsonTokenType_minus },
	{ (char *)"number", Dz1JsonTokenType_number },
	{ (char *)"string", Dz1JsonTokenType_string },
	{ (char *)"nul", Dz1JsonTokenType_nul },
	{ (char *)"symbol", Dz1JsonTokenType_symbol },
	{ NULL, Dz1JsonTokenType_max }
};

str_t Dz1JsonTokenTypeStrA(Dz1JsonTokenType v)
{
	struct Dz1JsonTokenTypeMapA *i = NULL;
	for (i = Dz1JsonTokenTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonTokenType Dz1JsonTokenTypeFromStrA(str_t str)
{
	struct Dz1JsonTokenTypeMapA *i = NULL;
	for (i = Dz1JsonTokenTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonTokenType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonTokenTypeMapW
{
	wstr_t str;
	Dz1JsonTokenType v;
} Dz1JsonTokenTypeMapW[] =
{
	{ (wchar_t *)L"comma", Dz1JsonTokenType_comma },
	{ (wchar_t *)L"dot", Dz1JsonTokenType_dot },
	{ (wchar_t *)L"white_space", Dz1JsonTokenType_white_space },
	{ (wchar_t *)L"lst_start", Dz1JsonTokenType_lst_start },
	{ (wchar_t *)L"lst_end", Dz1JsonTokenType_lst_end },
	{ (wchar_t *)L"blk_start", Dz1JsonTokenType_blk_start },
	{ (wchar_t *)L"blk_end", Dz1JsonTokenType_blk_end },
	{ (wchar_t *)L"colon", Dz1JsonTokenType_colon },
	{ (wchar_t *)L"plus", Dz1JsonTokenType_plus },
	{ (wchar_t *)L"minus", Dz1JsonTokenType_minus },
	{ (wchar_t *)L"number", Dz1JsonTokenType_number },
	{ (wchar_t *)L"string", Dz1JsonTokenType_string },
	{ (wchar_t *)L"nul", Dz1JsonTokenType_nul },
	{ (wchar_t *)L"symbol", Dz1JsonTokenType_symbol },
	{ NULL, Dz1JsonTokenType_max }
};

wstr_t Dz1JsonTokenTypeStrW(Dz1JsonTokenType v)
{
	struct Dz1JsonTokenTypeMapW *i = NULL;
	for (i = Dz1JsonTokenTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonTokenType Dz1JsonTokenTypeFromStrW(wstr_t str)
{
	struct Dz1JsonTokenTypeMapW *i = NULL;
	for (i = Dz1JsonTokenTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonTokenType_max;
}
#endif // UNIX_SYSTEM

Dz1JsonTokenType *Dz1JsonTokenType_new(Dz1JsonTokenType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonTokenType *__internal_ret = (Dz1JsonTokenType *)Dz1Calloc(sizeof(Dz1JsonTokenType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonTokenType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonToken
Dz1JsonToken *Dz1JsonToken_new(Dz1JsonTokenType t, Dz1Str v, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonToken *__internal_ret = (Dz1JsonToken *)Dz1Calloc(sizeof(Dz1JsonToken), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonToken_delAndSetNull, (void *)&__internal_ret);
		
		if (v && (__internal_ret->v = Dz1Str_clone(v, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->t = t;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonToken_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonToken_copy(Dz1JsonToken *dst, Dz1JsonToken *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->v && (dst->v = Dz1Str_clone(src->v, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->t = src->t;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonToken *Dz1JsonToken_clone(Dz1JsonToken *src, Dz1Error *err)
{
	Dz1JsonToken *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonToken *)Dz1Calloc(sizeof(Dz1JsonToken), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonToken_delAndSetNull, (void *)&dst);
		if (Dz1JsonToken_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonToken_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonToken_purge(Dz1JsonToken *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->v);
}

void Dz1JsonToken_del(Dz1JsonToken *p)
{
	if (p == NULL) return;
	Dz1JsonToken_purge(p);
	Dz1Free(p);
}

// Dz1JsonToken
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecPrimitive
Dz1JsonSpecPrimitive *Dz1JsonSpecPrimitive_new(Dz1JsonSpecEntry *owner/*_ref*/, 
											   Dz1JsonSpecPrimitiveLoaderF loader, 
											   Dz1JsonSpecPrimitiveStringifyF stringify, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecPrimitive *__internal_ret = (Dz1JsonSpecPrimitive *)Dz1Calloc(sizeof(Dz1JsonSpecPrimitive), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecPrimitive_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->owner = owner;
		__internal_ret->loader = loader;
		__internal_ret->stringify = stringify;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecPrimitive_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonSpecPrimitive_copy(Dz1JsonSpecPrimitive *dst, Dz1JsonSpecPrimitive *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->owner = src->owner;
		dst->loader = src->loader;
		dst->stringify = src->stringify;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonSpecPrimitive *Dz1JsonSpecPrimitive_clone(Dz1JsonSpecPrimitive *src, Dz1Error *err)
{
	Dz1JsonSpecPrimitive *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonSpecPrimitive *)Dz1Calloc(sizeof(Dz1JsonSpecPrimitive), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecPrimitive_delAndSetNull, (void *)&dst);
		if (Dz1JsonSpecPrimitive_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecPrimitive_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonSpecPrimitive_purge(Dz1JsonSpecPrimitive *p)
{
	if (p == NULL) return;
}

void Dz1JsonSpecPrimitive_del(Dz1JsonSpecPrimitive *p)
{
	if (p == NULL) return;
	Dz1JsonSpecPrimitive_purge(p);
	Dz1Free(p);
}

void Dz1JsonSpecPrimitive_dump(Dz1JsonSpecPrimitive *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("loader = %p\n"), p->loader);
		Dz1Thread_tprintf(tab, Dz1T("stringify = %p\n"), p->stringify);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonSpecPrimitive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecChild
Dz1JsonSpecChild *Dz1JsonSpecChild_new(Dz1Str name, Dz1Str type, u32_t index, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecChild *__internal_ret = (Dz1JsonSpecChild *)Dz1Calloc(sizeof(Dz1JsonSpecChild), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecChild_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if (type && (__internal_ret->type = Dz1Str_clone(type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->index = index;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecChild_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonSpecChild_copy(Dz1JsonSpecChild *dst, Dz1JsonSpecChild *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->type && (dst->type = Dz1Str_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->index = src->index;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonSpecChild *Dz1JsonSpecChild_clone(Dz1JsonSpecChild *src, Dz1Error *err)
{
	Dz1JsonSpecChild *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonSpecChild *)Dz1Calloc(sizeof(Dz1JsonSpecChild), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecChild_delAndSetNull, (void *)&dst);
		if (Dz1JsonSpecChild_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecChild_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonSpecChild_purge(Dz1JsonSpecChild *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1Str_del(p->type);
}

void Dz1JsonSpecChild_del(Dz1JsonSpecChild *p)
{
	if (p == NULL) return;
	Dz1JsonSpecChild_purge(p);
	Dz1Free(p);
}

int Dz1JsonSpecChild_cmp(Dz1JsonSpecChild *a, Dz1JsonSpecChild *b)
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
// Dz1JsonSpecChild
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecChilds
static Dz1Error Dz1JsonSpecChilds_add(Dz1JsonSpecChilds *p, Dz1JsonSpecChild *data)
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

static bool_t Dz1JsonSpecChilds_remove(Dz1JsonSpecChilds *p, Dz1JsonSpecChild *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1JsonSpecChild *Dz1JsonSpecChilds_extract(Dz1JsonSpecChilds *p, Dz1JsonSpecChild *key)
{
	return (Dz1JsonSpecChild *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1JsonSpecChildsMkArrArg
{
	Dz1JsonSpecChild **arr;
	unsigned int idx;
} Dz1JsonSpecChildsMkArrArg;

static Dz1Error _Dz1JsonSpecChilds_get_array(void *ptr, Dz1JsonSpecChild *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonSpecChildsMkArrArg *arg = (Dz1JsonSpecChildsMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1JsonSpecChild **Dz1JsonSpecChilds_get_array(Dz1JsonSpecChilds *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1JsonSpecChild **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1JsonSpecChild **)Dz1Calloc(sizeof(Dz1JsonSpecChild *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonSpecChildsMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1JsonSpecChilds_get_array, (void *)&arg);
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

static Dz1Error Dz1JsonSpecChilds_travelForward(Dz1JsonSpecChilds *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecChild *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1JsonSpecChilds_travelBackward(Dz1JsonSpecChilds *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecChild *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1JsonSpecChild *Dz1JsonSpecChilds_find(Dz1JsonSpecChilds *p, Dz1JsonSpecChild *key)
{
	return (Dz1JsonSpecChild *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1JsonSpecChilds_count(Dz1JsonSpecChilds *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1JsonSpecChilds *Dz1JsonSpecChilds_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecChilds *ret = (Dz1JsonSpecChilds *)Dz1Calloc(sizeof(Dz1JsonSpecChilds), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpecChilds_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1JsonSpecChild_cmp,
				(Dz1DelFunc)Dz1JsonSpecChild_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1JsonSpecChilds_count;
			ret->travel = Dz1JsonSpecChilds_travelForward;
			ret->travelForward = Dz1JsonSpecChilds_travelForward;
			ret->travelBackward = Dz1JsonSpecChilds_travelBackward;
			ret->get_array = Dz1JsonSpecChilds_get_array;
			ret->add = Dz1JsonSpecChilds_add;
			ret->remove = Dz1JsonSpecChilds_remove;
			ret->find = Dz1JsonSpecChilds_find;
			ret->extract = Dz1JsonSpecChilds_extract;
			ret->cmp = Dz1JsonSpecChild_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecChilds_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1JsonSpecChilds_clone(void *ptr, Dz1JsonSpecChild *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonSpecChilds *p = (Dz1JsonSpecChilds *)ptr;
	Dz1JsonSpecChild *cloned = Dz1JsonSpecChild_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1JsonSpecChilds *Dz1JsonSpecChilds_clone(Dz1JsonSpecChilds *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecChilds *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1JsonSpecChilds_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpecChilds_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1JsonSpecChilds_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecChilds_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonSpecChilds_purge(Dz1JsonSpecChilds *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1JsonSpecChilds_del(Dz1JsonSpecChilds *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1JsonSpecChilds_dump(void *ptr, Dz1JsonSpecChild *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1JsonSpecChild_dump(p, tab);
	return err;
}

void Dz1JsonSpecChilds_dump(Dz1JsonSpecChilds *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1JsonSpecChilds_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonSpecChilds
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonConstructType
static struct Dz1JsonConstructTypeMapA
{
	str_t str;
	Dz1JsonConstructType v;
} Dz1JsonConstructTypeMapA[] =
{
	{ (char *)"struct", Dz1JsonConstructType_struct },
	{ (char *)"union", Dz1JsonConstructType_union },
	{ NULL, Dz1JsonConstructType_max }
};

str_t Dz1JsonConstructTypeStrA(Dz1JsonConstructType v)
{
	struct Dz1JsonConstructTypeMapA *i = NULL;
	for (i = Dz1JsonConstructTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonConstructType Dz1JsonConstructTypeFromStrA(str_t str)
{
	struct Dz1JsonConstructTypeMapA *i = NULL;
	for (i = Dz1JsonConstructTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonConstructType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonConstructTypeMapW
{
	wstr_t str;
	Dz1JsonConstructType v;
} Dz1JsonConstructTypeMapW[] =
{
	{ (wchar_t *)L"struct", Dz1JsonConstructType_struct },
	{ (wchar_t *)L"union", Dz1JsonConstructType_union },
	{ NULL, Dz1JsonConstructType_max }
};

wstr_t Dz1JsonConstructTypeStrW(Dz1JsonConstructType v)
{
	struct Dz1JsonConstructTypeMapW *i = NULL;
	for (i = Dz1JsonConstructTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonConstructType Dz1JsonConstructTypeFromStrW(wstr_t str)
{
	struct Dz1JsonConstructTypeMapW *i = NULL;
	for (i = Dz1JsonConstructTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonConstructType_max;
}
#endif // UNIX_SYSTEM

Dz1JsonConstructType *Dz1JsonConstructType_new(Dz1JsonConstructType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonConstructType *__internal_ret = (Dz1JsonConstructType *)Dz1Calloc(sizeof(Dz1JsonConstructType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1JsonConstructType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecConstruct
Dz1JsonSpecConstruct *Dz1JsonSpecConstruct_new(Dz1JsonSpecEntry *owner/*_ref*/, 
											   Dz1JsonConstructType type, 
											   Dz1JsonConstructSetChildF set_child, 
											   Dz1JsonConstructGetChildF get_child, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecConstruct *__internal_ret = (Dz1JsonSpecConstruct *)Dz1Calloc(sizeof(Dz1JsonSpecConstruct), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecConstruct_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->childs = Dz1JsonSpecChilds_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->owner = owner;
			__internal_ret->type = type;
			__internal_ret->set_child = set_child;
			__internal_ret->get_child = get_child;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecConstruct_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonSpecConstruct_copy(Dz1JsonSpecConstruct *dst, Dz1JsonSpecConstruct *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->childs && (dst->childs = Dz1JsonSpecChilds_clone(src->childs, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->owner = src->owner;
		dst->type = src->type;
		dst->set_child = src->set_child;
		dst->get_child = src->get_child;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonSpecConstruct *Dz1JsonSpecConstruct_clone(Dz1JsonSpecConstruct *src, Dz1Error *err)
{
	Dz1JsonSpecConstruct *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonSpecConstruct *)Dz1Calloc(sizeof(Dz1JsonSpecConstruct), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecConstruct_delAndSetNull, (void *)&dst);
		if (Dz1JsonSpecConstruct_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecConstruct_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonSpecConstruct_purge(Dz1JsonSpecConstruct *p)
{
	if (p == NULL) return;
	Dz1JsonSpecChilds_del(p->childs);
}

void Dz1JsonSpecConstruct_del(Dz1JsonSpecConstruct *p)
{
	if (p == NULL) return;
	Dz1JsonSpecConstruct_purge(p);
	Dz1Free(p);
}

void Dz1JsonSpecConstruct_dump(Dz1JsonSpecConstruct *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("childs = ")); Dz1JsonSpecChilds_dump(p->childs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type = %s(%d)\n"), Dz1JsonConstructTypeStr(p->type), p->type);
		Dz1Thread_tprintf(tab, Dz1T("set_child = %p\n"), p->set_child);
		Dz1Thread_tprintf(tab, Dz1T("get_child = %p\n"), p->get_child);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonSpecConstruct
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecArray
Dz1JsonSpecArray *Dz1JsonSpecArray_new(Dz1JsonSpecEntry *owner/*_ref*/, 
									   Dz1Str elem_type, 
									   Dz1JsonArrayAppendF append, 
									   Dz1JsonArrayCountF count, 
									   Dz1JsonArrayTravelF travel, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecArray *__internal_ret = (Dz1JsonSpecArray *)Dz1Calloc(sizeof(Dz1JsonSpecArray), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecArray_delAndSetNull, (void *)&__internal_ret);
		
		if (elem_type && (__internal_ret->elem_type = Dz1Str_clone(elem_type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->owner = owner;
			__internal_ret->append = append;
			__internal_ret->count = count;
			__internal_ret->travel = travel;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecArray_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonSpecArray_copy(Dz1JsonSpecArray *dst, Dz1JsonSpecArray *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->elem_type && (dst->elem_type = Dz1Str_clone(src->elem_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->owner = src->owner;
		dst->append = src->append;
		dst->count = src->count;
		dst->travel = src->travel;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonSpecArray *Dz1JsonSpecArray_clone(Dz1JsonSpecArray *src, Dz1Error *err)
{
	Dz1JsonSpecArray *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonSpecArray *)Dz1Calloc(sizeof(Dz1JsonSpecArray), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecArray_delAndSetNull, (void *)&dst);
		if (Dz1JsonSpecArray_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecArray_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonSpecArray_purge(Dz1JsonSpecArray *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->elem_type);
}

void Dz1JsonSpecArray_del(Dz1JsonSpecArray *p)
{
	if (p == NULL) return;
	Dz1JsonSpecArray_purge(p);
	Dz1Free(p);
}

void Dz1JsonSpecArray_dump(Dz1JsonSpecArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("elem_type = ")); Dz1Str_dump(p->elem_type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("append = %p\n"), p->append);
		Dz1Thread_tprintf(tab, Dz1T("count = %p\n"), p->count);
		Dz1Thread_tprintf(tab, Dz1T("travel = %p\n"), p->travel);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonSpecArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecDataPresent
static struct Dz1JsonSpecDataPresentMapA
{
	str_t str;
	Dz1JsonSpecDataPresent v;
} Dz1JsonSpecDataPresentMapA[] =
{
	{ (char *)"pr", Dz1JsonSpecDataPresent_pr },
	{ (char *)"cst", Dz1JsonSpecDataPresent_cst },
	{ (char *)"ar", Dz1JsonSpecDataPresent_ar },
	{ NULL, Dz1JsonSpecDataPresent_max }
};

str_t Dz1JsonSpecDataPresentStrA(Dz1JsonSpecDataPresent v)
{
	struct Dz1JsonSpecDataPresentMapA *i = NULL;
	for (i = Dz1JsonSpecDataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonSpecDataPresent Dz1JsonSpecDataPresentFromStrA(str_t str)
{
	struct Dz1JsonSpecDataPresentMapA *i = NULL;
	for (i = Dz1JsonSpecDataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonSpecDataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1JsonSpecDataPresentMapW
{
	wstr_t str;
	Dz1JsonSpecDataPresent v;
} Dz1JsonSpecDataPresentMapW[] =
{
	{ (wchar_t *)L"pr", Dz1JsonSpecDataPresent_pr },
	{ (wchar_t *)L"cst", Dz1JsonSpecDataPresent_cst },
	{ (wchar_t *)L"ar", Dz1JsonSpecDataPresent_ar },
	{ NULL, Dz1JsonSpecDataPresent_max }
};

wstr_t Dz1JsonSpecDataPresentStrW(Dz1JsonSpecDataPresent v)
{
	struct Dz1JsonSpecDataPresentMapW *i = NULL;
	for (i = Dz1JsonSpecDataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1JsonSpecDataPresent Dz1JsonSpecDataPresentFromStrW(wstr_t str)
{
	struct Dz1JsonSpecDataPresentMapW *i = NULL;
	for (i = Dz1JsonSpecDataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1JsonSpecDataPresent_max;
}
#endif // UNIX_SYSTEM

Dz1JsonSpecDataPresent *Dz1JsonSpecDataPresent_new(Dz1JsonSpecDataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecDataPresent *__internal_ret = (Dz1JsonSpecDataPresent *)Dz1Calloc(sizeof(Dz1JsonSpecDataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1JsonSpecDataPresent_dump(Dz1JsonSpecDataPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1JsonSpecDataPresentStr(*v));
}
// Dz1JsonSpecDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecData
Dz1JsonSpecData *Dz1JsonSpecData_new(Dz1JsonSpecDataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecData *ret = (Dz1JsonSpecData *)Dz1Calloc(sizeof(Dz1JsonSpecData), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecData_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1JsonSpecDataPresent_pr:
			// _U_cst_clone
			if (ptr != NULL) ret->x.pr = (Dz1JsonSpecPrimitive *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonSpecDataPresent_cst:
			// _U_cst_clone
			if (ptr != NULL) ret->x.cst = (Dz1JsonSpecConstruct *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonSpecDataPresent_ar:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ar = (Dz1JsonSpecArray *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1JsonSpecDataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1JsonSpecData_copy(Dz1JsonSpecData *ret, Dz1JsonSpecData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1JsonSpecDataPresent_pr:
			// _U_cst_clone
			if (src->x.pr && (ret->x.pr = Dz1JsonSpecPrimitive_clone(src->x.pr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1JsonSpecDataPresent_cst:
			// _U_cst_clone
			if (src->x.cst && (ret->x.cst = Dz1JsonSpecConstruct_clone(src->x.cst, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1JsonSpecDataPresent_ar:
			// _U_cst_clone
			if (src->x.ar && (ret->x.ar = Dz1JsonSpecArray_clone(src->x.ar, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonSpecData *Dz1JsonSpecData_clone(Dz1JsonSpecData *src, Dz1Error *err)
{
	Dz1JsonSpecData *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1JsonSpecData *)Dz1Calloc(sizeof(Dz1JsonSpecData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecData_delAndSetNull, (void *)&ret);
		if (Dz1JsonSpecData_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonSpecData_purge(Dz1JsonSpecData *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1JsonSpecDataPresent_pr:
		Dz1JsonSpecPrimitive_del(p->x.pr);
		break;
	case Dz1JsonSpecDataPresent_cst:
		Dz1JsonSpecConstruct_del(p->x.cst);
		break;
	case Dz1JsonSpecDataPresent_ar:
		Dz1JsonSpecArray_del(p->x.ar);
		break;
	default:
		break;
	}
}

void Dz1JsonSpecData_del(Dz1JsonSpecData *p)
{
	if (!p) return;
	Dz1JsonSpecData_purge(p);
	Dz1Free(p);
}

void Dz1JsonSpecData_dump(Dz1JsonSpecData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1JsonSpecDataPresent_pr:
		Dz1Thread_printf(Dz1T("pr = ")); Dz1JsonSpecPrimitive_dump(p->x.pr, tab); 
		break;
	case Dz1JsonSpecDataPresent_cst:
		Dz1Thread_printf(Dz1T("cst = ")); Dz1JsonSpecConstruct_dump(p->x.cst, tab); 
		break;
	case Dz1JsonSpecDataPresent_ar:
		Dz1Thread_printf(Dz1T("ar = ")); Dz1JsonSpecArray_dump(p->x.ar, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1JsonSpecData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecEntry
Dz1JsonSpecEntry *Dz1JsonSpecEntry_new(Dz1Str name, 
									   Dz1JsonObjGenF gen, 
									   Dz1JsonObjDelF del, 
									   Dz1JsonSpecData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecEntry *__internal_ret = (Dz1JsonSpecEntry *)Dz1Calloc(sizeof(Dz1JsonSpecEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->gen = gen;
			__internal_ret->del = del;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1JsonSpecEntry_copy(Dz1JsonSpecEntry *dst, Dz1JsonSpecEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1JsonSpecData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->gen = src->gen;
		dst->del = src->del;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1JsonSpecEntry *Dz1JsonSpecEntry_clone(Dz1JsonSpecEntry *src, Dz1Error *err)
{
	Dz1JsonSpecEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1JsonSpecEntry *)Dz1Calloc(sizeof(Dz1JsonSpecEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpecEntry_delAndSetNull, (void *)&dst);
		if (Dz1JsonSpecEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1JsonSpecEntry_purge(Dz1JsonSpecEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1JsonSpecData_del(p->data);
}

void Dz1JsonSpecEntry_del(Dz1JsonSpecEntry *p)
{
	if (p == NULL) return;
	Dz1JsonSpecEntry_purge(p);
	Dz1Free(p);
}

void Dz1JsonSpecEntry_dump(Dz1JsonSpecEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("gen = %p\n"), p->gen);
		Dz1Thread_tprintf(tab, Dz1T("del = %p\n"), p->del);
		Dz1Thread_tprintf(tab, Dz1T("data.")); Dz1JsonSpecData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1JsonSpecEntry_cmp(Dz1JsonSpecEntry *a, Dz1JsonSpecEntry *b)
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
// Dz1JsonSpecEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecList
static Dz1Error Dz1JsonSpecList_add(Dz1JsonSpecList *p, Dz1JsonSpecEntry *data)
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

static bool_t Dz1JsonSpecList_remove(Dz1JsonSpecList *p, Dz1JsonSpecEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1JsonSpecEntry *Dz1JsonSpecList_extract(Dz1JsonSpecList *p, Dz1JsonSpecEntry *key)
{
	return (Dz1JsonSpecEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1JsonSpecListMkArrArg
{
	Dz1JsonSpecEntry **arr;
	unsigned int idx;
} Dz1JsonSpecListMkArrArg;

static Dz1Error _Dz1JsonSpecList_get_array(void *ptr, Dz1JsonSpecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonSpecListMkArrArg *arg = (Dz1JsonSpecListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1JsonSpecEntry **Dz1JsonSpecList_get_array(Dz1JsonSpecList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1JsonSpecEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1JsonSpecEntry **)Dz1Calloc(sizeof(Dz1JsonSpecEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonSpecListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1JsonSpecList_get_array, (void *)&arg);
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

static Dz1Error Dz1JsonSpecList_travelForward(Dz1JsonSpecList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1JsonSpecList_travelBackward(Dz1JsonSpecList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1JsonSpecEntry *Dz1JsonSpecList_find(Dz1JsonSpecList *p, Dz1JsonSpecEntry *key)
{
	return (Dz1JsonSpecEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1JsonSpecList_count(Dz1JsonSpecList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1JsonSpecList *Dz1JsonSpecList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecList *ret = (Dz1JsonSpecList *)Dz1Calloc(sizeof(Dz1JsonSpecList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpecList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1JsonSpecEntry_cmp,
				(Dz1DelFunc)Dz1JsonSpecEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1JsonSpecList_count;
			ret->travel = Dz1JsonSpecList_travelForward;
			ret->travelForward = Dz1JsonSpecList_travelForward;
			ret->travelBackward = Dz1JsonSpecList_travelBackward;
			ret->get_array = Dz1JsonSpecList_get_array;
			ret->add = Dz1JsonSpecList_add;
			ret->remove = Dz1JsonSpecList_remove;
			ret->find = Dz1JsonSpecList_find;
			ret->extract = Dz1JsonSpecList_extract;
			ret->cmp = Dz1JsonSpecEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1JsonSpecList_clone(void *ptr, Dz1JsonSpecEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1JsonSpecList *p = (Dz1JsonSpecList *)ptr;
	Dz1JsonSpecEntry *cloned = Dz1JsonSpecEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1JsonSpecList *Dz1JsonSpecList_clone(Dz1JsonSpecList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpecList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1JsonSpecList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpecList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1JsonSpecList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpecList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonSpecList_purge(Dz1JsonSpecList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1JsonSpecList_del(Dz1JsonSpecList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1JsonSpecList_dump(void *ptr, Dz1JsonSpecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1JsonSpecEntry_dump(p, tab);
	return err;
}

void Dz1JsonSpecList_dump(Dz1JsonSpecList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1JsonSpecList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonSpecList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec
Dz1JsonSpec *Dz1JsonSpec_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonSpec *__internal_ret = (Dz1JsonSpec *)Dz1Calloc(sizeof(Dz1JsonSpec), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->types = Dz1JsonSpecList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonSpec_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonSpec_purge(Dz1JsonSpec *p)
{
	if (p == NULL) return;
	Dz1JsonSpecList_del(p->types);
}

void Dz1JsonSpec_del(Dz1JsonSpec *p)
{
	if (p == NULL) return;
	Dz1JsonSpec_purge(p);
	Dz1Free(p);
}

void Dz1JsonSpec_dump(Dz1JsonSpec *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("types = ")); Dz1JsonSpecList_dump(p->types, tab); 
	}
}
// Dz1JsonSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonVarBind
Dz1JsonVarBind *Dz1JsonVarBind_new(Dz1JsonSpecChild *id/*_ref*/, 
								   Dz1JsonSpecEntry *type/*_ref*/, 
								   void *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1JsonVarBind *__internal_ret = (Dz1JsonVarBind *)Dz1Calloc(sizeof(Dz1JsonVarBind), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1JsonVarBind_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		__internal_ret->type = type;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1JsonVarBind_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1JsonVarBind_dump(Dz1JsonVarBind *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1JsonSpecChild_dump(p->id, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("type = ")); Dz1JsonSpecEntry_dump(p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data = %p\n"), p->data);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1JsonVarBind
////////////////////////////////////////////////////////////////////////////////

