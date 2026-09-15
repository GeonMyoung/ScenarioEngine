#ifndef _DZ1_TDC_DZ1_ASN1_CODEC_PER_DEF_H_
#define _DZ1_TDC_DZ1_ASN1_CODEC_PER_DEF_H_

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
// Dz1Asn1PerMode
typedef enum Dz1Asn1PerMode
{
	Dz1Asn1PerMode_aligned,
	Dz1Asn1PerMode_unaligned,
	Dz1Asn1PerMode_max
} Dz1Asn1PerMode;

DZ1_CPPLINK str_t Dz1Asn1PerModeStrA(Dz1Asn1PerMode v);
DZ1_CPPLINK Dz1Asn1PerMode Dz1Asn1PerModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1PerModeStrW(Dz1Asn1PerMode v);
DZ1_CPPLINK Dz1Asn1PerMode Dz1Asn1PerModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1PerModeStr Dz1Asn1PerModeStrW
#define Dz1Asn1PerModeFromStr Dz1Asn1PerModeFromStrW
#else // UNICODE
#define Dz1Asn1PerModeStr Dz1Asn1PerModeStrA
#define Dz1Asn1PerModeFromStr Dz1Asn1PerModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1PerModeStr Dz1Asn1PerModeStrA
#define Dz1Asn1PerModeFromStr Dz1Asn1PerModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1PerMode *Dz1Asn1PerMode_new(Dz1Asn1PerMode *src, Dz1Error *err);
static __inline__ Dz1Asn1PerMode *Dz1Asn1PerMode_gen(Dz1Error *err) { Dz1Asn1PerMode v = Dz1Asn1PerMode_max; return Dz1Asn1PerMode_new(&v, err); }
static __inline__ void Dz1Asn1PerMode_del(Dz1Asn1PerMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1PerMode_delAndSetNull(void *ptr)
{
	Dz1Asn1PerMode **p = (Dz1Asn1PerMode **)ptr;
	if (p != NULL) { Dz1Asn1PerMode_del(*p); *p = NULL; }
}
// Dz1Asn1PerMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerDecoderStk
struct Dz1Asn1PerDecoderStk;
struct Dz1Asn1TypeDescr;
struct Dz1Asn1TypeDescrChild;
struct Dz1Asn1PerDecoderStk;

typedef struct Dz1Asn1PerDecoderStk
{
	struct Dz1Asn1PerDecoderStk		*next;
	struct Dz1Asn1TypeDescr			*descr;
	struct Dz1Asn1TypeDescrChild	*child;
	u32_t							 consumed;
	struct Dz1Asn1PerDecoderStk		*ret_stk;
	s32_t							 tab;
} Dz1Asn1PerDecoderStk;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1PerDecoderStk *Dz1Asn1PerDecoderStk_new(struct Dz1Asn1TypeDescr *descr_ref, 
																	   s32_t tab, Dz1Error *err);
static __inline__ Dz1Asn1PerDecoderStk *Dz1Asn1PerDecoderStk_gen(Dz1Error *err) { return Dz1Asn1PerDecoderStk_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderStk_purge(Dz1Asn1PerDecoderStk *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderStk_del(Dz1Asn1PerDecoderStk *p);
static __inline__ void Dz1Asn1PerDecoderStk_delAndSetNull(void *ptr)
{
	Dz1Asn1PerDecoderStk **p = (Dz1Asn1PerDecoderStk **)ptr;
	if (p) { Dz1Asn1PerDecoderStk_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderStkA_dump(Dz1Asn1PerDecoderStk *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderStkW_dump(Dz1Asn1PerDecoderStk *p, int tab);
#ifdef UNICODE
#define Dz1Asn1PerDecoderStk_dump Dz1Asn1PerDecoderStkW_dump
#else //  UNICODE
#define Dz1Asn1PerDecoderStk_dump Dz1Asn1PerDecoderStkA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1PerDecoderStkX_dump(Dz1Asn1PerDecoderStk *p, int tab) { DZ1_DUMP(Dz1Asn1PerDecoderStk, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1PerDecoderStk_dump Dz1Asn1PerDecoderStkA_dump
#define Dz1Asn1PerDecoderStkX_dump Dz1Asn1PerDecoderStkA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1PerDecoderStk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerDecoderDataState
typedef enum Dz1Asn1PerDecoderDataState
{
	Dz1Asn1PerDecoderDataState_initial,
	Dz1Asn1PerDecoderDataState_data_wait,
	Dz1Asn1PerDecoderDataState_max
} Dz1Asn1PerDecoderDataState;

DZ1_CPPLINK str_t Dz1Asn1PerDecoderDataStateStrA(Dz1Asn1PerDecoderDataState v);
DZ1_CPPLINK Dz1Asn1PerDecoderDataState Dz1Asn1PerDecoderDataStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1PerDecoderDataStateStrW(Dz1Asn1PerDecoderDataState v);
DZ1_CPPLINK Dz1Asn1PerDecoderDataState Dz1Asn1PerDecoderDataStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1PerDecoderDataStateStr Dz1Asn1PerDecoderDataStateStrW
#define Dz1Asn1PerDecoderDataStateFromStr Dz1Asn1PerDecoderDataStateFromStrW
#else // UNICODE
#define Dz1Asn1PerDecoderDataStateStr Dz1Asn1PerDecoderDataStateStrA
#define Dz1Asn1PerDecoderDataStateFromStr Dz1Asn1PerDecoderDataStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1PerDecoderDataStateStr Dz1Asn1PerDecoderDataStateStrA
#define Dz1Asn1PerDecoderDataStateFromStr Dz1Asn1PerDecoderDataStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1PerDecoderDataState *Dz1Asn1PerDecoderDataState_new(Dz1Asn1PerDecoderDataState *src, Dz1Error *err);
static __inline__ Dz1Asn1PerDecoderDataState *Dz1Asn1PerDecoderDataState_gen(Dz1Error *err) { Dz1Asn1PerDecoderDataState v = Dz1Asn1PerDecoderDataState_max; return Dz1Asn1PerDecoderDataState_new(&v, err); }
static __inline__ void Dz1Asn1PerDecoderDataState_del(Dz1Asn1PerDecoderDataState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1PerDecoderDataState_delAndSetNull(void *ptr)
{
	Dz1Asn1PerDecoderDataState **p = (Dz1Asn1PerDecoderDataState **)ptr;
	if (p != NULL) { Dz1Asn1PerDecoderDataState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderDataStateA_dump(Dz1Asn1PerDecoderDataState *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderDataStateW_dump(Dz1Asn1PerDecoderDataState *v, int tab);
#ifdef UNICODE
#define Dz1Asn1PerDecoderDataState_dump Dz1Asn1PerDecoderDataStateW_dump
#else //  UNICODE
#define Dz1Asn1PerDecoderDataState_dump Dz1Asn1PerDecoderDataStateA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1PerDecoderDataStateX_dump(Dz1Asn1PerDecoderDataState *p, int tab) { DZ1_DUMP(Dz1Asn1PerDecoderDataState, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1PerDecoderDataState_dump Dz1Asn1PerDecoderDataStateA_dump
#define Dz1Asn1PerDecoderDataStateX_dump Dz1Asn1PerDecoderDataStateA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1PerDecoderDataState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerDecoderDataCtx
typedef struct Dz1Asn1PerDecoderDataCtx
{
	Dz1Asn1PerDecoderDataState		 state;
	Dz1Asn1WipValue					*wip;
	u64_t							 u64data;
} Dz1Asn1PerDecoderDataCtx;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1PerDecoderDataCtx *Dz1Asn1PerDecoderDataCtx_new(Dz1Error *err);
static __inline__ Dz1Asn1PerDecoderDataCtx *Dz1Asn1PerDecoderDataCtx_gen(Dz1Error *err) { return Dz1Asn1PerDecoderDataCtx_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderDataCtx_purge(Dz1Asn1PerDecoderDataCtx *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderDataCtx_del(Dz1Asn1PerDecoderDataCtx *p);
static __inline__ void Dz1Asn1PerDecoderDataCtx_delAndSetNull(void *ptr)
{
	Dz1Asn1PerDecoderDataCtx **p = (Dz1Asn1PerDecoderDataCtx **)ptr;
	if (p) { Dz1Asn1PerDecoderDataCtx_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderDataCtxA_dump(Dz1Asn1PerDecoderDataCtx *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderDataCtxW_dump(Dz1Asn1PerDecoderDataCtx *p, int tab);
#ifdef UNICODE
#define Dz1Asn1PerDecoderDataCtx_dump Dz1Asn1PerDecoderDataCtxW_dump
#else //  UNICODE
#define Dz1Asn1PerDecoderDataCtx_dump Dz1Asn1PerDecoderDataCtxA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1PerDecoderDataCtxX_dump(Dz1Asn1PerDecoderDataCtx *p, int tab) { DZ1_DUMP(Dz1Asn1PerDecoderDataCtx, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1PerDecoderDataCtx_dump Dz1Asn1PerDecoderDataCtxA_dump
#define Dz1Asn1PerDecoderDataCtxX_dump Dz1Asn1PerDecoderDataCtxA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1PerDecoderDataCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerDecoder
struct Dz1Asn1TypeDescr;

typedef struct Dz1Asn1PerDecoder
{
	struct Dz1Asn1TypeDescr		*target;
	Dz1Asn1PerMode				 mode;
	Dz1Asn1PerDecoderStk		*stk;
	Dz1Asn1WipValue				*ret;
} Dz1Asn1PerDecoder;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1PerDecoder *Dz1Asn1PerDecoder_new(struct Dz1Asn1TypeDescr *target_ref, 
																 Dz1Asn1PerMode mode, 
																 Dz1Asn1PerDecoderStk *stk, Dz1Error *err);
static __inline__ Dz1Asn1PerDecoder *Dz1Asn1PerDecoder_gen(Dz1Error *err) { return Dz1Asn1PerDecoder_new(NULL, Dz1Asn1PerMode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoder_purge(Dz1Asn1PerDecoder *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoder_del(Dz1Asn1PerDecoder *p);
static __inline__ void Dz1Asn1PerDecoder_delAndSetNull(void *ptr)
{
	Dz1Asn1PerDecoder **p = (Dz1Asn1PerDecoder **)ptr;
	if (p) { Dz1Asn1PerDecoder_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderA_dump(Dz1Asn1PerDecoder *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerDecoderW_dump(Dz1Asn1PerDecoder *p, int tab);
#ifdef UNICODE
#define Dz1Asn1PerDecoder_dump Dz1Asn1PerDecoderW_dump
#else //  UNICODE
#define Dz1Asn1PerDecoder_dump Dz1Asn1PerDecoderA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1PerDecoderX_dump(Dz1Asn1PerDecoder *p, int tab) { DZ1_DUMP(Dz1Asn1PerDecoder, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1PerDecoder_dump Dz1Asn1PerDecoderA_dump
#define Dz1Asn1PerDecoderX_dump Dz1Asn1PerDecoderA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1PerDecoder
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1PerEncoderArg
typedef struct Dz1Asn1PerEncoderArg
{
	Dz1Asn1PerMode		mode;
} Dz1Asn1PerEncoderArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1PerEncoderArg *Dz1Asn1PerEncoderArg_new(Dz1Asn1PerMode mode, Dz1Error *err);
static __inline__ Dz1Asn1PerEncoderArg *Dz1Asn1PerEncoderArg_gen(Dz1Error *err) { return Dz1Asn1PerEncoderArg_new(Dz1Asn1PerMode_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerEncoderArg_purge(Dz1Asn1PerEncoderArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1PerEncoderArg_del(Dz1Asn1PerEncoderArg *p);
static __inline__ void Dz1Asn1PerEncoderArg_delAndSetNull(void *ptr)
{
	Dz1Asn1PerEncoderArg **p = (Dz1Asn1PerEncoderArg **)ptr;
	if (p) { Dz1Asn1PerEncoderArg_del(*p); *p = NULL; }
}
// Dz1Asn1PerEncoderArg
////////////////////////////////////////////////////////////////////////////////

#endif
