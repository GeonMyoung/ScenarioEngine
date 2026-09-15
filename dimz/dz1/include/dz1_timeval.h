#ifndef DZ1_TIMEVAL_H
#define DZ1_TIMEVAL_H

#include <dz1.h>
#ifndef UNIX_SYSTEM
#include <winsock2.h>
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif
#include <dz1_time.h>

///////////////////////////////////////////////////////////////////////////////
// TimeVal 32bit
typedef struct timeval Dz1TimeVal;

static __inline__ Dz1TimeVal Dz1TimeVal_get(void)
{
	Dz1TimeVal ret;
#ifdef UNIX_SYSTEM
	gettimeofday(&ret, NULL);
#else
	struct timeb T;
	ftime(&T);
	ret.tv_sec = (long)T.time;
	ret.tv_usec = (long)T.millitm * 1000;
#endif
	return ret;
}

static __inline__ void Dz1TimeVal_errorFix(Dz1TimeVal *t)
{
	if (t->tv_usec >= 1000000)
	{
		t->tv_sec += t->tv_usec / 1000000;
		t->tv_usec %= 1000000;
	}
}

static __inline__ Dz1TimeVal Dz1TimeVal_add(Dz1TimeVal a, Dz1TimeVal b)
{
	a.tv_sec += b.tv_sec;
	a.tv_usec += b.tv_usec;
	Dz1TimeVal_errorFix(&a);
	return a;
}

static __inline__ Dz1TimeVal Dz1TimeVal_addMicroSec(Dz1TimeVal a, u64_t add_us)
{
	Dz1TimeVal b;
	b.tv_sec = (u32_t)(add_us / 1000000);
	b.tv_usec = (u32_t)(add_us % 1000000);
	b = Dz1TimeVal_add(a, b);
	return b;
}

static __inline__ Dz1TimeVal Dz1TimeVal_addMilliSec(Dz1TimeVal a, u32_t add_ms)
{
	Dz1TimeVal b;
	b.tv_sec = add_ms / 1000;
	b.tv_usec =  (add_ms % 1000) * 1000;
	b = Dz1TimeVal_add(a, b);
	return b;
}

static __inline__ Dz1TimeVal Dz1TimeVal_addSec(Dz1TimeVal a, u32_t add_s)
{
	a.tv_sec += add_s;
	return a;
}

// Sub Function does not return minus time
static __inline__ Dz1TimeVal Dz1TimeVal_sub(Dz1TimeVal a, Dz1TimeVal b)
{
	if (a.tv_sec < b.tv_sec) { a.tv_sec = 0; a.tv_usec = 0; }
	else if (a.tv_sec == b.tv_sec)
	{
		a.tv_sec = 0;
		if (a.tv_usec < b.tv_usec) a.tv_usec = 0;
		else a.tv_usec -= b.tv_usec;
	}
	else
	{
		a.tv_sec -= b.tv_sec;
		if (a.tv_usec < b.tv_usec) { a.tv_usec += (1000000 - b.tv_usec); a.tv_sec--; }
		else a.tv_usec -= b.tv_usec;
	}
	return a;
}

static __inline__ Dz1TimeVal Dz1TimeVal_subMicroSec(Dz1TimeVal a, u32_t sub_us)
{
	Dz1TimeVal b;
	b.tv_sec = sub_us / 1000000;
	b.tv_usec = sub_us % 1000000;
	return Dz1TimeVal_sub(a, b);
}

static __inline__ Dz1TimeVal Dz1TimeVal_subMilliSec(Dz1TimeVal a, u32_t sub_ms)
{
	Dz1TimeVal b;
	b.tv_sec = sub_ms / 1000;
	b.tv_usec = (sub_ms % 1000) * 1000;
	return Dz1TimeVal_sub(a, b);
}

static __inline__ Dz1TimeVal Dz1TimeVal_subSec(Dz1TimeVal a, u32_t sub_s)
{
	Dz1TimeVal b = { 0, 0 };
	b.tv_sec = sub_s;
	return Dz1TimeVal_sub(a, b);
}

static __inline__ int Dz1TimeVal_cmp(Dz1TimeVal *a, Dz1TimeVal *b)
{
	if (a->tv_sec == b->tv_sec)
		return a->tv_usec - b->tv_usec;
	return a->tv_sec - b->tv_sec;
}

