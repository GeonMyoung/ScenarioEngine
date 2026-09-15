////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_union_test.h"

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataPresent
static struct MyUnionDataPresentMapA
{
	str_t str;
	MyUnionDataPresent v;
} MyUnionDataPresentMapA[] =
{
	{ (char *)"name", MyUnionDataPresent_name },
	{ (char *)"val", MyUnionDataPresent_val },
	{ NULL, MyUnionDataPresent_max }
};

str_t MyUnionDataPresentStrA(MyUnionDataPresent v)
{
	struct MyUnionDataPresentMapA *i = NULL;
	for (i = MyUnionDataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionDataPresent MyUnionDataPresentFromStrA(str_t str)
{
	struct MyUnionDataPresentMapA *i = NULL;
	for (i = MyUnionDataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return MyUnionDataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct MyUnionDataPresentMapW
{
	wstr_t str;
	MyUnionDataPresent v;
} MyUnionDataPresentMapW[] =
{
	{ (wchar_t *)L"name", MyUnionDataPresent_name },
	{ (wchar_t *)L"val", MyUnionDataPresent_val },
	{ NULL, MyUnionDataPresent_max }
};

wstr_t MyUnionDataPresentStrW(MyUnionDataPresent v)
{
	struct MyUnionDataPresentMapW *i = NULL;
	for (i = MyUnionDataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionDataPresent MyUnionDataPresentFromStrW(wstr_t str)
{
	struct MyUnionDataPresentMapW *i = NULL;
	for (i = MyUnionDataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return MyUnionDataPresent_max;
}
#endif // UNIX_SYSTEM

MyUnionDataPresent *MyUnionDataPresent_new(MyUnionDataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataPresent *__internal_ret = (MyUnionDataPresent *)Dz1Calloc(sizeof(MyUnionDataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void MyUnionDataPresent_dump(MyUnionDataPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), MyUnionDataPresentStr(*v));
}
void MyUnionDataPresent_fdump(FILE *fp, MyUnionDataPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), MyUnionDataPresentStr(*v));
}

int MyUnionDataPresent_cmp(MyUnionDataPresent *a, MyUnionDataPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// MyUnionDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionData
MyUnionData *MyUnionData_new(MyUnionDataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionData *ret = (MyUnionData *)Dz1Calloc(sizeof(MyUnionData), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnionData_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case MyUnionDataPresent_name:
			// _U_imp_clone
			if (ptr != NULL) ret->x.name = (Dz1Asn1UTF8Str *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionDataPresent_val:
			// _U_prim_clone
			if (ptr != NULL) ret->x.val = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionDataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t MyUnionData_copy(MyUnionData *ret, MyUnionData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case MyUnionDataPresent_name:
			// _U_imp_clone
			if (src->x.name && (ret->x.name = Dz1Asn1UTF8Str_clone(src->x.name, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyUnionDataPresent_val:
			// _U_prim_clone
			ret->x.val = src->x.val;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyUnionData *MyUnionData_clone(MyUnionData *src, Dz1Error *err)
{
	MyUnionData *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (MyUnionData *)Dz1Calloc(sizeof(MyUnionData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnionData_delAndSetNull, (void *)&ret);
		if (MyUnionData_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionData_purge(MyUnionData *p)
{
	if (!p) return;
	switch(p->present)
	{
	case MyUnionDataPresent_name:
		Dz1Asn1UTF8Str_del(p->x.name);
		break;
	case MyUnionDataPresent_val:
		break;
	default:
		break;
	}
}

void MyUnionData_del(MyUnionData *p)
{
	if (!p) return;
	MyUnionData_purge(p);
	Dz1Free(p);
}

void MyUnionData_dump(MyUnionData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case MyUnionDataPresent_name:
		Dz1Thread_printf(Dz1T("name = ")); Dz1Asn1UTF8Str_dump(p->x.name, tab); 
		break;
	case MyUnionDataPresent_val:
		Dz1Thread_printf(Dz1T("val = ")); Dz1u32_dump(&p->x.val, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}
void MyUnionData_fdump(FILE *fp, MyUnionData *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else switch(p->present)
	{
	case MyUnionDataPresent_name:
		Dz1Thread_fprintf(fp, Dz1T("name = ")); Dz1Asn1UTF8Str_fdump(fp, p->x.name, tab); 
		break;
	case MyUnionDataPresent_val:
		Dz1Thread_fprintf(fp, Dz1T("val = ")); Dz1u32_fdump(fp, &p->x.val, tab); 
		break;
	default:
		Dz1Thread_ftprintf(fp, tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int MyUnionData_cmp(MyUnionData *a, MyUnionData *b)
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
		case MyUnionDataPresent_name:
			if (a->x.name == NULL && b->x.name == NULL) ret = 0;
			else if (a->x.name == NULL /*&& b->x.name != NULL*/) ret = -1;
			else if (/*a->x.name != NULL &&*/ b->x.name == NULL) ret = 1;
			else if ((ret = Dz1Asn1UTF8Str_cmp(a->x.name, b->x.name)) != 0) { }
			break;
		case MyUnionDataPresent_val:
			if ((ret = Dz1u32_cmp(&a->x.val, &b->x.val)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// MyUnionData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueList
static Dz1Error MyUnionDataUniqueList_add(MyUnionDataUniqueList *p, MyUnionData *data)
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

static bool_t MyUnionDataUniqueList_remove(MyUnionDataUniqueList *p, MyUnionData *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyUnionData *MyUnionDataUniqueList_extract(MyUnionDataUniqueList *p, MyUnionData *key)
{
	return (MyUnionData *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyUnionDataUniqueListMkArrArg
{
	MyUnionData **arr;
	unsigned int idx;
} MyUnionDataUniqueListMkArrArg;

static Dz1Error _MyUnionDataUniqueList_get_array(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueListMkArrArg *arg = (MyUnionDataUniqueListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionData **MyUnionDataUniqueList_get_array(MyUnionDataUniqueList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionData **)Dz1Calloc(sizeof(MyUnionData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataUniqueListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataUniqueList_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataUniqueList_travelForward(MyUnionDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataUniqueList_travelBackward(MyUnionDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionData *MyUnionDataUniqueList_find(MyUnionDataUniqueList *p, MyUnionData *key)
{
	return (MyUnionData *)Dz1AATree_find(p->storage, key);
}

static MyUnionData *MyUnionDataUniqueList_getHead(MyUnionDataUniqueList *p)
{
	return (MyUnionData *)Dz1AATree_getHead(p->storage);
}

static MyUnionData *MyUnionDataUniqueList_getTail(MyUnionDataUniqueList *p)
{
	return (MyUnionData *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyUnionDataUniqueList_count(MyUnionDataUniqueList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyUnionDataUniqueList *MyUnionDataUniqueList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueList *ret = (MyUnionDataUniqueList *)Dz1Calloc(sizeof(MyUnionDataUniqueList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyUnionData_cmp,
				(Dz1DelFunc)MyUnionData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataUniqueList_count;
			ret->travel = MyUnionDataUniqueList_travelForward;
			ret->travelForward = MyUnionDataUniqueList_travelForward;
			ret->travelBackward = MyUnionDataUniqueList_travelBackward;
			ret->get_array = MyUnionDataUniqueList_get_array;
			ret->add = MyUnionDataUniqueList_add;
			ret->remove = MyUnionDataUniqueList_remove;
			ret->find = MyUnionDataUniqueList_find;
			ret->extract = MyUnionDataUniqueList_extract;
			ret->getHead = MyUnionDataUniqueList_getHead;
			ret->getTail = MyUnionDataUniqueList_getTail;
			ret->cmp = MyUnionData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataUniqueList_clone(void *ptr, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueList *p = (MyUnionDataUniqueList *)ptr;
	MyUnionData *cloned = MyUnionData_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataUniqueList *MyUnionDataUniqueList_clone(MyUnionDataUniqueList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataUniqueList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataUniqueList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataUniqueList_purge(MyUnionDataUniqueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyUnionDataUniqueList_del(MyUnionDataUniqueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataUniqueList_dump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionData_dump(p, tab);
	return err;
}

void MyUnionDataUniqueList_dump(MyUnionDataUniqueList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataUniqueList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataUniqueList_fdump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionData_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataUniqueList_fdump(FILE *fp, MyUnionDataUniqueList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataUniqueList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataUniqueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedList
static Dz1Error MyUnionDataOrderedList_add(MyUnionDataOrderedList *p, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataOrderedList_remove(MyUnionDataOrderedList *p, MyUnionData *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyUnionData *MyUnionDataOrderedList_extract(MyUnionDataOrderedList *p, MyUnionData *key)
{
	return (MyUnionData *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyUnionDataOrderedListMkArrArg
{
	MyUnionData **arr;
	unsigned int idx;
} MyUnionDataOrderedListMkArrArg;

static Dz1Error _MyUnionDataOrderedList_get_array(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedListMkArrArg *arg = (MyUnionDataOrderedListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionData **MyUnionDataOrderedList_get_array(MyUnionDataOrderedList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionData **)Dz1Calloc(sizeof(MyUnionData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataOrderedListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataOrderedList_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataOrderedList_travelForward(MyUnionDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataOrderedList_travelBackward(MyUnionDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionData *MyUnionDataOrderedList_find(MyUnionDataOrderedList *p, MyUnionData *key)
{
	return (MyUnionData *)Dz1OrderedFifo_find(p->storage, key);
}

static MyUnionData *MyUnionDataOrderedList_getHead(MyUnionDataOrderedList *p)
{
	return (MyUnionData *)Dz1OrderedFifo_getHead(p->storage);
}

static MyUnionData *MyUnionDataOrderedList_getTail(MyUnionDataOrderedList *p)
{
	return (MyUnionData *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyUnionDataOrderedList_count(MyUnionDataOrderedList *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyUnionDataOrderedList *MyUnionDataOrderedList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedList *ret = (MyUnionDataOrderedList *)Dz1Calloc(sizeof(MyUnionDataOrderedList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyUnionData_cmp,
				(Dz1DelFunc)MyUnionData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataOrderedList_count;
			ret->travel = MyUnionDataOrderedList_travelForward;
			ret->travelForward = MyUnionDataOrderedList_travelForward;
			ret->travelBackward = MyUnionDataOrderedList_travelBackward;
			ret->get_array = MyUnionDataOrderedList_get_array;
			ret->add = MyUnionDataOrderedList_add;
			ret->remove = MyUnionDataOrderedList_remove;
			ret->find = MyUnionDataOrderedList_find;
			ret->extract = MyUnionDataOrderedList_extract;
			ret->getHead = MyUnionDataOrderedList_getHead;
			ret->getTail = MyUnionDataOrderedList_getTail;
			ret->cmp = MyUnionData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataOrderedList_clone(void *ptr, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedList *p = (MyUnionDataOrderedList *)ptr;
	MyUnionData *cloned = MyUnionData_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataOrderedList *MyUnionDataOrderedList_clone(MyUnionDataOrderedList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataOrderedList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedList_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataOrderedList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataOrderedList_purge(MyUnionDataOrderedList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyUnionDataOrderedList_del(MyUnionDataOrderedList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataOrderedList_dump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionData_dump(p, tab);
	return err;
}

void MyUnionDataOrderedList_dump(MyUnionDataOrderedList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataOrderedList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataOrderedList_fdump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionData_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataOrderedList_fdump(FILE *fp, MyUnionDataOrderedList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataOrderedList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataOrderedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataList
static Dz1Error MyUnionDataList_add(MyUnionDataList *p, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataList_remove(MyUnionDataList *p, MyUnionData *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyUnionData *MyUnionDataList_extract(MyUnionDataList *p, MyUnionData *ptr)
{
	return (MyUnionData *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyUnionDataListMkArrArg
{
	MyUnionData **arr;
	unsigned int idx;
} MyUnionDataListMkArrArg;

static Dz1Error _MyUnionDataList_get_array(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataListMkArrArg *arg = (MyUnionDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionData **MyUnionDataList_get_array(MyUnionDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionData **)Dz1Calloc(sizeof(MyUnionData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataList_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataList_travelForward(MyUnionDataList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataList_travelBackward(MyUnionDataList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyUnionDataListFindArg
{
	MyUnionData *key;
	MyUnionData *ret;
	int (*cmp)(MyUnionData *a, MyUnionData *b);
} MyUnionDataListFindArg;

static Dz1Error _MyUnionDataList_find(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyUnionDataListFindArg *arg = (MyUnionDataListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyUnionData *MyUnionDataList_find(MyUnionDataList *p, MyUnionData *key)
{
	MyUnionDataListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyUnionDataList_find, (void *)&arg);
	return arg.ret;
}

static MyUnionData *MyUnionDataList_getHead(MyUnionDataList *p)
{
	return (MyUnionData *)Dz1Fifo_getFirst(p->storage);
}

static MyUnionData *MyUnionDataList_getTail(MyUnionDataList *p)
{
	return (MyUnionData *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyUnionDataList_count(MyUnionDataList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionDataList *MyUnionDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataList *ret = (MyUnionDataList *)Dz1Calloc(sizeof(MyUnionDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyUnionData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataList_count;
			ret->travel = MyUnionDataList_travelForward;
			ret->travelForward = MyUnionDataList_travelForward;
			ret->travelBackward = MyUnionDataList_travelBackward;
			ret->get_array = MyUnionDataList_get_array;
			ret->add = MyUnionDataList_add;
			ret->remove = MyUnionDataList_remove;
			ret->find = MyUnionDataList_find;
			ret->extract = MyUnionDataList_extract;
			ret->getHead = MyUnionDataList_getHead;
			ret->getTail = MyUnionDataList_getTail;
			ret->cmp = MyUnionData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataList_clone(void *ptr, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataList *p = (MyUnionDataList *)ptr;
	MyUnionData *cloned = MyUnionData_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataList *MyUnionDataList_clone(MyUnionDataList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionDataList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataList_purge(MyUnionDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionDataList_del(MyUnionDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataList_dump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionData_dump(p, tab);
	return err;
}

void MyUnionDataList_dump(MyUnionDataList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataList_fdump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionData_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataList_fdump(FILE *fp, MyUnionDataList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueRefList
static Dz1Error MyUnionDataUniqueRefList_add(MyUnionDataUniqueRefList *p, MyUnionData *data)
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

static bool_t MyUnionDataUniqueRefList_remove(MyUnionDataUniqueRefList *p, MyUnionData *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyUnionData *MyUnionDataUniqueRefList_extract(MyUnionDataUniqueRefList *p, MyUnionData *key)
{
	return (MyUnionData *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyUnionDataUniqueRefListMkArrArg
{
	MyUnionData **arr;
	unsigned int idx;
} MyUnionDataUniqueRefListMkArrArg;

static Dz1Error _MyUnionDataUniqueRefList_get_array(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueRefListMkArrArg *arg = (MyUnionDataUniqueRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionData **MyUnionDataUniqueRefList_get_array(MyUnionDataUniqueRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionData **)Dz1Calloc(sizeof(MyUnionData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataUniqueRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataUniqueRefList_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataUniqueRefList_travelForward(MyUnionDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataUniqueRefList_travelBackward(MyUnionDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionData *MyUnionDataUniqueRefList_find(MyUnionDataUniqueRefList *p, MyUnionData *key)
{
	return (MyUnionData *)Dz1AATree_find(p->storage, key);
}

static MyUnionData *MyUnionDataUniqueRefList_getHead(MyUnionDataUniqueRefList *p)
{
	return (MyUnionData *)Dz1AATree_getHead(p->storage);
}

static MyUnionData *MyUnionDataUniqueRefList_getTail(MyUnionDataUniqueRefList *p)
{
	return (MyUnionData *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyUnionDataUniqueRefList_count(MyUnionDataUniqueRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyUnionDataUniqueRefList *MyUnionDataUniqueRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueRefList *ret = (MyUnionDataUniqueRefList *)Dz1Calloc(sizeof(MyUnionDataUniqueRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyUnionData_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataUniqueRefList_count;
			ret->travel = MyUnionDataUniqueRefList_travelForward;
			ret->travelForward = MyUnionDataUniqueRefList_travelForward;
			ret->travelBackward = MyUnionDataUniqueRefList_travelBackward;
			ret->get_array = MyUnionDataUniqueRefList_get_array;
			ret->add = MyUnionDataUniqueRefList_add;
			ret->remove = MyUnionDataUniqueRefList_remove;
			ret->find = MyUnionDataUniqueRefList_find;
			ret->extract = MyUnionDataUniqueRefList_extract;
			ret->getHead = MyUnionDataUniqueRefList_getHead;
			ret->getTail = MyUnionDataUniqueRefList_getTail;
			ret->cmp = MyUnionData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataUniqueRefList_clone(void *ptr, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueRefList *p = (MyUnionDataUniqueRefList *)ptr;
	MyUnionData *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataUniqueRefList *MyUnionDataUniqueRefList_clone(MyUnionDataUniqueRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataUniqueRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataUniqueRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataUniqueRefList_purge(MyUnionDataUniqueRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyUnionDataUniqueRefList_del(MyUnionDataUniqueRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataUniqueRefList_dump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionData_dump(p, tab);
	return err;
}

void MyUnionDataUniqueRefList_dump(MyUnionDataUniqueRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataUniqueRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataUniqueRefList_fdump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionData_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataUniqueRefList_fdump(FILE *fp, MyUnionDataUniqueRefList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataUniqueRefList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataUniqueRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedRefList
static Dz1Error MyUnionDataOrderedRefList_add(MyUnionDataOrderedRefList *p, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataOrderedRefList_remove(MyUnionDataOrderedRefList *p, MyUnionData *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyUnionData *MyUnionDataOrderedRefList_extract(MyUnionDataOrderedRefList *p, MyUnionData *key)
{
	return (MyUnionData *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyUnionDataOrderedRefListMkArrArg
{
	MyUnionData **arr;
	unsigned int idx;
} MyUnionDataOrderedRefListMkArrArg;

static Dz1Error _MyUnionDataOrderedRefList_get_array(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedRefListMkArrArg *arg = (MyUnionDataOrderedRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionData **MyUnionDataOrderedRefList_get_array(MyUnionDataOrderedRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionData **)Dz1Calloc(sizeof(MyUnionData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataOrderedRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataOrderedRefList_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataOrderedRefList_travelForward(MyUnionDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataOrderedRefList_travelBackward(MyUnionDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionData *MyUnionDataOrderedRefList_find(MyUnionDataOrderedRefList *p, MyUnionData *key)
{
	return (MyUnionData *)Dz1OrderedFifo_find(p->storage, key);
}

static MyUnionData *MyUnionDataOrderedRefList_getHead(MyUnionDataOrderedRefList *p)
{
	return (MyUnionData *)Dz1OrderedFifo_getHead(p->storage);
}

static MyUnionData *MyUnionDataOrderedRefList_getTail(MyUnionDataOrderedRefList *p)
{
	return (MyUnionData *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyUnionDataOrderedRefList_count(MyUnionDataOrderedRefList *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyUnionDataOrderedRefList *MyUnionDataOrderedRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedRefList *ret = (MyUnionDataOrderedRefList *)Dz1Calloc(sizeof(MyUnionDataOrderedRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyUnionData_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataOrderedRefList_count;
			ret->travel = MyUnionDataOrderedRefList_travelForward;
			ret->travelForward = MyUnionDataOrderedRefList_travelForward;
			ret->travelBackward = MyUnionDataOrderedRefList_travelBackward;
			ret->get_array = MyUnionDataOrderedRefList_get_array;
			ret->add = MyUnionDataOrderedRefList_add;
			ret->remove = MyUnionDataOrderedRefList_remove;
			ret->find = MyUnionDataOrderedRefList_find;
			ret->extract = MyUnionDataOrderedRefList_extract;
			ret->getHead = MyUnionDataOrderedRefList_getHead;
			ret->getTail = MyUnionDataOrderedRefList_getTail;
			ret->cmp = MyUnionData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataOrderedRefList_clone(void *ptr, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedRefList *p = (MyUnionDataOrderedRefList *)ptr;
	MyUnionData *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataOrderedRefList *MyUnionDataOrderedRefList_clone(MyUnionDataOrderedRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataOrderedRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataOrderedRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataOrderedRefList_purge(MyUnionDataOrderedRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyUnionDataOrderedRefList_del(MyUnionDataOrderedRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataOrderedRefList_dump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionData_dump(p, tab);
	return err;
}

void MyUnionDataOrderedRefList_dump(MyUnionDataOrderedRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataOrderedRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataOrderedRefList_fdump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionData_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataOrderedRefList_fdump(FILE *fp, MyUnionDataOrderedRefList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataOrderedRefList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataOrderedRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataRefList
static Dz1Error MyUnionDataRefList_add(MyUnionDataRefList *p, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataRefList_remove(MyUnionDataRefList *p, MyUnionData *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyUnionData *MyUnionDataRefList_extract(MyUnionDataRefList *p, MyUnionData *ptr)
{
	return (MyUnionData *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyUnionDataRefListMkArrArg
{
	MyUnionData **arr;
	unsigned int idx;
} MyUnionDataRefListMkArrArg;

static Dz1Error _MyUnionDataRefList_get_array(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataRefListMkArrArg *arg = (MyUnionDataRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionData **MyUnionDataRefList_get_array(MyUnionDataRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionData **)Dz1Calloc(sizeof(MyUnionData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataRefList_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataRefList_travelForward(MyUnionDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataRefList_travelBackward(MyUnionDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyUnionDataRefListFindArg
{
	MyUnionData *key;
	MyUnionData *ret;
	int (*cmp)(MyUnionData *a, MyUnionData *b);
} MyUnionDataRefListFindArg;

static Dz1Error _MyUnionDataRefList_find(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyUnionDataRefListFindArg *arg = (MyUnionDataRefListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyUnionData *MyUnionDataRefList_find(MyUnionDataRefList *p, MyUnionData *key)
{
	MyUnionDataRefListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyUnionDataRefList_find, (void *)&arg);
	return arg.ret;
}

static MyUnionData *MyUnionDataRefList_getHead(MyUnionDataRefList *p)
{
	return (MyUnionData *)Dz1Fifo_getFirst(p->storage);
}

static MyUnionData *MyUnionDataRefList_getTail(MyUnionDataRefList *p)
{
	return (MyUnionData *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyUnionDataRefList_count(MyUnionDataRefList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionDataRefList *MyUnionDataRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataRefList *ret = (MyUnionDataRefList *)Dz1Calloc(sizeof(MyUnionDataRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataRefList_count;
			ret->travel = MyUnionDataRefList_travelForward;
			ret->travelForward = MyUnionDataRefList_travelForward;
			ret->travelBackward = MyUnionDataRefList_travelBackward;
			ret->get_array = MyUnionDataRefList_get_array;
			ret->add = MyUnionDataRefList_add;
			ret->remove = MyUnionDataRefList_remove;
			ret->find = MyUnionDataRefList_find;
			ret->extract = MyUnionDataRefList_extract;
			ret->getHead = MyUnionDataRefList_getHead;
			ret->getTail = MyUnionDataRefList_getTail;
			ret->cmp = MyUnionData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataRefList_clone(void *ptr, MyUnionData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataRefList *p = (MyUnionDataRefList *)ptr;
	MyUnionData *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataRefList *MyUnionDataRefList_clone(MyUnionDataRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionDataRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataRefList_purge(MyUnionDataRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionDataRefList_del(MyUnionDataRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataRefList_dump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionData_dump(p, tab);
	return err;
}

void MyUnionDataRefList_dump(MyUnionDataRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataRefList_fdump(void *ptr, MyUnionData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionData_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataRefList_fdump(FILE *fp, MyUnionDataRefList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataRefList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataInfo
// void MyUnionDataInfo_obj_ptr_arr_del(MyUnionData **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyUnionDataInfo, MyUnionData*, obj_ptr_arr, u32_t, MyUnionData_del)
// void MyUnionDataInfo_obj_ptr_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyUnionDataInfo, MyUnionData*, obj_ptr_arr, u32_t)
// MyUnionData **MyUnionDataInfo_obj_ptr_arr_clone(MyUnionData **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyUnionDataInfo, MyUnionData*, obj_ptr_arr, u32_t, MyUnionData_clone)
// void MyUnionDataInfo_obj_ptr_arr_dump(MyUnionData **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_dump(MyUnionDataInfo, MyUnionData*, obj_ptr_arr, u32_t, ".", MyUnionData_dump)
// void MyUnionDataInfo_obj_ptr_arr_fdump(FILE *fp, MyUnionData **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_fdump(MyUnionDataInfo, MyUnionData*, obj_ptr_arr, u32_t, ".", MyUnionData_fdump)

// void MyUnionDataInfo_obj_arr_del(MyUnionData *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(MyUnionDataInfo, MyUnionData, obj_arr, u32_t, MyUnionData_purge)
// void MyUnionDataInfo_obj_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(MyUnionDataInfo, MyUnionData, obj_arr, u32_t)
// MyUnionData *MyUnionDataInfo_obj_arr_clone(MyUnionData *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(MyUnionDataInfo, MyUnionData, obj_arr, u32_t, MyUnionData_copy)
// void MyUnionDataInfo_obj_arr_dump(MyUnionData *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_dump(MyUnionDataInfo, MyUnionData, obj_arr, u32_t, ".", MyUnionData_dump)
// void MyUnionDataInfo_obj_arr_fdump(FILE *fp, MyUnionData *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_fdump(MyUnionDataInfo, MyUnionData, obj_arr, u32_t, ".", MyUnionData_fdump)

// void MyUnionDataInfo_prims_arr_del(u64_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(MyUnionDataInfo, u64_t, prims_arr, u32_t)
// void MyUnionDataInfo_prims_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(MyUnionDataInfo, u64_t, prims_arr)
// u64_t *MyUnionDataInfo_prims_arr_clone(u64_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(MyUnionDataInfo, u64_t, prims_arr, u32_t)
// void MyUnionDataInfo_prims_arr_dump(u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_dump(MyUnionDataInfo, u64_t, prims_arr, u32_t, " = ", Dz1u64_dump)
// void MyUnionDataInfo_prims_arr_fdump(FILE *fp, u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_fdump(MyUnionDataInfo, u64_t, prims_arr, u32_t, " = ", Dz1u64_fdump)

// void MyUnionDataInfo_primptrs_arr_del(u64_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyUnionDataInfo, u64_t*, primptrs_arr, u32_t, Dz1u64_del)
// void MyUnionDataInfo_primptrs_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyUnionDataInfo, u64_t*, primptrs_arr, u32_t)
// u64_t **MyUnionDataInfo_primptrs_arr_clone(u64_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyUnionDataInfo, u64_t*, primptrs_arr, u32_t, Dz1u64_clone)
// void MyUnionDataInfo_primptrs_arr_dump(u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_dump(MyUnionDataInfo, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64_dump)
// void MyUnionDataInfo_primptrs_arr_fdump(FILE *fp, u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_fdump(MyUnionDataInfo, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64_fdump)

MyUnionDataInfo *MyUnionDataInfo_new(MyUnionData **obj_ptr_arr/*_e_clone*/, 
									 u32_t obj_ptr_cnt, 
									 MyUnionData *obj_arr/*_e_copy*/, 
									 u32_t obj_cnt, 
									 u64_t *prims_arr/*_e_copy*/, 
									 u32_t prims_cnt, 
									 u64_t **primptrs_arr/*_e_clone*/, 
									 u32_t primptrs_cnt, 
									 s32_t *i_val/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataInfo *__internal_ret = (MyUnionDataInfo *)Dz1Calloc(sizeof(MyUnionDataInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnionDataInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (obj_ptr_arr != NULL && (__internal_ret->obj_ptr_arr = MyUnionDataInfo_obj_ptr_arr_clone(obj_ptr_arr, obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (obj_arr != NULL && (__internal_ret->obj_arr = MyUnionDataInfo_obj_arr_clone(obj_arr, obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (prims_arr != NULL && (__internal_ret->prims_arr = MyUnionDataInfo_prims_arr_clone(prims_arr, prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (primptrs_arr != NULL && (__internal_ret->primptrs_arr = MyUnionDataInfo_primptrs_arr_clone(primptrs_arr, primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->obj_ptr_cnt = obj_ptr_cnt;
			__internal_ret->obj_cnt = obj_cnt;
			__internal_ret->prims_cnt = prims_cnt;
			__internal_ret->primptrs_cnt = primptrs_cnt;
			__internal_ret->i_val = i_val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyUnionDataInfo_copy(MyUnionDataInfo *dst, MyUnionDataInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->obj_ptr_arr != NULL && (dst->obj_ptr_arr = MyUnionDataInfo_obj_ptr_arr_clone(src->obj_ptr_arr, src->obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->obj_arr != NULL && (dst->obj_arr = MyUnionDataInfo_obj_arr_clone(src->obj_arr, src->obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->prims_arr != NULL && (dst->prims_arr = MyUnionDataInfo_prims_arr_clone(src->prims_arr, src->prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->primptrs_arr != NULL && (dst->primptrs_arr = MyUnionDataInfo_primptrs_arr_clone(src->primptrs_arr, src->primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		dst->obj_ptr_cnt = src->obj_ptr_cnt;
		dst->obj_cnt = src->obj_cnt;
		dst->prims_cnt = src->prims_cnt;
		dst->primptrs_cnt = src->primptrs_cnt;
		dst->i_val = src->i_val;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyUnionDataInfo *MyUnionDataInfo_clone(MyUnionDataInfo *src, Dz1Error *err)
{
	MyUnionDataInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyUnionDataInfo *)Dz1Calloc(sizeof(MyUnionDataInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnionDataInfo_delAndSetNull, (void *)&dst);
		if (MyUnionDataInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyUnionDataInfo_purge(MyUnionDataInfo *p)
{
	if (p == NULL) return;
	MyUnionDataInfo_obj_ptr_arr_del(p->obj_ptr_arr, p->obj_ptr_cnt);
	MyUnionDataInfo_obj_arr_del(p->obj_arr, p->obj_cnt);
	MyUnionDataInfo_prims_arr_del(p->prims_arr, p->prims_cnt);
	MyUnionDataInfo_primptrs_arr_del(p->primptrs_arr, p->primptrs_cnt);
}

void MyUnionDataInfo_del(MyUnionDataInfo *p)
{
	if (p == NULL) return;
	MyUnionDataInfo_purge(p);
	Dz1Free(p);
}

void MyUnionDataInfo_dump(MyUnionDataInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("obj_ptr_arr = ")); MyUnionDataInfo_obj_ptr_arr_dump(p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("obj_ptr_cnt = ")); Dz1u32_dump(&p->obj_ptr_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("obj_arr = ")); MyUnionDataInfo_obj_arr_dump(p->obj_arr, p->obj_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("obj_cnt = ")); Dz1u32_dump(&p->obj_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("prims_arr = ")); MyUnionDataInfo_prims_arr_dump(p->prims_arr, p->prims_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("prims_cnt = ")); Dz1u32_dump(&p->prims_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("primptrs_arr = ")); MyUnionDataInfo_primptrs_arr_dump(p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("primptrs_cnt = ")); Dz1u32_dump(&p->primptrs_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("i_val = ")); Dz1s32_dump(p->i_val, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void MyUnionDataInfo_fdump(FILE *fp, MyUnionDataInfo *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_ptr_arr = ")); MyUnionDataInfo_obj_ptr_arr_fdump(fp, p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_ptr_cnt = ")); Dz1u32_fdump(fp, &p->obj_ptr_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_arr = ")); MyUnionDataInfo_obj_arr_fdump(fp, p->obj_arr, p->obj_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_cnt = ")); Dz1u32_fdump(fp, &p->obj_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("prims_arr = ")); MyUnionDataInfo_prims_arr_fdump(fp, p->prims_arr, p->prims_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("prims_cnt = ")); Dz1u32_fdump(fp, &p->prims_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("primptrs_arr = ")); MyUnionDataInfo_primptrs_arr_fdump(fp, p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("primptrs_cnt = ")); Dz1u32_fdump(fp, &p->primptrs_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("i_val = ")); Dz1s32_fdump(fp, p->i_val, tab); 
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataInfo
////////////////////////////////////////////////////////////////////////////////

