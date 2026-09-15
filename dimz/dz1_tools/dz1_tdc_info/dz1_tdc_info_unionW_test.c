////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdc_info_unionW_test.h"

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataWPresent
static struct MyUnionDataWPresentMapA
{
	str_t str;
	MyUnionDataWPresent v;
} MyUnionDataWPresentMapA[] =
{
	{ (char *)"name", MyUnionDataWPresent_name },
	{ (char *)"val", MyUnionDataWPresent_val },
	{ NULL, MyUnionDataWPresent_max }
};

str_t MyUnionDataWPresentStrA(MyUnionDataWPresent v)
{
	struct MyUnionDataWPresentMapA *i = NULL;
	for (i = MyUnionDataWPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionDataWPresent MyUnionDataWPresentFromStrA(str_t str)
{
	struct MyUnionDataWPresentMapA *i = NULL;
	for (i = MyUnionDataWPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return MyUnionDataWPresent_max;
}
static struct MyUnionDataWPresentMapW
{
	wstr_t str;
	MyUnionDataWPresent v;
} MyUnionDataWPresentMapW[] =
{
	{ (wchar_t *)L"name", MyUnionDataWPresent_name },
	{ (wchar_t *)L"val", MyUnionDataWPresent_val },
	{ NULL, MyUnionDataWPresent_max }
};

wstr_t MyUnionDataWPresentStrW(MyUnionDataWPresent v)
{
	struct MyUnionDataWPresentMapW *i = NULL;
	for (i = MyUnionDataWPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionDataWPresent MyUnionDataWPresentFromStrW(wstr_t str)
{
	struct MyUnionDataWPresentMapW *i = NULL;
	for (i = MyUnionDataWPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return MyUnionDataWPresent_max;
}

MyUnionDataWPresent *MyUnionDataWPresent_new(MyUnionDataWPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataWPresent *__internal_ret = (MyUnionDataWPresent *)Dz1Calloc(sizeof(MyUnionDataWPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void MyUnionDataWPresentW_dump(MyUnionDataWPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", MyUnionDataWPresentStrW(*v));
}
void MyUnionDataWPresentW_fdump(FILE *fp, MyUnionDataWPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", MyUnionDataWPresentStrW(*v));
}

int MyUnionDataWPresent_cmp(MyUnionDataWPresent *a, MyUnionDataWPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// MyUnionDataWPresent
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataW
MyUnionDataW *MyUnionDataW_new(MyUnionDataWPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataW *ret = (MyUnionDataW *)Dz1Calloc(sizeof(MyUnionDataW), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnionDataW_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case MyUnionDataWPresent_name:
			// _U_imp_clone
			if (ptr != NULL) ret->x.name = (Dz1Asn1UTF8Str *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionDataWPresent_val:
			// _U_prim_clone
			if (ptr != NULL) ret->x.val = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionDataWPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t MyUnionDataW_copy(MyUnionDataW *ret, MyUnionDataW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case MyUnionDataWPresent_name:
			// _U_imp_clone
			if (src->x.name && (ret->x.name = Dz1Asn1UTF8Str_clone(src->x.name, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyUnionDataWPresent_val:
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

MyUnionDataW *MyUnionDataW_clone(MyUnionDataW *src, Dz1Error *err)
{
	MyUnionDataW *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (MyUnionDataW *)Dz1Calloc(sizeof(MyUnionDataW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnionDataW_delAndSetNull, (void *)&ret);
		if (MyUnionDataW_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataW_purge(MyUnionDataW *p)
{
	if (!p) return;
	switch(p->present)
	{
	case MyUnionDataWPresent_name:
		Dz1Asn1UTF8Str_del(p->x.name);
		break;
	case MyUnionDataWPresent_val:
		break;
	default:
		break;
	}
}

void MyUnionDataW_del(MyUnionDataW *p)
{
	if (!p) return;
	MyUnionDataW_purge(p);
	Dz1Free(p);
}

void MyUnionDataW_dump(MyUnionDataW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case MyUnionDataWPresent_name:
		Dz1ThreadW_printf(L"name = "); Dz1Asn1UTF8Str_dump(p->x.name, tab); 
		break;
	case MyUnionDataWPresent_val:
		Dz1ThreadW_printf(L"val = "); Dz1u32_dump(&p->x.val, tab); 
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}
void MyUnionDataW_fdump(FILE *fp, MyUnionDataW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else switch(p->present)
	{
	case MyUnionDataWPresent_name:
		Dz1ThreadW_fprintf(fp, L"name = "); Dz1Asn1UTF8Str_fdump(fp, p->x.name, tab); 
		break;
	case MyUnionDataWPresent_val:
		Dz1ThreadW_fprintf(fp, L"val = "); Dz1u32_fdump(fp, &p->x.val, tab); 
		break;
	default:
		Dz1ThreadW_ftprintf(fp, tab, L"??? = %d\n", p->present);
		break;
	}
}

int MyUnionDataW_cmp(MyUnionDataW *a, MyUnionDataW *b)
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
		case MyUnionDataWPresent_name:
			if (a->x.name == NULL && b->x.name == NULL) ret = 0;
			else if (a->x.name == NULL /*&& b->x.name != NULL*/) ret = -1;
			else if (/*a->x.name != NULL &&*/ b->x.name == NULL) ret = 1;
			else if ((ret = Dz1Asn1UTF8Str_cmp(a->x.name, b->x.name)) != 0) { }
			break;
		case MyUnionDataWPresent_val:
			if ((ret = Dz1u32_cmp(&a->x.val, &b->x.val)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// MyUnionDataW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueListW
static Dz1Error MyUnionDataUniqueListW_add(MyUnionDataUniqueListW *p, MyUnionDataW *data)
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

static bool_t MyUnionDataUniqueListW_remove(MyUnionDataUniqueListW *p, MyUnionDataW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyUnionDataW *MyUnionDataUniqueListW_extract(MyUnionDataUniqueListW *p, MyUnionDataW *key)
{
	return (MyUnionDataW *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyUnionDataUniqueListWMkArrArg
{
	MyUnionDataW **arr;
	unsigned int idx;
} MyUnionDataUniqueListWMkArrArg;

static Dz1Error _MyUnionDataUniqueListW_get_array(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueListWMkArrArg *arg = (MyUnionDataUniqueListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataW **MyUnionDataUniqueListW_get_array(MyUnionDataUniqueListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataW **)Dz1Calloc(sizeof(MyUnionDataW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataUniqueListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataUniqueListW_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataUniqueListW_travelForward(MyUnionDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataUniqueListW_travelBackward(MyUnionDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionDataW *MyUnionDataUniqueListW_find(MyUnionDataUniqueListW *p, MyUnionDataW *key)
{
	return (MyUnionDataW *)Dz1AATree_find(p->storage, key);
}

static MyUnionDataW *MyUnionDataUniqueListW_getHead(MyUnionDataUniqueListW *p)
{
	return (MyUnionDataW *)Dz1AATree_getHead(p->storage);
}

static MyUnionDataW *MyUnionDataUniqueListW_getTail(MyUnionDataUniqueListW *p)
{
	return (MyUnionDataW *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyUnionDataUniqueListW_count(MyUnionDataUniqueListW *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyUnionDataUniqueListW *MyUnionDataUniqueListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueListW *ret = (MyUnionDataUniqueListW *)Dz1Calloc(sizeof(MyUnionDataUniqueListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyUnionDataW_cmp,
				(Dz1DelFunc)MyUnionDataW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataUniqueListW_count;
			ret->travel = MyUnionDataUniqueListW_travelForward;
			ret->travelForward = MyUnionDataUniqueListW_travelForward;
			ret->travelBackward = MyUnionDataUniqueListW_travelBackward;
			ret->get_array = MyUnionDataUniqueListW_get_array;
			ret->add = MyUnionDataUniqueListW_add;
			ret->remove = MyUnionDataUniqueListW_remove;
			ret->find = MyUnionDataUniqueListW_find;
			ret->extract = MyUnionDataUniqueListW_extract;
			ret->getHead = MyUnionDataUniqueListW_getHead;
			ret->getTail = MyUnionDataUniqueListW_getTail;
			ret->cmp = MyUnionDataW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataUniqueListW_clone(void *ptr, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueListW *p = (MyUnionDataUniqueListW *)ptr;
	MyUnionDataW *cloned = MyUnionDataW_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataUniqueListW *MyUnionDataUniqueListW_clone(MyUnionDataUniqueListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataUniqueListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueListW_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataUniqueListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataUniqueListW_purge(MyUnionDataUniqueListW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyUnionDataUniqueListW_del(MyUnionDataUniqueListW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataUniqueListW_dump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionDataW_dump(p, tab);
	return err;
}

void MyUnionDataUniqueListW_dump(MyUnionDataUniqueListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataUniqueListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionDataUniqueListW_fdump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataUniqueListW_fdump(FILE *fp, MyUnionDataUniqueListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataUniqueListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyUnionDataUniqueListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedListW
static Dz1Error MyUnionDataOrderedListW_add(MyUnionDataOrderedListW *p, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataOrderedListW_remove(MyUnionDataOrderedListW *p, MyUnionDataW *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyUnionDataW *MyUnionDataOrderedListW_extract(MyUnionDataOrderedListW *p, MyUnionDataW *key)
{
	return (MyUnionDataW *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyUnionDataOrderedListWMkArrArg
{
	MyUnionDataW **arr;
	unsigned int idx;
} MyUnionDataOrderedListWMkArrArg;

static Dz1Error _MyUnionDataOrderedListW_get_array(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedListWMkArrArg *arg = (MyUnionDataOrderedListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataW **MyUnionDataOrderedListW_get_array(MyUnionDataOrderedListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataW **)Dz1Calloc(sizeof(MyUnionDataW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataOrderedListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataOrderedListW_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataOrderedListW_travelForward(MyUnionDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataOrderedListW_travelBackward(MyUnionDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionDataW *MyUnionDataOrderedListW_find(MyUnionDataOrderedListW *p, MyUnionDataW *key)
{
	return (MyUnionDataW *)Dz1OrderedFifo_find(p->storage, key);
}

static MyUnionDataW *MyUnionDataOrderedListW_getHead(MyUnionDataOrderedListW *p)
{
	return (MyUnionDataW *)Dz1OrderedFifo_getHead(p->storage);
}

static MyUnionDataW *MyUnionDataOrderedListW_getTail(MyUnionDataOrderedListW *p)
{
	return (MyUnionDataW *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyUnionDataOrderedListW_count(MyUnionDataOrderedListW *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyUnionDataOrderedListW *MyUnionDataOrderedListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedListW *ret = (MyUnionDataOrderedListW *)Dz1Calloc(sizeof(MyUnionDataOrderedListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyUnionDataW_cmp,
				(Dz1DelFunc)MyUnionDataW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataOrderedListW_count;
			ret->travel = MyUnionDataOrderedListW_travelForward;
			ret->travelForward = MyUnionDataOrderedListW_travelForward;
			ret->travelBackward = MyUnionDataOrderedListW_travelBackward;
			ret->get_array = MyUnionDataOrderedListW_get_array;
			ret->add = MyUnionDataOrderedListW_add;
			ret->remove = MyUnionDataOrderedListW_remove;
			ret->find = MyUnionDataOrderedListW_find;
			ret->extract = MyUnionDataOrderedListW_extract;
			ret->getHead = MyUnionDataOrderedListW_getHead;
			ret->getTail = MyUnionDataOrderedListW_getTail;
			ret->cmp = MyUnionDataW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataOrderedListW_clone(void *ptr, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedListW *p = (MyUnionDataOrderedListW *)ptr;
	MyUnionDataW *cloned = MyUnionDataW_clone(data, &err); // normal
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataOrderedListW *MyUnionDataOrderedListW_clone(MyUnionDataOrderedListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataOrderedListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedListW_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataOrderedListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataOrderedListW_purge(MyUnionDataOrderedListW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyUnionDataOrderedListW_del(MyUnionDataOrderedListW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataOrderedListW_dump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionDataW_dump(p, tab);
	return err;
}

void MyUnionDataOrderedListW_dump(MyUnionDataOrderedListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataOrderedListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionDataOrderedListW_fdump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataOrderedListW_fdump(FILE *fp, MyUnionDataOrderedListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataOrderedListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyUnionDataOrderedListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataListW
static Dz1Error MyUnionDataListW_add(MyUnionDataListW *p, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataListW_remove(MyUnionDataListW *p, MyUnionDataW *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyUnionDataW *MyUnionDataListW_extract(MyUnionDataListW *p, MyUnionDataW *ptr)
{
	return (MyUnionDataW *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyUnionDataListWMkArrArg
{
	MyUnionDataW **arr;
	unsigned int idx;
} MyUnionDataListWMkArrArg;

static Dz1Error _MyUnionDataListW_get_array(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataListWMkArrArg *arg = (MyUnionDataListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataW **MyUnionDataListW_get_array(MyUnionDataListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataW **)Dz1Calloc(sizeof(MyUnionDataW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataListW_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataListW_travelForward(MyUnionDataListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataListW_travelBackward(MyUnionDataListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyUnionDataListWFindArg
{
	MyUnionDataW *key;
	MyUnionDataW *ret;
	int (*cmp)(MyUnionDataW *a, MyUnionDataW *b);
} MyUnionDataListWFindArg;

static Dz1Error _MyUnionDataListW_find(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyUnionDataListWFindArg *arg = (MyUnionDataListWFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyUnionDataW *MyUnionDataListW_find(MyUnionDataListW *p, MyUnionDataW *key)
{
	MyUnionDataListWFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyUnionDataListW_find, (void *)&arg);
	return arg.ret;
}

static MyUnionDataW *MyUnionDataListW_getHead(MyUnionDataListW *p)
{
	return (MyUnionDataW *)Dz1Fifo_getFirst(p->storage);
}

static MyUnionDataW *MyUnionDataListW_getTail(MyUnionDataListW *p)
{
	return (MyUnionDataW *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyUnionDataListW_count(MyUnionDataListW *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionDataListW *MyUnionDataListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataListW *ret = (MyUnionDataListW *)Dz1Calloc(sizeof(MyUnionDataListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyUnionDataW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataListW_count;
			ret->travel = MyUnionDataListW_travelForward;
			ret->travelForward = MyUnionDataListW_travelForward;
			ret->travelBackward = MyUnionDataListW_travelBackward;
			ret->get_array = MyUnionDataListW_get_array;
			ret->add = MyUnionDataListW_add;
			ret->remove = MyUnionDataListW_remove;
			ret->find = MyUnionDataListW_find;
			ret->extract = MyUnionDataListW_extract;
			ret->getHead = MyUnionDataListW_getHead;
			ret->getTail = MyUnionDataListW_getTail;
			ret->cmp = MyUnionDataW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataListW_clone(void *ptr, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataListW *p = (MyUnionDataListW *)ptr;
	MyUnionDataW *cloned = MyUnionDataW_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataListW *MyUnionDataListW_clone(MyUnionDataListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataListW_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionDataListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataListW_purge(MyUnionDataListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionDataListW_del(MyUnionDataListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataListW_dump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionDataW_dump(p, tab);
	return err;
}

void MyUnionDataListW_dump(MyUnionDataListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionDataListW_fdump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataListW_fdump(FILE *fp, MyUnionDataListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyUnionDataListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueRefListW
static Dz1Error MyUnionDataUniqueRefListW_add(MyUnionDataUniqueRefListW *p, MyUnionDataW *data)
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

static bool_t MyUnionDataUniqueRefListW_remove(MyUnionDataUniqueRefListW *p, MyUnionDataW *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static MyUnionDataW *MyUnionDataUniqueRefListW_extract(MyUnionDataUniqueRefListW *p, MyUnionDataW *key)
{
	return (MyUnionDataW *)Dz1AATree_extract(p->storage, key);
}

typedef struct MyUnionDataUniqueRefListWMkArrArg
{
	MyUnionDataW **arr;
	unsigned int idx;
} MyUnionDataUniqueRefListWMkArrArg;

static Dz1Error _MyUnionDataUniqueRefListW_get_array(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueRefListWMkArrArg *arg = (MyUnionDataUniqueRefListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataW **MyUnionDataUniqueRefListW_get_array(MyUnionDataUniqueRefListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataW **)Dz1Calloc(sizeof(MyUnionDataW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataUniqueRefListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataUniqueRefListW_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataUniqueRefListW_travelForward(MyUnionDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataUniqueRefListW_travelBackward(MyUnionDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionDataW *MyUnionDataUniqueRefListW_find(MyUnionDataUniqueRefListW *p, MyUnionDataW *key)
{
	return (MyUnionDataW *)Dz1AATree_find(p->storage, key);
}

static MyUnionDataW *MyUnionDataUniqueRefListW_getHead(MyUnionDataUniqueRefListW *p)
{
	return (MyUnionDataW *)Dz1AATree_getHead(p->storage);
}

static MyUnionDataW *MyUnionDataUniqueRefListW_getTail(MyUnionDataUniqueRefListW *p)
{
	return (MyUnionDataW *)Dz1AATree_getTail(p->storage);
}

static unsigned int MyUnionDataUniqueRefListW_count(MyUnionDataUniqueRefListW *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

MyUnionDataUniqueRefListW *MyUnionDataUniqueRefListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueRefListW *ret = (MyUnionDataUniqueRefListW *)Dz1Calloc(sizeof(MyUnionDataUniqueRefListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueRefListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)MyUnionDataW_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataUniqueRefListW_count;
			ret->travel = MyUnionDataUniqueRefListW_travelForward;
			ret->travelForward = MyUnionDataUniqueRefListW_travelForward;
			ret->travelBackward = MyUnionDataUniqueRefListW_travelBackward;
			ret->get_array = MyUnionDataUniqueRefListW_get_array;
			ret->add = MyUnionDataUniqueRefListW_add;
			ret->remove = MyUnionDataUniqueRefListW_remove;
			ret->find = MyUnionDataUniqueRefListW_find;
			ret->extract = MyUnionDataUniqueRefListW_extract;
			ret->getHead = MyUnionDataUniqueRefListW_getHead;
			ret->getTail = MyUnionDataUniqueRefListW_getTail;
			ret->cmp = MyUnionDataW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataUniqueRefListW_clone(void *ptr, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataUniqueRefListW *p = (MyUnionDataUniqueRefListW *)ptr;
	MyUnionDataW *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataUniqueRefListW *MyUnionDataUniqueRefListW_clone(MyUnionDataUniqueRefListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataUniqueRefListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataUniqueRefListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataUniqueRefListW_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataUniqueRefListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataUniqueRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataUniqueRefListW_purge(MyUnionDataUniqueRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void MyUnionDataUniqueRefListW_del(MyUnionDataUniqueRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataUniqueRefListW_dump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionDataW_dump(p, tab);
	return err;
}

void MyUnionDataUniqueRefListW_dump(MyUnionDataUniqueRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataUniqueRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionDataUniqueRefListW_fdump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataUniqueRefListW_fdump(FILE *fp, MyUnionDataUniqueRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataUniqueRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyUnionDataUniqueRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedRefListW
static Dz1Error MyUnionDataOrderedRefListW_add(MyUnionDataOrderedRefListW *p, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1OrderedFifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataOrderedRefListW_remove(MyUnionDataOrderedRefListW *p, MyUnionDataW *key)
{
	return Dz1OrderedFifo_remove(p->storage, key);
}

static MyUnionDataW *MyUnionDataOrderedRefListW_extract(MyUnionDataOrderedRefListW *p, MyUnionDataW *key)
{
	return (MyUnionDataW *)Dz1OrderedFifo_extract(p->storage, key);
}

typedef struct MyUnionDataOrderedRefListWMkArrArg
{
	MyUnionDataW **arr;
	unsigned int idx;
} MyUnionDataOrderedRefListWMkArrArg;

static Dz1Error _MyUnionDataOrderedRefListW_get_array(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedRefListWMkArrArg *arg = (MyUnionDataOrderedRefListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataW **MyUnionDataOrderedRefListW_get_array(MyUnionDataOrderedRefListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataW **)Dz1Calloc(sizeof(MyUnionDataW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataOrderedRefListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataOrderedRefListW_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataOrderedRefListW_travelForward(MyUnionDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1OrderedFifo_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataOrderedRefListW_travelBackward(MyUnionDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1OrderedFifo_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static MyUnionDataW *MyUnionDataOrderedRefListW_find(MyUnionDataOrderedRefListW *p, MyUnionDataW *key)
{
	return (MyUnionDataW *)Dz1OrderedFifo_find(p->storage, key);
}

static MyUnionDataW *MyUnionDataOrderedRefListW_getHead(MyUnionDataOrderedRefListW *p)
{
	return (MyUnionDataW *)Dz1OrderedFifo_getHead(p->storage);
}

static MyUnionDataW *MyUnionDataOrderedRefListW_getTail(MyUnionDataOrderedRefListW *p)
{
	return (MyUnionDataW *)Dz1OrderedFifo_getTail(p->storage);
}

static unsigned int MyUnionDataOrderedRefListW_count(MyUnionDataOrderedRefListW *p)
{
	unsigned int ret = Dz1OrderedFifo_count(p->storage);
	return ret;
}

MyUnionDataOrderedRefListW *MyUnionDataOrderedRefListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedRefListW *ret = (MyUnionDataOrderedRefListW *)Dz1Calloc(sizeof(MyUnionDataOrderedRefListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedRefListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1OrderedFifo_new(
				(Dz1CmpFunc)MyUnionDataW_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataOrderedRefListW_count;
			ret->travel = MyUnionDataOrderedRefListW_travelForward;
			ret->travelForward = MyUnionDataOrderedRefListW_travelForward;
			ret->travelBackward = MyUnionDataOrderedRefListW_travelBackward;
			ret->get_array = MyUnionDataOrderedRefListW_get_array;
			ret->add = MyUnionDataOrderedRefListW_add;
			ret->remove = MyUnionDataOrderedRefListW_remove;
			ret->find = MyUnionDataOrderedRefListW_find;
			ret->extract = MyUnionDataOrderedRefListW_extract;
			ret->getHead = MyUnionDataOrderedRefListW_getHead;
			ret->getTail = MyUnionDataOrderedRefListW_getTail;
			ret->cmp = MyUnionDataW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataOrderedRefListW_clone(void *ptr, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataOrderedRefListW *p = (MyUnionDataOrderedRefListW *)ptr;
	MyUnionDataW *cloned = data; // ref
	err = Dz1OrderedFifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataOrderedRefListW *MyUnionDataOrderedRefListW_clone(MyUnionDataOrderedRefListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataOrderedRefListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataOrderedRefListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataOrderedRefListW_delAndSetNull, (void *)&ret);

		*errp = Dz1OrderedFifo_travelForward(src->storage, (Dz1AATreeTravelFunc)_MyUnionDataOrderedRefListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataOrderedRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataOrderedRefListW_purge(MyUnionDataOrderedRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_empty(p->storage);
}

void MyUnionDataOrderedRefListW_del(MyUnionDataOrderedRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1OrderedFifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataOrderedRefListW_dump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionDataW_dump(p, tab);
	return err;
}

void MyUnionDataOrderedRefListW_dump(MyUnionDataOrderedRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataOrderedRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionDataOrderedRefListW_fdump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataOrderedRefListW_fdump(FILE *fp, MyUnionDataOrderedRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataOrderedRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyUnionDataOrderedRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataRefListW
static Dz1Error MyUnionDataRefListW_add(MyUnionDataRefListW *p, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static bool_t MyUnionDataRefListW_remove(MyUnionDataRefListW *p, MyUnionDataW *ptr)
{
	return Dz1Fifo_remove(p->storage, ptr);
}

static MyUnionDataW *MyUnionDataRefListW_extract(MyUnionDataRefListW *p, MyUnionDataW *ptr)
{
	return (MyUnionDataW *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct MyUnionDataRefListWMkArrArg
{
	MyUnionDataW **arr;
	unsigned int idx;
} MyUnionDataRefListWMkArrArg;

static Dz1Error _MyUnionDataRefListW_get_array(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataRefListWMkArrArg *arg = (MyUnionDataRefListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnionDataW **MyUnionDataRefListW_get_array(MyUnionDataRefListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnionDataW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnionDataW **)Dz1Calloc(sizeof(MyUnionDataW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionDataRefListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionDataRefListW_get_array, (void *)&arg);
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

static Dz1Error MyUnionDataRefListW_travelForward(MyUnionDataRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionDataRefListW_travelBackward(MyUnionDataRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct MyUnionDataRefListWFindArg
{
	MyUnionDataW *key;
	MyUnionDataW *ret;
	int (*cmp)(MyUnionDataW *a, MyUnionDataW *b);
} MyUnionDataRefListWFindArg;

static Dz1Error _MyUnionDataRefListW_find(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	MyUnionDataRefListWFindArg *arg = (MyUnionDataRefListWFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static MyUnionDataW *MyUnionDataRefListW_find(MyUnionDataRefListW *p, MyUnionDataW *key)
{
	MyUnionDataRefListWFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _MyUnionDataRefListW_find, (void *)&arg);
	return arg.ret;
}

static MyUnionDataW *MyUnionDataRefListW_getHead(MyUnionDataRefListW *p)
{
	return (MyUnionDataW *)Dz1Fifo_getFirst(p->storage);
}

static MyUnionDataW *MyUnionDataRefListW_getTail(MyUnionDataRefListW *p)
{
	return (MyUnionDataW *)Dz1Fifo_getLast(p->storage);
}

static unsigned int MyUnionDataRefListW_count(MyUnionDataRefListW *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionDataRefListW *MyUnionDataRefListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataRefListW *ret = (MyUnionDataRefListW *)Dz1Calloc(sizeof(MyUnionDataRefListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataRefListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionDataRefListW_count;
			ret->travel = MyUnionDataRefListW_travelForward;
			ret->travelForward = MyUnionDataRefListW_travelForward;
			ret->travelBackward = MyUnionDataRefListW_travelBackward;
			ret->get_array = MyUnionDataRefListW_get_array;
			ret->add = MyUnionDataRefListW_add;
			ret->remove = MyUnionDataRefListW_remove;
			ret->find = MyUnionDataRefListW_find;
			ret->extract = MyUnionDataRefListW_extract;
			ret->getHead = MyUnionDataRefListW_getHead;
			ret->getTail = MyUnionDataRefListW_getTail;
			ret->cmp = MyUnionDataW_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionDataRefListW_clone(void *ptr, MyUnionDataW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionDataRefListW *p = (MyUnionDataRefListW *)ptr;
	MyUnionDataW *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionDataRefListW *MyUnionDataRefListW_clone(MyUnionDataRefListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataRefListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionDataRefListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionDataRefListW_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionDataRefListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataRefListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionDataRefListW_purge(MyUnionDataRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionDataRefListW_del(MyUnionDataRefListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionDataRefListW_dump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); MyUnionDataW_dump(p, tab);
	return err;
}

void MyUnionDataRefListW_dump(MyUnionDataRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataRefListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _MyUnionDataRefListW_fdump(void *ptr, MyUnionDataW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); MyUnionDataW_fdump(arg->fp, p, tab);
	return err;
}

void MyUnionDataRefListW_fdump(FILE *fp, MyUnionDataRefListW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _MyUnionDataRefListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyUnionDataRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataInfoW
// void MyUnionDataInfoW_obj_ptr_arr_del(MyUnionDataW **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyUnionDataInfoW, MyUnionDataW*, obj_ptr_arr, u32_t, MyUnionDataW_del)
// void MyUnionDataInfoW_obj_ptr_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyUnionDataInfoW, MyUnionDataW*, obj_ptr_arr, u32_t)
// MyUnionDataW **MyUnionDataInfoW_obj_ptr_arr_clone(MyUnionDataW **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyUnionDataInfoW, MyUnionDataW*, obj_ptr_arr, u32_t, MyUnionDataW_clone)
// void MyUnionDataInfoW_obj_ptr_arrW_dump(MyUnionDataW **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(MyUnionDataInfoW, MyUnionDataW*, obj_ptr_arr, u32_t, ".", MyUnionDataW_dump)
// void MyUnionDataInfoW_obj_ptr_arrW_fdump(FILE *fp, MyUnionDataW **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(MyUnionDataInfoW, MyUnionDataW*, obj_ptr_arr, u32_t, ".", MyUnionDataW_fdump)

// void MyUnionDataInfoW_obj_arr_del(MyUnionDataW *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_construct_del(MyUnionDataInfoW, MyUnionDataW, obj_arr, u32_t, MyUnionDataW_purge)
// void MyUnionDataInfoW_obj_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_construct_delAndSetNull(MyUnionDataInfoW, MyUnionDataW, obj_arr, u32_t)
// MyUnionDataW *MyUnionDataInfoW_obj_arr_clone(MyUnionDataW *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_construct_clone(MyUnionDataInfoW, MyUnionDataW, obj_arr, u32_t, MyUnionDataW_copy)
// void MyUnionDataInfoW_obj_arrW_dump(MyUnionDataW *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_dump(MyUnionDataInfoW, MyUnionDataW, obj_arr, u32_t, ".", MyUnionDataW_dump)
// void MyUnionDataInfoW_obj_arrW_fdump(FILE *fp, MyUnionDataW *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_constructW_fdump(MyUnionDataInfoW, MyUnionDataW, obj_arr, u32_t, ".", MyUnionDataW_fdump)

// void MyUnionDataInfoW_prims_arr_del(u64_t *src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_val_primitive_del(MyUnionDataInfoW, u64_t, prims_arr, u32_t)
// void MyUnionDataInfoW_prims_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_val_primitive_delAndSetNull(MyUnionDataInfoW, u64_t, prims_arr)
// u64_t *MyUnionDataInfoW_prims_arr_clone(u64_t *src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_val_primitive_clone(MyUnionDataInfoW, u64_t, prims_arr, u32_t)
// void MyUnionDataInfoW_prims_arrW_dump(u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_dump(MyUnionDataInfoW, u64_t, prims_arr, u32_t, " = ", Dz1u64W_dump)
// void MyUnionDataInfoW_prims_arrW_fdump(FILE *fp, u64_t *p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_val_primitiveW_fdump(MyUnionDataInfoW, u64_t, prims_arr, u32_t, " = ", Dz1u64W_fdump)

// void MyUnionDataInfoW_primptrs_arr_del(u64_t **src, u32_t cnt);
static __inline__ Dz1StructArrayMemb_ptr_del(MyUnionDataInfoW, u64_t*, primptrs_arr, u32_t, Dz1u64_del)
// void MyUnionDataInfoW_primptrs_arr_delAndSetNull(void *ptr);
static __inline__ Dz1StructArrayMemb_ptr_delAndSetNull(MyUnionDataInfoW, u64_t*, primptrs_arr, u32_t)
// u64_t **MyUnionDataInfoW_primptrs_arr_clone(u64_t **src, u32_t cnt, Dz1Error *err);
static __inline__ Dz1StructArrayMemb_ptr_clone(MyUnionDataInfoW, u64_t*, primptrs_arr, u32_t, Dz1u64_clone)
// void MyUnionDataInfoW_primptrs_arrW_dump(u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_dump(MyUnionDataInfoW, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64W_dump)
// void MyUnionDataInfoW_primptrs_arrW_fdump(FILE *fp, u64_t **p, u32_t cnt, int tab);
static __inline__ Dz1StructArrayMemb_ptrW_fdump(MyUnionDataInfoW, u64_t*, primptrs_arr, u32_t, " = ", Dz1u64W_fdump)

MyUnionDataInfoW *MyUnionDataInfoW_new(MyUnionDataW **obj_ptr_arr/*_e_clone*/, 
									   u32_t obj_ptr_cnt, 
									   MyUnionDataW *obj_arr/*_e_copy*/, 
									   u32_t obj_cnt, 
									   u64_t *prims_arr/*_e_copy*/, 
									   u32_t prims_cnt, 
									   u64_t **primptrs_arr/*_e_clone*/, 
									   u32_t primptrs_cnt, 
									   s32_t *i_val/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionDataInfoW *__internal_ret = (MyUnionDataInfoW *)Dz1Calloc(sizeof(MyUnionDataInfoW), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnionDataInfoW_delAndSetNull, (void *)&__internal_ret);
		
		if (obj_ptr_arr != NULL && (__internal_ret->obj_ptr_arr = MyUnionDataInfoW_obj_ptr_arr_clone(obj_ptr_arr, obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (obj_arr != NULL && (__internal_ret->obj_arr = MyUnionDataInfoW_obj_arr_clone(obj_arr, obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (prims_arr != NULL && (__internal_ret->prims_arr = MyUnionDataInfoW_prims_arr_clone(prims_arr, prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else if (primptrs_arr != NULL && (__internal_ret->primptrs_arr = MyUnionDataInfoW_primptrs_arr_clone(primptrs_arr, primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			__internal_ret->obj_ptr_cnt = obj_ptr_cnt;
			__internal_ret->obj_cnt = obj_cnt;
			__internal_ret->prims_cnt = prims_cnt;
			__internal_ret->primptrs_cnt = primptrs_cnt;
			__internal_ret->i_val = i_val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataInfoW_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyUnionDataInfoW_copy(MyUnionDataInfoW *dst, MyUnionDataInfoW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->obj_ptr_arr != NULL && (dst->obj_ptr_arr = MyUnionDataInfoW_obj_ptr_arr_clone(src->obj_ptr_arr, src->obj_ptr_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->obj_arr != NULL && (dst->obj_arr = MyUnionDataInfoW_obj_arr_clone(src->obj_arr, src->obj_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->prims_arr != NULL && (dst->prims_arr = MyUnionDataInfoW_prims_arr_clone(src->prims_arr, src->prims_cnt, errp)) == NULL) { ERR_OUT(errp); }
	else if (src->primptrs_arr != NULL && (dst->primptrs_arr = MyUnionDataInfoW_primptrs_arr_clone(src->primptrs_arr, src->primptrs_cnt, errp)) == NULL) { ERR_OUT(errp); }
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

MyUnionDataInfoW *MyUnionDataInfoW_clone(MyUnionDataInfoW *src, Dz1Error *err)
{
	MyUnionDataInfoW *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyUnionDataInfoW *)Dz1Calloc(sizeof(MyUnionDataInfoW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnionDataInfoW_delAndSetNull, (void *)&dst);
		if (MyUnionDataInfoW_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionDataInfoW_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyUnionDataInfoW_purge(MyUnionDataInfoW *p)
{
	if (p == NULL) return;
	MyUnionDataInfoW_obj_ptr_arr_del(p->obj_ptr_arr, p->obj_ptr_cnt);
	MyUnionDataInfoW_obj_arr_del(p->obj_arr, p->obj_cnt);
	MyUnionDataInfoW_prims_arr_del(p->prims_arr, p->prims_cnt);
	MyUnionDataInfoW_primptrs_arr_del(p->primptrs_arr, p->primptrs_cnt);
}

void MyUnionDataInfoW_del(MyUnionDataInfoW *p)
{
	if (p == NULL) return;
	MyUnionDataInfoW_purge(p);
	Dz1Free(p);
}

void MyUnionDataInfoW_dump(MyUnionDataInfoW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"obj_ptr_arr = "); MyUnionDataInfoW_obj_ptr_arrW_dump(p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"obj_ptr_cnt = "); Dz1u32_dump(&p->obj_ptr_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"obj_arr = "); MyUnionDataInfoW_obj_arrW_dump(p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"obj_cnt = "); Dz1u32_dump(&p->obj_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"prims_arr = "); MyUnionDataInfoW_prims_arrW_dump(p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"prims_cnt = "); Dz1u32_dump(&p->prims_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"primptrs_arr = "); MyUnionDataInfoW_primptrs_arrW_dump(p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadW_tprintf(tab, L"primptrs_cnt = "); Dz1u32_dump(&p->primptrs_cnt, tab); 
		Dz1ThreadW_tprintf(tab, L"i_val = "); Dz1s32_dump(p->i_val, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void MyUnionDataInfoW_fdump(FILE *fp, MyUnionDataInfoW *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintf(fp, tab, L"obj_ptr_arr = "); MyUnionDataInfoW_obj_ptr_arrW_fdump(fp, p->obj_ptr_arr, p->obj_ptr_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"obj_ptr_cnt = "); Dz1u32_fdump(fp, &p->obj_ptr_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"obj_arr = "); MyUnionDataInfoW_obj_arrW_fdump(fp, p->obj_arr, p->obj_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"obj_cnt = "); Dz1u32_fdump(fp, &p->obj_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"prims_arr = "); MyUnionDataInfoW_prims_arrW_fdump(fp, p->prims_arr, p->prims_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"prims_cnt = "); Dz1u32_fdump(fp, &p->prims_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"primptrs_arr = "); MyUnionDataInfoW_primptrs_arrW_fdump(fp, p->primptrs_arr, p->primptrs_cnt, tab);
		Dz1ThreadW_ftprintf(fp, tab, L"primptrs_cnt = "); Dz1u32_fdump(fp, &p->primptrs_cnt, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"i_val = "); Dz1s32_fdump(fp, p->i_val, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
// MyUnionDataInfoW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