static __inline__ int _Dz1TimeVal_cmp(Dz1TimeVal a, Dz1TimeVal b)
{
	return Dz1TimeVal_cmp(&a, &b);
}

static __inline__ int Dz1TimeVal_isZero(Dz1TimeVal t) { return t.tv_sec == 0 && t.tv_usec == 0 ? TRUE : FALSE; }

static __inline__ u32_t Dz1TimeVal2MicroSec(Dz1TimeVal t)
{
	u32_t ret = t.tv_sec * 1000000 + t.tv_usec;
	return ret;
}

static __inline__ u64_t Dz1TimeVal2US(Dz1TimeVal t)
{
	u64_t ret = (u64_t)t.tv_sec * 1000000 + t.tv_usec;
	return ret;
}

static __inline__ Dz1TimeVal Dz1TimeValFromUS(u64_t t)
{
	Dz1TimeVal ret; // = { (long)(t / 1000000), (long)(t % 1000000) };
	ret.tv_sec = (long)(t / 1000000);
	ret.tv_usec = (long)(t % 1000000);
	return ret;
}

static __inline__ struct timespec Dz1TimeVal2Timespec(Dz1TimeVal a)
{
	struct timespec ret;
	ret.tv_sec = a.tv_sec;
	ret.tv_nsec = a.tv_usec * 1000;
	return ret;
}

