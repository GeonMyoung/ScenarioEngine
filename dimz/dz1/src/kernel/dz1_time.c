#include <dz1_time.h>
#include "dz1_thread_stdio.h"
#include <dz1_str.h>
#include "dz1_malloc.h"

Dz1Error Dz1Time_getMonotonic(u32_t *dst_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst_us == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
#if defined(LINUX)
#	ifndef CLOCK_MONOTONIC
#		define CLOCK_MONOTONIC		1
#	endif
		struct timespec t;
		if (clock_gettime(CLOCK_MONOTONIC, &t)) ERR_SET_OUT(&err, EFAULT);
		else *dst_us = t.tv_sec * 1000000 + t.tv_nsec / 1000;
#elif defined(WIN32) || defined(__BORLANDC__)
		*dst_us = GetTickCount() * 1000;
#endif
	}
	return err;
}

#define SCHEDULE_REPEAT		100

static pthread_mutex_t minTimeDelay_locak = PTHREAD_MUTEX_INITIALIZER;
static u32_t minTimeDelay_ms = 0;
static int minTimeDelay_caliberated = 0;

static __inline__ u64_t ts2us(struct timespec t)
{
	u64_t ret = (u64_t)t.tv_sec * 1000000 + (t.tv_nsec / 1000);
	return ret;
}

static __inline__ u64_t tv2us(struct timeval t)
{
	u64_t ret = (u64_t)t.tv_sec * 1000000 + t.tv_usec;
	return ret;
}

void Dz1Time_calibrateMinTimeDelay(void)
{
	pthread_mutex_lock(&minTimeDelay_locak);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&minTimeDelay_locak);

	if (minTimeDelay_caliberated == 0)
	{
#ifndef UNIX_SYSTEM // win32 and else win32 like...
		struct timeval t0, t1;
#else
#ifdef MAC_OS_X
		struct timeval t0, t1;
#else
		struct timespec t0, t1;
#endif
#endif
		u64_t avg_us = 0, max = 0, curr = 0;
		int cnt = SCHEDULE_REPEAT;

		Dz1Thread_eprintf("Dz1Time_calibrateMinTimeDelay() : Minimum delay time Calibrating...");
		while(cnt--)
		{
#ifndef UNIX_SYSTEM
			gettimeofday(&t0, NULL);
			Sleep(1);
			gettimeofday(&t1, NULL);

			t1.tv_sec -= t0.tv_sec;
			if (t1.tv_usec < t0.tv_usec)
			{
				t1.tv_usec = 1000000 - t0.tv_usec + t1.tv_usec;
				t1.tv_sec--;
			}
			else t1.tv_usec -= t0.tv_usec;

			curr = tv2us(t1) - 1000;
#else
#ifdef MAC_OS_X
			gettimeofday(&t0, NULL);
			usleep(0);
			gettimeofday(&t1, NULL);

			t1.tv_sec -= t0.tv_sec;
			if (t1.tv_usec < t0.tv_usec)
			{
				t1.tv_usec = 1000000 - t0.tv_usec + t1.tv_usec;
				t1.tv_sec--;
			}
			else t1.tv_usec -= t0.tv_usec;

			curr = tv2us(t1) - 1000;
#else
			clock_gettime(CLOCK_REALTIME, &t0);
			usleep(0);
			clock_gettime(CLOCK_REALTIME, &t1);

			t1.tv_sec -= t0.tv_sec;
			if (t1.tv_nsec < t0.tv_nsec)
			{
				t1.tv_nsec = 1000000000 - t0.tv_nsec + t1.tv_nsec;
				t1.tv_sec--;
			}
			else t1.tv_nsec -= t0.tv_nsec;

			curr = ts2us(t1);
#endif
#endif
			if (max < curr) max = curr;
			avg_us += curr;
		}
		avg_us = (avg_us - max) / (SCHEDULE_REPEAT - 1);

//		printf("avg_us = %llu\n", avg_us); fflush(stdout);
		minTimeDelay_ms = (u32_t)((avg_us << 2) / 1000);
		minTimeDelay_caliberated = 1;
		Dz1Thread_eprintf("done\n");
		Dz1Thread_eprintf("Minimum delay time is %d ms\n", minTimeDelay_ms);
	}

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&minTimeDelay_locak);
}

u32_t Dz1Time_getMinTimeDelay(void)
{
	if (minTimeDelay_caliberated == 0) Dz1Time_calibrateMinTimeDelay();
	return minTimeDelay_ms;
}

