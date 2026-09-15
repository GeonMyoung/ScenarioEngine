////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_asn1_types_def.h"

#include "dz1_asn1_typedescr_def.h"
////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TagClass
static struct Dz1Asn1TagClassMapA
{
	str_t str;
	Dz1Asn1TagClass v;
} Dz1Asn1TagClassMapA[] =
{
	{ (char *)"universal", Dz1Asn1TagClass_universal },
	{ (char *)"application", Dz1Asn1TagClass_application },
	{ (char *)"context_specific", Dz1Asn1TagClass_context_specific },
	{ (char *)"privated", Dz1Asn1TagClass_privated },
	{ NULL, Dz1Asn1TagClass_max }
};

str_t Dz1Asn1TagClassStrA(Dz1Asn1TagClass v)
{
	struct Dz1Asn1TagClassMapA *i = NULL;
	for (i = Dz1Asn1TagClassMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1TagClass Dz1Asn1TagClassFromStrA(str_t str)
{
	struct Dz1Asn1TagClassMapA *i = NULL;
	for (i = Dz1Asn1TagClassMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1TagClass_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1TagClassMapW
{
	wstr_t str;
	Dz1Asn1TagClass v;
} Dz1Asn1TagClassMapW[] =
{
	{ (wchar_t *)L"universal", Dz1Asn1TagClass_universal },
	{ (wchar_t *)L"application", Dz1Asn1TagClass_application },
	{ (wchar_t *)L"context_specific", Dz1Asn1TagClass_context_specific },
	{ (wchar_t *)L"privated", Dz1Asn1TagClass_privated },
	{ NULL, Dz1Asn1TagClass_max }
};

wstr_t Dz1Asn1TagClassStrW(Dz1Asn1TagClass v)
{
	struct Dz1Asn1TagClassMapW *i = NULL;
	for (i = Dz1Asn1TagClassMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1TagClass Dz1Asn1TagClassFromStrW(wstr_t str)
{
	struct Dz1Asn1TagClassMapW *i = NULL;
	for (i = Dz1Asn1TagClassMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1TagClass_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1TagClass *Dz1Asn1TagClass_new(Dz1Asn1TagClass *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1TagClass *__internal_ret = (Dz1Asn1TagClass *)Dz1Calloc(sizeof(Dz1Asn1TagClass), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1Asn1TagClassA_dump(Dz1Asn1TagClass *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1TagClassStrA(*v));
}
void Dz1Asn1TagClassA_fdump(FILE *fp, Dz1Asn1TagClass *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", Dz1Asn1TagClassStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1TagClassW_dump(Dz1Asn1TagClass *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1TagClassStrW(*v));
}
void Dz1Asn1TagClassW_fdump(FILE *fp, Dz1Asn1TagClass *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", Dz1Asn1TagClassStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1TagClass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TagFlag
static struct Dz1Asn1TagFlagMapA
{
	str_t str;
	Dz1Asn1TagFlag v;
} Dz1Asn1TagFlagMapA[] =
{
	{ (char *)"variable", Dz1Asn1TagFlag_variable },
	{ (char *)"primitive", Dz1Asn1TagFlag_primitive },
	{ (char *)"construct", Dz1Asn1TagFlag_construct },
	{ NULL, Dz1Asn1TagFlag_max }
};

str_t Dz1Asn1TagFlagStrA(Dz1Asn1TagFlag v)
{
	struct Dz1Asn1TagFlagMapA *i = NULL;
	for (i = Dz1Asn1TagFlagMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1TagFlag Dz1Asn1TagFlagFromStrA(str_t str)
{
	struct Dz1Asn1TagFlagMapA *i = NULL;
	for (i = Dz1Asn1TagFlagMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1TagFlag_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1TagFlagMapW
{
	wstr_t str;
	Dz1Asn1TagFlag v;
} Dz1Asn1TagFlagMapW[] =
{
	{ (wchar_t *)L"variable", Dz1Asn1TagFlag_variable },
	{ (wchar_t *)L"primitive", Dz1Asn1TagFlag_primitive },
	{ (wchar_t *)L"construct", Dz1Asn1TagFlag_construct },
	{ NULL, Dz1Asn1TagFlag_max }
};

wstr_t Dz1Asn1TagFlagStrW(Dz1Asn1TagFlag v)
{
	struct Dz1Asn1TagFlagMapW *i = NULL;
	for (i = Dz1Asn1TagFlagMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1TagFlag Dz1Asn1TagFlagFromStrW(wstr_t str)
{
	struct Dz1Asn1TagFlagMapW *i = NULL;
	for (i = Dz1Asn1TagFlagMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1TagFlag_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1TagFlag *Dz1Asn1TagFlag_new(Dz1Asn1TagFlag *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1TagFlag *__internal_ret = (Dz1Asn1TagFlag *)Dz1Calloc(sizeof(Dz1Asn1TagFlag), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1TagFlag
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Tag
Dz1Asn1Tag *Dz1Asn1Tag_new(Dz1Asn1TagClass cls, Dz1Asn1TagFlag flag, u64_t numb, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1Tag *__internal_ret = (Dz1Asn1Tag *)Dz1Calloc(sizeof(Dz1Asn1Tag), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1Tag_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cls = cls;
		__internal_ret->flag = flag;
		__internal_ret->numb = numb;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1Tag_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1Asn1Tag_copy(Dz1Asn1Tag *dst, Dz1Asn1Tag *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->cls = src->cls;
		dst->flag = src->flag;
		dst->numb = src->numb;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1Asn1Tag *Dz1Asn1Tag_clone(Dz1Asn1Tag *src, Dz1Error *err)
{
	Dz1Asn1Tag *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1Asn1Tag *)Dz1Calloc(sizeof(Dz1Asn1Tag), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1Tag_delAndSetNull, (void *)&dst);
		if (Dz1Asn1Tag_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1Tag_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1Asn1Tag_purge(Dz1Asn1Tag *p)
{
	if (p == NULL) return;
}

void Dz1Asn1Tag_del(Dz1Asn1Tag *p)
{
	if (p == NULL) return;
	Dz1Asn1Tag_purge(p);
	Dz1Free(p);
}

int Dz1Asn1Tag_cmp(Dz1Asn1Tag *a, Dz1Asn1Tag *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = (int)(a->cls - b->cls)) != 0) { }
	else if ((ret = Dz1u64_cmp(&a->numb, &b->numb)) != 0) { }
	return ret;
}
// Dz1Asn1Tag
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TagOpt
static struct Dz1Asn1TagOptMapA
{
	str_t str;
	Dz1Asn1TagOpt v;
} Dz1Asn1TagOptMapA[] =
{
	{ (char *)"implicit", Dz1Asn1TagOpt_implicit },
	{ (char *)"explicit", Dz1Asn1TagOpt_explicit },
	{ NULL, Dz1Asn1TagOpt_max }
};

str_t Dz1Asn1TagOptStrA(Dz1Asn1TagOpt v)
{
	struct Dz1Asn1TagOptMapA *i = NULL;
	for (i = Dz1Asn1TagOptMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1TagOpt Dz1Asn1TagOptFromStrA(str_t str)
{
	struct Dz1Asn1TagOptMapA *i = NULL;
	for (i = Dz1Asn1TagOptMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1TagOpt_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1TagOptMapW
{
	wstr_t str;
	Dz1Asn1TagOpt v;
} Dz1Asn1TagOptMapW[] =
{
	{ (wchar_t *)L"implicit", Dz1Asn1TagOpt_implicit },
	{ (wchar_t *)L"explicit", Dz1Asn1TagOpt_explicit },
	{ NULL, Dz1Asn1TagOpt_max }
};

wstr_t Dz1Asn1TagOptStrW(Dz1Asn1TagOpt v)
{
	struct Dz1Asn1TagOptMapW *i = NULL;
	for (i = Dz1Asn1TagOptMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1TagOpt Dz1Asn1TagOptFromStrW(wstr_t str)
{
	struct Dz1Asn1TagOptMapW *i = NULL;
	for (i = Dz1Asn1TagOptMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1TagOpt_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1TagOpt *Dz1Asn1TagOpt_new(Dz1Asn1TagOpt *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1TagOpt *__internal_ret = (Dz1Asn1TagOpt *)Dz1Calloc(sizeof(Dz1Asn1TagOpt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1Asn1TagOptA_dump(Dz1Asn1TagOpt *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1TagOptStrA(*v));
}
void Dz1Asn1TagOptA_fdump(FILE *fp, Dz1Asn1TagOpt *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", Dz1Asn1TagOptStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1TagOptW_dump(Dz1Asn1TagOpt *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1TagOptStrW(*v));
}
void Dz1Asn1TagOptW_fdump(FILE *fp, Dz1Asn1TagOpt *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", Dz1Asn1TagOptStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1TagOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenTypeEntry
Dz1Asn1WipOpenTypeEntry *Dz1Asn1WipOpenTypeEntry_new(u32_t order, 
													 Dz1Asn1WipOpenType *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipOpenTypeEntry *__internal_ret = (Dz1Asn1WipOpenTypeEntry *)Dz1Calloc(sizeof(Dz1Asn1WipOpenTypeEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOpenTypeEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->order = order;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipOpenTypeEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1WipOpenTypeEntry_purge(Dz1Asn1WipOpenTypeEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1WipOpenType_del(p->data);
}

void Dz1Asn1WipOpenTypeEntry_del(Dz1Asn1WipOpenTypeEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1WipOpenTypeEntry_purge(p);
	Dz1Free(p);
}

void Dz1Asn1WipOpenTypeEntryA_dump(Dz1Asn1WipOpenTypeEntry *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "order = "); Dz1u32A_dump(&p->order, tab); 
		// Normal member
		Dz1ThreadA_tprintf(tab, "data = "); Dz1Asn1WipOpenTypeA_dump(p->data, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1WipOpenTypeEntryW_dump(Dz1Asn1WipOpenTypeEntry *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"order = "); Dz1u32W_dump(&p->order, tab); 
		// Normal member
		Dz1ThreadW_tprintf(tab, L"data = "); Dz1Asn1WipOpenTypeW_dump(p->data, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
int Dz1Asn1WipOpenTypeEntry_cmp(Dz1Asn1WipOpenTypeEntry *a, Dz1Asn1WipOpenTypeEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->order, &b->order)) != 0) { }
	return ret;
}
// Dz1Asn1WipOpenTypeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenTypeList
static Dz1Error Dz1Asn1WipOpenTypeList_add(Dz1Asn1WipOpenTypeList *p, Dz1Asn1WipOpenTypeEntry *data)
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

static bool_t Dz1Asn1WipOpenTypeList_remove(Dz1Asn1WipOpenTypeList *p, Dz1Asn1WipOpenTypeEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1Asn1WipOpenTypeEntry *Dz1Asn1WipOpenTypeList_extract(Dz1Asn1WipOpenTypeList *p, Dz1Asn1WipOpenTypeEntry *key)
{
	return (Dz1Asn1WipOpenTypeEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1Asn1WipOpenTypeListMkArrArg
{
	Dz1Asn1WipOpenTypeEntry **arr;
	unsigned int idx;
} Dz1Asn1WipOpenTypeListMkArrArg;

static Dz1Error _Dz1Asn1WipOpenTypeList_get_array(void *ptr, Dz1Asn1WipOpenTypeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1WipOpenTypeListMkArrArg *arg = (Dz1Asn1WipOpenTypeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1Asn1WipOpenTypeEntry **Dz1Asn1WipOpenTypeList_get_array(Dz1Asn1WipOpenTypeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1Asn1WipOpenTypeEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Asn1WipOpenTypeEntry **)Dz1Calloc(sizeof(Dz1Asn1WipOpenTypeEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1WipOpenTypeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1Asn1WipOpenTypeList_get_array, (void *)&arg);
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

static Dz1Error Dz1Asn1WipOpenTypeList_travelForward(Dz1Asn1WipOpenTypeList *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOpenTypeEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1Asn1WipOpenTypeList_travelBackward(Dz1Asn1WipOpenTypeList *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOpenTypeEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Asn1WipOpenTypeEntry *Dz1Asn1WipOpenTypeList_find(Dz1Asn1WipOpenTypeList *p, Dz1Asn1WipOpenTypeEntry *key)
{
	return (Dz1Asn1WipOpenTypeEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1Asn1WipOpenTypeList_count(Dz1Asn1WipOpenTypeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1Asn1WipOpenTypeList *Dz1Asn1WipOpenTypeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipOpenTypeList *ret = (Dz1Asn1WipOpenTypeList *)Dz1Calloc(sizeof(Dz1Asn1WipOpenTypeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOpenTypeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1Asn1WipOpenTypeEntry_cmp,
				(Dz1DelFunc)Dz1Asn1WipOpenTypeEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1Asn1WipOpenTypeList_count;
			ret->travel = Dz1Asn1WipOpenTypeList_travelForward;
			ret->travelForward = Dz1Asn1WipOpenTypeList_travelForward;
			ret->travelBackward = Dz1Asn1WipOpenTypeList_travelBackward;
			ret->get_array = Dz1Asn1WipOpenTypeList_get_array;
			ret->add = Dz1Asn1WipOpenTypeList_add;
			ret->remove = Dz1Asn1WipOpenTypeList_remove;
			ret->find = Dz1Asn1WipOpenTypeList_find;
			ret->extract = Dz1Asn1WipOpenTypeList_extract;
			ret->cmp = Dz1Asn1WipOpenTypeEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipOpenTypeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1WipOpenTypeList_purge(Dz1Asn1WipOpenTypeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1Asn1WipOpenTypeList_del(Dz1Asn1WipOpenTypeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1Asn1WipOpenTypeListA_dump(void *ptr, Dz1Asn1WipOpenTypeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1Asn1WipOpenTypeEntryA_dump(p, tab);
	return err;
}

void Dz1Asn1WipOpenTypeListA_dump(Dz1Asn1WipOpenTypeList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1Asn1WipOpenTypeListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Dz1Asn1WipOpenTypeListW_dump(void *ptr, Dz1Asn1WipOpenTypeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1Asn1WipOpenTypeEntryW_dump(p, tab);
	return err;
}

void Dz1Asn1WipOpenTypeListW_dump(Dz1Asn1WipOpenTypeList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1Asn1WipOpenTypeListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1WipOpenTypeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenDataPresent
static struct Dz1Asn1WipOpenDataPresentMapA
{
	str_t str;
	Dz1Asn1WipOpenDataPresent v;
} Dz1Asn1WipOpenDataPresentMapA[] =
{
	{ (char *)"primitive", Dz1Asn1WipOpenDataPresent_primitive },
	{ (char *)"construct", Dz1Asn1WipOpenDataPresent_construct },
	{ NULL, Dz1Asn1WipOpenDataPresent_max }
};

str_t Dz1Asn1WipOpenDataPresentStrA(Dz1Asn1WipOpenDataPresent v)
{
	struct Dz1Asn1WipOpenDataPresentMapA *i = NULL;
	for (i = Dz1Asn1WipOpenDataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1WipOpenDataPresent Dz1Asn1WipOpenDataPresentFromStrA(str_t str)
{
	struct Dz1Asn1WipOpenDataPresentMapA *i = NULL;
	for (i = Dz1Asn1WipOpenDataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1WipOpenDataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1WipOpenDataPresentMapW
{
	wstr_t str;
	Dz1Asn1WipOpenDataPresent v;
} Dz1Asn1WipOpenDataPresentMapW[] =
{
	{ (wchar_t *)L"primitive", Dz1Asn1WipOpenDataPresent_primitive },
	{ (wchar_t *)L"construct", Dz1Asn1WipOpenDataPresent_construct },
	{ NULL, Dz1Asn1WipOpenDataPresent_max }
};

wstr_t Dz1Asn1WipOpenDataPresentStrW(Dz1Asn1WipOpenDataPresent v)
{
	struct Dz1Asn1WipOpenDataPresentMapW *i = NULL;
	for (i = Dz1Asn1WipOpenDataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1WipOpenDataPresent Dz1Asn1WipOpenDataPresentFromStrW(wstr_t str)
{
	struct Dz1Asn1WipOpenDataPresentMapW *i = NULL;
	for (i = Dz1Asn1WipOpenDataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1WipOpenDataPresent_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1WipOpenDataPresent *Dz1Asn1WipOpenDataPresent_new(Dz1Asn1WipOpenDataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipOpenDataPresent *__internal_ret = (Dz1Asn1WipOpenDataPresent *)Dz1Calloc(sizeof(Dz1Asn1WipOpenDataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1Asn1WipOpenDataPresentA_dump(Dz1Asn1WipOpenDataPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1WipOpenDataPresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1WipOpenDataPresentW_dump(Dz1Asn1WipOpenDataPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1WipOpenDataPresentStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1WipOpenDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenData
Dz1Asn1WipOpenData *Dz1Asn1WipOpenData_new(Dz1Asn1WipOpenDataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipOpenData *ret = (Dz1Asn1WipOpenData *)Dz1Calloc(sizeof(Dz1Asn1WipOpenData), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOpenData_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1Asn1WipOpenDataPresent_primitive:
			// _U_imp_clone
			if (ptr != NULL) ret->x.primitive = (Dz1ElasticBuf *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipOpenDataPresent_construct:
			// _U_cst_clone
			if (ptr != NULL) ret->x.construct = (Dz1Asn1WipOpenTypeList *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipOpenDataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipOpenData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1WipOpenData_purge(Dz1Asn1WipOpenData *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1Asn1WipOpenDataPresent_primitive:
		Dz1ElasticBuf_del(p->x.primitive);
		break;
	case Dz1Asn1WipOpenDataPresent_construct:
		Dz1Asn1WipOpenTypeList_del(p->x.construct);
		break;
	default:
		break;
	}
}

void Dz1Asn1WipOpenData_del(Dz1Asn1WipOpenData *p)
{
	if (!p) return;
	Dz1Asn1WipOpenData_purge(p);
	Dz1Free(p);
}

void Dz1Asn1WipOpenDataA_dump(Dz1Asn1WipOpenData *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1WipOpenDataPresent_primitive:
		Dz1ThreadA_printf("primitive = "); Dz1ElasticBufA_dump(p->x.primitive, tab); 
		break;
	case Dz1Asn1WipOpenDataPresent_construct:
		Dz1ThreadA_printf("construct = "); Dz1Asn1WipOpenTypeListA_dump(p->x.construct, tab); 
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1WipOpenDataW_dump(Dz1Asn1WipOpenData *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1WipOpenDataPresent_primitive:
		Dz1ThreadW_printf(L"primitive = "); Dz1ElasticBufW_dump(p->x.primitive, tab); 
		break;
	case Dz1Asn1WipOpenDataPresent_construct:
		Dz1ThreadW_printf(L"construct = "); Dz1Asn1WipOpenTypeListW_dump(p->x.construct, tab); 
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}
#endif // UNIX_SYSTEM

// Dz1Asn1WipOpenData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenType
Dz1Asn1WipOpenType *Dz1Asn1WipOpenType_new(Dz1Asn1TagClass cls, 
										   u64_t number, 
										   u64_t len, 
										   Dz1Asn1WipOpenData *contents, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipOpenType *__internal_ret = (Dz1Asn1WipOpenType *)Dz1Calloc(sizeof(Dz1Asn1WipOpenType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOpenType_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cls = cls;
		__internal_ret->number = number;
		__internal_ret->len = len;
		__internal_ret->contents = contents;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipOpenType_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1WipOpenType_purge(Dz1Asn1WipOpenType *p)
{
	if (p == NULL) return;
	Dz1Asn1WipOpenData_del(p->contents);
}

void Dz1Asn1WipOpenType_del(Dz1Asn1WipOpenType *p)
{
	if (p == NULL) return;
	Dz1Asn1WipOpenType_purge(p);
	Dz1Free(p);
}

void Dz1Asn1WipOpenTypeA_dump(Dz1Asn1WipOpenType *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "cls = %s(%d)\n", Dz1Asn1TagClassStrA(p->cls), p->cls);
		Dz1ThreadA_tprintf(tab, "number = "); Dz1u64A_dump(&p->number, tab); 
		Dz1ThreadA_tprintf(tab, "len = "); Dz1u64A_dump(&p->len, tab); 
		Dz1ThreadA_tprintf(tab, "contents."); Dz1Asn1WipOpenDataA_dump(p->contents, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1WipOpenTypeW_dump(Dz1Asn1WipOpenType *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"cls = %s(%d)\n", Dz1Asn1TagClassStrW(p->cls), p->cls);
		Dz1ThreadW_tprintf(tab, L"number = "); Dz1u64W_dump(&p->number, tab); 
		Dz1ThreadW_tprintf(tab, L"len = "); Dz1u64W_dump(&p->len, tab); 
		Dz1ThreadW_tprintf(tab, L"contents."); Dz1Asn1WipOpenDataW_dump(p->contents, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1WipOpenType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipBitString
Dz1Asn1WipBitString *Dz1Asn1WipBitString_new(Dz1ElasticBuf *elb, 
											 u32_t trim_bits, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipBitString *__internal_ret = (Dz1Asn1WipBitString *)Dz1Calloc(sizeof(Dz1Asn1WipBitString), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipBitString_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->elb = elb;
		__internal_ret->trim_bits = trim_bits;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipBitString_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1WipBitString_purge(Dz1Asn1WipBitString *p)
{
	if (p == NULL) return;
	Dz1ElasticBuf_del(p->elb);
}

void Dz1Asn1WipBitString_del(Dz1Asn1WipBitString *p)
{
	if (p == NULL) return;
	Dz1Asn1WipBitString_purge(p);
	Dz1Free(p);
}

void Dz1Asn1WipBitStringA_dump(Dz1Asn1WipBitString *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "elb = "); Dz1ElasticBufA_dump(p->elb, tab); 
		Dz1ThreadA_tprintf(tab, "trim_bits = "); Dz1u32A_dump(&p->trim_bits, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1WipBitStringW_dump(Dz1Asn1WipBitString *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"elb = "); Dz1ElasticBufW_dump(p->elb, tab); 
		Dz1ThreadW_tprintf(tab, L"trim_bits = "); Dz1u32W_dump(&p->trim_bits, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1WipBitString
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOidArc
Dz1Asn1WipOidArc *Dz1Asn1WipOidArc_new(u32_t ord, u32_t num, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipOidArc *__internal_ret = (Dz1Asn1WipOidArc *)Dz1Calloc(sizeof(Dz1Asn1WipOidArc), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOidArc_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->ord = ord;
		__internal_ret->num = num;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipOidArc_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1Asn1WipOidArc_copy(Dz1Asn1WipOidArc *dst, Dz1Asn1WipOidArc *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->ord = src->ord;
		dst->num = src->num;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1Asn1WipOidArc *Dz1Asn1WipOidArc_clone(Dz1Asn1WipOidArc *src, Dz1Error *err)
{
	Dz1Asn1WipOidArc *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1Asn1WipOidArc *)Dz1Calloc(sizeof(Dz1Asn1WipOidArc), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOidArc_delAndSetNull, (void *)&dst);
		if (Dz1Asn1WipOidArc_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipOidArc_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1Asn1WipOidArc_purge(Dz1Asn1WipOidArc *p)
{
	if (p == NULL) return;
}

void Dz1Asn1WipOidArc_del(Dz1Asn1WipOidArc *p)
{
	if (p == NULL) return;
	Dz1Asn1WipOidArc_purge(p);
	Dz1Free(p);
}

void Dz1Asn1WipOidArcA_dump(Dz1Asn1WipOidArc *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "ord = "); Dz1u32A_dump(&p->ord, tab); 
		Dz1ThreadA_tprintf(tab, "num = "); Dz1u32A_dump(&p->num, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1WipOidArcW_dump(Dz1Asn1WipOidArc *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"ord = "); Dz1u32W_dump(&p->ord, tab); 
		Dz1ThreadW_tprintf(tab, L"num = "); Dz1u32W_dump(&p->num, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
int Dz1Asn1WipOidArc_cmp(Dz1Asn1WipOidArc *a, Dz1Asn1WipOidArc *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->ord, &b->ord)) != 0) { }
	return ret;
}
// Dz1Asn1WipOidArc
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOid
static Dz1Error Dz1Asn1WipOid_add(Dz1Asn1WipOid *p, Dz1Asn1WipOidArc *data)
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

static bool_t Dz1Asn1WipOid_remove(Dz1Asn1WipOid *p, Dz1Asn1WipOidArc *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1Asn1WipOidArc *Dz1Asn1WipOid_extract(Dz1Asn1WipOid *p, Dz1Asn1WipOidArc *key)
{
	return (Dz1Asn1WipOidArc *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1Asn1WipOidMkArrArg
{
	Dz1Asn1WipOidArc **arr;
	unsigned int idx;
} Dz1Asn1WipOidMkArrArg;

static Dz1Error _Dz1Asn1WipOid_get_array(void *ptr, Dz1Asn1WipOidArc *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1WipOidMkArrArg *arg = (Dz1Asn1WipOidMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1Asn1WipOidArc **Dz1Asn1WipOid_get_array(Dz1Asn1WipOid *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1Asn1WipOidArc **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Asn1WipOidArc **)Dz1Calloc(sizeof(Dz1Asn1WipOidArc *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1WipOidMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1Asn1WipOid_get_array, (void *)&arg);
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

static Dz1Error Dz1Asn1WipOid_travelForward(Dz1Asn1WipOid *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOidArc *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1Asn1WipOid_travelBackward(Dz1Asn1WipOid *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOidArc *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Asn1WipOidArc *Dz1Asn1WipOid_find(Dz1Asn1WipOid *p, Dz1Asn1WipOidArc *key)
{
	return (Dz1Asn1WipOidArc *)Dz1AATree_find(p->storage, key);
}

static Dz1Asn1WipOidArc *Dz1Asn1WipOid_getHead(Dz1Asn1WipOid *p)
{
	return (Dz1Asn1WipOidArc *)Dz1AATree_getHead(p->storage);
}

static Dz1Asn1WipOidArc *Dz1Asn1WipOid_getTail(Dz1Asn1WipOid *p)
{
	return (Dz1Asn1WipOidArc *)Dz1AATree_getTail(p->storage);
}

static unsigned int Dz1Asn1WipOid_count(Dz1Asn1WipOid *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1Asn1WipOid *Dz1Asn1WipOid_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipOid *ret = (Dz1Asn1WipOid *)Dz1Calloc(sizeof(Dz1Asn1WipOid), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOid_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1Asn1WipOidArc_cmp,
				(Dz1DelFunc)Dz1Asn1WipOidArc_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1Asn1WipOid_count;
			ret->travel = Dz1Asn1WipOid_travelForward;
			ret->travelForward = Dz1Asn1WipOid_travelForward;
			ret->travelBackward = Dz1Asn1WipOid_travelBackward;
			ret->get_array = Dz1Asn1WipOid_get_array;
			ret->add = Dz1Asn1WipOid_add;
			ret->remove = Dz1Asn1WipOid_remove;
			ret->find = Dz1Asn1WipOid_find;
			ret->extract = Dz1Asn1WipOid_extract;
			ret->getHead = Dz1Asn1WipOid_getHead;
			ret->getTail = Dz1Asn1WipOid_getTail;
			ret->cmp = Dz1Asn1WipOidArc_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipOid_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1Asn1WipOid_clone(void *ptr, Dz1Asn1WipOidArc *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1WipOid *p = (Dz1Asn1WipOid *)ptr;
	Dz1Asn1WipOidArc *cloned = Dz1Asn1WipOidArc_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1Asn1WipOid *Dz1Asn1WipOid_clone(Dz1Asn1WipOid *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipOid *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1Asn1WipOid_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1WipOid_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1Asn1WipOid_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipOid_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1WipOid_purge(Dz1Asn1WipOid *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1Asn1WipOid_del(Dz1Asn1WipOid *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1Asn1WipOidA_dump(void *ptr, Dz1Asn1WipOidArc *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1Asn1WipOidArcA_dump(p, tab);
	return err;
}

void Dz1Asn1WipOidA_dump(Dz1Asn1WipOid *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1Asn1WipOidA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Dz1Asn1WipOidW_dump(void *ptr, Dz1Asn1WipOidArc *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1Asn1WipOidArcW_dump(p, tab);
	return err;
}

void Dz1Asn1WipOidW_dump(Dz1Asn1WipOid *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1Asn1WipOidW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1WipOid
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipExtOrInstPresent
static struct Dz1Asn1WipExtOrInstPresentMapA
{
	str_t str;
	Dz1Asn1WipExtOrInstPresent v;
} Dz1Asn1WipExtOrInstPresentMapA[] =
{
	{ (char *)"external", Dz1Asn1WipExtOrInstPresent_external },
	{ (char *)"instance_of", Dz1Asn1WipExtOrInstPresent_instance_of },
	{ NULL, Dz1Asn1WipExtOrInstPresent_max }
};

str_t Dz1Asn1WipExtOrInstPresentStrA(Dz1Asn1WipExtOrInstPresent v)
{
	struct Dz1Asn1WipExtOrInstPresentMapA *i = NULL;
	for (i = Dz1Asn1WipExtOrInstPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1WipExtOrInstPresent Dz1Asn1WipExtOrInstPresentFromStrA(str_t str)
{
	struct Dz1Asn1WipExtOrInstPresentMapA *i = NULL;
	for (i = Dz1Asn1WipExtOrInstPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1WipExtOrInstPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1WipExtOrInstPresentMapW
{
	wstr_t str;
	Dz1Asn1WipExtOrInstPresent v;
} Dz1Asn1WipExtOrInstPresentMapW[] =
{
	{ (wchar_t *)L"external", Dz1Asn1WipExtOrInstPresent_external },
	{ (wchar_t *)L"instance_of", Dz1Asn1WipExtOrInstPresent_instance_of },
	{ NULL, Dz1Asn1WipExtOrInstPresent_max }
};

wstr_t Dz1Asn1WipExtOrInstPresentStrW(Dz1Asn1WipExtOrInstPresent v)
{
	struct Dz1Asn1WipExtOrInstPresentMapW *i = NULL;
	for (i = Dz1Asn1WipExtOrInstPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1WipExtOrInstPresent Dz1Asn1WipExtOrInstPresentFromStrW(wstr_t str)
{
	struct Dz1Asn1WipExtOrInstPresentMapW *i = NULL;
	for (i = Dz1Asn1WipExtOrInstPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1WipExtOrInstPresent_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1WipExtOrInstPresent *Dz1Asn1WipExtOrInstPresent_new(Dz1Asn1WipExtOrInstPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipExtOrInstPresent *__internal_ret = (Dz1Asn1WipExtOrInstPresent *)Dz1Calloc(sizeof(Dz1Asn1WipExtOrInstPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1Asn1WipExtOrInstPresentA_dump(Dz1Asn1WipExtOrInstPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1WipExtOrInstPresentStrA(*v));
}
void Dz1Asn1WipExtOrInstPresentA_fdump(FILE *fp, Dz1Asn1WipExtOrInstPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", Dz1Asn1WipExtOrInstPresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1WipExtOrInstPresentW_dump(Dz1Asn1WipExtOrInstPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1WipExtOrInstPresentStrW(*v));
}
void Dz1Asn1WipExtOrInstPresentW_fdump(FILE *fp, Dz1Asn1WipExtOrInstPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", Dz1Asn1WipExtOrInstPresentStrW(*v));
}
#endif // UNIX_SYSTEM

int Dz1Asn1WipExtOrInstPresent_cmp(Dz1Asn1WipExtOrInstPresent *a, Dz1Asn1WipExtOrInstPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// Dz1Asn1WipExtOrInstPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipExtOrInst
Dz1Asn1WipExtOrInst *Dz1Asn1WipExtOrInst_new(Dz1Asn1WipExtOrInstPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipExtOrInst *ret = (Dz1Asn1WipExtOrInst *)Dz1Calloc(sizeof(Dz1Asn1WipExtOrInst), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipExtOrInst_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1Asn1WipExtOrInstPresent_external:
			// _U_cst_clone
			if (ptr != NULL) ret->x.external = (Dz1Asn1External *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipExtOrInstPresent_instance_of:
			// _U_cst_clone
			if (ptr != NULL) ret->x.instance_of = (Dz1Asn1InstanceOf *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipExtOrInstPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipExtOrInst_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1Asn1WipExtOrInst_copy(Dz1Asn1WipExtOrInst *ret, Dz1Asn1WipExtOrInst *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1Asn1WipExtOrInstPresent_external:
			// _U_cst_clone
			if (src->x.external && (ret->x.external = Dz1Asn1External_clone(src->x.external, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1Asn1WipExtOrInstPresent_instance_of:
			// _U_cst_clone
			if (src->x.instance_of && (ret->x.instance_of = Dz1Asn1InstanceOf_clone(src->x.instance_of, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1Asn1WipExtOrInst *Dz1Asn1WipExtOrInst_clone(Dz1Asn1WipExtOrInst *src, Dz1Error *err)
{
	Dz1Asn1WipExtOrInst *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1Asn1WipExtOrInst *)Dz1Calloc(sizeof(Dz1Asn1WipExtOrInst), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipExtOrInst_delAndSetNull, (void *)&ret);
		if (Dz1Asn1WipExtOrInst_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipExtOrInst_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1WipExtOrInst_purge(Dz1Asn1WipExtOrInst *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1Asn1WipExtOrInstPresent_external:
		Dz1Asn1External_del(p->x.external);
		break;
	case Dz1Asn1WipExtOrInstPresent_instance_of:
		Dz1Asn1InstanceOf_del(p->x.instance_of);
		break;
	default:
		break;
	}
}

void Dz1Asn1WipExtOrInst_del(Dz1Asn1WipExtOrInst *p)
{
	if (!p) return;
	Dz1Asn1WipExtOrInst_purge(p);
	Dz1Free(p);
}

void Dz1Asn1WipExtOrInstA_dump(Dz1Asn1WipExtOrInst *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1WipExtOrInstPresent_external:
		Dz1ThreadA_printf("external = "); Dz1Asn1ExternalA_dump(p->x.external, tab); 
		break;
	case Dz1Asn1WipExtOrInstPresent_instance_of:
		Dz1ThreadA_printf("instance_of = "); Dz1Asn1InstanceOfA_dump(p->x.instance_of, tab); 
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}
void Dz1Asn1WipExtOrInstA_fdump(FILE *fp, Dz1Asn1WipExtOrInst *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1WipExtOrInstPresent_external:
		Dz1ThreadA_fprintf(fp, "external = "); Dz1Asn1ExternalA_fdump(fp, p->x.external, tab); 
		break;
	case Dz1Asn1WipExtOrInstPresent_instance_of:
		Dz1ThreadA_fprintf(fp, "instance_of = "); Dz1Asn1InstanceOfA_fdump(fp, p->x.instance_of, tab); 
		break;
	default:
		Dz1ThreadA_ftprintf(fp, tab, "??? = %d\n", p->present);
		break;
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1WipExtOrInstW_dump(Dz1Asn1WipExtOrInst *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1WipExtOrInstPresent_external:
		Dz1ThreadW_printf(L"external = "); Dz1Asn1ExternalW_dump(p->x.external, tab); 
		break;
	case Dz1Asn1WipExtOrInstPresent_instance_of:
		Dz1ThreadW_printf(L"instance_of = "); Dz1Asn1InstanceOfW_dump(p->x.instance_of, tab); 
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}
void Dz1Asn1WipExtOrInstW_fdump(FILE *fp, Dz1Asn1WipExtOrInst *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1WipExtOrInstPresent_external:
		Dz1ThreadW_fprintf(fp, L"external = "); Dz1Asn1ExternalW_fdump(fp, p->x.external, tab); 
		break;
	case Dz1Asn1WipExtOrInstPresent_instance_of:
		Dz1ThreadW_fprintf(fp, L"instance_of = "); Dz1Asn1InstanceOfW_fdump(fp, p->x.instance_of, tab); 
		break;
	default:
		Dz1ThreadW_ftprintf(fp, tab, L"??? = %d\n", p->present);
		break;
	}
}
#endif // UNIX_SYSTEM

int Dz1Asn1WipExtOrInst_cmp(Dz1Asn1WipExtOrInst *a, Dz1Asn1WipExtOrInst *b)
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
		case Dz1Asn1WipExtOrInstPresent_external:
			if (a->x.external == NULL && b->x.external == NULL) ret = 0;
			else if (a->x.external == NULL /*&& b->x.external != NULL*/) ret = -1;
			else if (/*a->x.external != NULL &&*/ b->x.external == NULL) ret = 1;
			else if ((ret = Dz1Asn1External_cmp(a->x.external, b->x.external)) != 0) { }
			break;
		case Dz1Asn1WipExtOrInstPresent_instance_of:
			if (a->x.instance_of == NULL && b->x.instance_of == NULL) ret = 0;
			else if (a->x.instance_of == NULL /*&& b->x.instance_of != NULL*/) ret = -1;
			else if (/*a->x.instance_of != NULL &&*/ b->x.instance_of == NULL) ret = 1;
			else if ((ret = Dz1Asn1InstanceOf_cmp(a->x.instance_of, b->x.instance_of)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// Dz1Asn1WipExtOrInst
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipReal
Dz1Asn1WipReal *Dz1Asn1WipReal_new(Dz1ElasticBuf *elb, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipReal *__internal_ret = (Dz1Asn1WipReal *)Dz1Calloc(sizeof(Dz1Asn1WipReal), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipReal_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->elb = elb;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipReal_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1WipReal_purge(Dz1Asn1WipReal *p)
{
	if (p == NULL) return;
	Dz1ElasticBuf_del(p->elb);
}

void Dz1Asn1WipReal_del(Dz1Asn1WipReal *p)
{
	if (p == NULL) return;
	Dz1Asn1WipReal_purge(p);
	Dz1Free(p);
}

// Dz1Asn1WipReal
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipCst
Dz1Asn1WipCst *Dz1Asn1WipCst_new(Dz1Asn1Custom *storage, 
								 Dz1Asn1TypeDescr *indirect, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipCst *__internal_ret = (Dz1Asn1WipCst *)Dz1Calloc(sizeof(Dz1Asn1WipCst), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipCst_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->unknowns = Dz1Asn1WipOpenTypeList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->storage = storage;
			__internal_ret->indirect = indirect;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipCst_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1WipCst_purge(Dz1Asn1WipCst *p)
{
	if (p == NULL) return;
	Dz1Asn1Custom_del(p->storage);
	Dz1Asn1WipOpenTypeList_del(p->unknowns);
	Dz1Asn1TypeDescr_del(p->indirect);
}

void Dz1Asn1WipCst_del(Dz1Asn1WipCst *p)
{
	if (p == NULL) return;
	Dz1Asn1WipCst_purge(p);
	Dz1Free(p);
}

// Dz1Asn1WipCst
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipValuePresent
static struct Dz1Asn1WipValuePresentMapA
{
	str_t str;
	Dz1Asn1WipValuePresent v;
} Dz1Asn1WipValuePresentMapA[] =
{
	{ (char *)"any", Dz1Asn1WipValuePresent_any },
	{ (char *)"boolean", Dz1Asn1WipValuePresent_boolean },
	{ (char *)"number", Dz1Asn1WipValuePresent_number },
	{ (char *)"bit_str", Dz1Asn1WipValuePresent_bit_str },
	{ (char *)"octet_str", Dz1Asn1WipValuePresent_octet_str },
	{ (char *)"nul", Dz1Asn1WipValuePresent_nul },
	{ (char *)"oid", Dz1Asn1WipValuePresent_oid },
	{ (char *)"ext_or_inst", Dz1Asn1WipValuePresent_ext_or_inst },
	{ (char *)"realnum", Dz1Asn1WipValuePresent_realnum },
	{ (char *)"enumerated", Dz1Asn1WipValuePresent_enumerated },
	{ (char *)"embPDV", Dz1Asn1WipValuePresent_embPDV },
	{ (char *)"cst_seq", Dz1Asn1WipValuePresent_cst_seq },
	{ (char *)"cst_set", Dz1Asn1WipValuePresent_cst_set },
	{ (char *)"char_str", Dz1Asn1WipValuePresent_char_str },
	{ NULL, Dz1Asn1WipValuePresent_max }
};

str_t Dz1Asn1WipValuePresentStrA(Dz1Asn1WipValuePresent v)
{
	struct Dz1Asn1WipValuePresentMapA *i = NULL;
	for (i = Dz1Asn1WipValuePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1WipValuePresent Dz1Asn1WipValuePresentFromStrA(str_t str)
{
	struct Dz1Asn1WipValuePresentMapA *i = NULL;
	for (i = Dz1Asn1WipValuePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1WipValuePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1WipValuePresentMapW
{
	wstr_t str;
	Dz1Asn1WipValuePresent v;
} Dz1Asn1WipValuePresentMapW[] =
{
	{ (wchar_t *)L"any", Dz1Asn1WipValuePresent_any },
	{ (wchar_t *)L"boolean", Dz1Asn1WipValuePresent_boolean },
	{ (wchar_t *)L"number", Dz1Asn1WipValuePresent_number },
	{ (wchar_t *)L"bit_str", Dz1Asn1WipValuePresent_bit_str },
	{ (wchar_t *)L"octet_str", Dz1Asn1WipValuePresent_octet_str },
	{ (wchar_t *)L"nul", Dz1Asn1WipValuePresent_nul },
	{ (wchar_t *)L"oid", Dz1Asn1WipValuePresent_oid },
	{ (wchar_t *)L"ext_or_inst", Dz1Asn1WipValuePresent_ext_or_inst },
	{ (wchar_t *)L"realnum", Dz1Asn1WipValuePresent_realnum },
	{ (wchar_t *)L"enumerated", Dz1Asn1WipValuePresent_enumerated },
	{ (wchar_t *)L"embPDV", Dz1Asn1WipValuePresent_embPDV },
	{ (wchar_t *)L"cst_seq", Dz1Asn1WipValuePresent_cst_seq },
	{ (wchar_t *)L"cst_set", Dz1Asn1WipValuePresent_cst_set },
	{ (wchar_t *)L"char_str", Dz1Asn1WipValuePresent_char_str },
	{ NULL, Dz1Asn1WipValuePresent_max }
};

wstr_t Dz1Asn1WipValuePresentStrW(Dz1Asn1WipValuePresent v)
{
	struct Dz1Asn1WipValuePresentMapW *i = NULL;
	for (i = Dz1Asn1WipValuePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1WipValuePresent Dz1Asn1WipValuePresentFromStrW(wstr_t str)
{
	struct Dz1Asn1WipValuePresentMapW *i = NULL;
	for (i = Dz1Asn1WipValuePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1WipValuePresent_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1WipValuePresent *Dz1Asn1WipValuePresent_new(Dz1Asn1WipValuePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipValuePresent *__internal_ret = (Dz1Asn1WipValuePresent *)Dz1Calloc(sizeof(Dz1Asn1WipValuePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1WipValuePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipValue
Dz1Asn1WipValue *Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1WipValue *ret = (Dz1Asn1WipValue *)Dz1Calloc(sizeof(Dz1Asn1WipValue), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1WipValue_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1Asn1WipValuePresent_any:
			// _U_cst_clone
			if (ptr != NULL) ret->x.any = (Dz1Asn1WipOpenType *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_boolean:
			// _U_imp_clone
			if (ptr != NULL) ret->x.boolean = *(Dz1Asn1Bool *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_number:
			// _U_imp_clone
			if (ptr != NULL) ret->x.number = *(Dz1Asn1Int *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_bit_str:
			// _U_cst_clone
			if (ptr != NULL) ret->x.bit_str = (Dz1Asn1WipBitString *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_octet_str:
			// _U_imp_clone
			if (ptr != NULL) ret->x.octet_str = (Dz1ElasticBuf *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_nul:
			// _U_imp_clone
			if (ptr != NULL) ret->x.nul = *(Dz1Asn1Null *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_oid:
			// _U_cst_clone
			if (ptr != NULL) ret->x.oid = (Dz1Asn1WipOid *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_ext_or_inst:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ext_or_inst = (Dz1Asn1WipExtOrInst *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_realnum:
			// _U_cst_clone
			if (ptr != NULL) ret->x.realnum = (Dz1Asn1WipReal *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_enumerated:
			// _U_imp_clone
			if (ptr != NULL) ret->x.enumerated = *(Dz1Asn1Enum *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_embPDV:
			// _U_cst_clone
			if (ptr != NULL) ret->x.embPDV = (Dz1Asn1EmbPdv *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_cst_seq:
			// _U_cst_clone
			if (ptr != NULL) ret->x.cst_seq = (Dz1Asn1WipCst *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_cst_set:
			// _U_cst_clone
			if (ptr != NULL) ret->x.cst_set = (Dz1Asn1WipCst *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_char_str:
			// _U_cst_clone
			if (ptr != NULL) ret->x.char_str = (Dz1Asn1CharStr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1WipValuePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1WipValue_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1WipValue_purge(Dz1Asn1WipValue *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1Asn1WipValuePresent_any:
		Dz1Asn1WipOpenType_del(p->x.any);
		break;
	case Dz1Asn1WipValuePresent_boolean:
		break;
	case Dz1Asn1WipValuePresent_number:
		break;
	case Dz1Asn1WipValuePresent_bit_str:
		Dz1Asn1WipBitString_del(p->x.bit_str);
		break;
	case Dz1Asn1WipValuePresent_octet_str:
		Dz1ElasticBuf_del(p->x.octet_str);
		break;
	case Dz1Asn1WipValuePresent_nul:
		break;
	case Dz1Asn1WipValuePresent_oid:
		Dz1Asn1WipOid_del(p->x.oid);
		break;
	case Dz1Asn1WipValuePresent_ext_or_inst:
		Dz1Asn1WipExtOrInst_del(p->x.ext_or_inst);
		break;
	case Dz1Asn1WipValuePresent_realnum:
		Dz1Asn1WipReal_del(p->x.realnum);
		break;
	case Dz1Asn1WipValuePresent_enumerated:
		break;
	case Dz1Asn1WipValuePresent_embPDV:
		Dz1Asn1EmbPdv_del(p->x.embPDV);
		break;
	case Dz1Asn1WipValuePresent_cst_seq:
		Dz1Asn1WipCst_del(p->x.cst_seq);
		break;
	case Dz1Asn1WipValuePresent_cst_set:
		Dz1Asn1WipCst_del(p->x.cst_set);
		break;
	case Dz1Asn1WipValuePresent_char_str:
		Dz1Asn1CharStr_del(p->x.char_str);
		break;
	default:
		break;
	}
}

void Dz1Asn1WipValue_del(Dz1Asn1WipValue *p)
{
	if (!p) return;
	Dz1Asn1WipValue_purge(p);
	Dz1Free(p);
}

// Dz1Asn1WipValue
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1MetaDataRange
Dz1Asn1MetaDataRange *Dz1Asn1MetaDataRange_new(Dz1Asn1Int low, Dz1Asn1Int high, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1MetaDataRange *__internal_ret = (Dz1Asn1MetaDataRange *)Dz1Calloc(sizeof(Dz1Asn1MetaDataRange), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1MetaDataRange_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->low = low;
		__internal_ret->high = high;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1MetaDataRange_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1MetaDataRange_purge(Dz1Asn1MetaDataRange *p)
{
	if (p == NULL) return;
}

void Dz1Asn1MetaDataRange_del(Dz1Asn1MetaDataRange *p)
{
	if (p == NULL) return;
	Dz1Asn1MetaDataRange_purge(p);
	Dz1Free(p);
}

void Dz1Asn1MetaDataRangeA_dump(Dz1Asn1MetaDataRange *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadA_tprintf(tab, "low = "); Dz1Asn1IntA_dump(&p->low, tab); 
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadA_tprintf(tab, "high = "); Dz1Asn1IntA_dump(&p->high, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void Dz1Asn1MetaDataRangeA_fdump(FILE *fp, Dz1Asn1MetaDataRange *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadA_ftprintf(fp, tab, "low = "); Dz1Asn1IntA_fdump(fp, &p->low, tab); 
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadA_ftprintf(fp, tab, "high = "); Dz1Asn1IntA_fdump(fp, &p->high, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1MetaDataRangeW_dump(Dz1Asn1MetaDataRange *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadW_tprintf(tab, L"low = "); Dz1Asn1IntW_dump(&p->low, tab); 
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadW_tprintf(tab, L"high = "); Dz1Asn1IntW_dump(&p->high, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void Dz1Asn1MetaDataRangeW_fdump(FILE *fp, Dz1Asn1MetaDataRange *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadW_ftprintf(fp, tab, L"low = "); Dz1Asn1IntW_fdump(fp, &p->low, tab); 
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadW_ftprintf(fp, tab, L"high = "); Dz1Asn1IntW_fdump(fp, &p->high, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1MetaDataRange
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1MetaDataRealRange
Dz1Asn1MetaDataRealRange *Dz1Asn1MetaDataRealRange_new(Dz1Asn1Real low, 
													   Dz1Asn1Real high, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1MetaDataRealRange *__internal_ret = (Dz1Asn1MetaDataRealRange *)Dz1Calloc(sizeof(Dz1Asn1MetaDataRealRange), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1MetaDataRealRange_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->low = low;
		__internal_ret->high = high;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1MetaDataRealRange_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1MetaDataRealRange_purge(Dz1Asn1MetaDataRealRange *p)
{
	if (p == NULL) return;
}

void Dz1Asn1MetaDataRealRange_del(Dz1Asn1MetaDataRealRange *p)
{
	if (p == NULL) return;
	Dz1Asn1MetaDataRealRange_purge(p);
	Dz1Free(p);
}

void Dz1Asn1MetaDataRealRangeA_dump(Dz1Asn1MetaDataRealRange *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadA_tprintf(tab, "low = "); Dz1Asn1RealA_dump(&p->low, tab); 
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadA_tprintf(tab, "high = "); Dz1Asn1RealA_dump(&p->high, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void Dz1Asn1MetaDataRealRangeA_fdump(FILE *fp, Dz1Asn1MetaDataRealRange *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadA_ftprintf(fp, tab, "low = "); Dz1Asn1RealA_fdump(fp, &p->low, tab); 
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadA_ftprintf(fp, tab, "high = "); Dz1Asn1RealA_fdump(fp, &p->high, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1MetaDataRealRangeW_dump(Dz1Asn1MetaDataRealRange *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadW_tprintf(tab, L"low = "); Dz1Asn1RealW_dump(&p->low, tab); 
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadW_tprintf(tab, L"high = "); Dz1Asn1RealW_dump(&p->high, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void Dz1Asn1MetaDataRealRangeW_fdump(FILE *fp, Dz1Asn1MetaDataRealRange *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadW_ftprintf(fp, tab, L"low = "); Dz1Asn1RealW_fdump(fp, &p->low, tab); 
		// _imp_dump
		// _imp_dump : scalar
		Dz1ThreadW_ftprintf(fp, tab, L"high = "); Dz1Asn1RealW_fdump(fp, &p->high, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1MetaDataRealRange
////////////////////////////////////////////////////////////////////////////////

