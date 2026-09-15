////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_var_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqType
static struct Dz1TdqTypeMapA
{
	str_t str;
	Dz1TdqType v;
} Dz1TdqTypeMapA[] =
{
	{ (char *)"num_s8", Dz1TdqType_num_s8 },
	{ (char *)"num_u8", Dz1TdqType_num_u8 },
	{ (char *)"num_s16", Dz1TdqType_num_s16 },
	{ (char *)"num_u16", Dz1TdqType_num_u16 },
	{ (char *)"num_s32", Dz1TdqType_num_s32 },
	{ (char *)"num_u32", Dz1TdqType_num_u32 },
	{ (char *)"num_s64", Dz1TdqType_num_s64 },
	{ (char *)"num_u64", Dz1TdqType_num_u64 },
	{ (char *)"num_r32", Dz1TdqType_num_r32 },
	{ (char *)"num_r64", Dz1TdqType_num_r64 },
	{ (char *)"string", Dz1TdqType_string },
	{ (char *)"vstring", Dz1TdqType_vstring },
	{ (char *)"tstring", Dz1TdqType_tstring },
	{ (char *)"vtstring", Dz1TdqType_vtstring },
	{ (char *)"binary", Dz1TdqType_binary },
	{ (char *)"vbinary", Dz1TdqType_vbinary },
	{ (char *)"date", Dz1TdqType_date },
	{ (char *)"time", Dz1TdqType_time },
	{ (char *)"timestamp", Dz1TdqType_timestamp },
	{ (char *)"blob", Dz1TdqType_blob },
	{ (char *)"blobL", Dz1TdqType_blobL },
	{ NULL, Dz1TdqType_max }
};