void Dz1Time_setMinTimeDelay(int v_ms)
{
	pthread_mutex_lock(&minTimeDelay_locak);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&minTimeDelay_locak);
	minTimeDelay_caliberated = 1;
	minTimeDelay_ms = v_ms;
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&minTimeDelay_locak);
}

time_t *time_clone(time_t *t, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	time_t *ret = (time_t *)Dz1Calloc(sizeof(time_t), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else memcpy(ret, t, sizeof(time_t));
	return ret;
}

int time_cmp(time_t *a, time_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

void timeA_dump(time_t *t, int tab)
{
	if (!t) Dz1ThreadA_printf("NULL\n");
	else
	{
		struct tm *tm_p = localtime(t);
		struct tm tm;
		if (tm_p == NULL) Dz1ThreadA_printf("Invalid Time Value(%08X)\n", *t);
		else
		{
			tm = *tm_p;
			Dz1ThreadA_printf(DZ1_TIME_TM_FMT_FULL_A "\n", DZ1_TIME_TM_ARG_FULL(&tm));
		}
	}
}

void timeA_fdump( FILE *fp, time_t *t, int tab)
{
	if (!fp) return;
	else if (!t) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		struct tm *tm_p = localtime(t);
		struct tm tm;
		if (tm_p == NULL) Dz1ThreadA_fprintf(fp, "Invalid Time Value(%08X)\n", *t);
		else
		{
			tm = *tm_p;
			Dz1ThreadA_fprintf(fp, DZ1_TIME_TM_FMT_FULL_A "\n", DZ1_TIME_TM_ARG_FULL(&tm));
		}
	}
}
#ifndef UNIX_SYSTEM
void timeW_dump(time_t *t, int tab)
{
	if (!t) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		struct tm *tm_p = localtime(t);
		struct tm tm;
		if (tm_p == NULL) Dz1ThreadW_printf(L"Invalid Time Value(%08X)\n", *t);
		else
		{
			tm = *tm_p;
			Dz1ThreadW_printf(DZ1_TIME_TM_FMT_FULL_W L"\n", DZ1_TIME_TM_ARG_FULL(&tm));
		}
	}
}

void timeW_fdump( FILE *fp, time_t *t, int tab)
{
	if (!fp) return;
	else if (!t) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		struct tm *tm_p = localtime(t);
		struct tm tm;
		if (tm_p == NULL) Dz1ThreadW_fprintf(fp, L"Invalid Time Value(%08X)\n", *t);
		else
		{
			tm = *tm_p;
			Dz1ThreadW_fprintf(fp, DZ1_TIME_TM_FMT_FULL_W L"\n", DZ1_TIME_TM_ARG_FULL(&tm));
		}
	}
}

int gettimeofday(struct timeval *t, void *temp)
{
	struct _timeb _t;
	_ftime(&_t);
	t->tv_sec = (long)_t.time;
	t->tv_usec = _t.millitm * 1000;
	return 0;
}

int settimeofday(struct timeval *t, void *tz)
{
	struct tm *tm_p = gmtime((const time_t *)&t->tv_sec), tm = *tm_p;
	SYSTEMTIME _t; // SYSTIME _t should be GMT Time!
	_t.wYear = tm.tm_year + 1900;
	_t.wMonth = tm.tm_mon + 1;
	_t.wDay = tm.tm_mday;
	_t.wHour = tm.tm_hour;
	_t.wMinute = tm.tm_min;
	_t.wSecond = tm.tm_sec;
	_t.wMilliseconds = (u16_t)(t->tv_usec / 1000);
// 	{	// Dump Local Time
// 		struct tm *tm_p1 = localtime((const time_t *)&t->tv_sec), tm1 = *tm_p1;
//         Dz1Thread_eprintf("Time Set to "DZ1_TIME_TM_FMT_FULL_A"\n", DZ1_TIME_TM_ARG_FULL(&tm1));
// 	}
	return SetSystemTime(&_t) == TRUE ? 0 : -1;
}
#endif

static bool_t _isDateDelimiterA(char c)
{
	bool_t ret = FALSE;
	switch(c)
	{
	case '-': 
	case '/': 
	case '.': 
		ret = TRUE; 
		break;
	}
	return ret;
}

static bool_t _is_digit_strA(str_t str)
{
	bool_t ret = TRUE;
	char *cp = str;
	while(*cp)
	{
		if (!isdigit(*cp))
		{
			ret = FALSE;
			break;
		}
	}
	return ret;
}

