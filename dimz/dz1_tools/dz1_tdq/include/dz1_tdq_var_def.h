#ifndef _DZ1_TDC_DZ1_TDQ_VAR_DEF_H_
#define _DZ1_TDC_DZ1_TDQ_VAR_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqType
typedef enum Dz1TdqType
{
	Dz1TdqType_num_s8,
	Dz1TdqType_num_u8,
	Dz1TdqType_num_s16,
	Dz1TdqType_num_u16,
	Dz1TdqType_num_s32,
	Dz1TdqType_num_u32,
	Dz1TdqType_num_s64,
	Dz1TdqType_num_u64,
	Dz1TdqType_num_r32 = 16,
	Dz1TdqType_num_r64 = 17,
	Dz1TdqType_string = 32,
	Dz1TdqType_vstring,
	Dz1TdqType_tstring,
	Dz1TdqType_vtstring,
	Dz1TdqType_binary,
	Dz1TdqType_vbinary,
	Dz1TdqType_date = 48,
	Dz1TdqType_time,
	Dz1TdqType_timestamp,
	Dz1TdqType_blob = 64,
	Dz1TdqType_blobL,
	Dz1TdqType_max
} Dz1TdqType;

DZ1_CPPLINK str_t Dz1TdqTypeStrA(Dz1TdqType v);
DZ1_CPPLINK Dz1TdqType Dz1TdqTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqTypeStrW(Dz1TdqType v);
DZ1_CPPLINK Dz1TdqType Dz1TdqTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqTypeStr Dz1TdqTypeStrW
#define Dz1TdqTypeFromStr Dz1TdqTypeFromStrW
#else // UNICODE
#define Dz1TdqTypeStr Dz1TdqTypeStrA
#define Dz1TdqTypeFromStr Dz1TdqTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqTypeStr Dz1TdqTypeStrA
#define Dz1TdqTypeFromStr Dz1TdqTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqType *Dz1TdqType_new(Dz1TdqType *src, Dz1Error *err);
static __inline__ Dz1TdqType *Dz1TdqType_gen(Dz1Error *err) { Dz1TdqType v = Dz1TdqType_max; return Dz1TdqType_new(&v, err); }
static __inline__ void Dz1TdqType_del(Dz1TdqType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqType_delAndSetNull(void *ptr)
{
	Dz1TdqType **p = (Dz1TdqType **)ptr;
	if (p != NULL) { Dz1TdqType_del(*p); *p = NULL; }
}
// Dz1TdqType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlNumSpec
typedef struct Dz1TdqSqlNumSpec
{
	s64_t		size;
	bool_t		auto_inc;
} Dz1TdqSqlNumSpec;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlNumSpec *Dz1TdqSqlNumSpec_new(s64_t size, 
															   bool_t auto_inc, Dz1Error *err);
static __inline__ Dz1TdqSqlNumSpec *Dz1TdqSqlNumSpec_gen(Dz1Error *err) { return Dz1TdqSqlNumSpec_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlNumSpec_copy(Dz1TdqSqlNumSpec *dst, Dz1TdqSqlNumSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlNumSpec *Dz1TdqSqlNumSpec_clone(Dz1TdqSqlNumSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNumSpec_purge(Dz1TdqSqlNumSpec *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNumSpec_del(Dz1TdqSqlNumSpec *p);
static __inline__ void Dz1TdqSqlNumSpec_delAndSetNull(void *ptr)
{
	Dz1TdqSqlNumSpec **p = (Dz1TdqSqlNumSpec **)ptr;
	if (p) { Dz1TdqSqlNumSpec_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNumSpec_dump(Dz1TdqSqlNumSpec *p, int tab);
// Dz1TdqSqlNumSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlRealSpec
typedef struct Dz1TdqSqlRealSpec
{
	s64_t		percision;
} Dz1TdqSqlRealSpec;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlRealSpec *Dz1TdqSqlRealSpec_new(s64_t percision, Dz1Error *err);
static __inline__ Dz1TdqSqlRealSpec *Dz1TdqSqlRealSpec_gen(Dz1Error *err) { return Dz1TdqSqlRealSpec_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlRealSpec_copy(Dz1TdqSqlRealSpec *dst, Dz1TdqSqlRealSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlRealSpec *Dz1TdqSqlRealSpec_clone(Dz1TdqSqlRealSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlRealSpec_purge(Dz1TdqSqlRealSpec *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlRealSpec_del(Dz1TdqSqlRealSpec *p);
static __inline__ void Dz1TdqSqlRealSpec_delAndSetNull(void *ptr)
{
	Dz1TdqSqlRealSpec **p = (Dz1TdqSqlRealSpec **)ptr;
	if (p) { Dz1TdqSqlRealSpec_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlRealSpec_dump(Dz1TdqSqlRealSpec *p, int tab);
// Dz1TdqSqlRealSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlStrSpec
typedef struct Dz1TdqSqlStrSpec
{
	s64_t		size;
} Dz1TdqSqlStrSpec;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlStrSpec *Dz1TdqSqlStrSpec_new(s64_t size, Dz1Error *err);
static __inline__ Dz1TdqSqlStrSpec *Dz1TdqSqlStrSpec_gen(Dz1Error *err) { return Dz1TdqSqlStrSpec_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlStrSpec_copy(Dz1TdqSqlStrSpec *dst, Dz1TdqSqlStrSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlStrSpec *Dz1TdqSqlStrSpec_clone(Dz1TdqSqlStrSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStrSpec_purge(Dz1TdqSqlStrSpec *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStrSpec_del(Dz1TdqSqlStrSpec *p);
static __inline__ void Dz1TdqSqlStrSpec_delAndSetNull(void *ptr)
{
	Dz1TdqSqlStrSpec **p = (Dz1TdqSqlStrSpec **)ptr;
	if (p) { Dz1TdqSqlStrSpec_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStrSpec_dump(Dz1TdqSqlStrSpec *p, int tab);
// Dz1TdqSqlStrSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobSpec
typedef enum Dz1TdqSqlBlobSpec
{
	Dz1TdqSqlBlobSpec_embedded,
	Dz1TdqSqlBlobSpec_saved_file,
	Dz1TdqSqlBlobSpec_max
} Dz1TdqSqlBlobSpec;

DZ1_CPPLINK str_t Dz1TdqSqlBlobSpecStrA(Dz1TdqSqlBlobSpec v);
DZ1_CPPLINK Dz1TdqSqlBlobSpec Dz1TdqSqlBlobSpecFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqSqlBlobSpecStrW(Dz1TdqSqlBlobSpec v);
DZ1_CPPLINK Dz1TdqSqlBlobSpec Dz1TdqSqlBlobSpecFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqSqlBlobSpecStr Dz1TdqSqlBlobSpecStrW
#define Dz1TdqSqlBlobSpecFromStr Dz1TdqSqlBlobSpecFromStrW
#else // UNICODE
#define Dz1TdqSqlBlobSpecStr Dz1TdqSqlBlobSpecStrA
#define Dz1TdqSqlBlobSpecFromStr Dz1TdqSqlBlobSpecFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqSqlBlobSpecStr Dz1TdqSqlBlobSpecStrA
#define Dz1TdqSqlBlobSpecFromStr Dz1TdqSqlBlobSpecFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobSpec *Dz1TdqSqlBlobSpec_new(Dz1TdqSqlBlobSpec *src, Dz1Error *err);
static __inline__ Dz1TdqSqlBlobSpec *Dz1TdqSqlBlobSpec_gen(Dz1Error *err) { Dz1TdqSqlBlobSpec v = Dz1TdqSqlBlobSpec_max; return Dz1TdqSqlBlobSpec_new(&v, err); }
static __inline__ void Dz1TdqSqlBlobSpec_del(Dz1TdqSqlBlobSpec *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqSqlBlobSpec_delAndSetNull(void *ptr)
{
	Dz1TdqSqlBlobSpec **p = (Dz1TdqSqlBlobSpec **)ptr;
	if (p != NULL) { Dz1TdqSqlBlobSpec_del(*p); *p = NULL; }
}
// Dz1TdqSqlBlobSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlTypeSpecPresent
typedef enum Dz1TdqSqlTypeSpecPresent
{
	Dz1TdqSqlTypeSpecPresent_num_s8 = Dz1TdqType_num_s8,
	Dz1TdqSqlTypeSpecPresent_num_u8 = Dz1TdqType_num_u8,
	Dz1TdqSqlTypeSpecPresent_num_s16 = Dz1TdqType_num_s16,
	Dz1TdqSqlTypeSpecPresent_num_u16 = Dz1TdqType_num_u16,
	Dz1TdqSqlTypeSpecPresent_num_s32 = Dz1TdqType_num_s32,
	Dz1TdqSqlTypeSpecPresent_num_u32 = Dz1TdqType_num_u32,
	Dz1TdqSqlTypeSpecPresent_num_s64 = Dz1TdqType_num_s64,
	Dz1TdqSqlTypeSpecPresent_num_u64 = Dz1TdqType_num_u64,
	Dz1TdqSqlTypeSpecPresent_num_r32 = Dz1TdqType_num_r32,
	Dz1TdqSqlTypeSpecPresent_num_r64 = Dz1TdqType_num_r64,
	Dz1TdqSqlTypeSpecPresent_string = Dz1TdqType_string,
	Dz1TdqSqlTypeSpecPresent_vstring = Dz1TdqType_vstring,
	Dz1TdqSqlTypeSpecPresent_tstring = Dz1TdqType_tstring,
	Dz1TdqSqlTypeSpecPresent_vtstring = Dz1TdqType_vtstring,
	Dz1TdqSqlTypeSpecPresent_binary = Dz1TdqType_binary,
	Dz1TdqSqlTypeSpecPresent_vbinary = Dz1TdqType_vbinary,
	Dz1TdqSqlTypeSpecPresent_ymd = Dz1TdqType_date,
	Dz1TdqSqlTypeSpecPresent_hms = Dz1TdqType_time,
	Dz1TdqSqlTypeSpecPresent_stamp = Dz1TdqType_timestamp,
	Dz1TdqSqlTypeSpecPresent_blob = Dz1TdqType_blob,
	Dz1TdqSqlTypeSpecPresent_blobL = Dz1TdqType_blobL,
	Dz1TdqSqlTypeSpecPresent_max
} Dz1TdqSqlTypeSpecPresent;

DZ1_CPPLINK str_t Dz1TdqSqlTypeSpecPresentStrA(Dz1TdqSqlTypeSpecPresent v);
DZ1_CPPLINK Dz1TdqSqlTypeSpecPresent Dz1TdqSqlTypeSpecPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqSqlTypeSpecPresentStrW(Dz1TdqSqlTypeSpecPresent v);
DZ1_CPPLINK Dz1TdqSqlTypeSpecPresent Dz1TdqSqlTypeSpecPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqSqlTypeSpecPresentStr Dz1TdqSqlTypeSpecPresentStrW
#define Dz1TdqSqlTypeSpecPresentFromStr Dz1TdqSqlTypeSpecPresentFromStrW
#else // UNICODE
#define Dz1TdqSqlTypeSpecPresentStr Dz1TdqSqlTypeSpecPresentStrA
#define Dz1TdqSqlTypeSpecPresentFromStr Dz1TdqSqlTypeSpecPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqSqlTypeSpecPresentStr Dz1TdqSqlTypeSpecPresentStrA
#define Dz1TdqSqlTypeSpecPresentFromStr Dz1TdqSqlTypeSpecPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlTypeSpecPresent *Dz1TdqSqlTypeSpecPresent_new(Dz1TdqSqlTypeSpecPresent *src, Dz1Error *err);
static __inline__ Dz1TdqSqlTypeSpecPresent *Dz1TdqSqlTypeSpecPresent_gen(Dz1Error *err) { Dz1TdqSqlTypeSpecPresent v = Dz1TdqSqlTypeSpecPresent_max; return Dz1TdqSqlTypeSpecPresent_new(&v, err); }
#define Dz1TdqSqlTypeSpecPresent_clone             Dz1TdqSqlTypeSpecPresent_new
static __inline__ void Dz1TdqSqlTypeSpecPresent_del(Dz1TdqSqlTypeSpecPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqSqlTypeSpecPresent_delAndSetNull(void *ptr)
{
	Dz1TdqSqlTypeSpecPresent **p = (Dz1TdqSqlTypeSpecPresent **)ptr;
	if (p != NULL) { Dz1TdqSqlTypeSpecPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlTypeSpecPresent_dump(Dz1TdqSqlTypeSpecPresent *v, int tab);
// Dz1TdqSqlTypeSpecPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlTypeSpec
typedef struct Dz1TdqSqlTypeSpec
{
	Dz1TdqSqlTypeSpecPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1TdqSqlNumSpec		*num_s8;
		Dz1TdqSqlNumSpec		*num_u8;
		Dz1TdqSqlNumSpec		*num_s16;
		Dz1TdqSqlNumSpec		*num_u16;
		Dz1TdqSqlNumSpec		*num_s32;
		Dz1TdqSqlNumSpec		*num_u32;
		Dz1TdqSqlNumSpec		*num_s64;
		Dz1TdqSqlNumSpec		*num_u64;
		Dz1TdqSqlRealSpec		*num_r32;
		Dz1TdqSqlRealSpec		*num_r64;
		Dz1TdqSqlStrSpec		*string;
		Dz1TdqSqlStrSpec		*vstring;
		Dz1TdqSqlStrSpec		*tstring;
		Dz1TdqSqlStrSpec		*vtstring;
		Dz1TdqSqlStrSpec		*binary;
		Dz1TdqSqlStrSpec		*vbinary;
		u32_t					*ymd;
		u32_t					*hms;
		u32_t					*stamp;
		Dz1TdqSqlBlobSpec		 blob;
		Dz1TdqSqlBlobSpec		 blobL;
	} x;
} Dz1TdqSqlTypeSpec;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_new(Dz1TdqSqlTypeSpecPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_gen(Dz1Error *err) { return Dz1TdqSqlTypeSpec_new(Dz1TdqSqlTypeSpecPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TdqSqlTypeSpec_copy(Dz1TdqSqlTypeSpec *dst, Dz1TdqSqlTypeSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_clone(Dz1TdqSqlTypeSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlTypeSpec_purge(Dz1TdqSqlTypeSpec *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlTypeSpec_del(Dz1TdqSqlTypeSpec *p);
static __inline__ void Dz1TdqSqlTypeSpec_delAndSetNull(void *ptr)
{
	Dz1TdqSqlTypeSpec **p = (Dz1TdqSqlTypeSpec **)ptr;
	if (p != NULL) { Dz1TdqSqlTypeSpec_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlTypeSpec_dump(Dz1TdqSqlTypeSpec *p, int tab);
// Dz1TdqSqlTypeSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlStr
typedef struct Dz1TdqSqlStr
{
	Dz1Str		text;
	u32_t		alloc_byte;
} Dz1TdqSqlStr;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlStr *Dz1TdqSqlStr_new(Dz1Str text, 
													   u32_t alloc_byte, Dz1Error *err);	// User Customized
static __inline__ Dz1TdqSqlStr *Dz1TdqSqlStr_gen(Dz1Error *err) { return Dz1TdqSqlStr_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlStr_copy(Dz1TdqSqlStr *dst, Dz1TdqSqlStr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlStr *Dz1TdqSqlStr_clone(Dz1TdqSqlStr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStr_purge(Dz1TdqSqlStr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStr_del(Dz1TdqSqlStr *p);
static __inline__ void Dz1TdqSqlStr_delAndSetNull(void *ptr)
{
	Dz1TdqSqlStr **p = (Dz1TdqSqlStr **)ptr;
	if (p) { Dz1TdqSqlStr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStr_dump(Dz1TdqSqlStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlStr_cmp(Dz1TdqSqlStr *a, Dz1TdqSqlStr *b); 
// Dz1TdqSqlStr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlDate
typedef struct Dz1TdqSqlDate
{
	s16_t		year;
	u16_t		month;
	u16_t		day;
} Dz1TdqSqlDate;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlDate *Dz1TdqSqlDate_new(s16_t year, 
														 u16_t month, 
														 u16_t day, Dz1Error *err);
static __inline__ Dz1TdqSqlDate *Dz1TdqSqlDate_gen(Dz1Error *err) { return Dz1TdqSqlDate_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlDate_copy(Dz1TdqSqlDate *dst, Dz1TdqSqlDate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlDate *Dz1TdqSqlDate_clone(Dz1TdqSqlDate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlDate_purge(Dz1TdqSqlDate *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlDate_del(Dz1TdqSqlDate *p);
static __inline__ void Dz1TdqSqlDate_delAndSetNull(void *ptr)
{
	Dz1TdqSqlDate **p = (Dz1TdqSqlDate **)ptr;
	if (p) { Dz1TdqSqlDate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlDate_dump(Dz1TdqSqlDate *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlDate_cmp(Dz1TdqSqlDate *a, Dz1TdqSqlDate *b); 
// Dz1TdqSqlDate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlTime
typedef struct Dz1TdqSqlTime
{
	u16_t		hour;
	u16_t		minute;
	u16_t		second;
} Dz1TdqSqlTime;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlTime *Dz1TdqSqlTime_new(u16_t hour, 
														 u16_t minute, 
														 u16_t second, Dz1Error *err);
static __inline__ Dz1TdqSqlTime *Dz1TdqSqlTime_gen(Dz1Error *err) { return Dz1TdqSqlTime_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlTime_copy(Dz1TdqSqlTime *dst, Dz1TdqSqlTime *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlTime *Dz1TdqSqlTime_clone(Dz1TdqSqlTime *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlTime_purge(Dz1TdqSqlTime *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlTime_del(Dz1TdqSqlTime *p);
static __inline__ void Dz1TdqSqlTime_delAndSetNull(void *ptr)
{
	Dz1TdqSqlTime **p = (Dz1TdqSqlTime **)ptr;
	if (p) { Dz1TdqSqlTime_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlTime_dump(Dz1TdqSqlTime *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlTime_cmp(Dz1TdqSqlTime *a, Dz1TdqSqlTime *b); 
// Dz1TdqSqlTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlStamp
typedef struct Dz1TdqSqlStamp
{
	s16_t		year;
	u16_t		month;
	u16_t		day;
	u16_t		hour;
	u16_t		minute;
	u16_t		second;
	u32_t		frac;
} Dz1TdqSqlStamp;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlStamp *Dz1TdqSqlStamp_new(s16_t year, 
														   u16_t month, 
														   u16_t day, 
														   u16_t hour, 
														   u16_t minute, 
														   u16_t second, 
														   u32_t frac, Dz1Error *err);
static __inline__ Dz1TdqSqlStamp *Dz1TdqSqlStamp_gen(Dz1Error *err) { return Dz1TdqSqlStamp_new(0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlStamp_copy(Dz1TdqSqlStamp *dst, Dz1TdqSqlStamp *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlStamp *Dz1TdqSqlStamp_clone(Dz1TdqSqlStamp *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStamp_purge(Dz1TdqSqlStamp *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStamp_del(Dz1TdqSqlStamp *p);
static __inline__ void Dz1TdqSqlStamp_delAndSetNull(void *ptr)
{
	Dz1TdqSqlStamp **p = (Dz1TdqSqlStamp **)ptr;
	if (p) { Dz1TdqSqlStamp_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlStamp_dump(Dz1TdqSqlStamp *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlStamp_cmp(Dz1TdqSqlStamp *a, Dz1TdqSqlStamp *b); 
// Dz1TdqSqlStamp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobRef
typedef struct Dz1TdqSqlBlobRef
{
	void		*ptr;
	u32_t		 sz;
} Dz1TdqSqlBlobRef;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobRef *Dz1TdqSqlBlobRef_new(void *ptr_ref, 
															   u32_t sz, Dz1Error *err);
static __inline__ Dz1TdqSqlBlobRef *Dz1TdqSqlBlobRef_gen(Dz1Error *err) { return Dz1TdqSqlBlobRef_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlBlobRef_copy(Dz1TdqSqlBlobRef *dst, Dz1TdqSqlBlobRef *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobRef *Dz1TdqSqlBlobRef_clone(Dz1TdqSqlBlobRef *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobRef_purge(Dz1TdqSqlBlobRef *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobRef_del(Dz1TdqSqlBlobRef *p);
static __inline__ void Dz1TdqSqlBlobRef_delAndSetNull(void *ptr)
{
	Dz1TdqSqlBlobRef **p = (Dz1TdqSqlBlobRef **)ptr;
	if (p) { Dz1TdqSqlBlobRef_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobRef_dump(Dz1TdqSqlBlobRef *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlBlobRef_cmp(Dz1TdqSqlBlobRef *a, Dz1TdqSqlBlobRef *b); 	// User Customized
// Dz1TdqSqlBlobRef
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobToDBPresent
typedef enum Dz1TdqSqlBlobToDBPresent
{
	Dz1TdqSqlBlobToDBPresent_embedded = 0,
	Dz1TdqSqlBlobToDBPresent_ref_buf = 1,
	Dz1TdqSqlBlobToDBPresent_saved_file = 2,
	Dz1TdqSqlBlobToDBPresent_max
} Dz1TdqSqlBlobToDBPresent;

DZ1_CPPLINK str_t Dz1TdqSqlBlobToDBPresentStrA(Dz1TdqSqlBlobToDBPresent v);
DZ1_CPPLINK Dz1TdqSqlBlobToDBPresent Dz1TdqSqlBlobToDBPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqSqlBlobToDBPresentStrW(Dz1TdqSqlBlobToDBPresent v);
DZ1_CPPLINK Dz1TdqSqlBlobToDBPresent Dz1TdqSqlBlobToDBPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqSqlBlobToDBPresentStr Dz1TdqSqlBlobToDBPresentStrW
#define Dz1TdqSqlBlobToDBPresentFromStr Dz1TdqSqlBlobToDBPresentFromStrW
#else // UNICODE
#define Dz1TdqSqlBlobToDBPresentStr Dz1TdqSqlBlobToDBPresentStrA
#define Dz1TdqSqlBlobToDBPresentFromStr Dz1TdqSqlBlobToDBPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqSqlBlobToDBPresentStr Dz1TdqSqlBlobToDBPresentStrA
#define Dz1TdqSqlBlobToDBPresentFromStr Dz1TdqSqlBlobToDBPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobToDBPresent *Dz1TdqSqlBlobToDBPresent_new(Dz1TdqSqlBlobToDBPresent *src, Dz1Error *err);
static __inline__ Dz1TdqSqlBlobToDBPresent *Dz1TdqSqlBlobToDBPresent_gen(Dz1Error *err) { Dz1TdqSqlBlobToDBPresent v = Dz1TdqSqlBlobToDBPresent_max; return Dz1TdqSqlBlobToDBPresent_new(&v, err); }
#define Dz1TdqSqlBlobToDBPresent_clone             Dz1TdqSqlBlobToDBPresent_new
static __inline__ void Dz1TdqSqlBlobToDBPresent_del(Dz1TdqSqlBlobToDBPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqSqlBlobToDBPresent_delAndSetNull(void *ptr)
{
	Dz1TdqSqlBlobToDBPresent **p = (Dz1TdqSqlBlobToDBPresent **)ptr;
	if (p != NULL) { Dz1TdqSqlBlobToDBPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobToDBPresent_dump(Dz1TdqSqlBlobToDBPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlBlobToDBPresent_cmp(Dz1TdqSqlBlobToDBPresent *a, Dz1TdqSqlBlobToDBPresent *b);
// Dz1TdqSqlBlobToDBPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobToDB
typedef struct Dz1TdqSqlBlobToDB
{
	Dz1TdqSqlBlobToDBPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Binary2			*embedded;
		Dz1TdqSqlBlobRef	*ref_buf;
		Dz1Str				 saved_file;
	} x;
} Dz1TdqSqlBlobToDB;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobToDB *Dz1TdqSqlBlobToDB_new(Dz1TdqSqlBlobToDBPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TdqSqlBlobToDB *Dz1TdqSqlBlobToDB_gen(Dz1Error *err) { return Dz1TdqSqlBlobToDB_new(Dz1TdqSqlBlobToDBPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TdqSqlBlobToDB_copy(Dz1TdqSqlBlobToDB *dst, Dz1TdqSqlBlobToDB *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobToDB *Dz1TdqSqlBlobToDB_clone(Dz1TdqSqlBlobToDB *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobToDB_purge(Dz1TdqSqlBlobToDB *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobToDB_del(Dz1TdqSqlBlobToDB *p);
static __inline__ void Dz1TdqSqlBlobToDB_delAndSetNull(void *ptr)
{
	Dz1TdqSqlBlobToDB **p = (Dz1TdqSqlBlobToDB **)ptr;
	if (p != NULL) { Dz1TdqSqlBlobToDB_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobToDB_dump(Dz1TdqSqlBlobToDB *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlBlobToDB_cmp(Dz1TdqSqlBlobToDB *a, Dz1TdqSqlBlobToDB *b);
// Dz1TdqSqlBlobToDB
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobFromDBPresent
typedef enum Dz1TdqSqlBlobFromDBPresent
{
	Dz1TdqSqlBlobFromDBPresent_embedded = 0,
	Dz1TdqSqlBlobFromDBPresent_saved_file = 2,
	Dz1TdqSqlBlobFromDBPresent_max
} Dz1TdqSqlBlobFromDBPresent;

DZ1_CPPLINK str_t Dz1TdqSqlBlobFromDBPresentStrA(Dz1TdqSqlBlobFromDBPresent v);
DZ1_CPPLINK Dz1TdqSqlBlobFromDBPresent Dz1TdqSqlBlobFromDBPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqSqlBlobFromDBPresentStrW(Dz1TdqSqlBlobFromDBPresent v);
DZ1_CPPLINK Dz1TdqSqlBlobFromDBPresent Dz1TdqSqlBlobFromDBPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqSqlBlobFromDBPresentStr Dz1TdqSqlBlobFromDBPresentStrW
#define Dz1TdqSqlBlobFromDBPresentFromStr Dz1TdqSqlBlobFromDBPresentFromStrW
#else // UNICODE
#define Dz1TdqSqlBlobFromDBPresentStr Dz1TdqSqlBlobFromDBPresentStrA
#define Dz1TdqSqlBlobFromDBPresentFromStr Dz1TdqSqlBlobFromDBPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqSqlBlobFromDBPresentStr Dz1TdqSqlBlobFromDBPresentStrA
#define Dz1TdqSqlBlobFromDBPresentFromStr Dz1TdqSqlBlobFromDBPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobFromDBPresent *Dz1TdqSqlBlobFromDBPresent_new(Dz1TdqSqlBlobFromDBPresent *src, Dz1Error *err);
static __inline__ Dz1TdqSqlBlobFromDBPresent *Dz1TdqSqlBlobFromDBPresent_gen(Dz1Error *err) { Dz1TdqSqlBlobFromDBPresent v = Dz1TdqSqlBlobFromDBPresent_max; return Dz1TdqSqlBlobFromDBPresent_new(&v, err); }
#define Dz1TdqSqlBlobFromDBPresent_clone             Dz1TdqSqlBlobFromDBPresent_new
static __inline__ void Dz1TdqSqlBlobFromDBPresent_del(Dz1TdqSqlBlobFromDBPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqSqlBlobFromDBPresent_delAndSetNull(void *ptr)
{
	Dz1TdqSqlBlobFromDBPresent **p = (Dz1TdqSqlBlobFromDBPresent **)ptr;
	if (p != NULL) { Dz1TdqSqlBlobFromDBPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobFromDBPresent_dump(Dz1TdqSqlBlobFromDBPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlBlobFromDBPresent_cmp(Dz1TdqSqlBlobFromDBPresent *a, Dz1TdqSqlBlobFromDBPresent *b);
// Dz1TdqSqlBlobFromDBPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlobFromDB
typedef struct Dz1TdqSqlBlobFromDB
{
	Dz1TdqSqlBlobFromDBPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Binary2		*embedded;
		Dz1Str			 saved_file;
	} x;
} Dz1TdqSqlBlobFromDB;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobFromDB *Dz1TdqSqlBlobFromDB_new(Dz1TdqSqlBlobFromDBPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TdqSqlBlobFromDB *Dz1TdqSqlBlobFromDB_gen(Dz1Error *err) { return Dz1TdqSqlBlobFromDB_new(Dz1TdqSqlBlobFromDBPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TdqSqlBlobFromDB_copy(Dz1TdqSqlBlobFromDB *dst, Dz1TdqSqlBlobFromDB *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlobFromDB *Dz1TdqSqlBlobFromDB_clone(Dz1TdqSqlBlobFromDB *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobFromDB_purge(Dz1TdqSqlBlobFromDB *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobFromDB_del(Dz1TdqSqlBlobFromDB *p);
static __inline__ void Dz1TdqSqlBlobFromDB_delAndSetNull(void *ptr)
{
	Dz1TdqSqlBlobFromDB **p = (Dz1TdqSqlBlobFromDB **)ptr;
	if (p != NULL) { Dz1TdqSqlBlobFromDB_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlobFromDB_dump(Dz1TdqSqlBlobFromDB *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlBlobFromDB_cmp(Dz1TdqSqlBlobFromDB *a, Dz1TdqSqlBlobFromDB *b);
// Dz1TdqSqlBlobFromDB
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlob
typedef struct Dz1TdqSqlBlob
{
	Dz1TdqSqlBlobToDB		*writeToDB;
	Dz1TdqSqlBlobFromDB		*readFromDB;
	s64_t					 iosz;
} Dz1TdqSqlBlob;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlob *Dz1TdqSqlBlob_new(Dz1TdqSqlBlobToDB *writeToDB, 
														 Dz1TdqSqlBlobFromDB *readFromDB, Dz1Error *err);
static __inline__ Dz1TdqSqlBlob *Dz1TdqSqlBlob_gen(Dz1Error *err) { return Dz1TdqSqlBlob_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlBlob_copy(Dz1TdqSqlBlob *dst, Dz1TdqSqlBlob *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlBlob *Dz1TdqSqlBlob_clone(Dz1TdqSqlBlob *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlob_purge(Dz1TdqSqlBlob *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlob_del(Dz1TdqSqlBlob *p);
static __inline__ void Dz1TdqSqlBlob_delAndSetNull(void *ptr)
{
	Dz1TdqSqlBlob **p = (Dz1TdqSqlBlob **)ptr;
	if (p) { Dz1TdqSqlBlob_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlBlob_dump(Dz1TdqSqlBlob *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlBlob_cmp(Dz1TdqSqlBlob *a, Dz1TdqSqlBlob *b); 
// Dz1TdqSqlBlob
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarPresent
typedef enum Dz1TdqSqlVarPresent
{
	Dz1TdqSqlVarPresent_s8 = Dz1TdqType_num_s8,
	Dz1TdqSqlVarPresent_u8 = Dz1TdqType_num_u8,
	Dz1TdqSqlVarPresent_s16 = Dz1TdqType_num_s16,
	Dz1TdqSqlVarPresent_u16 = Dz1TdqType_num_u16,
	Dz1TdqSqlVarPresent_s32 = Dz1TdqType_num_s32,
	Dz1TdqSqlVarPresent_u32 = Dz1TdqType_num_u32,
	Dz1TdqSqlVarPresent_s64 = Dz1TdqType_num_s64,
	Dz1TdqSqlVarPresent_u64 = Dz1TdqType_num_u64,
	Dz1TdqSqlVarPresent_r32 = Dz1TdqType_num_r32,
	Dz1TdqSqlVarPresent_r64 = Dz1TdqType_num_r64,
	Dz1TdqSqlVarPresent_string = Dz1TdqType_string,
	Dz1TdqSqlVarPresent_vstring = Dz1TdqType_vstring,
	Dz1TdqSqlVarPresent_tstring = Dz1TdqType_tstring,
	Dz1TdqSqlVarPresent_vtstring = Dz1TdqType_vtstring,
	Dz1TdqSqlVarPresent_binary = Dz1TdqType_binary,
	Dz1TdqSqlVarPresent_vbinary = Dz1TdqType_vbinary,
	Dz1TdqSqlVarPresent_ymd = Dz1TdqType_date,
	Dz1TdqSqlVarPresent_hms = Dz1TdqType_time,
	Dz1TdqSqlVarPresent_stamp = Dz1TdqType_timestamp,
	Dz1TdqSqlVarPresent_blob = Dz1TdqType_blob,
	Dz1TdqSqlVarPresent_blobL = Dz1TdqType_blobL,
	Dz1TdqSqlVarPresent_nul = 65535,
	Dz1TdqSqlVarPresent_max
} Dz1TdqSqlVarPresent;

DZ1_CPPLINK str_t Dz1TdqSqlVarPresentStrA(Dz1TdqSqlVarPresent v);
DZ1_CPPLINK Dz1TdqSqlVarPresent Dz1TdqSqlVarPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqSqlVarPresentStrW(Dz1TdqSqlVarPresent v);
DZ1_CPPLINK Dz1TdqSqlVarPresent Dz1TdqSqlVarPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqSqlVarPresentStr Dz1TdqSqlVarPresentStrW
#define Dz1TdqSqlVarPresentFromStr Dz1TdqSqlVarPresentFromStrW
#else // UNICODE
#define Dz1TdqSqlVarPresentStr Dz1TdqSqlVarPresentStrA
#define Dz1TdqSqlVarPresentFromStr Dz1TdqSqlVarPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqSqlVarPresentStr Dz1TdqSqlVarPresentStrA
#define Dz1TdqSqlVarPresentFromStr Dz1TdqSqlVarPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlVarPresent *Dz1TdqSqlVarPresent_new(Dz1TdqSqlVarPresent *src, Dz1Error *err);
static __inline__ Dz1TdqSqlVarPresent *Dz1TdqSqlVarPresent_gen(Dz1Error *err) { Dz1TdqSqlVarPresent v = Dz1TdqSqlVarPresent_max; return Dz1TdqSqlVarPresent_new(&v, err); }
#define Dz1TdqSqlVarPresent_clone             Dz1TdqSqlVarPresent_new
static __inline__ void Dz1TdqSqlVarPresent_del(Dz1TdqSqlVarPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqSqlVarPresent_delAndSetNull(void *ptr)
{
	Dz1TdqSqlVarPresent **p = (Dz1TdqSqlVarPresent **)ptr;
	if (p != NULL) { Dz1TdqSqlVarPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVarPresent_dump(Dz1TdqSqlVarPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlVarPresent_cmp(Dz1TdqSqlVarPresent *a, Dz1TdqSqlVarPresent *b);
// Dz1TdqSqlVarPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVar
typedef struct Dz1TdqSqlVar
{
	Dz1TdqSqlVarPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		s8_t				 s8;
		u8_t				 u8;
		s16_t				 s16;
		u16_t				 u16;
		s32_t				 s32;
		u32_t				 u32;
		s64_t				 s64;
		u64_t				 u64;
		float				 r32;
		real64_t			 r64;
		Dz1TdqSqlStr		*string;
		Dz1TdqSqlStr		*vstring;
		Dz1TdqSqlStr		*tstring;
		Dz1TdqSqlStr		*vtstring;
		Dz1Binary2			*binary;
		Dz1Binary2			*vbinary;
		Dz1TdqSqlDate		*ymd;
		Dz1TdqSqlTime		*hms;
		Dz1TdqSqlStamp		*stamp;
		Dz1TdqSqlBlob		*blob;
		Dz1TdqSqlBlob		*blobL;
		Dz1TdqType			 nul;
	} x;
} Dz1TdqSqlVar;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlVar *Dz1TdqSqlVar_new(Dz1TdqSqlVarPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TdqSqlVar *Dz1TdqSqlVar_gen(Dz1Error *err) { return Dz1TdqSqlVar_new(Dz1TdqSqlVarPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TdqSqlVar_copy(Dz1TdqSqlVar *dst, Dz1TdqSqlVar *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlVar *Dz1TdqSqlVar_clone(Dz1TdqSqlVar *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVar_purge(Dz1TdqSqlVar *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVar_del(Dz1TdqSqlVar *p);
static __inline__ void Dz1TdqSqlVar_delAndSetNull(void *ptr)
{
	Dz1TdqSqlVar **p = (Dz1TdqSqlVar **)ptr;
	if (p != NULL) { Dz1TdqSqlVar_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVar_dump(Dz1TdqSqlVar *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlVar_cmp(Dz1TdqSqlVar *a, Dz1TdqSqlVar *b);
// Dz1TdqSqlVar
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarArray
typedef struct Dz1TdqSqlVarArray
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqSqlVarArray *p);
	Dz1Error (*travel)(struct Dz1TdqSqlVarArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqSqlVarArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqSqlVarArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *entry), void *ptr);
	Dz1TdqSqlVar **(*get_array)(struct Dz1TdqSqlVarArray *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqSqlVarArray *p, Dz1TdqSqlVar *data);
	int (*cmp)(Dz1TdqSqlVar *a, Dz1TdqSqlVar *b);
} Dz1TdqSqlVarArray;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_new(Dz1Error *err);
static __inline__ Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_gen(Dz1Error *err) { return Dz1TdqSqlVarArray_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_clone(Dz1TdqSqlVarArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVarArray_purge(Dz1TdqSqlVarArray *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVarArray_del(Dz1TdqSqlVarArray *p);
static __inline__ void Dz1TdqSqlVarArray_delAndSetNull(void *ptr)
{
	Dz1TdqSqlVarArray **p = (Dz1TdqSqlVarArray **)ptr;
	if (p != NULL) { Dz1TdqSqlVarArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVarArray_dump(Dz1TdqSqlVarArray *p, int tab);

// Dz1TdqSqlVarArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarRefArray
typedef struct Dz1TdqSqlVarRefArray
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqSqlVarRefArray *p);
	Dz1Error (*travel)(struct Dz1TdqSqlVarRefArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqSqlVarRefArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqSqlVarRefArray *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlVar *entry), void *ptr);
	Dz1TdqSqlVar **(*get_array)(struct Dz1TdqSqlVarRefArray *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqSqlVarRefArray *p, Dz1TdqSqlVar *data);
	int (*cmp)(Dz1TdqSqlVar *a, Dz1TdqSqlVar *b);
} Dz1TdqSqlVarRefArray;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlVarRefArray *Dz1TdqSqlVarRefArray_new(Dz1Error *err);
static __inline__ Dz1TdqSqlVarRefArray *Dz1TdqSqlVarRefArray_gen(Dz1Error *err) { return Dz1TdqSqlVarRefArray_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlVarRefArray *Dz1TdqSqlVarRefArray_clone(Dz1TdqSqlVarRefArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVarRefArray_purge(Dz1TdqSqlVarRefArray *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVarRefArray_del(Dz1TdqSqlVarRefArray *p);
static __inline__ void Dz1TdqSqlVarRefArray_delAndSetNull(void *ptr)
{
	Dz1TdqSqlVarRefArray **p = (Dz1TdqSqlVarRefArray **)ptr;
	if (p != NULL) { Dz1TdqSqlVarRefArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlVarRefArray_dump(Dz1TdqSqlVarRefArray *p, int tab);

// Dz1TdqSqlVarRefArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlNamedVar
typedef struct Dz1TdqSqlNamedVar
{
	Dz1Str			 name;
	Dz1TdqSqlVar	*val;
} Dz1TdqSqlNamedVar;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_new(Dz1Str name, 
																 Dz1TdqSqlVar *val, Dz1Error *err);
static __inline__ Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_gen(Dz1Error *err) { return Dz1TdqSqlNamedVar_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqSqlNamedVar_copy(Dz1TdqSqlNamedVar *dst, Dz1TdqSqlNamedVar *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_clone(Dz1TdqSqlNamedVar *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNamedVar_purge(Dz1TdqSqlNamedVar *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNamedVar_del(Dz1TdqSqlNamedVar *p);
static __inline__ void Dz1TdqSqlNamedVar_delAndSetNull(void *ptr)
{
	Dz1TdqSqlNamedVar **p = (Dz1TdqSqlNamedVar **)ptr;
	if (p) { Dz1TdqSqlNamedVar_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNamedVar_dump(Dz1TdqSqlNamedVar *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqSqlNamedVar_cmp(Dz1TdqSqlNamedVar *a, Dz1TdqSqlNamedVar *b); 
// Dz1TdqSqlNamedVar
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlNamedVarList
typedef struct Dz1TdqSqlNamedVarList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqSqlNamedVarList *p);
	Dz1Error (*travel)(struct Dz1TdqSqlNamedVarList *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlNamedVar *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqSqlNamedVarList *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlNamedVar *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqSqlNamedVarList *p, Dz1Error (*func)(void *ptr, Dz1TdqSqlNamedVar *entry), void *ptr);
	Dz1TdqSqlNamedVar **(*get_array)(struct Dz1TdqSqlNamedVarList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqSqlNamedVarList *p, Dz1TdqSqlNamedVar *data);
	bool_t (*remove)(struct Dz1TdqSqlNamedVarList *p, Dz1TdqSqlNamedVar *key);
	Dz1TdqSqlNamedVar *(*extract)(struct Dz1TdqSqlNamedVarList *p, Dz1TdqSqlNamedVar *key);
	Dz1TdqSqlNamedVar *(*find)(struct Dz1TdqSqlNamedVarList *p, Dz1TdqSqlNamedVar *key);
	int (*cmp)(Dz1TdqSqlNamedVar *a, Dz1TdqSqlNamedVar *b);
} Dz1TdqSqlNamedVarList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlNamedVarList *Dz1TdqSqlNamedVarList_new(Dz1Error *err);
static __inline__ Dz1TdqSqlNamedVarList *Dz1TdqSqlNamedVarList_gen(Dz1Error *err) { return Dz1TdqSqlNamedVarList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqSqlNamedVarList *Dz1TdqSqlNamedVarList_clone(Dz1TdqSqlNamedVarList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNamedVarList_purge(Dz1TdqSqlNamedVarList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNamedVarList_del(Dz1TdqSqlNamedVarList *p);
static __inline__ void Dz1TdqSqlNamedVarList_delAndSetNull(void *ptr)
{
	Dz1TdqSqlNamedVarList **p = (Dz1TdqSqlNamedVarList **)ptr;
	if (p != NULL) { Dz1TdqSqlNamedVarList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqSqlNamedVarList_dump(Dz1TdqSqlNamedVarList *p, int tab);

// Dz1TdqSqlNamedVarList
////////////////////////////////////////////////////////////////////////////////

#endif
