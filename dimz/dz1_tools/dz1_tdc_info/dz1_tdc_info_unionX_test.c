////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_unionX_test.h"

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataPresent
static struct MyUnionXDataPresentMapA
{
	str_t str;
	MyUnionXDataPresent v;
} MyUnionXDataPresentMapA[] =
{
	{ (char *)"name", MyUnionXDataPresent_name },
	{ (char *)"val", MyUnionXDataPresent_val },
	{ NULL, MyUnionXDataPresent_max }
};

str_t MyUnionXDataPresentStrA(MyUnionXDataPresent v)
{
	struct MyUnionXDataPresentMapA *i = NULL;
	for (i = MyUnionXDataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionXDataPresent MyUnionXDataPresentFromStrA(str_t str)
{
	struct MyUnionXDataPresentMapA *i = NULL;
	for (i = MyUnionXDataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return MyUnionXDataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct MyUnionXDataPresentMapW
{
	wstr_t str;
	MyUnionXDataPresent v;
} MyUnionXDataPresentMapW[] =
{
	{ (wchar_t *)L"name", MyUnionXDataPresent_name },
	{ (wchar_t *)L"val", MyUnionXDataPresent_val },
	{ NULL, MyUnionXDataPresent_max }
};

wstr_t MyUnionXDataPresentStrW(MyUnionXDataPresent v)
{
	struct MyUnionXDataPresentMapW *i = NULL;
	for (i = MyUnionXDataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionXDataPresent MyUnionXDataPresentFromStrW(wstr_t str)
{
	struct MyUnionXDataPresentMapW *i = NULL;
	for (i = MyUnionXDataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return MyUnionXDataPresent_max;
}
#endif // UNIX_SYSTEM

MyUnionXDataPresent *MyUnionXDataPresent_new(MyUnionXDataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataPresent *__internal_ret = (MyUnionXDataPresent *)Dz1Calloc(sizeof(MyUnionXDataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void MyUnionXDataPresentA_dump(MyUnionXDataPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", MyUnionXDataPresentStrA(*v));
}
void MyUnionXDataPresentA_fdump(FILE *fp, MyUnionXDataPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", MyUnionXDataPresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void MyUnionXDataPresentW_dump(MyUnionXDataPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", MyUnionXDataPresentStrW(*v));
}
void MyUnionXDataPresentW_fdump(FILE *fp, MyUnionXDataPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", MyUnionXDataPresentStrW(*v));
}
#endif // UNIX_SYSTEM

int MyUnionXDataPresent_cmp(MyUnionXDataPresent *a, MyUnionXDataPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// MyUnionXDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXData
MyUnionXData *MyUnionXData_new(MyUnionXDataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXData *ret = (MyUnionXData *)Dz1Calloc(sizeof(MyUnionXData), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnionXData_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case MyUnionXDataPresent_name:
			// _U_imp_clone
			if (ptr != NULL) ret->x.name = (Dz1Asn1UTF8Str *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionXDataPresent_val:
			// _U_prim_clone
			if (ptr != NULL) ret->x.val = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionXDataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t MyUnionXData_copy(MyUnionXData *ret, MyUnionXData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case MyUnionXDataPresent_name:
			// _U_imp_clone
			if (src->x.name && (ret->x.name = Dz1Asn1UTF8Str_clone(src->x.name, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyUnionXDataPresent_val:
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

MyUnionXData *MyUnionXData_clone(MyUnionXData *src, Dz1Error *err)
{
	MyUnionXData *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (MyUnionXData *)Dz1Calloc(sizeof(MyUnionXData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnionXData_delAndSetNull, (void *)&ret);
		if (MyUnionXData_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionXData_purge(MyUnionXData *p)
{
	if (!p) return;
	switch(p->present)
	{
	case MyUnionXDataPresent_name:
		Dz1Asn1UTF8Str_del(p->x.name);
		break;
	case MyUnionXDataPresent_val:
		break;
	default:
		break;
	}
}

void MyUnionXData_del(MyUnionXData *p)
{
	if (!p) return;
	MyUnionXData_purge(p);
	Dz1Free(p);
}

void MyUnionXDataA_dump(MyUnionXData *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case MyUnionXDataPresent_name:
		Dz1ThreadA_printf("name = "); Dz1Asn1UTF8StrA_dump(p->x.name, tab); 
		break;
	case MyUnionXDataPresent_val:
		Dz1ThreadA_printf("val = "); Dz1u32A_dump(&p->x.val, tab); 
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}
void MyUnionXDataA_fdump(FILE *fp, MyUnionXData *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else switch(p->present)
	{
	case MyUnionXDataPresent_name:
		Dz1ThreadA_fprintf(fp, "name = "); Dz1Asn1UTF8StrA_fdump(fp, p->x.name, tab); 
		break;
	case MyUnionXDataPresent_val:
		Dz1ThreadA_fprintf(fp, "val = "); Dz1u32A_fdump(fp, &p->x.val, tab); 
		break;
	default:
		Dz1ThreadA_ftprintf(fp, tab, "??? = %d\n", p->present);
		break;
	}
}
#ifndef UNIX_SYSTEM
void MyUnionXDataW_dump(MyUnionXData *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case MyUnionXDataPresent_name:
		Dz1ThreadW_printf(L"name = "); Dz1Asn1UTF8StrW_dump(p->x.name, tab); 
		break;
	case MyUnionXDataPresent_val:
		Dz1ThreadW_printf(L"val = "); Dz1u32W_dump(&p->x.val, tab); 
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}
void MyUnionXDataW_fdump(FILE *fp, MyUnionXData *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else switch(p->present)
	{
	case MyUnionXDataPresent_name:
		Dz1ThreadW_fprintf(fp, L"name = "); Dz1Asn1UTF8StrW_fdump(fp, p->x.name, tab); 
		break;
	case MyUnionXDataPresent_val:
		Dz1ThreadW_fprintf(fp, L"val = "); Dz1u32W_fdump(fp, &p->x.val, tab); 
		break;
	default:
		Dz1ThreadW_ftprintf(fp, tab, L"??? = %d\n", p->present);
		break;
	}
}
#endif // UNIX_SYSTEM

int MyUnionXData_cmp(MyUnionXData *a, MyUnionXData *b)
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
		case MyUnionXDataPresent_name:
			if (a->x.name == NULL && b->x.name == NULL) ret = 0;
			else if (a->x.name == NULL /*&& b->x.name != NULL*/) ret = -1;
			else if (/*a->x.name != NULL &&*/ b->x.name == NULL) ret = 1;
			else if ((ret = Dz1Asn1UTF8Str_cmp(a->x.name, b->x.name)) != 0) { }
			break;
		case MyUnionXDataPresent_val:
			if ((ret = Dz1u32_cmp(&a->x.val, &b->x.val)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// MyUnionXData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataUniqueList
static Dz1Error MyUnionXDataUniqueList_add(MyUnionXDataUniqueList *p, MyUnionXData *data)
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

static bool_t MyUnionXDataUniqueList_remove(MyUnionXDataUniqueList *p, MyUnionXData *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyUnionXData *MyUnionXDataUniqueList_extract(MyUnionXDataUniqueList *p, MyUnionXData *key)
{
	return (MyUnionXData *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyUnionXDataUniqueListMkArrArg
{
	MyUnionXData **arr;
	unsigned int idx;
} MyUnionXDataUniqueListMkArrArg;

static Dz1Error _MyUnionXDataUniqueList_get_array(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataUniqueListMkArrArg *arg = (MyUnionXDataUniqueListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionXData **MyUnionXDataUniqueList_get_array(MyUnionXDataUniqueList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionXData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionXData **)Dz1Calloc(sizeof(MyUnionXData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionXDataUniqueListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionXDataUniqueList_get_array, (void *)&arg);
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

static Dz1Error MyUnionXDataUniqueList_travelForward(MyUnionXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionXDataUniqueList_travelBackward(MyUnionXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionXData *MyUnionXDataUniqueList_find(MyUnionXDataUniqueList *p, MyUnionXData *key)
{
	return (MyUnionXData *)Dz1AATree_find(p->storage, key);
}

static MyUnionXData *MyUnionXDataUniqueList_getHead(MyUnionXDataUniqueList *p)
{
	return (MyUnionXData *)Dz1AATree_getHead(p->storage);
}

static MyUnionXData *MyUnionXDataUniqueList_getTail(MyUnionXDataUniqueList *p)
{
	return (MyUnionXData *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyUnionXDataUniqueList_count(MyUnionXDataUniqueList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyUnionXDataUniqueList *MyUnionXDataUniqueList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataUniqueList *ret = (MyUnionXDataUniqueList *)Dz1Calloc(sizeof(MyUnionXDataUniqueList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataUniqueList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyUnionXData_cmp,
				(Dz1DelFunc)MyUnionXData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionXDataUniqueList_count;
			ret->travel = MyUnionXDataUniqueList_travelForward;
			ret->travelForward = MyUnionXDataUniqueList_travelForward;
			ret->travelBackward = MyUnionXDataUniqueList_travelBackward;
			ret->get_array = MyUnionXDataUniqueList_get_array;
			ret->add = MyUnionXDataUniqueList_add;
			ret->remove = MyUnionXDataUniqueList_remove;
			ret->find = MyUnionXDataUniqueList_find;
			ret->extract = MyUnionXDataUniqueList_extract;
			ret->getHead = MyUnionXDataUniqueList_getHead;
			ret->getTail = MyUnionXDataUniqueList_getTail;
			ret->cmp = MyUnionXData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataUniqueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionXDataUniqueList_clone(void *ptr, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataUniqueList *p = (MyUnionXDataUniqueList *)ptr;
	MyUnionXData *cloned = MyUnionXData_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionXDataUniqueList *MyUnionXDataUniqueList_clone(MyUnionXDataUniqueList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataUniqueList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionXDataUniqueList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataUniqueList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionXDataUniqueList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataUniqueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionXDataUniqueList_purge(MyUnionXDataUniqueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyUnionXDataUniqueList_del(MyUnionXDataUniqueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionXDataUniqueListA_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyUnionXDataA_dump(p, tab);
	return err;
}

void MyUnionXDataUniqueListA_dump(MyUnionXDataUniqueList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataUniqueListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyUnionXDataUniqueListA_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyUnionXDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataUniqueListA_fdump(FILE *fp, MyUnionXDataUniqueList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataUniqueListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyUnionXDataUniqueListW_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionXDataW_dump(p, tab);
	return err;
}

void MyUnionXDataUniqueListW_dump(MyUnionXDataUniqueList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataUniqueListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionXDataUniqueListW_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionXDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataUniqueListW_fdump(FILE *fp, MyUnionXDataUniqueList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataUniqueListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyUnionXDataUniqueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataOrderedList
static Dz1Error MyUnionXDataOrderedList_add(MyUnionXDataOrderedList *p, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionXDataOrderedList_remove(MyUnionXDataOrderedList *p, MyUnionXData *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyUnionXData *MyUnionXDataOrderedList_extract(MyUnionXDataOrderedList *p, MyUnionXData *key)
{
	return (MyUnionXData *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyUnionXDataOrderedListMkArrArg
{
	MyUnionXData **arr;
	unsigned int idx;
} MyUnionXDataOrderedListMkArrArg;

static Dz1Error _MyUnionXDataOrderedList_get_array(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataOrderedListMkArrArg *arg = (MyUnionXDataOrderedListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionXData **MyUnionXDataOrderedList_get_array(MyUnionXDataOrderedList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionXData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionXData **)Dz1Calloc(sizeof(MyUnionXData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionXDataOrderedListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionXDataOrderedList_get_array, (void *)&arg);
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

static Dz1Error MyUnionXDataOrderedList_travelForward(MyUnionXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionXDataOrderedList_travelBackward(MyUnionXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionXData *MyUnionXDataOrderedList_find(MyUnionXDataOrderedList *p, MyUnionXData *key)
{
	return (MyUnionXData *)Dz1OrderedFifo_find(p->storage, key);
}

static MyUnionXData *MyUnionXDataOrderedList_getHead(MyUnionXDataOrderedList *p)
{
	return (MyUnionXData *)Dz1OrderedFifo_getHead(p->storage);
}

static MyUnionXData *MyUnionXDataOrderedList_getTail(MyUnionXDataOrderedList *p)
{
	return (MyUnionXData *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyUnionXDataOrderedList_count(MyUnionXDataOrderedList *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyUnionXDataOrderedList *MyUnionXDataOrderedList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataOrderedList *ret = (MyUnionXDataOrderedList *)Dz1Calloc(sizeof(MyUnionXDataOrderedList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataOrderedList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyUnionXData_cmp,
				(Dz1DelFunc)MyUnionXData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionXDataOrderedList_count;
			ret->travel = MyUnionXDataOrderedList_travelForward;
			ret->travelForward = MyUnionXDataOrderedList_travelForward;
			ret->travelBackward = MyUnionXDataOrderedList_travelBackward;
			ret->get_array = MyUnionXDataOrderedList_get_array;
			ret->add = MyUnionXDataOrderedList_add;
			ret->remove = MyUnionXDataOrderedList_remove;
			ret->find = MyUnionXDataOrderedList_find;
			ret->extract = MyUnionXDataOrderedList_extract;
			ret->getHead = MyUnionXDataOrderedList_getHead;
			ret->getTail = MyUnionXDataOrderedList_getTail;
			ret->cmp = MyUnionXData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataOrderedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionXDataOrderedList_clone(void *ptr, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataOrderedList *p = (MyUnionXDataOrderedList *)ptr;
	MyUnionXData *cloned = MyUnionXData_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionXDataOrderedList *MyUnionXDataOrderedList_clone(MyUnionXDataOrderedList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataOrderedList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionXDataOrderedList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataOrderedList_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionXDataOrderedList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataOrderedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionXDataOrderedList_purge(MyUnionXDataOrderedList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyUnionXDataOrderedList_del(MyUnionXDataOrderedList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionXDataOrderedListA_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyUnionXDataA_dump(p, tab);
	return err;
}

void MyUnionXDataOrderedListA_dump(MyUnionXDataOrderedList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataOrderedListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyUnionXDataOrderedListA_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyUnionXDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataOrderedListA_fdump(FILE *fp, MyUnionXDataOrderedList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataOrderedListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyUnionXDataOrderedListW_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionXDataW_dump(p, tab);
	return err;
}

void MyUnionXDataOrderedListW_dump(MyUnionXDataOrderedList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataOrderedListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionXDataOrderedListW_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionXDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataOrderedListW_fdump(FILE *fp, MyUnionXDataOrderedList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataOrderedListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyUnionXDataOrderedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataList
static Dz1Error MyUnionXDataList_add(MyUnionXDataList *p, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionXDataList_remove(MyUnionXDataList *p, MyUnionXData *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyUnionXData *MyUnionXDataList_extract(MyUnionXDataList *p, MyUnionXData *ptr)
{
	return (MyUnionXData *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyUnionXDataListMkArrArg
{
	MyUnionXData **arr;
	unsigned int idx;
} MyUnionXDataListMkArrArg;

static Dz1Error _MyUnionXDataList_get_array(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataListMkArrArg *arg = (MyUnionXDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionXData **MyUnionXDataList_get_array(MyUnionXDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionXData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionXData **)Dz1Calloc(sizeof(MyUnionXData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionXDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionXDataList_get_array, (void *)&arg);
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

static Dz1Error MyUnionXDataList_travelForward(MyUnionXDataList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionXDataList_travelBackward(MyUnionXDataList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyUnionXDataListFindArg
{
	MyUnionXData *key;
	MyUnionXData *ret;
	int (*cmp)(MyUnionXData *a, MyUnionXData *b);
} MyUnionXDataListFindArg;

static Dz1Error _MyUnionXDataList_find(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyUnionXDataListFindArg *arg = (MyUnionXDataListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyUnionXData *MyUnionXDataList_find(MyUnionXDataList *p, MyUnionXData *key)
{
	MyUnionXDataListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyUnionXDataList_find, (void *)&arg);
	return arg.ret;
}

static MyUnionXData *MyUnionXDataList_getHead(MyUnionXDataList *p)
{
	return (MyUnionXData *)Dz1Fifo_getFirst(p->storage);
}

static MyUnionXData *MyUnionXDataList_getTail(MyUnionXDataList *p)
{
	return (MyUnionXData *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyUnionXDataList_count(MyUnionXDataList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionXDataList *MyUnionXDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataList *ret = (MyUnionXDataList *)Dz1Calloc(sizeof(MyUnionXDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyUnionXData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionXDataList_count;
			ret->travel = MyUnionXDataList_travelForward;
			ret->travelForward = MyUnionXDataList_travelForward;
			ret->travelBackward = MyUnionXDataList_travelBackward;
			ret->get_array = MyUnionXDataList_get_array;
			ret->add = MyUnionXDataList_add;
			ret->remove = MyUnionXDataList_remove;
			ret->find = MyUnionXDataList_find;
			ret->extract = MyUnionXDataList_extract;
			ret->getHead = MyUnionXDataList_getHead;
			ret->getTail = MyUnionXDataList_getTail;
			ret->cmp = MyUnionXData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionXDataList_clone(void *ptr, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataList *p = (MyUnionXDataList *)ptr;
	MyUnionXData *cloned = MyUnionXData_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionXDataList *MyUnionXDataList_clone(MyUnionXDataList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionXDataList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionXDataList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionXDataList_purge(MyUnionXDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionXDataList_del(MyUnionXDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionXDataListA_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyUnionXDataA_dump(p, tab);
	return err;
}

void MyUnionXDataListA_dump(MyUnionXDataList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyUnionXDataListA_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyUnionXDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataListA_fdump(FILE *fp, MyUnionXDataList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyUnionXDataListW_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionXDataW_dump(p, tab);
	return err;
}

void MyUnionXDataListW_dump(MyUnionXDataList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionXDataListW_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionXDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataListW_fdump(FILE *fp, MyUnionXDataList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyUnionXDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataUniqueRefList
static Dz1Error MyUnionXDataUniqueRefList_add(MyUnionXDataUniqueRefList *p, MyUnionXData *data)
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

static bool_t MyUnionXDataUniqueRefList_remove(MyUnionXDataUniqueRefList *p, MyUnionXData *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyUnionXData *MyUnionXDataUniqueRefList_extract(MyUnionXDataUniqueRefList *p, MyUnionXData *key)
{
	return (MyUnionXData *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyUnionXDataUniqueRefListMkArrArg
{
	MyUnionXData **arr;
	unsigned int idx;
} MyUnionXDataUniqueRefListMkArrArg;

static Dz1Error _MyUnionXDataUniqueRefList_get_array(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataUniqueRefListMkArrArg *arg = (MyUnionXDataUniqueRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionXData **MyUnionXDataUniqueRefList_get_array(MyUnionXDataUniqueRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionXData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionXData **)Dz1Calloc(sizeof(MyUnionXData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionXDataUniqueRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionXDataUniqueRefList_get_array, (void *)&arg);
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

static Dz1Error MyUnionXDataUniqueRefList_travelForward(MyUnionXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionXDataUniqueRefList_travelBackward(MyUnionXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionXData *MyUnionXDataUniqueRefList_find(MyUnionXDataUniqueRefList *p, MyUnionXData *key)
{
	return (MyUnionXData *)Dz1AATree_find(p->storage, key);
}

static MyUnionXData *MyUnionXDataUniqueRefList_getHead(MyUnionXDataUniqueRefList *p)
{
	return (MyUnionXData *)Dz1AATree_getHead(p->storage);
}

static MyUnionXData *MyUnionXDataUniqueRefList_getTail(MyUnionXDataUniqueRefList *p)
{
	return (MyUnionXData *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyUnionXDataUniqueRefList_count(MyUnionXDataUniqueRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyUnionXDataUniqueRefList *MyUnionXDataUniqueRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataUniqueRefList *ret = (MyUnionXDataUniqueRefList *)Dz1Calloc(sizeof(MyUnionXDataUniqueRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataUniqueRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyUnionXData_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionXDataUniqueRefList_count;
			ret->travel = MyUnionXDataUniqueRefList_travelForward;
			ret->travelForward = MyUnionXDataUniqueRefList_travelForward;
			ret->travelBackward = MyUnionXDataUniqueRefList_travelBackward;
			ret->get_array = MyUnionXDataUniqueRefList_get_array;
			ret->add = MyUnionXDataUniqueRefList_add;
			ret->remove = MyUnionXDataUniqueRefList_remove;
			ret->find = MyUnionXDataUniqueRefList_find;
			ret->extract = MyUnionXDataUniqueRefList_extract;
			ret->getHead = MyUnionXDataUniqueRefList_getHead;
			ret->getTail = MyUnionXDataUniqueRefList_getTail;
			ret->cmp = MyUnionXData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataUniqueRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionXDataUniqueRefList_clone(void *ptr, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataUniqueRefList *p = (MyUnionXDataUniqueRefList *)ptr;
	MyUnionXData *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionXDataUniqueRefList *MyUnionXDataUniqueRefList_clone(MyUnionXDataUniqueRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataUniqueRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionXDataUniqueRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataUniqueRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionXDataUniqueRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataUniqueRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionXDataUniqueRefList_purge(MyUnionXDataUniqueRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyUnionXDataUniqueRefList_del(MyUnionXDataUniqueRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionXDataUniqueRefListA_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyUnionXDataA_dump(p, tab);
	return err;
}

void MyUnionXDataUniqueRefListA_dump(MyUnionXDataUniqueRefList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataUniqueRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyUnionXDataUniqueRefListA_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyUnionXDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataUniqueRefListA_fdump(FILE *fp, MyUnionXDataUniqueRefList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataUniqueRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyUnionXDataUniqueRefListW_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionXDataW_dump(p, tab);
	return err;
}

void MyUnionXDataUniqueRefListW_dump(MyUnionXDataUniqueRefList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataUniqueRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionXDataUniqueRefListW_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionXDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataUniqueRefListW_fdump(FILE *fp, MyUnionXDataUniqueRefList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataUniqueRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyUnionXDataUniqueRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataOrderedRefList
static Dz1Error MyUnionXDataOrderedRefList_add(MyUnionXDataOrderedRefList *p, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionXDataOrderedRefList_remove(MyUnionXDataOrderedRefList *p, MyUnionXData *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyUnionXData *MyUnionXDataOrderedRefList_extract(MyUnionXDataOrderedRefList *p, MyUnionXData *key)
{
	return (MyUnionXData *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyUnionXDataOrderedRefListMkArrArg
{
	MyUnionXData **arr;
	unsigned int idx;
} MyUnionXDataOrderedRefListMkArrArg;

static Dz1Error _MyUnionXDataOrderedRefList_get_array(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataOrderedRefListMkArrArg *arg = (MyUnionXDataOrderedRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionXData **MyUnionXDataOrderedRefList_get_array(MyUnionXDataOrderedRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionXData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionXData **)Dz1Calloc(sizeof(MyUnionXData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionXDataOrderedRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionXDataOrderedRefList_get_array, (void *)&arg);
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

static Dz1Error MyUnionXDataOrderedRefList_travelForward(MyUnionXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionXDataOrderedRefList_travelBackward(MyUnionXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionXData *MyUnionXDataOrderedRefList_find(MyUnionXDataOrderedRefList *p, MyUnionXData *key)
{
	return (MyUnionXData *)Dz1OrderedFifo_find(p->storage, key);
}

static MyUnionXData *MyUnionXDataOrderedRefList_getHead(MyUnionXDataOrderedRefList *p)
{
	return (MyUnionXData *)Dz1OrderedFifo_getHead(p->storage);
}

static MyUnionXData *MyUnionXDataOrderedRefList_getTail(MyUnionXDataOrderedRefList *p)
{
	return (MyUnionXData *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyUnionXDataOrderedRefList_count(MyUnionXDataOrderedRefList *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyUnionXDataOrderedRefList *MyUnionXDataOrderedRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataOrderedRefList *ret = (MyUnionXDataOrderedRefList *)Dz1Calloc(sizeof(MyUnionXDataOrderedRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataOrderedRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyUnionXData_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionXDataOrderedRefList_count;
			ret->travel = MyUnionXDataOrderedRefList_travelForward;
			ret->travelForward = MyUnionXDataOrderedRefList_travelForward;
			ret->travelBackward = MyUnionXDataOrderedRefList_travelBackward;
			ret->get_array = MyUnionXDataOrderedRefList_get_array;
			ret->add = MyUnionXDataOrderedRefList_add;
			ret->remove = MyUnionXDataOrderedRefList_remove;
			ret->find = MyUnionXDataOrderedRefList_find;
			ret->extract = MyUnionXDataOrderedRefList_extract;
			ret->getHead = MyUnionXDataOrderedRefList_getHead;
			ret->getTail = MyUnionXDataOrderedRefList_getTail;
			ret->cmp = MyUnionXData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataOrderedRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionXDataOrderedRefList_clone(void *ptr, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataOrderedRefList *p = (MyUnionXDataOrderedRefList *)ptr;
	MyUnionXData *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionXDataOrderedRefList *MyUnionXDataOrderedRefList_clone(MyUnionXDataOrderedRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataOrderedRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionXDataOrderedRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataOrderedRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionXDataOrderedRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataOrderedRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionXDataOrderedRefList_purge(MyUnionXDataOrderedRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyUnionXDataOrderedRefList_del(MyUnionXDataOrderedRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionXDataOrderedRefListA_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyUnionXDataA_dump(p, tab);
	return err;
}

void MyUnionXDataOrderedRefListA_dump(MyUnionXDataOrderedRefList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataOrderedRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyUnionXDataOrderedRefListA_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyUnionXDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataOrderedRefListA_fdump(FILE *fp, MyUnionXDataOrderedRefList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataOrderedRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyUnionXDataOrderedRefListW_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionXDataW_dump(p, tab);
	return err;
}

void MyUnionXDataOrderedRefListW_dump(MyUnionXDataOrderedRefList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataOrderedRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionXDataOrderedRefListW_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionXDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataOrderedRefListW_fdump(FILE *fp, MyUnionXDataOrderedRefList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataOrderedRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyUnionXDataOrderedRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataRefList
static Dz1Error MyUnionXDataRefList_add(MyUnionXDataRefList *p, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionXDataRefList_remove(MyUnionXDataRefList *p, MyUnionXData *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyUnionXData *MyUnionXDataRefList_extract(MyUnionXDataRefList *p, MyUnionXData *ptr)
{
	return (MyUnionXData *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyUnionXDataRefListMkArrArg
{
	MyUnionXData **arr;
	unsigned int idx;
} MyUnionXDataRefListMkArrArg;

static Dz1Error _MyUnionXDataRefList_get_array(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataRefListMkArrArg *arg = (MyUnionXDataRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionXData **MyUnionXDataRefList_get_array(MyUnionXDataRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionXData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionXData **)Dz1Calloc(sizeof(MyUnionXData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionXDataRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionXDataRefList_get_array, (void *)&arg);
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

static Dz1Error MyUnionXDataRefList_travelForward(MyUnionXDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionXDataRefList_travelBackward(MyUnionXDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyUnionXDataRefListFindArg
{
	MyUnionXData *key;
	MyUnionXData *ret;
	int (*cmp)(MyUnionXData *a, MyUnionXData *b);
} MyUnionXDataRefListFindArg;

static Dz1Error _MyUnionXDataRefList_find(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyUnionXDataRefListFindArg *arg = (MyUnionXDataRefListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyUnionXData *MyUnionXDataRefList_find(MyUnionXDataRefList *p, MyUnionXData *key)
{
	MyUnionXDataRefListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyUnionXDataRefList_find, (void *)&arg);
	return arg.ret;
}

static MyUnionXData *MyUnionXDataRefList_getHead(MyUnionXDataRefList *p)
{
	return (MyUnionXData *)Dz1Fifo_getFirst(p->storage);
}

static MyUnionXData *MyUnionXDataRefList_getTail(MyUnionXDataRefList *p)
{
	return (MyUnionXData *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyUnionXDataRefList_count(MyUnionXDataRefList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionXDataRefList *MyUnionXDataRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataRefList *ret = (MyUnionXDataRefList *)Dz1Calloc(sizeof(MyUnionXDataRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionXDataRefList_count;
			ret->travel = MyUnionXDataRefList_travelForward;
			ret->travelForward = MyUnionXDataRefList_travelForward;
			ret->travelBackward = MyUnionXDataRefList_travelBackward;
			ret->get_array = MyUnionXDataRefList_get_array;
			ret->add = MyUnionXDataRefList_add;
			ret->remove = MyUnionXDataRefList_remove;
			ret->find = MyUnionXDataRefList_find;
			ret->extract = MyUnionXDataRefList_extract;
			ret->getHead = MyUnionXDataRefList_getHead;
			ret->getTail = MyUnionXDataRefList_getTail;
			ret->cmp = MyUnionXData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionXDataRefList_clone(void *ptr, MyUnionXData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionXDataRefList *p = (MyUnionXDataRefList *)ptr;
	MyUnionXData *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionXDataRefList *MyUnionXDataRefList_clone(MyUnionXDataRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionXDataRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionXDataRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionXDataRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionXDataRefList_purge(MyUnionXDataRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionXDataRefList_del(MyUnionXDataRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionXDataRefListA_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyUnionXDataA_dump(p, tab);
	return err;
}

void MyUnionXDataRefListA_dump(MyUnionXDataRefList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyUnionXDataRefListA_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyUnionXDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataRefListA_fdump(FILE *fp, MyUnionXDataRefList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyUnionXDataRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyUnionXDataRefListW_dump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionXDataW_dump(p, tab);
	return err;
}

void MyUnionXDataRefListW_dump(MyUnionXDataRefList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionXDataRefListW_fdump(void *ptr, MyUnionXData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionXDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionXDataRefListW_fdump(FILE *fp, MyUnionXDataRefList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionXDataRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyUnionXDataRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataInfo
// void MyUnionXDataInfo_obj_ptr_arr_del(MyUnionXData **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyUnionXDataInfo, MyUnionXData*, obj_ptr_arr, u32_t, MyUnionXData_del)
// void MyUnionXDataInfo_obj_ptr_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyUnionXDataInfo, MyUnionXData*, obj_ptr_arr, u32_t)
// MyUnionXData **MyUnionXDataInfo_obj_ptr_arr_clone(MyUnionXData **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyUnionXDataInfo, MyUnionXData*, obj_ptr_arr, u32_t, MyUnionXData_clone)
// void MyUnionXDataInfo_obj_ptr_arr_dump(MyUnionXData **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_dump(MyUnionXDataInfo, MyUnionXData*, obj_ptr_arr, u32_t, ".", MyUnionXData_dump)
// void MyUnionXDataInfo_obj_ptr_arr_fdump(FILE *fp, MyUnionXData **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_fdump(MyUnionXDataInfo, MyUnionXData*, obj_ptr_arr, u32_t, ".", MyUnionXData_fdump)

// void MyUnionXDataInfo_obj_arr_del(MyUnionXData *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(MyUnionXDataInfo, MyUnionXData, obj_arr, u32_t, MyUnionXData_purge)
// void MyUnionXDataInfo_obj_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(MyUnionXDataInfo, MyUnionXData, obj_arr, u32_t)
// MyUnionXData *MyUnionXDataInfo_obj_arr_clone(MyUnionXData *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(MyUnionXDataInfo, MyUnionXData, obj_arr, u32_t, MyUnionXData_copy)
// void MyUnionXDataInfo_obj_arr_dump(MyUnionXData *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_dump(MyUnionXDataInfo, MyUnionXData, obj_arr, u32_t, ".", MyUnionXData_dump)
// void MyUnionXDataInfo_obj_arr_fdump(FILE *fp, MyUnionXData *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_fdump(MyUnionXDataInfo, MyUnionXData, obj_arr, u32_t, ".", MyUnionXData_fdump)

// void MyUnionXDataInfo_prims_arr_del(u64_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(MyUnionXDataInfo, u64_t, prims_arr, u32_t)
// void MyUnionXDataInfo_prims_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(MyUnionXDataInfo, u64_t, prims_arr)
// u64_t *MyUnionXDataInfo_prims_arr_clone(u64_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(MyUnionXDataInfo, u64_t, prims_arr, u32_t)
// void MyUnionXDataInfo_prims_arr_dump(u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_dump(MyUnionXDataInfo, u64_t, prims_arr, u32_t, " = ", Dz1u64_dump)
// void MyUnionXDataInfo_prims_arr_fdump(FILE *fp, u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_fdump(MyUnionXDataInfo, u64_t, prims_arr, u32_t, " = ", Dz1u64_fdump)

// void MyUnionXDataInfo_primptrs_arr_del(u64_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyUnionXDataInfo, u64_t*, primptrs_arr, u32_t, Dz1u64_del)
// void MyUnionXDataInfo_primptrs_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyUnionXDataInfo, u64_t*, primptrs_arr, u32_t)
// u64_t **MyUnionXDataInfo_primptrs_arr_clone(u64_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyUnionXDataInfo, u64_t*, primptrs_arr, u32_t, Dz1u64_clone)
// void MyUnionXDataInfo_primptrs_arr_dump(u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_dump(MyUnionXDataInfo, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64_dump)
// void MyUnionXDataInfo_primptrs_arr_fdump(FILE *fp, u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_fdump(MyUnionXDataInfo, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64_fdump)

MyUnionXDataInfo *MyUnionXDataInfo_new(MyUnionXData **obj_ptr_arr/*_e_clone*/, 
									   u32_t obj_ptr_cnt, 
									   MyUnionXData *obj_arr/*_e_copy*/, 
									   u32_t obj_cnt, 
									   u64_t *prims_arr/*_e_copy*/, 
									   u32_t prims_cnt, 
									   u64_t **primptrs_arr/*_e_clone*/, 
									   u32_t primptrs_cnt, 
									   s32_t *i_val/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionXDataInfo *__internal_ret = (MyUnionXDataInfo *)Dz1Calloc(sizeof(MyUnionXDataInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnionXDataInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (obj_ptr_arr != NULL && (__internal_ret->obj_ptr_arr = MyUnionXDataInfo_obj_ptr_arr_clone(obj_ptr_arr, obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (obj_arr != NULL && (__internal_ret->obj_arr = MyUnionXDataInfo_obj_arr_clone(obj_arr, obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (prims_arr != NULL && (__internal_ret->prims_arr = MyUnionXDataInfo_prims_arr_clone(prims_arr, prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (primptrs_arr != NULL && (__internal_ret->primptrs_arr = MyUnionXDataInfo_primptrs_arr_clone(primptrs_arr, primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->obj_ptr_cnt = obj_ptr_cnt;
			__internal_ret->obj_cnt = obj_cnt;
			__internal_ret->prims_cnt = prims_cnt;
			__internal_ret->primptrs_cnt = primptrs_cnt;
			__internal_ret->i_val = i_val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyUnionXDataInfo_copy(MyUnionXDataInfo *dst, MyUnionXDataInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->obj_ptr_arr != NULL && (dst->obj_ptr_arr = MyUnionXDataInfo_obj_ptr_arr_clone(src->obj_ptr_arr, src->obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->obj_arr != NULL && (dst->obj_arr = MyUnionXDataInfo_obj_arr_clone(src->obj_arr, src->obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->prims_arr != NULL && (dst->prims_arr = MyUnionXDataInfo_prims_arr_clone(src->prims_arr, src->prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->primptrs_arr != NULL && (dst->primptrs_arr = MyUnionXDataInfo_primptrs_arr_clone(src->primptrs_arr, src->primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
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

MyUnionXDataInfo *MyUnionXDataInfo_clone(MyUnionXDataInfo *src, Dz1Error *err)
{
	MyUnionXDataInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyUnionXDataInfo *)Dz1Calloc(sizeof(MyUnionXDataInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnionXDataInfo_delAndSetNull, (void *)&dst);
		if (MyUnionXDataInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionXDataInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyUnionXDataInfo_purge(MyUnionXDataInfo *p)
{
	if (p == NULL) return;
	MyUnionXDataInfo_obj_ptr_arr_del(p->obj_ptr_arr, p->obj_ptr_cnt);
	MyUnionXDataInfo_obj_arr_del(p->obj_arr, p->obj_cnt);
	MyUnionXDataInfo_prims_arr_del(p->prims_arr, p->prims_cnt);
	MyUnionXDataInfo_primptrs_arr_del(p->primptrs_arr, p->primptrs_cnt);
}

void MyUnionXDataInfo_del(MyUnionXDataInfo *p)
{
	if (p == NULL) return;
	MyUnionXDataInfo_purge(p);
	Dz1Free(p);
}

void MyUnionXDataInfo_dump(MyUnionXDataInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("obj_ptr_arr = ")); MyUnionXDataInfo_obj_ptr_arr_dump(p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("obj_ptr_cnt = ")); Dz1u32_dump(&p->obj_ptr_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("obj_arr = ")); MyUnionXDataInfo_obj_arr_dump(p->obj_arr, p->obj_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("obj_cnt = ")); Dz1u32_dump(&p->obj_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("prims_arr = ")); MyUnionXDataInfo_prims_arr_dump(p->prims_arr, p->prims_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("prims_cnt = ")); Dz1u32_dump(&p->prims_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("primptrs_arr = ")); MyUnionXDataInfo_primptrs_arr_dump(p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("primptrs_cnt = ")); Dz1u32_dump(&p->primptrs_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("i_val = ")); Dz1s32_dump(p->i_val, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void MyUnionXDataInfo_fdump(FILE *fp, MyUnionXDataInfo *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_ptr_arr = ")); MyUnionXDataInfo_obj_ptr_arr_fdump(fp, p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_ptr_cnt = ")); Dz1u32_fdump(fp, &p->obj_ptr_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_arr = ")); MyUnionXDataInfo_obj_arr_fdump(fp, p->obj_arr, p->obj_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_cnt = ")); Dz1u32_fdump(fp, &p->obj_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("prims_arr = ")); MyUnionXDataInfo_prims_arr_fdump(fp, p->prims_arr, p->prims_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("prims_cnt = ")); Dz1u32_fdump(fp, &p->prims_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("primptrs_arr = ")); MyUnionXDataInfo_primptrs_arr_fdump(fp, p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("primptrs_cnt = ")); Dz1u32_fdump(fp, &p->primptrs_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("i_val = ")); Dz1s32_fdump(fp, p->i_val, tab); 
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionXDataInfo
////////////////////////////////////////////////////////////////////////////////

