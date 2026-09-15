#ifndef _DZ1_TDC_GITSN_ASN_UTIL_DEF_H_
#define _DZ1_TDC_GITSN_ASN_UTIL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnAsnUtil
typedef struct GitsnAsnUtil
{
	s32_t		dummy;
} GitsnAsnUtil;

DZ1_CPPLINK DZ1_DLLPORT GitsnAsnUtil *GitsnAsnUtil_new(s32_t dummy, Dz1Error *err);
static __inline__ GitsnAsnUtil *GitsnAsnUtil_gen(Dz1Error *err) { return GitsnAsnUtil_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnAsnUtil_purge(GitsnAsnUtil *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnAsnUtil_del(GitsnAsnUtil *p);
static __inline__ void GitsnAsnUtil_delAndSetNull(void *ptr)
{
	GitsnAsnUtil **p = (GitsnAsnUtil **)ptr;
	if (p) { GitsnAsnUtil_del(*p); *p = NULL; }
}
// GitsnAsnUtil
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MsgCount
typedef s64_t Gitsn_MsgCount;

#define Gitsn_MsgCount_new               Dz1s64_new
#define Gitsn_MsgCount_clone             Dz1s64_clone
#define Gitsn_MsgCount_del               Dz1s64_del
#define Gitsn_MsgCount_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_MsgCountA_dump             Dz1s64A_dump
#define Gitsn_MsgCountA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_MsgCountW_dump             Dz1s64W_dump
#define Gitsn_MsgCountW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_MsgCount_dump              Dz1s64W_dump
#define Gitsn_MsgCount_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_MsgCount_dump              Dz1s64A_dump
#define Gitsn_MsgCount_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_MsgCountX_dump(Gitsn_MsgCount *p, int tab) { DZ1_DUMP(Gitsn_MsgCount, p, tab); }
static __inline__ void Gitsn_MsgCountX_fdump(FILE *fp, Gitsn_MsgCount *p, int tab) { DZ1_FDUMP(fp, Gitsn_MsgCount, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_MsgCount_dump              Dz1s64A_dump
#define Gitsn_MsgCountX_dump Gitsn_MsgCountA_dump
#define Gitsn_MsgCount_fdump             Dz1s64A_fdump
#define Gitsn_MsgCountX_fdump Gitsn_MsgCountA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_MsgCount_cmp               Dz1s64_cmp

// Gitsn_MsgCount
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DYear
typedef s64_t Gitsn_DYear;

#define Gitsn_DYear_new               Dz1s64_new
#define Gitsn_DYear_clone             Dz1s64_clone
#define Gitsn_DYear_del               Dz1s64_del
#define Gitsn_DYear_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DYearA_dump             Dz1s64A_dump
#define Gitsn_DYearA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DYearW_dump             Dz1s64W_dump
#define Gitsn_DYearW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DYear_dump              Dz1s64W_dump
#define Gitsn_DYear_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DYear_dump              Dz1s64A_dump
#define Gitsn_DYear_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DYearX_dump(Gitsn_DYear *p, int tab) { DZ1_DUMP(Gitsn_DYear, p, tab); }
static __inline__ void Gitsn_DYearX_fdump(FILE *fp, Gitsn_DYear *p, int tab) { DZ1_FDUMP(fp, Gitsn_DYear, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DYear_dump              Dz1s64A_dump
#define Gitsn_DYearX_dump Gitsn_DYearA_dump
#define Gitsn_DYear_fdump             Dz1s64A_fdump
#define Gitsn_DYearX_fdump Gitsn_DYearA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DYear_cmp               Dz1s64_cmp

// Gitsn_DYear
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DMonth
typedef s64_t Gitsn_DMonth;

#define Gitsn_DMonth_new               Dz1s64_new
#define Gitsn_DMonth_clone             Dz1s64_clone
#define Gitsn_DMonth_del               Dz1s64_del
#define Gitsn_DMonth_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DMonthA_dump             Dz1s64A_dump
#define Gitsn_DMonthA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DMonthW_dump             Dz1s64W_dump
#define Gitsn_DMonthW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DMonth_dump              Dz1s64W_dump
#define Gitsn_DMonth_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DMonth_dump              Dz1s64A_dump
#define Gitsn_DMonth_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DMonthX_dump(Gitsn_DMonth *p, int tab) { DZ1_DUMP(Gitsn_DMonth, p, tab); }
static __inline__ void Gitsn_DMonthX_fdump(FILE *fp, Gitsn_DMonth *p, int tab) { DZ1_FDUMP(fp, Gitsn_DMonth, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DMonth_dump              Dz1s64A_dump
#define Gitsn_DMonthX_dump Gitsn_DMonthA_dump
#define Gitsn_DMonth_fdump             Dz1s64A_fdump
#define Gitsn_DMonthX_fdump Gitsn_DMonthA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DMonth_cmp               Dz1s64_cmp

// Gitsn_DMonth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DDay
typedef s64_t Gitsn_DDay;

#define Gitsn_DDay_new               Dz1s64_new
#define Gitsn_DDay_clone             Dz1s64_clone
#define Gitsn_DDay_del               Dz1s64_del
#define Gitsn_DDay_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DDayA_dump             Dz1s64A_dump
#define Gitsn_DDayA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DDayW_dump             Dz1s64W_dump
#define Gitsn_DDayW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DDay_dump              Dz1s64W_dump
#define Gitsn_DDay_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DDay_dump              Dz1s64A_dump
#define Gitsn_DDay_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DDayX_dump(Gitsn_DDay *p, int tab) { DZ1_DUMP(Gitsn_DDay, p, tab); }
static __inline__ void Gitsn_DDayX_fdump(FILE *fp, Gitsn_DDay *p, int tab) { DZ1_FDUMP(fp, Gitsn_DDay, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DDay_dump              Dz1s64A_dump
#define Gitsn_DDayX_dump Gitsn_DDayA_dump
#define Gitsn_DDay_fdump             Dz1s64A_fdump
#define Gitsn_DDayX_fdump Gitsn_DDayA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DDay_cmp               Dz1s64_cmp

// Gitsn_DDay
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DHour
typedef s64_t Gitsn_DHour;

#define Gitsn_DHour_new               Dz1s64_new
#define Gitsn_DHour_clone             Dz1s64_clone
#define Gitsn_DHour_del               Dz1s64_del
#define Gitsn_DHour_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DHourA_dump             Dz1s64A_dump
#define Gitsn_DHourA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DHourW_dump             Dz1s64W_dump
#define Gitsn_DHourW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DHour_dump              Dz1s64W_dump
#define Gitsn_DHour_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DHour_dump              Dz1s64A_dump
#define Gitsn_DHour_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DHourX_dump(Gitsn_DHour *p, int tab) { DZ1_DUMP(Gitsn_DHour, p, tab); }
static __inline__ void Gitsn_DHourX_fdump(FILE *fp, Gitsn_DHour *p, int tab) { DZ1_FDUMP(fp, Gitsn_DHour, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DHour_dump              Dz1s64A_dump
#define Gitsn_DHourX_dump Gitsn_DHourA_dump
#define Gitsn_DHour_fdump             Dz1s64A_fdump
#define Gitsn_DHourX_fdump Gitsn_DHourA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DHour_cmp               Dz1s64_cmp

// Gitsn_DHour
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DMinute
typedef s64_t Gitsn_DMinute;

#define Gitsn_DMinute_new               Dz1s64_new
#define Gitsn_DMinute_clone             Dz1s64_clone
#define Gitsn_DMinute_del               Dz1s64_del
#define Gitsn_DMinute_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DMinuteA_dump             Dz1s64A_dump
#define Gitsn_DMinuteA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DMinuteW_dump             Dz1s64W_dump
#define Gitsn_DMinuteW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DMinute_dump              Dz1s64W_dump
#define Gitsn_DMinute_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DMinute_dump              Dz1s64A_dump
#define Gitsn_DMinute_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DMinuteX_dump(Gitsn_DMinute *p, int tab) { DZ1_DUMP(Gitsn_DMinute, p, tab); }
static __inline__ void Gitsn_DMinuteX_fdump(FILE *fp, Gitsn_DMinute *p, int tab) { DZ1_FDUMP(fp, Gitsn_DMinute, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DMinute_dump              Dz1s64A_dump
#define Gitsn_DMinuteX_dump Gitsn_DMinuteA_dump
#define Gitsn_DMinute_fdump             Dz1s64A_fdump
#define Gitsn_DMinuteX_fdump Gitsn_DMinuteA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DMinute_cmp               Dz1s64_cmp

// Gitsn_DMinute
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DSecond
typedef s64_t Gitsn_DSecond;

#define Gitsn_DSecond_new               Dz1s64_new
#define Gitsn_DSecond_clone             Dz1s64_clone
#define Gitsn_DSecond_del               Dz1s64_del
#define Gitsn_DSecond_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DSecondA_dump             Dz1s64A_dump
#define Gitsn_DSecondA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DSecondW_dump             Dz1s64W_dump
#define Gitsn_DSecondW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DSecond_dump              Dz1s64W_dump
#define Gitsn_DSecond_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DSecond_dump              Dz1s64A_dump
#define Gitsn_DSecond_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DSecondX_dump(Gitsn_DSecond *p, int tab) { DZ1_DUMP(Gitsn_DSecond, p, tab); }
static __inline__ void Gitsn_DSecondX_fdump(FILE *fp, Gitsn_DSecond *p, int tab) { DZ1_FDUMP(fp, Gitsn_DSecond, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DSecond_dump              Dz1s64A_dump
#define Gitsn_DSecondX_dump Gitsn_DSecondA_dump
#define Gitsn_DSecond_fdump             Dz1s64A_fdump
#define Gitsn_DSecondX_fdump Gitsn_DSecondA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DSecond_cmp               Dz1s64_cmp

// Gitsn_DSecond
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DOffset
typedef s64_t Gitsn_DOffset;

#define Gitsn_DOffset_new               Dz1s64_new
#define Gitsn_DOffset_clone             Dz1s64_clone
#define Gitsn_DOffset_del               Dz1s64_del
#define Gitsn_DOffset_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DOffsetA_dump             Dz1s64A_dump
#define Gitsn_DOffsetA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DOffsetW_dump             Dz1s64W_dump
#define Gitsn_DOffsetW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DOffset_dump              Dz1s64W_dump
#define Gitsn_DOffset_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DOffset_dump              Dz1s64A_dump
#define Gitsn_DOffset_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DOffsetX_dump(Gitsn_DOffset *p, int tab) { DZ1_DUMP(Gitsn_DOffset, p, tab); }
static __inline__ void Gitsn_DOffsetX_fdump(FILE *fp, Gitsn_DOffset *p, int tab) { DZ1_FDUMP(fp, Gitsn_DOffset, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DOffset_dump              Dz1s64A_dump
#define Gitsn_DOffsetX_dump Gitsn_DOffsetA_dump
#define Gitsn_DOffset_fdump             Dz1s64A_fdump
#define Gitsn_DOffsetX_fdump Gitsn_DOffsetA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DOffset_cmp               Dz1s64_cmp

// Gitsn_DOffset
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Longitude
typedef s64_t Gitsn_Longitude;

#define Gitsn_Longitude_new               Dz1s64_new
#define Gitsn_Longitude_clone             Dz1s64_clone
#define Gitsn_Longitude_del               Dz1s64_del
#define Gitsn_Longitude_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_LongitudeA_dump             Dz1s64A_dump
#define Gitsn_LongitudeA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LongitudeW_dump             Dz1s64W_dump
#define Gitsn_LongitudeW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Longitude_dump              Dz1s64W_dump
#define Gitsn_Longitude_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Longitude_dump              Dz1s64A_dump
#define Gitsn_Longitude_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LongitudeX_dump(Gitsn_Longitude *p, int tab) { DZ1_DUMP(Gitsn_Longitude, p, tab); }
static __inline__ void Gitsn_LongitudeX_fdump(FILE *fp, Gitsn_Longitude *p, int tab) { DZ1_FDUMP(fp, Gitsn_Longitude, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Longitude_dump              Dz1s64A_dump
#define Gitsn_LongitudeX_dump Gitsn_LongitudeA_dump
#define Gitsn_Longitude_fdump             Dz1s64A_fdump
#define Gitsn_LongitudeX_fdump Gitsn_LongitudeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Longitude_cmp               Dz1s64_cmp

// Gitsn_Longitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Latitude
typedef s64_t Gitsn_Latitude;

#define Gitsn_Latitude_new               Dz1s64_new
#define Gitsn_Latitude_clone             Dz1s64_clone
#define Gitsn_Latitude_del               Dz1s64_del
#define Gitsn_Latitude_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_LatitudeA_dump             Dz1s64A_dump
#define Gitsn_LatitudeA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LatitudeW_dump             Dz1s64W_dump
#define Gitsn_LatitudeW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Latitude_dump              Dz1s64W_dump
#define Gitsn_Latitude_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Latitude_dump              Dz1s64A_dump
#define Gitsn_Latitude_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LatitudeX_dump(Gitsn_Latitude *p, int tab) { DZ1_DUMP(Gitsn_Latitude, p, tab); }
static __inline__ void Gitsn_LatitudeX_fdump(FILE *fp, Gitsn_Latitude *p, int tab) { DZ1_FDUMP(fp, Gitsn_Latitude, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Latitude_dump              Dz1s64A_dump
#define Gitsn_LatitudeX_dump Gitsn_LatitudeA_dump
#define Gitsn_Latitude_fdump             Dz1s64A_fdump
#define Gitsn_LatitudeX_fdump Gitsn_LatitudeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Latitude_cmp               Dz1s64_cmp

// Gitsn_Latitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Heading
typedef s64_t Gitsn_Heading;

#define Gitsn_Heading_new               Dz1s64_new
#define Gitsn_Heading_clone             Dz1s64_clone
#define Gitsn_Heading_del               Dz1s64_del
#define Gitsn_Heading_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_HeadingA_dump             Dz1s64A_dump
#define Gitsn_HeadingA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_HeadingW_dump             Dz1s64W_dump
#define Gitsn_HeadingW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Heading_dump              Dz1s64W_dump
#define Gitsn_Heading_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Heading_dump              Dz1s64A_dump
#define Gitsn_Heading_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_HeadingX_dump(Gitsn_Heading *p, int tab) { DZ1_DUMP(Gitsn_Heading, p, tab); }
static __inline__ void Gitsn_HeadingX_fdump(FILE *fp, Gitsn_Heading *p, int tab) { DZ1_FDUMP(fp, Gitsn_Heading, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Heading_dump              Dz1s64A_dump
#define Gitsn_HeadingX_dump Gitsn_HeadingA_dump
#define Gitsn_Heading_fdump             Dz1s64A_fdump
#define Gitsn_HeadingX_fdump Gitsn_HeadingA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Heading_cmp               Dz1s64_cmp

// Gitsn_Heading
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Velocity
typedef s64_t Gitsn_Velocity;

#define Gitsn_Velocity_new               Dz1s64_new
#define Gitsn_Velocity_clone             Dz1s64_clone
#define Gitsn_Velocity_del               Dz1s64_del
#define Gitsn_Velocity_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_VelocityA_dump             Dz1s64A_dump
#define Gitsn_VelocityA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VelocityW_dump             Dz1s64W_dump
#define Gitsn_VelocityW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Velocity_dump              Dz1s64W_dump
#define Gitsn_Velocity_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Velocity_dump              Dz1s64A_dump
#define Gitsn_Velocity_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VelocityX_dump(Gitsn_Velocity *p, int tab) { DZ1_DUMP(Gitsn_Velocity, p, tab); }
static __inline__ void Gitsn_VelocityX_fdump(FILE *fp, Gitsn_Velocity *p, int tab) { DZ1_FDUMP(fp, Gitsn_Velocity, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Velocity_dump              Dz1s64A_dump
#define Gitsn_VelocityX_dump Gitsn_VelocityA_dump
#define Gitsn_Velocity_fdump             Dz1s64A_fdump
#define Gitsn_VelocityX_fdump Gitsn_VelocityA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Velocity_cmp               Dz1s64_cmp

// Gitsn_Velocity
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SemiMajorAxisAccuracy
typedef s64_t Gitsn_SemiMajorAxisAccuracy;

#define Gitsn_SemiMajorAxisAccuracy_new               Dz1s64_new
#define Gitsn_SemiMajorAxisAccuracy_clone             Dz1s64_clone
#define Gitsn_SemiMajorAxisAccuracy_del               Dz1s64_del
#define Gitsn_SemiMajorAxisAccuracy_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SemiMajorAxisAccuracyA_dump             Dz1s64A_dump
#define Gitsn_SemiMajorAxisAccuracyA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SemiMajorAxisAccuracyW_dump             Dz1s64W_dump
#define Gitsn_SemiMajorAxisAccuracyW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SemiMajorAxisAccuracy_dump              Dz1s64W_dump
#define Gitsn_SemiMajorAxisAccuracy_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SemiMajorAxisAccuracy_dump              Dz1s64A_dump
#define Gitsn_SemiMajorAxisAccuracy_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SemiMajorAxisAccuracyX_dump(Gitsn_SemiMajorAxisAccuracy *p, int tab) { DZ1_DUMP(Gitsn_SemiMajorAxisAccuracy, p, tab); }
static __inline__ void Gitsn_SemiMajorAxisAccuracyX_fdump(FILE *fp, Gitsn_SemiMajorAxisAccuracy *p, int tab) { DZ1_FDUMP(fp, Gitsn_SemiMajorAxisAccuracy, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SemiMajorAxisAccuracy_dump              Dz1s64A_dump
#define Gitsn_SemiMajorAxisAccuracyX_dump Gitsn_SemiMajorAxisAccuracyA_dump
#define Gitsn_SemiMajorAxisAccuracy_fdump             Dz1s64A_fdump
#define Gitsn_SemiMajorAxisAccuracyX_fdump Gitsn_SemiMajorAxisAccuracyA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SemiMajorAxisAccuracy_cmp               Dz1s64_cmp

// Gitsn_SemiMajorAxisAccuracy
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SemiMinorAxisAccuracy
typedef s64_t Gitsn_SemiMinorAxisAccuracy;

#define Gitsn_SemiMinorAxisAccuracy_new               Dz1s64_new
#define Gitsn_SemiMinorAxisAccuracy_clone             Dz1s64_clone
#define Gitsn_SemiMinorAxisAccuracy_del               Dz1s64_del
#define Gitsn_SemiMinorAxisAccuracy_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SemiMinorAxisAccuracyA_dump             Dz1s64A_dump
#define Gitsn_SemiMinorAxisAccuracyA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SemiMinorAxisAccuracyW_dump             Dz1s64W_dump
#define Gitsn_SemiMinorAxisAccuracyW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SemiMinorAxisAccuracy_dump              Dz1s64W_dump
#define Gitsn_SemiMinorAxisAccuracy_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SemiMinorAxisAccuracy_dump              Dz1s64A_dump
#define Gitsn_SemiMinorAxisAccuracy_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SemiMinorAxisAccuracyX_dump(Gitsn_SemiMinorAxisAccuracy *p, int tab) { DZ1_DUMP(Gitsn_SemiMinorAxisAccuracy, p, tab); }
static __inline__ void Gitsn_SemiMinorAxisAccuracyX_fdump(FILE *fp, Gitsn_SemiMinorAxisAccuracy *p, int tab) { DZ1_FDUMP(fp, Gitsn_SemiMinorAxisAccuracy, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SemiMinorAxisAccuracy_dump              Dz1s64A_dump
#define Gitsn_SemiMinorAxisAccuracyX_dump Gitsn_SemiMinorAxisAccuracyA_dump
#define Gitsn_SemiMinorAxisAccuracy_fdump             Dz1s64A_fdump
#define Gitsn_SemiMinorAxisAccuracyX_fdump Gitsn_SemiMinorAxisAccuracyA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SemiMinorAxisAccuracy_cmp               Dz1s64_cmp

// Gitsn_SemiMinorAxisAccuracy
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SemiMajorAxisOrientation
typedef s64_t Gitsn_SemiMajorAxisOrientation;

#define Gitsn_SemiMajorAxisOrientation_new               Dz1s64_new
#define Gitsn_SemiMajorAxisOrientation_clone             Dz1s64_clone
#define Gitsn_SemiMajorAxisOrientation_del               Dz1s64_del
#define Gitsn_SemiMajorAxisOrientation_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SemiMajorAxisOrientationA_dump             Dz1s64A_dump
#define Gitsn_SemiMajorAxisOrientationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SemiMajorAxisOrientationW_dump             Dz1s64W_dump
#define Gitsn_SemiMajorAxisOrientationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SemiMajorAxisOrientation_dump              Dz1s64W_dump
#define Gitsn_SemiMajorAxisOrientation_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SemiMajorAxisOrientation_dump              Dz1s64A_dump
#define Gitsn_SemiMajorAxisOrientation_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SemiMajorAxisOrientationX_dump(Gitsn_SemiMajorAxisOrientation *p, int tab) { DZ1_DUMP(Gitsn_SemiMajorAxisOrientation, p, tab); }
static __inline__ void Gitsn_SemiMajorAxisOrientationX_fdump(FILE *fp, Gitsn_SemiMajorAxisOrientation *p, int tab) { DZ1_FDUMP(fp, Gitsn_SemiMajorAxisOrientation, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SemiMajorAxisOrientation_dump              Dz1s64A_dump
#define Gitsn_SemiMajorAxisOrientationX_dump Gitsn_SemiMajorAxisOrientationA_dump
#define Gitsn_SemiMajorAxisOrientation_fdump             Dz1s64A_fdump
#define Gitsn_SemiMajorAxisOrientationX_fdump Gitsn_SemiMajorAxisOrientationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SemiMajorAxisOrientation_cmp               Dz1s64_cmp

// Gitsn_SemiMajorAxisOrientation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Elevation
typedef s64_t Gitsn_Elevation;

#define Gitsn_Elevation_new               Dz1s64_new
#define Gitsn_Elevation_clone             Dz1s64_clone
#define Gitsn_Elevation_del               Dz1s64_del
#define Gitsn_Elevation_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ElevationA_dump             Dz1s64A_dump
#define Gitsn_ElevationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ElevationW_dump             Dz1s64W_dump
#define Gitsn_ElevationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Elevation_dump              Dz1s64W_dump
#define Gitsn_Elevation_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Elevation_dump              Dz1s64A_dump
#define Gitsn_Elevation_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ElevationX_dump(Gitsn_Elevation *p, int tab) { DZ1_DUMP(Gitsn_Elevation, p, tab); }
static __inline__ void Gitsn_ElevationX_fdump(FILE *fp, Gitsn_Elevation *p, int tab) { DZ1_FDUMP(fp, Gitsn_Elevation, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Elevation_dump              Dz1s64A_dump
#define Gitsn_ElevationX_dump Gitsn_ElevationA_dump
#define Gitsn_Elevation_fdump             Dz1s64A_fdump
#define Gitsn_ElevationX_fdump Gitsn_ElevationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Elevation_cmp               Dz1s64_cmp

// Gitsn_Elevation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObjectDistance
typedef s64_t Gitsn_ObjectDistance;

#define Gitsn_ObjectDistance_new               Dz1s64_new
#define Gitsn_ObjectDistance_clone             Dz1s64_clone
#define Gitsn_ObjectDistance_del               Dz1s64_del
#define Gitsn_ObjectDistance_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ObjectDistanceA_dump             Dz1s64A_dump
#define Gitsn_ObjectDistanceA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ObjectDistanceW_dump             Dz1s64W_dump
#define Gitsn_ObjectDistanceW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ObjectDistance_dump              Dz1s64W_dump
#define Gitsn_ObjectDistance_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ObjectDistance_dump              Dz1s64A_dump
#define Gitsn_ObjectDistance_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ObjectDistanceX_dump(Gitsn_ObjectDistance *p, int tab) { DZ1_DUMP(Gitsn_ObjectDistance, p, tab); }
static __inline__ void Gitsn_ObjectDistanceX_fdump(FILE *fp, Gitsn_ObjectDistance *p, int tab) { DZ1_FDUMP(fp, Gitsn_ObjectDistance, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ObjectDistance_dump              Dz1s64A_dump
#define Gitsn_ObjectDistanceX_dump Gitsn_ObjectDistanceA_dump
#define Gitsn_ObjectDistance_fdump             Dz1s64A_fdump
#define Gitsn_ObjectDistanceX_fdump Gitsn_ObjectDistanceA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ObjectDistance_cmp               Dz1s64_cmp

// Gitsn_ObjectDistance
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GNSSstatus
typedef u8_t Gitsn_GNSSstatus;

#define Gitsn_GNSSstatus_new               Dz1u8_new
#define Gitsn_GNSSstatus_clone             Dz1u8_clone
#define Gitsn_GNSSstatus_del               Dz1u8_del
#define Gitsn_GNSSstatus_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_GNSSstatusA_dump             Dz1u8A_dump
#define Gitsn_GNSSstatusA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_GNSSstatusW_dump             Dz1u8W_dump
#define Gitsn_GNSSstatusW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_GNSSstatus_dump              Dz1u8W_dump
#define Gitsn_GNSSstatus_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_GNSSstatus_dump              Dz1u8A_dump
#define Gitsn_GNSSstatus_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_GNSSstatusX_dump(Gitsn_GNSSstatus *p, int tab) { DZ1_DUMP(Gitsn_GNSSstatus, p, tab); }
static __inline__ void Gitsn_GNSSstatusX_fdump(FILE *fp, Gitsn_GNSSstatus *p, int tab) { DZ1_FDUMP(fp, Gitsn_GNSSstatus, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_GNSSstatus_dump              Dz1u8A_dump
#define Gitsn_GNSSstatusX_dump Gitsn_GNSSstatusA_dump
#define Gitsn_GNSSstatus_fdump             Dz1u8A_fdump
#define Gitsn_GNSSstatusX_fdump Gitsn_GNSSstatusA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_GNSSstatus_cmp               Dz1u8_cmp

// Gitsn_GNSSstatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Acceleration
typedef s64_t Gitsn_Acceleration;

#define Gitsn_Acceleration_new               Dz1s64_new
#define Gitsn_Acceleration_clone             Dz1s64_clone
#define Gitsn_Acceleration_del               Dz1s64_del
#define Gitsn_Acceleration_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_AccelerationA_dump             Dz1s64A_dump
#define Gitsn_AccelerationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_AccelerationW_dump             Dz1s64W_dump
#define Gitsn_AccelerationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Acceleration_dump              Dz1s64W_dump
#define Gitsn_Acceleration_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Acceleration_dump              Dz1s64A_dump
#define Gitsn_Acceleration_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_AccelerationX_dump(Gitsn_Acceleration *p, int tab) { DZ1_DUMP(Gitsn_Acceleration, p, tab); }
static __inline__ void Gitsn_AccelerationX_fdump(FILE *fp, Gitsn_Acceleration *p, int tab) { DZ1_FDUMP(fp, Gitsn_Acceleration, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Acceleration_dump              Dz1s64A_dump
#define Gitsn_AccelerationX_dump Gitsn_AccelerationA_dump
#define Gitsn_Acceleration_fdump             Dz1s64A_fdump
#define Gitsn_AccelerationX_fdump Gitsn_AccelerationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Acceleration_cmp               Dz1s64_cmp

// Gitsn_Acceleration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VerticalAcceleration
typedef s64_t Gitsn_VerticalAcceleration;

#define Gitsn_VerticalAcceleration_new               Dz1s64_new
#define Gitsn_VerticalAcceleration_clone             Dz1s64_clone
#define Gitsn_VerticalAcceleration_del               Dz1s64_del
#define Gitsn_VerticalAcceleration_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_VerticalAccelerationA_dump             Dz1s64A_dump
#define Gitsn_VerticalAccelerationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VerticalAccelerationW_dump             Dz1s64W_dump
#define Gitsn_VerticalAccelerationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_VerticalAcceleration_dump              Dz1s64W_dump
#define Gitsn_VerticalAcceleration_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_VerticalAcceleration_dump              Dz1s64A_dump
#define Gitsn_VerticalAcceleration_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VerticalAccelerationX_dump(Gitsn_VerticalAcceleration *p, int tab) { DZ1_DUMP(Gitsn_VerticalAcceleration, p, tab); }
static __inline__ void Gitsn_VerticalAccelerationX_fdump(FILE *fp, Gitsn_VerticalAcceleration *p, int tab) { DZ1_FDUMP(fp, Gitsn_VerticalAcceleration, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VerticalAcceleration_dump              Dz1s64A_dump
#define Gitsn_VerticalAccelerationX_dump Gitsn_VerticalAccelerationA_dump
#define Gitsn_VerticalAcceleration_fdump             Dz1s64A_fdump
#define Gitsn_VerticalAccelerationX_fdump Gitsn_VerticalAccelerationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VerticalAcceleration_cmp               Dz1s64_cmp

// Gitsn_VerticalAcceleration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_YawRate
typedef s64_t Gitsn_YawRate;

#define Gitsn_YawRate_new               Dz1s64_new
#define Gitsn_YawRate_clone             Dz1s64_clone
#define Gitsn_YawRate_del               Dz1s64_del
#define Gitsn_YawRate_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_YawRateA_dump             Dz1s64A_dump
#define Gitsn_YawRateA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_YawRateW_dump             Dz1s64W_dump
#define Gitsn_YawRateW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_YawRate_dump              Dz1s64W_dump
#define Gitsn_YawRate_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_YawRate_dump              Dz1s64A_dump
#define Gitsn_YawRate_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_YawRateX_dump(Gitsn_YawRate *p, int tab) { DZ1_DUMP(Gitsn_YawRate, p, tab); }
static __inline__ void Gitsn_YawRateX_fdump(FILE *fp, Gitsn_YawRate *p, int tab) { DZ1_FDUMP(fp, Gitsn_YawRate, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_YawRate_dump              Dz1s64A_dump
#define Gitsn_YawRateX_dump Gitsn_YawRateA_dump
#define Gitsn_YawRate_fdump             Dz1s64A_fdump
#define Gitsn_YawRateX_fdump Gitsn_YawRateA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_YawRate_cmp               Dz1s64_cmp

// Gitsn_YawRate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleWidth
typedef s64_t Gitsn_VehicleWidth;

#define Gitsn_VehicleWidth_new               Dz1s64_new
#define Gitsn_VehicleWidth_clone             Dz1s64_clone
#define Gitsn_VehicleWidth_del               Dz1s64_del
#define Gitsn_VehicleWidth_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_VehicleWidthA_dump             Dz1s64A_dump
#define Gitsn_VehicleWidthA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VehicleWidthW_dump             Dz1s64W_dump
#define Gitsn_VehicleWidthW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_VehicleWidth_dump              Dz1s64W_dump
#define Gitsn_VehicleWidth_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_VehicleWidth_dump              Dz1s64A_dump
#define Gitsn_VehicleWidth_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VehicleWidthX_dump(Gitsn_VehicleWidth *p, int tab) { DZ1_DUMP(Gitsn_VehicleWidth, p, tab); }
static __inline__ void Gitsn_VehicleWidthX_fdump(FILE *fp, Gitsn_VehicleWidth *p, int tab) { DZ1_FDUMP(fp, Gitsn_VehicleWidth, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VehicleWidth_dump              Dz1s64A_dump
#define Gitsn_VehicleWidthX_dump Gitsn_VehicleWidthA_dump
#define Gitsn_VehicleWidth_fdump             Dz1s64A_fdump
#define Gitsn_VehicleWidthX_fdump Gitsn_VehicleWidthA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VehicleWidth_cmp               Dz1s64_cmp

// Gitsn_VehicleWidth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleLength
typedef s64_t Gitsn_VehicleLength;

#define Gitsn_VehicleLength_new               Dz1s64_new
#define Gitsn_VehicleLength_clone             Dz1s64_clone
#define Gitsn_VehicleLength_del               Dz1s64_del
#define Gitsn_VehicleLength_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_VehicleLengthA_dump             Dz1s64A_dump
#define Gitsn_VehicleLengthA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VehicleLengthW_dump             Dz1s64W_dump
#define Gitsn_VehicleLengthW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_VehicleLength_dump              Dz1s64W_dump
#define Gitsn_VehicleLength_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_VehicleLength_dump              Dz1s64A_dump
#define Gitsn_VehicleLength_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VehicleLengthX_dump(Gitsn_VehicleLength *p, int tab) { DZ1_DUMP(Gitsn_VehicleLength, p, tab); }
static __inline__ void Gitsn_VehicleLengthX_fdump(FILE *fp, Gitsn_VehicleLength *p, int tab) { DZ1_FDUMP(fp, Gitsn_VehicleLength, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VehicleLength_dump              Dz1s64A_dump
#define Gitsn_VehicleLengthX_dump Gitsn_VehicleLengthA_dump
#define Gitsn_VehicleLength_fdump             Dz1s64A_fdump
#define Gitsn_VehicleLengthX_fdump Gitsn_VehicleLengthA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VehicleLength_cmp               Dz1s64_cmp

// Gitsn_VehicleLength
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleHeight
typedef s64_t Gitsn_VehicleHeight;

#define Gitsn_VehicleHeight_new               Dz1s64_new
#define Gitsn_VehicleHeight_clone             Dz1s64_clone
#define Gitsn_VehicleHeight_del               Dz1s64_del
#define Gitsn_VehicleHeight_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_VehicleHeightA_dump             Dz1s64A_dump
#define Gitsn_VehicleHeightA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VehicleHeightW_dump             Dz1s64W_dump
#define Gitsn_VehicleHeightW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_VehicleHeight_dump              Dz1s64W_dump
#define Gitsn_VehicleHeight_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_VehicleHeight_dump              Dz1s64A_dump
#define Gitsn_VehicleHeight_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VehicleHeightX_dump(Gitsn_VehicleHeight *p, int tab) { DZ1_DUMP(Gitsn_VehicleHeight, p, tab); }
static __inline__ void Gitsn_VehicleHeightX_fdump(FILE *fp, Gitsn_VehicleHeight *p, int tab) { DZ1_FDUMP(fp, Gitsn_VehicleHeight, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VehicleHeight_dump              Dz1s64A_dump
#define Gitsn_VehicleHeightX_dump Gitsn_VehicleHeightA_dump
#define Gitsn_VehicleHeight_fdump             Dz1s64A_fdump
#define Gitsn_VehicleHeightX_fdump Gitsn_VehicleHeightA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VehicleHeight_cmp               Dz1s64_cmp

// Gitsn_VehicleHeight
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VertOffset_B12
typedef s64_t Gitsn_VertOffset_B12;

#define Gitsn_VertOffset_B12_new               Dz1s64_new
#define Gitsn_VertOffset_B12_clone             Dz1s64_clone
#define Gitsn_VertOffset_B12_del               Dz1s64_del
#define Gitsn_VertOffset_B12_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_VertOffset_B12A_dump             Dz1s64A_dump
#define Gitsn_VertOffset_B12A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VertOffset_B12W_dump             Dz1s64W_dump
#define Gitsn_VertOffset_B12W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_VertOffset_B12_dump              Dz1s64W_dump
#define Gitsn_VertOffset_B12_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_VertOffset_B12_dump              Dz1s64A_dump
#define Gitsn_VertOffset_B12_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VertOffset_B12X_dump(Gitsn_VertOffset_B12 *p, int tab) { DZ1_DUMP(Gitsn_VertOffset_B12, p, tab); }
static __inline__ void Gitsn_VertOffset_B12X_fdump(FILE *fp, Gitsn_VertOffset_B12 *p, int tab) { DZ1_FDUMP(fp, Gitsn_VertOffset_B12, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VertOffset_B12_dump              Dz1s64A_dump
#define Gitsn_VertOffset_B12X_dump Gitsn_VertOffset_B12A_dump
#define Gitsn_VertOffset_B12_fdump             Dz1s64A_fdump
#define Gitsn_VertOffset_B12X_fdump Gitsn_VertOffset_B12A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VertOffset_B12_cmp               Dz1s64_cmp

// Gitsn_VertOffset_B12
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Speed
typedef s64_t Gitsn_Speed;

#define Gitsn_Speed_new               Dz1s64_new
#define Gitsn_Speed_clone             Dz1s64_clone
#define Gitsn_Speed_del               Dz1s64_del
#define Gitsn_Speed_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SpeedA_dump             Dz1s64A_dump
#define Gitsn_SpeedA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SpeedW_dump             Dz1s64W_dump
#define Gitsn_SpeedW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Speed_dump              Dz1s64W_dump
#define Gitsn_Speed_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Speed_dump              Dz1s64A_dump
#define Gitsn_Speed_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SpeedX_dump(Gitsn_Speed *p, int tab) { DZ1_DUMP(Gitsn_Speed, p, tab); }
static __inline__ void Gitsn_SpeedX_fdump(FILE *fp, Gitsn_Speed *p, int tab) { DZ1_FDUMP(fp, Gitsn_Speed, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Speed_dump              Dz1s64A_dump
#define Gitsn_SpeedX_dump Gitsn_SpeedA_dump
#define Gitsn_Speed_fdump             Dz1s64A_fdump
#define Gitsn_SpeedX_fdump Gitsn_SpeedA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Speed_cmp               Dz1s64_cmp

// Gitsn_Speed
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_CoarseHeading
typedef s64_t Gitsn_CoarseHeading;

#define Gitsn_CoarseHeading_new               Dz1s64_new
#define Gitsn_CoarseHeading_clone             Dz1s64_clone
#define Gitsn_CoarseHeading_del               Dz1s64_del
#define Gitsn_CoarseHeading_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_CoarseHeadingA_dump             Dz1s64A_dump
#define Gitsn_CoarseHeadingA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_CoarseHeadingW_dump             Dz1s64W_dump
#define Gitsn_CoarseHeadingW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_CoarseHeading_dump              Dz1s64W_dump
#define Gitsn_CoarseHeading_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_CoarseHeading_dump              Dz1s64A_dump
#define Gitsn_CoarseHeading_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_CoarseHeadingX_dump(Gitsn_CoarseHeading *p, int tab) { DZ1_DUMP(Gitsn_CoarseHeading, p, tab); }
static __inline__ void Gitsn_CoarseHeadingX_fdump(FILE *fp, Gitsn_CoarseHeading *p, int tab) { DZ1_FDUMP(fp, Gitsn_CoarseHeading, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_CoarseHeading_dump              Dz1s64A_dump
#define Gitsn_CoarseHeadingX_dump Gitsn_CoarseHeadingA_dump
#define Gitsn_CoarseHeading_fdump             Dz1s64A_fdump
#define Gitsn_CoarseHeadingX_fdump Gitsn_CoarseHeadingA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_CoarseHeading_cmp               Dz1s64_cmp

// Gitsn_CoarseHeading
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MinuteOfTheYear
typedef s64_t Gitsn_MinuteOfTheYear;

#define Gitsn_MinuteOfTheYear_new               Dz1s64_new
#define Gitsn_MinuteOfTheYear_clone             Dz1s64_clone
#define Gitsn_MinuteOfTheYear_del               Dz1s64_del
#define Gitsn_MinuteOfTheYear_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_MinuteOfTheYearA_dump             Dz1s64A_dump
#define Gitsn_MinuteOfTheYearA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_MinuteOfTheYearW_dump             Dz1s64W_dump
#define Gitsn_MinuteOfTheYearW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_MinuteOfTheYear_dump              Dz1s64W_dump
#define Gitsn_MinuteOfTheYear_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_MinuteOfTheYear_dump              Dz1s64A_dump
#define Gitsn_MinuteOfTheYear_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_MinuteOfTheYearX_dump(Gitsn_MinuteOfTheYear *p, int tab) { DZ1_DUMP(Gitsn_MinuteOfTheYear, p, tab); }
static __inline__ void Gitsn_MinuteOfTheYearX_fdump(FILE *fp, Gitsn_MinuteOfTheYear *p, int tab) { DZ1_FDUMP(fp, Gitsn_MinuteOfTheYear, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_MinuteOfTheYear_dump              Dz1s64A_dump
#define Gitsn_MinuteOfTheYearX_dump Gitsn_MinuteOfTheYearA_dump
#define Gitsn_MinuteOfTheYear_fdump             Dz1s64A_fdump
#define Gitsn_MinuteOfTheYearX_fdump Gitsn_MinuteOfTheYearA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_MinuteOfTheYear_cmp               Dz1s64_cmp

// Gitsn_MinuteOfTheYear
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LayerID
typedef s64_t Gitsn_LayerID;

#define Gitsn_LayerID_new               Dz1s64_new
#define Gitsn_LayerID_clone             Dz1s64_clone
#define Gitsn_LayerID_del               Dz1s64_del
#define Gitsn_LayerID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_LayerIDA_dump             Dz1s64A_dump
#define Gitsn_LayerIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LayerIDW_dump             Dz1s64W_dump
#define Gitsn_LayerIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_LayerID_dump              Dz1s64W_dump
#define Gitsn_LayerID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_LayerID_dump              Dz1s64A_dump
#define Gitsn_LayerID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LayerIDX_dump(Gitsn_LayerID *p, int tab) { DZ1_DUMP(Gitsn_LayerID, p, tab); }
static __inline__ void Gitsn_LayerIDX_fdump(FILE *fp, Gitsn_LayerID *p, int tab) { DZ1_FDUMP(fp, Gitsn_LayerID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LayerID_dump              Dz1s64A_dump
#define Gitsn_LayerIDX_dump Gitsn_LayerIDA_dump
#define Gitsn_LayerID_fdump             Dz1s64A_fdump
#define Gitsn_LayerIDX_fdump Gitsn_LayerIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LayerID_cmp               Dz1s64_cmp

// Gitsn_LayerID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneWidth
typedef s64_t Gitsn_LaneWidth;

#define Gitsn_LaneWidth_new               Dz1s64_new
#define Gitsn_LaneWidth_clone             Dz1s64_clone
#define Gitsn_LaneWidth_del               Dz1s64_del
#define Gitsn_LaneWidth_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_LaneWidthA_dump             Dz1s64A_dump
#define Gitsn_LaneWidthA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneWidthW_dump             Dz1s64W_dump
#define Gitsn_LaneWidthW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_LaneWidth_dump              Dz1s64W_dump
#define Gitsn_LaneWidth_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_LaneWidth_dump              Dz1s64A_dump
#define Gitsn_LaneWidth_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneWidthX_dump(Gitsn_LaneWidth *p, int tab) { DZ1_DUMP(Gitsn_LaneWidth, p, tab); }
static __inline__ void Gitsn_LaneWidthX_fdump(FILE *fp, Gitsn_LaneWidth *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneWidth, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneWidth_dump              Dz1s64A_dump
#define Gitsn_LaneWidthX_dump Gitsn_LaneWidthA_dump
#define Gitsn_LaneWidth_fdump             Dz1s64A_fdump
#define Gitsn_LaneWidthX_fdump Gitsn_LaneWidthA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneWidth_cmp               Dz1s64_cmp

// Gitsn_LaneWidth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DescriptiveName
typedef Dz1Str Gitsn_DescriptiveName;

#define Gitsn_DescriptiveName_new               Dz1Str_new
#define Gitsn_DescriptiveName_clone             Dz1Str_clone
#define Gitsn_DescriptiveName_del               Dz1Str_del
#define Gitsn_DescriptiveName_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_DescriptiveNameA_dump             Dz1StrA_dump
#define Gitsn_DescriptiveNameA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DescriptiveNameW_dump             Dz1StrW_dump
#define Gitsn_DescriptiveNameW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_DescriptiveName_dump              Dz1StrW_dump
#define Gitsn_DescriptiveName_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_DescriptiveName_dump              Dz1StrA_dump
#define Gitsn_DescriptiveName_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DescriptiveNameX_dump(Gitsn_DescriptiveName *p, int tab) { DZ1_DUMP(Gitsn_DescriptiveName, p, tab); }
static __inline__ void Gitsn_DescriptiveNameX_fdump(FILE *fp, Gitsn_DescriptiveName *p, int tab) { DZ1_FDUMP(fp, Gitsn_DescriptiveName, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DescriptiveName_dump              Dz1StrA_dump
#define Gitsn_DescriptiveNameX_dump Gitsn_DescriptiveNameA_dump
#define Gitsn_DescriptiveName_fdump             Dz1StrA_fdump
#define Gitsn_DescriptiveNameX_fdump Gitsn_DescriptiveNameA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DescriptiveName_cmp               Dz1Str_cmp

// Gitsn_DescriptiveName
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadRegulatorID
typedef s64_t Gitsn_RoadRegulatorID;

#define Gitsn_RoadRegulatorID_new               Dz1s64_new
#define Gitsn_RoadRegulatorID_clone             Dz1s64_clone
#define Gitsn_RoadRegulatorID_del               Dz1s64_del
#define Gitsn_RoadRegulatorID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_RoadRegulatorIDA_dump             Dz1s64A_dump
#define Gitsn_RoadRegulatorIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RoadRegulatorIDW_dump             Dz1s64W_dump
#define Gitsn_RoadRegulatorIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_RoadRegulatorID_dump              Dz1s64W_dump
#define Gitsn_RoadRegulatorID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_RoadRegulatorID_dump              Dz1s64A_dump
#define Gitsn_RoadRegulatorID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RoadRegulatorIDX_dump(Gitsn_RoadRegulatorID *p, int tab) { DZ1_DUMP(Gitsn_RoadRegulatorID, p, tab); }
static __inline__ void Gitsn_RoadRegulatorIDX_fdump(FILE *fp, Gitsn_RoadRegulatorID *p, int tab) { DZ1_FDUMP(fp, Gitsn_RoadRegulatorID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RoadRegulatorID_dump              Dz1s64A_dump
#define Gitsn_RoadRegulatorIDX_dump Gitsn_RoadRegulatorIDA_dump
#define Gitsn_RoadRegulatorID_fdump             Dz1s64A_fdump
#define Gitsn_RoadRegulatorIDX_fdump Gitsn_RoadRegulatorIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RoadRegulatorID_cmp               Dz1s64_cmp

// Gitsn_RoadRegulatorID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSegmentID
typedef s64_t Gitsn_RoadSegmentID;

#define Gitsn_RoadSegmentID_new               Dz1s64_new
#define Gitsn_RoadSegmentID_clone             Dz1s64_clone
#define Gitsn_RoadSegmentID_del               Dz1s64_del
#define Gitsn_RoadSegmentID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_RoadSegmentIDA_dump             Dz1s64A_dump
#define Gitsn_RoadSegmentIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RoadSegmentIDW_dump             Dz1s64W_dump
#define Gitsn_RoadSegmentIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_RoadSegmentID_dump              Dz1s64W_dump
#define Gitsn_RoadSegmentID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_RoadSegmentID_dump              Dz1s64A_dump
#define Gitsn_RoadSegmentID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RoadSegmentIDX_dump(Gitsn_RoadSegmentID *p, int tab) { DZ1_DUMP(Gitsn_RoadSegmentID, p, tab); }
static __inline__ void Gitsn_RoadSegmentIDX_fdump(FILE *fp, Gitsn_RoadSegmentID *p, int tab) { DZ1_FDUMP(fp, Gitsn_RoadSegmentID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RoadSegmentID_dump              Dz1s64A_dump
#define Gitsn_RoadSegmentIDX_dump Gitsn_RoadSegmentIDA_dump
#define Gitsn_RoadSegmentID_fdump             Dz1s64A_fdump
#define Gitsn_RoadSegmentIDX_fdump Gitsn_RoadSegmentIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RoadSegmentID_cmp               Dz1s64_cmp

// Gitsn_RoadSegmentID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionID
typedef s64_t Gitsn_IntersectionID;

#define Gitsn_IntersectionID_new               Dz1s64_new
#define Gitsn_IntersectionID_clone             Dz1s64_clone
#define Gitsn_IntersectionID_del               Dz1s64_del
#define Gitsn_IntersectionID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_IntersectionIDA_dump             Dz1s64A_dump
#define Gitsn_IntersectionIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_IntersectionIDW_dump             Dz1s64W_dump
#define Gitsn_IntersectionIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_IntersectionID_dump              Dz1s64W_dump
#define Gitsn_IntersectionID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_IntersectionID_dump              Dz1s64A_dump
#define Gitsn_IntersectionID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_IntersectionIDX_dump(Gitsn_IntersectionID *p, int tab) { DZ1_DUMP(Gitsn_IntersectionID, p, tab); }
static __inline__ void Gitsn_IntersectionIDX_fdump(FILE *fp, Gitsn_IntersectionID *p, int tab) { DZ1_FDUMP(fp, Gitsn_IntersectionID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_IntersectionID_dump              Dz1s64A_dump
#define Gitsn_IntersectionIDX_dump Gitsn_IntersectionIDA_dump
#define Gitsn_IntersectionID_fdump             Dz1s64A_fdump
#define Gitsn_IntersectionIDX_fdump Gitsn_IntersectionIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_IntersectionID_cmp               Dz1s64_cmp

// Gitsn_IntersectionID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneID
typedef s64_t Gitsn_LaneID;

#define Gitsn_LaneID_new               Dz1s64_new
#define Gitsn_LaneID_clone             Dz1s64_clone
#define Gitsn_LaneID_del               Dz1s64_del
#define Gitsn_LaneID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_LaneIDA_dump             Dz1s64A_dump
#define Gitsn_LaneIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneIDW_dump             Dz1s64W_dump
#define Gitsn_LaneIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_LaneID_dump              Dz1s64W_dump
#define Gitsn_LaneID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_LaneID_dump              Dz1s64A_dump
#define Gitsn_LaneID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneIDX_dump(Gitsn_LaneID *p, int tab) { DZ1_DUMP(Gitsn_LaneID, p, tab); }
static __inline__ void Gitsn_LaneIDX_fdump(FILE *fp, Gitsn_LaneID *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneID_dump              Dz1s64A_dump
#define Gitsn_LaneIDX_dump Gitsn_LaneIDA_dump
#define Gitsn_LaneID_fdump             Dz1s64A_fdump
#define Gitsn_LaneIDX_fdump Gitsn_LaneIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneID_cmp               Dz1s64_cmp

// Gitsn_LaneID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ApproachID
typedef s64_t Gitsn_ApproachID;

#define Gitsn_ApproachID_new               Dz1s64_new
#define Gitsn_ApproachID_clone             Dz1s64_clone
#define Gitsn_ApproachID_del               Dz1s64_del
#define Gitsn_ApproachID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ApproachIDA_dump             Dz1s64A_dump
#define Gitsn_ApproachIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ApproachIDW_dump             Dz1s64W_dump
#define Gitsn_ApproachIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ApproachID_dump              Dz1s64W_dump
#define Gitsn_ApproachID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ApproachID_dump              Dz1s64A_dump
#define Gitsn_ApproachID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ApproachIDX_dump(Gitsn_ApproachID *p, int tab) { DZ1_DUMP(Gitsn_ApproachID, p, tab); }
static __inline__ void Gitsn_ApproachIDX_fdump(FILE *fp, Gitsn_ApproachID *p, int tab) { DZ1_FDUMP(fp, Gitsn_ApproachID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ApproachID_dump              Dz1s64A_dump
#define Gitsn_ApproachIDX_dump Gitsn_ApproachIDA_dump
#define Gitsn_ApproachID_fdump             Dz1s64A_fdump
#define Gitsn_ApproachIDX_fdump Gitsn_ApproachIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ApproachID_cmp               Dz1s64_cmp

// Gitsn_ApproachID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AllowedManeuvers
typedef u8_t Gitsn_AllowedManeuvers;

#define Gitsn_AllowedManeuvers_new               Dz1u8_new
#define Gitsn_AllowedManeuvers_clone             Dz1u8_clone
#define Gitsn_AllowedManeuvers_del               Dz1u8_del
#define Gitsn_AllowedManeuvers_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_AllowedManeuversA_dump             Dz1u8A_dump
#define Gitsn_AllowedManeuversA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_AllowedManeuversW_dump             Dz1u8W_dump
#define Gitsn_AllowedManeuversW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_AllowedManeuvers_dump              Dz1u8W_dump
#define Gitsn_AllowedManeuvers_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_AllowedManeuvers_dump              Dz1u8A_dump
#define Gitsn_AllowedManeuvers_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_AllowedManeuversX_dump(Gitsn_AllowedManeuvers *p, int tab) { DZ1_DUMP(Gitsn_AllowedManeuvers, p, tab); }
static __inline__ void Gitsn_AllowedManeuversX_fdump(FILE *fp, Gitsn_AllowedManeuvers *p, int tab) { DZ1_FDUMP(fp, Gitsn_AllowedManeuvers, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_AllowedManeuvers_dump              Dz1u8A_dump
#define Gitsn_AllowedManeuversX_dump Gitsn_AllowedManeuversA_dump
#define Gitsn_AllowedManeuvers_fdump             Dz1u8A_fdump
#define Gitsn_AllowedManeuversX_fdump Gitsn_AllowedManeuversA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_AllowedManeuvers_cmp               Dz1u8_cmp

// Gitsn_AllowedManeuvers
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneDirection
typedef u8_t Gitsn_LaneDirection;

#define Gitsn_LaneDirection_new               Dz1u8_new
#define Gitsn_LaneDirection_clone             Dz1u8_clone
#define Gitsn_LaneDirection_del               Dz1u8_del
#define Gitsn_LaneDirection_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneDirectionA_dump             Dz1u8A_dump
#define Gitsn_LaneDirectionA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneDirectionW_dump             Dz1u8W_dump
#define Gitsn_LaneDirectionW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneDirection_dump              Dz1u8W_dump
#define Gitsn_LaneDirection_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneDirection_dump              Dz1u8A_dump
#define Gitsn_LaneDirection_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneDirectionX_dump(Gitsn_LaneDirection *p, int tab) { DZ1_DUMP(Gitsn_LaneDirection, p, tab); }
static __inline__ void Gitsn_LaneDirectionX_fdump(FILE *fp, Gitsn_LaneDirection *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneDirection, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneDirection_dump              Dz1u8A_dump
#define Gitsn_LaneDirectionX_dump Gitsn_LaneDirectionA_dump
#define Gitsn_LaneDirection_fdump             Dz1u8A_fdump
#define Gitsn_LaneDirectionX_fdump Gitsn_LaneDirectionA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneDirection_cmp               Dz1u8_cmp

// Gitsn_LaneDirection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneSharing
typedef u8_t Gitsn_LaneSharing;

#define Gitsn_LaneSharing_new               Dz1u8_new
#define Gitsn_LaneSharing_clone             Dz1u8_clone
#define Gitsn_LaneSharing_del               Dz1u8_del
#define Gitsn_LaneSharing_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneSharingA_dump             Dz1u8A_dump
#define Gitsn_LaneSharingA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneSharingW_dump             Dz1u8W_dump
#define Gitsn_LaneSharingW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneSharing_dump              Dz1u8W_dump
#define Gitsn_LaneSharing_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneSharing_dump              Dz1u8A_dump
#define Gitsn_LaneSharing_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneSharingX_dump(Gitsn_LaneSharing *p, int tab) { DZ1_DUMP(Gitsn_LaneSharing, p, tab); }
static __inline__ void Gitsn_LaneSharingX_fdump(FILE *fp, Gitsn_LaneSharing *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneSharing, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneSharing_dump              Dz1u8A_dump
#define Gitsn_LaneSharingX_dump Gitsn_LaneSharingA_dump
#define Gitsn_LaneSharing_fdump             Dz1u8A_fdump
#define Gitsn_LaneSharingX_fdump Gitsn_LaneSharingA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneSharing_cmp               Dz1u8_cmp

// Gitsn_LaneSharing
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes_Vehicle
typedef u8_t Gitsn_LaneAttributes_Vehicle;

#define Gitsn_LaneAttributes_Vehicle_new               Dz1u8_new
#define Gitsn_LaneAttributes_Vehicle_clone             Dz1u8_clone
#define Gitsn_LaneAttributes_Vehicle_del               Dz1u8_del
#define Gitsn_LaneAttributes_Vehicle_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneAttributes_VehicleA_dump             Dz1u8A_dump
#define Gitsn_LaneAttributes_VehicleA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneAttributes_VehicleW_dump             Dz1u8W_dump
#define Gitsn_LaneAttributes_VehicleW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneAttributes_Vehicle_dump              Dz1u8W_dump
#define Gitsn_LaneAttributes_Vehicle_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneAttributes_Vehicle_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_Vehicle_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneAttributes_VehicleX_dump(Gitsn_LaneAttributes_Vehicle *p, int tab) { DZ1_DUMP(Gitsn_LaneAttributes_Vehicle, p, tab); }
static __inline__ void Gitsn_LaneAttributes_VehicleX_fdump(FILE *fp, Gitsn_LaneAttributes_Vehicle *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneAttributes_Vehicle, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Vehicle_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_VehicleX_dump Gitsn_LaneAttributes_VehicleA_dump
#define Gitsn_LaneAttributes_Vehicle_fdump             Dz1u8A_fdump
#define Gitsn_LaneAttributes_VehicleX_fdump Gitsn_LaneAttributes_VehicleA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Vehicle_cmp               Dz1u8_cmp

// Gitsn_LaneAttributes_Vehicle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes_Crosswalk
typedef u8_t Gitsn_LaneAttributes_Crosswalk;

#define Gitsn_LaneAttributes_Crosswalk_new               Dz1u8_new
#define Gitsn_LaneAttributes_Crosswalk_clone             Dz1u8_clone
#define Gitsn_LaneAttributes_Crosswalk_del               Dz1u8_del
#define Gitsn_LaneAttributes_Crosswalk_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneAttributes_CrosswalkA_dump             Dz1u8A_dump
#define Gitsn_LaneAttributes_CrosswalkA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneAttributes_CrosswalkW_dump             Dz1u8W_dump
#define Gitsn_LaneAttributes_CrosswalkW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneAttributes_Crosswalk_dump              Dz1u8W_dump
#define Gitsn_LaneAttributes_Crosswalk_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneAttributes_Crosswalk_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_Crosswalk_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneAttributes_CrosswalkX_dump(Gitsn_LaneAttributes_Crosswalk *p, int tab) { DZ1_DUMP(Gitsn_LaneAttributes_Crosswalk, p, tab); }
static __inline__ void Gitsn_LaneAttributes_CrosswalkX_fdump(FILE *fp, Gitsn_LaneAttributes_Crosswalk *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneAttributes_Crosswalk, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Crosswalk_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_CrosswalkX_dump Gitsn_LaneAttributes_CrosswalkA_dump
#define Gitsn_LaneAttributes_Crosswalk_fdump             Dz1u8A_fdump
#define Gitsn_LaneAttributes_CrosswalkX_fdump Gitsn_LaneAttributes_CrosswalkA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Crosswalk_cmp               Dz1u8_cmp

// Gitsn_LaneAttributes_Crosswalk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes_Bike
typedef u8_t Gitsn_LaneAttributes_Bike;

#define Gitsn_LaneAttributes_Bike_new               Dz1u8_new
#define Gitsn_LaneAttributes_Bike_clone             Dz1u8_clone
#define Gitsn_LaneAttributes_Bike_del               Dz1u8_del
#define Gitsn_LaneAttributes_Bike_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneAttributes_BikeA_dump             Dz1u8A_dump
#define Gitsn_LaneAttributes_BikeA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneAttributes_BikeW_dump             Dz1u8W_dump
#define Gitsn_LaneAttributes_BikeW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneAttributes_Bike_dump              Dz1u8W_dump
#define Gitsn_LaneAttributes_Bike_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneAttributes_Bike_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_Bike_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneAttributes_BikeX_dump(Gitsn_LaneAttributes_Bike *p, int tab) { DZ1_DUMP(Gitsn_LaneAttributes_Bike, p, tab); }
static __inline__ void Gitsn_LaneAttributes_BikeX_fdump(FILE *fp, Gitsn_LaneAttributes_Bike *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneAttributes_Bike, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Bike_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_BikeX_dump Gitsn_LaneAttributes_BikeA_dump
#define Gitsn_LaneAttributes_Bike_fdump             Dz1u8A_fdump
#define Gitsn_LaneAttributes_BikeX_fdump Gitsn_LaneAttributes_BikeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Bike_cmp               Dz1u8_cmp

// Gitsn_LaneAttributes_Bike
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes_Sidewalk
typedef u8_t Gitsn_LaneAttributes_Sidewalk;

#define Gitsn_LaneAttributes_Sidewalk_new               Dz1u8_new
#define Gitsn_LaneAttributes_Sidewalk_clone             Dz1u8_clone
#define Gitsn_LaneAttributes_Sidewalk_del               Dz1u8_del
#define Gitsn_LaneAttributes_Sidewalk_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneAttributes_SidewalkA_dump             Dz1u8A_dump
#define Gitsn_LaneAttributes_SidewalkA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneAttributes_SidewalkW_dump             Dz1u8W_dump
#define Gitsn_LaneAttributes_SidewalkW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneAttributes_Sidewalk_dump              Dz1u8W_dump
#define Gitsn_LaneAttributes_Sidewalk_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneAttributes_Sidewalk_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_Sidewalk_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneAttributes_SidewalkX_dump(Gitsn_LaneAttributes_Sidewalk *p, int tab) { DZ1_DUMP(Gitsn_LaneAttributes_Sidewalk, p, tab); }
static __inline__ void Gitsn_LaneAttributes_SidewalkX_fdump(FILE *fp, Gitsn_LaneAttributes_Sidewalk *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneAttributes_Sidewalk, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Sidewalk_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_SidewalkX_dump Gitsn_LaneAttributes_SidewalkA_dump
#define Gitsn_LaneAttributes_Sidewalk_fdump             Dz1u8A_fdump
#define Gitsn_LaneAttributes_SidewalkX_fdump Gitsn_LaneAttributes_SidewalkA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Sidewalk_cmp               Dz1u8_cmp

// Gitsn_LaneAttributes_Sidewalk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes_Barrier
typedef u8_t Gitsn_LaneAttributes_Barrier;

#define Gitsn_LaneAttributes_Barrier_new               Dz1u8_new
#define Gitsn_LaneAttributes_Barrier_clone             Dz1u8_clone
#define Gitsn_LaneAttributes_Barrier_del               Dz1u8_del
#define Gitsn_LaneAttributes_Barrier_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneAttributes_BarrierA_dump             Dz1u8A_dump
#define Gitsn_LaneAttributes_BarrierA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneAttributes_BarrierW_dump             Dz1u8W_dump
#define Gitsn_LaneAttributes_BarrierW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneAttributes_Barrier_dump              Dz1u8W_dump
#define Gitsn_LaneAttributes_Barrier_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneAttributes_Barrier_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_Barrier_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneAttributes_BarrierX_dump(Gitsn_LaneAttributes_Barrier *p, int tab) { DZ1_DUMP(Gitsn_LaneAttributes_Barrier, p, tab); }
static __inline__ void Gitsn_LaneAttributes_BarrierX_fdump(FILE *fp, Gitsn_LaneAttributes_Barrier *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneAttributes_Barrier, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Barrier_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_BarrierX_dump Gitsn_LaneAttributes_BarrierA_dump
#define Gitsn_LaneAttributes_Barrier_fdump             Dz1u8A_fdump
#define Gitsn_LaneAttributes_BarrierX_fdump Gitsn_LaneAttributes_BarrierA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Barrier_cmp               Dz1u8_cmp

// Gitsn_LaneAttributes_Barrier
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes_Striping
typedef u8_t Gitsn_LaneAttributes_Striping;

#define Gitsn_LaneAttributes_Striping_new               Dz1u8_new
#define Gitsn_LaneAttributes_Striping_clone             Dz1u8_clone
#define Gitsn_LaneAttributes_Striping_del               Dz1u8_del
#define Gitsn_LaneAttributes_Striping_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneAttributes_StripingA_dump             Dz1u8A_dump
#define Gitsn_LaneAttributes_StripingA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneAttributes_StripingW_dump             Dz1u8W_dump
#define Gitsn_LaneAttributes_StripingW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneAttributes_Striping_dump              Dz1u8W_dump
#define Gitsn_LaneAttributes_Striping_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneAttributes_Striping_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_Striping_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneAttributes_StripingX_dump(Gitsn_LaneAttributes_Striping *p, int tab) { DZ1_DUMP(Gitsn_LaneAttributes_Striping, p, tab); }
static __inline__ void Gitsn_LaneAttributes_StripingX_fdump(FILE *fp, Gitsn_LaneAttributes_Striping *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneAttributes_Striping, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Striping_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_StripingX_dump Gitsn_LaneAttributes_StripingA_dump
#define Gitsn_LaneAttributes_Striping_fdump             Dz1u8A_fdump
#define Gitsn_LaneAttributes_StripingX_fdump Gitsn_LaneAttributes_StripingA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Striping_cmp               Dz1u8_cmp

// Gitsn_LaneAttributes_Striping
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes_TrackedVehicle
typedef u8_t Gitsn_LaneAttributes_TrackedVehicle;

#define Gitsn_LaneAttributes_TrackedVehicle_new               Dz1u8_new
#define Gitsn_LaneAttributes_TrackedVehicle_clone             Dz1u8_clone
#define Gitsn_LaneAttributes_TrackedVehicle_del               Dz1u8_del
#define Gitsn_LaneAttributes_TrackedVehicle_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneAttributes_TrackedVehicleA_dump             Dz1u8A_dump
#define Gitsn_LaneAttributes_TrackedVehicleA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneAttributes_TrackedVehicleW_dump             Dz1u8W_dump
#define Gitsn_LaneAttributes_TrackedVehicleW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneAttributes_TrackedVehicle_dump              Dz1u8W_dump
#define Gitsn_LaneAttributes_TrackedVehicle_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneAttributes_TrackedVehicle_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_TrackedVehicle_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneAttributes_TrackedVehicleX_dump(Gitsn_LaneAttributes_TrackedVehicle *p, int tab) { DZ1_DUMP(Gitsn_LaneAttributes_TrackedVehicle, p, tab); }
static __inline__ void Gitsn_LaneAttributes_TrackedVehicleX_fdump(FILE *fp, Gitsn_LaneAttributes_TrackedVehicle *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneAttributes_TrackedVehicle, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneAttributes_TrackedVehicle_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_TrackedVehicleX_dump Gitsn_LaneAttributes_TrackedVehicleA_dump
#define Gitsn_LaneAttributes_TrackedVehicle_fdump             Dz1u8A_fdump
#define Gitsn_LaneAttributes_TrackedVehicleX_fdump Gitsn_LaneAttributes_TrackedVehicleA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneAttributes_TrackedVehicle_cmp               Dz1u8_cmp

// Gitsn_LaneAttributes_TrackedVehicle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes_Parking
typedef u8_t Gitsn_LaneAttributes_Parking;

#define Gitsn_LaneAttributes_Parking_new               Dz1u8_new
#define Gitsn_LaneAttributes_Parking_clone             Dz1u8_clone
#define Gitsn_LaneAttributes_Parking_del               Dz1u8_del
#define Gitsn_LaneAttributes_Parking_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_LaneAttributes_ParkingA_dump             Dz1u8A_dump
#define Gitsn_LaneAttributes_ParkingA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneAttributes_ParkingW_dump             Dz1u8W_dump
#define Gitsn_LaneAttributes_ParkingW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_LaneAttributes_Parking_dump              Dz1u8W_dump
#define Gitsn_LaneAttributes_Parking_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_LaneAttributes_Parking_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_Parking_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneAttributes_ParkingX_dump(Gitsn_LaneAttributes_Parking *p, int tab) { DZ1_DUMP(Gitsn_LaneAttributes_Parking, p, tab); }
static __inline__ void Gitsn_LaneAttributes_ParkingX_fdump(FILE *fp, Gitsn_LaneAttributes_Parking *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneAttributes_Parking, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Parking_dump              Dz1u8A_dump
#define Gitsn_LaneAttributes_ParkingX_dump Gitsn_LaneAttributes_ParkingA_dump
#define Gitsn_LaneAttributes_Parking_fdump             Dz1u8A_fdump
#define Gitsn_LaneAttributes_ParkingX_fdump Gitsn_LaneAttributes_ParkingA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneAttributes_Parking_cmp               Dz1u8_cmp

// Gitsn_LaneAttributes_Parking
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Offset_B09
typedef s64_t Gitsn_Offset_B09;

#define Gitsn_Offset_B09_new               Dz1s64_new
#define Gitsn_Offset_B09_clone             Dz1s64_clone
#define Gitsn_Offset_B09_del               Dz1s64_del
#define Gitsn_Offset_B09_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Offset_B09A_dump             Dz1s64A_dump
#define Gitsn_Offset_B09A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Offset_B09W_dump             Dz1s64W_dump
#define Gitsn_Offset_B09W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Offset_B09_dump              Dz1s64W_dump
#define Gitsn_Offset_B09_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Offset_B09_dump              Dz1s64A_dump
#define Gitsn_Offset_B09_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Offset_B09X_dump(Gitsn_Offset_B09 *p, int tab) { DZ1_DUMP(Gitsn_Offset_B09, p, tab); }
static __inline__ void Gitsn_Offset_B09X_fdump(FILE *fp, Gitsn_Offset_B09 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Offset_B09, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Offset_B09_dump              Dz1s64A_dump
#define Gitsn_Offset_B09X_dump Gitsn_Offset_B09A_dump
#define Gitsn_Offset_B09_fdump             Dz1s64A_fdump
#define Gitsn_Offset_B09X_fdump Gitsn_Offset_B09A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Offset_B09_cmp               Dz1s64_cmp

// Gitsn_Offset_B09
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Offset_B10
typedef s64_t Gitsn_Offset_B10;

#define Gitsn_Offset_B10_new               Dz1s64_new
#define Gitsn_Offset_B10_clone             Dz1s64_clone
#define Gitsn_Offset_B10_del               Dz1s64_del
#define Gitsn_Offset_B10_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Offset_B10A_dump             Dz1s64A_dump
#define Gitsn_Offset_B10A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Offset_B10W_dump             Dz1s64W_dump
#define Gitsn_Offset_B10W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Offset_B10_dump              Dz1s64W_dump
#define Gitsn_Offset_B10_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Offset_B10_dump              Dz1s64A_dump
#define Gitsn_Offset_B10_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Offset_B10X_dump(Gitsn_Offset_B10 *p, int tab) { DZ1_DUMP(Gitsn_Offset_B10, p, tab); }
static __inline__ void Gitsn_Offset_B10X_fdump(FILE *fp, Gitsn_Offset_B10 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Offset_B10, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Offset_B10_dump              Dz1s64A_dump
#define Gitsn_Offset_B10X_dump Gitsn_Offset_B10A_dump
#define Gitsn_Offset_B10_fdump             Dz1s64A_fdump
#define Gitsn_Offset_B10X_fdump Gitsn_Offset_B10A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Offset_B10_cmp               Dz1s64_cmp

// Gitsn_Offset_B10
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Offset_B11
typedef s64_t Gitsn_Offset_B11;

#define Gitsn_Offset_B11_new               Dz1s64_new
#define Gitsn_Offset_B11_clone             Dz1s64_clone
#define Gitsn_Offset_B11_del               Dz1s64_del
#define Gitsn_Offset_B11_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Offset_B11A_dump             Dz1s64A_dump
#define Gitsn_Offset_B11A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Offset_B11W_dump             Dz1s64W_dump
#define Gitsn_Offset_B11W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Offset_B11_dump              Dz1s64W_dump
#define Gitsn_Offset_B11_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Offset_B11_dump              Dz1s64A_dump
#define Gitsn_Offset_B11_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Offset_B11X_dump(Gitsn_Offset_B11 *p, int tab) { DZ1_DUMP(Gitsn_Offset_B11, p, tab); }
static __inline__ void Gitsn_Offset_B11X_fdump(FILE *fp, Gitsn_Offset_B11 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Offset_B11, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Offset_B11_dump              Dz1s64A_dump
#define Gitsn_Offset_B11X_dump Gitsn_Offset_B11A_dump
#define Gitsn_Offset_B11_fdump             Dz1s64A_fdump
#define Gitsn_Offset_B11X_fdump Gitsn_Offset_B11A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Offset_B11_cmp               Dz1s64_cmp

// Gitsn_Offset_B11
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Offset_B12
typedef s64_t Gitsn_Offset_B12;

#define Gitsn_Offset_B12_new               Dz1s64_new
#define Gitsn_Offset_B12_clone             Dz1s64_clone
#define Gitsn_Offset_B12_del               Dz1s64_del
#define Gitsn_Offset_B12_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Offset_B12A_dump             Dz1s64A_dump
#define Gitsn_Offset_B12A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Offset_B12W_dump             Dz1s64W_dump
#define Gitsn_Offset_B12W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Offset_B12_dump              Dz1s64W_dump
#define Gitsn_Offset_B12_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Offset_B12_dump              Dz1s64A_dump
#define Gitsn_Offset_B12_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Offset_B12X_dump(Gitsn_Offset_B12 *p, int tab) { DZ1_DUMP(Gitsn_Offset_B12, p, tab); }
static __inline__ void Gitsn_Offset_B12X_fdump(FILE *fp, Gitsn_Offset_B12 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Offset_B12, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Offset_B12_dump              Dz1s64A_dump
#define Gitsn_Offset_B12X_dump Gitsn_Offset_B12A_dump
#define Gitsn_Offset_B12_fdump             Dz1s64A_fdump
#define Gitsn_Offset_B12X_fdump Gitsn_Offset_B12A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Offset_B12_cmp               Dz1s64_cmp

// Gitsn_Offset_B12
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Offset_B13
typedef s64_t Gitsn_Offset_B13;

#define Gitsn_Offset_B13_new               Dz1s64_new
#define Gitsn_Offset_B13_clone             Dz1s64_clone
#define Gitsn_Offset_B13_del               Dz1s64_del
#define Gitsn_Offset_B13_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Offset_B13A_dump             Dz1s64A_dump
#define Gitsn_Offset_B13A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Offset_B13W_dump             Dz1s64W_dump
#define Gitsn_Offset_B13W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Offset_B13_dump              Dz1s64W_dump
#define Gitsn_Offset_B13_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Offset_B13_dump              Dz1s64A_dump
#define Gitsn_Offset_B13_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Offset_B13X_dump(Gitsn_Offset_B13 *p, int tab) { DZ1_DUMP(Gitsn_Offset_B13, p, tab); }
static __inline__ void Gitsn_Offset_B13X_fdump(FILE *fp, Gitsn_Offset_B13 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Offset_B13, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Offset_B13_dump              Dz1s64A_dump
#define Gitsn_Offset_B13X_dump Gitsn_Offset_B13A_dump
#define Gitsn_Offset_B13_fdump             Dz1s64A_fdump
#define Gitsn_Offset_B13X_fdump Gitsn_Offset_B13A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Offset_B13_cmp               Dz1s64_cmp

// Gitsn_Offset_B13
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Offset_B14
typedef s64_t Gitsn_Offset_B14;

#define Gitsn_Offset_B14_new               Dz1s64_new
#define Gitsn_Offset_B14_clone             Dz1s64_clone
#define Gitsn_Offset_B14_del               Dz1s64_del
#define Gitsn_Offset_B14_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Offset_B14A_dump             Dz1s64A_dump
#define Gitsn_Offset_B14A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Offset_B14W_dump             Dz1s64W_dump
#define Gitsn_Offset_B14W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Offset_B14_dump              Dz1s64W_dump
#define Gitsn_Offset_B14_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Offset_B14_dump              Dz1s64A_dump
#define Gitsn_Offset_B14_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Offset_B14X_dump(Gitsn_Offset_B14 *p, int tab) { DZ1_DUMP(Gitsn_Offset_B14, p, tab); }
static __inline__ void Gitsn_Offset_B14X_fdump(FILE *fp, Gitsn_Offset_B14 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Offset_B14, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Offset_B14_dump              Dz1s64A_dump
#define Gitsn_Offset_B14X_dump Gitsn_Offset_B14A_dump
#define Gitsn_Offset_B14_fdump             Dz1s64A_fdump
#define Gitsn_Offset_B14X_fdump Gitsn_Offset_B14A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Offset_B14_cmp               Dz1s64_cmp

// Gitsn_Offset_B14
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Offset_B16
typedef s64_t Gitsn_Offset_B16;

#define Gitsn_Offset_B16_new               Dz1s64_new
#define Gitsn_Offset_B16_clone             Dz1s64_clone
#define Gitsn_Offset_B16_del               Dz1s64_del
#define Gitsn_Offset_B16_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Offset_B16A_dump             Dz1s64A_dump
#define Gitsn_Offset_B16A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Offset_B16W_dump             Dz1s64W_dump
#define Gitsn_Offset_B16W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Offset_B16_dump              Dz1s64W_dump
#define Gitsn_Offset_B16_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Offset_B16_dump              Dz1s64A_dump
#define Gitsn_Offset_B16_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Offset_B16X_dump(Gitsn_Offset_B16 *p, int tab) { DZ1_DUMP(Gitsn_Offset_B16, p, tab); }
static __inline__ void Gitsn_Offset_B16X_fdump(FILE *fp, Gitsn_Offset_B16 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Offset_B16, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Offset_B16_dump              Dz1s64A_dump
#define Gitsn_Offset_B16X_dump Gitsn_Offset_B16A_dump
#define Gitsn_Offset_B16_fdump             Dz1s64A_fdump
#define Gitsn_Offset_B16X_fdump Gitsn_Offset_B16A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Offset_B16_cmp               Dz1s64_cmp

// Gitsn_Offset_B16
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetLL_B12
typedef s64_t Gitsn_OffsetLL_B12;

#define Gitsn_OffsetLL_B12_new               Dz1s64_new
#define Gitsn_OffsetLL_B12_clone             Dz1s64_clone
#define Gitsn_OffsetLL_B12_del               Dz1s64_del
#define Gitsn_OffsetLL_B12_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_OffsetLL_B12A_dump             Dz1s64A_dump
#define Gitsn_OffsetLL_B12A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_OffsetLL_B12W_dump             Dz1s64W_dump
#define Gitsn_OffsetLL_B12W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_OffsetLL_B12_dump              Dz1s64W_dump
#define Gitsn_OffsetLL_B12_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_OffsetLL_B12_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B12_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_OffsetLL_B12X_dump(Gitsn_OffsetLL_B12 *p, int tab) { DZ1_DUMP(Gitsn_OffsetLL_B12, p, tab); }
static __inline__ void Gitsn_OffsetLL_B12X_fdump(FILE *fp, Gitsn_OffsetLL_B12 *p, int tab) { DZ1_FDUMP(fp, Gitsn_OffsetLL_B12, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_OffsetLL_B12_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B12X_dump Gitsn_OffsetLL_B12A_dump
#define Gitsn_OffsetLL_B12_fdump             Dz1s64A_fdump
#define Gitsn_OffsetLL_B12X_fdump Gitsn_OffsetLL_B12A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_OffsetLL_B12_cmp               Dz1s64_cmp

// Gitsn_OffsetLL_B12
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetLL_B14
typedef s64_t Gitsn_OffsetLL_B14;

#define Gitsn_OffsetLL_B14_new               Dz1s64_new
#define Gitsn_OffsetLL_B14_clone             Dz1s64_clone
#define Gitsn_OffsetLL_B14_del               Dz1s64_del
#define Gitsn_OffsetLL_B14_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_OffsetLL_B14A_dump             Dz1s64A_dump
#define Gitsn_OffsetLL_B14A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_OffsetLL_B14W_dump             Dz1s64W_dump
#define Gitsn_OffsetLL_B14W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_OffsetLL_B14_dump              Dz1s64W_dump
#define Gitsn_OffsetLL_B14_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_OffsetLL_B14_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B14_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_OffsetLL_B14X_dump(Gitsn_OffsetLL_B14 *p, int tab) { DZ1_DUMP(Gitsn_OffsetLL_B14, p, tab); }
static __inline__ void Gitsn_OffsetLL_B14X_fdump(FILE *fp, Gitsn_OffsetLL_B14 *p, int tab) { DZ1_FDUMP(fp, Gitsn_OffsetLL_B14, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_OffsetLL_B14_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B14X_dump Gitsn_OffsetLL_B14A_dump
#define Gitsn_OffsetLL_B14_fdump             Dz1s64A_fdump
#define Gitsn_OffsetLL_B14X_fdump Gitsn_OffsetLL_B14A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_OffsetLL_B14_cmp               Dz1s64_cmp

// Gitsn_OffsetLL_B14
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetLL_B16
typedef s64_t Gitsn_OffsetLL_B16;

#define Gitsn_OffsetLL_B16_new               Dz1s64_new
#define Gitsn_OffsetLL_B16_clone             Dz1s64_clone
#define Gitsn_OffsetLL_B16_del               Dz1s64_del
#define Gitsn_OffsetLL_B16_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_OffsetLL_B16A_dump             Dz1s64A_dump
#define Gitsn_OffsetLL_B16A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_OffsetLL_B16W_dump             Dz1s64W_dump
#define Gitsn_OffsetLL_B16W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_OffsetLL_B16_dump              Dz1s64W_dump
#define Gitsn_OffsetLL_B16_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_OffsetLL_B16_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B16_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_OffsetLL_B16X_dump(Gitsn_OffsetLL_B16 *p, int tab) { DZ1_DUMP(Gitsn_OffsetLL_B16, p, tab); }
static __inline__ void Gitsn_OffsetLL_B16X_fdump(FILE *fp, Gitsn_OffsetLL_B16 *p, int tab) { DZ1_FDUMP(fp, Gitsn_OffsetLL_B16, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_OffsetLL_B16_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B16X_dump Gitsn_OffsetLL_B16A_dump
#define Gitsn_OffsetLL_B16_fdump             Dz1s64A_fdump
#define Gitsn_OffsetLL_B16X_fdump Gitsn_OffsetLL_B16A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_OffsetLL_B16_cmp               Dz1s64_cmp

// Gitsn_OffsetLL_B16
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetLL_B18
typedef s64_t Gitsn_OffsetLL_B18;

#define Gitsn_OffsetLL_B18_new               Dz1s64_new
#define Gitsn_OffsetLL_B18_clone             Dz1s64_clone
#define Gitsn_OffsetLL_B18_del               Dz1s64_del
#define Gitsn_OffsetLL_B18_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_OffsetLL_B18A_dump             Dz1s64A_dump
#define Gitsn_OffsetLL_B18A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_OffsetLL_B18W_dump             Dz1s64W_dump
#define Gitsn_OffsetLL_B18W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_OffsetLL_B18_dump              Dz1s64W_dump
#define Gitsn_OffsetLL_B18_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_OffsetLL_B18_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B18_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_OffsetLL_B18X_dump(Gitsn_OffsetLL_B18 *p, int tab) { DZ1_DUMP(Gitsn_OffsetLL_B18, p, tab); }
static __inline__ void Gitsn_OffsetLL_B18X_fdump(FILE *fp, Gitsn_OffsetLL_B18 *p, int tab) { DZ1_FDUMP(fp, Gitsn_OffsetLL_B18, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_OffsetLL_B18_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B18X_dump Gitsn_OffsetLL_B18A_dump
#define Gitsn_OffsetLL_B18_fdump             Dz1s64A_fdump
#define Gitsn_OffsetLL_B18X_fdump Gitsn_OffsetLL_B18A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_OffsetLL_B18_cmp               Dz1s64_cmp

// Gitsn_OffsetLL_B18
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetLL_B22
typedef s64_t Gitsn_OffsetLL_B22;

#define Gitsn_OffsetLL_B22_new               Dz1s64_new
#define Gitsn_OffsetLL_B22_clone             Dz1s64_clone
#define Gitsn_OffsetLL_B22_del               Dz1s64_del
#define Gitsn_OffsetLL_B22_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_OffsetLL_B22A_dump             Dz1s64A_dump
#define Gitsn_OffsetLL_B22A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_OffsetLL_B22W_dump             Dz1s64W_dump
#define Gitsn_OffsetLL_B22W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_OffsetLL_B22_dump              Dz1s64W_dump
#define Gitsn_OffsetLL_B22_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_OffsetLL_B22_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B22_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_OffsetLL_B22X_dump(Gitsn_OffsetLL_B22 *p, int tab) { DZ1_DUMP(Gitsn_OffsetLL_B22, p, tab); }
static __inline__ void Gitsn_OffsetLL_B22X_fdump(FILE *fp, Gitsn_OffsetLL_B22 *p, int tab) { DZ1_FDUMP(fp, Gitsn_OffsetLL_B22, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_OffsetLL_B22_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B22X_dump Gitsn_OffsetLL_B22A_dump
#define Gitsn_OffsetLL_B22_fdump             Dz1s64A_fdump
#define Gitsn_OffsetLL_B22X_fdump Gitsn_OffsetLL_B22A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_OffsetLL_B22_cmp               Dz1s64_cmp

// Gitsn_OffsetLL_B22
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetLL_B24
typedef s64_t Gitsn_OffsetLL_B24;

#define Gitsn_OffsetLL_B24_new               Dz1s64_new
#define Gitsn_OffsetLL_B24_clone             Dz1s64_clone
#define Gitsn_OffsetLL_B24_del               Dz1s64_del
#define Gitsn_OffsetLL_B24_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_OffsetLL_B24A_dump             Dz1s64A_dump
#define Gitsn_OffsetLL_B24A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_OffsetLL_B24W_dump             Dz1s64W_dump
#define Gitsn_OffsetLL_B24W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_OffsetLL_B24_dump              Dz1s64W_dump
#define Gitsn_OffsetLL_B24_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_OffsetLL_B24_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B24_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_OffsetLL_B24X_dump(Gitsn_OffsetLL_B24 *p, int tab) { DZ1_DUMP(Gitsn_OffsetLL_B24, p, tab); }
static __inline__ void Gitsn_OffsetLL_B24X_fdump(FILE *fp, Gitsn_OffsetLL_B24 *p, int tab) { DZ1_FDUMP(fp, Gitsn_OffsetLL_B24, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_OffsetLL_B24_dump              Dz1s64A_dump
#define Gitsn_OffsetLL_B24X_dump Gitsn_OffsetLL_B24A_dump
#define Gitsn_OffsetLL_B24_fdump             Dz1s64A_fdump
#define Gitsn_OffsetLL_B24X_fdump Gitsn_OffsetLL_B24A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_OffsetLL_B24_cmp               Dz1s64_cmp

// Gitsn_OffsetLL_B24
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DeltaAngle
typedef s64_t Gitsn_DeltaAngle;

#define Gitsn_DeltaAngle_new               Dz1s64_new
#define Gitsn_DeltaAngle_clone             Dz1s64_clone
#define Gitsn_DeltaAngle_del               Dz1s64_del
#define Gitsn_DeltaAngle_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DeltaAngleA_dump             Dz1s64A_dump
#define Gitsn_DeltaAngleA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DeltaAngleW_dump             Dz1s64W_dump
#define Gitsn_DeltaAngleW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DeltaAngle_dump              Dz1s64W_dump
#define Gitsn_DeltaAngle_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DeltaAngle_dump              Dz1s64A_dump
#define Gitsn_DeltaAngle_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DeltaAngleX_dump(Gitsn_DeltaAngle *p, int tab) { DZ1_DUMP(Gitsn_DeltaAngle, p, tab); }
static __inline__ void Gitsn_DeltaAngleX_fdump(FILE *fp, Gitsn_DeltaAngle *p, int tab) { DZ1_FDUMP(fp, Gitsn_DeltaAngle, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DeltaAngle_dump              Dz1s64A_dump
#define Gitsn_DeltaAngleX_dump Gitsn_DeltaAngleA_dump
#define Gitsn_DeltaAngle_fdump             Dz1s64A_fdump
#define Gitsn_DeltaAngleX_fdump Gitsn_DeltaAngleA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DeltaAngle_cmp               Dz1s64_cmp

// Gitsn_DeltaAngle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadwayCrownAngle
typedef s64_t Gitsn_RoadwayCrownAngle;

#define Gitsn_RoadwayCrownAngle_new               Dz1s64_new
#define Gitsn_RoadwayCrownAngle_clone             Dz1s64_clone
#define Gitsn_RoadwayCrownAngle_del               Dz1s64_del
#define Gitsn_RoadwayCrownAngle_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_RoadwayCrownAngleA_dump             Dz1s64A_dump
#define Gitsn_RoadwayCrownAngleA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RoadwayCrownAngleW_dump             Dz1s64W_dump
#define Gitsn_RoadwayCrownAngleW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_RoadwayCrownAngle_dump              Dz1s64W_dump
#define Gitsn_RoadwayCrownAngle_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_RoadwayCrownAngle_dump              Dz1s64A_dump
#define Gitsn_RoadwayCrownAngle_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RoadwayCrownAngleX_dump(Gitsn_RoadwayCrownAngle *p, int tab) { DZ1_DUMP(Gitsn_RoadwayCrownAngle, p, tab); }
static __inline__ void Gitsn_RoadwayCrownAngleX_fdump(FILE *fp, Gitsn_RoadwayCrownAngle *p, int tab) { DZ1_FDUMP(fp, Gitsn_RoadwayCrownAngle, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RoadwayCrownAngle_dump              Dz1s64A_dump
#define Gitsn_RoadwayCrownAngleX_dump Gitsn_RoadwayCrownAngleA_dump
#define Gitsn_RoadwayCrownAngle_fdump             Dz1s64A_fdump
#define Gitsn_RoadwayCrownAngleX_fdump Gitsn_RoadwayCrownAngleA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RoadwayCrownAngle_cmp               Dz1s64_cmp

// Gitsn_RoadwayCrownAngle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MergeDivergeNodeAngle
typedef s64_t Gitsn_MergeDivergeNodeAngle;

#define Gitsn_MergeDivergeNodeAngle_new               Dz1s64_new
#define Gitsn_MergeDivergeNodeAngle_clone             Dz1s64_clone
#define Gitsn_MergeDivergeNodeAngle_del               Dz1s64_del
#define Gitsn_MergeDivergeNodeAngle_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_MergeDivergeNodeAngleA_dump             Dz1s64A_dump
#define Gitsn_MergeDivergeNodeAngleA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_MergeDivergeNodeAngleW_dump             Dz1s64W_dump
#define Gitsn_MergeDivergeNodeAngleW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_MergeDivergeNodeAngle_dump              Dz1s64W_dump
#define Gitsn_MergeDivergeNodeAngle_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_MergeDivergeNodeAngle_dump              Dz1s64A_dump
#define Gitsn_MergeDivergeNodeAngle_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_MergeDivergeNodeAngleX_dump(Gitsn_MergeDivergeNodeAngle *p, int tab) { DZ1_DUMP(Gitsn_MergeDivergeNodeAngle, p, tab); }
static __inline__ void Gitsn_MergeDivergeNodeAngleX_fdump(FILE *fp, Gitsn_MergeDivergeNodeAngle *p, int tab) { DZ1_FDUMP(fp, Gitsn_MergeDivergeNodeAngle, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_MergeDivergeNodeAngle_dump              Dz1s64A_dump
#define Gitsn_MergeDivergeNodeAngleX_dump Gitsn_MergeDivergeNodeAngleA_dump
#define Gitsn_MergeDivergeNodeAngle_fdump             Dz1s64A_fdump
#define Gitsn_MergeDivergeNodeAngleX_fdump Gitsn_MergeDivergeNodeAngleA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_MergeDivergeNodeAngle_cmp               Dz1s64_cmp

// Gitsn_MergeDivergeNodeAngle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DrivenLineOffsetSm
typedef s64_t Gitsn_DrivenLineOffsetSm;

#define Gitsn_DrivenLineOffsetSm_new               Dz1s64_new
#define Gitsn_DrivenLineOffsetSm_clone             Dz1s64_clone
#define Gitsn_DrivenLineOffsetSm_del               Dz1s64_del
#define Gitsn_DrivenLineOffsetSm_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DrivenLineOffsetSmA_dump             Dz1s64A_dump
#define Gitsn_DrivenLineOffsetSmA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DrivenLineOffsetSmW_dump             Dz1s64W_dump
#define Gitsn_DrivenLineOffsetSmW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DrivenLineOffsetSm_dump              Dz1s64W_dump
#define Gitsn_DrivenLineOffsetSm_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DrivenLineOffsetSm_dump              Dz1s64A_dump
#define Gitsn_DrivenLineOffsetSm_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DrivenLineOffsetSmX_dump(Gitsn_DrivenLineOffsetSm *p, int tab) { DZ1_DUMP(Gitsn_DrivenLineOffsetSm, p, tab); }
static __inline__ void Gitsn_DrivenLineOffsetSmX_fdump(FILE *fp, Gitsn_DrivenLineOffsetSm *p, int tab) { DZ1_FDUMP(fp, Gitsn_DrivenLineOffsetSm, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DrivenLineOffsetSm_dump              Dz1s64A_dump
#define Gitsn_DrivenLineOffsetSmX_dump Gitsn_DrivenLineOffsetSmA_dump
#define Gitsn_DrivenLineOffsetSm_fdump             Dz1s64A_fdump
#define Gitsn_DrivenLineOffsetSmX_fdump Gitsn_DrivenLineOffsetSmA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DrivenLineOffsetSm_cmp               Dz1s64_cmp

// Gitsn_DrivenLineOffsetSm
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DrivenLineOffsetLg
typedef s64_t Gitsn_DrivenLineOffsetLg;

#define Gitsn_DrivenLineOffsetLg_new               Dz1s64_new
#define Gitsn_DrivenLineOffsetLg_clone             Dz1s64_clone
#define Gitsn_DrivenLineOffsetLg_del               Dz1s64_del
#define Gitsn_DrivenLineOffsetLg_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DrivenLineOffsetLgA_dump             Dz1s64A_dump
#define Gitsn_DrivenLineOffsetLgA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DrivenLineOffsetLgW_dump             Dz1s64W_dump
#define Gitsn_DrivenLineOffsetLgW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DrivenLineOffsetLg_dump              Dz1s64W_dump
#define Gitsn_DrivenLineOffsetLg_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DrivenLineOffsetLg_dump              Dz1s64A_dump
#define Gitsn_DrivenLineOffsetLg_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DrivenLineOffsetLgX_dump(Gitsn_DrivenLineOffsetLg *p, int tab) { DZ1_DUMP(Gitsn_DrivenLineOffsetLg, p, tab); }
static __inline__ void Gitsn_DrivenLineOffsetLgX_fdump(FILE *fp, Gitsn_DrivenLineOffsetLg *p, int tab) { DZ1_FDUMP(fp, Gitsn_DrivenLineOffsetLg, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DrivenLineOffsetLg_dump              Dz1s64A_dump
#define Gitsn_DrivenLineOffsetLgX_dump Gitsn_DrivenLineOffsetLgA_dump
#define Gitsn_DrivenLineOffsetLg_fdump             Dz1s64A_fdump
#define Gitsn_DrivenLineOffsetLgX_fdump Gitsn_DrivenLineOffsetLgA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DrivenLineOffsetLg_cmp               Dz1s64_cmp

// Gitsn_DrivenLineOffsetLg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Angle
typedef s64_t Gitsn_Angle;

#define Gitsn_Angle_new               Dz1s64_new
#define Gitsn_Angle_clone             Dz1s64_clone
#define Gitsn_Angle_del               Dz1s64_del
#define Gitsn_Angle_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_AngleA_dump             Dz1s64A_dump
#define Gitsn_AngleA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_AngleW_dump             Dz1s64W_dump
#define Gitsn_AngleW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Angle_dump              Dz1s64W_dump
#define Gitsn_Angle_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Angle_dump              Dz1s64A_dump
#define Gitsn_Angle_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_AngleX_dump(Gitsn_Angle *p, int tab) { DZ1_DUMP(Gitsn_Angle, p, tab); }
static __inline__ void Gitsn_AngleX_fdump(FILE *fp, Gitsn_Angle *p, int tab) { DZ1_FDUMP(fp, Gitsn_Angle, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Angle_dump              Dz1s64A_dump
#define Gitsn_AngleX_dump Gitsn_AngleA_dump
#define Gitsn_Angle_fdump             Dz1s64A_fdump
#define Gitsn_AngleX_fdump Gitsn_AngleA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Angle_cmp               Dz1s64_cmp

// Gitsn_Angle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Scale_B12
typedef s64_t Gitsn_Scale_B12;

#define Gitsn_Scale_B12_new               Dz1s64_new
#define Gitsn_Scale_B12_clone             Dz1s64_clone
#define Gitsn_Scale_B12_del               Dz1s64_del
#define Gitsn_Scale_B12_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Scale_B12A_dump             Dz1s64A_dump
#define Gitsn_Scale_B12A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Scale_B12W_dump             Dz1s64W_dump
#define Gitsn_Scale_B12W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Scale_B12_dump              Dz1s64W_dump
#define Gitsn_Scale_B12_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Scale_B12_dump              Dz1s64A_dump
#define Gitsn_Scale_B12_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Scale_B12X_dump(Gitsn_Scale_B12 *p, int tab) { DZ1_DUMP(Gitsn_Scale_B12, p, tab); }
static __inline__ void Gitsn_Scale_B12X_fdump(FILE *fp, Gitsn_Scale_B12 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Scale_B12, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Scale_B12_dump              Dz1s64A_dump
#define Gitsn_Scale_B12X_dump Gitsn_Scale_B12A_dump
#define Gitsn_Scale_B12_fdump             Dz1s64A_fdump
#define Gitsn_Scale_B12X_fdump Gitsn_Scale_B12A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Scale_B12_cmp               Dz1s64_cmp

// Gitsn_Scale_B12
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionClassID
typedef s64_t Gitsn_RestrictionClassID;

#define Gitsn_RestrictionClassID_new               Dz1s64_new
#define Gitsn_RestrictionClassID_clone             Dz1s64_clone
#define Gitsn_RestrictionClassID_del               Dz1s64_del
#define Gitsn_RestrictionClassID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_RestrictionClassIDA_dump             Dz1s64A_dump
#define Gitsn_RestrictionClassIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RestrictionClassIDW_dump             Dz1s64W_dump
#define Gitsn_RestrictionClassIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_RestrictionClassID_dump              Dz1s64W_dump
#define Gitsn_RestrictionClassID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_RestrictionClassID_dump              Dz1s64A_dump
#define Gitsn_RestrictionClassID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RestrictionClassIDX_dump(Gitsn_RestrictionClassID *p, int tab) { DZ1_DUMP(Gitsn_RestrictionClassID, p, tab); }
static __inline__ void Gitsn_RestrictionClassIDX_fdump(FILE *fp, Gitsn_RestrictionClassID *p, int tab) { DZ1_FDUMP(fp, Gitsn_RestrictionClassID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RestrictionClassID_dump              Dz1s64A_dump
#define Gitsn_RestrictionClassIDX_dump Gitsn_RestrictionClassIDA_dump
#define Gitsn_RestrictionClassID_fdump             Dz1s64A_fdump
#define Gitsn_RestrictionClassIDX_fdump Gitsn_RestrictionClassIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RestrictionClassID_cmp               Dz1s64_cmp

// Gitsn_RestrictionClassID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalGroupID
typedef s64_t Gitsn_SignalGroupID;

#define Gitsn_SignalGroupID_new               Dz1s64_new
#define Gitsn_SignalGroupID_clone             Dz1s64_clone
#define Gitsn_SignalGroupID_del               Dz1s64_del
#define Gitsn_SignalGroupID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SignalGroupIDA_dump             Dz1s64A_dump
#define Gitsn_SignalGroupIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SignalGroupIDW_dump             Dz1s64W_dump
#define Gitsn_SignalGroupIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SignalGroupID_dump              Dz1s64W_dump
#define Gitsn_SignalGroupID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SignalGroupID_dump              Dz1s64A_dump
#define Gitsn_SignalGroupID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SignalGroupIDX_dump(Gitsn_SignalGroupID *p, int tab) { DZ1_DUMP(Gitsn_SignalGroupID, p, tab); }
static __inline__ void Gitsn_SignalGroupIDX_fdump(FILE *fp, Gitsn_SignalGroupID *p, int tab) { DZ1_FDUMP(fp, Gitsn_SignalGroupID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SignalGroupID_dump              Dz1s64A_dump
#define Gitsn_SignalGroupIDX_dump Gitsn_SignalGroupIDA_dump
#define Gitsn_SignalGroupID_fdump             Dz1s64A_fdump
#define Gitsn_SignalGroupIDX_fdump Gitsn_SignalGroupIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SignalGroupID_cmp               Dz1s64_cmp

// Gitsn_SignalGroupID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneConnectionID
typedef s64_t Gitsn_LaneConnectionID;

#define Gitsn_LaneConnectionID_new               Dz1s64_new
#define Gitsn_LaneConnectionID_clone             Dz1s64_clone
#define Gitsn_LaneConnectionID_del               Dz1s64_del
#define Gitsn_LaneConnectionID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_LaneConnectionIDA_dump             Dz1s64A_dump
#define Gitsn_LaneConnectionIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_LaneConnectionIDW_dump             Dz1s64W_dump
#define Gitsn_LaneConnectionIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_LaneConnectionID_dump              Dz1s64W_dump
#define Gitsn_LaneConnectionID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_LaneConnectionID_dump              Dz1s64A_dump
#define Gitsn_LaneConnectionID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_LaneConnectionIDX_dump(Gitsn_LaneConnectionID *p, int tab) { DZ1_DUMP(Gitsn_LaneConnectionID, p, tab); }
static __inline__ void Gitsn_LaneConnectionIDX_fdump(FILE *fp, Gitsn_LaneConnectionID *p, int tab) { DZ1_FDUMP(fp, Gitsn_LaneConnectionID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_LaneConnectionID_dump              Dz1s64A_dump
#define Gitsn_LaneConnectionIDX_dump Gitsn_LaneConnectionIDA_dump
#define Gitsn_LaneConnectionID_fdump             Dz1s64A_fdump
#define Gitsn_LaneConnectionIDX_fdump Gitsn_LaneConnectionIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_LaneConnectionID_cmp               Dz1s64_cmp

// Gitsn_LaneConnectionID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeOffset
typedef s64_t Gitsn_TimeOffset;

#define Gitsn_TimeOffset_new               Dz1s64_new
#define Gitsn_TimeOffset_clone             Dz1s64_clone
#define Gitsn_TimeOffset_del               Dz1s64_del
#define Gitsn_TimeOffset_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TimeOffsetA_dump             Dz1s64A_dump
#define Gitsn_TimeOffsetA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TimeOffsetW_dump             Dz1s64W_dump
#define Gitsn_TimeOffsetW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TimeOffset_dump              Dz1s64W_dump
#define Gitsn_TimeOffset_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TimeOffset_dump              Dz1s64A_dump
#define Gitsn_TimeOffset_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TimeOffsetX_dump(Gitsn_TimeOffset *p, int tab) { DZ1_DUMP(Gitsn_TimeOffset, p, tab); }
static __inline__ void Gitsn_TimeOffsetX_fdump(FILE *fp, Gitsn_TimeOffset *p, int tab) { DZ1_FDUMP(fp, Gitsn_TimeOffset, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TimeOffset_dump              Dz1s64A_dump
#define Gitsn_TimeOffsetX_dump Gitsn_TimeOffsetA_dump
#define Gitsn_TimeOffset_fdump             Dz1s64A_fdump
#define Gitsn_TimeOffsetX_fdump Gitsn_TimeOffsetA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TimeOffset_cmp               Dz1s64_cmp

// Gitsn_TimeOffset
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeMark
typedef s64_t Gitsn_TimeMark;

#define Gitsn_TimeMark_new               Dz1s64_new
#define Gitsn_TimeMark_clone             Dz1s64_clone
#define Gitsn_TimeMark_del               Dz1s64_del
#define Gitsn_TimeMark_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TimeMarkA_dump             Dz1s64A_dump
#define Gitsn_TimeMarkA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TimeMarkW_dump             Dz1s64W_dump
#define Gitsn_TimeMarkW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TimeMark_dump              Dz1s64W_dump
#define Gitsn_TimeMark_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TimeMark_dump              Dz1s64A_dump
#define Gitsn_TimeMark_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TimeMarkX_dump(Gitsn_TimeMark *p, int tab) { DZ1_DUMP(Gitsn_TimeMark, p, tab); }
static __inline__ void Gitsn_TimeMarkX_fdump(FILE *fp, Gitsn_TimeMark *p, int tab) { DZ1_FDUMP(fp, Gitsn_TimeMark, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TimeMark_dump              Dz1s64A_dump
#define Gitsn_TimeMarkX_dump Gitsn_TimeMarkA_dump
#define Gitsn_TimeMark_fdump             Dz1s64A_fdump
#define Gitsn_TimeMarkX_fdump Gitsn_TimeMarkA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TimeMark_cmp               Dz1s64_cmp

// Gitsn_TimeMark
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BasicVehicleClass
typedef s64_t Gitsn_BasicVehicleClass;

#define Gitsn_BasicVehicleClass_new               Dz1s64_new
#define Gitsn_BasicVehicleClass_clone             Dz1s64_clone
#define Gitsn_BasicVehicleClass_del               Dz1s64_del
#define Gitsn_BasicVehicleClass_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_BasicVehicleClassA_dump             Dz1s64A_dump
#define Gitsn_BasicVehicleClassA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_BasicVehicleClassW_dump             Dz1s64W_dump
#define Gitsn_BasicVehicleClassW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_BasicVehicleClass_dump              Dz1s64W_dump
#define Gitsn_BasicVehicleClass_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_BasicVehicleClass_dump              Dz1s64A_dump
#define Gitsn_BasicVehicleClass_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_BasicVehicleClassX_dump(Gitsn_BasicVehicleClass *p, int tab) { DZ1_DUMP(Gitsn_BasicVehicleClass, p, tab); }
static __inline__ void Gitsn_BasicVehicleClassX_fdump(FILE *fp, Gitsn_BasicVehicleClass *p, int tab) { DZ1_FDUMP(fp, Gitsn_BasicVehicleClass, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_BasicVehicleClass_dump              Dz1s64A_dump
#define Gitsn_BasicVehicleClassX_dump Gitsn_BasicVehicleClassA_dump
#define Gitsn_BasicVehicleClass_fdump             Dz1s64A_fdump
#define Gitsn_BasicVehicleClassX_fdump Gitsn_BasicVehicleClassA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_BasicVehicleClass_cmp               Dz1s64_cmp

// Gitsn_BasicVehicleClass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso3833VehicleType
typedef s64_t Gitsn_Iso3833VehicleType;

#define Gitsn_Iso3833VehicleType_new               Dz1s64_new
#define Gitsn_Iso3833VehicleType_clone             Dz1s64_clone
#define Gitsn_Iso3833VehicleType_del               Dz1s64_del
#define Gitsn_Iso3833VehicleType_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Iso3833VehicleTypeA_dump             Dz1s64A_dump
#define Gitsn_Iso3833VehicleTypeA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Iso3833VehicleTypeW_dump             Dz1s64W_dump
#define Gitsn_Iso3833VehicleTypeW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Iso3833VehicleType_dump              Dz1s64W_dump
#define Gitsn_Iso3833VehicleType_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Iso3833VehicleType_dump              Dz1s64A_dump
#define Gitsn_Iso3833VehicleType_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Iso3833VehicleTypeX_dump(Gitsn_Iso3833VehicleType *p, int tab) { DZ1_DUMP(Gitsn_Iso3833VehicleType, p, tab); }
static __inline__ void Gitsn_Iso3833VehicleTypeX_fdump(FILE *fp, Gitsn_Iso3833VehicleType *p, int tab) { DZ1_FDUMP(fp, Gitsn_Iso3833VehicleType, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Iso3833VehicleType_dump              Dz1s64A_dump
#define Gitsn_Iso3833VehicleTypeX_dump Gitsn_Iso3833VehicleTypeA_dump
#define Gitsn_Iso3833VehicleType_fdump             Dz1s64A_fdump
#define Gitsn_Iso3833VehicleTypeX_fdump Gitsn_Iso3833VehicleTypeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Iso3833VehicleType_cmp               Dz1s64_cmp

// Gitsn_Iso3833VehicleType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_FuelType
typedef s64_t Gitsn_FuelType;

#define Gitsn_FuelType_new               Dz1s64_new
#define Gitsn_FuelType_clone             Dz1s64_clone
#define Gitsn_FuelType_del               Dz1s64_del
#define Gitsn_FuelType_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_FuelTypeA_dump             Dz1s64A_dump
#define Gitsn_FuelTypeA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_FuelTypeW_dump             Dz1s64W_dump
#define Gitsn_FuelTypeW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_FuelType_dump              Dz1s64W_dump
#define Gitsn_FuelType_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_FuelType_dump              Dz1s64A_dump
#define Gitsn_FuelType_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_FuelTypeX_dump(Gitsn_FuelType *p, int tab) { DZ1_DUMP(Gitsn_FuelType, p, tab); }
static __inline__ void Gitsn_FuelTypeX_fdump(FILE *fp, Gitsn_FuelType *p, int tab) { DZ1_FDUMP(fp, Gitsn_FuelType, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_FuelType_dump              Dz1s64A_dump
#define Gitsn_FuelTypeX_dump Gitsn_FuelTypeA_dump
#define Gitsn_FuelType_fdump             Dz1s64A_fdump
#define Gitsn_FuelTypeX_fdump Gitsn_FuelTypeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_FuelType_cmp               Dz1s64_cmp

// Gitsn_FuelType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleEventFlags
typedef u8_t Gitsn_VehicleEventFlags;

#define Gitsn_VehicleEventFlags_new               Dz1u8_new
#define Gitsn_VehicleEventFlags_clone             Dz1u8_clone
#define Gitsn_VehicleEventFlags_del               Dz1u8_del
#define Gitsn_VehicleEventFlags_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_VehicleEventFlagsA_dump             Dz1u8A_dump
#define Gitsn_VehicleEventFlagsA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VehicleEventFlagsW_dump             Dz1u8W_dump
#define Gitsn_VehicleEventFlagsW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_VehicleEventFlags_dump              Dz1u8W_dump
#define Gitsn_VehicleEventFlags_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_VehicleEventFlags_dump              Dz1u8A_dump
#define Gitsn_VehicleEventFlags_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VehicleEventFlagsX_dump(Gitsn_VehicleEventFlags *p, int tab) { DZ1_DUMP(Gitsn_VehicleEventFlags, p, tab); }
static __inline__ void Gitsn_VehicleEventFlagsX_fdump(FILE *fp, Gitsn_VehicleEventFlags *p, int tab) { DZ1_FDUMP(fp, Gitsn_VehicleEventFlags, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VehicleEventFlags_dump              Dz1u8A_dump
#define Gitsn_VehicleEventFlagsX_dump Gitsn_VehicleEventFlagsA_dump
#define Gitsn_VehicleEventFlags_fdump             Dz1u8A_fdump
#define Gitsn_VehicleEventFlagsX_fdump Gitsn_VehicleEventFlagsA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VehicleEventFlags_cmp               Dz1u8_cmp

// Gitsn_VehicleEventFlags
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ExteriorLights
typedef u8_t Gitsn_ExteriorLights;

#define Gitsn_ExteriorLights_new               Dz1u8_new
#define Gitsn_ExteriorLights_clone             Dz1u8_clone
#define Gitsn_ExteriorLights_del               Dz1u8_del
#define Gitsn_ExteriorLights_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_ExteriorLightsA_dump             Dz1u8A_dump
#define Gitsn_ExteriorLightsA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ExteriorLightsW_dump             Dz1u8W_dump
#define Gitsn_ExteriorLightsW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_ExteriorLights_dump              Dz1u8W_dump
#define Gitsn_ExteriorLights_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_ExteriorLights_dump              Dz1u8A_dump
#define Gitsn_ExteriorLights_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ExteriorLightsX_dump(Gitsn_ExteriorLights *p, int tab) { DZ1_DUMP(Gitsn_ExteriorLights, p, tab); }
static __inline__ void Gitsn_ExteriorLightsX_fdump(FILE *fp, Gitsn_ExteriorLights *p, int tab) { DZ1_FDUMP(fp, Gitsn_ExteriorLights, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ExteriorLights_dump              Dz1u8A_dump
#define Gitsn_ExteriorLightsX_dump Gitsn_ExteriorLightsA_dump
#define Gitsn_ExteriorLights_fdump             Dz1u8A_fdump
#define Gitsn_ExteriorLightsX_fdump Gitsn_ExteriorLightsA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ExteriorLights_cmp               Dz1u8_cmp

// Gitsn_ExteriorLights
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RadiusOfCurvature
typedef s64_t Gitsn_RadiusOfCurvature;

#define Gitsn_RadiusOfCurvature_new               Dz1s64_new
#define Gitsn_RadiusOfCurvature_clone             Dz1s64_clone
#define Gitsn_RadiusOfCurvature_del               Dz1s64_del
#define Gitsn_RadiusOfCurvature_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_RadiusOfCurvatureA_dump             Dz1s64A_dump
#define Gitsn_RadiusOfCurvatureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RadiusOfCurvatureW_dump             Dz1s64W_dump
#define Gitsn_RadiusOfCurvatureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_RadiusOfCurvature_dump              Dz1s64W_dump
#define Gitsn_RadiusOfCurvature_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_RadiusOfCurvature_dump              Dz1s64A_dump
#define Gitsn_RadiusOfCurvature_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RadiusOfCurvatureX_dump(Gitsn_RadiusOfCurvature *p, int tab) { DZ1_DUMP(Gitsn_RadiusOfCurvature, p, tab); }
static __inline__ void Gitsn_RadiusOfCurvatureX_fdump(FILE *fp, Gitsn_RadiusOfCurvature *p, int tab) { DZ1_FDUMP(fp, Gitsn_RadiusOfCurvature, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RadiusOfCurvature_dump              Dz1s64A_dump
#define Gitsn_RadiusOfCurvatureX_dump Gitsn_RadiusOfCurvatureA_dump
#define Gitsn_RadiusOfCurvature_fdump             Dz1s64A_fdump
#define Gitsn_RadiusOfCurvatureX_fdump Gitsn_RadiusOfCurvatureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RadiusOfCurvature_cmp               Dz1s64_cmp

// Gitsn_RadiusOfCurvature
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Confidence
typedef s64_t Gitsn_Confidence;

#define Gitsn_Confidence_new               Dz1s64_new
#define Gitsn_Confidence_clone             Dz1s64_clone
#define Gitsn_Confidence_del               Dz1s64_del
#define Gitsn_Confidence_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ConfidenceA_dump             Dz1s64A_dump
#define Gitsn_ConfidenceA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ConfidenceW_dump             Dz1s64W_dump
#define Gitsn_ConfidenceW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Confidence_dump              Dz1s64W_dump
#define Gitsn_Confidence_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Confidence_dump              Dz1s64A_dump
#define Gitsn_Confidence_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ConfidenceX_dump(Gitsn_Confidence *p, int tab) { DZ1_DUMP(Gitsn_Confidence, p, tab); }
static __inline__ void Gitsn_ConfidenceX_fdump(FILE *fp, Gitsn_Confidence *p, int tab) { DZ1_FDUMP(fp, Gitsn_Confidence, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Confidence_dump              Dz1s64A_dump
#define Gitsn_ConfidenceX_dump Gitsn_ConfidenceA_dump
#define Gitsn_Confidence_fdump             Dz1s64A_fdump
#define Gitsn_ConfidenceX_fdump Gitsn_ConfidenceA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Confidence_cmp               Dz1s64_cmp

// Gitsn_Confidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WiperRate
typedef s64_t Gitsn_WiperRate;

#define Gitsn_WiperRate_new               Dz1s64_new
#define Gitsn_WiperRate_clone             Dz1s64_clone
#define Gitsn_WiperRate_del               Dz1s64_del
#define Gitsn_WiperRate_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_WiperRateA_dump             Dz1s64A_dump
#define Gitsn_WiperRateA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_WiperRateW_dump             Dz1s64W_dump
#define Gitsn_WiperRateW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_WiperRate_dump              Dz1s64W_dump
#define Gitsn_WiperRate_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_WiperRate_dump              Dz1s64A_dump
#define Gitsn_WiperRate_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_WiperRateX_dump(Gitsn_WiperRate *p, int tab) { DZ1_DUMP(Gitsn_WiperRate, p, tab); }
static __inline__ void Gitsn_WiperRateX_fdump(FILE *fp, Gitsn_WiperRate *p, int tab) { DZ1_FDUMP(fp, Gitsn_WiperRate, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_WiperRate_dump              Dz1s64A_dump
#define Gitsn_WiperRateX_dump Gitsn_WiperRateA_dump
#define Gitsn_WiperRate_fdump             Dz1s64A_fdump
#define Gitsn_WiperRateX_fdump Gitsn_WiperRateA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_WiperRate_cmp               Dz1s64_cmp

// Gitsn_WiperRate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BrakeAppliedStatus
typedef u8_t Gitsn_BrakeAppliedStatus;

#define Gitsn_BrakeAppliedStatus_new               Dz1u8_new
#define Gitsn_BrakeAppliedStatus_clone             Dz1u8_clone
#define Gitsn_BrakeAppliedStatus_del               Dz1u8_del
#define Gitsn_BrakeAppliedStatus_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_BrakeAppliedStatusA_dump             Dz1u8A_dump
#define Gitsn_BrakeAppliedStatusA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_BrakeAppliedStatusW_dump             Dz1u8W_dump
#define Gitsn_BrakeAppliedStatusW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_BrakeAppliedStatus_dump              Dz1u8W_dump
#define Gitsn_BrakeAppliedStatus_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_BrakeAppliedStatus_dump              Dz1u8A_dump
#define Gitsn_BrakeAppliedStatus_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_BrakeAppliedStatusX_dump(Gitsn_BrakeAppliedStatus *p, int tab) { DZ1_DUMP(Gitsn_BrakeAppliedStatus, p, tab); }
static __inline__ void Gitsn_BrakeAppliedStatusX_fdump(FILE *fp, Gitsn_BrakeAppliedStatus *p, int tab) { DZ1_FDUMP(fp, Gitsn_BrakeAppliedStatus, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_BrakeAppliedStatus_dump              Dz1u8A_dump
#define Gitsn_BrakeAppliedStatusX_dump Gitsn_BrakeAppliedStatusA_dump
#define Gitsn_BrakeAppliedStatus_fdump             Dz1u8A_fdump
#define Gitsn_BrakeAppliedStatusX_fdump Gitsn_BrakeAppliedStatusA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_BrakeAppliedStatus_cmp               Dz1u8_cmp

// Gitsn_BrakeAppliedStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_CoefficientOfFriction
typedef s64_t Gitsn_CoefficientOfFriction;

#define Gitsn_CoefficientOfFriction_new               Dz1s64_new
#define Gitsn_CoefficientOfFriction_clone             Dz1s64_clone
#define Gitsn_CoefficientOfFriction_del               Dz1s64_del
#define Gitsn_CoefficientOfFriction_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_CoefficientOfFrictionA_dump             Dz1s64A_dump
#define Gitsn_CoefficientOfFrictionA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_CoefficientOfFrictionW_dump             Dz1s64W_dump
#define Gitsn_CoefficientOfFrictionW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_CoefficientOfFriction_dump              Dz1s64W_dump
#define Gitsn_CoefficientOfFriction_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_CoefficientOfFriction_dump              Dz1s64A_dump
#define Gitsn_CoefficientOfFriction_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_CoefficientOfFrictionX_dump(Gitsn_CoefficientOfFriction *p, int tab) { DZ1_DUMP(Gitsn_CoefficientOfFriction, p, tab); }
static __inline__ void Gitsn_CoefficientOfFrictionX_fdump(FILE *fp, Gitsn_CoefficientOfFriction *p, int tab) { DZ1_FDUMP(fp, Gitsn_CoefficientOfFriction, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_CoefficientOfFriction_dump              Dz1s64A_dump
#define Gitsn_CoefficientOfFrictionX_dump Gitsn_CoefficientOfFrictionA_dump
#define Gitsn_CoefficientOfFriction_fdump             Dz1s64A_fdump
#define Gitsn_CoefficientOfFrictionX_fdump Gitsn_CoefficientOfFrictionA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_CoefficientOfFriction_cmp               Dz1s64_cmp

// Gitsn_CoefficientOfFriction
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SunSensor
typedef s64_t Gitsn_SunSensor;

#define Gitsn_SunSensor_new               Dz1s64_new
#define Gitsn_SunSensor_clone             Dz1s64_clone
#define Gitsn_SunSensor_del               Dz1s64_del
#define Gitsn_SunSensor_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SunSensorA_dump             Dz1s64A_dump
#define Gitsn_SunSensorA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SunSensorW_dump             Dz1s64W_dump
#define Gitsn_SunSensorW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SunSensor_dump              Dz1s64W_dump
#define Gitsn_SunSensor_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SunSensor_dump              Dz1s64A_dump
#define Gitsn_SunSensor_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SunSensorX_dump(Gitsn_SunSensor *p, int tab) { DZ1_DUMP(Gitsn_SunSensor, p, tab); }
static __inline__ void Gitsn_SunSensorX_fdump(FILE *fp, Gitsn_SunSensor *p, int tab) { DZ1_FDUMP(fp, Gitsn_SunSensor, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SunSensor_dump              Dz1s64A_dump
#define Gitsn_SunSensorX_dump Gitsn_SunSensorA_dump
#define Gitsn_SunSensor_fdump             Dz1s64A_fdump
#define Gitsn_SunSensorX_fdump Gitsn_SunSensorA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SunSensor_cmp               Dz1s64_cmp

// Gitsn_SunSensor
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AmbientAirTemperature
typedef s64_t Gitsn_AmbientAirTemperature;

#define Gitsn_AmbientAirTemperature_new               Dz1s64_new
#define Gitsn_AmbientAirTemperature_clone             Dz1s64_clone
#define Gitsn_AmbientAirTemperature_del               Dz1s64_del
#define Gitsn_AmbientAirTemperature_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_AmbientAirTemperatureA_dump             Dz1s64A_dump
#define Gitsn_AmbientAirTemperatureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_AmbientAirTemperatureW_dump             Dz1s64W_dump
#define Gitsn_AmbientAirTemperatureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_AmbientAirTemperature_dump              Dz1s64W_dump
#define Gitsn_AmbientAirTemperature_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_AmbientAirTemperature_dump              Dz1s64A_dump
#define Gitsn_AmbientAirTemperature_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_AmbientAirTemperatureX_dump(Gitsn_AmbientAirTemperature *p, int tab) { DZ1_DUMP(Gitsn_AmbientAirTemperature, p, tab); }
static __inline__ void Gitsn_AmbientAirTemperatureX_fdump(FILE *fp, Gitsn_AmbientAirTemperature *p, int tab) { DZ1_FDUMP(fp, Gitsn_AmbientAirTemperature, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_AmbientAirTemperature_dump              Dz1s64A_dump
#define Gitsn_AmbientAirTemperatureX_dump Gitsn_AmbientAirTemperatureA_dump
#define Gitsn_AmbientAirTemperature_fdump             Dz1s64A_fdump
#define Gitsn_AmbientAirTemperatureX_fdump Gitsn_AmbientAirTemperatureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_AmbientAirTemperature_cmp               Dz1s64_cmp

// Gitsn_AmbientAirTemperature
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AmbientAirPressure
typedef s64_t Gitsn_AmbientAirPressure;

#define Gitsn_AmbientAirPressure_new               Dz1s64_new
#define Gitsn_AmbientAirPressure_clone             Dz1s64_clone
#define Gitsn_AmbientAirPressure_del               Dz1s64_del
#define Gitsn_AmbientAirPressure_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_AmbientAirPressureA_dump             Dz1s64A_dump
#define Gitsn_AmbientAirPressureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_AmbientAirPressureW_dump             Dz1s64W_dump
#define Gitsn_AmbientAirPressureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_AmbientAirPressure_dump              Dz1s64W_dump
#define Gitsn_AmbientAirPressure_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_AmbientAirPressure_dump              Dz1s64A_dump
#define Gitsn_AmbientAirPressure_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_AmbientAirPressureX_dump(Gitsn_AmbientAirPressure *p, int tab) { DZ1_DUMP(Gitsn_AmbientAirPressure, p, tab); }
static __inline__ void Gitsn_AmbientAirPressureX_fdump(FILE *fp, Gitsn_AmbientAirPressure *p, int tab) { DZ1_FDUMP(fp, Gitsn_AmbientAirPressure, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_AmbientAirPressure_dump              Dz1s64A_dump
#define Gitsn_AmbientAirPressureX_dump Gitsn_AmbientAirPressureA_dump
#define Gitsn_AmbientAirPressure_fdump             Dz1s64A_fdump
#define Gitsn_AmbientAirPressureX_fdump Gitsn_AmbientAirPressureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_AmbientAirPressure_cmp               Dz1s64_cmp

// Gitsn_AmbientAirPressure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SteeringWheelAngle
typedef s64_t Gitsn_SteeringWheelAngle;

#define Gitsn_SteeringWheelAngle_new               Dz1s64_new
#define Gitsn_SteeringWheelAngle_clone             Dz1s64_clone
#define Gitsn_SteeringWheelAngle_del               Dz1s64_del
#define Gitsn_SteeringWheelAngle_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SteeringWheelAngleA_dump             Dz1s64A_dump
#define Gitsn_SteeringWheelAngleA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SteeringWheelAngleW_dump             Dz1s64W_dump
#define Gitsn_SteeringWheelAngleW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SteeringWheelAngle_dump              Dz1s64W_dump
#define Gitsn_SteeringWheelAngle_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SteeringWheelAngle_dump              Dz1s64A_dump
#define Gitsn_SteeringWheelAngle_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SteeringWheelAngleX_dump(Gitsn_SteeringWheelAngle *p, int tab) { DZ1_DUMP(Gitsn_SteeringWheelAngle, p, tab); }
static __inline__ void Gitsn_SteeringWheelAngleX_fdump(FILE *fp, Gitsn_SteeringWheelAngle *p, int tab) { DZ1_FDUMP(fp, Gitsn_SteeringWheelAngle, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SteeringWheelAngle_dump              Dz1s64A_dump
#define Gitsn_SteeringWheelAngleX_dump Gitsn_SteeringWheelAngleA_dump
#define Gitsn_SteeringWheelAngle_fdump             Dz1s64A_fdump
#define Gitsn_SteeringWheelAngleX_fdump Gitsn_SteeringWheelAngleA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SteeringWheelAngle_cmp               Dz1s64_cmp

// Gitsn_SteeringWheelAngle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SteeringWheelAngleRateOfChange
typedef s64_t Gitsn_SteeringWheelAngleRateOfChange;

#define Gitsn_SteeringWheelAngleRateOfChange_new               Dz1s64_new
#define Gitsn_SteeringWheelAngleRateOfChange_clone             Dz1s64_clone
#define Gitsn_SteeringWheelAngleRateOfChange_del               Dz1s64_del
#define Gitsn_SteeringWheelAngleRateOfChange_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SteeringWheelAngleRateOfChangeA_dump             Dz1s64A_dump
#define Gitsn_SteeringWheelAngleRateOfChangeA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SteeringWheelAngleRateOfChangeW_dump             Dz1s64W_dump
#define Gitsn_SteeringWheelAngleRateOfChangeW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SteeringWheelAngleRateOfChange_dump              Dz1s64W_dump
#define Gitsn_SteeringWheelAngleRateOfChange_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SteeringWheelAngleRateOfChange_dump              Dz1s64A_dump
#define Gitsn_SteeringWheelAngleRateOfChange_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SteeringWheelAngleRateOfChangeX_dump(Gitsn_SteeringWheelAngleRateOfChange *p, int tab) { DZ1_DUMP(Gitsn_SteeringWheelAngleRateOfChange, p, tab); }
static __inline__ void Gitsn_SteeringWheelAngleRateOfChangeX_fdump(FILE *fp, Gitsn_SteeringWheelAngleRateOfChange *p, int tab) { DZ1_FDUMP(fp, Gitsn_SteeringWheelAngleRateOfChange, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SteeringWheelAngleRateOfChange_dump              Dz1s64A_dump
#define Gitsn_SteeringWheelAngleRateOfChangeX_dump Gitsn_SteeringWheelAngleRateOfChangeA_dump
#define Gitsn_SteeringWheelAngleRateOfChange_fdump             Dz1s64A_fdump
#define Gitsn_SteeringWheelAngleRateOfChangeX_fdump Gitsn_SteeringWheelAngleRateOfChangeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SteeringWheelAngleRateOfChange_cmp               Dz1s64_cmp

// Gitsn_SteeringWheelAngleRateOfChange
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DrivingWheelAngle
typedef s64_t Gitsn_DrivingWheelAngle;

#define Gitsn_DrivingWheelAngle_new               Dz1s64_new
#define Gitsn_DrivingWheelAngle_clone             Dz1s64_clone
#define Gitsn_DrivingWheelAngle_del               Dz1s64_del
#define Gitsn_DrivingWheelAngle_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DrivingWheelAngleA_dump             Dz1s64A_dump
#define Gitsn_DrivingWheelAngleA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DrivingWheelAngleW_dump             Dz1s64W_dump
#define Gitsn_DrivingWheelAngleW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DrivingWheelAngle_dump              Dz1s64W_dump
#define Gitsn_DrivingWheelAngle_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DrivingWheelAngle_dump              Dz1s64A_dump
#define Gitsn_DrivingWheelAngle_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DrivingWheelAngleX_dump(Gitsn_DrivingWheelAngle *p, int tab) { DZ1_DUMP(Gitsn_DrivingWheelAngle, p, tab); }
static __inline__ void Gitsn_DrivingWheelAngleX_fdump(FILE *fp, Gitsn_DrivingWheelAngle *p, int tab) { DZ1_FDUMP(fp, Gitsn_DrivingWheelAngle, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DrivingWheelAngle_dump              Dz1s64A_dump
#define Gitsn_DrivingWheelAngleX_dump Gitsn_DrivingWheelAngleA_dump
#define Gitsn_DrivingWheelAngle_fdump             Dz1s64A_fdump
#define Gitsn_DrivingWheelAngleX_fdump Gitsn_DrivingWheelAngleA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DrivingWheelAngle_cmp               Dz1s64_cmp

// Gitsn_DrivingWheelAngle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VerticalAccelerationThreshold
typedef u8_t Gitsn_VerticalAccelerationThreshold;

#define Gitsn_VerticalAccelerationThreshold_new               Dz1u8_new
#define Gitsn_VerticalAccelerationThreshold_clone             Dz1u8_clone
#define Gitsn_VerticalAccelerationThreshold_del               Dz1u8_del
#define Gitsn_VerticalAccelerationThreshold_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_VerticalAccelerationThresholdA_dump             Dz1u8A_dump
#define Gitsn_VerticalAccelerationThresholdA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VerticalAccelerationThresholdW_dump             Dz1u8W_dump
#define Gitsn_VerticalAccelerationThresholdW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_VerticalAccelerationThreshold_dump              Dz1u8W_dump
#define Gitsn_VerticalAccelerationThreshold_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_VerticalAccelerationThreshold_dump              Dz1u8A_dump
#define Gitsn_VerticalAccelerationThreshold_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VerticalAccelerationThresholdX_dump(Gitsn_VerticalAccelerationThreshold *p, int tab) { DZ1_DUMP(Gitsn_VerticalAccelerationThreshold, p, tab); }
static __inline__ void Gitsn_VerticalAccelerationThresholdX_fdump(FILE *fp, Gitsn_VerticalAccelerationThreshold *p, int tab) { DZ1_FDUMP(fp, Gitsn_VerticalAccelerationThreshold, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VerticalAccelerationThreshold_dump              Dz1u8A_dump
#define Gitsn_VerticalAccelerationThresholdX_dump Gitsn_VerticalAccelerationThresholdA_dump
#define Gitsn_VerticalAccelerationThreshold_fdump             Dz1u8A_fdump
#define Gitsn_VerticalAccelerationThresholdX_fdump Gitsn_VerticalAccelerationThresholdA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VerticalAccelerationThreshold_cmp               Dz1u8_cmp

// Gitsn_VerticalAccelerationThreshold
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObstacleDistance
typedef s64_t Gitsn_ObstacleDistance;

#define Gitsn_ObstacleDistance_new               Dz1s64_new
#define Gitsn_ObstacleDistance_clone             Dz1s64_clone
#define Gitsn_ObstacleDistance_del               Dz1s64_del
#define Gitsn_ObstacleDistance_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ObstacleDistanceA_dump             Dz1s64A_dump
#define Gitsn_ObstacleDistanceA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ObstacleDistanceW_dump             Dz1s64W_dump
#define Gitsn_ObstacleDistanceW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ObstacleDistance_dump              Dz1s64W_dump
#define Gitsn_ObstacleDistance_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ObstacleDistance_dump              Dz1s64A_dump
#define Gitsn_ObstacleDistance_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ObstacleDistanceX_dump(Gitsn_ObstacleDistance *p, int tab) { DZ1_DUMP(Gitsn_ObstacleDistance, p, tab); }
static __inline__ void Gitsn_ObstacleDistanceX_fdump(FILE *fp, Gitsn_ObstacleDistance *p, int tab) { DZ1_FDUMP(fp, Gitsn_ObstacleDistance, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ObstacleDistance_dump              Dz1s64A_dump
#define Gitsn_ObstacleDistanceX_dump Gitsn_ObstacleDistanceA_dump
#define Gitsn_ObstacleDistance_fdump             Dz1s64A_fdump
#define Gitsn_ObstacleDistanceX_fdump Gitsn_ObstacleDistanceA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ObstacleDistance_cmp               Dz1s64_cmp

// Gitsn_ObstacleDistance
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ThrottlePosition
typedef s64_t Gitsn_ThrottlePosition;

#define Gitsn_ThrottlePosition_new               Dz1s64_new
#define Gitsn_ThrottlePosition_clone             Dz1s64_clone
#define Gitsn_ThrottlePosition_del               Dz1s64_del
#define Gitsn_ThrottlePosition_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ThrottlePositionA_dump             Dz1s64A_dump
#define Gitsn_ThrottlePositionA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ThrottlePositionW_dump             Dz1s64W_dump
#define Gitsn_ThrottlePositionW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ThrottlePosition_dump              Dz1s64W_dump
#define Gitsn_ThrottlePosition_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ThrottlePosition_dump              Dz1s64A_dump
#define Gitsn_ThrottlePosition_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ThrottlePositionX_dump(Gitsn_ThrottlePosition *p, int tab) { DZ1_DUMP(Gitsn_ThrottlePosition, p, tab); }
static __inline__ void Gitsn_ThrottlePositionX_fdump(FILE *fp, Gitsn_ThrottlePosition *p, int tab) { DZ1_FDUMP(fp, Gitsn_ThrottlePosition, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ThrottlePosition_dump              Dz1s64A_dump
#define Gitsn_ThrottlePositionX_dump Gitsn_ThrottlePositionA_dump
#define Gitsn_ThrottlePosition_fdump             Dz1s64A_fdump
#define Gitsn_ThrottlePositionX_fdump Gitsn_ThrottlePositionA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ThrottlePosition_cmp               Dz1s64_cmp

// Gitsn_ThrottlePosition
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleMass
typedef s64_t Gitsn_VehicleMass;

#define Gitsn_VehicleMass_new               Dz1s64_new
#define Gitsn_VehicleMass_clone             Dz1s64_clone
#define Gitsn_VehicleMass_del               Dz1s64_del
#define Gitsn_VehicleMass_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_VehicleMassA_dump             Dz1s64A_dump
#define Gitsn_VehicleMassA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VehicleMassW_dump             Dz1s64W_dump
#define Gitsn_VehicleMassW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_VehicleMass_dump              Dz1s64W_dump
#define Gitsn_VehicleMass_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_VehicleMass_dump              Dz1s64A_dump
#define Gitsn_VehicleMass_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VehicleMassX_dump(Gitsn_VehicleMass *p, int tab) { DZ1_DUMP(Gitsn_VehicleMass, p, tab); }
static __inline__ void Gitsn_VehicleMassX_fdump(FILE *fp, Gitsn_VehicleMass *p, int tab) { DZ1_FDUMP(fp, Gitsn_VehicleMass, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VehicleMass_dump              Dz1s64A_dump
#define Gitsn_VehicleMassX_dump Gitsn_VehicleMassA_dump
#define Gitsn_VehicleMass_fdump             Dz1s64A_fdump
#define Gitsn_VehicleMassX_fdump Gitsn_VehicleMassA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VehicleMass_cmp               Dz1s64_cmp

// Gitsn_VehicleMass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrailerWeight
typedef s64_t Gitsn_TrailerWeight;

#define Gitsn_TrailerWeight_new               Dz1s64_new
#define Gitsn_TrailerWeight_clone             Dz1s64_clone
#define Gitsn_TrailerWeight_del               Dz1s64_del
#define Gitsn_TrailerWeight_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TrailerWeightA_dump             Dz1s64A_dump
#define Gitsn_TrailerWeightA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TrailerWeightW_dump             Dz1s64W_dump
#define Gitsn_TrailerWeightW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TrailerWeight_dump              Dz1s64W_dump
#define Gitsn_TrailerWeight_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TrailerWeight_dump              Dz1s64A_dump
#define Gitsn_TrailerWeight_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TrailerWeightX_dump(Gitsn_TrailerWeight *p, int tab) { DZ1_DUMP(Gitsn_TrailerWeight, p, tab); }
static __inline__ void Gitsn_TrailerWeightX_fdump(FILE *fp, Gitsn_TrailerWeight *p, int tab) { DZ1_FDUMP(fp, Gitsn_TrailerWeight, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TrailerWeight_dump              Dz1s64A_dump
#define Gitsn_TrailerWeightX_dump Gitsn_TrailerWeightA_dump
#define Gitsn_TrailerWeight_fdump             Dz1s64A_fdump
#define Gitsn_TrailerWeightX_fdump Gitsn_TrailerWeightA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TrailerWeight_cmp               Dz1s64_cmp

// Gitsn_TrailerWeight
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BumperHeight
typedef s64_t Gitsn_BumperHeight;

#define Gitsn_BumperHeight_new               Dz1s64_new
#define Gitsn_BumperHeight_clone             Dz1s64_clone
#define Gitsn_BumperHeight_del               Dz1s64_del
#define Gitsn_BumperHeight_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_BumperHeightA_dump             Dz1s64A_dump
#define Gitsn_BumperHeightA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_BumperHeightW_dump             Dz1s64W_dump
#define Gitsn_BumperHeightW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_BumperHeight_dump              Dz1s64W_dump
#define Gitsn_BumperHeight_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_BumperHeight_dump              Dz1s64A_dump
#define Gitsn_BumperHeight_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_BumperHeightX_dump(Gitsn_BumperHeight *p, int tab) { DZ1_DUMP(Gitsn_BumperHeight, p, tab); }
static __inline__ void Gitsn_BumperHeightX_fdump(FILE *fp, Gitsn_BumperHeight *p, int tab) { DZ1_FDUMP(fp, Gitsn_BumperHeight, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_BumperHeight_dump              Dz1s64A_dump
#define Gitsn_BumperHeightX_dump Gitsn_BumperHeightA_dump
#define Gitsn_BumperHeight_fdump             Dz1s64A_fdump
#define Gitsn_BumperHeightX_fdump Gitsn_BumperHeightA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_BumperHeight_cmp               Dz1s64_cmp

// Gitsn_BumperHeight
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VINstring
typedef Dz1Str Gitsn_VINstring;

#define Gitsn_VINstring_new               Dz1Str_new
#define Gitsn_VINstring_clone             Dz1Str_clone
#define Gitsn_VINstring_del               Dz1Str_del
#define Gitsn_VINstring_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_VINstringA_dump             Dz1StrA_dump
#define Gitsn_VINstringA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VINstringW_dump             Dz1StrW_dump
#define Gitsn_VINstringW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_VINstring_dump              Dz1StrW_dump
#define Gitsn_VINstring_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_VINstring_dump              Dz1StrA_dump
#define Gitsn_VINstring_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VINstringX_dump(Gitsn_VINstring *p, int tab) { DZ1_DUMP(Gitsn_VINstring, p, tab); }
static __inline__ void Gitsn_VINstringX_fdump(FILE *fp, Gitsn_VINstring *p, int tab) { DZ1_FDUMP(fp, Gitsn_VINstring, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VINstring_dump              Dz1StrA_dump
#define Gitsn_VINstringX_dump Gitsn_VINstringA_dump
#define Gitsn_VINstring_fdump             Dz1StrA_fdump
#define Gitsn_VINstringX_fdump Gitsn_VINstringA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VINstring_cmp               Dz1Str_cmp

// Gitsn_VINstring
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IA5String
typedef Dz1Str Gitsn_IA5String;

#define Gitsn_IA5String_new               Dz1Str_new
#define Gitsn_IA5String_clone             Dz1Str_clone
#define Gitsn_IA5String_del               Dz1Str_del
#define Gitsn_IA5String_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_IA5StringA_dump             Dz1StrA_dump
#define Gitsn_IA5StringA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_IA5StringW_dump             Dz1StrW_dump
#define Gitsn_IA5StringW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_IA5String_dump              Dz1StrW_dump
#define Gitsn_IA5String_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_IA5String_dump              Dz1StrA_dump
#define Gitsn_IA5String_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_IA5StringX_dump(Gitsn_IA5String *p, int tab) { DZ1_DUMP(Gitsn_IA5String, p, tab); }
static __inline__ void Gitsn_IA5StringX_fdump(FILE *fp, Gitsn_IA5String *p, int tab) { DZ1_FDUMP(fp, Gitsn_IA5String, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_IA5String_dump              Dz1StrA_dump
#define Gitsn_IA5StringX_dump Gitsn_IA5StringA_dump
#define Gitsn_IA5String_fdump             Dz1StrA_fdump
#define Gitsn_IA5StringX_fdump Gitsn_IA5StringA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_IA5String_cmp               Dz1Str_cmp

// Gitsn_IA5String
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_StationID
typedef s64_t Gitsn_StationID;

#define Gitsn_StationID_new               Dz1s64_new
#define Gitsn_StationID_clone             Dz1s64_clone
#define Gitsn_StationID_del               Dz1s64_del
#define Gitsn_StationID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_StationIDA_dump             Dz1s64A_dump
#define Gitsn_StationIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_StationIDW_dump             Dz1s64W_dump
#define Gitsn_StationIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_StationID_dump              Dz1s64W_dump
#define Gitsn_StationID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_StationID_dump              Dz1s64A_dump
#define Gitsn_StationID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_StationIDX_dump(Gitsn_StationID *p, int tab) { DZ1_DUMP(Gitsn_StationID, p, tab); }
static __inline__ void Gitsn_StationIDX_fdump(FILE *fp, Gitsn_StationID *p, int tab) { DZ1_FDUMP(fp, Gitsn_StationID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_StationID_dump              Dz1s64A_dump
#define Gitsn_StationIDX_dump Gitsn_StationIDA_dump
#define Gitsn_StationID_fdump             Dz1s64A_fdump
#define Gitsn_StationIDX_fdump Gitsn_StationIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_StationID_cmp               Dz1s64_cmp

// Gitsn_StationID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_CargoWeight
typedef s64_t Gitsn_CargoWeight;

#define Gitsn_CargoWeight_new               Dz1s64_new
#define Gitsn_CargoWeight_clone             Dz1s64_clone
#define Gitsn_CargoWeight_del               Dz1s64_del
#define Gitsn_CargoWeight_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_CargoWeightA_dump             Dz1s64A_dump
#define Gitsn_CargoWeightA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_CargoWeightW_dump             Dz1s64W_dump
#define Gitsn_CargoWeightW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_CargoWeight_dump              Dz1s64W_dump
#define Gitsn_CargoWeight_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_CargoWeight_dump              Dz1s64A_dump
#define Gitsn_CargoWeight_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_CargoWeightX_dump(Gitsn_CargoWeight *p, int tab) { DZ1_DUMP(Gitsn_CargoWeight, p, tab); }
static __inline__ void Gitsn_CargoWeightX_fdump(FILE *fp, Gitsn_CargoWeight *p, int tab) { DZ1_FDUMP(fp, Gitsn_CargoWeight, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_CargoWeight_dump              Dz1s64A_dump
#define Gitsn_CargoWeightX_dump Gitsn_CargoWeightA_dump
#define Gitsn_CargoWeight_fdump             Dz1s64A_fdump
#define Gitsn_CargoWeightX_fdump Gitsn_CargoWeightA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_CargoWeight_cmp               Dz1s64_cmp

// Gitsn_CargoWeight
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SteeringAxleTemperature
typedef s64_t Gitsn_SteeringAxleTemperature;

#define Gitsn_SteeringAxleTemperature_new               Dz1s64_new
#define Gitsn_SteeringAxleTemperature_clone             Dz1s64_clone
#define Gitsn_SteeringAxleTemperature_del               Dz1s64_del
#define Gitsn_SteeringAxleTemperature_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SteeringAxleTemperatureA_dump             Dz1s64A_dump
#define Gitsn_SteeringAxleTemperatureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SteeringAxleTemperatureW_dump             Dz1s64W_dump
#define Gitsn_SteeringAxleTemperatureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SteeringAxleTemperature_dump              Dz1s64W_dump
#define Gitsn_SteeringAxleTemperature_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SteeringAxleTemperature_dump              Dz1s64A_dump
#define Gitsn_SteeringAxleTemperature_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SteeringAxleTemperatureX_dump(Gitsn_SteeringAxleTemperature *p, int tab) { DZ1_DUMP(Gitsn_SteeringAxleTemperature, p, tab); }
static __inline__ void Gitsn_SteeringAxleTemperatureX_fdump(FILE *fp, Gitsn_SteeringAxleTemperature *p, int tab) { DZ1_FDUMP(fp, Gitsn_SteeringAxleTemperature, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SteeringAxleTemperature_dump              Dz1s64A_dump
#define Gitsn_SteeringAxleTemperatureX_dump Gitsn_SteeringAxleTemperatureA_dump
#define Gitsn_SteeringAxleTemperature_fdump             Dz1s64A_fdump
#define Gitsn_SteeringAxleTemperatureX_fdump Gitsn_SteeringAxleTemperatureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SteeringAxleTemperature_cmp               Dz1s64_cmp

// Gitsn_SteeringAxleTemperature
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DriveAxleLocation
typedef s64_t Gitsn_DriveAxleLocation;

#define Gitsn_DriveAxleLocation_new               Dz1s64_new
#define Gitsn_DriveAxleLocation_clone             Dz1s64_clone
#define Gitsn_DriveAxleLocation_del               Dz1s64_del
#define Gitsn_DriveAxleLocation_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DriveAxleLocationA_dump             Dz1s64A_dump
#define Gitsn_DriveAxleLocationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DriveAxleLocationW_dump             Dz1s64W_dump
#define Gitsn_DriveAxleLocationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DriveAxleLocation_dump              Dz1s64W_dump
#define Gitsn_DriveAxleLocation_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DriveAxleLocation_dump              Dz1s64A_dump
#define Gitsn_DriveAxleLocation_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DriveAxleLocationX_dump(Gitsn_DriveAxleLocation *p, int tab) { DZ1_DUMP(Gitsn_DriveAxleLocation, p, tab); }
static __inline__ void Gitsn_DriveAxleLocationX_fdump(FILE *fp, Gitsn_DriveAxleLocation *p, int tab) { DZ1_FDUMP(fp, Gitsn_DriveAxleLocation, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DriveAxleLocation_dump              Dz1s64A_dump
#define Gitsn_DriveAxleLocationX_dump Gitsn_DriveAxleLocationA_dump
#define Gitsn_DriveAxleLocation_fdump             Dz1s64A_fdump
#define Gitsn_DriveAxleLocationX_fdump Gitsn_DriveAxleLocationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DriveAxleLocation_cmp               Dz1s64_cmp

// Gitsn_DriveAxleLocation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DriveAxleLiftAirPressure
typedef s64_t Gitsn_DriveAxleLiftAirPressure;

#define Gitsn_DriveAxleLiftAirPressure_new               Dz1s64_new
#define Gitsn_DriveAxleLiftAirPressure_clone             Dz1s64_clone
#define Gitsn_DriveAxleLiftAirPressure_del               Dz1s64_del
#define Gitsn_DriveAxleLiftAirPressure_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DriveAxleLiftAirPressureA_dump             Dz1s64A_dump
#define Gitsn_DriveAxleLiftAirPressureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DriveAxleLiftAirPressureW_dump             Dz1s64W_dump
#define Gitsn_DriveAxleLiftAirPressureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DriveAxleLiftAirPressure_dump              Dz1s64W_dump
#define Gitsn_DriveAxleLiftAirPressure_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DriveAxleLiftAirPressure_dump              Dz1s64A_dump
#define Gitsn_DriveAxleLiftAirPressure_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DriveAxleLiftAirPressureX_dump(Gitsn_DriveAxleLiftAirPressure *p, int tab) { DZ1_DUMP(Gitsn_DriveAxleLiftAirPressure, p, tab); }
static __inline__ void Gitsn_DriveAxleLiftAirPressureX_fdump(FILE *fp, Gitsn_DriveAxleLiftAirPressure *p, int tab) { DZ1_FDUMP(fp, Gitsn_DriveAxleLiftAirPressure, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DriveAxleLiftAirPressure_dump              Dz1s64A_dump
#define Gitsn_DriveAxleLiftAirPressureX_dump Gitsn_DriveAxleLiftAirPressureA_dump
#define Gitsn_DriveAxleLiftAirPressure_fdump             Dz1s64A_fdump
#define Gitsn_DriveAxleLiftAirPressureX_fdump Gitsn_DriveAxleLiftAirPressureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DriveAxleLiftAirPressure_cmp               Dz1s64_cmp

// Gitsn_DriveAxleLiftAirPressure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DriveAxleTemperature
typedef s64_t Gitsn_DriveAxleTemperature;

#define Gitsn_DriveAxleTemperature_new               Dz1s64_new
#define Gitsn_DriveAxleTemperature_clone             Dz1s64_clone
#define Gitsn_DriveAxleTemperature_del               Dz1s64_del
#define Gitsn_DriveAxleTemperature_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DriveAxleTemperatureA_dump             Dz1s64A_dump
#define Gitsn_DriveAxleTemperatureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DriveAxleTemperatureW_dump             Dz1s64W_dump
#define Gitsn_DriveAxleTemperatureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DriveAxleTemperature_dump              Dz1s64W_dump
#define Gitsn_DriveAxleTemperature_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DriveAxleTemperature_dump              Dz1s64A_dump
#define Gitsn_DriveAxleTemperature_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DriveAxleTemperatureX_dump(Gitsn_DriveAxleTemperature *p, int tab) { DZ1_DUMP(Gitsn_DriveAxleTemperature, p, tab); }
static __inline__ void Gitsn_DriveAxleTemperatureX_fdump(FILE *fp, Gitsn_DriveAxleTemperature *p, int tab) { DZ1_FDUMP(fp, Gitsn_DriveAxleTemperature, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DriveAxleTemperature_dump              Dz1s64A_dump
#define Gitsn_DriveAxleTemperatureX_dump Gitsn_DriveAxleTemperatureA_dump
#define Gitsn_DriveAxleTemperature_fdump             Dz1s64A_fdump
#define Gitsn_DriveAxleTemperatureX_fdump Gitsn_DriveAxleTemperatureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DriveAxleTemperature_cmp               Dz1s64_cmp

// Gitsn_DriveAxleTemperature
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DriveAxleLubePressure
typedef s64_t Gitsn_DriveAxleLubePressure;

#define Gitsn_DriveAxleLubePressure_new               Dz1s64_new
#define Gitsn_DriveAxleLubePressure_clone             Dz1s64_clone
#define Gitsn_DriveAxleLubePressure_del               Dz1s64_del
#define Gitsn_DriveAxleLubePressure_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DriveAxleLubePressureA_dump             Dz1s64A_dump
#define Gitsn_DriveAxleLubePressureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DriveAxleLubePressureW_dump             Dz1s64W_dump
#define Gitsn_DriveAxleLubePressureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DriveAxleLubePressure_dump              Dz1s64W_dump
#define Gitsn_DriveAxleLubePressure_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DriveAxleLubePressure_dump              Dz1s64A_dump
#define Gitsn_DriveAxleLubePressure_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DriveAxleLubePressureX_dump(Gitsn_DriveAxleLubePressure *p, int tab) { DZ1_DUMP(Gitsn_DriveAxleLubePressure, p, tab); }
static __inline__ void Gitsn_DriveAxleLubePressureX_fdump(FILE *fp, Gitsn_DriveAxleLubePressure *p, int tab) { DZ1_FDUMP(fp, Gitsn_DriveAxleLubePressure, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DriveAxleLubePressure_dump              Dz1s64A_dump
#define Gitsn_DriveAxleLubePressureX_dump Gitsn_DriveAxleLubePressureA_dump
#define Gitsn_DriveAxleLubePressure_fdump             Dz1s64A_fdump
#define Gitsn_DriveAxleLubePressureX_fdump Gitsn_DriveAxleLubePressureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DriveAxleLubePressure_cmp               Dz1s64_cmp

// Gitsn_DriveAxleLubePressure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SteeringAxleLubePressure
typedef s64_t Gitsn_SteeringAxleLubePressure;

#define Gitsn_SteeringAxleLubePressure_new               Dz1s64_new
#define Gitsn_SteeringAxleLubePressure_clone             Dz1s64_clone
#define Gitsn_SteeringAxleLubePressure_del               Dz1s64_del
#define Gitsn_SteeringAxleLubePressure_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SteeringAxleLubePressureA_dump             Dz1s64A_dump
#define Gitsn_SteeringAxleLubePressureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SteeringAxleLubePressureW_dump             Dz1s64W_dump
#define Gitsn_SteeringAxleLubePressureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SteeringAxleLubePressure_dump              Dz1s64W_dump
#define Gitsn_SteeringAxleLubePressure_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SteeringAxleLubePressure_dump              Dz1s64A_dump
#define Gitsn_SteeringAxleLubePressure_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SteeringAxleLubePressureX_dump(Gitsn_SteeringAxleLubePressure *p, int tab) { DZ1_DUMP(Gitsn_SteeringAxleLubePressure, p, tab); }
static __inline__ void Gitsn_SteeringAxleLubePressureX_fdump(FILE *fp, Gitsn_SteeringAxleLubePressure *p, int tab) { DZ1_FDUMP(fp, Gitsn_SteeringAxleLubePressure, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SteeringAxleLubePressure_dump              Dz1s64A_dump
#define Gitsn_SteeringAxleLubePressureX_dump Gitsn_SteeringAxleLubePressureA_dump
#define Gitsn_SteeringAxleLubePressure_fdump             Dz1s64A_fdump
#define Gitsn_SteeringAxleLubePressureX_fdump Gitsn_SteeringAxleLubePressureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SteeringAxleLubePressure_cmp               Dz1s64_cmp

// Gitsn_SteeringAxleLubePressure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TireLocation
typedef s64_t Gitsn_TireLocation;

#define Gitsn_TireLocation_new               Dz1s64_new
#define Gitsn_TireLocation_clone             Dz1s64_clone
#define Gitsn_TireLocation_del               Dz1s64_del
#define Gitsn_TireLocation_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TireLocationA_dump             Dz1s64A_dump
#define Gitsn_TireLocationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TireLocationW_dump             Dz1s64W_dump
#define Gitsn_TireLocationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TireLocation_dump              Dz1s64W_dump
#define Gitsn_TireLocation_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TireLocation_dump              Dz1s64A_dump
#define Gitsn_TireLocation_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TireLocationX_dump(Gitsn_TireLocation *p, int tab) { DZ1_DUMP(Gitsn_TireLocation, p, tab); }
static __inline__ void Gitsn_TireLocationX_fdump(FILE *fp, Gitsn_TireLocation *p, int tab) { DZ1_FDUMP(fp, Gitsn_TireLocation, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TireLocation_dump              Dz1s64A_dump
#define Gitsn_TireLocationX_dump Gitsn_TireLocationA_dump
#define Gitsn_TireLocation_fdump             Dz1s64A_fdump
#define Gitsn_TireLocationX_fdump Gitsn_TireLocationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TireLocation_cmp               Dz1s64_cmp

// Gitsn_TireLocation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TirePressure
typedef s64_t Gitsn_TirePressure;

#define Gitsn_TirePressure_new               Dz1s64_new
#define Gitsn_TirePressure_clone             Dz1s64_clone
#define Gitsn_TirePressure_del               Dz1s64_del
#define Gitsn_TirePressure_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TirePressureA_dump             Dz1s64A_dump
#define Gitsn_TirePressureA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TirePressureW_dump             Dz1s64W_dump
#define Gitsn_TirePressureW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TirePressure_dump              Dz1s64W_dump
#define Gitsn_TirePressure_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TirePressure_dump              Dz1s64A_dump
#define Gitsn_TirePressure_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TirePressureX_dump(Gitsn_TirePressure *p, int tab) { DZ1_DUMP(Gitsn_TirePressure, p, tab); }
static __inline__ void Gitsn_TirePressureX_fdump(FILE *fp, Gitsn_TirePressure *p, int tab) { DZ1_FDUMP(fp, Gitsn_TirePressure, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TirePressure_dump              Dz1s64A_dump
#define Gitsn_TirePressureX_dump Gitsn_TirePressureA_dump
#define Gitsn_TirePressure_fdump             Dz1s64A_fdump
#define Gitsn_TirePressureX_fdump Gitsn_TirePressureA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TirePressure_cmp               Dz1s64_cmp

// Gitsn_TirePressure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TireTemp
typedef s64_t Gitsn_TireTemp;

#define Gitsn_TireTemp_new               Dz1s64_new
#define Gitsn_TireTemp_clone             Dz1s64_clone
#define Gitsn_TireTemp_del               Dz1s64_del
#define Gitsn_TireTemp_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TireTempA_dump             Dz1s64A_dump
#define Gitsn_TireTempA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TireTempW_dump             Dz1s64W_dump
#define Gitsn_TireTempW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TireTemp_dump              Dz1s64W_dump
#define Gitsn_TireTemp_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TireTemp_dump              Dz1s64A_dump
#define Gitsn_TireTemp_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TireTempX_dump(Gitsn_TireTemp *p, int tab) { DZ1_DUMP(Gitsn_TireTemp, p, tab); }
static __inline__ void Gitsn_TireTempX_fdump(FILE *fp, Gitsn_TireTemp *p, int tab) { DZ1_FDUMP(fp, Gitsn_TireTemp, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TireTemp_dump              Dz1s64A_dump
#define Gitsn_TireTempX_dump Gitsn_TireTempA_dump
#define Gitsn_TireTemp_fdump             Dz1s64A_fdump
#define Gitsn_TireTempX_fdump Gitsn_TireTempA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TireTemp_cmp               Dz1s64_cmp

// Gitsn_TireTemp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TireLeakageRate
typedef s64_t Gitsn_TireLeakageRate;

#define Gitsn_TireLeakageRate_new               Dz1s64_new
#define Gitsn_TireLeakageRate_clone             Dz1s64_clone
#define Gitsn_TireLeakageRate_del               Dz1s64_del
#define Gitsn_TireLeakageRate_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TireLeakageRateA_dump             Dz1s64A_dump
#define Gitsn_TireLeakageRateA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TireLeakageRateW_dump             Dz1s64W_dump
#define Gitsn_TireLeakageRateW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TireLeakageRate_dump              Dz1s64W_dump
#define Gitsn_TireLeakageRate_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TireLeakageRate_dump              Dz1s64A_dump
#define Gitsn_TireLeakageRate_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TireLeakageRateX_dump(Gitsn_TireLeakageRate *p, int tab) { DZ1_DUMP(Gitsn_TireLeakageRate, p, tab); }
static __inline__ void Gitsn_TireLeakageRateX_fdump(FILE *fp, Gitsn_TireLeakageRate *p, int tab) { DZ1_FDUMP(fp, Gitsn_TireLeakageRate, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TireLeakageRate_dump              Dz1s64A_dump
#define Gitsn_TireLeakageRateX_dump Gitsn_TireLeakageRateA_dump
#define Gitsn_TireLeakageRate_fdump             Dz1s64A_fdump
#define Gitsn_TireLeakageRateX_fdump Gitsn_TireLeakageRateA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TireLeakageRate_cmp               Dz1s64_cmp

// Gitsn_TireLeakageRate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TemporaryID
typedef Dz1Str Gitsn_TemporaryID;

#define Gitsn_TemporaryID_new               Dz1Str_new
#define Gitsn_TemporaryID_clone             Dz1Str_clone
#define Gitsn_TemporaryID_del               Dz1Str_del
#define Gitsn_TemporaryID_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_TemporaryIDA_dump             Dz1StrA_dump
#define Gitsn_TemporaryIDA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TemporaryIDW_dump             Dz1StrW_dump
#define Gitsn_TemporaryIDW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_TemporaryID_dump              Dz1StrW_dump
#define Gitsn_TemporaryID_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_TemporaryID_dump              Dz1StrA_dump
#define Gitsn_TemporaryID_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TemporaryIDX_dump(Gitsn_TemporaryID *p, int tab) { DZ1_DUMP(Gitsn_TemporaryID, p, tab); }
static __inline__ void Gitsn_TemporaryIDX_fdump(FILE *fp, Gitsn_TemporaryID *p, int tab) { DZ1_FDUMP(fp, Gitsn_TemporaryID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TemporaryID_dump              Dz1StrA_dump
#define Gitsn_TemporaryIDX_dump Gitsn_TemporaryIDA_dump
#define Gitsn_TemporaryID_fdump             Dz1StrA_fdump
#define Gitsn_TemporaryIDX_fdump Gitsn_TemporaryIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TemporaryID_cmp               Dz1Str_cmp

// Gitsn_TemporaryID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AxleLocation
typedef s64_t Gitsn_AxleLocation;

#define Gitsn_AxleLocation_new               Dz1s64_new
#define Gitsn_AxleLocation_clone             Dz1s64_clone
#define Gitsn_AxleLocation_del               Dz1s64_del
#define Gitsn_AxleLocation_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_AxleLocationA_dump             Dz1s64A_dump
#define Gitsn_AxleLocationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_AxleLocationW_dump             Dz1s64W_dump
#define Gitsn_AxleLocationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_AxleLocation_dump              Dz1s64W_dump
#define Gitsn_AxleLocation_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_AxleLocation_dump              Dz1s64A_dump
#define Gitsn_AxleLocation_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_AxleLocationX_dump(Gitsn_AxleLocation *p, int tab) { DZ1_DUMP(Gitsn_AxleLocation, p, tab); }
static __inline__ void Gitsn_AxleLocationX_fdump(FILE *fp, Gitsn_AxleLocation *p, int tab) { DZ1_FDUMP(fp, Gitsn_AxleLocation, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_AxleLocation_dump              Dz1s64A_dump
#define Gitsn_AxleLocationX_dump Gitsn_AxleLocationA_dump
#define Gitsn_AxleLocation_fdump             Dz1s64A_fdump
#define Gitsn_AxleLocationX_fdump Gitsn_AxleLocationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_AxleLocation_cmp               Dz1s64_cmp

// Gitsn_AxleLocation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AxleWeight
typedef s64_t Gitsn_AxleWeight;

#define Gitsn_AxleWeight_new               Dz1s64_new
#define Gitsn_AxleWeight_clone             Dz1s64_clone
#define Gitsn_AxleWeight_del               Dz1s64_del
#define Gitsn_AxleWeight_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_AxleWeightA_dump             Dz1s64A_dump
#define Gitsn_AxleWeightA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_AxleWeightW_dump             Dz1s64W_dump
#define Gitsn_AxleWeightW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_AxleWeight_dump              Dz1s64W_dump
#define Gitsn_AxleWeight_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_AxleWeight_dump              Dz1s64A_dump
#define Gitsn_AxleWeight_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_AxleWeightX_dump(Gitsn_AxleWeight *p, int tab) { DZ1_DUMP(Gitsn_AxleWeight, p, tab); }
static __inline__ void Gitsn_AxleWeightX_fdump(FILE *fp, Gitsn_AxleWeight *p, int tab) { DZ1_FDUMP(fp, Gitsn_AxleWeight, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_AxleWeight_dump              Dz1s64A_dump
#define Gitsn_AxleWeightX_dump Gitsn_AxleWeightA_dump
#define Gitsn_AxleWeight_fdump             Dz1s64A_fdump
#define Gitsn_AxleWeightX_fdump Gitsn_AxleWeightA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_AxleWeight_cmp               Dz1s64_cmp

// Gitsn_AxleWeight
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EssPrecipRate
typedef s64_t Gitsn_EssPrecipRate;

#define Gitsn_EssPrecipRate_new               Dz1s64_new
#define Gitsn_EssPrecipRate_clone             Dz1s64_clone
#define Gitsn_EssPrecipRate_del               Dz1s64_del
#define Gitsn_EssPrecipRate_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_EssPrecipRateA_dump             Dz1s64A_dump
#define Gitsn_EssPrecipRateA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_EssPrecipRateW_dump             Dz1s64W_dump
#define Gitsn_EssPrecipRateW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_EssPrecipRate_dump              Dz1s64W_dump
#define Gitsn_EssPrecipRate_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_EssPrecipRate_dump              Dz1s64A_dump
#define Gitsn_EssPrecipRate_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_EssPrecipRateX_dump(Gitsn_EssPrecipRate *p, int tab) { DZ1_DUMP(Gitsn_EssPrecipRate, p, tab); }
static __inline__ void Gitsn_EssPrecipRateX_fdump(FILE *fp, Gitsn_EssPrecipRate *p, int tab) { DZ1_FDUMP(fp, Gitsn_EssPrecipRate, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_EssPrecipRate_dump              Dz1s64A_dump
#define Gitsn_EssPrecipRateX_dump Gitsn_EssPrecipRateA_dump
#define Gitsn_EssPrecipRate_fdump             Dz1s64A_fdump
#define Gitsn_EssPrecipRateX_fdump Gitsn_EssPrecipRateA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_EssPrecipRate_cmp               Dz1s64_cmp

// Gitsn_EssPrecipRate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EssSolarRadiation
typedef s64_t Gitsn_EssSolarRadiation;

#define Gitsn_EssSolarRadiation_new               Dz1s64_new
#define Gitsn_EssSolarRadiation_clone             Dz1s64_clone
#define Gitsn_EssSolarRadiation_del               Dz1s64_del
#define Gitsn_EssSolarRadiation_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_EssSolarRadiationA_dump             Dz1s64A_dump
#define Gitsn_EssSolarRadiationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_EssSolarRadiationW_dump             Dz1s64W_dump
#define Gitsn_EssSolarRadiationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_EssSolarRadiation_dump              Dz1s64W_dump
#define Gitsn_EssSolarRadiation_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_EssSolarRadiation_dump              Dz1s64A_dump
#define Gitsn_EssSolarRadiation_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_EssSolarRadiationX_dump(Gitsn_EssSolarRadiation *p, int tab) { DZ1_DUMP(Gitsn_EssSolarRadiation, p, tab); }
static __inline__ void Gitsn_EssSolarRadiationX_fdump(FILE *fp, Gitsn_EssSolarRadiation *p, int tab) { DZ1_FDUMP(fp, Gitsn_EssSolarRadiation, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_EssSolarRadiation_dump              Dz1s64A_dump
#define Gitsn_EssSolarRadiationX_dump Gitsn_EssSolarRadiationA_dump
#define Gitsn_EssSolarRadiation_fdump             Dz1s64A_fdump
#define Gitsn_EssSolarRadiationX_fdump Gitsn_EssSolarRadiationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_EssSolarRadiation_cmp               Dz1s64_cmp

// Gitsn_EssSolarRadiation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EssMobileFriction
typedef s64_t Gitsn_EssMobileFriction;

#define Gitsn_EssMobileFriction_new               Dz1s64_new
#define Gitsn_EssMobileFriction_clone             Dz1s64_clone
#define Gitsn_EssMobileFriction_del               Dz1s64_del
#define Gitsn_EssMobileFriction_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_EssMobileFrictionA_dump             Dz1s64A_dump
#define Gitsn_EssMobileFrictionA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_EssMobileFrictionW_dump             Dz1s64W_dump
#define Gitsn_EssMobileFrictionW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_EssMobileFriction_dump              Dz1s64W_dump
#define Gitsn_EssMobileFriction_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_EssMobileFriction_dump              Dz1s64A_dump
#define Gitsn_EssMobileFriction_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_EssMobileFrictionX_dump(Gitsn_EssMobileFriction *p, int tab) { DZ1_DUMP(Gitsn_EssMobileFriction, p, tab); }
static __inline__ void Gitsn_EssMobileFrictionX_fdump(FILE *fp, Gitsn_EssMobileFriction *p, int tab) { DZ1_FDUMP(fp, Gitsn_EssMobileFriction, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_EssMobileFriction_dump              Dz1s64A_dump
#define Gitsn_EssMobileFrictionX_dump Gitsn_EssMobileFrictionA_dump
#define Gitsn_EssMobileFriction_fdump             Dz1s64A_fdump
#define Gitsn_EssMobileFrictionX_fdump Gitsn_EssMobileFrictionA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_EssMobileFriction_cmp               Dz1s64_cmp

// Gitsn_EssMobileFriction
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ProbeSegmentNumber
typedef s64_t Gitsn_ProbeSegmentNumber;

#define Gitsn_ProbeSegmentNumber_new               Dz1s64_new
#define Gitsn_ProbeSegmentNumber_clone             Dz1s64_clone
#define Gitsn_ProbeSegmentNumber_del               Dz1s64_del
#define Gitsn_ProbeSegmentNumber_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ProbeSegmentNumberA_dump             Dz1s64A_dump
#define Gitsn_ProbeSegmentNumberA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ProbeSegmentNumberW_dump             Dz1s64W_dump
#define Gitsn_ProbeSegmentNumberW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ProbeSegmentNumber_dump              Dz1s64W_dump
#define Gitsn_ProbeSegmentNumber_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ProbeSegmentNumber_dump              Dz1s64A_dump
#define Gitsn_ProbeSegmentNumber_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ProbeSegmentNumberX_dump(Gitsn_ProbeSegmentNumber *p, int tab) { DZ1_DUMP(Gitsn_ProbeSegmentNumber, p, tab); }
static __inline__ void Gitsn_ProbeSegmentNumberX_fdump(FILE *fp, Gitsn_ProbeSegmentNumber *p, int tab) { DZ1_FDUMP(fp, Gitsn_ProbeSegmentNumber, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ProbeSegmentNumber_dump              Dz1s64A_dump
#define Gitsn_ProbeSegmentNumberX_dump Gitsn_ProbeSegmentNumberA_dump
#define Gitsn_ProbeSegmentNumber_fdump             Dz1s64A_fdump
#define Gitsn_ProbeSegmentNumberX_fdump Gitsn_ProbeSegmentNumberA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ProbeSegmentNumber_cmp               Dz1s64_cmp

// Gitsn_ProbeSegmentNumber
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionStatusObject
typedef u8_t Gitsn_IntersectionStatusObject;

#define Gitsn_IntersectionStatusObject_new               Dz1u8_new
#define Gitsn_IntersectionStatusObject_clone             Dz1u8_clone
#define Gitsn_IntersectionStatusObject_del               Dz1u8_del
#define Gitsn_IntersectionStatusObject_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_IntersectionStatusObjectA_dump             Dz1u8A_dump
#define Gitsn_IntersectionStatusObjectA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_IntersectionStatusObjectW_dump             Dz1u8W_dump
#define Gitsn_IntersectionStatusObjectW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_IntersectionStatusObject_dump              Dz1u8W_dump
#define Gitsn_IntersectionStatusObject_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_IntersectionStatusObject_dump              Dz1u8A_dump
#define Gitsn_IntersectionStatusObject_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_IntersectionStatusObjectX_dump(Gitsn_IntersectionStatusObject *p, int tab) { DZ1_DUMP(Gitsn_IntersectionStatusObject, p, tab); }
static __inline__ void Gitsn_IntersectionStatusObjectX_fdump(FILE *fp, Gitsn_IntersectionStatusObject *p, int tab) { DZ1_FDUMP(fp, Gitsn_IntersectionStatusObject, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_IntersectionStatusObject_dump              Dz1u8A_dump
#define Gitsn_IntersectionStatusObjectX_dump Gitsn_IntersectionStatusObjectA_dump
#define Gitsn_IntersectionStatusObject_fdump             Dz1u8A_fdump
#define Gitsn_IntersectionStatusObjectX_fdump Gitsn_IntersectionStatusObjectA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_IntersectionStatusObject_cmp               Dz1u8_cmp

// Gitsn_IntersectionStatusObject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeIntervalConfidence
typedef s64_t Gitsn_TimeIntervalConfidence;

#define Gitsn_TimeIntervalConfidence_new               Dz1s64_new
#define Gitsn_TimeIntervalConfidence_clone             Dz1s64_clone
#define Gitsn_TimeIntervalConfidence_del               Dz1s64_del
#define Gitsn_TimeIntervalConfidence_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TimeIntervalConfidenceA_dump             Dz1s64A_dump
#define Gitsn_TimeIntervalConfidenceA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TimeIntervalConfidenceW_dump             Dz1s64W_dump
#define Gitsn_TimeIntervalConfidenceW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TimeIntervalConfidence_dump              Dz1s64W_dump
#define Gitsn_TimeIntervalConfidence_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TimeIntervalConfidence_dump              Dz1s64A_dump
#define Gitsn_TimeIntervalConfidence_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TimeIntervalConfidenceX_dump(Gitsn_TimeIntervalConfidence *p, int tab) { DZ1_DUMP(Gitsn_TimeIntervalConfidence, p, tab); }
static __inline__ void Gitsn_TimeIntervalConfidenceX_fdump(FILE *fp, Gitsn_TimeIntervalConfidence *p, int tab) { DZ1_FDUMP(fp, Gitsn_TimeIntervalConfidence, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TimeIntervalConfidence_dump              Dz1s64A_dump
#define Gitsn_TimeIntervalConfidenceX_dump Gitsn_TimeIntervalConfidenceA_dump
#define Gitsn_TimeIntervalConfidence_fdump             Dz1s64A_fdump
#define Gitsn_TimeIntervalConfidenceX_fdump Gitsn_TimeIntervalConfidenceA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TimeIntervalConfidence_cmp               Dz1s64_cmp

// Gitsn_TimeIntervalConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedAdvice
typedef s64_t Gitsn_SpeedAdvice;

#define Gitsn_SpeedAdvice_new               Dz1s64_new
#define Gitsn_SpeedAdvice_clone             Dz1s64_clone
#define Gitsn_SpeedAdvice_del               Dz1s64_del
#define Gitsn_SpeedAdvice_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SpeedAdviceA_dump             Dz1s64A_dump
#define Gitsn_SpeedAdviceA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SpeedAdviceW_dump             Dz1s64W_dump
#define Gitsn_SpeedAdviceW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SpeedAdvice_dump              Dz1s64W_dump
#define Gitsn_SpeedAdvice_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SpeedAdvice_dump              Dz1s64A_dump
#define Gitsn_SpeedAdvice_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SpeedAdviceX_dump(Gitsn_SpeedAdvice *p, int tab) { DZ1_DUMP(Gitsn_SpeedAdvice, p, tab); }
static __inline__ void Gitsn_SpeedAdviceX_fdump(FILE *fp, Gitsn_SpeedAdvice *p, int tab) { DZ1_FDUMP(fp, Gitsn_SpeedAdvice, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SpeedAdvice_dump              Dz1s64A_dump
#define Gitsn_SpeedAdviceX_dump Gitsn_SpeedAdviceA_dump
#define Gitsn_SpeedAdvice_fdump             Dz1s64A_fdump
#define Gitsn_SpeedAdviceX_fdump Gitsn_SpeedAdviceA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SpeedAdvice_cmp               Dz1s64_cmp

// Gitsn_SpeedAdvice
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ZoneLength
typedef s64_t Gitsn_ZoneLength;

#define Gitsn_ZoneLength_new               Dz1s64_new
#define Gitsn_ZoneLength_clone             Dz1s64_clone
#define Gitsn_ZoneLength_del               Dz1s64_del
#define Gitsn_ZoneLength_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ZoneLengthA_dump             Dz1s64A_dump
#define Gitsn_ZoneLengthA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ZoneLengthW_dump             Dz1s64W_dump
#define Gitsn_ZoneLengthW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ZoneLength_dump              Dz1s64W_dump
#define Gitsn_ZoneLength_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ZoneLength_dump              Dz1s64A_dump
#define Gitsn_ZoneLength_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ZoneLengthX_dump(Gitsn_ZoneLength *p, int tab) { DZ1_DUMP(Gitsn_ZoneLength, p, tab); }
static __inline__ void Gitsn_ZoneLengthX_fdump(FILE *fp, Gitsn_ZoneLength *p, int tab) { DZ1_FDUMP(fp, Gitsn_ZoneLength, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ZoneLength_dump              Dz1s64A_dump
#define Gitsn_ZoneLengthX_dump Gitsn_ZoneLengthA_dump
#define Gitsn_ZoneLength_fdump             Dz1s64A_fdump
#define Gitsn_ZoneLengthX_fdump Gitsn_ZoneLengthA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ZoneLength_cmp               Dz1s64_cmp

// Gitsn_ZoneLength
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WaitOnStopline
typedef bool_t Gitsn_WaitOnStopline;

#define Gitsn_WaitOnStopline_new               Dz1Bool_new
#define Gitsn_WaitOnStopline_clone             Dz1Bool_clone
#define Gitsn_WaitOnStopline_del               Dz1Bool_del
#define Gitsn_WaitOnStopline_delAndSetNull     Dz1Bool_delAndSetNull
#define Gitsn_WaitOnStoplineA_dump             Dz1BoolA_dump
#define Gitsn_WaitOnStoplineA_fdump            Dz1BoolA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_WaitOnStoplineW_dump             Dz1BoolW_dump
#define Gitsn_WaitOnStoplineW_fdump            Dz1BoolW_fdump
#ifdef UNICODE
#define Gitsn_WaitOnStopline_dump              Dz1BoolW_dump
#define Gitsn_WaitOnStopline_fdump             Dz1BoolW_fdump
#else //  UNICODE
#define Gitsn_WaitOnStopline_dump              Dz1BoolA_dump
#define Gitsn_WaitOnStopline_fdump             Dz1BoolA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_WaitOnStoplineX_dump(Gitsn_WaitOnStopline *p, int tab) { DZ1_DUMP(Gitsn_WaitOnStopline, p, tab); }
static __inline__ void Gitsn_WaitOnStoplineX_fdump(FILE *fp, Gitsn_WaitOnStopline *p, int tab) { DZ1_FDUMP(fp, Gitsn_WaitOnStopline, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_WaitOnStopline_dump              Dz1BoolA_dump
#define Gitsn_WaitOnStoplineX_dump Gitsn_WaitOnStoplineA_dump
#define Gitsn_WaitOnStopline_fdump             Dz1BoolA_fdump
#define Gitsn_WaitOnStoplineX_fdump Gitsn_WaitOnStoplineA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_WaitOnStopline_cmp               Dz1Bool_cmp

// Gitsn_WaitOnStopline
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PedestrianBicycleDetect
typedef bool_t Gitsn_PedestrianBicycleDetect;

#define Gitsn_PedestrianBicycleDetect_new               Dz1Bool_new
#define Gitsn_PedestrianBicycleDetect_clone             Dz1Bool_clone
#define Gitsn_PedestrianBicycleDetect_del               Dz1Bool_del
#define Gitsn_PedestrianBicycleDetect_delAndSetNull     Dz1Bool_delAndSetNull
#define Gitsn_PedestrianBicycleDetectA_dump             Dz1BoolA_dump
#define Gitsn_PedestrianBicycleDetectA_fdump            Dz1BoolA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PedestrianBicycleDetectW_dump             Dz1BoolW_dump
#define Gitsn_PedestrianBicycleDetectW_fdump            Dz1BoolW_fdump
#ifdef UNICODE
#define Gitsn_PedestrianBicycleDetect_dump              Dz1BoolW_dump
#define Gitsn_PedestrianBicycleDetect_fdump             Dz1BoolW_fdump
#else //  UNICODE
#define Gitsn_PedestrianBicycleDetect_dump              Dz1BoolA_dump
#define Gitsn_PedestrianBicycleDetect_fdump             Dz1BoolA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PedestrianBicycleDetectX_dump(Gitsn_PedestrianBicycleDetect *p, int tab) { DZ1_DUMP(Gitsn_PedestrianBicycleDetect, p, tab); }
static __inline__ void Gitsn_PedestrianBicycleDetectX_fdump(FILE *fp, Gitsn_PedestrianBicycleDetect *p, int tab) { DZ1_FDUMP(fp, Gitsn_PedestrianBicycleDetect, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PedestrianBicycleDetect_dump              Dz1BoolA_dump
#define Gitsn_PedestrianBicycleDetectX_dump Gitsn_PedestrianBicycleDetectA_dump
#define Gitsn_PedestrianBicycleDetect_fdump             Dz1BoolA_fdump
#define Gitsn_PedestrianBicycleDetectX_fdump Gitsn_PedestrianBicycleDetectA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PedestrianBicycleDetect_cmp               Dz1Bool_cmp

// Gitsn_PedestrianBicycleDetect
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ClassificationConfidence
typedef s64_t Gitsn_ClassificationConfidence;

#define Gitsn_ClassificationConfidence_new               Dz1s64_new
#define Gitsn_ClassificationConfidence_clone             Dz1s64_clone
#define Gitsn_ClassificationConfidence_del               Dz1s64_del
#define Gitsn_ClassificationConfidence_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ClassificationConfidenceA_dump             Dz1s64A_dump
#define Gitsn_ClassificationConfidenceA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ClassificationConfidenceW_dump             Dz1s64W_dump
#define Gitsn_ClassificationConfidenceW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ClassificationConfidence_dump              Dz1s64W_dump
#define Gitsn_ClassificationConfidence_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ClassificationConfidence_dump              Dz1s64A_dump
#define Gitsn_ClassificationConfidence_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ClassificationConfidenceX_dump(Gitsn_ClassificationConfidence *p, int tab) { DZ1_DUMP(Gitsn_ClassificationConfidence, p, tab); }
static __inline__ void Gitsn_ClassificationConfidenceX_fdump(FILE *fp, Gitsn_ClassificationConfidence *p, int tab) { DZ1_FDUMP(fp, Gitsn_ClassificationConfidence, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ClassificationConfidence_dump              Dz1s64A_dump
#define Gitsn_ClassificationConfidenceX_dump Gitsn_ClassificationConfidenceA_dump
#define Gitsn_ClassificationConfidence_fdump             Dz1s64A_fdump
#define Gitsn_ClassificationConfidenceX_fdump Gitsn_ClassificationConfidenceA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ClassificationConfidence_cmp               Dz1s64_cmp

// Gitsn_ClassificationConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObjectID
typedef s64_t Gitsn_ObjectID;

#define Gitsn_ObjectID_new               Dz1s64_new
#define Gitsn_ObjectID_clone             Dz1s64_clone
#define Gitsn_ObjectID_del               Dz1s64_del
#define Gitsn_ObjectID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ObjectIDA_dump             Dz1s64A_dump
#define Gitsn_ObjectIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ObjectIDW_dump             Dz1s64W_dump
#define Gitsn_ObjectIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ObjectID_dump              Dz1s64W_dump
#define Gitsn_ObjectID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ObjectID_dump              Dz1s64A_dump
#define Gitsn_ObjectID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ObjectIDX_dump(Gitsn_ObjectID *p, int tab) { DZ1_DUMP(Gitsn_ObjectID, p, tab); }
static __inline__ void Gitsn_ObjectIDX_fdump(FILE *fp, Gitsn_ObjectID *p, int tab) { DZ1_FDUMP(fp, Gitsn_ObjectID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ObjectID_dump              Dz1s64A_dump
#define Gitsn_ObjectIDX_dump Gitsn_ObjectIDA_dump
#define Gitsn_ObjectID_fdump             Dz1s64A_fdump
#define Gitsn_ObjectIDX_fdump Gitsn_ObjectIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ObjectID_cmp               Dz1s64_cmp

// Gitsn_ObjectID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MeasurementTimeOffset
typedef s64_t Gitsn_MeasurementTimeOffset;

#define Gitsn_MeasurementTimeOffset_new               Dz1s64_new
#define Gitsn_MeasurementTimeOffset_clone             Dz1s64_clone
#define Gitsn_MeasurementTimeOffset_del               Dz1s64_del
#define Gitsn_MeasurementTimeOffset_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_MeasurementTimeOffsetA_dump             Dz1s64A_dump
#define Gitsn_MeasurementTimeOffsetA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_MeasurementTimeOffsetW_dump             Dz1s64W_dump
#define Gitsn_MeasurementTimeOffsetW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_MeasurementTimeOffset_dump              Dz1s64W_dump
#define Gitsn_MeasurementTimeOffset_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_MeasurementTimeOffset_dump              Dz1s64A_dump
#define Gitsn_MeasurementTimeOffset_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_MeasurementTimeOffsetX_dump(Gitsn_MeasurementTimeOffset *p, int tab) { DZ1_DUMP(Gitsn_MeasurementTimeOffset, p, tab); }
static __inline__ void Gitsn_MeasurementTimeOffsetX_fdump(FILE *fp, Gitsn_MeasurementTimeOffset *p, int tab) { DZ1_FDUMP(fp, Gitsn_MeasurementTimeOffset, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_MeasurementTimeOffset_dump              Dz1s64A_dump
#define Gitsn_MeasurementTimeOffsetX_dump Gitsn_MeasurementTimeOffsetA_dump
#define Gitsn_MeasurementTimeOffset_fdump             Dz1s64A_fdump
#define Gitsn_MeasurementTimeOffsetX_fdump Gitsn_MeasurementTimeOffsetA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_MeasurementTimeOffset_cmp               Dz1s64_cmp

// Gitsn_MeasurementTimeOffset
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PitchDetected
typedef s64_t Gitsn_PitchDetected;

#define Gitsn_PitchDetected_new               Dz1s64_new
#define Gitsn_PitchDetected_clone             Dz1s64_clone
#define Gitsn_PitchDetected_del               Dz1s64_del
#define Gitsn_PitchDetected_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_PitchDetectedA_dump             Dz1s64A_dump
#define Gitsn_PitchDetectedA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PitchDetectedW_dump             Dz1s64W_dump
#define Gitsn_PitchDetectedW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_PitchDetected_dump              Dz1s64W_dump
#define Gitsn_PitchDetected_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_PitchDetected_dump              Dz1s64A_dump
#define Gitsn_PitchDetected_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PitchDetectedX_dump(Gitsn_PitchDetected *p, int tab) { DZ1_DUMP(Gitsn_PitchDetected, p, tab); }
static __inline__ void Gitsn_PitchDetectedX_fdump(FILE *fp, Gitsn_PitchDetected *p, int tab) { DZ1_FDUMP(fp, Gitsn_PitchDetected, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PitchDetected_dump              Dz1s64A_dump
#define Gitsn_PitchDetectedX_dump Gitsn_PitchDetectedA_dump
#define Gitsn_PitchDetected_fdump             Dz1s64A_fdump
#define Gitsn_PitchDetectedX_fdump Gitsn_PitchDetectedA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PitchDetected_cmp               Dz1s64_cmp

// Gitsn_PitchDetected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RollDetected
typedef s64_t Gitsn_RollDetected;

#define Gitsn_RollDetected_new               Dz1s64_new
#define Gitsn_RollDetected_clone             Dz1s64_clone
#define Gitsn_RollDetected_del               Dz1s64_del
#define Gitsn_RollDetected_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_RollDetectedA_dump             Dz1s64A_dump
#define Gitsn_RollDetectedA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RollDetectedW_dump             Dz1s64W_dump
#define Gitsn_RollDetectedW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_RollDetected_dump              Dz1s64W_dump
#define Gitsn_RollDetected_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_RollDetected_dump              Dz1s64A_dump
#define Gitsn_RollDetected_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RollDetectedX_dump(Gitsn_RollDetected *p, int tab) { DZ1_DUMP(Gitsn_RollDetected, p, tab); }
static __inline__ void Gitsn_RollDetectedX_fdump(FILE *fp, Gitsn_RollDetected *p, int tab) { DZ1_FDUMP(fp, Gitsn_RollDetected, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RollDetected_dump              Dz1s64A_dump
#define Gitsn_RollDetectedX_dump Gitsn_RollDetectedA_dump
#define Gitsn_RollDetected_fdump             Dz1s64A_fdump
#define Gitsn_RollDetectedX_fdump Gitsn_RollDetectedA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RollDetected_cmp               Dz1s64_cmp

// Gitsn_RollDetected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_YawDetected
typedef s64_t Gitsn_YawDetected;

#define Gitsn_YawDetected_new               Dz1s64_new
#define Gitsn_YawDetected_clone             Dz1s64_clone
#define Gitsn_YawDetected_del               Dz1s64_del
#define Gitsn_YawDetected_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_YawDetectedA_dump             Dz1s64A_dump
#define Gitsn_YawDetectedA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_YawDetectedW_dump             Dz1s64W_dump
#define Gitsn_YawDetectedW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_YawDetected_dump              Dz1s64W_dump
#define Gitsn_YawDetected_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_YawDetected_dump              Dz1s64A_dump
#define Gitsn_YawDetected_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_YawDetectedX_dump(Gitsn_YawDetected *p, int tab) { DZ1_DUMP(Gitsn_YawDetected, p, tab); }
static __inline__ void Gitsn_YawDetectedX_fdump(FILE *fp, Gitsn_YawDetected *p, int tab) { DZ1_FDUMP(fp, Gitsn_YawDetected, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_YawDetected_dump              Dz1s64A_dump
#define Gitsn_YawDetectedX_dump Gitsn_YawDetectedA_dump
#define Gitsn_YawDetected_fdump             Dz1s64A_fdump
#define Gitsn_YawDetectedX_fdump Gitsn_YawDetectedA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_YawDetected_cmp               Dz1s64_cmp

// Gitsn_YawDetected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PitchRate
typedef s64_t Gitsn_PitchRate;

#define Gitsn_PitchRate_new               Dz1s64_new
#define Gitsn_PitchRate_clone             Dz1s64_clone
#define Gitsn_PitchRate_del               Dz1s64_del
#define Gitsn_PitchRate_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_PitchRateA_dump             Dz1s64A_dump
#define Gitsn_PitchRateA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PitchRateW_dump             Dz1s64W_dump
#define Gitsn_PitchRateW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_PitchRate_dump              Dz1s64W_dump
#define Gitsn_PitchRate_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_PitchRate_dump              Dz1s64A_dump
#define Gitsn_PitchRate_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PitchRateX_dump(Gitsn_PitchRate *p, int tab) { DZ1_DUMP(Gitsn_PitchRate, p, tab); }
static __inline__ void Gitsn_PitchRateX_fdump(FILE *fp, Gitsn_PitchRate *p, int tab) { DZ1_FDUMP(fp, Gitsn_PitchRate, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PitchRate_dump              Dz1s64A_dump
#define Gitsn_PitchRateX_dump Gitsn_PitchRateA_dump
#define Gitsn_PitchRate_fdump             Dz1s64A_fdump
#define Gitsn_PitchRateX_fdump Gitsn_PitchRateA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PitchRate_cmp               Dz1s64_cmp

// Gitsn_PitchRate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RollRate
typedef s64_t Gitsn_RollRate;

#define Gitsn_RollRate_new               Dz1s64_new
#define Gitsn_RollRate_clone             Dz1s64_clone
#define Gitsn_RollRate_del               Dz1s64_del
#define Gitsn_RollRate_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_RollRateA_dump             Dz1s64A_dump
#define Gitsn_RollRateA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RollRateW_dump             Dz1s64W_dump
#define Gitsn_RollRateW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_RollRate_dump              Dz1s64W_dump
#define Gitsn_RollRate_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_RollRate_dump              Dz1s64A_dump
#define Gitsn_RollRate_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RollRateX_dump(Gitsn_RollRate *p, int tab) { DZ1_DUMP(Gitsn_RollRate, p, tab); }
static __inline__ void Gitsn_RollRateX_fdump(FILE *fp, Gitsn_RollRate *p, int tab) { DZ1_FDUMP(fp, Gitsn_RollRate, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RollRate_dump              Dz1s64A_dump
#define Gitsn_RollRateX_dump Gitsn_RollRateA_dump
#define Gitsn_RollRate_fdump             Dz1s64A_fdump
#define Gitsn_RollRateX_fdump Gitsn_RollRateA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RollRate_cmp               Dz1s64_cmp

// Gitsn_RollRate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AttachmentRadius
typedef s64_t Gitsn_AttachmentRadius;

#define Gitsn_AttachmentRadius_new               Dz1s64_new
#define Gitsn_AttachmentRadius_clone             Dz1s64_clone
#define Gitsn_AttachmentRadius_del               Dz1s64_del
#define Gitsn_AttachmentRadius_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_AttachmentRadiusA_dump             Dz1s64A_dump
#define Gitsn_AttachmentRadiusA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_AttachmentRadiusW_dump             Dz1s64W_dump
#define Gitsn_AttachmentRadiusW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_AttachmentRadius_dump              Dz1s64W_dump
#define Gitsn_AttachmentRadius_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_AttachmentRadius_dump              Dz1s64A_dump
#define Gitsn_AttachmentRadius_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_AttachmentRadiusX_dump(Gitsn_AttachmentRadius *p, int tab) { DZ1_DUMP(Gitsn_AttachmentRadius, p, tab); }
static __inline__ void Gitsn_AttachmentRadiusX_fdump(FILE *fp, Gitsn_AttachmentRadius *p, int tab) { DZ1_FDUMP(fp, Gitsn_AttachmentRadius, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_AttachmentRadius_dump              Dz1s64A_dump
#define Gitsn_AttachmentRadiusX_dump Gitsn_AttachmentRadiusA_dump
#define Gitsn_AttachmentRadius_fdump             Dz1s64A_fdump
#define Gitsn_AttachmentRadiusX_fdump Gitsn_AttachmentRadiusA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_AttachmentRadius_cmp               Dz1s64_cmp

// Gitsn_AttachmentRadius
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SizeValue
typedef s64_t Gitsn_SizeValue;

#define Gitsn_SizeValue_new               Dz1s64_new
#define Gitsn_SizeValue_clone             Dz1s64_clone
#define Gitsn_SizeValue_del               Dz1s64_del
#define Gitsn_SizeValue_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SizeValueA_dump             Dz1s64A_dump
#define Gitsn_SizeValueA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SizeValueW_dump             Dz1s64W_dump
#define Gitsn_SizeValueW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SizeValue_dump              Dz1s64W_dump
#define Gitsn_SizeValue_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SizeValue_dump              Dz1s64A_dump
#define Gitsn_SizeValue_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SizeValueX_dump(Gitsn_SizeValue *p, int tab) { DZ1_DUMP(Gitsn_SizeValue, p, tab); }
static __inline__ void Gitsn_SizeValueX_fdump(FILE *fp, Gitsn_SizeValue *p, int tab) { DZ1_FDUMP(fp, Gitsn_SizeValue, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SizeValue_dump              Dz1s64A_dump
#define Gitsn_SizeValueX_dump Gitsn_SizeValueA_dump
#define Gitsn_SizeValue_fdump             Dz1s64A_fdump
#define Gitsn_SizeValueX_fdump Gitsn_SizeValueA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SizeValue_cmp               Dz1s64_cmp

// Gitsn_SizeValue
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIScodes
typedef s64_t Gitsn_ITIScodes;

#define Gitsn_ITIScodes_new               Dz1s64_new
#define Gitsn_ITIScodes_clone             Dz1s64_clone
#define Gitsn_ITIScodes_del               Dz1s64_del
#define Gitsn_ITIScodes_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ITIScodesA_dump             Dz1s64A_dump
#define Gitsn_ITIScodesA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ITIScodesW_dump             Dz1s64W_dump
#define Gitsn_ITIScodesW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_ITIScodes_dump              Dz1s64W_dump
#define Gitsn_ITIScodes_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_ITIScodes_dump              Dz1s64A_dump
#define Gitsn_ITIScodes_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ITIScodesX_dump(Gitsn_ITIScodes *p, int tab) { DZ1_DUMP(Gitsn_ITIScodes, p, tab); }
static __inline__ void Gitsn_ITIScodesX_fdump(FILE *fp, Gitsn_ITIScodes *p, int tab) { DZ1_FDUMP(fp, Gitsn_ITIScodes, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ITIScodes_dump              Dz1s64A_dump
#define Gitsn_ITIScodesX_dump Gitsn_ITIScodesA_dump
#define Gitsn_ITIScodes_fdump             Dz1s64A_fdump
#define Gitsn_ITIScodesX_fdump Gitsn_ITIScodesA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ITIScodes_cmp               Dz1s64_cmp

// Gitsn_ITIScodes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Priority
typedef Dz1Str Gitsn_Priority;

#define Gitsn_Priority_new               Dz1Str_new
#define Gitsn_Priority_clone             Dz1Str_clone
#define Gitsn_Priority_del               Dz1Str_del
#define Gitsn_Priority_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_PriorityA_dump             Dz1StrA_dump
#define Gitsn_PriorityA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PriorityW_dump             Dz1StrW_dump
#define Gitsn_PriorityW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_Priority_dump              Dz1StrW_dump
#define Gitsn_Priority_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_Priority_dump              Dz1StrA_dump
#define Gitsn_Priority_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PriorityX_dump(Gitsn_Priority *p, int tab) { DZ1_DUMP(Gitsn_Priority, p, tab); }
static __inline__ void Gitsn_PriorityX_fdump(FILE *fp, Gitsn_Priority *p, int tab) { DZ1_FDUMP(fp, Gitsn_Priority, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Priority_dump              Dz1StrA_dump
#define Gitsn_PriorityX_dump Gitsn_PriorityA_dump
#define Gitsn_Priority_fdump             Dz1StrA_fdump
#define Gitsn_PriorityX_fdump Gitsn_PriorityA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Priority_cmp               Dz1Str_cmp

// Gitsn_Priority
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_HeadingSlice
typedef u8_t Gitsn_HeadingSlice;

#define Gitsn_HeadingSlice_new               Dz1u8_new
#define Gitsn_HeadingSlice_clone             Dz1u8_clone
#define Gitsn_HeadingSlice_del               Dz1u8_del
#define Gitsn_HeadingSlice_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_HeadingSliceA_dump             Dz1u8A_dump
#define Gitsn_HeadingSliceA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_HeadingSliceW_dump             Dz1u8W_dump
#define Gitsn_HeadingSliceW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_HeadingSlice_dump              Dz1u8W_dump
#define Gitsn_HeadingSlice_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_HeadingSlice_dump              Dz1u8A_dump
#define Gitsn_HeadingSlice_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_HeadingSliceX_dump(Gitsn_HeadingSlice *p, int tab) { DZ1_DUMP(Gitsn_HeadingSlice, p, tab); }
static __inline__ void Gitsn_HeadingSliceX_fdump(FILE *fp, Gitsn_HeadingSlice *p, int tab) { DZ1_FDUMP(fp, Gitsn_HeadingSlice, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_HeadingSlice_dump              Dz1u8A_dump
#define Gitsn_HeadingSliceX_dump Gitsn_HeadingSliceA_dump
#define Gitsn_HeadingSlice_fdump             Dz1u8A_fdump
#define Gitsn_HeadingSliceX_fdump Gitsn_HeadingSliceA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_HeadingSlice_cmp               Dz1u8_cmp

// Gitsn_HeadingSlice
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_FurtherInfoID
typedef u16_t Gitsn_FurtherInfoID;

#define Gitsn_FurtherInfoID_new               Dz1u16_new
#define Gitsn_FurtherInfoID_clone             Dz1u16_clone
#define Gitsn_FurtherInfoID_del               Dz1u16_del
#define Gitsn_FurtherInfoID_delAndSetNull     Dz1u16_delAndSetNull
#define Gitsn_FurtherInfoIDA_dump             Dz1u16A_dump
#define Gitsn_FurtherInfoIDA_fdump            Dz1u16A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_FurtherInfoIDW_dump             Dz1u16W_dump
#define Gitsn_FurtherInfoIDW_fdump            Dz1u16W_fdump
#ifdef UNICODE
#define Gitsn_FurtherInfoID_dump              Dz1u16W_dump
#define Gitsn_FurtherInfoID_fdump             Dz1u16W_fdump
#else //  UNICODE
#define Gitsn_FurtherInfoID_dump              Dz1u16A_dump
#define Gitsn_FurtherInfoID_fdump             Dz1u16A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_FurtherInfoIDX_dump(Gitsn_FurtherInfoID *p, int tab) { DZ1_DUMP(Gitsn_FurtherInfoID, p, tab); }
static __inline__ void Gitsn_FurtherInfoIDX_fdump(FILE *fp, Gitsn_FurtherInfoID *p, int tab) { DZ1_FDUMP(fp, Gitsn_FurtherInfoID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_FurtherInfoID_dump              Dz1u16A_dump
#define Gitsn_FurtherInfoIDX_dump Gitsn_FurtherInfoIDA_dump
#define Gitsn_FurtherInfoID_fdump             Dz1u16A_fdump
#define Gitsn_FurtherInfoIDX_fdump Gitsn_FurtherInfoIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_FurtherInfoID_cmp               Dz1u16_cmp

// Gitsn_FurtherInfoID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_UniqueMSGID
typedef Dz1Str Gitsn_UniqueMSGID;

#define Gitsn_UniqueMSGID_new               Dz1Str_new
#define Gitsn_UniqueMSGID_clone             Dz1Str_clone
#define Gitsn_UniqueMSGID_del               Dz1Str_del
#define Gitsn_UniqueMSGID_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_UniqueMSGIDA_dump             Dz1StrA_dump
#define Gitsn_UniqueMSGIDA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_UniqueMSGIDW_dump             Dz1StrW_dump
#define Gitsn_UniqueMSGIDW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_UniqueMSGID_dump              Dz1StrW_dump
#define Gitsn_UniqueMSGID_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_UniqueMSGID_dump              Dz1StrA_dump
#define Gitsn_UniqueMSGID_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_UniqueMSGIDX_dump(Gitsn_UniqueMSGID *p, int tab) { DZ1_DUMP(Gitsn_UniqueMSGID, p, tab); }
static __inline__ void Gitsn_UniqueMSGIDX_fdump(FILE *fp, Gitsn_UniqueMSGID *p, int tab) { DZ1_FDUMP(fp, Gitsn_UniqueMSGID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_UniqueMSGID_dump              Dz1StrA_dump
#define Gitsn_UniqueMSGIDX_dump Gitsn_UniqueMSGIDA_dump
#define Gitsn_UniqueMSGID_fdump             Dz1StrA_fdump
#define Gitsn_UniqueMSGIDX_fdump Gitsn_UniqueMSGIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_UniqueMSGID_cmp               Dz1Str_cmp

// Gitsn_UniqueMSGID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_URL_Base
typedef Dz1Str Gitsn_URL_Base;

#define Gitsn_URL_Base_new               Dz1Str_new
#define Gitsn_URL_Base_clone             Dz1Str_clone
#define Gitsn_URL_Base_del               Dz1Str_del
#define Gitsn_URL_Base_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_URL_BaseA_dump             Dz1StrA_dump
#define Gitsn_URL_BaseA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_URL_BaseW_dump             Dz1StrW_dump
#define Gitsn_URL_BaseW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_URL_Base_dump              Dz1StrW_dump
#define Gitsn_URL_Base_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_URL_Base_dump              Dz1StrA_dump
#define Gitsn_URL_Base_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_URL_BaseX_dump(Gitsn_URL_Base *p, int tab) { DZ1_DUMP(Gitsn_URL_Base, p, tab); }
static __inline__ void Gitsn_URL_BaseX_fdump(FILE *fp, Gitsn_URL_Base *p, int tab) { DZ1_FDUMP(fp, Gitsn_URL_Base, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_URL_Base_dump              Dz1StrA_dump
#define Gitsn_URL_BaseX_dump Gitsn_URL_BaseA_dump
#define Gitsn_URL_Base_fdump             Dz1StrA_fdump
#define Gitsn_URL_BaseX_fdump Gitsn_URL_BaseA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_URL_Base_cmp               Dz1Str_cmp

// Gitsn_URL_Base
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_URL_Short
typedef Dz1Str Gitsn_URL_Short;

#define Gitsn_URL_Short_new               Dz1Str_new
#define Gitsn_URL_Short_clone             Dz1Str_clone
#define Gitsn_URL_Short_del               Dz1Str_del
#define Gitsn_URL_Short_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_URL_ShortA_dump             Dz1StrA_dump
#define Gitsn_URL_ShortA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_URL_ShortW_dump             Dz1StrW_dump
#define Gitsn_URL_ShortW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_URL_Short_dump              Dz1StrW_dump
#define Gitsn_URL_Short_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_URL_Short_dump              Dz1StrA_dump
#define Gitsn_URL_Short_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_URL_ShortX_dump(Gitsn_URL_Short *p, int tab) { DZ1_DUMP(Gitsn_URL_Short, p, tab); }
static __inline__ void Gitsn_URL_ShortX_fdump(FILE *fp, Gitsn_URL_Short *p, int tab) { DZ1_FDUMP(fp, Gitsn_URL_Short, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_URL_Short_dump              Dz1StrA_dump
#define Gitsn_URL_ShortX_dump Gitsn_URL_ShortA_dump
#define Gitsn_URL_Short_fdump             Dz1StrA_fdump
#define Gitsn_URL_ShortX_fdump Gitsn_URL_ShortA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_URL_Short_cmp               Dz1Str_cmp

// Gitsn_URL_Short
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SSPindex
typedef s64_t Gitsn_SSPindex;

#define Gitsn_SSPindex_new               Dz1s64_new
#define Gitsn_SSPindex_clone             Dz1s64_clone
#define Gitsn_SSPindex_del               Dz1s64_del
#define Gitsn_SSPindex_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SSPindexA_dump             Dz1s64A_dump
#define Gitsn_SSPindexA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SSPindexW_dump             Dz1s64W_dump
#define Gitsn_SSPindexW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SSPindex_dump              Dz1s64W_dump
#define Gitsn_SSPindex_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SSPindex_dump              Dz1s64A_dump
#define Gitsn_SSPindex_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SSPindexX_dump(Gitsn_SSPindex *p, int tab) { DZ1_DUMP(Gitsn_SSPindex, p, tab); }
static __inline__ void Gitsn_SSPindexX_fdump(FILE *fp, Gitsn_SSPindex *p, int tab) { DZ1_FDUMP(fp, Gitsn_SSPindex, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SSPindex_dump              Dz1s64A_dump
#define Gitsn_SSPindexX_dump Gitsn_SSPindexA_dump
#define Gitsn_SSPindex_fdump             Dz1s64A_fdump
#define Gitsn_SSPindexX_fdump Gitsn_SSPindexA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SSPindex_cmp               Dz1s64_cmp

// Gitsn_SSPindex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MsgCRC
typedef Dz1Str Gitsn_MsgCRC;

#define Gitsn_MsgCRC_new               Dz1Str_new
#define Gitsn_MsgCRC_clone             Dz1Str_clone
#define Gitsn_MsgCRC_del               Dz1Str_del
#define Gitsn_MsgCRC_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_MsgCRCA_dump             Dz1StrA_dump
#define Gitsn_MsgCRCA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_MsgCRCW_dump             Dz1StrW_dump
#define Gitsn_MsgCRCW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_MsgCRC_dump              Dz1StrW_dump
#define Gitsn_MsgCRC_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_MsgCRC_dump              Dz1StrA_dump
#define Gitsn_MsgCRC_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_MsgCRCX_dump(Gitsn_MsgCRC *p, int tab) { DZ1_DUMP(Gitsn_MsgCRC, p, tab); }
static __inline__ void Gitsn_MsgCRCX_fdump(FILE *fp, Gitsn_MsgCRC *p, int tab) { DZ1_FDUMP(fp, Gitsn_MsgCRC, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_MsgCRC_dump              Dz1StrA_dump
#define Gitsn_MsgCRCX_dump Gitsn_MsgCRCA_dump
#define Gitsn_MsgCRC_fdump             Dz1StrA_fdump
#define Gitsn_MsgCRCX_fdump Gitsn_MsgCRCA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_MsgCRC_cmp               Dz1Str_cmp

// Gitsn_MsgCRC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MinutesDuration
typedef s64_t Gitsn_MinutesDuration;

#define Gitsn_MinutesDuration_new               Dz1s64_new
#define Gitsn_MinutesDuration_clone             Dz1s64_clone
#define Gitsn_MinutesDuration_del               Dz1s64_del
#define Gitsn_MinutesDuration_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_MinutesDurationA_dump             Dz1s64A_dump
#define Gitsn_MinutesDurationA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_MinutesDurationW_dump             Dz1s64W_dump
#define Gitsn_MinutesDurationW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_MinutesDuration_dump              Dz1s64W_dump
#define Gitsn_MinutesDuration_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_MinutesDuration_dump              Dz1s64A_dump
#define Gitsn_MinutesDuration_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_MinutesDurationX_dump(Gitsn_MinutesDuration *p, int tab) { DZ1_DUMP(Gitsn_MinutesDuration, p, tab); }
static __inline__ void Gitsn_MinutesDurationX_fdump(FILE *fp, Gitsn_MinutesDuration *p, int tab) { DZ1_FDUMP(fp, Gitsn_MinutesDuration, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_MinutesDuration_dump              Dz1s64A_dump
#define Gitsn_MinutesDurationX_dump Gitsn_MinutesDurationA_dump
#define Gitsn_MinutesDuration_fdump             Dz1s64A_fdump
#define Gitsn_MinutesDurationX_fdump Gitsn_MinutesDurationA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_MinutesDuration_cmp               Dz1s64_cmp

// Gitsn_MinutesDuration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignPriority
typedef s64_t Gitsn_SignPriority;

#define Gitsn_SignPriority_new               Dz1s64_new
#define Gitsn_SignPriority_clone             Dz1s64_clone
#define Gitsn_SignPriority_del               Dz1s64_del
#define Gitsn_SignPriority_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_SignPriorityA_dump             Dz1s64A_dump
#define Gitsn_SignPriorityA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_SignPriorityW_dump             Dz1s64W_dump
#define Gitsn_SignPriorityW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_SignPriority_dump              Dz1s64W_dump
#define Gitsn_SignPriority_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_SignPriority_dump              Dz1s64A_dump
#define Gitsn_SignPriority_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_SignPriorityX_dump(Gitsn_SignPriority *p, int tab) { DZ1_DUMP(Gitsn_SignPriority, p, tab); }
static __inline__ void Gitsn_SignPriorityX_fdump(FILE *fp, Gitsn_SignPriority *p, int tab) { DZ1_FDUMP(fp, Gitsn_SignPriority, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_SignPriority_dump              Dz1s64A_dump
#define Gitsn_SignPriorityX_dump Gitsn_SignPriorityA_dump
#define Gitsn_SignPriority_fdump             Dz1s64A_fdump
#define Gitsn_SignPriorityX_fdump Gitsn_SignPriorityA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_SignPriority_cmp               Dz1s64_cmp

// Gitsn_SignPriority
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Zoom
typedef s64_t Gitsn_Zoom;

#define Gitsn_Zoom_new               Dz1s64_new
#define Gitsn_Zoom_clone             Dz1s64_clone
#define Gitsn_Zoom_del               Dz1s64_del
#define Gitsn_Zoom_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_ZoomA_dump             Dz1s64A_dump
#define Gitsn_ZoomA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ZoomW_dump             Dz1s64W_dump
#define Gitsn_ZoomW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Zoom_dump              Dz1s64W_dump
#define Gitsn_Zoom_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Zoom_dump              Dz1s64A_dump
#define Gitsn_Zoom_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ZoomX_dump(Gitsn_Zoom *p, int tab) { DZ1_DUMP(Gitsn_Zoom, p, tab); }
static __inline__ void Gitsn_ZoomX_fdump(FILE *fp, Gitsn_Zoom *p, int tab) { DZ1_FDUMP(fp, Gitsn_Zoom, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Zoom_dump              Dz1s64A_dump
#define Gitsn_ZoomX_dump Gitsn_ZoomA_dump
#define Gitsn_Zoom_fdump             Dz1s64A_fdump
#define Gitsn_ZoomX_fdump Gitsn_ZoomA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Zoom_cmp               Dz1s64_cmp

// Gitsn_Zoom
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Radius_B12
typedef s64_t Gitsn_Radius_B12;

#define Gitsn_Radius_B12_new               Dz1s64_new
#define Gitsn_Radius_B12_clone             Dz1s64_clone
#define Gitsn_Radius_B12_del               Dz1s64_del
#define Gitsn_Radius_B12_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_Radius_B12A_dump             Dz1s64A_dump
#define Gitsn_Radius_B12A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_Radius_B12W_dump             Dz1s64W_dump
#define Gitsn_Radius_B12W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_Radius_B12_dump              Dz1s64W_dump
#define Gitsn_Radius_B12_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_Radius_B12_dump              Dz1s64A_dump
#define Gitsn_Radius_B12_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_Radius_B12X_dump(Gitsn_Radius_B12 *p, int tab) { DZ1_DUMP(Gitsn_Radius_B12, p, tab); }
static __inline__ void Gitsn_Radius_B12X_fdump(FILE *fp, Gitsn_Radius_B12 *p, int tab) { DZ1_FDUMP(fp, Gitsn_Radius_B12, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_Radius_B12_dump              Dz1s64A_dump
#define Gitsn_Radius_B12X_dump Gitsn_Radius_B12A_dump
#define Gitsn_Radius_B12_fdump             Dz1s64A_fdump
#define Gitsn_Radius_B12X_fdump Gitsn_Radius_B12A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_Radius_B12_cmp               Dz1s64_cmp

// Gitsn_Radius_B12
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIStext
typedef Dz1Str Gitsn_ITIStext;

#define Gitsn_ITIStext_new               Dz1Str_new
#define Gitsn_ITIStext_clone             Dz1Str_clone
#define Gitsn_ITIStext_del               Dz1Str_del
#define Gitsn_ITIStext_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_ITIStextA_dump             Dz1StrA_dump
#define Gitsn_ITIStextA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ITIStextW_dump             Dz1StrW_dump
#define Gitsn_ITIStextW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_ITIStext_dump              Dz1StrW_dump
#define Gitsn_ITIStext_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_ITIStext_dump              Dz1StrA_dump
#define Gitsn_ITIStext_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ITIStextX_dump(Gitsn_ITIStext *p, int tab) { DZ1_DUMP(Gitsn_ITIStext, p, tab); }
static __inline__ void Gitsn_ITIStextX_fdump(FILE *fp, Gitsn_ITIStext *p, int tab) { DZ1_FDUMP(fp, Gitsn_ITIStext, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ITIStext_dump              Dz1StrA_dump
#define Gitsn_ITIStextX_dump Gitsn_ITIStextA_dump
#define Gitsn_ITIStext_fdump             Dz1StrA_fdump
#define Gitsn_ITIStextX_fdump Gitsn_ITIStextA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ITIStext_cmp               Dz1Str_cmp

// Gitsn_ITIStext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_INTEGER
typedef s64_t Gitsn_INTEGER;

#define Gitsn_INTEGER_new               Dz1s64_new
#define Gitsn_INTEGER_clone             Dz1s64_clone
#define Gitsn_INTEGER_del               Dz1s64_del
#define Gitsn_INTEGER_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_INTEGERA_dump             Dz1s64A_dump
#define Gitsn_INTEGERA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_INTEGERW_dump             Dz1s64W_dump
#define Gitsn_INTEGERW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_INTEGER_dump              Dz1s64W_dump
#define Gitsn_INTEGER_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_INTEGER_dump              Dz1s64A_dump
#define Gitsn_INTEGER_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_INTEGERX_dump(Gitsn_INTEGER *p, int tab) { DZ1_DUMP(Gitsn_INTEGER, p, tab); }
static __inline__ void Gitsn_INTEGERX_fdump(FILE *fp, Gitsn_INTEGER *p, int tab) { DZ1_FDUMP(fp, Gitsn_INTEGER, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_INTEGER_dump              Dz1s64A_dump
#define Gitsn_INTEGERX_dump Gitsn_INTEGERA_dump
#define Gitsn_INTEGER_fdump             Dz1s64A_fdump
#define Gitsn_INTEGERX_fdump Gitsn_INTEGERA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_INTEGER_cmp               Dz1s64_cmp

// Gitsn_INTEGER
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightOperationStatus
typedef u8_t Gitsn_TrafficLightOperationStatus;

#define Gitsn_TrafficLightOperationStatus_new               Dz1u8_new
#define Gitsn_TrafficLightOperationStatus_clone             Dz1u8_clone
#define Gitsn_TrafficLightOperationStatus_del               Dz1u8_del
#define Gitsn_TrafficLightOperationStatus_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_TrafficLightOperationStatusA_dump             Dz1u8A_dump
#define Gitsn_TrafficLightOperationStatusA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TrafficLightOperationStatusW_dump             Dz1u8W_dump
#define Gitsn_TrafficLightOperationStatusW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_TrafficLightOperationStatus_dump              Dz1u8W_dump
#define Gitsn_TrafficLightOperationStatus_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_TrafficLightOperationStatus_dump              Dz1u8A_dump
#define Gitsn_TrafficLightOperationStatus_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TrafficLightOperationStatusX_dump(Gitsn_TrafficLightOperationStatus *p, int tab) { DZ1_DUMP(Gitsn_TrafficLightOperationStatus, p, tab); }
static __inline__ void Gitsn_TrafficLightOperationStatusX_fdump(FILE *fp, Gitsn_TrafficLightOperationStatus *p, int tab) { DZ1_FDUMP(fp, Gitsn_TrafficLightOperationStatus, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TrafficLightOperationStatus_dump              Dz1u8A_dump
#define Gitsn_TrafficLightOperationStatusX_dump Gitsn_TrafficLightOperationStatusA_dump
#define Gitsn_TrafficLightOperationStatus_fdump             Dz1u8A_fdump
#define Gitsn_TrafficLightOperationStatusX_fdump Gitsn_TrafficLightOperationStatusA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TrafficLightOperationStatus_cmp               Dz1u8_cmp

// Gitsn_TrafficLightOperationStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightControllerStatus
typedef u8_t Gitsn_TrafficLightControllerStatus;

#define Gitsn_TrafficLightControllerStatus_new               Dz1u8_new
#define Gitsn_TrafficLightControllerStatus_clone             Dz1u8_clone
#define Gitsn_TrafficLightControllerStatus_del               Dz1u8_del
#define Gitsn_TrafficLightControllerStatus_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_TrafficLightControllerStatusA_dump             Dz1u8A_dump
#define Gitsn_TrafficLightControllerStatusA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TrafficLightControllerStatusW_dump             Dz1u8W_dump
#define Gitsn_TrafficLightControllerStatusW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_TrafficLightControllerStatus_dump              Dz1u8W_dump
#define Gitsn_TrafficLightControllerStatus_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_TrafficLightControllerStatus_dump              Dz1u8A_dump
#define Gitsn_TrafficLightControllerStatus_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TrafficLightControllerStatusX_dump(Gitsn_TrafficLightControllerStatus *p, int tab) { DZ1_DUMP(Gitsn_TrafficLightControllerStatus, p, tab); }
static __inline__ void Gitsn_TrafficLightControllerStatusX_fdump(FILE *fp, Gitsn_TrafficLightControllerStatus *p, int tab) { DZ1_FDUMP(fp, Gitsn_TrafficLightControllerStatus, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TrafficLightControllerStatus_dump              Dz1u8A_dump
#define Gitsn_TrafficLightControllerStatusX_dump Gitsn_TrafficLightControllerStatusA_dump
#define Gitsn_TrafficLightControllerStatus_fdump             Dz1u8A_fdump
#define Gitsn_TrafficLightControllerStatusX_fdump Gitsn_TrafficLightControllerStatusA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TrafficLightControllerStatus_cmp               Dz1u8_cmp

// Gitsn_TrafficLightControllerStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeInSecond_B16
typedef s64_t Gitsn_TimeInSecond_B16;

#define Gitsn_TimeInSecond_B16_new               Dz1s64_new
#define Gitsn_TimeInSecond_B16_clone             Dz1s64_clone
#define Gitsn_TimeInSecond_B16_del               Dz1s64_del
#define Gitsn_TimeInSecond_B16_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TimeInSecond_B16A_dump             Dz1s64A_dump
#define Gitsn_TimeInSecond_B16A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TimeInSecond_B16W_dump             Dz1s64W_dump
#define Gitsn_TimeInSecond_B16W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TimeInSecond_B16_dump              Dz1s64W_dump
#define Gitsn_TimeInSecond_B16_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TimeInSecond_B16_dump              Dz1s64A_dump
#define Gitsn_TimeInSecond_B16_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TimeInSecond_B16X_dump(Gitsn_TimeInSecond_B16 *p, int tab) { DZ1_DUMP(Gitsn_TimeInSecond_B16, p, tab); }
static __inline__ void Gitsn_TimeInSecond_B16X_fdump(FILE *fp, Gitsn_TimeInSecond_B16 *p, int tab) { DZ1_FDUMP(fp, Gitsn_TimeInSecond_B16, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TimeInSecond_B16_dump              Dz1s64A_dump
#define Gitsn_TimeInSecond_B16X_dump Gitsn_TimeInSecond_B16A_dump
#define Gitsn_TimeInSecond_B16_fdump             Dz1s64A_fdump
#define Gitsn_TimeInSecond_B16X_fdump Gitsn_TimeInSecond_B16A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TimeInSecond_B16_cmp               Dz1s64_cmp

// Gitsn_TimeInSecond_B16
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeInSecond_B8
typedef s64_t Gitsn_TimeInSecond_B8;

#define Gitsn_TimeInSecond_B8_new               Dz1s64_new
#define Gitsn_TimeInSecond_B8_clone             Dz1s64_clone
#define Gitsn_TimeInSecond_B8_del               Dz1s64_del
#define Gitsn_TimeInSecond_B8_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TimeInSecond_B8A_dump             Dz1s64A_dump
#define Gitsn_TimeInSecond_B8A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TimeInSecond_B8W_dump             Dz1s64W_dump
#define Gitsn_TimeInSecond_B8W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TimeInSecond_B8_dump              Dz1s64W_dump
#define Gitsn_TimeInSecond_B8_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TimeInSecond_B8_dump              Dz1s64A_dump
#define Gitsn_TimeInSecond_B8_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TimeInSecond_B8X_dump(Gitsn_TimeInSecond_B8 *p, int tab) { DZ1_DUMP(Gitsn_TimeInSecond_B8, p, tab); }
static __inline__ void Gitsn_TimeInSecond_B8X_fdump(FILE *fp, Gitsn_TimeInSecond_B8 *p, int tab) { DZ1_FDUMP(fp, Gitsn_TimeInSecond_B8, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TimeInSecond_B8_dump              Dz1s64A_dump
#define Gitsn_TimeInSecond_B8X_dump Gitsn_TimeInSecond_B8A_dump
#define Gitsn_TimeInSecond_B8_fdump             Dz1s64A_fdump
#define Gitsn_TimeInSecond_B8X_fdump Gitsn_TimeInSecond_B8A_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TimeInSecond_B8_cmp               Dz1s64_cmp

// Gitsn_TimeInSecond_B8
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PedestrianCall
typedef bool_t Gitsn_PedestrianCall;

#define Gitsn_PedestrianCall_new               Dz1Bool_new
#define Gitsn_PedestrianCall_clone             Dz1Bool_clone
#define Gitsn_PedestrianCall_del               Dz1Bool_del
#define Gitsn_PedestrianCall_delAndSetNull     Dz1Bool_delAndSetNull
#define Gitsn_PedestrianCallA_dump             Dz1BoolA_dump
#define Gitsn_PedestrianCallA_fdump            Dz1BoolA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PedestrianCallW_dump             Dz1BoolW_dump
#define Gitsn_PedestrianCallW_fdump            Dz1BoolW_fdump
#ifdef UNICODE
#define Gitsn_PedestrianCall_dump              Dz1BoolW_dump
#define Gitsn_PedestrianCall_fdump             Dz1BoolW_fdump
#else //  UNICODE
#define Gitsn_PedestrianCall_dump              Dz1BoolA_dump
#define Gitsn_PedestrianCall_fdump             Dz1BoolA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PedestrianCallX_dump(Gitsn_PedestrianCall *p, int tab) { DZ1_DUMP(Gitsn_PedestrianCall, p, tab); }
static __inline__ void Gitsn_PedestrianCallX_fdump(FILE *fp, Gitsn_PedestrianCall *p, int tab) { DZ1_FDUMP(fp, Gitsn_PedestrianCall, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PedestrianCall_dump              Dz1BoolA_dump
#define Gitsn_PedestrianCallX_dump Gitsn_PedestrianCallA_dump
#define Gitsn_PedestrianCall_fdump             Dz1BoolA_fdump
#define Gitsn_PedestrianCallX_fdump Gitsn_PedestrianCallA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PedestrianCall_cmp               Dz1Bool_cmp

// Gitsn_PedestrianCall
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ActuatedInterval
typedef bool_t Gitsn_ActuatedInterval;

#define Gitsn_ActuatedInterval_new               Dz1Bool_new
#define Gitsn_ActuatedInterval_clone             Dz1Bool_clone
#define Gitsn_ActuatedInterval_del               Dz1Bool_del
#define Gitsn_ActuatedInterval_delAndSetNull     Dz1Bool_delAndSetNull
#define Gitsn_ActuatedIntervalA_dump             Dz1BoolA_dump
#define Gitsn_ActuatedIntervalA_fdump            Dz1BoolA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ActuatedIntervalW_dump             Dz1BoolW_dump
#define Gitsn_ActuatedIntervalW_fdump            Dz1BoolW_fdump
#ifdef UNICODE
#define Gitsn_ActuatedInterval_dump              Dz1BoolW_dump
#define Gitsn_ActuatedInterval_fdump             Dz1BoolW_fdump
#else //  UNICODE
#define Gitsn_ActuatedInterval_dump              Dz1BoolA_dump
#define Gitsn_ActuatedInterval_fdump             Dz1BoolA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ActuatedIntervalX_dump(Gitsn_ActuatedInterval *p, int tab) { DZ1_DUMP(Gitsn_ActuatedInterval, p, tab); }
static __inline__ void Gitsn_ActuatedIntervalX_fdump(FILE *fp, Gitsn_ActuatedInterval *p, int tab) { DZ1_FDUMP(fp, Gitsn_ActuatedInterval, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ActuatedInterval_dump              Dz1BoolA_dump
#define Gitsn_ActuatedIntervalX_dump Gitsn_ActuatedIntervalA_dump
#define Gitsn_ActuatedInterval_fdump             Dz1BoolA_fdump
#define Gitsn_ActuatedIntervalX_fdump Gitsn_ActuatedIntervalA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ActuatedInterval_cmp               Dz1Bool_cmp

// Gitsn_ActuatedInterval
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightDirectionCode
typedef s64_t Gitsn_TrafficLightDirectionCode;

#define Gitsn_TrafficLightDirectionCode_new               Dz1s64_new
#define Gitsn_TrafficLightDirectionCode_clone             Dz1s64_clone
#define Gitsn_TrafficLightDirectionCode_del               Dz1s64_del
#define Gitsn_TrafficLightDirectionCode_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TrafficLightDirectionCodeA_dump             Dz1s64A_dump
#define Gitsn_TrafficLightDirectionCodeA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TrafficLightDirectionCodeW_dump             Dz1s64W_dump
#define Gitsn_TrafficLightDirectionCodeW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TrafficLightDirectionCode_dump              Dz1s64W_dump
#define Gitsn_TrafficLightDirectionCode_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TrafficLightDirectionCode_dump              Dz1s64A_dump
#define Gitsn_TrafficLightDirectionCode_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TrafficLightDirectionCodeX_dump(Gitsn_TrafficLightDirectionCode *p, int tab) { DZ1_DUMP(Gitsn_TrafficLightDirectionCode, p, tab); }
static __inline__ void Gitsn_TrafficLightDirectionCodeX_fdump(FILE *fp, Gitsn_TrafficLightDirectionCode *p, int tab) { DZ1_FDUMP(fp, Gitsn_TrafficLightDirectionCode, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TrafficLightDirectionCode_dump              Dz1s64A_dump
#define Gitsn_TrafficLightDirectionCodeX_dump Gitsn_TrafficLightDirectionCodeA_dump
#define Gitsn_TrafficLightDirectionCode_fdump             Dz1s64A_fdump
#define Gitsn_TrafficLightDirectionCodeX_fdump Gitsn_TrafficLightDirectionCodeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TrafficLightDirectionCode_cmp               Dz1s64_cmp

// Gitsn_TrafficLightDirectionCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ReservedBit
typedef bool_t Gitsn_ReservedBit;

#define Gitsn_ReservedBit_new               Dz1Bool_new
#define Gitsn_ReservedBit_clone             Dz1Bool_clone
#define Gitsn_ReservedBit_del               Dz1Bool_del
#define Gitsn_ReservedBit_delAndSetNull     Dz1Bool_delAndSetNull
#define Gitsn_ReservedBitA_dump             Dz1BoolA_dump
#define Gitsn_ReservedBitA_fdump            Dz1BoolA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_ReservedBitW_dump             Dz1BoolW_dump
#define Gitsn_ReservedBitW_fdump            Dz1BoolW_fdump
#ifdef UNICODE
#define Gitsn_ReservedBit_dump              Dz1BoolW_dump
#define Gitsn_ReservedBit_fdump             Dz1BoolW_fdump
#else //  UNICODE
#define Gitsn_ReservedBit_dump              Dz1BoolA_dump
#define Gitsn_ReservedBit_fdump             Dz1BoolA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_ReservedBitX_dump(Gitsn_ReservedBit *p, int tab) { DZ1_DUMP(Gitsn_ReservedBit, p, tab); }
static __inline__ void Gitsn_ReservedBitX_fdump(FILE *fp, Gitsn_ReservedBit *p, int tab) { DZ1_FDUMP(fp, Gitsn_ReservedBit, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_ReservedBit_dump              Dz1BoolA_dump
#define Gitsn_ReservedBitX_dump Gitsn_ReservedBitA_dump
#define Gitsn_ReservedBit_fdump             Dz1BoolA_fdump
#define Gitsn_ReservedBitX_fdump Gitsn_ReservedBitA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_ReservedBit_cmp               Dz1Bool_cmp

// Gitsn_ReservedBit
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightID_KOR
typedef s64_t Gitsn_TrafficLightID_KOR;

#define Gitsn_TrafficLightID_KOR_new               Dz1s64_new
#define Gitsn_TrafficLightID_KOR_clone             Dz1s64_clone
#define Gitsn_TrafficLightID_KOR_del               Dz1s64_del
#define Gitsn_TrafficLightID_KOR_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_TrafficLightID_KORA_dump             Dz1s64A_dump
#define Gitsn_TrafficLightID_KORA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TrafficLightID_KORW_dump             Dz1s64W_dump
#define Gitsn_TrafficLightID_KORW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_TrafficLightID_KOR_dump              Dz1s64W_dump
#define Gitsn_TrafficLightID_KOR_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_TrafficLightID_KOR_dump              Dz1s64A_dump
#define Gitsn_TrafficLightID_KOR_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TrafficLightID_KORX_dump(Gitsn_TrafficLightID_KOR *p, int tab) { DZ1_DUMP(Gitsn_TrafficLightID_KOR, p, tab); }
static __inline__ void Gitsn_TrafficLightID_KORX_fdump(FILE *fp, Gitsn_TrafficLightID_KOR *p, int tab) { DZ1_FDUMP(fp, Gitsn_TrafficLightID_KOR, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TrafficLightID_KOR_dump              Dz1s64A_dump
#define Gitsn_TrafficLightID_KORX_dump Gitsn_TrafficLightID_KORA_dump
#define Gitsn_TrafficLightID_KOR_fdump             Dz1s64A_fdump
#define Gitsn_TrafficLightID_KORX_fdump Gitsn_TrafficLightID_KORA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TrafficLightID_KOR_cmp               Dz1s64_cmp

// Gitsn_TrafficLightID_KOR
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OCTETSTRING
typedef u8_t Gitsn_OCTETSTRING;

#define Gitsn_OCTETSTRING_new               Dz1u8_new
#define Gitsn_OCTETSTRING_clone             Dz1u8_clone
#define Gitsn_OCTETSTRING_del               Dz1u8_del
#define Gitsn_OCTETSTRING_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_OCTETSTRINGA_dump             Dz1u8A_dump
#define Gitsn_OCTETSTRINGA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_OCTETSTRINGW_dump             Dz1u8W_dump
#define Gitsn_OCTETSTRINGW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_OCTETSTRING_dump              Dz1u8W_dump
#define Gitsn_OCTETSTRING_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_OCTETSTRING_dump              Dz1u8A_dump
#define Gitsn_OCTETSTRING_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_OCTETSTRINGX_dump(Gitsn_OCTETSTRING *p, int tab) { DZ1_DUMP(Gitsn_OCTETSTRING, p, tab); }
static __inline__ void Gitsn_OCTETSTRINGX_fdump(FILE *fp, Gitsn_OCTETSTRING *p, int tab) { DZ1_FDUMP(fp, Gitsn_OCTETSTRING, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_OCTETSTRING_dump              Dz1u8A_dump
#define Gitsn_OCTETSTRINGX_dump Gitsn_OCTETSTRINGA_dump
#define Gitsn_OCTETSTRING_fdump             Dz1u8A_fdump
#define Gitsn_OCTETSTRINGX_fdump Gitsn_OCTETSTRINGA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_OCTETSTRING_cmp               Dz1u8_cmp

// Gitsn_OCTETSTRING
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VisibleString
typedef u8_t Gitsn_VisibleString;

#define Gitsn_VisibleString_new               Dz1u8_new
#define Gitsn_VisibleString_clone             Dz1u8_clone
#define Gitsn_VisibleString_del               Dz1u8_del
#define Gitsn_VisibleString_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_VisibleStringA_dump             Dz1u8A_dump
#define Gitsn_VisibleStringA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_VisibleStringW_dump             Dz1u8W_dump
#define Gitsn_VisibleStringW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_VisibleString_dump              Dz1u8W_dump
#define Gitsn_VisibleString_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_VisibleString_dump              Dz1u8A_dump
#define Gitsn_VisibleString_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_VisibleStringX_dump(Gitsn_VisibleString *p, int tab) { DZ1_DUMP(Gitsn_VisibleString, p, tab); }
static __inline__ void Gitsn_VisibleStringX_fdump(FILE *fp, Gitsn_VisibleString *p, int tab) { DZ1_FDUMP(fp, Gitsn_VisibleString, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_VisibleString_dump              Dz1u8A_dump
#define Gitsn_VisibleStringX_dump Gitsn_VisibleStringA_dump
#define Gitsn_VisibleString_fdump             Dz1u8A_fdump
#define Gitsn_VisibleStringX_fdump Gitsn_VisibleStringA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_VisibleString_cmp               Dz1u8_cmp

// Gitsn_VisibleString
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PrivilegedEventFlags
typedef u8_t Gitsn_PrivilegedEventFlags;

#define Gitsn_PrivilegedEventFlags_new               Dz1u8_new
#define Gitsn_PrivilegedEventFlags_clone             Dz1u8_clone
#define Gitsn_PrivilegedEventFlags_del               Dz1u8_del
#define Gitsn_PrivilegedEventFlags_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_PrivilegedEventFlagsA_dump             Dz1u8A_dump
#define Gitsn_PrivilegedEventFlagsA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PrivilegedEventFlagsW_dump             Dz1u8W_dump
#define Gitsn_PrivilegedEventFlagsW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_PrivilegedEventFlags_dump              Dz1u8W_dump
#define Gitsn_PrivilegedEventFlags_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_PrivilegedEventFlags_dump              Dz1u8A_dump
#define Gitsn_PrivilegedEventFlags_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PrivilegedEventFlagsX_dump(Gitsn_PrivilegedEventFlags *p, int tab) { DZ1_DUMP(Gitsn_PrivilegedEventFlags, p, tab); }
static __inline__ void Gitsn_PrivilegedEventFlagsX_fdump(FILE *fp, Gitsn_PrivilegedEventFlags *p, int tab) { DZ1_FDUMP(fp, Gitsn_PrivilegedEventFlags, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PrivilegedEventFlags_dump              Dz1u8A_dump
#define Gitsn_PrivilegedEventFlagsX_dump Gitsn_PrivilegedEventFlagsA_dump
#define Gitsn_PrivilegedEventFlags_fdump             Dz1u8A_fdump
#define Gitsn_PrivilegedEventFlagsX_fdump Gitsn_PrivilegedEventFlagsA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PrivilegedEventFlags_cmp               Dz1u8_cmp

// Gitsn_PrivilegedEventFlags
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RTCMmessage
typedef Dz1Str Gitsn_RTCMmessage;

#define Gitsn_RTCMmessage_new               Dz1Str_new
#define Gitsn_RTCMmessage_clone             Dz1Str_clone
#define Gitsn_RTCMmessage_del               Dz1Str_del
#define Gitsn_RTCMmessage_delAndSetNull     Dz1Str_delAndSetNull
#define Gitsn_RTCMmessageA_dump             Dz1StrA_dump
#define Gitsn_RTCMmessageA_fdump            Dz1StrA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RTCMmessageW_dump             Dz1StrW_dump
#define Gitsn_RTCMmessageW_fdump            Dz1StrW_fdump
#ifdef UNICODE
#define Gitsn_RTCMmessage_dump              Dz1StrW_dump
#define Gitsn_RTCMmessage_fdump             Dz1StrW_fdump
#else //  UNICODE
#define Gitsn_RTCMmessage_dump              Dz1StrA_dump
#define Gitsn_RTCMmessage_fdump             Dz1StrA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RTCMmessageX_dump(Gitsn_RTCMmessage *p, int tab) { DZ1_DUMP(Gitsn_RTCMmessage, p, tab); }
static __inline__ void Gitsn_RTCMmessageX_fdump(FILE *fp, Gitsn_RTCMmessage *p, int tab) { DZ1_FDUMP(fp, Gitsn_RTCMmessage, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RTCMmessage_dump              Dz1StrA_dump
#define Gitsn_RTCMmessageX_dump Gitsn_RTCMmessageA_dump
#define Gitsn_RTCMmessage_fdump             Dz1StrA_fdump
#define Gitsn_RTCMmessageX_fdump Gitsn_RTCMmessageA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RTCMmessage_cmp               Dz1Str_cmp

// Gitsn_RTCMmessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RequestID
typedef s64_t Gitsn_RequestID;

#define Gitsn_RequestID_new               Dz1s64_new
#define Gitsn_RequestID_clone             Dz1s64_clone
#define Gitsn_RequestID_del               Dz1s64_del
#define Gitsn_RequestID_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_RequestIDA_dump             Dz1s64A_dump
#define Gitsn_RequestIDA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_RequestIDW_dump             Dz1s64W_dump
#define Gitsn_RequestIDW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_RequestID_dump              Dz1s64W_dump
#define Gitsn_RequestID_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_RequestID_dump              Dz1s64A_dump
#define Gitsn_RequestID_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RequestIDX_dump(Gitsn_RequestID *p, int tab) { DZ1_DUMP(Gitsn_RequestID, p, tab); }
static __inline__ void Gitsn_RequestIDX_fdump(FILE *fp, Gitsn_RequestID *p, int tab) { DZ1_FDUMP(fp, Gitsn_RequestID, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RequestID_dump              Dz1s64A_dump
#define Gitsn_RequestIDX_dump Gitsn_RequestIDA_dump
#define Gitsn_RequestID_fdump             Dz1s64A_fdump
#define Gitsn_RequestIDX_fdump Gitsn_RequestIDA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_RequestID_cmp               Dz1s64_cmp

// Gitsn_RequestID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TransitVehicleStatus
typedef u8_t Gitsn_TransitVehicleStatus;

#define Gitsn_TransitVehicleStatus_new               Dz1u8_new
#define Gitsn_TransitVehicleStatus_clone             Dz1u8_clone
#define Gitsn_TransitVehicleStatus_del               Dz1u8_del
#define Gitsn_TransitVehicleStatus_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_TransitVehicleStatusA_dump             Dz1u8A_dump
#define Gitsn_TransitVehicleStatusA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_TransitVehicleStatusW_dump             Dz1u8W_dump
#define Gitsn_TransitVehicleStatusW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_TransitVehicleStatus_dump              Dz1u8W_dump
#define Gitsn_TransitVehicleStatus_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_TransitVehicleStatus_dump              Dz1u8A_dump
#define Gitsn_TransitVehicleStatus_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_TransitVehicleStatusX_dump(Gitsn_TransitVehicleStatus *p, int tab) { DZ1_DUMP(Gitsn_TransitVehicleStatus, p, tab); }
static __inline__ void Gitsn_TransitVehicleStatusX_fdump(FILE *fp, Gitsn_TransitVehicleStatus *p, int tab) { DZ1_FDUMP(fp, Gitsn_TransitVehicleStatus, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_TransitVehicleStatus_dump              Dz1u8A_dump
#define Gitsn_TransitVehicleStatusX_dump Gitsn_TransitVehicleStatusA_dump
#define Gitsn_TransitVehicleStatus_fdump             Dz1u8A_fdump
#define Gitsn_TransitVehicleStatusX_fdump Gitsn_TransitVehicleStatusA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_TransitVehicleStatus_cmp               Dz1u8_cmp

// Gitsn_TransitVehicleStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DeltaTime
typedef s64_t Gitsn_DeltaTime;

#define Gitsn_DeltaTime_new               Dz1s64_new
#define Gitsn_DeltaTime_clone             Dz1s64_clone
#define Gitsn_DeltaTime_del               Dz1s64_del
#define Gitsn_DeltaTime_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_DeltaTimeA_dump             Dz1s64A_dump
#define Gitsn_DeltaTimeA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_DeltaTimeW_dump             Dz1s64W_dump
#define Gitsn_DeltaTimeW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_DeltaTime_dump              Dz1s64W_dump
#define Gitsn_DeltaTime_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_DeltaTime_dump              Dz1s64A_dump
#define Gitsn_DeltaTime_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_DeltaTimeX_dump(Gitsn_DeltaTime *p, int tab) { DZ1_DUMP(Gitsn_DeltaTime, p, tab); }
static __inline__ void Gitsn_DeltaTimeX_fdump(FILE *fp, Gitsn_DeltaTime *p, int tab) { DZ1_FDUMP(fp, Gitsn_DeltaTime, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_DeltaTime_dump              Dz1s64A_dump
#define Gitsn_DeltaTimeX_dump Gitsn_DeltaTimeA_dump
#define Gitsn_DeltaTime_fdump             Dz1s64A_fdump
#define Gitsn_DeltaTimeX_fdump Gitsn_DeltaTimeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_DeltaTime_cmp               Dz1s64_cmp

// Gitsn_DeltaTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PersonalDeviceUsageState
typedef u8_t Gitsn_PersonalDeviceUsageState;

#define Gitsn_PersonalDeviceUsageState_new               Dz1u8_new
#define Gitsn_PersonalDeviceUsageState_clone             Dz1u8_clone
#define Gitsn_PersonalDeviceUsageState_del               Dz1u8_del
#define Gitsn_PersonalDeviceUsageState_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_PersonalDeviceUsageStateA_dump             Dz1u8A_dump
#define Gitsn_PersonalDeviceUsageStateA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PersonalDeviceUsageStateW_dump             Dz1u8W_dump
#define Gitsn_PersonalDeviceUsageStateW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_PersonalDeviceUsageState_dump              Dz1u8W_dump
#define Gitsn_PersonalDeviceUsageState_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_PersonalDeviceUsageState_dump              Dz1u8A_dump
#define Gitsn_PersonalDeviceUsageState_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PersonalDeviceUsageStateX_dump(Gitsn_PersonalDeviceUsageState *p, int tab) { DZ1_DUMP(Gitsn_PersonalDeviceUsageState, p, tab); }
static __inline__ void Gitsn_PersonalDeviceUsageStateX_fdump(FILE *fp, Gitsn_PersonalDeviceUsageState *p, int tab) { DZ1_FDUMP(fp, Gitsn_PersonalDeviceUsageState, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PersonalDeviceUsageState_dump              Dz1u8A_dump
#define Gitsn_PersonalDeviceUsageStateX_dump Gitsn_PersonalDeviceUsageStateA_dump
#define Gitsn_PersonalDeviceUsageState_fdump             Dz1u8A_fdump
#define Gitsn_PersonalDeviceUsageStateX_fdump Gitsn_PersonalDeviceUsageStateA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PersonalDeviceUsageState_cmp               Dz1u8_cmp

// Gitsn_PersonalDeviceUsageState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PersonalCrossingRequest
typedef bool_t Gitsn_PersonalCrossingRequest;

#define Gitsn_PersonalCrossingRequest_new               Dz1Bool_new
#define Gitsn_PersonalCrossingRequest_clone             Dz1Bool_clone
#define Gitsn_PersonalCrossingRequest_del               Dz1Bool_del
#define Gitsn_PersonalCrossingRequest_delAndSetNull     Dz1Bool_delAndSetNull
#define Gitsn_PersonalCrossingRequestA_dump             Dz1BoolA_dump
#define Gitsn_PersonalCrossingRequestA_fdump            Dz1BoolA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PersonalCrossingRequestW_dump             Dz1BoolW_dump
#define Gitsn_PersonalCrossingRequestW_fdump            Dz1BoolW_fdump
#ifdef UNICODE
#define Gitsn_PersonalCrossingRequest_dump              Dz1BoolW_dump
#define Gitsn_PersonalCrossingRequest_fdump             Dz1BoolW_fdump
#else //  UNICODE
#define Gitsn_PersonalCrossingRequest_dump              Dz1BoolA_dump
#define Gitsn_PersonalCrossingRequest_fdump             Dz1BoolA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PersonalCrossingRequestX_dump(Gitsn_PersonalCrossingRequest *p, int tab) { DZ1_DUMP(Gitsn_PersonalCrossingRequest, p, tab); }
static __inline__ void Gitsn_PersonalCrossingRequestX_fdump(FILE *fp, Gitsn_PersonalCrossingRequest *p, int tab) { DZ1_FDUMP(fp, Gitsn_PersonalCrossingRequest, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PersonalCrossingRequest_dump              Dz1BoolA_dump
#define Gitsn_PersonalCrossingRequestX_dump Gitsn_PersonalCrossingRequestA_dump
#define Gitsn_PersonalCrossingRequest_fdump             Dz1BoolA_fdump
#define Gitsn_PersonalCrossingRequestX_fdump Gitsn_PersonalCrossingRequestA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PersonalCrossingRequest_cmp               Dz1Bool_cmp

// Gitsn_PersonalCrossingRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PersonalCrossingInProgress
typedef bool_t Gitsn_PersonalCrossingInProgress;

#define Gitsn_PersonalCrossingInProgress_new               Dz1Bool_new
#define Gitsn_PersonalCrossingInProgress_clone             Dz1Bool_clone
#define Gitsn_PersonalCrossingInProgress_del               Dz1Bool_del
#define Gitsn_PersonalCrossingInProgress_delAndSetNull     Dz1Bool_delAndSetNull
#define Gitsn_PersonalCrossingInProgressA_dump             Dz1BoolA_dump
#define Gitsn_PersonalCrossingInProgressA_fdump            Dz1BoolA_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PersonalCrossingInProgressW_dump             Dz1BoolW_dump
#define Gitsn_PersonalCrossingInProgressW_fdump            Dz1BoolW_fdump
#ifdef UNICODE
#define Gitsn_PersonalCrossingInProgress_dump              Dz1BoolW_dump
#define Gitsn_PersonalCrossingInProgress_fdump             Dz1BoolW_fdump
#else //  UNICODE
#define Gitsn_PersonalCrossingInProgress_dump              Dz1BoolA_dump
#define Gitsn_PersonalCrossingInProgress_fdump             Dz1BoolA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PersonalCrossingInProgressX_dump(Gitsn_PersonalCrossingInProgress *p, int tab) { DZ1_DUMP(Gitsn_PersonalCrossingInProgress, p, tab); }
static __inline__ void Gitsn_PersonalCrossingInProgressX_fdump(FILE *fp, Gitsn_PersonalCrossingInProgress *p, int tab) { DZ1_FDUMP(fp, Gitsn_PersonalCrossingInProgress, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PersonalCrossingInProgress_dump              Dz1BoolA_dump
#define Gitsn_PersonalCrossingInProgressX_dump Gitsn_PersonalCrossingInProgressA_dump
#define Gitsn_PersonalCrossingInProgress_fdump             Dz1BoolA_fdump
#define Gitsn_PersonalCrossingInProgressX_fdump Gitsn_PersonalCrossingInProgressA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PersonalCrossingInProgress_cmp               Dz1Bool_cmp

// Gitsn_PersonalCrossingInProgress
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PersonalClusterRadius
typedef s64_t Gitsn_PersonalClusterRadius;

#define Gitsn_PersonalClusterRadius_new               Dz1s64_new
#define Gitsn_PersonalClusterRadius_clone             Dz1s64_clone
#define Gitsn_PersonalClusterRadius_del               Dz1s64_del
#define Gitsn_PersonalClusterRadius_delAndSetNull     Dz1s64_delAndSetNull
#define Gitsn_PersonalClusterRadiusA_dump             Dz1s64A_dump
#define Gitsn_PersonalClusterRadiusA_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PersonalClusterRadiusW_dump             Dz1s64W_dump
#define Gitsn_PersonalClusterRadiusW_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Gitsn_PersonalClusterRadius_dump              Dz1s64W_dump
#define Gitsn_PersonalClusterRadius_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Gitsn_PersonalClusterRadius_dump              Dz1s64A_dump
#define Gitsn_PersonalClusterRadius_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PersonalClusterRadiusX_dump(Gitsn_PersonalClusterRadius *p, int tab) { DZ1_DUMP(Gitsn_PersonalClusterRadius, p, tab); }
static __inline__ void Gitsn_PersonalClusterRadiusX_fdump(FILE *fp, Gitsn_PersonalClusterRadius *p, int tab) { DZ1_FDUMP(fp, Gitsn_PersonalClusterRadius, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PersonalClusterRadius_dump              Dz1s64A_dump
#define Gitsn_PersonalClusterRadiusX_dump Gitsn_PersonalClusterRadiusA_dump
#define Gitsn_PersonalClusterRadius_fdump             Dz1s64A_fdump
#define Gitsn_PersonalClusterRadiusX_fdump Gitsn_PersonalClusterRadiusA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PersonalClusterRadius_cmp               Dz1s64_cmp

// Gitsn_PersonalClusterRadius
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PublicSafetyAndRoadWorkerActivity
typedef u8_t Gitsn_PublicSafetyAndRoadWorkerActivity;

#define Gitsn_PublicSafetyAndRoadWorkerActivity_new               Dz1u8_new
#define Gitsn_PublicSafetyAndRoadWorkerActivity_clone             Dz1u8_clone
#define Gitsn_PublicSafetyAndRoadWorkerActivity_del               Dz1u8_del
#define Gitsn_PublicSafetyAndRoadWorkerActivity_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_PublicSafetyAndRoadWorkerActivityA_dump             Dz1u8A_dump
#define Gitsn_PublicSafetyAndRoadWorkerActivityA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PublicSafetyAndRoadWorkerActivityW_dump             Dz1u8W_dump
#define Gitsn_PublicSafetyAndRoadWorkerActivityW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_PublicSafetyAndRoadWorkerActivity_dump              Dz1u8W_dump
#define Gitsn_PublicSafetyAndRoadWorkerActivity_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_PublicSafetyAndRoadWorkerActivity_dump              Dz1u8A_dump
#define Gitsn_PublicSafetyAndRoadWorkerActivity_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PublicSafetyAndRoadWorkerActivityX_dump(Gitsn_PublicSafetyAndRoadWorkerActivity *p, int tab) { DZ1_DUMP(Gitsn_PublicSafetyAndRoadWorkerActivity, p, tab); }
static __inline__ void Gitsn_PublicSafetyAndRoadWorkerActivityX_fdump(FILE *fp, Gitsn_PublicSafetyAndRoadWorkerActivity *p, int tab) { DZ1_FDUMP(fp, Gitsn_PublicSafetyAndRoadWorkerActivity, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PublicSafetyAndRoadWorkerActivity_dump              Dz1u8A_dump
#define Gitsn_PublicSafetyAndRoadWorkerActivityX_dump Gitsn_PublicSafetyAndRoadWorkerActivityA_dump
#define Gitsn_PublicSafetyAndRoadWorkerActivity_fdump             Dz1u8A_fdump
#define Gitsn_PublicSafetyAndRoadWorkerActivityX_fdump Gitsn_PublicSafetyAndRoadWorkerActivityA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PublicSafetyAndRoadWorkerActivity_cmp               Dz1u8_cmp

// Gitsn_PublicSafetyAndRoadWorkerActivity
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PublicSafetyDirectingTrafficSubType
typedef u8_t Gitsn_PublicSafetyDirectingTrafficSubType;

#define Gitsn_PublicSafetyDirectingTrafficSubType_new               Dz1u8_new
#define Gitsn_PublicSafetyDirectingTrafficSubType_clone             Dz1u8_clone
#define Gitsn_PublicSafetyDirectingTrafficSubType_del               Dz1u8_del
#define Gitsn_PublicSafetyDirectingTrafficSubType_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_PublicSafetyDirectingTrafficSubTypeA_dump             Dz1u8A_dump
#define Gitsn_PublicSafetyDirectingTrafficSubTypeA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PublicSafetyDirectingTrafficSubTypeW_dump             Dz1u8W_dump
#define Gitsn_PublicSafetyDirectingTrafficSubTypeW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_PublicSafetyDirectingTrafficSubType_dump              Dz1u8W_dump
#define Gitsn_PublicSafetyDirectingTrafficSubType_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_PublicSafetyDirectingTrafficSubType_dump              Dz1u8A_dump
#define Gitsn_PublicSafetyDirectingTrafficSubType_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PublicSafetyDirectingTrafficSubTypeX_dump(Gitsn_PublicSafetyDirectingTrafficSubType *p, int tab) { DZ1_DUMP(Gitsn_PublicSafetyDirectingTrafficSubType, p, tab); }
static __inline__ void Gitsn_PublicSafetyDirectingTrafficSubTypeX_fdump(FILE *fp, Gitsn_PublicSafetyDirectingTrafficSubType *p, int tab) { DZ1_FDUMP(fp, Gitsn_PublicSafetyDirectingTrafficSubType, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PublicSafetyDirectingTrafficSubType_dump              Dz1u8A_dump
#define Gitsn_PublicSafetyDirectingTrafficSubTypeX_dump Gitsn_PublicSafetyDirectingTrafficSubTypeA_dump
#define Gitsn_PublicSafetyDirectingTrafficSubType_fdump             Dz1u8A_fdump
#define Gitsn_PublicSafetyDirectingTrafficSubTypeX_fdump Gitsn_PublicSafetyDirectingTrafficSubTypeA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PublicSafetyDirectingTrafficSubType_cmp               Dz1u8_cmp

// Gitsn_PublicSafetyDirectingTrafficSubType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PersonalAssistive
typedef u8_t Gitsn_PersonalAssistive;

#define Gitsn_PersonalAssistive_new               Dz1u8_new
#define Gitsn_PersonalAssistive_clone             Dz1u8_clone
#define Gitsn_PersonalAssistive_del               Dz1u8_del
#define Gitsn_PersonalAssistive_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_PersonalAssistiveA_dump             Dz1u8A_dump
#define Gitsn_PersonalAssistiveA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_PersonalAssistiveW_dump             Dz1u8W_dump
#define Gitsn_PersonalAssistiveW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_PersonalAssistive_dump              Dz1u8W_dump
#define Gitsn_PersonalAssistive_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_PersonalAssistive_dump              Dz1u8A_dump
#define Gitsn_PersonalAssistive_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_PersonalAssistiveX_dump(Gitsn_PersonalAssistive *p, int tab) { DZ1_DUMP(Gitsn_PersonalAssistive, p, tab); }
static __inline__ void Gitsn_PersonalAssistiveX_fdump(FILE *fp, Gitsn_PersonalAssistive *p, int tab) { DZ1_FDUMP(fp, Gitsn_PersonalAssistive, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_PersonalAssistive_dump              Dz1u8A_dump
#define Gitsn_PersonalAssistiveX_dump Gitsn_PersonalAssistiveA_dump
#define Gitsn_PersonalAssistive_fdump             Dz1u8A_fdump
#define Gitsn_PersonalAssistiveX_fdump Gitsn_PersonalAssistiveA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_PersonalAssistive_cmp               Dz1u8_cmp

// Gitsn_PersonalAssistive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_UserSizeAndBehaviour
typedef u8_t Gitsn_UserSizeAndBehaviour;

#define Gitsn_UserSizeAndBehaviour_new               Dz1u8_new
#define Gitsn_UserSizeAndBehaviour_clone             Dz1u8_clone
#define Gitsn_UserSizeAndBehaviour_del               Dz1u8_del
#define Gitsn_UserSizeAndBehaviour_delAndSetNull     Dz1u8_delAndSetNull
#define Gitsn_UserSizeAndBehaviourA_dump             Dz1u8A_dump
#define Gitsn_UserSizeAndBehaviourA_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Gitsn_UserSizeAndBehaviourW_dump             Dz1u8W_dump
#define Gitsn_UserSizeAndBehaviourW_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Gitsn_UserSizeAndBehaviour_dump              Dz1u8W_dump
#define Gitsn_UserSizeAndBehaviour_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Gitsn_UserSizeAndBehaviour_dump              Dz1u8A_dump
#define Gitsn_UserSizeAndBehaviour_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Gitsn_UserSizeAndBehaviourX_dump(Gitsn_UserSizeAndBehaviour *p, int tab) { DZ1_DUMP(Gitsn_UserSizeAndBehaviour, p, tab); }
static __inline__ void Gitsn_UserSizeAndBehaviourX_fdump(FILE *fp, Gitsn_UserSizeAndBehaviour *p, int tab) { DZ1_FDUMP(fp, Gitsn_UserSizeAndBehaviour, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_UserSizeAndBehaviour_dump              Dz1u8A_dump
#define Gitsn_UserSizeAndBehaviourX_dump Gitsn_UserSizeAndBehaviourA_dump
#define Gitsn_UserSizeAndBehaviour_fdump             Dz1u8A_fdump
#define Gitsn_UserSizeAndBehaviourX_fdump Gitsn_UserSizeAndBehaviourA_fdump
#endif // UNIX_SYSTEM
#define Gitsn_UserSizeAndBehaviour_cmp               Dz1u8_cmp

// Gitsn_UserSizeAndBehaviour
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TransmissionState
typedef enum Gitsn_TransmissionState
{
	Gitsn_TransmissionState_neutral,
	Gitsn_TransmissionState_park,
	Gitsn_TransmissionState_forwardGears,
	Gitsn_TransmissionState_reverseGears,
	Gitsn_TransmissionState_reserved1,
	Gitsn_TransmissionState_reserved2,
	Gitsn_TransmissionState_reserved3,
	Gitsn_TransmissionState_unavailable,
	Gitsn_TransmissionState_max
} Gitsn_TransmissionState;

DZ1_CPPLINK str_t Gitsn_TransmissionStateStrA(Gitsn_TransmissionState v);
DZ1_CPPLINK Gitsn_TransmissionState Gitsn_TransmissionStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TransmissionStateStrW(Gitsn_TransmissionState v);
DZ1_CPPLINK Gitsn_TransmissionState Gitsn_TransmissionStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TransmissionStateStr Gitsn_TransmissionStateStrW
#define Gitsn_TransmissionStateFromStr Gitsn_TransmissionStateFromStrW
#else // UNICODE
#define Gitsn_TransmissionStateStr Gitsn_TransmissionStateStrA
#define Gitsn_TransmissionStateFromStr Gitsn_TransmissionStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TransmissionStateStr Gitsn_TransmissionStateStrA
#define Gitsn_TransmissionStateFromStr Gitsn_TransmissionStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TransmissionState *Gitsn_TransmissionState_new(Gitsn_TransmissionState *src, Dz1Error *err);
static __inline__ Gitsn_TransmissionState *Gitsn_TransmissionState_gen(Dz1Error *err) { Gitsn_TransmissionState v = Gitsn_TransmissionState_max; return Gitsn_TransmissionState_new(&v, err); }
static __inline__ void Gitsn_TransmissionState_del(Gitsn_TransmissionState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TransmissionState_delAndSetNull(void *ptr)
{
	Gitsn_TransmissionState **p = (Gitsn_TransmissionState **)ptr;
	if (p != NULL) { Gitsn_TransmissionState_del(*p); *p = NULL; }
}
// Gitsn_TransmissionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeConfidence
typedef enum Gitsn_TimeConfidence
{
	Gitsn_TimeConfidence_unavailable = 0,
	Gitsn_TimeConfidence_time_100_000,
	Gitsn_TimeConfidence_time_050_000,
	Gitsn_TimeConfidence_time_020_000,
	Gitsn_TimeConfidence_time_010_000,
	Gitsn_TimeConfidence_time_002_000,
	Gitsn_TimeConfidence_time_001_000,
	Gitsn_TimeConfidence_time_000_500,
	Gitsn_TimeConfidence_time_000_200,
	Gitsn_TimeConfidence_time_000_100,
	Gitsn_TimeConfidence_time_000_050,
	Gitsn_TimeConfidence_time_000_020,
	Gitsn_TimeConfidence_time_000_010,
	Gitsn_TimeConfidence_time_000_005,
	Gitsn_TimeConfidence_time_000_002,
	Gitsn_TimeConfidence_time_000_001,
	Gitsn_TimeConfidence_time_000_000_5,
	Gitsn_TimeConfidence_time_000_000_2,
	Gitsn_TimeConfidence_time_000_000_1,
	Gitsn_TimeConfidence_time_000_000_05,
	Gitsn_TimeConfidence_time_000_000_02,
	Gitsn_TimeConfidence_time_000_000_01,
	Gitsn_TimeConfidence_time_000_000_005,
	Gitsn_TimeConfidence_time_000_000_002,
	Gitsn_TimeConfidence_time_000_000_001,
	Gitsn_TimeConfidence_time_000_000_000_5,
	Gitsn_TimeConfidence_time_000_000_000_2,
	Gitsn_TimeConfidence_time_000_000_000_1,
	Gitsn_TimeConfidence_time_000_000_000_05,
	Gitsn_TimeConfidence_time_000_000_000_02,
	Gitsn_TimeConfidence_time_000_000_000_01,
	Gitsn_TimeConfidence_time_000_000_000_005,
	Gitsn_TimeConfidence_time_000_000_000_002,
	Gitsn_TimeConfidence_time_000_000_000_001,
	Gitsn_TimeConfidence_time_000_000_000_000_5,
	Gitsn_TimeConfidence_time_000_000_000_000_2,
	Gitsn_TimeConfidence_time_000_000_000_000_1,
	Gitsn_TimeConfidence_time_000_000_000_000_05,
	Gitsn_TimeConfidence_time_000_000_000_000_02,
	Gitsn_TimeConfidence_time_000_000_000_000_01,
	Gitsn_TimeConfidence_max
} Gitsn_TimeConfidence;

DZ1_CPPLINK str_t Gitsn_TimeConfidenceStrA(Gitsn_TimeConfidence v);
DZ1_CPPLINK Gitsn_TimeConfidence Gitsn_TimeConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TimeConfidenceStrW(Gitsn_TimeConfidence v);
DZ1_CPPLINK Gitsn_TimeConfidence Gitsn_TimeConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TimeConfidenceStr Gitsn_TimeConfidenceStrW
#define Gitsn_TimeConfidenceFromStr Gitsn_TimeConfidenceFromStrW
#else // UNICODE
#define Gitsn_TimeConfidenceStr Gitsn_TimeConfidenceStrA
#define Gitsn_TimeConfidenceFromStr Gitsn_TimeConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TimeConfidenceStr Gitsn_TimeConfidenceStrA
#define Gitsn_TimeConfidenceFromStr Gitsn_TimeConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TimeConfidence *Gitsn_TimeConfidence_new(Gitsn_TimeConfidence *src, Dz1Error *err);
static __inline__ Gitsn_TimeConfidence *Gitsn_TimeConfidence_gen(Dz1Error *err) { Gitsn_TimeConfidence v = Gitsn_TimeConfidence_max; return Gitsn_TimeConfidence_new(&v, err); }
static __inline__ void Gitsn_TimeConfidence_del(Gitsn_TimeConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TimeConfidence_delAndSetNull(void *ptr)
{
	Gitsn_TimeConfidence **p = (Gitsn_TimeConfidence **)ptr;
	if (p != NULL) { Gitsn_TimeConfidence_del(*p); *p = NULL; }
}
// Gitsn_TimeConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PositionConfidence
typedef enum Gitsn_PositionConfidence
{
	Gitsn_PositionConfidence_unavailable = 0,
	Gitsn_PositionConfidence_a500m,
	Gitsn_PositionConfidence_a200m,
	Gitsn_PositionConfidence_a100m,
	Gitsn_PositionConfidence_a50m,
	Gitsn_PositionConfidence_a20m,
	Gitsn_PositionConfidence_a10m,
	Gitsn_PositionConfidence_a5m,
	Gitsn_PositionConfidence_a2m,
	Gitsn_PositionConfidence_a1m,
	Gitsn_PositionConfidence_a50cm,
	Gitsn_PositionConfidence_a20cm,
	Gitsn_PositionConfidence_a10cm,
	Gitsn_PositionConfidence_a5cm,
	Gitsn_PositionConfidence_a2cm,
	Gitsn_PositionConfidence_a1cm,
	Gitsn_PositionConfidence_max
} Gitsn_PositionConfidence;

DZ1_CPPLINK str_t Gitsn_PositionConfidenceStrA(Gitsn_PositionConfidence v);
DZ1_CPPLINK Gitsn_PositionConfidence Gitsn_PositionConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_PositionConfidenceStrW(Gitsn_PositionConfidence v);
DZ1_CPPLINK Gitsn_PositionConfidence Gitsn_PositionConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_PositionConfidenceStr Gitsn_PositionConfidenceStrW
#define Gitsn_PositionConfidenceFromStr Gitsn_PositionConfidenceFromStrW
#else // UNICODE
#define Gitsn_PositionConfidenceStr Gitsn_PositionConfidenceStrA
#define Gitsn_PositionConfidenceFromStr Gitsn_PositionConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_PositionConfidenceStr Gitsn_PositionConfidenceStrA
#define Gitsn_PositionConfidenceFromStr Gitsn_PositionConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PositionConfidence *Gitsn_PositionConfidence_new(Gitsn_PositionConfidence *src, Dz1Error *err);
static __inline__ Gitsn_PositionConfidence *Gitsn_PositionConfidence_gen(Dz1Error *err) { Gitsn_PositionConfidence v = Gitsn_PositionConfidence_max; return Gitsn_PositionConfidence_new(&v, err); }
static __inline__ void Gitsn_PositionConfidence_del(Gitsn_PositionConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_PositionConfidence_delAndSetNull(void *ptr)
{
	Gitsn_PositionConfidence **p = (Gitsn_PositionConfidence **)ptr;
	if (p != NULL) { Gitsn_PositionConfidence_del(*p); *p = NULL; }
}
// Gitsn_PositionConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ElevationConfidence
typedef enum Gitsn_ElevationConfidence
{
	Gitsn_ElevationConfidence_unavailable,
	Gitsn_ElevationConfidence_elev_500_00,
	Gitsn_ElevationConfidence_elev_200_00,
	Gitsn_ElevationConfidence_elev_100_00,
	Gitsn_ElevationConfidence_elev_050_00,
	Gitsn_ElevationConfidence_elev_020_00,
	Gitsn_ElevationConfidence_elev_010_00,
	Gitsn_ElevationConfidence_elev_005_00,
	Gitsn_ElevationConfidence_elev_002_00,
	Gitsn_ElevationConfidence_elev_001_00,
	Gitsn_ElevationConfidence_elev_000_50,
	Gitsn_ElevationConfidence_elev_000_20,
	Gitsn_ElevationConfidence_elev_000_10,
	Gitsn_ElevationConfidence_elev_000_05,
	Gitsn_ElevationConfidence_elev_000_02,
	Gitsn_ElevationConfidence_elev_000_01,
	Gitsn_ElevationConfidence_max
} Gitsn_ElevationConfidence;

DZ1_CPPLINK str_t Gitsn_ElevationConfidenceStrA(Gitsn_ElevationConfidence v);
DZ1_CPPLINK Gitsn_ElevationConfidence Gitsn_ElevationConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ElevationConfidenceStrW(Gitsn_ElevationConfidence v);
DZ1_CPPLINK Gitsn_ElevationConfidence Gitsn_ElevationConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ElevationConfidenceStr Gitsn_ElevationConfidenceStrW
#define Gitsn_ElevationConfidenceFromStr Gitsn_ElevationConfidenceFromStrW
#else // UNICODE
#define Gitsn_ElevationConfidenceStr Gitsn_ElevationConfidenceStrA
#define Gitsn_ElevationConfidenceFromStr Gitsn_ElevationConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ElevationConfidenceStr Gitsn_ElevationConfidenceStrA
#define Gitsn_ElevationConfidenceFromStr Gitsn_ElevationConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ElevationConfidence *Gitsn_ElevationConfidence_new(Gitsn_ElevationConfidence *src, Dz1Error *err);
static __inline__ Gitsn_ElevationConfidence *Gitsn_ElevationConfidence_gen(Dz1Error *err) { Gitsn_ElevationConfidence v = Gitsn_ElevationConfidence_max; return Gitsn_ElevationConfidence_new(&v, err); }
static __inline__ void Gitsn_ElevationConfidence_del(Gitsn_ElevationConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ElevationConfidence_delAndSetNull(void *ptr)
{
	Gitsn_ElevationConfidence **p = (Gitsn_ElevationConfidence **)ptr;
	if (p != NULL) { Gitsn_ElevationConfidence_del(*p); *p = NULL; }
}
// Gitsn_ElevationConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_HeadingConfidence
typedef enum Gitsn_HeadingConfidence
{
	Gitsn_HeadingConfidence_unavailable,
	Gitsn_HeadingConfidence_prec10deg,
	Gitsn_HeadingConfidence_prec05deg,
	Gitsn_HeadingConfidence_prec01deg,
	Gitsn_HeadingConfidence_prec0_1deg,
	Gitsn_HeadingConfidence_prec0_05deg,
	Gitsn_HeadingConfidence_prec0_01deg,
	Gitsn_HeadingConfidence_prec0_0125deg,
	Gitsn_HeadingConfidence_max
} Gitsn_HeadingConfidence;

DZ1_CPPLINK str_t Gitsn_HeadingConfidenceStrA(Gitsn_HeadingConfidence v);
DZ1_CPPLINK Gitsn_HeadingConfidence Gitsn_HeadingConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_HeadingConfidenceStrW(Gitsn_HeadingConfidence v);
DZ1_CPPLINK Gitsn_HeadingConfidence Gitsn_HeadingConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_HeadingConfidenceStr Gitsn_HeadingConfidenceStrW
#define Gitsn_HeadingConfidenceFromStr Gitsn_HeadingConfidenceFromStrW
#else // UNICODE
#define Gitsn_HeadingConfidenceStr Gitsn_HeadingConfidenceStrA
#define Gitsn_HeadingConfidenceFromStr Gitsn_HeadingConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_HeadingConfidenceStr Gitsn_HeadingConfidenceStrA
#define Gitsn_HeadingConfidenceFromStr Gitsn_HeadingConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_HeadingConfidence *Gitsn_HeadingConfidence_new(Gitsn_HeadingConfidence *src, Dz1Error *err);
static __inline__ Gitsn_HeadingConfidence *Gitsn_HeadingConfidence_gen(Dz1Error *err) { Gitsn_HeadingConfidence v = Gitsn_HeadingConfidence_max; return Gitsn_HeadingConfidence_new(&v, err); }
static __inline__ void Gitsn_HeadingConfidence_del(Gitsn_HeadingConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_HeadingConfidence_delAndSetNull(void *ptr)
{
	Gitsn_HeadingConfidence **p = (Gitsn_HeadingConfidence **)ptr;
	if (p != NULL) { Gitsn_HeadingConfidence_del(*p); *p = NULL; }
}
// Gitsn_HeadingConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedConfidence
typedef enum Gitsn_SpeedConfidence
{
	Gitsn_SpeedConfidence_unavailable,
	Gitsn_SpeedConfidence_prec100ms,
	Gitsn_SpeedConfidence_prec10ms,
	Gitsn_SpeedConfidence_prec5ms,
	Gitsn_SpeedConfidence_prec1ms,
	Gitsn_SpeedConfidence_prec0_1ms,
	Gitsn_SpeedConfidence_prec0_05ms,
	Gitsn_SpeedConfidence_prec0_01ms,
	Gitsn_SpeedConfidence_max
} Gitsn_SpeedConfidence;

DZ1_CPPLINK str_t Gitsn_SpeedConfidenceStrA(Gitsn_SpeedConfidence v);
DZ1_CPPLINK Gitsn_SpeedConfidence Gitsn_SpeedConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SpeedConfidenceStrW(Gitsn_SpeedConfidence v);
DZ1_CPPLINK Gitsn_SpeedConfidence Gitsn_SpeedConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SpeedConfidenceStr Gitsn_SpeedConfidenceStrW
#define Gitsn_SpeedConfidenceFromStr Gitsn_SpeedConfidenceFromStrW
#else // UNICODE
#define Gitsn_SpeedConfidenceStr Gitsn_SpeedConfidenceStrA
#define Gitsn_SpeedConfidenceFromStr Gitsn_SpeedConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SpeedConfidenceStr Gitsn_SpeedConfidenceStrA
#define Gitsn_SpeedConfidenceFromStr Gitsn_SpeedConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedConfidence *Gitsn_SpeedConfidence_new(Gitsn_SpeedConfidence *src, Dz1Error *err);
static __inline__ Gitsn_SpeedConfidence *Gitsn_SpeedConfidence_gen(Dz1Error *err) { Gitsn_SpeedConfidence v = Gitsn_SpeedConfidence_max; return Gitsn_SpeedConfidence_new(&v, err); }
static __inline__ void Gitsn_SpeedConfidence_del(Gitsn_SpeedConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SpeedConfidence_delAndSetNull(void *ptr)
{
	Gitsn_SpeedConfidence **p = (Gitsn_SpeedConfidence **)ptr;
	if (p != NULL) { Gitsn_SpeedConfidence_del(*p); *p = NULL; }
}
// Gitsn_SpeedConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ThrottleConfidence
typedef enum Gitsn_ThrottleConfidence
{
	Gitsn_ThrottleConfidence_unavailable,
	Gitsn_ThrottleConfidence_prec10percent,
	Gitsn_ThrottleConfidence_prec1percent,
	Gitsn_ThrottleConfidence_prec0_5percent,
	Gitsn_ThrottleConfidence_max
} Gitsn_ThrottleConfidence;

DZ1_CPPLINK str_t Gitsn_ThrottleConfidenceStrA(Gitsn_ThrottleConfidence v);
DZ1_CPPLINK Gitsn_ThrottleConfidence Gitsn_ThrottleConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ThrottleConfidenceStrW(Gitsn_ThrottleConfidence v);
DZ1_CPPLINK Gitsn_ThrottleConfidence Gitsn_ThrottleConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ThrottleConfidenceStr Gitsn_ThrottleConfidenceStrW
#define Gitsn_ThrottleConfidenceFromStr Gitsn_ThrottleConfidenceFromStrW
#else // UNICODE
#define Gitsn_ThrottleConfidenceStr Gitsn_ThrottleConfidenceStrA
#define Gitsn_ThrottleConfidenceFromStr Gitsn_ThrottleConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ThrottleConfidenceStr Gitsn_ThrottleConfidenceStrA
#define Gitsn_ThrottleConfidenceFromStr Gitsn_ThrottleConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ThrottleConfidence *Gitsn_ThrottleConfidence_new(Gitsn_ThrottleConfidence *src, Dz1Error *err);
static __inline__ Gitsn_ThrottleConfidence *Gitsn_ThrottleConfidence_gen(Dz1Error *err) { Gitsn_ThrottleConfidence v = Gitsn_ThrottleConfidence_max; return Gitsn_ThrottleConfidence_new(&v, err); }
static __inline__ void Gitsn_ThrottleConfidence_del(Gitsn_ThrottleConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ThrottleConfidence_delAndSetNull(void *ptr)
{
	Gitsn_ThrottleConfidence **p = (Gitsn_ThrottleConfidence **)ptr;
	if (p != NULL) { Gitsn_ThrottleConfidence_del(*p); *p = NULL; }
}
// Gitsn_ThrottleConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LightbarInUse
typedef enum Gitsn_LightbarInUse
{
	Gitsn_LightbarInUse_unavailable = 0,
	Gitsn_LightbarInUse_notInUse = 1,
	Gitsn_LightbarInUse_inUse = 2,
	Gitsn_LightbarInUse_yellowCautionLights = 3,
	Gitsn_LightbarInUse_schooldBusLights = 4,
	Gitsn_LightbarInUse_arrowSignsActive = 5,
	Gitsn_LightbarInUse_slowMovingVehicle = 6,
	Gitsn_LightbarInUse_freqStops = 7,
	Gitsn_LightbarInUse_max
} Gitsn_LightbarInUse;

DZ1_CPPLINK str_t Gitsn_LightbarInUseStrA(Gitsn_LightbarInUse v);
DZ1_CPPLINK Gitsn_LightbarInUse Gitsn_LightbarInUseFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_LightbarInUseStrW(Gitsn_LightbarInUse v);
DZ1_CPPLINK Gitsn_LightbarInUse Gitsn_LightbarInUseFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_LightbarInUseStr Gitsn_LightbarInUseStrW
#define Gitsn_LightbarInUseFromStr Gitsn_LightbarInUseFromStrW
#else // UNICODE
#define Gitsn_LightbarInUseStr Gitsn_LightbarInUseStrA
#define Gitsn_LightbarInUseFromStr Gitsn_LightbarInUseFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_LightbarInUseStr Gitsn_LightbarInUseStrA
#define Gitsn_LightbarInUseFromStr Gitsn_LightbarInUseFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LightbarInUse *Gitsn_LightbarInUse_new(Gitsn_LightbarInUse *src, Dz1Error *err);
static __inline__ Gitsn_LightbarInUse *Gitsn_LightbarInUse_gen(Dz1Error *err) { Gitsn_LightbarInUse v = Gitsn_LightbarInUse_max; return Gitsn_LightbarInUse_new(&v, err); }
static __inline__ void Gitsn_LightbarInUse_del(Gitsn_LightbarInUse *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_LightbarInUse_delAndSetNull(void *ptr)
{
	Gitsn_LightbarInUse **p = (Gitsn_LightbarInUse **)ptr;
	if (p != NULL) { Gitsn_LightbarInUse_del(*p); *p = NULL; }
}
// Gitsn_LightbarInUse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RainSensor
typedef enum Gitsn_RainSensor
{
	Gitsn_RainSensor_none = 0,
	Gitsn_RainSensor_lightMist = 1,
	Gitsn_RainSensor_heavyMist = 2,
	Gitsn_RainSensor_lightRainOrDrizzle = 3,
	Gitsn_RainSensor_rain = 4,
	Gitsn_RainSensor_moderateRain = 5,
	Gitsn_RainSensor_heavyRain = 6,
	Gitsn_RainSensor_heavyDownpour = 7,
	Gitsn_RainSensor_max
} Gitsn_RainSensor;

DZ1_CPPLINK str_t Gitsn_RainSensorStrA(Gitsn_RainSensor v);
DZ1_CPPLINK Gitsn_RainSensor Gitsn_RainSensorFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_RainSensorStrW(Gitsn_RainSensor v);
DZ1_CPPLINK Gitsn_RainSensor Gitsn_RainSensorFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_RainSensorStr Gitsn_RainSensorStrW
#define Gitsn_RainSensorFromStr Gitsn_RainSensorFromStrW
#else // UNICODE
#define Gitsn_RainSensorStr Gitsn_RainSensorStrA
#define Gitsn_RainSensorFromStr Gitsn_RainSensorFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_RainSensorStr Gitsn_RainSensorStrA
#define Gitsn_RainSensorFromStr Gitsn_RainSensorFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RainSensor *Gitsn_RainSensor_new(Gitsn_RainSensor *src, Dz1Error *err);
static __inline__ Gitsn_RainSensor *Gitsn_RainSensor_gen(Dz1Error *err) { Gitsn_RainSensor v = Gitsn_RainSensor_max; return Gitsn_RainSensor_new(&v, err); }
static __inline__ void Gitsn_RainSensor_del(Gitsn_RainSensor *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_RainSensor_delAndSetNull(void *ptr)
{
	Gitsn_RainSensor **p = (Gitsn_RainSensor **)ptr;
	if (p != NULL) { Gitsn_RainSensor_del(*p); *p = NULL; }
}
// Gitsn_RainSensor
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BasicVehicleRole
typedef enum Gitsn_BasicVehicleRole
{
	Gitsn_BasicVehicleRole_basicVehicle,
	Gitsn_BasicVehicleRole_publicTransport,
	Gitsn_BasicVehicleRole_specialTransport,
	Gitsn_BasicVehicleRole_dangerousGoods,
	Gitsn_BasicVehicleRole_roadWork,
	Gitsn_BasicVehicleRole_roadRescue,
	Gitsn_BasicVehicleRole_emergency,
	Gitsn_BasicVehicleRole_safetyCar,
	Gitsn_BasicVehicleRole_none,
	Gitsn_BasicVehicleRole_truck,
	Gitsn_BasicVehicleRole_motorcycle,
	Gitsn_BasicVehicleRole_roadSideSource,
	Gitsn_BasicVehicleRole_police,
	Gitsn_BasicVehicleRole_fire,
	Gitsn_BasicVehicleRole_ambulance,
	Gitsn_BasicVehicleRole_dot,
	Gitsn_BasicVehicleRole_transit,
	Gitsn_BasicVehicleRole_slowMoving,
	Gitsn_BasicVehicleRole_stopNgo,
	Gitsn_BasicVehicleRole_cyclist,
	Gitsn_BasicVehicleRole_pedestrian,
	Gitsn_BasicVehicleRole_nonMotorized,
	Gitsn_BasicVehicleRole_military,
	Gitsn_BasicVehicleRole_max
} Gitsn_BasicVehicleRole;

DZ1_CPPLINK str_t Gitsn_BasicVehicleRoleStrA(Gitsn_BasicVehicleRole v);
DZ1_CPPLINK Gitsn_BasicVehicleRole Gitsn_BasicVehicleRoleFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_BasicVehicleRoleStrW(Gitsn_BasicVehicleRole v);
DZ1_CPPLINK Gitsn_BasicVehicleRole Gitsn_BasicVehicleRoleFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_BasicVehicleRoleStr Gitsn_BasicVehicleRoleStrW
#define Gitsn_BasicVehicleRoleFromStr Gitsn_BasicVehicleRoleFromStrW
#else // UNICODE
#define Gitsn_BasicVehicleRoleStr Gitsn_BasicVehicleRoleStrA
#define Gitsn_BasicVehicleRoleFromStr Gitsn_BasicVehicleRoleFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_BasicVehicleRoleStr Gitsn_BasicVehicleRoleStrA
#define Gitsn_BasicVehicleRoleFromStr Gitsn_BasicVehicleRoleFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_BasicVehicleRole *Gitsn_BasicVehicleRole_new(Gitsn_BasicVehicleRole *src, Dz1Error *err);
static __inline__ Gitsn_BasicVehicleRole *Gitsn_BasicVehicleRole_gen(Dz1Error *err) { Gitsn_BasicVehicleRole v = Gitsn_BasicVehicleRole_max; return Gitsn_BasicVehicleRole_new(&v, err); }
static __inline__ void Gitsn_BasicVehicleRole_del(Gitsn_BasicVehicleRole *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_BasicVehicleRole_delAndSetNull(void *ptr)
{
	Gitsn_BasicVehicleRole **p = (Gitsn_BasicVehicleRole **)ptr;
	if (p != NULL) { Gitsn_BasicVehicleRole_del(*p); *p = NULL; }
}
// Gitsn_BasicVehicleRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleType
typedef enum Gitsn_VehicleType
{
	Gitsn_VehicleType_none,
	Gitsn_VehicleType_unknown,
	Gitsn_VehicleType_special,
	Gitsn_VehicleType_moto,
	Gitsn_VehicleType_car,
	Gitsn_VehicleType_carOther,
	Gitsn_VehicleType_bus,
	Gitsn_VehicleType_axleCnt2,
	Gitsn_VehicleType_axleCnt3,
	Gitsn_VehicleType_axleCnt4,
	Gitsn_VehicleType_axleCnt4Trailer,
	Gitsn_VehicleType_axleCnt5Trailer,
	Gitsn_VehicleType_axleCnt6Trailer,
	Gitsn_VehicleType_axleCnt5MultiTrailer,
	Gitsn_VehicleType_axleCnt6MultiTrailer,
	Gitsn_VehicleType_axleCnt7MultiTrailer,
	Gitsn_VehicleType_max
} Gitsn_VehicleType;

DZ1_CPPLINK str_t Gitsn_VehicleTypeStrA(Gitsn_VehicleType v);
DZ1_CPPLINK Gitsn_VehicleType Gitsn_VehicleTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_VehicleTypeStrW(Gitsn_VehicleType v);
DZ1_CPPLINK Gitsn_VehicleType Gitsn_VehicleTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_VehicleTypeStr Gitsn_VehicleTypeStrW
#define Gitsn_VehicleTypeFromStr Gitsn_VehicleTypeFromStrW
#else // UNICODE
#define Gitsn_VehicleTypeStr Gitsn_VehicleTypeStrA
#define Gitsn_VehicleTypeFromStr Gitsn_VehicleTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_VehicleTypeStr Gitsn_VehicleTypeStrA
#define Gitsn_VehicleTypeFromStr Gitsn_VehicleTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleType *Gitsn_VehicleType_new(Gitsn_VehicleType *src, Dz1Error *err);
static __inline__ Gitsn_VehicleType *Gitsn_VehicleType_gen(Dz1Error *err) { Gitsn_VehicleType v = Gitsn_VehicleType_max; return Gitsn_VehicleType_new(&v, err); }
static __inline__ void Gitsn_VehicleType_del(Gitsn_VehicleType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_VehicleType_delAndSetNull(void *ptr)
{
	Gitsn_VehicleType **p = (Gitsn_VehicleType **)ptr;
	if (p != NULL) { Gitsn_VehicleType_del(*p); *p = NULL; }
}
// Gitsn_VehicleType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleGroupAffected
typedef enum Gitsn_VehicleGroupAffected
{
	Gitsn_VehicleGroupAffected_all = 9217,
	Gitsn_VehicleGroupAffected_bicycles,
	Gitsn_VehicleGroupAffected_motorcycles,
	Gitsn_VehicleGroupAffected_cars,
	Gitsn_VehicleGroupAffected_light_vehicles,
	Gitsn_VehicleGroupAffected_cars_and_light_vehicles,
	Gitsn_VehicleGroupAffected_cars_with_trailers,
	Gitsn_VehicleGroupAffected_cars_with_recreational_trailers,
	Gitsn_VehicleGroupAffected_vehicles_with_trailers,
	Gitsn_VehicleGroupAffected_heavy_vehicles,
	Gitsn_VehicleGroupAffected_trucks,
	Gitsn_VehicleGroupAffected_buses,
	Gitsn_VehicleGroupAffected_articulated_buses,
	Gitsn_VehicleGroupAffected_school_buses,
	Gitsn_VehicleGroupAffected_vehicles_with_semi_trailers,
	Gitsn_VehicleGroupAffected_vehicles_with_double_trailers,
	Gitsn_VehicleGroupAffected_high_profile_vehicles,
	Gitsn_VehicleGroupAffected_wide_vehicles,
	Gitsn_VehicleGroupAffected_long_vehicles,
	Gitsn_VehicleGroupAffected_hazardous_loads,
	Gitsn_VehicleGroupAffected_exceptional_loads,
	Gitsn_VehicleGroupAffected_abnormal_loads,
	Gitsn_VehicleGroupAffected_convoys,
	Gitsn_VehicleGroupAffected_maintenance_vehicles,
	Gitsn_VehicleGroupAffected_delivery_vehicles,
	Gitsn_VehicleGroupAffected_vehicles_with_even_numbered_license_plates,
	Gitsn_VehicleGroupAffected_vehicles_with_odd_numbered_license_plates,
	Gitsn_VehicleGroupAffected_vehicles_with_parking_permits,
	Gitsn_VehicleGroupAffected_vehicles_with_catalytic_converters,
	Gitsn_VehicleGroupAffected_vehicles_without_catalytic_converters,
	Gitsn_VehicleGroupAffected_gas_powered_vehicles,
	Gitsn_VehicleGroupAffected_diesel_powered_vehicles,
	Gitsn_VehicleGroupAffected_lPG_vehicles,
	Gitsn_VehicleGroupAffected_military_convoys,
	Gitsn_VehicleGroupAffected_military_vehicles,
	Gitsn_VehicleGroupAffected_max
} Gitsn_VehicleGroupAffected;

DZ1_CPPLINK str_t Gitsn_VehicleGroupAffectedStrA(Gitsn_VehicleGroupAffected v);
DZ1_CPPLINK Gitsn_VehicleGroupAffected Gitsn_VehicleGroupAffectedFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_VehicleGroupAffectedStrW(Gitsn_VehicleGroupAffected v);
DZ1_CPPLINK Gitsn_VehicleGroupAffected Gitsn_VehicleGroupAffectedFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_VehicleGroupAffectedStr Gitsn_VehicleGroupAffectedStrW
#define Gitsn_VehicleGroupAffectedFromStr Gitsn_VehicleGroupAffectedFromStrW
#else // UNICODE
#define Gitsn_VehicleGroupAffectedStr Gitsn_VehicleGroupAffectedStrA
#define Gitsn_VehicleGroupAffectedFromStr Gitsn_VehicleGroupAffectedFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_VehicleGroupAffectedStr Gitsn_VehicleGroupAffectedStrA
#define Gitsn_VehicleGroupAffectedFromStr Gitsn_VehicleGroupAffectedFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleGroupAffected *Gitsn_VehicleGroupAffected_new(Gitsn_VehicleGroupAffected *src, Dz1Error *err);
static __inline__ Gitsn_VehicleGroupAffected *Gitsn_VehicleGroupAffected_gen(Dz1Error *err) { Gitsn_VehicleGroupAffected v = Gitsn_VehicleGroupAffected_max; return Gitsn_VehicleGroupAffected_new(&v, err); }
static __inline__ void Gitsn_VehicleGroupAffected_del(Gitsn_VehicleGroupAffected *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_VehicleGroupAffected_delAndSetNull(void *ptr)
{
	Gitsn_VehicleGroupAffected **p = (Gitsn_VehicleGroupAffected **)ptr;
	if (p != NULL) { Gitsn_VehicleGroupAffected_del(*p); *p = NULL; }
}
// Gitsn_VehicleGroupAffected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentResponseEquipment
typedef enum Gitsn_IncidentResponseEquipment
{
	Gitsn_IncidentResponseEquipment_ground_fire_suppression = 9985,
	Gitsn_IncidentResponseEquipment_heavy_ground_equipment,
	Gitsn_IncidentResponseEquipment_aircraft,
	Gitsn_IncidentResponseEquipment_marine_equipment,
	Gitsn_IncidentResponseEquipment_support_equipment,
	Gitsn_IncidentResponseEquipment_medical_rescue_unit,
	Gitsn_IncidentResponseEquipment_other,
	Gitsn_IncidentResponseEquipment_ground_fire_suppression_other,
	Gitsn_IncidentResponseEquipment_engine,
	Gitsn_IncidentResponseEquipment_truck_or_aerial,
	Gitsn_IncidentResponseEquipment_quint,
	Gitsn_IncidentResponseEquipment_tanker_pumper_combination,
	Gitsn_IncidentResponseEquipment_brush_truck,
	Gitsn_IncidentResponseEquipment_aircraft_rescue_firefighting,
	Gitsn_IncidentResponseEquipment_heavy_ground_equipment_other,
	Gitsn_IncidentResponseEquipment_dozer_or_plow,
	Gitsn_IncidentResponseEquipment_tractor,
	Gitsn_IncidentResponseEquipment_tanker_or_tender,
	Gitsn_IncidentResponseEquipment_aircraft_other,
	Gitsn_IncidentResponseEquipment_aircraft_fixed_wing_tanker,
	Gitsn_IncidentResponseEquipment_helitanker,
	Gitsn_IncidentResponseEquipment_helicopter,
	Gitsn_IncidentResponseEquipment_marine_equipment_other,
	Gitsn_IncidentResponseEquipment_fire_boat_with_pump,
	Gitsn_IncidentResponseEquipment_boat_no_pump,
	Gitsn_IncidentResponseEquipment_support_apparatus_other,
	Gitsn_IncidentResponseEquipment_breathing_apparatus_support,
	Gitsn_IncidentResponseEquipment_light_and_air_unit,
	Gitsn_IncidentResponseEquipment_medical_rescue_unit_other,
	Gitsn_IncidentResponseEquipment_rescue_unit,
	Gitsn_IncidentResponseEquipment_urban_search_rescue_unit,
	Gitsn_IncidentResponseEquipment_high_angle_rescue,
	Gitsn_IncidentResponseEquipment_crash_fire_rescue,
	Gitsn_IncidentResponseEquipment_bLS_unit,
	Gitsn_IncidentResponseEquipment_aLS_unit,
	Gitsn_IncidentResponseEquipment_mobile_command_post,
	Gitsn_IncidentResponseEquipment_chief_officer_car,
	Gitsn_IncidentResponseEquipment_hAZMAT_unit,
	Gitsn_IncidentResponseEquipment_type_i_hand_crew,
	Gitsn_IncidentResponseEquipment_type_ii_hand_crew,
	Gitsn_IncidentResponseEquipment_privately_owned_vehicle,
	Gitsn_IncidentResponseEquipment_other_apparatus_resource,
	Gitsn_IncidentResponseEquipment_ambulance,
	Gitsn_IncidentResponseEquipment_bomb_squad_van,
	Gitsn_IncidentResponseEquipment_combine_harvester,
	Gitsn_IncidentResponseEquipment_construction_vehicle,
	Gitsn_IncidentResponseEquipment_farm_tractor,
	Gitsn_IncidentResponseEquipment_grass_cutting_machines,
	Gitsn_IncidentResponseEquipment_hAZMAT_containment_tow,
	Gitsn_IncidentResponseEquipment_heavy_tow,
	Gitsn_IncidentResponseEquipment_light_tow,
	Gitsn_IncidentResponseEquipment_flatbed_tow,
	Gitsn_IncidentResponseEquipment_hedge_cutting_machines,
	Gitsn_IncidentResponseEquipment_mobile_crane,
	Gitsn_IncidentResponseEquipment_refuse_collection_vehicle,
	Gitsn_IncidentResponseEquipment_resurfacing_vehicle,
	Gitsn_IncidentResponseEquipment_road_sweeper,
	Gitsn_IncidentResponseEquipment_roadside_litter_collection_crews,
	Gitsn_IncidentResponseEquipment_salvage_vehicle,
	Gitsn_IncidentResponseEquipment_sand_truck,
	Gitsn_IncidentResponseEquipment_snowplow,
	Gitsn_IncidentResponseEquipment_steam_roller,
	Gitsn_IncidentResponseEquipment_swat_team_van,
	Gitsn_IncidentResponseEquipment_track_laying_vehicle,
	Gitsn_IncidentResponseEquipment_unknown_vehicle,
	Gitsn_IncidentResponseEquipment_white_lining_vehicle,
	Gitsn_IncidentResponseEquipment_dump_truck,
	Gitsn_IncidentResponseEquipment_supervisor_vehicle,
	Gitsn_IncidentResponseEquipment_snow_blower,
	Gitsn_IncidentResponseEquipment_rotary_snow_blower,
	Gitsn_IncidentResponseEquipment_road_grader,
	Gitsn_IncidentResponseEquipment_steam_truck,
	Gitsn_IncidentResponseEquipment_max
} Gitsn_IncidentResponseEquipment;

DZ1_CPPLINK str_t Gitsn_IncidentResponseEquipmentStrA(Gitsn_IncidentResponseEquipment v);
DZ1_CPPLINK Gitsn_IncidentResponseEquipment Gitsn_IncidentResponseEquipmentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_IncidentResponseEquipmentStrW(Gitsn_IncidentResponseEquipment v);
DZ1_CPPLINK Gitsn_IncidentResponseEquipment Gitsn_IncidentResponseEquipmentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_IncidentResponseEquipmentStr Gitsn_IncidentResponseEquipmentStrW
#define Gitsn_IncidentResponseEquipmentFromStr Gitsn_IncidentResponseEquipmentFromStrW
#else // UNICODE
#define Gitsn_IncidentResponseEquipmentStr Gitsn_IncidentResponseEquipmentStrA
#define Gitsn_IncidentResponseEquipmentFromStr Gitsn_IncidentResponseEquipmentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_IncidentResponseEquipmentStr Gitsn_IncidentResponseEquipmentStrA
#define Gitsn_IncidentResponseEquipmentFromStr Gitsn_IncidentResponseEquipmentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentResponseEquipment *Gitsn_IncidentResponseEquipment_new(Gitsn_IncidentResponseEquipment *src, Dz1Error *err);
static __inline__ Gitsn_IncidentResponseEquipment *Gitsn_IncidentResponseEquipment_gen(Dz1Error *err) { Gitsn_IncidentResponseEquipment v = Gitsn_IncidentResponseEquipment_max; return Gitsn_IncidentResponseEquipment_new(&v, err); }
static __inline__ void Gitsn_IncidentResponseEquipment_del(Gitsn_IncidentResponseEquipment *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_IncidentResponseEquipment_delAndSetNull(void *ptr)
{
	Gitsn_IncidentResponseEquipment **p = (Gitsn_IncidentResponseEquipment **)ptr;
	if (p != NULL) { Gitsn_IncidentResponseEquipment_del(*p); *p = NULL; }
}
// Gitsn_IncidentResponseEquipment
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ResponderGroupAffected
typedef enum Gitsn_ResponderGroupAffected
{
	Gitsn_ResponderGroupAffected_emergency_vehicle_units = 9729,
	Gitsn_ResponderGroupAffected_federal_law_enforcement_units,
	Gitsn_ResponderGroupAffected_state_police_units,
	Gitsn_ResponderGroupAffected_county_police_units,
	Gitsn_ResponderGroupAffected_local_police_units,
	Gitsn_ResponderGroupAffected_ambulance_units,
	Gitsn_ResponderGroupAffected_rescue_units,
	Gitsn_ResponderGroupAffected_fire_units,
	Gitsn_ResponderGroupAffected_hAZMAT_units,
	Gitsn_ResponderGroupAffected_light_tow_unit,
	Gitsn_ResponderGroupAffected_heavy_tow_unit,
	Gitsn_ResponderGroupAffected_freeway_service_patrols,
	Gitsn_ResponderGroupAffected_transportation_response_units,
	Gitsn_ResponderGroupAffected_private_contractor_response_units,
	Gitsn_ResponderGroupAffected_max
} Gitsn_ResponderGroupAffected;

DZ1_CPPLINK str_t Gitsn_ResponderGroupAffectedStrA(Gitsn_ResponderGroupAffected v);
DZ1_CPPLINK Gitsn_ResponderGroupAffected Gitsn_ResponderGroupAffectedFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ResponderGroupAffectedStrW(Gitsn_ResponderGroupAffected v);
DZ1_CPPLINK Gitsn_ResponderGroupAffected Gitsn_ResponderGroupAffectedFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ResponderGroupAffectedStr Gitsn_ResponderGroupAffectedStrW
#define Gitsn_ResponderGroupAffectedFromStr Gitsn_ResponderGroupAffectedFromStrW
#else // UNICODE
#define Gitsn_ResponderGroupAffectedStr Gitsn_ResponderGroupAffectedStrA
#define Gitsn_ResponderGroupAffectedFromStr Gitsn_ResponderGroupAffectedFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ResponderGroupAffectedStr Gitsn_ResponderGroupAffectedStrA
#define Gitsn_ResponderGroupAffectedFromStr Gitsn_ResponderGroupAffectedFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ResponderGroupAffected *Gitsn_ResponderGroupAffected_new(Gitsn_ResponderGroupAffected *src, Dz1Error *err);
static __inline__ Gitsn_ResponderGroupAffected *Gitsn_ResponderGroupAffected_gen(Dz1Error *err) { Gitsn_ResponderGroupAffected v = Gitsn_ResponderGroupAffected_max; return Gitsn_ResponderGroupAffected_new(&v, err); }
static __inline__ void Gitsn_ResponderGroupAffected_del(Gitsn_ResponderGroupAffected *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ResponderGroupAffected_delAndSetNull(void *ptr)
{
	Gitsn_ResponderGroupAffected **p = (Gitsn_ResponderGroupAffected **)ptr;
	if (p != NULL) { Gitsn_ResponderGroupAffected_del(*p); *p = NULL; }
}
// Gitsn_ResponderGroupAffected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WiperStatus
typedef enum Gitsn_WiperStatus
{
	Gitsn_WiperStatus_unavailable,
	Gitsn_WiperStatus_off,
	Gitsn_WiperStatus_intermittent,
	Gitsn_WiperStatus_low,
	Gitsn_WiperStatus_high,
	Gitsn_WiperStatus_washerInUse,
	Gitsn_WiperStatus_automaticPresent,
	Gitsn_WiperStatus_max
} Gitsn_WiperStatus;

DZ1_CPPLINK str_t Gitsn_WiperStatusStrA(Gitsn_WiperStatus v);
DZ1_CPPLINK Gitsn_WiperStatus Gitsn_WiperStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_WiperStatusStrW(Gitsn_WiperStatus v);
DZ1_CPPLINK Gitsn_WiperStatus Gitsn_WiperStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_WiperStatusStr Gitsn_WiperStatusStrW
#define Gitsn_WiperStatusFromStr Gitsn_WiperStatusFromStrW
#else // UNICODE
#define Gitsn_WiperStatusStr Gitsn_WiperStatusStrA
#define Gitsn_WiperStatusFromStr Gitsn_WiperStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_WiperStatusStr Gitsn_WiperStatusStrA
#define Gitsn_WiperStatusFromStr Gitsn_WiperStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_WiperStatus *Gitsn_WiperStatus_new(Gitsn_WiperStatus *src, Dz1Error *err);
static __inline__ Gitsn_WiperStatus *Gitsn_WiperStatus_gen(Dz1Error *err) { Gitsn_WiperStatus v = Gitsn_WiperStatus_max; return Gitsn_WiperStatus_new(&v, err); }
static __inline__ void Gitsn_WiperStatus_del(Gitsn_WiperStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_WiperStatus_delAndSetNull(void *ptr)
{
	Gitsn_WiperStatus **p = (Gitsn_WiperStatus **)ptr;
	if (p != NULL) { Gitsn_WiperStatus_del(*p); *p = NULL; }
}
// Gitsn_WiperStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TractionControlStatus
typedef enum Gitsn_TractionControlStatus
{
	Gitsn_TractionControlStatus_unavailable,
	Gitsn_TractionControlStatus_off,
	Gitsn_TractionControlStatus_on,
	Gitsn_TractionControlStatus_engaged,
	Gitsn_TractionControlStatus_max
} Gitsn_TractionControlStatus;

DZ1_CPPLINK str_t Gitsn_TractionControlStatusStrA(Gitsn_TractionControlStatus v);
DZ1_CPPLINK Gitsn_TractionControlStatus Gitsn_TractionControlStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TractionControlStatusStrW(Gitsn_TractionControlStatus v);
DZ1_CPPLINK Gitsn_TractionControlStatus Gitsn_TractionControlStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TractionControlStatusStr Gitsn_TractionControlStatusStrW
#define Gitsn_TractionControlStatusFromStr Gitsn_TractionControlStatusFromStrW
#else // UNICODE
#define Gitsn_TractionControlStatusStr Gitsn_TractionControlStatusStrA
#define Gitsn_TractionControlStatusFromStr Gitsn_TractionControlStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TractionControlStatusStr Gitsn_TractionControlStatusStrA
#define Gitsn_TractionControlStatusFromStr Gitsn_TractionControlStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TractionControlStatus *Gitsn_TractionControlStatus_new(Gitsn_TractionControlStatus *src, Dz1Error *err);
static __inline__ Gitsn_TractionControlStatus *Gitsn_TractionControlStatus_gen(Dz1Error *err) { Gitsn_TractionControlStatus v = Gitsn_TractionControlStatus_max; return Gitsn_TractionControlStatus_new(&v, err); }
static __inline__ void Gitsn_TractionControlStatus_del(Gitsn_TractionControlStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TractionControlStatus_delAndSetNull(void *ptr)
{
	Gitsn_TractionControlStatus **p = (Gitsn_TractionControlStatus **)ptr;
	if (p != NULL) { Gitsn_TractionControlStatus_del(*p); *p = NULL; }
}
// Gitsn_TractionControlStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AntiLockBrakeStatus
typedef enum Gitsn_AntiLockBrakeStatus
{
	Gitsn_AntiLockBrakeStatus_unavailable,
	Gitsn_AntiLockBrakeStatus_off,
	Gitsn_AntiLockBrakeStatus_on,
	Gitsn_AntiLockBrakeStatus_engaged,
	Gitsn_AntiLockBrakeStatus_max
} Gitsn_AntiLockBrakeStatus;

DZ1_CPPLINK str_t Gitsn_AntiLockBrakeStatusStrA(Gitsn_AntiLockBrakeStatus v);
DZ1_CPPLINK Gitsn_AntiLockBrakeStatus Gitsn_AntiLockBrakeStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_AntiLockBrakeStatusStrW(Gitsn_AntiLockBrakeStatus v);
DZ1_CPPLINK Gitsn_AntiLockBrakeStatus Gitsn_AntiLockBrakeStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_AntiLockBrakeStatusStr Gitsn_AntiLockBrakeStatusStrW
#define Gitsn_AntiLockBrakeStatusFromStr Gitsn_AntiLockBrakeStatusFromStrW
#else // UNICODE
#define Gitsn_AntiLockBrakeStatusStr Gitsn_AntiLockBrakeStatusStrA
#define Gitsn_AntiLockBrakeStatusFromStr Gitsn_AntiLockBrakeStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_AntiLockBrakeStatusStr Gitsn_AntiLockBrakeStatusStrA
#define Gitsn_AntiLockBrakeStatusFromStr Gitsn_AntiLockBrakeStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AntiLockBrakeStatus *Gitsn_AntiLockBrakeStatus_new(Gitsn_AntiLockBrakeStatus *src, Dz1Error *err);
static __inline__ Gitsn_AntiLockBrakeStatus *Gitsn_AntiLockBrakeStatus_gen(Dz1Error *err) { Gitsn_AntiLockBrakeStatus v = Gitsn_AntiLockBrakeStatus_max; return Gitsn_AntiLockBrakeStatus_new(&v, err); }
static __inline__ void Gitsn_AntiLockBrakeStatus_del(Gitsn_AntiLockBrakeStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_AntiLockBrakeStatus_delAndSetNull(void *ptr)
{
	Gitsn_AntiLockBrakeStatus **p = (Gitsn_AntiLockBrakeStatus **)ptr;
	if (p != NULL) { Gitsn_AntiLockBrakeStatus_del(*p); *p = NULL; }
}
// Gitsn_AntiLockBrakeStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_StabilityControlStatus
typedef enum Gitsn_StabilityControlStatus
{
	Gitsn_StabilityControlStatus_unavailable,
	Gitsn_StabilityControlStatus_off,
	Gitsn_StabilityControlStatus_on,
	Gitsn_StabilityControlStatus_engaged,
	Gitsn_StabilityControlStatus_max
} Gitsn_StabilityControlStatus;

DZ1_CPPLINK str_t Gitsn_StabilityControlStatusStrA(Gitsn_StabilityControlStatus v);
DZ1_CPPLINK Gitsn_StabilityControlStatus Gitsn_StabilityControlStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_StabilityControlStatusStrW(Gitsn_StabilityControlStatus v);
DZ1_CPPLINK Gitsn_StabilityControlStatus Gitsn_StabilityControlStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_StabilityControlStatusStr Gitsn_StabilityControlStatusStrW
#define Gitsn_StabilityControlStatusFromStr Gitsn_StabilityControlStatusFromStrW
#else // UNICODE
#define Gitsn_StabilityControlStatusStr Gitsn_StabilityControlStatusStrA
#define Gitsn_StabilityControlStatusFromStr Gitsn_StabilityControlStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_StabilityControlStatusStr Gitsn_StabilityControlStatusStrA
#define Gitsn_StabilityControlStatusFromStr Gitsn_StabilityControlStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_StabilityControlStatus *Gitsn_StabilityControlStatus_new(Gitsn_StabilityControlStatus *src, Dz1Error *err);
static __inline__ Gitsn_StabilityControlStatus *Gitsn_StabilityControlStatus_gen(Dz1Error *err) { Gitsn_StabilityControlStatus v = Gitsn_StabilityControlStatus_max; return Gitsn_StabilityControlStatus_new(&v, err); }
static __inline__ void Gitsn_StabilityControlStatus_del(Gitsn_StabilityControlStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_StabilityControlStatus_delAndSetNull(void *ptr)
{
	Gitsn_StabilityControlStatus **p = (Gitsn_StabilityControlStatus **)ptr;
	if (p != NULL) { Gitsn_StabilityControlStatus_del(*p); *p = NULL; }
}
// Gitsn_StabilityControlStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BrakeBoostApplied
typedef enum Gitsn_BrakeBoostApplied
{
	Gitsn_BrakeBoostApplied_unavailable,
	Gitsn_BrakeBoostApplied_off,
	Gitsn_BrakeBoostApplied_on,
	Gitsn_BrakeBoostApplied_max
} Gitsn_BrakeBoostApplied;

DZ1_CPPLINK str_t Gitsn_BrakeBoostAppliedStrA(Gitsn_BrakeBoostApplied v);
DZ1_CPPLINK Gitsn_BrakeBoostApplied Gitsn_BrakeBoostAppliedFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_BrakeBoostAppliedStrW(Gitsn_BrakeBoostApplied v);
DZ1_CPPLINK Gitsn_BrakeBoostApplied Gitsn_BrakeBoostAppliedFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_BrakeBoostAppliedStr Gitsn_BrakeBoostAppliedStrW
#define Gitsn_BrakeBoostAppliedFromStr Gitsn_BrakeBoostAppliedFromStrW
#else // UNICODE
#define Gitsn_BrakeBoostAppliedStr Gitsn_BrakeBoostAppliedStrA
#define Gitsn_BrakeBoostAppliedFromStr Gitsn_BrakeBoostAppliedFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_BrakeBoostAppliedStr Gitsn_BrakeBoostAppliedStrA
#define Gitsn_BrakeBoostAppliedFromStr Gitsn_BrakeBoostAppliedFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_BrakeBoostApplied *Gitsn_BrakeBoostApplied_new(Gitsn_BrakeBoostApplied *src, Dz1Error *err);
static __inline__ Gitsn_BrakeBoostApplied *Gitsn_BrakeBoostApplied_gen(Dz1Error *err) { Gitsn_BrakeBoostApplied v = Gitsn_BrakeBoostApplied_max; return Gitsn_BrakeBoostApplied_new(&v, err); }
static __inline__ void Gitsn_BrakeBoostApplied_del(Gitsn_BrakeBoostApplied *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_BrakeBoostApplied_delAndSetNull(void *ptr)
{
	Gitsn_BrakeBoostApplied **p = (Gitsn_BrakeBoostApplied **)ptr;
	if (p != NULL) { Gitsn_BrakeBoostApplied_del(*p); *p = NULL; }
}
// Gitsn_BrakeBoostApplied
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AuxiliaryBrakeStatus
typedef enum Gitsn_AuxiliaryBrakeStatus
{
	Gitsn_AuxiliaryBrakeStatus_unavailable,
	Gitsn_AuxiliaryBrakeStatus_off,
	Gitsn_AuxiliaryBrakeStatus_on,
	Gitsn_AuxiliaryBrakeStatus_reserved,
	Gitsn_AuxiliaryBrakeStatus_max
} Gitsn_AuxiliaryBrakeStatus;

DZ1_CPPLINK str_t Gitsn_AuxiliaryBrakeStatusStrA(Gitsn_AuxiliaryBrakeStatus v);
DZ1_CPPLINK Gitsn_AuxiliaryBrakeStatus Gitsn_AuxiliaryBrakeStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_AuxiliaryBrakeStatusStrW(Gitsn_AuxiliaryBrakeStatus v);
DZ1_CPPLINK Gitsn_AuxiliaryBrakeStatus Gitsn_AuxiliaryBrakeStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_AuxiliaryBrakeStatusStr Gitsn_AuxiliaryBrakeStatusStrW
#define Gitsn_AuxiliaryBrakeStatusFromStr Gitsn_AuxiliaryBrakeStatusFromStrW
#else // UNICODE
#define Gitsn_AuxiliaryBrakeStatusStr Gitsn_AuxiliaryBrakeStatusStrA
#define Gitsn_AuxiliaryBrakeStatusFromStr Gitsn_AuxiliaryBrakeStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_AuxiliaryBrakeStatusStr Gitsn_AuxiliaryBrakeStatusStrA
#define Gitsn_AuxiliaryBrakeStatusFromStr Gitsn_AuxiliaryBrakeStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AuxiliaryBrakeStatus *Gitsn_AuxiliaryBrakeStatus_new(Gitsn_AuxiliaryBrakeStatus *src, Dz1Error *err);
static __inline__ Gitsn_AuxiliaryBrakeStatus *Gitsn_AuxiliaryBrakeStatus_gen(Dz1Error *err) { Gitsn_AuxiliaryBrakeStatus v = Gitsn_AuxiliaryBrakeStatus_max; return Gitsn_AuxiliaryBrakeStatus_new(&v, err); }
static __inline__ void Gitsn_AuxiliaryBrakeStatus_del(Gitsn_AuxiliaryBrakeStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_AuxiliaryBrakeStatus_delAndSetNull(void *ptr)
{
	Gitsn_AuxiliaryBrakeStatus **p = (Gitsn_AuxiliaryBrakeStatus **)ptr;
	if (p != NULL) { Gitsn_AuxiliaryBrakeStatus_del(*p); *p = NULL; }
}
// Gitsn_AuxiliaryBrakeStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BrakeAppliedPressure
typedef enum Gitsn_BrakeAppliedPressure
{
	Gitsn_BrakeAppliedPressure_unavailable,
	Gitsn_BrakeAppliedPressure_minPressure,
	Gitsn_BrakeAppliedPressure_bkLvl_2,
	Gitsn_BrakeAppliedPressure_bkLvl_3,
	Gitsn_BrakeAppliedPressure_bkLvl_4,
	Gitsn_BrakeAppliedPressure_bkLvl_5,
	Gitsn_BrakeAppliedPressure_bkLvl_6,
	Gitsn_BrakeAppliedPressure_bkLvl_7,
	Gitsn_BrakeAppliedPressure_bkLvl_8,
	Gitsn_BrakeAppliedPressure_bkLvl_9,
	Gitsn_BrakeAppliedPressure_bkLvl_10,
	Gitsn_BrakeAppliedPressure_bkLvl_11,
	Gitsn_BrakeAppliedPressure_bkLvl_12,
	Gitsn_BrakeAppliedPressure_bkLvl_13,
	Gitsn_BrakeAppliedPressure_bkLvl_14,
	Gitsn_BrakeAppliedPressure_maxPressure,
	Gitsn_BrakeAppliedPressure_max
} Gitsn_BrakeAppliedPressure;

DZ1_CPPLINK str_t Gitsn_BrakeAppliedPressureStrA(Gitsn_BrakeAppliedPressure v);
DZ1_CPPLINK Gitsn_BrakeAppliedPressure Gitsn_BrakeAppliedPressureFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_BrakeAppliedPressureStrW(Gitsn_BrakeAppliedPressure v);
DZ1_CPPLINK Gitsn_BrakeAppliedPressure Gitsn_BrakeAppliedPressureFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_BrakeAppliedPressureStr Gitsn_BrakeAppliedPressureStrW
#define Gitsn_BrakeAppliedPressureFromStr Gitsn_BrakeAppliedPressureFromStrW
#else // UNICODE
#define Gitsn_BrakeAppliedPressureStr Gitsn_BrakeAppliedPressureStrA
#define Gitsn_BrakeAppliedPressureFromStr Gitsn_BrakeAppliedPressureFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_BrakeAppliedPressureStr Gitsn_BrakeAppliedPressureStrA
#define Gitsn_BrakeAppliedPressureFromStr Gitsn_BrakeAppliedPressureFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_BrakeAppliedPressure *Gitsn_BrakeAppliedPressure_new(Gitsn_BrakeAppliedPressure *src, Dz1Error *err);
static __inline__ Gitsn_BrakeAppliedPressure *Gitsn_BrakeAppliedPressure_gen(Dz1Error *err) { Gitsn_BrakeAppliedPressure v = Gitsn_BrakeAppliedPressure_max; return Gitsn_BrakeAppliedPressure_new(&v, err); }
static __inline__ void Gitsn_BrakeAppliedPressure_del(Gitsn_BrakeAppliedPressure *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_BrakeAppliedPressure_delAndSetNull(void *ptr)
{
	Gitsn_BrakeAppliedPressure **p = (Gitsn_BrakeAppliedPressure **)ptr;
	if (p != NULL) { Gitsn_BrakeAppliedPressure_del(*p); *p = NULL; }
}
// Gitsn_BrakeAppliedPressure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SteeringWheelAngleConfidence
typedef enum Gitsn_SteeringWheelAngleConfidence
{
	Gitsn_SteeringWheelAngleConfidence_unavailable,
	Gitsn_SteeringWheelAngleConfidence_prec2deg,
	Gitsn_SteeringWheelAngleConfidence_prec1deg,
	Gitsn_SteeringWheelAngleConfidence_prec0_02deg,
	Gitsn_SteeringWheelAngleConfidence_max
} Gitsn_SteeringWheelAngleConfidence;

DZ1_CPPLINK str_t Gitsn_SteeringWheelAngleConfidenceStrA(Gitsn_SteeringWheelAngleConfidence v);
DZ1_CPPLINK Gitsn_SteeringWheelAngleConfidence Gitsn_SteeringWheelAngleConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SteeringWheelAngleConfidenceStrW(Gitsn_SteeringWheelAngleConfidence v);
DZ1_CPPLINK Gitsn_SteeringWheelAngleConfidence Gitsn_SteeringWheelAngleConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SteeringWheelAngleConfidenceStr Gitsn_SteeringWheelAngleConfidenceStrW
#define Gitsn_SteeringWheelAngleConfidenceFromStr Gitsn_SteeringWheelAngleConfidenceFromStrW
#else // UNICODE
#define Gitsn_SteeringWheelAngleConfidenceStr Gitsn_SteeringWheelAngleConfidenceStrA
#define Gitsn_SteeringWheelAngleConfidenceFromStr Gitsn_SteeringWheelAngleConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SteeringWheelAngleConfidenceStr Gitsn_SteeringWheelAngleConfidenceStrA
#define Gitsn_SteeringWheelAngleConfidenceFromStr Gitsn_SteeringWheelAngleConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SteeringWheelAngleConfidence *Gitsn_SteeringWheelAngleConfidence_new(Gitsn_SteeringWheelAngleConfidence *src, Dz1Error *err);
static __inline__ Gitsn_SteeringWheelAngleConfidence *Gitsn_SteeringWheelAngleConfidence_gen(Dz1Error *err) { Gitsn_SteeringWheelAngleConfidence v = Gitsn_SteeringWheelAngleConfidence_max; return Gitsn_SteeringWheelAngleConfidence_new(&v, err); }
static __inline__ void Gitsn_SteeringWheelAngleConfidence_del(Gitsn_SteeringWheelAngleConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SteeringWheelAngleConfidence_delAndSetNull(void *ptr)
{
	Gitsn_SteeringWheelAngleConfidence **p = (Gitsn_SteeringWheelAngleConfidence **)ptr;
	if (p != NULL) { Gitsn_SteeringWheelAngleConfidence_del(*p); *p = NULL; }
}
// Gitsn_SteeringWheelAngleConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_YawRateConfidence
typedef enum Gitsn_YawRateConfidence
{
	Gitsn_YawRateConfidence_unavailable,
	Gitsn_YawRateConfidence_degSec_100_00,
	Gitsn_YawRateConfidence_degSec_010_00,
	Gitsn_YawRateConfidence_degSec_005_00,
	Gitsn_YawRateConfidence_degSec_001_00,
	Gitsn_YawRateConfidence_degSec_000_10,
	Gitsn_YawRateConfidence_degSec_000_05,
	Gitsn_YawRateConfidence_degSec_000_01,
	Gitsn_YawRateConfidence_max
} Gitsn_YawRateConfidence;

DZ1_CPPLINK str_t Gitsn_YawRateConfidenceStrA(Gitsn_YawRateConfidence v);
DZ1_CPPLINK Gitsn_YawRateConfidence Gitsn_YawRateConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_YawRateConfidenceStrW(Gitsn_YawRateConfidence v);
DZ1_CPPLINK Gitsn_YawRateConfidence Gitsn_YawRateConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_YawRateConfidenceStr Gitsn_YawRateConfidenceStrW
#define Gitsn_YawRateConfidenceFromStr Gitsn_YawRateConfidenceFromStrW
#else // UNICODE
#define Gitsn_YawRateConfidenceStr Gitsn_YawRateConfidenceStrA
#define Gitsn_YawRateConfidenceFromStr Gitsn_YawRateConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_YawRateConfidenceStr Gitsn_YawRateConfidenceStrA
#define Gitsn_YawRateConfidenceFromStr Gitsn_YawRateConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_YawRateConfidence *Gitsn_YawRateConfidence_new(Gitsn_YawRateConfidence *src, Dz1Error *err);
static __inline__ Gitsn_YawRateConfidence *Gitsn_YawRateConfidence_gen(Dz1Error *err) { Gitsn_YawRateConfidence v = Gitsn_YawRateConfidence_max; return Gitsn_YawRateConfidence_new(&v, err); }
static __inline__ void Gitsn_YawRateConfidence_del(Gitsn_YawRateConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_YawRateConfidence_delAndSetNull(void *ptr)
{
	Gitsn_YawRateConfidence **p = (Gitsn_YawRateConfidence **)ptr;
	if (p != NULL) { Gitsn_YawRateConfidence_del(*p); *p = NULL; }
}
// Gitsn_YawRateConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AccelerationConfidence
typedef enum Gitsn_AccelerationConfidence
{
	Gitsn_AccelerationConfidence_unavailable,
	Gitsn_AccelerationConfidence_accl_100_00,
	Gitsn_AccelerationConfidence_accl_010_00,
	Gitsn_AccelerationConfidence_accl_005_00,
	Gitsn_AccelerationConfidence_accl_001_00,
	Gitsn_AccelerationConfidence_accl_000_10,
	Gitsn_AccelerationConfidence_accl_000_05,
	Gitsn_AccelerationConfidence_accl_000_01,
	Gitsn_AccelerationConfidence_max
} Gitsn_AccelerationConfidence;

DZ1_CPPLINK str_t Gitsn_AccelerationConfidenceStrA(Gitsn_AccelerationConfidence v);
DZ1_CPPLINK Gitsn_AccelerationConfidence Gitsn_AccelerationConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_AccelerationConfidenceStrW(Gitsn_AccelerationConfidence v);
DZ1_CPPLINK Gitsn_AccelerationConfidence Gitsn_AccelerationConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_AccelerationConfidenceStr Gitsn_AccelerationConfidenceStrW
#define Gitsn_AccelerationConfidenceFromStr Gitsn_AccelerationConfidenceFromStrW
#else // UNICODE
#define Gitsn_AccelerationConfidenceStr Gitsn_AccelerationConfidenceStrA
#define Gitsn_AccelerationConfidenceFromStr Gitsn_AccelerationConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_AccelerationConfidenceStr Gitsn_AccelerationConfidenceStrA
#define Gitsn_AccelerationConfidenceFromStr Gitsn_AccelerationConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AccelerationConfidence *Gitsn_AccelerationConfidence_new(Gitsn_AccelerationConfidence *src, Dz1Error *err);
static __inline__ Gitsn_AccelerationConfidence *Gitsn_AccelerationConfidence_gen(Dz1Error *err) { Gitsn_AccelerationConfidence v = Gitsn_AccelerationConfidence_max; return Gitsn_AccelerationConfidence_new(&v, err); }
static __inline__ void Gitsn_AccelerationConfidence_del(Gitsn_AccelerationConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_AccelerationConfidence_delAndSetNull(void *ptr)
{
	Gitsn_AccelerationConfidence **p = (Gitsn_AccelerationConfidence **)ptr;
	if (p != NULL) { Gitsn_AccelerationConfidence_del(*p); *p = NULL; }
}
// Gitsn_AccelerationConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WheelSensorStatus
typedef enum Gitsn_WheelSensorStatus
{
	Gitsn_WheelSensorStatus_off,
	Gitsn_WheelSensorStatus_on,
	Gitsn_WheelSensorStatus_notDefined,
	Gitsn_WheelSensorStatus_notSupported,
	Gitsn_WheelSensorStatus_max
} Gitsn_WheelSensorStatus;

DZ1_CPPLINK str_t Gitsn_WheelSensorStatusStrA(Gitsn_WheelSensorStatus v);
DZ1_CPPLINK Gitsn_WheelSensorStatus Gitsn_WheelSensorStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_WheelSensorStatusStrW(Gitsn_WheelSensorStatus v);
DZ1_CPPLINK Gitsn_WheelSensorStatus Gitsn_WheelSensorStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_WheelSensorStatusStr Gitsn_WheelSensorStatusStrW
#define Gitsn_WheelSensorStatusFromStr Gitsn_WheelSensorStatusFromStrW
#else // UNICODE
#define Gitsn_WheelSensorStatusStr Gitsn_WheelSensorStatusStrA
#define Gitsn_WheelSensorStatusFromStr Gitsn_WheelSensorStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_WheelSensorStatusStr Gitsn_WheelSensorStatusStrA
#define Gitsn_WheelSensorStatusFromStr Gitsn_WheelSensorStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_WheelSensorStatus *Gitsn_WheelSensorStatus_new(Gitsn_WheelSensorStatus *src, Dz1Error *err);
static __inline__ Gitsn_WheelSensorStatus *Gitsn_WheelSensorStatus_gen(Dz1Error *err) { Gitsn_WheelSensorStatus v = Gitsn_WheelSensorStatus_max; return Gitsn_WheelSensorStatus_new(&v, err); }
static __inline__ void Gitsn_WheelSensorStatus_del(Gitsn_WheelSensorStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_WheelSensorStatus_delAndSetNull(void *ptr)
{
	Gitsn_WheelSensorStatus **p = (Gitsn_WheelSensorStatus **)ptr;
	if (p != NULL) { Gitsn_WheelSensorStatus_del(*p); *p = NULL; }
}
// Gitsn_WheelSensorStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WheelEndElectFault
typedef enum Gitsn_WheelEndElectFault
{
	Gitsn_WheelEndElectFault_isOk,
	Gitsn_WheelEndElectFault_isNotDefined,
	Gitsn_WheelEndElectFault_isError,
	Gitsn_WheelEndElectFault_isNotSupported,
	Gitsn_WheelEndElectFault_max
} Gitsn_WheelEndElectFault;

DZ1_CPPLINK str_t Gitsn_WheelEndElectFaultStrA(Gitsn_WheelEndElectFault v);
DZ1_CPPLINK Gitsn_WheelEndElectFault Gitsn_WheelEndElectFaultFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_WheelEndElectFaultStrW(Gitsn_WheelEndElectFault v);
DZ1_CPPLINK Gitsn_WheelEndElectFault Gitsn_WheelEndElectFaultFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_WheelEndElectFaultStr Gitsn_WheelEndElectFaultStrW
#define Gitsn_WheelEndElectFaultFromStr Gitsn_WheelEndElectFaultFromStrW
#else // UNICODE
#define Gitsn_WheelEndElectFaultStr Gitsn_WheelEndElectFaultStrA
#define Gitsn_WheelEndElectFaultFromStr Gitsn_WheelEndElectFaultFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_WheelEndElectFaultStr Gitsn_WheelEndElectFaultStrA
#define Gitsn_WheelEndElectFaultFromStr Gitsn_WheelEndElectFaultFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_WheelEndElectFault *Gitsn_WheelEndElectFault_new(Gitsn_WheelEndElectFault *src, Dz1Error *err);
static __inline__ Gitsn_WheelEndElectFault *Gitsn_WheelEndElectFault_gen(Dz1Error *err) { Gitsn_WheelEndElectFault v = Gitsn_WheelEndElectFault_max; return Gitsn_WheelEndElectFault_new(&v, err); }
static __inline__ void Gitsn_WheelEndElectFault_del(Gitsn_WheelEndElectFault *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_WheelEndElectFault_delAndSetNull(void *ptr)
{
	Gitsn_WheelEndElectFault **p = (Gitsn_WheelEndElectFault **)ptr;
	if (p != NULL) { Gitsn_WheelEndElectFault_del(*p); *p = NULL; }
}
// Gitsn_WheelEndElectFault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TirePressureThresholdDetection
typedef enum Gitsn_TirePressureThresholdDetection
{
	Gitsn_TirePressureThresholdDetection_noData,
	Gitsn_TirePressureThresholdDetection_overPressure,
	Gitsn_TirePressureThresholdDetection_noWarningPressure,
	Gitsn_TirePressureThresholdDetection_underPressure,
	Gitsn_TirePressureThresholdDetection_extremeUnderPressure,
	Gitsn_TirePressureThresholdDetection_undefined,
	Gitsn_TirePressureThresholdDetection_errorIndicator,
	Gitsn_TirePressureThresholdDetection_notAvailable,
	Gitsn_TirePressureThresholdDetection_max
} Gitsn_TirePressureThresholdDetection;

DZ1_CPPLINK str_t Gitsn_TirePressureThresholdDetectionStrA(Gitsn_TirePressureThresholdDetection v);
DZ1_CPPLINK Gitsn_TirePressureThresholdDetection Gitsn_TirePressureThresholdDetectionFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TirePressureThresholdDetectionStrW(Gitsn_TirePressureThresholdDetection v);
DZ1_CPPLINK Gitsn_TirePressureThresholdDetection Gitsn_TirePressureThresholdDetectionFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TirePressureThresholdDetectionStr Gitsn_TirePressureThresholdDetectionStrW
#define Gitsn_TirePressureThresholdDetectionFromStr Gitsn_TirePressureThresholdDetectionFromStrW
#else // UNICODE
#define Gitsn_TirePressureThresholdDetectionStr Gitsn_TirePressureThresholdDetectionStrA
#define Gitsn_TirePressureThresholdDetectionFromStr Gitsn_TirePressureThresholdDetectionFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TirePressureThresholdDetectionStr Gitsn_TirePressureThresholdDetectionStrA
#define Gitsn_TirePressureThresholdDetectionFromStr Gitsn_TirePressureThresholdDetectionFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TirePressureThresholdDetection *Gitsn_TirePressureThresholdDetection_new(Gitsn_TirePressureThresholdDetection *src, Dz1Error *err);
static __inline__ Gitsn_TirePressureThresholdDetection *Gitsn_TirePressureThresholdDetection_gen(Dz1Error *err) { Gitsn_TirePressureThresholdDetection v = Gitsn_TirePressureThresholdDetection_max; return Gitsn_TirePressureThresholdDetection_new(&v, err); }
static __inline__ void Gitsn_TirePressureThresholdDetection_del(Gitsn_TirePressureThresholdDetection *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TirePressureThresholdDetection_delAndSetNull(void *ptr)
{
	Gitsn_TirePressureThresholdDetection **p = (Gitsn_TirePressureThresholdDetection **)ptr;
	if (p != NULL) { Gitsn_TirePressureThresholdDetection_del(*p); *p = NULL; }
}
// Gitsn_TirePressureThresholdDetection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EssPrecipYesNo
typedef enum Gitsn_EssPrecipYesNo
{
	Gitsn_EssPrecipYesNo_EssPrecipYesNo_precip = 1,
	Gitsn_EssPrecipYesNo_EssPrecipYesNo_noPrecip,
	Gitsn_EssPrecipYesNo_EssPrecipYesNo_error,
	Gitsn_EssPrecipYesNo_max
} Gitsn_EssPrecipYesNo;

DZ1_CPPLINK str_t Gitsn_EssPrecipYesNoStrA(Gitsn_EssPrecipYesNo v);
DZ1_CPPLINK Gitsn_EssPrecipYesNo Gitsn_EssPrecipYesNoFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_EssPrecipYesNoStrW(Gitsn_EssPrecipYesNo v);
DZ1_CPPLINK Gitsn_EssPrecipYesNo Gitsn_EssPrecipYesNoFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_EssPrecipYesNoStr Gitsn_EssPrecipYesNoStrW
#define Gitsn_EssPrecipYesNoFromStr Gitsn_EssPrecipYesNoFromStrW
#else // UNICODE
#define Gitsn_EssPrecipYesNoStr Gitsn_EssPrecipYesNoStrA
#define Gitsn_EssPrecipYesNoFromStr Gitsn_EssPrecipYesNoFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_EssPrecipYesNoStr Gitsn_EssPrecipYesNoStrA
#define Gitsn_EssPrecipYesNoFromStr Gitsn_EssPrecipYesNoFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_EssPrecipYesNo *Gitsn_EssPrecipYesNo_new(Gitsn_EssPrecipYesNo *src, Dz1Error *err);
static __inline__ Gitsn_EssPrecipYesNo *Gitsn_EssPrecipYesNo_gen(Dz1Error *err) { Gitsn_EssPrecipYesNo v = Gitsn_EssPrecipYesNo_max; return Gitsn_EssPrecipYesNo_new(&v, err); }
static __inline__ void Gitsn_EssPrecipYesNo_del(Gitsn_EssPrecipYesNo *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_EssPrecipYesNo_delAndSetNull(void *ptr)
{
	Gitsn_EssPrecipYesNo **p = (Gitsn_EssPrecipYesNo **)ptr;
	if (p != NULL) { Gitsn_EssPrecipYesNo_del(*p); *p = NULL; }
}
// Gitsn_EssPrecipYesNo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EssPrecipSituation
typedef enum Gitsn_EssPrecipSituation
{
	Gitsn_EssPrecipSituation_EssPrecipSituation_other = 1,
	Gitsn_EssPrecipSituation_EssPrecipSituation_unknown,
	Gitsn_EssPrecipSituation_EssPrecipSituation_noPrecipitation,
	Gitsn_EssPrecipSituation_EssPrecipSituation_unidentifiedSlight,
	Gitsn_EssPrecipSituation_EssPrecipSituation_unidentifiedModerate,
	Gitsn_EssPrecipSituation_EssPrecipSituation_unidentifiedHeavy,
	Gitsn_EssPrecipSituation_EssPrecipSituation_snowSlight,
	Gitsn_EssPrecipSituation_EssPrecipSituation_snowModerate,
	Gitsn_EssPrecipSituation_EssPrecipSituation_snowHeavy,
	Gitsn_EssPrecipSituation_EssPrecipSituation_rainSlight,
	Gitsn_EssPrecipSituation_EssPrecipSituation_rainModerate,
	Gitsn_EssPrecipSituation_EssPrecipSituation_rainHeavy,
	Gitsn_EssPrecipSituation_EssPrecipSituation_frozenPrecipitationSlight,
	Gitsn_EssPrecipSituation_EssPrecipSituation_frozenPrecipitationModerate,
	Gitsn_EssPrecipSituation_EssPrecipSituation_frozenPrecipitationHeavy,
	Gitsn_EssPrecipSituation_max
} Gitsn_EssPrecipSituation;

DZ1_CPPLINK str_t Gitsn_EssPrecipSituationStrA(Gitsn_EssPrecipSituation v);
DZ1_CPPLINK Gitsn_EssPrecipSituation Gitsn_EssPrecipSituationFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_EssPrecipSituationStrW(Gitsn_EssPrecipSituation v);
DZ1_CPPLINK Gitsn_EssPrecipSituation Gitsn_EssPrecipSituationFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_EssPrecipSituationStr Gitsn_EssPrecipSituationStrW
#define Gitsn_EssPrecipSituationFromStr Gitsn_EssPrecipSituationFromStrW
#else // UNICODE
#define Gitsn_EssPrecipSituationStr Gitsn_EssPrecipSituationStrA
#define Gitsn_EssPrecipSituationFromStr Gitsn_EssPrecipSituationFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_EssPrecipSituationStr Gitsn_EssPrecipSituationStrA
#define Gitsn_EssPrecipSituationFromStr Gitsn_EssPrecipSituationFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_EssPrecipSituation *Gitsn_EssPrecipSituation_new(Gitsn_EssPrecipSituation *src, Dz1Error *err);
static __inline__ Gitsn_EssPrecipSituation *Gitsn_EssPrecipSituation_gen(Dz1Error *err) { Gitsn_EssPrecipSituation v = Gitsn_EssPrecipSituation_max; return Gitsn_EssPrecipSituation_new(&v, err); }
static __inline__ void Gitsn_EssPrecipSituation_del(Gitsn_EssPrecipSituation *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_EssPrecipSituation_delAndSetNull(void *ptr)
{
	Gitsn_EssPrecipSituation **p = (Gitsn_EssPrecipSituation **)ptr;
	if (p != NULL) { Gitsn_EssPrecipSituation_del(*p); *p = NULL; }
}
// Gitsn_EssPrecipSituation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LayerType
typedef enum Gitsn_LayerType
{
	Gitsn_LayerType_none,
	Gitsn_LayerType_mixedContent,
	Gitsn_LayerType_generalMapData,
	Gitsn_LayerType_intersectionData,
	Gitsn_LayerType_curveData,
	Gitsn_LayerType_roadwaySectionData,
	Gitsn_LayerType_parkingAreaData,
	Gitsn_LayerType_sharedLaneData,
	Gitsn_LayerType_max
} Gitsn_LayerType;

DZ1_CPPLINK str_t Gitsn_LayerTypeStrA(Gitsn_LayerType v);
DZ1_CPPLINK Gitsn_LayerType Gitsn_LayerTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_LayerTypeStrW(Gitsn_LayerType v);
DZ1_CPPLINK Gitsn_LayerType Gitsn_LayerTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_LayerTypeStr Gitsn_LayerTypeStrW
#define Gitsn_LayerTypeFromStr Gitsn_LayerTypeFromStrW
#else // UNICODE
#define Gitsn_LayerTypeStr Gitsn_LayerTypeStrA
#define Gitsn_LayerTypeFromStr Gitsn_LayerTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_LayerTypeStr Gitsn_LayerTypeStrA
#define Gitsn_LayerTypeFromStr Gitsn_LayerTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LayerType *Gitsn_LayerType_new(Gitsn_LayerType *src, Dz1Error *err);
static __inline__ Gitsn_LayerType *Gitsn_LayerType_gen(Dz1Error *err) { Gitsn_LayerType v = Gitsn_LayerType_max; return Gitsn_LayerType_new(&v, err); }
static __inline__ void Gitsn_LayerType_del(Gitsn_LayerType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_LayerType_delAndSetNull(void *ptr)
{
	Gitsn_LayerType **p = (Gitsn_LayerType **)ptr;
	if (p != NULL) { Gitsn_LayerType_del(*p); *p = NULL; }
}
// Gitsn_LayerType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimitType
typedef enum Gitsn_SpeedLimitType
{
	Gitsn_SpeedLimitType_unknown,
	Gitsn_SpeedLimitType_maxSpeedInSchoolZone,
	Gitsn_SpeedLimitType_maxSpeedInSchoolZoneWhenChildrenArePresent,
	Gitsn_SpeedLimitType_maxSpeedInConstructionZone,
	Gitsn_SpeedLimitType_vehicleMinSpeed,
	Gitsn_SpeedLimitType_vehicleMaxSpeed,
	Gitsn_SpeedLimitType_vehicleNightMaxSpeed,
	Gitsn_SpeedLimitType_truckMinSpeed,
	Gitsn_SpeedLimitType_truckMaxSpeed,
	Gitsn_SpeedLimitType_truckNightMaxSpeed,
	Gitsn_SpeedLimitType_vehicleWithTrailersMinSpeed,
	Gitsn_SpeedLimitType_vehicleWithTrailersMaxSpeed,
	Gitsn_SpeedLimitType_vehicleWithTrailersNightMaxSpeed,
	Gitsn_SpeedLimitType_max
} Gitsn_SpeedLimitType;

DZ1_CPPLINK str_t Gitsn_SpeedLimitTypeStrA(Gitsn_SpeedLimitType v);
DZ1_CPPLINK Gitsn_SpeedLimitType Gitsn_SpeedLimitTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SpeedLimitTypeStrW(Gitsn_SpeedLimitType v);
DZ1_CPPLINK Gitsn_SpeedLimitType Gitsn_SpeedLimitTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SpeedLimitTypeStr Gitsn_SpeedLimitTypeStrW
#define Gitsn_SpeedLimitTypeFromStr Gitsn_SpeedLimitTypeFromStrW
#else // UNICODE
#define Gitsn_SpeedLimitTypeStr Gitsn_SpeedLimitTypeStrA
#define Gitsn_SpeedLimitTypeFromStr Gitsn_SpeedLimitTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SpeedLimitTypeStr Gitsn_SpeedLimitTypeStrA
#define Gitsn_SpeedLimitTypeFromStr Gitsn_SpeedLimitTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimitType *Gitsn_SpeedLimitType_new(Gitsn_SpeedLimitType *src, Dz1Error *err);
static __inline__ Gitsn_SpeedLimitType *Gitsn_SpeedLimitType_gen(Dz1Error *err) { Gitsn_SpeedLimitType v = Gitsn_SpeedLimitType_max; return Gitsn_SpeedLimitType_new(&v, err); }
static __inline__ void Gitsn_SpeedLimitType_del(Gitsn_SpeedLimitType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SpeedLimitType_delAndSetNull(void *ptr)
{
	Gitsn_SpeedLimitType **p = (Gitsn_SpeedLimitType **)ptr;
	if (p != NULL) { Gitsn_SpeedLimitType_del(*p); *p = NULL; }
}
// Gitsn_SpeedLimitType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeXY
typedef enum Gitsn_NodeAttributeXY
{
	Gitsn_NodeAttributeXY_reversed,
	Gitsn_NodeAttributeXY_stopLine,
	Gitsn_NodeAttributeXY_roundedCapStyleA,
	Gitsn_NodeAttributeXY_roundedCapStyleB,
	Gitsn_NodeAttributeXY_mergePoint,
	Gitsn_NodeAttributeXY_divergePoint,
	Gitsn_NodeAttributeXY_downstreamStopLine,
	Gitsn_NodeAttributeXY_downstreamStartNode,
	Gitsn_NodeAttributeXY_closedToTraffic,
	Gitsn_NodeAttributeXY_safeIsland,
	Gitsn_NodeAttributeXY_curbPresentAtStepOff,
	Gitsn_NodeAttributeXY_hydrantPresent,
	Gitsn_NodeAttributeXY_max
} Gitsn_NodeAttributeXY;

DZ1_CPPLINK str_t Gitsn_NodeAttributeXYStrA(Gitsn_NodeAttributeXY v);
DZ1_CPPLINK Gitsn_NodeAttributeXY Gitsn_NodeAttributeXYFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NodeAttributeXYStrW(Gitsn_NodeAttributeXY v);
DZ1_CPPLINK Gitsn_NodeAttributeXY Gitsn_NodeAttributeXYFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NodeAttributeXYStr Gitsn_NodeAttributeXYStrW
#define Gitsn_NodeAttributeXYFromStr Gitsn_NodeAttributeXYFromStrW
#else // UNICODE
#define Gitsn_NodeAttributeXYStr Gitsn_NodeAttributeXYStrA
#define Gitsn_NodeAttributeXYFromStr Gitsn_NodeAttributeXYFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NodeAttributeXYStr Gitsn_NodeAttributeXYStrA
#define Gitsn_NodeAttributeXYFromStr Gitsn_NodeAttributeXYFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeXY *Gitsn_NodeAttributeXY_new(Gitsn_NodeAttributeXY *src, Dz1Error *err);
static __inline__ Gitsn_NodeAttributeXY *Gitsn_NodeAttributeXY_gen(Dz1Error *err) { Gitsn_NodeAttributeXY v = Gitsn_NodeAttributeXY_max; return Gitsn_NodeAttributeXY_new(&v, err); }
#define Gitsn_NodeAttributeXY_clone             Gitsn_NodeAttributeXY_new
static __inline__ void Gitsn_NodeAttributeXY_del(Gitsn_NodeAttributeXY *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_NodeAttributeXY_delAndSetNull(void *ptr)
{
	Gitsn_NodeAttributeXY **p = (Gitsn_NodeAttributeXY **)ptr;
	if (p != NULL) { Gitsn_NodeAttributeXY_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeXY_dump(Gitsn_NodeAttributeXY *v, int tab);
// Gitsn_NodeAttributeXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SegmentAttributeXY
typedef enum Gitsn_SegmentAttributeXY
{
	Gitsn_SegmentAttributeXY_reserved,
	Gitsn_SegmentAttributeXY_doNotBlock,
	Gitsn_SegmentAttributeXY_whiteLine,
	Gitsn_SegmentAttributeXY_mergingLaneLeft,
	Gitsn_SegmentAttributeXY_megingLaneRight,
	Gitsn_SegmentAttributeXY_curbOnLeft,
	Gitsn_SegmentAttributeXY_curbOnRight,
	Gitsn_SegmentAttributeXY_loadingzoneOnLeft,
	Gitsn_SegmentAttributeXY_loadingzoneOnRight,
	Gitsn_SegmentAttributeXY_turnOutPointOnLeft,
	Gitsn_SegmentAttributeXY_turnOutPointOnRight,
	Gitsn_SegmentAttributeXY_adjacentBikeLaneOnLeft,
	Gitsn_SegmentAttributeXY_adjacentBikeLaneOnRight,
	Gitsn_SegmentAttributeXY_sharedBikeLane,
	Gitsn_SegmentAttributeXY_bikeBoxInFront,
	Gitsn_SegmentAttributeXY_transitStopOnLeft,
	Gitsn_SegmentAttributeXY_transitStopOnRight,
	Gitsn_SegmentAttributeXY_transitStopInLane,
	Gitsn_SegmentAttributeXY_sharedWithTrackedVehicle,
	Gitsn_SegmentAttributeXY_safeIsland,
	Gitsn_SegmentAttributeXY_lowCurbsPresent,
	Gitsn_SegmentAttributeXY_rumbleStipPresent,
	Gitsn_SegmentAttributeXY_audibleSignalingPresent,
	Gitsn_SegmentAttributeXY_adaptiveTimingPresent,
	Gitsn_SegmentAttributeXY_rfSignalRequestPresent,
	Gitsn_SegmentAttributeXY_partialCurbIntrusion,
	Gitsn_SegmentAttributeXY_taperToLeft,
	Gitsn_SegmentAttributeXY_taperToRight,
	Gitsn_SegmentAttributeXY_taperToCenterLine,
	Gitsn_SegmentAttributeXY_parallelParking,
	Gitsn_SegmentAttributeXY_headInParking,
	Gitsn_SegmentAttributeXY_freeParking,
	Gitsn_SegmentAttributeXY_timeRestrictionsOnParking,
	Gitsn_SegmentAttributeXY_constToPark,
	Gitsn_SegmentAttributeXY_midBlockCurbPresent,
	Gitsn_SegmentAttributeXY_unEvenPavementPresent,
	Gitsn_SegmentAttributeXY_max
} Gitsn_SegmentAttributeXY;

DZ1_CPPLINK str_t Gitsn_SegmentAttributeXYStrA(Gitsn_SegmentAttributeXY v);
DZ1_CPPLINK Gitsn_SegmentAttributeXY Gitsn_SegmentAttributeXYFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SegmentAttributeXYStrW(Gitsn_SegmentAttributeXY v);
DZ1_CPPLINK Gitsn_SegmentAttributeXY Gitsn_SegmentAttributeXYFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SegmentAttributeXYStr Gitsn_SegmentAttributeXYStrW
#define Gitsn_SegmentAttributeXYFromStr Gitsn_SegmentAttributeXYFromStrW
#else // UNICODE
#define Gitsn_SegmentAttributeXYStr Gitsn_SegmentAttributeXYStrA
#define Gitsn_SegmentAttributeXYFromStr Gitsn_SegmentAttributeXYFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SegmentAttributeXYStr Gitsn_SegmentAttributeXYStrA
#define Gitsn_SegmentAttributeXYFromStr Gitsn_SegmentAttributeXYFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SegmentAttributeXY *Gitsn_SegmentAttributeXY_new(Gitsn_SegmentAttributeXY *src, Dz1Error *err);
static __inline__ Gitsn_SegmentAttributeXY *Gitsn_SegmentAttributeXY_gen(Dz1Error *err) { Gitsn_SegmentAttributeXY v = Gitsn_SegmentAttributeXY_max; return Gitsn_SegmentAttributeXY_new(&v, err); }
#define Gitsn_SegmentAttributeXY_clone             Gitsn_SegmentAttributeXY_new
static __inline__ void Gitsn_SegmentAttributeXY_del(Gitsn_SegmentAttributeXY *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SegmentAttributeXY_delAndSetNull(void *ptr)
{
	Gitsn_SegmentAttributeXY **p = (Gitsn_SegmentAttributeXY **)ptr;
	if (p != NULL) { Gitsn_SegmentAttributeXY_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SegmentAttributeXY_dump(Gitsn_SegmentAttributeXY *v, int tab);
// Gitsn_SegmentAttributeXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionAppliesTo
typedef enum Gitsn_RestrictionAppliesTo
{
	Gitsn_RestrictionAppliesTo_none,
	Gitsn_RestrictionAppliesTo_equippedTransit,
	Gitsn_RestrictionAppliesTo_equippedTaxis,
	Gitsn_RestrictionAppliesTo_equippedOther,
	Gitsn_RestrictionAppliesTo_emissionCompliant,
	Gitsn_RestrictionAppliesTo_equippedBicycle,
	Gitsn_RestrictionAppliesTo_weightCompliant,
	Gitsn_RestrictionAppliesTo_heightCompliant,
	Gitsn_RestrictionAppliesTo_pedestrians,
	Gitsn_RestrictionAppliesTo_slowMovingPersons,
	Gitsn_RestrictionAppliesTo_wheelchairUsers,
	Gitsn_RestrictionAppliesTo_visualDisabilities,
	Gitsn_RestrictionAppliesTo_audioDisabilities,
	Gitsn_RestrictionAppliesTo_otherUnknownDisabilities,
	Gitsn_RestrictionAppliesTo_max
} Gitsn_RestrictionAppliesTo;

DZ1_CPPLINK str_t Gitsn_RestrictionAppliesToStrA(Gitsn_RestrictionAppliesTo v);
DZ1_CPPLINK Gitsn_RestrictionAppliesTo Gitsn_RestrictionAppliesToFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_RestrictionAppliesToStrW(Gitsn_RestrictionAppliesTo v);
DZ1_CPPLINK Gitsn_RestrictionAppliesTo Gitsn_RestrictionAppliesToFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_RestrictionAppliesToStr Gitsn_RestrictionAppliesToStrW
#define Gitsn_RestrictionAppliesToFromStr Gitsn_RestrictionAppliesToFromStrW
#else // UNICODE
#define Gitsn_RestrictionAppliesToStr Gitsn_RestrictionAppliesToStrA
#define Gitsn_RestrictionAppliesToFromStr Gitsn_RestrictionAppliesToFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_RestrictionAppliesToStr Gitsn_RestrictionAppliesToStrA
#define Gitsn_RestrictionAppliesToFromStr Gitsn_RestrictionAppliesToFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionAppliesTo *Gitsn_RestrictionAppliesTo_new(Gitsn_RestrictionAppliesTo *src, Dz1Error *err);
static __inline__ Gitsn_RestrictionAppliesTo *Gitsn_RestrictionAppliesTo_gen(Dz1Error *err) { Gitsn_RestrictionAppliesTo v = Gitsn_RestrictionAppliesTo_max; return Gitsn_RestrictionAppliesTo_new(&v, err); }
static __inline__ void Gitsn_RestrictionAppliesTo_del(Gitsn_RestrictionAppliesTo *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_RestrictionAppliesTo_delAndSetNull(void *ptr)
{
	Gitsn_RestrictionAppliesTo **p = (Gitsn_RestrictionAppliesTo **)ptr;
	if (p != NULL) { Gitsn_RestrictionAppliesTo_del(*p); *p = NULL; }
}
// Gitsn_RestrictionAppliesTo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementPhaseState
typedef enum Gitsn_MovementPhaseState
{
	Gitsn_MovementPhaseState_unavailable,
	Gitsn_MovementPhaseState_dark,
	Gitsn_MovementPhaseState_stop_Then_Proceed,
	Gitsn_MovementPhaseState_stop_And_Remain,
	Gitsn_MovementPhaseState_pre_Movement,
	Gitsn_MovementPhaseState_permissive_Movement_Allowed,
	Gitsn_MovementPhaseState_protected_Movement_Allowed,
	Gitsn_MovementPhaseState_permissive_clearance,
	Gitsn_MovementPhaseState_protected_clearance,
	Gitsn_MovementPhaseState_caution_Conflicting_Traffic,
	Gitsn_MovementPhaseState_max
} Gitsn_MovementPhaseState;

DZ1_CPPLINK str_t Gitsn_MovementPhaseStateStrA(Gitsn_MovementPhaseState v);
DZ1_CPPLINK Gitsn_MovementPhaseState Gitsn_MovementPhaseStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_MovementPhaseStateStrW(Gitsn_MovementPhaseState v);
DZ1_CPPLINK Gitsn_MovementPhaseState Gitsn_MovementPhaseStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_MovementPhaseStateStr Gitsn_MovementPhaseStateStrW
#define Gitsn_MovementPhaseStateFromStr Gitsn_MovementPhaseStateFromStrW
#else // UNICODE
#define Gitsn_MovementPhaseStateStr Gitsn_MovementPhaseStateStrA
#define Gitsn_MovementPhaseStateFromStr Gitsn_MovementPhaseStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_MovementPhaseStateStr Gitsn_MovementPhaseStateStrA
#define Gitsn_MovementPhaseStateFromStr Gitsn_MovementPhaseStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementPhaseState *Gitsn_MovementPhaseState_new(Gitsn_MovementPhaseState *src, Dz1Error *err);
static __inline__ Gitsn_MovementPhaseState *Gitsn_MovementPhaseState_gen(Dz1Error *err) { Gitsn_MovementPhaseState v = Gitsn_MovementPhaseState_max; return Gitsn_MovementPhaseState_new(&v, err); }
static __inline__ void Gitsn_MovementPhaseState_del(Gitsn_MovementPhaseState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_MovementPhaseState_delAndSetNull(void *ptr)
{
	Gitsn_MovementPhaseState **p = (Gitsn_MovementPhaseState **)ptr;
	if (p != NULL) { Gitsn_MovementPhaseState_del(*p); *p = NULL; }
}
// Gitsn_MovementPhaseState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AdvisorySpeedType
typedef enum Gitsn_AdvisorySpeedType
{
	Gitsn_AdvisorySpeedType_none,
	Gitsn_AdvisorySpeedType_greenwave,
	Gitsn_AdvisorySpeedType_ecoDrive,
	Gitsn_AdvisorySpeedType_transit,
	Gitsn_AdvisorySpeedType_max
} Gitsn_AdvisorySpeedType;

DZ1_CPPLINK str_t Gitsn_AdvisorySpeedTypeStrA(Gitsn_AdvisorySpeedType v);
DZ1_CPPLINK Gitsn_AdvisorySpeedType Gitsn_AdvisorySpeedTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_AdvisorySpeedTypeStrW(Gitsn_AdvisorySpeedType v);
DZ1_CPPLINK Gitsn_AdvisorySpeedType Gitsn_AdvisorySpeedTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_AdvisorySpeedTypeStr Gitsn_AdvisorySpeedTypeStrW
#define Gitsn_AdvisorySpeedTypeFromStr Gitsn_AdvisorySpeedTypeFromStrW
#else // UNICODE
#define Gitsn_AdvisorySpeedTypeStr Gitsn_AdvisorySpeedTypeStrA
#define Gitsn_AdvisorySpeedTypeFromStr Gitsn_AdvisorySpeedTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_AdvisorySpeedTypeStr Gitsn_AdvisorySpeedTypeStrA
#define Gitsn_AdvisorySpeedTypeFromStr Gitsn_AdvisorySpeedTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AdvisorySpeedType *Gitsn_AdvisorySpeedType_new(Gitsn_AdvisorySpeedType *src, Dz1Error *err);
static __inline__ Gitsn_AdvisorySpeedType *Gitsn_AdvisorySpeedType_gen(Dz1Error *err) { Gitsn_AdvisorySpeedType v = Gitsn_AdvisorySpeedType_max; return Gitsn_AdvisorySpeedType_new(&v, err); }
static __inline__ void Gitsn_AdvisorySpeedType_del(Gitsn_AdvisorySpeedType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_AdvisorySpeedType_delAndSetNull(void *ptr)
{
	Gitsn_AdvisorySpeedType **p = (Gitsn_AdvisorySpeedType **)ptr;
	if (p != NULL) { Gitsn_AdvisorySpeedType_del(*p); *p = NULL; }
}
// Gitsn_AdvisorySpeedType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Extent
typedef enum Gitsn_Extent
{
	Gitsn_Extent_useInstantlyOnly = 0,
	Gitsn_Extent_useFor3meters = 1,
	Gitsn_Extent_useFor10meters = 2,
	Gitsn_Extent_useFor50meters = 3,
	Gitsn_Extent_useFor100meters = 4,
	Gitsn_Extent_useFor500meters = 5,
	Gitsn_Extent_useFor1000meters = 6,
	Gitsn_Extent_useFor5000meters = 7,
	Gitsn_Extent_useFor10000meters = 8,
	Gitsn_Extent_useFor50000meters = 9,
	Gitsn_Extent_useFor100000meters = 10,
	Gitsn_Extent_useFor500000meters = 11,
	Gitsn_Extent_useFor1000000meters = 12,
	Gitsn_Extent_useFor5000000meters = 13,
	Gitsn_Extent_useFor10000000meters = 14,
	Gitsn_Extent_forever = 15,
	Gitsn_Extent_max
} Gitsn_Extent;

DZ1_CPPLINK str_t Gitsn_ExtentStrA(Gitsn_Extent v);
DZ1_CPPLINK Gitsn_Extent Gitsn_ExtentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ExtentStrW(Gitsn_Extent v);
DZ1_CPPLINK Gitsn_Extent Gitsn_ExtentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ExtentStr Gitsn_ExtentStrW
#define Gitsn_ExtentFromStr Gitsn_ExtentFromStrW
#else // UNICODE
#define Gitsn_ExtentStr Gitsn_ExtentStrA
#define Gitsn_ExtentFromStr Gitsn_ExtentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ExtentStr Gitsn_ExtentStrA
#define Gitsn_ExtentFromStr Gitsn_ExtentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Extent *Gitsn_Extent_new(Gitsn_Extent *src, Dz1Error *err);
static __inline__ Gitsn_Extent *Gitsn_Extent_gen(Dz1Error *err) { Gitsn_Extent v = Gitsn_Extent_max; return Gitsn_Extent_new(&v, err); }
static __inline__ void Gitsn_Extent_del(Gitsn_Extent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Extent_delAndSetNull(void *ptr)
{
	Gitsn_Extent **p = (Gitsn_Extent **)ptr;
	if (p != NULL) { Gitsn_Extent_del(*p); *p = NULL; }
}
// Gitsn_Extent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerInfoType
typedef enum Gitsn_TravelerInfoType
{
	Gitsn_TravelerInfoType_unknown = 0,
	Gitsn_TravelerInfoType_advisory = 1,
	Gitsn_TravelerInfoType_roadSignage = 2,
	Gitsn_TravelerInfoType_commercialSignage = 3,
	Gitsn_TravelerInfoType_max
} Gitsn_TravelerInfoType;

DZ1_CPPLINK str_t Gitsn_TravelerInfoTypeStrA(Gitsn_TravelerInfoType v);
DZ1_CPPLINK Gitsn_TravelerInfoType Gitsn_TravelerInfoTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TravelerInfoTypeStrW(Gitsn_TravelerInfoType v);
DZ1_CPPLINK Gitsn_TravelerInfoType Gitsn_TravelerInfoTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TravelerInfoTypeStr Gitsn_TravelerInfoTypeStrW
#define Gitsn_TravelerInfoTypeFromStr Gitsn_TravelerInfoTypeFromStrW
#else // UNICODE
#define Gitsn_TravelerInfoTypeStr Gitsn_TravelerInfoTypeStrA
#define Gitsn_TravelerInfoTypeFromStr Gitsn_TravelerInfoTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TravelerInfoTypeStr Gitsn_TravelerInfoTypeStrA
#define Gitsn_TravelerInfoTypeFromStr Gitsn_TravelerInfoTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerInfoType *Gitsn_TravelerInfoType_new(Gitsn_TravelerInfoType *src, Dz1Error *err);
static __inline__ Gitsn_TravelerInfoType *Gitsn_TravelerInfoType_gen(Dz1Error *err) { Gitsn_TravelerInfoType v = Gitsn_TravelerInfoType_max; return Gitsn_TravelerInfoType_new(&v, err); }
static __inline__ void Gitsn_TravelerInfoType_del(Gitsn_TravelerInfoType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TravelerInfoType_delAndSetNull(void *ptr)
{
	Gitsn_TravelerInfoType **p = (Gitsn_TravelerInfoType **)ptr;
	if (p != NULL) { Gitsn_TravelerInfoType_del(*p); *p = NULL; }
}
// Gitsn_TravelerInfoType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MUTCDCode
typedef enum Gitsn_MUTCDCode
{
	Gitsn_MUTCDCode_none = 0,
	Gitsn_MUTCDCode_regulartory = 1,
	Gitsn_MUTCDCode_warning = 2,
	Gitsn_MUTCDCode_maintenance = 3,
	Gitsn_MUTCDCode_motoristService = 4,
	Gitsn_MUTCDCode_guide = 5,
	Gitsn_MUTCDCode_rec = 6,
	Gitsn_MUTCDCode_max
} Gitsn_MUTCDCode;

DZ1_CPPLINK str_t Gitsn_MUTCDCodeStrA(Gitsn_MUTCDCode v);
DZ1_CPPLINK Gitsn_MUTCDCode Gitsn_MUTCDCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_MUTCDCodeStrW(Gitsn_MUTCDCode v);
DZ1_CPPLINK Gitsn_MUTCDCode Gitsn_MUTCDCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_MUTCDCodeStr Gitsn_MUTCDCodeStrW
#define Gitsn_MUTCDCodeFromStr Gitsn_MUTCDCodeFromStrW
#else // UNICODE
#define Gitsn_MUTCDCodeStr Gitsn_MUTCDCodeStrA
#define Gitsn_MUTCDCodeFromStr Gitsn_MUTCDCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_MUTCDCodeStr Gitsn_MUTCDCodeStrA
#define Gitsn_MUTCDCodeFromStr Gitsn_MUTCDCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MUTCDCode *Gitsn_MUTCDCode_new(Gitsn_MUTCDCode *src, Dz1Error *err);
static __inline__ Gitsn_MUTCDCode *Gitsn_MUTCDCode_gen(Dz1Error *err) { Gitsn_MUTCDCode v = Gitsn_MUTCDCode_max; return Gitsn_MUTCDCode_new(&v, err); }
static __inline__ void Gitsn_MUTCDCode_del(Gitsn_MUTCDCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_MUTCDCode_delAndSetNull(void *ptr)
{
	Gitsn_MUTCDCode **p = (Gitsn_MUTCDCode **)ptr;
	if (p != NULL) { Gitsn_MUTCDCode_del(*p); *p = NULL; }
}
// Gitsn_MUTCDCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DirectionOfUse
typedef enum Gitsn_DirectionOfUse
{
	Gitsn_DirectionOfUse_unavailable = 0,
	Gitsn_DirectionOfUse_forward = 1,
	Gitsn_DirectionOfUse_reverse = 2,
	Gitsn_DirectionOfUse_both = 3,
	Gitsn_DirectionOfUse_max
} Gitsn_DirectionOfUse;

DZ1_CPPLINK str_t Gitsn_DirectionOfUseStrA(Gitsn_DirectionOfUse v);
DZ1_CPPLINK Gitsn_DirectionOfUse Gitsn_DirectionOfUseFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_DirectionOfUseStrW(Gitsn_DirectionOfUse v);
DZ1_CPPLINK Gitsn_DirectionOfUse Gitsn_DirectionOfUseFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_DirectionOfUseStr Gitsn_DirectionOfUseStrW
#define Gitsn_DirectionOfUseFromStr Gitsn_DirectionOfUseFromStrW
#else // UNICODE
#define Gitsn_DirectionOfUseStr Gitsn_DirectionOfUseStrA
#define Gitsn_DirectionOfUseFromStr Gitsn_DirectionOfUseFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_DirectionOfUseStr Gitsn_DirectionOfUseStrA
#define Gitsn_DirectionOfUseFromStr Gitsn_DirectionOfUseFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DirectionOfUse *Gitsn_DirectionOfUse_new(Gitsn_DirectionOfUse *src, Dz1Error *err);
static __inline__ Gitsn_DirectionOfUse *Gitsn_DirectionOfUse_gen(Dz1Error *err) { Gitsn_DirectionOfUse v = Gitsn_DirectionOfUse_max; return Gitsn_DirectionOfUse_new(&v, err); }
static __inline__ void Gitsn_DirectionOfUse_del(Gitsn_DirectionOfUse *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_DirectionOfUse_delAndSetNull(void *ptr)
{
	Gitsn_DirectionOfUse **p = (Gitsn_DirectionOfUse **)ptr;
	if (p != NULL) { Gitsn_DirectionOfUse_del(*p); *p = NULL; }
}
// Gitsn_DirectionOfUse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeLL
typedef enum Gitsn_NodeAttributeLL
{
	Gitsn_NodeAttributeLL_reserved,
	Gitsn_NodeAttributeLL_stopLine,
	Gitsn_NodeAttributeLL_roundedCapStyleA,
	Gitsn_NodeAttributeLL_roundedCapStyleB,
	Gitsn_NodeAttributeLL_mergePoint,
	Gitsn_NodeAttributeLL_divergePoint,
	Gitsn_NodeAttributeLL_downstreamStopLine,
	Gitsn_NodeAttributeLL_downstreamStartNode,
	Gitsn_NodeAttributeLL_closedToTraffic,
	Gitsn_NodeAttributeLL_safeIsland,
	Gitsn_NodeAttributeLL_curbPresentAtStepOff,
	Gitsn_NodeAttributeLL_hydrantPresent,
	Gitsn_NodeAttributeLL_max
} Gitsn_NodeAttributeLL;

DZ1_CPPLINK str_t Gitsn_NodeAttributeLLStrA(Gitsn_NodeAttributeLL v);
DZ1_CPPLINK Gitsn_NodeAttributeLL Gitsn_NodeAttributeLLFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NodeAttributeLLStrW(Gitsn_NodeAttributeLL v);
DZ1_CPPLINK Gitsn_NodeAttributeLL Gitsn_NodeAttributeLLFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NodeAttributeLLStr Gitsn_NodeAttributeLLStrW
#define Gitsn_NodeAttributeLLFromStr Gitsn_NodeAttributeLLFromStrW
#else // UNICODE
#define Gitsn_NodeAttributeLLStr Gitsn_NodeAttributeLLStrA
#define Gitsn_NodeAttributeLLFromStr Gitsn_NodeAttributeLLFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NodeAttributeLLStr Gitsn_NodeAttributeLLStrA
#define Gitsn_NodeAttributeLLFromStr Gitsn_NodeAttributeLLFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeLL *Gitsn_NodeAttributeLL_new(Gitsn_NodeAttributeLL *src, Dz1Error *err);
static __inline__ Gitsn_NodeAttributeLL *Gitsn_NodeAttributeLL_gen(Dz1Error *err) { Gitsn_NodeAttributeLL v = Gitsn_NodeAttributeLL_max; return Gitsn_NodeAttributeLL_new(&v, err); }
#define Gitsn_NodeAttributeLL_clone             Gitsn_NodeAttributeLL_new
static __inline__ void Gitsn_NodeAttributeLL_del(Gitsn_NodeAttributeLL *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_NodeAttributeLL_delAndSetNull(void *ptr)
{
	Gitsn_NodeAttributeLL **p = (Gitsn_NodeAttributeLL **)ptr;
	if (p != NULL) { Gitsn_NodeAttributeLL_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeLL_dump(Gitsn_NodeAttributeLL *v, int tab);
// Gitsn_NodeAttributeLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SegmentAttributeLL
typedef enum Gitsn_SegmentAttributeLL
{
	Gitsn_SegmentAttributeLL_reserved = 0,
	Gitsn_SegmentAttributeLL_doNotBlock = 1,
	Gitsn_SegmentAttributeLL_whiteLine = 2,
	Gitsn_SegmentAttributeLL_mergingLaneLeft = 3,
	Gitsn_SegmentAttributeLL_mergingLaneRight = 4,
	Gitsn_SegmentAttributeLL_curbOnLeft = 5,
	Gitsn_SegmentAttributeLL_curbOnRight = 6,
	Gitsn_SegmentAttributeLL_loadingzoneOnLeft = 7,
	Gitsn_SegmentAttributeLL_loadingzoneOnRight = 8,
	Gitsn_SegmentAttributeLL_turnOutPointOnLeft = 9,
	Gitsn_SegmentAttributeLL_turnOutPointOnRight = 10,
	Gitsn_SegmentAttributeLL_adjacentParkingOnLeft = 11,
	Gitsn_SegmentAttributeLL_adjacentParkingOnRight = 12,
	Gitsn_SegmentAttributeLL_adjacentBikeLaneOnLeft = 13,
	Gitsn_SegmentAttributeLL_adjacentBikeLaneOnRight = 14,
	Gitsn_SegmentAttributeLL_sharedBikeLane = 15,
	Gitsn_SegmentAttributeLL_bikeBoxInFront = 16,
	Gitsn_SegmentAttributeLL_transitStopOnLeft = 17,
	Gitsn_SegmentAttributeLL_transitStopOnRight = 18,
	Gitsn_SegmentAttributeLL_transitStopInLane = 19,
	Gitsn_SegmentAttributeLL_sharedWithTrackedVehicle = 20,
	Gitsn_SegmentAttributeLL_safeIsland = 21,
	Gitsn_SegmentAttributeLL_lowCurbsPresent = 22,
	Gitsn_SegmentAttributeLL_rumbleStripPresent = 23,
	Gitsn_SegmentAttributeLL_audibleSignalingPresent = 24,
	Gitsn_SegmentAttributeLL_adaptiveTimingPresent = 25,
	Gitsn_SegmentAttributeLL_rfSignalRequestPresent = 26,
	Gitsn_SegmentAttributeLL_partialCurbIntrusion = 27,
	Gitsn_SegmentAttributeLL_taperToLeft = 28,
	Gitsn_SegmentAttributeLL_taperToRight = 29,
	Gitsn_SegmentAttributeLL_taperToCenterLine = 30,
	Gitsn_SegmentAttributeLL_parallelParking = 31,
	Gitsn_SegmentAttributeLL_headInParking = 32,
	Gitsn_SegmentAttributeLL_freeParking = 33,
	Gitsn_SegmentAttributeLL_timeRestrictionsOnParking = 34,
	Gitsn_SegmentAttributeLL_costToPark = 35,
	Gitsn_SegmentAttributeLL_midBlockCurbPresent = 36,
	Gitsn_SegmentAttributeLL_unEvenPavementPresent = 37,
	Gitsn_SegmentAttributeLL_max
} Gitsn_SegmentAttributeLL;

DZ1_CPPLINK str_t Gitsn_SegmentAttributeLLStrA(Gitsn_SegmentAttributeLL v);
DZ1_CPPLINK Gitsn_SegmentAttributeLL Gitsn_SegmentAttributeLLFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SegmentAttributeLLStrW(Gitsn_SegmentAttributeLL v);
DZ1_CPPLINK Gitsn_SegmentAttributeLL Gitsn_SegmentAttributeLLFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SegmentAttributeLLStr Gitsn_SegmentAttributeLLStrW
#define Gitsn_SegmentAttributeLLFromStr Gitsn_SegmentAttributeLLFromStrW
#else // UNICODE
#define Gitsn_SegmentAttributeLLStr Gitsn_SegmentAttributeLLStrA
#define Gitsn_SegmentAttributeLLFromStr Gitsn_SegmentAttributeLLFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SegmentAttributeLLStr Gitsn_SegmentAttributeLLStrA
#define Gitsn_SegmentAttributeLLFromStr Gitsn_SegmentAttributeLLFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SegmentAttributeLL *Gitsn_SegmentAttributeLL_new(Gitsn_SegmentAttributeLL *src, Dz1Error *err);
static __inline__ Gitsn_SegmentAttributeLL *Gitsn_SegmentAttributeLL_gen(Dz1Error *err) { Gitsn_SegmentAttributeLL v = Gitsn_SegmentAttributeLL_max; return Gitsn_SegmentAttributeLL_new(&v, err); }
#define Gitsn_SegmentAttributeLL_clone             Gitsn_SegmentAttributeLL_new
static __inline__ void Gitsn_SegmentAttributeLL_del(Gitsn_SegmentAttributeLL *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SegmentAttributeLL_delAndSetNull(void *ptr)
{
	Gitsn_SegmentAttributeLL **p = (Gitsn_SegmentAttributeLL **)ptr;
	if (p != NULL) { Gitsn_SegmentAttributeLL_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SegmentAttributeLL_dump(Gitsn_SegmentAttributeLL *v, int tab);
// Gitsn_SegmentAttributeLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DistanceUnits
typedef enum Gitsn_DistanceUnits
{
	Gitsn_DistanceUnits_centimeter = 0,
	Gitsn_DistanceUnits_cm2 = 1,
	Gitsn_DistanceUnits_decimeter = 2,
	Gitsn_DistanceUnits_meter = 3,
	Gitsn_DistanceUnits_kilometer = 4,
	Gitsn_DistanceUnits_foot = 5,
	Gitsn_DistanceUnits_yard = 6,
	Gitsn_DistanceUnits_mile = 7,
	Gitsn_DistanceUnits_max
} Gitsn_DistanceUnits;

DZ1_CPPLINK str_t Gitsn_DistanceUnitsStrA(Gitsn_DistanceUnits v);
DZ1_CPPLINK Gitsn_DistanceUnits Gitsn_DistanceUnitsFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_DistanceUnitsStrW(Gitsn_DistanceUnits v);
DZ1_CPPLINK Gitsn_DistanceUnits Gitsn_DistanceUnitsFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_DistanceUnitsStr Gitsn_DistanceUnitsStrW
#define Gitsn_DistanceUnitsFromStr Gitsn_DistanceUnitsFromStrW
#else // UNICODE
#define Gitsn_DistanceUnitsStr Gitsn_DistanceUnitsStrA
#define Gitsn_DistanceUnitsFromStr Gitsn_DistanceUnitsFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_DistanceUnitsStr Gitsn_DistanceUnitsStrA
#define Gitsn_DistanceUnitsFromStr Gitsn_DistanceUnitsFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DistanceUnits *Gitsn_DistanceUnits_new(Gitsn_DistanceUnits *src, Dz1Error *err);
static __inline__ Gitsn_DistanceUnits *Gitsn_DistanceUnits_gen(Dz1Error *err) { Gitsn_DistanceUnits v = Gitsn_DistanceUnits_max; return Gitsn_DistanceUnits_new(&v, err); }
static __inline__ void Gitsn_DistanceUnits_del(Gitsn_DistanceUnits *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_DistanceUnits_delAndSetNull(void *ptr)
{
	Gitsn_DistanceUnits **p = (Gitsn_DistanceUnits **)ptr;
	if (p != NULL) { Gitsn_DistanceUnits_del(*p); *p = NULL; }
}
// Gitsn_DistanceUnits
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightType
typedef enum Gitsn_TrafficLightType
{
	Gitsn_TrafficLightType_reserved = 0,
	Gitsn_TrafficLightType_straight = 1,
	Gitsn_TrafficLightType_left_turn = 2,
	Gitsn_TrafficLightType_pedestrian = 3,
	Gitsn_TrafficLightType_bicycle = 4,
	Gitsn_TrafficLightType_right_turn = 5,
	Gitsn_TrafficLightType_bus = 6,
	Gitsn_TrafficLightType_u_turn = 7,
	Gitsn_TrafficLightType_max
} Gitsn_TrafficLightType;

DZ1_CPPLINK str_t Gitsn_TrafficLightTypeStrA(Gitsn_TrafficLightType v);
DZ1_CPPLINK Gitsn_TrafficLightType Gitsn_TrafficLightTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TrafficLightTypeStrW(Gitsn_TrafficLightType v);
DZ1_CPPLINK Gitsn_TrafficLightType Gitsn_TrafficLightTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TrafficLightTypeStr Gitsn_TrafficLightTypeStrW
#define Gitsn_TrafficLightTypeFromStr Gitsn_TrafficLightTypeFromStrW
#else // UNICODE
#define Gitsn_TrafficLightTypeStr Gitsn_TrafficLightTypeStrA
#define Gitsn_TrafficLightTypeFromStr Gitsn_TrafficLightTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TrafficLightTypeStr Gitsn_TrafficLightTypeStrA
#define Gitsn_TrafficLightTypeFromStr Gitsn_TrafficLightTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightType *Gitsn_TrafficLightType_new(Gitsn_TrafficLightType *src, Dz1Error *err);
static __inline__ Gitsn_TrafficLightType *Gitsn_TrafficLightType_gen(Dz1Error *err) { Gitsn_TrafficLightType v = Gitsn_TrafficLightType_max; return Gitsn_TrafficLightType_new(&v, err); }
#define Gitsn_TrafficLightType_clone             Gitsn_TrafficLightType_new
static __inline__ void Gitsn_TrafficLightType_del(Gitsn_TrafficLightType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TrafficLightType_delAndSetNull(void *ptr)
{
	Gitsn_TrafficLightType **p = (Gitsn_TrafficLightType **)ptr;
	if (p != NULL) { Gitsn_TrafficLightType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightType_dump(Gitsn_TrafficLightType *v, int tab);
// Gitsn_TrafficLightType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConsecutiveTrafficLight
typedef enum Gitsn_ConsecutiveTrafficLight
{
	Gitsn_ConsecutiveTrafficLight_none = 0,
	Gitsn_ConsecutiveTrafficLight_first = 1,
	Gitsn_ConsecutiveTrafficLight_second = 2,
	Gitsn_ConsecutiveTrafficLight_max
} Gitsn_ConsecutiveTrafficLight;

DZ1_CPPLINK str_t Gitsn_ConsecutiveTrafficLightStrA(Gitsn_ConsecutiveTrafficLight v);
DZ1_CPPLINK Gitsn_ConsecutiveTrafficLight Gitsn_ConsecutiveTrafficLightFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ConsecutiveTrafficLightStrW(Gitsn_ConsecutiveTrafficLight v);
DZ1_CPPLINK Gitsn_ConsecutiveTrafficLight Gitsn_ConsecutiveTrafficLightFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ConsecutiveTrafficLightStr Gitsn_ConsecutiveTrafficLightStrW
#define Gitsn_ConsecutiveTrafficLightFromStr Gitsn_ConsecutiveTrafficLightFromStrW
#else // UNICODE
#define Gitsn_ConsecutiveTrafficLightStr Gitsn_ConsecutiveTrafficLightStrA
#define Gitsn_ConsecutiveTrafficLightFromStr Gitsn_ConsecutiveTrafficLightFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ConsecutiveTrafficLightStr Gitsn_ConsecutiveTrafficLightStrA
#define Gitsn_ConsecutiveTrafficLightFromStr Gitsn_ConsecutiveTrafficLightFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConsecutiveTrafficLight *Gitsn_ConsecutiveTrafficLight_new(Gitsn_ConsecutiveTrafficLight *src, Dz1Error *err);
static __inline__ Gitsn_ConsecutiveTrafficLight *Gitsn_ConsecutiveTrafficLight_gen(Dz1Error *err) { Gitsn_ConsecutiveTrafficLight v = Gitsn_ConsecutiveTrafficLight_max; return Gitsn_ConsecutiveTrafficLight_new(&v, err); }
#define Gitsn_ConsecutiveTrafficLight_clone             Gitsn_ConsecutiveTrafficLight_new
static __inline__ void Gitsn_ConsecutiveTrafficLight_del(Gitsn_ConsecutiveTrafficLight *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ConsecutiveTrafficLight_delAndSetNull(void *ptr)
{
	Gitsn_ConsecutiveTrafficLight **p = (Gitsn_ConsecutiveTrafficLight **)ptr;
	if (p != NULL) { Gitsn_ConsecutiveTrafficLight_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConsecutiveTrafficLight_dump(Gitsn_ConsecutiveTrafficLight *v, int tab);
// Gitsn_ConsecutiveTrafficLight
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightIntervalType
typedef enum Gitsn_TrafficLightIntervalType
{
	Gitsn_TrafficLightIntervalType_static = 0,
	Gitsn_TrafficLightIntervalType_variable = 1,
	Gitsn_TrafficLightIntervalType_max
} Gitsn_TrafficLightIntervalType;

DZ1_CPPLINK str_t Gitsn_TrafficLightIntervalTypeStrA(Gitsn_TrafficLightIntervalType v);
DZ1_CPPLINK Gitsn_TrafficLightIntervalType Gitsn_TrafficLightIntervalTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TrafficLightIntervalTypeStrW(Gitsn_TrafficLightIntervalType v);
DZ1_CPPLINK Gitsn_TrafficLightIntervalType Gitsn_TrafficLightIntervalTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TrafficLightIntervalTypeStr Gitsn_TrafficLightIntervalTypeStrW
#define Gitsn_TrafficLightIntervalTypeFromStr Gitsn_TrafficLightIntervalTypeFromStrW
#else // UNICODE
#define Gitsn_TrafficLightIntervalTypeStr Gitsn_TrafficLightIntervalTypeStrA
#define Gitsn_TrafficLightIntervalTypeFromStr Gitsn_TrafficLightIntervalTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TrafficLightIntervalTypeStr Gitsn_TrafficLightIntervalTypeStrA
#define Gitsn_TrafficLightIntervalTypeFromStr Gitsn_TrafficLightIntervalTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightIntervalType *Gitsn_TrafficLightIntervalType_new(Gitsn_TrafficLightIntervalType *src, Dz1Error *err);
static __inline__ Gitsn_TrafficLightIntervalType *Gitsn_TrafficLightIntervalType_gen(Dz1Error *err) { Gitsn_TrafficLightIntervalType v = Gitsn_TrafficLightIntervalType_max; return Gitsn_TrafficLightIntervalType_new(&v, err); }
#define Gitsn_TrafficLightIntervalType_clone             Gitsn_TrafficLightIntervalType_new
static __inline__ void Gitsn_TrafficLightIntervalType_del(Gitsn_TrafficLightIntervalType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TrafficLightIntervalType_delAndSetNull(void *ptr)
{
	Gitsn_TrafficLightIntervalType **p = (Gitsn_TrafficLightIntervalType **)ptr;
	if (p != NULL) { Gitsn_TrafficLightIntervalType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightIntervalType_dump(Gitsn_TrafficLightIntervalType *v, int tab);
// Gitsn_TrafficLightIntervalType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PermissiveNonProtected
typedef enum Gitsn_PermissiveNonProtected
{
	Gitsn_PermissiveNonProtected_none = 0,
	Gitsn_PermissiveNonProtected_permissive = 1,
	Gitsn_PermissiveNonProtected_max
} Gitsn_PermissiveNonProtected;

DZ1_CPPLINK str_t Gitsn_PermissiveNonProtectedStrA(Gitsn_PermissiveNonProtected v);
DZ1_CPPLINK Gitsn_PermissiveNonProtected Gitsn_PermissiveNonProtectedFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_PermissiveNonProtectedStrW(Gitsn_PermissiveNonProtected v);
DZ1_CPPLINK Gitsn_PermissiveNonProtected Gitsn_PermissiveNonProtectedFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_PermissiveNonProtectedStr Gitsn_PermissiveNonProtectedStrW
#define Gitsn_PermissiveNonProtectedFromStr Gitsn_PermissiveNonProtectedFromStrW
#else // UNICODE
#define Gitsn_PermissiveNonProtectedStr Gitsn_PermissiveNonProtectedStrA
#define Gitsn_PermissiveNonProtectedFromStr Gitsn_PermissiveNonProtectedFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_PermissiveNonProtectedStr Gitsn_PermissiveNonProtectedStrA
#define Gitsn_PermissiveNonProtectedFromStr Gitsn_PermissiveNonProtectedFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PermissiveNonProtected *Gitsn_PermissiveNonProtected_new(Gitsn_PermissiveNonProtected *src, Dz1Error *err);
static __inline__ Gitsn_PermissiveNonProtected *Gitsn_PermissiveNonProtected_gen(Dz1Error *err) { Gitsn_PermissiveNonProtected v = Gitsn_PermissiveNonProtected_max; return Gitsn_PermissiveNonProtected_new(&v, err); }
#define Gitsn_PermissiveNonProtected_clone             Gitsn_PermissiveNonProtected_new
static __inline__ void Gitsn_PermissiveNonProtected_del(Gitsn_PermissiveNonProtected *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_PermissiveNonProtected_delAndSetNull(void *ptr)
{
	Gitsn_PermissiveNonProtected **p = (Gitsn_PermissiveNonProtected **)ptr;
	if (p != NULL) { Gitsn_PermissiveNonProtected_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PermissiveNonProtected_dump(Gitsn_PermissiveNonProtected *v, int tab);
// Gitsn_PermissiveNonProtected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightingStatus
typedef enum Gitsn_TrafficLightingStatus
{
	Gitsn_TrafficLightingStatus_off = 0,
	Gitsn_TrafficLightingStatus_red_on = 1,
	Gitsn_TrafficLightingStatus_yellow_on = 2,
	Gitsn_TrafficLightingStatus_green_on = 3,
	Gitsn_TrafficLightingStatus_red_blinking = 4,
	Gitsn_TrafficLightingStatus_yellow_blinking = 5,
	Gitsn_TrafficLightingStatus_green_blinking = 6,
	Gitsn_TrafficLightingStatus_max
} Gitsn_TrafficLightingStatus;

DZ1_CPPLINK str_t Gitsn_TrafficLightingStatusStrA(Gitsn_TrafficLightingStatus v);
DZ1_CPPLINK Gitsn_TrafficLightingStatus Gitsn_TrafficLightingStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TrafficLightingStatusStrW(Gitsn_TrafficLightingStatus v);
DZ1_CPPLINK Gitsn_TrafficLightingStatus Gitsn_TrafficLightingStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TrafficLightingStatusStr Gitsn_TrafficLightingStatusStrW
#define Gitsn_TrafficLightingStatusFromStr Gitsn_TrafficLightingStatusFromStrW
#else // UNICODE
#define Gitsn_TrafficLightingStatusStr Gitsn_TrafficLightingStatusStrA
#define Gitsn_TrafficLightingStatusFromStr Gitsn_TrafficLightingStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TrafficLightingStatusStr Gitsn_TrafficLightingStatusStrA
#define Gitsn_TrafficLightingStatusFromStr Gitsn_TrafficLightingStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightingStatus *Gitsn_TrafficLightingStatus_new(Gitsn_TrafficLightingStatus *src, Dz1Error *err);
static __inline__ Gitsn_TrafficLightingStatus *Gitsn_TrafficLightingStatus_gen(Dz1Error *err) { Gitsn_TrafficLightingStatus v = Gitsn_TrafficLightingStatus_max; return Gitsn_TrafficLightingStatus_new(&v, err); }
#define Gitsn_TrafficLightingStatus_clone             Gitsn_TrafficLightingStatus_new
static __inline__ void Gitsn_TrafficLightingStatus_del(Gitsn_TrafficLightingStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TrafficLightingStatus_delAndSetNull(void *ptr)
{
	Gitsn_TrafficLightingStatus **p = (Gitsn_TrafficLightingStatus **)ptr;
	if (p != NULL) { Gitsn_TrafficLightingStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightingStatus_dump(Gitsn_TrafficLightingStatus *v, int tab);
// Gitsn_TrafficLightingStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PositionalAccuracy
typedef struct Gitsn_PositionalAccuracy
{
	Gitsn_SemiMajorAxisAccuracy			semiMajor;
	Gitsn_SemiMinorAxisAccuracy			semiMinor;
	Gitsn_SemiMajorAxisOrientation		orientation;
} Gitsn_PositionalAccuracy;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PositionalAccuracy *Gitsn_PositionalAccuracy_new(Gitsn_SemiMajorAxisAccuracy semiMajor, 
																			   Gitsn_SemiMinorAxisAccuracy semiMinor, 
																			   Gitsn_SemiMajorAxisOrientation orientation, Dz1Error *err);
static __inline__ Gitsn_PositionalAccuracy *Gitsn_PositionalAccuracy_gen(Dz1Error *err) { return Gitsn_PositionalAccuracy_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_PositionalAccuracy_copy(Gitsn_PositionalAccuracy *dst, Gitsn_PositionalAccuracy *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PositionalAccuracy *Gitsn_PositionalAccuracy_clone(Gitsn_PositionalAccuracy *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionalAccuracy_purge(Gitsn_PositionalAccuracy *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionalAccuracy_del(Gitsn_PositionalAccuracy *p);
static __inline__ void Gitsn_PositionalAccuracy_delAndSetNull(void *ptr)
{
	Gitsn_PositionalAccuracy **p = (Gitsn_PositionalAccuracy **)ptr;
	if (p) { Gitsn_PositionalAccuracy_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionalAccuracy_dump(Gitsn_PositionalAccuracy *p, int tab);
// Gitsn_PositionalAccuracy
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AccelerationSet4Way
typedef struct Gitsn_AccelerationSet4Way
{
	Gitsn_Acceleration				lon;
	Gitsn_Acceleration				lat;
	Gitsn_VerticalAcceleration		vert;
	Gitsn_YawRate					yaw;
} Gitsn_AccelerationSet4Way;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AccelerationSet4Way *Gitsn_AccelerationSet4Way_new(Gitsn_Acceleration lon, 
																				 Gitsn_Acceleration lat, 
																				 Gitsn_VerticalAcceleration vert, 
																				 Gitsn_YawRate yaw, Dz1Error *err);
static __inline__ Gitsn_AccelerationSet4Way *Gitsn_AccelerationSet4Way_gen(Dz1Error *err) { return Gitsn_AccelerationSet4Way_new(0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_AccelerationSet4Way_copy(Gitsn_AccelerationSet4Way *dst, Gitsn_AccelerationSet4Way *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AccelerationSet4Way *Gitsn_AccelerationSet4Way_clone(Gitsn_AccelerationSet4Way *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AccelerationSet4Way_purge(Gitsn_AccelerationSet4Way *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AccelerationSet4Way_del(Gitsn_AccelerationSet4Way *p);
static __inline__ void Gitsn_AccelerationSet4Way_delAndSetNull(void *ptr)
{
	Gitsn_AccelerationSet4Way **p = (Gitsn_AccelerationSet4Way **)ptr;
	if (p) { Gitsn_AccelerationSet4Way_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AccelerationSet4Way_dump(Gitsn_AccelerationSet4Way *p, int tab);
// Gitsn_AccelerationSet4Way
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BrakeSystemStatus
typedef struct Gitsn_BrakeSystemStatus
{
	Gitsn_BrakeAppliedStatus		*wheelBrakes;
	Gitsn_TractionControlStatus		 traction;
	Gitsn_AntiLockBrakeStatus		 abs;
	Gitsn_StabilityControlStatus	 scs;
	Gitsn_BrakeBoostApplied			 brakeBoost;
	Gitsn_AuxiliaryBrakeStatus		 auxBrakes;
} Gitsn_BrakeSystemStatus;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_BrakeSystemStatus *Gitsn_BrakeSystemStatus_new(Gitsn_BrakeAppliedStatus *wheelBrakes, 
																			 Gitsn_TractionControlStatus traction, 
																			 Gitsn_AntiLockBrakeStatus abs, 
																			 Gitsn_StabilityControlStatus scs, 
																			 Gitsn_BrakeBoostApplied brakeBoost, 
																			 Gitsn_AuxiliaryBrakeStatus auxBrakes, Dz1Error *err);
static __inline__ Gitsn_BrakeSystemStatus *Gitsn_BrakeSystemStatus_gen(Dz1Error *err) { return Gitsn_BrakeSystemStatus_new(NULL, Gitsn_TractionControlStatus_max, Gitsn_AntiLockBrakeStatus_max, Gitsn_StabilityControlStatus_max, Gitsn_BrakeBoostApplied_max, Gitsn_AuxiliaryBrakeStatus_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_BrakeSystemStatus_copy(Gitsn_BrakeSystemStatus *dst, Gitsn_BrakeSystemStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_BrakeSystemStatus *Gitsn_BrakeSystemStatus_clone(Gitsn_BrakeSystemStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BrakeSystemStatus_purge(Gitsn_BrakeSystemStatus *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BrakeSystemStatus_del(Gitsn_BrakeSystemStatus *p);
static __inline__ void Gitsn_BrakeSystemStatus_delAndSetNull(void *ptr)
{
	Gitsn_BrakeSystemStatus **p = (Gitsn_BrakeSystemStatus **)ptr;
	if (p) { Gitsn_BrakeSystemStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BrakeSystemStatus_dump(Gitsn_BrakeSystemStatus *p, int tab);
// Gitsn_BrakeSystemStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleSize
typedef struct Gitsn_VehicleSize
{
	Gitsn_VehicleWidth		width;
	Gitsn_VehicleLength		length;
} Gitsn_VehicleSize;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleSize *Gitsn_VehicleSize_new(Gitsn_VehicleWidth width, 
																 Gitsn_VehicleLength length, Dz1Error *err);
static __inline__ Gitsn_VehicleSize *Gitsn_VehicleSize_gen(Dz1Error *err) { return Gitsn_VehicleSize_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleSize_copy(Gitsn_VehicleSize *dst, Gitsn_VehicleSize *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleSize *Gitsn_VehicleSize_clone(Gitsn_VehicleSize *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSize_purge(Gitsn_VehicleSize *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSize_del(Gitsn_VehicleSize *p);
static __inline__ void Gitsn_VehicleSize_delAndSetNull(void *ptr)
{
	Gitsn_VehicleSize **p = (Gitsn_VehicleSize **)ptr;
	if (p) { Gitsn_VehicleSize_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSize_dump(Gitsn_VehicleSize *p, int tab);
// Gitsn_VehicleSize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BSMCoreData
typedef struct Gitsn_BSMCoreData
{
	Gitsn_MsgCount					 msgCnt;
	Gitsn_TemporaryID				 id;
	Gitsn_DSecond					 secMark;
	Gitsn_Latitude					 lat;
	Gitsn_Longitude					 lon;
	Gitsn_Elevation					 elev;
	Gitsn_PositionalAccuracy		*accuracy;
	Gitsn_TransmissionState			 transmission;
	Gitsn_Speed						 speed;
	Gitsn_Heading					 heading;
	Gitsn_SteeringWheelAngle		 angle;
	Gitsn_AccelerationSet4Way		*accelSet;
	Gitsn_BrakeSystemStatus			*brakes;
	Gitsn_VehicleSize				*size;
} Gitsn_BSMCoreData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_BSMCoreData *Gitsn_BSMCoreData_new(Gitsn_MsgCount msgCnt, 
																 Gitsn_TemporaryID id, 
																 Gitsn_DSecond secMark, 
																 Gitsn_Latitude lat, 
																 Gitsn_Longitude lon, 
																 Gitsn_Elevation elev, 
																 Gitsn_PositionalAccuracy *accuracy, 
																 Gitsn_TransmissionState transmission, 
																 Gitsn_Speed speed, 
																 Gitsn_Heading heading, 
																 Gitsn_SteeringWheelAngle angle, 
																 Gitsn_AccelerationSet4Way *accelSet, 
																 Gitsn_BrakeSystemStatus *brakes, 
																 Gitsn_VehicleSize *size, Dz1Error *err);
static __inline__ Gitsn_BSMCoreData *Gitsn_BSMCoreData_gen(Dz1Error *err) { return Gitsn_BSMCoreData_new(0, NULL, 0, 0, 0, 0, NULL, Gitsn_TransmissionState_max, 0, 0, 0, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_BSMCoreData_copy(Gitsn_BSMCoreData *dst, Gitsn_BSMCoreData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_BSMCoreData *Gitsn_BSMCoreData_clone(Gitsn_BSMCoreData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BSMCoreData_purge(Gitsn_BSMCoreData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BSMCoreData_del(Gitsn_BSMCoreData *p);
static __inline__ void Gitsn_BSMCoreData_delAndSetNull(void *ptr)
{
	Gitsn_BSMCoreData **p = (Gitsn_BSMCoreData **)ptr;
	if (p) { Gitsn_BSMCoreData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BSMCoreData_dump(Gitsn_BSMCoreData *p, int tab);
// Gitsn_BSMCoreData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionReferenceID
typedef struct Gitsn_IntersectionReferenceID
{
	Gitsn_RoadRegulatorID		region;
	Gitsn_IntersectionID		id;
} Gitsn_IntersectionReferenceID;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionReferenceID *Gitsn_IntersectionReferenceID_new(Gitsn_IntersectionID id, Dz1Error *err);
static __inline__ Gitsn_IntersectionReferenceID *Gitsn_IntersectionReferenceID_gen(Dz1Error *err) { return Gitsn_IntersectionReferenceID_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_IntersectionReferenceID_copy(Gitsn_IntersectionReferenceID *dst, Gitsn_IntersectionReferenceID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionReferenceID *Gitsn_IntersectionReferenceID_clone(Gitsn_IntersectionReferenceID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionReferenceID_purge(Gitsn_IntersectionReferenceID *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionReferenceID_del(Gitsn_IntersectionReferenceID *p);
static __inline__ void Gitsn_IntersectionReferenceID_delAndSetNull(void *ptr)
{
	Gitsn_IntersectionReferenceID **p = (Gitsn_IntersectionReferenceID **)ptr;
	if (p) { Gitsn_IntersectionReferenceID_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionReferenceID_dump(Gitsn_IntersectionReferenceID *p, int tab);
// Gitsn_IntersectionReferenceID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Position3D
typedef struct Gitsn_Position3D
{
	Gitsn_Latitude		lat;
	Gitsn_Longitude		lon;
	Gitsn_Elevation		elevation;
} Gitsn_Position3D;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Position3D *Gitsn_Position3D_new(Gitsn_Latitude lat, 
															   Gitsn_Longitude lon, Dz1Error *err);
static __inline__ Gitsn_Position3D *Gitsn_Position3D_gen(Dz1Error *err) { return Gitsn_Position3D_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Position3D_copy(Gitsn_Position3D *dst, Gitsn_Position3D *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Position3D *Gitsn_Position3D_clone(Gitsn_Position3D *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Position3D_purge(Gitsn_Position3D *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Position3D_del(Gitsn_Position3D *p);
static __inline__ void Gitsn_Position3D_delAndSetNull(void *ptr)
{
	Gitsn_Position3D **p = (Gitsn_Position3D **)ptr;
	if (p) { Gitsn_Position3D_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Position3D_dump(Gitsn_Position3D *p, int tab);
// Gitsn_Position3D
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RegulatorySpeedLimit
typedef struct Gitsn_RegulatorySpeedLimit
{
	Gitsn_SpeedLimitType	type;
	Gitsn_Velocity			speed;
} Gitsn_RegulatorySpeedLimit;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RegulatorySpeedLimit *Gitsn_RegulatorySpeedLimit_new(Gitsn_SpeedLimitType type, 
																				   Gitsn_Velocity speed, Dz1Error *err);
static __inline__ Gitsn_RegulatorySpeedLimit *Gitsn_RegulatorySpeedLimit_gen(Dz1Error *err) { return Gitsn_RegulatorySpeedLimit_new(Gitsn_SpeedLimitType_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RegulatorySpeedLimit_copy(Gitsn_RegulatorySpeedLimit *dst, Gitsn_RegulatorySpeedLimit *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RegulatorySpeedLimit *Gitsn_RegulatorySpeedLimit_clone(Gitsn_RegulatorySpeedLimit *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegulatorySpeedLimit_purge(Gitsn_RegulatorySpeedLimit *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegulatorySpeedLimit_del(Gitsn_RegulatorySpeedLimit *p);
static __inline__ void Gitsn_RegulatorySpeedLimit_delAndSetNull(void *ptr)
{
	Gitsn_RegulatorySpeedLimit **p = (Gitsn_RegulatorySpeedLimit **)ptr;
	if (p) { Gitsn_RegulatorySpeedLimit_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegulatorySpeedLimit_dump(Gitsn_RegulatorySpeedLimit *p, int tab);
// Gitsn_RegulatorySpeedLimit
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimitList
typedef struct Gitsn_SpeedLimitList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_SpeedLimitList *p);
	Dz1Error (*travel)(struct Gitsn_SpeedLimitList *p, Dz1Error (*func)(void *ptr, Gitsn_RegulatorySpeedLimit *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_SpeedLimitList *p, Dz1Error (*func)(void *ptr, Gitsn_RegulatorySpeedLimit *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_SpeedLimitList *p, Dz1Error (*func)(void *ptr, Gitsn_RegulatorySpeedLimit *entry), void *ptr);
	Gitsn_RegulatorySpeedLimit **(*get_array)(struct Gitsn_SpeedLimitList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_SpeedLimitList *p, Gitsn_RegulatorySpeedLimit *data);
	Gitsn_RegulatorySpeedLimit *(*extract)(struct Gitsn_SpeedLimitList *p, Gitsn_RegulatorySpeedLimit *ptr);
	Gitsn_RegulatorySpeedLimit *(*getHead)(struct Gitsn_SpeedLimitList *p);
} Gitsn_SpeedLimitList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimitList *Gitsn_SpeedLimitList_new(Dz1Error *err);
static __inline__ Gitsn_SpeedLimitList *Gitsn_SpeedLimitList_gen(Dz1Error *err) { return Gitsn_SpeedLimitList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimitList *Gitsn_SpeedLimitList_clone(Gitsn_SpeedLimitList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimitList_purge(Gitsn_SpeedLimitList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimitList_del(Gitsn_SpeedLimitList *p);
static __inline__ void Gitsn_SpeedLimitList_delAndSetNull(void *ptr)
{
	Gitsn_SpeedLimitList **p = (Gitsn_SpeedLimitList **)ptr;
	if (p != NULL) { Gitsn_SpeedLimitList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimitList_dump(Gitsn_SpeedLimitList *p, int tab);

// Gitsn_SpeedLimitList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneTypeAttributesPresent
typedef enum Gitsn_LaneTypeAttributesPresent
{
	Gitsn_LaneTypeAttributesPresent_vehicle,
	Gitsn_LaneTypeAttributesPresent_crosswalk,
	Gitsn_LaneTypeAttributesPresent_bikeLane,
	Gitsn_LaneTypeAttributesPresent_sidewalk,
	Gitsn_LaneTypeAttributesPresent_median,
	Gitsn_LaneTypeAttributesPresent_striping,
	Gitsn_LaneTypeAttributesPresent_trackedVehicle,
	Gitsn_LaneTypeAttributesPresent_parking,
	Gitsn_LaneTypeAttributesPresent_max
} Gitsn_LaneTypeAttributesPresent;

DZ1_CPPLINK str_t Gitsn_LaneTypeAttributesPresentStrA(Gitsn_LaneTypeAttributesPresent v);
DZ1_CPPLINK Gitsn_LaneTypeAttributesPresent Gitsn_LaneTypeAttributesPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_LaneTypeAttributesPresentStrW(Gitsn_LaneTypeAttributesPresent v);
DZ1_CPPLINK Gitsn_LaneTypeAttributesPresent Gitsn_LaneTypeAttributesPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_LaneTypeAttributesPresentStr Gitsn_LaneTypeAttributesPresentStrW
#define Gitsn_LaneTypeAttributesPresentFromStr Gitsn_LaneTypeAttributesPresentFromStrW
#else // UNICODE
#define Gitsn_LaneTypeAttributesPresentStr Gitsn_LaneTypeAttributesPresentStrA
#define Gitsn_LaneTypeAttributesPresentFromStr Gitsn_LaneTypeAttributesPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_LaneTypeAttributesPresentStr Gitsn_LaneTypeAttributesPresentStrA
#define Gitsn_LaneTypeAttributesPresentFromStr Gitsn_LaneTypeAttributesPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneTypeAttributesPresent *Gitsn_LaneTypeAttributesPresent_new(Gitsn_LaneTypeAttributesPresent *src, Dz1Error *err);
static __inline__ Gitsn_LaneTypeAttributesPresent *Gitsn_LaneTypeAttributesPresent_gen(Dz1Error *err) { Gitsn_LaneTypeAttributesPresent v = Gitsn_LaneTypeAttributesPresent_max; return Gitsn_LaneTypeAttributesPresent_new(&v, err); }
#define Gitsn_LaneTypeAttributesPresent_clone             Gitsn_LaneTypeAttributesPresent_new
static __inline__ void Gitsn_LaneTypeAttributesPresent_del(Gitsn_LaneTypeAttributesPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_LaneTypeAttributesPresent_delAndSetNull(void *ptr)
{
	Gitsn_LaneTypeAttributesPresent **p = (Gitsn_LaneTypeAttributesPresent **)ptr;
	if (p != NULL) { Gitsn_LaneTypeAttributesPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneTypeAttributesPresent_dump(Gitsn_LaneTypeAttributesPresent *v, int tab);
// Gitsn_LaneTypeAttributesPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneTypeAttributes
typedef struct Gitsn_LaneTypeAttributes
{
	Gitsn_LaneTypeAttributesPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_LaneAttributes_Vehicle			*vehicle;
		Gitsn_LaneAttributes_Crosswalk			*crosswalk;
		Gitsn_LaneAttributes_Bike				*bikeLane;
		Gitsn_LaneAttributes_Sidewalk			*sidewalk;
		Gitsn_LaneAttributes_Barrier			*median;
		Gitsn_LaneAttributes_Striping			*striping;
		Gitsn_LaneAttributes_TrackedVehicle		*trackedVehicle;
		Gitsn_LaneAttributes_Parking			*parking;
	} x;
} Gitsn_LaneTypeAttributes;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneTypeAttributes *Gitsn_LaneTypeAttributes_new(Gitsn_LaneTypeAttributesPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_LaneTypeAttributes *Gitsn_LaneTypeAttributes_gen(Dz1Error *err) { return Gitsn_LaneTypeAttributes_new(Gitsn_LaneTypeAttributesPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_LaneTypeAttributes_copy(Gitsn_LaneTypeAttributes *dst, Gitsn_LaneTypeAttributes *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneTypeAttributes *Gitsn_LaneTypeAttributes_clone(Gitsn_LaneTypeAttributes *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneTypeAttributes_purge(Gitsn_LaneTypeAttributes *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneTypeAttributes_del(Gitsn_LaneTypeAttributes *p);
static __inline__ void Gitsn_LaneTypeAttributes_delAndSetNull(void *ptr)
{
	Gitsn_LaneTypeAttributes **p = (Gitsn_LaneTypeAttributes **)ptr;
	if (p != NULL) { Gitsn_LaneTypeAttributes_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneTypeAttributes_dump(Gitsn_LaneTypeAttributes *p, int tab);
// Gitsn_LaneTypeAttributes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes
typedef struct Gitsn_LaneAttributes
{
	Gitsn_LaneDirection			*directionalUse;
	Gitsn_LaneSharing			*sharedWith;
	Gitsn_LaneTypeAttributes	*laneType;
} Gitsn_LaneAttributes;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneAttributes *Gitsn_LaneAttributes_new(Gitsn_LaneDirection *directionalUse, 
																	   Gitsn_LaneSharing *sharedWith, 
																	   Gitsn_LaneTypeAttributes *laneType, Dz1Error *err);
static __inline__ Gitsn_LaneAttributes *Gitsn_LaneAttributes_gen(Dz1Error *err) { return Gitsn_LaneAttributes_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_LaneAttributes_copy(Gitsn_LaneAttributes *dst, Gitsn_LaneAttributes *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneAttributes *Gitsn_LaneAttributes_clone(Gitsn_LaneAttributes *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneAttributes_purge(Gitsn_LaneAttributes *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneAttributes_del(Gitsn_LaneAttributes *p);
static __inline__ void Gitsn_LaneAttributes_delAndSetNull(void *ptr)
{
	Gitsn_LaneAttributes **p = (Gitsn_LaneAttributes **)ptr;
	if (p) { Gitsn_LaneAttributes_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneAttributes_dump(Gitsn_LaneAttributes *p, int tab);
// Gitsn_LaneAttributes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_20b
typedef struct Gitsn_Node_XY_20b
{
	Gitsn_Offset_B10	x;
	Gitsn_Offset_B10	y;
} Gitsn_Node_XY_20b;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_20b *Gitsn_Node_XY_20b_new(Gitsn_Offset_B10 x, 
																 Gitsn_Offset_B10 y, Dz1Error *err);
static __inline__ Gitsn_Node_XY_20b *Gitsn_Node_XY_20b_gen(Dz1Error *err) { return Gitsn_Node_XY_20b_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_XY_20b_copy(Gitsn_Node_XY_20b *dst, Gitsn_Node_XY_20b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_20b *Gitsn_Node_XY_20b_clone(Gitsn_Node_XY_20b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_20b_purge(Gitsn_Node_XY_20b *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_20b_del(Gitsn_Node_XY_20b *p);
static __inline__ void Gitsn_Node_XY_20b_delAndSetNull(void *ptr)
{
	Gitsn_Node_XY_20b **p = (Gitsn_Node_XY_20b **)ptr;
	if (p) { Gitsn_Node_XY_20b_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_20b_dump(Gitsn_Node_XY_20b *p, int tab);
// Gitsn_Node_XY_20b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_22b
typedef struct Gitsn_Node_XY_22b
{
	Gitsn_Offset_B11	x;
	Gitsn_Offset_B11	y;
} Gitsn_Node_XY_22b;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_22b *Gitsn_Node_XY_22b_new(Gitsn_Offset_B11 x, 
																 Gitsn_Offset_B11 y, Dz1Error *err);
static __inline__ Gitsn_Node_XY_22b *Gitsn_Node_XY_22b_gen(Dz1Error *err) { return Gitsn_Node_XY_22b_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_XY_22b_copy(Gitsn_Node_XY_22b *dst, Gitsn_Node_XY_22b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_22b *Gitsn_Node_XY_22b_clone(Gitsn_Node_XY_22b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_22b_purge(Gitsn_Node_XY_22b *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_22b_del(Gitsn_Node_XY_22b *p);
static __inline__ void Gitsn_Node_XY_22b_delAndSetNull(void *ptr)
{
	Gitsn_Node_XY_22b **p = (Gitsn_Node_XY_22b **)ptr;
	if (p) { Gitsn_Node_XY_22b_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_22b_dump(Gitsn_Node_XY_22b *p, int tab);
// Gitsn_Node_XY_22b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_24b
typedef struct Gitsn_Node_XY_24b
{
	Gitsn_Offset_B12	x;
	Gitsn_Offset_B12	y;
} Gitsn_Node_XY_24b;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_24b *Gitsn_Node_XY_24b_new(Gitsn_Offset_B12 x, 
																 Gitsn_Offset_B12 y, Dz1Error *err);
static __inline__ Gitsn_Node_XY_24b *Gitsn_Node_XY_24b_gen(Dz1Error *err) { return Gitsn_Node_XY_24b_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_XY_24b_copy(Gitsn_Node_XY_24b *dst, Gitsn_Node_XY_24b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_24b *Gitsn_Node_XY_24b_clone(Gitsn_Node_XY_24b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_24b_purge(Gitsn_Node_XY_24b *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_24b_del(Gitsn_Node_XY_24b *p);
static __inline__ void Gitsn_Node_XY_24b_delAndSetNull(void *ptr)
{
	Gitsn_Node_XY_24b **p = (Gitsn_Node_XY_24b **)ptr;
	if (p) { Gitsn_Node_XY_24b_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_24b_dump(Gitsn_Node_XY_24b *p, int tab);
// Gitsn_Node_XY_24b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_26b
typedef struct Gitsn_Node_XY_26b
{
	Gitsn_Offset_B13	x;
	Gitsn_Offset_B13	y;
} Gitsn_Node_XY_26b;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_26b *Gitsn_Node_XY_26b_new(Gitsn_Offset_B13 x, 
																 Gitsn_Offset_B13 y, Dz1Error *err);
static __inline__ Gitsn_Node_XY_26b *Gitsn_Node_XY_26b_gen(Dz1Error *err) { return Gitsn_Node_XY_26b_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_XY_26b_copy(Gitsn_Node_XY_26b *dst, Gitsn_Node_XY_26b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_26b *Gitsn_Node_XY_26b_clone(Gitsn_Node_XY_26b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_26b_purge(Gitsn_Node_XY_26b *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_26b_del(Gitsn_Node_XY_26b *p);
static __inline__ void Gitsn_Node_XY_26b_delAndSetNull(void *ptr)
{
	Gitsn_Node_XY_26b **p = (Gitsn_Node_XY_26b **)ptr;
	if (p) { Gitsn_Node_XY_26b_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_26b_dump(Gitsn_Node_XY_26b *p, int tab);
// Gitsn_Node_XY_26b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_28b
typedef struct Gitsn_Node_XY_28b
{
	Gitsn_Offset_B14	x;
	Gitsn_Offset_B14	y;
} Gitsn_Node_XY_28b;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_28b *Gitsn_Node_XY_28b_new(Gitsn_Offset_B14 x, 
																 Gitsn_Offset_B14 y, Dz1Error *err);
static __inline__ Gitsn_Node_XY_28b *Gitsn_Node_XY_28b_gen(Dz1Error *err) { return Gitsn_Node_XY_28b_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_XY_28b_copy(Gitsn_Node_XY_28b *dst, Gitsn_Node_XY_28b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_28b *Gitsn_Node_XY_28b_clone(Gitsn_Node_XY_28b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_28b_purge(Gitsn_Node_XY_28b *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_28b_del(Gitsn_Node_XY_28b *p);
static __inline__ void Gitsn_Node_XY_28b_delAndSetNull(void *ptr)
{
	Gitsn_Node_XY_28b **p = (Gitsn_Node_XY_28b **)ptr;
	if (p) { Gitsn_Node_XY_28b_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_28b_dump(Gitsn_Node_XY_28b *p, int tab);
// Gitsn_Node_XY_28b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_32b
typedef struct Gitsn_Node_XY_32b
{
	Gitsn_Offset_B16	x;
	Gitsn_Offset_B16	y;
} Gitsn_Node_XY_32b;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_32b *Gitsn_Node_XY_32b_new(Gitsn_Offset_B16 x, 
																 Gitsn_Offset_B16 y, Dz1Error *err);
static __inline__ Gitsn_Node_XY_32b *Gitsn_Node_XY_32b_gen(Dz1Error *err) { return Gitsn_Node_XY_32b_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_XY_32b_copy(Gitsn_Node_XY_32b *dst, Gitsn_Node_XY_32b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_XY_32b *Gitsn_Node_XY_32b_clone(Gitsn_Node_XY_32b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_32b_purge(Gitsn_Node_XY_32b *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_32b_del(Gitsn_Node_XY_32b *p);
static __inline__ void Gitsn_Node_XY_32b_delAndSetNull(void *ptr)
{
	Gitsn_Node_XY_32b **p = (Gitsn_Node_XY_32b **)ptr;
	if (p) { Gitsn_Node_XY_32b_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_XY_32b_dump(Gitsn_Node_XY_32b *p, int tab);
// Gitsn_Node_XY_32b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LLmD_64b
typedef struct Gitsn_Node_LLmD_64b
{
	Gitsn_Longitude		lon;
	Gitsn_Latitude		lat;
} Gitsn_Node_LLmD_64b;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LLmD_64b *Gitsn_Node_LLmD_64b_new(Gitsn_Longitude lon, 
																	 Gitsn_Latitude lat, Dz1Error *err);
static __inline__ Gitsn_Node_LLmD_64b *Gitsn_Node_LLmD_64b_gen(Dz1Error *err) { return Gitsn_Node_LLmD_64b_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_LLmD_64b_copy(Gitsn_Node_LLmD_64b *dst, Gitsn_Node_LLmD_64b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LLmD_64b *Gitsn_Node_LLmD_64b_clone(Gitsn_Node_LLmD_64b *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LLmD_64b_purge(Gitsn_Node_LLmD_64b *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LLmD_64b_del(Gitsn_Node_LLmD_64b *p);
static __inline__ void Gitsn_Node_LLmD_64b_delAndSetNull(void *ptr)
{
	Gitsn_Node_LLmD_64b **p = (Gitsn_Node_LLmD_64b **)ptr;
	if (p) { Gitsn_Node_LLmD_64b_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LLmD_64b_dump(Gitsn_Node_LLmD_64b *p, int tab);
// Gitsn_Node_LLmD_64b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeOffsetPointXYPresent
typedef enum Gitsn_NodeOffsetPointXYPresent
{
	Gitsn_NodeOffsetPointXYPresent_node_XY1,
	Gitsn_NodeOffsetPointXYPresent_node_XY2,
	Gitsn_NodeOffsetPointXYPresent_node_XY3,
	Gitsn_NodeOffsetPointXYPresent_node_XY4,
	Gitsn_NodeOffsetPointXYPresent_node_XY5,
	Gitsn_NodeOffsetPointXYPresent_node_XY6,
	Gitsn_NodeOffsetPointXYPresent_node_LatLon,
	Gitsn_NodeOffsetPointXYPresent_max
} Gitsn_NodeOffsetPointXYPresent;

DZ1_CPPLINK str_t Gitsn_NodeOffsetPointXYPresentStrA(Gitsn_NodeOffsetPointXYPresent v);
DZ1_CPPLINK Gitsn_NodeOffsetPointXYPresent Gitsn_NodeOffsetPointXYPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NodeOffsetPointXYPresentStrW(Gitsn_NodeOffsetPointXYPresent v);
DZ1_CPPLINK Gitsn_NodeOffsetPointXYPresent Gitsn_NodeOffsetPointXYPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NodeOffsetPointXYPresentStr Gitsn_NodeOffsetPointXYPresentStrW
#define Gitsn_NodeOffsetPointXYPresentFromStr Gitsn_NodeOffsetPointXYPresentFromStrW
#else // UNICODE
#define Gitsn_NodeOffsetPointXYPresentStr Gitsn_NodeOffsetPointXYPresentStrA
#define Gitsn_NodeOffsetPointXYPresentFromStr Gitsn_NodeOffsetPointXYPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NodeOffsetPointXYPresentStr Gitsn_NodeOffsetPointXYPresentStrA
#define Gitsn_NodeOffsetPointXYPresentFromStr Gitsn_NodeOffsetPointXYPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeOffsetPointXYPresent *Gitsn_NodeOffsetPointXYPresent_new(Gitsn_NodeOffsetPointXYPresent *src, Dz1Error *err);
static __inline__ Gitsn_NodeOffsetPointXYPresent *Gitsn_NodeOffsetPointXYPresent_gen(Dz1Error *err) { Gitsn_NodeOffsetPointXYPresent v = Gitsn_NodeOffsetPointXYPresent_max; return Gitsn_NodeOffsetPointXYPresent_new(&v, err); }
#define Gitsn_NodeOffsetPointXYPresent_clone             Gitsn_NodeOffsetPointXYPresent_new
static __inline__ void Gitsn_NodeOffsetPointXYPresent_del(Gitsn_NodeOffsetPointXYPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_NodeOffsetPointXYPresent_delAndSetNull(void *ptr)
{
	Gitsn_NodeOffsetPointXYPresent **p = (Gitsn_NodeOffsetPointXYPresent **)ptr;
	if (p != NULL) { Gitsn_NodeOffsetPointXYPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeOffsetPointXYPresent_dump(Gitsn_NodeOffsetPointXYPresent *v, int tab);
// Gitsn_NodeOffsetPointXYPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeOffsetPointXY
typedef struct Gitsn_NodeOffsetPointXY
{
	Gitsn_NodeOffsetPointXYPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_Node_XY_20b		*node_XY1;
		Gitsn_Node_XY_22b		*node_XY2;
		Gitsn_Node_XY_24b		*node_XY3;
		Gitsn_Node_XY_26b		*node_XY4;
		Gitsn_Node_XY_28b		*node_XY5;
		Gitsn_Node_XY_32b		*node_XY6;
		Gitsn_Node_LLmD_64b		*node_LatLon;
	} x;
} Gitsn_NodeOffsetPointXY;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeOffsetPointXY *Gitsn_NodeOffsetPointXY_new(Gitsn_NodeOffsetPointXYPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_NodeOffsetPointXY *Gitsn_NodeOffsetPointXY_gen(Dz1Error *err) { return Gitsn_NodeOffsetPointXY_new(Gitsn_NodeOffsetPointXYPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_NodeOffsetPointXY_copy(Gitsn_NodeOffsetPointXY *dst, Gitsn_NodeOffsetPointXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeOffsetPointXY *Gitsn_NodeOffsetPointXY_clone(Gitsn_NodeOffsetPointXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeOffsetPointXY_purge(Gitsn_NodeOffsetPointXY *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeOffsetPointXY_del(Gitsn_NodeOffsetPointXY *p);
static __inline__ void Gitsn_NodeOffsetPointXY_delAndSetNull(void *ptr)
{
	Gitsn_NodeOffsetPointXY **p = (Gitsn_NodeOffsetPointXY **)ptr;
	if (p != NULL) { Gitsn_NodeOffsetPointXY_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeOffsetPointXY_dump(Gitsn_NodeOffsetPointXY *p, int tab);
// Gitsn_NodeOffsetPointXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeXYList
typedef struct Gitsn_NodeAttributeXYList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_NodeAttributeXYList *p);
	Dz1Error (*travel)(struct Gitsn_NodeAttributeXYList *p, Dz1Error (*func)(void *ptr, Gitsn_NodeAttributeXY *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_NodeAttributeXYList *p, Dz1Error (*func)(void *ptr, Gitsn_NodeAttributeXY *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_NodeAttributeXYList *p, Dz1Error (*func)(void *ptr, Gitsn_NodeAttributeXY *entry), void *ptr);
	Gitsn_NodeAttributeXY *(*get_array)(struct Gitsn_NodeAttributeXYList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_NodeAttributeXYList *p, Gitsn_NodeAttributeXY data);
	Gitsn_NodeAttributeXY *(*extract)(struct Gitsn_NodeAttributeXYList *p, Gitsn_NodeAttributeXY *ptr);
	Gitsn_NodeAttributeXY *(*getHead)(struct Gitsn_NodeAttributeXYList *p);
} Gitsn_NodeAttributeXYList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeXYList *Gitsn_NodeAttributeXYList_new(Dz1Error *err);
static __inline__ Gitsn_NodeAttributeXYList *Gitsn_NodeAttributeXYList_gen(Dz1Error *err) { return Gitsn_NodeAttributeXYList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeXYList *Gitsn_NodeAttributeXYList_clone(Gitsn_NodeAttributeXYList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeXYList_purge(Gitsn_NodeAttributeXYList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeXYList_del(Gitsn_NodeAttributeXYList *p);
static __inline__ void Gitsn_NodeAttributeXYList_delAndSetNull(void *ptr)
{
	Gitsn_NodeAttributeXYList **p = (Gitsn_NodeAttributeXYList **)ptr;
	if (p != NULL) { Gitsn_NodeAttributeXYList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeXYList_dump(Gitsn_NodeAttributeXYList *p, int tab);

// Gitsn_NodeAttributeXYList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SegmentAttributeXYList
typedef struct Gitsn_SegmentAttributeXYList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_SegmentAttributeXYList *p);
	Dz1Error (*travel)(struct Gitsn_SegmentAttributeXYList *p, Dz1Error (*func)(void *ptr, Gitsn_SegmentAttributeXY *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_SegmentAttributeXYList *p, Dz1Error (*func)(void *ptr, Gitsn_SegmentAttributeXY *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_SegmentAttributeXYList *p, Dz1Error (*func)(void *ptr, Gitsn_SegmentAttributeXY *entry), void *ptr);
	Gitsn_SegmentAttributeXY *(*get_array)(struct Gitsn_SegmentAttributeXYList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_SegmentAttributeXYList *p, Gitsn_SegmentAttributeXY data);
	Gitsn_SegmentAttributeXY *(*extract)(struct Gitsn_SegmentAttributeXYList *p, Gitsn_SegmentAttributeXY *ptr);
	Gitsn_SegmentAttributeXY *(*getHead)(struct Gitsn_SegmentAttributeXYList *p);
} Gitsn_SegmentAttributeXYList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SegmentAttributeXYList *Gitsn_SegmentAttributeXYList_new(Dz1Error *err);
static __inline__ Gitsn_SegmentAttributeXYList *Gitsn_SegmentAttributeXYList_gen(Dz1Error *err) { return Gitsn_SegmentAttributeXYList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SegmentAttributeXYList *Gitsn_SegmentAttributeXYList_clone(Gitsn_SegmentAttributeXYList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SegmentAttributeXYList_purge(Gitsn_SegmentAttributeXYList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SegmentAttributeXYList_del(Gitsn_SegmentAttributeXYList *p);
static __inline__ void Gitsn_SegmentAttributeXYList_delAndSetNull(void *ptr)
{
	Gitsn_SegmentAttributeXYList **p = (Gitsn_SegmentAttributeXYList **)ptr;
	if (p != NULL) { Gitsn_SegmentAttributeXYList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SegmentAttributeXYList_dump(Gitsn_SegmentAttributeXYList *p, int tab);

// Gitsn_SegmentAttributeXYList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneDataAttributePresent
typedef enum Gitsn_LaneDataAttributePresent
{
	Gitsn_LaneDataAttributePresent_pathEndPointAngle,
	Gitsn_LaneDataAttributePresent_laneCrownPointCenter,
	Gitsn_LaneDataAttributePresent_laneCrownPointLeft,
	Gitsn_LaneDataAttributePresent_laneCrownPointRight,
	Gitsn_LaneDataAttributePresent_laneAngle,
	Gitsn_LaneDataAttributePresent_speedLimits,
	Gitsn_LaneDataAttributePresent_max
} Gitsn_LaneDataAttributePresent;

DZ1_CPPLINK str_t Gitsn_LaneDataAttributePresentStrA(Gitsn_LaneDataAttributePresent v);
DZ1_CPPLINK Gitsn_LaneDataAttributePresent Gitsn_LaneDataAttributePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_LaneDataAttributePresentStrW(Gitsn_LaneDataAttributePresent v);
DZ1_CPPLINK Gitsn_LaneDataAttributePresent Gitsn_LaneDataAttributePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_LaneDataAttributePresentStr Gitsn_LaneDataAttributePresentStrW
#define Gitsn_LaneDataAttributePresentFromStr Gitsn_LaneDataAttributePresentFromStrW
#else // UNICODE
#define Gitsn_LaneDataAttributePresentStr Gitsn_LaneDataAttributePresentStrA
#define Gitsn_LaneDataAttributePresentFromStr Gitsn_LaneDataAttributePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_LaneDataAttributePresentStr Gitsn_LaneDataAttributePresentStrA
#define Gitsn_LaneDataAttributePresentFromStr Gitsn_LaneDataAttributePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneDataAttributePresent *Gitsn_LaneDataAttributePresent_new(Gitsn_LaneDataAttributePresent *src, Dz1Error *err);
static __inline__ Gitsn_LaneDataAttributePresent *Gitsn_LaneDataAttributePresent_gen(Dz1Error *err) { Gitsn_LaneDataAttributePresent v = Gitsn_LaneDataAttributePresent_max; return Gitsn_LaneDataAttributePresent_new(&v, err); }
#define Gitsn_LaneDataAttributePresent_clone             Gitsn_LaneDataAttributePresent_new
static __inline__ void Gitsn_LaneDataAttributePresent_del(Gitsn_LaneDataAttributePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_LaneDataAttributePresent_delAndSetNull(void *ptr)
{
	Gitsn_LaneDataAttributePresent **p = (Gitsn_LaneDataAttributePresent **)ptr;
	if (p != NULL) { Gitsn_LaneDataAttributePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneDataAttributePresent_dump(Gitsn_LaneDataAttributePresent *v, int tab);
// Gitsn_LaneDataAttributePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneDataAttribute
typedef struct Gitsn_LaneDataAttribute
{
	Gitsn_LaneDataAttributePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_DeltaAngle				 pathEndPointAngle;
		Gitsn_RoadwayCrownAngle			 laneCrownPointCenter;
		Gitsn_RoadwayCrownAngle			 laneCrownPointLeft;
		Gitsn_RoadwayCrownAngle			 laneCrownPointRight;
		Gitsn_MergeDivergeNodeAngle		 laneAngle;
		Gitsn_SpeedLimitList			*speedLimits;
	} x;
} Gitsn_LaneDataAttribute;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneDataAttribute *Gitsn_LaneDataAttribute_new(Gitsn_LaneDataAttributePresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_LaneDataAttribute *Gitsn_LaneDataAttribute_gen(Dz1Error *err) { return Gitsn_LaneDataAttribute_new(Gitsn_LaneDataAttributePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_LaneDataAttribute_copy(Gitsn_LaneDataAttribute *dst, Gitsn_LaneDataAttribute *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneDataAttribute *Gitsn_LaneDataAttribute_clone(Gitsn_LaneDataAttribute *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneDataAttribute_purge(Gitsn_LaneDataAttribute *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneDataAttribute_del(Gitsn_LaneDataAttribute *p);
static __inline__ void Gitsn_LaneDataAttribute_delAndSetNull(void *ptr)
{
	Gitsn_LaneDataAttribute **p = (Gitsn_LaneDataAttribute **)ptr;
	if (p != NULL) { Gitsn_LaneDataAttribute_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneDataAttribute_dump(Gitsn_LaneDataAttribute *p, int tab);
// Gitsn_LaneDataAttribute
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneDataAttributeList
typedef struct Gitsn_LaneDataAttributeList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_LaneDataAttributeList *p);
	Dz1Error (*travel)(struct Gitsn_LaneDataAttributeList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneDataAttribute *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_LaneDataAttributeList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneDataAttribute *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_LaneDataAttributeList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneDataAttribute *entry), void *ptr);
	Gitsn_LaneDataAttribute **(*get_array)(struct Gitsn_LaneDataAttributeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_LaneDataAttributeList *p, Gitsn_LaneDataAttribute *data);
	Gitsn_LaneDataAttribute *(*extract)(struct Gitsn_LaneDataAttributeList *p, Gitsn_LaneDataAttribute *ptr);
	Gitsn_LaneDataAttribute *(*getHead)(struct Gitsn_LaneDataAttributeList *p);
} Gitsn_LaneDataAttributeList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneDataAttributeList *Gitsn_LaneDataAttributeList_new(Dz1Error *err);
static __inline__ Gitsn_LaneDataAttributeList *Gitsn_LaneDataAttributeList_gen(Dz1Error *err) { return Gitsn_LaneDataAttributeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneDataAttributeList *Gitsn_LaneDataAttributeList_clone(Gitsn_LaneDataAttributeList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneDataAttributeList_purge(Gitsn_LaneDataAttributeList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneDataAttributeList_del(Gitsn_LaneDataAttributeList *p);
static __inline__ void Gitsn_LaneDataAttributeList_delAndSetNull(void *ptr)
{
	Gitsn_LaneDataAttributeList **p = (Gitsn_LaneDataAttributeList **)ptr;
	if (p != NULL) { Gitsn_LaneDataAttributeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneDataAttributeList_dump(Gitsn_LaneDataAttributeList *p, int tab);

// Gitsn_LaneDataAttributeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeSetXY
typedef struct Gitsn_NodeAttributeSetXY
{
	Gitsn_NodeAttributeXYList		*localNode;
	Gitsn_SegmentAttributeXYList	*disabled;
	Gitsn_SegmentAttributeXYList	*enabled;
	Gitsn_LaneDataAttributeList		*data;
	Gitsn_Offset_B10				 dWidth;
	Gitsn_Offset_B10				 dElevation;
} Gitsn_NodeAttributeSetXY;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeSetXY *Gitsn_NodeAttributeSetXY_new(Dz1Error *err);
static __inline__ Gitsn_NodeAttributeSetXY *Gitsn_NodeAttributeSetXY_gen(Dz1Error *err) { return Gitsn_NodeAttributeSetXY_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_NodeAttributeSetXY_copy(Gitsn_NodeAttributeSetXY *dst, Gitsn_NodeAttributeSetXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeSetXY *Gitsn_NodeAttributeSetXY_clone(Gitsn_NodeAttributeSetXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeSetXY_purge(Gitsn_NodeAttributeSetXY *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeSetXY_del(Gitsn_NodeAttributeSetXY *p);
static __inline__ void Gitsn_NodeAttributeSetXY_delAndSetNull(void *ptr)
{
	Gitsn_NodeAttributeSetXY **p = (Gitsn_NodeAttributeSetXY **)ptr;
	if (p) { Gitsn_NodeAttributeSetXY_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeSetXY_dump(Gitsn_NodeAttributeSetXY *p, int tab);
// Gitsn_NodeAttributeSetXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeXY
typedef struct Gitsn_NodeXY
{
	Gitsn_NodeOffsetPointXY		*delta;
	Gitsn_NodeAttributeSetXY	*attributes;
} Gitsn_NodeXY;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeXY *Gitsn_NodeXY_new(Gitsn_NodeOffsetPointXY *delta, 
													   Gitsn_NodeAttributeSetXY *attributes, Dz1Error *err);
static __inline__ Gitsn_NodeXY *Gitsn_NodeXY_gen(Dz1Error *err) { return Gitsn_NodeXY_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_NodeXY_copy(Gitsn_NodeXY *dst, Gitsn_NodeXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeXY *Gitsn_NodeXY_clone(Gitsn_NodeXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeXY_purge(Gitsn_NodeXY *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeXY_del(Gitsn_NodeXY *p);
static __inline__ void Gitsn_NodeXY_delAndSetNull(void *ptr)
{
	Gitsn_NodeXY **p = (Gitsn_NodeXY **)ptr;
	if (p) { Gitsn_NodeXY_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeXY_dump(Gitsn_NodeXY *p, int tab);
// Gitsn_NodeXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeSetXY
typedef struct Gitsn_NodeSetXY
{
	void *storage;
	unsigned int (*count)(struct Gitsn_NodeSetXY *p);
	Dz1Error (*travel)(struct Gitsn_NodeSetXY *p, Dz1Error (*func)(void *ptr, Gitsn_NodeXY *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_NodeSetXY *p, Dz1Error (*func)(void *ptr, Gitsn_NodeXY *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_NodeSetXY *p, Dz1Error (*func)(void *ptr, Gitsn_NodeXY *entry), void *ptr);
	Gitsn_NodeXY **(*get_array)(struct Gitsn_NodeSetXY *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_NodeSetXY *p, Gitsn_NodeXY *data);
	Gitsn_NodeXY *(*extract)(struct Gitsn_NodeSetXY *p, Gitsn_NodeXY *ptr);
	Gitsn_NodeXY *(*getHead)(struct Gitsn_NodeSetXY *p);
} Gitsn_NodeSetXY;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeSetXY *Gitsn_NodeSetXY_new(Dz1Error *err);
static __inline__ Gitsn_NodeSetXY *Gitsn_NodeSetXY_gen(Dz1Error *err) { return Gitsn_NodeSetXY_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeSetXY *Gitsn_NodeSetXY_clone(Gitsn_NodeSetXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeSetXY_purge(Gitsn_NodeSetXY *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeSetXY_del(Gitsn_NodeSetXY *p);
static __inline__ void Gitsn_NodeSetXY_delAndSetNull(void *ptr)
{
	Gitsn_NodeSetXY **p = (Gitsn_NodeSetXY **)ptr;
	if (p != NULL) { Gitsn_NodeSetXY_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeSetXY_dump(Gitsn_NodeSetXY *p, int tab);

// Gitsn_NodeSetXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ComputedLane_offsetXaxisPresent
typedef enum Gitsn_ComputedLane_offsetXaxisPresent
{
	Gitsn_ComputedLane_offsetXaxisPresent_small,
	Gitsn_ComputedLane_offsetXaxisPresent_large,
	Gitsn_ComputedLane_offsetXaxisPresent_max
} Gitsn_ComputedLane_offsetXaxisPresent;

DZ1_CPPLINK str_t Gitsn_ComputedLane_offsetXaxisPresentStrA(Gitsn_ComputedLane_offsetXaxisPresent v);
DZ1_CPPLINK Gitsn_ComputedLane_offsetXaxisPresent Gitsn_ComputedLane_offsetXaxisPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ComputedLane_offsetXaxisPresentStrW(Gitsn_ComputedLane_offsetXaxisPresent v);
DZ1_CPPLINK Gitsn_ComputedLane_offsetXaxisPresent Gitsn_ComputedLane_offsetXaxisPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ComputedLane_offsetXaxisPresentStr Gitsn_ComputedLane_offsetXaxisPresentStrW
#define Gitsn_ComputedLane_offsetXaxisPresentFromStr Gitsn_ComputedLane_offsetXaxisPresentFromStrW
#else // UNICODE
#define Gitsn_ComputedLane_offsetXaxisPresentStr Gitsn_ComputedLane_offsetXaxisPresentStrA
#define Gitsn_ComputedLane_offsetXaxisPresentFromStr Gitsn_ComputedLane_offsetXaxisPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ComputedLane_offsetXaxisPresentStr Gitsn_ComputedLane_offsetXaxisPresentStrA
#define Gitsn_ComputedLane_offsetXaxisPresentFromStr Gitsn_ComputedLane_offsetXaxisPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ComputedLane_offsetXaxisPresent *Gitsn_ComputedLane_offsetXaxisPresent_new(Gitsn_ComputedLane_offsetXaxisPresent *src, Dz1Error *err);
static __inline__ Gitsn_ComputedLane_offsetXaxisPresent *Gitsn_ComputedLane_offsetXaxisPresent_gen(Dz1Error *err) { Gitsn_ComputedLane_offsetXaxisPresent v = Gitsn_ComputedLane_offsetXaxisPresent_max; return Gitsn_ComputedLane_offsetXaxisPresent_new(&v, err); }
#define Gitsn_ComputedLane_offsetXaxisPresent_clone             Gitsn_ComputedLane_offsetXaxisPresent_new
static __inline__ void Gitsn_ComputedLane_offsetXaxisPresent_del(Gitsn_ComputedLane_offsetXaxisPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ComputedLane_offsetXaxisPresent_delAndSetNull(void *ptr)
{
	Gitsn_ComputedLane_offsetXaxisPresent **p = (Gitsn_ComputedLane_offsetXaxisPresent **)ptr;
	if (p != NULL) { Gitsn_ComputedLane_offsetXaxisPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_offsetXaxisPresent_dump(Gitsn_ComputedLane_offsetXaxisPresent *v, int tab);
// Gitsn_ComputedLane_offsetXaxisPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ComputedLane_offsetXaxis
typedef struct Gitsn_ComputedLane_offsetXaxis
{
	Gitsn_ComputedLane_offsetXaxisPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_DrivenLineOffsetSm	small;
		Gitsn_DrivenLineOffsetLg	large;
	} x;
} Gitsn_ComputedLane_offsetXaxis;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ComputedLane_offsetXaxis *Gitsn_ComputedLane_offsetXaxis_new(Gitsn_ComputedLane_offsetXaxisPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_ComputedLane_offsetXaxis *Gitsn_ComputedLane_offsetXaxis_gen(Dz1Error *err) { return Gitsn_ComputedLane_offsetXaxis_new(Gitsn_ComputedLane_offsetXaxisPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_ComputedLane_offsetXaxis_copy(Gitsn_ComputedLane_offsetXaxis *dst, Gitsn_ComputedLane_offsetXaxis *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ComputedLane_offsetXaxis *Gitsn_ComputedLane_offsetXaxis_clone(Gitsn_ComputedLane_offsetXaxis *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_offsetXaxis_purge(Gitsn_ComputedLane_offsetXaxis *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_offsetXaxis_del(Gitsn_ComputedLane_offsetXaxis *p);
static __inline__ void Gitsn_ComputedLane_offsetXaxis_delAndSetNull(void *ptr)
{
	Gitsn_ComputedLane_offsetXaxis **p = (Gitsn_ComputedLane_offsetXaxis **)ptr;
	if (p != NULL) { Gitsn_ComputedLane_offsetXaxis_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_offsetXaxis_dump(Gitsn_ComputedLane_offsetXaxis *p, int tab);
// Gitsn_ComputedLane_offsetXaxis
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ComputedLane_offsetYaxisPresent
typedef enum Gitsn_ComputedLane_offsetYaxisPresent
{
	Gitsn_ComputedLane_offsetYaxisPresent_small,
	Gitsn_ComputedLane_offsetYaxisPresent_large,
	Gitsn_ComputedLane_offsetYaxisPresent_max
} Gitsn_ComputedLane_offsetYaxisPresent;

DZ1_CPPLINK str_t Gitsn_ComputedLane_offsetYaxisPresentStrA(Gitsn_ComputedLane_offsetYaxisPresent v);
DZ1_CPPLINK Gitsn_ComputedLane_offsetYaxisPresent Gitsn_ComputedLane_offsetYaxisPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ComputedLane_offsetYaxisPresentStrW(Gitsn_ComputedLane_offsetYaxisPresent v);
DZ1_CPPLINK Gitsn_ComputedLane_offsetYaxisPresent Gitsn_ComputedLane_offsetYaxisPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ComputedLane_offsetYaxisPresentStr Gitsn_ComputedLane_offsetYaxisPresentStrW
#define Gitsn_ComputedLane_offsetYaxisPresentFromStr Gitsn_ComputedLane_offsetYaxisPresentFromStrW
#else // UNICODE
#define Gitsn_ComputedLane_offsetYaxisPresentStr Gitsn_ComputedLane_offsetYaxisPresentStrA
#define Gitsn_ComputedLane_offsetYaxisPresentFromStr Gitsn_ComputedLane_offsetYaxisPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ComputedLane_offsetYaxisPresentStr Gitsn_ComputedLane_offsetYaxisPresentStrA
#define Gitsn_ComputedLane_offsetYaxisPresentFromStr Gitsn_ComputedLane_offsetYaxisPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ComputedLane_offsetYaxisPresent *Gitsn_ComputedLane_offsetYaxisPresent_new(Gitsn_ComputedLane_offsetYaxisPresent *src, Dz1Error *err);
static __inline__ Gitsn_ComputedLane_offsetYaxisPresent *Gitsn_ComputedLane_offsetYaxisPresent_gen(Dz1Error *err) { Gitsn_ComputedLane_offsetYaxisPresent v = Gitsn_ComputedLane_offsetYaxisPresent_max; return Gitsn_ComputedLane_offsetYaxisPresent_new(&v, err); }
#define Gitsn_ComputedLane_offsetYaxisPresent_clone             Gitsn_ComputedLane_offsetYaxisPresent_new
static __inline__ void Gitsn_ComputedLane_offsetYaxisPresent_del(Gitsn_ComputedLane_offsetYaxisPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ComputedLane_offsetYaxisPresent_delAndSetNull(void *ptr)
{
	Gitsn_ComputedLane_offsetYaxisPresent **p = (Gitsn_ComputedLane_offsetYaxisPresent **)ptr;
	if (p != NULL) { Gitsn_ComputedLane_offsetYaxisPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_offsetYaxisPresent_dump(Gitsn_ComputedLane_offsetYaxisPresent *v, int tab);
// Gitsn_ComputedLane_offsetYaxisPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ComputedLane_offsetYaxis
typedef struct Gitsn_ComputedLane_offsetYaxis
{
	Gitsn_ComputedLane_offsetYaxisPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_DrivenLineOffsetSm	small;
		Gitsn_DrivenLineOffsetLg	large;
	} x;
} Gitsn_ComputedLane_offsetYaxis;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ComputedLane_offsetYaxis *Gitsn_ComputedLane_offsetYaxis_new(Gitsn_ComputedLane_offsetYaxisPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_ComputedLane_offsetYaxis *Gitsn_ComputedLane_offsetYaxis_gen(Dz1Error *err) { return Gitsn_ComputedLane_offsetYaxis_new(Gitsn_ComputedLane_offsetYaxisPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_ComputedLane_offsetYaxis_copy(Gitsn_ComputedLane_offsetYaxis *dst, Gitsn_ComputedLane_offsetYaxis *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ComputedLane_offsetYaxis *Gitsn_ComputedLane_offsetYaxis_clone(Gitsn_ComputedLane_offsetYaxis *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_offsetYaxis_purge(Gitsn_ComputedLane_offsetYaxis *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_offsetYaxis_del(Gitsn_ComputedLane_offsetYaxis *p);
static __inline__ void Gitsn_ComputedLane_offsetYaxis_delAndSetNull(void *ptr)
{
	Gitsn_ComputedLane_offsetYaxis **p = (Gitsn_ComputedLane_offsetYaxis **)ptr;
	if (p != NULL) { Gitsn_ComputedLane_offsetYaxis_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_offsetYaxis_dump(Gitsn_ComputedLane_offsetYaxis *p, int tab);
// Gitsn_ComputedLane_offsetYaxis
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ComputedLane
typedef struct Gitsn_ComputedLane
{
	Gitsn_LaneID						 referenceLaneId;
	Gitsn_ComputedLane_offsetXaxis		*offsetXaxis;
	Gitsn_ComputedLane_offsetYaxis		*offsetYaxis;
	Gitsn_Angle							 rotateXY;
	Gitsn_Scale_B12						 scaleXaxis;
	Gitsn_Scale_B12						 scaleYaxis;
} Gitsn_ComputedLane;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ComputedLane *Gitsn_ComputedLane_new(Gitsn_LaneID referenceLaneId, 
																   Gitsn_ComputedLane_offsetXaxis *offsetXaxis, 
																   Gitsn_ComputedLane_offsetYaxis *offsetYaxis, Dz1Error *err);
static __inline__ Gitsn_ComputedLane *Gitsn_ComputedLane_gen(Dz1Error *err) { return Gitsn_ComputedLane_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ComputedLane_copy(Gitsn_ComputedLane *dst, Gitsn_ComputedLane *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ComputedLane *Gitsn_ComputedLane_clone(Gitsn_ComputedLane *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_purge(Gitsn_ComputedLane *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_del(Gitsn_ComputedLane *p);
static __inline__ void Gitsn_ComputedLane_delAndSetNull(void *ptr)
{
	Gitsn_ComputedLane **p = (Gitsn_ComputedLane **)ptr;
	if (p) { Gitsn_ComputedLane_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ComputedLane_dump(Gitsn_ComputedLane *p, int tab);
// Gitsn_ComputedLane
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeListXYPresent
typedef enum Gitsn_NodeListXYPresent
{
	Gitsn_NodeListXYPresent_nodes,
	Gitsn_NodeListXYPresent_computed,
	Gitsn_NodeListXYPresent_max
} Gitsn_NodeListXYPresent;

DZ1_CPPLINK str_t Gitsn_NodeListXYPresentStrA(Gitsn_NodeListXYPresent v);
DZ1_CPPLINK Gitsn_NodeListXYPresent Gitsn_NodeListXYPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NodeListXYPresentStrW(Gitsn_NodeListXYPresent v);
DZ1_CPPLINK Gitsn_NodeListXYPresent Gitsn_NodeListXYPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NodeListXYPresentStr Gitsn_NodeListXYPresentStrW
#define Gitsn_NodeListXYPresentFromStr Gitsn_NodeListXYPresentFromStrW
#else // UNICODE
#define Gitsn_NodeListXYPresentStr Gitsn_NodeListXYPresentStrA
#define Gitsn_NodeListXYPresentFromStr Gitsn_NodeListXYPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NodeListXYPresentStr Gitsn_NodeListXYPresentStrA
#define Gitsn_NodeListXYPresentFromStr Gitsn_NodeListXYPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeListXYPresent *Gitsn_NodeListXYPresent_new(Gitsn_NodeListXYPresent *src, Dz1Error *err);
static __inline__ Gitsn_NodeListXYPresent *Gitsn_NodeListXYPresent_gen(Dz1Error *err) { Gitsn_NodeListXYPresent v = Gitsn_NodeListXYPresent_max; return Gitsn_NodeListXYPresent_new(&v, err); }
#define Gitsn_NodeListXYPresent_clone             Gitsn_NodeListXYPresent_new
static __inline__ void Gitsn_NodeListXYPresent_del(Gitsn_NodeListXYPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_NodeListXYPresent_delAndSetNull(void *ptr)
{
	Gitsn_NodeListXYPresent **p = (Gitsn_NodeListXYPresent **)ptr;
	if (p != NULL) { Gitsn_NodeListXYPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeListXYPresent_dump(Gitsn_NodeListXYPresent *v, int tab);
// Gitsn_NodeListXYPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeListXY
typedef struct Gitsn_NodeListXY
{
	Gitsn_NodeListXYPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_NodeSetXY			*nodes;
		Gitsn_ComputedLane		*computed;
	} x;
} Gitsn_NodeListXY;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeListXY *Gitsn_NodeListXY_new(Gitsn_NodeListXYPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_NodeListXY *Gitsn_NodeListXY_gen(Dz1Error *err) { return Gitsn_NodeListXY_new(Gitsn_NodeListXYPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_NodeListXY_copy(Gitsn_NodeListXY *dst, Gitsn_NodeListXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeListXY *Gitsn_NodeListXY_clone(Gitsn_NodeListXY *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeListXY_purge(Gitsn_NodeListXY *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeListXY_del(Gitsn_NodeListXY *p);
static __inline__ void Gitsn_NodeListXY_delAndSetNull(void *ptr)
{
	Gitsn_NodeListXY **p = (Gitsn_NodeListXY **)ptr;
	if (p != NULL) { Gitsn_NodeListXY_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeListXY_dump(Gitsn_NodeListXY *p, int tab);
// Gitsn_NodeListXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConnectingLane
typedef struct Gitsn_ConnectingLane
{
	Gitsn_LaneID				 lane;
	Gitsn_AllowedManeuvers		*maneuver;
} Gitsn_ConnectingLane;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConnectingLane *Gitsn_ConnectingLane_new(Gitsn_LaneID lane, Dz1Error *err);
static __inline__ Gitsn_ConnectingLane *Gitsn_ConnectingLane_gen(Dz1Error *err) { return Gitsn_ConnectingLane_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ConnectingLane_copy(Gitsn_ConnectingLane *dst, Gitsn_ConnectingLane *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConnectingLane *Gitsn_ConnectingLane_clone(Gitsn_ConnectingLane *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectingLane_purge(Gitsn_ConnectingLane *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectingLane_del(Gitsn_ConnectingLane *p);
static __inline__ void Gitsn_ConnectingLane_delAndSetNull(void *ptr)
{
	Gitsn_ConnectingLane **p = (Gitsn_ConnectingLane **)ptr;
	if (p) { Gitsn_ConnectingLane_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectingLane_dump(Gitsn_ConnectingLane *p, int tab);
// Gitsn_ConnectingLane
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Connection
typedef struct Gitsn_Connection
{
	Gitsn_ConnectingLane				*connecctingLnae;
	Gitsn_IntersectionReferenceID		*remoteIntersection;
	Gitsn_SignalGroupID					 signalGroup;
	Gitsn_RestrictionClassID			 userClass;
	Gitsn_LaneConnectionID				 connectionID;
} Gitsn_Connection;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Connection *Gitsn_Connection_new(Gitsn_ConnectingLane *connecctingLnae, Dz1Error *err);
static __inline__ Gitsn_Connection *Gitsn_Connection_gen(Dz1Error *err) { return Gitsn_Connection_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Connection_copy(Gitsn_Connection *dst, Gitsn_Connection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Connection *Gitsn_Connection_clone(Gitsn_Connection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Connection_purge(Gitsn_Connection *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Connection_del(Gitsn_Connection *p);
static __inline__ void Gitsn_Connection_delAndSetNull(void *ptr)
{
	Gitsn_Connection **p = (Gitsn_Connection **)ptr;
	if (p) { Gitsn_Connection_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Connection_dump(Gitsn_Connection *p, int tab);
// Gitsn_Connection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConnectsToList
typedef struct Gitsn_ConnectsToList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_ConnectsToList *p);
	Dz1Error (*travel)(struct Gitsn_ConnectsToList *p, Dz1Error (*func)(void *ptr, Gitsn_Connection *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_ConnectsToList *p, Dz1Error (*func)(void *ptr, Gitsn_Connection *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_ConnectsToList *p, Dz1Error (*func)(void *ptr, Gitsn_Connection *entry), void *ptr);
	Gitsn_Connection **(*get_array)(struct Gitsn_ConnectsToList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_ConnectsToList *p, Gitsn_Connection *data);
	Gitsn_Connection *(*extract)(struct Gitsn_ConnectsToList *p, Gitsn_Connection *ptr);
	Gitsn_Connection *(*getHead)(struct Gitsn_ConnectsToList *p);
} Gitsn_ConnectsToList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConnectsToList *Gitsn_ConnectsToList_new(Dz1Error *err);
static __inline__ Gitsn_ConnectsToList *Gitsn_ConnectsToList_gen(Dz1Error *err) { return Gitsn_ConnectsToList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConnectsToList *Gitsn_ConnectsToList_clone(Gitsn_ConnectsToList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectsToList_purge(Gitsn_ConnectsToList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectsToList_del(Gitsn_ConnectsToList *p);
static __inline__ void Gitsn_ConnectsToList_delAndSetNull(void *ptr)
{
	Gitsn_ConnectsToList **p = (Gitsn_ConnectsToList **)ptr;
	if (p != NULL) { Gitsn_ConnectsToList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectsToList_dump(Gitsn_ConnectsToList *p, int tab);

// Gitsn_ConnectsToList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OverlayLaneList
typedef struct Gitsn_OverlayLaneList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_OverlayLaneList *p);
	Dz1Error (*travel)(struct Gitsn_OverlayLaneList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneID *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_OverlayLaneList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneID *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_OverlayLaneList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneID *entry), void *ptr);
	Gitsn_LaneID *(*get_array)(struct Gitsn_OverlayLaneList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_OverlayLaneList *p, Gitsn_LaneID data);
	Gitsn_LaneID *(*extract)(struct Gitsn_OverlayLaneList *p, Gitsn_LaneID *ptr);
	Gitsn_LaneID *(*getHead)(struct Gitsn_OverlayLaneList *p);
	int (*cmp)(Gitsn_LaneID *a, Gitsn_LaneID *b);
} Gitsn_OverlayLaneList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_OverlayLaneList *Gitsn_OverlayLaneList_new(Dz1Error *err);
static __inline__ Gitsn_OverlayLaneList *Gitsn_OverlayLaneList_gen(Dz1Error *err) { return Gitsn_OverlayLaneList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_OverlayLaneList *Gitsn_OverlayLaneList_clone(Gitsn_OverlayLaneList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OverlayLaneList_purge(Gitsn_OverlayLaneList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OverlayLaneList_del(Gitsn_OverlayLaneList *p);
static __inline__ void Gitsn_OverlayLaneList_delAndSetNull(void *ptr)
{
	Gitsn_OverlayLaneList **p = (Gitsn_OverlayLaneList **)ptr;
	if (p != NULL) { Gitsn_OverlayLaneList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OverlayLaneListA_dump(Gitsn_OverlayLaneList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OverlayLaneListA_fdump(FILE *fp, Gitsn_OverlayLaneList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OverlayLaneListW_dump(Gitsn_OverlayLaneList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OverlayLaneListW_fdump(FILE *fp, Gitsn_OverlayLaneList *p, int tab);
#ifdef UNICODE
#define Gitsn_OverlayLaneList_dump Gitsn_OverlayLaneListW_dump
#define Gitsn_OverlayLaneList_fdump Gitsn_OverlayLaneListW_fdump
#else //  UNICODE
#define Gitsn_OverlayLaneList_dump Gitsn_OverlayLaneListA_dump
#define Gitsn_OverlayLaneList_fdump Gitsn_OverlayLaneListA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_OverlayLaneListX_dump(Gitsn_OverlayLaneList *p, int tab) { DZ1_DUMP(Gitsn_OverlayLaneList, p, tab); }
static __inline__ void Gitsn_OverlayLaneListX_fdump(FILE *fp, Gitsn_OverlayLaneList *p, int tab) { DZ1_FDUMP(fp, Gitsn_OverlayLaneList, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_OverlayLaneList_dump Gitsn_OverlayLaneListA_dump
#define Gitsn_OverlayLaneListX_dump Gitsn_OverlayLaneListA_dump
#define Gitsn_OverlayLaneList_fdump Gitsn_OverlayLaneListA_fdump
#define Gitsn_OverlayLaneListX_fdump Gitsn_OverlayLaneListA_fdump
#endif // UNIX_SYSTEM

// Gitsn_OverlayLaneList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericLane
typedef struct Gitsn_GenericLane
{
	Gitsn_LaneID				 laneID;
	Gitsn_DescriptiveName		 name;
	Gitsn_ApproachID			 ingressApproach;
	Gitsn_ApproachID			 egressApproach;
	Gitsn_LaneAttributes		*laneAttributes;
	Gitsn_AllowedManeuvers		*maneuvers;
	Gitsn_NodeListXY			*nodeList;
	Gitsn_ConnectsToList		*connectsTo;
	Gitsn_OverlayLaneList		*overlays;
} Gitsn_GenericLane;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericLane *Gitsn_GenericLane_new(Gitsn_LaneID laneID, 
																 Gitsn_LaneAttributes *laneAttributes, 
																 Gitsn_NodeListXY *nodeList, Dz1Error *err);
static __inline__ Gitsn_GenericLane *Gitsn_GenericLane_gen(Dz1Error *err) { return Gitsn_GenericLane_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_GenericLane_copy(Gitsn_GenericLane *dst, Gitsn_GenericLane *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericLane *Gitsn_GenericLane_clone(Gitsn_GenericLane *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericLane_purge(Gitsn_GenericLane *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericLane_del(Gitsn_GenericLane *p);
static __inline__ void Gitsn_GenericLane_delAndSetNull(void *ptr)
{
	Gitsn_GenericLane **p = (Gitsn_GenericLane **)ptr;
	if (p) { Gitsn_GenericLane_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericLane_dump(Gitsn_GenericLane *p, int tab);
// Gitsn_GenericLane
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneList
typedef struct Gitsn_LaneList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_LaneList *p);
	Dz1Error (*travel)(struct Gitsn_LaneList *p, Dz1Error (*func)(void *ptr, Gitsn_GenericLane *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_LaneList *p, Dz1Error (*func)(void *ptr, Gitsn_GenericLane *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_LaneList *p, Dz1Error (*func)(void *ptr, Gitsn_GenericLane *entry), void *ptr);
	Gitsn_GenericLane **(*get_array)(struct Gitsn_LaneList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_LaneList *p, Gitsn_GenericLane *data);
	Gitsn_GenericLane *(*extract)(struct Gitsn_LaneList *p, Gitsn_GenericLane *ptr);
	Gitsn_GenericLane *(*getHead)(struct Gitsn_LaneList *p);
} Gitsn_LaneList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneList *Gitsn_LaneList_new(Dz1Error *err);
static __inline__ Gitsn_LaneList *Gitsn_LaneList_gen(Dz1Error *err) { return Gitsn_LaneList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_LaneList *Gitsn_LaneList_clone(Gitsn_LaneList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneList_purge(Gitsn_LaneList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneList_del(Gitsn_LaneList *p);
static __inline__ void Gitsn_LaneList_delAndSetNull(void *ptr)
{
	Gitsn_LaneList **p = (Gitsn_LaneList **)ptr;
	if (p != NULL) { Gitsn_LaneList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_LaneList_dump(Gitsn_LaneList *p, int tab);

// Gitsn_LaneList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalControlZone
typedef struct Gitsn_SignalControlZone
{
	u8_t	*zone;
} Gitsn_SignalControlZone;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalControlZone *Gitsn_SignalControlZone_new(u8_t *zone, Dz1Error *err);
static __inline__ Gitsn_SignalControlZone *Gitsn_SignalControlZone_gen(Dz1Error *err) { return Gitsn_SignalControlZone_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SignalControlZone_copy(Gitsn_SignalControlZone *dst, Gitsn_SignalControlZone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalControlZone *Gitsn_SignalControlZone_clone(Gitsn_SignalControlZone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalControlZone_purge(Gitsn_SignalControlZone *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalControlZone_del(Gitsn_SignalControlZone *p);
static __inline__ void Gitsn_SignalControlZone_delAndSetNull(void *ptr)
{
	Gitsn_SignalControlZone **p = (Gitsn_SignalControlZone **)ptr;
	if (p) { Gitsn_SignalControlZone_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalControlZone_dump(Gitsn_SignalControlZone *p, int tab);
// Gitsn_SignalControlZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PreemptPriorityList
typedef struct Gitsn_PreemptPriorityList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_PreemptPriorityList *p);
	Dz1Error (*travel)(struct Gitsn_PreemptPriorityList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalControlZone *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_PreemptPriorityList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalControlZone *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_PreemptPriorityList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalControlZone *entry), void *ptr);
	Gitsn_SignalControlZone **(*get_array)(struct Gitsn_PreemptPriorityList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_PreemptPriorityList *p, Gitsn_SignalControlZone *data);
	Gitsn_SignalControlZone *(*extract)(struct Gitsn_PreemptPriorityList *p, Gitsn_SignalControlZone *ptr);
	Gitsn_SignalControlZone *(*getHead)(struct Gitsn_PreemptPriorityList *p);
} Gitsn_PreemptPriorityList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PreemptPriorityList *Gitsn_PreemptPriorityList_new(Dz1Error *err);
static __inline__ Gitsn_PreemptPriorityList *Gitsn_PreemptPriorityList_gen(Dz1Error *err) { return Gitsn_PreemptPriorityList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PreemptPriorityList *Gitsn_PreemptPriorityList_clone(Gitsn_PreemptPriorityList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PreemptPriorityList_purge(Gitsn_PreemptPriorityList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PreemptPriorityList_del(Gitsn_PreemptPriorityList *p);
static __inline__ void Gitsn_PreemptPriorityList_delAndSetNull(void *ptr)
{
	Gitsn_PreemptPriorityList **p = (Gitsn_PreemptPriorityList **)ptr;
	if (p != NULL) { Gitsn_PreemptPriorityList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PreemptPriorityList_dump(Gitsn_PreemptPriorityList *p, int tab);

// Gitsn_PreemptPriorityList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionGeometry
typedef struct Gitsn_IntersectionGeometry
{
	Gitsn_DescriptiveName				 name;
	Gitsn_IntersectionReferenceID		*id;
	Gitsn_MsgCount						 revision;
	Gitsn_Position3D					*refPoint;
	Gitsn_LaneWidth						 laneWidth;
	Gitsn_SpeedLimitList				*speedLimits;
	Gitsn_LaneList						*laneSet;
	Gitsn_PreemptPriorityList			*preemptPriorityData;
} Gitsn_IntersectionGeometry;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionGeometry *Gitsn_IntersectionGeometry_new(Gitsn_IntersectionReferenceID *id, 
																				   Gitsn_MsgCount revision, 
																				   Gitsn_Position3D *refPoint, 
																				   Gitsn_LaneList *laneSet, Dz1Error *err);
static __inline__ Gitsn_IntersectionGeometry *Gitsn_IntersectionGeometry_gen(Dz1Error *err) { return Gitsn_IntersectionGeometry_new(NULL, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_IntersectionGeometry_copy(Gitsn_IntersectionGeometry *dst, Gitsn_IntersectionGeometry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionGeometry *Gitsn_IntersectionGeometry_clone(Gitsn_IntersectionGeometry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionGeometry_purge(Gitsn_IntersectionGeometry *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionGeometry_del(Gitsn_IntersectionGeometry *p);
static __inline__ void Gitsn_IntersectionGeometry_delAndSetNull(void *ptr)
{
	Gitsn_IntersectionGeometry **p = (Gitsn_IntersectionGeometry **)ptr;
	if (p) { Gitsn_IntersectionGeometry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionGeometry_dump(Gitsn_IntersectionGeometry *p, int tab);
// Gitsn_IntersectionGeometry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionGeometryList
typedef struct Gitsn_IntersectionGeometryList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_IntersectionGeometryList *p);
	Dz1Error (*travel)(struct Gitsn_IntersectionGeometryList *p, Dz1Error (*func)(void *ptr, Gitsn_IntersectionGeometry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_IntersectionGeometryList *p, Dz1Error (*func)(void *ptr, Gitsn_IntersectionGeometry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_IntersectionGeometryList *p, Dz1Error (*func)(void *ptr, Gitsn_IntersectionGeometry *entry), void *ptr);
	Gitsn_IntersectionGeometry **(*get_array)(struct Gitsn_IntersectionGeometryList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_IntersectionGeometryList *p, Gitsn_IntersectionGeometry *data);
	Gitsn_IntersectionGeometry *(*extract)(struct Gitsn_IntersectionGeometryList *p, Gitsn_IntersectionGeometry *ptr);
	Gitsn_IntersectionGeometry *(*getHead)(struct Gitsn_IntersectionGeometryList *p);
} Gitsn_IntersectionGeometryList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionGeometryList *Gitsn_IntersectionGeometryList_new(Dz1Error *err);
static __inline__ Gitsn_IntersectionGeometryList *Gitsn_IntersectionGeometryList_gen(Dz1Error *err) { return Gitsn_IntersectionGeometryList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionGeometryList *Gitsn_IntersectionGeometryList_clone(Gitsn_IntersectionGeometryList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionGeometryList_purge(Gitsn_IntersectionGeometryList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionGeometryList_del(Gitsn_IntersectionGeometryList *p);
static __inline__ void Gitsn_IntersectionGeometryList_delAndSetNull(void *ptr)
{
	Gitsn_IntersectionGeometryList **p = (Gitsn_IntersectionGeometryList **)ptr;
	if (p != NULL) { Gitsn_IntersectionGeometryList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionGeometryList_dump(Gitsn_IntersectionGeometryList *p, int tab);

// Gitsn_IntersectionGeometryList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSegmentReferenceID
typedef struct Gitsn_RoadSegmentReferenceID
{
	Gitsn_RoadRegulatorID		region;
	Gitsn_RoadSegmentID			id;
} Gitsn_RoadSegmentReferenceID;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSegmentReferenceID *Gitsn_RoadSegmentReferenceID_new(Gitsn_RoadRegulatorID region, 
																					   Gitsn_RoadSegmentID id, Dz1Error *err);
static __inline__ Gitsn_RoadSegmentReferenceID *Gitsn_RoadSegmentReferenceID_gen(Dz1Error *err) { return Gitsn_RoadSegmentReferenceID_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RoadSegmentReferenceID_copy(Gitsn_RoadSegmentReferenceID *dst, Gitsn_RoadSegmentReferenceID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSegmentReferenceID *Gitsn_RoadSegmentReferenceID_clone(Gitsn_RoadSegmentReferenceID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegmentReferenceID_purge(Gitsn_RoadSegmentReferenceID *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegmentReferenceID_del(Gitsn_RoadSegmentReferenceID *p);
static __inline__ void Gitsn_RoadSegmentReferenceID_delAndSetNull(void *ptr)
{
	Gitsn_RoadSegmentReferenceID **p = (Gitsn_RoadSegmentReferenceID **)ptr;
	if (p) { Gitsn_RoadSegmentReferenceID_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegmentReferenceID_dump(Gitsn_RoadSegmentReferenceID *p, int tab);
// Gitsn_RoadSegmentReferenceID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadLaneSetList
typedef struct Gitsn_RoadLaneSetList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_RoadLaneSetList *p);
	Dz1Error (*travel)(struct Gitsn_RoadLaneSetList *p, Dz1Error (*func)(void *ptr, Gitsn_GenericLane *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_RoadLaneSetList *p, Dz1Error (*func)(void *ptr, Gitsn_GenericLane *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_RoadLaneSetList *p, Dz1Error (*func)(void *ptr, Gitsn_GenericLane *entry), void *ptr);
	Gitsn_GenericLane **(*get_array)(struct Gitsn_RoadLaneSetList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_RoadLaneSetList *p, Gitsn_GenericLane *data);
	Gitsn_GenericLane *(*extract)(struct Gitsn_RoadLaneSetList *p, Gitsn_GenericLane *ptr);
	Gitsn_GenericLane *(*getHead)(struct Gitsn_RoadLaneSetList *p);
} Gitsn_RoadLaneSetList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadLaneSetList *Gitsn_RoadLaneSetList_new(Dz1Error *err);
static __inline__ Gitsn_RoadLaneSetList *Gitsn_RoadLaneSetList_gen(Dz1Error *err) { return Gitsn_RoadLaneSetList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadLaneSetList *Gitsn_RoadLaneSetList_clone(Gitsn_RoadLaneSetList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadLaneSetList_purge(Gitsn_RoadLaneSetList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadLaneSetList_del(Gitsn_RoadLaneSetList *p);
static __inline__ void Gitsn_RoadLaneSetList_delAndSetNull(void *ptr)
{
	Gitsn_RoadLaneSetList **p = (Gitsn_RoadLaneSetList **)ptr;
	if (p != NULL) { Gitsn_RoadLaneSetList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadLaneSetList_dump(Gitsn_RoadLaneSetList *p, int tab);

// Gitsn_RoadLaneSetList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSegment
typedef struct Gitsn_RoadSegment
{
	Gitsn_DescriptiveName			 name;
	Gitsn_RoadSegmentReferenceID	*id;
	Gitsn_MsgCount					 revision;
	Gitsn_Position3D				*refPoint;
	Gitsn_LaneWidth					 laneWidth;
	Gitsn_SpeedLimitList			*speedLimits;
	Gitsn_RoadLaneSetList			*roadLaneSet;
} Gitsn_RoadSegment;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSegment *Gitsn_RoadSegment_new(Gitsn_RoadSegmentReferenceID *id, 
																 Gitsn_MsgCount revision, 
																 Gitsn_Position3D *refPoint, 
																 Gitsn_RoadLaneSetList *roadLaneSet, Dz1Error *err);
static __inline__ Gitsn_RoadSegment *Gitsn_RoadSegment_gen(Dz1Error *err) { return Gitsn_RoadSegment_new(NULL, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RoadSegment_copy(Gitsn_RoadSegment *dst, Gitsn_RoadSegment *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSegment *Gitsn_RoadSegment_clone(Gitsn_RoadSegment *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegment_purge(Gitsn_RoadSegment *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegment_del(Gitsn_RoadSegment *p);
static __inline__ void Gitsn_RoadSegment_delAndSetNull(void *ptr)
{
	Gitsn_RoadSegment **p = (Gitsn_RoadSegment **)ptr;
	if (p) { Gitsn_RoadSegment_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegment_dump(Gitsn_RoadSegment *p, int tab);
// Gitsn_RoadSegment
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSegmentList
typedef struct Gitsn_RoadSegmentList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_RoadSegmentList *p);
	Dz1Error (*travel)(struct Gitsn_RoadSegmentList *p, Dz1Error (*func)(void *ptr, Gitsn_RoadSegment *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_RoadSegmentList *p, Dz1Error (*func)(void *ptr, Gitsn_RoadSegment *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_RoadSegmentList *p, Dz1Error (*func)(void *ptr, Gitsn_RoadSegment *entry), void *ptr);
	Gitsn_RoadSegment **(*get_array)(struct Gitsn_RoadSegmentList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_RoadSegmentList *p, Gitsn_RoadSegment *data);
	Gitsn_RoadSegment *(*extract)(struct Gitsn_RoadSegmentList *p, Gitsn_RoadSegment *ptr);
	Gitsn_RoadSegment *(*getHead)(struct Gitsn_RoadSegmentList *p);
} Gitsn_RoadSegmentList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSegmentList *Gitsn_RoadSegmentList_new(Dz1Error *err);
static __inline__ Gitsn_RoadSegmentList *Gitsn_RoadSegmentList_gen(Dz1Error *err) { return Gitsn_RoadSegmentList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSegmentList *Gitsn_RoadSegmentList_clone(Gitsn_RoadSegmentList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegmentList_purge(Gitsn_RoadSegmentList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegmentList_del(Gitsn_RoadSegmentList *p);
static __inline__ void Gitsn_RoadSegmentList_delAndSetNull(void *ptr)
{
	Gitsn_RoadSegmentList **p = (Gitsn_RoadSegmentList **)ptr;
	if (p != NULL) { Gitsn_RoadSegmentList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSegmentList_dump(Gitsn_RoadSegmentList *p, int tab);

// Gitsn_RoadSegmentList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DataParameters
typedef struct Gitsn_DataParameters
{
	Dz1Str		processMethod;
	Dz1Str		processAgency;
	Dz1Str		lastCheckedDate;
	Dz1Str		geoidUsed;
} Gitsn_DataParameters;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DataParameters *Gitsn_DataParameters_new(Dz1Error *err);
static __inline__ Gitsn_DataParameters *Gitsn_DataParameters_gen(Dz1Error *err) { return Gitsn_DataParameters_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_DataParameters_copy(Gitsn_DataParameters *dst, Gitsn_DataParameters *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DataParameters *Gitsn_DataParameters_clone(Gitsn_DataParameters *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DataParameters_purge(Gitsn_DataParameters *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DataParameters_del(Gitsn_DataParameters *p);
static __inline__ void Gitsn_DataParameters_delAndSetNull(void *ptr)
{
	Gitsn_DataParameters **p = (Gitsn_DataParameters **)ptr;
	if (p) { Gitsn_DataParameters_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DataParameters_dump(Gitsn_DataParameters *p, int tab);
// Gitsn_DataParameters
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionUserTypePresent
typedef enum Gitsn_RestrictionUserTypePresent
{
	Gitsn_RestrictionUserTypePresent_basicType,
	Gitsn_RestrictionUserTypePresent_max
} Gitsn_RestrictionUserTypePresent;

DZ1_CPPLINK str_t Gitsn_RestrictionUserTypePresentStrA(Gitsn_RestrictionUserTypePresent v);
DZ1_CPPLINK Gitsn_RestrictionUserTypePresent Gitsn_RestrictionUserTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_RestrictionUserTypePresentStrW(Gitsn_RestrictionUserTypePresent v);
DZ1_CPPLINK Gitsn_RestrictionUserTypePresent Gitsn_RestrictionUserTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_RestrictionUserTypePresentStr Gitsn_RestrictionUserTypePresentStrW
#define Gitsn_RestrictionUserTypePresentFromStr Gitsn_RestrictionUserTypePresentFromStrW
#else // UNICODE
#define Gitsn_RestrictionUserTypePresentStr Gitsn_RestrictionUserTypePresentStrA
#define Gitsn_RestrictionUserTypePresentFromStr Gitsn_RestrictionUserTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_RestrictionUserTypePresentStr Gitsn_RestrictionUserTypePresentStrA
#define Gitsn_RestrictionUserTypePresentFromStr Gitsn_RestrictionUserTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionUserTypePresent *Gitsn_RestrictionUserTypePresent_new(Gitsn_RestrictionUserTypePresent *src, Dz1Error *err);
static __inline__ Gitsn_RestrictionUserTypePresent *Gitsn_RestrictionUserTypePresent_gen(Dz1Error *err) { Gitsn_RestrictionUserTypePresent v = Gitsn_RestrictionUserTypePresent_max; return Gitsn_RestrictionUserTypePresent_new(&v, err); }
#define Gitsn_RestrictionUserTypePresent_clone             Gitsn_RestrictionUserTypePresent_new
static __inline__ void Gitsn_RestrictionUserTypePresent_del(Gitsn_RestrictionUserTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_RestrictionUserTypePresent_delAndSetNull(void *ptr)
{
	Gitsn_RestrictionUserTypePresent **p = (Gitsn_RestrictionUserTypePresent **)ptr;
	if (p != NULL) { Gitsn_RestrictionUserTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionUserTypePresent_dump(Gitsn_RestrictionUserTypePresent *v, int tab);
// Gitsn_RestrictionUserTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionUserType
typedef struct Gitsn_RestrictionUserType
{
	Gitsn_RestrictionUserTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_RestrictionAppliesTo		basicType;
	} x;
} Gitsn_RestrictionUserType;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionUserType *Gitsn_RestrictionUserType_new(Gitsn_RestrictionUserTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_RestrictionUserType *Gitsn_RestrictionUserType_gen(Dz1Error *err) { return Gitsn_RestrictionUserType_new(Gitsn_RestrictionUserTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_RestrictionUserType_copy(Gitsn_RestrictionUserType *dst, Gitsn_RestrictionUserType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionUserType *Gitsn_RestrictionUserType_clone(Gitsn_RestrictionUserType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionUserType_purge(Gitsn_RestrictionUserType *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionUserType_del(Gitsn_RestrictionUserType *p);
static __inline__ void Gitsn_RestrictionUserType_delAndSetNull(void *ptr)
{
	Gitsn_RestrictionUserType **p = (Gitsn_RestrictionUserType **)ptr;
	if (p != NULL) { Gitsn_RestrictionUserType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionUserType_dump(Gitsn_RestrictionUserType *p, int tab);
// Gitsn_RestrictionUserType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionUserTypeList
typedef struct Gitsn_RestrictionUserTypeList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_RestrictionUserTypeList *p);
	Dz1Error (*travel)(struct Gitsn_RestrictionUserTypeList *p, Dz1Error (*func)(void *ptr, Gitsn_RestrictionUserType *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_RestrictionUserTypeList *p, Dz1Error (*func)(void *ptr, Gitsn_RestrictionUserType *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_RestrictionUserTypeList *p, Dz1Error (*func)(void *ptr, Gitsn_RestrictionUserType *entry), void *ptr);
	Gitsn_RestrictionUserType **(*get_array)(struct Gitsn_RestrictionUserTypeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_RestrictionUserTypeList *p, Gitsn_RestrictionUserType *data);
	Gitsn_RestrictionUserType *(*extract)(struct Gitsn_RestrictionUserTypeList *p, Gitsn_RestrictionUserType *ptr);
	Gitsn_RestrictionUserType *(*getHead)(struct Gitsn_RestrictionUserTypeList *p);
} Gitsn_RestrictionUserTypeList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionUserTypeList *Gitsn_RestrictionUserTypeList_new(Dz1Error *err);
static __inline__ Gitsn_RestrictionUserTypeList *Gitsn_RestrictionUserTypeList_gen(Dz1Error *err) { return Gitsn_RestrictionUserTypeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionUserTypeList *Gitsn_RestrictionUserTypeList_clone(Gitsn_RestrictionUserTypeList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionUserTypeList_purge(Gitsn_RestrictionUserTypeList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionUserTypeList_del(Gitsn_RestrictionUserTypeList *p);
static __inline__ void Gitsn_RestrictionUserTypeList_delAndSetNull(void *ptr)
{
	Gitsn_RestrictionUserTypeList **p = (Gitsn_RestrictionUserTypeList **)ptr;
	if (p != NULL) { Gitsn_RestrictionUserTypeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionUserTypeList_dump(Gitsn_RestrictionUserTypeList *p, int tab);

// Gitsn_RestrictionUserTypeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionClassAssignment
typedef struct Gitsn_RestrictionClassAssignment
{
	Gitsn_RestrictionClassID			 id;
	Gitsn_RestrictionUserTypeList		*users;
} Gitsn_RestrictionClassAssignment;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionClassAssignment *Gitsn_RestrictionClassAssignment_new(Gitsn_RestrictionClassID id, 
																							   Gitsn_RestrictionUserTypeList *users, Dz1Error *err);
static __inline__ Gitsn_RestrictionClassAssignment *Gitsn_RestrictionClassAssignment_gen(Dz1Error *err) { return Gitsn_RestrictionClassAssignment_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RestrictionClassAssignment_copy(Gitsn_RestrictionClassAssignment *dst, Gitsn_RestrictionClassAssignment *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionClassAssignment *Gitsn_RestrictionClassAssignment_clone(Gitsn_RestrictionClassAssignment *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionClassAssignment_purge(Gitsn_RestrictionClassAssignment *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionClassAssignment_del(Gitsn_RestrictionClassAssignment *p);
static __inline__ void Gitsn_RestrictionClassAssignment_delAndSetNull(void *ptr)
{
	Gitsn_RestrictionClassAssignment **p = (Gitsn_RestrictionClassAssignment **)ptr;
	if (p) { Gitsn_RestrictionClassAssignment_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionClassAssignment_dump(Gitsn_RestrictionClassAssignment *p, int tab);
// Gitsn_RestrictionClassAssignment
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionClassList
typedef struct Gitsn_RestrictionClassList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_RestrictionClassList *p);
	Dz1Error (*travel)(struct Gitsn_RestrictionClassList *p, Dz1Error (*func)(void *ptr, Gitsn_RestrictionClassAssignment *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_RestrictionClassList *p, Dz1Error (*func)(void *ptr, Gitsn_RestrictionClassAssignment *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_RestrictionClassList *p, Dz1Error (*func)(void *ptr, Gitsn_RestrictionClassAssignment *entry), void *ptr);
	Gitsn_RestrictionClassAssignment **(*get_array)(struct Gitsn_RestrictionClassList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_RestrictionClassList *p, Gitsn_RestrictionClassAssignment *data);
	Gitsn_RestrictionClassAssignment *(*extract)(struct Gitsn_RestrictionClassList *p, Gitsn_RestrictionClassAssignment *ptr);
	Gitsn_RestrictionClassAssignment *(*getHead)(struct Gitsn_RestrictionClassList *p);
} Gitsn_RestrictionClassList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionClassList *Gitsn_RestrictionClassList_new(Dz1Error *err);
static __inline__ Gitsn_RestrictionClassList *Gitsn_RestrictionClassList_gen(Dz1Error *err) { return Gitsn_RestrictionClassList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RestrictionClassList *Gitsn_RestrictionClassList_clone(Gitsn_RestrictionClassList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionClassList_purge(Gitsn_RestrictionClassList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionClassList_del(Gitsn_RestrictionClassList *p);
static __inline__ void Gitsn_RestrictionClassList_delAndSetNull(void *ptr)
{
	Gitsn_RestrictionClassList **p = (Gitsn_RestrictionClassList **)ptr;
	if (p != NULL) { Gitsn_RestrictionClassList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RestrictionClassList_dump(Gitsn_RestrictionClassList *p, int tab);

// Gitsn_RestrictionClassList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EnabledLaneList
typedef struct Gitsn_EnabledLaneList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_EnabledLaneList *p);
	Dz1Error (*travel)(struct Gitsn_EnabledLaneList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneID *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_EnabledLaneList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneID *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_EnabledLaneList *p, Dz1Error (*func)(void *ptr, Gitsn_LaneID *entry), void *ptr);
	Gitsn_LaneID *(*get_array)(struct Gitsn_EnabledLaneList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_EnabledLaneList *p, Gitsn_LaneID data);
	Gitsn_LaneID *(*extract)(struct Gitsn_EnabledLaneList *p, Gitsn_LaneID *ptr);
	Gitsn_LaneID *(*getHead)(struct Gitsn_EnabledLaneList *p);
	int (*cmp)(Gitsn_LaneID *a, Gitsn_LaneID *b);
} Gitsn_EnabledLaneList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_EnabledLaneList *Gitsn_EnabledLaneList_new(Dz1Error *err);
static __inline__ Gitsn_EnabledLaneList *Gitsn_EnabledLaneList_gen(Dz1Error *err) { return Gitsn_EnabledLaneList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_EnabledLaneList *Gitsn_EnabledLaneList_clone(Gitsn_EnabledLaneList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EnabledLaneList_purge(Gitsn_EnabledLaneList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EnabledLaneList_del(Gitsn_EnabledLaneList *p);
static __inline__ void Gitsn_EnabledLaneList_delAndSetNull(void *ptr)
{
	Gitsn_EnabledLaneList **p = (Gitsn_EnabledLaneList **)ptr;
	if (p != NULL) { Gitsn_EnabledLaneList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EnabledLaneListA_dump(Gitsn_EnabledLaneList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EnabledLaneListA_fdump(FILE *fp, Gitsn_EnabledLaneList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EnabledLaneListW_dump(Gitsn_EnabledLaneList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EnabledLaneListW_fdump(FILE *fp, Gitsn_EnabledLaneList *p, int tab);
#ifdef UNICODE
#define Gitsn_EnabledLaneList_dump Gitsn_EnabledLaneListW_dump
#define Gitsn_EnabledLaneList_fdump Gitsn_EnabledLaneListW_fdump
#else //  UNICODE
#define Gitsn_EnabledLaneList_dump Gitsn_EnabledLaneListA_dump
#define Gitsn_EnabledLaneList_fdump Gitsn_EnabledLaneListA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_EnabledLaneListX_dump(Gitsn_EnabledLaneList *p, int tab) { DZ1_DUMP(Gitsn_EnabledLaneList, p, tab); }
static __inline__ void Gitsn_EnabledLaneListX_fdump(FILE *fp, Gitsn_EnabledLaneList *p, int tab) { DZ1_FDUMP(fp, Gitsn_EnabledLaneList, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_EnabledLaneList_dump Gitsn_EnabledLaneListA_dump
#define Gitsn_EnabledLaneListX_dump Gitsn_EnabledLaneListA_dump
#define Gitsn_EnabledLaneList_fdump Gitsn_EnabledLaneListA_fdump
#define Gitsn_EnabledLaneListX_fdump Gitsn_EnabledLaneListA_fdump
#endif // UNIX_SYSTEM

// Gitsn_EnabledLaneList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AdvisorySpeed
typedef struct Gitsn_AdvisorySpeed
{
	Gitsn_AdvisorySpeedType		type;
	Gitsn_SpeedAdvice			speed;
	Gitsn_SpeedConfidence		confidence;
	Gitsn_ZoneLength			distance;
	Gitsn_RestrictionClassID	class;
} Gitsn_AdvisorySpeed;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AdvisorySpeed *Gitsn_AdvisorySpeed_new(Gitsn_AdvisorySpeedType type, Dz1Error *err);
static __inline__ Gitsn_AdvisorySpeed *Gitsn_AdvisorySpeed_gen(Dz1Error *err) { return Gitsn_AdvisorySpeed_new(Gitsn_AdvisorySpeedType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_AdvisorySpeed_copy(Gitsn_AdvisorySpeed *dst, Gitsn_AdvisorySpeed *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AdvisorySpeed *Gitsn_AdvisorySpeed_clone(Gitsn_AdvisorySpeed *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AdvisorySpeed_purge(Gitsn_AdvisorySpeed *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AdvisorySpeed_del(Gitsn_AdvisorySpeed *p);
static __inline__ void Gitsn_AdvisorySpeed_delAndSetNull(void *ptr)
{
	Gitsn_AdvisorySpeed **p = (Gitsn_AdvisorySpeed **)ptr;
	if (p) { Gitsn_AdvisorySpeed_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AdvisorySpeed_dump(Gitsn_AdvisorySpeed *p, int tab);
// Gitsn_AdvisorySpeed
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AdvisorySpeedList
typedef struct Gitsn_AdvisorySpeedList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_AdvisorySpeedList *p);
	Dz1Error (*travel)(struct Gitsn_AdvisorySpeedList *p, Dz1Error (*func)(void *ptr, Gitsn_AdvisorySpeed *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_AdvisorySpeedList *p, Dz1Error (*func)(void *ptr, Gitsn_AdvisorySpeed *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_AdvisorySpeedList *p, Dz1Error (*func)(void *ptr, Gitsn_AdvisorySpeed *entry), void *ptr);
	Gitsn_AdvisorySpeed **(*get_array)(struct Gitsn_AdvisorySpeedList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_AdvisorySpeedList *p, Gitsn_AdvisorySpeed *data);
	Gitsn_AdvisorySpeed *(*extract)(struct Gitsn_AdvisorySpeedList *p, Gitsn_AdvisorySpeed *ptr);
	Gitsn_AdvisorySpeed *(*getHead)(struct Gitsn_AdvisorySpeedList *p);
} Gitsn_AdvisorySpeedList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AdvisorySpeedList *Gitsn_AdvisorySpeedList_new(Dz1Error *err);
static __inline__ Gitsn_AdvisorySpeedList *Gitsn_AdvisorySpeedList_gen(Dz1Error *err) { return Gitsn_AdvisorySpeedList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AdvisorySpeedList *Gitsn_AdvisorySpeedList_clone(Gitsn_AdvisorySpeedList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AdvisorySpeedList_purge(Gitsn_AdvisorySpeedList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AdvisorySpeedList_del(Gitsn_AdvisorySpeedList *p);
static __inline__ void Gitsn_AdvisorySpeedList_delAndSetNull(void *ptr)
{
	Gitsn_AdvisorySpeedList **p = (Gitsn_AdvisorySpeedList **)ptr;
	if (p != NULL) { Gitsn_AdvisorySpeedList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AdvisorySpeedList_dump(Gitsn_AdvisorySpeedList *p, int tab);

// Gitsn_AdvisorySpeedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeChangeDetails
typedef struct Gitsn_TimeChangeDetails
{
	Gitsn_TimeMark					startTime;
	Gitsn_TimeMark					minEndTime;
	Gitsn_TimeMark					maxEndTime;
	Gitsn_TimeMark					likelyTime;
	Gitsn_TimeIntervalConfidence	confidence;
	Gitsn_TimeMark					nextTime;
} Gitsn_TimeChangeDetails;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TimeChangeDetails *Gitsn_TimeChangeDetails_new(Dz1Error *err);
static __inline__ Gitsn_TimeChangeDetails *Gitsn_TimeChangeDetails_gen(Dz1Error *err) { return Gitsn_TimeChangeDetails_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_TimeChangeDetails_copy(Gitsn_TimeChangeDetails *dst, Gitsn_TimeChangeDetails *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TimeChangeDetails *Gitsn_TimeChangeDetails_clone(Gitsn_TimeChangeDetails *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TimeChangeDetails_purge(Gitsn_TimeChangeDetails *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TimeChangeDetails_del(Gitsn_TimeChangeDetails *p);
static __inline__ void Gitsn_TimeChangeDetails_delAndSetNull(void *ptr)
{
	Gitsn_TimeChangeDetails **p = (Gitsn_TimeChangeDetails **)ptr;
	if (p) { Gitsn_TimeChangeDetails_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TimeChangeDetails_dump(Gitsn_TimeChangeDetails *p, int tab);
// Gitsn_TimeChangeDetails
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementEvent
typedef struct Gitsn_MovementEvent
{
	Gitsn_MovementPhaseState	 eventState;
	Gitsn_TimeChangeDetails		*timing;
	Gitsn_AdvisorySpeedList		*speeds;
} Gitsn_MovementEvent;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementEvent *Gitsn_MovementEvent_new(Gitsn_MovementPhaseState eventState, Dz1Error *err);
static __inline__ Gitsn_MovementEvent *Gitsn_MovementEvent_gen(Dz1Error *err) { return Gitsn_MovementEvent_new(Gitsn_MovementPhaseState_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_MovementEvent_copy(Gitsn_MovementEvent *dst, Gitsn_MovementEvent *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementEvent *Gitsn_MovementEvent_clone(Gitsn_MovementEvent *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementEvent_purge(Gitsn_MovementEvent *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementEvent_del(Gitsn_MovementEvent *p);
static __inline__ void Gitsn_MovementEvent_delAndSetNull(void *ptr)
{
	Gitsn_MovementEvent **p = (Gitsn_MovementEvent **)ptr;
	if (p) { Gitsn_MovementEvent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementEvent_dump(Gitsn_MovementEvent *p, int tab);
// Gitsn_MovementEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementEventList
typedef struct Gitsn_MovementEventList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_MovementEventList *p);
	Dz1Error (*travel)(struct Gitsn_MovementEventList *p, Dz1Error (*func)(void *ptr, Gitsn_MovementEvent *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_MovementEventList *p, Dz1Error (*func)(void *ptr, Gitsn_MovementEvent *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_MovementEventList *p, Dz1Error (*func)(void *ptr, Gitsn_MovementEvent *entry), void *ptr);
	Gitsn_MovementEvent **(*get_array)(struct Gitsn_MovementEventList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_MovementEventList *p, Gitsn_MovementEvent *data);
	Gitsn_MovementEvent *(*extract)(struct Gitsn_MovementEventList *p, Gitsn_MovementEvent *ptr);
	Gitsn_MovementEvent *(*getHead)(struct Gitsn_MovementEventList *p);
} Gitsn_MovementEventList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementEventList *Gitsn_MovementEventList_new(Dz1Error *err);
static __inline__ Gitsn_MovementEventList *Gitsn_MovementEventList_gen(Dz1Error *err) { return Gitsn_MovementEventList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementEventList *Gitsn_MovementEventList_clone(Gitsn_MovementEventList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementEventList_purge(Gitsn_MovementEventList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementEventList_del(Gitsn_MovementEventList *p);
static __inline__ void Gitsn_MovementEventList_delAndSetNull(void *ptr)
{
	Gitsn_MovementEventList **p = (Gitsn_MovementEventList **)ptr;
	if (p != NULL) { Gitsn_MovementEventList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementEventList_dump(Gitsn_MovementEventList *p, int tab);

// Gitsn_MovementEventList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConnectionManeuverAssist
typedef struct Gitsn_ConnectionManeuverAssist
{
	Gitsn_LaneConnectionID				connectionID;
	Gitsn_ZoneLength					queueLength;
	Gitsn_ZoneLength					availableStorageLength;
	Gitsn_WaitOnStopline				waitOnStop;
	Gitsn_PedestrianBicycleDetect		pedBicycleDetect;
} Gitsn_ConnectionManeuverAssist;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConnectionManeuverAssist *Gitsn_ConnectionManeuverAssist_new(Gitsn_LaneConnectionID connectionID, Dz1Error *err);
static __inline__ Gitsn_ConnectionManeuverAssist *Gitsn_ConnectionManeuverAssist_gen(Dz1Error *err) { return Gitsn_ConnectionManeuverAssist_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ConnectionManeuverAssist_copy(Gitsn_ConnectionManeuverAssist *dst, Gitsn_ConnectionManeuverAssist *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConnectionManeuverAssist *Gitsn_ConnectionManeuverAssist_clone(Gitsn_ConnectionManeuverAssist *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectionManeuverAssist_purge(Gitsn_ConnectionManeuverAssist *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectionManeuverAssist_del(Gitsn_ConnectionManeuverAssist *p);
static __inline__ void Gitsn_ConnectionManeuverAssist_delAndSetNull(void *ptr)
{
	Gitsn_ConnectionManeuverAssist **p = (Gitsn_ConnectionManeuverAssist **)ptr;
	if (p) { Gitsn_ConnectionManeuverAssist_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConnectionManeuverAssist_dump(Gitsn_ConnectionManeuverAssist *p, int tab);
// Gitsn_ConnectionManeuverAssist
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ManeuverAssistList
typedef struct Gitsn_ManeuverAssistList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_ManeuverAssistList *p);
	Dz1Error (*travel)(struct Gitsn_ManeuverAssistList *p, Dz1Error (*func)(void *ptr, Gitsn_ConnectionManeuverAssist *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_ManeuverAssistList *p, Dz1Error (*func)(void *ptr, Gitsn_ConnectionManeuverAssist *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_ManeuverAssistList *p, Dz1Error (*func)(void *ptr, Gitsn_ConnectionManeuverAssist *entry), void *ptr);
	Gitsn_ConnectionManeuverAssist **(*get_array)(struct Gitsn_ManeuverAssistList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_ManeuverAssistList *p, Gitsn_ConnectionManeuverAssist *data);
	Gitsn_ConnectionManeuverAssist *(*extract)(struct Gitsn_ManeuverAssistList *p, Gitsn_ConnectionManeuverAssist *ptr);
	Gitsn_ConnectionManeuverAssist *(*getHead)(struct Gitsn_ManeuverAssistList *p);
} Gitsn_ManeuverAssistList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ManeuverAssistList *Gitsn_ManeuverAssistList_new(Dz1Error *err);
static __inline__ Gitsn_ManeuverAssistList *Gitsn_ManeuverAssistList_gen(Dz1Error *err) { return Gitsn_ManeuverAssistList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ManeuverAssistList *Gitsn_ManeuverAssistList_clone(Gitsn_ManeuverAssistList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ManeuverAssistList_purge(Gitsn_ManeuverAssistList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ManeuverAssistList_del(Gitsn_ManeuverAssistList *p);
static __inline__ void Gitsn_ManeuverAssistList_delAndSetNull(void *ptr)
{
	Gitsn_ManeuverAssistList **p = (Gitsn_ManeuverAssistList **)ptr;
	if (p != NULL) { Gitsn_ManeuverAssistList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ManeuverAssistList_dump(Gitsn_ManeuverAssistList *p, int tab);

// Gitsn_ManeuverAssistList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementState
typedef struct Gitsn_MovementState
{
	Gitsn_DescriptiveName		 movementName;
	Gitsn_SignalGroupID			 signalGroup;
	Gitsn_MovementEventList		*state_time_speed;
	Gitsn_ManeuverAssistList	*maneuverAssistList;
} Gitsn_MovementState;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementState *Gitsn_MovementState_new(Gitsn_SignalGroupID signalGroup, 
																	 Gitsn_MovementEventList *state_time_speed, Dz1Error *err);
static __inline__ Gitsn_MovementState *Gitsn_MovementState_gen(Dz1Error *err) { return Gitsn_MovementState_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_MovementState_copy(Gitsn_MovementState *dst, Gitsn_MovementState *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementState *Gitsn_MovementState_clone(Gitsn_MovementState *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementState_purge(Gitsn_MovementState *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementState_del(Gitsn_MovementState *p);
static __inline__ void Gitsn_MovementState_delAndSetNull(void *ptr)
{
	Gitsn_MovementState **p = (Gitsn_MovementState **)ptr;
	if (p) { Gitsn_MovementState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementState_dump(Gitsn_MovementState *p, int tab);
// Gitsn_MovementState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementList
typedef struct Gitsn_MovementList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_MovementList *p);
	Dz1Error (*travel)(struct Gitsn_MovementList *p, Dz1Error (*func)(void *ptr, Gitsn_MovementState *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_MovementList *p, Dz1Error (*func)(void *ptr, Gitsn_MovementState *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_MovementList *p, Dz1Error (*func)(void *ptr, Gitsn_MovementState *entry), void *ptr);
	Gitsn_MovementState **(*get_array)(struct Gitsn_MovementList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_MovementList *p, Gitsn_MovementState *data);
	Gitsn_MovementState *(*extract)(struct Gitsn_MovementList *p, Gitsn_MovementState *ptr);
	Gitsn_MovementState *(*getHead)(struct Gitsn_MovementList *p);
} Gitsn_MovementList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementList *Gitsn_MovementList_new(Dz1Error *err);
static __inline__ Gitsn_MovementList *Gitsn_MovementList_gen(Dz1Error *err) { return Gitsn_MovementList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovementList *Gitsn_MovementList_clone(Gitsn_MovementList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementList_purge(Gitsn_MovementList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementList_del(Gitsn_MovementList *p);
static __inline__ void Gitsn_MovementList_delAndSetNull(void *ptr)
{
	Gitsn_MovementList **p = (Gitsn_MovementList **)ptr;
	if (p != NULL) { Gitsn_MovementList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovementList_dump(Gitsn_MovementList *p, int tab);

// Gitsn_MovementList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionState
typedef struct Gitsn_IntersectionState
{
	Gitsn_DescriptiveName				 name;
	Gitsn_IntersectionReferenceID		*id;
	Gitsn_MsgCount						 revision;
	Gitsn_IntersectionStatusObject		*status;
	Gitsn_MinuteOfTheYear				 moy;
	Gitsn_DSecond						 timeStamp;
	Gitsn_EnabledLaneList				*enabledLanes;
	Gitsn_MovementList					*states;
	Gitsn_ManeuverAssistList			*maneuverAssistList;
} Gitsn_IntersectionState;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionState *Gitsn_IntersectionState_new(Gitsn_IntersectionReferenceID *id, 
																			 Gitsn_MsgCount revision, 
																			 Gitsn_IntersectionStatusObject *status, Dz1Error *err);
static __inline__ Gitsn_IntersectionState *Gitsn_IntersectionState_gen(Dz1Error *err) { return Gitsn_IntersectionState_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_IntersectionState_copy(Gitsn_IntersectionState *dst, Gitsn_IntersectionState *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionState *Gitsn_IntersectionState_clone(Gitsn_IntersectionState *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionState_purge(Gitsn_IntersectionState *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionState_del(Gitsn_IntersectionState *p);
static __inline__ void Gitsn_IntersectionState_delAndSetNull(void *ptr)
{
	Gitsn_IntersectionState **p = (Gitsn_IntersectionState **)ptr;
	if (p) { Gitsn_IntersectionState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionState_dump(Gitsn_IntersectionState *p, int tab);
// Gitsn_IntersectionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionStateList
typedef struct Gitsn_IntersectionStateList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_IntersectionStateList *p);
	Dz1Error (*travel)(struct Gitsn_IntersectionStateList *p, Dz1Error (*func)(void *ptr, Gitsn_IntersectionState *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_IntersectionStateList *p, Dz1Error (*func)(void *ptr, Gitsn_IntersectionState *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_IntersectionStateList *p, Dz1Error (*func)(void *ptr, Gitsn_IntersectionState *entry), void *ptr);
	Gitsn_IntersectionState **(*get_array)(struct Gitsn_IntersectionStateList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_IntersectionStateList *p, Gitsn_IntersectionState *data);
	Gitsn_IntersectionState *(*extract)(struct Gitsn_IntersectionStateList *p, Gitsn_IntersectionState *ptr);
	Gitsn_IntersectionState *(*getHead)(struct Gitsn_IntersectionStateList *p);
} Gitsn_IntersectionStateList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionStateList *Gitsn_IntersectionStateList_new(Dz1Error *err);
static __inline__ Gitsn_IntersectionStateList *Gitsn_IntersectionStateList_gen(Dz1Error *err) { return Gitsn_IntersectionStateList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionStateList *Gitsn_IntersectionStateList_clone(Gitsn_IntersectionStateList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionStateList_purge(Gitsn_IntersectionStateList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionStateList_del(Gitsn_IntersectionStateList *p);
static __inline__ void Gitsn_IntersectionStateList_delAndSetNull(void *ptr)
{
	Gitsn_IntersectionStateList **p = (Gitsn_IntersectionStateList **)ptr;
	if (p != NULL) { Gitsn_IntersectionStateList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionStateList_dump(Gitsn_IntersectionStateList *p, int tab);

// Gitsn_IntersectionStateList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleIDPresent
typedef enum Gitsn_VehicleIDPresent
{
	Gitsn_VehicleIDPresent_entityID,
	Gitsn_VehicleIDPresent_stationID,
	Gitsn_VehicleIDPresent_max
} Gitsn_VehicleIDPresent;

DZ1_CPPLINK str_t Gitsn_VehicleIDPresentStrA(Gitsn_VehicleIDPresent v);
DZ1_CPPLINK Gitsn_VehicleIDPresent Gitsn_VehicleIDPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_VehicleIDPresentStrW(Gitsn_VehicleIDPresent v);
DZ1_CPPLINK Gitsn_VehicleIDPresent Gitsn_VehicleIDPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_VehicleIDPresentStr Gitsn_VehicleIDPresentStrW
#define Gitsn_VehicleIDPresentFromStr Gitsn_VehicleIDPresentFromStrW
#else // UNICODE
#define Gitsn_VehicleIDPresentStr Gitsn_VehicleIDPresentStrA
#define Gitsn_VehicleIDPresentFromStr Gitsn_VehicleIDPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_VehicleIDPresentStr Gitsn_VehicleIDPresentStrA
#define Gitsn_VehicleIDPresentFromStr Gitsn_VehicleIDPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleIDPresent *Gitsn_VehicleIDPresent_new(Gitsn_VehicleIDPresent *src, Dz1Error *err);
static __inline__ Gitsn_VehicleIDPresent *Gitsn_VehicleIDPresent_gen(Dz1Error *err) { Gitsn_VehicleIDPresent v = Gitsn_VehicleIDPresent_max; return Gitsn_VehicleIDPresent_new(&v, err); }
#define Gitsn_VehicleIDPresent_clone             Gitsn_VehicleIDPresent_new
static __inline__ void Gitsn_VehicleIDPresent_del(Gitsn_VehicleIDPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_VehicleIDPresent_delAndSetNull(void *ptr)
{
	Gitsn_VehicleIDPresent **p = (Gitsn_VehicleIDPresent **)ptr;
	if (p != NULL) { Gitsn_VehicleIDPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleIDPresent_dump(Gitsn_VehicleIDPresent *v, int tab);
// Gitsn_VehicleIDPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleID
typedef struct Gitsn_VehicleID
{
	Gitsn_VehicleIDPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_TemporaryID		entityID;
		Gitsn_StationID			stationID;
	} x;
} Gitsn_VehicleID;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleID *Gitsn_VehicleID_new(Gitsn_VehicleIDPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_VehicleID *Gitsn_VehicleID_gen(Dz1Error *err) { return Gitsn_VehicleID_new(Gitsn_VehicleIDPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_VehicleID_copy(Gitsn_VehicleID *dst, Gitsn_VehicleID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleID *Gitsn_VehicleID_clone(Gitsn_VehicleID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleID_purge(Gitsn_VehicleID *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleID_del(Gitsn_VehicleID *p);
static __inline__ void Gitsn_VehicleID_delAndSetNull(void *ptr)
{
	Gitsn_VehicleID **p = (Gitsn_VehicleID **)ptr;
	if (p != NULL) { Gitsn_VehicleID_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleID_dump(Gitsn_VehicleID *p, int tab);
// Gitsn_VehicleID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleIdent_vehicleClassPresent
typedef enum Gitsn_VehicleIdent_vehicleClassPresent
{
	Gitsn_VehicleIdent_vehicleClassPresent_vGroup,
	Gitsn_VehicleIdent_vehicleClassPresent_rGroup,
	Gitsn_VehicleIdent_vehicleClassPresent_rEquip,
	Gitsn_VehicleIdent_vehicleClassPresent_max
} Gitsn_VehicleIdent_vehicleClassPresent;

DZ1_CPPLINK str_t Gitsn_VehicleIdent_vehicleClassPresentStrA(Gitsn_VehicleIdent_vehicleClassPresent v);
DZ1_CPPLINK Gitsn_VehicleIdent_vehicleClassPresent Gitsn_VehicleIdent_vehicleClassPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_VehicleIdent_vehicleClassPresentStrW(Gitsn_VehicleIdent_vehicleClassPresent v);
DZ1_CPPLINK Gitsn_VehicleIdent_vehicleClassPresent Gitsn_VehicleIdent_vehicleClassPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_VehicleIdent_vehicleClassPresentStr Gitsn_VehicleIdent_vehicleClassPresentStrW
#define Gitsn_VehicleIdent_vehicleClassPresentFromStr Gitsn_VehicleIdent_vehicleClassPresentFromStrW
#else // UNICODE
#define Gitsn_VehicleIdent_vehicleClassPresentStr Gitsn_VehicleIdent_vehicleClassPresentStrA
#define Gitsn_VehicleIdent_vehicleClassPresentFromStr Gitsn_VehicleIdent_vehicleClassPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_VehicleIdent_vehicleClassPresentStr Gitsn_VehicleIdent_vehicleClassPresentStrA
#define Gitsn_VehicleIdent_vehicleClassPresentFromStr Gitsn_VehicleIdent_vehicleClassPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleIdent_vehicleClassPresent *Gitsn_VehicleIdent_vehicleClassPresent_new(Gitsn_VehicleIdent_vehicleClassPresent *src, Dz1Error *err);
static __inline__ Gitsn_VehicleIdent_vehicleClassPresent *Gitsn_VehicleIdent_vehicleClassPresent_gen(Dz1Error *err) { Gitsn_VehicleIdent_vehicleClassPresent v = Gitsn_VehicleIdent_vehicleClassPresent_max; return Gitsn_VehicleIdent_vehicleClassPresent_new(&v, err); }
#define Gitsn_VehicleIdent_vehicleClassPresent_clone             Gitsn_VehicleIdent_vehicleClassPresent_new
static __inline__ void Gitsn_VehicleIdent_vehicleClassPresent_del(Gitsn_VehicleIdent_vehicleClassPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_VehicleIdent_vehicleClassPresent_delAndSetNull(void *ptr)
{
	Gitsn_VehicleIdent_vehicleClassPresent **p = (Gitsn_VehicleIdent_vehicleClassPresent **)ptr;
	if (p != NULL) { Gitsn_VehicleIdent_vehicleClassPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleIdent_vehicleClassPresent_dump(Gitsn_VehicleIdent_vehicleClassPresent *v, int tab);
// Gitsn_VehicleIdent_vehicleClassPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleIdent_vehicleClass
typedef struct Gitsn_VehicleIdent_vehicleClass
{
	Gitsn_VehicleIdent_vehicleClassPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_VehicleGroupAffected			vGroup;
		Gitsn_ResponderGroupAffected		rGroup;
		Gitsn_IncidentResponseEquipment		rEquip;
	} x;
} Gitsn_VehicleIdent_vehicleClass;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleIdent_vehicleClass *Gitsn_VehicleIdent_vehicleClass_new(Gitsn_VehicleIdent_vehicleClassPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_VehicleIdent_vehicleClass *Gitsn_VehicleIdent_vehicleClass_gen(Dz1Error *err) { return Gitsn_VehicleIdent_vehicleClass_new(Gitsn_VehicleIdent_vehicleClassPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_VehicleIdent_vehicleClass_copy(Gitsn_VehicleIdent_vehicleClass *dst, Gitsn_VehicleIdent_vehicleClass *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleIdent_vehicleClass *Gitsn_VehicleIdent_vehicleClass_clone(Gitsn_VehicleIdent_vehicleClass *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleIdent_vehicleClass_purge(Gitsn_VehicleIdent_vehicleClass *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleIdent_vehicleClass_del(Gitsn_VehicleIdent_vehicleClass *p);
static __inline__ void Gitsn_VehicleIdent_vehicleClass_delAndSetNull(void *ptr)
{
	Gitsn_VehicleIdent_vehicleClass **p = (Gitsn_VehicleIdent_vehicleClass **)ptr;
	if (p != NULL) { Gitsn_VehicleIdent_vehicleClass_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleIdent_vehicleClass_dump(Gitsn_VehicleIdent_vehicleClass *p, int tab);
// Gitsn_VehicleIdent_vehicleClass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleIdent
typedef struct Gitsn_VehicleIdent
{
	Gitsn_DescriptiveName				 name;
	Gitsn_VINstring						 vin;
	Gitsn_IA5String						 ownerCode;
	Gitsn_VehicleID						*id;
	Gitsn_VehicleType					 vehicleType;
	Gitsn_VehicleIdent_vehicleClass		*vehicleClass;
} Gitsn_VehicleIdent;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleIdent *Gitsn_VehicleIdent_new(Dz1Error *err);
static __inline__ Gitsn_VehicleIdent *Gitsn_VehicleIdent_gen(Dz1Error *err) { return Gitsn_VehicleIdent_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleIdent_copy(Gitsn_VehicleIdent *dst, Gitsn_VehicleIdent *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleIdent *Gitsn_VehicleIdent_clone(Gitsn_VehicleIdent *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleIdent_purge(Gitsn_VehicleIdent *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleIdent_del(Gitsn_VehicleIdent *p);
static __inline__ void Gitsn_VehicleIdent_delAndSetNull(void *ptr)
{
	Gitsn_VehicleIdent **p = (Gitsn_VehicleIdent **)ptr;
	if (p) { Gitsn_VehicleIdent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleIdent_dump(Gitsn_VehicleIdent *p, int tab);
// Gitsn_VehicleIdent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DDateTime
typedef struct Gitsn_DDateTime
{
	Gitsn_DYear			year;
	Gitsn_DMonth		month;
	Gitsn_DDay			day;
	Gitsn_DHour			hour;
	Gitsn_DMinute		minute;
	Gitsn_DSecond		second;
	Gitsn_DOffset		offset;
} Gitsn_DDateTime;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DDateTime *Gitsn_DDateTime_new(Dz1Error *err);
static __inline__ Gitsn_DDateTime *Gitsn_DDateTime_gen(Dz1Error *err) { return Gitsn_DDateTime_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_DDateTime_copy(Gitsn_DDateTime *dst, Gitsn_DDateTime *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DDateTime *Gitsn_DDateTime_clone(Gitsn_DDateTime *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DDateTime_purge(Gitsn_DDateTime *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DDateTime_del(Gitsn_DDateTime *p);
static __inline__ void Gitsn_DDateTime_delAndSetNull(void *ptr)
{
	Gitsn_DDateTime **p = (Gitsn_DDateTime **)ptr;
	if (p) { Gitsn_DDateTime_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DDateTime_dump(Gitsn_DDateTime *p, int tab);
// Gitsn_DDateTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TransmissionAndSpeed
typedef struct Gitsn_TransmissionAndSpeed
{
	Gitsn_TransmissionState		transmission;
	Gitsn_Velocity				speed;
} Gitsn_TransmissionAndSpeed;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TransmissionAndSpeed *Gitsn_TransmissionAndSpeed_new(Gitsn_TransmissionState transmission, 
																				   Gitsn_Velocity speed, Dz1Error *err);
static __inline__ Gitsn_TransmissionAndSpeed *Gitsn_TransmissionAndSpeed_gen(Dz1Error *err) { return Gitsn_TransmissionAndSpeed_new(Gitsn_TransmissionState_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_TransmissionAndSpeed_copy(Gitsn_TransmissionAndSpeed *dst, Gitsn_TransmissionAndSpeed *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TransmissionAndSpeed *Gitsn_TransmissionAndSpeed_clone(Gitsn_TransmissionAndSpeed *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TransmissionAndSpeed_purge(Gitsn_TransmissionAndSpeed *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TransmissionAndSpeed_del(Gitsn_TransmissionAndSpeed *p);
static __inline__ void Gitsn_TransmissionAndSpeed_delAndSetNull(void *ptr)
{
	Gitsn_TransmissionAndSpeed **p = (Gitsn_TransmissionAndSpeed **)ptr;
	if (p) { Gitsn_TransmissionAndSpeed_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TransmissionAndSpeed_dump(Gitsn_TransmissionAndSpeed *p, int tab);
// Gitsn_TransmissionAndSpeed
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PositionConfidenceSet
typedef struct Gitsn_PositionConfidenceSet
{
	Gitsn_PositionConfidence		pos;
	Gitsn_ElevationConfidence		elevation;
} Gitsn_PositionConfidenceSet;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PositionConfidenceSet *Gitsn_PositionConfidenceSet_new(Gitsn_PositionConfidence pos, 
																					 Gitsn_ElevationConfidence elevation, Dz1Error *err);
static __inline__ Gitsn_PositionConfidenceSet *Gitsn_PositionConfidenceSet_gen(Dz1Error *err) { return Gitsn_PositionConfidenceSet_new(Gitsn_PositionConfidence_max, Gitsn_ElevationConfidence_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_PositionConfidenceSet_copy(Gitsn_PositionConfidenceSet *dst, Gitsn_PositionConfidenceSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PositionConfidenceSet *Gitsn_PositionConfidenceSet_clone(Gitsn_PositionConfidenceSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionConfidenceSet_purge(Gitsn_PositionConfidenceSet *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionConfidenceSet_del(Gitsn_PositionConfidenceSet *p);
static __inline__ void Gitsn_PositionConfidenceSet_delAndSetNull(void *ptr)
{
	Gitsn_PositionConfidenceSet **p = (Gitsn_PositionConfidenceSet **)ptr;
	if (p) { Gitsn_PositionConfidenceSet_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionConfidenceSet_dump(Gitsn_PositionConfidenceSet *p, int tab);
// Gitsn_PositionConfidenceSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedandHeadingandThrottleConfidence
typedef struct Gitsn_SpeedandHeadingandThrottleConfidence
{
	Gitsn_HeadingConfidence		heading;
	Gitsn_SpeedConfidence		speed;
	Gitsn_ThrottleConfidence	throttle;
} Gitsn_SpeedandHeadingandThrottleConfidence;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedandHeadingandThrottleConfidence *Gitsn_SpeedandHeadingandThrottleConfidence_new(Gitsn_HeadingConfidence heading, 
																												   Gitsn_SpeedConfidence speed, 
																												   Gitsn_ThrottleConfidence throttle, Dz1Error *err);
static __inline__ Gitsn_SpeedandHeadingandThrottleConfidence *Gitsn_SpeedandHeadingandThrottleConfidence_gen(Dz1Error *err) { return Gitsn_SpeedandHeadingandThrottleConfidence_new(Gitsn_HeadingConfidence_max, Gitsn_SpeedConfidence_max, Gitsn_ThrottleConfidence_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SpeedandHeadingandThrottleConfidence_copy(Gitsn_SpeedandHeadingandThrottleConfidence *dst, Gitsn_SpeedandHeadingandThrottleConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedandHeadingandThrottleConfidence *Gitsn_SpeedandHeadingandThrottleConfidence_clone(Gitsn_SpeedandHeadingandThrottleConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedandHeadingandThrottleConfidence_purge(Gitsn_SpeedandHeadingandThrottleConfidence *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedandHeadingandThrottleConfidence_del(Gitsn_SpeedandHeadingandThrottleConfidence *p);
static __inline__ void Gitsn_SpeedandHeadingandThrottleConfidence_delAndSetNull(void *ptr)
{
	Gitsn_SpeedandHeadingandThrottleConfidence **p = (Gitsn_SpeedandHeadingandThrottleConfidence **)ptr;
	if (p) { Gitsn_SpeedandHeadingandThrottleConfidence_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedandHeadingandThrottleConfidence_dump(Gitsn_SpeedandHeadingandThrottleConfidence *p, int tab);
// Gitsn_SpeedandHeadingandThrottleConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_FullPositionVector
typedef struct Gitsn_FullPositionVector
{
	Gitsn_DDateTime									*utcTime;
	Gitsn_Longitude									 lon;
	Gitsn_Latitude									 lat;
	Gitsn_Elevation									 elevation;
	Gitsn_Heading									 heading;
	Gitsn_TransmissionAndSpeed						*speed;
	Gitsn_PositionalAccuracy						*posAccuracy;
	Gitsn_TimeConfidence							 timeConfidence;
	Gitsn_PositionConfidenceSet						*posConfidence;
	Gitsn_SpeedandHeadingandThrottleConfidence		*speedConfidence;
} Gitsn_FullPositionVector;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_FullPositionVector *Gitsn_FullPositionVector_new(Gitsn_Longitude lon, 
																			   Gitsn_Latitude lat, Dz1Error *err);
static __inline__ Gitsn_FullPositionVector *Gitsn_FullPositionVector_gen(Dz1Error *err) { return Gitsn_FullPositionVector_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_FullPositionVector_copy(Gitsn_FullPositionVector *dst, Gitsn_FullPositionVector *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_FullPositionVector *Gitsn_FullPositionVector_clone(Gitsn_FullPositionVector *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_FullPositionVector_purge(Gitsn_FullPositionVector *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_FullPositionVector_del(Gitsn_FullPositionVector *p);
static __inline__ void Gitsn_FullPositionVector_delAndSetNull(void *ptr)
{
	Gitsn_FullPositionVector **p = (Gitsn_FullPositionVector **)ptr;
	if (p) { Gitsn_FullPositionVector_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_FullPositionVector_dump(Gitsn_FullPositionVector *p, int tab);
// Gitsn_FullPositionVector
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleClassification
typedef struct Gitsn_VehicleClassification
{
	Gitsn_BasicVehicleClass				keyType;
	Gitsn_BasicVehicleRole				role;
	Gitsn_Iso3833VehicleType			iso3883;
	Gitsn_VehicleType					hpmsType;
	Gitsn_VehicleGroupAffected			vehicleType;
	Gitsn_IncidentResponseEquipment		responseEquip;
	Gitsn_ResponderGroupAffected		responderType;
	Gitsn_FuelType						fuelType;
} Gitsn_VehicleClassification;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleClassification *Gitsn_VehicleClassification_new(Dz1Error *err);
static __inline__ Gitsn_VehicleClassification *Gitsn_VehicleClassification_gen(Dz1Error *err) { return Gitsn_VehicleClassification_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleClassification_copy(Gitsn_VehicleClassification *dst, Gitsn_VehicleClassification *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleClassification *Gitsn_VehicleClassification_clone(Gitsn_VehicleClassification *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleClassification_purge(Gitsn_VehicleClassification *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleClassification_del(Gitsn_VehicleClassification *p);
static __inline__ void Gitsn_VehicleClassification_delAndSetNull(void *ptr)
{
	Gitsn_VehicleClassification **p = (Gitsn_VehicleClassification **)ptr;
	if (p) { Gitsn_VehicleClassification_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleClassification_dump(Gitsn_VehicleClassification *p, int tab);
// Gitsn_VehicleClassification
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PathHistoryPoint
typedef struct Gitsn_PathHistoryPoint
{
	Gitsn_OffsetLL_B18			 latOffset;
	Gitsn_OffsetLL_B18			 lonOffset;
	Gitsn_VertOffset_B12		 elevationOffset;
	Gitsn_TimeOffset			 timeOffset;
	Gitsn_Speed					 speed;
	Gitsn_PositionalAccuracy	*posAccuracy;
	Gitsn_CoarseHeading			 heading;
} Gitsn_PathHistoryPoint;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PathHistoryPoint *Gitsn_PathHistoryPoint_new(Gitsn_OffsetLL_B18 latOffset, 
																		   Gitsn_OffsetLL_B18 lonOffset, 
																		   Gitsn_VertOffset_B12 elevationOffset, 
																		   Gitsn_TimeOffset timeOffset, Dz1Error *err);
static __inline__ Gitsn_PathHistoryPoint *Gitsn_PathHistoryPoint_gen(Dz1Error *err) { return Gitsn_PathHistoryPoint_new(0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_PathHistoryPoint_copy(Gitsn_PathHistoryPoint *dst, Gitsn_PathHistoryPoint *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PathHistoryPoint *Gitsn_PathHistoryPoint_clone(Gitsn_PathHistoryPoint *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistoryPoint_purge(Gitsn_PathHistoryPoint *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistoryPoint_del(Gitsn_PathHistoryPoint *p);
static __inline__ void Gitsn_PathHistoryPoint_delAndSetNull(void *ptr)
{
	Gitsn_PathHistoryPoint **p = (Gitsn_PathHistoryPoint **)ptr;
	if (p) { Gitsn_PathHistoryPoint_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistoryPoint_dump(Gitsn_PathHistoryPoint *p, int tab);
// Gitsn_PathHistoryPoint
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PathHistoryPointList
typedef struct Gitsn_PathHistoryPointList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_PathHistoryPointList *p);
	Dz1Error (*travel)(struct Gitsn_PathHistoryPointList *p, Dz1Error (*func)(void *ptr, Gitsn_PathHistoryPoint *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_PathHistoryPointList *p, Dz1Error (*func)(void *ptr, Gitsn_PathHistoryPoint *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_PathHistoryPointList *p, Dz1Error (*func)(void *ptr, Gitsn_PathHistoryPoint *entry), void *ptr);
	Gitsn_PathHistoryPoint **(*get_array)(struct Gitsn_PathHistoryPointList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_PathHistoryPointList *p, Gitsn_PathHistoryPoint *data);
	Gitsn_PathHistoryPoint *(*extract)(struct Gitsn_PathHistoryPointList *p, Gitsn_PathHistoryPoint *ptr);
	Gitsn_PathHistoryPoint *(*getHead)(struct Gitsn_PathHistoryPointList *p);
} Gitsn_PathHistoryPointList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PathHistoryPointList *Gitsn_PathHistoryPointList_new(Dz1Error *err);
static __inline__ Gitsn_PathHistoryPointList *Gitsn_PathHistoryPointList_gen(Dz1Error *err) { return Gitsn_PathHistoryPointList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PathHistoryPointList *Gitsn_PathHistoryPointList_clone(Gitsn_PathHistoryPointList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistoryPointList_purge(Gitsn_PathHistoryPointList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistoryPointList_del(Gitsn_PathHistoryPointList *p);
static __inline__ void Gitsn_PathHistoryPointList_delAndSetNull(void *ptr)
{
	Gitsn_PathHistoryPointList **p = (Gitsn_PathHistoryPointList **)ptr;
	if (p != NULL) { Gitsn_PathHistoryPointList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistoryPointList_dump(Gitsn_PathHistoryPointList *p, int tab);

// Gitsn_PathHistoryPointList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PathHistory
typedef struct Gitsn_PathHistory
{
	Gitsn_FullPositionVector		*initialPosition;
	Gitsn_GNSSstatus				*currGNSSstatus;
	Gitsn_PathHistoryPointList		*crumbData;
} Gitsn_PathHistory;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PathHistory *Gitsn_PathHistory_new(Gitsn_PathHistoryPointList *crumbData, Dz1Error *err);
static __inline__ Gitsn_PathHistory *Gitsn_PathHistory_gen(Dz1Error *err) { return Gitsn_PathHistory_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_PathHistory_copy(Gitsn_PathHistory *dst, Gitsn_PathHistory *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PathHistory *Gitsn_PathHistory_clone(Gitsn_PathHistory *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistory_purge(Gitsn_PathHistory *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistory_del(Gitsn_PathHistory *p);
static __inline__ void Gitsn_PathHistory_delAndSetNull(void *ptr)
{
	Gitsn_PathHistory **p = (Gitsn_PathHistory **)ptr;
	if (p) { Gitsn_PathHistory_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathHistory_dump(Gitsn_PathHistory *p, int tab);
// Gitsn_PathHistory
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PathPrediction
typedef struct Gitsn_PathPrediction
{
	Gitsn_RadiusOfCurvature		radiusOfCurve;
	Gitsn_Confidence			confidence;
} Gitsn_PathPrediction;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PathPrediction *Gitsn_PathPrediction_new(Gitsn_RadiusOfCurvature radiusOfCurve, 
																	   Gitsn_Confidence confidence, Dz1Error *err);
static __inline__ Gitsn_PathPrediction *Gitsn_PathPrediction_gen(Dz1Error *err) { return Gitsn_PathPrediction_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_PathPrediction_copy(Gitsn_PathPrediction *dst, Gitsn_PathPrediction *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PathPrediction *Gitsn_PathPrediction_clone(Gitsn_PathPrediction *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathPrediction_purge(Gitsn_PathPrediction *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathPrediction_del(Gitsn_PathPrediction *p);
static __inline__ void Gitsn_PathPrediction_delAndSetNull(void *ptr)
{
	Gitsn_PathPrediction **p = (Gitsn_PathPrediction **)ptr;
	if (p) { Gitsn_PathPrediction_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PathPrediction_dump(Gitsn_PathPrediction *p, int tab);
// Gitsn_PathPrediction
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleSafetyExtensions
typedef struct Gitsn_VehicleSafetyExtensions
{
	Gitsn_VehicleEventFlags		*events;
	Gitsn_PathHistory			*pathHistory;
	Gitsn_PathPrediction		*pathPrediction;
	Gitsn_ExteriorLights		*lights;
} Gitsn_VehicleSafetyExtensions;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleSafetyExtensions *Gitsn_VehicleSafetyExtensions_new(Dz1Error *err);
static __inline__ Gitsn_VehicleSafetyExtensions *Gitsn_VehicleSafetyExtensions_gen(Dz1Error *err) { return Gitsn_VehicleSafetyExtensions_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleSafetyExtensions_copy(Gitsn_VehicleSafetyExtensions *dst, Gitsn_VehicleSafetyExtensions *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleSafetyExtensions *Gitsn_VehicleSafetyExtensions_clone(Gitsn_VehicleSafetyExtensions *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSafetyExtensions_purge(Gitsn_VehicleSafetyExtensions *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSafetyExtensions_del(Gitsn_VehicleSafetyExtensions *p);
static __inline__ void Gitsn_VehicleSafetyExtensions_delAndSetNull(void *ptr)
{
	Gitsn_VehicleSafetyExtensions **p = (Gitsn_VehicleSafetyExtensions **)ptr;
	if (p) { Gitsn_VehicleSafetyExtensions_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSafetyExtensions_dump(Gitsn_VehicleSafetyExtensions *p, int tab);
// Gitsn_VehicleSafetyExtensions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WiperSet
typedef struct Gitsn_WiperSet
{
	Gitsn_WiperStatus		statusFront;
	Gitsn_WiperRate			rateFront;
	Gitsn_WiperStatus		statusRear;
	Gitsn_WiperRate			rateRear;
} Gitsn_WiperSet;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_WiperSet *Gitsn_WiperSet_new(Gitsn_WiperStatus statusFront, 
														   Gitsn_WiperRate rateFront, Dz1Error *err);
static __inline__ Gitsn_WiperSet *Gitsn_WiperSet_gen(Dz1Error *err) { return Gitsn_WiperSet_new(Gitsn_WiperStatus_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_WiperSet_copy(Gitsn_WiperSet *dst, Gitsn_WiperSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_WiperSet *Gitsn_WiperSet_clone(Gitsn_WiperSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WiperSet_purge(Gitsn_WiperSet *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WiperSet_del(Gitsn_WiperSet *p);
static __inline__ void Gitsn_WiperSet_delAndSetNull(void *ptr)
{
	Gitsn_WiperSet **p = (Gitsn_WiperSet **)ptr;
	if (p) { Gitsn_WiperSet_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WiperSet_dump(Gitsn_WiperSet *p, int tab);
// Gitsn_WiperSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_steering
typedef struct Gitsn_VehicleStatus_steering
{
	Gitsn_SteeringWheelAngle				angle;
	Gitsn_SteeringWheelAngleConfidence		confidence;
	Gitsn_SteeringWheelAngleRateOfChange	rate;
	Gitsn_DrivingWheelAngle					wheels;
} Gitsn_VehicleStatus_steering;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_steering *Gitsn_VehicleStatus_steering_new(Gitsn_SteeringWheelAngle angle, Dz1Error *err);
static __inline__ Gitsn_VehicleStatus_steering *Gitsn_VehicleStatus_steering_gen(Dz1Error *err) { return Gitsn_VehicleStatus_steering_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleStatus_steering_copy(Gitsn_VehicleStatus_steering *dst, Gitsn_VehicleStatus_steering *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_steering *Gitsn_VehicleStatus_steering_clone(Gitsn_VehicleStatus_steering *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_steering_purge(Gitsn_VehicleStatus_steering *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_steering_del(Gitsn_VehicleStatus_steering *p);
static __inline__ void Gitsn_VehicleStatus_steering_delAndSetNull(void *ptr)
{
	Gitsn_VehicleStatus_steering **p = (Gitsn_VehicleStatus_steering **)ptr;
	if (p) { Gitsn_VehicleStatus_steering_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_steering_dump(Gitsn_VehicleStatus_steering *p, int tab);
// Gitsn_VehicleStatus_steering
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AccelSteerYawRateConfidence
typedef struct Gitsn_AccelSteerYawRateConfidence
{
	Gitsn_YawRateConfidence					yawRate;
	Gitsn_AccelerationConfidence			acceleration;
	Gitsn_SteeringWheelAngleConfidence		steeringWheelAngle;
} Gitsn_AccelSteerYawRateConfidence;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AccelSteerYawRateConfidence *Gitsn_AccelSteerYawRateConfidence_new(Gitsn_YawRateConfidence yawRate, 
																								 Gitsn_AccelerationConfidence acceleration, 
																								 Gitsn_SteeringWheelAngleConfidence steeringWheelAngle, Dz1Error *err);
static __inline__ Gitsn_AccelSteerYawRateConfidence *Gitsn_AccelSteerYawRateConfidence_gen(Dz1Error *err) { return Gitsn_AccelSteerYawRateConfidence_new(Gitsn_YawRateConfidence_max, Gitsn_AccelerationConfidence_max, Gitsn_SteeringWheelAngleConfidence_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_AccelSteerYawRateConfidence_copy(Gitsn_AccelSteerYawRateConfidence *dst, Gitsn_AccelSteerYawRateConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AccelSteerYawRateConfidence *Gitsn_AccelSteerYawRateConfidence_clone(Gitsn_AccelSteerYawRateConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AccelSteerYawRateConfidence_purge(Gitsn_AccelSteerYawRateConfidence *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AccelSteerYawRateConfidence_del(Gitsn_AccelSteerYawRateConfidence *p);
static __inline__ void Gitsn_AccelSteerYawRateConfidence_delAndSetNull(void *ptr)
{
	Gitsn_AccelSteerYawRateConfidence **p = (Gitsn_AccelSteerYawRateConfidence **)ptr;
	if (p) { Gitsn_AccelSteerYawRateConfidence_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AccelSteerYawRateConfidence_dump(Gitsn_AccelSteerYawRateConfidence *p, int tab);
// Gitsn_AccelSteerYawRateConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConfidenceSet
typedef struct Gitsn_ConfidenceSet
{
	Gitsn_AccelSteerYawRateConfidence				*accelConfidence;
	Gitsn_SpeedandHeadingandThrottleConfidence		*speedConfidence;
	Gitsn_TimeConfidence							 timeConfidence;
	Gitsn_PositionConfidenceSet						*posConfidence;
	Gitsn_SteeringWheelAngleConfidence				 steerConfidence;
	Gitsn_HeadingConfidence							 headingConfidence;
	Gitsn_ThrottleConfidence						 throttleConfidence;
} Gitsn_ConfidenceSet;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConfidenceSet *Gitsn_ConfidenceSet_new(Dz1Error *err);
static __inline__ Gitsn_ConfidenceSet *Gitsn_ConfidenceSet_gen(Dz1Error *err) { return Gitsn_ConfidenceSet_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ConfidenceSet_copy(Gitsn_ConfidenceSet *dst, Gitsn_ConfidenceSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ConfidenceSet *Gitsn_ConfidenceSet_clone(Gitsn_ConfidenceSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConfidenceSet_purge(Gitsn_ConfidenceSet *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConfidenceSet_del(Gitsn_ConfidenceSet *p);
static __inline__ void Gitsn_ConfidenceSet_delAndSetNull(void *ptr)
{
	Gitsn_ConfidenceSet **p = (Gitsn_ConfidenceSet **)ptr;
	if (p) { Gitsn_ConfidenceSet_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ConfidenceSet_dump(Gitsn_ConfidenceSet *p, int tab);
// Gitsn_ConfidenceSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_accelSets
typedef struct Gitsn_VehicleStatus_accelSets
{
	Gitsn_AccelerationSet4Way				*accel4way;
	Gitsn_VerticalAccelerationThreshold		*vertAccelThres;
	Gitsn_YawRateConfidence					 yawRateCon;
	Gitsn_AccelerationConfidence			 hozAccelCon;
	Gitsn_ConfidenceSet						*confidenceSet;
} Gitsn_VehicleStatus_accelSets;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_accelSets *Gitsn_VehicleStatus_accelSets_new(Dz1Error *err);
static __inline__ Gitsn_VehicleStatus_accelSets *Gitsn_VehicleStatus_accelSets_gen(Dz1Error *err) { return Gitsn_VehicleStatus_accelSets_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleStatus_accelSets_copy(Gitsn_VehicleStatus_accelSets *dst, Gitsn_VehicleStatus_accelSets *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_accelSets *Gitsn_VehicleStatus_accelSets_clone(Gitsn_VehicleStatus_accelSets *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_accelSets_purge(Gitsn_VehicleStatus_accelSets *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_accelSets_del(Gitsn_VehicleStatus_accelSets *p);
static __inline__ void Gitsn_VehicleStatus_accelSets_delAndSetNull(void *ptr)
{
	Gitsn_VehicleStatus_accelSets **p = (Gitsn_VehicleStatus_accelSets **)ptr;
	if (p) { Gitsn_VehicleStatus_accelSets_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_accelSets_dump(Gitsn_VehicleStatus_accelSets *p, int tab);
// Gitsn_VehicleStatus_accelSets
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_object
typedef struct Gitsn_VehicleStatus_object
{
	Gitsn_ObstacleDistance		 obDist;
	Gitsn_Angle					 obDirect;
	Gitsn_DDateTime				*dateTime;
} Gitsn_VehicleStatus_object;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_object *Gitsn_VehicleStatus_object_new(Gitsn_ObstacleDistance obDist, 
																				   Gitsn_Angle obDirect, 
																				   Gitsn_DDateTime *dateTime, Dz1Error *err);
static __inline__ Gitsn_VehicleStatus_object *Gitsn_VehicleStatus_object_gen(Dz1Error *err) { return Gitsn_VehicleStatus_object_new(0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleStatus_object_copy(Gitsn_VehicleStatus_object *dst, Gitsn_VehicleStatus_object *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_object *Gitsn_VehicleStatus_object_clone(Gitsn_VehicleStatus_object *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_object_purge(Gitsn_VehicleStatus_object *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_object_del(Gitsn_VehicleStatus_object *p);
static __inline__ void Gitsn_VehicleStatus_object_delAndSetNull(void *ptr)
{
	Gitsn_VehicleStatus_object **p = (Gitsn_VehicleStatus_object **)ptr;
	if (p) { Gitsn_VehicleStatus_object_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_object_dump(Gitsn_VehicleStatus_object *p, int tab);
// Gitsn_VehicleStatus_object
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BumperHeights
typedef struct Gitsn_BumperHeights
{
	Gitsn_BumperHeight		front;
	Gitsn_BumperHeight		rear;
} Gitsn_BumperHeights;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_BumperHeights *Gitsn_BumperHeights_new(Gitsn_BumperHeight front, 
																	 Gitsn_BumperHeight rear, Dz1Error *err);
static __inline__ Gitsn_BumperHeights *Gitsn_BumperHeights_gen(Dz1Error *err) { return Gitsn_BumperHeights_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_BumperHeights_copy(Gitsn_BumperHeights *dst, Gitsn_BumperHeights *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_BumperHeights *Gitsn_BumperHeights_clone(Gitsn_BumperHeights *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BumperHeights_purge(Gitsn_BumperHeights *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BumperHeights_del(Gitsn_BumperHeights *p);
static __inline__ void Gitsn_BumperHeights_delAndSetNull(void *ptr)
{
	Gitsn_BumperHeights **p = (Gitsn_BumperHeights **)ptr;
	if (p) { Gitsn_BumperHeights_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BumperHeights_dump(Gitsn_BumperHeights *p, int tab);
// Gitsn_BumperHeights
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_vehicleData
typedef struct Gitsn_VehicleStatus_vehicleData
{
	Gitsn_VehicleHeight		 height;
	Gitsn_BumperHeights		*bumpers;
	Gitsn_VehicleMass		 mass;
	Gitsn_TrailerWeight		 trailerWeight;
	Gitsn_VehicleType		 type;
} Gitsn_VehicleStatus_vehicleData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_vehicleData *Gitsn_VehicleStatus_vehicleData_new(Gitsn_VehicleHeight height, 
																							 Gitsn_BumperHeights *bumpers, 
																							 Gitsn_VehicleMass mass, 
																							 Gitsn_TrailerWeight trailerWeight, 
																							 Gitsn_VehicleType type, Dz1Error *err);
static __inline__ Gitsn_VehicleStatus_vehicleData *Gitsn_VehicleStatus_vehicleData_gen(Dz1Error *err) { return Gitsn_VehicleStatus_vehicleData_new(0, NULL, 0, 0, Gitsn_VehicleType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleStatus_vehicleData_copy(Gitsn_VehicleStatus_vehicleData *dst, Gitsn_VehicleStatus_vehicleData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_vehicleData *Gitsn_VehicleStatus_vehicleData_clone(Gitsn_VehicleStatus_vehicleData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_vehicleData_purge(Gitsn_VehicleStatus_vehicleData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_vehicleData_del(Gitsn_VehicleStatus_vehicleData *p);
static __inline__ void Gitsn_VehicleStatus_vehicleData_delAndSetNull(void *ptr)
{
	Gitsn_VehicleStatus_vehicleData **p = (Gitsn_VehicleStatus_vehicleData **)ptr;
	if (p) { Gitsn_VehicleStatus_vehicleData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_vehicleData_dump(Gitsn_VehicleStatus_vehicleData *p, int tab);
// Gitsn_VehicleStatus_vehicleData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TireData
typedef struct Gitsn_TireData
{
	Gitsn_TireLocation						location;
	Gitsn_TirePressure						pressure;
	Gitsn_TireTemp							temp;
	Gitsn_WheelSensorStatus					wheelSensorStatus;
	Gitsn_WheelEndElectFault				wheelEndElectFault;
	Gitsn_TireLeakageRate					leakageRate;
	Gitsn_TirePressureThresholdDetection	detection;
} Gitsn_TireData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TireData *Gitsn_TireData_new(Dz1Error *err);
static __inline__ Gitsn_TireData *Gitsn_TireData_gen(Dz1Error *err) { return Gitsn_TireData_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_TireData_copy(Gitsn_TireData *dst, Gitsn_TireData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TireData *Gitsn_TireData_clone(Gitsn_TireData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TireData_purge(Gitsn_TireData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TireData_del(Gitsn_TireData *p);
static __inline__ void Gitsn_TireData_delAndSetNull(void *ptr)
{
	Gitsn_TireData **p = (Gitsn_TireData **)ptr;
	if (p) { Gitsn_TireData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TireData_dump(Gitsn_TireData *p, int tab);
// Gitsn_TireData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TireDataList
typedef struct Gitsn_TireDataList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_TireDataList *p);
	Dz1Error (*travel)(struct Gitsn_TireDataList *p, Dz1Error (*func)(void *ptr, Gitsn_TireData *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_TireDataList *p, Dz1Error (*func)(void *ptr, Gitsn_TireData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_TireDataList *p, Dz1Error (*func)(void *ptr, Gitsn_TireData *entry), void *ptr);
	Gitsn_TireData **(*get_array)(struct Gitsn_TireDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_TireDataList *p, Gitsn_TireData *data);
	Gitsn_TireData *(*extract)(struct Gitsn_TireDataList *p, Gitsn_TireData *ptr);
	Gitsn_TireData *(*getHead)(struct Gitsn_TireDataList *p);
} Gitsn_TireDataList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TireDataList *Gitsn_TireDataList_new(Dz1Error *err);
static __inline__ Gitsn_TireDataList *Gitsn_TireDataList_gen(Dz1Error *err) { return Gitsn_TireDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TireDataList *Gitsn_TireDataList_clone(Gitsn_TireDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TireDataList_purge(Gitsn_TireDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TireDataList_del(Gitsn_TireDataList *p);
static __inline__ void Gitsn_TireDataList_delAndSetNull(void *ptr)
{
	Gitsn_TireDataList **p = (Gitsn_TireDataList **)ptr;
	if (p != NULL) { Gitsn_TireDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TireDataList_dump(Gitsn_TireDataList *p, int tab);

// Gitsn_TireDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AxleWeightSet
typedef struct Gitsn_AxleWeightSet
{
	Gitsn_AxleLocation		location;
	Gitsn_AxleWeight		weight;
} Gitsn_AxleWeightSet;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AxleWeightSet *Gitsn_AxleWeightSet_new(Dz1Error *err);
static __inline__ Gitsn_AxleWeightSet *Gitsn_AxleWeightSet_gen(Dz1Error *err) { return Gitsn_AxleWeightSet_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_AxleWeightSet_copy(Gitsn_AxleWeightSet *dst, Gitsn_AxleWeightSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AxleWeightSet *Gitsn_AxleWeightSet_clone(Gitsn_AxleWeightSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AxleWeightSet_purge(Gitsn_AxleWeightSet *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AxleWeightSet_del(Gitsn_AxleWeightSet *p);
static __inline__ void Gitsn_AxleWeightSet_delAndSetNull(void *ptr)
{
	Gitsn_AxleWeightSet **p = (Gitsn_AxleWeightSet **)ptr;
	if (p) { Gitsn_AxleWeightSet_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AxleWeightSet_dump(Gitsn_AxleWeightSet *p, int tab);
// Gitsn_AxleWeightSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AxleWeightList
typedef struct Gitsn_AxleWeightList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_AxleWeightList *p);
	Dz1Error (*travel)(struct Gitsn_AxleWeightList *p, Dz1Error (*func)(void *ptr, Gitsn_AxleWeightSet *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_AxleWeightList *p, Dz1Error (*func)(void *ptr, Gitsn_AxleWeightSet *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_AxleWeightList *p, Dz1Error (*func)(void *ptr, Gitsn_AxleWeightSet *entry), void *ptr);
	Gitsn_AxleWeightSet **(*get_array)(struct Gitsn_AxleWeightList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_AxleWeightList *p, Gitsn_AxleWeightSet *data);
	Gitsn_AxleWeightSet *(*extract)(struct Gitsn_AxleWeightList *p, Gitsn_AxleWeightSet *ptr);
	Gitsn_AxleWeightSet *(*getHead)(struct Gitsn_AxleWeightList *p);
} Gitsn_AxleWeightList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AxleWeightList *Gitsn_AxleWeightList_new(Dz1Error *err);
static __inline__ Gitsn_AxleWeightList *Gitsn_AxleWeightList_gen(Dz1Error *err) { return Gitsn_AxleWeightList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AxleWeightList *Gitsn_AxleWeightList_clone(Gitsn_AxleWeightList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AxleWeightList_purge(Gitsn_AxleWeightList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AxleWeightList_del(Gitsn_AxleWeightList *p);
static __inline__ void Gitsn_AxleWeightList_delAndSetNull(void *ptr)
{
	Gitsn_AxleWeightList **p = (Gitsn_AxleWeightList **)ptr;
	if (p != NULL) { Gitsn_AxleWeightList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AxleWeightList_dump(Gitsn_AxleWeightList *p, int tab);

// Gitsn_AxleWeightList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_J1939DataItems
typedef struct Gitsn_J1939DataItems
{
	Gitsn_TireDataList					*tires;
	Gitsn_AxleWeightList				*axles;
	Gitsn_TrailerWeight					 trailerWeight;
	Gitsn_CargoWeight					 cargoWeight;
	Gitsn_SteeringAxleTemperature		 steeringAxleTemperature;
	Gitsn_DriveAxleLocation				 driveAxleLocation;
	Gitsn_DriveAxleLiftAirPressure		 driveAxleLiftAirPressure;
	Gitsn_DriveAxleTemperature			 driveAxleTemperature;
	Gitsn_DriveAxleLubePressure			 driveAxleLubePressure;
	Gitsn_SteeringAxleLubePressure		 steeringAxleLubePressure;
} Gitsn_J1939DataItems;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_J1939DataItems *Gitsn_J1939DataItems_new(Dz1Error *err);
static __inline__ Gitsn_J1939DataItems *Gitsn_J1939DataItems_gen(Dz1Error *err) { return Gitsn_J1939DataItems_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_J1939DataItems_copy(Gitsn_J1939DataItems *dst, Gitsn_J1939DataItems *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_J1939DataItems *Gitsn_J1939DataItems_clone(Gitsn_J1939DataItems *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_J1939DataItems_purge(Gitsn_J1939DataItems *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_J1939DataItems_del(Gitsn_J1939DataItems *p);
static __inline__ void Gitsn_J1939DataItems_delAndSetNull(void *ptr)
{
	Gitsn_J1939DataItems **p = (Gitsn_J1939DataItems **)ptr;
	if (p) { Gitsn_J1939DataItems_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_J1939DataItems_dump(Gitsn_J1939DataItems *p, int tab);
// Gitsn_J1939DataItems
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_weatherReport
typedef struct Gitsn_VehicleStatus_weatherReport
{
	Gitsn_EssPrecipYesNo		isRaining;
	Gitsn_EssPrecipRate			rainRate;
	Gitsn_EssPrecipSituation	precipSituation;
	Gitsn_EssSolarRadiation		solarRadiation;
	Gitsn_EssMobileFriction		friction;
} Gitsn_VehicleStatus_weatherReport;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_weatherReport *Gitsn_VehicleStatus_weatherReport_new(Gitsn_EssPrecipYesNo isRaining, Dz1Error *err);
static __inline__ Gitsn_VehicleStatus_weatherReport *Gitsn_VehicleStatus_weatherReport_gen(Dz1Error *err) { return Gitsn_VehicleStatus_weatherReport_new(Gitsn_EssPrecipYesNo_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleStatus_weatherReport_copy(Gitsn_VehicleStatus_weatherReport *dst, Gitsn_VehicleStatus_weatherReport *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus_weatherReport *Gitsn_VehicleStatus_weatherReport_clone(Gitsn_VehicleStatus_weatherReport *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_weatherReport_purge(Gitsn_VehicleStatus_weatherReport *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_weatherReport_del(Gitsn_VehicleStatus_weatherReport *p);
static __inline__ void Gitsn_VehicleStatus_weatherReport_delAndSetNull(void *ptr)
{
	Gitsn_VehicleStatus_weatherReport **p = (Gitsn_VehicleStatus_weatherReport **)ptr;
	if (p) { Gitsn_VehicleStatus_weatherReport_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_weatherReport_dump(Gitsn_VehicleStatus_weatherReport *p, int tab);
// Gitsn_VehicleStatus_weatherReport
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus
typedef struct Gitsn_VehicleStatus
{
	Gitsn_ExteriorLights							*lights;
	Gitsn_LightbarInUse								 lightBar;
	Gitsn_WiperSet									*wipers;
	Gitsn_BrakeSystemStatus							*brakeStatus;
	Gitsn_BrakeAppliedPressure						 brakePressure;
	Gitsn_CoefficientOfFriction						 roadFriction;
	Gitsn_SunSensor									 sunData;
	Gitsn_RainSensor								 rainData;
	Gitsn_AmbientAirTemperature						 airTemp;
	Gitsn_AmbientAirPressure						 airPres;
	Gitsn_VehicleStatus_steering					*steering;
	Gitsn_VehicleStatus_accelSets					*accelSets;
	Gitsn_VehicleStatus_object						*object;
	Gitsn_FullPositionVector						*fullPos;
	Gitsn_ThrottlePosition							 throttlePos;
	Gitsn_SpeedandHeadingandThrottleConfidence		*speedHeadC;
	Gitsn_SpeedConfidence							 speedC;
	Gitsn_VehicleStatus_vehicleData					*vehicleData;
	Gitsn_VehicleIdent								*vehicleIdent;
	Gitsn_J1939DataItems							*j1939DataItems;
	Gitsn_VehicleStatus_weatherReport				*weatherReport;
	Gitsn_GNSSstatus								*gnssStatus;
} Gitsn_VehicleStatus;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus *Gitsn_VehicleStatus_new(Dz1Error *err);
static __inline__ Gitsn_VehicleStatus *Gitsn_VehicleStatus_gen(Dz1Error *err) { return Gitsn_VehicleStatus_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleStatus_copy(Gitsn_VehicleStatus *dst, Gitsn_VehicleStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleStatus *Gitsn_VehicleStatus_clone(Gitsn_VehicleStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_purge(Gitsn_VehicleStatus *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_del(Gitsn_VehicleStatus *p);
static __inline__ void Gitsn_VehicleStatus_delAndSetNull(void *ptr)
{
	Gitsn_VehicleStatus **p = (Gitsn_VehicleStatus **)ptr;
	if (p) { Gitsn_VehicleStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleStatus_dump(Gitsn_VehicleStatus *p, int tab);
// Gitsn_VehicleStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Snapshot
typedef struct Gitsn_Snapshot
{
	Gitsn_FullPositionVector			*thePosition;
	Gitsn_VehicleSafetyExtensions		*safetyExt;
	Gitsn_VehicleStatus					*dataSet;
} Gitsn_Snapshot;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Snapshot *Gitsn_Snapshot_new(Gitsn_FullPositionVector *thePosition, Dz1Error *err);
static __inline__ Gitsn_Snapshot *Gitsn_Snapshot_gen(Dz1Error *err) { return Gitsn_Snapshot_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Snapshot_copy(Gitsn_Snapshot *dst, Gitsn_Snapshot *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Snapshot *Gitsn_Snapshot_clone(Gitsn_Snapshot *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Snapshot_purge(Gitsn_Snapshot *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Snapshot_del(Gitsn_Snapshot *p);
static __inline__ void Gitsn_Snapshot_delAndSetNull(void *ptr)
{
	Gitsn_Snapshot **p = (Gitsn_Snapshot **)ptr;
	if (p) { Gitsn_Snapshot_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Snapshot_dump(Gitsn_Snapshot *p, int tab);
// Gitsn_Snapshot
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ProbeVehicleData_snapshots
typedef struct Gitsn_ProbeVehicleData_snapshots
{
	void *storage;
	unsigned int (*count)(struct Gitsn_ProbeVehicleData_snapshots *p);
	Dz1Error (*travel)(struct Gitsn_ProbeVehicleData_snapshots *p, Dz1Error (*func)(void *ptr, Gitsn_Snapshot *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_ProbeVehicleData_snapshots *p, Dz1Error (*func)(void *ptr, Gitsn_Snapshot *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_ProbeVehicleData_snapshots *p, Dz1Error (*func)(void *ptr, Gitsn_Snapshot *entry), void *ptr);
	Gitsn_Snapshot **(*get_array)(struct Gitsn_ProbeVehicleData_snapshots *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_ProbeVehicleData_snapshots *p, Gitsn_Snapshot *data);
	Gitsn_Snapshot *(*extract)(struct Gitsn_ProbeVehicleData_snapshots *p, Gitsn_Snapshot *ptr);
	Gitsn_Snapshot *(*getHead)(struct Gitsn_ProbeVehicleData_snapshots *p);
} Gitsn_ProbeVehicleData_snapshots;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ProbeVehicleData_snapshots *Gitsn_ProbeVehicleData_snapshots_new(Dz1Error *err);
static __inline__ Gitsn_ProbeVehicleData_snapshots *Gitsn_ProbeVehicleData_snapshots_gen(Dz1Error *err) { return Gitsn_ProbeVehicleData_snapshots_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ProbeVehicleData_snapshots *Gitsn_ProbeVehicleData_snapshots_clone(Gitsn_ProbeVehicleData_snapshots *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ProbeVehicleData_snapshots_purge(Gitsn_ProbeVehicleData_snapshots *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ProbeVehicleData_snapshots_del(Gitsn_ProbeVehicleData_snapshots *p);
static __inline__ void Gitsn_ProbeVehicleData_snapshots_delAndSetNull(void *ptr)
{
	Gitsn_ProbeVehicleData_snapshots **p = (Gitsn_ProbeVehicleData_snapshots **)ptr;
	if (p != NULL) { Gitsn_ProbeVehicleData_snapshots_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ProbeVehicleData_snapshots_dump(Gitsn_ProbeVehicleData_snapshots *p, int tab);

// Gitsn_ProbeVehicleData_snapshots
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSideAlert_description
typedef struct Gitsn_RoadSideAlert_description
{
	void *storage;
	unsigned int (*count)(struct Gitsn_RoadSideAlert_description *p);
	Dz1Error (*travel)(struct Gitsn_RoadSideAlert_description *p, Dz1Error (*func)(void *ptr, Gitsn_ITIScodes *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_RoadSideAlert_description *p, Dz1Error (*func)(void *ptr, Gitsn_ITIScodes *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_RoadSideAlert_description *p, Dz1Error (*func)(void *ptr, Gitsn_ITIScodes *entry), void *ptr);
	Gitsn_ITIScodes *(*get_array)(struct Gitsn_RoadSideAlert_description *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_RoadSideAlert_description *p, Gitsn_ITIScodes data);
	Gitsn_ITIScodes *(*extract)(struct Gitsn_RoadSideAlert_description *p, Gitsn_ITIScodes *ptr);
	Gitsn_ITIScodes *(*getHead)(struct Gitsn_RoadSideAlert_description *p);
	int (*cmp)(Gitsn_ITIScodes *a, Gitsn_ITIScodes *b);
} Gitsn_RoadSideAlert_description;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSideAlert_description *Gitsn_RoadSideAlert_description_new(Dz1Error *err);
static __inline__ Gitsn_RoadSideAlert_description *Gitsn_RoadSideAlert_description_gen(Dz1Error *err) { return Gitsn_RoadSideAlert_description_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSideAlert_description *Gitsn_RoadSideAlert_description_clone(Gitsn_RoadSideAlert_description *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_description_purge(Gitsn_RoadSideAlert_description *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_description_del(Gitsn_RoadSideAlert_description *p);
static __inline__ void Gitsn_RoadSideAlert_description_delAndSetNull(void *ptr)
{
	Gitsn_RoadSideAlert_description **p = (Gitsn_RoadSideAlert_description **)ptr;
	if (p != NULL) { Gitsn_RoadSideAlert_description_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_descriptionA_dump(Gitsn_RoadSideAlert_description *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_descriptionA_fdump(FILE *fp, Gitsn_RoadSideAlert_description *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_descriptionW_dump(Gitsn_RoadSideAlert_description *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_descriptionW_fdump(FILE *fp, Gitsn_RoadSideAlert_description *p, int tab);
#ifdef UNICODE
#define Gitsn_RoadSideAlert_description_dump Gitsn_RoadSideAlert_descriptionW_dump
#define Gitsn_RoadSideAlert_description_fdump Gitsn_RoadSideAlert_descriptionW_fdump
#else //  UNICODE
#define Gitsn_RoadSideAlert_description_dump Gitsn_RoadSideAlert_descriptionA_dump
#define Gitsn_RoadSideAlert_description_fdump Gitsn_RoadSideAlert_descriptionA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RoadSideAlert_descriptionX_dump(Gitsn_RoadSideAlert_description *p, int tab) { DZ1_DUMP(Gitsn_RoadSideAlert_description, p, tab); }
static __inline__ void Gitsn_RoadSideAlert_descriptionX_fdump(FILE *fp, Gitsn_RoadSideAlert_description *p, int tab) { DZ1_FDUMP(fp, Gitsn_RoadSideAlert_description, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RoadSideAlert_description_dump Gitsn_RoadSideAlert_descriptionA_dump
#define Gitsn_RoadSideAlert_descriptionX_dump Gitsn_RoadSideAlert_descriptionA_dump
#define Gitsn_RoadSideAlert_description_fdump Gitsn_RoadSideAlert_descriptionA_fdump
#define Gitsn_RoadSideAlert_descriptionX_fdump Gitsn_RoadSideAlert_descriptionA_fdump
#endif // UNIX_SYSTEM

// Gitsn_RoadSideAlert_description
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSignID
typedef struct Gitsn_RoadSignID
{
	Gitsn_Position3D		*position;
	Gitsn_HeadingSlice		*viewAngle;
	Gitsn_MUTCDCode			 mutcdCode;
	Gitsn_MsgCRC			 crc;
} Gitsn_RoadSignID;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSignID *Gitsn_RoadSignID_new(Gitsn_Position3D *position, 
															   Gitsn_HeadingSlice *viewAngle, Dz1Error *err);
static __inline__ Gitsn_RoadSignID *Gitsn_RoadSignID_gen(Dz1Error *err) { return Gitsn_RoadSignID_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RoadSignID_copy(Gitsn_RoadSignID *dst, Gitsn_RoadSignID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSignID *Gitsn_RoadSignID_clone(Gitsn_RoadSignID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSignID_purge(Gitsn_RoadSignID *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSignID_del(Gitsn_RoadSignID *p);
static __inline__ void Gitsn_RoadSignID_delAndSetNull(void *ptr)
{
	Gitsn_RoadSignID **p = (Gitsn_RoadSignID **)ptr;
	if (p) { Gitsn_RoadSignID_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSignID_dump(Gitsn_RoadSignID *p, int tab);
// Gitsn_RoadSignID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame_msgIdPresent
typedef enum Gitsn_TravelerDataFrame_msgIdPresent
{
	Gitsn_TravelerDataFrame_msgIdPresent_furtherInfoID,
	Gitsn_TravelerDataFrame_msgIdPresent_roadSignID,
	Gitsn_TravelerDataFrame_msgIdPresent_max
} Gitsn_TravelerDataFrame_msgIdPresent;

DZ1_CPPLINK str_t Gitsn_TravelerDataFrame_msgIdPresentStrA(Gitsn_TravelerDataFrame_msgIdPresent v);
DZ1_CPPLINK Gitsn_TravelerDataFrame_msgIdPresent Gitsn_TravelerDataFrame_msgIdPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TravelerDataFrame_msgIdPresentStrW(Gitsn_TravelerDataFrame_msgIdPresent v);
DZ1_CPPLINK Gitsn_TravelerDataFrame_msgIdPresent Gitsn_TravelerDataFrame_msgIdPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TravelerDataFrame_msgIdPresentStr Gitsn_TravelerDataFrame_msgIdPresentStrW
#define Gitsn_TravelerDataFrame_msgIdPresentFromStr Gitsn_TravelerDataFrame_msgIdPresentFromStrW
#else // UNICODE
#define Gitsn_TravelerDataFrame_msgIdPresentStr Gitsn_TravelerDataFrame_msgIdPresentStrA
#define Gitsn_TravelerDataFrame_msgIdPresentFromStr Gitsn_TravelerDataFrame_msgIdPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TravelerDataFrame_msgIdPresentStr Gitsn_TravelerDataFrame_msgIdPresentStrA
#define Gitsn_TravelerDataFrame_msgIdPresentFromStr Gitsn_TravelerDataFrame_msgIdPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame_msgIdPresent *Gitsn_TravelerDataFrame_msgIdPresent_new(Gitsn_TravelerDataFrame_msgIdPresent *src, Dz1Error *err);
static __inline__ Gitsn_TravelerDataFrame_msgIdPresent *Gitsn_TravelerDataFrame_msgIdPresent_gen(Dz1Error *err) { Gitsn_TravelerDataFrame_msgIdPresent v = Gitsn_TravelerDataFrame_msgIdPresent_max; return Gitsn_TravelerDataFrame_msgIdPresent_new(&v, err); }
#define Gitsn_TravelerDataFrame_msgIdPresent_clone             Gitsn_TravelerDataFrame_msgIdPresent_new
static __inline__ void Gitsn_TravelerDataFrame_msgIdPresent_del(Gitsn_TravelerDataFrame_msgIdPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TravelerDataFrame_msgIdPresent_delAndSetNull(void *ptr)
{
	Gitsn_TravelerDataFrame_msgIdPresent **p = (Gitsn_TravelerDataFrame_msgIdPresent **)ptr;
	if (p != NULL) { Gitsn_TravelerDataFrame_msgIdPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_msgIdPresent_dump(Gitsn_TravelerDataFrame_msgIdPresent *v, int tab);
// Gitsn_TravelerDataFrame_msgIdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame_msgId
typedef struct Gitsn_TravelerDataFrame_msgId
{
	Gitsn_TravelerDataFrame_msgIdPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_FurtherInfoID		 furtherInfoID;
		Gitsn_RoadSignID		*roadSignID;
	} x;
} Gitsn_TravelerDataFrame_msgId;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame_msgId *Gitsn_TravelerDataFrame_msgId_new(Gitsn_TravelerDataFrame_msgIdPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_TravelerDataFrame_msgId *Gitsn_TravelerDataFrame_msgId_gen(Dz1Error *err) { return Gitsn_TravelerDataFrame_msgId_new(Gitsn_TravelerDataFrame_msgIdPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_TravelerDataFrame_msgId_copy(Gitsn_TravelerDataFrame_msgId *dst, Gitsn_TravelerDataFrame_msgId *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame_msgId *Gitsn_TravelerDataFrame_msgId_clone(Gitsn_TravelerDataFrame_msgId *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_msgId_purge(Gitsn_TravelerDataFrame_msgId *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_msgId_del(Gitsn_TravelerDataFrame_msgId *p);
static __inline__ void Gitsn_TravelerDataFrame_msgId_delAndSetNull(void *ptr)
{
	Gitsn_TravelerDataFrame_msgId **p = (Gitsn_TravelerDataFrame_msgId **)ptr;
	if (p != NULL) { Gitsn_TravelerDataFrame_msgId_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_msgId_dump(Gitsn_TravelerDataFrame_msgId *p, int tab);
// Gitsn_TravelerDataFrame_msgId
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_24B
typedef struct Gitsn_Node_LL_24B
{
	Gitsn_OffsetLL_B12		lon;
	Gitsn_OffsetLL_B12		lat;
} Gitsn_Node_LL_24B;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_24B *Gitsn_Node_LL_24B_new(Gitsn_OffsetLL_B12 lon, 
																 Gitsn_OffsetLL_B12 lat, Dz1Error *err);
static __inline__ Gitsn_Node_LL_24B *Gitsn_Node_LL_24B_gen(Dz1Error *err) { return Gitsn_Node_LL_24B_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_LL_24B_copy(Gitsn_Node_LL_24B *dst, Gitsn_Node_LL_24B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_24B *Gitsn_Node_LL_24B_clone(Gitsn_Node_LL_24B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_24B_purge(Gitsn_Node_LL_24B *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_24B_del(Gitsn_Node_LL_24B *p);
static __inline__ void Gitsn_Node_LL_24B_delAndSetNull(void *ptr)
{
	Gitsn_Node_LL_24B **p = (Gitsn_Node_LL_24B **)ptr;
	if (p) { Gitsn_Node_LL_24B_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_24B_dump(Gitsn_Node_LL_24B *p, int tab);
// Gitsn_Node_LL_24B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_28B
typedef struct Gitsn_Node_LL_28B
{
	Gitsn_OffsetLL_B14		lon;
	Gitsn_OffsetLL_B14		lat;
} Gitsn_Node_LL_28B;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_28B *Gitsn_Node_LL_28B_new(Gitsn_OffsetLL_B14 lon, 
																 Gitsn_OffsetLL_B14 lat, Dz1Error *err);
static __inline__ Gitsn_Node_LL_28B *Gitsn_Node_LL_28B_gen(Dz1Error *err) { return Gitsn_Node_LL_28B_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_LL_28B_copy(Gitsn_Node_LL_28B *dst, Gitsn_Node_LL_28B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_28B *Gitsn_Node_LL_28B_clone(Gitsn_Node_LL_28B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_28B_purge(Gitsn_Node_LL_28B *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_28B_del(Gitsn_Node_LL_28B *p);
static __inline__ void Gitsn_Node_LL_28B_delAndSetNull(void *ptr)
{
	Gitsn_Node_LL_28B **p = (Gitsn_Node_LL_28B **)ptr;
	if (p) { Gitsn_Node_LL_28B_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_28B_dump(Gitsn_Node_LL_28B *p, int tab);
// Gitsn_Node_LL_28B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_32B
typedef struct Gitsn_Node_LL_32B
{
	Gitsn_OffsetLL_B16		lon;
	Gitsn_OffsetLL_B16		lat;
} Gitsn_Node_LL_32B;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_32B *Gitsn_Node_LL_32B_new(Gitsn_OffsetLL_B16 lon, 
																 Gitsn_OffsetLL_B16 lat, Dz1Error *err);
static __inline__ Gitsn_Node_LL_32B *Gitsn_Node_LL_32B_gen(Dz1Error *err) { return Gitsn_Node_LL_32B_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_LL_32B_copy(Gitsn_Node_LL_32B *dst, Gitsn_Node_LL_32B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_32B *Gitsn_Node_LL_32B_clone(Gitsn_Node_LL_32B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_32B_purge(Gitsn_Node_LL_32B *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_32B_del(Gitsn_Node_LL_32B *p);
static __inline__ void Gitsn_Node_LL_32B_delAndSetNull(void *ptr)
{
	Gitsn_Node_LL_32B **p = (Gitsn_Node_LL_32B **)ptr;
	if (p) { Gitsn_Node_LL_32B_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_32B_dump(Gitsn_Node_LL_32B *p, int tab);
// Gitsn_Node_LL_32B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_36B
typedef struct Gitsn_Node_LL_36B
{
	Gitsn_OffsetLL_B18		lon;
	Gitsn_OffsetLL_B18		lat;
} Gitsn_Node_LL_36B;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_36B *Gitsn_Node_LL_36B_new(Gitsn_OffsetLL_B18 lon, 
																 Gitsn_OffsetLL_B18 lat, Dz1Error *err);
static __inline__ Gitsn_Node_LL_36B *Gitsn_Node_LL_36B_gen(Dz1Error *err) { return Gitsn_Node_LL_36B_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_LL_36B_copy(Gitsn_Node_LL_36B *dst, Gitsn_Node_LL_36B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_36B *Gitsn_Node_LL_36B_clone(Gitsn_Node_LL_36B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_36B_purge(Gitsn_Node_LL_36B *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_36B_del(Gitsn_Node_LL_36B *p);
static __inline__ void Gitsn_Node_LL_36B_delAndSetNull(void *ptr)
{
	Gitsn_Node_LL_36B **p = (Gitsn_Node_LL_36B **)ptr;
	if (p) { Gitsn_Node_LL_36B_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_36B_dump(Gitsn_Node_LL_36B *p, int tab);
// Gitsn_Node_LL_36B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_44B
typedef struct Gitsn_Node_LL_44B
{
	Gitsn_OffsetLL_B22		lon;
	Gitsn_OffsetLL_B22		lat;
} Gitsn_Node_LL_44B;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_44B *Gitsn_Node_LL_44B_new(Gitsn_OffsetLL_B22 lon, 
																 Gitsn_OffsetLL_B22 lat, Dz1Error *err);
static __inline__ Gitsn_Node_LL_44B *Gitsn_Node_LL_44B_gen(Dz1Error *err) { return Gitsn_Node_LL_44B_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_LL_44B_copy(Gitsn_Node_LL_44B *dst, Gitsn_Node_LL_44B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_44B *Gitsn_Node_LL_44B_clone(Gitsn_Node_LL_44B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_44B_purge(Gitsn_Node_LL_44B *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_44B_del(Gitsn_Node_LL_44B *p);
static __inline__ void Gitsn_Node_LL_44B_delAndSetNull(void *ptr)
{
	Gitsn_Node_LL_44B **p = (Gitsn_Node_LL_44B **)ptr;
	if (p) { Gitsn_Node_LL_44B_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_44B_dump(Gitsn_Node_LL_44B *p, int tab);
// Gitsn_Node_LL_44B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_48B
typedef struct Gitsn_Node_LL_48B
{
	Gitsn_OffsetLL_B24		lon;
	Gitsn_OffsetLL_B24		lat;
} Gitsn_Node_LL_48B;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_48B *Gitsn_Node_LL_48B_new(Gitsn_OffsetLL_B24 lon, 
																 Gitsn_OffsetLL_B24 lat, Dz1Error *err);
static __inline__ Gitsn_Node_LL_48B *Gitsn_Node_LL_48B_gen(Dz1Error *err) { return Gitsn_Node_LL_48B_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Node_LL_48B_copy(Gitsn_Node_LL_48B *dst, Gitsn_Node_LL_48B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Node_LL_48B *Gitsn_Node_LL_48B_clone(Gitsn_Node_LL_48B *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_48B_purge(Gitsn_Node_LL_48B *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_48B_del(Gitsn_Node_LL_48B *p);
static __inline__ void Gitsn_Node_LL_48B_delAndSetNull(void *ptr)
{
	Gitsn_Node_LL_48B **p = (Gitsn_Node_LL_48B **)ptr;
	if (p) { Gitsn_Node_LL_48B_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Node_LL_48B_dump(Gitsn_Node_LL_48B *p, int tab);
// Gitsn_Node_LL_48B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeOffsetPointLLPresent
typedef enum Gitsn_NodeOffsetPointLLPresent
{
	Gitsn_NodeOffsetPointLLPresent_node_LL1,
	Gitsn_NodeOffsetPointLLPresent_node_LL2,
	Gitsn_NodeOffsetPointLLPresent_node_LL3,
	Gitsn_NodeOffsetPointLLPresent_node_LL4,
	Gitsn_NodeOffsetPointLLPresent_node_LL5,
	Gitsn_NodeOffsetPointLLPresent_node_LL6,
	Gitsn_NodeOffsetPointLLPresent_node_LatLon,
	Gitsn_NodeOffsetPointLLPresent_max
} Gitsn_NodeOffsetPointLLPresent;

DZ1_CPPLINK str_t Gitsn_NodeOffsetPointLLPresentStrA(Gitsn_NodeOffsetPointLLPresent v);
DZ1_CPPLINK Gitsn_NodeOffsetPointLLPresent Gitsn_NodeOffsetPointLLPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NodeOffsetPointLLPresentStrW(Gitsn_NodeOffsetPointLLPresent v);
DZ1_CPPLINK Gitsn_NodeOffsetPointLLPresent Gitsn_NodeOffsetPointLLPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NodeOffsetPointLLPresentStr Gitsn_NodeOffsetPointLLPresentStrW
#define Gitsn_NodeOffsetPointLLPresentFromStr Gitsn_NodeOffsetPointLLPresentFromStrW
#else // UNICODE
#define Gitsn_NodeOffsetPointLLPresentStr Gitsn_NodeOffsetPointLLPresentStrA
#define Gitsn_NodeOffsetPointLLPresentFromStr Gitsn_NodeOffsetPointLLPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NodeOffsetPointLLPresentStr Gitsn_NodeOffsetPointLLPresentStrA
#define Gitsn_NodeOffsetPointLLPresentFromStr Gitsn_NodeOffsetPointLLPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeOffsetPointLLPresent *Gitsn_NodeOffsetPointLLPresent_new(Gitsn_NodeOffsetPointLLPresent *src, Dz1Error *err);
static __inline__ Gitsn_NodeOffsetPointLLPresent *Gitsn_NodeOffsetPointLLPresent_gen(Dz1Error *err) { Gitsn_NodeOffsetPointLLPresent v = Gitsn_NodeOffsetPointLLPresent_max; return Gitsn_NodeOffsetPointLLPresent_new(&v, err); }
#define Gitsn_NodeOffsetPointLLPresent_clone             Gitsn_NodeOffsetPointLLPresent_new
static __inline__ void Gitsn_NodeOffsetPointLLPresent_del(Gitsn_NodeOffsetPointLLPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_NodeOffsetPointLLPresent_delAndSetNull(void *ptr)
{
	Gitsn_NodeOffsetPointLLPresent **p = (Gitsn_NodeOffsetPointLLPresent **)ptr;
	if (p != NULL) { Gitsn_NodeOffsetPointLLPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeOffsetPointLLPresent_dump(Gitsn_NodeOffsetPointLLPresent *v, int tab);
// Gitsn_NodeOffsetPointLLPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeOffsetPointLL
typedef struct Gitsn_NodeOffsetPointLL
{
	Gitsn_NodeOffsetPointLLPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_Node_LL_24B		*node_LL1;
		Gitsn_Node_LL_28B		*node_LL2;
		Gitsn_Node_LL_32B		*node_LL3;
		Gitsn_Node_LL_36B		*node_LL4;
		Gitsn_Node_LL_44B		*node_LL5;
		Gitsn_Node_LL_48B		*node_LL6;
		Gitsn_Node_LLmD_64b		*node_LatLon;
	} x;
} Gitsn_NodeOffsetPointLL;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeOffsetPointLL *Gitsn_NodeOffsetPointLL_new(Gitsn_NodeOffsetPointLLPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_NodeOffsetPointLL *Gitsn_NodeOffsetPointLL_gen(Dz1Error *err) { return Gitsn_NodeOffsetPointLL_new(Gitsn_NodeOffsetPointLLPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_NodeOffsetPointLL_copy(Gitsn_NodeOffsetPointLL *dst, Gitsn_NodeOffsetPointLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeOffsetPointLL *Gitsn_NodeOffsetPointLL_clone(Gitsn_NodeOffsetPointLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeOffsetPointLL_purge(Gitsn_NodeOffsetPointLL *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeOffsetPointLL_del(Gitsn_NodeOffsetPointLL *p);
static __inline__ void Gitsn_NodeOffsetPointLL_delAndSetNull(void *ptr)
{
	Gitsn_NodeOffsetPointLL **p = (Gitsn_NodeOffsetPointLL **)ptr;
	if (p != NULL) { Gitsn_NodeOffsetPointLL_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeOffsetPointLL_dump(Gitsn_NodeOffsetPointLL *p, int tab);
// Gitsn_NodeOffsetPointLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeLLList
typedef struct Gitsn_NodeAttributeLLList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_NodeAttributeLLList *p);
	Dz1Error (*travel)(struct Gitsn_NodeAttributeLLList *p, Dz1Error (*func)(void *ptr, Gitsn_NodeAttributeLL *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_NodeAttributeLLList *p, Dz1Error (*func)(void *ptr, Gitsn_NodeAttributeLL *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_NodeAttributeLLList *p, Dz1Error (*func)(void *ptr, Gitsn_NodeAttributeLL *entry), void *ptr);
	Gitsn_NodeAttributeLL *(*get_array)(struct Gitsn_NodeAttributeLLList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_NodeAttributeLLList *p, Gitsn_NodeAttributeLL data);
	Gitsn_NodeAttributeLL *(*extract)(struct Gitsn_NodeAttributeLLList *p, Gitsn_NodeAttributeLL *ptr);
	Gitsn_NodeAttributeLL *(*getHead)(struct Gitsn_NodeAttributeLLList *p);
} Gitsn_NodeAttributeLLList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeLLList *Gitsn_NodeAttributeLLList_new(Dz1Error *err);
static __inline__ Gitsn_NodeAttributeLLList *Gitsn_NodeAttributeLLList_gen(Dz1Error *err) { return Gitsn_NodeAttributeLLList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeLLList *Gitsn_NodeAttributeLLList_clone(Gitsn_NodeAttributeLLList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeLLList_purge(Gitsn_NodeAttributeLLList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeLLList_del(Gitsn_NodeAttributeLLList *p);
static __inline__ void Gitsn_NodeAttributeLLList_delAndSetNull(void *ptr)
{
	Gitsn_NodeAttributeLLList **p = (Gitsn_NodeAttributeLLList **)ptr;
	if (p != NULL) { Gitsn_NodeAttributeLLList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeLLList_dump(Gitsn_NodeAttributeLLList *p, int tab);

// Gitsn_NodeAttributeLLList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SegmentAttributeLLList
typedef struct Gitsn_SegmentAttributeLLList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_SegmentAttributeLLList *p);
	Dz1Error (*travel)(struct Gitsn_SegmentAttributeLLList *p, Dz1Error (*func)(void *ptr, Gitsn_SegmentAttributeLL *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_SegmentAttributeLLList *p, Dz1Error (*func)(void *ptr, Gitsn_SegmentAttributeLL *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_SegmentAttributeLLList *p, Dz1Error (*func)(void *ptr, Gitsn_SegmentAttributeLL *entry), void *ptr);
	Gitsn_SegmentAttributeLL *(*get_array)(struct Gitsn_SegmentAttributeLLList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_SegmentAttributeLLList *p, Gitsn_SegmentAttributeLL data);
	Gitsn_SegmentAttributeLL *(*extract)(struct Gitsn_SegmentAttributeLLList *p, Gitsn_SegmentAttributeLL *ptr);
	Gitsn_SegmentAttributeLL *(*getHead)(struct Gitsn_SegmentAttributeLLList *p);
} Gitsn_SegmentAttributeLLList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SegmentAttributeLLList *Gitsn_SegmentAttributeLLList_new(Dz1Error *err);
static __inline__ Gitsn_SegmentAttributeLLList *Gitsn_SegmentAttributeLLList_gen(Dz1Error *err) { return Gitsn_SegmentAttributeLLList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SegmentAttributeLLList *Gitsn_SegmentAttributeLLList_clone(Gitsn_SegmentAttributeLLList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SegmentAttributeLLList_purge(Gitsn_SegmentAttributeLLList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SegmentAttributeLLList_del(Gitsn_SegmentAttributeLLList *p);
static __inline__ void Gitsn_SegmentAttributeLLList_delAndSetNull(void *ptr)
{
	Gitsn_SegmentAttributeLLList **p = (Gitsn_SegmentAttributeLLList **)ptr;
	if (p != NULL) { Gitsn_SegmentAttributeLLList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SegmentAttributeLLList_dump(Gitsn_SegmentAttributeLLList *p, int tab);

// Gitsn_SegmentAttributeLLList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeSetLL
typedef struct Gitsn_NodeAttributeSetLL
{
	Gitsn_NodeAttributeLLList		*localNode;
	Gitsn_SegmentAttributeLLList	*disabled;
	Gitsn_SegmentAttributeLLList	*enabled;
	Gitsn_LaneDataAttributeList		*data;
	Gitsn_Offset_B10				 dWidth;
	Gitsn_Offset_B10				 dElevation;
} Gitsn_NodeAttributeSetLL;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeSetLL *Gitsn_NodeAttributeSetLL_new(Dz1Error *err);
static __inline__ Gitsn_NodeAttributeSetLL *Gitsn_NodeAttributeSetLL_gen(Dz1Error *err) { return Gitsn_NodeAttributeSetLL_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_NodeAttributeSetLL_copy(Gitsn_NodeAttributeSetLL *dst, Gitsn_NodeAttributeSetLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeAttributeSetLL *Gitsn_NodeAttributeSetLL_clone(Gitsn_NodeAttributeSetLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeSetLL_purge(Gitsn_NodeAttributeSetLL *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeSetLL_del(Gitsn_NodeAttributeSetLL *p);
static __inline__ void Gitsn_NodeAttributeSetLL_delAndSetNull(void *ptr)
{
	Gitsn_NodeAttributeSetLL **p = (Gitsn_NodeAttributeSetLL **)ptr;
	if (p) { Gitsn_NodeAttributeSetLL_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeAttributeSetLL_dump(Gitsn_NodeAttributeSetLL *p, int tab);
// Gitsn_NodeAttributeSetLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeLL
typedef struct Gitsn_NodeLL
{
	Gitsn_NodeOffsetPointLL		*delta;
	Gitsn_NodeAttributeSetLL	*attributes;
} Gitsn_NodeLL;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeLL *Gitsn_NodeLL_new(Gitsn_NodeOffsetPointLL *delta, Dz1Error *err);
static __inline__ Gitsn_NodeLL *Gitsn_NodeLL_gen(Dz1Error *err) { return Gitsn_NodeLL_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_NodeLL_copy(Gitsn_NodeLL *dst, Gitsn_NodeLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeLL *Gitsn_NodeLL_clone(Gitsn_NodeLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeLL_purge(Gitsn_NodeLL *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeLL_del(Gitsn_NodeLL *p);
static __inline__ void Gitsn_NodeLL_delAndSetNull(void *ptr)
{
	Gitsn_NodeLL **p = (Gitsn_NodeLL **)ptr;
	if (p) { Gitsn_NodeLL_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeLL_dump(Gitsn_NodeLL *p, int tab);
// Gitsn_NodeLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeSetLL
typedef struct Gitsn_NodeSetLL
{
	void *storage;
	unsigned int (*count)(struct Gitsn_NodeSetLL *p);
	Dz1Error (*travel)(struct Gitsn_NodeSetLL *p, Dz1Error (*func)(void *ptr, Gitsn_NodeLL *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_NodeSetLL *p, Dz1Error (*func)(void *ptr, Gitsn_NodeLL *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_NodeSetLL *p, Dz1Error (*func)(void *ptr, Gitsn_NodeLL *entry), void *ptr);
	Gitsn_NodeLL **(*get_array)(struct Gitsn_NodeSetLL *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_NodeSetLL *p, Gitsn_NodeLL *data);
	Gitsn_NodeLL *(*extract)(struct Gitsn_NodeSetLL *p, Gitsn_NodeLL *ptr);
	Gitsn_NodeLL *(*getHead)(struct Gitsn_NodeSetLL *p);
} Gitsn_NodeSetLL;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeSetLL *Gitsn_NodeSetLL_new(Dz1Error *err);
static __inline__ Gitsn_NodeSetLL *Gitsn_NodeSetLL_gen(Dz1Error *err) { return Gitsn_NodeSetLL_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeSetLL *Gitsn_NodeSetLL_clone(Gitsn_NodeSetLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeSetLL_purge(Gitsn_NodeSetLL *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeSetLL_del(Gitsn_NodeSetLL *p);
static __inline__ void Gitsn_NodeSetLL_delAndSetNull(void *ptr)
{
	Gitsn_NodeSetLL **p = (Gitsn_NodeSetLL **)ptr;
	if (p != NULL) { Gitsn_NodeSetLL_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeSetLL_dump(Gitsn_NodeSetLL *p, int tab);

// Gitsn_NodeSetLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeListLLPresent
typedef enum Gitsn_NodeListLLPresent
{
	Gitsn_NodeListLLPresent_nodes,
	Gitsn_NodeListLLPresent_max
} Gitsn_NodeListLLPresent;

DZ1_CPPLINK str_t Gitsn_NodeListLLPresentStrA(Gitsn_NodeListLLPresent v);
DZ1_CPPLINK Gitsn_NodeListLLPresent Gitsn_NodeListLLPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NodeListLLPresentStrW(Gitsn_NodeListLLPresent v);
DZ1_CPPLINK Gitsn_NodeListLLPresent Gitsn_NodeListLLPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NodeListLLPresentStr Gitsn_NodeListLLPresentStrW
#define Gitsn_NodeListLLPresentFromStr Gitsn_NodeListLLPresentFromStrW
#else // UNICODE
#define Gitsn_NodeListLLPresentStr Gitsn_NodeListLLPresentStrA
#define Gitsn_NodeListLLPresentFromStr Gitsn_NodeListLLPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NodeListLLPresentStr Gitsn_NodeListLLPresentStrA
#define Gitsn_NodeListLLPresentFromStr Gitsn_NodeListLLPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeListLLPresent *Gitsn_NodeListLLPresent_new(Gitsn_NodeListLLPresent *src, Dz1Error *err);
static __inline__ Gitsn_NodeListLLPresent *Gitsn_NodeListLLPresent_gen(Dz1Error *err) { Gitsn_NodeListLLPresent v = Gitsn_NodeListLLPresent_max; return Gitsn_NodeListLLPresent_new(&v, err); }
#define Gitsn_NodeListLLPresent_clone             Gitsn_NodeListLLPresent_new
static __inline__ void Gitsn_NodeListLLPresent_del(Gitsn_NodeListLLPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_NodeListLLPresent_delAndSetNull(void *ptr)
{
	Gitsn_NodeListLLPresent **p = (Gitsn_NodeListLLPresent **)ptr;
	if (p != NULL) { Gitsn_NodeListLLPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeListLLPresent_dump(Gitsn_NodeListLLPresent *v, int tab);
// Gitsn_NodeListLLPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeListLL
typedef struct Gitsn_NodeListLL
{
	Gitsn_NodeListLLPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_NodeSetLL		*nodes;
	} x;
} Gitsn_NodeListLL;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeListLL *Gitsn_NodeListLL_new(Gitsn_NodeListLLPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_NodeListLL *Gitsn_NodeListLL_gen(Dz1Error *err) { return Gitsn_NodeListLL_new(Gitsn_NodeListLLPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_NodeListLL_copy(Gitsn_NodeListLL *dst, Gitsn_NodeListLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NodeListLL *Gitsn_NodeListLL_clone(Gitsn_NodeListLL *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeListLL_purge(Gitsn_NodeListLL *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeListLL_del(Gitsn_NodeListLL *p);
static __inline__ void Gitsn_NodeListLL_delAndSetNull(void *ptr)
{
	Gitsn_NodeListLL **p = (Gitsn_NodeListLL **)ptr;
	if (p != NULL) { Gitsn_NodeListLL_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NodeListLL_dump(Gitsn_NodeListLL *p, int tab);
// Gitsn_NodeListLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetSystem_offsetPresent
typedef enum Gitsn_OffsetSystem_offsetPresent
{
	Gitsn_OffsetSystem_offsetPresent_xy,
	Gitsn_OffsetSystem_offsetPresent_ll,
	Gitsn_OffsetSystem_offsetPresent_max
} Gitsn_OffsetSystem_offsetPresent;

DZ1_CPPLINK str_t Gitsn_OffsetSystem_offsetPresentStrA(Gitsn_OffsetSystem_offsetPresent v);
DZ1_CPPLINK Gitsn_OffsetSystem_offsetPresent Gitsn_OffsetSystem_offsetPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_OffsetSystem_offsetPresentStrW(Gitsn_OffsetSystem_offsetPresent v);
DZ1_CPPLINK Gitsn_OffsetSystem_offsetPresent Gitsn_OffsetSystem_offsetPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_OffsetSystem_offsetPresentStr Gitsn_OffsetSystem_offsetPresentStrW
#define Gitsn_OffsetSystem_offsetPresentFromStr Gitsn_OffsetSystem_offsetPresentFromStrW
#else // UNICODE
#define Gitsn_OffsetSystem_offsetPresentStr Gitsn_OffsetSystem_offsetPresentStrA
#define Gitsn_OffsetSystem_offsetPresentFromStr Gitsn_OffsetSystem_offsetPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_OffsetSystem_offsetPresentStr Gitsn_OffsetSystem_offsetPresentStrA
#define Gitsn_OffsetSystem_offsetPresentFromStr Gitsn_OffsetSystem_offsetPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_OffsetSystem_offsetPresent *Gitsn_OffsetSystem_offsetPresent_new(Gitsn_OffsetSystem_offsetPresent *src, Dz1Error *err);
static __inline__ Gitsn_OffsetSystem_offsetPresent *Gitsn_OffsetSystem_offsetPresent_gen(Dz1Error *err) { Gitsn_OffsetSystem_offsetPresent v = Gitsn_OffsetSystem_offsetPresent_max; return Gitsn_OffsetSystem_offsetPresent_new(&v, err); }
#define Gitsn_OffsetSystem_offsetPresent_clone             Gitsn_OffsetSystem_offsetPresent_new
static __inline__ void Gitsn_OffsetSystem_offsetPresent_del(Gitsn_OffsetSystem_offsetPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_OffsetSystem_offsetPresent_delAndSetNull(void *ptr)
{
	Gitsn_OffsetSystem_offsetPresent **p = (Gitsn_OffsetSystem_offsetPresent **)ptr;
	if (p != NULL) { Gitsn_OffsetSystem_offsetPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OffsetSystem_offsetPresent_dump(Gitsn_OffsetSystem_offsetPresent *v, int tab);
// Gitsn_OffsetSystem_offsetPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetSystem_offset
typedef struct Gitsn_OffsetSystem_offset
{
	Gitsn_OffsetSystem_offsetPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_NodeListXY	*xy;
		Gitsn_NodeListLL	*ll;
	} x;
} Gitsn_OffsetSystem_offset;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_OffsetSystem_offset *Gitsn_OffsetSystem_offset_new(Gitsn_OffsetSystem_offsetPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_OffsetSystem_offset *Gitsn_OffsetSystem_offset_gen(Dz1Error *err) { return Gitsn_OffsetSystem_offset_new(Gitsn_OffsetSystem_offsetPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_OffsetSystem_offset_copy(Gitsn_OffsetSystem_offset *dst, Gitsn_OffsetSystem_offset *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_OffsetSystem_offset *Gitsn_OffsetSystem_offset_clone(Gitsn_OffsetSystem_offset *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OffsetSystem_offset_purge(Gitsn_OffsetSystem_offset *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OffsetSystem_offset_del(Gitsn_OffsetSystem_offset *p);
static __inline__ void Gitsn_OffsetSystem_offset_delAndSetNull(void *ptr)
{
	Gitsn_OffsetSystem_offset **p = (Gitsn_OffsetSystem_offset **)ptr;
	if (p != NULL) { Gitsn_OffsetSystem_offset_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OffsetSystem_offset_dump(Gitsn_OffsetSystem_offset *p, int tab);
// Gitsn_OffsetSystem_offset
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetSystem
typedef struct Gitsn_OffsetSystem
{
	Gitsn_Zoom						 scale;
	Gitsn_OffsetSystem_offset		*offset;
} Gitsn_OffsetSystem;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_OffsetSystem *Gitsn_OffsetSystem_new(Gitsn_OffsetSystem_offset *offset, Dz1Error *err);
static __inline__ Gitsn_OffsetSystem *Gitsn_OffsetSystem_gen(Dz1Error *err) { return Gitsn_OffsetSystem_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_OffsetSystem_copy(Gitsn_OffsetSystem *dst, Gitsn_OffsetSystem *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_OffsetSystem *Gitsn_OffsetSystem_clone(Gitsn_OffsetSystem *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OffsetSystem_purge(Gitsn_OffsetSystem *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OffsetSystem_del(Gitsn_OffsetSystem *p);
static __inline__ void Gitsn_OffsetSystem_delAndSetNull(void *ptr)
{
	Gitsn_OffsetSystem **p = (Gitsn_OffsetSystem **)ptr;
	if (p) { Gitsn_OffsetSystem_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OffsetSystem_dump(Gitsn_OffsetSystem *p, int tab);
// Gitsn_OffsetSystem
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Circle
typedef struct Gitsn_Circle
{
	Gitsn_Position3D		*center;
	Gitsn_Radius_B12		 radius;
	Gitsn_DistanceUnits		 units;
} Gitsn_Circle;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Circle *Gitsn_Circle_new(Gitsn_Position3D *center, 
													   Gitsn_Radius_B12 radius, 
													   Gitsn_DistanceUnits units, Dz1Error *err);
static __inline__ Gitsn_Circle *Gitsn_Circle_gen(Dz1Error *err) { return Gitsn_Circle_new(NULL, 0, Gitsn_DistanceUnits_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Circle_copy(Gitsn_Circle *dst, Gitsn_Circle *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Circle *Gitsn_Circle_clone(Gitsn_Circle *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Circle_purge(Gitsn_Circle *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Circle_del(Gitsn_Circle *p);
static __inline__ void Gitsn_Circle_delAndSetNull(void *ptr)
{
	Gitsn_Circle **p = (Gitsn_Circle **)ptr;
	if (p) { Gitsn_Circle_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Circle_dump(Gitsn_Circle *p, int tab);
// Gitsn_Circle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GeometricProjection
typedef struct Gitsn_GeometricProjection
{
	Gitsn_HeadingSlice		*direction;
	Gitsn_Extent			 extent;
	Gitsn_LaneWidth			 laneWidth;
	Gitsn_Circle			*circle;
} Gitsn_GeometricProjection;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_GeometricProjection *Gitsn_GeometricProjection_new(Gitsn_HeadingSlice *direction, 
																				 Gitsn_Circle *circle, Dz1Error *err);
static __inline__ Gitsn_GeometricProjection *Gitsn_GeometricProjection_gen(Dz1Error *err) { return Gitsn_GeometricProjection_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_GeometricProjection_copy(Gitsn_GeometricProjection *dst, Gitsn_GeometricProjection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GeometricProjection *Gitsn_GeometricProjection_clone(Gitsn_GeometricProjection *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeometricProjection_purge(Gitsn_GeometricProjection *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeometricProjection_del(Gitsn_GeometricProjection *p);
static __inline__ void Gitsn_GeometricProjection_delAndSetNull(void *ptr)
{
	Gitsn_GeometricProjection **p = (Gitsn_GeometricProjection **)ptr;
	if (p) { Gitsn_GeometricProjection_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeometricProjection_dump(Gitsn_GeometricProjection *p, int tab);
// Gitsn_GeometricProjection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ShapePointSet
typedef struct Gitsn_ShapePointSet
{
	Gitsn_Position3D		*anchor;
	Gitsn_LaneWidth			 laneWidth;
	Gitsn_DirectionOfUse	 directionality;
	Gitsn_NodeListXY		*nodeList;
} Gitsn_ShapePointSet;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ShapePointSet *Gitsn_ShapePointSet_new(Gitsn_NodeListXY *nodeList, Dz1Error *err);
static __inline__ Gitsn_ShapePointSet *Gitsn_ShapePointSet_gen(Dz1Error *err) { return Gitsn_ShapePointSet_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ShapePointSet_copy(Gitsn_ShapePointSet *dst, Gitsn_ShapePointSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ShapePointSet *Gitsn_ShapePointSet_clone(Gitsn_ShapePointSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ShapePointSet_purge(Gitsn_ShapePointSet *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ShapePointSet_del(Gitsn_ShapePointSet *p);
static __inline__ void Gitsn_ShapePointSet_delAndSetNull(void *ptr)
{
	Gitsn_ShapePointSet **p = (Gitsn_ShapePointSet **)ptr;
	if (p) { Gitsn_ShapePointSet_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ShapePointSet_dump(Gitsn_ShapePointSet *p, int tab);
// Gitsn_ShapePointSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RegionOffsets
typedef struct Gitsn_RegionOffsets
{
	Gitsn_Offset_B16	xOffset;
	Gitsn_Offset_B16	yOffset;
	Gitsn_Offset_B16	zOffset;
} Gitsn_RegionOffsets;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RegionOffsets *Gitsn_RegionOffsets_new(Gitsn_Offset_B16 xOffset, 
																	 Gitsn_Offset_B16 yOffset, Dz1Error *err);
static __inline__ Gitsn_RegionOffsets *Gitsn_RegionOffsets_gen(Dz1Error *err) { return Gitsn_RegionOffsets_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RegionOffsets_copy(Gitsn_RegionOffsets *dst, Gitsn_RegionOffsets *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RegionOffsets *Gitsn_RegionOffsets_clone(Gitsn_RegionOffsets *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionOffsets_purge(Gitsn_RegionOffsets *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionOffsets_del(Gitsn_RegionOffsets *p);
static __inline__ void Gitsn_RegionOffsets_delAndSetNull(void *ptr)
{
	Gitsn_RegionOffsets **p = (Gitsn_RegionOffsets **)ptr;
	if (p) { Gitsn_RegionOffsets_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionOffsets_dump(Gitsn_RegionOffsets *p, int tab);
// Gitsn_RegionOffsets
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RegionList
typedef struct Gitsn_RegionList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_RegionList *p);
	Dz1Error (*travel)(struct Gitsn_RegionList *p, Dz1Error (*func)(void *ptr, Gitsn_RegionOffsets *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_RegionList *p, Dz1Error (*func)(void *ptr, Gitsn_RegionOffsets *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_RegionList *p, Dz1Error (*func)(void *ptr, Gitsn_RegionOffsets *entry), void *ptr);
	Gitsn_RegionOffsets **(*get_array)(struct Gitsn_RegionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_RegionList *p, Gitsn_RegionOffsets *data);
	Gitsn_RegionOffsets *(*extract)(struct Gitsn_RegionList *p, Gitsn_RegionOffsets *ptr);
	Gitsn_RegionOffsets *(*getHead)(struct Gitsn_RegionList *p);
} Gitsn_RegionList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RegionList *Gitsn_RegionList_new(Dz1Error *err);
static __inline__ Gitsn_RegionList *Gitsn_RegionList_gen(Dz1Error *err) { return Gitsn_RegionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RegionList *Gitsn_RegionList_clone(Gitsn_RegionList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionList_purge(Gitsn_RegionList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionList_del(Gitsn_RegionList *p);
static __inline__ void Gitsn_RegionList_delAndSetNull(void *ptr)
{
	Gitsn_RegionList **p = (Gitsn_RegionList **)ptr;
	if (p != NULL) { Gitsn_RegionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionList_dump(Gitsn_RegionList *p, int tab);

// Gitsn_RegionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RegionPointSet
typedef struct Gitsn_RegionPointSet
{
	Gitsn_Position3D	*anchor;
	Gitsn_Zoom			 scale;
	Gitsn_RegionList	*nodeList;
} Gitsn_RegionPointSet;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RegionPointSet *Gitsn_RegionPointSet_new(Gitsn_RegionList *nodeList, Dz1Error *err);
static __inline__ Gitsn_RegionPointSet *Gitsn_RegionPointSet_gen(Dz1Error *err) { return Gitsn_RegionPointSet_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RegionPointSet_copy(Gitsn_RegionPointSet *dst, Gitsn_RegionPointSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RegionPointSet *Gitsn_RegionPointSet_clone(Gitsn_RegionPointSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionPointSet_purge(Gitsn_RegionPointSet *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionPointSet_del(Gitsn_RegionPointSet *p);
static __inline__ void Gitsn_RegionPointSet_delAndSetNull(void *ptr)
{
	Gitsn_RegionPointSet **p = (Gitsn_RegionPointSet **)ptr;
	if (p) { Gitsn_RegionPointSet_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RegionPointSet_dump(Gitsn_RegionPointSet *p, int tab);
// Gitsn_RegionPointSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ValidRegion_areaPresent
typedef enum Gitsn_ValidRegion_areaPresent
{
	Gitsn_ValidRegion_areaPresent_shapePointSet,
	Gitsn_ValidRegion_areaPresent_circle,
	Gitsn_ValidRegion_areaPresent_regionPointSet,
	Gitsn_ValidRegion_areaPresent_max
} Gitsn_ValidRegion_areaPresent;

DZ1_CPPLINK str_t Gitsn_ValidRegion_areaPresentStrA(Gitsn_ValidRegion_areaPresent v);
DZ1_CPPLINK Gitsn_ValidRegion_areaPresent Gitsn_ValidRegion_areaPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ValidRegion_areaPresentStrW(Gitsn_ValidRegion_areaPresent v);
DZ1_CPPLINK Gitsn_ValidRegion_areaPresent Gitsn_ValidRegion_areaPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ValidRegion_areaPresentStr Gitsn_ValidRegion_areaPresentStrW
#define Gitsn_ValidRegion_areaPresentFromStr Gitsn_ValidRegion_areaPresentFromStrW
#else // UNICODE
#define Gitsn_ValidRegion_areaPresentStr Gitsn_ValidRegion_areaPresentStrA
#define Gitsn_ValidRegion_areaPresentFromStr Gitsn_ValidRegion_areaPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ValidRegion_areaPresentStr Gitsn_ValidRegion_areaPresentStrA
#define Gitsn_ValidRegion_areaPresentFromStr Gitsn_ValidRegion_areaPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ValidRegion_areaPresent *Gitsn_ValidRegion_areaPresent_new(Gitsn_ValidRegion_areaPresent *src, Dz1Error *err);
static __inline__ Gitsn_ValidRegion_areaPresent *Gitsn_ValidRegion_areaPresent_gen(Dz1Error *err) { Gitsn_ValidRegion_areaPresent v = Gitsn_ValidRegion_areaPresent_max; return Gitsn_ValidRegion_areaPresent_new(&v, err); }
#define Gitsn_ValidRegion_areaPresent_clone             Gitsn_ValidRegion_areaPresent_new
static __inline__ void Gitsn_ValidRegion_areaPresent_del(Gitsn_ValidRegion_areaPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ValidRegion_areaPresent_delAndSetNull(void *ptr)
{
	Gitsn_ValidRegion_areaPresent **p = (Gitsn_ValidRegion_areaPresent **)ptr;
	if (p != NULL) { Gitsn_ValidRegion_areaPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ValidRegion_areaPresent_dump(Gitsn_ValidRegion_areaPresent *v, int tab);
// Gitsn_ValidRegion_areaPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ValidRegion_area
typedef struct Gitsn_ValidRegion_area
{
	Gitsn_ValidRegion_areaPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_ShapePointSet		*shapePointSet;
		Gitsn_Circle			*circle;
		Gitsn_RegionPointSet	*regionPointSet;
	} x;
} Gitsn_ValidRegion_area;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ValidRegion_area *Gitsn_ValidRegion_area_new(Gitsn_ValidRegion_areaPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_ValidRegion_area *Gitsn_ValidRegion_area_gen(Dz1Error *err) { return Gitsn_ValidRegion_area_new(Gitsn_ValidRegion_areaPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_ValidRegion_area_copy(Gitsn_ValidRegion_area *dst, Gitsn_ValidRegion_area *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ValidRegion_area *Gitsn_ValidRegion_area_clone(Gitsn_ValidRegion_area *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ValidRegion_area_purge(Gitsn_ValidRegion_area *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ValidRegion_area_del(Gitsn_ValidRegion_area *p);
static __inline__ void Gitsn_ValidRegion_area_delAndSetNull(void *ptr)
{
	Gitsn_ValidRegion_area **p = (Gitsn_ValidRegion_area **)ptr;
	if (p != NULL) { Gitsn_ValidRegion_area_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ValidRegion_area_dump(Gitsn_ValidRegion_area *p, int tab);
// Gitsn_ValidRegion_area
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ValidRegion
typedef struct Gitsn_ValidRegion
{
	Gitsn_HeadingSlice			*direction;
	Gitsn_Extent				 extent;
	Gitsn_ValidRegion_area		*area;
} Gitsn_ValidRegion;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ValidRegion *Gitsn_ValidRegion_new(Gitsn_HeadingSlice *direction, 
																 Gitsn_ValidRegion_area *area, Dz1Error *err);
static __inline__ Gitsn_ValidRegion *Gitsn_ValidRegion_gen(Dz1Error *err) { return Gitsn_ValidRegion_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ValidRegion_copy(Gitsn_ValidRegion *dst, Gitsn_ValidRegion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ValidRegion *Gitsn_ValidRegion_clone(Gitsn_ValidRegion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ValidRegion_purge(Gitsn_ValidRegion *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ValidRegion_del(Gitsn_ValidRegion *p);
static __inline__ void Gitsn_ValidRegion_delAndSetNull(void *ptr)
{
	Gitsn_ValidRegion **p = (Gitsn_ValidRegion **)ptr;
	if (p) { Gitsn_ValidRegion_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ValidRegion_dump(Gitsn_ValidRegion *p, int tab);
// Gitsn_ValidRegion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GeographicalPath_descriptionPresent
typedef enum Gitsn_GeographicalPath_descriptionPresent
{
	Gitsn_GeographicalPath_descriptionPresent_path,
	Gitsn_GeographicalPath_descriptionPresent_geometry,
	Gitsn_GeographicalPath_descriptionPresent_oldRegion,
	Gitsn_GeographicalPath_descriptionPresent_max
} Gitsn_GeographicalPath_descriptionPresent;

DZ1_CPPLINK str_t Gitsn_GeographicalPath_descriptionPresentStrA(Gitsn_GeographicalPath_descriptionPresent v);
DZ1_CPPLINK Gitsn_GeographicalPath_descriptionPresent Gitsn_GeographicalPath_descriptionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_GeographicalPath_descriptionPresentStrW(Gitsn_GeographicalPath_descriptionPresent v);
DZ1_CPPLINK Gitsn_GeographicalPath_descriptionPresent Gitsn_GeographicalPath_descriptionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_GeographicalPath_descriptionPresentStr Gitsn_GeographicalPath_descriptionPresentStrW
#define Gitsn_GeographicalPath_descriptionPresentFromStr Gitsn_GeographicalPath_descriptionPresentFromStrW
#else // UNICODE
#define Gitsn_GeographicalPath_descriptionPresentStr Gitsn_GeographicalPath_descriptionPresentStrA
#define Gitsn_GeographicalPath_descriptionPresentFromStr Gitsn_GeographicalPath_descriptionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_GeographicalPath_descriptionPresentStr Gitsn_GeographicalPath_descriptionPresentStrA
#define Gitsn_GeographicalPath_descriptionPresentFromStr Gitsn_GeographicalPath_descriptionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GeographicalPath_descriptionPresent *Gitsn_GeographicalPath_descriptionPresent_new(Gitsn_GeographicalPath_descriptionPresent *src, Dz1Error *err);
static __inline__ Gitsn_GeographicalPath_descriptionPresent *Gitsn_GeographicalPath_descriptionPresent_gen(Dz1Error *err) { Gitsn_GeographicalPath_descriptionPresent v = Gitsn_GeographicalPath_descriptionPresent_max; return Gitsn_GeographicalPath_descriptionPresent_new(&v, err); }
#define Gitsn_GeographicalPath_descriptionPresent_clone             Gitsn_GeographicalPath_descriptionPresent_new
static __inline__ void Gitsn_GeographicalPath_descriptionPresent_del(Gitsn_GeographicalPath_descriptionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_GeographicalPath_descriptionPresent_delAndSetNull(void *ptr)
{
	Gitsn_GeographicalPath_descriptionPresent **p = (Gitsn_GeographicalPath_descriptionPresent **)ptr;
	if (p != NULL) { Gitsn_GeographicalPath_descriptionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeographicalPath_descriptionPresent_dump(Gitsn_GeographicalPath_descriptionPresent *v, int tab);
// Gitsn_GeographicalPath_descriptionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GeographicalPath_description
typedef struct Gitsn_GeographicalPath_description
{
	Gitsn_GeographicalPath_descriptionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_OffsetSystem				*path;
		Gitsn_GeometricProjection		*geometry;
		Gitsn_ValidRegion				*oldRegion;
	} x;
} Gitsn_GeographicalPath_description;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_GeographicalPath_description *Gitsn_GeographicalPath_description_new(Gitsn_GeographicalPath_descriptionPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_GeographicalPath_description *Gitsn_GeographicalPath_description_gen(Dz1Error *err) { return Gitsn_GeographicalPath_description_new(Gitsn_GeographicalPath_descriptionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_GeographicalPath_description_copy(Gitsn_GeographicalPath_description *dst, Gitsn_GeographicalPath_description *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GeographicalPath_description *Gitsn_GeographicalPath_description_clone(Gitsn_GeographicalPath_description *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeographicalPath_description_purge(Gitsn_GeographicalPath_description *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeographicalPath_description_del(Gitsn_GeographicalPath_description *p);
static __inline__ void Gitsn_GeographicalPath_description_delAndSetNull(void *ptr)
{
	Gitsn_GeographicalPath_description **p = (Gitsn_GeographicalPath_description **)ptr;
	if (p != NULL) { Gitsn_GeographicalPath_description_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeographicalPath_description_dump(Gitsn_GeographicalPath_description *p, int tab);
// Gitsn_GeographicalPath_description
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GeographicalPath
typedef struct Gitsn_GeographicalPath
{
	Gitsn_DescriptiveName					 name;
	Gitsn_RoadSegmentReferenceID			*id;
	Gitsn_Position3D						*anchor;
	Gitsn_LaneWidth							 laneWidth;
	Gitsn_DirectionOfUse					 directionality;
	bool_t									 closedPath;
	Gitsn_HeadingSlice						*direction;
	Gitsn_GeographicalPath_description		*description;
} Gitsn_GeographicalPath;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_GeographicalPath *Gitsn_GeographicalPath_new(Dz1Error *err);
static __inline__ Gitsn_GeographicalPath *Gitsn_GeographicalPath_gen(Dz1Error *err) { return Gitsn_GeographicalPath_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_GeographicalPath_copy(Gitsn_GeographicalPath *dst, Gitsn_GeographicalPath *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GeographicalPath *Gitsn_GeographicalPath_clone(Gitsn_GeographicalPath *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeographicalPath_purge(Gitsn_GeographicalPath *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeographicalPath_del(Gitsn_GeographicalPath *p);
static __inline__ void Gitsn_GeographicalPath_delAndSetNull(void *ptr)
{
	Gitsn_GeographicalPath **p = (Gitsn_GeographicalPath **)ptr;
	if (p) { Gitsn_GeographicalPath_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GeographicalPath_dump(Gitsn_GeographicalPath *p, int tab);
// Gitsn_GeographicalPath
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame_regions
typedef struct Gitsn_TravelerDataFrame_regions
{
	void *storage;
	unsigned int (*count)(struct Gitsn_TravelerDataFrame_regions *p);
	Dz1Error (*travel)(struct Gitsn_TravelerDataFrame_regions *p, Dz1Error (*func)(void *ptr, Gitsn_GeographicalPath *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_TravelerDataFrame_regions *p, Dz1Error (*func)(void *ptr, Gitsn_GeographicalPath *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_TravelerDataFrame_regions *p, Dz1Error (*func)(void *ptr, Gitsn_GeographicalPath *entry), void *ptr);
	Gitsn_GeographicalPath **(*get_array)(struct Gitsn_TravelerDataFrame_regions *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_TravelerDataFrame_regions *p, Gitsn_GeographicalPath *data);
	Gitsn_GeographicalPath *(*extract)(struct Gitsn_TravelerDataFrame_regions *p, Gitsn_GeographicalPath *ptr);
	Gitsn_GeographicalPath *(*getHead)(struct Gitsn_TravelerDataFrame_regions *p);
} Gitsn_TravelerDataFrame_regions;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame_regions *Gitsn_TravelerDataFrame_regions_new(Dz1Error *err);
static __inline__ Gitsn_TravelerDataFrame_regions *Gitsn_TravelerDataFrame_regions_gen(Dz1Error *err) { return Gitsn_TravelerDataFrame_regions_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame_regions *Gitsn_TravelerDataFrame_regions_clone(Gitsn_TravelerDataFrame_regions *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_regions_purge(Gitsn_TravelerDataFrame_regions *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_regions_del(Gitsn_TravelerDataFrame_regions *p);
static __inline__ void Gitsn_TravelerDataFrame_regions_delAndSetNull(void *ptr)
{
	Gitsn_TravelerDataFrame_regions **p = (Gitsn_TravelerDataFrame_regions **)ptr;
	if (p != NULL) { Gitsn_TravelerDataFrame_regions_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_regions_dump(Gitsn_TravelerDataFrame_regions *p, int tab);

// Gitsn_TravelerDataFrame_regions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIScodesAndText_element_itemPresent
typedef enum Gitsn_ITIScodesAndText_element_itemPresent
{
	Gitsn_ITIScodesAndText_element_itemPresent_itis,
	Gitsn_ITIScodesAndText_element_itemPresent_text,
	Gitsn_ITIScodesAndText_element_itemPresent_max
} Gitsn_ITIScodesAndText_element_itemPresent;

DZ1_CPPLINK str_t Gitsn_ITIScodesAndText_element_itemPresentStrA(Gitsn_ITIScodesAndText_element_itemPresent v);
DZ1_CPPLINK Gitsn_ITIScodesAndText_element_itemPresent Gitsn_ITIScodesAndText_element_itemPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ITIScodesAndText_element_itemPresentStrW(Gitsn_ITIScodesAndText_element_itemPresent v);
DZ1_CPPLINK Gitsn_ITIScodesAndText_element_itemPresent Gitsn_ITIScodesAndText_element_itemPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ITIScodesAndText_element_itemPresentStr Gitsn_ITIScodesAndText_element_itemPresentStrW
#define Gitsn_ITIScodesAndText_element_itemPresentFromStr Gitsn_ITIScodesAndText_element_itemPresentFromStrW
#else // UNICODE
#define Gitsn_ITIScodesAndText_element_itemPresentStr Gitsn_ITIScodesAndText_element_itemPresentStrA
#define Gitsn_ITIScodesAndText_element_itemPresentFromStr Gitsn_ITIScodesAndText_element_itemPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ITIScodesAndText_element_itemPresentStr Gitsn_ITIScodesAndText_element_itemPresentStrA
#define Gitsn_ITIScodesAndText_element_itemPresentFromStr Gitsn_ITIScodesAndText_element_itemPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ITIScodesAndText_element_itemPresent *Gitsn_ITIScodesAndText_element_itemPresent_new(Gitsn_ITIScodesAndText_element_itemPresent *src, Dz1Error *err);
static __inline__ Gitsn_ITIScodesAndText_element_itemPresent *Gitsn_ITIScodesAndText_element_itemPresent_gen(Dz1Error *err) { Gitsn_ITIScodesAndText_element_itemPresent v = Gitsn_ITIScodesAndText_element_itemPresent_max; return Gitsn_ITIScodesAndText_element_itemPresent_new(&v, err); }
#define Gitsn_ITIScodesAndText_element_itemPresent_clone             Gitsn_ITIScodesAndText_element_itemPresent_new
static __inline__ void Gitsn_ITIScodesAndText_element_itemPresent_del(Gitsn_ITIScodesAndText_element_itemPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ITIScodesAndText_element_itemPresent_delAndSetNull(void *ptr)
{
	Gitsn_ITIScodesAndText_element_itemPresent **p = (Gitsn_ITIScodesAndText_element_itemPresent **)ptr;
	if (p != NULL) { Gitsn_ITIScodesAndText_element_itemPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_element_itemPresent_dump(Gitsn_ITIScodesAndText_element_itemPresent *v, int tab);
// Gitsn_ITIScodesAndText_element_itemPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIScodesAndText_element_item
typedef struct Gitsn_ITIScodesAndText_element_item
{
	Gitsn_ITIScodesAndText_element_itemPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_ITIScodes		itis;
		Gitsn_ITIStext		text;
	} x;
} Gitsn_ITIScodesAndText_element_item;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ITIScodesAndText_element_item *Gitsn_ITIScodesAndText_element_item_new(Gitsn_ITIScodesAndText_element_itemPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_ITIScodesAndText_element_item *Gitsn_ITIScodesAndText_element_item_gen(Dz1Error *err) { return Gitsn_ITIScodesAndText_element_item_new(Gitsn_ITIScodesAndText_element_itemPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_ITIScodesAndText_element_item_copy(Gitsn_ITIScodesAndText_element_item *dst, Gitsn_ITIScodesAndText_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ITIScodesAndText_element_item *Gitsn_ITIScodesAndText_element_item_clone(Gitsn_ITIScodesAndText_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_element_item_purge(Gitsn_ITIScodesAndText_element_item *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_element_item_del(Gitsn_ITIScodesAndText_element_item *p);
static __inline__ void Gitsn_ITIScodesAndText_element_item_delAndSetNull(void *ptr)
{
	Gitsn_ITIScodesAndText_element_item **p = (Gitsn_ITIScodesAndText_element_item **)ptr;
	if (p != NULL) { Gitsn_ITIScodesAndText_element_item_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_element_item_dump(Gitsn_ITIScodesAndText_element_item *p, int tab);
// Gitsn_ITIScodesAndText_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIScodesAndText_element
typedef struct Gitsn_ITIScodesAndText_element
{
	Gitsn_ITIScodesAndText_element_item		*item;
} Gitsn_ITIScodesAndText_element;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ITIScodesAndText_element *Gitsn_ITIScodesAndText_element_new(Gitsn_ITIScodesAndText_element_item *item, Dz1Error *err);
static __inline__ Gitsn_ITIScodesAndText_element *Gitsn_ITIScodesAndText_element_gen(Dz1Error *err) { return Gitsn_ITIScodesAndText_element_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ITIScodesAndText_element_copy(Gitsn_ITIScodesAndText_element *dst, Gitsn_ITIScodesAndText_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ITIScodesAndText_element *Gitsn_ITIScodesAndText_element_clone(Gitsn_ITIScodesAndText_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_element_purge(Gitsn_ITIScodesAndText_element *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_element_del(Gitsn_ITIScodesAndText_element *p);
static __inline__ void Gitsn_ITIScodesAndText_element_delAndSetNull(void *ptr)
{
	Gitsn_ITIScodesAndText_element **p = (Gitsn_ITIScodesAndText_element **)ptr;
	if (p) { Gitsn_ITIScodesAndText_element_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_element_dump(Gitsn_ITIScodesAndText_element *p, int tab);
// Gitsn_ITIScodesAndText_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIScodesAndText
typedef struct Gitsn_ITIScodesAndText
{
	void *storage;
	unsigned int (*count)(struct Gitsn_ITIScodesAndText *p);
	Dz1Error (*travel)(struct Gitsn_ITIScodesAndText *p, Dz1Error (*func)(void *ptr, Gitsn_ITIScodesAndText_element *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_ITIScodesAndText *p, Dz1Error (*func)(void *ptr, Gitsn_ITIScodesAndText_element *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_ITIScodesAndText *p, Dz1Error (*func)(void *ptr, Gitsn_ITIScodesAndText_element *entry), void *ptr);
	Gitsn_ITIScodesAndText_element **(*get_array)(struct Gitsn_ITIScodesAndText *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_ITIScodesAndText *p, Gitsn_ITIScodesAndText_element *data);
	Gitsn_ITIScodesAndText_element *(*extract)(struct Gitsn_ITIScodesAndText *p, Gitsn_ITIScodesAndText_element *ptr);
	Gitsn_ITIScodesAndText_element *(*getHead)(struct Gitsn_ITIScodesAndText *p);
} Gitsn_ITIScodesAndText;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ITIScodesAndText *Gitsn_ITIScodesAndText_new(Dz1Error *err);
static __inline__ Gitsn_ITIScodesAndText *Gitsn_ITIScodesAndText_gen(Dz1Error *err) { return Gitsn_ITIScodesAndText_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ITIScodesAndText *Gitsn_ITIScodesAndText_clone(Gitsn_ITIScodesAndText *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_purge(Gitsn_ITIScodesAndText *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_del(Gitsn_ITIScodesAndText *p);
static __inline__ void Gitsn_ITIScodesAndText_delAndSetNull(void *ptr)
{
	Gitsn_ITIScodesAndText **p = (Gitsn_ITIScodesAndText **)ptr;
	if (p != NULL) { Gitsn_ITIScodesAndText_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ITIScodesAndText_dump(Gitsn_ITIScodesAndText *p, int tab);

// Gitsn_ITIScodesAndText
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WorkZone_element_itemPresent
typedef enum Gitsn_WorkZone_element_itemPresent
{
	Gitsn_WorkZone_element_itemPresent_itis,
	Gitsn_WorkZone_element_itemPresent_text,
	Gitsn_WorkZone_element_itemPresent_max
} Gitsn_WorkZone_element_itemPresent;

DZ1_CPPLINK str_t Gitsn_WorkZone_element_itemPresentStrA(Gitsn_WorkZone_element_itemPresent v);
DZ1_CPPLINK Gitsn_WorkZone_element_itemPresent Gitsn_WorkZone_element_itemPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_WorkZone_element_itemPresentStrW(Gitsn_WorkZone_element_itemPresent v);
DZ1_CPPLINK Gitsn_WorkZone_element_itemPresent Gitsn_WorkZone_element_itemPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_WorkZone_element_itemPresentStr Gitsn_WorkZone_element_itemPresentStrW
#define Gitsn_WorkZone_element_itemPresentFromStr Gitsn_WorkZone_element_itemPresentFromStrW
#else // UNICODE
#define Gitsn_WorkZone_element_itemPresentStr Gitsn_WorkZone_element_itemPresentStrA
#define Gitsn_WorkZone_element_itemPresentFromStr Gitsn_WorkZone_element_itemPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_WorkZone_element_itemPresentStr Gitsn_WorkZone_element_itemPresentStrA
#define Gitsn_WorkZone_element_itemPresentFromStr Gitsn_WorkZone_element_itemPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_WorkZone_element_itemPresent *Gitsn_WorkZone_element_itemPresent_new(Gitsn_WorkZone_element_itemPresent *src, Dz1Error *err);
static __inline__ Gitsn_WorkZone_element_itemPresent *Gitsn_WorkZone_element_itemPresent_gen(Dz1Error *err) { Gitsn_WorkZone_element_itemPresent v = Gitsn_WorkZone_element_itemPresent_max; return Gitsn_WorkZone_element_itemPresent_new(&v, err); }
#define Gitsn_WorkZone_element_itemPresent_clone             Gitsn_WorkZone_element_itemPresent_new
static __inline__ void Gitsn_WorkZone_element_itemPresent_del(Gitsn_WorkZone_element_itemPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_WorkZone_element_itemPresent_delAndSetNull(void *ptr)
{
	Gitsn_WorkZone_element_itemPresent **p = (Gitsn_WorkZone_element_itemPresent **)ptr;
	if (p != NULL) { Gitsn_WorkZone_element_itemPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_element_itemPresent_dump(Gitsn_WorkZone_element_itemPresent *v, int tab);
// Gitsn_WorkZone_element_itemPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WorkZone_element_item
typedef struct Gitsn_WorkZone_element_item
{
	Gitsn_WorkZone_element_itemPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_ITIScodes		itis;
		Gitsn_ITIStext		text;
	} x;
} Gitsn_WorkZone_element_item;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_WorkZone_element_item *Gitsn_WorkZone_element_item_new(Gitsn_WorkZone_element_itemPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_WorkZone_element_item *Gitsn_WorkZone_element_item_gen(Dz1Error *err) { return Gitsn_WorkZone_element_item_new(Gitsn_WorkZone_element_itemPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_WorkZone_element_item_copy(Gitsn_WorkZone_element_item *dst, Gitsn_WorkZone_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_WorkZone_element_item *Gitsn_WorkZone_element_item_clone(Gitsn_WorkZone_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_element_item_purge(Gitsn_WorkZone_element_item *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_element_item_del(Gitsn_WorkZone_element_item *p);
static __inline__ void Gitsn_WorkZone_element_item_delAndSetNull(void *ptr)
{
	Gitsn_WorkZone_element_item **p = (Gitsn_WorkZone_element_item **)ptr;
	if (p != NULL) { Gitsn_WorkZone_element_item_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_element_item_dump(Gitsn_WorkZone_element_item *p, int tab);
// Gitsn_WorkZone_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WorkZone_element
typedef struct Gitsn_WorkZone_element
{
	Gitsn_WorkZone_element_item		*item;
} Gitsn_WorkZone_element;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_WorkZone_element *Gitsn_WorkZone_element_new(Gitsn_WorkZone_element_item *item, Dz1Error *err);
static __inline__ Gitsn_WorkZone_element *Gitsn_WorkZone_element_gen(Dz1Error *err) { return Gitsn_WorkZone_element_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_WorkZone_element_copy(Gitsn_WorkZone_element *dst, Gitsn_WorkZone_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_WorkZone_element *Gitsn_WorkZone_element_clone(Gitsn_WorkZone_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_element_purge(Gitsn_WorkZone_element *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_element_del(Gitsn_WorkZone_element *p);
static __inline__ void Gitsn_WorkZone_element_delAndSetNull(void *ptr)
{
	Gitsn_WorkZone_element **p = (Gitsn_WorkZone_element **)ptr;
	if (p) { Gitsn_WorkZone_element_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_element_dump(Gitsn_WorkZone_element *p, int tab);
// Gitsn_WorkZone_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WorkZone
typedef struct Gitsn_WorkZone
{
	void *storage;
	unsigned int (*count)(struct Gitsn_WorkZone *p);
	Dz1Error (*travel)(struct Gitsn_WorkZone *p, Dz1Error (*func)(void *ptr, Gitsn_WorkZone_element *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_WorkZone *p, Dz1Error (*func)(void *ptr, Gitsn_WorkZone_element *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_WorkZone *p, Dz1Error (*func)(void *ptr, Gitsn_WorkZone_element *entry), void *ptr);
	Gitsn_WorkZone_element **(*get_array)(struct Gitsn_WorkZone *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_WorkZone *p, Gitsn_WorkZone_element *data);
	Gitsn_WorkZone_element *(*extract)(struct Gitsn_WorkZone *p, Gitsn_WorkZone_element *ptr);
	Gitsn_WorkZone_element *(*getHead)(struct Gitsn_WorkZone *p);
} Gitsn_WorkZone;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_WorkZone *Gitsn_WorkZone_new(Dz1Error *err);
static __inline__ Gitsn_WorkZone *Gitsn_WorkZone_gen(Dz1Error *err) { return Gitsn_WorkZone_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_WorkZone *Gitsn_WorkZone_clone(Gitsn_WorkZone *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_purge(Gitsn_WorkZone *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_del(Gitsn_WorkZone *p);
static __inline__ void Gitsn_WorkZone_delAndSetNull(void *ptr)
{
	Gitsn_WorkZone **p = (Gitsn_WorkZone **)ptr;
	if (p != NULL) { Gitsn_WorkZone_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_WorkZone_dump(Gitsn_WorkZone *p, int tab);

// Gitsn_WorkZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericSignage_element_itemPresent
typedef enum Gitsn_GenericSignage_element_itemPresent
{
	Gitsn_GenericSignage_element_itemPresent_itis,
	Gitsn_GenericSignage_element_itemPresent_text,
	Gitsn_GenericSignage_element_itemPresent_max
} Gitsn_GenericSignage_element_itemPresent;

DZ1_CPPLINK str_t Gitsn_GenericSignage_element_itemPresentStrA(Gitsn_GenericSignage_element_itemPresent v);
DZ1_CPPLINK Gitsn_GenericSignage_element_itemPresent Gitsn_GenericSignage_element_itemPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_GenericSignage_element_itemPresentStrW(Gitsn_GenericSignage_element_itemPresent v);
DZ1_CPPLINK Gitsn_GenericSignage_element_itemPresent Gitsn_GenericSignage_element_itemPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_GenericSignage_element_itemPresentStr Gitsn_GenericSignage_element_itemPresentStrW
#define Gitsn_GenericSignage_element_itemPresentFromStr Gitsn_GenericSignage_element_itemPresentFromStrW
#else // UNICODE
#define Gitsn_GenericSignage_element_itemPresentStr Gitsn_GenericSignage_element_itemPresentStrA
#define Gitsn_GenericSignage_element_itemPresentFromStr Gitsn_GenericSignage_element_itemPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_GenericSignage_element_itemPresentStr Gitsn_GenericSignage_element_itemPresentStrA
#define Gitsn_GenericSignage_element_itemPresentFromStr Gitsn_GenericSignage_element_itemPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericSignage_element_itemPresent *Gitsn_GenericSignage_element_itemPresent_new(Gitsn_GenericSignage_element_itemPresent *src, Dz1Error *err);
static __inline__ Gitsn_GenericSignage_element_itemPresent *Gitsn_GenericSignage_element_itemPresent_gen(Dz1Error *err) { Gitsn_GenericSignage_element_itemPresent v = Gitsn_GenericSignage_element_itemPresent_max; return Gitsn_GenericSignage_element_itemPresent_new(&v, err); }
#define Gitsn_GenericSignage_element_itemPresent_clone             Gitsn_GenericSignage_element_itemPresent_new
static __inline__ void Gitsn_GenericSignage_element_itemPresent_del(Gitsn_GenericSignage_element_itemPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_GenericSignage_element_itemPresent_delAndSetNull(void *ptr)
{
	Gitsn_GenericSignage_element_itemPresent **p = (Gitsn_GenericSignage_element_itemPresent **)ptr;
	if (p != NULL) { Gitsn_GenericSignage_element_itemPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_element_itemPresent_dump(Gitsn_GenericSignage_element_itemPresent *v, int tab);
// Gitsn_GenericSignage_element_itemPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericSignage_element_item
typedef struct Gitsn_GenericSignage_element_item
{
	Gitsn_GenericSignage_element_itemPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_ITIScodes		itis;
		Gitsn_ITIStext		text;
	} x;
} Gitsn_GenericSignage_element_item;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericSignage_element_item *Gitsn_GenericSignage_element_item_new(Gitsn_GenericSignage_element_itemPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_GenericSignage_element_item *Gitsn_GenericSignage_element_item_gen(Dz1Error *err) { return Gitsn_GenericSignage_element_item_new(Gitsn_GenericSignage_element_itemPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_GenericSignage_element_item_copy(Gitsn_GenericSignage_element_item *dst, Gitsn_GenericSignage_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericSignage_element_item *Gitsn_GenericSignage_element_item_clone(Gitsn_GenericSignage_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_element_item_purge(Gitsn_GenericSignage_element_item *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_element_item_del(Gitsn_GenericSignage_element_item *p);
static __inline__ void Gitsn_GenericSignage_element_item_delAndSetNull(void *ptr)
{
	Gitsn_GenericSignage_element_item **p = (Gitsn_GenericSignage_element_item **)ptr;
	if (p != NULL) { Gitsn_GenericSignage_element_item_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_element_item_dump(Gitsn_GenericSignage_element_item *p, int tab);
// Gitsn_GenericSignage_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericSignage_element
typedef struct Gitsn_GenericSignage_element
{
	Gitsn_GenericSignage_element_item		*item;
} Gitsn_GenericSignage_element;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericSignage_element *Gitsn_GenericSignage_element_new(Gitsn_GenericSignage_element_item *item, Dz1Error *err);
static __inline__ Gitsn_GenericSignage_element *Gitsn_GenericSignage_element_gen(Dz1Error *err) { return Gitsn_GenericSignage_element_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_GenericSignage_element_copy(Gitsn_GenericSignage_element *dst, Gitsn_GenericSignage_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericSignage_element *Gitsn_GenericSignage_element_clone(Gitsn_GenericSignage_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_element_purge(Gitsn_GenericSignage_element *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_element_del(Gitsn_GenericSignage_element *p);
static __inline__ void Gitsn_GenericSignage_element_delAndSetNull(void *ptr)
{
	Gitsn_GenericSignage_element **p = (Gitsn_GenericSignage_element **)ptr;
	if (p) { Gitsn_GenericSignage_element_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_element_dump(Gitsn_GenericSignage_element *p, int tab);
// Gitsn_GenericSignage_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericSignage
typedef struct Gitsn_GenericSignage
{
	void *storage;
	unsigned int (*count)(struct Gitsn_GenericSignage *p);
	Dz1Error (*travel)(struct Gitsn_GenericSignage *p, Dz1Error (*func)(void *ptr, Gitsn_GenericSignage_element *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_GenericSignage *p, Dz1Error (*func)(void *ptr, Gitsn_GenericSignage_element *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_GenericSignage *p, Dz1Error (*func)(void *ptr, Gitsn_GenericSignage_element *entry), void *ptr);
	Gitsn_GenericSignage_element **(*get_array)(struct Gitsn_GenericSignage *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_GenericSignage *p, Gitsn_GenericSignage_element *data);
	Gitsn_GenericSignage_element *(*extract)(struct Gitsn_GenericSignage *p, Gitsn_GenericSignage_element *ptr);
	Gitsn_GenericSignage_element *(*getHead)(struct Gitsn_GenericSignage *p);
} Gitsn_GenericSignage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericSignage *Gitsn_GenericSignage_new(Dz1Error *err);
static __inline__ Gitsn_GenericSignage *Gitsn_GenericSignage_gen(Dz1Error *err) { return Gitsn_GenericSignage_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_GenericSignage *Gitsn_GenericSignage_clone(Gitsn_GenericSignage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_purge(Gitsn_GenericSignage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_del(Gitsn_GenericSignage *p);
static __inline__ void Gitsn_GenericSignage_delAndSetNull(void *ptr)
{
	Gitsn_GenericSignage **p = (Gitsn_GenericSignage **)ptr;
	if (p != NULL) { Gitsn_GenericSignage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_GenericSignage_dump(Gitsn_GenericSignage *p, int tab);

// Gitsn_GenericSignage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimit_element_itemPresent
typedef enum Gitsn_SpeedLimit_element_itemPresent
{
	Gitsn_SpeedLimit_element_itemPresent_itis,
	Gitsn_SpeedLimit_element_itemPresent_text,
	Gitsn_SpeedLimit_element_itemPresent_max
} Gitsn_SpeedLimit_element_itemPresent;

DZ1_CPPLINK str_t Gitsn_SpeedLimit_element_itemPresentStrA(Gitsn_SpeedLimit_element_itemPresent v);
DZ1_CPPLINK Gitsn_SpeedLimit_element_itemPresent Gitsn_SpeedLimit_element_itemPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SpeedLimit_element_itemPresentStrW(Gitsn_SpeedLimit_element_itemPresent v);
DZ1_CPPLINK Gitsn_SpeedLimit_element_itemPresent Gitsn_SpeedLimit_element_itemPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SpeedLimit_element_itemPresentStr Gitsn_SpeedLimit_element_itemPresentStrW
#define Gitsn_SpeedLimit_element_itemPresentFromStr Gitsn_SpeedLimit_element_itemPresentFromStrW
#else // UNICODE
#define Gitsn_SpeedLimit_element_itemPresentStr Gitsn_SpeedLimit_element_itemPresentStrA
#define Gitsn_SpeedLimit_element_itemPresentFromStr Gitsn_SpeedLimit_element_itemPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SpeedLimit_element_itemPresentStr Gitsn_SpeedLimit_element_itemPresentStrA
#define Gitsn_SpeedLimit_element_itemPresentFromStr Gitsn_SpeedLimit_element_itemPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimit_element_itemPresent *Gitsn_SpeedLimit_element_itemPresent_new(Gitsn_SpeedLimit_element_itemPresent *src, Dz1Error *err);
static __inline__ Gitsn_SpeedLimit_element_itemPresent *Gitsn_SpeedLimit_element_itemPresent_gen(Dz1Error *err) { Gitsn_SpeedLimit_element_itemPresent v = Gitsn_SpeedLimit_element_itemPresent_max; return Gitsn_SpeedLimit_element_itemPresent_new(&v, err); }
#define Gitsn_SpeedLimit_element_itemPresent_clone             Gitsn_SpeedLimit_element_itemPresent_new
static __inline__ void Gitsn_SpeedLimit_element_itemPresent_del(Gitsn_SpeedLimit_element_itemPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SpeedLimit_element_itemPresent_delAndSetNull(void *ptr)
{
	Gitsn_SpeedLimit_element_itemPresent **p = (Gitsn_SpeedLimit_element_itemPresent **)ptr;
	if (p != NULL) { Gitsn_SpeedLimit_element_itemPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_element_itemPresent_dump(Gitsn_SpeedLimit_element_itemPresent *v, int tab);
// Gitsn_SpeedLimit_element_itemPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimit_element_item
typedef struct Gitsn_SpeedLimit_element_item
{
	Gitsn_SpeedLimit_element_itemPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_ITIScodes		itis;
		Gitsn_ITIStext		text;
	} x;
} Gitsn_SpeedLimit_element_item;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimit_element_item *Gitsn_SpeedLimit_element_item_new(Gitsn_SpeedLimit_element_itemPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_SpeedLimit_element_item *Gitsn_SpeedLimit_element_item_gen(Dz1Error *err) { return Gitsn_SpeedLimit_element_item_new(Gitsn_SpeedLimit_element_itemPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_SpeedLimit_element_item_copy(Gitsn_SpeedLimit_element_item *dst, Gitsn_SpeedLimit_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimit_element_item *Gitsn_SpeedLimit_element_item_clone(Gitsn_SpeedLimit_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_element_item_purge(Gitsn_SpeedLimit_element_item *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_element_item_del(Gitsn_SpeedLimit_element_item *p);
static __inline__ void Gitsn_SpeedLimit_element_item_delAndSetNull(void *ptr)
{
	Gitsn_SpeedLimit_element_item **p = (Gitsn_SpeedLimit_element_item **)ptr;
	if (p != NULL) { Gitsn_SpeedLimit_element_item_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_element_item_dump(Gitsn_SpeedLimit_element_item *p, int tab);
// Gitsn_SpeedLimit_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimit_element
typedef struct Gitsn_SpeedLimit_element
{
	Gitsn_SpeedLimit_element_item		*item;
} Gitsn_SpeedLimit_element;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimit_element *Gitsn_SpeedLimit_element_new(Gitsn_SpeedLimit_element_item *item, Dz1Error *err);
static __inline__ Gitsn_SpeedLimit_element *Gitsn_SpeedLimit_element_gen(Dz1Error *err) { return Gitsn_SpeedLimit_element_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SpeedLimit_element_copy(Gitsn_SpeedLimit_element *dst, Gitsn_SpeedLimit_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimit_element *Gitsn_SpeedLimit_element_clone(Gitsn_SpeedLimit_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_element_purge(Gitsn_SpeedLimit_element *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_element_del(Gitsn_SpeedLimit_element *p);
static __inline__ void Gitsn_SpeedLimit_element_delAndSetNull(void *ptr)
{
	Gitsn_SpeedLimit_element **p = (Gitsn_SpeedLimit_element **)ptr;
	if (p) { Gitsn_SpeedLimit_element_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_element_dump(Gitsn_SpeedLimit_element *p, int tab);
// Gitsn_SpeedLimit_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimit
typedef struct Gitsn_SpeedLimit
{
	void *storage;
	unsigned int (*count)(struct Gitsn_SpeedLimit *p);
	Dz1Error (*travel)(struct Gitsn_SpeedLimit *p, Dz1Error (*func)(void *ptr, Gitsn_SpeedLimit_element *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_SpeedLimit *p, Dz1Error (*func)(void *ptr, Gitsn_SpeedLimit_element *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_SpeedLimit *p, Dz1Error (*func)(void *ptr, Gitsn_SpeedLimit_element *entry), void *ptr);
	Gitsn_SpeedLimit_element **(*get_array)(struct Gitsn_SpeedLimit *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_SpeedLimit *p, Gitsn_SpeedLimit_element *data);
	Gitsn_SpeedLimit_element *(*extract)(struct Gitsn_SpeedLimit *p, Gitsn_SpeedLimit_element *ptr);
	Gitsn_SpeedLimit_element *(*getHead)(struct Gitsn_SpeedLimit *p);
} Gitsn_SpeedLimit;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimit *Gitsn_SpeedLimit_new(Dz1Error *err);
static __inline__ Gitsn_SpeedLimit *Gitsn_SpeedLimit_gen(Dz1Error *err) { return Gitsn_SpeedLimit_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SpeedLimit *Gitsn_SpeedLimit_clone(Gitsn_SpeedLimit *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_purge(Gitsn_SpeedLimit *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_del(Gitsn_SpeedLimit *p);
static __inline__ void Gitsn_SpeedLimit_delAndSetNull(void *ptr)
{
	Gitsn_SpeedLimit **p = (Gitsn_SpeedLimit **)ptr;
	if (p != NULL) { Gitsn_SpeedLimit_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SpeedLimit_dump(Gitsn_SpeedLimit *p, int tab);

// Gitsn_SpeedLimit
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ExitService_element_itemPresent
typedef enum Gitsn_ExitService_element_itemPresent
{
	Gitsn_ExitService_element_itemPresent_itis,
	Gitsn_ExitService_element_itemPresent_text,
	Gitsn_ExitService_element_itemPresent_max
} Gitsn_ExitService_element_itemPresent;

DZ1_CPPLINK str_t Gitsn_ExitService_element_itemPresentStrA(Gitsn_ExitService_element_itemPresent v);
DZ1_CPPLINK Gitsn_ExitService_element_itemPresent Gitsn_ExitService_element_itemPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ExitService_element_itemPresentStrW(Gitsn_ExitService_element_itemPresent v);
DZ1_CPPLINK Gitsn_ExitService_element_itemPresent Gitsn_ExitService_element_itemPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ExitService_element_itemPresentStr Gitsn_ExitService_element_itemPresentStrW
#define Gitsn_ExitService_element_itemPresentFromStr Gitsn_ExitService_element_itemPresentFromStrW
#else // UNICODE
#define Gitsn_ExitService_element_itemPresentStr Gitsn_ExitService_element_itemPresentStrA
#define Gitsn_ExitService_element_itemPresentFromStr Gitsn_ExitService_element_itemPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ExitService_element_itemPresentStr Gitsn_ExitService_element_itemPresentStrA
#define Gitsn_ExitService_element_itemPresentFromStr Gitsn_ExitService_element_itemPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ExitService_element_itemPresent *Gitsn_ExitService_element_itemPresent_new(Gitsn_ExitService_element_itemPresent *src, Dz1Error *err);
static __inline__ Gitsn_ExitService_element_itemPresent *Gitsn_ExitService_element_itemPresent_gen(Dz1Error *err) { Gitsn_ExitService_element_itemPresent v = Gitsn_ExitService_element_itemPresent_max; return Gitsn_ExitService_element_itemPresent_new(&v, err); }
#define Gitsn_ExitService_element_itemPresent_clone             Gitsn_ExitService_element_itemPresent_new
static __inline__ void Gitsn_ExitService_element_itemPresent_del(Gitsn_ExitService_element_itemPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ExitService_element_itemPresent_delAndSetNull(void *ptr)
{
	Gitsn_ExitService_element_itemPresent **p = (Gitsn_ExitService_element_itemPresent **)ptr;
	if (p != NULL) { Gitsn_ExitService_element_itemPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_element_itemPresent_dump(Gitsn_ExitService_element_itemPresent *v, int tab);
// Gitsn_ExitService_element_itemPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ExitService_element_item
typedef struct Gitsn_ExitService_element_item
{
	Gitsn_ExitService_element_itemPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_ITIScodes		itis;
		Gitsn_ITIStext		text;
	} x;
} Gitsn_ExitService_element_item;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ExitService_element_item *Gitsn_ExitService_element_item_new(Gitsn_ExitService_element_itemPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_ExitService_element_item *Gitsn_ExitService_element_item_gen(Dz1Error *err) { return Gitsn_ExitService_element_item_new(Gitsn_ExitService_element_itemPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_ExitService_element_item_copy(Gitsn_ExitService_element_item *dst, Gitsn_ExitService_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ExitService_element_item *Gitsn_ExitService_element_item_clone(Gitsn_ExitService_element_item *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_element_item_purge(Gitsn_ExitService_element_item *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_element_item_del(Gitsn_ExitService_element_item *p);
static __inline__ void Gitsn_ExitService_element_item_delAndSetNull(void *ptr)
{
	Gitsn_ExitService_element_item **p = (Gitsn_ExitService_element_item **)ptr;
	if (p != NULL) { Gitsn_ExitService_element_item_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_element_item_dump(Gitsn_ExitService_element_item *p, int tab);
// Gitsn_ExitService_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ExitService_element
typedef struct Gitsn_ExitService_element
{
	Gitsn_ExitService_element_item		*item;
} Gitsn_ExitService_element;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ExitService_element *Gitsn_ExitService_element_new(Gitsn_ExitService_element_item *item, Dz1Error *err);
static __inline__ Gitsn_ExitService_element *Gitsn_ExitService_element_gen(Dz1Error *err) { return Gitsn_ExitService_element_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ExitService_element_copy(Gitsn_ExitService_element *dst, Gitsn_ExitService_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ExitService_element *Gitsn_ExitService_element_clone(Gitsn_ExitService_element *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_element_purge(Gitsn_ExitService_element *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_element_del(Gitsn_ExitService_element *p);
static __inline__ void Gitsn_ExitService_element_delAndSetNull(void *ptr)
{
	Gitsn_ExitService_element **p = (Gitsn_ExitService_element **)ptr;
	if (p) { Gitsn_ExitService_element_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_element_dump(Gitsn_ExitService_element *p, int tab);
// Gitsn_ExitService_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ExitService
typedef struct Gitsn_ExitService
{
	void *storage;
	unsigned int (*count)(struct Gitsn_ExitService *p);
	Dz1Error (*travel)(struct Gitsn_ExitService *p, Dz1Error (*func)(void *ptr, Gitsn_ExitService_element *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_ExitService *p, Dz1Error (*func)(void *ptr, Gitsn_ExitService_element *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_ExitService *p, Dz1Error (*func)(void *ptr, Gitsn_ExitService_element *entry), void *ptr);
	Gitsn_ExitService_element **(*get_array)(struct Gitsn_ExitService *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_ExitService *p, Gitsn_ExitService_element *data);
	Gitsn_ExitService_element *(*extract)(struct Gitsn_ExitService *p, Gitsn_ExitService_element *ptr);
	Gitsn_ExitService_element *(*getHead)(struct Gitsn_ExitService *p);
} Gitsn_ExitService;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ExitService *Gitsn_ExitService_new(Dz1Error *err);
static __inline__ Gitsn_ExitService *Gitsn_ExitService_gen(Dz1Error *err) { return Gitsn_ExitService_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ExitService *Gitsn_ExitService_clone(Gitsn_ExitService *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_purge(Gitsn_ExitService *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_del(Gitsn_ExitService *p);
static __inline__ void Gitsn_ExitService_delAndSetNull(void *ptr)
{
	Gitsn_ExitService **p = (Gitsn_ExitService **)ptr;
	if (p != NULL) { Gitsn_ExitService_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ExitService_dump(Gitsn_ExitService *p, int tab);

// Gitsn_ExitService
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame_contentPresent
typedef enum Gitsn_TravelerDataFrame_contentPresent
{
	Gitsn_TravelerDataFrame_contentPresent_advisory,
	Gitsn_TravelerDataFrame_contentPresent_workZone,
	Gitsn_TravelerDataFrame_contentPresent_genericSign,
	Gitsn_TravelerDataFrame_contentPresent_speedLimit,
	Gitsn_TravelerDataFrame_contentPresent_exitService,
	Gitsn_TravelerDataFrame_contentPresent_max
} Gitsn_TravelerDataFrame_contentPresent;

DZ1_CPPLINK str_t Gitsn_TravelerDataFrame_contentPresentStrA(Gitsn_TravelerDataFrame_contentPresent v);
DZ1_CPPLINK Gitsn_TravelerDataFrame_contentPresent Gitsn_TravelerDataFrame_contentPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TravelerDataFrame_contentPresentStrW(Gitsn_TravelerDataFrame_contentPresent v);
DZ1_CPPLINK Gitsn_TravelerDataFrame_contentPresent Gitsn_TravelerDataFrame_contentPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TravelerDataFrame_contentPresentStr Gitsn_TravelerDataFrame_contentPresentStrW
#define Gitsn_TravelerDataFrame_contentPresentFromStr Gitsn_TravelerDataFrame_contentPresentFromStrW
#else // UNICODE
#define Gitsn_TravelerDataFrame_contentPresentStr Gitsn_TravelerDataFrame_contentPresentStrA
#define Gitsn_TravelerDataFrame_contentPresentFromStr Gitsn_TravelerDataFrame_contentPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TravelerDataFrame_contentPresentStr Gitsn_TravelerDataFrame_contentPresentStrA
#define Gitsn_TravelerDataFrame_contentPresentFromStr Gitsn_TravelerDataFrame_contentPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame_contentPresent *Gitsn_TravelerDataFrame_contentPresent_new(Gitsn_TravelerDataFrame_contentPresent *src, Dz1Error *err);
static __inline__ Gitsn_TravelerDataFrame_contentPresent *Gitsn_TravelerDataFrame_contentPresent_gen(Dz1Error *err) { Gitsn_TravelerDataFrame_contentPresent v = Gitsn_TravelerDataFrame_contentPresent_max; return Gitsn_TravelerDataFrame_contentPresent_new(&v, err); }
#define Gitsn_TravelerDataFrame_contentPresent_clone             Gitsn_TravelerDataFrame_contentPresent_new
static __inline__ void Gitsn_TravelerDataFrame_contentPresent_del(Gitsn_TravelerDataFrame_contentPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TravelerDataFrame_contentPresent_delAndSetNull(void *ptr)
{
	Gitsn_TravelerDataFrame_contentPresent **p = (Gitsn_TravelerDataFrame_contentPresent **)ptr;
	if (p != NULL) { Gitsn_TravelerDataFrame_contentPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_contentPresent_dump(Gitsn_TravelerDataFrame_contentPresent *v, int tab);
// Gitsn_TravelerDataFrame_contentPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame_content
typedef struct Gitsn_TravelerDataFrame_content
{
	Gitsn_TravelerDataFrame_contentPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_ITIScodesAndText		*advisory;
		Gitsn_WorkZone				*workZone;
		Gitsn_GenericSignage		*genericSign;
		Gitsn_SpeedLimit			*speedLimit;
		Gitsn_ExitService			*exitService;
	} x;
} Gitsn_TravelerDataFrame_content;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame_content *Gitsn_TravelerDataFrame_content_new(Gitsn_TravelerDataFrame_contentPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_TravelerDataFrame_content *Gitsn_TravelerDataFrame_content_gen(Dz1Error *err) { return Gitsn_TravelerDataFrame_content_new(Gitsn_TravelerDataFrame_contentPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_TravelerDataFrame_content_copy(Gitsn_TravelerDataFrame_content *dst, Gitsn_TravelerDataFrame_content *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame_content *Gitsn_TravelerDataFrame_content_clone(Gitsn_TravelerDataFrame_content *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_content_purge(Gitsn_TravelerDataFrame_content *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_content_del(Gitsn_TravelerDataFrame_content *p);
static __inline__ void Gitsn_TravelerDataFrame_content_delAndSetNull(void *ptr)
{
	Gitsn_TravelerDataFrame_content **p = (Gitsn_TravelerDataFrame_content **)ptr;
	if (p != NULL) { Gitsn_TravelerDataFrame_content_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_content_dump(Gitsn_TravelerDataFrame_content *p, int tab);
// Gitsn_TravelerDataFrame_content
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame
typedef struct Gitsn_TravelerDataFrame
{
	Gitsn_SSPindex						 notUsed;
	Gitsn_TravelerInfoType				 frameType;
	Gitsn_TravelerDataFrame_msgId		*msgId;
	Gitsn_DYear							 startYear;
	Gitsn_MinuteOfTheYear				 startTime;
	Gitsn_MinutesDuration				 durationTime;
	Gitsn_SignPriority					 priority;
	Gitsn_SSPindex						 notUsed1;
	Gitsn_TravelerDataFrame_regions		*regions;
	Gitsn_SSPindex						 notUsed2;
	Gitsn_SSPindex						 notUsed3;
	Gitsn_TravelerDataFrame_content		*content;
	Gitsn_URL_Short						 url;
} Gitsn_TravelerDataFrame;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame *Gitsn_TravelerDataFrame_new(Gitsn_SSPindex notUsed, 
																			 Gitsn_TravelerInfoType frameType, 
																			 Gitsn_TravelerDataFrame_msgId *msgId, 
																			 Gitsn_MinuteOfTheYear startTime, 
																			 Gitsn_MinutesDuration durationTime, 
																			 Gitsn_SignPriority priority, 
																			 Gitsn_SSPindex notUsed1, 
																			 Gitsn_TravelerDataFrame_regions *regions, 
																			 Gitsn_SSPindex notUsed2, 
																			 Gitsn_SSPindex notUsed3, 
																			 Gitsn_TravelerDataFrame_content *content, Dz1Error *err);
static __inline__ Gitsn_TravelerDataFrame *Gitsn_TravelerDataFrame_gen(Dz1Error *err) { return Gitsn_TravelerDataFrame_new(0, Gitsn_TravelerInfoType_max, NULL, 0, 0, 0, 0, NULL, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_TravelerDataFrame_copy(Gitsn_TravelerDataFrame *dst, Gitsn_TravelerDataFrame *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrame *Gitsn_TravelerDataFrame_clone(Gitsn_TravelerDataFrame *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_purge(Gitsn_TravelerDataFrame *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_del(Gitsn_TravelerDataFrame *p);
static __inline__ void Gitsn_TravelerDataFrame_delAndSetNull(void *ptr)
{
	Gitsn_TravelerDataFrame **p = (Gitsn_TravelerDataFrame **)ptr;
	if (p) { Gitsn_TravelerDataFrame_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrame_dump(Gitsn_TravelerDataFrame *p, int tab);
// Gitsn_TravelerDataFrame
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrameList
typedef struct Gitsn_TravelerDataFrameList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_TravelerDataFrameList *p);
	Dz1Error (*travel)(struct Gitsn_TravelerDataFrameList *p, Dz1Error (*func)(void *ptr, Gitsn_TravelerDataFrame *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_TravelerDataFrameList *p, Dz1Error (*func)(void *ptr, Gitsn_TravelerDataFrame *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_TravelerDataFrameList *p, Dz1Error (*func)(void *ptr, Gitsn_TravelerDataFrame *entry), void *ptr);
	Gitsn_TravelerDataFrame **(*get_array)(struct Gitsn_TravelerDataFrameList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_TravelerDataFrameList *p, Gitsn_TravelerDataFrame *data);
	Gitsn_TravelerDataFrame *(*extract)(struct Gitsn_TravelerDataFrameList *p, Gitsn_TravelerDataFrame *ptr);
	Gitsn_TravelerDataFrame *(*getHead)(struct Gitsn_TravelerDataFrameList *p);
} Gitsn_TravelerDataFrameList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrameList *Gitsn_TravelerDataFrameList_new(Dz1Error *err);
static __inline__ Gitsn_TravelerDataFrameList *Gitsn_TravelerDataFrameList_gen(Dz1Error *err) { return Gitsn_TravelerDataFrameList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerDataFrameList *Gitsn_TravelerDataFrameList_clone(Gitsn_TravelerDataFrameList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrameList_purge(Gitsn_TravelerDataFrameList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrameList_del(Gitsn_TravelerDataFrameList *p);
static __inline__ void Gitsn_TravelerDataFrameList_delAndSetNull(void *ptr)
{
	Gitsn_TravelerDataFrameList **p = (Gitsn_TravelerDataFrameList **)ptr;
	if (p != NULL) { Gitsn_TravelerDataFrameList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerDataFrameList_dump(Gitsn_TravelerDataFrameList *p, int tab);

// Gitsn_TravelerDataFrameList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OBJECTIDENTIFIER
typedef struct Gitsn_OBJECTIDENTIFIER
{
	u32_t		 numids;
	u32_t		*subid;
} Gitsn_OBJECTIDENTIFIER;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_OBJECTIDENTIFIER *Gitsn_OBJECTIDENTIFIER_new(u32_t numids, 
																		   u32_t *subid, Dz1Error *err);
static __inline__ Gitsn_OBJECTIDENTIFIER *Gitsn_OBJECTIDENTIFIER_gen(Dz1Error *err) { return Gitsn_OBJECTIDENTIFIER_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_OBJECTIDENTIFIER_copy(Gitsn_OBJECTIDENTIFIER *dst, Gitsn_OBJECTIDENTIFIER *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_OBJECTIDENTIFIER *Gitsn_OBJECTIDENTIFIER_clone(Gitsn_OBJECTIDENTIFIER *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OBJECTIDENTIFIER_purge(Gitsn_OBJECTIDENTIFIER *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OBJECTIDENTIFIER_del(Gitsn_OBJECTIDENTIFIER *p);
static __inline__ void Gitsn_OBJECTIDENTIFIER_delAndSetNull(void *ptr)
{
	Gitsn_OBJECTIDENTIFIER **p = (Gitsn_OBJECTIDENTIFIER **)ptr;
	if (p) { Gitsn_OBJECTIDENTIFIER_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_OBJECTIDENTIFIER_dump(Gitsn_OBJECTIDENTIFIER *p, int tab);
// Gitsn_OBJECTIDENTIFIER
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightIDPresent
typedef enum Gitsn_TrafficLightIDPresent
{
	Gitsn_TrafficLightIDPresent_id,
	Gitsn_TrafficLightIDPresent_oid,
	Gitsn_TrafficLightIDPresent_max
} Gitsn_TrafficLightIDPresent;

DZ1_CPPLINK str_t Gitsn_TrafficLightIDPresentStrA(Gitsn_TrafficLightIDPresent v);
DZ1_CPPLINK Gitsn_TrafficLightIDPresent Gitsn_TrafficLightIDPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TrafficLightIDPresentStrW(Gitsn_TrafficLightIDPresent v);
DZ1_CPPLINK Gitsn_TrafficLightIDPresent Gitsn_TrafficLightIDPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TrafficLightIDPresentStr Gitsn_TrafficLightIDPresentStrW
#define Gitsn_TrafficLightIDPresentFromStr Gitsn_TrafficLightIDPresentFromStrW
#else // UNICODE
#define Gitsn_TrafficLightIDPresentStr Gitsn_TrafficLightIDPresentStrA
#define Gitsn_TrafficLightIDPresentFromStr Gitsn_TrafficLightIDPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TrafficLightIDPresentStr Gitsn_TrafficLightIDPresentStrA
#define Gitsn_TrafficLightIDPresentFromStr Gitsn_TrafficLightIDPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightIDPresent *Gitsn_TrafficLightIDPresent_new(Gitsn_TrafficLightIDPresent *src, Dz1Error *err);
static __inline__ Gitsn_TrafficLightIDPresent *Gitsn_TrafficLightIDPresent_gen(Dz1Error *err) { Gitsn_TrafficLightIDPresent v = Gitsn_TrafficLightIDPresent_max; return Gitsn_TrafficLightIDPresent_new(&v, err); }
#define Gitsn_TrafficLightIDPresent_clone             Gitsn_TrafficLightIDPresent_new
static __inline__ void Gitsn_TrafficLightIDPresent_del(Gitsn_TrafficLightIDPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TrafficLightIDPresent_delAndSetNull(void *ptr)
{
	Gitsn_TrafficLightIDPresent **p = (Gitsn_TrafficLightIDPresent **)ptr;
	if (p != NULL) { Gitsn_TrafficLightIDPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightIDPresent_dump(Gitsn_TrafficLightIDPresent *v, int tab);
// Gitsn_TrafficLightIDPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightID
typedef struct Gitsn_TrafficLightID
{
	Gitsn_TrafficLightIDPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_INTEGER				 id;
		Gitsn_OBJECTIDENTIFIER		*oid;
	} x;
} Gitsn_TrafficLightID;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightID *Gitsn_TrafficLightID_new(Gitsn_TrafficLightIDPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_TrafficLightID *Gitsn_TrafficLightID_gen(Dz1Error *err) { return Gitsn_TrafficLightID_new(Gitsn_TrafficLightIDPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_TrafficLightID_copy(Gitsn_TrafficLightID *dst, Gitsn_TrafficLightID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightID *Gitsn_TrafficLightID_clone(Gitsn_TrafficLightID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightID_purge(Gitsn_TrafficLightID *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightID_del(Gitsn_TrafficLightID *p);
static __inline__ void Gitsn_TrafficLightID_delAndSetNull(void *ptr)
{
	Gitsn_TrafficLightID **p = (Gitsn_TrafficLightID **)ptr;
	if (p != NULL) { Gitsn_TrafficLightID_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightID_dump(Gitsn_TrafficLightID *p, int tab);
// Gitsn_TrafficLightID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightStatus
typedef struct Gitsn_TrafficLightStatus
{
	Gitsn_TrafficLightType				trafficLightType;
	Gitsn_ConsecutiveTrafficLight		consecutiveTrafficLight;
	Gitsn_TrafficLightIntervalType		trafficLightIntervalType;
	Gitsn_PedestrianCall				pedestrianCall;
	Gitsn_ActuatedInterval				actuatedinterval;
	Gitsn_PermissiveNonProtected		permissiveNonProtected;
	Gitsn_TrafficLightingStatus			lightingStatus;
	Gitsn_TimeInSecond_B8				maxIntervalLength;
	Gitsn_TimeInSecond_B8				remainingTime;
	Gitsn_TrafficLightDirectionCode		directionCode;
	Gitsn_ReservedBit					reserved;
} Gitsn_TrafficLightStatus;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightStatus *Gitsn_TrafficLightStatus_new(Gitsn_TrafficLightType trafficLightType, 
																			   Gitsn_ConsecutiveTrafficLight consecutiveTrafficLight, 
																			   Gitsn_TrafficLightIntervalType trafficLightIntervalType, 
																			   Gitsn_PedestrianCall pedestrianCall, 
																			   Gitsn_ActuatedInterval actuatedinterval, 
																			   Gitsn_PermissiveNonProtected permissiveNonProtected, 
																			   Gitsn_TrafficLightingStatus lightingStatus, 
																			   Gitsn_TimeInSecond_B8 maxIntervalLength, 
																			   Gitsn_TimeInSecond_B8 remainingTime, 
																			   Gitsn_TrafficLightDirectionCode directionCode, 
																			   Gitsn_ReservedBit reserved, Dz1Error *err);
static __inline__ Gitsn_TrafficLightStatus *Gitsn_TrafficLightStatus_gen(Dz1Error *err) { return Gitsn_TrafficLightStatus_new(Gitsn_TrafficLightType_max, Gitsn_ConsecutiveTrafficLight_max, Gitsn_TrafficLightIntervalType_max, 0, 0, Gitsn_PermissiveNonProtected_max, Gitsn_TrafficLightingStatus_max, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_TrafficLightStatus_copy(Gitsn_TrafficLightStatus *dst, Gitsn_TrafficLightStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightStatus *Gitsn_TrafficLightStatus_clone(Gitsn_TrafficLightStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatus_purge(Gitsn_TrafficLightStatus *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatus_del(Gitsn_TrafficLightStatus *p);
static __inline__ void Gitsn_TrafficLightStatus_delAndSetNull(void *ptr)
{
	Gitsn_TrafficLightStatus **p = (Gitsn_TrafficLightStatus **)ptr;
	if (p) { Gitsn_TrafficLightStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatus_dump(Gitsn_TrafficLightStatus *p, int tab);
// Gitsn_TrafficLightStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightStatusList
typedef struct Gitsn_TrafficLightStatusList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_TrafficLightStatusList *p);
	Dz1Error (*travel)(struct Gitsn_TrafficLightStatusList *p, Dz1Error (*func)(void *ptr, Gitsn_TrafficLightStatus *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_TrafficLightStatusList *p, Dz1Error (*func)(void *ptr, Gitsn_TrafficLightStatus *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_TrafficLightStatusList *p, Dz1Error (*func)(void *ptr, Gitsn_TrafficLightStatus *entry), void *ptr);
	Gitsn_TrafficLightStatus **(*get_array)(struct Gitsn_TrafficLightStatusList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_TrafficLightStatusList *p, Gitsn_TrafficLightStatus *data);
	Gitsn_TrafficLightStatus *(*extract)(struct Gitsn_TrafficLightStatusList *p, Gitsn_TrafficLightStatus *ptr);
	Gitsn_TrafficLightStatus *(*getHead)(struct Gitsn_TrafficLightStatusList *p);
} Gitsn_TrafficLightStatusList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightStatusList *Gitsn_TrafficLightStatusList_new(Dz1Error *err);
static __inline__ Gitsn_TrafficLightStatusList *Gitsn_TrafficLightStatusList_gen(Dz1Error *err) { return Gitsn_TrafficLightStatusList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightStatusList *Gitsn_TrafficLightStatusList_clone(Gitsn_TrafficLightStatusList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatusList_purge(Gitsn_TrafficLightStatusList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatusList_del(Gitsn_TrafficLightStatusList *p);
static __inline__ void Gitsn_TrafficLightStatusList_delAndSetNull(void *ptr)
{
	Gitsn_TrafficLightStatusList **p = (Gitsn_TrafficLightStatusList **)ptr;
	if (p != NULL) { Gitsn_TrafficLightStatusList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatusList_dump(Gitsn_TrafficLightStatusList *p, int tab);

// Gitsn_TrafficLightStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MapData
typedef struct Gitsn_MapData
{
	Gitsn_MinuteOfTheYear				 timeStamp;
	Gitsn_MsgCount						 msgIssueRevision;
	Gitsn_LayerType						 layerType;
	Gitsn_LayerID						 layerID;
	Gitsn_IntersectionGeometryList		*intersections;
	Gitsn_RoadSegmentList				*roadSegments;
	Gitsn_DataParameters				*dataParameters;
	Gitsn_RestrictionClassList			*restrictionList;
} Gitsn_MapData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_MapData *Gitsn_MapData_new(Gitsn_MsgCount msgIssueRevision, Dz1Error *err);
static __inline__ Gitsn_MapData *Gitsn_MapData_gen(Dz1Error *err) { return Gitsn_MapData_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_MapData_copy(Gitsn_MapData *dst, Gitsn_MapData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MapData *Gitsn_MapData_clone(Gitsn_MapData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MapData_purge(Gitsn_MapData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MapData_del(Gitsn_MapData *p);
static __inline__ void Gitsn_MapData_delAndSetNull(void *ptr)
{
	Gitsn_MapData **p = (Gitsn_MapData **)ptr;
	if (p) { Gitsn_MapData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MapData_dump(Gitsn_MapData *p, int tab);
// Gitsn_MapData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BasicSafetyMessage
typedef struct Gitsn_BasicSafetyMessage
{
	Gitsn_BSMCoreData		*coreData;
} Gitsn_BasicSafetyMessage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_BasicSafetyMessage *Gitsn_BasicSafetyMessage_new(Gitsn_BSMCoreData *coreData, Dz1Error *err);
static __inline__ Gitsn_BasicSafetyMessage *Gitsn_BasicSafetyMessage_gen(Dz1Error *err) { return Gitsn_BasicSafetyMessage_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_BasicSafetyMessage_copy(Gitsn_BasicSafetyMessage *dst, Gitsn_BasicSafetyMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_BasicSafetyMessage *Gitsn_BasicSafetyMessage_clone(Gitsn_BasicSafetyMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BasicSafetyMessage_purge(Gitsn_BasicSafetyMessage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BasicSafetyMessage_del(Gitsn_BasicSafetyMessage *p);
static __inline__ void Gitsn_BasicSafetyMessage_delAndSetNull(void *ptr)
{
	Gitsn_BasicSafetyMessage **p = (Gitsn_BasicSafetyMessage **)ptr;
	if (p) { Gitsn_BasicSafetyMessage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_BasicSafetyMessage_dump(Gitsn_BasicSafetyMessage *p, int tab);
// Gitsn_BasicSafetyMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SPAT
typedef struct Gitsn_SPAT
{
	Gitsn_MinuteOfTheYear			 timeStamp;
	Gitsn_DescriptiveName			 name;
	Gitsn_IntersectionStateList		*intersections;
} Gitsn_SPAT;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SPAT *Gitsn_SPAT_new(Gitsn_IntersectionStateList *intersections, Dz1Error *err);
static __inline__ Gitsn_SPAT *Gitsn_SPAT_gen(Dz1Error *err) { return Gitsn_SPAT_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SPAT_copy(Gitsn_SPAT *dst, Gitsn_SPAT *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SPAT *Gitsn_SPAT_clone(Gitsn_SPAT *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SPAT_purge(Gitsn_SPAT *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SPAT_del(Gitsn_SPAT *p);
static __inline__ void Gitsn_SPAT_delAndSetNull(void *ptr)
{
	Gitsn_SPAT **p = (Gitsn_SPAT **)ptr;
	if (p) { Gitsn_SPAT_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SPAT_dump(Gitsn_SPAT *p, int tab);
// Gitsn_SPAT
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ProbeVehicleData
typedef struct Gitsn_ProbeVehicleData
{
	Gitsn_MinuteOfTheYear				 timeStamp;
	Gitsn_ProbeSegmentNumber			 segNum;
	Gitsn_VehicleIdent					*probeID;
	Gitsn_FullPositionVector			*startVector;
	Gitsn_VehicleClassification			*vehicleType;
	Gitsn_ProbeVehicleData_snapshots	*snapshots;
} Gitsn_ProbeVehicleData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ProbeVehicleData *Gitsn_ProbeVehicleData_new(Gitsn_FullPositionVector *startVector, 
																		   Gitsn_VehicleClassification *vehicleType, 
																		   Gitsn_ProbeVehicleData_snapshots *snapshots, Dz1Error *err);
static __inline__ Gitsn_ProbeVehicleData *Gitsn_ProbeVehicleData_gen(Dz1Error *err) { return Gitsn_ProbeVehicleData_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ProbeVehicleData_copy(Gitsn_ProbeVehicleData *dst, Gitsn_ProbeVehicleData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ProbeVehicleData *Gitsn_ProbeVehicleData_clone(Gitsn_ProbeVehicleData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ProbeVehicleData_purge(Gitsn_ProbeVehicleData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ProbeVehicleData_del(Gitsn_ProbeVehicleData *p);
static __inline__ void Gitsn_ProbeVehicleData_delAndSetNull(void *ptr)
{
	Gitsn_ProbeVehicleData **p = (Gitsn_ProbeVehicleData **)ptr;
	if (p) { Gitsn_ProbeVehicleData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ProbeVehicleData_dump(Gitsn_ProbeVehicleData *p, int tab);
// Gitsn_ProbeVehicleData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSideAlert
typedef struct Gitsn_RoadSideAlert
{
	Gitsn_MsgCount						 msgCnt;
	Gitsn_MinuteOfTheYear				 timeStamp;
	Gitsn_ITIScodes						 typeEvent;
	Gitsn_RoadSideAlert_description		*description;
	Gitsn_Priority						 priority;
	Gitsn_HeadingSlice					*heading;
	Gitsn_Extent						 extent;
	Gitsn_FullPositionVector			*position;
	Gitsn_FurtherInfoID					 furtherInfoID;
} Gitsn_RoadSideAlert;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSideAlert *Gitsn_RoadSideAlert_new(Gitsn_MsgCount msgCnt, 
																	 Gitsn_ITIScodes typeEvent, Dz1Error *err);
static __inline__ Gitsn_RoadSideAlert *Gitsn_RoadSideAlert_gen(Dz1Error *err) { return Gitsn_RoadSideAlert_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RoadSideAlert_copy(Gitsn_RoadSideAlert *dst, Gitsn_RoadSideAlert *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RoadSideAlert *Gitsn_RoadSideAlert_clone(Gitsn_RoadSideAlert *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_purge(Gitsn_RoadSideAlert *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_del(Gitsn_RoadSideAlert *p);
static __inline__ void Gitsn_RoadSideAlert_delAndSetNull(void *ptr)
{
	Gitsn_RoadSideAlert **p = (Gitsn_RoadSideAlert **)ptr;
	if (p) { Gitsn_RoadSideAlert_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RoadSideAlert_dump(Gitsn_RoadSideAlert *p, int tab);
// Gitsn_RoadSideAlert
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerInformation
typedef struct Gitsn_TravelerInformation
{
	Gitsn_MsgCount					 msgCnt;
	Gitsn_MinuteOfTheYear			 timeStamp;
	Gitsn_UniqueMSGID				 packetID;
	Gitsn_URL_Base					 urlB;
	Gitsn_TravelerDataFrameList		*dataFrames;
} Gitsn_TravelerInformation;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerInformation *Gitsn_TravelerInformation_new(Gitsn_MsgCount msgCnt, 
																				 Gitsn_TravelerDataFrameList *dataFrames, Dz1Error *err);
static __inline__ Gitsn_TravelerInformation *Gitsn_TravelerInformation_gen(Dz1Error *err) { return Gitsn_TravelerInformation_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_TravelerInformation_copy(Gitsn_TravelerInformation *dst, Gitsn_TravelerInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TravelerInformation *Gitsn_TravelerInformation_clone(Gitsn_TravelerInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerInformation_purge(Gitsn_TravelerInformation *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerInformation_del(Gitsn_TravelerInformation *p);
static __inline__ void Gitsn_TravelerInformation_delAndSetNull(void *ptr)
{
	Gitsn_TravelerInformation **p = (Gitsn_TravelerInformation **)ptr;
	if (p) { Gitsn_TravelerInformation_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TravelerInformation_dump(Gitsn_TravelerInformation *p, int tab);
// Gitsn_TravelerInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EquipmentType
typedef enum Gitsn_EquipmentType
{
	Gitsn_EquipmentType_unknown,
	Gitsn_EquipmentType_rsu,
	Gitsn_EquipmentType_obu,
	Gitsn_EquipmentType_vru,
	Gitsn_EquipmentType_max
} Gitsn_EquipmentType;

DZ1_CPPLINK str_t Gitsn_EquipmentTypeStrA(Gitsn_EquipmentType v);
DZ1_CPPLINK Gitsn_EquipmentType Gitsn_EquipmentTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_EquipmentTypeStrW(Gitsn_EquipmentType v);
DZ1_CPPLINK Gitsn_EquipmentType Gitsn_EquipmentTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_EquipmentTypeStr Gitsn_EquipmentTypeStrW
#define Gitsn_EquipmentTypeFromStr Gitsn_EquipmentTypeFromStrW
#else // UNICODE
#define Gitsn_EquipmentTypeStr Gitsn_EquipmentTypeStrA
#define Gitsn_EquipmentTypeFromStr Gitsn_EquipmentTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_EquipmentTypeStr Gitsn_EquipmentTypeStrA
#define Gitsn_EquipmentTypeFromStr Gitsn_EquipmentTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_EquipmentType *Gitsn_EquipmentType_new(Gitsn_EquipmentType *src, Dz1Error *err);
static __inline__ Gitsn_EquipmentType *Gitsn_EquipmentType_gen(Dz1Error *err) { Gitsn_EquipmentType v = Gitsn_EquipmentType_max; return Gitsn_EquipmentType_new(&v, err); }
static __inline__ void Gitsn_EquipmentType_del(Gitsn_EquipmentType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_EquipmentType_delAndSetNull(void *ptr)
{
	Gitsn_EquipmentType **p = (Gitsn_EquipmentType **)ptr;
	if (p != NULL) { Gitsn_EquipmentType_del(*p); *p = NULL; }
}
// Gitsn_EquipmentType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObjectType
typedef enum Gitsn_ObjectType
{
	Gitsn_ObjectType_unknown,
	Gitsn_ObjectType_vehicle,
	Gitsn_ObjectType_vru,
	Gitsn_ObjectType_animal,
	Gitsn_ObjectType_max
} Gitsn_ObjectType;

DZ1_CPPLINK str_t Gitsn_ObjectTypeStrA(Gitsn_ObjectType v);
DZ1_CPPLINK Gitsn_ObjectType Gitsn_ObjectTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ObjectTypeStrW(Gitsn_ObjectType v);
DZ1_CPPLINK Gitsn_ObjectType Gitsn_ObjectTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ObjectTypeStr Gitsn_ObjectTypeStrW
#define Gitsn_ObjectTypeFromStr Gitsn_ObjectTypeFromStrW
#else // UNICODE
#define Gitsn_ObjectTypeStr Gitsn_ObjectTypeStrA
#define Gitsn_ObjectTypeFromStr Gitsn_ObjectTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ObjectTypeStr Gitsn_ObjectTypeStrA
#define Gitsn_ObjectTypeFromStr Gitsn_ObjectTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ObjectType *Gitsn_ObjectType_new(Gitsn_ObjectType *src, Dz1Error *err);
static __inline__ Gitsn_ObjectType *Gitsn_ObjectType_gen(Dz1Error *err) { Gitsn_ObjectType v = Gitsn_ObjectType_max; return Gitsn_ObjectType_new(&v, err); }
static __inline__ void Gitsn_ObjectType_del(Gitsn_ObjectType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ObjectType_delAndSetNull(void *ptr)
{
	Gitsn_ObjectType **p = (Gitsn_ObjectType **)ptr;
	if (p != NULL) { Gitsn_ObjectType_del(*p); *p = NULL; }
}
// Gitsn_ObjectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PositionOffsetXYZ
typedef struct Gitsn_PositionOffsetXYZ
{
	Gitsn_ObjectDistance	offsetX;
	Gitsn_ObjectDistance	offsetY;
	Gitsn_ObjectDistance	offsetZ;
} Gitsn_PositionOffsetXYZ;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PositionOffsetXYZ *Gitsn_PositionOffsetXYZ_new(Gitsn_ObjectDistance offsetX, 
																			 Gitsn_ObjectDistance offsetY, 
																			 Gitsn_ObjectDistance offsetZ, Dz1Error *err);
static __inline__ Gitsn_PositionOffsetXYZ *Gitsn_PositionOffsetXYZ_gen(Dz1Error *err) { return Gitsn_PositionOffsetXYZ_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_PositionOffsetXYZ_copy(Gitsn_PositionOffsetXYZ *dst, Gitsn_PositionOffsetXYZ *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PositionOffsetXYZ *Gitsn_PositionOffsetXYZ_clone(Gitsn_PositionOffsetXYZ *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionOffsetXYZ_purge(Gitsn_PositionOffsetXYZ *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionOffsetXYZ_del(Gitsn_PositionOffsetXYZ *p);
static __inline__ void Gitsn_PositionOffsetXYZ_delAndSetNull(void *ptr)
{
	Gitsn_PositionOffsetXYZ **p = (Gitsn_PositionOffsetXYZ **)ptr;
	if (p) { Gitsn_PositionOffsetXYZ_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PositionOffsetXYZ_dump(Gitsn_PositionOffsetXYZ *p, int tab);
// Gitsn_PositionOffsetXYZ
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectCommonData
typedef struct Gitsn_DetectedObjectCommonData
{
	Gitsn_ObjectType					 objType;
	Gitsn_ClassificationConfidence		 objTypeCfd;
	Gitsn_ObjectID						 objectID;
	Gitsn_MeasurementTimeOffset			 measurementTime;
	Gitsn_TimeConfidence				 timeConfidence;
	Gitsn_PositionOffsetXYZ				*pos;
	Gitsn_PositionConfidenceSet			*posConfidence;
	Gitsn_Speed							 speed;
	Gitsn_SpeedConfidence				 speedConfidence;
	Gitsn_Speed							 speedZ;
	Gitsn_SpeedConfidence				 speedConfidenceZ;
	Gitsn_Heading						 heading;
	Gitsn_HeadingConfidence				 headingConf;
	Gitsn_AccelerationSet4Way			*accel4way;
	Gitsn_AccelerationConfidence		 accCfdX;
	Gitsn_AccelerationConfidence		 accCfdY;
	Gitsn_AccelerationConfidence		 accCfdZ;
	Gitsn_YawRateConfidence				 accCfdYaw;
} Gitsn_DetectedObjectCommonData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectCommonData *Gitsn_DetectedObjectCommonData_new(Gitsn_ObjectType objType, 
																						   Gitsn_ClassificationConfidence objTypeCfd, 
																						   Gitsn_ObjectID objectID, 
																						   Gitsn_MeasurementTimeOffset measurementTime, 
																						   Gitsn_TimeConfidence timeConfidence, 
																						   Gitsn_PositionOffsetXYZ *pos, 
																						   Gitsn_PositionConfidenceSet *posConfidence, 
																						   Gitsn_Speed speed, 
																						   Gitsn_SpeedConfidence speedConfidence, 
																						   Gitsn_SpeedConfidence speedConfidenceZ, 
																						   Gitsn_Heading heading, 
																						   Gitsn_HeadingConfidence headingConf, Dz1Error *err);
static __inline__ Gitsn_DetectedObjectCommonData *Gitsn_DetectedObjectCommonData_gen(Dz1Error *err) { return Gitsn_DetectedObjectCommonData_new(Gitsn_ObjectType_max, 0, 0, 0, Gitsn_TimeConfidence_max, NULL, NULL, 0, Gitsn_SpeedConfidence_max, Gitsn_SpeedConfidence_max, 0, Gitsn_HeadingConfidence_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_DetectedObjectCommonData_copy(Gitsn_DetectedObjectCommonData *dst, Gitsn_DetectedObjectCommonData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectCommonData *Gitsn_DetectedObjectCommonData_clone(Gitsn_DetectedObjectCommonData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectCommonData_purge(Gitsn_DetectedObjectCommonData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectCommonData_del(Gitsn_DetectedObjectCommonData *p);
static __inline__ void Gitsn_DetectedObjectCommonData_delAndSetNull(void *ptr)
{
	Gitsn_DetectedObjectCommonData **p = (Gitsn_DetectedObjectCommonData **)ptr;
	if (p) { Gitsn_DetectedObjectCommonData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectCommonData_dump(Gitsn_DetectedObjectCommonData *p, int tab);
// Gitsn_DetectedObjectCommonData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Attitude
typedef struct Gitsn_Attitude
{
	Gitsn_PitchDetected		pitch;
	Gitsn_RollDetected		roll;
	Gitsn_YawDetected		yaw;
} Gitsn_Attitude;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_Attitude *Gitsn_Attitude_new(Gitsn_PitchDetected pitch, 
														   Gitsn_RollDetected roll, 
														   Gitsn_YawDetected yaw, Dz1Error *err);
static __inline__ Gitsn_Attitude *Gitsn_Attitude_gen(Dz1Error *err) { return Gitsn_Attitude_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_Attitude_copy(Gitsn_Attitude *dst, Gitsn_Attitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Attitude *Gitsn_Attitude_clone(Gitsn_Attitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Attitude_purge(Gitsn_Attitude *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Attitude_del(Gitsn_Attitude *p);
static __inline__ void Gitsn_Attitude_delAndSetNull(void *ptr)
{
	Gitsn_Attitude **p = (Gitsn_Attitude **)ptr;
	if (p) { Gitsn_Attitude_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Attitude_dump(Gitsn_Attitude *p, int tab);
// Gitsn_Attitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AttitudeConfidence
typedef struct Gitsn_AttitudeConfidence
{
	Gitsn_HeadingConfidence		pitchConfidence;
	Gitsn_HeadingConfidence		rollConfidence;
	Gitsn_HeadingConfidence		yawConfidence;
} Gitsn_AttitudeConfidence;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AttitudeConfidence *Gitsn_AttitudeConfidence_new(Gitsn_HeadingConfidence pitchConfidence, 
																			   Gitsn_HeadingConfidence rollConfidence, 
																			   Gitsn_HeadingConfidence yawConfidence, Dz1Error *err);
static __inline__ Gitsn_AttitudeConfidence *Gitsn_AttitudeConfidence_gen(Dz1Error *err) { return Gitsn_AttitudeConfidence_new(Gitsn_HeadingConfidence_max, Gitsn_HeadingConfidence_max, Gitsn_HeadingConfidence_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_AttitudeConfidence_copy(Gitsn_AttitudeConfidence *dst, Gitsn_AttitudeConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AttitudeConfidence *Gitsn_AttitudeConfidence_clone(Gitsn_AttitudeConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AttitudeConfidence_purge(Gitsn_AttitudeConfidence *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AttitudeConfidence_del(Gitsn_AttitudeConfidence *p);
static __inline__ void Gitsn_AttitudeConfidence_delAndSetNull(void *ptr)
{
	Gitsn_AttitudeConfidence **p = (Gitsn_AttitudeConfidence **)ptr;
	if (p) { Gitsn_AttitudeConfidence_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AttitudeConfidence_dump(Gitsn_AttitudeConfidence *p, int tab);
// Gitsn_AttitudeConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AngularVelocity
typedef struct Gitsn_AngularVelocity
{
	Gitsn_PitchRate		pitchRate;
	Gitsn_RollRate		rollRate;
} Gitsn_AngularVelocity;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AngularVelocity *Gitsn_AngularVelocity_new(Gitsn_PitchRate pitchRate, 
																		 Gitsn_RollRate rollRate, Dz1Error *err);
static __inline__ Gitsn_AngularVelocity *Gitsn_AngularVelocity_gen(Dz1Error *err) { return Gitsn_AngularVelocity_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_AngularVelocity_copy(Gitsn_AngularVelocity *dst, Gitsn_AngularVelocity *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AngularVelocity *Gitsn_AngularVelocity_clone(Gitsn_AngularVelocity *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AngularVelocity_purge(Gitsn_AngularVelocity *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AngularVelocity_del(Gitsn_AngularVelocity *p);
static __inline__ void Gitsn_AngularVelocity_delAndSetNull(void *ptr)
{
	Gitsn_AngularVelocity **p = (Gitsn_AngularVelocity **)ptr;
	if (p) { Gitsn_AngularVelocity_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AngularVelocity_dump(Gitsn_AngularVelocity *p, int tab);
// Gitsn_AngularVelocity
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PitchRateConfidence
typedef enum Gitsn_PitchRateConfidence
{
	Gitsn_PitchRateConfidence_unavailable,
	Gitsn_PitchRateConfidence_degSec_100_00,
	Gitsn_PitchRateConfidence_degSec_010_00,
	Gitsn_PitchRateConfidence_degSec_005_00,
	Gitsn_PitchRateConfidence_degSec_001_00,
	Gitsn_PitchRateConfidence_degSec_000_10,
	Gitsn_PitchRateConfidence_degSec_000_05,
	Gitsn_PitchRateConfidence_degSec_000_01,
	Gitsn_PitchRateConfidence_max
} Gitsn_PitchRateConfidence;

DZ1_CPPLINK str_t Gitsn_PitchRateConfidenceStrA(Gitsn_PitchRateConfidence v);
DZ1_CPPLINK Gitsn_PitchRateConfidence Gitsn_PitchRateConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_PitchRateConfidenceStrW(Gitsn_PitchRateConfidence v);
DZ1_CPPLINK Gitsn_PitchRateConfidence Gitsn_PitchRateConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_PitchRateConfidenceStr Gitsn_PitchRateConfidenceStrW
#define Gitsn_PitchRateConfidenceFromStr Gitsn_PitchRateConfidenceFromStrW
#else // UNICODE
#define Gitsn_PitchRateConfidenceStr Gitsn_PitchRateConfidenceStrA
#define Gitsn_PitchRateConfidenceFromStr Gitsn_PitchRateConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_PitchRateConfidenceStr Gitsn_PitchRateConfidenceStrA
#define Gitsn_PitchRateConfidenceFromStr Gitsn_PitchRateConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PitchRateConfidence *Gitsn_PitchRateConfidence_new(Gitsn_PitchRateConfidence *src, Dz1Error *err);
static __inline__ Gitsn_PitchRateConfidence *Gitsn_PitchRateConfidence_gen(Dz1Error *err) { Gitsn_PitchRateConfidence v = Gitsn_PitchRateConfidence_max; return Gitsn_PitchRateConfidence_new(&v, err); }
static __inline__ void Gitsn_PitchRateConfidence_del(Gitsn_PitchRateConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_PitchRateConfidence_delAndSetNull(void *ptr)
{
	Gitsn_PitchRateConfidence **p = (Gitsn_PitchRateConfidence **)ptr;
	if (p != NULL) { Gitsn_PitchRateConfidence_del(*p); *p = NULL; }
}
// Gitsn_PitchRateConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RollRateConfidence
typedef enum Gitsn_RollRateConfidence
{
	Gitsn_RollRateConfidence_unavailable,
	Gitsn_RollRateConfidence_degSec_100_00,
	Gitsn_RollRateConfidence_degSec_010_00,
	Gitsn_RollRateConfidence_degSec_005_00,
	Gitsn_RollRateConfidence_degSec_001_00,
	Gitsn_RollRateConfidence_degSec_000_10,
	Gitsn_RollRateConfidence_degSec_000_05,
	Gitsn_RollRateConfidence_degSec_000_01,
	Gitsn_RollRateConfidence_max
} Gitsn_RollRateConfidence;

DZ1_CPPLINK str_t Gitsn_RollRateConfidenceStrA(Gitsn_RollRateConfidence v);
DZ1_CPPLINK Gitsn_RollRateConfidence Gitsn_RollRateConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_RollRateConfidenceStrW(Gitsn_RollRateConfidence v);
DZ1_CPPLINK Gitsn_RollRateConfidence Gitsn_RollRateConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_RollRateConfidenceStr Gitsn_RollRateConfidenceStrW
#define Gitsn_RollRateConfidenceFromStr Gitsn_RollRateConfidenceFromStrW
#else // UNICODE
#define Gitsn_RollRateConfidenceStr Gitsn_RollRateConfidenceStrA
#define Gitsn_RollRateConfidenceFromStr Gitsn_RollRateConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_RollRateConfidenceStr Gitsn_RollRateConfidenceStrA
#define Gitsn_RollRateConfidenceFromStr Gitsn_RollRateConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RollRateConfidence *Gitsn_RollRateConfidence_new(Gitsn_RollRateConfidence *src, Dz1Error *err);
static __inline__ Gitsn_RollRateConfidence *Gitsn_RollRateConfidence_gen(Dz1Error *err) { Gitsn_RollRateConfidence v = Gitsn_RollRateConfidence_max; return Gitsn_RollRateConfidence_new(&v, err); }
static __inline__ void Gitsn_RollRateConfidence_del(Gitsn_RollRateConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_RollRateConfidence_delAndSetNull(void *ptr)
{
	Gitsn_RollRateConfidence **p = (Gitsn_RollRateConfidence **)ptr;
	if (p != NULL) { Gitsn_RollRateConfidence_del(*p); *p = NULL; }
}
// Gitsn_RollRateConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AngularVelocityConfidence
typedef struct Gitsn_AngularVelocityConfidence
{
	Gitsn_PitchRateConfidence		pitchRateConfidence;
	Gitsn_RollRateConfidence		rollRateConfidence;
} Gitsn_AngularVelocityConfidence;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AngularVelocityConfidence *Gitsn_AngularVelocityConfidence_new(Dz1Error *err);
static __inline__ Gitsn_AngularVelocityConfidence *Gitsn_AngularVelocityConfidence_gen(Dz1Error *err) { return Gitsn_AngularVelocityConfidence_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_AngularVelocityConfidence_copy(Gitsn_AngularVelocityConfidence *dst, Gitsn_AngularVelocityConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AngularVelocityConfidence *Gitsn_AngularVelocityConfidence_clone(Gitsn_AngularVelocityConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AngularVelocityConfidence_purge(Gitsn_AngularVelocityConfidence *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AngularVelocityConfidence_del(Gitsn_AngularVelocityConfidence *p);
static __inline__ void Gitsn_AngularVelocityConfidence_delAndSetNull(void *ptr)
{
	Gitsn_AngularVelocityConfidence **p = (Gitsn_AngularVelocityConfidence **)ptr;
	if (p) { Gitsn_AngularVelocityConfidence_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AngularVelocityConfidence_dump(Gitsn_AngularVelocityConfidence *p, int tab);
// Gitsn_AngularVelocityConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SizeValueConfidence
typedef enum Gitsn_SizeValueConfidence
{
	Gitsn_SizeValueConfidence_unavailable,
	Gitsn_SizeValueConfidence_size_100_00,
	Gitsn_SizeValueConfidence_size_050_00,
	Gitsn_SizeValueConfidence_size_020_00,
	Gitsn_SizeValueConfidence_size_010_00,
	Gitsn_SizeValueConfidence_size_005_00,
	Gitsn_SizeValueConfidence_size_002_00,
	Gitsn_SizeValueConfidence_size_001_00,
	Gitsn_SizeValueConfidence_size_000_50,
	Gitsn_SizeValueConfidence_size_000_20,
	Gitsn_SizeValueConfidence_size_000_10,
	Gitsn_SizeValueConfidence_size_000_05,
	Gitsn_SizeValueConfidence_size_000_02,
	Gitsn_SizeValueConfidence_size_000_01,
	Gitsn_SizeValueConfidence_max
} Gitsn_SizeValueConfidence;

DZ1_CPPLINK str_t Gitsn_SizeValueConfidenceStrA(Gitsn_SizeValueConfidence v);
DZ1_CPPLINK Gitsn_SizeValueConfidence Gitsn_SizeValueConfidenceFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SizeValueConfidenceStrW(Gitsn_SizeValueConfidence v);
DZ1_CPPLINK Gitsn_SizeValueConfidence Gitsn_SizeValueConfidenceFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SizeValueConfidenceStr Gitsn_SizeValueConfidenceStrW
#define Gitsn_SizeValueConfidenceFromStr Gitsn_SizeValueConfidenceFromStrW
#else // UNICODE
#define Gitsn_SizeValueConfidenceStr Gitsn_SizeValueConfidenceStrA
#define Gitsn_SizeValueConfidenceFromStr Gitsn_SizeValueConfidenceFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SizeValueConfidenceStr Gitsn_SizeValueConfidenceStrA
#define Gitsn_SizeValueConfidenceFromStr Gitsn_SizeValueConfidenceFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SizeValueConfidence *Gitsn_SizeValueConfidence_new(Gitsn_SizeValueConfidence *src, Dz1Error *err);
static __inline__ Gitsn_SizeValueConfidence *Gitsn_SizeValueConfidence_gen(Dz1Error *err) { Gitsn_SizeValueConfidence v = Gitsn_SizeValueConfidence_max; return Gitsn_SizeValueConfidence_new(&v, err); }
static __inline__ void Gitsn_SizeValueConfidence_del(Gitsn_SizeValueConfidence *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SizeValueConfidence_delAndSetNull(void *ptr)
{
	Gitsn_SizeValueConfidence **p = (Gitsn_SizeValueConfidence **)ptr;
	if (p != NULL) { Gitsn_SizeValueConfidence_del(*p); *p = NULL; }
}
// Gitsn_SizeValueConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleSizeConfidence
typedef struct Gitsn_VehicleSizeConfidence
{
	Gitsn_SizeValueConfidence		vehicleWidthConfidence;
	Gitsn_SizeValueConfidence		vehicleLengthConfidence;
	Gitsn_SizeValueConfidence		vehicleHeightConfidence;
} Gitsn_VehicleSizeConfidence;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleSizeConfidence *Gitsn_VehicleSizeConfidence_new(Gitsn_SizeValueConfidence vehicleWidthConfidence, 
																					 Gitsn_SizeValueConfidence vehicleLengthConfidence, Dz1Error *err);
static __inline__ Gitsn_VehicleSizeConfidence *Gitsn_VehicleSizeConfidence_gen(Dz1Error *err) { return Gitsn_VehicleSizeConfidence_new(Gitsn_SizeValueConfidence_max, Gitsn_SizeValueConfidence_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_VehicleSizeConfidence_copy(Gitsn_VehicleSizeConfidence *dst, Gitsn_VehicleSizeConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_VehicleSizeConfidence *Gitsn_VehicleSizeConfidence_clone(Gitsn_VehicleSizeConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSizeConfidence_purge(Gitsn_VehicleSizeConfidence *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSizeConfidence_del(Gitsn_VehicleSizeConfidence *p);
static __inline__ void Gitsn_VehicleSizeConfidence_delAndSetNull(void *ptr)
{
	Gitsn_VehicleSizeConfidence **p = (Gitsn_VehicleSizeConfidence **)ptr;
	if (p) { Gitsn_VehicleSizeConfidence_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_VehicleSizeConfidence_dump(Gitsn_VehicleSizeConfidence *p, int tab);
// Gitsn_VehicleSizeConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedVehicleData
typedef struct Gitsn_DetectedVehicleData
{
	Gitsn_ExteriorLights				*lights;
	Gitsn_Attitude						*vehAttitude;
	Gitsn_AttitudeConfidence			*vehAttitudeConfidence;
	Gitsn_AngularVelocity				*vehAngVel;
	Gitsn_AngularVelocityConfidence		*vehAngleConfidence;
	Gitsn_VehicleSize					*size;
	Gitsn_VehicleHeight					 height;
	Gitsn_VehicleSizeConfidence			*vehicleSizeConfidence;
	Gitsn_BasicVehicleClass				 vehicleClass;
	Gitsn_ClassificationConfidence		 classConf;
} Gitsn_DetectedVehicleData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedVehicleData *Gitsn_DetectedVehicleData_new(Dz1Error *err);
static __inline__ Gitsn_DetectedVehicleData *Gitsn_DetectedVehicleData_gen(Dz1Error *err) { return Gitsn_DetectedVehicleData_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_DetectedVehicleData_copy(Gitsn_DetectedVehicleData *dst, Gitsn_DetectedVehicleData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedVehicleData *Gitsn_DetectedVehicleData_clone(Gitsn_DetectedVehicleData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedVehicleData_purge(Gitsn_DetectedVehicleData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedVehicleData_del(Gitsn_DetectedVehicleData *p);
static __inline__ void Gitsn_DetectedVehicleData_delAndSetNull(void *ptr)
{
	Gitsn_DetectedVehicleData **p = (Gitsn_DetectedVehicleData **)ptr;
	if (p) { Gitsn_DetectedVehicleData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedVehicleData_dump(Gitsn_DetectedVehicleData *p, int tab);
// Gitsn_DetectedVehicleData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PersonalDeviceUserType
typedef enum Gitsn_PersonalDeviceUserType
{
	Gitsn_PersonalDeviceUserType_unavailable,
	Gitsn_PersonalDeviceUserType_aPEDESTRIAN,
	Gitsn_PersonalDeviceUserType_aPEDALCYCLIST,
	Gitsn_PersonalDeviceUserType_aPUBLICSAFETYWORKER,
	Gitsn_PersonalDeviceUserType_anANIMAL,
	Gitsn_PersonalDeviceUserType_max
} Gitsn_PersonalDeviceUserType;

DZ1_CPPLINK str_t Gitsn_PersonalDeviceUserTypeStrA(Gitsn_PersonalDeviceUserType v);
DZ1_CPPLINK Gitsn_PersonalDeviceUserType Gitsn_PersonalDeviceUserTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_PersonalDeviceUserTypeStrW(Gitsn_PersonalDeviceUserType v);
DZ1_CPPLINK Gitsn_PersonalDeviceUserType Gitsn_PersonalDeviceUserTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_PersonalDeviceUserTypeStr Gitsn_PersonalDeviceUserTypeStrW
#define Gitsn_PersonalDeviceUserTypeFromStr Gitsn_PersonalDeviceUserTypeFromStrW
#else // UNICODE
#define Gitsn_PersonalDeviceUserTypeStr Gitsn_PersonalDeviceUserTypeStrA
#define Gitsn_PersonalDeviceUserTypeFromStr Gitsn_PersonalDeviceUserTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_PersonalDeviceUserTypeStr Gitsn_PersonalDeviceUserTypeStrA
#define Gitsn_PersonalDeviceUserTypeFromStr Gitsn_PersonalDeviceUserTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PersonalDeviceUserType *Gitsn_PersonalDeviceUserType_new(Gitsn_PersonalDeviceUserType *src, Dz1Error *err);
static __inline__ Gitsn_PersonalDeviceUserType *Gitsn_PersonalDeviceUserType_gen(Dz1Error *err) { Gitsn_PersonalDeviceUserType v = Gitsn_PersonalDeviceUserType_max; return Gitsn_PersonalDeviceUserType_new(&v, err); }
static __inline__ void Gitsn_PersonalDeviceUserType_del(Gitsn_PersonalDeviceUserType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_PersonalDeviceUserType_delAndSetNull(void *ptr)
{
	Gitsn_PersonalDeviceUserType **p = (Gitsn_PersonalDeviceUserType **)ptr;
	if (p != NULL) { Gitsn_PersonalDeviceUserType_del(*p); *p = NULL; }
}
// Gitsn_PersonalDeviceUserType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_HumanPropelledType
typedef enum Gitsn_HumanPropelledType
{
	Gitsn_HumanPropelledType_unavailable,
	Gitsn_HumanPropelledType_otherTypes,
	Gitsn_HumanPropelledType_onFoot,
	Gitsn_HumanPropelledType_skateboard,
	Gitsn_HumanPropelledType_pushOrKickScooter,
	Gitsn_HumanPropelledType_wheelchair,
	Gitsn_HumanPropelledType_max
} Gitsn_HumanPropelledType;

DZ1_CPPLINK str_t Gitsn_HumanPropelledTypeStrA(Gitsn_HumanPropelledType v);
DZ1_CPPLINK Gitsn_HumanPropelledType Gitsn_HumanPropelledTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_HumanPropelledTypeStrW(Gitsn_HumanPropelledType v);
DZ1_CPPLINK Gitsn_HumanPropelledType Gitsn_HumanPropelledTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_HumanPropelledTypeStr Gitsn_HumanPropelledTypeStrW
#define Gitsn_HumanPropelledTypeFromStr Gitsn_HumanPropelledTypeFromStrW
#else // UNICODE
#define Gitsn_HumanPropelledTypeStr Gitsn_HumanPropelledTypeStrA
#define Gitsn_HumanPropelledTypeFromStr Gitsn_HumanPropelledTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_HumanPropelledTypeStr Gitsn_HumanPropelledTypeStrA
#define Gitsn_HumanPropelledTypeFromStr Gitsn_HumanPropelledTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_HumanPropelledType *Gitsn_HumanPropelledType_new(Gitsn_HumanPropelledType *src, Dz1Error *err);
static __inline__ Gitsn_HumanPropelledType *Gitsn_HumanPropelledType_gen(Dz1Error *err) { Gitsn_HumanPropelledType v = Gitsn_HumanPropelledType_max; return Gitsn_HumanPropelledType_new(&v, err); }
static __inline__ void Gitsn_HumanPropelledType_del(Gitsn_HumanPropelledType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_HumanPropelledType_delAndSetNull(void *ptr)
{
	Gitsn_HumanPropelledType **p = (Gitsn_HumanPropelledType **)ptr;
	if (p != NULL) { Gitsn_HumanPropelledType_del(*p); *p = NULL; }
}
// Gitsn_HumanPropelledType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AnimalPropelledType
typedef enum Gitsn_AnimalPropelledType
{
	Gitsn_AnimalPropelledType_unavailable,
	Gitsn_AnimalPropelledType_otherTypes,
	Gitsn_AnimalPropelledType_animalMounted,
	Gitsn_AnimalPropelledType_animalDrawnCarriage,
	Gitsn_AnimalPropelledType_max
} Gitsn_AnimalPropelledType;

DZ1_CPPLINK str_t Gitsn_AnimalPropelledTypeStrA(Gitsn_AnimalPropelledType v);
DZ1_CPPLINK Gitsn_AnimalPropelledType Gitsn_AnimalPropelledTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_AnimalPropelledTypeStrW(Gitsn_AnimalPropelledType v);
DZ1_CPPLINK Gitsn_AnimalPropelledType Gitsn_AnimalPropelledTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_AnimalPropelledTypeStr Gitsn_AnimalPropelledTypeStrW
#define Gitsn_AnimalPropelledTypeFromStr Gitsn_AnimalPropelledTypeFromStrW
#else // UNICODE
#define Gitsn_AnimalPropelledTypeStr Gitsn_AnimalPropelledTypeStrA
#define Gitsn_AnimalPropelledTypeFromStr Gitsn_AnimalPropelledTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_AnimalPropelledTypeStr Gitsn_AnimalPropelledTypeStrA
#define Gitsn_AnimalPropelledTypeFromStr Gitsn_AnimalPropelledTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AnimalPropelledType *Gitsn_AnimalPropelledType_new(Gitsn_AnimalPropelledType *src, Dz1Error *err);
static __inline__ Gitsn_AnimalPropelledType *Gitsn_AnimalPropelledType_gen(Dz1Error *err) { Gitsn_AnimalPropelledType v = Gitsn_AnimalPropelledType_max; return Gitsn_AnimalPropelledType_new(&v, err); }
static __inline__ void Gitsn_AnimalPropelledType_del(Gitsn_AnimalPropelledType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_AnimalPropelledType_delAndSetNull(void *ptr)
{
	Gitsn_AnimalPropelledType **p = (Gitsn_AnimalPropelledType **)ptr;
	if (p != NULL) { Gitsn_AnimalPropelledType_del(*p); *p = NULL; }
}
// Gitsn_AnimalPropelledType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MotorizedPropelledType
typedef enum Gitsn_MotorizedPropelledType
{
	Gitsn_MotorizedPropelledType_unavailable,
	Gitsn_MotorizedPropelledType_otherTypes,
	Gitsn_MotorizedPropelledType_wheelChair,
	Gitsn_MotorizedPropelledType_bicycle,
	Gitsn_MotorizedPropelledType_scooter,
	Gitsn_MotorizedPropelledType_selfBalancingDevice,
	Gitsn_MotorizedPropelledType_max
} Gitsn_MotorizedPropelledType;

DZ1_CPPLINK str_t Gitsn_MotorizedPropelledTypeStrA(Gitsn_MotorizedPropelledType v);
DZ1_CPPLINK Gitsn_MotorizedPropelledType Gitsn_MotorizedPropelledTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_MotorizedPropelledTypeStrW(Gitsn_MotorizedPropelledType v);
DZ1_CPPLINK Gitsn_MotorizedPropelledType Gitsn_MotorizedPropelledTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_MotorizedPropelledTypeStr Gitsn_MotorizedPropelledTypeStrW
#define Gitsn_MotorizedPropelledTypeFromStr Gitsn_MotorizedPropelledTypeFromStrW
#else // UNICODE
#define Gitsn_MotorizedPropelledTypeStr Gitsn_MotorizedPropelledTypeStrA
#define Gitsn_MotorizedPropelledTypeFromStr Gitsn_MotorizedPropelledTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_MotorizedPropelledTypeStr Gitsn_MotorizedPropelledTypeStrA
#define Gitsn_MotorizedPropelledTypeFromStr Gitsn_MotorizedPropelledTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MotorizedPropelledType *Gitsn_MotorizedPropelledType_new(Gitsn_MotorizedPropelledType *src, Dz1Error *err);
static __inline__ Gitsn_MotorizedPropelledType *Gitsn_MotorizedPropelledType_gen(Dz1Error *err) { Gitsn_MotorizedPropelledType v = Gitsn_MotorizedPropelledType_max; return Gitsn_MotorizedPropelledType_new(&v, err); }
static __inline__ void Gitsn_MotorizedPropelledType_del(Gitsn_MotorizedPropelledType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_MotorizedPropelledType_delAndSetNull(void *ptr)
{
	Gitsn_MotorizedPropelledType **p = (Gitsn_MotorizedPropelledType **)ptr;
	if (p != NULL) { Gitsn_MotorizedPropelledType_del(*p); *p = NULL; }
}
// Gitsn_MotorizedPropelledType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PropelledInformationPresent
typedef enum Gitsn_PropelledInformationPresent
{
	Gitsn_PropelledInformationPresent_human,
	Gitsn_PropelledInformationPresent_animal,
	Gitsn_PropelledInformationPresent_motor,
	Gitsn_PropelledInformationPresent_max
} Gitsn_PropelledInformationPresent;

DZ1_CPPLINK str_t Gitsn_PropelledInformationPresentStrA(Gitsn_PropelledInformationPresent v);
DZ1_CPPLINK Gitsn_PropelledInformationPresent Gitsn_PropelledInformationPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_PropelledInformationPresentStrW(Gitsn_PropelledInformationPresent v);
DZ1_CPPLINK Gitsn_PropelledInformationPresent Gitsn_PropelledInformationPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_PropelledInformationPresentStr Gitsn_PropelledInformationPresentStrW
#define Gitsn_PropelledInformationPresentFromStr Gitsn_PropelledInformationPresentFromStrW
#else // UNICODE
#define Gitsn_PropelledInformationPresentStr Gitsn_PropelledInformationPresentStrA
#define Gitsn_PropelledInformationPresentFromStr Gitsn_PropelledInformationPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_PropelledInformationPresentStr Gitsn_PropelledInformationPresentStrA
#define Gitsn_PropelledInformationPresentFromStr Gitsn_PropelledInformationPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PropelledInformationPresent *Gitsn_PropelledInformationPresent_new(Gitsn_PropelledInformationPresent *src, Dz1Error *err);
static __inline__ Gitsn_PropelledInformationPresent *Gitsn_PropelledInformationPresent_gen(Dz1Error *err) { Gitsn_PropelledInformationPresent v = Gitsn_PropelledInformationPresent_max; return Gitsn_PropelledInformationPresent_new(&v, err); }
#define Gitsn_PropelledInformationPresent_clone             Gitsn_PropelledInformationPresent_new
static __inline__ void Gitsn_PropelledInformationPresent_del(Gitsn_PropelledInformationPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_PropelledInformationPresent_delAndSetNull(void *ptr)
{
	Gitsn_PropelledInformationPresent **p = (Gitsn_PropelledInformationPresent **)ptr;
	if (p != NULL) { Gitsn_PropelledInformationPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PropelledInformationPresent_dump(Gitsn_PropelledInformationPresent *v, int tab);
// Gitsn_PropelledInformationPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PropelledInformation
typedef struct Gitsn_PropelledInformation
{
	Gitsn_PropelledInformationPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_HumanPropelledType		human;
		Gitsn_AnimalPropelledType		animal;
		Gitsn_MotorizedPropelledType	motor;
	} x;
} Gitsn_PropelledInformation;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PropelledInformation *Gitsn_PropelledInformation_new(Gitsn_PropelledInformationPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_PropelledInformation *Gitsn_PropelledInformation_gen(Dz1Error *err) { return Gitsn_PropelledInformation_new(Gitsn_PropelledInformationPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_PropelledInformation_copy(Gitsn_PropelledInformation *dst, Gitsn_PropelledInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PropelledInformation *Gitsn_PropelledInformation_clone(Gitsn_PropelledInformation *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PropelledInformation_purge(Gitsn_PropelledInformation *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PropelledInformation_del(Gitsn_PropelledInformation *p);
static __inline__ void Gitsn_PropelledInformation_delAndSetNull(void *ptr)
{
	Gitsn_PropelledInformation **p = (Gitsn_PropelledInformation **)ptr;
	if (p != NULL) { Gitsn_PropelledInformation_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PropelledInformation_dump(Gitsn_PropelledInformation *p, int tab);
// Gitsn_PropelledInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Attachment
typedef enum Gitsn_Attachment
{
	Gitsn_Attachment_unavailable,
	Gitsn_Attachment_stroller,
	Gitsn_Attachment_bicycleTrailer,
	Gitsn_Attachment_cart,
	Gitsn_Attachment_wheelchair,
	Gitsn_Attachment_otherWalkAssistAttachments,
	Gitsn_Attachment_pet,
	Gitsn_Attachment_max
} Gitsn_Attachment;

DZ1_CPPLINK str_t Gitsn_AttachmentStrA(Gitsn_Attachment v);
DZ1_CPPLINK Gitsn_Attachment Gitsn_AttachmentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_AttachmentStrW(Gitsn_Attachment v);
DZ1_CPPLINK Gitsn_Attachment Gitsn_AttachmentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_AttachmentStr Gitsn_AttachmentStrW
#define Gitsn_AttachmentFromStr Gitsn_AttachmentFromStrW
#else // UNICODE
#define Gitsn_AttachmentStr Gitsn_AttachmentStrA
#define Gitsn_AttachmentFromStr Gitsn_AttachmentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_AttachmentStr Gitsn_AttachmentStrA
#define Gitsn_AttachmentFromStr Gitsn_AttachmentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Attachment *Gitsn_Attachment_new(Gitsn_Attachment *src, Dz1Error *err);
static __inline__ Gitsn_Attachment *Gitsn_Attachment_gen(Dz1Error *err) { Gitsn_Attachment v = Gitsn_Attachment_max; return Gitsn_Attachment_new(&v, err); }
static __inline__ void Gitsn_Attachment_del(Gitsn_Attachment *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Attachment_delAndSetNull(void *ptr)
{
	Gitsn_Attachment **p = (Gitsn_Attachment **)ptr;
	if (p != NULL) { Gitsn_Attachment_del(*p); *p = NULL; }
}
// Gitsn_Attachment
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedVRUData
typedef struct Gitsn_DetectedVRUData
{
	Gitsn_PersonalDeviceUserType	 basicType;
	Gitsn_PropelledInformation		*propulsion;
	Gitsn_Attachment				 attachment;
	Gitsn_AttachmentRadius			 radius;
} Gitsn_DetectedVRUData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedVRUData *Gitsn_DetectedVRUData_new(Dz1Error *err);
static __inline__ Gitsn_DetectedVRUData *Gitsn_DetectedVRUData_gen(Dz1Error *err) { return Gitsn_DetectedVRUData_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_DetectedVRUData_copy(Gitsn_DetectedVRUData *dst, Gitsn_DetectedVRUData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedVRUData *Gitsn_DetectedVRUData_clone(Gitsn_DetectedVRUData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedVRUData_purge(Gitsn_DetectedVRUData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedVRUData_del(Gitsn_DetectedVRUData *p);
static __inline__ void Gitsn_DetectedVRUData_delAndSetNull(void *ptr)
{
	Gitsn_DetectedVRUData **p = (Gitsn_DetectedVRUData **)ptr;
	if (p) { Gitsn_DetectedVRUData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedVRUData_dump(Gitsn_DetectedVRUData *p, int tab);
// Gitsn_DetectedVRUData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObstacleSize
typedef struct Gitsn_ObstacleSize
{
	Gitsn_SizeValue		width;
	Gitsn_SizeValue		length;
	Gitsn_SizeValue		height;
} Gitsn_ObstacleSize;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ObstacleSize *Gitsn_ObstacleSize_new(Gitsn_SizeValue width, 
																   Gitsn_SizeValue length, Dz1Error *err);
static __inline__ Gitsn_ObstacleSize *Gitsn_ObstacleSize_gen(Dz1Error *err) { return Gitsn_ObstacleSize_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ObstacleSize_copy(Gitsn_ObstacleSize *dst, Gitsn_ObstacleSize *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ObstacleSize *Gitsn_ObstacleSize_clone(Gitsn_ObstacleSize *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ObstacleSize_purge(Gitsn_ObstacleSize *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ObstacleSize_del(Gitsn_ObstacleSize *p);
static __inline__ void Gitsn_ObstacleSize_delAndSetNull(void *ptr)
{
	Gitsn_ObstacleSize **p = (Gitsn_ObstacleSize **)ptr;
	if (p) { Gitsn_ObstacleSize_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ObstacleSize_dump(Gitsn_ObstacleSize *p, int tab);
// Gitsn_ObstacleSize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObstacleSizeConfidence
typedef struct Gitsn_ObstacleSizeConfidence
{
	Gitsn_SizeValueConfidence		widthConfidence;
	Gitsn_SizeValueConfidence		lengthConfidence;
	Gitsn_SizeValueConfidence		heightConfidence;
} Gitsn_ObstacleSizeConfidence;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ObstacleSizeConfidence *Gitsn_ObstacleSizeConfidence_new(Gitsn_SizeValueConfidence widthConfidence, 
																					   Gitsn_SizeValueConfidence lengthConfidence, Dz1Error *err);
static __inline__ Gitsn_ObstacleSizeConfidence *Gitsn_ObstacleSizeConfidence_gen(Dz1Error *err) { return Gitsn_ObstacleSizeConfidence_new(Gitsn_SizeValueConfidence_max, Gitsn_SizeValueConfidence_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ObstacleSizeConfidence_copy(Gitsn_ObstacleSizeConfidence *dst, Gitsn_ObstacleSizeConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ObstacleSizeConfidence *Gitsn_ObstacleSizeConfidence_clone(Gitsn_ObstacleSizeConfidence *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ObstacleSizeConfidence_purge(Gitsn_ObstacleSizeConfidence *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ObstacleSizeConfidence_del(Gitsn_ObstacleSizeConfidence *p);
static __inline__ void Gitsn_ObstacleSizeConfidence_delAndSetNull(void *ptr)
{
	Gitsn_ObstacleSizeConfidence **p = (Gitsn_ObstacleSizeConfidence **)ptr;
	if (p) { Gitsn_ObstacleSizeConfidence_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ObstacleSizeConfidence_dump(Gitsn_ObstacleSizeConfidence *p, int tab);
// Gitsn_ObstacleSizeConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObstacleData
typedef struct Gitsn_DetectedObstacleData
{
	Gitsn_ObstacleSize				*obstSize;
	Gitsn_ObstacleSizeConfidence	*obstSizeConfidence;
} Gitsn_DetectedObstacleData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObstacleData *Gitsn_DetectedObstacleData_new(Gitsn_ObstacleSize *obstSize, 
																				   Gitsn_ObstacleSizeConfidence *obstSizeConfidence, Dz1Error *err);
static __inline__ Gitsn_DetectedObstacleData *Gitsn_DetectedObstacleData_gen(Dz1Error *err) { return Gitsn_DetectedObstacleData_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_DetectedObstacleData_copy(Gitsn_DetectedObstacleData *dst, Gitsn_DetectedObstacleData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObstacleData *Gitsn_DetectedObstacleData_clone(Gitsn_DetectedObstacleData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObstacleData_purge(Gitsn_DetectedObstacleData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObstacleData_del(Gitsn_DetectedObstacleData *p);
static __inline__ void Gitsn_DetectedObstacleData_delAndSetNull(void *ptr)
{
	Gitsn_DetectedObstacleData **p = (Gitsn_DetectedObstacleData **)ptr;
	if (p) { Gitsn_DetectedObstacleData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObstacleData_dump(Gitsn_DetectedObstacleData *p, int tab);
// Gitsn_DetectedObstacleData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectOptionalDataPresent
typedef enum Gitsn_DetectedObjectOptionalDataPresent
{
	Gitsn_DetectedObjectOptionalDataPresent_detVeh,
	Gitsn_DetectedObjectOptionalDataPresent_detVRU,
	Gitsn_DetectedObjectOptionalDataPresent_detObst,
	Gitsn_DetectedObjectOptionalDataPresent_max
} Gitsn_DetectedObjectOptionalDataPresent;

DZ1_CPPLINK str_t Gitsn_DetectedObjectOptionalDataPresentStrA(Gitsn_DetectedObjectOptionalDataPresent v);
DZ1_CPPLINK Gitsn_DetectedObjectOptionalDataPresent Gitsn_DetectedObjectOptionalDataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_DetectedObjectOptionalDataPresentStrW(Gitsn_DetectedObjectOptionalDataPresent v);
DZ1_CPPLINK Gitsn_DetectedObjectOptionalDataPresent Gitsn_DetectedObjectOptionalDataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_DetectedObjectOptionalDataPresentStr Gitsn_DetectedObjectOptionalDataPresentStrW
#define Gitsn_DetectedObjectOptionalDataPresentFromStr Gitsn_DetectedObjectOptionalDataPresentFromStrW
#else // UNICODE
#define Gitsn_DetectedObjectOptionalDataPresentStr Gitsn_DetectedObjectOptionalDataPresentStrA
#define Gitsn_DetectedObjectOptionalDataPresentFromStr Gitsn_DetectedObjectOptionalDataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_DetectedObjectOptionalDataPresentStr Gitsn_DetectedObjectOptionalDataPresentStrA
#define Gitsn_DetectedObjectOptionalDataPresentFromStr Gitsn_DetectedObjectOptionalDataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectOptionalDataPresent *Gitsn_DetectedObjectOptionalDataPresent_new(Gitsn_DetectedObjectOptionalDataPresent *src, Dz1Error *err);
static __inline__ Gitsn_DetectedObjectOptionalDataPresent *Gitsn_DetectedObjectOptionalDataPresent_gen(Dz1Error *err) { Gitsn_DetectedObjectOptionalDataPresent v = Gitsn_DetectedObjectOptionalDataPresent_max; return Gitsn_DetectedObjectOptionalDataPresent_new(&v, err); }
#define Gitsn_DetectedObjectOptionalDataPresent_clone             Gitsn_DetectedObjectOptionalDataPresent_new
static __inline__ void Gitsn_DetectedObjectOptionalDataPresent_del(Gitsn_DetectedObjectOptionalDataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_DetectedObjectOptionalDataPresent_delAndSetNull(void *ptr)
{
	Gitsn_DetectedObjectOptionalDataPresent **p = (Gitsn_DetectedObjectOptionalDataPresent **)ptr;
	if (p != NULL) { Gitsn_DetectedObjectOptionalDataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectOptionalDataPresent_dump(Gitsn_DetectedObjectOptionalDataPresent *v, int tab);
// Gitsn_DetectedObjectOptionalDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectOptionalData
typedef struct Gitsn_DetectedObjectOptionalData
{
	Gitsn_DetectedObjectOptionalDataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_DetectedVehicleData		*detVeh;
		Gitsn_DetectedVRUData			*detVRU;
		Gitsn_DetectedObstacleData		*detObst;
	} x;
} Gitsn_DetectedObjectOptionalData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectOptionalData *Gitsn_DetectedObjectOptionalData_new(Gitsn_DetectedObjectOptionalDataPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_DetectedObjectOptionalData *Gitsn_DetectedObjectOptionalData_gen(Dz1Error *err) { return Gitsn_DetectedObjectOptionalData_new(Gitsn_DetectedObjectOptionalDataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_DetectedObjectOptionalData_copy(Gitsn_DetectedObjectOptionalData *dst, Gitsn_DetectedObjectOptionalData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectOptionalData *Gitsn_DetectedObjectOptionalData_clone(Gitsn_DetectedObjectOptionalData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectOptionalData_purge(Gitsn_DetectedObjectOptionalData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectOptionalData_del(Gitsn_DetectedObjectOptionalData *p);
static __inline__ void Gitsn_DetectedObjectOptionalData_delAndSetNull(void *ptr)
{
	Gitsn_DetectedObjectOptionalData **p = (Gitsn_DetectedObjectOptionalData **)ptr;
	if (p != NULL) { Gitsn_DetectedObjectOptionalData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectOptionalData_dump(Gitsn_DetectedObjectOptionalData *p, int tab);
// Gitsn_DetectedObjectOptionalData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectData
typedef struct Gitsn_DetectedObjectData
{
	Gitsn_DetectedObjectCommonData		*detObjCommon;
	Gitsn_DetectedObjectOptionalData	*detObjOptData;
} Gitsn_DetectedObjectData;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectData *Gitsn_DetectedObjectData_new(Gitsn_DetectedObjectCommonData *detObjCommon, Dz1Error *err);
static __inline__ Gitsn_DetectedObjectData *Gitsn_DetectedObjectData_gen(Dz1Error *err) { return Gitsn_DetectedObjectData_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_DetectedObjectData_copy(Gitsn_DetectedObjectData *dst, Gitsn_DetectedObjectData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectData *Gitsn_DetectedObjectData_clone(Gitsn_DetectedObjectData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectData_purge(Gitsn_DetectedObjectData *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectData_del(Gitsn_DetectedObjectData *p);
static __inline__ void Gitsn_DetectedObjectData_delAndSetNull(void *ptr)
{
	Gitsn_DetectedObjectData **p = (Gitsn_DetectedObjectData **)ptr;
	if (p) { Gitsn_DetectedObjectData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectData_dump(Gitsn_DetectedObjectData *p, int tab);
// Gitsn_DetectedObjectData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectList
typedef struct Gitsn_DetectedObjectList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_DetectedObjectList *p);
	Dz1Error (*travel)(struct Gitsn_DetectedObjectList *p, Dz1Error (*func)(void *ptr, Gitsn_DetectedObjectData *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_DetectedObjectList *p, Dz1Error (*func)(void *ptr, Gitsn_DetectedObjectData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_DetectedObjectList *p, Dz1Error (*func)(void *ptr, Gitsn_DetectedObjectData *entry), void *ptr);
	Gitsn_DetectedObjectData **(*get_array)(struct Gitsn_DetectedObjectList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_DetectedObjectList *p, Gitsn_DetectedObjectData *data);
	Gitsn_DetectedObjectData *(*extract)(struct Gitsn_DetectedObjectList *p, Gitsn_DetectedObjectData *ptr);
	Gitsn_DetectedObjectData *(*getHead)(struct Gitsn_DetectedObjectList *p);
} Gitsn_DetectedObjectList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectList *Gitsn_DetectedObjectList_new(Dz1Error *err);
static __inline__ Gitsn_DetectedObjectList *Gitsn_DetectedObjectList_gen(Dz1Error *err) { return Gitsn_DetectedObjectList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_DetectedObjectList *Gitsn_DetectedObjectList_clone(Gitsn_DetectedObjectList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectList_purge(Gitsn_DetectedObjectList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectList_del(Gitsn_DetectedObjectList *p);
static __inline__ void Gitsn_DetectedObjectList_delAndSetNull(void *ptr)
{
	Gitsn_DetectedObjectList **p = (Gitsn_DetectedObjectList **)ptr;
	if (p != NULL) { Gitsn_DetectedObjectList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_DetectedObjectList_dump(Gitsn_DetectedObjectList *p, int tab);

// Gitsn_DetectedObjectList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SensorDataSharingMessage
typedef struct Gitsn_SensorDataSharingMessage
{
	Gitsn_MsgCount					 msgCnt;
	Gitsn_TemporaryID				 sourceID;
	Gitsn_EquipmentType				 equipmentType;
	Gitsn_DDateTime					*sDSMTimeStamp;
	Gitsn_Position3D				*refPos;
	Gitsn_PositionalAccuracy		*refPosXYConf;
	Gitsn_ElevationConfidence		 refPosElConf;
	Gitsn_DetectedObjectList		*objects;
} Gitsn_SensorDataSharingMessage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SensorDataSharingMessage *Gitsn_SensorDataSharingMessage_new(Gitsn_MsgCount msgCnt, 
																						   Gitsn_TemporaryID sourceID, 
																						   Gitsn_EquipmentType equipmentType, 
																						   Gitsn_DDateTime *sDSMTimeStamp, 
																						   Gitsn_Position3D *refPos, 
																						   Gitsn_PositionalAccuracy *refPosXYConf, 
																						   Gitsn_DetectedObjectList *objects, Dz1Error *err);
static __inline__ Gitsn_SensorDataSharingMessage *Gitsn_SensorDataSharingMessage_gen(Dz1Error *err) { return Gitsn_SensorDataSharingMessage_new(0, NULL, Gitsn_EquipmentType_max, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SensorDataSharingMessage_copy(Gitsn_SensorDataSharingMessage *dst, Gitsn_SensorDataSharingMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SensorDataSharingMessage *Gitsn_SensorDataSharingMessage_clone(Gitsn_SensorDataSharingMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorDataSharingMessage_purge(Gitsn_SensorDataSharingMessage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorDataSharingMessage_del(Gitsn_SensorDataSharingMessage *p);
static __inline__ void Gitsn_SensorDataSharingMessage_delAndSetNull(void *ptr)
{
	Gitsn_SensorDataSharingMessage **p = (Gitsn_SensorDataSharingMessage **)ptr;
	if (p) { Gitsn_SensorDataSharingMessage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorDataSharingMessage_dump(Gitsn_SensorDataSharingMessage *p, int tab);
// Gitsn_SensorDataSharingMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TLS
typedef struct Gitsn_TLS
{
	Gitsn_TrafficLightID					*trafficLightID;
	Gitsn_Latitude							 lat;
	Gitsn_Longitude							 lon;
	Gitsn_TrafficLightOperationStatus		*operationStatus;
	Gitsn_TrafficLightControllerStatus		*controllerStatus;
	Gitsn_TimeInSecond_B16					 cyclecounter;
	Gitsn_TimeInSecond_B16					 cycletime;
	Gitsn_DDateTime							*currentTime;
	Gitsn_TrafficLightStatusList			*trafficLightStatus;
} Gitsn_TLS;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TLS *Gitsn_TLS_new(Gitsn_TrafficLightID *trafficLightID, 
												 Gitsn_TrafficLightOperationStatus *operationStatus, 
												 Gitsn_TrafficLightControllerStatus *controllerStatus, 
												 Gitsn_TimeInSecond_B16 cyclecounter, 
												 Gitsn_TimeInSecond_B16 cycletime, 
												 Gitsn_DDateTime *currentTime, 
												 Gitsn_TrafficLightStatusList *trafficLightStatus, Dz1Error *err);
static __inline__ Gitsn_TLS *Gitsn_TLS_gen(Dz1Error *err) { return Gitsn_TLS_new(NULL, NULL, NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_TLS_copy(Gitsn_TLS *dst, Gitsn_TLS *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TLS *Gitsn_TLS_clone(Gitsn_TLS *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TLS_purge(Gitsn_TLS *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TLS_del(Gitsn_TLS *p);
static __inline__ void Gitsn_TLS_delAndSetNull(void *ptr)
{
	Gitsn_TLS **p = (Gitsn_TLS **)ptr;
	if (p) { Gitsn_TLS_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TLS_dump(Gitsn_TLS *p, int tab);
// Gitsn_TLS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightStatusMessage
typedef struct Gitsn_TrafficLightStatusMessage
{
	Gitsn_TrafficLightID_KOR				 trafficLightID;
	Gitsn_Latitude							 lat;
	Gitsn_Longitude							 lon;
	Gitsn_TrafficLightOperationStatus		*operationStatus;
	Gitsn_TrafficLightControllerStatus		*controllerStatus;
	Gitsn_TimeInSecond_B16					 cyclecounter;
	Gitsn_TimeInSecond_B16					 cycletime;
	Gitsn_DDateTime							*currentTime;
	Gitsn_TrafficLightStatusList			*trafficLightStatus;
} Gitsn_TrafficLightStatusMessage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightStatusMessage *Gitsn_TrafficLightStatusMessage_new(Gitsn_TrafficLightID_KOR trafficLightID, 
																							 Gitsn_TrafficLightOperationStatus *operationStatus, 
																							 Gitsn_TrafficLightControllerStatus *controllerStatus, 
																							 Gitsn_TimeInSecond_B16 cyclecounter, 
																							 Gitsn_TimeInSecond_B16 cycletime, 
																							 Gitsn_DDateTime *currentTime, 
																							 Gitsn_TrafficLightStatusList *trafficLightStatus, Dz1Error *err);
static __inline__ Gitsn_TrafficLightStatusMessage *Gitsn_TrafficLightStatusMessage_gen(Dz1Error *err) { return Gitsn_TrafficLightStatusMessage_new(0, NULL, NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_TrafficLightStatusMessage_copy(Gitsn_TrafficLightStatusMessage *dst, Gitsn_TrafficLightStatusMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TrafficLightStatusMessage *Gitsn_TrafficLightStatusMessage_clone(Gitsn_TrafficLightStatusMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatusMessage_purge(Gitsn_TrafficLightStatusMessage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatusMessage_del(Gitsn_TrafficLightStatusMessage *p);
static __inline__ void Gitsn_TrafficLightStatusMessage_delAndSetNull(void *ptr)
{
	Gitsn_TrafficLightStatusMessage **p = (Gitsn_TrafficLightStatusMessage **)ptr;
	if (p) { Gitsn_TrafficLightStatusMessage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TrafficLightStatusMessage_dump(Gitsn_TrafficLightStatusMessage *p, int tab);
// Gitsn_TrafficLightStatusMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ResponseType
typedef enum Gitsn_ResponseType
{
	Gitsn_ResponseType_notInUseOrNotEquipped = 0,
	Gitsn_ResponseType_emergency = 1,
	Gitsn_ResponseType_nonEmergency = 2,
	Gitsn_ResponseType_pursuit = 3,
	Gitsn_ResponseType_stationary = 4,
	Gitsn_ResponseType_slowMoving = 5,
	Gitsn_ResponseType_stopAndGoMovement = 6,
	Gitsn_ResponseType_max
} Gitsn_ResponseType;

DZ1_CPPLINK str_t Gitsn_ResponseTypeStrA(Gitsn_ResponseType v);
DZ1_CPPLINK Gitsn_ResponseType Gitsn_ResponseTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_ResponseTypeStrW(Gitsn_ResponseType v);
DZ1_CPPLINK Gitsn_ResponseType Gitsn_ResponseTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_ResponseTypeStr Gitsn_ResponseTypeStrW
#define Gitsn_ResponseTypeFromStr Gitsn_ResponseTypeFromStrW
#else // UNICODE
#define Gitsn_ResponseTypeStr Gitsn_ResponseTypeStrA
#define Gitsn_ResponseTypeFromStr Gitsn_ResponseTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_ResponseTypeStr Gitsn_ResponseTypeStrA
#define Gitsn_ResponseTypeFromStr Gitsn_ResponseTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ResponseType *Gitsn_ResponseType_new(Gitsn_ResponseType *src, Dz1Error *err);
static __inline__ Gitsn_ResponseType *Gitsn_ResponseType_gen(Dz1Error *err) { Gitsn_ResponseType v = Gitsn_ResponseType_max; return Gitsn_ResponseType_new(&v, err); }
#define Gitsn_ResponseType_clone             Gitsn_ResponseType_new
static __inline__ void Gitsn_ResponseType_del(Gitsn_ResponseType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_ResponseType_delAndSetNull(void *ptr)
{
	Gitsn_ResponseType **p = (Gitsn_ResponseType **)ptr;
	if (p != NULL) { Gitsn_ResponseType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ResponseType_dump(Gitsn_ResponseType *v, int tab);
// Gitsn_ResponseType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SirenInUse
typedef enum Gitsn_SirenInUse
{
	Gitsn_SirenInUse_unavailable = 0,
	Gitsn_SirenInUse_notInUse = 1,
	Gitsn_SirenInUse_inUse = 2,
	Gitsn_SirenInUse_reserved = 3,
	Gitsn_SirenInUse_max
} Gitsn_SirenInUse;

DZ1_CPPLINK str_t Gitsn_SirenInUseStrA(Gitsn_SirenInUse v);
DZ1_CPPLINK Gitsn_SirenInUse Gitsn_SirenInUseFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SirenInUseStrW(Gitsn_SirenInUse v);
DZ1_CPPLINK Gitsn_SirenInUse Gitsn_SirenInUseFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SirenInUseStr Gitsn_SirenInUseStrW
#define Gitsn_SirenInUseFromStr Gitsn_SirenInUseFromStrW
#else // UNICODE
#define Gitsn_SirenInUseStr Gitsn_SirenInUseStrA
#define Gitsn_SirenInUseFromStr Gitsn_SirenInUseFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SirenInUseStr Gitsn_SirenInUseStrA
#define Gitsn_SirenInUseFromStr Gitsn_SirenInUseFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SirenInUse *Gitsn_SirenInUse_new(Gitsn_SirenInUse *src, Dz1Error *err);
static __inline__ Gitsn_SirenInUse *Gitsn_SirenInUse_gen(Dz1Error *err) { Gitsn_SirenInUse v = Gitsn_SirenInUse_max; return Gitsn_SirenInUse_new(&v, err); }
#define Gitsn_SirenInUse_clone             Gitsn_SirenInUse_new
static __inline__ void Gitsn_SirenInUse_del(Gitsn_SirenInUse *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SirenInUse_delAndSetNull(void *ptr)
{
	Gitsn_SirenInUse **p = (Gitsn_SirenInUse **)ptr;
	if (p != NULL) { Gitsn_SirenInUse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SirenInUse_dump(Gitsn_SirenInUse *v, int tab);
// Gitsn_SirenInUse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MultiVehicleResponse
typedef enum Gitsn_MultiVehicleResponse
{
	Gitsn_MultiVehicleResponse_unavailable = 0,
	Gitsn_MultiVehicleResponse_singleVehicle = 1,
	Gitsn_MultiVehicleResponse_multiVehicle = 2,
	Gitsn_MultiVehicleResponse_reserved = 3,
	Gitsn_MultiVehicleResponse_max
} Gitsn_MultiVehicleResponse;

DZ1_CPPLINK str_t Gitsn_MultiVehicleResponseStrA(Gitsn_MultiVehicleResponse v);
DZ1_CPPLINK Gitsn_MultiVehicleResponse Gitsn_MultiVehicleResponseFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_MultiVehicleResponseStrW(Gitsn_MultiVehicleResponse v);
DZ1_CPPLINK Gitsn_MultiVehicleResponse Gitsn_MultiVehicleResponseFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_MultiVehicleResponseStr Gitsn_MultiVehicleResponseStrW
#define Gitsn_MultiVehicleResponseFromStr Gitsn_MultiVehicleResponseFromStrW
#else // UNICODE
#define Gitsn_MultiVehicleResponseStr Gitsn_MultiVehicleResponseStrA
#define Gitsn_MultiVehicleResponseFromStr Gitsn_MultiVehicleResponseFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_MultiVehicleResponseStr Gitsn_MultiVehicleResponseStrA
#define Gitsn_MultiVehicleResponseFromStr Gitsn_MultiVehicleResponseFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MultiVehicleResponse *Gitsn_MultiVehicleResponse_new(Gitsn_MultiVehicleResponse *src, Dz1Error *err);
static __inline__ Gitsn_MultiVehicleResponse *Gitsn_MultiVehicleResponse_gen(Dz1Error *err) { Gitsn_MultiVehicleResponse v = Gitsn_MultiVehicleResponse_max; return Gitsn_MultiVehicleResponse_new(&v, err); }
#define Gitsn_MultiVehicleResponse_clone             Gitsn_MultiVehicleResponse_new
static __inline__ void Gitsn_MultiVehicleResponse_del(Gitsn_MultiVehicleResponse *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_MultiVehicleResponse_delAndSetNull(void *ptr)
{
	Gitsn_MultiVehicleResponse **p = (Gitsn_MultiVehicleResponse **)ptr;
	if (p != NULL) { Gitsn_MultiVehicleResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MultiVehicleResponse_dump(Gitsn_MultiVehicleResponse *v, int tab);
// Gitsn_MultiVehicleResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PrivilegedEvents
typedef struct Gitsn_PrivilegedEvents
{
	Gitsn_SSPindex					 doNotUse;
	Gitsn_PrivilegedEventFlags		*event;
} Gitsn_PrivilegedEvents;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PrivilegedEvents *Gitsn_PrivilegedEvents_new(Gitsn_SSPindex doNotUse, 
																		   Gitsn_PrivilegedEventFlags *event, Dz1Error *err);
static __inline__ Gitsn_PrivilegedEvents *Gitsn_PrivilegedEvents_gen(Dz1Error *err) { return Gitsn_PrivilegedEvents_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_PrivilegedEvents_copy(Gitsn_PrivilegedEvents *dst, Gitsn_PrivilegedEvents *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PrivilegedEvents *Gitsn_PrivilegedEvents_clone(Gitsn_PrivilegedEvents *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PrivilegedEvents_purge(Gitsn_PrivilegedEvents *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PrivilegedEvents_del(Gitsn_PrivilegedEvents *p);
static __inline__ void Gitsn_PrivilegedEvents_delAndSetNull(void *ptr)
{
	Gitsn_PrivilegedEvents **p = (Gitsn_PrivilegedEvents **)ptr;
	if (p) { Gitsn_PrivilegedEvents_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PrivilegedEvents_dump(Gitsn_PrivilegedEvents *p, int tab);
// Gitsn_PrivilegedEvents
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EmergencyDetails
typedef struct Gitsn_EmergencyDetails
{
	Gitsn_SSPindex					 doNotUse;
	Gitsn_SirenInUse				 sirenUse;
	Gitsn_LightbarInUse				 lightsUse;
	Gitsn_MultiVehicleResponse		 multi;
	Gitsn_PrivilegedEvents			*events;
	Gitsn_ResponseType				 responseType;
} Gitsn_EmergencyDetails;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_EmergencyDetails *Gitsn_EmergencyDetails_new(Gitsn_SSPindex doNotUse, 
																		   Gitsn_SirenInUse sirenUse, 
																		   Gitsn_LightbarInUse lightsUse, 
																		   Gitsn_MultiVehicleResponse multi, Dz1Error *err);
static __inline__ Gitsn_EmergencyDetails *Gitsn_EmergencyDetails_gen(Dz1Error *err) { return Gitsn_EmergencyDetails_new(0, Gitsn_SirenInUse_max, Gitsn_LightbarInUse_max, Gitsn_MultiVehicleResponse_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_EmergencyDetails_copy(Gitsn_EmergencyDetails *dst, Gitsn_EmergencyDetails *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_EmergencyDetails *Gitsn_EmergencyDetails_clone(Gitsn_EmergencyDetails *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EmergencyDetails_purge(Gitsn_EmergencyDetails *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EmergencyDetails_del(Gitsn_EmergencyDetails *p);
static __inline__ void Gitsn_EmergencyDetails_delAndSetNull(void *ptr)
{
	Gitsn_EmergencyDetails **p = (Gitsn_EmergencyDetails **)ptr;
	if (p) { Gitsn_EmergencyDetails_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EmergencyDetails_dump(Gitsn_EmergencyDetails *p, int tab);
// Gitsn_EmergencyDetails
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EmergencyVehicleAlert
typedef struct Gitsn_EmergencyVehicleAlert
{
	Gitsn_MinuteOfTheYear				 timeStamp;
	Gitsn_TemporaryID					 id;
	Gitsn_RoadSideAlert					*rsaMsg;
	Gitsn_ResponseType					 responseType;
	Gitsn_EmergencyDetails				*details;
	Gitsn_VehicleMass					 mass;
	Gitsn_VehicleType					 basicType;
	Gitsn_VehicleGroupAffected			 vehicleType;
	Gitsn_IncidentResponseEquipment		 responseEquip;
	Gitsn_ResponderGroupAffected		 responderType;
} Gitsn_EmergencyVehicleAlert;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_EmergencyVehicleAlert *Gitsn_EmergencyVehicleAlert_new(Gitsn_RoadSideAlert *rsaMsg, Dz1Error *err);
static __inline__ Gitsn_EmergencyVehicleAlert *Gitsn_EmergencyVehicleAlert_gen(Dz1Error *err) { return Gitsn_EmergencyVehicleAlert_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_EmergencyVehicleAlert_copy(Gitsn_EmergencyVehicleAlert *dst, Gitsn_EmergencyVehicleAlert *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_EmergencyVehicleAlert *Gitsn_EmergencyVehicleAlert_clone(Gitsn_EmergencyVehicleAlert *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EmergencyVehicleAlert_purge(Gitsn_EmergencyVehicleAlert *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EmergencyVehicleAlert_del(Gitsn_EmergencyVehicleAlert *p);
static __inline__ void Gitsn_EmergencyVehicleAlert_delAndSetNull(void *ptr)
{
	Gitsn_EmergencyVehicleAlert **p = (Gitsn_EmergencyVehicleAlert **)ptr;
	if (p) { Gitsn_EmergencyVehicleAlert_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_EmergencyVehicleAlert_dump(Gitsn_EmergencyVehicleAlert *p, int tab);
// Gitsn_EmergencyVehicleAlert
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RTCM_Revision
typedef enum Gitsn_RTCM_Revision
{
	Gitsn_RTCM_Revision_unknown = 1,
	Gitsn_RTCM_Revision_rtcmRev2 = 2,
	Gitsn_RTCM_Revision_rtcmRev3 = 3,
	Gitsn_RTCM_Revision_reserved = 4,
	Gitsn_RTCM_Revision_max
} Gitsn_RTCM_Revision;

DZ1_CPPLINK str_t Gitsn_RTCM_RevisionStrA(Gitsn_RTCM_Revision v);
DZ1_CPPLINK Gitsn_RTCM_Revision Gitsn_RTCM_RevisionFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_RTCM_RevisionStrW(Gitsn_RTCM_Revision v);
DZ1_CPPLINK Gitsn_RTCM_Revision Gitsn_RTCM_RevisionFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_RTCM_RevisionStr Gitsn_RTCM_RevisionStrW
#define Gitsn_RTCM_RevisionFromStr Gitsn_RTCM_RevisionFromStrW
#else // UNICODE
#define Gitsn_RTCM_RevisionStr Gitsn_RTCM_RevisionStrA
#define Gitsn_RTCM_RevisionFromStr Gitsn_RTCM_RevisionFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_RTCM_RevisionStr Gitsn_RTCM_RevisionStrA
#define Gitsn_RTCM_RevisionFromStr Gitsn_RTCM_RevisionFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RTCM_Revision *Gitsn_RTCM_Revision_new(Gitsn_RTCM_Revision *src, Dz1Error *err);
static __inline__ Gitsn_RTCM_Revision *Gitsn_RTCM_Revision_gen(Dz1Error *err) { Gitsn_RTCM_Revision v = Gitsn_RTCM_Revision_max; return Gitsn_RTCM_Revision_new(&v, err); }
#define Gitsn_RTCM_Revision_clone             Gitsn_RTCM_Revision_new
static __inline__ void Gitsn_RTCM_Revision_del(Gitsn_RTCM_Revision *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_RTCM_Revision_delAndSetNull(void *ptr)
{
	Gitsn_RTCM_Revision **p = (Gitsn_RTCM_Revision **)ptr;
	if (p != NULL) { Gitsn_RTCM_Revision_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCM_Revision_dump(Gitsn_RTCM_Revision *v, int tab);
// Gitsn_RTCM_Revision
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AntennaOffsetSet
typedef struct Gitsn_AntennaOffsetSet
{
	Gitsn_Offset_B12	antOffsetX;
	Gitsn_Offset_B09	antOffsetY;
	Gitsn_Offset_B10	antOffsetZ;
} Gitsn_AntennaOffsetSet;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_AntennaOffsetSet *Gitsn_AntennaOffsetSet_new(Gitsn_Offset_B12 antOffsetX, 
																		   Gitsn_Offset_B09 antOffsetY, 
																		   Gitsn_Offset_B10 antOffsetZ, Dz1Error *err);
static __inline__ Gitsn_AntennaOffsetSet *Gitsn_AntennaOffsetSet_gen(Dz1Error *err) { return Gitsn_AntennaOffsetSet_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_AntennaOffsetSet_copy(Gitsn_AntennaOffsetSet *dst, Gitsn_AntennaOffsetSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AntennaOffsetSet *Gitsn_AntennaOffsetSet_clone(Gitsn_AntennaOffsetSet *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AntennaOffsetSet_purge(Gitsn_AntennaOffsetSet *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AntennaOffsetSet_del(Gitsn_AntennaOffsetSet *p);
static __inline__ void Gitsn_AntennaOffsetSet_delAndSetNull(void *ptr)
{
	Gitsn_AntennaOffsetSet **p = (Gitsn_AntennaOffsetSet **)ptr;
	if (p) { Gitsn_AntennaOffsetSet_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AntennaOffsetSet_dump(Gitsn_AntennaOffsetSet *p, int tab);
// Gitsn_AntennaOffsetSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RTCMheader
typedef struct Gitsn_RTCMheader
{
	Gitsn_GNSSstatus			*status;
	Gitsn_AntennaOffsetSet		*offsetSet;
} Gitsn_RTCMheader;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RTCMheader *Gitsn_RTCMheader_new(Gitsn_GNSSstatus *status, 
															   Gitsn_AntennaOffsetSet *offsetSet, Dz1Error *err);
static __inline__ Gitsn_RTCMheader *Gitsn_RTCMheader_gen(Dz1Error *err) { return Gitsn_RTCMheader_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RTCMheader_copy(Gitsn_RTCMheader *dst, Gitsn_RTCMheader *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RTCMheader *Gitsn_RTCMheader_clone(Gitsn_RTCMheader *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMheader_purge(Gitsn_RTCMheader *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMheader_del(Gitsn_RTCMheader *p);
static __inline__ void Gitsn_RTCMheader_delAndSetNull(void *ptr)
{
	Gitsn_RTCMheader **p = (Gitsn_RTCMheader **)ptr;
	if (p) { Gitsn_RTCMheader_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMheader_dump(Gitsn_RTCMheader *p, int tab);
// Gitsn_RTCMheader
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RTCMmessageList
typedef struct Gitsn_RTCMmessageList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_RTCMmessageList *p);
	Dz1Error (*travel)(struct Gitsn_RTCMmessageList *p, Dz1Error (*func)(void *ptr, Gitsn_RTCMmessage entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_RTCMmessageList *p, Dz1Error (*func)(void *ptr, Gitsn_RTCMmessage entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_RTCMmessageList *p, Dz1Error (*func)(void *ptr, Gitsn_RTCMmessage entry), void *ptr);
	Gitsn_RTCMmessage *(*get_array)(struct Gitsn_RTCMmessageList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_RTCMmessageList *p, Gitsn_RTCMmessage data);
	Gitsn_RTCMmessage (*extract)(struct Gitsn_RTCMmessageList *p, Gitsn_RTCMmessage ptr);
	Gitsn_RTCMmessage (*getHead)(struct Gitsn_RTCMmessageList *p);
	int (*cmp)(Gitsn_RTCMmessage a, Gitsn_RTCMmessage b);
} Gitsn_RTCMmessageList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RTCMmessageList *Gitsn_RTCMmessageList_new(Dz1Error *err);
static __inline__ Gitsn_RTCMmessageList *Gitsn_RTCMmessageList_gen(Dz1Error *err) { return Gitsn_RTCMmessageList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RTCMmessageList *Gitsn_RTCMmessageList_clone(Gitsn_RTCMmessageList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMmessageList_purge(Gitsn_RTCMmessageList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMmessageList_del(Gitsn_RTCMmessageList *p);
static __inline__ void Gitsn_RTCMmessageList_delAndSetNull(void *ptr)
{
	Gitsn_RTCMmessageList **p = (Gitsn_RTCMmessageList **)ptr;
	if (p != NULL) { Gitsn_RTCMmessageList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMmessageListA_dump(Gitsn_RTCMmessageList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMmessageListA_fdump(FILE *fp, Gitsn_RTCMmessageList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMmessageListW_dump(Gitsn_RTCMmessageList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMmessageListW_fdump(FILE *fp, Gitsn_RTCMmessageList *p, int tab);
#ifdef UNICODE
#define Gitsn_RTCMmessageList_dump Gitsn_RTCMmessageListW_dump
#define Gitsn_RTCMmessageList_fdump Gitsn_RTCMmessageListW_fdump
#else //  UNICODE
#define Gitsn_RTCMmessageList_dump Gitsn_RTCMmessageListA_dump
#define Gitsn_RTCMmessageList_fdump Gitsn_RTCMmessageListA_fdump
#endif //  UNICODE
static __inline__ void Gitsn_RTCMmessageListX_dump(Gitsn_RTCMmessageList *p, int tab) { DZ1_DUMP(Gitsn_RTCMmessageList, p, tab); }
static __inline__ void Gitsn_RTCMmessageListX_fdump(FILE *fp, Gitsn_RTCMmessageList *p, int tab) { DZ1_FDUMP(fp, Gitsn_RTCMmessageList, p, tab); }
#else // UNIX_SYSTEM
#define Gitsn_RTCMmessageList_dump Gitsn_RTCMmessageListA_dump
#define Gitsn_RTCMmessageListX_dump Gitsn_RTCMmessageListA_dump
#define Gitsn_RTCMmessageList_fdump Gitsn_RTCMmessageListA_fdump
#define Gitsn_RTCMmessageListX_fdump Gitsn_RTCMmessageListA_fdump
#endif // UNIX_SYSTEM

// Gitsn_RTCMmessageList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RTCMcorrections
typedef struct Gitsn_RTCMcorrections
{
	Gitsn_MsgCount				 msgCnt;
	Gitsn_RTCM_Revision			 rev;
	Gitsn_MinuteOfTheYear		 timeStamp;
	Gitsn_FullPositionVector	*anchorPoint;
	Gitsn_RTCMheader			*rtcmHeader;
	Gitsn_RTCMmessageList		*msgs;
} Gitsn_RTCMcorrections;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RTCMcorrections *Gitsn_RTCMcorrections_new(Gitsn_MsgCount msgCnt, 
																		 Gitsn_RTCM_Revision rev, 
																		 Gitsn_RTCMmessageList *msgs, Dz1Error *err);
static __inline__ Gitsn_RTCMcorrections *Gitsn_RTCMcorrections_gen(Dz1Error *err) { return Gitsn_RTCMcorrections_new(0, Gitsn_RTCM_Revision_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RTCMcorrections_copy(Gitsn_RTCMcorrections *dst, Gitsn_RTCMcorrections *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RTCMcorrections *Gitsn_RTCMcorrections_clone(Gitsn_RTCMcorrections *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMcorrections_purge(Gitsn_RTCMcorrections *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMcorrections_del(Gitsn_RTCMcorrections *p);
static __inline__ void Gitsn_RTCMcorrections_delAndSetNull(void *ptr)
{
	Gitsn_RTCMcorrections **p = (Gitsn_RTCMcorrections **)ptr;
	if (p) { Gitsn_RTCMcorrections_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RTCMcorrections_dump(Gitsn_RTCMcorrections *p, int tab);
// Gitsn_RTCMcorrections
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PriorityRequestType
typedef enum Gitsn_PriorityRequestType
{
	Gitsn_PriorityRequestType_priorityRequestTypeReserved = 0,
	Gitsn_PriorityRequestType_priorityRequest = 1,
	Gitsn_PriorityRequestType_priorityRequestUpdate = 2,
	Gitsn_PriorityRequestType_priorityCancellation = 3,
	Gitsn_PriorityRequestType_max
} Gitsn_PriorityRequestType;

DZ1_CPPLINK str_t Gitsn_PriorityRequestTypeStrA(Gitsn_PriorityRequestType v);
DZ1_CPPLINK Gitsn_PriorityRequestType Gitsn_PriorityRequestTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_PriorityRequestTypeStrW(Gitsn_PriorityRequestType v);
DZ1_CPPLINK Gitsn_PriorityRequestType Gitsn_PriorityRequestTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_PriorityRequestTypeStr Gitsn_PriorityRequestTypeStrW
#define Gitsn_PriorityRequestTypeFromStr Gitsn_PriorityRequestTypeFromStrW
#else // UNICODE
#define Gitsn_PriorityRequestTypeStr Gitsn_PriorityRequestTypeStrA
#define Gitsn_PriorityRequestTypeFromStr Gitsn_PriorityRequestTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_PriorityRequestTypeStr Gitsn_PriorityRequestTypeStrA
#define Gitsn_PriorityRequestTypeFromStr Gitsn_PriorityRequestTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PriorityRequestType *Gitsn_PriorityRequestType_new(Gitsn_PriorityRequestType *src, Dz1Error *err);
static __inline__ Gitsn_PriorityRequestType *Gitsn_PriorityRequestType_gen(Dz1Error *err) { Gitsn_PriorityRequestType v = Gitsn_PriorityRequestType_max; return Gitsn_PriorityRequestType_new(&v, err); }
#define Gitsn_PriorityRequestType_clone             Gitsn_PriorityRequestType_new
static __inline__ void Gitsn_PriorityRequestType_del(Gitsn_PriorityRequestType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_PriorityRequestType_delAndSetNull(void *ptr)
{
	Gitsn_PriorityRequestType **p = (Gitsn_PriorityRequestType **)ptr;
	if (p != NULL) { Gitsn_PriorityRequestType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PriorityRequestType_dump(Gitsn_PriorityRequestType *v, int tab);
// Gitsn_PriorityRequestType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionAccessPointPresent
typedef enum Gitsn_IntersectionAccessPointPresent
{
	Gitsn_IntersectionAccessPointPresent_lane,
	Gitsn_IntersectionAccessPointPresent_approach,
	Gitsn_IntersectionAccessPointPresent_connection,
	Gitsn_IntersectionAccessPointPresent_max
} Gitsn_IntersectionAccessPointPresent;

DZ1_CPPLINK str_t Gitsn_IntersectionAccessPointPresentStrA(Gitsn_IntersectionAccessPointPresent v);
DZ1_CPPLINK Gitsn_IntersectionAccessPointPresent Gitsn_IntersectionAccessPointPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_IntersectionAccessPointPresentStrW(Gitsn_IntersectionAccessPointPresent v);
DZ1_CPPLINK Gitsn_IntersectionAccessPointPresent Gitsn_IntersectionAccessPointPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_IntersectionAccessPointPresentStr Gitsn_IntersectionAccessPointPresentStrW
#define Gitsn_IntersectionAccessPointPresentFromStr Gitsn_IntersectionAccessPointPresentFromStrW
#else // UNICODE
#define Gitsn_IntersectionAccessPointPresentStr Gitsn_IntersectionAccessPointPresentStrA
#define Gitsn_IntersectionAccessPointPresentFromStr Gitsn_IntersectionAccessPointPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_IntersectionAccessPointPresentStr Gitsn_IntersectionAccessPointPresentStrA
#define Gitsn_IntersectionAccessPointPresentFromStr Gitsn_IntersectionAccessPointPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionAccessPointPresent *Gitsn_IntersectionAccessPointPresent_new(Gitsn_IntersectionAccessPointPresent *src, Dz1Error *err);
static __inline__ Gitsn_IntersectionAccessPointPresent *Gitsn_IntersectionAccessPointPresent_gen(Dz1Error *err) { Gitsn_IntersectionAccessPointPresent v = Gitsn_IntersectionAccessPointPresent_max; return Gitsn_IntersectionAccessPointPresent_new(&v, err); }
#define Gitsn_IntersectionAccessPointPresent_clone             Gitsn_IntersectionAccessPointPresent_new
static __inline__ void Gitsn_IntersectionAccessPointPresent_del(Gitsn_IntersectionAccessPointPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_IntersectionAccessPointPresent_delAndSetNull(void *ptr)
{
	Gitsn_IntersectionAccessPointPresent **p = (Gitsn_IntersectionAccessPointPresent **)ptr;
	if (p != NULL) { Gitsn_IntersectionAccessPointPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionAccessPointPresent_dump(Gitsn_IntersectionAccessPointPresent *v, int tab);
// Gitsn_IntersectionAccessPointPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionAccessPoint
typedef struct Gitsn_IntersectionAccessPoint
{
	Gitsn_IntersectionAccessPointPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_LaneID				lane;
		Gitsn_ApproachID			approach;
		Gitsn_LaneConnectionID		connection;
	} x;
} Gitsn_IntersectionAccessPoint;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionAccessPoint *Gitsn_IntersectionAccessPoint_new(Gitsn_IntersectionAccessPointPresent present, void *ptr, Dz1Error *err);
static __inline__ Gitsn_IntersectionAccessPoint *Gitsn_IntersectionAccessPoint_gen(Dz1Error *err) { return Gitsn_IntersectionAccessPoint_new(Gitsn_IntersectionAccessPointPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Gitsn_IntersectionAccessPoint_copy(Gitsn_IntersectionAccessPoint *dst, Gitsn_IntersectionAccessPoint *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IntersectionAccessPoint *Gitsn_IntersectionAccessPoint_clone(Gitsn_IntersectionAccessPoint *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionAccessPoint_purge(Gitsn_IntersectionAccessPoint *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionAccessPoint_del(Gitsn_IntersectionAccessPoint *p);
static __inline__ void Gitsn_IntersectionAccessPoint_delAndSetNull(void *ptr)
{
	Gitsn_IntersectionAccessPoint **p = (Gitsn_IntersectionAccessPoint **)ptr;
	if (p != NULL) { Gitsn_IntersectionAccessPoint_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IntersectionAccessPoint_dump(Gitsn_IntersectionAccessPoint *p, int tab);
// Gitsn_IntersectionAccessPoint
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalRequest
typedef struct Gitsn_SignalRequest
{
	Gitsn_IntersectionReferenceID		*id;
	Gitsn_RequestID						 requestID;
	Gitsn_PriorityRequestType			 requestType;
	Gitsn_IntersectionAccessPoint		*inBoundLane;
	Gitsn_IntersectionAccessPoint		*outBoundLane;
} Gitsn_SignalRequest;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequest *Gitsn_SignalRequest_new(Gitsn_IntersectionReferenceID *id, 
																	 Gitsn_RequestID requestID, 
																	 Gitsn_PriorityRequestType requestType, Dz1Error *err);
static __inline__ Gitsn_SignalRequest *Gitsn_SignalRequest_gen(Dz1Error *err) { return Gitsn_SignalRequest_new(NULL, 0, Gitsn_PriorityRequestType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SignalRequest_copy(Gitsn_SignalRequest *dst, Gitsn_SignalRequest *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequest *Gitsn_SignalRequest_clone(Gitsn_SignalRequest *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequest_purge(Gitsn_SignalRequest *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequest_del(Gitsn_SignalRequest *p);
static __inline__ void Gitsn_SignalRequest_delAndSetNull(void *ptr)
{
	Gitsn_SignalRequest **p = (Gitsn_SignalRequest **)ptr;
	if (p) { Gitsn_SignalRequest_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequest_dump(Gitsn_SignalRequest *p, int tab);
// Gitsn_SignalRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalRequestPackage
typedef struct Gitsn_SignalRequestPackage
{
	Gitsn_SignalRequest			*request;
	Gitsn_MinuteOfTheYear		 minute;
	Gitsn_DSecond				 second;
	Gitsn_DSecond				 duration;
} Gitsn_SignalRequestPackage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequestPackage *Gitsn_SignalRequestPackage_new(Gitsn_SignalRequest *request, Dz1Error *err);
static __inline__ Gitsn_SignalRequestPackage *Gitsn_SignalRequestPackage_gen(Dz1Error *err) { return Gitsn_SignalRequestPackage_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SignalRequestPackage_copy(Gitsn_SignalRequestPackage *dst, Gitsn_SignalRequestPackage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequestPackage *Gitsn_SignalRequestPackage_clone(Gitsn_SignalRequestPackage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestPackage_purge(Gitsn_SignalRequestPackage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestPackage_del(Gitsn_SignalRequestPackage *p);
static __inline__ void Gitsn_SignalRequestPackage_delAndSetNull(void *ptr)
{
	Gitsn_SignalRequestPackage **p = (Gitsn_SignalRequestPackage **)ptr;
	if (p) { Gitsn_SignalRequestPackage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestPackage_dump(Gitsn_SignalRequestPackage *p, int tab);
// Gitsn_SignalRequestPackage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalRequestList
typedef struct Gitsn_SignalRequestList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_SignalRequestList *p);
	Dz1Error (*travel)(struct Gitsn_SignalRequestList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalRequestPackage *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_SignalRequestList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalRequestPackage *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_SignalRequestList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalRequestPackage *entry), void *ptr);
	Gitsn_SignalRequestPackage **(*get_array)(struct Gitsn_SignalRequestList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_SignalRequestList *p, Gitsn_SignalRequestPackage *data);
	Gitsn_SignalRequestPackage *(*extract)(struct Gitsn_SignalRequestList *p, Gitsn_SignalRequestPackage *ptr);
	Gitsn_SignalRequestPackage *(*getHead)(struct Gitsn_SignalRequestList *p);
} Gitsn_SignalRequestList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequestList *Gitsn_SignalRequestList_new(Dz1Error *err);
static __inline__ Gitsn_SignalRequestList *Gitsn_SignalRequestList_gen(Dz1Error *err) { return Gitsn_SignalRequestList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequestList *Gitsn_SignalRequestList_clone(Gitsn_SignalRequestList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestList_purge(Gitsn_SignalRequestList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestList_del(Gitsn_SignalRequestList *p);
static __inline__ void Gitsn_SignalRequestList_delAndSetNull(void *ptr)
{
	Gitsn_SignalRequestList **p = (Gitsn_SignalRequestList **)ptr;
	if (p != NULL) { Gitsn_SignalRequestList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestList_dump(Gitsn_SignalRequestList *p, int tab);

// Gitsn_SignalRequestList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RequestSubRole
typedef enum Gitsn_RequestSubRole
{
	Gitsn_RequestSubRole_requestSubRoleUnKnown = 0,
	Gitsn_RequestSubRole_requestSubRole1 = 1,
	Gitsn_RequestSubRole_requestSubRole2 = 2,
	Gitsn_RequestSubRole_requestSubRole3 = 3,
	Gitsn_RequestSubRole_requestSubRole4 = 4,
	Gitsn_RequestSubRole_requestSubRole5 = 5,
	Gitsn_RequestSubRole_requestSubRole6 = 6,
	Gitsn_RequestSubRole_requestSubRole7 = 7,
	Gitsn_RequestSubRole_requestSubRole8 = 8,
	Gitsn_RequestSubRole_requestSubRole9 = 9,
	Gitsn_RequestSubRole_requestSubRole10 = 10,
	Gitsn_RequestSubRole_requestSubRole11 = 11,
	Gitsn_RequestSubRole_requestSubRole12 = 12,
	Gitsn_RequestSubRole_requestSubRole13 = 13,
	Gitsn_RequestSubRole_requestSubRole14 = 14,
	Gitsn_RequestSubRole_requestSubRoleReserved = 15,
	Gitsn_RequestSubRole_max
} Gitsn_RequestSubRole;

DZ1_CPPLINK str_t Gitsn_RequestSubRoleStrA(Gitsn_RequestSubRole v);
DZ1_CPPLINK Gitsn_RequestSubRole Gitsn_RequestSubRoleFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_RequestSubRoleStrW(Gitsn_RequestSubRole v);
DZ1_CPPLINK Gitsn_RequestSubRole Gitsn_RequestSubRoleFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_RequestSubRoleStr Gitsn_RequestSubRoleStrW
#define Gitsn_RequestSubRoleFromStr Gitsn_RequestSubRoleFromStrW
#else // UNICODE
#define Gitsn_RequestSubRoleStr Gitsn_RequestSubRoleStrA
#define Gitsn_RequestSubRoleFromStr Gitsn_RequestSubRoleFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_RequestSubRoleStr Gitsn_RequestSubRoleStrA
#define Gitsn_RequestSubRoleFromStr Gitsn_RequestSubRoleFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RequestSubRole *Gitsn_RequestSubRole_new(Gitsn_RequestSubRole *src, Dz1Error *err);
static __inline__ Gitsn_RequestSubRole *Gitsn_RequestSubRole_gen(Dz1Error *err) { Gitsn_RequestSubRole v = Gitsn_RequestSubRole_max; return Gitsn_RequestSubRole_new(&v, err); }
#define Gitsn_RequestSubRole_clone             Gitsn_RequestSubRole_new
static __inline__ void Gitsn_RequestSubRole_del(Gitsn_RequestSubRole *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_RequestSubRole_delAndSetNull(void *ptr)
{
	Gitsn_RequestSubRole **p = (Gitsn_RequestSubRole **)ptr;
	if (p != NULL) { Gitsn_RequestSubRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestSubRole_dump(Gitsn_RequestSubRole *v, int tab);
// Gitsn_RequestSubRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RequestImportanceLevel
typedef enum Gitsn_RequestImportanceLevel
{
	Gitsn_RequestImportanceLevel_requestImportanceLevelUnKnown = 0,
	Gitsn_RequestImportanceLevel_requestImportanceLevel1 = 1,
	Gitsn_RequestImportanceLevel_requestImportanceLevel2 = 2,
	Gitsn_RequestImportanceLevel_requestImportanceLevel3 = 3,
	Gitsn_RequestImportanceLevel_requestImportanceLevel4 = 4,
	Gitsn_RequestImportanceLevel_requestImportanceLevel5 = 5,
	Gitsn_RequestImportanceLevel_requestImportanceLevel6 = 6,
	Gitsn_RequestImportanceLevel_requestImportanceLevel7 = 7,
	Gitsn_RequestImportanceLevel_requestImportanceLevel8 = 8,
	Gitsn_RequestImportanceLevel_requestImportanceLevel9 = 9,
	Gitsn_RequestImportanceLevel_requestImportanceLevel10 = 10,
	Gitsn_RequestImportanceLevel_requestImportanceLevel11 = 11,
	Gitsn_RequestImportanceLevel_requestImportanceLevel12 = 12,
	Gitsn_RequestImportanceLevel_requestImportanceLevel13 = 13,
	Gitsn_RequestImportanceLevel_requestImportanceLevel14 = 14,
	Gitsn_RequestImportanceLevel_requestImportanceReserved = 15,
	Gitsn_RequestImportanceLevel_max
} Gitsn_RequestImportanceLevel;

DZ1_CPPLINK str_t Gitsn_RequestImportanceLevelStrA(Gitsn_RequestImportanceLevel v);
DZ1_CPPLINK Gitsn_RequestImportanceLevel Gitsn_RequestImportanceLevelFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_RequestImportanceLevelStrW(Gitsn_RequestImportanceLevel v);
DZ1_CPPLINK Gitsn_RequestImportanceLevel Gitsn_RequestImportanceLevelFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_RequestImportanceLevelStr Gitsn_RequestImportanceLevelStrW
#define Gitsn_RequestImportanceLevelFromStr Gitsn_RequestImportanceLevelFromStrW
#else // UNICODE
#define Gitsn_RequestImportanceLevelStr Gitsn_RequestImportanceLevelStrA
#define Gitsn_RequestImportanceLevelFromStr Gitsn_RequestImportanceLevelFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_RequestImportanceLevelStr Gitsn_RequestImportanceLevelStrA
#define Gitsn_RequestImportanceLevelFromStr Gitsn_RequestImportanceLevelFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RequestImportanceLevel *Gitsn_RequestImportanceLevel_new(Gitsn_RequestImportanceLevel *src, Dz1Error *err);
static __inline__ Gitsn_RequestImportanceLevel *Gitsn_RequestImportanceLevel_gen(Dz1Error *err) { Gitsn_RequestImportanceLevel v = Gitsn_RequestImportanceLevel_max; return Gitsn_RequestImportanceLevel_new(&v, err); }
#define Gitsn_RequestImportanceLevel_clone             Gitsn_RequestImportanceLevel_new
static __inline__ void Gitsn_RequestImportanceLevel_del(Gitsn_RequestImportanceLevel *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_RequestImportanceLevel_delAndSetNull(void *ptr)
{
	Gitsn_RequestImportanceLevel **p = (Gitsn_RequestImportanceLevel **)ptr;
	if (p != NULL) { Gitsn_RequestImportanceLevel_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestImportanceLevel_dump(Gitsn_RequestImportanceLevel *v, int tab);
// Gitsn_RequestImportanceLevel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RequestorType
typedef struct Gitsn_RequestorType
{
	Gitsn_BasicVehicleRole			role;
	Gitsn_RequestSubRole			subrole;
	Gitsn_RequestImportanceLevel	request;
	Gitsn_Iso3833VehicleType		iso3883;
	Gitsn_VehicleType				hpmsType;
} Gitsn_RequestorType;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RequestorType *Gitsn_RequestorType_new(Gitsn_BasicVehicleRole role, Dz1Error *err);
static __inline__ Gitsn_RequestorType *Gitsn_RequestorType_gen(Dz1Error *err) { return Gitsn_RequestorType_new(Gitsn_BasicVehicleRole_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RequestorType_copy(Gitsn_RequestorType *dst, Gitsn_RequestorType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RequestorType *Gitsn_RequestorType_clone(Gitsn_RequestorType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorType_purge(Gitsn_RequestorType *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorType_del(Gitsn_RequestorType *p);
static __inline__ void Gitsn_RequestorType_delAndSetNull(void *ptr)
{
	Gitsn_RequestorType **p = (Gitsn_RequestorType **)ptr;
	if (p) { Gitsn_RequestorType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorType_dump(Gitsn_RequestorType *p, int tab);
// Gitsn_RequestorType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RequestorPositionVector
typedef struct Gitsn_RequestorPositionVector
{
	Gitsn_Position3D				*position;
	Gitsn_Angle						 heading;
	Gitsn_TransmissionAndSpeed		*speed;
} Gitsn_RequestorPositionVector;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RequestorPositionVector *Gitsn_RequestorPositionVector_new(Gitsn_Position3D *position, Dz1Error *err);
static __inline__ Gitsn_RequestorPositionVector *Gitsn_RequestorPositionVector_gen(Dz1Error *err) { return Gitsn_RequestorPositionVector_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RequestorPositionVector_copy(Gitsn_RequestorPositionVector *dst, Gitsn_RequestorPositionVector *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RequestorPositionVector *Gitsn_RequestorPositionVector_clone(Gitsn_RequestorPositionVector *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorPositionVector_purge(Gitsn_RequestorPositionVector *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorPositionVector_del(Gitsn_RequestorPositionVector *p);
static __inline__ void Gitsn_RequestorPositionVector_delAndSetNull(void *ptr)
{
	Gitsn_RequestorPositionVector **p = (Gitsn_RequestorPositionVector **)ptr;
	if (p) { Gitsn_RequestorPositionVector_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorPositionVector_dump(Gitsn_RequestorPositionVector *p, int tab);
// Gitsn_RequestorPositionVector
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TransitVehicleOccupancy
typedef enum Gitsn_TransitVehicleOccupancy
{
	Gitsn_TransitVehicleOccupancy_occupancyUnknown = 0,
	Gitsn_TransitVehicleOccupancy_occupancyEmpty = 1,
	Gitsn_TransitVehicleOccupancy_occupancyVeryLow = 2,
	Gitsn_TransitVehicleOccupancy_occupancyLow = 3,
	Gitsn_TransitVehicleOccupancy_occupancyMed = 4,
	Gitsn_TransitVehicleOccupancy_occupancyHigh = 5,
	Gitsn_TransitVehicleOccupancy_occupancyNearlyFull = 6,
	Gitsn_TransitVehicleOccupancy_occupancyFull = 7,
	Gitsn_TransitVehicleOccupancy_max
} Gitsn_TransitVehicleOccupancy;

DZ1_CPPLINK str_t Gitsn_TransitVehicleOccupancyStrA(Gitsn_TransitVehicleOccupancy v);
DZ1_CPPLINK Gitsn_TransitVehicleOccupancy Gitsn_TransitVehicleOccupancyFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_TransitVehicleOccupancyStrW(Gitsn_TransitVehicleOccupancy v);
DZ1_CPPLINK Gitsn_TransitVehicleOccupancy Gitsn_TransitVehicleOccupancyFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_TransitVehicleOccupancyStr Gitsn_TransitVehicleOccupancyStrW
#define Gitsn_TransitVehicleOccupancyFromStr Gitsn_TransitVehicleOccupancyFromStrW
#else // UNICODE
#define Gitsn_TransitVehicleOccupancyStr Gitsn_TransitVehicleOccupancyStrA
#define Gitsn_TransitVehicleOccupancyFromStr Gitsn_TransitVehicleOccupancyFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_TransitVehicleOccupancyStr Gitsn_TransitVehicleOccupancyStrA
#define Gitsn_TransitVehicleOccupancyFromStr Gitsn_TransitVehicleOccupancyFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_TransitVehicleOccupancy *Gitsn_TransitVehicleOccupancy_new(Gitsn_TransitVehicleOccupancy *src, Dz1Error *err);
static __inline__ Gitsn_TransitVehicleOccupancy *Gitsn_TransitVehicleOccupancy_gen(Dz1Error *err) { Gitsn_TransitVehicleOccupancy v = Gitsn_TransitVehicleOccupancy_max; return Gitsn_TransitVehicleOccupancy_new(&v, err); }
#define Gitsn_TransitVehicleOccupancy_clone             Gitsn_TransitVehicleOccupancy_new
static __inline__ void Gitsn_TransitVehicleOccupancy_del(Gitsn_TransitVehicleOccupancy *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_TransitVehicleOccupancy_delAndSetNull(void *ptr)
{
	Gitsn_TransitVehicleOccupancy **p = (Gitsn_TransitVehicleOccupancy **)ptr;
	if (p != NULL) { Gitsn_TransitVehicleOccupancy_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_TransitVehicleOccupancy_dump(Gitsn_TransitVehicleOccupancy *v, int tab);
// Gitsn_TransitVehicleOccupancy
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RequestorDescription
typedef struct Gitsn_RequestorDescription
{
	Gitsn_VehicleID						*id;
	Gitsn_RequestorType					*type;
	Gitsn_RequestorPositionVector		*position;
	Gitsn_DescriptiveName				 name;
	Gitsn_DescriptiveName				 routeName;
	Gitsn_TransitVehicleStatus			*transitStatus;
	Gitsn_TransitVehicleOccupancy		 transitOccupancy;
	Gitsn_DeltaTime						 transitSchedule;
} Gitsn_RequestorDescription;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_RequestorDescription *Gitsn_RequestorDescription_new(Gitsn_VehicleID *id, Dz1Error *err);
static __inline__ Gitsn_RequestorDescription *Gitsn_RequestorDescription_gen(Dz1Error *err) { return Gitsn_RequestorDescription_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_RequestorDescription_copy(Gitsn_RequestorDescription *dst, Gitsn_RequestorDescription *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_RequestorDescription *Gitsn_RequestorDescription_clone(Gitsn_RequestorDescription *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorDescription_purge(Gitsn_RequestorDescription *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorDescription_del(Gitsn_RequestorDescription *p);
static __inline__ void Gitsn_RequestorDescription_delAndSetNull(void *ptr)
{
	Gitsn_RequestorDescription **p = (Gitsn_RequestorDescription **)ptr;
	if (p) { Gitsn_RequestorDescription_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_RequestorDescription_dump(Gitsn_RequestorDescription *p, int tab);
// Gitsn_RequestorDescription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalRequestMessage
typedef struct Gitsn_SignalRequestMessage
{
	Gitsn_MinuteOfTheYear			 timeStamp;
	Gitsn_DSecond					 second;
	Gitsn_MsgCount					 sequenceNumber;
	Gitsn_SignalRequestList			*requests;
	Gitsn_RequestorDescription		*requestor;
} Gitsn_SignalRequestMessage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequestMessage *Gitsn_SignalRequestMessage_new(Gitsn_DSecond second, 
																				   Gitsn_RequestorDescription *requestor, Dz1Error *err);
static __inline__ Gitsn_SignalRequestMessage *Gitsn_SignalRequestMessage_gen(Dz1Error *err) { return Gitsn_SignalRequestMessage_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SignalRequestMessage_copy(Gitsn_SignalRequestMessage *dst, Gitsn_SignalRequestMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequestMessage *Gitsn_SignalRequestMessage_clone(Gitsn_SignalRequestMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestMessage_purge(Gitsn_SignalRequestMessage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestMessage_del(Gitsn_SignalRequestMessage *p);
static __inline__ void Gitsn_SignalRequestMessage_delAndSetNull(void *ptr)
{
	Gitsn_SignalRequestMessage **p = (Gitsn_SignalRequestMessage **)ptr;
	if (p) { Gitsn_SignalRequestMessage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequestMessage_dump(Gitsn_SignalRequestMessage *p, int tab);
// Gitsn_SignalRequestMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalRequesterInfo
typedef struct Gitsn_SignalRequesterInfo
{
	Gitsn_VehicleID				*id;
	Gitsn_RequestID				 request;
	Gitsn_MsgCount				 sequenceNumber;
	Gitsn_BasicVehicleRole		 role;
	Gitsn_RequestorType			*typeData;
} Gitsn_SignalRequesterInfo;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequesterInfo *Gitsn_SignalRequesterInfo_new(Gitsn_VehicleID *id, 
																				 Gitsn_RequestID request, 
																				 Gitsn_MsgCount sequenceNumber, Dz1Error *err);
static __inline__ Gitsn_SignalRequesterInfo *Gitsn_SignalRequesterInfo_gen(Dz1Error *err) { return Gitsn_SignalRequesterInfo_new(NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SignalRequesterInfo_copy(Gitsn_SignalRequesterInfo *dst, Gitsn_SignalRequesterInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalRequesterInfo *Gitsn_SignalRequesterInfo_clone(Gitsn_SignalRequesterInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequesterInfo_purge(Gitsn_SignalRequesterInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequesterInfo_del(Gitsn_SignalRequesterInfo *p);
static __inline__ void Gitsn_SignalRequesterInfo_delAndSetNull(void *ptr)
{
	Gitsn_SignalRequesterInfo **p = (Gitsn_SignalRequesterInfo **)ptr;
	if (p) { Gitsn_SignalRequesterInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalRequesterInfo_dump(Gitsn_SignalRequesterInfo *p, int tab);
// Gitsn_SignalRequesterInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PrioritizationResponseStatus
typedef enum Gitsn_PrioritizationResponseStatus
{
	Gitsn_PrioritizationResponseStatus_unknown = 0,
	Gitsn_PrioritizationResponseStatus_requested = 1,
	Gitsn_PrioritizationResponseStatus_processing = 2,
	Gitsn_PrioritizationResponseStatus_watchOtherTraffic = 3,
	Gitsn_PrioritizationResponseStatus_granted = 4,
	Gitsn_PrioritizationResponseStatus_rejected = 5,
	Gitsn_PrioritizationResponseStatus_maxPresence = 6,
	Gitsn_PrioritizationResponseStatus_reserviceLocked = 7,
	Gitsn_PrioritizationResponseStatus_max
} Gitsn_PrioritizationResponseStatus;

DZ1_CPPLINK str_t Gitsn_PrioritizationResponseStatusStrA(Gitsn_PrioritizationResponseStatus v);
DZ1_CPPLINK Gitsn_PrioritizationResponseStatus Gitsn_PrioritizationResponseStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_PrioritizationResponseStatusStrW(Gitsn_PrioritizationResponseStatus v);
DZ1_CPPLINK Gitsn_PrioritizationResponseStatus Gitsn_PrioritizationResponseStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_PrioritizationResponseStatusStr Gitsn_PrioritizationResponseStatusStrW
#define Gitsn_PrioritizationResponseStatusFromStr Gitsn_PrioritizationResponseStatusFromStrW
#else // UNICODE
#define Gitsn_PrioritizationResponseStatusStr Gitsn_PrioritizationResponseStatusStrA
#define Gitsn_PrioritizationResponseStatusFromStr Gitsn_PrioritizationResponseStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_PrioritizationResponseStatusStr Gitsn_PrioritizationResponseStatusStrA
#define Gitsn_PrioritizationResponseStatusFromStr Gitsn_PrioritizationResponseStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PrioritizationResponseStatus *Gitsn_PrioritizationResponseStatus_new(Gitsn_PrioritizationResponseStatus *src, Dz1Error *err);
static __inline__ Gitsn_PrioritizationResponseStatus *Gitsn_PrioritizationResponseStatus_gen(Dz1Error *err) { Gitsn_PrioritizationResponseStatus v = Gitsn_PrioritizationResponseStatus_max; return Gitsn_PrioritizationResponseStatus_new(&v, err); }
#define Gitsn_PrioritizationResponseStatus_clone             Gitsn_PrioritizationResponseStatus_new
static __inline__ void Gitsn_PrioritizationResponseStatus_del(Gitsn_PrioritizationResponseStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_PrioritizationResponseStatus_delAndSetNull(void *ptr)
{
	Gitsn_PrioritizationResponseStatus **p = (Gitsn_PrioritizationResponseStatus **)ptr;
	if (p != NULL) { Gitsn_PrioritizationResponseStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PrioritizationResponseStatus_dump(Gitsn_PrioritizationResponseStatus *v, int tab);
// Gitsn_PrioritizationResponseStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalStatusPackage
typedef struct Gitsn_SignalStatusPackage
{
	Gitsn_SignalRequesterInfo				*requester;
	Gitsn_IntersectionAccessPoint			*inboundOn;
	Gitsn_IntersectionAccessPoint			*outboundOn;
	Gitsn_MinuteOfTheYear					 minute;
	Gitsn_DSecond							 second;
	Gitsn_DSecond							 duration;
	Gitsn_PrioritizationResponseStatus		 status;
} Gitsn_SignalStatusPackage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatusPackage *Gitsn_SignalStatusPackage_new(Gitsn_PrioritizationResponseStatus status, Dz1Error *err);
static __inline__ Gitsn_SignalStatusPackage *Gitsn_SignalStatusPackage_gen(Dz1Error *err) { return Gitsn_SignalStatusPackage_new(Gitsn_PrioritizationResponseStatus_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SignalStatusPackage_copy(Gitsn_SignalStatusPackage *dst, Gitsn_SignalStatusPackage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatusPackage *Gitsn_SignalStatusPackage_clone(Gitsn_SignalStatusPackage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusPackage_purge(Gitsn_SignalStatusPackage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusPackage_del(Gitsn_SignalStatusPackage *p);
static __inline__ void Gitsn_SignalStatusPackage_delAndSetNull(void *ptr)
{
	Gitsn_SignalStatusPackage **p = (Gitsn_SignalStatusPackage **)ptr;
	if (p) { Gitsn_SignalStatusPackage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusPackage_dump(Gitsn_SignalStatusPackage *p, int tab);
// Gitsn_SignalStatusPackage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalStatusPackageList
typedef struct Gitsn_SignalStatusPackageList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_SignalStatusPackageList *p);
	Dz1Error (*travel)(struct Gitsn_SignalStatusPackageList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalStatusPackage *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_SignalStatusPackageList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalStatusPackage *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_SignalStatusPackageList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalStatusPackage *entry), void *ptr);
	Gitsn_SignalStatusPackage **(*get_array)(struct Gitsn_SignalStatusPackageList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_SignalStatusPackageList *p, Gitsn_SignalStatusPackage *data);
	Gitsn_SignalStatusPackage *(*extract)(struct Gitsn_SignalStatusPackageList *p, Gitsn_SignalStatusPackage *ptr);
	Gitsn_SignalStatusPackage *(*getHead)(struct Gitsn_SignalStatusPackageList *p);
} Gitsn_SignalStatusPackageList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatusPackageList *Gitsn_SignalStatusPackageList_new(Dz1Error *err);
static __inline__ Gitsn_SignalStatusPackageList *Gitsn_SignalStatusPackageList_gen(Dz1Error *err) { return Gitsn_SignalStatusPackageList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatusPackageList *Gitsn_SignalStatusPackageList_clone(Gitsn_SignalStatusPackageList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusPackageList_purge(Gitsn_SignalStatusPackageList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusPackageList_del(Gitsn_SignalStatusPackageList *p);
static __inline__ void Gitsn_SignalStatusPackageList_delAndSetNull(void *ptr)
{
	Gitsn_SignalStatusPackageList **p = (Gitsn_SignalStatusPackageList **)ptr;
	if (p != NULL) { Gitsn_SignalStatusPackageList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusPackageList_dump(Gitsn_SignalStatusPackageList *p, int tab);

// Gitsn_SignalStatusPackageList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalStatus
typedef struct Gitsn_SignalStatus
{
	Gitsn_MsgCount						 sequenceNumber;
	Gitsn_IntersectionReferenceID		*id;
	Gitsn_SignalStatusPackageList		*sigStatus;
} Gitsn_SignalStatus;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatus *Gitsn_SignalStatus_new(Gitsn_MsgCount sequenceNumber, 
																   Gitsn_IntersectionReferenceID *id, 
																   Gitsn_SignalStatusPackageList *sigStatus, Dz1Error *err);
static __inline__ Gitsn_SignalStatus *Gitsn_SignalStatus_gen(Dz1Error *err) { return Gitsn_SignalStatus_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SignalStatus_copy(Gitsn_SignalStatus *dst, Gitsn_SignalStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatus *Gitsn_SignalStatus_clone(Gitsn_SignalStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatus_purge(Gitsn_SignalStatus *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatus_del(Gitsn_SignalStatus *p);
static __inline__ void Gitsn_SignalStatus_delAndSetNull(void *ptr)
{
	Gitsn_SignalStatus **p = (Gitsn_SignalStatus **)ptr;
	if (p) { Gitsn_SignalStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatus_dump(Gitsn_SignalStatus *p, int tab);
// Gitsn_SignalStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalStatusList
typedef struct Gitsn_SignalStatusList
{
	void *storage;
	unsigned int (*count)(struct Gitsn_SignalStatusList *p);
	Dz1Error (*travel)(struct Gitsn_SignalStatusList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalStatus *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_SignalStatusList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalStatus *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_SignalStatusList *p, Dz1Error (*func)(void *ptr, Gitsn_SignalStatus *entry), void *ptr);
	Gitsn_SignalStatus **(*get_array)(struct Gitsn_SignalStatusList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_SignalStatusList *p, Gitsn_SignalStatus *data);
	Gitsn_SignalStatus *(*extract)(struct Gitsn_SignalStatusList *p, Gitsn_SignalStatus *ptr);
	Gitsn_SignalStatus *(*getHead)(struct Gitsn_SignalStatusList *p);
} Gitsn_SignalStatusList;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatusList *Gitsn_SignalStatusList_new(Dz1Error *err);
static __inline__ Gitsn_SignalStatusList *Gitsn_SignalStatusList_gen(Dz1Error *err) { return Gitsn_SignalStatusList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatusList *Gitsn_SignalStatusList_clone(Gitsn_SignalStatusList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusList_purge(Gitsn_SignalStatusList *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusList_del(Gitsn_SignalStatusList *p);
static __inline__ void Gitsn_SignalStatusList_delAndSetNull(void *ptr)
{
	Gitsn_SignalStatusList **p = (Gitsn_SignalStatusList **)ptr;
	if (p != NULL) { Gitsn_SignalStatusList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusList_dump(Gitsn_SignalStatusList *p, int tab);

// Gitsn_SignalStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalStatusMessage
typedef struct Gitsn_SignalStatusMessage
{
	Gitsn_MinuteOfTheYear		 timeStamp;
	Gitsn_DSecond				 second;
	Gitsn_MsgCount				 sequenceNumber;
	Gitsn_SignalStatusList		*status;
} Gitsn_SignalStatusMessage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatusMessage *Gitsn_SignalStatusMessage_new(Gitsn_DSecond second, 
																				 Gitsn_SignalStatusList *status, Dz1Error *err);
static __inline__ Gitsn_SignalStatusMessage *Gitsn_SignalStatusMessage_gen(Dz1Error *err) { return Gitsn_SignalStatusMessage_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SignalStatusMessage_copy(Gitsn_SignalStatusMessage *dst, Gitsn_SignalStatusMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SignalStatusMessage *Gitsn_SignalStatusMessage_clone(Gitsn_SignalStatusMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusMessage_purge(Gitsn_SignalStatusMessage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusMessage_del(Gitsn_SignalStatusMessage *p);
static __inline__ void Gitsn_SignalStatusMessage_delAndSetNull(void *ptr)
{
	Gitsn_SignalStatusMessage **p = (Gitsn_SignalStatusMessage **)ptr;
	if (p) { Gitsn_SignalStatusMessage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SignalStatusMessage_dump(Gitsn_SignalStatusMessage *p, int tab);
// Gitsn_SignalStatusMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NumberOfParticipantsInCluster
typedef enum Gitsn_NumberOfParticipantsInCluster
{
	Gitsn_NumberOfParticipantsInCluster_unavailable = 0,
	Gitsn_NumberOfParticipantsInCluster_small = 1,
	Gitsn_NumberOfParticipantsInCluster_medium = 2,
	Gitsn_NumberOfParticipantsInCluster_large = 3,
	Gitsn_NumberOfParticipantsInCluster_max
} Gitsn_NumberOfParticipantsInCluster;

DZ1_CPPLINK str_t Gitsn_NumberOfParticipantsInClusterStrA(Gitsn_NumberOfParticipantsInCluster v);
DZ1_CPPLINK Gitsn_NumberOfParticipantsInCluster Gitsn_NumberOfParticipantsInClusterFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NumberOfParticipantsInClusterStrW(Gitsn_NumberOfParticipantsInCluster v);
DZ1_CPPLINK Gitsn_NumberOfParticipantsInCluster Gitsn_NumberOfParticipantsInClusterFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NumberOfParticipantsInClusterStr Gitsn_NumberOfParticipantsInClusterStrW
#define Gitsn_NumberOfParticipantsInClusterFromStr Gitsn_NumberOfParticipantsInClusterFromStrW
#else // UNICODE
#define Gitsn_NumberOfParticipantsInClusterStr Gitsn_NumberOfParticipantsInClusterStrA
#define Gitsn_NumberOfParticipantsInClusterFromStr Gitsn_NumberOfParticipantsInClusterFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NumberOfParticipantsInClusterStr Gitsn_NumberOfParticipantsInClusterStrA
#define Gitsn_NumberOfParticipantsInClusterFromStr Gitsn_NumberOfParticipantsInClusterFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NumberOfParticipantsInCluster *Gitsn_NumberOfParticipantsInCluster_new(Gitsn_NumberOfParticipantsInCluster *src, Dz1Error *err);
static __inline__ Gitsn_NumberOfParticipantsInCluster *Gitsn_NumberOfParticipantsInCluster_gen(Dz1Error *err) { Gitsn_NumberOfParticipantsInCluster v = Gitsn_NumberOfParticipantsInCluster_max; return Gitsn_NumberOfParticipantsInCluster_new(&v, err); }
#define Gitsn_NumberOfParticipantsInCluster_clone             Gitsn_NumberOfParticipantsInCluster_new
static __inline__ void Gitsn_NumberOfParticipantsInCluster_del(Gitsn_NumberOfParticipantsInCluster *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_NumberOfParticipantsInCluster_delAndSetNull(void *ptr)
{
	Gitsn_NumberOfParticipantsInCluster **p = (Gitsn_NumberOfParticipantsInCluster **)ptr;
	if (p != NULL) { Gitsn_NumberOfParticipantsInCluster_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NumberOfParticipantsInCluster_dump(Gitsn_NumberOfParticipantsInCluster *v, int tab);
// Gitsn_NumberOfParticipantsInCluster
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PublicSafetyEventResponderWorkerType
typedef enum Gitsn_PublicSafetyEventResponderWorkerType
{
	Gitsn_PublicSafetyEventResponderWorkerType_unavailable = 0,
	Gitsn_PublicSafetyEventResponderWorkerType_towOperater = 1,
	Gitsn_PublicSafetyEventResponderWorkerType_fireAndEMSWorker = 2,
	Gitsn_PublicSafetyEventResponderWorkerType_aDOTWorker = 3,
	Gitsn_PublicSafetyEventResponderWorkerType_lawEnforcement = 4,
	Gitsn_PublicSafetyEventResponderWorkerType_hazmatResponder = 5,
	Gitsn_PublicSafetyEventResponderWorkerType_animalControlWorker = 6,
	Gitsn_PublicSafetyEventResponderWorkerType_otherPersonnel = 7,
	Gitsn_PublicSafetyEventResponderWorkerType_max
} Gitsn_PublicSafetyEventResponderWorkerType;

DZ1_CPPLINK str_t Gitsn_PublicSafetyEventResponderWorkerTypeStrA(Gitsn_PublicSafetyEventResponderWorkerType v);
DZ1_CPPLINK Gitsn_PublicSafetyEventResponderWorkerType Gitsn_PublicSafetyEventResponderWorkerTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_PublicSafetyEventResponderWorkerTypeStrW(Gitsn_PublicSafetyEventResponderWorkerType v);
DZ1_CPPLINK Gitsn_PublicSafetyEventResponderWorkerType Gitsn_PublicSafetyEventResponderWorkerTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_PublicSafetyEventResponderWorkerTypeStr Gitsn_PublicSafetyEventResponderWorkerTypeStrW
#define Gitsn_PublicSafetyEventResponderWorkerTypeFromStr Gitsn_PublicSafetyEventResponderWorkerTypeFromStrW
#else // UNICODE
#define Gitsn_PublicSafetyEventResponderWorkerTypeStr Gitsn_PublicSafetyEventResponderWorkerTypeStrA
#define Gitsn_PublicSafetyEventResponderWorkerTypeFromStr Gitsn_PublicSafetyEventResponderWorkerTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_PublicSafetyEventResponderWorkerTypeStr Gitsn_PublicSafetyEventResponderWorkerTypeStrA
#define Gitsn_PublicSafetyEventResponderWorkerTypeFromStr Gitsn_PublicSafetyEventResponderWorkerTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PublicSafetyEventResponderWorkerType *Gitsn_PublicSafetyEventResponderWorkerType_new(Gitsn_PublicSafetyEventResponderWorkerType *src, Dz1Error *err);
static __inline__ Gitsn_PublicSafetyEventResponderWorkerType *Gitsn_PublicSafetyEventResponderWorkerType_gen(Dz1Error *err) { Gitsn_PublicSafetyEventResponderWorkerType v = Gitsn_PublicSafetyEventResponderWorkerType_max; return Gitsn_PublicSafetyEventResponderWorkerType_new(&v, err); }
#define Gitsn_PublicSafetyEventResponderWorkerType_clone             Gitsn_PublicSafetyEventResponderWorkerType_new
static __inline__ void Gitsn_PublicSafetyEventResponderWorkerType_del(Gitsn_PublicSafetyEventResponderWorkerType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_PublicSafetyEventResponderWorkerType_delAndSetNull(void *ptr)
{
	Gitsn_PublicSafetyEventResponderWorkerType **p = (Gitsn_PublicSafetyEventResponderWorkerType **)ptr;
	if (p != NULL) { Gitsn_PublicSafetyEventResponderWorkerType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PublicSafetyEventResponderWorkerType_dump(Gitsn_PublicSafetyEventResponderWorkerType *v, int tab);
// Gitsn_PublicSafetyEventResponderWorkerType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AnimalType
typedef enum Gitsn_AnimalType
{
	Gitsn_AnimalType_unavailable = 0,
	Gitsn_AnimalType_serviceUse = 1,
	Gitsn_AnimalType_pet = 2,
	Gitsn_AnimalType_farm = 3,
	Gitsn_AnimalType_max
} Gitsn_AnimalType;

DZ1_CPPLINK str_t Gitsn_AnimalTypeStrA(Gitsn_AnimalType v);
DZ1_CPPLINK Gitsn_AnimalType Gitsn_AnimalTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_AnimalTypeStrW(Gitsn_AnimalType v);
DZ1_CPPLINK Gitsn_AnimalType Gitsn_AnimalTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_AnimalTypeStr Gitsn_AnimalTypeStrW
#define Gitsn_AnimalTypeFromStr Gitsn_AnimalTypeFromStrW
#else // UNICODE
#define Gitsn_AnimalTypeStr Gitsn_AnimalTypeStrA
#define Gitsn_AnimalTypeFromStr Gitsn_AnimalTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_AnimalTypeStr Gitsn_AnimalTypeStrA
#define Gitsn_AnimalTypeFromStr Gitsn_AnimalTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_AnimalType *Gitsn_AnimalType_new(Gitsn_AnimalType *src, Dz1Error *err);
static __inline__ Gitsn_AnimalType *Gitsn_AnimalType_gen(Dz1Error *err) { Gitsn_AnimalType v = Gitsn_AnimalType_max; return Gitsn_AnimalType_new(&v, err); }
#define Gitsn_AnimalType_clone             Gitsn_AnimalType_new
static __inline__ void Gitsn_AnimalType_del(Gitsn_AnimalType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_AnimalType_delAndSetNull(void *ptr)
{
	Gitsn_AnimalType **p = (Gitsn_AnimalType **)ptr;
	if (p != NULL) { Gitsn_AnimalType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_AnimalType_dump(Gitsn_AnimalType *v, int tab);
// Gitsn_AnimalType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PersonalSafetyMessage
typedef struct Gitsn_PersonalSafetyMessage
{
	Gitsn_PersonalDeviceUserType					 basicType;
	Gitsn_DSecond									 secMark;
	Gitsn_MsgCount									 msgCnt;
	Gitsn_TemporaryID								 id;
	Gitsn_Position3D								*position;
	Gitsn_PositionalAccuracy						*accuracy;
	Gitsn_Velocity									 speed;
	Gitsn_Heading									 heading;
	Gitsn_AccelerationSet4Way						*accelSet;
	Gitsn_PathHistory								*pathHistory;
	Gitsn_PathPrediction							*pathPrediction;
	Gitsn_PropelledInformation						*propulsion;
	Gitsn_PersonalDeviceUsageState					*useState;
	Gitsn_PersonalCrossingRequest					 crossRequest;
	Gitsn_PersonalCrossingInProgress				 crossState;
	Gitsn_NumberOfParticipantsInCluster				 clusterSize;
	Gitsn_PersonalClusterRadius						 clusterRadius;
	Gitsn_PublicSafetyEventResponderWorkerType		 eventResponderType;
	Gitsn_PublicSafetyAndRoadWorkerActivity			*activityType;
	Gitsn_PublicSafetyDirectingTrafficSubType		*activitySubType;
	Gitsn_PersonalAssistive							*assistType;
	Gitsn_UserSizeAndBehaviour						*sizing;
	Gitsn_Attachment								 attachment;
	Gitsn_AttachmentRadius							 attachmentRadius;
	Gitsn_AnimalType								 animalType;
} Gitsn_PersonalSafetyMessage;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_PersonalSafetyMessage *Gitsn_PersonalSafetyMessage_new(Gitsn_PersonalDeviceUserType basicType, 
																					 Gitsn_DSecond secMark, 
																					 Gitsn_MsgCount msgCnt, 
																					 Gitsn_TemporaryID id, 
																					 Gitsn_Position3D *position, 
																					 Gitsn_PositionalAccuracy *accuracy, 
																					 Gitsn_Velocity speed, 
																					 Gitsn_Heading heading, Dz1Error *err);
static __inline__ Gitsn_PersonalSafetyMessage *Gitsn_PersonalSafetyMessage_gen(Dz1Error *err) { return Gitsn_PersonalSafetyMessage_new(Gitsn_PersonalDeviceUserType_max, 0, 0, NULL, NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_PersonalSafetyMessage_copy(Gitsn_PersonalSafetyMessage *dst, Gitsn_PersonalSafetyMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_PersonalSafetyMessage *Gitsn_PersonalSafetyMessage_clone(Gitsn_PersonalSafetyMessage *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PersonalSafetyMessage_purge(Gitsn_PersonalSafetyMessage *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PersonalSafetyMessage_del(Gitsn_PersonalSafetyMessage *p);
static __inline__ void Gitsn_PersonalSafetyMessage_delAndSetNull(void *ptr)
{
	Gitsn_PersonalSafetyMessage **p = (Gitsn_PersonalSafetyMessage **)ptr;
	if (p) { Gitsn_PersonalSafetyMessage_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_PersonalSafetyMessage_dump(Gitsn_PersonalSafetyMessage *p, int tab);
// Gitsn_PersonalSafetyMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgPresent
typedef enum GitsnDSRCMsgPresent
{
	GitsnDSRCMsgPresent_map,
	GitsnDSRCMsgPresent_spat,
	GitsnDSRCMsgPresent_bsm,
	GitsnDSRCMsgPresent_eva,
	GitsnDSRCMsgPresent_pvd,
	GitsnDSRCMsgPresent_rsa,
	GitsnDSRCMsgPresent_rtcm,
	GitsnDSRCMsgPresent_srm,
	GitsnDSRCMsgPresent_ssm,
	GitsnDSRCMsgPresent_tim,
	GitsnDSRCMsgPresent_psm,
	GitsnDSRCMsgPresent_sdsm,
	GitsnDSRCMsgPresent_tls,
	GitsnDSRCMsgPresent_tlsm,
	GitsnDSRCMsgPresent_max
} GitsnDSRCMsgPresent;

DZ1_CPPLINK str_t GitsnDSRCMsgPresentStrA(GitsnDSRCMsgPresent v);
DZ1_CPPLINK GitsnDSRCMsgPresent GitsnDSRCMsgPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnDSRCMsgPresentStrW(GitsnDSRCMsgPresent v);
DZ1_CPPLINK GitsnDSRCMsgPresent GitsnDSRCMsgPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnDSRCMsgPresentStr GitsnDSRCMsgPresentStrW
#define GitsnDSRCMsgPresentFromStr GitsnDSRCMsgPresentFromStrW
#else // UNICODE
#define GitsnDSRCMsgPresentStr GitsnDSRCMsgPresentStrA
#define GitsnDSRCMsgPresentFromStr GitsnDSRCMsgPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnDSRCMsgPresentStr GitsnDSRCMsgPresentStrA
#define GitsnDSRCMsgPresentFromStr GitsnDSRCMsgPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgPresent *GitsnDSRCMsgPresent_new(GitsnDSRCMsgPresent *src, Dz1Error *err);
static __inline__ GitsnDSRCMsgPresent *GitsnDSRCMsgPresent_gen(Dz1Error *err) { GitsnDSRCMsgPresent v = GitsnDSRCMsgPresent_max; return GitsnDSRCMsgPresent_new(&v, err); }
#define GitsnDSRCMsgPresent_clone             GitsnDSRCMsgPresent_new
static __inline__ void GitsnDSRCMsgPresent_del(GitsnDSRCMsgPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnDSRCMsgPresent_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgPresent **p = (GitsnDSRCMsgPresent **)ptr;
	if (p != NULL) { GitsnDSRCMsgPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgPresent_dump(GitsnDSRCMsgPresent *v, int tab);
// GitsnDSRCMsgPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsg
typedef struct GitsnDSRCMsg
{
	GitsnDSRCMsgPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Gitsn_MapData						*map;
		Gitsn_SPAT							*spat;
		Gitsn_BasicSafetyMessage			*bsm;
		Gitsn_EmergencyVehicleAlert			*eva;
		Gitsn_ProbeVehicleData				*pvd;
		Gitsn_RoadSideAlert					*rsa;
		Gitsn_RTCMcorrections				*rtcm;
		Gitsn_SignalRequestMessage			*srm;
		Gitsn_SignalStatusMessage			*ssm;
		Gitsn_TravelerInformation			*tim;
		Gitsn_PersonalSafetyMessage			*psm;
		Gitsn_SensorDataSharingMessage		*sdsm;
		Gitsn_TLS							*tls;
		Gitsn_TrafficLightStatusMessage		*tlsm;
	} x;
} GitsnDSRCMsg;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsg *GitsnDSRCMsg_new(GitsnDSRCMsgPresent present, void *ptr, Dz1Error *err);
static __inline__ GitsnDSRCMsg *GitsnDSRCMsg_gen(Dz1Error *err) { return GitsnDSRCMsg_new(GitsnDSRCMsgPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  GitsnDSRCMsg_copy(GitsnDSRCMsg *dst, GitsnDSRCMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsg *GitsnDSRCMsg_clone(GitsnDSRCMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsg_purge(GitsnDSRCMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsg_del(GitsnDSRCMsg *p);
static __inline__ void GitsnDSRCMsg_delAndSetNull(void *ptr)
{
	GitsnDSRCMsg **p = (GitsnDSRCMsg **)ptr;
	if (p != NULL) { GitsnDSRCMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsg_dump(GitsnDSRCMsg *p, int tab);
// GitsnDSRCMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentDetectionInfo_incident_Detected_Type
typedef enum Gitsn_IncidentDetectionInfo_incident_Detected_Type
{
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_stalledVehicle = 1,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_reverseDriving = 2,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_pedestrian = 3,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_roadwayDebris = 4,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_rireSmoke = 5,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_roadShouldersVehicle = 6,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_roadkill = 7,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_slowVehicle = 8,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_delayCongested = 9,
	Gitsn_IncidentDetectionInfo_incident_Detected_Type_max
} Gitsn_IncidentDetectionInfo_incident_Detected_Type;

DZ1_CPPLINK str_t Gitsn_IncidentDetectionInfo_incident_Detected_TypeStrA(Gitsn_IncidentDetectionInfo_incident_Detected_Type v);
DZ1_CPPLINK Gitsn_IncidentDetectionInfo_incident_Detected_Type Gitsn_IncidentDetectionInfo_incident_Detected_TypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_IncidentDetectionInfo_incident_Detected_TypeStrW(Gitsn_IncidentDetectionInfo_incident_Detected_Type v);
DZ1_CPPLINK Gitsn_IncidentDetectionInfo_incident_Detected_Type Gitsn_IncidentDetectionInfo_incident_Detected_TypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_IncidentDetectionInfo_incident_Detected_TypeStr Gitsn_IncidentDetectionInfo_incident_Detected_TypeStrW
#define Gitsn_IncidentDetectionInfo_incident_Detected_TypeFromStr Gitsn_IncidentDetectionInfo_incident_Detected_TypeFromStrW
#else // UNICODE
#define Gitsn_IncidentDetectionInfo_incident_Detected_TypeStr Gitsn_IncidentDetectionInfo_incident_Detected_TypeStrA
#define Gitsn_IncidentDetectionInfo_incident_Detected_TypeFromStr Gitsn_IncidentDetectionInfo_incident_Detected_TypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_IncidentDetectionInfo_incident_Detected_TypeStr Gitsn_IncidentDetectionInfo_incident_Detected_TypeStrA
#define Gitsn_IncidentDetectionInfo_incident_Detected_TypeFromStr Gitsn_IncidentDetectionInfo_incident_Detected_TypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionInfo_incident_Detected_Type *Gitsn_IncidentDetectionInfo_incident_Detected_Type_new(Gitsn_IncidentDetectionInfo_incident_Detected_Type *src, Dz1Error *err);
static __inline__ Gitsn_IncidentDetectionInfo_incident_Detected_Type *Gitsn_IncidentDetectionInfo_incident_Detected_Type_gen(Dz1Error *err) { Gitsn_IncidentDetectionInfo_incident_Detected_Type v = Gitsn_IncidentDetectionInfo_incident_Detected_Type_max; return Gitsn_IncidentDetectionInfo_incident_Detected_Type_new(&v, err); }
#define Gitsn_IncidentDetectionInfo_incident_Detected_Type_clone             Gitsn_IncidentDetectionInfo_incident_Detected_Type_new
static __inline__ void Gitsn_IncidentDetectionInfo_incident_Detected_Type_del(Gitsn_IncidentDetectionInfo_incident_Detected_Type *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_IncidentDetectionInfo_incident_Detected_Type_delAndSetNull(void *ptr)
{
	Gitsn_IncidentDetectionInfo_incident_Detected_Type **p = (Gitsn_IncidentDetectionInfo_incident_Detected_Type **)ptr;
	if (p != NULL) { Gitsn_IncidentDetectionInfo_incident_Detected_Type_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionInfo_incident_Detected_Type_dump(Gitsn_IncidentDetectionInfo_incident_Detected_Type *v, int tab);
// Gitsn_IncidentDetectionInfo_incident_Detected_Type
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NMEACoord_compass
typedef enum Gitsn_NMEACoord_compass
{
	Gitsn_NMEACoord_compass_north,
	Gitsn_NMEACoord_compass_south,
	Gitsn_NMEACoord_compass_max
} Gitsn_NMEACoord_compass;

DZ1_CPPLINK str_t Gitsn_NMEACoord_compassStrA(Gitsn_NMEACoord_compass v);
DZ1_CPPLINK Gitsn_NMEACoord_compass Gitsn_NMEACoord_compassFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NMEACoord_compassStrW(Gitsn_NMEACoord_compass v);
DZ1_CPPLINK Gitsn_NMEACoord_compass Gitsn_NMEACoord_compassFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NMEACoord_compassStr Gitsn_NMEACoord_compassStrW
#define Gitsn_NMEACoord_compassFromStr Gitsn_NMEACoord_compassFromStrW
#else // UNICODE
#define Gitsn_NMEACoord_compassStr Gitsn_NMEACoord_compassStrA
#define Gitsn_NMEACoord_compassFromStr Gitsn_NMEACoord_compassFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NMEACoord_compassStr Gitsn_NMEACoord_compassStrA
#define Gitsn_NMEACoord_compassFromStr Gitsn_NMEACoord_compassFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NMEACoord_compass *Gitsn_NMEACoord_compass_new(Gitsn_NMEACoord_compass *src, Dz1Error *err);
static __inline__ Gitsn_NMEACoord_compass *Gitsn_NMEACoord_compass_gen(Dz1Error *err) { Gitsn_NMEACoord_compass v = Gitsn_NMEACoord_compass_max; return Gitsn_NMEACoord_compass_new(&v, err); }
#define Gitsn_NMEACoord_compass_clone             Gitsn_NMEACoord_compass_new
static __inline__ void Gitsn_NMEACoord_compass_del(Gitsn_NMEACoord_compass *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_NMEACoord_compass_delAndSetNull(void *ptr)
{
	Gitsn_NMEACoord_compass **p = (Gitsn_NMEACoord_compass **)ptr;
	if (p != NULL) { Gitsn_NMEACoord_compass_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_compass_dump(Gitsn_NMEACoord_compass *v, int tab);
// Gitsn_NMEACoord_compass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NMEACoord_latitude
typedef struct Gitsn_NMEACoord_latitude
{
	s64_t						integerValue;
	s64_t						fractionValue;
	s64_t						fracSize;
	Gitsn_NMEACoord_compass		compass;
} Gitsn_NMEACoord_latitude;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NMEACoord_latitude *Gitsn_NMEACoord_latitude_new(s64_t integerValue, 
																			   s64_t fractionValue, 
																			   s64_t fracSize, 
																			   Gitsn_NMEACoord_compass compass, Dz1Error *err);
static __inline__ Gitsn_NMEACoord_latitude *Gitsn_NMEACoord_latitude_gen(Dz1Error *err) { return Gitsn_NMEACoord_latitude_new(0, 0, 0, Gitsn_NMEACoord_compass_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_NMEACoord_latitude_copy(Gitsn_NMEACoord_latitude *dst, Gitsn_NMEACoord_latitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NMEACoord_latitude *Gitsn_NMEACoord_latitude_clone(Gitsn_NMEACoord_latitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_latitude_purge(Gitsn_NMEACoord_latitude *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_latitude_del(Gitsn_NMEACoord_latitude *p);
static __inline__ void Gitsn_NMEACoord_latitude_delAndSetNull(void *ptr)
{
	Gitsn_NMEACoord_latitude **p = (Gitsn_NMEACoord_latitude **)ptr;
	if (p) { Gitsn_NMEACoord_latitude_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_latitude_dump(Gitsn_NMEACoord_latitude *p, int tab);
// Gitsn_NMEACoord_latitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NMEACoord_longitude
typedef struct Gitsn_NMEACoord_longitude
{
	s64_t						integerValue;
	s64_t						fractionValue;
	s64_t						fracSize;
	Gitsn_NMEACoord_compass		compass;
} Gitsn_NMEACoord_longitude;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NMEACoord_longitude *Gitsn_NMEACoord_longitude_new(s64_t integerValue, 
																				 s64_t fractionValue, 
																				 s64_t fracSize, 
																				 Gitsn_NMEACoord_compass compass, Dz1Error *err);
static __inline__ Gitsn_NMEACoord_longitude *Gitsn_NMEACoord_longitude_gen(Dz1Error *err) { return Gitsn_NMEACoord_longitude_new(0, 0, 0, Gitsn_NMEACoord_compass_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_NMEACoord_longitude_copy(Gitsn_NMEACoord_longitude *dst, Gitsn_NMEACoord_longitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NMEACoord_longitude *Gitsn_NMEACoord_longitude_clone(Gitsn_NMEACoord_longitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_longitude_purge(Gitsn_NMEACoord_longitude *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_longitude_del(Gitsn_NMEACoord_longitude *p);
static __inline__ void Gitsn_NMEACoord_longitude_delAndSetNull(void *ptr)
{
	Gitsn_NMEACoord_longitude **p = (Gitsn_NMEACoord_longitude **)ptr;
	if (p) { Gitsn_NMEACoord_longitude_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_longitude_dump(Gitsn_NMEACoord_longitude *p, int tab);
// Gitsn_NMEACoord_longitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NMEACoord
typedef struct Gitsn_NMEACoord
{
	Gitsn_NMEACoord_latitude		*latitude;
	Gitsn_NMEACoord_longitude		*longitude;
	Dz1Binary						*optData;
} Gitsn_NMEACoord;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_NMEACoord *Gitsn_NMEACoord_new(Gitsn_NMEACoord_latitude *latitude, 
															 Gitsn_NMEACoord_longitude *longitude, Dz1Error *err);
static __inline__ Gitsn_NMEACoord *Gitsn_NMEACoord_gen(Dz1Error *err) { return Gitsn_NMEACoord_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_NMEACoord_copy(Gitsn_NMEACoord *dst, Gitsn_NMEACoord *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_NMEACoord *Gitsn_NMEACoord_clone(Gitsn_NMEACoord *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_purge(Gitsn_NMEACoord *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_del(Gitsn_NMEACoord *p);
static __inline__ void Gitsn_NMEACoord_delAndSetNull(void *ptr)
{
	Gitsn_NMEACoord **p = (Gitsn_NMEACoord **)ptr;
	if (p) { Gitsn_NMEACoord_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_NMEACoord_dump(Gitsn_NMEACoord *p, int tab);
// Gitsn_NMEACoord
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentDetectionInfo
typedef struct Gitsn_IncidentDetectionInfo
{
	Dz1Str													 incident_Detected_Time;
	Gitsn_IncidentDetectionInfo_incident_Detected_Type		 incident_Detected_Type;
	Gitsn_NMEACoord											*incident_Detected_Site;
	s64_t													 detected_Object_Size;
	s64_t													 detected_Object_Distance;
	s64_t													 detected_Object_Angle;
	s64_t													 detected_Object_Speed;
} Gitsn_IncidentDetectionInfo;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionInfo *Gitsn_IncidentDetectionInfo_new(Dz1Str incident_Detected_Time, 
																					 Gitsn_IncidentDetectionInfo_incident_Detected_Type incident_Detected_Type, 
																					 Gitsn_NMEACoord *incident_Detected_Site, 
																					 s64_t detected_Object_Distance, 
																					 s64_t detected_Object_Angle, 
																					 s64_t detected_Object_Speed, Dz1Error *err);
static __inline__ Gitsn_IncidentDetectionInfo *Gitsn_IncidentDetectionInfo_gen(Dz1Error *err) { return Gitsn_IncidentDetectionInfo_new(NULL, Gitsn_IncidentDetectionInfo_incident_Detected_Type_max, NULL, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_IncidentDetectionInfo_copy(Gitsn_IncidentDetectionInfo *dst, Gitsn_IncidentDetectionInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionInfo *Gitsn_IncidentDetectionInfo_clone(Gitsn_IncidentDetectionInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionInfo_purge(Gitsn_IncidentDetectionInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionInfo_del(Gitsn_IncidentDetectionInfo *p);
static __inline__ void Gitsn_IncidentDetectionInfo_delAndSetNull(void *ptr)
{
	Gitsn_IncidentDetectionInfo **p = (Gitsn_IncidentDetectionInfo **)ptr;
	if (p) { Gitsn_IncidentDetectionInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionInfo_dump(Gitsn_IncidentDetectionInfo *p, int tab);
// Gitsn_IncidentDetectionInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentTerminationInfo_terminate_incidentType
typedef enum Gitsn_IncidentTerminationInfo_terminate_incidentType
{
	Gitsn_IncidentTerminationInfo_terminate_incidentType_termination = 1,
	Gitsn_IncidentTerminationInfo_terminate_incidentType_timeout = 2,
	Gitsn_IncidentTerminationInfo_terminate_incidentType_max
} Gitsn_IncidentTerminationInfo_terminate_incidentType;

DZ1_CPPLINK str_t Gitsn_IncidentTerminationInfo_terminate_incidentTypeStrA(Gitsn_IncidentTerminationInfo_terminate_incidentType v);
DZ1_CPPLINK Gitsn_IncidentTerminationInfo_terminate_incidentType Gitsn_IncidentTerminationInfo_terminate_incidentTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_IncidentTerminationInfo_terminate_incidentTypeStrW(Gitsn_IncidentTerminationInfo_terminate_incidentType v);
DZ1_CPPLINK Gitsn_IncidentTerminationInfo_terminate_incidentType Gitsn_IncidentTerminationInfo_terminate_incidentTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_IncidentTerminationInfo_terminate_incidentTypeStr Gitsn_IncidentTerminationInfo_terminate_incidentTypeStrW
#define Gitsn_IncidentTerminationInfo_terminate_incidentTypeFromStr Gitsn_IncidentTerminationInfo_terminate_incidentTypeFromStrW
#else // UNICODE
#define Gitsn_IncidentTerminationInfo_terminate_incidentTypeStr Gitsn_IncidentTerminationInfo_terminate_incidentTypeStrA
#define Gitsn_IncidentTerminationInfo_terminate_incidentTypeFromStr Gitsn_IncidentTerminationInfo_terminate_incidentTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_IncidentTerminationInfo_terminate_incidentTypeStr Gitsn_IncidentTerminationInfo_terminate_incidentTypeStrA
#define Gitsn_IncidentTerminationInfo_terminate_incidentTypeFromStr Gitsn_IncidentTerminationInfo_terminate_incidentTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentTerminationInfo_terminate_incidentType *Gitsn_IncidentTerminationInfo_terminate_incidentType_new(Gitsn_IncidentTerminationInfo_terminate_incidentType *src, Dz1Error *err);
static __inline__ Gitsn_IncidentTerminationInfo_terminate_incidentType *Gitsn_IncidentTerminationInfo_terminate_incidentType_gen(Dz1Error *err) { Gitsn_IncidentTerminationInfo_terminate_incidentType v = Gitsn_IncidentTerminationInfo_terminate_incidentType_max; return Gitsn_IncidentTerminationInfo_terminate_incidentType_new(&v, err); }
#define Gitsn_IncidentTerminationInfo_terminate_incidentType_clone             Gitsn_IncidentTerminationInfo_terminate_incidentType_new
static __inline__ void Gitsn_IncidentTerminationInfo_terminate_incidentType_del(Gitsn_IncidentTerminationInfo_terminate_incidentType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_IncidentTerminationInfo_terminate_incidentType_delAndSetNull(void *ptr)
{
	Gitsn_IncidentTerminationInfo_terminate_incidentType **p = (Gitsn_IncidentTerminationInfo_terminate_incidentType **)ptr;
	if (p != NULL) { Gitsn_IncidentTerminationInfo_terminate_incidentType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentTerminationInfo_terminate_incidentType_dump(Gitsn_IncidentTerminationInfo_terminate_incidentType *v, int tab);
// Gitsn_IncidentTerminationInfo_terminate_incidentType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentTerminationInfo
typedef struct Gitsn_IncidentTerminationInfo
{
	Gitsn_IncidentTerminationInfo_terminate_incidentType	terminate_incidentType;
} Gitsn_IncidentTerminationInfo;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentTerminationInfo *Gitsn_IncidentTerminationInfo_new(Gitsn_IncidentTerminationInfo_terminate_incidentType terminate_incidentType, Dz1Error *err);
static __inline__ Gitsn_IncidentTerminationInfo *Gitsn_IncidentTerminationInfo_gen(Dz1Error *err) { return Gitsn_IncidentTerminationInfo_new(Gitsn_IncidentTerminationInfo_terminate_incidentType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_IncidentTerminationInfo_copy(Gitsn_IncidentTerminationInfo *dst, Gitsn_IncidentTerminationInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentTerminationInfo *Gitsn_IncidentTerminationInfo_clone(Gitsn_IncidentTerminationInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentTerminationInfo_purge(Gitsn_IncidentTerminationInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentTerminationInfo_del(Gitsn_IncidentTerminationInfo *p);
static __inline__ void Gitsn_IncidentTerminationInfo_delAndSetNull(void *ptr)
{
	Gitsn_IncidentTerminationInfo **p = (Gitsn_IncidentTerminationInfo **)ptr;
	if (p) { Gitsn_IncidentTerminationInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentTerminationInfo_dump(Gitsn_IncidentTerminationInfo *p, int tab);
// Gitsn_IncidentTerminationInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus
typedef enum Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus
{
	Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileExists = 0,
	Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileAlreadyExists = 1,
	Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_max
} Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus;

DZ1_CPPLINK str_t Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusStrA(Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus v);
DZ1_CPPLINK Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusStrW(Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus v);
DZ1_CPPLINK Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusStr Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusStrW
#define Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusFromStr Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusFromStrW
#else // UNICODE
#define Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusStr Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusStrA
#define Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusFromStr Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusStr Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusStrA
#define Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusFromStr Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus *Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_new(Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus *src, Dz1Error *err);
static __inline__ Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus *Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_gen(Dz1Error *err) { Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus v = Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_max; return Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_new(&v, err); }
#define Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_clone             Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_new
static __inline__ void Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_del(Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_delAndSetNull(void *ptr)
{
	Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus **p = (Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus **)ptr;
	if (p != NULL) { Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_dump(Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus *v, int tab);
// Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentDetectionVideoFileInfoProvide
typedef struct Gitsn_IncidentDetectionVideoFileInfoProvide
{
	Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus		fileSatatus;
	Dz1Str														fileName;
	s64_t														fileSize;
} Gitsn_IncidentDetectionVideoFileInfoProvide;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionVideoFileInfoProvide *Gitsn_IncidentDetectionVideoFileInfoProvide_new(Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus fileSatatus, Dz1Error *err);
static __inline__ Gitsn_IncidentDetectionVideoFileInfoProvide *Gitsn_IncidentDetectionVideoFileInfoProvide_gen(Dz1Error *err) { return Gitsn_IncidentDetectionVideoFileInfoProvide_new(Gitsn_IncidentDetectionVideoFileInfoProvide_fileStatus_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_IncidentDetectionVideoFileInfoProvide_copy(Gitsn_IncidentDetectionVideoFileInfoProvide *dst, Gitsn_IncidentDetectionVideoFileInfoProvide *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionVideoFileInfoProvide *Gitsn_IncidentDetectionVideoFileInfoProvide_clone(Gitsn_IncidentDetectionVideoFileInfoProvide *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionVideoFileInfoProvide_purge(Gitsn_IncidentDetectionVideoFileInfoProvide *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionVideoFileInfoProvide_del(Gitsn_IncidentDetectionVideoFileInfoProvide *p);
static __inline__ void Gitsn_IncidentDetectionVideoFileInfoProvide_delAndSetNull(void *ptr)
{
	Gitsn_IncidentDetectionVideoFileInfoProvide **p = (Gitsn_IncidentDetectionVideoFileInfoProvide **)ptr;
	if (p) { Gitsn_IncidentDetectionVideoFileInfoProvide_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionVideoFileInfoProvide_dump(Gitsn_IncidentDetectionVideoFileInfoProvide *p, int tab);
// Gitsn_IncidentDetectionVideoFileInfoProvide
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ControlStateInfo
typedef struct Gitsn_ControlStateInfo
{
	s64_t		cpu;
	s64_t		ram;
	s64_t		disk;
} Gitsn_ControlStateInfo;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ControlStateInfo *Gitsn_ControlStateInfo_new(s64_t cpu, 
																		   s64_t ram, 
																		   s64_t disk, Dz1Error *err);
static __inline__ Gitsn_ControlStateInfo *Gitsn_ControlStateInfo_gen(Dz1Error *err) { return Gitsn_ControlStateInfo_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_ControlStateInfo_copy(Gitsn_ControlStateInfo *dst, Gitsn_ControlStateInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ControlStateInfo *Gitsn_ControlStateInfo_clone(Gitsn_ControlStateInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ControlStateInfo_purge(Gitsn_ControlStateInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ControlStateInfo_del(Gitsn_ControlStateInfo *p);
static __inline__ void Gitsn_ControlStateInfo_delAndSetNull(void *ptr)
{
	Gitsn_ControlStateInfo **p = (Gitsn_ControlStateInfo **)ptr;
	if (p) { Gitsn_ControlStateInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ControlStateInfo_dump(Gitsn_ControlStateInfo *p, int tab);
// Gitsn_ControlStateInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SensorStateInfo_state
typedef enum Gitsn_SensorStateInfo_state
{
	Gitsn_SensorStateInfo_state_normal = 0,
	Gitsn_SensorStateInfo_state_abnormal = 1,
	Gitsn_SensorStateInfo_state_max
} Gitsn_SensorStateInfo_state;

DZ1_CPPLINK str_t Gitsn_SensorStateInfo_stateStrA(Gitsn_SensorStateInfo_state v);
DZ1_CPPLINK Gitsn_SensorStateInfo_state Gitsn_SensorStateInfo_stateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_SensorStateInfo_stateStrW(Gitsn_SensorStateInfo_state v);
DZ1_CPPLINK Gitsn_SensorStateInfo_state Gitsn_SensorStateInfo_stateFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_SensorStateInfo_stateStr Gitsn_SensorStateInfo_stateStrW
#define Gitsn_SensorStateInfo_stateFromStr Gitsn_SensorStateInfo_stateFromStrW
#else // UNICODE
#define Gitsn_SensorStateInfo_stateStr Gitsn_SensorStateInfo_stateStrA
#define Gitsn_SensorStateInfo_stateFromStr Gitsn_SensorStateInfo_stateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_SensorStateInfo_stateStr Gitsn_SensorStateInfo_stateStrA
#define Gitsn_SensorStateInfo_stateFromStr Gitsn_SensorStateInfo_stateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SensorStateInfo_state *Gitsn_SensorStateInfo_state_new(Gitsn_SensorStateInfo_state *src, Dz1Error *err);
static __inline__ Gitsn_SensorStateInfo_state *Gitsn_SensorStateInfo_state_gen(Dz1Error *err) { Gitsn_SensorStateInfo_state v = Gitsn_SensorStateInfo_state_max; return Gitsn_SensorStateInfo_state_new(&v, err); }
#define Gitsn_SensorStateInfo_state_clone             Gitsn_SensorStateInfo_state_new
static __inline__ void Gitsn_SensorStateInfo_state_del(Gitsn_SensorStateInfo_state *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_SensorStateInfo_state_delAndSetNull(void *ptr)
{
	Gitsn_SensorStateInfo_state **p = (Gitsn_SensorStateInfo_state **)ptr;
	if (p != NULL) { Gitsn_SensorStateInfo_state_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorStateInfo_state_dump(Gitsn_SensorStateInfo_state *v, int tab);
// Gitsn_SensorStateInfo_state
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SensorStateInfo
typedef struct Gitsn_SensorStateInfo
{
	Gitsn_SensorStateInfo_state		msm;
	Gitsn_SensorStateInfo_state		txb;
	Gitsn_SensorStateInfo_state		rxb;
	Gitsn_SensorStateInfo_state		pwr;
} Gitsn_SensorStateInfo;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SensorStateInfo *Gitsn_SensorStateInfo_new(Gitsn_SensorStateInfo_state msm, 
																		 Gitsn_SensorStateInfo_state txb, 
																		 Gitsn_SensorStateInfo_state rxb, 
																		 Gitsn_SensorStateInfo_state pwr, Dz1Error *err);
static __inline__ Gitsn_SensorStateInfo *Gitsn_SensorStateInfo_gen(Dz1Error *err) { return Gitsn_SensorStateInfo_new(Gitsn_SensorStateInfo_state_max, Gitsn_SensorStateInfo_state_max, Gitsn_SensorStateInfo_state_max, Gitsn_SensorStateInfo_state_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_SensorStateInfo_copy(Gitsn_SensorStateInfo *dst, Gitsn_SensorStateInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SensorStateInfo *Gitsn_SensorStateInfo_clone(Gitsn_SensorStateInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorStateInfo_purge(Gitsn_SensorStateInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorStateInfo_del(Gitsn_SensorStateInfo *p);
static __inline__ void Gitsn_SensorStateInfo_delAndSetNull(void *ptr)
{
	Gitsn_SensorStateInfo **p = (Gitsn_SensorStateInfo **)ptr;
	if (p) { Gitsn_SensorStateInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorStateInfo_dump(Gitsn_SensorStateInfo *p, int tab);
// Gitsn_SensorStateInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovingObject_objectType
typedef enum Gitsn_MovingObject_objectType
{
	Gitsn_MovingObject_objectType_pedestrian = 0,
	Gitsn_MovingObject_objectType_vehicle = 1,
	Gitsn_MovingObject_objectType_bike = 2,
	Gitsn_MovingObject_objectType_max
} Gitsn_MovingObject_objectType;

DZ1_CPPLINK str_t Gitsn_MovingObject_objectTypeStrA(Gitsn_MovingObject_objectType v);
DZ1_CPPLINK Gitsn_MovingObject_objectType Gitsn_MovingObject_objectTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_MovingObject_objectTypeStrW(Gitsn_MovingObject_objectType v);
DZ1_CPPLINK Gitsn_MovingObject_objectType Gitsn_MovingObject_objectTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_MovingObject_objectTypeStr Gitsn_MovingObject_objectTypeStrW
#define Gitsn_MovingObject_objectTypeFromStr Gitsn_MovingObject_objectTypeFromStrW
#else // UNICODE
#define Gitsn_MovingObject_objectTypeStr Gitsn_MovingObject_objectTypeStrA
#define Gitsn_MovingObject_objectTypeFromStr Gitsn_MovingObject_objectTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_MovingObject_objectTypeStr Gitsn_MovingObject_objectTypeStrA
#define Gitsn_MovingObject_objectTypeFromStr Gitsn_MovingObject_objectTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovingObject_objectType *Gitsn_MovingObject_objectType_new(Gitsn_MovingObject_objectType *src, Dz1Error *err);
static __inline__ Gitsn_MovingObject_objectType *Gitsn_MovingObject_objectType_gen(Dz1Error *err) { Gitsn_MovingObject_objectType v = Gitsn_MovingObject_objectType_max; return Gitsn_MovingObject_objectType_new(&v, err); }
#define Gitsn_MovingObject_objectType_clone             Gitsn_MovingObject_objectType_new
static __inline__ void Gitsn_MovingObject_objectType_del(Gitsn_MovingObject_objectType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_MovingObject_objectType_delAndSetNull(void *ptr)
{
	Gitsn_MovingObject_objectType **p = (Gitsn_MovingObject_objectType **)ptr;
	if (p != NULL) { Gitsn_MovingObject_objectType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovingObject_objectType_dump(Gitsn_MovingObject_objectType *v, int tab);
// Gitsn_MovingObject_objectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Novelty
typedef enum Gitsn_Novelty
{
	Gitsn_Novelty_noveltyNew = 0,
	Gitsn_Novelty_noveltyUpdate = 1,
	Gitsn_Novelty_max
} Gitsn_Novelty;

DZ1_CPPLINK str_t Gitsn_NoveltyStrA(Gitsn_Novelty v);
DZ1_CPPLINK Gitsn_Novelty Gitsn_NoveltyFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Gitsn_NoveltyStrW(Gitsn_Novelty v);
DZ1_CPPLINK Gitsn_Novelty Gitsn_NoveltyFromStrW(wstr_t str);
#ifdef UNICODE
#define Gitsn_NoveltyStr Gitsn_NoveltyStrW
#define Gitsn_NoveltyFromStr Gitsn_NoveltyFromStrW
#else // UNICODE
#define Gitsn_NoveltyStr Gitsn_NoveltyStrA
#define Gitsn_NoveltyFromStr Gitsn_NoveltyFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Gitsn_NoveltyStr Gitsn_NoveltyStrA
#define Gitsn_NoveltyFromStr Gitsn_NoveltyFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Gitsn_Novelty *Gitsn_Novelty_new(Gitsn_Novelty *src, Dz1Error *err);
static __inline__ Gitsn_Novelty *Gitsn_Novelty_gen(Dz1Error *err) { Gitsn_Novelty v = Gitsn_Novelty_max; return Gitsn_Novelty_new(&v, err); }
#define Gitsn_Novelty_clone             Gitsn_Novelty_new
static __inline__ void Gitsn_Novelty_del(Gitsn_Novelty *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Gitsn_Novelty_delAndSetNull(void *ptr)
{
	Gitsn_Novelty **p = (Gitsn_Novelty **)ptr;
	if (p != NULL) { Gitsn_Novelty_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_Novelty_dump(Gitsn_Novelty *v, int tab);
// Gitsn_Novelty
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovingObject
typedef struct Gitsn_MovingObject
{
	Gitsn_MovingObject_objectType		 objectType;
	Gitsn_ObjectID						 objectID;
	Gitsn_Novelty						 novelty;
	s64_t								 reliability;
	Gitsn_FullPositionVector			*fullPositionVector;
} Gitsn_MovingObject;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovingObject *Gitsn_MovingObject_new(Gitsn_MovingObject_objectType objectType, 
																   Gitsn_ObjectID objectID, 
																   s64_t reliability, 
																   Gitsn_FullPositionVector *fullPositionVector, Dz1Error *err);
static __inline__ Gitsn_MovingObject *Gitsn_MovingObject_gen(Dz1Error *err) { return Gitsn_MovingObject_new(Gitsn_MovingObject_objectType_max, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Gitsn_MovingObject_copy(Gitsn_MovingObject *dst, Gitsn_MovingObject *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovingObject *Gitsn_MovingObject_clone(Gitsn_MovingObject *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovingObject_purge(Gitsn_MovingObject *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovingObject_del(Gitsn_MovingObject *p);
static __inline__ void Gitsn_MovingObject_delAndSetNull(void *ptr)
{
	Gitsn_MovingObject **p = (Gitsn_MovingObject **)ptr;
	if (p) { Gitsn_MovingObject_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovingObject_dump(Gitsn_MovingObject *p, int tab);
// Gitsn_MovingObject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentDetectionInfoResponse
typedef struct Gitsn_IncidentDetectionInfoResponse
{
	void *storage;
	unsigned int (*count)(struct Gitsn_IncidentDetectionInfoResponse *p);
	Dz1Error (*travel)(struct Gitsn_IncidentDetectionInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentDetectionInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_IncidentDetectionInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentDetectionInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_IncidentDetectionInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentDetectionInfo *entry), void *ptr);
	Gitsn_IncidentDetectionInfo **(*get_array)(struct Gitsn_IncidentDetectionInfoResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_IncidentDetectionInfoResponse *p, Gitsn_IncidentDetectionInfo *data);
	Gitsn_IncidentDetectionInfo *(*extract)(struct Gitsn_IncidentDetectionInfoResponse *p, Gitsn_IncidentDetectionInfo *ptr);
	Gitsn_IncidentDetectionInfo *(*getHead)(struct Gitsn_IncidentDetectionInfoResponse *p);
} Gitsn_IncidentDetectionInfoResponse;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionInfoResponse *Gitsn_IncidentDetectionInfoResponse_new(Dz1Error *err);
static __inline__ Gitsn_IncidentDetectionInfoResponse *Gitsn_IncidentDetectionInfoResponse_gen(Dz1Error *err) { return Gitsn_IncidentDetectionInfoResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionInfoResponse *Gitsn_IncidentDetectionInfoResponse_clone(Gitsn_IncidentDetectionInfoResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionInfoResponse_purge(Gitsn_IncidentDetectionInfoResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionInfoResponse_del(Gitsn_IncidentDetectionInfoResponse *p);
static __inline__ void Gitsn_IncidentDetectionInfoResponse_delAndSetNull(void *ptr)
{
	Gitsn_IncidentDetectionInfoResponse **p = (Gitsn_IncidentDetectionInfoResponse **)ptr;
	if (p != NULL) { Gitsn_IncidentDetectionInfoResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionInfoResponse_dump(Gitsn_IncidentDetectionInfoResponse *p, int tab);

// Gitsn_IncidentDetectionInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentTerminationInfoResponse
typedef struct Gitsn_IncidentTerminationInfoResponse
{
	void *storage;
	unsigned int (*count)(struct Gitsn_IncidentTerminationInfoResponse *p);
	Dz1Error (*travel)(struct Gitsn_IncidentTerminationInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentTerminationInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_IncidentTerminationInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentTerminationInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_IncidentTerminationInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentTerminationInfo *entry), void *ptr);
	Gitsn_IncidentTerminationInfo **(*get_array)(struct Gitsn_IncidentTerminationInfoResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_IncidentTerminationInfoResponse *p, Gitsn_IncidentTerminationInfo *data);
	Gitsn_IncidentTerminationInfo *(*extract)(struct Gitsn_IncidentTerminationInfoResponse *p, Gitsn_IncidentTerminationInfo *ptr);
	Gitsn_IncidentTerminationInfo *(*getHead)(struct Gitsn_IncidentTerminationInfoResponse *p);
} Gitsn_IncidentTerminationInfoResponse;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentTerminationInfoResponse *Gitsn_IncidentTerminationInfoResponse_new(Dz1Error *err);
static __inline__ Gitsn_IncidentTerminationInfoResponse *Gitsn_IncidentTerminationInfoResponse_gen(Dz1Error *err) { return Gitsn_IncidentTerminationInfoResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentTerminationInfoResponse *Gitsn_IncidentTerminationInfoResponse_clone(Gitsn_IncidentTerminationInfoResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentTerminationInfoResponse_purge(Gitsn_IncidentTerminationInfoResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentTerminationInfoResponse_del(Gitsn_IncidentTerminationInfoResponse *p);
static __inline__ void Gitsn_IncidentTerminationInfoResponse_delAndSetNull(void *ptr)
{
	Gitsn_IncidentTerminationInfoResponse **p = (Gitsn_IncidentTerminationInfoResponse **)ptr;
	if (p != NULL) { Gitsn_IncidentTerminationInfoResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentTerminationInfoResponse_dump(Gitsn_IncidentTerminationInfoResponse *p, int tab);

// Gitsn_IncidentTerminationInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentDetectionVideoFileInfoProvideResponse
typedef struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse
{
	void *storage;
	unsigned int (*count)(struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p);
	Dz1Error (*travel)(struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentDetectionVideoFileInfoProvide *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentDetectionVideoFileInfoProvide *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p, Dz1Error (*func)(void *ptr, Gitsn_IncidentDetectionVideoFileInfoProvide *entry), void *ptr);
	Gitsn_IncidentDetectionVideoFileInfoProvide **(*get_array)(struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p, Gitsn_IncidentDetectionVideoFileInfoProvide *data);
	Gitsn_IncidentDetectionVideoFileInfoProvide *(*extract)(struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p, Gitsn_IncidentDetectionVideoFileInfoProvide *ptr);
	Gitsn_IncidentDetectionVideoFileInfoProvide *(*getHead)(struct Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p);
} Gitsn_IncidentDetectionVideoFileInfoProvideResponse;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionVideoFileInfoProvideResponse *Gitsn_IncidentDetectionVideoFileInfoProvideResponse_new(Dz1Error *err);
static __inline__ Gitsn_IncidentDetectionVideoFileInfoProvideResponse *Gitsn_IncidentDetectionVideoFileInfoProvideResponse_gen(Dz1Error *err) { return Gitsn_IncidentDetectionVideoFileInfoProvideResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_IncidentDetectionVideoFileInfoProvideResponse *Gitsn_IncidentDetectionVideoFileInfoProvideResponse_clone(Gitsn_IncidentDetectionVideoFileInfoProvideResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionVideoFileInfoProvideResponse_purge(Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionVideoFileInfoProvideResponse_del(Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p);
static __inline__ void Gitsn_IncidentDetectionVideoFileInfoProvideResponse_delAndSetNull(void *ptr)
{
	Gitsn_IncidentDetectionVideoFileInfoProvideResponse **p = (Gitsn_IncidentDetectionVideoFileInfoProvideResponse **)ptr;
	if (p != NULL) { Gitsn_IncidentDetectionVideoFileInfoProvideResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_IncidentDetectionVideoFileInfoProvideResponse_dump(Gitsn_IncidentDetectionVideoFileInfoProvideResponse *p, int tab);

// Gitsn_IncidentDetectionVideoFileInfoProvideResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ControlStateInfoResponse
typedef struct Gitsn_ControlStateInfoResponse
{
	void *storage;
	unsigned int (*count)(struct Gitsn_ControlStateInfoResponse *p);
	Dz1Error (*travel)(struct Gitsn_ControlStateInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_ControlStateInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_ControlStateInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_ControlStateInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_ControlStateInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_ControlStateInfo *entry), void *ptr);
	Gitsn_ControlStateInfo **(*get_array)(struct Gitsn_ControlStateInfoResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_ControlStateInfoResponse *p, Gitsn_ControlStateInfo *data);
	Gitsn_ControlStateInfo *(*extract)(struct Gitsn_ControlStateInfoResponse *p, Gitsn_ControlStateInfo *ptr);
	Gitsn_ControlStateInfo *(*getHead)(struct Gitsn_ControlStateInfoResponse *p);
} Gitsn_ControlStateInfoResponse;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_ControlStateInfoResponse *Gitsn_ControlStateInfoResponse_new(Dz1Error *err);
static __inline__ Gitsn_ControlStateInfoResponse *Gitsn_ControlStateInfoResponse_gen(Dz1Error *err) { return Gitsn_ControlStateInfoResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_ControlStateInfoResponse *Gitsn_ControlStateInfoResponse_clone(Gitsn_ControlStateInfoResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ControlStateInfoResponse_purge(Gitsn_ControlStateInfoResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ControlStateInfoResponse_del(Gitsn_ControlStateInfoResponse *p);
static __inline__ void Gitsn_ControlStateInfoResponse_delAndSetNull(void *ptr)
{
	Gitsn_ControlStateInfoResponse **p = (Gitsn_ControlStateInfoResponse **)ptr;
	if (p != NULL) { Gitsn_ControlStateInfoResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_ControlStateInfoResponse_dump(Gitsn_ControlStateInfoResponse *p, int tab);

// Gitsn_ControlStateInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SensorStateInfoResponse
typedef struct Gitsn_SensorStateInfoResponse
{
	void *storage;
	unsigned int (*count)(struct Gitsn_SensorStateInfoResponse *p);
	Dz1Error (*travel)(struct Gitsn_SensorStateInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_SensorStateInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_SensorStateInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_SensorStateInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_SensorStateInfoResponse *p, Dz1Error (*func)(void *ptr, Gitsn_SensorStateInfo *entry), void *ptr);
	Gitsn_SensorStateInfo **(*get_array)(struct Gitsn_SensorStateInfoResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_SensorStateInfoResponse *p, Gitsn_SensorStateInfo *data);
	Gitsn_SensorStateInfo *(*extract)(struct Gitsn_SensorStateInfoResponse *p, Gitsn_SensorStateInfo *ptr);
	Gitsn_SensorStateInfo *(*getHead)(struct Gitsn_SensorStateInfoResponse *p);
} Gitsn_SensorStateInfoResponse;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_SensorStateInfoResponse *Gitsn_SensorStateInfoResponse_new(Dz1Error *err);
static __inline__ Gitsn_SensorStateInfoResponse *Gitsn_SensorStateInfoResponse_gen(Dz1Error *err) { return Gitsn_SensorStateInfoResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_SensorStateInfoResponse *Gitsn_SensorStateInfoResponse_clone(Gitsn_SensorStateInfoResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorStateInfoResponse_purge(Gitsn_SensorStateInfoResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorStateInfoResponse_del(Gitsn_SensorStateInfoResponse *p);
static __inline__ void Gitsn_SensorStateInfoResponse_delAndSetNull(void *ptr)
{
	Gitsn_SensorStateInfoResponse **p = (Gitsn_SensorStateInfoResponse **)ptr;
	if (p != NULL) { Gitsn_SensorStateInfoResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_SensorStateInfoResponse_dump(Gitsn_SensorStateInfoResponse *p, int tab);

// Gitsn_SensorStateInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovingObjectResponse
typedef struct Gitsn_MovingObjectResponse
{
	void *storage;
	unsigned int (*count)(struct Gitsn_MovingObjectResponse *p);
	Dz1Error (*travel)(struct Gitsn_MovingObjectResponse *p, Dz1Error (*func)(void *ptr, Gitsn_MovingObject *entry), void *ptr);
	Dz1Error (*travelForward)(struct Gitsn_MovingObjectResponse *p, Dz1Error (*func)(void *ptr, Gitsn_MovingObject *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Gitsn_MovingObjectResponse *p, Dz1Error (*func)(void *ptr, Gitsn_MovingObject *entry), void *ptr);
	Gitsn_MovingObject **(*get_array)(struct Gitsn_MovingObjectResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Gitsn_MovingObjectResponse *p, Gitsn_MovingObject *data);
	Gitsn_MovingObject *(*extract)(struct Gitsn_MovingObjectResponse *p, Gitsn_MovingObject *ptr);
	Gitsn_MovingObject *(*getHead)(struct Gitsn_MovingObjectResponse *p);
} Gitsn_MovingObjectResponse;

DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovingObjectResponse *Gitsn_MovingObjectResponse_new(Dz1Error *err);
static __inline__ Gitsn_MovingObjectResponse *Gitsn_MovingObjectResponse_gen(Dz1Error *err) { return Gitsn_MovingObjectResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Gitsn_MovingObjectResponse *Gitsn_MovingObjectResponse_clone(Gitsn_MovingObjectResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovingObjectResponse_purge(Gitsn_MovingObjectResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovingObjectResponse_del(Gitsn_MovingObjectResponse *p);
static __inline__ void Gitsn_MovingObjectResponse_delAndSetNull(void *ptr)
{
	Gitsn_MovingObjectResponse **p = (Gitsn_MovingObjectResponse **)ptr;
	if (p != NULL) { Gitsn_MovingObjectResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Gitsn_MovingObjectResponse_dump(Gitsn_MovingObjectResponse *p, int tab);

// Gitsn_MovingObjectResponse
////////////////////////////////////////////////////////////////////////////////

#endif
