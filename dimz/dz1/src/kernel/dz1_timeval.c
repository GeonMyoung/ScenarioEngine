#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_timeval.h>

Dz1TimeVal *Dz1TimeVal_new(u16_t year, u8_t month, u8_t day, u8_t h, u8_t m, u8_t s, u32_t usec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TimeVal *ret = NULL;
	
	if (year < 1900 || month > 11 || day >= 31) ERR_SET_OUT(errp, EINVAL);
	else if (h > 23 || m > 59 || s >= 59) ERR_SET_OUT(errp, EINVAL);
	if ((ret = (Dz1TimeVal *)Dz1Calloc(sizeof(Dz1TimeVal), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		struct tm tmTemp;
		tmTemp.tm_year = year - 1900;
		tmTemp.tm_mon = month - 1;
		tmTemp.tm_mday = day;
		tmTemp.tm_hour = h;
		tmTemp.tm_min = m;
		tmTemp.tm_sec = s;
		ret->tv_sec = (long)mktime(&tmTemp);
		ret->tv_usec = usec;
		Dz1Error_set(errp, 0);
	}
	return ret;
}
Dz1TimeVal *Dz1TimeVal_newFromTime(time_t *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TimeVal *ret = NULL, temp;
	if (src == NULL) temp = Dz1TimeVal_get();
	else { temp.tv_sec = (long)(*src); temp.tv_usec = 0; };

	if ((ret = Dz1TimeVal_clone(&temp, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

Dz1TimeVal *Dz1TimeVal_clone(Dz1TimeVal *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TimeVal *ret = (Dz1TimeVal *)Dz1Malloc(sizeof(Dz1TimeVal), errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->tv_sec = src->tv_sec;
		ret->tv_usec = src->tv_usec;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1TimeVal_del(Dz1TimeVal *t)
{
	if (t == NULL) return;
	Dz1Free(t);
}

void Dz1TimeValA_dump(Dz1TimeVal *t, int tab)
{
	if (!t) Dz1ThreadA_printf("NULL\n");
	else
	{
		time_t tTemp = t->tv_sec;
		struct tm *tm_p = localtime((const time_t *)&tTemp);
		if (tm_p == NULL) Dz1ThreadA_printf("%lu.%06lu\n", t->tv_sec, t->tv_usec);
		else
		{
			struct tm tm = *tm_p;
			Dz1ThreadA_printf("%04d-%02d-%02d %02d:%02d:%02d.%06d\n",
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
				tm.tm_hour, tm.tm_min, tm.tm_sec, t->tv_usec);
		}
	}
}
void Dz1TimeValA_fdump(FILE *fp, Dz1TimeVal *t, int tab)
{
	if (!t) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		time_t tTemp = t->tv_sec;
		struct tm *tm_p = localtime((const time_t *)&tTemp);
		if (tm_p == NULL) Dz1ThreadA_fprintf(fp, "%lu.%06lu\n", t->tv_sec, t->tv_usec);
		else
		{
			struct tm tm = *tm_p;
			Dz1ThreadA_fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d.%06d\n",
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
				tm.tm_hour, tm.tm_min, tm.tm_sec, t->tv_usec);
		}
	}
}
#ifndef UNIX_SYSTEM
void Dz1TimeValW_dump(Dz1TimeVal *t, int tab)
{
	if (!t) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		time_t tTemp = t->tv_sec;
		struct tm *tm_p = localtime((const time_t *)&tTemp);
		if (tm_p == NULL) Dz1ThreadW_printf(L"%lu.%06lu\n", t->tv_sec, t->tv_usec);
		else
		{
			struct tm tm = *tm_p;
			Dz1ThreadW_printf(L"%04d-%02d-%02d %02d:%02d:%02d.%06d\n",
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
				tm.tm_hour, tm.tm_min, tm.tm_sec, t->tv_usec);
		}
	}
}
void Dz1TimeValW_fdump(FILE *fp, Dz1TimeVal *t, int tab)
{
	if (!t) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		time_t tTemp = t->tv_sec;
		struct tm *tm_p = localtime((const time_t *)&tTemp);
		if (tm_p == NULL) Dz1ThreadW_fprintf(fp, L"%lu.%06lu\n", t->tv_sec, t->tv_usec);
		else
		{
			struct tm tm = *tm_p;
			Dz1ThreadW_fprintf(fp, L"%04d-%02d-%02d %02d:%02d:%02d.%06d\n",
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
				tm.tm_hour, tm.tm_min, tm.tm_sec, t->tv_usec);
		}
	}
}
#endif