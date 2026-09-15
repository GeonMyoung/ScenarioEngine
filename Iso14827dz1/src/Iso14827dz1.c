////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827dz1.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827Cost
Iso14827Cost *Iso14827Cost_new(Dz1Asn1OctetStr *currency, 
							   s32_t factor, 
							   s32_t qty, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Cost *__internal_ret = (Iso14827Cost *)Dz1Calloc(sizeof(Iso14827Cost), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Cost_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->currency = currency;
		__internal_ret->factor = factor;
		__internal_ret->qty = qty;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Cost_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827Cost_copy(Iso14827Cost *dst, Iso14827Cost *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->currency && (dst->currency = Dz1Asn1OctetStr_clone(src->currency, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->factor = src->factor;
		dst->qty = src->qty;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827Cost *Iso14827Cost_clone(Iso14827Cost *src, Dz1Error *err)
{
	Iso14827Cost *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827Cost *)Dz1Calloc(sizeof(Iso14827Cost), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Cost_delAndSetNull, (void *)&dst);
		if (Iso14827Cost_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Cost_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827Cost_purge(Iso14827Cost *p)
{
	if (p == NULL) return;
	Dz1Asn1OctetStr_del(p->currency);
}

void Iso14827Cost_del(Iso14827Cost *p)
{
	if (p == NULL) return;
	Iso14827Cost_purge(p);
	Dz1Free(p);
}

void Iso14827Cost_dump(Iso14827Cost *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("currency = ")); Dz1Asn1OctetStr_dump(p->currency, tab); 
		Dz1Thread_tprintf(tab, Dz1T("factor = ")); Dz1s32_dump(&p->factor, tab); 
		Dz1Thread_tprintf(tab, Dz1T("qty = ")); Dz1s32_dump(&p->qty, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827Cost
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TimeFracPresent
static struct Iso14827TimeFracPresentMapA
{
	str_t str;
	Iso14827TimeFracPresent v;
} Iso14827TimeFracPresentMapA[] =
{
	{ (char *)"deci", Iso14827TimeFracPresent_deci },
	{ (char *)"centi", Iso14827TimeFracPresent_centi },
	{ (char *)"milli", Iso14827TimeFracPresent_milli },
	{ NULL, Iso14827TimeFracPresent_max }
};

str_t Iso14827TimeFracPresentStrA(Iso14827TimeFracPresent v)
{
	struct Iso14827TimeFracPresentMapA *i = NULL;
	for (i = Iso14827TimeFracPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TimeFracPresent Iso14827TimeFracPresentFromStrA(str_t str)
{
	struct Iso14827TimeFracPresentMapA *i = NULL;
	for (i = Iso14827TimeFracPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TimeFracPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TimeFracPresentMapW
{
	wstr_t str;
	Iso14827TimeFracPresent v;
} Iso14827TimeFracPresentMapW[] =
{
	{ (wchar_t *)L"deci", Iso14827TimeFracPresent_deci },
	{ (wchar_t *)L"centi", Iso14827TimeFracPresent_centi },
	{ (wchar_t *)L"milli", Iso14827TimeFracPresent_milli },
	{ NULL, Iso14827TimeFracPresent_max }
};

wstr_t Iso14827TimeFracPresentStrW(Iso14827TimeFracPresent v)
{
	struct Iso14827TimeFracPresentMapW *i = NULL;
	for (i = Iso14827TimeFracPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TimeFracPresent Iso14827TimeFracPresentFromStrW(wstr_t str)
{
	struct Iso14827TimeFracPresentMapW *i = NULL;
	for (i = Iso14827TimeFracPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TimeFracPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TimeFracPresent *Iso14827TimeFracPresent_new(Iso14827TimeFracPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TimeFracPresent *__internal_ret = (Iso14827TimeFracPresent *)Dz1Calloc(sizeof(Iso14827TimeFracPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TimeFracPresent_dump(Iso14827TimeFracPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TimeFracPresentStr(*v));
}
// Iso14827TimeFracPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TimeFrac
Iso14827TimeFrac *Iso14827TimeFrac_new(Iso14827TimeFracPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TimeFrac *ret = (Iso14827TimeFrac *)Dz1Calloc(sizeof(Iso14827TimeFrac), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TimeFrac_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TimeFracPresent_deci:
			// _U_prim_clone
			if (ptr != NULL) ret->x.deci = *(s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TimeFracPresent_centi:
			// _U_prim_clone
			if (ptr != NULL) ret->x.centi = *(s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TimeFracPresent_milli:
			// _U_prim_clone
			if (ptr != NULL) ret->x.milli = *(s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TimeFracPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TimeFrac_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827TimeFrac_copy(Iso14827TimeFrac *ret, Iso14827TimeFrac *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827TimeFracPresent_deci:
			// _U_prim_clone
			ret->x.deci = src->x.deci;
			ERR_CLEAR(errp);
			break;
		case Iso14827TimeFracPresent_centi:
			// _U_prim_clone
			ret->x.centi = src->x.centi;
			ERR_CLEAR(errp);
			break;
		case Iso14827TimeFracPresent_milli:
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

Iso14827TimeFrac *Iso14827TimeFrac_clone(Iso14827TimeFrac *src, Dz1Error *err)
{
	Iso14827TimeFrac *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827TimeFrac *)Dz1Calloc(sizeof(Iso14827TimeFrac), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TimeFrac_delAndSetNull, (void *)&ret);
		if (Iso14827TimeFrac_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TimeFrac_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TimeFrac_purge(Iso14827TimeFrac *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TimeFracPresent_deci:
		break;
	case Iso14827TimeFracPresent_centi:
		break;
	case Iso14827TimeFracPresent_milli:
		break;
	default:
		break;
	}
}

void Iso14827TimeFrac_del(Iso14827TimeFrac *p)
{
	if (!p) return;
	Iso14827TimeFrac_purge(p);
	Dz1Free(p);
}

void Iso14827TimeFrac_dump(Iso14827TimeFrac *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TimeFracPresent_deci:
		Dz1Thread_printf(Dz1T("deci = ")); Dz1s32_dump(&p->x.deci, tab); 
		break;
	case Iso14827TimeFracPresent_centi:
		Dz1Thread_printf(Dz1T("centi = ")); Dz1s32_dump(&p->x.centi, tab); 
		break;
	case Iso14827TimeFracPresent_milli:
		Dz1Thread_printf(Dz1T("milli = ")); Dz1s32_dump(&p->x.milli, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827TimeFrac
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TimeZone
Iso14827TimeZone *Iso14827TimeZone_new(s32_t modH, s32_t modM, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TimeZone *__internal_ret = (Iso14827TimeZone *)Dz1Calloc(sizeof(Iso14827TimeZone), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TimeZone_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->modH = modH;
		__internal_ret->modM = modM;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TimeZone_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TimeZone_copy(Iso14827TimeZone *dst, Iso14827TimeZone *src, Dz1Error *err)
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

Iso14827TimeZone *Iso14827TimeZone_clone(Iso14827TimeZone *src, Dz1Error *err)
{
	Iso14827TimeZone *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TimeZone *)Dz1Calloc(sizeof(Iso14827TimeZone), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TimeZone_delAndSetNull, (void *)&dst);
		if (Iso14827TimeZone_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TimeZone_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TimeZone_purge(Iso14827TimeZone *p)
{
	if (p == NULL) return;
}

void Iso14827TimeZone_del(Iso14827TimeZone *p)
{
	if (p == NULL) return;
	Iso14827TimeZone_purge(p);
	Dz1Free(p);
}

void Iso14827TimeZone_dump(Iso14827TimeZone *p, int tab)
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
// Iso14827TimeZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Time
Iso14827Time *Iso14827Time_new(s32_t *year, 
							   s32_t *month, 
							   s32_t *day, 
							   s32_t h, 
							   s32_t m, 
							   s32_t s, 
							   Iso14827TimeFrac *frac, 
							   Iso14827TimeZone *zone, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Time *__internal_ret = (Iso14827Time *)Dz1Calloc(sizeof(Iso14827Time), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Time_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->year = year;
		__internal_ret->month = month;
		__internal_ret->day = day;
		__internal_ret->h = h;
		__internal_ret->m = m;
		__internal_ret->s = s;
		__internal_ret->frac = frac;
		__internal_ret->zone = zone;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Time_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827Time_copy(Iso14827Time *dst, Iso14827Time *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->year && (dst->year = Dz1s32_clone(src->year, errp)) == NULL) ERR_OUT(errp);
	else if (src->month && (dst->month = Dz1s32_clone(src->month, errp)) == NULL) ERR_OUT(errp);
	else if (src->day && (dst->day = Dz1s32_clone(src->day, errp)) == NULL) ERR_OUT(errp);
	else if (src->frac && (dst->frac = Iso14827TimeFrac_clone(src->frac, errp)) == NULL) ERR_OUT(errp);
	else if (src->zone && (dst->zone = Iso14827TimeZone_clone(src->zone, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->h = src->h;
		dst->m = src->m;
		dst->s = src->s;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827Time *Iso14827Time_clone(Iso14827Time *src, Dz1Error *err)
{
	Iso14827Time *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827Time *)Dz1Calloc(sizeof(Iso14827Time), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Time_delAndSetNull, (void *)&dst);
		if (Iso14827Time_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Time_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827Time_purge(Iso14827Time *p)
{
	if (p == NULL) return;
	Dz1s32_del(p->year);
	Dz1s32_del(p->month);
	Dz1s32_del(p->day);
	Iso14827TimeFrac_del(p->frac);
	Iso14827TimeZone_del(p->zone);
}

void Iso14827Time_del(Iso14827Time *p)
{
	if (p == NULL) return;
	Iso14827Time_purge(p);
	Dz1Free(p);
}

// Iso14827Time
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827HdrOpt
Iso14827HdrOpt *Iso14827HdrOpt_new(Dz1Asn1UTF8Str *origin, 
								   Dz1Asn1OctetStr *originAddr, 
								   Dz1Asn1UTF8Str *sender, 
								   Dz1Asn1OctetStr *senderAddr, 
								   Dz1Asn1UTF8Str *dest, 
								   Dz1Asn1OctetStr *destAddr, 
								   Iso14827Cost *cost, 
								   Iso14827Time *t, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827HdrOpt *__internal_ret = (Iso14827HdrOpt *)Dz1Calloc(sizeof(Iso14827HdrOpt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827HdrOpt_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->origin = origin;
		__internal_ret->originAddr = originAddr;
		__internal_ret->sender = sender;
		__internal_ret->senderAddr = senderAddr;
		__internal_ret->dest = dest;
		__internal_ret->destAddr = destAddr;
		__internal_ret->cost = cost;
		__internal_ret->t = t;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827HdrOpt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827HdrOpt_copy(Iso14827HdrOpt *dst, Iso14827HdrOpt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->origin && (dst->origin = Dz1Asn1UTF8Str_clone(src->origin, errp)) == NULL) ERR_OUT(errp);
	else if (src->originAddr && (dst->originAddr = Dz1Asn1OctetStr_clone(src->originAddr, errp)) == NULL) ERR_OUT(errp);
	else if (src->sender && (dst->sender = Dz1Asn1UTF8Str_clone(src->sender, errp)) == NULL) ERR_OUT(errp);
	else if (src->senderAddr && (dst->senderAddr = Dz1Asn1OctetStr_clone(src->senderAddr, errp)) == NULL) ERR_OUT(errp);
	else if (src->dest && (dst->dest = Dz1Asn1UTF8Str_clone(src->dest, errp)) == NULL) ERR_OUT(errp);
	else if (src->destAddr && (dst->destAddr = Dz1Asn1OctetStr_clone(src->destAddr, errp)) == NULL) ERR_OUT(errp);
	else if (src->cost && (dst->cost = Iso14827Cost_clone(src->cost, errp)) == NULL) ERR_OUT(errp);
	else if (src->t && (dst->t = Iso14827Time_clone(src->t, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827HdrOpt *Iso14827HdrOpt_clone(Iso14827HdrOpt *src, Dz1Error *err)
{
	Iso14827HdrOpt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827HdrOpt *)Dz1Calloc(sizeof(Iso14827HdrOpt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827HdrOpt_delAndSetNull, (void *)&dst);
		if (Iso14827HdrOpt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827HdrOpt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827HdrOpt_purge(Iso14827HdrOpt *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->origin);
	Dz1Asn1OctetStr_del(p->originAddr);
	Dz1Asn1UTF8Str_del(p->sender);
	Dz1Asn1OctetStr_del(p->senderAddr);
	Dz1Asn1UTF8Str_del(p->dest);
	Dz1Asn1OctetStr_del(p->destAddr);
	Iso14827Cost_del(p->cost);
	Iso14827Time_del(p->t);
}

void Iso14827HdrOpt_del(Iso14827HdrOpt *p)
{
	if (p == NULL) return;
	Iso14827HdrOpt_purge(p);
	Dz1Free(p);
}

void Iso14827HdrOpt_dump(Iso14827HdrOpt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("origin = ")); Dz1Asn1UTF8Str_dump(p->origin, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("originAddr = ")); Dz1Asn1OctetStr_dump(p->originAddr, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("sender = ")); Dz1Asn1UTF8Str_dump(p->sender, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("senderAddr = ")); Dz1Asn1OctetStr_dump(p->senderAddr, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("dest = ")); Dz1Asn1UTF8Str_dump(p->dest, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("destAddr = ")); Dz1Asn1OctetStr_dump(p->destAddr, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("cost = ")); Iso14827Cost_dump(p->cost, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("t = ")); Iso14827Time_dump(p->t, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827HdrOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Initiate
Iso14827Initiate *Iso14827Initiate_new(Dz1Asn1UTF8Str *sender, 
									   Dz1Asn1UTF8Str *dest, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Initiate *__internal_ret = (Iso14827Initiate *)Dz1Calloc(sizeof(Iso14827Initiate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Initiate_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->sender = sender;
		__internal_ret->dest = dest;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Initiate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827Initiate_copy(Iso14827Initiate *dst, Iso14827Initiate *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->sender && (dst->sender = Dz1Asn1UTF8Str_clone(src->sender, errp)) == NULL) ERR_OUT(errp);
	else if (src->dest && (dst->dest = Dz1Asn1UTF8Str_clone(src->dest, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827Initiate *Iso14827Initiate_clone(Iso14827Initiate *src, Dz1Error *err)
{
	Iso14827Initiate *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827Initiate *)Dz1Calloc(sizeof(Iso14827Initiate), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Initiate_delAndSetNull, (void *)&dst);
		if (Iso14827Initiate_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Initiate_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827Initiate_purge(Iso14827Initiate *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->sender);
	Dz1Asn1UTF8Str_del(p->dest);
}

void Iso14827Initiate_del(Iso14827Initiate *p)
{
	if (p == NULL) return;
	Iso14827Initiate_purge(p);
	Dz1Free(p);
}

void Iso14827Initiate_dump(Iso14827Initiate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("sender = ")); Dz1Asn1UTF8Str_dump(p->sender, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("dest = ")); Dz1Asn1UTF8Str_dump(p->dest, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827Initiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1OIDList
static Dz1Error Dz1OIDList_add(Dz1OIDList *p, Dz1Asn1OID *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1OIDListMkArrArg
{
	Dz1Asn1OID **arr;
	unsigned int idx;
} Dz1OIDListMkArrArg;

static Dz1Error _Dz1OIDList_get_array(void *ptr, Dz1Asn1OID *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1OIDListMkArrArg *arg = (Dz1OIDListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1Asn1OID **Dz1OIDList_get_array(Dz1OIDList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1Asn1OID **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Asn1OID **)Dz1Calloc(sizeof(Dz1Asn1OID *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1OIDListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1OIDList_get_array, (void *)&arg);
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

static Dz1Error Dz1OIDList_travelForward(Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Asn1OID *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1OIDList_travelBackward(Dz1OIDList *p, Dz1Error (*func)(void *ptr, Dz1Asn1OID *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

typedef struct Dz1OIDListFindArg
{
	Dz1Asn1OID *key;
	Dz1Asn1OID *ret;
	int (*cmp)(Dz1Asn1OID *a, Dz1Asn1OID *b);
} Dz1OIDListFindArg;

static Dz1Error _Dz1OIDList_find(void *ptr, Dz1Asn1OID *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1OIDListFindArg *arg = (Dz1OIDListFindArg *)ptr;
	if (arg->cmp(arg->key, p) == 0) { arg->ret = p; ERR_SET(&err, EEXIST); }
	return  err;
}

static Dz1Asn1OID *Dz1OIDList_find(Dz1OIDList *p, Dz1Asn1OID *key)
{
	Dz1OIDListFindArg arg = { NULL, NULL };
	arg.key = key;
	arg.cmp = p->cmp;
	p->travel(p, _Dz1OIDList_find, (void *)&arg);
	return arg.ret;
}

static unsigned int Dz1OIDList_count(Dz1OIDList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1OIDList *Dz1OIDList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1OIDList *ret = (Dz1OIDList *)Dz1Calloc(sizeof(Dz1OIDList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1OIDList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1Asn1OID_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1OIDList_count;
			ret->travel = Dz1OIDList_travelForward;
			ret->travelForward = Dz1OIDList_travelForward;
			ret->travelBackward = Dz1OIDList_travelBackward;
			ret->get_array = Dz1OIDList_get_array;
			ret->add = Dz1OIDList_add;
			ret->find = Dz1OIDList_find;
			ret->cmp = Dz1Asn1OID_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1OIDList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1OIDList_clone(void *ptr, Dz1Asn1OID *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1OIDList *p = (Dz1OIDList *)ptr;
	Dz1Asn1OID *cloned = Dz1Asn1OID_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1OIDList *Dz1OIDList_clone(Dz1OIDList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1OIDList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1OIDList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1OIDList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1OIDList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1OIDList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1OIDList_purge(Dz1OIDList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1OIDList_del(Dz1OIDList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1OIDListA_dump(void *ptr, Dz1Asn1OID *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1Asn1OIDA_dump(p, tab);
	return err;
}

void Dz1OIDListA_dump(Dz1OIDList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _Dz1OIDListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _Dz1OIDListA_fdump(void *ptr, Dz1Asn1OID *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); Dz1Asn1OIDA_fdump(arg->fp, p, tab);
	return err;
}

void Dz1OIDListA_fdump(FILE *fp, Dz1OIDList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _Dz1OIDListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _Dz1OIDListW_dump(void *ptr, Dz1Asn1OID *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1Asn1OIDW_dump(p, tab);
	return err;
}

void Dz1OIDListW_dump(Dz1OIDList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _Dz1OIDListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _Dz1OIDListW_fdump(void *ptr, Dz1Asn1OID *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); Dz1Asn1OIDW_fdump(arg->fp, p, tab);
	return err;
}

void Dz1OIDListW_fdump(FILE *fp, Dz1OIDList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _Dz1OIDListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1OIDList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827LoginInitiator
static struct Iso14827LoginInitiatorMapA
{
	str_t str;
	Iso14827LoginInitiator v;
} Iso14827LoginInitiatorMapA[] =
{
	{ (char *)"serverInitiated", Iso14827LoginInitiator_serverInitiated },
	{ (char *)"clientInitiated", Iso14827LoginInitiator_clientInitiated },
	{ NULL, Iso14827LoginInitiator_max }
};

str_t Iso14827LoginInitiatorStrA(Iso14827LoginInitiator v)
{
	struct Iso14827LoginInitiatorMapA *i = NULL;
	for (i = Iso14827LoginInitiatorMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827LoginInitiator Iso14827LoginInitiatorFromStrA(str_t str)
{
	struct Iso14827LoginInitiatorMapA *i = NULL;
	for (i = Iso14827LoginInitiatorMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827LoginInitiator_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827LoginInitiatorMapW
{
	wstr_t str;
	Iso14827LoginInitiator v;
} Iso14827LoginInitiatorMapW[] =
{
	{ (wchar_t *)L"serverInitiated", Iso14827LoginInitiator_serverInitiated },
	{ (wchar_t *)L"clientInitiated", Iso14827LoginInitiator_clientInitiated },
	{ NULL, Iso14827LoginInitiator_max }
};

wstr_t Iso14827LoginInitiatorStrW(Iso14827LoginInitiator v)
{
	struct Iso14827LoginInitiatorMapW *i = NULL;
	for (i = Iso14827LoginInitiatorMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827LoginInitiator Iso14827LoginInitiatorFromStrW(wstr_t str)
{
	struct Iso14827LoginInitiatorMapW *i = NULL;
	for (i = Iso14827LoginInitiatorMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827LoginInitiator_max;
}
#endif // UNIX_SYSTEM

Iso14827LoginInitiator *Iso14827LoginInitiator_new(Iso14827LoginInitiator *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827LoginInitiator *__internal_ret = (Iso14827LoginInitiator *)Dz1Calloc(sizeof(Iso14827LoginInitiator), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827LoginInitiator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Login
Iso14827Login *Iso14827Login_new(Dz1Asn1UTF8Str *sender, 
								 Dz1Asn1UTF8Str *dest, 
								 Dz1Asn1OctetStr *user, 
								 Dz1Asn1OctetStr *pass, 
								 s32_t hbDur, 
								 s32_t timeout, 
								 Iso14827LoginInitiator initiator, 
								 u16_t datagramSize, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Login *__internal_ret = (Iso14827Login *)Dz1Calloc(sizeof(Iso14827Login), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Login_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->encRules = Dz1OIDList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->sender = sender;
			__internal_ret->dest = dest;
			__internal_ret->user = user;
			__internal_ret->pass = pass;
			__internal_ret->hbDur = hbDur;
			__internal_ret->timeout = timeout;
			__internal_ret->initiator = initiator;
			__internal_ret->datagramSize = datagramSize;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Login_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827Login_copy(Iso14827Login *dst, Iso14827Login *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->sender && (dst->sender = Dz1Asn1UTF8Str_clone(src->sender, errp)) == NULL) ERR_OUT(errp);
	else if (src->dest && (dst->dest = Dz1Asn1UTF8Str_clone(src->dest, errp)) == NULL) ERR_OUT(errp);
	else if (src->user && (dst->user = Dz1Asn1OctetStr_clone(src->user, errp)) == NULL) ERR_OUT(errp);
	else if (src->pass && (dst->pass = Dz1Asn1OctetStr_clone(src->pass, errp)) == NULL) ERR_OUT(errp);
	else if (src->encRules && (dst->encRules = Dz1OIDList_clone(src->encRules, errp)) == NULL) ERR_OUT(errp);
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

Iso14827Login *Iso14827Login_clone(Iso14827Login *src, Dz1Error *err)
{
	Iso14827Login *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827Login *)Dz1Calloc(sizeof(Iso14827Login), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Login_delAndSetNull, (void *)&dst);
		if (Iso14827Login_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Login_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827Login_purge(Iso14827Login *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->sender);
	Dz1Asn1UTF8Str_del(p->dest);
	Dz1Asn1OctetStr_del(p->user);
	Dz1Asn1OctetStr_del(p->pass);
	Dz1OIDList_del(p->encRules);
}

void Iso14827Login_del(Iso14827Login *p)
{
	if (p == NULL) return;
	Iso14827Login_purge(p);
	Dz1Free(p);
}

void Iso14827Login_dump(Iso14827Login *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("sender = ")); Dz1Asn1UTF8Str_dump(p->sender, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("dest = ")); Dz1Asn1UTF8Str_dump(p->dest, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Asn1OctetStr_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("encRules = ")); Dz1OIDList_dump(p->encRules, tab); 
		Dz1Thread_tprintf(tab, Dz1T("hbDur = ")); Dz1s32_dump(&p->hbDur, tab); 
		Dz1Thread_tprintf(tab, Dz1T("timeout = ")); Dz1s32_dump(&p->timeout, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initiator = %s(%d)\n"), Iso14827LoginInitiatorStr(p->initiator), p->initiator);
		Dz1Thread_tprintf(tab, Dz1T("datagramSize = ")); Dz1u16_dump(&p->datagramSize, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827Login
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Terminate
static struct Iso14827TerminateMapA
{
	str_t str;
	Iso14827Terminate v;
} Iso14827TerminateMapA[] =
{
	{ (char *)"other", Iso14827Terminate_other },
	{ (char *)"serverRequested", Iso14827Terminate_serverRequested },
	{ (char *)"clientRequested", Iso14827Terminate_clientRequested },
	{ (char *)"serverShutdown", Iso14827Terminate_serverShutdown },
	{ (char *)"clientShutdown", Iso14827Terminate_clientShutdown },
	{ (char *)"serverCommProblems", Iso14827Terminate_serverCommProblems },
	{ (char *)"clientCommProblems", Iso14827Terminate_clientCommProblems },
	{ NULL, Iso14827Terminate_max }
};

str_t Iso14827TerminateStrA(Iso14827Terminate v)
{
	struct Iso14827TerminateMapA *i = NULL;
	for (i = Iso14827TerminateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827Terminate Iso14827TerminateFromStrA(str_t str)
{
	struct Iso14827TerminateMapA *i = NULL;
	for (i = Iso14827TerminateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827Terminate_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TerminateMapW
{
	wstr_t str;
	Iso14827Terminate v;
} Iso14827TerminateMapW[] =
{
	{ (wchar_t *)L"other", Iso14827Terminate_other },
	{ (wchar_t *)L"serverRequested", Iso14827Terminate_serverRequested },
	{ (wchar_t *)L"clientRequested", Iso14827Terminate_clientRequested },
	{ (wchar_t *)L"serverShutdown", Iso14827Terminate_serverShutdown },
	{ (wchar_t *)L"clientShutdown", Iso14827Terminate_clientShutdown },
	{ (wchar_t *)L"serverCommProblems", Iso14827Terminate_serverCommProblems },
	{ (wchar_t *)L"clientCommProblems", Iso14827Terminate_clientCommProblems },
	{ NULL, Iso14827Terminate_max }
};

wstr_t Iso14827TerminateStrW(Iso14827Terminate v)
{
	struct Iso14827TerminateMapW *i = NULL;
	for (i = Iso14827TerminateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827Terminate Iso14827TerminateFromStrW(wstr_t str)
{
	struct Iso14827TerminateMapW *i = NULL;
	for (i = Iso14827TerminateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827Terminate_max;
}
#endif // UNIX_SYSTEM

Iso14827Terminate *Iso14827Terminate_new(Iso14827Terminate *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Terminate *__internal_ret = (Iso14827Terminate *)Dz1Calloc(sizeof(Iso14827Terminate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827Terminate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Logout
static struct Iso14827LogoutMapA
{
	str_t str;
	Iso14827Logout v;
} Iso14827LogoutMapA[] =
{
	{ (char *)"other", Iso14827Logout_other },
	{ (char *)"serverRequested", Iso14827Logout_serverRequested },
	{ (char *)"clientRequested", Iso14827Logout_clientRequested },
	{ (char *)"serverShutdown", Iso14827Logout_serverShutdown },
	{ (char *)"clientShutdown", Iso14827Logout_clientShutdown },
	{ (char *)"serverCommProblems", Iso14827Logout_serverCommProblems },
	{ (char *)"clientCommProblems", Iso14827Logout_clientCommProblems },
	{ NULL, Iso14827Logout_max }
};

str_t Iso14827LogoutStrA(Iso14827Logout v)
{
	struct Iso14827LogoutMapA *i = NULL;
	for (i = Iso14827LogoutMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827Logout Iso14827LogoutFromStrA(str_t str)
{
	struct Iso14827LogoutMapA *i = NULL;
	for (i = Iso14827LogoutMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827Logout_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827LogoutMapW
{
	wstr_t str;
	Iso14827Logout v;
} Iso14827LogoutMapW[] =
{
	{ (wchar_t *)L"other", Iso14827Logout_other },
	{ (wchar_t *)L"serverRequested", Iso14827Logout_serverRequested },
	{ (wchar_t *)L"clientRequested", Iso14827Logout_clientRequested },
	{ (wchar_t *)L"serverShutdown", Iso14827Logout_serverShutdown },
	{ (wchar_t *)L"clientShutdown", Iso14827Logout_clientShutdown },
	{ (wchar_t *)L"serverCommProblems", Iso14827Logout_serverCommProblems },
	{ (wchar_t *)L"clientCommProblems", Iso14827Logout_clientCommProblems },
	{ NULL, Iso14827Logout_max }
};

wstr_t Iso14827LogoutStrW(Iso14827Logout v)
{
	struct Iso14827LogoutMapW *i = NULL;
	for (i = Iso14827LogoutMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827Logout Iso14827LogoutFromStrW(wstr_t str)
{
	struct Iso14827LogoutMapW *i = NULL;
	for (i = Iso14827LogoutMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827Logout_max;
}
#endif // UNIX_SYSTEM

Iso14827Logout *Iso14827Logout_new(Iso14827Logout *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Logout *__internal_ret = (Iso14827Logout *)Dz1Calloc(sizeof(Iso14827Logout), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827Logout
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionDataStatus
static struct Iso14827SubscriptionDataStatusMapA
{
	str_t str;
	Iso14827SubscriptionDataStatus v;
} Iso14827SubscriptionDataStatusMapA[] =
{
	{ (char *)"NEW", Iso14827SubscriptionDataStatus_NEW },
	{ (char *)"UPDATED", Iso14827SubscriptionDataStatus_UPDATED },
	{ NULL, Iso14827SubscriptionDataStatus_max }
};

str_t Iso14827SubscriptionDataStatusStrA(Iso14827SubscriptionDataStatus v)
{
	struct Iso14827SubscriptionDataStatusMapA *i = NULL;
	for (i = Iso14827SubscriptionDataStatusMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionDataStatus Iso14827SubscriptionDataStatusFromStrA(str_t str)
{
	struct Iso14827SubscriptionDataStatusMapA *i = NULL;
	for (i = Iso14827SubscriptionDataStatusMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionDataStatus_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827SubscriptionDataStatusMapW
{
	wstr_t str;
	Iso14827SubscriptionDataStatus v;
} Iso14827SubscriptionDataStatusMapW[] =
{
	{ (wchar_t *)L"NEW", Iso14827SubscriptionDataStatus_NEW },
	{ (wchar_t *)L"UPDATED", Iso14827SubscriptionDataStatus_UPDATED },
	{ NULL, Iso14827SubscriptionDataStatus_max }
};

wstr_t Iso14827SubscriptionDataStatusStrW(Iso14827SubscriptionDataStatus v)
{
	struct Iso14827SubscriptionDataStatusMapW *i = NULL;
	for (i = Iso14827SubscriptionDataStatusMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionDataStatus Iso14827SubscriptionDataStatusFromStrW(wstr_t str)
{
	struct Iso14827SubscriptionDataStatusMapW *i = NULL;
	for (i = Iso14827SubscriptionDataStatusMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionDataStatus_max;
}
#endif // UNIX_SYSTEM

Iso14827SubscriptionDataStatus *Iso14827SubscriptionDataStatus_new(Iso14827SubscriptionDataStatus *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827SubscriptionDataStatus *__internal_ret = (Iso14827SubscriptionDataStatus *)Dz1Calloc(sizeof(Iso14827SubscriptionDataStatus), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827SubscriptionDataStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RegisteredContinuous
Iso14827RegisteredContinuous *Iso14827RegisteredContinuous_new(u32_t updateDelay, 
															   Iso14827Time *start, 
															   Iso14827Time *end, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RegisteredContinuous *__internal_ret = (Iso14827RegisteredContinuous *)Dz1Calloc(sizeof(Iso14827RegisteredContinuous), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827RegisteredContinuous_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->updateDelay = updateDelay;
		__internal_ret->start = start;
		__internal_ret->end = end;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827RegisteredContinuous_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827RegisteredContinuous_copy(Iso14827RegisteredContinuous *dst, Iso14827RegisteredContinuous *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->start && (dst->start = Iso14827Time_clone(src->start, errp)) == NULL) ERR_OUT(errp);
	else if (src->end && (dst->end = Iso14827Time_clone(src->end, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->updateDelay = src->updateDelay;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827RegisteredContinuous *Iso14827RegisteredContinuous_clone(Iso14827RegisteredContinuous *src, Dz1Error *err)
{
	Iso14827RegisteredContinuous *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827RegisteredContinuous *)Dz1Calloc(sizeof(Iso14827RegisteredContinuous), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827RegisteredContinuous_delAndSetNull, (void *)&dst);
		if (Iso14827RegisteredContinuous_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827RegisteredContinuous_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827RegisteredContinuous_purge(Iso14827RegisteredContinuous *p)
{
	if (p == NULL) return;
	Iso14827Time_del(p->start);
	Iso14827Time_del(p->end);
}

void Iso14827RegisteredContinuous_del(Iso14827RegisteredContinuous *p)
{
	if (p == NULL) return;
	Iso14827RegisteredContinuous_purge(p);
	Dz1Free(p);
}

void Iso14827RegisteredContinuous_dump(Iso14827RegisteredContinuous *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("updateDelay = ")); Dz1u32_dump(&p->updateDelay, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("start = ")); Iso14827Time_dump(p->start, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("end = ")); Iso14827Time_dump(p->end, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827RegisteredContinuous
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RegisteredDaily
Iso14827RegisteredDaily *Iso14827RegisteredDaily_new(u32_t updateDelay, 
													 u8_t daysOfWeek, 
													 Iso14827Time *startDate, 
													 Iso14827Time *endDate, 
													 Iso14827Time *startTime, 
													 u16_t *duration, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RegisteredDaily *__internal_ret = (Iso14827RegisteredDaily *)Dz1Calloc(sizeof(Iso14827RegisteredDaily), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827RegisteredDaily_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->updateDelay = updateDelay;
		__internal_ret->daysOfWeek = daysOfWeek;
		__internal_ret->startDate = startDate;
		__internal_ret->endDate = endDate;
		__internal_ret->startTime = startTime;
		__internal_ret->duration = duration;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827RegisteredDaily_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827RegisteredDaily_copy(Iso14827RegisteredDaily *dst, Iso14827RegisteredDaily *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->startDate && (dst->startDate = Iso14827Time_clone(src->startDate, errp)) == NULL) ERR_OUT(errp);
	else if (src->endDate && (dst->endDate = Iso14827Time_clone(src->endDate, errp)) == NULL) ERR_OUT(errp);
	else if (src->startTime && (dst->startTime = Iso14827Time_clone(src->startTime, errp)) == NULL) ERR_OUT(errp);
	else if (src->duration && (dst->duration = Dz1u16_clone(src->duration, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->updateDelay = src->updateDelay;
		dst->daysOfWeek = src->daysOfWeek;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827RegisteredDaily *Iso14827RegisteredDaily_clone(Iso14827RegisteredDaily *src, Dz1Error *err)
{
	Iso14827RegisteredDaily *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827RegisteredDaily *)Dz1Calloc(sizeof(Iso14827RegisteredDaily), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827RegisteredDaily_delAndSetNull, (void *)&dst);
		if (Iso14827RegisteredDaily_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827RegisteredDaily_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827RegisteredDaily_purge(Iso14827RegisteredDaily *p)
{
	if (p == NULL) return;
	Iso14827Time_del(p->startDate);
	Iso14827Time_del(p->endDate);
	Iso14827Time_del(p->startTime);
	Dz1u16_del(p->duration);
}

void Iso14827RegisteredDaily_del(Iso14827RegisteredDaily *p)
{
	if (p == NULL) return;
	Iso14827RegisteredDaily_purge(p);
	Dz1Free(p);
}

void Iso14827RegisteredDaily_dump(Iso14827RegisteredDaily *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("updateDelay = ")); Dz1u32_dump(&p->updateDelay, tab); 
		Dz1Thread_tprintf(tab, Dz1T("daysOfWeek = ")); Dz1u8_dump(&p->daysOfWeek, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("startDate = ")); Iso14827Time_dump(p->startDate, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("endDate = ")); Iso14827Time_dump(p->endDate, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("startTime = ")); Iso14827Time_dump(p->startTime, tab); 
		Dz1Thread_tprintf(tab, Dz1T("duration = ")); Dz1u16_dump(p->duration, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827RegisteredDaily
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RegisteredPresent
static struct Iso14827RegisteredPresentMapA
{
	str_t str;
	Iso14827RegisteredPresent v;
} Iso14827RegisteredPresentMapA[] =
{
	{ (char *)"continuous", Iso14827RegisteredPresent_continuous },
	{ (char *)"daily", Iso14827RegisteredPresent_daily },
	{ NULL, Iso14827RegisteredPresent_max }
};

str_t Iso14827RegisteredPresentStrA(Iso14827RegisteredPresent v)
{
	struct Iso14827RegisteredPresentMapA *i = NULL;
	for (i = Iso14827RegisteredPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RegisteredPresent Iso14827RegisteredPresentFromStrA(str_t str)
{
	struct Iso14827RegisteredPresentMapA *i = NULL;
	for (i = Iso14827RegisteredPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827RegisteredPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827RegisteredPresentMapW
{
	wstr_t str;
	Iso14827RegisteredPresent v;
} Iso14827RegisteredPresentMapW[] =
{
	{ (wchar_t *)L"continuous", Iso14827RegisteredPresent_continuous },
	{ (wchar_t *)L"daily", Iso14827RegisteredPresent_daily },
	{ NULL, Iso14827RegisteredPresent_max }
};

wstr_t Iso14827RegisteredPresentStrW(Iso14827RegisteredPresent v)
{
	struct Iso14827RegisteredPresentMapW *i = NULL;
	for (i = Iso14827RegisteredPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RegisteredPresent Iso14827RegisteredPresentFromStrW(wstr_t str)
{
	struct Iso14827RegisteredPresentMapW *i = NULL;
	for (i = Iso14827RegisteredPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827RegisteredPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827RegisteredPresent *Iso14827RegisteredPresent_new(Iso14827RegisteredPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RegisteredPresent *__internal_ret = (Iso14827RegisteredPresent *)Dz1Calloc(sizeof(Iso14827RegisteredPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827RegisteredPresent_dump(Iso14827RegisteredPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827RegisteredPresentStr(*v));
}
// Iso14827RegisteredPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Registered
Iso14827Registered *Iso14827Registered_new(Iso14827RegisteredPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Registered *ret = (Iso14827Registered *)Dz1Calloc(sizeof(Iso14827Registered), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Registered_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827RegisteredPresent_continuous:
			// _U_cst_clone
			if (ptr != NULL) ret->x.continuous = (Iso14827RegisteredContinuous *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827RegisteredPresent_daily:
			// _U_cst_clone
			if (ptr != NULL) ret->x.daily = (Iso14827RegisteredDaily *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827RegisteredPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Registered_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827Registered_copy(Iso14827Registered *ret, Iso14827Registered *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827RegisteredPresent_continuous:
			// _U_cst_clone
			if (src->x.continuous && (ret->x.continuous = Iso14827RegisteredContinuous_clone(src->x.continuous, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827RegisteredPresent_daily:
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

Iso14827Registered *Iso14827Registered_clone(Iso14827Registered *src, Dz1Error *err)
{
	Iso14827Registered *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827Registered *)Dz1Calloc(sizeof(Iso14827Registered), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Registered_delAndSetNull, (void *)&ret);
		if (Iso14827Registered_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Registered_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827Registered_purge(Iso14827Registered *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827RegisteredPresent_continuous:
		Iso14827RegisteredContinuous_del(p->x.continuous);
		break;
	case Iso14827RegisteredPresent_daily:
		Iso14827RegisteredDaily_del(p->x.daily);
		break;
	default:
		break;
	}
}

void Iso14827Registered_del(Iso14827Registered *p)
{
	if (!p) return;
	Iso14827Registered_purge(p);
	Dz1Free(p);
}

void Iso14827Registered_dump(Iso14827Registered *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827RegisteredPresent_continuous:
		Dz1Thread_printf(Dz1T("continuous = ")); Iso14827RegisteredContinuous_dump(p->x.continuous, tab); 
		break;
	case Iso14827RegisteredPresent_daily:
		Dz1Thread_printf(Dz1T("daily = ")); Iso14827RegisteredDaily_dump(p->x.daily, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827Registered
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionDataModePresent
static struct Iso14827SubscriptionDataModePresentMapA
{
	str_t str;
	Iso14827SubscriptionDataModePresent v;
} Iso14827SubscriptionDataModePresentMapA[] =
{
	{ (char *)"single", Iso14827SubscriptionDataModePresent_single },
	{ (char *)"eventDriven", Iso14827SubscriptionDataModePresent_eventDriven },
	{ (char *)"periodic", Iso14827SubscriptionDataModePresent_periodic },
	{ NULL, Iso14827SubscriptionDataModePresent_max }
};

str_t Iso14827SubscriptionDataModePresentStrA(Iso14827SubscriptionDataModePresent v)
{
	struct Iso14827SubscriptionDataModePresentMapA *i = NULL;
	for (i = Iso14827SubscriptionDataModePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionDataModePresent Iso14827SubscriptionDataModePresentFromStrA(str_t str)
{
	struct Iso14827SubscriptionDataModePresentMapA *i = NULL;
	for (i = Iso14827SubscriptionDataModePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionDataModePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827SubscriptionDataModePresentMapW
{
	wstr_t str;
	Iso14827SubscriptionDataModePresent v;
} Iso14827SubscriptionDataModePresentMapW[] =
{
	{ (wchar_t *)L"single", Iso14827SubscriptionDataModePresent_single },
	{ (wchar_t *)L"eventDriven", Iso14827SubscriptionDataModePresent_eventDriven },
	{ (wchar_t *)L"periodic", Iso14827SubscriptionDataModePresent_periodic },
	{ NULL, Iso14827SubscriptionDataModePresent_max }
};

wstr_t Iso14827SubscriptionDataModePresentStrW(Iso14827SubscriptionDataModePresent v)
{
	struct Iso14827SubscriptionDataModePresentMapW *i = NULL;
	for (i = Iso14827SubscriptionDataModePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionDataModePresent Iso14827SubscriptionDataModePresentFromStrW(wstr_t str)
{
	struct Iso14827SubscriptionDataModePresentMapW *i = NULL;
	for (i = Iso14827SubscriptionDataModePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionDataModePresent_max;
}
#endif // UNIX_SYSTEM

Iso14827SubscriptionDataModePresent *Iso14827SubscriptionDataModePresent_new(Iso14827SubscriptionDataModePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827SubscriptionDataModePresent *__internal_ret = (Iso14827SubscriptionDataModePresent *)Dz1Calloc(sizeof(Iso14827SubscriptionDataModePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827SubscriptionDataModePresent_dump(Iso14827SubscriptionDataModePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827SubscriptionDataModePresentStr(*v));
}
// Iso14827SubscriptionDataModePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionDataMode
Iso14827SubscriptionDataMode *Iso14827SubscriptionDataMode_new(Iso14827SubscriptionDataModePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827SubscriptionDataMode *ret = (Iso14827SubscriptionDataMode *)Dz1Calloc(sizeof(Iso14827SubscriptionDataMode), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827SubscriptionDataMode_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827SubscriptionDataModePresent_single:
			// _U_prim_clone
			if (ptr != NULL) ret->x.single = (s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827SubscriptionDataModePresent_eventDriven:
			// _U_cst_clone
			if (ptr != NULL) ret->x.eventDriven = (Iso14827Registered *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827SubscriptionDataModePresent_periodic:
			// _U_cst_clone
			if (ptr != NULL) ret->x.periodic = (Iso14827Registered *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827SubscriptionDataModePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827SubscriptionDataMode_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827SubscriptionDataMode_copy(Iso14827SubscriptionDataMode *ret, Iso14827SubscriptionDataMode *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827SubscriptionDataModePresent_single:
			// _U_prim_clone
			if (src->x.single && (ret->x.single = Dz1s32_clone(src->x.single, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827SubscriptionDataModePresent_eventDriven:
			// _U_cst_clone
			if (src->x.eventDriven && (ret->x.eventDriven = Iso14827Registered_clone(src->x.eventDriven, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827SubscriptionDataModePresent_periodic:
			// _U_cst_clone
			if (src->x.periodic && (ret->x.periodic = Iso14827Registered_clone(src->x.periodic, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827SubscriptionDataMode *Iso14827SubscriptionDataMode_clone(Iso14827SubscriptionDataMode *src, Dz1Error *err)
{
	Iso14827SubscriptionDataMode *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827SubscriptionDataMode *)Dz1Calloc(sizeof(Iso14827SubscriptionDataMode), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827SubscriptionDataMode_delAndSetNull, (void *)&ret);
		if (Iso14827SubscriptionDataMode_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827SubscriptionDataMode_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827SubscriptionDataMode_purge(Iso14827SubscriptionDataMode *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827SubscriptionDataModePresent_single:
		Dz1s32_del(p->x.single);
		break;
	case Iso14827SubscriptionDataModePresent_eventDriven:
		Iso14827Registered_del(p->x.eventDriven);
		break;
	case Iso14827SubscriptionDataModePresent_periodic:
		Iso14827Registered_del(p->x.periodic);
		break;
	default:
		break;
	}
}

void Iso14827SubscriptionDataMode_del(Iso14827SubscriptionDataMode *p)
{
	if (!p) return;
	Iso14827SubscriptionDataMode_purge(p);
	Dz1Free(p);
}

void Iso14827SubscriptionDataMode_dump(Iso14827SubscriptionDataMode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827SubscriptionDataModePresent_single:
		Dz1Thread_printf(Dz1T("single = ")); Dz1s32_dump(p->x.single, tab); 
		break;
	case Iso14827SubscriptionDataModePresent_eventDriven:
		Dz1Thread_printf(Dz1T("eventDriven.")); Iso14827Registered_dump(p->x.eventDriven, tab); 
		break;
	case Iso14827SubscriptionDataModePresent_periodic:
		Dz1Thread_printf(Dz1T("periodic.")); Iso14827Registered_dump(p->x.periodic, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827SubscriptionDataMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionDataFormat
static struct Iso14827SubscriptionDataFormatMapA
{
	str_t str;
	Iso14827SubscriptionDataFormat v;
} Iso14827SubscriptionDataFormatMapA[] =
{
	{ (char *)"other", Iso14827SubscriptionDataFormat_other },
	{ (char *)"ftp", Iso14827SubscriptionDataFormat_ftp },
	{ (char *)"tftp", Iso14827SubscriptionDataFormat_tftp },
	{ (char *)"dataPacket", Iso14827SubscriptionDataFormat_dataPacket },
	{ NULL, Iso14827SubscriptionDataFormat_max }
};

str_t Iso14827SubscriptionDataFormatStrA(Iso14827SubscriptionDataFormat v)
{
	struct Iso14827SubscriptionDataFormatMapA *i = NULL;
	for (i = Iso14827SubscriptionDataFormatMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionDataFormat Iso14827SubscriptionDataFormatFromStrA(str_t str)
{
	struct Iso14827SubscriptionDataFormatMapA *i = NULL;
	for (i = Iso14827SubscriptionDataFormatMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionDataFormat_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827SubscriptionDataFormatMapW
{
	wstr_t str;
	Iso14827SubscriptionDataFormat v;
} Iso14827SubscriptionDataFormatMapW[] =
{
	{ (wchar_t *)L"other", Iso14827SubscriptionDataFormat_other },
	{ (wchar_t *)L"ftp", Iso14827SubscriptionDataFormat_ftp },
	{ (wchar_t *)L"tftp", Iso14827SubscriptionDataFormat_tftp },
	{ (wchar_t *)L"dataPacket", Iso14827SubscriptionDataFormat_dataPacket },
	{ NULL, Iso14827SubscriptionDataFormat_max }
};

wstr_t Iso14827SubscriptionDataFormatStrW(Iso14827SubscriptionDataFormat v)
{
	struct Iso14827SubscriptionDataFormatMapW *i = NULL;
	for (i = Iso14827SubscriptionDataFormatMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionDataFormat Iso14827SubscriptionDataFormatFromStrW(wstr_t str)
{
	struct Iso14827SubscriptionDataFormatMapW *i = NULL;
	for (i = Iso14827SubscriptionDataFormatMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionDataFormat_max;
}
#endif // UNIX_SYSTEM

Iso14827SubscriptionDataFormat *Iso14827SubscriptionDataFormat_new(Iso14827SubscriptionDataFormat *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827SubscriptionDataFormat *__internal_ret = (Iso14827SubscriptionDataFormat *)Dz1Calloc(sizeof(Iso14827SubscriptionDataFormat), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827SubscriptionDataFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827EndAppMsg
Iso14827EndAppMsg *Iso14827EndAppMsg_new(Dz1Asn1OID *oid, Dz1Asn1Any *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827EndAppMsg *__internal_ret = (Iso14827EndAppMsg *)Dz1Calloc(sizeof(Iso14827EndAppMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827EndAppMsg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->oid = oid;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827EndAppMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827EndAppMsg_copy(Iso14827EndAppMsg *dst, Iso14827EndAppMsg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->oid && (dst->oid = Dz1Asn1OID_clone(src->oid, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1Asn1Any_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827EndAppMsg *Iso14827EndAppMsg_clone(Iso14827EndAppMsg *src, Dz1Error *err)
{
	Iso14827EndAppMsg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827EndAppMsg *)Dz1Calloc(sizeof(Iso14827EndAppMsg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827EndAppMsg_delAndSetNull, (void *)&dst);
		if (Iso14827EndAppMsg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827EndAppMsg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827EndAppMsg_purge(Iso14827EndAppMsg *p)
{
	if (p == NULL) return;
	Dz1Asn1OID_del(p->oid);
	Dz1Asn1Any_del(p->data);
}

void Iso14827EndAppMsg_del(Iso14827EndAppMsg *p)
{
	if (p == NULL) return;
	Iso14827EndAppMsg_purge(p);
	Dz1Free(p);
}

void Iso14827EndAppMsg_dump(Iso14827EndAppMsg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("oid = ")); Dz1Asn1OID_dump(p->oid, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Asn1Any_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827EndAppMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionData
Iso14827SubscriptionData *Iso14827SubscriptionData_new(bool_t persistent, 
													   Iso14827SubscriptionDataStatus status, 
													   Iso14827SubscriptionDataMode *mode, 
													   Iso14827SubscriptionDataFormat fmt, 
													   s32_t priority, 
													   bool_t guarantee, 
													   Iso14827EndAppMsg *msg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827SubscriptionData *__internal_ret = (Iso14827SubscriptionData *)Dz1Calloc(sizeof(Iso14827SubscriptionData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827SubscriptionData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->persistent = persistent;
		__internal_ret->status = status;
		__internal_ret->mode = mode;
		__internal_ret->fmt = fmt;
		__internal_ret->priority = priority;
		__internal_ret->guarantee = guarantee;
		__internal_ret->msg = msg;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827SubscriptionData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827SubscriptionData_copy(Iso14827SubscriptionData *dst, Iso14827SubscriptionData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->mode && (dst->mode = Iso14827SubscriptionDataMode_clone(src->mode, errp)) == NULL) ERR_OUT(errp);
	else if (src->msg && (dst->msg = Iso14827EndAppMsg_clone(src->msg, errp)) == NULL) ERR_OUT(errp);
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

Iso14827SubscriptionData *Iso14827SubscriptionData_clone(Iso14827SubscriptionData *src, Dz1Error *err)
{
	Iso14827SubscriptionData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827SubscriptionData *)Dz1Calloc(sizeof(Iso14827SubscriptionData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827SubscriptionData_delAndSetNull, (void *)&dst);
		if (Iso14827SubscriptionData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827SubscriptionData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827SubscriptionData_purge(Iso14827SubscriptionData *p)
{
	if (p == NULL) return;
	Iso14827SubscriptionDataMode_del(p->mode);
	Iso14827EndAppMsg_del(p->msg);
}

void Iso14827SubscriptionData_del(Iso14827SubscriptionData *p)
{
	if (p == NULL) return;
	Iso14827SubscriptionData_purge(p);
	Dz1Free(p);
}

void Iso14827SubscriptionData_dump(Iso14827SubscriptionData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("persistent = ")); Dz1Bool_dump(&p->persistent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("status = %s(%d)\n"), Iso14827SubscriptionDataStatusStr(p->status), p->status);
		Dz1Thread_tprintf(tab, Dz1T("mode.")); Iso14827SubscriptionDataMode_dump(p->mode, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fmt = %s(%d)\n"), Iso14827SubscriptionDataFormatStr(p->fmt), p->fmt);
		Dz1Thread_tprintf(tab, Dz1T("priority = ")); Dz1s32_dump(&p->priority, tab); 
		Dz1Thread_tprintf(tab, Dz1T("guarantee = ")); Dz1Bool_dump(&p->guarantee, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("msg = ")); Iso14827EndAppMsg_dump(p->msg, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827SubscriptionData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionCancel
static struct Iso14827SubscriptionCancelMapA
{
	str_t str;
	Iso14827SubscriptionCancel v;
} Iso14827SubscriptionCancelMapA[] =
{
	{ (char *)"other", Iso14827SubscriptionCancel_other },
	{ (char *)"dataNotNeeded", Iso14827SubscriptionCancel_dataNotNeeded },
	{ (char *)"errorsInPublication", Iso14827SubscriptionCancel_errorsInPublication },
	{ (char *)"pendingLogout", Iso14827SubscriptionCancel_pendingLogout },
	{ (char *)"processingMgmt", Iso14827SubscriptionCancel_processingMgmt },
	{ (char *)"bandwidthMgmt", Iso14827SubscriptionCancel_bandwidthMgmt },
	{ NULL, Iso14827SubscriptionCancel_max }
};

str_t Iso14827SubscriptionCancelStrA(Iso14827SubscriptionCancel v)
{
	struct Iso14827SubscriptionCancelMapA *i = NULL;
	for (i = Iso14827SubscriptionCancelMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionCancel Iso14827SubscriptionCancelFromStrA(str_t str)
{
	struct Iso14827SubscriptionCancelMapA *i = NULL;
	for (i = Iso14827SubscriptionCancelMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionCancel_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827SubscriptionCancelMapW
{
	wstr_t str;
	Iso14827SubscriptionCancel v;
} Iso14827SubscriptionCancelMapW[] =
{
	{ (wchar_t *)L"other", Iso14827SubscriptionCancel_other },
	{ (wchar_t *)L"dataNotNeeded", Iso14827SubscriptionCancel_dataNotNeeded },
	{ (wchar_t *)L"errorsInPublication", Iso14827SubscriptionCancel_errorsInPublication },
	{ (wchar_t *)L"pendingLogout", Iso14827SubscriptionCancel_pendingLogout },
	{ (wchar_t *)L"processingMgmt", Iso14827SubscriptionCancel_processingMgmt },
	{ (wchar_t *)L"bandwidthMgmt", Iso14827SubscriptionCancel_bandwidthMgmt },
	{ NULL, Iso14827SubscriptionCancel_max }
};

wstr_t Iso14827SubscriptionCancelStrW(Iso14827SubscriptionCancel v)
{
	struct Iso14827SubscriptionCancelMapW *i = NULL;
	for (i = Iso14827SubscriptionCancelMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionCancel Iso14827SubscriptionCancelFromStrW(wstr_t str)
{
	struct Iso14827SubscriptionCancelMapW *i = NULL;
	for (i = Iso14827SubscriptionCancelMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionCancel_max;
}
#endif // UNIX_SYSTEM

Iso14827SubscriptionCancel *Iso14827SubscriptionCancel_new(Iso14827SubscriptionCancel *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827SubscriptionCancel *__internal_ret = (Iso14827SubscriptionCancel *)Dz1Calloc(sizeof(Iso14827SubscriptionCancel), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827SubscriptionCancel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionTypePresent
static struct Iso14827SubscriptionTypePresentMapA
{
	str_t str;
	Iso14827SubscriptionTypePresent v;
} Iso14827SubscriptionTypePresentMapA[] =
{
	{ (char *)"data", Iso14827SubscriptionTypePresent_data },
	{ (char *)"reason", Iso14827SubscriptionTypePresent_reason },
	{ NULL, Iso14827SubscriptionTypePresent_max }
};

str_t Iso14827SubscriptionTypePresentStrA(Iso14827SubscriptionTypePresent v)
{
	struct Iso14827SubscriptionTypePresentMapA *i = NULL;
	for (i = Iso14827SubscriptionTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionTypePresent Iso14827SubscriptionTypePresentFromStrA(str_t str)
{
	struct Iso14827SubscriptionTypePresentMapA *i = NULL;
	for (i = Iso14827SubscriptionTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827SubscriptionTypePresentMapW
{
	wstr_t str;
	Iso14827SubscriptionTypePresent v;
} Iso14827SubscriptionTypePresentMapW[] =
{
	{ (wchar_t *)L"data", Iso14827SubscriptionTypePresent_data },
	{ (wchar_t *)L"reason", Iso14827SubscriptionTypePresent_reason },
	{ NULL, Iso14827SubscriptionTypePresent_max }
};

wstr_t Iso14827SubscriptionTypePresentStrW(Iso14827SubscriptionTypePresent v)
{
	struct Iso14827SubscriptionTypePresentMapW *i = NULL;
	for (i = Iso14827SubscriptionTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827SubscriptionTypePresent Iso14827SubscriptionTypePresentFromStrW(wstr_t str)
{
	struct Iso14827SubscriptionTypePresentMapW *i = NULL;
	for (i = Iso14827SubscriptionTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827SubscriptionTypePresent_max;
}
#endif // UNIX_SYSTEM

Iso14827SubscriptionTypePresent *Iso14827SubscriptionTypePresent_new(Iso14827SubscriptionTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827SubscriptionTypePresent *__internal_ret = (Iso14827SubscriptionTypePresent *)Dz1Calloc(sizeof(Iso14827SubscriptionTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827SubscriptionTypePresent_dump(Iso14827SubscriptionTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827SubscriptionTypePresentStr(*v));
}
// Iso14827SubscriptionTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionType
Iso14827SubscriptionType *Iso14827SubscriptionType_new(Iso14827SubscriptionTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827SubscriptionType *ret = (Iso14827SubscriptionType *)Dz1Calloc(sizeof(Iso14827SubscriptionType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827SubscriptionType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827SubscriptionTypePresent_data:
			// _U_cst_clone
			if (ptr != NULL) ret->x.data = (Iso14827SubscriptionData *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827SubscriptionTypePresent_reason:
			// _U_enum_clone
			if (ptr != NULL) ret->x.reason = *(Iso14827SubscriptionCancel *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827SubscriptionTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827SubscriptionType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827SubscriptionType_copy(Iso14827SubscriptionType *ret, Iso14827SubscriptionType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827SubscriptionTypePresent_data:
			// _U_cst_clone
			if (src->x.data && (ret->x.data = Iso14827SubscriptionData_clone(src->x.data, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827SubscriptionTypePresent_reason:
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

Iso14827SubscriptionType *Iso14827SubscriptionType_clone(Iso14827SubscriptionType *src, Dz1Error *err)
{
	Iso14827SubscriptionType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827SubscriptionType *)Dz1Calloc(sizeof(Iso14827SubscriptionType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827SubscriptionType_delAndSetNull, (void *)&ret);
		if (Iso14827SubscriptionType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827SubscriptionType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827SubscriptionType_purge(Iso14827SubscriptionType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827SubscriptionTypePresent_data:
		Iso14827SubscriptionData_del(p->x.data);
		break;
	case Iso14827SubscriptionTypePresent_reason:
		break;
	default:
		break;
	}
}

void Iso14827SubscriptionType_del(Iso14827SubscriptionType *p)
{
	if (!p) return;
	Iso14827SubscriptionType_purge(p);
	Dz1Free(p);
}

void Iso14827SubscriptionType_dump(Iso14827SubscriptionType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827SubscriptionTypePresent_data:
		Dz1Thread_printf(Dz1T("data = ")); Iso14827SubscriptionData_dump(p->x.data, tab); 
		break;
	case Iso14827SubscriptionTypePresent_reason:
		Dz1Thread_printf(Dz1T("reason = %s(%d)\n"), Iso14827SubscriptionCancelStr(p->x.reason), p->x.reason);
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827SubscriptionType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Subscription
Iso14827Subscription *Iso14827Subscription_new(u32_t serial, 
											   Iso14827SubscriptionType *type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Subscription *__internal_ret = (Iso14827Subscription *)Dz1Calloc(sizeof(Iso14827Subscription), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Subscription_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->serial = serial;
		__internal_ret->type = type;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Subscription_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827Subscription_copy(Iso14827Subscription *dst, Iso14827Subscription *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->type && (dst->type = Iso14827SubscriptionType_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->serial = src->serial;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827Subscription *Iso14827Subscription_clone(Iso14827Subscription *src, Dz1Error *err)
{
	Iso14827Subscription *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827Subscription *)Dz1Calloc(sizeof(Iso14827Subscription), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Subscription_delAndSetNull, (void *)&dst);
		if (Iso14827Subscription_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Subscription_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827Subscription_purge(Iso14827Subscription *p)
{
	if (p == NULL) return;
	Iso14827SubscriptionType_del(p->type);
}

void Iso14827Subscription_del(Iso14827Subscription *p)
{
	if (p == NULL) return;
	Iso14827Subscription_purge(p);
	Dz1Free(p);
}

void Iso14827Subscription_dump(Iso14827Subscription *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type.")); Iso14827SubscriptionType_dump(p->type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827Subscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationMgmt
static struct Iso14827PublicationMgmtMapA
{
	str_t str;
	Iso14827PublicationMgmt v;
} Iso14827PublicationMgmtMapA[] =
{
	{ (char *)"temporarilySuspended", Iso14827PublicationMgmt_temporarilySuspended },
	{ (char *)"resume", Iso14827PublicationMgmt_resume },
	{ (char *)"terminateOther", Iso14827PublicationMgmt_terminateOther },
	{ (char *)"terminateDataNoLongerAvailable", Iso14827PublicationMgmt_terminateDataNoLongerAvailable },
	{ (char *)"terminatePublicationsBeingRejected", Iso14827PublicationMgmt_terminatePublicationsBeingRejected },
	{ (char *)"terminatePendingShutdown", Iso14827PublicationMgmt_terminatePendingShutdown },
	{ (char *)"terminateProcessingMgmt", Iso14827PublicationMgmt_terminateProcessingMgmt },
	{ (char *)"terminateBandwidthMgmt", Iso14827PublicationMgmt_terminateBandwidthMgmt },
	{ (char *)"terminateAccessDenied", Iso14827PublicationMgmt_terminateAccessDenied },
	{ (char *)"unknownRequest", Iso14827PublicationMgmt_unknownRequest },
	{ NULL, Iso14827PublicationMgmt_max }
};

str_t Iso14827PublicationMgmtStrA(Iso14827PublicationMgmt v)
{
	struct Iso14827PublicationMgmtMapA *i = NULL;
	for (i = Iso14827PublicationMgmtMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827PublicationMgmt Iso14827PublicationMgmtFromStrA(str_t str)
{
	struct Iso14827PublicationMgmtMapA *i = NULL;
	for (i = Iso14827PublicationMgmtMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827PublicationMgmt_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827PublicationMgmtMapW
{
	wstr_t str;
	Iso14827PublicationMgmt v;
} Iso14827PublicationMgmtMapW[] =
{
	{ (wchar_t *)L"temporarilySuspended", Iso14827PublicationMgmt_temporarilySuspended },
	{ (wchar_t *)L"resume", Iso14827PublicationMgmt_resume },
	{ (wchar_t *)L"terminateOther", Iso14827PublicationMgmt_terminateOther },
	{ (wchar_t *)L"terminateDataNoLongerAvailable", Iso14827PublicationMgmt_terminateDataNoLongerAvailable },
	{ (wchar_t *)L"terminatePublicationsBeingRejected", Iso14827PublicationMgmt_terminatePublicationsBeingRejected },
	{ (wchar_t *)L"terminatePendingShutdown", Iso14827PublicationMgmt_terminatePendingShutdown },
	{ (wchar_t *)L"terminateProcessingMgmt", Iso14827PublicationMgmt_terminateProcessingMgmt },
	{ (wchar_t *)L"terminateBandwidthMgmt", Iso14827PublicationMgmt_terminateBandwidthMgmt },
	{ (wchar_t *)L"terminateAccessDenied", Iso14827PublicationMgmt_terminateAccessDenied },
	{ (wchar_t *)L"unknownRequest", Iso14827PublicationMgmt_unknownRequest },
	{ NULL, Iso14827PublicationMgmt_max }
};

wstr_t Iso14827PublicationMgmtStrW(Iso14827PublicationMgmt v)
{
	struct Iso14827PublicationMgmtMapW *i = NULL;
	for (i = Iso14827PublicationMgmtMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827PublicationMgmt Iso14827PublicationMgmtFromStrW(wstr_t str)
{
	struct Iso14827PublicationMgmtMapW *i = NULL;
	for (i = Iso14827PublicationMgmtMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827PublicationMgmt_max;
}
#endif // UNIX_SYSTEM

Iso14827PublicationMgmt *Iso14827PublicationMgmt_new(Iso14827PublicationMgmt *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PublicationMgmt *__internal_ret = (Iso14827PublicationMgmt *)Dz1Calloc(sizeof(Iso14827PublicationMgmt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827PublicationMgmt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationTypePresent
static struct Iso14827PublicationTypePresentMapA
{
	str_t str;
	Iso14827PublicationTypePresent v;
} Iso14827PublicationTypePresentMapA[] =
{
	{ (char *)"mgmt", Iso14827PublicationTypePresent_mgmt },
	{ (char *)"msg", Iso14827PublicationTypePresent_msg },
	{ NULL, Iso14827PublicationTypePresent_max }
};

str_t Iso14827PublicationTypePresentStrA(Iso14827PublicationTypePresent v)
{
	struct Iso14827PublicationTypePresentMapA *i = NULL;
	for (i = Iso14827PublicationTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827PublicationTypePresent Iso14827PublicationTypePresentFromStrA(str_t str)
{
	struct Iso14827PublicationTypePresentMapA *i = NULL;
	for (i = Iso14827PublicationTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827PublicationTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827PublicationTypePresentMapW
{
	wstr_t str;
	Iso14827PublicationTypePresent v;
} Iso14827PublicationTypePresentMapW[] =
{
	{ (wchar_t *)L"mgmt", Iso14827PublicationTypePresent_mgmt },
	{ (wchar_t *)L"msg", Iso14827PublicationTypePresent_msg },
	{ NULL, Iso14827PublicationTypePresent_max }
};

wstr_t Iso14827PublicationTypePresentStrW(Iso14827PublicationTypePresent v)
{
	struct Iso14827PublicationTypePresentMapW *i = NULL;
	for (i = Iso14827PublicationTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827PublicationTypePresent Iso14827PublicationTypePresentFromStrW(wstr_t str)
{
	struct Iso14827PublicationTypePresentMapW *i = NULL;
	for (i = Iso14827PublicationTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827PublicationTypePresent_max;
}
#endif // UNIX_SYSTEM

Iso14827PublicationTypePresent *Iso14827PublicationTypePresent_new(Iso14827PublicationTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PublicationTypePresent *__internal_ret = (Iso14827PublicationTypePresent *)Dz1Calloc(sizeof(Iso14827PublicationTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827PublicationTypePresent_dump(Iso14827PublicationTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827PublicationTypePresentStr(*v));
}
// Iso14827PublicationTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationType
Iso14827PublicationType *Iso14827PublicationType_new(Iso14827PublicationTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PublicationType *ret = (Iso14827PublicationType *)Dz1Calloc(sizeof(Iso14827PublicationType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827PublicationType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827PublicationTypePresent_mgmt:
			// _U_enum_clone
			if (ptr != NULL) ret->x.mgmt = *(Iso14827PublicationMgmt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PublicationTypePresent_msg:
			// _U_cst_clone
			if (ptr != NULL) ret->x.msg = (Iso14827EndAppMsg *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PublicationTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PublicationType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827PublicationType_copy(Iso14827PublicationType *ret, Iso14827PublicationType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827PublicationTypePresent_mgmt:
			// _U_enum_clone
			ret->x.mgmt = src->x.mgmt;
			ERR_CLEAR(errp);
			break;
		case Iso14827PublicationTypePresent_msg:
			// _U_cst_clone
			if (src->x.msg && (ret->x.msg = Iso14827EndAppMsg_clone(src->x.msg, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827PublicationType *Iso14827PublicationType_clone(Iso14827PublicationType *src, Dz1Error *err)
{
	Iso14827PublicationType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827PublicationType *)Dz1Calloc(sizeof(Iso14827PublicationType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827PublicationType_delAndSetNull, (void *)&ret);
		if (Iso14827PublicationType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PublicationType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827PublicationType_purge(Iso14827PublicationType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827PublicationTypePresent_mgmt:
		break;
	case Iso14827PublicationTypePresent_msg:
		Iso14827EndAppMsg_del(p->x.msg);
		break;
	default:
		break;
	}
}

void Iso14827PublicationType_del(Iso14827PublicationType *p)
{
	if (!p) return;
	Iso14827PublicationType_purge(p);
	Dz1Free(p);
}

void Iso14827PublicationType_dump(Iso14827PublicationType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827PublicationTypePresent_mgmt:
		Dz1Thread_printf(Dz1T("mgmt = %s(%d)\n"), Iso14827PublicationMgmtStr(p->x.mgmt), p->x.mgmt);
		break;
	case Iso14827PublicationTypePresent_msg:
		Dz1Thread_printf(Dz1T("msg = ")); Iso14827EndAppMsg_dump(p->x.msg, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827PublicationType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationData
Iso14827PublicationData *Iso14827PublicationData_new(u32_t subscriptionSerial, 
													 u32_t serial, 
													 bool_t isLated, 
													 Iso14827PublicationType *type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PublicationData *__internal_ret = (Iso14827PublicationData *)Dz1Calloc(sizeof(Iso14827PublicationData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->subscriptionSerial = subscriptionSerial;
		__internal_ret->serial = serial;
		__internal_ret->isLated = isLated;
		__internal_ret->type = type;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PublicationData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827PublicationData_copy(Iso14827PublicationData *dst, Iso14827PublicationData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->type && (dst->type = Iso14827PublicationType_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->subscriptionSerial = src->subscriptionSerial;
		dst->serial = src->serial;
		dst->isLated = src->isLated;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827PublicationData *Iso14827PublicationData_clone(Iso14827PublicationData *src, Dz1Error *err)
{
	Iso14827PublicationData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827PublicationData *)Dz1Calloc(sizeof(Iso14827PublicationData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)&dst);
		if (Iso14827PublicationData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PublicationData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827PublicationData_purge(Iso14827PublicationData *p)
{
	if (p == NULL) return;
	Iso14827PublicationType_del(p->type);
}

void Iso14827PublicationData_del(Iso14827PublicationData *p)
{
	if (p == NULL) return;
	Iso14827PublicationData_purge(p);
	Dz1Free(p);
}

void Iso14827PublicationData_dump(Iso14827PublicationData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("subscriptionSerial = ")); Dz1u32_dump(&p->subscriptionSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isLated = ")); Dz1Bool_dump(&p->isLated, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type.")); Iso14827PublicationType_dump(p->type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Iso14827PublicationData_cmp(Iso14827PublicationData *a, Iso14827PublicationData *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->subscriptionSerial, &b->subscriptionSerial)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->serial, &b->serial)) != 0) { }
	return ret;
}
// Iso14827PublicationData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublicationDataList
static Dz1Error Iso14827PublicationDataList_add(Iso14827PublicationDataList *p, Iso14827PublicationData *data)
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

static bool_t Iso14827PublicationDataList_remove(Iso14827PublicationDataList *p, Iso14827PublicationData *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Iso14827PublicationData *Iso14827PublicationDataList_extract(Iso14827PublicationDataList *p, Iso14827PublicationData *key)
{
	return (Iso14827PublicationData *)Dz1AATree_extract(p->storage, key);
}

typedef struct Iso14827PublicationDataListMkArrArg
{
	Iso14827PublicationData **arr;
	unsigned int idx;
} Iso14827PublicationDataListMkArrArg;

static Dz1Error _Iso14827PublicationDataList_get_array(void *ptr, Iso14827PublicationData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827PublicationDataListMkArrArg *arg = (Iso14827PublicationDataListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Iso14827PublicationData **Iso14827PublicationDataList_get_array(Iso14827PublicationDataList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Iso14827PublicationData **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Iso14827PublicationData **)Dz1Calloc(sizeof(Iso14827PublicationData *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827PublicationDataListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Iso14827PublicationDataList_get_array, (void *)&arg);
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

static Dz1Error Iso14827PublicationDataList_travelForward(Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Iso14827PublicationData *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Iso14827PublicationDataList_travelBackward(Iso14827PublicationDataList *p, Dz1Error (*func)(void *ptr, Iso14827PublicationData *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Iso14827PublicationData *Iso14827PublicationDataList_find(Iso14827PublicationDataList *p, Iso14827PublicationData *key)
{
	return (Iso14827PublicationData *)Dz1AATree_find(p->storage, key);
}

static Iso14827PublicationData *Iso14827PublicationDataList_getHead(Iso14827PublicationDataList *p)
{
	return (Iso14827PublicationData *)Dz1AATree_getHead(p->storage);
}

static unsigned int Iso14827PublicationDataList_count(Iso14827PublicationDataList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Iso14827PublicationDataList *Iso14827PublicationDataList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PublicationDataList *ret = (Iso14827PublicationDataList *)Dz1Calloc(sizeof(Iso14827PublicationDataList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827PublicationDataList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Iso14827PublicationData_cmp,
				(Dz1DelFunc)Iso14827PublicationData_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Iso14827PublicationDataList_count;
			ret->travel = Iso14827PublicationDataList_travelForward;
			ret->travelForward = Iso14827PublicationDataList_travelForward;
			ret->travelBackward = Iso14827PublicationDataList_travelBackward;
			ret->get_array = Iso14827PublicationDataList_get_array;
			ret->add = Iso14827PublicationDataList_add;
			ret->remove = Iso14827PublicationDataList_remove;
			ret->find = Iso14827PublicationDataList_find;
			ret->extract = Iso14827PublicationDataList_extract;
			ret->getHead = Iso14827PublicationDataList_getHead;
			ret->cmp = Iso14827PublicationData_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PublicationDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Iso14827PublicationDataList_clone(void *ptr, Iso14827PublicationData *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827PublicationDataList *p = (Iso14827PublicationDataList *)ptr;
	Iso14827PublicationData *cloned = Iso14827PublicationData_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Iso14827PublicationDataList *Iso14827PublicationDataList_clone(Iso14827PublicationDataList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PublicationDataList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Iso14827PublicationDataList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827PublicationDataList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Iso14827PublicationDataList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PublicationDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827PublicationDataList_purge(Iso14827PublicationDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Iso14827PublicationDataList_del(Iso14827PublicationDataList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Iso14827PublicationDataList_dump(void *ptr, Iso14827PublicationData *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Iso14827PublicationData_dump(p, tab);
	return err;
}

void Iso14827PublicationDataList_dump(Iso14827PublicationDataList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Iso14827PublicationDataList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827PublicationDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublishFormatPresent
static struct Iso14827PublishFormatPresentMapA
{
	str_t str;
	Iso14827PublishFormatPresent v;
} Iso14827PublishFormatPresentMapA[] =
{
	{ (char *)"dataList", Iso14827PublishFormatPresent_dataList },
	{ (char *)"filename", Iso14827PublishFormatPresent_filename },
	{ NULL, Iso14827PublishFormatPresent_max }
};

str_t Iso14827PublishFormatPresentStrA(Iso14827PublishFormatPresent v)
{
	struct Iso14827PublishFormatPresentMapA *i = NULL;
	for (i = Iso14827PublishFormatPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827PublishFormatPresent Iso14827PublishFormatPresentFromStrA(str_t str)
{
	struct Iso14827PublishFormatPresentMapA *i = NULL;
	for (i = Iso14827PublishFormatPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827PublishFormatPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827PublishFormatPresentMapW
{
	wstr_t str;
	Iso14827PublishFormatPresent v;
} Iso14827PublishFormatPresentMapW[] =
{
	{ (wchar_t *)L"dataList", Iso14827PublishFormatPresent_dataList },
	{ (wchar_t *)L"filename", Iso14827PublishFormatPresent_filename },
	{ NULL, Iso14827PublishFormatPresent_max }
};

wstr_t Iso14827PublishFormatPresentStrW(Iso14827PublishFormatPresent v)
{
	struct Iso14827PublishFormatPresentMapW *i = NULL;
	for (i = Iso14827PublishFormatPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827PublishFormatPresent Iso14827PublishFormatPresentFromStrW(wstr_t str)
{
	struct Iso14827PublishFormatPresentMapW *i = NULL;
	for (i = Iso14827PublishFormatPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827PublishFormatPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827PublishFormatPresent *Iso14827PublishFormatPresent_new(Iso14827PublishFormatPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PublishFormatPresent *__internal_ret = (Iso14827PublishFormatPresent *)Dz1Calloc(sizeof(Iso14827PublishFormatPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827PublishFormatPresent_dump(Iso14827PublishFormatPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827PublishFormatPresentStr(*v));
}
// Iso14827PublishFormatPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PublishFormat
Iso14827PublishFormat *Iso14827PublishFormat_new(Iso14827PublishFormatPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PublishFormat *ret = (Iso14827PublishFormat *)Dz1Calloc(sizeof(Iso14827PublishFormat), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827PublishFormat_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827PublishFormatPresent_dataList:
			// _U_cst_clone
			if (ptr != NULL) ret->x.dataList = (Iso14827PublicationDataList *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PublishFormatPresent_filename:
			// _U_imp_clone
			if (ptr != NULL) ret->x.filename = (Dz1Asn1UTF8Str *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PublishFormatPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PublishFormat_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827PublishFormat_copy(Iso14827PublishFormat *ret, Iso14827PublishFormat *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827PublishFormatPresent_dataList:
			// _U_cst_clone
			if (src->x.dataList && (ret->x.dataList = Iso14827PublicationDataList_clone(src->x.dataList, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827PublishFormatPresent_filename:
			// _U_imp_clone
			if (src->x.filename && (ret->x.filename = Dz1Asn1UTF8Str_clone(src->x.filename, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827PublishFormat *Iso14827PublishFormat_clone(Iso14827PublishFormat *src, Dz1Error *err)
{
	Iso14827PublishFormat *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827PublishFormat *)Dz1Calloc(sizeof(Iso14827PublishFormat), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827PublishFormat_delAndSetNull, (void *)&ret);
		if (Iso14827PublishFormat_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PublishFormat_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827PublishFormat_purge(Iso14827PublishFormat *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827PublishFormatPresent_dataList:
		Iso14827PublicationDataList_del(p->x.dataList);
		break;
	case Iso14827PublishFormatPresent_filename:
		Dz1Asn1UTF8Str_del(p->x.filename);
		break;
	default:
		break;
	}
}

void Iso14827PublishFormat_del(Iso14827PublishFormat *p)
{
	if (!p) return;
	Iso14827PublishFormat_purge(p);
	Dz1Free(p);
}

void Iso14827PublishFormat_dump(Iso14827PublishFormat *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827PublishFormatPresent_dataList:
		Dz1Thread_printf(Dz1T("dataList = ")); Iso14827PublicationDataList_dump(p->x.dataList, tab); 
		break;
	case Iso14827PublishFormatPresent_filename:
		Dz1Thread_printf(Dz1T("filename = ")); Dz1Asn1UTF8Str_dump(p->x.filename, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827PublishFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Publication
Iso14827Publication *Iso14827Publication_new(bool_t guaranteed, 
											 Iso14827PublishFormat *fmt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Publication *__internal_ret = (Iso14827Publication *)Dz1Calloc(sizeof(Iso14827Publication), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Publication_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->guaranteed = guaranteed;
		__internal_ret->fmt = fmt;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Publication_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827Publication_copy(Iso14827Publication *dst, Iso14827Publication *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->fmt && (dst->fmt = Iso14827PublishFormat_clone(src->fmt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->guaranteed = src->guaranteed;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827Publication *Iso14827Publication_clone(Iso14827Publication *src, Dz1Error *err)
{
	Iso14827Publication *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827Publication *)Dz1Calloc(sizeof(Iso14827Publication), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Publication_delAndSetNull, (void *)&dst);
		if (Iso14827Publication_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Publication_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827Publication_purge(Iso14827Publication *p)
{
	if (p == NULL) return;
	Iso14827PublishFormat_del(p->fmt);
}

void Iso14827Publication_del(Iso14827Publication *p)
{
	if (p == NULL) return;
	Iso14827Publication_purge(p);
	Dz1Free(p);
}

void Iso14827Publication_dump(Iso14827Publication *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("guaranteed = ")); Dz1Bool_dump(&p->guaranteed, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fmt.")); Iso14827PublishFormat_dump(p->fmt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827Publication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TransferDone
Iso14827TransferDone *Iso14827TransferDone_new(Dz1Asn1UTF8Str *filename, 
											   bool_t isSuccess, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TransferDone *__internal_ret = (Iso14827TransferDone *)Dz1Calloc(sizeof(Iso14827TransferDone), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TransferDone_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->filename = filename;
		__internal_ret->isSuccess = isSuccess;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TransferDone_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827TransferDone_copy(Iso14827TransferDone *dst, Iso14827TransferDone *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->filename && (dst->filename = Dz1Asn1UTF8Str_clone(src->filename, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->isSuccess = src->isSuccess;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827TransferDone *Iso14827TransferDone_clone(Iso14827TransferDone *src, Dz1Error *err)
{
	Iso14827TransferDone *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827TransferDone *)Dz1Calloc(sizeof(Iso14827TransferDone), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827TransferDone_delAndSetNull, (void *)&dst);
		if (Iso14827TransferDone_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TransferDone_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827TransferDone_purge(Iso14827TransferDone *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->filename);
}

void Iso14827TransferDone_del(Iso14827TransferDone *p)
{
	if (p == NULL) return;
	Iso14827TransferDone_purge(p);
	Dz1Free(p);
}

void Iso14827TransferDone_dump(Iso14827TransferDone *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("filename = ")); Dz1Asn1UTF8Str_dump(p->filename, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isSuccess = ")); Dz1Bool_dump(&p->isSuccess, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827TransferDone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827AcceptTypePresent
static struct Iso14827AcceptTypePresentMapA
{
	str_t str;
	Iso14827AcceptTypePresent v;
} Iso14827AcceptTypePresentMapA[] =
{
	{ (char *)"login", Iso14827AcceptTypePresent_login },
	{ (char *)"singleSubscription", Iso14827AcceptTypePresent_singleSubscription },
	{ (char *)"registeredSubscription", Iso14827AcceptTypePresent_registeredSubscription },
	{ (char *)"publication", Iso14827AcceptTypePresent_publication },
	{ NULL, Iso14827AcceptTypePresent_max }
};

str_t Iso14827AcceptTypePresentStrA(Iso14827AcceptTypePresent v)
{
	struct Iso14827AcceptTypePresentMapA *i = NULL;
	for (i = Iso14827AcceptTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827AcceptTypePresent Iso14827AcceptTypePresentFromStrA(str_t str)
{
	struct Iso14827AcceptTypePresentMapA *i = NULL;
	for (i = Iso14827AcceptTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827AcceptTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827AcceptTypePresentMapW
{
	wstr_t str;
	Iso14827AcceptTypePresent v;
} Iso14827AcceptTypePresentMapW[] =
{
	{ (wchar_t *)L"login", Iso14827AcceptTypePresent_login },
	{ (wchar_t *)L"singleSubscription", Iso14827AcceptTypePresent_singleSubscription },
	{ (wchar_t *)L"registeredSubscription", Iso14827AcceptTypePresent_registeredSubscription },
	{ (wchar_t *)L"publication", Iso14827AcceptTypePresent_publication },
	{ NULL, Iso14827AcceptTypePresent_max }
};

wstr_t Iso14827AcceptTypePresentStrW(Iso14827AcceptTypePresent v)
{
	struct Iso14827AcceptTypePresentMapW *i = NULL;
	for (i = Iso14827AcceptTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827AcceptTypePresent Iso14827AcceptTypePresentFromStrW(wstr_t str)
{
	struct Iso14827AcceptTypePresentMapW *i = NULL;
	for (i = Iso14827AcceptTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827AcceptTypePresent_max;
}
#endif // UNIX_SYSTEM

Iso14827AcceptTypePresent *Iso14827AcceptTypePresent_new(Iso14827AcceptTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827AcceptTypePresent *__internal_ret = (Iso14827AcceptTypePresent *)Dz1Calloc(sizeof(Iso14827AcceptTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827AcceptTypePresent_dump(Iso14827AcceptTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827AcceptTypePresentStr(*v));
}
// Iso14827AcceptTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827AcceptType
Iso14827AcceptType *Iso14827AcceptType_new(Iso14827AcceptTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827AcceptType *ret = (Iso14827AcceptType *)Dz1Calloc(sizeof(Iso14827AcceptType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827AcceptType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827AcceptTypePresent_login:
			// _U_imp_clone
			if (ptr != NULL) ret->x.login = (Dz1Asn1OID *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827AcceptTypePresent_singleSubscription:
			// _U_prim_clone
			if (ptr != NULL) ret->x.singleSubscription = (s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827AcceptTypePresent_registeredSubscription:
			// _U_prim_clone
			if (ptr != NULL) ret->x.registeredSubscription = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827AcceptTypePresent_publication:
			// _U_prim_clone
			if (ptr != NULL) ret->x.publication = (s32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827AcceptTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827AcceptType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827AcceptType_copy(Iso14827AcceptType *ret, Iso14827AcceptType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827AcceptTypePresent_login:
			// _U_imp_clone
			if (src->x.login && (ret->x.login = Dz1Asn1OID_clone(src->x.login, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827AcceptTypePresent_singleSubscription:
			// _U_prim_clone
			if (src->x.singleSubscription && (ret->x.singleSubscription = Dz1s32_clone(src->x.singleSubscription, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827AcceptTypePresent_registeredSubscription:
			// _U_prim_clone
			ret->x.registeredSubscription = src->x.registeredSubscription;
			ERR_CLEAR(errp);
			break;
		case Iso14827AcceptTypePresent_publication:
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

Iso14827AcceptType *Iso14827AcceptType_clone(Iso14827AcceptType *src, Dz1Error *err)
{
	Iso14827AcceptType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827AcceptType *)Dz1Calloc(sizeof(Iso14827AcceptType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827AcceptType_delAndSetNull, (void *)&ret);
		if (Iso14827AcceptType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827AcceptType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827AcceptType_purge(Iso14827AcceptType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827AcceptTypePresent_login:
		Dz1Asn1OID_del(p->x.login);
		break;
	case Iso14827AcceptTypePresent_singleSubscription:
		Dz1s32_del(p->x.singleSubscription);
		break;
	case Iso14827AcceptTypePresent_registeredSubscription:
		break;
	case Iso14827AcceptTypePresent_publication:
		Dz1s32_del(p->x.publication);
		break;
	default:
		break;
	}
}

void Iso14827AcceptType_del(Iso14827AcceptType *p)
{
	if (!p) return;
	Iso14827AcceptType_purge(p);
	Dz1Free(p);
}

void Iso14827AcceptType_dump(Iso14827AcceptType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827AcceptTypePresent_login:
		Dz1Thread_printf(Dz1T("login = ")); Dz1Asn1OID_dump(p->x.login, tab); 
		break;
	case Iso14827AcceptTypePresent_singleSubscription:
		Dz1Thread_printf(Dz1T("singleSubscription = ")); Dz1s32_dump(p->x.singleSubscription, tab); 
		break;
	case Iso14827AcceptTypePresent_registeredSubscription:
		Dz1Thread_printf(Dz1T("registeredSubscription = ")); Dz1u32_dump(&p->x.registeredSubscription, tab); 
		break;
	case Iso14827AcceptTypePresent_publication:
		Dz1Thread_printf(Dz1T("publication = ")); Dz1s32_dump(p->x.publication, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827AcceptType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Accept
Iso14827Accept *Iso14827Accept_new(u32_t pktNbr, Iso14827AcceptType *acceptType, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Accept *__internal_ret = (Iso14827Accept *)Dz1Calloc(sizeof(Iso14827Accept), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Accept_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->pktNbr = pktNbr;
		__internal_ret->acceptType = acceptType;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Accept_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827Accept_copy(Iso14827Accept *dst, Iso14827Accept *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->acceptType && (dst->acceptType = Iso14827AcceptType_clone(src->acceptType, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->pktNbr = src->pktNbr;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827Accept *Iso14827Accept_clone(Iso14827Accept *src, Dz1Error *err)
{
	Iso14827Accept *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827Accept *)Dz1Calloc(sizeof(Iso14827Accept), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Accept_delAndSetNull, (void *)&dst);
		if (Iso14827Accept_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Accept_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827Accept_purge(Iso14827Accept *p)
{
	if (p == NULL) return;
	Iso14827AcceptType_del(p->acceptType);
}

void Iso14827Accept_del(Iso14827Accept *p)
{
	if (p == NULL) return;
	Iso14827Accept_purge(p);
	Dz1Free(p);
}

void Iso14827Accept_dump(Iso14827Accept *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("pktNbr = ")); Dz1u32_dump(&p->pktNbr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("acceptType.")); Iso14827AcceptType_dump(p->acceptType, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827Accept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectLogin
static struct Iso14827RejectLoginMapA
{
	str_t str;
	Iso14827RejectLogin v;
} Iso14827RejectLoginMapA[] =
{
	{ (char *)"other", Iso14827RejectLogin_other },
	{ (char *)"unknownDomainName", Iso14827RejectLogin_unknownDomainName },
	{ (char *)"accessDenied", Iso14827RejectLogin_accessDenied },
	{ (char *)"invalidPassword", Iso14827RejectLogin_invalidPassword },
	{ (char *)"timeoutTooSmall", Iso14827RejectLogin_timeoutTooSmall },
	{ (char *)"timeoutTooLarge", Iso14827RejectLogin_timeoutTooLarge },
	{ (char *)"heartbeatTooSmall", Iso14827RejectLogin_heartbeatTooSmall },
	{ (char *)"heartbeatTooLarge", Iso14827RejectLogin_heartbeatTooLarge },
	{ (char *)"sessionExist", Iso14827RejectLogin_sessionExist },
	{ (char *)"maxSessionReached", Iso14827RejectLogin_maxSessionReached },
	{ NULL, Iso14827RejectLogin_max }
};

str_t Iso14827RejectLoginStrA(Iso14827RejectLogin v)
{
	struct Iso14827RejectLoginMapA *i = NULL;
	for (i = Iso14827RejectLoginMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectLogin Iso14827RejectLoginFromStrA(str_t str)
{
	struct Iso14827RejectLoginMapA *i = NULL;
	for (i = Iso14827RejectLoginMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectLogin_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827RejectLoginMapW
{
	wstr_t str;
	Iso14827RejectLogin v;
} Iso14827RejectLoginMapW[] =
{
	{ (wchar_t *)L"other", Iso14827RejectLogin_other },
	{ (wchar_t *)L"unknownDomainName", Iso14827RejectLogin_unknownDomainName },
	{ (wchar_t *)L"accessDenied", Iso14827RejectLogin_accessDenied },
	{ (wchar_t *)L"invalidPassword", Iso14827RejectLogin_invalidPassword },
	{ (wchar_t *)L"timeoutTooSmall", Iso14827RejectLogin_timeoutTooSmall },
	{ (wchar_t *)L"timeoutTooLarge", Iso14827RejectLogin_timeoutTooLarge },
	{ (wchar_t *)L"heartbeatTooSmall", Iso14827RejectLogin_heartbeatTooSmall },
	{ (wchar_t *)L"heartbeatTooLarge", Iso14827RejectLogin_heartbeatTooLarge },
	{ (wchar_t *)L"sessionExist", Iso14827RejectLogin_sessionExist },
	{ (wchar_t *)L"maxSessionReached", Iso14827RejectLogin_maxSessionReached },
	{ NULL, Iso14827RejectLogin_max }
};

wstr_t Iso14827RejectLoginStrW(Iso14827RejectLogin v)
{
	struct Iso14827RejectLoginMapW *i = NULL;
	for (i = Iso14827RejectLoginMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectLogin Iso14827RejectLoginFromStrW(wstr_t str)
{
	struct Iso14827RejectLoginMapW *i = NULL;
	for (i = Iso14827RejectLoginMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectLogin_max;
}
#endif // UNIX_SYSTEM

Iso14827RejectLogin *Iso14827RejectLogin_new(Iso14827RejectLogin *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RejectLogin *__internal_ret = (Iso14827RejectLogin *)Dz1Calloc(sizeof(Iso14827RejectLogin), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827RejectLogin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectSubscription
static struct Iso14827RejectSubscriptionMapA
{
	str_t str;
	Iso14827RejectSubscription v;
} Iso14827RejectSubscriptionMapA[] =
{
	{ (char *)"other", Iso14827RejectSubscription_other },
	{ (char *)"unknownSubscriptionNbr", Iso14827RejectSubscription_unknownSubscriptionNbr },
	{ (char *)"invalidTimes", Iso14827RejectSubscription_invalidTimes },
	{ (char *)"frequencyTooSmall", Iso14827RejectSubscription_frequencyTooSmall },
	{ (char *)"frequencyTooLarge", Iso14827RejectSubscription_frequencyTooLarge },
	{ (char *)"invalidMode", Iso14827RejectSubscription_invalidMode },
	{ (char *)"publishFormatNotSupported", Iso14827RejectSubscription_publishFormatNotSupported },
	{ (char *)"unknownSubscriptionMsgId", Iso14827RejectSubscription_unknownSubscriptionMsgId },
	{ (char *)"invalidSubscriptionMsgId", Iso14827RejectSubscription_invalidSubscriptionMsgId },
	{ (char *)"invalidSubscriptionContent", Iso14827RejectSubscription_invalidSubscriptionContent },
	{ NULL, Iso14827RejectSubscription_max }
};

str_t Iso14827RejectSubscriptionStrA(Iso14827RejectSubscription v)
{
	struct Iso14827RejectSubscriptionMapA *i = NULL;
	for (i = Iso14827RejectSubscriptionMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectSubscription Iso14827RejectSubscriptionFromStrA(str_t str)
{
	struct Iso14827RejectSubscriptionMapA *i = NULL;
	for (i = Iso14827RejectSubscriptionMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectSubscription_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827RejectSubscriptionMapW
{
	wstr_t str;
	Iso14827RejectSubscription v;
} Iso14827RejectSubscriptionMapW[] =
{
	{ (wchar_t *)L"other", Iso14827RejectSubscription_other },
	{ (wchar_t *)L"unknownSubscriptionNbr", Iso14827RejectSubscription_unknownSubscriptionNbr },
	{ (wchar_t *)L"invalidTimes", Iso14827RejectSubscription_invalidTimes },
	{ (wchar_t *)L"frequencyTooSmall", Iso14827RejectSubscription_frequencyTooSmall },
	{ (wchar_t *)L"frequencyTooLarge", Iso14827RejectSubscription_frequencyTooLarge },
	{ (wchar_t *)L"invalidMode", Iso14827RejectSubscription_invalidMode },
	{ (wchar_t *)L"publishFormatNotSupported", Iso14827RejectSubscription_publishFormatNotSupported },
	{ (wchar_t *)L"unknownSubscriptionMsgId", Iso14827RejectSubscription_unknownSubscriptionMsgId },
	{ (wchar_t *)L"invalidSubscriptionMsgId", Iso14827RejectSubscription_invalidSubscriptionMsgId },
	{ (wchar_t *)L"invalidSubscriptionContent", Iso14827RejectSubscription_invalidSubscriptionContent },
	{ NULL, Iso14827RejectSubscription_max }
};

wstr_t Iso14827RejectSubscriptionStrW(Iso14827RejectSubscription v)
{
	struct Iso14827RejectSubscriptionMapW *i = NULL;
	for (i = Iso14827RejectSubscriptionMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectSubscription Iso14827RejectSubscriptionFromStrW(wstr_t str)
{
	struct Iso14827RejectSubscriptionMapW *i = NULL;
	for (i = Iso14827RejectSubscriptionMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectSubscription_max;
}
#endif // UNIX_SYSTEM

Iso14827RejectSubscription *Iso14827RejectSubscription_new(Iso14827RejectSubscription *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RejectSubscription *__internal_ret = (Iso14827RejectSubscription *)Dz1Calloc(sizeof(Iso14827RejectSubscription), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827RejectSubscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectPublication
static struct Iso14827RejectPublicationMapA
{
	str_t str;
	Iso14827RejectPublication v;
} Iso14827RejectPublicationMapA[] =
{
	{ (char *)"other", Iso14827RejectPublication_other },
	{ (char *)"invalidPublishFormat", Iso14827RejectPublication_invalidPublishFormat },
	{ NULL, Iso14827RejectPublication_max }
};

str_t Iso14827RejectPublicationStrA(Iso14827RejectPublication v)
{
	struct Iso14827RejectPublicationMapA *i = NULL;
	for (i = Iso14827RejectPublicationMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectPublication Iso14827RejectPublicationFromStrA(str_t str)
{
	struct Iso14827RejectPublicationMapA *i = NULL;
	for (i = Iso14827RejectPublicationMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectPublication_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827RejectPublicationMapW
{
	wstr_t str;
	Iso14827RejectPublication v;
} Iso14827RejectPublicationMapW[] =
{
	{ (wchar_t *)L"other", Iso14827RejectPublication_other },
	{ (wchar_t *)L"invalidPublishFormat", Iso14827RejectPublication_invalidPublishFormat },
	{ NULL, Iso14827RejectPublication_max }
};

wstr_t Iso14827RejectPublicationStrW(Iso14827RejectPublication v)
{
	struct Iso14827RejectPublicationMapW *i = NULL;
	for (i = Iso14827RejectPublicationMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectPublication Iso14827RejectPublicationFromStrW(wstr_t str)
{
	struct Iso14827RejectPublicationMapW *i = NULL;
	for (i = Iso14827RejectPublicationMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectPublication_max;
}
#endif // UNIX_SYSTEM

Iso14827RejectPublication *Iso14827RejectPublication_new(Iso14827RejectPublication *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RejectPublication *__internal_ret = (Iso14827RejectPublication *)Dz1Calloc(sizeof(Iso14827RejectPublication), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827RejectPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectPubDataReason
static struct Iso14827RejectPubDataReasonMapA
{
	str_t str;
	Iso14827RejectPubDataReason v;
} Iso14827RejectPubDataReasonMapA[] =
{
	{ (char *)"other", Iso14827RejectPubDataReason_other },
	{ (char *)"unknownSubscription", Iso14827RejectPubDataReason_unknownSubscription },
	{ (char *)"unknownPublicationNbr", Iso14827RejectPubDataReason_unknownPublicationNbr },
	{ (char *)"unknownPublicationMsgId", Iso14827RejectPubDataReason_unknownPublicationMsgId },
	{ (char *)"invalidPublicationMsgId", Iso14827RejectPubDataReason_invalidPublicationMsgId },
	{ (char *)"invalidPublicationMsgContent", Iso14827RejectPubDataReason_invalidPublicationMsgContent },
	{ (char *)"repeatedPublicationNbr", Iso14827RejectPubDataReason_repeatedPublicationNbr },
	{ NULL, Iso14827RejectPubDataReason_max }
};

str_t Iso14827RejectPubDataReasonStrA(Iso14827RejectPubDataReason v)
{
	struct Iso14827RejectPubDataReasonMapA *i = NULL;
	for (i = Iso14827RejectPubDataReasonMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectPubDataReason Iso14827RejectPubDataReasonFromStrA(str_t str)
{
	struct Iso14827RejectPubDataReasonMapA *i = NULL;
	for (i = Iso14827RejectPubDataReasonMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectPubDataReason_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827RejectPubDataReasonMapW
{
	wstr_t str;
	Iso14827RejectPubDataReason v;
} Iso14827RejectPubDataReasonMapW[] =
{
	{ (wchar_t *)L"other", Iso14827RejectPubDataReason_other },
	{ (wchar_t *)L"unknownSubscription", Iso14827RejectPubDataReason_unknownSubscription },
	{ (wchar_t *)L"unknownPublicationNbr", Iso14827RejectPubDataReason_unknownPublicationNbr },
	{ (wchar_t *)L"unknownPublicationMsgId", Iso14827RejectPubDataReason_unknownPublicationMsgId },
	{ (wchar_t *)L"invalidPublicationMsgId", Iso14827RejectPubDataReason_invalidPublicationMsgId },
	{ (wchar_t *)L"invalidPublicationMsgContent", Iso14827RejectPubDataReason_invalidPublicationMsgContent },
	{ (wchar_t *)L"repeatedPublicationNbr", Iso14827RejectPubDataReason_repeatedPublicationNbr },
	{ NULL, Iso14827RejectPubDataReason_max }
};

wstr_t Iso14827RejectPubDataReasonStrW(Iso14827RejectPubDataReason v)
{
	struct Iso14827RejectPubDataReasonMapW *i = NULL;
	for (i = Iso14827RejectPubDataReasonMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectPubDataReason Iso14827RejectPubDataReasonFromStrW(wstr_t str)
{
	struct Iso14827RejectPubDataReasonMapW *i = NULL;
	for (i = Iso14827RejectPubDataReasonMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectPubDataReason_max;
}
#endif // UNIX_SYSTEM

Iso14827RejectPubDataReason *Iso14827RejectPubDataReason_new(Iso14827RejectPubDataReason *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RejectPubDataReason *__internal_ret = (Iso14827RejectPubDataReason *)Dz1Calloc(sizeof(Iso14827RejectPubDataReason), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827RejectPubDataReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectPubData
Iso14827RejectPubData *Iso14827RejectPubData_new(u32_t subSerial, 
												 u32_t pubSerial, 
												 Iso14827RejectPubDataReason reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RejectPubData *__internal_ret = (Iso14827RejectPubData *)Dz1Calloc(sizeof(Iso14827RejectPubData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827RejectPubData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->subSerial = subSerial;
		__internal_ret->pubSerial = pubSerial;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827RejectPubData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827RejectPubData_copy(Iso14827RejectPubData *dst, Iso14827RejectPubData *src, Dz1Error *err)
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

Iso14827RejectPubData *Iso14827RejectPubData_clone(Iso14827RejectPubData *src, Dz1Error *err)
{
	Iso14827RejectPubData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827RejectPubData *)Dz1Calloc(sizeof(Iso14827RejectPubData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827RejectPubData_delAndSetNull, (void *)&dst);
		if (Iso14827RejectPubData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827RejectPubData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827RejectPubData_purge(Iso14827RejectPubData *p)
{
	if (p == NULL) return;
}

void Iso14827RejectPubData_del(Iso14827RejectPubData *p)
{
	if (p == NULL) return;
	Iso14827RejectPubData_purge(p);
	Dz1Free(p);
}

void Iso14827RejectPubData_dump(Iso14827RejectPubData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("subSerial = ")); Dz1u32_dump(&p->subSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pubSerial = ")); Dz1u32_dump(&p->pubSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827RejectPubDataReasonStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827RejectPubData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectTypePresent
static struct Iso14827RejectTypePresentMapA
{
	str_t str;
	Iso14827RejectTypePresent v;
} Iso14827RejectTypePresentMapA[] =
{
	{ (char *)"login", Iso14827RejectTypePresent_login },
	{ (char *)"subscription", Iso14827RejectTypePresent_subscription },
	{ (char *)"publication", Iso14827RejectTypePresent_publication },
	{ (char *)"pubData", Iso14827RejectTypePresent_pubData },
	{ NULL, Iso14827RejectTypePresent_max }
};

str_t Iso14827RejectTypePresentStrA(Iso14827RejectTypePresent v)
{
	struct Iso14827RejectTypePresentMapA *i = NULL;
	for (i = Iso14827RejectTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectTypePresent Iso14827RejectTypePresentFromStrA(str_t str)
{
	struct Iso14827RejectTypePresentMapA *i = NULL;
	for (i = Iso14827RejectTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827RejectTypePresentMapW
{
	wstr_t str;
	Iso14827RejectTypePresent v;
} Iso14827RejectTypePresentMapW[] =
{
	{ (wchar_t *)L"login", Iso14827RejectTypePresent_login },
	{ (wchar_t *)L"subscription", Iso14827RejectTypePresent_subscription },
	{ (wchar_t *)L"publication", Iso14827RejectTypePresent_publication },
	{ (wchar_t *)L"pubData", Iso14827RejectTypePresent_pubData },
	{ NULL, Iso14827RejectTypePresent_max }
};

wstr_t Iso14827RejectTypePresentStrW(Iso14827RejectTypePresent v)
{
	struct Iso14827RejectTypePresentMapW *i = NULL;
	for (i = Iso14827RejectTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827RejectTypePresent Iso14827RejectTypePresentFromStrW(wstr_t str)
{
	struct Iso14827RejectTypePresentMapW *i = NULL;
	for (i = Iso14827RejectTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827RejectTypePresent_max;
}
#endif // UNIX_SYSTEM

Iso14827RejectTypePresent *Iso14827RejectTypePresent_new(Iso14827RejectTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RejectTypePresent *__internal_ret = (Iso14827RejectTypePresent *)Dz1Calloc(sizeof(Iso14827RejectTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827RejectTypePresent_dump(Iso14827RejectTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827RejectTypePresentStr(*v));
}
// Iso14827RejectTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RejectType
Iso14827RejectType *Iso14827RejectType_new(Iso14827RejectTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827RejectType *ret = (Iso14827RejectType *)Dz1Calloc(sizeof(Iso14827RejectType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827RejectType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827RejectTypePresent_login:
			// _U_enum_clone
			if (ptr != NULL) ret->x.login = *(Iso14827RejectLogin *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827RejectTypePresent_subscription:
			// _U_enum_clone
			if (ptr != NULL) ret->x.subscription = *(Iso14827RejectSubscription *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827RejectTypePresent_publication:
			// _U_enum_clone
			if (ptr != NULL) ret->x.publication = *(Iso14827RejectPublication *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827RejectTypePresent_pubData:
			// _U_cst_clone
			if (ptr != NULL) ret->x.pubData = (Iso14827RejectPubData *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827RejectTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827RejectType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827RejectType_copy(Iso14827RejectType *ret, Iso14827RejectType *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827RejectTypePresent_login:
			// _U_enum_clone
			ret->x.login = src->x.login;
			ERR_CLEAR(errp);
			break;
		case Iso14827RejectTypePresent_subscription:
			// _U_enum_clone
			ret->x.subscription = src->x.subscription;
			ERR_CLEAR(errp);
			break;
		case Iso14827RejectTypePresent_publication:
			// _U_enum_clone
			ret->x.publication = src->x.publication;
			ERR_CLEAR(errp);
			break;
		case Iso14827RejectTypePresent_pubData:
			// _U_cst_clone
			if (src->x.pubData && (ret->x.pubData = Iso14827RejectPubData_clone(src->x.pubData, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827RejectType *Iso14827RejectType_clone(Iso14827RejectType *src, Dz1Error *err)
{
	Iso14827RejectType *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827RejectType *)Dz1Calloc(sizeof(Iso14827RejectType), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827RejectType_delAndSetNull, (void *)&ret);
		if (Iso14827RejectType_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827RejectType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827RejectType_purge(Iso14827RejectType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827RejectTypePresent_login:
		break;
	case Iso14827RejectTypePresent_subscription:
		break;
	case Iso14827RejectTypePresent_publication:
		break;
	case Iso14827RejectTypePresent_pubData:
		Iso14827RejectPubData_del(p->x.pubData);
		break;
	default:
		break;
	}
}

void Iso14827RejectType_del(Iso14827RejectType *p)
{
	if (!p) return;
	Iso14827RejectType_purge(p);
	Dz1Free(p);
}

void Iso14827RejectType_dump(Iso14827RejectType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827RejectTypePresent_login:
		Dz1Thread_printf(Dz1T("login = %s(%d)\n"), Iso14827RejectLoginStr(p->x.login), p->x.login);
		break;
	case Iso14827RejectTypePresent_subscription:
		Dz1Thread_printf(Dz1T("subscription = %s(%d)\n"), Iso14827RejectSubscriptionStr(p->x.subscription), p->x.subscription);
		break;
	case Iso14827RejectTypePresent_publication:
		Dz1Thread_printf(Dz1T("publication = %s(%d)\n"), Iso14827RejectPublicationStr(p->x.publication), p->x.publication);
		break;
	case Iso14827RejectTypePresent_pubData:
		Dz1Thread_printf(Dz1T("pubData = ")); Iso14827RejectPubData_dump(p->x.pubData, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827RejectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Reject
Iso14827Reject *Iso14827Reject_new(u32_t pktNbr, 
								   Iso14827RejectType *type, 
								   Iso14827SubscriptionType *altReq, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827Reject *__internal_ret = (Iso14827Reject *)Dz1Calloc(sizeof(Iso14827Reject), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827Reject_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->pktNbr = pktNbr;
		__internal_ret->type = type;
		__internal_ret->altReq = altReq;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Reject_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827Reject_copy(Iso14827Reject *dst, Iso14827Reject *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->type && (dst->type = Iso14827RejectType_clone(src->type, errp)) == NULL) ERR_OUT(errp);
	else if (src->altReq && (dst->altReq = Iso14827SubscriptionType_clone(src->altReq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->pktNbr = src->pktNbr;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827Reject *Iso14827Reject_clone(Iso14827Reject *src, Dz1Error *err)
{
	Iso14827Reject *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827Reject *)Dz1Calloc(sizeof(Iso14827Reject), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827Reject_delAndSetNull, (void *)&dst);
		if (Iso14827Reject_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827Reject_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827Reject_purge(Iso14827Reject *p)
{
	if (p == NULL) return;
	Iso14827RejectType_del(p->type);
	Iso14827SubscriptionType_del(p->altReq);
}

void Iso14827Reject_del(Iso14827Reject *p)
{
	if (p == NULL) return;
	Iso14827Reject_purge(p);
	Dz1Free(p);
}

void Iso14827Reject_dump(Iso14827Reject *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("pktNbr = ")); Dz1u32_dump(&p->pktNbr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type.")); Iso14827RejectType_dump(p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("altReq.")); Iso14827SubscriptionType_dump(p->altReq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827Reject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PDUsPresent
static struct Iso14827PDUsPresentMapA
{
	str_t str;
	Iso14827PDUsPresent v;
} Iso14827PDUsPresentMapA[] =
{
	{ (char *)"initiate", Iso14827PDUsPresent_initiate },
	{ (char *)"login", Iso14827PDUsPresent_login },
	{ (char *)"fred", Iso14827PDUsPresent_fred },
	{ (char *)"term", Iso14827PDUsPresent_term },
	{ (char *)"logout", Iso14827PDUsPresent_logout },
	{ (char *)"subscription", Iso14827PDUsPresent_subscription },
	{ (char *)"publication", Iso14827PDUsPresent_publication },
	{ (char *)"transferDone", Iso14827PDUsPresent_transferDone },
	{ (char *)"ack", Iso14827PDUsPresent_ack },
	{ (char *)"nak", Iso14827PDUsPresent_nak },
	{ NULL, Iso14827PDUsPresent_max }
};

str_t Iso14827PDUsPresentStrA(Iso14827PDUsPresent v)
{
	struct Iso14827PDUsPresentMapA *i = NULL;
	for (i = Iso14827PDUsPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827PDUsPresent Iso14827PDUsPresentFromStrA(str_t str)
{
	struct Iso14827PDUsPresentMapA *i = NULL;
	for (i = Iso14827PDUsPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827PDUsPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827PDUsPresentMapW
{
	wstr_t str;
	Iso14827PDUsPresent v;
} Iso14827PDUsPresentMapW[] =
{
	{ (wchar_t *)L"initiate", Iso14827PDUsPresent_initiate },
	{ (wchar_t *)L"login", Iso14827PDUsPresent_login },
	{ (wchar_t *)L"fred", Iso14827PDUsPresent_fred },
	{ (wchar_t *)L"term", Iso14827PDUsPresent_term },
	{ (wchar_t *)L"logout", Iso14827PDUsPresent_logout },
	{ (wchar_t *)L"subscription", Iso14827PDUsPresent_subscription },
	{ (wchar_t *)L"publication", Iso14827PDUsPresent_publication },
	{ (wchar_t *)L"transferDone", Iso14827PDUsPresent_transferDone },
	{ (wchar_t *)L"ack", Iso14827PDUsPresent_ack },
	{ (wchar_t *)L"nak", Iso14827PDUsPresent_nak },
	{ NULL, Iso14827PDUsPresent_max }
};

wstr_t Iso14827PDUsPresentStrW(Iso14827PDUsPresent v)
{
	struct Iso14827PDUsPresentMapW *i = NULL;
	for (i = Iso14827PDUsPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827PDUsPresent Iso14827PDUsPresentFromStrW(wstr_t str)
{
	struct Iso14827PDUsPresentMapW *i = NULL;
	for (i = Iso14827PDUsPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827PDUsPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827PDUsPresent *Iso14827PDUsPresent_new(Iso14827PDUsPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PDUsPresent *__internal_ret = (Iso14827PDUsPresent *)Dz1Calloc(sizeof(Iso14827PDUsPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827PDUsPresent_dump(Iso14827PDUsPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827PDUsPresentStr(*v));
}
// Iso14827PDUsPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827PDUs
Iso14827PDUs *Iso14827PDUs_new(Iso14827PDUsPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827PDUs *ret = (Iso14827PDUs *)Dz1Calloc(sizeof(Iso14827PDUs), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827PDUsPresent_initiate:
			// _U_cst_clone
			if (ptr != NULL) ret->x.initiate = (Iso14827Initiate *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_login:
			// _U_cst_clone
			if (ptr != NULL) ret->x.login = (Iso14827Login *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_fred:
			// _U_prim_clone
			if (ptr != NULL) ret->x.fred = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_term:
			// _U_enum_clone
			if (ptr != NULL) ret->x.term = *(Iso14827Terminate *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_logout:
			// _U_enum_clone
			if (ptr != NULL) ret->x.logout = *(Iso14827Logout *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_subscription:
			// _U_cst_clone
			if (ptr != NULL) ret->x.subscription = (Iso14827Subscription *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_publication:
			// _U_cst_clone
			if (ptr != NULL) ret->x.publication = (Iso14827Publication *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_transferDone:
			// _U_cst_clone
			if (ptr != NULL) ret->x.transferDone = (Iso14827TransferDone *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_ack:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ack = (Iso14827Accept *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_nak:
			// _U_cst_clone
			if (ptr != NULL) ret->x.nak = (Iso14827Reject *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PDUs_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Iso14827PDUs_copy(Iso14827PDUs *ret, Iso14827PDUs *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Iso14827PDUsPresent_initiate:
			// _U_cst_clone
			if (src->x.initiate && (ret->x.initiate = Iso14827Initiate_clone(src->x.initiate, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827PDUsPresent_login:
			// _U_cst_clone
			if (src->x.login && (ret->x.login = Iso14827Login_clone(src->x.login, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827PDUsPresent_fred:
			// _U_prim_clone
			ret->x.fred = src->x.fred;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_term:
			// _U_enum_clone
			ret->x.term = src->x.term;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_logout:
			// _U_enum_clone
			ret->x.logout = src->x.logout;
			ERR_CLEAR(errp);
			break;
		case Iso14827PDUsPresent_subscription:
			// _U_cst_clone
			if (src->x.subscription && (ret->x.subscription = Iso14827Subscription_clone(src->x.subscription, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827PDUsPresent_publication:
			// _U_cst_clone
			if (src->x.publication && (ret->x.publication = Iso14827Publication_clone(src->x.publication, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827PDUsPresent_transferDone:
			// _U_cst_clone
			if (src->x.transferDone && (ret->x.transferDone = Iso14827TransferDone_clone(src->x.transferDone, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827PDUsPresent_ack:
			// _U_cst_clone
			if (src->x.ack && (ret->x.ack = Iso14827Accept_clone(src->x.ack, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Iso14827PDUsPresent_nak:
			// _U_cst_clone
			if (src->x.nak && (ret->x.nak = Iso14827Reject_clone(src->x.nak, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827PDUs *Iso14827PDUs_clone(Iso14827PDUs *src, Dz1Error *err)
{
	Iso14827PDUs *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Iso14827PDUs *)Dz1Calloc(sizeof(Iso14827PDUs), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827PDUs_delAndSetNull, (void *)&ret);
		if (Iso14827PDUs_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827PDUs_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827PDUs_purge(Iso14827PDUs *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827PDUsPresent_initiate:
		Iso14827Initiate_del(p->x.initiate);
		break;
	case Iso14827PDUsPresent_login:
		Iso14827Login_del(p->x.login);
		break;
	case Iso14827PDUsPresent_fred:
		break;
	case Iso14827PDUsPresent_term:
		break;
	case Iso14827PDUsPresent_logout:
		break;
	case Iso14827PDUsPresent_subscription:
		Iso14827Subscription_del(p->x.subscription);
		break;
	case Iso14827PDUsPresent_publication:
		Iso14827Publication_del(p->x.publication);
		break;
	case Iso14827PDUsPresent_transferDone:
		Iso14827TransferDone_del(p->x.transferDone);
		break;
	case Iso14827PDUsPresent_ack:
		Iso14827Accept_del(p->x.ack);
		break;
	case Iso14827PDUsPresent_nak:
		Iso14827Reject_del(p->x.nak);
		break;
	default:
		break;
	}
}

void Iso14827PDUs_del(Iso14827PDUs *p)
{
	if (!p) return;
	Iso14827PDUs_purge(p);
	Dz1Free(p);
}

void Iso14827PDUs_dump(Iso14827PDUs *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827PDUsPresent_initiate:
		Dz1Thread_printf(Dz1T("initiate = ")); Iso14827Initiate_dump(p->x.initiate, tab); 
		break;
	case Iso14827PDUsPresent_login:
		Dz1Thread_printf(Dz1T("login = ")); Iso14827Login_dump(p->x.login, tab); 
		break;
	case Iso14827PDUsPresent_fred:
		Dz1Thread_printf(Dz1T("fred = ")); Dz1u32_dump(&p->x.fred, tab); 
		break;
	case Iso14827PDUsPresent_term:
		Dz1Thread_printf(Dz1T("term = %s(%d)\n"), Iso14827TerminateStr(p->x.term), p->x.term);
		break;
	case Iso14827PDUsPresent_logout:
		Dz1Thread_printf(Dz1T("logout = %s(%d)\n"), Iso14827LogoutStr(p->x.logout), p->x.logout);
		break;
	case Iso14827PDUsPresent_subscription:
		Dz1Thread_printf(Dz1T("subscription = ")); Iso14827Subscription_dump(p->x.subscription, tab); 
		break;
	case Iso14827PDUsPresent_publication:
		Dz1Thread_printf(Dz1T("publication = ")); Iso14827Publication_dump(p->x.publication, tab); 
		break;
	case Iso14827PDUsPresent_transferDone:
		Dz1Thread_printf(Dz1T("transferDone = ")); Iso14827TransferDone_dump(p->x.transferDone, tab); 
		break;
	case Iso14827PDUsPresent_ack:
		Dz1Thread_printf(Dz1T("ack = ")); Iso14827Accept_dump(p->x.ack, tab); 
		break;
	case Iso14827PDUsPresent_nak:
		Dz1Thread_printf(Dz1T("nak = ")); Iso14827Reject_dump(p->x.nak, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Iso14827PDUs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827C2CAuthMsg
Iso14827C2CAuthMsg *Iso14827C2CAuthMsg_new(Dz1Asn1OctetStr *authInfo, 
										   u32_t pktNbr, 
										   s32_t priority, 
										   Iso14827HdrOpt *hdrOpt, 
										   Iso14827PDUs *pdu, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827C2CAuthMsg *__internal_ret = (Iso14827C2CAuthMsg *)Dz1Calloc(sizeof(Iso14827C2CAuthMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->authInfo = authInfo;
		__internal_ret->pktNbr = pktNbr;
		__internal_ret->priority = priority;
		__internal_ret->hdrOpt = hdrOpt;
		__internal_ret->pdu = pdu;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Iso14827C2CAuthMsg_copy(Iso14827C2CAuthMsg *dst, Iso14827C2CAuthMsg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->authInfo && (dst->authInfo = Dz1Asn1OctetStr_clone(src->authInfo, errp)) == NULL) ERR_OUT(errp);
	else if (src->hdrOpt && (dst->hdrOpt = Iso14827HdrOpt_clone(src->hdrOpt, errp)) == NULL) ERR_OUT(errp);
	else if (src->pdu && (dst->pdu = Iso14827PDUs_clone(src->pdu, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->pktNbr = src->pktNbr;
		dst->priority = src->priority;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Iso14827C2CAuthMsg *Iso14827C2CAuthMsg_clone(Iso14827C2CAuthMsg *src, Dz1Error *err)
{
	Iso14827C2CAuthMsg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Iso14827C2CAuthMsg *)Dz1Calloc(sizeof(Iso14827C2CAuthMsg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Iso14827C2CAuthMsg_delAndSetNull, (void *)&dst);
		if (Iso14827C2CAuthMsg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827C2CAuthMsg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Iso14827C2CAuthMsg_purge(Iso14827C2CAuthMsg *p)
{
	if (p == NULL) return;
	Dz1Asn1OctetStr_del(p->authInfo);
	Iso14827HdrOpt_del(p->hdrOpt);
	Iso14827PDUs_del(p->pdu);
}

void Iso14827C2CAuthMsg_del(Iso14827C2CAuthMsg *p)
{
	if (p == NULL) return;
	Iso14827C2CAuthMsg_purge(p);
	Dz1Free(p);
}

void Iso14827C2CAuthMsg_dump(Iso14827C2CAuthMsg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("authInfo = ")); Dz1Asn1OctetStr_dump(p->authInfo, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pktNbr = ")); Dz1u32_dump(&p->pktNbr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("priority = ")); Dz1s32_dump(&p->priority, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("hdrOpt = ")); Iso14827HdrOpt_dump(p->hdrOpt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pdu.")); Iso14827PDUs_dump(p->pdu, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Iso14827C2CAuthMsg_cmp(Iso14827C2CAuthMsg *a, Iso14827C2CAuthMsg *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->pktNbr, &b->pktNbr)) != 0) { }
	return ret;
}
// Iso14827C2CAuthMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827DatexVersionNumber
static struct Iso14827DatexVersionNumberMapA
{
	str_t str;
	Iso14827DatexVersionNumber v;
} Iso14827DatexVersionNumberMapA[] =
{
	{ (char *)"experimental", Iso14827DatexVersionNumber_experimental },
	{ (char *)"version1", Iso14827DatexVersionNumber_version1 },
	{ (char *)"version2", Iso14827DatexVersionNumber_version2 },
	{ NULL, Iso14827DatexVersionNumber_max }
};

str_t Iso14827DatexVersionNumberStrA(Iso14827DatexVersionNumber v)
{
	struct Iso14827DatexVersionNumberMapA *i = NULL;
	for (i = Iso14827DatexVersionNumberMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827DatexVersionNumber Iso14827DatexVersionNumberFromStrA(str_t str)
{
	struct Iso14827DatexVersionNumberMapA *i = NULL;
	for (i = Iso14827DatexVersionNumberMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827DatexVersionNumber_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827DatexVersionNumberMapW
{
	wstr_t str;
	Iso14827DatexVersionNumber v;
} Iso14827DatexVersionNumberMapW[] =
{
	{ (wchar_t *)L"experimental", Iso14827DatexVersionNumber_experimental },
	{ (wchar_t *)L"version1", Iso14827DatexVersionNumber_version1 },
	{ (wchar_t *)L"version2", Iso14827DatexVersionNumber_version2 },
	{ NULL, Iso14827DatexVersionNumber_max }
};

wstr_t Iso14827DatexVersionNumberStrW(Iso14827DatexVersionNumber v)
{
	struct Iso14827DatexVersionNumberMapW *i = NULL;
	for (i = Iso14827DatexVersionNumberMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827DatexVersionNumber Iso14827DatexVersionNumberFromStrW(wstr_t str)
{
	struct Iso14827DatexVersionNumberMapW *i = NULL;
	for (i = Iso14827DatexVersionNumberMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827DatexVersionNumber_max;
}
#endif // UNIX_SYSTEM

Iso14827DatexVersionNumber *Iso14827DatexVersionNumber_new(Iso14827DatexVersionNumber *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827DatexVersionNumber *__internal_ret = (Iso14827DatexVersionNumber *)Dz1Calloc(sizeof(Iso14827DatexVersionNumber), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Iso14827DatexVersionNumber
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827DatexDataPacket
Iso14827DatexDataPacket *Iso14827DatexDataPacket_new(Iso14827DatexVersionNumber version, 
													 Dz1Asn1OctetStr *data, 
													 u16_t crc16, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827DatexDataPacket *__internal_ret = (Iso14827DatexDataPacket *)Dz1Calloc(sizeof(Iso14827DatexDataPacket), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827DatexDataPacket_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->version = version;
		__internal_ret->data = data;
		__internal_ret->crc16 = crc16;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827DatexDataPacket_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827DatexDataPacket_purge(Iso14827DatexDataPacket *p)
{
	if (p == NULL) return;
	Dz1Asn1OctetStr_del(p->data);
}

void Iso14827DatexDataPacket_del(Iso14827DatexDataPacket *p)
{
	if (p == NULL) return;
	Iso14827DatexDataPacket_purge(p);
	Dz1Free(p);
}

void Iso14827DatexDataPacket_dump(Iso14827DatexDataPacket *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("version = %s(%d)\n"), Iso14827DatexVersionNumberStr(p->version), p->version);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Dz1Asn1OctetStr_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("crc16 = ")); Dz1u16_dump(&p->crc16, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827DatexDataPacket
////////////////////////////////////////////////////////////////////////////////

