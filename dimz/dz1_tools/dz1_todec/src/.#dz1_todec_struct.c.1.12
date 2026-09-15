////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_todec_struct.h"

////////////////////////////////////////////////////////////////////////////////
// PointerNodeEntry
PointerNodeEntry *PointerNodeEntry_new(u32_t idx, 
									   ObjectInfo *obj/*_ref*/, 
									   str_t name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PointerNodeEntry *__internal_ret = (PointerNodeEntry *)Dz1Calloc(sizeof(PointerNodeEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PointerNodeEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = dz1_built_in_str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->idx = idx;
			__internal_ret->obj = obj;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PointerNodeEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PointerNodeEntry_copy(PointerNodeEntry *dst, PointerNodeEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = dz1_built_in_str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->idx = src->idx;
		dst->obj = src->obj;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PointerNodeEntry *PointerNodeEntry_clone(PointerNodeEntry *src, Dz1Error *err)
{
	PointerNodeEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PointerNodeEntry *)Dz1Calloc(sizeof(PointerNodeEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PointerNodeEntry_delAndSetNull, (void *)&dst);
		if (PointerNodeEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PointerNodeEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PointerNodeEntry_purge(PointerNodeEntry *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->name);
}

void PointerNodeEntry_del(PointerNodeEntry *p)
{
	if (p == NULL) return;
	PointerNodeEntry_purge(p);
	Dz1Free(p);
}

void PointerNodeEntry_dump(PointerNodeEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("idx = ")); Dz1u32_dump(&p->idx, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("obj = %p\n"), p->obj);
		Dz1Thread_tprintf(tab, Dz1T("name = ")); dz1_built_in_str_dump(p->name, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int PointerNodeEntry_cmp(PointerNodeEntry *a, PointerNodeEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->idx, &b->idx)) != 0) { }
	return ret;
}
// PointerNodeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PointerNodeList
static Dz1Error PointerNodeList_add(PointerNodeList *p, PointerNodeEntry *data)
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

static bool_t PointerNodeList_remove(PointerNodeList *p, PointerNodeEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static PointerNodeEntry *PointerNodeList_extract(PointerNodeList *p, PointerNodeEntry *key)
{
	return (PointerNodeEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct PointerNodeListMkArrArg
{
	PointerNodeEntry **arr;
	unsigned int idx;
} PointerNodeListMkArrArg;

static Dz1Error _PointerNodeList_get_array(void *ptr, PointerNodeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PointerNodeListMkArrArg *arg = (PointerNodeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static PointerNodeEntry **PointerNodeList_get_array(PointerNodeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	PointerNodeEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (PointerNodeEntry **)Dz1Calloc(sizeof(PointerNodeEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		PointerNodeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _PointerNodeList_get_array, (void *)&arg);
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

static Dz1Error PointerNodeList_travelForward(PointerNodeList *p, Dz1Error (*func)(void *ptr, PointerNodeEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error PointerNodeList_travelBackward(PointerNodeList *p, Dz1Error (*func)(void *ptr, PointerNodeEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static PointerNodeEntry *PointerNodeList_find(PointerNodeList *p, PointerNodeEntry *key)
{
	return (PointerNodeEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int PointerNodeList_count(PointerNodeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

PointerNodeList *PointerNodeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PointerNodeList *ret = (PointerNodeList *)Dz1Calloc(sizeof(PointerNodeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PointerNodeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)PointerNodeEntry_cmp,
				(Dz1DelFunc)PointerNodeEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = PointerNodeList_count;
			ret->travel = PointerNodeList_travelForward;
			ret->travelForward = PointerNodeList_travelForward;
			ret->travelBackward = PointerNodeList_travelBackward;
			ret->get_array = PointerNodeList_get_array;
			ret->add = PointerNodeList_add;
			ret->remove = PointerNodeList_remove;
			ret->find = PointerNodeList_find;
			ret->extract = PointerNodeList_extract;
			ret->cmp = PointerNodeEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PointerNodeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _PointerNodeList_clone(void *ptr, PointerNodeEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PointerNodeList *p = (PointerNodeList *)ptr;
	PointerNodeEntry *cloned = PointerNodeEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

PointerNodeList *PointerNodeList_clone(PointerNodeList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PointerNodeList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = PointerNodeList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PointerNodeList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_PointerNodeList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (PointerNodeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PointerNodeList_purge(PointerNodeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void PointerNodeList_del(PointerNodeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _PointerNodeList_dump(void *ptr, PointerNodeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); PointerNodeEntry_dump(p, tab);
	return err;
}

void PointerNodeList_dump(PointerNodeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _PointerNodeList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PointerNodeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementSimplePartial
StreamElementSimplePartial *StreamElementSimplePartial_new(str_t byte_tp, 
														   Dz1TodecUnitSize byte_sz, 
														   str_t dst_tp, 
														   str_t mask, 
														   s32_t shf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementSimplePartial *__internal_ret = (StreamElementSimplePartial *)Dz1Calloc(sizeof(StreamElementSimplePartial), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementSimplePartial_delAndSetNull, (void *)&__internal_ret);
		
		if (byte_tp && (__internal_ret->byte_tp = dz1_built_in_str_clone(byte_tp, errp)) == NULL) ERR_OUT(errp);
		else if (dst_tp && (__internal_ret->dst_tp = dz1_built_in_str_clone(dst_tp, errp)) == NULL) ERR_OUT(errp);
		else if (mask && (__internal_ret->mask = dz1_built_in_str_clone(mask, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->byte_sz = byte_sz;
			__internal_ret->shf = shf;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementSimplePartial_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamElementSimplePartial_copy(StreamElementSimplePartial *dst, StreamElementSimplePartial *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->byte_tp && (dst->byte_tp = dz1_built_in_str_clone(src->byte_tp, errp)) == NULL) ERR_OUT(errp);
	else if (src->dst_tp && (dst->dst_tp = dz1_built_in_str_clone(src->dst_tp, errp)) == NULL) ERR_OUT(errp);
	else if (src->mask && (dst->mask = dz1_built_in_str_clone(src->mask, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->byte_sz = src->byte_sz;
		dst->shf = src->shf;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementSimplePartial *StreamElementSimplePartial_clone(StreamElementSimplePartial *src, Dz1Error *err)
{
	StreamElementSimplePartial *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamElementSimplePartial *)Dz1Calloc(sizeof(StreamElementSimplePartial), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementSimplePartial_delAndSetNull, (void *)&dst);
		if (StreamElementSimplePartial_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementSimplePartial_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamElementSimplePartial_purge(StreamElementSimplePartial *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->byte_tp);
	dz1_built_in_str_del(p->dst_tp);
	dz1_built_in_str_del(p->mask);
}

void StreamElementSimplePartial_del(StreamElementSimplePartial *p)
{
	if (p == NULL) return;
	StreamElementSimplePartial_purge(p);
	Dz1Free(p);
}

void StreamElementSimplePartial_dump(StreamElementSimplePartial *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("byte_tp = ")); dz1_built_in_str_dump(p->byte_tp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("byte_sz = %s(%d)\n"), Dz1TodecUnitSizeStr(p->byte_sz), p->byte_sz);
		Dz1Thread_tprintf(tab, Dz1T("dst_tp = ")); dz1_built_in_str_dump(p->dst_tp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("mask = ")); dz1_built_in_str_dump(p->mask, tab); 
		Dz1Thread_tprintf(tab, Dz1T("shf = ")); Dz1s32_dump(&p->shf, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamElementSimplePartial
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementSimpleMethodPresent
static struct StreamElementSimpleMethodPresentMapA
{
	str_t str;
	StreamElementSimpleMethodPresent v;
} StreamElementSimpleMethodPresentMapA[] =
{
	{ (char *)"def", StreamElementSimpleMethodPresent_def },
	{ (char *)"part", StreamElementSimpleMethodPresent_part },
	{ (char *)"restricted", StreamElementSimpleMethodPresent_restricted },
	{ (char *)"alter", StreamElementSimpleMethodPresent_alter },
	{ NULL, StreamElementSimpleMethodPresent_max }
};

str_t StreamElementSimpleMethodPresentStrA(StreamElementSimpleMethodPresent v)
{
	struct StreamElementSimpleMethodPresentMapA *i = NULL;
	for (i = StreamElementSimpleMethodPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

StreamElementSimpleMethodPresent StreamElementSimpleMethodPresentFromStrA(str_t str)
{
	struct StreamElementSimpleMethodPresentMapA *i = NULL;
	for (i = StreamElementSimpleMethodPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return StreamElementSimpleMethodPresent_max;
}
#ifndef UNIX_SYSTEM
static struct StreamElementSimpleMethodPresentMapW
{
	wstr_t str;
	StreamElementSimpleMethodPresent v;
} StreamElementSimpleMethodPresentMapW[] =
{
	{ (wchar_t *)L"def", StreamElementSimpleMethodPresent_def },
	{ (wchar_t *)L"part", StreamElementSimpleMethodPresent_part },
	{ (wchar_t *)L"restricted", StreamElementSimpleMethodPresent_restricted },
	{ (wchar_t *)L"alter", StreamElementSimpleMethodPresent_alter },
	{ NULL, StreamElementSimpleMethodPresent_max }
};

wstr_t StreamElementSimpleMethodPresentStrW(StreamElementSimpleMethodPresent v)
{
	struct StreamElementSimpleMethodPresentMapW *i = NULL;
	for (i = StreamElementSimpleMethodPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

StreamElementSimpleMethodPresent StreamElementSimpleMethodPresentFromStrW(wstr_t str)
{
	struct StreamElementSimpleMethodPresentMapW *i = NULL;
	for (i = StreamElementSimpleMethodPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return StreamElementSimpleMethodPresent_max;
}
#endif // UNIX_SYSTEM

StreamElementSimpleMethodPresent *StreamElementSimpleMethodPresent_new(StreamElementSimpleMethodPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementSimpleMethodPresent *__internal_ret = (StreamElementSimpleMethodPresent *)Dz1Calloc(sizeof(StreamElementSimpleMethodPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void StreamElementSimpleMethodPresent_dump(StreamElementSimpleMethodPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), StreamElementSimpleMethodPresentStr(*v));
}
// StreamElementSimpleMethodPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementSimpleMethod
StreamElementSimpleMethod *StreamElementSimpleMethod_new(StreamElementSimpleMethodPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementSimpleMethod *ret = (StreamElementSimpleMethod *)Dz1Calloc(sizeof(StreamElementSimpleMethod), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementSimpleMethod_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case StreamElementSimpleMethodPresent_def:
			// _U_prim_clone
			if (ptr != NULL) ret->x.def = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementSimpleMethodPresent_part:
			// _U_cst_clone
			if (ptr != NULL) ret->x.part = (StreamElementSimplePartial *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementSimpleMethodPresent_restricted:
			// _U_cst_clone
			if (ptr != NULL) ret->x.restricted = (Dz1TodecRestrictDescr *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementSimpleMethodPresent_alter:
			// _U_prim_clone
			if (ptr && (ret->x.alter = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementSimpleMethodPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementSimpleMethod_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t StreamElementSimpleMethod_copy(StreamElementSimpleMethod *ret, StreamElementSimpleMethod *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case StreamElementSimpleMethodPresent_def:
			// _U_prim_clone
			if (src->x.def && (ret->x.def = Dz1u32_clone(src->x.def, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementSimpleMethodPresent_part:
			// _U_cst_clone
			if (src->x.part && (ret->x.part = StreamElementSimplePartial_clone(src->x.part, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementSimpleMethodPresent_restricted:
			// _U_cst_clone
			if (src->x.restricted && (ret->x.restricted = Dz1TodecRestrictDescr_clone(src->x.restricted, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementSimpleMethodPresent_alter:
			// _U_prim_clone
			if (src->x.alter && (ret->x.alter = dz1_built_in_str_clone(src->x.alter, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementSimpleMethod *StreamElementSimpleMethod_clone(StreamElementSimpleMethod *src, Dz1Error *err)
{
	StreamElementSimpleMethod *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (StreamElementSimpleMethod *)Dz1Calloc(sizeof(StreamElementSimpleMethod), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementSimpleMethod_delAndSetNull, (void *)&ret);
		if (StreamElementSimpleMethod_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementSimpleMethod_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StreamElementSimpleMethod_purge(StreamElementSimpleMethod *p)
{
	if (!p) return;
	switch(p->present)
	{
	case StreamElementSimpleMethodPresent_def:
		Dz1u32_del(p->x.def);
		break;
	case StreamElementSimpleMethodPresent_part:
		StreamElementSimplePartial_del(p->x.part);
		break;
	case StreamElementSimpleMethodPresent_restricted:
		Dz1TodecRestrictDescr_del(p->x.restricted);
		break;
	case StreamElementSimpleMethodPresent_alter:
		dz1_built_in_str_del(p->x.alter);
		break;
	default:
		break;
	}
}

void StreamElementSimpleMethod_del(StreamElementSimpleMethod *p)
{
	if (!p) return;
	StreamElementSimpleMethod_purge(p);
	Dz1Free(p);
}

void StreamElementSimpleMethod_dump(StreamElementSimpleMethod *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case StreamElementSimpleMethodPresent_def:
		Dz1Thread_printf(Dz1T("def = ")); Dz1u32_dump(p->x.def, tab); 
		break;
	case StreamElementSimpleMethodPresent_part:
		Dz1Thread_printf(Dz1T("part = ")); StreamElementSimplePartial_dump(p->x.part, tab); 
		break;
	case StreamElementSimpleMethodPresent_restricted:
		Dz1Thread_printf(Dz1T("restricted.")); Dz1TodecRestrictDescr_dump(p->x.restricted, tab); 
		break;
	case StreamElementSimpleMethodPresent_alter:
		Dz1Thread_printf(Dz1T("alter = ")); dz1_built_in_str_dump(p->x.alter, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// StreamElementSimpleMethod
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementVariable
StreamElementVariable *StreamElementVariable_new(ObjectInfo *target/*_ref*/, 
												 ObjectInfo *origin/*_ref*/, 
												 ObjectInfo *mother/*_ref*/, 
												 str_t variable, 
												 bool_t var_is_ptr, 
												 str_t instance, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementVariable *__internal_ret = (StreamElementVariable *)Dz1Calloc(sizeof(StreamElementVariable), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementVariable_delAndSetNull, (void *)&__internal_ret);
		
		if (variable && (__internal_ret->variable = dz1_built_in_str_clone(variable, errp)) == NULL) ERR_OUT(errp);
		else if (instance && (__internal_ret->instance = dz1_built_in_str_clone(instance, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->ptrs = PointerNodeList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->target = target;
			__internal_ret->origin = origin;
			__internal_ret->mother = mother;
			__internal_ret->var_is_ptr = var_is_ptr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementVariable_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamElementVariable_copy(StreamElementVariable *dst, StreamElementVariable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ptrs && (dst->ptrs = PointerNodeList_clone(src->ptrs, errp)) == NULL) ERR_OUT(errp);
	else if (src->variable && (dst->variable = dz1_built_in_str_clone(src->variable, errp)) == NULL) ERR_OUT(errp);
	else if (src->instance && (dst->instance = dz1_built_in_str_clone(src->instance, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->target = src->target;
		dst->origin = src->origin;
		dst->mother = src->mother;
		dst->var_is_ptr = src->var_is_ptr;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementVariable *StreamElementVariable_clone(StreamElementVariable *src, Dz1Error *err)
{
	StreamElementVariable *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamElementVariable *)Dz1Calloc(sizeof(StreamElementVariable), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementVariable_delAndSetNull, (void *)&dst);
		if (StreamElementVariable_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementVariable_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamElementVariable_purge(StreamElementVariable *p)
{
	if (p == NULL) return;
	PointerNodeList_del(p->ptrs);
	dz1_built_in_str_del(p->variable);
	dz1_built_in_str_del(p->instance);
}

void StreamElementVariable_del(StreamElementVariable *p)
{
	if (p == NULL) return;
	StreamElementVariable_purge(p);
	Dz1Free(p);
}

void StreamElementVariable_dump(StreamElementVariable *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("target = %p\n"), p->target);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("origin = %p\n"), p->origin);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("mother = %p\n"), p->mother);
		Dz1Thread_tprintf(tab, Dz1T("ptrs = ")); PointerNodeList_dump(p->ptrs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("variable = ")); dz1_built_in_str_dump(p->variable, tab); 
		Dz1Thread_tprintf(tab, Dz1T("var_is_ptr = ")); Dz1Bool_dump(&p->var_is_ptr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("instance = ")); dz1_built_in_str_dump(p->instance, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamElementVariable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementSimple
StreamElementSimple *StreamElementSimple_new(StreamElementVariable *var, 
											 StreamElementSimpleMethod *met, 
											 Dz1TodecUnitSize nul_flag, 
											 str_t postfix, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementSimple *__internal_ret = (StreamElementSimple *)Dz1Calloc(sizeof(StreamElementSimple), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementSimple_delAndSetNull, (void *)&__internal_ret);
		
		if (postfix && (__internal_ret->postfix = dz1_built_in_str_clone(postfix, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->var = var;
			__internal_ret->met = met;
			__internal_ret->nul_flag = nul_flag;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementSimple_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamElementSimple_copy(StreamElementSimple *dst, StreamElementSimple *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->var && (dst->var = StreamElementVariable_clone(src->var, errp)) == NULL) ERR_OUT(errp);
	else if (src->met && (dst->met = StreamElementSimpleMethod_clone(src->met, errp)) == NULL) ERR_OUT(errp);
	else if (src->postfix && (dst->postfix = dz1_built_in_str_clone(src->postfix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->nul_flag = src->nul_flag;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementSimple *StreamElementSimple_clone(StreamElementSimple *src, Dz1Error *err)
{
	StreamElementSimple *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamElementSimple *)Dz1Calloc(sizeof(StreamElementSimple), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementSimple_delAndSetNull, (void *)&dst);
		if (StreamElementSimple_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementSimple_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamElementSimple_purge(StreamElementSimple *p)
{
	if (p == NULL) return;
	StreamElementVariable_del(p->var);
	StreamElementSimpleMethod_del(p->met);
	dz1_built_in_str_del(p->postfix);
}

void StreamElementSimple_del(StreamElementSimple *p)
{
	if (p == NULL) return;
	StreamElementSimple_purge(p);
	Dz1Free(p);
}

void StreamElementSimple_dump(StreamElementSimple *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("var = ")); StreamElementVariable_dump(p->var, tab); 
		Dz1Thread_tprintf(tab, Dz1T("met.")); StreamElementSimpleMethod_dump(p->met, tab); 
		Dz1Thread_tprintf(tab, Dz1T("nul_flag = %s(%d)\n"), Dz1TodecUnitSizeStr(p->nul_flag), p->nul_flag);
		Dz1Thread_tprintf(tab, Dz1T("postfix = ")); dz1_built_in_str_dump(p->postfix, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamElementSimple
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementConditional
StreamElementConditional *StreamElementConditional_new(StreamElementVariable *var, 
													   str_t decider, 
													   StreamElementSimpleMethod *met, 
													   str_t postfix, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementConditional *__internal_ret = (StreamElementConditional *)Dz1Calloc(sizeof(StreamElementConditional), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementConditional_delAndSetNull, (void *)&__internal_ret);
		
		if (decider && (__internal_ret->decider = dz1_built_in_str_clone(decider, errp)) == NULL) ERR_OUT(errp);
		else if (postfix && (__internal_ret->postfix = dz1_built_in_str_clone(postfix, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->var = var;
			__internal_ret->met = met;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementConditional_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamElementConditional_copy(StreamElementConditional *dst, StreamElementConditional *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->var && (dst->var = StreamElementVariable_clone(src->var, errp)) == NULL) ERR_OUT(errp);
	else if (src->decider && (dst->decider = dz1_built_in_str_clone(src->decider, errp)) == NULL) ERR_OUT(errp);
	else if (src->met && (dst->met = StreamElementSimpleMethod_clone(src->met, errp)) == NULL) ERR_OUT(errp);
	else if (src->postfix && (dst->postfix = dz1_built_in_str_clone(src->postfix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementConditional *StreamElementConditional_clone(StreamElementConditional *src, Dz1Error *err)
{
	StreamElementConditional *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamElementConditional *)Dz1Calloc(sizeof(StreamElementConditional), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementConditional_delAndSetNull, (void *)&dst);
		if (StreamElementConditional_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementConditional_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamElementConditional_purge(StreamElementConditional *p)
{
	if (p == NULL) return;
	StreamElementVariable_del(p->var);
	dz1_built_in_str_del(p->decider);
	StreamElementSimpleMethod_del(p->met);
	dz1_built_in_str_del(p->postfix);
}

void StreamElementConditional_del(StreamElementConditional *p)
{
	if (p == NULL) return;
	StreamElementConditional_purge(p);
	Dz1Free(p);
}

void StreamElementConditional_dump(StreamElementConditional *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("var = ")); StreamElementVariable_dump(p->var, tab); 
		Dz1Thread_tprintf(tab, Dz1T("decider = ")); dz1_built_in_str_dump(p->decider, tab); 
		Dz1Thread_tprintf(tab, Dz1T("met.")); StreamElementSimpleMethod_dump(p->met, tab); 
		Dz1Thread_tprintf(tab, Dz1T("postfix = ")); dz1_built_in_str_dump(p->postfix, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamElementConditional
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementBitInfo
StreamElementBitInfo *StreamElementBitInfo_new(StreamElementVariable *var, 
											   Dz1TodecBitDescr *met, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementBitInfo *__internal_ret = (StreamElementBitInfo *)Dz1Calloc(sizeof(StreamElementBitInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementBitInfo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->var = var;
		__internal_ret->met = met;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementBitInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamElementBitInfo_copy(StreamElementBitInfo *dst, StreamElementBitInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->var && (dst->var = StreamElementVariable_clone(src->var, errp)) == NULL) ERR_OUT(errp);
	else if (src->met && (dst->met = Dz1TodecBitDescr_clone(src->met, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementBitInfo *StreamElementBitInfo_clone(StreamElementBitInfo *src, Dz1Error *err)
{
	StreamElementBitInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamElementBitInfo *)Dz1Calloc(sizeof(StreamElementBitInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementBitInfo_delAndSetNull, (void *)&dst);
		if (StreamElementBitInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementBitInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamElementBitInfo_purge(StreamElementBitInfo *p)
{
	if (p == NULL) return;
	StreamElementVariable_del(p->var);
	Dz1TodecBitDescr_del(p->met);
}

void StreamElementBitInfo_del(StreamElementBitInfo *p)
{
	if (p == NULL) return;
	StreamElementBitInfo_purge(p);
	Dz1Free(p);
}

void StreamElementBitInfo_dump(StreamElementBitInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("var = ")); StreamElementVariable_dump(p->var, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("met = ")); Dz1TodecBitDescr_dump(p->met, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamElementBitInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementBitPresent
static struct StreamElementBitPresentMapA
{
	str_t str;
	StreamElementBitPresent v;
} StreamElementBitPresentMapA[] =
{
	{ (char *)"data", StreamElementBitPresent_data },
	{ (char *)"pad", StreamElementBitPresent_pad },
	{ NULL, StreamElementBitPresent_max }
};

str_t StreamElementBitPresentStrA(StreamElementBitPresent v)
{
	struct StreamElementBitPresentMapA *i = NULL;
	for (i = StreamElementBitPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

StreamElementBitPresent StreamElementBitPresentFromStrA(str_t str)
{
	struct StreamElementBitPresentMapA *i = NULL;
	for (i = StreamElementBitPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return StreamElementBitPresent_max;
}
#ifndef UNIX_SYSTEM
static struct StreamElementBitPresentMapW
{
	wstr_t str;
	StreamElementBitPresent v;
} StreamElementBitPresentMapW[] =
{
	{ (wchar_t *)L"data", StreamElementBitPresent_data },
	{ (wchar_t *)L"pad", StreamElementBitPresent_pad },
	{ NULL, StreamElementBitPresent_max }
};

wstr_t StreamElementBitPresentStrW(StreamElementBitPresent v)
{
	struct StreamElementBitPresentMapW *i = NULL;
	for (i = StreamElementBitPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

StreamElementBitPresent StreamElementBitPresentFromStrW(wstr_t str)
{
	struct StreamElementBitPresentMapW *i = NULL;
	for (i = StreamElementBitPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return StreamElementBitPresent_max;
}
#endif // UNIX_SYSTEM

StreamElementBitPresent *StreamElementBitPresent_new(StreamElementBitPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementBitPresent *__internal_ret = (StreamElementBitPresent *)Dz1Calloc(sizeof(StreamElementBitPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void StreamElementBitPresent_dump(StreamElementBitPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), StreamElementBitPresentStr(*v));
}
// StreamElementBitPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementBit
StreamElementBit *StreamElementBit_new(StreamElementBitPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementBit *ret = (StreamElementBit *)Dz1Calloc(sizeof(StreamElementBit), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementBit_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case StreamElementBitPresent_data:
			// _U_cst_clone
			if (ptr != NULL) ret->x.data = (StreamElementBitInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementBitPresent_pad:
			// _U_prim_clone
			if (ptr != NULL) ret->x.pad = *(u8_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementBitPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementBit_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t StreamElementBit_copy(StreamElementBit *ret, StreamElementBit *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case StreamElementBitPresent_data:
			// _U_cst_clone
			if (src->x.data && (ret->x.data = StreamElementBitInfo_clone(src->x.data, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementBitPresent_pad:
			// _U_prim_clone
			ret->x.pad = src->x.pad;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementBit *StreamElementBit_clone(StreamElementBit *src, Dz1Error *err)
{
	StreamElementBit *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (StreamElementBit *)Dz1Calloc(sizeof(StreamElementBit), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementBit_delAndSetNull, (void *)&ret);
		if (StreamElementBit_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementBit_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StreamElementBit_purge(StreamElementBit *p)
{
	if (!p) return;
	switch(p->present)
	{
	case StreamElementBitPresent_data:
		StreamElementBitInfo_del(p->x.data);
		break;
	case StreamElementBitPresent_pad:
		break;
	default:
		break;
	}
}

void StreamElementBit_del(StreamElementBit *p)
{
	if (!p) return;
	StreamElementBit_purge(p);
	Dz1Free(p);
}

void StreamElementBit_dump(StreamElementBit *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case StreamElementBitPresent_data:
		Dz1Thread_printf(Dz1T("data = ")); StreamElementBitInfo_dump(p->x.data, tab); 
		break;
	case StreamElementBitPresent_pad:
		Dz1Thread_printf(Dz1T("pad = ")); Dz1u8_dump(&p->x.pad, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// StreamElementBit
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementBits
static Dz1Error StreamElementBits_add(StreamElementBits *p, StreamElementBit *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct StreamElementBitsMkArrArg
{
	StreamElementBit **arr;
	unsigned int idx;
} StreamElementBitsMkArrArg;

static Dz1Error _StreamElementBits_get_array(void *ptr, StreamElementBit *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StreamElementBitsMkArrArg *arg = (StreamElementBitsMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static StreamElementBit **StreamElementBits_get_array(StreamElementBits *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	StreamElementBit **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (StreamElementBit **)Dz1Calloc(sizeof(StreamElementBit *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		StreamElementBitsMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _StreamElementBits_get_array, (void *)&arg);
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

static Dz1Error StreamElementBits_travelForward(StreamElementBits *p, Dz1Error (*func)(void *ptr, StreamElementBit *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error StreamElementBits_travelBackward(StreamElementBits *p, Dz1Error (*func)(void *ptr, StreamElementBit *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int StreamElementBits_count(StreamElementBits *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

StreamElementBits *StreamElementBits_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementBits *ret = (StreamElementBits *)Dz1Calloc(sizeof(StreamElementBits), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamElementBits_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)StreamElementBit_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = StreamElementBits_count;
			ret->travel = StreamElementBits_travelForward;
			ret->travelForward = StreamElementBits_travelForward;
			ret->travelBackward = StreamElementBits_travelBackward;
			ret->get_array = StreamElementBits_get_array;
			ret->add = StreamElementBits_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementBits_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _StreamElementBits_clone(void *ptr, StreamElementBit *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StreamElementBits *p = (StreamElementBits *)ptr;
	StreamElementBit *cloned = StreamElementBit_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

StreamElementBits *StreamElementBits_clone(StreamElementBits *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementBits *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = StreamElementBits_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamElementBits_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_StreamElementBits_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementBits_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StreamElementBits_purge(StreamElementBits *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void StreamElementBits_del(StreamElementBits *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _StreamElementBits_dump(void *ptr, StreamElementBit *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); StreamElementBit_dump(p, tab);
	return err;
}

void StreamElementBits_dump(StreamElementBits *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _StreamElementBits_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamElementBits
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementComplex
StreamElementComplex *StreamElementComplex_new(Dz1TodecUnitSize stream_sz, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementComplex *__internal_ret = (StreamElementComplex *)Dz1Calloc(sizeof(StreamElementComplex), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementComplex_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->seq = StreamElementBits_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->stream_sz = stream_sz;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementComplex_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamElementComplex_copy(StreamElementComplex *dst, StreamElementComplex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->seq && (dst->seq = StreamElementBits_clone(src->seq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->stream_sz = src->stream_sz;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementComplex *StreamElementComplex_clone(StreamElementComplex *src, Dz1Error *err)
{
	StreamElementComplex *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamElementComplex *)Dz1Calloc(sizeof(StreamElementComplex), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementComplex_delAndSetNull, (void *)&dst);
		if (StreamElementComplex_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementComplex_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamElementComplex_purge(StreamElementComplex *p)
{
	if (p == NULL) return;
	StreamElementBits_del(p->seq);
}

void StreamElementComplex_del(StreamElementComplex *p)
{
	if (p == NULL) return;
	StreamElementComplex_purge(p);
	Dz1Free(p);
}

void StreamElementComplex_dump(StreamElementComplex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("stream_sz = %s(%d)\n"), Dz1TodecUnitSizeStr(p->stream_sz), p->stream_sz);
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); StreamElementBits_dump(p->seq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamElementComplex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementInfoPresent
static struct StreamElementInfoPresentMapA
{
	str_t str;
	StreamElementInfoPresent v;
} StreamElementInfoPresentMapA[] =
{
	{ (char *)"complex", StreamElementInfoPresent_complex },
	{ (char *)"simple", StreamElementInfoPresent_simple },
	{ (char *)"conditional", StreamElementInfoPresent_conditional },
	{ (char *)"pad", StreamElementInfoPresent_pad },
	{ (char *)"value", StreamElementInfoPresent_value },
	{ (char *)"omit", StreamElementInfoPresent_omit },
	{ NULL, StreamElementInfoPresent_max }
};

str_t StreamElementInfoPresentStrA(StreamElementInfoPresent v)
{
	struct StreamElementInfoPresentMapA *i = NULL;
	for (i = StreamElementInfoPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

StreamElementInfoPresent StreamElementInfoPresentFromStrA(str_t str)
{
	struct StreamElementInfoPresentMapA *i = NULL;
	for (i = StreamElementInfoPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return StreamElementInfoPresent_max;
}
#ifndef UNIX_SYSTEM
static struct StreamElementInfoPresentMapW
{
	wstr_t str;
	StreamElementInfoPresent v;
} StreamElementInfoPresentMapW[] =
{
	{ (wchar_t *)L"complex", StreamElementInfoPresent_complex },
	{ (wchar_t *)L"simple", StreamElementInfoPresent_simple },
	{ (wchar_t *)L"conditional", StreamElementInfoPresent_conditional },
	{ (wchar_t *)L"pad", StreamElementInfoPresent_pad },
	{ (wchar_t *)L"value", StreamElementInfoPresent_value },
	{ (wchar_t *)L"omit", StreamElementInfoPresent_omit },
	{ NULL, StreamElementInfoPresent_max }
};

wstr_t StreamElementInfoPresentStrW(StreamElementInfoPresent v)
{
	struct StreamElementInfoPresentMapW *i = NULL;
	for (i = StreamElementInfoPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

StreamElementInfoPresent StreamElementInfoPresentFromStrW(wstr_t str)
{
	struct StreamElementInfoPresentMapW *i = NULL;
	for (i = StreamElementInfoPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return StreamElementInfoPresent_max;
}
#endif // UNIX_SYSTEM

StreamElementInfoPresent *StreamElementInfoPresent_new(StreamElementInfoPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementInfoPresent *__internal_ret = (StreamElementInfoPresent *)Dz1Calloc(sizeof(StreamElementInfoPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void StreamElementInfoPresent_dump(StreamElementInfoPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), StreamElementInfoPresentStr(*v));
}
// StreamElementInfoPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementInfo
StreamElementInfo *StreamElementInfo_new(StreamElementInfoPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementInfo *ret = (StreamElementInfo *)Dz1Calloc(sizeof(StreamElementInfo), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamElementInfo_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case StreamElementInfoPresent_complex:
			// _U_cst_clone
			if (ptr != NULL) ret->x.complex = (StreamElementComplex *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementInfoPresent_simple:
			// _U_cst_clone
			if (ptr != NULL) ret->x.simple = (StreamElementSimple *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementInfoPresent_conditional:
			// _U_cst_clone
			if (ptr != NULL) ret->x.conditional = (StreamElementConditional *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementInfoPresent_pad:
			// _U_prim_clone
			if (ptr != NULL) ret->x.pad = *(u16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementInfoPresent_value:
			// _U_imp_clone
			if (ptr != NULL) ret->x.value = (Dz1Binary *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementInfoPresent_omit:
			// _U_cst_clone
			if (ptr != NULL) ret->x.omit = (StreamElementVariable *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamElementInfoPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t StreamElementInfo_copy(StreamElementInfo *ret, StreamElementInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case StreamElementInfoPresent_complex:
			// _U_cst_clone
			if (src->x.complex && (ret->x.complex = StreamElementComplex_clone(src->x.complex, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementInfoPresent_simple:
			// _U_cst_clone
			if (src->x.simple && (ret->x.simple = StreamElementSimple_clone(src->x.simple, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementInfoPresent_conditional:
			// _U_cst_clone
			if (src->x.conditional && (ret->x.conditional = StreamElementConditional_clone(src->x.conditional, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementInfoPresent_pad:
			// _U_prim_clone
			ret->x.pad = src->x.pad;
			ERR_CLEAR(errp);
			break;
		case StreamElementInfoPresent_value:
			// _U_imp_clone
			if (src->x.value && (ret->x.value = Dz1Binary_clone(src->x.value, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamElementInfoPresent_omit:
			// _U_cst_clone
			if (src->x.omit && (ret->x.omit = StreamElementVariable_clone(src->x.omit, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamElementInfo *StreamElementInfo_clone(StreamElementInfo *src, Dz1Error *err)
{
	StreamElementInfo *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (StreamElementInfo *)Dz1Calloc(sizeof(StreamElementInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamElementInfo_delAndSetNull, (void *)&ret);
		if (StreamElementInfo_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StreamElementInfo_purge(StreamElementInfo *p)
{
	if (!p) return;
	switch(p->present)
	{
	case StreamElementInfoPresent_complex:
		StreamElementComplex_del(p->x.complex);
		break;
	case StreamElementInfoPresent_simple:
		StreamElementSimple_del(p->x.simple);
		break;
	case StreamElementInfoPresent_conditional:
		StreamElementConditional_del(p->x.conditional);
		break;
	case StreamElementInfoPresent_pad:
		break;
	case StreamElementInfoPresent_value:
		Dz1Binary_del(p->x.value);
		break;
	case StreamElementInfoPresent_omit:
		StreamElementVariable_del(p->x.omit);
		break;
	default:
		break;
	}
}

void StreamElementInfo_del(StreamElementInfo *p)
{
	if (!p) return;
	StreamElementInfo_purge(p);
	Dz1Free(p);
}

void StreamElementInfo_dump(StreamElementInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case StreamElementInfoPresent_complex:
		Dz1Thread_printf(Dz1T("complex = ")); StreamElementComplex_dump(p->x.complex, tab); 
		break;
	case StreamElementInfoPresent_simple:
		Dz1Thread_printf(Dz1T("simple = ")); StreamElementSimple_dump(p->x.simple, tab); 
		break;
	case StreamElementInfoPresent_conditional:
		Dz1Thread_printf(Dz1T("conditional = ")); StreamElementConditional_dump(p->x.conditional, tab); 
		break;
	case StreamElementInfoPresent_pad:
		Dz1Thread_printf(Dz1T("pad = ")); Dz1u16_dump(&p->x.pad, tab); 
		break;
	case StreamElementInfoPresent_value:
		Dz1Thread_printf(Dz1T("value = ")); Dz1Binary_dump(p->x.value, tab); 
		break;
	case StreamElementInfoPresent_omit:
		Dz1Thread_printf(Dz1T("omit = ")); StreamElementVariable_dump(p->x.omit, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// StreamElementInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementList
static Dz1Error StreamElementList_add(StreamElementList *p, StreamElementInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct StreamElementListMkArrArg
{
	StreamElementInfo **arr;
	unsigned int idx;
} StreamElementListMkArrArg;

static Dz1Error _StreamElementList_get_array(void *ptr, StreamElementInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StreamElementListMkArrArg *arg = (StreamElementListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static StreamElementInfo **StreamElementList_get_array(StreamElementList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	StreamElementInfo **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (StreamElementInfo **)Dz1Calloc(sizeof(StreamElementInfo *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		StreamElementListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _StreamElementList_get_array, (void *)&arg);
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

static Dz1Error StreamElementList_travelForward(StreamElementList *p, Dz1Error (*func)(void *ptr, StreamElementInfo *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error StreamElementList_travelBackward(StreamElementList *p, Dz1Error (*func)(void *ptr, StreamElementInfo *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int StreamElementList_count(StreamElementList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

StreamElementList *StreamElementList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementList *ret = (StreamElementList *)Dz1Calloc(sizeof(StreamElementList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamElementList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)StreamElementInfo_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = StreamElementList_count;
			ret->travel = StreamElementList_travelForward;
			ret->travelForward = StreamElementList_travelForward;
			ret->travelBackward = StreamElementList_travelBackward;
			ret->get_array = StreamElementList_get_array;
			ret->add = StreamElementList_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _StreamElementList_clone(void *ptr, StreamElementInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StreamElementList *p = (StreamElementList *)ptr;
	StreamElementInfo *cloned = StreamElementInfo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

StreamElementList *StreamElementList_clone(StreamElementList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamElementList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = StreamElementList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamElementList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_StreamElementList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamElementList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StreamElementList_purge(StreamElementList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void StreamElementList_del(StreamElementList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _StreamElementList_dump(void *ptr, StreamElementInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); StreamElementInfo_dump(p, tab);
	return err;
}

void StreamElementList_dump(StreamElementList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _StreamElementList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamElementList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamObjectAttrUnion
StreamObjectAttrUnion *StreamObjectAttrUnion_new(StreamElementSimple *pr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamObjectAttrUnion *__internal_ret = (StreamObjectAttrUnion *)Dz1Calloc(sizeof(StreamObjectAttrUnion), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamObjectAttrUnion_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->pr = pr;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamObjectAttrUnion_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamObjectAttrUnion_copy(StreamObjectAttrUnion *dst, StreamObjectAttrUnion *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->pr && (dst->pr = StreamElementSimple_clone(src->pr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamObjectAttrUnion *StreamObjectAttrUnion_clone(StreamObjectAttrUnion *src, Dz1Error *err)
{
	StreamObjectAttrUnion *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamObjectAttrUnion *)Dz1Calloc(sizeof(StreamObjectAttrUnion), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamObjectAttrUnion_delAndSetNull, (void *)&dst);
		if (StreamObjectAttrUnion_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamObjectAttrUnion_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamObjectAttrUnion_purge(StreamObjectAttrUnion *p)
{
	if (p == NULL) return;
	StreamElementSimple_del(p->pr);
}

void StreamObjectAttrUnion_del(StreamObjectAttrUnion *p)
{
	if (p == NULL) return;
	StreamObjectAttrUnion_purge(p);
	Dz1Free(p);
}

void StreamObjectAttrUnion_dump(StreamObjectAttrUnion *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		// Normal member
		Dz1Thread_printf(Dz1T("pr = ")); StreamElementSimple_dump(p->pr, tab); 
	}
}
// StreamObjectAttrUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamObjectAttrArray
StreamObjectAttrArray *StreamObjectAttrArray_new(StreamElementSimple *cnt, 
												 StreamElementSimple *etr, 
												 str_t postfix, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamObjectAttrArray *__internal_ret = (StreamObjectAttrArray *)Dz1Calloc(sizeof(StreamObjectAttrArray), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamObjectAttrArray_delAndSetNull, (void *)&__internal_ret);
		
		if (postfix && (__internal_ret->postfix = dz1_built_in_str_clone(postfix, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->cnt = cnt;
			__internal_ret->etr = etr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamObjectAttrArray_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamObjectAttrArray_copy(StreamObjectAttrArray *dst, StreamObjectAttrArray *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->cnt && (dst->cnt = StreamElementSimple_clone(src->cnt, errp)) == NULL) ERR_OUT(errp);
	else if (src->etr && (dst->etr = StreamElementSimple_clone(src->etr, errp)) == NULL) ERR_OUT(errp);
	else if (src->postfix && (dst->postfix = dz1_built_in_str_clone(src->postfix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamObjectAttrArray *StreamObjectAttrArray_clone(StreamObjectAttrArray *src, Dz1Error *err)
{
	StreamObjectAttrArray *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamObjectAttrArray *)Dz1Calloc(sizeof(StreamObjectAttrArray), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamObjectAttrArray_delAndSetNull, (void *)&dst);
		if (StreamObjectAttrArray_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamObjectAttrArray_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamObjectAttrArray_purge(StreamObjectAttrArray *p)
{
	if (p == NULL) return;
	StreamElementSimple_del(p->cnt);
	StreamElementSimple_del(p->etr);
	dz1_built_in_str_del(p->postfix);
}

void StreamObjectAttrArray_del(StreamObjectAttrArray *p)
{
	if (p == NULL) return;
	StreamObjectAttrArray_purge(p);
	Dz1Free(p);
}

void StreamObjectAttrArray_dump(StreamObjectAttrArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("cnt = ")); StreamElementSimple_dump(p->cnt, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("etr = ")); StreamElementSimple_dump(p->etr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("postfix = ")); dz1_built_in_str_dump(p->postfix, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamObjectAttrArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamObjectAttrPresent
static struct StreamObjectAttrPresentMapA
{
	str_t str;
	StreamObjectAttrPresent v;
} StreamObjectAttrPresentMapA[] =
{
	{ (char *)"st", StreamObjectAttrPresent_st },
	{ (char *)"un", StreamObjectAttrPresent_un },
	{ (char *)"ar", StreamObjectAttrPresent_ar },
	{ NULL, StreamObjectAttrPresent_max }
};

str_t StreamObjectAttrPresentStrA(StreamObjectAttrPresent v)
{
	struct StreamObjectAttrPresentMapA *i = NULL;
	for (i = StreamObjectAttrPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

StreamObjectAttrPresent StreamObjectAttrPresentFromStrA(str_t str)
{
	struct StreamObjectAttrPresentMapA *i = NULL;
	for (i = StreamObjectAttrPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return StreamObjectAttrPresent_max;
}
#ifndef UNIX_SYSTEM
static struct StreamObjectAttrPresentMapW
{
	wstr_t str;
	StreamObjectAttrPresent v;
} StreamObjectAttrPresentMapW[] =
{
	{ (wchar_t *)L"st", StreamObjectAttrPresent_st },
	{ (wchar_t *)L"un", StreamObjectAttrPresent_un },
	{ (wchar_t *)L"ar", StreamObjectAttrPresent_ar },
	{ NULL, StreamObjectAttrPresent_max }
};

wstr_t StreamObjectAttrPresentStrW(StreamObjectAttrPresent v)
{
	struct StreamObjectAttrPresentMapW *i = NULL;
	for (i = StreamObjectAttrPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

StreamObjectAttrPresent StreamObjectAttrPresentFromStrW(wstr_t str)
{
	struct StreamObjectAttrPresentMapW *i = NULL;
	for (i = StreamObjectAttrPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return StreamObjectAttrPresent_max;
}
#endif // UNIX_SYSTEM

StreamObjectAttrPresent *StreamObjectAttrPresent_new(StreamObjectAttrPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamObjectAttrPresent *__internal_ret = (StreamObjectAttrPresent *)Dz1Calloc(sizeof(StreamObjectAttrPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void StreamObjectAttrPresent_dump(StreamObjectAttrPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), StreamObjectAttrPresentStr(*v));
}
// StreamObjectAttrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamObjectAttr
StreamObjectAttr *StreamObjectAttr_new(StreamObjectAttrPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamObjectAttr *ret = (StreamObjectAttr *)Dz1Calloc(sizeof(StreamObjectAttr), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamObjectAttr_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case StreamObjectAttrPresent_st:
			// _U_prim_clone
			if (ptr != NULL) ret->x.st = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamObjectAttrPresent_un:
			// _U_cst_clone
			if (ptr != NULL) ret->x.un = (StreamObjectAttrUnion *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamObjectAttrPresent_ar:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ar = (StreamObjectAttrArray *)ptr;
			ERR_CLEAR(errp);
			break;
		case StreamObjectAttrPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamObjectAttr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t StreamObjectAttr_copy(StreamObjectAttr *ret, StreamObjectAttr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case StreamObjectAttrPresent_st:
			// _U_prim_clone
			if (src->x.st && (ret->x.st = Dz1u32_clone(src->x.st, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamObjectAttrPresent_un:
			// _U_cst_clone
			if (src->x.un && (ret->x.un = StreamObjectAttrUnion_clone(src->x.un, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case StreamObjectAttrPresent_ar:
			// _U_cst_clone
			if (src->x.ar && (ret->x.ar = StreamObjectAttrArray_clone(src->x.ar, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamObjectAttr *StreamObjectAttr_clone(StreamObjectAttr *src, Dz1Error *err)
{
	StreamObjectAttr *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (StreamObjectAttr *)Dz1Calloc(sizeof(StreamObjectAttr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamObjectAttr_delAndSetNull, (void *)&ret);
		if (StreamObjectAttr_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamObjectAttr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StreamObjectAttr_purge(StreamObjectAttr *p)
{
	if (!p) return;
	switch(p->present)
	{
	case StreamObjectAttrPresent_st:
		Dz1u32_del(p->x.st);
		break;
	case StreamObjectAttrPresent_un:
		StreamObjectAttrUnion_del(p->x.un);
		break;
	case StreamObjectAttrPresent_ar:
		StreamObjectAttrArray_del(p->x.ar);
		break;
	default:
		break;
	}
}

void StreamObjectAttr_del(StreamObjectAttr *p)
{
	if (!p) return;
	StreamObjectAttr_purge(p);
	Dz1Free(p);
}

void StreamObjectAttr_dump(StreamObjectAttr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case StreamObjectAttrPresent_st:
		Dz1Thread_printf(Dz1T("st = ")); Dz1u32_dump(p->x.st, tab); 
		break;
	case StreamObjectAttrPresent_un:
		Dz1Thread_printf(Dz1T("un = ")); StreamObjectAttrUnion_dump(p->x.un, tab); 
		break;
	case StreamObjectAttrPresent_ar:
		Dz1Thread_printf(Dz1T("ar = ")); StreamObjectAttrArray_dump(p->x.ar, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// StreamObjectAttr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamInfo
StreamInfo *StreamInfo_new(u32_t read_var, 
						   u32_t write_var, 
						   StreamObjectAttr *attr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamInfo *__internal_ret = (StreamInfo *)Dz1Calloc(sizeof(StreamInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StreamInfo_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->seq = StreamElementList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->read_var = read_var;
			__internal_ret->write_var = write_var;
			__internal_ret->attr = attr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StreamInfo_copy(StreamInfo *dst, StreamInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->attr && (dst->attr = StreamObjectAttr_clone(src->attr, errp)) == NULL) ERR_OUT(errp);
	else if (src->seq && (dst->seq = StreamElementList_clone(src->seq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->read_var = src->read_var;
		dst->write_var = src->write_var;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StreamInfo *StreamInfo_clone(StreamInfo *src, Dz1Error *err)
{
	StreamInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StreamInfo *)Dz1Calloc(sizeof(StreamInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StreamInfo_delAndSetNull, (void *)&dst);
		if (StreamInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StreamInfo_purge(StreamInfo *p)
{
	if (p == NULL) return;
	StreamObjectAttr_del(p->attr);
	StreamElementList_del(p->seq);
}

void StreamInfo_del(StreamInfo *p)
{
	if (p == NULL) return;
	StreamInfo_purge(p);
	Dz1Free(p);
}

void StreamInfo_dump(StreamInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("read_var = ")); Dz1u32_dump(&p->read_var, tab); 
		Dz1Thread_tprintf(tab, Dz1T("write_var = ")); Dz1u32_dump(&p->write_var, tab); 
		Dz1Thread_tprintf(tab, Dz1T("attr.")); StreamObjectAttr_dump(p->attr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); StreamElementList_dump(p->seq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamList
static Dz1Error StreamList_add(StreamList *p, StreamInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct StreamListMkArrArg
{
	StreamInfo **arr;
	unsigned int idx;
} StreamListMkArrArg;

static Dz1Error _StreamList_get_array(void *ptr, StreamInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StreamListMkArrArg *arg = (StreamListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static StreamInfo **StreamList_get_array(StreamList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	StreamInfo **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (StreamInfo **)Dz1Calloc(sizeof(StreamInfo *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		StreamListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _StreamList_get_array, (void *)&arg);
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

static Dz1Error StreamList_travelForward(StreamList *p, Dz1Error (*func)(void *ptr, StreamInfo *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error StreamList_travelBackward(StreamList *p, Dz1Error (*func)(void *ptr, StreamInfo *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int StreamList_count(StreamList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

StreamList *StreamList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamList *ret = (StreamList *)Dz1Calloc(sizeof(StreamList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)StreamInfo_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = StreamList_count;
			ret->travel = StreamList_travelForward;
			ret->travelForward = StreamList_travelForward;
			ret->travelBackward = StreamList_travelBackward;
			ret->get_array = StreamList_get_array;
			ret->add = StreamList_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _StreamList_clone(void *ptr, StreamInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StreamList *p = (StreamList *)ptr;
	StreamInfo *cloned = StreamInfo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

StreamList *StreamList_clone(StreamList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StreamList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = StreamList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_StreamList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (StreamList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StreamList_purge(StreamList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void StreamList_del(StreamList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _StreamList_dump(void *ptr, StreamInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); StreamInfo_dump(p, tab);
	return err;
}

void StreamList_dump(StreamList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _StreamList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StreamList
////////////////////////////////////////////////////////////////////////////////

