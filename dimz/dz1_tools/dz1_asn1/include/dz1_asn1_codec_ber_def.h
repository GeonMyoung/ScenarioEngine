#ifndef _DZ1_TDC_DZ1_ASN1_CODEC_BER_DEF_H_
#define _DZ1_TDC_DZ1_ASN1_CODEC_BER_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"
#include "dz1_asn1_types_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescr
struct Dz1Asn1TypeDescr;
// Dz1Asn1TypeDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescrChild
struct Dz1Asn1TypeDescrChild;
// Dz1Asn1TypeDescrChild
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderTagState
typedef enum Dz1Asn1BerDecoderTagState
{
	Dz1Asn1BerDecoderTagState_first_byte,
	Dz1Asn1BerDecoderTagState_tag_nums,
	Dz1Asn1BerDecoderTagState_max
} Dz1Asn1BerDecoderTagState;

DZ1_CPPLINK str_t Dz1Asn1BerDecoderTagStateStrA(Dz1Asn1BerDecoderTagState v);
DZ1_CPPLINK Dz1Asn1BerDecoderTagState Dz1Asn1BerDecoderTagStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1BerDecoderTagStateStrW(Dz1Asn1BerDecoderTagState v);
DZ1_CPPLINK Dz1Asn1BerDecoderTagState Dz1Asn1BerDecoderTagStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1BerDecoderTagStateStr Dz1Asn1BerDecoderTagStateStrW
#define Dz1Asn1BerDecoderTagStateFromStr Dz1Asn1BerDecoderTagStateFromStrW
#else // UNICODE
#define Dz1Asn1BerDecoderTagStateStr Dz1Asn1BerDecoderTagStateStrA
#define Dz1Asn1BerDecoderTagStateFromStr Dz1Asn1BerDecoderTagStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1BerDecoderTagStateStr Dz1Asn1BerDecoderTagStateStrA
#define Dz1Asn1BerDecoderTagStateFromStr Dz1Asn1BerDecoderTagStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderTagState *Dz1Asn1BerDecoderTagState_new(Dz1Asn1BerDecoderTagState *src, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderTagState *Dz1Asn1BerDecoderTagState_gen(Dz1Error *err) { Dz1Asn1BerDecoderTagState v = Dz1Asn1BerDecoderTagState_max; return Dz1Asn1BerDecoderTagState_new(&v, err); }
static __inline__ void Dz1Asn1BerDecoderTagState_del(Dz1Asn1BerDecoderTagState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1BerDecoderTagState_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderTagState **p = (Dz1Asn1BerDecoderTagState **)ptr;
	if (p != NULL) { Dz1Asn1BerDecoderTagState_del(*p); *p = NULL; }
}
// Dz1Asn1BerDecoderTagState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderTagCtx
typedef struct Dz1Asn1BerDecoderTagCtx
{
	Dz1Asn1BerDecoderTagState		 state;
	Dz1Asn1Tag						*wip;
} Dz1Asn1BerDecoderTagCtx;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderTagCtx *Dz1Asn1BerDecoderTagCtx_new(Dz1Asn1BerDecoderTagState state, 
																			 Dz1Asn1Tag *wip, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderTagCtx *Dz1Asn1BerDecoderTagCtx_gen(Dz1Error *err) { return Dz1Asn1BerDecoderTagCtx_new(Dz1Asn1BerDecoderTagState_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderTagCtx_purge(Dz1Asn1BerDecoderTagCtx *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderTagCtx_del(Dz1Asn1BerDecoderTagCtx *p);
static __inline__ void Dz1Asn1BerDecoderTagCtx_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderTagCtx **p = (Dz1Asn1BerDecoderTagCtx **)ptr;
	if (p) { Dz1Asn1BerDecoderTagCtx_del(*p); *p = NULL; }
}
// Dz1Asn1BerDecoderTagCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderLengthState
typedef enum Dz1Asn1BerDecoderLengthState
{
	Dz1Asn1BerDecoderLengthState_initial,
	Dz1Asn1BerDecoderLengthState_data_wait,
	Dz1Asn1BerDecoderLengthState_max
} Dz1Asn1BerDecoderLengthState;

DZ1_CPPLINK str_t Dz1Asn1BerDecoderLengthStateStrA(Dz1Asn1BerDecoderLengthState v);
DZ1_CPPLINK Dz1Asn1BerDecoderLengthState Dz1Asn1BerDecoderLengthStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1BerDecoderLengthStateStrW(Dz1Asn1BerDecoderLengthState v);
DZ1_CPPLINK Dz1Asn1BerDecoderLengthState Dz1Asn1BerDecoderLengthStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1BerDecoderLengthStateStr Dz1Asn1BerDecoderLengthStateStrW
#define Dz1Asn1BerDecoderLengthStateFromStr Dz1Asn1BerDecoderLengthStateFromStrW
#else // UNICODE
#define Dz1Asn1BerDecoderLengthStateStr Dz1Asn1BerDecoderLengthStateStrA
#define Dz1Asn1BerDecoderLengthStateFromStr Dz1Asn1BerDecoderLengthStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1BerDecoderLengthStateStr Dz1Asn1BerDecoderLengthStateStrA
#define Dz1Asn1BerDecoderLengthStateFromStr Dz1Asn1BerDecoderLengthStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderLengthState *Dz1Asn1BerDecoderLengthState_new(Dz1Asn1BerDecoderLengthState *src, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderLengthState *Dz1Asn1BerDecoderLengthState_gen(Dz1Error *err) { Dz1Asn1BerDecoderLengthState v = Dz1Asn1BerDecoderLengthState_max; return Dz1Asn1BerDecoderLengthState_new(&v, err); }
static __inline__ void Dz1Asn1BerDecoderLengthState_del(Dz1Asn1BerDecoderLengthState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1BerDecoderLengthState_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderLengthState **p = (Dz1Asn1BerDecoderLengthState **)ptr;
	if (p != NULL) { Dz1Asn1BerDecoderLengthState_del(*p); *p = NULL; }
}
// Dz1Asn1BerDecoderLengthState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderLengthCtx
typedef struct Dz1Asn1BerDecoderLengthCtx
{
	Dz1Asn1BerDecoderLengthState	state;
	size_t							remain_bytes;
	u64_t							wip;
} Dz1Asn1BerDecoderLengthCtx;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderLengthCtx *Dz1Asn1BerDecoderLengthCtx_new(Dz1Asn1BerDecoderLengthState state, 
																				   size_t remain_bytes, 
																				   u64_t wip, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderLengthCtx *Dz1Asn1BerDecoderLengthCtx_gen(Dz1Error *err) { return Dz1Asn1BerDecoderLengthCtx_new(Dz1Asn1BerDecoderLengthState_max, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderLengthCtx_purge(Dz1Asn1BerDecoderLengthCtx *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderLengthCtx_del(Dz1Asn1BerDecoderLengthCtx *p);
static __inline__ void Dz1Asn1BerDecoderLengthCtx_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderLengthCtx **p = (Dz1Asn1BerDecoderLengthCtx **)ptr;
	if (p) { Dz1Asn1BerDecoderLengthCtx_del(*p); *p = NULL; }
}
// Dz1Asn1BerDecoderLengthCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderDataState
typedef enum Dz1Asn1BerDecoderDataState
{
	Dz1Asn1BerDecoderDataState_initial,
	Dz1Asn1BerDecoderDataState_data_wait,
	Dz1Asn1BerDecoderDataState_nested,
	Dz1Asn1BerDecoderDataState_max
} Dz1Asn1BerDecoderDataState;

DZ1_CPPLINK str_t Dz1Asn1BerDecoderDataStateStrA(Dz1Asn1BerDecoderDataState v);
DZ1_CPPLINK Dz1Asn1BerDecoderDataState Dz1Asn1BerDecoderDataStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1BerDecoderDataStateStrW(Dz1Asn1BerDecoderDataState v);
DZ1_CPPLINK Dz1Asn1BerDecoderDataState Dz1Asn1BerDecoderDataStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1BerDecoderDataStateStr Dz1Asn1BerDecoderDataStateStrW
#define Dz1Asn1BerDecoderDataStateFromStr Dz1Asn1BerDecoderDataStateFromStrW
#else // UNICODE
#define Dz1Asn1BerDecoderDataStateStr Dz1Asn1BerDecoderDataStateStrA
#define Dz1Asn1BerDecoderDataStateFromStr Dz1Asn1BerDecoderDataStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1BerDecoderDataStateStr Dz1Asn1BerDecoderDataStateStrA
#define Dz1Asn1BerDecoderDataStateFromStr Dz1Asn1BerDecoderDataStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderDataState *Dz1Asn1BerDecoderDataState_new(Dz1Asn1BerDecoderDataState *src, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderDataState *Dz1Asn1BerDecoderDataState_gen(Dz1Error *err) { Dz1Asn1BerDecoderDataState v = Dz1Asn1BerDecoderDataState_max; return Dz1Asn1BerDecoderDataState_new(&v, err); }
static __inline__ void Dz1Asn1BerDecoderDataState_del(Dz1Asn1BerDecoderDataState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1BerDecoderDataState_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderDataState **p = (Dz1Asn1BerDecoderDataState **)ptr;
	if (p != NULL) { Dz1Asn1BerDecoderDataState_del(*p); *p = NULL; }
}
// Dz1Asn1BerDecoderDataState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderDataCtx
typedef struct Dz1Asn1BerDecoderDataCtx
{
	Dz1Asn1BerDecoderDataState		 state;
	u64_t							 u64data;
	u32_t							 u32data;
	s32_t							 s32data;
	u8_t							 u8data;
	s32_t							 idx;
	Dz1Asn1WipValue					*wip;
} Dz1Asn1BerDecoderDataCtx;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderDataCtx *Dz1Asn1BerDecoderDataCtx_new(Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderDataCtx *Dz1Asn1BerDecoderDataCtx_gen(Dz1Error *err) { return Dz1Asn1BerDecoderDataCtx_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderDataCtx_purge(Dz1Asn1BerDecoderDataCtx *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderDataCtx_del(Dz1Asn1BerDecoderDataCtx *p);
static __inline__ void Dz1Asn1BerDecoderDataCtx_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderDataCtx **p = (Dz1Asn1BerDecoderDataCtx **)ptr;
	if (p) { Dz1Asn1BerDecoderDataCtx_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderDataCtxA_dump(Dz1Asn1BerDecoderDataCtx *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderDataCtxW_dump(Dz1Asn1BerDecoderDataCtx *p, int tab);
#ifdef UNICODE
#define Dz1Asn1BerDecoderDataCtx_dump Dz1Asn1BerDecoderDataCtxW_dump
#else //  UNICODE
#define Dz1Asn1BerDecoderDataCtx_dump Dz1Asn1BerDecoderDataCtxA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1BerDecoderDataCtxX_dump(Dz1Asn1BerDecoderDataCtx *p, int tab) { DZ1_DUMP(Dz1Asn1BerDecoderDataCtx, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1BerDecoderDataCtx_dump Dz1Asn1BerDecoderDataCtxA_dump
#define Dz1Asn1BerDecoderDataCtxX_dump Dz1Asn1BerDecoderDataCtxA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1BerDecoderDataCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderCtxPresent
typedef enum Dz1Asn1BerDecoderCtxPresent
{
	Dz1Asn1BerDecoderCtxPresent_tag,
	Dz1Asn1BerDecoderCtxPresent_len,
	Dz1Asn1BerDecoderCtxPresent_data,
	Dz1Asn1BerDecoderCtxPresent_max
} Dz1Asn1BerDecoderCtxPresent;

DZ1_CPPLINK str_t Dz1Asn1BerDecoderCtxPresentStrA(Dz1Asn1BerDecoderCtxPresent v);
DZ1_CPPLINK Dz1Asn1BerDecoderCtxPresent Dz1Asn1BerDecoderCtxPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1BerDecoderCtxPresentStrW(Dz1Asn1BerDecoderCtxPresent v);
DZ1_CPPLINK Dz1Asn1BerDecoderCtxPresent Dz1Asn1BerDecoderCtxPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1BerDecoderCtxPresentStr Dz1Asn1BerDecoderCtxPresentStrW
#define Dz1Asn1BerDecoderCtxPresentFromStr Dz1Asn1BerDecoderCtxPresentFromStrW
#else // UNICODE
#define Dz1Asn1BerDecoderCtxPresentStr Dz1Asn1BerDecoderCtxPresentStrA
#define Dz1Asn1BerDecoderCtxPresentFromStr Dz1Asn1BerDecoderCtxPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1BerDecoderCtxPresentStr Dz1Asn1BerDecoderCtxPresentStrA
#define Dz1Asn1BerDecoderCtxPresentFromStr Dz1Asn1BerDecoderCtxPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderCtxPresent *Dz1Asn1BerDecoderCtxPresent_new(Dz1Asn1BerDecoderCtxPresent *src, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderCtxPresent *Dz1Asn1BerDecoderCtxPresent_gen(Dz1Error *err) { Dz1Asn1BerDecoderCtxPresent v = Dz1Asn1BerDecoderCtxPresent_max; return Dz1Asn1BerDecoderCtxPresent_new(&v, err); }
static __inline__ void Dz1Asn1BerDecoderCtxPresent_del(Dz1Asn1BerDecoderCtxPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1BerDecoderCtxPresent_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderCtxPresent **p = (Dz1Asn1BerDecoderCtxPresent **)ptr;
	if (p != NULL) { Dz1Asn1BerDecoderCtxPresent_del(*p); *p = NULL; }
}
// Dz1Asn1BerDecoderCtxPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderCtx
typedef struct Dz1Asn1BerDecoderCtx
{
	Dz1Asn1BerDecoderCtxPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1BerDecoderTagCtx			*tag;
		Dz1Asn1BerDecoderLengthCtx		*len;
		Dz1Asn1BerDecoderDataCtx		*data;
	} x;
} Dz1Asn1BerDecoderCtx;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderCtx *Dz1Asn1BerDecoderCtx_new(Dz1Asn1BerDecoderCtxPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderCtx *Dz1Asn1BerDecoderCtx_gen(Dz1Error *err) { return Dz1Asn1BerDecoderCtx_new(Dz1Asn1BerDecoderCtxPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderCtx_purge(Dz1Asn1BerDecoderCtx *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderCtx_del(Dz1Asn1BerDecoderCtx *p);
static __inline__ void Dz1Asn1BerDecoderCtx_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderCtx **p = (Dz1Asn1BerDecoderCtx **)ptr;
	if (p != NULL) { Dz1Asn1BerDecoderCtx_del(*p); *p = NULL; }
}
// Dz1Asn1BerDecoderCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoderStk
struct Dz1Asn1BerDecoderStk;
struct Dz1Asn1TypeDescr;
struct Dz1Asn1TypeDescrChild;
struct Dz1Asn1BerDecoderStk;

typedef struct Dz1Asn1BerDecoderStk
{
	struct Dz1Asn1BerDecoderStk		*next;
	struct Dz1Asn1TypeDescr			*descr;
	Dz1Asn1TagOpt					 tag_opt;
	struct Dz1Asn1TypeDescrChild	*child;
	Dz1Asn1BerDecoderCtx			*ctx;
	Dz1Asn1Tag						*tag;
	u64_t							 len;
	Dz1Asn1WipValue					*data;
	u32_t							 consumed;
	struct Dz1Asn1BerDecoderStk		*ret_stk;
	s32_t							 tab;
} Dz1Asn1BerDecoderStk;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoderStk *Dz1Asn1BerDecoderStk_new(struct Dz1Asn1TypeDescr *descr_ref, 
																	   Dz1Asn1TagOpt tag_opt, 
																	   s32_t tab, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoderStk *Dz1Asn1BerDecoderStk_gen(Dz1Error *err) { return Dz1Asn1BerDecoderStk_new(NULL, Dz1Asn1TagOpt_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderStk_purge(Dz1Asn1BerDecoderStk *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderStk_del(Dz1Asn1BerDecoderStk *p);
static __inline__ void Dz1Asn1BerDecoderStk_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoderStk **p = (Dz1Asn1BerDecoderStk **)ptr;
	if (p) { Dz1Asn1BerDecoderStk_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderStkA_dump(Dz1Asn1BerDecoderStk *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoderStkW_dump(Dz1Asn1BerDecoderStk *p, int tab);
#ifdef UNICODE
#define Dz1Asn1BerDecoderStk_dump Dz1Asn1BerDecoderStkW_dump
#else //  UNICODE
#define Dz1Asn1BerDecoderStk_dump Dz1Asn1BerDecoderStkA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1BerDecoderStkX_dump(Dz1Asn1BerDecoderStk *p, int tab) { DZ1_DUMP(Dz1Asn1BerDecoderStk, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1BerDecoderStk_dump Dz1Asn1BerDecoderStkA_dump
#define Dz1Asn1BerDecoderStkX_dump Dz1Asn1BerDecoderStkA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1BerDecoderStk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerDecoder
struct Dz1Asn1TypeDescr;

typedef struct Dz1Asn1BerDecoder
{
	struct Dz1Asn1TypeDescr		*target;
	Dz1Asn1BerDecoderStk		*stk;
	Dz1Asn1WipValue				*ret;
} Dz1Asn1BerDecoder;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerDecoder *Dz1Asn1BerDecoder_new(struct Dz1Asn1TypeDescr *target_ref, 
																 Dz1Asn1BerDecoderStk *stk, Dz1Error *err);
static __inline__ Dz1Asn1BerDecoder *Dz1Asn1BerDecoder_gen(Dz1Error *err) { return Dz1Asn1BerDecoder_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoder_purge(Dz1Asn1BerDecoder *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerDecoder_del(Dz1Asn1BerDecoder *p);
static __inline__ void Dz1Asn1BerDecoder_delAndSetNull(void *ptr)
{
	Dz1Asn1BerDecoder **p = (Dz1Asn1BerDecoder **)ptr;
	if (p) { Dz1Asn1BerDecoder_del(*p); *p = NULL; }
}
// Dz1Asn1BerDecoder
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1DataBerDecF
typedef ssize_t (*Dz1Asn1DataBerDecF)(
					Dz1Asn1BerDecoderDataCtx *dst, 
					Dz1Asn1Stream *src, 
					Dz1Asn1BerDecoderStk *stk, 
					Dz1Asn1BerDecoder *decoder, 
					Dz1Error *err);
// Dz1Asn1DataBerDecF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerEncoderOpt
typedef enum Dz1Asn1BerEncoderOpt
{
	Dz1Asn1BerEncoderOpt_cer,
	Dz1Asn1BerEncoderOpt_der,
	Dz1Asn1BerEncoderOpt_max
} Dz1Asn1BerEncoderOpt;

DZ1_CPPLINK str_t Dz1Asn1BerEncoderOptStrA(Dz1Asn1BerEncoderOpt v);
DZ1_CPPLINK Dz1Asn1BerEncoderOpt Dz1Asn1BerEncoderOptFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1BerEncoderOptStrW(Dz1Asn1BerEncoderOpt v);
DZ1_CPPLINK Dz1Asn1BerEncoderOpt Dz1Asn1BerEncoderOptFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1BerEncoderOptStr Dz1Asn1BerEncoderOptStrW
#define Dz1Asn1BerEncoderOptFromStr Dz1Asn1BerEncoderOptFromStrW
#else // UNICODE
#define Dz1Asn1BerEncoderOptStr Dz1Asn1BerEncoderOptStrA
#define Dz1Asn1BerEncoderOptFromStr Dz1Asn1BerEncoderOptFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1BerEncoderOptStr Dz1Asn1BerEncoderOptStrA
#define Dz1Asn1BerEncoderOptFromStr Dz1Asn1BerEncoderOptFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerEncoderOpt *Dz1Asn1BerEncoderOpt_new(Dz1Asn1BerEncoderOpt *src, Dz1Error *err);
static __inline__ Dz1Asn1BerEncoderOpt *Dz1Asn1BerEncoderOpt_gen(Dz1Error *err) { Dz1Asn1BerEncoderOpt v = Dz1Asn1BerEncoderOpt_max; return Dz1Asn1BerEncoderOpt_new(&v, err); }
static __inline__ void Dz1Asn1BerEncoderOpt_del(Dz1Asn1BerEncoderOpt *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1BerEncoderOpt_delAndSetNull(void *ptr)
{
	Dz1Asn1BerEncoderOpt **p = (Dz1Asn1BerEncoderOpt **)ptr;
	if (p != NULL) { Dz1Asn1BerEncoderOpt_del(*p); *p = NULL; }
}
// Dz1Asn1BerEncoderOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerEncoderStk
struct Dz1Asn1BerEncoderStk;
struct Dz1Asn1TypeDescr;
struct Dz1Asn1BerEncoderStk;

typedef struct Dz1Asn1BerEncoderStk
{
	struct Dz1Asn1BerEncoderStk		*next;
	struct Dz1Asn1TypeDescr			*descr;
	Dz1Asn1TagOpt					 tag_opt;
	Dz1Asn1BerEncoderOpt			 codec_opt;
	Dz1ElasticBuf					*elb;
	bool_t							 is_constructed;
	struct Dz1Asn1BerEncoderStk		*ret_stk;
} Dz1Asn1BerEncoderStk;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerEncoderStk *Dz1Asn1BerEncoderStk_new(struct Dz1Asn1TypeDescr *descr_ref, 
																	   Dz1Asn1TagOpt tag_opt, 
																	   Dz1Asn1BerEncoderOpt codec_opt, 
																	   Dz1ElasticBuf *elb, Dz1Error *err);
static __inline__ Dz1Asn1BerEncoderStk *Dz1Asn1BerEncoderStk_gen(Dz1Error *err) { return Dz1Asn1BerEncoderStk_new(NULL, Dz1Asn1TagOpt_max, Dz1Asn1BerEncoderOpt_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerEncoderStk_purge(Dz1Asn1BerEncoderStk *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerEncoderStk_del(Dz1Asn1BerEncoderStk *p);
static __inline__ void Dz1Asn1BerEncoderStk_delAndSetNull(void *ptr)
{
	Dz1Asn1BerEncoderStk **p = (Dz1Asn1BerEncoderStk **)ptr;
	if (p) { Dz1Asn1BerEncoderStk_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerEncoderStkA_dump(Dz1Asn1BerEncoderStk *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerEncoderStkW_dump(Dz1Asn1BerEncoderStk *p, int tab);
#ifdef UNICODE
#define Dz1Asn1BerEncoderStk_dump Dz1Asn1BerEncoderStkW_dump
#else //  UNICODE
#define Dz1Asn1BerEncoderStk_dump Dz1Asn1BerEncoderStkA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1BerEncoderStkX_dump(Dz1Asn1BerEncoderStk *p, int tab) { DZ1_DUMP(Dz1Asn1BerEncoderStk, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1BerEncoderStk_dump Dz1Asn1BerEncoderStkA_dump
#define Dz1Asn1BerEncoderStkX_dump Dz1Asn1BerEncoderStkA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1BerEncoderStk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BerEncoderArg
typedef struct Dz1Asn1BerEncoderArg
{
	Dz1Asn1BerEncoderOpt	opt;
} Dz1Asn1BerEncoderArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BerEncoderArg *Dz1Asn1BerEncoderArg_new(Dz1Asn1BerEncoderOpt opt, Dz1Error *err);
static __inline__ Dz1Asn1BerEncoderArg *Dz1Asn1BerEncoderArg_gen(Dz1Error *err) { return Dz1Asn1BerEncoderArg_new(Dz1Asn1BerEncoderOpt_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerEncoderArg_purge(Dz1Asn1BerEncoderArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1BerEncoderArg_del(Dz1Asn1BerEncoderArg *p);
static __inline__ void Dz1Asn1BerEncoderArg_delAndSetNull(void *ptr)
{
	Dz1Asn1BerEncoderArg **p = (Dz1Asn1BerEncoderArg **)ptr;
	if (p) { Dz1Asn1BerEncoderArg_del(*p); *p = NULL; }
}
// Dz1Asn1BerEncoderArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1DataBerEncF
typedef bool_t (*Dz1Asn1DataBerEncF)(
					Dz1ElasticBuf *dst, 
					struct Dz1Asn1TypeDescr *descr, 
					void *src, 
					bool_t *ret_is_constructed_form, 
					Dz1Asn1BerEncoderArg *enc_arg, 
					Dz1Error *err);
// Dz1Asn1DataBerEncF
////////////////////////////////////////////////////////////////////////////////

#endif
