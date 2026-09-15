////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_unionA_test.h"

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataAPresent
static struct MyUnionDataAPresentMapA
{
	str_t str;
	MyUnionDataAPresent v;
} MyUnionDataAPresentMapA[] =
{
	{ (char *)"name", MyUnionDataAPresent_name },
	{ (char *)"val", MyUnionDataAPresent_val },
	{ NULL, MyUnionDataAPresent_max }
};

str_t MyUnionDataAPresentStrA(MyUnionDataAPresent v)
{
	struct MyUnionDataAPresentMapA *i = NULL;
	for (i = MyUnionDataAPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionDataAPresent MyUnionDataAPresentFromStrA(str_t str)
{
	struct MyUnionDataAPresentMapA *i = NULL;
	for (i = MyUnionDataAPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return MyUnionDataAPresent_max;
}
#ifndef UNIX_SYSTEM
static struct MyUnionDataAPresentMapW
{
	wstr_t str;
	MyUnionDataAPresent v;
} MyUnionDataAPresentMapW[] =
{
	{ (wchar_t *)L"name", MyUnionDataAPresent_name },
	{ (wchar_t *)L"val", MyUnionDataAPresent_val },
	{ NULL, MyUnionDataAPresent_max }
};

wstr_t MyUnionDataAPresentStrW(MyUnionDataAPresent v)
{
	struct MyUnionDataAPresentMapW *i = NULL;
	for (i = MyUnionDataAPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionDataAPresent MyUnionDataAPresentFromStrW(wstr_t str)
{
	struct MyUnionDataAPresentMapW *i = NULL;
	for (i = MyUnionDataAPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return MyUnionDataAPresent_max;
}
#endif // UNIX_SYSTEM

MyUnionDataAPresent *MyUnionDataAPresent_new(MyUnionDataAPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataAPresent *__internal_ret = (MyUnionDataAPresent *)Dz1Calloc(sizeof(MyUnionDataAPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void MyUnionDataAPresent_dump(MyUnionDataAPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), MyUnionDataAPresentStr(*v));
}
void MyUnionDataAPresent_fdump(FILE *fp, MyUnionDataAPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), MyUnionDataAPresentStr(*v));
}

int MyUnionDataAPresent_cmp(MyUnionDataAPresent *a, MyUnionDataAPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// MyUnionDataAPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataA
MyUnionDataA *MyUnionDataA_new(MyUnionDataAPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataA *ret = (MyUnionDataA *)Dz1Calloc(sizeof(MyUnionDataA), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnionDataA_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case MyUnionDataAPresent_name:
			// _U_imp_clone
			if (ptr != NULL) ret->x.name = (Dz1Asn1UTF8Str *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionDataAPresent_val:
			// _U_prim_clone
			if (ptr != NULL) ret->x.val = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionDataAPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t MyUnionDataA_copy(MyUnionDataA *ret, MyUnionDataA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case MyUnionDataAPresent_name:
			// _U_imp_clone
			if (src->x.name && (ret->x.name = Dz1Asn1UTF8Str_clone(src->x.name, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyUnionDataAPresent_val:
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

MyUnionDataA *MyUnionDataA_clone(MyUnionDataA *src, Dz1Error *err)
{
	MyUnionDataA *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (MyUnionDataA *)Dz1Calloc(sizeof(MyUnionDataA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnionDataA_delAndSetNull, (void *)&ret);
		if (MyUnionDataA_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataA_purge(MyUnionDataA *p)
{
	if (!p) return;
	switch(p->present)
	{
	case MyUnionDataAPresent_name:
		Dz1Asn1UTF8Str_del(p->x.name);
		break;
	case MyUnionDataAPresent_val:
		break;
	default:
		break;
	}
}

void MyUnionDataA_del(MyUnionDataA *p)
{
	if (!p) return;
	MyUnionDataA_purge(p);
	Dz1Free(p);
}

void MyUnionDataA_dump(MyUnionDataA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case MyUnionDataAPresent_name:
		Dz1Thread_printf(Dz1T("name = ")); Dz1Asn1UTF8Str_dump(p->x.name, tab); 
		break;
	case MyUnionDataAPresent_val:
		Dz1Thread_printf(Dz1T("val = ")); Dz1u32_dump(&p->x.val, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}
void MyUnionDataA_fdump(FILE *fp, MyUnionDataA *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else switch(p->present)
	{
	case MyUnionDataAPresent_name:
		Dz1Thread_fprintf(fp, Dz1T("name = ")); Dz1Asn1UTF8Str_fdump(fp, p->x.name, tab); 
		break;
	case MyUnionDataAPresent_val:
		Dz1Thread_fprintf(fp, Dz1T("val = ")); Dz1u32_fdump(fp, &p->x.val, tab); 
		break;
	default:
		Dz1Thread_ftprintf(fp, tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int MyUnionDataA_cmp(MyUnionDataA *a, MyUnionDataA *b)
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
		case MyUnionDataAPresent_name:
			if (a->x.name == NULL && b->x.name == NULL) ret = 0;
			else if (a->x.name == NULL /*&& b->x.name != NULL*/) ret = -1;
			else if (/*a->x.name != NULL &&*/ b->x.name == NULL) ret = 1;
			else if ((ret = Dz1Asn1UTF8Str_cmp(a->x.name, b->x.name)) != 0) { }
			break;
		case MyUnionDataAPresent_val:
			if ((ret = Dz1u32_cmp(&a->x.val, &b->x.val)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// MyUnionDataA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueListA
static Dz1Error MyUnionDataUniqueListA_add(MyUnionDataUniqueListA *p, MyUnionDataA *data)
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

static bool_t MyUnionDataUniqueListA_remove(MyUnionDataUniqueListA *p, MyUnionDataA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyUnionDataA *MyUnionDataUniqueListA_extract(MyUnionDataUniqueListA *p, MyUnionDataA *key)
{
	return (MyUnionDataA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyUnionDataUniqueListAMkArrArg
{
	MyUnionDataA **arr;
	unsigned int idx;
} MyUnionDataUniqueListAMkArrArg;

static Dz1Error _MyUnionDataUniqueListA_get_array(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueListAMkArrArg *arg = (MyUnionDataUniqueListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataA **MyUnionDataUniqueListA_get_array(MyUnionDataUniqueListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataA **)Dz1Calloc(sizeof(MyUnionDataA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataUniqueListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataUniqueListA_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataUniqueListA_travelForward(MyUnionDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataUniqueListA_travelBackward(MyUnionDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionDataA *MyUnionDataUniqueListA_find(MyUnionDataUniqueListA *p, MyUnionDataA *key)
{
	return (MyUnionDataA *)Dz1AATree_find(p->storage, key);
}

static MyUnionDataA *MyUnionDataUniqueListA_getHead(MyUnionDataUniqueListA *p)
{
	return (MyUnionDataA *)Dz1AATree_getHead(p->storage);
}

static MyUnionDataA *MyUnionDataUniqueListA_getTail(MyUnionDataUniqueListA *p)
{
	return (MyUnionDataA *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyUnionDataUniqueListA_count(MyUnionDataUniqueListA *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyUnionDataUniqueListA *MyUnionDataUniqueListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueListA *ret = (MyUnionDataUniqueListA *)Dz1Calloc(sizeof(MyUnionDataUniqueListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyUnionDataA_cmp,
				(Dz1DelFunc)MyUnionDataA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataUniqueListA_count;
			ret->travel = MyUnionDataUniqueListA_travelForward;
			ret->travelForward = MyUnionDataUniqueListA_travelForward;
			ret->travelBackward = MyUnionDataUniqueListA_travelBackward;
			ret->get_array = MyUnionDataUniqueListA_get_array;
			ret->add = MyUnionDataUniqueListA_add;
			ret->remove = MyUnionDataUniqueListA_remove;
			ret->find = MyUnionDataUniqueListA_find;
			ret->extract = MyUnionDataUniqueListA_extract;
			ret->getHead = MyUnionDataUniqueListA_getHead;
			ret->getTail = MyUnionDataUniqueListA_getTail;
			ret->cmp = MyUnionDataA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataUniqueListA_clone(void *ptr, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueListA *p = (MyUnionDataUniqueListA *)ptr;
	MyUnionDataA *cloned = MyUnionDataA_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataUniqueListA *MyUnionDataUniqueListA_clone(MyUnionDataUniqueListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataUniqueListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueListA_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataUniqueListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataUniqueListA_purge(MyUnionDataUniqueListA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyUnionDataUniqueListA_del(MyUnionDataUniqueListA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataUniqueListA_dump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionDataA_dump(p, tab);
	return err;
}

void MyUnionDataUniqueListA_dump(MyUnionDataUniqueListA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataUniqueListA_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataUniqueListA_fdump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataUniqueListA_fdump(FILE *fp, MyUnionDataUniqueListA *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataUniqueListA_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataUniqueListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedListA
static Dz1Error MyUnionDataOrderedListA_add(MyUnionDataOrderedListA *p, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataOrderedListA_remove(MyUnionDataOrderedListA *p, MyUnionDataA *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyUnionDataA *MyUnionDataOrderedListA_extract(MyUnionDataOrderedListA *p, MyUnionDataA *key)
{
	return (MyUnionDataA *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyUnionDataOrderedListAMkArrArg
{
	MyUnionDataA **arr;
	unsigned int idx;
} MyUnionDataOrderedListAMkArrArg;

static Dz1Error _MyUnionDataOrderedListA_get_array(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedListAMkArrArg *arg = (MyUnionDataOrderedListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataA **MyUnionDataOrderedListA_get_array(MyUnionDataOrderedListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataA **)Dz1Calloc(sizeof(MyUnionDataA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataOrderedListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataOrderedListA_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataOrderedListA_travelForward(MyUnionDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataOrderedListA_travelBackward(MyUnionDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionDataA *MyUnionDataOrderedListA_find(MyUnionDataOrderedListA *p, MyUnionDataA *key)
{
	return (MyUnionDataA *)Dz1OrderedFifo_find(p->storage, key);
}

static MyUnionDataA *MyUnionDataOrderedListA_getHead(MyUnionDataOrderedListA *p)
{
	return (MyUnionDataA *)Dz1OrderedFifo_getHead(p->storage);
}

static MyUnionDataA *MyUnionDataOrderedListA_getTail(MyUnionDataOrderedListA *p)
{
	return (MyUnionDataA *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyUnionDataOrderedListA_count(MyUnionDataOrderedListA *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyUnionDataOrderedListA *MyUnionDataOrderedListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedListA *ret = (MyUnionDataOrderedListA *)Dz1Calloc(sizeof(MyUnionDataOrderedListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyUnionDataA_cmp,
				(Dz1DelFunc)MyUnionDataA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataOrderedListA_count;
			ret->travel = MyUnionDataOrderedListA_travelForward;
			ret->travelForward = MyUnionDataOrderedListA_travelForward;
			ret->travelBackward = MyUnionDataOrderedListA_travelBackward;
			ret->get_array = MyUnionDataOrderedListA_get_array;
			ret->add = MyUnionDataOrderedListA_add;
			ret->remove = MyUnionDataOrderedListA_remove;
			ret->find = MyUnionDataOrderedListA_find;
			ret->extract = MyUnionDataOrderedListA_extract;
			ret->getHead = MyUnionDataOrderedListA_getHead;
			ret->getTail = MyUnionDataOrderedListA_getTail;
			ret->cmp = MyUnionDataA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataOrderedListA_clone(void *ptr, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedListA *p = (MyUnionDataOrderedListA *)ptr;
	MyUnionDataA *cloned = MyUnionDataA_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataOrderedListA *MyUnionDataOrderedListA_clone(MyUnionDataOrderedListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataOrderedListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedListA_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataOrderedListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataOrderedListA_purge(MyUnionDataOrderedListA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyUnionDataOrderedListA_del(MyUnionDataOrderedListA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataOrderedListA_dump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionDataA_dump(p, tab);
	return err;
}

void MyUnionDataOrderedListA_dump(MyUnionDataOrderedListA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataOrderedListA_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataOrderedListA_fdump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataOrderedListA_fdump(FILE *fp, MyUnionDataOrderedListA *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataOrderedListA_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataOrderedListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataListA
static Dz1Error MyUnionDataListA_add(MyUnionDataListA *p, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataListA_remove(MyUnionDataListA *p, MyUnionDataA *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyUnionDataA *MyUnionDataListA_extract(MyUnionDataListA *p, MyUnionDataA *ptr)
{
	return (MyUnionDataA *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyUnionDataListAMkArrArg
{
	MyUnionDataA **arr;
	unsigned int idx;
} MyUnionDataListAMkArrArg;

static Dz1Error _MyUnionDataListA_get_array(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataListAMkArrArg *arg = (MyUnionDataListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataA **MyUnionDataListA_get_array(MyUnionDataListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataA **)Dz1Calloc(sizeof(MyUnionDataA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataListA_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataListA_travelForward(MyUnionDataListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataListA_travelBackward(MyUnionDataListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyUnionDataListAFindArg
{
	MyUnionDataA *key;
	MyUnionDataA *ret;
	int (*cmp)(MyUnionDataA *a, MyUnionDataA *b);
} MyUnionDataListAFindArg;

static Dz1Error _MyUnionDataListA_find(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyUnionDataListAFindArg *arg = (MyUnionDataListAFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyUnionDataA *MyUnionDataListA_find(MyUnionDataListA *p, MyUnionDataA *key)
{
	MyUnionDataListAFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyUnionDataListA_find, (void *)&arg);
	return arg.ret;
}

static MyUnionDataA *MyUnionDataListA_getHead(MyUnionDataListA *p)
{
	return (MyUnionDataA *)Dz1Fifo_getFirst(p->storage);
}

static MyUnionDataA *MyUnionDataListA_getTail(MyUnionDataListA *p)
{
	return (MyUnionDataA *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyUnionDataListA_count(MyUnionDataListA *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionDataListA *MyUnionDataListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataListA *ret = (MyUnionDataListA *)Dz1Calloc(sizeof(MyUnionDataListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyUnionDataA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataListA_count;
			ret->travel = MyUnionDataListA_travelForward;
			ret->travelForward = MyUnionDataListA_travelForward;
			ret->travelBackward = MyUnionDataListA_travelBackward;
			ret->get_array = MyUnionDataListA_get_array;
			ret->add = MyUnionDataListA_add;
			ret->remove = MyUnionDataListA_remove;
			ret->find = MyUnionDataListA_find;
			ret->extract = MyUnionDataListA_extract;
			ret->getHead = MyUnionDataListA_getHead;
			ret->getTail = MyUnionDataListA_getTail;
			ret->cmp = MyUnionDataA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataListA_clone(void *ptr, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataListA *p = (MyUnionDataListA *)ptr;
	MyUnionDataA *cloned = MyUnionDataA_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataListA *MyUnionDataListA_clone(MyUnionDataListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataListA_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionDataListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataListA_purge(MyUnionDataListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionDataListA_del(MyUnionDataListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataListA_dump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionDataA_dump(p, tab);
	return err;
}

void MyUnionDataListA_dump(MyUnionDataListA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataListA_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataListA_fdump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataListA_fdump(FILE *fp, MyUnionDataListA *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataListA_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueRefListA
static Dz1Error MyUnionDataUniqueRefListA_add(MyUnionDataUniqueRefListA *p, MyUnionDataA *data)
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

static bool_t MyUnionDataUniqueRefListA_remove(MyUnionDataUniqueRefListA *p, MyUnionDataA *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyUnionDataA *MyUnionDataUniqueRefListA_extract(MyUnionDataUniqueRefListA *p, MyUnionDataA *key)
{
	return (MyUnionDataA *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyUnionDataUniqueRefListAMkArrArg
{
	MyUnionDataA **arr;
	unsigned int idx;
} MyUnionDataUniqueRefListAMkArrArg;

static Dz1Error _MyUnionDataUniqueRefListA_get_array(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueRefListAMkArrArg *arg = (MyUnionDataUniqueRefListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataA **MyUnionDataUniqueRefListA_get_array(MyUnionDataUniqueRefListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataA **)Dz1Calloc(sizeof(MyUnionDataA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataUniqueRefListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataUniqueRefListA_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataUniqueRefListA_travelForward(MyUnionDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataUniqueRefListA_travelBackward(MyUnionDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionDataA *MyUnionDataUniqueRefListA_find(MyUnionDataUniqueRefListA *p, MyUnionDataA *key)
{
	return (MyUnionDataA *)Dz1AATree_find(p->storage, key);
}

static MyUnionDataA *MyUnionDataUniqueRefListA_getHead(MyUnionDataUniqueRefListA *p)
{
	return (MyUnionDataA *)Dz1AATree_getHead(p->storage);
}

static MyUnionDataA *MyUnionDataUniqueRefListA_getTail(MyUnionDataUniqueRefListA *p)
{
	return (MyUnionDataA *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyUnionDataUniqueRefListA_count(MyUnionDataUniqueRefListA *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyUnionDataUniqueRefListA *MyUnionDataUniqueRefListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueRefListA *ret = (MyUnionDataUniqueRefListA *)Dz1Calloc(sizeof(MyUnionDataUniqueRefListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueRefListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyUnionDataA_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataUniqueRefListA_count;
			ret->travel = MyUnionDataUniqueRefListA_travelForward;
			ret->travelForward = MyUnionDataUniqueRefListA_travelForward;
			ret->travelBackward = MyUnionDataUniqueRefListA_travelBackward;
			ret->get_array = MyUnionDataUniqueRefListA_get_array;
			ret->add = MyUnionDataUniqueRefListA_add;
			ret->remove = MyUnionDataUniqueRefListA_remove;
			ret->find = MyUnionDataUniqueRefListA_find;
			ret->extract = MyUnionDataUniqueRefListA_extract;
			ret->getHead = MyUnionDataUniqueRefListA_getHead;
			ret->getTail = MyUnionDataUniqueRefListA_getTail;
			ret->cmp = MyUnionDataA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataUniqueRefListA_clone(void *ptr, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueRefListA *p = (MyUnionDataUniqueRefListA *)ptr;
	MyUnionDataA *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataUniqueRefListA *MyUnionDataUniqueRefListA_clone(MyUnionDataUniqueRefListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueRefListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataUniqueRefListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueRefListA_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataUniqueRefListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataUniqueRefListA_purge(MyUnionDataUniqueRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyUnionDataUniqueRefListA_del(MyUnionDataUniqueRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataUniqueRefListA_dump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionDataA_dump(p, tab);
	return err;
}

void MyUnionDataUniqueRefListA_dump(MyUnionDataUniqueRefListA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataUniqueRefListA_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataUniqueRefListA_fdump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataUniqueRefListA_fdump(FILE *fp, MyUnionDataUniqueRefListA *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataUniqueRefListA_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataUniqueRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedRefListA
static Dz1Error MyUnionDataOrderedRefListA_add(MyUnionDataOrderedRefListA *p, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataOrderedRefListA_remove(MyUnionDataOrderedRefListA *p, MyUnionDataA *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyUnionDataA *MyUnionDataOrderedRefListA_extract(MyUnionDataOrderedRefListA *p, MyUnionDataA *key)
{
	return (MyUnionDataA *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyUnionDataOrderedRefListAMkArrArg
{
	MyUnionDataA **arr;
	unsigned int idx;
} MyUnionDataOrderedRefListAMkArrArg;

static Dz1Error _MyUnionDataOrderedRefListA_get_array(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedRefListAMkArrArg *arg = (MyUnionDataOrderedRefListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataA **MyUnionDataOrderedRefListA_get_array(MyUnionDataOrderedRefListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataA **)Dz1Calloc(sizeof(MyUnionDataA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataOrderedRefListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataOrderedRefListA_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataOrderedRefListA_travelForward(MyUnionDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataOrderedRefListA_travelBackward(MyUnionDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionDataA *MyUnionDataOrderedRefListA_find(MyUnionDataOrderedRefListA *p, MyUnionDataA *key)
{
	return (MyUnionDataA *)Dz1OrderedFifo_find(p->storage, key);
}

static MyUnionDataA *MyUnionDataOrderedRefListA_getHead(MyUnionDataOrderedRefListA *p)
{
	return (MyUnionDataA *)Dz1OrderedFifo_getHead(p->storage);
}

static MyUnionDataA *MyUnionDataOrderedRefListA_getTail(MyUnionDataOrderedRefListA *p)
{
	return (MyUnionDataA *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyUnionDataOrderedRefListA_count(MyUnionDataOrderedRefListA *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyUnionDataOrderedRefListA *MyUnionDataOrderedRefListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedRefListA *ret = (MyUnionDataOrderedRefListA *)Dz1Calloc(sizeof(MyUnionDataOrderedRefListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedRefListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyUnionDataA_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataOrderedRefListA_count;
			ret->travel = MyUnionDataOrderedRefListA_travelForward;
			ret->travelForward = MyUnionDataOrderedRefListA_travelForward;
			ret->travelBackward = MyUnionDataOrderedRefListA_travelBackward;
			ret->get_array = MyUnionDataOrderedRefListA_get_array;
			ret->add = MyUnionDataOrderedRefListA_add;
			ret->remove = MyUnionDataOrderedRefListA_remove;
			ret->find = MyUnionDataOrderedRefListA_find;
			ret->extract = MyUnionDataOrderedRefListA_extract;
			ret->getHead = MyUnionDataOrderedRefListA_getHead;
			ret->getTail = MyUnionDataOrderedRefListA_getTail;
			ret->cmp = MyUnionDataA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataOrderedRefListA_clone(void *ptr, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedRefListA *p = (MyUnionDataOrderedRefListA *)ptr;
	MyUnionDataA *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataOrderedRefListA *MyUnionDataOrderedRefListA_clone(MyUnionDataOrderedRefListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedRefListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataOrderedRefListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedRefListA_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataOrderedRefListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataOrderedRefListA_purge(MyUnionDataOrderedRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyUnionDataOrderedRefListA_del(MyUnionDataOrderedRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataOrderedRefListA_dump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionDataA_dump(p, tab);
	return err;
}

void MyUnionDataOrderedRefListA_dump(MyUnionDataOrderedRefListA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataOrderedRefListA_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataOrderedRefListA_fdump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataOrderedRefListA_fdump(FILE *fp, MyUnionDataOrderedRefListA *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataOrderedRefListA_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataOrderedRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataRefListA
static Dz1Error MyUnionDataRefListA_add(MyUnionDataRefListA *p, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataRefListA_remove(MyUnionDataRefListA *p, MyUnionDataA *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyUnionDataA *MyUnionDataRefListA_extract(MyUnionDataRefListA *p, MyUnionDataA *ptr)
{
	return (MyUnionDataA *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyUnionDataRefListAMkArrArg
{
	MyUnionDataA **arr;
	unsigned int idx;
} MyUnionDataRefListAMkArrArg;

static Dz1Error _MyUnionDataRefListA_get_array(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataRefListAMkArrArg *arg = (MyUnionDataRefListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataA **MyUnionDataRefListA_get_array(MyUnionDataRefListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataA **)Dz1Calloc(sizeof(MyUnionDataA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataRefListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataRefListA_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataRefListA_travelForward(MyUnionDataRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataRefListA_travelBackward(MyUnionDataRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyUnionDataRefListAFindArg
{
	MyUnionDataA *key;
	MyUnionDataA *ret;
	int (*cmp)(MyUnionDataA *a, MyUnionDataA *b);
} MyUnionDataRefListAFindArg;

static Dz1Error _MyUnionDataRefListA_find(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyUnionDataRefListAFindArg *arg = (MyUnionDataRefListAFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyUnionDataA *MyUnionDataRefListA_find(MyUnionDataRefListA *p, MyUnionDataA *key)
{
	MyUnionDataRefListAFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyUnionDataRefListA_find, (void *)&arg);
	return arg.ret;
}

static MyUnionDataA *MyUnionDataRefListA_getHead(MyUnionDataRefListA *p)
{
	return (MyUnionDataA *)Dz1Fifo_getFirst(p->storage);
}

static MyUnionDataA *MyUnionDataRefListA_getTail(MyUnionDataRefListA *p)
{
	return (MyUnionDataA *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyUnionDataRefListA_count(MyUnionDataRefListA *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionDataRefListA *MyUnionDataRefListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataRefListA *ret = (MyUnionDataRefListA *)Dz1Calloc(sizeof(MyUnionDataRefListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataRefListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataRefListA_count;
			ret->travel = MyUnionDataRefListA_travelForward;
			ret->travelForward = MyUnionDataRefListA_travelForward;
			ret->travelBackward = MyUnionDataRefListA_travelBackward;
			ret->get_array = MyUnionDataRefListA_get_array;
			ret->add = MyUnionDataRefListA_add;
			ret->remove = MyUnionDataRefListA_remove;
			ret->find = MyUnionDataRefListA_find;
			ret->extract = MyUnionDataRefListA_extract;
			ret->getHead = MyUnionDataRefListA_getHead;
			ret->getTail = MyUnionDataRefListA_getTail;
			ret->cmp = MyUnionDataA_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataRefListA_clone(void *ptr, MyUnionDataA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataRefListA *p = (MyUnionDataRefListA *)ptr;
	MyUnionDataA *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataRefListA *MyUnionDataRefListA_clone(MyUnionDataRefListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataRefListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataRefListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataRefListA_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionDataRefListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataRefListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataRefListA_purge(MyUnionDataRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionDataRefListA_del(MyUnionDataRefListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataRefListA_dump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnionDataA_dump(p, tab);
	return err;
}

void MyUnionDataRefListA_dump(MyUnionDataRefListA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataRefListA_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _MyUnionDataRefListA_fdump(void *ptr, MyUnionDataA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); MyUnionDataA_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataRefListA_fdump(FILE *fp, MyUnionDataRefListA *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionDataRefListA_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataInfoA
// void MyUnionDataInfoA_obj_ptr_arr_del(MyUnionDataA **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyUnionDataInfoA, MyUnionDataA*, obj_ptr_arr, u32_t, MyUnionDataA_del)
// void MyUnionDataInfoA_obj_ptr_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyUnionDataInfoA, MyUnionDataA*, obj_ptr_arr, u32_t)
// MyUnionDataA **MyUnionDataInfoA_obj_ptr_arr_clone(MyUnionDataA **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyUnionDataInfoA, MyUnionDataA*, obj_ptr_arr, u32_t, MyUnionDataA_clone)
// void MyUnionDataInfoA_obj_ptr_arr_dump(MyUnionDataA **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_dump(MyUnionDataInfoA, MyUnionDataA*, obj_ptr_arr, u32_t, ".", MyUnionDataA_dump)
// void MyUnionDataInfoA_obj_ptr_arr_fdump(FILE *fp, MyUnionDataA **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_fdump(MyUnionDataInfoA, MyUnionDataA*, obj_ptr_arr, u32_t, ".", MyUnionDataA_fdump)

// void MyUnionDataInfoA_obj_arr_del(MyUnionDataA *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(MyUnionDataInfoA, MyUnionDataA, obj_arr, u32_t, MyUnionDataA_purge)
// void MyUnionDataInfoA_obj_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(MyUnionDataInfoA, MyUnionDataA, obj_arr, u32_t)
// MyUnionDataA *MyUnionDataInfoA_obj_arr_clone(MyUnionDataA *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(MyUnionDataInfoA, MyUnionDataA, obj_arr, u32_t, MyUnionDataA_copy)
// void MyUnionDataInfoA_obj_arr_dump(MyUnionDataA *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_dump(MyUnionDataInfoA, MyUnionDataA, obj_arr, u32_t, ".", MyUnionDataA_dump)
// void MyUnionDataInfoA_obj_arr_fdump(FILE *fp, MyUnionDataA *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_construct_fdump(MyUnionDataInfoA, MyUnionDataA, obj_arr, u32_t, ".", MyUnionDataA_fdump)

// void MyUnionDataInfoA_prims_arr_del(u64_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(MyUnionDataInfoA, u64_t, prims_arr, u32_t)
// void MyUnionDataInfoA_prims_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(MyUnionDataInfoA, u64_t, prims_arr)
// u64_t *MyUnionDataInfoA_prims_arr_clone(u64_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(MyUnionDataInfoA, u64_t, prims_arr, u32_t)
// void MyUnionDataInfoA_prims_arr_dump(u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_dump(MyUnionDataInfoA, u64_t, prims_arr, u32_t, " = ", Dz1u64_dump)
// void MyUnionDataInfoA_prims_arr_fdump(FILE *fp, u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitive_fdump(MyUnionDataInfoA, u64_t, prims_arr, u32_t, " = ", Dz1u64_fdump)

// void MyUnionDataInfoA_primptrs_arr_del(u64_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyUnionDataInfoA, u64_t*, primptrs_arr, u32_t, Dz1u64_del)
// void MyUnionDataInfoA_primptrs_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyUnionDataInfoA, u64_t*, primptrs_arr, u32_t)
// u64_t **MyUnionDataInfoA_primptrs_arr_clone(u64_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyUnionDataInfoA, u64_t*, primptrs_arr, u32_t, Dz1u64_clone)
// void MyUnionDataInfoA_primptrs_arr_dump(u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_dump(MyUnionDataInfoA, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64_dump)
// void MyUnionDataInfoA_primptrs_arr_fdump(FILE *fp, u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptr_fdump(MyUnionDataInfoA, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64_fdump)

MyUnionDataInfoA *MyUnionDataInfoA_new(MyUnionDataA **obj_ptr_arr/*_e_clone*/, 
									   u32_t obj_ptr_cnt, 
									   MyUnionDataA *obj_arr/*_e_copy*/, 
									   u32_t obj_cnt, 
									   u64_t *prims_arr/*_e_copy*/, 
									   u32_t prims_cnt, 
									   u64_t **primptrs_arr/*_e_clone*/, 
									   u32_t primptrs_cnt, 
									   s32_t *i_val/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataInfoA *__internal_ret = (MyUnionDataInfoA *)Dz1Calloc(sizeof(MyUnionDataInfoA), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnionDataInfoA_delAndSetNull, (void *)&__internal_ret);
		
		if (obj_ptr_arr != NULL && (__internal_ret->obj_ptr_arr = MyUnionDataInfoA_obj_ptr_arr_clone(obj_ptr_arr, obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (obj_arr != NULL && (__internal_ret->obj_arr = MyUnionDataInfoA_obj_arr_clone(obj_arr, obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (prims_arr != NULL && (__internal_ret->prims_arr = MyUnionDataInfoA_prims_arr_clone(prims_arr, prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (primptrs_arr != NULL && (__internal_ret->primptrs_arr = MyUnionDataInfoA_primptrs_arr_clone(primptrs_arr, primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->obj_ptr_cnt = obj_ptr_cnt;
			__internal_ret->obj_cnt = obj_cnt;
			__internal_ret->prims_cnt = prims_cnt;
			__internal_ret->primptrs_cnt = primptrs_cnt;
			__internal_ret->i_val = i_val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataInfoA_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyUnionDataInfoA_copy(MyUnionDataInfoA *dst, MyUnionDataInfoA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->obj_ptr_arr != NULL && (dst->obj_ptr_arr = MyUnionDataInfoA_obj_ptr_arr_clone(src->obj_ptr_arr, src->obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->obj_arr != NULL && (dst->obj_arr = MyUnionDataInfoA_obj_arr_clone(src->obj_arr, src->obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->prims_arr != NULL && (dst->prims_arr = MyUnionDataInfoA_prims_arr_clone(src->prims_arr, src->prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->primptrs_arr != NULL && (dst->primptrs_arr = MyUnionDataInfoA_primptrs_arr_clone(src->primptrs_arr, src->primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
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

MyUnionDataInfoA *MyUnionDataInfoA_clone(MyUnionDataInfoA *src, Dz1Error *err)
{
	MyUnionDataInfoA *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyUnionDataInfoA *)Dz1Calloc(sizeof(MyUnionDataInfoA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnionDataInfoA_delAndSetNull, (void *)&dst);
		if (MyUnionDataInfoA_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataInfoA_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyUnionDataInfoA_purge(MyUnionDataInfoA *p)
{
	if (p == NULL) return;
	MyUnionDataInfoA_obj_ptr_arr_del(p->obj_ptr_arr, p->obj_ptr_cnt);
	MyUnionDataInfoA_obj_arr_del(p->obj_arr, p->obj_cnt);
	MyUnionDataInfoA_prims_arr_del(p->prims_arr, p->prims_cnt);
	MyUnionDataInfoA_primptrs_arr_del(p->primptrs_arr, p->primptrs_cnt);
}

void MyUnionDataInfoA_del(MyUnionDataInfoA *p)
{
	if (p == NULL) return;
	MyUnionDataInfoA_purge(p);
	Dz1Free(p);
}

void MyUnionDataInfoA_dump(MyUnionDataInfoA *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("obj_ptr_arr = ")); MyUnionDataInfoA_obj_ptr_arr_dump(p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("obj_ptr_cnt = ")); Dz1u32_dump(&p->obj_ptr_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("obj_arr = ")); MyUnionDataInfoA_obj_arr_dump(p->obj_arr, p->obj_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("obj_cnt = ")); Dz1u32_dump(&p->obj_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("prims_arr = ")); MyUnionDataInfoA_prims_arr_dump(p->prims_arr, p->prims_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("prims_cnt = ")); Dz1u32_dump(&p->prims_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("primptrs_arr = ")); MyUnionDataInfoA_primptrs_arr_dump(p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1Thread_tprintf(tab, Dz1T("primptrs_cnt = ")); Dz1u32_dump(&p->primptrs_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("i_val = ")); Dz1s32_dump(p->i_val, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void MyUnionDataInfoA_fdump(FILE *fp, MyUnionDataInfoA *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_ptr_arr = ")); MyUnionDataInfoA_obj_ptr_arr_fdump(fp, p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_ptr_cnt = ")); Dz1u32_fdump(fp, &p->obj_ptr_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_arr = ")); MyUnionDataInfoA_obj_arr_fdump(fp, p->obj_arr, p->obj_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("obj_cnt = ")); Dz1u32_fdump(fp, &p->obj_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("prims_arr = ")); MyUnionDataInfoA_prims_arr_fdump(fp, p->prims_arr, p->prims_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("prims_cnt = ")); Dz1u32_fdump(fp, &p->prims_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("primptrs_arr = ")); MyUnionDataInfoA_primptrs_arr_fdump(fp, p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("primptrs_cnt = ")); Dz1u32_fdump(fp, &p->primptrs_cnt, tab); 
		Dz1Thread_ftprintf(fp, tab, Dz1T("i_val = ")); Dz1s32_fdump(fp, p->i_val, tab); 
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// MyUnionDataInfoA
////////////////////////////////////////////////////////////////////////////////

