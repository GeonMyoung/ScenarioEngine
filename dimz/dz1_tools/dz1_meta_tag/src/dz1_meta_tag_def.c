////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_meta_tag_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValuePresent
static struct Dz1MetaTagValuePresentMapA
{
	str_t str;
	Dz1MetaTagValuePresent v;
} Dz1MetaTagValuePresentMapA[] =
{
	{ (char *)"data8", Dz1MetaTagValuePresent_data8 },
	{ (char *)"data16", Dz1MetaTagValuePresent_data16 },
	{ (char *)"data32", Dz1MetaTagValuePresent_data32 },
	{ (char *)"data64", Dz1MetaTagValuePresent_data64 },
	{ (char *)"binary", Dz1MetaTagValuePresent_binary },
	{ NULL, Dz1MetaTagValuePresent_max }
};

str_t Dz1MetaTagValuePresentStrA(Dz1MetaTagValuePresent v)
{
	struct Dz1MetaTagValuePresentMapA *i = NULL;
	for (i = Dz1MetaTagValuePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagValuePresent Dz1MetaTagValuePresentFromStrA(str_t str)
{
	struct Dz1MetaTagValuePresentMapA *i = NULL;
	for (i = Dz1MetaTagValuePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagValuePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MetaTagValuePresentMapW
{
	wstr_t str;
	Dz1MetaTagValuePresent v;
} Dz1MetaTagValuePresentMapW[] =
{
	{ (wchar_t *)L"data8", Dz1MetaTagValuePresent_data8 },
	{ (wchar_t *)L"data16", Dz1MetaTagValuePresent_data16 },
	{ (wchar_t *)L"data32", Dz1MetaTagValuePresent_data32 },
	{ (wchar_t *)L"data64", Dz1MetaTagValuePresent_data64 },
	{ (wchar_t *)L"binary", Dz1MetaTagValuePresent_binary },
	{ NULL, Dz1MetaTagValuePresent_max }
};

wstr_t Dz1MetaTagValuePresentStrW(Dz1MetaTagValuePresent v)
{
	struct Dz1MetaTagValuePresentMapW *i = NULL;
	for (i = Dz1MetaTagValuePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagValuePresent Dz1MetaTagValuePresentFromStrW(wstr_t str)
{
	struct Dz1MetaTagValuePresentMapW *i = NULL;
	for (i = Dz1MetaTagValuePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagValuePresent_max;
}
#endif // UNIX_SYSTEM

Dz1MetaTagValuePresent *Dz1MetaTagValuePresent_new(Dz1MetaTagValuePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagValuePresent *__internal_ret = (Dz1MetaTagValuePresent *)Dz1Calloc(sizeof(Dz1MetaTagValuePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1MetaTagValuePresent_dump(Dz1MetaTagValuePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1MetaTagValuePresentStr(*v));
}

int Dz1MetaTagValuePresent_cmp(Dz1MetaTagValuePresent *a, Dz1MetaTagValuePresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// Dz1MetaTagValuePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValue
Dz1MetaTagValue *Dz1MetaTagValue_new(Dz1MetaTagValuePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagValue *ret = (Dz1MetaTagValue *)Dz1Calloc(sizeof(Dz1MetaTagValue), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1MetaTagValuePresent_data8:
			// _U_prim_clone
			if (ptr != NULL) ret->x.data8 = *(u8_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_data16:
			// _U_prim_clone
			if (ptr != NULL) ret->x.data16 = *(u16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_data32:
			// _U_prim_clone
			if (ptr != NULL) ret->x.data32 = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_data64:
			// _U_prim_clone
			if (ptr != NULL) ret->x.data64 = *(u64_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_binary:
			// _U_imp_clone
			if (ptr != NULL) ret->x.binary = (Dz1Binary *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagValue_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1MetaTagValue_copy(Dz1MetaTagValue *ret, Dz1MetaTagValue *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1MetaTagValuePresent_data8:
			// _U_prim_clone
			ret->x.data8 = src->x.data8;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_data16:
			// _U_prim_clone
			ret->x.data16 = src->x.data16;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_data32:
			// _U_prim_clone
			ret->x.data32 = src->x.data32;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_data64:
			// _U_prim_clone
			ret->x.data64 = src->x.data64;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagValuePresent_binary:
			// _U_imp_clone
			if (src->x.binary && (ret->x.binary = Dz1Binary_clone(src->x.binary, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MetaTagValue *Dz1MetaTagValue_clone(Dz1MetaTagValue *src, Dz1Error *err)
{
	Dz1MetaTagValue *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1MetaTagValue *)Dz1Calloc(sizeof(Dz1MetaTagValue), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&ret);
		if (Dz1MetaTagValue_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagValue_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagValue_purge(Dz1MetaTagValue *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1MetaTagValuePresent_data8:
		break;
	case Dz1MetaTagValuePresent_data16:
		break;
	case Dz1MetaTagValuePresent_data32:
		break;
	case Dz1MetaTagValuePresent_data64:
		break;
	case Dz1MetaTagValuePresent_binary:
		Dz1Binary_del(p->x.binary);
		break;
	default:
		break;
	}
}

void Dz1MetaTagValue_del(Dz1MetaTagValue *p)
{
	if (!p) return;
	Dz1MetaTagValue_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagValue_dump(Dz1MetaTagValue *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1MetaTagValuePresent_data8:
		Dz1Thread_printf(Dz1T("data8 = ")); Dz1u8_dump(&p->x.data8, tab); 
		break;
	case Dz1MetaTagValuePresent_data16:
		Dz1Thread_printf(Dz1T("data16 = ")); Dz1u16_dump(&p->x.data16, tab); 
		break;
	case Dz1MetaTagValuePresent_data32:
		Dz1Thread_printf(Dz1T("data32 = ")); Dz1u32_dump(&p->x.data32, tab); 
		break;
	case Dz1MetaTagValuePresent_data64:
		Dz1Thread_printf(Dz1T("data64 = ")); Dz1u64_dump(&p->x.data64, tab); 
		break;
	case Dz1MetaTagValuePresent_binary:
		Dz1Thread_printf(Dz1T("binary = ")); Dz1Binary_dump(p->x.binary, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int Dz1MetaTagValue_cmp(Dz1MetaTagValue *a, Dz1MetaTagValue *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL && b != NULL) ret = -1;
	else if (a != NULL && b == NULL) ret = 1;
	else if (a->present != b->present) ret = (int)(a->present - b->present);
	else
	{
		switch(a->present)
		{
		case Dz1MetaTagValuePresent_data8:
			if ((ret = Dz1u8_cmp(&a->x.data8, &b->x.data8)) != 0) { }
			break;
		case Dz1MetaTagValuePresent_data16:
			if ((ret = Dz1u16_cmp(&a->x.data16, &b->x.data16)) != 0) { }
			break;
		case Dz1MetaTagValuePresent_data32:
			if ((ret = Dz1u32_cmp(&a->x.data32, &b->x.data32)) != 0) { }
			break;
		case Dz1MetaTagValuePresent_data64:
			if ((ret = Dz1u64_cmp(&a->x.data64, &b->x.data64)) != 0) { }
			break;
		case Dz1MetaTagValuePresent_binary:
			if (a->x.binary == NULL && b->x.binary == NULL) ret = 0;
			else if (a->x.binary == NULL /*&& b->x.binary != NULL*/) ret = -1;
			else if (/*a->x.binary != NULL &&*/ b->x.binary == NULL) ret = 1;
			else if ((ret = Dz1Binary_cmp(a->x.binary, b->x.binary)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// Dz1MetaTagValue
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValueList
static Dz1Error Dz1MetaTagValueList_add(Dz1MetaTagValueList *p, Dz1MetaTagValue *data)
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

static bool_t Dz1MetaTagValueList_remove(Dz1MetaTagValueList *p, Dz1MetaTagValue *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MetaTagValue *Dz1MetaTagValueList_extract(Dz1MetaTagValueList *p, Dz1MetaTagValue *key)
{
	return (Dz1MetaTagValue *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MetaTagValueListMkArrArg
{
	Dz1MetaTagValue **arr;
	unsigned int idx;
} Dz1MetaTagValueListMkArrArg;

static Dz1Error _Dz1MetaTagValueList_get_array(void *ptr, Dz1MetaTagValue *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagValueListMkArrArg *arg = (Dz1MetaTagValueListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MetaTagValue **Dz1MetaTagValueList_get_array(Dz1MetaTagValueList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MetaTagValue **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MetaTagValue **)Dz1Calloc(sizeof(Dz1MetaTagValue *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagValueListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MetaTagValueList_get_array, (void *)&arg);
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

static Dz1Error Dz1MetaTagValueList_travelForward(Dz1MetaTagValueList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagValue *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MetaTagValueList_travelBackward(Dz1MetaTagValueList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagValue *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MetaTagValue *Dz1MetaTagValueList_find(Dz1MetaTagValueList *p, Dz1MetaTagValue *key)
{
	return (Dz1MetaTagValue *)Dz1AATree_find(p->storage, key);
}

static Dz1MetaTagValue *Dz1MetaTagValueList_getHead(Dz1MetaTagValueList *p)
{
	return (Dz1MetaTagValue *)Dz1AATree_getHead(p->storage);
}

static Dz1MetaTagValue *Dz1MetaTagValueList_getTail(Dz1MetaTagValueList *p)
{
	return (Dz1MetaTagValue *)Dz1AATree_getTail(p->storage);
}

static unsigned int Dz1MetaTagValueList_count(Dz1MetaTagValueList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MetaTagValueList *Dz1MetaTagValueList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagValueList *ret = (Dz1MetaTagValueList *)Dz1Calloc(sizeof(Dz1MetaTagValueList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValueList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MetaTagValue_cmp,
				(Dz1DelFunc)Dz1MetaTagValue_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MetaTagValueList_count;
			ret->travel = Dz1MetaTagValueList_travelForward;
			ret->travelForward = Dz1MetaTagValueList_travelForward;
			ret->travelBackward = Dz1MetaTagValueList_travelBackward;
			ret->get_array = Dz1MetaTagValueList_get_array;
			ret->add = Dz1MetaTagValueList_add;
			ret->remove = Dz1MetaTagValueList_remove;
			ret->find = Dz1MetaTagValueList_find;
			ret->extract = Dz1MetaTagValueList_extract;
			ret->getHead = Dz1MetaTagValueList_getHead;
			ret->getTail = Dz1MetaTagValueList_getTail;
			ret->cmp = Dz1MetaTagValue_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagValueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MetaTagValueList_clone(void *ptr, Dz1MetaTagValue *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagValueList *p = (Dz1MetaTagValueList *)ptr;
	Dz1MetaTagValue *cloned = Dz1MetaTagValue_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MetaTagValueList *Dz1MetaTagValueList_clone(Dz1MetaTagValueList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagValueList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTagValueList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValueList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MetaTagValueList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagValueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagValueList_purge(Dz1MetaTagValueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MetaTagValueList_del(Dz1MetaTagValueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MetaTagValueList_dump(void *ptr, Dz1MetaTagValue *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MetaTagValue_dump(p, tab);
	return err;
}

void Dz1MetaTagValueList_dump(Dz1MetaTagValueList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MetaTagValueList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagValueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataEntry
Dz1MetaTagDataEntry *Dz1MetaTagDataEntry_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDataEntry *__internal_ret = (Dz1MetaTagDataEntry *)Dz1Calloc(sizeof(Dz1MetaTagDataEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDataEntry_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->values = Dz1MetaTagValueList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->id = id;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDataEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MetaTagDataEntry_copy(Dz1MetaTagDataEntry *dst, Dz1MetaTagDataEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->values && (dst->values = Dz1MetaTagValueList_clone(src->values, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->id = src->id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MetaTagDataEntry *Dz1MetaTagDataEntry_clone(Dz1MetaTagDataEntry *src, Dz1Error *err)
{
	Dz1MetaTagDataEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MetaTagDataEntry *)Dz1Calloc(sizeof(Dz1MetaTagDataEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDataEntry_delAndSetNull, (void *)&dst);
		if (Dz1MetaTagDataEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDataEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MetaTagDataEntry_purge(Dz1MetaTagDataEntry *p)
{
	if (p == NULL) return;
	Dz1MetaTagValueList_del(p->values);
}

void Dz1MetaTagDataEntry_del(Dz1MetaTagDataEntry *p)
{
	if (p == NULL) return;
	Dz1MetaTagDataEntry_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDataEntry_dump(Dz1MetaTagDataEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("values = ")); Dz1MetaTagValueList_dump(p->values, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MetaTagDataEntry_cmp(Dz1MetaTagDataEntry *a, Dz1MetaTagDataEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// Dz1MetaTagDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataList
static Dz1Error Dz1MetaTagDataList_add(Dz1MetaTagDataList *p, Dz1MetaTagDataEntry *data)
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

static bool_t Dz1MetaTagDataList_remove(Dz1MetaTagDataList *p, Dz1MetaTagDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MetaTagDataEntry *Dz1MetaTagDataList_extract(Dz1MetaTagDataList *p, Dz1MetaTagDataEntry *key)
{
	return (Dz1MetaTagDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MetaTagDataListMkArrArg
{
	Dz1MetaTagDataEntry **arr;
	unsigned int idx;
} Dz1MetaTagDataListMkArrArg;

static Dz1Error _Dz1MetaTagDataList_get_array(void *ptr, Dz1MetaTagDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagDataListMkArrArg *arg = (Dz1MetaTagDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MetaTagDataEntry **Dz1MetaTagDataList_get_array(Dz1MetaTagDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MetaTagDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MetaTagDataEntry **)Dz1Calloc(sizeof(Dz1MetaTagDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MetaTagDataList_get_array, (void *)&arg);
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

static Dz1Error Dz1MetaTagDataList_travelForward(Dz1MetaTagDataList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MetaTagDataList_travelBackward(Dz1MetaTagDataList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MetaTagDataEntry *Dz1MetaTagDataList_find(Dz1MetaTagDataList *p, Dz1MetaTagDataEntry *key)
{
	return (Dz1MetaTagDataEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MetaTagDataList_count(Dz1MetaTagDataList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MetaTagDataList *Dz1MetaTagDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDataList *ret = (Dz1MetaTagDataList *)Dz1Calloc(sizeof(Dz1MetaTagDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MetaTagDataEntry_cmp,
				(Dz1DelFunc)Dz1MetaTagDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MetaTagDataList_count;
			ret->travel = Dz1MetaTagDataList_travelForward;
			ret->travelForward = Dz1MetaTagDataList_travelForward;
			ret->travelBackward = Dz1MetaTagDataList_travelBackward;
			ret->get_array = Dz1MetaTagDataList_get_array;
			ret->add = Dz1MetaTagDataList_add;
			ret->remove = Dz1MetaTagDataList_remove;
			ret->find = Dz1MetaTagDataList_find;
			ret->extract = Dz1MetaTagDataList_extract;
			ret->cmp = Dz1MetaTagDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MetaTagDataList_clone(void *ptr, Dz1MetaTagDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagDataList *p = (Dz1MetaTagDataList *)ptr;
	Dz1MetaTagDataEntry *cloned = Dz1MetaTagDataEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MetaTagDataList *Dz1MetaTagDataList_clone(Dz1MetaTagDataList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDataList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTagDataList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDataList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MetaTagDataList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagDataList_purge(Dz1MetaTagDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MetaTagDataList_del(Dz1MetaTagDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MetaTagDataList_dump(void *ptr, Dz1MetaTagDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MetaTagDataEntry_dump(p, tab);
	return err;
}

void Dz1MetaTagDataList_dump(Dz1MetaTagDataList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MetaTagDataList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagData
Dz1MetaTagData *Dz1MetaTagData_new(u32_t target_type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagData *__internal_ret = (Dz1MetaTagData *)Dz1Calloc(sizeof(Dz1MetaTagData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagData_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->tags = Dz1MetaTagDataList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->target_type = target_type;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MetaTagData_copy(Dz1MetaTagData *dst, Dz1MetaTagData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->tags && (dst->tags = Dz1MetaTagDataList_clone(src->tags, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->target_type = src->target_type;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MetaTagData *Dz1MetaTagData_clone(Dz1MetaTagData *src, Dz1Error *err)
{
	Dz1MetaTagData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MetaTagData *)Dz1Calloc(sizeof(Dz1MetaTagData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagData_delAndSetNull, (void *)&dst);
		if (Dz1MetaTagData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MetaTagData_purge(Dz1MetaTagData *p)
{
	if (p == NULL) return;
	Dz1MetaTagDataList_del(p->tags);
}

void Dz1MetaTagData_del(Dz1MetaTagData *p)
{
	if (p == NULL) return;
	Dz1MetaTagData_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagData_dump(Dz1MetaTagData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("target_type = ")); Dz1u32_dump(&p->target_type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tags = ")); Dz1MetaTagDataList_dump(p->tags, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeEntry
Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeEntry_new(u32_t type, 
												   Dz1Asn1UTF8Str *name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTargetTypeEntry *__internal_ret = (Dz1MetaTargetTypeEntry *)Dz1Calloc(sizeof(Dz1MetaTargetTypeEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		__internal_ret->name = name;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MetaTargetTypeEntry_copy(Dz1MetaTargetTypeEntry *dst, Dz1MetaTargetTypeEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Asn1UTF8Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->name_w && (dst->name_w = dz1_built_in_wstr_clone(src->name_w, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->type = src->type;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeEntry_clone(Dz1MetaTargetTypeEntry *src, Dz1Error *err)
{
	Dz1MetaTargetTypeEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MetaTargetTypeEntry *)Dz1Calloc(sizeof(Dz1MetaTargetTypeEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&dst);
		if (Dz1MetaTargetTypeEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MetaTargetTypeEntry_purge(Dz1MetaTargetTypeEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
	dz1_built_in_wstr_del(p->name_w);
}

void Dz1MetaTargetTypeEntry_del(Dz1MetaTargetTypeEntry *p)
{
	if (p == NULL) return;
	Dz1MetaTargetTypeEntry_purge(p);
	Dz1Free(p);
}

int Dz1MetaTargetTypeEntry_cmp(Dz1MetaTargetTypeEntry *a, Dz1MetaTargetTypeEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->type, &b->type)) != 0) { }
	return ret;
}
// Dz1MetaTargetTypeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeList
static Dz1Error Dz1MetaTargetTypeList_add(Dz1MetaTargetTypeList *p, Dz1MetaTargetTypeEntry *data)
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

static bool_t Dz1MetaTargetTypeList_remove(Dz1MetaTargetTypeList *p, Dz1MetaTargetTypeEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeList_extract(Dz1MetaTargetTypeList *p, Dz1MetaTargetTypeEntry *key)
{
	return (Dz1MetaTargetTypeEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MetaTargetTypeListMkArrArg
{
	Dz1MetaTargetTypeEntry **arr;
	unsigned int idx;
} Dz1MetaTargetTypeListMkArrArg;

static Dz1Error _Dz1MetaTargetTypeList_get_array(void *ptr, Dz1MetaTargetTypeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTargetTypeListMkArrArg *arg = (Dz1MetaTargetTypeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MetaTargetTypeEntry **Dz1MetaTargetTypeList_get_array(Dz1MetaTargetTypeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MetaTargetTypeEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MetaTargetTypeEntry **)Dz1Calloc(sizeof(Dz1MetaTargetTypeEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTargetTypeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MetaTargetTypeList_get_array, (void *)&arg);
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

static Dz1Error Dz1MetaTargetTypeList_travelForward(Dz1MetaTargetTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTargetTypeEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MetaTargetTypeList_travelBackward(Dz1MetaTargetTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTargetTypeEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeList_find(Dz1MetaTargetTypeList *p, Dz1MetaTargetTypeEntry *key)
{
	return (Dz1MetaTargetTypeEntry *)Dz1AATree_find(p->storage, key);
}

static Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeList_getTail(Dz1MetaTargetTypeList *p)
{
	return (Dz1MetaTargetTypeEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int Dz1MetaTargetTypeList_count(Dz1MetaTargetTypeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MetaTargetTypeList *Dz1MetaTargetTypeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTargetTypeList *ret = (Dz1MetaTargetTypeList *)Dz1Calloc(sizeof(Dz1MetaTargetTypeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTargetTypeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MetaTargetTypeEntry_cmp,
				(Dz1DelFunc)Dz1MetaTargetTypeEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MetaTargetTypeList_count;
			ret->travel = Dz1MetaTargetTypeList_travelForward;
			ret->travelForward = Dz1MetaTargetTypeList_travelForward;
			ret->travelBackward = Dz1MetaTargetTypeList_travelBackward;
			ret->get_array = Dz1MetaTargetTypeList_get_array;
			ret->add = Dz1MetaTargetTypeList_add;
			ret->remove = Dz1MetaTargetTypeList_remove;
			ret->find = Dz1MetaTargetTypeList_find;
			ret->extract = Dz1MetaTargetTypeList_extract;
			ret->getTail = Dz1MetaTargetTypeList_getTail;
			ret->cmp = Dz1MetaTargetTypeEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTargetTypeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MetaTargetTypeList_clone(void *ptr, Dz1MetaTargetTypeEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTargetTypeList *p = (Dz1MetaTargetTypeList *)ptr;
	Dz1MetaTargetTypeEntry *cloned = Dz1MetaTargetTypeEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MetaTargetTypeList *Dz1MetaTargetTypeList_clone(Dz1MetaTargetTypeList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTargetTypeList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTargetTypeList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTargetTypeList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MetaTargetTypeList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTargetTypeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTargetTypeList_purge(Dz1MetaTargetTypeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MetaTargetTypeList_del(Dz1MetaTargetTypeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MetaTargetTypeList_dump(void *ptr, Dz1MetaTargetTypeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MetaTargetTypeEntry_dump(p, tab);
	return err;
}

void Dz1MetaTargetTypeList_dump(Dz1MetaTargetTypeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MetaTargetTypeList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTargetTypeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagRestrictMode
static struct Dz1MetaTagRestrictModeMapA
{
	str_t str;
	Dz1MetaTagRestrictMode v;
} Dz1MetaTagRestrictModeMapA[] =
{
	{ (char *)"accept", Dz1MetaTagRestrictMode_accept },
	{ (char *)"reject", Dz1MetaTagRestrictMode_reject },
	{ NULL, Dz1MetaTagRestrictMode_max }
};

str_t Dz1MetaTagRestrictModeStrA(Dz1MetaTagRestrictMode v)
{
	struct Dz1MetaTagRestrictModeMapA *i = NULL;
	for (i = Dz1MetaTagRestrictModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagRestrictMode Dz1MetaTagRestrictModeFromStrA(str_t str)
{
	struct Dz1MetaTagRestrictModeMapA *i = NULL;
	for (i = Dz1MetaTagRestrictModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagRestrictMode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MetaTagRestrictModeMapW
{
	wstr_t str;
	Dz1MetaTagRestrictMode v;
} Dz1MetaTagRestrictModeMapW[] =
{
	{ (wchar_t *)L"accept", Dz1MetaTagRestrictMode_accept },
	{ (wchar_t *)L"reject", Dz1MetaTagRestrictMode_reject },
	{ NULL, Dz1MetaTagRestrictMode_max }
};

wstr_t Dz1MetaTagRestrictModeStrW(Dz1MetaTagRestrictMode v)
{
	struct Dz1MetaTagRestrictModeMapW *i = NULL;
	for (i = Dz1MetaTagRestrictModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagRestrictMode Dz1MetaTagRestrictModeFromStrW(wstr_t str)
{
	struct Dz1MetaTagRestrictModeMapW *i = NULL;
	for (i = Dz1MetaTagRestrictModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagRestrictMode_max;
}
#endif // UNIX_SYSTEM

Dz1MetaTagRestrictMode *Dz1MetaTagRestrictMode_new(Dz1MetaTagRestrictMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagRestrictMode *__internal_ret = (Dz1MetaTagRestrictMode *)Dz1Calloc(sizeof(Dz1MetaTagRestrictMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1MetaTagRestrictMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagRestrict
Dz1MetaTagRestrict *Dz1MetaTagRestrict_new(Dz1MetaTagRestrictMode mode, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagRestrict *__internal_ret = (Dz1MetaTagRestrict *)Dz1Calloc(sizeof(Dz1MetaTagRestrict), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagRestrict_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->list = Dz1MetaTargetTypeList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->mode = mode;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagRestrict_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MetaTagRestrict_copy(Dz1MetaTagRestrict *dst, Dz1MetaTagRestrict *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->list && (dst->list = Dz1MetaTargetTypeList_clone(src->list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->mode = src->mode;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MetaTagRestrict *Dz1MetaTagRestrict_clone(Dz1MetaTagRestrict *src, Dz1Error *err)
{
	Dz1MetaTagRestrict *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MetaTagRestrict *)Dz1Calloc(sizeof(Dz1MetaTagRestrict), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagRestrict_delAndSetNull, (void *)&dst);
		if (Dz1MetaTagRestrict_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagRestrict_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MetaTagRestrict_purge(Dz1MetaTagRestrict *p)
{
	if (p == NULL) return;
	Dz1MetaTargetTypeList_del(p->list);
}

void Dz1MetaTagRestrict_del(Dz1MetaTagRestrict *p)
{
	if (p == NULL) return;
	Dz1MetaTagRestrict_purge(p);
	Dz1Free(p);
}

// Dz1MetaTagRestrict
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrNum
static struct Dz1MetaTagDescrNumMapA
{
	str_t str;
	Dz1MetaTagDescrNum v;
} Dz1MetaTagDescrNumMapA[] =
{
	{ (char *)"signed", Dz1MetaTagDescrNum_signed },
	{ (char *)"unsigned", Dz1MetaTagDescrNum_unsigned },
	{ (char *)"hex", Dz1MetaTagDescrNum_hex },
	{ (char *)"binary", Dz1MetaTagDescrNum_binary },
	{ NULL, Dz1MetaTagDescrNum_max }
};

str_t Dz1MetaTagDescrNumStrA(Dz1MetaTagDescrNum v)
{
	struct Dz1MetaTagDescrNumMapA *i = NULL;
	for (i = Dz1MetaTagDescrNumMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagDescrNum Dz1MetaTagDescrNumFromStrA(str_t str)
{
	struct Dz1MetaTagDescrNumMapA *i = NULL;
	for (i = Dz1MetaTagDescrNumMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagDescrNum_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MetaTagDescrNumMapW
{
	wstr_t str;
	Dz1MetaTagDescrNum v;
} Dz1MetaTagDescrNumMapW[] =
{
	{ (wchar_t *)L"signed", Dz1MetaTagDescrNum_signed },
	{ (wchar_t *)L"unsigned", Dz1MetaTagDescrNum_unsigned },
	{ (wchar_t *)L"hex", Dz1MetaTagDescrNum_hex },
	{ (wchar_t *)L"binary", Dz1MetaTagDescrNum_binary },
	{ NULL, Dz1MetaTagDescrNum_max }
};

wstr_t Dz1MetaTagDescrNumStrW(Dz1MetaTagDescrNum v)
{
	struct Dz1MetaTagDescrNumMapW *i = NULL;
	for (i = Dz1MetaTagDescrNumMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagDescrNum Dz1MetaTagDescrNumFromStrW(wstr_t str)
{
	struct Dz1MetaTagDescrNumMapW *i = NULL;
	for (i = Dz1MetaTagDescrNumMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagDescrNum_max;
}
#endif // UNIX_SYSTEM

Dz1MetaTagDescrNum *Dz1MetaTagDescrNum_new(Dz1MetaTagDescrNum *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrNum *__internal_ret = (Dz1MetaTagDescrNum *)Dz1Calloc(sizeof(Dz1MetaTagDescrNum), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1MetaTagDescrNum
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrNumber
Dz1MetaTagDescrNumber *Dz1MetaTagDescrNumber_new(Dz1MetaTagDescrNum type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrNumber *__internal_ret = (Dz1MetaTagDescrNumber *)Dz1Calloc(sizeof(Dz1MetaTagDescrNumber), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrNumber_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrNumber_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDescrNumber_purge(Dz1MetaTagDescrNumber *p)
{
	if (p == NULL) return;
}

void Dz1MetaTagDescrNumber_del(Dz1MetaTagDescrNumber *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrNumber_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescrNumber_dump(Dz1MetaTagDescrNumber *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("type = %s(%d)\n"), Dz1MetaTagDescrNumStr(p->type), p->type);
	}
}
// Dz1MetaTagDescrNumber
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrFloat
Dz1MetaTagDescrFloat *Dz1MetaTagDescrFloat_new(s32_t precision, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrFloat *__internal_ret = (Dz1MetaTagDescrFloat *)Dz1Calloc(sizeof(Dz1MetaTagDescrFloat), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrFloat_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->precision = precision;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrFloat_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDescrFloat_purge(Dz1MetaTagDescrFloat *p)
{
	if (p == NULL) return;
}

void Dz1MetaTagDescrFloat_del(Dz1MetaTagDescrFloat *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrFloat_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescrFloat_dump(Dz1MetaTagDescrFloat *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("precision = ")); Dz1s32_dump(&p->precision, tab); 
	}
}
// Dz1MetaTagDescrFloat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrGrade
Dz1MetaTagDescrGrade *Dz1MetaTagDescrGrade_new(u32_t max_grade, 
											   Dz1Asn1UTF8Str *grade_unit, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrGrade *__internal_ret = (Dz1MetaTagDescrGrade *)Dz1Calloc(sizeof(Dz1MetaTagDescrGrade), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrGrade_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->max_grade = max_grade;
		__internal_ret->grade_unit = grade_unit;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrGrade_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDescrGrade_purge(Dz1MetaTagDescrGrade *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->grade_unit);
	dz1_built_in_wstr_del(p->grade_unit_w);
}

void Dz1MetaTagDescrGrade_del(Dz1MetaTagDescrGrade *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrGrade_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescrGrade_dump(Dz1MetaTagDescrGrade *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("max_grade = ")); Dz1u32_dump(&p->max_grade, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("grade_unit = ")); Dz1Asn1UTF8Str_dump(p->grade_unit, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagDescrGrade
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrString
Dz1MetaTagDescrString *Dz1MetaTagDescrString_new(str_t charset, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrString *__internal_ret = (Dz1MetaTagDescrString *)Dz1Calloc(sizeof(Dz1MetaTagDescrString), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrString_delAndSetNull, (void *)&__internal_ret);
		
		if (charset && (__internal_ret->charset = dz1_built_in_str_clone(charset, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrString_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDescrString_purge(Dz1MetaTagDescrString *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->charset);
}

void Dz1MetaTagDescrString_del(Dz1MetaTagDescrString *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrString_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescrString_dump(Dz1MetaTagDescrString *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("charset = ")); dz1_built_in_str_dump(p->charset, tab); 
	}
}
// Dz1MetaTagDescrString
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumEntry
Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumEntry_new(u32_t value, 
													   Dz1Asn1UTF8Str *string, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrEnumEntry *__internal_ret = (Dz1MetaTagDescrEnumEntry *)Dz1Calloc(sizeof(Dz1MetaTagDescrEnumEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->value = value;
		__internal_ret->string = string;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MetaTagDescrEnumEntry_copy(Dz1MetaTagDescrEnumEntry *dst, Dz1MetaTagDescrEnumEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->string && (dst->string = Dz1Asn1UTF8Str_clone(src->string, errp)) == NULL) ERR_OUT(errp);
	else if (src->str_w && (dst->str_w = dz1_built_in_wstr_clone(src->str_w, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->value = src->value;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumEntry_clone(Dz1MetaTagDescrEnumEntry *src, Dz1Error *err)
{
	Dz1MetaTagDescrEnumEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MetaTagDescrEnumEntry *)Dz1Calloc(sizeof(Dz1MetaTagDescrEnumEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&dst);
		if (Dz1MetaTagDescrEnumEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MetaTagDescrEnumEntry_purge(Dz1MetaTagDescrEnumEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->string);
	dz1_built_in_wstr_del(p->str_w);
}

void Dz1MetaTagDescrEnumEntry_del(Dz1MetaTagDescrEnumEntry *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrEnumEntry_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescrEnumEntry_dump(Dz1MetaTagDescrEnumEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("value = ")); Dz1u32_dump(&p->value, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("string = ")); Dz1Asn1UTF8Str_dump(p->string, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MetaTagDescrEnumEntry_cmp(Dz1MetaTagDescrEnumEntry *a, Dz1MetaTagDescrEnumEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->value, &b->value)) != 0) { }
	return ret;
}
// Dz1MetaTagDescrEnumEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumList
static Dz1Error Dz1MetaTagDescrEnumList_add(Dz1MetaTagDescrEnumList *p, Dz1MetaTagDescrEnumEntry *data)
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

static bool_t Dz1MetaTagDescrEnumList_remove(Dz1MetaTagDescrEnumList *p, Dz1MetaTagDescrEnumEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumList_extract(Dz1MetaTagDescrEnumList *p, Dz1MetaTagDescrEnumEntry *key)
{
	return (Dz1MetaTagDescrEnumEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MetaTagDescrEnumListMkArrArg
{
	Dz1MetaTagDescrEnumEntry **arr;
	unsigned int idx;
} Dz1MetaTagDescrEnumListMkArrArg;

static Dz1Error _Dz1MetaTagDescrEnumList_get_array(void *ptr, Dz1MetaTagDescrEnumEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagDescrEnumListMkArrArg *arg = (Dz1MetaTagDescrEnumListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MetaTagDescrEnumEntry **Dz1MetaTagDescrEnumList_get_array(Dz1MetaTagDescrEnumList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MetaTagDescrEnumEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MetaTagDescrEnumEntry **)Dz1Calloc(sizeof(Dz1MetaTagDescrEnumEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrEnumListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MetaTagDescrEnumList_get_array, (void *)&arg);
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

static Dz1Error Dz1MetaTagDescrEnumList_travelForward(Dz1MetaTagDescrEnumList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MetaTagDescrEnumList_travelBackward(Dz1MetaTagDescrEnumList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumList_find(Dz1MetaTagDescrEnumList *p, Dz1MetaTagDescrEnumEntry *key)
{
	return (Dz1MetaTagDescrEnumEntry *)Dz1AATree_find(p->storage, key);
}

static Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumList_getTail(Dz1MetaTagDescrEnumList *p)
{
	return (Dz1MetaTagDescrEnumEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int Dz1MetaTagDescrEnumList_count(Dz1MetaTagDescrEnumList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MetaTagDescrEnumList *Dz1MetaTagDescrEnumList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrEnumList *ret = (Dz1MetaTagDescrEnumList *)Dz1Calloc(sizeof(Dz1MetaTagDescrEnumList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnumList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MetaTagDescrEnumEntry_cmp,
				(Dz1DelFunc)Dz1MetaTagDescrEnumEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MetaTagDescrEnumList_count;
			ret->travel = Dz1MetaTagDescrEnumList_travelForward;
			ret->travelForward = Dz1MetaTagDescrEnumList_travelForward;
			ret->travelBackward = Dz1MetaTagDescrEnumList_travelBackward;
			ret->get_array = Dz1MetaTagDescrEnumList_get_array;
			ret->add = Dz1MetaTagDescrEnumList_add;
			ret->remove = Dz1MetaTagDescrEnumList_remove;
			ret->find = Dz1MetaTagDescrEnumList_find;
			ret->extract = Dz1MetaTagDescrEnumList_extract;
			ret->getTail = Dz1MetaTagDescrEnumList_getTail;
			ret->cmp = Dz1MetaTagDescrEnumEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnumList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MetaTagDescrEnumList_clone(void *ptr, Dz1MetaTagDescrEnumEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagDescrEnumList *p = (Dz1MetaTagDescrEnumList *)ptr;
	Dz1MetaTagDescrEnumEntry *cloned = Dz1MetaTagDescrEnumEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MetaTagDescrEnumList *Dz1MetaTagDescrEnumList_clone(Dz1MetaTagDescrEnumList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrEnumList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTagDescrEnumList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnumList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MetaTagDescrEnumList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnumList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagDescrEnumList_purge(Dz1MetaTagDescrEnumList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MetaTagDescrEnumList_del(Dz1MetaTagDescrEnumList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MetaTagDescrEnumList_dump(void *ptr, Dz1MetaTagDescrEnumEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MetaTagDescrEnumEntry_dump(p, tab);
	return err;
}

void Dz1MetaTagDescrEnumList_dump(Dz1MetaTagDescrEnumList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MetaTagDescrEnumList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagDescrEnumList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumIndex
Dz1MetaTagDescrEnumIndex *Dz1MetaTagDescrEnumIndex_new(u32_t value, 
													   Dz1Asn1UTF8Str *string, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrEnumIndex *__internal_ret = (Dz1MetaTagDescrEnumIndex *)Dz1Calloc(sizeof(Dz1MetaTagDescrEnumIndex), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnumIndex_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->value = value;
		__internal_ret->string = string;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnumIndex_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MetaTagDescrEnumIndex_copy(Dz1MetaTagDescrEnumIndex *dst, Dz1MetaTagDescrEnumIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->string && (dst->string = Dz1Asn1UTF8Str_clone(src->string, errp)) == NULL) ERR_OUT(errp);
	else if (src->str_w && (dst->str_w = dz1_built_in_wstr_clone(src->str_w, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->value = src->value;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MetaTagDescrEnumIndex *Dz1MetaTagDescrEnumIndex_clone(Dz1MetaTagDescrEnumIndex *src, Dz1Error *err)
{
	Dz1MetaTagDescrEnumIndex *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MetaTagDescrEnumIndex *)Dz1Calloc(sizeof(Dz1MetaTagDescrEnumIndex), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnumIndex_delAndSetNull, (void *)&dst);
		if (Dz1MetaTagDescrEnumIndex_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnumIndex_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MetaTagDescrEnumIndex_purge(Dz1MetaTagDescrEnumIndex *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->string);
	dz1_built_in_wstr_del(p->str_w);
}

void Dz1MetaTagDescrEnumIndex_del(Dz1MetaTagDescrEnumIndex *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrEnumIndex_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescrEnumIndex_dump(Dz1MetaTagDescrEnumIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("value = ")); Dz1u32_dump(&p->value, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("string = ")); Dz1Asn1UTF8Str_dump(p->string, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MetaTagDescrEnumIndex_cmp(Dz1MetaTagDescrEnumIndex *a, Dz1MetaTagDescrEnumIndex *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->string == NULL && b->string == NULL) ret = 0;
	else if (a->string == NULL /*&& b->string != NULL*/) ret = -1;
	else if (/*a->string != NULL &&*/ b->string == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->string, b->string)) != 0) { }
	return ret;
}
// Dz1MetaTagDescrEnumIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumTable
static Dz1Error Dz1MetaTagDescrEnumTable_add(Dz1MetaTagDescrEnumTable *p, Dz1MetaTagDescrEnumIndex *data)
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

static bool_t Dz1MetaTagDescrEnumTable_remove(Dz1MetaTagDescrEnumTable *p, Dz1MetaTagDescrEnumIndex *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MetaTagDescrEnumIndex *Dz1MetaTagDescrEnumTable_extract(Dz1MetaTagDescrEnumTable *p, Dz1MetaTagDescrEnumIndex *key)
{
	return (Dz1MetaTagDescrEnumIndex *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MetaTagDescrEnumTableMkArrArg
{
	Dz1MetaTagDescrEnumIndex **arr;
	unsigned int idx;
} Dz1MetaTagDescrEnumTableMkArrArg;

static Dz1Error _Dz1MetaTagDescrEnumTable_get_array(void *ptr, Dz1MetaTagDescrEnumIndex *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagDescrEnumTableMkArrArg *arg = (Dz1MetaTagDescrEnumTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MetaTagDescrEnumIndex **Dz1MetaTagDescrEnumTable_get_array(Dz1MetaTagDescrEnumTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MetaTagDescrEnumIndex **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MetaTagDescrEnumIndex **)Dz1Calloc(sizeof(Dz1MetaTagDescrEnumIndex *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrEnumTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MetaTagDescrEnumTable_get_array, (void *)&arg);
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

static Dz1Error Dz1MetaTagDescrEnumTable_travelForward(Dz1MetaTagDescrEnumTable *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumIndex *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MetaTagDescrEnumTable_travelBackward(Dz1MetaTagDescrEnumTable *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumIndex *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MetaTagDescrEnumIndex *Dz1MetaTagDescrEnumTable_find(Dz1MetaTagDescrEnumTable *p, Dz1MetaTagDescrEnumIndex *key)
{
	return (Dz1MetaTagDescrEnumIndex *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MetaTagDescrEnumTable_count(Dz1MetaTagDescrEnumTable *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MetaTagDescrEnumTable *Dz1MetaTagDescrEnumTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrEnumTable *ret = (Dz1MetaTagDescrEnumTable *)Dz1Calloc(sizeof(Dz1MetaTagDescrEnumTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnumTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MetaTagDescrEnumIndex_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MetaTagDescrEnumTable_count;
			ret->travel = Dz1MetaTagDescrEnumTable_travelForward;
			ret->travelForward = Dz1MetaTagDescrEnumTable_travelForward;
			ret->travelBackward = Dz1MetaTagDescrEnumTable_travelBackward;
			ret->get_array = Dz1MetaTagDescrEnumTable_get_array;
			ret->add = Dz1MetaTagDescrEnumTable_add;
			ret->remove = Dz1MetaTagDescrEnumTable_remove;
			ret->find = Dz1MetaTagDescrEnumTable_find;
			ret->extract = Dz1MetaTagDescrEnumTable_extract;
			ret->cmp = Dz1MetaTagDescrEnumIndex_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnumTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MetaTagDescrEnumTable_clone(void *ptr, Dz1MetaTagDescrEnumIndex *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagDescrEnumTable *p = (Dz1MetaTagDescrEnumTable *)ptr;
	Dz1MetaTagDescrEnumIndex *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MetaTagDescrEnumTable *Dz1MetaTagDescrEnumTable_clone(Dz1MetaTagDescrEnumTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrEnumTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTagDescrEnumTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnumTable_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1MetaTagDescrEnumTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnumTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagDescrEnumTable_purge(Dz1MetaTagDescrEnumTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MetaTagDescrEnumTable_del(Dz1MetaTagDescrEnumTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MetaTagDescrEnumTable_dump(void *ptr, Dz1MetaTagDescrEnumIndex *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MetaTagDescrEnumIndex_dump(p, tab);
	return err;
}

void Dz1MetaTagDescrEnumTable_dump(Dz1MetaTagDescrEnumTable *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MetaTagDescrEnumTable_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagDescrEnumTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnums
Dz1MetaTagDescrEnums *Dz1MetaTagDescrEnums_new(Dz1MetaTagDescrEnumsAdd add, 
											   Dz1MetaTagDescrEnumsFind find, 
											   Dz1MetaTagDescrEnumsExtract extract, 
											   Dz1MetaTagDescrEnumsGetArray get_array, 
											   Dz1MetaTagDescrEnumsGetLast getTail, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrEnums *__internal_ret = (Dz1MetaTagDescrEnums *)Dz1Calloc(sizeof(Dz1MetaTagDescrEnums), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnums_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->values = Dz1MetaTagDescrEnumList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->strings = Dz1MetaTagDescrEnumTable_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->add = add;
			__internal_ret->find = find;
			__internal_ret->extract = extract;
			__internal_ret->get_array = get_array;
			__internal_ret->getTail = getTail;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnums_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDescrEnums_purge(Dz1MetaTagDescrEnums *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrEnumList_del(p->values);
	Dz1MetaTagDescrEnumTable_del(p->strings);
}

void Dz1MetaTagDescrEnums_del(Dz1MetaTagDescrEnums *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrEnums_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescrEnums_dump(Dz1MetaTagDescrEnums *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("values = ")); Dz1MetaTagDescrEnumList_dump(p->values, tab); 
		Dz1Thread_tprintf(tab, Dz1T("strings = ")); Dz1MetaTagDescrEnumTable_dump(p->strings, tab); 
		Dz1Thread_tprintf(tab, Dz1T("add = %p\n"), p->add);
		Dz1Thread_tprintf(tab, Dz1T("find = %p\n"), p->find);
		Dz1Thread_tprintf(tab, Dz1T("extract = %p\n"), p->extract);
		Dz1Thread_tprintf(tab, Dz1T("get_array = %p\n"), p->get_array);
		Dz1Thread_tprintf(tab, Dz1T("getTail = %p\n"), p->getTail);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagDescrEnums
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrDate8Mode
static struct Dz1MetaTagDescrDate8ModeMapA
{
	str_t str;
	Dz1MetaTagDescrDate8Mode v;
} Dz1MetaTagDescrDate8ModeMapA[] =
{
	{ (char *)"even", Dz1MetaTagDescrDate8Mode_even },
	{ (char *)"odd", Dz1MetaTagDescrDate8Mode_odd },
	{ NULL, Dz1MetaTagDescrDate8Mode_max }
};

str_t Dz1MetaTagDescrDate8ModeStrA(Dz1MetaTagDescrDate8Mode v)
{
	struct Dz1MetaTagDescrDate8ModeMapA *i = NULL;
	for (i = Dz1MetaTagDescrDate8ModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagDescrDate8Mode Dz1MetaTagDescrDate8ModeFromStrA(str_t str)
{
	struct Dz1MetaTagDescrDate8ModeMapA *i = NULL;
	for (i = Dz1MetaTagDescrDate8ModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagDescrDate8Mode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MetaTagDescrDate8ModeMapW
{
	wstr_t str;
	Dz1MetaTagDescrDate8Mode v;
} Dz1MetaTagDescrDate8ModeMapW[] =
{
	{ (wchar_t *)L"even", Dz1MetaTagDescrDate8Mode_even },
	{ (wchar_t *)L"odd", Dz1MetaTagDescrDate8Mode_odd },
	{ NULL, Dz1MetaTagDescrDate8Mode_max }
};

wstr_t Dz1MetaTagDescrDate8ModeStrW(Dz1MetaTagDescrDate8Mode v)
{
	struct Dz1MetaTagDescrDate8ModeMapW *i = NULL;
	for (i = Dz1MetaTagDescrDate8ModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagDescrDate8Mode Dz1MetaTagDescrDate8ModeFromStrW(wstr_t str)
{
	struct Dz1MetaTagDescrDate8ModeMapW *i = NULL;
	for (i = Dz1MetaTagDescrDate8ModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagDescrDate8Mode_max;
}
#endif // UNIX_SYSTEM

Dz1MetaTagDescrDate8Mode *Dz1MetaTagDescrDate8Mode_new(Dz1MetaTagDescrDate8Mode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrDate8Mode *__internal_ret = (Dz1MetaTagDescrDate8Mode *)Dz1Calloc(sizeof(Dz1MetaTagDescrDate8Mode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1MetaTagDescrDate8Mode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrDate
Dz1MetaTagDescrDate *Dz1MetaTagDescrDate_new(Dz1MetaTagDescrDate8Mode date8, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrDate *__internal_ret = (Dz1MetaTagDescrDate *)Dz1Calloc(sizeof(Dz1MetaTagDescrDate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrDate_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->date8 = date8;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrDate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MetaTagDescrDate_copy(Dz1MetaTagDescrDate *dst, Dz1MetaTagDescrDate *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->date8 = src->date8;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MetaTagDescrDate *Dz1MetaTagDescrDate_clone(Dz1MetaTagDescrDate *src, Dz1Error *err)
{
	Dz1MetaTagDescrDate *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MetaTagDescrDate *)Dz1Calloc(sizeof(Dz1MetaTagDescrDate), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrDate_delAndSetNull, (void *)&dst);
		if (Dz1MetaTagDescrDate_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrDate_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MetaTagDescrDate_purge(Dz1MetaTagDescrDate *p)
{
	if (p == NULL) return;
}

void Dz1MetaTagDescrDate_del(Dz1MetaTagDescrDate *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrDate_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescrDate_dump(Dz1MetaTagDescrDate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("date8 = %s(%d)\n"), Dz1MetaTagDescrDate8ModeStr(p->date8), p->date8);
	}
}
// Dz1MetaTagDescrDate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrAlias
Dz1MetaTagDescrAlias *Dz1MetaTagDescrAlias_new(u32_t origin_descr_id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrAlias *__internal_ret = (Dz1MetaTagDescrAlias *)Dz1Calloc(sizeof(Dz1MetaTagDescrAlias), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrAlias_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->origin_descr_id = origin_descr_id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrAlias_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDescrAlias_purge(Dz1MetaTagDescrAlias *p)
{
	if (p == NULL) return;
}

void Dz1MetaTagDescrAlias_del(Dz1MetaTagDescrAlias *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrAlias_purge(p);
	Dz1Free(p);
}

// Dz1MetaTagDescrAlias
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescriptorUser
Dz1MetaTagDescriptorUser *Dz1MetaTagDescriptorUser_new(u32_t userHandlingType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescriptorUser *__internal_ret = (Dz1MetaTagDescriptorUser *)Dz1Calloc(sizeof(Dz1MetaTagDescriptorUser), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescriptorUser_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->userHandlingType = userHandlingType;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescriptorUser_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDescriptorUser_purge(Dz1MetaTagDescriptorUser *p)
{
	if (p == NULL) return;
}

void Dz1MetaTagDescriptorUser_del(Dz1MetaTagDescriptorUser *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescriptorUser_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescriptorUser_dump(Dz1MetaTagDescriptorUser *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("userHandlingType = ")); Dz1u32_dump(&p->userHandlingType, tab); 
	}
}
// Dz1MetaTagDescriptorUser
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescriptorPresent
static struct Dz1MetaTagDescriptorPresentMapA
{
	str_t str;
	Dz1MetaTagDescriptorPresent v;
} Dz1MetaTagDescriptorPresentMapA[] =
{
	{ (char *)"no_data", Dz1MetaTagDescriptorPresent_no_data },
	{ (char *)"number", Dz1MetaTagDescriptorPresent_number },
	{ (char *)"floating", Dz1MetaTagDescriptorPresent_floating },
	{ (char *)"grade", Dz1MetaTagDescriptorPresent_grade },
	{ (char *)"enumerate", Dz1MetaTagDescriptorPresent_enumerate },
	{ (char *)"date", Dz1MetaTagDescriptorPresent_date },
	{ (char *)"tim", Dz1MetaTagDescriptorPresent_tim },
	{ (char *)"date_time", Dz1MetaTagDescriptorPresent_date_time },
	{ (char *)"string", Dz1MetaTagDescriptorPresent_string },
	{ (char *)"web_url", Dz1MetaTagDescriptorPresent_web_url },
	{ (char *)"binary", Dz1MetaTagDescriptorPresent_binary },
	{ (char *)"user", Dz1MetaTagDescriptorPresent_user },
	{ (char *)"alias", Dz1MetaTagDescriptorPresent_alias },
	{ NULL, Dz1MetaTagDescriptorPresent_max }
};

str_t Dz1MetaTagDescriptorPresentStrA(Dz1MetaTagDescriptorPresent v)
{
	struct Dz1MetaTagDescriptorPresentMapA *i = NULL;
	for (i = Dz1MetaTagDescriptorPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagDescriptorPresent Dz1MetaTagDescriptorPresentFromStrA(str_t str)
{
	struct Dz1MetaTagDescriptorPresentMapA *i = NULL;
	for (i = Dz1MetaTagDescriptorPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagDescriptorPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MetaTagDescriptorPresentMapW
{
	wstr_t str;
	Dz1MetaTagDescriptorPresent v;
} Dz1MetaTagDescriptorPresentMapW[] =
{
	{ (wchar_t *)L"no_data", Dz1MetaTagDescriptorPresent_no_data },
	{ (wchar_t *)L"number", Dz1MetaTagDescriptorPresent_number },
	{ (wchar_t *)L"floating", Dz1MetaTagDescriptorPresent_floating },
	{ (wchar_t *)L"grade", Dz1MetaTagDescriptorPresent_grade },
	{ (wchar_t *)L"enumerate", Dz1MetaTagDescriptorPresent_enumerate },
	{ (wchar_t *)L"date", Dz1MetaTagDescriptorPresent_date },
	{ (wchar_t *)L"tim", Dz1MetaTagDescriptorPresent_tim },
	{ (wchar_t *)L"date_time", Dz1MetaTagDescriptorPresent_date_time },
	{ (wchar_t *)L"string", Dz1MetaTagDescriptorPresent_string },
	{ (wchar_t *)L"web_url", Dz1MetaTagDescriptorPresent_web_url },
	{ (wchar_t *)L"binary", Dz1MetaTagDescriptorPresent_binary },
	{ (wchar_t *)L"user", Dz1MetaTagDescriptorPresent_user },
	{ (wchar_t *)L"alias", Dz1MetaTagDescriptorPresent_alias },
	{ NULL, Dz1MetaTagDescriptorPresent_max }
};

wstr_t Dz1MetaTagDescriptorPresentStrW(Dz1MetaTagDescriptorPresent v)
{
	struct Dz1MetaTagDescriptorPresentMapW *i = NULL;
	for (i = Dz1MetaTagDescriptorPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagDescriptorPresent Dz1MetaTagDescriptorPresentFromStrW(wstr_t str)
{
	struct Dz1MetaTagDescriptorPresentMapW *i = NULL;
	for (i = Dz1MetaTagDescriptorPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagDescriptorPresent_max;
}
#endif // UNIX_SYSTEM

Dz1MetaTagDescriptorPresent *Dz1MetaTagDescriptorPresent_new(Dz1MetaTagDescriptorPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescriptorPresent *__internal_ret = (Dz1MetaTagDescriptorPresent *)Dz1Calloc(sizeof(Dz1MetaTagDescriptorPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1MetaTagDescriptorPresent_dump(Dz1MetaTagDescriptorPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1MetaTagDescriptorPresentStr(*v));
}
// Dz1MetaTagDescriptorPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescriptor
Dz1MetaTagDescriptor *Dz1MetaTagDescriptor_new(Dz1MetaTagDescriptorPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescriptor *ret = (Dz1MetaTagDescriptor *)Dz1Calloc(sizeof(Dz1MetaTagDescriptor), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1MetaTagDescriptorPresent_no_data:
			// _U_prim_clone
			if (ptr != NULL) ret->x.no_data = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_number:
			// _U_cst_clone
			if (ptr != NULL) ret->x.number = (Dz1MetaTagDescrNumber *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_floating:
			// _U_cst_clone
			if (ptr != NULL) ret->x.floating = (Dz1MetaTagDescrFloat *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_grade:
			// _U_cst_clone
			if (ptr != NULL) ret->x.grade = (Dz1MetaTagDescrGrade *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_enumerate:
			// _U_cst_clone
			if (ptr != NULL) ret->x.enumerate = (Dz1MetaTagDescrEnums *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_date:
			// _U_cst_clone
			if (ptr != NULL) ret->x.date = (Dz1MetaTagDescrDate *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_tim:
			// _U_prim_clone
			if (ptr != NULL) ret->x.tim = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_date_time:
			// _U_prim_clone
			if (ptr != NULL) ret->x.date_time = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_string:
			// _U_cst_clone
			if (ptr != NULL) ret->x.string = (Dz1MetaTagDescrString *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_web_url:
			// _U_prim_clone
			if (ptr != NULL) ret->x.web_url = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_binary:
			// _U_prim_clone
			if (ptr != NULL) ret->x.binary = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_user:
			// _U_cst_clone
			if (ptr != NULL) ret->x.user = (Dz1MetaTagDescriptorUser *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_alias:
			// _U_cst_clone
			if (ptr != NULL) ret->x.alias = (Dz1MetaTagDescrAlias *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1MetaTagDescriptorPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagDescriptor_purge(Dz1MetaTagDescriptor *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1MetaTagDescriptorPresent_no_data:
		Dz1u32_del(p->x.no_data);
		break;
	case Dz1MetaTagDescriptorPresent_number:
		Dz1MetaTagDescrNumber_del(p->x.number);
		break;
	case Dz1MetaTagDescriptorPresent_floating:
		Dz1MetaTagDescrFloat_del(p->x.floating);
		break;
	case Dz1MetaTagDescriptorPresent_grade:
		Dz1MetaTagDescrGrade_del(p->x.grade);
		break;
	case Dz1MetaTagDescriptorPresent_enumerate:
		Dz1MetaTagDescrEnums_del(p->x.enumerate);
		break;
	case Dz1MetaTagDescriptorPresent_date:
		Dz1MetaTagDescrDate_del(p->x.date);
		break;
	case Dz1MetaTagDescriptorPresent_tim:
		Dz1u32_del(p->x.tim);
		break;
	case Dz1MetaTagDescriptorPresent_date_time:
		Dz1u32_del(p->x.date_time);
		break;
	case Dz1MetaTagDescriptorPresent_string:
		Dz1MetaTagDescrString_del(p->x.string);
		break;
	case Dz1MetaTagDescriptorPresent_web_url:
		Dz1u32_del(p->x.web_url);
		break;
	case Dz1MetaTagDescriptorPresent_binary:
		Dz1u32_del(p->x.binary);
		break;
	case Dz1MetaTagDescriptorPresent_user:
		Dz1MetaTagDescriptorUser_del(p->x.user);
		break;
	case Dz1MetaTagDescriptorPresent_alias:
		Dz1MetaTagDescrAlias_del(p->x.alias);
		break;
	default:
		break;
	}
}

void Dz1MetaTagDescriptor_del(Dz1MetaTagDescriptor *p)
{
	if (!p) return;
	Dz1MetaTagDescriptor_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDescriptor_dump(Dz1MetaTagDescriptor *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1MetaTagDescriptorPresent_no_data:
		Dz1Thread_printf(Dz1T("no_data = ")); Dz1u32_dump(p->x.no_data, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_number:
		Dz1Thread_printf(Dz1T("number = ")); Dz1MetaTagDescrNumber_dump(p->x.number, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_floating:
		Dz1Thread_printf(Dz1T("floating = ")); Dz1MetaTagDescrFloat_dump(p->x.floating, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_grade:
		Dz1Thread_printf(Dz1T("grade = ")); Dz1MetaTagDescrGrade_dump(p->x.grade, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_enumerate:
		Dz1Thread_printf(Dz1T("enumerate = ")); Dz1MetaTagDescrEnums_dump(p->x.enumerate, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_date:
		Dz1Thread_printf(Dz1T("date = ")); Dz1MetaTagDescrDate_dump(p->x.date, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_tim:
		Dz1Thread_printf(Dz1T("tim = ")); Dz1u32_dump(p->x.tim, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_date_time:
		Dz1Thread_printf(Dz1T("date_time = ")); Dz1u32_dump(p->x.date_time, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_string:
		Dz1Thread_printf(Dz1T("string = ")); Dz1MetaTagDescrString_dump(p->x.string, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_web_url:
		Dz1Thread_printf(Dz1T("web_url = ")); Dz1u32_dump(p->x.web_url, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_binary:
		Dz1Thread_printf(Dz1T("binary = ")); Dz1u32_dump(p->x.binary, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_user:
		Dz1Thread_printf(Dz1T("user = ")); Dz1MetaTagDescriptorUser_dump(p->x.user, tab); 
		break;
	case Dz1MetaTagDescriptorPresent_alias:
		Dz1Thread_printf(Dz1T("alias = ")); Dz1MetaTagDescrAlias_dump(p->x.alias, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1MetaTagDescriptor
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataMode
static struct Dz1MetaTagDataModeMapA
{
	str_t str;
	Dz1MetaTagDataMode v;
} Dz1MetaTagDataModeMapA[] =
{
	{ (char *)"Array", Dz1MetaTagDataMode_Array },
	{ (char *)"Single", Dz1MetaTagDataMode_Single },
	{ (char *)"Void", Dz1MetaTagDataMode_Void },
	{ NULL, Dz1MetaTagDataMode_max }
};

str_t Dz1MetaTagDataModeStrA(Dz1MetaTagDataMode v)
{
	struct Dz1MetaTagDataModeMapA *i = NULL;
	for (i = Dz1MetaTagDataModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagDataMode Dz1MetaTagDataModeFromStrA(str_t str)
{
	struct Dz1MetaTagDataModeMapA *i = NULL;
	for (i = Dz1MetaTagDataModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagDataMode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MetaTagDataModeMapW
{
	wstr_t str;
	Dz1MetaTagDataMode v;
} Dz1MetaTagDataModeMapW[] =
{
	{ (wchar_t *)L"Array", Dz1MetaTagDataMode_Array },
	{ (wchar_t *)L"Single", Dz1MetaTagDataMode_Single },
	{ (wchar_t *)L"Void", Dz1MetaTagDataMode_Void },
	{ NULL, Dz1MetaTagDataMode_max }
};

wstr_t Dz1MetaTagDataModeStrW(Dz1MetaTagDataMode v)
{
	struct Dz1MetaTagDataModeMapW *i = NULL;
	for (i = Dz1MetaTagDataModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MetaTagDataMode Dz1MetaTagDataModeFromStrW(wstr_t str)
{
	struct Dz1MetaTagDataModeMapW *i = NULL;
	for (i = Dz1MetaTagDataModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MetaTagDataMode_max;
}
#endif // UNIX_SYSTEM

Dz1MetaTagDataMode *Dz1MetaTagDataMode_new(Dz1MetaTagDataMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDataMode *__internal_ret = (Dz1MetaTagDataMode *)Dz1Calloc(sizeof(Dz1MetaTagDataMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1MetaTagDataMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEntry
Dz1MetaTagDescrEntry *Dz1MetaTagDescrEntry_new(u32_t id, 
											   Dz1Asn1UTF8Str *name, 
											   Dz1MetaTagDescriptor *descr, 
											   bool_t mandatory, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrEntry *__internal_ret = (Dz1MetaTagDescrEntry *)Dz1Calloc(sizeof(Dz1MetaTagDescrEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		__internal_ret->name = name;
		__internal_ret->descr = descr;
		__internal_ret->mandatory = mandatory;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDescrEntry_purge(Dz1MetaTagDescrEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
	dz1_built_in_wstr_del(p->name_w);
	Dz1MetaTagRestrict_del(p->status);
	Dz1MetaTagDescriptor_del(p->descr);
}

void Dz1MetaTagDescrEntry_del(Dz1MetaTagDescrEntry *p)
{
	if (p == NULL) return;
	Dz1MetaTagDescrEntry_purge(p);
	Dz1Free(p);
}

int Dz1MetaTagDescrEntry_cmp(Dz1MetaTagDescrEntry *a, Dz1MetaTagDescrEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// Dz1MetaTagDescrEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrList
static Dz1Error Dz1MetaTagDescrList_add(Dz1MetaTagDescrList *p, Dz1MetaTagDescrEntry *data)
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

static bool_t Dz1MetaTagDescrList_remove(Dz1MetaTagDescrList *p, Dz1MetaTagDescrEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MetaTagDescrEntry *Dz1MetaTagDescrList_extract(Dz1MetaTagDescrList *p, Dz1MetaTagDescrEntry *key)
{
	return (Dz1MetaTagDescrEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MetaTagDescrListMkArrArg
{
	Dz1MetaTagDescrEntry **arr;
	unsigned int idx;
} Dz1MetaTagDescrListMkArrArg;

static Dz1Error _Dz1MetaTagDescrList_get_array(void *ptr, Dz1MetaTagDescrEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagDescrListMkArrArg *arg = (Dz1MetaTagDescrListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MetaTagDescrEntry **Dz1MetaTagDescrList_get_array(Dz1MetaTagDescrList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MetaTagDescrEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MetaTagDescrEntry **)Dz1Calloc(sizeof(Dz1MetaTagDescrEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MetaTagDescrList_get_array, (void *)&arg);
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

static Dz1Error Dz1MetaTagDescrList_travelForward(Dz1MetaTagDescrList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MetaTagDescrList_travelBackward(Dz1MetaTagDescrList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MetaTagDescrEntry *Dz1MetaTagDescrList_find(Dz1MetaTagDescrList *p, Dz1MetaTagDescrEntry *key)
{
	return (Dz1MetaTagDescrEntry *)Dz1AATree_find(p->storage, key);
}

static Dz1MetaTagDescrEntry *Dz1MetaTagDescrList_getTail(Dz1MetaTagDescrList *p)
{
	return (Dz1MetaTagDescrEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int Dz1MetaTagDescrList_count(Dz1MetaTagDescrList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MetaTagDescrList *Dz1MetaTagDescrList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDescrList *ret = (Dz1MetaTagDescrList *)Dz1Calloc(sizeof(Dz1MetaTagDescrList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MetaTagDescrEntry_cmp,
				(Dz1DelFunc)Dz1MetaTagDescrEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MetaTagDescrList_count;
			ret->travel = Dz1MetaTagDescrList_travelForward;
			ret->travelForward = Dz1MetaTagDescrList_travelForward;
			ret->travelBackward = Dz1MetaTagDescrList_travelBackward;
			ret->get_array = Dz1MetaTagDescrList_get_array;
			ret->add = Dz1MetaTagDescrList_add;
			ret->remove = Dz1MetaTagDescrList_remove;
			ret->find = Dz1MetaTagDescrList_find;
			ret->extract = Dz1MetaTagDescrList_extract;
			ret->getTail = Dz1MetaTagDescrList_getTail;
			ret->cmp = Dz1MetaTagDescrEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagDescrList_purge(Dz1MetaTagDescrList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MetaTagDescrList_del(Dz1MetaTagDescrList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MetaTagDescrList_dump(void *ptr, Dz1MetaTagDescrEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MetaTagDescrEntry_dump(p, tab);
	return err;
}

void Dz1MetaTagDescrList_dump(Dz1MetaTagDescrList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MetaTagDescrList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagDescrList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagUserTypeEntry
Dz1MetaTagUserTypeEntry *Dz1MetaTagUserTypeEntry_new(u32_t userType, 
													 Dz1Asn1UTF8Str *userTypeName, 
													 void *resource, 
													 Dz1DelFunc resource_del, 
													 Dz1DumpFunc resource_dump, 
													 void *userData, 
													 Dz1DelFunc userDataDel, 
													 Dz1DumpFunc userDataDump, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagUserTypeEntry *__internal_ret = (Dz1MetaTagUserTypeEntry *)Dz1Calloc(sizeof(Dz1MetaTagUserTypeEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagUserTypeEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->userType = userType;
		__internal_ret->userTypeName = userTypeName;
		__internal_ret->resource = resource;
		__internal_ret->resource_del = resource_del;
		__internal_ret->resource_dump = resource_dump;
		__internal_ret->userData = userData;
		__internal_ret->userDataDel = userDataDel;
		__internal_ret->userDataDump = userDataDump;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagUserTypeEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagUserTypeEntry_dump(Dz1MetaTagUserTypeEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("userType = ")); Dz1u32_dump(&p->userType, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("userTypeName = ")); Dz1Asn1UTF8Str_dump(p->userTypeName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("resource = %p\n"), p->resource);
		Dz1Thread_tprintf(tab, Dz1T("resource_del = %p\n"), p->resource_del);
		Dz1Thread_tprintf(tab, Dz1T("resource_dump = %p\n"), p->resource_dump);
		Dz1Thread_tprintf(tab, Dz1T("userData = %p\n"), p->userData);
		Dz1Thread_tprintf(tab, Dz1T("userDataDel = %p\n"), p->userDataDel);
		Dz1Thread_tprintf(tab, Dz1T("userDataDump = %p\n"), p->userDataDump);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1MetaTagUserTypeEntry_cmp(Dz1MetaTagUserTypeEntry *a, Dz1MetaTagUserTypeEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->userType, &b->userType)) != 0) { }
	return ret;
}
// Dz1MetaTagUserTypeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagUserTypeList
static Dz1Error Dz1MetaTagUserTypeList_add(Dz1MetaTagUserTypeList *p, Dz1MetaTagUserTypeEntry *data)
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

static bool_t Dz1MetaTagUserTypeList_remove(Dz1MetaTagUserTypeList *p, Dz1MetaTagUserTypeEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1MetaTagUserTypeEntry *Dz1MetaTagUserTypeList_extract(Dz1MetaTagUserTypeList *p, Dz1MetaTagUserTypeEntry *key)
{
	return (Dz1MetaTagUserTypeEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1MetaTagUserTypeListMkArrArg
{
	Dz1MetaTagUserTypeEntry **arr;
	unsigned int idx;
} Dz1MetaTagUserTypeListMkArrArg;

static Dz1Error _Dz1MetaTagUserTypeList_get_array(void *ptr, Dz1MetaTagUserTypeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MetaTagUserTypeListMkArrArg *arg = (Dz1MetaTagUserTypeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MetaTagUserTypeEntry **Dz1MetaTagUserTypeList_get_array(Dz1MetaTagUserTypeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1MetaTagUserTypeEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MetaTagUserTypeEntry **)Dz1Calloc(sizeof(Dz1MetaTagUserTypeEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagUserTypeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1MetaTagUserTypeList_get_array, (void *)&arg);
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

static Dz1Error Dz1MetaTagUserTypeList_travelForward(Dz1MetaTagUserTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagUserTypeEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1MetaTagUserTypeList_travelBackward(Dz1MetaTagUserTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagUserTypeEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1MetaTagUserTypeEntry *Dz1MetaTagUserTypeList_find(Dz1MetaTagUserTypeList *p, Dz1MetaTagUserTypeEntry *key)
{
	return (Dz1MetaTagUserTypeEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1MetaTagUserTypeList_count(Dz1MetaTagUserTypeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1MetaTagUserTypeList *Dz1MetaTagUserTypeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagUserTypeList *ret = (Dz1MetaTagUserTypeList *)Dz1Calloc(sizeof(Dz1MetaTagUserTypeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagUserTypeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1MetaTagUserTypeEntry_cmp,
				(Dz1DelFunc)Dz1MetaTagUserTypeEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MetaTagUserTypeList_count;
			ret->travel = Dz1MetaTagUserTypeList_travelForward;
			ret->travelForward = Dz1MetaTagUserTypeList_travelForward;
			ret->travelBackward = Dz1MetaTagUserTypeList_travelBackward;
			ret->get_array = Dz1MetaTagUserTypeList_get_array;
			ret->add = Dz1MetaTagUserTypeList_add;
			ret->remove = Dz1MetaTagUserTypeList_remove;
			ret->find = Dz1MetaTagUserTypeList_find;
			ret->extract = Dz1MetaTagUserTypeList_extract;
			ret->cmp = Dz1MetaTagUserTypeEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagUserTypeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagUserTypeList_purge(Dz1MetaTagUserTypeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1MetaTagUserTypeList_del(Dz1MetaTagUserTypeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MetaTagUserTypeList_dump(void *ptr, Dz1MetaTagUserTypeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MetaTagUserTypeEntry_dump(p, tab);
	return err;
}

void Dz1MetaTagUserTypeList_dump(Dz1MetaTagUserTypeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MetaTagUserTypeList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagUserTypeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDB
Dz1MetaTagDB *Dz1MetaTagDB_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MetaTagDB *__internal_ret = (Dz1MetaTagDB *)Dz1Calloc(sizeof(Dz1MetaTagDB), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDB_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->types = Dz1MetaTargetTypeList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->table = Dz1MetaTagDescrList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->userTypes = Dz1MetaTagUserTypeList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDB_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1MetaTagDB_purge(Dz1MetaTagDB *p)
{
	if (p == NULL) return;
	Dz1MetaTargetTypeList_del(p->types);
	Dz1MetaTagDescrList_del(p->table);
	Dz1MetaTagUserTypeList_del(p->userTypes);
}

void Dz1MetaTagDB_del(Dz1MetaTagDB *p)
{
	if (p == NULL) return;
	Dz1MetaTagDB_purge(p);
	Dz1Free(p);
}

void Dz1MetaTagDB_dump(Dz1MetaTagDB *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("types = ")); Dz1MetaTargetTypeList_dump(p->types, tab); 
		Dz1Thread_tprintf(tab, Dz1T("table = ")); Dz1MetaTagDescrList_dump(p->table, tab); 
		Dz1Thread_tprintf(tab, Dz1T("userTypes = ")); Dz1MetaTagUserTypeList_dump(p->userTypes, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1MetaTagDB
////////////////////////////////////////////////////////////////////////////////

