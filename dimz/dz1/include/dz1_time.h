#ifndef DZ1_TIME_H
#define DZ1_TIME_H

#include <dz1_error.h>
#include <dz1_thread_stdio.h>

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	Dz1Time_getMonotonic(u32_t *dst_us);
DZ1_CPPLINK DZ1_DLLPORT void		Dz1Time_calibrateMinTimeDelay(void);
DZ1_CPPLINK DZ1_DLLPORT u32_t		Dz1Time_getMinTimeDelay(void);
DZ1_CPPLINK DZ1_DLLPORT void		Dz1Time_setMinTimeDelay(int v_ms);

DZ1_CPPLINK DZ1_DLLPORT time_t	*time_clone(time_t *t, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT int		 time_cmp(time_t *a, time_t *b);
DZ1_CPPLINK DZ1_DLLPORT void	 timeA_dump(time_t *t, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 timeA_fdump(FILE *fp, time_t *t, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 timeW_dump(time_t *t, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 timeW_fdump(FILE *fp, time_t *t, int tab);
#ifdef UNICODE
#define							 time_dump			timeW_dump
#define							 time_fdump			timeW_fdump
#else // UNICODE
#define							 time_dump			timeA_dump
#define							 time_fdump			timeA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 time_dump			timeA_dump
#define							 time_fdump			timeA_fdump
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
#include <sys/timeb.h>
DZ1_CPPLINK DZ1_DLLPORT int gettimeofday(struct timeval *t, void *temp);
DZ1_CPPLINK DZ1_DLLPORT int settimeofday(struct timeval *t, void *tz);
#endif

#define Dz1Time_diff(start, end)		((start > end) ? (~(start)) + (end) : (end) - (start))

static __inline__ struct timeval Dz1GetTimeval(void)
{
	struct timeval ret;
	gettimeofday(&ret, NULL);
	return ret;
}

DZ1_CPPLINK s32_t Dz1Time_GetGmtOffset(void);


#define DZ1_TIME_TM_FMT_DATE_A		"%04u-%02u-%02u"
#define DZ1_TIME_TM_FMT_TIME_A		"%02u:%02u:%02u"
#define DZ1_TIME_TM_FMT_FULL_A		"%04u-%02u-%02u %02u:%02u:%02u"
#ifndef UNIX_SYSTEM
#define DZ1_TIME_TM_FMT_DATE_W		DZ1WIDER2(DZ1_TIME_TM_FMT_DATE_A)
#define DZ1_TIME_TM_FMT_TIME_W		DZ1WIDER2(DZ1_TIME_TM_FMT_TIME_A)
#define DZ1_TIME_TM_FMT_FULL_W		DZ1WIDER2(DZ1_TIME_TM_FMT_FULL_A)
#ifdef UNICODE
#define DZ1_TIME_TM_FMT_DATE		DZ1_TIME_TM_FMT_DATE_W
#define DZ1_TIME_TM_FMT_TIME		DZ1_TIME_TM_FMT_TIME_W
#define DZ1_TIME_TM_FMT_FULL		DZ1_TIME_TM_FMT_FULL_W
#else // UNICODE
#define DZ1_TIME_TM_FMT_DATE		DZ1_TIME_TM_FMT_DATE_A
#define DZ1_TIME_TM_FMT_TIME		DZ1_TIME_TM_FMT_TIME_A
#define DZ1_TIME_TM_FMT_FULL		DZ1_TIME_TM_FMT_FULL_A
#endif // UNICODE
#else // UNIX_SYSTEM
#define DZ1_TIME_TM_FMT_DATE		DZ1_TIME_TM_FMT_DATE_A
#define DZ1_TIME_TM_FMT_TIME		DZ1_TIME_TM_FMT_TIME_A
#define DZ1_TIME_TM_FMT_FULL		DZ1_TIME_TM_FMT_FULL_A
#endif // UNIX_SYSTEM

#define DZ1_TIME_TM_ARG_DATE(tmp)	(tmp)->tm_year + 1900, (tmp)->tm_mon + 1, (tmp)->tm_mday
#define DZ1_TIME_TM_ARG_TIME(tmp)	(tmp)->tm_hour, (tmp)->tm_min, (tmp)->tm_sec
#define DZ1_TIME_TM_ARG_FULL(tmp)	DZ1_TIME_TM_ARG_DATE(tmp), DZ1_TIME_TM_ARG_TIME(tmp)

DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TmDateFromStrA(struct tm *dst, str_t strYYYYMMDD, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TmTimeFromStrA(struct tm *dst, str_t strHHMMSS, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TmFromStrA_DT(struct tm *dst, str_t strYYYYMMDD, str_t strHHMMSS, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TmFromStrA(struct tm *dst, str_t strYYYYMMDDHHMMSS, Dz1Error *err);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TmDateFromStrW(struct tm *dst, wstr_t strYYYYMMDD, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TmTimeFromStrW(struct tm *dst, wstr_t strHHMMSS, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TmFromStrW_DT(struct tm *dst, wstr_t strYYYYMMDD, wstr_t strHHMMSS, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TmFromStrW(struct tm *dst, wstr_t strYYYYMMDDHHMMSS, Dz1Error *err);
#ifdef UNICODE
#define Dz1TmDateFromStr					Dz1TmDateFromStrW
#define Dz1TmTimeFromStr					Dz1TmTimeFromStrW
#define Dz1TmFromStr_DT						Dz1TmFromStrW_DT
#define Dz1TmFromStr						Dz1TmFromStrW
#else	// UNICODE
#define Dz1TmDateFromStr					Dz1TmDateFromStrA
#define Dz1TmTimeFromStr					Dz1TmTimeFromStrA
#define Dz1TmFromStr_DT						Dz1TmFromStrA_DT
#define Dz1TmFromStr						Dz1TmFromStrA
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define Dz1TmDateFromStr					Dz1TmDateFromStrA
#define Dz1TmTimeFromStr					Dz1TmTimeFromStrA
#define Dz1TmFromStr_DT						Dz1TmFromStrA_DT
#define Dz1TmFromStr						Dz1TmFromStrA
#endif	// UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Time_getNanoTime(s64_t *dst, Dz1Error *err);

#endif	


