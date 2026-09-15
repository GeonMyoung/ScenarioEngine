#ifndef _DZ1_TDC_DZ1_LOGICS_DEF_H_
#define _DZ1_TDC_DZ1_LOGICS_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_logics_type.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchType
typedef enum Dz1LogicMatchType
{
	Dz1LogicMatchType_LessThen,
	Dz1LogicMatchType_GreaterThen,
	Dz1LogicMatchType_Equal,
	Dz1LogicMatchType_LessEqual,
	Dz1LogicMatchType_GreaterEqual,
	Dz1LogicMatchType_Like,
	Dz1LogicMatchType_max
} Dz1LogicMatchType;

DZ1_CPPLINK str_t Dz1LogicMatchTypeStrA(Dz1LogicMatchType v);
DZ1_CPPLINK Dz1LogicMatchType Dz1LogicMatchTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1LogicMatchTypeStrW(Dz1LogicMatchType v);
DZ1_CPPLINK Dz1LogicMatchType Dz1LogicMatchTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1LogicMatchTypeStr Dz1LogicMatchTypeStrW
#define Dz1LogicMatchTypeFromStr Dz1LogicMatchTypeFromStrW
#else // UNICODE
#define Dz1LogicMatchTypeStr Dz1LogicMatchTypeStrA
#define Dz1LogicMatchTypeFromStr Dz1LogicMatchTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1LogicMatchTypeStr Dz1LogicMatchTypeStrA
#define Dz1LogicMatchTypeFromStr Dz1LogicMatchTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchType *Dz1LogicMatchType_new(Dz1LogicMatchType *src, Dz1Error *err);
static __inline__ Dz1LogicMatchType *Dz1LogicMatchType_gen(Dz1Error *err) { Dz1LogicMatchType v = Dz1LogicMatchType_max; return Dz1LogicMatchType_new(&v, err); }
static __inline__ void Dz1LogicMatchType_del(Dz1LogicMatchType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1LogicMatchType_delAndSetNull(void *ptr)
{
	Dz1LogicMatchType **p = (Dz1LogicMatchType **)ptr;
	if (p != NULL) { Dz1LogicMatchType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchTypeA_dump(Dz1LogicMatchType *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchTypeW_dump(Dz1LogicMatchType *v, int tab);
#ifdef UNICODE
#define Dz1LogicMatchType_dump Dz1LogicMatchTypeW_dump
#else //  UNICODE
#define Dz1LogicMatchType_dump Dz1LogicMatchTypeA_dump
#endif //  UNICODE
static __inline__ void Dz1LogicMatchTypeX_dump(Dz1LogicMatchType *p, int tab) { DZ1_DUMP(Dz1LogicMatchType, p, tab); }
#else // UNIX_SYSTEM
#define Dz1LogicMatchType_dump Dz1LogicMatchTypeA_dump
#define Dz1LogicMatchTypeX_dump Dz1LogicMatchTypeA_dump
#endif // UNIX_SYSTEM
// Dz1LogicMatchType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchNumSimple
typedef struct Dz1LogicMatchNumSimple
{
	s64_t					value;
	Dz1LogicMatchType		cond;
} Dz1LogicMatchNumSimple;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchNumSimple *Dz1LogicMatchNumSimple_new(s64_t value, 
																		   Dz1LogicMatchType cond, Dz1Error *err);
static __inline__ Dz1LogicMatchNumSimple *Dz1LogicMatchNumSimple_gen(Dz1Error *err) { return Dz1LogicMatchNumSimple_new(0, Dz1LogicMatchType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1LogicMatchNumSimple_copy(Dz1LogicMatchNumSimple *dst, Dz1LogicMatchNumSimple *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchNumSimple *Dz1LogicMatchNumSimple_clone(Dz1LogicMatchNumSimple *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumSimple_purge(Dz1LogicMatchNumSimple *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumSimple_del(Dz1LogicMatchNumSimple *p);
static __inline__ void Dz1LogicMatchNumSimple_delAndSetNull(void *ptr)
{
	Dz1LogicMatchNumSimple **p = (Dz1LogicMatchNumSimple **)ptr;
	if (p) { Dz1LogicMatchNumSimple_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumSimpleA_dump(Dz1LogicMatchNumSimple *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumSimpleW_dump(Dz1LogicMatchNumSimple *p, int tab);
#ifdef UNICODE
#define Dz1LogicMatchNumSimple_dump Dz1LogicMatchNumSimpleW_dump
#else //  UNICODE
#define Dz1LogicMatchNumSimple_dump Dz1LogicMatchNumSimpleA_dump
#endif //  UNICODE
static __inline__ void Dz1LogicMatchNumSimpleX_dump(Dz1LogicMatchNumSimple *p, int tab) { DZ1_DUMP(Dz1LogicMatchNumSimple, p, tab); }
#else // UNIX_SYSTEM
#define Dz1LogicMatchNumSimple_dump Dz1LogicMatchNumSimpleA_dump
#define Dz1LogicMatchNumSimpleX_dump Dz1LogicMatchNumSimpleA_dump
#endif // UNIX_SYSTEM
// Dz1LogicMatchNumSimple
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchNumRange
typedef struct Dz1LogicMatchNumRange
{
	s64_t		LowValue;
	bool_t		LowInclude;
	s64_t		HighValue;
	bool_t		HighInclude;
} Dz1LogicMatchNumRange;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchNumRange *Dz1LogicMatchNumRange_new(s64_t LowValue, 
																		 bool_t LowInclude, 
																		 s64_t HighValue, 
																		 bool_t HighInclude, Dz1Error *err);
static __inline__ Dz1LogicMatchNumRange *Dz1LogicMatchNumRange_gen(Dz1Error *err) { return Dz1LogicMatchNumRange_new(0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1LogicMatchNumRange_copy(Dz1LogicMatchNumRange *dst, Dz1LogicMatchNumRange *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchNumRange *Dz1LogicMatchNumRange_clone(Dz1LogicMatchNumRange *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumRange_purge(Dz1LogicMatchNumRange *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumRange_del(Dz1LogicMatchNumRange *p);
static __inline__ void Dz1LogicMatchNumRange_delAndSetNull(void *ptr)
{
	Dz1LogicMatchNumRange **p = (Dz1LogicMatchNumRange **)ptr;
	if (p) { Dz1LogicMatchNumRange_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumRangeA_dump(Dz1LogicMatchNumRange *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumRangeW_dump(Dz1LogicMatchNumRange *p, int tab);
#ifdef UNICODE
#define Dz1LogicMatchNumRange_dump Dz1LogicMatchNumRangeW_dump
#else //  UNICODE
#define Dz1LogicMatchNumRange_dump Dz1LogicMatchNumRangeA_dump
#endif //  UNICODE
static __inline__ void Dz1LogicMatchNumRangeX_dump(Dz1LogicMatchNumRange *p, int tab) { DZ1_DUMP(Dz1LogicMatchNumRange, p, tab); }
#else // UNIX_SYSTEM
#define Dz1LogicMatchNumRange_dump Dz1LogicMatchNumRangeA_dump
#define Dz1LogicMatchNumRangeX_dump Dz1LogicMatchNumRangeA_dump
#endif // UNIX_SYSTEM
// Dz1LogicMatchNumRange
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchNumPresent
typedef enum Dz1LogicMatchNumPresent
{
	Dz1LogicMatchNumPresent_simple,
	Dz1LogicMatchNumPresent_range,
	Dz1LogicMatchNumPresent_max
} Dz1LogicMatchNumPresent;

DZ1_CPPLINK str_t Dz1LogicMatchNumPresentStrA(Dz1LogicMatchNumPresent v);
DZ1_CPPLINK Dz1LogicMatchNumPresent Dz1LogicMatchNumPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1LogicMatchNumPresentStrW(Dz1LogicMatchNumPresent v);
DZ1_CPPLINK Dz1LogicMatchNumPresent Dz1LogicMatchNumPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1LogicMatchNumPresentStr Dz1LogicMatchNumPresentStrW
#define Dz1LogicMatchNumPresentFromStr Dz1LogicMatchNumPresentFromStrW
#else // UNICODE
#define Dz1LogicMatchNumPresentStr Dz1LogicMatchNumPresentStrA
#define Dz1LogicMatchNumPresentFromStr Dz1LogicMatchNumPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1LogicMatchNumPresentStr Dz1LogicMatchNumPresentStrA
#define Dz1LogicMatchNumPresentFromStr Dz1LogicMatchNumPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchNumPresent *Dz1LogicMatchNumPresent_new(Dz1LogicMatchNumPresent *src, Dz1Error *err);
static __inline__ Dz1LogicMatchNumPresent *Dz1LogicMatchNumPresent_gen(Dz1Error *err) { Dz1LogicMatchNumPresent v = Dz1LogicMatchNumPresent_max; return Dz1LogicMatchNumPresent_new(&v, err); }
#define Dz1LogicMatchNumPresent_clone             Dz1LogicMatchNumPresent_new
static __inline__ void Dz1LogicMatchNumPresent_del(Dz1LogicMatchNumPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1LogicMatchNumPresent_delAndSetNull(void *ptr)
{
	Dz1LogicMatchNumPresent **p = (Dz1LogicMatchNumPresent **)ptr;
	if (p != NULL) { Dz1LogicMatchNumPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumPresentA_dump(Dz1LogicMatchNumPresent *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumPresentW_dump(Dz1LogicMatchNumPresent *v, int tab);
#ifdef UNICODE
#define Dz1LogicMatchNumPresent_dump Dz1LogicMatchNumPresentW_dump
#else //  UNICODE
#define Dz1LogicMatchNumPresent_dump Dz1LogicMatchNumPresentA_dump
#endif //  UNICODE
static __inline__ void Dz1LogicMatchNumPresentX_dump(Dz1LogicMatchNumPresent *p, int tab) { DZ1_DUMP(Dz1LogicMatchNumPresent, p, tab); }
#else // UNIX_SYSTEM
#define Dz1LogicMatchNumPresent_dump Dz1LogicMatchNumPresentA_dump
#define Dz1LogicMatchNumPresentX_dump Dz1LogicMatchNumPresentA_dump
#endif // UNIX_SYSTEM
// Dz1LogicMatchNumPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchNum
typedef struct Dz1LogicMatchNum
{
	Dz1LogicMatchNumPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1LogicMatchNumSimple		*simple;
		Dz1LogicMatchNumRange		*range;
	} x;
} Dz1LogicMatchNum;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchNum *Dz1LogicMatchNum_new(Dz1LogicMatchNumPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1LogicMatchNum *Dz1LogicMatchNum_gen(Dz1Error *err) { return Dz1LogicMatchNum_new(Dz1LogicMatchNumPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1LogicMatchNum_copy(Dz1LogicMatchNum *dst, Dz1LogicMatchNum *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchNum *Dz1LogicMatchNum_clone(Dz1LogicMatchNum *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNum_purge(Dz1LogicMatchNum *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNum_del(Dz1LogicMatchNum *p);
static __inline__ void Dz1LogicMatchNum_delAndSetNull(void *ptr)
{
	Dz1LogicMatchNum **p = (Dz1LogicMatchNum **)ptr;
	if (p != NULL) { Dz1LogicMatchNum_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumA_dump(Dz1LogicMatchNum *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchNumW_dump(Dz1LogicMatchNum *p, int tab);
#ifdef UNICODE
#define Dz1LogicMatchNum_dump Dz1LogicMatchNumW_dump
#else //  UNICODE
#define Dz1LogicMatchNum_dump Dz1LogicMatchNumA_dump
#endif //  UNICODE
static __inline__ void Dz1LogicMatchNumX_dump(Dz1LogicMatchNum *p, int tab) { DZ1_DUMP(Dz1LogicMatchNum, p, tab); }
#else // UNIX_SYSTEM
#define Dz1LogicMatchNum_dump Dz1LogicMatchNumA_dump
#define Dz1LogicMatchNumX_dump Dz1LogicMatchNumA_dump
#endif // UNIX_SYSTEM
// Dz1LogicMatchNum
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringSimpleA
typedef struct Dz1LogicMatchStringSimpleA
{
	str_t					value;
	Dz1LogicMatchType		cond;
} Dz1LogicMatchStringSimpleA;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringSimpleA *Dz1LogicMatchStringSimpleA_new(str_t value, 
																				   Dz1LogicMatchType cond, Dz1Error *err);
static __inline__ Dz1LogicMatchStringSimpleA *Dz1LogicMatchStringSimpleA_gen(Dz1Error *err) { return Dz1LogicMatchStringSimpleA_new(NULL, Dz1LogicMatchType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1LogicMatchStringSimpleA_copy(Dz1LogicMatchStringSimpleA *dst, Dz1LogicMatchStringSimpleA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringSimpleA *Dz1LogicMatchStringSimpleA_clone(Dz1LogicMatchStringSimpleA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringSimpleA_purge(Dz1LogicMatchStringSimpleA *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringSimpleA_del(Dz1LogicMatchStringSimpleA *p);
static __inline__ void Dz1LogicMatchStringSimpleA_delAndSetNull(void *ptr)
{
	Dz1LogicMatchStringSimpleA **p = (Dz1LogicMatchStringSimpleA **)ptr;
	if (p) { Dz1LogicMatchStringSimpleA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringSimpleA_dump(Dz1LogicMatchStringSimpleA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1LogicMatchStringSimpleA_cmp(Dz1LogicMatchStringSimpleA *a, Dz1LogicMatchStringSimpleA *b); 
// Dz1LogicMatchStringSimpleA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringSimpleW
typedef struct Dz1LogicMatchStringSimpleW
{
	wstr_t					value;
	Dz1LogicMatchType		cond;
} Dz1LogicMatchStringSimpleW;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringSimpleW *Dz1LogicMatchStringSimpleW_new(wstr_t value, 
																				   Dz1LogicMatchType cond, Dz1Error *err);
static __inline__ Dz1LogicMatchStringSimpleW *Dz1LogicMatchStringSimpleW_gen(Dz1Error *err) { return Dz1LogicMatchStringSimpleW_new(NULL, Dz1LogicMatchType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1LogicMatchStringSimpleW_copy(Dz1LogicMatchStringSimpleW *dst, Dz1LogicMatchStringSimpleW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringSimpleW *Dz1LogicMatchStringSimpleW_clone(Dz1LogicMatchStringSimpleW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringSimpleW_purge(Dz1LogicMatchStringSimpleW *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringSimpleW_del(Dz1LogicMatchStringSimpleW *p);
static __inline__ void Dz1LogicMatchStringSimpleW_delAndSetNull(void *ptr)
{
	Dz1LogicMatchStringSimpleW **p = (Dz1LogicMatchStringSimpleW **)ptr;
	if (p) { Dz1LogicMatchStringSimpleW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringSimpleW_dump(Dz1LogicMatchStringSimpleW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1LogicMatchStringSimpleW_cmp(Dz1LogicMatchStringSimpleW *a, Dz1LogicMatchStringSimpleW *b); 
// Dz1LogicMatchStringSimpleW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringsA
typedef struct Dz1LogicMatchStringsA
{
	Dz1LogicStringArrA		*arr;
	Dz1LogicMatchType		 cond;
} Dz1LogicMatchStringsA;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringsA *Dz1LogicMatchStringsA_new(Dz1LogicStringArrA *arr, 
																		 Dz1LogicMatchType cond, Dz1Error *err);
static __inline__ Dz1LogicMatchStringsA *Dz1LogicMatchStringsA_gen(Dz1Error *err) { return Dz1LogicMatchStringsA_new(NULL, Dz1LogicMatchType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1LogicMatchStringsA_copy(Dz1LogicMatchStringsA *dst, Dz1LogicMatchStringsA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringsA *Dz1LogicMatchStringsA_clone(Dz1LogicMatchStringsA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringsA_purge(Dz1LogicMatchStringsA *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringsA_del(Dz1LogicMatchStringsA *p);
static __inline__ void Dz1LogicMatchStringsA_delAndSetNull(void *ptr)
{
	Dz1LogicMatchStringsA **p = (Dz1LogicMatchStringsA **)ptr;
	if (p) { Dz1LogicMatchStringsA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringsA_dump(Dz1LogicMatchStringsA *p, int tab);
// Dz1LogicMatchStringsA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringsW
typedef struct Dz1LogicMatchStringsW
{
	Dz1LogicStringArrW		*arr;
	Dz1LogicMatchType		 cond;
} Dz1LogicMatchStringsW;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringsW *Dz1LogicMatchStringsW_new(Dz1LogicStringArrW *arr, 
																		 Dz1LogicMatchType cond, Dz1Error *err);
static __inline__ Dz1LogicMatchStringsW *Dz1LogicMatchStringsW_gen(Dz1Error *err) { return Dz1LogicMatchStringsW_new(NULL, Dz1LogicMatchType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1LogicMatchStringsW_copy(Dz1LogicMatchStringsW *dst, Dz1LogicMatchStringsW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringsW *Dz1LogicMatchStringsW_clone(Dz1LogicMatchStringsW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringsW_purge(Dz1LogicMatchStringsW *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringsW_del(Dz1LogicMatchStringsW *p);
static __inline__ void Dz1LogicMatchStringsW_delAndSetNull(void *ptr)
{
	Dz1LogicMatchStringsW **p = (Dz1LogicMatchStringsW **)ptr;
	if (p) { Dz1LogicMatchStringsW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringsW_dump(Dz1LogicMatchStringsW *p, int tab);
// Dz1LogicMatchStringsW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchRefStringsA
typedef struct Dz1LogicMatchRefStringsA
{
	Dz1LogicStringRefArrA		*arr;
	Dz1LogicMatchType			 cond;
} Dz1LogicMatchRefStringsA;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchRefStringsA *Dz1LogicMatchRefStringsA_new(Dz1LogicStringRefArrA *arr, 
																			   Dz1LogicMatchType cond, Dz1Error *err);
static __inline__ Dz1LogicMatchRefStringsA *Dz1LogicMatchRefStringsA_gen(Dz1Error *err) { return Dz1LogicMatchRefStringsA_new(NULL, Dz1LogicMatchType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1LogicMatchRefStringsA_copy(Dz1LogicMatchRefStringsA *dst, Dz1LogicMatchRefStringsA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchRefStringsA *Dz1LogicMatchRefStringsA_clone(Dz1LogicMatchRefStringsA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchRefStringsA_purge(Dz1LogicMatchRefStringsA *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchRefStringsA_del(Dz1LogicMatchRefStringsA *p);
static __inline__ void Dz1LogicMatchRefStringsA_delAndSetNull(void *ptr)
{
	Dz1LogicMatchRefStringsA **p = (Dz1LogicMatchRefStringsA **)ptr;
	if (p) { Dz1LogicMatchRefStringsA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchRefStringsA_dump(Dz1LogicMatchRefStringsA *p, int tab);
// Dz1LogicMatchRefStringsA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchRefStringsW
typedef struct Dz1LogicMatchRefStringsW
{
	Dz1LogicStringRefArrW		*arr;
	Dz1LogicMatchType			 cond;
} Dz1LogicMatchRefStringsW;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchRefStringsW *Dz1LogicMatchRefStringsW_new(Dz1LogicStringRefArrW *arr, 
																			   Dz1LogicMatchType cond, Dz1Error *err);
static __inline__ Dz1LogicMatchRefStringsW *Dz1LogicMatchRefStringsW_gen(Dz1Error *err) { return Dz1LogicMatchRefStringsW_new(NULL, Dz1LogicMatchType_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1LogicMatchRefStringsW_copy(Dz1LogicMatchRefStringsW *dst, Dz1LogicMatchRefStringsW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchRefStringsW *Dz1LogicMatchRefStringsW_clone(Dz1LogicMatchRefStringsW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchRefStringsW_purge(Dz1LogicMatchRefStringsW *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchRefStringsW_del(Dz1LogicMatchRefStringsW *p);
static __inline__ void Dz1LogicMatchRefStringsW_delAndSetNull(void *ptr)
{
	Dz1LogicMatchRefStringsW **p = (Dz1LogicMatchRefStringsW **)ptr;
	if (p) { Dz1LogicMatchRefStringsW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchRefStringsW_dump(Dz1LogicMatchRefStringsW *p, int tab);
// Dz1LogicMatchRefStringsW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringAPresent
typedef enum Dz1LogicMatchStringAPresent
{
	Dz1LogicMatchStringAPresent_simple,
	Dz1LogicMatchStringAPresent_complexA,
	Dz1LogicMatchStringAPresent_complexR,
	Dz1LogicMatchStringAPresent_max
} Dz1LogicMatchStringAPresent;

DZ1_CPPLINK str_t Dz1LogicMatchStringAPresentStrA(Dz1LogicMatchStringAPresent v);
DZ1_CPPLINK Dz1LogicMatchStringAPresent Dz1LogicMatchStringAPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1LogicMatchStringAPresentStrW(Dz1LogicMatchStringAPresent v);
DZ1_CPPLINK Dz1LogicMatchStringAPresent Dz1LogicMatchStringAPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1LogicMatchStringAPresentStr Dz1LogicMatchStringAPresentStrW
#define Dz1LogicMatchStringAPresentFromStr Dz1LogicMatchStringAPresentFromStrW
#else // UNICODE
#define Dz1LogicMatchStringAPresentStr Dz1LogicMatchStringAPresentStrA
#define Dz1LogicMatchStringAPresentFromStr Dz1LogicMatchStringAPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1LogicMatchStringAPresentStr Dz1LogicMatchStringAPresentStrA
#define Dz1LogicMatchStringAPresentFromStr Dz1LogicMatchStringAPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringAPresent *Dz1LogicMatchStringAPresent_new(Dz1LogicMatchStringAPresent *src, Dz1Error *err);
static __inline__ Dz1LogicMatchStringAPresent *Dz1LogicMatchStringAPresent_gen(Dz1Error *err) { Dz1LogicMatchStringAPresent v = Dz1LogicMatchStringAPresent_max; return Dz1LogicMatchStringAPresent_new(&v, err); }
#define Dz1LogicMatchStringAPresent_clone             Dz1LogicMatchStringAPresent_new
static __inline__ void Dz1LogicMatchStringAPresent_del(Dz1LogicMatchStringAPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1LogicMatchStringAPresent_delAndSetNull(void *ptr)
{
	Dz1LogicMatchStringAPresent **p = (Dz1LogicMatchStringAPresent **)ptr;
	if (p != NULL) { Dz1LogicMatchStringAPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringAPresentA_dump(Dz1LogicMatchStringAPresent *v, int tab);
// Dz1LogicMatchStringAPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringA
typedef struct Dz1LogicMatchStringA
{
	Dz1LogicMatchStringAPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1LogicMatchStringSimpleA		*simple;
		Dz1LogicMatchStringsA			*complexA;
		Dz1LogicMatchRefStringsA		*complexR;
	} x;
} Dz1LogicMatchStringA;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringA *Dz1LogicMatchStringA_new(Dz1LogicMatchStringAPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1LogicMatchStringA *Dz1LogicMatchStringA_gen(Dz1Error *err) { return Dz1LogicMatchStringA_new(Dz1LogicMatchStringAPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1LogicMatchStringA_copy(Dz1LogicMatchStringA *dst, Dz1LogicMatchStringA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringA *Dz1LogicMatchStringA_clone(Dz1LogicMatchStringA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringA_purge(Dz1LogicMatchStringA *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringA_del(Dz1LogicMatchStringA *p);
static __inline__ void Dz1LogicMatchStringA_delAndSetNull(void *ptr)
{
	Dz1LogicMatchStringA **p = (Dz1LogicMatchStringA **)ptr;
	if (p != NULL) { Dz1LogicMatchStringA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringA_dump(Dz1LogicMatchStringA *p, int tab);
// Dz1LogicMatchStringA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringWPresent
typedef enum Dz1LogicMatchStringWPresent
{
	Dz1LogicMatchStringWPresent_simple,
	Dz1LogicMatchStringWPresent_complexA,
	Dz1LogicMatchStringWPresent_complexR,
	Dz1LogicMatchStringWPresent_max
} Dz1LogicMatchStringWPresent;

DZ1_CPPLINK str_t Dz1LogicMatchStringWPresentStrA(Dz1LogicMatchStringWPresent v);
DZ1_CPPLINK Dz1LogicMatchStringWPresent Dz1LogicMatchStringWPresentFromStrA(str_t str);
DZ1_CPPLINK wstr_t Dz1LogicMatchStringWPresentStrW(Dz1LogicMatchStringWPresent v);
DZ1_CPPLINK Dz1LogicMatchStringWPresent Dz1LogicMatchStringWPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1LogicMatchStringWPresentStr Dz1LogicMatchStringWPresentStrW
#define Dz1LogicMatchStringWPresentFromStr Dz1LogicMatchStringWPresentFromStrW
#else // UNICODE
#define Dz1LogicMatchStringWPresentStr Dz1LogicMatchStringWPresentStrA
#define Dz1LogicMatchStringWPresentFromStr Dz1LogicMatchStringWPresentFromStrA
#endif // UNICODE
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringWPresent *Dz1LogicMatchStringWPresent_new(Dz1LogicMatchStringWPresent *src, Dz1Error *err);
static __inline__ Dz1LogicMatchStringWPresent *Dz1LogicMatchStringWPresent_gen(Dz1Error *err) { Dz1LogicMatchStringWPresent v = Dz1LogicMatchStringWPresent_max; return Dz1LogicMatchStringWPresent_new(&v, err); }
#define Dz1LogicMatchStringWPresent_clone             Dz1LogicMatchStringWPresent_new
static __inline__ void Dz1LogicMatchStringWPresent_del(Dz1LogicMatchStringWPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1LogicMatchStringWPresent_delAndSetNull(void *ptr)
{
	Dz1LogicMatchStringWPresent **p = (Dz1LogicMatchStringWPresent **)ptr;
	if (p != NULL) { Dz1LogicMatchStringWPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringWPresentW_dump(Dz1LogicMatchStringWPresent *v, int tab);
// Dz1LogicMatchStringWPresent
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchStringW
typedef struct Dz1LogicMatchStringW
{
	Dz1LogicMatchStringWPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1LogicMatchStringSimpleW		*simple;
		Dz1LogicMatchStringsW			*complexA;
		Dz1LogicMatchRefStringsW		*complexR;
	} x;
} Dz1LogicMatchStringW;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringW *Dz1LogicMatchStringW_new(Dz1LogicMatchStringWPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1LogicMatchStringW *Dz1LogicMatchStringW_gen(Dz1Error *err) { return Dz1LogicMatchStringW_new(Dz1LogicMatchStringWPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1LogicMatchStringW_copy(Dz1LogicMatchStringW *dst, Dz1LogicMatchStringW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchStringW *Dz1LogicMatchStringW_clone(Dz1LogicMatchStringW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringW_purge(Dz1LogicMatchStringW *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringW_del(Dz1LogicMatchStringW *p);
static __inline__ void Dz1LogicMatchStringW_delAndSetNull(void *ptr)
{
	Dz1LogicMatchStringW **p = (Dz1LogicMatchStringW **)ptr;
	if (p != NULL) { Dz1LogicMatchStringW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchStringW_dump(Dz1LogicMatchStringW *p, int tab);
// Dz1LogicMatchStringW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchAPresent
typedef enum Dz1LogicMatchAPresent
{
	Dz1LogicMatchAPresent_number,
	Dz1LogicMatchAPresent_text,
	Dz1LogicMatchAPresent_max
} Dz1LogicMatchAPresent;

DZ1_CPPLINK str_t Dz1LogicMatchAPresentStrA(Dz1LogicMatchAPresent v);
DZ1_CPPLINK Dz1LogicMatchAPresent Dz1LogicMatchAPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1LogicMatchAPresentStrW(Dz1LogicMatchAPresent v);
DZ1_CPPLINK Dz1LogicMatchAPresent Dz1LogicMatchAPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1LogicMatchAPresentStr Dz1LogicMatchAPresentStrW
#define Dz1LogicMatchAPresentFromStr Dz1LogicMatchAPresentFromStrW
#else // UNICODE
#define Dz1LogicMatchAPresentStr Dz1LogicMatchAPresentStrA
#define Dz1LogicMatchAPresentFromStr Dz1LogicMatchAPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1LogicMatchAPresentStr Dz1LogicMatchAPresentStrA
#define Dz1LogicMatchAPresentFromStr Dz1LogicMatchAPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchAPresent *Dz1LogicMatchAPresent_new(Dz1LogicMatchAPresent *src, Dz1Error *err);
static __inline__ Dz1LogicMatchAPresent *Dz1LogicMatchAPresent_gen(Dz1Error *err) { Dz1LogicMatchAPresent v = Dz1LogicMatchAPresent_max; return Dz1LogicMatchAPresent_new(&v, err); }
#define Dz1LogicMatchAPresent_clone             Dz1LogicMatchAPresent_new
static __inline__ void Dz1LogicMatchAPresent_del(Dz1LogicMatchAPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1LogicMatchAPresent_delAndSetNull(void *ptr)
{
	Dz1LogicMatchAPresent **p = (Dz1LogicMatchAPresent **)ptr;
	if (p != NULL) { Dz1LogicMatchAPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchAPresentA_dump(Dz1LogicMatchAPresent *v, int tab);
// Dz1LogicMatchAPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchA
typedef struct Dz1LogicMatchA
{
	Dz1LogicMatchAPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1LogicMatchNum		*number;
		Dz1LogicMatchStringA	*text;
	} x;
} Dz1LogicMatchA;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchA *Dz1LogicMatchA_new(Dz1LogicMatchAPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1LogicMatchA *Dz1LogicMatchA_gen(Dz1Error *err) { return Dz1LogicMatchA_new(Dz1LogicMatchAPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1LogicMatchA_copy(Dz1LogicMatchA *dst, Dz1LogicMatchA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchA *Dz1LogicMatchA_clone(Dz1LogicMatchA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchA_purge(Dz1LogicMatchA *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchA_del(Dz1LogicMatchA *p);
static __inline__ void Dz1LogicMatchA_delAndSetNull(void *ptr)
{
	Dz1LogicMatchA **p = (Dz1LogicMatchA **)ptr;
	if (p != NULL) { Dz1LogicMatchA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchA_dump(Dz1LogicMatchA *p, int tab);
// Dz1LogicMatchA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchWPresent
typedef enum Dz1LogicMatchWPresent
{
	Dz1LogicMatchWPresent_number,
	Dz1LogicMatchWPresent_text,
	Dz1LogicMatchWPresent_max
} Dz1LogicMatchWPresent;

DZ1_CPPLINK str_t Dz1LogicMatchWPresentStrA(Dz1LogicMatchWPresent v);
DZ1_CPPLINK Dz1LogicMatchWPresent Dz1LogicMatchWPresentFromStrA(str_t str);
DZ1_CPPLINK wstr_t Dz1LogicMatchWPresentStrW(Dz1LogicMatchWPresent v);
DZ1_CPPLINK Dz1LogicMatchWPresent Dz1LogicMatchWPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1LogicMatchWPresentStr Dz1LogicMatchWPresentStrW
#define Dz1LogicMatchWPresentFromStr Dz1LogicMatchWPresentFromStrW
#else // UNICODE
#define Dz1LogicMatchWPresentStr Dz1LogicMatchWPresentStrA
#define Dz1LogicMatchWPresentFromStr Dz1LogicMatchWPresentFromStrA
#endif // UNICODE
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchWPresent *Dz1LogicMatchWPresent_new(Dz1LogicMatchWPresent *src, Dz1Error *err);
static __inline__ Dz1LogicMatchWPresent *Dz1LogicMatchWPresent_gen(Dz1Error *err) { Dz1LogicMatchWPresent v = Dz1LogicMatchWPresent_max; return Dz1LogicMatchWPresent_new(&v, err); }
#define Dz1LogicMatchWPresent_clone             Dz1LogicMatchWPresent_new
static __inline__ void Dz1LogicMatchWPresent_del(Dz1LogicMatchWPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1LogicMatchWPresent_delAndSetNull(void *ptr)
{
	Dz1LogicMatchWPresent **p = (Dz1LogicMatchWPresent **)ptr;
	if (p != NULL) { Dz1LogicMatchWPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchWPresentW_dump(Dz1LogicMatchWPresent *v, int tab);
// Dz1LogicMatchWPresent
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchW
typedef struct Dz1LogicMatchW
{
	Dz1LogicMatchWPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1LogicMatchNum		*number;
		Dz1LogicMatchStringW	*text;
	} x;
} Dz1LogicMatchW;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchW *Dz1LogicMatchW_new(Dz1LogicMatchWPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1LogicMatchW *Dz1LogicMatchW_gen(Dz1Error *err) { return Dz1LogicMatchW_new(Dz1LogicMatchWPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1LogicMatchW_copy(Dz1LogicMatchW *dst, Dz1LogicMatchW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchW *Dz1LogicMatchW_clone(Dz1LogicMatchW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchW_purge(Dz1LogicMatchW *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchW_del(Dz1LogicMatchW *p);
static __inline__ void Dz1LogicMatchW_delAndSetNull(void *ptr)
{
	Dz1LogicMatchW **p = (Dz1LogicMatchW **)ptr;
	if (p != NULL) { Dz1LogicMatchW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchW_dump(Dz1LogicMatchW *p, int tab);
// Dz1LogicMatchW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchListA
typedef struct Dz1LogicMatchListA
{
	void *storage;
	unsigned int (*count)(struct Dz1LogicMatchListA *p);
	Dz1Error (*travel)(struct Dz1LogicMatchListA *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchA *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1LogicMatchListA *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1LogicMatchListA *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchA *entry), void *ptr);
	Dz1LogicMatchA **(*get_array)(struct Dz1LogicMatchListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1LogicMatchListA *p, Dz1LogicMatchA *data);
} Dz1LogicMatchListA;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchListA *Dz1LogicMatchListA_new(Dz1Error *err);
static __inline__ Dz1LogicMatchListA *Dz1LogicMatchListA_gen(Dz1Error *err) { return Dz1LogicMatchListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchListA *Dz1LogicMatchListA_clone(Dz1LogicMatchListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchListA_purge(Dz1LogicMatchListA *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchListA_del(Dz1LogicMatchListA *p);
static __inline__ void Dz1LogicMatchListA_delAndSetNull(void *ptr)
{
	Dz1LogicMatchListA **p = (Dz1LogicMatchListA **)ptr;
	if (p != NULL) { Dz1LogicMatchListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchListA_dump(Dz1LogicMatchListA *p, int tab);

// Dz1LogicMatchListA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchListW
typedef struct Dz1LogicMatchListW
{
	void *storage;
	unsigned int (*count)(struct Dz1LogicMatchListW *p);
	Dz1Error (*travel)(struct Dz1LogicMatchListW *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchW *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1LogicMatchListW *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1LogicMatchListW *p, Dz1Error (*func)(void *ptr, Dz1LogicMatchW *entry), void *ptr);
	Dz1LogicMatchW **(*get_array)(struct Dz1LogicMatchListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1LogicMatchListW *p, Dz1LogicMatchW *data);
} Dz1LogicMatchListW;

DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchListW *Dz1LogicMatchListW_new(Dz1Error *err);
static __inline__ Dz1LogicMatchListW *Dz1LogicMatchListW_gen(Dz1Error *err) { return Dz1LogicMatchListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchListW *Dz1LogicMatchListW_clone(Dz1LogicMatchListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchListW_purge(Dz1LogicMatchListW *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchListW_del(Dz1LogicMatchListW *p);
static __inline__ void Dz1LogicMatchListW_delAndSetNull(void *ptr)
{
	Dz1LogicMatchListW **p = (Dz1LogicMatchListW **)ptr;
	if (p != NULL) { Dz1LogicMatchListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchListW_dump(Dz1LogicMatchListW *p, int tab);

// Dz1LogicMatchListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Dz1LogicMatchValueType
typedef enum Dz1LogicMatchValueType
{
	Dz1LogicMatchValueType_Signed8,
	Dz1LogicMatchValueType_Signed16,
	Dz1LogicMatchValueType_Signed32,
	Dz1LogicMatchValueType_Signed64,
	Dz1LogicMatchValueType_Unsigned8,
	Dz1LogicMatchValueType_Unsigned16,
	Dz1LogicMatchValueType_Unsigned32,
	Dz1LogicMatchValueType_Unsigned64,
	Dz1LogicMatchValueType_String,
	Dz1LogicMatchValueType_max
} Dz1LogicMatchValueType;

DZ1_CPPLINK str_t Dz1LogicMatchValueTypeStrA(Dz1LogicMatchValueType v);
DZ1_CPPLINK Dz1LogicMatchValueType Dz1LogicMatchValueTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1LogicMatchValueTypeStrW(Dz1LogicMatchValueType v);
DZ1_CPPLINK Dz1LogicMatchValueType Dz1LogicMatchValueTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1LogicMatchValueTypeStr Dz1LogicMatchValueTypeStrW
#define Dz1LogicMatchValueTypeFromStr Dz1LogicMatchValueTypeFromStrW
#else // UNICODE
#define Dz1LogicMatchValueTypeStr Dz1LogicMatchValueTypeStrA
#define Dz1LogicMatchValueTypeFromStr Dz1LogicMatchValueTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1LogicMatchValueTypeStr Dz1LogicMatchValueTypeStrA
#define Dz1LogicMatchValueTypeFromStr Dz1LogicMatchValueTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1LogicMatchValueType *Dz1LogicMatchValueType_new(Dz1LogicMatchValueType *src, Dz1Error *err);
static __inline__ Dz1LogicMatchValueType *Dz1LogicMatchValueType_gen(Dz1Error *err) { Dz1LogicMatchValueType v = Dz1LogicMatchValueType_max; return Dz1LogicMatchValueType_new(&v, err); }
static __inline__ void Dz1LogicMatchValueType_del(Dz1LogicMatchValueType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1LogicMatchValueType_delAndSetNull(void *ptr)
{
	Dz1LogicMatchValueType **p = (Dz1LogicMatchValueType **)ptr;
	if (p != NULL) { Dz1LogicMatchValueType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchValueTypeA_dump(Dz1LogicMatchValueType *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1LogicMatchValueTypeW_dump(Dz1LogicMatchValueType *v, int tab);
#ifdef UNICODE
#define Dz1LogicMatchValueType_dump Dz1LogicMatchValueTypeW_dump
#else //  UNICODE
#define Dz1LogicMatchValueType_dump Dz1LogicMatchValueTypeA_dump
#endif //  UNICODE
static __inline__ void Dz1LogicMatchValueTypeX_dump(Dz1LogicMatchValueType *p, int tab) { DZ1_DUMP(Dz1LogicMatchValueType, p, tab); }
#else // UNIX_SYSTEM
#define Dz1LogicMatchValueType_dump Dz1LogicMatchValueTypeA_dump
#define Dz1LogicMatchValueTypeX_dump Dz1LogicMatchValueTypeA_dump
#endif // UNIX_SYSTEM
// Dz1LogicMatchValueType
////////////////////////////////////////////////////////////////////////////////

#endif
