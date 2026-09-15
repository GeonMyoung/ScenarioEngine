////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_structW_test.h"

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataEntryW
MyDataEntryW *MyDataEntryW_new(wstr_t name, u32_t val, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataEntryW *__internal_ret = (MyDataEntryW *)Dz1Calloc(sizeof(MyDataEntryW), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyDataEntryW_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = dz1_built_in_wstr_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->val = val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataEntryW_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyDataEntryW_copy(MyDataEntryW *dst, MyDataEntryW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = dz1_built_in_wstr_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->val = src->val;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyDataEntryW *MyDataEntryW_clone(MyDataEntryW *src, Dz1Error *err)
{
	MyDataEntryW *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyDataEntryW *)Dz1Calloc(sizeof(MyDataEntryW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyDataEntryW_delAndSetNull, (void *)&dst);
		if (MyDataEntryW_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataEntryW_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyDataEntryW_purge(MyDataEntryW *p)
{
	if (p == NULL) return;
	dz1_built_in_wstr_del(p->name);
}

void MyDataEntryW_del(MyDataEntryW *p)
{
	if (p == NULL) return;
	MyDataEntryW_purge(p);
	Dz1Free(p);
}

void MyDataEntryW_dump(MyDataEntryW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"name = "); dz1_built_in_wstr_dump(p->name, tab); 
		Dz1ThreadW_tprintf(tab, L"val = "); Dz1u32_dump(&p->val, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void MyDataEntryW_fdump(FILE *fp, MyDataEntryW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintf(fp, tab, L"name = "); dz1_built_in_wstr_fdump(fp, p->name, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"val = "); Dz1u32_fdump(fp, &p->val, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
int MyDataEntryW_cmp(MyDataEntryW *a, MyDataEntryW *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = dz1_built_in_wstr_cmp(a->name, b->name)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}
// MyDataEntryW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueListW
static Dz1Error MyDataUniqueListW_add(MyDataUniqueListW *p, MyDataEntryW *data)
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

static bool_t MyDataUniqueListW_remove(MyDataUniqueListW *p, MyDataEntryW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryW *MyDataUniqueListW_extract(MyDataUniqueListW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueListWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataUniqueListWMkArrArg;

static Dz1Error _MyDataUniqueListW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueListWMkArrArg *arg = (MyDataUniqueListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataUniqueListW_get_array(MyDataUniqueListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueListW_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueListW_travelForward(MyDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueListW_travelBackward(MyDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataUniqueListW_find(MyDataUniqueListW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_find(p->storage, key);
}

static MyDataEntryW *MyDataUniqueListW_getHead(MyDataUniqueListW *p)
{
	return (MyDataEntryW *)Dz1AATree_getHead(p->storage);
}

static MyDataEntryW *MyDataUniqueListW_getTail(MyDataUniqueListW *p)
{
	return (MyDataEntryW *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueListW_count(MyDataUniqueListW *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueListW *MyDataUniqueListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueListW *ret = (MyDataUniqueListW *)Dz1Calloc(sizeof(MyDataUniqueListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntryW_cmp,
				(Dz1DelFunc)MyDataEntryW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueListW_count;
			ret->travel = MyDataUniqueListW_travelForward;
			ret->travelForward = MyDataUniqueListW_travelForward;
			ret->travelBackward = MyDataUniqueListW_travelBackward;
			ret->get_array = MyDataUniqueListW_get_array;
			ret->add = MyDataUniqueListW_add;
			ret->remove = MyDataUniqueListW_remove;
			ret->find = MyDataUniqueListW_find;
			ret->extract = MyDataUniqueListW_extract;
			ret->getHead = MyDataUniqueListW_getHead;
			ret->getTail = MyDataUniqueListW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueListW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueListW *p = (MyDataUniqueListW *)ptr;
	MyDataEntryW *cloned = MyDataEntryW_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueListW *MyDataUniqueListW_clone(MyDataUniqueListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueListW_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueListW_purge(MyDataUniqueListW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueListW_del(MyDataUniqueListW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueListW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataUniqueListW_dump(MyDataUniqueListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataUniqueListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataUniqueListW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueListW_fdump(FILE *fp, MyDataUniqueListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataUniqueListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataUniqueListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefListW
static Dz1Error MyDataUniqueRefListW_add(MyDataUniqueRefListW *p, MyDataEntryW *data)
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

static bool_t MyDataUniqueRefListW_remove(MyDataUniqueRefListW *p, MyDataEntryW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryW *MyDataUniqueRefListW_extract(MyDataUniqueRefListW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueRefListWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataUniqueRefListWMkArrArg;

static Dz1Error _MyDataUniqueRefListW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefListWMkArrArg *arg = (MyDataUniqueRefListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataUniqueRefListW_get_array(MyDataUniqueRefListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueRefListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueRefListW_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueRefListW_travelForward(MyDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueRefListW_travelBackward(MyDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataUniqueRefListW_find(MyDataUniqueRefListW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_find(p->storage, key);
}

static MyDataEntryW *MyDataUniqueRefListW_getHead(MyDataUniqueRefListW *p)
{
	return (MyDataEntryW *)Dz1AATree_getHead(p->storage);
}

static MyDataEntryW *MyDataUniqueRefListW_getTail(MyDataUniqueRefListW *p)
{
	return (MyDataEntryW *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueRefListW_count(MyDataUniqueRefListW *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueRefListW *MyDataUniqueRefListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefListW *ret = (MyDataUniqueRefListW *)Dz1Calloc(sizeof(MyDataUniqueRefListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntryW_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueRefListW_count;
			ret->travel = MyDataUniqueRefListW_travelForward;
			ret->travelForward = MyDataUniqueRefListW_travelForward;
			ret->travelBackward = MyDataUniqueRefListW_travelBackward;
			ret->get_array = MyDataUniqueRefListW_get_array;
			ret->add = MyDataUniqueRefListW_add;
			ret->remove = MyDataUniqueRefListW_remove;
			ret->find = MyDataUniqueRefListW_find;
			ret->extract = MyDataUniqueRefListW_extract;
			ret->getHead = MyDataUniqueRefListW_getHead;
			ret->getTail = MyDataUniqueRefListW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueRefListW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefListW *p = (MyDataUniqueRefListW *)ptr;
	MyDataEntryW *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueRefListW *MyDataUniqueRefListW_clone(MyDataUniqueRefListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueRefListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefListW_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueRefListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueRefListW_purge(MyDataUniqueRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueRefListW_del(MyDataUniqueRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueRefListW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataUniqueRefListW_dump(MyDataUniqueRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataUniqueRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataUniqueRefListW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueRefListW_fdump(FILE *fp, MyDataUniqueRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataUniqueRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataUniqueRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedListW
static Dz1Error MyDataOrderedListW_add(MyDataOrderedListW *p, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedListW_remove(MyDataOrderedListW *p, MyDataEntryW *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntryW *MyDataOrderedListW_extract(MyDataOrderedListW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedListWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataOrderedListWMkArrArg;

static Dz1Error _MyDataOrderedListW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedListWMkArrArg *arg = (MyDataOrderedListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataOrderedListW_get_array(MyDataOrderedListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedListW_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedListW_travelForward(MyDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedListW_travelBackward(MyDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataOrderedListW_find(MyDataOrderedListW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntryW *MyDataOrderedListW_getHead(MyDataOrderedListW *p)
{
	return (MyDataEntryW *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntryW *MyDataOrderedListW_getTail(MyDataOrderedListW *p)
{
	return (MyDataEntryW *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedListW_count(MyDataOrderedListW *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedListW *MyDataOrderedListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedListW *ret = (MyDataOrderedListW *)Dz1Calloc(sizeof(MyDataOrderedListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntryW_cmp,
				(Dz1DelFunc)MyDataEntryW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedListW_count;
			ret->travel = MyDataOrderedListW_travelForward;
			ret->travelForward = MyDataOrderedListW_travelForward;
			ret->travelBackward = MyDataOrderedListW_travelBackward;
			ret->get_array = MyDataOrderedListW_get_array;
			ret->add = MyDataOrderedListW_add;
			ret->remove = MyDataOrderedListW_remove;
			ret->find = MyDataOrderedListW_find;
			ret->extract = MyDataOrderedListW_extract;
			ret->getHead = MyDataOrderedListW_getHead;
			ret->getTail = MyDataOrderedListW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedListW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedListW *p = (MyDataOrderedListW *)ptr;
	MyDataEntryW *cloned = MyDataEntryW_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedListW *MyDataOrderedListW_clone(MyDataOrderedListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedListW_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedListW_purge(MyDataOrderedListW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedListW_del(MyDataOrderedListW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedListW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataOrderedListW_dump(MyDataOrderedListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataOrderedListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataOrderedListW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedListW_fdump(FILE *fp, MyDataOrderedListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataOrderedListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataOrderedListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefListW
static Dz1Error MyDataOrderedRefListW_add(MyDataOrderedRefListW *p, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedRefListW_remove(MyDataOrderedRefListW *p, MyDataEntryW *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntryW *MyDataOrderedRefListW_extract(MyDataOrderedRefListW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedRefListWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataOrderedRefListWMkArrArg;

static Dz1Error _MyDataOrderedRefListW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefListWMkArrArg *arg = (MyDataOrderedRefListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataOrderedRefListW_get_array(MyDataOrderedRefListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedRefListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedRefListW_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedRefListW_travelForward(MyDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedRefListW_travelBackward(MyDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataOrderedRefListW_find(MyDataOrderedRefListW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntryW *MyDataOrderedRefListW_getHead(MyDataOrderedRefListW *p)
{
	return (MyDataEntryW *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntryW *MyDataOrderedRefListW_getTail(MyDataOrderedRefListW *p)
{
	return (MyDataEntryW *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedRefListW_count(MyDataOrderedRefListW *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedRefListW *MyDataOrderedRefListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefListW *ret = (MyDataOrderedRefListW *)Dz1Calloc(sizeof(MyDataOrderedRefListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntryW_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedRefListW_count;
			ret->travel = MyDataOrderedRefListW_travelForward;
			ret->travelForward = MyDataOrderedRefListW_travelForward;
			ret->travelBackward = MyDataOrderedRefListW_travelBackward;
			ret->get_array = MyDataOrderedRefListW_get_array;
			ret->add = MyDataOrderedRefListW_add;
			ret->remove = MyDataOrderedRefListW_remove;
			ret->find = MyDataOrderedRefListW_find;
			ret->extract = MyDataOrderedRefListW_extract;
			ret->getHead = MyDataOrderedRefListW_getHead;
			ret->getTail = MyDataOrderedRefListW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedRefListW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefListW *p = (MyDataOrderedRefListW *)ptr;
	MyDataEntryW *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedRefListW *MyDataOrderedRefListW_clone(MyDataOrderedRefListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedRefListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefListW_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedRefListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedRefListW_purge(MyDataOrderedRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedRefListW_del(MyDataOrderedRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedRefListW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataOrderedRefListW_dump(MyDataOrderedRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataOrderedRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataOrderedRefListW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedRefListW_fdump(FILE *fp, MyDataOrderedRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataOrderedRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataOrderedRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataListW
static Dz1Error MyDataListW_add(MyDataListW *p, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyDataEntryW *MyDataListW_extract(MyDataListW *p, MyDataEntryW *ptr)
{
	return (MyDataEntryW *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataListWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataListWMkArrArg;

static Dz1Error _MyDataListW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataListWMkArrArg *arg = (MyDataListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataListW_get_array(MyDataListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataListW_get_array, (void *)&arg);
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

static Dz1Error MyDataListW_travelForward(MyDataListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataListW_travelBackward(MyDataListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataListWFindArg
{
	MyDataEntryW *key;
	MyDataEntryW *ret;
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataListWFindArg;

static Dz1Error _MyDataListW_find(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataListWFindArg *arg = (MyDataListWFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntryW *MyDataListW_find(MyDataListW *p, MyDataEntryW *key)
{
	MyDataListWFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataListW_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntryW *MyDataListW_getHead(MyDataListW *p)
{
	return (MyDataEntryW *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntryW *MyDataListW_getTail(MyDataListW *p)
{
	return (MyDataEntryW *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataListW_count(MyDataListW *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataListW *MyDataListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataListW *ret = (MyDataListW *)Dz1Calloc(sizeof(MyDataListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyDataEntryW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataListW_count;
			ret->travel = MyDataListW_travelForward;
			ret->travelForward = MyDataListW_travelForward;
			ret->travelBackward = MyDataListW_travelBackward;
			ret->get_array = MyDataListW_get_array;
			ret->add = MyDataListW_add;
			ret->find = MyDataListW_find;
			ret->extract = MyDataListW_extract;
			ret->getHead = MyDataListW_getHead;
			ret->getTail = MyDataListW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataListW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataListW *p = (MyDataListW *)ptr;
	MyDataEntryW *cloned = MyDataEntryW_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataListW *MyDataListW_clone(MyDataListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataListW_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataListW_purge(MyDataListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataListW_del(MyDataListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataListW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataListW_dump(MyDataListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataListW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataListW_fdump(FILE *fp, MyDataListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataRefListW
static Dz1Error MyDataRefListW_add(MyDataRefListW *p, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyDataEntryW *MyDataRefListW_extract(MyDataRefListW *p, MyDataEntryW *ptr)
{
	return (MyDataEntryW *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataRefListWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataRefListWMkArrArg;

static Dz1Error _MyDataRefListW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefListWMkArrArg *arg = (MyDataRefListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataRefListW_get_array(MyDataRefListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataRefListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataRefListW_get_array, (void *)&arg);
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

static Dz1Error MyDataRefListW_travelForward(MyDataRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataRefListW_travelBackward(MyDataRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataRefListWFindArg
{
	MyDataEntryW *key;
	MyDataEntryW *ret;
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataRefListWFindArg;

static Dz1Error _MyDataRefListW_find(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataRefListWFindArg *arg = (MyDataRefListWFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntryW *MyDataRefListW_find(MyDataRefListW *p, MyDataEntryW *key)
{
	MyDataRefListWFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataRefListW_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntryW *MyDataRefListW_getHead(MyDataRefListW *p)
{
	return (MyDataEntryW *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntryW *MyDataRefListW_getTail(MyDataRefListW *p)
{
	return (MyDataEntryW *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataRefListW_count(MyDataRefListW *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataRefListW *MyDataRefListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefListW *ret = (MyDataRefListW *)Dz1Calloc(sizeof(MyDataRefListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataRefListW_count;
			ret->travel = MyDataRefListW_travelForward;
			ret->travelForward = MyDataRefListW_travelForward;
			ret->travelBackward = MyDataRefListW_travelBackward;
			ret->get_array = MyDataRefListW_get_array;
			ret->add = MyDataRefListW_add;
			ret->find = MyDataRefListW_find;
			ret->extract = MyDataRefListW_extract;
			ret->getHead = MyDataRefListW_getHead;
			ret->getTail = MyDataRefListW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataRefListW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefListW *p = (MyDataRefListW *)ptr;
	MyDataEntryW *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataRefListW *MyDataRefListW_clone(MyDataRefListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataRefListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefListW_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataRefListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataRefListW_purge(MyDataRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataRefListW_del(MyDataRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataRefListW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataRefListW_dump(MyDataRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataRefListW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataRefListW_fdump(FILE *fp, MyDataRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueArrayW
static Dz1Error MyDataUniqueArrayW_add(MyDataUniqueArrayW *p, MyDataEntryW *data)
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

static bool_t MyDataUniqueArrayW_remove(MyDataUniqueArrayW *p, MyDataEntryW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryW *MyDataUniqueArrayW_extract(MyDataUniqueArrayW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueArrayWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataUniqueArrayWMkArrArg;

static Dz1Error _MyDataUniqueArrayW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueArrayWMkArrArg *arg = (MyDataUniqueArrayWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataUniqueArrayW_get_array(MyDataUniqueArrayW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueArrayWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueArrayW_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueArrayW_travelForward(MyDataUniqueArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueArrayW_travelBackward(MyDataUniqueArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataUniqueArrayW_find(MyDataUniqueArrayW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_find(p->storage, key);
}

static MyDataEntryW *MyDataUniqueArrayW_getHead(MyDataUniqueArrayW *p)
{
	return (MyDataEntryW *)Dz1AATree_getHead(p->storage);
}

static MyDataEntryW *MyDataUniqueArrayW_getTail(MyDataUniqueArrayW *p)
{
	return (MyDataEntryW *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueArrayW_count(MyDataUniqueArrayW *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueArrayW *MyDataUniqueArrayW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueArrayW *ret = (MyDataUniqueArrayW *)Dz1Calloc(sizeof(MyDataUniqueArrayW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueArrayW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntryW_cmp,
				(Dz1DelFunc)MyDataEntryW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueArrayW_count;
			ret->travel = MyDataUniqueArrayW_travelForward;
			ret->travelForward = MyDataUniqueArrayW_travelForward;
			ret->travelBackward = MyDataUniqueArrayW_travelBackward;
			ret->get_array = MyDataUniqueArrayW_get_array;
			ret->add = MyDataUniqueArrayW_add;
			ret->remove = MyDataUniqueArrayW_remove;
			ret->find = MyDataUniqueArrayW_find;
			ret->extract = MyDataUniqueArrayW_extract;
			ret->getHead = MyDataUniqueArrayW_getHead;
			ret->getTail = MyDataUniqueArrayW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueArrayW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueArrayW *p = (MyDataUniqueArrayW *)ptr;
	MyDataEntryW *cloned = MyDataEntryW_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueArrayW *MyDataUniqueArrayW_clone(MyDataUniqueArrayW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueArrayW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueArrayW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueArrayW_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueArrayW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueArrayW_purge(MyDataUniqueArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueArrayW_del(MyDataUniqueArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueArrayW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataUniqueArrayW_dump(MyDataUniqueArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataUniqueArrayW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataUniqueArrayW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueArrayW_fdump(FILE *fp, MyDataUniqueArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataUniqueArrayW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataUniqueArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefArrayW
static Dz1Error MyDataUniqueRefArrayW_add(MyDataUniqueRefArrayW *p, MyDataEntryW *data)
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

static bool_t MyDataUniqueRefArrayW_remove(MyDataUniqueRefArrayW *p, MyDataEntryW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryW *MyDataUniqueRefArrayW_extract(MyDataUniqueRefArrayW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataUniqueRefArrayWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataUniqueRefArrayWMkArrArg;

static Dz1Error _MyDataUniqueRefArrayW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefArrayWMkArrArg *arg = (MyDataUniqueRefArrayWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataUniqueRefArrayW_get_array(MyDataUniqueRefArrayW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataUniqueRefArrayWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataUniqueRefArrayW_get_array, (void *)&arg);
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

static Dz1Error MyDataUniqueRefArrayW_travelForward(MyDataUniqueRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataUniqueRefArrayW_travelBackward(MyDataUniqueRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataUniqueRefArrayW_find(MyDataUniqueRefArrayW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_find(p->storage, key);
}

static MyDataEntryW *MyDataUniqueRefArrayW_getHead(MyDataUniqueRefArrayW *p)
{
	return (MyDataEntryW *)Dz1AATree_getHead(p->storage);
}

static MyDataEntryW *MyDataUniqueRefArrayW_getTail(MyDataUniqueRefArrayW *p)
{
	return (MyDataEntryW *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyDataUniqueRefArrayW_count(MyDataUniqueRefArrayW *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyDataUniqueRefArrayW *MyDataUniqueRefArrayW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefArrayW *ret = (MyDataUniqueRefArrayW *)Dz1Calloc(sizeof(MyDataUniqueRefArrayW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefArrayW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyDataEntryW_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataUniqueRefArrayW_count;
			ret->travel = MyDataUniqueRefArrayW_travelForward;
			ret->travelForward = MyDataUniqueRefArrayW_travelForward;
			ret->travelBackward = MyDataUniqueRefArrayW_travelBackward;
			ret->get_array = MyDataUniqueRefArrayW_get_array;
			ret->add = MyDataUniqueRefArrayW_add;
			ret->remove = MyDataUniqueRefArrayW_remove;
			ret->find = MyDataUniqueRefArrayW_find;
			ret->extract = MyDataUniqueRefArrayW_extract;
			ret->getHead = MyDataUniqueRefArrayW_getHead;
			ret->getTail = MyDataUniqueRefArrayW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataUniqueRefArrayW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataUniqueRefArrayW *p = (MyDataUniqueRefArrayW *)ptr;
	MyDataEntryW *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataUniqueRefArrayW *MyDataUniqueRefArrayW_clone(MyDataUniqueRefArrayW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataUniqueRefArrayW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataUniqueRefArrayW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataUniqueRefArrayW_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataUniqueRefArrayW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataUniqueRefArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataUniqueRefArrayW_purge(MyDataUniqueRefArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataUniqueRefArrayW_del(MyDataUniqueRefArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataUniqueRefArrayW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataUniqueRefArrayW_dump(MyDataUniqueRefArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataUniqueRefArrayW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataUniqueRefArrayW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataUniqueRefArrayW_fdump(FILE *fp, MyDataUniqueRefArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataUniqueRefArrayW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataUniqueRefArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedArrayW
static Dz1Error MyDataOrderedArrayW_add(MyDataOrderedArrayW *p, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedArrayW_remove(MyDataOrderedArrayW *p, MyDataEntryW *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntryW *MyDataOrderedArrayW_extract(MyDataOrderedArrayW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedArrayWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataOrderedArrayWMkArrArg;

static Dz1Error _MyDataOrderedArrayW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedArrayWMkArrArg *arg = (MyDataOrderedArrayWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataOrderedArrayW_get_array(MyDataOrderedArrayW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedArrayWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedArrayW_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedArrayW_travelForward(MyDataOrderedArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedArrayW_travelBackward(MyDataOrderedArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataOrderedArrayW_find(MyDataOrderedArrayW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntryW *MyDataOrderedArrayW_getHead(MyDataOrderedArrayW *p)
{
	return (MyDataEntryW *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntryW *MyDataOrderedArrayW_getTail(MyDataOrderedArrayW *p)
{
	return (MyDataEntryW *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedArrayW_count(MyDataOrderedArrayW *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedArrayW *MyDataOrderedArrayW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedArrayW *ret = (MyDataOrderedArrayW *)Dz1Calloc(sizeof(MyDataOrderedArrayW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedArrayW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntryW_cmp,
				(Dz1DelFunc)MyDataEntryW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedArrayW_count;
			ret->travel = MyDataOrderedArrayW_travelForward;
			ret->travelForward = MyDataOrderedArrayW_travelForward;
			ret->travelBackward = MyDataOrderedArrayW_travelBackward;
			ret->get_array = MyDataOrderedArrayW_get_array;
			ret->add = MyDataOrderedArrayW_add;
			ret->remove = MyDataOrderedArrayW_remove;
			ret->find = MyDataOrderedArrayW_find;
			ret->extract = MyDataOrderedArrayW_extract;
			ret->getHead = MyDataOrderedArrayW_getHead;
			ret->getTail = MyDataOrderedArrayW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedArrayW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedArrayW *p = (MyDataOrderedArrayW *)ptr;
	MyDataEntryW *cloned = MyDataEntryW_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedArrayW *MyDataOrderedArrayW_clone(MyDataOrderedArrayW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedArrayW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedArrayW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedArrayW_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedArrayW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedArrayW_purge(MyDataOrderedArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedArrayW_del(MyDataOrderedArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedArrayW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataOrderedArrayW_dump(MyDataOrderedArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataOrderedArrayW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataOrderedArrayW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedArrayW_fdump(FILE *fp, MyDataOrderedArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataOrderedArrayW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataOrderedArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefArrayW
static Dz1Error MyDataOrderedRefArrayW_add(MyDataOrderedRefArrayW *p, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyDataOrderedRefArrayW_remove(MyDataOrderedRefArrayW *p, MyDataEntryW *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyDataEntryW *MyDataOrderedRefArrayW_extract(MyDataOrderedRefArrayW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyDataOrderedRefArrayWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataOrderedRefArrayWMkArrArg;

static Dz1Error _MyDataOrderedRefArrayW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefArrayWMkArrArg *arg = (MyDataOrderedRefArrayWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataOrderedRefArrayW_get_array(MyDataOrderedRefArrayW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataOrderedRefArrayWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataOrderedRefArrayW_get_array, (void *)&arg);
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

static Dz1Error MyDataOrderedRefArrayW_travelForward(MyDataOrderedRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataOrderedRefArrayW_travelBackward(MyDataOrderedRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataOrderedRefArrayW_find(MyDataOrderedRefArrayW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1OrderedFifo_find(p->storage, key);
}

static MyDataEntryW *MyDataOrderedRefArrayW_getHead(MyDataOrderedRefArrayW *p)
{
	return (MyDataEntryW *)Dz1OrderedFifo_getHead(p->storage);
}

static MyDataEntryW *MyDataOrderedRefArrayW_getTail(MyDataOrderedRefArrayW *p)
{
	return (MyDataEntryW *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyDataOrderedRefArrayW_count(MyDataOrderedRefArrayW *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyDataOrderedRefArrayW *MyDataOrderedRefArrayW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefArrayW *ret = (MyDataOrderedRefArrayW *)Dz1Calloc(sizeof(MyDataOrderedRefArrayW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefArrayW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyDataEntryW_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataOrderedRefArrayW_count;
			ret->travel = MyDataOrderedRefArrayW_travelForward;
			ret->travelForward = MyDataOrderedRefArrayW_travelForward;
			ret->travelBackward = MyDataOrderedRefArrayW_travelBackward;
			ret->get_array = MyDataOrderedRefArrayW_get_array;
			ret->add = MyDataOrderedRefArrayW_add;
			ret->remove = MyDataOrderedRefArrayW_remove;
			ret->find = MyDataOrderedRefArrayW_find;
			ret->extract = MyDataOrderedRefArrayW_extract;
			ret->getHead = MyDataOrderedRefArrayW_getHead;
			ret->getTail = MyDataOrderedRefArrayW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataOrderedRefArrayW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataOrderedRefArrayW *p = (MyDataOrderedRefArrayW *)ptr;
	MyDataEntryW *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataOrderedRefArrayW *MyDataOrderedRefArrayW_clone(MyDataOrderedRefArrayW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataOrderedRefArrayW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataOrderedRefArrayW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataOrderedRefArrayW_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataOrderedRefArrayW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataOrderedRefArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataOrderedRefArrayW_purge(MyDataOrderedRefArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyDataOrderedRefArrayW_del(MyDataOrderedRefArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataOrderedRefArrayW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataOrderedRefArrayW_dump(MyDataOrderedRefArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataOrderedRefArrayW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataOrderedRefArrayW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataOrderedRefArrayW_fdump(FILE *fp, MyDataOrderedRefArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataOrderedRefArrayW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataOrderedRefArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataArrayW
static Dz1Error MyDataArrayW_add(MyDataArrayW *p, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyDataEntryW *MyDataArrayW_extract(MyDataArrayW *p, MyDataEntryW *ptr)
{
	return (MyDataEntryW *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataArrayWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataArrayWMkArrArg;

static Dz1Error _MyDataArrayW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataArrayWMkArrArg *arg = (MyDataArrayWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataArrayW_get_array(MyDataArrayW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataArrayWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataArrayW_get_array, (void *)&arg);
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

static Dz1Error MyDataArrayW_travelForward(MyDataArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataArrayW_travelBackward(MyDataArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataArrayWFindArg
{
	MyDataEntryW *key;
	MyDataEntryW *ret;
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataArrayWFindArg;

static Dz1Error _MyDataArrayW_find(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataArrayWFindArg *arg = (MyDataArrayWFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntryW *MyDataArrayW_find(MyDataArrayW *p, MyDataEntryW *key)
{
	MyDataArrayWFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataArrayW_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntryW *MyDataArrayW_getHead(MyDataArrayW *p)
{
	return (MyDataEntryW *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntryW *MyDataArrayW_getTail(MyDataArrayW *p)
{
	return (MyDataEntryW *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataArrayW_count(MyDataArrayW *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataArrayW *MyDataArrayW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataArrayW *ret = (MyDataArrayW *)Dz1Calloc(sizeof(MyDataArrayW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataArrayW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyDataEntryW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataArrayW_count;
			ret->travel = MyDataArrayW_travelForward;
			ret->travelForward = MyDataArrayW_travelForward;
			ret->travelBackward = MyDataArrayW_travelBackward;
			ret->get_array = MyDataArrayW_get_array;
			ret->add = MyDataArrayW_add;
			ret->find = MyDataArrayW_find;
			ret->extract = MyDataArrayW_extract;
			ret->getHead = MyDataArrayW_getHead;
			ret->getTail = MyDataArrayW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataArrayW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataArrayW *p = (MyDataArrayW *)ptr;
	MyDataEntryW *cloned = MyDataEntryW_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataArrayW *MyDataArrayW_clone(MyDataArrayW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataArrayW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataArrayW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataArrayW_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataArrayW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataArrayW_purge(MyDataArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataArrayW_del(MyDataArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataArrayW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataArrayW_dump(MyDataArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataArrayW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataArrayW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataArrayW_fdump(FILE *fp, MyDataArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataArrayW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataRefArrayW
static Dz1Error MyDataRefArrayW_add(MyDataRefArrayW *p, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static MyDataEntryW *MyDataRefArrayW_extract(MyDataRefArrayW *p, MyDataEntryW *ptr)
{
	return (MyDataEntryW *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyDataRefArrayWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataRefArrayWMkArrArg;

static Dz1Error _MyDataRefArrayW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefArrayWMkArrArg *arg = (MyDataRefArrayWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataRefArrayW_get_array(MyDataRefArrayW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataRefArrayWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataRefArrayW_get_array, (void *)&arg);
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

static Dz1Error MyDataRefArrayW_travelForward(MyDataRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyDataRefArrayW_travelBackward(MyDataRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyDataRefArrayWFindArg
{
	MyDataEntryW *key;
	MyDataEntryW *ret;
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataRefArrayWFindArg;

static Dz1Error _MyDataRefArrayW_find(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyDataRefArrayWFindArg *arg = (MyDataRefArrayWFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyDataEntryW *MyDataRefArrayW_find(MyDataRefArrayW *p, MyDataEntryW *key)
{
	MyDataRefArrayWFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyDataRefArrayW_find, (void *)&arg);
	return arg.ret;
}

static MyDataEntryW *MyDataRefArrayW_getHead(MyDataRefArrayW *p)
{
	return (MyDataEntryW *)Dz1Fifo_getFirst(p->storage);
}

static MyDataEntryW *MyDataRefArrayW_getTail(MyDataRefArrayW *p)
{
	return (MyDataEntryW *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyDataRefArrayW_count(MyDataRefArrayW *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyDataRefArrayW *MyDataRefArrayW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefArrayW *ret = (MyDataRefArrayW *)Dz1Calloc(sizeof(MyDataRefArrayW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefArrayW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataRefArrayW_count;
			ret->travel = MyDataRefArrayW_travelForward;
			ret->travelForward = MyDataRefArrayW_travelForward;
			ret->travelBackward = MyDataRefArrayW_travelBackward;
			ret->get_array = MyDataRefArrayW_get_array;
			ret->add = MyDataRefArrayW_add;
			ret->find = MyDataRefArrayW_find;
			ret->extract = MyDataRefArrayW_extract;
			ret->getHead = MyDataRefArrayW_getHead;
			ret->getTail = MyDataRefArrayW_getTail;
			ret->cmp = MyDataEntryW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataRefArrayW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefArrayW *p = (MyDataRefArrayW *)ptr;
	MyDataEntryW *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataRefArrayW *MyDataRefArrayW_clone(MyDataRefArrayW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefArrayW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataRefArrayW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefArrayW_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyDataRefArrayW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefArrayW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataRefArrayW_purge(MyDataRefArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyDataRefArrayW_del(MyDataRefArrayW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataRefArrayW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataRefArrayW_dump(MyDataRefArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataRefArrayW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataRefArrayW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataRefArrayW_fdump(FILE *fp, MyDataRefArrayW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataRefArrayW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataRefArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataIndexW
static Dz1Error MyDataIndexW_add(MyDataIndexW *p, MyDataEntryW *data)
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

static bool_t MyDataIndexW_remove(MyDataIndexW *p, MyDataEntryW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryW *MyDataIndexW_extract(MyDataIndexW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataIndexWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataIndexWMkArrArg;

static Dz1Error _MyDataIndexW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataIndexWMkArrArg *arg = (MyDataIndexWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataIndexW_get_array(MyDataIndexW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataIndexWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataIndexW_get_array, (void *)&arg);
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

static Dz1Error MyDataIndexW_travelForward(MyDataIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataIndexW_travelBackward(MyDataIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataIndexW_find(MyDataIndexW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyDataIndexW_count(MyDataIndexW *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _MyDataIndexW_cmp(MyDataEntryW *a, MyDataEntryW *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}

MyDataIndexW *MyDataIndexW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataIndexW *ret = (MyDataIndexW *)Dz1Calloc(sizeof(MyDataIndexW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataIndexW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_MyDataIndexW_cmp, (Dz1DelFunc)MyDataEntryW_del, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataIndexW_count;
			ret->travel = MyDataIndexW_travelForward;
			ret->travelForward = MyDataIndexW_travelForward;
			ret->travelBackward = MyDataIndexW_travelBackward;
			ret->get_array = MyDataIndexW_get_array;
			ret->add = MyDataIndexW_add;
			ret->remove = MyDataIndexW_remove;
			ret->find = MyDataIndexW_find;
			ret->extract = MyDataIndexW_extract;
			ret->cmp = _MyDataIndexW_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataIndexW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataIndexW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataIndexW *p = (MyDataIndexW *)ptr;
	MyDataEntryW *cloned = MyDataEntryW_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataIndexW *MyDataIndexW_clone(MyDataIndexW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataIndexW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataIndexW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataIndexW_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataIndexW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataIndexW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataIndexW_purge(MyDataIndexW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataIndexW_del(MyDataIndexW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataIndexW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataIndexW_dump(MyDataIndexW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataIndexW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataIndexW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataIndexW_fdump(FILE *fp, MyDataIndexW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataIndexW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataIndexW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataRefIndexW
static Dz1Error MyDataRefIndexW_add(MyDataRefIndexW *p, MyDataEntryW *data)
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

static bool_t MyDataRefIndexW_remove(MyDataRefIndexW *p, MyDataEntryW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyDataEntryW *MyDataRefIndexW_extract(MyDataRefIndexW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyDataRefIndexWMkArrArg
{
	MyDataEntryW **arr;
	unsigned int idx;
} MyDataRefIndexWMkArrArg;

static Dz1Error _MyDataRefIndexW_get_array(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefIndexWMkArrArg *arg = (MyDataRefIndexWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyDataEntryW **MyDataRefIndexW_get_array(MyDataRefIndexW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyDataEntryW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyDataEntryW **)Dz1Calloc(sizeof(MyDataEntryW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyDataRefIndexWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyDataRefIndexW_get_array, (void *)&arg);
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

static Dz1Error MyDataRefIndexW_travelForward(MyDataRefIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyDataRefIndexW_travelBackward(MyDataRefIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyDataEntryW *MyDataRefIndexW_find(MyDataRefIndexW *p, MyDataEntryW *key)
{
	return (MyDataEntryW *)Dz1AATree_find(p->storage, key);
}

static unsigned int MyDataRefIndexW_count(MyDataRefIndexW *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _MyDataRefIndexW_cmp(MyDataEntryW *a, MyDataEntryW *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->val, &b->val)) != 0) { }
	return ret;
}

MyDataRefIndexW *MyDataRefIndexW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefIndexW *ret = (MyDataRefIndexW *)Dz1Calloc(sizeof(MyDataRefIndexW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefIndexW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_MyDataRefIndexW_cmp, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyDataRefIndexW_count;
			ret->travel = MyDataRefIndexW_travelForward;
			ret->travelForward = MyDataRefIndexW_travelForward;
			ret->travelBackward = MyDataRefIndexW_travelBackward;
			ret->get_array = MyDataRefIndexW_get_array;
			ret->add = MyDataRefIndexW_add;
			ret->remove = MyDataRefIndexW_remove;
			ret->find = MyDataRefIndexW_find;
			ret->extract = MyDataRefIndexW_extract;
			ret->cmp = _MyDataRefIndexW_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefIndexW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyDataRefIndexW_clone(void *ptr, MyDataEntryW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyDataRefIndexW *p = (MyDataRefIndexW *)ptr;
	MyDataEntryW *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyDataRefIndexW *MyDataRefIndexW_clone(MyDataRefIndexW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyDataRefIndexW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyDataRefIndexW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyDataRefIndexW_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyDataRefIndexW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyDataRefIndexW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyDataRefIndexW_purge(MyDataRefIndexW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyDataRefIndexW_del(MyDataRefIndexW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyDataRefIndexW_dump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyDataEntryW_dump(p, tab);
	return err;
}

void MyDataRefIndexW_dump(MyDataRefIndexW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyDataRefIndexW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyDataRefIndexW_fdump(void *ptr, MyDataEntryW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyDataEntryW_fdump(arg->fp, p, tab);
	return err;
}

void MyDataRefIndexW_fdump(FILE *fp, MyDataRefIndexW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyDataRefIndexW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyDataRefIndexW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// ArrayMemberTypeW
// void ArrayMemberTypeW_obj_ptr_arr_del(MyDataEntryW **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberTypeW, MyDataEntryW*, obj_ptr_arr, u32_t, MyDataEntryW_del)
// void ArrayMemberTypeW_obj_ptr_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberTypeW, MyDataEntryW*, obj_ptr_arr, u32_t)
// MyDataEntryW **ArrayMemberTypeW_obj_ptr_arr_clone(MyDataEntryW **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberTypeW, MyDataEntryW*, obj_ptr_arr, u32_t, MyDataEntryW_clone)
// void ArrayMemberTypeW_obj_ptr_arrW_dump(MyDataEntryW **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberTypeW, MyDataEntryW*, obj_ptr_arr, u32_t, " = ", MyDataEntryW_dump)
// void ArrayMemberTypeW_obj_ptr_arrW_fdump(FILE *fp, MyDataEntryW **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberTypeW, MyDataEntryW*, obj_ptr_arr, u32_t, " = ", MyDataEntryW_fdump)

// void ArrayMemberTypeW_obj_arr_del(MyDataEntryW *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(ArrayMemberTypeW, MyDataEntryW, obj_arr, u32_t, MyDataEntryW_purge)
// void ArrayMemberTypeW_obj_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(ArrayMemberTypeW, MyDataEntryW, obj_arr, u32_t)
// MyDataEntryW *ArrayMemberTypeW_obj_arr_clone(MyDataEntryW *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(ArrayMemberTypeW, MyDataEntryW, obj_arr, u32_t, MyDataEntryW_copy)
// void ArrayMemberTypeW_obj_arrW_dump(MyDataEntryW *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(ArrayMemberTypeW, MyDataEntryW, obj_arr, u32_t, " = ", MyDataEntryW_dump)
// void ArrayMemberTypeW_obj_arrW_fdump(FILE *fp, MyDataEntryW *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(ArrayMemberTypeW, MyDataEntryW, obj_arr, u32_t, " = ", MyDataEntryW_fdump)

// void ArrayMemberTypeW_prims_arr_del(u64_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(ArrayMemberTypeW, u64_t, prims_arr, u32_t)
// void ArrayMemberTypeW_prims_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(ArrayMemberTypeW, u64_t, prims_arr)
// u64_t *ArrayMemberTypeW_prims_arr_clone(u64_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(ArrayMemberTypeW, u64_t, prims_arr, u32_t)
// void ArrayMemberTypeW_prims_arrW_dump(u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_dump(ArrayMemberTypeW, u64_t, prims_arr, u32_t, " = ", Dz1u64W_dump)
// void ArrayMemberTypeW_prims_arrW_fdump(FILE *fp, u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_fdump(ArrayMemberTypeW, u64_t, prims_arr, u32_t, " = ", Dz1u64W_fdump)

// void ArrayMemberTypeW_primptrs_arr_del(u64_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberTypeW, u64_t*, primptrs_arr, u32_t, Dz1u64_del)
// void ArrayMemberTypeW_primptrs_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberTypeW, u64_t*, primptrs_arr, u32_t)
// u64_t **ArrayMemberTypeW_primptrs_arr_clone(u64_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberTypeW, u64_t*, primptrs_arr, u32_t, Dz1u64_clone)
// void ArrayMemberTypeW_primptrs_arrW_dump(u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberTypeW, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64W_dump)
// void ArrayMemberTypeW_primptrs_arrW_fdump(FILE *fp, u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberTypeW, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64W_fdump)

// void ArrayMemberTypeW_str_arr_del(wstr_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(ArrayMemberTypeW, wstr_t, str_arr, u32_t, dz1_built_in_wstr_del)
// void ArrayMemberTypeW_str_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(ArrayMemberTypeW, wstr_t, str_arr, u32_t)
// wstr_t *ArrayMemberTypeW_str_arr_clone(wstr_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(ArrayMemberTypeW, wstr_t, str_arr, u32_t, dz1_built_in_wstr_clone)
// void ArrayMemberTypeW_str_arrW_dump(wstr_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(ArrayMemberTypeW, wstr_t, str_arr, u32_t, " = ", dz1_built_in_wstrW_dump)
// void ArrayMemberTypeW_str_arrW_fdump(FILE *fp, wstr_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(ArrayMemberTypeW, wstr_t, str_arr, u32_t, " = ", dz1_built_in_wstrW_fdump)

ArrayMemberTypeW *ArrayMemberTypeW_new(MyDataEntryW **obj_ptr_arr/*_e_clone*/, 
									   u32_t obj_ptr_cnt, 
									   MyDataEntryW *obj_arr/*_e_copy*/, 
									   u32_t obj_cnt, 
									   u64_t *prims_arr/*_e_copy*/, 
									   u32_t prims_cnt, 
									   u64_t **primptrs_arr/*_e_clone*/, 
									   u32_t primptrs_cnt, 
									   wstr_t *str_arr/*_e_clone*/, 
									   u32_t str_cnt, 
									   s32_t *i_val/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ArrayMemberTypeW *__internal_ret = (ArrayMemberTypeW *)Dz1Calloc(sizeof(ArrayMemberTypeW), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ArrayMemberTypeW_delAndSetNull, (void *)&__internal_ret);
		
		if (obj_ptr_arr != NULL && (__internal_ret->obj_ptr_arr = ArrayMemberTypeW_obj_ptr_arr_clone(obj_ptr_arr, obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (obj_arr != NULL && (__internal_ret->obj_arr = ArrayMemberTypeW_obj_arr_clone(obj_arr, obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (prims_arr != NULL && (__internal_ret->prims_arr = ArrayMemberTypeW_prims_arr_clone(prims_arr, prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (primptrs_arr != NULL && (__internal_ret->primptrs_arr = ArrayMemberTypeW_primptrs_arr_clone(primptrs_arr, primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (str_arr != NULL && (__internal_ret->str_arr = ArrayMemberTypeW_str_arr_clone(str_arr, str_cnt, errp)) == NULL) { ERR_OUT(errp); }
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
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberTypeW_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ArrayMemberTypeW_copy(ArrayMemberTypeW *dst, ArrayMemberTypeW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->obj_ptr_arr != NULL && (dst->obj_ptr_arr = ArrayMemberTypeW_obj_ptr_arr_clone(src->obj_ptr_arr, src->obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->obj_arr != NULL && (dst->obj_arr = ArrayMemberTypeW_obj_arr_clone(src->obj_arr, src->obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->prims_arr != NULL && (dst->prims_arr = ArrayMemberTypeW_prims_arr_clone(src->prims_arr, src->prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->primptrs_arr != NULL && (dst->primptrs_arr = ArrayMemberTypeW_primptrs_arr_clone(src->primptrs_arr, src->primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->str_arr != NULL && (dst->str_arr = ArrayMemberTypeW_str_arr_clone(src->str_arr, src->str_cnt, errp)) == NULL) { ERR_OUT(errp); }
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

ArrayMemberTypeW *ArrayMemberTypeW_clone(ArrayMemberTypeW *src, Dz1Error *err)
{
	ArrayMemberTypeW *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ArrayMemberTypeW *)Dz1Calloc(sizeof(ArrayMemberTypeW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ArrayMemberTypeW_delAndSetNull, (void *)&dst);
		if (ArrayMemberTypeW_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ArrayMemberTypeW_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ArrayMemberTypeW_purge(ArrayMemberTypeW *p)
{
	if (p == NULL) return;
	ArrayMemberTypeW_obj_ptr_arr_del(p->obj_ptr_arr, p->obj_ptr_cnt);
	ArrayMemberTypeW_obj_arr_del(p->obj_arr, p->obj_cnt);
	ArrayMemberTypeW_prims_arr_del(p->prims_arr, p->prims_cnt);
	ArrayMemberTypeW_primptrs_arr_del(p->primptrs_arr, p->primptrs_cnt);
	ArrayMemberTypeW_str_arr_del(p->str_arr, p->str_cnt);
}

void ArrayMemberTypeW_del(ArrayMemberTypeW *p)
{
	if (p == NULL) return;
	ArrayMemberTypeW_purge(p);
	Dz1Free(p);
}

void ArrayMemberTypeW_dump(ArrayMemberTypeW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"obj_ptr_arr = "); ArrayMemberTypeW_obj_ptr_arrW_dump(p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"obj_ptr_cnt = "); Dz1u32_dump(&p->obj_ptr_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"obj_arr = "); ArrayMemberTypeW_obj_arrW_dump(p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"obj_cnt = "); Dz1u32_dump(&p->obj_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"prims_arr = "); ArrayMemberTypeW_prims_arrW_dump(p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"prims_cnt = "); Dz1u32_dump(&p->prims_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"primptrs_arr = "); ArrayMemberTypeW_primptrs_arrW_dump(p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"primptrs_cnt = "); Dz1u32_dump(&p->primptrs_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"str_arr = "); ArrayMemberTypeW_str_arrW_dump(p->str_arr, p->str_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"str_cnt = "); Dz1u32_dump(&p->str_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"i_val = "); Dz1s32_dump(p->i_val, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void ArrayMemberTypeW_fdump(FILE *fp, ArrayMemberTypeW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintf(fp, tab, L"obj_ptr_arr = "); ArrayMemberTypeW_obj_ptr_arrW_fdump(fp, p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"obj_ptr_cnt = "); Dz1u32_fdump(fp, &p->obj_ptr_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"obj_arr = "); ArrayMemberTypeW_obj_arrW_fdump(fp, p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"obj_cnt = "); Dz1u32_fdump(fp, &p->obj_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"prims_arr = "); ArrayMemberTypeW_prims_arrW_fdump(fp, p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"prims_cnt = "); Dz1u32_fdump(fp, &p->prims_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"primptrs_arr = "); ArrayMemberTypeW_primptrs_arrW_fdump(fp, p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"primptrs_cnt = "); Dz1u32_fdump(fp, &p->primptrs_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"str_arr = "); ArrayMemberTypeW_str_arrW_fdump(fp, p->str_arr, p->str_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"str_cnt = "); Dz1u32_fdump(fp, &p->str_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"i_val = "); Dz1s32_fdump(fp, p->i_val, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// ArrayMemberTypeW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

