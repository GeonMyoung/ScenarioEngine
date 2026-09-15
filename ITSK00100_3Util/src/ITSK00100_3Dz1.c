////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include <ITSK00100_3Dz1.h>

#include <dz1_gasn_support.h>

////////////////////////////////////////////////////////////////////////////////
// Dz1DDateTime_00100
Dz1DDateTime_00100* Dz1DDateTime_00100_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1DDateTime_00100* __internal_ret = (Dz1DDateTime_00100*)Dz1Calloc(sizeof(Dz1DDateTime_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1DDateTime_00100_delAndSetNull, (void*)&__internal_ret);

		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1DDateTime_00100_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1DDateTime_00100_copy(Dz1DDateTime_00100* dst, Dz1DDateTime_00100* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->year && (dst->year = Dz1DYear_00100_clone(src->year, errp)) == NULL) ERR_OUT(errp);
	else if (src->month && (dst->month = Dz1DMonth_00100_clone(src->month, errp)) == NULL) ERR_OUT(errp);
	else if (src->day && (dst->day = Dz1DDay_00100_clone(src->day, errp)) == NULL) ERR_OUT(errp);
	else if (src->hour && (dst->hour = Dz1DHour_00100_clone(src->hour, errp)) == NULL) ERR_OUT(errp);
	else if (src->minute && (dst->minute = Dz1DMinute_00100_clone(src->minute, errp)) == NULL) ERR_OUT(errp);
	else if (src->second && (dst->second = Dz1DSecond_00100_clone(src->second, errp)) == NULL) ERR_OUT(errp);
	else if (src->offset && (dst->offset = Dz1DOffset_00100_clone(src->offset, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1DDateTime_00100* Dz1DDateTime_00100_clone(Dz1DDateTime_00100* src, Dz1Error* err)
{
	Dz1DDateTime_00100* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1DDateTime_00100*)Dz1Calloc(sizeof(Dz1DDateTime_00100), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1DDateTime_00100_delAndSetNull, (void*)&dst);
		if (Dz1DDateTime_00100_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1DDateTime_00100_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1DDateTime_00100_purge(Dz1DDateTime_00100* p)
{
	if (p == NULL) return;
	Dz1DYear_00100_del(p->year);
	Dz1DMonth_00100_del(p->month);
	Dz1DDay_00100_del(p->day);
	Dz1DHour_00100_del(p->hour);
	Dz1DMinute_00100_del(p->minute);
	Dz1DSecond_00100_del(p->second);
	Dz1DOffset_00100_del(p->offset);
}

void Dz1DDateTime_00100_del(Dz1DDateTime_00100* p)
{
	if (p == NULL) return;
	Dz1DDateTime_00100_purge(p);
	Dz1Free(p);
}

void Dz1DDateTime_00100_dump(Dz1DDateTime_00100* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("year = ")); Dz1DYear_00100_dump(p->year, tab);
		Dz1Thread_tprintf(tab, Dz1T("month = ")); Dz1DMonth_00100_dump(p->month, tab);
		Dz1Thread_tprintf(tab, Dz1T("day = ")); Dz1DDay_00100_dump(p->day, tab);
		Dz1Thread_tprintf(tab, Dz1T("hour = ")); Dz1DHour_00100_dump(p->hour, tab);
		Dz1Thread_tprintf(tab, Dz1T("minute = ")); Dz1DMinute_00100_dump(p->minute, tab);
		Dz1Thread_tprintf(tab, Dz1T("second = ")); Dz1DSecond_00100_dump(p->second, tab);
		Dz1Thread_tprintf(tab, Dz1T("offset = ")); Dz1DOffset_00100_dump(p->offset, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1DDateTime_00100_fdump(FILE* fp, Dz1DDateTime_00100* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("year = ")); Dz1DYear_00100_fdump(fp, p->year, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("month = ")); Dz1DMonth_00100_fdump(fp, p->month, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("day = ")); Dz1DDay_00100_fdump(fp, p->day, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("hour = ")); Dz1DHour_00100_fdump(fp, p->hour, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("minute = ")); Dz1DMinute_00100_fdump(fp, p->minute, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("second = ")); Dz1DSecond_00100_fdump(fp, p->second, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("offset = ")); Dz1DOffset_00100_fdump(fp, p->offset, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1DDateTime_00100_fromASN(Dz1DDateTime_00100* dst, DDateTime_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if (src->DEF_DDateTime_00100_year && (dst->year = u16_t_newFromASN(&src->year, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_DDateTime_00100_month && (dst->month = u8_t_newFromASN(&src->month, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_DDateTime_00100_day && (dst->day = u8_t_newFromASN(&src->day, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_DDateTime_00100_hour && (dst->hour = u8_t_newFromASN(&src->hour, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_DDateTime_00100_minute && (dst->minute = u8_t_newFromASN(&src->minute, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_DDateTime_00100_second && (dst->second = u16_t_newFromASN(&src->second, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_DDateTime_00100_offset && (dst->offset = s16_t_newFromASN(&src->offset, &err)) == NULL) ERR_OUT(&err);
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1DDateTime_00100, DDateTime_00100)

Dz1Error Dz1DDateTime_00100_toASN(DDateTime_00100* dst, Dz1DDateTime_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->DEF_DDateTime_00100_year = src->year ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->year, src->year, ws)).code) { Dz1Thread_printf("year : "); ERR_OUT(&err); }
		else if ((dst->DEF_DDateTime_00100_month = src->month ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->month, src->month, ws)).code) { Dz1Thread_printf("month : "); ERR_OUT(&err); }
		else if ((dst->DEF_DDateTime_00100_day = src->day ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->day, src->day, ws)).code) { Dz1Thread_printf("day : "); ERR_OUT(&err); }
		else if ((dst->DEF_DDateTime_00100_hour = src->hour ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->hour, src->hour, ws)).code) { Dz1Thread_printf("hour : "); ERR_OUT(&err); }
		else if ((dst->DEF_DDateTime_00100_minute = src->minute ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->minute, src->minute, ws)).code) { Dz1Thread_printf("minute : "); ERR_OUT(&err); }
		else if ((dst->DEF_DDateTime_00100_second = src->second ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->second, src->second, ws)).code) { Dz1Thread_printf("second : "); ERR_OUT(&err); }
		else if ((dst->DEF_DDateTime_00100_offset = src->offset ? 1 : 0) == 1 && (err = s16_t_toASN(&dst->offset, src->offset, ws)).code) { Dz1Thread_printf("offset : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1DDateTime_00100, DDateTime_00100)
// Dz1DDateTime_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TransmissionAndSpeed_00100
Dz1TransmissionAndSpeed_00100* Dz1TransmissionAndSpeed_00100_new(Dz1TransmissionState_00100 transmisson,
	u16_t speed, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1TransmissionAndSpeed_00100* __internal_ret = (Dz1TransmissionAndSpeed_00100*)Dz1Calloc(sizeof(Dz1TransmissionAndSpeed_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TransmissionAndSpeed_00100_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->transmisson = transmisson;
		__internal_ret->speed = speed;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TransmissionAndSpeed_00100_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TransmissionAndSpeed_00100_copy(Dz1TransmissionAndSpeed_00100* dst, Dz1TransmissionAndSpeed_00100* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->transmisson = src->transmisson;
		dst->speed = src->speed;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1TransmissionAndSpeed_00100* Dz1TransmissionAndSpeed_00100_clone(Dz1TransmissionAndSpeed_00100* src, Dz1Error* err)
{
	Dz1TransmissionAndSpeed_00100* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1TransmissionAndSpeed_00100*)Dz1Calloc(sizeof(Dz1TransmissionAndSpeed_00100), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TransmissionAndSpeed_00100_delAndSetNull, (void*)&dst);
		if (Dz1TransmissionAndSpeed_00100_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TransmissionAndSpeed_00100_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1TransmissionAndSpeed_00100_purge(Dz1TransmissionAndSpeed_00100* p)
{
	if (p == NULL) return;
}

void Dz1TransmissionAndSpeed_00100_del(Dz1TransmissionAndSpeed_00100* p)
{
	if (p == NULL) return;
	Dz1TransmissionAndSpeed_00100_purge(p);
	Dz1Free(p);
}

void Dz1TransmissionAndSpeed_00100_dump(Dz1TransmissionAndSpeed_00100* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("transmisson = %s(%d)\n"), Dz1TransmissionState_00100Str(p->transmisson), p->transmisson);
		Dz1Thread_tprintf(tab, Dz1T("speed = ")); Dz1u16_dump(&p->speed, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1TransmissionAndSpeed_00100_fdump(FILE* fp, Dz1TransmissionAndSpeed_00100* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("transmisson = %s(%d)\n"), Dz1TransmissionState_00100Str(p->transmisson), p->transmisson);
		Dz1Thread_ftprintf(fp, tab, Dz1T("speed = ")); Dz1u16_fdump(fp, &p->speed, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1TransmissionAndSpeed_00100_fromASN(Dz1TransmissionAndSpeed_00100* dst, TransmissionAndSpeed_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u16_t_fromASN(&dst->speed, &src->speed)).code) { Dz1Thread_printf("speed : "); ERR_OUT(&err); }
		else
		{
			dst->transmisson = (Dz1TransmissionState_00100)src->transmisson;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1TransmissionAndSpeed_00100, TransmissionAndSpeed_00100)

Dz1Error Dz1TransmissionAndSpeed_00100_toASN(TransmissionAndSpeed_00100* dst, Dz1TransmissionAndSpeed_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u16_t_toASN(&dst->speed, &src->speed, ws)).code) { Dz1Thread_printf("speed : "); ERR_OUT(&err); }
		else
		{
			dst->transmisson = src->transmisson;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1TransmissionAndSpeed_00100, TransmissionAndSpeed_00100)
// Dz1TransmissionAndSpeed_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TransmissionState_00100
static struct Dz1TransmissionState_00100MapA
{
	str_t str;
	Dz1TransmissionState_00100 v;
} Dz1TransmissionState_00100MapA[] =
{
	{ (char*)"neutral", Dz1TransmissionState_00100_neutral },
	{ (char*)"park", Dz1TransmissionState_00100_park },
	{ (char*)"forwardGears", Dz1TransmissionState_00100_forwardGears },
	{ (char*)"reverseGears", Dz1TransmissionState_00100_reverseGears },
	{ (char*)"reserved1", Dz1TransmissionState_00100_reserved1 },
	{ (char*)"reserved2", Dz1TransmissionState_00100_reserved2 },
	{ (char*)"reserved3", Dz1TransmissionState_00100_reserved3 },
	{ (char*)"unavailable", Dz1TransmissionState_00100_unavailable },
	{ NULL, Dz1TransmissionState_00100_max }
};

str_t Dz1TransmissionState_00100StrA(Dz1TransmissionState_00100 v)
{
	struct Dz1TransmissionState_00100MapA* i = NULL;
	for (i = Dz1TransmissionState_00100MapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TransmissionState_00100 Dz1TransmissionState_00100FromStrA(str_t str)
{
	struct Dz1TransmissionState_00100MapA* i = NULL;
	for (i = Dz1TransmissionState_00100MapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TransmissionState_00100_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TransmissionState_00100MapW
{
	wstr_t str;
	Dz1TransmissionState_00100 v;
} Dz1TransmissionState_00100MapW[] =
{
	{ (wchar_t*)L"neutral", Dz1TransmissionState_00100_neutral },
	{ (wchar_t*)L"park", Dz1TransmissionState_00100_park },
	{ (wchar_t*)L"forwardGears", Dz1TransmissionState_00100_forwardGears },
	{ (wchar_t*)L"reverseGears", Dz1TransmissionState_00100_reverseGears },
	{ (wchar_t*)L"reserved1", Dz1TransmissionState_00100_reserved1 },
	{ (wchar_t*)L"reserved2", Dz1TransmissionState_00100_reserved2 },
	{ (wchar_t*)L"reserved3", Dz1TransmissionState_00100_reserved3 },
	{ (wchar_t*)L"unavailable", Dz1TransmissionState_00100_unavailable },
	{ NULL, Dz1TransmissionState_00100_max }
};

wstr_t Dz1TransmissionState_00100StrW(Dz1TransmissionState_00100 v)
{
	struct Dz1TransmissionState_00100MapW* i = NULL;
	for (i = Dz1TransmissionState_00100MapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TransmissionState_00100 Dz1TransmissionState_00100FromStrW(wstr_t str)
{
	struct Dz1TransmissionState_00100MapW* i = NULL;
	for (i = Dz1TransmissionState_00100MapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TransmissionState_00100_max;
}
#endif // UNIX_SYSTEM

Dz1TransmissionState_00100* Dz1TransmissionState_00100_new(Dz1TransmissionState_00100* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1TransmissionState_00100* __internal_ret = (Dz1TransmissionState_00100*)Dz1Calloc(sizeof(Dz1TransmissionState_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TransmissionState_00100_dump(Dz1TransmissionState_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TransmissionState_00100Str(*v));
}
void Dz1TransmissionState_00100_fdump(FILE* fp, Dz1TransmissionState_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1TransmissionState_00100Str(*v));
}
Dz1Error Dz1TransmissionState_00100_fromASN(Dz1TransmissionState_00100* dst, TransmissionState_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1TransmissionState_00100)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1TransmissionState_00100, TransmissionState_00100)

Dz1Error Dz1TransmissionState_00100_toASN(TransmissionState_00100* dst, Dz1TransmissionState_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (TransmissionState_00100)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1TransmissionState_00100, TransmissionState_00100)
// Dz1TransmissionState_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1PositionalAccuracy_00100
Dz1PositionalAccuracy_00100* Dz1PositionalAccuracy_00100_new(u8_t semiMajor,
	u8_t semiMinor,
	u16_t orientation, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1PositionalAccuracy_00100* __internal_ret = (Dz1PositionalAccuracy_00100*)Dz1Calloc(sizeof(Dz1PositionalAccuracy_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1PositionalAccuracy_00100_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->semiMajor = semiMajor;
		__internal_ret->semiMinor = semiMinor;
		__internal_ret->orientation = orientation;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1PositionalAccuracy_00100_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1PositionalAccuracy_00100_copy(Dz1PositionalAccuracy_00100* dst, Dz1PositionalAccuracy_00100* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->semiMajor = src->semiMajor;
		dst->semiMinor = src->semiMinor;
		dst->orientation = src->orientation;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1PositionalAccuracy_00100* Dz1PositionalAccuracy_00100_clone(Dz1PositionalAccuracy_00100* src, Dz1Error* err)
{
	Dz1PositionalAccuracy_00100* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1PositionalAccuracy_00100*)Dz1Calloc(sizeof(Dz1PositionalAccuracy_00100), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1PositionalAccuracy_00100_delAndSetNull, (void*)&dst);
		if (Dz1PositionalAccuracy_00100_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1PositionalAccuracy_00100_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1PositionalAccuracy_00100_purge(Dz1PositionalAccuracy_00100* p)
{
	if (p == NULL) return;
}

void Dz1PositionalAccuracy_00100_del(Dz1PositionalAccuracy_00100* p)
{
	if (p == NULL) return;
	Dz1PositionalAccuracy_00100_purge(p);
	Dz1Free(p);
}

void Dz1PositionalAccuracy_00100_dump(Dz1PositionalAccuracy_00100* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("semiMajor = ")); Dz1u8_dump(&p->semiMajor, tab);
		Dz1Thread_tprintf(tab, Dz1T("semiMinor = ")); Dz1u8_dump(&p->semiMinor, tab);
		Dz1Thread_tprintf(tab, Dz1T("orientation = ")); Dz1u16_dump(&p->orientation, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1PositionalAccuracy_00100_fdump(FILE* fp, Dz1PositionalAccuracy_00100* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("semiMajor = ")); Dz1u8_fdump(fp, &p->semiMajor, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("semiMinor = ")); Dz1u8_fdump(fp, &p->semiMinor, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("orientation = ")); Dz1u16_fdump(fp, &p->orientation, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1PositionalAccuracy_00100_fromASN(Dz1PositionalAccuracy_00100* dst, PositionalAccuracy_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u8_t_fromASN(&dst->semiMajor, &src->semiMajor)).code) { Dz1Thread_printf("semiMajor : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->semiMinor, &src->semiMinor)).code) { Dz1Thread_printf("semiMinor : "); ERR_OUT(&err); }
		else if ((err = u16_t_fromASN(&dst->orientation, &src->orientation)).code) { Dz1Thread_printf("orientation : "); ERR_OUT(&err); }
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1PositionalAccuracy_00100, PositionalAccuracy_00100)

Dz1Error Dz1PositionalAccuracy_00100_toASN(PositionalAccuracy_00100* dst, Dz1PositionalAccuracy_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u8_t_toASN(&dst->semiMajor, &src->semiMajor, ws)).code) { Dz1Thread_printf("semiMajor : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->semiMinor, &src->semiMinor, ws)).code) { Dz1Thread_printf("semiMinor : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->orientation, &src->orientation, ws)).code) { Dz1Thread_printf("orientation : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1PositionalAccuracy_00100, PositionalAccuracy_00100)
// Dz1PositionalAccuracy_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TimeConfidence_00100
static struct Dz1TimeConfidence_00100MapA
{
	str_t str;
	Dz1TimeConfidence_00100 v;
} Dz1TimeConfidence_00100MapA[] =
{
	{ (char*)"unavailable", Dz1TimeConfidence_00100_unavailable },
	{ (char*)"time_100_000", Dz1TimeConfidence_00100_time_100_000 },
	{ (char*)"time_050_000", Dz1TimeConfidence_00100_time_050_000 },
	{ (char*)"time_020_000", Dz1TimeConfidence_00100_time_020_000 },
	{ (char*)"time_010_000", Dz1TimeConfidence_00100_time_010_000 },
	{ (char*)"time_002_000", Dz1TimeConfidence_00100_time_002_000 },
	{ (char*)"time_001_000", Dz1TimeConfidence_00100_time_001_000 },
	{ (char*)"time_000_500", Dz1TimeConfidence_00100_time_000_500 },
	{ (char*)"time_000_200", Dz1TimeConfidence_00100_time_000_200 },
	{ (char*)"time_000_100", Dz1TimeConfidence_00100_time_000_100 },
	{ (char*)"time_000_050", Dz1TimeConfidence_00100_time_000_050 },
	{ (char*)"time_000_020", Dz1TimeConfidence_00100_time_000_020 },
	{ (char*)"time_000_010", Dz1TimeConfidence_00100_time_000_010 },
	{ (char*)"time_000_005", Dz1TimeConfidence_00100_time_000_005 },
	{ (char*)"time_000_002", Dz1TimeConfidence_00100_time_000_002 },
	{ (char*)"time_000_001", Dz1TimeConfidence_00100_time_000_001 },
	{ (char*)"time_000_000_5", Dz1TimeConfidence_00100_time_000_000_5 },
	{ (char*)"time_000_000_2", Dz1TimeConfidence_00100_time_000_000_2 },
	{ (char*)"time_000_000_1", Dz1TimeConfidence_00100_time_000_000_1 },
	{ (char*)"time_000_000_05", Dz1TimeConfidence_00100_time_000_000_05 },
	{ (char*)"time_000_000_02", Dz1TimeConfidence_00100_time_000_000_02 },
	{ (char*)"time_000_000_01", Dz1TimeConfidence_00100_time_000_000_01 },
	{ (char*)"time_000_000_005", Dz1TimeConfidence_00100_time_000_000_005 },
	{ (char*)"time_000_000_002", Dz1TimeConfidence_00100_time_000_000_002 },
	{ (char*)"time_000_000_001", Dz1TimeConfidence_00100_time_000_000_001 },
	{ (char*)"time_000_000_000_5", Dz1TimeConfidence_00100_time_000_000_000_5 },
	{ (char*)"time_000_000_000_2", Dz1TimeConfidence_00100_time_000_000_000_2 },
	{ (char*)"time_000_000_000_1", Dz1TimeConfidence_00100_time_000_000_000_1 },
	{ (char*)"time_000_000_000_05", Dz1TimeConfidence_00100_time_000_000_000_05 },
	{ (char*)"time_000_000_000_02", Dz1TimeConfidence_00100_time_000_000_000_02 },
	{ (char*)"time_000_000_000_01", Dz1TimeConfidence_00100_time_000_000_000_01 },
	{ (char*)"time_000_000_000_005", Dz1TimeConfidence_00100_time_000_000_000_005 },
	{ (char*)"time_000_000_000_002", Dz1TimeConfidence_00100_time_000_000_000_002 },
	{ (char*)"time_000_000_000_001", Dz1TimeConfidence_00100_time_000_000_000_001 },
	{ (char*)"time_000_000_000_000_5", Dz1TimeConfidence_00100_time_000_000_000_000_5 },
	{ (char*)"time_000_000_000_000_2", Dz1TimeConfidence_00100_time_000_000_000_000_2 },
	{ (char*)"time_000_000_000_000_1", Dz1TimeConfidence_00100_time_000_000_000_000_1 },
	{ (char*)"time_000_000_000_000_05", Dz1TimeConfidence_00100_time_000_000_000_000_05 },
	{ (char*)"time_000_000_000_000_02", Dz1TimeConfidence_00100_time_000_000_000_000_02 },
	{ (char*)"time_000_000_000_000_01", Dz1TimeConfidence_00100_time_000_000_000_000_01 },
	{ NULL, Dz1TimeConfidence_00100_max }
};

str_t Dz1TimeConfidence_00100StrA(Dz1TimeConfidence_00100 v)
{
	struct Dz1TimeConfidence_00100MapA* i = NULL;
	for (i = Dz1TimeConfidence_00100MapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TimeConfidence_00100 Dz1TimeConfidence_00100FromStrA(str_t str)
{
	struct Dz1TimeConfidence_00100MapA* i = NULL;
	for (i = Dz1TimeConfidence_00100MapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TimeConfidence_00100_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TimeConfidence_00100MapW
{
	wstr_t str;
	Dz1TimeConfidence_00100 v;
} Dz1TimeConfidence_00100MapW[] =
{
	{ (wchar_t*)L"unavailable", Dz1TimeConfidence_00100_unavailable },
	{ (wchar_t*)L"time_100_000", Dz1TimeConfidence_00100_time_100_000 },
	{ (wchar_t*)L"time_050_000", Dz1TimeConfidence_00100_time_050_000 },
	{ (wchar_t*)L"time_020_000", Dz1TimeConfidence_00100_time_020_000 },
	{ (wchar_t*)L"time_010_000", Dz1TimeConfidence_00100_time_010_000 },
	{ (wchar_t*)L"time_002_000", Dz1TimeConfidence_00100_time_002_000 },
	{ (wchar_t*)L"time_001_000", Dz1TimeConfidence_00100_time_001_000 },
	{ (wchar_t*)L"time_000_500", Dz1TimeConfidence_00100_time_000_500 },
	{ (wchar_t*)L"time_000_200", Dz1TimeConfidence_00100_time_000_200 },
	{ (wchar_t*)L"time_000_100", Dz1TimeConfidence_00100_time_000_100 },
	{ (wchar_t*)L"time_000_050", Dz1TimeConfidence_00100_time_000_050 },
	{ (wchar_t*)L"time_000_020", Dz1TimeConfidence_00100_time_000_020 },
	{ (wchar_t*)L"time_000_010", Dz1TimeConfidence_00100_time_000_010 },
	{ (wchar_t*)L"time_000_005", Dz1TimeConfidence_00100_time_000_005 },
	{ (wchar_t*)L"time_000_002", Dz1TimeConfidence_00100_time_000_002 },
	{ (wchar_t*)L"time_000_001", Dz1TimeConfidence_00100_time_000_001 },
	{ (wchar_t*)L"time_000_000_5", Dz1TimeConfidence_00100_time_000_000_5 },
	{ (wchar_t*)L"time_000_000_2", Dz1TimeConfidence_00100_time_000_000_2 },
	{ (wchar_t*)L"time_000_000_1", Dz1TimeConfidence_00100_time_000_000_1 },
	{ (wchar_t*)L"time_000_000_05", Dz1TimeConfidence_00100_time_000_000_05 },
	{ (wchar_t*)L"time_000_000_02", Dz1TimeConfidence_00100_time_000_000_02 },
	{ (wchar_t*)L"time_000_000_01", Dz1TimeConfidence_00100_time_000_000_01 },
	{ (wchar_t*)L"time_000_000_005", Dz1TimeConfidence_00100_time_000_000_005 },
	{ (wchar_t*)L"time_000_000_002", Dz1TimeConfidence_00100_time_000_000_002 },
	{ (wchar_t*)L"time_000_000_001", Dz1TimeConfidence_00100_time_000_000_001 },
	{ (wchar_t*)L"time_000_000_000_5", Dz1TimeConfidence_00100_time_000_000_000_5 },
	{ (wchar_t*)L"time_000_000_000_2", Dz1TimeConfidence_00100_time_000_000_000_2 },
	{ (wchar_t*)L"time_000_000_000_1", Dz1TimeConfidence_00100_time_000_000_000_1 },
	{ (wchar_t*)L"time_000_000_000_05", Dz1TimeConfidence_00100_time_000_000_000_05 },
	{ (wchar_t*)L"time_000_000_000_02", Dz1TimeConfidence_00100_time_000_000_000_02 },
	{ (wchar_t*)L"time_000_000_000_01", Dz1TimeConfidence_00100_time_000_000_000_01 },
	{ (wchar_t*)L"time_000_000_000_005", Dz1TimeConfidence_00100_time_000_000_000_005 },
	{ (wchar_t*)L"time_000_000_000_002", Dz1TimeConfidence_00100_time_000_000_000_002 },
	{ (wchar_t*)L"time_000_000_000_001", Dz1TimeConfidence_00100_time_000_000_000_001 },
	{ (wchar_t*)L"time_000_000_000_000_5", Dz1TimeConfidence_00100_time_000_000_000_000_5 },
	{ (wchar_t*)L"time_000_000_000_000_2", Dz1TimeConfidence_00100_time_000_000_000_000_2 },
	{ (wchar_t*)L"time_000_000_000_000_1", Dz1TimeConfidence_00100_time_000_000_000_000_1 },
	{ (wchar_t*)L"time_000_000_000_000_05", Dz1TimeConfidence_00100_time_000_000_000_000_05 },
	{ (wchar_t*)L"time_000_000_000_000_02", Dz1TimeConfidence_00100_time_000_000_000_000_02 },
	{ (wchar_t*)L"time_000_000_000_000_01", Dz1TimeConfidence_00100_time_000_000_000_000_01 },
	{ NULL, Dz1TimeConfidence_00100_max }
};

wstr_t Dz1TimeConfidence_00100StrW(Dz1TimeConfidence_00100 v)
{
	struct Dz1TimeConfidence_00100MapW* i = NULL;
	for (i = Dz1TimeConfidence_00100MapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TimeConfidence_00100 Dz1TimeConfidence_00100FromStrW(wstr_t str)
{
	struct Dz1TimeConfidence_00100MapW* i = NULL;
	for (i = Dz1TimeConfidence_00100MapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TimeConfidence_00100_max;
}
#endif // UNIX_SYSTEM

Dz1TimeConfidence_00100* Dz1TimeConfidence_00100_new(Dz1TimeConfidence_00100* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1TimeConfidence_00100* __internal_ret = (Dz1TimeConfidence_00100*)Dz1Calloc(sizeof(Dz1TimeConfidence_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1TimeConfidence_00100_dump(Dz1TimeConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1TimeConfidence_00100Str(*v));
}
void Dz1TimeConfidence_00100_fdump(FILE* fp, Dz1TimeConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1TimeConfidence_00100Str(*v));
}
Dz1Error Dz1TimeConfidence_00100_fromASN(Dz1TimeConfidence_00100* dst, TimeConfidence_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1TimeConfidence_00100)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1TimeConfidence_00100, TimeConfidence_00100)

Dz1Error Dz1TimeConfidence_00100_toASN(TimeConfidence_00100* dst, Dz1TimeConfidence_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (TimeConfidence_00100)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1TimeConfidence_00100, TimeConfidence_00100)
// Dz1TimeConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1PositionConfidenceSet_00100
Dz1PositionConfidenceSet_00100* Dz1PositionConfidenceSet_00100_new(Dz1PositionConfidence_00100 pos,
	Dz1ElevationConfidence_00100 elevation, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1PositionConfidenceSet_00100* __internal_ret = (Dz1PositionConfidenceSet_00100*)Dz1Calloc(sizeof(Dz1PositionConfidenceSet_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1PositionConfidenceSet_00100_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->pos = pos;
		__internal_ret->elevation = elevation;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1PositionConfidenceSet_00100_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1PositionConfidenceSet_00100_copy(Dz1PositionConfidenceSet_00100* dst, Dz1PositionConfidenceSet_00100* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->pos = src->pos;
		dst->elevation = src->elevation;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1PositionConfidenceSet_00100* Dz1PositionConfidenceSet_00100_clone(Dz1PositionConfidenceSet_00100* src, Dz1Error* err)
{
	Dz1PositionConfidenceSet_00100* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1PositionConfidenceSet_00100*)Dz1Calloc(sizeof(Dz1PositionConfidenceSet_00100), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1PositionConfidenceSet_00100_delAndSetNull, (void*)&dst);
		if (Dz1PositionConfidenceSet_00100_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1PositionConfidenceSet_00100_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1PositionConfidenceSet_00100_purge(Dz1PositionConfidenceSet_00100* p)
{
	if (p == NULL) return;
}

void Dz1PositionConfidenceSet_00100_del(Dz1PositionConfidenceSet_00100* p)
{
	if (p == NULL) return;
	Dz1PositionConfidenceSet_00100_purge(p);
	Dz1Free(p);
}

void Dz1PositionConfidenceSet_00100_dump(Dz1PositionConfidenceSet_00100* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("pos = %s(%d)\n"), Dz1PositionConfidence_00100Str(p->pos), p->pos);
		Dz1Thread_tprintf(tab, Dz1T("elevation = %s(%d)\n"), Dz1ElevationConfidence_00100Str(p->elevation), p->elevation);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1PositionConfidenceSet_00100_fdump(FILE* fp, Dz1PositionConfidenceSet_00100* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("pos = %s(%d)\n"), Dz1PositionConfidence_00100Str(p->pos), p->pos);
		Dz1Thread_ftprintf(fp, tab, Dz1T("elevation = %s(%d)\n"), Dz1ElevationConfidence_00100Str(p->elevation), p->elevation);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1PositionConfidenceSet_00100_fromASN(Dz1PositionConfidenceSet_00100* dst, PositionConfidenceSet_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->pos = (Dz1PositionConfidence_00100)src->pos;
		dst->elevation = (Dz1ElevationConfidence_00100)src->elevation;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1PositionConfidenceSet_00100, PositionConfidenceSet_00100)

Dz1Error Dz1PositionConfidenceSet_00100_toASN(PositionConfidenceSet_00100* dst, Dz1PositionConfidenceSet_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->pos = src->pos;
		dst->elevation = src->elevation;
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1PositionConfidenceSet_00100, PositionConfidenceSet_00100)
// Dz1PositionConfidenceSet_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ElevationConfidence_00100
static struct Dz1ElevationConfidence_00100MapA
{
	str_t str;
	Dz1ElevationConfidence_00100 v;
} Dz1ElevationConfidence_00100MapA[] =
{
	{ (char*)"unavailable", Dz1ElevationConfidence_00100_unavailable },
	{ (char*)"elev_500_00", Dz1ElevationConfidence_00100_elev_500_00 },
	{ (char*)"elev_200_00", Dz1ElevationConfidence_00100_elev_200_00 },
	{ (char*)"elev_100_00", Dz1ElevationConfidence_00100_elev_100_00 },
	{ (char*)"elev_050_00", Dz1ElevationConfidence_00100_elev_050_00 },
	{ (char*)"elev_020_00", Dz1ElevationConfidence_00100_elev_020_00 },
	{ (char*)"elev_010_00", Dz1ElevationConfidence_00100_elev_010_00 },
	{ (char*)"elev_005_00", Dz1ElevationConfidence_00100_elev_005_00 },
	{ (char*)"elev_002_00", Dz1ElevationConfidence_00100_elev_002_00 },
	{ (char*)"elev_001_00", Dz1ElevationConfidence_00100_elev_001_00 },
	{ (char*)"elev_000_50", Dz1ElevationConfidence_00100_elev_000_50 },
	{ (char*)"elev_000_20", Dz1ElevationConfidence_00100_elev_000_20 },
	{ (char*)"elev_000_10", Dz1ElevationConfidence_00100_elev_000_10 },
	{ (char*)"elev_000_05", Dz1ElevationConfidence_00100_elev_000_05 },
	{ (char*)"elev_000_02", Dz1ElevationConfidence_00100_elev_000_02 },
	{ (char*)"elev_000_01", Dz1ElevationConfidence_00100_elev_000_01 },
	{ NULL, Dz1ElevationConfidence_00100_max }
};

str_t Dz1ElevationConfidence_00100StrA(Dz1ElevationConfidence_00100 v)
{
	struct Dz1ElevationConfidence_00100MapA* i = NULL;
	for (i = Dz1ElevationConfidence_00100MapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1ElevationConfidence_00100 Dz1ElevationConfidence_00100FromStrA(str_t str)
{
	struct Dz1ElevationConfidence_00100MapA* i = NULL;
	for (i = Dz1ElevationConfidence_00100MapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1ElevationConfidence_00100_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1ElevationConfidence_00100MapW
{
	wstr_t str;
	Dz1ElevationConfidence_00100 v;
} Dz1ElevationConfidence_00100MapW[] =
{
	{ (wchar_t*)L"unavailable", Dz1ElevationConfidence_00100_unavailable },
	{ (wchar_t*)L"elev_500_00", Dz1ElevationConfidence_00100_elev_500_00 },
	{ (wchar_t*)L"elev_200_00", Dz1ElevationConfidence_00100_elev_200_00 },
	{ (wchar_t*)L"elev_100_00", Dz1ElevationConfidence_00100_elev_100_00 },
	{ (wchar_t*)L"elev_050_00", Dz1ElevationConfidence_00100_elev_050_00 },
	{ (wchar_t*)L"elev_020_00", Dz1ElevationConfidence_00100_elev_020_00 },
	{ (wchar_t*)L"elev_010_00", Dz1ElevationConfidence_00100_elev_010_00 },
	{ (wchar_t*)L"elev_005_00", Dz1ElevationConfidence_00100_elev_005_00 },
	{ (wchar_t*)L"elev_002_00", Dz1ElevationConfidence_00100_elev_002_00 },
	{ (wchar_t*)L"elev_001_00", Dz1ElevationConfidence_00100_elev_001_00 },
	{ (wchar_t*)L"elev_000_50", Dz1ElevationConfidence_00100_elev_000_50 },
	{ (wchar_t*)L"elev_000_20", Dz1ElevationConfidence_00100_elev_000_20 },
	{ (wchar_t*)L"elev_000_10", Dz1ElevationConfidence_00100_elev_000_10 },
	{ (wchar_t*)L"elev_000_05", Dz1ElevationConfidence_00100_elev_000_05 },
	{ (wchar_t*)L"elev_000_02", Dz1ElevationConfidence_00100_elev_000_02 },
	{ (wchar_t*)L"elev_000_01", Dz1ElevationConfidence_00100_elev_000_01 },
	{ NULL, Dz1ElevationConfidence_00100_max }
};

wstr_t Dz1ElevationConfidence_00100StrW(Dz1ElevationConfidence_00100 v)
{
	struct Dz1ElevationConfidence_00100MapW* i = NULL;
	for (i = Dz1ElevationConfidence_00100MapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1ElevationConfidence_00100 Dz1ElevationConfidence_00100FromStrW(wstr_t str)
{
	struct Dz1ElevationConfidence_00100MapW* i = NULL;
	for (i = Dz1ElevationConfidence_00100MapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1ElevationConfidence_00100_max;
}
#endif // UNIX_SYSTEM

Dz1ElevationConfidence_00100* Dz1ElevationConfidence_00100_new(Dz1ElevationConfidence_00100* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ElevationConfidence_00100* __internal_ret = (Dz1ElevationConfidence_00100*)Dz1Calloc(sizeof(Dz1ElevationConfidence_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1ElevationConfidence_00100_dump(Dz1ElevationConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1ElevationConfidence_00100Str(*v));
}
void Dz1ElevationConfidence_00100_fdump(FILE* fp, Dz1ElevationConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1ElevationConfidence_00100Str(*v));
}
Dz1Error Dz1ElevationConfidence_00100_fromASN(Dz1ElevationConfidence_00100* dst, ElevationConfidence_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1ElevationConfidence_00100)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1ElevationConfidence_00100, ElevationConfidence_00100)

Dz1Error Dz1ElevationConfidence_00100_toASN(ElevationConfidence_00100* dst, Dz1ElevationConfidence_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (ElevationConfidence_00100)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1ElevationConfidence_00100, ElevationConfidence_00100)
// Dz1ElevationConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1PositionConfidence_00100
static struct Dz1PositionConfidence_00100MapA
{
	str_t str;
	Dz1PositionConfidence_00100 v;
} Dz1PositionConfidence_00100MapA[] =
{
	{ (char*)"unavailable", Dz1PositionConfidence_00100_unavailable },
	{ (char*)"a500m", Dz1PositionConfidence_00100_a500m },
	{ (char*)"a200m", Dz1PositionConfidence_00100_a200m },
	{ (char*)"a100m", Dz1PositionConfidence_00100_a100m },
	{ (char*)"a50m", Dz1PositionConfidence_00100_a50m },
	{ (char*)"a20m", Dz1PositionConfidence_00100_a20m },
	{ (char*)"a10m", Dz1PositionConfidence_00100_a10m },
	{ (char*)"a5m", Dz1PositionConfidence_00100_a5m },
	{ (char*)"a2m", Dz1PositionConfidence_00100_a2m },
	{ (char*)"a1m", Dz1PositionConfidence_00100_a1m },
	{ (char*)"a50cm", Dz1PositionConfidence_00100_a50cm },
	{ (char*)"a20cm", Dz1PositionConfidence_00100_a20cm },
	{ (char*)"a10cm", Dz1PositionConfidence_00100_a10cm },
	{ (char*)"a5cm", Dz1PositionConfidence_00100_a5cm },
	{ (char*)"a2cm", Dz1PositionConfidence_00100_a2cm },
	{ (char*)"a1cm", Dz1PositionConfidence_00100_a1cm },
	{ NULL, Dz1PositionConfidence_00100_max }
};

str_t Dz1PositionConfidence_00100StrA(Dz1PositionConfidence_00100 v)
{
	struct Dz1PositionConfidence_00100MapA* i = NULL;
	for (i = Dz1PositionConfidence_00100MapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1PositionConfidence_00100 Dz1PositionConfidence_00100FromStrA(str_t str)
{
	struct Dz1PositionConfidence_00100MapA* i = NULL;
	for (i = Dz1PositionConfidence_00100MapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1PositionConfidence_00100_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1PositionConfidence_00100MapW
{
	wstr_t str;
	Dz1PositionConfidence_00100 v;
} Dz1PositionConfidence_00100MapW[] =
{
	{ (wchar_t*)L"unavailable", Dz1PositionConfidence_00100_unavailable },
	{ (wchar_t*)L"a500m", Dz1PositionConfidence_00100_a500m },
	{ (wchar_t*)L"a200m", Dz1PositionConfidence_00100_a200m },
	{ (wchar_t*)L"a100m", Dz1PositionConfidence_00100_a100m },
	{ (wchar_t*)L"a50m", Dz1PositionConfidence_00100_a50m },
	{ (wchar_t*)L"a20m", Dz1PositionConfidence_00100_a20m },
	{ (wchar_t*)L"a10m", Dz1PositionConfidence_00100_a10m },
	{ (wchar_t*)L"a5m", Dz1PositionConfidence_00100_a5m },
	{ (wchar_t*)L"a2m", Dz1PositionConfidence_00100_a2m },
	{ (wchar_t*)L"a1m", Dz1PositionConfidence_00100_a1m },
	{ (wchar_t*)L"a50cm", Dz1PositionConfidence_00100_a50cm },
	{ (wchar_t*)L"a20cm", Dz1PositionConfidence_00100_a20cm },
	{ (wchar_t*)L"a10cm", Dz1PositionConfidence_00100_a10cm },
	{ (wchar_t*)L"a5cm", Dz1PositionConfidence_00100_a5cm },
	{ (wchar_t*)L"a2cm", Dz1PositionConfidence_00100_a2cm },
	{ (wchar_t*)L"a1cm", Dz1PositionConfidence_00100_a1cm },
	{ NULL, Dz1PositionConfidence_00100_max }
};

wstr_t Dz1PositionConfidence_00100StrW(Dz1PositionConfidence_00100 v)
{
	struct Dz1PositionConfidence_00100MapW* i = NULL;
	for (i = Dz1PositionConfidence_00100MapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1PositionConfidence_00100 Dz1PositionConfidence_00100FromStrW(wstr_t str)
{
	struct Dz1PositionConfidence_00100MapW* i = NULL;
	for (i = Dz1PositionConfidence_00100MapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1PositionConfidence_00100_max;
}
#endif // UNIX_SYSTEM

Dz1PositionConfidence_00100* Dz1PositionConfidence_00100_new(Dz1PositionConfidence_00100* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1PositionConfidence_00100* __internal_ret = (Dz1PositionConfidence_00100*)Dz1Calloc(sizeof(Dz1PositionConfidence_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1PositionConfidence_00100_dump(Dz1PositionConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1PositionConfidence_00100Str(*v));
}
void Dz1PositionConfidence_00100_fdump(FILE* fp, Dz1PositionConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1PositionConfidence_00100Str(*v));
}
Dz1Error Dz1PositionConfidence_00100_fromASN(Dz1PositionConfidence_00100* dst, PositionConfidence_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1PositionConfidence_00100)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1PositionConfidence_00100, PositionConfidence_00100)

Dz1Error Dz1PositionConfidence_00100_toASN(PositionConfidence_00100* dst, Dz1PositionConfidence_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (PositionConfidence_00100)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1PositionConfidence_00100, PositionConfidence_00100)
// Dz1PositionConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SpeedandHeadingandThrottleConfidence_00100
Dz1SpeedandHeadingandThrottleConfidence_00100* Dz1SpeedandHeadingandThrottleConfidence_00100_new(Dz1HeadingConfidence_00100 heading,
	Dz1SpeedConfidence_00100 speed,
	Dz1ThrottleConfidence_00100 throttle, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1SpeedandHeadingandThrottleConfidence_00100* __internal_ret = (Dz1SpeedandHeadingandThrottleConfidence_00100*)Dz1Calloc(sizeof(Dz1SpeedandHeadingandThrottleConfidence_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SpeedandHeadingandThrottleConfidence_00100_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->heading = heading;
		__internal_ret->speed = speed;
		__internal_ret->throttle = throttle;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SpeedandHeadingandThrottleConfidence_00100_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1SpeedandHeadingandThrottleConfidence_00100_copy(Dz1SpeedandHeadingandThrottleConfidence_00100* dst, Dz1SpeedandHeadingandThrottleConfidence_00100* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->heading = src->heading;
		dst->speed = src->speed;
		dst->throttle = src->throttle;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1SpeedandHeadingandThrottleConfidence_00100* Dz1SpeedandHeadingandThrottleConfidence_00100_clone(Dz1SpeedandHeadingandThrottleConfidence_00100* src, Dz1Error* err)
{
	Dz1SpeedandHeadingandThrottleConfidence_00100* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1SpeedandHeadingandThrottleConfidence_00100*)Dz1Calloc(sizeof(Dz1SpeedandHeadingandThrottleConfidence_00100), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SpeedandHeadingandThrottleConfidence_00100_delAndSetNull, (void*)&dst);
		if (Dz1SpeedandHeadingandThrottleConfidence_00100_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SpeedandHeadingandThrottleConfidence_00100_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1SpeedandHeadingandThrottleConfidence_00100_purge(Dz1SpeedandHeadingandThrottleConfidence_00100* p)
{
	if (p == NULL) return;
}

void Dz1SpeedandHeadingandThrottleConfidence_00100_del(Dz1SpeedandHeadingandThrottleConfidence_00100* p)
{
	if (p == NULL) return;
	Dz1SpeedandHeadingandThrottleConfidence_00100_purge(p);
	Dz1Free(p);
}

void Dz1SpeedandHeadingandThrottleConfidence_00100_dump(Dz1SpeedandHeadingandThrottleConfidence_00100* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("heading = %s(%d)\n"), Dz1HeadingConfidence_00100Str(p->heading), p->heading);
		Dz1Thread_tprintf(tab, Dz1T("speed = %s(%d)\n"), Dz1SpeedConfidence_00100Str(p->speed), p->speed);
		Dz1Thread_tprintf(tab, Dz1T("throttle = %s(%d)\n"), Dz1ThrottleConfidence_00100Str(p->throttle), p->throttle);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1SpeedandHeadingandThrottleConfidence_00100_fdump(FILE* fp, Dz1SpeedandHeadingandThrottleConfidence_00100* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("heading = %s(%d)\n"), Dz1HeadingConfidence_00100Str(p->heading), p->heading);
		Dz1Thread_ftprintf(fp, tab, Dz1T("speed = %s(%d)\n"), Dz1SpeedConfidence_00100Str(p->speed), p->speed);
		Dz1Thread_ftprintf(fp, tab, Dz1T("throttle = %s(%d)\n"), Dz1ThrottleConfidence_00100Str(p->throttle), p->throttle);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1SpeedandHeadingandThrottleConfidence_00100_fromASN(Dz1SpeedandHeadingandThrottleConfidence_00100* dst, SpeedandHeadingandThrottleConfidence_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->heading = (Dz1HeadingConfidence_00100)src->heading;
		dst->speed = (Dz1SpeedConfidence_00100)src->speed;
		dst->throttle = (Dz1ThrottleConfidence_00100)src->throttle;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1SpeedandHeadingandThrottleConfidence_00100, SpeedandHeadingandThrottleConfidence_00100)

Dz1Error Dz1SpeedandHeadingandThrottleConfidence_00100_toASN(SpeedandHeadingandThrottleConfidence_00100* dst, Dz1SpeedandHeadingandThrottleConfidence_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->heading = src->heading;
		dst->speed = src->speed;
		dst->throttle = src->throttle;
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1SpeedandHeadingandThrottleConfidence_00100, SpeedandHeadingandThrottleConfidence_00100)
// Dz1SpeedandHeadingandThrottleConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1HeadingConfidence_00100
static struct Dz1HeadingConfidence_00100MapA
{
	str_t str;
	Dz1HeadingConfidence_00100 v;
} Dz1HeadingConfidence_00100MapA[] =
{
	{ (char*)"unavailable", Dz1HeadingConfidence_00100_unavailable },
	{ (char*)"prec10deg", Dz1HeadingConfidence_00100_prec10deg },
	{ (char*)"prec05deg", Dz1HeadingConfidence_00100_prec05deg },
	{ (char*)"prec01deg", Dz1HeadingConfidence_00100_prec01deg },
	{ (char*)"prec0_1deg", Dz1HeadingConfidence_00100_prec0_1deg },
	{ (char*)"prec0_05deg", Dz1HeadingConfidence_00100_prec0_05deg },
	{ (char*)"prec0_01deg", Dz1HeadingConfidence_00100_prec0_01deg },
	{ (char*)"prec0_0125deg", Dz1HeadingConfidence_00100_prec0_0125deg },
	{ NULL, Dz1HeadingConfidence_00100_max }
};

str_t Dz1HeadingConfidence_00100StrA(Dz1HeadingConfidence_00100 v)
{
	struct Dz1HeadingConfidence_00100MapA* i = NULL;
	for (i = Dz1HeadingConfidence_00100MapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1HeadingConfidence_00100 Dz1HeadingConfidence_00100FromStrA(str_t str)
{
	struct Dz1HeadingConfidence_00100MapA* i = NULL;
	for (i = Dz1HeadingConfidence_00100MapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1HeadingConfidence_00100_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1HeadingConfidence_00100MapW
{
	wstr_t str;
	Dz1HeadingConfidence_00100 v;
} Dz1HeadingConfidence_00100MapW[] =
{
	{ (wchar_t*)L"unavailable", Dz1HeadingConfidence_00100_unavailable },
	{ (wchar_t*)L"prec10deg", Dz1HeadingConfidence_00100_prec10deg },
	{ (wchar_t*)L"prec05deg", Dz1HeadingConfidence_00100_prec05deg },
	{ (wchar_t*)L"prec01deg", Dz1HeadingConfidence_00100_prec01deg },
	{ (wchar_t*)L"prec0_1deg", Dz1HeadingConfidence_00100_prec0_1deg },
	{ (wchar_t*)L"prec0_05deg", Dz1HeadingConfidence_00100_prec0_05deg },
	{ (wchar_t*)L"prec0_01deg", Dz1HeadingConfidence_00100_prec0_01deg },
	{ (wchar_t*)L"prec0_0125deg", Dz1HeadingConfidence_00100_prec0_0125deg },
	{ NULL, Dz1HeadingConfidence_00100_max }
};

wstr_t Dz1HeadingConfidence_00100StrW(Dz1HeadingConfidence_00100 v)
{
	struct Dz1HeadingConfidence_00100MapW* i = NULL;
	for (i = Dz1HeadingConfidence_00100MapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1HeadingConfidence_00100 Dz1HeadingConfidence_00100FromStrW(wstr_t str)
{
	struct Dz1HeadingConfidence_00100MapW* i = NULL;
	for (i = Dz1HeadingConfidence_00100MapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1HeadingConfidence_00100_max;
}
#endif // UNIX_SYSTEM

Dz1HeadingConfidence_00100* Dz1HeadingConfidence_00100_new(Dz1HeadingConfidence_00100* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1HeadingConfidence_00100* __internal_ret = (Dz1HeadingConfidence_00100*)Dz1Calloc(sizeof(Dz1HeadingConfidence_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1HeadingConfidence_00100_dump(Dz1HeadingConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1HeadingConfidence_00100Str(*v));
}
void Dz1HeadingConfidence_00100_fdump(FILE* fp, Dz1HeadingConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1HeadingConfidence_00100Str(*v));
}
Dz1Error Dz1HeadingConfidence_00100_fromASN(Dz1HeadingConfidence_00100* dst, HeadingConfidence_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1HeadingConfidence_00100)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1HeadingConfidence_00100, HeadingConfidence_00100)

Dz1Error Dz1HeadingConfidence_00100_toASN(HeadingConfidence_00100* dst, Dz1HeadingConfidence_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (HeadingConfidence_00100)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1HeadingConfidence_00100, HeadingConfidence_00100)
// Dz1HeadingConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SpeedConfidence_00100
static struct Dz1SpeedConfidence_00100MapA
{
	str_t str;
	Dz1SpeedConfidence_00100 v;
} Dz1SpeedConfidence_00100MapA[] =
{
	{ (char*)"unavailable", Dz1SpeedConfidence_00100_unavailable },
	{ (char*)"prec100ms", Dz1SpeedConfidence_00100_prec100ms },
	{ (char*)"prec10ms", Dz1SpeedConfidence_00100_prec10ms },
	{ (char*)"prec5ms", Dz1SpeedConfidence_00100_prec5ms },
	{ (char*)"prec1ms", Dz1SpeedConfidence_00100_prec1ms },
	{ (char*)"prec0_1ms", Dz1SpeedConfidence_00100_prec0_1ms },
	{ (char*)"prec0_05ms", Dz1SpeedConfidence_00100_prec0_05ms },
	{ (char*)"prec0_01ms", Dz1SpeedConfidence_00100_prec0_01ms },
	{ NULL, Dz1SpeedConfidence_00100_max }
};

str_t Dz1SpeedConfidence_00100StrA(Dz1SpeedConfidence_00100 v)
{
	struct Dz1SpeedConfidence_00100MapA* i = NULL;
	for (i = Dz1SpeedConfidence_00100MapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1SpeedConfidence_00100 Dz1SpeedConfidence_00100FromStrA(str_t str)
{
	struct Dz1SpeedConfidence_00100MapA* i = NULL;
	for (i = Dz1SpeedConfidence_00100MapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1SpeedConfidence_00100_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1SpeedConfidence_00100MapW
{
	wstr_t str;
	Dz1SpeedConfidence_00100 v;
} Dz1SpeedConfidence_00100MapW[] =
{
	{ (wchar_t*)L"unavailable", Dz1SpeedConfidence_00100_unavailable },
	{ (wchar_t*)L"prec100ms", Dz1SpeedConfidence_00100_prec100ms },
	{ (wchar_t*)L"prec10ms", Dz1SpeedConfidence_00100_prec10ms },
	{ (wchar_t*)L"prec5ms", Dz1SpeedConfidence_00100_prec5ms },
	{ (wchar_t*)L"prec1ms", Dz1SpeedConfidence_00100_prec1ms },
	{ (wchar_t*)L"prec0_1ms", Dz1SpeedConfidence_00100_prec0_1ms },
	{ (wchar_t*)L"prec0_05ms", Dz1SpeedConfidence_00100_prec0_05ms },
	{ (wchar_t*)L"prec0_01ms", Dz1SpeedConfidence_00100_prec0_01ms },
	{ NULL, Dz1SpeedConfidence_00100_max }
};

wstr_t Dz1SpeedConfidence_00100StrW(Dz1SpeedConfidence_00100 v)
{
	struct Dz1SpeedConfidence_00100MapW* i = NULL;
	for (i = Dz1SpeedConfidence_00100MapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1SpeedConfidence_00100 Dz1SpeedConfidence_00100FromStrW(wstr_t str)
{
	struct Dz1SpeedConfidence_00100MapW* i = NULL;
	for (i = Dz1SpeedConfidence_00100MapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1SpeedConfidence_00100_max;
}
#endif // UNIX_SYSTEM

Dz1SpeedConfidence_00100* Dz1SpeedConfidence_00100_new(Dz1SpeedConfidence_00100* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1SpeedConfidence_00100* __internal_ret = (Dz1SpeedConfidence_00100*)Dz1Calloc(sizeof(Dz1SpeedConfidence_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1SpeedConfidence_00100_dump(Dz1SpeedConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1SpeedConfidence_00100Str(*v));
}
void Dz1SpeedConfidence_00100_fdump(FILE* fp, Dz1SpeedConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1SpeedConfidence_00100Str(*v));
}
Dz1Error Dz1SpeedConfidence_00100_fromASN(Dz1SpeedConfidence_00100* dst, SpeedConfidence_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1SpeedConfidence_00100)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1SpeedConfidence_00100, SpeedConfidence_00100)

Dz1Error Dz1SpeedConfidence_00100_toASN(SpeedConfidence_00100* dst, Dz1SpeedConfidence_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (SpeedConfidence_00100)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1SpeedConfidence_00100, SpeedConfidence_00100)
// Dz1SpeedConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ThrottleConfidence_00100
static struct Dz1ThrottleConfidence_00100MapA
{
	str_t str;
	Dz1ThrottleConfidence_00100 v;
} Dz1ThrottleConfidence_00100MapA[] =
{
	{ (char*)"unavailable", Dz1ThrottleConfidence_00100_unavailable },
	{ (char*)"prec10percent", Dz1ThrottleConfidence_00100_prec10percent },
	{ (char*)"prec1percent", Dz1ThrottleConfidence_00100_prec1percent },
	{ (char*)"prec0_5percent", Dz1ThrottleConfidence_00100_prec0_5percent },
	{ NULL, Dz1ThrottleConfidence_00100_max }
};

str_t Dz1ThrottleConfidence_00100StrA(Dz1ThrottleConfidence_00100 v)
{
	struct Dz1ThrottleConfidence_00100MapA* i = NULL;
	for (i = Dz1ThrottleConfidence_00100MapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1ThrottleConfidence_00100 Dz1ThrottleConfidence_00100FromStrA(str_t str)
{
	struct Dz1ThrottleConfidence_00100MapA* i = NULL;
	for (i = Dz1ThrottleConfidence_00100MapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1ThrottleConfidence_00100_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1ThrottleConfidence_00100MapW
{
	wstr_t str;
	Dz1ThrottleConfidence_00100 v;
} Dz1ThrottleConfidence_00100MapW[] =
{
	{ (wchar_t*)L"unavailable", Dz1ThrottleConfidence_00100_unavailable },
	{ (wchar_t*)L"prec10percent", Dz1ThrottleConfidence_00100_prec10percent },
	{ (wchar_t*)L"prec1percent", Dz1ThrottleConfidence_00100_prec1percent },
	{ (wchar_t*)L"prec0_5percent", Dz1ThrottleConfidence_00100_prec0_5percent },
	{ NULL, Dz1ThrottleConfidence_00100_max }
};

wstr_t Dz1ThrottleConfidence_00100StrW(Dz1ThrottleConfidence_00100 v)
{
	struct Dz1ThrottleConfidence_00100MapW* i = NULL;
	for (i = Dz1ThrottleConfidence_00100MapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1ThrottleConfidence_00100 Dz1ThrottleConfidence_00100FromStrW(wstr_t str)
{
	struct Dz1ThrottleConfidence_00100MapW* i = NULL;
	for (i = Dz1ThrottleConfidence_00100MapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1ThrottleConfidence_00100_max;
}
#endif // UNIX_SYSTEM

Dz1ThrottleConfidence_00100* Dz1ThrottleConfidence_00100_new(Dz1ThrottleConfidence_00100* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ThrottleConfidence_00100* __internal_ret = (Dz1ThrottleConfidence_00100*)Dz1Calloc(sizeof(Dz1ThrottleConfidence_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1ThrottleConfidence_00100_dump(Dz1ThrottleConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1ThrottleConfidence_00100Str(*v));
}
void Dz1ThrottleConfidence_00100_fdump(FILE* fp, Dz1ThrottleConfidence_00100* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1ThrottleConfidence_00100Str(*v));
}
Dz1Error Dz1ThrottleConfidence_00100_fromASN(Dz1ThrottleConfidence_00100* dst, ThrottleConfidence_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1ThrottleConfidence_00100)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1ThrottleConfidence_00100, ThrottleConfidence_00100)

Dz1Error Dz1ThrottleConfidence_00100_toASN(ThrottleConfidence_00100* dst, Dz1ThrottleConfidence_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (ThrottleConfidence_00100)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1ThrottleConfidence_00100, ThrottleConfidence_00100)
// Dz1ThrottleConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1FullPositionVector_00100
Dz1FullPositionVector_00100* Dz1FullPositionVector_00100_new(Dz1Longitude_00100 lon,
	Dz1Latitude_00100 lat, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1FullPositionVector_00100* __internal_ret = (Dz1FullPositionVector_00100*)Dz1Calloc(sizeof(Dz1FullPositionVector_00100), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1FullPositionVector_00100_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->lon = lon;
		__internal_ret->lat = lat;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1FullPositionVector_00100_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1FullPositionVector_00100_copy(Dz1FullPositionVector_00100* dst, Dz1FullPositionVector_00100* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->utcTime && (dst->utcTime = Dz1DDateTime_00100_clone(src->utcTime, errp)) == NULL) ERR_OUT(errp);
	else if (src->elevation && (dst->elevation = Dz1Elevation_00100_clone(src->elevation, errp)) == NULL) ERR_OUT(errp);
	else if (src->heading && (dst->heading = Dz1Heading_00100_clone(src->heading, errp)) == NULL) ERR_OUT(errp);
	else if (src->speed && (dst->speed = Dz1TransmissionAndSpeed_00100_clone(src->speed, errp)) == NULL) ERR_OUT(errp);
	else if (src->posAccuracy && (dst->posAccuracy = Dz1PositionalAccuracy_00100_clone(src->posAccuracy, errp)) == NULL) ERR_OUT(errp);
	else if (src->timeConfidence && (dst->timeConfidence = Dz1TimeConfidence_00100_clone(src->timeConfidence, errp)) == NULL) ERR_OUT(errp);
	else if (src->posConfidence && (dst->posConfidence = Dz1PositionConfidenceSet_00100_clone(src->posConfidence, errp)) == NULL) ERR_OUT(errp);
	else if (src->speedConfidence && (dst->speedConfidence = Dz1SpeedandHeadingandThrottleConfidence_00100_clone(src->speedConfidence, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->lon = src->lon;
		dst->lat = src->lat;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1FullPositionVector_00100* Dz1FullPositionVector_00100_clone(Dz1FullPositionVector_00100* src, Dz1Error* err)
{
	Dz1FullPositionVector_00100* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1FullPositionVector_00100*)Dz1Calloc(sizeof(Dz1FullPositionVector_00100), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1FullPositionVector_00100_delAndSetNull, (void*)&dst);
		if (Dz1FullPositionVector_00100_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1FullPositionVector_00100_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1FullPositionVector_00100_purge(Dz1FullPositionVector_00100* p)
{
	if (p == NULL) return;
	Dz1DDateTime_00100_del(p->utcTime);
	Dz1Elevation_00100_del(p->elevation);
	Dz1Heading_00100_del(p->heading);
	Dz1TransmissionAndSpeed_00100_del(p->speed);
	Dz1PositionalAccuracy_00100_del(p->posAccuracy);
	Dz1TimeConfidence_00100_del(p->timeConfidence);
	Dz1PositionConfidenceSet_00100_del(p->posConfidence);
	Dz1SpeedandHeadingandThrottleConfidence_00100_del(p->speedConfidence);
}

void Dz1FullPositionVector_00100_del(Dz1FullPositionVector_00100* p)
{
	if (p == NULL) return;
	Dz1FullPositionVector_00100_purge(p);
	Dz1Free(p);
}

void Dz1FullPositionVector_00100_dump(Dz1FullPositionVector_00100* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("utcTime = ")); Dz1DDateTime_00100_dump(p->utcTime, tab);
		Dz1Thread_tprintf(tab, Dz1T("lon = ")); Dz1Longitude_00100_dump(&p->lon, tab);
		Dz1Thread_tprintf(tab, Dz1T("lat = ")); Dz1Latitude_00100_dump(&p->lat, tab);
		Dz1Thread_tprintf(tab, Dz1T("elevation = ")); Dz1Elevation_00100_dump(p->elevation, tab);
		Dz1Thread_tprintf(tab, Dz1T("heading = ")); Dz1Heading_00100_dump(p->heading, tab);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("speed = ")); Dz1TransmissionAndSpeed_00100_dump(p->speed, tab);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("posAccuracy = ")); Dz1PositionalAccuracy_00100_dump(p->posAccuracy, tab);
		if (p->timeConfidence == NULL) Dz1Thread_tprintf(tab, Dz1T("timeConfidence = NULL\n"));
		else Dz1Thread_tprintf(tab, Dz1T("timeConfidence = %s(%d)\n"), Dz1TimeConfidence_00100Str(*p->timeConfidence), *p->timeConfidence);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("posConfidence = ")); Dz1PositionConfidenceSet_00100_dump(p->posConfidence, tab);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("speedConfidence = ")); Dz1SpeedandHeadingandThrottleConfidence_00100_dump(p->speedConfidence, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1FullPositionVector_00100_fdump(FILE* fp, Dz1FullPositionVector_00100* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("utcTime = ")); Dz1DDateTime_00100_fdump(fp, p->utcTime, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("lon = ")); Dz1Longitude_00100_fdump(fp, &p->lon, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("lat = ")); Dz1Latitude_00100_fdump(fp, &p->lat, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("elevation = ")); Dz1Elevation_00100_fdump(fp, p->elevation, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("heading = ")); Dz1Heading_00100_fdump(fp, p->heading, tab);
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("speed = ")); Dz1TransmissionAndSpeed_00100_fdump(fp, p->speed, tab);
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("posAccuracy = ")); Dz1PositionalAccuracy_00100_fdump(fp, p->posAccuracy, tab);
		if (p->timeConfidence == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("timeConfidence = NULL\n"));
		else Dz1Thread_ftprintf(fp, tab, Dz1T("timeConfidence = %s(%d)\n"), Dz1TimeConfidence_00100Str(*p->timeConfidence), *p->timeConfidence);
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("posConfidence = ")); Dz1PositionConfidenceSet_00100_fdump(fp, p->posConfidence, tab);
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("speedConfidence = ")); Dz1SpeedandHeadingandThrottleConfidence_00100_fdump(fp, p->speedConfidence, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1FullPositionVector_00100_fromASN(Dz1FullPositionVector_00100* dst, FullPositionVector_00100* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1TimeConfidence_00100 timeConfidence = (Dz1TimeConfidence_00100)(src->DEF_FullPositionVector_00100_timeConfidence ? src->timeConfidence : 0);
		if (src->DEF_FullPositionVector_00100_utcTime && (dst->utcTime = Dz1DDateTime_00100_newFromASN(src->utcTime, &err)) == NULL) ERR_OUT(&err);
		else if ((err = s32_t_fromASN(&dst->lon, &src->lon)).code) { Dz1Thread_printf("lon : "); ERR_OUT(&err); }
		else if ((err = s32_t_fromASN(&dst->lat, &src->lat)).code) { Dz1Thread_printf("lat : "); ERR_OUT(&err); }
		else if (src->DEF_FullPositionVector_00100_elevation && (dst->elevation = s32_t_newFromASN(&src->elevation, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_FullPositionVector_00100_heading && (dst->heading = u16_t_newFromASN(&src->heading, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_FullPositionVector_00100_speed && (dst->speed = Dz1TransmissionAndSpeed_00100_newFromASN(src->speed, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_FullPositionVector_00100_posAccuracy && (dst->posAccuracy = Dz1PositionalAccuracy_00100_newFromASN(src->posAccuracy, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_FullPositionVector_00100_timeConfidence && (dst->timeConfidence = Dz1TimeConfidence_00100_new(&timeConfidence, &err)) == NULL) { Dz1Thread_printf("timeConfidence : "); ERR_OUT(&err); }
		else if (src->DEF_FullPositionVector_00100_posConfidence && (dst->posConfidence = Dz1PositionConfidenceSet_00100_newFromASN(src->posConfidence, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_FullPositionVector_00100_speedConfidence && (dst->speedConfidence = Dz1SpeedandHeadingandThrottleConfidence_00100_newFromASN(src->speedConfidence, &err)) == NULL) ERR_OUT(&err);
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1FullPositionVector_00100, FullPositionVector_00100)

Dz1Error Dz1FullPositionVector_00100_toASN(FullPositionVector_00100* dst, Dz1FullPositionVector_00100* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->DEF_FullPositionVector_00100_utcTime = src->utcTime ? 1 : 0) == 1 && (dst->utcTime = Dz1DDateTime_00100_toNewASN(src->utcTime, ws, &err)) == NULL) { Dz1Thread_printf("utcTime : "); ERR_OUT(&err); }
		else if ((err = s32_t_toASN(&dst->lon, &src->lon, ws)).code) { Dz1Thread_printf("lon : "); ERR_OUT(&err); }
		else if ((err = s32_t_toASN(&dst->lat, &src->lat, ws)).code) { Dz1Thread_printf("lat : "); ERR_OUT(&err); }
		else if ((dst->DEF_FullPositionVector_00100_elevation = src->elevation ? 1 : 0) == 1 && (err = s32_t_toASN(&dst->elevation, src->elevation, ws)).code) { Dz1Thread_printf("elevation : "); ERR_OUT(&err); }
		else if ((dst->DEF_FullPositionVector_00100_heading = src->heading ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->heading, src->heading, ws)).code) { Dz1Thread_printf("heading : "); ERR_OUT(&err); }
		else if ((dst->DEF_FullPositionVector_00100_speed = src->speed ? 1 : 0) == 1 && (dst->speed = Dz1TransmissionAndSpeed_00100_toNewASN(src->speed, ws, &err)) == NULL) { Dz1Thread_printf("speed : "); ERR_OUT(&err); }
		else if ((dst->DEF_FullPositionVector_00100_posAccuracy = src->posAccuracy ? 1 : 0) == 1 && (dst->posAccuracy = Dz1PositionalAccuracy_00100_toNewASN(src->posAccuracy, ws, &err)) == NULL) { Dz1Thread_printf("posAccuracy : "); ERR_OUT(&err); }
		else if ((dst->DEF_FullPositionVector_00100_posConfidence = src->posConfidence ? 1 : 0) == 1 && (dst->posConfidence = Dz1PositionConfidenceSet_00100_toNewASN(src->posConfidence, ws, &err)) == NULL) { Dz1Thread_printf("posConfidence : "); ERR_OUT(&err); }
		else if ((dst->DEF_FullPositionVector_00100_speedConfidence = src->speedConfidence ? 1 : 0) == 1 && (dst->speedConfidence = Dz1SpeedandHeadingandThrottleConfidence_00100_toNewASN(src->speedConfidence, ws, &err)) == NULL) { Dz1Thread_printf("speedConfidence : "); ERR_OUT(&err); }
		else
		{
			if ((dst->DEF_FullPositionVector_00100_timeConfidence = src->timeConfidence ? 1 : 0) == 1) dst->timeConfidence = *src->timeConfidence;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1FullPositionVector_00100, FullPositionVector_00100)
// Dz1FullPositionVector_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionInfo_incident_Detected_Type
static struct Dz1IncidentDetectionInfo_incident_Detected_TypeMapA
{
	str_t str;
	Dz1IncidentDetectionInfo_incident_Detected_Type v;
} Dz1IncidentDetectionInfo_incident_Detected_TypeMapA[] =
{
	{ (char*)"stalledVehicle", Dz1IncidentDetectionInfo_incident_Detected_Type_stalledVehicle },
	{ (char*)"reverseDriving", Dz1IncidentDetectionInfo_incident_Detected_Type_reverseDriving },
	{ (char*)"pedestrian", Dz1IncidentDetectionInfo_incident_Detected_Type_pedestrian },
	{ (char*)"roadwayDebris", Dz1IncidentDetectionInfo_incident_Detected_Type_roadwayDebris },
	{ (char*)"rireSmoke", Dz1IncidentDetectionInfo_incident_Detected_Type_rireSmoke },
	{ (char*)"roadShouldersVehicle", Dz1IncidentDetectionInfo_incident_Detected_Type_roadShouldersVehicle },
	{ (char*)"roadkill", Dz1IncidentDetectionInfo_incident_Detected_Type_roadkill },
	{ (char*)"slowVehicle", Dz1IncidentDetectionInfo_incident_Detected_Type_slowVehicle },
	{ (char*)"delayCongested", Dz1IncidentDetectionInfo_incident_Detected_Type_delayCongested },
	{ NULL, Dz1IncidentDetectionInfo_incident_Detected_Type_max }
};

str_t Dz1IncidentDetectionInfo_incident_Detected_TypeStrA(Dz1IncidentDetectionInfo_incident_Detected_Type v)
{
	struct Dz1IncidentDetectionInfo_incident_Detected_TypeMapA* i = NULL;
	for (i = Dz1IncidentDetectionInfo_incident_Detected_TypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentDetectionInfo_incident_Detected_Type Dz1IncidentDetectionInfo_incident_Detected_TypeFromStrA(str_t str)
{
	struct Dz1IncidentDetectionInfo_incident_Detected_TypeMapA* i = NULL;
	for (i = Dz1IncidentDetectionInfo_incident_Detected_TypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1IncidentDetectionInfo_incident_Detected_Type_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1IncidentDetectionInfo_incident_Detected_TypeMapW
{
	wstr_t str;
	Dz1IncidentDetectionInfo_incident_Detected_Type v;
} Dz1IncidentDetectionInfo_incident_Detected_TypeMapW[] =
{
	{ (wchar_t*)L"stalledVehicle", Dz1IncidentDetectionInfo_incident_Detected_Type_stalledVehicle },
	{ (wchar_t*)L"reverseDriving", Dz1IncidentDetectionInfo_incident_Detected_Type_reverseDriving },
	{ (wchar_t*)L"pedestrian", Dz1IncidentDetectionInfo_incident_Detected_Type_pedestrian },
	{ (wchar_t*)L"roadwayDebris", Dz1IncidentDetectionInfo_incident_Detected_Type_roadwayDebris },
	{ (wchar_t*)L"rireSmoke", Dz1IncidentDetectionInfo_incident_Detected_Type_rireSmoke },
	{ (wchar_t*)L"roadShouldersVehicle", Dz1IncidentDetectionInfo_incident_Detected_Type_roadShouldersVehicle },
	{ (wchar_t*)L"roadkill", Dz1IncidentDetectionInfo_incident_Detected_Type_roadkill },
	{ (wchar_t*)L"slowVehicle", Dz1IncidentDetectionInfo_incident_Detected_Type_slowVehicle },
	{ (wchar_t*)L"delayCongested", Dz1IncidentDetectionInfo_incident_Detected_Type_delayCongested },
	{ NULL, Dz1IncidentDetectionInfo_incident_Detected_Type_max }
};

wstr_t Dz1IncidentDetectionInfo_incident_Detected_TypeStrW(Dz1IncidentDetectionInfo_incident_Detected_Type v)
{
	struct Dz1IncidentDetectionInfo_incident_Detected_TypeMapW* i = NULL;
	for (i = Dz1IncidentDetectionInfo_incident_Detected_TypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentDetectionInfo_incident_Detected_Type Dz1IncidentDetectionInfo_incident_Detected_TypeFromStrW(wstr_t str)
{
	struct Dz1IncidentDetectionInfo_incident_Detected_TypeMapW* i = NULL;
	for (i = Dz1IncidentDetectionInfo_incident_Detected_TypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1IncidentDetectionInfo_incident_Detected_Type_max;
}
#endif // UNIX_SYSTEM

Dz1IncidentDetectionInfo_incident_Detected_Type* Dz1IncidentDetectionInfo_incident_Detected_Type_new(Dz1IncidentDetectionInfo_incident_Detected_Type* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentDetectionInfo_incident_Detected_Type* __internal_ret = (Dz1IncidentDetectionInfo_incident_Detected_Type*)Dz1Calloc(sizeof(Dz1IncidentDetectionInfo_incident_Detected_Type), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1IncidentDetectionInfo_incident_Detected_Type_dump(Dz1IncidentDetectionInfo_incident_Detected_Type* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1IncidentDetectionInfo_incident_Detected_TypeStr(*v));
}
void Dz1IncidentDetectionInfo_incident_Detected_Type_fdump(FILE* fp, Dz1IncidentDetectionInfo_incident_Detected_Type* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1IncidentDetectionInfo_incident_Detected_TypeStr(*v));
}
Dz1Error Dz1IncidentDetectionInfo_incident_Detected_Type_fromASN(Dz1IncidentDetectionInfo_incident_Detected_Type* dst, IncidentDetectionInfo_incident_Detected_Type* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1IncidentDetectionInfo_incident_Detected_Type)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1IncidentDetectionInfo_incident_Detected_Type, IncidentDetectionInfo_incident_Detected_Type)

Dz1Error Dz1IncidentDetectionInfo_incident_Detected_Type_toASN(IncidentDetectionInfo_incident_Detected_Type* dst, Dz1IncidentDetectionInfo_incident_Detected_Type* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (IncidentDetectionInfo_incident_Detected_Type)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1IncidentDetectionInfo_incident_Detected_Type, IncidentDetectionInfo_incident_Detected_Type)
// Dz1IncidentDetectionInfo_incident_Detected_Type
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NMEACoord_compass
static struct Dz1NMEACoord_compassMapA
{
	str_t str;
	Dz1NMEACoord_compass v;
} Dz1NMEACoord_compassMapA[] =
{
	{ (char*)"north", Dz1NMEACoord_compass_north },
	{ (char*)"south", Dz1NMEACoord_compass_south },
	{ NULL, Dz1NMEACoord_compass_max }
};

str_t Dz1NMEACoord_compassStrA(Dz1NMEACoord_compass v)
{
	struct Dz1NMEACoord_compassMapA* i = NULL;
	for (i = Dz1NMEACoord_compassMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1NMEACoord_compass Dz1NMEACoord_compassFromStrA(str_t str)
{
	struct Dz1NMEACoord_compassMapA* i = NULL;
	for (i = Dz1NMEACoord_compassMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1NMEACoord_compass_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1NMEACoord_compassMapW
{
	wstr_t str;
	Dz1NMEACoord_compass v;
} Dz1NMEACoord_compassMapW[] =
{
	{ (wchar_t*)L"north", Dz1NMEACoord_compass_north },
	{ (wchar_t*)L"south", Dz1NMEACoord_compass_south },
	{ NULL, Dz1NMEACoord_compass_max }
};

wstr_t Dz1NMEACoord_compassStrW(Dz1NMEACoord_compass v)
{
	struct Dz1NMEACoord_compassMapW* i = NULL;
	for (i = Dz1NMEACoord_compassMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1NMEACoord_compass Dz1NMEACoord_compassFromStrW(wstr_t str)
{
	struct Dz1NMEACoord_compassMapW* i = NULL;
	for (i = Dz1NMEACoord_compassMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1NMEACoord_compass_max;
}
#endif // UNIX_SYSTEM

Dz1NMEACoord_compass* Dz1NMEACoord_compass_new(Dz1NMEACoord_compass* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1NMEACoord_compass* __internal_ret = (Dz1NMEACoord_compass*)Dz1Calloc(sizeof(Dz1NMEACoord_compass), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1NMEACoord_compass_dump(Dz1NMEACoord_compass* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1NMEACoord_compassStr(*v));
}
void Dz1NMEACoord_compass_fdump(FILE* fp, Dz1NMEACoord_compass* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1NMEACoord_compassStr(*v));
}
Dz1Error Dz1NMEACoord_compass_fromASN(Dz1NMEACoord_compass* dst, NMEACoord_compass* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1NMEACoord_compass)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1NMEACoord_compass, NMEACoord_compass)

Dz1Error Dz1NMEACoord_compass_toASN(NMEACoord_compass* dst, Dz1NMEACoord_compass* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (NMEACoord_compass)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1NMEACoord_compass, NMEACoord_compass)
// Dz1NMEACoord_compass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NMEACoord_latitude
Dz1NMEACoord_latitude* Dz1NMEACoord_latitude_new(s64_t integerValue,
	s64_t fractionValue,
	u8_t fracSize,
	Dz1NMEACoord_compass compass, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1NMEACoord_latitude* __internal_ret = (Dz1NMEACoord_latitude*)Dz1Calloc(sizeof(Dz1NMEACoord_latitude), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_latitude_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->integerValue = integerValue;
		__internal_ret->fractionValue = fractionValue;
		__internal_ret->fracSize = fracSize;
		__internal_ret->compass = compass;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1NMEACoord_latitude_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1NMEACoord_latitude_copy(Dz1NMEACoord_latitude* dst, Dz1NMEACoord_latitude* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->integerValue = src->integerValue;
		dst->fractionValue = src->fractionValue;
		dst->fracSize = src->fracSize;
		dst->compass = src->compass;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1NMEACoord_latitude* Dz1NMEACoord_latitude_clone(Dz1NMEACoord_latitude* src, Dz1Error* err)
{
	Dz1NMEACoord_latitude* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1NMEACoord_latitude*)Dz1Calloc(sizeof(Dz1NMEACoord_latitude), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_latitude_delAndSetNull, (void*)&dst);
		if (Dz1NMEACoord_latitude_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1NMEACoord_latitude_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1NMEACoord_latitude_purge(Dz1NMEACoord_latitude* p)
{
	if (p == NULL) return;
}

void Dz1NMEACoord_latitude_del(Dz1NMEACoord_latitude* p)
{
	if (p == NULL) return;
	Dz1NMEACoord_latitude_purge(p);
	Dz1Free(p);
}

void Dz1NMEACoord_latitude_dump(Dz1NMEACoord_latitude* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("integerValue = ")); Dz1s64_dump(&p->integerValue, tab);
		Dz1Thread_tprintf(tab, Dz1T("fractionValue = ")); Dz1s64_dump(&p->fractionValue, tab);
		Dz1Thread_tprintf(tab, Dz1T("fracSize = ")); Dz1u8_dump(&p->fracSize, tab);
		Dz1Thread_tprintf(tab, Dz1T("compass = %s(%d)\n"), Dz1NMEACoord_compassStr(p->compass), p->compass);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1NMEACoord_latitude_fdump(FILE* fp, Dz1NMEACoord_latitude* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("integerValue = ")); Dz1s64_fdump(fp, &p->integerValue, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("fractionValue = ")); Dz1s64_fdump(fp, &p->fractionValue, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("fracSize = ")); Dz1u8_fdump(fp, &p->fracSize, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("compass = %s(%d)\n"), Dz1NMEACoord_compassStr(p->compass), p->compass);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1NMEACoord_latitude_fromASN(Dz1NMEACoord_latitude* dst, NMEACoord_latitude* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = s64_t_fromASN(&dst->integerValue, &src->integerValue)).code) { Dz1Thread_printf("integerValue : "); ERR_OUT(&err); }
		else if ((err = s64_t_fromASN(&dst->fractionValue, &src->fractionValue)).code) { Dz1Thread_printf("fractionValue : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->fracSize, &src->fracSize)).code) { Dz1Thread_printf("fracSize : "); ERR_OUT(&err); }
		else
		{
			dst->compass = (Dz1NMEACoord_compass)src->compass;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1NMEACoord_latitude, NMEACoord_latitude)

Dz1Error Dz1NMEACoord_latitude_toASN(NMEACoord_latitude* dst, Dz1NMEACoord_latitude* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = s64_t_toASN(&dst->integerValue, &src->integerValue, ws)).code) { Dz1Thread_printf("integerValue : "); ERR_OUT(&err); }
		else if ((err = s64_t_toASN(&dst->fractionValue, &src->fractionValue, ws)).code) { Dz1Thread_printf("fractionValue : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->fracSize, &src->fracSize, ws)).code) { Dz1Thread_printf("fracSize : "); ERR_OUT(&err); }
		else
		{
			dst->compass = src->compass;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1NMEACoord_latitude, NMEACoord_latitude)
// Dz1NMEACoord_latitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NMEACoord_longitude
Dz1NMEACoord_longitude* Dz1NMEACoord_longitude_new(s64_t integerValue,
	s64_t fractionValue,
	u8_t fracSize,
	Dz1NMEACoord_compass compass, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1NMEACoord_longitude* __internal_ret = (Dz1NMEACoord_longitude*)Dz1Calloc(sizeof(Dz1NMEACoord_longitude), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_longitude_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->integerValue = integerValue;
		__internal_ret->fractionValue = fractionValue;
		__internal_ret->fracSize = fracSize;
		__internal_ret->compass = compass;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1NMEACoord_longitude_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1NMEACoord_longitude_copy(Dz1NMEACoord_longitude* dst, Dz1NMEACoord_longitude* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->integerValue = src->integerValue;
		dst->fractionValue = src->fractionValue;
		dst->fracSize = src->fracSize;
		dst->compass = src->compass;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1NMEACoord_longitude* Dz1NMEACoord_longitude_clone(Dz1NMEACoord_longitude* src, Dz1Error* err)
{
	Dz1NMEACoord_longitude* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1NMEACoord_longitude*)Dz1Calloc(sizeof(Dz1NMEACoord_longitude), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_longitude_delAndSetNull, (void*)&dst);
		if (Dz1NMEACoord_longitude_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1NMEACoord_longitude_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1NMEACoord_longitude_purge(Dz1NMEACoord_longitude* p)
{
	if (p == NULL) return;
}

void Dz1NMEACoord_longitude_del(Dz1NMEACoord_longitude* p)
{
	if (p == NULL) return;
	Dz1NMEACoord_longitude_purge(p);
	Dz1Free(p);
}

void Dz1NMEACoord_longitude_dump(Dz1NMEACoord_longitude* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("integerValue = ")); Dz1s64_dump(&p->integerValue, tab);
		Dz1Thread_tprintf(tab, Dz1T("fractionValue = ")); Dz1s64_dump(&p->fractionValue, tab);
		Dz1Thread_tprintf(tab, Dz1T("fracSize = ")); Dz1u8_dump(&p->fracSize, tab);
		Dz1Thread_tprintf(tab, Dz1T("compass = %s(%d)\n"), Dz1NMEACoord_compassStr(p->compass), p->compass);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1NMEACoord_longitude_fdump(FILE* fp, Dz1NMEACoord_longitude* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("integerValue = ")); Dz1s64_fdump(fp, &p->integerValue, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("fractionValue = ")); Dz1s64_fdump(fp, &p->fractionValue, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("fracSize = ")); Dz1u8_fdump(fp, &p->fracSize, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("compass = %s(%d)\n"), Dz1NMEACoord_compassStr(p->compass), p->compass);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1NMEACoord_longitude_fromASN(Dz1NMEACoord_longitude* dst, NMEACoord_longitude* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = s64_t_fromASN(&dst->integerValue, &src->integerValue)).code) { Dz1Thread_printf("integerValue : "); ERR_OUT(&err); }
		else if ((err = s64_t_fromASN(&dst->fractionValue, &src->fractionValue)).code) { Dz1Thread_printf("fractionValue : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->fracSize, &src->fracSize)).code) { Dz1Thread_printf("fracSize : "); ERR_OUT(&err); }
		else
		{
			dst->compass = (Dz1NMEACoord_compass)src->compass;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1NMEACoord_longitude, NMEACoord_longitude)

Dz1Error Dz1NMEACoord_longitude_toASN(NMEACoord_longitude* dst, Dz1NMEACoord_longitude* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = s64_t_toASN(&dst->integerValue, &src->integerValue, ws)).code) { Dz1Thread_printf("integerValue : "); ERR_OUT(&err); }
		else if ((err = s64_t_toASN(&dst->fractionValue, &src->fractionValue, ws)).code) { Dz1Thread_printf("fractionValue : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->fracSize, &src->fracSize, ws)).code) { Dz1Thread_printf("fracSize : "); ERR_OUT(&err); }
		else
		{
			dst->compass = src->compass;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1NMEACoord_longitude, NMEACoord_longitude)
// Dz1NMEACoord_longitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NMEACoord
Dz1NMEACoord* Dz1NMEACoord_new(Dz1NMEACoord_latitude* latitude,
	Dz1NMEACoord_longitude* longitude, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1NMEACoord* __internal_ret = (Dz1NMEACoord*)Dz1Calloc(sizeof(Dz1NMEACoord), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->latitude = latitude;
		__internal_ret->longitude = longitude;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1NMEACoord_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1NMEACoord_copy(Dz1NMEACoord* dst, Dz1NMEACoord* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->latitude && (dst->latitude = Dz1NMEACoord_latitude_clone(src->latitude, errp)) == NULL) ERR_OUT(errp);
	else if (src->longitude && (dst->longitude = Dz1NMEACoord_longitude_clone(src->longitude, errp)) == NULL) ERR_OUT(errp);
	else if (src->optData && (dst->optData = Dz1Asn1OctetStr_clone(src->optData, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1NMEACoord* Dz1NMEACoord_clone(Dz1NMEACoord* src, Dz1Error* err)
{
	Dz1NMEACoord* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1NMEACoord*)Dz1Calloc(sizeof(Dz1NMEACoord), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_delAndSetNull, (void*)&dst);
		if (Dz1NMEACoord_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1NMEACoord_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1NMEACoord_purge(Dz1NMEACoord* p)
{
	if (p == NULL) return;
	Dz1NMEACoord_latitude_del(p->latitude);
	Dz1NMEACoord_longitude_del(p->longitude);
	Dz1Asn1OctetStr_del(p->optData);
}

void Dz1NMEACoord_del(Dz1NMEACoord* p)
{
	if (p == NULL) return;
	Dz1NMEACoord_purge(p);
	Dz1Free(p);
}

void Dz1NMEACoord_dump(Dz1NMEACoord* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("latitude = ")); Dz1NMEACoord_latitude_dump(p->latitude, tab);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("longitude = ")); Dz1NMEACoord_longitude_dump(p->longitude, tab);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("optData = ")); Dz1Asn1OctetStr_dump(p->optData, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1NMEACoord_fdump(FILE* fp, Dz1NMEACoord* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("latitude = ")); Dz1NMEACoord_latitude_fdump(fp, p->latitude, tab);
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("longitude = ")); Dz1NMEACoord_longitude_fdump(fp, p->longitude, tab);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_ftprintf(fp, tab, Dz1T("optData = ")); Dz1Asn1OctetStr_fdump(fp, p->optData, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1NMEACoord_fromASN(Dz1NMEACoord* dst, NMEACoord* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->latitude = Dz1NMEACoord_latitude_newFromASN(src->latitude, &err)) == NULL) { Dz1Thread_printf("latitude : "); ERR_OUT(&err); }
		else if ((dst->longitude = Dz1NMEACoord_longitude_newFromASN(src->longitude, &err)) == NULL) { Dz1Thread_printf("longitude : "); ERR_OUT(&err); }
		else if (src->DEF_NMEACoord_optData && (dst->optData = Dz1Asn1OctetStr_newFromASN(&src->optData, &err)) == NULL) ERR_OUT(&err);
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1NMEACoord, NMEACoord)

Dz1Error Dz1NMEACoord_toASN(NMEACoord* dst, Dz1NMEACoord* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->latitude = Dz1NMEACoord_latitude_toNewASN(src->latitude, ws, &err)) == NULL) { Dz1Thread_printf("latitude : "); ERR_OUT(&err); }
		else if ((dst->longitude = Dz1NMEACoord_longitude_toNewASN(src->longitude, ws, &err)) == NULL) { Dz1Thread_printf("longitude : "); ERR_OUT(&err); }
		else if ((dst->DEF_NMEACoord_optData = src->optData ? 1 : 0) == 1 && (err = Dz1Asn1OctetStr_toASN(&dst->optData, src->optData, ws)).code) { Dz1Thread_printf("optData : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1NMEACoord, NMEACoord)
// Dz1NMEACoord
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionInfo
Dz1IncidentDetectionInfo* Dz1IncidentDetectionInfo_new(Dz1Asn1VisibleStr* incident_Detected_Time,
	Dz1IncidentDetectionInfo_incident_Detected_Type incident_Detected_Type,
	Dz1NMEACoord* incident_Detected_Site,
	u16_t detected_Object_Distance,
	u16_t detected_Object_Angle,
	u16_t detected_Object_Speed, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentDetectionInfo* __internal_ret = (Dz1IncidentDetectionInfo*)Dz1Calloc(sizeof(Dz1IncidentDetectionInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1IncidentDetectionInfo_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->incident_Detected_Time = incident_Detected_Time;
		__internal_ret->incident_Detected_Type = incident_Detected_Type;
		__internal_ret->incident_Detected_Site = incident_Detected_Site;
		__internal_ret->detected_Object_Distance = detected_Object_Distance;
		__internal_ret->detected_Object_Angle = detected_Object_Angle;
		__internal_ret->detected_Object_Speed = detected_Object_Speed;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentDetectionInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1IncidentDetectionInfo_copy(Dz1IncidentDetectionInfo* dst, Dz1IncidentDetectionInfo* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->incident_Detected_Time && (dst->incident_Detected_Time = Dz1Asn1VisibleStr_clone(src->incident_Detected_Time, errp)) == NULL) ERR_OUT(errp);
	else if (src->incident_Detected_Site && (dst->incident_Detected_Site = Dz1NMEACoord_clone(src->incident_Detected_Site, errp)) == NULL) ERR_OUT(errp);
	else if (src->detected_Object_Size && (dst->detected_Object_Size = Dz1u8_clone(src->detected_Object_Size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->incident_Detected_Type = src->incident_Detected_Type;
		dst->detected_Object_Distance = src->detected_Object_Distance;
		dst->detected_Object_Angle = src->detected_Object_Angle;
		dst->detected_Object_Speed = src->detected_Object_Speed;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1IncidentDetectionInfo* Dz1IncidentDetectionInfo_clone(Dz1IncidentDetectionInfo* src, Dz1Error* err)
{
	Dz1IncidentDetectionInfo* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1IncidentDetectionInfo*)Dz1Calloc(sizeof(Dz1IncidentDetectionInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1IncidentDetectionInfo_delAndSetNull, (void*)&dst);
		if (Dz1IncidentDetectionInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentDetectionInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1IncidentDetectionInfo_purge(Dz1IncidentDetectionInfo* p)
{
	if (p == NULL) return;
	Dz1Asn1VisibleStr_del(p->incident_Detected_Time);
	Dz1NMEACoord_del(p->incident_Detected_Site);
	Dz1u8_del(p->detected_Object_Size);
}

void Dz1IncidentDetectionInfo_del(Dz1IncidentDetectionInfo* p)
{
	if (p == NULL) return;
	Dz1IncidentDetectionInfo_purge(p);
	Dz1Free(p);
}

void Dz1IncidentDetectionInfo_dump(Dz1IncidentDetectionInfo* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("incident_Detected_Time = ")); Dz1Asn1VisibleStr_dump(p->incident_Detected_Time, tab);
		Dz1Thread_tprintf(tab, Dz1T("incident_Detected_Type = %s(%d)\n"), Dz1IncidentDetectionInfo_incident_Detected_TypeStr(p->incident_Detected_Type), p->incident_Detected_Type);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("incident_Detected_Site = ")); Dz1NMEACoord_dump(p->incident_Detected_Site, tab);
		Dz1Thread_tprintf(tab, Dz1T("detected_Object_Size = ")); Dz1u8_dump(p->detected_Object_Size, tab);
		Dz1Thread_tprintf(tab, Dz1T("detected_Object_Distance = ")); Dz1u16_dump(&p->detected_Object_Distance, tab);
		Dz1Thread_tprintf(tab, Dz1T("detected_Object_Angle = ")); Dz1u16_dump(&p->detected_Object_Angle, tab);
		Dz1Thread_tprintf(tab, Dz1T("detected_Object_Speed = ")); Dz1u16_dump(&p->detected_Object_Speed, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1IncidentDetectionInfo_fdump(FILE* fp, Dz1IncidentDetectionInfo* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_ftprintf(fp, tab, Dz1T("incident_Detected_Time = ")); Dz1Asn1VisibleStr_fdump(fp, p->incident_Detected_Time, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("incident_Detected_Type = %s(%d)\n"), Dz1IncidentDetectionInfo_incident_Detected_TypeStr(p->incident_Detected_Type), p->incident_Detected_Type);
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("incident_Detected_Site = ")); Dz1NMEACoord_fdump(fp, p->incident_Detected_Site, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("detected_Object_Size = ")); Dz1u8_fdump(fp, p->detected_Object_Size, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("detected_Object_Distance = ")); Dz1u16_fdump(fp, &p->detected_Object_Distance, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("detected_Object_Angle = ")); Dz1u16_fdump(fp, &p->detected_Object_Angle, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("detected_Object_Speed = ")); Dz1u16_fdump(fp, &p->detected_Object_Speed, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1IncidentDetectionInfo_fromASN(Dz1IncidentDetectionInfo* dst, IncidentDetectionInfo* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->incident_Detected_Time = Dz1Asn1VisibleStr_newFromASN(&src->incident_Detected_Time, &err)) == NULL) { Dz1Thread_printf("incident_Detected_Time : "); ERR_OUT(&err); }
		else if ((dst->incident_Detected_Site = Dz1NMEACoord_newFromASN(src->incident_Detected_Site, &err)) == NULL) { Dz1Thread_printf("incident_Detected_Site : "); ERR_OUT(&err); }
		else if (src->DEF_IncidentDetectionInfo_detected_Object_Size && (dst->detected_Object_Size = u8_t_newFromASN(&src->detected_Object_Size, &err)) == NULL) ERR_OUT(&err);
		else if ((err = u16_t_fromASN(&dst->detected_Object_Distance, &src->detected_Object_Distance)).code) { Dz1Thread_printf("detected_Object_Distance : "); ERR_OUT(&err); }
		else if ((err = u16_t_fromASN(&dst->detected_Object_Angle, &src->detected_Object_Angle)).code) { Dz1Thread_printf("detected_Object_Angle : "); ERR_OUT(&err); }
		else if ((err = u16_t_fromASN(&dst->detected_Object_Speed, &src->detected_Object_Speed)).code) { Dz1Thread_printf("detected_Object_Speed : "); ERR_OUT(&err); }
		else
		{
			dst->incident_Detected_Type = (Dz1IncidentDetectionInfo_incident_Detected_Type)src->incident_Detected_Type;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1IncidentDetectionInfo, IncidentDetectionInfo)

Dz1Error Dz1IncidentDetectionInfo_toASN(IncidentDetectionInfo* dst, Dz1IncidentDetectionInfo* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1VisibleStr_toASN(&dst->incident_Detected_Time, src->incident_Detected_Time, ws)).code) { Dz1Thread_printf("incident_Detected_Time : "); ERR_OUT(&err); }
		else if ((dst->incident_Detected_Site = Dz1NMEACoord_toNewASN(src->incident_Detected_Site, ws, &err)) == NULL) { Dz1Thread_printf("incident_Detected_Site : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentDetectionInfo_detected_Object_Size = src->detected_Object_Size ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->detected_Object_Size, src->detected_Object_Size, ws)).code) { Dz1Thread_printf("detected_Object_Size : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->detected_Object_Distance, &src->detected_Object_Distance, ws)).code) { Dz1Thread_printf("detected_Object_Distance : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->detected_Object_Angle, &src->detected_Object_Angle, ws)).code) { Dz1Thread_printf("detected_Object_Angle : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->detected_Object_Speed, &src->detected_Object_Speed, ws)).code) { Dz1Thread_printf("detected_Object_Speed : "); ERR_OUT(&err); }
		else
		{
			dst->incident_Detected_Type = src->incident_Detected_Type;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1IncidentDetectionInfo, IncidentDetectionInfo)
// Dz1IncidentDetectionInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentTerminationInfo_terminate_incidentType
static struct Dz1IncidentTerminationInfo_terminate_incidentTypeMapA
{
	str_t str;
	Dz1IncidentTerminationInfo_terminate_incidentType v;
} Dz1IncidentTerminationInfo_terminate_incidentTypeMapA[] =
{
	{ (char*)"termination", Dz1IncidentTerminationInfo_terminate_incidentType_termination },
	{ (char*)"timeout", Dz1IncidentTerminationInfo_terminate_incidentType_timeout },
	{ NULL, Dz1IncidentTerminationInfo_terminate_incidentType_max }
};

str_t Dz1IncidentTerminationInfo_terminate_incidentTypeStrA(Dz1IncidentTerminationInfo_terminate_incidentType v)
{
	struct Dz1IncidentTerminationInfo_terminate_incidentTypeMapA* i = NULL;
	for (i = Dz1IncidentTerminationInfo_terminate_incidentTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentTerminationInfo_terminate_incidentType Dz1IncidentTerminationInfo_terminate_incidentTypeFromStrA(str_t str)
{
	struct Dz1IncidentTerminationInfo_terminate_incidentTypeMapA* i = NULL;
	for (i = Dz1IncidentTerminationInfo_terminate_incidentTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1IncidentTerminationInfo_terminate_incidentType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1IncidentTerminationInfo_terminate_incidentTypeMapW
{
	wstr_t str;
	Dz1IncidentTerminationInfo_terminate_incidentType v;
} Dz1IncidentTerminationInfo_terminate_incidentTypeMapW[] =
{
	{ (wchar_t*)L"termination", Dz1IncidentTerminationInfo_terminate_incidentType_termination },
	{ (wchar_t*)L"timeout", Dz1IncidentTerminationInfo_terminate_incidentType_timeout },
	{ NULL, Dz1IncidentTerminationInfo_terminate_incidentType_max }
};

wstr_t Dz1IncidentTerminationInfo_terminate_incidentTypeStrW(Dz1IncidentTerminationInfo_terminate_incidentType v)
{
	struct Dz1IncidentTerminationInfo_terminate_incidentTypeMapW* i = NULL;
	for (i = Dz1IncidentTerminationInfo_terminate_incidentTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentTerminationInfo_terminate_incidentType Dz1IncidentTerminationInfo_terminate_incidentTypeFromStrW(wstr_t str)
{
	struct Dz1IncidentTerminationInfo_terminate_incidentTypeMapW* i = NULL;
	for (i = Dz1IncidentTerminationInfo_terminate_incidentTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1IncidentTerminationInfo_terminate_incidentType_max;
}
#endif // UNIX_SYSTEM

Dz1IncidentTerminationInfo_terminate_incidentType* Dz1IncidentTerminationInfo_terminate_incidentType_new(Dz1IncidentTerminationInfo_terminate_incidentType* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentTerminationInfo_terminate_incidentType* __internal_ret = (Dz1IncidentTerminationInfo_terminate_incidentType*)Dz1Calloc(sizeof(Dz1IncidentTerminationInfo_terminate_incidentType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1IncidentTerminationInfo_terminate_incidentType_dump(Dz1IncidentTerminationInfo_terminate_incidentType* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1IncidentTerminationInfo_terminate_incidentTypeStr(*v));
}
void Dz1IncidentTerminationInfo_terminate_incidentType_fdump(FILE* fp, Dz1IncidentTerminationInfo_terminate_incidentType* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1IncidentTerminationInfo_terminate_incidentTypeStr(*v));
}
Dz1Error Dz1IncidentTerminationInfo_terminate_incidentType_fromASN(Dz1IncidentTerminationInfo_terminate_incidentType* dst, IncidentTerminationInfo_terminate_incidentType* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1IncidentTerminationInfo_terminate_incidentType)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1IncidentTerminationInfo_terminate_incidentType, IncidentTerminationInfo_terminate_incidentType)

Dz1Error Dz1IncidentTerminationInfo_terminate_incidentType_toASN(IncidentTerminationInfo_terminate_incidentType* dst, Dz1IncidentTerminationInfo_terminate_incidentType* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (IncidentTerminationInfo_terminate_incidentType)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1IncidentTerminationInfo_terminate_incidentType, IncidentTerminationInfo_terminate_incidentType)
// Dz1IncidentTerminationInfo_terminate_incidentType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentTerminationInfo
Dz1IncidentTerminationInfo* Dz1IncidentTerminationInfo_new(Dz1IncidentTerminationInfo_terminate_incidentType terminate_incidentType, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentTerminationInfo* __internal_ret = (Dz1IncidentTerminationInfo*)Dz1Calloc(sizeof(Dz1IncidentTerminationInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1IncidentTerminationInfo_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->terminate_incidentType = terminate_incidentType;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentTerminationInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1IncidentTerminationInfo_copy(Dz1IncidentTerminationInfo* dst, Dz1IncidentTerminationInfo* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->terminate_incidentType = src->terminate_incidentType;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1IncidentTerminationInfo* Dz1IncidentTerminationInfo_clone(Dz1IncidentTerminationInfo* src, Dz1Error* err)
{
	Dz1IncidentTerminationInfo* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1IncidentTerminationInfo*)Dz1Calloc(sizeof(Dz1IncidentTerminationInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1IncidentTerminationInfo_delAndSetNull, (void*)&dst);
		if (Dz1IncidentTerminationInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentTerminationInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1IncidentTerminationInfo_purge(Dz1IncidentTerminationInfo* p)
{
	if (p == NULL) return;
}

void Dz1IncidentTerminationInfo_del(Dz1IncidentTerminationInfo* p)
{
	if (p == NULL) return;
	Dz1IncidentTerminationInfo_purge(p);
	Dz1Free(p);
}

void Dz1IncidentTerminationInfo_dump(Dz1IncidentTerminationInfo* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("terminate_incidentType = %s(%d)\n"), Dz1IncidentTerminationInfo_terminate_incidentTypeStr(p->terminate_incidentType), p->terminate_incidentType);
	}
}
void Dz1IncidentTerminationInfo_fdump(FILE* fp, Dz1IncidentTerminationInfo* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("terminate_incidentType = %s(%d)\n"), Dz1IncidentTerminationInfo_terminate_incidentTypeStr(p->terminate_incidentType), p->terminate_incidentType);
	}
}
Dz1Error Dz1IncidentTerminationInfo_fromASN(Dz1IncidentTerminationInfo* dst, IncidentTerminationInfo* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->terminate_incidentType = (Dz1IncidentTerminationInfo_terminate_incidentType)src->terminate_incidentType;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1IncidentTerminationInfo, IncidentTerminationInfo)

Dz1Error Dz1IncidentTerminationInfo_toASN(IncidentTerminationInfo* dst, Dz1IncidentTerminationInfo* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->terminate_incidentType = src->terminate_incidentType;
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1IncidentTerminationInfo, IncidentTerminationInfo)
// Dz1IncidentTerminationInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionVideoFileInfoProvide_fileStatus
static struct Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapA
{
	str_t str;
	Dz1IncidentDetectionVideoFileInfoProvide_fileStatus v;
} Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapA[] =
{
	{ (char*)"videoFileExists", Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileExists },
	{ (char*)"videoFileAlreadyExists", Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileAlreadyExists },
	{ NULL, Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_max }
};

str_t Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStrA(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus v)
{
	struct Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapA* i = NULL;
	for (i = Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentDetectionVideoFileInfoProvide_fileStatus Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStrA(str_t str)
{
	struct Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapA* i = NULL;
	for (i = Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapW
{
	wstr_t str;
	Dz1IncidentDetectionVideoFileInfoProvide_fileStatus v;
} Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapW[] =
{
	{ (wchar_t*)L"videoFileExists", Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileExists },
	{ (wchar_t*)L"videoFileAlreadyExists", Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileAlreadyExists },
	{ NULL, Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_max }
};

wstr_t Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStrW(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus v)
{
	struct Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapW* i = NULL;
	for (i = Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentDetectionVideoFileInfoProvide_fileStatus Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStrW(wstr_t str)
{
	struct Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapW* i = NULL;
	for (i = Dz1IncidentDetectionVideoFileInfoProvide_fileStatusMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_max;
}
#endif // UNIX_SYSTEM

Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_new(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* __internal_ret = (Dz1IncidentDetectionVideoFileInfoProvide_fileStatus*)Dz1Calloc(sizeof(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_dump(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStr(*v));
}
void Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_fdump(FILE* fp, Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStr(*v));
}
Dz1Error Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_fromASN(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* dst, IncidentDetectionVideoFileInfoProvide_fileStatus* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1IncidentDetectionVideoFileInfoProvide_fileStatus)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus, IncidentDetectionVideoFileInfoProvide_fileStatus)

Dz1Error Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_toASN(IncidentDetectionVideoFileInfoProvide_fileStatus* dst, Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (IncidentDetectionVideoFileInfoProvide_fileStatus)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus, IncidentDetectionVideoFileInfoProvide_fileStatus)
// Dz1IncidentDetectionVideoFileInfoProvide_fileStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionVideoFileInfoProvide
Dz1IncidentDetectionVideoFileInfoProvide* Dz1IncidentDetectionVideoFileInfoProvide_new(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus fileStatus, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentDetectionVideoFileInfoProvide* __internal_ret = (Dz1IncidentDetectionVideoFileInfoProvide*)Dz1Calloc(sizeof(Dz1IncidentDetectionVideoFileInfoProvide), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1IncidentDetectionVideoFileInfoProvide_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->fileStatus = fileStatus;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentDetectionVideoFileInfoProvide_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1IncidentDetectionVideoFileInfoProvide_copy(Dz1IncidentDetectionVideoFileInfoProvide* dst, Dz1IncidentDetectionVideoFileInfoProvide* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->fileName && (dst->fileName = Dz1Asn1OctetStr_clone(src->fileName, errp)) == NULL) ERR_OUT(errp);
	else if (src->fileSize && (dst->fileSize = Dz1s64_clone(src->fileSize, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->fileStatus = src->fileStatus;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1IncidentDetectionVideoFileInfoProvide* Dz1IncidentDetectionVideoFileInfoProvide_clone(Dz1IncidentDetectionVideoFileInfoProvide* src, Dz1Error* err)
{
	Dz1IncidentDetectionVideoFileInfoProvide* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1IncidentDetectionVideoFileInfoProvide*)Dz1Calloc(sizeof(Dz1IncidentDetectionVideoFileInfoProvide), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1IncidentDetectionVideoFileInfoProvide_delAndSetNull, (void*)&dst);
		if (Dz1IncidentDetectionVideoFileInfoProvide_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentDetectionVideoFileInfoProvide_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1IncidentDetectionVideoFileInfoProvide_purge(Dz1IncidentDetectionVideoFileInfoProvide* p)
{
	if (p == NULL) return;
	Dz1Asn1OctetStr_del(p->fileName);
	Dz1s64_del(p->fileSize);
}

void Dz1IncidentDetectionVideoFileInfoProvide_del(Dz1IncidentDetectionVideoFileInfoProvide* p)
{
	if (p == NULL) return;
	Dz1IncidentDetectionVideoFileInfoProvide_purge(p);
	Dz1Free(p);
}

void Dz1IncidentDetectionVideoFileInfoProvide_dump(Dz1IncidentDetectionVideoFileInfoProvide* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("fileStatus = %s(%d)\n"), Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStr(p->fileStatus), p->fileStatus);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("fileName = ")); Dz1Asn1OctetStr_dump(p->fileName, tab);
		Dz1Thread_tprintf(tab, Dz1T("fileSize = ")); Dz1s64_dump(p->fileSize, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1IncidentDetectionVideoFileInfoProvide_fdump(FILE* fp, Dz1IncidentDetectionVideoFileInfoProvide* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("fileStatus = %s(%d)\n"), Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStr(p->fileStatus), p->fileStatus);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_ftprintf(fp, tab, Dz1T("fileName = ")); Dz1Asn1OctetStr_fdump(fp, p->fileName, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("fileSize = ")); Dz1s64_fdump(fp, p->fileSize, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1IncidentDetectionVideoFileInfoProvide_fromASN(Dz1IncidentDetectionVideoFileInfoProvide* dst, IncidentDetectionVideoFileInfoProvide* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if (src->DEF_IncidentDetectionVideoFileInfoProvide_fileName && (dst->fileName = Dz1Asn1OctetStr_newFromASN(&src->fileName, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_IncidentDetectionVideoFileInfoProvide_fileSize && (dst->fileSize = s64_t_newFromASN(&src->fileSize, &err)) == NULL) ERR_OUT(&err);
		else
		{
			dst->fileStatus = (Dz1IncidentDetectionVideoFileInfoProvide_fileStatus)src->fileStatus;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1IncidentDetectionVideoFileInfoProvide, IncidentDetectionVideoFileInfoProvide)

Dz1Error Dz1IncidentDetectionVideoFileInfoProvide_toASN(IncidentDetectionVideoFileInfoProvide* dst, Dz1IncidentDetectionVideoFileInfoProvide* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->DEF_IncidentDetectionVideoFileInfoProvide_fileName = src->fileName ? 1 : 0) == 1 && (err = Dz1Asn1OctetStr_toASN(&dst->fileName, src->fileName, ws)).code) { Dz1Thread_printf("fileName : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentDetectionVideoFileInfoProvide_fileSize = src->fileSize ? 1 : 0) == 1 && (err = s64_t_toASN(&dst->fileSize, src->fileSize, ws)).code) { Dz1Thread_printf("fileSize : "); ERR_OUT(&err); }
		else
		{
			dst->fileStatus = src->fileStatus;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1IncidentDetectionVideoFileInfoProvide, IncidentDetectionVideoFileInfoProvide)
// Dz1IncidentDetectionVideoFileInfoProvide
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ControlStateInfo
Dz1ControlStateInfo* Dz1ControlStateInfo_new(u8_t cpu, u8_t ram, u8_t disk, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ControlStateInfo* __internal_ret = (Dz1ControlStateInfo*)Dz1Calloc(sizeof(Dz1ControlStateInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1ControlStateInfo_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->cpu = cpu;
		__internal_ret->ram = ram;
		__internal_ret->disk = disk;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ControlStateInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1ControlStateInfo_copy(Dz1ControlStateInfo* dst, Dz1ControlStateInfo* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->cpu = src->cpu;
		dst->ram = src->ram;
		dst->disk = src->disk;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1ControlStateInfo* Dz1ControlStateInfo_clone(Dz1ControlStateInfo* src, Dz1Error* err)
{
	Dz1ControlStateInfo* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1ControlStateInfo*)Dz1Calloc(sizeof(Dz1ControlStateInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1ControlStateInfo_delAndSetNull, (void*)&dst);
		if (Dz1ControlStateInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ControlStateInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1ControlStateInfo_purge(Dz1ControlStateInfo* p)
{
	if (p == NULL) return;
}

void Dz1ControlStateInfo_del(Dz1ControlStateInfo* p)
{
	if (p == NULL) return;
	Dz1ControlStateInfo_purge(p);
	Dz1Free(p);
}

void Dz1ControlStateInfo_dump(Dz1ControlStateInfo* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cpu = ")); Dz1u8_dump(&p->cpu, tab);
		Dz1Thread_tprintf(tab, Dz1T("ram = ")); Dz1u8_dump(&p->ram, tab);
		Dz1Thread_tprintf(tab, Dz1T("disk = ")); Dz1u8_dump(&p->disk, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1ControlStateInfo_fdump(FILE* fp, Dz1ControlStateInfo* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("cpu = ")); Dz1u8_fdump(fp, &p->cpu, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("ram = ")); Dz1u8_fdump(fp, &p->ram, tab);
		Dz1Thread_ftprintf(fp, tab, Dz1T("disk = ")); Dz1u8_fdump(fp, &p->disk, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1ControlStateInfo_fromASN(Dz1ControlStateInfo* dst, ControlStateInfo* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u8_t_fromASN(&dst->cpu, &src->cpu)).code) { Dz1Thread_printf("cpu : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->ram, &src->ram)).code) { Dz1Thread_printf("ram : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->disk, &src->disk)).code) { Dz1Thread_printf("disk : "); ERR_OUT(&err); }
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1ControlStateInfo, ControlStateInfo)

Dz1Error Dz1ControlStateInfo_toASN(ControlStateInfo* dst, Dz1ControlStateInfo* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u8_t_toASN(&dst->cpu, &src->cpu, ws)).code) { Dz1Thread_printf("cpu : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->ram, &src->ram, ws)).code) { Dz1Thread_printf("ram : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->disk, &src->disk, ws)).code) { Dz1Thread_printf("disk : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1ControlStateInfo, ControlStateInfo)
// Dz1ControlStateInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SensorStateInfo_state
static struct Dz1SensorStateInfo_stateMapA
{
	str_t str;
	Dz1SensorStateInfo_state v;
} Dz1SensorStateInfo_stateMapA[] =
{
	{ (char*)"normal", Dz1SensorStateInfo_state_normal },
	{ (char*)"abnormal", Dz1SensorStateInfo_state_abnormal },
	{ NULL, Dz1SensorStateInfo_state_max }
};

str_t Dz1SensorStateInfo_stateStrA(Dz1SensorStateInfo_state v)
{
	struct Dz1SensorStateInfo_stateMapA* i = NULL;
	for (i = Dz1SensorStateInfo_stateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1SensorStateInfo_state Dz1SensorStateInfo_stateFromStrA(str_t str)
{
	struct Dz1SensorStateInfo_stateMapA* i = NULL;
	for (i = Dz1SensorStateInfo_stateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1SensorStateInfo_state_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1SensorStateInfo_stateMapW
{
	wstr_t str;
	Dz1SensorStateInfo_state v;
} Dz1SensorStateInfo_stateMapW[] =
{
	{ (wchar_t*)L"normal", Dz1SensorStateInfo_state_normal },
	{ (wchar_t*)L"abnormal", Dz1SensorStateInfo_state_abnormal },
	{ NULL, Dz1SensorStateInfo_state_max }
};

wstr_t Dz1SensorStateInfo_stateStrW(Dz1SensorStateInfo_state v)
{
	struct Dz1SensorStateInfo_stateMapW* i = NULL;
	for (i = Dz1SensorStateInfo_stateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1SensorStateInfo_state Dz1SensorStateInfo_stateFromStrW(wstr_t str)
{
	struct Dz1SensorStateInfo_stateMapW* i = NULL;
	for (i = Dz1SensorStateInfo_stateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1SensorStateInfo_state_max;
}
#endif // UNIX_SYSTEM

Dz1SensorStateInfo_state* Dz1SensorStateInfo_state_new(Dz1SensorStateInfo_state* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1SensorStateInfo_state* __internal_ret = (Dz1SensorStateInfo_state*)Dz1Calloc(sizeof(Dz1SensorStateInfo_state), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1SensorStateInfo_state_dump(Dz1SensorStateInfo_state* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1SensorStateInfo_stateStr(*v));
}
void Dz1SensorStateInfo_state_fdump(FILE* fp, Dz1SensorStateInfo_state* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1SensorStateInfo_stateStr(*v));
}
Dz1Error Dz1SensorStateInfo_state_fromASN(Dz1SensorStateInfo_state* dst, SensorStateInfo_state* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1SensorStateInfo_state)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1SensorStateInfo_state, SensorStateInfo_state)

Dz1Error Dz1SensorStateInfo_state_toASN(SensorStateInfo_state* dst, Dz1SensorStateInfo_state* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (SensorStateInfo_state)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1SensorStateInfo_state, SensorStateInfo_state)
// Dz1SensorStateInfo_state
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SensorStateInfo
Dz1SensorStateInfo* Dz1SensorStateInfo_new(Dz1SensorStateInfo_state msm,
	Dz1SensorStateInfo_state txb,
	Dz1SensorStateInfo_state rxb,
	Dz1SensorStateInfo_state pwr, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1SensorStateInfo* __internal_ret = (Dz1SensorStateInfo*)Dz1Calloc(sizeof(Dz1SensorStateInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SensorStateInfo_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->msm = msm;
		__internal_ret->txb = txb;
		__internal_ret->rxb = rxb;
		__internal_ret->pwr = pwr;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SensorStateInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1SensorStateInfo_copy(Dz1SensorStateInfo* dst, Dz1SensorStateInfo* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->msm = src->msm;
		dst->txb = src->txb;
		dst->rxb = src->rxb;
		dst->pwr = src->pwr;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1SensorStateInfo* Dz1SensorStateInfo_clone(Dz1SensorStateInfo* src, Dz1Error* err)
{
	Dz1SensorStateInfo* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1SensorStateInfo*)Dz1Calloc(sizeof(Dz1SensorStateInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SensorStateInfo_delAndSetNull, (void*)&dst);
		if (Dz1SensorStateInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SensorStateInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1SensorStateInfo_purge(Dz1SensorStateInfo* p)
{
	if (p == NULL) return;
}

void Dz1SensorStateInfo_del(Dz1SensorStateInfo* p)
{
	if (p == NULL) return;
	Dz1SensorStateInfo_purge(p);
	Dz1Free(p);
}

void Dz1SensorStateInfo_dump(Dz1SensorStateInfo* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("msm = %s(%d)\n"), Dz1SensorStateInfo_stateStr(p->msm), p->msm);
		Dz1Thread_tprintf(tab, Dz1T("txb = %s(%d)\n"), Dz1SensorStateInfo_stateStr(p->txb), p->txb);
		Dz1Thread_tprintf(tab, Dz1T("rxb = %s(%d)\n"), Dz1SensorStateInfo_stateStr(p->rxb), p->rxb);
		Dz1Thread_tprintf(tab, Dz1T("pwr = %s(%d)\n"), Dz1SensorStateInfo_stateStr(p->pwr), p->pwr);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1SensorStateInfo_fdump(FILE* fp, Dz1SensorStateInfo* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("msm = %s(%d)\n"), Dz1SensorStateInfo_stateStr(p->msm), p->msm);
		Dz1Thread_ftprintf(fp, tab, Dz1T("txb = %s(%d)\n"), Dz1SensorStateInfo_stateStr(p->txb), p->txb);
		Dz1Thread_ftprintf(fp, tab, Dz1T("rxb = %s(%d)\n"), Dz1SensorStateInfo_stateStr(p->rxb), p->rxb);
		Dz1Thread_ftprintf(fp, tab, Dz1T("pwr = %s(%d)\n"), Dz1SensorStateInfo_stateStr(p->pwr), p->pwr);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1SensorStateInfo_fromASN(Dz1SensorStateInfo* dst, SensorStateInfo* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->msm = (Dz1SensorStateInfo_state)src->msm;
		dst->txb = (Dz1SensorStateInfo_state)src->txb;
		dst->rxb = (Dz1SensorStateInfo_state)src->rxb;
		dst->pwr = (Dz1SensorStateInfo_state)src->pwr;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1SensorStateInfo, SensorStateInfo)

Dz1Error Dz1SensorStateInfo_toASN(SensorStateInfo* dst, Dz1SensorStateInfo* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->msm = src->msm;
		dst->txb = src->txb;
		dst->rxb = src->rxb;
		dst->pwr = src->pwr;
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1SensorStateInfo, SensorStateInfo)
// Dz1SensorStateInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Novelty
static struct Dz1NoveltyMapA
{
	str_t str;
	Dz1Novelty v;
} Dz1NoveltyMapA[] =
{
	{ (char*)"noveltyNew", Dz1Novelty_noveltyNew },
	{ (char*)"noveltyUpdate", Dz1Novelty_noveltyUpdate },
	{ NULL, Dz1Novelty_max }
};

str_t Dz1NoveltyStrA(Dz1Novelty v)
{
	struct Dz1NoveltyMapA* i = NULL;
	for (i = Dz1NoveltyMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Novelty Dz1NoveltyFromStrA(str_t str)
{
	struct Dz1NoveltyMapA* i = NULL;
	for (i = Dz1NoveltyMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Novelty_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1NoveltyMapW
{
	wstr_t str;
	Dz1Novelty v;
} Dz1NoveltyMapW[] =
{
	{ (wchar_t*)L"noveltyNew", Dz1Novelty_noveltyNew },
	{ (wchar_t*)L"noveltyUpdate", Dz1Novelty_noveltyUpdate },
	{ NULL, Dz1Novelty_max }
};

wstr_t Dz1NoveltyStrW(Dz1Novelty v)
{
	struct Dz1NoveltyMapW* i = NULL;
	for (i = Dz1NoveltyMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Novelty Dz1NoveltyFromStrW(wstr_t str)
{
	struct Dz1NoveltyMapW* i = NULL;
	for (i = Dz1NoveltyMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Novelty_max;
}
#endif // UNIX_SYSTEM

Dz1Novelty* Dz1Novelty_new(Dz1Novelty* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1Novelty* __internal_ret = (Dz1Novelty*)Dz1Calloc(sizeof(Dz1Novelty), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1Novelty_dump(Dz1Novelty* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1NoveltyStr(*v));
}
void Dz1Novelty_fdump(FILE* fp, Dz1Novelty* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1NoveltyStr(*v));
}
Dz1Error Dz1Novelty_fromASN(Dz1Novelty* dst, Novelty* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1Novelty)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1Novelty, Novelty)

Dz1Error Dz1Novelty_toASN(Novelty* dst, Dz1Novelty* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Novelty)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1Novelty, Novelty)
// Dz1Novelty
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MovingObject_objectType
static struct Dz1MovingObject_objectTypeMapA
{
	str_t str;
	Dz1MovingObject_objectType v;
} Dz1MovingObject_objectTypeMapA[] =
{
	{ (char*)"pedestrian", Dz1MovingObject_objectType_pedestrian },
	{ (char*)"vehicle", Dz1MovingObject_objectType_vehicle },
	{ (char*)"bike", Dz1MovingObject_objectType_bike },
	{ NULL, Dz1MovingObject_objectType_max }
};

str_t Dz1MovingObject_objectTypeStrA(Dz1MovingObject_objectType v)
{
	struct Dz1MovingObject_objectTypeMapA* i = NULL;
	for (i = Dz1MovingObject_objectTypeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MovingObject_objectType Dz1MovingObject_objectTypeFromStrA(str_t str)
{
	struct Dz1MovingObject_objectTypeMapA* i = NULL;
	for (i = Dz1MovingObject_objectTypeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1MovingObject_objectType_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1MovingObject_objectTypeMapW
{
	wstr_t str;
	Dz1MovingObject_objectType v;
} Dz1MovingObject_objectTypeMapW[] =
{
	{ (wchar_t*)L"pedestrian", Dz1MovingObject_objectType_pedestrian },
	{ (wchar_t*)L"vehicle", Dz1MovingObject_objectType_vehicle },
	{ (wchar_t*)L"bike", Dz1MovingObject_objectType_bike },
	{ NULL, Dz1MovingObject_objectType_max }
};

wstr_t Dz1MovingObject_objectTypeStrW(Dz1MovingObject_objectType v)
{
	struct Dz1MovingObject_objectTypeMapW* i = NULL;
	for (i = Dz1MovingObject_objectTypeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1MovingObject_objectType Dz1MovingObject_objectTypeFromStrW(wstr_t str)
{
	struct Dz1MovingObject_objectTypeMapW* i = NULL;
	for (i = Dz1MovingObject_objectTypeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1MovingObject_objectType_max;
}
#endif // UNIX_SYSTEM

Dz1MovingObject_objectType* Dz1MovingObject_objectType_new(Dz1MovingObject_objectType* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1MovingObject_objectType* __internal_ret = (Dz1MovingObject_objectType*)Dz1Calloc(sizeof(Dz1MovingObject_objectType), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1MovingObject_objectType_dump(Dz1MovingObject_objectType* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1MovingObject_objectTypeStr(*v));
}
void Dz1MovingObject_objectType_fdump(FILE* fp, Dz1MovingObject_objectType* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1MovingObject_objectTypeStr(*v));
}
Dz1Error Dz1MovingObject_objectType_fromASN(Dz1MovingObject_objectType* dst, MovingObject_objectType* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1MovingObject_objectType)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1MovingObject_objectType, MovingObject_objectType)

Dz1Error Dz1MovingObject_objectType_toASN(MovingObject_objectType* dst, Dz1MovingObject_objectType* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (MovingObject_objectType)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1MovingObject_objectType, MovingObject_objectType)
// Dz1MovingObject_objectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MovingObject
Dz1MovingObject* Dz1MovingObject_new(Dz1MovingObject_objectType objectType,
	Dz1ObjectID_00100 objectID,
	u8_t reliability,
	Dz1FullPositionVector_00100* fullPositionVector, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1MovingObject* __internal_ret = (Dz1MovingObject*)Dz1Calloc(sizeof(Dz1MovingObject), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1MovingObject_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->objectType = objectType;
		__internal_ret->objectID = objectID;
		__internal_ret->reliability = reliability;
		__internal_ret->fullPositionVector = fullPositionVector;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MovingObject_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1MovingObject_copy(Dz1MovingObject* dst, Dz1MovingObject* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->novelty && (dst->novelty = Dz1Novelty_clone(src->novelty, errp)) == NULL) ERR_OUT(errp);
	else if (src->fullPositionVector && (dst->fullPositionVector = Dz1FullPositionVector_00100_clone(src->fullPositionVector, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->objectType = src->objectType;
		dst->objectID = src->objectID;
		dst->reliability = src->reliability;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1MovingObject* Dz1MovingObject_clone(Dz1MovingObject* src, Dz1Error* err)
{
	Dz1MovingObject* dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1MovingObject*)Dz1Calloc(sizeof(Dz1MovingObject), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MovingObject_delAndSetNull, (void*)&dst);
		if (Dz1MovingObject_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MovingObject_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1MovingObject_purge(Dz1MovingObject* p)
{
	if (p == NULL) return;
	Dz1Novelty_del(p->novelty);
	Dz1FullPositionVector_00100_del(p->fullPositionVector);
}

void Dz1MovingObject_del(Dz1MovingObject* p)
{
	if (p == NULL) return;
	Dz1MovingObject_purge(p);
	Dz1Free(p);
}

void Dz1MovingObject_dump(Dz1MovingObject* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("objectType = %s(%d)\n"), Dz1MovingObject_objectTypeStr(p->objectType), p->objectType);
		Dz1Thread_tprintf(tab, Dz1T("objectID = ")); Dz1ObjectID_00100_dump(&p->objectID, tab);
		if (p->novelty == NULL) Dz1Thread_tprintf(tab, Dz1T("novelty = NULL\n"));
		else Dz1Thread_tprintf(tab, Dz1T("novelty = %s(%d)\n"), Dz1NoveltyStr(*p->novelty), *p->novelty);
		Dz1Thread_tprintf(tab, Dz1T("reliability = ")); Dz1u8_dump(&p->reliability, tab);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("fullPositionVector = ")); Dz1FullPositionVector_00100_dump(p->fullPositionVector, tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
void Dz1MovingObject_fdump(FILE* fp, Dz1MovingObject* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
		Dz1Thread_ftprintf(fp, tab, Dz1T("objectType = %s(%d)\n"), Dz1MovingObject_objectTypeStr(p->objectType), p->objectType);
		Dz1Thread_ftprintf(fp, tab, Dz1T("objectID = ")); Dz1ObjectID_00100_fdump(fp, &p->objectID, tab);
		if (p->novelty == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("novelty = NULL\n"));
		else Dz1Thread_ftprintf(fp, tab, Dz1T("novelty = %s(%d)\n"), Dz1NoveltyStr(*p->novelty), *p->novelty);
		Dz1Thread_ftprintf(fp, tab, Dz1T("reliability = ")); Dz1u8_fdump(fp, &p->reliability, tab);
		// Normal member
		Dz1Thread_ftprintf(fp, tab, Dz1T("fullPositionVector = ")); Dz1FullPositionVector_00100_fdump(fp, p->fullPositionVector, tab);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
Dz1Error Dz1MovingObject_fromASN(Dz1MovingObject* dst, MovingObject* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1Novelty novelty = (Dz1Novelty)(src->DEF_MovingObject_novelty ? src->novelty : 0);
		if ((err = s64_t_fromASN(&dst->objectID, &src->objectID)).code) { Dz1Thread_printf("objectID : "); ERR_OUT(&err); }
		else if (src->DEF_MovingObject_novelty && (dst->novelty = Dz1Novelty_new(&novelty, &err)) == NULL) { Dz1Thread_printf("novelty : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->reliability, &src->reliability)).code) { Dz1Thread_printf("reliability : "); ERR_OUT(&err); }
		else if ((dst->fullPositionVector = Dz1FullPositionVector_00100_newFromASN(src->fullPositionVector, &err)) == NULL) { Dz1Thread_printf("fullPositionVector : "); ERR_OUT(&err); }
		else
		{
			dst->objectType = (Dz1MovingObject_objectType)src->objectType;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1MovingObject, MovingObject)

Dz1Error Dz1MovingObject_toASN(MovingObject* dst, Dz1MovingObject* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = s64_t_toASN(&dst->objectID, &src->objectID, ws)).code) { Dz1Thread_printf("objectID : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->reliability, &src->reliability, ws)).code) { Dz1Thread_printf("reliability : "); ERR_OUT(&err); }
		else if ((dst->fullPositionVector = Dz1FullPositionVector_00100_toNewASN(src->fullPositionVector, ws, &err)) == NULL) { Dz1Thread_printf("fullPositionVector : "); ERR_OUT(&err); }
		else
		{
			dst->objectType = src->objectType;
			if ((dst->DEF_MovingObject_novelty = src->novelty ? 1 : 0) == 1) dst->novelty = *src->novelty;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1MovingObject, MovingObject)
// Dz1MovingObject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionInfoResponse
static Dz1Error Dz1IncidentDetectionInfoResponse_add(Dz1IncidentDetectionInfoResponse* p, Dz1IncidentDetectionInfo* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1IncidentDetectionInfoResponseMkArrArg
{
	Dz1IncidentDetectionInfo** arr;
	unsigned int idx;
} Dz1IncidentDetectionInfoResponseMkArrArg;

static Dz1Error _Dz1IncidentDetectionInfoResponse_get_array(void* ptr, Dz1IncidentDetectionInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentDetectionInfoResponseMkArrArg* arg = (Dz1IncidentDetectionInfoResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1IncidentDetectionInfo** Dz1IncidentDetectionInfoResponse_get_array(Dz1IncidentDetectionInfoResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1IncidentDetectionInfo** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1IncidentDetectionInfo**)Dz1Calloc(sizeof(Dz1IncidentDetectionInfo*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1IncidentDetectionInfoResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1IncidentDetectionInfoResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1IncidentDetectionInfoResponse_travelForward(Dz1IncidentDetectionInfoResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentDetectionInfo* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1IncidentDetectionInfoResponse_travelBackward(Dz1IncidentDetectionInfoResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentDetectionInfo* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1IncidentDetectionInfoResponse_count(Dz1IncidentDetectionInfoResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1IncidentDetectionInfoResponse* Dz1IncidentDetectionInfoResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentDetectionInfoResponse* ret = (Dz1IncidentDetectionInfoResponse*)Dz1Calloc(sizeof(Dz1IncidentDetectionInfoResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentDetectionInfoResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1IncidentDetectionInfo_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1IncidentDetectionInfoResponse_count;
			ret->travel = Dz1IncidentDetectionInfoResponse_travelForward;
			ret->travelForward = Dz1IncidentDetectionInfoResponse_travelForward;
			ret->travelBackward = Dz1IncidentDetectionInfoResponse_travelBackward;
			ret->get_array = Dz1IncidentDetectionInfoResponse_get_array;
			ret->add = Dz1IncidentDetectionInfoResponse_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentDetectionInfoResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1IncidentDetectionInfoResponse_clone(void* ptr, Dz1IncidentDetectionInfo* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentDetectionInfoResponse* p = (Dz1IncidentDetectionInfoResponse*)ptr;
	Dz1IncidentDetectionInfo* cloned = Dz1IncidentDetectionInfo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1IncidentDetectionInfoResponse* Dz1IncidentDetectionInfoResponse_clone(Dz1IncidentDetectionInfoResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentDetectionInfoResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1IncidentDetectionInfoResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentDetectionInfoResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1IncidentDetectionInfoResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentDetectionInfoResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1IncidentDetectionInfoResponse_purge(Dz1IncidentDetectionInfoResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1IncidentDetectionInfoResponse_del(Dz1IncidentDetectionInfoResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1IncidentDetectionInfoResponse_dump(void* ptr, Dz1IncidentDetectionInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	int tab = *(int*)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1IncidentDetectionInfo_dump(p, tab);
	return err;
}

void Dz1IncidentDetectionInfoResponse_dump(Dz1IncidentDetectionInfoResponse* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1IncidentDetectionInfoResponse_dump, (void*)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1IncidentDetectionInfoResponse_fdump(void* ptr, Dz1IncidentDetectionInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	FILE* fp = arg->fp;
	int tab = *(int*)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1IncidentDetectionInfo_fdump(arg->fp, p, tab);
	return err;
}

void Dz1IncidentDetectionInfoResponse_fdump(FILE* fp, Dz1IncidentDetectionInfoResponse* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1IncidentDetectionInfoResponse_fdump, (void*)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
PSEUDO_LIST_FROM_ASN(Dz1IncidentDetectionInfoResponse, Dz1IncidentDetectionInfo, IncidentDetectionInfo)
DZ1_NEW_LIST_FROM_ASN(Dz1IncidentDetectionInfoResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1IncidentDetectionInfoResponse, Dz1IncidentDetectionInfo, IncidentDetectionInfo)
PSEUDO_LIST_TO_ASN(Dz1IncidentDetectionInfoResponse)
DZ1_TO_NEW_ASN_LIST(Dz1IncidentDetectionInfoResponse, ASN1List)

// Dz1IncidentDetectionInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentTerminationInfoResponse
static Dz1Error Dz1IncidentTerminationInfoResponse_add(Dz1IncidentTerminationInfoResponse* p, Dz1IncidentTerminationInfo* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1IncidentTerminationInfoResponseMkArrArg
{
	Dz1IncidentTerminationInfo** arr;
	unsigned int idx;
} Dz1IncidentTerminationInfoResponseMkArrArg;

static Dz1Error _Dz1IncidentTerminationInfoResponse_get_array(void* ptr, Dz1IncidentTerminationInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentTerminationInfoResponseMkArrArg* arg = (Dz1IncidentTerminationInfoResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1IncidentTerminationInfo** Dz1IncidentTerminationInfoResponse_get_array(Dz1IncidentTerminationInfoResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1IncidentTerminationInfo** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1IncidentTerminationInfo**)Dz1Calloc(sizeof(Dz1IncidentTerminationInfo*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1IncidentTerminationInfoResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1IncidentTerminationInfoResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1IncidentTerminationInfoResponse_travelForward(Dz1IncidentTerminationInfoResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentTerminationInfo* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1IncidentTerminationInfoResponse_travelBackward(Dz1IncidentTerminationInfoResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentTerminationInfo* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1IncidentTerminationInfoResponse_count(Dz1IncidentTerminationInfoResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1IncidentTerminationInfoResponse* Dz1IncidentTerminationInfoResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentTerminationInfoResponse* ret = (Dz1IncidentTerminationInfoResponse*)Dz1Calloc(sizeof(Dz1IncidentTerminationInfoResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentTerminationInfoResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1IncidentTerminationInfo_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1IncidentTerminationInfoResponse_count;
			ret->travel = Dz1IncidentTerminationInfoResponse_travelForward;
			ret->travelForward = Dz1IncidentTerminationInfoResponse_travelForward;
			ret->travelBackward = Dz1IncidentTerminationInfoResponse_travelBackward;
			ret->get_array = Dz1IncidentTerminationInfoResponse_get_array;
			ret->add = Dz1IncidentTerminationInfoResponse_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentTerminationInfoResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1IncidentTerminationInfoResponse_clone(void* ptr, Dz1IncidentTerminationInfo* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentTerminationInfoResponse* p = (Dz1IncidentTerminationInfoResponse*)ptr;
	Dz1IncidentTerminationInfo* cloned = Dz1IncidentTerminationInfo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1IncidentTerminationInfoResponse* Dz1IncidentTerminationInfoResponse_clone(Dz1IncidentTerminationInfoResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentTerminationInfoResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1IncidentTerminationInfoResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentTerminationInfoResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1IncidentTerminationInfoResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentTerminationInfoResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1IncidentTerminationInfoResponse_purge(Dz1IncidentTerminationInfoResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1IncidentTerminationInfoResponse_del(Dz1IncidentTerminationInfoResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1IncidentTerminationInfoResponse_dump(void* ptr, Dz1IncidentTerminationInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	int tab = *(int*)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1IncidentTerminationInfo_dump(p, tab);
	return err;
}

void Dz1IncidentTerminationInfoResponse_dump(Dz1IncidentTerminationInfoResponse* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1IncidentTerminationInfoResponse_dump, (void*)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1IncidentTerminationInfoResponse_fdump(void* ptr, Dz1IncidentTerminationInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	FILE* fp = arg->fp;
	int tab = *(int*)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1IncidentTerminationInfo_fdump(arg->fp, p, tab);
	return err;
}

void Dz1IncidentTerminationInfoResponse_fdump(FILE* fp, Dz1IncidentTerminationInfoResponse* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1IncidentTerminationInfoResponse_fdump, (void*)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
PSEUDO_LIST_FROM_ASN(Dz1IncidentTerminationInfoResponse, Dz1IncidentTerminationInfo, IncidentTerminationInfo)
DZ1_NEW_LIST_FROM_ASN(Dz1IncidentTerminationInfoResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1IncidentTerminationInfoResponse, Dz1IncidentTerminationInfo, IncidentTerminationInfo)
PSEUDO_LIST_TO_ASN(Dz1IncidentTerminationInfoResponse)
DZ1_TO_NEW_ASN_LIST(Dz1IncidentTerminationInfoResponse, ASN1List)

// Dz1IncidentTerminationInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionVideoFileInfoProvideResponse
static Dz1Error Dz1IncidentDetectionVideoFileInfoProvideResponse_add(Dz1IncidentDetectionVideoFileInfoProvideResponse* p, Dz1IncidentDetectionVideoFileInfoProvide* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1IncidentDetectionVideoFileInfoProvideResponseMkArrArg
{
	Dz1IncidentDetectionVideoFileInfoProvide** arr;
	unsigned int idx;
} Dz1IncidentDetectionVideoFileInfoProvideResponseMkArrArg;

static Dz1Error _Dz1IncidentDetectionVideoFileInfoProvideResponse_get_array(void* ptr, Dz1IncidentDetectionVideoFileInfoProvide* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentDetectionVideoFileInfoProvideResponseMkArrArg* arg = (Dz1IncidentDetectionVideoFileInfoProvideResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1IncidentDetectionVideoFileInfoProvide** Dz1IncidentDetectionVideoFileInfoProvideResponse_get_array(Dz1IncidentDetectionVideoFileInfoProvideResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1IncidentDetectionVideoFileInfoProvide** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1IncidentDetectionVideoFileInfoProvide**)Dz1Calloc(sizeof(Dz1IncidentDetectionVideoFileInfoProvide*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1IncidentDetectionVideoFileInfoProvideResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1IncidentDetectionVideoFileInfoProvideResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1IncidentDetectionVideoFileInfoProvideResponse_travelForward(Dz1IncidentDetectionVideoFileInfoProvideResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentDetectionVideoFileInfoProvide* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1IncidentDetectionVideoFileInfoProvideResponse_travelBackward(Dz1IncidentDetectionVideoFileInfoProvideResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentDetectionVideoFileInfoProvide* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1IncidentDetectionVideoFileInfoProvideResponse_count(Dz1IncidentDetectionVideoFileInfoProvideResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1IncidentDetectionVideoFileInfoProvideResponse* Dz1IncidentDetectionVideoFileInfoProvideResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentDetectionVideoFileInfoProvideResponse* ret = (Dz1IncidentDetectionVideoFileInfoProvideResponse*)Dz1Calloc(sizeof(Dz1IncidentDetectionVideoFileInfoProvideResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentDetectionVideoFileInfoProvideResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1IncidentDetectionVideoFileInfoProvide_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1IncidentDetectionVideoFileInfoProvideResponse_count;
			ret->travel = Dz1IncidentDetectionVideoFileInfoProvideResponse_travelForward;
			ret->travelForward = Dz1IncidentDetectionVideoFileInfoProvideResponse_travelForward;
			ret->travelBackward = Dz1IncidentDetectionVideoFileInfoProvideResponse_travelBackward;
			ret->get_array = Dz1IncidentDetectionVideoFileInfoProvideResponse_get_array;
			ret->add = Dz1IncidentDetectionVideoFileInfoProvideResponse_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentDetectionVideoFileInfoProvideResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1IncidentDetectionVideoFileInfoProvideResponse_clone(void* ptr, Dz1IncidentDetectionVideoFileInfoProvide* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentDetectionVideoFileInfoProvideResponse* p = (Dz1IncidentDetectionVideoFileInfoProvideResponse*)ptr;
	Dz1IncidentDetectionVideoFileInfoProvide* cloned = Dz1IncidentDetectionVideoFileInfoProvide_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1IncidentDetectionVideoFileInfoProvideResponse* Dz1IncidentDetectionVideoFileInfoProvideResponse_clone(Dz1IncidentDetectionVideoFileInfoProvideResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentDetectionVideoFileInfoProvideResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1IncidentDetectionVideoFileInfoProvideResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentDetectionVideoFileInfoProvideResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1IncidentDetectionVideoFileInfoProvideResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentDetectionVideoFileInfoProvideResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1IncidentDetectionVideoFileInfoProvideResponse_purge(Dz1IncidentDetectionVideoFileInfoProvideResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1IncidentDetectionVideoFileInfoProvideResponse_del(Dz1IncidentDetectionVideoFileInfoProvideResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1IncidentDetectionVideoFileInfoProvideResponse_dump(void* ptr, Dz1IncidentDetectionVideoFileInfoProvide* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	int tab = *(int*)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1IncidentDetectionVideoFileInfoProvide_dump(p, tab);
	return err;
}

void Dz1IncidentDetectionVideoFileInfoProvideResponse_dump(Dz1IncidentDetectionVideoFileInfoProvideResponse* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1IncidentDetectionVideoFileInfoProvideResponse_dump, (void*)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1IncidentDetectionVideoFileInfoProvideResponse_fdump(void* ptr, Dz1IncidentDetectionVideoFileInfoProvide* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	FILE* fp = arg->fp;
	int tab = *(int*)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1IncidentDetectionVideoFileInfoProvide_fdump(arg->fp, p, tab);
	return err;
}

void Dz1IncidentDetectionVideoFileInfoProvideResponse_fdump(FILE* fp, Dz1IncidentDetectionVideoFileInfoProvideResponse* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1IncidentDetectionVideoFileInfoProvideResponse_fdump, (void*)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
PSEUDO_LIST_FROM_ASN(Dz1IncidentDetectionVideoFileInfoProvideResponse, Dz1IncidentDetectionVideoFileInfoProvide, IncidentDetectionVideoFileInfoProvide)
DZ1_NEW_LIST_FROM_ASN(Dz1IncidentDetectionVideoFileInfoProvideResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1IncidentDetectionVideoFileInfoProvideResponse, Dz1IncidentDetectionVideoFileInfoProvide, IncidentDetectionVideoFileInfoProvide)
PSEUDO_LIST_TO_ASN(Dz1IncidentDetectionVideoFileInfoProvideResponse)
DZ1_TO_NEW_ASN_LIST(Dz1IncidentDetectionVideoFileInfoProvideResponse, ASN1List)

// Dz1IncidentDetectionVideoFileInfoProvideResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ControlStateInfoResponse
static Dz1Error Dz1ControlStateInfoResponse_add(Dz1ControlStateInfoResponse* p, Dz1ControlStateInfo* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1ControlStateInfoResponseMkArrArg
{
	Dz1ControlStateInfo** arr;
	unsigned int idx;
} Dz1ControlStateInfoResponseMkArrArg;

static Dz1Error _Dz1ControlStateInfoResponse_get_array(void* ptr, Dz1ControlStateInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ControlStateInfoResponseMkArrArg* arg = (Dz1ControlStateInfoResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1ControlStateInfo** Dz1ControlStateInfoResponse_get_array(Dz1ControlStateInfoResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1ControlStateInfo** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1ControlStateInfo**)Dz1Calloc(sizeof(Dz1ControlStateInfo*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ControlStateInfoResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1ControlStateInfoResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1ControlStateInfoResponse_travelForward(Dz1ControlStateInfoResponse* p, Dz1Error(*func)(void* ptr, Dz1ControlStateInfo* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1ControlStateInfoResponse_travelBackward(Dz1ControlStateInfoResponse* p, Dz1Error(*func)(void* ptr, Dz1ControlStateInfo* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1ControlStateInfoResponse_count(Dz1ControlStateInfoResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1ControlStateInfoResponse* Dz1ControlStateInfoResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ControlStateInfoResponse* ret = (Dz1ControlStateInfoResponse*)Dz1Calloc(sizeof(Dz1ControlStateInfoResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ControlStateInfoResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1ControlStateInfo_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1ControlStateInfoResponse_count;
			ret->travel = Dz1ControlStateInfoResponse_travelForward;
			ret->travelForward = Dz1ControlStateInfoResponse_travelForward;
			ret->travelBackward = Dz1ControlStateInfoResponse_travelBackward;
			ret->get_array = Dz1ControlStateInfoResponse_get_array;
			ret->add = Dz1ControlStateInfoResponse_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ControlStateInfoResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1ControlStateInfoResponse_clone(void* ptr, Dz1ControlStateInfo* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ControlStateInfoResponse* p = (Dz1ControlStateInfoResponse*)ptr;
	Dz1ControlStateInfo* cloned = Dz1ControlStateInfo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1ControlStateInfoResponse* Dz1ControlStateInfoResponse_clone(Dz1ControlStateInfoResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ControlStateInfoResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1ControlStateInfoResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ControlStateInfoResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1ControlStateInfoResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ControlStateInfoResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ControlStateInfoResponse_purge(Dz1ControlStateInfoResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1ControlStateInfoResponse_del(Dz1ControlStateInfoResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1ControlStateInfoResponse_dump(void* ptr, Dz1ControlStateInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	int tab = *(int*)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1ControlStateInfo_dump(p, tab);
	return err;
}

void Dz1ControlStateInfoResponse_dump(Dz1ControlStateInfoResponse* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1ControlStateInfoResponse_dump, (void*)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1ControlStateInfoResponse_fdump(void* ptr, Dz1ControlStateInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	FILE* fp = arg->fp;
	int tab = *(int*)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1ControlStateInfo_fdump(arg->fp, p, tab);
	return err;
}

void Dz1ControlStateInfoResponse_fdump(FILE* fp, Dz1ControlStateInfoResponse* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1ControlStateInfoResponse_fdump, (void*)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
PSEUDO_LIST_FROM_ASN(Dz1ControlStateInfoResponse, Dz1ControlStateInfo, ControlStateInfo)
DZ1_NEW_LIST_FROM_ASN(Dz1ControlStateInfoResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1ControlStateInfoResponse, Dz1ControlStateInfo, ControlStateInfo)
PSEUDO_LIST_TO_ASN(Dz1ControlStateInfoResponse)
DZ1_TO_NEW_ASN_LIST(Dz1ControlStateInfoResponse, ASN1List)

// Dz1ControlStateInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SensorStateInfoResponse
static Dz1Error Dz1SensorStateInfoResponse_add(Dz1SensorStateInfoResponse* p, Dz1SensorStateInfo* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1SensorStateInfoResponseMkArrArg
{
	Dz1SensorStateInfo** arr;
	unsigned int idx;
} Dz1SensorStateInfoResponseMkArrArg;

static Dz1Error _Dz1SensorStateInfoResponse_get_array(void* ptr, Dz1SensorStateInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SensorStateInfoResponseMkArrArg* arg = (Dz1SensorStateInfoResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1SensorStateInfo** Dz1SensorStateInfoResponse_get_array(Dz1SensorStateInfoResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1SensorStateInfo** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SensorStateInfo**)Dz1Calloc(sizeof(Dz1SensorStateInfo*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1SensorStateInfoResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1SensorStateInfoResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1SensorStateInfoResponse_travelForward(Dz1SensorStateInfoResponse* p, Dz1Error(*func)(void* ptr, Dz1SensorStateInfo* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1SensorStateInfoResponse_travelBackward(Dz1SensorStateInfoResponse* p, Dz1Error(*func)(void* ptr, Dz1SensorStateInfo* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1SensorStateInfoResponse_count(Dz1SensorStateInfoResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1SensorStateInfoResponse* Dz1SensorStateInfoResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1SensorStateInfoResponse* ret = (Dz1SensorStateInfoResponse*)Dz1Calloc(sizeof(Dz1SensorStateInfoResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SensorStateInfoResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1SensorStateInfo_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1SensorStateInfoResponse_count;
			ret->travel = Dz1SensorStateInfoResponse_travelForward;
			ret->travelForward = Dz1SensorStateInfoResponse_travelForward;
			ret->travelBackward = Dz1SensorStateInfoResponse_travelBackward;
			ret->get_array = Dz1SensorStateInfoResponse_get_array;
			ret->add = Dz1SensorStateInfoResponse_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SensorStateInfoResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1SensorStateInfoResponse_clone(void* ptr, Dz1SensorStateInfo* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SensorStateInfoResponse* p = (Dz1SensorStateInfoResponse*)ptr;
	Dz1SensorStateInfo* cloned = Dz1SensorStateInfo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1SensorStateInfoResponse* Dz1SensorStateInfoResponse_clone(Dz1SensorStateInfoResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1SensorStateInfoResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1SensorStateInfoResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SensorStateInfoResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1SensorStateInfoResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SensorStateInfoResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SensorStateInfoResponse_purge(Dz1SensorStateInfoResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1SensorStateInfoResponse_del(Dz1SensorStateInfoResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1SensorStateInfoResponse_dump(void* ptr, Dz1SensorStateInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	int tab = *(int*)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1SensorStateInfo_dump(p, tab);
	return err;
}

void Dz1SensorStateInfoResponse_dump(Dz1SensorStateInfoResponse* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1SensorStateInfoResponse_dump, (void*)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1SensorStateInfoResponse_fdump(void* ptr, Dz1SensorStateInfo* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	FILE* fp = arg->fp;
	int tab = *(int*)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1SensorStateInfo_fdump(arg->fp, p, tab);
	return err;
}

void Dz1SensorStateInfoResponse_fdump(FILE* fp, Dz1SensorStateInfoResponse* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1SensorStateInfoResponse_fdump, (void*)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
PSEUDO_LIST_FROM_ASN(Dz1SensorStateInfoResponse, Dz1SensorStateInfo, SensorStateInfo)
DZ1_NEW_LIST_FROM_ASN(Dz1SensorStateInfoResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1SensorStateInfoResponse, Dz1SensorStateInfo, SensorStateInfo)
PSEUDO_LIST_TO_ASN(Dz1SensorStateInfoResponse)
DZ1_TO_NEW_ASN_LIST(Dz1SensorStateInfoResponse, ASN1List)

// Dz1SensorStateInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MovingObjectResponse
static Dz1Error Dz1MovingObjectResponse_add(Dz1MovingObjectResponse* p, Dz1MovingObject* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1MovingObjectResponseMkArrArg
{
	Dz1MovingObject** arr;
	unsigned int idx;
} Dz1MovingObjectResponseMkArrArg;

static Dz1Error _Dz1MovingObjectResponse_get_array(void* ptr, Dz1MovingObject* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MovingObjectResponseMkArrArg* arg = (Dz1MovingObjectResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1MovingObject** Dz1MovingObjectResponse_get_array(Dz1MovingObjectResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1MovingObject** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1MovingObject**)Dz1Calloc(sizeof(Dz1MovingObject*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MovingObjectResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1MovingObjectResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1MovingObjectResponse_travelForward(Dz1MovingObjectResponse* p, Dz1Error(*func)(void* ptr, Dz1MovingObject* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1MovingObjectResponse_travelBackward(Dz1MovingObjectResponse* p, Dz1Error(*func)(void* ptr, Dz1MovingObject* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1MovingObjectResponse_count(Dz1MovingObjectResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1MovingObjectResponse* Dz1MovingObjectResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1MovingObjectResponse* ret = (Dz1MovingObjectResponse*)Dz1Calloc(sizeof(Dz1MovingObjectResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MovingObjectResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1MovingObject_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1MovingObjectResponse_count;
			ret->travel = Dz1MovingObjectResponse_travelForward;
			ret->travelForward = Dz1MovingObjectResponse_travelForward;
			ret->travelBackward = Dz1MovingObjectResponse_travelBackward;
			ret->get_array = Dz1MovingObjectResponse_get_array;
			ret->add = Dz1MovingObjectResponse_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MovingObjectResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1MovingObjectResponse_clone(void* ptr, Dz1MovingObject* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MovingObjectResponse* p = (Dz1MovingObjectResponse*)ptr;
	Dz1MovingObject* cloned = Dz1MovingObject_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1MovingObjectResponse* Dz1MovingObjectResponse_clone(Dz1MovingObjectResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1MovingObjectResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MovingObjectResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MovingObjectResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1MovingObjectResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MovingObjectResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MovingObjectResponse_purge(Dz1MovingObjectResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1MovingObjectResponse_del(Dz1MovingObjectResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1MovingObjectResponse_dump(void* ptr, Dz1MovingObject* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	int tab = *(int*)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1MovingObject_dump(p, tab);
	return err;
}

void Dz1MovingObjectResponse_dump(Dz1MovingObjectResponse* p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MovingObjectResponse_dump, (void*)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1MovingObjectResponse_fdump(void* ptr, Dz1MovingObject* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2* arg = (Dz1ListFDumpArg2*)ptr;
	FILE* fp = arg->fp;
	int tab = *(int*)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); Dz1MovingObject_fdump(arg->fp, p, tab);
	return err;
}

void Dz1MovingObjectResponse_fdump(FILE* fp, Dz1MovingObjectResponse* p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1MovingObjectResponse_fdump, (void*)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
PSEUDO_LIST_FROM_ASN(Dz1MovingObjectResponse, Dz1MovingObject, MovingObject)
DZ1_NEW_LIST_FROM_ASN(Dz1MovingObjectResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1MovingObjectResponse, Dz1MovingObject, MovingObject)
PSEUDO_LIST_TO_ASN(Dz1MovingObjectResponse)
DZ1_TO_NEW_ASN_LIST(Dz1MovingObjectResponse, ASN1List)

// Dz1MovingObjectResponse
////////////////////////////////////////////////////////////////////////////////