str_t Dz1TdqTypeStrA(Dz1TdqType v)
{
	struct Dz1TdqTypeMapA *i = NULL;
	for (i = Dz1TdqTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqType Dz1TdqTypeFromStrA(str_t str)
{
	struct Dz1TdqTypeMapA *i = NULL;
	for (i = Dz1TdqTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqTypeMapW
{
	wstr_t str;
	Dz1TdqType v;
} Dz1TdqTypeMapW[] =
{
	{ (wchar_t *)L"num_s8", Dz1TdqType_num_s8 },
	{ (wchar_t *)L"num_u8", Dz1TdqType_num_u8 },
	{ (wchar_t *)L"num_s16", Dz1TdqType_num_s16 },
	{ (wchar_t *)L"num_u16", Dz1TdqType_num_u16 },
	{ (wchar_t *)L"num_s32", Dz1TdqType_num_s32 },
	{ (wchar_t *)L"num_u32", Dz1TdqType_num_u32 },
	{ (wchar_t *)L"num_s64", Dz1TdqType_num_s64 },
	{ (wchar_t *)L"num_u64", Dz1TdqType_num_u64 },
	{ (wchar_t *)L"num_r32", Dz1TdqType_num_r32 },
	{ (wchar_t *)L"num_r64", Dz1TdqType_num_r64 },
	{ (wchar_t *)L"string", Dz1TdqType_string },
	{ (wchar_t *)L"vstring", Dz1TdqType_vstring },
	{ (wchar_t *)L"tstring", Dz1TdqType_tstring },
	{ (wchar_t *)L"vtstring", Dz1TdqType_vtstring },
	{ (wchar_t *)L"binary", Dz1TdqType_binary },
	{ (wchar_t *)L"vbinary", Dz1TdqType_vbinary },
	{ (wchar_t *)L"date", Dz1TdqType_date },
	{ (wchar_t *)L"time", Dz1TdqType_time },
	{ (wchar_t *)L"timestamp", Dz1TdqType_timestamp },
	{ (wchar_t *)L"blob", Dz1TdqType_blob },
	{ (wchar_t *)L"blobL", Dz1TdqType_blobL },
	{ NULL, Dz1TdqType_max }
};

wstr_t Dz1TdqTypeStrW(Dz1TdqType v)
{
	struct Dz1TdqTypeMapW *i = NULL;
	for (i = Dz1TdqTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqType Dz1TdqTypeFromStrW(wstr_t str)
{
	struct Dz1TdqTypeMapW *i = NULL;
	for (i = Dz1TdqTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqType_max;
}
#endif // UNIX_SYSTEM

Dz1TdqType *Dz1TdqType_new(Dz1TdqType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqType *__internal_ret = (Dz1TdqType *)Dz1Calloc(sizeof(Dz1TdqType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1TdqType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlNumSpec
Dz1TdqSqlNumSpec *Dz1TdqSqlNumSpec_new(s64_t size, bool_t auto_inc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlNumSpec *__internal_ret = (Dz1TdqSqlNumSpec *)Dz1Calloc(sizeof(Dz1TdqSqlNumSpec), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNumSpec_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->size = size;
		__internal_ret->auto_inc = auto_inc;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlNumSpec_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlNumSpec_copy(Dz1TdqSqlNumSpec *dst, Dz1TdqSqlNumSpec *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->size = src->size;
		dst->auto_inc = src->auto_inc;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlNumSpec *Dz1TdqSqlNumSpec_clone(Dz1TdqSqlNumSpec *src, Dz1Error *err)
{
	Dz1TdqSqlNumSpec *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlNumSpec *)Dz1Calloc(sizeof(Dz1TdqSqlNumSpec), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNumSpec_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlNumSpec_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlNumSpec_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlNumSpec_purge(Dz1TdqSqlNumSpec *p)
{
	if (p == NULL) return;
}

void Dz1TdqSqlNumSpec_del(Dz1TdqSqlNumSpec *p)
{
	if (p == NULL) return;
	Dz1TdqSqlNumSpec_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlNumSpec_dump(Dz1TdqSqlNumSpec *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("size = ")); Dz1s64_dump(&p->size, tab); 
		Dz1Thread_tprintf(tab, Dz1T("auto_inc = ")); Dz1Bool_dump(&p->auto_inc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqSqlNumSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlRealSpec
Dz1TdqSqlRealSpec *Dz1TdqSqlRealSpec_new(s64_t percision, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlRealSpec *__internal_ret = (Dz1TdqSqlRealSpec *)Dz1Calloc(sizeof(Dz1TdqSqlRealSpec), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlRealSpec_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->percision = percision;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlRealSpec_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlRealSpec_copy(Dz1TdqSqlRealSpec *dst, Dz1TdqSqlRealSpec *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->percision = src->percision;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlRealSpec *Dz1TdqSqlRealSpec_clone(Dz1TdqSqlRealSpec *src, Dz1Error *err)
{
	Dz1TdqSqlRealSpec *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlRealSpec *)Dz1Calloc(sizeof(Dz1TdqSqlRealSpec), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlRealSpec_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlRealSpec_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlRealSpec_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlRealSpec_purge(Dz1TdqSqlRealSpec *p)
{
	if (p == NULL) return;
}

void Dz1TdqSqlRealSpec_del(Dz1TdqSqlRealSpec *p)
{
	if (p == NULL) return;
	Dz1TdqSqlRealSpec_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlRealSpec_dump(Dz1TdqSqlRealSpec *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("percision = ")); Dz1s64_dump(&p->percision, tab); 
	}
}
// Dz1TdqSqlRealSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlStrSpec
Dz1TdqSqlStrSpec *Dz1TdqSqlStrSpec_new(s64_t size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlStrSpec *__internal_ret = (Dz1TdqSqlStrSpec *)Dz1Calloc(sizeof(Dz1TdqSqlStrSpec), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlStrSpec_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->size = size;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlStrSpec_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlStrSpec_copy(Dz1TdqSqlStrSpec *dst, Dz1TdqSqlStrSpec *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->size = src->size;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlStrSpec *Dz1TdqSqlStrSpec_clone(Dz1TdqSqlStrSpec *src, Dz1Error *err)
{
	Dz1TdqSqlStrSpec *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlStrSpec *)Dz1Calloc(sizeof(Dz1TdqSqlStrSpec), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlStrSpec_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlStrSpec_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlStrSpec_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlStrSpec_purge(Dz1TdqSqlStrSpec *p)
{
	if (p == NULL) return;
}

void Dz1TdqSqlStrSpec_del(Dz1TdqSqlStrSpec *p)
{
	if (p == NULL) return;
	Dz1TdqSqlStrSpec_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlStrSpec_dump(Dz1TdqSqlStrSpec *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("size = ")); Dz1s64_dump(&p->size, tab); 
	}
}
// Dz1TdqSqlStrSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobSpec
static struct Dz1TdqSqlBlobSpecMapA
{
	str_t str;
	Dz1TdqSqlBlobSpec v;
} Dz1TdqSqlBlobSpecMapA[] =
{
	{ (char *)"embedded", Dz1TdqSqlBlobSpec_embedded },
	{ (char *)"saved_file", Dz1TdqSqlBlobSpec_saved_file },
	{ NULL, Dz1TdqSqlBlobSpec_max }
};

str_t Dz1TdqSqlBlobSpecStrA(Dz1TdqSqlBlobSpec v)
{
	struct Dz1TdqSqlBlobSpecMapA *i = NULL;
	for (i = Dz1TdqSqlBlobSpecMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlBlobSpec Dz1TdqSqlBlobSpecFromStrA(str_t str)
{
	struct Dz1TdqSqlBlobSpecMapA *i = NULL;
	for (i = Dz1TdqSqlBlobSpecMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlBlobSpec_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqSqlBlobSpecMapW
{
	wstr_t str;
	Dz1TdqSqlBlobSpec v;
} Dz1TdqSqlBlobSpecMapW[] =
{
	{ (wchar_t *)L"embedded", Dz1TdqSqlBlobSpec_embedded },
	{ (wchar_t *)L"saved_file", Dz1TdqSqlBlobSpec_saved_file },
	{ NULL, Dz1TdqSqlBlobSpec_max }
};

wstr_t Dz1TdqSqlBlobSpecStrW(Dz1TdqSqlBlobSpec v)
{
	struct Dz1TdqSqlBlobSpecMapW *i = NULL;
	for (i = Dz1TdqSqlBlobSpecMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlBlobSpec Dz1TdqSqlBlobSpecFromStrW(wstr_t str)
{
	struct Dz1TdqSqlBlobSpecMapW *i = NULL;
	for (i = Dz1TdqSqlBlobSpecMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlBlobSpec_max;
}
#endif // UNIX_SYSTEM

Dz1TdqSqlBlobSpec *Dz1TdqSqlBlobSpec_new(Dz1TdqSqlBlobSpec *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlBlobSpec *__internal_ret = (Dz1TdqSqlBlobSpec *)Dz1Calloc(sizeof(Dz1TdqSqlBlobSpec), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1TdqSqlBlobSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlTypeSpecPresent
static struct Dz1TdqSqlTypeSpecPresentMapA
{
	str_t str;
	Dz1TdqSqlTypeSpecPresent v;
} Dz1TdqSqlTypeSpecPresentMapA[] =
{
	{ (char *)"num_s8", Dz1TdqSqlTypeSpecPresent_num_s8 },
	{ (char *)"num_u8", Dz1TdqSqlTypeSpecPresent_num_u8 },
	{ (char *)"num_s16", Dz1TdqSqlTypeSpecPresent_num_s16 },
	{ (char *)"num_u16", Dz1TdqSqlTypeSpecPresent_num_u16 },
	{ (char *)"num_s32", Dz1TdqSqlTypeSpecPresent_num_s32 },
	{ (char *)"num_u32", Dz1TdqSqlTypeSpecPresent_num_u32 },
	{ (char *)"num_s64", Dz1TdqSqlTypeSpecPresent_num_s64 },
	{ (char *)"num_u64", Dz1TdqSqlTypeSpecPresent_num_u64 },
	{ (char *)"num_r32", Dz1TdqSqlTypeSpecPresent_num_r32 },
	{ (char *)"num_r64", Dz1TdqSqlTypeSpecPresent_num_r64 },
	{ (char *)"string", Dz1TdqSqlTypeSpecPresent_string },
	{ (char *)"vstring", Dz1TdqSqlTypeSpecPresent_vstring },
	{ (char *)"tstring", Dz1TdqSqlTypeSpecPresent_tstring },
	{ (char *)"vtstring", Dz1TdqSqlTypeSpecPresent_vtstring },
	{ (char *)"binary", Dz1TdqSqlTypeSpecPresent_binary },
	{ (char *)"vbinary", Dz1TdqSqlTypeSpecPresent_vbinary },
	{ (char *)"ymd", Dz1TdqSqlTypeSpecPresent_ymd },
	{ (char *)"hms", Dz1TdqSqlTypeSpecPresent_hms },
	{ (char *)"stamp", Dz1TdqSqlTypeSpecPresent_stamp },
	{ (char *)"blob", Dz1TdqSqlTypeSpecPresent_blob },
	{ (char *)"blobL", Dz1TdqSqlTypeSpecPresent_blobL },
	{ NULL, Dz1TdqSqlTypeSpecPresent_max }
};

str_t Dz1TdqSqlTypeSpecPresentStrA(Dz1TdqSqlTypeSpecPresent v)
{
	struct Dz1TdqSqlTypeSpecPresentMapA *i = NULL;
	for (i = Dz1TdqSqlTypeSpecPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlTypeSpecPresent Dz1TdqSqlTypeSpecPresentFromStrA(str_t str)
{
	struct Dz1TdqSqlTypeSpecPresentMapA *i = NULL;
	for (i = Dz1TdqSqlTypeSpecPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlTypeSpecPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqSqlTypeSpecPresentMapW
{
	wstr_t str;
	Dz1TdqSqlTypeSpecPresent v;
} Dz1TdqSqlTypeSpecPresentMapW[] =
{
	{ (wchar_t *)L"num_s8", Dz1TdqSqlTypeSpecPresent_num_s8 },
	{ (wchar_t *)L"num_u8", Dz1TdqSqlTypeSpecPresent_num_u8 },
	{ (wchar_t *)L"num_s16", Dz1TdqSqlTypeSpecPresent_num_s16 },
	{ (wchar_t *)L"num_u16", Dz1TdqSqlTypeSpecPresent_num_u16 },
	{ (wchar_t *)L"num_s32", Dz1TdqSqlTypeSpecPresent_num_s32 },
	{ (wchar_t *)L"num_u32", Dz1TdqSqlTypeSpecPresent_num_u32 },
	{ (wchar_t *)L"num_s64", Dz1TdqSqlTypeSpecPresent_num_s64 },
	{ (wchar_t *)L"num_u64", Dz1TdqSqlTypeSpecPresent_num_u64 },
	{ (wchar_t *)L"num_r32", Dz1TdqSqlTypeSpecPresent_num_r32 },
	{ (wchar_t *)L"num_r64", Dz1TdqSqlTypeSpecPresent_num_r64 },
	{ (wchar_t *)L"string", Dz1TdqSqlTypeSpecPresent_string },
	{ (wchar_t *)L"vstring", Dz1TdqSqlTypeSpecPresent_vstring },
	{ (wchar_t *)L"tstring", Dz1TdqSqlTypeSpecPresent_tstring },
	{ (wchar_t *)L"vtstring", Dz1TdqSqlTypeSpecPresent_vtstring },
	{ (wchar_t *)L"binary", Dz1TdqSqlTypeSpecPresent_binary },
	{ (wchar_t *)L"vbinary", Dz1TdqSqlTypeSpecPresent_vbinary },
	{ (wchar_t *)L"ymd", Dz1TdqSqlTypeSpecPresent_ymd },
	{ (wchar_t *)L"hms", Dz1TdqSqlTypeSpecPresent_hms },
	{ (wchar_t *)L"stamp", Dz1TdqSqlTypeSpecPresent_stamp },
	{ (wchar_t *)L"blob", Dz1TdqSqlTypeSpecPresent_blob },
	{ (wchar_t *)L"blobL", Dz1TdqSqlTypeSpecPresent_blobL },
	{ NULL, Dz1TdqSqlTypeSpecPresent_max }
};

wstr_t Dz1TdqSqlTypeSpecPresentStrW(Dz1TdqSqlTypeSpecPresent v)
{
	struct Dz1TdqSqlTypeSpecPresentMapW *i = NULL;
	for (i = Dz1TdqSqlTypeSpecPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlTypeSpecPresent Dz1TdqSqlTypeSpecPresentFromStrW(wstr_t str)
{
	struct Dz1TdqSqlTypeSpecPresentMapW *i = NULL;
	for (i = Dz1TdqSqlTypeSpecPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlTypeSpecPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TdqSqlTypeSpecPresent *Dz1TdqSqlTypeSpecPresent_new(Dz1TdqSqlTypeSpecPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlTypeSpecPresent *__internal_ret = (Dz1TdqSqlTypeSpecPresent *)Dz1Calloc(sizeof(Dz1TdqSqlTypeSpecPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TdqSqlTypeSpecPresent_dump(Dz1TdqSqlTypeSpecPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TdqSqlTypeSpecPresentStr(*v));
}
// Dz1TdqSqlTypeSpecPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlTypeSpec
Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_new(Dz1TdqSqlTypeSpecPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlTypeSpec *ret = (Dz1TdqSqlTypeSpec *)Dz1Calloc(sizeof(Dz1TdqSqlTypeSpec), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TdqSqlTypeSpecPresent_num_s8:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_s8 = (Dz1TdqSqlNumSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_u8:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_u8 = (Dz1TdqSqlNumSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_s16:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_s16 = (Dz1TdqSqlNumSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_u16:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_u16 = (Dz1TdqSqlNumSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_s32:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_s32 = (Dz1TdqSqlNumSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_u32:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_u32 = (Dz1TdqSqlNumSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_s64:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_s64 = (Dz1TdqSqlNumSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_u64:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_u64 = (Dz1TdqSqlNumSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_r32:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_r32 = (Dz1TdqSqlRealSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_num_r64:
			// _U_cst_clone
			if (ptr != NULL) ret->x.num_r64 = (Dz1TdqSqlRealSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_string:
			// _U_cst_clone
			if (ptr != NULL) ret->x.string = (Dz1TdqSqlStrSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_vstring:
			// _U_cst_clone
			if (ptr != NULL) ret->x.vstring = (Dz1TdqSqlStrSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_tstring:
			// _U_cst_clone
			if (ptr != NULL) ret->x.tstring = (Dz1TdqSqlStrSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_vtstring:
			// _U_cst_clone
			if (ptr != NULL) ret->x.vtstring = (Dz1TdqSqlStrSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_binary:
			// _U_cst_clone
			if (ptr != NULL) ret->x.binary = (Dz1TdqSqlStrSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_vbinary:
			// _U_cst_clone
			if (ptr != NULL) ret->x.vbinary = (Dz1TdqSqlStrSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_ymd:
			// _U_prim_clone
			if (ptr != NULL) ret->x.ymd = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_hms:
			// _U_prim_clone
			if (ptr != NULL) ret->x.hms = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_stamp:
			// _U_prim_clone
			if (ptr != NULL) ret->x.stamp = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_blob:
			// _U_enum_clone
			if (ptr != NULL) ret->x.blob = *(Dz1TdqSqlBlobSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_blobL:
			// _U_enum_clone
			if (ptr != NULL) ret->x.blobL = *(Dz1TdqSqlBlobSpec *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlTypeSpec_copy(Dz1TdqSqlTypeSpec *ret, Dz1TdqSqlTypeSpec *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TdqSqlTypeSpecPresent_num_s8:
			// _U_cst_clone
			if (src->x.num_s8 && (ret->x.num_s8 = Dz1TdqSqlNumSpec_clone(src->x.num_s8, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_u8:
			// _U_cst_clone
			if (src->x.num_u8 && (ret->x.num_u8 = Dz1TdqSqlNumSpec_clone(src->x.num_u8, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_s16:
			// _U_cst_clone
			if (src->x.num_s16 && (ret->x.num_s16 = Dz1TdqSqlNumSpec_clone(src->x.num_s16, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_u16:
			// _U_cst_clone
			if (src->x.num_u16 && (ret->x.num_u16 = Dz1TdqSqlNumSpec_clone(src->x.num_u16, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_s32:
			// _U_cst_clone
			if (src->x.num_s32 && (ret->x.num_s32 = Dz1TdqSqlNumSpec_clone(src->x.num_s32, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_u32:
			// _U_cst_clone
			if (src->x.num_u32 && (ret->x.num_u32 = Dz1TdqSqlNumSpec_clone(src->x.num_u32, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_s64:
			// _U_cst_clone
			if (src->x.num_s64 && (ret->x.num_s64 = Dz1TdqSqlNumSpec_clone(src->x.num_s64, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_u64:
			// _U_cst_clone
			if (src->x.num_u64 && (ret->x.num_u64 = Dz1TdqSqlNumSpec_clone(src->x.num_u64, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_r32:
			// _U_cst_clone
			if (src->x.num_r32 && (ret->x.num_r32 = Dz1TdqSqlRealSpec_clone(src->x.num_r32, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_num_r64:
			// _U_cst_clone
			if (src->x.num_r64 && (ret->x.num_r64 = Dz1TdqSqlRealSpec_clone(src->x.num_r64, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_string:
			// _U_cst_clone
			if (src->x.string && (ret->x.string = Dz1TdqSqlStrSpec_clone(src->x.string, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_vstring:
			// _U_cst_clone
			if (src->x.vstring && (ret->x.vstring = Dz1TdqSqlStrSpec_clone(src->x.vstring, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_tstring:
			// _U_cst_clone
			if (src->x.tstring && (ret->x.tstring = Dz1TdqSqlStrSpec_clone(src->x.tstring, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_vtstring:
			// _U_cst_clone
			if (src->x.vtstring && (ret->x.vtstring = Dz1TdqSqlStrSpec_clone(src->x.vtstring, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_binary:
			// _U_cst_clone
			if (src->x.binary && (ret->x.binary = Dz1TdqSqlStrSpec_clone(src->x.binary, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_vbinary:
			// _U_cst_clone
			if (src->x.vbinary && (ret->x.vbinary = Dz1TdqSqlStrSpec_clone(src->x.vbinary, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_ymd:
			// _U_prim_clone
			if (src->x.ymd && (ret->x.ymd = Dz1u32_clone(src->x.ymd, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_hms:
			// _U_prim_clone
			if (src->x.hms && (ret->x.hms = Dz1u32_clone(src->x.hms, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_stamp:
			// _U_prim_clone
			if (src->x.stamp && (ret->x.stamp = Dz1u32_clone(src->x.stamp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlTypeSpecPresent_blob:
			// _U_enum_clone
			ret->x.blob = src->x.blob;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlTypeSpecPresent_blobL:
			// _U_enum_clone
			ret->x.blobL = src->x.blobL;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_clone(Dz1TdqSqlTypeSpec *src, Dz1Error *err)
{
	Dz1TdqSqlTypeSpec *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TdqSqlTypeSpec *)Dz1Calloc(sizeof(Dz1TdqSqlTypeSpec), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
		if (Dz1TdqSqlTypeSpec_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqSqlTypeSpec_purge(Dz1TdqSqlTypeSpec *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TdqSqlTypeSpecPresent_num_s8:
		Dz1TdqSqlNumSpec_del(p->x.num_s8);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_u8:
		Dz1TdqSqlNumSpec_del(p->x.num_u8);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_s16:
		Dz1TdqSqlNumSpec_del(p->x.num_s16);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_u16:
		Dz1TdqSqlNumSpec_del(p->x.num_u16);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_s32:
		Dz1TdqSqlNumSpec_del(p->x.num_s32);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_u32:
		Dz1TdqSqlNumSpec_del(p->x.num_u32);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_s64:
		Dz1TdqSqlNumSpec_del(p->x.num_s64);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_u64:
		Dz1TdqSqlNumSpec_del(p->x.num_u64);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_r32:
		Dz1TdqSqlRealSpec_del(p->x.num_r32);
		break;
	case Dz1TdqSqlTypeSpecPresent_num_r64:
		Dz1TdqSqlRealSpec_del(p->x.num_r64);
		break;
	case Dz1TdqSqlTypeSpecPresent_string:
		Dz1TdqSqlStrSpec_del(p->x.string);
		break;
	case Dz1TdqSqlTypeSpecPresent_vstring:
		Dz1TdqSqlStrSpec_del(p->x.vstring);
		break;
	case Dz1TdqSqlTypeSpecPresent_tstring:
		Dz1TdqSqlStrSpec_del(p->x.tstring);
		break;
	case Dz1TdqSqlTypeSpecPresent_vtstring:
		Dz1TdqSqlStrSpec_del(p->x.vtstring);
		break;
	case Dz1TdqSqlTypeSpecPresent_binary:
		Dz1TdqSqlStrSpec_del(p->x.binary);
		break;
	case Dz1TdqSqlTypeSpecPresent_vbinary:
		Dz1TdqSqlStrSpec_del(p->x.vbinary);
		break;
	case Dz1TdqSqlTypeSpecPresent_ymd:
		Dz1u32_del(p->x.ymd);
		break;
	case Dz1TdqSqlTypeSpecPresent_hms:
		Dz1u32_del(p->x.hms);
		break;
	case Dz1TdqSqlTypeSpecPresent_stamp:
		Dz1u32_del(p->x.stamp);
		break;
	case Dz1TdqSqlTypeSpecPresent_blob:
		break;
	case Dz1TdqSqlTypeSpecPresent_blobL:
		break;
	default:
		break;
	}
}

void Dz1TdqSqlTypeSpec_del(Dz1TdqSqlTypeSpec *p)
{
	if (!p) return;
	Dz1TdqSqlTypeSpec_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlTypeSpec_dump(Dz1TdqSqlTypeSpec *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TdqSqlTypeSpecPresent_num_s8:
		Dz1Thread_printf(Dz1T("num_s8 = ")); Dz1TdqSqlNumSpec_dump(p->x.num_s8, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_u8:
		Dz1Thread_printf(Dz1T("num_u8 = ")); Dz1TdqSqlNumSpec_dump(p->x.num_u8, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_s16:
		Dz1Thread_printf(Dz1T("num_s16 = ")); Dz1TdqSqlNumSpec_dump(p->x.num_s16, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_u16:
		Dz1Thread_printf(Dz1T("num_u16 = ")); Dz1TdqSqlNumSpec_dump(p->x.num_u16, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_s32:
		Dz1Thread_printf(Dz1T("num_s32 = ")); Dz1TdqSqlNumSpec_dump(p->x.num_s32, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_u32:
		Dz1Thread_printf(Dz1T("num_u32 = ")); Dz1TdqSqlNumSpec_dump(p->x.num_u32, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_s64:
		Dz1Thread_printf(Dz1T("num_s64 = ")); Dz1TdqSqlNumSpec_dump(p->x.num_s64, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_u64:
		Dz1Thread_printf(Dz1T("num_u64 = ")); Dz1TdqSqlNumSpec_dump(p->x.num_u64, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_r32:
		Dz1Thread_printf(Dz1T("num_r32 = ")); Dz1TdqSqlRealSpec_dump(p->x.num_r32, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_num_r64:
		Dz1Thread_printf(Dz1T("num_r64 = ")); Dz1TdqSqlRealSpec_dump(p->x.num_r64, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_string:
		Dz1Thread_printf(Dz1T("string = ")); Dz1TdqSqlStrSpec_dump(p->x.string, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_vstring:
		Dz1Thread_printf(Dz1T("vstring = ")); Dz1TdqSqlStrSpec_dump(p->x.vstring, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_tstring:
		Dz1Thread_printf(Dz1T("tstring = ")); Dz1TdqSqlStrSpec_dump(p->x.tstring, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_vtstring:
		Dz1Thread_printf(Dz1T("vtstring = ")); Dz1TdqSqlStrSpec_dump(p->x.vtstring, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_binary:
		Dz1Thread_printf(Dz1T("binary = ")); Dz1TdqSqlStrSpec_dump(p->x.binary, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_vbinary:
		Dz1Thread_printf(Dz1T("vbinary = ")); Dz1TdqSqlStrSpec_dump(p->x.vbinary, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_ymd:
		Dz1Thread_printf(Dz1T("ymd = ")); Dz1u32_dump(p->x.ymd, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_hms:
		Dz1Thread_printf(Dz1T("hms = ")); Dz1u32_dump(p->x.hms, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_stamp:
		Dz1Thread_printf(Dz1T("stamp = ")); Dz1u32_dump(p->x.stamp, tab); 
		break;
	case Dz1TdqSqlTypeSpecPresent_blob:
		Dz1Thread_printf(Dz1T("blob = %s(%d)\n"), Dz1TdqSqlBlobSpecStr(p->x.blob), p->x.blob);
		break;
	case Dz1TdqSqlTypeSpecPresent_blobL:
		Dz1Thread_printf(Dz1T("blobL = %s(%d)\n"), Dz1TdqSqlBlobSpecStr(p->x.blobL), p->x.blobL);
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TdqSqlTypeSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlStr
bool_t Dz1TdqSqlStr_copy(Dz1TdqSqlStr *dst, Dz1TdqSqlStr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->text && (dst->text = Dz1Str_clone(src->text, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->alloc_byte = src->alloc_byte;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlStr *Dz1TdqSqlStr_clone(Dz1TdqSqlStr *src, Dz1Error *err)
{
	Dz1TdqSqlStr *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlStr *)Dz1Calloc(sizeof(Dz1TdqSqlStr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlStr_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlStr_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlStr_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlStr_purge(Dz1TdqSqlStr *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->text);
}

void Dz1TdqSqlStr_del(Dz1TdqSqlStr *p)
{
	if (p == NULL) return;
	Dz1TdqSqlStr_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlStr_dump(Dz1TdqSqlStr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("text = ")); Dz1Str_dump(p->text, tab); 
		Dz1Thread_tprintf(tab, Dz1T("alloc_byte = ")); Dz1u32_dump(&p->alloc_byte, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TdqSqlStr_cmp(Dz1TdqSqlStr *a, Dz1TdqSqlStr *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->text == NULL && b->text == NULL) ret = 0;
	else if (a->text == NULL /*&& b->text != NULL*/) ret = -1;
	else if (/*a->text != NULL &&*/ b->text == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->text, b->text)) != 0) { }
	return ret;
}
// Dz1TdqSqlStr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlDate
Dz1TdqSqlDate *Dz1TdqSqlDate_new(s16_t year, u16_t month, u16_t day, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlDate *__internal_ret = (Dz1TdqSqlDate *)Dz1Calloc(sizeof(Dz1TdqSqlDate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlDate_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->year = year;
		__internal_ret->month = month;
		__internal_ret->day = day;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlDate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlDate_copy(Dz1TdqSqlDate *dst, Dz1TdqSqlDate *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->year = src->year;
		dst->month = src->month;
		dst->day = src->day;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlDate *Dz1TdqSqlDate_clone(Dz1TdqSqlDate *src, Dz1Error *err)
{
	Dz1TdqSqlDate *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlDate *)Dz1Calloc(sizeof(Dz1TdqSqlDate), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlDate_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlDate_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlDate_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlDate_purge(Dz1TdqSqlDate *p)
{
	if (p == NULL) return;
}

void Dz1TdqSqlDate_del(Dz1TdqSqlDate *p)
{
	if (p == NULL) return;
	Dz1TdqSqlDate_purge(p);
	Dz1Free(p);
}

int Dz1TdqSqlDate_cmp(Dz1TdqSqlDate *a, Dz1TdqSqlDate *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1s16_cmp(&a->year, &b->year)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->month, &b->month)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->day, &b->day)) != 0) { }
	return ret;
}
// Dz1TdqSqlDate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlTime
Dz1TdqSqlTime *Dz1TdqSqlTime_new(u16_t hour, u16_t minute, u16_t second, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlTime *__internal_ret = (Dz1TdqSqlTime *)Dz1Calloc(sizeof(Dz1TdqSqlTime), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlTime_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->hour = hour;
		__internal_ret->minute = minute;
		__internal_ret->second = second;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlTime_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlTime_copy(Dz1TdqSqlTime *dst, Dz1TdqSqlTime *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->hour = src->hour;
		dst->minute = src->minute;
		dst->second = src->second;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlTime *Dz1TdqSqlTime_clone(Dz1TdqSqlTime *src, Dz1Error *err)
{
	Dz1TdqSqlTime *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlTime *)Dz1Calloc(sizeof(Dz1TdqSqlTime), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlTime_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlTime_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlTime_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlTime_purge(Dz1TdqSqlTime *p)
{
	if (p == NULL) return;
}

void Dz1TdqSqlTime_del(Dz1TdqSqlTime *p)
{
	if (p == NULL) return;
	Dz1TdqSqlTime_purge(p);
	Dz1Free(p);
}

int Dz1TdqSqlTime_cmp(Dz1TdqSqlTime *a, Dz1TdqSqlTime *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u16_cmp(&a->hour, &b->hour)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->minute, &b->minute)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->second, &b->second)) != 0) { }
	return ret;
}
// Dz1TdqSqlTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlStamp
Dz1TdqSqlStamp *Dz1TdqSqlStamp_new(s16_t year, 
								   u16_t month, 
								   u16_t day, 
								   u16_t hour, 
								   u16_t minute, 
								   u16_t second, 
								   u32_t frac, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlStamp *__internal_ret = (Dz1TdqSqlStamp *)Dz1Calloc(sizeof(Dz1TdqSqlStamp), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlStamp_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->year = year;
		__internal_ret->month = month;
		__internal_ret->day = day;
		__internal_ret->hour = hour;
		__internal_ret->minute = minute;
		__internal_ret->second = second;
		__internal_ret->frac = frac;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlStamp_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlStamp_copy(Dz1TdqSqlStamp *dst, Dz1TdqSqlStamp *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->year = src->year;
		dst->month = src->month;
		dst->day = src->day;
		dst->hour = src->hour;
		dst->minute = src->minute;
		dst->second = src->second;
		dst->frac = src->frac;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlStamp *Dz1TdqSqlStamp_clone(Dz1TdqSqlStamp *src, Dz1Error *err)
{
	Dz1TdqSqlStamp *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlStamp *)Dz1Calloc(sizeof(Dz1TdqSqlStamp), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlStamp_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlStamp_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlStamp_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlStamp_purge(Dz1TdqSqlStamp *p)
{
	if (p == NULL) return;
}

void Dz1TdqSqlStamp_del(Dz1TdqSqlStamp *p)
{
	if (p == NULL) return;
	Dz1TdqSqlStamp_purge(p);
	Dz1Free(p);
}

int Dz1TdqSqlStamp_cmp(Dz1TdqSqlStamp *a, Dz1TdqSqlStamp *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1s16_cmp(&a->year, &b->year)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->month, &b->month)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->day, &b->day)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->hour, &b->hour)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->minute, &b->minute)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->second, &b->second)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->frac, &b->frac)) != 0) { }
	return ret;
}
// Dz1TdqSqlStamp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobRef
Dz1TdqSqlBlobRef *Dz1TdqSqlBlobRef_new(void *ptr/*_ref*/, u32_t sz, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlBlobRef *__internal_ret = (Dz1TdqSqlBlobRef *)Dz1Calloc(sizeof(Dz1TdqSqlBlobRef), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlobRef_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->ptr = ptr;
		__internal_ret->sz = sz;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlBlobRef_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlBlobRef_copy(Dz1TdqSqlBlobRef *dst, Dz1TdqSqlBlobRef *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->ptr = src->ptr;
		dst->sz = src->sz;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlBlobRef *Dz1TdqSqlBlobRef_clone(Dz1TdqSqlBlobRef *src, Dz1Error *err)
{
	Dz1TdqSqlBlobRef *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlBlobRef *)Dz1Calloc(sizeof(Dz1TdqSqlBlobRef), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlobRef_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlBlobRef_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlBlobRef_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlBlobRef_purge(Dz1TdqSqlBlobRef *p)
{
	if (p == NULL) return;
}

void Dz1TdqSqlBlobRef_del(Dz1TdqSqlBlobRef *p)
{
	if (p == NULL) return;
	Dz1TdqSqlBlobRef_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlBlobRef_dump(Dz1TdqSqlBlobRef *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ptr = %p\n"), p->ptr);
		Dz1Thread_tprintf(tab, Dz1T("sz = ")); Dz1u32_dump(&p->sz, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqSqlBlobRef
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobToDBPresent
static struct Dz1TdqSqlBlobToDBPresentMapA
{
	str_t str;
	Dz1TdqSqlBlobToDBPresent v;
} Dz1TdqSqlBlobToDBPresentMapA[] =
{
	{ (char *)"embedded", Dz1TdqSqlBlobToDBPresent_embedded },
	{ (char *)"ref_buf", Dz1TdqSqlBlobToDBPresent_ref_buf },
	{ (char *)"saved_file", Dz1TdqSqlBlobToDBPresent_saved_file },
	{ NULL, Dz1TdqSqlBlobToDBPresent_max }
};

str_t Dz1TdqSqlBlobToDBPresentStrA(Dz1TdqSqlBlobToDBPresent v)
{
	struct Dz1TdqSqlBlobToDBPresentMapA *i = NULL;
	for (i = Dz1TdqSqlBlobToDBPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlBlobToDBPresent Dz1TdqSqlBlobToDBPresentFromStrA(str_t str)
{
	struct Dz1TdqSqlBlobToDBPresentMapA *i = NULL;
	for (i = Dz1TdqSqlBlobToDBPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlBlobToDBPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqSqlBlobToDBPresentMapW
{
	wstr_t str;
	Dz1TdqSqlBlobToDBPresent v;
} Dz1TdqSqlBlobToDBPresentMapW[] =
{
	{ (wchar_t *)L"embedded", Dz1TdqSqlBlobToDBPresent_embedded },
	{ (wchar_t *)L"ref_buf", Dz1TdqSqlBlobToDBPresent_ref_buf },
	{ (wchar_t *)L"saved_file", Dz1TdqSqlBlobToDBPresent_saved_file },
	{ NULL, Dz1TdqSqlBlobToDBPresent_max }
};

wstr_t Dz1TdqSqlBlobToDBPresentStrW(Dz1TdqSqlBlobToDBPresent v)
{
	struct Dz1TdqSqlBlobToDBPresentMapW *i = NULL;
	for (i = Dz1TdqSqlBlobToDBPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlBlobToDBPresent Dz1TdqSqlBlobToDBPresentFromStrW(wstr_t str)
{
	struct Dz1TdqSqlBlobToDBPresentMapW *i = NULL;
	for (i = Dz1TdqSqlBlobToDBPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlBlobToDBPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TdqSqlBlobToDBPresent *Dz1TdqSqlBlobToDBPresent_new(Dz1TdqSqlBlobToDBPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlBlobToDBPresent *__internal_ret = (Dz1TdqSqlBlobToDBPresent *)Dz1Calloc(sizeof(Dz1TdqSqlBlobToDBPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TdqSqlBlobToDBPresent_dump(Dz1TdqSqlBlobToDBPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TdqSqlBlobToDBPresentStr(*v));
}

int Dz1TdqSqlBlobToDBPresent_cmp(Dz1TdqSqlBlobToDBPresent *a, Dz1TdqSqlBlobToDBPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// Dz1TdqSqlBlobToDBPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobToDB
Dz1TdqSqlBlobToDB *Dz1TdqSqlBlobToDB_new(Dz1TdqSqlBlobToDBPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlBlobToDB *ret = (Dz1TdqSqlBlobToDB *)Dz1Calloc(sizeof(Dz1TdqSqlBlobToDB), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlobToDB_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TdqSqlBlobToDBPresent_embedded:
			// _U_imp_clone
			if (ptr != NULL) ret->x.embedded = (Dz1Binary2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlBlobToDBPresent_ref_buf:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ref_buf = (Dz1TdqSqlBlobRef *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlBlobToDBPresent_saved_file:
			// _U_prim_clone
			if (ptr && (ret->x.saved_file = Dz1Str_clone((Dz1Str)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlBlobToDBPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlBlobToDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlBlobToDB_copy(Dz1TdqSqlBlobToDB *ret, Dz1TdqSqlBlobToDB *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TdqSqlBlobToDBPresent_embedded:
			// _U_imp_clone
			if (src->x.embedded && (ret->x.embedded = Dz1Binary2_clone(src->x.embedded, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlBlobToDBPresent_ref_buf:
			// _U_cst_clone
			if (src->x.ref_buf && (ret->x.ref_buf = Dz1TdqSqlBlobRef_clone(src->x.ref_buf, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlBlobToDBPresent_saved_file:
			// _U_prim_clone
			if (src->x.saved_file && (ret->x.saved_file = Dz1Str_clone(src->x.saved_file, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlBlobToDB *Dz1TdqSqlBlobToDB_clone(Dz1TdqSqlBlobToDB *src, Dz1Error *err)
{
	Dz1TdqSqlBlobToDB *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TdqSqlBlobToDB *)Dz1Calloc(sizeof(Dz1TdqSqlBlobToDB), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlobToDB_delAndSetNull, (void *)&ret);
		if (Dz1TdqSqlBlobToDB_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlBlobToDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqSqlBlobToDB_purge(Dz1TdqSqlBlobToDB *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TdqSqlBlobToDBPresent_embedded:
		Dz1Binary2_del(p->x.embedded);
		break;
	case Dz1TdqSqlBlobToDBPresent_ref_buf:
		Dz1TdqSqlBlobRef_del(p->x.ref_buf);
		break;
	case Dz1TdqSqlBlobToDBPresent_saved_file:
		Dz1Str_del(p->x.saved_file);
		break;
	default:
		break;
	}
}

void Dz1TdqSqlBlobToDB_del(Dz1TdqSqlBlobToDB *p)
{
	if (!p) return;
	Dz1TdqSqlBlobToDB_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlBlobToDB_dump(Dz1TdqSqlBlobToDB *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TdqSqlBlobToDBPresent_embedded:
		Dz1Thread_printf(Dz1T("embedded = ")); Dz1Binary2_dump(p->x.embedded, tab); 
		break;
	case Dz1TdqSqlBlobToDBPresent_ref_buf:
		Dz1Thread_printf(Dz1T("ref_buf = ")); Dz1TdqSqlBlobRef_dump(p->x.ref_buf, tab); 
		break;
	case Dz1TdqSqlBlobToDBPresent_saved_file:
		Dz1Thread_printf(Dz1T("saved_file = ")); Dz1Str_dump(p->x.saved_file, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int Dz1TdqSqlBlobToDB_cmp(Dz1TdqSqlBlobToDB *a, Dz1TdqSqlBlobToDB *b)
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
		case Dz1TdqSqlBlobToDBPresent_embedded:
			if (a->x.embedded == NULL && b->x.embedded == NULL) ret = 0;
			else if (a->x.embedded == NULL /*&& b->x.embedded != NULL*/) ret = -1;
			else if (/*a->x.embedded != NULL &&*/ b->x.embedded == NULL) ret = 1;
			else if ((ret = Dz1Binary2_cmp(a->x.embedded, b->x.embedded)) != 0) { }
			break;
		case Dz1TdqSqlBlobToDBPresent_ref_buf:
			if (a->x.ref_buf == NULL && b->x.ref_buf == NULL) ret = 0;
			else if (a->x.ref_buf == NULL /*&& b->x.ref_buf != NULL*/) ret = -1;
			else if (/*a->x.ref_buf != NULL &&*/ b->x.ref_buf == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlBlobRef_cmp(a->x.ref_buf, b->x.ref_buf)) != 0) { }
			break;
		case Dz1TdqSqlBlobToDBPresent_saved_file:
			if (a->x.saved_file == NULL && b->x.saved_file == NULL) ret = 0;
			else if (a->x.saved_file == NULL /*&& b->x.saved_file != NULL*/) ret = -1;
			else if (/*a->x.saved_file != NULL &&*/ b->x.saved_file == NULL) ret = 1;
			else if ((ret = Dz1Str_cmp(a->x.saved_file, b->x.saved_file)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// Dz1TdqSqlBlobToDB
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobFromDBPresent
static struct Dz1TdqSqlBlobFromDBPresentMapA
{
	str_t str;
	Dz1TdqSqlBlobFromDBPresent v;
} Dz1TdqSqlBlobFromDBPresentMapA[] =
{
	{ (char *)"embedded", Dz1TdqSqlBlobFromDBPresent_embedded },
	{ (char *)"saved_file", Dz1TdqSqlBlobFromDBPresent_saved_file },
	{ NULL, Dz1TdqSqlBlobFromDBPresent_max }
};

str_t Dz1TdqSqlBlobFromDBPresentStrA(Dz1TdqSqlBlobFromDBPresent v)
{
	struct Dz1TdqSqlBlobFromDBPresentMapA *i = NULL;
	for (i = Dz1TdqSqlBlobFromDBPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlBlobFromDBPresent Dz1TdqSqlBlobFromDBPresentFromStrA(str_t str)
{
	struct Dz1TdqSqlBlobFromDBPresentMapA *i = NULL;
	for (i = Dz1TdqSqlBlobFromDBPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlBlobFromDBPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqSqlBlobFromDBPresentMapW
{
	wstr_t str;
	Dz1TdqSqlBlobFromDBPresent v;
} Dz1TdqSqlBlobFromDBPresentMapW[] =
{
	{ (wchar_t *)L"embedded", Dz1TdqSqlBlobFromDBPresent_embedded },
	{ (wchar_t *)L"saved_file", Dz1TdqSqlBlobFromDBPresent_saved_file },
	{ NULL, Dz1TdqSqlBlobFromDBPresent_max }
};

wstr_t Dz1TdqSqlBlobFromDBPresentStrW(Dz1TdqSqlBlobFromDBPresent v)
{
	struct Dz1TdqSqlBlobFromDBPresentMapW *i = NULL;
	for (i = Dz1TdqSqlBlobFromDBPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlBlobFromDBPresent Dz1TdqSqlBlobFromDBPresentFromStrW(wstr_t str)
{
	struct Dz1TdqSqlBlobFromDBPresentMapW *i = NULL;
	for (i = Dz1TdqSqlBlobFromDBPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlBlobFromDBPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TdqSqlBlobFromDBPresent *Dz1TdqSqlBlobFromDBPresent_new(Dz1TdqSqlBlobFromDBPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlBlobFromDBPresent *__internal_ret = (Dz1TdqSqlBlobFromDBPresent *)Dz1Calloc(sizeof(Dz1TdqSqlBlobFromDBPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TdqSqlBlobFromDBPresent_dump(Dz1TdqSqlBlobFromDBPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TdqSqlBlobFromDBPresentStr(*v));
}

int Dz1TdqSqlBlobFromDBPresent_cmp(Dz1TdqSqlBlobFromDBPresent *a, Dz1TdqSqlBlobFromDBPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// Dz1TdqSqlBlobFromDBPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobFromDB
Dz1TdqSqlBlobFromDB *Dz1TdqSqlBlobFromDB_new(Dz1TdqSqlBlobFromDBPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlBlobFromDB *ret = (Dz1TdqSqlBlobFromDB *)Dz1Calloc(sizeof(Dz1TdqSqlBlobFromDB), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlobFromDB_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TdqSqlBlobFromDBPresent_embedded:
			// _U_imp_clone
			if (ptr != NULL) ret->x.embedded = (Dz1Binary2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlBlobFromDBPresent_saved_file:
			// _U_prim_clone
			if (ptr && (ret->x.saved_file = Dz1Str_clone((Dz1Str)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlBlobFromDBPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlBlobFromDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlBlobFromDB_copy(Dz1TdqSqlBlobFromDB *ret, Dz1TdqSqlBlobFromDB *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TdqSqlBlobFromDBPresent_embedded:
			// _U_imp_clone
			if (src->x.embedded && (ret->x.embedded = Dz1Binary2_clone(src->x.embedded, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlBlobFromDBPresent_saved_file:
			// _U_prim_clone
			if (src->x.saved_file && (ret->x.saved_file = Dz1Str_clone(src->x.saved_file, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlBlobFromDB *Dz1TdqSqlBlobFromDB_clone(Dz1TdqSqlBlobFromDB *src, Dz1Error *err)
{
	Dz1TdqSqlBlobFromDB *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TdqSqlBlobFromDB *)Dz1Calloc(sizeof(Dz1TdqSqlBlobFromDB), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlobFromDB_delAndSetNull, (void *)&ret);
		if (Dz1TdqSqlBlobFromDB_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlBlobFromDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqSqlBlobFromDB_purge(Dz1TdqSqlBlobFromDB *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TdqSqlBlobFromDBPresent_embedded:
		Dz1Binary2_del(p->x.embedded);
		break;
	case Dz1TdqSqlBlobFromDBPresent_saved_file:
		Dz1Str_del(p->x.saved_file);
		break;
	default:
		break;
	}
}

void Dz1TdqSqlBlobFromDB_del(Dz1TdqSqlBlobFromDB *p)
{
	if (!p) return;
	Dz1TdqSqlBlobFromDB_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlBlobFromDB_dump(Dz1TdqSqlBlobFromDB *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TdqSqlBlobFromDBPresent_embedded:
		Dz1Thread_printf(Dz1T("embedded = ")); Dz1Binary2_dump(p->x.embedded, tab); 
		break;
	case Dz1TdqSqlBlobFromDBPresent_saved_file:
		Dz1Thread_printf(Dz1T("saved_file = ")); Dz1Str_dump(p->x.saved_file, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int Dz1TdqSqlBlobFromDB_cmp(Dz1TdqSqlBlobFromDB *a, Dz1TdqSqlBlobFromDB *b)
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
		case Dz1TdqSqlBlobFromDBPresent_embedded:
			if (a->x.embedded == NULL && b->x.embedded == NULL) ret = 0;
			else if (a->x.embedded == NULL /*&& b->x.embedded != NULL*/) ret = -1;
			else if (/*a->x.embedded != NULL &&*/ b->x.embedded == NULL) ret = 1;
			else if ((ret = Dz1Binary2_cmp(a->x.embedded, b->x.embedded)) != 0) { }
			break;
		case Dz1TdqSqlBlobFromDBPresent_saved_file:
			if (a->x.saved_file == NULL && b->x.saved_file == NULL) ret = 0;
			else if (a->x.saved_file == NULL /*&& b->x.saved_file != NULL*/) ret = -1;
			else if (/*a->x.saved_file != NULL &&*/ b->x.saved_file == NULL) ret = 1;
			else if ((ret = Dz1Str_cmp(a->x.saved_file, b->x.saved_file)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// Dz1TdqSqlBlobFromDB
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlob
Dz1TdqSqlBlob *Dz1TdqSqlBlob_new(Dz1TdqSqlBlobToDB *writeToDB, 
								 Dz1TdqSqlBlobFromDB *readFromDB, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlBlob *__internal_ret = (Dz1TdqSqlBlob *)Dz1Calloc(sizeof(Dz1TdqSqlBlob), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlob_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->writeToDB = writeToDB;
		__internal_ret->readFromDB = readFromDB;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlBlob_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlBlob_copy(Dz1TdqSqlBlob *dst, Dz1TdqSqlBlob *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->writeToDB && (dst->writeToDB = Dz1TdqSqlBlobToDB_clone(src->writeToDB, errp)) == NULL) ERR_OUT(errp);
	else if (src->readFromDB && (dst->readFromDB = Dz1TdqSqlBlobFromDB_clone(src->readFromDB, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->iosz = src->iosz;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlBlob *Dz1TdqSqlBlob_clone(Dz1TdqSqlBlob *src, Dz1Error *err)
{
	Dz1TdqSqlBlob *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlBlob *)Dz1Calloc(sizeof(Dz1TdqSqlBlob), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlob_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlBlob_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlBlob_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlBlob_purge(Dz1TdqSqlBlob *p)
{
	if (p == NULL) return;
	Dz1TdqSqlBlobToDB_del(p->writeToDB);
	Dz1TdqSqlBlobFromDB_del(p->readFromDB);
}

void Dz1TdqSqlBlob_del(Dz1TdqSqlBlob *p)
{
	if (p == NULL) return;
	Dz1TdqSqlBlob_purge(p);
	Dz1Free(p);
}

int Dz1TdqSqlBlob_cmp(Dz1TdqSqlBlob *a, Dz1TdqSqlBlob *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->writeToDB == NULL && b->writeToDB == NULL) ret = 0;
	else if (a->writeToDB == NULL /*&& b->writeToDB != NULL*/) ret = -1;
	else if (/*a->writeToDB != NULL &&*/ b->writeToDB == NULL) ret = 1;
	else if ((ret = Dz1TdqSqlBlobToDB_cmp(a->writeToDB, b->writeToDB)) != 0) { }
	else if (a->readFromDB == NULL && b->readFromDB == NULL) ret = 0;
	else if (a->readFromDB == NULL /*&& b->readFromDB != NULL*/) ret = -1;
	else if (/*a->readFromDB != NULL &&*/ b->readFromDB == NULL) ret = 1;
	else if ((ret = Dz1TdqSqlBlobFromDB_cmp(a->readFromDB, b->readFromDB)) != 0) { }
	return ret;
}
// Dz1TdqSqlBlob
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarPresent
static struct Dz1TdqSqlVarPresentMapA
{
	str_t str;
	Dz1TdqSqlVarPresent v;
} Dz1TdqSqlVarPresentMapA[] =
{
	{ (char *)"s8", Dz1TdqSqlVarPresent_s8 },
	{ (char *)"u8", Dz1TdqSqlVarPresent_u8 },
	{ (char *)"s16", Dz1TdqSqlVarPresent_s16 },
	{ (char *)"u16", Dz1TdqSqlVarPresent_u16 },
	{ (char *)"s32", Dz1TdqSqlVarPresent_s32 },
	{ (char *)"u32", Dz1TdqSqlVarPresent_u32 },
	{ (char *)"s64", Dz1TdqSqlVarPresent_s64 },
	{ (char *)"u64", Dz1TdqSqlVarPresent_u64 },
	{ (char *)"r32", Dz1TdqSqlVarPresent_r32 },
	{ (char *)"r64", Dz1TdqSqlVarPresent_r64 },
	{ (char *)"string", Dz1TdqSqlVarPresent_string },
	{ (char *)"vstring", Dz1TdqSqlVarPresent_vstring },
	{ (char *)"tstring", Dz1TdqSqlVarPresent_tstring },
	{ (char *)"vtstring", Dz1TdqSqlVarPresent_vtstring },
	{ (char *)"binary", Dz1TdqSqlVarPresent_binary },
	{ (char *)"vbinary", Dz1TdqSqlVarPresent_vbinary },
	{ (char *)"ymd", Dz1TdqSqlVarPresent_ymd },
	{ (char *)"hms", Dz1TdqSqlVarPresent_hms },
	{ (char *)"stamp", Dz1TdqSqlVarPresent_stamp },
	{ (char *)"blob", Dz1TdqSqlVarPresent_blob },
	{ (char *)"blobL", Dz1TdqSqlVarPresent_blobL },
	{ (char *)"nul", Dz1TdqSqlVarPresent_nul },
	{ NULL, Dz1TdqSqlVarPresent_max }
};

str_t Dz1TdqSqlVarPresentStrA(Dz1TdqSqlVarPresent v)
{
	struct Dz1TdqSqlVarPresentMapA *i = NULL;
	for (i = Dz1TdqSqlVarPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlVarPresent Dz1TdqSqlVarPresentFromStrA(str_t str)
{
	struct Dz1TdqSqlVarPresentMapA *i = NULL;
	for (i = Dz1TdqSqlVarPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlVarPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TdqSqlVarPresentMapW
{
	wstr_t str;
	Dz1TdqSqlVarPresent v;
} Dz1TdqSqlVarPresentMapW[] =
{
	{ (wchar_t *)L"s8", Dz1TdqSqlVarPresent_s8 },
	{ (wchar_t *)L"u8", Dz1TdqSqlVarPresent_u8 },
	{ (wchar_t *)L"s16", Dz1TdqSqlVarPresent_s16 },
	{ (wchar_t *)L"u16", Dz1TdqSqlVarPresent_u16 },
	{ (wchar_t *)L"s32", Dz1TdqSqlVarPresent_s32 },
	{ (wchar_t *)L"u32", Dz1TdqSqlVarPresent_u32 },
	{ (wchar_t *)L"s64", Dz1TdqSqlVarPresent_s64 },
	{ (wchar_t *)L"u64", Dz1TdqSqlVarPresent_u64 },
	{ (wchar_t *)L"r32", Dz1TdqSqlVarPresent_r32 },
	{ (wchar_t *)L"r64", Dz1TdqSqlVarPresent_r64 },
	{ (wchar_t *)L"string", Dz1TdqSqlVarPresent_string },
	{ (wchar_t *)L"vstring", Dz1TdqSqlVarPresent_vstring },
	{ (wchar_t *)L"tstring", Dz1TdqSqlVarPresent_tstring },
	{ (wchar_t *)L"vtstring", Dz1TdqSqlVarPresent_vtstring },
	{ (wchar_t *)L"binary", Dz1TdqSqlVarPresent_binary },
	{ (wchar_t *)L"vbinary", Dz1TdqSqlVarPresent_vbinary },
	{ (wchar_t *)L"ymd", Dz1TdqSqlVarPresent_ymd },
	{ (wchar_t *)L"hms", Dz1TdqSqlVarPresent_hms },
	{ (wchar_t *)L"stamp", Dz1TdqSqlVarPresent_stamp },
	{ (wchar_t *)L"blob", Dz1TdqSqlVarPresent_blob },
	{ (wchar_t *)L"blobL", Dz1TdqSqlVarPresent_blobL },
	{ (wchar_t *)L"nul", Dz1TdqSqlVarPresent_nul },
	{ NULL, Dz1TdqSqlVarPresent_max }
};

wstr_t Dz1TdqSqlVarPresentStrW(Dz1TdqSqlVarPresent v)
{
	struct Dz1TdqSqlVarPresentMapW *i = NULL;
	for (i = Dz1TdqSqlVarPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TdqSqlVarPresent Dz1TdqSqlVarPresentFromStrW(wstr_t str)
{
	struct Dz1TdqSqlVarPresentMapW *i = NULL;
	for (i = Dz1TdqSqlVarPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TdqSqlVarPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TdqSqlVarPresent *Dz1TdqSqlVarPresent_new(Dz1TdqSqlVarPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlVarPresent *__internal_ret = (Dz1TdqSqlVarPresent *)Dz1Calloc(sizeof(Dz1TdqSqlVarPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TdqSqlVarPresent_dump(Dz1TdqSqlVarPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TdqSqlVarPresentStr(*v));
}

int Dz1TdqSqlVarPresent_cmp(Dz1TdqSqlVarPresent *a, Dz1TdqSqlVarPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// Dz1TdqSqlVarPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVar
Dz1TdqSqlVar *Dz1TdqSqlVar_new(Dz1TdqSqlVarPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlVar *ret = (Dz1TdqSqlVar *)Dz1Calloc(sizeof(Dz1TdqSqlVar), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TdqSqlVarPresent_s8:
			// _U_prim_clone
			if (ptr != NULL) ret->x.s8 = *(s8_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_u8:
			// _U_prim_clone
			if (ptr != NULL) ret->x.u8 = *(u8_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_s16:
			// _U_prim_clone
			if (ptr != NULL) ret->x.s16 = *(s16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_u16:
			// _U_prim_clone
			if (ptr != NULL) ret->x.u16 = *(u16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_s32:
			// _U_prim_clone
			if (ptr != NULL) ret->x.s32 = *(s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_u32:
			// _U_prim_clone
			if (ptr != NULL) ret->x.u32 = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_s64:
			// _U_prim_clone
			if (ptr != NULL) ret->x.s64 = *(s64_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_u64:
			// _U_prim_clone
			if (ptr != NULL) ret->x.u64 = *(u64_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_r32:
			// _U_prim_clone
			if (ptr != NULL) ret->x.r32 = *(float *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_r64:
			// _U_prim_clone
			if (ptr != NULL) ret->x.r64 = *(real64_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_string:
			// _U_cst_clone
			if (ptr != NULL) ret->x.string = (Dz1TdqSqlStr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_vstring:
			// _U_cst_clone
			if (ptr != NULL) ret->x.vstring = (Dz1TdqSqlStr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_tstring:
			// _U_cst_clone
			if (ptr != NULL) ret->x.tstring = (Dz1TdqSqlStr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_vtstring:
			// _U_cst_clone
			if (ptr != NULL) ret->x.vtstring = (Dz1TdqSqlStr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_binary:
			// _U_imp_clone
			if (ptr != NULL) ret->x.binary = (Dz1Binary2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_vbinary:
			// _U_imp_clone
			if (ptr != NULL) ret->x.vbinary = (Dz1Binary2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_ymd:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ymd = (Dz1TdqSqlDate *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_hms:
			// _U_cst_clone
			if (ptr != NULL) ret->x.hms = (Dz1TdqSqlTime *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_stamp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.stamp = (Dz1TdqSqlStamp *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_blob:
			// _U_cst_clone
			if (ptr != NULL) ret->x.blob = (Dz1TdqSqlBlob *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_blobL:
			// _U_cst_clone
			if (ptr != NULL) ret->x.blobL = (Dz1TdqSqlBlob *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_nul:
			// _U_enum_clone
			if (ptr != NULL) ret->x.nul = *(Dz1TdqType *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlVar_copy(Dz1TdqSqlVar *ret, Dz1TdqSqlVar *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TdqSqlVarPresent_s8:
			// _U_prim_clone
			ret->x.s8 = src->x.s8;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_u8:
			// _U_prim_clone
			ret->x.u8 = src->x.u8;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_s16:
			// _U_prim_clone
			ret->x.s16 = src->x.s16;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_u16:
			// _U_prim_clone
			ret->x.u16 = src->x.u16;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_s32:
			// _U_prim_clone
			ret->x.s32 = src->x.s32;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_u32:
			// _U_prim_clone
			ret->x.u32 = src->x.u32;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_s64:
			// _U_prim_clone
			ret->x.s64 = src->x.s64;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_u64:
			// _U_prim_clone
			ret->x.u64 = src->x.u64;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_r32:
			// _U_prim_clone
			ret->x.r32 = src->x.r32;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_r64:
			// _U_prim_clone
			ret->x.r64 = src->x.r64;
			ERR_CLEAR(errp);
			break;
		case Dz1TdqSqlVarPresent_string:
			// _U_cst_clone
			if (src->x.string && (ret->x.string = Dz1TdqSqlStr_clone(src->x.string, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_vstring:
			// _U_cst_clone
			if (src->x.vstring && (ret->x.vstring = Dz1TdqSqlStr_clone(src->x.vstring, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_tstring:
			// _U_cst_clone
			if (src->x.tstring && (ret->x.tstring = Dz1TdqSqlStr_clone(src->x.tstring, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_vtstring:
			// _U_cst_clone
			if (src->x.vtstring && (ret->x.vtstring = Dz1TdqSqlStr_clone(src->x.vtstring, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_binary:
			// _U_imp_clone
			if (src->x.binary && (ret->x.binary = Dz1Binary2_clone(src->x.binary, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_vbinary:
			// _U_imp_clone
			if (src->x.vbinary && (ret->x.vbinary = Dz1Binary2_clone(src->x.vbinary, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_ymd:
			// _U_cst_clone
			if (src->x.ymd && (ret->x.ymd = Dz1TdqSqlDate_clone(src->x.ymd, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_hms:
			// _U_cst_clone
			if (src->x.hms && (ret->x.hms = Dz1TdqSqlTime_clone(src->x.hms, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_stamp:
			// _U_cst_clone
			if (src->x.stamp && (ret->x.stamp = Dz1TdqSqlStamp_clone(src->x.stamp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_blob:
			// _U_cst_clone
			if (src->x.blob && (ret->x.blob = Dz1TdqSqlBlob_clone(src->x.blob, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_blobL:
			// _U_cst_clone
			if (src->x.blobL && (ret->x.blobL = Dz1TdqSqlBlob_clone(src->x.blobL, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TdqSqlVarPresent_nul:
			// _U_enum_clone
			ret->x.nul = src->x.nul;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlVar *Dz1TdqSqlVar_clone(Dz1TdqSqlVar *src, Dz1Error *err)
{
	Dz1TdqSqlVar *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TdqSqlVar *)Dz1Calloc(sizeof(Dz1TdqSqlVar), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
		if (Dz1TdqSqlVar_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqSqlVar_purge(Dz1TdqSqlVar *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TdqSqlVarPresent_s8:
		break;
	case Dz1TdqSqlVarPresent_u8:
		break;
	case Dz1TdqSqlVarPresent_s16:
		break;
	case Dz1TdqSqlVarPresent_u16:
		break;
	case Dz1TdqSqlVarPresent_s32:
		break;
	case Dz1TdqSqlVarPresent_u32:
		break;
	case Dz1TdqSqlVarPresent_s64:
		break;
	case Dz1TdqSqlVarPresent_u64:
		break;
	case Dz1TdqSqlVarPresent_r32:
		break;
	case Dz1TdqSqlVarPresent_r64:
		break;
	case Dz1TdqSqlVarPresent_string:
		Dz1TdqSqlStr_del(p->x.string);
		break;
	case Dz1TdqSqlVarPresent_vstring:
		Dz1TdqSqlStr_del(p->x.vstring);
		break;
	case Dz1TdqSqlVarPresent_tstring:
		Dz1TdqSqlStr_del(p->x.tstring);
		break;
	case Dz1TdqSqlVarPresent_vtstring:
		Dz1TdqSqlStr_del(p->x.vtstring);
		break;
	case Dz1TdqSqlVarPresent_binary:
		Dz1Binary2_del(p->x.binary);
		break;
	case Dz1TdqSqlVarPresent_vbinary:
		Dz1Binary2_del(p->x.vbinary);
		break;
	case Dz1TdqSqlVarPresent_ymd:
		Dz1TdqSqlDate_del(p->x.ymd);
		break;
	case Dz1TdqSqlVarPresent_hms:
		Dz1TdqSqlTime_del(p->x.hms);
		break;
	case Dz1TdqSqlVarPresent_stamp:
		Dz1TdqSqlStamp_del(p->x.stamp);
		break;
	case Dz1TdqSqlVarPresent_blob:
		Dz1TdqSqlBlob_del(p->x.blob);
		break;
	case Dz1TdqSqlVarPresent_blobL:
		Dz1TdqSqlBlob_del(p->x.blobL);
		break;
	case Dz1TdqSqlVarPresent_nul:
		break;
	default:
		break;
	}
}

void Dz1TdqSqlVar_del(Dz1TdqSqlVar *p)
{
	if (!p) return;
	Dz1TdqSqlVar_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlVar_dump(Dz1TdqSqlVar *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TdqSqlVarPresent_s8:
		Dz1Thread_printf(Dz1T("s8 = ")); Dz1s8_dump(&p->x.s8, tab); 
		break;
	case Dz1TdqSqlVarPresent_u8:
		Dz1Thread_printf(Dz1T("u8 = ")); Dz1u8_dump(&p->x.u8, tab); 
		break;
	case Dz1TdqSqlVarPresent_s16:
		Dz1Thread_printf(Dz1T("s16 = ")); Dz1s16_dump(&p->x.s16, tab); 
		break;
	case Dz1TdqSqlVarPresent_u16:
		Dz1Thread_printf(Dz1T("u16 = ")); Dz1u16_dump(&p->x.u16, tab); 
		break;
	case Dz1TdqSqlVarPresent_s32:
		Dz1Thread_printf(Dz1T("s32 = ")); Dz1s32_dump(&p->x.s32, tab); 
		break;
	case Dz1TdqSqlVarPresent_u32:
		Dz1Thread_printf(Dz1T("u32 = ")); Dz1u32_dump(&p->x.u32, tab); 
		break;
	case Dz1TdqSqlVarPresent_s64:
		Dz1Thread_printf(Dz1T("s64 = ")); Dz1s64_dump(&p->x.s64, tab); 
		break;
	case Dz1TdqSqlVarPresent_u64:
		Dz1Thread_printf(Dz1T("u64 = ")); Dz1u64_dump(&p->x.u64, tab); 
		break;
	case Dz1TdqSqlVarPresent_r32:
		Dz1Thread_printf(Dz1T("r32 = ")); Dz1Real32_dump(&p->x.r32, tab); 
		break;
	case Dz1TdqSqlVarPresent_r64:
		Dz1Thread_printf(Dz1T("r64 = ")); Dz1Real64_dump(&p->x.r64, tab); 
		break;
	case Dz1TdqSqlVarPresent_string:
		Dz1Thread_printf(Dz1T("string = ")); Dz1TdqSqlStr_dump(p->x.string, tab); 
		break;
	case Dz1TdqSqlVarPresent_vstring:
		Dz1Thread_printf(Dz1T("vstring = ")); Dz1TdqSqlStr_dump(p->x.vstring, tab); 
		break;
	case Dz1TdqSqlVarPresent_tstring:
		Dz1Thread_printf(Dz1T("tstring = ")); Dz1TdqSqlStr_dump(p->x.tstring, tab); 
		break;
	case Dz1TdqSqlVarPresent_vtstring:
		Dz1Thread_printf(Dz1T("vtstring = ")); Dz1TdqSqlStr_dump(p->x.vtstring, tab); 
		break;
	case Dz1TdqSqlVarPresent_binary:
		Dz1Thread_printf(Dz1T("binary = ")); Dz1Binary2_dump(p->x.binary, tab); 
		break;
	case Dz1TdqSqlVarPresent_vbinary:
		Dz1Thread_printf(Dz1T("vbinary = ")); Dz1Binary2_dump(p->x.vbinary, tab); 
		break;
	case Dz1TdqSqlVarPresent_ymd:
		Dz1Thread_printf(Dz1T("ymd = ")); Dz1TdqSqlDate_dump(p->x.ymd, tab); 
		break;
	case Dz1TdqSqlVarPresent_hms:
		Dz1Thread_printf(Dz1T("hms = ")); Dz1TdqSqlTime_dump(p->x.hms, tab); 
		break;
	case Dz1TdqSqlVarPresent_stamp:
		Dz1Thread_printf(Dz1T("stamp = ")); Dz1TdqSqlStamp_dump(p->x.stamp, tab); 
		break;
	case Dz1TdqSqlVarPresent_blob:
		Dz1Thread_printf(Dz1T("blob = ")); Dz1TdqSqlBlob_dump(p->x.blob, tab); 
		break;
	case Dz1TdqSqlVarPresent_blobL:
		Dz1Thread_printf(Dz1T("blobL = ")); Dz1TdqSqlBlob_dump(p->x.blobL, tab); 
		break;
	case Dz1TdqSqlVarPresent_nul:
		Dz1Thread_printf(Dz1T("nul = %s(%d)\n"), Dz1TdqTypeStr(p->x.nul), p->x.nul);
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int Dz1TdqSqlVar_cmp(Dz1TdqSqlVar *a, Dz1TdqSqlVar *b)
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
		case Dz1TdqSqlVarPresent_s8:
			if ((ret = Dz1s8_cmp(&a->x.s8, &b->x.s8)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_u8:
			if ((ret = Dz1u8_cmp(&a->x.u8, &b->x.u8)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_s16:
			if ((ret = Dz1s16_cmp(&a->x.s16, &b->x.s16)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_u16:
			if ((ret = Dz1u16_cmp(&a->x.u16, &b->x.u16)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_s32:
			if ((ret = Dz1s32_cmp(&a->x.s32, &b->x.s32)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_u32:
			if ((ret = Dz1u32_cmp(&a->x.u32, &b->x.u32)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_s64:
			if ((ret = Dz1s64_cmp(&a->x.s64, &b->x.s64)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_u64:
			if ((ret = Dz1u64_cmp(&a->x.u64, &b->x.u64)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_r32:
			if ((ret = Dz1Real32_cmp(&a->x.r32, &b->x.r32)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_r64:
			if ((ret = Dz1Real64_cmp(&a->x.r64, &b->x.r64)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_string:
			if (a->x.string == NULL && b->x.string == NULL) ret = 0;
			else if (a->x.string == NULL /*&& b->x.string != NULL*/) ret = -1;
			else if (/*a->x.string != NULL &&*/ b->x.string == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlStr_cmp(a->x.string, b->x.string)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_vstring:
			if (a->x.vstring == NULL && b->x.vstring == NULL) ret = 0;
			else if (a->x.vstring == NULL /*&& b->x.vstring != NULL*/) ret = -1;
			else if (/*a->x.vstring != NULL &&*/ b->x.vstring == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlStr_cmp(a->x.vstring, b->x.vstring)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_tstring:
			if (a->x.tstring == NULL && b->x.tstring == NULL) ret = 0;
			else if (a->x.tstring == NULL /*&& b->x.tstring != NULL*/) ret = -1;
			else if (/*a->x.tstring != NULL &&*/ b->x.tstring == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlStr_cmp(a->x.tstring, b->x.tstring)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_vtstring:
			if (a->x.vtstring == NULL && b->x.vtstring == NULL) ret = 0;
			else if (a->x.vtstring == NULL /*&& b->x.vtstring != NULL*/) ret = -1;
			else if (/*a->x.vtstring != NULL &&*/ b->x.vtstring == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlStr_cmp(a->x.vtstring, b->x.vtstring)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_binary:
			if (a->x.binary == NULL && b->x.binary == NULL) ret = 0;
			else if (a->x.binary == NULL /*&& b->x.binary != NULL*/) ret = -1;
			else if (/*a->x.binary != NULL &&*/ b->x.binary == NULL) ret = 1;
			else if ((ret = Dz1Binary2_cmp(a->x.binary, b->x.binary)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_vbinary:
			if (a->x.vbinary == NULL && b->x.vbinary == NULL) ret = 0;
			else if (a->x.vbinary == NULL /*&& b->x.vbinary != NULL*/) ret = -1;
			else if (/*a->x.vbinary != NULL &&*/ b->x.vbinary == NULL) ret = 1;
			else if ((ret = Dz1Binary2_cmp(a->x.vbinary, b->x.vbinary)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_ymd:
			if (a->x.ymd == NULL && b->x.ymd == NULL) ret = 0;
			else if (a->x.ymd == NULL /*&& b->x.ymd != NULL*/) ret = -1;
			else if (/*a->x.ymd != NULL &&*/ b->x.ymd == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlDate_cmp(a->x.ymd, b->x.ymd)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_hms:
			if (a->x.hms == NULL && b->x.hms == NULL) ret = 0;
			else if (a->x.hms == NULL /*&& b->x.hms != NULL*/) ret = -1;
			else if (/*a->x.hms != NULL &&*/ b->x.hms == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlTime_cmp(a->x.hms, b->x.hms)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_stamp:
			if (a->x.stamp == NULL && b->x.stamp == NULL) ret = 0;
			else if (a->x.stamp == NULL /*&& b->x.stamp != NULL*/) ret = -1;
			else if (/*a->x.stamp != NULL &&*/ b->x.stamp == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlStamp_cmp(a->x.stamp, b->x.stamp)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_blob:
			if (a->x.blob == NULL && b->x.blob == NULL) ret = 0;
			else if (a->x.blob == NULL /*&& b->x.blob != NULL*/) ret = -1;
			else if (/*a->x.blob != NULL &&*/ b->x.blob == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlBlob_cmp(a->x.blob, b->x.blob)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_blobL:
			if (a->x.blobL == NULL && b->x.blobL == NULL) ret = 0;
			else if (a->x.blobL == NULL /*&& b->x.blobL != NULL*/) ret = -1;
			else if (/*a->x.blobL != NULL &&*/ b->x.blobL == NULL) ret = 1;
			else if ((ret = Dz1TdqSqlBlob_cmp(a->x.blobL, b->x.blobL)) != 0) { }
			break;
		case Dz1TdqSqlVarPresent_nul:
			if ((ret = (int)(a->x.nul - b->x.nul)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// Dz1TdqSqlVar
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarArray
static Dz1Error Dz1TdqSqlVarArray_add(Dz1TdqSqlVarArray *p, Dz1TdqSqlVar *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqSqlVarArrayMkArrArg
{
	Dz1TdqSqlVar **arr;
	unsigned int idx;
} Dz1TdqSqlVarArrayMkArrArg;

static Dz1Error _Dz1TdqSqlVarArray_get_array(void *ptr, Dz1TdqSqlVar *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqSqlVarArrayMkArrArg *arg = (Dz1TdqSqlVarArrayMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqSqlVar **Dz1TdqSqlVarArray_get_array(Dz1TdqSqlVarArray *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqSqlVar **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqSqlVar **)Dz1Calloc(sizeof(Dz1TdqSqlVar *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqSqlVarArrayMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqSqlVarArray_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqSqlVarArray_travelForward(Dz1TdqSqlVarArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqSqlVarArray_travelBackward(Dz1TdqSqlVarArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqSqlVarArray_count(Dz1TdqSqlVarArray *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlVarArray *ret = (Dz1TdqSqlVarArray *)Dz1Calloc(sizeof(Dz1TdqSqlVarArray), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1TdqSqlVar_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqSqlVarArray_count;
			ret->travel = Dz1TdqSqlVarArray_travelForward;
			ret->travelForward = Dz1TdqSqlVarArray_travelForward;
			ret->travelBackward = Dz1TdqSqlVarArray_travelBackward;
			ret->get_array = Dz1TdqSqlVarArray_get_array;
			ret->add = Dz1TdqSqlVarArray_add;
			ret->cmp = Dz1TdqSqlVar_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqSqlVarArray_clone(void *ptr, Dz1TdqSqlVar *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqSqlVarArray *p = (Dz1TdqSqlVarArray *)ptr;
	Dz1TdqSqlVar *cloned = Dz1TdqSqlVar_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_clone(Dz1TdqSqlVarArray *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlVarArray *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlVarArray_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqSqlVarArray_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqSqlVarArray_purge(Dz1TdqSqlVarArray *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqSqlVarArray_del(Dz1TdqSqlVarArray *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqSqlVarArray_dump(void *ptr, Dz1TdqSqlVar *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqSqlVar_dump(p, tab);
	return err;
}

void Dz1TdqSqlVarArray_dump(Dz1TdqSqlVarArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqSqlVarArray_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqSqlVarArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarRefArray
static Dz1Error Dz1TdqSqlVarRefArray_add(Dz1TdqSqlVarRefArray *p, Dz1TdqSqlVar *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TdqSqlVarRefArrayMkArrArg
{
	Dz1TdqSqlVar **arr;
	unsigned int idx;
} Dz1TdqSqlVarRefArrayMkArrArg;

static Dz1Error _Dz1TdqSqlVarRefArray_get_array(void *ptr, Dz1TdqSqlVar *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqSqlVarRefArrayMkArrArg *arg = (Dz1TdqSqlVarRefArrayMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqSqlVar **Dz1TdqSqlVarRefArray_get_array(Dz1TdqSqlVarRefArray *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqSqlVar **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqSqlVar **)Dz1Calloc(sizeof(Dz1TdqSqlVar *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqSqlVarRefArrayMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqSqlVarRefArray_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqSqlVarRefArray_travelForward(Dz1TdqSqlVarRefArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqSqlVarRefArray_travelBackward(Dz1TdqSqlVarRefArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TdqSqlVarRefArray_count(Dz1TdqSqlVarRefArray *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TdqSqlVarRefArray *Dz1TdqSqlVarRefArray_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlVarRefArray *ret = (Dz1TdqSqlVarRefArray *)Dz1Calloc(sizeof(Dz1TdqSqlVarRefArray), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVarRefArray_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqSqlVarRefArray_count;
			ret->travel = Dz1TdqSqlVarRefArray_travelForward;
			ret->travelForward = Dz1TdqSqlVarRefArray_travelForward;
			ret->travelBackward = Dz1TdqSqlVarRefArray_travelBackward;
			ret->get_array = Dz1TdqSqlVarRefArray_get_array;
			ret->add = Dz1TdqSqlVarRefArray_add;
			ret->cmp = Dz1TdqSqlVar_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlVarRefArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqSqlVarRefArray_clone(void *ptr, Dz1TdqSqlVar *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqSqlVarRefArray *p = (Dz1TdqSqlVarRefArray *)ptr;
	Dz1TdqSqlVar *cloned = data; // ref
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqSqlVarRefArray *Dz1TdqSqlVarRefArray_clone(Dz1TdqSqlVarRefArray *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlVarRefArray *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlVarRefArray_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVarRefArray_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TdqSqlVarRefArray_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlVarRefArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqSqlVarRefArray_purge(Dz1TdqSqlVarRefArray *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TdqSqlVarRefArray_del(Dz1TdqSqlVarRefArray *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqSqlVarRefArray_dump(void *ptr, Dz1TdqSqlVar *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqSqlVar_dump(p, tab);
	return err;
}

void Dz1TdqSqlVarRefArray_dump(Dz1TdqSqlVarRefArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqSqlVarRefArray_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqSqlVarRefArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlNamedVar
Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_new(Dz1Str name, Dz1TdqSqlVar *val, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlNamedVar *__internal_ret = (Dz1TdqSqlNamedVar *)Dz1Calloc(sizeof(Dz1TdqSqlNamedVar), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->val = val;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqSqlNamedVar_copy(Dz1TdqSqlNamedVar *dst, Dz1TdqSqlNamedVar *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->val && (dst->val = Dz1TdqSqlVar_clone(src->val, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_clone(Dz1TdqSqlNamedVar *src, Dz1Error *err)
{
	Dz1TdqSqlNamedVar *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TdqSqlNamedVar *)Dz1Calloc(sizeof(Dz1TdqSqlNamedVar), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&dst);
		if (Dz1TdqSqlNamedVar_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TdqSqlNamedVar_purge(Dz1TdqSqlNamedVar *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1TdqSqlVar_del(p->val);
}

void Dz1TdqSqlNamedVar_del(Dz1TdqSqlNamedVar *p)
{
	if (p == NULL) return;
	Dz1TdqSqlNamedVar_purge(p);
	Dz1Free(p);
}

void Dz1TdqSqlNamedVar_dump(Dz1TdqSqlNamedVar *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("val.")); Dz1TdqSqlVar_dump(p->val, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TdqSqlNamedVar_cmp(Dz1TdqSqlNamedVar *a, Dz1TdqSqlNamedVar *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// Dz1TdqSqlNamedVar
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlNamedVarList
static Dz1Error Dz1TdqSqlNamedVarList_add(Dz1TdqSqlNamedVarList *p, Dz1TdqSqlNamedVar *data)
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

static bool_t Dz1TdqSqlNamedVarList_remove(Dz1TdqSqlNamedVarList *p, Dz1TdqSqlNamedVar *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVarList_extract(Dz1TdqSqlNamedVarList *p, Dz1TdqSqlNamedVar *key)
{
	return (Dz1TdqSqlNamedVar *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TdqSqlNamedVarListMkArrArg
{
	Dz1TdqSqlNamedVar **arr;
	unsigned int idx;
} Dz1TdqSqlNamedVarListMkArrArg;

static Dz1Error _Dz1TdqSqlNamedVarList_get_array(void *ptr, Dz1TdqSqlNamedVar *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqSqlNamedVarListMkArrArg *arg = (Dz1TdqSqlNamedVarListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TdqSqlNamedVar **Dz1TdqSqlNamedVarList_get_array(Dz1TdqSqlNamedVarList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TdqSqlNamedVar **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TdqSqlNamedVar **)Dz1Calloc(sizeof(Dz1TdqSqlNamedVar *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqSqlNamedVarListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TdqSqlNamedVarList_get_array, (void *)&arg);
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

static Dz1Error Dz1TdqSqlNamedVarList_travelForward(Dz1TdqSqlNamedVarList *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlNamedVar *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TdqSqlNamedVarList_travelBackward(Dz1TdqSqlNamedVarList *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlNamedVar *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVarList_find(Dz1TdqSqlNamedVarList *p, Dz1TdqSqlNamedVar *key)
{
	return (Dz1TdqSqlNamedVar *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TdqSqlNamedVarList_count(Dz1TdqSqlNamedVarList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TdqSqlNamedVarList *Dz1TdqSqlNamedVarList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlNamedVarList *ret = (Dz1TdqSqlNamedVarList *)Dz1Calloc(sizeof(Dz1TdqSqlNamedVarList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TdqSqlNamedVar_cmp,
				(Dz1DelFunc)Dz1TdqSqlNamedVar_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TdqSqlNamedVarList_count;
			ret->travel = Dz1TdqSqlNamedVarList_travelForward;
			ret->travelForward = Dz1TdqSqlNamedVarList_travelForward;
			ret->travelBackward = Dz1TdqSqlNamedVarList_travelBackward;
			ret->get_array = Dz1TdqSqlNamedVarList_get_array;
			ret->add = Dz1TdqSqlNamedVarList_add;
			ret->remove = Dz1TdqSqlNamedVarList_remove;
			ret->find = Dz1TdqSqlNamedVarList_find;
			ret->extract = Dz1TdqSqlNamedVarList_extract;
			ret->cmp = Dz1TdqSqlNamedVar_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TdqSqlNamedVarList_clone(void *ptr, Dz1TdqSqlNamedVar *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdqSqlNamedVarList *p = (Dz1TdqSqlNamedVarList *)ptr;
	Dz1TdqSqlNamedVar *cloned = Dz1TdqSqlNamedVar_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TdqSqlNamedVarList *Dz1TdqSqlNamedVarList_clone(Dz1TdqSqlNamedVarList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqSqlNamedVarList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlNamedVarList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TdqSqlNamedVarList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqSqlNamedVarList_purge(Dz1TdqSqlNamedVarList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TdqSqlNamedVarList_del(Dz1TdqSqlNamedVarList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TdqSqlNamedVarList_dump(void *ptr, Dz1TdqSqlNamedVar *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TdqSqlNamedVar_dump(p, tab);
	return err;
}

void Dz1TdqSqlNamedVarList_dump(Dz1TdqSqlNamedVarList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TdqSqlNamedVarList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqSqlNamedVarList
////////////////////////////////////////////////////////////////////////////////

