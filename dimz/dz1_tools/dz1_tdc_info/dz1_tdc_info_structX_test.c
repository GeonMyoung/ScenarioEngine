////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_structX_test.h"

////////////////////////////////////////////////////////////////////////////////
// MyXDataEntry
MyXDataEntry *MyXDataEntry_new(Dz1Asn1UTF8Str *name, u32_t val, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataEntry *__internal_ret = (MyXDataEntry *)Dz1Calloc(sizeof(MyXDataEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyXDataEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->name = name;
		__internal_ret->val = val;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyXDataEntry_copy(MyXDataEntry *dst, MyXDataEntry *src, Dz1Error *err)
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

MyXDataEntry *MyXDataEntry_clone(MyXDataEntry *src, Dz1Error *err)
{
	MyXDataEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyXDataEntry *)Dz1Calloc(sizeof(MyXDataEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyXDataEntry_delAndSetNull, (void *)&dst);
		if (MyXDataEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyXDataEntry_purge(MyXDataEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
}

void MyXDataEntry_del(MyXDataEntry *p)
{
	if (p == NULL) return;
	MyXDataEntry_purge(p);
	Dz1Free(p);
}

void MyXDataEntryA_dump(MyXDataEntry *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "name = "); Dz1Asn1UTF8StrA_dump(p->name, tab); 
		Dz1ThreadA_tprintf(tab, "val = "); Dz1u32A_dump(&p->val, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void MyXDataEntryA_fdump(FILE *fp, MyXDataEntry *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_ftprintf(fp, tab, "name = "); Dz1Asn1UTF8StrA_fdump(fp, p->name, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "val = "); Dz1u32A_fdump(fp, &p->val, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void MyXDataEntryW_dump(MyXDataEntry *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"name = "); Dz1Asn1UTF8StrW_dump(p->name, tab); 
		Dz1ThreadW_tprintf(tab, L"val = "); Dz1u32W_dump(&p->val, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void MyXDataEntryW_fdump(FILE *fp, MyXDataEntry *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_ftprintf(fp, tab, L"name = "); Dz1Asn1UTF8StrW_fdump(fp, p->name, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"val = "); Dz1u32W_fdump(fp, &p->val, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
int MyXDataEntry_cmp(MyXDataEntry *a, MyXDataEntry *b)
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
// MyXDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataUniqueList
static Dz1Error MyXDataUniqueList_add(MyXDataUniqueList *p, MyXDataEntry *data)
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

static bool_t MyXDataUniqueList_remove(MyXDataUniqueList *p, MyXDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyXDataEntry *MyXDataUniqueList_extract(MyXDataUniqueList *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyXDataUniqueListMkArrArg
{
	MyXDataEntry **arr;
	unsigned int idx;
} MyXDataUniqueListMkArrArg;

static Dz1Error _MyXDataUniqueList_get_array(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataUniqueListMkArrArg *arg = (MyXDataUniqueListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyXDataEntry **MyXDataUniqueList_get_array(MyXDataUniqueList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyXDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyXDataEntry **)Dz1Calloc(sizeof(MyXDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyXDataUniqueListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyXDataUniqueList_get_array, (void *)&arg);
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

static Dz1Error MyXDataUniqueList_travelForward(MyXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyXDataUniqueList_travelBackward(MyXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyXDataEntry *MyXDataUniqueList_find(MyXDataUniqueList *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1AATree_find(p->storage, key);
}

static MyXDataEntry *MyXDataUniqueList_getHead(MyXDataUniqueList *p)
{
	return (MyXDataEntry *)Dz1AATree_getHead(p->storage);
}

static MyXDataEntry *MyXDataUniqueList_getTail(MyXDataUniqueList *p)
{
	return (MyXDataEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyXDataUniqueList_count(MyXDataUniqueList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyXDataUniqueList *MyXDataUniqueList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataUniqueList *ret = (MyXDataUniqueList *)Dz1Calloc(sizeof(MyXDataUniqueList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataUniqueList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyXDataEntry_cmp,
				(Dz1DelFunc)MyXDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyXDataUniqueList_count;
			ret->travel = MyXDataUniqueList_travelForward;
			ret->travelForward = MyXDataUniqueList_travelForward;
			ret->travelBackward = MyXDataUniqueList_travelBackward;
			ret->get_array = MyXDataUniqueList_get_array;
			ret->add = MyXDataUniqueList_add;
			ret->remove = MyXDataUniqueList_remove;
			ret->find = MyXDataUniqueList_find;
			ret->extract = MyXDataUniqueList_extract;
			ret->getHead = MyXDataUniqueList_getHead;
			ret->getTail = MyXDataUniqueList_getTail;
			ret->cmp = MyXDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataUniqueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyXDataUniqueList_clone(void *ptr, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataUniqueList *p = (MyXDataUniqueList *)ptr;
	MyXDataEntry *cloned = MyXDataEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyXDataUniqueList *MyXDataUniqueList_clone(MyXDataUniqueList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataUniqueList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyXDataUniqueList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataUniqueList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyXDataUniqueList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataUniqueList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyXDataUniqueList_purge(MyXDataUniqueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyXDataUniqueList_del(MyXDataUniqueList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyXDataUniqueListA_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyXDataEntryA_dump(p, tab);
	return err;
}

void MyXDataUniqueListA_dump(MyXDataUniqueList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyXDataUniqueListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyXDataUniqueListA_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyXDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataUniqueListA_fdump(FILE *fp, MyXDataUniqueList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyXDataUniqueListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyXDataUniqueListW_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyXDataEntryW_dump(p, tab);
	return err;
}

void MyXDataUniqueListW_dump(MyXDataUniqueList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyXDataUniqueListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyXDataUniqueListW_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyXDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataUniqueListW_fdump(FILE *fp, MyXDataUniqueList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyXDataUniqueListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataUniqueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataOrderedList
static Dz1Error MyXDataOrderedList_add(MyXDataOrderedList *p, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyXDataOrderedList_remove(MyXDataOrderedList *p, MyXDataEntry *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyXDataEntry *MyXDataOrderedList_extract(MyXDataOrderedList *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyXDataOrderedListMkArrArg
{
	MyXDataEntry **arr;
	unsigned int idx;
} MyXDataOrderedListMkArrArg;

static Dz1Error _MyXDataOrderedList_get_array(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataOrderedListMkArrArg *arg = (MyXDataOrderedListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyXDataEntry **MyXDataOrderedList_get_array(MyXDataOrderedList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyXDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyXDataEntry **)Dz1Calloc(sizeof(MyXDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyXDataOrderedListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyXDataOrderedList_get_array, (void *)&arg);
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

static Dz1Error MyXDataOrderedList_travelForward(MyXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyXDataOrderedList_travelBackward(MyXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyXDataEntry *MyXDataOrderedList_find(MyXDataOrderedList *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1OrderedFifo_find(p->storage, key);
}

static MyXDataEntry *MyXDataOrderedList_getHead(MyXDataOrderedList *p)
{
	return (MyXDataEntry *)Dz1OrderedFifo_getHead(p->storage);
}

static MyXDataEntry *MyXDataOrderedList_getTail(MyXDataOrderedList *p)
{
	return (MyXDataEntry *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyXDataOrderedList_count(MyXDataOrderedList *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyXDataOrderedList *MyXDataOrderedList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataOrderedList *ret = (MyXDataOrderedList *)Dz1Calloc(sizeof(MyXDataOrderedList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataOrderedList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyXDataEntry_cmp,
				(Dz1DelFunc)MyXDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyXDataOrderedList_count;
			ret->travel = MyXDataOrderedList_travelForward;
			ret->travelForward = MyXDataOrderedList_travelForward;
			ret->travelBackward = MyXDataOrderedList_travelBackward;
			ret->get_array = MyXDataOrderedList_get_array;
			ret->add = MyXDataOrderedList_add;
			ret->remove = MyXDataOrderedList_remove;
			ret->find = MyXDataOrderedList_find;
			ret->extract = MyXDataOrderedList_extract;
			ret->getHead = MyXDataOrderedList_getHead;
			ret->getTail = MyXDataOrderedList_getTail;
			ret->cmp = MyXDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataOrderedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyXDataOrderedList_clone(void *ptr, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataOrderedList *p = (MyXDataOrderedList *)ptr;
	MyXDataEntry *cloned = MyXDataEntry_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyXDataOrderedList *MyXDataOrderedList_clone(MyXDataOrderedList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataOrderedList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyXDataOrderedList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataOrderedList_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyXDataOrderedList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataOrderedList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyXDataOrderedList_purge(MyXDataOrderedList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyXDataOrderedList_del(MyXDataOrderedList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyXDataOrderedListA_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyXDataEntryA_dump(p, tab);
	return err;
}

void MyXDataOrderedListA_dump(MyXDataOrderedList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyXDataOrderedListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyXDataOrderedListA_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyXDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataOrderedListA_fdump(FILE *fp, MyXDataOrderedList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyXDataOrderedListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyXDataOrderedListW_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyXDataEntryW_dump(p, tab);
	return err;
}

void MyXDataOrderedListW_dump(MyXDataOrderedList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyXDataOrderedListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyXDataOrderedListW_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyXDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataOrderedListW_fdump(FILE *fp, MyXDataOrderedList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyXDataOrderedListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataOrderedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataList
static Dz1Error MyXDataList_add(MyXDataList *p, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyXDataEntry *MyXDataList_extract(MyXDataList *p, MyXDataEntry *ptr)
{
	return (MyXDataEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyXDataListMkArrArg
{
	MyXDataEntry **arr;
	unsigned int idx;
} MyXDataListMkArrArg;

static Dz1Error _MyXDataList_get_array(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataListMkArrArg *arg = (MyXDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyXDataEntry **MyXDataList_get_array(MyXDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyXDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyXDataEntry **)Dz1Calloc(sizeof(MyXDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyXDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyXDataList_get_array, (void *)&arg);
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

static Dz1Error MyXDataList_travelForward(MyXDataList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyXDataList_travelBackward(MyXDataList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyXDataListFindArg
{
	MyXDataEntry *key;
	MyXDataEntry *ret;
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataListFindArg;

static Dz1Error _MyXDataList_find(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyXDataListFindArg *arg = (MyXDataListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyXDataEntry *MyXDataList_find(MyXDataList *p, MyXDataEntry *key)
{
	MyXDataListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyXDataList_find, (void *)&arg);
	return arg.ret;
}

static MyXDataEntry *MyXDataList_getHead(MyXDataList *p)
{
	return (MyXDataEntry *)Dz1Fifo_getFirst(p->storage);
}

static MyXDataEntry *MyXDataList_getTail(MyXDataList *p)
{
	return (MyXDataEntry *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyXDataList_count(MyXDataList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyXDataList *MyXDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataList *ret = (MyXDataList *)Dz1Calloc(sizeof(MyXDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyXDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyXDataList_count;
			ret->travel = MyXDataList_travelForward;
			ret->travelForward = MyXDataList_travelForward;
			ret->travelBackward = MyXDataList_travelBackward;
			ret->get_array = MyXDataList_get_array;
			ret->add = MyXDataList_add;
			ret->find = MyXDataList_find;
			ret->extract = MyXDataList_extract;
			ret->getHead = MyXDataList_getHead;
			ret->getTail = MyXDataList_getTail;
			ret->cmp = MyXDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyXDataList_clone(void *ptr, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataList *p = (MyXDataList *)ptr;
	MyXDataEntry *cloned = MyXDataEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyXDataList *MyXDataList_clone(MyXDataList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyXDataList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyXDataList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyXDataList_purge(MyXDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyXDataList_del(MyXDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyXDataListA_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyXDataEntryA_dump(p, tab);
	return err;
}

void MyXDataListA_dump(MyXDataList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyXDataListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyXDataListA_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyXDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataListA_fdump(FILE *fp, MyXDataList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyXDataListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyXDataListW_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyXDataEntryW_dump(p, tab);
	return err;
}

void MyXDataListW_dump(MyXDataList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyXDataListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyXDataListW_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyXDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataListW_fdump(FILE *fp, MyXDataList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyXDataListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataUniqueRefList
static Dz1Error MyXDataUniqueRefList_add(MyXDataUniqueRefList *p, MyXDataEntry *data)
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

static bool_t MyXDataUniqueRefList_remove(MyXDataUniqueRefList *p, MyXDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyXDataEntry *MyXDataUniqueRefList_extract(MyXDataUniqueRefList *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyXDataUniqueRefListMkArrArg
{
	MyXDataEntry **arr;
	unsigned int idx;
} MyXDataUniqueRefListMkArrArg;

static Dz1Error _MyXDataUniqueRefList_get_array(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataUniqueRefListMkArrArg *arg = (MyXDataUniqueRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyXDataEntry **MyXDataUniqueRefList_get_array(MyXDataUniqueRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyXDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyXDataEntry **)Dz1Calloc(sizeof(MyXDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyXDataUniqueRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyXDataUniqueRefList_get_array, (void *)&arg);
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

static Dz1Error MyXDataUniqueRefList_travelForward(MyXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyXDataUniqueRefList_travelBackward(MyXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyXDataEntry *MyXDataUniqueRefList_find(MyXDataUniqueRefList *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1AATree_find(p->storage, key);
}

static MyXDataEntry *MyXDataUniqueRefList_getHead(MyXDataUniqueRefList *p)
{
	return (MyXDataEntry *)Dz1AATree_getHead(p->storage);
}

static MyXDataEntry *MyXDataUniqueRefList_getTail(MyXDataUniqueRefList *p)
{
	return (MyXDataEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyXDataUniqueRefList_count(MyXDataUniqueRefList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyXDataUniqueRefList *MyXDataUniqueRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataUniqueRefList *ret = (MyXDataUniqueRefList *)Dz1Calloc(sizeof(MyXDataUniqueRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataUniqueRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyXDataEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyXDataUniqueRefList_count;
			ret->travel = MyXDataUniqueRefList_travelForward;
			ret->travelForward = MyXDataUniqueRefList_travelForward;
			ret->travelBackward = MyXDataUniqueRefList_travelBackward;
			ret->get_array = MyXDataUniqueRefList_get_array;
			ret->add = MyXDataUniqueRefList_add;
			ret->remove = MyXDataUniqueRefList_remove;
			ret->find = MyXDataUniqueRefList_find;
			ret->extract = MyXDataUniqueRefList_extract;
			ret->getHead = MyXDataUniqueRefList_getHead;
			ret->getTail = MyXDataUniqueRefList_getTail;
			ret->cmp = MyXDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataUniqueRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyXDataUniqueRefList_clone(void *ptr, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataUniqueRefList *p = (MyXDataUniqueRefList *)ptr;
	MyXDataEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyXDataUniqueRefList *MyXDataUniqueRefList_clone(MyXDataUniqueRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataUniqueRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyXDataUniqueRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataUniqueRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyXDataUniqueRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataUniqueRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyXDataUniqueRefList_purge(MyXDataUniqueRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyXDataUniqueRefList_del(MyXDataUniqueRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyXDataUniqueRefListA_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyXDataEntryA_dump(p, tab);
	return err;
}

void MyXDataUniqueRefListA_dump(MyXDataUniqueRefList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyXDataUniqueRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyXDataUniqueRefListA_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyXDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataUniqueRefListA_fdump(FILE *fp, MyXDataUniqueRefList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyXDataUniqueRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyXDataUniqueRefListW_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyXDataEntryW_dump(p, tab);
	return err;
}

void MyXDataUniqueRefListW_dump(MyXDataUniqueRefList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyXDataUniqueRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyXDataUniqueRefListW_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyXDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataUniqueRefListW_fdump(FILE *fp, MyXDataUniqueRefList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyXDataUniqueRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataUniqueRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataOrderedRefList
static Dz1Error MyXDataOrderedRefList_add(MyXDataOrderedRefList *p, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyXDataOrderedRefList_remove(MyXDataOrderedRefList *p, MyXDataEntry *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyXDataEntry *MyXDataOrderedRefList_extract(MyXDataOrderedRefList *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyXDataOrderedRefListMkArrArg
{
	MyXDataEntry **arr;
	unsigned int idx;
} MyXDataOrderedRefListMkArrArg;

static Dz1Error _MyXDataOrderedRefList_get_array(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataOrderedRefListMkArrArg *arg = (MyXDataOrderedRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyXDataEntry **MyXDataOrderedRefList_get_array(MyXDataOrderedRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyXDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyXDataEntry **)Dz1Calloc(sizeof(MyXDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyXDataOrderedRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyXDataOrderedRefList_get_array, (void *)&arg);
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

static Dz1Error MyXDataOrderedRefList_travelForward(MyXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyXDataOrderedRefList_travelBackward(MyXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyXDataEntry *MyXDataOrderedRefList_find(MyXDataOrderedRefList *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1OrderedFifo_find(p->storage, key);
}

static MyXDataEntry *MyXDataOrderedRefList_getHead(MyXDataOrderedRefList *p)
{
	return (MyXDataEntry *)Dz1OrderedFifo_getHead(p->storage);
}

static MyXDataEntry *MyXDataOrderedRefList_getTail(MyXDataOrderedRefList *p)
{
	return (MyXDataEntry *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyXDataOrderedRefList_count(MyXDataOrderedRefList *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyXDataOrderedRefList *MyXDataOrderedRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataOrderedRefList *ret = (MyXDataOrderedRefList *)Dz1Calloc(sizeof(MyXDataOrderedRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataOrderedRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyXDataEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyXDataOrderedRefList_count;
			ret->travel = MyXDataOrderedRefList_travelForward;
			ret->travelForward = MyXDataOrderedRefList_travelForward;
			ret->travelBackward = MyXDataOrderedRefList_travelBackward;
			ret->get_array = MyXDataOrderedRefList_get_array;
			ret->add = MyXDataOrderedRefList_add;
			ret->remove = MyXDataOrderedRefList_remove;
			ret->find = MyXDataOrderedRefList_find;
			ret->extract = MyXDataOrderedRefList_extract;
			ret->getHead = MyXDataOrderedRefList_getHead;
			ret->getTail = MyXDataOrderedRefList_getTail;
			ret->cmp = MyXDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataOrderedRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyXDataOrderedRefList_clone(void *ptr, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataOrderedRefList *p = (MyXDataOrderedRefList *)ptr;
	MyXDataEntry *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyXDataOrderedRefList *MyXDataOrderedRefList_clone(MyXDataOrderedRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataOrderedRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyXDataOrderedRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataOrderedRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyXDataOrderedRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataOrderedRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyXDataOrderedRefList_purge(MyXDataOrderedRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyXDataOrderedRefList_del(MyXDataOrderedRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyXDataOrderedRefListA_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyXDataEntryA_dump(p, tab);
	return err;
}

void MyXDataOrderedRefListA_dump(MyXDataOrderedRefList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyXDataOrderedRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyXDataOrderedRefListA_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyXDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataOrderedRefListA_fdump(FILE *fp, MyXDataOrderedRefList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyXDataOrderedRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyXDataOrderedRefListW_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyXDataEntryW_dump(p, tab);
	return err;
}

void MyXDataOrderedRefListW_dump(MyXDataOrderedRefList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyXDataOrderedRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyXDataOrderedRefListW_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyXDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataOrderedRefListW_fdump(FILE *fp, MyXDataOrderedRefList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyXDataOrderedRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataOrderedRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataRefList
static Dz1Error MyXDataRefList_add(MyXDataRefList *p, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyXDataEntry *MyXDataRefList_extract(MyXDataRefList *p, MyXDataEntry *ptr)
{
	return (MyXDataEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyXDataRefListMkArrArg
{
	MyXDataEntry **arr;
	unsigned int idx;
} MyXDataRefListMkArrArg;

static Dz1Error _MyXDataRefList_get_array(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataRefListMkArrArg *arg = (MyXDataRefListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyXDataEntry **MyXDataRefList_get_array(MyXDataRefList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyXDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyXDataEntry **)Dz1Calloc(sizeof(MyXDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyXDataRefListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyXDataRefList_get_array, (void *)&arg);
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

static Dz1Error MyXDataRefList_travelForward(MyXDataRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyXDataRefList_travelBackward(MyXDataRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyXDataRefListFindArg
{
	MyXDataEntry *key;
	MyXDataEntry *ret;
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataRefListFindArg;

static Dz1Error _MyXDataRefList_find(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyXDataRefListFindArg *arg = (MyXDataRefListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyXDataEntry *MyXDataRefList_find(MyXDataRefList *p, MyXDataEntry *key)
{
	MyXDataRefListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyXDataRefList_find, (void *)&arg);
	return arg.ret;
}

static MyXDataEntry *MyXDataRefList_getHead(MyXDataRefList *p)
{
	return (MyXDataEntry *)Dz1Fifo_getFirst(p->storage);
}

static MyXDataEntry *MyXDataRefList_getTail(MyXDataRefList *p)
{
	return (MyXDataEntry *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyXDataRefList_count(MyXDataRefList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyXDataRefList *MyXDataRefList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataRefList *ret = (MyXDataRefList *)Dz1Calloc(sizeof(MyXDataRefList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataRefList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyXDataRefList_count;
			ret->travel = MyXDataRefList_travelForward;
			ret->travelForward = MyXDataRefList_travelForward;
			ret->travelBackward = MyXDataRefList_travelBackward;
			ret->get_array = MyXDataRefList_get_array;
			ret->add = MyXDataRefList_add;
			ret->find = MyXDataRefList_find;
			ret->extract = MyXDataRefList_extract;
			ret->getHead = MyXDataRefList_getHead;
			ret->getTail = MyXDataRefList_getTail;
			ret->cmp = MyXDataEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyXDataRefList_clone(void *ptr, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataRefList *p = (MyXDataRefList *)ptr;
	MyXDataEntry *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyXDataRefList *MyXDataRefList_clone(MyXDataRefList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataRefList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyXDataRefList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataRefList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyXDataRefList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataRefList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyXDataRefList_purge(MyXDataRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyXDataRefList_del(MyXDataRefList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyXDataRefListA_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyXDataEntryA_dump(p, tab);
	return err;
}

void MyXDataRefListA_dump(MyXDataRefList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyXDataRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyXDataRefListA_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyXDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataRefListA_fdump(FILE *fp, MyXDataRefList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyXDataRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyXDataRefListW_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyXDataEntryW_dump(p, tab);
	return err;
}

void MyXDataRefListW_dump(MyXDataRefList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyXDataRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyXDataRefListW_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyXDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataRefListW_fdump(FILE *fp, MyXDataRefList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyXDataRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataIndex
static Dz1Error MyXDataIndex_add(MyXDataIndex *p, MyXDataEntry *data)
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

static bool_t MyXDataIndex_remove(MyXDataIndex *p, MyXDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyXDataEntry *MyXDataIndex_extract(MyXDataIndex *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyXDataIndexMkArrArg
{
	MyXDataEntry **arr;
	unsigned int idx;
} MyXDataIndexMkArrArg;

static Dz1Error _MyXDataIndex_get_array(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataIndexMkArrArg *arg = (MyXDataIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyXDataEntry **MyXDataIndex_get_array(MyXDataIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyXDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyXDataEntry **)Dz1Calloc(sizeof(MyXDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyXDataIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyXDataIndex_get_array, (void *)&arg);
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

static Dz1Error MyXDataIndex_travelForward(MyXDataIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyXDataIndex_travelBackward(MyXDataIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyXDataEntry *MyXDataIndex_find(MyXDataIndex *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyXDataIndex_count(MyXDataIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _MyXDataIndex_cmp(MyXDataEntry *a, MyXDataEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}

MyXDataIndex *MyXDataIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataIndex *ret = (MyXDataIndex *)Dz1Calloc(sizeof(MyXDataIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_MyXDataIndex_cmp, (Dz1DelFunc)MyXDataEntry_del, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyXDataIndex_count;
			ret->travel = MyXDataIndex_travelForward;
			ret->travelForward = MyXDataIndex_travelForward;
			ret->travelBackward = MyXDataIndex_travelBackward;
			ret->get_array = MyXDataIndex_get_array;
			ret->add = MyXDataIndex_add;
			ret->remove = MyXDataIndex_remove;
			ret->find = MyXDataIndex_find;
			ret->extract = MyXDataIndex_extract;
			ret->cmp = _MyXDataIndex_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyXDataIndex_clone(void *ptr, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataIndex *p = (MyXDataIndex *)ptr;
	MyXDataEntry *cloned = MyXDataEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyXDataIndex *MyXDataIndex_clone(MyXDataIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyXDataIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyXDataIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyXDataIndex_purge(MyXDataIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyXDataIndex_del(MyXDataIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyXDataIndexA_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyXDataEntryA_dump(p, tab);
	return err;
}

void MyXDataIndexA_dump(MyXDataIndex *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyXDataIndexA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyXDataIndexA_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyXDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataIndexA_fdump(FILE *fp, MyXDataIndex *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyXDataIndexA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyXDataIndexW_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyXDataEntryW_dump(p, tab);
	return err;
}

void MyXDataIndexW_dump(MyXDataIndex *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyXDataIndexW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyXDataIndexW_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyXDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataIndexW_fdump(FILE *fp, MyXDataIndex *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyXDataIndexW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataRefIndex
static Dz1Error MyXDataRefIndex_add(MyXDataRefIndex *p, MyXDataEntry *data)
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

static bool_t MyXDataRefIndex_remove(MyXDataRefIndex *p, MyXDataEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyXDataEntry *MyXDataRefIndex_extract(MyXDataRefIndex *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyXDataRefIndexMkArrArg
{
	MyXDataEntry **arr;
	unsigned int idx;
} MyXDataRefIndexMkArrArg;

static Dz1Error _MyXDataRefIndex_get_array(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataRefIndexMkArrArg *arg = (MyXDataRefIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyXDataEntry **MyXDataRefIndex_get_array(MyXDataRefIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyXDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyXDataEntry **)Dz1Calloc(sizeof(MyXDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyXDataRefIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyXDataRefIndex_get_array, (void *)&arg);
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

static Dz1Error MyXDataRefIndex_travelForward(MyXDataRefIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyXDataRefIndex_travelBackward(MyXDataRefIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyXDataEntry *MyXDataRefIndex_find(MyXDataRefIndex *p, MyXDataEntry *key)
{
	return (MyXDataEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyXDataRefIndex_count(MyXDataRefIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _MyXDataRefIndex_cmp(MyXDataEntry *a, MyXDataEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}

MyXDataRefIndex *MyXDataRefIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataRefIndex *ret = (MyXDataRefIndex *)Dz1Calloc(sizeof(MyXDataRefIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataRefIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_MyXDataRefIndex_cmp, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyXDataRefIndex_count;
			ret->travel = MyXDataRefIndex_travelForward;
			ret->travelForward = MyXDataRefIndex_travelForward;
			ret->travelBackward = MyXDataRefIndex_travelBackward;
			ret->get_array = MyXDataRefIndex_get_array;
			ret->add = MyXDataRefIndex_add;
			ret->remove = MyXDataRefIndex_remove;
			ret->find = MyXDataRefIndex_find;
			ret->extract = MyXDataRefIndex_extract;
			ret->cmp = _MyXDataRefIndex_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataRefIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyXDataRefIndex_clone(void *ptr, MyXDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyXDataRefIndex *p = (MyXDataRefIndex *)ptr;
	MyXDataEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyXDataRefIndex *MyXDataRefIndex_clone(MyXDataRefIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataRefIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyXDataRefIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyXDataRefIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyXDataRefIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataRefIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyXDataRefIndex_purge(MyXDataRefIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyXDataRefIndex_del(MyXDataRefIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyXDataRefIndexA_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyXDataEntryA_dump(p, tab);
	return err;
}

void MyXDataRefIndexA_dump(MyXDataRefIndex *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyXDataRefIndexA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyXDataRefIndexA_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyXDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataRefIndexA_fdump(FILE *fp, MyXDataRefIndex *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyXDataRefIndexA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyXDataRefIndexW_dump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyXDataEntryW_dump(p, tab);
	return err;
}

void MyXDataRefIndexW_dump(MyXDataRefIndex *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyXDataRefIndexW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyXDataRefIndexW_fdump(void *ptr, MyXDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyXDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyXDataRefIndexW_fdump(FILE *fp, MyXDataRefIndex *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyXDataRefIndexW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataRefIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataInfo
// void MyXDataInfo_obj_ptr_arr_del(MyXDataEntry **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyXDataInfo, MyXDataEntry*, obj_ptr_arr, u32_t, MyXDataEntry_del)
// void MyXDataInfo_obj_ptr_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyXDataInfo, MyXDataEntry*, obj_ptr_arr, u32_t)
// MyXDataEntry **MyXDataInfo_obj_ptr_arr_clone(MyXDataEntry **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyXDataInfo, MyXDataEntry*, obj_ptr_arr, u32_t, MyXDataEntry_clone)
// void MyXDataInfo_obj_ptr_arrA_dump(MyXDataEntry **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(MyXDataInfo, MyXDataEntry*, obj_ptr_arr, u32_t, " = ", MyXDataEntryA_dump)
// void MyXDataInfo_obj_ptr_arrA_fdump(FILE *fp, MyXDataEntry **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(MyXDataInfo, MyXDataEntry*, obj_ptr_arr, u32_t, " = ", MyXDataEntryA_fdump)
#ifndef UNIX_SYSTEM
// void MyXDataInfo_obj_ptr_arrW_dump(MyXDataEntry **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(MyXDataInfo, MyXDataEntry*, obj_ptr_arr, u32_t, " = ", MyXDataEntryW_dump)
// void MyXDataInfo_obj_ptr_arrW_fdump(FILE *fp, MyXDataEntry **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(MyXDataInfo, MyXDataEntry*, obj_ptr_arr, u32_t, " = ", MyXDataEntryW_fdump)
#endif // UNIX_SYSTEM

// void MyXDataInfo_obj_arr_del(MyXDataEntry *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(MyXDataInfo, MyXDataEntry, obj_arr, u32_t, MyXDataEntry_purge)
// void MyXDataInfo_obj_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(MyXDataInfo, MyXDataEntry, obj_arr, u32_t)
// MyXDataEntry *MyXDataInfo_obj_arr_clone(MyXDataEntry *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(MyXDataInfo, MyXDataEntry, obj_arr, u32_t, MyXDataEntry_copy)
// void MyXDataInfo_obj_arrA_dump(MyXDataEntry *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_dump(MyXDataInfo, MyXDataEntry, obj_arr, u32_t, " = ", MyXDataEntryA_dump)
// void MyXDataInfo_obj_arrA_fdump(FILE *fp, MyXDataEntry *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_fdump(MyXDataInfo, MyXDataEntry, obj_arr, u32_t, " = ", MyXDataEntryA_fdump)
#ifndef UNIX_SYSTEM
// void MyXDataInfo_obj_arrW_dump(MyXDataEntry *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(MyXDataInfo, MyXDataEntry, obj_arr, u32_t, " = ", MyXDataEntryW_dump)
// void MyXDataInfo_obj_arrW_fdump(FILE *fp, MyXDataEntry *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(MyXDataInfo, MyXDataEntry, obj_arr, u32_t, " = ", MyXDataEntryW_fdump)
#endif // UNIX_SYSTEM

// void MyXDataInfo_prims_arr_del(u64_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(MyXDataInfo, u64_t, prims_arr, u32_t)
// void MyXDataInfo_prims_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(MyXDataInfo, u64_t, prims_arr)
// u64_t *MyXDataInfo_prims_arr_clone(u64_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(MyXDataInfo, u64_t, prims_arr, u32_t)
// void MyXDataInfo_prims_arrA_dump(u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_dump(MyXDataInfo, u64_t, prims_arr, u32_t, " = ", Dz1u64A_dump)
// void MyXDataInfo_prims_arrA_fdump(FILE *fp, u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_fdump(MyXDataInfo, u64_t, prims_arr, u32_t, " = ", Dz1u64A_fdump)
#ifndef UNIX_SYSTEM
// void MyXDataInfo_prims_arrW_dump(u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_dump(MyXDataInfo, u64_t, prims_arr, u32_t, " = ", Dz1u64W_dump)
// void MyXDataInfo_prims_arrW_fdump(FILE *fp, u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_fdump(MyXDataInfo, u64_t, prims_arr, u32_t, " = ", Dz1u64W_fdump)
#endif // UNIX_SYSTEM

// void MyXDataInfo_primptrs_arr_del(u64_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyXDataInfo, u64_t*, primptrs_arr, u32_t, Dz1u64_del)
// void MyXDataInfo_primptrs_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyXDataInfo, u64_t*, primptrs_arr, u32_t)
// u64_t **MyXDataInfo_primptrs_arr_clone(u64_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyXDataInfo, u64_t*, primptrs_arr, u32_t, Dz1u64_clone)
// void MyXDataInfo_primptrs_arrA_dump(u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(MyXDataInfo, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64A_dump)
// void MyXDataInfo_primptrs_arrA_fdump(FILE *fp, u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(MyXDataInfo, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64A_fdump)
#ifndef UNIX_SYSTEM
// void MyXDataInfo_primptrs_arrW_dump(u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(MyXDataInfo, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64W_dump)
// void MyXDataInfo_primptrs_arrW_fdump(FILE *fp, u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(MyXDataInfo, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64W_fdump)
#endif // UNIX_SYSTEM

MyXDataInfo *MyXDataInfo_new(MyXDataEntry **obj_ptr_arr/*_e_clone*/, 
							 u32_t obj_ptr_cnt, 
							 MyXDataEntry *obj_arr/*_e_copy*/, 
							 u32_t obj_cnt, 
							 u64_t *prims_arr/*_e_copy*/, 
							 u32_t prims_cnt, 
							 u64_t **primptrs_arr/*_e_clone*/, 
							 u32_t primptrs_cnt, 
							 s32_t *i_val/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyXDataInfo *__internal_ret = (MyXDataInfo *)Dz1Calloc(sizeof(MyXDataInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyXDataInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (obj_ptr_arr != NULL && (__internal_ret->obj_ptr_arr = MyXDataInfo_obj_ptr_arr_clone(obj_ptr_arr, obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (obj_arr != NULL && (__internal_ret->obj_arr = MyXDataInfo_obj_arr_clone(obj_arr, obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (prims_arr != NULL && (__internal_ret->prims_arr = MyXDataInfo_prims_arr_clone(prims_arr, prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (primptrs_arr != NULL && (__internal_ret->primptrs_arr = MyXDataInfo_primptrs_arr_clone(primptrs_arr, primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->obj_ptr_cnt = obj_ptr_cnt;
			__internal_ret->obj_cnt = obj_cnt;
			__internal_ret->prims_cnt = prims_cnt;
			__internal_ret->primptrs_cnt = primptrs_cnt;
			__internal_ret->i_val = i_val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyXDataInfo_copy(MyXDataInfo *dst, MyXDataInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->obj_ptr_arr != NULL && (dst->obj_ptr_arr = MyXDataInfo_obj_ptr_arr_clone(src->obj_ptr_arr, src->obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->obj_arr != NULL && (dst->obj_arr = MyXDataInfo_obj_arr_clone(src->obj_arr, src->obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->prims_arr != NULL && (dst->prims_arr = MyXDataInfo_prims_arr_clone(src->prims_arr, src->prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->primptrs_arr != NULL && (dst->primptrs_arr = MyXDataInfo_primptrs_arr_clone(src->primptrs_arr, src->primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
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

MyXDataInfo *MyXDataInfo_clone(MyXDataInfo *src, Dz1Error *err)
{
	MyXDataInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyXDataInfo *)Dz1Calloc(sizeof(MyXDataInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyXDataInfo_delAndSetNull, (void *)&dst);
		if (MyXDataInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyXDataInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyXDataInfo_purge(MyXDataInfo *p)
{
	if (p == NULL) return;
	MyXDataInfo_obj_ptr_arr_del(p->obj_ptr_arr, p->obj_ptr_cnt);
	MyXDataInfo_obj_arr_del(p->obj_arr, p->obj_cnt);
	MyXDataInfo_prims_arr_del(p->prims_arr, p->prims_cnt);
	MyXDataInfo_primptrs_arr_del(p->primptrs_arr, p->primptrs_cnt);
}

void MyXDataInfo_del(MyXDataInfo *p)
{
	if (p == NULL) return;
	MyXDataInfo_purge(p);
	Dz1Free(p);
}

void MyXDataInfoA_dump(MyXDataInfo *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "obj_ptr_arr = "); MyXDataInfo_obj_ptr_arrA_dump(p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadA_tprintf(tab, "obj_ptr_cnt = "); Dz1u32A_dump(&p->obj_ptr_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "obj_arr = "); MyXDataInfo_obj_arrA_dump(p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadA_tprintf(tab, "obj_cnt = "); Dz1u32A_dump(&p->obj_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "prims_arr = "); MyXDataInfo_prims_arrA_dump(p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadA_tprintf(tab, "prims_cnt = "); Dz1u32A_dump(&p->prims_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "primptrs_arr = "); MyXDataInfo_primptrs_arrA_dump(p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadA_tprintf(tab, "primptrs_cnt = "); Dz1u32A_dump(&p->primptrs_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "i_val = "); Dz1s32A_dump(p->i_val, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void MyXDataInfoA_fdump(FILE *fp, MyXDataInfo *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintf(fp, tab, "obj_ptr_arr = "); MyXDataInfo_obj_ptr_arrA_fdump(fp, p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "obj_ptr_cnt = "); Dz1u32A_fdump(fp, &p->obj_ptr_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "obj_arr = "); MyXDataInfo_obj_arrA_fdump(fp, p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "obj_cnt = "); Dz1u32A_fdump(fp, &p->obj_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "prims_arr = "); MyXDataInfo_prims_arrA_fdump(fp, p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "prims_cnt = "); Dz1u32A_fdump(fp, &p->prims_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "primptrs_arr = "); MyXDataInfo_primptrs_arrA_fdump(fp, p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "primptrs_cnt = "); Dz1u32A_fdump(fp, &p->primptrs_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "i_val = "); Dz1s32A_fdump(fp, p->i_val, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void MyXDataInfoW_dump(MyXDataInfo *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"obj_ptr_arr = "); MyXDataInfo_obj_ptr_arrW_dump(p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"obj_ptr_cnt = "); Dz1u32W_dump(&p->obj_ptr_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"obj_arr = "); MyXDataInfo_obj_arrW_dump(p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"obj_cnt = "); Dz1u32W_dump(&p->obj_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"prims_arr = "); MyXDataInfo_prims_arrW_dump(p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"prims_cnt = "); Dz1u32W_dump(&p->prims_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"primptrs_arr = "); MyXDataInfo_primptrs_arrW_dump(p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"primptrs_cnt = "); Dz1u32W_dump(&p->primptrs_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"i_val = "); Dz1s32W_dump(p->i_val, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void MyXDataInfoW_fdump(FILE *fp, MyXDataInfo *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintf(fp, tab, L"obj_ptr_arr = "); MyXDataInfo_obj_ptr_arrW_fdump(fp, p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"obj_ptr_cnt = "); Dz1u32W_fdump(fp, &p->obj_ptr_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"obj_arr = "); MyXDataInfo_obj_arrW_fdump(fp, p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"obj_cnt = "); Dz1u32W_fdump(fp, &p->obj_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"prims_arr = "); MyXDataInfo_prims_arrW_fdump(fp, p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"prims_cnt = "); Dz1u32W_fdump(fp, &p->prims_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"primptrs_arr = "); MyXDataInfo_primptrs_arrW_fdump(fp, p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"primptrs_cnt = "); Dz1u32W_fdump(fp, &p->primptrs_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"i_val = "); Dz1s32W_fdump(fp, p->i_val, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyXDataInfo
////////////////////////////////////////////////////////////////////////////////

