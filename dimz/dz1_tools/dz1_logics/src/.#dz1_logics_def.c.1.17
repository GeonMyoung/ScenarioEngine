////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_logics_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchType
static struct Dz1LogicMatchTypeMapA
{
	str_t str;
	Dz1LogicMatchType v;
} Dz1LogicMatchTypeMapA[] =
{
	{ (char *)"LessThen", Dz1LogicMatchType_LessThen },
	{ (char *)"GreaterThen", Dz1LogicMatchType_GreaterThen },
	{ (char *)"Equal", Dz1LogicMatchType_Equal },
	{ (char *)"LessEqual", Dz1LogicMatchType_LessEqual },
	{ (char *)"GreaterEqual", Dz1LogicMatchType_GreaterEqual },
	{ (char *)"Like", Dz1LogicMatchType_Like },
	{ NULL, Dz1LogicMatchType_max }
};

str_t Dz1LogicMatchTypeStrA(Dz1LogicMatchType v)
{
	struct Dz1LogicMatchTypeMapA *i = NULL;
	for (i = Dz1LogicMatchTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchType Dz1LogicMatchTypeFromStrA(str_t str)
{
	struct Dz1LogicMatchTypeMapA *i = NULL;
	for (i = Dz1LogicMatchTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1LogicMatchTypeMapW
{
	wstr_t str;
	Dz1LogicMatchType v;
} Dz1LogicMatchTypeMapW[] =
{
	{ (wchar_t *)L"LessThen", Dz1LogicMatchType_LessThen },
	{ (wchar_t *)L"GreaterThen", Dz1LogicMatchType_GreaterThen },
	{ (wchar_t *)L"Equal", Dz1LogicMatchType_Equal },
	{ (wchar_t *)L"LessEqual", Dz1LogicMatchType_LessEqual },
	{ (wchar_t *)L"GreaterEqual", Dz1LogicMatchType_GreaterEqual },
	{ (wchar_t *)L"Like", Dz1LogicMatchType_Like },
	{ NULL, Dz1LogicMatchType_max }
};

wstr_t Dz1LogicMatchTypeStrW(Dz1LogicMatchType v)
{
	struct Dz1LogicMatchTypeMapW *i = NULL;
	for (i = Dz1LogicMatchTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchType Dz1LogicMatchTypeFromStrW(wstr_t str)
{
	struct Dz1LogicMatchTypeMapW *i = NULL;
	for (i = Dz1LogicMatchTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchType_max;
}
#endif // UNIX_SYSTEM

Dz1LogicMatchType *Dz1LogicMatchType_new(Dz1LogicMatchType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchType *__internal_ret = (Dz1LogicMatchType *)Dz1Calloc(sizeof(Dz1LogicMatchType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1LogicMatchTypeA_dump(Dz1LogicMatchType *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1LogicMatchTypeStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1LogicMatchTypeW_dump(Dz1LogicMatchType *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1LogicMatchTypeStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1LogicMatchType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchNumSimple
Dz1LogicMatchNumSimple *Dz1LogicMatchNumSimple_new(s64_t value, 
												   Dz1LogicMatchType cond, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchNumSimple *__internal_ret = (Dz1LogicMatchNumSimple *)Dz1Calloc(sizeof(Dz1LogicMatchNumSimple), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchNumSimple_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->value = value;
		__internal_ret->cond = cond;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchNumSimple_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1LogicMatchNumSimple_copy(Dz1LogicMatchNumSimple *dst, Dz1LogicMatchNumSimple *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->value = src->value;
		dst->cond = src->cond;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchNumSimple *Dz1LogicMatchNumSimple_clone(Dz1LogicMatchNumSimple *src, Dz1Error *err)
{
	Dz1LogicMatchNumSimple *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1LogicMatchNumSimple *)Dz1Calloc(sizeof(Dz1LogicMatchNumSimple), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchNumSimple_delAndSetNull, (void *)&dst);
		if (Dz1LogicMatchNumSimple_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchNumSimple_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1LogicMatchNumSimple_purge(Dz1LogicMatchNumSimple *p)
{
	if (p == NULL) return;
}

void Dz1LogicMatchNumSimple_del(Dz1LogicMatchNumSimple *p)
{
	if (p == NULL) return;
	Dz1LogicMatchNumSimple_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchNumSimpleA_dump(Dz1LogicMatchNumSimple *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "value = "); Dz1s64A_dump(&p->value, tab); 
		Dz1ThreadA_tprintf(tab, "cond = %s(%d)\n", Dz1LogicMatchTypeStrA(p->cond), p->cond);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1LogicMatchNumSimpleW_dump(Dz1LogicMatchNumSimple *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"value = "); Dz1s64W_dump(&p->value, tab); 
		Dz1ThreadW_tprintf(tab, L"cond = %s(%d)\n", Dz1LogicMatchTypeStrW(p->cond), p->cond);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1LogicMatchNumSimple
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchNumRange
Dz1LogicMatchNumRange *Dz1LogicMatchNumRange_new(s64_t LowValue, 
												 bool_t LowInclude, 
												 s64_t HighValue, 
												 bool_t HighInclude, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchNumRange *__internal_ret = (Dz1LogicMatchNumRange *)Dz1Calloc(sizeof(Dz1LogicMatchNumRange), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchNumRange_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->LowValue = LowValue;
		__internal_ret->LowInclude = LowInclude;
		__internal_ret->HighValue = HighValue;
		__internal_ret->HighInclude = HighInclude;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchNumRange_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1LogicMatchNumRange_copy(Dz1LogicMatchNumRange *dst, Dz1LogicMatchNumRange *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->LowValue = src->LowValue;
		dst->LowInclude = src->LowInclude;
		dst->HighValue = src->HighValue;
		dst->HighInclude = src->HighInclude;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchNumRange *Dz1LogicMatchNumRange_clone(Dz1LogicMatchNumRange *src, Dz1Error *err)
{
	Dz1LogicMatchNumRange *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1LogicMatchNumRange *)Dz1Calloc(sizeof(Dz1LogicMatchNumRange), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchNumRange_delAndSetNull, (void *)&dst);
		if (Dz1LogicMatchNumRange_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchNumRange_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1LogicMatchNumRange_purge(Dz1LogicMatchNumRange *p)
{
	if (p == NULL) return;
}

void Dz1LogicMatchNumRange_del(Dz1LogicMatchNumRange *p)
{
	if (p == NULL) return;
	Dz1LogicMatchNumRange_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchNumRangeA_dump(Dz1LogicMatchNumRange *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "LowValue = "); Dz1s64A_dump(&p->LowValue, tab); 
		Dz1ThreadA_tprintf(tab, "LowInclude = "); Dz1BoolA_dump(&p->LowInclude, tab); 
		Dz1ThreadA_tprintf(tab, "HighValue = "); Dz1s64A_dump(&p->HighValue, tab); 
		Dz1ThreadA_tprintf(tab, "HighInclude = "); Dz1BoolA_dump(&p->HighInclude, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1LogicMatchNumRangeW_dump(Dz1LogicMatchNumRange *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"LowValue = "); Dz1s64W_dump(&p->LowValue, tab); 
		Dz1ThreadW_tprintf(tab, L"LowInclude = "); Dz1BoolW_dump(&p->LowInclude, tab); 
		Dz1ThreadW_tprintf(tab, L"HighValue = "); Dz1s64W_dump(&p->HighValue, tab); 
		Dz1ThreadW_tprintf(tab, L"HighInclude = "); Dz1BoolW_dump(&p->HighInclude, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1LogicMatchNumRange
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchNumPresent
static struct Dz1LogicMatchNumPresentMapA
{
	str_t str;
	Dz1LogicMatchNumPresent v;
} Dz1LogicMatchNumPresentMapA[] =
{
	{ (char *)"simple", Dz1LogicMatchNumPresent_simple },
	{ (char *)"range", Dz1LogicMatchNumPresent_range },
	{ NULL, Dz1LogicMatchNumPresent_max }
};

str_t Dz1LogicMatchNumPresentStrA(Dz1LogicMatchNumPresent v)
{
	struct Dz1LogicMatchNumPresentMapA *i = NULL;
	for (i = Dz1LogicMatchNumPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchNumPresent Dz1LogicMatchNumPresentFromStrA(str_t str)
{
	struct Dz1LogicMatchNumPresentMapA *i = NULL;
	for (i = Dz1LogicMatchNumPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchNumPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1LogicMatchNumPresentMapW
{
	wstr_t str;
	Dz1LogicMatchNumPresent v;
} Dz1LogicMatchNumPresentMapW[] =
{
	{ (wchar_t *)L"simple", Dz1LogicMatchNumPresent_simple },
	{ (wchar_t *)L"range", Dz1LogicMatchNumPresent_range },
	{ NULL, Dz1LogicMatchNumPresent_max }
};

wstr_t Dz1LogicMatchNumPresentStrW(Dz1LogicMatchNumPresent v)
{
	struct Dz1LogicMatchNumPresentMapW *i = NULL;
	for (i = Dz1LogicMatchNumPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchNumPresent Dz1LogicMatchNumPresentFromStrW(wstr_t str)
{
	struct Dz1LogicMatchNumPresentMapW *i = NULL;
	for (i = Dz1LogicMatchNumPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchNumPresent_max;
}
#endif // UNIX_SYSTEM

Dz1LogicMatchNumPresent *Dz1LogicMatchNumPresent_new(Dz1LogicMatchNumPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchNumPresent *__internal_ret = (Dz1LogicMatchNumPresent *)Dz1Calloc(sizeof(Dz1LogicMatchNumPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1LogicMatchNumPresentA_dump(Dz1LogicMatchNumPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1LogicMatchNumPresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1LogicMatchNumPresentW_dump(Dz1LogicMatchNumPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1LogicMatchNumPresentStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1LogicMatchNumPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchNum
Dz1LogicMatchNum *Dz1LogicMatchNum_new(Dz1LogicMatchNumPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchNum *ret = (Dz1LogicMatchNum *)Dz1Calloc(sizeof(Dz1LogicMatchNum), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchNum_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1LogicMatchNumPresent_simple:
			// _U_cst_clone
			if (ptr != NULL) ret->x.simple = (Dz1LogicMatchNumSimple *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchNumPresent_range:
			// _U_cst_clone
			if (ptr != NULL) ret->x.range = (Dz1LogicMatchNumRange *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchNumPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchNum_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1LogicMatchNum_copy(Dz1LogicMatchNum *ret, Dz1LogicMatchNum *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1LogicMatchNumPresent_simple:
			// _U_cst_clone
			if (src->x.simple && (ret->x.simple = Dz1LogicMatchNumSimple_clone(src->x.simple, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1LogicMatchNumPresent_range:
			// _U_cst_clone
			if (src->x.range && (ret->x.range = Dz1LogicMatchNumRange_clone(src->x.range, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchNum *Dz1LogicMatchNum_clone(Dz1LogicMatchNum *src, Dz1Error *err)
{
	Dz1LogicMatchNum *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1LogicMatchNum *)Dz1Calloc(sizeof(Dz1LogicMatchNum), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchNum_delAndSetNull, (void *)&ret);
		if (Dz1LogicMatchNum_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchNum_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicMatchNum_purge(Dz1LogicMatchNum *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1LogicMatchNumPresent_simple:
		Dz1LogicMatchNumSimple_del(p->x.simple);
		break;
	case Dz1LogicMatchNumPresent_range:
		Dz1LogicMatchNumRange_del(p->x.range);
		break;
	default:
		break;
	}
}

void Dz1LogicMatchNum_del(Dz1LogicMatchNum *p)
{
	if (!p) return;
	Dz1LogicMatchNum_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchNumA_dump(Dz1LogicMatchNum *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case Dz1LogicMatchNumPresent_simple:
		Dz1ThreadA_printf("simple = "); Dz1LogicMatchNumSimpleA_dump(p->x.simple, tab); 
		break;
	case Dz1LogicMatchNumPresent_range:
		Dz1ThreadA_printf("range = "); Dz1LogicMatchNumRangeA_dump(p->x.range, tab); 
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}
#ifndef UNIX_SYSTEM
void Dz1LogicMatchNumW_dump(Dz1LogicMatchNum *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case Dz1LogicMatchNumPresent_simple:
		Dz1ThreadW_printf(L"simple = "); Dz1LogicMatchNumSimpleW_dump(p->x.simple, tab); 
		break;
	case Dz1LogicMatchNumPresent_range:
		Dz1ThreadW_printf(L"range = "); Dz1LogicMatchNumRangeW_dump(p->x.range, tab); 
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}
#endif // UNIX_SYSTEM

// Dz1LogicMatchNum
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringSimpleA
Dz1LogicMatchStringSimpleA *Dz1LogicMatchStringSimpleA_new(str_t value, 
														   Dz1LogicMatchType cond, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchStringSimpleA *__internal_ret = (Dz1LogicMatchStringSimpleA *)Dz1Calloc(sizeof(Dz1LogicMatchStringSimpleA), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringSimpleA_delAndSetNull, (void *)&__internal_ret);
		
		if (value && (__internal_ret->value = dz1_built_in_str_clone(value, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->cond = cond;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringSimpleA_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1LogicMatchStringSimpleA_copy(Dz1LogicMatchStringSimpleA *dst, Dz1LogicMatchStringSimpleA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->value && (dst->value = dz1_built_in_str_clone(src->value, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cond = src->cond;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchStringSimpleA *Dz1LogicMatchStringSimpleA_clone(Dz1LogicMatchStringSimpleA *src, Dz1Error *err)
{
	Dz1LogicMatchStringSimpleA *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1LogicMatchStringSimpleA *)Dz1Calloc(sizeof(Dz1LogicMatchStringSimpleA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringSimpleA_delAndSetNull, (void *)&dst);
		if (Dz1LogicMatchStringSimpleA_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringSimpleA_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1LogicMatchStringSimpleA_purge(Dz1LogicMatchStringSimpleA *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->value);
}

void Dz1LogicMatchStringSimpleA_del(Dz1LogicMatchStringSimpleA *p)
{
	if (p == NULL) return;
	Dz1LogicMatchStringSimpleA_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchStringSimpleA_dump(Dz1LogicMatchStringSimpleA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "value = "); dz1_built_in_str_dump(p->value, tab); 
		Dz1ThreadA_tprintf(tab, "cond = %s(%d)\n", Dz1LogicMatchTypeStr(p->cond), p->cond);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
int Dz1LogicMatchStringSimpleA_cmp(Dz1LogicMatchStringSimpleA *a, Dz1LogicMatchStringSimpleA *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->value == NULL && b->value == NULL) ret = 0;
	else if (a->value == NULL /*&& b->value != NULL*/) ret = -1;
	else if (/*a->value != NULL &&*/ b->value == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->value, b->value)) != 0) { }
	return ret;
}
// Dz1LogicMatchStringSimpleA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringSimpleW
Dz1LogicMatchStringSimpleW *Dz1LogicMatchStringSimpleW_new(wstr_t value, 
														   Dz1LogicMatchType cond, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchStringSimpleW *__internal_ret = (Dz1LogicMatchStringSimpleW *)Dz1Calloc(sizeof(Dz1LogicMatchStringSimpleW), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringSimpleW_delAndSetNull, (void *)&__internal_ret);
		
		if (value && (__internal_ret->value = dz1_built_in_wstr_clone(value, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->cond = cond;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringSimpleW_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1LogicMatchStringSimpleW_copy(Dz1LogicMatchStringSimpleW *dst, Dz1LogicMatchStringSimpleW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->value && (dst->value = dz1_built_in_wstr_clone(src->value, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cond = src->cond;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchStringSimpleW *Dz1LogicMatchStringSimpleW_clone(Dz1LogicMatchStringSimpleW *src, Dz1Error *err)
{
	Dz1LogicMatchStringSimpleW *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1LogicMatchStringSimpleW *)Dz1Calloc(sizeof(Dz1LogicMatchStringSimpleW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringSimpleW_delAndSetNull, (void *)&dst);
		if (Dz1LogicMatchStringSimpleW_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringSimpleW_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1LogicMatchStringSimpleW_purge(Dz1LogicMatchStringSimpleW *p)
{
	if (p == NULL) return;
	dz1_built_in_wstr_del(p->value);
}

void Dz1LogicMatchStringSimpleW_del(Dz1LogicMatchStringSimpleW *p)
{
	if (p == NULL) return;
	Dz1LogicMatchStringSimpleW_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchStringSimpleW_dump(Dz1LogicMatchStringSimpleW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"value = "); dz1_built_in_wstr_dump(p->value, tab); 
		Dz1ThreadW_tprintf(tab, L"cond = %s(%d)\n", Dz1LogicMatchTypeStr(p->cond), p->cond);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
int Dz1LogicMatchStringSimpleW_cmp(Dz1LogicMatchStringSimpleW *a, Dz1LogicMatchStringSimpleW *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->value == NULL && b->value == NULL) ret = 0;
	else if (a->value == NULL /*&& b->value != NULL*/) ret = -1;
	else if (/*a->value != NULL &&*/ b->value == NULL) ret = 1;
	else if ((ret = dz1_built_in_wstr_cmp(a->value, b->value)) != 0) { }
	return ret;
}
// Dz1LogicMatchStringSimpleW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringsA
Dz1LogicMatchStringsA *Dz1LogicMatchStringsA_new(Dz1LogicStringArrA *arr, 
												 Dz1LogicMatchType cond, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchStringsA *__internal_ret = (Dz1LogicMatchStringsA *)Dz1Calloc(sizeof(Dz1LogicMatchStringsA), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringsA_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->arr = arr;
		__internal_ret->cond = cond;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringsA_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1LogicMatchStringsA_copy(Dz1LogicMatchStringsA *dst, Dz1LogicMatchStringsA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->arr && (dst->arr = Dz1LogicStringArrA_clone(src->arr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cond = src->cond;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchStringsA *Dz1LogicMatchStringsA_clone(Dz1LogicMatchStringsA *src, Dz1Error *err)
{
	Dz1LogicMatchStringsA *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1LogicMatchStringsA *)Dz1Calloc(sizeof(Dz1LogicMatchStringsA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringsA_delAndSetNull, (void *)&dst);
		if (Dz1LogicMatchStringsA_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringsA_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1LogicMatchStringsA_purge(Dz1LogicMatchStringsA *p)
{
	if (p == NULL) return;
	Dz1LogicStringArrA_del(p->arr);
}

void Dz1LogicMatchStringsA_del(Dz1LogicMatchStringsA *p)
{
	if (p == NULL) return;
	Dz1LogicMatchStringsA_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchStringsA_dump(Dz1LogicMatchStringsA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "arr = "); Dz1LogicStringArrA_dump(p->arr, tab); 
		Dz1ThreadA_tprintf(tab, "cond = %s(%d)\n", Dz1LogicMatchTypeStr(p->cond), p->cond);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
// Dz1LogicMatchStringsA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringsW
Dz1LogicMatchStringsW *Dz1LogicMatchStringsW_new(Dz1LogicStringArrW *arr, 
												 Dz1LogicMatchType cond, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchStringsW *__internal_ret = (Dz1LogicMatchStringsW *)Dz1Calloc(sizeof(Dz1LogicMatchStringsW), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringsW_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->arr = arr;
		__internal_ret->cond = cond;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringsW_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1LogicMatchStringsW_copy(Dz1LogicMatchStringsW *dst, Dz1LogicMatchStringsW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->arr && (dst->arr = Dz1LogicStringArrW_clone(src->arr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cond = src->cond;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchStringsW *Dz1LogicMatchStringsW_clone(Dz1LogicMatchStringsW *src, Dz1Error *err)
{
	Dz1LogicMatchStringsW *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1LogicMatchStringsW *)Dz1Calloc(sizeof(Dz1LogicMatchStringsW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringsW_delAndSetNull, (void *)&dst);
		if (Dz1LogicMatchStringsW_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringsW_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1LogicMatchStringsW_purge(Dz1LogicMatchStringsW *p)
{
	if (p == NULL) return;
	Dz1LogicStringArrW_del(p->arr);
}

void Dz1LogicMatchStringsW_del(Dz1LogicMatchStringsW *p)
{
	if (p == NULL) return;
	Dz1LogicMatchStringsW_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchStringsW_dump(Dz1LogicMatchStringsW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"arr = "); Dz1LogicStringArrW_dump(p->arr, tab); 
		Dz1ThreadW_tprintf(tab, L"cond = %s(%d)\n", Dz1LogicMatchTypeStr(p->cond), p->cond);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
// Dz1LogicMatchStringsW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchRefStringsA
Dz1LogicMatchRefStringsA *Dz1LogicMatchRefStringsA_new(Dz1LogicStringRefArrA *arr, 
													   Dz1LogicMatchType cond, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchRefStringsA *__internal_ret = (Dz1LogicMatchRefStringsA *)Dz1Calloc(sizeof(Dz1LogicMatchRefStringsA), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchRefStringsA_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->arr = arr;
		__internal_ret->cond = cond;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchRefStringsA_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1LogicMatchRefStringsA_copy(Dz1LogicMatchRefStringsA *dst, Dz1LogicMatchRefStringsA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->arr && (dst->arr = Dz1LogicStringRefArrA_clone(src->arr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cond = src->cond;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchRefStringsA *Dz1LogicMatchRefStringsA_clone(Dz1LogicMatchRefStringsA *src, Dz1Error *err)
{
	Dz1LogicMatchRefStringsA *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1LogicMatchRefStringsA *)Dz1Calloc(sizeof(Dz1LogicMatchRefStringsA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchRefStringsA_delAndSetNull, (void *)&dst);
		if (Dz1LogicMatchRefStringsA_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchRefStringsA_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1LogicMatchRefStringsA_purge(Dz1LogicMatchRefStringsA *p)
{
	if (p == NULL) return;
	Dz1LogicStringRefArrA_del(p->arr);
}

void Dz1LogicMatchRefStringsA_del(Dz1LogicMatchRefStringsA *p)
{
	if (p == NULL) return;
	Dz1LogicMatchRefStringsA_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchRefStringsA_dump(Dz1LogicMatchRefStringsA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "arr = "); Dz1LogicStringRefArrA_dump(p->arr, tab); 
		Dz1ThreadA_tprintf(tab, "cond = %s(%d)\n", Dz1LogicMatchTypeStr(p->cond), p->cond);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
// Dz1LogicMatchRefStringsA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchRefStringsW
Dz1LogicMatchRefStringsW *Dz1LogicMatchRefStringsW_new(Dz1LogicStringRefArrW *arr, 
													   Dz1LogicMatchType cond, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchRefStringsW *__internal_ret = (Dz1LogicMatchRefStringsW *)Dz1Calloc(sizeof(Dz1LogicMatchRefStringsW), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchRefStringsW_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->arr = arr;
		__internal_ret->cond = cond;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchRefStringsW_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1LogicMatchRefStringsW_copy(Dz1LogicMatchRefStringsW *dst, Dz1LogicMatchRefStringsW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->arr && (dst->arr = Dz1LogicStringRefArrW_clone(src->arr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cond = src->cond;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchRefStringsW *Dz1LogicMatchRefStringsW_clone(Dz1LogicMatchRefStringsW *src, Dz1Error *err)
{
	Dz1LogicMatchRefStringsW *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1LogicMatchRefStringsW *)Dz1Calloc(sizeof(Dz1LogicMatchRefStringsW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchRefStringsW_delAndSetNull, (void *)&dst);
		if (Dz1LogicMatchRefStringsW_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchRefStringsW_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1LogicMatchRefStringsW_purge(Dz1LogicMatchRefStringsW *p)
{
	if (p == NULL) return;
	Dz1LogicStringRefArrW_del(p->arr);
}

void Dz1LogicMatchRefStringsW_del(Dz1LogicMatchRefStringsW *p)
{
	if (p == NULL) return;
	Dz1LogicMatchRefStringsW_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchRefStringsW_dump(Dz1LogicMatchRefStringsW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"arr = "); Dz1LogicStringRefArrW_dump(p->arr, tab); 
		Dz1ThreadW_tprintf(tab, L"cond = %s(%d)\n", Dz1LogicMatchTypeStr(p->cond), p->cond);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
// Dz1LogicMatchRefStringsW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringAPresent
static struct Dz1LogicMatchStringAPresentMapA
{
	str_t str;
	Dz1LogicMatchStringAPresent v;
} Dz1LogicMatchStringAPresentMapA[] =
{
	{ (char *)"simple", Dz1LogicMatchStringAPresent_simple },
	{ (char *)"complexA", Dz1LogicMatchStringAPresent_complexA },
	{ (char *)"complexR", Dz1LogicMatchStringAPresent_complexR },
	{ NULL, Dz1LogicMatchStringAPresent_max }
};

str_t Dz1LogicMatchStringAPresentStrA(Dz1LogicMatchStringAPresent v)
{
	struct Dz1LogicMatchStringAPresentMapA *i = NULL;
	for (i = Dz1LogicMatchStringAPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchStringAPresent Dz1LogicMatchStringAPresentFromStrA(str_t str)
{
	struct Dz1LogicMatchStringAPresentMapA *i = NULL;
	for (i = Dz1LogicMatchStringAPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchStringAPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1LogicMatchStringAPresentMapW
{
	wstr_t str;
	Dz1LogicMatchStringAPresent v;
} Dz1LogicMatchStringAPresentMapW[] =
{
	{ (wchar_t *)L"simple", Dz1LogicMatchStringAPresent_simple },
	{ (wchar_t *)L"complexA", Dz1LogicMatchStringAPresent_complexA },
	{ (wchar_t *)L"complexR", Dz1LogicMatchStringAPresent_complexR },
	{ NULL, Dz1LogicMatchStringAPresent_max }
};

wstr_t Dz1LogicMatchStringAPresentStrW(Dz1LogicMatchStringAPresent v)
{
	struct Dz1LogicMatchStringAPresentMapW *i = NULL;
	for (i = Dz1LogicMatchStringAPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchStringAPresent Dz1LogicMatchStringAPresentFromStrW(wstr_t str)
{
	struct Dz1LogicMatchStringAPresentMapW *i = NULL;
	for (i = Dz1LogicMatchStringAPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchStringAPresent_max;
}
#endif // UNIX_SYSTEM

Dz1LogicMatchStringAPresent *Dz1LogicMatchStringAPresent_new(Dz1LogicMatchStringAPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchStringAPresent *__internal_ret = (Dz1LogicMatchStringAPresent *)Dz1Calloc(sizeof(Dz1LogicMatchStringAPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1LogicMatchStringAPresentA_dump(Dz1LogicMatchStringAPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1LogicMatchStringAPresentStrA(*v));
}
// Dz1LogicMatchStringAPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringA
Dz1LogicMatchStringA *Dz1LogicMatchStringA_new(Dz1LogicMatchStringAPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchStringA *ret = (Dz1LogicMatchStringA *)Dz1Calloc(sizeof(Dz1LogicMatchStringA), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringA_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1LogicMatchStringAPresent_simple:
			// _U_cst_clone
			if (ptr != NULL) ret->x.simple = (Dz1LogicMatchStringSimpleA *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchStringAPresent_complexA:
			// _U_cst_clone
			if (ptr != NULL) ret->x.complexA = (Dz1LogicMatchStringsA *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchStringAPresent_complexR:
			// _U_cst_clone
			if (ptr != NULL) ret->x.complexR = (Dz1LogicMatchRefStringsA *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchStringAPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1LogicMatchStringA_copy(Dz1LogicMatchStringA *ret, Dz1LogicMatchStringA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1LogicMatchStringAPresent_simple:
			// _U_cst_clone
			if (src->x.simple && (ret->x.simple = Dz1LogicMatchStringSimpleA_clone(src->x.simple, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1LogicMatchStringAPresent_complexA:
			// _U_cst_clone
			if (src->x.complexA && (ret->x.complexA = Dz1LogicMatchStringsA_clone(src->x.complexA, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1LogicMatchStringAPresent_complexR:
			// _U_cst_clone
			if (src->x.complexR && (ret->x.complexR = Dz1LogicMatchRefStringsA_clone(src->x.complexR, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchStringA *Dz1LogicMatchStringA_clone(Dz1LogicMatchStringA *src, Dz1Error *err)
{
	Dz1LogicMatchStringA *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1LogicMatchStringA *)Dz1Calloc(sizeof(Dz1LogicMatchStringA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringA_delAndSetNull, (void *)&ret);
		if (Dz1LogicMatchStringA_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicMatchStringA_purge(Dz1LogicMatchStringA *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1LogicMatchStringAPresent_simple:
		Dz1LogicMatchStringSimpleA_del(p->x.simple);
		break;
	case Dz1LogicMatchStringAPresent_complexA:
		Dz1LogicMatchStringsA_del(p->x.complexA);
		break;
	case Dz1LogicMatchStringAPresent_complexR:
		Dz1LogicMatchRefStringsA_del(p->x.complexR);
		break;
	default:
		break;
	}
}

void Dz1LogicMatchStringA_del(Dz1LogicMatchStringA *p)
{
	if (!p) return;
	Dz1LogicMatchStringA_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchStringA_dump(Dz1LogicMatchStringA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case Dz1LogicMatchStringAPresent_simple:
		Dz1ThreadA_printf("simple = "); Dz1LogicMatchStringSimpleA_dump(p->x.simple, tab); 
		break;
	case Dz1LogicMatchStringAPresent_complexA:
		Dz1ThreadA_printf("complexA = "); Dz1LogicMatchStringsA_dump(p->x.complexA, tab); 
		break;
	case Dz1LogicMatchStringAPresent_complexR:
		Dz1ThreadA_printf("complexR = "); Dz1LogicMatchRefStringsA_dump(p->x.complexR, tab); 
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}

// Dz1LogicMatchStringA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringWPresent
static struct Dz1LogicMatchStringWPresentMapA
{
	str_t str;
	Dz1LogicMatchStringWPresent v;
} Dz1LogicMatchStringWPresentMapA[] =
{
	{ (char *)"simple", Dz1LogicMatchStringWPresent_simple },
	{ (char *)"complexA", Dz1LogicMatchStringWPresent_complexA },
	{ (char *)"complexR", Dz1LogicMatchStringWPresent_complexR },
	{ NULL, Dz1LogicMatchStringWPresent_max }
};

str_t Dz1LogicMatchStringWPresentStrA(Dz1LogicMatchStringWPresent v)
{
	struct Dz1LogicMatchStringWPresentMapA *i = NULL;
	for (i = Dz1LogicMatchStringWPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchStringWPresent Dz1LogicMatchStringWPresentFromStrA(str_t str)
{
	struct Dz1LogicMatchStringWPresentMapA *i = NULL;
	for (i = Dz1LogicMatchStringWPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchStringWPresent_max;
}
static struct Dz1LogicMatchStringWPresentMapW
{
	wstr_t str;
	Dz1LogicMatchStringWPresent v;
} Dz1LogicMatchStringWPresentMapW[] =
{
	{ (wchar_t *)L"simple", Dz1LogicMatchStringWPresent_simple },
	{ (wchar_t *)L"complexA", Dz1LogicMatchStringWPresent_complexA },
	{ (wchar_t *)L"complexR", Dz1LogicMatchStringWPresent_complexR },
	{ NULL, Dz1LogicMatchStringWPresent_max }
};

wstr_t Dz1LogicMatchStringWPresentStrW(Dz1LogicMatchStringWPresent v)
{
	struct Dz1LogicMatchStringWPresentMapW *i = NULL;
	for (i = Dz1LogicMatchStringWPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchStringWPresent Dz1LogicMatchStringWPresentFromStrW(wstr_t str)
{
	struct Dz1LogicMatchStringWPresentMapW *i = NULL;
	for (i = Dz1LogicMatchStringWPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchStringWPresent_max;
}

Dz1LogicMatchStringWPresent *Dz1LogicMatchStringWPresent_new(Dz1LogicMatchStringWPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchStringWPresent *__internal_ret = (Dz1LogicMatchStringWPresent *)Dz1Calloc(sizeof(Dz1LogicMatchStringWPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1LogicMatchStringWPresentW_dump(Dz1LogicMatchStringWPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1LogicMatchStringWPresentStrW(*v));
}
// Dz1LogicMatchStringWPresent
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringW
Dz1LogicMatchStringW *Dz1LogicMatchStringW_new(Dz1LogicMatchStringWPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchStringW *ret = (Dz1LogicMatchStringW *)Dz1Calloc(sizeof(Dz1LogicMatchStringW), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringW_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1LogicMatchStringWPresent_simple:
			// _U_cst_clone
			if (ptr != NULL) ret->x.simple = (Dz1LogicMatchStringSimpleW *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchStringWPresent_complexA:
			// _U_cst_clone
			if (ptr != NULL) ret->x.complexA = (Dz1LogicMatchStringsW *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchStringWPresent_complexR:
			// _U_cst_clone
			if (ptr != NULL) ret->x.complexR = (Dz1LogicMatchRefStringsW *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchStringWPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1LogicMatchStringW_copy(Dz1LogicMatchStringW *ret, Dz1LogicMatchStringW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1LogicMatchStringWPresent_simple:
			// _U_cst_clone
			if (src->x.simple && (ret->x.simple = Dz1LogicMatchStringSimpleW_clone(src->x.simple, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1LogicMatchStringWPresent_complexA:
			// _U_cst_clone
			if (src->x.complexA && (ret->x.complexA = Dz1LogicMatchStringsW_clone(src->x.complexA, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1LogicMatchStringWPresent_complexR:
			// _U_cst_clone
			if (src->x.complexR && (ret->x.complexR = Dz1LogicMatchRefStringsW_clone(src->x.complexR, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchStringW *Dz1LogicMatchStringW_clone(Dz1LogicMatchStringW *src, Dz1Error *err)
{
	Dz1LogicMatchStringW *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1LogicMatchStringW *)Dz1Calloc(sizeof(Dz1LogicMatchStringW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchStringW_delAndSetNull, (void *)&ret);
		if (Dz1LogicMatchStringW_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchStringW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicMatchStringW_purge(Dz1LogicMatchStringW *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1LogicMatchStringWPresent_simple:
		Dz1LogicMatchStringSimpleW_del(p->x.simple);
		break;
	case Dz1LogicMatchStringWPresent_complexA:
		Dz1LogicMatchStringsW_del(p->x.complexA);
		break;
	case Dz1LogicMatchStringWPresent_complexR:
		Dz1LogicMatchRefStringsW_del(p->x.complexR);
		break;
	default:
		break;
	}
}

void Dz1LogicMatchStringW_del(Dz1LogicMatchStringW *p)
{
	if (!p) return;
	Dz1LogicMatchStringW_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchStringW_dump(Dz1LogicMatchStringW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case Dz1LogicMatchStringWPresent_simple:
		Dz1ThreadW_printf(L"simple = "); Dz1LogicMatchStringSimpleW_dump(p->x.simple, tab); 
		break;
	case Dz1LogicMatchStringWPresent_complexA:
		Dz1ThreadW_printf(L"complexA = "); Dz1LogicMatchStringsW_dump(p->x.complexA, tab); 
		break;
	case Dz1LogicMatchStringWPresent_complexR:
		Dz1ThreadW_printf(L"complexR = "); Dz1LogicMatchRefStringsW_dump(p->x.complexR, tab); 
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}

// Dz1LogicMatchStringW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchAPresent
static struct Dz1LogicMatchAPresentMapA
{
	str_t str;
	Dz1LogicMatchAPresent v;
} Dz1LogicMatchAPresentMapA[] =
{
	{ (char *)"number", Dz1LogicMatchAPresent_number },
	{ (char *)"text", Dz1LogicMatchAPresent_text },
	{ NULL, Dz1LogicMatchAPresent_max }
};

str_t Dz1LogicMatchAPresentStrA(Dz1LogicMatchAPresent v)
{
	struct Dz1LogicMatchAPresentMapA *i = NULL;
	for (i = Dz1LogicMatchAPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchAPresent Dz1LogicMatchAPresentFromStrA(str_t str)
{
	struct Dz1LogicMatchAPresentMapA *i = NULL;
	for (i = Dz1LogicMatchAPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchAPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1LogicMatchAPresentMapW
{
	wstr_t str;
	Dz1LogicMatchAPresent v;
} Dz1LogicMatchAPresentMapW[] =
{
	{ (wchar_t *)L"number", Dz1LogicMatchAPresent_number },
	{ (wchar_t *)L"text", Dz1LogicMatchAPresent_text },
	{ NULL, Dz1LogicMatchAPresent_max }
};

wstr_t Dz1LogicMatchAPresentStrW(Dz1LogicMatchAPresent v)
{
	struct Dz1LogicMatchAPresentMapW *i = NULL;
	for (i = Dz1LogicMatchAPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchAPresent Dz1LogicMatchAPresentFromStrW(wstr_t str)
{
	struct Dz1LogicMatchAPresentMapW *i = NULL;
	for (i = Dz1LogicMatchAPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchAPresent_max;
}
#endif // UNIX_SYSTEM

Dz1LogicMatchAPresent *Dz1LogicMatchAPresent_new(Dz1LogicMatchAPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchAPresent *__internal_ret = (Dz1LogicMatchAPresent *)Dz1Calloc(sizeof(Dz1LogicMatchAPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1LogicMatchAPresentA_dump(Dz1LogicMatchAPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1LogicMatchAPresentStrA(*v));
}
// Dz1LogicMatchAPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchA
Dz1LogicMatchA *Dz1LogicMatchA_new(Dz1LogicMatchAPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchA *ret = (Dz1LogicMatchA *)Dz1Calloc(sizeof(Dz1LogicMatchA), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchA_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1LogicMatchAPresent_number:
			// _U_cst_clone
			if (ptr != NULL) ret->x.number = (Dz1LogicMatchNum *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchAPresent_text:
			// _U_cst_clone
			if (ptr != NULL) ret->x.text = (Dz1LogicMatchStringA *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchAPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1LogicMatchA_copy(Dz1LogicMatchA *ret, Dz1LogicMatchA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1LogicMatchAPresent_number:
			// _U_cst_clone
			if (src->x.number && (ret->x.number = Dz1LogicMatchNum_clone(src->x.number, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1LogicMatchAPresent_text:
			// _U_cst_clone
			if (src->x.text && (ret->x.text = Dz1LogicMatchStringA_clone(src->x.text, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchA *Dz1LogicMatchA_clone(Dz1LogicMatchA *src, Dz1Error *err)
{
	Dz1LogicMatchA *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1LogicMatchA *)Dz1Calloc(sizeof(Dz1LogicMatchA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchA_delAndSetNull, (void *)&ret);
		if (Dz1LogicMatchA_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicMatchA_purge(Dz1LogicMatchA *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1LogicMatchAPresent_number:
		Dz1LogicMatchNum_del(p->x.number);
		break;
	case Dz1LogicMatchAPresent_text:
		Dz1LogicMatchStringA_del(p->x.text);
		break;
	default:
		break;
	}
}

void Dz1LogicMatchA_del(Dz1LogicMatchA *p)
{
	if (!p) return;
	Dz1LogicMatchA_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchA_dump(Dz1LogicMatchA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case Dz1LogicMatchAPresent_number:
		Dz1ThreadA_printf("number."); Dz1LogicMatchNum_dump(p->x.number, tab); 
		break;
	case Dz1LogicMatchAPresent_text:
		Dz1ThreadA_printf("text."); Dz1LogicMatchStringA_dump(p->x.text, tab); 
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}

// Dz1LogicMatchA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchWPresent
static struct Dz1LogicMatchWPresentMapA
{
	str_t str;
	Dz1LogicMatchWPresent v;
} Dz1LogicMatchWPresentMapA[] =
{
	{ (char *)"number", Dz1LogicMatchWPresent_number },
	{ (char *)"text", Dz1LogicMatchWPresent_text },
	{ NULL, Dz1LogicMatchWPresent_max }
};

str_t Dz1LogicMatchWPresentStrA(Dz1LogicMatchWPresent v)
{
	struct Dz1LogicMatchWPresentMapA *i = NULL;
	for (i = Dz1LogicMatchWPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchWPresent Dz1LogicMatchWPresentFromStrA(str_t str)
{
	struct Dz1LogicMatchWPresentMapA *i = NULL;
	for (i = Dz1LogicMatchWPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchWPresent_max;
}
static struct Dz1LogicMatchWPresentMapW
{
	wstr_t str;
	Dz1LogicMatchWPresent v;
} Dz1LogicMatchWPresentMapW[] =
{
	{ (wchar_t *)L"number", Dz1LogicMatchWPresent_number },
	{ (wchar_t *)L"text", Dz1LogicMatchWPresent_text },
	{ NULL, Dz1LogicMatchWPresent_max }
};

wstr_t Dz1LogicMatchWPresentStrW(Dz1LogicMatchWPresent v)
{
	struct Dz1LogicMatchWPresentMapW *i = NULL;
	for (i = Dz1LogicMatchWPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchWPresent Dz1LogicMatchWPresentFromStrW(wstr_t str)
{
	struct Dz1LogicMatchWPresentMapW *i = NULL;
	for (i = Dz1LogicMatchWPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchWPresent_max;
}

Dz1LogicMatchWPresent *Dz1LogicMatchWPresent_new(Dz1LogicMatchWPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchWPresent *__internal_ret = (Dz1LogicMatchWPresent *)Dz1Calloc(sizeof(Dz1LogicMatchWPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1LogicMatchWPresentW_dump(Dz1LogicMatchWPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1LogicMatchWPresentStrW(*v));
}
// Dz1LogicMatchWPresent
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchW
Dz1LogicMatchW *Dz1LogicMatchW_new(Dz1LogicMatchWPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchW *ret = (Dz1LogicMatchW *)Dz1Calloc(sizeof(Dz1LogicMatchW), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchW_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1LogicMatchWPresent_number:
			// _U_cst_clone
			if (ptr != NULL) ret->x.number = (Dz1LogicMatchNum *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchWPresent_text:
			// _U_cst_clone
			if (ptr != NULL) ret->x.text = (Dz1LogicMatchStringW *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1LogicMatchWPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1LogicMatchW_copy(Dz1LogicMatchW *ret, Dz1LogicMatchW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1LogicMatchWPresent_number:
			// _U_cst_clone
			if (src->x.number && (ret->x.number = Dz1LogicMatchNum_clone(src->x.number, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1LogicMatchWPresent_text:
			// _U_cst_clone
			if (src->x.text && (ret->x.text = Dz1LogicMatchStringW_clone(src->x.text, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1LogicMatchW *Dz1LogicMatchW_clone(Dz1LogicMatchW *src, Dz1Error *err)
{
	Dz1LogicMatchW *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1LogicMatchW *)Dz1Calloc(sizeof(Dz1LogicMatchW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LogicMatchW_delAndSetNull, (void *)&ret);
		if (Dz1LogicMatchW_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicMatchW_purge(Dz1LogicMatchW *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1LogicMatchWPresent_number:
		Dz1LogicMatchNum_del(p->x.number);
		break;
	case Dz1LogicMatchWPresent_text:
		Dz1LogicMatchStringW_del(p->x.text);
		break;
	default:
		break;
	}
}

void Dz1LogicMatchW_del(Dz1LogicMatchW *p)
{
	if (!p) return;
	Dz1LogicMatchW_purge(p);
	Dz1Free(p);
}

void Dz1LogicMatchW_dump(Dz1LogicMatchW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case Dz1LogicMatchWPresent_number:
		Dz1ThreadW_printf(L"number."); Dz1LogicMatchNum_dump(p->x.number, tab); 
		break;
	case Dz1LogicMatchWPresent_text:
		Dz1ThreadW_printf(L"text."); Dz1LogicMatchStringW_dump(p->x.text, tab); 
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}

// Dz1LogicMatchW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchListA
static Dz1Error Dz1LogicMatchListA_add(Dz1LogicMatchListA *p, Dz1LogicMatchA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1LogicMatchListAMkArrArg
{
	Dz1LogicMatchA **arr;
	unsigned int idx;
} Dz1LogicMatchListAMkArrArg;

static Dz1Error _Dz1LogicMatchListA_get_array(void *ptr, Dz1LogicMatchA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LogicMatchListAMkArrArg *arg = (Dz1LogicMatchListAMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1LogicMatchA **Dz1LogicMatchListA_get_array(Dz1LogicMatchListA *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1LogicMatchA **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LogicMatchA **)Dz1Calloc(sizeof(Dz1LogicMatchA *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1LogicMatchListAMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1LogicMatchListA_get_array, (void *)&arg);
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

static Dz1Error Dz1LogicMatchListA_travelForward(Dz1LogicMatchListA *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchA *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1LogicMatchListA_travelBackward(Dz1LogicMatchListA *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchA *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1LogicMatchListA_count(Dz1LogicMatchListA *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1LogicMatchListA *Dz1LogicMatchListA_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchListA *ret = (Dz1LogicMatchListA *)Dz1Calloc(sizeof(Dz1LogicMatchListA), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicMatchListA_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1LogicMatchA_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1LogicMatchListA_count;
			ret->travel = Dz1LogicMatchListA_travelForward;
			ret->travelForward = Dz1LogicMatchListA_travelForward;
			ret->travelBackward = Dz1LogicMatchListA_travelBackward;
			ret->get_array = Dz1LogicMatchListA_get_array;
			ret->add = Dz1LogicMatchListA_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1LogicMatchListA_clone(void *ptr, Dz1LogicMatchA *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LogicMatchListA *p = (Dz1LogicMatchListA *)ptr;
	Dz1LogicMatchA *cloned = Dz1LogicMatchA_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1LogicMatchListA *Dz1LogicMatchListA_clone(Dz1LogicMatchListA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchListA *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1LogicMatchListA_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicMatchListA_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1LogicMatchListA_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchListA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicMatchListA_purge(Dz1LogicMatchListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1LogicMatchListA_del(Dz1LogicMatchListA *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1LogicMatchListA_dump(void *ptr, Dz1LogicMatchA *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1LogicMatchA_dump(p, tab);
	return err;
}

void Dz1LogicMatchListA_dump(Dz1LogicMatchListA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1LogicMatchListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
// Dz1LogicMatchListA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchListW
static Dz1Error Dz1LogicMatchListW_add(Dz1LogicMatchListW *p, Dz1LogicMatchW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1LogicMatchListWMkArrArg
{
	Dz1LogicMatchW **arr;
	unsigned int idx;
} Dz1LogicMatchListWMkArrArg;

static Dz1Error _Dz1LogicMatchListW_get_array(void *ptr, Dz1LogicMatchW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LogicMatchListWMkArrArg *arg = (Dz1LogicMatchListWMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1LogicMatchW **Dz1LogicMatchListW_get_array(Dz1LogicMatchListW *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1LogicMatchW **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LogicMatchW **)Dz1Calloc(sizeof(Dz1LogicMatchW *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1LogicMatchListWMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1LogicMatchListW_get_array, (void *)&arg);
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

static Dz1Error Dz1LogicMatchListW_travelForward(Dz1LogicMatchListW *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchW *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1LogicMatchListW_travelBackward(Dz1LogicMatchListW *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchW *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1LogicMatchListW_count(Dz1LogicMatchListW *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1LogicMatchListW *Dz1LogicMatchListW_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchListW *ret = (Dz1LogicMatchListW *)Dz1Calloc(sizeof(Dz1LogicMatchListW), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicMatchListW_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1LogicMatchW_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1LogicMatchListW_count;
			ret->travel = Dz1LogicMatchListW_travelForward;
			ret->travelForward = Dz1LogicMatchListW_travelForward;
			ret->travelBackward = Dz1LogicMatchListW_travelBackward;
			ret->get_array = Dz1LogicMatchListW_get_array;
			ret->add = Dz1LogicMatchListW_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1LogicMatchListW_clone(void *ptr, Dz1LogicMatchW *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LogicMatchListW *p = (Dz1LogicMatchListW *)ptr;
	Dz1LogicMatchW *cloned = Dz1LogicMatchW_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1LogicMatchListW *Dz1LogicMatchListW_clone(Dz1LogicMatchListW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchListW *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1LogicMatchListW_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LogicMatchListW_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1LogicMatchListW_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LogicMatchListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LogicMatchListW_purge(Dz1LogicMatchListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1LogicMatchListW_del(Dz1LogicMatchListW *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1LogicMatchListW_dump(void *ptr, Dz1LogicMatchW *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1LogicMatchW_dump(p, tab);
	return err;
}

void Dz1LogicMatchListW_dump(Dz1LogicMatchListW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1LogicMatchListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
// Dz1LogicMatchListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchValueType
static struct Dz1LogicMatchValueTypeMapA
{
	str_t str;
	Dz1LogicMatchValueType v;
} Dz1LogicMatchValueTypeMapA[] =
{
	{ (char *)"Signed8", Dz1LogicMatchValueType_Signed8 },
	{ (char *)"Signed16", Dz1LogicMatchValueType_Signed16 },
	{ (char *)"Signed32", Dz1LogicMatchValueType_Signed32 },
	{ (char *)"Signed64", Dz1LogicMatchValueType_Signed64 },
	{ (char *)"Unsigned8", Dz1LogicMatchValueType_Unsigned8 },
	{ (char *)"Unsigned16", Dz1LogicMatchValueType_Unsigned16 },
	{ (char *)"Unsigned32", Dz1LogicMatchValueType_Unsigned32 },
	{ (char *)"Unsigned64", Dz1LogicMatchValueType_Unsigned64 },
	{ (char *)"String", Dz1LogicMatchValueType_String },
	{ NULL, Dz1LogicMatchValueType_max }
};

str_t Dz1LogicMatchValueTypeStrA(Dz1LogicMatchValueType v)
{
	struct Dz1LogicMatchValueTypeMapA *i = NULL;
	for (i = Dz1LogicMatchValueTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchValueType Dz1LogicMatchValueTypeFromStrA(str_t str)
{
	struct Dz1LogicMatchValueTypeMapA *i = NULL;
	for (i = Dz1LogicMatchValueTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchValueType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1LogicMatchValueTypeMapW
{
	wstr_t str;
	Dz1LogicMatchValueType v;
} Dz1LogicMatchValueTypeMapW[] =
{
	{ (wchar_t *)L"Signed8", Dz1LogicMatchValueType_Signed8 },
	{ (wchar_t *)L"Signed16", Dz1LogicMatchValueType_Signed16 },
	{ (wchar_t *)L"Signed32", Dz1LogicMatchValueType_Signed32 },
	{ (wchar_t *)L"Signed64", Dz1LogicMatchValueType_Signed64 },
	{ (wchar_t *)L"Unsigned8", Dz1LogicMatchValueType_Unsigned8 },
	{ (wchar_t *)L"Unsigned16", Dz1LogicMatchValueType_Unsigned16 },
	{ (wchar_t *)L"Unsigned32", Dz1LogicMatchValueType_Unsigned32 },
	{ (wchar_t *)L"Unsigned64", Dz1LogicMatchValueType_Unsigned64 },
	{ (wchar_t *)L"String", Dz1LogicMatchValueType_String },
	{ NULL, Dz1LogicMatchValueType_max }
};

wstr_t Dz1LogicMatchValueTypeStrW(Dz1LogicMatchValueType v)
{
	struct Dz1LogicMatchValueTypeMapW *i = NULL;
	for (i = Dz1LogicMatchValueTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LogicMatchValueType Dz1LogicMatchValueTypeFromStrW(wstr_t str)
{
	struct Dz1LogicMatchValueTypeMapW *i = NULL;
	for (i = Dz1LogicMatchValueTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1LogicMatchValueType_max;
}
#endif // UNIX_SYSTEM

Dz1LogicMatchValueType *Dz1LogicMatchValueType_new(Dz1LogicMatchValueType *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1LogicMatchValueType *__internal_ret = (Dz1LogicMatchValueType *)Dz1Calloc(sizeof(Dz1LogicMatchValueType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1LogicMatchValueTypeA_dump(Dz1LogicMatchValueType *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1LogicMatchValueTypeStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1LogicMatchValueTypeW_dump(Dz1LogicMatchValueType *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1LogicMatchValueTypeStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1LogicMatchValueType
////////////////////////////////////////////////////////////////////////////////