static bool_t _Dz1TmDateFromStrA_mode1(struct tm *dst, str_t strYYYYMMDD, Dz1Error *errp)
{	// 9999-99-99
	u32_t yy, mm, dd;
	char temp[11]= { 0, }, *cp = temp, *yp = NULL, *mp = NULL, *dp = NULL;
	strncpy(temp, strYYYYMMDD, 10);
	yp = cp; cp += 4;
	*cp++ = 0;
	mp = cp; cp += 2;
	*cp++ = 0;
	dp = cp; cp += 2;
	*cp = 0;
	if ((yy = Dz1Ato32(yp)) < 1900) ERR_SET_OUT(errp, EINVAL);
	else if ((mm = Dz1Ato32(mp)) > 12 || mm == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((dd = Dz1Ato32(dp)) > 31 || dd == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->tm_year = yy - 1900;
		dst->tm_mon = mm - 1;
		dst->tm_mday = dd;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1TmDateFromStrA_mode2(struct tm *dst, str_t strYYYYMMDD, Dz1Error *errp)
{
	char temp[11] = { 0, }, *dp = temp, *sp = strYYYYMMDD;
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = '-';
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = '-';
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = 0;
	return _Dz1TmDateFromStrA_mode1(dst, temp, errp);
}

bool_t Dz1TmDateFromStrA(struct tm *dst, str_t strYYYYMMDD, Dz1Error *err)
{	// 9999-99-99 = 10, 99991231 = 8
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	char *cp = strYYYYMMDD;
	if (dst == NULL || strYYYYMMDD == NULL || strYYYYMMDD[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((len = strlen(strYYYYMMDD)) != 10 && len != 8) ERR_SET_OUT(errp, EINVAL);
	else
	{
		switch(len)
		{
		case 10:
			if (!_isDateDelimiterA(cp[4]) || !_isDateDelimiterA(cp[7])) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmDateFromStrA_mode1(dst, cp, errp) == FALSE) ERR_OUT(errp);	// 9999-99-99
			else Dz1Error_set(errp, 0);
			break;
		case 8:
			if (_is_digit_strA(cp))
			{
				if (_Dz1TmDateFromStrA_mode2(dst, cp, errp) == FALSE) ERR_OUT(errp);	// 99991231
				else Dz1Error_set(errp, 0);
			}
			else ERR_SET_OUT(errp, EINVAL);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _isTimeDelimiterA(char c)
{
	bool_t ret = FALSE;
	switch(c)
	{
	case ':': 
	case '-':
	case '.':
		ret = TRUE;
	}
	return ret;
}

static bool_t _Dz1TmTimeFromStrA_mode1(struct tm *dst, str_t strHHMMSS, Dz1Error *errp)
{	// hh:mm:ss
	u32_t hh, mm, ss;
	char temp[9]= { 0, }, *cp = temp, *hp = NULL, *mp = NULL, *sp = NULL;
	strncpy(temp, strHHMMSS, 8);
	hp = cp; cp += 2;
	*cp++ = 0;
	mp = cp; cp += 2;
	*cp++ = 0;
	sp = cp; cp += 2;
	*cp = 0;
	if ((hh = Dz1Ato32(hp)) > 23) ERR_SET_OUT(errp, EINVAL);
	else if ((mm = Dz1Ato32(mp)) > 59) ERR_SET_OUT(errp, EINVAL);
	else if ((ss = Dz1Ato32(sp)) > 59) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->tm_hour = hh;
		dst->tm_min = mm;
		dst->tm_sec = ss;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1TmTimeFromStrA_mode2(struct tm *dst, str_t strHHMMSS, Dz1Error *errp)
{	// hhmmss
	char temp[9], *dp = temp, *cp = strHHMMSS;
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = 0;
	return _Dz1TmTimeFromStrA_mode1(dst, temp, errp);
}

static bool_t _Dz1TmTimeFromStrA_mode3(struct tm *dst, str_t strHHMMSS, Dz1Error *errp)
{	// hh:mm
	char temp[9], *dp = temp, *cp = strHHMMSS;
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':'; cp++;
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = '0';
	*dp++ = '0';
	*dp++ = 0;
	return _Dz1TmTimeFromStrA_mode1(dst, temp, errp);
}

static bool_t _Dz1TmTimeFromStrA_mode4(struct tm *dst, str_t strHHMMSS, Dz1Error *errp)
{	// hhmm
	char temp[9], *dp = temp, *cp = strHHMMSS;
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = '0';
	*dp++ = '0';
	*dp++ = 0;
	return _Dz1TmTimeFromStrA_mode1(dst, temp, errp);
}

bool_t Dz1TmTimeFromStrA(struct tm *dst, str_t strHHMMSS, Dz1Error *err)
{	// hh:mm:ss = 8, hhmmss = 6 hh:mm = 5, hhmm = 4
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	if (dst == NULL || strHHMMSS == NULL || strHHMMSS[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((len = strlen(strHHMMSS)) != 10 && len != 8) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char *cp = strHHMMSS;
		switch(len)
		{
		case 8: // hh:mm:ss
			if (!_isTimeDelimiterA(cp[2]) || !_isTimeDelimiterA(cp[5])) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmTimeFromStrA_mode1(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 6: // hhmmss
			if (_is_digit_strA(strHHMMSS)) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmTimeFromStrA_mode2(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 5: // hh:mm
			if (!_isTimeDelimiterA(cp[2])) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmTimeFromStrA_mode3(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 4: // hhmm
			if (_is_digit_strA(strHHMMSS)) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmTimeFromStrA_mode4(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TmFromStrA_DT(struct tm *dst, str_t strYYYYMMDD, str_t strHHMMSS, Dz1Error *err)
{	// 9999-99-99 = 10, 99-99-99 = 8 99991231 = 8, 991231 = 6 // hh:mm:ss = 8, hhmmss = 6 hh:mm = 5, hhmm = 4
	DZ1_ERROR_SAFE_PTR(errp, err);
	
	if (Dz1TmDateFromStrA(dst, strYYYYMMDD, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TmTimeFromStrA(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TmFromStrA(struct tm *dst, str_t strYYYYMMDDHHMMSS, Dz1Error *err)
{	// 9999-99-99 hh:mm:ss
	DZ1_ERROR_SAFE_PTR(errp, err);
	char *cp = strYYYYMMDDHHMMSS;
	size_t len = strlen(cp);
	if (len < 19 || !_isDateDelimiterA(cp[4]) || !_isDateDelimiterA(cp[7]) || cp[10] != ' ' || !_isTimeDelimiterA(cp[13]) || !_isTimeDelimiterA(cp[16])) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char dt[10] = { 0, }, ti[9] = { 0, };
		strncpy(dt, cp, 10); cp += 10;
		cp++;
		strncpy(ti, cp, 8); cp += 8;

		if (Dz1TmFromStrA_DT(dst, dt, ti, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
static bool_t _isDateDelimiterW(wchar_t c)
{
	bool_t ret = FALSE;
	switch(c)
	{
	case L'-': 
	case L'/': 
	case L'.': 
		ret = TRUE; 
		break;
	}
	return ret;
}

static bool_t _isTimeDelimiterW(wchar_t c)
{
	bool_t ret = FALSE;
	switch(c)
	{
	case L':': 
	case L'-':
	case L'.':
		ret = TRUE;
	}
	return ret;
}

static bool_t _is_digit_strW(wstr_t str)
{
	bool_t ret = TRUE;
	wchar_t *cp = str;
	while(*cp)
	{
		if (!iswdigit(*cp))
		{
			ret = FALSE;
			break;
		}
	}
	return ret;
}

static bool_t _Dz1TmDateFromStrW_mode1(struct tm *dst, wstr_t strYYYYMMDD, Dz1Error *errp)
{	// 9999-99-99
	u32_t yy, mm, dd;
	wchar_t temp[11]= { 0, }, *cp = temp, *yp = NULL, *mp = NULL, *dp = NULL;
	wcsncpy(temp, strYYYYMMDD, 10);
	yp = cp; cp += 4;
	*cp++ = 0;
	mp = cp; cp += 2;
	*cp++ = 0;
	dp = cp; cp += 2;
	*cp = 0;
	if ((yy = Dz1Wto32(yp)) < 1900) ERR_SET_OUT(errp, EINVAL);
	else if ((mm = Dz1Wto32(mp)) > 12 || mm == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((dd = Dz1Wto32(dp)) > 31 || dd == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->tm_year = yy - 1900;
		dst->tm_mon = mm - 1;
		dst->tm_mday = dd;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1TmDateFromStrW_mode2(struct tm *dst, wstr_t strYYYYMMDD, Dz1Error *errp)
{
	wchar_t temp[11] = { 0, }, *dp = temp, *sp = strYYYYMMDD;
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = '-';
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = '-';
	*dp++ = *sp++;
	*dp++ = *sp++;
	*dp++ = 0;
	return _Dz1TmDateFromStrW_mode1(dst, temp, errp);
}

bool_t Dz1TmDateFromStrW(struct tm *dst, wstr_t strYYYYMMDD, Dz1Error *err)
{	// 9999-99-99 = 10, 99991231 = 8
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	wchar_t *cp = strYYYYMMDD;
	if (dst == NULL || strYYYYMMDD == NULL || strYYYYMMDD[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((len = wcslen(strYYYYMMDD)) != 10 && len != 8) ERR_SET_OUT(errp, EINVAL);
	else
	{
		switch(len)
		{
		case 10:
			if (!_isDateDelimiterW(cp[4]) || !_isDateDelimiterW(cp[7])) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmDateFromStrW_mode1(dst, cp, errp) == FALSE) ERR_OUT(errp);	// 9999-99-99
			else Dz1Error_set(errp, 0);
			break;
		case 8:
			if (_is_digit_strW(cp))
			{
				if (_Dz1TmDateFromStrW_mode2(dst, cp, errp) == FALSE) ERR_OUT(errp);	// 99991231
				else Dz1Error_set(errp, 0);
			}
			else ERR_SET_OUT(errp, EINVAL);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1TmTimeFromStrW_mode1(struct tm *dst, wstr_t strHHMMSS, Dz1Error *errp)
{	// hh:mm:ss
	u32_t hh, mm, ss;
	wchar_t temp[9]= { 0, }, *cp = temp, *hp = NULL, *mp = NULL, *sp = NULL;
	wcsncpy(temp, strHHMMSS, 8);
	hp = cp; cp += 2;
	*cp++ = 0;
	mp = cp; cp += 2;
	*cp++ = 0;
	sp = cp; cp += 2;
	*cp = 0;
	if ((hh = Dz1Wto32(hp)) > 23) ERR_SET_OUT(errp, EINVAL);
	else if ((mm = Dz1Wto32(mp)) > 59) ERR_SET_OUT(errp, EINVAL);
	else if ((ss = Dz1Wto32(sp)) > 59) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->tm_hour = hh;
		dst->tm_min = mm;
		dst->tm_sec = ss;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1TmTimeFromStrW_mode2(struct tm *dst, wstr_t strHHMMSS, Dz1Error *errp)
{	// hhmmss
	wchar_t temp[9], *dp = temp, *cp = strHHMMSS;
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = 0;
	return _Dz1TmTimeFromStrW_mode1(dst, temp, errp);
}

static bool_t _Dz1TmTimeFromStrW_mode3(struct tm *dst, wstr_t strHHMMSS, Dz1Error *errp)
{	// hh:mm
	wchar_t temp[9], *dp = temp, *cp = strHHMMSS;
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':'; cp++;
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = '0';
	*dp++ = '0';
	*dp++ = 0;
	return _Dz1TmTimeFromStrW_mode1(dst, temp, errp);
}

static bool_t _Dz1TmTimeFromStrW_mode4(struct tm *dst, wstr_t strHHMMSS, Dz1Error *errp)
{	// hhmm
	wchar_t temp[9], *dp = temp, *cp = strHHMMSS;
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = *cp++;
	*dp++ = *cp++;
	*dp++ = ':';
	*dp++ = '0';
	*dp++ = '0';
	*dp++ = 0;
	return _Dz1TmTimeFromStrW_mode1(dst, temp, errp);
}

bool_t Dz1TmTimeFromStrW(struct tm *dst, wstr_t strHHMMSS, Dz1Error *err)
{	// hh:mm:ss = 8, hhmmss = 6 hh:mm = 5, hhmm = 4
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	if (dst == NULL || strHHMMSS == NULL || strHHMMSS[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((len = wcslen(strHHMMSS)) != 10 && len != 8) ERR_SET_OUT(errp, EINVAL);
	else
	{
		wchar_t *cp = strHHMMSS;
		switch(len)
		{
		case 8: // hh:mm:ss
			if (!_isTimeDelimiterW(cp[2]) || !_isTimeDelimiterW(cp[5])) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmTimeFromStrW_mode1(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 6: // hhmmss
			if (_is_digit_strW(strHHMMSS)) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmTimeFromStrW_mode2(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 5: // hh:mm
			if (!_isTimeDelimiterW(cp[2])) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmTimeFromStrW_mode3(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case 4: // hhmm
			if (_is_digit_strW(strHHMMSS)) ERR_SET_OUT(errp, EINVAL);
			else if (_Dz1TmTimeFromStrW_mode4(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TmFromStrW_DT(struct tm *dst, wstr_t strYYYYMMDD, wstr_t strHHMMSS, Dz1Error *err)
{	// 9999-99-99 = 10, 99-99-99 = 8 99991231 = 8, 991231 = 6 // hh:mm:ss = 8, hhmmss = 6 hh:mm = 5, hhmm = 4
	DZ1_ERROR_SAFE_PTR(errp, err);
	
	if (Dz1TmDateFromStrW(dst, strYYYYMMDD, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TmTimeFromStrW(dst, strHHMMSS, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TmFromStrW(struct tm *dst, wstr_t strYYYYMMDDHHMMSS, Dz1Error *err)
{	// 9999-99-99 hh:mm:ss
	DZ1_ERROR_SAFE_PTR(errp, err);
	wchar_t *cp = strYYYYMMDDHHMMSS;
	size_t len = wcslen(cp);
	if (len < 19 || !_isDateDelimiterW(cp[4]) || !_isDateDelimiterW(cp[7]) || cp[10] != ' ' || !_isTimeDelimiterW(cp[13]) || !_isTimeDelimiterW(cp[16])) ERR_SET_OUT(errp, EINVAL);
	else
	{
		wchar_t dt[10] = { 0, }, ti[9] = { 0, };
		wcsncpy(dt, cp, 10); cp += 10;
		cp++;
		wcsncpy(ti, cp, 8); cp += 8;

		if (Dz1TmFromStrW_DT(dst, dt, ti, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif

static pthread_mutex_t tz_lock = PTHREAD_MUTEX_INITIALIZER;
static bool_t tz_flag = FALSE;
static s32_t tz_sec = 0;

s32_t Dz1Time_GetGmtOffset(void)
{
	s32_t ret = 0;
	pthread_mutex_lock(&tz_lock);
	if (tz_flag == FALSE)
	{
		time_t tBias, tRef;
		struct tm tmB, *tmTemp = NULL, tmR;
		tmB.tm_year = 71;			// 1971
		tmB.tm_mon = 0;				// 1
		tmB.tm_mday = 1;			// 1
		tmB.tm_hour = 0;			// 0
		tmB.tm_min = 0;				// 0
		tmB.tm_sec = 0;				// 0
		tBias = mktime(&tmB);		// UTC time
		tmTemp = gmtime(&tBias); 
		tmR = *tmTemp;				// GMT Date-Time
		tRef = mktime(&tmR);		// Ref time

		tz_sec = (s32_t)(tBias - tRef);
	}
	ret = tz_sec;
	pthread_mutex_unlock(&tz_lock);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Nano-Second Time
#ifdef UNIX_SYSTEM
#else
static int hires_freq_status = 0;
static LARGE_INTEGER hires_freq = { 0 };
static bool_t _init_hires_freq(Dz1Error *errp)
{
	switch(hires_freq_status)
	{
	case 0:
		if (QueryPerformanceFrequency(&hires_freq) == FALSE) Dz1Error_set(errp, GetLastError());
		else if (hires_freq.QuadPart == 0)
		{
			hires_freq_status = -1;
			Dz1Error_set(errp, ENOSYS);
		}
		else
		{
			hires_freq_status = 1;
			Dz1Error_set(errp, 0);
		}
		break;
	case -1:
		Dz1Error_set(errp, ENOSYS);
		break;
	default: Dz1Error_set(errp, 0); break;
	}
	return ERR_IS_SUCCESS(errp);
}
#endif

bool_t Dz1Time_getNanoTime(s64_t *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
#ifdef UNIX_SYSTEM
	// XXX : Implement it
#else
	LARGE_INTEGER hires_time = { 0 };
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_init_hires_freq(errp) == FALSE) ERR_OUT(errp);
	else if (!QueryPerformanceCounter(&hires_time)) ERR_SET_OUT(errp, GetLastError());
	else
	{
		s64_t ns_per_tick = 1000000000 / hires_freq.QuadPart;
		if (ns_per_tick == 0) ns_per_tick = 1;
		*dst = hires_time.QuadPart * ns_per_tick;
		Dz1Error_set(errp, 0);
	}
#endif
	return ERR_IS_SUCCESS(errp);
}
// Nano-Second Time
///////////////////////////////////////////////////////////////////////////////

