////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827TestHelperDef.h"

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Cost
Gitsn_Iso14827Cost *Gitsn_Iso14827Cost_new(Dz1Str currency, 
										   s32_t factor, 
										   s32_t qty, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Cost *__internal_ret = (Gitsn_Iso14827Cost *)Dz1Calloc(sizeof(Gitsn_Iso14827Cost), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Cost_delAndSetNull, (void *)&__internal_ret);
		
		if (currency && (__internal_ret->currency = Dz1Str_clone(currency, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->factor = factor;
			__internal_ret->qty = qty;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Cost_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827Cost_copy(Gitsn_Iso14827Cost *dst, Gitsn_Iso14827Cost *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->currency && (dst->currency = Dz1Str_clone(src->currency, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->factor = src->factor;
		dst->qty = src->qty;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Cost *Gitsn_Iso14827Cost_clone(Gitsn_Iso14827Cost *src, Dz1Error *err)
{
	Gitsn_Iso14827Cost *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827Cost *)Dz1Calloc(sizeof(Gitsn_Iso14827Cost), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Cost_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827Cost_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Cost_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827Cost_purge(Gitsn_Iso14827Cost *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->currency);
}

void Gitsn_Iso14827Cost_del(Gitsn_Iso14827Cost *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Cost_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827Cost_dump(Gitsn_Iso14827Cost *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("currency = ")); Dz1Str_dump(p->currency, tab); 
		Dz1Thread_tprintf(tab, Dz1T("factor = ")); Dz1s32_dump(&p->factor, tab); 
		Dz1Thread_tprintf(tab, Dz1T("qty = ")); Dz1s32_dump(&p->qty, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827Cost
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TimeFracPresent
static struct Gitsn_Iso14827TimeFracPresentMapA
{
	str_t str;
	Gitsn_Iso14827TimeFracPresent v;
} Gitsn_Iso14827TimeFracPresentMapA[] =
{
	{ (char *)"deci", Gitsn_Iso14827TimeFracPresent_deci },
	{ (char *)"centi", Gitsn_Iso14827TimeFracPresent_centi },
	{ (char *)"milli", Gitsn_Iso14827TimeFracPresent_milli },
	{ NULL, Gitsn_Iso14827TimeFracPresent_max }
};

str_t Gitsn_Iso14827TimeFracPresentStrA(Gitsn_Iso14827TimeFracPresent v)
{
	struct Gitsn_Iso14827TimeFracPresentMapA *i = NULL;
	for (i = Gitsn_Iso14827TimeFracPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827TimeFracPresent Gitsn_Iso14827TimeFracPresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827TimeFracPresentMapA *i = NULL;
	for (i = Gitsn_Iso14827TimeFracPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827TimeFracPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827TimeFracPresentMapW
{
	wstr_t str;
	Gitsn_Iso14827TimeFracPresent v;
} Gitsn_Iso14827TimeFracPresentMapW[] =
{
	{ (wchar_t *)L"deci", Gitsn_Iso14827TimeFracPresent_deci },
	{ (wchar_t *)L"centi", Gitsn_Iso14827TimeFracPresent_centi },
	{ (wchar_t *)L"milli", Gitsn_Iso14827TimeFracPresent_milli },
	{ NULL, Gitsn_Iso14827TimeFracPresent_max }
};

wstr_t Gitsn_Iso14827TimeFracPresentStrW(Gitsn_Iso14827TimeFracPresent v)
{
	struct Gitsn_Iso14827TimeFracPresentMapW *i = NULL;
	for (i = Gitsn_Iso14827TimeFracPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827TimeFracPresent Gitsn_Iso14827TimeFracPresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827TimeFracPresentMapW *i = NULL;
	for (i = Gitsn_Iso14827TimeFracPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827TimeFracPresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827TimeFracPresent *Gitsn_Iso14827TimeFracPresent_new(Gitsn_Iso14827TimeFracPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827TimeFracPresent *__internal_ret = (Gitsn_Iso14827TimeFracPresent *)Dz1Calloc(sizeof(Gitsn_Iso14827TimeFracPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827TimeFracPresent_dump(Gitsn_Iso14827TimeFracPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827TimeFracPresentStr(*v));
}
// Gitsn_Iso14827TimeFracPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TimeFrac
Gitsn_Iso14827TimeFrac *Gitsn_Iso14827TimeFrac_new(Gitsn_Iso14827TimeFracPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827TimeFrac *ret = (Gitsn_Iso14827TimeFrac *)Dz1Calloc(sizeof(Gitsn_Iso14827TimeFrac), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TimeFrac_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827TimeFracPresent_deci:
			// _U_prim_clone
			if (ptr != NULL) ret->x.deci = *(s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827TimeFracPresent_centi:
			// _U_prim_clone
			if (ptr != NULL) ret->x.centi = *(s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827TimeFracPresent_milli:
			// _U_prim_clone
			if (ptr != NULL) ret->x.milli = *(s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827TimeFracPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827TimeFrac_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827TimeFrac_copy(Gitsn_Iso14827TimeFrac *ret, Gitsn_Iso14827TimeFrac *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827TimeFracPresent_deci:
			// _U_prim_clone
			ret->x.deci = src->x.deci;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827TimeFracPresent_centi:
			// _U_prim_clone
			ret->x.centi = src->x.centi;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827TimeFracPresent_milli:
			// _U_prim_clone
			ret->x.milli = src->x.milli;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827TimeFrac *Gitsn_Iso14827TimeFrac_clone(Gitsn_Iso14827TimeFrac *src, Dz1Error *err)
{
	Gitsn_Iso14827TimeFrac *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827TimeFrac *)Dz1Calloc(sizeof(Gitsn_Iso14827TimeFrac), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TimeFrac_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827TimeFrac_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827TimeFrac_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827TimeFrac_purge(Gitsn_Iso14827TimeFrac *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827TimeFracPresent_deci:
		break;
	case Gitsn_Iso14827TimeFracPresent_centi:
		break;
	case Gitsn_Iso14827TimeFracPresent_milli:
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827TimeFrac_del(Gitsn_Iso14827TimeFrac *p)
{
	if (!p) return;
	Gitsn_Iso14827TimeFrac_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827TimeFrac_dump(Gitsn_Iso14827TimeFrac *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827TimeFracPresent_deci:
		Dz1Thread_printf(Dz1T("deci = ")); Dz1s32_dump(&p->x.deci, tab); 
		break;
	case Gitsn_Iso14827TimeFracPresent_centi:
		Dz1Thread_printf(Dz1T("centi = ")); Dz1s32_dump(&p->x.centi, tab); 
		break;
	case Gitsn_Iso14827TimeFracPresent_milli:
		Dz1Thread_printf(Dz1T("milli = ")); Dz1s32_dump(&p->x.milli, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827TimeFrac
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TimeZone
Gitsn_Iso14827TimeZone *Gitsn_Iso14827TimeZone_new(s32_t modH, s32_t modM, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827TimeZone *__internal_ret = (Gitsn_Iso14827TimeZone *)Dz1Calloc(sizeof(Gitsn_Iso14827TimeZone), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TimeZone_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->modH = modH;
		__internal_ret->modM = modM;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827TimeZone_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827TimeZone_copy(Gitsn_Iso14827TimeZone *dst, Gitsn_Iso14827TimeZone *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->modH = src->modH;
		dst->modM = src->modM;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827TimeZone *Gitsn_Iso14827TimeZone_clone(Gitsn_Iso14827TimeZone *src, Dz1Error *err)
{
	Gitsn_Iso14827TimeZone *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827TimeZone *)Dz1Calloc(sizeof(Gitsn_Iso14827TimeZone), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TimeZone_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827TimeZone_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827TimeZone_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827TimeZone_purge(Gitsn_Iso14827TimeZone *p)
{
	if (p == NULL) return;
}

void Gitsn_Iso14827TimeZone_del(Gitsn_Iso14827TimeZone *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827TimeZone_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827TimeZone_dump(Gitsn_Iso14827TimeZone *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("modH = ")); Dz1s32_dump(&p->modH, tab); 
		Dz1Thread_tprintf(tab, Dz1T("modM = ")); Dz1s32_dump(&p->modM, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827TimeZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Time
Gitsn_Iso14827Time *Gitsn_Iso14827Time_new(s32_t *year, 
										   s32_t *month, 
										   s32_t *day, 
										   s32_t h, 
										   s32_t m, 
										   s32_t s, 
										   Gitsn_Iso14827TimeFrac *frac, 
										   Gitsn_Iso14827TimeZone *zone, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Time *__internal_ret = (Gitsn_Iso14827Time *)Dz1Calloc(sizeof(Gitsn_Iso14827Time), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Time_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->year = year;
		__internal_ret->month = month;
		__internal_ret->day = day;
		__internal_ret->h = h;
		__internal_ret->m = m;
		__internal_ret->s = s;
		__internal_ret->frac = frac;
		__internal_ret->zone = zone;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Time_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827Time_copy(Gitsn_Iso14827Time *dst, Gitsn_Iso14827Time *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->year && (dst->year = Dz1s32_clone(src->year, errp)) == NULL) ERR_OUT(errp);
	else if (src->month && (dst->month = Dz1s32_clone(src->month, errp)) == NULL) ERR_OUT(errp);
	else if (src->day && (dst->day = Dz1s32_clone(src->day, errp)) == NULL) ERR_OUT(errp);
	else if (src->frac && (dst->frac = Gitsn_Iso14827TimeFrac_clone(src->frac, errp)) == NULL) ERR_OUT(errp);
	else if (src->zone && (dst->zone = Gitsn_Iso14827TimeZone_clone(src->zone, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->h = src->h;
		dst->m = src->m;
		dst->s = src->s;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Time *Gitsn_Iso14827Time_clone(Gitsn_Iso14827Time *src, Dz1Error *err)
{
	Gitsn_Iso14827Time *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827Time *)Dz1Calloc(sizeof(Gitsn_Iso14827Time), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Time_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827Time_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Time_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827Time_purge(Gitsn_Iso14827Time *p)
{
	if (p == NULL) return;
	Dz1s32_del(p->year);
	Dz1s32_del(p->month);
	Dz1s32_del(p->day);
	Gitsn_Iso14827TimeFrac_del(p->frac);
	Gitsn_Iso14827TimeZone_del(p->zone);
}

void Gitsn_Iso14827Time_del(Gitsn_Iso14827Time *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Time_purge(p);
	Dz1Free(p);
}

// Gitsn_Iso14827Time
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827HdrOpt
Gitsn_Iso14827HdrOpt *Gitsn_Iso14827HdrOpt_new(Dz1Str origin, 
											   Dz1Str originAddr, 
											   Dz1Str sender, 
											   Dz1Str senderAddr, 
											   Dz1Str dest, 
											   Dz1Str destAddr, 
											   Gitsn_Iso14827Cost *cost, 
											   Gitsn_Iso14827Time *t, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827HdrOpt *__internal_ret = (Gitsn_Iso14827HdrOpt *)Dz1Calloc(sizeof(Gitsn_Iso14827HdrOpt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827HdrOpt_delAndSetNull, (void *)&__internal_ret);
		
		if (origin && (__internal_ret->origin = Dz1Str_clone(origin, errp)) == NULL) ERR_OUT(errp);
		else if (originAddr && (__internal_ret->originAddr = Dz1Str_clone(originAddr, errp)) == NULL) ERR_OUT(errp);
		else if (sender && (__internal_ret->sender = Dz1Str_clone(sender, errp)) == NULL) ERR_OUT(errp);
		else if (senderAddr && (__internal_ret->senderAddr = Dz1Str_clone(senderAddr, errp)) == NULL) ERR_OUT(errp);
		else if (dest && (__internal_ret->dest = Dz1Str_clone(dest, errp)) == NULL) ERR_OUT(errp);
		else if (destAddr && (__internal_ret->destAddr = Dz1Str_clone(destAddr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->cost = cost;
			__internal_ret->t = t;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827HdrOpt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827HdrOpt_copy(Gitsn_Iso14827HdrOpt *dst, Gitsn_Iso14827HdrOpt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->origin && (dst->origin = Dz1Str_clone(src->origin, errp)) == NULL) ERR_OUT(errp);
	else if (src->originAddr && (dst->originAddr = Dz1Str_clone(src->originAddr, errp)) == NULL) ERR_OUT(errp);
	else if (src->sender && (dst->sender = Dz1Str_clone(src->sender, errp)) == NULL) ERR_OUT(errp);
	else if (src->senderAddr && (dst->senderAddr = Dz1Str_clone(src->senderAddr, errp)) == NULL) ERR_OUT(errp);
	else if (src->dest && (dst->dest = Dz1Str_clone(src->dest, errp)) == NULL) ERR_OUT(errp);
	else if (src->destAddr && (dst->destAddr = Dz1Str_clone(src->destAddr, errp)) == NULL) ERR_OUT(errp);
	else if (src->cost && (dst->cost = Gitsn_Iso14827Cost_clone(src->cost, errp)) == NULL) ERR_OUT(errp);
	else if (src->t && (dst->t = Gitsn_Iso14827Time_clone(src->t, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827HdrOpt *Gitsn_Iso14827HdrOpt_clone(Gitsn_Iso14827HdrOpt *src, Dz1Error *err)
{
	Gitsn_Iso14827HdrOpt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827HdrOpt *)Dz1Calloc(sizeof(Gitsn_Iso14827HdrOpt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827HdrOpt_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827HdrOpt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827HdrOpt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827HdrOpt_purge(Gitsn_Iso14827HdrOpt *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->origin);
	Dz1Str_del(p->originAddr);
	Dz1Str_del(p->sender);
	Dz1Str_del(p->senderAddr);
	Dz1Str_del(p->dest);
	Dz1Str_del(p->destAddr);
	Gitsn_Iso14827Cost_del(p->cost);
	Gitsn_Iso14827Time_del(p->t);
}

void Gitsn_Iso14827HdrOpt_del(Gitsn_Iso14827HdrOpt *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827HdrOpt_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827HdrOpt_dump(Gitsn_Iso14827HdrOpt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("origin = ")); Dz1Str_dump(p->origin, tab); 
		Dz1Thread_tprintf(tab, Dz1T("originAddr = ")); Dz1Str_dump(p->originAddr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sender = ")); Dz1Str_dump(p->sender, tab); 
		Dz1Thread_tprintf(tab, Dz1T("senderAddr = ")); Dz1Str_dump(p->senderAddr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dest = ")); Dz1Str_dump(p->dest, tab); 
		Dz1Thread_tprintf(tab, Dz1T("destAddr = ")); Dz1Str_dump(p->destAddr, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("cost = ")); Gitsn_Iso14827Cost_dump(p->cost, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("t = ")); Gitsn_Iso14827Time_dump(p->t, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827HdrOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Initiate
Gitsn_Iso14827Initiate *Gitsn_Iso14827Initiate_new(Dz1Str sender, Dz1Str dest, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Initiate *__internal_ret = (Gitsn_Iso14827Initiate *)Dz1Calloc(sizeof(Gitsn_Iso14827Initiate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Initiate_delAndSetNull, (void *)&__internal_ret);
		
		if (sender && (__internal_ret->sender = Dz1Str_clone(sender, errp)) == NULL) ERR_OUT(errp);
		else if (dest && (__internal_ret->dest = Dz1Str_clone(dest, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Initiate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827Initiate_copy(Gitsn_Iso14827Initiate *dst, Gitsn_Iso14827Initiate *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->sender && (dst->sender = Dz1Str_clone(src->sender, errp)) == NULL) ERR_OUT(errp);
	else if (src->dest && (dst->dest = Dz1Str_clone(src->dest, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Initiate *Gitsn_Iso14827Initiate_clone(Gitsn_Iso14827Initiate *src, Dz1Error *err)
{
	Gitsn_Iso14827Initiate *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827Initiate *)Dz1Calloc(sizeof(Gitsn_Iso14827Initiate), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Initiate_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827Initiate_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Initiate_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827Initiate_purge(Gitsn_Iso14827Initiate *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->sender);
	Dz1Str_del(p->dest);
}

void Gitsn_Iso14827Initiate_del(Gitsn_Iso14827Initiate *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Initiate_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827Initiate_dump(Gitsn_Iso14827Initiate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("sender = ")); Dz1Str_dump(p->sender, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dest = ")); Dz1Str_dump(p->dest, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827Initiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Dz1OIDList
static Dz1Error Gitsn_Dz1OIDList_add(Gitsn_Dz1OIDList *p, Dz1Str data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Gitsn_Dz1OIDListMkArrArg
{
	Dz1Str *arr;
	unsigned int idx;
} Gitsn_Dz1OIDListMkArrArg;

static Dz1Error _Gitsn_Dz1OIDList_get_array(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Gitsn_Dz1OIDListMkArrArg *arg = (Gitsn_Dz1OIDListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1Str *Gitsn_Dz1OIDList_get_array(Gitsn_Dz1OIDList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1Str *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Str *)Dz1Calloc(sizeof(Dz1Str *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_Dz1OIDListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Gitsn_Dz1OIDList_get_array, (void *)&arg);
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

static Dz1Error Gitsn_Dz1OIDList_travelForward(Gitsn_Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Str data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Gitsn_Dz1OIDList_travelBackward(Gitsn_Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Str data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct Gitsn_Dz1OIDListFindArg
{
	Dz1Str key;
	Dz1Str ret;
	int (*cmp)(Dz1Str a, Dz1Str b);
} Gitsn_Dz1OIDListFindArg;

static Dz1Error _Gitsn_Dz1OIDList_find(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Gitsn_Dz1OIDListFindArg *arg = (Gitsn_Dz1OIDListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static Dz1Str Gitsn_Dz1OIDList_find(Gitsn_Dz1OIDList *p, Dz1Str key)
{
	Gitsn_Dz1OIDListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _Gitsn_Dz1OIDList_find, (void *)&arg);
	return arg.ret;
}

static unsigned int Gitsn_Dz1OIDList_count(Gitsn_Dz1OIDList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Gitsn_Dz1OIDList *Gitsn_Dz1OIDList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Dz1OIDList *ret = (Gitsn_Dz1OIDList *)Dz1Calloc(sizeof(Gitsn_Dz1OIDList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Dz1OIDList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1Str_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Gitsn_Dz1OIDList_count;
			ret->travel = Gitsn_Dz1OIDList_travelForward;
			ret->travelForward = Gitsn_Dz1OIDList_travelForward;
			ret->travelBackward = Gitsn_Dz1OIDList_travelBackward;
			ret->get_array = Gitsn_Dz1OIDList_get_array;
			ret->add = Gitsn_Dz1OIDList_add;
			ret->find = Gitsn_Dz1OIDList_find;
			ret->cmp = Dz1Str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Dz1OIDList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Gitsn_Dz1OIDList_clone(void *ptr, Dz1Str data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Gitsn_Dz1OIDList *p = (Gitsn_Dz1OIDList *)ptr;
	Dz1Str cloned = Dz1Str_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Gitsn_Dz1OIDList *Gitsn_Dz1OIDList_clone(Gitsn_Dz1OIDList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Dz1OIDList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Gitsn_Dz1OIDList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Dz1OIDList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Gitsn_Dz1OIDList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Dz1OIDList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Dz1OIDList_purge(Gitsn_Dz1OIDList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Gitsn_Dz1OIDList_del(Gitsn_Dz1OIDList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Gitsn_Dz1OIDListA_dump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1StrA_dump(p, tab);
	return err;
}

void Gitsn_Dz1OIDListA_dump(Gitsn_Dz1OIDList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Gitsn_Dz1OIDListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _Gitsn_Dz1OIDListA_fdump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); Dz1StrA_fdump(arg->fp, p, tab);
	return err;
}

void Gitsn_Dz1OIDListA_fdump(FILE *fp, Gitsn_Dz1OIDList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _Gitsn_Dz1OIDListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Gitsn_Dz1OIDListW_dump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1StrW_dump(p, tab);
	return err;
}

void Gitsn_Dz1OIDListW_dump(Gitsn_Dz1OIDList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Gitsn_Dz1OIDListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _Gitsn_Dz1OIDListW_fdump(void *ptr, Dz1Str p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); Dz1StrW_fdump(arg->fp, p, tab);
	return err;
}

void Gitsn_Dz1OIDListW_fdump(FILE *fp, Gitsn_Dz1OIDList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _Gitsn_Dz1OIDListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Gitsn_Dz1OIDList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827LoginInitiator
static struct Gitsn_Iso14827LoginInitiatorMapA
{
	str_t str;
	Gitsn_Iso14827LoginInitiator v;
} Gitsn_Iso14827LoginInitiatorMapA[] =
{
	{ (char *)"serverInitiated", Gitsn_Iso14827LoginInitiator_serverInitiated },
	{ (char *)"clientInitiated", Gitsn_Iso14827LoginInitiator_clientInitiated },
	{ NULL, Gitsn_Iso14827LoginInitiator_max }
};

str_t Gitsn_Iso14827LoginInitiatorStrA(Gitsn_Iso14827LoginInitiator v)
{
	struct Gitsn_Iso14827LoginInitiatorMapA *i = NULL;
	for (i = Gitsn_Iso14827LoginInitiatorMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827LoginInitiator Gitsn_Iso14827LoginInitiatorFromStrA(str_t str)
{
	struct Gitsn_Iso14827LoginInitiatorMapA *i = NULL;
	for (i = Gitsn_Iso14827LoginInitiatorMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827LoginInitiator_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827LoginInitiatorMapW
{
	wstr_t str;
	Gitsn_Iso14827LoginInitiator v;
} Gitsn_Iso14827LoginInitiatorMapW[] =
{
	{ (wchar_t *)L"serverInitiated", Gitsn_Iso14827LoginInitiator_serverInitiated },
	{ (wchar_t *)L"clientInitiated", Gitsn_Iso14827LoginInitiator_clientInitiated },
	{ NULL, Gitsn_Iso14827LoginInitiator_max }
};

wstr_t Gitsn_Iso14827LoginInitiatorStrW(Gitsn_Iso14827LoginInitiator v)
{
	struct Gitsn_Iso14827LoginInitiatorMapW *i = NULL;
	for (i = Gitsn_Iso14827LoginInitiatorMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827LoginInitiator Gitsn_Iso14827LoginInitiatorFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827LoginInitiatorMapW *i = NULL;
	for (i = Gitsn_Iso14827LoginInitiatorMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827LoginInitiator_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827LoginInitiator *Gitsn_Iso14827LoginInitiator_new(Gitsn_Iso14827LoginInitiator *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827LoginInitiator *__internal_ret = (Gitsn_Iso14827LoginInitiator *)Dz1Calloc(sizeof(Gitsn_Iso14827LoginInitiator), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827LoginInitiator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Login
Gitsn_Iso14827Login *Gitsn_Iso14827Login_new(Dz1Str sender, 
											 Dz1Str dest, 
											 Dz1Str user, 
											 Dz1Str pass, 
											 s32_t hbDur, 
											 s32_t timeout, 
											 Gitsn_Iso14827LoginInitiator initiator, 
											 u16_t datagramSize, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Login *__internal_ret = (Gitsn_Iso14827Login *)Dz1Calloc(sizeof(Gitsn_Iso14827Login), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Login_delAndSetNull, (void *)&__internal_ret);
		
		if (sender && (__internal_ret->sender = Dz1Str_clone(sender, errp)) == NULL) ERR_OUT(errp);
		else if (dest && (__internal_ret->dest = Dz1Str_clone(dest, errp)) == NULL) ERR_OUT(errp);
		else if (user && (__internal_ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = Dz1Str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->encRules = Gitsn_Dz1OIDList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->hbDur = hbDur;
			__internal_ret->timeout = timeout;
			__internal_ret->initiator = initiator;
			__internal_ret->datagramSize = datagramSize;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Login_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827Login_copy(Gitsn_Iso14827Login *dst, Gitsn_Iso14827Login *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->sender && (dst->sender = Dz1Str_clone(src->sender, errp)) == NULL) ERR_OUT(errp);
	else if (src->dest && (dst->dest = Dz1Str_clone(src->dest, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Str_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Str_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else if (src->encRules && (dst->encRules = Gitsn_Dz1OIDList_clone(src->encRules, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->hbDur = src->hbDur;
		dst->timeout = src->timeout;
		dst->initiator = src->initiator;
		dst->datagramSize = src->datagramSize;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Login *Gitsn_Iso14827Login_clone(Gitsn_Iso14827Login *src, Dz1Error *err)
{
	Gitsn_Iso14827Login *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827Login *)Dz1Calloc(sizeof(Gitsn_Iso14827Login), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Login_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827Login_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Login_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827Login_purge(Gitsn_Iso14827Login *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->sender);
	Dz1Str_del(p->dest);
	Dz1Str_del(p->user);
	Dz1Str_del(p->pass);
	Gitsn_Dz1OIDList_del(p->encRules);
}

void Gitsn_Iso14827Login_del(Gitsn_Iso14827Login *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Login_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827Login_dump(Gitsn_Iso14827Login *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("sender = ")); Dz1Str_dump(p->sender, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dest = ")); Dz1Str_dump(p->dest, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encRules = ")); Gitsn_Dz1OIDList_dump(p->encRules, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hbDur = ")); Dz1s32_dump(&p->hbDur, tab); 
		Dz1Thread_tprintf(tab, Dz1T("timeout = ")); Dz1s32_dump(&p->timeout, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initiator = %s(%d)\n"), Gitsn_Iso14827LoginInitiatorStr(p->initiator), p->initiator);
		Dz1Thread_tprintf(tab, Dz1T("datagramSize = ")); Dz1u16_dump(&p->datagramSize, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827Login
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Terminate
static struct Gitsn_Iso14827TerminateMapA
{
	str_t str;
	Gitsn_Iso14827Terminate v;
} Gitsn_Iso14827TerminateMapA[] =
{
	{ (char *)"other", Gitsn_Iso14827Terminate_other },
	{ (char *)"serverRequested", Gitsn_Iso14827Terminate_serverRequested },
	{ (char *)"clientRequested", Gitsn_Iso14827Terminate_clientRequested },
	{ (char *)"serverShutdown", Gitsn_Iso14827Terminate_serverShutdown },
	{ (char *)"clientShutdown", Gitsn_Iso14827Terminate_clientShutdown },
	{ (char *)"serverCommProblems", Gitsn_Iso14827Terminate_serverCommProblems },
	{ (char *)"clientCommProblems", Gitsn_Iso14827Terminate_clientCommProblems },
	{ NULL, Gitsn_Iso14827Terminate_max }
};

str_t Gitsn_Iso14827TerminateStrA(Gitsn_Iso14827Terminate v)
{
	struct Gitsn_Iso14827TerminateMapA *i = NULL;
	for (i = Gitsn_Iso14827TerminateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827Terminate Gitsn_Iso14827TerminateFromStrA(str_t str)
{
	struct Gitsn_Iso14827TerminateMapA *i = NULL;
	for (i = Gitsn_Iso14827TerminateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827Terminate_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827TerminateMapW
{
	wstr_t str;
	Gitsn_Iso14827Terminate v;
} Gitsn_Iso14827TerminateMapW[] =
{
	{ (wchar_t *)L"other", Gitsn_Iso14827Terminate_other },
	{ (wchar_t *)L"serverRequested", Gitsn_Iso14827Terminate_serverRequested },
	{ (wchar_t *)L"clientRequested", Gitsn_Iso14827Terminate_clientRequested },
	{ (wchar_t *)L"serverShutdown", Gitsn_Iso14827Terminate_serverShutdown },
	{ (wchar_t *)L"clientShutdown", Gitsn_Iso14827Terminate_clientShutdown },
	{ (wchar_t *)L"serverCommProblems", Gitsn_Iso14827Terminate_serverCommProblems },
	{ (wchar_t *)L"clientCommProblems", Gitsn_Iso14827Terminate_clientCommProblems },
	{ NULL, Gitsn_Iso14827Terminate_max }
};

wstr_t Gitsn_Iso14827TerminateStrW(Gitsn_Iso14827Terminate v)
{
	struct Gitsn_Iso14827TerminateMapW *i = NULL;
	for (i = Gitsn_Iso14827TerminateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827Terminate Gitsn_Iso14827TerminateFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827TerminateMapW *i = NULL;
	for (i = Gitsn_Iso14827TerminateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827Terminate_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827Terminate *Gitsn_Iso14827Terminate_new(Gitsn_Iso14827Terminate *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Terminate *__internal_ret = (Gitsn_Iso14827Terminate *)Dz1Calloc(sizeof(Gitsn_Iso14827Terminate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827Terminate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Logout
static struct Gitsn_Iso14827LogoutMapA
{
	str_t str;
	Gitsn_Iso14827Logout v;
} Gitsn_Iso14827LogoutMapA[] =
{
	{ (char *)"other", Gitsn_Iso14827Logout_other },
	{ (char *)"serverRequested", Gitsn_Iso14827Logout_serverRequested },
	{ (char *)"clientRequested", Gitsn_Iso14827Logout_clientRequested },
	{ (char *)"serverShutdown", Gitsn_Iso14827Logout_serverShutdown },
	{ (char *)"clientShutdown", Gitsn_Iso14827Logout_clientShutdown },
	{ (char *)"serverCommProblems", Gitsn_Iso14827Logout_serverCommProblems },
	{ (char *)"clientCommProblems", Gitsn_Iso14827Logout_clientCommProblems },
	{ NULL, Gitsn_Iso14827Logout_max }
};

str_t Gitsn_Iso14827LogoutStrA(Gitsn_Iso14827Logout v)
{
	struct Gitsn_Iso14827LogoutMapA *i = NULL;
	for (i = Gitsn_Iso14827LogoutMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827Logout Gitsn_Iso14827LogoutFromStrA(str_t str)
{
	struct Gitsn_Iso14827LogoutMapA *i = NULL;
	for (i = Gitsn_Iso14827LogoutMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827Logout_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827LogoutMapW
{
	wstr_t str;
	Gitsn_Iso14827Logout v;
} Gitsn_Iso14827LogoutMapW[] =
{
	{ (wchar_t *)L"other", Gitsn_Iso14827Logout_other },
	{ (wchar_t *)L"serverRequested", Gitsn_Iso14827Logout_serverRequested },
	{ (wchar_t *)L"clientRequested", Gitsn_Iso14827Logout_clientRequested },
	{ (wchar_t *)L"serverShutdown", Gitsn_Iso14827Logout_serverShutdown },
	{ (wchar_t *)L"clientShutdown", Gitsn_Iso14827Logout_clientShutdown },
	{ (wchar_t *)L"serverCommProblems", Gitsn_Iso14827Logout_serverCommProblems },
	{ (wchar_t *)L"clientCommProblems", Gitsn_Iso14827Logout_clientCommProblems },
	{ NULL, Gitsn_Iso14827Logout_max }
};

wstr_t Gitsn_Iso14827LogoutStrW(Gitsn_Iso14827Logout v)
{
	struct Gitsn_Iso14827LogoutMapW *i = NULL;
	for (i = Gitsn_Iso14827LogoutMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827Logout Gitsn_Iso14827LogoutFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827LogoutMapW *i = NULL;
	for (i = Gitsn_Iso14827LogoutMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827Logout_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827Logout *Gitsn_Iso14827Logout_new(Gitsn_Iso14827Logout *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Logout *__internal_ret = (Gitsn_Iso14827Logout *)Dz1Calloc(sizeof(Gitsn_Iso14827Logout), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827Logout
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataStatus
static struct Gitsn_Iso14827SubscriptionDataStatusMapA
{
	str_t str;
	Gitsn_Iso14827SubscriptionDataStatus v;
} Gitsn_Iso14827SubscriptionDataStatusMapA[] =
{
	{ (char *)"NEW", Gitsn_Iso14827SubscriptionDataStatus_NEW },
	{ (char *)"UPDATED", Gitsn_Iso14827SubscriptionDataStatus_UPDATED },
	{ NULL, Gitsn_Iso14827SubscriptionDataStatus_max }
};

str_t Gitsn_Iso14827SubscriptionDataStatusStrA(Gitsn_Iso14827SubscriptionDataStatus v)
{
	struct Gitsn_Iso14827SubscriptionDataStatusMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataStatusMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionDataStatus Gitsn_Iso14827SubscriptionDataStatusFromStrA(str_t str)
{
	struct Gitsn_Iso14827SubscriptionDataStatusMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataStatusMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionDataStatus_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827SubscriptionDataStatusMapW
{
	wstr_t str;
	Gitsn_Iso14827SubscriptionDataStatus v;
} Gitsn_Iso14827SubscriptionDataStatusMapW[] =
{
	{ (wchar_t *)L"NEW", Gitsn_Iso14827SubscriptionDataStatus_NEW },
	{ (wchar_t *)L"UPDATED", Gitsn_Iso14827SubscriptionDataStatus_UPDATED },
	{ NULL, Gitsn_Iso14827SubscriptionDataStatus_max }
};

wstr_t Gitsn_Iso14827SubscriptionDataStatusStrW(Gitsn_Iso14827SubscriptionDataStatus v)
{
	struct Gitsn_Iso14827SubscriptionDataStatusMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataStatusMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionDataStatus Gitsn_Iso14827SubscriptionDataStatusFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827SubscriptionDataStatusMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataStatusMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionDataStatus_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827SubscriptionDataStatus *Gitsn_Iso14827SubscriptionDataStatus_new(Gitsn_Iso14827SubscriptionDataStatus *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827SubscriptionDataStatus *__internal_ret = (Gitsn_Iso14827SubscriptionDataStatus *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionDataStatus), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827SubscriptionDataStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RegisteredContinuous
Gitsn_Iso14827RegisteredContinuous *Gitsn_Iso14827RegisteredContinuous_new(u32_t updateDelay, 
																		   Gitsn_Iso14827Time *start, 
																		   Gitsn_Iso14827Time *end, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RegisteredContinuous *__internal_ret = (Gitsn_Iso14827RegisteredContinuous *)Dz1Calloc(sizeof(Gitsn_Iso14827RegisteredContinuous), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RegisteredContinuous_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->updateDelay = updateDelay;
		__internal_ret->start = start;
		__internal_ret->end = end;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827RegisteredContinuous_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827RegisteredContinuous_copy(Gitsn_Iso14827RegisteredContinuous *dst, Gitsn_Iso14827RegisteredContinuous *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->start && (dst->start = Gitsn_Iso14827Time_clone(src->start, errp)) == NULL) ERR_OUT(errp);
	else if (src->end && (dst->end = Gitsn_Iso14827Time_clone(src->end, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->updateDelay = src->updateDelay;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827RegisteredContinuous *Gitsn_Iso14827RegisteredContinuous_clone(Gitsn_Iso14827RegisteredContinuous *src, Dz1Error *err)
{
	Gitsn_Iso14827RegisteredContinuous *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827RegisteredContinuous *)Dz1Calloc(sizeof(Gitsn_Iso14827RegisteredContinuous), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RegisteredContinuous_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827RegisteredContinuous_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827RegisteredContinuous_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827RegisteredContinuous_purge(Gitsn_Iso14827RegisteredContinuous *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Time_del(p->start);
	Gitsn_Iso14827Time_del(p->end);
}

void Gitsn_Iso14827RegisteredContinuous_del(Gitsn_Iso14827RegisteredContinuous *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827RegisteredContinuous_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827RegisteredContinuous_dump(Gitsn_Iso14827RegisteredContinuous *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("updateDelay = ")); Dz1u32_dump(&p->updateDelay, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("start = ")); Gitsn_Iso14827Time_dump(p->start, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("end = ")); Gitsn_Iso14827Time_dump(p->end, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827RegisteredContinuous
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RegisteredDaily
Gitsn_Iso14827RegisteredDaily *Gitsn_Iso14827RegisteredDaily_new(u32_t updateDelay, 
																 u8_t daysOfWeek, 
																 Gitsn_Iso14827Time *startDate, 
																 Gitsn_Iso14827Time *endDate, 
																 Gitsn_Iso14827Time *startTime, 
																 u16_t *duration, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RegisteredDaily *__internal_ret = (Gitsn_Iso14827RegisteredDaily *)Dz1Calloc(sizeof(Gitsn_Iso14827RegisteredDaily), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RegisteredDaily_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->updateDelay = updateDelay;
		__internal_ret->daysOfWeek = daysOfWeek;
		__internal_ret->startDate = startDate;
		__internal_ret->endDate = endDate;
		__internal_ret->startTime = startTime;
		__internal_ret->duration = duration;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827RegisteredDaily_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827RegisteredDaily_copy(Gitsn_Iso14827RegisteredDaily *dst, Gitsn_Iso14827RegisteredDaily *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->startDate && (dst->startDate = Gitsn_Iso14827Time_clone(src->startDate, errp)) == NULL) ERR_OUT(errp);
	else if (src->endDate && (dst->endDate = Gitsn_Iso14827Time_clone(src->endDate, errp)) == NULL) ERR_OUT(errp);
	else if (src->startTime && (dst->startTime = Gitsn_Iso14827Time_clone(src->startTime, errp)) == NULL) ERR_OUT(errp);
	else if (src->duration && (dst->duration = Dz1u16_clone(src->duration, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->updateDelay = src->updateDelay;
		dst->daysOfWeek = src->daysOfWeek;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827RegisteredDaily *Gitsn_Iso14827RegisteredDaily_clone(Gitsn_Iso14827RegisteredDaily *src, Dz1Error *err)
{
	Gitsn_Iso14827RegisteredDaily *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827RegisteredDaily *)Dz1Calloc(sizeof(Gitsn_Iso14827RegisteredDaily), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RegisteredDaily_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827RegisteredDaily_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827RegisteredDaily_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827RegisteredDaily_purge(Gitsn_Iso14827RegisteredDaily *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Time_del(p->startDate);
	Gitsn_Iso14827Time_del(p->endDate);
	Gitsn_Iso14827Time_del(p->startTime);
	Dz1u16_del(p->duration);
}

void Gitsn_Iso14827RegisteredDaily_del(Gitsn_Iso14827RegisteredDaily *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827RegisteredDaily_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827RegisteredDaily_dump(Gitsn_Iso14827RegisteredDaily *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("updateDelay = ")); Dz1u32_dump(&p->updateDelay, tab); 
		Dz1Thread_tprintf(tab, Dz1T("daysOfWeek = ")); Dz1u8_dump(&p->daysOfWeek, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("startDate = ")); Gitsn_Iso14827Time_dump(p->startDate, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("endDate = ")); Gitsn_Iso14827Time_dump(p->endDate, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("startTime = ")); Gitsn_Iso14827Time_dump(p->startTime, tab); 
		Dz1Thread_tprintf(tab, Dz1T("duration = ")); Dz1u16_dump(p->duration, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827RegisteredDaily
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RegisteredPresent
static struct Gitsn_Iso14827RegisteredPresentMapA
{
	str_t str;
	Gitsn_Iso14827RegisteredPresent v;
} Gitsn_Iso14827RegisteredPresentMapA[] =
{
	{ (char *)"continuous", Gitsn_Iso14827RegisteredPresent_continuous },
	{ (char *)"daily", Gitsn_Iso14827RegisteredPresent_daily },
	{ NULL, Gitsn_Iso14827RegisteredPresent_max }
};

str_t Gitsn_Iso14827RegisteredPresentStrA(Gitsn_Iso14827RegisteredPresent v)
{
	struct Gitsn_Iso14827RegisteredPresentMapA *i = NULL;
	for (i = Gitsn_Iso14827RegisteredPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RegisteredPresent Gitsn_Iso14827RegisteredPresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827RegisteredPresentMapA *i = NULL;
	for (i = Gitsn_Iso14827RegisteredPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RegisteredPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827RegisteredPresentMapW
{
	wstr_t str;
	Gitsn_Iso14827RegisteredPresent v;
} Gitsn_Iso14827RegisteredPresentMapW[] =
{
	{ (wchar_t *)L"continuous", Gitsn_Iso14827RegisteredPresent_continuous },
	{ (wchar_t *)L"daily", Gitsn_Iso14827RegisteredPresent_daily },
	{ NULL, Gitsn_Iso14827RegisteredPresent_max }
};

wstr_t Gitsn_Iso14827RegisteredPresentStrW(Gitsn_Iso14827RegisteredPresent v)
{
	struct Gitsn_Iso14827RegisteredPresentMapW *i = NULL;
	for (i = Gitsn_Iso14827RegisteredPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RegisteredPresent Gitsn_Iso14827RegisteredPresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827RegisteredPresentMapW *i = NULL;
	for (i = Gitsn_Iso14827RegisteredPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RegisteredPresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827RegisteredPresent *Gitsn_Iso14827RegisteredPresent_new(Gitsn_Iso14827RegisteredPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RegisteredPresent *__internal_ret = (Gitsn_Iso14827RegisteredPresent *)Dz1Calloc(sizeof(Gitsn_Iso14827RegisteredPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827RegisteredPresent_dump(Gitsn_Iso14827RegisteredPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827RegisteredPresentStr(*v));
}
// Gitsn_Iso14827RegisteredPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Registered
Gitsn_Iso14827Registered *Gitsn_Iso14827Registered_new(Gitsn_Iso14827RegisteredPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Registered *ret = (Gitsn_Iso14827Registered *)Dz1Calloc(sizeof(Gitsn_Iso14827Registered), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Registered_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827RegisteredPresent_continuous:
			// _U_cst_clone
			if (ptr != NULL) ret->x.continuous = (Gitsn_Iso14827RegisteredContinuous *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RegisteredPresent_daily:
			// _U_cst_clone
			if (ptr != NULL) ret->x.daily = (Gitsn_Iso14827RegisteredDaily *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RegisteredPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Registered_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827Registered_copy(Gitsn_Iso14827Registered *ret, Gitsn_Iso14827Registered *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827RegisteredPresent_continuous:
			// _U_cst_clone
			if (src->x.continuous && (ret->x.continuous = Gitsn_Iso14827RegisteredContinuous_clone(src->x.continuous, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827RegisteredPresent_daily:
			// _U_cst_clone
			if (src->x.daily && (ret->x.daily = Gitsn_Iso14827RegisteredDaily_clone(src->x.daily, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Registered *Gitsn_Iso14827Registered_clone(Gitsn_Iso14827Registered *src, Dz1Error *err)
{
	Gitsn_Iso14827Registered *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827Registered *)Dz1Calloc(sizeof(Gitsn_Iso14827Registered), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Registered_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827Registered_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Registered_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827Registered_purge(Gitsn_Iso14827Registered *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827RegisteredPresent_continuous:
		Gitsn_Iso14827RegisteredContinuous_del(p->x.continuous);
		break;
	case Gitsn_Iso14827RegisteredPresent_daily:
		Gitsn_Iso14827RegisteredDaily_del(p->x.daily);
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827Registered_del(Gitsn_Iso14827Registered *p)
{
	if (!p) return;
	Gitsn_Iso14827Registered_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827Registered_dump(Gitsn_Iso14827Registered *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827RegisteredPresent_continuous:
		Dz1Thread_printf(Dz1T("continuous = ")); Gitsn_Iso14827RegisteredContinuous_dump(p->x.continuous, tab); 
		break;
	case Gitsn_Iso14827RegisteredPresent_daily:
		Dz1Thread_printf(Dz1T("daily = ")); Gitsn_Iso14827RegisteredDaily_dump(p->x.daily, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827Registered
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataModePresent
static struct Gitsn_Iso14827SubscriptionDataModePresentMapA
{
	str_t str;
	Gitsn_Iso14827SubscriptionDataModePresent v;
} Gitsn_Iso14827SubscriptionDataModePresentMapA[] =
{
	{ (char *)"single", Gitsn_Iso14827SubscriptionDataModePresent_single },
	{ (char *)"eventDriven", Gitsn_Iso14827SubscriptionDataModePresent_eventDriven },
	{ (char *)"periodic", Gitsn_Iso14827SubscriptionDataModePresent_periodic },
	{ NULL, Gitsn_Iso14827SubscriptionDataModePresent_max }
};

str_t Gitsn_Iso14827SubscriptionDataModePresentStrA(Gitsn_Iso14827SubscriptionDataModePresent v)
{
	struct Gitsn_Iso14827SubscriptionDataModePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataModePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionDataModePresent Gitsn_Iso14827SubscriptionDataModePresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827SubscriptionDataModePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataModePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionDataModePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827SubscriptionDataModePresentMapW
{
	wstr_t str;
	Gitsn_Iso14827SubscriptionDataModePresent v;
} Gitsn_Iso14827SubscriptionDataModePresentMapW[] =
{
	{ (wchar_t *)L"single", Gitsn_Iso14827SubscriptionDataModePresent_single },
	{ (wchar_t *)L"eventDriven", Gitsn_Iso14827SubscriptionDataModePresent_eventDriven },
	{ (wchar_t *)L"periodic", Gitsn_Iso14827SubscriptionDataModePresent_periodic },
	{ NULL, Gitsn_Iso14827SubscriptionDataModePresent_max }
};

wstr_t Gitsn_Iso14827SubscriptionDataModePresentStrW(Gitsn_Iso14827SubscriptionDataModePresent v)
{
	struct Gitsn_Iso14827SubscriptionDataModePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataModePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionDataModePresent Gitsn_Iso14827SubscriptionDataModePresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827SubscriptionDataModePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataModePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionDataModePresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827SubscriptionDataModePresent *Gitsn_Iso14827SubscriptionDataModePresent_new(Gitsn_Iso14827SubscriptionDataModePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827SubscriptionDataModePresent *__internal_ret = (Gitsn_Iso14827SubscriptionDataModePresent *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionDataModePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827SubscriptionDataModePresent_dump(Gitsn_Iso14827SubscriptionDataModePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827SubscriptionDataModePresentStr(*v));
}
// Gitsn_Iso14827SubscriptionDataModePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataMode
Gitsn_Iso14827SubscriptionDataMode *Gitsn_Iso14827SubscriptionDataMode_new(Gitsn_Iso14827SubscriptionDataModePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827SubscriptionDataMode *ret = (Gitsn_Iso14827SubscriptionDataMode *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionDataMode), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionDataMode_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827SubscriptionDataModePresent_single:
			// _U_prim_clone
			if (ptr != NULL) ret->x.single = (s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827SubscriptionDataModePresent_eventDriven:
			// _U_cst_clone
			if (ptr != NULL) ret->x.eventDriven = (Gitsn_Iso14827Registered *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827SubscriptionDataModePresent_periodic:
			// _U_cst_clone
			if (ptr != NULL) ret->x.periodic = (Gitsn_Iso14827Registered *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827SubscriptionDataModePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827SubscriptionDataMode_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827SubscriptionDataMode_copy(Gitsn_Iso14827SubscriptionDataMode *ret, Gitsn_Iso14827SubscriptionDataMode *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827SubscriptionDataModePresent_single:
			// _U_prim_clone
			if (src->x.single && (ret->x.single = Dz1s32_clone(src->x.single, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827SubscriptionDataModePresent_eventDriven:
			// _U_cst_clone
			if (src->x.eventDriven && (ret->x.eventDriven = Gitsn_Iso14827Registered_clone(src->x.eventDriven, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827SubscriptionDataModePresent_periodic:
			// _U_cst_clone
			if (src->x.periodic && (ret->x.periodic = Gitsn_Iso14827Registered_clone(src->x.periodic, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827SubscriptionDataMode *Gitsn_Iso14827SubscriptionDataMode_clone(Gitsn_Iso14827SubscriptionDataMode *src, Dz1Error *err)
{
	Gitsn_Iso14827SubscriptionDataMode *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827SubscriptionDataMode *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionDataMode), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionDataMode_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827SubscriptionDataMode_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827SubscriptionDataMode_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827SubscriptionDataMode_purge(Gitsn_Iso14827SubscriptionDataMode *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827SubscriptionDataModePresent_single:
		Dz1s32_del(p->x.single);
		break;
	case Gitsn_Iso14827SubscriptionDataModePresent_eventDriven:
		Gitsn_Iso14827Registered_del(p->x.eventDriven);
		break;
	case Gitsn_Iso14827SubscriptionDataModePresent_periodic:
		Gitsn_Iso14827Registered_del(p->x.periodic);
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827SubscriptionDataMode_del(Gitsn_Iso14827SubscriptionDataMode *p)
{
	if (!p) return;
	Gitsn_Iso14827SubscriptionDataMode_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827SubscriptionDataMode_dump(Gitsn_Iso14827SubscriptionDataMode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827SubscriptionDataModePresent_single:
		Dz1Thread_printf(Dz1T("single = ")); Dz1s32_dump(p->x.single, tab); 
		break;
	case Gitsn_Iso14827SubscriptionDataModePresent_eventDriven:
		Dz1Thread_printf(Dz1T("eventDriven.")); Gitsn_Iso14827Registered_dump(p->x.eventDriven, tab); 
		break;
	case Gitsn_Iso14827SubscriptionDataModePresent_periodic:
		Dz1Thread_printf(Dz1T("periodic.")); Gitsn_Iso14827Registered_dump(p->x.periodic, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827SubscriptionDataMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataFormat
static struct Gitsn_Iso14827SubscriptionDataFormatMapA
{
	str_t str;
	Gitsn_Iso14827SubscriptionDataFormat v;
} Gitsn_Iso14827SubscriptionDataFormatMapA[] =
{
	{ (char *)"other", Gitsn_Iso14827SubscriptionDataFormat_other },
	{ (char *)"ftp", Gitsn_Iso14827SubscriptionDataFormat_ftp },
	{ (char *)"tftp", Gitsn_Iso14827SubscriptionDataFormat_tftp },
	{ (char *)"dataPacket", Gitsn_Iso14827SubscriptionDataFormat_dataPacket },
	{ NULL, Gitsn_Iso14827SubscriptionDataFormat_max }
};

str_t Gitsn_Iso14827SubscriptionDataFormatStrA(Gitsn_Iso14827SubscriptionDataFormat v)
{
	struct Gitsn_Iso14827SubscriptionDataFormatMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataFormatMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionDataFormat Gitsn_Iso14827SubscriptionDataFormatFromStrA(str_t str)
{
	struct Gitsn_Iso14827SubscriptionDataFormatMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataFormatMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionDataFormat_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827SubscriptionDataFormatMapW
{
	wstr_t str;
	Gitsn_Iso14827SubscriptionDataFormat v;
} Gitsn_Iso14827SubscriptionDataFormatMapW[] =
{
	{ (wchar_t *)L"other", Gitsn_Iso14827SubscriptionDataFormat_other },
	{ (wchar_t *)L"ftp", Gitsn_Iso14827SubscriptionDataFormat_ftp },
	{ (wchar_t *)L"tftp", Gitsn_Iso14827SubscriptionDataFormat_tftp },
	{ (wchar_t *)L"dataPacket", Gitsn_Iso14827SubscriptionDataFormat_dataPacket },
	{ NULL, Gitsn_Iso14827SubscriptionDataFormat_max }
};

wstr_t Gitsn_Iso14827SubscriptionDataFormatStrW(Gitsn_Iso14827SubscriptionDataFormat v)
{
	struct Gitsn_Iso14827SubscriptionDataFormatMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataFormatMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionDataFormat Gitsn_Iso14827SubscriptionDataFormatFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827SubscriptionDataFormatMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionDataFormatMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionDataFormat_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827SubscriptionDataFormat *Gitsn_Iso14827SubscriptionDataFormat_new(Gitsn_Iso14827SubscriptionDataFormat *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827SubscriptionDataFormat *__internal_ret = (Gitsn_Iso14827SubscriptionDataFormat *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionDataFormat), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827SubscriptionDataFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827EndAppMsg
Gitsn_Iso14827EndAppMsg *Gitsn_Iso14827EndAppMsg_new(Dz1Str oid, 
													 Dz1Binary *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827EndAppMsg *__internal_ret = (Gitsn_Iso14827EndAppMsg *)Dz1Calloc(sizeof(Gitsn_Iso14827EndAppMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827EndAppMsg_delAndSetNull, (void *)&__internal_ret);
		
		if (oid && (__internal_ret->oid = Dz1Str_clone(oid, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827EndAppMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827EndAppMsg_copy(Gitsn_Iso14827EndAppMsg *dst, Gitsn_Iso14827EndAppMsg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->oid && (dst->oid = Dz1Str_clone(src->oid, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Binary_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827EndAppMsg *Gitsn_Iso14827EndAppMsg_clone(Gitsn_Iso14827EndAppMsg *src, Dz1Error *err)
{
	Gitsn_Iso14827EndAppMsg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827EndAppMsg *)Dz1Calloc(sizeof(Gitsn_Iso14827EndAppMsg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827EndAppMsg_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827EndAppMsg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827EndAppMsg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827EndAppMsg_purge(Gitsn_Iso14827EndAppMsg *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->oid);
	Dz1Binary_del(p->data);
}

void Gitsn_Iso14827EndAppMsg_del(Gitsn_Iso14827EndAppMsg *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827EndAppMsg_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827EndAppMsg_dump(Gitsn_Iso14827EndAppMsg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("oid = ")); Dz1Str_dump(p->oid, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827EndAppMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionData
Gitsn_Iso14827SubscriptionData *Gitsn_Iso14827SubscriptionData_new(bool_t persistent, 
																   Gitsn_Iso14827SubscriptionDataStatus status, 
																   Gitsn_Iso14827SubscriptionDataMode *mode, 
																   Gitsn_Iso14827SubscriptionDataFormat fmt, 
																   s32_t priority, 
																   bool_t guarantee, 
																   Gitsn_Iso14827EndAppMsg *msg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827SubscriptionData *__internal_ret = (Gitsn_Iso14827SubscriptionData *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->persistent = persistent;
		__internal_ret->status = status;
		__internal_ret->mode = mode;
		__internal_ret->fmt = fmt;
		__internal_ret->priority = priority;
		__internal_ret->guarantee = guarantee;
		__internal_ret->msg = msg;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827SubscriptionData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827SubscriptionData_copy(Gitsn_Iso14827SubscriptionData *dst, Gitsn_Iso14827SubscriptionData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->mode && (dst->mode = Gitsn_Iso14827SubscriptionDataMode_clone(src->mode, errp)) == NULL) ERR_OUT(errp);
	else if (src->msg && (dst->msg = Gitsn_Iso14827EndAppMsg_clone(src->msg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->persistent = src->persistent;
		dst->status = src->status;
		dst->fmt = src->fmt;
		dst->priority = src->priority;
		dst->guarantee = src->guarantee;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827SubscriptionData *Gitsn_Iso14827SubscriptionData_clone(Gitsn_Iso14827SubscriptionData *src, Dz1Error *err)
{
	Gitsn_Iso14827SubscriptionData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827SubscriptionData *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionData_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827SubscriptionData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827SubscriptionData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827SubscriptionData_purge(Gitsn_Iso14827SubscriptionData *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827SubscriptionDataMode_del(p->mode);
	Gitsn_Iso14827EndAppMsg_del(p->msg);
}

void Gitsn_Iso14827SubscriptionData_del(Gitsn_Iso14827SubscriptionData *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827SubscriptionData_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827SubscriptionData_dump(Gitsn_Iso14827SubscriptionData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("persistent = ")); Dz1Bool_dump(&p->persistent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("status = %s(%d)\n"), Gitsn_Iso14827SubscriptionDataStatusStr(p->status), p->status);
		Dz1Thread_tprintf(tab, Dz1T("mode.")); Gitsn_Iso14827SubscriptionDataMode_dump(p->mode, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fmt = %s(%d)\n"), Gitsn_Iso14827SubscriptionDataFormatStr(p->fmt), p->fmt);
		Dz1Thread_tprintf(tab, Dz1T("priority = ")); Dz1s32_dump(&p->priority, tab); 
		Dz1Thread_tprintf(tab, Dz1T("guarantee = ")); Dz1Bool_dump(&p->guarantee, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("msg = ")); Gitsn_Iso14827EndAppMsg_dump(p->msg, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827SubscriptionData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionCancel
static struct Gitsn_Iso14827SubscriptionCancelMapA
{
	str_t str;
	Gitsn_Iso14827SubscriptionCancel v;
} Gitsn_Iso14827SubscriptionCancelMapA[] =
{
	{ (char *)"other", Gitsn_Iso14827SubscriptionCancel_other },
	{ (char *)"dataNotNeeded", Gitsn_Iso14827SubscriptionCancel_dataNotNeeded },
	{ (char *)"errorsInPublication", Gitsn_Iso14827SubscriptionCancel_errorsInPublication },
	{ (char *)"pendingLogout", Gitsn_Iso14827SubscriptionCancel_pendingLogout },
	{ (char *)"processingMgmt", Gitsn_Iso14827SubscriptionCancel_processingMgmt },
	{ (char *)"bandwidthMgmt", Gitsn_Iso14827SubscriptionCancel_bandwidthMgmt },
	{ NULL, Gitsn_Iso14827SubscriptionCancel_max }
};

str_t Gitsn_Iso14827SubscriptionCancelStrA(Gitsn_Iso14827SubscriptionCancel v)
{
	struct Gitsn_Iso14827SubscriptionCancelMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionCancelMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionCancel Gitsn_Iso14827SubscriptionCancelFromStrA(str_t str)
{
	struct Gitsn_Iso14827SubscriptionCancelMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionCancelMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionCancel_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827SubscriptionCancelMapW
{
	wstr_t str;
	Gitsn_Iso14827SubscriptionCancel v;
} Gitsn_Iso14827SubscriptionCancelMapW[] =
{
	{ (wchar_t *)L"other", Gitsn_Iso14827SubscriptionCancel_other },
	{ (wchar_t *)L"dataNotNeeded", Gitsn_Iso14827SubscriptionCancel_dataNotNeeded },
	{ (wchar_t *)L"errorsInPublication", Gitsn_Iso14827SubscriptionCancel_errorsInPublication },
	{ (wchar_t *)L"pendingLogout", Gitsn_Iso14827SubscriptionCancel_pendingLogout },
	{ (wchar_t *)L"processingMgmt", Gitsn_Iso14827SubscriptionCancel_processingMgmt },
	{ (wchar_t *)L"bandwidthMgmt", Gitsn_Iso14827SubscriptionCancel_bandwidthMgmt },
	{ NULL, Gitsn_Iso14827SubscriptionCancel_max }
};

wstr_t Gitsn_Iso14827SubscriptionCancelStrW(Gitsn_Iso14827SubscriptionCancel v)
{
	struct Gitsn_Iso14827SubscriptionCancelMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionCancelMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionCancel Gitsn_Iso14827SubscriptionCancelFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827SubscriptionCancelMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionCancelMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionCancel_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827SubscriptionCancel *Gitsn_Iso14827SubscriptionCancel_new(Gitsn_Iso14827SubscriptionCancel *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827SubscriptionCancel *__internal_ret = (Gitsn_Iso14827SubscriptionCancel *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionCancel), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827SubscriptionCancel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionTypePresent
static struct Gitsn_Iso14827SubscriptionTypePresentMapA
{
	str_t str;
	Gitsn_Iso14827SubscriptionTypePresent v;
} Gitsn_Iso14827SubscriptionTypePresentMapA[] =
{
	{ (char *)"data", Gitsn_Iso14827SubscriptionTypePresent_data },
	{ (char *)"reason", Gitsn_Iso14827SubscriptionTypePresent_reason },
	{ NULL, Gitsn_Iso14827SubscriptionTypePresent_max }
};

str_t Gitsn_Iso14827SubscriptionTypePresentStrA(Gitsn_Iso14827SubscriptionTypePresent v)
{
	struct Gitsn_Iso14827SubscriptionTypePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionTypePresent Gitsn_Iso14827SubscriptionTypePresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827SubscriptionTypePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827SubscriptionTypePresentMapW
{
	wstr_t str;
	Gitsn_Iso14827SubscriptionTypePresent v;
} Gitsn_Iso14827SubscriptionTypePresentMapW[] =
{
	{ (wchar_t *)L"data", Gitsn_Iso14827SubscriptionTypePresent_data },
	{ (wchar_t *)L"reason", Gitsn_Iso14827SubscriptionTypePresent_reason },
	{ NULL, Gitsn_Iso14827SubscriptionTypePresent_max }
};

wstr_t Gitsn_Iso14827SubscriptionTypePresentStrW(Gitsn_Iso14827SubscriptionTypePresent v)
{
	struct Gitsn_Iso14827SubscriptionTypePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827SubscriptionTypePresent Gitsn_Iso14827SubscriptionTypePresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827SubscriptionTypePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827SubscriptionTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827SubscriptionTypePresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827SubscriptionTypePresent *Gitsn_Iso14827SubscriptionTypePresent_new(Gitsn_Iso14827SubscriptionTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827SubscriptionTypePresent *__internal_ret = (Gitsn_Iso14827SubscriptionTypePresent *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827SubscriptionTypePresent_dump(Gitsn_Iso14827SubscriptionTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827SubscriptionTypePresentStr(*v));
}
// Gitsn_Iso14827SubscriptionTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionType
Gitsn_Iso14827SubscriptionType *Gitsn_Iso14827SubscriptionType_new(Gitsn_Iso14827SubscriptionTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827SubscriptionType *ret = (Gitsn_Iso14827SubscriptionType *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827SubscriptionTypePresent_data:
			// _U_cst_clone
			if (ptr != NULL) ret->x.data = (Gitsn_Iso14827SubscriptionData *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827SubscriptionTypePresent_reason:
			// _U_enum_clone
			if (ptr != NULL) ret->x.reason = *(Gitsn_Iso14827SubscriptionCancel *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827SubscriptionTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827SubscriptionType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827SubscriptionType_copy(Gitsn_Iso14827SubscriptionType *ret, Gitsn_Iso14827SubscriptionType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827SubscriptionTypePresent_data:
			// _U_cst_clone
			if (src->x.data && (ret->x.data = Gitsn_Iso14827SubscriptionData_clone(src->x.data, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827SubscriptionTypePresent_reason:
			// _U_enum_clone
			ret->x.reason = src->x.reason;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827SubscriptionType *Gitsn_Iso14827SubscriptionType_clone(Gitsn_Iso14827SubscriptionType *src, Dz1Error *err)
{
	Gitsn_Iso14827SubscriptionType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827SubscriptionType *)Dz1Calloc(sizeof(Gitsn_Iso14827SubscriptionType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionType_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827SubscriptionType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827SubscriptionType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827SubscriptionType_purge(Gitsn_Iso14827SubscriptionType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827SubscriptionTypePresent_data:
		Gitsn_Iso14827SubscriptionData_del(p->x.data);
		break;
	case Gitsn_Iso14827SubscriptionTypePresent_reason:
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827SubscriptionType_del(Gitsn_Iso14827SubscriptionType *p)
{
	if (!p) return;
	Gitsn_Iso14827SubscriptionType_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827SubscriptionType_dump(Gitsn_Iso14827SubscriptionType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827SubscriptionTypePresent_data:
		Dz1Thread_printf(Dz1T("data = ")); Gitsn_Iso14827SubscriptionData_dump(p->x.data, tab); 
		break;
	case Gitsn_Iso14827SubscriptionTypePresent_reason:
		Dz1Thread_printf(Dz1T("reason = %s(%d)\n"), Gitsn_Iso14827SubscriptionCancelStr(p->x.reason), p->x.reason);
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827SubscriptionType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Subscription
Gitsn_Iso14827Subscription *Gitsn_Iso14827Subscription_new(u32_t serial, 
														   Gitsn_Iso14827SubscriptionType *type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Subscription *__internal_ret = (Gitsn_Iso14827Subscription *)Dz1Calloc(sizeof(Gitsn_Iso14827Subscription), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Subscription_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->serial = serial;
		__internal_ret->type = type;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Subscription_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827Subscription_copy(Gitsn_Iso14827Subscription *dst, Gitsn_Iso14827Subscription *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->type && (dst->type = Gitsn_Iso14827SubscriptionType_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->serial = src->serial;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Subscription *Gitsn_Iso14827Subscription_clone(Gitsn_Iso14827Subscription *src, Dz1Error *err)
{
	Gitsn_Iso14827Subscription *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827Subscription *)Dz1Calloc(sizeof(Gitsn_Iso14827Subscription), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Subscription_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827Subscription_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Subscription_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827Subscription_purge(Gitsn_Iso14827Subscription *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827SubscriptionType_del(p->type);
}

void Gitsn_Iso14827Subscription_del(Gitsn_Iso14827Subscription *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Subscription_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827Subscription_dump(Gitsn_Iso14827Subscription *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type.")); Gitsn_Iso14827SubscriptionType_dump(p->type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827Subscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationMgmt
static struct Gitsn_Iso14827PublicationMgmtMapA
{
	str_t str;
	Gitsn_Iso14827PublicationMgmt v;
} Gitsn_Iso14827PublicationMgmtMapA[] =
{
	{ (char *)"temporarilySuspended", Gitsn_Iso14827PublicationMgmt_temporarilySuspended },
	{ (char *)"resume", Gitsn_Iso14827PublicationMgmt_resume },
	{ (char *)"terminateOther", Gitsn_Iso14827PublicationMgmt_terminateOther },
	{ (char *)"terminateDataNoLongerAvailable", Gitsn_Iso14827PublicationMgmt_terminateDataNoLongerAvailable },
	{ (char *)"terminatePublicationsBeingRejected", Gitsn_Iso14827PublicationMgmt_terminatePublicationsBeingRejected },
	{ (char *)"terminatePendingShutdown", Gitsn_Iso14827PublicationMgmt_terminatePendingShutdown },
	{ (char *)"terminateProcessingMgmt", Gitsn_Iso14827PublicationMgmt_terminateProcessingMgmt },
	{ (char *)"terminateBandwidthMgmt", Gitsn_Iso14827PublicationMgmt_terminateBandwidthMgmt },
	{ (char *)"terminateAccessDenied", Gitsn_Iso14827PublicationMgmt_terminateAccessDenied },
	{ (char *)"unknownRequest", Gitsn_Iso14827PublicationMgmt_unknownRequest },
	{ NULL, Gitsn_Iso14827PublicationMgmt_max }
};

str_t Gitsn_Iso14827PublicationMgmtStrA(Gitsn_Iso14827PublicationMgmt v)
{
	struct Gitsn_Iso14827PublicationMgmtMapA *i = NULL;
	for (i = Gitsn_Iso14827PublicationMgmtMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827PublicationMgmt Gitsn_Iso14827PublicationMgmtFromStrA(str_t str)
{
	struct Gitsn_Iso14827PublicationMgmtMapA *i = NULL;
	for (i = Gitsn_Iso14827PublicationMgmtMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827PublicationMgmt_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827PublicationMgmtMapW
{
	wstr_t str;
	Gitsn_Iso14827PublicationMgmt v;
} Gitsn_Iso14827PublicationMgmtMapW[] =
{
	{ (wchar_t *)L"temporarilySuspended", Gitsn_Iso14827PublicationMgmt_temporarilySuspended },
	{ (wchar_t *)L"resume", Gitsn_Iso14827PublicationMgmt_resume },
	{ (wchar_t *)L"terminateOther", Gitsn_Iso14827PublicationMgmt_terminateOther },
	{ (wchar_t *)L"terminateDataNoLongerAvailable", Gitsn_Iso14827PublicationMgmt_terminateDataNoLongerAvailable },
	{ (wchar_t *)L"terminatePublicationsBeingRejected", Gitsn_Iso14827PublicationMgmt_terminatePublicationsBeingRejected },
	{ (wchar_t *)L"terminatePendingShutdown", Gitsn_Iso14827PublicationMgmt_terminatePendingShutdown },
	{ (wchar_t *)L"terminateProcessingMgmt", Gitsn_Iso14827PublicationMgmt_terminateProcessingMgmt },
	{ (wchar_t *)L"terminateBandwidthMgmt", Gitsn_Iso14827PublicationMgmt_terminateBandwidthMgmt },
	{ (wchar_t *)L"terminateAccessDenied", Gitsn_Iso14827PublicationMgmt_terminateAccessDenied },
	{ (wchar_t *)L"unknownRequest", Gitsn_Iso14827PublicationMgmt_unknownRequest },
	{ NULL, Gitsn_Iso14827PublicationMgmt_max }
};

wstr_t Gitsn_Iso14827PublicationMgmtStrW(Gitsn_Iso14827PublicationMgmt v)
{
	struct Gitsn_Iso14827PublicationMgmtMapW *i = NULL;
	for (i = Gitsn_Iso14827PublicationMgmtMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827PublicationMgmt Gitsn_Iso14827PublicationMgmtFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827PublicationMgmtMapW *i = NULL;
	for (i = Gitsn_Iso14827PublicationMgmtMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827PublicationMgmt_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827PublicationMgmt *Gitsn_Iso14827PublicationMgmt_new(Gitsn_Iso14827PublicationMgmt *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PublicationMgmt *__internal_ret = (Gitsn_Iso14827PublicationMgmt *)Dz1Calloc(sizeof(Gitsn_Iso14827PublicationMgmt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827PublicationMgmt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationTypePresent
static struct Gitsn_Iso14827PublicationTypePresentMapA
{
	str_t str;
	Gitsn_Iso14827PublicationTypePresent v;
} Gitsn_Iso14827PublicationTypePresentMapA[] =
{
	{ (char *)"mgmt", Gitsn_Iso14827PublicationTypePresent_mgmt },
	{ (char *)"msg", Gitsn_Iso14827PublicationTypePresent_msg },
	{ NULL, Gitsn_Iso14827PublicationTypePresent_max }
};

str_t Gitsn_Iso14827PublicationTypePresentStrA(Gitsn_Iso14827PublicationTypePresent v)
{
	struct Gitsn_Iso14827PublicationTypePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827PublicationTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827PublicationTypePresent Gitsn_Iso14827PublicationTypePresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827PublicationTypePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827PublicationTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827PublicationTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827PublicationTypePresentMapW
{
	wstr_t str;
	Gitsn_Iso14827PublicationTypePresent v;
} Gitsn_Iso14827PublicationTypePresentMapW[] =
{
	{ (wchar_t *)L"mgmt", Gitsn_Iso14827PublicationTypePresent_mgmt },
	{ (wchar_t *)L"msg", Gitsn_Iso14827PublicationTypePresent_msg },
	{ NULL, Gitsn_Iso14827PublicationTypePresent_max }
};

wstr_t Gitsn_Iso14827PublicationTypePresentStrW(Gitsn_Iso14827PublicationTypePresent v)
{
	struct Gitsn_Iso14827PublicationTypePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827PublicationTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827PublicationTypePresent Gitsn_Iso14827PublicationTypePresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827PublicationTypePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827PublicationTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827PublicationTypePresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827PublicationTypePresent *Gitsn_Iso14827PublicationTypePresent_new(Gitsn_Iso14827PublicationTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PublicationTypePresent *__internal_ret = (Gitsn_Iso14827PublicationTypePresent *)Dz1Calloc(sizeof(Gitsn_Iso14827PublicationTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827PublicationTypePresent_dump(Gitsn_Iso14827PublicationTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827PublicationTypePresentStr(*v));
}
// Gitsn_Iso14827PublicationTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationType
Gitsn_Iso14827PublicationType *Gitsn_Iso14827PublicationType_new(Gitsn_Iso14827PublicationTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PublicationType *ret = (Gitsn_Iso14827PublicationType *)Dz1Calloc(sizeof(Gitsn_Iso14827PublicationType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublicationType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827PublicationTypePresent_mgmt:
			// _U_enum_clone
			if (ptr != NULL) ret->x.mgmt = *(Gitsn_Iso14827PublicationMgmt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PublicationTypePresent_msg:
			// _U_cst_clone
			if (ptr != NULL) ret->x.msg = (Gitsn_Iso14827EndAppMsg *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PublicationTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PublicationType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827PublicationType_copy(Gitsn_Iso14827PublicationType *ret, Gitsn_Iso14827PublicationType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827PublicationTypePresent_mgmt:
			// _U_enum_clone
			ret->x.mgmt = src->x.mgmt;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PublicationTypePresent_msg:
			// _U_cst_clone
			if (src->x.msg && (ret->x.msg = Gitsn_Iso14827EndAppMsg_clone(src->x.msg, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827PublicationType *Gitsn_Iso14827PublicationType_clone(Gitsn_Iso14827PublicationType *src, Dz1Error *err)
{
	Gitsn_Iso14827PublicationType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827PublicationType *)Dz1Calloc(sizeof(Gitsn_Iso14827PublicationType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublicationType_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827PublicationType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PublicationType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827PublicationType_purge(Gitsn_Iso14827PublicationType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827PublicationTypePresent_mgmt:
		break;
	case Gitsn_Iso14827PublicationTypePresent_msg:
		Gitsn_Iso14827EndAppMsg_del(p->x.msg);
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827PublicationType_del(Gitsn_Iso14827PublicationType *p)
{
	if (!p) return;
	Gitsn_Iso14827PublicationType_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827PublicationType_dump(Gitsn_Iso14827PublicationType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827PublicationTypePresent_mgmt:
		Dz1Thread_printf(Dz1T("mgmt = %s(%d)\n"), Gitsn_Iso14827PublicationMgmtStr(p->x.mgmt), p->x.mgmt);
		break;
	case Gitsn_Iso14827PublicationTypePresent_msg:
		Dz1Thread_printf(Dz1T("msg = ")); Gitsn_Iso14827EndAppMsg_dump(p->x.msg, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827PublicationType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationData
Gitsn_Iso14827PublicationData *Gitsn_Iso14827PublicationData_new(u32_t subscriptionSerial, 
																 u32_t serial, 
																 bool_t isLated, 
																 Gitsn_Iso14827PublicationType *type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PublicationData *__internal_ret = (Gitsn_Iso14827PublicationData *)Dz1Calloc(sizeof(Gitsn_Iso14827PublicationData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublicationData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->subscriptionSerial = subscriptionSerial;
		__internal_ret->serial = serial;
		__internal_ret->isLated = isLated;
		__internal_ret->type = type;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PublicationData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827PublicationData_copy(Gitsn_Iso14827PublicationData *dst, Gitsn_Iso14827PublicationData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->type && (dst->type = Gitsn_Iso14827PublicationType_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subscriptionSerial = src->subscriptionSerial;
		dst->serial = src->serial;
		dst->isLated = src->isLated;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827PublicationData *Gitsn_Iso14827PublicationData_clone(Gitsn_Iso14827PublicationData *src, Dz1Error *err)
{
	Gitsn_Iso14827PublicationData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827PublicationData *)Dz1Calloc(sizeof(Gitsn_Iso14827PublicationData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublicationData_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827PublicationData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PublicationData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827PublicationData_purge(Gitsn_Iso14827PublicationData *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827PublicationType_del(p->type);
}

void Gitsn_Iso14827PublicationData_del(Gitsn_Iso14827PublicationData *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827PublicationData_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827PublicationData_dump(Gitsn_Iso14827PublicationData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("subscriptionSerial = ")); Dz1u32_dump(&p->subscriptionSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isLated = ")); Dz1Bool_dump(&p->isLated, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type.")); Gitsn_Iso14827PublicationType_dump(p->type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Gitsn_Iso14827PublicationData_cmp(Gitsn_Iso14827PublicationData *a, Gitsn_Iso14827PublicationData *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->subscriptionSerial, &b->subscriptionSerial)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->serial, &b->serial)) != 0) { }
	return ret;
}
// Gitsn_Iso14827PublicationData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationDataList
static Dz1Error Gitsn_Iso14827PublicationDataList_add(Gitsn_Iso14827PublicationDataList *p, Gitsn_Iso14827PublicationData *data)
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

static bool_t Gitsn_Iso14827PublicationDataList_remove(Gitsn_Iso14827PublicationDataList *p, Gitsn_Iso14827PublicationData *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Gitsn_Iso14827PublicationData *Gitsn_Iso14827PublicationDataList_extract(Gitsn_Iso14827PublicationDataList *p, Gitsn_Iso14827PublicationData *key)
{
	return (Gitsn_Iso14827PublicationData *)Dz1AATree_extract(p->storage, key);
}

typedef struct Gitsn_Iso14827PublicationDataListMkArrArg
{
	Gitsn_Iso14827PublicationData **arr;
	unsigned int idx;
} Gitsn_Iso14827PublicationDataListMkArrArg;

static Dz1Error _Gitsn_Iso14827PublicationDataList_get_array(void *ptr, Gitsn_Iso14827PublicationData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Gitsn_Iso14827PublicationDataListMkArrArg *arg = (Gitsn_Iso14827PublicationDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Gitsn_Iso14827PublicationData **Gitsn_Iso14827PublicationDataList_get_array(Gitsn_Iso14827PublicationDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Gitsn_Iso14827PublicationData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Gitsn_Iso14827PublicationData **)Dz1Calloc(sizeof(Gitsn_Iso14827PublicationData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_Iso14827PublicationDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Gitsn_Iso14827PublicationDataList_get_array, (void *)&arg);
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

static Dz1Error Gitsn_Iso14827PublicationDataList_travelForward(Gitsn_Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Gitsn_Iso14827PublicationData *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Gitsn_Iso14827PublicationDataList_travelBackward(Gitsn_Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Gitsn_Iso14827PublicationData *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Gitsn_Iso14827PublicationData *Gitsn_Iso14827PublicationDataList_find(Gitsn_Iso14827PublicationDataList *p, Gitsn_Iso14827PublicationData *key)
{
	return (Gitsn_Iso14827PublicationData *)Dz1AATree_find(p->storage, key);
}

static Gitsn_Iso14827PublicationData *Gitsn_Iso14827PublicationDataList_getHead(Gitsn_Iso14827PublicationDataList *p)
{
	return (Gitsn_Iso14827PublicationData *)Dz1AATree_getHead(p->storage);
}

static unsigned int Gitsn_Iso14827PublicationDataList_count(Gitsn_Iso14827PublicationDataList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Gitsn_Iso14827PublicationDataList *Gitsn_Iso14827PublicationDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PublicationDataList *ret = (Gitsn_Iso14827PublicationDataList *)Dz1Calloc(sizeof(Gitsn_Iso14827PublicationDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublicationDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Gitsn_Iso14827PublicationData_cmp,
				(Dz1DelFunc)Gitsn_Iso14827PublicationData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Gitsn_Iso14827PublicationDataList_count;
			ret->travel = Gitsn_Iso14827PublicationDataList_travelForward;
			ret->travelForward = Gitsn_Iso14827PublicationDataList_travelForward;
			ret->travelBackward = Gitsn_Iso14827PublicationDataList_travelBackward;
			ret->get_array = Gitsn_Iso14827PublicationDataList_get_array;
			ret->add = Gitsn_Iso14827PublicationDataList_add;
			ret->remove = Gitsn_Iso14827PublicationDataList_remove;
			ret->find = Gitsn_Iso14827PublicationDataList_find;
			ret->extract = Gitsn_Iso14827PublicationDataList_extract;
			ret->getHead = Gitsn_Iso14827PublicationDataList_getHead;
			ret->cmp = Gitsn_Iso14827PublicationData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PublicationDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Gitsn_Iso14827PublicationDataList_clone(void *ptr, Gitsn_Iso14827PublicationData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Gitsn_Iso14827PublicationDataList *p = (Gitsn_Iso14827PublicationDataList *)ptr;
	Gitsn_Iso14827PublicationData *cloned = Gitsn_Iso14827PublicationData_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Gitsn_Iso14827PublicationDataList *Gitsn_Iso14827PublicationDataList_clone(Gitsn_Iso14827PublicationDataList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PublicationDataList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Gitsn_Iso14827PublicationDataList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublicationDataList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Gitsn_Iso14827PublicationDataList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PublicationDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827PublicationDataList_purge(Gitsn_Iso14827PublicationDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Gitsn_Iso14827PublicationDataList_del(Gitsn_Iso14827PublicationDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Gitsn_Iso14827PublicationDataList_dump(void *ptr, Gitsn_Iso14827PublicationData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Gitsn_Iso14827PublicationData_dump(p, tab);
	return err;
}

void Gitsn_Iso14827PublicationDataList_dump(Gitsn_Iso14827PublicationDataList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Gitsn_Iso14827PublicationDataList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827PublicationDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublishFormatPresent
static struct Gitsn_Iso14827PublishFormatPresentMapA
{
	str_t str;
	Gitsn_Iso14827PublishFormatPresent v;
} Gitsn_Iso14827PublishFormatPresentMapA[] =
{
	{ (char *)"dataList", Gitsn_Iso14827PublishFormatPresent_dataList },
	{ (char *)"filename", Gitsn_Iso14827PublishFormatPresent_filename },
	{ NULL, Gitsn_Iso14827PublishFormatPresent_max }
};

str_t Gitsn_Iso14827PublishFormatPresentStrA(Gitsn_Iso14827PublishFormatPresent v)
{
	struct Gitsn_Iso14827PublishFormatPresentMapA *i = NULL;
	for (i = Gitsn_Iso14827PublishFormatPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827PublishFormatPresent Gitsn_Iso14827PublishFormatPresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827PublishFormatPresentMapA *i = NULL;
	for (i = Gitsn_Iso14827PublishFormatPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827PublishFormatPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827PublishFormatPresentMapW
{
	wstr_t str;
	Gitsn_Iso14827PublishFormatPresent v;
} Gitsn_Iso14827PublishFormatPresentMapW[] =
{
	{ (wchar_t *)L"dataList", Gitsn_Iso14827PublishFormatPresent_dataList },
	{ (wchar_t *)L"filename", Gitsn_Iso14827PublishFormatPresent_filename },
	{ NULL, Gitsn_Iso14827PublishFormatPresent_max }
};

wstr_t Gitsn_Iso14827PublishFormatPresentStrW(Gitsn_Iso14827PublishFormatPresent v)
{
	struct Gitsn_Iso14827PublishFormatPresentMapW *i = NULL;
	for (i = Gitsn_Iso14827PublishFormatPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827PublishFormatPresent Gitsn_Iso14827PublishFormatPresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827PublishFormatPresentMapW *i = NULL;
	for (i = Gitsn_Iso14827PublishFormatPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827PublishFormatPresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827PublishFormatPresent *Gitsn_Iso14827PublishFormatPresent_new(Gitsn_Iso14827PublishFormatPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PublishFormatPresent *__internal_ret = (Gitsn_Iso14827PublishFormatPresent *)Dz1Calloc(sizeof(Gitsn_Iso14827PublishFormatPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827PublishFormatPresent_dump(Gitsn_Iso14827PublishFormatPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827PublishFormatPresentStr(*v));
}
// Gitsn_Iso14827PublishFormatPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublishFormat
Gitsn_Iso14827PublishFormat *Gitsn_Iso14827PublishFormat_new(Gitsn_Iso14827PublishFormatPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PublishFormat *ret = (Gitsn_Iso14827PublishFormat *)Dz1Calloc(sizeof(Gitsn_Iso14827PublishFormat), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublishFormat_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827PublishFormatPresent_dataList:
			// _U_cst_clone
			if (ptr != NULL) ret->x.dataList = (Gitsn_Iso14827PublicationDataList *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PublishFormatPresent_filename:
			// _U_prim_clone
			if (ptr && (ret->x.filename = Dz1Str_clone((Dz1Str)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827PublishFormatPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PublishFormat_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827PublishFormat_copy(Gitsn_Iso14827PublishFormat *ret, Gitsn_Iso14827PublishFormat *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827PublishFormatPresent_dataList:
			// _U_cst_clone
			if (src->x.dataList && (ret->x.dataList = Gitsn_Iso14827PublicationDataList_clone(src->x.dataList, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827PublishFormatPresent_filename:
			// _U_prim_clone
			if (src->x.filename && (ret->x.filename = Dz1Str_clone(src->x.filename, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827PublishFormat *Gitsn_Iso14827PublishFormat_clone(Gitsn_Iso14827PublishFormat *src, Dz1Error *err)
{
	Gitsn_Iso14827PublishFormat *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827PublishFormat *)Dz1Calloc(sizeof(Gitsn_Iso14827PublishFormat), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublishFormat_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827PublishFormat_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PublishFormat_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827PublishFormat_purge(Gitsn_Iso14827PublishFormat *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827PublishFormatPresent_dataList:
		Gitsn_Iso14827PublicationDataList_del(p->x.dataList);
		break;
	case Gitsn_Iso14827PublishFormatPresent_filename:
		Dz1Str_del(p->x.filename);
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827PublishFormat_del(Gitsn_Iso14827PublishFormat *p)
{
	if (!p) return;
	Gitsn_Iso14827PublishFormat_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827PublishFormat_dump(Gitsn_Iso14827PublishFormat *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827PublishFormatPresent_dataList:
		Dz1Thread_printf(Dz1T("dataList = ")); Gitsn_Iso14827PublicationDataList_dump(p->x.dataList, tab); 
		break;
	case Gitsn_Iso14827PublishFormatPresent_filename:
		Dz1Thread_printf(Dz1T("filename = ")); Dz1Str_dump(p->x.filename, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827PublishFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Publication
Gitsn_Iso14827Publication *Gitsn_Iso14827Publication_new(bool_t guaranteed, 
														 Gitsn_Iso14827PublishFormat *fmt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Publication *__internal_ret = (Gitsn_Iso14827Publication *)Dz1Calloc(sizeof(Gitsn_Iso14827Publication), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Publication_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->guaranteed = guaranteed;
		__internal_ret->fmt = fmt;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Publication_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827Publication_copy(Gitsn_Iso14827Publication *dst, Gitsn_Iso14827Publication *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->fmt && (dst->fmt = Gitsn_Iso14827PublishFormat_clone(src->fmt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->guaranteed = src->guaranteed;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Publication *Gitsn_Iso14827Publication_clone(Gitsn_Iso14827Publication *src, Dz1Error *err)
{
	Gitsn_Iso14827Publication *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827Publication *)Dz1Calloc(sizeof(Gitsn_Iso14827Publication), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Publication_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827Publication_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Publication_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827Publication_purge(Gitsn_Iso14827Publication *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827PublishFormat_del(p->fmt);
}

void Gitsn_Iso14827Publication_del(Gitsn_Iso14827Publication *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Publication_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827Publication_dump(Gitsn_Iso14827Publication *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("guaranteed = ")); Dz1Bool_dump(&p->guaranteed, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fmt.")); Gitsn_Iso14827PublishFormat_dump(p->fmt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827Publication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TransferDone
Gitsn_Iso14827TransferDone *Gitsn_Iso14827TransferDone_new(Dz1Str filename, 
														   bool_t isSuccess, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827TransferDone *__internal_ret = (Gitsn_Iso14827TransferDone *)Dz1Calloc(sizeof(Gitsn_Iso14827TransferDone), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TransferDone_delAndSetNull, (void *)&__internal_ret);
		
		if (filename && (__internal_ret->filename = Dz1Str_clone(filename, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->isSuccess = isSuccess;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827TransferDone_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827TransferDone_copy(Gitsn_Iso14827TransferDone *dst, Gitsn_Iso14827TransferDone *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->filename && (dst->filename = Dz1Str_clone(src->filename, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->isSuccess = src->isSuccess;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827TransferDone *Gitsn_Iso14827TransferDone_clone(Gitsn_Iso14827TransferDone *src, Dz1Error *err)
{
	Gitsn_Iso14827TransferDone *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827TransferDone *)Dz1Calloc(sizeof(Gitsn_Iso14827TransferDone), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TransferDone_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827TransferDone_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827TransferDone_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827TransferDone_purge(Gitsn_Iso14827TransferDone *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->filename);
}

void Gitsn_Iso14827TransferDone_del(Gitsn_Iso14827TransferDone *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827TransferDone_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827TransferDone_dump(Gitsn_Iso14827TransferDone *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("filename = ")); Dz1Str_dump(p->filename, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isSuccess = ")); Dz1Bool_dump(&p->isSuccess, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827TransferDone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827AcceptTypePresent
static struct Gitsn_Iso14827AcceptTypePresentMapA
{
	str_t str;
	Gitsn_Iso14827AcceptTypePresent v;
} Gitsn_Iso14827AcceptTypePresentMapA[] =
{
	{ (char *)"login", Gitsn_Iso14827AcceptTypePresent_login },
	{ (char *)"singleSubscription", Gitsn_Iso14827AcceptTypePresent_singleSubscription },
	{ (char *)"registeredSubscription", Gitsn_Iso14827AcceptTypePresent_registeredSubscription },
	{ (char *)"publication", Gitsn_Iso14827AcceptTypePresent_publication },
	{ NULL, Gitsn_Iso14827AcceptTypePresent_max }
};

str_t Gitsn_Iso14827AcceptTypePresentStrA(Gitsn_Iso14827AcceptTypePresent v)
{
	struct Gitsn_Iso14827AcceptTypePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827AcceptTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827AcceptTypePresent Gitsn_Iso14827AcceptTypePresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827AcceptTypePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827AcceptTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827AcceptTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827AcceptTypePresentMapW
{
	wstr_t str;
	Gitsn_Iso14827AcceptTypePresent v;
} Gitsn_Iso14827AcceptTypePresentMapW[] =
{
	{ (wchar_t *)L"login", Gitsn_Iso14827AcceptTypePresent_login },
	{ (wchar_t *)L"singleSubscription", Gitsn_Iso14827AcceptTypePresent_singleSubscription },
	{ (wchar_t *)L"registeredSubscription", Gitsn_Iso14827AcceptTypePresent_registeredSubscription },
	{ (wchar_t *)L"publication", Gitsn_Iso14827AcceptTypePresent_publication },
	{ NULL, Gitsn_Iso14827AcceptTypePresent_max }
};

wstr_t Gitsn_Iso14827AcceptTypePresentStrW(Gitsn_Iso14827AcceptTypePresent v)
{
	struct Gitsn_Iso14827AcceptTypePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827AcceptTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827AcceptTypePresent Gitsn_Iso14827AcceptTypePresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827AcceptTypePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827AcceptTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827AcceptTypePresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827AcceptTypePresent *Gitsn_Iso14827AcceptTypePresent_new(Gitsn_Iso14827AcceptTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827AcceptTypePresent *__internal_ret = (Gitsn_Iso14827AcceptTypePresent *)Dz1Calloc(sizeof(Gitsn_Iso14827AcceptTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827AcceptTypePresent_dump(Gitsn_Iso14827AcceptTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827AcceptTypePresentStr(*v));
}
// Gitsn_Iso14827AcceptTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827AcceptType
Gitsn_Iso14827AcceptType *Gitsn_Iso14827AcceptType_new(Gitsn_Iso14827AcceptTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827AcceptType *ret = (Gitsn_Iso14827AcceptType *)Dz1Calloc(sizeof(Gitsn_Iso14827AcceptType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827AcceptType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827AcceptTypePresent_login:
			// _U_prim_clone
			if (ptr && (ret->x.login = Dz1Str_clone((Dz1Str)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827AcceptTypePresent_singleSubscription:
			// _U_prim_clone
			if (ptr != NULL) ret->x.singleSubscription = (s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827AcceptTypePresent_registeredSubscription:
			// _U_prim_clone
			if (ptr != NULL) ret->x.registeredSubscription = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827AcceptTypePresent_publication:
			// _U_prim_clone
			if (ptr != NULL) ret->x.publication = (s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827AcceptTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827AcceptType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827AcceptType_copy(Gitsn_Iso14827AcceptType *ret, Gitsn_Iso14827AcceptType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827AcceptTypePresent_login:
			// _U_prim_clone
			if (src->x.login && (ret->x.login = Dz1Str_clone(src->x.login, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827AcceptTypePresent_singleSubscription:
			// _U_prim_clone
			if (src->x.singleSubscription && (ret->x.singleSubscription = Dz1s32_clone(src->x.singleSubscription, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827AcceptTypePresent_registeredSubscription:
			// _U_prim_clone
			ret->x.registeredSubscription = src->x.registeredSubscription;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827AcceptTypePresent_publication:
			// _U_prim_clone
			if (src->x.publication && (ret->x.publication = Dz1s32_clone(src->x.publication, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827AcceptType *Gitsn_Iso14827AcceptType_clone(Gitsn_Iso14827AcceptType *src, Dz1Error *err)
{
	Gitsn_Iso14827AcceptType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827AcceptType *)Dz1Calloc(sizeof(Gitsn_Iso14827AcceptType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827AcceptType_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827AcceptType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827AcceptType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827AcceptType_purge(Gitsn_Iso14827AcceptType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827AcceptTypePresent_login:
		Dz1Str_del(p->x.login);
		break;
	case Gitsn_Iso14827AcceptTypePresent_singleSubscription:
		Dz1s32_del(p->x.singleSubscription);
		break;
	case Gitsn_Iso14827AcceptTypePresent_registeredSubscription:
		break;
	case Gitsn_Iso14827AcceptTypePresent_publication:
		Dz1s32_del(p->x.publication);
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827AcceptType_del(Gitsn_Iso14827AcceptType *p)
{
	if (!p) return;
	Gitsn_Iso14827AcceptType_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827AcceptType_dump(Gitsn_Iso14827AcceptType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827AcceptTypePresent_login:
		Dz1Thread_printf(Dz1T("login = ")); Dz1Str_dump(p->x.login, tab); 
		break;
	case Gitsn_Iso14827AcceptTypePresent_singleSubscription:
		Dz1Thread_printf(Dz1T("singleSubscription = ")); Dz1s32_dump(p->x.singleSubscription, tab); 
		break;
	case Gitsn_Iso14827AcceptTypePresent_registeredSubscription:
		Dz1Thread_printf(Dz1T("registeredSubscription = ")); Dz1u32_dump(&p->x.registeredSubscription, tab); 
		break;
	case Gitsn_Iso14827AcceptTypePresent_publication:
		Dz1Thread_printf(Dz1T("publication = ")); Dz1s32_dump(p->x.publication, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827AcceptType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Accept
Gitsn_Iso14827Accept *Gitsn_Iso14827Accept_new(u32_t pktNbr, 
											   Gitsn_Iso14827AcceptType *acceptType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Accept *__internal_ret = (Gitsn_Iso14827Accept *)Dz1Calloc(sizeof(Gitsn_Iso14827Accept), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Accept_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->pktNbr = pktNbr;
		__internal_ret->acceptType = acceptType;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Accept_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827Accept_copy(Gitsn_Iso14827Accept *dst, Gitsn_Iso14827Accept *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->acceptType && (dst->acceptType = Gitsn_Iso14827AcceptType_clone(src->acceptType, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->pktNbr = src->pktNbr;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Accept *Gitsn_Iso14827Accept_clone(Gitsn_Iso14827Accept *src, Dz1Error *err)
{
	Gitsn_Iso14827Accept *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827Accept *)Dz1Calloc(sizeof(Gitsn_Iso14827Accept), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Accept_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827Accept_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Accept_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827Accept_purge(Gitsn_Iso14827Accept *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827AcceptType_del(p->acceptType);
}

void Gitsn_Iso14827Accept_del(Gitsn_Iso14827Accept *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Accept_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827Accept_dump(Gitsn_Iso14827Accept *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("pktNbr = ")); Dz1u32_dump(&p->pktNbr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("acceptType.")); Gitsn_Iso14827AcceptType_dump(p->acceptType, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827Accept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectLogin
static struct Gitsn_Iso14827RejectLoginMapA
{
	str_t str;
	Gitsn_Iso14827RejectLogin v;
} Gitsn_Iso14827RejectLoginMapA[] =
{
	{ (char *)"other", Gitsn_Iso14827RejectLogin_other },
	{ (char *)"unknownDomainName", Gitsn_Iso14827RejectLogin_unknownDomainName },
	{ (char *)"accessDenied", Gitsn_Iso14827RejectLogin_accessDenied },
	{ (char *)"invalidPassword", Gitsn_Iso14827RejectLogin_invalidPassword },
	{ (char *)"timeoutTooSmall", Gitsn_Iso14827RejectLogin_timeoutTooSmall },
	{ (char *)"timeoutTooLarge", Gitsn_Iso14827RejectLogin_timeoutTooLarge },
	{ (char *)"heartbeatTooSmall", Gitsn_Iso14827RejectLogin_heartbeatTooSmall },
	{ (char *)"heartbeatTooLarge", Gitsn_Iso14827RejectLogin_heartbeatTooLarge },
	{ (char *)"sessionExist", Gitsn_Iso14827RejectLogin_sessionExist },
	{ (char *)"maxSessionReached", Gitsn_Iso14827RejectLogin_maxSessionReached },
	{ NULL, Gitsn_Iso14827RejectLogin_max }
};

str_t Gitsn_Iso14827RejectLoginStrA(Gitsn_Iso14827RejectLogin v)
{
	struct Gitsn_Iso14827RejectLoginMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectLoginMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectLogin Gitsn_Iso14827RejectLoginFromStrA(str_t str)
{
	struct Gitsn_Iso14827RejectLoginMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectLoginMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectLogin_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827RejectLoginMapW
{
	wstr_t str;
	Gitsn_Iso14827RejectLogin v;
} Gitsn_Iso14827RejectLoginMapW[] =
{
	{ (wchar_t *)L"other", Gitsn_Iso14827RejectLogin_other },
	{ (wchar_t *)L"unknownDomainName", Gitsn_Iso14827RejectLogin_unknownDomainName },
	{ (wchar_t *)L"accessDenied", Gitsn_Iso14827RejectLogin_accessDenied },
	{ (wchar_t *)L"invalidPassword", Gitsn_Iso14827RejectLogin_invalidPassword },
	{ (wchar_t *)L"timeoutTooSmall", Gitsn_Iso14827RejectLogin_timeoutTooSmall },
	{ (wchar_t *)L"timeoutTooLarge", Gitsn_Iso14827RejectLogin_timeoutTooLarge },
	{ (wchar_t *)L"heartbeatTooSmall", Gitsn_Iso14827RejectLogin_heartbeatTooSmall },
	{ (wchar_t *)L"heartbeatTooLarge", Gitsn_Iso14827RejectLogin_heartbeatTooLarge },
	{ (wchar_t *)L"sessionExist", Gitsn_Iso14827RejectLogin_sessionExist },
	{ (wchar_t *)L"maxSessionReached", Gitsn_Iso14827RejectLogin_maxSessionReached },
	{ NULL, Gitsn_Iso14827RejectLogin_max }
};

wstr_t Gitsn_Iso14827RejectLoginStrW(Gitsn_Iso14827RejectLogin v)
{
	struct Gitsn_Iso14827RejectLoginMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectLoginMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectLogin Gitsn_Iso14827RejectLoginFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827RejectLoginMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectLoginMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectLogin_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827RejectLogin *Gitsn_Iso14827RejectLogin_new(Gitsn_Iso14827RejectLogin *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RejectLogin *__internal_ret = (Gitsn_Iso14827RejectLogin *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectLogin), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827RejectLogin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectSubscription
static struct Gitsn_Iso14827RejectSubscriptionMapA
{
	str_t str;
	Gitsn_Iso14827RejectSubscription v;
} Gitsn_Iso14827RejectSubscriptionMapA[] =
{
	{ (char *)"other", Gitsn_Iso14827RejectSubscription_other },
	{ (char *)"unknownSubscriptionNbr", Gitsn_Iso14827RejectSubscription_unknownSubscriptionNbr },
	{ (char *)"invalidTimes", Gitsn_Iso14827RejectSubscription_invalidTimes },
	{ (char *)"frequencyTooSmall", Gitsn_Iso14827RejectSubscription_frequencyTooSmall },
	{ (char *)"frequencyTooLarge", Gitsn_Iso14827RejectSubscription_frequencyTooLarge },
	{ (char *)"invalidMode", Gitsn_Iso14827RejectSubscription_invalidMode },
	{ (char *)"publishFormatNotSupported", Gitsn_Iso14827RejectSubscription_publishFormatNotSupported },
	{ (char *)"unknownSubscriptionMsgId", Gitsn_Iso14827RejectSubscription_unknownSubscriptionMsgId },
	{ (char *)"invalidSubscriptionMsgId", Gitsn_Iso14827RejectSubscription_invalidSubscriptionMsgId },
	{ (char *)"invalidSubscriptionContent", Gitsn_Iso14827RejectSubscription_invalidSubscriptionContent },
	{ NULL, Gitsn_Iso14827RejectSubscription_max }
};

str_t Gitsn_Iso14827RejectSubscriptionStrA(Gitsn_Iso14827RejectSubscription v)
{
	struct Gitsn_Iso14827RejectSubscriptionMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectSubscriptionMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectSubscription Gitsn_Iso14827RejectSubscriptionFromStrA(str_t str)
{
	struct Gitsn_Iso14827RejectSubscriptionMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectSubscriptionMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectSubscription_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827RejectSubscriptionMapW
{
	wstr_t str;
	Gitsn_Iso14827RejectSubscription v;
} Gitsn_Iso14827RejectSubscriptionMapW[] =
{
	{ (wchar_t *)L"other", Gitsn_Iso14827RejectSubscription_other },
	{ (wchar_t *)L"unknownSubscriptionNbr", Gitsn_Iso14827RejectSubscription_unknownSubscriptionNbr },
	{ (wchar_t *)L"invalidTimes", Gitsn_Iso14827RejectSubscription_invalidTimes },
	{ (wchar_t *)L"frequencyTooSmall", Gitsn_Iso14827RejectSubscription_frequencyTooSmall },
	{ (wchar_t *)L"frequencyTooLarge", Gitsn_Iso14827RejectSubscription_frequencyTooLarge },
	{ (wchar_t *)L"invalidMode", Gitsn_Iso14827RejectSubscription_invalidMode },
	{ (wchar_t *)L"publishFormatNotSupported", Gitsn_Iso14827RejectSubscription_publishFormatNotSupported },
	{ (wchar_t *)L"unknownSubscriptionMsgId", Gitsn_Iso14827RejectSubscription_unknownSubscriptionMsgId },
	{ (wchar_t *)L"invalidSubscriptionMsgId", Gitsn_Iso14827RejectSubscription_invalidSubscriptionMsgId },
	{ (wchar_t *)L"invalidSubscriptionContent", Gitsn_Iso14827RejectSubscription_invalidSubscriptionContent },
	{ NULL, Gitsn_Iso14827RejectSubscription_max }
};

wstr_t Gitsn_Iso14827RejectSubscriptionStrW(Gitsn_Iso14827RejectSubscription v)
{
	struct Gitsn_Iso14827RejectSubscriptionMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectSubscriptionMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectSubscription Gitsn_Iso14827RejectSubscriptionFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827RejectSubscriptionMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectSubscriptionMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectSubscription_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827RejectSubscription *Gitsn_Iso14827RejectSubscription_new(Gitsn_Iso14827RejectSubscription *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RejectSubscription *__internal_ret = (Gitsn_Iso14827RejectSubscription *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectSubscription), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827RejectSubscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPublication
static struct Gitsn_Iso14827RejectPublicationMapA
{
	str_t str;
	Gitsn_Iso14827RejectPublication v;
} Gitsn_Iso14827RejectPublicationMapA[] =
{
	{ (char *)"other", Gitsn_Iso14827RejectPublication_other },
	{ (char *)"invalidPublishFormat", Gitsn_Iso14827RejectPublication_invalidPublishFormat },
	{ NULL, Gitsn_Iso14827RejectPublication_max }
};

str_t Gitsn_Iso14827RejectPublicationStrA(Gitsn_Iso14827RejectPublication v)
{
	struct Gitsn_Iso14827RejectPublicationMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectPublicationMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectPublication Gitsn_Iso14827RejectPublicationFromStrA(str_t str)
{
	struct Gitsn_Iso14827RejectPublicationMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectPublicationMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectPublication_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827RejectPublicationMapW
{
	wstr_t str;
	Gitsn_Iso14827RejectPublication v;
} Gitsn_Iso14827RejectPublicationMapW[] =
{
	{ (wchar_t *)L"other", Gitsn_Iso14827RejectPublication_other },
	{ (wchar_t *)L"invalidPublishFormat", Gitsn_Iso14827RejectPublication_invalidPublishFormat },
	{ NULL, Gitsn_Iso14827RejectPublication_max }
};

wstr_t Gitsn_Iso14827RejectPublicationStrW(Gitsn_Iso14827RejectPublication v)
{
	struct Gitsn_Iso14827RejectPublicationMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectPublicationMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectPublication Gitsn_Iso14827RejectPublicationFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827RejectPublicationMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectPublicationMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectPublication_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827RejectPublication *Gitsn_Iso14827RejectPublication_new(Gitsn_Iso14827RejectPublication *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RejectPublication *__internal_ret = (Gitsn_Iso14827RejectPublication *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectPublication), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827RejectPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPubDataReason
static struct Gitsn_Iso14827RejectPubDataReasonMapA
{
	str_t str;
	Gitsn_Iso14827RejectPubDataReason v;
} Gitsn_Iso14827RejectPubDataReasonMapA[] =
{
	{ (char *)"other", Gitsn_Iso14827RejectPubDataReason_other },
	{ (char *)"unknownSubscription", Gitsn_Iso14827RejectPubDataReason_unknownSubscription },
	{ (char *)"unknownPublicationNbr", Gitsn_Iso14827RejectPubDataReason_unknownPublicationNbr },
	{ (char *)"unknownPublicationMsgId", Gitsn_Iso14827RejectPubDataReason_unknownPublicationMsgId },
	{ (char *)"invalidPublicationMsgId", Gitsn_Iso14827RejectPubDataReason_invalidPublicationMsgId },
	{ (char *)"invalidPublicationMsgContent", Gitsn_Iso14827RejectPubDataReason_invalidPublicationMsgContent },
	{ (char *)"repeatedPublicationNbr", Gitsn_Iso14827RejectPubDataReason_repeatedPublicationNbr },
	{ NULL, Gitsn_Iso14827RejectPubDataReason_max }
};

str_t Gitsn_Iso14827RejectPubDataReasonStrA(Gitsn_Iso14827RejectPubDataReason v)
{
	struct Gitsn_Iso14827RejectPubDataReasonMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectPubDataReasonMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectPubDataReason Gitsn_Iso14827RejectPubDataReasonFromStrA(str_t str)
{
	struct Gitsn_Iso14827RejectPubDataReasonMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectPubDataReasonMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectPubDataReason_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827RejectPubDataReasonMapW
{
	wstr_t str;
	Gitsn_Iso14827RejectPubDataReason v;
} Gitsn_Iso14827RejectPubDataReasonMapW[] =
{
	{ (wchar_t *)L"other", Gitsn_Iso14827RejectPubDataReason_other },
	{ (wchar_t *)L"unknownSubscription", Gitsn_Iso14827RejectPubDataReason_unknownSubscription },
	{ (wchar_t *)L"unknownPublicationNbr", Gitsn_Iso14827RejectPubDataReason_unknownPublicationNbr },
	{ (wchar_t *)L"unknownPublicationMsgId", Gitsn_Iso14827RejectPubDataReason_unknownPublicationMsgId },
	{ (wchar_t *)L"invalidPublicationMsgId", Gitsn_Iso14827RejectPubDataReason_invalidPublicationMsgId },
	{ (wchar_t *)L"invalidPublicationMsgContent", Gitsn_Iso14827RejectPubDataReason_invalidPublicationMsgContent },
	{ (wchar_t *)L"repeatedPublicationNbr", Gitsn_Iso14827RejectPubDataReason_repeatedPublicationNbr },
	{ NULL, Gitsn_Iso14827RejectPubDataReason_max }
};

wstr_t Gitsn_Iso14827RejectPubDataReasonStrW(Gitsn_Iso14827RejectPubDataReason v)
{
	struct Gitsn_Iso14827RejectPubDataReasonMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectPubDataReasonMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectPubDataReason Gitsn_Iso14827RejectPubDataReasonFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827RejectPubDataReasonMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectPubDataReasonMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectPubDataReason_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827RejectPubDataReason *Gitsn_Iso14827RejectPubDataReason_new(Gitsn_Iso14827RejectPubDataReason *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RejectPubDataReason *__internal_ret = (Gitsn_Iso14827RejectPubDataReason *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectPubDataReason), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827RejectPubDataReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPubData
Gitsn_Iso14827RejectPubData *Gitsn_Iso14827RejectPubData_new(u32_t subSerial, 
															 u32_t pubSerial, 
															 Gitsn_Iso14827RejectPubDataReason reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RejectPubData *__internal_ret = (Gitsn_Iso14827RejectPubData *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectPubData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RejectPubData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->subSerial = subSerial;
		__internal_ret->pubSerial = pubSerial;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827RejectPubData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827RejectPubData_copy(Gitsn_Iso14827RejectPubData *dst, Gitsn_Iso14827RejectPubData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->subSerial = src->subSerial;
		dst->pubSerial = src->pubSerial;
		dst->reason = src->reason;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827RejectPubData *Gitsn_Iso14827RejectPubData_clone(Gitsn_Iso14827RejectPubData *src, Dz1Error *err)
{
	Gitsn_Iso14827RejectPubData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827RejectPubData *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectPubData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RejectPubData_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827RejectPubData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827RejectPubData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827RejectPubData_purge(Gitsn_Iso14827RejectPubData *p)
{
	if (p == NULL) return;
}

void Gitsn_Iso14827RejectPubData_del(Gitsn_Iso14827RejectPubData *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827RejectPubData_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827RejectPubData_dump(Gitsn_Iso14827RejectPubData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("subSerial = ")); Dz1u32_dump(&p->subSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pubSerial = ")); Dz1u32_dump(&p->pubSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Gitsn_Iso14827RejectPubDataReasonStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827RejectPubData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectTypePresent
static struct Gitsn_Iso14827RejectTypePresentMapA
{
	str_t str;
	Gitsn_Iso14827RejectTypePresent v;
} Gitsn_Iso14827RejectTypePresentMapA[] =
{
	{ (char *)"login", Gitsn_Iso14827RejectTypePresent_login },
	{ (char *)"subscription", Gitsn_Iso14827RejectTypePresent_subscription },
	{ (char *)"publication", Gitsn_Iso14827RejectTypePresent_publication },
	{ (char *)"pubData", Gitsn_Iso14827RejectTypePresent_pubData },
	{ NULL, Gitsn_Iso14827RejectTypePresent_max }
};

str_t Gitsn_Iso14827RejectTypePresentStrA(Gitsn_Iso14827RejectTypePresent v)
{
	struct Gitsn_Iso14827RejectTypePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectTypePresent Gitsn_Iso14827RejectTypePresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827RejectTypePresentMapA *i = NULL;
	for (i = Gitsn_Iso14827RejectTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827RejectTypePresentMapW
{
	wstr_t str;
	Gitsn_Iso14827RejectTypePresent v;
} Gitsn_Iso14827RejectTypePresentMapW[] =
{
	{ (wchar_t *)L"login", Gitsn_Iso14827RejectTypePresent_login },
	{ (wchar_t *)L"subscription", Gitsn_Iso14827RejectTypePresent_subscription },
	{ (wchar_t *)L"publication", Gitsn_Iso14827RejectTypePresent_publication },
	{ (wchar_t *)L"pubData", Gitsn_Iso14827RejectTypePresent_pubData },
	{ NULL, Gitsn_Iso14827RejectTypePresent_max }
};

wstr_t Gitsn_Iso14827RejectTypePresentStrW(Gitsn_Iso14827RejectTypePresent v)
{
	struct Gitsn_Iso14827RejectTypePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827RejectTypePresent Gitsn_Iso14827RejectTypePresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827RejectTypePresentMapW *i = NULL;
	for (i = Gitsn_Iso14827RejectTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827RejectTypePresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827RejectTypePresent *Gitsn_Iso14827RejectTypePresent_new(Gitsn_Iso14827RejectTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RejectTypePresent *__internal_ret = (Gitsn_Iso14827RejectTypePresent *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827RejectTypePresent_dump(Gitsn_Iso14827RejectTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827RejectTypePresentStr(*v));
}
// Gitsn_Iso14827RejectTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectType
Gitsn_Iso14827RejectType *Gitsn_Iso14827RejectType_new(Gitsn_Iso14827RejectTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827RejectType *ret = (Gitsn_Iso14827RejectType *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RejectType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827RejectTypePresent_login:
			// _U_enum_clone
			if (ptr != NULL) ret->x.login = *(Gitsn_Iso14827RejectLogin *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RejectTypePresent_subscription:
			// _U_enum_clone
			if (ptr != NULL) ret->x.subscription = *(Gitsn_Iso14827RejectSubscription *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RejectTypePresent_publication:
			// _U_enum_clone
			if (ptr != NULL) ret->x.publication = *(Gitsn_Iso14827RejectPublication *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RejectTypePresent_pubData:
			// _U_cst_clone
			if (ptr != NULL) ret->x.pubData = (Gitsn_Iso14827RejectPubData *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RejectTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827RejectType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827RejectType_copy(Gitsn_Iso14827RejectType *ret, Gitsn_Iso14827RejectType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827RejectTypePresent_login:
			// _U_enum_clone
			ret->x.login = src->x.login;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RejectTypePresent_subscription:
			// _U_enum_clone
			ret->x.subscription = src->x.subscription;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RejectTypePresent_publication:
			// _U_enum_clone
			ret->x.publication = src->x.publication;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827RejectTypePresent_pubData:
			// _U_cst_clone
			if (src->x.pubData && (ret->x.pubData = Gitsn_Iso14827RejectPubData_clone(src->x.pubData, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827RejectType *Gitsn_Iso14827RejectType_clone(Gitsn_Iso14827RejectType *src, Dz1Error *err)
{
	Gitsn_Iso14827RejectType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827RejectType *)Dz1Calloc(sizeof(Gitsn_Iso14827RejectType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RejectType_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827RejectType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827RejectType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827RejectType_purge(Gitsn_Iso14827RejectType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827RejectTypePresent_login:
		break;
	case Gitsn_Iso14827RejectTypePresent_subscription:
		break;
	case Gitsn_Iso14827RejectTypePresent_publication:
		break;
	case Gitsn_Iso14827RejectTypePresent_pubData:
		Gitsn_Iso14827RejectPubData_del(p->x.pubData);
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827RejectType_del(Gitsn_Iso14827RejectType *p)
{
	if (!p) return;
	Gitsn_Iso14827RejectType_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827RejectType_dump(Gitsn_Iso14827RejectType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827RejectTypePresent_login:
		Dz1Thread_printf(Dz1T("login = %s(%d)\n"), Gitsn_Iso14827RejectLoginStr(p->x.login), p->x.login);
		break;
	case Gitsn_Iso14827RejectTypePresent_subscription:
		Dz1Thread_printf(Dz1T("subscription = %s(%d)\n"), Gitsn_Iso14827RejectSubscriptionStr(p->x.subscription), p->x.subscription);
		break;
	case Gitsn_Iso14827RejectTypePresent_publication:
		Dz1Thread_printf(Dz1T("publication = %s(%d)\n"), Gitsn_Iso14827RejectPublicationStr(p->x.publication), p->x.publication);
		break;
	case Gitsn_Iso14827RejectTypePresent_pubData:
		Dz1Thread_printf(Dz1T("pubData = ")); Gitsn_Iso14827RejectPubData_dump(p->x.pubData, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827RejectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Reject
Gitsn_Iso14827Reject *Gitsn_Iso14827Reject_new(u32_t pktNbr, 
											   Gitsn_Iso14827RejectType *type, 
											   Gitsn_Iso14827SubscriptionType *altReq, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827Reject *__internal_ret = (Gitsn_Iso14827Reject *)Dz1Calloc(sizeof(Gitsn_Iso14827Reject), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Reject_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->pktNbr = pktNbr;
		__internal_ret->type = type;
		__internal_ret->altReq = altReq;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Reject_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Gitsn_Iso14827Reject_copy(Gitsn_Iso14827Reject *dst, Gitsn_Iso14827Reject *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->type && (dst->type = Gitsn_Iso14827RejectType_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else if (src->altReq && (dst->altReq = Gitsn_Iso14827SubscriptionType_clone(src->altReq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->pktNbr = src->pktNbr;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827Reject *Gitsn_Iso14827Reject_clone(Gitsn_Iso14827Reject *src, Dz1Error *err)
{
	Gitsn_Iso14827Reject *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Gitsn_Iso14827Reject *)Dz1Calloc(sizeof(Gitsn_Iso14827Reject), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Reject_delAndSetNull, (void *)&dst);
		if (Gitsn_Iso14827Reject_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827Reject_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Gitsn_Iso14827Reject_purge(Gitsn_Iso14827Reject *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827RejectType_del(p->type);
	Gitsn_Iso14827SubscriptionType_del(p->altReq);
}

void Gitsn_Iso14827Reject_del(Gitsn_Iso14827Reject *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827Reject_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827Reject_dump(Gitsn_Iso14827Reject *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("pktNbr = ")); Dz1u32_dump(&p->pktNbr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type.")); Gitsn_Iso14827RejectType_dump(p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("altReq.")); Gitsn_Iso14827SubscriptionType_dump(p->altReq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827Reject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PDUsPresent
static struct Gitsn_Iso14827PDUsPresentMapA
{
	str_t str;
	Gitsn_Iso14827PDUsPresent v;
} Gitsn_Iso14827PDUsPresentMapA[] =
{
	{ (char *)"initiate", Gitsn_Iso14827PDUsPresent_initiate },
	{ (char *)"login", Gitsn_Iso14827PDUsPresent_login },
	{ (char *)"fred", Gitsn_Iso14827PDUsPresent_fred },
	{ (char *)"term", Gitsn_Iso14827PDUsPresent_term },
	{ (char *)"logout", Gitsn_Iso14827PDUsPresent_logout },
	{ (char *)"subscription", Gitsn_Iso14827PDUsPresent_subscription },
	{ (char *)"publication", Gitsn_Iso14827PDUsPresent_publication },
	{ (char *)"transferDone", Gitsn_Iso14827PDUsPresent_transferDone },
	{ (char *)"ack", Gitsn_Iso14827PDUsPresent_ack },
	{ (char *)"nak", Gitsn_Iso14827PDUsPresent_nak },
	{ NULL, Gitsn_Iso14827PDUsPresent_max }
};

str_t Gitsn_Iso14827PDUsPresentStrA(Gitsn_Iso14827PDUsPresent v)
{
	struct Gitsn_Iso14827PDUsPresentMapA *i = NULL;
	for (i = Gitsn_Iso14827PDUsPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827PDUsPresent Gitsn_Iso14827PDUsPresentFromStrA(str_t str)
{
	struct Gitsn_Iso14827PDUsPresentMapA *i = NULL;
	for (i = Gitsn_Iso14827PDUsPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827PDUsPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827PDUsPresentMapW
{
	wstr_t str;
	Gitsn_Iso14827PDUsPresent v;
} Gitsn_Iso14827PDUsPresentMapW[] =
{
	{ (wchar_t *)L"initiate", Gitsn_Iso14827PDUsPresent_initiate },
	{ (wchar_t *)L"login", Gitsn_Iso14827PDUsPresent_login },
	{ (wchar_t *)L"fred", Gitsn_Iso14827PDUsPresent_fred },
	{ (wchar_t *)L"term", Gitsn_Iso14827PDUsPresent_term },
	{ (wchar_t *)L"logout", Gitsn_Iso14827PDUsPresent_logout },
	{ (wchar_t *)L"subscription", Gitsn_Iso14827PDUsPresent_subscription },
	{ (wchar_t *)L"publication", Gitsn_Iso14827PDUsPresent_publication },
	{ (wchar_t *)L"transferDone", Gitsn_Iso14827PDUsPresent_transferDone },
	{ (wchar_t *)L"ack", Gitsn_Iso14827PDUsPresent_ack },
	{ (wchar_t *)L"nak", Gitsn_Iso14827PDUsPresent_nak },
	{ NULL, Gitsn_Iso14827PDUsPresent_max }
};

wstr_t Gitsn_Iso14827PDUsPresentStrW(Gitsn_Iso14827PDUsPresent v)
{
	struct Gitsn_Iso14827PDUsPresentMapW *i = NULL;
	for (i = Gitsn_Iso14827PDUsPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827PDUsPresent Gitsn_Iso14827PDUsPresentFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827PDUsPresentMapW *i = NULL;
	for (i = Gitsn_Iso14827PDUsPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827PDUsPresent_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827PDUsPresent *Gitsn_Iso14827PDUsPresent_new(Gitsn_Iso14827PDUsPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PDUsPresent *__internal_ret = (Gitsn_Iso14827PDUsPresent *)Dz1Calloc(sizeof(Gitsn_Iso14827PDUsPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Gitsn_Iso14827PDUsPresent_dump(Gitsn_Iso14827PDUsPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Gitsn_Iso14827PDUsPresentStr(*v));
}
// Gitsn_Iso14827PDUsPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PDUs
Gitsn_Iso14827PDUs *Gitsn_Iso14827PDUs_new(Gitsn_Iso14827PDUsPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827PDUs *ret = (Gitsn_Iso14827PDUs *)Dz1Calloc(sizeof(Gitsn_Iso14827PDUs), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PDUs_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Gitsn_Iso14827PDUsPresent_initiate:
			// _U_cst_clone
			if (ptr != NULL) ret->x.initiate = (Gitsn_Iso14827Initiate *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_login:
			// _U_cst_clone
			if (ptr != NULL) ret->x.login = (Gitsn_Iso14827Login *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_fred:
			// _U_prim_clone
			if (ptr != NULL) ret->x.fred = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_term:
			// _U_enum_clone
			if (ptr != NULL) ret->x.term = *(Gitsn_Iso14827Terminate *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_logout:
			// _U_enum_clone
			if (ptr != NULL) ret->x.logout = *(Gitsn_Iso14827Logout *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_subscription:
			// _U_cst_clone
			if (ptr != NULL) ret->x.subscription = (Gitsn_Iso14827Subscription *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_publication:
			// _U_cst_clone
			if (ptr != NULL) ret->x.publication = (Gitsn_Iso14827Publication *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_transferDone:
			// _U_cst_clone
			if (ptr != NULL) ret->x.transferDone = (Gitsn_Iso14827TransferDone *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_ack:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ack = (Gitsn_Iso14827Accept *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_nak:
			// _U_cst_clone
			if (ptr != NULL) ret->x.nak = (Gitsn_Iso14827Reject *)ptr;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PDUs_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Gitsn_Iso14827PDUs_copy(Gitsn_Iso14827PDUs *ret, Gitsn_Iso14827PDUs *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Gitsn_Iso14827PDUsPresent_initiate:
			// _U_cst_clone
			if (src->x.initiate && (ret->x.initiate = Gitsn_Iso14827Initiate_clone(src->x.initiate, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827PDUsPresent_login:
			// _U_cst_clone
			if (src->x.login && (ret->x.login = Gitsn_Iso14827Login_clone(src->x.login, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827PDUsPresent_fred:
			// _U_prim_clone
			ret->x.fred = src->x.fred;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_term:
			// _U_enum_clone
			ret->x.term = src->x.term;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_logout:
			// _U_enum_clone
			ret->x.logout = src->x.logout;
			ERR_CLEAR(errp);
			break;
		case Gitsn_Iso14827PDUsPresent_subscription:
			// _U_cst_clone
			if (src->x.subscription && (ret->x.subscription = Gitsn_Iso14827Subscription_clone(src->x.subscription, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827PDUsPresent_publication:
			// _U_cst_clone
			if (src->x.publication && (ret->x.publication = Gitsn_Iso14827Publication_clone(src->x.publication, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827PDUsPresent_transferDone:
			// _U_cst_clone
			if (src->x.transferDone && (ret->x.transferDone = Gitsn_Iso14827TransferDone_clone(src->x.transferDone, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827PDUsPresent_ack:
			// _U_cst_clone
			if (src->x.ack && (ret->x.ack = Gitsn_Iso14827Accept_clone(src->x.ack, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Gitsn_Iso14827PDUsPresent_nak:
			// _U_cst_clone
			if (src->x.nak && (ret->x.nak = Gitsn_Iso14827Reject_clone(src->x.nak, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Gitsn_Iso14827PDUs *Gitsn_Iso14827PDUs_clone(Gitsn_Iso14827PDUs *src, Dz1Error *err)
{
	Gitsn_Iso14827PDUs *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Gitsn_Iso14827PDUs *)Dz1Calloc(sizeof(Gitsn_Iso14827PDUs), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PDUs_delAndSetNull, (void *)&ret);
		if (Gitsn_Iso14827PDUs_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827PDUs_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Gitsn_Iso14827PDUs_purge(Gitsn_Iso14827PDUs *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Gitsn_Iso14827PDUsPresent_initiate:
		Gitsn_Iso14827Initiate_del(p->x.initiate);
		break;
	case Gitsn_Iso14827PDUsPresent_login:
		Gitsn_Iso14827Login_del(p->x.login);
		break;
	case Gitsn_Iso14827PDUsPresent_fred:
		break;
	case Gitsn_Iso14827PDUsPresent_term:
		break;
	case Gitsn_Iso14827PDUsPresent_logout:
		break;
	case Gitsn_Iso14827PDUsPresent_subscription:
		Gitsn_Iso14827Subscription_del(p->x.subscription);
		break;
	case Gitsn_Iso14827PDUsPresent_publication:
		Gitsn_Iso14827Publication_del(p->x.publication);
		break;
	case Gitsn_Iso14827PDUsPresent_transferDone:
		Gitsn_Iso14827TransferDone_del(p->x.transferDone);
		break;
	case Gitsn_Iso14827PDUsPresent_ack:
		Gitsn_Iso14827Accept_del(p->x.ack);
		break;
	case Gitsn_Iso14827PDUsPresent_nak:
		Gitsn_Iso14827Reject_del(p->x.nak);
		break;
	default:
		break;
	}
}

void Gitsn_Iso14827PDUs_del(Gitsn_Iso14827PDUs *p)
{
	if (!p) return;
	Gitsn_Iso14827PDUs_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827PDUs_dump(Gitsn_Iso14827PDUs *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Gitsn_Iso14827PDUsPresent_initiate:
		Dz1Thread_printf(Dz1T("initiate = ")); Gitsn_Iso14827Initiate_dump(p->x.initiate, tab); 
		break;
	case Gitsn_Iso14827PDUsPresent_login:
		Dz1Thread_printf(Dz1T("login = ")); Gitsn_Iso14827Login_dump(p->x.login, tab); 
		break;
	case Gitsn_Iso14827PDUsPresent_fred:
		Dz1Thread_printf(Dz1T("fred = ")); Dz1u32_dump(&p->x.fred, tab); 
		break;
	case Gitsn_Iso14827PDUsPresent_term:
		Dz1Thread_printf(Dz1T("term = %s(%d)\n"), Gitsn_Iso14827TerminateStr(p->x.term), p->x.term);
		break;
	case Gitsn_Iso14827PDUsPresent_logout:
		Dz1Thread_printf(Dz1T("logout = %s(%d)\n"), Gitsn_Iso14827LogoutStr(p->x.logout), p->x.logout);
		break;
	case Gitsn_Iso14827PDUsPresent_subscription:
		Dz1Thread_printf(Dz1T("subscription = ")); Gitsn_Iso14827Subscription_dump(p->x.subscription, tab); 
		break;
	case Gitsn_Iso14827PDUsPresent_publication:
		Dz1Thread_printf(Dz1T("publication = ")); Gitsn_Iso14827Publication_dump(p->x.publication, tab); 
		break;
	case Gitsn_Iso14827PDUsPresent_transferDone:
		Dz1Thread_printf(Dz1T("transferDone = ")); Gitsn_Iso14827TransferDone_dump(p->x.transferDone, tab); 
		break;
	case Gitsn_Iso14827PDUsPresent_ack:
		Dz1Thread_printf(Dz1T("ack = ")); Gitsn_Iso14827Accept_dump(p->x.ack, tab); 
		break;
	case Gitsn_Iso14827PDUsPresent_nak:
		Dz1Thread_printf(Dz1T("nak = ")); Gitsn_Iso14827Reject_dump(p->x.nak, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Gitsn_Iso14827PDUs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827C2CAuthMsg
Gitsn_Iso14827C2CAuthMsg *Gitsn_Iso14827C2CAuthMsg_new(Dz1Str authInfo, 
													   u32_t pktNbr, 
													   s32_t priority, 
													   Gitsn_Iso14827HdrOpt *hdrOpt, 
													   Gitsn_Iso14827PDUs *pdu, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827C2CAuthMsg *__internal_ret = (Gitsn_Iso14827C2CAuthMsg *)Dz1Calloc(sizeof(Gitsn_Iso14827C2CAuthMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827C2CAuthMsg_delAndSetNull, (void *)&__internal_ret);
		
		if (authInfo && (__internal_ret->authInfo = Dz1Str_clone(authInfo, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->pktNbr = pktNbr;
			__internal_ret->priority = priority;
			__internal_ret->hdrOpt = hdrOpt;
			__internal_ret->pdu = pdu;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827C2CAuthMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Gitsn_Iso14827C2CAuthMsg_purge(Gitsn_Iso14827C2CAuthMsg *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->authInfo);
	Gitsn_Iso14827HdrOpt_del(p->hdrOpt);
	Gitsn_Iso14827PDUs_del(p->pdu);
}

void Gitsn_Iso14827C2CAuthMsg_del(Gitsn_Iso14827C2CAuthMsg *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827C2CAuthMsg_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827C2CAuthMsg_dump(Gitsn_Iso14827C2CAuthMsg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("authInfo = ")); Dz1Str_dump(p->authInfo, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pktNbr = ")); Dz1u32_dump(&p->pktNbr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("priority = ")); Dz1s32_dump(&p->priority, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("hdrOpt = ")); Gitsn_Iso14827HdrOpt_dump(p->hdrOpt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pdu.")); Gitsn_Iso14827PDUs_dump(p->pdu, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Gitsn_Iso14827C2CAuthMsg_cmp(Gitsn_Iso14827C2CAuthMsg *a, Gitsn_Iso14827C2CAuthMsg *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->pktNbr, &b->pktNbr)) != 0) { }
	return ret;
}
// Gitsn_Iso14827C2CAuthMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827DatexVersionNumber
static struct Gitsn_Iso14827DatexVersionNumberMapA
{
	str_t str;
	Gitsn_Iso14827DatexVersionNumber v;
} Gitsn_Iso14827DatexVersionNumberMapA[] =
{
	{ (char *)"experimental", Gitsn_Iso14827DatexVersionNumber_experimental },
	{ (char *)"version1", Gitsn_Iso14827DatexVersionNumber_version1 },
	{ NULL, Gitsn_Iso14827DatexVersionNumber_max }
};

str_t Gitsn_Iso14827DatexVersionNumberStrA(Gitsn_Iso14827DatexVersionNumber v)
{
	struct Gitsn_Iso14827DatexVersionNumberMapA *i = NULL;
	for (i = Gitsn_Iso14827DatexVersionNumberMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827DatexVersionNumber Gitsn_Iso14827DatexVersionNumberFromStrA(str_t str)
{
	struct Gitsn_Iso14827DatexVersionNumberMapA *i = NULL;
	for (i = Gitsn_Iso14827DatexVersionNumberMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827DatexVersionNumber_max;
}
#ifndef UNIX_SYSTEM
static struct Gitsn_Iso14827DatexVersionNumberMapW
{
	wstr_t str;
	Gitsn_Iso14827DatexVersionNumber v;
} Gitsn_Iso14827DatexVersionNumberMapW[] =
{
	{ (wchar_t *)L"experimental", Gitsn_Iso14827DatexVersionNumber_experimental },
	{ (wchar_t *)L"version1", Gitsn_Iso14827DatexVersionNumber_version1 },
	{ NULL, Gitsn_Iso14827DatexVersionNumber_max }
};

wstr_t Gitsn_Iso14827DatexVersionNumberStrW(Gitsn_Iso14827DatexVersionNumber v)
{
	struct Gitsn_Iso14827DatexVersionNumberMapW *i = NULL;
	for (i = Gitsn_Iso14827DatexVersionNumberMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Gitsn_Iso14827DatexVersionNumber Gitsn_Iso14827DatexVersionNumberFromStrW(wstr_t str)
{
	struct Gitsn_Iso14827DatexVersionNumberMapW *i = NULL;
	for (i = Gitsn_Iso14827DatexVersionNumberMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Gitsn_Iso14827DatexVersionNumber_max;
}
#endif // UNIX_SYSTEM

Gitsn_Iso14827DatexVersionNumber *Gitsn_Iso14827DatexVersionNumber_new(Gitsn_Iso14827DatexVersionNumber *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827DatexVersionNumber *__internal_ret = (Gitsn_Iso14827DatexVersionNumber *)Dz1Calloc(sizeof(Gitsn_Iso14827DatexVersionNumber), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Gitsn_Iso14827DatexVersionNumber
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827DatexDataPacket
Gitsn_Iso14827DatexDataPacket *Gitsn_Iso14827DatexDataPacket_new(Gitsn_Iso14827DatexVersionNumber version, 
																 Dz1Asn1OctetStr *data, 
																 u16_t crc16, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Gitsn_Iso14827DatexDataPacket *__internal_ret = (Gitsn_Iso14827DatexDataPacket *)Dz1Calloc(sizeof(Gitsn_Iso14827DatexDataPacket), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827DatexDataPacket_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->version = version;
		__internal_ret->data = data;
		__internal_ret->crc16 = crc16;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Gitsn_Iso14827DatexDataPacket_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Gitsn_Iso14827DatexDataPacket_purge(Gitsn_Iso14827DatexDataPacket *p)
{
	if (p == NULL) return;
	Dz1Asn1OctetStr_del(p->data);
}

void Gitsn_Iso14827DatexDataPacket_del(Gitsn_Iso14827DatexDataPacket *p)
{
	if (p == NULL) return;
	Gitsn_Iso14827DatexDataPacket_purge(p);
	Dz1Free(p);
}

void Gitsn_Iso14827DatexDataPacket_dump(Gitsn_Iso14827DatexDataPacket *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("version = %s(%d)\n"), Gitsn_Iso14827DatexVersionNumberStr(p->version), p->version);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Asn1OctetStr_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("crc16 = ")); Dz1u16_dump(&p->crc16, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Gitsn_Iso14827DatexDataPacket
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypeRegPresent
static struct SubscribeSpecTypeRegPresentMapA
{
	str_t str;
	SubscribeSpecTypeRegPresent v;
} SubscribeSpecTypeRegPresentMapA[] =
{
	{ (char *)"continuous", SubscribeSpecTypeRegPresent_continuous },
	{ (char *)"daily", SubscribeSpecTypeRegPresent_daily },
	{ NULL, SubscribeSpecTypeRegPresent_max }
};

str_t SubscribeSpecTypeRegPresentStrA(SubscribeSpecTypeRegPresent v)
{
	struct SubscribeSpecTypeRegPresentMapA *i = NULL;
	for (i = SubscribeSpecTypeRegPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

SubscribeSpecTypeRegPresent SubscribeSpecTypeRegPresentFromStrA(str_t str)
{
	struct SubscribeSpecTypeRegPresentMapA *i = NULL;
	for (i = SubscribeSpecTypeRegPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return SubscribeSpecTypeRegPresent_max;
}
#ifndef UNIX_SYSTEM
static struct SubscribeSpecTypeRegPresentMapW
{
	wstr_t str;
	SubscribeSpecTypeRegPresent v;
} SubscribeSpecTypeRegPresentMapW[] =
{
	{ (wchar_t *)L"continuous", SubscribeSpecTypeRegPresent_continuous },
	{ (wchar_t *)L"daily", SubscribeSpecTypeRegPresent_daily },
	{ NULL, SubscribeSpecTypeRegPresent_max }
};

wstr_t SubscribeSpecTypeRegPresentStrW(SubscribeSpecTypeRegPresent v)
{
	struct SubscribeSpecTypeRegPresentMapW *i = NULL;
	for (i = SubscribeSpecTypeRegPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

SubscribeSpecTypeRegPresent SubscribeSpecTypeRegPresentFromStrW(wstr_t str)
{
	struct SubscribeSpecTypeRegPresentMapW *i = NULL;
	for (i = SubscribeSpecTypeRegPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return SubscribeSpecTypeRegPresent_max;
}
#endif // UNIX_SYSTEM

SubscribeSpecTypeRegPresent *SubscribeSpecTypeRegPresent_new(SubscribeSpecTypeRegPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecTypeRegPresent *__internal_ret = (SubscribeSpecTypeRegPresent *)Dz1Calloc(sizeof(SubscribeSpecTypeRegPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void SubscribeSpecTypeRegPresent_dump(SubscribeSpecTypeRegPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), SubscribeSpecTypeRegPresentStr(*v));
}
// SubscribeSpecTypeRegPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypeReg
SubscribeSpecTypeReg *SubscribeSpecTypeReg_new(SubscribeSpecTypeRegPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecTypeReg *ret = (SubscribeSpecTypeReg *)Dz1Calloc(sizeof(SubscribeSpecTypeReg), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SubscribeSpecTypeReg_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case SubscribeSpecTypeRegPresent_continuous:
			// _U_cst_clone
			if (ptr != NULL) ret->x.continuous = (Iso14827RegisteredContinuous *)ptr;
			ERR_CLEAR(errp);
			break;
		case SubscribeSpecTypeRegPresent_daily:
			// _U_cst_clone
			if (ptr != NULL) ret->x.daily = (Iso14827RegisteredDaily *)ptr;
			ERR_CLEAR(errp);
			break;
		case SubscribeSpecTypeRegPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecTypeReg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t SubscribeSpecTypeReg_copy(SubscribeSpecTypeReg *ret, SubscribeSpecTypeReg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case SubscribeSpecTypeRegPresent_continuous:
			// _U_cst_clone
			if (src->x.continuous && (ret->x.continuous = Iso14827RegisteredContinuous_clone(src->x.continuous, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case SubscribeSpecTypeRegPresent_daily:
			// _U_cst_clone
			if (src->x.daily && (ret->x.daily = Iso14827RegisteredDaily_clone(src->x.daily, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SubscribeSpecTypeReg *SubscribeSpecTypeReg_clone(SubscribeSpecTypeReg *src, Dz1Error *err)
{
	SubscribeSpecTypeReg *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (SubscribeSpecTypeReg *)Dz1Calloc(sizeof(SubscribeSpecTypeReg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SubscribeSpecTypeReg_delAndSetNull, (void *)&ret);
		if (SubscribeSpecTypeReg_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecTypeReg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void SubscribeSpecTypeReg_purge(SubscribeSpecTypeReg *p)
{
	if (!p) return;
	switch(p->present)
	{
	case SubscribeSpecTypeRegPresent_continuous:
		Iso14827RegisteredContinuous_del(p->x.continuous);
		break;
	case SubscribeSpecTypeRegPresent_daily:
		Iso14827RegisteredDaily_del(p->x.daily);
		break;
	default:
		break;
	}
}

void SubscribeSpecTypeReg_del(SubscribeSpecTypeReg *p)
{
	if (!p) return;
	SubscribeSpecTypeReg_purge(p);
	Dz1Free(p);
}

void SubscribeSpecTypeReg_dump(SubscribeSpecTypeReg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case SubscribeSpecTypeRegPresent_continuous:
		Dz1Thread_printf(Dz1T("continuous = ")); Iso14827RegisteredContinuous_dump(p->x.continuous, tab); 
		break;
	case SubscribeSpecTypeRegPresent_daily:
		Dz1Thread_printf(Dz1T("daily = ")); Iso14827RegisteredDaily_dump(p->x.daily, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// SubscribeSpecTypeReg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypeRegistered
SubscribeSpecTypeRegistered *SubscribeSpecTypeRegistered_new(bool_t is_periodic, 
															 SubscribeSpecTypeReg *reg_info, 
															 Iso14827SubscriptionCancel when_cancel, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecTypeRegistered *__internal_ret = (SubscribeSpecTypeRegistered *)Dz1Calloc(sizeof(SubscribeSpecTypeRegistered), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SubscribeSpecTypeRegistered_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->is_periodic = is_periodic;
		__internal_ret->reg_info = reg_info;
		__internal_ret->when_cancel = when_cancel;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecTypeRegistered_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SubscribeSpecTypeRegistered_copy(SubscribeSpecTypeRegistered *dst, SubscribeSpecTypeRegistered *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->reg_info && (dst->reg_info = SubscribeSpecTypeReg_clone(src->reg_info, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->is_periodic = src->is_periodic;
		dst->when_cancel = src->when_cancel;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SubscribeSpecTypeRegistered *SubscribeSpecTypeRegistered_clone(SubscribeSpecTypeRegistered *src, Dz1Error *err)
{
	SubscribeSpecTypeRegistered *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SubscribeSpecTypeRegistered *)Dz1Calloc(sizeof(SubscribeSpecTypeRegistered), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SubscribeSpecTypeRegistered_delAndSetNull, (void *)&dst);
		if (SubscribeSpecTypeRegistered_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecTypeRegistered_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SubscribeSpecTypeRegistered_purge(SubscribeSpecTypeRegistered *p)
{
	if (p == NULL) return;
	SubscribeSpecTypeReg_del(p->reg_info);
}

void SubscribeSpecTypeRegistered_del(SubscribeSpecTypeRegistered *p)
{
	if (p == NULL) return;
	SubscribeSpecTypeRegistered_purge(p);
	Dz1Free(p);
}

void SubscribeSpecTypeRegistered_dump(SubscribeSpecTypeRegistered *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("is_periodic = ")); Dz1Bool_dump(&p->is_periodic, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reg_info.")); SubscribeSpecTypeReg_dump(p->reg_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("when_cancel = %s(%d)\n"), Iso14827SubscriptionCancelStr(p->when_cancel), p->when_cancel);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SubscribeSpecTypeRegistered
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypePresent
static struct SubscribeSpecTypePresentMapA
{
	str_t str;
	SubscribeSpecTypePresent v;
} SubscribeSpecTypePresentMapA[] =
{
	{ (char *)"single", SubscribeSpecTypePresent_single },
	{ (char *)"registered", SubscribeSpecTypePresent_registered },
	{ NULL, SubscribeSpecTypePresent_max }
};

str_t SubscribeSpecTypePresentStrA(SubscribeSpecTypePresent v)
{
	struct SubscribeSpecTypePresentMapA *i = NULL;
	for (i = SubscribeSpecTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

SubscribeSpecTypePresent SubscribeSpecTypePresentFromStrA(str_t str)
{
	struct SubscribeSpecTypePresentMapA *i = NULL;
	for (i = SubscribeSpecTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return SubscribeSpecTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct SubscribeSpecTypePresentMapW
{
	wstr_t str;
	SubscribeSpecTypePresent v;
} SubscribeSpecTypePresentMapW[] =
{
	{ (wchar_t *)L"single", SubscribeSpecTypePresent_single },
	{ (wchar_t *)L"registered", SubscribeSpecTypePresent_registered },
	{ NULL, SubscribeSpecTypePresent_max }
};

wstr_t SubscribeSpecTypePresentStrW(SubscribeSpecTypePresent v)
{
	struct SubscribeSpecTypePresentMapW *i = NULL;
	for (i = SubscribeSpecTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

SubscribeSpecTypePresent SubscribeSpecTypePresentFromStrW(wstr_t str)
{
	struct SubscribeSpecTypePresentMapW *i = NULL;
	for (i = SubscribeSpecTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return SubscribeSpecTypePresent_max;
}
#endif // UNIX_SYSTEM

SubscribeSpecTypePresent *SubscribeSpecTypePresent_new(SubscribeSpecTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecTypePresent *__internal_ret = (SubscribeSpecTypePresent *)Dz1Calloc(sizeof(SubscribeSpecTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void SubscribeSpecTypePresent_dump(SubscribeSpecTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), SubscribeSpecTypePresentStr(*v));
}
// SubscribeSpecTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecType
SubscribeSpecType *SubscribeSpecType_new(SubscribeSpecTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecType *ret = (SubscribeSpecType *)Dz1Calloc(sizeof(SubscribeSpecType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SubscribeSpecType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case SubscribeSpecTypePresent_single:
			// _U_prim_clone
			if (ptr != NULL) ret->x.single = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case SubscribeSpecTypePresent_registered:
			// _U_cst_clone
			if (ptr != NULL) ret->x.registered = (SubscribeSpecTypeRegistered *)ptr;
			ERR_CLEAR(errp);
			break;
		case SubscribeSpecTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t SubscribeSpecType_copy(SubscribeSpecType *ret, SubscribeSpecType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case SubscribeSpecTypePresent_single:
			// _U_prim_clone
			ret->x.single = src->x.single;
			ERR_CLEAR(errp);
			break;
		case SubscribeSpecTypePresent_registered:
			// _U_cst_clone
			if (src->x.registered && (ret->x.registered = SubscribeSpecTypeRegistered_clone(src->x.registered, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SubscribeSpecType *SubscribeSpecType_clone(SubscribeSpecType *src, Dz1Error *err)
{
	SubscribeSpecType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (SubscribeSpecType *)Dz1Calloc(sizeof(SubscribeSpecType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SubscribeSpecType_delAndSetNull, (void *)&ret);
		if (SubscribeSpecType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void SubscribeSpecType_purge(SubscribeSpecType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case SubscribeSpecTypePresent_single:
		break;
	case SubscribeSpecTypePresent_registered:
		SubscribeSpecTypeRegistered_del(p->x.registered);
		break;
	default:
		break;
	}
}

void SubscribeSpecType_del(SubscribeSpecType *p)
{
	if (!p) return;
	SubscribeSpecType_purge(p);
	Dz1Free(p);
}

void SubscribeSpecType_dump(SubscribeSpecType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case SubscribeSpecTypePresent_single:
		Dz1Thread_printf(Dz1T("single = ")); Dz1u32_dump(&p->x.single, tab); 
		break;
	case SubscribeSpecTypePresent_registered:
		Dz1Thread_printf(Dz1T("registered = ")); SubscribeSpecTypeRegistered_dump(p->x.registered, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// SubscribeSpecType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecEntry
SubscribeSpecEntry *SubscribeSpecEntry_new(Dz1Str oid, 
										   u8_t priority, 
										   SubscribeSpecType *type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecEntry *__internal_ret = (SubscribeSpecEntry *)Dz1Calloc(sizeof(SubscribeSpecEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (oid && (__internal_ret->oid = Dz1Str_clone(oid, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->priority = priority;
			__internal_ret->type = type;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SubscribeSpecEntry_copy(SubscribeSpecEntry *dst, SubscribeSpecEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->oid && (dst->oid = Dz1Str_clone(src->oid, errp)) == NULL) ERR_OUT(errp);
	else if (src->type && (dst->type = SubscribeSpecType_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->priority = src->priority;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SubscribeSpecEntry *SubscribeSpecEntry_clone(SubscribeSpecEntry *src, Dz1Error *err)
{
	SubscribeSpecEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SubscribeSpecEntry *)Dz1Calloc(sizeof(SubscribeSpecEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void *)&dst);
		if (SubscribeSpecEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SubscribeSpecEntry_purge(SubscribeSpecEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->oid);
	SubscribeSpecType_del(p->type);
}

void SubscribeSpecEntry_del(SubscribeSpecEntry *p)
{
	if (p == NULL) return;
	SubscribeSpecEntry_purge(p);
	Dz1Free(p);
}

int SubscribeSpecEntry_cmp(SubscribeSpecEntry *a, SubscribeSpecEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->oid == NULL && b->oid == NULL) ret = 0;
	else if (a->oid == NULL /*&& b->oid != NULL*/) ret = -1;
	else if (/*a->oid != NULL &&*/ b->oid == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->oid, b->oid)) != 0) { }
	return ret;
}
// SubscribeSpecEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecList
static Dz1Error SubscribeSpecList_add(SubscribeSpecList *p, SubscribeSpecEntry *data)
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

static bool_t SubscribeSpecList_remove(SubscribeSpecList *p, SubscribeSpecEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static SubscribeSpecEntry *SubscribeSpecList_extract(SubscribeSpecList *p, SubscribeSpecEntry *key)
{
	return (SubscribeSpecEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct SubscribeSpecListMkArrArg
{
	SubscribeSpecEntry **arr;
	unsigned int idx;
} SubscribeSpecListMkArrArg;

static Dz1Error _SubscribeSpecList_get_array(void *ptr, SubscribeSpecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	SubscribeSpecListMkArrArg *arg = (SubscribeSpecListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static SubscribeSpecEntry **SubscribeSpecList_get_array(SubscribeSpecList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	SubscribeSpecEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (SubscribeSpecEntry **)Dz1Calloc(sizeof(SubscribeSpecEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		SubscribeSpecListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _SubscribeSpecList_get_array, (void *)&arg);
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

static Dz1Error SubscribeSpecList_travelForward(SubscribeSpecList *p, Dz1Error (*func)(void *ptr, SubscribeSpecEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error SubscribeSpecList_travelBackward(SubscribeSpecList *p, Dz1Error (*func)(void *ptr, SubscribeSpecEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static SubscribeSpecEntry *SubscribeSpecList_find(SubscribeSpecList *p, SubscribeSpecEntry *key)
{
	return (SubscribeSpecEntry *)Dz1AATree_find(p->storage, key);
}

static SubscribeSpecEntry *SubscribeSpecList_getHead(SubscribeSpecList *p)
{
	return (SubscribeSpecEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int SubscribeSpecList_count(SubscribeSpecList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

SubscribeSpecList *SubscribeSpecList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecList *ret = (SubscribeSpecList *)Dz1Calloc(sizeof(SubscribeSpecList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SubscribeSpecList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)SubscribeSpecEntry_cmp,
				(Dz1DelFunc)SubscribeSpecEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = SubscribeSpecList_count;
			ret->travel = SubscribeSpecList_travelForward;
			ret->travelForward = SubscribeSpecList_travelForward;
			ret->travelBackward = SubscribeSpecList_travelBackward;
			ret->get_array = SubscribeSpecList_get_array;
			ret->add = SubscribeSpecList_add;
			ret->remove = SubscribeSpecList_remove;
			ret->find = SubscribeSpecList_find;
			ret->extract = SubscribeSpecList_extract;
			ret->getHead = SubscribeSpecList_getHead;
			ret->cmp = SubscribeSpecEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _SubscribeSpecList_clone(void *ptr, SubscribeSpecEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	SubscribeSpecList *p = (SubscribeSpecList *)ptr;
	SubscribeSpecEntry *cloned = SubscribeSpecEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

SubscribeSpecList *SubscribeSpecList_clone(SubscribeSpecList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = SubscribeSpecList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SubscribeSpecList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_SubscribeSpecList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void SubscribeSpecList_purge(SubscribeSpecList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void SubscribeSpecList_del(SubscribeSpecList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _SubscribeSpecList_dump(void *ptr, SubscribeSpecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); SubscribeSpecEntry_dump(p, tab);
	return err;
}

void SubscribeSpecList_dump(SubscribeSpecList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _SubscribeSpecList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SubscribeSpecList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ConfTestSocketAddress
ConfTestSocketAddress *ConfTestSocketAddress_new(Dz1Str addr, u16_t port, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ConfTestSocketAddress *__internal_ret = (ConfTestSocketAddress *)Dz1Calloc(sizeof(ConfTestSocketAddress), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ConfTestSocketAddress_delAndSetNull, (void *)&__internal_ret);
		
		if (addr && (__internal_ret->addr = Dz1Str_clone(addr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->port = port;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ConfTestSocketAddress_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ConfTestSocketAddress_copy(ConfTestSocketAddress *dst, ConfTestSocketAddress *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->addr && (dst->addr = Dz1Str_clone(src->addr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->port = src->port;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ConfTestSocketAddress *ConfTestSocketAddress_clone(ConfTestSocketAddress *src, Dz1Error *err)
{
	ConfTestSocketAddress *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ConfTestSocketAddress *)Dz1Calloc(sizeof(ConfTestSocketAddress), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ConfTestSocketAddress_delAndSetNull, (void *)&dst);
		if (ConfTestSocketAddress_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ConfTestSocketAddress_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ConfTestSocketAddress_purge(ConfTestSocketAddress *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->addr);
}

void ConfTestSocketAddress_del(ConfTestSocketAddress *p)
{
	if (p == NULL) return;
	ConfTestSocketAddress_purge(p);
	Dz1Free(p);
}

// ConfTestSocketAddress
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConnectionPresent
static struct Iso14827TestConnectionPresentMapA
{
	str_t str;
	Iso14827TestConnectionPresent v;
} Iso14827TestConnectionPresentMapA[] =
{
	{ (char *)"passive", Iso14827TestConnectionPresent_passive },
	{ (char *)"active", Iso14827TestConnectionPresent_active },
	{ NULL, Iso14827TestConnectionPresent_max }
};

str_t Iso14827TestConnectionPresentStrA(Iso14827TestConnectionPresent v)
{
	struct Iso14827TestConnectionPresentMapA *i = NULL;
	for (i = Iso14827TestConnectionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestConnectionPresent Iso14827TestConnectionPresentFromStrA(str_t str)
{
	struct Iso14827TestConnectionPresentMapA *i = NULL;
	for (i = Iso14827TestConnectionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestConnectionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestConnectionPresentMapW
{
	wstr_t str;
	Iso14827TestConnectionPresent v;
} Iso14827TestConnectionPresentMapW[] =
{
	{ (wchar_t *)L"passive", Iso14827TestConnectionPresent_passive },
	{ (wchar_t *)L"active", Iso14827TestConnectionPresent_active },
	{ NULL, Iso14827TestConnectionPresent_max }
};

wstr_t Iso14827TestConnectionPresentStrW(Iso14827TestConnectionPresent v)
{
	struct Iso14827TestConnectionPresentMapW *i = NULL;
	for (i = Iso14827TestConnectionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestConnectionPresent Iso14827TestConnectionPresentFromStrW(wstr_t str)
{
	struct Iso14827TestConnectionPresentMapW *i = NULL;
	for (i = Iso14827TestConnectionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestConnectionPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestConnectionPresent *Iso14827TestConnectionPresent_new(Iso14827TestConnectionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestConnectionPresent *__internal_ret = (Iso14827TestConnectionPresent *)Dz1Calloc(sizeof(Iso14827TestConnectionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestConnectionPresent_dump(Iso14827TestConnectionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestConnectionPresentStr(*v));
}
// Iso14827TestConnectionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConnection
Iso14827TestConnection *Iso14827TestConnection_new(Iso14827TestConnectionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestConnection *ret = (Iso14827TestConnection *)Dz1Calloc(sizeof(Iso14827TestConnection), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TestConnectionPresent_passive:
			// _U_prim_clone
			if (ptr != NULL) ret->x.passive = *(u16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConnectionPresent_active:
			// _U_cst_clone
			if (ptr != NULL) ret->x.active = (ConfTestSocketAddress *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConnectionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestConnection_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827TestConnection_copy(Iso14827TestConnection *ret, Iso14827TestConnection *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827TestConnectionPresent_passive:
			// _U_prim_clone
			ret->x.passive = src->x.passive;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConnectionPresent_active:
			// _U_cst_clone
			if (src->x.active && (ret->x.active = ConfTestSocketAddress_clone(src->x.active, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestConnection *Iso14827TestConnection_clone(Iso14827TestConnection *src, Dz1Error *err)
{
	Iso14827TestConnection *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827TestConnection *)Dz1Calloc(sizeof(Iso14827TestConnection), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void *)&ret);
		if (Iso14827TestConnection_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestConnection_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestConnection_purge(Iso14827TestConnection *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TestConnectionPresent_passive:
		break;
	case Iso14827TestConnectionPresent_active:
		ConfTestSocketAddress_del(p->x.active);
		break;
	default:
		break;
	}
}

void Iso14827TestConnection_del(Iso14827TestConnection *p)
{
	if (!p) return;
	Iso14827TestConnection_purge(p);
	Dz1Free(p);
}

void Iso14827TestConnection_dump(Iso14827TestConnection *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TestConnectionPresent_passive:
		Dz1Thread_printf(Dz1T("passive = ")); Dz1u16_dump(&p->x.passive, tab); 
		break;
	case Iso14827TestConnectionPresent_active:
		Dz1Thread_printf(Dz1T("active = ")); ConfTestSocketAddress_dump(p->x.active, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827TestConnection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2ConnectionPresent
static struct TechnicalRegulation2ConnectionPresentMapA
{
	str_t str;
	TechnicalRegulation2ConnectionPresent v;
} TechnicalRegulation2ConnectionPresentMapA[] =
{
	{ (char *)"passive", TechnicalRegulation2ConnectionPresent_passive },
	{ (char *)"active", TechnicalRegulation2ConnectionPresent_active },
	{ NULL, TechnicalRegulation2ConnectionPresent_max }
};

str_t TechnicalRegulation2ConnectionPresentStrA(TechnicalRegulation2ConnectionPresent v)
{
	struct TechnicalRegulation2ConnectionPresentMapA *i = NULL;
	for (i = TechnicalRegulation2ConnectionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TechnicalRegulation2ConnectionPresent TechnicalRegulation2ConnectionPresentFromStrA(str_t str)
{
	struct TechnicalRegulation2ConnectionPresentMapA *i = NULL;
	for (i = TechnicalRegulation2ConnectionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TechnicalRegulation2ConnectionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct TechnicalRegulation2ConnectionPresentMapW
{
	wstr_t str;
	TechnicalRegulation2ConnectionPresent v;
} TechnicalRegulation2ConnectionPresentMapW[] =
{
	{ (wchar_t *)L"passive", TechnicalRegulation2ConnectionPresent_passive },
	{ (wchar_t *)L"active", TechnicalRegulation2ConnectionPresent_active },
	{ NULL, TechnicalRegulation2ConnectionPresent_max }
};

wstr_t TechnicalRegulation2ConnectionPresentStrW(TechnicalRegulation2ConnectionPresent v)
{
	struct TechnicalRegulation2ConnectionPresentMapW *i = NULL;
	for (i = TechnicalRegulation2ConnectionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TechnicalRegulation2ConnectionPresent TechnicalRegulation2ConnectionPresentFromStrW(wstr_t str)
{
	struct TechnicalRegulation2ConnectionPresentMapW *i = NULL;
	for (i = TechnicalRegulation2ConnectionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TechnicalRegulation2ConnectionPresent_max;
}
#endif // UNIX_SYSTEM

TechnicalRegulation2ConnectionPresent *TechnicalRegulation2ConnectionPresent_new(TechnicalRegulation2ConnectionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation2ConnectionPresent *__internal_ret = (TechnicalRegulation2ConnectionPresent *)Dz1Calloc(sizeof(TechnicalRegulation2ConnectionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TechnicalRegulation2ConnectionPresent_dump(TechnicalRegulation2ConnectionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TechnicalRegulation2ConnectionPresentStr(*v));
}
// TechnicalRegulation2ConnectionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2Connection
TechnicalRegulation2Connection *TechnicalRegulation2Connection_new(TechnicalRegulation2ConnectionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation2Connection *ret = (TechnicalRegulation2Connection *)Dz1Calloc(sizeof(TechnicalRegulation2Connection), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2Connection_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case TechnicalRegulation2ConnectionPresent_passive:
			// _U_prim_clone
			if (ptr != NULL) ret->x.passive = *(u16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation2ConnectionPresent_active:
			// _U_cst_clone
			if (ptr != NULL) ret->x.active = (ConfTestSocketAddress *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation2ConnectionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2Connection_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TechnicalRegulation2Connection_copy(TechnicalRegulation2Connection *ret, TechnicalRegulation2Connection *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case TechnicalRegulation2ConnectionPresent_passive:
			// _U_prim_clone
			ret->x.passive = src->x.passive;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation2ConnectionPresent_active:
			// _U_cst_clone
			if (src->x.active && (ret->x.active = ConfTestSocketAddress_clone(src->x.active, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation2Connection *TechnicalRegulation2Connection_clone(TechnicalRegulation2Connection *src, Dz1Error *err)
{
	TechnicalRegulation2Connection *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (TechnicalRegulation2Connection *)Dz1Calloc(sizeof(TechnicalRegulation2Connection), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2Connection_delAndSetNull, (void *)&ret);
		if (TechnicalRegulation2Connection_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2Connection_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TechnicalRegulation2Connection_purge(TechnicalRegulation2Connection *p)
{
	if (!p) return;
	switch(p->present)
	{
	case TechnicalRegulation2ConnectionPresent_passive:
		break;
	case TechnicalRegulation2ConnectionPresent_active:
		ConfTestSocketAddress_del(p->x.active);
		break;
	default:
		break;
	}
}

void TechnicalRegulation2Connection_del(TechnicalRegulation2Connection *p)
{
	if (!p) return;
	TechnicalRegulation2Connection_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation2Connection_dump(TechnicalRegulation2Connection *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case TechnicalRegulation2ConnectionPresent_passive:
		Dz1Thread_printf(Dz1T("passive = ")); Dz1u16_dump(&p->x.passive, tab); 
		break;
	case TechnicalRegulation2ConnectionPresent_active:
		Dz1Thread_printf(Dz1T("active = ")); ConfTestSocketAddress_dump(p->x.active, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// TechnicalRegulation2Connection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecDuo
SubscribeSpecDuo *SubscribeSpecDuo_new(SubscribeSpecEntry *session1, 
									   SubscribeSpecEntry *session2, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	SubscribeSpecDuo *__internal_ret = (SubscribeSpecDuo *)Dz1Calloc(sizeof(SubscribeSpecDuo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(SubscribeSpecDuo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->session1 = session1;
		__internal_ret->session2 = session2;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecDuo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t SubscribeSpecDuo_copy(SubscribeSpecDuo *dst, SubscribeSpecDuo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->session1 && (dst->session1 = SubscribeSpecEntry_clone(src->session1, errp)) == NULL) ERR_OUT(errp);
	else if (src->session2 && (dst->session2 = SubscribeSpecEntry_clone(src->session2, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

SubscribeSpecDuo *SubscribeSpecDuo_clone(SubscribeSpecDuo *src, Dz1Error *err)
{
	SubscribeSpecDuo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (SubscribeSpecDuo *)Dz1Calloc(sizeof(SubscribeSpecDuo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(SubscribeSpecDuo_delAndSetNull, (void *)&dst);
		if (SubscribeSpecDuo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (SubscribeSpecDuo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void SubscribeSpecDuo_purge(SubscribeSpecDuo *p)
{
	if (p == NULL) return;
	SubscribeSpecEntry_del(p->session1);
	SubscribeSpecEntry_del(p->session2);
}

void SubscribeSpecDuo_del(SubscribeSpecDuo *p)
{
	if (p == NULL) return;
	SubscribeSpecDuo_purge(p);
	Dz1Free(p);
}

void SubscribeSpecDuo_dump(SubscribeSpecDuo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("session1 = ")); SubscribeSpecEntry_dump(p->session1, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("session2 = ")); SubscribeSpecEntry_dump(p->session2, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// SubscribeSpecDuo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestAuth
static struct Iso14827TestAuthMapA
{
	str_t str;
	Iso14827TestAuth v;
} Iso14827TestAuthMapA[] =
{
	{ (char *)"success", Iso14827TestAuth_success },
	{ (char *)"not_found", Iso14827TestAuth_not_found },
	{ (char *)"invalid_passwd", Iso14827TestAuth_invalid_passwd },
	{ (char *)"codec_not_support", Iso14827TestAuth_codec_not_support },
	{ NULL, Iso14827TestAuth_max }
};

str_t Iso14827TestAuthStrA(Iso14827TestAuth v)
{
	struct Iso14827TestAuthMapA *i = NULL;
	for (i = Iso14827TestAuthMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestAuth Iso14827TestAuthFromStrA(str_t str)
{
	struct Iso14827TestAuthMapA *i = NULL;
	for (i = Iso14827TestAuthMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestAuth_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestAuthMapW
{
	wstr_t str;
	Iso14827TestAuth v;
} Iso14827TestAuthMapW[] =
{
	{ (wchar_t *)L"success", Iso14827TestAuth_success },
	{ (wchar_t *)L"not_found", Iso14827TestAuth_not_found },
	{ (wchar_t *)L"invalid_passwd", Iso14827TestAuth_invalid_passwd },
	{ (wchar_t *)L"codec_not_support", Iso14827TestAuth_codec_not_support },
	{ NULL, Iso14827TestAuth_max }
};

wstr_t Iso14827TestAuthStrW(Iso14827TestAuth v)
{
	struct Iso14827TestAuthMapW *i = NULL;
	for (i = Iso14827TestAuthMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestAuth Iso14827TestAuthFromStrW(wstr_t str)
{
	struct Iso14827TestAuthMapW *i = NULL;
	for (i = Iso14827TestAuthMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestAuth_max;
}
#endif // UNIX_SYSTEM

Iso14827TestAuth *Iso14827TestAuth_new(Iso14827TestAuth *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestAuth *__internal_ret = (Iso14827TestAuth *)Dz1Calloc(sizeof(Iso14827TestAuth), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827TestAuth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_centerClient2rse
PolicePrj4ValidateSet_centerClient2rse *PolicePrj4ValidateSet_centerClient2rse_new(bool_t test_bsm, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4ValidateSet_centerClient2rse *__internal_ret = (PolicePrj4ValidateSet_centerClient2rse *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_centerClient2rse), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_centerClient2rse_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_bsm = test_bsm;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_centerClient2rse_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4ValidateSet_centerClient2rse_copy(PolicePrj4ValidateSet_centerClient2rse *dst, PolicePrj4ValidateSet_centerClient2rse *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_bsm = src->test_bsm;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4ValidateSet_centerClient2rse *PolicePrj4ValidateSet_centerClient2rse_clone(PolicePrj4ValidateSet_centerClient2rse *src, Dz1Error *err)
{
	PolicePrj4ValidateSet_centerClient2rse *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4ValidateSet_centerClient2rse *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_centerClient2rse), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_centerClient2rse_delAndSetNull, (void *)&dst);
		if (PolicePrj4ValidateSet_centerClient2rse_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_centerClient2rse_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4ValidateSet_centerClient2rse_purge(PolicePrj4ValidateSet_centerClient2rse *p)
{
	if (p == NULL) return;
}

void PolicePrj4ValidateSet_centerClient2rse_del(PolicePrj4ValidateSet_centerClient2rse *p)
{
	if (p == NULL) return;
	PolicePrj4ValidateSet_centerClient2rse_purge(p);
	Dz1Free(p);
}

void PolicePrj4ValidateSet_centerClient2rse_dump(PolicePrj4ValidateSet_centerClient2rse *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("test_bsm = ")); Dz1Bool_dump(&p->test_bsm, tab); 
	}
}
// PolicePrj4ValidateSet_centerClient2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_rseServer2center
PolicePrj4ValidateSet_rseServer2center *PolicePrj4ValidateSet_rseServer2center_new(bool_t test_bsm, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4ValidateSet_rseServer2center *__internal_ret = (PolicePrj4ValidateSet_rseServer2center *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_rseServer2center), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_rseServer2center_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_bsm = test_bsm;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_rseServer2center_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4ValidateSet_rseServer2center_copy(PolicePrj4ValidateSet_rseServer2center *dst, PolicePrj4ValidateSet_rseServer2center *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_bsm = src->test_bsm;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4ValidateSet_rseServer2center *PolicePrj4ValidateSet_rseServer2center_clone(PolicePrj4ValidateSet_rseServer2center *src, Dz1Error *err)
{
	PolicePrj4ValidateSet_rseServer2center *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4ValidateSet_rseServer2center *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_rseServer2center), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_rseServer2center_delAndSetNull, (void *)&dst);
		if (PolicePrj4ValidateSet_rseServer2center_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_rseServer2center_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4ValidateSet_rseServer2center_purge(PolicePrj4ValidateSet_rseServer2center *p)
{
	if (p == NULL) return;
}

void PolicePrj4ValidateSet_rseServer2center_del(PolicePrj4ValidateSet_rseServer2center *p)
{
	if (p == NULL) return;
	PolicePrj4ValidateSet_rseServer2center_purge(p);
	Dz1Free(p);
}

void PolicePrj4ValidateSet_rseServer2center_dump(PolicePrj4ValidateSet_rseServer2center *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("test_bsm = ")); Dz1Bool_dump(&p->test_bsm, tab); 
	}
}
// PolicePrj4ValidateSet_rseServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_rseClient2center
PolicePrj4ValidateSet_rseClient2center *PolicePrj4ValidateSet_rseClient2center_new(bool_t test_map, 
																				   bool_t test_rsa, 
																				   bool_t test_tim, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4ValidateSet_rseClient2center *__internal_ret = (PolicePrj4ValidateSet_rseClient2center *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_rseClient2center), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_rseClient2center_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_map = test_map;
		__internal_ret->test_rsa = test_rsa;
		__internal_ret->test_tim = test_tim;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_rseClient2center_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4ValidateSet_rseClient2center_copy(PolicePrj4ValidateSet_rseClient2center *dst, PolicePrj4ValidateSet_rseClient2center *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_map = src->test_map;
		dst->test_rsa = src->test_rsa;
		dst->test_tim = src->test_tim;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4ValidateSet_rseClient2center *PolicePrj4ValidateSet_rseClient2center_clone(PolicePrj4ValidateSet_rseClient2center *src, Dz1Error *err)
{
	PolicePrj4ValidateSet_rseClient2center *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4ValidateSet_rseClient2center *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_rseClient2center), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_rseClient2center_delAndSetNull, (void *)&dst);
		if (PolicePrj4ValidateSet_rseClient2center_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_rseClient2center_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4ValidateSet_rseClient2center_purge(PolicePrj4ValidateSet_rseClient2center *p)
{
	if (p == NULL) return;
}

void PolicePrj4ValidateSet_rseClient2center_del(PolicePrj4ValidateSet_rseClient2center *p)
{
	if (p == NULL) return;
	PolicePrj4ValidateSet_rseClient2center_purge(p);
	Dz1Free(p);
}

void PolicePrj4ValidateSet_rseClient2center_dump(PolicePrj4ValidateSet_rseClient2center *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsa = ")); Dz1Bool_dump(&p->test_rsa, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tim = ")); Dz1Bool_dump(&p->test_tim, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PolicePrj4ValidateSet_rseClient2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_centerServer2rse
PolicePrj4ValidateSet_centerServer2rse *PolicePrj4ValidateSet_centerServer2rse_new(bool_t test_map, 
																				   bool_t test_rsa, 
																				   bool_t test_tim, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4ValidateSet_centerServer2rse *__internal_ret = (PolicePrj4ValidateSet_centerServer2rse *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_centerServer2rse), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_centerServer2rse_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_map = test_map;
		__internal_ret->test_rsa = test_rsa;
		__internal_ret->test_tim = test_tim;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_centerServer2rse_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4ValidateSet_centerServer2rse_copy(PolicePrj4ValidateSet_centerServer2rse *dst, PolicePrj4ValidateSet_centerServer2rse *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_map = src->test_map;
		dst->test_rsa = src->test_rsa;
		dst->test_tim = src->test_tim;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4ValidateSet_centerServer2rse *PolicePrj4ValidateSet_centerServer2rse_clone(PolicePrj4ValidateSet_centerServer2rse *src, Dz1Error *err)
{
	PolicePrj4ValidateSet_centerServer2rse *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4ValidateSet_centerServer2rse *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_centerServer2rse), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_centerServer2rse_delAndSetNull, (void *)&dst);
		if (PolicePrj4ValidateSet_centerServer2rse_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_centerServer2rse_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4ValidateSet_centerServer2rse_purge(PolicePrj4ValidateSet_centerServer2rse *p)
{
	if (p == NULL) return;
}

void PolicePrj4ValidateSet_centerServer2rse_del(PolicePrj4ValidateSet_centerServer2rse *p)
{
	if (p == NULL) return;
	PolicePrj4ValidateSet_centerServer2rse_purge(p);
	Dz1Free(p);
}

void PolicePrj4ValidateSet_centerServer2rse_dump(PolicePrj4ValidateSet_centerServer2rse *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsa = ")); Dz1Bool_dump(&p->test_rsa, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tim = ")); Dz1Bool_dump(&p->test_tim, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PolicePrj4ValidateSet_centerServer2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4ValidateSet_signalserverServer2center
PolicePrj4ValidateSet_signalserverServer2center *PolicePrj4ValidateSet_signalserverServer2center_new(bool_t test_spat, 
																									 bool_t test_tls, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4ValidateSet_signalserverServer2center *__internal_ret = (PolicePrj4ValidateSet_signalserverServer2center *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_signalserverServer2center), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_signalserverServer2center_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_spat = test_spat;
		__internal_ret->test_tls = test_tls;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_signalserverServer2center_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4ValidateSet_signalserverServer2center_copy(PolicePrj4ValidateSet_signalserverServer2center *dst, PolicePrj4ValidateSet_signalserverServer2center *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_spat = src->test_spat;
		dst->test_tls = src->test_tls;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4ValidateSet_signalserverServer2center *PolicePrj4ValidateSet_signalserverServer2center_clone(PolicePrj4ValidateSet_signalserverServer2center *src, Dz1Error *err)
{
	PolicePrj4ValidateSet_signalserverServer2center *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4ValidateSet_signalserverServer2center *)Dz1Calloc(sizeof(PolicePrj4ValidateSet_signalserverServer2center), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4ValidateSet_signalserverServer2center_delAndSetNull, (void *)&dst);
		if (PolicePrj4ValidateSet_signalserverServer2center_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4ValidateSet_signalserverServer2center_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4ValidateSet_signalserverServer2center_purge(PolicePrj4ValidateSet_signalserverServer2center *p)
{
	if (p == NULL) return;
}

void PolicePrj4ValidateSet_signalserverServer2center_del(PolicePrj4ValidateSet_signalserverServer2center *p)
{
	if (p == NULL) return;
	PolicePrj4ValidateSet_signalserverServer2center_purge(p);
	Dz1Free(p);
}

void PolicePrj4ValidateSet_signalserverServer2center_dump(PolicePrj4ValidateSet_signalserverServer2center *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_spat = ")); Dz1Bool_dump(&p->test_spat, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tls = ")); Dz1Bool_dump(&p->test_tls, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PolicePrj4ValidateSet_signalserverServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3ValidateSet_c2cClient
ITSK00100_3ValidateSet_c2cClient *ITSK00100_3ValidateSet_c2cClient_new(bool_t test_pub_incident_detection_info, 
																	   bool_t test_pub_incident_termination_info, 
																	   bool_t test_pub_incident_detection_video_file_info_provide, 
																	   bool_t test_pub_control_state_info, 
																	   bool_t test_pub_sensor_state_info, 
																	   bool_t test_pub_moving_object, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00100_3ValidateSet_c2cClient *__internal_ret = (ITSK00100_3ValidateSet_c2cClient *)Dz1Calloc(sizeof(ITSK00100_3ValidateSet_c2cClient), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00100_3ValidateSet_c2cClient_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_pub_incident_detection_info = test_pub_incident_detection_info;
		__internal_ret->test_pub_incident_termination_info = test_pub_incident_termination_info;
		__internal_ret->test_pub_incident_detection_video_file_info_provide = test_pub_incident_detection_video_file_info_provide;
		__internal_ret->test_pub_control_state_info = test_pub_control_state_info;
		__internal_ret->test_pub_sensor_state_info = test_pub_sensor_state_info;
		__internal_ret->test_pub_moving_object = test_pub_moving_object;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00100_3ValidateSet_c2cClient_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00100_3ValidateSet_c2cClient_copy(ITSK00100_3ValidateSet_c2cClient *dst, ITSK00100_3ValidateSet_c2cClient *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_pub_incident_detection_info = src->test_pub_incident_detection_info;
		dst->test_pub_incident_termination_info = src->test_pub_incident_termination_info;
		dst->test_pub_incident_detection_video_file_info_provide = src->test_pub_incident_detection_video_file_info_provide;
		dst->test_pub_control_state_info = src->test_pub_control_state_info;
		dst->test_pub_sensor_state_info = src->test_pub_sensor_state_info;
		dst->test_pub_moving_object = src->test_pub_moving_object;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00100_3ValidateSet_c2cClient *ITSK00100_3ValidateSet_c2cClient_clone(ITSK00100_3ValidateSet_c2cClient *src, Dz1Error *err)
{
	ITSK00100_3ValidateSet_c2cClient *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00100_3ValidateSet_c2cClient *)Dz1Calloc(sizeof(ITSK00100_3ValidateSet_c2cClient), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00100_3ValidateSet_c2cClient_delAndSetNull, (void *)&dst);
		if (ITSK00100_3ValidateSet_c2cClient_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00100_3ValidateSet_c2cClient_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00100_3ValidateSet_c2cClient_purge(ITSK00100_3ValidateSet_c2cClient *p)
{
	if (p == NULL) return;
}

void ITSK00100_3ValidateSet_c2cClient_del(ITSK00100_3ValidateSet_c2cClient *p)
{
	if (p == NULL) return;
	ITSK00100_3ValidateSet_c2cClient_purge(p);
	Dz1Free(p);
}

void ITSK00100_3ValidateSet_c2cClient_dump(ITSK00100_3ValidateSet_c2cClient *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_detection_info = ")); Dz1Bool_dump(&p->test_pub_incident_detection_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_termination_info = ")); Dz1Bool_dump(&p->test_pub_incident_termination_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_detection_video_file_info_provide = ")); Dz1Bool_dump(&p->test_pub_incident_detection_video_file_info_provide, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_control_state_info = ")); Dz1Bool_dump(&p->test_pub_control_state_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_sensor_state_info = ")); Dz1Bool_dump(&p->test_pub_sensor_state_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_moving_object = ")); Dz1Bool_dump(&p->test_pub_moving_object, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00100_3ValidateSet_c2cClient
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3ValidateSet_c2cServer
ITSK00100_3ValidateSet_c2cServer *ITSK00100_3ValidateSet_c2cServer_new(bool_t test_pub_incident_detection_info, 
																	   bool_t test_pub_incident_termination_info, 
																	   bool_t test_pub_incident_detection_video_file_info_provide, 
																	   bool_t test_pub_control_state_info, 
																	   bool_t test_pub_sensor_state_info, 
																	   bool_t test_pub_moving_object, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00100_3ValidateSet_c2cServer *__internal_ret = (ITSK00100_3ValidateSet_c2cServer *)Dz1Calloc(sizeof(ITSK00100_3ValidateSet_c2cServer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00100_3ValidateSet_c2cServer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_pub_incident_detection_info = test_pub_incident_detection_info;
		__internal_ret->test_pub_incident_termination_info = test_pub_incident_termination_info;
		__internal_ret->test_pub_incident_detection_video_file_info_provide = test_pub_incident_detection_video_file_info_provide;
		__internal_ret->test_pub_control_state_info = test_pub_control_state_info;
		__internal_ret->test_pub_sensor_state_info = test_pub_sensor_state_info;
		__internal_ret->test_pub_moving_object = test_pub_moving_object;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00100_3ValidateSet_c2cServer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00100_3ValidateSet_c2cServer_copy(ITSK00100_3ValidateSet_c2cServer *dst, ITSK00100_3ValidateSet_c2cServer *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_pub_incident_detection_info = src->test_pub_incident_detection_info;
		dst->test_pub_incident_termination_info = src->test_pub_incident_termination_info;
		dst->test_pub_incident_detection_video_file_info_provide = src->test_pub_incident_detection_video_file_info_provide;
		dst->test_pub_control_state_info = src->test_pub_control_state_info;
		dst->test_pub_sensor_state_info = src->test_pub_sensor_state_info;
		dst->test_pub_moving_object = src->test_pub_moving_object;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00100_3ValidateSet_c2cServer *ITSK00100_3ValidateSet_c2cServer_clone(ITSK00100_3ValidateSet_c2cServer *src, Dz1Error *err)
{
	ITSK00100_3ValidateSet_c2cServer *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00100_3ValidateSet_c2cServer *)Dz1Calloc(sizeof(ITSK00100_3ValidateSet_c2cServer), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00100_3ValidateSet_c2cServer_delAndSetNull, (void *)&dst);
		if (ITSK00100_3ValidateSet_c2cServer_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00100_3ValidateSet_c2cServer_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00100_3ValidateSet_c2cServer_purge(ITSK00100_3ValidateSet_c2cServer *p)
{
	if (p == NULL) return;
}

void ITSK00100_3ValidateSet_c2cServer_del(ITSK00100_3ValidateSet_c2cServer *p)
{
	if (p == NULL) return;
	ITSK00100_3ValidateSet_c2cServer_purge(p);
	Dz1Free(p);
}

void ITSK00100_3ValidateSet_c2cServer_dump(ITSK00100_3ValidateSet_c2cServer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_detection_info = ")); Dz1Bool_dump(&p->test_pub_incident_detection_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_termination_info = ")); Dz1Bool_dump(&p->test_pub_incident_termination_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_detection_video_file_info_provide = ")); Dz1Bool_dump(&p->test_pub_incident_detection_video_file_info_provide, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_control_state_info = ")); Dz1Bool_dump(&p->test_pub_control_state_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_sensor_state_info = ")); Dz1Bool_dump(&p->test_pub_sensor_state_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_moving_object = ")); Dz1Bool_dump(&p->test_pub_moving_object, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00100_3ValidateSet_c2cServer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1ValidateSet_clientRole1
TechnicalRegulation1ValidateSet_clientRole1 *TechnicalRegulation1ValidateSet_clientRole1_new(bool_t test_pub_current_link_state, 
																							 bool_t test_pub_event_identity, 
																							 bool_t test_pub_incident_identity, 
																							 bool_t test_pub_incident_conditions, 
																							 bool_t test_pub_roadway_surface_status, 
																							 bool_t test_pub_weather_information, 
																							 bool_t test_pub_link_roadway_geometry, 
																							 bool_t test_pub_probe_vehicle_detection, 
																							 bool_t test_pub_detector_collection, 
																							 bool_t test_pub_extention_comm_pdu, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation1ValidateSet_clientRole1 *__internal_ret = (TechnicalRegulation1ValidateSet_clientRole1 *)Dz1Calloc(sizeof(TechnicalRegulation1ValidateSet_clientRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1ValidateSet_clientRole1_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_pub_current_link_state = test_pub_current_link_state;
		__internal_ret->test_pub_event_identity = test_pub_event_identity;
		__internal_ret->test_pub_incident_identity = test_pub_incident_identity;
		__internal_ret->test_pub_incident_conditions = test_pub_incident_conditions;
		__internal_ret->test_pub_roadway_surface_status = test_pub_roadway_surface_status;
		__internal_ret->test_pub_weather_information = test_pub_weather_information;
		__internal_ret->test_pub_link_roadway_geometry = test_pub_link_roadway_geometry;
		__internal_ret->test_pub_probe_vehicle_detection = test_pub_probe_vehicle_detection;
		__internal_ret->test_pub_detector_collection = test_pub_detector_collection;
		__internal_ret->test_pub_extention_comm_pdu = test_pub_extention_comm_pdu;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1ValidateSet_clientRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulation1ValidateSet_clientRole1_copy(TechnicalRegulation1ValidateSet_clientRole1 *dst, TechnicalRegulation1ValidateSet_clientRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_pub_current_link_state = src->test_pub_current_link_state;
		dst->test_pub_event_identity = src->test_pub_event_identity;
		dst->test_pub_incident_identity = src->test_pub_incident_identity;
		dst->test_pub_incident_conditions = src->test_pub_incident_conditions;
		dst->test_pub_roadway_surface_status = src->test_pub_roadway_surface_status;
		dst->test_pub_weather_information = src->test_pub_weather_information;
		dst->test_pub_link_roadway_geometry = src->test_pub_link_roadway_geometry;
		dst->test_pub_probe_vehicle_detection = src->test_pub_probe_vehicle_detection;
		dst->test_pub_detector_collection = src->test_pub_detector_collection;
		dst->test_pub_extention_comm_pdu = src->test_pub_extention_comm_pdu;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation1ValidateSet_clientRole1 *TechnicalRegulation1ValidateSet_clientRole1_clone(TechnicalRegulation1ValidateSet_clientRole1 *src, Dz1Error *err)
{
	TechnicalRegulation1ValidateSet_clientRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulation1ValidateSet_clientRole1 *)Dz1Calloc(sizeof(TechnicalRegulation1ValidateSet_clientRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1ValidateSet_clientRole1_delAndSetNull, (void *)&dst);
		if (TechnicalRegulation1ValidateSet_clientRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1ValidateSet_clientRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulation1ValidateSet_clientRole1_purge(TechnicalRegulation1ValidateSet_clientRole1 *p)
{
	if (p == NULL) return;
}

void TechnicalRegulation1ValidateSet_clientRole1_del(TechnicalRegulation1ValidateSet_clientRole1 *p)
{
	if (p == NULL) return;
	TechnicalRegulation1ValidateSet_clientRole1_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation1ValidateSet_clientRole1_dump(TechnicalRegulation1ValidateSet_clientRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_pub_current_link_state = ")); Dz1Bool_dump(&p->test_pub_current_link_state, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_event_identity = ")); Dz1Bool_dump(&p->test_pub_event_identity, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_identity = ")); Dz1Bool_dump(&p->test_pub_incident_identity, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_conditions = ")); Dz1Bool_dump(&p->test_pub_incident_conditions, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_roadway_surface_status = ")); Dz1Bool_dump(&p->test_pub_roadway_surface_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_weather_information = ")); Dz1Bool_dump(&p->test_pub_weather_information, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_link_roadway_geometry = ")); Dz1Bool_dump(&p->test_pub_link_roadway_geometry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_probe_vehicle_detection = ")); Dz1Bool_dump(&p->test_pub_probe_vehicle_detection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_detector_collection = ")); Dz1Bool_dump(&p->test_pub_detector_collection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_extention_comm_pdu = ")); Dz1Bool_dump(&p->test_pub_extention_comm_pdu, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulation1ValidateSet_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1ValidateSet_serverRole1
TechnicalRegulation1ValidateSet_serverRole1 *TechnicalRegulation1ValidateSet_serverRole1_new(bool_t test_sub_current_link_state, 
																							 bool_t test_sub_event_identity, 
																							 bool_t test_sub_incident_identity, 
																							 bool_t test_sub_incident_conditions, 
																							 bool_t test_sub_roadway_surface_status, 
																							 bool_t test_sub_weather_information, 
																							 bool_t test_sub_link_roadway_geometry, 
																							 bool_t test_sub_probe_vehicle_detection, 
																							 bool_t test_sub_detector_collection, 
																							 bool_t test_sub_extention_comm_pdu, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation1ValidateSet_serverRole1 *__internal_ret = (TechnicalRegulation1ValidateSet_serverRole1 *)Dz1Calloc(sizeof(TechnicalRegulation1ValidateSet_serverRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1ValidateSet_serverRole1_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_sub_current_link_state = test_sub_current_link_state;
		__internal_ret->test_sub_event_identity = test_sub_event_identity;
		__internal_ret->test_sub_incident_identity = test_sub_incident_identity;
		__internal_ret->test_sub_incident_conditions = test_sub_incident_conditions;
		__internal_ret->test_sub_roadway_surface_status = test_sub_roadway_surface_status;
		__internal_ret->test_sub_weather_information = test_sub_weather_information;
		__internal_ret->test_sub_link_roadway_geometry = test_sub_link_roadway_geometry;
		__internal_ret->test_sub_probe_vehicle_detection = test_sub_probe_vehicle_detection;
		__internal_ret->test_sub_detector_collection = test_sub_detector_collection;
		__internal_ret->test_sub_extention_comm_pdu = test_sub_extention_comm_pdu;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1ValidateSet_serverRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulation1ValidateSet_serverRole1_copy(TechnicalRegulation1ValidateSet_serverRole1 *dst, TechnicalRegulation1ValidateSet_serverRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_sub_current_link_state = src->test_sub_current_link_state;
		dst->test_sub_event_identity = src->test_sub_event_identity;
		dst->test_sub_incident_identity = src->test_sub_incident_identity;
		dst->test_sub_incident_conditions = src->test_sub_incident_conditions;
		dst->test_sub_roadway_surface_status = src->test_sub_roadway_surface_status;
		dst->test_sub_weather_information = src->test_sub_weather_information;
		dst->test_sub_link_roadway_geometry = src->test_sub_link_roadway_geometry;
		dst->test_sub_probe_vehicle_detection = src->test_sub_probe_vehicle_detection;
		dst->test_sub_detector_collection = src->test_sub_detector_collection;
		dst->test_sub_extention_comm_pdu = src->test_sub_extention_comm_pdu;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation1ValidateSet_serverRole1 *TechnicalRegulation1ValidateSet_serverRole1_clone(TechnicalRegulation1ValidateSet_serverRole1 *src, Dz1Error *err)
{
	TechnicalRegulation1ValidateSet_serverRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulation1ValidateSet_serverRole1 *)Dz1Calloc(sizeof(TechnicalRegulation1ValidateSet_serverRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1ValidateSet_serverRole1_delAndSetNull, (void *)&dst);
		if (TechnicalRegulation1ValidateSet_serverRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1ValidateSet_serverRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulation1ValidateSet_serverRole1_purge(TechnicalRegulation1ValidateSet_serverRole1 *p)
{
	if (p == NULL) return;
}

void TechnicalRegulation1ValidateSet_serverRole1_del(TechnicalRegulation1ValidateSet_serverRole1 *p)
{
	if (p == NULL) return;
	TechnicalRegulation1ValidateSet_serverRole1_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation1ValidateSet_serverRole1_dump(TechnicalRegulation1ValidateSet_serverRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_sub_current_link_state = ")); Dz1Bool_dump(&p->test_sub_current_link_state, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_event_identity = ")); Dz1Bool_dump(&p->test_sub_event_identity, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_incident_identity = ")); Dz1Bool_dump(&p->test_sub_incident_identity, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_incident_conditions = ")); Dz1Bool_dump(&p->test_sub_incident_conditions, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_roadway_surface_status = ")); Dz1Bool_dump(&p->test_sub_roadway_surface_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_weather_information = ")); Dz1Bool_dump(&p->test_sub_weather_information, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_link_roadway_geometry = ")); Dz1Bool_dump(&p->test_sub_link_roadway_geometry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_probe_vehicle_detection = ")); Dz1Bool_dump(&p->test_sub_probe_vehicle_detection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_detector_collection = ")); Dz1Bool_dump(&p->test_sub_detector_collection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_extention_comm_pdu = ")); Dz1Bool_dump(&p->test_sub_extention_comm_pdu, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulation1ValidateSet_serverRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2ValidateSet_clientRole1
TechnicalRegulation2ValidateSet_clientRole1 *TechnicalRegulation2ValidateSet_clientRole1_new(bool_t test_pub_comm_tx_pdu, 
																							 bool_t test_pub_comm_rx_pdu, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation2ValidateSet_clientRole1 *__internal_ret = (TechnicalRegulation2ValidateSet_clientRole1 *)Dz1Calloc(sizeof(TechnicalRegulation2ValidateSet_clientRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2ValidateSet_clientRole1_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_pub_comm_tx_pdu = test_pub_comm_tx_pdu;
		__internal_ret->test_pub_comm_rx_pdu = test_pub_comm_rx_pdu;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2ValidateSet_clientRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulation2ValidateSet_clientRole1_copy(TechnicalRegulation2ValidateSet_clientRole1 *dst, TechnicalRegulation2ValidateSet_clientRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_pub_comm_tx_pdu = src->test_pub_comm_tx_pdu;
		dst->test_pub_comm_rx_pdu = src->test_pub_comm_rx_pdu;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation2ValidateSet_clientRole1 *TechnicalRegulation2ValidateSet_clientRole1_clone(TechnicalRegulation2ValidateSet_clientRole1 *src, Dz1Error *err)
{
	TechnicalRegulation2ValidateSet_clientRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulation2ValidateSet_clientRole1 *)Dz1Calloc(sizeof(TechnicalRegulation2ValidateSet_clientRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2ValidateSet_clientRole1_delAndSetNull, (void *)&dst);
		if (TechnicalRegulation2ValidateSet_clientRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2ValidateSet_clientRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulation2ValidateSet_clientRole1_purge(TechnicalRegulation2ValidateSet_clientRole1 *p)
{
	if (p == NULL) return;
}

void TechnicalRegulation2ValidateSet_clientRole1_del(TechnicalRegulation2ValidateSet_clientRole1 *p)
{
	if (p == NULL) return;
	TechnicalRegulation2ValidateSet_clientRole1_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation2ValidateSet_clientRole1_dump(TechnicalRegulation2ValidateSet_clientRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_pub_comm_tx_pdu = ")); Dz1Bool_dump(&p->test_pub_comm_tx_pdu, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_comm_rx_pdu = ")); Dz1Bool_dump(&p->test_pub_comm_rx_pdu, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulation2ValidateSet_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2ValidateSet_serverRole1
TechnicalRegulation2ValidateSet_serverRole1 *TechnicalRegulation2ValidateSet_serverRole1_new(bool_t test_pub_comm_tx_pdu, 
																							 bool_t test_pub_comm_rx_pdu, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation2ValidateSet_serverRole1 *__internal_ret = (TechnicalRegulation2ValidateSet_serverRole1 *)Dz1Calloc(sizeof(TechnicalRegulation2ValidateSet_serverRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2ValidateSet_serverRole1_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->test_pub_comm_tx_pdu = test_pub_comm_tx_pdu;
		__internal_ret->test_pub_comm_rx_pdu = test_pub_comm_rx_pdu;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2ValidateSet_serverRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulation2ValidateSet_serverRole1_copy(TechnicalRegulation2ValidateSet_serverRole1 *dst, TechnicalRegulation2ValidateSet_serverRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->test_pub_comm_tx_pdu = src->test_pub_comm_tx_pdu;
		dst->test_pub_comm_rx_pdu = src->test_pub_comm_rx_pdu;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation2ValidateSet_serverRole1 *TechnicalRegulation2ValidateSet_serverRole1_clone(TechnicalRegulation2ValidateSet_serverRole1 *src, Dz1Error *err)
{
	TechnicalRegulation2ValidateSet_serverRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulation2ValidateSet_serverRole1 *)Dz1Calloc(sizeof(TechnicalRegulation2ValidateSet_serverRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2ValidateSet_serverRole1_delAndSetNull, (void *)&dst);
		if (TechnicalRegulation2ValidateSet_serverRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2ValidateSet_serverRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulation2ValidateSet_serverRole1_purge(TechnicalRegulation2ValidateSet_serverRole1 *p)
{
	if (p == NULL) return;
}

void TechnicalRegulation2ValidateSet_serverRole1_del(TechnicalRegulation2ValidateSet_serverRole1 *p)
{
	if (p == NULL) return;
	TechnicalRegulation2ValidateSet_serverRole1_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation2ValidateSet_serverRole1_dump(TechnicalRegulation2ValidateSet_serverRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_pub_comm_tx_pdu = ")); Dz1Bool_dump(&p->test_pub_comm_tx_pdu, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_comm_rx_pdu = ")); Dz1Bool_dump(&p->test_pub_comm_rx_pdu, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulation2ValidateSet_serverRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateSetPresent
static struct Iso14827TestValidateSetPresentMapA
{
	str_t str;
	Iso14827TestValidateSetPresent v;
} Iso14827TestValidateSetPresentMapA[] =
{
	{ (char *)"centerClient2rse", Iso14827TestValidateSetPresent_centerClient2rse },
	{ (char *)"rseServer2center", Iso14827TestValidateSetPresent_rseServer2center },
	{ (char *)"rseClient2center", Iso14827TestValidateSetPresent_rseClient2center },
	{ (char *)"centerServer2rse", Iso14827TestValidateSetPresent_centerServer2rse },
	{ (char *)"signalserverServer2center", Iso14827TestValidateSetPresent_signalserverServer2center },
	{ (char *)"itsk00100_3c2cClient", Iso14827TestValidateSetPresent_itsk00100_3c2cClient },
	{ (char *)"itsk00100_3c2cServer", Iso14827TestValidateSetPresent_itsk00100_3c2cServer },
	{ (char *)"technical_regulation1_clientRole1", Iso14827TestValidateSetPresent_technical_regulation1_clientRole1 },
	{ (char *)"technical_regulation1_serverRole1", Iso14827TestValidateSetPresent_technical_regulation1_serverRole1 },
	{ (char *)"technical_regulation2_clientRole1", Iso14827TestValidateSetPresent_technical_regulation2_clientRole1 },
	{ (char *)"technical_regulation2_serverRole1", Iso14827TestValidateSetPresent_technical_regulation2_serverRole1 },
	{ NULL, Iso14827TestValidateSetPresent_max }
};

str_t Iso14827TestValidateSetPresentStrA(Iso14827TestValidateSetPresent v)
{
	struct Iso14827TestValidateSetPresentMapA *i = NULL;
	for (i = Iso14827TestValidateSetPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestValidateSetPresent Iso14827TestValidateSetPresentFromStrA(str_t str)
{
	struct Iso14827TestValidateSetPresentMapA *i = NULL;
	for (i = Iso14827TestValidateSetPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestValidateSetPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestValidateSetPresentMapW
{
	wstr_t str;
	Iso14827TestValidateSetPresent v;
} Iso14827TestValidateSetPresentMapW[] =
{
	{ (wchar_t *)L"centerClient2rse", Iso14827TestValidateSetPresent_centerClient2rse },
	{ (wchar_t *)L"rseServer2center", Iso14827TestValidateSetPresent_rseServer2center },
	{ (wchar_t *)L"rseClient2center", Iso14827TestValidateSetPresent_rseClient2center },
	{ (wchar_t *)L"centerServer2rse", Iso14827TestValidateSetPresent_centerServer2rse },
	{ (wchar_t *)L"signalserverServer2center", Iso14827TestValidateSetPresent_signalserverServer2center },
	{ (wchar_t *)L"itsk00100_3c2cClient", Iso14827TestValidateSetPresent_itsk00100_3c2cClient },
	{ (wchar_t *)L"itsk00100_3c2cServer", Iso14827TestValidateSetPresent_itsk00100_3c2cServer },
	{ (wchar_t *)L"technical_regulation1_clientRole1", Iso14827TestValidateSetPresent_technical_regulation1_clientRole1 },
	{ (wchar_t *)L"technical_regulation1_serverRole1", Iso14827TestValidateSetPresent_technical_regulation1_serverRole1 },
	{ (wchar_t *)L"technical_regulation2_clientRole1", Iso14827TestValidateSetPresent_technical_regulation2_clientRole1 },
	{ (wchar_t *)L"technical_regulation2_serverRole1", Iso14827TestValidateSetPresent_technical_regulation2_serverRole1 },
	{ NULL, Iso14827TestValidateSetPresent_max }
};

wstr_t Iso14827TestValidateSetPresentStrW(Iso14827TestValidateSetPresent v)
{
	struct Iso14827TestValidateSetPresentMapW *i = NULL;
	for (i = Iso14827TestValidateSetPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestValidateSetPresent Iso14827TestValidateSetPresentFromStrW(wstr_t str)
{
	struct Iso14827TestValidateSetPresentMapW *i = NULL;
	for (i = Iso14827TestValidateSetPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestValidateSetPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestValidateSetPresent *Iso14827TestValidateSetPresent_new(Iso14827TestValidateSetPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestValidateSetPresent *__internal_ret = (Iso14827TestValidateSetPresent *)Dz1Calloc(sizeof(Iso14827TestValidateSetPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestValidateSetPresent_dump(Iso14827TestValidateSetPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestValidateSetPresentStr(*v));
}
// Iso14827TestValidateSetPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateSet
Iso14827TestValidateSet *Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestValidateSet *ret = (Iso14827TestValidateSet *)Dz1Calloc(sizeof(Iso14827TestValidateSet), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestValidateSet_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TestValidateSetPresent_centerClient2rse:
			// _U_cst_clone
			if (ptr != NULL) ret->x.centerClient2rse = (PolicePrj4ValidateSet_centerClient2rse *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_rseServer2center:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rseServer2center = (PolicePrj4ValidateSet_rseServer2center *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_rseClient2center:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rseClient2center = (PolicePrj4ValidateSet_rseClient2center *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_centerServer2rse:
			// _U_cst_clone
			if (ptr != NULL) ret->x.centerServer2rse = (PolicePrj4ValidateSet_centerServer2rse *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_signalserverServer2center:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signalserverServer2center = (PolicePrj4ValidateSet_signalserverServer2center *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_itsk00100_3c2cClient:
			// _U_cst_clone
			if (ptr != NULL) ret->x.itsk00100_3c2cClient = (ITSK00100_3ValidateSet_c2cClient *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_itsk00100_3c2cServer:
			// _U_cst_clone
			if (ptr != NULL) ret->x.itsk00100_3c2cServer = (ITSK00100_3ValidateSet_c2cServer *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_technical_regulation1_clientRole1:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation1_clientRole1 = (TechnicalRegulation1ValidateSet_clientRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_technical_regulation1_serverRole1:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation1_serverRole1 = (TechnicalRegulation1ValidateSet_serverRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_technical_regulation2_clientRole1:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation2_clientRole1 = (TechnicalRegulation2ValidateSet_clientRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_technical_regulation2_serverRole1:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation2_serverRole1 = (TechnicalRegulation2ValidateSet_serverRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestValidateSetPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestValidateSet_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827TestValidateSet_copy(Iso14827TestValidateSet *ret, Iso14827TestValidateSet *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827TestValidateSetPresent_centerClient2rse:
			// _U_cst_clone
			if (src->x.centerClient2rse && (ret->x.centerClient2rse = PolicePrj4ValidateSet_centerClient2rse_clone(src->x.centerClient2rse, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_rseServer2center:
			// _U_cst_clone
			if (src->x.rseServer2center && (ret->x.rseServer2center = PolicePrj4ValidateSet_rseServer2center_clone(src->x.rseServer2center, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_rseClient2center:
			// _U_cst_clone
			if (src->x.rseClient2center && (ret->x.rseClient2center = PolicePrj4ValidateSet_rseClient2center_clone(src->x.rseClient2center, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_centerServer2rse:
			// _U_cst_clone
			if (src->x.centerServer2rse && (ret->x.centerServer2rse = PolicePrj4ValidateSet_centerServer2rse_clone(src->x.centerServer2rse, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_signalserverServer2center:
			// _U_cst_clone
			if (src->x.signalserverServer2center && (ret->x.signalserverServer2center = PolicePrj4ValidateSet_signalserverServer2center_clone(src->x.signalserverServer2center, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_itsk00100_3c2cClient:
			// _U_cst_clone
			if (src->x.itsk00100_3c2cClient && (ret->x.itsk00100_3c2cClient = ITSK00100_3ValidateSet_c2cClient_clone(src->x.itsk00100_3c2cClient, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_itsk00100_3c2cServer:
			// _U_cst_clone
			if (src->x.itsk00100_3c2cServer && (ret->x.itsk00100_3c2cServer = ITSK00100_3ValidateSet_c2cServer_clone(src->x.itsk00100_3c2cServer, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_technical_regulation1_clientRole1:
			// _U_cst_clone
			if (src->x.technical_regulation1_clientRole1 && (ret->x.technical_regulation1_clientRole1 = TechnicalRegulation1ValidateSet_clientRole1_clone(src->x.technical_regulation1_clientRole1, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_technical_regulation1_serverRole1:
			// _U_cst_clone
			if (src->x.technical_regulation1_serverRole1 && (ret->x.technical_regulation1_serverRole1 = TechnicalRegulation1ValidateSet_serverRole1_clone(src->x.technical_regulation1_serverRole1, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_technical_regulation2_clientRole1:
			// _U_cst_clone
			if (src->x.technical_regulation2_clientRole1 && (ret->x.technical_regulation2_clientRole1 = TechnicalRegulation2ValidateSet_clientRole1_clone(src->x.technical_regulation2_clientRole1, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestValidateSetPresent_technical_regulation2_serverRole1:
			// _U_cst_clone
			if (src->x.technical_regulation2_serverRole1 && (ret->x.technical_regulation2_serverRole1 = TechnicalRegulation2ValidateSet_serverRole1_clone(src->x.technical_regulation2_serverRole1, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestValidateSet *Iso14827TestValidateSet_clone(Iso14827TestValidateSet *src, Dz1Error *err)
{
	Iso14827TestValidateSet *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827TestValidateSet *)Dz1Calloc(sizeof(Iso14827TestValidateSet), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestValidateSet_delAndSetNull, (void *)&ret);
		if (Iso14827TestValidateSet_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestValidateSet_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestValidateSet_purge(Iso14827TestValidateSet *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TestValidateSetPresent_centerClient2rse:
		PolicePrj4ValidateSet_centerClient2rse_del(p->x.centerClient2rse);
		break;
	case Iso14827TestValidateSetPresent_rseServer2center:
		PolicePrj4ValidateSet_rseServer2center_del(p->x.rseServer2center);
		break;
	case Iso14827TestValidateSetPresent_rseClient2center:
		PolicePrj4ValidateSet_rseClient2center_del(p->x.rseClient2center);
		break;
	case Iso14827TestValidateSetPresent_centerServer2rse:
		PolicePrj4ValidateSet_centerServer2rse_del(p->x.centerServer2rse);
		break;
	case Iso14827TestValidateSetPresent_signalserverServer2center:
		PolicePrj4ValidateSet_signalserverServer2center_del(p->x.signalserverServer2center);
		break;
	case Iso14827TestValidateSetPresent_itsk00100_3c2cClient:
		ITSK00100_3ValidateSet_c2cClient_del(p->x.itsk00100_3c2cClient);
		break;
	case Iso14827TestValidateSetPresent_itsk00100_3c2cServer:
		ITSK00100_3ValidateSet_c2cServer_del(p->x.itsk00100_3c2cServer);
		break;
	case Iso14827TestValidateSetPresent_technical_regulation1_clientRole1:
		TechnicalRegulation1ValidateSet_clientRole1_del(p->x.technical_regulation1_clientRole1);
		break;
	case Iso14827TestValidateSetPresent_technical_regulation1_serverRole1:
		TechnicalRegulation1ValidateSet_serverRole1_del(p->x.technical_regulation1_serverRole1);
		break;
	case Iso14827TestValidateSetPresent_technical_regulation2_clientRole1:
		TechnicalRegulation2ValidateSet_clientRole1_del(p->x.technical_regulation2_clientRole1);
		break;
	case Iso14827TestValidateSetPresent_technical_regulation2_serverRole1:
		TechnicalRegulation2ValidateSet_serverRole1_del(p->x.technical_regulation2_serverRole1);
		break;
	default:
		break;
	}
}

void Iso14827TestValidateSet_del(Iso14827TestValidateSet *p)
{
	if (!p) return;
	Iso14827TestValidateSet_purge(p);
	Dz1Free(p);
}

void Iso14827TestValidateSet_dump(Iso14827TestValidateSet *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TestValidateSetPresent_centerClient2rse:
		Dz1Thread_printf(Dz1T("centerClient2rse = ")); PolicePrj4ValidateSet_centerClient2rse_dump(p->x.centerClient2rse, tab); 
		break;
	case Iso14827TestValidateSetPresent_rseServer2center:
		Dz1Thread_printf(Dz1T("rseServer2center = ")); PolicePrj4ValidateSet_rseServer2center_dump(p->x.rseServer2center, tab); 
		break;
	case Iso14827TestValidateSetPresent_rseClient2center:
		Dz1Thread_printf(Dz1T("rseClient2center = ")); PolicePrj4ValidateSet_rseClient2center_dump(p->x.rseClient2center, tab); 
		break;
	case Iso14827TestValidateSetPresent_centerServer2rse:
		Dz1Thread_printf(Dz1T("centerServer2rse = ")); PolicePrj4ValidateSet_centerServer2rse_dump(p->x.centerServer2rse, tab); 
		break;
	case Iso14827TestValidateSetPresent_signalserverServer2center:
		Dz1Thread_printf(Dz1T("signalserverServer2center = ")); PolicePrj4ValidateSet_signalserverServer2center_dump(p->x.signalserverServer2center, tab); 
		break;
	case Iso14827TestValidateSetPresent_itsk00100_3c2cClient:
		Dz1Thread_printf(Dz1T("itsk00100_3c2cClient = ")); ITSK00100_3ValidateSet_c2cClient_dump(p->x.itsk00100_3c2cClient, tab); 
		break;
	case Iso14827TestValidateSetPresent_itsk00100_3c2cServer:
		Dz1Thread_printf(Dz1T("itsk00100_3c2cServer = ")); ITSK00100_3ValidateSet_c2cServer_dump(p->x.itsk00100_3c2cServer, tab); 
		break;
	case Iso14827TestValidateSetPresent_technical_regulation1_clientRole1:
		Dz1Thread_printf(Dz1T("technical_regulation1_clientRole1 = ")); TechnicalRegulation1ValidateSet_clientRole1_dump(p->x.technical_regulation1_clientRole1, tab); 
		break;
	case Iso14827TestValidateSetPresent_technical_regulation1_serverRole1:
		Dz1Thread_printf(Dz1T("technical_regulation1_serverRole1 = ")); TechnicalRegulation1ValidateSet_serverRole1_dump(p->x.technical_regulation1_serverRole1, tab); 
		break;
	case Iso14827TestValidateSetPresent_technical_regulation2_clientRole1:
		Dz1Thread_printf(Dz1T("technical_regulation2_clientRole1 = ")); TechnicalRegulation2ValidateSet_clientRole1_dump(p->x.technical_regulation2_clientRole1, tab); 
		break;
	case Iso14827TestValidateSetPresent_technical_regulation2_serverRole1:
		Dz1Thread_printf(Dz1T("technical_regulation2_serverRole1 = ")); TechnicalRegulation2ValidateSet_serverRole1_dump(p->x.technical_regulation2_serverRole1, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827TestValidateSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRoleSubsEntry
Iso14827TestServerRoleSubsEntry *Iso14827TestServerRoleSubsEntry_new(Dz1Str oid, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServerRoleSubsEntry *__internal_ret = (Iso14827TestServerRoleSubsEntry *)Dz1Calloc(sizeof(Iso14827TestServerRoleSubsEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRoleSubsEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (oid && (__internal_ret->oid = Dz1Str_clone(oid, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRoleSubsEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestServerRoleSubsEntry_copy(Iso14827TestServerRoleSubsEntry *dst, Iso14827TestServerRoleSubsEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->oid && (dst->oid = Dz1Str_clone(src->oid, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestServerRoleSubsEntry *Iso14827TestServerRoleSubsEntry_clone(Iso14827TestServerRoleSubsEntry *src, Dz1Error *err)
{
	Iso14827TestServerRoleSubsEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestServerRoleSubsEntry *)Dz1Calloc(sizeof(Iso14827TestServerRoleSubsEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRoleSubsEntry_delAndSetNull, (void *)&dst);
		if (Iso14827TestServerRoleSubsEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRoleSubsEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestServerRoleSubsEntry_purge(Iso14827TestServerRoleSubsEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->oid);
}

void Iso14827TestServerRoleSubsEntry_del(Iso14827TestServerRoleSubsEntry *p)
{
	if (p == NULL) return;
	Iso14827TestServerRoleSubsEntry_purge(p);
	Dz1Free(p);
}

void Iso14827TestServerRoleSubsEntry_dump(Iso14827TestServerRoleSubsEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("oid = ")); Dz1Str_dump(p->oid, tab); 
	}
}
int Iso14827TestServerRoleSubsEntry_cmp(Iso14827TestServerRoleSubsEntry *a, Iso14827TestServerRoleSubsEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->oid == NULL && b->oid == NULL) ret = 0;
	else if (a->oid == NULL /*&& b->oid != NULL*/) ret = -1;
	else if (/*a->oid != NULL &&*/ b->oid == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->oid, b->oid)) != 0) { }
	return ret;
}
// Iso14827TestServerRoleSubsEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRoleSubsList
static Dz1Error Iso14827TestServerRoleSubsList_add(Iso14827TestServerRoleSubsList *p, Iso14827TestServerRoleSubsEntry *data)
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

static bool_t Iso14827TestServerRoleSubsList_remove(Iso14827TestServerRoleSubsList *p, Iso14827TestServerRoleSubsEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Iso14827TestServerRoleSubsEntry *Iso14827TestServerRoleSubsList_extract(Iso14827TestServerRoleSubsList *p, Iso14827TestServerRoleSubsEntry *key)
{
	return (Iso14827TestServerRoleSubsEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Iso14827TestServerRoleSubsListMkArrArg
{
	Iso14827TestServerRoleSubsEntry **arr;
	unsigned int idx;
} Iso14827TestServerRoleSubsListMkArrArg;

static Dz1Error _Iso14827TestServerRoleSubsList_get_array(void *ptr, Iso14827TestServerRoleSubsEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827TestServerRoleSubsListMkArrArg *arg = (Iso14827TestServerRoleSubsListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Iso14827TestServerRoleSubsEntry **Iso14827TestServerRoleSubsList_get_array(Iso14827TestServerRoleSubsList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Iso14827TestServerRoleSubsEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Iso14827TestServerRoleSubsEntry **)Dz1Calloc(sizeof(Iso14827TestServerRoleSubsEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827TestServerRoleSubsListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Iso14827TestServerRoleSubsList_get_array, (void *)&arg);
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

static Dz1Error Iso14827TestServerRoleSubsList_travelForward(Iso14827TestServerRoleSubsList *p, Dz1Error (*func)(void *ptr, Iso14827TestServerRoleSubsEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Iso14827TestServerRoleSubsList_travelBackward(Iso14827TestServerRoleSubsList *p, Dz1Error (*func)(void *ptr, Iso14827TestServerRoleSubsEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Iso14827TestServerRoleSubsEntry *Iso14827TestServerRoleSubsList_find(Iso14827TestServerRoleSubsList *p, Iso14827TestServerRoleSubsEntry *key)
{
	return (Iso14827TestServerRoleSubsEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Iso14827TestServerRoleSubsList_count(Iso14827TestServerRoleSubsList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Iso14827TestServerRoleSubsList *Iso14827TestServerRoleSubsList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServerRoleSubsList *ret = (Iso14827TestServerRoleSubsList *)Dz1Calloc(sizeof(Iso14827TestServerRoleSubsList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestServerRoleSubsList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Iso14827TestServerRoleSubsEntry_cmp,
				(Dz1DelFunc)Iso14827TestServerRoleSubsEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Iso14827TestServerRoleSubsList_count;
			ret->travel = Iso14827TestServerRoleSubsList_travelForward;
			ret->travelForward = Iso14827TestServerRoleSubsList_travelForward;
			ret->travelBackward = Iso14827TestServerRoleSubsList_travelBackward;
			ret->get_array = Iso14827TestServerRoleSubsList_get_array;
			ret->add = Iso14827TestServerRoleSubsList_add;
			ret->remove = Iso14827TestServerRoleSubsList_remove;
			ret->find = Iso14827TestServerRoleSubsList_find;
			ret->extract = Iso14827TestServerRoleSubsList_extract;
			ret->cmp = Iso14827TestServerRoleSubsEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRoleSubsList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Iso14827TestServerRoleSubsList_clone(void *ptr, Iso14827TestServerRoleSubsEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827TestServerRoleSubsList *p = (Iso14827TestServerRoleSubsList *)ptr;
	Iso14827TestServerRoleSubsEntry *cloned = Iso14827TestServerRoleSubsEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Iso14827TestServerRoleSubsList *Iso14827TestServerRoleSubsList_clone(Iso14827TestServerRoleSubsList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServerRoleSubsList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Iso14827TestServerRoleSubsList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestServerRoleSubsList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Iso14827TestServerRoleSubsList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRoleSubsList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestServerRoleSubsList_purge(Iso14827TestServerRoleSubsList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Iso14827TestServerRoleSubsList_del(Iso14827TestServerRoleSubsList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Iso14827TestServerRoleSubsList_dump(void *ptr, Iso14827TestServerRoleSubsEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Iso14827TestServerRoleSubsEntry_dump(p, tab);
	return err;
}

void Iso14827TestServerRoleSubsList_dump(Iso14827TestServerRoleSubsList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Iso14827TestServerRoleSubsList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestServerRoleSubsList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRoleViolatedSubTest
Iso14827TestServerRoleViolatedSubTest *Iso14827TestServerRoleViolatedSubTest_new(u32_t sub_serial, 
																				 bool_t guaranteed, 
																				 Dz1Str oid, 
																				 s32_t wait_pub_s, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServerRoleViolatedSubTest *__internal_ret = (Iso14827TestServerRoleViolatedSubTest *)Dz1Calloc(sizeof(Iso14827TestServerRoleViolatedSubTest), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRoleViolatedSubTest_delAndSetNull, (void *)&__internal_ret);
		
		if (oid && (__internal_ret->oid = Dz1Str_clone(oid, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->sub_serial = sub_serial;
			__internal_ret->guaranteed = guaranteed;
			__internal_ret->wait_pub_s = wait_pub_s;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRoleViolatedSubTest_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestServerRoleViolatedSubTest_copy(Iso14827TestServerRoleViolatedSubTest *dst, Iso14827TestServerRoleViolatedSubTest *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->oid && (dst->oid = Dz1Str_clone(src->oid, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->sub_serial = src->sub_serial;
		dst->guaranteed = src->guaranteed;
		dst->wait_pub_s = src->wait_pub_s;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestServerRoleViolatedSubTest *Iso14827TestServerRoleViolatedSubTest_clone(Iso14827TestServerRoleViolatedSubTest *src, Dz1Error *err)
{
	Iso14827TestServerRoleViolatedSubTest *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestServerRoleViolatedSubTest *)Dz1Calloc(sizeof(Iso14827TestServerRoleViolatedSubTest), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRoleViolatedSubTest_delAndSetNull, (void *)&dst);
		if (Iso14827TestServerRoleViolatedSubTest_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRoleViolatedSubTest_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestServerRoleViolatedSubTest_purge(Iso14827TestServerRoleViolatedSubTest *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->oid);
}

void Iso14827TestServerRoleViolatedSubTest_del(Iso14827TestServerRoleViolatedSubTest *p)
{
	if (p == NULL) return;
	Iso14827TestServerRoleViolatedSubTest_purge(p);
	Dz1Free(p);
}

void Iso14827TestServerRoleViolatedSubTest_dump(Iso14827TestServerRoleViolatedSubTest *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("sub_serial = ")); Dz1u32_dump(&p->sub_serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("guaranteed = ")); Dz1Bool_dump(&p->guaranteed, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oid = ")); Dz1Str_dump(p->oid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("wait_pub_s = ")); Dz1s32_dump(&p->wait_pub_s, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestServerRoleViolatedSubTest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRole1
Iso14827TestServerRole1 *Iso14827TestServerRole1_new(Dz1Asn1UTF8Str *my_domain, 
													 Dz1Asn1UTF8Str *peer_domain, 
													 Iso14827TestConnection *connection, 
													 bool_t test_session, 
													 bool_t test_login_retry, 
													 Iso14827TestServerRoleSubsList *test_subs, 
													 Iso14827TestValidateSet *validate_set, 
													 bool_t test_request_retry, 
													 bool_t test_invalid_pub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServerRole1 *__internal_ret = (Iso14827TestServerRole1 *)Dz1Calloc(sizeof(Iso14827TestServerRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRole1_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_domain = my_domain;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->connection = connection;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_retry = test_login_retry;
		__internal_ret->test_subs = test_subs;
		__internal_ret->validate_set = validate_set;
		__internal_ret->test_request_retry = test_request_retry;
		__internal_ret->test_invalid_pub = test_invalid_pub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestServerRole1_copy(Iso14827TestServerRole1 *dst, Iso14827TestServerRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Asn1UTF8Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Asn1UTF8Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->connection && (dst->connection = Iso14827TestConnection_clone(src->connection, errp)) == NULL) ERR_OUT(errp);
	else if (src->test_subs && (dst->test_subs = Iso14827TestServerRoleSubsList_clone(src->test_subs, errp)) == NULL) ERR_OUT(errp);
	else if (src->validate_set && (dst->validate_set = Iso14827TestValidateSet_clone(src->validate_set, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->test_session = src->test_session;
		dst->test_login_retry = src->test_login_retry;
		dst->test_request_retry = src->test_request_retry;
		dst->test_invalid_pub = src->test_invalid_pub;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestServerRole1 *Iso14827TestServerRole1_clone(Iso14827TestServerRole1 *src, Dz1Error *err)
{
	Iso14827TestServerRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestServerRole1 *)Dz1Calloc(sizeof(Iso14827TestServerRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRole1_delAndSetNull, (void *)&dst);
		if (Iso14827TestServerRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestServerRole1_purge(Iso14827TestServerRole1 *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->my_domain);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	Iso14827TestConnection_del(p->connection);
	Iso14827TestServerRoleSubsList_del(p->test_subs);
	Iso14827TestValidateSet_del(p->validate_set);
}

void Iso14827TestServerRole1_del(Iso14827TestServerRole1 *p)
{
	if (p == NULL) return;
	Iso14827TestServerRole1_purge(p);
	Dz1Free(p);
}

void Iso14827TestServerRole1_dump(Iso14827TestServerRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Asn1UTF8Str_dump(p->my_domain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("connection.")); Iso14827TestConnection_dump(p->connection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_retry = ")); Dz1Bool_dump(&p->test_login_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs = ")); Iso14827TestServerRoleSubsList_dump(p->test_subs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("validate_set.")); Iso14827TestValidateSet_dump(p->validate_set, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_request_retry = ")); Dz1Bool_dump(&p->test_request_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_pub = ")); Dz1Bool_dump(&p->test_invalid_pub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestServerRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRole2
Iso14827TestServerRole2 *Iso14827TestServerRole2_new(Dz1Asn1UTF8Str *my_domain, 
													 Dz1Asn1UTF8Str *peer_domain, 
													 Iso14827TestConnection *connection, 
													 u32_t subs_timeout_s, 
													 Iso14827PublicationMgmt subs_cancel_reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServerRole2 *__internal_ret = (Iso14827TestServerRole2 *)Dz1Calloc(sizeof(Iso14827TestServerRole2), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRole2_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_domain = my_domain;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->connection = connection;
		__internal_ret->subs_timeout_s = subs_timeout_s;
		__internal_ret->subs_cancel_reason = subs_cancel_reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRole2_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestServerRole2_copy(Iso14827TestServerRole2 *dst, Iso14827TestServerRole2 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Asn1UTF8Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Asn1UTF8Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->connection && (dst->connection = Iso14827TestConnection_clone(src->connection, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subs_timeout_s = src->subs_timeout_s;
		dst->subs_cancel_reason = src->subs_cancel_reason;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestServerRole2 *Iso14827TestServerRole2_clone(Iso14827TestServerRole2 *src, Dz1Error *err)
{
	Iso14827TestServerRole2 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestServerRole2 *)Dz1Calloc(sizeof(Iso14827TestServerRole2), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRole2_delAndSetNull, (void *)&dst);
		if (Iso14827TestServerRole2_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRole2_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestServerRole2_purge(Iso14827TestServerRole2 *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->my_domain);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	Iso14827TestConnection_del(p->connection);
}

void Iso14827TestServerRole2_del(Iso14827TestServerRole2 *p)
{
	if (p == NULL) return;
	Iso14827TestServerRole2_purge(p);
	Dz1Free(p);
}

void Iso14827TestServerRole2_dump(Iso14827TestServerRole2 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Asn1UTF8Str_dump(p->my_domain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("connection.")); Iso14827TestConnection_dump(p->connection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_timeout_s = ")); Dz1u32_dump(&p->subs_timeout_s, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_cancel_reason = %s(%d)\n"), Iso14827PublicationMgmtStr(p->subs_cancel_reason), p->subs_cancel_reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestServerRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestServerRole3
Iso14827TestServerRole3 *Iso14827TestServerRole3_new(Dz1Asn1UTF8Str *my_domain, 
													 Dz1Asn1UTF8Str *peer_domain, 
													 Iso14827TestConnection *connection, 
													 bool_t test_session, 
													 bool_t test_login_retry, 
													 u32_t subs_timeout_s, 
													 Iso14827PublicationMgmt subs_cancel_reason, 
													 Iso14827TestValidateSet *validate_set, 
													 bool_t test_request_retry, 
													 bool_t test_invalid_pub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestServerRole3 *__internal_ret = (Iso14827TestServerRole3 *)Dz1Calloc(sizeof(Iso14827TestServerRole3), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRole3_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_domain = my_domain;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->connection = connection;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_retry = test_login_retry;
		__internal_ret->subs_timeout_s = subs_timeout_s;
		__internal_ret->subs_cancel_reason = subs_cancel_reason;
		__internal_ret->validate_set = validate_set;
		__internal_ret->test_request_retry = test_request_retry;
		__internal_ret->test_invalid_pub = test_invalid_pub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRole3_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestServerRole3_copy(Iso14827TestServerRole3 *dst, Iso14827TestServerRole3 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Asn1UTF8Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Asn1UTF8Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->connection && (dst->connection = Iso14827TestConnection_clone(src->connection, errp)) == NULL) ERR_OUT(errp);
	else if (src->validate_set && (dst->validate_set = Iso14827TestValidateSet_clone(src->validate_set, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->test_session = src->test_session;
		dst->test_login_retry = src->test_login_retry;
		dst->subs_timeout_s = src->subs_timeout_s;
		dst->subs_cancel_reason = src->subs_cancel_reason;
		dst->test_request_retry = src->test_request_retry;
		dst->test_invalid_pub = src->test_invalid_pub;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestServerRole3 *Iso14827TestServerRole3_clone(Iso14827TestServerRole3 *src, Dz1Error *err)
{
	Iso14827TestServerRole3 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestServerRole3 *)Dz1Calloc(sizeof(Iso14827TestServerRole3), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestServerRole3_delAndSetNull, (void *)&dst);
		if (Iso14827TestServerRole3_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestServerRole3_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestServerRole3_purge(Iso14827TestServerRole3 *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->my_domain);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	Iso14827TestConnection_del(p->connection);
	Iso14827TestValidateSet_del(p->validate_set);
}

void Iso14827TestServerRole3_del(Iso14827TestServerRole3 *p)
{
	if (p == NULL) return;
	Iso14827TestServerRole3_purge(p);
	Dz1Free(p);
}

void Iso14827TestServerRole3_dump(Iso14827TestServerRole3 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Asn1UTF8Str_dump(p->my_domain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("connection.")); Iso14827TestConnection_dump(p->connection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_retry = ")); Dz1Bool_dump(&p->test_login_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_timeout_s = ")); Dz1u32_dump(&p->subs_timeout_s, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_cancel_reason = %s(%d)\n"), Iso14827PublicationMgmtStr(p->subs_cancel_reason), p->subs_cancel_reason);
		Dz1Thread_tprintf(tab, Dz1T("validate_set.")); Iso14827TestValidateSet_dump(p->validate_set, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_request_retry = ")); Dz1Bool_dump(&p->test_request_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_pub = ")); Dz1Bool_dump(&p->test_invalid_pub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestServerRole3
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientAccount
Iso14827TestClientAccount *Iso14827TestClientAccount_new(Dz1Asn1UTF8Str *my_domain, 
														 Dz1Asn1OctetStr *authinfo, 
														 Dz1Asn1OctetStr *userid, 
														 Dz1Asn1OctetStr *passwd, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientAccount *__internal_ret = (Iso14827TestClientAccount *)Dz1Calloc(sizeof(Iso14827TestClientAccount), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientAccount_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_domain = my_domain;
		__internal_ret->authinfo = authinfo;
		__internal_ret->userid = userid;
		__internal_ret->passwd = passwd;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientAccount_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestClientAccount_copy(Iso14827TestClientAccount *dst, Iso14827TestClientAccount *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Asn1UTF8Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->authinfo && (dst->authinfo = Dz1Asn1OctetStr_clone(src->authinfo, errp)) == NULL) ERR_OUT(errp);
	else if (src->userid && (dst->userid = Dz1Asn1OctetStr_clone(src->userid, errp)) == NULL) ERR_OUT(errp);
	else if (src->passwd && (dst->passwd = Dz1Asn1OctetStr_clone(src->passwd, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestClientAccount *Iso14827TestClientAccount_clone(Iso14827TestClientAccount *src, Dz1Error *err)
{
	Iso14827TestClientAccount *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestClientAccount *)Dz1Calloc(sizeof(Iso14827TestClientAccount), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientAccount_delAndSetNull, (void *)&dst);
		if (Iso14827TestClientAccount_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientAccount_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestClientAccount_purge(Iso14827TestClientAccount *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->my_domain);
	Dz1Asn1OctetStr_del(p->authinfo);
	Dz1Asn1OctetStr_del(p->userid);
	Dz1Asn1OctetStr_del(p->passwd);
}

void Iso14827TestClientAccount_del(Iso14827TestClientAccount *p)
{
	if (p == NULL) return;
	Iso14827TestClientAccount_purge(p);
	Dz1Free(p);
}

// Iso14827TestClientAccount
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientPassive
Iso14827TestClientPassive *Iso14827TestClientPassive_new(u16_t local_port, 
														 u16_t peer_port, 
														 Iso14827TestClientAccount *account1, 
														 Iso14827TestClientAccount *account2, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientPassive *__internal_ret = (Iso14827TestClientPassive *)Dz1Calloc(sizeof(Iso14827TestClientPassive), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientPassive_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->peer_port = peer_port;
		__internal_ret->account1 = account1;
		__internal_ret->account2 = account2;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientPassive_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestClientPassive_copy(Iso14827TestClientPassive *dst, Iso14827TestClientPassive *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->account1 && (dst->account1 = Iso14827TestClientAccount_clone(src->account1, errp)) == NULL) ERR_OUT(errp);
	else if (src->account2 && (dst->account2 = Iso14827TestClientAccount_clone(src->account2, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->peer_port = src->peer_port;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestClientPassive *Iso14827TestClientPassive_clone(Iso14827TestClientPassive *src, Dz1Error *err)
{
	Iso14827TestClientPassive *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestClientPassive *)Dz1Calloc(sizeof(Iso14827TestClientPassive), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientPassive_delAndSetNull, (void *)&dst);
		if (Iso14827TestClientPassive_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientPassive_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestClientPassive_purge(Iso14827TestClientPassive *p)
{
	if (p == NULL) return;
	Iso14827TestClientAccount_del(p->account1);
	Iso14827TestClientAccount_del(p->account2);
}

void Iso14827TestClientPassive_del(Iso14827TestClientPassive *p)
{
	if (p == NULL) return;
	Iso14827TestClientPassive_purge(p);
	Dz1Free(p);
}

void Iso14827TestClientPassive_dump(Iso14827TestClientPassive *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1u16_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1u16_dump(&p->peer_port, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("account1 = ")); Iso14827TestClientAccount_dump(p->account1, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("account2 = ")); Iso14827TestClientAccount_dump(p->account2, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestClientPassive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientActive
Iso14827TestClientActive *Iso14827TestClientActive_new(ConfTestSocketAddress *peer, 
													   Iso14827TestClientAccount *account1, 
													   Iso14827TestClientAccount *account2, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientActive *__internal_ret = (Iso14827TestClientActive *)Dz1Calloc(sizeof(Iso14827TestClientActive), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientActive_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->account1 = account1;
		__internal_ret->account2 = account2;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientActive_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestClientActive_copy(Iso14827TestClientActive *dst, Iso14827TestClientActive *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->peer && (dst->peer = ConfTestSocketAddress_clone(src->peer, errp)) == NULL) ERR_OUT(errp);
	else if (src->account1 && (dst->account1 = Iso14827TestClientAccount_clone(src->account1, errp)) == NULL) ERR_OUT(errp);
	else if (src->account2 && (dst->account2 = Iso14827TestClientAccount_clone(src->account2, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestClientActive *Iso14827TestClientActive_clone(Iso14827TestClientActive *src, Dz1Error *err)
{
	Iso14827TestClientActive *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestClientActive *)Dz1Calloc(sizeof(Iso14827TestClientActive), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientActive_delAndSetNull, (void *)&dst);
		if (Iso14827TestClientActive_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientActive_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestClientActive_purge(Iso14827TestClientActive *p)
{
	if (p == NULL) return;
	ConfTestSocketAddress_del(p->peer);
	Iso14827TestClientAccount_del(p->account1);
	Iso14827TestClientAccount_del(p->account2);
}

void Iso14827TestClientActive_del(Iso14827TestClientActive *p)
{
	if (p == NULL) return;
	Iso14827TestClientActive_purge(p);
	Dz1Free(p);
}

void Iso14827TestClientActive_dump(Iso14827TestClientActive *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); ConfTestSocketAddress_dump(p->peer, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("account1 = ")); Iso14827TestClientAccount_dump(p->account1, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("account2 = ")); Iso14827TestClientAccount_dump(p->account2, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestClientActive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientConnectionPresent
static struct Iso14827TestClientConnectionPresentMapA
{
	str_t str;
	Iso14827TestClientConnectionPresent v;
} Iso14827TestClientConnectionPresentMapA[] =
{
	{ (char *)"passive", Iso14827TestClientConnectionPresent_passive },
	{ (char *)"active", Iso14827TestClientConnectionPresent_active },
	{ NULL, Iso14827TestClientConnectionPresent_max }
};

str_t Iso14827TestClientConnectionPresentStrA(Iso14827TestClientConnectionPresent v)
{
	struct Iso14827TestClientConnectionPresentMapA *i = NULL;
	for (i = Iso14827TestClientConnectionPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestClientConnectionPresent Iso14827TestClientConnectionPresentFromStrA(str_t str)
{
	struct Iso14827TestClientConnectionPresentMapA *i = NULL;
	for (i = Iso14827TestClientConnectionPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestClientConnectionPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestClientConnectionPresentMapW
{
	wstr_t str;
	Iso14827TestClientConnectionPresent v;
} Iso14827TestClientConnectionPresentMapW[] =
{
	{ (wchar_t *)L"passive", Iso14827TestClientConnectionPresent_passive },
	{ (wchar_t *)L"active", Iso14827TestClientConnectionPresent_active },
	{ NULL, Iso14827TestClientConnectionPresent_max }
};

wstr_t Iso14827TestClientConnectionPresentStrW(Iso14827TestClientConnectionPresent v)
{
	struct Iso14827TestClientConnectionPresentMapW *i = NULL;
	for (i = Iso14827TestClientConnectionPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestClientConnectionPresent Iso14827TestClientConnectionPresentFromStrW(wstr_t str)
{
	struct Iso14827TestClientConnectionPresentMapW *i = NULL;
	for (i = Iso14827TestClientConnectionPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestClientConnectionPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestClientConnectionPresent *Iso14827TestClientConnectionPresent_new(Iso14827TestClientConnectionPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientConnectionPresent *__internal_ret = (Iso14827TestClientConnectionPresent *)Dz1Calloc(sizeof(Iso14827TestClientConnectionPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestClientConnectionPresent_dump(Iso14827TestClientConnectionPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestClientConnectionPresentStr(*v));
}
// Iso14827TestClientConnectionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientConnection
Iso14827TestClientConnection *Iso14827TestClientConnection_new(Iso14827TestClientConnectionPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientConnection *ret = (Iso14827TestClientConnection *)Dz1Calloc(sizeof(Iso14827TestClientConnection), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TestClientConnectionPresent_passive:
			// _U_cst_clone
			if (ptr != NULL) ret->x.passive = (Iso14827TestClientPassive *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestClientConnectionPresent_active:
			// _U_cst_clone
			if (ptr != NULL) ret->x.active = (Iso14827TestClientActive *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestClientConnectionPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientConnection_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827TestClientConnection_copy(Iso14827TestClientConnection *ret, Iso14827TestClientConnection *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827TestClientConnectionPresent_passive:
			// _U_cst_clone
			if (src->x.passive && (ret->x.passive = Iso14827TestClientPassive_clone(src->x.passive, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestClientConnectionPresent_active:
			// _U_cst_clone
			if (src->x.active && (ret->x.active = Iso14827TestClientActive_clone(src->x.active, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestClientConnection *Iso14827TestClientConnection_clone(Iso14827TestClientConnection *src, Dz1Error *err)
{
	Iso14827TestClientConnection *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827TestClientConnection *)Dz1Calloc(sizeof(Iso14827TestClientConnection), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void *)&ret);
		if (Iso14827TestClientConnection_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientConnection_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestClientConnection_purge(Iso14827TestClientConnection *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		Iso14827TestClientPassive_del(p->x.passive);
		break;
	case Iso14827TestClientConnectionPresent_active:
		Iso14827TestClientActive_del(p->x.active);
		break;
	default:
		break;
	}
}

void Iso14827TestClientConnection_del(Iso14827TestClientConnection *p)
{
	if (!p) return;
	Iso14827TestClientConnection_purge(p);
	Dz1Free(p);
}

void Iso14827TestClientConnection_dump(Iso14827TestClientConnection *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		Dz1Thread_printf(Dz1T("passive = ")); Iso14827TestClientPassive_dump(p->x.passive, tab); 
		break;
	case Iso14827TestClientConnectionPresent_active:
		Dz1Thread_printf(Dz1T("active = ")); Iso14827TestClientActive_dump(p->x.active, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827TestClientConnection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientRole1
Iso14827TestClientRole1 *Iso14827TestClientRole1_new(Iso14827TestClientConnection *connection, 
													 Dz1Asn1UTF8Str *peer_domain, 
													 bool_t test_session, 
													 bool_t test_login_invalid, 
													 bool_t test_login_duplicate, 
													 bool_t test_session_maintain, 
													 bool_t test_normal_pub, 
													 Iso14827TestValidateSet *validate_set, 
													 SubscribeSpecList *subs_invalid_list, 
													 SubscribeSpecList *subs_normal_list, 
													 SubscribeSpecEntry *subs_cancel, 
													 SubscribeSpecEntry *subs_pub_retry, 
													 Iso14827SubscriptionCancel subs_cancel_reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientRole1 *__internal_ret = (Iso14827TestClientRole1 *)Dz1Calloc(sizeof(Iso14827TestClientRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientRole1_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->connection = connection;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_invalid = test_login_invalid;
		__internal_ret->test_login_duplicate = test_login_duplicate;
		__internal_ret->test_session_maintain = test_session_maintain;
		__internal_ret->test_normal_pub = test_normal_pub;
		__internal_ret->validate_set = validate_set;
		__internal_ret->subs_invalid_list = subs_invalid_list;
		__internal_ret->subs_normal_list = subs_normal_list;
		__internal_ret->subs_cancel = subs_cancel;
		__internal_ret->subs_pub_retry = subs_pub_retry;
		__internal_ret->subs_cancel_reason = subs_cancel_reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestClientRole1_copy(Iso14827TestClientRole1 *dst, Iso14827TestClientRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->connection && (dst->connection = Iso14827TestClientConnection_clone(src->connection, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Asn1UTF8Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->validate_set && (dst->validate_set = Iso14827TestValidateSet_clone(src->validate_set, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_invalid_list && (dst->subs_invalid_list = SubscribeSpecList_clone(src->subs_invalid_list, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_normal_list && (dst->subs_normal_list = SubscribeSpecList_clone(src->subs_normal_list, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_cancel && (dst->subs_cancel = SubscribeSpecEntry_clone(src->subs_cancel, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_pub_retry && (dst->subs_pub_retry = SubscribeSpecEntry_clone(src->subs_pub_retry, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->test_session = src->test_session;
		dst->test_login_invalid = src->test_login_invalid;
		dst->test_login_duplicate = src->test_login_duplicate;
		dst->test_session_maintain = src->test_session_maintain;
		dst->test_normal_pub = src->test_normal_pub;
		dst->subs_cancel_reason = src->subs_cancel_reason;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestClientRole1 *Iso14827TestClientRole1_clone(Iso14827TestClientRole1 *src, Dz1Error *err)
{
	Iso14827TestClientRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestClientRole1 *)Dz1Calloc(sizeof(Iso14827TestClientRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientRole1_delAndSetNull, (void *)&dst);
		if (Iso14827TestClientRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestClientRole1_purge(Iso14827TestClientRole1 *p)
{
	if (p == NULL) return;
	Iso14827TestClientConnection_del(p->connection);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	Iso14827TestValidateSet_del(p->validate_set);
	SubscribeSpecList_del(p->subs_invalid_list);
	SubscribeSpecList_del(p->subs_normal_list);
	SubscribeSpecEntry_del(p->subs_cancel);
	SubscribeSpecEntry_del(p->subs_pub_retry);
}

void Iso14827TestClientRole1_del(Iso14827TestClientRole1 *p)
{
	if (p == NULL) return;
	Iso14827TestClientRole1_purge(p);
	Dz1Free(p);
}

void Iso14827TestClientRole1_dump(Iso14827TestClientRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("connection.")); Iso14827TestClientConnection_dump(p->connection, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_invalid = ")); Dz1Bool_dump(&p->test_login_invalid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_duplicate = ")); Dz1Bool_dump(&p->test_login_duplicate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_normal_pub = ")); Dz1Bool_dump(&p->test_normal_pub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("validate_set.")); Iso14827TestValidateSet_dump(p->validate_set, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_invalid_list = ")); SubscribeSpecList_dump(p->subs_invalid_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_normal_list = ")); SubscribeSpecList_dump(p->subs_normal_list, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("subs_cancel = ")); SubscribeSpecEntry_dump(p->subs_cancel, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("subs_pub_retry = ")); SubscribeSpecEntry_dump(p->subs_pub_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_cancel_reason = %s(%d)\n"), Iso14827SubscriptionCancelStr(p->subs_cancel_reason), p->subs_cancel_reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestClientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientRole1TR
Iso14827TestClientRole1TR *Iso14827TestClientRole1TR_new(Iso14827TestClientConnection *connection, 
														 Dz1Asn1UTF8Str *peer_domain, 
														 bool_t test_session, 
														 bool_t test_login_invalid, 
														 bool_t test_login_duplicate, 
														 bool_t test_session_maintain, 
														 bool_t test_normal_pub, 
														 Iso14827TestValidateSet *validate_set, 
														 SubscribeSpecList *subs_invalid_list, 
														 SubscribeSpecList *subs_normal_list, 
														 SubscribeSpecEntry *subs_cancel, 
														 SubscribeSpecEntry *subs_pub_retry, 
														 Iso14827SubscriptionCancel subs_cancel_reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientRole1TR *__internal_ret = (Iso14827TestClientRole1TR *)Dz1Calloc(sizeof(Iso14827TestClientRole1TR), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientRole1TR_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->connection = connection;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_invalid = test_login_invalid;
		__internal_ret->test_login_duplicate = test_login_duplicate;
		__internal_ret->test_session_maintain = test_session_maintain;
		__internal_ret->test_normal_pub = test_normal_pub;
		__internal_ret->validate_set = validate_set;
		__internal_ret->subs_invalid_list = subs_invalid_list;
		__internal_ret->subs_normal_list = subs_normal_list;
		__internal_ret->subs_cancel = subs_cancel;
		__internal_ret->subs_pub_retry = subs_pub_retry;
		__internal_ret->subs_cancel_reason = subs_cancel_reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientRole1TR_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestClientRole1TR_copy(Iso14827TestClientRole1TR *dst, Iso14827TestClientRole1TR *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->connection && (dst->connection = Iso14827TestClientConnection_clone(src->connection, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Asn1UTF8Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->validate_set && (dst->validate_set = Iso14827TestValidateSet_clone(src->validate_set, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_invalid_list && (dst->subs_invalid_list = SubscribeSpecList_clone(src->subs_invalid_list, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_normal_list && (dst->subs_normal_list = SubscribeSpecList_clone(src->subs_normal_list, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_cancel && (dst->subs_cancel = SubscribeSpecEntry_clone(src->subs_cancel, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_pub_retry && (dst->subs_pub_retry = SubscribeSpecEntry_clone(src->subs_pub_retry, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->test_session = src->test_session;
		dst->test_login_invalid = src->test_login_invalid;
		dst->test_login_duplicate = src->test_login_duplicate;
		dst->test_session_maintain = src->test_session_maintain;
		dst->test_normal_pub = src->test_normal_pub;
		dst->subs_cancel_reason = src->subs_cancel_reason;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestClientRole1TR *Iso14827TestClientRole1TR_clone(Iso14827TestClientRole1TR *src, Dz1Error *err)
{
	Iso14827TestClientRole1TR *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestClientRole1TR *)Dz1Calloc(sizeof(Iso14827TestClientRole1TR), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientRole1TR_delAndSetNull, (void *)&dst);
		if (Iso14827TestClientRole1TR_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientRole1TR_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestClientRole1TR_purge(Iso14827TestClientRole1TR *p)
{
	if (p == NULL) return;
	Iso14827TestClientConnection_del(p->connection);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	Iso14827TestValidateSet_del(p->validate_set);
	SubscribeSpecList_del(p->subs_invalid_list);
	SubscribeSpecList_del(p->subs_normal_list);
	SubscribeSpecEntry_del(p->subs_cancel);
	SubscribeSpecEntry_del(p->subs_pub_retry);
}

void Iso14827TestClientRole1TR_del(Iso14827TestClientRole1TR *p)
{
	if (p == NULL) return;
	Iso14827TestClientRole1TR_purge(p);
	Dz1Free(p);
}

void Iso14827TestClientRole1TR_dump(Iso14827TestClientRole1TR *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("connection.")); Iso14827TestClientConnection_dump(p->connection, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_invalid = ")); Dz1Bool_dump(&p->test_login_invalid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_duplicate = ")); Dz1Bool_dump(&p->test_login_duplicate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_normal_pub = ")); Dz1Bool_dump(&p->test_normal_pub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("validate_set.")); Iso14827TestValidateSet_dump(p->validate_set, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_invalid_list = ")); SubscribeSpecList_dump(p->subs_invalid_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_normal_list = ")); SubscribeSpecList_dump(p->subs_normal_list, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("subs_cancel = ")); SubscribeSpecEntry_dump(p->subs_cancel, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("subs_pub_retry = ")); SubscribeSpecEntry_dump(p->subs_pub_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_cancel_reason = %s(%d)\n"), Iso14827SubscriptionCancelStr(p->subs_cancel_reason), p->subs_cancel_reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestClientRole1TR
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestClientRole2
Iso14827TestClientRole2 *Iso14827TestClientRole2_new(Iso14827TestClientConnection *connection, 
													 Dz1Asn1UTF8Str *peer_domain, 
													 SubscribeSpecList *subs_total_list, 
													 u32_t expireTime, 
													 Iso14827SubscriptionCancel subs_cancel_reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestClientRole2 *__internal_ret = (Iso14827TestClientRole2 *)Dz1Calloc(sizeof(Iso14827TestClientRole2), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientRole2_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->connection = connection;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->subs_total_list = subs_total_list;
		__internal_ret->expireTime = expireTime;
		__internal_ret->subs_cancel_reason = subs_cancel_reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientRole2_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestClientRole2_copy(Iso14827TestClientRole2 *dst, Iso14827TestClientRole2 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->connection && (dst->connection = Iso14827TestClientConnection_clone(src->connection, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Asn1UTF8Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_total_list && (dst->subs_total_list = SubscribeSpecList_clone(src->subs_total_list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->expireTime = src->expireTime;
		dst->subs_cancel_reason = src->subs_cancel_reason;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestClientRole2 *Iso14827TestClientRole2_clone(Iso14827TestClientRole2 *src, Dz1Error *err)
{
	Iso14827TestClientRole2 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestClientRole2 *)Dz1Calloc(sizeof(Iso14827TestClientRole2), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestClientRole2_delAndSetNull, (void *)&dst);
		if (Iso14827TestClientRole2_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestClientRole2_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestClientRole2_purge(Iso14827TestClientRole2 *p)
{
	if (p == NULL) return;
	Iso14827TestClientConnection_del(p->connection);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	SubscribeSpecList_del(p->subs_total_list);
}

void Iso14827TestClientRole2_del(Iso14827TestClientRole2 *p)
{
	if (p == NULL) return;
	Iso14827TestClientRole2_purge(p);
	Dz1Free(p);
}

void Iso14827TestClientRole2_dump(Iso14827TestClientRole2 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("connection.")); Iso14827TestClientConnection_dump(p->connection, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_total_list = ")); SubscribeSpecList_dump(p->subs_total_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("expireTime = ")); Dz1u32_dump(&p->expireTime, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_cancel_reason = %s(%d)\n"), Iso14827SubscriptionCancelStr(p->subs_cancel_reason), p->subs_cancel_reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestClientRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoClientRole
Iso14827TestDuoClientRole *Iso14827TestDuoClientRole_new(Iso14827TestClientConnection *connection, 
														 Dz1Asn1UTF8Str *peer_domain, 
														 SubscribeSpecDuo *subs_duo, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestDuoClientRole *__internal_ret = (Iso14827TestDuoClientRole *)Dz1Calloc(sizeof(Iso14827TestDuoClientRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestDuoClientRole_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->connection = connection;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->subs_duo = subs_duo;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestDuoClientRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestDuoClientRole_copy(Iso14827TestDuoClientRole *dst, Iso14827TestDuoClientRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->connection && (dst->connection = Iso14827TestClientConnection_clone(src->connection, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Asn1UTF8Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->subs_duo && (dst->subs_duo = SubscribeSpecDuo_clone(src->subs_duo, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestDuoClientRole *Iso14827TestDuoClientRole_clone(Iso14827TestDuoClientRole *src, Dz1Error *err)
{
	Iso14827TestDuoClientRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestDuoClientRole *)Dz1Calloc(sizeof(Iso14827TestDuoClientRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestDuoClientRole_delAndSetNull, (void *)&dst);
		if (Iso14827TestDuoClientRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestDuoClientRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestDuoClientRole_purge(Iso14827TestDuoClientRole *p)
{
	if (p == NULL) return;
	Iso14827TestClientConnection_del(p->connection);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	SubscribeSpecDuo_del(p->subs_duo);
}

void Iso14827TestDuoClientRole_del(Iso14827TestDuoClientRole *p)
{
	if (p == NULL) return;
	Iso14827TestDuoClientRole_purge(p);
	Dz1Free(p);
}

void Iso14827TestDuoClientRole_dump(Iso14827TestDuoClientRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("connection.")); Iso14827TestClientConnection_dump(p->connection, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("subs_duo = ")); SubscribeSpecDuo_dump(p->subs_duo, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestDuoClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestAccount
Iso14827TestAccount *Iso14827TestAccount_new(Dz1Asn1OctetStr *authinfo, 
											 Dz1Asn1OctetStr *userid, 
											 Dz1Asn1OctetStr *passwd, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestAccount *__internal_ret = (Iso14827TestAccount *)Dz1Calloc(sizeof(Iso14827TestAccount), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestAccount_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->authinfo = authinfo;
		__internal_ret->userid = userid;
		__internal_ret->passwd = passwd;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestAccount_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestAccount_copy(Iso14827TestAccount *dst, Iso14827TestAccount *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->authinfo && (dst->authinfo = Dz1Asn1OctetStr_clone(src->authinfo, errp)) == NULL) ERR_OUT(errp);
	else if (src->userid && (dst->userid = Dz1Asn1OctetStr_clone(src->userid, errp)) == NULL) ERR_OUT(errp);
	else if (src->passwd && (dst->passwd = Dz1Asn1OctetStr_clone(src->passwd, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestAccount *Iso14827TestAccount_clone(Iso14827TestAccount *src, Dz1Error *err)
{
	Iso14827TestAccount *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestAccount *)Dz1Calloc(sizeof(Iso14827TestAccount), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestAccount_delAndSetNull, (void *)&dst);
		if (Iso14827TestAccount_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestAccount_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestAccount_purge(Iso14827TestAccount *p)
{
	if (p == NULL) return;
	Dz1Asn1OctetStr_del(p->authinfo);
	Dz1Asn1OctetStr_del(p->userid);
	Dz1Asn1OctetStr_del(p->passwd);
}

void Iso14827TestAccount_del(Iso14827TestAccount *p)
{
	if (p == NULL) return;
	Iso14827TestAccount_purge(p);
	Dz1Free(p);
}

void Iso14827TestAccount_dump(Iso14827TestAccount *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("authinfo = ")); Dz1Asn1OctetStr_dump(p->authinfo, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("userid = ")); Dz1Asn1OctetStr_dump(p->userid, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("passwd = ")); Dz1Asn1OctetStr_dump(p->passwd, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestAccount
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestDuoSessionRole
Iso14827TestDuoSessionRole *Iso14827TestDuoSessionRole_new(Dz1Asn1UTF8Str *my_domain, 
														   Dz1Asn1UTF8Str *peer_server_domain, 
														   Iso14827TestConnection *c_peer_server, 
														   Iso14827TestAccount *c_account, 
														   SubscribeSpecEntry *c_sub, 
														   Dz1Asn1UTF8Str *peer_client_domain, 
														   Iso14827TestConnection *s_peer_client, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestDuoSessionRole *__internal_ret = (Iso14827TestDuoSessionRole *)Dz1Calloc(sizeof(Iso14827TestDuoSessionRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestDuoSessionRole_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_domain = my_domain;
		__internal_ret->peer_server_domain = peer_server_domain;
		__internal_ret->c_peer_server = c_peer_server;
		__internal_ret->c_account = c_account;
		__internal_ret->c_sub = c_sub;
		__internal_ret->peer_client_domain = peer_client_domain;
		__internal_ret->s_peer_client = s_peer_client;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestDuoSessionRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestDuoSessionRole_copy(Iso14827TestDuoSessionRole *dst, Iso14827TestDuoSessionRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Asn1UTF8Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_server_domain && (dst->peer_server_domain = Dz1Asn1UTF8Str_clone(src->peer_server_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->c_peer_server && (dst->c_peer_server = Iso14827TestConnection_clone(src->c_peer_server, errp)) == NULL) ERR_OUT(errp);
	else if (src->c_account && (dst->c_account = Iso14827TestAccount_clone(src->c_account, errp)) == NULL) ERR_OUT(errp);
	else if (src->c_sub && (dst->c_sub = SubscribeSpecEntry_clone(src->c_sub, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_client_domain && (dst->peer_client_domain = Dz1Asn1UTF8Str_clone(src->peer_client_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->s_peer_client && (dst->s_peer_client = Iso14827TestConnection_clone(src->s_peer_client, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestDuoSessionRole *Iso14827TestDuoSessionRole_clone(Iso14827TestDuoSessionRole *src, Dz1Error *err)
{
	Iso14827TestDuoSessionRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestDuoSessionRole *)Dz1Calloc(sizeof(Iso14827TestDuoSessionRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestDuoSessionRole_delAndSetNull, (void *)&dst);
		if (Iso14827TestDuoSessionRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestDuoSessionRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestDuoSessionRole_purge(Iso14827TestDuoSessionRole *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->my_domain);
	Dz1Asn1UTF8Str_del(p->peer_server_domain);
	Iso14827TestConnection_del(p->c_peer_server);
	Iso14827TestAccount_del(p->c_account);
	SubscribeSpecEntry_del(p->c_sub);
	Dz1Asn1UTF8Str_del(p->peer_client_domain);
	Iso14827TestConnection_del(p->s_peer_client);
}

void Iso14827TestDuoSessionRole_del(Iso14827TestDuoSessionRole *p)
{
	if (p == NULL) return;
	Iso14827TestDuoSessionRole_purge(p);
	Dz1Free(p);
}

void Iso14827TestDuoSessionRole_dump(Iso14827TestDuoSessionRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Asn1UTF8Str_dump(p->my_domain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_server_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_server_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("c_peer_server.")); Iso14827TestConnection_dump(p->c_peer_server, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("c_account = ")); Iso14827TestAccount_dump(p->c_account, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("c_sub = ")); SubscribeSpecEntry_dump(p->c_sub, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_client_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_client_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("s_peer_client.")); Iso14827TestConnection_dump(p->s_peer_client, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestDuoSessionRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestScenarioPresent
static struct Iso14827TestScenarioPresentMapA
{
	str_t str;
	Iso14827TestScenarioPresent v;
} Iso14827TestScenarioPresentMapA[] =
{
	{ (char *)"server1", Iso14827TestScenarioPresent_server1 },
	{ (char *)"server2", Iso14827TestScenarioPresent_server2 },
	{ (char *)"server3", Iso14827TestScenarioPresent_server3 },
	{ (char *)"client1", Iso14827TestScenarioPresent_client1 },
	{ (char *)"client2", Iso14827TestScenarioPresent_client2 },
	{ (char *)"duo_client", Iso14827TestScenarioPresent_duo_client },
	{ (char *)"duo_session", Iso14827TestScenarioPresent_duo_session },
	{ (char *)"client1_tr", Iso14827TestScenarioPresent_client1_tr },
	{ NULL, Iso14827TestScenarioPresent_max }
};

str_t Iso14827TestScenarioPresentStrA(Iso14827TestScenarioPresent v)
{
	struct Iso14827TestScenarioPresentMapA *i = NULL;
	for (i = Iso14827TestScenarioPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestScenarioPresent Iso14827TestScenarioPresentFromStrA(str_t str)
{
	struct Iso14827TestScenarioPresentMapA *i = NULL;
	for (i = Iso14827TestScenarioPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestScenarioPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestScenarioPresentMapW
{
	wstr_t str;
	Iso14827TestScenarioPresent v;
} Iso14827TestScenarioPresentMapW[] =
{
	{ (wchar_t *)L"server1", Iso14827TestScenarioPresent_server1 },
	{ (wchar_t *)L"server2", Iso14827TestScenarioPresent_server2 },
	{ (wchar_t *)L"server3", Iso14827TestScenarioPresent_server3 },
	{ (wchar_t *)L"client1", Iso14827TestScenarioPresent_client1 },
	{ (wchar_t *)L"client2", Iso14827TestScenarioPresent_client2 },
	{ (wchar_t *)L"duo_client", Iso14827TestScenarioPresent_duo_client },
	{ (wchar_t *)L"duo_session", Iso14827TestScenarioPresent_duo_session },
	{ (wchar_t *)L"client1_tr", Iso14827TestScenarioPresent_client1_tr },
	{ NULL, Iso14827TestScenarioPresent_max }
};

wstr_t Iso14827TestScenarioPresentStrW(Iso14827TestScenarioPresent v)
{
	struct Iso14827TestScenarioPresentMapW *i = NULL;
	for (i = Iso14827TestScenarioPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestScenarioPresent Iso14827TestScenarioPresentFromStrW(wstr_t str)
{
	struct Iso14827TestScenarioPresentMapW *i = NULL;
	for (i = Iso14827TestScenarioPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestScenarioPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestScenarioPresent *Iso14827TestScenarioPresent_new(Iso14827TestScenarioPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestScenarioPresent *__internal_ret = (Iso14827TestScenarioPresent *)Dz1Calloc(sizeof(Iso14827TestScenarioPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestScenarioPresent_dump(Iso14827TestScenarioPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestScenarioPresentStr(*v));
}
// Iso14827TestScenarioPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestScenario
Iso14827TestScenario *Iso14827TestScenario_new(Iso14827TestScenarioPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestScenario *ret = (Iso14827TestScenario *)Dz1Calloc(sizeof(Iso14827TestScenario), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestScenario_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TestScenarioPresent_server1:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server1 = (Iso14827TestServerRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestScenarioPresent_server2:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server2 = (Iso14827TestServerRole2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestScenarioPresent_server3:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server3 = (Iso14827TestServerRole3 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestScenarioPresent_client1:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client1 = (Iso14827TestClientRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestScenarioPresent_client2:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client2 = (Iso14827TestClientRole2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestScenarioPresent_duo_client:
			// _U_cst_clone
			if (ptr != NULL) ret->x.duo_client = (Iso14827TestDuoClientRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestScenarioPresent_duo_session:
			// _U_cst_clone
			if (ptr != NULL) ret->x.duo_session = (Iso14827TestDuoSessionRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestScenarioPresent_client1_tr:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client1_tr = (Iso14827TestClientRole1TR *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestScenarioPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestScenario_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827TestScenario_copy(Iso14827TestScenario *ret, Iso14827TestScenario *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827TestScenarioPresent_server1:
			// _U_cst_clone
			if (src->x.server1 && (ret->x.server1 = Iso14827TestServerRole1_clone(src->x.server1, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestScenarioPresent_server2:
			// _U_cst_clone
			if (src->x.server2 && (ret->x.server2 = Iso14827TestServerRole2_clone(src->x.server2, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestScenarioPresent_server3:
			// _U_cst_clone
			if (src->x.server3 && (ret->x.server3 = Iso14827TestServerRole3_clone(src->x.server3, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestScenarioPresent_client1:
			// _U_cst_clone
			if (src->x.client1 && (ret->x.client1 = Iso14827TestClientRole1_clone(src->x.client1, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestScenarioPresent_client2:
			// _U_cst_clone
			if (src->x.client2 && (ret->x.client2 = Iso14827TestClientRole2_clone(src->x.client2, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestScenarioPresent_duo_client:
			// _U_cst_clone
			if (src->x.duo_client && (ret->x.duo_client = Iso14827TestDuoClientRole_clone(src->x.duo_client, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestScenarioPresent_duo_session:
			// _U_cst_clone
			if (src->x.duo_session && (ret->x.duo_session = Iso14827TestDuoSessionRole_clone(src->x.duo_session, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestScenarioPresent_client1_tr:
			// _U_cst_clone
			if (src->x.client1_tr && (ret->x.client1_tr = Iso14827TestClientRole1TR_clone(src->x.client1_tr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestScenario *Iso14827TestScenario_clone(Iso14827TestScenario *src, Dz1Error *err)
{
	Iso14827TestScenario *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827TestScenario *)Dz1Calloc(sizeof(Iso14827TestScenario), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestScenario_delAndSetNull, (void *)&ret);
		if (Iso14827TestScenario_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestScenario_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestScenario_purge(Iso14827TestScenario *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TestScenarioPresent_server1:
		Iso14827TestServerRole1_del(p->x.server1);
		break;
	case Iso14827TestScenarioPresent_server2:
		Iso14827TestServerRole2_del(p->x.server2);
		break;
	case Iso14827TestScenarioPresent_server3:
		Iso14827TestServerRole3_del(p->x.server3);
		break;
	case Iso14827TestScenarioPresent_client1:
		Iso14827TestClientRole1_del(p->x.client1);
		break;
	case Iso14827TestScenarioPresent_client2:
		Iso14827TestClientRole2_del(p->x.client2);
		break;
	case Iso14827TestScenarioPresent_duo_client:
		Iso14827TestDuoClientRole_del(p->x.duo_client);
		break;
	case Iso14827TestScenarioPresent_duo_session:
		Iso14827TestDuoSessionRole_del(p->x.duo_session);
		break;
	case Iso14827TestScenarioPresent_client1_tr:
		Iso14827TestClientRole1TR_del(p->x.client1_tr);
		break;
	default:
		break;
	}
}

void Iso14827TestScenario_del(Iso14827TestScenario *p)
{
	if (!p) return;
	Iso14827TestScenario_purge(p);
	Dz1Free(p);
}

void Iso14827TestScenario_dump(Iso14827TestScenario *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TestScenarioPresent_server1:
		Dz1Thread_printf(Dz1T("server1 = ")); Iso14827TestServerRole1_dump(p->x.server1, tab); 
		break;
	case Iso14827TestScenarioPresent_server2:
		Dz1Thread_printf(Dz1T("server2 = ")); Iso14827TestServerRole2_dump(p->x.server2, tab); 
		break;
	case Iso14827TestScenarioPresent_server3:
		Dz1Thread_printf(Dz1T("server3 = ")); Iso14827TestServerRole3_dump(p->x.server3, tab); 
		break;
	case Iso14827TestScenarioPresent_client1:
		Dz1Thread_printf(Dz1T("client1 = ")); Iso14827TestClientRole1_dump(p->x.client1, tab); 
		break;
	case Iso14827TestScenarioPresent_client2:
		Dz1Thread_printf(Dz1T("client2 = ")); Iso14827TestClientRole2_dump(p->x.client2, tab); 
		break;
	case Iso14827TestScenarioPresent_duo_client:
		Dz1Thread_printf(Dz1T("duo_client = ")); Iso14827TestDuoClientRole_dump(p->x.duo_client, tab); 
		break;
	case Iso14827TestScenarioPresent_duo_session:
		Dz1Thread_printf(Dz1T("duo_session = ")); Iso14827TestDuoSessionRole_dump(p->x.duo_session, tab); 
		break;
	case Iso14827TestScenarioPresent_client1_tr:
		Dz1Thread_printf(Dz1T("client1_tr = ")); Iso14827TestClientRole1TR_dump(p->x.client1_tr, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827TestScenario
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestProcessStatusCode
static struct Iso14827TestProcessStatusCodeMapA
{
	str_t str;
	Iso14827TestProcessStatusCode v;
} Iso14827TestProcessStatusCodeMapA[] =
{
	{ (char *)"OK", Iso14827TestProcessStatusCode_OK },
	{ (char *)"FAILURE", Iso14827TestProcessStatusCode_FAILURE },
	{ (char *)"AGENT_SYSTEM_ERROR", Iso14827TestProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (char *)"SERVER_DISCONNECTED", Iso14827TestProcessStatusCode_SERVER_DISCONNECTED },
	{ (char *)"TEST_CONFIGURATION_ERROR", Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (char *)"CONNECTION_FAIL", Iso14827TestProcessStatusCode_CONNECTION_FAIL },
	{ (char *)"DISCONNECTED", Iso14827TestProcessStatusCode_DISCONNECTED },
	{ (char *)"TIMEOUT", Iso14827TestProcessStatusCode_TIMEOUT },
	{ (char *)"OUT_OF_RANGE", Iso14827TestProcessStatusCode_OUT_OF_RANGE },
	{ (char *)"INVALID_PROCESS", Iso14827TestProcessStatusCode_INVALID_PROCESS },
	{ (char *)"INVALID_IDENTIFIER", Iso14827TestProcessStatusCode_INVALID_IDENTIFIER },
	{ (char *)"SESSION_DUPLICATE", Iso14827TestProcessStatusCode_SESSION_DUPLICATE },
	{ (char *)"DECODE_FAIL", Iso14827TestProcessStatusCode_DECODE_FAIL },
	{ (char *)"INVALID_ENCODING_RULE", Iso14827TestProcessStatusCode_INVALID_ENCODING_RULE },
	{ (char *)"INVALID_OID", Iso14827TestProcessStatusCode_INVALID_OID },
	{ (char *)"INVALID_DSRC_MSG_ID", Iso14827TestProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (char *)"JSON_PARSE_ERROR", Iso14827TestProcessStatusCode_JSON_PARSE_ERROR },
	{ (char *)"PROTOBUF_DESERAILIZE_ERROR", Iso14827TestProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (char *)"INVALID_TOPIC", Iso14827TestProcessStatusCode_INVALID_TOPIC },
	{ (char *)"UNKNOWN", Iso14827TestProcessStatusCode_UNKNOWN },
	{ NULL, Iso14827TestProcessStatusCode_max }
};

str_t Iso14827TestProcessStatusCodeStrA(Iso14827TestProcessStatusCode v)
{
	struct Iso14827TestProcessStatusCodeMapA *i = NULL;
	for (i = Iso14827TestProcessStatusCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestProcessStatusCode Iso14827TestProcessStatusCodeFromStrA(str_t str)
{
	struct Iso14827TestProcessStatusCodeMapA *i = NULL;
	for (i = Iso14827TestProcessStatusCodeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestProcessStatusCode_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestProcessStatusCodeMapW
{
	wstr_t str;
	Iso14827TestProcessStatusCode v;
} Iso14827TestProcessStatusCodeMapW[] =
{
	{ (wchar_t *)L"OK", Iso14827TestProcessStatusCode_OK },
	{ (wchar_t *)L"FAILURE", Iso14827TestProcessStatusCode_FAILURE },
	{ (wchar_t *)L"AGENT_SYSTEM_ERROR", Iso14827TestProcessStatusCode_AGENT_SYSTEM_ERROR },
	{ (wchar_t *)L"SERVER_DISCONNECTED", Iso14827TestProcessStatusCode_SERVER_DISCONNECTED },
	{ (wchar_t *)L"TEST_CONFIGURATION_ERROR", Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR },
	{ (wchar_t *)L"CONNECTION_FAIL", Iso14827TestProcessStatusCode_CONNECTION_FAIL },
	{ (wchar_t *)L"DISCONNECTED", Iso14827TestProcessStatusCode_DISCONNECTED },
	{ (wchar_t *)L"TIMEOUT", Iso14827TestProcessStatusCode_TIMEOUT },
	{ (wchar_t *)L"OUT_OF_RANGE", Iso14827TestProcessStatusCode_OUT_OF_RANGE },
	{ (wchar_t *)L"INVALID_PROCESS", Iso14827TestProcessStatusCode_INVALID_PROCESS },
	{ (wchar_t *)L"INVALID_IDENTIFIER", Iso14827TestProcessStatusCode_INVALID_IDENTIFIER },
	{ (wchar_t *)L"SESSION_DUPLICATE", Iso14827TestProcessStatusCode_SESSION_DUPLICATE },
	{ (wchar_t *)L"DECODE_FAIL", Iso14827TestProcessStatusCode_DECODE_FAIL },
	{ (wchar_t *)L"INVALID_ENCODING_RULE", Iso14827TestProcessStatusCode_INVALID_ENCODING_RULE },
	{ (wchar_t *)L"INVALID_OID", Iso14827TestProcessStatusCode_INVALID_OID },
	{ (wchar_t *)L"INVALID_DSRC_MSG_ID", Iso14827TestProcessStatusCode_INVALID_DSRC_MSG_ID },
	{ (wchar_t *)L"JSON_PARSE_ERROR", Iso14827TestProcessStatusCode_JSON_PARSE_ERROR },
	{ (wchar_t *)L"PROTOBUF_DESERAILIZE_ERROR", Iso14827TestProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR },
	{ (wchar_t *)L"INVALID_TOPIC", Iso14827TestProcessStatusCode_INVALID_TOPIC },
	{ (wchar_t *)L"UNKNOWN", Iso14827TestProcessStatusCode_UNKNOWN },
	{ NULL, Iso14827TestProcessStatusCode_max }
};

wstr_t Iso14827TestProcessStatusCodeStrW(Iso14827TestProcessStatusCode v)
{
	struct Iso14827TestProcessStatusCodeMapW *i = NULL;
	for (i = Iso14827TestProcessStatusCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestProcessStatusCode Iso14827TestProcessStatusCodeFromStrW(wstr_t str)
{
	struct Iso14827TestProcessStatusCodeMapW *i = NULL;
	for (i = Iso14827TestProcessStatusCodeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestProcessStatusCode_max;
}
#endif // UNIX_SYSTEM

Iso14827TestProcessStatusCode *Iso14827TestProcessStatusCode_new(Iso14827TestProcessStatusCode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestProcessStatusCode *__internal_ret = (Iso14827TestProcessStatusCode *)Dz1Calloc(sizeof(Iso14827TestProcessStatusCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestProcessStatusCode_dump(Iso14827TestProcessStatusCode *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestProcessStatusCodeStr(*v));
}
// Iso14827TestProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyStateContext
Iso14827TestNotifyStateContext *Iso14827TestNotifyStateContext_new(Dz1Str testName, 
																   s64_t time, 
																   Dz1Str state, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestNotifyStateContext *__internal_ret = (Iso14827TestNotifyStateContext *)Dz1Calloc(sizeof(Iso14827TestNotifyStateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyStateContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (state && (__internal_ret->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyStateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestNotifyStateContext_copy(Iso14827TestNotifyStateContext *dst, Iso14827TestNotifyStateContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->testName && (dst->testName = Dz1Str_clone(src->testName, errp)) == NULL) ERR_OUT(errp);
	else if (src->state && (dst->state = Dz1Str_clone(src->state, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->time = src->time;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestNotifyStateContext *Iso14827TestNotifyStateContext_clone(Iso14827TestNotifyStateContext *src, Dz1Error *err)
{
	Iso14827TestNotifyStateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestNotifyStateContext *)Dz1Calloc(sizeof(Iso14827TestNotifyStateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyStateContext_delAndSetNull, (void *)&dst);
		if (Iso14827TestNotifyStateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyStateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestNotifyStateContext_purge(Iso14827TestNotifyStateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->state);
}

void Iso14827TestNotifyStateContext_del(Iso14827TestNotifyStateContext *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyStateContext_purge(p);
	Dz1Free(p);
}

void Iso14827TestNotifyStateContext_dump(Iso14827TestNotifyStateContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = ")); Dz1Str_dump(p->state, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyInfoContext
Iso14827TestNotifyInfoContext *Iso14827TestNotifyInfoContext_new(Dz1Str testName, 
																 s64_t time, 
																 Dz1Str sender, 
																 Dz1Str log, 
																 Dz1Binary *data, 
																 Dz1Str dataType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestNotifyInfoContext *__internal_ret = (Iso14827TestNotifyInfoContext *)Dz1Calloc(sizeof(Iso14827TestNotifyInfoContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyInfoContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (sender && (__internal_ret->sender = Dz1Str_clone(sender, errp)) == NULL) ERR_OUT(errp);
		else if (log && (__internal_ret->log = Dz1Str_clone(log, errp)) == NULL) ERR_OUT(errp);
		else if (dataType && (__internal_ret->dataType = Dz1Str_clone(dataType, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyInfoContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestNotifyInfoContext_copy(Iso14827TestNotifyInfoContext *dst, Iso14827TestNotifyInfoContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->testName && (dst->testName = Dz1Str_clone(src->testName, errp)) == NULL) ERR_OUT(errp);
	else if (src->sender && (dst->sender = Dz1Str_clone(src->sender, errp)) == NULL) ERR_OUT(errp);
	else if (src->log && (dst->log = Dz1Str_clone(src->log, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Binary_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else if (src->dataType && (dst->dataType = Dz1Str_clone(src->dataType, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->time = src->time;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestNotifyInfoContext *Iso14827TestNotifyInfoContext_clone(Iso14827TestNotifyInfoContext *src, Dz1Error *err)
{
	Iso14827TestNotifyInfoContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestNotifyInfoContext *)Dz1Calloc(sizeof(Iso14827TestNotifyInfoContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyInfoContext_delAndSetNull, (void *)&dst);
		if (Iso14827TestNotifyInfoContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyInfoContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestNotifyInfoContext_purge(Iso14827TestNotifyInfoContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->sender);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->dataType);
}

void Iso14827TestNotifyInfoContext_del(Iso14827TestNotifyInfoContext *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyInfoContext_purge(p);
	Dz1Free(p);
}

void Iso14827TestNotifyInfoContext_dump(Iso14827TestNotifyInfoContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sender = ")); Dz1Str_dump(p->sender, tab); 
		Dz1Thread_tprintf(tab, Dz1T("log = ")); Dz1Str_dump(p->log, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dataType = ")); Dz1Str_dump(p->dataType, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyErrorContext
Iso14827TestNotifyErrorContext *Iso14827TestNotifyErrorContext_new(Dz1Str testName, 
																   s64_t time, 
																   Iso14827TestProcessStatusCode code, 
																   Dz1Str desc, 
																   Dz1Str log, 
																   Dz1Binary *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestNotifyErrorContext *__internal_ret = (Iso14827TestNotifyErrorContext *)Dz1Calloc(sizeof(Iso14827TestNotifyErrorContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyErrorContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (desc && (__internal_ret->desc = Dz1Str_clone(desc, errp)) == NULL) ERR_OUT(errp);
		else if (log && (__internal_ret->log = Dz1Str_clone(log, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			__internal_ret->code = code;
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyErrorContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestNotifyErrorContext_copy(Iso14827TestNotifyErrorContext *dst, Iso14827TestNotifyErrorContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->testName && (dst->testName = Dz1Str_clone(src->testName, errp)) == NULL) ERR_OUT(errp);
	else if (src->desc && (dst->desc = Dz1Str_clone(src->desc, errp)) == NULL) ERR_OUT(errp);
	else if (src->log && (dst->log = Dz1Str_clone(src->log, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Binary_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->time = src->time;
		dst->code = src->code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestNotifyErrorContext *Iso14827TestNotifyErrorContext_clone(Iso14827TestNotifyErrorContext *src, Dz1Error *err)
{
	Iso14827TestNotifyErrorContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestNotifyErrorContext *)Dz1Calloc(sizeof(Iso14827TestNotifyErrorContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyErrorContext_delAndSetNull, (void *)&dst);
		if (Iso14827TestNotifyErrorContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyErrorContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestNotifyErrorContext_purge(Iso14827TestNotifyErrorContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Str_del(p->desc);
	Dz1Str_del(p->log);
	Dz1Binary_del(p->data);
}

void Iso14827TestNotifyErrorContext_del(Iso14827TestNotifyErrorContext *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyErrorContext_purge(p);
	Dz1Free(p);
}

void Iso14827TestNotifyErrorContext_dump(Iso14827TestNotifyErrorContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), Iso14827TestProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("log = ")); Dz1Str_dump(p->log, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyContextPresent
static struct Iso14827TestNotifyContextPresentMapA
{
	str_t str;
	Iso14827TestNotifyContextPresent v;
} Iso14827TestNotifyContextPresentMapA[] =
{
	{ (char *)"state", Iso14827TestNotifyContextPresent_state },
	{ (char *)"info", Iso14827TestNotifyContextPresent_info },
	{ (char *)"error", Iso14827TestNotifyContextPresent_error },
	{ NULL, Iso14827TestNotifyContextPresent_max }
};

str_t Iso14827TestNotifyContextPresentStrA(Iso14827TestNotifyContextPresent v)
{
	struct Iso14827TestNotifyContextPresentMapA *i = NULL;
	for (i = Iso14827TestNotifyContextPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestNotifyContextPresent Iso14827TestNotifyContextPresentFromStrA(str_t str)
{
	struct Iso14827TestNotifyContextPresentMapA *i = NULL;
	for (i = Iso14827TestNotifyContextPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestNotifyContextPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestNotifyContextPresentMapW
{
	wstr_t str;
	Iso14827TestNotifyContextPresent v;
} Iso14827TestNotifyContextPresentMapW[] =
{
	{ (wchar_t *)L"state", Iso14827TestNotifyContextPresent_state },
	{ (wchar_t *)L"info", Iso14827TestNotifyContextPresent_info },
	{ (wchar_t *)L"error", Iso14827TestNotifyContextPresent_error },
	{ NULL, Iso14827TestNotifyContextPresent_max }
};

wstr_t Iso14827TestNotifyContextPresentStrW(Iso14827TestNotifyContextPresent v)
{
	struct Iso14827TestNotifyContextPresentMapW *i = NULL;
	for (i = Iso14827TestNotifyContextPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestNotifyContextPresent Iso14827TestNotifyContextPresentFromStrW(wstr_t str)
{
	struct Iso14827TestNotifyContextPresentMapW *i = NULL;
	for (i = Iso14827TestNotifyContextPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestNotifyContextPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestNotifyContextPresent *Iso14827TestNotifyContextPresent_new(Iso14827TestNotifyContextPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestNotifyContextPresent *__internal_ret = (Iso14827TestNotifyContextPresent *)Dz1Calloc(sizeof(Iso14827TestNotifyContextPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestNotifyContextPresent_dump(Iso14827TestNotifyContextPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestNotifyContextPresentStr(*v));
}
// Iso14827TestNotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyContext
Iso14827TestNotifyContext *Iso14827TestNotifyContext_new(Iso14827TestNotifyContextPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestNotifyContext *ret = (Iso14827TestNotifyContext *)Dz1Calloc(sizeof(Iso14827TestNotifyContext), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyContext_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TestNotifyContextPresent_state:
			// _U_cst_clone
			if (ptr != NULL) ret->x.state = (Iso14827TestNotifyStateContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestNotifyContextPresent_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.info = (Iso14827TestNotifyInfoContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestNotifyContextPresent_error:
			// _U_cst_clone
			if (ptr != NULL) ret->x.error = (Iso14827TestNotifyErrorContext *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestNotifyContextPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827TestNotifyContext_copy(Iso14827TestNotifyContext *ret, Iso14827TestNotifyContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827TestNotifyContextPresent_state:
			// _U_cst_clone
			if (src->x.state && (ret->x.state = Iso14827TestNotifyStateContext_clone(src->x.state, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestNotifyContextPresent_info:
			// _U_cst_clone
			if (src->x.info && (ret->x.info = Iso14827TestNotifyInfoContext_clone(src->x.info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestNotifyContextPresent_error:
			// _U_cst_clone
			if (src->x.error && (ret->x.error = Iso14827TestNotifyErrorContext_clone(src->x.error, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestNotifyContext *Iso14827TestNotifyContext_clone(Iso14827TestNotifyContext *src, Dz1Error *err)
{
	Iso14827TestNotifyContext *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827TestNotifyContext *)Dz1Calloc(sizeof(Iso14827TestNotifyContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyContext_delAndSetNull, (void *)&ret);
		if (Iso14827TestNotifyContext_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestNotifyContext_purge(Iso14827TestNotifyContext *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TestNotifyContextPresent_state:
		Iso14827TestNotifyStateContext_del(p->x.state);
		break;
	case Iso14827TestNotifyContextPresent_info:
		Iso14827TestNotifyInfoContext_del(p->x.info);
		break;
	case Iso14827TestNotifyContextPresent_error:
		Iso14827TestNotifyErrorContext_del(p->x.error);
		break;
	default:
		break;
	}
}

void Iso14827TestNotifyContext_del(Iso14827TestNotifyContext *p)
{
	if (!p) return;
	Iso14827TestNotifyContext_purge(p);
	Dz1Free(p);
}

void Iso14827TestNotifyContext_dump(Iso14827TestNotifyContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TestNotifyContextPresent_state:
		Dz1Thread_printf(Dz1T("state = ")); Iso14827TestNotifyStateContext_dump(p->x.state, tab); 
		break;
	case Iso14827TestNotifyContextPresent_info:
		Dz1Thread_printf(Dz1T("info = ")); Iso14827TestNotifyInfoContext_dump(p->x.info, tab); 
		break;
	case Iso14827TestNotifyContextPresent_error:
		Dz1Thread_printf(Dz1T("error = ")); Iso14827TestNotifyErrorContext_dump(p->x.error, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827TestNotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyStateArg
Iso14827TestNotifyStateArg *Iso14827TestNotifyStateArg_new(u32_t testIdx, 
														   Iso14827TestNotifyStateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestNotifyStateArg *__internal_ret = (Iso14827TestNotifyStateArg *)Dz1Calloc(sizeof(Iso14827TestNotifyStateArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyStateArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyStateArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestNotifyStateArg_copy(Iso14827TestNotifyStateArg *dst, Iso14827TestNotifyStateArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Iso14827TestNotifyStateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestNotifyStateArg *Iso14827TestNotifyStateArg_clone(Iso14827TestNotifyStateArg *src, Dz1Error *err)
{
	Iso14827TestNotifyStateArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestNotifyStateArg *)Dz1Calloc(sizeof(Iso14827TestNotifyStateArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyStateArg_delAndSetNull, (void *)&dst);
		if (Iso14827TestNotifyStateArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyStateArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestNotifyStateArg_purge(Iso14827TestNotifyStateArg *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyStateContext_del(p->context);
}

void Iso14827TestNotifyStateArg_del(Iso14827TestNotifyStateArg *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyStateArg_purge(p);
	Dz1Free(p);
}

void Iso14827TestNotifyStateArg_dump(Iso14827TestNotifyStateArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Iso14827TestNotifyStateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestNotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyInfoArg
Iso14827TestNotifyInfoArg *Iso14827TestNotifyInfoArg_new(u32_t testIdx, 
														 Iso14827TestNotifyInfoContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestNotifyInfoArg *__internal_ret = (Iso14827TestNotifyInfoArg *)Dz1Calloc(sizeof(Iso14827TestNotifyInfoArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyInfoArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyInfoArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestNotifyInfoArg_copy(Iso14827TestNotifyInfoArg *dst, Iso14827TestNotifyInfoArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Iso14827TestNotifyInfoContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestNotifyInfoArg *Iso14827TestNotifyInfoArg_clone(Iso14827TestNotifyInfoArg *src, Dz1Error *err)
{
	Iso14827TestNotifyInfoArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestNotifyInfoArg *)Dz1Calloc(sizeof(Iso14827TestNotifyInfoArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyInfoArg_delAndSetNull, (void *)&dst);
		if (Iso14827TestNotifyInfoArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyInfoArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestNotifyInfoArg_purge(Iso14827TestNotifyInfoArg *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyInfoContext_del(p->context);
}

void Iso14827TestNotifyInfoArg_del(Iso14827TestNotifyInfoArg *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyInfoArg_purge(p);
	Dz1Free(p);
}

void Iso14827TestNotifyInfoArg_dump(Iso14827TestNotifyInfoArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Iso14827TestNotifyInfoContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestNotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyErrorArg
Iso14827TestNotifyErrorArg *Iso14827TestNotifyErrorArg_new(u32_t testIdx, 
														   Iso14827TestNotifyErrorContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestNotifyErrorArg *__internal_ret = (Iso14827TestNotifyErrorArg *)Dz1Calloc(sizeof(Iso14827TestNotifyErrorArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyErrorArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyErrorArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestNotifyErrorArg_copy(Iso14827TestNotifyErrorArg *dst, Iso14827TestNotifyErrorArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Iso14827TestNotifyErrorContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestNotifyErrorArg *Iso14827TestNotifyErrorArg_clone(Iso14827TestNotifyErrorArg *src, Dz1Error *err)
{
	Iso14827TestNotifyErrorArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestNotifyErrorArg *)Dz1Calloc(sizeof(Iso14827TestNotifyErrorArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestNotifyErrorArg_delAndSetNull, (void *)&dst);
		if (Iso14827TestNotifyErrorArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestNotifyErrorArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestNotifyErrorArg_purge(Iso14827TestNotifyErrorArg *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyErrorContext_del(p->context);
}

void Iso14827TestNotifyErrorArg_del(Iso14827TestNotifyErrorArg *p)
{
	if (p == NULL) return;
	Iso14827TestNotifyErrorArg_purge(p);
	Dz1Free(p);
}

void Iso14827TestNotifyErrorArg_dump(Iso14827TestNotifyErrorArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Iso14827TestNotifyErrorContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestNotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateContext
Iso14827TestValidateContext *Iso14827TestValidateContext_new(Dz1Str testName, 
															 s64_t time, 
															 Dz1Binary *raw, 
															 Dz1Binary *data, 
															 Iso14827TestProcessStatusCode code, 
															 Dz1Str desc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestValidateContext *__internal_ret = (Iso14827TestValidateContext *)Dz1Calloc(sizeof(Iso14827TestValidateContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestValidateContext_delAndSetNull, (void *)&__internal_ret);
		
		if (testName && (__internal_ret->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
		else if (desc && (__internal_ret->desc = Dz1Str_clone(desc, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->time = time;
			__internal_ret->raw = raw;
			__internal_ret->data = data;
			__internal_ret->code = code;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestValidateContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestValidateContext_copy(Iso14827TestValidateContext *dst, Iso14827TestValidateContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->testName && (dst->testName = Dz1Str_clone(src->testName, errp)) == NULL) ERR_OUT(errp);
	else if (src->raw && (dst->raw = Dz1Binary_clone(src->raw, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Binary_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else if (src->desc && (dst->desc = Dz1Str_clone(src->desc, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->time = src->time;
		dst->code = src->code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestValidateContext *Iso14827TestValidateContext_clone(Iso14827TestValidateContext *src, Dz1Error *err)
{
	Iso14827TestValidateContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestValidateContext *)Dz1Calloc(sizeof(Iso14827TestValidateContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestValidateContext_delAndSetNull, (void *)&dst);
		if (Iso14827TestValidateContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestValidateContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestValidateContext_purge(Iso14827TestValidateContext *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->testName);
	Dz1Binary_del(p->raw);
	Dz1Binary_del(p->data);
	Dz1Str_del(p->desc);
}

void Iso14827TestValidateContext_del(Iso14827TestValidateContext *p)
{
	if (p == NULL) return;
	Iso14827TestValidateContext_purge(p);
	Dz1Free(p);
}

void Iso14827TestValidateContext_dump(Iso14827TestValidateContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testName = ")); Dz1Str_dump(p->testName, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time = ")); Dz1s64_dump(&p->time, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("raw = ")); Dz1Binary_dump(p->raw, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Binary_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("code = %s(%d)\n"), Iso14827TestProcessStatusCodeStr(p->code), p->code);
		Dz1Thread_tprintf(tab, Dz1T("desc = ")); Dz1Str_dump(p->desc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateContextArg
Iso14827TestValidateContextArg *Iso14827TestValidateContextArg_new(u32_t testIdx, 
																   Iso14827TestValidateContext *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestValidateContextArg *__internal_ret = (Iso14827TestValidateContextArg *)Dz1Calloc(sizeof(Iso14827TestValidateContextArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestValidateContextArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->testIdx = testIdx;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestValidateContextArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestValidateContextArg_copy(Iso14827TestValidateContextArg *dst, Iso14827TestValidateContextArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Iso14827TestValidateContext_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->testIdx = src->testIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestValidateContextArg *Iso14827TestValidateContextArg_clone(Iso14827TestValidateContextArg *src, Dz1Error *err)
{
	Iso14827TestValidateContextArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestValidateContextArg *)Dz1Calloc(sizeof(Iso14827TestValidateContextArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestValidateContextArg_delAndSetNull, (void *)&dst);
		if (Iso14827TestValidateContextArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestValidateContextArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestValidateContextArg_purge(Iso14827TestValidateContextArg *p)
{
	if (p == NULL) return;
	Iso14827TestValidateContext_del(p->context);
}

void Iso14827TestValidateContextArg_del(Iso14827TestValidateContextArg *p)
{
	if (p == NULL) return;
	Iso14827TestValidateContextArg_purge(p);
	Dz1Free(p);
}

void Iso14827TestValidateContextArg_dump(Iso14827TestValidateContextArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("testIdx = ")); Dz1u32_dump(&p->testIdx, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Iso14827TestValidateContext_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_centerClient2rse
PolicePrj4TestConfiguration_centerClient2rse *PolicePrj4TestConfiguration_centerClient2rse_new(Dz1Str peer_ip, 
																							   s64_t peer_port, 
																							   Dz1Str user, 
																							   Dz1Str pass, 
																							   bool_t test_session, 
																							   bool_t test_login_invalid, 
																							   bool_t test_session_maintain, 
																							   bool_t test_normal_pub, 
																							   bool_t test_bsm, 
																							   bool_t test_login_duplicate, 
																							   bool_t test_invalid_sub, 
																							   bool_t test_subs_cancel, 
																							   bool_t test_pub_retry, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4TestConfiguration_centerClient2rse *__internal_ret = (PolicePrj4TestConfiguration_centerClient2rse *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_centerClient2rse), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_centerClient2rse_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else if (user && (__internal_ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = Dz1Str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->test_session = test_session;
			__internal_ret->test_login_invalid = test_login_invalid;
			__internal_ret->test_session_maintain = test_session_maintain;
			__internal_ret->test_normal_pub = test_normal_pub;
			__internal_ret->test_bsm = test_bsm;
			__internal_ret->test_login_duplicate = test_login_duplicate;
			__internal_ret->test_invalid_sub = test_invalid_sub;
			__internal_ret->test_subs_cancel = test_subs_cancel;
			__internal_ret->test_pub_retry = test_pub_retry;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_centerClient2rse_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4TestConfiguration_centerClient2rse_copy(PolicePrj4TestConfiguration_centerClient2rse *dst, PolicePrj4TestConfiguration_centerClient2rse *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Str_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Str_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->test_session = src->test_session;
		dst->test_login_invalid = src->test_login_invalid;
		dst->test_session_maintain = src->test_session_maintain;
		dst->test_normal_pub = src->test_normal_pub;
		dst->test_bsm = src->test_bsm;
		dst->test_login_duplicate = src->test_login_duplicate;
		dst->test_invalid_sub = src->test_invalid_sub;
		dst->test_subs_cancel = src->test_subs_cancel;
		dst->test_pub_retry = src->test_pub_retry;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4TestConfiguration_centerClient2rse *PolicePrj4TestConfiguration_centerClient2rse_clone(PolicePrj4TestConfiguration_centerClient2rse *src, Dz1Error *err)
{
	PolicePrj4TestConfiguration_centerClient2rse *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4TestConfiguration_centerClient2rse *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_centerClient2rse), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_centerClient2rse_delAndSetNull, (void *)&dst);
		if (PolicePrj4TestConfiguration_centerClient2rse_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_centerClient2rse_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4TestConfiguration_centerClient2rse_purge(PolicePrj4TestConfiguration_centerClient2rse *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
	Dz1Str_del(p->peer_ip);
	Dz1Str_del(p->user);
	Dz1Str_del(p->pass);
}

void PolicePrj4TestConfiguration_centerClient2rse_del(PolicePrj4TestConfiguration_centerClient2rse *p)
{
	if (p == NULL) return;
	PolicePrj4TestConfiguration_centerClient2rse_purge(p);
	Dz1Free(p);
}

void PolicePrj4TestConfiguration_centerClient2rse_dump(PolicePrj4TestConfiguration_centerClient2rse *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1s64_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_invalid = ")); Dz1Bool_dump(&p->test_login_invalid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_normal_pub = ")); Dz1Bool_dump(&p->test_normal_pub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_bsm = ")); Dz1Bool_dump(&p->test_bsm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_duplicate = ")); Dz1Bool_dump(&p->test_login_duplicate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_sub = ")); Dz1Bool_dump(&p->test_invalid_sub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs_cancel = ")); Dz1Bool_dump(&p->test_subs_cancel, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_retry = ")); Dz1Bool_dump(&p->test_pub_retry, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PolicePrj4TestConfiguration_centerClient2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_rseServer2center
PolicePrj4TestConfiguration_rseServer2center *PolicePrj4TestConfiguration_rseServer2center_new(s64_t local_port, 
																							   bool_t test_session, 
																							   bool_t test_login_retry, 
																							   s64_t subs_timeout_s, 
																							   bool_t test_bsm, 
																							   bool_t test_sub_retry, 
																							   bool_t test_invalid_pub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4TestConfiguration_rseServer2center *__internal_ret = (PolicePrj4TestConfiguration_rseServer2center *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_rseServer2center), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_rseServer2center_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_retry = test_login_retry;
		__internal_ret->subs_timeout_s = subs_timeout_s;
		__internal_ret->test_bsm = test_bsm;
		__internal_ret->test_sub_retry = test_sub_retry;
		__internal_ret->test_invalid_pub = test_invalid_pub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_rseServer2center_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4TestConfiguration_rseServer2center_copy(PolicePrj4TestConfiguration_rseServer2center *dst, PolicePrj4TestConfiguration_rseServer2center *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_session = src->test_session;
		dst->test_login_retry = src->test_login_retry;
		dst->subs_timeout_s = src->subs_timeout_s;
		dst->test_bsm = src->test_bsm;
		dst->test_sub_retry = src->test_sub_retry;
		dst->test_invalid_pub = src->test_invalid_pub;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4TestConfiguration_rseServer2center *PolicePrj4TestConfiguration_rseServer2center_clone(PolicePrj4TestConfiguration_rseServer2center *src, Dz1Error *err)
{
	PolicePrj4TestConfiguration_rseServer2center *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4TestConfiguration_rseServer2center *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_rseServer2center), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_rseServer2center_delAndSetNull, (void *)&dst);
		if (PolicePrj4TestConfiguration_rseServer2center_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_rseServer2center_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4TestConfiguration_rseServer2center_purge(PolicePrj4TestConfiguration_rseServer2center *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
}

void PolicePrj4TestConfiguration_rseServer2center_del(PolicePrj4TestConfiguration_rseServer2center *p)
{
	if (p == NULL) return;
	PolicePrj4TestConfiguration_rseServer2center_purge(p);
	Dz1Free(p);
}

void PolicePrj4TestConfiguration_rseServer2center_dump(PolicePrj4TestConfiguration_rseServer2center *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1s64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_retry = ")); Dz1Bool_dump(&p->test_login_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_timeout_s = ")); Dz1s64_dump(&p->subs_timeout_s, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_bsm = ")); Dz1Bool_dump(&p->test_bsm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_retry = ")); Dz1Bool_dump(&p->test_sub_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_pub = ")); Dz1Bool_dump(&p->test_invalid_pub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PolicePrj4TestConfiguration_rseServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_rseClient2center
PolicePrj4TestConfiguration_rseClient2center *PolicePrj4TestConfiguration_rseClient2center_new(Dz1Str peer_ip, 
																							   s64_t peer_port, 
																							   Dz1Str user, 
																							   Dz1Str pass, 
																							   bool_t test_session, 
																							   bool_t test_login_invalid, 
																							   bool_t test_session_maintain, 
																							   bool_t test_normal_pub, 
																							   bool_t test_map, 
																							   bool_t test_rsa, 
																							   bool_t test_tim, 
																							   bool_t test_login_duplicate, 
																							   bool_t test_invalid_sub, 
																							   bool_t test_subs_cancel, 
																							   bool_t test_pub_retry, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4TestConfiguration_rseClient2center *__internal_ret = (PolicePrj4TestConfiguration_rseClient2center *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_rseClient2center), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_rseClient2center_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else if (user && (__internal_ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = Dz1Str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->test_session = test_session;
			__internal_ret->test_login_invalid = test_login_invalid;
			__internal_ret->test_session_maintain = test_session_maintain;
			__internal_ret->test_normal_pub = test_normal_pub;
			__internal_ret->test_map = test_map;
			__internal_ret->test_rsa = test_rsa;
			__internal_ret->test_tim = test_tim;
			__internal_ret->test_login_duplicate = test_login_duplicate;
			__internal_ret->test_invalid_sub = test_invalid_sub;
			__internal_ret->test_subs_cancel = test_subs_cancel;
			__internal_ret->test_pub_retry = test_pub_retry;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_rseClient2center_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4TestConfiguration_rseClient2center_copy(PolicePrj4TestConfiguration_rseClient2center *dst, PolicePrj4TestConfiguration_rseClient2center *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Str_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Str_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->test_session = src->test_session;
		dst->test_login_invalid = src->test_login_invalid;
		dst->test_session_maintain = src->test_session_maintain;
		dst->test_normal_pub = src->test_normal_pub;
		dst->test_map = src->test_map;
		dst->test_rsa = src->test_rsa;
		dst->test_tim = src->test_tim;
		dst->test_login_duplicate = src->test_login_duplicate;
		dst->test_invalid_sub = src->test_invalid_sub;
		dst->test_subs_cancel = src->test_subs_cancel;
		dst->test_pub_retry = src->test_pub_retry;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4TestConfiguration_rseClient2center *PolicePrj4TestConfiguration_rseClient2center_clone(PolicePrj4TestConfiguration_rseClient2center *src, Dz1Error *err)
{
	PolicePrj4TestConfiguration_rseClient2center *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4TestConfiguration_rseClient2center *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_rseClient2center), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_rseClient2center_delAndSetNull, (void *)&dst);
		if (PolicePrj4TestConfiguration_rseClient2center_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_rseClient2center_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4TestConfiguration_rseClient2center_purge(PolicePrj4TestConfiguration_rseClient2center *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
	Dz1Str_del(p->peer_ip);
	Dz1Str_del(p->user);
	Dz1Str_del(p->pass);
}

void PolicePrj4TestConfiguration_rseClient2center_del(PolicePrj4TestConfiguration_rseClient2center *p)
{
	if (p == NULL) return;
	PolicePrj4TestConfiguration_rseClient2center_purge(p);
	Dz1Free(p);
}

void PolicePrj4TestConfiguration_rseClient2center_dump(PolicePrj4TestConfiguration_rseClient2center *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1s64_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_invalid = ")); Dz1Bool_dump(&p->test_login_invalid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_normal_pub = ")); Dz1Bool_dump(&p->test_normal_pub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsa = ")); Dz1Bool_dump(&p->test_rsa, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tim = ")); Dz1Bool_dump(&p->test_tim, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_duplicate = ")); Dz1Bool_dump(&p->test_login_duplicate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_sub = ")); Dz1Bool_dump(&p->test_invalid_sub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs_cancel = ")); Dz1Bool_dump(&p->test_subs_cancel, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_retry = ")); Dz1Bool_dump(&p->test_pub_retry, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PolicePrj4TestConfiguration_rseClient2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_centerServer2rse
PolicePrj4TestConfiguration_centerServer2rse *PolicePrj4TestConfiguration_centerServer2rse_new(s64_t local_port, 
																							   bool_t test_session, 
																							   bool_t test_login_retry, 
																							   s64_t subs_timeout_s, 
																							   bool_t test_map, 
																							   bool_t test_rsa, 
																							   bool_t test_tim, 
																							   bool_t test_sub_retry, 
																							   bool_t test_invalid_pub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4TestConfiguration_centerServer2rse *__internal_ret = (PolicePrj4TestConfiguration_centerServer2rse *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_centerServer2rse), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_centerServer2rse_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_retry = test_login_retry;
		__internal_ret->subs_timeout_s = subs_timeout_s;
		__internal_ret->test_map = test_map;
		__internal_ret->test_rsa = test_rsa;
		__internal_ret->test_tim = test_tim;
		__internal_ret->test_sub_retry = test_sub_retry;
		__internal_ret->test_invalid_pub = test_invalid_pub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_centerServer2rse_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4TestConfiguration_centerServer2rse_copy(PolicePrj4TestConfiguration_centerServer2rse *dst, PolicePrj4TestConfiguration_centerServer2rse *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_session = src->test_session;
		dst->test_login_retry = src->test_login_retry;
		dst->subs_timeout_s = src->subs_timeout_s;
		dst->test_map = src->test_map;
		dst->test_rsa = src->test_rsa;
		dst->test_tim = src->test_tim;
		dst->test_sub_retry = src->test_sub_retry;
		dst->test_invalid_pub = src->test_invalid_pub;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4TestConfiguration_centerServer2rse *PolicePrj4TestConfiguration_centerServer2rse_clone(PolicePrj4TestConfiguration_centerServer2rse *src, Dz1Error *err)
{
	PolicePrj4TestConfiguration_centerServer2rse *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4TestConfiguration_centerServer2rse *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_centerServer2rse), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_centerServer2rse_delAndSetNull, (void *)&dst);
		if (PolicePrj4TestConfiguration_centerServer2rse_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_centerServer2rse_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4TestConfiguration_centerServer2rse_purge(PolicePrj4TestConfiguration_centerServer2rse *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
}

void PolicePrj4TestConfiguration_centerServer2rse_del(PolicePrj4TestConfiguration_centerServer2rse *p)
{
	if (p == NULL) return;
	PolicePrj4TestConfiguration_centerServer2rse_purge(p);
	Dz1Free(p);
}

void PolicePrj4TestConfiguration_centerServer2rse_dump(PolicePrj4TestConfiguration_centerServer2rse *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1s64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_retry = ")); Dz1Bool_dump(&p->test_login_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_timeout_s = ")); Dz1s64_dump(&p->subs_timeout_s, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_map = ")); Dz1Bool_dump(&p->test_map, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_rsa = ")); Dz1Bool_dump(&p->test_rsa, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tim = ")); Dz1Bool_dump(&p->test_tim, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_retry = ")); Dz1Bool_dump(&p->test_sub_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_pub = ")); Dz1Bool_dump(&p->test_invalid_pub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PolicePrj4TestConfiguration_centerServer2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_signalserverServer2center
PolicePrj4TestConfiguration_signalserverServer2center *PolicePrj4TestConfiguration_signalserverServer2center_new(s64_t local_port, 
																												 bool_t test_session, 
																												 bool_t test_login_retry, 
																												 s64_t subs_timeout_s, 
																												 bool_t test_spat, 
																												 bool_t test_tls, 
																												 bool_t test_sub_retry, 
																												 bool_t test_invalid_pub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	PolicePrj4TestConfiguration_signalserverServer2center *__internal_ret = (PolicePrj4TestConfiguration_signalserverServer2center *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_signalserverServer2center), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_signalserverServer2center_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_retry = test_login_retry;
		__internal_ret->subs_timeout_s = subs_timeout_s;
		__internal_ret->test_spat = test_spat;
		__internal_ret->test_tls = test_tls;
		__internal_ret->test_sub_retry = test_sub_retry;
		__internal_ret->test_invalid_pub = test_invalid_pub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_signalserverServer2center_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t PolicePrj4TestConfiguration_signalserverServer2center_copy(PolicePrj4TestConfiguration_signalserverServer2center *dst, PolicePrj4TestConfiguration_signalserverServer2center *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_session = src->test_session;
		dst->test_login_retry = src->test_login_retry;
		dst->subs_timeout_s = src->subs_timeout_s;
		dst->test_spat = src->test_spat;
		dst->test_tls = src->test_tls;
		dst->test_sub_retry = src->test_sub_retry;
		dst->test_invalid_pub = src->test_invalid_pub;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

PolicePrj4TestConfiguration_signalserverServer2center *PolicePrj4TestConfiguration_signalserverServer2center_clone(PolicePrj4TestConfiguration_signalserverServer2center *src, Dz1Error *err)
{
	PolicePrj4TestConfiguration_signalserverServer2center *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (PolicePrj4TestConfiguration_signalserverServer2center *)Dz1Calloc(sizeof(PolicePrj4TestConfiguration_signalserverServer2center), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(PolicePrj4TestConfiguration_signalserverServer2center_delAndSetNull, (void *)&dst);
		if (PolicePrj4TestConfiguration_signalserverServer2center_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (PolicePrj4TestConfiguration_signalserverServer2center_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void PolicePrj4TestConfiguration_signalserverServer2center_purge(PolicePrj4TestConfiguration_signalserverServer2center *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
}

void PolicePrj4TestConfiguration_signalserverServer2center_del(PolicePrj4TestConfiguration_signalserverServer2center *p)
{
	if (p == NULL) return;
	PolicePrj4TestConfiguration_signalserverServer2center_purge(p);
	Dz1Free(p);
}

void PolicePrj4TestConfiguration_signalserverServer2center_dump(PolicePrj4TestConfiguration_signalserverServer2center *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1s64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_retry = ")); Dz1Bool_dump(&p->test_login_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_timeout_s = ")); Dz1s64_dump(&p->subs_timeout_s, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_spat = ")); Dz1Bool_dump(&p->test_spat, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_tls = ")); Dz1Bool_dump(&p->test_tls, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_retry = ")); Dz1Bool_dump(&p->test_sub_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_pub = ")); Dz1Bool_dump(&p->test_invalid_pub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// PolicePrj4TestConfiguration_signalserverServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3TestConfigurationServerRole
ITSK00100_3TestConfigurationServerRole *ITSK00100_3TestConfigurationServerRole_new(s64_t local_port, 
																				   bool_t test_session, 
																				   bool_t test_login_retry, 
																				   bool_t test_sub_incident_detection_info, 
																				   bool_t test_sub_incident_termination_info, 
																				   bool_t test_sub_incident_detection_video_file_info_provide, 
																				   bool_t test_sub_control_state_info, 
																				   bool_t test_sub_sensor_state_info, 
																				   bool_t test_sub_moving_object, 
																				   bool_t test_sub_retry, 
																				   bool_t test_invalid_pub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00100_3TestConfigurationServerRole *__internal_ret = (ITSK00100_3TestConfigurationServerRole *)Dz1Calloc(sizeof(ITSK00100_3TestConfigurationServerRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00100_3TestConfigurationServerRole_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_retry = test_login_retry;
		__internal_ret->test_sub_incident_detection_info = test_sub_incident_detection_info;
		__internal_ret->test_sub_incident_termination_info = test_sub_incident_termination_info;
		__internal_ret->test_sub_incident_detection_video_file_info_provide = test_sub_incident_detection_video_file_info_provide;
		__internal_ret->test_sub_control_state_info = test_sub_control_state_info;
		__internal_ret->test_sub_sensor_state_info = test_sub_sensor_state_info;
		__internal_ret->test_sub_moving_object = test_sub_moving_object;
		__internal_ret->test_sub_retry = test_sub_retry;
		__internal_ret->test_invalid_pub = test_invalid_pub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00100_3TestConfigurationServerRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00100_3TestConfigurationServerRole_copy(ITSK00100_3TestConfigurationServerRole *dst, ITSK00100_3TestConfigurationServerRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_session = src->test_session;
		dst->test_login_retry = src->test_login_retry;
		dst->test_sub_incident_detection_info = src->test_sub_incident_detection_info;
		dst->test_sub_incident_termination_info = src->test_sub_incident_termination_info;
		dst->test_sub_incident_detection_video_file_info_provide = src->test_sub_incident_detection_video_file_info_provide;
		dst->test_sub_control_state_info = src->test_sub_control_state_info;
		dst->test_sub_sensor_state_info = src->test_sub_sensor_state_info;
		dst->test_sub_moving_object = src->test_sub_moving_object;
		dst->test_sub_retry = src->test_sub_retry;
		dst->test_invalid_pub = src->test_invalid_pub;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00100_3TestConfigurationServerRole *ITSK00100_3TestConfigurationServerRole_clone(ITSK00100_3TestConfigurationServerRole *src, Dz1Error *err)
{
	ITSK00100_3TestConfigurationServerRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00100_3TestConfigurationServerRole *)Dz1Calloc(sizeof(ITSK00100_3TestConfigurationServerRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00100_3TestConfigurationServerRole_delAndSetNull, (void *)&dst);
		if (ITSK00100_3TestConfigurationServerRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00100_3TestConfigurationServerRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00100_3TestConfigurationServerRole_purge(ITSK00100_3TestConfigurationServerRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
}

void ITSK00100_3TestConfigurationServerRole_del(ITSK00100_3TestConfigurationServerRole *p)
{
	if (p == NULL) return;
	ITSK00100_3TestConfigurationServerRole_purge(p);
	Dz1Free(p);
}

void ITSK00100_3TestConfigurationServerRole_dump(ITSK00100_3TestConfigurationServerRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1s64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_retry = ")); Dz1Bool_dump(&p->test_login_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_incident_detection_info = ")); Dz1Bool_dump(&p->test_sub_incident_detection_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_incident_termination_info = ")); Dz1Bool_dump(&p->test_sub_incident_termination_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_incident_detection_video_file_info_provide = ")); Dz1Bool_dump(&p->test_sub_incident_detection_video_file_info_provide, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_control_state_info = ")); Dz1Bool_dump(&p->test_sub_control_state_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_sensor_state_info = ")); Dz1Bool_dump(&p->test_sub_sensor_state_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_moving_object = ")); Dz1Bool_dump(&p->test_sub_moving_object, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_retry = ")); Dz1Bool_dump(&p->test_sub_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_pub = ")); Dz1Bool_dump(&p->test_invalid_pub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00100_3TestConfigurationServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3TestConfigurationClientRole
ITSK00100_3TestConfigurationClientRole *ITSK00100_3TestConfigurationClientRole_new(Dz1Str peer_ip, 
																				   s64_t peer_port, 
																				   Dz1Str user, 
																				   Dz1Str pass, 
																				   bool_t test_session, 
																				   bool_t test_login_invalid, 
																				   bool_t test_session_maintain, 
																				   bool_t test_normal_pub, 
																				   bool_t test_pub_incident_detection_info, 
																				   bool_t test_pub_incident_termination_info, 
																				   bool_t test_pub_incident_detection_video_file_info_provide, 
																				   bool_t test_pub_control_state_info, 
																				   bool_t test_pub_sensor_state_info, 
																				   bool_t test_pub_moving_object, 
																				   bool_t test_login_duplicate, 
																				   bool_t test_invalid_sub, 
																				   bool_t test_subs_cancel, 
																				   bool_t test_pub_retry, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00100_3TestConfigurationClientRole *__internal_ret = (ITSK00100_3TestConfigurationClientRole *)Dz1Calloc(sizeof(ITSK00100_3TestConfigurationClientRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00100_3TestConfigurationClientRole_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else if (user && (__internal_ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = Dz1Str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->test_session = test_session;
			__internal_ret->test_login_invalid = test_login_invalid;
			__internal_ret->test_session_maintain = test_session_maintain;
			__internal_ret->test_normal_pub = test_normal_pub;
			__internal_ret->test_pub_incident_detection_info = test_pub_incident_detection_info;
			__internal_ret->test_pub_incident_termination_info = test_pub_incident_termination_info;
			__internal_ret->test_pub_incident_detection_video_file_info_provide = test_pub_incident_detection_video_file_info_provide;
			__internal_ret->test_pub_control_state_info = test_pub_control_state_info;
			__internal_ret->test_pub_sensor_state_info = test_pub_sensor_state_info;
			__internal_ret->test_pub_moving_object = test_pub_moving_object;
			__internal_ret->test_login_duplicate = test_login_duplicate;
			__internal_ret->test_invalid_sub = test_invalid_sub;
			__internal_ret->test_subs_cancel = test_subs_cancel;
			__internal_ret->test_pub_retry = test_pub_retry;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00100_3TestConfigurationClientRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00100_3TestConfigurationClientRole_copy(ITSK00100_3TestConfigurationClientRole *dst, ITSK00100_3TestConfigurationClientRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Str_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Str_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->test_session = src->test_session;
		dst->test_login_invalid = src->test_login_invalid;
		dst->test_session_maintain = src->test_session_maintain;
		dst->test_normal_pub = src->test_normal_pub;
		dst->test_pub_incident_detection_info = src->test_pub_incident_detection_info;
		dst->test_pub_incident_termination_info = src->test_pub_incident_termination_info;
		dst->test_pub_incident_detection_video_file_info_provide = src->test_pub_incident_detection_video_file_info_provide;
		dst->test_pub_control_state_info = src->test_pub_control_state_info;
		dst->test_pub_sensor_state_info = src->test_pub_sensor_state_info;
		dst->test_pub_moving_object = src->test_pub_moving_object;
		dst->test_login_duplicate = src->test_login_duplicate;
		dst->test_invalid_sub = src->test_invalid_sub;
		dst->test_subs_cancel = src->test_subs_cancel;
		dst->test_pub_retry = src->test_pub_retry;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00100_3TestConfigurationClientRole *ITSK00100_3TestConfigurationClientRole_clone(ITSK00100_3TestConfigurationClientRole *src, Dz1Error *err)
{
	ITSK00100_3TestConfigurationClientRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00100_3TestConfigurationClientRole *)Dz1Calloc(sizeof(ITSK00100_3TestConfigurationClientRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00100_3TestConfigurationClientRole_delAndSetNull, (void *)&dst);
		if (ITSK00100_3TestConfigurationClientRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00100_3TestConfigurationClientRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00100_3TestConfigurationClientRole_purge(ITSK00100_3TestConfigurationClientRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
	Dz1Str_del(p->peer_ip);
	Dz1Str_del(p->user);
	Dz1Str_del(p->pass);
}

void ITSK00100_3TestConfigurationClientRole_del(ITSK00100_3TestConfigurationClientRole *p)
{
	if (p == NULL) return;
	ITSK00100_3TestConfigurationClientRole_purge(p);
	Dz1Free(p);
}

void ITSK00100_3TestConfigurationClientRole_dump(ITSK00100_3TestConfigurationClientRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1s64_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_invalid = ")); Dz1Bool_dump(&p->test_login_invalid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_normal_pub = ")); Dz1Bool_dump(&p->test_normal_pub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_detection_info = ")); Dz1Bool_dump(&p->test_pub_incident_detection_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_termination_info = ")); Dz1Bool_dump(&p->test_pub_incident_termination_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_detection_video_file_info_provide = ")); Dz1Bool_dump(&p->test_pub_incident_detection_video_file_info_provide, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_control_state_info = ")); Dz1Bool_dump(&p->test_pub_control_state_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_sensor_state_info = ")); Dz1Bool_dump(&p->test_pub_sensor_state_info, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_moving_object = ")); Dz1Bool_dump(&p->test_pub_moving_object, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_duplicate = ")); Dz1Bool_dump(&p->test_login_duplicate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_sub = ")); Dz1Bool_dump(&p->test_invalid_sub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs_cancel = ")); Dz1Bool_dump(&p->test_subs_cancel, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_retry = ")); Dz1Bool_dump(&p->test_pub_retry, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00100_3TestConfigurationClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1TestConfiguration_clientRole1
TechnicalRegulation1TestConfiguration_clientRole1 *TechnicalRegulation1TestConfiguration_clientRole1_new(Dz1Str peer_ip, 
																										 s64_t peer_port, 
																										 Dz1Str user, 
																										 Dz1Str pass, 
																										 bool_t test_session, 
																										 bool_t test_login_invalid, 
																										 bool_t test_session_maintain, 
																										 bool_t test_normal_pub, 
																										 bool_t test_pub_current_link_state, 
																										 bool_t test_pub_event_identity, 
																										 bool_t test_pub_incident_identity, 
																										 bool_t test_pub_incident_conditions, 
																										 bool_t test_pub_roadway_surface_status, 
																										 bool_t test_pub_weather_information, 
																										 bool_t test_pub_link_roadway_geometry, 
																										 bool_t test_pub_probe_vehicle_detection, 
																										 bool_t test_pub_detector_collection, 
																										 bool_t test_pub_extention_comm_pdu, 
																										 bool_t test_login_duplicate, 
																										 bool_t test_invalid_sub, 
																										 bool_t test_subs_cancel, 
																										 bool_t test_pub_retry, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation1TestConfiguration_clientRole1 *__internal_ret = (TechnicalRegulation1TestConfiguration_clientRole1 *)Dz1Calloc(sizeof(TechnicalRegulation1TestConfiguration_clientRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else if (user && (__internal_ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = Dz1Str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->test_session = test_session;
			__internal_ret->test_login_invalid = test_login_invalid;
			__internal_ret->test_session_maintain = test_session_maintain;
			__internal_ret->test_normal_pub = test_normal_pub;
			__internal_ret->test_pub_current_link_state = test_pub_current_link_state;
			__internal_ret->test_pub_event_identity = test_pub_event_identity;
			__internal_ret->test_pub_incident_identity = test_pub_incident_identity;
			__internal_ret->test_pub_incident_conditions = test_pub_incident_conditions;
			__internal_ret->test_pub_roadway_surface_status = test_pub_roadway_surface_status;
			__internal_ret->test_pub_weather_information = test_pub_weather_information;
			__internal_ret->test_pub_link_roadway_geometry = test_pub_link_roadway_geometry;
			__internal_ret->test_pub_probe_vehicle_detection = test_pub_probe_vehicle_detection;
			__internal_ret->test_pub_detector_collection = test_pub_detector_collection;
			__internal_ret->test_pub_extention_comm_pdu = test_pub_extention_comm_pdu;
			__internal_ret->test_login_duplicate = test_login_duplicate;
			__internal_ret->test_invalid_sub = test_invalid_sub;
			__internal_ret->test_subs_cancel = test_subs_cancel;
			__internal_ret->test_pub_retry = test_pub_retry;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulation1TestConfiguration_clientRole1_copy(TechnicalRegulation1TestConfiguration_clientRole1 *dst, TechnicalRegulation1TestConfiguration_clientRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Str_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Str_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->test_session = src->test_session;
		dst->test_login_invalid = src->test_login_invalid;
		dst->test_session_maintain = src->test_session_maintain;
		dst->test_normal_pub = src->test_normal_pub;
		dst->test_pub_current_link_state = src->test_pub_current_link_state;
		dst->test_pub_event_identity = src->test_pub_event_identity;
		dst->test_pub_incident_identity = src->test_pub_incident_identity;
		dst->test_pub_incident_conditions = src->test_pub_incident_conditions;
		dst->test_pub_roadway_surface_status = src->test_pub_roadway_surface_status;
		dst->test_pub_weather_information = src->test_pub_weather_information;
		dst->test_pub_link_roadway_geometry = src->test_pub_link_roadway_geometry;
		dst->test_pub_probe_vehicle_detection = src->test_pub_probe_vehicle_detection;
		dst->test_pub_detector_collection = src->test_pub_detector_collection;
		dst->test_pub_extention_comm_pdu = src->test_pub_extention_comm_pdu;
		dst->test_login_duplicate = src->test_login_duplicate;
		dst->test_invalid_sub = src->test_invalid_sub;
		dst->test_subs_cancel = src->test_subs_cancel;
		dst->test_pub_retry = src->test_pub_retry;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation1TestConfiguration_clientRole1 *TechnicalRegulation1TestConfiguration_clientRole1_clone(TechnicalRegulation1TestConfiguration_clientRole1 *src, Dz1Error *err)
{
	TechnicalRegulation1TestConfiguration_clientRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulation1TestConfiguration_clientRole1 *)Dz1Calloc(sizeof(TechnicalRegulation1TestConfiguration_clientRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull, (void *)&dst);
		if (TechnicalRegulation1TestConfiguration_clientRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulation1TestConfiguration_clientRole1_purge(TechnicalRegulation1TestConfiguration_clientRole1 *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
	Dz1Str_del(p->peer_ip);
	Dz1Str_del(p->user);
	Dz1Str_del(p->pass);
}

void TechnicalRegulation1TestConfiguration_clientRole1_del(TechnicalRegulation1TestConfiguration_clientRole1 *p)
{
	if (p == NULL) return;
	TechnicalRegulation1TestConfiguration_clientRole1_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation1TestConfiguration_clientRole1_dump(TechnicalRegulation1TestConfiguration_clientRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1s64_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_invalid = ")); Dz1Bool_dump(&p->test_login_invalid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_normal_pub = ")); Dz1Bool_dump(&p->test_normal_pub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_current_link_state = ")); Dz1Bool_dump(&p->test_pub_current_link_state, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_event_identity = ")); Dz1Bool_dump(&p->test_pub_event_identity, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_identity = ")); Dz1Bool_dump(&p->test_pub_incident_identity, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_incident_conditions = ")); Dz1Bool_dump(&p->test_pub_incident_conditions, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_roadway_surface_status = ")); Dz1Bool_dump(&p->test_pub_roadway_surface_status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_weather_information = ")); Dz1Bool_dump(&p->test_pub_weather_information, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_link_roadway_geometry = ")); Dz1Bool_dump(&p->test_pub_link_roadway_geometry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_probe_vehicle_detection = ")); Dz1Bool_dump(&p->test_pub_probe_vehicle_detection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_detector_collection = ")); Dz1Bool_dump(&p->test_pub_detector_collection, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_extention_comm_pdu = ")); Dz1Bool_dump(&p->test_pub_extention_comm_pdu, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_duplicate = ")); Dz1Bool_dump(&p->test_login_duplicate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_sub = ")); Dz1Bool_dump(&p->test_invalid_sub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs_cancel = ")); Dz1Bool_dump(&p->test_subs_cancel, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_retry = ")); Dz1Bool_dump(&p->test_pub_retry, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulation1TestConfiguration_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2TestConfiguration_clientRole1
TechnicalRegulation2TestConfiguration_clientRole1 *TechnicalRegulation2TestConfiguration_clientRole1_new(Dz1Str peer_ip, 
																										 s64_t peer_port, 
																										 Dz1Str user, 
																										 Dz1Str pass, 
																										 bool_t test_session, 
																										 bool_t test_login_invalid, 
																										 bool_t test_session_maintain, 
																										 bool_t test_normal_pub, 
																										 bool_t test_pub_comm_tx_pdu, 
																										 bool_t test_pub_comm_rx_pdu, 
																										 bool_t test_login_duplicate, 
																										 bool_t test_invalid_sub, 
																										 bool_t test_subs_cancel, 
																										 bool_t test_pub_retry, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation2TestConfiguration_clientRole1 *__internal_ret = (TechnicalRegulation2TestConfiguration_clientRole1 *)Dz1Calloc(sizeof(TechnicalRegulation2TestConfiguration_clientRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2TestConfiguration_clientRole1_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else if (user && (__internal_ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = Dz1Str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->test_session = test_session;
			__internal_ret->test_login_invalid = test_login_invalid;
			__internal_ret->test_session_maintain = test_session_maintain;
			__internal_ret->test_normal_pub = test_normal_pub;
			__internal_ret->test_pub_comm_tx_pdu = test_pub_comm_tx_pdu;
			__internal_ret->test_pub_comm_rx_pdu = test_pub_comm_rx_pdu;
			__internal_ret->test_login_duplicate = test_login_duplicate;
			__internal_ret->test_invalid_sub = test_invalid_sub;
			__internal_ret->test_subs_cancel = test_subs_cancel;
			__internal_ret->test_pub_retry = test_pub_retry;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2TestConfiguration_clientRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulation2TestConfiguration_clientRole1_copy(TechnicalRegulation2TestConfiguration_clientRole1 *dst, TechnicalRegulation2TestConfiguration_clientRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Str_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Str_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->test_session = src->test_session;
		dst->test_login_invalid = src->test_login_invalid;
		dst->test_session_maintain = src->test_session_maintain;
		dst->test_normal_pub = src->test_normal_pub;
		dst->test_pub_comm_tx_pdu = src->test_pub_comm_tx_pdu;
		dst->test_pub_comm_rx_pdu = src->test_pub_comm_rx_pdu;
		dst->test_login_duplicate = src->test_login_duplicate;
		dst->test_invalid_sub = src->test_invalid_sub;
		dst->test_subs_cancel = src->test_subs_cancel;
		dst->test_pub_retry = src->test_pub_retry;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation2TestConfiguration_clientRole1 *TechnicalRegulation2TestConfiguration_clientRole1_clone(TechnicalRegulation2TestConfiguration_clientRole1 *src, Dz1Error *err)
{
	TechnicalRegulation2TestConfiguration_clientRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulation2TestConfiguration_clientRole1 *)Dz1Calloc(sizeof(TechnicalRegulation2TestConfiguration_clientRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2TestConfiguration_clientRole1_delAndSetNull, (void *)&dst);
		if (TechnicalRegulation2TestConfiguration_clientRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2TestConfiguration_clientRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulation2TestConfiguration_clientRole1_purge(TechnicalRegulation2TestConfiguration_clientRole1 *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
	Dz1Str_del(p->peer_ip);
	Dz1Str_del(p->user);
	Dz1Str_del(p->pass);
}

void TechnicalRegulation2TestConfiguration_clientRole1_del(TechnicalRegulation2TestConfiguration_clientRole1 *p)
{
	if (p == NULL) return;
	TechnicalRegulation2TestConfiguration_clientRole1_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation2TestConfiguration_clientRole1_dump(TechnicalRegulation2TestConfiguration_clientRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1s64_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_invalid = ")); Dz1Bool_dump(&p->test_login_invalid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session_maintain = ")); Dz1Bool_dump(&p->test_session_maintain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_normal_pub = ")); Dz1Bool_dump(&p->test_normal_pub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_comm_tx_pdu = ")); Dz1Bool_dump(&p->test_pub_comm_tx_pdu, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_comm_rx_pdu = ")); Dz1Bool_dump(&p->test_pub_comm_rx_pdu, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_duplicate = ")); Dz1Bool_dump(&p->test_login_duplicate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_sub = ")); Dz1Bool_dump(&p->test_invalid_sub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_subs_cancel = ")); Dz1Bool_dump(&p->test_subs_cancel, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_pub_retry = ")); Dz1Bool_dump(&p->test_pub_retry, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulation2TestConfiguration_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1TestConfiguration_serverRole1
TechnicalRegulation1TestConfiguration_serverRole1 *TechnicalRegulation1TestConfiguration_serverRole1_new(s64_t local_port, 
																										 bool_t test_session, 
																										 bool_t test_login_retry, 
																										 bool_t test_normal_sub, 
																										 bool_t test_sub_retry, 
																										 bool_t test_invalid_pub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation1TestConfiguration_serverRole1 *__internal_ret = (TechnicalRegulation1TestConfiguration_serverRole1 *)Dz1Calloc(sizeof(TechnicalRegulation1TestConfiguration_serverRole1), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->local_port = local_port;
		__internal_ret->test_session = test_session;
		__internal_ret->test_login_retry = test_login_retry;
		__internal_ret->test_normal_sub = test_normal_sub;
		__internal_ret->test_sub_retry = test_sub_retry;
		__internal_ret->test_invalid_pub = test_invalid_pub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulation1TestConfiguration_serverRole1_copy(TechnicalRegulation1TestConfiguration_serverRole1 *dst, TechnicalRegulation1TestConfiguration_serverRole1 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_session = src->test_session;
		dst->test_login_retry = src->test_login_retry;
		dst->test_normal_sub = src->test_normal_sub;
		dst->test_sub_retry = src->test_sub_retry;
		dst->test_invalid_pub = src->test_invalid_pub;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation1TestConfiguration_serverRole1 *TechnicalRegulation1TestConfiguration_serverRole1_clone(TechnicalRegulation1TestConfiguration_serverRole1 *src, Dz1Error *err)
{
	TechnicalRegulation1TestConfiguration_serverRole1 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulation1TestConfiguration_serverRole1 *)Dz1Calloc(sizeof(TechnicalRegulation1TestConfiguration_serverRole1), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull, (void *)&dst);
		if (TechnicalRegulation1TestConfiguration_serverRole1_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulation1TestConfiguration_serverRole1_purge(TechnicalRegulation1TestConfiguration_serverRole1 *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
}

void TechnicalRegulation1TestConfiguration_serverRole1_del(TechnicalRegulation1TestConfiguration_serverRole1 *p)
{
	if (p == NULL) return;
	TechnicalRegulation1TestConfiguration_serverRole1_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation1TestConfiguration_serverRole1_dump(TechnicalRegulation1TestConfiguration_serverRole1 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1s64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_session = ")); Dz1Bool_dump(&p->test_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_login_retry = ")); Dz1Bool_dump(&p->test_login_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_normal_sub = ")); Dz1Bool_dump(&p->test_normal_sub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_sub_retry = ")); Dz1Bool_dump(&p->test_sub_retry, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_invalid_pub = ")); Dz1Bool_dump(&p->test_invalid_pub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulation1TestConfiguration_serverRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_clientRole2
TechnicalRegulationTestConfiguration_clientRole2 *TechnicalRegulationTestConfiguration_clientRole2_new(Dz1Str my_domain, 
																									   Dz1Str peer_domain, 
																									   Dz1Str peer_ip, 
																									   s64_t peer_port, 
																									   Dz1Str user, 
																									   Dz1Str pass, 
																									   bool_t test_total, 
																									   s64_t expire_time, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulationTestConfiguration_clientRole2 *__internal_ret = (TechnicalRegulationTestConfiguration_clientRole2 *)Dz1Calloc(sizeof(TechnicalRegulationTestConfiguration_clientRole2), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull, (void *)&__internal_ret);
		
		if (my_domain && (__internal_ret->my_domain = Dz1Str_clone(my_domain, errp)) == NULL) ERR_OUT(errp);
		else if (peer_domain && (__internal_ret->peer_domain = Dz1Str_clone(peer_domain, errp)) == NULL) ERR_OUT(errp);
		else if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else if (user && (__internal_ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = Dz1Str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->test_total = test_total;
			__internal_ret->expire_time = expire_time;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulationTestConfiguration_clientRole2_copy(TechnicalRegulationTestConfiguration_clientRole2 *dst, TechnicalRegulationTestConfiguration_clientRole2 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Str_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Str_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->test_total = src->test_total;
		dst->expire_time = src->expire_time;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulationTestConfiguration_clientRole2 *TechnicalRegulationTestConfiguration_clientRole2_clone(TechnicalRegulationTestConfiguration_clientRole2 *src, Dz1Error *err)
{
	TechnicalRegulationTestConfiguration_clientRole2 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulationTestConfiguration_clientRole2 *)Dz1Calloc(sizeof(TechnicalRegulationTestConfiguration_clientRole2), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull, (void *)&dst);
		if (TechnicalRegulationTestConfiguration_clientRole2_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulationTestConfiguration_clientRole2_purge(TechnicalRegulationTestConfiguration_clientRole2 *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
	Dz1Str_del(p->peer_ip);
	Dz1Str_del(p->user);
	Dz1Str_del(p->pass);
}

void TechnicalRegulationTestConfiguration_clientRole2_del(TechnicalRegulationTestConfiguration_clientRole2 *p)
{
	if (p == NULL) return;
	TechnicalRegulationTestConfiguration_clientRole2_purge(p);
	Dz1Free(p);
}

void TechnicalRegulationTestConfiguration_clientRole2_dump(TechnicalRegulationTestConfiguration_clientRole2 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1s64_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_total = ")); Dz1Bool_dump(&p->test_total, tab); 
		Dz1Thread_tprintf(tab, Dz1T("expire_time = ")); Dz1s64_dump(&p->expire_time, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulationTestConfiguration_clientRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_serverRole2
TechnicalRegulationTestConfiguration_serverRole2 *TechnicalRegulationTestConfiguration_serverRole2_new(Dz1Str my_domain, 
																									   Dz1Str peer_domain, 
																									   s64_t local_port, 
																									   bool_t test_total, 
																									   s64_t subs_timeout_s, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulationTestConfiguration_serverRole2 *__internal_ret = (TechnicalRegulationTestConfiguration_serverRole2 *)Dz1Calloc(sizeof(TechnicalRegulationTestConfiguration_serverRole2), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull, (void *)&__internal_ret);
		
		if (my_domain && (__internal_ret->my_domain = Dz1Str_clone(my_domain, errp)) == NULL) ERR_OUT(errp);
		else if (peer_domain && (__internal_ret->peer_domain = Dz1Str_clone(peer_domain, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->local_port = local_port;
			__internal_ret->test_total = test_total;
			__internal_ret->subs_timeout_s = subs_timeout_s;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulationTestConfiguration_serverRole2_copy(TechnicalRegulationTestConfiguration_serverRole2 *dst, TechnicalRegulationTestConfiguration_serverRole2 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->local_port = src->local_port;
		dst->test_total = src->test_total;
		dst->subs_timeout_s = src->subs_timeout_s;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulationTestConfiguration_serverRole2 *TechnicalRegulationTestConfiguration_serverRole2_clone(TechnicalRegulationTestConfiguration_serverRole2 *src, Dz1Error *err)
{
	TechnicalRegulationTestConfiguration_serverRole2 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulationTestConfiguration_serverRole2 *)Dz1Calloc(sizeof(TechnicalRegulationTestConfiguration_serverRole2), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull, (void *)&dst);
		if (TechnicalRegulationTestConfiguration_serverRole2_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulationTestConfiguration_serverRole2_purge(TechnicalRegulationTestConfiguration_serverRole2 *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_domain);
}

void TechnicalRegulationTestConfiguration_serverRole2_del(TechnicalRegulationTestConfiguration_serverRole2 *p)
{
	if (p == NULL) return;
	TechnicalRegulationTestConfiguration_serverRole2_purge(p);
	Dz1Free(p);
}

void TechnicalRegulationTestConfiguration_serverRole2_dump(TechnicalRegulationTestConfiguration_serverRole2 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("local_port = ")); Dz1s64_dump(&p->local_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_total = ")); Dz1Bool_dump(&p->test_total, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subs_timeout_s = ")); Dz1s64_dump(&p->subs_timeout_s, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulationTestConfiguration_serverRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_duoClientRole
TechnicalRegulationTestConfiguration_duoClientRole *TechnicalRegulationTestConfiguration_duoClientRole_new(Dz1Str peer_domain, 
																										   Dz1Str peer_ip, 
																										   s64_t peer_port, 
																										   Dz1Str my_domain1, 
																										   Dz1Str user1, 
																										   Dz1Str pass1, 
																										   Dz1Str my_domain2, 
																										   Dz1Str user2, 
																										   Dz1Str pass2, 
																										   bool_t test_duo_client, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulationTestConfiguration_duoClientRole *__internal_ret = (TechnicalRegulationTestConfiguration_duoClientRole *)Dz1Calloc(sizeof(TechnicalRegulationTestConfiguration_duoClientRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull, (void *)&__internal_ret);
		
		if (peer_domain && (__internal_ret->peer_domain = Dz1Str_clone(peer_domain, errp)) == NULL) ERR_OUT(errp);
		else if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else if (my_domain1 && (__internal_ret->my_domain1 = Dz1Str_clone(my_domain1, errp)) == NULL) ERR_OUT(errp);
		else if (user1 && (__internal_ret->user1 = Dz1Str_clone(user1, errp)) == NULL) ERR_OUT(errp);
		else if (pass1 && (__internal_ret->pass1 = Dz1Str_clone(pass1, errp)) == NULL) ERR_OUT(errp);
		else if (my_domain2 && (__internal_ret->my_domain2 = Dz1Str_clone(my_domain2, errp)) == NULL) ERR_OUT(errp);
		else if (user2 && (__internal_ret->user2 = Dz1Str_clone(user2, errp)) == NULL) ERR_OUT(errp);
		else if (pass2 && (__internal_ret->pass2 = Dz1Str_clone(pass2, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer_port = peer_port;
			__internal_ret->test_duo_client = test_duo_client;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulationTestConfiguration_duoClientRole_copy(TechnicalRegulationTestConfiguration_duoClientRole *dst, TechnicalRegulationTestConfiguration_duoClientRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->peer_domain && (dst->peer_domain = Dz1Str_clone(src->peer_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->my_domain1 && (dst->my_domain1 = Dz1Str_clone(src->my_domain1, errp)) == NULL) ERR_OUT(errp);
	else if (src->user1 && (dst->user1 = Dz1Str_clone(src->user1, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass1 && (dst->pass1 = Dz1Str_clone(src->pass1, errp)) == NULL) ERR_OUT(errp);
	else if (src->my_domain2 && (dst->my_domain2 = Dz1Str_clone(src->my_domain2, errp)) == NULL) ERR_OUT(errp);
	else if (src->user2 && (dst->user2 = Dz1Str_clone(src->user2, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass2 && (dst->pass2 = Dz1Str_clone(src->pass2, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->peer_port = src->peer_port;
		dst->test_duo_client = src->test_duo_client;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulationTestConfiguration_duoClientRole *TechnicalRegulationTestConfiguration_duoClientRole_clone(TechnicalRegulationTestConfiguration_duoClientRole *src, Dz1Error *err)
{
	TechnicalRegulationTestConfiguration_duoClientRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulationTestConfiguration_duoClientRole *)Dz1Calloc(sizeof(TechnicalRegulationTestConfiguration_duoClientRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull, (void *)&dst);
		if (TechnicalRegulationTestConfiguration_duoClientRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulationTestConfiguration_duoClientRole_purge(TechnicalRegulationTestConfiguration_duoClientRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->peer_domain);
	Dz1Str_del(p->peer_ip);
	Dz1Str_del(p->my_domain1);
	Dz1Str_del(p->user1);
	Dz1Str_del(p->pass1);
	Dz1Str_del(p->my_domain2);
	Dz1Str_del(p->user2);
	Dz1Str_del(p->pass2);
}

void TechnicalRegulationTestConfiguration_duoClientRole_del(TechnicalRegulationTestConfiguration_duoClientRole *p)
{
	if (p == NULL) return;
	TechnicalRegulationTestConfiguration_duoClientRole_purge(p);
	Dz1Free(p);
}

void TechnicalRegulationTestConfiguration_duoClientRole_dump(TechnicalRegulationTestConfiguration_duoClientRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Str_dump(p->peer_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_port = ")); Dz1s64_dump(&p->peer_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_domain1 = ")); Dz1Str_dump(p->my_domain1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user1 = ")); Dz1Str_dump(p->user1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass1 = ")); Dz1Str_dump(p->pass1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_domain2 = ")); Dz1Str_dump(p->my_domain2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user2 = ")); Dz1Str_dump(p->user2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass2 = ")); Dz1Str_dump(p->pass2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("test_duo_client = ")); Dz1Bool_dump(&p->test_duo_client, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulationTestConfiguration_duoClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_duoSessionRole
TechnicalRegulationTestConfiguration_duoSessionRole *TechnicalRegulationTestConfiguration_duoSessionRole_new(bool_t test_duo_session, 
																											 Dz1Str my_domain, 
																											 Dz1Str peer_ip, 
																											 Dz1Str peer_server_domain, 
																											 s64_t peer_server_port, 
																											 Dz1Str user, 
																											 Dz1Str pass, 
																											 Dz1Str peer_client_domain, 
																											 s64_t peer_client_port, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulationTestConfiguration_duoSessionRole *__internal_ret = (TechnicalRegulationTestConfiguration_duoSessionRole *)Dz1Calloc(sizeof(TechnicalRegulationTestConfiguration_duoSessionRole), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull, (void *)&__internal_ret);
		
		if (my_domain && (__internal_ret->my_domain = Dz1Str_clone(my_domain, errp)) == NULL) ERR_OUT(errp);
		else if (peer_ip && (__internal_ret->peer_ip = Dz1Str_clone(peer_ip, errp)) == NULL) ERR_OUT(errp);
		else if (peer_server_domain && (__internal_ret->peer_server_domain = Dz1Str_clone(peer_server_domain, errp)) == NULL) ERR_OUT(errp);
		else if (user && (__internal_ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = Dz1Str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else if (peer_client_domain && (__internal_ret->peer_client_domain = Dz1Str_clone(peer_client_domain, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->test_duo_session = test_duo_session;
			__internal_ret->peer_server_port = peer_server_port;
			__internal_ret->peer_client_port = peer_client_port;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TechnicalRegulationTestConfiguration_duoSessionRole_copy(TechnicalRegulationTestConfiguration_duoSessionRole *dst, TechnicalRegulationTestConfiguration_duoSessionRole *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->my_domain && (dst->my_domain = Dz1Str_clone(src->my_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_ip && (dst->peer_ip = Dz1Str_clone(src->peer_ip, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_server_domain && (dst->peer_server_domain = Dz1Str_clone(src->peer_server_domain, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Str_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Str_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else if (src->peer_client_domain && (dst->peer_client_domain = Dz1Str_clone(src->peer_client_domain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->test_duo_session = src->test_duo_session;
		dst->peer_server_port = src->peer_server_port;
		dst->peer_client_port = src->peer_client_port;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulationTestConfiguration_duoSessionRole *TechnicalRegulationTestConfiguration_duoSessionRole_clone(TechnicalRegulationTestConfiguration_duoSessionRole *src, Dz1Error *err)
{
	TechnicalRegulationTestConfiguration_duoSessionRole *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TechnicalRegulationTestConfiguration_duoSessionRole *)Dz1Calloc(sizeof(TechnicalRegulationTestConfiguration_duoSessionRole), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull, (void *)&dst);
		if (TechnicalRegulationTestConfiguration_duoSessionRole_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TechnicalRegulationTestConfiguration_duoSessionRole_purge(TechnicalRegulationTestConfiguration_duoSessionRole *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->my_domain);
	Dz1Str_del(p->peer_ip);
	Dz1Str_del(p->peer_server_domain);
	Dz1Str_del(p->user);
	Dz1Str_del(p->pass);
	Dz1Str_del(p->peer_client_domain);
}

void TechnicalRegulationTestConfiguration_duoSessionRole_del(TechnicalRegulationTestConfiguration_duoSessionRole *p)
{
	if (p == NULL) return;
	TechnicalRegulationTestConfiguration_duoSessionRole_purge(p);
	Dz1Free(p);
}

void TechnicalRegulationTestConfiguration_duoSessionRole_dump(TechnicalRegulationTestConfiguration_duoSessionRole *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("test_duo_session = ")); Dz1Bool_dump(&p->test_duo_session, tab); 
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Str_dump(p->my_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_ip = ")); Dz1Str_dump(p->peer_ip, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_server_domain = ")); Dz1Str_dump(p->peer_server_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_server_port = ")); Dz1s64_dump(&p->peer_server_port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_client_domain = ")); Dz1Str_dump(p->peer_client_domain, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peer_client_port = ")); Dz1s64_dump(&p->peer_client_port, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TechnicalRegulationTestConfiguration_duoSessionRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConfigurationPresent
static struct Iso14827TestConfigurationPresentMapA
{
	str_t str;
	Iso14827TestConfigurationPresent v;
} Iso14827TestConfigurationPresentMapA[] =
{
	{ (char *)"centerClient2rse", Iso14827TestConfigurationPresent_centerClient2rse },
	{ (char *)"rseServer2center", Iso14827TestConfigurationPresent_rseServer2center },
	{ (char *)"rseClient2center", Iso14827TestConfigurationPresent_rseClient2center },
	{ (char *)"centerServer2rse", Iso14827TestConfigurationPresent_centerServer2rse },
	{ (char *)"signalserver2center", Iso14827TestConfigurationPresent_signalserver2center },
	{ (char *)"itsk00100_3c2cClient", Iso14827TestConfigurationPresent_itsk00100_3c2cClient },
	{ (char *)"itsk00100_3c2cServer", Iso14827TestConfigurationPresent_itsk00100_3c2cServer },
	{ (char *)"technical_regulation1_clientRole1", Iso14827TestConfigurationPresent_technical_regulation1_clientRole1 },
	{ (char *)"technical_regulation1_serverRole1", Iso14827TestConfigurationPresent_technical_regulation1_serverRole1 },
	{ (char *)"technical_regulation2_clientRole", Iso14827TestConfigurationPresent_technical_regulation2_clientRole },
	{ (char *)"technical_regulation1_clientRole2", Iso14827TestConfigurationPresent_technical_regulation1_clientRole2 },
	{ (char *)"technical_regulation1_serverRole2", Iso14827TestConfigurationPresent_technical_regulation1_serverRole2 },
	{ (char *)"technical_regulation1_duoClientRole", Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole },
	{ (char *)"technical_regulation1_duoSessionRole", Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole },
	{ (char *)"technical_regulation2_clientRole2", Iso14827TestConfigurationPresent_technical_regulation2_clientRole2 },
	{ (char *)"technical_regulation2_serverRole2", Iso14827TestConfigurationPresent_technical_regulation2_serverRole2 },
	{ (char *)"technical_regulation2_duoClientRole", Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole },
	{ (char *)"technical_regulation2_duoSessionRole", Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole },
	{ NULL, Iso14827TestConfigurationPresent_max }
};

str_t Iso14827TestConfigurationPresentStrA(Iso14827TestConfigurationPresent v)
{
	struct Iso14827TestConfigurationPresentMapA *i = NULL;
	for (i = Iso14827TestConfigurationPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestConfigurationPresent Iso14827TestConfigurationPresentFromStrA(str_t str)
{
	struct Iso14827TestConfigurationPresentMapA *i = NULL;
	for (i = Iso14827TestConfigurationPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestConfigurationPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestConfigurationPresentMapW
{
	wstr_t str;
	Iso14827TestConfigurationPresent v;
} Iso14827TestConfigurationPresentMapW[] =
{
	{ (wchar_t *)L"centerClient2rse", Iso14827TestConfigurationPresent_centerClient2rse },
	{ (wchar_t *)L"rseServer2center", Iso14827TestConfigurationPresent_rseServer2center },
	{ (wchar_t *)L"rseClient2center", Iso14827TestConfigurationPresent_rseClient2center },
	{ (wchar_t *)L"centerServer2rse", Iso14827TestConfigurationPresent_centerServer2rse },
	{ (wchar_t *)L"signalserver2center", Iso14827TestConfigurationPresent_signalserver2center },
	{ (wchar_t *)L"itsk00100_3c2cClient", Iso14827TestConfigurationPresent_itsk00100_3c2cClient },
	{ (wchar_t *)L"itsk00100_3c2cServer", Iso14827TestConfigurationPresent_itsk00100_3c2cServer },
	{ (wchar_t *)L"technical_regulation1_clientRole1", Iso14827TestConfigurationPresent_technical_regulation1_clientRole1 },
	{ (wchar_t *)L"technical_regulation1_serverRole1", Iso14827TestConfigurationPresent_technical_regulation1_serverRole1 },
	{ (wchar_t *)L"technical_regulation2_clientRole", Iso14827TestConfigurationPresent_technical_regulation2_clientRole },
	{ (wchar_t *)L"technical_regulation1_clientRole2", Iso14827TestConfigurationPresent_technical_regulation1_clientRole2 },
	{ (wchar_t *)L"technical_regulation1_serverRole2", Iso14827TestConfigurationPresent_technical_regulation1_serverRole2 },
	{ (wchar_t *)L"technical_regulation1_duoClientRole", Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole },
	{ (wchar_t *)L"technical_regulation1_duoSessionRole", Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole },
	{ (wchar_t *)L"technical_regulation2_clientRole2", Iso14827TestConfigurationPresent_technical_regulation2_clientRole2 },
	{ (wchar_t *)L"technical_regulation2_serverRole2", Iso14827TestConfigurationPresent_technical_regulation2_serverRole2 },
	{ (wchar_t *)L"technical_regulation2_duoClientRole", Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole },
	{ (wchar_t *)L"technical_regulation2_duoSessionRole", Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole },
	{ NULL, Iso14827TestConfigurationPresent_max }
};

wstr_t Iso14827TestConfigurationPresentStrW(Iso14827TestConfigurationPresent v)
{
	struct Iso14827TestConfigurationPresentMapW *i = NULL;
	for (i = Iso14827TestConfigurationPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestConfigurationPresent Iso14827TestConfigurationPresentFromStrW(wstr_t str)
{
	struct Iso14827TestConfigurationPresentMapW *i = NULL;
	for (i = Iso14827TestConfigurationPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestConfigurationPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestConfigurationPresent *Iso14827TestConfigurationPresent_new(Iso14827TestConfigurationPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestConfigurationPresent *__internal_ret = (Iso14827TestConfigurationPresent *)Dz1Calloc(sizeof(Iso14827TestConfigurationPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestConfigurationPresent_dump(Iso14827TestConfigurationPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestConfigurationPresentStr(*v));
}
// Iso14827TestConfigurationPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConfiguration
Iso14827TestConfiguration *Iso14827TestConfiguration_new(Iso14827TestConfigurationPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestConfiguration *ret = (Iso14827TestConfiguration *)Dz1Calloc(sizeof(Iso14827TestConfiguration), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestConfiguration_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TestConfigurationPresent_centerClient2rse:
			// _U_cst_clone
			if (ptr != NULL) ret->x.centerClient2rse = (PolicePrj4TestConfiguration_centerClient2rse *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_rseServer2center:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rseServer2center = (PolicePrj4TestConfiguration_rseServer2center *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_rseClient2center:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rseClient2center = (PolicePrj4TestConfiguration_rseClient2center *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_centerServer2rse:
			// _U_cst_clone
			if (ptr != NULL) ret->x.centerServer2rse = (PolicePrj4TestConfiguration_centerServer2rse *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_signalserver2center:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signalserver2center = (PolicePrj4TestConfiguration_signalserverServer2center *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_itsk00100_3c2cClient:
			// _U_cst_clone
			if (ptr != NULL) ret->x.itsk00100_3c2cClient = (ITSK00100_3TestConfigurationClientRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_itsk00100_3c2cServer:
			// _U_cst_clone
			if (ptr != NULL) ret->x.itsk00100_3c2cServer = (ITSK00100_3TestConfigurationServerRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_clientRole1:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation1_clientRole1 = (TechnicalRegulation1TestConfiguration_clientRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_serverRole1:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation1_serverRole1 = (TechnicalRegulation1TestConfiguration_serverRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_clientRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation2_clientRole = (TechnicalRegulation2TestConfiguration_clientRole1 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_clientRole2:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation1_clientRole2 = (TechnicalRegulationTestConfiguration_clientRole2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_serverRole2:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation1_serverRole2 = (TechnicalRegulationTestConfiguration_serverRole2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation1_duoClientRole = (TechnicalRegulationTestConfiguration_duoClientRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation1_duoSessionRole = (TechnicalRegulationTestConfiguration_duoSessionRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_clientRole2:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation2_clientRole2 = (TechnicalRegulationTestConfiguration_clientRole2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_serverRole2:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation2_serverRole2 = (TechnicalRegulationTestConfiguration_serverRole2 *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation2_duoClientRole = (TechnicalRegulationTestConfiguration_duoClientRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole:
			// _U_cst_clone
			if (ptr != NULL) ret->x.technical_regulation2_duoSessionRole = (TechnicalRegulationTestConfiguration_duoSessionRole *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestConfigurationPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestConfiguration_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827TestConfiguration_copy(Iso14827TestConfiguration *ret, Iso14827TestConfiguration *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827TestConfigurationPresent_centerClient2rse:
			// _U_cst_clone
			if (src->x.centerClient2rse && (ret->x.centerClient2rse = PolicePrj4TestConfiguration_centerClient2rse_clone(src->x.centerClient2rse, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_rseServer2center:
			// _U_cst_clone
			if (src->x.rseServer2center && (ret->x.rseServer2center = PolicePrj4TestConfiguration_rseServer2center_clone(src->x.rseServer2center, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_rseClient2center:
			// _U_cst_clone
			if (src->x.rseClient2center && (ret->x.rseClient2center = PolicePrj4TestConfiguration_rseClient2center_clone(src->x.rseClient2center, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_centerServer2rse:
			// _U_cst_clone
			if (src->x.centerServer2rse && (ret->x.centerServer2rse = PolicePrj4TestConfiguration_centerServer2rse_clone(src->x.centerServer2rse, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_signalserver2center:
			// _U_cst_clone
			if (src->x.signalserver2center && (ret->x.signalserver2center = PolicePrj4TestConfiguration_signalserverServer2center_clone(src->x.signalserver2center, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_itsk00100_3c2cClient:
			// _U_cst_clone
			if (src->x.itsk00100_3c2cClient && (ret->x.itsk00100_3c2cClient = ITSK00100_3TestConfigurationClientRole_clone(src->x.itsk00100_3c2cClient, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_itsk00100_3c2cServer:
			// _U_cst_clone
			if (src->x.itsk00100_3c2cServer && (ret->x.itsk00100_3c2cServer = ITSK00100_3TestConfigurationServerRole_clone(src->x.itsk00100_3c2cServer, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_clientRole1:
			// _U_cst_clone
			if (src->x.technical_regulation1_clientRole1 && (ret->x.technical_regulation1_clientRole1 = TechnicalRegulation1TestConfiguration_clientRole1_clone(src->x.technical_regulation1_clientRole1, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_serverRole1:
			// _U_cst_clone
			if (src->x.technical_regulation1_serverRole1 && (ret->x.technical_regulation1_serverRole1 = TechnicalRegulation1TestConfiguration_serverRole1_clone(src->x.technical_regulation1_serverRole1, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_clientRole:
			// _U_cst_clone
			if (src->x.technical_regulation2_clientRole && (ret->x.technical_regulation2_clientRole = TechnicalRegulation2TestConfiguration_clientRole1_clone(src->x.technical_regulation2_clientRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_clientRole2:
			// _U_cst_clone
			if (src->x.technical_regulation1_clientRole2 && (ret->x.technical_regulation1_clientRole2 = TechnicalRegulationTestConfiguration_clientRole2_clone(src->x.technical_regulation1_clientRole2, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_serverRole2:
			// _U_cst_clone
			if (src->x.technical_regulation1_serverRole2 && (ret->x.technical_regulation1_serverRole2 = TechnicalRegulationTestConfiguration_serverRole2_clone(src->x.technical_regulation1_serverRole2, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole:
			// _U_cst_clone
			if (src->x.technical_regulation1_duoClientRole && (ret->x.technical_regulation1_duoClientRole = TechnicalRegulationTestConfiguration_duoClientRole_clone(src->x.technical_regulation1_duoClientRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole:
			// _U_cst_clone
			if (src->x.technical_regulation1_duoSessionRole && (ret->x.technical_regulation1_duoSessionRole = TechnicalRegulationTestConfiguration_duoSessionRole_clone(src->x.technical_regulation1_duoSessionRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_clientRole2:
			// _U_cst_clone
			if (src->x.technical_regulation2_clientRole2 && (ret->x.technical_regulation2_clientRole2 = TechnicalRegulationTestConfiguration_clientRole2_clone(src->x.technical_regulation2_clientRole2, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_serverRole2:
			// _U_cst_clone
			if (src->x.technical_regulation2_serverRole2 && (ret->x.technical_regulation2_serverRole2 = TechnicalRegulationTestConfiguration_serverRole2_clone(src->x.technical_regulation2_serverRole2, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole:
			// _U_cst_clone
			if (src->x.technical_regulation2_duoClientRole && (ret->x.technical_regulation2_duoClientRole = TechnicalRegulationTestConfiguration_duoClientRole_clone(src->x.technical_regulation2_duoClientRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole:
			// _U_cst_clone
			if (src->x.technical_regulation2_duoSessionRole && (ret->x.technical_regulation2_duoSessionRole = TechnicalRegulationTestConfiguration_duoSessionRole_clone(src->x.technical_regulation2_duoSessionRole, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestConfiguration *Iso14827TestConfiguration_clone(Iso14827TestConfiguration *src, Dz1Error *err)
{
	Iso14827TestConfiguration *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827TestConfiguration *)Dz1Calloc(sizeof(Iso14827TestConfiguration), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestConfiguration_delAndSetNull, (void *)&ret);
		if (Iso14827TestConfiguration_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestConfiguration_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestConfiguration_purge(Iso14827TestConfiguration *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TestConfigurationPresent_centerClient2rse:
		PolicePrj4TestConfiguration_centerClient2rse_del(p->x.centerClient2rse);
		break;
	case Iso14827TestConfigurationPresent_rseServer2center:
		PolicePrj4TestConfiguration_rseServer2center_del(p->x.rseServer2center);
		break;
	case Iso14827TestConfigurationPresent_rseClient2center:
		PolicePrj4TestConfiguration_rseClient2center_del(p->x.rseClient2center);
		break;
	case Iso14827TestConfigurationPresent_centerServer2rse:
		PolicePrj4TestConfiguration_centerServer2rse_del(p->x.centerServer2rse);
		break;
	case Iso14827TestConfigurationPresent_signalserver2center:
		PolicePrj4TestConfiguration_signalserverServer2center_del(p->x.signalserver2center);
		break;
	case Iso14827TestConfigurationPresent_itsk00100_3c2cClient:
		ITSK00100_3TestConfigurationClientRole_del(p->x.itsk00100_3c2cClient);
		break;
	case Iso14827TestConfigurationPresent_itsk00100_3c2cServer:
		ITSK00100_3TestConfigurationServerRole_del(p->x.itsk00100_3c2cServer);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_clientRole1:
		TechnicalRegulation1TestConfiguration_clientRole1_del(p->x.technical_regulation1_clientRole1);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_serverRole1:
		TechnicalRegulation1TestConfiguration_serverRole1_del(p->x.technical_regulation1_serverRole1);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_clientRole:
		TechnicalRegulation2TestConfiguration_clientRole1_del(p->x.technical_regulation2_clientRole);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_clientRole2:
		TechnicalRegulationTestConfiguration_clientRole2_del(p->x.technical_regulation1_clientRole2);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_serverRole2:
		TechnicalRegulationTestConfiguration_serverRole2_del(p->x.technical_regulation1_serverRole2);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole:
		TechnicalRegulationTestConfiguration_duoClientRole_del(p->x.technical_regulation1_duoClientRole);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole:
		TechnicalRegulationTestConfiguration_duoSessionRole_del(p->x.technical_regulation1_duoSessionRole);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_clientRole2:
		TechnicalRegulationTestConfiguration_clientRole2_del(p->x.technical_regulation2_clientRole2);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_serverRole2:
		TechnicalRegulationTestConfiguration_serverRole2_del(p->x.technical_regulation2_serverRole2);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole:
		TechnicalRegulationTestConfiguration_duoClientRole_del(p->x.technical_regulation2_duoClientRole);
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole:
		TechnicalRegulationTestConfiguration_duoSessionRole_del(p->x.technical_regulation2_duoSessionRole);
		break;
	default:
		break;
	}
}

void Iso14827TestConfiguration_del(Iso14827TestConfiguration *p)
{
	if (!p) return;
	Iso14827TestConfiguration_purge(p);
	Dz1Free(p);
}

void Iso14827TestConfiguration_dump(Iso14827TestConfiguration *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TestConfigurationPresent_centerClient2rse:
		Dz1Thread_printf(Dz1T("centerClient2rse = ")); PolicePrj4TestConfiguration_centerClient2rse_dump(p->x.centerClient2rse, tab); 
		break;
	case Iso14827TestConfigurationPresent_rseServer2center:
		Dz1Thread_printf(Dz1T("rseServer2center = ")); PolicePrj4TestConfiguration_rseServer2center_dump(p->x.rseServer2center, tab); 
		break;
	case Iso14827TestConfigurationPresent_rseClient2center:
		Dz1Thread_printf(Dz1T("rseClient2center = ")); PolicePrj4TestConfiguration_rseClient2center_dump(p->x.rseClient2center, tab); 
		break;
	case Iso14827TestConfigurationPresent_centerServer2rse:
		Dz1Thread_printf(Dz1T("centerServer2rse = ")); PolicePrj4TestConfiguration_centerServer2rse_dump(p->x.centerServer2rse, tab); 
		break;
	case Iso14827TestConfigurationPresent_signalserver2center:
		Dz1Thread_printf(Dz1T("signalserver2center = ")); PolicePrj4TestConfiguration_signalserverServer2center_dump(p->x.signalserver2center, tab); 
		break;
	case Iso14827TestConfigurationPresent_itsk00100_3c2cClient:
		Dz1Thread_printf(Dz1T("itsk00100_3c2cClient = ")); ITSK00100_3TestConfigurationClientRole_dump(p->x.itsk00100_3c2cClient, tab); 
		break;
	case Iso14827TestConfigurationPresent_itsk00100_3c2cServer:
		Dz1Thread_printf(Dz1T("itsk00100_3c2cServer = ")); ITSK00100_3TestConfigurationServerRole_dump(p->x.itsk00100_3c2cServer, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_clientRole1:
		Dz1Thread_printf(Dz1T("technical_regulation1_clientRole1 = ")); TechnicalRegulation1TestConfiguration_clientRole1_dump(p->x.technical_regulation1_clientRole1, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_serverRole1:
		Dz1Thread_printf(Dz1T("technical_regulation1_serverRole1 = ")); TechnicalRegulation1TestConfiguration_serverRole1_dump(p->x.technical_regulation1_serverRole1, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_clientRole:
		Dz1Thread_printf(Dz1T("technical_regulation2_clientRole = ")); TechnicalRegulation2TestConfiguration_clientRole1_dump(p->x.technical_regulation2_clientRole, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_clientRole2:
		Dz1Thread_printf(Dz1T("technical_regulation1_clientRole2 = ")); TechnicalRegulationTestConfiguration_clientRole2_dump(p->x.technical_regulation1_clientRole2, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_serverRole2:
		Dz1Thread_printf(Dz1T("technical_regulation1_serverRole2 = ")); TechnicalRegulationTestConfiguration_serverRole2_dump(p->x.technical_regulation1_serverRole2, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole:
		Dz1Thread_printf(Dz1T("technical_regulation1_duoClientRole = ")); TechnicalRegulationTestConfiguration_duoClientRole_dump(p->x.technical_regulation1_duoClientRole, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole:
		Dz1Thread_printf(Dz1T("technical_regulation1_duoSessionRole = ")); TechnicalRegulationTestConfiguration_duoSessionRole_dump(p->x.technical_regulation1_duoSessionRole, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_clientRole2:
		Dz1Thread_printf(Dz1T("technical_regulation2_clientRole2 = ")); TechnicalRegulationTestConfiguration_clientRole2_dump(p->x.technical_regulation2_clientRole2, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_serverRole2:
		Dz1Thread_printf(Dz1T("technical_regulation2_serverRole2 = ")); TechnicalRegulationTestConfiguration_serverRole2_dump(p->x.technical_regulation2_serverRole2, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole:
		Dz1Thread_printf(Dz1T("technical_regulation2_duoClientRole = ")); TechnicalRegulationTestConfiguration_duoClientRole_dump(p->x.technical_regulation2_duoClientRole, tab); 
		break;
	case Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole:
		Dz1Thread_printf(Dz1T("technical_regulation2_duoSessionRole = ")); TechnicalRegulationTestConfiguration_duoSessionRole_dump(p->x.technical_regulation2_duoSessionRole, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827TestConfiguration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperC2CHookArg
Iso14827TestHelperC2CHookArg *Iso14827TestHelperC2CHookArg_new(Iso14827C2CAuthMsg *msg, 
															   Dz1Str current_test, 
															   bool_t isReceived, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperC2CHookArg *__internal_ret = (Iso14827TestHelperC2CHookArg *)Dz1Calloc(sizeof(Iso14827TestHelperC2CHookArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperC2CHookArg_delAndSetNull, (void *)&__internal_ret);
		
		if (current_test && (__internal_ret->current_test = Dz1Str_clone(current_test, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->msg = msg;
			__internal_ret->isReceived = isReceived;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperC2CHookArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TestHelperC2CHookArg_copy(Iso14827TestHelperC2CHookArg *dst, Iso14827TestHelperC2CHookArg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->msg && (dst->msg = Iso14827C2CAuthMsg_clone(src->msg, errp)) == NULL) ERR_OUT(errp);
	else if (src->current_test && (dst->current_test = Dz1Str_clone(src->current_test, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->isReceived = src->isReceived;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TestHelperC2CHookArg *Iso14827TestHelperC2CHookArg_clone(Iso14827TestHelperC2CHookArg *src, Dz1Error *err)
{
	Iso14827TestHelperC2CHookArg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TestHelperC2CHookArg *)Dz1Calloc(sizeof(Iso14827TestHelperC2CHookArg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperC2CHookArg_delAndSetNull, (void *)&dst);
		if (Iso14827TestHelperC2CHookArg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperC2CHookArg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TestHelperC2CHookArg_purge(Iso14827TestHelperC2CHookArg *p)
{
	if (p == NULL) return;
	Iso14827C2CAuthMsg_del(p->msg);
	Dz1Str_del(p->current_test);
}

void Iso14827TestHelperC2CHookArg_del(Iso14827TestHelperC2CHookArg *p)
{
	if (p == NULL) return;
	Iso14827TestHelperC2CHookArg_purge(p);
	Dz1Free(p);
}

void Iso14827TestHelperC2CHookArg_dump(Iso14827TestHelperC2CHookArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("msg = ")); Iso14827C2CAuthMsg_dump(p->msg, tab); 
		Dz1Thread_tprintf(tab, Dz1T("current_test = ")); Dz1Str_dump(p->current_test, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isReceived = ")); Dz1Bool_dump(&p->isReceived, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TestHelperC2CHookArg
////////////////////////////////////////////////////////////////////////////////

