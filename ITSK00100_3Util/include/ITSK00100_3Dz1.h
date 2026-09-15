#ifndef _DZ1_TDC_I_T_S_K00100_3_DZ1_H_
#define _DZ1_TDC_I_T_S_K00100_3_DZ1_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"

#include <ITSK00100_3Eam.h>

////////////////////////////////////////////////////////////////////////////////
// Dz1ObjectID_00100
typedef s64_t Dz1ObjectID_00100;

#define Dz1ObjectID_00100_new               Dz1s64_new
#define Dz1ObjectID_00100_clone             Dz1s64_clone
#define Dz1ObjectID_00100_del               Dz1s64_del
#define Dz1ObjectID_00100_delAndSetNull     Dz1s64_delAndSetNull
#define Dz1ObjectID_00100A_dump             Dz1s64A_dump
#define Dz1ObjectID_00100A_fdump            Dz1s64A_fdump
#ifndef UNIX_SYSTEM
#define Dz1ObjectID_00100W_dump             Dz1s64W_dump
#define Dz1ObjectID_00100W_fdump            Dz1s64W_fdump
#ifdef UNICODE
#define Dz1ObjectID_00100_dump              Dz1s64W_dump
#define Dz1ObjectID_00100_fdump             Dz1s64W_fdump
#else //  UNICODE
#define Dz1ObjectID_00100_dump              Dz1s64A_dump
#define Dz1ObjectID_00100_fdump             Dz1s64A_fdump
#endif //  UNICODE
static __inline__ void Dz1ObjectID_00100X_dump(Dz1ObjectID_00100 *p, int tab) { DZ1_DUMP(Dz1ObjectID_00100, p, tab); }
static __inline__ void Dz1ObjectID_00100X_fdump(FILE *fp, Dz1ObjectID_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1ObjectID_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1ObjectID_00100_dump              Dz1s64A_dump
#define Dz1ObjectID_00100X_dump Dz1ObjectID_00100A_dump
#define Dz1ObjectID_00100_fdump             Dz1s64A_fdump
#define Dz1ObjectID_00100X_fdump Dz1ObjectID_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1ObjectID_00100_cmp               Dz1s64_cmp

// Dz1ObjectID_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DYear_00100
typedef u16_t Dz1DYear_00100;

#define Dz1DYear_00100_new               Dz1u16_new
#define Dz1DYear_00100_clone             Dz1u16_clone
#define Dz1DYear_00100_del               Dz1u16_del
#define Dz1DYear_00100_delAndSetNull     Dz1u16_delAndSetNull
#define Dz1DYear_00100A_dump             Dz1u16A_dump
#define Dz1DYear_00100A_fdump            Dz1u16A_fdump
#ifndef UNIX_SYSTEM
#define Dz1DYear_00100W_dump             Dz1u16W_dump
#define Dz1DYear_00100W_fdump            Dz1u16W_fdump
#ifdef UNICODE
#define Dz1DYear_00100_dump              Dz1u16W_dump
#define Dz1DYear_00100_fdump             Dz1u16W_fdump
#else //  UNICODE
#define Dz1DYear_00100_dump              Dz1u16A_dump
#define Dz1DYear_00100_fdump             Dz1u16A_fdump
#endif //  UNICODE
static __inline__ void Dz1DYear_00100X_dump(Dz1DYear_00100 *p, int tab) { DZ1_DUMP(Dz1DYear_00100, p, tab); }
static __inline__ void Dz1DYear_00100X_fdump(FILE *fp, Dz1DYear_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1DYear_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1DYear_00100_dump              Dz1u16A_dump
#define Dz1DYear_00100X_dump Dz1DYear_00100A_dump
#define Dz1DYear_00100_fdump             Dz1u16A_fdump
#define Dz1DYear_00100X_fdump Dz1DYear_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1DYear_00100_cmp               Dz1u16_cmp

// Dz1DYear_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DDay_00100
typedef u8_t Dz1DDay_00100;

#define Dz1DDay_00100_new               Dz1u8_new
#define Dz1DDay_00100_clone             Dz1u8_clone
#define Dz1DDay_00100_del               Dz1u8_del
#define Dz1DDay_00100_delAndSetNull     Dz1u8_delAndSetNull
#define Dz1DDay_00100A_dump             Dz1u8A_dump
#define Dz1DDay_00100A_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Dz1DDay_00100W_dump             Dz1u8W_dump
#define Dz1DDay_00100W_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Dz1DDay_00100_dump              Dz1u8W_dump
#define Dz1DDay_00100_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Dz1DDay_00100_dump              Dz1u8A_dump
#define Dz1DDay_00100_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Dz1DDay_00100X_dump(Dz1DDay_00100 *p, int tab) { DZ1_DUMP(Dz1DDay_00100, p, tab); }
static __inline__ void Dz1DDay_00100X_fdump(FILE *fp, Dz1DDay_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1DDay_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1DDay_00100_dump              Dz1u8A_dump
#define Dz1DDay_00100X_dump Dz1DDay_00100A_dump
#define Dz1DDay_00100_fdump             Dz1u8A_fdump
#define Dz1DDay_00100X_fdump Dz1DDay_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1DDay_00100_cmp               Dz1u8_cmp

// Dz1DDay_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DHour_00100
typedef u8_t Dz1DHour_00100;

#define Dz1DHour_00100_new               Dz1u8_new
#define Dz1DHour_00100_clone             Dz1u8_clone
#define Dz1DHour_00100_del               Dz1u8_del
#define Dz1DHour_00100_delAndSetNull     Dz1u8_delAndSetNull
#define Dz1DHour_00100A_dump             Dz1u8A_dump
#define Dz1DHour_00100A_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Dz1DHour_00100W_dump             Dz1u8W_dump
#define Dz1DHour_00100W_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Dz1DHour_00100_dump              Dz1u8W_dump
#define Dz1DHour_00100_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Dz1DHour_00100_dump              Dz1u8A_dump
#define Dz1DHour_00100_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Dz1DHour_00100X_dump(Dz1DHour_00100 *p, int tab) { DZ1_DUMP(Dz1DHour_00100, p, tab); }
static __inline__ void Dz1DHour_00100X_fdump(FILE *fp, Dz1DHour_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1DHour_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1DHour_00100_dump              Dz1u8A_dump
#define Dz1DHour_00100X_dump Dz1DHour_00100A_dump
#define Dz1DHour_00100_fdump             Dz1u8A_fdump
#define Dz1DHour_00100X_fdump Dz1DHour_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1DHour_00100_cmp               Dz1u8_cmp

// Dz1DHour_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DMinute_00100
typedef u8_t Dz1DMinute_00100;

#define Dz1DMinute_00100_new               Dz1u8_new
#define Dz1DMinute_00100_clone             Dz1u8_clone
#define Dz1DMinute_00100_del               Dz1u8_del
#define Dz1DMinute_00100_delAndSetNull     Dz1u8_delAndSetNull
#define Dz1DMinute_00100A_dump             Dz1u8A_dump
#define Dz1DMinute_00100A_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Dz1DMinute_00100W_dump             Dz1u8W_dump
#define Dz1DMinute_00100W_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Dz1DMinute_00100_dump              Dz1u8W_dump
#define Dz1DMinute_00100_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Dz1DMinute_00100_dump              Dz1u8A_dump
#define Dz1DMinute_00100_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Dz1DMinute_00100X_dump(Dz1DMinute_00100 *p, int tab) { DZ1_DUMP(Dz1DMinute_00100, p, tab); }
static __inline__ void Dz1DMinute_00100X_fdump(FILE *fp, Dz1DMinute_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1DMinute_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1DMinute_00100_dump              Dz1u8A_dump
#define Dz1DMinute_00100X_dump Dz1DMinute_00100A_dump
#define Dz1DMinute_00100_fdump             Dz1u8A_fdump
#define Dz1DMinute_00100X_fdump Dz1DMinute_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1DMinute_00100_cmp               Dz1u8_cmp

// Dz1DMinute_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DMonth_00100
typedef u8_t Dz1DMonth_00100;

#define Dz1DMonth_00100_new               Dz1u8_new
#define Dz1DMonth_00100_clone             Dz1u8_clone
#define Dz1DMonth_00100_del               Dz1u8_del
#define Dz1DMonth_00100_delAndSetNull     Dz1u8_delAndSetNull
#define Dz1DMonth_00100A_dump             Dz1u8A_dump
#define Dz1DMonth_00100A_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Dz1DMonth_00100W_dump             Dz1u8W_dump
#define Dz1DMonth_00100W_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Dz1DMonth_00100_dump              Dz1u8W_dump
#define Dz1DMonth_00100_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Dz1DMonth_00100_dump              Dz1u8A_dump
#define Dz1DMonth_00100_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Dz1DMonth_00100X_dump(Dz1DMonth_00100 *p, int tab) { DZ1_DUMP(Dz1DMonth_00100, p, tab); }
static __inline__ void Dz1DMonth_00100X_fdump(FILE *fp, Dz1DMonth_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1DMonth_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1DMonth_00100_dump              Dz1u8A_dump
#define Dz1DMonth_00100X_dump Dz1DMonth_00100A_dump
#define Dz1DMonth_00100_fdump             Dz1u8A_fdump
#define Dz1DMonth_00100X_fdump Dz1DMonth_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1DMonth_00100_cmp               Dz1u8_cmp

// Dz1DMonth_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DOffset_00100
typedef s16_t Dz1DOffset_00100;

#define Dz1DOffset_00100_new               Dz1s16_new
#define Dz1DOffset_00100_clone             Dz1s16_clone
#define Dz1DOffset_00100_del               Dz1s16_del
#define Dz1DOffset_00100_delAndSetNull     Dz1s16_delAndSetNull
#define Dz1DOffset_00100A_dump             Dz1s16A_dump
#define Dz1DOffset_00100A_fdump            Dz1s16A_fdump
#ifndef UNIX_SYSTEM
#define Dz1DOffset_00100W_dump             Dz1s16W_dump
#define Dz1DOffset_00100W_fdump            Dz1s16W_fdump
#ifdef UNICODE
#define Dz1DOffset_00100_dump              Dz1s16W_dump
#define Dz1DOffset_00100_fdump             Dz1s16W_fdump
#else //  UNICODE
#define Dz1DOffset_00100_dump              Dz1s16A_dump
#define Dz1DOffset_00100_fdump             Dz1s16A_fdump
#endif //  UNICODE
static __inline__ void Dz1DOffset_00100X_dump(Dz1DOffset_00100 *p, int tab) { DZ1_DUMP(Dz1DOffset_00100, p, tab); }
static __inline__ void Dz1DOffset_00100X_fdump(FILE *fp, Dz1DOffset_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1DOffset_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1DOffset_00100_dump              Dz1s16A_dump
#define Dz1DOffset_00100X_dump Dz1DOffset_00100A_dump
#define Dz1DOffset_00100_fdump             Dz1s16A_fdump
#define Dz1DOffset_00100X_fdump Dz1DOffset_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1DOffset_00100_cmp               Dz1s16_cmp

// Dz1DOffset_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DSecond_00100
typedef u16_t Dz1DSecond_00100;

#define Dz1DSecond_00100_new               Dz1u16_new
#define Dz1DSecond_00100_clone             Dz1u16_clone
#define Dz1DSecond_00100_del               Dz1u16_del
#define Dz1DSecond_00100_delAndSetNull     Dz1u16_delAndSetNull
#define Dz1DSecond_00100A_dump             Dz1u16A_dump
#define Dz1DSecond_00100A_fdump            Dz1u16A_fdump
#ifndef UNIX_SYSTEM
#define Dz1DSecond_00100W_dump             Dz1u16W_dump
#define Dz1DSecond_00100W_fdump            Dz1u16W_fdump
#ifdef UNICODE
#define Dz1DSecond_00100_dump              Dz1u16W_dump
#define Dz1DSecond_00100_fdump             Dz1u16W_fdump
#else //  UNICODE
#define Dz1DSecond_00100_dump              Dz1u16A_dump
#define Dz1DSecond_00100_fdump             Dz1u16A_fdump
#endif //  UNICODE
static __inline__ void Dz1DSecond_00100X_dump(Dz1DSecond_00100 *p, int tab) { DZ1_DUMP(Dz1DSecond_00100, p, tab); }
static __inline__ void Dz1DSecond_00100X_fdump(FILE *fp, Dz1DSecond_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1DSecond_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1DSecond_00100_dump              Dz1u16A_dump
#define Dz1DSecond_00100X_dump Dz1DSecond_00100A_dump
#define Dz1DSecond_00100_fdump             Dz1u16A_fdump
#define Dz1DSecond_00100X_fdump Dz1DSecond_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1DSecond_00100_cmp               Dz1u16_cmp

// Dz1DSecond_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DDateTime_00100
typedef struct Dz1DDateTime_00100
{
	Dz1DYear_00100		*year;
	Dz1DMonth_00100		*month;
	Dz1DDay_00100		*day;
	Dz1DHour_00100		*hour;
	Dz1DMinute_00100	*minute;
	Dz1DSecond_00100	*second;
	Dz1DOffset_00100	*offset;
} Dz1DDateTime_00100;

DZ1_CPPLINK DZ1_DLLPORT Dz1DDateTime_00100 *Dz1DDateTime_00100_new(Dz1Error *err);
static __inline__ Dz1DDateTime_00100 *Dz1DDateTime_00100_gen(Dz1Error *err) { return Dz1DDateTime_00100_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1DDateTime_00100_copy(Dz1DDateTime_00100 *dst, Dz1DDateTime_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1DDateTime_00100 *Dz1DDateTime_00100_clone(Dz1DDateTime_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DDateTime_00100_purge(Dz1DDateTime_00100 *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DDateTime_00100_del(Dz1DDateTime_00100 *p);
static __inline__ void Dz1DDateTime_00100_delAndSetNull(void *ptr)
{
	Dz1DDateTime_00100 **p = (Dz1DDateTime_00100 **)ptr;
	if (p) { Dz1DDateTime_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1DDateTime_00100_dump(Dz1DDateTime_00100 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DDateTime_00100_fdump(FILE *fp, Dz1DDateTime_00100 *p, int tab);
// Dz1DDateTime_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Longitude_00100
typedef s32_t Dz1Longitude_00100;

#define Dz1Longitude_00100_new               Dz1s32_new
#define Dz1Longitude_00100_clone             Dz1s32_clone
#define Dz1Longitude_00100_del               Dz1s32_del
#define Dz1Longitude_00100_delAndSetNull     Dz1s32_delAndSetNull
#define Dz1Longitude_00100A_dump             Dz1s32A_dump
#define Dz1Longitude_00100A_fdump            Dz1s32A_fdump
#ifndef UNIX_SYSTEM
#define Dz1Longitude_00100W_dump             Dz1s32W_dump
#define Dz1Longitude_00100W_fdump            Dz1s32W_fdump
#ifdef UNICODE
#define Dz1Longitude_00100_dump              Dz1s32W_dump
#define Dz1Longitude_00100_fdump             Dz1s32W_fdump
#else //  UNICODE
#define Dz1Longitude_00100_dump              Dz1s32A_dump
#define Dz1Longitude_00100_fdump             Dz1s32A_fdump
#endif //  UNICODE
static __inline__ void Dz1Longitude_00100X_dump(Dz1Longitude_00100 *p, int tab) { DZ1_DUMP(Dz1Longitude_00100, p, tab); }
static __inline__ void Dz1Longitude_00100X_fdump(FILE *fp, Dz1Longitude_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1Longitude_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Longitude_00100_dump              Dz1s32A_dump
#define Dz1Longitude_00100X_dump Dz1Longitude_00100A_dump
#define Dz1Longitude_00100_fdump             Dz1s32A_fdump
#define Dz1Longitude_00100X_fdump Dz1Longitude_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1Longitude_00100_cmp               Dz1s32_cmp

// Dz1Longitude_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Latitude_00100
typedef s32_t Dz1Latitude_00100;

#define Dz1Latitude_00100_new               Dz1s32_new
#define Dz1Latitude_00100_clone             Dz1s32_clone
#define Dz1Latitude_00100_del               Dz1s32_del
#define Dz1Latitude_00100_delAndSetNull     Dz1s32_delAndSetNull
#define Dz1Latitude_00100A_dump             Dz1s32A_dump
#define Dz1Latitude_00100A_fdump            Dz1s32A_fdump
#ifndef UNIX_SYSTEM
#define Dz1Latitude_00100W_dump             Dz1s32W_dump
#define Dz1Latitude_00100W_fdump            Dz1s32W_fdump
#ifdef UNICODE
#define Dz1Latitude_00100_dump              Dz1s32W_dump
#define Dz1Latitude_00100_fdump             Dz1s32W_fdump
#else //  UNICODE
#define Dz1Latitude_00100_dump              Dz1s32A_dump
#define Dz1Latitude_00100_fdump             Dz1s32A_fdump
#endif //  UNICODE
static __inline__ void Dz1Latitude_00100X_dump(Dz1Latitude_00100 *p, int tab) { DZ1_DUMP(Dz1Latitude_00100, p, tab); }
static __inline__ void Dz1Latitude_00100X_fdump(FILE *fp, Dz1Latitude_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1Latitude_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Latitude_00100_dump              Dz1s32A_dump
#define Dz1Latitude_00100X_dump Dz1Latitude_00100A_dump
#define Dz1Latitude_00100_fdump             Dz1s32A_fdump
#define Dz1Latitude_00100X_fdump Dz1Latitude_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1Latitude_00100_cmp               Dz1s32_cmp

// Dz1Latitude_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Elevation_00100
typedef s32_t Dz1Elevation_00100;

#define Dz1Elevation_00100_new               Dz1s32_new
#define Dz1Elevation_00100_clone             Dz1s32_clone
#define Dz1Elevation_00100_del               Dz1s32_del
#define Dz1Elevation_00100_delAndSetNull     Dz1s32_delAndSetNull
#define Dz1Elevation_00100A_dump             Dz1s32A_dump
#define Dz1Elevation_00100A_fdump            Dz1s32A_fdump
#ifndef UNIX_SYSTEM
#define Dz1Elevation_00100W_dump             Dz1s32W_dump
#define Dz1Elevation_00100W_fdump            Dz1s32W_fdump
#ifdef UNICODE
#define Dz1Elevation_00100_dump              Dz1s32W_dump
#define Dz1Elevation_00100_fdump             Dz1s32W_fdump
#else //  UNICODE
#define Dz1Elevation_00100_dump              Dz1s32A_dump
#define Dz1Elevation_00100_fdump             Dz1s32A_fdump
#endif //  UNICODE
static __inline__ void Dz1Elevation_00100X_dump(Dz1Elevation_00100 *p, int tab) { DZ1_DUMP(Dz1Elevation_00100, p, tab); }
static __inline__ void Dz1Elevation_00100X_fdump(FILE *fp, Dz1Elevation_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1Elevation_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Elevation_00100_dump              Dz1s32A_dump
#define Dz1Elevation_00100X_dump Dz1Elevation_00100A_dump
#define Dz1Elevation_00100_fdump             Dz1s32A_fdump
#define Dz1Elevation_00100X_fdump Dz1Elevation_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1Elevation_00100_cmp               Dz1s32_cmp

// Dz1Elevation_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TransmissionState_00100
typedef enum Dz1TransmissionState_00100
{
	Dz1TransmissionState_00100_neutral = 0,
	Dz1TransmissionState_00100_park = 1,
	Dz1TransmissionState_00100_forwardGears = 2,
	Dz1TransmissionState_00100_reverseGears = 3,
	Dz1TransmissionState_00100_reserved1 = 4,
	Dz1TransmissionState_00100_reserved2 = 5,
	Dz1TransmissionState_00100_reserved3 = 6,
	Dz1TransmissionState_00100_unavailable = 7,
	Dz1TransmissionState_00100_max
} Dz1TransmissionState_00100;

DZ1_CPPLINK str_t Dz1TransmissionState_00100StrA(Dz1TransmissionState_00100 v);
DZ1_CPPLINK Dz1TransmissionState_00100 Dz1TransmissionState_00100FromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TransmissionState_00100StrW(Dz1TransmissionState_00100 v);
DZ1_CPPLINK Dz1TransmissionState_00100 Dz1TransmissionState_00100FromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TransmissionState_00100Str Dz1TransmissionState_00100StrW
#define Dz1TransmissionState_00100FromStr Dz1TransmissionState_00100FromStrW
#else // UNICODE
#define Dz1TransmissionState_00100Str Dz1TransmissionState_00100StrA
#define Dz1TransmissionState_00100FromStr Dz1TransmissionState_00100FromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TransmissionState_00100Str Dz1TransmissionState_00100StrA
#define Dz1TransmissionState_00100FromStr Dz1TransmissionState_00100FromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TransmissionState_00100 *Dz1TransmissionState_00100_new(Dz1TransmissionState_00100 *src, Dz1Error *err);
static __inline__ Dz1TransmissionState_00100 *Dz1TransmissionState_00100_gen(Dz1Error *err) { Dz1TransmissionState_00100 v = Dz1TransmissionState_00100_max; return Dz1TransmissionState_00100_new(&v, err); }
#define Dz1TransmissionState_00100_clone             Dz1TransmissionState_00100_new
static __inline__ void Dz1TransmissionState_00100_del(Dz1TransmissionState_00100 *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TransmissionState_00100_delAndSetNull(void *ptr)
{
	Dz1TransmissionState_00100 **p = (Dz1TransmissionState_00100 **)ptr;
	if (p != NULL) { Dz1TransmissionState_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TransmissionState_00100_dump(Dz1TransmissionState_00100 *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TransmissionState_00100_fdump(FILE *fp, Dz1TransmissionState_00100 *v, int tab);
// Dz1TransmissionState_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TransmissionAndSpeed_00100
enum Dz1TransmissionState_00100;

typedef struct Dz1TransmissionAndSpeed_00100
{
	enum Dz1TransmissionState_00100		transmisson;
	u16_t								speed;
} Dz1TransmissionAndSpeed_00100;

DZ1_CPPLINK DZ1_DLLPORT Dz1TransmissionAndSpeed_00100 *Dz1TransmissionAndSpeed_00100_new(enum Dz1TransmissionState_00100 transmisson, 
																						 u16_t speed, Dz1Error *err);
static __inline__ Dz1TransmissionAndSpeed_00100 *Dz1TransmissionAndSpeed_00100_gen(Dz1Error *err) { return Dz1TransmissionAndSpeed_00100_new(Dz1TransmissionState_00100_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TransmissionAndSpeed_00100_copy(Dz1TransmissionAndSpeed_00100 *dst, Dz1TransmissionAndSpeed_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TransmissionAndSpeed_00100 *Dz1TransmissionAndSpeed_00100_clone(Dz1TransmissionAndSpeed_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TransmissionAndSpeed_00100_purge(Dz1TransmissionAndSpeed_00100 *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TransmissionAndSpeed_00100_del(Dz1TransmissionAndSpeed_00100 *p);
static __inline__ void Dz1TransmissionAndSpeed_00100_delAndSetNull(void *ptr)
{
	Dz1TransmissionAndSpeed_00100 **p = (Dz1TransmissionAndSpeed_00100 **)ptr;
	if (p) { Dz1TransmissionAndSpeed_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TransmissionAndSpeed_00100_dump(Dz1TransmissionAndSpeed_00100 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TransmissionAndSpeed_00100_fdump(FILE *fp, Dz1TransmissionAndSpeed_00100 *p, int tab);
// Dz1TransmissionAndSpeed_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Velocity_00100
typedef u16_t Dz1Velocity_00100;

#define Dz1Velocity_00100_new               Dz1u16_new
#define Dz1Velocity_00100_clone             Dz1u16_clone
#define Dz1Velocity_00100_del               Dz1u16_del
#define Dz1Velocity_00100_delAndSetNull     Dz1u16_delAndSetNull
#define Dz1Velocity_00100A_dump             Dz1u16A_dump
#define Dz1Velocity_00100A_fdump            Dz1u16A_fdump
#ifndef UNIX_SYSTEM
#define Dz1Velocity_00100W_dump             Dz1u16W_dump
#define Dz1Velocity_00100W_fdump            Dz1u16W_fdump
#ifdef UNICODE
#define Dz1Velocity_00100_dump              Dz1u16W_dump
#define Dz1Velocity_00100_fdump             Dz1u16W_fdump
#else //  UNICODE
#define Dz1Velocity_00100_dump              Dz1u16A_dump
#define Dz1Velocity_00100_fdump             Dz1u16A_fdump
#endif //  UNICODE
static __inline__ void Dz1Velocity_00100X_dump(Dz1Velocity_00100 *p, int tab) { DZ1_DUMP(Dz1Velocity_00100, p, tab); }
static __inline__ void Dz1Velocity_00100X_fdump(FILE *fp, Dz1Velocity_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1Velocity_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Velocity_00100_dump              Dz1u16A_dump
#define Dz1Velocity_00100X_dump Dz1Velocity_00100A_dump
#define Dz1Velocity_00100_fdump             Dz1u16A_fdump
#define Dz1Velocity_00100X_fdump Dz1Velocity_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1Velocity_00100_cmp               Dz1u16_cmp

// Dz1Velocity_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Heading_00100
typedef u16_t Dz1Heading_00100;

#define Dz1Heading_00100_new               Dz1u16_new
#define Dz1Heading_00100_clone             Dz1u16_clone
#define Dz1Heading_00100_del               Dz1u16_del
#define Dz1Heading_00100_delAndSetNull     Dz1u16_delAndSetNull
#define Dz1Heading_00100A_dump             Dz1u16A_dump
#define Dz1Heading_00100A_fdump            Dz1u16A_fdump
#ifndef UNIX_SYSTEM
#define Dz1Heading_00100W_dump             Dz1u16W_dump
#define Dz1Heading_00100W_fdump            Dz1u16W_fdump
#ifdef UNICODE
#define Dz1Heading_00100_dump              Dz1u16W_dump
#define Dz1Heading_00100_fdump             Dz1u16W_fdump
#else //  UNICODE
#define Dz1Heading_00100_dump              Dz1u16A_dump
#define Dz1Heading_00100_fdump             Dz1u16A_fdump
#endif //  UNICODE
static __inline__ void Dz1Heading_00100X_dump(Dz1Heading_00100 *p, int tab) { DZ1_DUMP(Dz1Heading_00100, p, tab); }
static __inline__ void Dz1Heading_00100X_fdump(FILE *fp, Dz1Heading_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1Heading_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Heading_00100_dump              Dz1u16A_dump
#define Dz1Heading_00100X_dump Dz1Heading_00100A_dump
#define Dz1Heading_00100_fdump             Dz1u16A_fdump
#define Dz1Heading_00100X_fdump Dz1Heading_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1Heading_00100_cmp               Dz1u16_cmp

// Dz1Heading_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1PositionalAccuracy_00100
typedef struct Dz1PositionalAccuracy_00100
{
	u8_t		semiMajor;
	u8_t		semiMinor;
	u16_t		orientation;
} Dz1PositionalAccuracy_00100;

DZ1_CPPLINK DZ1_DLLPORT Dz1PositionalAccuracy_00100 *Dz1PositionalAccuracy_00100_new(u8_t semiMajor, 
																					 u8_t semiMinor, 
																					 u16_t orientation, Dz1Error *err);
static __inline__ Dz1PositionalAccuracy_00100 *Dz1PositionalAccuracy_00100_gen(Dz1Error *err) { return Dz1PositionalAccuracy_00100_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1PositionalAccuracy_00100_copy(Dz1PositionalAccuracy_00100 *dst, Dz1PositionalAccuracy_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1PositionalAccuracy_00100 *Dz1PositionalAccuracy_00100_clone(Dz1PositionalAccuracy_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionalAccuracy_00100_purge(Dz1PositionalAccuracy_00100 *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionalAccuracy_00100_del(Dz1PositionalAccuracy_00100 *p);
static __inline__ void Dz1PositionalAccuracy_00100_delAndSetNull(void *ptr)
{
	Dz1PositionalAccuracy_00100 **p = (Dz1PositionalAccuracy_00100 **)ptr;
	if (p) { Dz1PositionalAccuracy_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionalAccuracy_00100_dump(Dz1PositionalAccuracy_00100 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionalAccuracy_00100_fdump(FILE *fp, Dz1PositionalAccuracy_00100 *p, int tab);
// Dz1PositionalAccuracy_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SemiMajorAxisAccuracy_00100
typedef u8_t Dz1SemiMajorAxisAccuracy_00100;

#define Dz1SemiMajorAxisAccuracy_00100_new               Dz1u8_new
#define Dz1SemiMajorAxisAccuracy_00100_clone             Dz1u8_clone
#define Dz1SemiMajorAxisAccuracy_00100_del               Dz1u8_del
#define Dz1SemiMajorAxisAccuracy_00100_delAndSetNull     Dz1u8_delAndSetNull
#define Dz1SemiMajorAxisAccuracy_00100A_dump             Dz1u8A_dump
#define Dz1SemiMajorAxisAccuracy_00100A_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Dz1SemiMajorAxisAccuracy_00100W_dump             Dz1u8W_dump
#define Dz1SemiMajorAxisAccuracy_00100W_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Dz1SemiMajorAxisAccuracy_00100_dump              Dz1u8W_dump
#define Dz1SemiMajorAxisAccuracy_00100_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Dz1SemiMajorAxisAccuracy_00100_dump              Dz1u8A_dump
#define Dz1SemiMajorAxisAccuracy_00100_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Dz1SemiMajorAxisAccuracy_00100X_dump(Dz1SemiMajorAxisAccuracy_00100 *p, int tab) { DZ1_DUMP(Dz1SemiMajorAxisAccuracy_00100, p, tab); }
static __inline__ void Dz1SemiMajorAxisAccuracy_00100X_fdump(FILE *fp, Dz1SemiMajorAxisAccuracy_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1SemiMajorAxisAccuracy_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SemiMajorAxisAccuracy_00100_dump              Dz1u8A_dump
#define Dz1SemiMajorAxisAccuracy_00100X_dump Dz1SemiMajorAxisAccuracy_00100A_dump
#define Dz1SemiMajorAxisAccuracy_00100_fdump             Dz1u8A_fdump
#define Dz1SemiMajorAxisAccuracy_00100X_fdump Dz1SemiMajorAxisAccuracy_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1SemiMajorAxisAccuracy_00100_cmp               Dz1u8_cmp

// Dz1SemiMajorAxisAccuracy_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SemiMajorAxisOrientation_00100
typedef u16_t Dz1SemiMajorAxisOrientation_00100;

#define Dz1SemiMajorAxisOrientation_00100_new               Dz1u16_new
#define Dz1SemiMajorAxisOrientation_00100_clone             Dz1u16_clone
#define Dz1SemiMajorAxisOrientation_00100_del               Dz1u16_del
#define Dz1SemiMajorAxisOrientation_00100_delAndSetNull     Dz1u16_delAndSetNull
#define Dz1SemiMajorAxisOrientation_00100A_dump             Dz1u16A_dump
#define Dz1SemiMajorAxisOrientation_00100A_fdump            Dz1u16A_fdump
#ifndef UNIX_SYSTEM
#define Dz1SemiMajorAxisOrientation_00100W_dump             Dz1u16W_dump
#define Dz1SemiMajorAxisOrientation_00100W_fdump            Dz1u16W_fdump
#ifdef UNICODE
#define Dz1SemiMajorAxisOrientation_00100_dump              Dz1u16W_dump
#define Dz1SemiMajorAxisOrientation_00100_fdump             Dz1u16W_fdump
#else //  UNICODE
#define Dz1SemiMajorAxisOrientation_00100_dump              Dz1u16A_dump
#define Dz1SemiMajorAxisOrientation_00100_fdump             Dz1u16A_fdump
#endif //  UNICODE
static __inline__ void Dz1SemiMajorAxisOrientation_00100X_dump(Dz1SemiMajorAxisOrientation_00100 *p, int tab) { DZ1_DUMP(Dz1SemiMajorAxisOrientation_00100, p, tab); }
static __inline__ void Dz1SemiMajorAxisOrientation_00100X_fdump(FILE *fp, Dz1SemiMajorAxisOrientation_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1SemiMajorAxisOrientation_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SemiMajorAxisOrientation_00100_dump              Dz1u16A_dump
#define Dz1SemiMajorAxisOrientation_00100X_dump Dz1SemiMajorAxisOrientation_00100A_dump
#define Dz1SemiMajorAxisOrientation_00100_fdump             Dz1u16A_fdump
#define Dz1SemiMajorAxisOrientation_00100X_fdump Dz1SemiMajorAxisOrientation_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1SemiMajorAxisOrientation_00100_cmp               Dz1u16_cmp

// Dz1SemiMajorAxisOrientation_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SemiMinorAxisAccuracy_00100
typedef u8_t Dz1SemiMinorAxisAccuracy_00100;

#define Dz1SemiMinorAxisAccuracy_00100_new               Dz1u8_new
#define Dz1SemiMinorAxisAccuracy_00100_clone             Dz1u8_clone
#define Dz1SemiMinorAxisAccuracy_00100_del               Dz1u8_del
#define Dz1SemiMinorAxisAccuracy_00100_delAndSetNull     Dz1u8_delAndSetNull
#define Dz1SemiMinorAxisAccuracy_00100A_dump             Dz1u8A_dump
#define Dz1SemiMinorAxisAccuracy_00100A_fdump            Dz1u8A_fdump
#ifndef UNIX_SYSTEM
#define Dz1SemiMinorAxisAccuracy_00100W_dump             Dz1u8W_dump
#define Dz1SemiMinorAxisAccuracy_00100W_fdump            Dz1u8W_fdump
#ifdef UNICODE
#define Dz1SemiMinorAxisAccuracy_00100_dump              Dz1u8W_dump
#define Dz1SemiMinorAxisAccuracy_00100_fdump             Dz1u8W_fdump
#else //  UNICODE
#define Dz1SemiMinorAxisAccuracy_00100_dump              Dz1u8A_dump
#define Dz1SemiMinorAxisAccuracy_00100_fdump             Dz1u8A_fdump
#endif //  UNICODE
static __inline__ void Dz1SemiMinorAxisAccuracy_00100X_dump(Dz1SemiMinorAxisAccuracy_00100 *p, int tab) { DZ1_DUMP(Dz1SemiMinorAxisAccuracy_00100, p, tab); }
static __inline__ void Dz1SemiMinorAxisAccuracy_00100X_fdump(FILE *fp, Dz1SemiMinorAxisAccuracy_00100 *p, int tab) { DZ1_FDUMP(fp, Dz1SemiMinorAxisAccuracy_00100, p, tab); }
#else // UNIX_SYSTEM
#define Dz1SemiMinorAxisAccuracy_00100_dump              Dz1u8A_dump
#define Dz1SemiMinorAxisAccuracy_00100X_dump Dz1SemiMinorAxisAccuracy_00100A_dump
#define Dz1SemiMinorAxisAccuracy_00100_fdump             Dz1u8A_fdump
#define Dz1SemiMinorAxisAccuracy_00100X_fdump Dz1SemiMinorAxisAccuracy_00100A_fdump
#endif // UNIX_SYSTEM
#define Dz1SemiMinorAxisAccuracy_00100_cmp               Dz1u8_cmp

// Dz1SemiMinorAxisAccuracy_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TimeConfidence_00100
typedef enum Dz1TimeConfidence_00100
{
	Dz1TimeConfidence_00100_unavailable = 0,
	Dz1TimeConfidence_00100_time_100_000 = 1,
	Dz1TimeConfidence_00100_time_050_000 = 2,
	Dz1TimeConfidence_00100_time_020_000 = 3,
	Dz1TimeConfidence_00100_time_010_000 = 4,
	Dz1TimeConfidence_00100_time_002_000 = 5,
	Dz1TimeConfidence_00100_time_001_000 = 6,
	Dz1TimeConfidence_00100_time_000_500 = 7,
	Dz1TimeConfidence_00100_time_000_200 = 8,
	Dz1TimeConfidence_00100_time_000_100 = 9,
	Dz1TimeConfidence_00100_time_000_050 = 10,
	Dz1TimeConfidence_00100_time_000_020 = 11,
	Dz1TimeConfidence_00100_time_000_010 = 12,
	Dz1TimeConfidence_00100_time_000_005 = 13,
	Dz1TimeConfidence_00100_time_000_002 = 14,
	Dz1TimeConfidence_00100_time_000_001 = 15,
	Dz1TimeConfidence_00100_time_000_000_5 = 16,
	Dz1TimeConfidence_00100_time_000_000_2 = 17,
	Dz1TimeConfidence_00100_time_000_000_1 = 18,
	Dz1TimeConfidence_00100_time_000_000_05 = 19,
	Dz1TimeConfidence_00100_time_000_000_02 = 20,
	Dz1TimeConfidence_00100_time_000_000_01 = 21,
	Dz1TimeConfidence_00100_time_000_000_005 = 22,
	Dz1TimeConfidence_00100_time_000_000_002 = 23,
	Dz1TimeConfidence_00100_time_000_000_001 = 24,
	Dz1TimeConfidence_00100_time_000_000_000_5 = 25,
	Dz1TimeConfidence_00100_time_000_000_000_2 = 26,
	Dz1TimeConfidence_00100_time_000_000_000_1 = 27,
	Dz1TimeConfidence_00100_time_000_000_000_05 = 28,
	Dz1TimeConfidence_00100_time_000_000_000_02 = 29,
	Dz1TimeConfidence_00100_time_000_000_000_01 = 30,
	Dz1TimeConfidence_00100_time_000_000_000_005 = 31,
	Dz1TimeConfidence_00100_time_000_000_000_002 = 32,
	Dz1TimeConfidence_00100_time_000_000_000_001 = 33,
	Dz1TimeConfidence_00100_time_000_000_000_000_5 = 34,
	Dz1TimeConfidence_00100_time_000_000_000_000_2 = 35,
	Dz1TimeConfidence_00100_time_000_000_000_000_1 = 36,
	Dz1TimeConfidence_00100_time_000_000_000_000_05 = 37,
	Dz1TimeConfidence_00100_time_000_000_000_000_02 = 38,
	Dz1TimeConfidence_00100_time_000_000_000_000_01 = 39,
	Dz1TimeConfidence_00100_max
} Dz1TimeConfidence_00100;

DZ1_CPPLINK str_t Dz1TimeConfidence_00100StrA(Dz1TimeConfidence_00100 v);
DZ1_CPPLINK Dz1TimeConfidence_00100 Dz1TimeConfidence_00100FromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TimeConfidence_00100StrW(Dz1TimeConfidence_00100 v);
DZ1_CPPLINK Dz1TimeConfidence_00100 Dz1TimeConfidence_00100FromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TimeConfidence_00100Str Dz1TimeConfidence_00100StrW
#define Dz1TimeConfidence_00100FromStr Dz1TimeConfidence_00100FromStrW
#else // UNICODE
#define Dz1TimeConfidence_00100Str Dz1TimeConfidence_00100StrA
#define Dz1TimeConfidence_00100FromStr Dz1TimeConfidence_00100FromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TimeConfidence_00100Str Dz1TimeConfidence_00100StrA
#define Dz1TimeConfidence_00100FromStr Dz1TimeConfidence_00100FromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TimeConfidence_00100 *Dz1TimeConfidence_00100_new(Dz1TimeConfidence_00100 *src, Dz1Error *err);
static __inline__ Dz1TimeConfidence_00100 *Dz1TimeConfidence_00100_gen(Dz1Error *err) { Dz1TimeConfidence_00100 v = Dz1TimeConfidence_00100_max; return Dz1TimeConfidence_00100_new(&v, err); }
#define Dz1TimeConfidence_00100_clone             Dz1TimeConfidence_00100_new
static __inline__ void Dz1TimeConfidence_00100_del(Dz1TimeConfidence_00100 *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TimeConfidence_00100_delAndSetNull(void *ptr)
{
	Dz1TimeConfidence_00100 **p = (Dz1TimeConfidence_00100 **)ptr;
	if (p != NULL) { Dz1TimeConfidence_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TimeConfidence_00100_dump(Dz1TimeConfidence_00100 *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TimeConfidence_00100_fdump(FILE *fp, Dz1TimeConfidence_00100 *v, int tab);
// Dz1TimeConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ElevationConfidence_00100
typedef enum Dz1ElevationConfidence_00100
{
	Dz1ElevationConfidence_00100_unavailable = 0,
	Dz1ElevationConfidence_00100_elev_500_00 = 1,
	Dz1ElevationConfidence_00100_elev_200_00 = 2,
	Dz1ElevationConfidence_00100_elev_100_00 = 3,
	Dz1ElevationConfidence_00100_elev_050_00 = 4,
	Dz1ElevationConfidence_00100_elev_020_00 = 5,
	Dz1ElevationConfidence_00100_elev_010_00 = 6,
	Dz1ElevationConfidence_00100_elev_005_00 = 7,
	Dz1ElevationConfidence_00100_elev_002_00 = 8,
	Dz1ElevationConfidence_00100_elev_001_00 = 9,
	Dz1ElevationConfidence_00100_elev_000_50 = 10,
	Dz1ElevationConfidence_00100_elev_000_20 = 11,
	Dz1ElevationConfidence_00100_elev_000_10 = 12,
	Dz1ElevationConfidence_00100_elev_000_05 = 13,
	Dz1ElevationConfidence_00100_elev_000_02 = 14,
	Dz1ElevationConfidence_00100_elev_000_01 = 15,
	Dz1ElevationConfidence_00100_max
} Dz1ElevationConfidence_00100;

DZ1_CPPLINK str_t Dz1ElevationConfidence_00100StrA(Dz1ElevationConfidence_00100 v);
DZ1_CPPLINK Dz1ElevationConfidence_00100 Dz1ElevationConfidence_00100FromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1ElevationConfidence_00100StrW(Dz1ElevationConfidence_00100 v);
DZ1_CPPLINK Dz1ElevationConfidence_00100 Dz1ElevationConfidence_00100FromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1ElevationConfidence_00100Str Dz1ElevationConfidence_00100StrW
#define Dz1ElevationConfidence_00100FromStr Dz1ElevationConfidence_00100FromStrW
#else // UNICODE
#define Dz1ElevationConfidence_00100Str Dz1ElevationConfidence_00100StrA
#define Dz1ElevationConfidence_00100FromStr Dz1ElevationConfidence_00100FromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1ElevationConfidence_00100Str Dz1ElevationConfidence_00100StrA
#define Dz1ElevationConfidence_00100FromStr Dz1ElevationConfidence_00100FromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1ElevationConfidence_00100 *Dz1ElevationConfidence_00100_new(Dz1ElevationConfidence_00100 *src, Dz1Error *err);
static __inline__ Dz1ElevationConfidence_00100 *Dz1ElevationConfidence_00100_gen(Dz1Error *err) { Dz1ElevationConfidence_00100 v = Dz1ElevationConfidence_00100_max; return Dz1ElevationConfidence_00100_new(&v, err); }
#define Dz1ElevationConfidence_00100_clone             Dz1ElevationConfidence_00100_new
static __inline__ void Dz1ElevationConfidence_00100_del(Dz1ElevationConfidence_00100 *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1ElevationConfidence_00100_delAndSetNull(void *ptr)
{
	Dz1ElevationConfidence_00100 **p = (Dz1ElevationConfidence_00100 **)ptr;
	if (p != NULL) { Dz1ElevationConfidence_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ElevationConfidence_00100_dump(Dz1ElevationConfidence_00100 *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ElevationConfidence_00100_fdump(FILE *fp, Dz1ElevationConfidence_00100 *v, int tab);
// Dz1ElevationConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1PositionConfidence_00100
typedef enum Dz1PositionConfidence_00100
{
	Dz1PositionConfidence_00100_unavailable = 0,
	Dz1PositionConfidence_00100_a500m = 1,
	Dz1PositionConfidence_00100_a200m = 2,
	Dz1PositionConfidence_00100_a100m = 3,
	Dz1PositionConfidence_00100_a50m = 4,
	Dz1PositionConfidence_00100_a20m = 5,
	Dz1PositionConfidence_00100_a10m = 6,
	Dz1PositionConfidence_00100_a5m = 7,
	Dz1PositionConfidence_00100_a2m = 8,
	Dz1PositionConfidence_00100_a1m = 9,
	Dz1PositionConfidence_00100_a50cm = 10,
	Dz1PositionConfidence_00100_a20cm = 11,
	Dz1PositionConfidence_00100_a10cm = 12,
	Dz1PositionConfidence_00100_a5cm = 13,
	Dz1PositionConfidence_00100_a2cm = 14,
	Dz1PositionConfidence_00100_a1cm = 15,
	Dz1PositionConfidence_00100_max
} Dz1PositionConfidence_00100;

DZ1_CPPLINK str_t Dz1PositionConfidence_00100StrA(Dz1PositionConfidence_00100 v);
DZ1_CPPLINK Dz1PositionConfidence_00100 Dz1PositionConfidence_00100FromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1PositionConfidence_00100StrW(Dz1PositionConfidence_00100 v);
DZ1_CPPLINK Dz1PositionConfidence_00100 Dz1PositionConfidence_00100FromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1PositionConfidence_00100Str Dz1PositionConfidence_00100StrW
#define Dz1PositionConfidence_00100FromStr Dz1PositionConfidence_00100FromStrW
#else // UNICODE
#define Dz1PositionConfidence_00100Str Dz1PositionConfidence_00100StrA
#define Dz1PositionConfidence_00100FromStr Dz1PositionConfidence_00100FromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1PositionConfidence_00100Str Dz1PositionConfidence_00100StrA
#define Dz1PositionConfidence_00100FromStr Dz1PositionConfidence_00100FromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1PositionConfidence_00100 *Dz1PositionConfidence_00100_new(Dz1PositionConfidence_00100 *src, Dz1Error *err);
static __inline__ Dz1PositionConfidence_00100 *Dz1PositionConfidence_00100_gen(Dz1Error *err) { Dz1PositionConfidence_00100 v = Dz1PositionConfidence_00100_max; return Dz1PositionConfidence_00100_new(&v, err); }
#define Dz1PositionConfidence_00100_clone             Dz1PositionConfidence_00100_new
static __inline__ void Dz1PositionConfidence_00100_del(Dz1PositionConfidence_00100 *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1PositionConfidence_00100_delAndSetNull(void *ptr)
{
	Dz1PositionConfidence_00100 **p = (Dz1PositionConfidence_00100 **)ptr;
	if (p != NULL) { Dz1PositionConfidence_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionConfidence_00100_dump(Dz1PositionConfidence_00100 *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionConfidence_00100_fdump(FILE *fp, Dz1PositionConfidence_00100 *v, int tab);
// Dz1PositionConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1PositionConfidenceSet_00100
enum Dz1PositionConfidence_00100;
enum Dz1ElevationConfidence_00100;

typedef struct Dz1PositionConfidenceSet_00100
{
	enum Dz1PositionConfidence_00100		pos;
	enum Dz1ElevationConfidence_00100		elevation;
} Dz1PositionConfidenceSet_00100;

DZ1_CPPLINK DZ1_DLLPORT Dz1PositionConfidenceSet_00100 *Dz1PositionConfidenceSet_00100_new(enum Dz1PositionConfidence_00100 pos, 
																						   enum Dz1ElevationConfidence_00100 elevation, Dz1Error *err);
static __inline__ Dz1PositionConfidenceSet_00100 *Dz1PositionConfidenceSet_00100_gen(Dz1Error *err) { return Dz1PositionConfidenceSet_00100_new(Dz1PositionConfidence_00100_max, Dz1ElevationConfidence_00100_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1PositionConfidenceSet_00100_copy(Dz1PositionConfidenceSet_00100 *dst, Dz1PositionConfidenceSet_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1PositionConfidenceSet_00100 *Dz1PositionConfidenceSet_00100_clone(Dz1PositionConfidenceSet_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionConfidenceSet_00100_purge(Dz1PositionConfidenceSet_00100 *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionConfidenceSet_00100_del(Dz1PositionConfidenceSet_00100 *p);
static __inline__ void Dz1PositionConfidenceSet_00100_delAndSetNull(void *ptr)
{
	Dz1PositionConfidenceSet_00100 **p = (Dz1PositionConfidenceSet_00100 **)ptr;
	if (p) { Dz1PositionConfidenceSet_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionConfidenceSet_00100_dump(Dz1PositionConfidenceSet_00100 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1PositionConfidenceSet_00100_fdump(FILE *fp, Dz1PositionConfidenceSet_00100 *p, int tab);
// Dz1PositionConfidenceSet_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1HeadingConfidence_00100
typedef enum Dz1HeadingConfidence_00100
{
	Dz1HeadingConfidence_00100_unavailable = 0,
	Dz1HeadingConfidence_00100_prec10deg = 1,
	Dz1HeadingConfidence_00100_prec05deg = 2,
	Dz1HeadingConfidence_00100_prec01deg = 3,
	Dz1HeadingConfidence_00100_prec0_1deg = 4,
	Dz1HeadingConfidence_00100_prec0_05deg = 5,
	Dz1HeadingConfidence_00100_prec0_01deg = 6,
	Dz1HeadingConfidence_00100_prec0_0125deg = 7,
	Dz1HeadingConfidence_00100_max
} Dz1HeadingConfidence_00100;

DZ1_CPPLINK str_t Dz1HeadingConfidence_00100StrA(Dz1HeadingConfidence_00100 v);
DZ1_CPPLINK Dz1HeadingConfidence_00100 Dz1HeadingConfidence_00100FromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1HeadingConfidence_00100StrW(Dz1HeadingConfidence_00100 v);
DZ1_CPPLINK Dz1HeadingConfidence_00100 Dz1HeadingConfidence_00100FromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1HeadingConfidence_00100Str Dz1HeadingConfidence_00100StrW
#define Dz1HeadingConfidence_00100FromStr Dz1HeadingConfidence_00100FromStrW
#else // UNICODE
#define Dz1HeadingConfidence_00100Str Dz1HeadingConfidence_00100StrA
#define Dz1HeadingConfidence_00100FromStr Dz1HeadingConfidence_00100FromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1HeadingConfidence_00100Str Dz1HeadingConfidence_00100StrA
#define Dz1HeadingConfidence_00100FromStr Dz1HeadingConfidence_00100FromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1HeadingConfidence_00100 *Dz1HeadingConfidence_00100_new(Dz1HeadingConfidence_00100 *src, Dz1Error *err);
static __inline__ Dz1HeadingConfidence_00100 *Dz1HeadingConfidence_00100_gen(Dz1Error *err) { Dz1HeadingConfidence_00100 v = Dz1HeadingConfidence_00100_max; return Dz1HeadingConfidence_00100_new(&v, err); }
#define Dz1HeadingConfidence_00100_clone             Dz1HeadingConfidence_00100_new
static __inline__ void Dz1HeadingConfidence_00100_del(Dz1HeadingConfidence_00100 *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1HeadingConfidence_00100_delAndSetNull(void *ptr)
{
	Dz1HeadingConfidence_00100 **p = (Dz1HeadingConfidence_00100 **)ptr;
	if (p != NULL) { Dz1HeadingConfidence_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1HeadingConfidence_00100_dump(Dz1HeadingConfidence_00100 *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1HeadingConfidence_00100_fdump(FILE *fp, Dz1HeadingConfidence_00100 *v, int tab);
// Dz1HeadingConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SpeedConfidence_00100
typedef enum Dz1SpeedConfidence_00100
{
	Dz1SpeedConfidence_00100_unavailable = 0,
	Dz1SpeedConfidence_00100_prec100ms = 1,
	Dz1SpeedConfidence_00100_prec10ms = 2,
	Dz1SpeedConfidence_00100_prec5ms = 3,
	Dz1SpeedConfidence_00100_prec1ms = 4,
	Dz1SpeedConfidence_00100_prec0_1ms = 5,
	Dz1SpeedConfidence_00100_prec0_05ms = 6,
	Dz1SpeedConfidence_00100_prec0_01ms = 7,
	Dz1SpeedConfidence_00100_max
} Dz1SpeedConfidence_00100;

DZ1_CPPLINK str_t Dz1SpeedConfidence_00100StrA(Dz1SpeedConfidence_00100 v);
DZ1_CPPLINK Dz1SpeedConfidence_00100 Dz1SpeedConfidence_00100FromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1SpeedConfidence_00100StrW(Dz1SpeedConfidence_00100 v);
DZ1_CPPLINK Dz1SpeedConfidence_00100 Dz1SpeedConfidence_00100FromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1SpeedConfidence_00100Str Dz1SpeedConfidence_00100StrW
#define Dz1SpeedConfidence_00100FromStr Dz1SpeedConfidence_00100FromStrW
#else // UNICODE
#define Dz1SpeedConfidence_00100Str Dz1SpeedConfidence_00100StrA
#define Dz1SpeedConfidence_00100FromStr Dz1SpeedConfidence_00100FromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1SpeedConfidence_00100Str Dz1SpeedConfidence_00100StrA
#define Dz1SpeedConfidence_00100FromStr Dz1SpeedConfidence_00100FromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1SpeedConfidence_00100 *Dz1SpeedConfidence_00100_new(Dz1SpeedConfidence_00100 *src, Dz1Error *err);
static __inline__ Dz1SpeedConfidence_00100 *Dz1SpeedConfidence_00100_gen(Dz1Error *err) { Dz1SpeedConfidence_00100 v = Dz1SpeedConfidence_00100_max; return Dz1SpeedConfidence_00100_new(&v, err); }
#define Dz1SpeedConfidence_00100_clone             Dz1SpeedConfidence_00100_new
static __inline__ void Dz1SpeedConfidence_00100_del(Dz1SpeedConfidence_00100 *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1SpeedConfidence_00100_delAndSetNull(void *ptr)
{
	Dz1SpeedConfidence_00100 **p = (Dz1SpeedConfidence_00100 **)ptr;
	if (p != NULL) { Dz1SpeedConfidence_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SpeedConfidence_00100_dump(Dz1SpeedConfidence_00100 *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SpeedConfidence_00100_fdump(FILE *fp, Dz1SpeedConfidence_00100 *v, int tab);
// Dz1SpeedConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ThrottleConfidence_00100
typedef enum Dz1ThrottleConfidence_00100
{
	Dz1ThrottleConfidence_00100_unavailable = 0,
	Dz1ThrottleConfidence_00100_prec10percent = 1,
	Dz1ThrottleConfidence_00100_prec1percent = 2,
	Dz1ThrottleConfidence_00100_prec0_5percent = 3,
	Dz1ThrottleConfidence_00100_max
} Dz1ThrottleConfidence_00100;

DZ1_CPPLINK str_t Dz1ThrottleConfidence_00100StrA(Dz1ThrottleConfidence_00100 v);
DZ1_CPPLINK Dz1ThrottleConfidence_00100 Dz1ThrottleConfidence_00100FromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1ThrottleConfidence_00100StrW(Dz1ThrottleConfidence_00100 v);
DZ1_CPPLINK Dz1ThrottleConfidence_00100 Dz1ThrottleConfidence_00100FromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1ThrottleConfidence_00100Str Dz1ThrottleConfidence_00100StrW
#define Dz1ThrottleConfidence_00100FromStr Dz1ThrottleConfidence_00100FromStrW
#else // UNICODE
#define Dz1ThrottleConfidence_00100Str Dz1ThrottleConfidence_00100StrA
#define Dz1ThrottleConfidence_00100FromStr Dz1ThrottleConfidence_00100FromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1ThrottleConfidence_00100Str Dz1ThrottleConfidence_00100StrA
#define Dz1ThrottleConfidence_00100FromStr Dz1ThrottleConfidence_00100FromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1ThrottleConfidence_00100 *Dz1ThrottleConfidence_00100_new(Dz1ThrottleConfidence_00100 *src, Dz1Error *err);
static __inline__ Dz1ThrottleConfidence_00100 *Dz1ThrottleConfidence_00100_gen(Dz1Error *err) { Dz1ThrottleConfidence_00100 v = Dz1ThrottleConfidence_00100_max; return Dz1ThrottleConfidence_00100_new(&v, err); }
#define Dz1ThrottleConfidence_00100_clone             Dz1ThrottleConfidence_00100_new
static __inline__ void Dz1ThrottleConfidence_00100_del(Dz1ThrottleConfidence_00100 *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1ThrottleConfidence_00100_delAndSetNull(void *ptr)
{
	Dz1ThrottleConfidence_00100 **p = (Dz1ThrottleConfidence_00100 **)ptr;
	if (p != NULL) { Dz1ThrottleConfidence_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ThrottleConfidence_00100_dump(Dz1ThrottleConfidence_00100 *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ThrottleConfidence_00100_fdump(FILE *fp, Dz1ThrottleConfidence_00100 *v, int tab);
// Dz1ThrottleConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SpeedandHeadingandThrottleConfidence_00100
enum Dz1HeadingConfidence_00100;
enum Dz1SpeedConfidence_00100;
enum Dz1ThrottleConfidence_00100;

typedef struct Dz1SpeedandHeadingandThrottleConfidence_00100
{
	enum Dz1HeadingConfidence_00100		heading;
	enum Dz1SpeedConfidence_00100		speed;
	enum Dz1ThrottleConfidence_00100	throttle;
} Dz1SpeedandHeadingandThrottleConfidence_00100;

DZ1_CPPLINK DZ1_DLLPORT Dz1SpeedandHeadingandThrottleConfidence_00100 *Dz1SpeedandHeadingandThrottleConfidence_00100_new(enum Dz1HeadingConfidence_00100 heading, 
																														 enum Dz1SpeedConfidence_00100 speed, 
																														 enum Dz1ThrottleConfidence_00100 throttle, Dz1Error *err);
static __inline__ Dz1SpeedandHeadingandThrottleConfidence_00100 *Dz1SpeedandHeadingandThrottleConfidence_00100_gen(Dz1Error *err) { return Dz1SpeedandHeadingandThrottleConfidence_00100_new(Dz1HeadingConfidence_00100_max, Dz1SpeedConfidence_00100_max, Dz1ThrottleConfidence_00100_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1SpeedandHeadingandThrottleConfidence_00100_copy(Dz1SpeedandHeadingandThrottleConfidence_00100 *dst, Dz1SpeedandHeadingandThrottleConfidence_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1SpeedandHeadingandThrottleConfidence_00100 *Dz1SpeedandHeadingandThrottleConfidence_00100_clone(Dz1SpeedandHeadingandThrottleConfidence_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SpeedandHeadingandThrottleConfidence_00100_purge(Dz1SpeedandHeadingandThrottleConfidence_00100 *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SpeedandHeadingandThrottleConfidence_00100_del(Dz1SpeedandHeadingandThrottleConfidence_00100 *p);
static __inline__ void Dz1SpeedandHeadingandThrottleConfidence_00100_delAndSetNull(void *ptr)
{
	Dz1SpeedandHeadingandThrottleConfidence_00100 **p = (Dz1SpeedandHeadingandThrottleConfidence_00100 **)ptr;
	if (p) { Dz1SpeedandHeadingandThrottleConfidence_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SpeedandHeadingandThrottleConfidence_00100_dump(Dz1SpeedandHeadingandThrottleConfidence_00100 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SpeedandHeadingandThrottleConfidence_00100_fdump(FILE *fp, Dz1SpeedandHeadingandThrottleConfidence_00100 *p, int tab);
// Dz1SpeedandHeadingandThrottleConfidence_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1FullPositionVector_00100
typedef struct Dz1FullPositionVector_00100
{
	Dz1DDateTime_00100									*utcTime;
	Dz1Longitude_00100									 lon;
	Dz1Latitude_00100									 lat;
	Dz1Elevation_00100									*elevation;
	Dz1Heading_00100									*heading;
	Dz1TransmissionAndSpeed_00100						*speed;
	Dz1PositionalAccuracy_00100							*posAccuracy;
	Dz1TimeConfidence_00100								*timeConfidence;
	Dz1PositionConfidenceSet_00100						*posConfidence;
	Dz1SpeedandHeadingandThrottleConfidence_00100		*speedConfidence;
} Dz1FullPositionVector_00100;

DZ1_CPPLINK DZ1_DLLPORT Dz1FullPositionVector_00100 *Dz1FullPositionVector_00100_new(Dz1Longitude_00100 lon, 
																					 Dz1Latitude_00100 lat, Dz1Error *err);
static __inline__ Dz1FullPositionVector_00100 *Dz1FullPositionVector_00100_gen(Dz1Error *err) { return Dz1FullPositionVector_00100_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1FullPositionVector_00100_copy(Dz1FullPositionVector_00100 *dst, Dz1FullPositionVector_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FullPositionVector_00100 *Dz1FullPositionVector_00100_clone(Dz1FullPositionVector_00100 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1FullPositionVector_00100_purge(Dz1FullPositionVector_00100 *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1FullPositionVector_00100_del(Dz1FullPositionVector_00100 *p);
static __inline__ void Dz1FullPositionVector_00100_delAndSetNull(void *ptr)
{
	Dz1FullPositionVector_00100 **p = (Dz1FullPositionVector_00100 **)ptr;
	if (p) { Dz1FullPositionVector_00100_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1FullPositionVector_00100_dump(Dz1FullPositionVector_00100 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1FullPositionVector_00100_fdump(FILE *fp, Dz1FullPositionVector_00100 *p, int tab);
// Dz1FullPositionVector_00100
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionInfo_incident_Detected_Type
typedef enum Dz1IncidentDetectionInfo_incident_Detected_Type
{
	Dz1IncidentDetectionInfo_incident_Detected_Type_stalledVehicle = 1,
	Dz1IncidentDetectionInfo_incident_Detected_Type_reverseDriving = 2,
	Dz1IncidentDetectionInfo_incident_Detected_Type_pedestrian = 3,
	Dz1IncidentDetectionInfo_incident_Detected_Type_roadwayDebris = 4,
	Dz1IncidentDetectionInfo_incident_Detected_Type_rireSmoke = 5,
	Dz1IncidentDetectionInfo_incident_Detected_Type_roadShouldersVehicle = 6,
	Dz1IncidentDetectionInfo_incident_Detected_Type_roadkill = 7,
	Dz1IncidentDetectionInfo_incident_Detected_Type_slowVehicle = 8,
	Dz1IncidentDetectionInfo_incident_Detected_Type_delayCongested = 9,
	Dz1IncidentDetectionInfo_incident_Detected_Type_max
} Dz1IncidentDetectionInfo_incident_Detected_Type;

DZ1_CPPLINK str_t Dz1IncidentDetectionInfo_incident_Detected_TypeStrA(Dz1IncidentDetectionInfo_incident_Detected_Type v);
DZ1_CPPLINK Dz1IncidentDetectionInfo_incident_Detected_Type Dz1IncidentDetectionInfo_incident_Detected_TypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1IncidentDetectionInfo_incident_Detected_TypeStrW(Dz1IncidentDetectionInfo_incident_Detected_Type v);
DZ1_CPPLINK Dz1IncidentDetectionInfo_incident_Detected_Type Dz1IncidentDetectionInfo_incident_Detected_TypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1IncidentDetectionInfo_incident_Detected_TypeStr Dz1IncidentDetectionInfo_incident_Detected_TypeStrW
#define Dz1IncidentDetectionInfo_incident_Detected_TypeFromStr Dz1IncidentDetectionInfo_incident_Detected_TypeFromStrW
#else // UNICODE
#define Dz1IncidentDetectionInfo_incident_Detected_TypeStr Dz1IncidentDetectionInfo_incident_Detected_TypeStrA
#define Dz1IncidentDetectionInfo_incident_Detected_TypeFromStr Dz1IncidentDetectionInfo_incident_Detected_TypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1IncidentDetectionInfo_incident_Detected_TypeStr Dz1IncidentDetectionInfo_incident_Detected_TypeStrA
#define Dz1IncidentDetectionInfo_incident_Detected_TypeFromStr Dz1IncidentDetectionInfo_incident_Detected_TypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionInfo_incident_Detected_Type *Dz1IncidentDetectionInfo_incident_Detected_Type_new(Dz1IncidentDetectionInfo_incident_Detected_Type *src, Dz1Error *err);
static __inline__ Dz1IncidentDetectionInfo_incident_Detected_Type *Dz1IncidentDetectionInfo_incident_Detected_Type_gen(Dz1Error *err) { Dz1IncidentDetectionInfo_incident_Detected_Type v = Dz1IncidentDetectionInfo_incident_Detected_Type_max; return Dz1IncidentDetectionInfo_incident_Detected_Type_new(&v, err); }
#define Dz1IncidentDetectionInfo_incident_Detected_Type_clone             Dz1IncidentDetectionInfo_incident_Detected_Type_new
static __inline__ void Dz1IncidentDetectionInfo_incident_Detected_Type_del(Dz1IncidentDetectionInfo_incident_Detected_Type *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1IncidentDetectionInfo_incident_Detected_Type_delAndSetNull(void *ptr)
{
	Dz1IncidentDetectionInfo_incident_Detected_Type **p = (Dz1IncidentDetectionInfo_incident_Detected_Type **)ptr;
	if (p != NULL) { Dz1IncidentDetectionInfo_incident_Detected_Type_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfo_incident_Detected_Type_dump(Dz1IncidentDetectionInfo_incident_Detected_Type *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfo_incident_Detected_Type_fdump(FILE *fp, Dz1IncidentDetectionInfo_incident_Detected_Type *v, int tab);
// Dz1IncidentDetectionInfo_incident_Detected_Type
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NMEACoord_compass
typedef enum Dz1NMEACoord_compass
{
	Dz1NMEACoord_compass_north,
	Dz1NMEACoord_compass_south,
	Dz1NMEACoord_compass_max
} Dz1NMEACoord_compass;

DZ1_CPPLINK str_t Dz1NMEACoord_compassStrA(Dz1NMEACoord_compass v);
DZ1_CPPLINK Dz1NMEACoord_compass Dz1NMEACoord_compassFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1NMEACoord_compassStrW(Dz1NMEACoord_compass v);
DZ1_CPPLINK Dz1NMEACoord_compass Dz1NMEACoord_compassFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1NMEACoord_compassStr Dz1NMEACoord_compassStrW
#define Dz1NMEACoord_compassFromStr Dz1NMEACoord_compassFromStrW
#else // UNICODE
#define Dz1NMEACoord_compassStr Dz1NMEACoord_compassStrA
#define Dz1NMEACoord_compassFromStr Dz1NMEACoord_compassFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1NMEACoord_compassStr Dz1NMEACoord_compassStrA
#define Dz1NMEACoord_compassFromStr Dz1NMEACoord_compassFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord_compass *Dz1NMEACoord_compass_new(Dz1NMEACoord_compass *src, Dz1Error *err);
static __inline__ Dz1NMEACoord_compass *Dz1NMEACoord_compass_gen(Dz1Error *err) { Dz1NMEACoord_compass v = Dz1NMEACoord_compass_max; return Dz1NMEACoord_compass_new(&v, err); }
#define Dz1NMEACoord_compass_clone             Dz1NMEACoord_compass_new
static __inline__ void Dz1NMEACoord_compass_del(Dz1NMEACoord_compass *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1NMEACoord_compass_delAndSetNull(void *ptr)
{
	Dz1NMEACoord_compass **p = (Dz1NMEACoord_compass **)ptr;
	if (p != NULL) { Dz1NMEACoord_compass_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_compass_dump(Dz1NMEACoord_compass *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_compass_fdump(FILE *fp, Dz1NMEACoord_compass *v, int tab);
// Dz1NMEACoord_compass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NMEACoord_latitude
typedef struct Dz1NMEACoord_latitude
{
	s64_t					integerValue;
	s64_t					fractionValue;
	u8_t					fracSize;
	Dz1NMEACoord_compass	compass;
} Dz1NMEACoord_latitude;

DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord_latitude *Dz1NMEACoord_latitude_new(s64_t integerValue, 
																		 s64_t fractionValue, 
																		 u8_t fracSize, 
																		 Dz1NMEACoord_compass compass, Dz1Error *err);
static __inline__ Dz1NMEACoord_latitude *Dz1NMEACoord_latitude_gen(Dz1Error *err) { return Dz1NMEACoord_latitude_new(0, 0, 0, Dz1NMEACoord_compass_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1NMEACoord_latitude_copy(Dz1NMEACoord_latitude *dst, Dz1NMEACoord_latitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord_latitude *Dz1NMEACoord_latitude_clone(Dz1NMEACoord_latitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_latitude_purge(Dz1NMEACoord_latitude *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_latitude_del(Dz1NMEACoord_latitude *p);
static __inline__ void Dz1NMEACoord_latitude_delAndSetNull(void *ptr)
{
	Dz1NMEACoord_latitude **p = (Dz1NMEACoord_latitude **)ptr;
	if (p) { Dz1NMEACoord_latitude_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_latitude_dump(Dz1NMEACoord_latitude *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_latitude_fdump(FILE *fp, Dz1NMEACoord_latitude *p, int tab);
// Dz1NMEACoord_latitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NMEACoord_longitude
typedef struct Dz1NMEACoord_longitude
{
	s64_t					integerValue;
	s64_t					fractionValue;
	u8_t					fracSize;
	Dz1NMEACoord_compass	compass;
} Dz1NMEACoord_longitude;

DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord_longitude *Dz1NMEACoord_longitude_new(s64_t integerValue, 
																		   s64_t fractionValue, 
																		   u8_t fracSize, 
																		   Dz1NMEACoord_compass compass, Dz1Error *err);
static __inline__ Dz1NMEACoord_longitude *Dz1NMEACoord_longitude_gen(Dz1Error *err) { return Dz1NMEACoord_longitude_new(0, 0, 0, Dz1NMEACoord_compass_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1NMEACoord_longitude_copy(Dz1NMEACoord_longitude *dst, Dz1NMEACoord_longitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord_longitude *Dz1NMEACoord_longitude_clone(Dz1NMEACoord_longitude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_longitude_purge(Dz1NMEACoord_longitude *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_longitude_del(Dz1NMEACoord_longitude *p);
static __inline__ void Dz1NMEACoord_longitude_delAndSetNull(void *ptr)
{
	Dz1NMEACoord_longitude **p = (Dz1NMEACoord_longitude **)ptr;
	if (p) { Dz1NMEACoord_longitude_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_longitude_dump(Dz1NMEACoord_longitude *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_longitude_fdump(FILE *fp, Dz1NMEACoord_longitude *p, int tab);
// Dz1NMEACoord_longitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NMEACoord
typedef struct Dz1NMEACoord
{
	Dz1NMEACoord_latitude		*latitude;
	Dz1NMEACoord_longitude		*longitude;
	Dz1Asn1OctetStr				*optData;
} Dz1NMEACoord;

DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord *Dz1NMEACoord_new(Dz1NMEACoord_latitude *latitude, 
													   Dz1NMEACoord_longitude *longitude, Dz1Error *err);
static __inline__ Dz1NMEACoord *Dz1NMEACoord_gen(Dz1Error *err) { return Dz1NMEACoord_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1NMEACoord_copy(Dz1NMEACoord *dst, Dz1NMEACoord *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord *Dz1NMEACoord_clone(Dz1NMEACoord *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_purge(Dz1NMEACoord *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_del(Dz1NMEACoord *p);
static __inline__ void Dz1NMEACoord_delAndSetNull(void *ptr)
{
	Dz1NMEACoord **p = (Dz1NMEACoord **)ptr;
	if (p) { Dz1NMEACoord_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_dump(Dz1NMEACoord *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NMEACoord_fdump(FILE *fp, Dz1NMEACoord *p, int tab);
// Dz1NMEACoord
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionInfo
typedef struct Dz1IncidentDetectionInfo
{
	Dz1Asn1VisibleStr									*incident_Detected_Time;
	Dz1IncidentDetectionInfo_incident_Detected_Type		 incident_Detected_Type;
	Dz1NMEACoord										*incident_Detected_Site;
	u8_t												*detected_Object_Size;
	u16_t												 detected_Object_Distance;
	u16_t												 detected_Object_Angle;
	u16_t												 detected_Object_Speed;
} Dz1IncidentDetectionInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionInfo *Dz1IncidentDetectionInfo_new(Dz1Asn1VisibleStr *incident_Detected_Time, 
																			   Dz1IncidentDetectionInfo_incident_Detected_Type incident_Detected_Type, 
																			   Dz1NMEACoord *incident_Detected_Site, 
																			   u16_t detected_Object_Distance, 
																			   u16_t detected_Object_Angle, 
																			   u16_t detected_Object_Speed, Dz1Error *err);
static __inline__ Dz1IncidentDetectionInfo *Dz1IncidentDetectionInfo_gen(Dz1Error *err) { return Dz1IncidentDetectionInfo_new(NULL, Dz1IncidentDetectionInfo_incident_Detected_Type_max, NULL, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1IncidentDetectionInfo_copy(Dz1IncidentDetectionInfo *dst, Dz1IncidentDetectionInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionInfo *Dz1IncidentDetectionInfo_clone(Dz1IncidentDetectionInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfo_purge(Dz1IncidentDetectionInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfo_del(Dz1IncidentDetectionInfo *p);
static __inline__ void Dz1IncidentDetectionInfo_delAndSetNull(void *ptr)
{
	Dz1IncidentDetectionInfo **p = (Dz1IncidentDetectionInfo **)ptr;
	if (p) { Dz1IncidentDetectionInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfo_dump(Dz1IncidentDetectionInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfo_fdump(FILE *fp, Dz1IncidentDetectionInfo *p, int tab);
// Dz1IncidentDetectionInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentTerminationInfo_terminate_incidentType
typedef enum Dz1IncidentTerminationInfo_terminate_incidentType
{
	Dz1IncidentTerminationInfo_terminate_incidentType_termination = 1,
	Dz1IncidentTerminationInfo_terminate_incidentType_timeout = 2,
	Dz1IncidentTerminationInfo_terminate_incidentType_max
} Dz1IncidentTerminationInfo_terminate_incidentType;

DZ1_CPPLINK str_t Dz1IncidentTerminationInfo_terminate_incidentTypeStrA(Dz1IncidentTerminationInfo_terminate_incidentType v);
DZ1_CPPLINK Dz1IncidentTerminationInfo_terminate_incidentType Dz1IncidentTerminationInfo_terminate_incidentTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1IncidentTerminationInfo_terminate_incidentTypeStrW(Dz1IncidentTerminationInfo_terminate_incidentType v);
DZ1_CPPLINK Dz1IncidentTerminationInfo_terminate_incidentType Dz1IncidentTerminationInfo_terminate_incidentTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1IncidentTerminationInfo_terminate_incidentTypeStr Dz1IncidentTerminationInfo_terminate_incidentTypeStrW
#define Dz1IncidentTerminationInfo_terminate_incidentTypeFromStr Dz1IncidentTerminationInfo_terminate_incidentTypeFromStrW
#else // UNICODE
#define Dz1IncidentTerminationInfo_terminate_incidentTypeStr Dz1IncidentTerminationInfo_terminate_incidentTypeStrA
#define Dz1IncidentTerminationInfo_terminate_incidentTypeFromStr Dz1IncidentTerminationInfo_terminate_incidentTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1IncidentTerminationInfo_terminate_incidentTypeStr Dz1IncidentTerminationInfo_terminate_incidentTypeStrA
#define Dz1IncidentTerminationInfo_terminate_incidentTypeFromStr Dz1IncidentTerminationInfo_terminate_incidentTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentTerminationInfo_terminate_incidentType *Dz1IncidentTerminationInfo_terminate_incidentType_new(Dz1IncidentTerminationInfo_terminate_incidentType *src, Dz1Error *err);
static __inline__ Dz1IncidentTerminationInfo_terminate_incidentType *Dz1IncidentTerminationInfo_terminate_incidentType_gen(Dz1Error *err) { Dz1IncidentTerminationInfo_terminate_incidentType v = Dz1IncidentTerminationInfo_terminate_incidentType_max; return Dz1IncidentTerminationInfo_terminate_incidentType_new(&v, err); }
#define Dz1IncidentTerminationInfo_terminate_incidentType_clone             Dz1IncidentTerminationInfo_terminate_incidentType_new
static __inline__ void Dz1IncidentTerminationInfo_terminate_incidentType_del(Dz1IncidentTerminationInfo_terminate_incidentType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1IncidentTerminationInfo_terminate_incidentType_delAndSetNull(void *ptr)
{
	Dz1IncidentTerminationInfo_terminate_incidentType **p = (Dz1IncidentTerminationInfo_terminate_incidentType **)ptr;
	if (p != NULL) { Dz1IncidentTerminationInfo_terminate_incidentType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfo_terminate_incidentType_dump(Dz1IncidentTerminationInfo_terminate_incidentType *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfo_terminate_incidentType_fdump(FILE *fp, Dz1IncidentTerminationInfo_terminate_incidentType *v, int tab);
// Dz1IncidentTerminationInfo_terminate_incidentType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentTerminationInfo
typedef struct Dz1IncidentTerminationInfo
{
	Dz1IncidentTerminationInfo_terminate_incidentType		terminate_incidentType;
} Dz1IncidentTerminationInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentTerminationInfo *Dz1IncidentTerminationInfo_new(Dz1IncidentTerminationInfo_terminate_incidentType terminate_incidentType, Dz1Error *err);
static __inline__ Dz1IncidentTerminationInfo *Dz1IncidentTerminationInfo_gen(Dz1Error *err) { return Dz1IncidentTerminationInfo_new(Dz1IncidentTerminationInfo_terminate_incidentType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1IncidentTerminationInfo_copy(Dz1IncidentTerminationInfo *dst, Dz1IncidentTerminationInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentTerminationInfo *Dz1IncidentTerminationInfo_clone(Dz1IncidentTerminationInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfo_purge(Dz1IncidentTerminationInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfo_del(Dz1IncidentTerminationInfo *p);
static __inline__ void Dz1IncidentTerminationInfo_delAndSetNull(void *ptr)
{
	Dz1IncidentTerminationInfo **p = (Dz1IncidentTerminationInfo **)ptr;
	if (p) { Dz1IncidentTerminationInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfo_dump(Dz1IncidentTerminationInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfo_fdump(FILE *fp, Dz1IncidentTerminationInfo *p, int tab);
// Dz1IncidentTerminationInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionVideoFileInfoProvide_fileStatus
typedef enum Dz1IncidentDetectionVideoFileInfoProvide_fileStatus
{
	Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileExists = 0,
	Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileAlreadyExists = 1,
	Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_max
} Dz1IncidentDetectionVideoFileInfoProvide_fileStatus;

DZ1_CPPLINK str_t Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStrA(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus v);
DZ1_CPPLINK Dz1IncidentDetectionVideoFileInfoProvide_fileStatus Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStrW(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus v);
DZ1_CPPLINK Dz1IncidentDetectionVideoFileInfoProvide_fileStatus Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStr Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStrW
#define Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStr Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStrW
#else // UNICODE
#define Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStr Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStrA
#define Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStr Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStr Dz1IncidentDetectionVideoFileInfoProvide_fileStatusStrA
#define Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStr Dz1IncidentDetectionVideoFileInfoProvide_fileStatusFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionVideoFileInfoProvide_fileStatus *Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_new(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus *src, Dz1Error *err);
static __inline__ Dz1IncidentDetectionVideoFileInfoProvide_fileStatus *Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_gen(Dz1Error *err) { Dz1IncidentDetectionVideoFileInfoProvide_fileStatus v = Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_max; return Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_new(&v, err); }
#define Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_clone             Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_new
static __inline__ void Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_del(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_delAndSetNull(void *ptr)
{
	Dz1IncidentDetectionVideoFileInfoProvide_fileStatus **p = (Dz1IncidentDetectionVideoFileInfoProvide_fileStatus **)ptr;
	if (p != NULL) { Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_dump(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_fdump(FILE *fp, Dz1IncidentDetectionVideoFileInfoProvide_fileStatus *v, int tab);
// Dz1IncidentDetectionVideoFileInfoProvide_fileStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionVideoFileInfoProvide
typedef struct Dz1IncidentDetectionVideoFileInfoProvide
{
	Dz1IncidentDetectionVideoFileInfoProvide_fileStatus		 fileStatus;
	Dz1Asn1OctetStr											*fileName;
	s64_t													*fileSize;
} Dz1IncidentDetectionVideoFileInfoProvide;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionVideoFileInfoProvide *Dz1IncidentDetectionVideoFileInfoProvide_new(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus fileStatus, Dz1Error *err);
static __inline__ Dz1IncidentDetectionVideoFileInfoProvide *Dz1IncidentDetectionVideoFileInfoProvide_gen(Dz1Error *err) { return Dz1IncidentDetectionVideoFileInfoProvide_new(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1IncidentDetectionVideoFileInfoProvide_copy(Dz1IncidentDetectionVideoFileInfoProvide *dst, Dz1IncidentDetectionVideoFileInfoProvide *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionVideoFileInfoProvide *Dz1IncidentDetectionVideoFileInfoProvide_clone(Dz1IncidentDetectionVideoFileInfoProvide *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvide_purge(Dz1IncidentDetectionVideoFileInfoProvide *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvide_del(Dz1IncidentDetectionVideoFileInfoProvide *p);
static __inline__ void Dz1IncidentDetectionVideoFileInfoProvide_delAndSetNull(void *ptr)
{
	Dz1IncidentDetectionVideoFileInfoProvide **p = (Dz1IncidentDetectionVideoFileInfoProvide **)ptr;
	if (p) { Dz1IncidentDetectionVideoFileInfoProvide_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvide_dump(Dz1IncidentDetectionVideoFileInfoProvide *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvide_fdump(FILE *fp, Dz1IncidentDetectionVideoFileInfoProvide *p, int tab);
// Dz1IncidentDetectionVideoFileInfoProvide
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ControlStateInfo
typedef struct Dz1ControlStateInfo
{
	u8_t	cpu;
	u8_t	ram;
	u8_t	disk;
} Dz1ControlStateInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1ControlStateInfo *Dz1ControlStateInfo_new(u8_t cpu, 
																	 u8_t ram, 
																	 u8_t disk, Dz1Error *err);
static __inline__ Dz1ControlStateInfo *Dz1ControlStateInfo_gen(Dz1Error *err) { return Dz1ControlStateInfo_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ControlStateInfo_copy(Dz1ControlStateInfo *dst, Dz1ControlStateInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1ControlStateInfo *Dz1ControlStateInfo_clone(Dz1ControlStateInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ControlStateInfo_purge(Dz1ControlStateInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ControlStateInfo_del(Dz1ControlStateInfo *p);
static __inline__ void Dz1ControlStateInfo_delAndSetNull(void *ptr)
{
	Dz1ControlStateInfo **p = (Dz1ControlStateInfo **)ptr;
	if (p) { Dz1ControlStateInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ControlStateInfo_dump(Dz1ControlStateInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ControlStateInfo_fdump(FILE *fp, Dz1ControlStateInfo *p, int tab);
// Dz1ControlStateInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SensorStateInfo_state
typedef enum Dz1SensorStateInfo_state
{
	Dz1SensorStateInfo_state_normal = 0,
	Dz1SensorStateInfo_state_abnormal = 1,
	Dz1SensorStateInfo_state_max
} Dz1SensorStateInfo_state;

DZ1_CPPLINK str_t Dz1SensorStateInfo_stateStrA(Dz1SensorStateInfo_state v);
DZ1_CPPLINK Dz1SensorStateInfo_state Dz1SensorStateInfo_stateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1SensorStateInfo_stateStrW(Dz1SensorStateInfo_state v);
DZ1_CPPLINK Dz1SensorStateInfo_state Dz1SensorStateInfo_stateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1SensorStateInfo_stateStr Dz1SensorStateInfo_stateStrW
#define Dz1SensorStateInfo_stateFromStr Dz1SensorStateInfo_stateFromStrW
#else // UNICODE
#define Dz1SensorStateInfo_stateStr Dz1SensorStateInfo_stateStrA
#define Dz1SensorStateInfo_stateFromStr Dz1SensorStateInfo_stateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1SensorStateInfo_stateStr Dz1SensorStateInfo_stateStrA
#define Dz1SensorStateInfo_stateFromStr Dz1SensorStateInfo_stateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1SensorStateInfo_state *Dz1SensorStateInfo_state_new(Dz1SensorStateInfo_state *src, Dz1Error *err);
static __inline__ Dz1SensorStateInfo_state *Dz1SensorStateInfo_state_gen(Dz1Error *err) { Dz1SensorStateInfo_state v = Dz1SensorStateInfo_state_max; return Dz1SensorStateInfo_state_new(&v, err); }
#define Dz1SensorStateInfo_state_clone             Dz1SensorStateInfo_state_new
static __inline__ void Dz1SensorStateInfo_state_del(Dz1SensorStateInfo_state *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1SensorStateInfo_state_delAndSetNull(void *ptr)
{
	Dz1SensorStateInfo_state **p = (Dz1SensorStateInfo_state **)ptr;
	if (p != NULL) { Dz1SensorStateInfo_state_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfo_state_dump(Dz1SensorStateInfo_state *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfo_state_fdump(FILE *fp, Dz1SensorStateInfo_state *v, int tab);
// Dz1SensorStateInfo_state
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SensorStateInfo
typedef struct Dz1SensorStateInfo
{
	Dz1SensorStateInfo_state	msm;
	Dz1SensorStateInfo_state	txb;
	Dz1SensorStateInfo_state	rxb;
	Dz1SensorStateInfo_state	pwr;
} Dz1SensorStateInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1SensorStateInfo *Dz1SensorStateInfo_new(Dz1SensorStateInfo_state msm, 
																   Dz1SensorStateInfo_state txb, 
																   Dz1SensorStateInfo_state rxb, 
																   Dz1SensorStateInfo_state pwr, Dz1Error *err);
static __inline__ Dz1SensorStateInfo *Dz1SensorStateInfo_gen(Dz1Error *err) { return Dz1SensorStateInfo_new(Dz1SensorStateInfo_state_max, Dz1SensorStateInfo_state_max, Dz1SensorStateInfo_state_max, Dz1SensorStateInfo_state_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1SensorStateInfo_copy(Dz1SensorStateInfo *dst, Dz1SensorStateInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1SensorStateInfo *Dz1SensorStateInfo_clone(Dz1SensorStateInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfo_purge(Dz1SensorStateInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfo_del(Dz1SensorStateInfo *p);
static __inline__ void Dz1SensorStateInfo_delAndSetNull(void *ptr)
{
	Dz1SensorStateInfo **p = (Dz1SensorStateInfo **)ptr;
	if (p) { Dz1SensorStateInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfo_dump(Dz1SensorStateInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfo_fdump(FILE *fp, Dz1SensorStateInfo *p, int tab);
// Dz1SensorStateInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Novelty
typedef enum Dz1Novelty
{
	Dz1Novelty_noveltyNew = 0,
	Dz1Novelty_noveltyUpdate = 1,
	Dz1Novelty_max
} Dz1Novelty;

DZ1_CPPLINK str_t Dz1NoveltyStrA(Dz1Novelty v);
DZ1_CPPLINK Dz1Novelty Dz1NoveltyFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1NoveltyStrW(Dz1Novelty v);
DZ1_CPPLINK Dz1Novelty Dz1NoveltyFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1NoveltyStr Dz1NoveltyStrW
#define Dz1NoveltyFromStr Dz1NoveltyFromStrW
#else // UNICODE
#define Dz1NoveltyStr Dz1NoveltyStrA
#define Dz1NoveltyFromStr Dz1NoveltyFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1NoveltyStr Dz1NoveltyStrA
#define Dz1NoveltyFromStr Dz1NoveltyFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Novelty *Dz1Novelty_new(Dz1Novelty *src, Dz1Error *err);
static __inline__ Dz1Novelty *Dz1Novelty_gen(Dz1Error *err) { Dz1Novelty v = Dz1Novelty_max; return Dz1Novelty_new(&v, err); }
#define Dz1Novelty_clone             Dz1Novelty_new
static __inline__ void Dz1Novelty_del(Dz1Novelty *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Novelty_delAndSetNull(void *ptr)
{
	Dz1Novelty **p = (Dz1Novelty **)ptr;
	if (p != NULL) { Dz1Novelty_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Novelty_dump(Dz1Novelty *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Novelty_fdump(FILE *fp, Dz1Novelty *v, int tab);
// Dz1Novelty
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MovingObject_objectType
typedef enum Dz1MovingObject_objectType
{
	Dz1MovingObject_objectType_pedestrian = 0,
	Dz1MovingObject_objectType_vehicle = 1,
	Dz1MovingObject_objectType_bike = 2,
	Dz1MovingObject_objectType_max
} Dz1MovingObject_objectType;

DZ1_CPPLINK str_t Dz1MovingObject_objectTypeStrA(Dz1MovingObject_objectType v);
DZ1_CPPLINK Dz1MovingObject_objectType Dz1MovingObject_objectTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MovingObject_objectTypeStrW(Dz1MovingObject_objectType v);
DZ1_CPPLINK Dz1MovingObject_objectType Dz1MovingObject_objectTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MovingObject_objectTypeStr Dz1MovingObject_objectTypeStrW
#define Dz1MovingObject_objectTypeFromStr Dz1MovingObject_objectTypeFromStrW
#else // UNICODE
#define Dz1MovingObject_objectTypeStr Dz1MovingObject_objectTypeStrA
#define Dz1MovingObject_objectTypeFromStr Dz1MovingObject_objectTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MovingObject_objectTypeStr Dz1MovingObject_objectTypeStrA
#define Dz1MovingObject_objectTypeFromStr Dz1MovingObject_objectTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MovingObject_objectType *Dz1MovingObject_objectType_new(Dz1MovingObject_objectType *src, Dz1Error *err);
static __inline__ Dz1MovingObject_objectType *Dz1MovingObject_objectType_gen(Dz1Error *err) { Dz1MovingObject_objectType v = Dz1MovingObject_objectType_max; return Dz1MovingObject_objectType_new(&v, err); }
#define Dz1MovingObject_objectType_clone             Dz1MovingObject_objectType_new
static __inline__ void Dz1MovingObject_objectType_del(Dz1MovingObject_objectType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MovingObject_objectType_delAndSetNull(void *ptr)
{
	Dz1MovingObject_objectType **p = (Dz1MovingObject_objectType **)ptr;
	if (p != NULL) { Dz1MovingObject_objectType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObject_objectType_dump(Dz1MovingObject_objectType *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObject_objectType_fdump(FILE *fp, Dz1MovingObject_objectType *v, int tab);
// Dz1MovingObject_objectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MovingObject
typedef struct Dz1MovingObject
{
	Dz1MovingObject_objectType		 objectType;
	Dz1ObjectID_00100				 objectID;
	Dz1Novelty						*novelty;
	u8_t							 reliability;
	Dz1FullPositionVector_00100		*fullPositionVector;
} Dz1MovingObject;

DZ1_CPPLINK DZ1_DLLPORT Dz1MovingObject *Dz1MovingObject_new(Dz1MovingObject_objectType objectType, 
															 Dz1ObjectID_00100 objectID, 
															 u8_t reliability, 
															 Dz1FullPositionVector_00100 *fullPositionVector, Dz1Error *err);
static __inline__ Dz1MovingObject *Dz1MovingObject_gen(Dz1Error *err) { return Dz1MovingObject_new(Dz1MovingObject_objectType_max, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MovingObject_copy(Dz1MovingObject *dst, Dz1MovingObject *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MovingObject *Dz1MovingObject_clone(Dz1MovingObject *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObject_purge(Dz1MovingObject *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObject_del(Dz1MovingObject *p);
static __inline__ void Dz1MovingObject_delAndSetNull(void *ptr)
{
	Dz1MovingObject **p = (Dz1MovingObject **)ptr;
	if (p) { Dz1MovingObject_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObject_dump(Dz1MovingObject *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObject_fdump(FILE *fp, Dz1MovingObject *p, int tab);
// Dz1MovingObject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionInfoResponse
typedef struct Dz1IncidentDetectionInfoResponse
{
	void *storage;
	unsigned int (*count)(struct Dz1IncidentDetectionInfoResponse *p);
	Dz1Error (*travel)(struct Dz1IncidentDetectionInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentDetectionInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1IncidentDetectionInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentDetectionInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1IncidentDetectionInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentDetectionInfo *entry), void *ptr);
	Dz1IncidentDetectionInfo **(*get_array)(struct Dz1IncidentDetectionInfoResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1IncidentDetectionInfoResponse *p, Dz1IncidentDetectionInfo *data);
} Dz1IncidentDetectionInfoResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionInfoResponse *Dz1IncidentDetectionInfoResponse_new(Dz1Error *err);
static __inline__ Dz1IncidentDetectionInfoResponse *Dz1IncidentDetectionInfoResponse_gen(Dz1Error *err) { return Dz1IncidentDetectionInfoResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionInfoResponse *Dz1IncidentDetectionInfoResponse_clone(Dz1IncidentDetectionInfoResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfoResponse_purge(Dz1IncidentDetectionInfoResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfoResponse_del(Dz1IncidentDetectionInfoResponse *p);
static __inline__ void Dz1IncidentDetectionInfoResponse_delAndSetNull(void *ptr)
{
	Dz1IncidentDetectionInfoResponse **p = (Dz1IncidentDetectionInfoResponse **)ptr;
	if (p != NULL) { Dz1IncidentDetectionInfoResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfoResponse_dump(Dz1IncidentDetectionInfoResponse *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionInfoResponse_fdump(FILE *fp, Dz1IncidentDetectionInfoResponse *p, int tab);

// Dz1IncidentDetectionInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentTerminationInfoResponse
typedef struct Dz1IncidentTerminationInfoResponse
{
	void *storage;
	unsigned int (*count)(struct Dz1IncidentTerminationInfoResponse *p);
	Dz1Error (*travel)(struct Dz1IncidentTerminationInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentTerminationInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1IncidentTerminationInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentTerminationInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1IncidentTerminationInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentTerminationInfo *entry), void *ptr);
	Dz1IncidentTerminationInfo **(*get_array)(struct Dz1IncidentTerminationInfoResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1IncidentTerminationInfoResponse *p, Dz1IncidentTerminationInfo *data);
} Dz1IncidentTerminationInfoResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentTerminationInfoResponse *Dz1IncidentTerminationInfoResponse_new(Dz1Error *err);
static __inline__ Dz1IncidentTerminationInfoResponse *Dz1IncidentTerminationInfoResponse_gen(Dz1Error *err) { return Dz1IncidentTerminationInfoResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentTerminationInfoResponse *Dz1IncidentTerminationInfoResponse_clone(Dz1IncidentTerminationInfoResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfoResponse_purge(Dz1IncidentTerminationInfoResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfoResponse_del(Dz1IncidentTerminationInfoResponse *p);
static __inline__ void Dz1IncidentTerminationInfoResponse_delAndSetNull(void *ptr)
{
	Dz1IncidentTerminationInfoResponse **p = (Dz1IncidentTerminationInfoResponse **)ptr;
	if (p != NULL) { Dz1IncidentTerminationInfoResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfoResponse_dump(Dz1IncidentTerminationInfoResponse *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentTerminationInfoResponse_fdump(FILE *fp, Dz1IncidentTerminationInfoResponse *p, int tab);

// Dz1IncidentTerminationInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentDetectionVideoFileInfoProvideResponse
typedef struct Dz1IncidentDetectionVideoFileInfoProvideResponse
{
	void *storage;
	unsigned int (*count)(struct Dz1IncidentDetectionVideoFileInfoProvideResponse *p);
	Dz1Error (*travel)(struct Dz1IncidentDetectionVideoFileInfoProvideResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentDetectionVideoFileInfoProvide *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1IncidentDetectionVideoFileInfoProvideResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentDetectionVideoFileInfoProvide *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1IncidentDetectionVideoFileInfoProvideResponse *p, Dz1Error (*func)(void *ptr, Dz1IncidentDetectionVideoFileInfoProvide *entry), void *ptr);
	Dz1IncidentDetectionVideoFileInfoProvide **(*get_array)(struct Dz1IncidentDetectionVideoFileInfoProvideResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1IncidentDetectionVideoFileInfoProvideResponse *p, Dz1IncidentDetectionVideoFileInfoProvide *data);
} Dz1IncidentDetectionVideoFileInfoProvideResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionVideoFileInfoProvideResponse *Dz1IncidentDetectionVideoFileInfoProvideResponse_new(Dz1Error *err);
static __inline__ Dz1IncidentDetectionVideoFileInfoProvideResponse *Dz1IncidentDetectionVideoFileInfoProvideResponse_gen(Dz1Error *err) { return Dz1IncidentDetectionVideoFileInfoProvideResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionVideoFileInfoProvideResponse *Dz1IncidentDetectionVideoFileInfoProvideResponse_clone(Dz1IncidentDetectionVideoFileInfoProvideResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvideResponse_purge(Dz1IncidentDetectionVideoFileInfoProvideResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvideResponse_del(Dz1IncidentDetectionVideoFileInfoProvideResponse *p);
static __inline__ void Dz1IncidentDetectionVideoFileInfoProvideResponse_delAndSetNull(void *ptr)
{
	Dz1IncidentDetectionVideoFileInfoProvideResponse **p = (Dz1IncidentDetectionVideoFileInfoProvideResponse **)ptr;
	if (p != NULL) { Dz1IncidentDetectionVideoFileInfoProvideResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvideResponse_dump(Dz1IncidentDetectionVideoFileInfoProvideResponse *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1IncidentDetectionVideoFileInfoProvideResponse_fdump(FILE *fp, Dz1IncidentDetectionVideoFileInfoProvideResponse *p, int tab);

// Dz1IncidentDetectionVideoFileInfoProvideResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ControlStateInfoResponse
typedef struct Dz1ControlStateInfoResponse
{
	void *storage;
	unsigned int (*count)(struct Dz1ControlStateInfoResponse *p);
	Dz1Error (*travel)(struct Dz1ControlStateInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1ControlStateInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1ControlStateInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1ControlStateInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1ControlStateInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1ControlStateInfo *entry), void *ptr);
	Dz1ControlStateInfo **(*get_array)(struct Dz1ControlStateInfoResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1ControlStateInfoResponse *p, Dz1ControlStateInfo *data);
} Dz1ControlStateInfoResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1ControlStateInfoResponse *Dz1ControlStateInfoResponse_new(Dz1Error *err);
static __inline__ Dz1ControlStateInfoResponse *Dz1ControlStateInfoResponse_gen(Dz1Error *err) { return Dz1ControlStateInfoResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1ControlStateInfoResponse *Dz1ControlStateInfoResponse_clone(Dz1ControlStateInfoResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ControlStateInfoResponse_purge(Dz1ControlStateInfoResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ControlStateInfoResponse_del(Dz1ControlStateInfoResponse *p);
static __inline__ void Dz1ControlStateInfoResponse_delAndSetNull(void *ptr)
{
	Dz1ControlStateInfoResponse **p = (Dz1ControlStateInfoResponse **)ptr;
	if (p != NULL) { Dz1ControlStateInfoResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ControlStateInfoResponse_dump(Dz1ControlStateInfoResponse *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ControlStateInfoResponse_fdump(FILE *fp, Dz1ControlStateInfoResponse *p, int tab);

// Dz1ControlStateInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1SensorStateInfoResponse
typedef struct Dz1SensorStateInfoResponse
{
	void *storage;
	unsigned int (*count)(struct Dz1SensorStateInfoResponse *p);
	Dz1Error (*travel)(struct Dz1SensorStateInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1SensorStateInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1SensorStateInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1SensorStateInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1SensorStateInfoResponse *p, Dz1Error (*func)(void *ptr, Dz1SensorStateInfo *entry), void *ptr);
	Dz1SensorStateInfo **(*get_array)(struct Dz1SensorStateInfoResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1SensorStateInfoResponse *p, Dz1SensorStateInfo *data);
} Dz1SensorStateInfoResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1SensorStateInfoResponse *Dz1SensorStateInfoResponse_new(Dz1Error *err);
static __inline__ Dz1SensorStateInfoResponse *Dz1SensorStateInfoResponse_gen(Dz1Error *err) { return Dz1SensorStateInfoResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1SensorStateInfoResponse *Dz1SensorStateInfoResponse_clone(Dz1SensorStateInfoResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfoResponse_purge(Dz1SensorStateInfoResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfoResponse_del(Dz1SensorStateInfoResponse *p);
static __inline__ void Dz1SensorStateInfoResponse_delAndSetNull(void *ptr)
{
	Dz1SensorStateInfoResponse **p = (Dz1SensorStateInfoResponse **)ptr;
	if (p != NULL) { Dz1SensorStateInfoResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfoResponse_dump(Dz1SensorStateInfoResponse *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SensorStateInfoResponse_fdump(FILE *fp, Dz1SensorStateInfoResponse *p, int tab);

// Dz1SensorStateInfoResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MovingObjectResponse
typedef struct Dz1MovingObjectResponse
{
	void *storage;
	unsigned int (*count)(struct Dz1MovingObjectResponse *p);
	Dz1Error (*travel)(struct Dz1MovingObjectResponse *p, Dz1Error (*func)(void *ptr, Dz1MovingObject *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MovingObjectResponse *p, Dz1Error (*func)(void *ptr, Dz1MovingObject *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MovingObjectResponse *p, Dz1Error (*func)(void *ptr, Dz1MovingObject *entry), void *ptr);
	Dz1MovingObject **(*get_array)(struct Dz1MovingObjectResponse *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MovingObjectResponse *p, Dz1MovingObject *data);
} Dz1MovingObjectResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1MovingObjectResponse *Dz1MovingObjectResponse_new(Dz1Error *err);
static __inline__ Dz1MovingObjectResponse *Dz1MovingObjectResponse_gen(Dz1Error *err) { return Dz1MovingObjectResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MovingObjectResponse *Dz1MovingObjectResponse_clone(Dz1MovingObjectResponse *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObjectResponse_purge(Dz1MovingObjectResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObjectResponse_del(Dz1MovingObjectResponse *p);
static __inline__ void Dz1MovingObjectResponse_delAndSetNull(void *ptr)
{
	Dz1MovingObjectResponse **p = (Dz1MovingObjectResponse **)ptr;
	if (p != NULL) { Dz1MovingObjectResponse_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObjectResponse_dump(Dz1MovingObjectResponse *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MovingObjectResponse_fdump(FILE *fp, Dz1MovingObjectResponse *p, int tab);

// Dz1MovingObjectResponse
////////////////////////////////////////////////////////////////////////////////



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1DDateTime_00100_fromASN(Dz1DDateTime_00100* dst, DDateTime_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1DDateTime_00100* Dz1DDateTime_00100_newFromASN(DDateTime_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1DDateTime_00100_toASN(DDateTime_00100* dst, Dz1DDateTime_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT DDateTime_00100* Dz1DDateTime_00100_toNewASN(Dz1DDateTime_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TransmissionAndSpeed_00100_fromASN(Dz1TransmissionAndSpeed_00100* dst, TransmissionAndSpeed_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1TransmissionAndSpeed_00100* Dz1TransmissionAndSpeed_00100_newFromASN(TransmissionAndSpeed_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TransmissionAndSpeed_00100_toASN(TransmissionAndSpeed_00100* dst, Dz1TransmissionAndSpeed_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT TransmissionAndSpeed_00100* Dz1TransmissionAndSpeed_00100_toNewASN(Dz1TransmissionAndSpeed_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TransmissionState_00100_fromASN(Dz1TransmissionState_00100* dst, TransmissionState_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1TransmissionState_00100* Dz1TransmissionState_00100_newFromASN(TransmissionState_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TransmissionState_00100_toASN(TransmissionState_00100* dst, Dz1TransmissionState_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT TransmissionState_00100* Dz1TransmissionState_00100_toNewASN(Dz1TransmissionState_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PositionalAccuracy_00100_fromASN(Dz1PositionalAccuracy_00100* dst, PositionalAccuracy_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1PositionalAccuracy_00100* Dz1PositionalAccuracy_00100_newFromASN(PositionalAccuracy_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PositionalAccuracy_00100_toASN(PositionalAccuracy_00100* dst, Dz1PositionalAccuracy_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT PositionalAccuracy_00100* Dz1PositionalAccuracy_00100_toNewASN(Dz1PositionalAccuracy_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TimeConfidence_00100_fromASN(Dz1TimeConfidence_00100* dst, TimeConfidence_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1TimeConfidence_00100* Dz1TimeConfidence_00100_newFromASN(TimeConfidence_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1TimeConfidence_00100_toASN(TimeConfidence_00100* dst, Dz1TimeConfidence_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT TimeConfidence_00100* Dz1TimeConfidence_00100_toNewASN(Dz1TimeConfidence_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PositionConfidenceSet_00100_fromASN(Dz1PositionConfidenceSet_00100* dst, PositionConfidenceSet_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1PositionConfidenceSet_00100* Dz1PositionConfidenceSet_00100_newFromASN(PositionConfidenceSet_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PositionConfidenceSet_00100_toASN(PositionConfidenceSet_00100* dst, Dz1PositionConfidenceSet_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT PositionConfidenceSet_00100* Dz1PositionConfidenceSet_00100_toNewASN(Dz1PositionConfidenceSet_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ElevationConfidence_00100_fromASN(Dz1ElevationConfidence_00100* dst, ElevationConfidence_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ElevationConfidence_00100* Dz1ElevationConfidence_00100_newFromASN(ElevationConfidence_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ElevationConfidence_00100_toASN(ElevationConfidence_00100* dst, Dz1ElevationConfidence_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ElevationConfidence_00100* Dz1ElevationConfidence_00100_toNewASN(Dz1ElevationConfidence_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PositionConfidence_00100_fromASN(Dz1PositionConfidence_00100* dst, PositionConfidence_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1PositionConfidence_00100* Dz1PositionConfidence_00100_newFromASN(PositionConfidence_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PositionConfidence_00100_toASN(PositionConfidence_00100* dst, Dz1PositionConfidence_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT PositionConfidence_00100* Dz1PositionConfidence_00100_toNewASN(Dz1PositionConfidence_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SpeedandHeadingandThrottleConfidence_00100_fromASN(Dz1SpeedandHeadingandThrottleConfidence_00100* dst, SpeedandHeadingandThrottleConfidence_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1SpeedandHeadingandThrottleConfidence_00100* Dz1SpeedandHeadingandThrottleConfidence_00100_newFromASN(SpeedandHeadingandThrottleConfidence_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SpeedandHeadingandThrottleConfidence_00100_toASN(SpeedandHeadingandThrottleConfidence_00100* dst, Dz1SpeedandHeadingandThrottleConfidence_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT SpeedandHeadingandThrottleConfidence_00100* Dz1SpeedandHeadingandThrottleConfidence_00100_toNewASN(Dz1SpeedandHeadingandThrottleConfidence_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1HeadingConfidence_00100_fromASN(Dz1HeadingConfidence_00100* dst, HeadingConfidence_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1HeadingConfidence_00100* Dz1HeadingConfidence_00100_newFromASN(HeadingConfidence_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1HeadingConfidence_00100_toASN(HeadingConfidence_00100* dst, Dz1HeadingConfidence_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT HeadingConfidence_00100* Dz1HeadingConfidence_00100_toNewASN(Dz1HeadingConfidence_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SpeedConfidence_00100_fromASN(Dz1SpeedConfidence_00100* dst, SpeedConfidence_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1SpeedConfidence_00100* Dz1SpeedConfidence_00100_newFromASN(SpeedConfidence_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SpeedConfidence_00100_toASN(SpeedConfidence_00100* dst, Dz1SpeedConfidence_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT SpeedConfidence_00100* Dz1SpeedConfidence_00100_toNewASN(Dz1SpeedConfidence_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ThrottleConfidence_00100_fromASN(Dz1ThrottleConfidence_00100* dst, ThrottleConfidence_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ThrottleConfidence_00100* Dz1ThrottleConfidence_00100_newFromASN(ThrottleConfidence_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ThrottleConfidence_00100_toASN(ThrottleConfidence_00100* dst, Dz1ThrottleConfidence_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ThrottleConfidence_00100* Dz1ThrottleConfidence_00100_toNewASN(Dz1ThrottleConfidence_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FullPositionVector_00100_fromASN(Dz1FullPositionVector_00100* dst, FullPositionVector_00100* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1FullPositionVector_00100* Dz1FullPositionVector_00100_newFromASN(FullPositionVector_00100* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FullPositionVector_00100_toASN(FullPositionVector_00100* dst, Dz1FullPositionVector_00100* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT FullPositionVector_00100* Dz1FullPositionVector_00100_toNewASN(Dz1FullPositionVector_00100* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionInfo_incident_Detected_Type_fromASN(Dz1IncidentDetectionInfo_incident_Detected_Type* dst, IncidentDetectionInfo_incident_Detected_Type* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionInfo_incident_Detected_Type* Dz1IncidentDetectionInfo_incident_Detected_Type_newFromASN(IncidentDetectionInfo_incident_Detected_Type* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionInfo_incident_Detected_Type_toASN(IncidentDetectionInfo_incident_Detected_Type* dst, Dz1IncidentDetectionInfo_incident_Detected_Type* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT IncidentDetectionInfo_incident_Detected_Type* Dz1IncidentDetectionInfo_incident_Detected_Type_toNewASN(Dz1IncidentDetectionInfo_incident_Detected_Type* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NMEACoord_compass_fromASN(Dz1NMEACoord_compass* dst, NMEACoord_compass* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord_compass* Dz1NMEACoord_compass_newFromASN(NMEACoord_compass* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NMEACoord_compass_toASN(NMEACoord_compass* dst, Dz1NMEACoord_compass* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT NMEACoord_compass* Dz1NMEACoord_compass_toNewASN(Dz1NMEACoord_compass* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NMEACoord_latitude_fromASN(Dz1NMEACoord_latitude* dst, NMEACoord_latitude* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord_latitude* Dz1NMEACoord_latitude_newFromASN(NMEACoord_latitude* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NMEACoord_latitude_toASN(NMEACoord_latitude* dst, Dz1NMEACoord_latitude* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT NMEACoord_latitude* Dz1NMEACoord_latitude_toNewASN(Dz1NMEACoord_latitude* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NMEACoord_longitude_fromASN(Dz1NMEACoord_longitude* dst, NMEACoord_longitude* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord_longitude* Dz1NMEACoord_longitude_newFromASN(NMEACoord_longitude* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NMEACoord_longitude_toASN(NMEACoord_longitude* dst, Dz1NMEACoord_longitude* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT NMEACoord_longitude* Dz1NMEACoord_longitude_toNewASN(Dz1NMEACoord_longitude* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NMEACoord_fromASN(Dz1NMEACoord* dst, NMEACoord* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1NMEACoord* Dz1NMEACoord_newFromASN(NMEACoord* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NMEACoord_toASN(NMEACoord* dst, Dz1NMEACoord* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT NMEACoord* Dz1NMEACoord_toNewASN(Dz1NMEACoord* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionInfo_fromASN(Dz1IncidentDetectionInfo* dst, IncidentDetectionInfo* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionInfo* Dz1IncidentDetectionInfo_newFromASN(IncidentDetectionInfo* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionInfo_toASN(IncidentDetectionInfo* dst, Dz1IncidentDetectionInfo* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT IncidentDetectionInfo* Dz1IncidentDetectionInfo_toNewASN(Dz1IncidentDetectionInfo* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentTerminationInfo_terminate_incidentType_fromASN(Dz1IncidentTerminationInfo_terminate_incidentType* dst, IncidentTerminationInfo_terminate_incidentType* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentTerminationInfo_terminate_incidentType* Dz1IncidentTerminationInfo_terminate_incidentType_newFromASN(IncidentTerminationInfo_terminate_incidentType* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentTerminationInfo_terminate_incidentType_toASN(IncidentTerminationInfo_terminate_incidentType* dst, Dz1IncidentTerminationInfo_terminate_incidentType* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT IncidentTerminationInfo_terminate_incidentType* Dz1IncidentTerminationInfo_terminate_incidentType_toNewASN(Dz1IncidentTerminationInfo_terminate_incidentType* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentTerminationInfo_fromASN(Dz1IncidentTerminationInfo* dst, IncidentTerminationInfo* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentTerminationInfo* Dz1IncidentTerminationInfo_newFromASN(IncidentTerminationInfo* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentTerminationInfo_toASN(IncidentTerminationInfo* dst, Dz1IncidentTerminationInfo* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT IncidentTerminationInfo* Dz1IncidentTerminationInfo_toNewASN(Dz1IncidentTerminationInfo* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_fromASN(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* dst, IncidentDetectionVideoFileInfoProvide_fileStatus* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_newFromASN(IncidentDetectionVideoFileInfoProvide_fileStatus* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_toASN(IncidentDetectionVideoFileInfoProvide_fileStatus* dst, Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT IncidentDetectionVideoFileInfoProvide_fileStatus* Dz1IncidentDetectionVideoFileInfoProvide_fileStatus_toNewASN(Dz1IncidentDetectionVideoFileInfoProvide_fileStatus* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionVideoFileInfoProvide_fromASN(Dz1IncidentDetectionVideoFileInfoProvide* dst, IncidentDetectionVideoFileInfoProvide* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionVideoFileInfoProvide* Dz1IncidentDetectionVideoFileInfoProvide_newFromASN(IncidentDetectionVideoFileInfoProvide* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionVideoFileInfoProvide_toASN(IncidentDetectionVideoFileInfoProvide* dst, Dz1IncidentDetectionVideoFileInfoProvide* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT IncidentDetectionVideoFileInfoProvide* Dz1IncidentDetectionVideoFileInfoProvide_toNewASN(Dz1IncidentDetectionVideoFileInfoProvide* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ControlStateInfo_fromASN(Dz1ControlStateInfo* dst, ControlStateInfo* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ControlStateInfo* Dz1ControlStateInfo_newFromASN(ControlStateInfo* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ControlStateInfo_toASN(ControlStateInfo* dst, Dz1ControlStateInfo* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ControlStateInfo* Dz1ControlStateInfo_toNewASN(Dz1ControlStateInfo* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SensorStateInfo_state_fromASN(Dz1SensorStateInfo_state* dst, SensorStateInfo_state* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1SensorStateInfo_state* Dz1SensorStateInfo_state_newFromASN(SensorStateInfo_state* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SensorStateInfo_state_toASN(SensorStateInfo_state* dst, Dz1SensorStateInfo_state* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT SensorStateInfo_state* Dz1SensorStateInfo_state_toNewASN(Dz1SensorStateInfo_state* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SensorStateInfo_fromASN(Dz1SensorStateInfo* dst, SensorStateInfo* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1SensorStateInfo* Dz1SensorStateInfo_newFromASN(SensorStateInfo* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SensorStateInfo_toASN(SensorStateInfo* dst, Dz1SensorStateInfo* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT SensorStateInfo* Dz1SensorStateInfo_toNewASN(Dz1SensorStateInfo* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Novelty_fromASN(Dz1Novelty* dst, Novelty* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1Novelty* Dz1Novelty_newFromASN(Novelty* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Novelty_toASN(Novelty* dst, Dz1Novelty* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT Novelty* Dz1Novelty_toNewASN(Dz1Novelty* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1MovingObject_objectType_fromASN(Dz1MovingObject_objectType* dst, MovingObject_objectType* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1MovingObject_objectType* Dz1MovingObject_objectType_newFromASN(MovingObject_objectType* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1MovingObject_objectType_toASN(MovingObject_objectType* dst, Dz1MovingObject_objectType* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT MovingObject_objectType* Dz1MovingObject_objectType_toNewASN(Dz1MovingObject_objectType* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1MovingObject_fromASN(Dz1MovingObject* dst, MovingObject* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1MovingObject* Dz1MovingObject_newFromASN(MovingObject* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1MovingObject_toASN(MovingObject* dst, Dz1MovingObject* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT MovingObject* Dz1MovingObject_toNewASN(Dz1MovingObject* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionInfoResponse_fromASN(Dz1IncidentDetectionInfoResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionInfoResponse* Dz1IncidentDetectionInfoResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionInfoResponse_toASN(ASN1List* dst, Dz1IncidentDetectionInfoResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1IncidentDetectionInfoResponse_toNewASN(Dz1IncidentDetectionInfoResponse* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentTerminationInfoResponse_fromASN(Dz1IncidentTerminationInfoResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentTerminationInfoResponse* Dz1IncidentTerminationInfoResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentTerminationInfoResponse_toASN(ASN1List* dst, Dz1IncidentTerminationInfoResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1IncidentTerminationInfoResponse_toNewASN(Dz1IncidentTerminationInfoResponse* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionVideoFileInfoProvideResponse_fromASN(Dz1IncidentDetectionVideoFileInfoProvideResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1IncidentDetectionVideoFileInfoProvideResponse* Dz1IncidentDetectionVideoFileInfoProvideResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1IncidentDetectionVideoFileInfoProvideResponse_toASN(ASN1List* dst, Dz1IncidentDetectionVideoFileInfoProvideResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1IncidentDetectionVideoFileInfoProvideResponse_toNewASN(Dz1IncidentDetectionVideoFileInfoProvideResponse* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ControlStateInfoResponse_fromASN(Dz1ControlStateInfoResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1ControlStateInfoResponse* Dz1ControlStateInfoResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ControlStateInfoResponse_toASN(ASN1List* dst, Dz1ControlStateInfoResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1ControlStateInfoResponse_toNewASN(Dz1ControlStateInfoResponse* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SensorStateInfoResponse_fromASN(Dz1SensorStateInfoResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1SensorStateInfoResponse* Dz1SensorStateInfoResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1SensorStateInfoResponse_toASN(ASN1List* dst, Dz1SensorStateInfoResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1SensorStateInfoResponse_toNewASN(Dz1SensorStateInfoResponse* src, ASN1WorkSpace* ws, Dz1Error* err);



DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1MovingObjectResponse_fromASN(Dz1MovingObjectResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1MovingObjectResponse* Dz1MovingObjectResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1MovingObjectResponse_toASN(ASN1List* dst, Dz1MovingObjectResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1MovingObjectResponse_toNewASN(Dz1MovingObjectResponse* src, ASN1WorkSpace* ws, Dz1Error* err);


#endif
