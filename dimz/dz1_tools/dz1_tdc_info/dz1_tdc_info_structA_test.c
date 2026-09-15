////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_structA_test.h"

////////////////////////////////////////////////////////////////////////////////
// MyDataEntryA
MyDataEntryA *MyDataEntryA_new(str_t name, u32_t val, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataEntryA *__internal_ret = (MyDataEntryA *)Dz1Calloc(sizeof(MyDataEntryA), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyDataEntryA_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = dz1_built_in_str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->val = val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataEntryA_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyDataEntryA_copy(MyDataEntryA *dst, MyDataEntryA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = dz1_built_in_str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->val = src->val;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyDataEntryA *MyDataEntryA_clone(MyDataEntryA *src, Dz1Error *err)
{
	MyDataEntryA *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyDataEntryA *)Dz1Calloc(sizeof(MyDataEntryA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyDataEntryA_delAndSetNull, (void *)&dst);
		if (MyDataEntryA_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataEntryA_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyDataEntryA_purge(MyDataEntryA *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->name);
}

void MyDataEntryA_del(MyDataEntryA *p)
{
	if (p == NULL) return;
	MyDataEntryA_purge(p);
	Dz1Free(p);
}

void MyDataEntryA_dump(MyDataEntryA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "name = "); dz1_built_in_str_dump(p->name, tab); 
		Dz1ThreadA_tprintf(tab, "val = "); Dz1u32_dump(&p->val, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void MyDataEntryA_fdump(FILE *fp, MyDataEntryA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintf(fp, tab, "name = "); dz1_built_in_str_fdump(fp, p->name, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "val = "); Dz1u32_fdump(fp, &p->val, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
int MyDataEntryA_cmp(MyDataEntryA *a, MyDataEntryA *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->name, b->name)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}
// MyDataEntryA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueListA
static Dz1Error MyDataUniqueListA_add(MyDataUniqueListA *p, MyDataEntryA *data)
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

static bool_t MyDataUniqueListA_remove(MyDataUniqueListA *p, MyDataEntryA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryA *MyDataUniqueListA_extract(MyDataUniqueListA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueListAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataUniqueListAMkArrArg;

static Dz1Error _MyDataUniqueListA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueListAMkArrArg *arg = (MyDataUniqueListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataUniqueListA_get_array(MyDataUniqueListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueListA_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueListA_travelForward(MyDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueListA_travelBackward(MyDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataUniqueListA_find(MyDataUniqueListA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_find(p->storage, key);
}

static MyDataEntryA *MyDataUniqueListA_getHead(MyDataUniqueListA *p)
{
	return (MyDataEntryA *)Dz1AATree_getHead(p->storage);
}

static MyDataEntryA *MyDataUniqueListA_getTail(MyDataUniqueListA *p)
{
	return (MyDataEntryA *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueListA_count(MyDataUniqueListA *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueListA *MyDataUniqueListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueListA *ret = (MyDataUniqueListA *)Dz1Calloc(sizeof(MyDataUniqueListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntryA_cmp,
				(Dz1DelFunc)MyDataEntryA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueListA_count;
			ret->travel = MyDataUniqueListA_travelForward;
			ret->travelForward = MyDataUniqueListA_travelForward;
			ret->travelBackward = MyDataUniqueListA_travelBackward;
			ret->get_array = MyDataUniqueListA_get_array;
			ret->add = MyDataUniqueListA_add;
			ret->remove = MyDataUniqueListA_remove;
			ret->find = MyDataUniqueListA_find;
			ret->extract = MyDataUniqueListA_extract;
			ret->getHead = MyDataUniqueListA_getHead;
			ret->getTail = MyDataUniqueListA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueListA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueListA *p = (MyDataUniqueListA *)ptr;
	MyDataEntryA *cloned = MyDataEntryA_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueListA *MyDataUniqueListA_clone(MyDataUniqueListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueListA_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueListA_purge(MyDataUniqueListA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueListA_del(MyDataUniqueListA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueListA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataUniqueListA_dump(MyDataUniqueListA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataUniqueListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataUniqueListA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueListA_fdump(FILE *fp, MyDataUniqueListA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataUniqueListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataUniqueListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefListA
static Dz1Error MyDataUniqueRefListA_add(MyDataUniqueRefListA *p, MyDataEntryA *data)
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

static bool_t MyDataUniqueRefListA_remove(MyDataUniqueRefListA *p, MyDataEntryA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryA *MyDataUniqueRefListA_extract(MyDataUniqueRefListA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueRefListAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataUniqueRefListAMkArrArg;

static Dz1Error _MyDataUniqueRefListA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefListAMkArrArg *arg = (MyDataUniqueRefListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataUniqueRefListA_get_array(MyDataUniqueRefListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueRefListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueRefListA_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueRefListA_travelForward(MyDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueRefListA_travelBackward(MyDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataUniqueRefListA_find(MyDataUniqueRefListA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_find(p->storage, key);
}

static MyDataEntryA *MyDataUniqueRefListA_getHead(MyDataUniqueRefListA *p)
{
	return (MyDataEntryA *)Dz1AATree_getHead(p->storage);
}

static MyDataEntryA *MyDataUniqueRefListA_getTail(MyDataUniqueRefListA *p)
{
	return (MyDataEntryA *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueRefListA_count(MyDataUniqueRefListA *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueRefListA *MyDataUniqueRefListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefListA *ret = (MyDataUniqueRefListA *)Dz1Calloc(sizeof(MyDataUniqueRefListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntryA_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueRefListA_count;
			ret->travel = MyDataUniqueRefListA_travelForward;
			ret->travelForward = MyDataUniqueRefListA_travelForward;
			ret->travelBackward = MyDataUniqueRefListA_travelBackward;
			ret->get_array = MyDataUniqueRefListA_get_array;
			ret->add = MyDataUniqueRefListA_add;
			ret->remove = MyDataUniqueRefListA_remove;
			ret->find = MyDataUniqueRefListA_find;
			ret->extract = MyDataUniqueRefListA_extract;
			ret->getHead = MyDataUniqueRefListA_getHead;
			ret->getTail = MyDataUniqueRefListA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueRefListA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefListA *p = (MyDataUniqueRefListA *)ptr;
	MyDataEntryA *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueRefListA *MyDataUniqueRefListA_clone(MyDataUniqueRefListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueRefListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefListA_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueRefListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueRefListA_purge(MyDataUniqueRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueRefListA_del(MyDataUniqueRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueRefListA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataUniqueRefListA_dump(MyDataUniqueRefListA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataUniqueRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataUniqueRefListA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueRefListA_fdump(FILE *fp, MyDataUniqueRefListA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataUniqueRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataUniqueRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedListA
static Dz1Error MyDataOrderedListA_add(MyDataOrderedListA *p, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedListA_remove(MyDataOrderedListA *p, MyDataEntryA *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntryA *MyDataOrderedListA_extract(MyDataOrderedListA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedListAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataOrderedListAMkArrArg;

static Dz1Error _MyDataOrderedListA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedListAMkArrArg *arg = (MyDataOrderedListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataOrderedListA_get_array(MyDataOrderedListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedListA_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedListA_travelForward(MyDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedListA_travelBackward(MyDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataOrderedListA_find(MyDataOrderedListA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntryA *MyDataOrderedListA_getHead(MyDataOrderedListA *p)
{
	return (MyDataEntryA *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntryA *MyDataOrderedListA_getTail(MyDataOrderedListA *p)
{
	return (MyDataEntryA *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedListA_count(MyDataOrderedListA *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedListA *MyDataOrderedListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedListA *ret = (MyDataOrderedListA *)Dz1Calloc(sizeof(MyDataOrderedListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntryA_cmp,
				(Dz1DelFunc)MyDataEntryA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedListA_count;
			ret->travel = MyDataOrderedListA_travelForward;
			ret->travelForward = MyDataOrderedListA_travelForward;
			ret->travelBackward = MyDataOrderedListA_travelBackward;
			ret->get_array = MyDataOrderedListA_get_array;
			ret->add = MyDataOrderedListA_add;
			ret->remove = MyDataOrderedListA_remove;
			ret->find = MyDataOrderedListA_find;
			ret->extract = MyDataOrderedListA_extract;
			ret->getHead = MyDataOrderedListA_getHead;
			ret->getTail = MyDataOrderedListA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedListA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedListA *p = (MyDataOrderedListA *)ptr;
	MyDataEntryA *cloned = MyDataEntryA_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedListA *MyDataOrderedListA_clone(MyDataOrderedListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedListA_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedListA_purge(MyDataOrderedListA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedListA_del(MyDataOrderedListA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedListA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataOrderedListA_dump(MyDataOrderedListA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataOrderedListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataOrderedListA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedListA_fdump(FILE *fp, MyDataOrderedListA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataOrderedListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataOrderedListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefListA
static Dz1Error MyDataOrderedRefListA_add(MyDataOrderedRefListA *p, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedRefListA_remove(MyDataOrderedRefListA *p, MyDataEntryA *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntryA *MyDataOrderedRefListA_extract(MyDataOrderedRefListA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedRefListAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataOrderedRefListAMkArrArg;

static Dz1Error _MyDataOrderedRefListA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefListAMkArrArg *arg = (MyDataOrderedRefListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataOrderedRefListA_get_array(MyDataOrderedRefListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedRefListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedRefListA_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedRefListA_travelForward(MyDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedRefListA_travelBackward(MyDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataOrderedRefListA_find(MyDataOrderedRefListA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntryA *MyDataOrderedRefListA_getHead(MyDataOrderedRefListA *p)
{
	return (MyDataEntryA *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntryA *MyDataOrderedRefListA_getTail(MyDataOrderedRefListA *p)
{
	return (MyDataEntryA *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedRefListA_count(MyDataOrderedRefListA *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedRefListA *MyDataOrderedRefListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefListA *ret = (MyDataOrderedRefListA *)Dz1Calloc(sizeof(MyDataOrderedRefListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntryA_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedRefListA_count;
			ret->travel = MyDataOrderedRefListA_travelForward;
			ret->travelForward = MyDataOrderedRefListA_travelForward;
			ret->travelBackward = MyDataOrderedRefListA_travelBackward;
			ret->get_array = MyDataOrderedRefListA_get_array;
			ret->add = MyDataOrderedRefListA_add;
			ret->remove = MyDataOrderedRefListA_remove;
			ret->find = MyDataOrderedRefListA_find;
			ret->extract = MyDataOrderedRefListA_extract;
			ret->getHead = MyDataOrderedRefListA_getHead;
			ret->getTail = MyDataOrderedRefListA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedRefListA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefListA *p = (MyDataOrderedRefListA *)ptr;
	MyDataEntryA *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedRefListA *MyDataOrderedRefListA_clone(MyDataOrderedRefListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedRefListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefListA_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedRefListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedRefListA_purge(MyDataOrderedRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedRefListA_del(MyDataOrderedRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedRefListA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataOrderedRefListA_dump(MyDataOrderedRefListA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataOrderedRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataOrderedRefListA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedRefListA_fdump(FILE *fp, MyDataOrderedRefListA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataOrderedRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataOrderedRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataListA
static Dz1Error MyDataListA_add(MyDataListA *p, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyDataEntryA *MyDataListA_extract(MyDataListA *p, MyDataEntryA *ptr)
{
	return (MyDataEntryA *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataListAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataListAMkArrArg;

static Dz1Error _MyDataListA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataListAMkArrArg *arg = (MyDataListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataListA_get_array(MyDataListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataListA_get_array, (void *)&arg);
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

static Dz1Error MyDataListA_travelForward(MyDataListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataListA_travelBackward(MyDataListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataListAFindArg
{
	MyDataEntryA *key;
	MyDataEntryA *ret;
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataListAFindArg;

static Dz1Error _MyDataListA_find(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataListAFindArg *arg = (MyDataListAFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntryA *MyDataListA_find(MyDataListA *p, MyDataEntryA *key)
{
	MyDataListAFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataListA_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntryA *MyDataListA_getHead(MyDataListA *p)
{
	return (MyDataEntryA *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntryA *MyDataListA_getTail(MyDataListA *p)
{
	return (MyDataEntryA *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataListA_count(MyDataListA *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataListA *MyDataListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataListA *ret = (MyDataListA *)Dz1Calloc(sizeof(MyDataListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyDataEntryA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataListA_count;
			ret->travel = MyDataListA_travelForward;
			ret->travelForward = MyDataListA_travelForward;
			ret->travelBackward = MyDataListA_travelBackward;
			ret->get_array = MyDataListA_get_array;
			ret->add = MyDataListA_add;
			ret->find = MyDataListA_find;
			ret->extract = MyDataListA_extract;
			ret->getHead = MyDataListA_getHead;
			ret->getTail = MyDataListA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataListA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataListA *p = (MyDataListA *)ptr;
	MyDataEntryA *cloned = MyDataEntryA_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataListA *MyDataListA_clone(MyDataListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataListA_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataListA_purge(MyDataListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataListA_del(MyDataListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataListA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataListA_dump(MyDataListA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataListA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataListA_fdump(FILE *fp, MyDataListA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefListA
static Dz1Error MyDataRefListA_add(MyDataRefListA *p, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyDataEntryA *MyDataRefListA_extract(MyDataRefListA *p, MyDataEntryA *ptr)
{
	return (MyDataEntryA *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataRefListAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataRefListAMkArrArg;

static Dz1Error _MyDataRefListA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefListAMkArrArg *arg = (MyDataRefListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataRefListA_get_array(MyDataRefListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataRefListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataRefListA_get_array, (void *)&arg);
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

static Dz1Error MyDataRefListA_travelForward(MyDataRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataRefListA_travelBackward(MyDataRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataRefListAFindArg
{
	MyDataEntryA *key;
	MyDataEntryA *ret;
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataRefListAFindArg;

static Dz1Error _MyDataRefListA_find(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataRefListAFindArg *arg = (MyDataRefListAFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntryA *MyDataRefListA_find(MyDataRefListA *p, MyDataEntryA *key)
{
	MyDataRefListAFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataRefListA_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntryA *MyDataRefListA_getHead(MyDataRefListA *p)
{
	return (MyDataEntryA *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntryA *MyDataRefListA_getTail(MyDataRefListA *p)
{
	return (MyDataEntryA *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataRefListA_count(MyDataRefListA *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataRefListA *MyDataRefListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefListA *ret = (MyDataRefListA *)Dz1Calloc(sizeof(MyDataRefListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataRefListA_count;
			ret->travel = MyDataRefListA_travelForward;
			ret->travelForward = MyDataRefListA_travelForward;
			ret->travelBackward = MyDataRefListA_travelBackward;
			ret->get_array = MyDataRefListA_get_array;
			ret->add = MyDataRefListA_add;
			ret->find = MyDataRefListA_find;
			ret->extract = MyDataRefListA_extract;
			ret->getHead = MyDataRefListA_getHead;
			ret->getTail = MyDataRefListA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataRefListA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefListA *p = (MyDataRefListA *)ptr;
	MyDataEntryA *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataRefListA *MyDataRefListA_clone(MyDataRefListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataRefListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefListA_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataRefListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataRefListA_purge(MyDataRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataRefListA_del(MyDataRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataRefListA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataRefListA_dump(MyDataRefListA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataRefListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataRefListA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataRefListA_fdump(FILE *fp, MyDataRefListA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataRefListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueArrayA
static Dz1Error MyDataUniqueArrayA_add(MyDataUniqueArrayA *p, MyDataEntryA *data)
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

static bool_t MyDataUniqueArrayA_remove(MyDataUniqueArrayA *p, MyDataEntryA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryA *MyDataUniqueArrayA_extract(MyDataUniqueArrayA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueArrayAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataUniqueArrayAMkArrArg;

static Dz1Error _MyDataUniqueArrayA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueArrayAMkArrArg *arg = (MyDataUniqueArrayAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataUniqueArrayA_get_array(MyDataUniqueArrayA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueArrayAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueArrayA_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueArrayA_travelForward(MyDataUniqueArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueArrayA_travelBackward(MyDataUniqueArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataUniqueArrayA_find(MyDataUniqueArrayA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_find(p->storage, key);
}

static MyDataEntryA *MyDataUniqueArrayA_getHead(MyDataUniqueArrayA *p)
{
	return (MyDataEntryA *)Dz1AATree_getHead(p->storage);
}

static MyDataEntryA *MyDataUniqueArrayA_getTail(MyDataUniqueArrayA *p)
{
	return (MyDataEntryA *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueArrayA_count(MyDataUniqueArrayA *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueArrayA *MyDataUniqueArrayA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueArrayA *ret = (MyDataUniqueArrayA *)Dz1Calloc(sizeof(MyDataUniqueArrayA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueArrayA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntryA_cmp,
				(Dz1DelFunc)MyDataEntryA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueArrayA_count;
			ret->travel = MyDataUniqueArrayA_travelForward;
			ret->travelForward = MyDataUniqueArrayA_travelForward;
			ret->travelBackward = MyDataUniqueArrayA_travelBackward;
			ret->get_array = MyDataUniqueArrayA_get_array;
			ret->add = MyDataUniqueArrayA_add;
			ret->remove = MyDataUniqueArrayA_remove;
			ret->find = MyDataUniqueArrayA_find;
			ret->extract = MyDataUniqueArrayA_extract;
			ret->getHead = MyDataUniqueArrayA_getHead;
			ret->getTail = MyDataUniqueArrayA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueArrayA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueArrayA *p = (MyDataUniqueArrayA *)ptr;
	MyDataEntryA *cloned = MyDataEntryA_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueArrayA *MyDataUniqueArrayA_clone(MyDataUniqueArrayA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueArrayA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueArrayA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueArrayA_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueArrayA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueArrayA_purge(MyDataUniqueArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueArrayA_del(MyDataUniqueArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueArrayA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataUniqueArrayA_dump(MyDataUniqueArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataUniqueArrayA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataUniqueArrayA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueArrayA_fdump(FILE *fp, MyDataUniqueArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataUniqueArrayA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataUniqueArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefArrayA
static Dz1Error MyDataUniqueRefArrayA_add(MyDataUniqueRefArrayA *p, MyDataEntryA *data)
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

static bool_t MyDataUniqueRefArrayA_remove(MyDataUniqueRefArrayA *p, MyDataEntryA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryA *MyDataUniqueRefArrayA_extract(MyDataUniqueRefArrayA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueRefArrayAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataUniqueRefArrayAMkArrArg;

static Dz1Error _MyDataUniqueRefArrayA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefArrayAMkArrArg *arg = (MyDataUniqueRefArrayAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataUniqueRefArrayA_get_array(MyDataUniqueRefArrayA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueRefArrayAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueRefArrayA_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueRefArrayA_travelForward(MyDataUniqueRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueRefArrayA_travelBackward(MyDataUniqueRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataUniqueRefArrayA_find(MyDataUniqueRefArrayA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_find(p->storage, key);
}

static MyDataEntryA *MyDataUniqueRefArrayA_getHead(MyDataUniqueRefArrayA *p)
{
	return (MyDataEntryA *)Dz1AATree_getHead(p->storage);
}

static MyDataEntryA *MyDataUniqueRefArrayA_getTail(MyDataUniqueRefArrayA *p)
{
	return (MyDataEntryA *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueRefArrayA_count(MyDataUniqueRefArrayA *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueRefArrayA *MyDataUniqueRefArrayA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefArrayA *ret = (MyDataUniqueRefArrayA *)Dz1Calloc(sizeof(MyDataUniqueRefArrayA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefArrayA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntryA_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueRefArrayA_count;
			ret->travel = MyDataUniqueRefArrayA_travelForward;
			ret->travelForward = MyDataUniqueRefArrayA_travelForward;
			ret->travelBackward = MyDataUniqueRefArrayA_travelBackward;
			ret->get_array = MyDataUniqueRefArrayA_get_array;
			ret->add = MyDataUniqueRefArrayA_add;
			ret->remove = MyDataUniqueRefArrayA_remove;
			ret->find = MyDataUniqueRefArrayA_find;
			ret->extract = MyDataUniqueRefArrayA_extract;
			ret->getHead = MyDataUniqueRefArrayA_getHead;
			ret->getTail = MyDataUniqueRefArrayA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueRefArrayA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefArrayA *p = (MyDataUniqueRefArrayA *)ptr;
	MyDataEntryA *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueRefArrayA *MyDataUniqueRefArrayA_clone(MyDataUniqueRefArrayA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefArrayA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueRefArrayA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefArrayA_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueRefArrayA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueRefArrayA_purge(MyDataUniqueRefArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueRefArrayA_del(MyDataUniqueRefArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueRefArrayA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataUniqueRefArrayA_dump(MyDataUniqueRefArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataUniqueRefArrayA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataUniqueRefArrayA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueRefArrayA_fdump(FILE *fp, MyDataUniqueRefArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataUniqueRefArrayA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataUniqueRefArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedArrayA
static Dz1Error MyDataOrderedArrayA_add(MyDataOrderedArrayA *p, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedArrayA_remove(MyDataOrderedArrayA *p, MyDataEntryA *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntryA *MyDataOrderedArrayA_extract(MyDataOrderedArrayA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedArrayAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataOrderedArrayAMkArrArg;

static Dz1Error _MyDataOrderedArrayA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedArrayAMkArrArg *arg = (MyDataOrderedArrayAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataOrderedArrayA_get_array(MyDataOrderedArrayA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedArrayAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedArrayA_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedArrayA_travelForward(MyDataOrderedArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedArrayA_travelBackward(MyDataOrderedArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataOrderedArrayA_find(MyDataOrderedArrayA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntryA *MyDataOrderedArrayA_getHead(MyDataOrderedArrayA *p)
{
	return (MyDataEntryA *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntryA *MyDataOrderedArrayA_getTail(MyDataOrderedArrayA *p)
{
	return (MyDataEntryA *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedArrayA_count(MyDataOrderedArrayA *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedArrayA *MyDataOrderedArrayA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedArrayA *ret = (MyDataOrderedArrayA *)Dz1Calloc(sizeof(MyDataOrderedArrayA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedArrayA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntryA_cmp,
				(Dz1DelFunc)MyDataEntryA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedArrayA_count;
			ret->travel = MyDataOrderedArrayA_travelForward;
			ret->travelForward = MyDataOrderedArrayA_travelForward;
			ret->travelBackward = MyDataOrderedArrayA_travelBackward;
			ret->get_array = MyDataOrderedArrayA_get_array;
			ret->add = MyDataOrderedArrayA_add;
			ret->remove = MyDataOrderedArrayA_remove;
			ret->find = MyDataOrderedArrayA_find;
			ret->extract = MyDataOrderedArrayA_extract;
			ret->getHead = MyDataOrderedArrayA_getHead;
			ret->getTail = MyDataOrderedArrayA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedArrayA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedArrayA *p = (MyDataOrderedArrayA *)ptr;
	MyDataEntryA *cloned = MyDataEntryA_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedArrayA *MyDataOrderedArrayA_clone(MyDataOrderedArrayA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedArrayA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedArrayA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedArrayA_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedArrayA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedArrayA_purge(MyDataOrderedArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedArrayA_del(MyDataOrderedArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedArrayA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataOrderedArrayA_dump(MyDataOrderedArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataOrderedArrayA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataOrderedArrayA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedArrayA_fdump(FILE *fp, MyDataOrderedArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataOrderedArrayA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataOrderedArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefArrayA
static Dz1Error MyDataOrderedRefArrayA_add(MyDataOrderedRefArrayA *p, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedRefArrayA_remove(MyDataOrderedRefArrayA *p, MyDataEntryA *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntryA *MyDataOrderedRefArrayA_extract(MyDataOrderedRefArrayA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedRefArrayAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataOrderedRefArrayAMkArrArg;

static Dz1Error _MyDataOrderedRefArrayA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefArrayAMkArrArg *arg = (MyDataOrderedRefArrayAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataOrderedRefArrayA_get_array(MyDataOrderedRefArrayA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedRefArrayAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedRefArrayA_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedRefArrayA_travelForward(MyDataOrderedRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedRefArrayA_travelBackward(MyDataOrderedRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataOrderedRefArrayA_find(MyDataOrderedRefArrayA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntryA *MyDataOrderedRefArrayA_getHead(MyDataOrderedRefArrayA *p)
{
	return (MyDataEntryA *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntryA *MyDataOrderedRefArrayA_getTail(MyDataOrderedRefArrayA *p)
{
	return (MyDataEntryA *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedRefArrayA_count(MyDataOrderedRefArrayA *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedRefArrayA *MyDataOrderedRefArrayA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefArrayA *ret = (MyDataOrderedRefArrayA *)Dz1Calloc(sizeof(MyDataOrderedRefArrayA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefArrayA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntryA_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedRefArrayA_count;
			ret->travel = MyDataOrderedRefArrayA_travelForward;
			ret->travelForward = MyDataOrderedRefArrayA_travelForward;
			ret->travelBackward = MyDataOrderedRefArrayA_travelBackward;
			ret->get_array = MyDataOrderedRefArrayA_get_array;
			ret->add = MyDataOrderedRefArrayA_add;
			ret->remove = MyDataOrderedRefArrayA_remove;
			ret->find = MyDataOrderedRefArrayA_find;
			ret->extract = MyDataOrderedRefArrayA_extract;
			ret->getHead = MyDataOrderedRefArrayA_getHead;
			ret->getTail = MyDataOrderedRefArrayA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedRefArrayA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefArrayA *p = (MyDataOrderedRefArrayA *)ptr;
	MyDataEntryA *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedRefArrayA *MyDataOrderedRefArrayA_clone(MyDataOrderedRefArrayA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefArrayA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedRefArrayA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefArrayA_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedRefArrayA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedRefArrayA_purge(MyDataOrderedRefArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedRefArrayA_del(MyDataOrderedRefArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedRefArrayA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataOrderedRefArrayA_dump(MyDataOrderedRefArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataOrderedRefArrayA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataOrderedRefArrayA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedRefArrayA_fdump(FILE *fp, MyDataOrderedRefArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataOrderedRefArrayA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataOrderedRefArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataArrayA
static Dz1Error MyDataArrayA_add(MyDataArrayA *p, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyDataEntryA *MyDataArrayA_extract(MyDataArrayA *p, MyDataEntryA *ptr)
{
	return (MyDataEntryA *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataArrayAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataArrayAMkArrArg;

static Dz1Error _MyDataArrayA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataArrayAMkArrArg *arg = (MyDataArrayAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataArrayA_get_array(MyDataArrayA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataArrayAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataArrayA_get_array, (void *)&arg);
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

static Dz1Error MyDataArrayA_travelForward(MyDataArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataArrayA_travelBackward(MyDataArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataArrayAFindArg
{
	MyDataEntryA *key;
	MyDataEntryA *ret;
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataArrayAFindArg;

static Dz1Error _MyDataArrayA_find(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataArrayAFindArg *arg = (MyDataArrayAFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntryA *MyDataArrayA_find(MyDataArrayA *p, MyDataEntryA *key)
{
	MyDataArrayAFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataArrayA_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntryA *MyDataArrayA_getHead(MyDataArrayA *p)
{
	return (MyDataEntryA *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntryA *MyDataArrayA_getTail(MyDataArrayA *p)
{
	return (MyDataEntryA *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataArrayA_count(MyDataArrayA *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataArrayA *MyDataArrayA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataArrayA *ret = (MyDataArrayA *)Dz1Calloc(sizeof(MyDataArrayA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataArrayA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyDataEntryA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataArrayA_count;
			ret->travel = MyDataArrayA_travelForward;
			ret->travelForward = MyDataArrayA_travelForward;
			ret->travelBackward = MyDataArrayA_travelBackward;
			ret->get_array = MyDataArrayA_get_array;
			ret->add = MyDataArrayA_add;
			ret->find = MyDataArrayA_find;
			ret->extract = MyDataArrayA_extract;
			ret->getHead = MyDataArrayA_getHead;
			ret->getTail = MyDataArrayA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataArrayA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataArrayA *p = (MyDataArrayA *)ptr;
	MyDataEntryA *cloned = MyDataEntryA_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataArrayA *MyDataArrayA_clone(MyDataArrayA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataArrayA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataArrayA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataArrayA_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataArrayA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataArrayA_purge(MyDataArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataArrayA_del(MyDataArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataArrayA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataArrayA_dump(MyDataArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataArrayA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataArrayA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataArrayA_fdump(FILE *fp, MyDataArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataArrayA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefArrayA
static Dz1Error MyDataRefArrayA_add(MyDataRefArrayA *p, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyDataEntryA *MyDataRefArrayA_extract(MyDataRefArrayA *p, MyDataEntryA *ptr)
{
	return (MyDataEntryA *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataRefArrayAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataRefArrayAMkArrArg;

static Dz1Error _MyDataRefArrayA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefArrayAMkArrArg *arg = (MyDataRefArrayAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataRefArrayA_get_array(MyDataRefArrayA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataRefArrayAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataRefArrayA_get_array, (void *)&arg);
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

static Dz1Error MyDataRefArrayA_travelForward(MyDataRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataRefArrayA_travelBackward(MyDataRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataRefArrayAFindArg
{
	MyDataEntryA *key;
	MyDataEntryA *ret;
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataRefArrayAFindArg;

static Dz1Error _MyDataRefArrayA_find(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataRefArrayAFindArg *arg = (MyDataRefArrayAFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntryA *MyDataRefArrayA_find(MyDataRefArrayA *p, MyDataEntryA *key)
{
	MyDataRefArrayAFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataRefArrayA_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntryA *MyDataRefArrayA_getHead(MyDataRefArrayA *p)
{
	return (MyDataEntryA *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntryA *MyDataRefArrayA_getTail(MyDataRefArrayA *p)
{
	return (MyDataEntryA *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataRefArrayA_count(MyDataRefArrayA *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataRefArrayA *MyDataRefArrayA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefArrayA *ret = (MyDataRefArrayA *)Dz1Calloc(sizeof(MyDataRefArrayA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefArrayA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataRefArrayA_count;
			ret->travel = MyDataRefArrayA_travelForward;
			ret->travelForward = MyDataRefArrayA_travelForward;
			ret->travelBackward = MyDataRefArrayA_travelBackward;
			ret->get_array = MyDataRefArrayA_get_array;
			ret->add = MyDataRefArrayA_add;
			ret->find = MyDataRefArrayA_find;
			ret->extract = MyDataRefArrayA_extract;
			ret->getHead = MyDataRefArrayA_getHead;
			ret->getTail = MyDataRefArrayA_getTail;
			ret->cmp = MyDataEntryA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataRefArrayA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefArrayA *p = (MyDataRefArrayA *)ptr;
	MyDataEntryA *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataRefArrayA *MyDataRefArrayA_clone(MyDataRefArrayA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefArrayA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataRefArrayA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefArrayA_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataRefArrayA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefArrayA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataRefArrayA_purge(MyDataRefArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataRefArrayA_del(MyDataRefArrayA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataRefArrayA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataRefArrayA_dump(MyDataRefArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataRefArrayA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataRefArrayA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataRefArrayA_fdump(FILE *fp, MyDataRefArrayA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataRefArrayA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataRefArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataIndexA
static Dz1Error MyDataIndexA_add(MyDataIndexA *p, MyDataEntryA *data)
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

static bool_t MyDataIndexA_remove(MyDataIndexA *p, MyDataEntryA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryA *MyDataIndexA_extract(MyDataIndexA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataIndexAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataIndexAMkArrArg;

static Dz1Error _MyDataIndexA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataIndexAMkArrArg *arg = (MyDataIndexAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataIndexA_get_array(MyDataIndexA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataIndexAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataIndexA_get_array, (void *)&arg);
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

static Dz1Error MyDataIndexA_travelForward(MyDataIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataIndexA_travelBackward(MyDataIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataIndexA_find(MyDataIndexA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyDataIndexA_count(MyDataIndexA *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _MyDataIndexA_cmp(MyDataEntryA *a, MyDataEntryA *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}

MyDataIndexA *MyDataIndexA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataIndexA *ret = (MyDataIndexA *)Dz1Calloc(sizeof(MyDataIndexA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataIndexA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_MyDataIndexA_cmp, (Dz1DelFunc)MyDataEntryA_del, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataIndexA_count;
			ret->travel = MyDataIndexA_travelForward;
			ret->travelForward = MyDataIndexA_travelForward;
			ret->travelBackward = MyDataIndexA_travelBackward;
			ret->get_array = MyDataIndexA_get_array;
			ret->add = MyDataIndexA_add;
			ret->remove = MyDataIndexA_remove;
			ret->find = MyDataIndexA_find;
			ret->extract = MyDataIndexA_extract;
			ret->cmp = _MyDataIndexA_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataIndexA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataIndexA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataIndexA *p = (MyDataIndexA *)ptr;
	MyDataEntryA *cloned = MyDataEntryA_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataIndexA *MyDataIndexA_clone(MyDataIndexA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataIndexA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataIndexA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataIndexA_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataIndexA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataIndexA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataIndexA_purge(MyDataIndexA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataIndexA_del(MyDataIndexA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataIndexA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataIndexA_dump(MyDataIndexA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataIndexA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataIndexA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataIndexA_fdump(FILE *fp, MyDataIndexA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataIndexA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataIndexA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefIndexA
static Dz1Error MyDataRefIndexA_add(MyDataRefIndexA *p, MyDataEntryA *data)
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

static bool_t MyDataRefIndexA_remove(MyDataRefIndexA *p, MyDataEntryA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryA *MyDataRefIndexA_extract(MyDataRefIndexA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataRefIndexAMkArrArg
{
	MyDataEntryA **arr;
	unsigned int idx;
} MyDataRefIndexAMkArrArg;

static Dz1Error _MyDataRefIndexA_get_array(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefIndexAMkArrArg *arg = (MyDataRefIndexAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryA **MyDataRefIndexA_get_array(MyDataRefIndexA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryA **)Dz1Calloc(sizeof(MyDataEntryA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataRefIndexAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataRefIndexA_get_array, (void *)&arg);
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

static Dz1Error MyDataRefIndexA_travelForward(MyDataRefIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataRefIndexA_travelBackward(MyDataRefIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryA *MyDataRefIndexA_find(MyDataRefIndexA *p, MyDataEntryA *key)
{
	return (MyDataEntryA *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyDataRefIndexA_count(MyDataRefIndexA *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _MyDataRefIndexA_cmp(MyDataEntryA *a, MyDataEntryA *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}

MyDataRefIndexA *MyDataRefIndexA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefIndexA *ret = (MyDataRefIndexA *)Dz1Calloc(sizeof(MyDataRefIndexA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefIndexA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_MyDataRefIndexA_cmp, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataRefIndexA_count;
			ret->travel = MyDataRefIndexA_travelForward;
			ret->travelForward = MyDataRefIndexA_travelForward;
			ret->travelBackward = MyDataRefIndexA_travelBackward;
			ret->get_array = MyDataRefIndexA_get_array;
			ret->add = MyDataRefIndexA_add;
			ret->remove = MyDataRefIndexA_remove;
			ret->find = MyDataRefIndexA_find;
			ret->extract = MyDataRefIndexA_extract;
			ret->cmp = _MyDataRefIndexA_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefIndexA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataRefIndexA_clone(void *ptr, MyDataEntryA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefIndexA *p = (MyDataRefIndexA *)ptr;
	MyDataEntryA *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataRefIndexA *MyDataRefIndexA_clone(MyDataRefIndexA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefIndexA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataRefIndexA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefIndexA_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataRefIndexA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefIndexA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataRefIndexA_purge(MyDataRefIndexA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataRefIndexA_del(MyDataRefIndexA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataRefIndexA_dump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); MyDataEntryA_dump(p, tab);
	return err;
}

void MyDataRefIndexA_dump(MyDataRefIndexA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _MyDataRefIndexA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _MyDataRefIndexA_fdump(void *ptr, MyDataEntryA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); MyDataEntryA_fdump(arg->fp, p, tab);
	return err;
}

void MyDataRefIndexA_fdump(FILE *fp, MyDataRefIndexA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _MyDataRefIndexA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// MyDataRefIndexA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberTypeA
// void ArrayMemberTypeA_obj_ptr_arr_del(MyDataEntryA **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberTypeA, MyDataEntryA*, obj_ptr_arr, u32_t, MyDataEntryA_del)
// void ArrayMemberTypeA_obj_ptr_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberTypeA, MyDataEntryA*, obj_ptr_arr, u32_t)
// MyDataEntryA **ArrayMemberTypeA_obj_ptr_arr_clone(MyDataEntryA **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberTypeA, MyDataEntryA*, obj_ptr_arr, u32_t, MyDataEntryA_clone)
// void ArrayMemberTypeA_obj_ptr_arrA_dump(MyDataEntryA **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberTypeA, MyDataEntryA*, obj_ptr_arr, u32_t, " = ", MyDataEntryA_dump)
// void ArrayMemberTypeA_obj_ptr_arrA_fdump(FILE *fp, MyDataEntryA **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberTypeA, MyDataEntryA*, obj_ptr_arr, u32_t, " = ", MyDataEntryA_fdump)

// void ArrayMemberTypeA_obj_arr_del(MyDataEntryA *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(ArrayMemberTypeA, MyDataEntryA, obj_arr, u32_t, MyDataEntryA_purge)
// void ArrayMemberTypeA_obj_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(ArrayMemberTypeA, MyDataEntryA, obj_arr, u32_t)
// MyDataEntryA *ArrayMemberTypeA_obj_arr_clone(MyDataEntryA *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(ArrayMemberTypeA, MyDataEntryA, obj_arr, u32_t, MyDataEntryA_copy)
// void ArrayMemberTypeA_obj_arrA_dump(MyDataEntryA *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_dump(ArrayMemberTypeA, MyDataEntryA, obj_arr, u32_t, " = ", MyDataEntryA_dump)
// void ArrayMemberTypeA_obj_arrA_fdump(FILE *fp, MyDataEntryA *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructA_fdump(ArrayMemberTypeA, MyDataEntryA, obj_arr, u32_t, " = ", MyDataEntryA_fdump)

// void ArrayMemberTypeA_prims_arr_del(u64_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(ArrayMemberTypeA, u64_t, prims_arr, u32_t)
// void ArrayMemberTypeA_prims_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(ArrayMemberTypeA, u64_t, prims_arr)
// u64_t *ArrayMemberTypeA_prims_arr_clone(u64_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(ArrayMemberTypeA, u64_t, prims_arr, u32_t)
// void ArrayMemberTypeA_prims_arrA_dump(u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_dump(ArrayMemberTypeA, u64_t, prims_arr, u32_t, " = ", Dz1u64A_dump)
// void ArrayMemberTypeA_prims_arrA_fdump(FILE *fp, u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveA_fdump(ArrayMemberTypeA, u64_t, prims_arr, u32_t, " = ", Dz1u64A_fdump)

// void ArrayMemberTypeA_primptrs_arr_del(u64_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberTypeA, u64_t*, primptrs_arr, u32_t, Dz1u64_del)
// void ArrayMemberTypeA_primptrs_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberTypeA, u64_t*, primptrs_arr, u32_t)
// u64_t **ArrayMemberTypeA_primptrs_arr_clone(u64_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberTypeA, u64_t*, primptrs_arr, u32_t, Dz1u64_clone)
// void ArrayMemberTypeA_primptrs_arrA_dump(u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberTypeA, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64A_dump)
// void ArrayMemberTypeA_primptrs_arrA_fdump(FILE *fp, u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberTypeA, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64A_fdump)

// void ArrayMemberTypeA_str_arr_del(str_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberTypeA, str_t, str_arr, u32_t, dz1_built_in_str_del)
// void ArrayMemberTypeA_str_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberTypeA, str_t, str_arr, u32_t)
// str_t *ArrayMemberTypeA_str_arr_clone(str_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberTypeA, str_t, str_arr, u32_t, dz1_built_in_str_clone)
// void ArrayMemberTypeA_str_arrA_dump(str_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_dump(ArrayMemberTypeA, str_t, str_arr, u32_t, " = ", dz1_built_in_strA_dump)
// void ArrayMemberTypeA_str_arrA_fdump(FILE *fp, str_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrA_fdump(ArrayMemberTypeA, str_t, str_arr, u32_t, " = ", dz1_built_in_strA_fdump)

ArrayMemberTypeA *ArrayMemberTypeA_new(MyDataEntryA **obj_ptr_arr/*_e_clone*/, 
									   u32_t obj_ptr_cnt, 
									   MyDataEntryA *obj_arr/*_e_copy*/, 
									   u32_t obj_cnt, 
									   u64_t *prims_arr/*_e_copy*/, 
									   u32_t prims_cnt, 
									   u64_t **primptrs_arr/*_e_clone*/, 
									   u32_t primptrs_cnt, 
									   str_t *str_arr/*_e_clone*/, 
									   u32_t str_cnt, 
									   s32_t *i_val/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberTypeA *__internal_ret = (ArrayMemberTypeA *)Dz1Calloc(sizeof(ArrayMemberTypeA), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ArrayMemberTypeA_delAndSetNull, (void *)&__internal_ret);
		
		if (obj_ptr_arr != NULL && (__internal_ret->obj_ptr_arr = ArrayMemberTypeA_obj_ptr_arr_clone(obj_ptr_arr, obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (obj_arr != NULL && (__internal_ret->obj_arr = ArrayMemberTypeA_obj_arr_clone(obj_arr, obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (prims_arr != NULL && (__internal_ret->prims_arr = ArrayMemberTypeA_prims_arr_clone(prims_arr, prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (primptrs_arr != NULL && (__internal_ret->primptrs_arr = ArrayMemberTypeA_primptrs_arr_clone(primptrs_arr, primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (str_arr != NULL && (__internal_ret->str_arr = ArrayMemberTypeA_str_arr_clone(str_arr, str_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->obj_ptr_cnt = obj_ptr_cnt;
			__internal_ret->obj_cnt = obj_cnt;
			__internal_ret->prims_cnt = prims_cnt;
			__internal_ret->primptrs_cnt = primptrs_cnt;
			__internal_ret->str_cnt = str_cnt;
			__internal_ret->i_val = i_val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberTypeA_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ArrayMemberTypeA_copy(ArrayMemberTypeA *dst, ArrayMemberTypeA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->obj_ptr_arr != NULL && (dst->obj_ptr_arr = ArrayMemberTypeA_obj_ptr_arr_clone(src->obj_ptr_arr, src->obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->obj_arr != NULL && (dst->obj_arr = ArrayMemberTypeA_obj_arr_clone(src->obj_arr, src->obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->prims_arr != NULL && (dst->prims_arr = ArrayMemberTypeA_prims_arr_clone(src->prims_arr, src->prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->primptrs_arr != NULL && (dst->primptrs_arr = ArrayMemberTypeA_primptrs_arr_clone(src->primptrs_arr, src->primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->str_arr != NULL && (dst->str_arr = ArrayMemberTypeA_str_arr_clone(src->str_arr, src->str_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		dst->obj_ptr_cnt = src->obj_ptr_cnt;
		dst->obj_cnt = src->obj_cnt;
		dst->prims_cnt = src->prims_cnt;
		dst->primptrs_cnt = src->primptrs_cnt;
		dst->str_cnt = src->str_cnt;
		dst->i_val = src->i_val;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ArrayMemberTypeA *ArrayMemberTypeA_clone(ArrayMemberTypeA *src, Dz1Error *err)
{
	ArrayMemberTypeA *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ArrayMemberTypeA *)Dz1Calloc(sizeof(ArrayMemberTypeA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ArrayMemberTypeA_delAndSetNull, (void *)&dst);
		if (ArrayMemberTypeA_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberTypeA_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ArrayMemberTypeA_purge(ArrayMemberTypeA *p)
{
	if (p == NULL) return;
	ArrayMemberTypeA_obj_ptr_arr_del(p->obj_ptr_arr, p->obj_ptr_cnt);
	ArrayMemberTypeA_obj_arr_del(p->obj_arr, p->obj_cnt);
	ArrayMemberTypeA_prims_arr_del(p->prims_arr, p->prims_cnt);
	ArrayMemberTypeA_primptrs_arr_del(p->primptrs_arr, p->primptrs_cnt);
	ArrayMemberTypeA_str_arr_del(p->str_arr, p->str_cnt);
}

void ArrayMemberTypeA_del(ArrayMemberTypeA *p)
{
	if (p == NULL) return;
	ArrayMemberTypeA_purge(p);
	Dz1Free(p);
}

void ArrayMemberTypeA_dump(ArrayMemberTypeA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "obj_ptr_arr = "); ArrayMemberTypeA_obj_ptr_arrA_dump(p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadA_tprintf(tab, "obj_ptr_cnt = "); Dz1u32_dump(&p->obj_ptr_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "obj_arr = "); ArrayMemberTypeA_obj_arrA_dump(p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadA_tprintf(tab, "obj_cnt = "); Dz1u32_dump(&p->obj_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "prims_arr = "); ArrayMemberTypeA_prims_arrA_dump(p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadA_tprintf(tab, "prims_cnt = "); Dz1u32_dump(&p->prims_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "primptrs_arr = "); ArrayMemberTypeA_primptrs_arrA_dump(p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadA_tprintf(tab, "primptrs_cnt = "); Dz1u32_dump(&p->primptrs_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "str_arr = "); ArrayMemberTypeA_str_arrA_dump(p->str_arr, p->str_cnt, tab);
		Dz1ThreadA_tprintf(tab, "str_cnt = "); Dz1u32_dump(&p->str_cnt, tab); 
		Dz1ThreadA_tprintf(tab, "i_val = "); Dz1s32_dump(p->i_val, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void ArrayMemberTypeA_fdump(FILE *fp, ArrayMemberTypeA *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintf(fp, tab, "obj_ptr_arr = "); ArrayMemberTypeA_obj_ptr_arrA_fdump(fp, p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "obj_ptr_cnt = "); Dz1u32_fdump(fp, &p->obj_ptr_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "obj_arr = "); ArrayMemberTypeA_obj_arrA_fdump(fp, p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "obj_cnt = "); Dz1u32_fdump(fp, &p->obj_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "prims_arr = "); ArrayMemberTypeA_prims_arrA_fdump(fp, p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "prims_cnt = "); Dz1u32_fdump(fp, &p->prims_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "primptrs_arr = "); ArrayMemberTypeA_primptrs_arrA_fdump(fp, p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "primptrs_cnt = "); Dz1u32_fdump(fp, &p->primptrs_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "str_arr = "); ArrayMemberTypeA_str_arrA_fdump(fp, p->str_arr, p->str_cnt, tab);
		Dz1ThreadA_ftprintf(fp, tab, "str_cnt = "); Dz1u32_fdump(fp, &p->str_cnt, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "i_val = "); Dz1s32_fdump(fp, p->i_val, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
// ArrayMemberTypeA
////////////////////////////////////////////////////////////////////////////////

