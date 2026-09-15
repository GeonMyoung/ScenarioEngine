////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_jsonTestDef.h"

////////////////////////////////////////////////////////////////////////////////
// MyEnum
static struct MyEnumMapA
{
	str_t str;
	MyEnum v;
} MyEnumMapA[] =
{
	{ (char *)"abc", MyEnum_abc },
	{ (char *)"bcd", MyEnum_bcd },
	{ (char *)"cde", MyEnum_cde },
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
	{ (wchar_t *)L"abc", MyEnum_abc },
	{ (wchar_t *)L"bcd", MyEnum_bcd },
	{ (wchar_t *)L"cde", MyEnum_cde },
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
// MyEnum
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStruct
MyStruct *MyStruct_new(u8_t a, u16_t b, u32_t c, u64_t d, Dz1Str e, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStruct *__internal_ret = (MyStruct *)Dz1Calloc(sizeof(MyStruct), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyStruct_delAndSetNull, (void *)&__internal_ret);
		
		if (e && (__internal_ret->e = Dz1Str_clone(e, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->a = a;
			__internal_ret->b = b;
			__internal_ret->c = c;
			__internal_ret->d = d;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStruct_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyStruct_copy(MyStruct *dst, MyStruct *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->e && (dst->e = Dz1Str_clone(src->e, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->a = src->a;
		dst->b = src->b;
		dst->c = src->c;
		dst->d = src->d;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyStruct *MyStruct_clone(MyStruct *src, Dz1Error *err)
{
	MyStruct *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyStruct *)Dz1Calloc(sizeof(MyStruct), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyStruct_delAndSetNull, (void *)&dst);
		if (MyStruct_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStruct_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyStruct_purge(MyStruct *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->e);
}

void MyStruct_del(MyStruct *p)
{
	if (p == NULL) return;
	MyStruct_purge(p);
	Dz1Free(p);
}

void MyStruct_dump(MyStruct *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("a = ")); Dz1u8_dump(&p->a, tab); 
		Dz1Thread_tprintf(tab, Dz1T("b = ")); Dz1u16_dump(&p->b, tab); 
		Dz1Thread_tprintf(tab, Dz1T("c = ")); Dz1u32_dump(&p->c, tab); 
		Dz1Thread_tprintf(tab, Dz1T("d = ")); Dz1u64_dump(&p->d, tab); 
		Dz1Thread_tprintf(tab, Dz1T("e = ")); Dz1Str_dump(p->e, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// MyStruct
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStructList
static Dz1Error MyStructList_add(MyStructList *p, MyStruct *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct MyStructListMkArrArg
{
	MyStruct **arr;
	unsigned int idx;
} MyStructListMkArrArg;

static Dz1Error _MyStructList_get_array(void *ptr, MyStruct *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStructListMkArrArg *arg = (MyStructListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyStruct **MyStructList_get_array(MyStructList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyStruct **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyStruct **)Dz1Calloc(sizeof(MyStruct *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyStructListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyStructList_get_array, (void *)&arg);
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

static Dz1Error MyStructList_travelForward(MyStructList *p, Dz1Error (*func)(void *ptr, MyStruct *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyStructList_travelBackward(MyStructList *p, Dz1Error (*func)(void *ptr, MyStruct *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int MyStructList_count(MyStructList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyStructList *MyStructList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStructList *ret = (MyStructList *)Dz1Calloc(sizeof(MyStructList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStructList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyStruct_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyStructList_count;
			ret->travel = MyStructList_travelForward;
			ret->travelForward = MyStructList_travelForward;
			ret->travelBackward = MyStructList_travelBackward;
			ret->get_array = MyStructList_get_array;
			ret->add = MyStructList_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyStructList_clone(void *ptr, MyStruct *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyStructList *p = (MyStructList *)ptr;
	MyStruct *cloned = MyStruct_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyStructList *MyStructList_clone(MyStructList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyStructList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyStructList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyStructList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyStructList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyStructList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyStructList_purge(MyStructList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyStructList_del(MyStructList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyStructList_dump(void *ptr, MyStruct *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyStruct_dump(p, tab);
	return err;
}

void MyStructList_dump(MyStructList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyStructList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// MyStructList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionPresent
static struct MyUnionPresentMapA
{
	str_t str;
	MyUnionPresent v;
} MyUnionPresentMapA[] =
{
	{ (char *)"a", MyUnionPresent_a },
	{ (char *)"b", MyUnionPresent_b },
	{ (char *)"c", MyUnionPresent_c },
	{ (char *)"d", MyUnionPresent_d },
	{ (char *)"e", MyUnionPresent_e },
	{ (char *)"f", MyUnionPresent_f },
	{ (char *)"g", MyUnionPresent_g },
	{ (char *)"h", MyUnionPresent_h },
	{ (char *)"i", MyUnionPresent_i },
	{ (char *)"j", MyUnionPresent_j },
	{ NULL, MyUnionPresent_max }
};

str_t MyUnionPresentStrA(MyUnionPresent v)
{
	struct MyUnionPresentMapA *i = NULL;
	for (i = MyUnionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionPresent MyUnionPresentFromStrA(str_t str)
{
	struct MyUnionPresentMapA *i = NULL;
	for (i = MyUnionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return MyUnionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct MyUnionPresentMapW
{
	wstr_t str;
	MyUnionPresent v;
} MyUnionPresentMapW[] =
{
	{ (wchar_t *)L"a", MyUnionPresent_a },
	{ (wchar_t *)L"b", MyUnionPresent_b },
	{ (wchar_t *)L"c", MyUnionPresent_c },
	{ (wchar_t *)L"d", MyUnionPresent_d },
	{ (wchar_t *)L"e", MyUnionPresent_e },
	{ (wchar_t *)L"f", MyUnionPresent_f },
	{ (wchar_t *)L"g", MyUnionPresent_g },
	{ (wchar_t *)L"h", MyUnionPresent_h },
	{ (wchar_t *)L"i", MyUnionPresent_i },
	{ (wchar_t *)L"j", MyUnionPresent_j },
	{ NULL, MyUnionPresent_max }
};

wstr_t MyUnionPresentStrW(MyUnionPresent v)
{
	struct MyUnionPresentMapW *i = NULL;
	for (i = MyUnionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

MyUnionPresent MyUnionPresentFromStrW(wstr_t str)
{
	struct MyUnionPresentMapW *i = NULL;
	for (i = MyUnionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return MyUnionPresent_max;
}
#endif // UNIX_SYSTEM

MyUnionPresent *MyUnionPresent_new(MyUnionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionPresent *__internal_ret = (MyUnionPresent *)Dz1Calloc(sizeof(MyUnionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void MyUnionPresent_dump(MyUnionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), MyUnionPresentStr(*v));
}
// MyUnionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnion
MyUnion *MyUnion_new(MyUnionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnion *ret = (MyUnion *)Dz1Calloc(sizeof(MyUnion), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyUnion_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case MyUnionPresent_a:
			// _U_prim_clone
			if (ptr != NULL) ret->x.a = *(u8_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_b:
			// _U_prim_clone
			if (ptr != NULL) ret->x.b = *(u16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_c:
			// _U_prim_clone
			if (ptr != NULL) ret->x.c = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_d:
			// _U_prim_clone
			if (ptr != NULL) ret->x.d = *(u64_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_e:
			// _U_prim_clone
			if (ptr && (ret->x.e = Dz1Str_clone((Dz1Str)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyUnionPresent_f:
			// _U_cst_clone
			if (ptr != NULL) ret->x.f = (MyStructList *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_g:
			// _U_prim_clone
			if (ptr != NULL) ret->x.g = *(real64_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_h:
			// _U_prim_clone
			if (ptr != NULL) ret->x.h = *(real32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_i:
			// _U_enum_clone
			if (ptr != NULL) ret->x.i = *(MyEnum *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_j:
			// _U_imp_clone
			if (ptr != NULL) ret->x.j = *(MyExternHz *)ptr;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnion_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t MyUnion_copy(MyUnion *ret, MyUnion *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case MyUnionPresent_a:
			// _U_prim_clone
			ret->x.a = src->x.a;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_b:
			// _U_prim_clone
			ret->x.b = src->x.b;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_c:
			// _U_prim_clone
			ret->x.c = src->x.c;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_d:
			// _U_prim_clone
			ret->x.d = src->x.d;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_e:
			// _U_prim_clone
			if (src->x.e && (ret->x.e = Dz1Str_clone(src->x.e, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyUnionPresent_f:
			// _U_cst_clone
			if (src->x.f && (ret->x.f = MyStructList_clone(src->x.f, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case MyUnionPresent_g:
			// _U_prim_clone
			ret->x.g = src->x.g;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_h:
			// _U_prim_clone
			ret->x.h = src->x.h;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_i:
			// _U_enum_clone
			ret->x.i = src->x.i;
			ERR_CLEAR(errp);
			break;
		case MyUnionPresent_j:
			// _U_imp_clone
			ret->x.j = src->x.j;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyUnion *MyUnion_clone(MyUnion *src, Dz1Error *err)
{
	MyUnion *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (MyUnion *)Dz1Calloc(sizeof(MyUnion), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyUnion_delAndSetNull, (void *)&ret);
		if (MyUnion_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnion_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnion_purge(MyUnion *p)
{
	if (!p) return;
	switch(p->present)
	{
	case MyUnionPresent_a:
		break;
	case MyUnionPresent_b:
		break;
	case MyUnionPresent_c:
		break;
	case MyUnionPresent_d:
		break;
	case MyUnionPresent_e:
		Dz1Str_del(p->x.e);
		break;
	case MyUnionPresent_f:
		MyStructList_del(p->x.f);
		break;
	case MyUnionPresent_g:
		break;
	case MyUnionPresent_h:
		break;
	case MyUnionPresent_i:
		break;
	case MyUnionPresent_j:
		break;
	default:
		break;
	}
}

void MyUnion_del(MyUnion *p)
{
	if (!p) return;
	MyUnion_purge(p);
	Dz1Free(p);
}

void MyUnion_dump(MyUnion *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case MyUnionPresent_a:
		Dz1Thread_printf(Dz1T("a = ")); Dz1u8_dump(&p->x.a, tab); 
		break;
	case MyUnionPresent_b:
		Dz1Thread_printf(Dz1T("b = ")); Dz1u16_dump(&p->x.b, tab); 
		break;
	case MyUnionPresent_c:
		Dz1Thread_printf(Dz1T("c = ")); Dz1u32_dump(&p->x.c, tab); 
		break;
	case MyUnionPresent_d:
		Dz1Thread_printf(Dz1T("d = ")); Dz1u64_dump(&p->x.d, tab); 
		break;
	case MyUnionPresent_e:
		Dz1Thread_printf(Dz1T("e = ")); Dz1Str_dump(p->x.e, tab); 
		break;
	case MyUnionPresent_f:
		Dz1Thread_printf(Dz1T("f = ")); MyStructList_dump(p->x.f, tab); 
		break;
	case MyUnionPresent_g:
		Dz1Thread_printf(Dz1T("g = ")); Dz1Real64_dump(&p->x.g, tab); 
		break;
	case MyUnionPresent_h:
		Dz1Thread_printf(Dz1T("h = ")); Dz1Real32_dump(&p->x.h, tab); 
		break;
	case MyUnionPresent_i:
		Dz1Thread_printf(Dz1T("i = %s(%d)\n"), MyEnumStr(p->x.i), p->x.i);
		break;
	case MyUnionPresent_j:
		Dz1Thread_printf(Dz1T("j = ")); MyExternHz_dump(&p->x.j, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// MyUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionList
static Dz1Error MyUnionList_add(MyUnionList *p, MyUnion *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct MyUnionListMkArrArg
{
	MyUnion **arr;
	unsigned int idx;
} MyUnionListMkArrArg;

static Dz1Error _MyUnionList_get_array(void *ptr, MyUnion *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionListMkArrArg *arg = (MyUnionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static MyUnion **MyUnionList_get_array(MyUnionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	MyUnion **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (MyUnion **)Dz1Calloc(sizeof(MyUnion *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		MyUnionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _MyUnionList_get_array, (void *)&arg);
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

static Dz1Error MyUnionList_travelForward(MyUnionList *p, Dz1Error (*func)(void *ptr, MyUnion *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error MyUnionList_travelBackward(MyUnionList *p, Dz1Error (*func)(void *ptr, MyUnion *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int MyUnionList_count(MyUnionList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

MyUnionList *MyUnionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionList *ret = (MyUnionList *)Dz1Calloc(sizeof(MyUnionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)MyUnion_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = MyUnionList_count;
			ret->travel = MyUnionList_travelForward;
			ret->travelForward = MyUnionList_travelForward;
			ret->travelBackward = MyUnionList_travelBackward;
			ret->get_array = MyUnionList_get_array;
			ret->add = MyUnionList_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _MyUnionList_clone(void *ptr, MyUnion *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyUnionList *p = (MyUnionList *)ptr;
	MyUnion *cloned = MyUnion_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

MyUnionList *MyUnionList_clone(MyUnionList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyUnionList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = MyUnionList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(MyUnionList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_MyUnionList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyUnionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void MyUnionList_purge(MyUnionList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void MyUnionList_del(MyUnionList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _MyUnionList_dump(void *ptr, MyUnion *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); MyUnion_dump(p, tab);
	return err;
}

void MyUnionList_dump(MyUnionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _MyUnionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// MyUnionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyComponent
MyComponent *MyComponent_new(u32_t a, 
							 MyStruct *b, 
							 MyUnion *c, 
							 real64_t f, 
							 real32_t g, 
							 MyEnum h, 
							 MyExternHz i, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	MyComponent *__internal_ret = (MyComponent *)Dz1Calloc(sizeof(MyComponent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(MyComponent_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->d = MyStructList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->e = MyUnionList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->a = a;
			__internal_ret->b = b;
			__internal_ret->c = c;
			__internal_ret->f = f;
			__internal_ret->g = g;
			__internal_ret->h = h;
			__internal_ret->i = i;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyComponent_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t MyComponent_copy(MyComponent *dst, MyComponent *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->b && (dst->b = MyStruct_clone(src->b, errp)) == NULL) ERR_OUT(errp);
	else if (src->c && (dst->c = MyUnion_clone(src->c, errp)) == NULL) ERR_OUT(errp);
	else if (src->d && (dst->d = MyStructList_clone(src->d, errp)) == NULL) ERR_OUT(errp);
	else if (src->e && (dst->e = MyUnionList_clone(src->e, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->a = src->a;
		dst->f = src->f;
		dst->g = src->g;
		dst->h = src->h;
		dst->i = src->i;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

MyComponent *MyComponent_clone(MyComponent *src, Dz1Error *err)
{
	MyComponent *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (MyComponent *)Dz1Calloc(sizeof(MyComponent), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(MyComponent_delAndSetNull, (void *)&dst);
		if (MyComponent_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (MyComponent_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void MyComponent_purge(MyComponent *p)
{
	if (p == NULL) return;
	MyStruct_del(p->b);
	MyUnion_del(p->c);
	MyStructList_del(p->d);
	MyUnionList_del(p->e);
}

void MyComponent_del(MyComponent *p)
{
	if (p == NULL) return;
	MyComponent_purge(p);
	Dz1Free(p);
}

void MyComponent_dump(MyComponent *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("a = ")); Dz1u32_dump(&p->a, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("b = ")); MyStruct_dump(p->b, tab); 
		Dz1Thread_tprintf(tab, Dz1T("c.")); MyUnion_dump(p->c, tab); 
		Dz1Thread_tprintf(tab, Dz1T("d = ")); MyStructList_dump(p->d, tab); 
		Dz1Thread_tprintf(tab, Dz1T("e = ")); MyUnionList_dump(p->e, tab); 
		Dz1Thread_tprintf(tab, Dz1T("f = ")); Dz1Real64_dump(&p->f, tab); 
		Dz1Thread_tprintf(tab, Dz1T("g = ")); Dz1Real32_dump(&p->g, tab); 
		Dz1Thread_tprintf(tab, Dz1T("h = %s(%d)\n"), MyEnumStr(p->h), p->h);
		// _imp_dump
		// _imp_dump : scalar
		Dz1Thread_tprintf(tab, Dz1T("i = ")); MyExternHz_dump(&p->i, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// MyComponent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StringList
static Dz1Error StringList_add(StringList *p, Dz1Str data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct StringListMkArrArg
{
	Dz1Str *arr;
	unsigned int idx;
} StringListMkArrArg;

static Dz1Error _StringList_get_array(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StringListMkArrArg *arg = (StringListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1Str *StringList_get_array(StringList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1Str *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Str *)Dz1Calloc(sizeof(Dz1Str *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		StringListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _StringList_get_array, (void *)&arg);
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

static Dz1Error StringList_travelForward(StringList *p, Dz1Error (*func)(void *ptr, Dz1Str data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error StringList_travelBackward(StringList *p, Dz1Error (*func)(void *ptr, Dz1Str data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int StringList_count(StringList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

StringList *StringList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StringList *ret = (StringList *)Dz1Calloc(sizeof(StringList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StringList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1Str_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = StringList_count;
			ret->travel = StringList_travelForward;
			ret->travelForward = StringList_travelForward;
			ret->travelBackward = StringList_travelBackward;
			ret->get_array = StringList_get_array;
			ret->add = StringList_add;
			ret->cmp = Dz1Str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (StringList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _StringList_clone(void *ptr, Dz1Str data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StringList *p = (StringList *)ptr;
	Dz1Str cloned = Dz1Str_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

StringList *StringList_clone(StringList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	StringList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = StringList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StringList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_StringList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (StringList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void StringList_purge(StringList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void StringList_del(StringList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _StringList_dump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1Str_dump(p, tab);
	return err;
}

void StringList_dump(StringList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _StringList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _StringList_fdump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1Str_fdump(arg->fp, p, tab);
	return err;
}

void StringList_fdump(FILE *fp, StringList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _StringList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// StringList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaDataList
static Dz1Error Asn1MetaDataList_add(Asn1MetaDataList *p, Asn1MetaData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Asn1MetaDataListMkArrArg
{
	Asn1MetaData **arr;
	unsigned int idx;
} Asn1MetaDataListMkArrArg;

static Dz1Error _Asn1MetaDataList_get_array(void *ptr, Asn1MetaData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Asn1MetaDataListMkArrArg *arg = (Asn1MetaDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Asn1MetaData **Asn1MetaDataList_get_array(Asn1MetaDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Asn1MetaData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Asn1MetaData **)Dz1Calloc(sizeof(Asn1MetaData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Asn1MetaDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Asn1MetaDataList_get_array, (void *)&arg);
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

static Dz1Error Asn1MetaDataList_travelForward(Asn1MetaDataList *p, Dz1Error (*func)(void *ptr, Asn1MetaData *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Asn1MetaDataList_travelBackward(Asn1MetaDataList *p, Dz1Error (*func)(void *ptr, Asn1MetaData *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Asn1MetaDataList_count(Asn1MetaDataList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Asn1MetaDataList *Asn1MetaDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Asn1MetaDataList *ret = (Asn1MetaDataList *)Dz1Calloc(sizeof(Asn1MetaDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Asn1MetaDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Asn1MetaData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Asn1MetaDataList_count;
			ret->travel = Asn1MetaDataList_travelForward;
			ret->travelForward = Asn1MetaDataList_travelForward;
			ret->travelBackward = Asn1MetaDataList_travelBackward;
			ret->get_array = Asn1MetaDataList_get_array;
			ret->add = Asn1MetaDataList_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Asn1MetaDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Asn1MetaDataList_purge(Asn1MetaDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Asn1MetaDataList_del(Asn1MetaDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Asn1MetaDataList_dump(void *ptr, Asn1MetaData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Asn1MetaData_dump(p, tab);
	return err;
}

void Asn1MetaDataList_dump(Asn1MetaDataList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Asn1MetaDataList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Asn1MetaDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaData
Asn1MetaData *Asn1MetaData_new(Dz1Str name, Dz1Str value, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Asn1MetaData *__internal_ret = (Asn1MetaData *)Dz1Calloc(sizeof(Asn1MetaData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Asn1MetaData_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if (value && (__internal_ret->value = Dz1Str_clone(value, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->elements = Asn1MetaDataList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Asn1MetaData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Asn1MetaData_purge(Asn1MetaData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1Str_del(p->value);
	Asn1MetaDataList_del(p->elements);
}

void Asn1MetaData_del(Asn1MetaData *p)
{
	if (p == NULL) return;
	Asn1MetaData_purge(p);
	Dz1Free(p);
}

void Asn1MetaData_dump(Asn1MetaData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("value = ")); Dz1Str_dump(p->value, tab); 
		Dz1Thread_tprintf(tab, Dz1T("elements = ")); Asn1MetaDataList_dump(p->elements, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Asn1MetaData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaDataModule
Asn1MetaDataModule *Asn1MetaDataModule_new(Dz1Str name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Asn1MetaDataModule *__internal_ret = (Asn1MetaDataModule *)Dz1Calloc(sizeof(Asn1MetaDataModule), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Asn1MetaDataModule_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->elements = Asn1MetaDataList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Asn1MetaDataModule_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Asn1MetaDataModule_purge(Asn1MetaDataModule *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Asn1MetaDataList_del(p->elements);
}

void Asn1MetaDataModule_del(Asn1MetaDataModule *p)
{
	if (p == NULL) return;
	Asn1MetaDataModule_purge(p);
	Dz1Free(p);
}

void Asn1MetaDataModule_dump(Asn1MetaDataModule *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("elements = ")); Asn1MetaDataList_dump(p->elements, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Asn1MetaDataModule
////////////////////////////////////////////////////////////////////////////////

