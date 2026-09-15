////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_asn1_codec_ber_def.h"

#include "dz1_asn1_codec.h"
////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderTagState
static struct Dz1Asn1BerDecoderTagStateMapA
{
	str_t str;
	Dz1Asn1BerDecoderTagState v;
} Dz1Asn1BerDecoderTagStateMapA[] =
{
	{ (char *)"first_byte", Dz1Asn1BerDecoderTagState_first_byte },
	{ (char *)"tag_nums", Dz1Asn1BerDecoderTagState_tag_nums },
	{ NULL, Dz1Asn1BerDecoderTagState_max }
};

str_t Dz1Asn1BerDecoderTagStateStrA(Dz1Asn1BerDecoderTagState v)
{
	struct Dz1Asn1BerDecoderTagStateMapA *i = NULL;
	for (i = Dz1Asn1BerDecoderTagStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerDecoderTagState Dz1Asn1BerDecoderTagStateFromStrA(str_t str)
{
	struct Dz1Asn1BerDecoderTagStateMapA *i = NULL;
	for (i = Dz1Asn1BerDecoderTagStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerDecoderTagState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1BerDecoderTagStateMapW
{
	wstr_t str;
	Dz1Asn1BerDecoderTagState v;
} Dz1Asn1BerDecoderTagStateMapW[] =
{
	{ (wchar_t *)L"first_byte", Dz1Asn1BerDecoderTagState_first_byte },
	{ (wchar_t *)L"tag_nums", Dz1Asn1BerDecoderTagState_tag_nums },
	{ NULL, Dz1Asn1BerDecoderTagState_max }
};

wstr_t Dz1Asn1BerDecoderTagStateStrW(Dz1Asn1BerDecoderTagState v)
{
	struct Dz1Asn1BerDecoderTagStateMapW *i = NULL;
	for (i = Dz1Asn1BerDecoderTagStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerDecoderTagState Dz1Asn1BerDecoderTagStateFromStrW(wstr_t str)
{
	struct Dz1Asn1BerDecoderTagStateMapW *i = NULL;
	for (i = Dz1Asn1BerDecoderTagStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerDecoderTagState_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1BerDecoderTagState *Dz1Asn1BerDecoderTagState_new(Dz1Asn1BerDecoderTagState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderTagState *__internal_ret = (Dz1Asn1BerDecoderTagState *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderTagState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1BerDecoderTagState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderTagCtx
Dz1Asn1BerDecoderTagCtx *Dz1Asn1BerDecoderTagCtx_new(Dz1Asn1BerDecoderTagState state, 
													 Dz1Asn1Tag *wip, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderTagCtx *__internal_ret = (Dz1Asn1BerDecoderTagCtx *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderTagCtx), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1BerDecoderTagCtx_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->state = state;
		__internal_ret->wip = wip;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1BerDecoderTagCtx_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1BerDecoderTagCtx_purge(Dz1Asn1BerDecoderTagCtx *p)
{
	if (p == NULL) return;
	Dz1Asn1Tag_del(p->wip);
}

void Dz1Asn1BerDecoderTagCtx_del(Dz1Asn1BerDecoderTagCtx *p)
{
	if (p == NULL) return;
	Dz1Asn1BerDecoderTagCtx_purge(p);
	Dz1Free(p);
}

// Dz1Asn1BerDecoderTagCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderLengthState
static struct Dz1Asn1BerDecoderLengthStateMapA
{
	str_t str;
	Dz1Asn1BerDecoderLengthState v;
} Dz1Asn1BerDecoderLengthStateMapA[] =
{
	{ (char *)"initial", Dz1Asn1BerDecoderLengthState_initial },
	{ (char *)"data_wait", Dz1Asn1BerDecoderLengthState_data_wait },
	{ NULL, Dz1Asn1BerDecoderLengthState_max }
};

str_t Dz1Asn1BerDecoderLengthStateStrA(Dz1Asn1BerDecoderLengthState v)
{
	struct Dz1Asn1BerDecoderLengthStateMapA *i = NULL;
	for (i = Dz1Asn1BerDecoderLengthStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerDecoderLengthState Dz1Asn1BerDecoderLengthStateFromStrA(str_t str)
{
	struct Dz1Asn1BerDecoderLengthStateMapA *i = NULL;
	for (i = Dz1Asn1BerDecoderLengthStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerDecoderLengthState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1BerDecoderLengthStateMapW
{
	wstr_t str;
	Dz1Asn1BerDecoderLengthState v;
} Dz1Asn1BerDecoderLengthStateMapW[] =
{
	{ (wchar_t *)L"initial", Dz1Asn1BerDecoderLengthState_initial },
	{ (wchar_t *)L"data_wait", Dz1Asn1BerDecoderLengthState_data_wait },
	{ NULL, Dz1Asn1BerDecoderLengthState_max }
};

wstr_t Dz1Asn1BerDecoderLengthStateStrW(Dz1Asn1BerDecoderLengthState v)
{
	struct Dz1Asn1BerDecoderLengthStateMapW *i = NULL;
	for (i = Dz1Asn1BerDecoderLengthStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerDecoderLengthState Dz1Asn1BerDecoderLengthStateFromStrW(wstr_t str)
{
	struct Dz1Asn1BerDecoderLengthStateMapW *i = NULL;
	for (i = Dz1Asn1BerDecoderLengthStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerDecoderLengthState_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1BerDecoderLengthState *Dz1Asn1BerDecoderLengthState_new(Dz1Asn1BerDecoderLengthState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderLengthState *__internal_ret = (Dz1Asn1BerDecoderLengthState *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderLengthState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1BerDecoderLengthState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderLengthCtx
Dz1Asn1BerDecoderLengthCtx *Dz1Asn1BerDecoderLengthCtx_new(Dz1Asn1BerDecoderLengthState state, 
														   size_t remain_bytes, 
														   u64_t wip, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderLengthCtx *__internal_ret = (Dz1Asn1BerDecoderLengthCtx *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderLengthCtx), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1BerDecoderLengthCtx_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->state = state;
		__internal_ret->remain_bytes = remain_bytes;
		__internal_ret->wip = wip;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1BerDecoderLengthCtx_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1BerDecoderLengthCtx_purge(Dz1Asn1BerDecoderLengthCtx *p)
{
	if (p == NULL) return;
}

void Dz1Asn1BerDecoderLengthCtx_del(Dz1Asn1BerDecoderLengthCtx *p)
{
	if (p == NULL) return;
	Dz1Asn1BerDecoderLengthCtx_purge(p);
	Dz1Free(p);
}

// Dz1Asn1BerDecoderLengthCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderDataState
static struct Dz1Asn1BerDecoderDataStateMapA
{
	str_t str;
	Dz1Asn1BerDecoderDataState v;
} Dz1Asn1BerDecoderDataStateMapA[] =
{
	{ (char *)"initial", Dz1Asn1BerDecoderDataState_initial },
	{ (char *)"data_wait", Dz1Asn1BerDecoderDataState_data_wait },
	{ (char *)"nested", Dz1Asn1BerDecoderDataState_nested },
	{ NULL, Dz1Asn1BerDecoderDataState_max }
};

str_t Dz1Asn1BerDecoderDataStateStrA(Dz1Asn1BerDecoderDataState v)
{
	struct Dz1Asn1BerDecoderDataStateMapA *i = NULL;
	for (i = Dz1Asn1BerDecoderDataStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerDecoderDataState Dz1Asn1BerDecoderDataStateFromStrA(str_t str)
{
	struct Dz1Asn1BerDecoderDataStateMapA *i = NULL;
	for (i = Dz1Asn1BerDecoderDataStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerDecoderDataState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1BerDecoderDataStateMapW
{
	wstr_t str;
	Dz1Asn1BerDecoderDataState v;
} Dz1Asn1BerDecoderDataStateMapW[] =
{
	{ (wchar_t *)L"initial", Dz1Asn1BerDecoderDataState_initial },
	{ (wchar_t *)L"data_wait", Dz1Asn1BerDecoderDataState_data_wait },
	{ (wchar_t *)L"nested", Dz1Asn1BerDecoderDataState_nested },
	{ NULL, Dz1Asn1BerDecoderDataState_max }
};

wstr_t Dz1Asn1BerDecoderDataStateStrW(Dz1Asn1BerDecoderDataState v)
{
	struct Dz1Asn1BerDecoderDataStateMapW *i = NULL;
	for (i = Dz1Asn1BerDecoderDataStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerDecoderDataState Dz1Asn1BerDecoderDataStateFromStrW(wstr_t str)
{
	struct Dz1Asn1BerDecoderDataStateMapW *i = NULL;
	for (i = Dz1Asn1BerDecoderDataStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerDecoderDataState_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1BerDecoderDataState *Dz1Asn1BerDecoderDataState_new(Dz1Asn1BerDecoderDataState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderDataState *__internal_ret = (Dz1Asn1BerDecoderDataState *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderDataState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1BerDecoderDataState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderDataCtx
Dz1Asn1BerDecoderDataCtx *Dz1Asn1BerDecoderDataCtx_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderDataCtx *__internal_ret = (Dz1Asn1BerDecoderDataCtx *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderDataCtx), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1BerDecoderDataCtx_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1BerDecoderDataCtx_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1BerDecoderDataCtx_purge(Dz1Asn1BerDecoderDataCtx *p)
{
	if (p == NULL) return;
	Dz1Asn1WipValue_del(p->wip);
}

void Dz1Asn1BerDecoderDataCtx_del(Dz1Asn1BerDecoderDataCtx *p)
{
	if (p == NULL) return;
	Dz1Asn1BerDecoderDataCtx_purge(p);
	Dz1Free(p);
}

void Dz1Asn1BerDecoderDataCtxA_dump(Dz1Asn1BerDecoderDataCtx *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "state = %s(%d)\n", Dz1Asn1BerDecoderDataStateStrA(p->state), p->state);
		Dz1ThreadA_tprintf(tab, "u64data = "); Dz1u64A_dump(&p->u64data, tab); 
		Dz1ThreadA_tprintf(tab, "u32data = "); Dz1u32A_dump(&p->u32data, tab); 
		Dz1ThreadA_tprintf(tab, "s32data = "); Dz1s32A_dump(&p->s32data, tab); 
		Dz1ThreadA_tprintf(tab, "u8data = "); Dz1u8A_dump(&p->u8data, tab); 
		Dz1ThreadA_tprintf(tab, "idx = "); Dz1s32A_dump(&p->idx, tab); 
		Dz1ThreadA_tprintf(tab, "wip = %p\n", p->wip);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1BerDecoderDataCtxW_dump(Dz1Asn1BerDecoderDataCtx *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"state = %s(%d)\n", Dz1Asn1BerDecoderDataStateStrW(p->state), p->state);
		Dz1ThreadW_tprintf(tab, L"u64data = "); Dz1u64W_dump(&p->u64data, tab); 
		Dz1ThreadW_tprintf(tab, L"u32data = "); Dz1u32W_dump(&p->u32data, tab); 
		Dz1ThreadW_tprintf(tab, L"s32data = "); Dz1s32W_dump(&p->s32data, tab); 
		Dz1ThreadW_tprintf(tab, L"u8data = "); Dz1u8W_dump(&p->u8data, tab); 
		Dz1ThreadW_tprintf(tab, L"idx = "); Dz1s32W_dump(&p->idx, tab); 
		Dz1ThreadW_tprintf(tab, L"wip = %p\n", p->wip);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1BerDecoderDataCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderCtxPresent
static struct Dz1Asn1BerDecoderCtxPresentMapA
{
	str_t str;
	Dz1Asn1BerDecoderCtxPresent v;
} Dz1Asn1BerDecoderCtxPresentMapA[] =
{
	{ (char *)"tag", Dz1Asn1BerDecoderCtxPresent_tag },
	{ (char *)"len", Dz1Asn1BerDecoderCtxPresent_len },
	{ (char *)"data", Dz1Asn1BerDecoderCtxPresent_data },
	{ NULL, Dz1Asn1BerDecoderCtxPresent_max }
};

str_t Dz1Asn1BerDecoderCtxPresentStrA(Dz1Asn1BerDecoderCtxPresent v)
{
	struct Dz1Asn1BerDecoderCtxPresentMapA *i = NULL;
	for (i = Dz1Asn1BerDecoderCtxPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerDecoderCtxPresent Dz1Asn1BerDecoderCtxPresentFromStrA(str_t str)
{
	struct Dz1Asn1BerDecoderCtxPresentMapA *i = NULL;
	for (i = Dz1Asn1BerDecoderCtxPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerDecoderCtxPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1BerDecoderCtxPresentMapW
{
	wstr_t str;
	Dz1Asn1BerDecoderCtxPresent v;
} Dz1Asn1BerDecoderCtxPresentMapW[] =
{
	{ (wchar_t *)L"tag", Dz1Asn1BerDecoderCtxPresent_tag },
	{ (wchar_t *)L"len", Dz1Asn1BerDecoderCtxPresent_len },
	{ (wchar_t *)L"data", Dz1Asn1BerDecoderCtxPresent_data },
	{ NULL, Dz1Asn1BerDecoderCtxPresent_max }
};

wstr_t Dz1Asn1BerDecoderCtxPresentStrW(Dz1Asn1BerDecoderCtxPresent v)
{
	struct Dz1Asn1BerDecoderCtxPresentMapW *i = NULL;
	for (i = Dz1Asn1BerDecoderCtxPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerDecoderCtxPresent Dz1Asn1BerDecoderCtxPresentFromStrW(wstr_t str)
{
	struct Dz1Asn1BerDecoderCtxPresentMapW *i = NULL;
	for (i = Dz1Asn1BerDecoderCtxPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerDecoderCtxPresent_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1BerDecoderCtxPresent *Dz1Asn1BerDecoderCtxPresent_new(Dz1Asn1BerDecoderCtxPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderCtxPresent *__internal_ret = (Dz1Asn1BerDecoderCtxPresent *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderCtxPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1BerDecoderCtxPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderCtx
Dz1Asn1BerDecoderCtx *Dz1Asn1BerDecoderCtx_new(Dz1Asn1BerDecoderCtxPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderCtx *ret = (Dz1Asn1BerDecoderCtx *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderCtx), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1BerDecoderCtx_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1Asn1BerDecoderCtxPresent_tag:
			// _U_cst_clone
			if (ptr != NULL) ret->x.tag = (Dz1Asn1BerDecoderTagCtx *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1BerDecoderCtxPresent_len:
			// _U_cst_clone
			if (ptr != NULL) ret->x.len = (Dz1Asn1BerDecoderLengthCtx *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1BerDecoderCtxPresent_data:
			// _U_cst_clone
			if (ptr != NULL) ret->x.data = (Dz1Asn1BerDecoderDataCtx *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1BerDecoderCtxPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1BerDecoderCtx_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1BerDecoderCtx_purge(Dz1Asn1BerDecoderCtx *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1Asn1BerDecoderCtxPresent_tag:
		Dz1Asn1BerDecoderTagCtx_del(p->x.tag);
		break;
	case Dz1Asn1BerDecoderCtxPresent_len:
		Dz1Asn1BerDecoderLengthCtx_del(p->x.len);
		break;
	case Dz1Asn1BerDecoderCtxPresent_data:
		Dz1Asn1BerDecoderDataCtx_del(p->x.data);
		break;
	default:
		break;
	}
}

void Dz1Asn1BerDecoderCtx_del(Dz1Asn1BerDecoderCtx *p)
{
	if (!p) return;
	Dz1Asn1BerDecoderCtx_purge(p);
	Dz1Free(p);
}

// Dz1Asn1BerDecoderCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderStk
Dz1Asn1BerDecoderStk *Dz1Asn1BerDecoderStk_new(Dz1Asn1TypeDescr *descr/*_ref*/, 
											   Dz1Asn1TagOpt tag_opt, 
											   s32_t tab, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoderStk *__internal_ret = (Dz1Asn1BerDecoderStk *)Dz1Calloc(sizeof(Dz1Asn1BerDecoderStk), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->descr = descr;
		__internal_ret->tag_opt = tag_opt;
		__internal_ret->tab = tab;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1BerDecoderStk_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1BerDecoderStk_purge(Dz1Asn1BerDecoderStk *p)
{
	if (p == NULL) return;
	Dz1Asn1BerDecoderCtx_del(p->ctx);
	Dz1Asn1Tag_del(p->tag);
	Dz1Asn1WipValue_del(p->data);
}

void Dz1Asn1BerDecoderStk_del(Dz1Asn1BerDecoderStk *p)
{
	if (p == NULL) return;
	Dz1Asn1BerDecoderStk_purge(p);
	Dz1Free(p);
}

void Dz1Asn1BerDecoderStkA_dump(Dz1Asn1BerDecoderStk *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// Recursive member
		// Cascade dump
		{	// cascade dump
			int _cnt;
			Dz1Asn1BerDecoderStk *i = NULL;
			Dz1ThreadA_tprintf(tab++, "cascade {\n");
			for (i = p->next, _cnt = 1; i; i = i->next, _cnt++)
			{
				Dz1ThreadA_tprintf(tab, "next[%d] = ", _cnt);
				Dz1Asn1BerDecoderStkA_dump(i, tab);
			}
			Dz1ThreadA_tprintf(--tab, "}\n");
		}
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "descr = %p\n", p->descr);
		Dz1ThreadA_tprintf(tab, "tag_opt = %s(%d)\n", Dz1Asn1TagOptStrA(p->tag_opt), p->tag_opt);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "child = %p\n", p->child);
		Dz1ThreadA_tprintf(tab, "ctx = %p\n", p->ctx);
		// Normal member
		Dz1ThreadA_tprintf(tab, "tag = "); Dz1Asn1TagA_dump(p->tag, tab); 
		Dz1ThreadA_tprintf(tab, "len = "); Dz1u64A_dump(&p->len, tab); 
		Dz1ThreadA_tprintf(tab, "data = %p\n", p->data);
		Dz1ThreadA_tprintf(tab, "consumed = "); Dz1u32A_dump(&p->consumed, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1ThreadA_tprintf(tab, "ret_stk = %p\n", p->ret_stk);
		Dz1ThreadA_tprintf(tab, "tab = "); Dz1s32A_dump(&p->tab, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1BerDecoderStkW_dump(Dz1Asn1BerDecoderStk *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// Recursive member
		// Cascade dump
		{	// cascade dump
			int _cnt;
			Dz1Asn1BerDecoderStk *i = NULL;
			Dz1ThreadW_tprintf(tab++, L"cascade {\n");
			for (i = p->next, _cnt = 1; i; i = i->next, _cnt++)
			{
				Dz1ThreadW_tprintf(tab, L"next[%d] = ", _cnt);
				Dz1Asn1BerDecoderStkW_dump(i, tab);
			}
			Dz1ThreadW_tprintf(--tab, L"}\n");
		}
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"descr = %p\n", p->descr);
		Dz1ThreadW_tprintf(tab, L"tag_opt = %s(%d)\n", Dz1Asn1TagOptStrW(p->tag_opt), p->tag_opt);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"child = %p\n", p->child);
		Dz1ThreadW_tprintf(tab, L"ctx = %p\n", p->ctx);
		// Normal member
		Dz1ThreadW_tprintf(tab, L"tag = "); Dz1Asn1TagW_dump(p->tag, tab); 
		Dz1ThreadW_tprintf(tab, L"len = "); Dz1u64W_dump(&p->len, tab); 
		Dz1ThreadW_tprintf(tab, L"data = %p\n", p->data);
		Dz1ThreadW_tprintf(tab, L"consumed = "); Dz1u32W_dump(&p->consumed, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1ThreadW_tprintf(tab, L"ret_stk = %p\n", p->ret_stk);
		Dz1ThreadW_tprintf(tab, L"tab = "); Dz1s32W_dump(&p->tab, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1BerDecoderStk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoder
Dz1Asn1BerDecoder *Dz1Asn1BerDecoder_new(Dz1Asn1TypeDescr *target/*_ref*/, 
										 Dz1Asn1BerDecoderStk *stk, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerDecoder *__internal_ret = (Dz1Asn1BerDecoder *)Dz1Calloc(sizeof(Dz1Asn1BerDecoder), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1BerDecoder_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->target = target;
		__internal_ret->stk = stk;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1BerDecoder_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1BerDecoder_purge(Dz1Asn1BerDecoder *p)
{
	if (p == NULL) return;
	Dz1Asn1BerDecoderStk_del(p->stk);
	Dz1Asn1WipValue_del(p->ret);
}

void Dz1Asn1BerDecoder_del(Dz1Asn1BerDecoder *p)
{
	if (p == NULL) return;
	Dz1Asn1BerDecoder_purge(p);
	Dz1Free(p);
}

// Dz1Asn1BerDecoder
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerEncoderOpt
static struct Dz1Asn1BerEncoderOptMapA
{
	str_t str;
	Dz1Asn1BerEncoderOpt v;
} Dz1Asn1BerEncoderOptMapA[] =
{
	{ (char *)"cer", Dz1Asn1BerEncoderOpt_cer },
	{ (char *)"der", Dz1Asn1BerEncoderOpt_der },
	{ NULL, Dz1Asn1BerEncoderOpt_max }
};

str_t Dz1Asn1BerEncoderOptStrA(Dz1Asn1BerEncoderOpt v)
{
	struct Dz1Asn1BerEncoderOptMapA *i = NULL;
	for (i = Dz1Asn1BerEncoderOptMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerEncoderOpt Dz1Asn1BerEncoderOptFromStrA(str_t str)
{
	struct Dz1Asn1BerEncoderOptMapA *i = NULL;
	for (i = Dz1Asn1BerEncoderOptMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerEncoderOpt_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1BerEncoderOptMapW
{
	wstr_t str;
	Dz1Asn1BerEncoderOpt v;
} Dz1Asn1BerEncoderOptMapW[] =
{
	{ (wchar_t *)L"cer", Dz1Asn1BerEncoderOpt_cer },
	{ (wchar_t *)L"der", Dz1Asn1BerEncoderOpt_der },
	{ NULL, Dz1Asn1BerEncoderOpt_max }
};

wstr_t Dz1Asn1BerEncoderOptStrW(Dz1Asn1BerEncoderOpt v)
{
	struct Dz1Asn1BerEncoderOptMapW *i = NULL;
	for (i = Dz1Asn1BerEncoderOptMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1BerEncoderOpt Dz1Asn1BerEncoderOptFromStrW(wstr_t str)
{
	struct Dz1Asn1BerEncoderOptMapW *i = NULL;
	for (i = Dz1Asn1BerEncoderOptMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1BerEncoderOpt_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1BerEncoderOpt *Dz1Asn1BerEncoderOpt_new(Dz1Asn1BerEncoderOpt *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerEncoderOpt *__internal_ret = (Dz1Asn1BerEncoderOpt *)Dz1Calloc(sizeof(Dz1Asn1BerEncoderOpt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1BerEncoderOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerEncoderStk
Dz1Asn1BerEncoderStk *Dz1Asn1BerEncoderStk_new(Dz1Asn1TypeDescr *descr/*_ref*/, 
											   Dz1Asn1TagOpt tag_opt, 
											   Dz1Asn1BerEncoderOpt codec_opt, 
											   Dz1ElasticBuf *elb, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerEncoderStk *__internal_ret = (Dz1Asn1BerEncoderStk *)Dz1Calloc(sizeof(Dz1Asn1BerEncoderStk), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1BerEncoderStk_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->descr = descr;
		__internal_ret->tag_opt = tag_opt;
		__internal_ret->codec_opt = codec_opt;
		__internal_ret->elb = elb;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1BerEncoderStk_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1BerEncoderStk_purge(Dz1Asn1BerEncoderStk *p)
{
	if (p == NULL) return;
	Dz1ElasticBuf_del(p->elb);
}

void Dz1Asn1BerEncoderStk_del(Dz1Asn1BerEncoderStk *p)
{
	if (p == NULL) return;
	Dz1Asn1BerEncoderStk_purge(p);
	Dz1Free(p);
}

void Dz1Asn1BerEncoderStkA_dump(Dz1Asn1BerEncoderStk *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// Recursive member
		// Recursive but address dump
		Dz1ThreadA_tprintf(tab, "next = %p\n", p->next);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "descr = %p\n", p->descr);
		Dz1ThreadA_tprintf(tab, "tag_opt = %s(%d)\n", Dz1Asn1TagOptStrA(p->tag_opt), p->tag_opt);
		Dz1ThreadA_tprintf(tab, "codec_opt = %s(%d)\n", Dz1Asn1BerEncoderOptStrA(p->codec_opt), p->codec_opt);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "elb = "); Dz1ElasticBufA_dump(p->elb, tab); 
		Dz1ThreadA_tprintf(tab, "is_constructed = "); Dz1BoolA_dump(&p->is_constructed, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1ThreadA_tprintf(tab, "ret_stk = %p\n", p->ret_stk);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1BerEncoderStkW_dump(Dz1Asn1BerEncoderStk *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// Recursive member
		// Recursive but address dump
		Dz1ThreadW_tprintf(tab, L"next = %p\n", p->next);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"descr = %p\n", p->descr);
		Dz1ThreadW_tprintf(tab, L"tag_opt = %s(%d)\n", Dz1Asn1TagOptStrW(p->tag_opt), p->tag_opt);
		Dz1ThreadW_tprintf(tab, L"codec_opt = %s(%d)\n", Dz1Asn1BerEncoderOptStrW(p->codec_opt), p->codec_opt);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"elb = "); Dz1ElasticBufW_dump(p->elb, tab); 
		Dz1ThreadW_tprintf(tab, L"is_constructed = "); Dz1BoolW_dump(&p->is_constructed, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1ThreadW_tprintf(tab, L"ret_stk = %p\n", p->ret_stk);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1BerEncoderStk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerEncoderArg
Dz1Asn1BerEncoderArg *Dz1Asn1BerEncoderArg_new(Dz1Asn1BerEncoderOpt opt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1BerEncoderArg *__internal_ret = (Dz1Asn1BerEncoderArg *)Dz1Calloc(sizeof(Dz1Asn1BerEncoderArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1BerEncoderArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->opt = opt;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1BerEncoderArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1BerEncoderArg_purge(Dz1Asn1BerEncoderArg *p)
{
	if (p == NULL) return;
}

void Dz1Asn1BerEncoderArg_del(Dz1Asn1BerEncoderArg *p)
{
	if (p == NULL) return;
	Dz1Asn1BerEncoderArg_purge(p);
	Dz1Free(p);
}

// Dz1Asn1BerEncoderArg
////////////////////////////////////////////////////////////////////////////////

