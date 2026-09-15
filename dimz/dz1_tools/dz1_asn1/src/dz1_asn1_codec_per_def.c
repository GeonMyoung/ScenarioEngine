////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_asn1_codec_per_def.h"

#include "dz1_asn1_codec.h"
////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerMode
static struct Dz1Asn1PerModeMapA
{
	str_t str;
	Dz1Asn1PerMode v;
} Dz1Asn1PerModeMapA[] =
{
	{ (char *)"aligned", Dz1Asn1PerMode_aligned },
	{ (char *)"unaligned", Dz1Asn1PerMode_unaligned },
	{ NULL, Dz1Asn1PerMode_max }
};

str_t Dz1Asn1PerModeStrA(Dz1Asn1PerMode v)
{
	struct Dz1Asn1PerModeMapA *i = NULL;
	for (i = Dz1Asn1PerModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1PerMode Dz1Asn1PerModeFromStrA(str_t str)
{
	struct Dz1Asn1PerModeMapA *i = NULL;
	for (i = Dz1Asn1PerModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1PerMode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1PerModeMapW
{
	wstr_t str;
	Dz1Asn1PerMode v;
} Dz1Asn1PerModeMapW[] =
{
	{ (wchar_t *)L"aligned", Dz1Asn1PerMode_aligned },
	{ (wchar_t *)L"unaligned", Dz1Asn1PerMode_unaligned },
	{ NULL, Dz1Asn1PerMode_max }
};

wstr_t Dz1Asn1PerModeStrW(Dz1Asn1PerMode v)
{
	struct Dz1Asn1PerModeMapW *i = NULL;
	for (i = Dz1Asn1PerModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1PerMode Dz1Asn1PerModeFromStrW(wstr_t str)
{
	struct Dz1Asn1PerModeMapW *i = NULL;
	for (i = Dz1Asn1PerModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1PerMode_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1PerMode *Dz1Asn1PerMode_new(Dz1Asn1PerMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1PerMode *__internal_ret = (Dz1Asn1PerMode *)Dz1Calloc(sizeof(Dz1Asn1PerMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1PerMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerDecoderStk
Dz1Asn1PerDecoderStk *Dz1Asn1PerDecoderStk_new(Dz1Asn1TypeDescr *descr/*_ref*/, 
											   s32_t tab, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1PerDecoderStk *__internal_ret = (Dz1Asn1PerDecoderStk *)Dz1Calloc(sizeof(Dz1Asn1PerDecoderStk), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1PerDecoderStk_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->descr = descr;
		__internal_ret->tab = tab;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1PerDecoderStk_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1PerDecoderStk_purge(Dz1Asn1PerDecoderStk *p)
{
	if (p == NULL) return;
}

void Dz1Asn1PerDecoderStk_del(Dz1Asn1PerDecoderStk *p)
{
	if (p == NULL) return;
	Dz1Asn1PerDecoderStk_purge(p);
	Dz1Free(p);
}

void Dz1Asn1PerDecoderStkA_dump(Dz1Asn1PerDecoderStk *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// Recursive member
		// Cascade dump
		{	// cascade dump
			int _cnt;
			Dz1Asn1PerDecoderStk *i = NULL;
			Dz1ThreadA_tprintf(tab++, "cascade {\n");
			for (i = p->next, _cnt = 1; i; i = i->next, _cnt++)
			{
				Dz1ThreadA_tprintf(tab, "next[%d] = ", _cnt);
				Dz1Asn1PerDecoderStkA_dump(i, tab);
			}
			Dz1ThreadA_tprintf(--tab, "}\n");
		}
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "descr = %p\n", p->descr);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "child = %p\n", p->child);
		Dz1ThreadA_tprintf(tab, "consumed = "); Dz1u32A_dump(&p->consumed, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1ThreadA_tprintf(tab, "ret_stk = %p\n", p->ret_stk);
		Dz1ThreadA_tprintf(tab, "tab = "); Dz1s32A_dump(&p->tab, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1PerDecoderStkW_dump(Dz1Asn1PerDecoderStk *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// Recursive member
		// Cascade dump
		{	// cascade dump
			int _cnt;
			Dz1Asn1PerDecoderStk *i = NULL;
			Dz1ThreadW_tprintf(tab++, L"cascade {\n");
			for (i = p->next, _cnt = 1; i; i = i->next, _cnt++)
			{
				Dz1ThreadW_tprintf(tab, L"next[%d] = ", _cnt);
				Dz1Asn1PerDecoderStkW_dump(i, tab);
			}
			Dz1ThreadW_tprintf(--tab, L"}\n");
		}
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"descr = %p\n", p->descr);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"child = %p\n", p->child);
		Dz1ThreadW_tprintf(tab, L"consumed = "); Dz1u32W_dump(&p->consumed, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1ThreadW_tprintf(tab, L"ret_stk = %p\n", p->ret_stk);
		Dz1ThreadW_tprintf(tab, L"tab = "); Dz1s32W_dump(&p->tab, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1PerDecoderStk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerDecoderDataState
static struct Dz1Asn1PerDecoderDataStateMapA
{
	str_t str;
	Dz1Asn1PerDecoderDataState v;
} Dz1Asn1PerDecoderDataStateMapA[] =
{
	{ (char *)"initial", Dz1Asn1PerDecoderDataState_initial },
	{ (char *)"data_wait", Dz1Asn1PerDecoderDataState_data_wait },
	{ NULL, Dz1Asn1PerDecoderDataState_max }
};

str_t Dz1Asn1PerDecoderDataStateStrA(Dz1Asn1PerDecoderDataState v)
{
	struct Dz1Asn1PerDecoderDataStateMapA *i = NULL;
	for (i = Dz1Asn1PerDecoderDataStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1PerDecoderDataState Dz1Asn1PerDecoderDataStateFromStrA(str_t str)
{
	struct Dz1Asn1PerDecoderDataStateMapA *i = NULL;
	for (i = Dz1Asn1PerDecoderDataStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1PerDecoderDataState_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1PerDecoderDataStateMapW
{
	wstr_t str;
	Dz1Asn1PerDecoderDataState v;
} Dz1Asn1PerDecoderDataStateMapW[] =
{
	{ (wchar_t *)L"initial", Dz1Asn1PerDecoderDataState_initial },
	{ (wchar_t *)L"data_wait", Dz1Asn1PerDecoderDataState_data_wait },
	{ NULL, Dz1Asn1PerDecoderDataState_max }
};

wstr_t Dz1Asn1PerDecoderDataStateStrW(Dz1Asn1PerDecoderDataState v)
{
	struct Dz1Asn1PerDecoderDataStateMapW *i = NULL;
	for (i = Dz1Asn1PerDecoderDataStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1PerDecoderDataState Dz1Asn1PerDecoderDataStateFromStrW(wstr_t str)
{
	struct Dz1Asn1PerDecoderDataStateMapW *i = NULL;
	for (i = Dz1Asn1PerDecoderDataStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1PerDecoderDataState_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1PerDecoderDataState *Dz1Asn1PerDecoderDataState_new(Dz1Asn1PerDecoderDataState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1PerDecoderDataState *__internal_ret = (Dz1Asn1PerDecoderDataState *)Dz1Calloc(sizeof(Dz1Asn1PerDecoderDataState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1Asn1PerDecoderDataStateA_dump(Dz1Asn1PerDecoderDataState *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1PerDecoderDataStateStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1PerDecoderDataStateW_dump(Dz1Asn1PerDecoderDataState *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1PerDecoderDataStateStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1PerDecoderDataState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerDecoderDataCtx
Dz1Asn1PerDecoderDataCtx *Dz1Asn1PerDecoderDataCtx_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1PerDecoderDataCtx *__internal_ret = (Dz1Asn1PerDecoderDataCtx *)Dz1Calloc(sizeof(Dz1Asn1PerDecoderDataCtx), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1PerDecoderDataCtx_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1PerDecoderDataCtx_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1PerDecoderDataCtx_purge(Dz1Asn1PerDecoderDataCtx *p)
{
	if (p == NULL) return;
	Dz1Asn1WipValue_del(p->wip);
}

void Dz1Asn1PerDecoderDataCtx_del(Dz1Asn1PerDecoderDataCtx *p)
{
	if (p == NULL) return;
	Dz1Asn1PerDecoderDataCtx_purge(p);
	Dz1Free(p);
}

void Dz1Asn1PerDecoderDataCtxA_dump(Dz1Asn1PerDecoderDataCtx *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "state = %s(%d)\n", Dz1Asn1PerDecoderDataStateStrA(p->state), p->state);
		Dz1ThreadA_tprintf(tab, "wip = %p\n", p->wip);
		Dz1ThreadA_tprintf(tab, "u64data = "); Dz1u64A_dump(&p->u64data, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1PerDecoderDataCtxW_dump(Dz1Asn1PerDecoderDataCtx *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"state = %s(%d)\n", Dz1Asn1PerDecoderDataStateStrW(p->state), p->state);
		Dz1ThreadW_tprintf(tab, L"wip = %p\n", p->wip);
		Dz1ThreadW_tprintf(tab, L"u64data = "); Dz1u64W_dump(&p->u64data, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1PerDecoderDataCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerDecoder
Dz1Asn1PerDecoder *Dz1Asn1PerDecoder_new(Dz1Asn1TypeDescr *target/*_ref*/, 
										 Dz1Asn1PerMode mode, 
										 Dz1Asn1PerDecoderStk *stk, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1PerDecoder *__internal_ret = (Dz1Asn1PerDecoder *)Dz1Calloc(sizeof(Dz1Asn1PerDecoder), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1PerDecoder_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->target = target;
		__internal_ret->mode = mode;
		__internal_ret->stk = stk;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1PerDecoder_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1PerDecoder_purge(Dz1Asn1PerDecoder *p)
{
	if (p == NULL) return;
	Dz1Asn1PerDecoderStk_del(p->stk);
	Dz1Asn1WipValue_del(p->ret);
}

void Dz1Asn1PerDecoder_del(Dz1Asn1PerDecoder *p)
{
	if (p == NULL) return;
	Dz1Asn1PerDecoder_purge(p);
	Dz1Free(p);
}

void Dz1Asn1PerDecoderA_dump(Dz1Asn1PerDecoder *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "target = %p\n", p->target);
		Dz1ThreadA_tprintf(tab, "mode = %s(%d)\n", Dz1Asn1PerModeStrA(p->mode), p->mode);
		// Normal member
		Dz1ThreadA_tprintf(tab, "stk = "); Dz1Asn1PerDecoderStkA_dump(p->stk, tab); 
		Dz1ThreadA_tprintf(tab, "ret = %p\n", p->ret);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1PerDecoderW_dump(Dz1Asn1PerDecoder *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"target = %p\n", p->target);
		Dz1ThreadW_tprintf(tab, L"mode = %s(%d)\n", Dz1Asn1PerModeStrW(p->mode), p->mode);
		// Normal member
		Dz1ThreadW_tprintf(tab, L"stk = "); Dz1Asn1PerDecoderStkW_dump(p->stk, tab); 
		Dz1ThreadW_tprintf(tab, L"ret = %p\n", p->ret);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1PerDecoder
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerEncoderArg
Dz1Asn1PerEncoderArg *Dz1Asn1PerEncoderArg_new(Dz1Asn1PerMode mode, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1PerEncoderArg *__internal_ret = (Dz1Asn1PerEncoderArg *)Dz1Calloc(sizeof(Dz1Asn1PerEncoderArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1PerEncoderArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->mode = mode;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1PerEncoderArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1PerEncoderArg_purge(Dz1Asn1PerEncoderArg *p)
{
	if (p == NULL) return;
}

void Dz1Asn1PerEncoderArg_del(Dz1Asn1PerEncoderArg *p)
{
	if (p == NULL) return;
	Dz1Asn1PerEncoderArg_purge(p);
	Dz1Free(p);
}

// Dz1Asn1PerEncoderArg
////////////////////////////////////////////////////////////////////////////////

