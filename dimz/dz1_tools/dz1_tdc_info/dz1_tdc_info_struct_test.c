////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_struct_test.h"

#include "dz1_tdc_info_test_ref.h"
////////////////////////////////////////////////////////////////////////////////
// MyDataInfo
MyDataInfo *MyDataInfo_new(MyDataInfo *next/*_ref*/, 
						   MyDataEntry *data, 
						   TestExternalType *opt, 
						   TestTypeInfo *info1, 
						   TestTypeInfo *info2, 
						   TestTypeInfo *info3/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataInfo *__internal_ret = (MyDataInfo *)Dz1Calloc(sizeof(MyDataInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyDataInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (TestTypeInfo_copy(&__internal_ret->info1, info1, errp) == FALSE) ERR_OUT(errp);
		else
		{
			__internal_ret->next = next;
			__internal_ret->data = data;
			__internal_ret->opt = opt;
			__internal_ret->info2 = info2;
			__internal_ret->info3 = info3;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyDataInfo_copy(MyDataInfo *dst, MyDataInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->data && (dst->data = MyDataEntry_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else if (src->opt && (dst->opt = TestExternalType_clone(src->opt, errp)) == NULL) ERR_OUT(errp);
	else if (TestTypeInfo_copy(&dst->info1, &src->info1, errp) == FALSE) ERR_OUT(errp);
	else if (src->info2 && (dst->info2 = TestTypeInfo_clone(src->info2, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->next = src->next;
		dst->info3 = src->info3;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyDataInfo *MyDataInfo_clone(MyDataInfo *src, Dz1Error *err)
{
	MyDataInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyDataInfo *)Dz1Calloc(sizeof(MyDataInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyDataInfo_delAndSetNull, (void *)&dst);
		if (MyDataInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyDataInfo_purge(MyDataInfo *p)
{
	if (p == NULL) return;
	MyDataEntry_del(p->data);
	TestExternalType_del(p->opt);
	TestTypeInfo_purge(&p->info1);
	TestTypeInfo_del(p->info2);
}

void MyDataInfo_del(MyDataInfo *p)
{
	if (p == NULL) return;
	MyDataInfo_purge(p);
	Dz1Free(p);
}

void MyDataInfo_dump(MyDataInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); MyDataEntry_dump(p->data, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("opt = %p\n"), p->opt);
		// _imp_dump
		// _imp_dump : scalar
		Dz1Thread_tprintf(tab, Dz1T("info1 = ")); TestTypeInfo_dump(&p->info1, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("info2 = ")); TestTypeInfo_dump(p->info2, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("info3 = ")); TestTypeInfo_dump(p->info3, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void MyDataInfo_fdump(FILE *fp, MyDataInfo *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("data = ")); MyDataEntry_fdump(fp, p->data, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_ftprintf(fp, tab, Dz1T("opt = %p\n"), p->opt);
		// _imp_dump
		// _imp_dump : scalar
		Dz1Thread_ftprintf(fp, tab, Dz1T("info1 = ")); TestTypeInfo_fdump(fp, &p->info1, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_ftprintf(fp, tab, Dz1T("info2 = ")); TestTypeInfo_fdump(fp, p->info2, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_ftprintf(fp, tab, Dz1T("info3 = ")); TestTypeInfo_fdump(fp, p->info3, tab); 
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataEntry
MyDataEntry *MyDataEntry_new(Dz1Asn1UTF8Str *name, u32_t val, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataEntry *__internal_ret = (MyDataEntry *)Dz1Calloc(sizeof(MyDataEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyDataEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->name = name;
		__internal_ret->val = val;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyDataEntry_copy(MyDataEntry *dst, MyDataEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Asn1UTF8Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->val = src->val;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyDataEntry *MyDataEntry_clone(MyDataEntry *src, Dz1Error *err)
{
	MyDataEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyDataEntry *)Dz1Calloc(sizeof(MyDataEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyDataEntry_delAndSetNull, (void *)&dst);
		if (MyDataEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyDataEntry_purge(MyDataEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
}

void MyDataEntry_del(MyDataEntry *p)
{
	if (p == NULL) return;
	MyDataEntry_purge(p);
	Dz1Free(p);
}

void MyDataEntry_dump(MyDataEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Asn1UTF8Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("val = ")); Dz1u32_dump(&p->val, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void MyDataEntry_fdump(FILE *fp, MyDataEntry *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_ftprintf(fp, tab, Dz1T("name = ")); Dz1Asn1UTF8Str_fdump(fp, p->name, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("val = ")); Dz1u32_fdump(fp, &p->val, tab); 
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
int MyDataEntry_cmp(MyDataEntry *a, MyDataEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->name, b->name)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}
// MyDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueList
static Dz1Error MyDataUniqueList_add(MyDataUniqueList *p, MyDataEntry *data)
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

static bool_t MyDataUniqueList_remove(MyDataUniqueList *p, MyDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntry *MyDataUniqueList_extract(MyDataUniqueList *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueListMkArrArg
{
	MyDataEntry **arr;
	unsigned int idx;
} MyDataUniqueListMkArrArg;

static Dz1Error _MyDataUniqueList_get_array(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueListMkArrArg *arg = (MyDataUniqueListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntry **MyDataUniqueList_get_array(MyDataUniqueList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntry **)Dz1Calloc(sizeof(MyDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueList_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueList_travelForward(MyDataUniqueList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueList_travelBackward(MyDataUniqueList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntry *MyDataUniqueList_find(MyDataUniqueList *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1AATree_find(p->storage, key);
}

static MyDataEntry *MyDataUniqueList_getHead(MyDataUniqueList *p)
{
	return (MyDataEntry *)Dz1AATree_getHead(p->storage);
}

static MyDataEntry *MyDataUniqueList_getTail(MyDataUniqueList *p)
{
	return (MyDataEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueList_count(MyDataUniqueList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueList *MyDataUniqueList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueList *ret = (MyDataUniqueList *)Dz1Calloc(sizeof(MyDataUniqueList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntry_cmp,
				(Dz1DelFunc)MyDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueList_count;
			ret->travel = MyDataUniqueList_travelForward;
			ret->travelForward = MyDataUniqueList_travelForward;
			ret->travelBackward = MyDataUniqueList_travelBackward;
			ret->get_array = MyDataUniqueList_get_array;
			ret->add = MyDataUniqueList_add;
			ret->remove = MyDataUniqueList_remove;
			ret->find = MyDataUniqueList_find;
			ret->extract = MyDataUniqueList_extract;
			ret->getHead = MyDataUniqueList_getHead;
			ret->getTail = MyDataUniqueList_getTail;
			ret->cmp = MyDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueList_clone(void *ptr, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueList *p = (MyDataUniqueList *)ptr;
	MyDataEntry *cloned = MyDataEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueList *MyDataUniqueList_clone(MyDataUniqueList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueList_purge(MyDataUniqueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueList_del(MyDataUniqueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueList_dump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("cos = ")); MyDataEntry_dump(p, tab);
	return err;
}

void MyDataUniqueList_dump(MyDataUniqueList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataUniqueList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyDataUniqueList_fdump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("cos = ")); MyDataEntry_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueList_fdump(FILE *fp, MyDataUniqueList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataUniqueList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataUniqueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedList
static Dz1Error MyDataOrderedList_add(MyDataOrderedList *p, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedList_remove(MyDataOrderedList *p, MyDataEntry *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntry *MyDataOrderedList_extract(MyDataOrderedList *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedListMkArrArg
{
	MyDataEntry **arr;
	unsigned int idx;
} MyDataOrderedListMkArrArg;

static Dz1Error _MyDataOrderedList_get_array(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedListMkArrArg *arg = (MyDataOrderedListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntry **MyDataOrderedList_get_array(MyDataOrderedList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntry **)Dz1Calloc(sizeof(MyDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedList_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedList_travelForward(MyDataOrderedList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedList_travelBackward(MyDataOrderedList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntry *MyDataOrderedList_find(MyDataOrderedList *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntry *MyDataOrderedList_getHead(MyDataOrderedList *p)
{
	return (MyDataEntry *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntry *MyDataOrderedList_getTail(MyDataOrderedList *p)
{
	return (MyDataEntry *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedList_count(MyDataOrderedList *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedList *MyDataOrderedList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedList *ret = (MyDataOrderedList *)Dz1Calloc(sizeof(MyDataOrderedList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntry_cmp,
				(Dz1DelFunc)MyDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedList_count;
			ret->travel = MyDataOrderedList_travelForward;
			ret->travelForward = MyDataOrderedList_travelForward;
			ret->travelBackward = MyDataOrderedList_travelBackward;
			ret->get_array = MyDataOrderedList_get_array;
			ret->add = MyDataOrderedList_add;
			ret->remove = MyDataOrderedList_remove;
			ret->find = MyDataOrderedList_find;
			ret->extract = MyDataOrderedList_extract;
			ret->getHead = MyDataOrderedList_getHead;
			ret->getTail = MyDataOrderedList_getTail;
			ret->cmp = MyDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedList_clone(void *ptr, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedList *p = (MyDataOrderedList *)ptr;
	MyDataEntry *cloned = MyDataEntry_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedList *MyDataOrderedList_clone(MyDataOrderedList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedList_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedList_purge(MyDataOrderedList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedList_del(MyDataOrderedList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedList_dump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("tan = ")); MyDataEntry_dump(p, tab);
	return err;
}

void MyDataOrderedList_dump(MyDataOrderedList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataOrderedList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyDataOrderedList_fdump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("tan = ")); MyDataEntry_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedList_fdump(FILE *fp, MyDataOrderedList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataOrderedList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataOrderedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataList
static Dz1Error MyDataList_add(MyDataList *p, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataList_remove(MyDataList *p, MyDataEntry *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyDataEntry *MyDataList_extract(MyDataList *p, MyDataEntry *ptr)
{
	return (MyDataEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataListMkArrArg
{
	MyDataEntry **arr;
	unsigned int idx;
} MyDataListMkArrArg;

static Dz1Error _MyDataList_get_array(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataListMkArrArg *arg = (MyDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntry **MyDataList_get_array(MyDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntry **)Dz1Calloc(sizeof(MyDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataList_get_array, (void *)&arg);
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

static Dz1Error MyDataList_travelForward(MyDataList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataList_travelBackward(MyDataList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataListFindArg
{
	MyDataEntry *key;
	MyDataEntry *ret;
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataListFindArg;

static Dz1Error _MyDataList_find(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataListFindArg *arg = (MyDataListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntry *MyDataList_find(MyDataList *p, MyDataEntry *key)
{
	MyDataListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataList_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntry *MyDataList_getHead(MyDataList *p)
{
	return (MyDataEntry *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntry *MyDataList_getTail(MyDataList *p)
{
	return (MyDataEntry *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataList_count(MyDataList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataList *MyDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataList *ret = (MyDataList *)Dz1Calloc(sizeof(MyDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataList_count;
			ret->travel = MyDataList_travelForward;
			ret->travelForward = MyDataList_travelForward;
			ret->travelBackward = MyDataList_travelBackward;
			ret->get_array = MyDataList_get_array;
			ret->add = MyDataList_add;
			ret->remove = MyDataList_remove;
			ret->find = MyDataList_find;
			ret->extract = MyDataList_extract;
			ret->getHead = MyDataList_getHead;
			ret->getTail = MyDataList_getTail;
			ret->cmp = MyDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataList_clone(void *ptr, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataList *p = (MyDataList *)ptr;
	MyDataEntry *cloned = MyDataEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataList *MyDataList_clone(MyDataList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataList_purge(MyDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataList_del(MyDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataList_dump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_dumptab(tab); MyDataEntry_dump(p, tab);
	return err;
}

void MyDataList_dump(MyDataList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyDataList_fdump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_fdumptab(arg->fp, tab); MyDataEntry_fdump(arg->fp, p, tab);
	return err;
}

void MyDataList_fdump(FILE *fp, MyDataList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefList
static Dz1Error MyDataUniqueRefList_add(MyDataUniqueRefList *p, MyDataEntry *data)
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

static bool_t MyDataUniqueRefList_remove(MyDataUniqueRefList *p, MyDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntry *MyDataUniqueRefList_extract(MyDataUniqueRefList *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueRefListMkArrArg
{
	MyDataEntry **arr;
	unsigned int idx;
} MyDataUniqueRefListMkArrArg;

static Dz1Error _MyDataUniqueRefList_get_array(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefListMkArrArg *arg = (MyDataUniqueRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntry **MyDataUniqueRefList_get_array(MyDataUniqueRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntry **)Dz1Calloc(sizeof(MyDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueRefList_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueRefList_travelForward(MyDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueRefList_travelBackward(MyDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntry *MyDataUniqueRefList_find(MyDataUniqueRefList *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1AATree_find(p->storage, key);
}

static MyDataEntry *MyDataUniqueRefList_getHead(MyDataUniqueRefList *p)
{
	return (MyDataEntry *)Dz1AATree_getHead(p->storage);
}

static MyDataEntry *MyDataUniqueRefList_getTail(MyDataUniqueRefList *p)
{
	return (MyDataEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueRefList_count(MyDataUniqueRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueRefList *MyDataUniqueRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefList *ret = (MyDataUniqueRefList *)Dz1Calloc(sizeof(MyDataUniqueRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueRefList_count;
			ret->travel = MyDataUniqueRefList_travelForward;
			ret->travelForward = MyDataUniqueRefList_travelForward;
			ret->travelBackward = MyDataUniqueRefList_travelBackward;
			ret->get_array = MyDataUniqueRefList_get_array;
			ret->add = MyDataUniqueRefList_add;
			ret->remove = MyDataUniqueRefList_remove;
			ret->find = MyDataUniqueRefList_find;
			ret->extract = MyDataUniqueRefList_extract;
			ret->getHead = MyDataUniqueRefList_getHead;
			ret->getTail = MyDataUniqueRefList_getTail;
			ret->cmp = MyDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueRefList_clone(void *ptr, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefList *p = (MyDataUniqueRefList *)ptr;
	MyDataEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueRefList *MyDataUniqueRefList_clone(MyDataUniqueRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueRefList_purge(MyDataUniqueRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueRefList_del(MyDataUniqueRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueRefList_dump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyDataEntry_dump(p, tab);
	return err;
}

void MyDataUniqueRefList_dump(MyDataUniqueRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataUniqueRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyDataUniqueRefList_fdump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyDataEntry_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueRefList_fdump(FILE *fp, MyDataUniqueRefList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataUniqueRefList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataUniqueRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefList
static Dz1Error MyDataOrderedRefList_add(MyDataOrderedRefList *p, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedRefList_remove(MyDataOrderedRefList *p, MyDataEntry *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntry *MyDataOrderedRefList_extract(MyDataOrderedRefList *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedRefListMkArrArg
{
	MyDataEntry **arr;
	unsigned int idx;
} MyDataOrderedRefListMkArrArg;

static Dz1Error _MyDataOrderedRefList_get_array(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefListMkArrArg *arg = (MyDataOrderedRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntry **MyDataOrderedRefList_get_array(MyDataOrderedRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntry **)Dz1Calloc(sizeof(MyDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedRefList_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedRefList_travelForward(MyDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedRefList_travelBackward(MyDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntry *MyDataOrderedRefList_find(MyDataOrderedRefList *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntry *MyDataOrderedRefList_getHead(MyDataOrderedRefList *p)
{
	return (MyDataEntry *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntry *MyDataOrderedRefList_getTail(MyDataOrderedRefList *p)
{
	return (MyDataEntry *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedRefList_count(MyDataOrderedRefList *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedRefList *MyDataOrderedRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefList *ret = (MyDataOrderedRefList *)Dz1Calloc(sizeof(MyDataOrderedRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedRefList_count;
			ret->travel = MyDataOrderedRefList_travelForward;
			ret->travelForward = MyDataOrderedRefList_travelForward;
			ret->travelBackward = MyDataOrderedRefList_travelBackward;
			ret->get_array = MyDataOrderedRefList_get_array;
			ret->add = MyDataOrderedRefList_add;
			ret->remove = MyDataOrderedRefList_remove;
			ret->find = MyDataOrderedRefList_find;
			ret->extract = MyDataOrderedRefList_extract;
			ret->getHead = MyDataOrderedRefList_getHead;
			ret->getTail = MyDataOrderedRefList_getTail;
			ret->cmp = MyDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedRefList_clone(void *ptr, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefList *p = (MyDataOrderedRefList *)ptr;
	MyDataEntry *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedRefList *MyDataOrderedRefList_clone(MyDataOrderedRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedRefList_purge(MyDataOrderedRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedRefList_del(MyDataOrderedRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedRefList_dump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyDataEntry_dump(p, tab);
	return err;
}

void MyDataOrderedRefList_dump(MyDataOrderedRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataOrderedRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyDataOrderedRefList_fdump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyDataEntry_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedRefList_fdump(FILE *fp, MyDataOrderedRefList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataOrderedRefList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataOrderedRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefList
static Dz1Error MyDataRefList_add(MyDataRefList *p, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataRefList_remove(MyDataRefList *p, MyDataEntry *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyDataEntry *MyDataRefList_extract(MyDataRefList *p, MyDataEntry *ptr)
{
	return (MyDataEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataRefListMkArrArg
{
	MyDataEntry **arr;
	unsigned int idx;
} MyDataRefListMkArrArg;

static Dz1Error _MyDataRefList_get_array(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefListMkArrArg *arg = (MyDataRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntry **MyDataRefList_get_array(MyDataRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntry **)Dz1Calloc(sizeof(MyDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataRefList_get_array, (void *)&arg);
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

static Dz1Error MyDataRefList_travelForward(MyDataRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataRefList_travelBackward(MyDataRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataRefListFindArg
{
	MyDataEntry *key;
	MyDataEntry *ret;
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataRefListFindArg;

static Dz1Error _MyDataRefList_find(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataRefListFindArg *arg = (MyDataRefListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntry *MyDataRefList_find(MyDataRefList *p, MyDataEntry *key)
{
	MyDataRefListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataRefList_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntry *MyDataRefList_getHead(MyDataRefList *p)
{
	return (MyDataEntry *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntry *MyDataRefList_getTail(MyDataRefList *p)
{
	return (MyDataEntry *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataRefList_count(MyDataRefList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataRefList *MyDataRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefList *ret = (MyDataRefList *)Dz1Calloc(sizeof(MyDataRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataRefList_count;
			ret->travel = MyDataRefList_travelForward;
			ret->travelForward = MyDataRefList_travelForward;
			ret->travelBackward = MyDataRefList_travelBackward;
			ret->get_array = MyDataRefList_get_array;
			ret->add = MyDataRefList_add;
			ret->remove = MyDataRefList_remove;
			ret->find = MyDataRefList_find;
			ret->extract = MyDataRefList_extract;
			ret->getHead = MyDataRefList_getHead;
			ret->getTail = MyDataRefList_getTail;
			ret->cmp = MyDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataRefList_clone(void *ptr, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefList *p = (MyDataRefList *)ptr;
	MyDataEntry *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataRefList *MyDataRefList_clone(MyDataRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataRefList_purge(MyDataRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataRefList_del(MyDataRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataRefList_dump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyDataEntry_dump(p, tab);
	return err;
}

void MyDataRefList_dump(MyDataRefList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataRefList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyDataRefList_fdump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyDataEntry_fdump(arg->fp, p, tab);
	return err;
}

void MyDataRefList_fdump(FILE *fp, MyDataRefList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataRefList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataIndex
static Dz1Error MyDataIndex_add(MyDataIndex *p, MyDataEntry *data)
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

static bool_t MyDataIndex_remove(MyDataIndex *p, MyDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntry *MyDataIndex_extract(MyDataIndex *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataIndexMkArrArg
{
	MyDataEntry **arr;
	unsigned int idx;
} MyDataIndexMkArrArg;

static Dz1Error _MyDataIndex_get_array(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataIndexMkArrArg *arg = (MyDataIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntry **MyDataIndex_get_array(MyDataIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntry **)Dz1Calloc(sizeof(MyDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataIndex_get_array, (void *)&arg);
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

static Dz1Error MyDataIndex_travelForward(MyDataIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataIndex_travelBackward(MyDataIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntry *MyDataIndex_find(MyDataIndex *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyDataIndex_count(MyDataIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _MyDataIndex_cmp(MyDataEntry *a, MyDataEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}

MyDataIndex *MyDataIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataIndex *ret = (MyDataIndex *)Dz1Calloc(sizeof(MyDataIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_MyDataIndex_cmp, (Dz1DelFunc)MyDataEntry_del, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataIndex_count;
			ret->travel = MyDataIndex_travelForward;
			ret->travelForward = MyDataIndex_travelForward;
			ret->travelBackward = MyDataIndex_travelBackward;
			ret->get_array = MyDataIndex_get_array;
			ret->add = MyDataIndex_add;
			ret->remove = MyDataIndex_remove;
			ret->find = MyDataIndex_find;
			ret->extract = MyDataIndex_extract;
			ret->cmp = _MyDataIndex_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataIndex_clone(void *ptr, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataIndex *p = (MyDataIndex *)ptr;
	MyDataEntry *cloned = MyDataEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataIndex *MyDataIndex_clone(MyDataIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataIndex_purge(MyDataIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataIndex_del(MyDataIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataIndex_dump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyDataEntry_dump(p, tab);
	return err;
}

void MyDataIndex_dump(MyDataIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataIndex_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyDataIndex_fdump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyDataEntry_fdump(arg->fp, p, tab);
	return err;
}

void MyDataIndex_fdump(FILE *fp, MyDataIndex *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataIndex_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefIndex
static Dz1Error MyDataRefIndex_add(MyDataRefIndex *p, MyDataEntry *data)
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

static bool_t MyDataRefIndex_remove(MyDataRefIndex *p, MyDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntry *MyDataRefIndex_extract(MyDataRefIndex *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataRefIndexMkArrArg
{
	MyDataEntry **arr;
	unsigned int idx;
} MyDataRefIndexMkArrArg;

static Dz1Error _MyDataRefIndex_get_array(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefIndexMkArrArg *arg = (MyDataRefIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntry **MyDataRefIndex_get_array(MyDataRefIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntry **)Dz1Calloc(sizeof(MyDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataRefIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataRefIndex_get_array, (void *)&arg);
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

static Dz1Error MyDataRefIndex_travelForward(MyDataRefIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataRefIndex_travelBackward(MyDataRefIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntry *MyDataRefIndex_find(MyDataRefIndex *p, MyDataEntry *key)
{
	return (MyDataEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyDataRefIndex_count(MyDataRefIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _MyDataRefIndex_cmp(MyDataEntry *a, MyDataEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}

MyDataRefIndex *MyDataRefIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefIndex *ret = (MyDataRefIndex *)Dz1Calloc(sizeof(MyDataRefIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_MyDataRefIndex_cmp, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataRefIndex_count;
			ret->travel = MyDataRefIndex_travelForward;
			ret->travelForward = MyDataRefIndex_travelForward;
			ret->travelBackward = MyDataRefIndex_travelBackward;
			ret->get_array = MyDataRefIndex_get_array;
			ret->add = MyDataRefIndex_add;
			ret->remove = MyDataRefIndex_remove;
			ret->find = MyDataRefIndex_find;
			ret->extract = MyDataRefIndex_extract;
			ret->cmp = _MyDataRefIndex_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataRefIndex_clone(void *ptr, MyDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefIndex *p = (MyDataRefIndex *)ptr;
	MyDataEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataRefIndex *MyDataRefIndex_clone(MyDataRefIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataRefIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataRefIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataRefIndex_purge(MyDataRefIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataRefIndex_del(MyDataRefIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataRefIndex_dump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyDataEntry_dump(p, tab);
	return err;
}

void MyDataRefIndex_dump(MyDataRefIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataRefIndex_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyDataRefIndex_fdump(void *ptr, MyDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyDataEntry_fdump(arg->fp, p, tab);
	return err;
}

void MyDataRefIndex_fdump(FILE *fp, MyDataRefIndex *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyDataRefIndex_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyDataRefIndex
////////////////////////////////////////////////////////////////////////////////

