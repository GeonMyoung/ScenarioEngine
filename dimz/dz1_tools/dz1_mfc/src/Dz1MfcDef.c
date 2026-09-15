////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1MfcDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcKeyboardEvent
static struct Dz1MfcKeyboardEventMapA
{
	str_t str;
	Dz1MfcKeyboardEvent v;
} Dz1MfcKeyboardEventMapA[] =
{
	{ (char *)"Pressed", Dz1MfcKeyboardEvent_Pressed },
	{ (char *)"Repeated", Dz1MfcKeyboardEvent_Repeated },
	{ (char *)"Released", Dz1MfcKeyboardEvent_Released },
	{ NULL, Dz1MfcKeyboardEvent_max }
};

str_t Dz1MfcKeyboardEventStrA(Dz1MfcKeyboardEvent v)
{
	struct Dz1MfcKeyboardEventMapA *i = NULL;
	for (i = Dz1MfcKeyboardEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcKeyboardEvent Dz1MfcKeyboardEventFromStrA(str_t str)
{
	struct Dz1MfcKeyboardEventMapA *i = NULL;
	for (i = Dz1MfcKeyboardEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcKeyboardEvent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MfcKeyboardEventMapW
{
	wstr_t str;
	Dz1MfcKeyboardEvent v;
} Dz1MfcKeyboardEventMapW[] =
{
	{ (wchar_t *)L"Pressed", Dz1MfcKeyboardEvent_Pressed },
	{ (wchar_t *)L"Repeated", Dz1MfcKeyboardEvent_Repeated },
	{ (wchar_t *)L"Released", Dz1MfcKeyboardEvent_Released },
	{ NULL, Dz1MfcKeyboardEvent_max }
};

wstr_t Dz1MfcKeyboardEventStrW(Dz1MfcKeyboardEvent v)
{
	struct Dz1MfcKeyboardEventMapW *i = NULL;
	for (i = Dz1MfcKeyboardEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcKeyboardEvent Dz1MfcKeyboardEventFromStrW(wstr_t str)
{
	struct Dz1MfcKeyboardEventMapW *i = NULL;
	for (i = Dz1MfcKeyboardEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcKeyboardEvent_max;
}
#endif // UNIX_SYSTEM

Dz1MfcKeyboardEvent *Dz1MfcKeyboardEvent_new(Dz1MfcKeyboardEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcKeyboardEvent *__internal_ret = (Dz1MfcKeyboardEvent *)Dz1Calloc(sizeof(Dz1MfcKeyboardEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

int Dz1MfcKeyboardEvent_cmp(Dz1MfcKeyboardEvent *a, Dz1MfcKeyboardEvent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// Dz1MfcKeyboardEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcKeyboardKeyEntry
Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyEntry_new(Dz1MfcKeyboardEvent event, 
												   bool_t isExtKey, 
												   u32_t code, 
												   s32_t cmd, 
												   s32_t arg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcKeyboardKeyEntry *__internal_ret = (Dz1MfcKeyboardKeyEntry *)Dz1Calloc(sizeof(Dz1MfcKeyboardKeyEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcKeyboardKeyEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->event = event;
		__internal_ret->isExtKey = isExtKey;
		__internal_ret->code = code;
		__internal_ret->cmd = cmd;
		__internal_ret->arg = arg;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcKeyboardKeyEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcKeyboardKeyEntry_copy(Dz1MfcKeyboardKeyEntry *dst, Dz1MfcKeyboardKeyEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->event = src->event;
		dst->isExtKey = src->isExtKey;
		dst->code = src->code;
		dst->cmd = src->cmd;
		dst->arg = src->arg;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyEntry_clone(Dz1MfcKeyboardKeyEntry *src, Dz1Error *err)
{
	Dz1MfcKeyboardKeyEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcKeyboardKeyEntry *)Dz1Calloc(sizeof(Dz1MfcKeyboardKeyEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcKeyboardKeyEntry_delAndSetNull, (void *)&dst);
		if (Dz1MfcKeyboardKeyEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcKeyboardKeyEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcKeyboardKeyEntry_purge(Dz1MfcKeyboardKeyEntry *p)
{
	if (p == NULL) return;
}

void Dz1MfcKeyboardKeyEntry_del(Dz1MfcKeyboardKeyEntry *p)
{
	if (p == NULL) return;
	Dz1MfcKeyboardKeyEntry_purge(p);
	Dz1Free(p);
}

void Dz1MfcKeyboardKeyEntry_dump(Dz1MfcKeyboardKeyEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("event = %s(%d)\n"), Dz1MfcKeyboardEventStr(p->event), p->event);
		Dz1Thread_tprintf(tab, Dz1T("isExtKey = ")); Dz1Bool_dump(&p->isExtKey, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = ")); Dz1u32_dump(&p->code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("cmd = ")); Dz1s32_dump(&p->cmd, tab); 
		Dz1Thread_tprintf(tab, Dz1T("arg = ")); Dz1s32_dump(&p->arg, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcKeyboardKeyEntry_cmp(Dz1MfcKeyboardKeyEntry *a, Dz1MfcKeyboardKeyEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = (int)(a->event - b->event)) != 0) { }
	else if ((ret = Dz1Bool_cmp(&a->isExtKey, &b->isExtKey)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->code, &b->code)) != 0) { }
	return ret;
}
// Dz1MfcKeyboardKeyEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcKeyboardKeyList
static Dz1Error Dz1MfcKeyboardKeyList_add(Dz1MfcKeyboardKeyList *p, Dz1MfcKeyboardKeyEntry *data)
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

static bool_t Dz1MfcKeyboardKeyList_remove(Dz1MfcKeyboardKeyList *p, Dz1MfcKeyboardKeyEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyList_extract(Dz1MfcKeyboardKeyList *p, Dz1MfcKeyboardKeyEntry *key)
{
	return (Dz1MfcKeyboardKeyEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcKeyboardKeyListMkArrArg
{
	Dz1MfcKeyboardKeyEntry **arr;
	unsigned int idx;
} Dz1MfcKeyboardKeyListMkArrArg;

static Dz1Error _Dz1MfcKeyboardKeyList_get_array(void *ptr, Dz1MfcKeyboardKeyEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcKeyboardKeyListMkArrArg *arg = (Dz1MfcKeyboardKeyListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcKeyboardKeyEntry **Dz1MfcKeyboardKeyList_get_array(Dz1MfcKeyboardKeyList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcKeyboardKeyEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcKeyboardKeyEntry **)Dz1Calloc(sizeof(Dz1MfcKeyboardKeyEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcKeyboardKeyListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcKeyboardKeyList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcKeyboardKeyList_travelForward(Dz1MfcKeyboardKeyList *p, Dz1Error (*func)(void *ptr, Dz1MfcKeyboardKeyEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcKeyboardKeyList_travelBackward(Dz1MfcKeyboardKeyList *p, Dz1Error (*func)(void *ptr, Dz1MfcKeyboardKeyEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyList_find(Dz1MfcKeyboardKeyList *p, Dz1MfcKeyboardKeyEntry *key)
{
	return (Dz1MfcKeyboardKeyEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcKeyboardKeyList_count(Dz1MfcKeyboardKeyList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcKeyboardKeyList *Dz1MfcKeyboardKeyList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcKeyboardKeyList *ret = (Dz1MfcKeyboardKeyList *)Dz1Calloc(sizeof(Dz1MfcKeyboardKeyList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcKeyboardKeyList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcKeyboardKeyEntry_cmp,
				(Dz1DelFunc)Dz1MfcKeyboardKeyEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcKeyboardKeyList_count;
			ret->travel = Dz1MfcKeyboardKeyList_travelForward;
			ret->travelForward = Dz1MfcKeyboardKeyList_travelForward;
			ret->travelBackward = Dz1MfcKeyboardKeyList_travelBackward;
			ret->get_array = Dz1MfcKeyboardKeyList_get_array;
			ret->add = Dz1MfcKeyboardKeyList_add;
			ret->remove = Dz1MfcKeyboardKeyList_remove;
			ret->find = Dz1MfcKeyboardKeyList_find;
			ret->extract = Dz1MfcKeyboardKeyList_extract;
			ret->cmp = Dz1MfcKeyboardKeyEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcKeyboardKeyList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcKeyboardKeyList_clone(void *ptr, Dz1MfcKeyboardKeyEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcKeyboardKeyList *p = (Dz1MfcKeyboardKeyList *)ptr;
	Dz1MfcKeyboardKeyEntry *cloned = Dz1MfcKeyboardKeyEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcKeyboardKeyList *Dz1MfcKeyboardKeyList_clone(Dz1MfcKeyboardKeyList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcKeyboardKeyList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcKeyboardKeyList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcKeyboardKeyList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcKeyboardKeyList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcKeyboardKeyList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcKeyboardKeyList_purge(Dz1MfcKeyboardKeyList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcKeyboardKeyList_del(Dz1MfcKeyboardKeyList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcKeyboardKeyList_dump(void *ptr, Dz1MfcKeyboardKeyEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcKeyboardKeyEntry_dump(p, tab);
	return err;
}

void Dz1MfcKeyboardKeyList_dump(Dz1MfcKeyboardKeyList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcKeyboardKeyList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcKeyboardKeyList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcLanManPathEntry
Dz1MfcLanManPathEntry *Dz1MfcLanManPathEntry_new(Dz1Str name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcLanManPathEntry *__internal_ret = (Dz1MfcLanManPathEntry *)Dz1Calloc(sizeof(Dz1MfcLanManPathEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcLanManPathEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcLanManPathEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcLanManPathEntry_copy(Dz1MfcLanManPathEntry *dst, Dz1MfcLanManPathEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcLanManPathEntry *Dz1MfcLanManPathEntry_clone(Dz1MfcLanManPathEntry *src, Dz1Error *err)
{
	Dz1MfcLanManPathEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcLanManPathEntry *)Dz1Calloc(sizeof(Dz1MfcLanManPathEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcLanManPathEntry_delAndSetNull, (void *)&dst);
		if (Dz1MfcLanManPathEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcLanManPathEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcLanManPathEntry_purge(Dz1MfcLanManPathEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
}

void Dz1MfcLanManPathEntry_del(Dz1MfcLanManPathEntry *p)
{
	if (p == NULL) return;
	Dz1MfcLanManPathEntry_purge(p);
	Dz1Free(p);
}

void Dz1MfcLanManPathEntry_dump(Dz1MfcLanManPathEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
	}
}
int Dz1MfcLanManPathEntry_cmp(Dz1MfcLanManPathEntry *a, Dz1MfcLanManPathEntry *b)
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
// Dz1MfcLanManPathEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcLanManPathList
static Dz1Error Dz1MfcLanManPathList_add(Dz1MfcLanManPathList *p, Dz1MfcLanManPathEntry *data)
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

static bool_t Dz1MfcLanManPathList_remove(Dz1MfcLanManPathList *p, Dz1MfcLanManPathEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcLanManPathEntry *Dz1MfcLanManPathList_extract(Dz1MfcLanManPathList *p, Dz1MfcLanManPathEntry *key)
{
	return (Dz1MfcLanManPathEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcLanManPathListMkArrArg
{
	Dz1MfcLanManPathEntry **arr;
	unsigned int idx;
} Dz1MfcLanManPathListMkArrArg;

static Dz1Error _Dz1MfcLanManPathList_get_array(void *ptr, Dz1MfcLanManPathEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcLanManPathListMkArrArg *arg = (Dz1MfcLanManPathListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcLanManPathEntry **Dz1MfcLanManPathList_get_array(Dz1MfcLanManPathList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcLanManPathEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcLanManPathEntry **)Dz1Calloc(sizeof(Dz1MfcLanManPathEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcLanManPathListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcLanManPathList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcLanManPathList_travelForward(Dz1MfcLanManPathList *p, Dz1Error (*func)(void *ptr, Dz1MfcLanManPathEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcLanManPathList_travelBackward(Dz1MfcLanManPathList *p, Dz1Error (*func)(void *ptr, Dz1MfcLanManPathEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcLanManPathEntry *Dz1MfcLanManPathList_find(Dz1MfcLanManPathList *p, Dz1MfcLanManPathEntry *key)
{
	return (Dz1MfcLanManPathEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcLanManPathList_count(Dz1MfcLanManPathList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcLanManPathList *Dz1MfcLanManPathList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcLanManPathList *ret = (Dz1MfcLanManPathList *)Dz1Calloc(sizeof(Dz1MfcLanManPathList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcLanManPathList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcLanManPathEntry_cmp,
				(Dz1DelFunc)Dz1MfcLanManPathEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcLanManPathList_count;
			ret->travel = Dz1MfcLanManPathList_travelForward;
			ret->travelForward = Dz1MfcLanManPathList_travelForward;
			ret->travelBackward = Dz1MfcLanManPathList_travelBackward;
			ret->get_array = Dz1MfcLanManPathList_get_array;
			ret->add = Dz1MfcLanManPathList_add;
			ret->remove = Dz1MfcLanManPathList_remove;
			ret->find = Dz1MfcLanManPathList_find;
			ret->extract = Dz1MfcLanManPathList_extract;
			ret->cmp = Dz1MfcLanManPathEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcLanManPathList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcLanManPathList_clone(void *ptr, Dz1MfcLanManPathEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcLanManPathList *p = (Dz1MfcLanManPathList *)ptr;
	Dz1MfcLanManPathEntry *cloned = Dz1MfcLanManPathEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcLanManPathList *Dz1MfcLanManPathList_clone(Dz1MfcLanManPathList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcLanManPathList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcLanManPathList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcLanManPathList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcLanManPathList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcLanManPathList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcLanManPathList_purge(Dz1MfcLanManPathList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcLanManPathList_del(Dz1MfcLanManPathList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcLanManPathList_dump(void *ptr, Dz1MfcLanManPathEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcLanManPathEntry_dump(p, tab);
	return err;
}

void Dz1MfcLanManPathList_dump(Dz1MfcLanManPathList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcLanManPathList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcLanManPathList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterValueRangeSigned
Dz1MfcListFilterValueRangeSigned *Dz1MfcListFilterValueRangeSigned_new(s64_t lowValue, 
																	   s64_t highValue, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcListFilterValueRangeSigned *__internal_ret = (Dz1MfcListFilterValueRangeSigned *)Dz1Calloc(sizeof(Dz1MfcListFilterValueRangeSigned), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterValueRangeSigned_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->lowValue = lowValue;
		__internal_ret->highValue = highValue;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterValueRangeSigned_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcListFilterValueRangeSigned_copy(Dz1MfcListFilterValueRangeSigned *dst, Dz1MfcListFilterValueRangeSigned *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->lowValue = src->lowValue;
		dst->highValue = src->highValue;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcListFilterValueRangeSigned *Dz1MfcListFilterValueRangeSigned_clone(Dz1MfcListFilterValueRangeSigned *src, Dz1Error *err)
{
	Dz1MfcListFilterValueRangeSigned *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcListFilterValueRangeSigned *)Dz1Calloc(sizeof(Dz1MfcListFilterValueRangeSigned), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterValueRangeSigned_delAndSetNull, (void *)&dst);
		if (Dz1MfcListFilterValueRangeSigned_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterValueRangeSigned_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcListFilterValueRangeSigned_purge(Dz1MfcListFilterValueRangeSigned *p)
{
	if (p == NULL) return;
}

void Dz1MfcListFilterValueRangeSigned_del(Dz1MfcListFilterValueRangeSigned *p)
{
	if (p == NULL) return;
	Dz1MfcListFilterValueRangeSigned_purge(p);
	Dz1Free(p);
}

void Dz1MfcListFilterValueRangeSigned_dump(Dz1MfcListFilterValueRangeSigned *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("lowValue = ")); Dz1s64_dump(&p->lowValue, tab); 
		Dz1Thread_tprintf(tab, Dz1T("highValue = ")); Dz1s64_dump(&p->highValue, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcListFilterValueRangeSigned
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterValueRangeUnsigned
Dz1MfcListFilterValueRangeUnsigned *Dz1MfcListFilterValueRangeUnsigned_new(u64_t lowValue, 
																		   u64_t highValue, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcListFilterValueRangeUnsigned *__internal_ret = (Dz1MfcListFilterValueRangeUnsigned *)Dz1Calloc(sizeof(Dz1MfcListFilterValueRangeUnsigned), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterValueRangeUnsigned_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->lowValue = lowValue;
		__internal_ret->highValue = highValue;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterValueRangeUnsigned_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcListFilterValueRangeUnsigned_copy(Dz1MfcListFilterValueRangeUnsigned *dst, Dz1MfcListFilterValueRangeUnsigned *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->lowValue = src->lowValue;
		dst->highValue = src->highValue;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcListFilterValueRangeUnsigned *Dz1MfcListFilterValueRangeUnsigned_clone(Dz1MfcListFilterValueRangeUnsigned *src, Dz1Error *err)
{
	Dz1MfcListFilterValueRangeUnsigned *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcListFilterValueRangeUnsigned *)Dz1Calloc(sizeof(Dz1MfcListFilterValueRangeUnsigned), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterValueRangeUnsigned_delAndSetNull, (void *)&dst);
		if (Dz1MfcListFilterValueRangeUnsigned_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterValueRangeUnsigned_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcListFilterValueRangeUnsigned_purge(Dz1MfcListFilterValueRangeUnsigned *p)
{
	if (p == NULL) return;
}

void Dz1MfcListFilterValueRangeUnsigned_del(Dz1MfcListFilterValueRangeUnsigned *p)
{
	if (p == NULL) return;
	Dz1MfcListFilterValueRangeUnsigned_purge(p);
	Dz1Free(p);
}

void Dz1MfcListFilterValueRangeUnsigned_dump(Dz1MfcListFilterValueRangeUnsigned *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("lowValue = ")); Dz1u64_dump(&p->lowValue, tab); 
		Dz1Thread_tprintf(tab, Dz1T("highValue = ")); Dz1u64_dump(&p->highValue, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcListFilterValueRangeUnsigned
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterValuePresent
static struct Dz1MfcListFilterValuePresentMapA
{
	str_t str;
	Dz1MfcListFilterValuePresent v;
} Dz1MfcListFilterValuePresentMapA[] =
{
	{ (char *)"sNum", Dz1MfcListFilterValuePresent_sNum },
	{ (char *)"uNum", Dz1MfcListFilterValuePresent_uNum },
	{ (char *)"sRange", Dz1MfcListFilterValuePresent_sRange },
	{ (char *)"uRange", Dz1MfcListFilterValuePresent_uRange },
	{ (char *)"txtValue", Dz1MfcListFilterValuePresent_txtValue },
	{ (char *)"txtList", Dz1MfcListFilterValuePresent_txtList },
	{ NULL, Dz1MfcListFilterValuePresent_max }
};

str_t Dz1MfcListFilterValuePresentStrA(Dz1MfcListFilterValuePresent v)
{
	struct Dz1MfcListFilterValuePresentMapA *i = NULL;
	for (i = Dz1MfcListFilterValuePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcListFilterValuePresent Dz1MfcListFilterValuePresentFromStrA(str_t str)
{
	struct Dz1MfcListFilterValuePresentMapA *i = NULL;
	for (i = Dz1MfcListFilterValuePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcListFilterValuePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MfcListFilterValuePresentMapW
{
	wstr_t str;
	Dz1MfcListFilterValuePresent v;
} Dz1MfcListFilterValuePresentMapW[] =
{
	{ (wchar_t *)L"sNum", Dz1MfcListFilterValuePresent_sNum },
	{ (wchar_t *)L"uNum", Dz1MfcListFilterValuePresent_uNum },
	{ (wchar_t *)L"sRange", Dz1MfcListFilterValuePresent_sRange },
	{ (wchar_t *)L"uRange", Dz1MfcListFilterValuePresent_uRange },
	{ (wchar_t *)L"txtValue", Dz1MfcListFilterValuePresent_txtValue },
	{ (wchar_t *)L"txtList", Dz1MfcListFilterValuePresent_txtList },
	{ NULL, Dz1MfcListFilterValuePresent_max }
};

wstr_t Dz1MfcListFilterValuePresentStrW(Dz1MfcListFilterValuePresent v)
{
	struct Dz1MfcListFilterValuePresentMapW *i = NULL;
	for (i = Dz1MfcListFilterValuePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcListFilterValuePresent Dz1MfcListFilterValuePresentFromStrW(wstr_t str)
{
	struct Dz1MfcListFilterValuePresentMapW *i = NULL;
	for (i = Dz1MfcListFilterValuePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcListFilterValuePresent_max;
}
#endif // UNIX_SYSTEM

Dz1MfcListFilterValuePresent *Dz1MfcListFilterValuePresent_new(Dz1MfcListFilterValuePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcListFilterValuePresent *__internal_ret = (Dz1MfcListFilterValuePresent *)Dz1Calloc(sizeof(Dz1MfcListFilterValuePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1MfcListFilterValuePresent_dump(Dz1MfcListFilterValuePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1MfcListFilterValuePresentStr(*v));
}
// Dz1MfcListFilterValuePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterValue
Dz1MfcListFilterValue *Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcListFilterValue *ret = (Dz1MfcListFilterValue *)Dz1Calloc(sizeof(Dz1MfcListFilterValue), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterValue_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1MfcListFilterValuePresent_sNum:
			// _U_prim_clone
			if (ptr != NULL) ret->x.sNum = *(s64_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcListFilterValuePresent_uNum:
			// _U_prim_clone
			if (ptr != NULL) ret->x.uNum = *(u64_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcListFilterValuePresent_sRange:
			// _U_cst_clone
			if (ptr != NULL) ret->x.sRange = (Dz1MfcListFilterValueRangeSigned *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcListFilterValuePresent_uRange:
			// _U_cst_clone
			if (ptr != NULL) ret->x.uRange = (Dz1MfcListFilterValueRangeUnsigned *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcListFilterValuePresent_txtValue:
			// _U_prim_clone
			if (ptr && (ret->x.txtValue = Dz1Str_clone((Dz1Str)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1MfcListFilterValuePresent_txtList:
			// _U_imp_clone
			if (ptr != NULL) ret->x.txtList = (Dz1LogicStringArr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcListFilterValuePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterValue_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1MfcListFilterValue_copy(Dz1MfcListFilterValue *ret, Dz1MfcListFilterValue *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1MfcListFilterValuePresent_sNum:
			// _U_prim_clone
			ret->x.sNum = src->x.sNum;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcListFilterValuePresent_uNum:
			// _U_prim_clone
			ret->x.uNum = src->x.uNum;
			ERR_CLEAR(errp);
			break;
		case Dz1MfcListFilterValuePresent_sRange:
			// _U_cst_clone
			if (src->x.sRange && (ret->x.sRange = Dz1MfcListFilterValueRangeSigned_clone(src->x.sRange, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1MfcListFilterValuePresent_uRange:
			// _U_cst_clone
			if (src->x.uRange && (ret->x.uRange = Dz1MfcListFilterValueRangeUnsigned_clone(src->x.uRange, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1MfcListFilterValuePresent_txtValue:
			// _U_prim_clone
			if (src->x.txtValue && (ret->x.txtValue = Dz1Str_clone(src->x.txtValue, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1MfcListFilterValuePresent_txtList:
			// _U_imp_clone
			if (src->x.txtList && (ret->x.txtList = Dz1LogicStringArr_clone(src->x.txtList, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcListFilterValue *Dz1MfcListFilterValue_clone(Dz1MfcListFilterValue *src, Dz1Error *err)
{
	Dz1MfcListFilterValue *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1MfcListFilterValue *)Dz1Calloc(sizeof(Dz1MfcListFilterValue), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterValue_delAndSetNull, (void *)&ret);
		if (Dz1MfcListFilterValue_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterValue_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcListFilterValue_purge(Dz1MfcListFilterValue *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1MfcListFilterValuePresent_sNum:
		break;
	case Dz1MfcListFilterValuePresent_uNum:
		break;
	case Dz1MfcListFilterValuePresent_sRange:
		Dz1MfcListFilterValueRangeSigned_del(p->x.sRange);
		break;
	case Dz1MfcListFilterValuePresent_uRange:
		Dz1MfcListFilterValueRangeUnsigned_del(p->x.uRange);
		break;
	case Dz1MfcListFilterValuePresent_txtValue:
		Dz1Str_del(p->x.txtValue);
		break;
	case Dz1MfcListFilterValuePresent_txtList:
		Dz1LogicStringArr_del(p->x.txtList);
		break;
	default:
		break;
	}
}

void Dz1MfcListFilterValue_del(Dz1MfcListFilterValue *p)
{
	if (!p) return;
	Dz1MfcListFilterValue_purge(p);
	Dz1Free(p);
}

void Dz1MfcListFilterValue_dump(Dz1MfcListFilterValue *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1MfcListFilterValuePresent_sNum:
		Dz1Thread_printf(Dz1T("sNum = ")); Dz1s64_dump(&p->x.sNum, tab); 
		break;
	case Dz1MfcListFilterValuePresent_uNum:
		Dz1Thread_printf(Dz1T("uNum = ")); Dz1u64_dump(&p->x.uNum, tab); 
		break;
	case Dz1MfcListFilterValuePresent_sRange:
		Dz1Thread_printf(Dz1T("sRange = ")); Dz1MfcListFilterValueRangeSigned_dump(p->x.sRange, tab); 
		break;
	case Dz1MfcListFilterValuePresent_uRange:
		Dz1Thread_printf(Dz1T("uRange = ")); Dz1MfcListFilterValueRangeUnsigned_dump(p->x.uRange, tab); 
		break;
	case Dz1MfcListFilterValuePresent_txtValue:
		Dz1Thread_printf(Dz1T("txtValue = ")); Dz1Str_dump(p->x.txtValue, tab); 
		break;
	case Dz1MfcListFilterValuePresent_txtList:
		Dz1Thread_printf(Dz1T("txtList = ")); Dz1LogicStringArr_dump(p->x.txtList, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1MfcListFilterValue
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterEntry
Dz1MfcListFilterEntry *Dz1MfcListFilterEntry_new(s32_t col, 
												 Dz1LogicMatchType mode, 
												 Dz1MfcListFilterValue *value, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcListFilterEntry *__internal_ret = (Dz1MfcListFilterEntry *)Dz1Calloc(sizeof(Dz1MfcListFilterEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->col = col;
		__internal_ret->mode = mode;
		__internal_ret->value = value;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcListFilterEntry_copy(Dz1MfcListFilterEntry *dst, Dz1MfcListFilterEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->value && (dst->value = Dz1MfcListFilterValue_clone(src->value, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->col = src->col;
		dst->mode = src->mode;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcListFilterEntry *Dz1MfcListFilterEntry_clone(Dz1MfcListFilterEntry *src, Dz1Error *err)
{
	Dz1MfcListFilterEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcListFilterEntry *)Dz1Calloc(sizeof(Dz1MfcListFilterEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterEntry_delAndSetNull, (void *)&dst);
		if (Dz1MfcListFilterEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcListFilterEntry_purge(Dz1MfcListFilterEntry *p)
{
	if (p == NULL) return;
	Dz1MfcListFilterValue_del(p->value);
}

void Dz1MfcListFilterEntry_del(Dz1MfcListFilterEntry *p)
{
	if (p == NULL) return;
	Dz1MfcListFilterEntry_purge(p);
	Dz1Free(p);
}

void Dz1MfcListFilterEntry_dump(Dz1MfcListFilterEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("col = ")); Dz1s32_dump(&p->col, tab); 
		Dz1Thread_tprintf(tab, Dz1T("mode = %s(%d)\n"), Dz1LogicMatchTypeStr(p->mode), p->mode);
		Dz1Thread_tprintf(tab, Dz1T("value.")); Dz1MfcListFilterValue_dump(p->value, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcListFilterEntry_cmp(Dz1MfcListFilterEntry *a, Dz1MfcListFilterEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1s32_cmp(&a->col, &b->col)) != 0) { }
	return ret;
}
// Dz1MfcListFilterEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterList
static Dz1Error Dz1MfcListFilterList_add(Dz1MfcListFilterList *p, Dz1MfcListFilterEntry *data)
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

static bool_t Dz1MfcListFilterList_remove(Dz1MfcListFilterList *p, Dz1MfcListFilterEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcListFilterEntry *Dz1MfcListFilterList_extract(Dz1MfcListFilterList *p, Dz1MfcListFilterEntry *key)
{
	return (Dz1MfcListFilterEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcListFilterListMkArrArg
{
	Dz1MfcListFilterEntry **arr;
	unsigned int idx;
} Dz1MfcListFilterListMkArrArg;

static Dz1Error _Dz1MfcListFilterList_get_array(void *ptr, Dz1MfcListFilterEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcListFilterListMkArrArg *arg = (Dz1MfcListFilterListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcListFilterEntry **Dz1MfcListFilterList_get_array(Dz1MfcListFilterList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcListFilterEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcListFilterEntry **)Dz1Calloc(sizeof(Dz1MfcListFilterEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcListFilterListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcListFilterList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcListFilterList_travelForward(Dz1MfcListFilterList *p, Dz1Error (*func)(void *ptr, Dz1MfcListFilterEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcListFilterList_travelBackward(Dz1MfcListFilterList *p, Dz1Error (*func)(void *ptr, Dz1MfcListFilterEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcListFilterEntry *Dz1MfcListFilterList_find(Dz1MfcListFilterList *p, Dz1MfcListFilterEntry *key)
{
	return (Dz1MfcListFilterEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcListFilterList_count(Dz1MfcListFilterList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcListFilterList *Dz1MfcListFilterList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcListFilterList *ret = (Dz1MfcListFilterList *)Dz1Calloc(sizeof(Dz1MfcListFilterList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcListFilterEntry_cmp,
				(Dz1DelFunc)Dz1MfcListFilterEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcListFilterList_count;
			ret->travel = Dz1MfcListFilterList_travelForward;
			ret->travelForward = Dz1MfcListFilterList_travelForward;
			ret->travelBackward = Dz1MfcListFilterList_travelBackward;
			ret->get_array = Dz1MfcListFilterList_get_array;
			ret->add = Dz1MfcListFilterList_add;
			ret->remove = Dz1MfcListFilterList_remove;
			ret->find = Dz1MfcListFilterList_find;
			ret->extract = Dz1MfcListFilterList_extract;
			ret->cmp = Dz1MfcListFilterEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcListFilterList_clone(void *ptr, Dz1MfcListFilterEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcListFilterList *p = (Dz1MfcListFilterList *)ptr;
	Dz1MfcListFilterEntry *cloned = Dz1MfcListFilterEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcListFilterList *Dz1MfcListFilterList_clone(Dz1MfcListFilterList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcListFilterList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcListFilterList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcListFilterList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcListFilterList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcListFilterList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcListFilterList_purge(Dz1MfcListFilterList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcListFilterList_del(Dz1MfcListFilterList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcListFilterList_dump(void *ptr, Dz1MfcListFilterEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcListFilterEntry_dump(p, tab);
	return err;
}

void Dz1MfcListFilterList_dump(Dz1MfcListFilterList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcListFilterList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcListFilterList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcProgInfoArgEntry
Dz1MfcProgInfoArgEntry *Dz1MfcProgInfoArgEntry_new(u32_t idx, Dz1Str str, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcProgInfoArgEntry *__internal_ret = (Dz1MfcProgInfoArgEntry *)Dz1Calloc(sizeof(Dz1MfcProgInfoArgEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcProgInfoArgEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (str && (__internal_ret->str = Dz1Str_clone(str, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->idx = idx;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcProgInfoArgEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcProgInfoArgEntry_copy(Dz1MfcProgInfoArgEntry *dst, Dz1MfcProgInfoArgEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->str && (dst->str = Dz1Str_clone(src->str, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->idx = src->idx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcProgInfoArgEntry *Dz1MfcProgInfoArgEntry_clone(Dz1MfcProgInfoArgEntry *src, Dz1Error *err)
{
	Dz1MfcProgInfoArgEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcProgInfoArgEntry *)Dz1Calloc(sizeof(Dz1MfcProgInfoArgEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcProgInfoArgEntry_delAndSetNull, (void *)&dst);
		if (Dz1MfcProgInfoArgEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcProgInfoArgEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcProgInfoArgEntry_purge(Dz1MfcProgInfoArgEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->str);
}

void Dz1MfcProgInfoArgEntry_del(Dz1MfcProgInfoArgEntry *p)
{
	if (p == NULL) return;
	Dz1MfcProgInfoArgEntry_purge(p);
	Dz1Free(p);
}

void Dz1MfcProgInfoArgEntry_dump(Dz1MfcProgInfoArgEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("idx = ")); Dz1u32_dump(&p->idx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("str = ")); Dz1Str_dump(p->str, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcProgInfoArgEntry_cmp(Dz1MfcProgInfoArgEntry *a, Dz1MfcProgInfoArgEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->idx, &b->idx)) != 0) { }
	return ret;
}
// Dz1MfcProgInfoArgEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcProgInfoArgList
static Dz1Error Dz1MfcProgInfoArgList_add(Dz1MfcProgInfoArgList *p, Dz1MfcProgInfoArgEntry *data)
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

static bool_t Dz1MfcProgInfoArgList_remove(Dz1MfcProgInfoArgList *p, Dz1MfcProgInfoArgEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcProgInfoArgEntry *Dz1MfcProgInfoArgList_extract(Dz1MfcProgInfoArgList *p, Dz1MfcProgInfoArgEntry *key)
{
	return (Dz1MfcProgInfoArgEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcProgInfoArgListMkArrArg
{
	Dz1MfcProgInfoArgEntry **arr;
	unsigned int idx;
} Dz1MfcProgInfoArgListMkArrArg;

static Dz1Error _Dz1MfcProgInfoArgList_get_array(void *ptr, Dz1MfcProgInfoArgEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcProgInfoArgListMkArrArg *arg = (Dz1MfcProgInfoArgListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcProgInfoArgEntry **Dz1MfcProgInfoArgList_get_array(Dz1MfcProgInfoArgList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcProgInfoArgEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcProgInfoArgEntry **)Dz1Calloc(sizeof(Dz1MfcProgInfoArgEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcProgInfoArgListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcProgInfoArgList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcProgInfoArgList_travelForward(Dz1MfcProgInfoArgList *p, Dz1Error (*func)(void *ptr, Dz1MfcProgInfoArgEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcProgInfoArgList_travelBackward(Dz1MfcProgInfoArgList *p, Dz1Error (*func)(void *ptr, Dz1MfcProgInfoArgEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcProgInfoArgEntry *Dz1MfcProgInfoArgList_find(Dz1MfcProgInfoArgList *p, Dz1MfcProgInfoArgEntry *key)
{
	return (Dz1MfcProgInfoArgEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcProgInfoArgList_count(Dz1MfcProgInfoArgList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcProgInfoArgList *Dz1MfcProgInfoArgList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcProgInfoArgList *ret = (Dz1MfcProgInfoArgList *)Dz1Calloc(sizeof(Dz1MfcProgInfoArgList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcProgInfoArgList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcProgInfoArgEntry_cmp,
				(Dz1DelFunc)Dz1MfcProgInfoArgEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcProgInfoArgList_count;
			ret->travel = Dz1MfcProgInfoArgList_travelForward;
			ret->travelForward = Dz1MfcProgInfoArgList_travelForward;
			ret->travelBackward = Dz1MfcProgInfoArgList_travelBackward;
			ret->get_array = Dz1MfcProgInfoArgList_get_array;
			ret->add = Dz1MfcProgInfoArgList_add;
			ret->remove = Dz1MfcProgInfoArgList_remove;
			ret->find = Dz1MfcProgInfoArgList_find;
			ret->extract = Dz1MfcProgInfoArgList_extract;
			ret->cmp = Dz1MfcProgInfoArgEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcProgInfoArgList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcProgInfoArgList_clone(void *ptr, Dz1MfcProgInfoArgEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcProgInfoArgList *p = (Dz1MfcProgInfoArgList *)ptr;
	Dz1MfcProgInfoArgEntry *cloned = Dz1MfcProgInfoArgEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcProgInfoArgList *Dz1MfcProgInfoArgList_clone(Dz1MfcProgInfoArgList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcProgInfoArgList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcProgInfoArgList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcProgInfoArgList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcProgInfoArgList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcProgInfoArgList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcProgInfoArgList_purge(Dz1MfcProgInfoArgList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcProgInfoArgList_del(Dz1MfcProgInfoArgList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcProgInfoArgList_dump(void *ptr, Dz1MfcProgInfoArgEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcProgInfoArgEntry_dump(p, tab);
	return err;
}

void Dz1MfcProgInfoArgList_dump(Dz1MfcProgInfoArgList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcProgInfoArgList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcProgInfoArgList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcProgInfo
Dz1MfcProgInfo *Dz1MfcProgInfo_new(Dz1Str cmd_line, 
								   Dz1Str path_name_ext, 
								   Dz1Str path, 
								   Dz1Str name_ext, 
								   Dz1Str name, 
								   Dz1Str ext, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcProgInfo *__internal_ret = (Dz1MfcProgInfo *)Dz1Calloc(sizeof(Dz1MfcProgInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcProgInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (cmd_line && (__internal_ret->cmd_line = Dz1Str_clone(cmd_line, errp)) == NULL) ERR_OUT(errp);
		else if (path_name_ext && (__internal_ret->path_name_ext = Dz1Str_clone(path_name_ext, errp)) == NULL) ERR_OUT(errp);
		else if (path && (__internal_ret->path = Dz1Str_clone(path, errp)) == NULL) ERR_OUT(errp);
		else if (name_ext && (__internal_ret->name_ext = Dz1Str_clone(name_ext, errp)) == NULL) ERR_OUT(errp);
		else if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if (ext && (__internal_ret->ext = Dz1Str_clone(ext, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->args = Dz1MfcProgInfoArgList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcProgInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcProgInfo_copy(Dz1MfcProgInfo *dst, Dz1MfcProgInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->cmd_line && (dst->cmd_line = Dz1Str_clone(src->cmd_line, errp)) == NULL) ERR_OUT(errp);
	else if (src->path_name_ext && (dst->path_name_ext = Dz1Str_clone(src->path_name_ext, errp)) == NULL) ERR_OUT(errp);
	else if (src->path && (dst->path = Dz1Str_clone(src->path, errp)) == NULL) ERR_OUT(errp);
	else if (src->name_ext && (dst->name_ext = Dz1Str_clone(src->name_ext, errp)) == NULL) ERR_OUT(errp);
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->ext && (dst->ext = Dz1Str_clone(src->ext, errp)) == NULL) ERR_OUT(errp);
	else if (src->args && (dst->args = Dz1MfcProgInfoArgList_clone(src->args, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcProgInfo *Dz1MfcProgInfo_clone(Dz1MfcProgInfo *src, Dz1Error *err)
{
	Dz1MfcProgInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcProgInfo *)Dz1Calloc(sizeof(Dz1MfcProgInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcProgInfo_delAndSetNull, (void *)&dst);
		if (Dz1MfcProgInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcProgInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcProgInfo_purge(Dz1MfcProgInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->cmd_line);
	Dz1Str_del(p->path_name_ext);
	Dz1Str_del(p->path);
	Dz1Str_del(p->name_ext);
	Dz1Str_del(p->name);
	Dz1Str_del(p->ext);
	Dz1MfcProgInfoArgList_del(p->args);
}

void Dz1MfcProgInfo_del(Dz1MfcProgInfo *p)
{
	if (p == NULL) return;
	Dz1MfcProgInfo_purge(p);
	Dz1Free(p);
}

void Dz1MfcProgInfo_dump(Dz1MfcProgInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cmd_line = ")); Dz1Str_dump(p->cmd_line, tab); 
		Dz1Thread_tprintf(tab, Dz1T("path_name_ext = ")); Dz1Str_dump(p->path_name_ext, tab); 
		Dz1Thread_tprintf(tab, Dz1T("path = ")); Dz1Str_dump(p->path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("name_ext = ")); Dz1Str_dump(p->name_ext, tab); 
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ext = ")); Dz1Str_dump(p->ext, tab); 
		Dz1Thread_tprintf(tab, Dz1T("args = ")); Dz1MfcProgInfoArgList_dump(p->args, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcProgInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DirCatalogACache
static Dz1Error Dz1DirCatalogACache_add(Dz1DirCatalogACache *p, Dz1DirCatalogA *data)
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

static bool_t Dz1DirCatalogACache_remove(Dz1DirCatalogACache *p, Dz1DirCatalogA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1DirCatalogA *Dz1DirCatalogACache_extract(Dz1DirCatalogACache *p, Dz1DirCatalogA *key)
{
	return (Dz1DirCatalogA *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1DirCatalogACacheMkArrArg
{
	Dz1DirCatalogA **arr;
	unsigned int idx;
} Dz1DirCatalogACacheMkArrArg;

static Dz1Error _Dz1DirCatalogACache_get_array(void *ptr, Dz1DirCatalogA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DirCatalogACacheMkArrArg *arg = (Dz1DirCatalogACacheMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1DirCatalogA **Dz1DirCatalogACache_get_array(Dz1DirCatalogACache *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1DirCatalogA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1DirCatalogA **)Dz1Calloc(sizeof(Dz1DirCatalogA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1DirCatalogACacheMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1DirCatalogACache_get_array, (void *)&arg);
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

static Dz1Error Dz1DirCatalogACache_travelForward(Dz1DirCatalogACache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1DirCatalogACache_travelBackward(Dz1DirCatalogACache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1DirCatalogA *Dz1DirCatalogACache_find(Dz1DirCatalogACache *p, Dz1DirCatalogA *key)
{
	return (Dz1DirCatalogA *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1DirCatalogACache_count(Dz1DirCatalogACache *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1DirCatalogACache *Dz1DirCatalogACache_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1DirCatalogACache *ret = (Dz1DirCatalogACache *)Dz1Calloc(sizeof(Dz1DirCatalogACache), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DirCatalogACache_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1DirCatalogA_cmp,
				(Dz1DelFunc)Dz1DirCatalogA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1DirCatalogACache_count;
			ret->travel = Dz1DirCatalogACache_travelForward;
			ret->travelForward = Dz1DirCatalogACache_travelForward;
			ret->travelBackward = Dz1DirCatalogACache_travelBackward;
			ret->get_array = Dz1DirCatalogACache_get_array;
			ret->add = Dz1DirCatalogACache_add;
			ret->remove = Dz1DirCatalogACache_remove;
			ret->find = Dz1DirCatalogACache_find;
			ret->extract = Dz1DirCatalogACache_extract;
			ret->cmp = Dz1DirCatalogA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1DirCatalogACache_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1DirCatalogACache_purge(Dz1DirCatalogACache *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1DirCatalogACache_del(Dz1DirCatalogACache *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

// Dz1DirCatalogACache
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DirCatalogWCache
static Dz1Error Dz1DirCatalogWCache_add(Dz1DirCatalogWCache *p, Dz1DirCatalogW *data)
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

static bool_t Dz1DirCatalogWCache_remove(Dz1DirCatalogWCache *p, Dz1DirCatalogW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1DirCatalogW *Dz1DirCatalogWCache_extract(Dz1DirCatalogWCache *p, Dz1DirCatalogW *key)
{
	return (Dz1DirCatalogW *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1DirCatalogWCacheMkArrArg
{
	Dz1DirCatalogW **arr;
	unsigned int idx;
} Dz1DirCatalogWCacheMkArrArg;

static Dz1Error _Dz1DirCatalogWCache_get_array(void *ptr, Dz1DirCatalogW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DirCatalogWCacheMkArrArg *arg = (Dz1DirCatalogWCacheMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1DirCatalogW **Dz1DirCatalogWCache_get_array(Dz1DirCatalogWCache *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1DirCatalogW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1DirCatalogW **)Dz1Calloc(sizeof(Dz1DirCatalogW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1DirCatalogWCacheMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1DirCatalogWCache_get_array, (void *)&arg);
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

static Dz1Error Dz1DirCatalogWCache_travelForward(Dz1DirCatalogWCache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1DirCatalogWCache_travelBackward(Dz1DirCatalogWCache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1DirCatalogW *Dz1DirCatalogWCache_find(Dz1DirCatalogWCache *p, Dz1DirCatalogW *key)
{
	return (Dz1DirCatalogW *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1DirCatalogWCache_count(Dz1DirCatalogWCache *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1DirCatalogWCache *Dz1DirCatalogWCache_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1DirCatalogWCache *ret = (Dz1DirCatalogWCache *)Dz1Calloc(sizeof(Dz1DirCatalogWCache), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DirCatalogWCache_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1DirCatalogW_cmp,
				(Dz1DelFunc)Dz1DirCatalogW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1DirCatalogWCache_count;
			ret->travel = Dz1DirCatalogWCache_travelForward;
			ret->travelForward = Dz1DirCatalogWCache_travelForward;
			ret->travelBackward = Dz1DirCatalogWCache_travelBackward;
			ret->get_array = Dz1DirCatalogWCache_get_array;
			ret->add = Dz1DirCatalogWCache_add;
			ret->remove = Dz1DirCatalogWCache_remove;
			ret->find = Dz1DirCatalogWCache_find;
			ret->extract = Dz1DirCatalogWCache_extract;
			ret->cmp = Dz1DirCatalogW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1DirCatalogWCache_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1DirCatalogWCache_purge(Dz1DirCatalogWCache *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1DirCatalogWCache_del(Dz1DirCatalogWCache *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

// Dz1DirCatalogWCache
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcPathTreeNodeList
static Dz1Error Dz1MfcPathTreeNodeList_add(Dz1MfcPathTreeNodeList *p, Dz1MfcPathTreeNode *data)
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

static bool_t Dz1MfcPathTreeNodeList_remove(Dz1MfcPathTreeNodeList *p, Dz1MfcPathTreeNode *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcPathTreeNode *Dz1MfcPathTreeNodeList_extract(Dz1MfcPathTreeNodeList *p, Dz1MfcPathTreeNode *key)
{
	return (Dz1MfcPathTreeNode *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcPathTreeNodeListMkArrArg
{
	Dz1MfcPathTreeNode **arr;
	unsigned int idx;
} Dz1MfcPathTreeNodeListMkArrArg;

static Dz1Error _Dz1MfcPathTreeNodeList_get_array(void *ptr, Dz1MfcPathTreeNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcPathTreeNodeListMkArrArg *arg = (Dz1MfcPathTreeNodeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcPathTreeNode **Dz1MfcPathTreeNodeList_get_array(Dz1MfcPathTreeNodeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcPathTreeNode **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcPathTreeNode **)Dz1Calloc(sizeof(Dz1MfcPathTreeNode *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcPathTreeNodeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcPathTreeNodeList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcPathTreeNodeList_travelForward(Dz1MfcPathTreeNodeList *p, Dz1Error (*func)(void *ptr, Dz1MfcPathTreeNode *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcPathTreeNodeList_travelBackward(Dz1MfcPathTreeNodeList *p, Dz1Error (*func)(void *ptr, Dz1MfcPathTreeNode *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcPathTreeNode *Dz1MfcPathTreeNodeList_find(Dz1MfcPathTreeNodeList *p, Dz1MfcPathTreeNode *key)
{
	return (Dz1MfcPathTreeNode *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcPathTreeNodeList_count(Dz1MfcPathTreeNodeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcPathTreeNodeList *Dz1MfcPathTreeNodeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcPathTreeNodeList *ret = (Dz1MfcPathTreeNodeList *)Dz1Calloc(sizeof(Dz1MfcPathTreeNodeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcPathTreeNodeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcPathTreeNode_cmp,
				(Dz1DelFunc)Dz1MfcPathTreeNode_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcPathTreeNodeList_count;
			ret->travel = Dz1MfcPathTreeNodeList_travelForward;
			ret->travelForward = Dz1MfcPathTreeNodeList_travelForward;
			ret->travelBackward = Dz1MfcPathTreeNodeList_travelBackward;
			ret->get_array = Dz1MfcPathTreeNodeList_get_array;
			ret->add = Dz1MfcPathTreeNodeList_add;
			ret->remove = Dz1MfcPathTreeNodeList_remove;
			ret->find = Dz1MfcPathTreeNodeList_find;
			ret->extract = Dz1MfcPathTreeNodeList_extract;
			ret->cmp = Dz1MfcPathTreeNode_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcPathTreeNodeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcPathTreeNodeList_clone(void *ptr, Dz1MfcPathTreeNode *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcPathTreeNodeList *p = (Dz1MfcPathTreeNodeList *)ptr;
	Dz1MfcPathTreeNode *cloned = Dz1MfcPathTreeNode_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcPathTreeNodeList *Dz1MfcPathTreeNodeList_clone(Dz1MfcPathTreeNodeList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcPathTreeNodeList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcPathTreeNodeList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcPathTreeNodeList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcPathTreeNodeList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcPathTreeNodeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcPathTreeNodeList_purge(Dz1MfcPathTreeNodeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcPathTreeNodeList_del(Dz1MfcPathTreeNodeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcPathTreeNodeList_dump(void *ptr, Dz1MfcPathTreeNode *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcPathTreeNode_dump(p, tab);
	return err;
}

void Dz1MfcPathTreeNodeList_dump(Dz1MfcPathTreeNodeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcPathTreeNodeList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcPathTreeNodeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcPathTreeNode
Dz1MfcPathTreeNode *Dz1MfcPathTreeNode_new(Dz1Str name, 
										   Dz1MfcPathTreeNode *parent, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcPathTreeNode *__internal_ret = (Dz1MfcPathTreeNode *)Dz1Calloc(sizeof(Dz1MfcPathTreeNode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcPathTreeNode_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->childs = Dz1MfcPathTreeNodeList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->parent = parent;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcPathTreeNode_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcPathTreeNode_copy(Dz1MfcPathTreeNode *dst, Dz1MfcPathTreeNode *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->parent && (dst->parent = Dz1MfcPathTreeNode_clone(src->parent, errp)) == NULL) ERR_OUT(errp);
	else if (src->childs && (dst->childs = Dz1MfcPathTreeNodeList_clone(src->childs, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcPathTreeNode *Dz1MfcPathTreeNode_clone(Dz1MfcPathTreeNode *src, Dz1Error *err)
{
	Dz1MfcPathTreeNode *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcPathTreeNode *)Dz1Calloc(sizeof(Dz1MfcPathTreeNode), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcPathTreeNode_delAndSetNull, (void *)&dst);
		if (Dz1MfcPathTreeNode_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcPathTreeNode_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcPathTreeNode_purge(Dz1MfcPathTreeNode *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1MfcPathTreeNode_del(p->parent);
	Dz1MfcPathTreeNodeList_del(p->childs);
}

void Dz1MfcPathTreeNode_del(Dz1MfcPathTreeNode *p)
{
	if (p == NULL) return;
	Dz1MfcPathTreeNode_purge(p);
	Dz1Free(p);
}

void Dz1MfcPathTreeNode_dump(Dz1MfcPathTreeNode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1Thread_tprintf(tab, Dz1T("parent = %p\n"), p->parent);
		Dz1Thread_tprintf(tab, Dz1T("childs = ")); Dz1MfcPathTreeNodeList_dump(p->childs, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcPathTreeNode_cmp(Dz1MfcPathTreeNode *a, Dz1MfcPathTreeNode *b)
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
// Dz1MfcPathTreeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlParseEnv
Dz1MfcHtmlParseEnv *Dz1MfcHtmlParseEnv_new(Dz1Str src, Dz1Str lex_ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcHtmlParseEnv *__internal_ret = (Dz1MfcHtmlParseEnv *)Dz1Calloc(sizeof(Dz1MfcHtmlParseEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlParseEnv_delAndSetNull, (void *)&__internal_ret);
		
		if (src && (__internal_ret->src = Dz1Str_clone(src, errp)) == NULL) ERR_OUT(errp);
		else if (lex_ptr && (__internal_ret->lex_ptr = Dz1Str_clone(lex_ptr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlParseEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcHtmlParseEnv_copy(Dz1MfcHtmlParseEnv *dst, Dz1MfcHtmlParseEnv *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->src && (dst->src = Dz1Str_clone(src->src, errp)) == NULL) ERR_OUT(errp);
	else if (src->lex_ptr && (dst->lex_ptr = Dz1Str_clone(src->lex_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcHtmlParseEnv *Dz1MfcHtmlParseEnv_clone(Dz1MfcHtmlParseEnv *src, Dz1Error *err)
{
	Dz1MfcHtmlParseEnv *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcHtmlParseEnv *)Dz1Calloc(sizeof(Dz1MfcHtmlParseEnv), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlParseEnv_delAndSetNull, (void *)&dst);
		if (Dz1MfcHtmlParseEnv_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlParseEnv_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcHtmlParseEnv_purge(Dz1MfcHtmlParseEnv *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->src);
	Dz1Str_del(p->lex_ptr);
}

void Dz1MfcHtmlParseEnv_del(Dz1MfcHtmlParseEnv *p)
{
	if (p == NULL) return;
	Dz1MfcHtmlParseEnv_purge(p);
	Dz1Free(p);
}

void Dz1MfcHtmlParseEnv_dump(Dz1MfcHtmlParseEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("src = ")); Dz1Str_dump(p->src, tab); 
		Dz1Thread_tprintf(tab, Dz1T("lex_ptr = ")); Dz1Str_dump(p->lex_ptr, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcHtmlParseEnv
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlTokenType
static struct Dz1MfcHtmlTokenTypeMapA
{
	str_t str;
	Dz1MfcHtmlTokenType v;
} Dz1MfcHtmlTokenTypeMapA[] =
{
	{ (char *)"undef", Dz1MfcHtmlTokenType_undef },
	{ (char *)"space", Dz1MfcHtmlTokenType_space },
	{ (char *)"new_line", Dz1MfcHtmlTokenType_new_line },
	{ (char *)"start", Dz1MfcHtmlTokenType_start },
	{ (char *)"stop", Dz1MfcHtmlTokenType_stop },
	{ (char *)"term", Dz1MfcHtmlTokenType_term },
	{ (char *)"equal", Dz1MfcHtmlTokenType_equal },
	{ (char *)"string", Dz1MfcHtmlTokenType_string },
	{ (char *)"symbol", Dz1MfcHtmlTokenType_symbol },
	{ NULL, Dz1MfcHtmlTokenType_max }
};

str_t Dz1MfcHtmlTokenTypeStrA(Dz1MfcHtmlTokenType v)
{
	struct Dz1MfcHtmlTokenTypeMapA *i = NULL;
	for (i = Dz1MfcHtmlTokenTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcHtmlTokenType Dz1MfcHtmlTokenTypeFromStrA(str_t str)
{
	struct Dz1MfcHtmlTokenTypeMapA *i = NULL;
	for (i = Dz1MfcHtmlTokenTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcHtmlTokenType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MfcHtmlTokenTypeMapW
{
	wstr_t str;
	Dz1MfcHtmlTokenType v;
} Dz1MfcHtmlTokenTypeMapW[] =
{
	{ (wchar_t *)L"undef", Dz1MfcHtmlTokenType_undef },
	{ (wchar_t *)L"space", Dz1MfcHtmlTokenType_space },
	{ (wchar_t *)L"new_line", Dz1MfcHtmlTokenType_new_line },
	{ (wchar_t *)L"start", Dz1MfcHtmlTokenType_start },
	{ (wchar_t *)L"stop", Dz1MfcHtmlTokenType_stop },
	{ (wchar_t *)L"term", Dz1MfcHtmlTokenType_term },
	{ (wchar_t *)L"equal", Dz1MfcHtmlTokenType_equal },
	{ (wchar_t *)L"string", Dz1MfcHtmlTokenType_string },
	{ (wchar_t *)L"symbol", Dz1MfcHtmlTokenType_symbol },
	{ NULL, Dz1MfcHtmlTokenType_max }
};

wstr_t Dz1MfcHtmlTokenTypeStrW(Dz1MfcHtmlTokenType v)
{
	struct Dz1MfcHtmlTokenTypeMapW *i = NULL;
	for (i = Dz1MfcHtmlTokenTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MfcHtmlTokenType Dz1MfcHtmlTokenTypeFromStrW(wstr_t str)
{
	struct Dz1MfcHtmlTokenTypeMapW *i = NULL;
	for (i = Dz1MfcHtmlTokenTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MfcHtmlTokenType_max;
}
#endif // UNIX_SYSTEM

Dz1MfcHtmlTokenType *Dz1MfcHtmlTokenType_new(Dz1MfcHtmlTokenType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcHtmlTokenType *__internal_ret = (Dz1MfcHtmlTokenType *)Dz1Calloc(sizeof(Dz1MfcHtmlTokenType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1MfcHtmlTokenType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlToken
Dz1MfcHtmlToken *Dz1MfcHtmlToken_new(Dz1MfcHtmlTokenType type, Dz1Str value, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcHtmlToken *__internal_ret = (Dz1MfcHtmlToken *)Dz1Calloc(sizeof(Dz1MfcHtmlToken), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&__internal_ret);
		
		if (value && (__internal_ret->value = Dz1Str_clone(value, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->type = type;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcHtmlToken_copy(Dz1MfcHtmlToken *dst, Dz1MfcHtmlToken *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->value && (dst->value = Dz1Str_clone(src->value, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->type = src->type;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcHtmlToken *Dz1MfcHtmlToken_clone(Dz1MfcHtmlToken *src, Dz1Error *err)
{
	Dz1MfcHtmlToken *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcHtmlToken *)Dz1Calloc(sizeof(Dz1MfcHtmlToken), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlToken_delAndSetNull, (void *)&dst);
		if (Dz1MfcHtmlToken_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlToken_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcHtmlToken_purge(Dz1MfcHtmlToken *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->value);
}

void Dz1MfcHtmlToken_del(Dz1MfcHtmlToken *p)
{
	if (p == NULL) return;
	Dz1MfcHtmlToken_purge(p);
	Dz1Free(p);
}

void Dz1MfcHtmlToken_dump(Dz1MfcHtmlToken *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("type = %s(%d)\n"), Dz1MfcHtmlTokenTypeStr(p->type), p->type);
		Dz1Thread_tprintf(tab, Dz1T("value = ")); Dz1Str_dump(p->value, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcHtmlToken
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlTagAttr
Dz1MfcHtmlTagAttr *Dz1MfcHtmlTagAttr_new(Dz1Str id, Dz1Str value, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcHtmlTagAttr *__internal_ret = (Dz1MfcHtmlTagAttr *)Dz1Calloc(sizeof(Dz1MfcHtmlTagAttr), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlTagAttr_delAndSetNull, (void *)&__internal_ret);
		
		if (id && (__internal_ret->id = Dz1Str_clone(id, errp)) == NULL) ERR_OUT(errp);
		else if (value && (__internal_ret->value = Dz1Str_clone(value, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlTagAttr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcHtmlTagAttr_copy(Dz1MfcHtmlTagAttr *dst, Dz1MfcHtmlTagAttr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->id && (dst->id = Dz1Str_clone(src->id, errp)) == NULL) ERR_OUT(errp);
	else if (src->value && (dst->value = Dz1Str_clone(src->value, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcHtmlTagAttr *Dz1MfcHtmlTagAttr_clone(Dz1MfcHtmlTagAttr *src, Dz1Error *err)
{
	Dz1MfcHtmlTagAttr *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcHtmlTagAttr *)Dz1Calloc(sizeof(Dz1MfcHtmlTagAttr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlTagAttr_delAndSetNull, (void *)&dst);
		if (Dz1MfcHtmlTagAttr_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlTagAttr_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcHtmlTagAttr_purge(Dz1MfcHtmlTagAttr *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->id);
	Dz1Str_del(p->value);
}

void Dz1MfcHtmlTagAttr_del(Dz1MfcHtmlTagAttr *p)
{
	if (p == NULL) return;
	Dz1MfcHtmlTagAttr_purge(p);
	Dz1Free(p);
}

void Dz1MfcHtmlTagAttr_dump(Dz1MfcHtmlTagAttr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1Str_dump(p->id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("value = ")); Dz1Str_dump(p->value, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcHtmlTagAttr_cmp(Dz1MfcHtmlTagAttr *a, Dz1MfcHtmlTagAttr *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->id == NULL && b->id == NULL) ret = 0;
	else if (a->id == NULL /*&& b->id != NULL*/) ret = -1;
	else if (/*a->id != NULL &&*/ b->id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->id, b->id)) != 0) { }
	return ret;
}
// Dz1MfcHtmlTagAttr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlTagAttrList
static Dz1Error Dz1MfcHtmlTagAttrList_add(Dz1MfcHtmlTagAttrList *p, Dz1MfcHtmlTagAttr *data)
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

static bool_t Dz1MfcHtmlTagAttrList_remove(Dz1MfcHtmlTagAttrList *p, Dz1MfcHtmlTagAttr *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcHtmlTagAttr *Dz1MfcHtmlTagAttrList_extract(Dz1MfcHtmlTagAttrList *p, Dz1MfcHtmlTagAttr *key)
{
	return (Dz1MfcHtmlTagAttr *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcHtmlTagAttrListMkArrArg
{
	Dz1MfcHtmlTagAttr **arr;
	unsigned int idx;
} Dz1MfcHtmlTagAttrListMkArrArg;

static Dz1Error _Dz1MfcHtmlTagAttrList_get_array(void *ptr, Dz1MfcHtmlTagAttr *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcHtmlTagAttrListMkArrArg *arg = (Dz1MfcHtmlTagAttrListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcHtmlTagAttr **Dz1MfcHtmlTagAttrList_get_array(Dz1MfcHtmlTagAttrList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcHtmlTagAttr **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcHtmlTagAttr **)Dz1Calloc(sizeof(Dz1MfcHtmlTagAttr *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcHtmlTagAttrListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcHtmlTagAttrList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcHtmlTagAttrList_travelForward(Dz1MfcHtmlTagAttrList *p, Dz1Error (*func)(void *ptr, Dz1MfcHtmlTagAttr *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcHtmlTagAttrList_travelBackward(Dz1MfcHtmlTagAttrList *p, Dz1Error (*func)(void *ptr, Dz1MfcHtmlTagAttr *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcHtmlTagAttr *Dz1MfcHtmlTagAttrList_find(Dz1MfcHtmlTagAttrList *p, Dz1MfcHtmlTagAttr *key)
{
	return (Dz1MfcHtmlTagAttr *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcHtmlTagAttrList_count(Dz1MfcHtmlTagAttrList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcHtmlTagAttrList *Dz1MfcHtmlTagAttrList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcHtmlTagAttrList *ret = (Dz1MfcHtmlTagAttrList *)Dz1Calloc(sizeof(Dz1MfcHtmlTagAttrList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlTagAttrList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcHtmlTagAttr_cmp,
				(Dz1DelFunc)Dz1MfcHtmlTagAttr_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcHtmlTagAttrList_count;
			ret->travel = Dz1MfcHtmlTagAttrList_travelForward;
			ret->travelForward = Dz1MfcHtmlTagAttrList_travelForward;
			ret->travelBackward = Dz1MfcHtmlTagAttrList_travelBackward;
			ret->get_array = Dz1MfcHtmlTagAttrList_get_array;
			ret->add = Dz1MfcHtmlTagAttrList_add;
			ret->remove = Dz1MfcHtmlTagAttrList_remove;
			ret->find = Dz1MfcHtmlTagAttrList_find;
			ret->extract = Dz1MfcHtmlTagAttrList_extract;
			ret->cmp = Dz1MfcHtmlTagAttr_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlTagAttrList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcHtmlTagAttrList_clone(void *ptr, Dz1MfcHtmlTagAttr *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcHtmlTagAttrList *p = (Dz1MfcHtmlTagAttrList *)ptr;
	Dz1MfcHtmlTagAttr *cloned = Dz1MfcHtmlTagAttr_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcHtmlTagAttrList *Dz1MfcHtmlTagAttrList_clone(Dz1MfcHtmlTagAttrList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcHtmlTagAttrList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcHtmlTagAttrList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlTagAttrList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcHtmlTagAttrList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlTagAttrList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcHtmlTagAttrList_purge(Dz1MfcHtmlTagAttrList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcHtmlTagAttrList_del(Dz1MfcHtmlTagAttrList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcHtmlTagAttrList_dump(void *ptr, Dz1MfcHtmlTagAttr *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcHtmlTagAttr_dump(p, tab);
	return err;
}

void Dz1MfcHtmlTagAttrList_dump(Dz1MfcHtmlTagAttrList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcHtmlTagAttrList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcHtmlTagAttrList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlTag
Dz1MfcHtmlTag *Dz1MfcHtmlTag_new(Dz1Str tag_name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcHtmlTag *__internal_ret = (Dz1MfcHtmlTag *)Dz1Calloc(sizeof(Dz1MfcHtmlTag), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlTag_delAndSetNull, (void *)&__internal_ret);
		
		if (tag_name && (__internal_ret->tag_name = Dz1Str_clone(tag_name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->attr = Dz1MfcHtmlTagAttrList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlTag_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MfcHtmlTag_copy(Dz1MfcHtmlTag *dst, Dz1MfcHtmlTag *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->tag_name && (dst->tag_name = Dz1Str_clone(src->tag_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->attr && (dst->attr = Dz1MfcHtmlTagAttrList_clone(src->attr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MfcHtmlTag *Dz1MfcHtmlTag_clone(Dz1MfcHtmlTag *src, Dz1Error *err)
{
	Dz1MfcHtmlTag *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MfcHtmlTag *)Dz1Calloc(sizeof(Dz1MfcHtmlTag), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MfcHtmlTag_delAndSetNull, (void *)&dst);
		if (Dz1MfcHtmlTag_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcHtmlTag_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MfcHtmlTag_purge(Dz1MfcHtmlTag *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->tag_name);
	Dz1MfcHtmlTagAttrList_del(p->attr);
}

void Dz1MfcHtmlTag_del(Dz1MfcHtmlTag *p)
{
	if (p == NULL) return;
	Dz1MfcHtmlTag_purge(p);
	Dz1Free(p);
}

void Dz1MfcHtmlTag_dump(Dz1MfcHtmlTag *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tag_name = ")); Dz1Str_dump(p->tag_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("attr = ")); Dz1MfcHtmlTagAttrList_dump(p->attr, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcHtmlTag
////////////////////////////////////////////////////////////////////////////////

