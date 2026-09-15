////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "sample.h"

////////////////////////////////////////////////////////////////////////////////
// EnumSample
static struct EnumSampleMapA
{
	str_t str;
	EnumSample v;
} EnumSampleMapA[] =
{
	{ (char *)"value0", EnumSample_value0 },
	{ (char *)"value1", EnumSample_value1 },
	{ (char *)"value2", EnumSample_value2 },
	{ NULL, EnumSample_max }
};

str_t EnumSampleStrA(EnumSample v)
{
	struct EnumSampleMapA *i = NULL;
	for (i = EnumSampleMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

EnumSample EnumSampleFromStrA(str_t str)
{
	struct EnumSampleMapA *i = NULL;
	for (i = EnumSampleMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return EnumSample_max;
}
#ifndef UNIX_SYSTEM
static struct EnumSampleMapW
{
	wstr_t str;
	EnumSample v;
} EnumSampleMapW[] =
{
	{ (wchar_t *)L"value0", EnumSample_value0 },
	{ (wchar_t *)L"value1", EnumSample_value1 },
	{ (wchar_t *)L"value2", EnumSample_value2 },
	{ NULL, EnumSample_max }
};

wstr_t EnumSampleStrW(EnumSample v)
{
	struct EnumSampleMapW *i = NULL;
	for (i = EnumSampleMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

EnumSample EnumSampleFromStrW(wstr_t str)
{
	struct EnumSampleMapW *i = NULL;
	for (i = EnumSampleMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return EnumSample_max;
}
#endif // UNIX_SYSTEM

EnumSample *EnumSample_new(EnumSample *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	EnumSample *__internal_ret = (EnumSample *)Dz1Calloc(sizeof(EnumSample), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// EnumSample
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyData
MyData *MyData_new(u32_t data1, u16_t data2, u8_t data3, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyData *__internal_ret = (MyData *)Dz1Calloc(sizeof(MyData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->data1 = data1;
		__internal_ret->data2 = data2;
		__internal_ret->data3 = data3;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyData_copy(MyData *dst, MyData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->data1 = src->data1;
		dst->data2 = src->data2;
		dst->data3 = src->data3;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyData *MyData_clone(MyData *src, Dz1Error *err)
{
	MyData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyData *)Dz1Calloc(sizeof(MyData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyData_delAndSetNull, (void *)&dst);
		if (MyData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyData_purge(MyData *p)
{
	if (p == NULL) return;
}

void MyData_del(MyData *p)
{
	if (p == NULL) return;
	MyData_purge(p);
	Dz1Free(p);
}

void MyData_dump(MyData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("data1 = ")); Dz1u32_dump(&p->data1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data2 = ")); Dz1u16_dump(&p->data2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data3 = ")); Dz1u8_dump(&p->data3, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int MyData_cmp(MyData *a, MyData *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->data1, &b->data1)) != 0) { }
	return ret;
}
// MyData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StructSample
StructSample *StructSample_new(u32_t data1, 
							   u16_t data2, 
							   u8_t data3, 
							   EnumSample data4, 
							   MyData *data5, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StructSample *__internal_ret = (StructSample *)Dz1Calloc(sizeof(StructSample), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(StructSample_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->data1 = data1;
		__internal_ret->data2 = data2;
		__internal_ret->data3 = data3;
		__internal_ret->data4 = data4;
		__internal_ret->data5 = data5;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StructSample_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t StructSample_copy(StructSample *dst, StructSample *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->data5 && (dst->data5 = MyData_clone(src->data5, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->data1 = src->data1;
		dst->data2 = src->data2;
		dst->data3 = src->data3;
		dst->data4 = src->data4;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

StructSample *StructSample_clone(StructSample *src, Dz1Error *err)
{
	StructSample *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (StructSample *)Dz1Calloc(sizeof(StructSample), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(StructSample_delAndSetNull, (void *)&dst);
		if (StructSample_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StructSample_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void StructSample_purge(StructSample *p)
{
	if (p == NULL) return;
	MyData_del(p->data5);
}

void StructSample_del(StructSample *p)
{
	if (p == NULL) return;
	StructSample_purge(p);
	Dz1Free(p);
}

void StructSample_dump(StructSample *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("data1 = ")); Dz1u32_dump(&p->data1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data2 = ")); Dz1u16_dump(&p->data2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data3 = ")); Dz1u8_dump(&p->data3, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data4 = %s(%d)\n"), EnumSampleStr(p->data4), p->data4);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data5 = ")); MyData_dump(p->data5, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int StructSample_cmp(StructSample *a, StructSample *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->data1, &b->data1)) != 0) { }
	return ret;
}
// StructSample
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StructSampleList
static Dz1Error StructSampleList_add(StructSampleList *p, StructSample *data)
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

static bool_t StructSampleList_remove(StructSampleList *p, StructSample *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static StructSample *StructSampleList_extract(StructSampleList *p, StructSample *key)
{
	return (StructSample *)Dz1AATree_extract(p->storage, key);
}

typedef struct StructSampleListMkArrArg
{
	StructSample **arr;
	unsigned int idx;
} StructSampleListMkArrArg;

static Dz1Error _StructSampleList_get_array(void *ptr, StructSample *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StructSampleListMkArrArg *arg = (StructSampleListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static StructSample **StructSampleList_get_array(StructSampleList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	StructSample **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (StructSample **)Dz1Calloc(sizeof(StructSample *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		StructSampleListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _StructSampleList_get_array, (void *)&arg);
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

static Dz1Error StructSampleList_travelForward(StructSampleList *p, Dz1Error (*func)(void *ptr, StructSample *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error StructSampleList_travelBackward(StructSampleList *p, Dz1Error (*func)(void *ptr, StructSample *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static StructSample *StructSampleList_find(StructSampleList *p, StructSample *key)
{
	return (StructSample *)Dz1AATree_find(p->storage, key);
}

static unsigned int StructSampleList_count(StructSampleList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

StructSampleList *StructSampleList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StructSampleList *ret = (StructSampleList *)Dz1Calloc(sizeof(StructSampleList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StructSampleList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)StructSample_cmp,
				(Dz1DelFunc)StructSample_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = StructSampleList_count;
			ret->travel = StructSampleList_travelForward;
			ret->travelForward = StructSampleList_travelForward;
			ret->travelBackward = StructSampleList_travelBackward;
			ret->get_array = StructSampleList_get_array;
			ret->add = StructSampleList_add;
			ret->remove = StructSampleList_remove;
			ret->find = StructSampleList_find;
			ret->extract = StructSampleList_extract;
			ret->cmp = StructSample_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StructSampleList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _StructSampleList_clone(void *ptr, StructSample *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StructSampleList *p = (StructSampleList *)ptr;
	StructSample *cloned = StructSample_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

StructSampleList *StructSampleList_clone(StructSampleList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StructSampleList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = StructSampleList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StructSampleList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_StructSampleList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (StructSampleList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StructSampleList_purge(StructSampleList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void StructSampleList_del(StructSampleList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _StructSampleList_dump(void *ptr, StructSample *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); StructSample_dump(p, tab);
	return err;
}

void StructSampleList_dump(StructSampleList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _StructSampleList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// StructSampleList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UnionSamplePresent
static struct UnionSamplePresentMapA
{
	str_t str;
	UnionSamplePresent v;
} UnionSamplePresentMapA[] =
{
	{ (char *)"data1", UnionSamplePresent_data1 },
	{ (char *)"data2", UnionSamplePresent_data2 },
	{ (char *)"data3", UnionSamplePresent_data3 },
	{ (char *)"data4", UnionSamplePresent_data4 },
	{ (char *)"data5", UnionSamplePresent_data5 },
	{ NULL, UnionSamplePresent_max }
};

str_t UnionSamplePresentStrA(UnionSamplePresent v)
{
	struct UnionSamplePresentMapA *i = NULL;
	for (i = UnionSamplePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

UnionSamplePresent UnionSamplePresentFromStrA(str_t str)
{
	struct UnionSamplePresentMapA *i = NULL;
	for (i = UnionSamplePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return UnionSamplePresent_max;
}
#ifndef UNIX_SYSTEM
static struct UnionSamplePresentMapW
{
	wstr_t str;
	UnionSamplePresent v;
} UnionSamplePresentMapW[] =
{
	{ (wchar_t *)L"data1", UnionSamplePresent_data1 },
	{ (wchar_t *)L"data2", UnionSamplePresent_data2 },
	{ (wchar_t *)L"data3", UnionSamplePresent_data3 },
	{ (wchar_t *)L"data4", UnionSamplePresent_data4 },
	{ (wchar_t *)L"data5", UnionSamplePresent_data5 },
	{ NULL, UnionSamplePresent_max }
};

wstr_t UnionSamplePresentStrW(UnionSamplePresent v)
{
	struct UnionSamplePresentMapW *i = NULL;
	for (i = UnionSamplePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

UnionSamplePresent UnionSamplePresentFromStrW(wstr_t str)
{
	struct UnionSamplePresentMapW *i = NULL;
	for (i = UnionSamplePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return UnionSamplePresent_max;
}
#endif // UNIX_SYSTEM

UnionSamplePresent *UnionSamplePresent_new(UnionSamplePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	UnionSamplePresent *__internal_ret = (UnionSamplePresent *)Dz1Calloc(sizeof(UnionSamplePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void UnionSamplePresent_dump(UnionSamplePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), UnionSamplePresentStr(*v));
}
// UnionSamplePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UnionSample
UnionSample *UnionSample_new(UnionSamplePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	UnionSample *ret = (UnionSample *)Dz1Calloc(sizeof(UnionSample), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(UnionSample_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case UnionSamplePresent_data1:
			// _U_prim_clone
			if (ptr != NULL) ret->x.data1 = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_data2:
			// _U_prim_clone
			if (ptr != NULL) ret->x.data2 = *(u16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_data3:
			// _U_prim_clone
			if (ptr != NULL) ret->x.data3 = *(u8_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_data4:
			// _U_enum_clone
			if (ptr != NULL) ret->x.data4 = *(EnumSample *)ptr;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_data5:
			// _U_cst_clone
			if (ptr != NULL) ret->x.data5 = (MyData *)ptr;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (UnionSample_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t UnionSample_copy(UnionSample *ret, UnionSample *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case UnionSamplePresent_data1:
			// _U_prim_clone
			ret->x.data1 = src->x.data1;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_data2:
			// _U_prim_clone
			ret->x.data2 = src->x.data2;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_data3:
			// _U_prim_clone
			ret->x.data3 = src->x.data3;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_data4:
			// _U_enum_clone
			ret->x.data4 = src->x.data4;
			ERR_CLEAR(errp);
			break;
		case UnionSamplePresent_data5:
			// _U_cst_clone
			if (src->x.data5 && (ret->x.data5 = MyData_clone(src->x.data5, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

UnionSample *UnionSample_clone(UnionSample *src, Dz1Error *err)
{
	UnionSample *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (UnionSample *)Dz1Calloc(sizeof(UnionSample), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(UnionSample_delAndSetNull, (void *)&ret);
		if (UnionSample_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (UnionSample_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void UnionSample_purge(UnionSample *p)
{
	if (!p) return;
	switch(p->present)
	{
	case UnionSamplePresent_data1:
		break;
	case UnionSamplePresent_data2:
		break;
	case UnionSamplePresent_data3:
		break;
	case UnionSamplePresent_data4:
		break;
	case UnionSamplePresent_data5:
		MyData_del(p->x.data5);
		break;
	default:
		break;
	}
}

void UnionSample_del(UnionSample *p)
{
	if (!p) return;
	UnionSample_purge(p);
	Dz1Free(p);
}

void UnionSample_dump(UnionSample *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case UnionSamplePresent_data1:
		Dz1Thread_printf(Dz1T("data1 = ")); Dz1u32_dump(&p->x.data1, tab); 
		break;
	case UnionSamplePresent_data2:
		Dz1Thread_printf(Dz1T("data2 = ")); Dz1u16_dump(&p->x.data2, tab); 
		break;
	case UnionSamplePresent_data3:
		Dz1Thread_printf(Dz1T("data3 = ")); Dz1u8_dump(&p->x.data3, tab); 
		break;
	case UnionSamplePresent_data4:
		Dz1Thread_printf(Dz1T("data4 = %s(%d)\n"), EnumSampleStr(p->x.data4), p->x.data4);
		break;
	case UnionSamplePresent_data5:
		Dz1Thread_printf(Dz1T("data5 = ")); MyData_dump(p->x.data5, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// UnionSample
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UnionSampleList
static Dz1Error UnionSampleList_add(UnionSampleList *p, UnionSample *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct UnionSampleListMkArrArg
{
	UnionSample **arr;
	unsigned int idx;
} UnionSampleListMkArrArg;

static Dz1Error _UnionSampleList_get_array(void *ptr, UnionSample *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	UnionSampleListMkArrArg *arg = (UnionSampleListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static UnionSample **UnionSampleList_get_array(UnionSampleList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	UnionSample **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (UnionSample **)Dz1Calloc(sizeof(UnionSample *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		UnionSampleListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _UnionSampleList_get_array, (void *)&arg);
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

static Dz1Error UnionSampleList_travelForward(UnionSampleList *p, Dz1Error (*func)(void *ptr, UnionSample *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error UnionSampleList_travelBackward(UnionSampleList *p, Dz1Error (*func)(void *ptr, UnionSample *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int UnionSampleList_count(UnionSampleList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

UnionSampleList *UnionSampleList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	UnionSampleList *ret = (UnionSampleList *)Dz1Calloc(sizeof(UnionSampleList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(UnionSampleList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)UnionSample_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = UnionSampleList_count;
			ret->travel = UnionSampleList_travelForward;
			ret->travelForward = UnionSampleList_travelForward;
			ret->travelBackward = UnionSampleList_travelBackward;
			ret->get_array = UnionSampleList_get_array;
			ret->add = UnionSampleList_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (UnionSampleList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _UnionSampleList_clone(void *ptr, UnionSample *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	UnionSampleList *p = (UnionSampleList *)ptr;
	UnionSample *cloned = UnionSample_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

UnionSampleList *UnionSampleList_clone(UnionSampleList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	UnionSampleList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = UnionSampleList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(UnionSampleList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_UnionSampleList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (UnionSampleList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void UnionSampleList_purge(UnionSampleList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void UnionSampleList_del(UnionSampleList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _UnionSampleList_dump(void *ptr, UnionSample *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); UnionSample_dump(p, tab);
	return err;
}

void UnionSampleList_dump(UnionSampleList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _UnionSampleList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// UnionSampleList
////////////////////////////////////////////////////////////////////////////////

