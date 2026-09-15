////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_prim_test.h"

////////////////////////////////////////////////////////////////////////////////
// MyStrUniqueTable
static Dz1Error MyStrUniqueTable_add(MyStrUniqueTable *p, str_t data)
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

static bool_t MyStrUniqueTable_remove(MyStrUniqueTable *p, str_t key)
{
	return Dz1AATree_remove(p->storage, key);
}

static str_t MyStrUniqueTable_extract(MyStrUniqueTable *p, str_t key)
{
	return (str_t )Dz1AATree_extract(p->storage, key);
}

typedef struct MyStrUniqueTableMkArrArg
{
	str_t *arr;
	unsigned int idx;
} MyStrUniqueTableMkArrArg;

static Dz1Error _MyStrUniqueTable_get_array(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStrUniqueTableMkArrArg *arg = (MyStrUniqueTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static str_t *MyStrUniqueTable_get_array(MyStrUniqueTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	str_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (str_t *)Dz1Calloc(sizeof(str_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyStrUniqueTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyStrUniqueTable_get_array, (void *)&arg);
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

static Dz1Error MyStrUniqueTable_travelForward(MyStrUniqueTable *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyStrUniqueTable_travelBackward(MyStrUniqueTable *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static str_t MyStrUniqueTable_find(MyStrUniqueTable *p, str_t key)
{
	return (str_t )Dz1AATree_find(p->storage, key);
}

static str_t MyStrUniqueTable_getHead(MyStrUniqueTable *p)
{
	return (str_t )Dz1AATree_getHead(p->storage);
}

static str_t MyStrUniqueTable_getTail(MyStrUniqueTable *p)
{
	return (str_t )Dz1AATree_getTail(p->storage);
}

static unsigned int MyStrUniqueTable_count(MyStrUniqueTable *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyStrUniqueTable *MyStrUniqueTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStrUniqueTable *ret = (MyStrUniqueTable *)Dz1Calloc(sizeof(MyStrUniqueTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStrUniqueTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)dz1_built_in_str_cmp,
				(Dz1DelFunc)dz1_built_in_str_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyStrUniqueTable_count;
			ret->travel = MyStrUniqueTable_travelForward;
			ret->travelForward = MyStrUniqueTable_travelForward;
			ret->travelBackward = MyStrUniqueTable_travelBackward;
			ret->get_array = MyStrUniqueTable_get_array;
			ret->add = MyStrUniqueTable_add;
			ret->remove = MyStrUniqueTable_remove;
			ret->find = MyStrUniqueTable_find;
			ret->extract = MyStrUniqueTable_extract;
			ret->getHead = MyStrUniqueTable_getHead;
			ret->getTail = MyStrUniqueTable_getTail;
			ret->cmp = dz1_built_in_str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStrUniqueTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyStrUniqueTable_clone(void *ptr, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStrUniqueTable *p = (MyStrUniqueTable *)ptr;
	str_t cloned = dz1_built_in_str_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyStrUniqueTable *MyStrUniqueTable_clone(MyStrUniqueTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStrUniqueTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyStrUniqueTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStrUniqueTable_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyStrUniqueTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStrUniqueTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyStrUniqueTable_purge(MyStrUniqueTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyStrUniqueTable_del(MyStrUniqueTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyStrUniqueTableA_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); dz1_built_in_strA_dump(p, tab);
	return err;
}

void MyStrUniqueTableA_dump(MyStrUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyStrUniqueTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyStrUniqueTableA_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); dz1_built_in_strA_fdump(arg->fp, p, tab);
	return err;
}

void MyStrUniqueTableA_fdump(FILE *fp, MyStrUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyStrUniqueTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyStrUniqueTableW_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); dz1_built_in_strW_dump(p, tab);
	return err;
}

void MyStrUniqueTableW_dump(MyStrUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyStrUniqueTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyStrUniqueTableW_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); dz1_built_in_strW_fdump(arg->fp, p, tab);
	return err;
}

void MyStrUniqueTableW_fdump(FILE *fp, MyStrUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyStrUniqueTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyStrUniqueTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStrOrderedTable
static Dz1Error MyStrOrderedTable_add(MyStrOrderedTable *p, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyStrOrderedTable_remove(MyStrOrderedTable *p, str_t key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static str_t MyStrOrderedTable_extract(MyStrOrderedTable *p, str_t key)
{
	return (str_t )Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyStrOrderedTableMkArrArg
{
	str_t *arr;
	unsigned int idx;
} MyStrOrderedTableMkArrArg;

static Dz1Error _MyStrOrderedTable_get_array(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStrOrderedTableMkArrArg *arg = (MyStrOrderedTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static str_t *MyStrOrderedTable_get_array(MyStrOrderedTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	str_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (str_t *)Dz1Calloc(sizeof(str_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyStrOrderedTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyStrOrderedTable_get_array, (void *)&arg);
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

static Dz1Error MyStrOrderedTable_travelForward(MyStrOrderedTable *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyStrOrderedTable_travelBackward(MyStrOrderedTable *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static str_t MyStrOrderedTable_find(MyStrOrderedTable *p, str_t key)
{
	return (str_t )Dz1OrderedFifo_find(p->storage, key);
}

static str_t MyStrOrderedTable_getHead(MyStrOrderedTable *p)
{
	return (str_t )Dz1OrderedFifo_getHead(p->storage);
}

static str_t MyStrOrderedTable_getTail(MyStrOrderedTable *p)
{
	return (str_t )Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyStrOrderedTable_count(MyStrOrderedTable *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyStrOrderedTable *MyStrOrderedTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStrOrderedTable *ret = (MyStrOrderedTable *)Dz1Calloc(sizeof(MyStrOrderedTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStrOrderedTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)dz1_built_in_str_cmp,
				(Dz1DelFunc)dz1_built_in_str_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyStrOrderedTable_count;
			ret->travel = MyStrOrderedTable_travelForward;
			ret->travelForward = MyStrOrderedTable_travelForward;
			ret->travelBackward = MyStrOrderedTable_travelBackward;
			ret->get_array = MyStrOrderedTable_get_array;
			ret->add = MyStrOrderedTable_add;
			ret->remove = MyStrOrderedTable_remove;
			ret->find = MyStrOrderedTable_find;
			ret->extract = MyStrOrderedTable_extract;
			ret->getHead = MyStrOrderedTable_getHead;
			ret->getTail = MyStrOrderedTable_getTail;
			ret->cmp = dz1_built_in_str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStrOrderedTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyStrOrderedTable_clone(void *ptr, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStrOrderedTable *p = (MyStrOrderedTable *)ptr;
	str_t cloned = dz1_built_in_str_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyStrOrderedTable *MyStrOrderedTable_clone(MyStrOrderedTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStrOrderedTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyStrOrderedTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStrOrderedTable_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyStrOrderedTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStrOrderedTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyStrOrderedTable_purge(MyStrOrderedTable *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyStrOrderedTable_del(MyStrOrderedTable *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyStrOrderedTableA_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); dz1_built_in_strA_dump(p, tab);
	return err;
}

void MyStrOrderedTableA_dump(MyStrOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyStrOrderedTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyStrOrderedTableA_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); dz1_built_in_strA_fdump(arg->fp, p, tab);
	return err;
}

void MyStrOrderedTableA_fdump(FILE *fp, MyStrOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyStrOrderedTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyStrOrderedTableW_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); dz1_built_in_strW_dump(p, tab);
	return err;
}

void MyStrOrderedTableW_dump(MyStrOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyStrOrderedTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyStrOrderedTableW_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); dz1_built_in_strW_fdump(arg->fp, p, tab);
	return err;
}

void MyStrOrderedTableW_fdump(FILE *fp, MyStrOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyStrOrderedTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyStrOrderedTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStrTable
static Dz1Error MyStrTable_add(MyStrTable *p, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyStrTable_remove(MyStrTable *p, str_t ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static str_t MyStrTable_extract(MyStrTable *p, str_t ptr)
{
	return (str_t )Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyStrTableMkArrArg
{
	str_t *arr;
	unsigned int idx;
} MyStrTableMkArrArg;

static Dz1Error _MyStrTable_get_array(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStrTableMkArrArg *arg = (MyStrTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static str_t *MyStrTable_get_array(MyStrTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	str_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (str_t *)Dz1Calloc(sizeof(str_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyStrTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyStrTable_get_array, (void *)&arg);
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

static Dz1Error MyStrTable_travelForward(MyStrTable *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyStrTable_travelBackward(MyStrTable *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyStrTableFindArg
{
	str_t key;
	str_t ret;
	int (*cmp)(str_t a, str_t b);
} MyStrTableFindArg;

static Dz1Error _MyStrTable_find(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyStrTableFindArg *arg = (MyStrTableFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static str_t MyStrTable_find(MyStrTable *p, str_t key)
{
	MyStrTableFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyStrTable_find, (void *)&arg);
	return arg.ret;
}

static str_t MyStrTable_getHead(MyStrTable *p)
{
	return (str_t )Dz1Fifo_getFirst(p->storage);
}

static str_t MyStrTable_getTail(MyStrTable *p)
{
	return (str_t )Dz1Fifo_getLast(p->storage);
}

static unsigned int MyStrTable_count(MyStrTable *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyStrTable *MyStrTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStrTable *ret = (MyStrTable *)Dz1Calloc(sizeof(MyStrTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStrTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)dz1_built_in_str_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyStrTable_count;
			ret->travel = MyStrTable_travelForward;
			ret->travelForward = MyStrTable_travelForward;
			ret->travelBackward = MyStrTable_travelBackward;
			ret->get_array = MyStrTable_get_array;
			ret->add = MyStrTable_add;
			ret->remove = MyStrTable_remove;
			ret->find = MyStrTable_find;
			ret->extract = MyStrTable_extract;
			ret->getHead = MyStrTable_getHead;
			ret->getTail = MyStrTable_getTail;
			ret->cmp = dz1_built_in_str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStrTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyStrTable_clone(void *ptr, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStrTable *p = (MyStrTable *)ptr;
	str_t cloned = dz1_built_in_str_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyStrTable *MyStrTable_clone(MyStrTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStrTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyStrTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStrTable_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyStrTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStrTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyStrTable_purge(MyStrTable *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyStrTable_del(MyStrTable *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyStrTableA_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); dz1_built_in_strA_dump(p, tab);
	return err;
}

void MyStrTableA_dump(MyStrTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyStrTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyStrTableA_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); dz1_built_in_strA_fdump(arg->fp, p, tab);
	return err;
}

void MyStrTableA_fdump(FILE *fp, MyStrTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyStrTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyStrTableW_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); dz1_built_in_strW_dump(p, tab);
	return err;
}

void MyStrTableW_dump(MyStrTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyStrTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyStrTableW_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); dz1_built_in_strW_fdump(arg->fp, p, tab);
	return err;
}

void MyStrTableW_fdump(FILE *fp, MyStrTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyStrTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyStrTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyWStrUniqueTable
static Dz1Error MyWStrUniqueTable_add(MyWStrUniqueTable *p, wstr_t data)
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

static bool_t MyWStrUniqueTable_remove(MyWStrUniqueTable *p, wstr_t key)
{
	return Dz1AATree_remove(p->storage, key);
}

static wstr_t MyWStrUniqueTable_extract(MyWStrUniqueTable *p, wstr_t key)
{
	return (wstr_t )Dz1AATree_extract(p->storage, key);
}

typedef struct MyWStrUniqueTableMkArrArg
{
	wstr_t *arr;
	unsigned int idx;
} MyWStrUniqueTableMkArrArg;

static Dz1Error _MyWStrUniqueTable_get_array(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyWStrUniqueTableMkArrArg *arg = (MyWStrUniqueTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static wstr_t *MyWStrUniqueTable_get_array(MyWStrUniqueTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	wstr_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (wstr_t *)Dz1Calloc(sizeof(wstr_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyWStrUniqueTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyWStrUniqueTable_get_array, (void *)&arg);
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

static Dz1Error MyWStrUniqueTable_travelForward(MyWStrUniqueTable *p, Dz1Error (*func)(void *ptr, wstr_t data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyWStrUniqueTable_travelBackward(MyWStrUniqueTable *p, Dz1Error (*func)(void *ptr, wstr_t data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static wstr_t MyWStrUniqueTable_find(MyWStrUniqueTable *p, wstr_t key)
{
	return (wstr_t )Dz1AATree_find(p->storage, key);
}

static wstr_t MyWStrUniqueTable_getHead(MyWStrUniqueTable *p)
{
	return (wstr_t )Dz1AATree_getHead(p->storage);
}

static wstr_t MyWStrUniqueTable_getTail(MyWStrUniqueTable *p)
{
	return (wstr_t )Dz1AATree_getTail(p->storage);
}

static unsigned int MyWStrUniqueTable_count(MyWStrUniqueTable *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyWStrUniqueTable *MyWStrUniqueTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyWStrUniqueTable *ret = (MyWStrUniqueTable *)Dz1Calloc(sizeof(MyWStrUniqueTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyWStrUniqueTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)dz1_built_in_wstr_cmp,
				(Dz1DelFunc)dz1_built_in_wstr_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyWStrUniqueTable_count;
			ret->travel = MyWStrUniqueTable_travelForward;
			ret->travelForward = MyWStrUniqueTable_travelForward;
			ret->travelBackward = MyWStrUniqueTable_travelBackward;
			ret->get_array = MyWStrUniqueTable_get_array;
			ret->add = MyWStrUniqueTable_add;
			ret->remove = MyWStrUniqueTable_remove;
			ret->find = MyWStrUniqueTable_find;
			ret->extract = MyWStrUniqueTable_extract;
			ret->getHead = MyWStrUniqueTable_getHead;
			ret->getTail = MyWStrUniqueTable_getTail;
			ret->cmp = dz1_built_in_wstr_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyWStrUniqueTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyWStrUniqueTable_clone(void *ptr, wstr_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyWStrUniqueTable *p = (MyWStrUniqueTable *)ptr;
	wstr_t cloned = dz1_built_in_wstr_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyWStrUniqueTable *MyWStrUniqueTable_clone(MyWStrUniqueTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyWStrUniqueTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyWStrUniqueTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyWStrUniqueTable_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyWStrUniqueTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyWStrUniqueTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyWStrUniqueTable_purge(MyWStrUniqueTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyWStrUniqueTable_del(MyWStrUniqueTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyWStrUniqueTableA_dump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); dz1_built_in_wstrA_dump(p, tab);
	return err;
}

void MyWStrUniqueTableA_dump(MyWStrUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyWStrUniqueTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyWStrUniqueTableA_fdump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); dz1_built_in_wstrA_fdump(arg->fp, p, tab);
	return err;
}

void MyWStrUniqueTableA_fdump(FILE *fp, MyWStrUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyWStrUniqueTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyWStrUniqueTableW_dump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); dz1_built_in_wstrW_dump(p, tab);
	return err;
}

void MyWStrUniqueTableW_dump(MyWStrUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyWStrUniqueTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyWStrUniqueTableW_fdump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); dz1_built_in_wstrW_fdump(arg->fp, p, tab);
	return err;
}

void MyWStrUniqueTableW_fdump(FILE *fp, MyWStrUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyWStrUniqueTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyWStrUniqueTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyWStrOrderedTable
static Dz1Error MyWStrOrderedTable_add(MyWStrOrderedTable *p, wstr_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyWStrOrderedTable_remove(MyWStrOrderedTable *p, wstr_t key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static wstr_t MyWStrOrderedTable_extract(MyWStrOrderedTable *p, wstr_t key)
{
	return (wstr_t )Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyWStrOrderedTableMkArrArg
{
	wstr_t *arr;
	unsigned int idx;
} MyWStrOrderedTableMkArrArg;

static Dz1Error _MyWStrOrderedTable_get_array(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyWStrOrderedTableMkArrArg *arg = (MyWStrOrderedTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static wstr_t *MyWStrOrderedTable_get_array(MyWStrOrderedTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	wstr_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (wstr_t *)Dz1Calloc(sizeof(wstr_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyWStrOrderedTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyWStrOrderedTable_get_array, (void *)&arg);
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

static Dz1Error MyWStrOrderedTable_travelForward(MyWStrOrderedTable *p, Dz1Error (*func)(void *ptr, wstr_t data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyWStrOrderedTable_travelBackward(MyWStrOrderedTable *p, Dz1Error (*func)(void *ptr, wstr_t data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static wstr_t MyWStrOrderedTable_find(MyWStrOrderedTable *p, wstr_t key)
{
	return (wstr_t )Dz1OrderedFifo_find(p->storage, key);
}

static wstr_t MyWStrOrderedTable_getHead(MyWStrOrderedTable *p)
{
	return (wstr_t )Dz1OrderedFifo_getHead(p->storage);
}

static wstr_t MyWStrOrderedTable_getTail(MyWStrOrderedTable *p)
{
	return (wstr_t )Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyWStrOrderedTable_count(MyWStrOrderedTable *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyWStrOrderedTable *MyWStrOrderedTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyWStrOrderedTable *ret = (MyWStrOrderedTable *)Dz1Calloc(sizeof(MyWStrOrderedTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyWStrOrderedTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)dz1_built_in_wstr_cmp,
				(Dz1DelFunc)dz1_built_in_wstr_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyWStrOrderedTable_count;
			ret->travel = MyWStrOrderedTable_travelForward;
			ret->travelForward = MyWStrOrderedTable_travelForward;
			ret->travelBackward = MyWStrOrderedTable_travelBackward;
			ret->get_array = MyWStrOrderedTable_get_array;
			ret->add = MyWStrOrderedTable_add;
			ret->remove = MyWStrOrderedTable_remove;
			ret->find = MyWStrOrderedTable_find;
			ret->extract = MyWStrOrderedTable_extract;
			ret->getHead = MyWStrOrderedTable_getHead;
			ret->getTail = MyWStrOrderedTable_getTail;
			ret->cmp = dz1_built_in_wstr_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyWStrOrderedTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyWStrOrderedTable_clone(void *ptr, wstr_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyWStrOrderedTable *p = (MyWStrOrderedTable *)ptr;
	wstr_t cloned = dz1_built_in_wstr_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyWStrOrderedTable *MyWStrOrderedTable_clone(MyWStrOrderedTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyWStrOrderedTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyWStrOrderedTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyWStrOrderedTable_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyWStrOrderedTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyWStrOrderedTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyWStrOrderedTable_purge(MyWStrOrderedTable *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyWStrOrderedTable_del(MyWStrOrderedTable *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyWStrOrderedTableA_dump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); dz1_built_in_wstrA_dump(p, tab);
	return err;
}

void MyWStrOrderedTableA_dump(MyWStrOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyWStrOrderedTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyWStrOrderedTableA_fdump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); dz1_built_in_wstrA_fdump(arg->fp, p, tab);
	return err;
}

void MyWStrOrderedTableA_fdump(FILE *fp, MyWStrOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyWStrOrderedTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyWStrOrderedTableW_dump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); dz1_built_in_wstrW_dump(p, tab);
	return err;
}

void MyWStrOrderedTableW_dump(MyWStrOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyWStrOrderedTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyWStrOrderedTableW_fdump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); dz1_built_in_wstrW_fdump(arg->fp, p, tab);
	return err;
}

void MyWStrOrderedTableW_fdump(FILE *fp, MyWStrOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyWStrOrderedTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyWStrOrderedTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyWStrTable
static Dz1Error MyWStrTable_add(MyWStrTable *p, wstr_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyWStrTable_remove(MyWStrTable *p, wstr_t ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static wstr_t MyWStrTable_extract(MyWStrTable *p, wstr_t ptr)
{
	return (wstr_t )Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyWStrTableMkArrArg
{
	wstr_t *arr;
	unsigned int idx;
} MyWStrTableMkArrArg;

static Dz1Error _MyWStrTable_get_array(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyWStrTableMkArrArg *arg = (MyWStrTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static wstr_t *MyWStrTable_get_array(MyWStrTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	wstr_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (wstr_t *)Dz1Calloc(sizeof(wstr_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyWStrTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyWStrTable_get_array, (void *)&arg);
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

static Dz1Error MyWStrTable_travelForward(MyWStrTable *p, Dz1Error (*func)(void *ptr, wstr_t data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyWStrTable_travelBackward(MyWStrTable *p, Dz1Error (*func)(void *ptr, wstr_t data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyWStrTableFindArg
{
	wstr_t key;
	wstr_t ret;
	int (*cmp)(wstr_t a, wstr_t b);
} MyWStrTableFindArg;

static Dz1Error _MyWStrTable_find(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyWStrTableFindArg *arg = (MyWStrTableFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static wstr_t MyWStrTable_find(MyWStrTable *p, wstr_t key)
{
	MyWStrTableFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyWStrTable_find, (void *)&arg);
	return arg.ret;
}

static wstr_t MyWStrTable_getHead(MyWStrTable *p)
{
	return (wstr_t )Dz1Fifo_getFirst(p->storage);
}

static wstr_t MyWStrTable_getTail(MyWStrTable *p)
{
	return (wstr_t )Dz1Fifo_getLast(p->storage);
}

static unsigned int MyWStrTable_count(MyWStrTable *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyWStrTable *MyWStrTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyWStrTable *ret = (MyWStrTable *)Dz1Calloc(sizeof(MyWStrTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyWStrTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)dz1_built_in_wstr_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyWStrTable_count;
			ret->travel = MyWStrTable_travelForward;
			ret->travelForward = MyWStrTable_travelForward;
			ret->travelBackward = MyWStrTable_travelBackward;
			ret->get_array = MyWStrTable_get_array;
			ret->add = MyWStrTable_add;
			ret->remove = MyWStrTable_remove;
			ret->find = MyWStrTable_find;
			ret->extract = MyWStrTable_extract;
			ret->getHead = MyWStrTable_getHead;
			ret->getTail = MyWStrTable_getTail;
			ret->cmp = dz1_built_in_wstr_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyWStrTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyWStrTable_clone(void *ptr, wstr_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyWStrTable *p = (MyWStrTable *)ptr;
	wstr_t cloned = dz1_built_in_wstr_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyWStrTable *MyWStrTable_clone(MyWStrTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyWStrTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyWStrTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyWStrTable_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyWStrTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyWStrTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyWStrTable_purge(MyWStrTable *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyWStrTable_del(MyWStrTable *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyWStrTableA_dump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); dz1_built_in_wstrA_dump(p, tab);
	return err;
}

void MyWStrTableA_dump(MyWStrTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyWStrTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyWStrTableA_fdump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); dz1_built_in_wstrA_fdump(arg->fp, p, tab);
	return err;
}

void MyWStrTableA_fdump(FILE *fp, MyWStrTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyWStrTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyWStrTableW_dump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); dz1_built_in_wstrW_dump(p, tab);
	return err;
}

void MyWStrTableW_dump(MyWStrTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyWStrTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyWStrTableW_fdump(void *ptr, wstr_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); dz1_built_in_wstrW_fdump(arg->fp, p, tab);
	return err;
}

void MyWStrTableW_fdump(FILE *fp, MyWStrTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyWStrTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyWStrTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyIntUniqueTable
static Dz1Error MyIntUniqueTable_add(MyIntUniqueTable *p, s32_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	s32_t *temp = NULL;
	if (Dz1AATree_find(p->storage, (void *)&data)) ERR_SET_OUT(&err, EEXIST);
	else if ((temp = (s32_t *)Dz1Calloc(sizeof(s32_t), 1, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((void (*)(void *))Dz1s32_del, (void *)temp);

		memcpy(temp, &data, sizeof(s32_t));
		err = Dz1AATree_insert(p->storage, temp);
		if (ERR_PROBE(&err)) ERR_OUT(&err);

		pthread_cleanup_pop(ERR_PROBE(&err)); // ((void (*)(void *))Dz1s32_del, (void *)temp);

	}
	return err;
}

static bool_t MyIntUniqueTable_remove(MyIntUniqueTable *p, s32_t *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static s32_t *MyIntUniqueTable_extract(MyIntUniqueTable *p, s32_t *key)
{
	return (s32_t *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyIntUniqueTableMkArrArg
{
	s32_t *arr;
	unsigned int idx;
} MyIntUniqueTableMkArrArg;

static Dz1Error _MyIntUniqueTable_get_array(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyIntUniqueTableMkArrArg *arg = (MyIntUniqueTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = *p;
	return err;
}

static s32_t *MyIntUniqueTable_get_array(MyIntUniqueTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	s32_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (s32_t *)Dz1Calloc(sizeof(s32_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyIntUniqueTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyIntUniqueTable_get_array, (void *)&arg);
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

static Dz1Error MyIntUniqueTable_travelForward(MyIntUniqueTable *p, Dz1Error (*func)(void *ptr, s32_t *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyIntUniqueTable_travelBackward(MyIntUniqueTable *p, Dz1Error (*func)(void *ptr, s32_t *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static s32_t *MyIntUniqueTable_find(MyIntUniqueTable *p, s32_t key)
{
	return (s32_t *)Dz1AATree_find(p->storage, &key);
}

static s32_t *MyIntUniqueTable_getHead(MyIntUniqueTable *p)
{
	return (s32_t *)Dz1AATree_getHead(p->storage);
}

static s32_t *MyIntUniqueTable_getTail(MyIntUniqueTable *p)
{
	return (s32_t *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyIntUniqueTable_count(MyIntUniqueTable *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyIntUniqueTable *MyIntUniqueTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyIntUniqueTable *ret = (MyIntUniqueTable *)Dz1Calloc(sizeof(MyIntUniqueTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyIntUniqueTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1s32_cmp,
				(Dz1DelFunc)Dz1s32_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyIntUniqueTable_count;
			ret->travel = MyIntUniqueTable_travelForward;
			ret->travelForward = MyIntUniqueTable_travelForward;
			ret->travelBackward = MyIntUniqueTable_travelBackward;
			ret->get_array = MyIntUniqueTable_get_array;
			ret->add = MyIntUniqueTable_add;
			ret->remove = MyIntUniqueTable_remove;
			ret->find = MyIntUniqueTable_find;
			ret->extract = MyIntUniqueTable_extract;
			ret->getHead = MyIntUniqueTable_getHead;
			ret->getTail = MyIntUniqueTable_getTail;
			ret->cmp = Dz1s32_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyIntUniqueTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyIntUniqueTable_clone(void *ptr, s32_t *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyIntUniqueTable *p = (MyIntUniqueTable *)ptr;
	s32_t *cloned = Dz1s32_clone(data, &err);
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyIntUniqueTable *MyIntUniqueTable_clone(MyIntUniqueTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyIntUniqueTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyIntUniqueTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyIntUniqueTable_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyIntUniqueTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyIntUniqueTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyIntUniqueTable_purge(MyIntUniqueTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyIntUniqueTable_del(MyIntUniqueTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyIntUniqueTableA_dump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1s32A_dump(p, tab);
	return err;
}

void MyIntUniqueTableA_dump(MyIntUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyIntUniqueTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyIntUniqueTableA_fdump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); Dz1s32A_fdump(arg->fp, p, tab);
	return err;
}

void MyIntUniqueTableA_fdump(FILE *fp, MyIntUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyIntUniqueTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyIntUniqueTableW_dump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1s32W_dump(p, tab);
	return err;
}

void MyIntUniqueTableW_dump(MyIntUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyIntUniqueTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyIntUniqueTableW_fdump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); Dz1s32W_fdump(arg->fp, p, tab);
	return err;
}

void MyIntUniqueTableW_fdump(FILE *fp, MyIntUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyIntUniqueTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyIntUniqueTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyIntOrderedTable
static Dz1Error MyIntOrderedTable_add(MyIntOrderedTable *p, s32_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	s32_t *temp = NULL;
	if ((temp = (s32_t *)Dz1Calloc(sizeof(s32_t), 1, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((void (*)(void *))Dz1s32_del, (void *)temp);

		memcpy(temp, &data, sizeof(s32_t));
		err = Dz1OrderedFifo_push(p->storage, temp);
		if (ERR_PROBE(&err)) ERR_OUT(&err);

		pthread_cleanup_pop(ERR_PROBE(&err)); // ((void (*)(void *))Dz1s32_del, (void *)temp);

	}
	return err;
}

static bool_t MyIntOrderedTable_remove(MyIntOrderedTable *p, s32_t *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static s32_t *MyIntOrderedTable_extract(MyIntOrderedTable *p, s32_t *key)
{
	return (s32_t *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyIntOrderedTableMkArrArg
{
	s32_t *arr;
	unsigned int idx;
} MyIntOrderedTableMkArrArg;

static Dz1Error _MyIntOrderedTable_get_array(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyIntOrderedTableMkArrArg *arg = (MyIntOrderedTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = *p;
	return err;
}

static s32_t *MyIntOrderedTable_get_array(MyIntOrderedTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	s32_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (s32_t *)Dz1Calloc(sizeof(s32_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyIntOrderedTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyIntOrderedTable_get_array, (void *)&arg);
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

static Dz1Error MyIntOrderedTable_travelForward(MyIntOrderedTable *p, Dz1Error (*func)(void *ptr, s32_t *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyIntOrderedTable_travelBackward(MyIntOrderedTable *p, Dz1Error (*func)(void *ptr, s32_t *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static s32_t *MyIntOrderedTable_find(MyIntOrderedTable *p, s32_t key)
{
	return (s32_t *)Dz1OrderedFifo_find(p->storage, &key);
}

static s32_t *MyIntOrderedTable_getHead(MyIntOrderedTable *p)
{
	return (s32_t *)Dz1OrderedFifo_getHead(p->storage);
}

static s32_t *MyIntOrderedTable_getTail(MyIntOrderedTable *p)
{
	return (s32_t *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyIntOrderedTable_count(MyIntOrderedTable *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyIntOrderedTable *MyIntOrderedTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyIntOrderedTable *ret = (MyIntOrderedTable *)Dz1Calloc(sizeof(MyIntOrderedTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyIntOrderedTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)Dz1s32_cmp,
				(Dz1DelFunc)Dz1s32_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyIntOrderedTable_count;
			ret->travel = MyIntOrderedTable_travelForward;
			ret->travelForward = MyIntOrderedTable_travelForward;
			ret->travelBackward = MyIntOrderedTable_travelBackward;
			ret->get_array = MyIntOrderedTable_get_array;
			ret->add = MyIntOrderedTable_add;
			ret->remove = MyIntOrderedTable_remove;
			ret->find = MyIntOrderedTable_find;
			ret->extract = MyIntOrderedTable_extract;
			ret->getHead = MyIntOrderedTable_getHead;
			ret->getTail = MyIntOrderedTable_getTail;
			ret->cmp = Dz1s32_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyIntOrderedTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyIntOrderedTable_clone(void *ptr, s32_t *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyIntOrderedTable *p = (MyIntOrderedTable *)ptr;
	s32_t *cloned = Dz1s32_clone(data, &err);
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyIntOrderedTable *MyIntOrderedTable_clone(MyIntOrderedTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyIntOrderedTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyIntOrderedTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyIntOrderedTable_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyIntOrderedTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyIntOrderedTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyIntOrderedTable_purge(MyIntOrderedTable *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyIntOrderedTable_del(MyIntOrderedTable *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyIntOrderedTableA_dump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1s32A_dump(p, tab);
	return err;
}

void MyIntOrderedTableA_dump(MyIntOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyIntOrderedTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyIntOrderedTableA_fdump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); Dz1s32A_fdump(arg->fp, p, tab);
	return err;
}

void MyIntOrderedTableA_fdump(FILE *fp, MyIntOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyIntOrderedTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyIntOrderedTableW_dump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1s32W_dump(p, tab);
	return err;
}

void MyIntOrderedTableW_dump(MyIntOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyIntOrderedTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyIntOrderedTableW_fdump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); Dz1s32W_fdump(arg->fp, p, tab);
	return err;
}

void MyIntOrderedTableW_fdump(FILE *fp, MyIntOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyIntOrderedTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyIntOrderedTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyIntTable
static Dz1Error MyIntTable_add(MyIntTable *p, s32_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	s32_t *temp = NULL;
	if ((temp = (s32_t *)Dz1Calloc(sizeof(s32_t), 1, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((void (*)(void *))Dz1s32_del, (void *)temp);

		memcpy(temp, &data, sizeof(s32_t));
		err = Dz1Fifo_push(p->storage, temp);
		if (ERR_PROBE(&err)) ERR_OUT(&err);

		pthread_cleanup_pop(ERR_PROBE(&err)); // ((void (*)(void *))Dz1s32_del, (void *)temp);

	}
	return err;
}

static bool_t MyIntTable_remove(MyIntTable *p, s32_t *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static s32_t *MyIntTable_extract(MyIntTable *p, s32_t *ptr)
{
	return (s32_t *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyIntTableMkArrArg
{
	s32_t *arr;
	unsigned int idx;
} MyIntTableMkArrArg;

static Dz1Error _MyIntTable_get_array(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyIntTableMkArrArg *arg = (MyIntTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = *p;
	return err;
}

static s32_t *MyIntTable_get_array(MyIntTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	s32_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (s32_t *)Dz1Calloc(sizeof(s32_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyIntTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyIntTable_get_array, (void *)&arg);
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

static Dz1Error MyIntTable_travelForward(MyIntTable *p, Dz1Error (*func)(void *ptr, s32_t *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyIntTable_travelBackward(MyIntTable *p, Dz1Error (*func)(void *ptr, s32_t *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyIntTableFindArg
{
	s32_t *key;
	s32_t *ret;
	int (*cmp)(s32_t *a, s32_t *b);
} MyIntTableFindArg;

static Dz1Error _MyIntTable_find(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyIntTableFindArg *arg = (MyIntTableFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static s32_t *MyIntTable_find(MyIntTable *p, s32_t key)
{
	MyIntTableFindArg arg = { NULL, NULL };
	arg.key = &key;
	arg.cmp = p->cmp;
	p->travel(p, _MyIntTable_find, (void *)&arg);
	return arg.ret;
}

static s32_t *MyIntTable_getHead(MyIntTable *p)
{
	return (s32_t *)Dz1Fifo_getFirst(p->storage);
}

static s32_t *MyIntTable_getTail(MyIntTable *p)
{
	return (s32_t *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyIntTable_count(MyIntTable *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyIntTable *MyIntTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyIntTable *ret = (MyIntTable *)Dz1Calloc(sizeof(MyIntTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyIntTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1s32_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyIntTable_count;
			ret->travel = MyIntTable_travelForward;
			ret->travelForward = MyIntTable_travelForward;
			ret->travelBackward = MyIntTable_travelBackward;
			ret->get_array = MyIntTable_get_array;
			ret->add = MyIntTable_add;
			ret->remove = MyIntTable_remove;
			ret->find = MyIntTable_find;
			ret->extract = MyIntTable_extract;
			ret->getHead = MyIntTable_getHead;
			ret->getTail = MyIntTable_getTail;
			ret->cmp = Dz1s32_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyIntTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyIntTable_clone(void *ptr, s32_t *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyIntTable *p = (MyIntTable *)ptr;
	s32_t *cloned = Dz1s32_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyIntTable *MyIntTable_clone(MyIntTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyIntTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyIntTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyIntTable_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyIntTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyIntTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyIntTable_purge(MyIntTable *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyIntTable_del(MyIntTable *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyIntTableA_dump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1s32A_dump(p, tab);
	return err;
}

void MyIntTableA_dump(MyIntTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyIntTableA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyIntTableA_fdump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); Dz1s32A_fdump(arg->fp, p, tab);
	return err;
}

void MyIntTableA_fdump(FILE *fp, MyIntTable *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyIntTableA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _MyIntTableW_dump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1s32W_dump(p, tab);
	return err;
}

void MyIntTableW_dump(MyIntTable *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyIntTableW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyIntTableW_fdump(void *ptr, s32_t *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); Dz1s32W_fdump(arg->fp, p, tab);
	return err;
}

void MyIntTableW_fdump(FILE *fp, MyIntTable *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyIntTableW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// MyIntTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnum
static struct MyEnumMapA
{
	str_t str;
	MyEnum v;
} MyEnumMapA[] =
{
	{ (char *)"first", MyEnum_first },
	{ (char *)"second", MyEnum_second },
	{ NULL, MyEnum_max }
};

str_t MyEnumStrA(MyEnum v)
{
	struct MyEnumMapA *i = NULL;
	for (i = MyEnumMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyEnum MyEnumFromStrA(str_t str)
{
	struct MyEnumMapA *i = NULL;
	for (i = MyEnumMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return MyEnum_max;
}
#ifndef UNIX_SYSTEM
static struct MyEnumMapW
{
	wstr_t str;
	MyEnum v;
} MyEnumMapW[] =
{
	{ (wchar_t *)L"first", MyEnum_first },
	{ (wchar_t *)L"second", MyEnum_second },
	{ NULL, MyEnum_max }
};

wstr_t MyEnumStrW(MyEnum v)
{
	struct MyEnumMapW *i = NULL;
	for (i = MyEnumMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyEnum MyEnumFromStrW(wstr_t str)
{
	struct MyEnumMapW *i = NULL;
	for (i = MyEnumMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return MyEnum_max;
}
#endif // UNIX_SYSTEM

MyEnum *MyEnum_new(MyEnum *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyEnum *__internal_ret = (MyEnum *)Dz1Calloc(sizeof(MyEnum), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void MyEnumA_dump(MyEnum *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", MyEnumStrA(*v));
}

int MyEnum_cmp(MyEnum *a, MyEnum *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// MyEnum
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnumUniqueTable
static Dz1Error MyEnumUniqueTable_add(MyEnumUniqueTable *p, MyEnum data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyEnum *temp = NULL;
	if (Dz1AATree_find(p->storage, (void *)&data)) ERR_SET_OUT(&err, EEXIST);
	else if ((temp = (MyEnum *)Dz1Calloc(sizeof(MyEnum), 1, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((void (*)(void *))MyEnum_del, (void *)temp);

		memcpy(temp, &data, sizeof(MyEnum));
		err = Dz1AATree_insert(p->storage, temp);
		if (ERR_PROBE(&err)) ERR_OUT(&err);

		pthread_cleanup_pop(ERR_PROBE(&err)); // ((void (*)(void *))MyEnum_del, (void *)temp);

	}
	return err;
}

static bool_t MyEnumUniqueTable_remove(MyEnumUniqueTable *p, MyEnum *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyEnum *MyEnumUniqueTable_extract(MyEnumUniqueTable *p, MyEnum *key)
{
	return (MyEnum *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyEnumUniqueTableMkArrArg
{
	MyEnum *arr;
	unsigned int idx;
} MyEnumUniqueTableMkArrArg;

static Dz1Error _MyEnumUniqueTable_get_array(void *ptr, MyEnum *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyEnumUniqueTableMkArrArg *arg = (MyEnumUniqueTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = *p;
	return err;
}

static MyEnum *MyEnumUniqueTable_get_array(MyEnumUniqueTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyEnum *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyEnum *)Dz1Calloc(sizeof(MyEnum *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyEnumUniqueTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyEnumUniqueTable_get_array, (void *)&arg);
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

static Dz1Error MyEnumUniqueTable_travelForward(MyEnumUniqueTable *p, Dz1Error (*func)(void *ptr, MyEnum *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyEnumUniqueTable_travelBackward(MyEnumUniqueTable *p, Dz1Error (*func)(void *ptr, MyEnum *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyEnum *MyEnumUniqueTable_find(MyEnumUniqueTable *p, MyEnum key)
{
	return (MyEnum *)Dz1AATree_find(p->storage, &key);
}

static MyEnum *MyEnumUniqueTable_getHead(MyEnumUniqueTable *p)
{
	return (MyEnum *)Dz1AATree_getHead(p->storage);
}

static MyEnum *MyEnumUniqueTable_getTail(MyEnumUniqueTable *p)
{
	return (MyEnum *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyEnumUniqueTable_count(MyEnumUniqueTable *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyEnumUniqueTable *MyEnumUniqueTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyEnumUniqueTable *ret = (MyEnumUniqueTable *)Dz1Calloc(sizeof(MyEnumUniqueTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyEnumUniqueTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyEnum_cmp,
				(Dz1DelFunc)MyEnum_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyEnumUniqueTable_count;
			ret->travel = MyEnumUniqueTable_travelForward;
			ret->travelForward = MyEnumUniqueTable_travelForward;
			ret->travelBackward = MyEnumUniqueTable_travelBackward;
			ret->get_array = MyEnumUniqueTable_get_array;
			ret->add = MyEnumUniqueTable_add;
			ret->remove = MyEnumUniqueTable_remove;
			ret->find = MyEnumUniqueTable_find;
			ret->extract = MyEnumUniqueTable_extract;
			ret->getHead = MyEnumUniqueTable_getHead;
			ret->getTail = MyEnumUniqueTable_getTail;
			ret->cmp = MyEnum_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyEnumUniqueTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyEnumUniqueTable_purge(MyEnumUniqueTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyEnumUniqueTable_del(MyEnumUniqueTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyEnumUniqueTable_dump(void *ptr, MyEnum *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "name = %s(%d)\n", MyEnumStr(*p), *p);
	return err;
}

void MyEnumUniqueTable_dump(MyEnumUniqueTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyEnumUniqueTable_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
// MyEnumUniqueTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnumOrderedTable
static Dz1Error MyEnumOrderedTable_add(MyEnumOrderedTable *p, MyEnum data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyEnum *temp = NULL;
	if ((temp = (MyEnum *)Dz1Calloc(sizeof(MyEnum), 1, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((void (*)(void *))MyEnum_del, (void *)temp);

		memcpy(temp, &data, sizeof(MyEnum));
		err = Dz1OrderedFifo_push(p->storage, temp);
		if (ERR_PROBE(&err)) ERR_OUT(&err);

		pthread_cleanup_pop(ERR_PROBE(&err)); // ((void (*)(void *))MyEnum_del, (void *)temp);

	}
	return err;
}

static bool_t MyEnumOrderedTable_remove(MyEnumOrderedTable *p, MyEnum *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyEnum *MyEnumOrderedTable_extract(MyEnumOrderedTable *p, MyEnum *key)
{
	return (MyEnum *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyEnumOrderedTableMkArrArg
{
	MyEnum *arr;
	unsigned int idx;
} MyEnumOrderedTableMkArrArg;

static Dz1Error _MyEnumOrderedTable_get_array(void *ptr, MyEnum *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyEnumOrderedTableMkArrArg *arg = (MyEnumOrderedTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = *p;
	return err;
}

static MyEnum *MyEnumOrderedTable_get_array(MyEnumOrderedTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyEnum *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyEnum *)Dz1Calloc(sizeof(MyEnum *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyEnumOrderedTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyEnumOrderedTable_get_array, (void *)&arg);
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

static Dz1Error MyEnumOrderedTable_travelForward(MyEnumOrderedTable *p, Dz1Error (*func)(void *ptr, MyEnum *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyEnumOrderedTable_travelBackward(MyEnumOrderedTable *p, Dz1Error (*func)(void *ptr, MyEnum *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyEnum *MyEnumOrderedTable_find(MyEnumOrderedTable *p, MyEnum key)
{
	return (MyEnum *)Dz1OrderedFifo_find(p->storage, &key);
}

static MyEnum *MyEnumOrderedTable_getHead(MyEnumOrderedTable *p)
{
	return (MyEnum *)Dz1OrderedFifo_getHead(p->storage);
}

static MyEnum *MyEnumOrderedTable_getTail(MyEnumOrderedTable *p)
{
	return (MyEnum *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyEnumOrderedTable_count(MyEnumOrderedTable *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyEnumOrderedTable *MyEnumOrderedTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyEnumOrderedTable *ret = (MyEnumOrderedTable *)Dz1Calloc(sizeof(MyEnumOrderedTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyEnumOrderedTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyEnum_cmp,
				(Dz1DelFunc)MyEnum_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyEnumOrderedTable_count;
			ret->travel = MyEnumOrderedTable_travelForward;
			ret->travelForward = MyEnumOrderedTable_travelForward;
			ret->travelBackward = MyEnumOrderedTable_travelBackward;
			ret->get_array = MyEnumOrderedTable_get_array;
			ret->add = MyEnumOrderedTable_add;
			ret->remove = MyEnumOrderedTable_remove;
			ret->find = MyEnumOrderedTable_find;
			ret->extract = MyEnumOrderedTable_extract;
			ret->getHead = MyEnumOrderedTable_getHead;
			ret->getTail = MyEnumOrderedTable_getTail;
			ret->cmp = MyEnum_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyEnumOrderedTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyEnumOrderedTable_purge(MyEnumOrderedTable *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyEnumOrderedTable_del(MyEnumOrderedTable *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyEnumOrderedTable_dump(void *ptr, MyEnum *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "seq = %s(%d)\n", MyEnumStr(*p), *p);
	return err;
}

void MyEnumOrderedTable_dump(MyEnumOrderedTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyEnumOrderedTable_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
// MyEnumOrderedTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnumTable
static Dz1Error MyEnumTable_add(MyEnumTable *p, MyEnum data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyEnum *temp = NULL;
	if ((temp = (MyEnum *)Dz1Calloc(sizeof(MyEnum), 1, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((void (*)(void *))MyEnum_del, (void *)temp);

		memcpy(temp, &data, sizeof(MyEnum));
		err = Dz1Fifo_push(p->storage, temp);
		if (ERR_PROBE(&err)) ERR_OUT(&err);

		pthread_cleanup_pop(ERR_PROBE(&err)); // ((void (*)(void *))MyEnum_del, (void *)temp);

	}
	return err;
}

typedef struct MyEnumTableMkArrArg
{
	MyEnum *arr;
	unsigned int idx;
} MyEnumTableMkArrArg;

static Dz1Error _MyEnumTable_get_array(void *ptr, MyEnum *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyEnumTableMkArrArg *arg = (MyEnumTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = *p;
	return err;
}

static MyEnum *MyEnumTable_get_array(MyEnumTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyEnum *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyEnum *)Dz1Calloc(sizeof(MyEnum *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyEnumTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyEnumTable_get_array, (void *)&arg);
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

static Dz1Error MyEnumTable_travelForward(MyEnumTable *p, Dz1Error (*func)(void *ptr, MyEnum *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyEnumTable_travelBackward(MyEnumTable *p, Dz1Error (*func)(void *ptr, MyEnum *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static MyEnum *MyEnumTable_getHead(MyEnumTable *p)
{
	return (MyEnum *)Dz1Fifo_getFirst(p->storage);
}

static MyEnum *MyEnumTable_getTail(MyEnumTable *p)
{
	return (MyEnum *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyEnumTable_count(MyEnumTable *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyEnumTable *MyEnumTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyEnumTable *ret = (MyEnumTable *)Dz1Calloc(sizeof(MyEnumTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyEnumTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyEnum_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyEnumTable_count;
			ret->travel = MyEnumTable_travelForward;
			ret->travelForward = MyEnumTable_travelForward;
			ret->travelBackward = MyEnumTable_travelBackward;
			ret->get_array = MyEnumTable_get_array;
			ret->add = MyEnumTable_add;
			ret->getHead = MyEnumTable_getHead;
			ret->getTail = MyEnumTable_getTail;
			ret->cmp = MyEnum_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyEnumTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyEnumTable_purge(MyEnumTable *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyEnumTable_del(MyEnumTable *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyEnumTable_dump(void *ptr, MyEnum *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "%s(%d)\n", MyEnumStr(*p), *p);
	return err;
}

void MyEnumTable_dump(MyEnumTable *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyEnumTable_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
// MyEnumTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnumIndex
static Dz1Error MyEnumIndex_add(MyEnumIndex *p, MyEnum data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyEnum *temp = NULL;
	if (Dz1AATree_find(p->storage, (void *)&data)) ERR_SET_OUT(&err, EEXIST);
	else if ((temp = (MyEnum *)Dz1Calloc(sizeof(MyEnum), 1, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((void (*)(void *))MyEnum_del, (void *)temp);

		memcpy(temp, &data, sizeof(MyEnum));
		err = Dz1AATree_insert(p->storage, temp);
		if (ERR_PROBE(&err)) ERR_OUT(&err);

		pthread_cleanup_pop(ERR_PROBE(&err)); // ((void (*)(void *))MyEnum_del, (void *)temp);

	}
	return err;
}

static bool_t MyEnumIndex_remove(MyEnumIndex *p, MyEnum *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyEnum *MyEnumIndex_extract(MyEnumIndex *p, MyEnum *key)
{
	return (MyEnum *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyEnumIndexMkArrArg
{
	MyEnum *arr;
	unsigned int idx;
} MyEnumIndexMkArrArg;

static Dz1Error _MyEnumIndex_get_array(void *ptr, MyEnum *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyEnumIndexMkArrArg *arg = (MyEnumIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = *p;
	return err;
}

static MyEnum *MyEnumIndex_get_array(MyEnumIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyEnum *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyEnum *)Dz1Calloc(sizeof(MyEnum *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyEnumIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyEnumIndex_get_array, (void *)&arg);
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

static Dz1Error MyEnumIndex_travelForward(MyEnumIndex *p, Dz1Error (*func)(void *ptr, MyEnum *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyEnumIndex_travelBackward(MyEnumIndex *p, Dz1Error (*func)(void *ptr, MyEnum *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyEnum *MyEnumIndex_find(MyEnumIndex *p, MyEnum key)
{
	return (MyEnum *)Dz1AATree_find(p->storage, &key);
}

static MyEnum *MyEnumIndex_getHead(MyEnumIndex *p)
{
	return (MyEnum *)Dz1AATree_getHead(p->storage);
}

static MyEnum *MyEnumIndex_getTail(MyEnumIndex *p)
{
	return (MyEnum *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyEnumIndex_count(MyEnumIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyEnumIndex *MyEnumIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyEnumIndex *ret = (MyEnumIndex *)Dz1Calloc(sizeof(MyEnumIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyEnumIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)MyEnum_cmp, (Dz1DelFunc)MyEnum_del, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyEnumIndex_count;
			ret->travel = MyEnumIndex_travelForward;
			ret->travelForward = MyEnumIndex_travelForward;
			ret->travelBackward = MyEnumIndex_travelBackward;
			ret->get_array = MyEnumIndex_get_array;
			ret->add = MyEnumIndex_add;
			ret->remove = MyEnumIndex_remove;
			ret->find = MyEnumIndex_find;
			ret->extract = MyEnumIndex_extract;
			ret->getHead = MyEnumIndex_getHead;
			ret->getTail = MyEnumIndex_getTail;
			ret->cmp = MyEnum_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyEnumIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyEnumIndex_purge(MyEnumIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyEnumIndex_del(MyEnumIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyEnumIndex_dump(void *ptr, MyEnum *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "%s(%d)\n", MyEnumStr(*p), *p);
	return err;
}

void MyEnumIndex_dump(MyEnumIndex *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyEnumIndex_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
// MyEnumIndex
////////////////////////////////////////////////////////////////////////////////

