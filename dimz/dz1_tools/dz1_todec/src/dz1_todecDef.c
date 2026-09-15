////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_todecDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecUnitSize
static struct Dz1TodecUnitSizeMapA
{
	str_t str;
	Dz1TodecUnitSize v;
} Dz1TodecUnitSizeMapA[] =
{
	{ (char *)"Byte1", Dz1TodecUnitSize_Byte1 },
	{ (char *)"Byte2", Dz1TodecUnitSize_Byte2 },
	{ (char *)"Byte4", Dz1TodecUnitSize_Byte4 },
	{ (char *)"Byte8", Dz1TodecUnitSize_Byte8 },
	{ NULL, Dz1TodecUnitSize_max }
};

str_t Dz1TodecUnitSizeStrA(Dz1TodecUnitSize v)
{
	struct Dz1TodecUnitSizeMapA *i = NULL;
	for (i = Dz1TodecUnitSizeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecUnitSize Dz1TodecUnitSizeFromStrA(str_t str)
{
	struct Dz1TodecUnitSizeMapA *i = NULL;
	for (i = Dz1TodecUnitSizeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecUnitSize_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecUnitSizeMapW
{
	wstr_t str;
	Dz1TodecUnitSize v;
} Dz1TodecUnitSizeMapW[] =
{
	{ (wchar_t *)L"Byte1", Dz1TodecUnitSize_Byte1 },
	{ (wchar_t *)L"Byte2", Dz1TodecUnitSize_Byte2 },
	{ (wchar_t *)L"Byte4", Dz1TodecUnitSize_Byte4 },
	{ (wchar_t *)L"Byte8", Dz1TodecUnitSize_Byte8 },
	{ NULL, Dz1TodecUnitSize_max }
};

wstr_t Dz1TodecUnitSizeStrW(Dz1TodecUnitSize v)
{
	struct Dz1TodecUnitSizeMapW *i = NULL;
	for (i = Dz1TodecUnitSizeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecUnitSize Dz1TodecUnitSizeFromStrW(wstr_t str)
{
	struct Dz1TodecUnitSizeMapW *i = NULL;
	for (i = Dz1TodecUnitSizeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecUnitSize_max;
}
#endif // UNIX_SYSTEM

Dz1TodecUnitSize *Dz1TodecUnitSize_new(Dz1TodecUnitSize *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecUnitSize *__internal_ret = (Dz1TodecUnitSize *)Dz1Calloc(sizeof(Dz1TodecUnitSize), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1TodecUnitSize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecOrigin
static struct Dz1TodecOriginMapA
{
	str_t str;
	Dz1TodecOrigin v;
} Dz1TodecOriginMapA[] =
{
	{ (char *)"MSB", Dz1TodecOrigin_MSB },
	{ (char *)"LSB", Dz1TodecOrigin_LSB },
	{ NULL, Dz1TodecOrigin_max }
};

str_t Dz1TodecOriginStrA(Dz1TodecOrigin v)
{
	struct Dz1TodecOriginMapA *i = NULL;
	for (i = Dz1TodecOriginMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecOrigin Dz1TodecOriginFromStrA(str_t str)
{
	struct Dz1TodecOriginMapA *i = NULL;
	for (i = Dz1TodecOriginMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecOrigin_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecOriginMapW
{
	wstr_t str;
	Dz1TodecOrigin v;
} Dz1TodecOriginMapW[] =
{
	{ (wchar_t *)L"MSB", Dz1TodecOrigin_MSB },
	{ (wchar_t *)L"LSB", Dz1TodecOrigin_LSB },
	{ NULL, Dz1TodecOrigin_max }
};

wstr_t Dz1TodecOriginStrW(Dz1TodecOrigin v)
{
	struct Dz1TodecOriginMapW *i = NULL;
	for (i = Dz1TodecOriginMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecOrigin Dz1TodecOriginFromStrW(wstr_t str)
{
	struct Dz1TodecOriginMapW *i = NULL;
	for (i = Dz1TodecOriginMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecOrigin_max;
}
#endif // UNIX_SYSTEM

Dz1TodecOrigin *Dz1TodecOrigin_new(Dz1TodecOrigin *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecOrigin *__internal_ret = (Dz1TodecOrigin *)Dz1Calloc(sizeof(Dz1TodecOrigin), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1TodecOrigin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBitDescr
Dz1TodecBitDescr *Dz1TodecBitDescr_new(u8_t bit_trim, u8_t bit_take, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecBitDescr *__internal_ret = (Dz1TodecBitDescr *)Dz1Calloc(sizeof(Dz1TodecBitDescr), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecBitDescr_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->bit_trim = bit_trim;
		__internal_ret->bit_take = bit_take;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBitDescr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecBitDescr_copy(Dz1TodecBitDescr *dst, Dz1TodecBitDescr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->bit_trim = src->bit_trim;
		dst->bit_take = src->bit_take;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecBitDescr *Dz1TodecBitDescr_clone(Dz1TodecBitDescr *src, Dz1Error *err)
{
	Dz1TodecBitDescr *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecBitDescr *)Dz1Calloc(sizeof(Dz1TodecBitDescr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecBitDescr_delAndSetNull, (void *)&dst);
		if (Dz1TodecBitDescr_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBitDescr_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecBitDescr_purge(Dz1TodecBitDescr *p)
{
	if (p == NULL) return;
}

void Dz1TodecBitDescr_del(Dz1TodecBitDescr *p)
{
	if (p == NULL) return;
	Dz1TodecBitDescr_purge(p);
	Dz1Free(p);
}

void Dz1TodecBitDescr_dump(Dz1TodecBitDescr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("bit_trim = ")); Dz1u8_dump(&p->bit_trim, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bit_take = ")); Dz1u8_dump(&p->bit_take, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecBitDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecByteDescr
Dz1TodecByteDescr *Dz1TodecByteDescr_new(u8_t byte_trim, 
										 Dz1TodecUnitSize byte_take, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecByteDescr *__internal_ret = (Dz1TodecByteDescr *)Dz1Calloc(sizeof(Dz1TodecByteDescr), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecByteDescr_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->byte_trim = byte_trim;
		__internal_ret->byte_take = byte_take;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecByteDescr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecByteDescr_copy(Dz1TodecByteDescr *dst, Dz1TodecByteDescr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->byte_trim = src->byte_trim;
		dst->byte_take = src->byte_take;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecByteDescr *Dz1TodecByteDescr_clone(Dz1TodecByteDescr *src, Dz1Error *err)
{
	Dz1TodecByteDescr *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecByteDescr *)Dz1Calloc(sizeof(Dz1TodecByteDescr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecByteDescr_delAndSetNull, (void *)&dst);
		if (Dz1TodecByteDescr_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecByteDescr_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecByteDescr_purge(Dz1TodecByteDescr *p)
{
	if (p == NULL) return;
}

void Dz1TodecByteDescr_del(Dz1TodecByteDescr *p)
{
	if (p == NULL) return;
	Dz1TodecByteDescr_purge(p);
	Dz1Free(p);
}

void Dz1TodecByteDescr_dump(Dz1TodecByteDescr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("byte_trim = ")); Dz1u8_dump(&p->byte_trim, tab); 
		Dz1Thread_tprintf(tab, Dz1T("byte_take = %s(%d)\n"), Dz1TodecUnitSizeStr(p->byte_take), p->byte_take);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecByteDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecRestrictDescrPresent
static struct Dz1TodecRestrictDescrPresentMapA
{
	str_t str;
	Dz1TodecRestrictDescrPresent v;
} Dz1TodecRestrictDescrPresentMapA[] =
{
	{ (char *)"fixed", Dz1TodecRestrictDescrPresent_fixed },
	{ (char *)"dynamic", Dz1TodecRestrictDescrPresent_dynamic },
	{ NULL, Dz1TodecRestrictDescrPresent_max }
};

str_t Dz1TodecRestrictDescrPresentStrA(Dz1TodecRestrictDescrPresent v)
{
	struct Dz1TodecRestrictDescrPresentMapA *i = NULL;
	for (i = Dz1TodecRestrictDescrPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecRestrictDescrPresent Dz1TodecRestrictDescrPresentFromStrA(str_t str)
{
	struct Dz1TodecRestrictDescrPresentMapA *i = NULL;
	for (i = Dz1TodecRestrictDescrPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecRestrictDescrPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecRestrictDescrPresentMapW
{
	wstr_t str;
	Dz1TodecRestrictDescrPresent v;
} Dz1TodecRestrictDescrPresentMapW[] =
{
	{ (wchar_t *)L"fixed", Dz1TodecRestrictDescrPresent_fixed },
	{ (wchar_t *)L"dynamic", Dz1TodecRestrictDescrPresent_dynamic },
	{ NULL, Dz1TodecRestrictDescrPresent_max }
};

wstr_t Dz1TodecRestrictDescrPresentStrW(Dz1TodecRestrictDescrPresent v)
{
	struct Dz1TodecRestrictDescrPresentMapW *i = NULL;
	for (i = Dz1TodecRestrictDescrPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecRestrictDescrPresent Dz1TodecRestrictDescrPresentFromStrW(wstr_t str)
{
	struct Dz1TodecRestrictDescrPresentMapW *i = NULL;
	for (i = Dz1TodecRestrictDescrPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecRestrictDescrPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TodecRestrictDescrPresent *Dz1TodecRestrictDescrPresent_new(Dz1TodecRestrictDescrPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecRestrictDescrPresent *__internal_ret = (Dz1TodecRestrictDescrPresent *)Dz1Calloc(sizeof(Dz1TodecRestrictDescrPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TodecRestrictDescrPresent_dump(Dz1TodecRestrictDescrPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TodecRestrictDescrPresentStr(*v));
}
// Dz1TodecRestrictDescrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecRestrictDescr
Dz1TodecRestrictDescr *Dz1TodecRestrictDescr_new(Dz1TodecRestrictDescrPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecRestrictDescr *ret = (Dz1TodecRestrictDescr *)Dz1Calloc(sizeof(Dz1TodecRestrictDescr), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecRestrictDescr_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TodecRestrictDescrPresent_fixed:
			// _U_prim_clone
			if (ptr != NULL) ret->x.fixed = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecRestrictDescrPresent_dynamic:
			// _U_enum_clone
			if (ptr != NULL) ret->x.dynamic = *(Dz1TodecUnitSize *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecRestrictDescrPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecRestrictDescr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TodecRestrictDescr_copy(Dz1TodecRestrictDescr *ret, Dz1TodecRestrictDescr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TodecRestrictDescrPresent_fixed:
			// _U_prim_clone
			ret->x.fixed = src->x.fixed;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecRestrictDescrPresent_dynamic:
			// _U_enum_clone
			ret->x.dynamic = src->x.dynamic;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecRestrictDescr *Dz1TodecRestrictDescr_clone(Dz1TodecRestrictDescr *src, Dz1Error *err)
{
	Dz1TodecRestrictDescr *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TodecRestrictDescr *)Dz1Calloc(sizeof(Dz1TodecRestrictDescr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecRestrictDescr_delAndSetNull, (void *)&ret);
		if (Dz1TodecRestrictDescr_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecRestrictDescr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecRestrictDescr_purge(Dz1TodecRestrictDescr *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TodecRestrictDescrPresent_fixed:
		break;
	case Dz1TodecRestrictDescrPresent_dynamic:
		break;
	default:
		break;
	}
}

void Dz1TodecRestrictDescr_del(Dz1TodecRestrictDescr *p)
{
	if (!p) return;
	Dz1TodecRestrictDescr_purge(p);
	Dz1Free(p);
}

void Dz1TodecRestrictDescr_dump(Dz1TodecRestrictDescr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TodecRestrictDescrPresent_fixed:
		Dz1Thread_printf(Dz1T("fixed = ")); Dz1u32_dump(&p->x.fixed, tab); 
		break;
	case Dz1TodecRestrictDescrPresent_dynamic:
		Dz1Thread_printf(Dz1T("dynamic = %s(%d)\n"), Dz1TodecUnitSizeStr(p->x.dynamic), p->x.dynamic);
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TodecRestrictDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchDataEntry
Dz1TodecBunchDataEntry *Dz1TodecBunchDataEntry_new(str_t src_name, 
												   Dz1TodecBitDescr *src_descr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecBunchDataEntry *__internal_ret = (Dz1TodecBunchDataEntry *)Dz1Calloc(sizeof(Dz1TodecBunchDataEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecBunchDataEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (src_name && (__internal_ret->src_name = dz1_built_in_str_clone(src_name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->src_descr = src_descr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBunchDataEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecBunchDataEntry_copy(Dz1TodecBunchDataEntry *dst, Dz1TodecBunchDataEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->src_name && (dst->src_name = dz1_built_in_str_clone(src->src_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->src_descr && (dst->src_descr = Dz1TodecBitDescr_clone(src->src_descr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecBunchDataEntry *Dz1TodecBunchDataEntry_clone(Dz1TodecBunchDataEntry *src, Dz1Error *err)
{
	Dz1TodecBunchDataEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecBunchDataEntry *)Dz1Calloc(sizeof(Dz1TodecBunchDataEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecBunchDataEntry_delAndSetNull, (void *)&dst);
		if (Dz1TodecBunchDataEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBunchDataEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecBunchDataEntry_purge(Dz1TodecBunchDataEntry *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->src_name);
	Dz1TodecBitDescr_del(p->src_descr);
}

void Dz1TodecBunchDataEntry_del(Dz1TodecBunchDataEntry *p)
{
	if (p == NULL) return;
	Dz1TodecBunchDataEntry_purge(p);
	Dz1Free(p);
}

void Dz1TodecBunchDataEntry_dump(Dz1TodecBunchDataEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("src_name = ")); dz1_built_in_str_dump(p->src_name, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("src_descr = ")); Dz1TodecBitDescr_dump(p->src_descr, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecBunchDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchEntryPresent
static struct Dz1TodecBunchEntryPresentMapA
{
	str_t str;
	Dz1TodecBunchEntryPresent v;
} Dz1TodecBunchEntryPresentMapA[] =
{
	{ (char *)"data_bits", Dz1TodecBunchEntryPresent_data_bits },
	{ (char *)"pad_bits", Dz1TodecBunchEntryPresent_pad_bits },
	{ NULL, Dz1TodecBunchEntryPresent_max }
};

str_t Dz1TodecBunchEntryPresentStrA(Dz1TodecBunchEntryPresent v)
{
	struct Dz1TodecBunchEntryPresentMapA *i = NULL;
	for (i = Dz1TodecBunchEntryPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecBunchEntryPresent Dz1TodecBunchEntryPresentFromStrA(str_t str)
{
	struct Dz1TodecBunchEntryPresentMapA *i = NULL;
	for (i = Dz1TodecBunchEntryPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecBunchEntryPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecBunchEntryPresentMapW
{
	wstr_t str;
	Dz1TodecBunchEntryPresent v;
} Dz1TodecBunchEntryPresentMapW[] =
{
	{ (wchar_t *)L"data_bits", Dz1TodecBunchEntryPresent_data_bits },
	{ (wchar_t *)L"pad_bits", Dz1TodecBunchEntryPresent_pad_bits },
	{ NULL, Dz1TodecBunchEntryPresent_max }
};

wstr_t Dz1TodecBunchEntryPresentStrW(Dz1TodecBunchEntryPresent v)
{
	struct Dz1TodecBunchEntryPresentMapW *i = NULL;
	for (i = Dz1TodecBunchEntryPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecBunchEntryPresent Dz1TodecBunchEntryPresentFromStrW(wstr_t str)
{
	struct Dz1TodecBunchEntryPresentMapW *i = NULL;
	for (i = Dz1TodecBunchEntryPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecBunchEntryPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TodecBunchEntryPresent *Dz1TodecBunchEntryPresent_new(Dz1TodecBunchEntryPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecBunchEntryPresent *__internal_ret = (Dz1TodecBunchEntryPresent *)Dz1Calloc(sizeof(Dz1TodecBunchEntryPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TodecBunchEntryPresent_dump(Dz1TodecBunchEntryPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TodecBunchEntryPresentStr(*v));
}
// Dz1TodecBunchEntryPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchEntry
Dz1TodecBunchEntry *Dz1TodecBunchEntry_new(Dz1TodecBunchEntryPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecBunchEntry *ret = (Dz1TodecBunchEntry *)Dz1Calloc(sizeof(Dz1TodecBunchEntry), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecBunchEntry_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TodecBunchEntryPresent_data_bits:
			// _U_cst_clone
			if (ptr != NULL) ret->x.data_bits = (Dz1TodecBunchDataEntry *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecBunchEntryPresent_pad_bits:
			// _U_prim_clone
			if (ptr != NULL) ret->x.pad_bits = *(u8_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecBunchEntryPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBunchEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TodecBunchEntry_copy(Dz1TodecBunchEntry *ret, Dz1TodecBunchEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TodecBunchEntryPresent_data_bits:
			// _U_cst_clone
			if (src->x.data_bits && (ret->x.data_bits = Dz1TodecBunchDataEntry_clone(src->x.data_bits, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecBunchEntryPresent_pad_bits:
			// _U_prim_clone
			ret->x.pad_bits = src->x.pad_bits;
			ERR_CLEAR(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecBunchEntry *Dz1TodecBunchEntry_clone(Dz1TodecBunchEntry *src, Dz1Error *err)
{
	Dz1TodecBunchEntry *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TodecBunchEntry *)Dz1Calloc(sizeof(Dz1TodecBunchEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecBunchEntry_delAndSetNull, (void *)&ret);
		if (Dz1TodecBunchEntry_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBunchEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecBunchEntry_purge(Dz1TodecBunchEntry *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TodecBunchEntryPresent_data_bits:
		Dz1TodecBunchDataEntry_del(p->x.data_bits);
		break;
	case Dz1TodecBunchEntryPresent_pad_bits:
		break;
	default:
		break;
	}
}

void Dz1TodecBunchEntry_del(Dz1TodecBunchEntry *p)
{
	if (!p) return;
	Dz1TodecBunchEntry_purge(p);
	Dz1Free(p);
}

void Dz1TodecBunchEntry_dump(Dz1TodecBunchEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TodecBunchEntryPresent_data_bits:
		Dz1Thread_printf(Dz1T("data_bits = ")); Dz1TodecBunchDataEntry_dump(p->x.data_bits, tab); 
		break;
	case Dz1TodecBunchEntryPresent_pad_bits:
		Dz1Thread_printf(Dz1T("pad_bits = ")); Dz1u8_dump(&p->x.pad_bits, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TodecBunchEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchSeq
static Dz1Error Dz1TodecBunchSeq_add(Dz1TodecBunchSeq *p, Dz1TodecBunchEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TodecBunchSeqMkArrArg
{
	Dz1TodecBunchEntry **arr;
	unsigned int idx;
} Dz1TodecBunchSeqMkArrArg;

static Dz1Error _Dz1TodecBunchSeq_get_array(void *ptr, Dz1TodecBunchEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecBunchSeqMkArrArg *arg = (Dz1TodecBunchSeqMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TodecBunchEntry **Dz1TodecBunchSeq_get_array(Dz1TodecBunchSeq *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TodecBunchEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TodecBunchEntry **)Dz1Calloc(sizeof(Dz1TodecBunchEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecBunchSeqMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TodecBunchSeq_get_array, (void *)&arg);
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

static Dz1Error Dz1TodecBunchSeq_travelForward(Dz1TodecBunchSeq *p, Dz1Error (*func)(void *ptr, Dz1TodecBunchEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TodecBunchSeq_travelBackward(Dz1TodecBunchSeq *p, Dz1Error (*func)(void *ptr, Dz1TodecBunchEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TodecBunchSeq_count(Dz1TodecBunchSeq *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TodecBunchSeq *Dz1TodecBunchSeq_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecBunchSeq *ret = (Dz1TodecBunchSeq *)Dz1Calloc(sizeof(Dz1TodecBunchSeq), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecBunchSeq_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1TodecBunchEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TodecBunchSeq_count;
			ret->travel = Dz1TodecBunchSeq_travelForward;
			ret->travelForward = Dz1TodecBunchSeq_travelForward;
			ret->travelBackward = Dz1TodecBunchSeq_travelBackward;
			ret->get_array = Dz1TodecBunchSeq_get_array;
			ret->add = Dz1TodecBunchSeq_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBunchSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TodecBunchSeq_clone(void *ptr, Dz1TodecBunchEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecBunchSeq *p = (Dz1TodecBunchSeq *)ptr;
	Dz1TodecBunchEntry *cloned = Dz1TodecBunchEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TodecBunchSeq *Dz1TodecBunchSeq_clone(Dz1TodecBunchSeq *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecBunchSeq *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TodecBunchSeq_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecBunchSeq_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TodecBunchSeq_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBunchSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecBunchSeq_purge(Dz1TodecBunchSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TodecBunchSeq_del(Dz1TodecBunchSeq *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TodecBunchSeq_dump(void *ptr, Dz1TodecBunchEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TodecBunchEntry_dump(p, tab);
	return err;
}

void Dz1TodecBunchSeq_dump(Dz1TodecBunchSeq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TodecBunchSeq_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecBunchSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchOfSource
Dz1TodecBunchOfSource *Dz1TodecBunchOfSource_new(Dz1TodecUnitSize target_sz, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecBunchOfSource *__internal_ret = (Dz1TodecBunchOfSource *)Dz1Calloc(sizeof(Dz1TodecBunchOfSource), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecBunchOfSource_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->seq = Dz1TodecBunchSeq_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->target_sz = target_sz;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBunchOfSource_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecBunchOfSource_copy(Dz1TodecBunchOfSource *dst, Dz1TodecBunchOfSource *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->seq && (dst->seq = Dz1TodecBunchSeq_clone(src->seq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->target_sz = src->target_sz;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecBunchOfSource *Dz1TodecBunchOfSource_clone(Dz1TodecBunchOfSource *src, Dz1Error *err)
{
	Dz1TodecBunchOfSource *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecBunchOfSource *)Dz1Calloc(sizeof(Dz1TodecBunchOfSource), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecBunchOfSource_delAndSetNull, (void *)&dst);
		if (Dz1TodecBunchOfSource_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecBunchOfSource_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecBunchOfSource_purge(Dz1TodecBunchOfSource *p)
{
	if (p == NULL) return;
	Dz1TodecBunchSeq_del(p->seq);
}

void Dz1TodecBunchOfSource_del(Dz1TodecBunchOfSource *p)
{
	if (p == NULL) return;
	Dz1TodecBunchOfSource_purge(p);
	Dz1Free(p);
}

void Dz1TodecBunchOfSource_dump(Dz1TodecBunchOfSource *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("target_sz = %s(%d)\n"), Dz1TodecUnitSizeStr(p->target_sz), p->target_sz);
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1TodecBunchSeq_dump(p->seq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecBunchOfSource
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecSingleDescrPresent
static struct Dz1TodecSingleDescrPresentMapA
{
	str_t str;
	Dz1TodecSingleDescrPresent v;
} Dz1TodecSingleDescrPresentMapA[] =
{
	{ (char *)"partial_byte", Dz1TodecSingleDescrPresent_partial_byte },
	{ (char *)"restricted", Dz1TodecSingleDescrPresent_restricted },
	{ (char *)"alter_codec", Dz1TodecSingleDescrPresent_alter_codec },
	{ NULL, Dz1TodecSingleDescrPresent_max }
};

str_t Dz1TodecSingleDescrPresentStrA(Dz1TodecSingleDescrPresent v)
{
	struct Dz1TodecSingleDescrPresentMapA *i = NULL;
	for (i = Dz1TodecSingleDescrPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecSingleDescrPresent Dz1TodecSingleDescrPresentFromStrA(str_t str)
{
	struct Dz1TodecSingleDescrPresentMapA *i = NULL;
	for (i = Dz1TodecSingleDescrPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecSingleDescrPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecSingleDescrPresentMapW
{
	wstr_t str;
	Dz1TodecSingleDescrPresent v;
} Dz1TodecSingleDescrPresentMapW[] =
{
	{ (wchar_t *)L"partial_byte", Dz1TodecSingleDescrPresent_partial_byte },
	{ (wchar_t *)L"restricted", Dz1TodecSingleDescrPresent_restricted },
	{ (wchar_t *)L"alter_codec", Dz1TodecSingleDescrPresent_alter_codec },
	{ NULL, Dz1TodecSingleDescrPresent_max }
};

wstr_t Dz1TodecSingleDescrPresentStrW(Dz1TodecSingleDescrPresent v)
{
	struct Dz1TodecSingleDescrPresentMapW *i = NULL;
	for (i = Dz1TodecSingleDescrPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecSingleDescrPresent Dz1TodecSingleDescrPresentFromStrW(wstr_t str)
{
	struct Dz1TodecSingleDescrPresentMapW *i = NULL;
	for (i = Dz1TodecSingleDescrPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecSingleDescrPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TodecSingleDescrPresent *Dz1TodecSingleDescrPresent_new(Dz1TodecSingleDescrPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecSingleDescrPresent *__internal_ret = (Dz1TodecSingleDescrPresent *)Dz1Calloc(sizeof(Dz1TodecSingleDescrPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TodecSingleDescrPresent_dump(Dz1TodecSingleDescrPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TodecSingleDescrPresentStr(*v));
}
// Dz1TodecSingleDescrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecSingleDescr
Dz1TodecSingleDescr *Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecSingleDescr *ret = (Dz1TodecSingleDescr *)Dz1Calloc(sizeof(Dz1TodecSingleDescr), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecSingleDescr_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TodecSingleDescrPresent_partial_byte:
			// _U_cst_clone
			if (ptr != NULL) ret->x.partial_byte = (Dz1TodecByteDescr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecSingleDescrPresent_restricted:
			// _U_cst_clone
			if (ptr != NULL) ret->x.restricted = (Dz1TodecRestrictDescr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecSingleDescrPresent_alter_codec:
			// _U_prim_clone
			if (ptr && (ret->x.alter_codec = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecSingleDescrPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecSingleDescr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TodecSingleDescr_copy(Dz1TodecSingleDescr *ret, Dz1TodecSingleDescr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TodecSingleDescrPresent_partial_byte:
			// _U_cst_clone
			if (src->x.partial_byte && (ret->x.partial_byte = Dz1TodecByteDescr_clone(src->x.partial_byte, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecSingleDescrPresent_restricted:
			// _U_cst_clone
			if (src->x.restricted && (ret->x.restricted = Dz1TodecRestrictDescr_clone(src->x.restricted, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecSingleDescrPresent_alter_codec:
			// _U_prim_clone
			if (src->x.alter_codec && (ret->x.alter_codec = dz1_built_in_str_clone(src->x.alter_codec, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecSingleDescr *Dz1TodecSingleDescr_clone(Dz1TodecSingleDescr *src, Dz1Error *err)
{
	Dz1TodecSingleDescr *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TodecSingleDescr *)Dz1Calloc(sizeof(Dz1TodecSingleDescr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecSingleDescr_delAndSetNull, (void *)&ret);
		if (Dz1TodecSingleDescr_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecSingleDescr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecSingleDescr_purge(Dz1TodecSingleDescr *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TodecSingleDescrPresent_partial_byte:
		Dz1TodecByteDescr_del(p->x.partial_byte);
		break;
	case Dz1TodecSingleDescrPresent_restricted:
		Dz1TodecRestrictDescr_del(p->x.restricted);
		break;
	case Dz1TodecSingleDescrPresent_alter_codec:
		dz1_built_in_str_del(p->x.alter_codec);
		break;
	default:
		break;
	}
}

void Dz1TodecSingleDescr_del(Dz1TodecSingleDescr *p)
{
	if (!p) return;
	Dz1TodecSingleDescr_purge(p);
	Dz1Free(p);
}

void Dz1TodecSingleDescr_dump(Dz1TodecSingleDescr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TodecSingleDescrPresent_partial_byte:
		Dz1Thread_printf(Dz1T("partial_byte = ")); Dz1TodecByteDescr_dump(p->x.partial_byte, tab); 
		break;
	case Dz1TodecSingleDescrPresent_restricted:
		Dz1Thread_printf(Dz1T("restricted.")); Dz1TodecRestrictDescr_dump(p->x.restricted, tab); 
		break;
	case Dz1TodecSingleDescrPresent_alter_codec:
		Dz1Thread_printf(Dz1T("alter_codec = ")); dz1_built_in_str_dump(p->x.alter_codec, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TodecSingleDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecSingleSource
Dz1TodecSingleSource *Dz1TodecSingleSource_new(str_t src_name, 
											   Dz1TodecSingleDescr *src_descr, 
											   Dz1TodecUnitSize nul_flag, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecSingleSource *__internal_ret = (Dz1TodecSingleSource *)Dz1Calloc(sizeof(Dz1TodecSingleSource), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecSingleSource_delAndSetNull, (void *)&__internal_ret);
		
		if (src_name && (__internal_ret->src_name = dz1_built_in_str_clone(src_name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->src_descr = src_descr;
			__internal_ret->nul_flag = nul_flag;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecSingleSource_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecSingleSource_copy(Dz1TodecSingleSource *dst, Dz1TodecSingleSource *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->src_name && (dst->src_name = dz1_built_in_str_clone(src->src_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->src_descr && (dst->src_descr = Dz1TodecSingleDescr_clone(src->src_descr, errp)) == NULL) ERR_OUT(errp);
	else if (src->postfix && (dst->postfix = dz1_built_in_str_clone(src->postfix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->nul_flag = src->nul_flag;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecSingleSource *Dz1TodecSingleSource_clone(Dz1TodecSingleSource *src, Dz1Error *err)
{
	Dz1TodecSingleSource *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecSingleSource *)Dz1Calloc(sizeof(Dz1TodecSingleSource), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecSingleSource_delAndSetNull, (void *)&dst);
		if (Dz1TodecSingleSource_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecSingleSource_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecSingleSource_purge(Dz1TodecSingleSource *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->src_name);
	Dz1TodecSingleDescr_del(p->src_descr);
	dz1_built_in_str_del(p->postfix);
}

void Dz1TodecSingleSource_del(Dz1TodecSingleSource *p)
{
	if (p == NULL) return;
	Dz1TodecSingleSource_purge(p);
	Dz1Free(p);
}

void Dz1TodecSingleSource_dump(Dz1TodecSingleSource *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("src_name = ")); dz1_built_in_str_dump(p->src_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("src_descr.")); Dz1TodecSingleDescr_dump(p->src_descr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("nul_flag = %s(%d)\n"), Dz1TodecUnitSizeStr(p->nul_flag), p->nul_flag);
		Dz1Thread_tprintf(tab, Dz1T("postfix = ")); dz1_built_in_str_dump(p->postfix, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecSingleSource
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecConditionalSource
Dz1TodecConditionalSource *Dz1TodecConditionalSource_new(str_t src_name, 
														 str_t decider, 
														 Dz1TodecSingleDescr *src_descr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecConditionalSource *__internal_ret = (Dz1TodecConditionalSource *)Dz1Calloc(sizeof(Dz1TodecConditionalSource), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecConditionalSource_delAndSetNull, (void *)&__internal_ret);
		
		if (src_name && (__internal_ret->src_name = dz1_built_in_str_clone(src_name, errp)) == NULL) ERR_OUT(errp);
		else if (decider && (__internal_ret->decider = dz1_built_in_str_clone(decider, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->src_descr = src_descr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecConditionalSource_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecConditionalSource_copy(Dz1TodecConditionalSource *dst, Dz1TodecConditionalSource *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->src_name && (dst->src_name = dz1_built_in_str_clone(src->src_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->decider && (dst->decider = dz1_built_in_str_clone(src->decider, errp)) == NULL) ERR_OUT(errp);
	else if (src->src_descr && (dst->src_descr = Dz1TodecSingleDescr_clone(src->src_descr, errp)) == NULL) ERR_OUT(errp);
	else if (src->postfix && (dst->postfix = dz1_built_in_str_clone(src->postfix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecConditionalSource *Dz1TodecConditionalSource_clone(Dz1TodecConditionalSource *src, Dz1Error *err)
{
	Dz1TodecConditionalSource *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecConditionalSource *)Dz1Calloc(sizeof(Dz1TodecConditionalSource), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecConditionalSource_delAndSetNull, (void *)&dst);
		if (Dz1TodecConditionalSource_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecConditionalSource_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecConditionalSource_purge(Dz1TodecConditionalSource *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->src_name);
	dz1_built_in_str_del(p->decider);
	Dz1TodecSingleDescr_del(p->src_descr);
	dz1_built_in_str_del(p->postfix);
}

void Dz1TodecConditionalSource_del(Dz1TodecConditionalSource *p)
{
	if (p == NULL) return;
	Dz1TodecConditionalSource_purge(p);
	Dz1Free(p);
}

void Dz1TodecConditionalSource_dump(Dz1TodecConditionalSource *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("src_name = ")); dz1_built_in_str_dump(p->src_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("decider = ")); dz1_built_in_str_dump(p->decider, tab); 
		Dz1Thread_tprintf(tab, Dz1T("src_descr.")); Dz1TodecSingleDescr_dump(p->src_descr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("postfix = ")); dz1_built_in_str_dump(p->postfix, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecConditionalSource
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrDescrPresent
static struct Dz1TodecTargetCodecAttrDescrPresentMapA
{
	str_t str;
	Dz1TodecTargetCodecAttrDescrPresent v;
} Dz1TodecTargetCodecAttrDescrPresentMapA[] =
{
	{ (char *)"omit", Dz1TodecTargetCodecAttrDescrPresent_omit },
	{ (char *)"def", Dz1TodecTargetCodecAttrDescrPresent_def },
	{ (char *)"partial_byte", Dz1TodecTargetCodecAttrDescrPresent_partial_byte },
	{ (char *)"alter_codec", Dz1TodecTargetCodecAttrDescrPresent_alter_codec },
	{ NULL, Dz1TodecTargetCodecAttrDescrPresent_max }
};

str_t Dz1TodecTargetCodecAttrDescrPresentStrA(Dz1TodecTargetCodecAttrDescrPresent v)
{
	struct Dz1TodecTargetCodecAttrDescrPresentMapA *i = NULL;
	for (i = Dz1TodecTargetCodecAttrDescrPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecTargetCodecAttrDescrPresent Dz1TodecTargetCodecAttrDescrPresentFromStrA(str_t str)
{
	struct Dz1TodecTargetCodecAttrDescrPresentMapA *i = NULL;
	for (i = Dz1TodecTargetCodecAttrDescrPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecTargetCodecAttrDescrPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecTargetCodecAttrDescrPresentMapW
{
	wstr_t str;
	Dz1TodecTargetCodecAttrDescrPresent v;
} Dz1TodecTargetCodecAttrDescrPresentMapW[] =
{
	{ (wchar_t *)L"omit", Dz1TodecTargetCodecAttrDescrPresent_omit },
	{ (wchar_t *)L"def", Dz1TodecTargetCodecAttrDescrPresent_def },
	{ (wchar_t *)L"partial_byte", Dz1TodecTargetCodecAttrDescrPresent_partial_byte },
	{ (wchar_t *)L"alter_codec", Dz1TodecTargetCodecAttrDescrPresent_alter_codec },
	{ NULL, Dz1TodecTargetCodecAttrDescrPresent_max }
};

wstr_t Dz1TodecTargetCodecAttrDescrPresentStrW(Dz1TodecTargetCodecAttrDescrPresent v)
{
	struct Dz1TodecTargetCodecAttrDescrPresentMapW *i = NULL;
	for (i = Dz1TodecTargetCodecAttrDescrPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecTargetCodecAttrDescrPresent Dz1TodecTargetCodecAttrDescrPresentFromStrW(wstr_t str)
{
	struct Dz1TodecTargetCodecAttrDescrPresentMapW *i = NULL;
	for (i = Dz1TodecTargetCodecAttrDescrPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecTargetCodecAttrDescrPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TodecTargetCodecAttrDescrPresent *Dz1TodecTargetCodecAttrDescrPresent_new(Dz1TodecTargetCodecAttrDescrPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecAttrDescrPresent *__internal_ret = (Dz1TodecTargetCodecAttrDescrPresent *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttrDescrPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TodecTargetCodecAttrDescrPresent_dump(Dz1TodecTargetCodecAttrDescrPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TodecTargetCodecAttrDescrPresentStr(*v));
}
// Dz1TodecTargetCodecAttrDescrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrDescr
Dz1TodecTargetCodecAttrDescr *Dz1TodecTargetCodecAttrDescr_new(Dz1TodecTargetCodecAttrDescrPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecAttrDescr *ret = (Dz1TodecTargetCodecAttrDescr *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttrDescr), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecAttrDescr_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TodecTargetCodecAttrDescrPresent_omit:
			// _U_prim_clone
			if (ptr != NULL) ret->x.omit = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecTargetCodecAttrDescrPresent_def:
			// _U_prim_clone
			if (ptr != NULL) ret->x.def = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecTargetCodecAttrDescrPresent_partial_byte:
			// _U_cst_clone
			if (ptr != NULL) ret->x.partial_byte = (Dz1TodecByteDescr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecTargetCodecAttrDescrPresent_alter_codec:
			// _U_prim_clone
			if (ptr && (ret->x.alter_codec = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecTargetCodecAttrDescrPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecAttrDescr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TodecTargetCodecAttrDescr_copy(Dz1TodecTargetCodecAttrDescr *ret, Dz1TodecTargetCodecAttrDescr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TodecTargetCodecAttrDescrPresent_omit:
			// _U_prim_clone
			if (src->x.omit && (ret->x.omit = Dz1u32_clone(src->x.omit, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecTargetCodecAttrDescrPresent_def:
			// _U_prim_clone
			if (src->x.def && (ret->x.def = Dz1u32_clone(src->x.def, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecTargetCodecAttrDescrPresent_partial_byte:
			// _U_cst_clone
			if (src->x.partial_byte && (ret->x.partial_byte = Dz1TodecByteDescr_clone(src->x.partial_byte, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecTargetCodecAttrDescrPresent_alter_codec:
			// _U_prim_clone
			if (src->x.alter_codec && (ret->x.alter_codec = dz1_built_in_str_clone(src->x.alter_codec, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecTargetCodecAttrDescr *Dz1TodecTargetCodecAttrDescr_clone(Dz1TodecTargetCodecAttrDescr *src, Dz1Error *err)
{
	Dz1TodecTargetCodecAttrDescr *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TodecTargetCodecAttrDescr *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttrDescr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecAttrDescr_delAndSetNull, (void *)&ret);
		if (Dz1TodecTargetCodecAttrDescr_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecAttrDescr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecTargetCodecAttrDescr_purge(Dz1TodecTargetCodecAttrDescr *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TodecTargetCodecAttrDescrPresent_omit:
		Dz1u32_del(p->x.omit);
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_def:
		Dz1u32_del(p->x.def);
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_partial_byte:
		Dz1TodecByteDescr_del(p->x.partial_byte);
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_alter_codec:
		dz1_built_in_str_del(p->x.alter_codec);
		break;
	default:
		break;
	}
}

void Dz1TodecTargetCodecAttrDescr_del(Dz1TodecTargetCodecAttrDescr *p)
{
	if (!p) return;
	Dz1TodecTargetCodecAttrDescr_purge(p);
	Dz1Free(p);
}

void Dz1TodecTargetCodecAttrDescr_dump(Dz1TodecTargetCodecAttrDescr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TodecTargetCodecAttrDescrPresent_omit:
		Dz1Thread_printf(Dz1T("omit = ")); Dz1u32_dump(p->x.omit, tab); 
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_def:
		Dz1Thread_printf(Dz1T("def = ")); Dz1u32_dump(p->x.def, tab); 
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_partial_byte:
		Dz1Thread_printf(Dz1T("partial_byte = ")); Dz1TodecByteDescr_dump(p->x.partial_byte, tab); 
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_alter_codec:
		Dz1Thread_printf(Dz1T("alter_codec = ")); dz1_built_in_str_dump(p->x.alter_codec, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TodecTargetCodecAttrDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrUnion
Dz1TodecTargetCodecAttrUnion *Dz1TodecTargetCodecAttrUnion_new(Dz1TodecTargetCodecAttrDescr *pr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecAttrUnion *__internal_ret = (Dz1TodecTargetCodecAttrUnion *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttrUnion), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecAttrUnion_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->pr = pr;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecAttrUnion_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecTargetCodecAttrUnion_copy(Dz1TodecTargetCodecAttrUnion *dst, Dz1TodecTargetCodecAttrUnion *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->pr && (dst->pr = Dz1TodecTargetCodecAttrDescr_clone(src->pr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecTargetCodecAttrUnion *Dz1TodecTargetCodecAttrUnion_clone(Dz1TodecTargetCodecAttrUnion *src, Dz1Error *err)
{
	Dz1TodecTargetCodecAttrUnion *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecTargetCodecAttrUnion *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttrUnion), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecAttrUnion_delAndSetNull, (void *)&dst);
		if (Dz1TodecTargetCodecAttrUnion_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecAttrUnion_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecTargetCodecAttrUnion_purge(Dz1TodecTargetCodecAttrUnion *p)
{
	if (p == NULL) return;
	Dz1TodecTargetCodecAttrDescr_del(p->pr);
}

void Dz1TodecTargetCodecAttrUnion_del(Dz1TodecTargetCodecAttrUnion *p)
{
	if (p == NULL) return;
	Dz1TodecTargetCodecAttrUnion_purge(p);
	Dz1Free(p);
}

void Dz1TodecTargetCodecAttrUnion_dump(Dz1TodecTargetCodecAttrUnion *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("pr.")); Dz1TodecTargetCodecAttrDescr_dump(p->pr, tab); 
	}
}
// Dz1TodecTargetCodecAttrUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrArray
Dz1TodecTargetCodecAttrArray *Dz1TodecTargetCodecAttrArray_new(Dz1TodecTargetCodecAttrDescr *cnt, 
															   Dz1TodecTargetCodecAttrDescr *body, 
															   str_t postfix, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecAttrArray *__internal_ret = (Dz1TodecTargetCodecAttrArray *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttrArray), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecAttrArray_delAndSetNull, (void *)&__internal_ret);
		
		if (postfix && (__internal_ret->postfix = dz1_built_in_str_clone(postfix, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->cnt = cnt;
			__internal_ret->body = body;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecAttrArray_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecTargetCodecAttrArray_copy(Dz1TodecTargetCodecAttrArray *dst, Dz1TodecTargetCodecAttrArray *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->cnt && (dst->cnt = Dz1TodecTargetCodecAttrDescr_clone(src->cnt, errp)) == NULL) ERR_OUT(errp);
	else if (src->body && (dst->body = Dz1TodecTargetCodecAttrDescr_clone(src->body, errp)) == NULL) ERR_OUT(errp);
	else if (src->postfix && (dst->postfix = dz1_built_in_str_clone(src->postfix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecTargetCodecAttrArray *Dz1TodecTargetCodecAttrArray_clone(Dz1TodecTargetCodecAttrArray *src, Dz1Error *err)
{
	Dz1TodecTargetCodecAttrArray *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecTargetCodecAttrArray *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttrArray), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecAttrArray_delAndSetNull, (void *)&dst);
		if (Dz1TodecTargetCodecAttrArray_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecAttrArray_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecTargetCodecAttrArray_purge(Dz1TodecTargetCodecAttrArray *p)
{
	if (p == NULL) return;
	Dz1TodecTargetCodecAttrDescr_del(p->cnt);
	Dz1TodecTargetCodecAttrDescr_del(p->body);
	dz1_built_in_str_del(p->postfix);
}

void Dz1TodecTargetCodecAttrArray_del(Dz1TodecTargetCodecAttrArray *p)
{
	if (p == NULL) return;
	Dz1TodecTargetCodecAttrArray_purge(p);
	Dz1Free(p);
}

void Dz1TodecTargetCodecAttrArray_dump(Dz1TodecTargetCodecAttrArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cnt.")); Dz1TodecTargetCodecAttrDescr_dump(p->cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("body.")); Dz1TodecTargetCodecAttrDescr_dump(p->body, tab); 
		Dz1Thread_tprintf(tab, Dz1T("postfix = ")); dz1_built_in_str_dump(p->postfix, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecTargetCodecAttrArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrPresent
static struct Dz1TodecTargetCodecAttrPresentMapA
{
	str_t str;
	Dz1TodecTargetCodecAttrPresent v;
} Dz1TodecTargetCodecAttrPresentMapA[] =
{
	{ (char *)"st", Dz1TodecTargetCodecAttrPresent_st },
	{ (char *)"un", Dz1TodecTargetCodecAttrPresent_un },
	{ (char *)"ar", Dz1TodecTargetCodecAttrPresent_ar },
	{ NULL, Dz1TodecTargetCodecAttrPresent_max }
};

str_t Dz1TodecTargetCodecAttrPresentStrA(Dz1TodecTargetCodecAttrPresent v)
{
	struct Dz1TodecTargetCodecAttrPresentMapA *i = NULL;
	for (i = Dz1TodecTargetCodecAttrPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecTargetCodecAttrPresent Dz1TodecTargetCodecAttrPresentFromStrA(str_t str)
{
	struct Dz1TodecTargetCodecAttrPresentMapA *i = NULL;
	for (i = Dz1TodecTargetCodecAttrPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecTargetCodecAttrPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecTargetCodecAttrPresentMapW
{
	wstr_t str;
	Dz1TodecTargetCodecAttrPresent v;
} Dz1TodecTargetCodecAttrPresentMapW[] =
{
	{ (wchar_t *)L"st", Dz1TodecTargetCodecAttrPresent_st },
	{ (wchar_t *)L"un", Dz1TodecTargetCodecAttrPresent_un },
	{ (wchar_t *)L"ar", Dz1TodecTargetCodecAttrPresent_ar },
	{ NULL, Dz1TodecTargetCodecAttrPresent_max }
};

wstr_t Dz1TodecTargetCodecAttrPresentStrW(Dz1TodecTargetCodecAttrPresent v)
{
	struct Dz1TodecTargetCodecAttrPresentMapW *i = NULL;
	for (i = Dz1TodecTargetCodecAttrPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecTargetCodecAttrPresent Dz1TodecTargetCodecAttrPresentFromStrW(wstr_t str)
{
	struct Dz1TodecTargetCodecAttrPresentMapW *i = NULL;
	for (i = Dz1TodecTargetCodecAttrPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecTargetCodecAttrPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TodecTargetCodecAttrPresent *Dz1TodecTargetCodecAttrPresent_new(Dz1TodecTargetCodecAttrPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecAttrPresent *__internal_ret = (Dz1TodecTargetCodecAttrPresent *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttrPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TodecTargetCodecAttrPresent_dump(Dz1TodecTargetCodecAttrPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TodecTargetCodecAttrPresentStr(*v));
}
// Dz1TodecTargetCodecAttrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttr
Dz1TodecTargetCodecAttr *Dz1TodecTargetCodecAttr_new(Dz1TodecTargetCodecAttrPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecAttr *ret = (Dz1TodecTargetCodecAttr *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttr), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecAttr_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TodecTargetCodecAttrPresent_st:
			// _U_prim_clone
			if (ptr != NULL) ret->x.st = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecTargetCodecAttrPresent_un:
			// _U_cst_clone
			if (ptr != NULL) ret->x.un = (Dz1TodecTargetCodecAttrUnion *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecTargetCodecAttrPresent_ar:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ar = (Dz1TodecTargetCodecAttrArray *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecTargetCodecAttrPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecAttr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TodecTargetCodecAttr_copy(Dz1TodecTargetCodecAttr *ret, Dz1TodecTargetCodecAttr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TodecTargetCodecAttrPresent_st:
			// _U_prim_clone
			if (src->x.st && (ret->x.st = Dz1u32_clone(src->x.st, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecTargetCodecAttrPresent_un:
			// _U_cst_clone
			if (src->x.un && (ret->x.un = Dz1TodecTargetCodecAttrUnion_clone(src->x.un, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecTargetCodecAttrPresent_ar:
			// _U_cst_clone
			if (src->x.ar && (ret->x.ar = Dz1TodecTargetCodecAttrArray_clone(src->x.ar, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecTargetCodecAttr *Dz1TodecTargetCodecAttr_clone(Dz1TodecTargetCodecAttr *src, Dz1Error *err)
{
	Dz1TodecTargetCodecAttr *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TodecTargetCodecAttr *)Dz1Calloc(sizeof(Dz1TodecTargetCodecAttr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecAttr_delAndSetNull, (void *)&ret);
		if (Dz1TodecTargetCodecAttr_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecAttr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecTargetCodecAttr_purge(Dz1TodecTargetCodecAttr *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TodecTargetCodecAttrPresent_st:
		Dz1u32_del(p->x.st);
		break;
	case Dz1TodecTargetCodecAttrPresent_un:
		Dz1TodecTargetCodecAttrUnion_del(p->x.un);
		break;
	case Dz1TodecTargetCodecAttrPresent_ar:
		Dz1TodecTargetCodecAttrArray_del(p->x.ar);
		break;
	default:
		break;
	}
}

void Dz1TodecTargetCodecAttr_del(Dz1TodecTargetCodecAttr *p)
{
	if (!p) return;
	Dz1TodecTargetCodecAttr_purge(p);
	Dz1Free(p);
}

void Dz1TodecTargetCodecAttr_dump(Dz1TodecTargetCodecAttr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TodecTargetCodecAttrPresent_st:
		Dz1Thread_printf(Dz1T("st = ")); Dz1u32_dump(p->x.st, tab); 
		break;
	case Dz1TodecTargetCodecAttrPresent_un:
		Dz1Thread_printf(Dz1T("un = ")); Dz1TodecTargetCodecAttrUnion_dump(p->x.un, tab); 
		break;
	case Dz1TodecTargetCodecAttrPresent_ar:
		Dz1Thread_printf(Dz1T("ar = ")); Dz1TodecTargetCodecAttrArray_dump(p->x.ar, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TodecTargetCodecAttr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecStreamEntryPresent
static struct Dz1TodecStreamEntryPresentMapA
{
	str_t str;
	Dz1TodecStreamEntryPresent v;
} Dz1TodecStreamEntryPresentMapA[] =
{
	{ (char *)"bunch", Dz1TodecStreamEntryPresent_bunch },
	{ (char *)"conditional", Dz1TodecStreamEntryPresent_conditional },
	{ (char *)"omit", Dz1TodecStreamEntryPresent_omit },
	{ (char *)"single", Dz1TodecStreamEntryPresent_single },
	{ (char *)"pad", Dz1TodecStreamEntryPresent_pad },
	{ (char *)"value", Dz1TodecStreamEntryPresent_value },
	{ NULL, Dz1TodecStreamEntryPresent_max }
};

str_t Dz1TodecStreamEntryPresentStrA(Dz1TodecStreamEntryPresent v)
{
	struct Dz1TodecStreamEntryPresentMapA *i = NULL;
	for (i = Dz1TodecStreamEntryPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecStreamEntryPresent Dz1TodecStreamEntryPresentFromStrA(str_t str)
{
	struct Dz1TodecStreamEntryPresentMapA *i = NULL;
	for (i = Dz1TodecStreamEntryPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecStreamEntryPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecStreamEntryPresentMapW
{
	wstr_t str;
	Dz1TodecStreamEntryPresent v;
} Dz1TodecStreamEntryPresentMapW[] =
{
	{ (wchar_t *)L"bunch", Dz1TodecStreamEntryPresent_bunch },
	{ (wchar_t *)L"conditional", Dz1TodecStreamEntryPresent_conditional },
	{ (wchar_t *)L"omit", Dz1TodecStreamEntryPresent_omit },
	{ (wchar_t *)L"single", Dz1TodecStreamEntryPresent_single },
	{ (wchar_t *)L"pad", Dz1TodecStreamEntryPresent_pad },
	{ (wchar_t *)L"value", Dz1TodecStreamEntryPresent_value },
	{ NULL, Dz1TodecStreamEntryPresent_max }
};

wstr_t Dz1TodecStreamEntryPresentStrW(Dz1TodecStreamEntryPresent v)
{
	struct Dz1TodecStreamEntryPresentMapW *i = NULL;
	for (i = Dz1TodecStreamEntryPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecStreamEntryPresent Dz1TodecStreamEntryPresentFromStrW(wstr_t str)
{
	struct Dz1TodecStreamEntryPresentMapW *i = NULL;
	for (i = Dz1TodecStreamEntryPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecStreamEntryPresent_max;
}
#endif // UNIX_SYSTEM

Dz1TodecStreamEntryPresent *Dz1TodecStreamEntryPresent_new(Dz1TodecStreamEntryPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecStreamEntryPresent *__internal_ret = (Dz1TodecStreamEntryPresent *)Dz1Calloc(sizeof(Dz1TodecStreamEntryPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TodecStreamEntryPresent_dump(Dz1TodecStreamEntryPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TodecStreamEntryPresentStr(*v));
}
// Dz1TodecStreamEntryPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecStreamEntry
Dz1TodecStreamEntry *Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecStreamEntry *ret = (Dz1TodecStreamEntry *)Dz1Calloc(sizeof(Dz1TodecStreamEntry), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecStreamEntry_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1TodecStreamEntryPresent_bunch:
			// _U_cst_clone
			if (ptr != NULL) ret->x.bunch = (Dz1TodecBunchOfSource *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecStreamEntryPresent_conditional:
			// _U_cst_clone
			if (ptr != NULL) ret->x.conditional = (Dz1TodecConditionalSource *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecStreamEntryPresent_omit:
			// _U_prim_clone
			if (ptr && (ret->x.omit = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecStreamEntryPresent_single:
			// _U_cst_clone
			if (ptr != NULL) ret->x.single = (Dz1TodecSingleSource *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecStreamEntryPresent_pad:
			// _U_prim_clone
			if (ptr != NULL) ret->x.pad = *(u16_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecStreamEntryPresent_value:
			// _U_imp_clone
			if (ptr != NULL) ret->x.value = (Dz1ElasticBuf *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecStreamEntryPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecStreamEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TodecStreamEntry_copy(Dz1TodecStreamEntry *ret, Dz1TodecStreamEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1TodecStreamEntryPresent_bunch:
			// _U_cst_clone
			if (src->x.bunch && (ret->x.bunch = Dz1TodecBunchOfSource_clone(src->x.bunch, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecStreamEntryPresent_conditional:
			// _U_cst_clone
			if (src->x.conditional && (ret->x.conditional = Dz1TodecConditionalSource_clone(src->x.conditional, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecStreamEntryPresent_omit:
			// _U_prim_clone
			if (src->x.omit && (ret->x.omit = dz1_built_in_str_clone(src->x.omit, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecStreamEntryPresent_single:
			// _U_cst_clone
			if (src->x.single && (ret->x.single = Dz1TodecSingleSource_clone(src->x.single, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1TodecStreamEntryPresent_pad:
			// _U_prim_clone
			ret->x.pad = src->x.pad;
			ERR_CLEAR(errp);
			break;
		case Dz1TodecStreamEntryPresent_value:
			// _U_imp_clone
			if (src->x.value && (ret->x.value = Dz1ElasticBuf_clone(src->x.value, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecStreamEntry *Dz1TodecStreamEntry_clone(Dz1TodecStreamEntry *src, Dz1Error *err)
{
	Dz1TodecStreamEntry *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1TodecStreamEntry *)Dz1Calloc(sizeof(Dz1TodecStreamEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecStreamEntry_delAndSetNull, (void *)&ret);
		if (Dz1TodecStreamEntry_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecStreamEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecStreamEntry_purge(Dz1TodecStreamEntry *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1TodecStreamEntryPresent_bunch:
		Dz1TodecBunchOfSource_del(p->x.bunch);
		break;
	case Dz1TodecStreamEntryPresent_conditional:
		Dz1TodecConditionalSource_del(p->x.conditional);
		break;
	case Dz1TodecStreamEntryPresent_omit:
		dz1_built_in_str_del(p->x.omit);
		break;
	case Dz1TodecStreamEntryPresent_single:
		Dz1TodecSingleSource_del(p->x.single);
		break;
	case Dz1TodecStreamEntryPresent_pad:
		break;
	case Dz1TodecStreamEntryPresent_value:
		Dz1ElasticBuf_del(p->x.value);
		break;
	default:
		break;
	}
}

void Dz1TodecStreamEntry_del(Dz1TodecStreamEntry *p)
{
	if (!p) return;
	Dz1TodecStreamEntry_purge(p);
	Dz1Free(p);
}

void Dz1TodecStreamEntry_dump(Dz1TodecStreamEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1TodecStreamEntryPresent_bunch:
		Dz1Thread_printf(Dz1T("bunch = ")); Dz1TodecBunchOfSource_dump(p->x.bunch, tab); 
		break;
	case Dz1TodecStreamEntryPresent_conditional:
		Dz1Thread_printf(Dz1T("conditional = ")); Dz1TodecConditionalSource_dump(p->x.conditional, tab); 
		break;
	case Dz1TodecStreamEntryPresent_omit:
		Dz1Thread_printf(Dz1T("omit = ")); dz1_built_in_str_dump(p->x.omit, tab); 
		break;
	case Dz1TodecStreamEntryPresent_single:
		Dz1Thread_printf(Dz1T("single = ")); Dz1TodecSingleSource_dump(p->x.single, tab); 
		break;
	case Dz1TodecStreamEntryPresent_pad:
		Dz1Thread_printf(Dz1T("pad = ")); Dz1u16_dump(&p->x.pad, tab); 
		break;
	case Dz1TodecStreamEntryPresent_value:
		Dz1Thread_printf(Dz1T("value = ")); Dz1ElasticBuf_dump(p->x.value, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1TodecStreamEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecStreamList
static Dz1Error Dz1TodecStreamList_add(Dz1TodecStreamList *p, Dz1TodecStreamEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TodecStreamListMkArrArg
{
	Dz1TodecStreamEntry **arr;
	unsigned int idx;
} Dz1TodecStreamListMkArrArg;

static Dz1Error _Dz1TodecStreamList_get_array(void *ptr, Dz1TodecStreamEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecStreamListMkArrArg *arg = (Dz1TodecStreamListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TodecStreamEntry **Dz1TodecStreamList_get_array(Dz1TodecStreamList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TodecStreamEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TodecStreamEntry **)Dz1Calloc(sizeof(Dz1TodecStreamEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecStreamListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TodecStreamList_get_array, (void *)&arg);
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

static Dz1Error Dz1TodecStreamList_travelForward(Dz1TodecStreamList *p, Dz1Error (*func)(void *ptr, Dz1TodecStreamEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TodecStreamList_travelBackward(Dz1TodecStreamList *p, Dz1Error (*func)(void *ptr, Dz1TodecStreamEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TodecStreamList_count(Dz1TodecStreamList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TodecStreamList *Dz1TodecStreamList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecStreamList *ret = (Dz1TodecStreamList *)Dz1Calloc(sizeof(Dz1TodecStreamList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecStreamList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1TodecStreamEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TodecStreamList_count;
			ret->travel = Dz1TodecStreamList_travelForward;
			ret->travelForward = Dz1TodecStreamList_travelForward;
			ret->travelBackward = Dz1TodecStreamList_travelBackward;
			ret->get_array = Dz1TodecStreamList_get_array;
			ret->add = Dz1TodecStreamList_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecStreamList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TodecStreamList_clone(void *ptr, Dz1TodecStreamEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecStreamList *p = (Dz1TodecStreamList *)ptr;
	Dz1TodecStreamEntry *cloned = Dz1TodecStreamEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TodecStreamList *Dz1TodecStreamList_clone(Dz1TodecStreamList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecStreamList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TodecStreamList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecStreamList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TodecStreamList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecStreamList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecStreamList_purge(Dz1TodecStreamList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TodecStreamList_del(Dz1TodecStreamList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TodecStreamList_dump(void *ptr, Dz1TodecStreamEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TodecStreamEntry_dump(p, tab);
	return err;
}

void Dz1TodecStreamList_dump(Dz1TodecStreamList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TodecStreamList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecStreamList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecMode
static struct Dz1TodecTargetCodecModeMapA
{
	str_t str;
	Dz1TodecTargetCodecMode v;
} Dz1TodecTargetCodecModeMapA[] =
{
	{ (char *)"public", Dz1TodecTargetCodecMode_public },
	{ (char *)"header", Dz1TodecTargetCodecMode_header },
	{ (char *)"private", Dz1TodecTargetCodecMode_private },
	{ NULL, Dz1TodecTargetCodecMode_max }
};

str_t Dz1TodecTargetCodecModeStrA(Dz1TodecTargetCodecMode v)
{
	struct Dz1TodecTargetCodecModeMapA *i = NULL;
	for (i = Dz1TodecTargetCodecModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecTargetCodecMode Dz1TodecTargetCodecModeFromStrA(str_t str)
{
	struct Dz1TodecTargetCodecModeMapA *i = NULL;
	for (i = Dz1TodecTargetCodecModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecTargetCodecMode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TodecTargetCodecModeMapW
{
	wstr_t str;
	Dz1TodecTargetCodecMode v;
} Dz1TodecTargetCodecModeMapW[] =
{
	{ (wchar_t *)L"public", Dz1TodecTargetCodecMode_public },
	{ (wchar_t *)L"header", Dz1TodecTargetCodecMode_header },
	{ (wchar_t *)L"private", Dz1TodecTargetCodecMode_private },
	{ NULL, Dz1TodecTargetCodecMode_max }
};

wstr_t Dz1TodecTargetCodecModeStrW(Dz1TodecTargetCodecMode v)
{
	struct Dz1TodecTargetCodecModeMapW *i = NULL;
	for (i = Dz1TodecTargetCodecModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TodecTargetCodecMode Dz1TodecTargetCodecModeFromStrW(wstr_t str)
{
	struct Dz1TodecTargetCodecModeMapW *i = NULL;
	for (i = Dz1TodecTargetCodecModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TodecTargetCodecMode_max;
}
#endif // UNIX_SYSTEM

Dz1TodecTargetCodecMode *Dz1TodecTargetCodecMode_new(Dz1TodecTargetCodecMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecMode *__internal_ret = (Dz1TodecTargetCodecMode *)Dz1Calloc(sizeof(Dz1TodecTargetCodecMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1TodecTargetCodecMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecEntry
Dz1TodecTargetCodecEntry *Dz1TodecTargetCodecEntry_new(str_t alter_codec, 
													   Dz1TodecTargetCodecMode mode, 
													   Dz1TodecTargetCodecAttr *attr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecEntry *__internal_ret = (Dz1TodecTargetCodecEntry *)Dz1Calloc(sizeof(Dz1TodecTargetCodecEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (alter_codec && (__internal_ret->alter_codec = dz1_built_in_str_clone(alter_codec, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->seq = Dz1TodecStreamList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->mode = mode;
			__internal_ret->attr = attr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecTargetCodecEntry_copy(Dz1TodecTargetCodecEntry *dst, Dz1TodecTargetCodecEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->alter_codec && (dst->alter_codec = dz1_built_in_str_clone(src->alter_codec, errp)) == NULL) ERR_OUT(errp);
	else if (src->attr && (dst->attr = Dz1TodecTargetCodecAttr_clone(src->attr, errp)) == NULL) ERR_OUT(errp);
	else if (src->seq && (dst->seq = Dz1TodecStreamList_clone(src->seq, errp)) == NULL) ERR_OUT(errp);
	else if (src->postfix && (dst->postfix = dz1_built_in_str_clone(src->postfix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->mode = src->mode;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecTargetCodecEntry *Dz1TodecTargetCodecEntry_clone(Dz1TodecTargetCodecEntry *src, Dz1Error *err)
{
	Dz1TodecTargetCodecEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecTargetCodecEntry *)Dz1Calloc(sizeof(Dz1TodecTargetCodecEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecEntry_delAndSetNull, (void *)&dst);
		if (Dz1TodecTargetCodecEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecTargetCodecEntry_purge(Dz1TodecTargetCodecEntry *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->alter_codec);
	Dz1TodecTargetCodecAttr_del(p->attr);
	Dz1TodecStreamList_del(p->seq);
	dz1_built_in_str_del(p->postfix);
}

void Dz1TodecTargetCodecEntry_del(Dz1TodecTargetCodecEntry *p)
{
	if (p == NULL) return;
	Dz1TodecTargetCodecEntry_purge(p);
	Dz1Free(p);
}

void Dz1TodecTargetCodecEntry_dump(Dz1TodecTargetCodecEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("alter_codec = ")); dz1_built_in_str_dump(p->alter_codec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("mode = %s(%d)\n"), Dz1TodecTargetCodecModeStr(p->mode), p->mode);
		Dz1Thread_tprintf(tab, Dz1T("attr.")); Dz1TodecTargetCodecAttr_dump(p->attr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1TodecStreamList_dump(p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("postfix = ")); dz1_built_in_str_dump(p->postfix, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TodecTargetCodecEntry_cmp(Dz1TodecTargetCodecEntry *a, Dz1TodecTargetCodecEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->alter_codec == NULL && b->alter_codec == NULL) ret = 0;
	else if (a->alter_codec == NULL /*&& b->alter_codec != NULL*/) ret = -1;
	else if (/*a->alter_codec != NULL &&*/ b->alter_codec == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->alter_codec, b->alter_codec)) != 0) { }
	return ret;
}
// Dz1TodecTargetCodecEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecList
static Dz1Error Dz1TodecTargetCodecList_add(Dz1TodecTargetCodecList *p, Dz1TodecTargetCodecEntry *data)
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

static bool_t Dz1TodecTargetCodecList_remove(Dz1TodecTargetCodecList *p, Dz1TodecTargetCodecEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TodecTargetCodecEntry *Dz1TodecTargetCodecList_extract(Dz1TodecTargetCodecList *p, Dz1TodecTargetCodecEntry *key)
{
	return (Dz1TodecTargetCodecEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TodecTargetCodecListMkArrArg
{
	Dz1TodecTargetCodecEntry **arr;
	unsigned int idx;
} Dz1TodecTargetCodecListMkArrArg;

static Dz1Error _Dz1TodecTargetCodecList_get_array(void *ptr, Dz1TodecTargetCodecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecTargetCodecListMkArrArg *arg = (Dz1TodecTargetCodecListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TodecTargetCodecEntry **Dz1TodecTargetCodecList_get_array(Dz1TodecTargetCodecList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TodecTargetCodecEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TodecTargetCodecEntry **)Dz1Calloc(sizeof(Dz1TodecTargetCodecEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecTargetCodecListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TodecTargetCodecList_get_array, (void *)&arg);
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

static Dz1Error Dz1TodecTargetCodecList_travelForward(Dz1TodecTargetCodecList *p, Dz1Error (*func)(void *ptr, Dz1TodecTargetCodecEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TodecTargetCodecList_travelBackward(Dz1TodecTargetCodecList *p, Dz1Error (*func)(void *ptr, Dz1TodecTargetCodecEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TodecTargetCodecEntry *Dz1TodecTargetCodecList_find(Dz1TodecTargetCodecList *p, Dz1TodecTargetCodecEntry *key)
{
	return (Dz1TodecTargetCodecEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TodecTargetCodecList_count(Dz1TodecTargetCodecList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TodecTargetCodecList *Dz1TodecTargetCodecList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecList *ret = (Dz1TodecTargetCodecList *)Dz1Calloc(sizeof(Dz1TodecTargetCodecList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TodecTargetCodecEntry_cmp,
				(Dz1DelFunc)Dz1TodecTargetCodecEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TodecTargetCodecList_count;
			ret->travel = Dz1TodecTargetCodecList_travelForward;
			ret->travelForward = Dz1TodecTargetCodecList_travelForward;
			ret->travelBackward = Dz1TodecTargetCodecList_travelBackward;
			ret->get_array = Dz1TodecTargetCodecList_get_array;
			ret->add = Dz1TodecTargetCodecList_add;
			ret->remove = Dz1TodecTargetCodecList_remove;
			ret->find = Dz1TodecTargetCodecList_find;
			ret->extract = Dz1TodecTargetCodecList_extract;
			ret->cmp = Dz1TodecTargetCodecEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TodecTargetCodecList_clone(void *ptr, Dz1TodecTargetCodecEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecTargetCodecList *p = (Dz1TodecTargetCodecList *)ptr;
	Dz1TodecTargetCodecEntry *cloned = Dz1TodecTargetCodecEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TodecTargetCodecList *Dz1TodecTargetCodecList_clone(Dz1TodecTargetCodecList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetCodecList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TodecTargetCodecList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TodecTargetCodecList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetCodecList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecTargetCodecList_purge(Dz1TodecTargetCodecList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TodecTargetCodecList_del(Dz1TodecTargetCodecList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TodecTargetCodecList_dump(void *ptr, Dz1TodecTargetCodecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TodecTargetCodecEntry_dump(p, tab);
	return err;
}

void Dz1TodecTargetCodecList_dump(Dz1TodecTargetCodecList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TodecTargetCodecList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecTargetCodecList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTarget
Dz1TodecTarget *Dz1TodecTarget_new(str_t src_name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTarget *__internal_ret = (Dz1TodecTarget *)Dz1Calloc(sizeof(Dz1TodecTarget), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecTarget_delAndSetNull, (void *)&__internal_ret);
		
		if (src_name && (__internal_ret->src_name = dz1_built_in_str_clone(src_name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->codecs = Dz1TodecTargetCodecList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTarget_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecTarget_copy(Dz1TodecTarget *dst, Dz1TodecTarget *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->src_name && (dst->src_name = dz1_built_in_str_clone(src->src_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->codecs && (dst->codecs = Dz1TodecTargetCodecList_clone(src->codecs, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecTarget *Dz1TodecTarget_clone(Dz1TodecTarget *src, Dz1Error *err)
{
	Dz1TodecTarget *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecTarget *)Dz1Calloc(sizeof(Dz1TodecTarget), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecTarget_delAndSetNull, (void *)&dst);
		if (Dz1TodecTarget_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTarget_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecTarget_purge(Dz1TodecTarget *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->src_name);
	Dz1TodecTargetCodecList_del(p->codecs);
}

void Dz1TodecTarget_del(Dz1TodecTarget *p)
{
	if (p == NULL) return;
	Dz1TodecTarget_purge(p);
	Dz1Free(p);
}

void Dz1TodecTarget_dump(Dz1TodecTarget *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("src_name = ")); dz1_built_in_str_dump(p->src_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("codecs = ")); Dz1TodecTargetCodecList_dump(p->codecs, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1TodecTarget_cmp(Dz1TodecTarget *a, Dz1TodecTarget *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->src_name == NULL && b->src_name == NULL) ret = 0;
	else if (a->src_name == NULL /*&& b->src_name != NULL*/) ret = -1;
	else if (/*a->src_name != NULL &&*/ b->src_name == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->src_name, b->src_name)) != 0) { }
	return ret;
}
// Dz1TodecTarget
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetList
static Dz1Error Dz1TodecTargetList_add(Dz1TodecTargetList *p, Dz1TodecTarget *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TodecTargetListMkArrArg
{
	Dz1TodecTarget **arr;
	unsigned int idx;
} Dz1TodecTargetListMkArrArg;

static Dz1Error _Dz1TodecTargetList_get_array(void *ptr, Dz1TodecTarget *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecTargetListMkArrArg *arg = (Dz1TodecTargetListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TodecTarget **Dz1TodecTargetList_get_array(Dz1TodecTargetList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TodecTarget **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TodecTarget **)Dz1Calloc(sizeof(Dz1TodecTarget *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecTargetListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TodecTargetList_get_array, (void *)&arg);
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

static Dz1Error Dz1TodecTargetList_travelForward(Dz1TodecTargetList *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TodecTargetList_travelBackward(Dz1TodecTargetList *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TodecTargetList_count(Dz1TodecTargetList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TodecTargetList *Dz1TodecTargetList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetList *ret = (Dz1TodecTargetList *)Dz1Calloc(sizeof(Dz1TodecTargetList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTargetList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1TodecTarget_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TodecTargetList_count;
			ret->travel = Dz1TodecTargetList_travelForward;
			ret->travelForward = Dz1TodecTargetList_travelForward;
			ret->travelBackward = Dz1TodecTargetList_travelBackward;
			ret->get_array = Dz1TodecTargetList_get_array;
			ret->add = Dz1TodecTargetList_add;
			ret->cmp = Dz1TodecTarget_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TodecTargetList_clone(void *ptr, Dz1TodecTarget *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecTargetList *p = (Dz1TodecTargetList *)ptr;
	Dz1TodecTarget *cloned = Dz1TodecTarget_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TodecTargetList *Dz1TodecTargetList_clone(Dz1TodecTargetList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TodecTargetList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTargetList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TodecTargetList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecTargetList_purge(Dz1TodecTargetList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TodecTargetList_del(Dz1TodecTargetList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TodecTargetList_dump(void *ptr, Dz1TodecTarget *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TodecTarget_dump(p, tab);
	return err;
}

void Dz1TodecTargetList_dump(Dz1TodecTargetList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TodecTargetList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecTargetList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetTable
static Dz1Error Dz1TodecTargetTable_add(Dz1TodecTargetTable *p, Dz1TodecTarget *data)
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

static bool_t Dz1TodecTargetTable_remove(Dz1TodecTargetTable *p, Dz1TodecTarget *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TodecTarget *Dz1TodecTargetTable_extract(Dz1TodecTargetTable *p, Dz1TodecTarget *key)
{
	return (Dz1TodecTarget *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TodecTargetTableMkArrArg
{
	Dz1TodecTarget **arr;
	unsigned int idx;
} Dz1TodecTargetTableMkArrArg;

static Dz1Error _Dz1TodecTargetTable_get_array(void *ptr, Dz1TodecTarget *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecTargetTableMkArrArg *arg = (Dz1TodecTargetTableMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TodecTarget **Dz1TodecTargetTable_get_array(Dz1TodecTargetTable *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TodecTarget **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TodecTarget **)Dz1Calloc(sizeof(Dz1TodecTarget *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecTargetTableMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TodecTargetTable_get_array, (void *)&arg);
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

static Dz1Error Dz1TodecTargetTable_travelForward(Dz1TodecTargetTable *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TodecTargetTable_travelBackward(Dz1TodecTargetTable *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TodecTarget *Dz1TodecTargetTable_find(Dz1TodecTargetTable *p, Dz1TodecTarget *key)
{
	return (Dz1TodecTarget *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TodecTargetTable_count(Dz1TodecTargetTable *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TodecTargetTable *Dz1TodecTargetTable_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetTable *ret = (Dz1TodecTargetTable *)Dz1Calloc(sizeof(Dz1TodecTargetTable), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTargetTable_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TodecTarget_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TodecTargetTable_count;
			ret->travel = Dz1TodecTargetTable_travelForward;
			ret->travelForward = Dz1TodecTargetTable_travelForward;
			ret->travelBackward = Dz1TodecTargetTable_travelBackward;
			ret->get_array = Dz1TodecTargetTable_get_array;
			ret->add = Dz1TodecTargetTable_add;
			ret->remove = Dz1TodecTargetTable_remove;
			ret->find = Dz1TodecTargetTable_find;
			ret->extract = Dz1TodecTargetTable_extract;
			ret->cmp = Dz1TodecTarget_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TodecTargetTable_clone(void *ptr, Dz1TodecTarget *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecTargetTable *p = (Dz1TodecTargetTable *)ptr;
	Dz1TodecTarget *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TodecTargetTable *Dz1TodecTargetTable_clone(Dz1TodecTargetTable *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecTargetTable *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TodecTargetTable_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTargetTable_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TodecTargetTable_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecTargetTable_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecTargetTable_purge(Dz1TodecTargetTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TodecTargetTable_del(Dz1TodecTargetTable *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TodecTargetTable_dump(void *ptr, Dz1TodecTarget *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TodecTarget_dump(p, tab);
	return err;
}

void Dz1TodecTargetTable_dump(Dz1TodecTargetTable *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TodecTargetTable_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecTargetTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecIncEntry
Dz1TodecIncEntry *Dz1TodecIncEntry_new(str_t name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecIncEntry *__internal_ret = (Dz1TodecIncEntry *)Dz1Calloc(sizeof(Dz1TodecIncEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecIncEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = dz1_built_in_str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecIncEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecIncEntry_copy(Dz1TodecIncEntry *dst, Dz1TodecIncEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = dz1_built_in_str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecIncEntry *Dz1TodecIncEntry_clone(Dz1TodecIncEntry *src, Dz1Error *err)
{
	Dz1TodecIncEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecIncEntry *)Dz1Calloc(sizeof(Dz1TodecIncEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecIncEntry_delAndSetNull, (void *)&dst);
		if (Dz1TodecIncEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecIncEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecIncEntry_purge(Dz1TodecIncEntry *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->name);
}

void Dz1TodecIncEntry_del(Dz1TodecIncEntry *p)
{
	if (p == NULL) return;
	Dz1TodecIncEntry_purge(p);
	Dz1Free(p);
}

void Dz1TodecIncEntry_dump(Dz1TodecIncEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("name = ")); dz1_built_in_str_dump(p->name, tab); 
	}
}
int Dz1TodecIncEntry_cmp(Dz1TodecIncEntry *a, Dz1TodecIncEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// Dz1TodecIncEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecIncIndex
static Dz1Error Dz1TodecIncIndex_add(Dz1TodecIncIndex *p, Dz1TodecIncEntry *data)
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

static bool_t Dz1TodecIncIndex_remove(Dz1TodecIncIndex *p, Dz1TodecIncEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1TodecIncEntry *Dz1TodecIncIndex_extract(Dz1TodecIncIndex *p, Dz1TodecIncEntry *key)
{
	return (Dz1TodecIncEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TodecIncIndexMkArrArg
{
	Dz1TodecIncEntry **arr;
	unsigned int idx;
} Dz1TodecIncIndexMkArrArg;

static Dz1Error _Dz1TodecIncIndex_get_array(void *ptr, Dz1TodecIncEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecIncIndexMkArrArg *arg = (Dz1TodecIncIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TodecIncEntry **Dz1TodecIncIndex_get_array(Dz1TodecIncIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TodecIncEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TodecIncEntry **)Dz1Calloc(sizeof(Dz1TodecIncEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecIncIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TodecIncIndex_get_array, (void *)&arg);
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

static Dz1Error Dz1TodecIncIndex_travelForward(Dz1TodecIncIndex *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TodecIncIndex_travelBackward(Dz1TodecIncIndex *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TodecIncEntry *Dz1TodecIncIndex_find(Dz1TodecIncIndex *p, Dz1TodecIncEntry *key)
{
	return (Dz1TodecIncEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TodecIncIndex_count(Dz1TodecIncIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TodecIncIndex *Dz1TodecIncIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecIncIndex *ret = (Dz1TodecIncIndex *)Dz1Calloc(sizeof(Dz1TodecIncIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecIncIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TodecIncEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TodecIncIndex_count;
			ret->travel = Dz1TodecIncIndex_travelForward;
			ret->travelForward = Dz1TodecIncIndex_travelForward;
			ret->travelBackward = Dz1TodecIncIndex_travelBackward;
			ret->get_array = Dz1TodecIncIndex_get_array;
			ret->add = Dz1TodecIncIndex_add;
			ret->remove = Dz1TodecIncIndex_remove;
			ret->find = Dz1TodecIncIndex_find;
			ret->extract = Dz1TodecIncIndex_extract;
			ret->cmp = Dz1TodecIncEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecIncIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TodecIncIndex_clone(void *ptr, Dz1TodecIncEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecIncIndex *p = (Dz1TodecIncIndex *)ptr;
	Dz1TodecIncEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TodecIncIndex *Dz1TodecIncIndex_clone(Dz1TodecIncIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecIncIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TodecIncIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecIncIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TodecIncIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecIncIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecIncIndex_purge(Dz1TodecIncIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1TodecIncIndex_del(Dz1TodecIncIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TodecIncIndex_dump(void *ptr, Dz1TodecIncEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TodecIncEntry_dump(p, tab);
	return err;
}

void Dz1TodecIncIndex_dump(Dz1TodecIncIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TodecIncIndex_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecIncIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecIncList
static Dz1Error Dz1TodecIncList_add(Dz1TodecIncList *p, Dz1TodecIncEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1TodecIncListMkArrArg
{
	Dz1TodecIncEntry **arr;
	unsigned int idx;
} Dz1TodecIncListMkArrArg;

static Dz1Error _Dz1TodecIncList_get_array(void *ptr, Dz1TodecIncEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecIncListMkArrArg *arg = (Dz1TodecIncListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TodecIncEntry **Dz1TodecIncList_get_array(Dz1TodecIncList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TodecIncEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TodecIncEntry **)Dz1Calloc(sizeof(Dz1TodecIncEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecIncListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TodecIncList_get_array, (void *)&arg);
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

static Dz1Error Dz1TodecIncList_travelForward(Dz1TodecIncList *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1TodecIncList_travelBackward(Dz1TodecIncList *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1TodecIncList_count(Dz1TodecIncList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1TodecIncList *Dz1TodecIncList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecIncList *ret = (Dz1TodecIncList *)Dz1Calloc(sizeof(Dz1TodecIncList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecIncList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1TodecIncEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1TodecIncList_count;
			ret->travel = Dz1TodecIncList_travelForward;
			ret->travelForward = Dz1TodecIncList_travelForward;
			ret->travelBackward = Dz1TodecIncList_travelBackward;
			ret->get_array = Dz1TodecIncList_get_array;
			ret->add = Dz1TodecIncList_add;
			ret->cmp = Dz1TodecIncEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecIncList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TodecIncList_clone(void *ptr, Dz1TodecIncEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TodecIncList *p = (Dz1TodecIncList *)ptr;
	Dz1TodecIncEntry *cloned = Dz1TodecIncEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TodecIncList *Dz1TodecIncList_clone(Dz1TodecIncList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecIncList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TodecIncList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecIncList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1TodecIncList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecIncList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TodecIncList_purge(Dz1TodecIncList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1TodecIncList_del(Dz1TodecIncList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TodecIncList_dump(void *ptr, Dz1TodecIncEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1TodecIncEntry_dump(p, tab);
	return err;
}

void Dz1TodecIncList_dump(Dz1TodecIncList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1TodecIncList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecIncList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecInclude
Dz1TodecInclude *Dz1TodecInclude_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecInclude *__internal_ret = (Dz1TodecInclude *)Dz1Calloc(sizeof(Dz1TodecInclude), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecInclude_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->ref_idx = Dz1TodecIncIndex_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->seq = Dz1TodecIncList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecInclude_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TodecInclude_copy(Dz1TodecInclude *dst, Dz1TodecInclude *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ref_idx && (dst->ref_idx = Dz1TodecIncIndex_clone(src->ref_idx, errp)) == NULL) ERR_OUT(errp);
	else if (src->seq && (dst->seq = Dz1TodecIncList_clone(src->seq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TodecInclude *Dz1TodecInclude_clone(Dz1TodecInclude *src, Dz1Error *err)
{
	Dz1TodecInclude *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TodecInclude *)Dz1Calloc(sizeof(Dz1TodecInclude), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TodecInclude_delAndSetNull, (void *)&dst);
		if (Dz1TodecInclude_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecInclude_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TodecInclude_purge(Dz1TodecInclude *p)
{
	if (p == NULL) return;
	Dz1TodecIncIndex_del(p->ref_idx);
	Dz1TodecIncList_del(p->seq);
}

void Dz1TodecInclude_del(Dz1TodecInclude *p)
{
	if (p == NULL) return;
	Dz1TodecInclude_purge(p);
	Dz1Free(p);
}

void Dz1TodecInclude_dump(Dz1TodecInclude *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ref_idx = ")); Dz1TodecIncIndex_dump(p->ref_idx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1TodecIncList_dump(p->seq, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecInclude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Todec
bool_t Dz1Todec_copy(Dz1Todec *dst, Dz1Todec *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->mod_name && (dst->mod_name = dz1_built_in_str_clone(src->mod_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->incl && (dst->incl = Dz1TodecInclude_clone(src->incl, errp)) == NULL) ERR_OUT(errp);
	else if (src->list && (dst->list = Dz1TodecTargetList_clone(src->list, errp)) == NULL) ERR_OUT(errp);
	else if (src->idx && (dst->idx = Dz1TodecTargetTable_clone(src->idx, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1Todec *Dz1Todec_clone(Dz1Todec *src, Dz1Error *err)
{
	Dz1Todec *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1Todec *)Dz1Calloc(sizeof(Dz1Todec), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Todec_delAndSetNull, (void *)&dst);
		if (Dz1Todec_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Todec_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1Todec_purge(Dz1Todec *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->mod_name);
	Dz1TodecInclude_del(p->incl);
	Dz1TodecTargetList_del(p->list);
	Dz1TodecTargetTable_del(p->idx);
}

void Dz1Todec_del(Dz1Todec *p)
{
	if (p == NULL) return;
	Dz1Todec_purge(p);
	Dz1Free(p);
}

void Dz1Todec_dump(Dz1Todec *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("mod_name = ")); dz1_built_in_str_dump(p->mod_name, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("incl = ")); Dz1TodecInclude_dump(p->incl, tab); 
		Dz1Thread_tprintf(tab, Dz1T("list = ")); Dz1TodecTargetList_dump(p->list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1Todec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecPubArg
Dz1TodecPubArg *Dz1TodecPubArg_new(str_t mod_inc_path, 
								   str_t dst_path_c, 
								   str_t dst_path_h, 
								   bool_t output_src, 
								   bool_t output_hdr, 
								   u32_t flags, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TodecPubArg *__internal_ret = (Dz1TodecPubArg *)Dz1Calloc(sizeof(Dz1TodecPubArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TodecPubArg_delAndSetNull, (void *)&__internal_ret);
		
		if (mod_inc_path && (__internal_ret->mod_inc_path = dz1_built_in_str_clone(mod_inc_path, errp)) == NULL) ERR_OUT(errp);
		else if (dst_path_c && (__internal_ret->dst_path_c = dz1_built_in_str_clone(dst_path_c, errp)) == NULL) ERR_OUT(errp);
		else if (dst_path_h && (__internal_ret->dst_path_h = dz1_built_in_str_clone(dst_path_h, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->output_src = output_src;
			__internal_ret->output_hdr = output_hdr;
			__internal_ret->flags = flags;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TodecPubArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TodecPubArg_purge(Dz1TodecPubArg *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->mod_inc_path);
	dz1_built_in_str_del(p->dst_path_c);
	dz1_built_in_str_del(p->dst_path_h);
}

void Dz1TodecPubArg_del(Dz1TodecPubArg *p)
{
	if (p == NULL) return;
	Dz1TodecPubArg_purge(p);
	Dz1Free(p);
}

void Dz1TodecPubArg_dump(Dz1TodecPubArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("mod_inc_path = ")); dz1_built_in_str_dump(p->mod_inc_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dst_path_c = ")); dz1_built_in_str_dump(p->dst_path_c, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dst_path_h = ")); dz1_built_in_str_dump(p->dst_path_h, tab); 
		Dz1Thread_tprintf(tab, Dz1T("output_src = ")); Dz1Bool_dump(&p->output_src, tab); 
		Dz1Thread_tprintf(tab, Dz1T("output_hdr = ")); Dz1Bool_dump(&p->output_hdr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("flags = ")); Dz1u32_dump(&p->flags, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TodecPubArg
////////////////////////////////////////////////////////////////////////////////

