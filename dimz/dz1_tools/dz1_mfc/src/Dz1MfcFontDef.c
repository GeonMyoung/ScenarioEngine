////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1MfcFontDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFontEntry
void Dz1MfcFontEntry_dump(Dz1MfcFontEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("font_name = ")); Dz1Str_dump(p->font_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("font_size = ")); Dz1u16_dump(&p->font_size, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MfcFontEntry_cmp(Dz1MfcFontEntry *a, Dz1MfcFontEntry *b)
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
// Dz1MfcFontEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFontList
static Dz1Error Dz1MfcFontList_add(Dz1MfcFontList *p, Dz1MfcFontEntry *data)
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

static bool_t Dz1MfcFontList_remove(Dz1MfcFontList *p, Dz1MfcFontEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MfcFontEntry *Dz1MfcFontList_extract(Dz1MfcFontList *p, Dz1MfcFontEntry *key)
{
	return (Dz1MfcFontEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MfcFontListMkArrArg
{
	Dz1MfcFontEntry **arr;
	unsigned int idx;
} Dz1MfcFontListMkArrArg;

static Dz1Error _Dz1MfcFontList_get_array(void *ptr, Dz1MfcFontEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFontListMkArrArg *arg = (Dz1MfcFontListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MfcFontEntry **Dz1MfcFontList_get_array(Dz1MfcFontList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MfcFontEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MfcFontEntry **)Dz1Calloc(sizeof(Dz1MfcFontEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFontListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MfcFontList_get_array, (void *)&arg);
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

static Dz1Error Dz1MfcFontList_travelForward(Dz1MfcFontList *p, Dz1Error (*func)(void *ptr, Dz1MfcFontEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MfcFontList_travelBackward(Dz1MfcFontList *p, Dz1Error (*func)(void *ptr, Dz1MfcFontEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MfcFontEntry *Dz1MfcFontList_find(Dz1MfcFontList *p, Dz1MfcFontEntry *key)
{
	return (Dz1MfcFontEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MfcFontList_count(Dz1MfcFontList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MfcFontList *Dz1MfcFontList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFontList *ret = (Dz1MfcFontList *)Dz1Calloc(sizeof(Dz1MfcFontList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFontList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MfcFontEntry_cmp,
				(Dz1DelFunc)Dz1MfcFontEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MfcFontList_count;
			ret->travel = Dz1MfcFontList_travelForward;
			ret->travelForward = Dz1MfcFontList_travelForward;
			ret->travelBackward = Dz1MfcFontList_travelBackward;
			ret->get_array = Dz1MfcFontList_get_array;
			ret->add = Dz1MfcFontList_add;
			ret->remove = Dz1MfcFontList_remove;
			ret->find = Dz1MfcFontList_find;
			ret->extract = Dz1MfcFontList_extract;
			ret->cmp = Dz1MfcFontEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFontList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MfcFontList_clone(void *ptr, Dz1MfcFontEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MfcFontList *p = (Dz1MfcFontList *)ptr;
	Dz1MfcFontEntry *cloned = Dz1MfcFontEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MfcFontList *Dz1MfcFontList_clone(Dz1MfcFontList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFontList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFontList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFontList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MfcFontList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFontList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcFontList_purge(Dz1MfcFontList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MfcFontList_del(Dz1MfcFontList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MfcFontList_dump(void *ptr, Dz1MfcFontEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MfcFontEntry_dump(p, tab);
	return err;
}

void Dz1MfcFontList_dump(Dz1MfcFontList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MfcFontList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFontList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFonts
Dz1MfcFonts *Dz1MfcFonts_new(real64_t factor, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFonts *__internal_ret = (Dz1MfcFonts *)Dz1Calloc(sizeof(Dz1MfcFonts), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MfcFonts_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->Dz1MfcFontList = Dz1MfcFontList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->factor = factor;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFonts_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MfcFonts_purge(Dz1MfcFonts *p)
{
	if (p == NULL) return;
	Dz1MfcFontList_del(p->Dz1MfcFontList);
}

void Dz1MfcFonts_del(Dz1MfcFonts *p)
{
	if (p == NULL) return;
	Dz1MfcFonts_purge(p);
	Dz1Free(p);
}

void Dz1MfcFonts_dump(Dz1MfcFonts *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("Dz1MfcFontList = ")); Dz1MfcFontList_dump(p->Dz1MfcFontList, tab); 
		Dz1Thread_tprintf(tab, Dz1T("factor = ")); Dz1Real64_dump(&p->factor, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MfcFonts
////////////////////////////////////////////////////////////////////////////////

