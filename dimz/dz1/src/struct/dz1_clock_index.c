#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_clock_index.h>

typedef struct Dz1ClockIndexEntry
{
	u32_t index;
	void *data;
	Dz1DelFunc dataDel;
	Dz1DumpFunc dataDump;
} Dz1ClockIndexEntry;

static void Dz1ClockIndexEntryA_dump(Dz1ClockIndexEntry *p, int tab)
{
	u32_t h, m, s;
	if (p == NULL) return;

	s = p->index;
	h = s / 3600; s %= 3600;
	m = s / 60; s %= 60;
	if (p->data == NULL || p->dataDump == NULL)
		Dz1ThreadA_printf("%02u:%02u:%02u\n", h, m, s);
	else
	{
		Dz1ThreadA_printf("%02u:%02u:%02u = ", h, m, s);
		p->dataDump(p->data, tab);
	}
}
#ifndef UNIX_SYSTEM
static void Dz1ClockIndexEntryW_dump(Dz1ClockIndexEntry *p, int tab)
{
	u32_t h, m, s;
	if (p == NULL) return;

	s = p->index;
	h = s / 3600; s %= 3600;
	m = s / 60; s %= 60;
	if (p->data == NULL || p->dataDump == NULL)
		Dz1ThreadW_printf(L"%02u:%02u:%02u\n", h, m, s);
	else
	{
		Dz1ThreadW_printf(L"%02u:%02u:%02u = ", h, m, s);
		p->dataDump(p->data, tab);
	}
}
#endif
typedef struct _Dz1ClockIndex
{
	Dz1ClockIndexEntry *arr;
	u32_t size;
	u32_t cnt;
	u32_t ptr;
} _Dz1ClockIndex;

void *Dz1ClockIndex_new(u32_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1ClockIndex *ret = NULL;

	if (size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (_Dz1ClockIndex *)Dz1Calloc(sizeof(_Dz1ClockIndex), 1, errp)) == NULL) ERR_OUT(err);
	else
	{
		pthread_cleanup_push(Dz1ClockIndex_delAndSetNull, (void *)&ret);
		if ((ret->arr = (Dz1ClockIndexEntry *)Dz1Calloc(sizeof(Dz1ClockIndexEntry), size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->size = size;
			ret->cnt = 0;
			ret->ptr = 0;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ClockIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ClockIndex_del(void *pClockIndex)
{
	_Dz1ClockIndex *p = (_Dz1ClockIndex *)pClockIndex;
	if (p == NULL) return;
	if (p->arr)
	{
		/*
		u32_t i;
		for (i = 0; i < p->cnt; i++)
		{
			if (p->arr[i].data != NULL && p->arr[i].dataDel != NULL)
			{
				p->arr[i].dataDel(p->arr[i].data);
				p->arr[i].data = NULL;
			}
		}
		*/
		Dz1Free(p->arr);
	}
	Dz1Free(p);
}

void Dz1ClockIndex_delAndSetNull(void *ppClockIndex)
{
	_Dz1ClockIndex **p = (_Dz1ClockIndex **)ppClockIndex;
	Dz1ClockIndex_del(*p); *p = NULL;
}

void Dz1ClockIndexA_dump(void *pClockIndex, int tab)
{
	_Dz1ClockIndex *p = (_Dz1ClockIndex *)pClockIndex;
	if (p == NULL) return;
	if (p->arr)
	{
		u32_t i;
		if (p->cnt == 0) Dz1ThreadA_tprintf(tab, "Empty\n");
		else
		{
			Dz1ThreadA_printf("{\n"); tab++;
			for (i = 0; i < p->cnt; i++)
			{
				Dz1ThreadA_tprintf(tab, "[%05u]", i);
				Dz1ClockIndexEntryA_dump(&p->arr[i], tab);
			}
			Dz1ThreadA_tprintf(--tab, "}\n");
		}
	}
}
#ifndef UNIX_SYSTEM
void Dz1ClockIndexW_dump(void *pClockIndex, int tab)
{
	_Dz1ClockIndex *p = (_Dz1ClockIndex *)pClockIndex;
	if (p == NULL) return;
	if (p->arr)
	{
		u32_t i;
		if (p->cnt == 0) Dz1ThreadW_tprintf(tab, L"Empty\n");
		else
		{
			Dz1ThreadW_printf(L"{\n"); tab++;
			for (i = 0; i < p->cnt; i++)
			{
				Dz1ThreadW_tprintf(tab, L"[%05u]", i);
				Dz1ClockIndexEntryW_dump(&p->arr[i], tab);
			}
			Dz1ThreadW_tprintf(--tab, L"}\n");
		}
	}
}
#endif
Dz1Error Dz1ClockIndex_addX(void *pClockIndex, u32_t tIDX, void **user_data, Dz1DelFunc user_data_del, Dz1DumpFunc user_data_dump)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	_Dz1ClockIndex *p = (_Dz1ClockIndex *)pClockIndex;
	if (p == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (p->cnt > 0 && p->arr[p->cnt - 1].index >= tIDX) ERR_SET_OUT(&err, EINVAL);
	else if (p->cnt >= p->size) ERR_SET_OUT(&err, ENOMEM);
	else
	{
		p->arr[p->cnt].index = tIDX;
		if (user_data != NULL)
		{
			p->arr[p->cnt].data = *user_data;
			p->arr[p->cnt].dataDel = user_data_del;
			p->arr[p->cnt].dataDump = user_data_dump;
			if (user_data_del != NULL) *user_data = NULL;
		}
		p->cnt++;
	}
	return err;
}

Dz1Error Dz1ClockIndex_add(void *pClockIndex, u32_t tIDX, void **user_data, Dz1DelFunc user_data_del)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1ClockIndex_addX(pClockIndex, tIDX, user_data, user_data_del, NULL)).code) ERR_OUT(&err);
	return err;
}

#define SECOND_OF_DAY	86400

static time_t getBaseTime(time_t t)
{
	time_t _z = 0;
	struct tm *tm_p = localtime(&t), tm = tm_p == NULL ? *(localtime(&_z)) : *tm_p;
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	return mktime(&tm);
}

static u32_t getDailyClock(time_t t)
{
	time_t _z = 0;
	struct tm *tm_p = localtime(&t), tm = tm_p == NULL ? *(localtime(&_z)) : *tm_p;
	return tm.tm_hour * 3600 + tm.tm_min * 60 + tm.tm_sec;
}

time_t Dz1ClockIndex_mostClosedTime(void *pClockIndex, void **curData, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1ClockIndex *p = (_Dz1ClockIndex *)pClockIndex;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->cnt == 0) ERR_SET_OUT(errp, ESRCH);
	else
	{
		time_t tNow = time(NULL);
		time_t tBase = getBaseTime(tNow);
		u32_t idx = getDailyClock(tNow), i, mod = 0;
		bool_t found = FALSE;
		while(1)
		{
			found = FALSE;

			for (i = 0; i < p->cnt; i++)
			{
				if (idx < (p->arr[i].index + mod))
				{
					found = TRUE;
					break;
				}
			}

			if (found)
			{
				p->ptr = i;
				if (curData != NULL)
				{
					u32_t current = i > 0 ? i - 1 : p->cnt - 1;
					(*curData) = p->arr[current].data;
				}
				return tBase + p->arr[i].index + mod;
			}
			else mod += SECOND_OF_DAY;
		}
	}
	return (time_t)-1;
}

void *Dz1ClockIndex_getData(void *pClockIndex, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1ClockIndex *p = (_Dz1ClockIndex *)pClockIndex;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	return p->arr[p->ptr].data;
}

