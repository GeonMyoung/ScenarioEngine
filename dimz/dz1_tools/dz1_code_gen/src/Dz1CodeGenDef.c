////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1CodeGenDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenSetupEntry
Dz1CodeGenSetupEntry *Dz1CodeGenSetupEntry_new(str_t label, bool_t useThisArg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenSetupEntry *__internal_ret = (Dz1CodeGenSetupEntry *)Dz1Calloc(sizeof(Dz1CodeGenSetupEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1CodeGenSetupEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (label && (__internal_ret->label = dz1_built_in_str_clone(label, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->useThisArg = useThisArg;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenSetupEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1CodeGenSetupEntry_purge(Dz1CodeGenSetupEntry *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->label);
}

void Dz1CodeGenSetupEntry_del(Dz1CodeGenSetupEntry *p)
{
	if (p == NULL) return;
	Dz1CodeGenSetupEntry_purge(p);
	Dz1Free(p);
}

// Dz1CodeGenSetupEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenSetupTable
Dz1CodeGenSetupTable *Dz1CodeGenSetupTable_new(s32_t type, 
											   Dz1CodeGenSetupEntry *setup, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenSetupTable *__internal_ret = (Dz1CodeGenSetupTable *)Dz1Calloc(sizeof(Dz1CodeGenSetupTable), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1CodeGenSetupTable_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		__internal_ret->setup = setup;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenSetupTable_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1CodeGenSetupTable_purge(Dz1CodeGenSetupTable *p)
{
	if (p == NULL) return;
	Dz1CodeGenSetupEntry_del(p->setup);
}

void Dz1CodeGenSetupTable_del(Dz1CodeGenSetupTable *p)
{
	if (p == NULL) return;
	Dz1CodeGenSetupTable_purge(p);
	Dz1Free(p);
}

// Dz1CodeGenSetupTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenReplaceEnt
Dz1CodeGenReplaceEnt *Dz1CodeGenReplaceEnt_new(str_t target, str_t replace, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenReplaceEnt *__internal_ret = (Dz1CodeGenReplaceEnt *)Dz1Calloc(sizeof(Dz1CodeGenReplaceEnt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceEnt_delAndSetNull, (void *)&__internal_ret);
		
		if (target && (__internal_ret->target = dz1_built_in_str_clone(target, errp)) == NULL) ERR_OUT(errp);
		else if (replace && (__internal_ret->replace = dz1_built_in_str_clone(replace, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenReplaceEnt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1CodeGenReplaceEnt_copy(Dz1CodeGenReplaceEnt *dst, Dz1CodeGenReplaceEnt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->target && (dst->target = dz1_built_in_str_clone(src->target, errp)) == NULL) ERR_OUT(errp);
	else if (src->replace && (dst->replace = dz1_built_in_str_clone(src->replace, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1CodeGenReplaceEnt *Dz1CodeGenReplaceEnt_clone(Dz1CodeGenReplaceEnt *src, Dz1Error *err)
{
	Dz1CodeGenReplaceEnt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1CodeGenReplaceEnt *)Dz1Calloc(sizeof(Dz1CodeGenReplaceEnt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceEnt_delAndSetNull, (void *)&dst);
		if (Dz1CodeGenReplaceEnt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenReplaceEnt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1CodeGenReplaceEnt_purge(Dz1CodeGenReplaceEnt *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->target);
	dz1_built_in_str_del(p->replace);
}

void Dz1CodeGenReplaceEnt_del(Dz1CodeGenReplaceEnt *p)
{
	if (p == NULL) return;
	Dz1CodeGenReplaceEnt_purge(p);
	Dz1Free(p);
}

void Dz1CodeGenReplaceEnt_dump(Dz1CodeGenReplaceEnt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("target = ")); dz1_built_in_str_dump(p->target, tab); 
		Dz1Thread_tprintf(tab, Dz1T("replace = ")); dz1_built_in_str_dump(p->replace, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1CodeGenReplaceEnt_cmp(Dz1CodeGenReplaceEnt *a, Dz1CodeGenReplaceEnt *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->target == NULL && b->target == NULL) ret = 0;
	else if (a->target == NULL /*&& b->target != NULL*/) ret = -1;
	else if (/*a->target != NULL &&*/ b->target == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->target, b->target)) != 0) { }
	return ret;
}
// Dz1CodeGenReplaceEnt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenReplaceList
static Dz1Error Dz1CodeGenReplaceList_add(Dz1CodeGenReplaceList *p, Dz1CodeGenReplaceEnt *data)
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

static bool_t Dz1CodeGenReplaceList_remove(Dz1CodeGenReplaceList *p, Dz1CodeGenReplaceEnt *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1CodeGenReplaceEnt *Dz1CodeGenReplaceList_extract(Dz1CodeGenReplaceList *p, Dz1CodeGenReplaceEnt *key)
{
	return (Dz1CodeGenReplaceEnt *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1CodeGenReplaceListMkArrArg
{
	Dz1CodeGenReplaceEnt **arr;
	unsigned int idx;
} Dz1CodeGenReplaceListMkArrArg;

static Dz1Error _Dz1CodeGenReplaceList_get_array(void *ptr, Dz1CodeGenReplaceEnt *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CodeGenReplaceListMkArrArg *arg = (Dz1CodeGenReplaceListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1CodeGenReplaceEnt **Dz1CodeGenReplaceList_get_array(Dz1CodeGenReplaceList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1CodeGenReplaceEnt **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1CodeGenReplaceEnt **)Dz1Calloc(sizeof(Dz1CodeGenReplaceEnt *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1CodeGenReplaceListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1CodeGenReplaceList_get_array, (void *)&arg);
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

static Dz1Error Dz1CodeGenReplaceList_travelForward(Dz1CodeGenReplaceList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenReplaceEnt *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1CodeGenReplaceList_travelBackward(Dz1CodeGenReplaceList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenReplaceEnt *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1CodeGenReplaceEnt *Dz1CodeGenReplaceList_find(Dz1CodeGenReplaceList *p, Dz1CodeGenReplaceEnt *key)
{
	return (Dz1CodeGenReplaceEnt *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1CodeGenReplaceList_count(Dz1CodeGenReplaceList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1CodeGenReplaceList *Dz1CodeGenReplaceList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenReplaceList *ret = (Dz1CodeGenReplaceList *)Dz1Calloc(sizeof(Dz1CodeGenReplaceList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1CodeGenReplaceEnt_cmp,
				(Dz1DelFunc)Dz1CodeGenReplaceEnt_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1CodeGenReplaceList_count;
			ret->travel = Dz1CodeGenReplaceList_travelForward;
			ret->travelForward = Dz1CodeGenReplaceList_travelForward;
			ret->travelBackward = Dz1CodeGenReplaceList_travelBackward;
			ret->get_array = Dz1CodeGenReplaceList_get_array;
			ret->add = Dz1CodeGenReplaceList_add;
			ret->remove = Dz1CodeGenReplaceList_remove;
			ret->find = Dz1CodeGenReplaceList_find;
			ret->extract = Dz1CodeGenReplaceList_extract;
			ret->cmp = Dz1CodeGenReplaceEnt_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1CodeGenReplaceList_clone(void *ptr, Dz1CodeGenReplaceEnt *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CodeGenReplaceList *p = (Dz1CodeGenReplaceList *)ptr;
	Dz1CodeGenReplaceEnt *cloned = Dz1CodeGenReplaceEnt_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1CodeGenReplaceList *Dz1CodeGenReplaceList_clone(Dz1CodeGenReplaceList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenReplaceList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1CodeGenReplaceList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenReplaceList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1CodeGenReplaceList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenReplaceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1CodeGenReplaceList_purge(Dz1CodeGenReplaceList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1CodeGenReplaceList_del(Dz1CodeGenReplaceList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1CodeGenReplaceList_dump(void *ptr, Dz1CodeGenReplaceEnt *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1CodeGenReplaceEnt_dump(p, tab);
	return err;
}

void Dz1CodeGenReplaceList_dump(Dz1CodeGenReplaceList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1CodeGenReplaceList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1CodeGenReplaceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListType
static struct Dz1CodeGenListTypeMapA
{
	str_t str;
	Dz1CodeGenListType v;
} Dz1CodeGenListTypeMapA[] =
{
	{ (char *)"addNode", Dz1CodeGenListType_addNode },
	{ (char *)"codec", Dz1CodeGenListType_codec },
	{ (char *)"stream", Dz1CodeGenListType_stream },
	{ (char *)"mfc_list_h", Dz1CodeGenListType_mfc_list_h },
	{ (char *)"mfc_list_cpp", Dz1CodeGenListType_mfc_list_cpp },
	{ (char *)"mfc_list_base", Dz1CodeGenListType_mfc_list_base },
	{ (char *)"mfc_list_changed", Dz1CodeGenListType_mfc_list_changed },
	{ (char *)"mfc_list_clicked", Dz1CodeGenListType_mfc_list_clicked },
	{ NULL, Dz1CodeGenListType_max }
};

str_t Dz1CodeGenListTypeStrA(Dz1CodeGenListType v)
{
	struct Dz1CodeGenListTypeMapA *i = NULL;
	for (i = Dz1CodeGenListTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenListType Dz1CodeGenListTypeFromStrA(str_t str)
{
	struct Dz1CodeGenListTypeMapA *i = NULL;
	for (i = Dz1CodeGenListTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenListType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1CodeGenListTypeMapW
{
	wstr_t str;
	Dz1CodeGenListType v;
} Dz1CodeGenListTypeMapW[] =
{
	{ (wchar_t *)L"addNode", Dz1CodeGenListType_addNode },
	{ (wchar_t *)L"codec", Dz1CodeGenListType_codec },
	{ (wchar_t *)L"stream", Dz1CodeGenListType_stream },
	{ (wchar_t *)L"mfc_list_h", Dz1CodeGenListType_mfc_list_h },
	{ (wchar_t *)L"mfc_list_cpp", Dz1CodeGenListType_mfc_list_cpp },
	{ (wchar_t *)L"mfc_list_base", Dz1CodeGenListType_mfc_list_base },
	{ (wchar_t *)L"mfc_list_changed", Dz1CodeGenListType_mfc_list_changed },
	{ (wchar_t *)L"mfc_list_clicked", Dz1CodeGenListType_mfc_list_clicked },
	{ NULL, Dz1CodeGenListType_max }
};

wstr_t Dz1CodeGenListTypeStrW(Dz1CodeGenListType v)
{
	struct Dz1CodeGenListTypeMapW *i = NULL;
	for (i = Dz1CodeGenListTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenListType Dz1CodeGenListTypeFromStrW(wstr_t str)
{
	struct Dz1CodeGenListTypeMapW *i = NULL;
	for (i = Dz1CodeGenListTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenListType_max;
}
#endif // UNIX_SYSTEM

Dz1CodeGenListType *Dz1CodeGenListType_new(Dz1CodeGenListType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenListType *__internal_ret = (Dz1CodeGenListType *)Dz1Calloc(sizeof(Dz1CodeGenListType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1CodeGenListType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenStubType
static struct Dz1CodeGenStubTypeMapA
{
	str_t str;
	Dz1CodeGenStubType v;
} Dz1CodeGenStubTypeMapA[] =
{
	{ (char *)"creation", Dz1CodeGenStubType_creation },
	{ (char *)"s_api", Dz1CodeGenStubType_s_api },
	{ (char *)"s_codec", Dz1CodeGenStubType_s_codec },
	{ (char *)"u_codec", Dz1CodeGenStubType_u_codec },
	{ (char *)"v_codec", Dz1CodeGenStubType_v_codec },
	{ (char *)"codec_conv", Dz1CodeGenStubType_codec_conv },
	{ (char *)"codec_test", Dz1CodeGenStubType_codec_test },
	{ (char *)"s_stream", Dz1CodeGenStubType_s_stream },
	{ (char *)"u_stream", Dz1CodeGenStubType_u_stream },
	{ (char *)"v_stream", Dz1CodeGenStubType_v_stream },
	{ (char *)"stream_conv", Dz1CodeGenStubType_stream_conv },
	{ (char *)"stream_test", Dz1CodeGenStubType_stream_test },
	{ (char *)"test_gen", Dz1CodeGenStubType_test_gen },
	{ (char *)"test_ugen", Dz1CodeGenStubType_test_ugen },
	{ (char *)"mfc_enum_combo_h", Dz1CodeGenStubType_mfc_enum_combo_h },
	{ NULL, Dz1CodeGenStubType_max }
};

str_t Dz1CodeGenStubTypeStrA(Dz1CodeGenStubType v)
{
	struct Dz1CodeGenStubTypeMapA *i = NULL;
	for (i = Dz1CodeGenStubTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenStubType Dz1CodeGenStubTypeFromStrA(str_t str)
{
	struct Dz1CodeGenStubTypeMapA *i = NULL;
	for (i = Dz1CodeGenStubTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenStubType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1CodeGenStubTypeMapW
{
	wstr_t str;
	Dz1CodeGenStubType v;
} Dz1CodeGenStubTypeMapW[] =
{
	{ (wchar_t *)L"creation", Dz1CodeGenStubType_creation },
	{ (wchar_t *)L"s_api", Dz1CodeGenStubType_s_api },
	{ (wchar_t *)L"s_codec", Dz1CodeGenStubType_s_codec },
	{ (wchar_t *)L"u_codec", Dz1CodeGenStubType_u_codec },
	{ (wchar_t *)L"v_codec", Dz1CodeGenStubType_v_codec },
	{ (wchar_t *)L"codec_conv", Dz1CodeGenStubType_codec_conv },
	{ (wchar_t *)L"codec_test", Dz1CodeGenStubType_codec_test },
	{ (wchar_t *)L"s_stream", Dz1CodeGenStubType_s_stream },
	{ (wchar_t *)L"u_stream", Dz1CodeGenStubType_u_stream },
	{ (wchar_t *)L"v_stream", Dz1CodeGenStubType_v_stream },
	{ (wchar_t *)L"stream_conv", Dz1CodeGenStubType_stream_conv },
	{ (wchar_t *)L"stream_test", Dz1CodeGenStubType_stream_test },
	{ (wchar_t *)L"test_gen", Dz1CodeGenStubType_test_gen },
	{ (wchar_t *)L"test_ugen", Dz1CodeGenStubType_test_ugen },
	{ (wchar_t *)L"mfc_enum_combo_h", Dz1CodeGenStubType_mfc_enum_combo_h },
	{ NULL, Dz1CodeGenStubType_max }
};

wstr_t Dz1CodeGenStubTypeStrW(Dz1CodeGenStubType v)
{
	struct Dz1CodeGenStubTypeMapW *i = NULL;
	for (i = Dz1CodeGenStubTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenStubType Dz1CodeGenStubTypeFromStrW(wstr_t str)
{
	struct Dz1CodeGenStubTypeMapW *i = NULL;
	for (i = Dz1CodeGenStubTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenStubType_max;
}
#endif // UNIX_SYSTEM

Dz1CodeGenStubType *Dz1CodeGenStubType_new(Dz1CodeGenStubType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenStubType *__internal_ret = (Dz1CodeGenStubType *)Dz1Calloc(sizeof(Dz1CodeGenStubType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1CodeGenStubType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenParserType
static struct Dz1CodeGenParserTypeMapA
{
	str_t str;
	Dz1CodeGenParserType v;
} Dz1CodeGenParserTypeMapA[] =
{
	{ (char *)"emitter", Dz1CodeGenParserType_emitter },
	{ (char *)"parser", Dz1CodeGenParserType_parser },
	{ NULL, Dz1CodeGenParserType_max }
};

str_t Dz1CodeGenParserTypeStrA(Dz1CodeGenParserType v)
{
	struct Dz1CodeGenParserTypeMapA *i = NULL;
	for (i = Dz1CodeGenParserTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenParserType Dz1CodeGenParserTypeFromStrA(str_t str)
{
	struct Dz1CodeGenParserTypeMapA *i = NULL;
	for (i = Dz1CodeGenParserTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenParserType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1CodeGenParserTypeMapW
{
	wstr_t str;
	Dz1CodeGenParserType v;
} Dz1CodeGenParserTypeMapW[] =
{
	{ (wchar_t *)L"emitter", Dz1CodeGenParserType_emitter },
	{ (wchar_t *)L"parser", Dz1CodeGenParserType_parser },
	{ NULL, Dz1CodeGenParserType_max }
};

wstr_t Dz1CodeGenParserTypeStrW(Dz1CodeGenParserType v)
{
	struct Dz1CodeGenParserTypeMapW *i = NULL;
	for (i = Dz1CodeGenParserTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenParserType Dz1CodeGenParserTypeFromStrW(wstr_t str)
{
	struct Dz1CodeGenParserTypeMapW *i = NULL;
	for (i = Dz1CodeGenParserTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenParserType_max;
}
#endif // UNIX_SYSTEM

Dz1CodeGenParserType *Dz1CodeGenParserType_new(Dz1CodeGenParserType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenParserType *__internal_ret = (Dz1CodeGenParserType *)Dz1Calloc(sizeof(Dz1CodeGenParserType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1CodeGenParserType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenShellType
static struct Dz1CodeGenShellTypeMapA
{
	str_t str;
	Dz1CodeGenShellType v;
} Dz1CodeGenShellTypeMapA[] =
{
	{ (char *)"root_cmd", Dz1CodeGenShellType_root_cmd },
	{ (char *)"sub_cmd", Dz1CodeGenShellType_sub_cmd },
	{ NULL, Dz1CodeGenShellType_max }
};

str_t Dz1CodeGenShellTypeStrA(Dz1CodeGenShellType v)
{
	struct Dz1CodeGenShellTypeMapA *i = NULL;
	for (i = Dz1CodeGenShellTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenShellType Dz1CodeGenShellTypeFromStrA(str_t str)
{
	struct Dz1CodeGenShellTypeMapA *i = NULL;
	for (i = Dz1CodeGenShellTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenShellType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1CodeGenShellTypeMapW
{
	wstr_t str;
	Dz1CodeGenShellType v;
} Dz1CodeGenShellTypeMapW[] =
{
	{ (wchar_t *)L"root_cmd", Dz1CodeGenShellType_root_cmd },
	{ (wchar_t *)L"sub_cmd", Dz1CodeGenShellType_sub_cmd },
	{ NULL, Dz1CodeGenShellType_max }
};

wstr_t Dz1CodeGenShellTypeStrW(Dz1CodeGenShellType v)
{
	struct Dz1CodeGenShellTypeMapW *i = NULL;
	for (i = Dz1CodeGenShellTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenShellType Dz1CodeGenShellTypeFromStrW(wstr_t str)
{
	struct Dz1CodeGenShellTypeMapW *i = NULL;
	for (i = Dz1CodeGenShellTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenShellType_max;
}
#endif // UNIX_SYSTEM

Dz1CodeGenShellType *Dz1CodeGenShellType_new(Dz1CodeGenShellType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenShellType *__internal_ret = (Dz1CodeGenShellType *)Dz1Calloc(sizeof(Dz1CodeGenShellType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1CodeGenShellType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListCtrlObjectParent
Dz1CodeGenListCtrlObjectParent *Dz1CodeGenListCtrlObjectParent_new(Dz1CodeGenListCtrlObjectParent *p/*_ref*/, 
																   str_t instance, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenListCtrlObjectParent *__internal_ret = (Dz1CodeGenListCtrlObjectParent *)Dz1Calloc(sizeof(Dz1CodeGenListCtrlObjectParent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1CodeGenListCtrlObjectParent_delAndSetNull, (void *)&__internal_ret);
		
		if (instance && (__internal_ret->instance = dz1_built_in_str_clone(instance, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->p = p;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenListCtrlObjectParent_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1CodeGenListCtrlObjectParent_purge(Dz1CodeGenListCtrlObjectParent *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->instance);
}

void Dz1CodeGenListCtrlObjectParent_del(Dz1CodeGenListCtrlObjectParent *p)
{
	if (p == NULL) return;
	Dz1CodeGenListCtrlObjectParent_purge(p);
	Dz1Free(p);
}

void Dz1CodeGenListCtrlObjectParent_dump(Dz1CodeGenListCtrlObjectParent *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Recursive member
		// Recursive but address dump
		Dz1Thread_tprintf(tab, Dz1T("p = %p\n"), p->p);
		Dz1Thread_tprintf(tab, Dz1T("instance = ")); dz1_built_in_str_dump(p->instance, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1CodeGenListCtrlObjectParent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListCtrlInstanceMode
static struct Dz1CodeGenListCtrlInstanceModeMapA
{
	str_t str;
	Dz1CodeGenListCtrlInstanceMode v;
} Dz1CodeGenListCtrlInstanceModeMapA[] =
{
	{ (char *)"dot", Dz1CodeGenListCtrlInstanceMode_dot },
	{ (char *)"arrow", Dz1CodeGenListCtrlInstanceMode_arrow },
	{ (char *)"arrowxdot", Dz1CodeGenListCtrlInstanceMode_arrowxdot },
	{ NULL, Dz1CodeGenListCtrlInstanceMode_max }
};

str_t Dz1CodeGenListCtrlInstanceModeStrA(Dz1CodeGenListCtrlInstanceMode v)
{
	struct Dz1CodeGenListCtrlInstanceModeMapA *i = NULL;
	for (i = Dz1CodeGenListCtrlInstanceModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenListCtrlInstanceMode Dz1CodeGenListCtrlInstanceModeFromStrA(str_t str)
{
	struct Dz1CodeGenListCtrlInstanceModeMapA *i = NULL;
	for (i = Dz1CodeGenListCtrlInstanceModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenListCtrlInstanceMode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1CodeGenListCtrlInstanceModeMapW
{
	wstr_t str;
	Dz1CodeGenListCtrlInstanceMode v;
} Dz1CodeGenListCtrlInstanceModeMapW[] =
{
	{ (wchar_t *)L"dot", Dz1CodeGenListCtrlInstanceMode_dot },
	{ (wchar_t *)L"arrow", Dz1CodeGenListCtrlInstanceMode_arrow },
	{ (wchar_t *)L"arrowxdot", Dz1CodeGenListCtrlInstanceMode_arrowxdot },
	{ NULL, Dz1CodeGenListCtrlInstanceMode_max }
};

wstr_t Dz1CodeGenListCtrlInstanceModeStrW(Dz1CodeGenListCtrlInstanceMode v)
{
	struct Dz1CodeGenListCtrlInstanceModeMapW *i = NULL;
	for (i = Dz1CodeGenListCtrlInstanceModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1CodeGenListCtrlInstanceMode Dz1CodeGenListCtrlInstanceModeFromStrW(wstr_t str)
{
	struct Dz1CodeGenListCtrlInstanceModeMapW *i = NULL;
	for (i = Dz1CodeGenListCtrlInstanceModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1CodeGenListCtrlInstanceMode_max;
}
#endif // UNIX_SYSTEM

Dz1CodeGenListCtrlInstanceMode *Dz1CodeGenListCtrlInstanceMode_new(Dz1CodeGenListCtrlInstanceMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenListCtrlInstanceMode *__internal_ret = (Dz1CodeGenListCtrlInstanceMode *)Dz1Calloc(sizeof(Dz1CodeGenListCtrlInstanceMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1CodeGenListCtrlInstanceMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListColumn
Dz1CodeGenListColumn *Dz1CodeGenListColumn_new(u32_t order, 
											   str_t name, 
											   ObjectInfo *type, 
											   str_t instance, 
											   Dz1CodeGenListCtrlInstanceMode mode, 
											   Dz1CodeGenListCtrlObjectParent *parent, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenListColumn *__internal_ret = (Dz1CodeGenListColumn *)Dz1Calloc(sizeof(Dz1CodeGenListColumn), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1CodeGenListColumn_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = dz1_built_in_str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if (instance && (__internal_ret->instance = dz1_built_in_str_clone(instance, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->order = order;
			__internal_ret->type = type;
			__internal_ret->mode = mode;
			__internal_ret->parent = parent;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenListColumn_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1CodeGenListColumn_purge(Dz1CodeGenListColumn *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->name);
	ObjectInfo_del(p->type);
	dz1_built_in_str_del(p->instance);
	Dz1CodeGenListCtrlObjectParent_del(p->parent);
}

void Dz1CodeGenListColumn_del(Dz1CodeGenListColumn *p)
{
	if (p == NULL) return;
	Dz1CodeGenListColumn_purge(p);
	Dz1Free(p);
}

void Dz1CodeGenListColumn_dump(Dz1CodeGenListColumn *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("order = ")); Dz1u32_dump(&p->order, tab); 
		Dz1Thread_tprintf(tab, Dz1T("name = ")); dz1_built_in_str_dump(p->name, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("type = ")); ObjectInfo_dump(p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("instance = ")); dz1_built_in_str_dump(p->instance, tab); 
		Dz1Thread_tprintf(tab, Dz1T("mode = %s(%d)\n"), Dz1CodeGenListCtrlInstanceModeStr(p->mode), p->mode);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("parent = ")); Dz1CodeGenListCtrlObjectParent_dump(p->parent, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1CodeGenListColumn_cmp(Dz1CodeGenListColumn *a, Dz1CodeGenListColumn *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->order, &b->order)) != 0) { }
	return ret;
}
// Dz1CodeGenListColumn
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CodeGenListColumnList
static Dz1Error Dz1CodeGenListColumnList_add(Dz1CodeGenListColumnList *p, Dz1CodeGenListColumn *data)
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

static bool_t Dz1CodeGenListColumnList_remove(Dz1CodeGenListColumnList *p, Dz1CodeGenListColumn *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1CodeGenListColumn *Dz1CodeGenListColumnList_extract(Dz1CodeGenListColumnList *p, Dz1CodeGenListColumn *key)
{
	return (Dz1CodeGenListColumn *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1CodeGenListColumnListMkArrArg
{
	Dz1CodeGenListColumn **arr;
	unsigned int idx;
} Dz1CodeGenListColumnListMkArrArg;

static Dz1Error _Dz1CodeGenListColumnList_get_array(void *ptr, Dz1CodeGenListColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CodeGenListColumnListMkArrArg *arg = (Dz1CodeGenListColumnListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1CodeGenListColumn **Dz1CodeGenListColumnList_get_array(Dz1CodeGenListColumnList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1CodeGenListColumn **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1CodeGenListColumn **)Dz1Calloc(sizeof(Dz1CodeGenListColumn *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1CodeGenListColumnListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1CodeGenListColumnList_get_array, (void *)&arg);
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

static Dz1Error Dz1CodeGenListColumnList_travelForward(Dz1CodeGenListColumnList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenListColumn *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1CodeGenListColumnList_travelBackward(Dz1CodeGenListColumnList *p, Dz1Error (*func)(void *ptr, Dz1CodeGenListColumn *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1CodeGenListColumn *Dz1CodeGenListColumnList_find(Dz1CodeGenListColumnList *p, Dz1CodeGenListColumn *key)
{
	return (Dz1CodeGenListColumn *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1CodeGenListColumnList_count(Dz1CodeGenListColumnList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1CodeGenListColumnList *Dz1CodeGenListColumnList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1CodeGenListColumnList *ret = (Dz1CodeGenListColumnList *)Dz1Calloc(sizeof(Dz1CodeGenListColumnList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenListColumnList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1CodeGenListColumn_cmp,
				(Dz1DelFunc)Dz1CodeGenListColumn_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1CodeGenListColumnList_count;
			ret->travel = Dz1CodeGenListColumnList_travelForward;
			ret->travelForward = Dz1CodeGenListColumnList_travelForward;
			ret->travelBackward = Dz1CodeGenListColumnList_travelBackward;
			ret->get_array = Dz1CodeGenListColumnList_get_array;
			ret->add = Dz1CodeGenListColumnList_add;
			ret->remove = Dz1CodeGenListColumnList_remove;
			ret->find = Dz1CodeGenListColumnList_find;
			ret->extract = Dz1CodeGenListColumnList_extract;
			ret->cmp = Dz1CodeGenListColumn_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CodeGenListColumnList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1CodeGenListColumnList_purge(Dz1CodeGenListColumnList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1CodeGenListColumnList_del(Dz1CodeGenListColumnList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1CodeGenListColumnList_dump(void *ptr, Dz1CodeGenListColumn *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1CodeGenListColumn_dump(p, tab);
	return err;
}

void Dz1CodeGenListColumnList_dump(Dz1CodeGenListColumnList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1CodeGenListColumnList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1CodeGenListColumnList
////////////////////////////////////////////////////////////////////////////////

