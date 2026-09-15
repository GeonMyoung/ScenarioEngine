////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "sample.h"

////////////////////////////////////////////////////////////////////////////////
// MyBinDataPresent
static struct MyBinDataPresentMapA
{
	str_t str;
	MyBinDataPresent v;
} MyBinDataPresentMapA[] =
{
	{ (char *)"fn", MyBinDataPresent_fn },
	{ (char *)"buf", MyBinDataPresent_buf },
	{ NULL, MyBinDataPresent_max }
};

str_t MyBinDataPresentStrA(MyBinDataPresent v)
{
	struct MyBinDataPresentMapA *i = NULL;
	for (i = MyBinDataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyBinDataPresent MyBinDataPresentFromStrA(str_t str)
{
	struct MyBinDataPresentMapA *i = NULL;
	for (i = MyBinDataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return MyBinDataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct MyBinDataPresentMapW
{
	wstr_t str;
	MyBinDataPresent v;
} MyBinDataPresentMapW[] =
{
	{ (wchar_t *)L"fn", MyBinDataPresent_fn },
	{ (wchar_t *)L"buf", MyBinDataPresent_buf },
	{ NULL, MyBinDataPresent_max }
};

wstr_t MyBinDataPresentStrW(MyBinDataPresent v)
{
	struct MyBinDataPresentMapW *i = NULL;
	for (i = MyBinDataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyBinDataPresent MyBinDataPresentFromStrW(wstr_t str)
{
	struct MyBinDataPresentMapW *i = NULL;
	for (i = MyBinDataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return MyBinDataPresent_max;
}
#endif // UNIX_SYSTEM

MyBinDataPresent *MyBinDataPresent_new(MyBinDataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyBinDataPresent *__internal_ret = (MyBinDataPresent *)Dz1Calloc(sizeof(MyBinDataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void MyBinDataPresent_dump(MyBinDataPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), MyBinDataPresentStr(*v));
}
// MyBinDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyBinData
MyBinData *MyBinData_new(MyBinDataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyBinData *ret = (MyBinData *)Dz1Calloc(sizeof(MyBinData), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyBinData_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case MyBinDataPresent_fn:
			// _U_prim_clone
			if (ptr && (ret->x.fn = Dz1Str_clone((Dz1Str)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyBinDataPresent_buf:
			// _U_imp_clone
			if (ptr != NULL) ret->x.buf = (Dz1Binary *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyBinDataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyBinData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t MyBinData_copy(MyBinData *ret, MyBinData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case MyBinDataPresent_fn:
			// _U_prim_clone
			if (src->x.fn && (ret->x.fn = Dz1Str_clone(src->x.fn, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyBinDataPresent_buf:
			// _U_imp_clone
			if (src->x.buf && (ret->x.buf = Dz1Binary_clone(src->x.buf, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyBinData *MyBinData_clone(MyBinData *src, Dz1Error *err)
{
	MyBinData *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (MyBinData *)Dz1Calloc(sizeof(MyBinData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyBinData_delAndSetNull, (void *)&ret);
		if (MyBinData_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyBinData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyBinData_purge(MyBinData *p)
{
	if (!p) return;
	switch(p->present)
	{
	case MyBinDataPresent_fn:
		Dz1Str_del(p->x.fn);
		break;
	case MyBinDataPresent_buf:
		Dz1Binary_del(p->x.buf);
		break;
	default:
		break;
	}
}

void MyBinData_del(MyBinData *p)
{
	if (!p) return;
	MyBinData_purge(p);
	Dz1Free(p);
}

void MyBinData_dump(MyBinData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case MyBinDataPresent_fn:
		Dz1Thread_printf(Dz1T("fn = ")); Dz1Str_dump(p->x.fn, tab); 
		break;
	case MyBinDataPresent_buf:
		Dz1Thread_printf(Dz1T("buf = ")); Dz1Binary_dump(p->x.buf, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// MyBinData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRow
MyDataRow *MyDataRow_new(u32_t id, Dz1Str name, MyBinData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRow *__internal_ret = (MyDataRow *)Dz1Calloc(sizeof(MyDataRow), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyDataRow_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->id = id;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRow_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyDataRow_copy(MyDataRow *dst, MyDataRow *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = MyBinData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->id = src->id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyDataRow *MyDataRow_clone(MyDataRow *src, Dz1Error *err)
{
	MyDataRow *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyDataRow *)Dz1Calloc(sizeof(MyDataRow), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyDataRow_delAndSetNull, (void *)&dst);
		if (MyDataRow_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRow_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyDataRow_purge(MyDataRow *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	MyBinData_del(p->data);
}

void MyDataRow_del(MyDataRow *p)
{
	if (p == NULL) return;
	MyDataRow_purge(p);
	Dz1Free(p);
}

void MyDataRow_dump(MyDataRow *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data.")); MyBinData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int MyDataRow_cmp(MyDataRow *a, MyDataRow *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// MyDataRow
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataTbl
static Dz1Error MyDataTbl_add(MyDataTbl *p, MyDataRow *data)
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

static bool_t MyDataTbl_remove(MyDataTbl *p, MyDataRow *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataRow *MyDataTbl_extract(MyDataTbl *p, MyDataRow *key)
{
	return (MyDataRow *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataTblMkArrArg
{
	MyDataRow **arr;
	unsigned int idx;
} MyDataTblMkArrArg;

static Dz1Error _MyDataTbl_get_array(void *ptr, MyDataRow *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataTblMkArrArg *arg = (MyDataTblMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataRow **MyDataTbl_get_array(MyDataTbl *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataRow **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataRow **)Dz1Calloc(sizeof(MyDataRow *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataTblMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataTbl_get_array, (void *)&arg);
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

static Dz1Error MyDataTbl_travelForward(MyDataTbl *p, Dz1Error (*func)(void *ptr, MyDataRow *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataTbl_travelBackward(MyDataTbl *p, Dz1Error (*func)(void *ptr, MyDataRow *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataRow *MyDataTbl_find(MyDataTbl *p, MyDataRow *key)
{
	return (MyDataRow *)Dz1AATree_find(p->storage, key);
}

static MyDataRow *MyDataTbl_getHead(MyDataTbl *p)
{
	return (MyDataRow *)Dz1AATree_getHead(p->storage);
}

static unsigned int MyDataTbl_count(MyDataTbl *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataTbl *MyDataTbl_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataTbl *ret = (MyDataTbl *)Dz1Calloc(sizeof(MyDataTbl), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataTbl_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataRow_cmp,
				(Dz1DelFunc)MyDataRow_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataTbl_count;
			ret->travel = MyDataTbl_travelForward;
			ret->travelForward = MyDataTbl_travelForward;
			ret->travelBackward = MyDataTbl_travelBackward;
			ret->get_array = MyDataTbl_get_array;
			ret->add = MyDataTbl_add;
			ret->remove = MyDataTbl_remove;
			ret->find = MyDataTbl_find;
			ret->extract = MyDataTbl_extract;
			ret->getHead = MyDataTbl_getHead;
			ret->cmp = MyDataRow_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataTbl_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataTbl_clone(void *ptr, MyDataRow *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataTbl *p = (MyDataTbl *)ptr;
	MyDataRow *cloned = MyDataRow_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataTbl *MyDataTbl_clone(MyDataTbl *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataTbl *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataTbl_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataTbl_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataTbl_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataTbl_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataTbl_purge(MyDataTbl *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataTbl_del(MyDataTbl *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataTbl_dump(void *ptr, MyDataRow *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyDataRow_dump(p, tab);
	return err;
}

void MyDataTbl_dump(MyDataTbl *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataTbl_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// MyDataTbl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStructAAAA
MyStructAAAA *MyStructAAAA_new(u64_t my_unum64, s64_t my_num64, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStructAAAA *__internal_ret = (MyStructAAAA *)Dz1Calloc(sizeof(MyStructAAAA), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyStructAAAA_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_unum64 = my_unum64;
		__internal_ret->my_num64 = my_num64;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructAAAA_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyStructAAAA_copy(MyStructAAAA *dst, MyStructAAAA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_str && (dst->my_str = Dz1Str_clone(src->my_str, errp)) == NULL) ERR_OUT(errp);
	else if (src->my_blob && (dst->my_blob = Dz1Binary_clone(src->my_blob, errp)) == NULL) ERR_OUT(errp);
	else if (src->my_blobl && (dst->my_blobl = Dz1Binary_clone(src->my_blobl, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->my_unum64 = src->my_unum64;
		dst->my_num64 = src->my_num64;
		dst->my_unum32 = src->my_unum32;
		dst->my_num32 = src->my_num32;
		dst->my_unum16 = src->my_unum16;
		dst->my_num16 = src->my_num16;
		dst->my_unum8 = src->my_unum8;
		dst->my_num8 = src->my_num8;
		dst->my_real = src->my_real;
		dst->my_date = src->my_date;
		dst->my_clock = src->my_clock;
		dst->my_stamp = src->my_stamp;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyStructAAAA *MyStructAAAA_clone(MyStructAAAA *src, Dz1Error *err)
{
	MyStructAAAA *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyStructAAAA *)Dz1Calloc(sizeof(MyStructAAAA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyStructAAAA_delAndSetNull, (void *)&dst);
		if (MyStructAAAA_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructAAAA_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyStructAAAA_purge(MyStructAAAA *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_str);
	Dz1Binary_del(p->my_blob);
	Dz1Binary_del(p->my_blobl);
}

void MyStructAAAA_del(MyStructAAAA *p)
{
	if (p == NULL) return;
	MyStructAAAA_purge(p);
	Dz1Free(p);
}

void MyStructAAAA_dump(MyStructAAAA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_unum64 = ")); Dz1u64_dump(&p->my_unum64, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_num64 = ")); Dz1s64_dump(&p->my_num64, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_unum32 = ")); Dz1u32_dump(&p->my_unum32, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_num32 = ")); Dz1s32_dump(&p->my_num32, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_unum16 = ")); Dz1u16_dump(&p->my_unum16, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_num16 = ")); Dz1s16_dump(&p->my_num16, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_unum8 = ")); Dz1u8_dump(&p->my_unum8, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_num8 = ")); Dz1s8_dump(&p->my_num8, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_real = ")); Dz1Real64_dump(&p->my_real, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_str = ")); Dz1Str_dump(p->my_str, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_date = ")); time_dump(&p->my_date, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_clock = ")); time_dump(&p->my_clock, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_stamp = ")); time_dump(&p->my_stamp, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_blob = ")); Dz1Binary_dump(p->my_blob, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_blobl = ")); Dz1Binary_dump(p->my_blobl, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int MyStructAAAA_cmp(MyStructAAAA *a, MyStructAAAA *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u64_cmp(&a->my_unum64, &b->my_unum64)) != 0) { }
	return ret;
}
// MyStructAAAA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStructAAAAList
static Dz1Error MyStructAAAAList_add(MyStructAAAAList *p, MyStructAAAA *data)
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

static bool_t MyStructAAAAList_remove(MyStructAAAAList *p, MyStructAAAA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyStructAAAA *MyStructAAAAList_extract(MyStructAAAAList *p, MyStructAAAA *key)
{
	return (MyStructAAAA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyStructAAAAListMkArrArg
{
	MyStructAAAA **arr;
	unsigned int idx;
} MyStructAAAAListMkArrArg;

static Dz1Error _MyStructAAAAList_get_array(void *ptr, MyStructAAAA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStructAAAAListMkArrArg *arg = (MyStructAAAAListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyStructAAAA **MyStructAAAAList_get_array(MyStructAAAAList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyStructAAAA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyStructAAAA **)Dz1Calloc(sizeof(MyStructAAAA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyStructAAAAListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyStructAAAAList_get_array, (void *)&arg);
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

static Dz1Error MyStructAAAAList_travelForward(MyStructAAAAList *p, Dz1Error (*func)(void *ptr, MyStructAAAA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyStructAAAAList_travelBackward(MyStructAAAAList *p, Dz1Error (*func)(void *ptr, MyStructAAAA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyStructAAAA *MyStructAAAAList_find(MyStructAAAAList *p, MyStructAAAA *key)
{
	return (MyStructAAAA *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyStructAAAAList_count(MyStructAAAAList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyStructAAAAList *MyStructAAAAList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStructAAAAList *ret = (MyStructAAAAList *)Dz1Calloc(sizeof(MyStructAAAAList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStructAAAAList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyStructAAAA_cmp,
				(Dz1DelFunc)MyStructAAAA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyStructAAAAList_count;
			ret->travel = MyStructAAAAList_travelForward;
			ret->travelForward = MyStructAAAAList_travelForward;
			ret->travelBackward = MyStructAAAAList_travelBackward;
			ret->get_array = MyStructAAAAList_get_array;
			ret->add = MyStructAAAAList_add;
			ret->remove = MyStructAAAAList_remove;
			ret->find = MyStructAAAAList_find;
			ret->extract = MyStructAAAAList_extract;
			ret->cmp = MyStructAAAA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructAAAAList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyStructAAAAList_clone(void *ptr, MyStructAAAA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStructAAAAList *p = (MyStructAAAAList *)ptr;
	MyStructAAAA *cloned = MyStructAAAA_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyStructAAAAList *MyStructAAAAList_clone(MyStructAAAAList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStructAAAAList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyStructAAAAList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStructAAAAList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyStructAAAAList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructAAAAList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyStructAAAAList_purge(MyStructAAAAList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyStructAAAAList_del(MyStructAAAAList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyStructAAAAList_dump(void *ptr, MyStructAAAA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyStructAAAA_dump(p, tab);
	return err;
}

void MyStructAAAAList_dump(MyStructAAAAList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyStructAAAAList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// MyStructAAAAList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStructBBBB
MyStructBBBB *MyStructBBBB_new(u64_t my_unum64, s64_t my_num64, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStructBBBB *__internal_ret = (MyStructBBBB *)Dz1Calloc(sizeof(MyStructBBBB), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyStructBBBB_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_unum64 = my_unum64;
		__internal_ret->my_num64 = my_num64;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructBBBB_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyStructBBBB_copy(MyStructBBBB *dst, MyStructBBBB *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->my_unum64 = src->my_unum64;
		dst->my_num64 = src->my_num64;
		dst->my_unum32 = src->my_unum32;
		dst->my_num32 = src->my_num32;
		dst->my_unum16 = src->my_unum16;
		dst->my_num16 = src->my_num16;
		dst->my_unum8 = src->my_unum8;
		dst->my_num8 = src->my_num8;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyStructBBBB *MyStructBBBB_clone(MyStructBBBB *src, Dz1Error *err)
{
	MyStructBBBB *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyStructBBBB *)Dz1Calloc(sizeof(MyStructBBBB), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyStructBBBB_delAndSetNull, (void *)&dst);
		if (MyStructBBBB_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructBBBB_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyStructBBBB_purge(MyStructBBBB *p)
{
	if (p == NULL) return;
}

void MyStructBBBB_del(MyStructBBBB *p)
{
	if (p == NULL) return;
	MyStructBBBB_purge(p);
	Dz1Free(p);
}

void MyStructBBBB_dump(MyStructBBBB *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_unum64 = ")); Dz1u64_dump(&p->my_unum64, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_num64 = ")); Dz1s64_dump(&p->my_num64, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_unum32 = ")); Dz1u32_dump(&p->my_unum32, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_num32 = ")); Dz1s32_dump(&p->my_num32, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_unum16 = ")); Dz1u16_dump(&p->my_unum16, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_num16 = ")); Dz1s16_dump(&p->my_num16, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_unum8 = ")); Dz1u8_dump(&p->my_unum8, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_num8 = ")); Dz1s8_dump(&p->my_num8, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int MyStructBBBB_cmp(MyStructBBBB *a, MyStructBBBB *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u64_cmp(&a->my_unum64, &b->my_unum64)) != 0) { }
	else if ((ret = Dz1s64_cmp(&a->my_num64, &b->my_num64)) != 0) { }
	return ret;
}
// MyStructBBBB
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStructBBBBList
static Dz1Error MyStructBBBBList_add(MyStructBBBBList *p, MyStructBBBB *data)
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

static bool_t MyStructBBBBList_remove(MyStructBBBBList *p, MyStructBBBB *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyStructBBBB *MyStructBBBBList_extract(MyStructBBBBList *p, MyStructBBBB *key)
{
	return (MyStructBBBB *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyStructBBBBListMkArrArg
{
	MyStructBBBB **arr;
	unsigned int idx;
} MyStructBBBBListMkArrArg;

static Dz1Error _MyStructBBBBList_get_array(void *ptr, MyStructBBBB *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStructBBBBListMkArrArg *arg = (MyStructBBBBListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyStructBBBB **MyStructBBBBList_get_array(MyStructBBBBList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyStructBBBB **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyStructBBBB **)Dz1Calloc(sizeof(MyStructBBBB *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyStructBBBBListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyStructBBBBList_get_array, (void *)&arg);
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

static Dz1Error MyStructBBBBList_travelForward(MyStructBBBBList *p, Dz1Error (*func)(void *ptr, MyStructBBBB *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyStructBBBBList_travelBackward(MyStructBBBBList *p, Dz1Error (*func)(void *ptr, MyStructBBBB *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyStructBBBB *MyStructBBBBList_find(MyStructBBBBList *p, MyStructBBBB *key)
{
	return (MyStructBBBB *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyStructBBBBList_count(MyStructBBBBList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyStructBBBBList *MyStructBBBBList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStructBBBBList *ret = (MyStructBBBBList *)Dz1Calloc(sizeof(MyStructBBBBList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStructBBBBList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyStructBBBB_cmp,
				(Dz1DelFunc)MyStructBBBB_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyStructBBBBList_count;
			ret->travel = MyStructBBBBList_travelForward;
			ret->travelForward = MyStructBBBBList_travelForward;
			ret->travelBackward = MyStructBBBBList_travelBackward;
			ret->get_array = MyStructBBBBList_get_array;
			ret->add = MyStructBBBBList_add;
			ret->remove = MyStructBBBBList_remove;
			ret->find = MyStructBBBBList_find;
			ret->extract = MyStructBBBBList_extract;
			ret->cmp = MyStructBBBB_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructBBBBList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyStructBBBBList_clone(void *ptr, MyStructBBBB *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStructBBBBList *p = (MyStructBBBBList *)ptr;
	MyStructBBBB *cloned = MyStructBBBB_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyStructBBBBList *MyStructBBBBList_clone(MyStructBBBBList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStructBBBBList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyStructBBBBList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStructBBBBList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyStructBBBBList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructBBBBList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyStructBBBBList_purge(MyStructBBBBList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyStructBBBBList_del(MyStructBBBBList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyStructBBBBList_dump(void *ptr, MyStructBBBB *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyStructBBBB_dump(p, tab);
	return err;
}

void MyStructBBBBList_dump(MyStructBBBBList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyStructBBBBList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// MyStructBBBBList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CentralEntry
CentralEntry *CentralEntry_new(u64_t my_unum64, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CentralEntry *__internal_ret = (CentralEntry *)Dz1Calloc(sizeof(CentralEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CentralEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_unum64 = my_unum64;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CentralEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CentralEntry_copy(CentralEntry *dst, CentralEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_blob && (dst->my_blob = Dz1Binary_clone(src->my_blob, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->my_unum64 = src->my_unum64;
		dst->my_unum32 = src->my_unum32;
		dst->my_unum16 = src->my_unum16;
		dst->value = src->value;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CentralEntry *CentralEntry_clone(CentralEntry *src, Dz1Error *err)
{
	CentralEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CentralEntry *)Dz1Calloc(sizeof(CentralEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CentralEntry_delAndSetNull, (void *)&dst);
		if (CentralEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CentralEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CentralEntry_purge(CentralEntry *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->my_blob);
}

void CentralEntry_del(CentralEntry *p)
{
	if (p == NULL) return;
	CentralEntry_purge(p);
	Dz1Free(p);
}

void CentralEntry_dump(CentralEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_unum64 = ")); Dz1u64_dump(&p->my_unum64, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_unum32 = ")); Dz1u32_dump(&p->my_unum32, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_unum16 = ")); Dz1u16_dump(&p->my_unum16, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_blob = ")); Dz1Binary_dump(p->my_blob, tab); 
		Dz1Thread_tprintf(tab, Dz1T("value = ")); Dz1u64_dump(&p->value, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int CentralEntry_cmp(CentralEntry *a, CentralEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u64_cmp(&a->my_unum64, &b->my_unum64)) != 0) { }
	return ret;
}
// CentralEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CentralList
static Dz1Error CentralList_add(CentralList *p, CentralEntry *data)
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

static bool_t CentralList_remove(CentralList *p, CentralEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static CentralEntry *CentralList_extract(CentralList *p, CentralEntry *key)
{
	return (CentralEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct CentralListMkArrArg
{
	CentralEntry **arr;
	unsigned int idx;
} CentralListMkArrArg;

static Dz1Error _CentralList_get_array(void *ptr, CentralEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CentralListMkArrArg *arg = (CentralListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static CentralEntry **CentralList_get_array(CentralList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	CentralEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (CentralEntry **)Dz1Calloc(sizeof(CentralEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		CentralListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _CentralList_get_array, (void *)&arg);
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

static Dz1Error CentralList_travelForward(CentralList *p, Dz1Error (*func)(void *ptr, CentralEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error CentralList_travelBackward(CentralList *p, Dz1Error (*func)(void *ptr, CentralEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static CentralEntry *CentralList_find(CentralList *p, CentralEntry *key)
{
	return (CentralEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int CentralList_count(CentralList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

CentralList *CentralList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CentralList *ret = (CentralList *)Dz1Calloc(sizeof(CentralList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CentralList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)CentralEntry_cmp,
				(Dz1DelFunc)CentralEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = CentralList_count;
			ret->travel = CentralList_travelForward;
			ret->travelForward = CentralList_travelForward;
			ret->travelBackward = CentralList_travelBackward;
			ret->get_array = CentralList_get_array;
			ret->add = CentralList_add;
			ret->remove = CentralList_remove;
			ret->find = CentralList_find;
			ret->extract = CentralList_extract;
			ret->cmp = CentralEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CentralList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _CentralList_clone(void *ptr, CentralEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CentralList *p = (CentralList *)ptr;
	CentralEntry *cloned = CentralEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

CentralList *CentralList_clone(CentralList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CentralList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = CentralList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CentralList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_CentralList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (CentralList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void CentralList_purge(CentralList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void CentralList_del(CentralList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _CentralList_dump(void *ptr, CentralEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); CentralEntry_dump(p, tab);
	return err;
}

void CentralList_dump(CentralList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _CentralList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CentralList
////////////////////////////////////////////////////////////////////////////////