DZ1_CPPLINK DZ1_DLLPORT Dz1TimeVal	*Dz1TimeVal_new(u16_t year, u8_t month, u8_t day, u8_t h, u8_t m, u8_t s, u32_t usec, Dz1Error *err); // should use UCT-Calender value
DZ1_CPPLINK DZ1_DLLPORT Dz1TimeVal	*Dz1TimeVal_newFromTime(time_t *src, Dz1Error *err);	// src == NULL then create current time
DZ1_CPPLINK DZ1_DLLPORT Dz1TimeVal	*Dz1TimeVal_clone(Dz1TimeVal *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1TimeValA_dump(Dz1TimeVal *t, int tab);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1TimeValA_fdump(FILE *fp, Dz1TimeVal *t, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1TimeValW_dump(Dz1TimeVal *t, int tab);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1TimeValW_fdump(FILE *fp, Dz1TimeVal *t, int tab);
#ifdef UNICODE
#define								 Dz1TimeVal_dump			Dz1TimeValW_dump
#define								 Dz1TimeVal_fdump			Dz1TimeValW_fdump
#else // UNICODE
#define								 Dz1TimeVal_dump			Dz1TimeValA_dump
#define								 Dz1TimeVal_fdump			Dz1TimeValA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1TimeVal_dump			Dz1TimeValA_dump
#define								 Dz1TimeVal_fdump			Dz1TimeValA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1TimeVal_del(Dz1TimeVal *t);
static __inline__ void				 Dz1TimeVal_delAndSetNull(void *ptr)
{
	Dz1TimeVal **p = (Dz1TimeVal **)ptr;
	Dz1TimeVal_del(*p); *p = NULL;
}
// TimeVal 32bit
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TimeVal 64bit
typedef struct Dz1TimeVal64
{
	s64_t			 tv_sec;
	u32_t			 tv_usec;
} Dz1TimeVal64;

static __inline__ Dz1TimeVal64 Dz1TimeVal64_get(void)
{
	Dz1TimeVal64 ret;
#ifdef UNIX_SYSTEM
	struct timeval tv;
	gettimeofday(&tv, NULL);
	ret.tv_sec = (u64_t)tv.tv_sec;
	ret.tv_usec = tv.tv_usec;
#else
#if defined(__BORLANDC__)
	Dz1TimeVal T = Dz1TimeVal_get();
	ret.tv_sec 	= T.tv_sec  ;
	ret.tv_usec = T.tv_usec;
#else
	struct __timeb64 T;
	_ftime64(&T);
	ret.tv_sec = T.time;
	ret.tv_usec = (u32_t)T.millitm * 1000;
#endif
#endif
	return ret;
}

static __inline__ void Dz1TimeVal64_errorFix(Dz1TimeVal64 *t)
{
	if (t->tv_usec >= 1000000)
	{
		t->tv_sec += t->tv_usec / 1000000;
		t->tv_usec %= 1000000;
	}
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64_add(Dz1TimeVal64 a, Dz1TimeVal64 b)
{
	a.tv_sec += b.tv_sec;
	a.tv_usec += b.tv_usec;
	Dz1TimeVal64_errorFix(&a);
	return a;
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64_addMicroSec(Dz1TimeVal64 a, u64_t add_us)
{
	Dz1TimeVal64 b;
	b.tv_sec = (s64_t)(add_us / 1000000);
	b.tv_usec = (u32_t)(add_us % 1000000);
	b = Dz1TimeVal64_add(a, b);
	return b;
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64_addMilliSec(Dz1TimeVal64 a, u32_t add_ms)
{
	Dz1TimeVal64 b;
	b.tv_sec = (s64_t)(add_ms / 1000);
	b.tv_usec =  (add_ms % 1000) * 1000;
	b = Dz1TimeVal64_add(a, b);
	return b;
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64_addSec(Dz1TimeVal64 a, u32_t add_s)
{
	a.tv_sec += add_s;
	return a;
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64_sub(Dz1TimeVal64 a, Dz1TimeVal64 b)
{
	if (a.tv_sec < b.tv_sec) { a.tv_sec = 0; a.tv_usec = 0; }
	else if (a.tv_sec == b.tv_sec)
	{	// same second
		a.tv_sec = 0;									// zero for second part
		if (a.tv_usec < b.tv_usec) a.tv_usec = 0;
		else a.tv_usec -= b.tv_usec;
	}
	else
	{
		a.tv_sec -= b.tv_sec;
		if (a.tv_usec < b.tv_usec) { a.tv_usec = a.tv_usec + (1000000 - b.tv_usec); a.tv_sec--; }
		else a.tv_usec -= b.tv_usec;
	}
	return a;
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64_subMicroSec(Dz1TimeVal64 a, u32_t sub_us)
{
	Dz1TimeVal64 b;
	b.tv_sec = sub_us / 1000000;
	b.tv_usec = sub_us % 1000000;
	return Dz1TimeVal64_sub(a, b);
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64_subMilliSec(Dz1TimeVal64 a, u32_t sub_ms)
{
	Dz1TimeVal64 b;
	b.tv_sec = sub_ms / 1000;
	b.tv_usec = (sub_ms % 1000) * 1000;
	return Dz1TimeVal64_sub(a, b);
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64_subSec(Dz1TimeVal64 a, u32_t sub_s)
{
	Dz1TimeVal64 b = { 0, 0 };
	b.tv_sec = sub_s;
	return Dz1TimeVal64_sub(a, b);
}

static __inline__ int Dz1TimeVal64_cmp(Dz1TimeVal64 *a, Dz1TimeVal64 *b)
{
	if (a->tv_sec == b->tv_sec)
		return (int)(a->tv_usec - b->tv_usec);
	return (int)(a->tv_sec - b->tv_sec);
}

static __inline__ int _Dz1TimeVal64_cmp(Dz1TimeVal64 a, Dz1TimeVal64 b)
{
	return Dz1TimeVal64_cmp(&a, &b);
}

static __inline__ int Dz1TimeVal64_isZero(Dz1TimeVal64 t) { return t.tv_sec == 0 && t.tv_usec == 0 ? TRUE : FALSE; }

static __inline__ u64_t Dz1TimeVal64ToMicroSec(Dz1TimeVal64 t)
{
	u64_t ret = (u64_t)t.tv_sec * 1000000 + t.tv_usec;
	return ret;
}

static __inline__ u64_t Dz1TimeVal64ToUS(Dz1TimeVal64 t)
{
	u64_t ret = (u64_t)t.tv_sec * 1000000 + t.tv_usec;
	return ret;
}

static __inline__ Dz1TimeVal64 Dz1TimeVal64FromUS(u64_t t)
{
	Dz1TimeVal64 ret; // = { (long)(t / 1000000), (long)(t % 1000000) };
	ret.tv_sec = (s64_t)(t / 1000000);
	ret.tv_usec = t % 1000000;
	return ret;
}

static __inline__ struct timespec Dz1TimeVal64ToTimespec(Dz1TimeVal64 a)
{
	struct timespec ret;
	ret.tv_sec = (time_t)a.tv_sec;
	ret.tv_nsec = (long)a.tv_usec * 1000;
	return ret;
}
// TimeVal 64bit
///////////////////////////////////////////////////////////////////////////////

#endif
