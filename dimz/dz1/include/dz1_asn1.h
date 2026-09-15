#ifndef DZ1ASN1_H
#define DZ1ASN1_H

#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_thread_stdio.h>
#include <dz1_io_stream.h>

#ifndef UNIX_SYSTEM
#pragma warning(disable:4819)
#endif

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Type
typedef enum Dz1Asn1Type
{
	Dz1Asn1Type_eoc				= 0,
	Dz1Asn1Type_boolean			= 1,	//										Prim
	Dz1Asn1Type_integer			= 2,	//										Prim
	Dz1Asn1Type_bit_str			= 3,	//										  Polymorph
	Dz1Asn1Type_octet_str		= 4,	//										  Polymorph
	Dz1Asn1Type_nul				= 5,	//										Prim
	Dz1Asn1Type_oid				= 6,	//										Prim
	Dz1Asn1Type_obj_descr		= 7,	// [UNIVERSAL 7] IMPLICIT GraphicString			String	Restricted
	Dz1Asn1Type_external		= 8,	//											Construct
	Dz1Asn1Type_realnum			= 9,	//										Prim
	Dz1Asn1Type_enumerated		= 10,	//										Prim
	Dz1Asn1Type_embPDV			= 11,	//											Construct
	Dz1Asn1Type_utf8str			= 12,	//												String	Restricted	Known-Multiplier
	Dz1Asn1Type_reloid			= 13,	//										Prim
	Dz1Asn1Type_time			= 14,	// ISO-8601 Simple String						String	Restricted
										// Reserved
	Dz1Asn1Type_seq				= 16,	//											Construct
	Dz1Asn1Type_set				= 17,	//											Construct
	Dz1Asn1Type_digit_str		= 18,	//												String	Restricted	Known-Multiplier
	Dz1Asn1Type_print_str		= 19,	//												String	Restricted	Known-Multiplier
	Dz1Asn1Type_teletex_str		= 20,	//												String	Restricted
	Dz1Asn1Type_videotex_str	= 21,	//												String	Restricted
	Dz1Asn1Type_ia5_str			= 22,	//												String	Restricted	Known-Multiplier
	Dz1Asn1Type_utc_time		= 23,	// [UNIVERSAL 23] IMPLICIT VisibleString		String	Restricted	Known-Multiplier
	Dz1Asn1Type_general_time	= 24,	// [UNIVERSAL 24] IMPLICIT VisibleString		String	Restricted	Known-Multiplier
	Dz1Asn1Type_graphic_str		= 25,	//												String	Restricted
	Dz1Asn1Type_visible_str		= 26,	//												String	Restricted	Known-Multiplier
	Dz1Asn1Type_general_str		= 27,	//												String	Restricted
	Dz1Asn1Type_uni_str			= 28,	//												String	Restricted	Known-Multiplier
	Dz1Asn1Type_char_str		= 29,	// Embedded-PDV									String
	Dz1Asn1Type_bmp_str			= 30,	//												String	Restricted	Known-Multiplier
	Dz1Asn1Type_date			= 31,	// ISO-8601 Simple String						String	Restricted	Known-Multiplier
	Dz1Asn1Type_time_of_day		= 32,	// ISO-8601 Simple String						String	Restricted	Known-Multiplier
	Dz1Asn1Type_date_time		= 33,	// ISO-8601 Simple String						String	Restricted	Known-Multiplier
	Dz1Asn1Type_duration		= 34,	// ISO-8601 Simple String						String	Restricted	Known-Multiplier
	Dz1Asn1Type_max
} Dz1Asn1Type;

#define Dz1Asn1Type_instance				 Dz1Asn1Type_external
#define Dz1Asn1Type_seqof					 Dz1Asn1Type_seq
#define Dz1Asn1Type_setof					 Dz1Asn1Type_set
#define Dz1Asn1Type_t61_str					 Dz1Asn1Type_teletex_str
#define Dz1Asn1Type_iso646_str				 Dz1Asn1Type_visible_str

DZ1_CPPLINK str_t							 Dz1Asn1TypeStrA(Dz1Asn1Type v);
DZ1_CPPLINK Dz1Asn1Type						 Dz1Asn1TypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t							 Dz1Asn1TypeStrW(Dz1Asn1Type v);
DZ1_CPPLINK Dz1Asn1Type						 Dz1Asn1TypeFromStrW(wstr_t str);
#ifdef UNICODE
#define										 Dz1Asn1TypeStr							Dz1Asn1TypeStrW
#define										 Dz1Asn1TypeFromStr						Dz1Asn1TypeFromStrW
#else // UNICODE
#define										 Dz1Asn1TypeStr							Dz1Asn1TypeStrA
#define										 Dz1Asn1TypeFromStr						Dz1Asn1TypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1TypeStr							Dz1Asn1TypeStrA
#define										 Dz1Asn1TypeFromStr						Dz1Asn1TypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Type			*Dz1Asn1Type_new(Dz1Asn1Type *src, Dz1Error *err);
static __inline__ Dz1Asn1Type				*Dz1Asn1Type_gen(Dz1Error *err) { Dz1Asn1Type v = Dz1Asn1Type_max; return Dz1Asn1Type_new(&v, err); }
#define										 Dz1Asn1Type_clone						Dz1Asn1Type_new
#define										 Dz1Asn1Type_del						Dz1u32_del
#define										 Dz1Asn1Type_delAndSetNull				Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1TypeA_dump(Dz1Asn1Type *v, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1TypeW_dump(Dz1Asn1Type *v, int tab);
#ifdef UNICODE
#define										 Dz1Asn1Type_dump						Dz1Asn1TypeW_dump
#else // UNICODE
#define										 Dz1Asn1Type_dump						Dz1Asn1TypeA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Type_dump						Dz1Asn1TypeA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1Type
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Primitive API
DZ1_CPPLINK DZ1_DLLPORT	void				*Dz1Asn1Primitive_gen(size_t sz, Dz1Error *err, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT	void				*Dz1Asn1Primitive_clone(void *ptr, size_t sz, Dz1Error *err, const char *__file__, int __line__);
static __inline__ void						 Dz1Asn1Primitive_del(void *primitive_ptr) { if (primitive_ptr != NULL) Dz1Free(primitive_ptr); }
static __inline__ void						 Dz1Asn1Primitive_delAndSetNull(void *pptr)
{
	void **p = (void **)pptr;
	if (p != NULL)
	{
		Dz1Asn1Primitive_del(*p);
		*p = NULL;
	}
}
DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1Primitive_cmp(void *a, void *b, size_t sz, bool_t is_real);
// Primitive API
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Custom Data Handling Structure
typedef struct Dz1Asn1Custom
{
	void			*data;
	Dz1CloneFunc	 data_clone;
	Dz1DelFunc		 data_del;

	Dz1DumpFunc		 data_dumpA;
	Dz1FDumpFunc	 data_fdumpA;

	Dz1DumpFunc		 data_dumpW;
	Dz1FDumpFunc	 data_fdumpW;
} Dz1Asn1Custom;

#ifdef UNIX_SYSTEM
#define										 Dz1Asn1Custom_new(TypeName, datap, ep)		__Dz1Asn1Custom_new(datap, TypeName##_clone, TypeName##_del, TypeName##A_dump, TypeName##A_fdump, NULL, NULL, ep)
#else
#define										 Dz1Asn1Custom_new(TypeName, datap, ep)		__Dz1Asn1Custom_new(datap, TypeName##_clone, TypeName##_del, TypeName##A_dump, TypeName##A_fdump, TypeName##W_dump, TypeName##W_fdump, ep)
#endif
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Custom	  *__Dz1Asn1Custom_new(void *data, Dz1CloneFunc _clone, Dz1DelFunc _del,
#ifdef UNIX_SYSTEM	// modified by gm 20230601 - gen func seperate -> UNIX/WINDOWS
															   Dz1DumpFunc _dump, Dz1FDumpFunc fdump,
#else
															   Dz1DumpFunc _dumpA, Dz1FDumpFunc fdumpA,
															   Dz1DumpFunc _dumpW, Dz1FDumpFunc fdumpW,
#endif
															   Dz1Error *err);
#ifdef UNIX_SYSTEM
static __inline__		Dz1Asn1Custom		*Dz1Asn1Custom_gen(Dz1Error *err) { return __Dz1Asn1Custom_new(NULL, NULL, NULL, NULL, NULL, err); }
#else // UNIX_SYSTEM
static __inline__		Dz1Asn1Custom		*Dz1Asn1Custom_gen(Dz1Error *err) { return __Dz1Asn1Custom_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Custom		*Dz1Asn1Custom_clone(Dz1Asn1Custom *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1Custom_del(Dz1Asn1Custom *p);
static __inline__ void						 Dz1Asn1Custom_delAndSetNull(void *pptr)
{
	Dz1Asn1Custom **p = (Dz1Asn1Custom **)pptr;
	Dz1Asn1Custom_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CustomA_dump(Dz1Asn1Custom *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CustomA_fdump(FILE *fp, Dz1Asn1Custom *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CustomW_dump(Dz1Asn1Custom *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CustomW_fdump(FILE *fp, Dz1Asn1Custom *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1Custom_dump						Dz1Asn1CustomW_dump
#define										 Dz1Asn1Custom_fdump					Dz1Asn1CustomW_fdump
#else // UNICODE
#define										 Dz1Asn1Custom_dump						Dz1Asn1CustomA_dump
#define										 Dz1Asn1Custom_fdump					Dz1Asn1CustomA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Custom_dump						Dz1Asn1CustomA_dump
#define										 Dz1Asn1Custom_fdump					Dz1Asn1CustomA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Custom Data Handling Structure
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 CODEC
struct Dz1Asn1OID;
typedef enum Dz1Asn1Codec
{
	Dz1Asn1Codec_unknown,
	Dz1Asn1Codec_ber,
	Dz1Asn1Codec_aper,
	Dz1Asn1Codec_uper,
	Dz1Asn1Codec_xer,
	Dz1Asn1Codec_cxer,
	Dz1Asn1Codec_max
} Dz1Asn1Codec;

static __inline__ Dz1Asn1Codec	*Dz1Asn1Codec_new(Dz1Asn1Codec *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Codec *ret = NULL, v = src == NULL ? Dz1Asn1Codec_max : *src;
	if ((ret = (Dz1Asn1Codec *)Dz1Memory_clone(&v, sizeof(Dz1Asn1Codec), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
static __inline__ void			 Dz1Asn1Codec_del(Dz1Asn1Codec *p) { if (p != NULL) Dz1Memory_cancel(p); }
static __inline__ void			 Dz1Asn1Codec_delAndSetNull(void *pptr) { Dz1Asn1Codec **p = (Dz1Asn1Codec **)pptr; if (p != NULL) { Dz1Asn1Codec_del(*p); *p = NULL; } }
static __inline__ Dz1Asn1Codec	*Dz1Asn1Codec_gen(Dz1Error *err) { return Dz1Asn1Codec_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT str_t				 Dz1Asn1CodecStrA(Dz1Asn1Codec codec);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Codec		 Dz1Asn1CodecFromStrA(str_t n);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t				 Dz1Asn1CodecStrW(Dz1Asn1Codec codec);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Codec		 Dz1Asn1CodecFromStrW(wstr_t n);
#ifdef UNICODE
#define										 Dz1Asn1CodecStr						Dz1Asn1CodecStrW
#define										 Dz1Asn1CodecFromStr					Dz1Asn1CodecFromStrW
#else
#define										 Dz1Asn1CodecStr						Dz1Asn1CodecStrA
#define										 Dz1Asn1CodecFromStr					Dz1Asn1CodecFromStrA
#endif
#else
#define										 Dz1Asn1CodecStr						Dz1Asn1CodecStrA
#define										 Dz1Asn1CodecFromStr					Dz1Asn1CodecFromStrA
#endif
struct Dz1Asn1OID;
DZ1_CPPLINK DZ1_DLLPORT struct Dz1Asn1OID	*Dz1Asn1Codec2OID(Dz1Asn1Codec codec, Dz1Error *err);
// ASN.1 CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 BOOLEAN (1)
typedef bool_t Dz1Asn1Bool;
#define										 Dz1Asn1Bool_new(sp, ep)				_Dz1Asn1Bool_new(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Bool			   *_Dz1Asn1Bool_new(Dz1Asn1Bool *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Bool *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Bool), err, __file, __line); }
#define										 Dz1Asn1Bool_gen(ep)					_Dz1Asn1Bool_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Bool			   *_Dz1Asn1Bool_gen(Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Bool *)Dz1Asn1Primitive_gen(sizeof(Dz1Asn1Bool), err, __file, __line); }
static __inline__ Dz1Asn1Bool			  *__Dz1Asn1Bool_gen(Dz1Error *err)			{ return Dz1Asn1Bool_gen(err); }
#define										 Dz1Asn1Bool_clone(sp, ep)				_Dz1Asn1Bool_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Bool			   *_Dz1Asn1Bool_clone(Dz1Asn1Bool *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Bool *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Bool), err, __file, __line); }
static __inline__ Dz1Asn1Bool			  *__Dz1Asn1Bool_clone(Dz1Asn1Bool *src, Dz1Error *err) { return Dz1Asn1Bool_clone(src, err); }
static __inline__ void						 Dz1Asn1Bool_del(Dz1Asn1Bool *p) { Dz1Asn1Primitive_del(p); }
#define										 Dz1Asn1Bool_delAndSetNull				Dz1Asn1Primitive_delAndSetNull

static __inline__ int						 Dz1Asn1Bool_cmp(Dz1Asn1Bool *a, Dz1Asn1Bool *b)
{ 
	if (a == NULL && b ==NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else return Dz1Bool_cmp(a, b);
}

static __inline__ void						 Dz1Asn1BoolA_dump(Dz1Asn1Bool *p, int tab) { Dz1BoolA_dump(p, tab); }
static __inline__ void						 Dz1Asn1BoolA_fdump(FILE *fp, Dz1Asn1Bool *p, int tab) { Dz1BoolA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1BoolW_dump(Dz1Asn1Bool *p, int tab) { Dz1BoolW_dump(p, tab); }
static __inline__ void						 Dz1Asn1BoolW_fdump(FILE *fp, Dz1Asn1Bool *p, int tab) { Dz1BoolW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1Bool_dump						Dz1Asn1BoolW_dump
#define										 Dz1Asn1Bool_fdump						Dz1Asn1BoolW_fdump
#else
#define										 Dz1Asn1Bool_dump						Dz1Asn1BoolA_dump
#define										 Dz1Asn1Bool_fdump						Dz1Asn1BoolA_fdump
#endif
#else // UNIX_SYSTEM
#define										 Dz1Asn1Bool_dump						Dz1Asn1BoolA_dump
#define										 Dz1Asn1Bool_fdump						Dz1Asn1BoolA_fdump
#endif
// ASN.1 BOOLEAN (1)
///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
// ASN.1 INTEGER (2)
typedef s64_t Dz1Asn1Int;
#define										 Dz1Asn1Int_new(sp, ep)					_Dz1Asn1Int_new(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Int			   *_Dz1Asn1Int_new(Dz1Asn1Int *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Int *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Int), err, __file, __line); }
#define										 Dz1Asn1Int_gen(ep)						_Dz1Asn1Int_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Int			   *_Dz1Asn1Int_gen(Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Int *)Dz1Asn1Primitive_gen(sizeof(Dz1Asn1Int), err, __file, __line); }
static __inline__ Dz1Asn1Int			  *__Dz1Asn1Int_gen(Dz1Error *err)			{ return Dz1Asn1Int_gen(err); }
#define										 Dz1Asn1Int_clone(sp, ep)				_Dz1Asn1Int_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Int			   *_Dz1Asn1Int_clone(Dz1Asn1Int *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Int *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Int), err, __file, __line); }
static __inline__ Dz1Asn1Int			  *__Dz1Asn1Int_clone(Dz1Asn1Int *src, Dz1Error *err) { return Dz1Asn1Int_clone(src, err); }
static __inline__ void						 Dz1Asn1Int_del(Dz1Asn1Int *p) { Dz1Asn1Primitive_del(p); }
#define										 Dz1Asn1Int_delAndSetNull				Dz1Asn1Primitive_delAndSetNull

static __inline__ int						 Dz1Asn1Int_cmp(Dz1Asn1Int *a, Dz1Asn1Int *b) { return Dz1s64_cmp(a, b); }

static __inline__ void						 Dz1Asn1IntA_dump(Dz1Asn1Int *p, int tab) { Dz1s64A_dump(p, tab); }
static __inline__ void						 Dz1Asn1IntA_fdump(FILE *fp, Dz1Asn1Int *p, int tab) { Dz1s64A_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1IntW_dump(Dz1Asn1Int *p, int tab) { Dz1s64W_dump(p, tab); }
static __inline__ void						 Dz1Asn1IntW_fdump(FILE *fp, Dz1Asn1Int *p, int tab) { Dz1s64W_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1Int_dump						Dz1Asn1IntW_dump
#define										 Dz1Asn1Int_fdump						Dz1Asn1IntW_fdump
#else
#define										 Dz1Asn1Int_dump						Dz1Asn1IntA_dump
#define										 Dz1Asn1Int_fdump						Dz1Asn1IntA_fdump
#endif
#else // UNIX_SYSTEM
#define										 Dz1Asn1Int_dump						Dz1Asn1IntA_dump
#define										 Dz1Asn1Int_fdump						Dz1Asn1IntA_fdump
#endif
#define Dz1Asn1Int_minimum					 DZ1INT64(0x8000000000000000)
#define Dz1Asn1Int_maximum					 DZ1INT64(0x7FFFFFFFFFFFFFFF)
// ASN.1 INTEGER (2)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 BIT STRING (3)
typedef struct Dz1Asn1BitStr
{
	u8_t			*bits;
	size_t			 maxBit;
	size_t			 allocByte;
} Dz1Asn1BitStr;
#define										 Dz1Asn1BitStr_new(u8_bits_p, alloc_sz, ep)	_Dz1Asn1BitStr_new(u8_bits_p, alloc_sz, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BitStr	   *_Dz1Asn1BitStr_new(u8_t *bits, size_t allocByte, Dz1Error *err, const char *__file, int __line);
#define										 Dz1Asn1BitStr_gen(ep)					_Dz1Asn1BitStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1BitStr			   *_Dz1Asn1BitStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1BitStr_new(NULL, 0, err, __file, __line); }
static __inline__ Dz1Asn1BitStr			  *__Dz1Asn1BitStr_gen(Dz1Error *err) { return Dz1Asn1BitStr_gen(err); }
#define										 Dz1Asn1BitStr_clone(sp, ep) _Dz1Asn1BitStr_clone(sp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BitStr	   *_Dz1Asn1BitStr_clone(Dz1Asn1BitStr *src, Dz1Error *err, const char *__file, int __line);
static __inline__ Dz1Asn1BitStr			  *__Dz1Asn1BitStr_clone(Dz1Asn1BitStr *src, Dz1Error *err) { return Dz1Asn1BitStr_clone(src, err); }
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BitStr_del(Dz1Asn1BitStr *p);

DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1BitStr_cmp(Dz1Asn1BitStr *a, Dz1Asn1BitStr *b);

DZ1_CPPLINK DZ1_DLLPORT bool_t				 Dz1Asn1BitStr_setMaxBit(Dz1Asn1BitStr *p, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BitStrA_dump(Dz1Asn1BitStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BitStrA_fdump(FILE *fp, Dz1Asn1BitStr *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BitStrW_dump(Dz1Asn1BitStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BitStrW_fdump(FILE *fp, Dz1Asn1BitStr *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1BitStr_dump						Dz1Asn1BitStrW_dump
#define										 Dz1Asn1BitStr_fdump					Dz1Asn1BitStrW_fdump
#else // UNICODE
#define										 Dz1Asn1BitStr_dump						Dz1Asn1BitStrA_dump
#define										 Dz1Asn1BitStr_fdump					Dz1Asn1BitStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1BitStr_dump						Dz1Asn1BitStrA_dump
#define										 Dz1Asn1BitStr_fdump					Dz1Asn1BitStrA_fdump
#endif // UNIX_SYSTEM
static __inline__ void						 Dz1Asn1BitStr_delAndSetNull(void *ptr)
{
	Dz1Asn1BitStr **p = (Dz1Asn1BitStr **)ptr;
	Dz1Asn1BitStr_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT Dz1Error			 Dz1Asn1BitStr_assign(Dz1Asn1BitStr *dst, u8_t *src, size_t bitSize);	// replace bits data with src

DZ1_CPPLINK DZ1_DLLPORT bool_t				_Dz1Asn1BitStr_set(Dz1Asn1BitStr *dst, size_t bitNum, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error			 Dz1Asn1BitStr_set(Dz1Asn1BitStr *dst, size_t bitNum);

DZ1_CPPLINK DZ1_DLLPORT bool_t				_Dz1Asn1BitStr_clr(Dz1Asn1BitStr *dst, size_t bitNum, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error			 Dz1Asn1BitStr_clr(Dz1Asn1BitStr *dst, size_t bitNum);

DZ1_CPPLINK DZ1_DLLPORT bool_t				 Dz1Asn1BitStr_get(Dz1Asn1BitStr *src, size_t bitNum, Dz1Error *err);	// return -1 = error, 0 or 1 = bit value
// ASN.1 BIT STRING (3)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 OCTET STRING (4)
typedef struct Dz1Asn1OctetStr
{
	u8_t		*data;
	u32_t		 size;
} Dz1Asn1OctetStr;
typedef Dz1Asn1OctetStr Dz1Asn1UniversalStr;
#define DZ1_ASN1_OCTETSTR_DATA_ALLOC		 ((u8_t *)-1)

#define										 Dz1Asn1OctetStr_new(dp, sz, errp)		_Dz1Asn1OctetStr_new(dp, sz, errp, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OctetStr	   *_Dz1Asn1OctetStr_new(u8_t *data, uint32_t size, Dz1Error *err, const char *__file__, int __line__);
#define										 Dz1Asn1OctetStr_gen(errp)				_Dz1Asn1OctetStr_gen(errp, __FILE__, __LINE__)
static __inline__ Dz1Asn1OctetStr		   *_Dz1Asn1OctetStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(NULL, 0, err, __file, __line); }
static __inline__ Dz1Asn1OctetStr		  *__Dz1Asn1OctetStr_gen(Dz1Error *err)		{ return Dz1Asn1OctetStr_gen(err); }
#define										 Dz1Asn1OctetStr_copy(dp, sp, ep)		_Dz1Asn1OctetStr_copy(dp, sp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT bool_t			    _Dz1Asn1OctetStr_copy(Dz1Asn1OctetStr *dst, Dz1Asn1OctetStr *src, Dz1Error *err, const char *__file__, int __line__);
static __inline__ bool_t				   __Dz1Asn1OctetStr_copy(Dz1Asn1OctetStr *dst, Dz1Asn1OctetStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_copy(dst, src, err); }
#define										 Dz1Asn1OctetStr_clone(srcp, errp)		_Dz1Asn1OctetStr_clone(srcp, errp, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OctetStr	   *_Dz1Asn1OctetStr_clone(Dz1Asn1OctetStr *src, Dz1Error *err, const char *__file__, int __line__);
static __inline__ Dz1Asn1OctetStr		  *__Dz1Asn1OctetStr_clone(Dz1Asn1OctetStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OctetStr_purge(Dz1Asn1OctetStr *p);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OctetStr_del(Dz1Asn1OctetStr *p);
static __inline__		void				 Dz1Asn1OctetStr_delAndSetNull(void *ptr)
{
	Dz1Asn1OctetStr **p = (Dz1Asn1OctetStr **)ptr;
	Dz1Asn1OctetStr_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1OctetStr_cmp(Dz1Asn1OctetStr *a, Dz1Asn1OctetStr *b);

#define										 Dz1Asn1OctetStrA_newFromFile(path, name, errp) _Dz1Asn1OctetStrA_newFromFile(path, name, errp, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OctetStr	   *_Dz1Asn1OctetStrA_newFromFile(str_t path, str_t name, Dz1Error *errp, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OctetStrA_dump(Dz1Asn1OctetStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OctetStrA_fdump(FILE *fp, Dz1Asn1OctetStr *p, int tab);
#ifndef UNIX_SYSTEM
#define										 Dz1Asn1OctetStrW_newFromFile(path, name, errp) _Dz1Asn1OctetStrW_newFromFile(path, name, errp, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OctetStr	   *_Dz1Asn1OctetStrW_newFromFile(wstr_t path, wstr_t name, Dz1Error *errp, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OctetStrW_dump(Dz1Asn1OctetStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OctetStrW_fdump(FILE *fp, Dz1Asn1OctetStr *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1OctetStr_newFromFile			Dz1Asn1OctetStrW_newFromFile
#define										 Dz1Asn1OctetStr_dump					Dz1Asn1OctetStrW_dump
#define										 Dz1Asn1OctetStr_fdump					Dz1Asn1OctetStrW_fdump
#else // UNICODE
#define										 Dz1Asn1OctetStr_newFromFile			Dz1Asn1OctetStrA_newFromFile
#define										 Dz1Asn1OctetStr_dump					Dz1Asn1OctetStrA_dump
#define										 Dz1Asn1OctetStr_fdump					Dz1Asn1OctetStrA_fdump
#endif // UNICODE
#else	// !UNIX_SYSTEM
#define										 Dz1Asn1OctetStr_newFromFile			Dz1Asn1OctetStrA_newFromFile
#define										 Dz1Asn1OctetStr_dump					Dz1Asn1OctetStrA_dump
#define										 Dz1Asn1OctetStr_fdump					Dz1Asn1OctetStrA_fdump
#endif	// UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1OctetStr_enc(u8_t *dst, size_t size, Dz1Asn1OctetStr *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1OctetStr_dec(Dz1Asn1OctetStr *dst, u8_t *src, size_t size, void *param, Dz1Error *err);
// ASN.1 OCTET STRING (4)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 NULL (5)
typedef int Dz1Asn1Null;
#define Dz1Asn1Null_initializer			0
#define										 Dz1Asn1Null_new(srcp, errp)			_Dz1Asn1Null_new((srcp), (errp), __FILE__, __LINE__)
static __inline__ Dz1Asn1Null			   *_Dz1Asn1Null_new(Dz1Asn1Null *p, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Null *)Dz1Asn1Primitive_clone(p, sizeof(Dz1Asn1Null), err, __file, __line); }
#define										 Dz1Asn1Null_gen(errp)					_Dz1Asn1Null_gen((errp), __FILE__, __LINE__)
static __inline__ Dz1Asn1Null			   *_Dz1Asn1Null_gen(Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Null *)Dz1Asn1Primitive_gen(sizeof(Dz1Asn1Null), err, __file, __line); }
static __inline__ Dz1Asn1Null			  *__Dz1Asn1Null_gen(Dz1Error *err)			{ return Dz1Asn1Null_gen(err); }
#define										 Dz1Asn1Null_clone(srcp, errp)			_Dz1Asn1Null_clone((srcp), (errp), __FILE__, __LINE__)
static __inline__ Dz1Asn1Null			   *_Dz1Asn1Null_clone(Dz1Asn1Null *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Null *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Null), err, __file, __line); }
static __inline__ Dz1Asn1Null			  *__Dz1Asn1Null_clone(Dz1Asn1Null *src, Dz1Error *err) { return Dz1Asn1Null_clone(src, err); }
static __inline__ void						 Dz1Asn1Null_del(Dz1Asn1Null *p) { Dz1Asn1Primitive_del(p); }
#define										 Dz1Asn1Null_delAndSetNull				Dz1Asn1Primitive_delAndSetNull
static __inline__ int						 Dz1Asn1Null_cmp(Dz1Asn1Null *a, Dz1Asn1Null *b)
{
	if (a == NULL && b == NULL) return 0; 
	else if (a == NULL && b != NULL) return -1; 
	else return 0;
}
static __inline__ void						 Dz1Asn1NullA_dump(Dz1Asn1Null *p, int tab)				{ Dz1ThreadA_printf(	"(null)\n"); }
static __inline__ void						 Dz1Asn1NullA_fdump(FILE *fp, Dz1Asn1Null *p, int tab)	{ Dz1ThreadA_fprintf(fp,"(null)\n"); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1NullW_dump(Dz1Asn1Null *p, int tab)				{ Dz1ThreadW_printf(	L"(null)\n"); }
static __inline__ void						 Dz1Asn1NullW_fdump(FILE *fp, Dz1Asn1Null *p, int tab)	{ Dz1ThreadW_fprintf(fp,L"(null)\n"); }
#ifdef UNICODE
#define										 Dz1Asn1Null_dump						Dz1Asn1NullW_dump
#define										 Dz1Asn1Null_fdump						Dz1Asn1NullW_fdump
#else // UNICODE
#define										 Dz1Asn1Null_dump						Dz1Asn1NullA_dump
#define										 Dz1Asn1Null_fdump						Dz1Asn1NullA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Null_dump						Dz1Asn1NullA_dump
#define										 Dz1Asn1Null_fdump						Dz1Asn1NullA_fdump
#endif // UNIX_SYSTEM
// ASN.1 NULL (5)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 OBJECT IDENTIFIER (6)
typedef struct Dz1Asn1OID
{
	u32_t *data;
	size_t cnt;
} Dz1Asn1OID;

#define										 Dz1Asn1OID_new(arr, cnt, ep)	_Dz1Asn1OID_new(arr, cnt, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OID		   *_Dz1Asn1OID_new(u32_t *arg_arr, size_t cnt, Dz1Error *err, const char *__file, int __line);	// old Dz1Asn1OID_new >> Dz1Asn1OID_newFromData
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OID			*Dz1Asn1OID_newFromData(u8_t *data, size_t data_unit_size, size_t cnt, Dz1Error *err);
#define										 Dz1Asn1OID_gen(ep)	_Dz1Asn1OID_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1OID			   *_Dz1Asn1OID_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OID_new(NULL, 0, err, __file, __line); }
static __inline__ Dz1Asn1OID			  *__Dz1Asn1OID_gen(Dz1Error *err) { return Dz1Asn1OID_gen(err); }
#define										 Dz1Asn1OID_clone(sp, ep) _Dz1Asn1OID_clone(sp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OID		   *_Dz1Asn1OID_clone(Dz1Asn1OID *src, Dz1Error *err, const char *__file, int __line);
static __inline__ Dz1Asn1OID			  *__Dz1Asn1OID_clone(Dz1Asn1OID *src, Dz1Error *err) { return Dz1Asn1OID_clone(src, err); }
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OID_del(Dz1Asn1OID *p);
static __inline__ void						 Dz1Asn1OID_delAndSetNull(void *ptr)
{
	Dz1Asn1OID **p = (Dz1Asn1OID **)ptr;
	Dz1Asn1OID_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1OID_cmp(Dz1Asn1OID *a, Dz1Asn1OID *b);

DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1OIDA_printable(Dz1Asn1OID *oid, char *dst, size_t dstSize, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OID			*Dz1Asn1OIDA_newFromStr(str_t strOid, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OIDA_dump(Dz1Asn1OID *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OIDA_fdump(FILE *fp, Dz1Asn1OID *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1OIDW_printable(Dz1Asn1OID *oid, wchar_t *dst, size_t dstSize, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1OID			*Dz1Asn1OIDW_newFromStr(wstr_t strOid, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OIDW_dump(Dz1Asn1OID *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1OIDW_fdump(FILE *fp, Dz1Asn1OID *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1OID_printable					Dz1Asn1OIDW_printable
#define										 Dz1Asn1OID_newFromStr					Dz1Asn1OIDW_newFromStr
#define										 Dz1Asn1OID_dump						Dz1Asn1OIDW_dump
#define										 Dz1Asn1OID_fdump						Dz1Asn1OIDW_fdump
#else // UNICODE
#define										 Dz1Asn1OID_printable					Dz1Asn1OIDA_printable
#define										 Dz1Asn1OID_newFromStr					Dz1Asn1OIDA_newFromStr
#define										 Dz1Asn1OID_dump						Dz1Asn1OIDA_dump
#define										 Dz1Asn1OID_fdump						Dz1Asn1OIDA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1OID_printable					Dz1Asn1OIDA_printable
#define										 Dz1Asn1OID_newFromStr					Dz1Asn1OIDA_newFromStr
#define										 Dz1Asn1OID_dump						Dz1Asn1OIDA_dump
#define										 Dz1Asn1OID_fdump						Dz1Asn1OIDA_fdump
#endif // UNIX_SYSTEM

DZ1_CPPLINK_VAR Dz1Asn1OID dz1Asn1OID_value_BER;	// Basic Encoding Rule
DZ1_CPPLINK_VAR Dz1Asn1OID dz1Asn1OID_value_DER;	// Distinguished Encoding Rule
DZ1_CPPLINK_VAR Dz1Asn1OID dz1Asn1OID_value_CER;	// Canonical Encoding Rule
DZ1_CPPLINK_VAR Dz1Asn1OID dz1Asn1OID_value_BAPER;	// Basic Aligned Packed Encoding Rule
DZ1_CPPLINK_VAR Dz1Asn1OID dz1Asn1OID_value_BUPER;	// Basic Unaligned Packed Encoding Rule
DZ1_CPPLINK_VAR Dz1Asn1OID dz1Asn1OID_value_CAPER;	// Canonical Aligned Packed Encoding Rule
DZ1_CPPLINK_VAR Dz1Asn1OID dz1Asn1OID_value_CUPER;	// Canonical Unaligned Packed Encoding Rule
// ASN.1 OBJECT IDENTIFIER (6)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 OBJECT DESCRIPTION : [UNIVERSAL 7] IMPLICIT GraphicString
typedef Dz1Asn1OctetStr Dz1Asn1ObjDescr;
#define										 Dz1Asn1ObjDescr_new(dp, sz, ep)		_Dz1Asn1ObjDescr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1ObjDescr		   *_Dz1Asn1ObjDescr_new(u8_t *data, u32_t sz, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, sz, err, __file, __line); }
#define										 Dz1Asn1ObjDescr_gen(ep)				_Dz1Asn1ObjDescr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1ObjDescr		   *_Dz1Asn1ObjDescr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1ObjDescr		  *__Dz1Asn1ObjDescr_gen(Dz1Error *err)		{ return Dz1Asn1ObjDescr_gen(err); }
#define										 Dz1Asn1ObjDescr_clone(sp, ep)			_Dz1Asn1ObjDescr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1ObjDescr		   *_Dz1Asn1ObjDescr_clone(Dz1Asn1ObjDescr *p, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(p, err, __file, __line); }
static __inline__ Dz1Asn1ObjDescr		  *__Dz1Asn1ObjDescr_clone(Dz1Asn1ObjDescr *p, Dz1Error *err) { return Dz1Asn1ObjDescr_clone(p, err); }
static __inline__ void						 Dz1Asn1ObjDescr_del(Dz1Asn1ObjDescr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1ObjDescr_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1ObjDescr_cmp(Dz1Asn1ObjDescr *a, Dz1Asn1ObjDescr *b) { return Dz1Asn1OctetStr_cmp(a, b); }

static __inline__ void						 Dz1Asn1ObjDescrA_dump(Dz1Asn1ObjDescr *p, int tab) { Dz1Asn1OctetStrA_dump(p, tab); }
static __inline__ void						 Dz1Asn1ObjDescrA_fdump(FILE *fp, Dz1Asn1ObjDescr *p, int tab) { Dz1Asn1OctetStrA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1ObjDescrW_dump(Dz1Asn1ObjDescr *p, int tab) { Dz1Asn1OctetStrW_dump(p, tab); }
static __inline__ void						 Dz1Asn1ObjDescrW_fdump(FILE *fp, Dz1Asn1ObjDescr *p, int tab) { Dz1Asn1OctetStrW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1ObjDescr_dump					Dz1Asn1ObjDescrW_dump
#define										 Dz1Asn1ObjDescr_fdump					Dz1Asn1ObjDescrW_fdump
#else // UNICODE
#define										 Dz1Asn1ObjDescr_dump					Dz1Asn1ObjDescrA_dump
#define										 Dz1Asn1ObjDescr_fdump					Dz1Asn1ObjDescrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1ObjDescr_dump					Dz1Asn1ObjDescrA_dump
#define										 Dz1Asn1ObjDescr_fdump					Dz1Asn1ObjDescrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 OBJECT DESCRIPTION : [UNIVERSAL 7] IMPLICIT GraphicString
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncodingPresent
typedef enum Dz1Asn1ExternalEncodingPresent
{
	Dz1Asn1ExternalEncodingPresent_single_ASN1_type,
	Dz1Asn1ExternalEncodingPresent_octet_aligned,
	Dz1Asn1ExternalEncodingPresent_arbitrary,
	Dz1Asn1ExternalEncodingPresent_max
} Dz1Asn1ExternalEncodingPresent;

DZ1_CPPLINK str_t										 Dz1Asn1ExternalEncodingPresentStrA(Dz1Asn1ExternalEncodingPresent v);
DZ1_CPPLINK Dz1Asn1ExternalEncodingPresent				 Dz1Asn1ExternalEncodingPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t										 Dz1Asn1ExternalEncodingPresentStrW(Dz1Asn1ExternalEncodingPresent v);
DZ1_CPPLINK Dz1Asn1ExternalEncodingPresent				 Dz1Asn1ExternalEncodingPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define													 Dz1Asn1ExternalEncodingPresentStr		Dz1Asn1ExternalEncodingPresentStrW
#define													 Dz1Asn1ExternalEncodingPresentFromStr	Dz1Asn1ExternalEncodingPresentFromStrW
#else // UNICODE
#define													 Dz1Asn1ExternalEncodingPresentStr		Dz1Asn1ExternalEncodingPresentStrA
#define													 Dz1Asn1ExternalEncodingPresentFromStr	Dz1Asn1ExternalEncodingPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define													 Dz1Asn1ExternalEncodingPresentStr		Dz1Asn1ExternalEncodingPresentStrA
#define													 Dz1Asn1ExternalEncodingPresentFromStr	Dz1Asn1ExternalEncodingPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1ExternalEncodingPresent	*Dz1Asn1ExternalEncodingPresent_new(Dz1Asn1ExternalEncodingPresent *src, Dz1Error *err);
static __inline__ Dz1Asn1ExternalEncodingPresent		*Dz1Asn1ExternalEncodingPresent_gen(Dz1Error *err) { Dz1Asn1ExternalEncodingPresent v = Dz1Asn1ExternalEncodingPresent_max; return Dz1Asn1ExternalEncodingPresent_new(&v, err); }
#define													 Dz1Asn1ExternalEncodingPresent_clone             Dz1Asn1ExternalEncodingPresent_new
#define													 Dz1Asn1ExternalEncodingPresent_del               Dz1u32_del
#define													 Dz1Asn1ExternalEncodingPresent_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void							 Dz1Asn1ExternalEncodingPresentA_dump(Dz1Asn1ExternalEncodingPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void							 Dz1Asn1ExternalEncodingPresentA_fdump(FILE *fp, Dz1Asn1ExternalEncodingPresent *v, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void							 Dz1Asn1ExternalEncodingPresentW_dump(Dz1Asn1ExternalEncodingPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void							 Dz1Asn1ExternalEncodingPresentW_fdump(FILE *fp, Dz1Asn1ExternalEncodingPresent *v, int tab);
#ifdef UNICODE
#define													 Dz1Asn1ExternalEncodingPresent_dump Dz1Asn1ExternalEncodingPresentW_dump
#define													 Dz1Asn1ExternalEncodingPresent_fdump Dz1Asn1ExternalEncodingPresentW_fdump
#else // UNICODE
#define													 Dz1Asn1ExternalEncodingPresent_dump Dz1Asn1ExternalEncodingPresentA_dump
#define													 Dz1Asn1ExternalEncodingPresent_fdump Dz1Asn1ExternalEncodingPresentA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define													 Dz1Asn1ExternalEncodingPresent_dump Dz1Asn1ExternalEncodingPresentA_dump
#define													 Dz1Asn1ExternalEncodingPresent_fdump Dz1Asn1ExternalEncodingPresentA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1ExternalEncodingPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncoding
typedef struct Dz1Asn1OctetStr Dz1Asn1Any;
typedef struct Dz1Asn1ExternalEncoding
{
	Dz1Asn1ExternalEncodingPresent	 present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1Any		*single_ASN1_type;
		Dz1Asn1OctetStr *octet_aligned;
		Dz1Asn1BitStr	*arbitrary;
	} x;
} Dz1Asn1ExternalEncoding;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1ExternalEncoding		*Dz1Asn1ExternalEncoding_new(Dz1Asn1ExternalEncodingPresent present, void *ptr, Dz1Error *err);
static __inline__		Dz1Asn1ExternalEncoding		*Dz1Asn1ExternalEncoding_gen(Dz1Error *err) { return Dz1Asn1ExternalEncoding_new(Dz1Asn1ExternalEncodingPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1ExternalEncoding		*Dz1Asn1ExternalEncoding_clone(Dz1Asn1ExternalEncoding *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void						 Dz1Asn1ExternalEncoding_del(Dz1Asn1ExternalEncoding *p);
static __inline__ void								 Dz1Asn1ExternalEncoding_delAndSetNull(void *ptr)
{
	Dz1Asn1ExternalEncoding **p = (Dz1Asn1ExternalEncoding **)ptr;
	Dz1Asn1ExternalEncoding_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int							 Dz1Asn1ExternalEncoding_cmp(Dz1Asn1ExternalEncoding *a, Dz1Asn1ExternalEncoding *b);

DZ1_CPPLINK DZ1_DLLPORT void						 Dz1Asn1ExternalEncodingA_dump(Dz1Asn1ExternalEncoding *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void						 Dz1Asn1ExternalEncodingA_fdump(FILE *fp, Dz1Asn1ExternalEncoding *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void						 Dz1Asn1ExternalEncodingW_dump(Dz1Asn1ExternalEncoding *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void						 Dz1Asn1ExternalEncodingW_fdump(FILE *fp, Dz1Asn1ExternalEncoding *p, int tab);
#ifdef UNICODE
#define												 Dz1Asn1ExternalEncoding_dump			Dz1Asn1ExternalEncodingW_dump
#define												 Dz1Asn1ExternalEncoding_fdump			Dz1Asn1ExternalEncodingW_fdump
#else // UNICODE
#define												 Dz1Asn1ExternalEncoding_dump			Dz1Asn1ExternalEncodingA_dump
#define												 Dz1Asn1ExternalEncoding_fdump			Dz1Asn1ExternalEncodingA_fdump
#endif //  UNICODE
#else // UNIX_SYSTEM
#define												 Dz1Asn1ExternalEncoding_dump			Dz1Asn1ExternalEncodingA_dump
#define												 Dz1Asn1ExternalEncoding_fdump			Dz1Asn1ExternalEncodingA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1ExternalEncoding
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 EXTERNAL (8)
typedef struct Dz1Asn1External
{
	Dz1Asn1OID					    *direct_reference;					// OPTIONAL
	Dz1Asn1Int					    *indirect_reference;				// OPTIONAL
	Dz1Asn1ObjDescr				    *data_value_descriptor;				// OPTIONAL
	Dz1Asn1ExternalEncoding			*encoding;
} Dz1Asn1External;

#define										 Dz1Asn1External_new(enc, ep) _Dz1Asn1External_new(enc, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT	Dz1Asn1External	   *_Dz1Asn1External_new(Dz1Asn1ExternalEncoding *encoding, Dz1Error *err, const char *__file, int __line);
#define										 Dz1Asn1External_gen(ep) _Dz1Asn1External_gen(ep, __FILE__, __LINE__)
static __inline__		Dz1Asn1External	   *_Dz1Asn1External_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1External_new(NULL, err, __file, __line); }
static __inline__		Dz1Asn1External	  *__Dz1Asn1External_gen(Dz1Error *err) { return Dz1Asn1External_gen(err); }
#define										 Dz1Asn1External_clone(src, ep) _Dz1Asn1External_clone(src, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1External	   *_Dz1Asn1External_clone(Dz1Asn1External *src, Dz1Error *err, const char *__file, int __line);
static __inline__ Dz1Asn1External		  *__Dz1Asn1External_clone(Dz1Asn1External *src, Dz1Error *err) { return Dz1Asn1External_clone(src, err); }
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1External_del(Dz1Asn1External *p);
static __inline__ void						 Dz1Asn1External_delAndSetNull(void *ptr)
{
	Dz1Asn1External **p = (Dz1Asn1External **)ptr;
	Dz1Asn1External_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1External_cmp(Dz1Asn1External *a, Dz1Asn1External *b);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1ExternalA_dump(Dz1Asn1External *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1ExternalA_fdump(FILE *fp, Dz1Asn1External *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1ExternalW_dump(Dz1Asn1External *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1ExternalW_fdump(FILE *fp, Dz1Asn1External *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1External_dump					Dz1Asn1ExternalW_dump
#define										 Dz1Asn1External_fdump					Dz1Asn1ExternalW_fdump
#else //  UNICODE
#define										 Dz1Asn1External_dump					Dz1Asn1ExternalA_dump
#define										 Dz1Asn1External_fdump					Dz1Asn1ExternalA_fdump
#endif //  UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1External_dump					Dz1Asn1ExternalA_dump
#define										 Dz1Asn1External_fdump					Dz1Asn1ExternalA_fdump
#endif // UNIX_SYSTEM
// ASN.1 EXTERNAL (8)
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ASN.1 INSTANCE-OF (8)
typedef struct Dz1Asn1InstanceOf
{
	Dz1Asn1OID	*type_id;
	Dz1Asn1Any	*value;
} Dz1Asn1InstanceOf;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1InstanceOf	*Dz1Asn1InstanceOf_new(Dz1Asn1OID *type_id, Dz1Asn1Any *value, Dz1Error *err);
static __inline__ Dz1Asn1InstanceOf			*Dz1Asn1InstanceOf_gen(Dz1Error *err) { return Dz1Asn1InstanceOf_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1InstanceOf	*Dz1Asn1InstanceOf_clone(Dz1Asn1InstanceOf *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1InstanceOf_del(Dz1Asn1InstanceOf *p);
static __inline__ void						 Dz1Asn1InstanceOf_delAndSetNull(void *ptr)
{
	Dz1Asn1InstanceOf **p = (Dz1Asn1InstanceOf **)ptr;
	Dz1Asn1InstanceOf_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1InstanceOf_cmp(Dz1Asn1InstanceOf *a, Dz1Asn1InstanceOf *b);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1InstanceOfA_dump(Dz1Asn1InstanceOf *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1InstanceOfA_fdump(FILE *fp, Dz1Asn1InstanceOf *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1InstanceOfW_dump(Dz1Asn1InstanceOf *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1InstanceOfW_fdump(FILE *fp, Dz1Asn1InstanceOf *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1InstanceOf_dump					Dz1Asn1InstanceOfW_dump
#define										 Dz1Asn1InstanceOf_fdump				Dz1Asn1InstanceOfW_fdump
#else //  UNICODE
#define										 Dz1Asn1InstanceOf_dump					Dz1Asn1InstanceOfA_dump
#define										 Dz1Asn1InstanceOf_fdump				Dz1Asn1InstanceOfA_fdump
#endif //  UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1InstanceOf_dump					Dz1Asn1InstanceOfA_dump
#define										 Dz1Asn1InstanceOf_fdump				Dz1Asn1InstanceOfA_fdump
#endif // UNIX_SYSTEM
// ASN.1 INSTANCE-OF (8)
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 REAL (9)
typedef real64_t Dz1Asn1Real;
#define										 Dz1Asn1Real_new(sp, ep)				_Dz1Asn1Real_new(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Real			   *_Dz1Asn1Real_new(Dz1Asn1Real *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Real *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Real), err, __file, __line); }
#define										 Dz1Asn1Real_gen(ep)					_Dz1Asn1Real_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Real			   *_Dz1Asn1Real_gen(Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Real *)Dz1Asn1Primitive_gen(sizeof(Dz1Asn1Real), err, __file, __line); }
static __inline__ Dz1Asn1Real			  *__Dz1Asn1Real_gen(Dz1Error *err)			{ return Dz1Asn1Real_gen(err); }
#define										 Dz1Asn1Real_clone(sp, ep)				_Dz1Asn1Real_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Real			   *_Dz1Asn1Real_clone(Dz1Asn1Real *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Real *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Real), err, __file, __line); }
static __inline__ Dz1Asn1Real			  *__Dz1Asn1Real_clone(Dz1Asn1Real *src, Dz1Error *err) { return Dz1Asn1Real_clone(src, err); }
static __inline__ void						 Dz1Asn1Real_del(Dz1Asn1Real *p) { Dz1Asn1Primitive_del(p); }
#define										 Dz1Asn1Real_delAndSetNull				Dz1Asn1Primitive_delAndSetNull

static __inline__ int						 Dz1Asn1Real_cmp(Dz1Asn1Real *a, Dz1Asn1Real *b) { return Dz1Real64_cmp(a, b); }

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1RealA_dump(Dz1Asn1Real *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1RealA_fdump(FILE *fp, Dz1Asn1Real *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1RealW_dump(Dz1Asn1Real *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1RealW_fdump(FILE *fp, Dz1Asn1Real *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1Real_dump						Dz1Asn1RealW_dump
#define										 Dz1Asn1Real_fdump						Dz1Asn1RealW_fdump
#else // UNICODE
#define										 Dz1Asn1Real_dump						Dz1Asn1RealA_dump
#define										 Dz1Asn1Real_fdump						Dz1Asn1RealA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Real_dump						Dz1Asn1RealA_dump
#define										 Dz1Asn1Real_fdump						Dz1Asn1RealA_fdump
#endif // UNIX_SYSTEM
#define										 Dz1Asn1Real_plus_inf					1.7e+308
#define										 Dz1Asn1Real_minus_inf					-1.7e+308
#define										 Dz1Asn1Real_not_num					(Dz1Asn1Real_plus_inf * 0.f)
#define										 Dz1Asn1Real_minus_zero					-0.f
// ASN.1 REAL (9)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 ENUMERATED (10)
typedef Dz1Asn1Int Dz1Asn1Enum;
#define										 Dz1Asn1Enum_new(sp, ep)				_Dz1Asn1Enum_new(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Enum			   *_Dz1Asn1Enum_new(Dz1Asn1Enum *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Enum *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Enum), err, __file, __line); }
#define										 Dz1Asn1Enum_gen(ep)					_Dz1Asn1Enum_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Enum			   *_Dz1Asn1Enum_gen(Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Enum *)Dz1Asn1Primitive_gen(sizeof(Dz1Asn1Enum), err, __file, __line); }
#define										 Dz1Asn1Enum_clone(sp, ep)				_Dz1Asn1Enum_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Enum			  *__Dz1Asn1Enum_gen(Dz1Error *err)			{ return Dz1Asn1Enum_gen(err); }
static __inline__ Dz1Asn1Enum			   *_Dz1Asn1Enum_clone(Dz1Asn1Enum *src, Dz1Error *err, const char *__file, int __line) { return (Dz1Asn1Enum *)Dz1Asn1Primitive_clone((void *)src, sizeof(Dz1Asn1Enum), err, __file, __line); }
static __inline__ Dz1Asn1Enum			  *__Dz1Asn1Enum_clone(Dz1Asn1Enum *src, Dz1Error *err) { return Dz1Asn1Enum_clone(src, err); }
static __inline__ void						 Dz1Asn1Enum_del(Dz1Asn1Enum *p) { Dz1Asn1Primitive_del(p); }
#define										 Dz1Asn1Enum_delAndSetNull				Dz1Asn1Primitive_delAndSetNull

static __inline__ int						 Dz1Asn1Enum_cmp(Dz1Asn1Enum *a, Dz1Asn1Enum *b) { return Dz1s64_cmp(a, b); }

static __inline__ void						 Dz1Asn1EnumA_dump(Dz1Asn1Enum *p, int tab) { Dz1s64A_dump(p, tab); }
static __inline__ void						 Dz1Asn1EnumA_fdump(FILE *fp, Dz1Asn1Enum *p, int tab) { Dz1s64A_fdump(fp, p, tab); }
typedef struct Dz1Asn1EnumNameMapA
{
	s64_t				 val;
	str_t				 str;
} Dz1Asn1EnumNameMapA;
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1EnumW_dump(Dz1Asn1Enum *p, int tab) { Dz1s64W_dump(p, tab); }
static __inline__ void						 Dz1Asn1EnumW_fdump(FILE *fp, Dz1Asn1Enum *p, int tab) { Dz1s64W_fdump(fp, p, tab); }
typedef struct Dz1Asn1EnumNameMapW
{
	s64_t				 val;
	wstr_t				 str;
} Dz1Asn1EnumNameMapW;
#ifdef UNICODE
#define										 Dz1Asn1Enum_dump						Dz1Asn1EnumW_dump
#define										 Dz1Asn1Enum_fdump						Dz1Asn1EnumW_fdump
#define										 Dz1Asn1EnumNameMap						Dz1Asn1EnumNameMapW
#else
#define										 Dz1Asn1Enum_dump						Dz1Asn1EnumA_dump
#define										 Dz1Asn1Enum_fdump						Dz1Asn1EnumA_fdump
#define										 Dz1Asn1EnumNameMap						Dz1Asn1EnumNameMapA
#endif
#else // UNIX_SYSTEM
#define										 Dz1Asn1Enum_dump						Dz1Asn1EnumA_dump
#define										 Dz1Asn1Enum_fdump						Dz1Asn1EnumA_fdump
#define										 Dz1Asn1EnumNameMap						Dz1Asn1EnumNameMapA
#endif
// ASN.1 ENUMERATED (10)
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvSyntaxes
typedef struct Dz1Asn1EmbPdvSyntaxes
{
	Dz1Asn1OID	*abstract;
	Dz1Asn1OID	*transfer;
} Dz1Asn1EmbPdvSyntaxes;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdvSyntaxes	*Dz1Asn1EmbPdvSyntaxes_new(Dz1Asn1OID *abstract, Dz1Asn1OID *transfer, Dz1Error *err);
static __inline__ Dz1Asn1EmbPdvSyntaxes			*Dz1Asn1EmbPdvSyntaxes_gen(Dz1Error *err) { return Dz1Asn1EmbPdvSyntaxes_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdvSyntaxes	*Dz1Asn1EmbPdvSyntaxes_clone(Dz1Asn1EmbPdvSyntaxes *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvSyntaxes_del(Dz1Asn1EmbPdvSyntaxes *p);
static __inline__ void							 Dz1Asn1EmbPdvSyntaxes_delAndSetNull(void *ptr)
{
	Dz1Asn1EmbPdvSyntaxes **p = (Dz1Asn1EmbPdvSyntaxes **)ptr;
	Dz1Asn1EmbPdvSyntaxes_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int						 Dz1Asn1EmbPdvSyntaxes_cmp(Dz1Asn1EmbPdvSyntaxes *a, Dz1Asn1EmbPdvSyntaxes *b);

DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvSyntaxesA_dump(Dz1Asn1EmbPdvSyntaxes *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvSyntaxesA_fdump(FILE *fp, Dz1Asn1EmbPdvSyntaxes *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvSyntaxesW_dump(Dz1Asn1EmbPdvSyntaxes *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvSyntaxesW_fdump(FILE *fp, Dz1Asn1EmbPdvSyntaxes *p, int tab);
#ifdef UNICODE
#define											 Dz1Asn1EmbPdvSyntaxes_dump			Dz1Asn1EmbPdvSyntaxesW_dump
#define											 Dz1Asn1EmbPdvSyntaxes_fdump		Dz1Asn1EmbPdvSyntaxesW_fdump
#else //  UNICODE
#define											 Dz1Asn1EmbPdvSyntaxes_dump			Dz1Asn1EmbPdvSyntaxesA_dump
#define											 Dz1Asn1EmbPdvSyntaxes_fdump		Dz1Asn1EmbPdvSyntaxesA_fdump
#endif //  UNICODE
#else // UNIX_SYSTEM
#define											 Dz1Asn1EmbPdvSyntaxes_dump			Dz1Asn1EmbPdvSyntaxesA_dump
#define											 Dz1Asn1EmbPdvSyntaxes_fdump		Dz1Asn1EmbPdvSyntaxesA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1EmbPdvSyntaxes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvCtxNego
typedef struct Dz1Asn1EmbPdvCtxNego
{
	Dz1Asn1Int	 presentation_context_id;
	Dz1Asn1OID	*transfer_syntax;
} Dz1Asn1EmbPdvCtxNego;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdvCtxNego	*Dz1Asn1EmbPdvCtxNego_new(Dz1Asn1Int presentation_context_id, Dz1Asn1OID *transfer_syntax, Dz1Error *err);
static __inline__ Dz1Asn1EmbPdvCtxNego			*Dz1Asn1EmbPdvCtxNego_gen(Dz1Error *err) { return Dz1Asn1EmbPdvCtxNego_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdvCtxNego	*Dz1Asn1EmbPdvCtxNego_clone(Dz1Asn1EmbPdvCtxNego *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvCtxNego_del(Dz1Asn1EmbPdvCtxNego *p);
static __inline__ void							 Dz1Asn1EmbPdvCtxNego_delAndSetNull(void *ptr)
{
	Dz1Asn1EmbPdvCtxNego **p = (Dz1Asn1EmbPdvCtxNego **)ptr;
	Dz1Asn1EmbPdvCtxNego_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int						 Dz1Asn1EmbPdvCtxNego_cmp(Dz1Asn1EmbPdvCtxNego *a, Dz1Asn1EmbPdvCtxNego *b);

DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvCtxNegoA_dump(Dz1Asn1EmbPdvCtxNego *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvCtxNegoA_fdump(FILE *fp, Dz1Asn1EmbPdvCtxNego *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvCtxNegoW_dump(Dz1Asn1EmbPdvCtxNego *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvCtxNegoW_fdump(FILE *fp, Dz1Asn1EmbPdvCtxNego *p, int tab);
#ifdef UNICODE
#define											 Dz1Asn1EmbPdvCtxNego_dump			Dz1Asn1EmbPdvCtxNegoW_dump
#define											 Dz1Asn1EmbPdvCtxNego_fdump			Dz1Asn1EmbPdvCtxNegoW_fdump
#else //  UNICODE
#define											 Dz1Asn1EmbPdvCtxNego_dump			Dz1Asn1EmbPdvCtxNegoA_dump
#define											 Dz1Asn1EmbPdvCtxNego_fdump			Dz1Asn1EmbPdvCtxNegoA_fdump
#endif //  UNICODE
#else // UNIX_SYSTEM
#define											 Dz1Asn1EmbPdvCtxNego_dump			Dz1Asn1EmbPdvCtxNegoA_dump
#define											 Dz1Asn1EmbPdvCtxNego_fdump			Dz1Asn1EmbPdvCtxNegoA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1EmbPdvCtxNego
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvIDPresent
typedef enum Dz1Asn1EmbPdvIDPresent
{
	Dz1Asn1EmbPdvIDPresent_syntaxes,
	Dz1Asn1EmbPdvIDPresent_syntax,
	Dz1Asn1EmbPdvIDPresent_presentation_context_id,
	Dz1Asn1EmbPdvIDPresent_context_negotiation,
	Dz1Asn1EmbPdvIDPresent_transfer_syntax,
	Dz1Asn1EmbPdvIDPresent_fixed,
	Dz1Asn1EmbPdvIDPresent_max
} Dz1Asn1EmbPdvIDPresent;

DZ1_CPPLINK str_t								 Dz1Asn1EmbPdvIDPresentStrA(Dz1Asn1EmbPdvIDPresent v);
DZ1_CPPLINK Dz1Asn1EmbPdvIDPresent				 Dz1Asn1EmbPdvIDPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t								 Dz1Asn1EmbPdvIDPresentStrW(Dz1Asn1EmbPdvIDPresent v);
DZ1_CPPLINK Dz1Asn1EmbPdvIDPresent				 Dz1Asn1EmbPdvIDPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define											 Dz1Asn1EmbPdvIDPresentStr			Dz1Asn1EmbPdvIDPresentStrW
#define											 Dz1Asn1EmbPdvIDPresentFromStr		Dz1Asn1EmbPdvIDPresentFromStrW
#else // UNICODE
#define											 Dz1Asn1EmbPdvIDPresentStr			Dz1Asn1EmbPdvIDPresentStrA
#define											 Dz1Asn1EmbPdvIDPresentFromStr		Dz1Asn1EmbPdvIDPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define											 Dz1Asn1EmbPdvIDPresentStr			Dz1Asn1EmbPdvIDPresentStrA
#define											 Dz1Asn1EmbPdvIDPresentFromStr		Dz1Asn1EmbPdvIDPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdvIDPresent	*Dz1Asn1EmbPdvIDPresent_new(Dz1Asn1EmbPdvIDPresent *src, Dz1Error *err);
static __inline__ Dz1Asn1EmbPdvIDPresent		*Dz1Asn1EmbPdvIDPresent_gen(Dz1Error *err) { Dz1Asn1EmbPdvIDPresent v = Dz1Asn1EmbPdvIDPresent_max; return Dz1Asn1EmbPdvIDPresent_new(&v, err); }
#define											 Dz1Asn1EmbPdvIDPresent_clone             Dz1Asn1EmbPdvIDPresent_new
#define											 Dz1Asn1EmbPdvIDPresent_del               Dz1u32_del
#define											 Dz1Asn1EmbPdvIDPresent_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvIDPresentA_dump(Dz1Asn1EmbPdvIDPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvIDPresentA_fdump(FILE *fp, Dz1Asn1EmbPdvIDPresent *v, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvIDPresentW_dump(Dz1Asn1EmbPdvIDPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Asn1EmbPdvIDPresentW_fdump(FILE *fp, Dz1Asn1EmbPdvIDPresent *v, int tab);
#ifdef UNICODE
#define											 Dz1Asn1EmbPdvIDPresent_dump		Dz1Asn1EmbPdvIDPresentW_dump
#define											 Dz1Asn1EmbPdvIDPresent_fdump		Dz1Asn1EmbPdvIDPresentW_fdump
#else // UNICODE
#define											 Dz1Asn1EmbPdvIDPresent_dump		Dz1Asn1EmbPdvIDPresentA_dump
#define											 Dz1Asn1EmbPdvIDPresent_fdump		Dz1Asn1EmbPdvIDPresentA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define											 Dz1Asn1EmbPdvIDPresent_dump		Dz1Asn1EmbPdvIDPresentA_dump
#define											 Dz1Asn1EmbPdvIDPresent_fdump		Dz1Asn1EmbPdvIDPresentA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1EmbPdvIDPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID
typedef struct Dz1Asn1EmbPdvID
{
	Dz1Asn1EmbPdvIDPresent		 present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1EmbPdvSyntaxes	*syntaxes;
		Dz1Asn1OID				*syntax;
		Dz1Asn1Int				 presentation_context_id;
		Dz1Asn1EmbPdvCtxNego	*context_negotiation;
		Dz1Asn1OID				*transfer_syntax;
		Dz1Asn1Null				 fixed;
	} x;
} Dz1Asn1EmbPdvID;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdvID		*Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1Asn1EmbPdvID			*Dz1Asn1EmbPdvID_gen(Dz1Error *err) { return Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdvID		*Dz1Asn1EmbPdvID_clone(Dz1Asn1EmbPdvID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvID_del(Dz1Asn1EmbPdvID *p);
static __inline__ void						 Dz1Asn1EmbPdvID_delAndSetNull(void *ptr)
{
	Dz1Asn1EmbPdvID **p = (Dz1Asn1EmbPdvID **)ptr;
	Dz1Asn1EmbPdvID_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1EmbPdvID_cmp(Dz1Asn1EmbPdvID *a, Dz1Asn1EmbPdvID *b);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvIDA_dump(Dz1Asn1EmbPdvID *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvIDA_fdump(FILE *fp, Dz1Asn1EmbPdvID *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvIDW_dump(Dz1Asn1EmbPdvID *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvIDW_fdump(FILE *fp, Dz1Asn1EmbPdvID *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1EmbPdvID_dump					Dz1Asn1EmbPdvIDW_dump
#define										 Dz1Asn1EmbPdvID_fdump					Dz1Asn1EmbPdvIDW_fdump
#else // UNICODE
#define										 Dz1Asn1EmbPdvID_dump					Dz1Asn1EmbPdvIDA_dump
#define										 Dz1Asn1EmbPdvID_fdump					Dz1Asn1EmbPdvIDA_fdump
#endif //  UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1EmbPdvID_dump					Dz1Asn1EmbPdvIDA_dump
#define										 Dz1Asn1EmbPdvID_fdump					Dz1Asn1EmbPdvIDA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1EmbPdvID
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Embedded-PDV (11)
typedef struct Dz1Asn1EmbPdv
{
	Dz1Asn1EmbPdvID		*identifier;
	Dz1Asn1ObjDescr		*data_value_descriptor;			// OPTIONAL
	Dz1Asn1OctetStr		*data_value;
} Dz1Asn1EmbPdv;

#define										 Dz1Asn1EmbPdv_new(id, dval, ep) _Dz1Asn1EmbPdv_new(id, dval, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdv	   *_Dz1Asn1EmbPdv_new(Dz1Asn1EmbPdvID *identifier, Dz1Asn1OctetStr *data_value, Dz1Error *err, const char *__file, int __line);
#define										 Dz1Asn1EmbPdv_gen(ep) _Dz1Asn1EmbPdv_gen(ep, __FILE__, __LINE__)
static __inline__		Dz1Asn1EmbPdv	   *_Dz1Asn1EmbPdv_gen(Dz1Error *err, const char *__file, int __line) { return Dz1Asn1EmbPdv_new(NULL, NULL, err); }
static __inline__		Dz1Asn1EmbPdv	  *__Dz1Asn1EmbPdv_gen(Dz1Error *err) { return Dz1Asn1EmbPdv_gen(err); }
#define										 Dz1Asn1EmbPdv_clone(sp, ep) _Dz1Asn1EmbPdv_clone(sp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1EmbPdv	   *_Dz1Asn1EmbPdv_clone(Dz1Asn1EmbPdv *src, Dz1Error *err, const char *__file, int __line);
static __inline__ Dz1Asn1EmbPdv			  *__Dz1Asn1EmbPdv_clone(Dz1Asn1EmbPdv *src, Dz1Error *err) { return Dz1Asn1EmbPdv_clone(src, err); }
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdv_del(Dz1Asn1EmbPdv *p);
static __inline__ void						 Dz1Asn1EmbPdv_delAndSetNull(void *ptr)
{
	Dz1Asn1EmbPdv **p = (Dz1Asn1EmbPdv **)ptr;
	Dz1Asn1EmbPdv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1EmbPdv_cmp(Dz1Asn1EmbPdv *a, Dz1Asn1EmbPdv *b);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvA_dump(Dz1Asn1EmbPdv *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvA_fdump(FILE *fp, Dz1Asn1EmbPdv *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvW_dump(Dz1Asn1EmbPdv *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1EmbPdvW_fdump(FILE *fp, Dz1Asn1EmbPdv *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1EmbPdv_dump						Dz1Asn1EmbPdvW_dump
#define										 Dz1Asn1EmbPdv_fdump					Dz1Asn1EmbPdvW_fdump
#else //  UNICODE
#define										 Dz1Asn1EmbPdv_dump						Dz1Asn1EmbPdvA_dump
#define										 Dz1Asn1EmbPdv_fdump					Dz1Asn1EmbPdvA_fdump
#endif //  UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1EmbPdv_dump						Dz1Asn1EmbPdvA_dump
#define										 Dz1Asn1EmbPdv_fdump					Dz1Asn1EmbPdvA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Embedded-PDV (11)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 UTF8String (12)
typedef Dz1Asn1OctetStr Dz1Asn1UTF8Str;
#define DZ1_ASN1_UTF8STR_DATA_ALLOC		 DZ1_ASN1_OCTETSTR_DATA_ALLOC
#define										 Dz1Asn1UTF8Str_new(dp, sz, ep)			_Dz1Asn1UTF8Str_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UTF8Str		   *_Dz1Asn1UTF8Str_new(u8_t *data, u32_t sz, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, sz, err, __file, __line); }
#define										 Dz1Asn1UTF8Str_gen(ep)					_Dz1Asn1UTF8Str_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UTF8Str		   *_Dz1Asn1UTF8Str_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1UTF8Str		  *__Dz1Asn1UTF8Str_gen(Dz1Error *err)		{ return Dz1Asn1UTF8Str_gen(err); }
#define										 Dz1Asn1UTF8Str_copy(dp, sp, ep)		_Dz1Asn1UTF8Str_copy(dp, sp, ep, __FILE__, __LINE__)
static __inline__ bool_t				    _Dz1Asn1UTF8Str_copy(Dz1Asn1UTF8Str *dst, Dz1Asn1UTF8Str *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_copy(dst, src, err, __file, __line); }
static __inline__ bool_t				   __Dz1Asn1UTF8Str_copy(Dz1Asn1UTF8Str *dst, Dz1Asn1UTF8Str *src, Dz1Error *err) { return Dz1Asn1UTF8Str_copy(dst, src, err); }
#define										 Dz1Asn1UTF8Str_clone(sp, ep)			_Dz1Asn1UTF8Str_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UTF8Str		   *_Dz1Asn1UTF8Str_clone(Dz1Asn1UTF8Str *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1UTF8Str		  *__Dz1Asn1UTF8Str_clone(Dz1Asn1UTF8Str *src, Dz1Error *err) { return Dz1Asn1UTF8Str_clone(src, err); }
static __inline__ void						 Dz1Asn1UTF8Str_purge(Dz1Asn1UTF8Str *p) { Dz1Asn1OctetStr_purge(p); }
static __inline__ void						 Dz1Asn1UTF8Str_del(Dz1Asn1UTF8Str *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1UTF8Str_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1UTF8Str_cmp(Dz1Asn1UTF8Str *a, Dz1Asn1UTF8Str *b);
DZ1_CPPLINK DZ1_DLLPORT size_t				 Dz1Asn1UTF8Str_strlen(Dz1Asn1UTF8Str *p);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UniversalStr *Dz1Asn1UTF8Str_toUCS4(Dz1Asn1UTF8Str *src, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1UTF8Str_conv(Dz1Asn1UTF8Str *src, str_t dst_charset, void *dst, size_t dst_size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UTF8Str		*Dz1Asn1UTF8Str_newFromBuf(u8_t *src, size_t src_byte_size, const char *src_charset, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UTF8Str		*Dz1Asn1UTF8StrA_newFromStr(str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t				 Dz1Asn1UTF8StrA_printable(Dz1Asn1UTF8Str *src, char *buf, size_t buf_sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t				 Dz1Asn1UTF8StrA_toStr(Dz1Asn1UTF8Str *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UTF8StrA_dump(Dz1Asn1UTF8Str *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UTF8StrA_fdump(FILE *fp, Dz1Asn1UTF8Str *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UTF8Str		*Dz1Asn1UTF8StrW_newFromStr(wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t				 Dz1Asn1UTF8StrW_printable(Dz1Asn1UTF8Str *src, wchar_t *buf, size_t buf_sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t				 Dz1Asn1UTF8StrW_toStr(Dz1Asn1UTF8Str *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UTF8StrW_dump(Dz1Asn1UTF8Str *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UTF8StrW_fdump(FILE *fp, Dz1Asn1UTF8Str *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1UTF8Str_newFromStr				Dz1Asn1UTF8StrW_newFromStr
#define										 Dz1Asn1UTF8Str_printable				Dz1Asn1UTF8StrW_printable
#define										 Dz1Asn1UTF8Str_toStr					Dz1Asn1UTF8StrW_toStr
#define										 Dz1Asn1UTF8Str_dump					Dz1Asn1UTF8StrW_dump
#define										 Dz1Asn1UTF8Str_fdump					Dz1Asn1UTF8StrW_fdump
#else // UNICODE
#define										 Dz1Asn1UTF8Str_newFromStr				Dz1Asn1UTF8StrA_newFromStr
#define										 Dz1Asn1UTF8Str_printable				Dz1Asn1UTF8StrA_printable
#define										 Dz1Asn1UTF8Str_toStr					Dz1Asn1UTF8StrA_toStr
#define										 Dz1Asn1UTF8Str_dump					Dz1Asn1UTF8StrA_dump
#define										 Dz1Asn1UTF8Str_fdump					Dz1Asn1UTF8StrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1UTF8Str_newFromStr				Dz1Asn1UTF8StrA_newFromStr
#define										 Dz1Asn1UTF8Str_printable				Dz1Asn1UTF8StrA_printable
#define										 Dz1Asn1UTF8Str_toStr					Dz1Asn1UTF8StrA_toStr
#define										 Dz1Asn1UTF8Str_dump					Dz1Asn1UTF8StrA_dump
#define										 Dz1Asn1UTF8Str_fdump					Dz1Asn1UTF8StrA_fdump
#endif
// CODEC
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1UTF8Str_enc(u8_t *dst, size_t size, Dz1Asn1UTF8Str *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1UTF8Str_dec(Dz1Asn1UTF8Str *dst, u8_t *src, size_t size, void *param, Dz1Error *err);
// Stream
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1UTF8Str_write(Dz1Stream *dst, Dz1Asn1UTF8Str *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1UTF8Str_read(Dz1Asn1UTF8Str *dst, Dz1Stream *src, Dz1IOStreamEndian rd, void *param, Dz1Error *err);
// ASN.1 UTF8String (12)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 RELATIVE OBJECT IDENTIFIER (13)
typedef Dz1Asn1OID Dz1Asn1RelativeOID;

static __inline__ Dz1Asn1RelativeOID		*Dz1Asn1RelativeOID_new(u32_t *data, size_t cnt, Dz1Error *err) {return Dz1Asn1OID_new(data, cnt, err); }
static __inline__ Dz1Asn1RelativeOID		*Dz1Asn1RelativeOID_newFromData(u8_t *data, size_t data_unit_size, size_t cnt, Dz1Error *err) {return Dz1Asn1OID_newFromData(data, data_unit_size, cnt, err); }
static __inline__ Dz1Asn1RelativeOID		*Dz1Asn1RelativeOID_gen(Dz1Error *err) { return Dz1Asn1OID_gen(err); }
static __inline__ Dz1Asn1RelativeOID		*Dz1Asn1RelativeOID_clone(Dz1Asn1RelativeOID *src, Dz1Error *err) { return Dz1Asn1OID_clone(src, err); }
static __inline__ void						 Dz1Asn1RelativeOID_del(Dz1Asn1RelativeOID *p) { Dz1Asn1OID_del(p); }
#define										 Dz1Asn1RelativeOID_delAndSetNull		Dz1Asn1OID_delAndSetNull

static __inline__ int						 Dz1Asn1RelativeOID_cmp(Dz1Asn1RelativeOID *a, Dz1Asn1RelativeOID *b) {return Dz1Asn1OID_cmp(a, b); }

static __inline__ ssize_t					 Dz1Asn1RelativeOIDA_printable(Dz1Asn1OID *p, char *dst, size_t dst_size, Dz1Error *err) { return Dz1Asn1OIDA_printable(p, dst, dst_size, err); }
static __inline__ Dz1Asn1RelativeOID		*Dz1Asn1RelativeOIDA_newFromStr(str_t str_oid, Dz1Error *err) { return Dz1Asn1OIDA_newFromStr(str_oid, err); } // modified by gm 20230601 - do return
static __inline__ void						 Dz1Asn1RelativeOIDA_dump(Dz1Asn1RelativeOID *p, int tab) { Dz1Asn1OIDA_dump(p, tab); }
static __inline__ void						 Dz1Asn1RelativeOIDA_fdump(FILE *fp, Dz1Asn1RelativeOID *p, int tab) { Dz1Asn1OIDA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ ssize_t					 Dz1Asn1RelativeOIDW_printable(Dz1Asn1OID *p, wchar_t *dst, size_t dst_size, Dz1Error *err) { return Dz1Asn1OIDW_printable(p, dst, dst_size, err); }
static __inline__ Dz1Asn1RelativeOID		*Dz1Asn1RelativeOIDW_newFromStr(wstr_t str_oid, Dz1Error *err) { Dz1Asn1OIDW_newFromStr(str_oid, err); }
static __inline__ void						 Dz1Asn1RelativeOIDW_dump(Dz1Asn1RelativeOID *p, int tab) { Dz1Asn1OIDW_dump(p, tab); }
static __inline__ void						 Dz1Asn1RelativeOIDW_fdump(FILE *fp, Dz1Asn1RelativeOID *p, int tab) { Dz1Asn1OIDW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1RelativeOID_printable			Dz1Asn1RelativeOIDW_printable
#define										 Dz1Asn1RelativeOID_newFromStr			Dz1Asn1RelativeOIDW_newFromStr
#define										 Dz1Asn1RelativeOID_dump				Dz1Asn1RelativeOIDW_dump
#define										 Dz1Asn1RelativeOID_fdump				Dz1Asn1RelativeOIDW_fdump
#else // UNICODE
#define										 Dz1Asn1RelativeOID_printable			Dz1Asn1RelativeOIDA_printable
#define										 Dz1Asn1RelativeOID_newFromStr			Dz1Asn1RelativeOIDA_newFromStr
#define										 Dz1Asn1RelativeOID_dump				Dz1Asn1RelativeOIDA_dump
#define										 Dz1Asn1RelativeOID_fdump				Dz1Asn1RelativeOIDA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1RelativeOID_printable			Dz1Asn1RelativeOIDA_printable
#define										 Dz1Asn1RelativeOID_newFromStr			Dz1Asn1RelativeOIDA_newFromStr
#define										 Dz1Asn1RelativeOID_dump				Dz1Asn1RelativeOIDA_dump
#define										 Dz1Asn1RelativeOID_fdump				Dz1Asn1RelativeOIDA_fdump
#endif // UNIX_SYSTEM
// ASN.1 RELATIVE OBJECT IDENTIFIER (13)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 TIME (14) : ISO-8601 Simple String
typedef Dz1Asn1OctetStr Dz1Asn1Time;
// No new functions
#define										 Dz1Asn1Time_gen(ep)					_Dz1Asn1Time_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Time			   *_Dz1Asn1Time_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1Time			  *__Dz1Asn1Time_gen(Dz1Error *err) { return Dz1Asn1Time_gen(err); }
#define										 Dz1Asn1Time_clone(sp, ep)				_Dz1Asn1Time_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Time			   *_Dz1Asn1Time_clone(Dz1Asn1Time *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1Time			  *__Dz1Asn1Time_clone(Dz1Asn1Time *src, Dz1Error *err) { return Dz1Asn1Time_clone(src, err); }
static __inline__ void						 Dz1Asn1Time_del(Dz1Asn1Time *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1Time_delAndSetNull				Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1Time_cmp(Dz1Asn1Time *a, Dz1Asn1Time *b) { return Dz1Asn1OctetStr_cmp(a, b); }

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Time			*Dz1Asn1TimeA_newFromStr(str_t iso8601_formatted_str, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t				 Dz1Asn1TimeA_toStr(Dz1Asn1Time *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1TimeA_dump(Dz1Asn1Time *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1TimeA_fdump(FILE *fp, Dz1Asn1Time *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Time			*Dz1Asn1TimeW_newFromStr(wstr_t iso8601_formatted_str, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t				 Dz1Asn1TimeW_toStr(Dz1Asn1Time *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1TimeW_dump(Dz1Asn1Time *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1TimeW_fdump(FILE *fp, Dz1Asn1Time *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1Time_dump						Dz1Asn1TimeW_dump
#define										 Dz1Asn1Time_fdump						Dz1Asn1TimeW_fdump
#define										 Dz1Asn1Time_toStr						Dz1Asn1TimeW_toStr
#else // UNICODE
#define										 Dz1Asn1Time_dump						Dz1Asn1TimeA_dump
#define										 Dz1Asn1Time_fdump						Dz1Asn1TimeA_fdump
#define										 Dz1Asn1Time_toStr						Dz1Asn1TimeA_toStr
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Time_dump						Dz1Asn1TimeA_dump
#define										 Dz1Asn1Time_fdump						Dz1Asn1TimeA_fdump
#define										 Dz1Asn1Time_toStr						Dz1Asn1TimeA_toStr
#endif
// ASN.1 TIME (14)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Reserved (15)
// ----------------------------------------------------------------------------
// ASN.1 SEQUENCE, SEQUENCE OF (16)
// ASN.1 SET, SET OF (17)
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT size_t Dz1Asn1SimpleStr_strlen(Dz1Asn1OctetStr *p);

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Numeric String (18)
// 0..9 + SPACE
typedef Dz1Asn1OctetStr Dz1Asn1DigitStr;

#define										 Dz1Asn1DigitStr_new(dp, sz, ep)		_Dz1Asn1DigitStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1DigitStr		   *_Dz1Asn1DigitStr_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1DigitStr_gen(ep)				_Dz1Asn1DigitStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1DigitStr		   *_Dz1Asn1DigitStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1DigitStr		  *__Dz1Asn1DigitStr_gen(Dz1Error *err)		{ return Dz1Asn1DigitStr_gen(err); }
#define										 Dz1Asn1DigitStr_clone(sp, ep)			_Dz1Asn1DigitStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1DigitStr		   *_Dz1Asn1DigitStr_clone(Dz1Asn1DigitStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1DigitStr		  *__Dz1Asn1DigitStr_clone(Dz1Asn1DigitStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1DigitStr_del(Dz1Asn1DigitStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1DigitStr_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1DigitStr_cmp(Dz1Asn1DigitStr *a, Dz1Asn1DigitStr *b) { return Dz1Asn1OctetStr_cmp(a, b); }

DZ1_CPPLINK DZ1_DLLPORT bool_t				 Dz1Asn1DigitStr_check(Dz1Asn1DigitStr *p);
#define										 Dz1Asn1DigitStr_strlen		Dz1Asn1SimpleStr_strlen

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1DigitStr		*Dz1Asn1DigitStrA_newFromStr(str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1DigitStrA_dump(Dz1Asn1DigitStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1DigitStrA_fdump(FILE *fp, Dz1Asn1DigitStr *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1DigitStr		*Dz1Asn1DigitStrW_newFromStr(wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1DigitStrW_dump(Dz1Asn1DigitStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1DigitStrW_fdump(FILE *fp, Dz1Asn1DigitStr *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1DigitStr_newFromStr				Dz1Asn1DigitStrW_newFromStr
#define										 Dz1Asn1DigitStr_dump					Dz1Asn1DigitStrW_dump
#define										 Dz1Asn1DigitStr_fdump					Dz1Asn1DigitStrW_fdump
#else // UNICODE
#define										 Dz1Asn1DigitStr_newFromStr				Dz1Asn1DigitStrA_newFromStr
#define										 Dz1Asn1DigitStr_dump					Dz1Asn1DigitStrA_dump
#define										 Dz1Asn1DigitStr_fdump					Dz1Asn1DigitStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1DigitStr_newFromStr				Dz1Asn1DigitStrA_newFromStr
#define										 Dz1Asn1DigitStr_dump					Dz1Asn1DigitStrA_dump
#define										 Dz1Asn1DigitStr_fdump					Dz1Asn1DigitStrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Numeric String (18)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Printable String (19)
// A..Z + a..z + SPACE + '()+,-./:=?
typedef Dz1Asn1OctetStr Dz1Asn1PrintStr;

#define										 Dz1Asn1PrintStr_new(dp, sz, ep)		_Dz1Asn1PrintStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1PrintStr		   *_Dz1Asn1PrintStr_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1PrintStr_gen(ep)				_Dz1Asn1PrintStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1PrintStr		   *_Dz1Asn1PrintStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1PrintStr		  *__Dz1Asn1PrintStr_gen(Dz1Error *err)		{ return Dz1Asn1PrintStr_gen(err); }
#define										 Dz1Asn1PrintStr_clone(sp, ep)			_Dz1Asn1PrintStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1PrintStr		   *_Dz1Asn1PrintStr_clone(Dz1Asn1PrintStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1PrintStr		  *__Dz1Asn1PrintStr_clone(Dz1Asn1PrintStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1PrintStr_del(Dz1Asn1PrintStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1PrintStr_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1PrintStr_cmp(Dz1Asn1PrintStr *a, Dz1Asn1PrintStr *b) { return Dz1Asn1OctetStr_cmp(a, b); }
DZ1_CPPLINK DZ1_DLLPORT bool_t				 Dz1Asn1PrintStr_check(Dz1Asn1PrintStr *p);

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1PrintStr		*Dz1Asn1PrintStrA_newFromStr(str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1PrintStrA_dump(Dz1Asn1PrintStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1PrintStrA_fdump(FILE *fp, Dz1Asn1PrintStr *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1PrintStr		*Dz1Asn1PrintStrW_newFromStr(wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1PrintStrW_dump(Dz1Asn1PrintStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1PrintStrW_fdump(FILE *fp, Dz1Asn1PrintStr *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1PrintStr_newFromStr				Dz1Asn1PrintStrW_newFromStr
#define										 Dz1Asn1PrintStr_dump					Dz1Asn1PrintStrW_dump
#define										 Dz1Asn1PrintStr_fdump					Dz1Asn1PrintStrW_fdump
#else // UNICODE
#define										 Dz1Asn1PrintStr_newFromStr				Dz1Asn1PrintStrA_newFromStr
#define										 Dz1Asn1PrintStr_dump					Dz1Asn1PrintStrA_dump
#define										 Dz1Asn1PrintStr_fdump					Dz1Asn1PrintStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1PrintStr_newFromStr				Dz1Asn1PrintStrA_newFromStr
#define										 Dz1Asn1PrintStr_dump					Dz1Asn1PrintStrA_dump
#define										 Dz1Asn1PrintStr_fdump					Dz1Asn1PrintStrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Printable String (19)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 TeleTex String, T64 String (20)
// CP-6 + CP-87 + CP-102 + CP-103 + CP-106 + CP-107 + CP-126 + CP-144 + 
// CP-150 + CP-153 + CP-156 + CP-164 + CP-165 + CP-168 + SPACE + DELETE
typedef Dz1Asn1OctetStr Dz1Asn1TeletexStr;

#define										 Dz1Asn1TeletexStr_new(dp, sz, ep)		_Dz1Asn1TeletexStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1TeletexStr		   *_Dz1Asn1TeletexStr_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1TeletexStr_gen(ep)				_Dz1Asn1TeletexStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1TeletexStr		   *_Dz1Asn1TeletexStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1TeletexStr_new(NULL, 0, err, __file, __line); }
static __inline__ Dz1Asn1TeletexStr		  *__Dz1Asn1TeletexStr_gen(Dz1Error *err) { return Dz1Asn1TeletexStr_gen(err); }
#define										 Dz1Asn1TeletexStr_clone(sp, ep)		_Dz1Asn1TeletexStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1TeletexStr		   *_Dz1Asn1TeletexStr_clone(Dz1Asn1TeletexStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1TeletexStr		  *__Dz1Asn1TeletexStr_clone(Dz1Asn1TeletexStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1TeletexStr_del(Dz1Asn1TeletexStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1TeletexStr_delAndSetNull		Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1TeletexStr_cmp(Dz1Asn1TeletexStr *a, Dz1Asn1TeletexStr *b) { return Dz1Asn1OctetStr_cmp(a, b); }
DZ1_CPPLINK DZ1_DLLPORT bool_t				 Dz1Asn1TeletexStr_check(Dz1Asn1TeletexStr *p);

static __inline__ void						 Dz1Asn1TeletexStrA_dump(Dz1Asn1TeletexStr *p, int tab) { Dz1Asn1OctetStrA_dump(p, tab); }
static __inline__ void						 Dz1Asn1TeletexStrA_fdump(FILE *fp, Dz1Asn1TeletexStr *p, int tab) { Dz1Asn1OctetStrA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1TeletexStrW_dump(Dz1Asn1TeletexStr *p, int tab) { Dz1Asn1OctetStrW_dump(p, tab); }
static __inline__ void						 Dz1Asn1TeletexStrW_fdump(FILE *fp, Dz1Asn1TeletexStr *p, int tab) { Dz1Asn1OctetStrW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1TeletexStr_dump					Dz1Asn1TeletexStrW_dump
#define										 Dz1Asn1TeletexStr_fdump				Dz1Asn1TeletexStrW_fdump
#else // UNICODE
#define										 Dz1Asn1TeletexStr_dump					Dz1Asn1TeletexStrA_dump
#define										 Dz1Asn1TeletexStr_fdump				Dz1Asn1TeletexStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1TeletexStr_dump					Dz1Asn1TeletexStrA_dump
#define										 Dz1Asn1TeletexStr_fdump				Dz1Asn1TeletexStrA_fdump
#endif // UNIX_SYSTEM

#define										 Dz1Asn1T64Str							Dz1Asn1TeletexStr
#define										 Dz1Asn1T64Str_new						Dz1Asn1TeletexStr_new
#define										 Dz1Asn1T64Str_gen						Dz1Asn1TeletexStr_gen
#define										 Dz1Asn1T64Str_clone					Dz1Asn1TeletexStr_clone
#define										 Dz1Asn1T64Str_del						Dz1Asn1TeletexStr_del
#define										 Dz1Asn1T64Str_delAndSetNull			Dz1Asn1TeletexStr_delAndSetNull
#define										 Dz1Asn1T64Str_cmp						Dz1Asn1TeletexStr_cmp

#define										 Dz1Asn1T64StrA_dump					Dz1Asn1TeletexStrA_dump
#define										 Dz1Asn1T64StrA_fdump					Dz1Asn1TeletexStrA_fdump
#ifndef UNIX_SYSTEM
#define										 Dz1Asn1T64StrW_dump					Dz1Asn1TeletexStrW_dump
#define										 Dz1Asn1T64StrW_fdump					Dz1Asn1TeletexStrW_fdump
#ifdef UNICODE
#define										 Dz1Asn1T64Str_dump						Dz1Asn1T64StrW_dump
#define										 Dz1Asn1T64Str_fdump					Dz1Asn1T64StrW_fdump
#else // UNICODE
#define										 Dz1Asn1T64Str_dump						Dz1Asn1T64StrA_dump
#define										 Dz1Asn1T64Str_fdump					Dz1Asn1T64StrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1T64Str_dump						Dz1Asn1T64StrA_dump
#define										 Dz1Asn1T64Str_fdump					Dz1Asn1T64StrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 TeleTex String, T64 String (20)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 VideoTex String (21)
// CP-1 + CP-13 + CP-72 + CP-73 + CP-87 + CP-89 + CP-102 + 
// CP-108 + CP-126 + CP-128 + CP-129 + CP-144 + CP-150 + 
// CP-153 + CP-164 + CP-165 + CP-168 + SPACE + DELETE
typedef Dz1Asn1OctetStr Dz1Asn1VideotexStr;

#define										 Dz1Asn1VideotexStr_new(dp, sz, ep)		_Dz1Asn1VideotexStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1VideotexStr	   *_Dz1Asn1VideotexStr_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1VideotexStr_gen(ep)				_Dz1Asn1VideotexStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1VideotexStr	   *_Dz1Asn1VideotexStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1VideotexStr_new(NULL, 0, err, __file, __line); }
static __inline__ Dz1Asn1VideotexStr	  *__Dz1Asn1VideotexStr_gen(Dz1Error *err) { return Dz1Asn1VideotexStr_gen(err); }
#define										 Dz1Asn1VideotexStr_clone(sp, ep)		_Dz1Asn1VideotexStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1VideotexStr	   *_Dz1Asn1VideotexStr_clone(Dz1Asn1VideotexStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1VideotexStr	  *__Dz1Asn1VideotexStr_clone(Dz1Asn1VideotexStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1VideotexStr_del(Dz1Asn1VideotexStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1VideotexStr_delAndSetNull		Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1VideotexStr_cmp(Dz1Asn1VideotexStr *a, Dz1Asn1VideotexStr *b) { return Dz1Asn1OctetStr_cmp(a, b); }

static __inline__ void						 Dz1Asn1VideotexStrA_dump(Dz1Asn1VideotexStr *p, int tab) { Dz1Asn1OctetStrA_dump(p, tab); }
static __inline__ void						 Dz1Asn1VideotexStrA_fdump(FILE *fp, Dz1Asn1VideotexStr *p, int tab) { Dz1Asn1OctetStrA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1VideotexStrW_dump(Dz1Asn1VideotexStr *p, int tab) { Dz1Asn1OctetStrW_dump(p, tab); }
static __inline__ void						 Dz1Asn1VideotexStrW_fdump(FILE *fp, Dz1Asn1VideotexStr *p, int tab) { Dz1Asn1OctetStrW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1VideotexStr_dump				Dz1Asn1VideotexStrW_dump
#define										 Dz1Asn1VideotexStr_fdump				Dz1Asn1VideotexStrW_fdump
#else // UNICODE
#define										 Dz1Asn1VideotexStr_dump				Dz1Asn1VideotexStrA_dump
#define										 Dz1Asn1VideotexStr_fdump				Dz1Asn1VideotexStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1VideotexStr_dump				Dz1Asn1VideotexStrA_dump
#define										 Dz1Asn1VideotexStr_fdump				Dz1Asn1VideotexStrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 VideoTex String (21)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 IA5 String (22)
// CP-1 + CP-6 + SPACE + DELETE == ASCII(0x00-0xFF)
typedef Dz1Asn1OctetStr Dz1Asn1IA5Str;

#define										 Dz1Asn1IA5Str_new(dp, sz, ep)			_Dz1Asn1IA5Str_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1IA5Str			   *_Dz1Asn1IA5Str_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1IA5Str_gen(ep)					_Dz1Asn1IA5Str_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1IA5Str			   *_Dz1Asn1IA5Str_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1IA5Str			  *__Dz1Asn1IA5Str_gen(Dz1Error *err)		{ return Dz1Asn1IA5Str_gen(err); }
#define										 Dz1Asn1IA5Str_clone(sp, ep)			_Dz1Asn1IA5Str_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1IA5Str			   *_Dz1Asn1IA5Str_clone(Dz1Asn1IA5Str *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1IA5Str			  *__Dz1Asn1IA5Str_clone(Dz1Asn1IA5Str *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1IA5Str_del(Dz1Asn1IA5Str *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1IA5Str_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1IA5Str_cmp(Dz1Asn1IA5Str *a, Dz1Asn1IA5Str *b) { return Dz1Asn1OctetStr_cmp(a, b); }
DZ1_CPPLINK DZ1_DLLPORT bool_t				 Dz1Asn1IA5Str_check(Dz1Asn1IA5Str *p);

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1IA5Str		*Dz1Asn1IA5StrA_newFromStr(str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1IA5StrA_dump(Dz1Asn1IA5Str *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1IA5StrA_fdump(FILE *fp, Dz1Asn1IA5Str *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1IA5Str		*Dz1Asn1IA5StrW_newFromStr(wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1IA5StrW_dump(Dz1Asn1IA5Str *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1IA5StrW_fdump(FILE *fp, Dz1Asn1IA5Str *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1IA5Str_newFromStr				Dz1Asn1IA5StrW_newFromStr
#define										 Dz1Asn1IA5Str_dump						Dz1Asn1IA5StrW_dump
#define										 Dz1Asn1IA5Str_fdump					Dz1Asn1IA5StrW_fdump
#else // UNICODE
#define										 Dz1Asn1IA5Str_newFromStr				Dz1Asn1IA5StrA_newFromStr
#define										 Dz1Asn1IA5Str_dump						Dz1Asn1IA5StrA_dump
#define										 Dz1Asn1IA5Str_fdump					Dz1Asn1IA5StrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1IA5Str_newFromStr				Dz1Asn1IA5StrA_newFromStr
#define										 Dz1Asn1IA5Str_dump						Dz1Asn1IA5StrA_dump
#define										 Dz1Asn1IA5Str_fdump					Dz1Asn1IA5StrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 IA5 String (22)
///////////////////////////////////////////////////////////////////////////////

typedef enum Dz1Asn1TimeFracDen
{
	Dz1Asn1TimeFrac_milli	= -3,
	Dz1Asn1TimeFrac_micro	= -6,
	Dz1Asn1TimeFrac_nano	= -9
} Dz1Asn1TimeFracDen;

///////////////////////////////////////////////////////////////////////////////
// ASN.1 UTC Time (23) : [UNIVERSAL 23] IMPLICIT VisibleString
typedef Dz1Asn1OctetStr Dz1Asn1UTCTime;
#define										 Dz1Asn1UTCTime_new(dp, sz, ep)			_Dz1Asn1UTCTime_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UTCTime		   *_Dz1Asn1UTCTime_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1UTCTime_gen(ep)					_Dz1Asn1UTCTime_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UTCTime		   *_Dz1Asn1UTCTime_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1UTCTime		  *__Dz1Asn1UTCTime_gen(Dz1Error *err)		{ return Dz1Asn1UTCTime_gen(err); }
#define										 Dz1Asn1UTCTime_clone(sp, ep)			_Dz1Asn1UTCTime_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UTCTime		   *_Dz1Asn1UTCTime_clone(Dz1Asn1UTCTime *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1UTCTime		  *__Dz1Asn1UTCTime_clone(Dz1Asn1UTCTime *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1UTCTime_del(Dz1Asn1UTCTime *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1UTCTime_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1UTCTime_cmp(Dz1Asn1UTCTime *a, Dz1Asn1UTCTime *b) { return Dz1Asn1OctetStr_cmp(a, b); }

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UTCTime		*Dz1Asn1UTCTime_newFromTM(struct tm *t, s32_t gmt_offset_min, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UTCTime		*Dz1Asn1UTCTime_newFromT(time_t t, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT time_t				 Dz1Asn1UTCTime_toT(Dz1Asn1UTCTime *p, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UTCTimeA_dump(Dz1Asn1UTCTime *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UTCTimeA_fdump(FILE *fp, Dz1Asn1UTCTime *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UTCTimeW_dump(Dz1Asn1UTCTime *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UTCTimeW_fdump(FILE *fp, Dz1Asn1UTCTime *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1UTCTime_dump					Dz1Asn1UTCTimeW_dump
#define										 Dz1Asn1UTCTime_fdump					Dz1Asn1UTCTimeW_fdump
#else // UNICODE
#define										 Dz1Asn1UTCTime_dump					Dz1Asn1UTCTimeA_dump
#define										 Dz1ASn1UTCTime_fdump					Dz1Asn1UTCTimeA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1UTCTime_dump					Dz1Asn1UTCTimeA_dump
#define										 Dz1Asn1UTCTime_fdump					Dz1Asn1UTCTimeA_fdump
#endif // UNIX_SYSTEM
// ASN.1 UTC Time (23)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Generalized Time (24) : [UNIVERSAL 24] IMPLICIT VisibleString
//	a)	a local time of day, including midnight at the start of a day, but excluding midnight at the end of a day, to an accuracy of:
//		1) hours, minutes, and seconds (or seconds and fractions of a second to any number of decimal places);	-> 소숫점이하 후행 0 사용 금지
//		2) hours and minutes (or minutes and fractions of a minute to any number of decimal places);			-> 사용금지, 인식은 가능해야 함
//		3) hours (or hours and fractions of an hour to any number of decimal places);							-> 사용금지, 인식은 가능해야 함
//		1) hours, minutes, and seconds (or seconds and fractions of a second to any number of decimal places);
//		2) hours and minutes (or minutes and fractions of a minute to any number of decimal places);
//		3) hours (or hours and fractions of an hour to any number of decimal places);
//	b) a UTC time of day, including midnight at the start of a day, but excluding midnight at the end of a day, to any of the accuracies listed in a) above;
//	c) a local time of day as specified in a) above, together with the difference between local time and UTC.	-> 사용금지, 인식은 가능해야 함
//	c) a local time of day as specified in a) above, together with the difference between local time and UTC.
typedef Dz1Asn1OctetStr Dz1Asn1GeneralTime;
#define										 Dz1Asn1GeneralTime_new(dp, sz, ep)			_Dz1Asn1GeneralTime_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GeneralTime	   *_Dz1Asn1GeneralTime_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1GeneralTime_gen(ep)					_Dz1Asn1GeneralTime_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GeneralTime	   *_Dz1Asn1GeneralTime_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1GeneralTime	  *__Dz1Asn1GeneralTime_gen(Dz1Error *err)		{ return Dz1Asn1GeneralTime_gen(err); }
#define										 Dz1Asn1GeneralTime_clone(sp, ep)			_Dz1Asn1GeneralTime_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GeneralTime	   *_Dz1Asn1GeneralTime_clone(Dz1Asn1GeneralTime *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1GeneralTime	  *__Dz1Asn1GeneralTime_clone(Dz1Asn1GeneralTime *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1GeneralTime_del(Dz1Asn1GeneralTime *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1GeneralTime_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1GeneralTime_cmp(Dz1Asn1GeneralTime *a, Dz1Asn1GeneralTime *b) { return Dz1Asn1OctetStr_cmp(a, b); }

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1GeneralTime	*Dz1Asn1GeneralTime_newFromTM(struct tm *t, u32_t frac, u32_t frac_depth, s32_t gmt_offset_min, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1GeneralTime	*Dz1Asn1GeneralTime_newFromT(time_t t, u32_t frac, u32_t frac_depth, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT time_t				 Dz1Asn1GeneralTime_toT(Dz1Asn1GeneralTime *p, u32_t *ret_frac, u32_t *ret_frac_depth, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1GeneralTimeA_dump(Dz1Asn1GeneralTime *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1GeneralTimeA_fdump(FILE *fp, Dz1Asn1GeneralTime *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1GeneralTimeW_dump(Dz1Asn1GeneralTime *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1GeneralTimeW_fdump(FILE *fp, Dz1Asn1GeneralTime *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1GeneralTime_dump					Dz1Asn1GeneralTimeW_dump
#define										 Dz1Asn1GeneralTime_fdump					Dz1Asn1GeneralTimeW_fdump
#else // UNICODE
#define										 Dz1Asn1GeneralTime_dump					Dz1Asn1GeneralTimeA_dump
#define										 Dz1Asn1GeneralTime_fdump					Dz1Asn1GeneralTimeA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1GeneralTime_dump					Dz1Asn1GeneralTimeA_dump
#define										 Dz1Asn1GeneralTime_fdump					Dz1Asn1GeneralTimeA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Generalized Time (24)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Graphic String (25)
// All G sets + SPACE
typedef Dz1Asn1OctetStr Dz1Asn1GraphicStr;

#define										 Dz1Asn1GraphicStr_new(dp, sz, ep)		_Dz1Asn1GraphicStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GraphicStr		   *_Dz1Asn1GraphicStr_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1GraphicStr_gen(ep)				_Dz1Asn1GraphicStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GraphicStr		   *_Dz1Asn1GraphicStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1GraphicStr_new(NULL, 0, err, __file, __line); }
static __inline__ Dz1Asn1GraphicStr		  *__Dz1Asn1GraphicStr_gen(Dz1Error *err) { return Dz1Asn1GraphicStr_gen(err); }
#define										 Dz1Asn1GraphicStr_clone(sp, ep)		_Dz1Asn1GraphicStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GraphicStr		   *_Dz1Asn1GraphicStr_clone(Dz1Asn1GraphicStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1GraphicStr		  *__Dz1Asn1GraphicStr_clone(Dz1Asn1GraphicStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1GraphicStr_del(Dz1Asn1GraphicStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1GraphicStr_delAndSetNull		Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1GraphicStr_cmp(Dz1Asn1GraphicStr *a, Dz1Asn1GraphicStr *b) { return Dz1Asn1OctetStr_cmp(a, b); }
size_t										 Dz1Asn1GraphicStr_len(Dz1Asn1GraphicStr *a);
static __inline__ void						 Dz1Asn1GraphicStrA_dump(Dz1Asn1GraphicStr *p, int tab) { Dz1Asn1OctetStrA_dump(p, tab); }
static __inline__ void						 Dz1Asn1GraphicStrA_fdump(FILE *fp, Dz1Asn1GraphicStr *p, int tab) { Dz1Asn1OctetStrA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1GraphicStrW_dump(Dz1Asn1GraphicStr *p, int tab) { Dz1Asn1OctetStrW_dump(p, tab); }
static __inline__ void						 Dz1Asn1GraphicStrW_fdump(FILE *fp, Dz1Asn1GraphicStr *p, int tab) { Dz1Asn1OctetStrW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1GraphicStr_dump					Dz1Asn1GraphicStrW_dump
#define										 Dz1Asn1GraphicStr_fdump				Dz1Asn1GraphicStrW_fdump
#else // UNICODE
#define										 Dz1Asn1GraphicStr_dump					Dz1Asn1GraphicStrA_dump
#define										 Dz1Asn1GraphicStr_fdump				Dz1Asn1GraphicStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1GraphicStr_dump					Dz1Asn1GraphicStrA_dump
#define										 Dz1Asn1GraphicStr_fdump				Dz1Asn1GraphicStrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Graphic String (25)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Visible String, ISO646 String (26)
// CP-6 + SPACE
typedef Dz1Asn1OctetStr Dz1Asn1VisibleStr;
#define										 Dz1Asn1VisibleStr_new(dp, sz, ep)		_Dz1Asn1VisibleStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1VisibleStr		   *_Dz1Asn1VisibleStr_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1VisibleStr_gen(ep)				_Dz1Asn1VisibleStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1VisibleStr		   *_Dz1Asn1VisibleStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1VisibleStr		  *__Dz1Asn1VisibleStr_gen(Dz1Error *err)	{ return Dz1Asn1VisibleStr_gen(err); }
#define										 Dz1Asn1VisibleStr_clone(sp, ep)		_Dz1Asn1VisibleStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1VisibleStr		   *_Dz1Asn1VisibleStr_clone(Dz1Asn1VisibleStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1VisibleStr		  *__Dz1Asn1VisibleStr_clone(Dz1Asn1VisibleStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1VisibleStr_del(Dz1Asn1VisibleStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1VisibleStr_delAndSetNull		Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1VisibleStr_cmp(Dz1Asn1VisibleStr *a, Dz1Asn1VisibleStr *b) { return Dz1Asn1OctetStr_cmp(a, b); }
DZ1_CPPLINK DZ1_DLLPORT bool_t				 Dz1Asn1VisibleStr_check(Dz1Asn1VisibleStr *p);

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1VisibleStr	*Dz1Asn1VisibleStrA_newFromStr(str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1VisibleStrA_dump(Dz1Asn1VisibleStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1VisibleStrA_fdump(FILE *fp, Dz1Asn1VisibleStr *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1VisibleStr	*Dz1Asn1VisibleStrW_newFromStr(wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1VisibleStrW_dump(Dz1Asn1VisibleStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1VisibleStrW_fdump(FILE *fp, Dz1Asn1VisibleStr *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1VisibleStr_newFromStr			Dz1Asn1VisibleStrW_newFromStr
#define										 Dz1Asn1VisibleStr_dump					Dz1Asn1VisibleStrW_dump
#define										 Dz1Asn1VisibleStr_fdump				Dz1Asn1VisibleStrW_fdump
#else // UNICODE
#define										 Dz1Asn1VisibleStr_newFromStr			Dz1Asn1VisibleStrA_newFromStr
#define										 Dz1Asn1VisibleStr_dump					Dz1Asn1VisibleStrA_dump
#define										 Dz1Asn1VisibleStr_fdump				Dz1Asn1VisibleStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1VisibleStr_newFromStr			Dz1Asn1VisibleStrA_newFromStr
#define										 Dz1Asn1VisibleStr_dump					Dz1Asn1VisibleStrA_dump
#define										 Dz1Asn1VisibleStr_fdump				Dz1Asn1VisibleStrA_fdump
#endif // UNIX_SYSTEM
#define										 Dz1Asn1Iso646Str						Dz1Asn1VisibleStr
#define										 Dz1Asn1Iso646Str_new					Dz1Asn1VisibleStr_new
#define										 Dz1Asn1Iso646Str_gen					Dz1Asn1VisibleStr_gen
#define										 Dz1Asn1Iso646Str_clone					Dz1Asn1VisibleStr_clone
#define										 Dz1Asn1Iso646Str_del					Dz1Asn1VisibleStr_del
#define										 Dz1Asn1Iso646Str_delAndSetNull			Dz1Asn1VisibleStr_delAndSetNull
#define										 Dz1Asn1Iso646Str_cmp					Dz1Asn1VisibleStr_cmp

#define										 Dz1Asn1Iso646StrA_newFromStr			Dz1Asn1VisibleStrA_newFromStr
#define										 Dz1Asn1Iso646StrA_dump					Dz1Asn1VisibleStrA_dump
#define										 Dz1Asn1Iso646StrA_fdump				Dz1Asn1VisibleStrA_fdump
#ifndef UNIX_SYSTEM
#define										 Dz1Asn1Iso646StrW_newFromStr			Dz1Asn1VisibleStrW_newFromStr
#define										 Dz1Asn1Iso646StrW_dump					Dz1Asn1VisibleStrW_dump
#define										 Dz1Asn1Iso646StrW_fdump				Dz1Asn1VisibleStrW_fdump
#ifdef UNICODE
#define										 Dz1Asn1Iso646Str_newFromStr			Dz1Asn1Iso646StrW_newFromStr
#define										 Dz1Asn1Iso646Str_dump					Dz1Asn1Iso646StrW_dump
#define										 Dz1Asn1Iso646Str_fdump					Dz1Asn1Iso646StrW_fdump
#else // UNICODE
#define										 Dz1Asn1Iso646Str_newFromStr			Dz1Asn1Iso646StrA_newFromStr
#define										 Dz1Asn1Iso646Str_dump					Dz1Asn1Iso646StrA_dump
#define										 Dz1Asn1Iso646Str_fdump					Dz1Asn1Iso646StrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Iso646Str_newFromStr			Dz1Asn1Iso646StrA_newFromStr
#define										 Dz1Asn1Iso646Str_dump					Dz1Asn1Iso646StrA_dump
#define										 Dz1Asn1Iso646Str_fdump					Dz1Asn1Iso646StrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Visible String, ISO646 String (26)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 General String (27)
// All G sets + All C sets + SPACE + DELETE
typedef Dz1Asn1OctetStr Dz1Asn1GeneralStr;

#define										 Dz1Asn1GeneralStr_new(dp, sz, ep)		_Dz1Asn1GeneralStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GeneralStr		   *_Dz1Asn1GeneralStr_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1GeneralStr_gen(ep)				_Dz1Asn1GeneralStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GeneralStr		   *_Dz1Asn1GeneralStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1GeneralStr_new(NULL, 0, err, __file, __line); }
static __inline__ Dz1Asn1GeneralStr		  *__Dz1Asn1GeneralStr_gen(Dz1Error *err) { return Dz1Asn1GeneralStr_gen(err); }
#define										 Dz1Asn1GeneralStr_clone(sp, ep)		_Dz1Asn1GeneralStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1GeneralStr		   *_Dz1Asn1GeneralStr_clone(Dz1Asn1GeneralStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1GeneralStr		  *__Dz1Asn1GeneralStr_clone(Dz1Asn1GeneralStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1GeneralStr_del(Dz1Asn1GeneralStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1GeneralStr_delAndSetNull		Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1GeneralStr_cmp(Dz1Asn1GeneralStr *a, Dz1Asn1GeneralStr *b) { return Dz1Asn1OctetStr_cmp(a, b); }

static __inline__ void						 Dz1Asn1GeneralStrA_dump(Dz1Asn1GeneralStr *p, int tab) { Dz1Asn1OctetStrA_dump(p, tab); }
static __inline__ void						 Dz1Asn1GeneralStrA_fdump(FILE *fp, Dz1Asn1GeneralStr *p, int tab) { Dz1Asn1OctetStrA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1GeneralStrW_dump(Dz1Asn1GeneralStr *p, int tab) { Dz1Asn1OctetStrW_dump(p, tab); }
static __inline__ void						 Dz1Asn1GeneralStrW_fdump(FILE *fp, Dz1Asn1GeneralStr *p, int tab) { Dz1Asn1OctetStrW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1GeneralStr_dump					Dz1Asn1GeneralStrW_dump
#define										 Dz1Asn1GeneralStr_fdump				Dz1Asn1GeneralStrW_fdump
#else // UNICODE
#define										 Dz1Asn1GeneralStr_dump					Dz1Asn1GeneralStrA_dump
#define										 Dz1Asn1GeneralStr_fdump				Dz1Asn1GeneralStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1GeneralStr_dump					Dz1Asn1GeneralStrA_dump
#define										 Dz1Asn1GeneralStr_fdump				Dz1Asn1GeneralStrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 General String (27)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Universal String (28)
//typedef Dz1Asn1OctetStr Dz1Asn1UniversalStr; -> moved to Below of OctetStr
#define										 Dz1Asn1UniversalStr_new(dp, sz, ep)	_Dz1Asn1UniversalStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UniversalStr	   *_Dz1Asn1UniversalStr_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1UniversalStr_gen(ep)			_Dz1Asn1UniversalStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UniversalStr	   *_Dz1Asn1UniversalStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1UniversalStr	  *__Dz1Asn1UniversalStr_gen(Dz1Error *err)	{ return Dz1Asn1UniversalStr_gen(err); }
#define										 Dz1Asn1UniversalStr_clone(sp, ep)		_Dz1Asn1UniversalStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1UniversalStr	   *_Dz1Asn1UniversalStr_clone(Dz1Asn1UniversalStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1UniversalStr	  *__Dz1Asn1UniversalStr_clone(Dz1Asn1UniversalStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1UniversalStr_del(Dz1Asn1UniversalStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1UniversalStr_delAndSetNull		Dz1Asn1OctetStr_delAndSetNull

DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1UniversalStr_cmp(Dz1Asn1UniversalStr *a, Dz1Asn1UniversalStr *b);
DZ1_CPPLINK DZ1_DLLPORT size_t				 Dz1Asn1UniversalStr_strlen(Dz1Asn1UniversalStr *p);
//DZ1_CPPLINK DZ1_DLLPORT u32_t				*Dz1Asn1UniversalStr_toUCS4(Dz1Asn1UniversalStr *p, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1UniversalStr_conv(Dz1Asn1UniversalStr *src, str_t dst_charset, void *dst, size_t dst_byte_size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UniversalStr	*Dz1Asn1UniversalStr_newFromBuf(u8_t *src, size_t src_byte_size, const char *src_charset, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UniversalStr	*Dz1Asn1UniversalStrA_newFromStr(str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t				 Dz1Asn1UniversalStrA_toStr(Dz1Asn1UniversalStr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UniversalStrA_dump(Dz1Asn1UniversalStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UniversalStrA_fdump(FILE *fp, Dz1Asn1UniversalStr *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UniversalStr	*Dz1Asn1UniversalStrW_newFromStr(wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t				 Dz1Asn1UniversalStrW_toStr(Dz1Asn1UniversalStr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UniversalStrW_dump(Dz1Asn1UniversalStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1UniversalStrW_fdump(FILE *fp, Dz1Asn1UniversalStr *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1UniversalStr_newFromStr			Dz1Asn1UniversalStrW_newFromStr
#define										 Dz1Asn1UniversalStr_toStr				Dz1Asn1UniversalStrW_toStr
#define										 Dz1Asn1UniversalStr_dump				Dz1Asn1UniversalStrW_dump
#define										 Dz1Asn1UniversalStr_fdump				Dz1Asn1UniversalStrW_fdump
#else // UNICODE
#define										 Dz1Asn1UniversalStr_newFromStr			Dz1Asn1UniversalStrA_newFromStr
#define										 Dz1Asn1UniversalStr_toStr				Dz1Asn1UniversalStrA_toStr
#define										 Dz1Asn1UniversalStr_dump				Dz1Asn1UniversalStrA_dump
#define										 Dz1Asn1UniversalStr_fdump				Dz1Asn1UniversalStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1UniversalStr_newFromStr			Dz1Asn1UniversalStrA_newFromStr
#define										 Dz1Asn1UniversalStr_dump				Dz1Asn1UniversalStrA_dump
#define										 Dz1Asn1UniversalStr_fdump				Dz1Asn1UniversalStrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Universal String (28)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Character String (29)
// X.680 44.5
typedef struct Dz1Asn1CharStr
{
	Dz1Asn1EmbPdvID		*identifier;
	Dz1Asn1ObjDescr		*str_value_descriptor;			// OPTIONAL
	Dz1Asn1OctetStr		*str_value;
} Dz1Asn1CharStr;

#define										 Dz1Asn1CharStr_new(idp, strp, ep)	_Dz1Asn1CharStr_new(idp, strp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1CharStr	   *_Dz1Asn1CharStr_new(Dz1Asn1EmbPdvID *identifier, Dz1Asn1OctetStr *str_value, Dz1Error *err, const char *__file, int __line);
static __inline__ Dz1Asn1CharStr		  *__Dz1Asn1CharStr_new(Dz1Asn1EmbPdvID *identifier, Dz1Asn1OctetStr *str_value, Dz1Error *err) { return Dz1Asn1CharStr_new(identifier, str_value, err); }

#define										 Dz1Asn1CharStr_gen(ep)	_Dz1Asn1CharStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1CharStr		   *_Dz1Asn1CharStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1CharStr_new(NULL, NULL, err, __file, __line); }
static __inline__ Dz1Asn1CharStr		  *__Dz1Asn1CharStr_gen(Dz1Error *err) { return Dz1Asn1CharStr_gen(err); }

#define										 Dz1Asn1CharStr_clone(sp, ep)	_Dz1Asn1CharStr_clone(sp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1CharStr	   *_Dz1Asn1CharStr_clone(Dz1Asn1CharStr *src, Dz1Error *err, const char *__file, int __line);
static __inline__ Dz1Asn1CharStr		  *__Dz1Asn1CharStr_clone(Dz1Asn1CharStr *src, Dz1Error *err) { return Dz1Asn1CharStr_clone(src, err); }

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CharStr_del(Dz1Asn1CharStr *p);
static __inline__ void						 Dz1Asn1CharStr_delAndSetNull(void *ptr)
{
	Dz1Asn1CharStr **p = (Dz1Asn1CharStr **)ptr;
	Dz1Asn1CharStr_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1CharStr_cmp(Dz1Asn1CharStr *a, Dz1Asn1CharStr *b);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CharStrA_dump(Dz1Asn1CharStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CharStrA_fdump(FILE *fp, Dz1Asn1CharStr *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CharStrW_dump(Dz1Asn1CharStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1CharStrW_fdump(FILE *fp, Dz1Asn1CharStr *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1CharStr_dump					Dz1Asn1CharStrW_dump
#define										 Dz1Asn1CharStr_fdump					Dz1Asn1CharStrW_fdump
#else //  UNICODE
#define										 Dz1Asn1CharStr_dump					Dz1Asn1CharStrA_dump
#define										 Dz1Asn1CharStr_fdump					Dz1Asn1CharStrA_fdump
#endif //  UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1CharStr_dump					Dz1Asn1CharStrA_dump
#define										 Dz1Asn1CharStr_fdump					Dz1Asn1CharStrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 Character String (29)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 BMPString (30)
typedef Dz1Asn1OctetStr Dz1Asn1BMPStr;
#define DZ1_ASN1_BMPSTR_DATA_ALLOC			 DZ1_ASN1_OCTETSTR_DATA_ALLOC
#define										 Dz1Asn1BMPStr_new(dp, sz, ep)			_Dz1Asn1BMPStr_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1BMPStr			   *_Dz1Asn1BMPStr_new(u8_t *data, u32_t sz, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, sz, err, __file, __line); }
#define										 Dz1Asn1BMPStr_gen(ep)					_Dz1Asn1BMPStr_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1BMPStr			   *_Dz1Asn1BMPStr_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1BMPStr			  *__Dz1Asn1BMPStr_gen(Dz1Error *err)		{ return Dz1Asn1BMPStr_gen(err); }
#define										 Dz1Asn1BMPStr_clone(sp, ep)			_Dz1Asn1BMPStr_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1BMPStr			   *_Dz1Asn1BMPStr_clone(Dz1Asn1BMPStr *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1BMPStr			  *__Dz1Asn1BMPStr_clone(Dz1Asn1BMPStr *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1BMPStr_del(Dz1Asn1BMPStr *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1BMPStr_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

DZ1_CPPLINK DZ1_DLLPORT int					 Dz1Asn1BMPStr_cmp(Dz1Asn1BMPStr *a, Dz1Asn1BMPStr *b);
DZ1_CPPLINK DZ1_DLLPORT size_t				 Dz1Asn1BMPStr_strlen(Dz1Asn1BMPStr *p);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1UniversalStr *Dz1Asn1BMPStr_toUCS4(Dz1Asn1BMPStr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1Asn1BMPStr_conv(Dz1Asn1BMPStr *src, str_t dst_charset, void *dst, size_t dst_byte_size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BMPStr		*Dz1Asn1BMPStr_newFromBuf(u8_t *src, size_t src_byte_size, const char *src_charset, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BMPStr		*Dz1Asn1BMPStrA_newFromStr(str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t				 Dz1Asn1BMPStrA_toStr(Dz1Asn1BMPStr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BMPStrA_dump(Dz1Asn1BMPStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BMPStrA_fdump(FILE *fp, Dz1Asn1BMPStr *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1BMPStr		*Dz1Asn1BMPStrW_newFromStr(wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t				 Dz1Asn1BMPStrW_toStr(Dz1Asn1BMPStr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BMPStrW_dump(Dz1Asn1BMPStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1Asn1BMPStrW_fdump(FILE *fp, Dz1Asn1BMPStr *p, int tab);
#ifdef UNICODE
#define										 Dz1Asn1BMPStr_newFromStr				Dz1Asn1BMPStrW_newFromStr
#define										 Dz1Asn1BMPStr_toStr					Dz1Asn1BMPStrW_toStr
#define										 Dz1Asn1BMPStr_dump						Dz1Asn1BMPStrW_dump
#define										 Dz1Asn1BMPStr_fdump					Dz1Asn1BMPStrW_fdump
#else // UNICODE
#define										 Dz1Asn1BMPStr_newFromStr				Dz1Asn1BMPStrA_newFromStr
#define										 Dz1Asn1BMPStr_toStr					Dz1Asn1BMPStrA_toStr
#define										 Dz1Asn1BMPStr_dump						Dz1Asn1BMPStrA_dump
#define										 Dz1Asn1BMPStr_fdump					Dz1Asn1BMPStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1BMPStr_newFromStr				Dz1Asn1BMPStrA_newFromStr
#define										 Dz1Asn1BMPStr_dump						Dz1Asn1BMPStrA_dump
#define										 Dz1Asn1BMPStr_fdump					Dz1Asn1BMPStrA_fdump
#define										 Dz1Asn1BMPStr_toStr					Dz1Asn1BMPStrA_toStr
#endif
// ASN.1 BMPString (30)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 DATE (31) : ISO-8601 Simple String
typedef Dz1Asn1Time Dz1Asn1Date;
// No new functions
#define										 Dz1Asn1Date_gen(ep)					_Dz1Asn1Date_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Date			   *_Dz1Asn1Date_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1Date			  *__Dz1Asn1Date_gen(Dz1Error *err) { return Dz1Asn1Date_gen(err); }
#define										 Dz1Asn1Date_clone(sp, ep)				_Dz1Asn1Date_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Date			   *_Dz1Asn1Date_clone(Dz1Asn1Date *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1Date			  *__Dz1Asn1Date_clone(Dz1Asn1Date *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1Date_del(Dz1Asn1Date *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1Date_delAndSetNull				Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1Date_cmp(Dz1Asn1Date *a, Dz1Asn1Date *b) { return Dz1Asn1OctetStr_cmp(a, b); }

static __inline__ Dz1Asn1Date				*Dz1Asn1DateA_newFromStr(str_t iso8601_date_formatted_str, Dz1Error *err) { return Dz1Asn1TimeA_newFromStr(iso8601_date_formatted_str, err); }
static __inline__ str_t						 Dz1Asn1DateA_toStr(Dz1Asn1Date *src, Dz1Error *err) { return Dz1Asn1TimeA_toStr(src, err); }
static __inline__ void						 Dz1Asn1DateA_dump(Dz1Asn1Date *p, int tab) { Dz1Asn1TimeA_dump(p, tab); }
static __inline__ void						 Dz1Asn1DateA_fdump(FILE *fp, Dz1Asn1Date *p, int tab) { Dz1Asn1TimeA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ Dz1Asn1Date				*Dz1Asn1DateW_newFromStr(wstr_t iso8601_date_formatted_str, Dz1Error *err) { return Dz1Asn1TimeW_newFromStr(iso8601_date_formatted_str, err); }
static __inline__ wstr_t					 Dz1Asn1DateW_toStr(Dz1Asn1Date *src, Dz1Error *err) { return Dz1Asn1TimeW_toStr(src, err); }
static __inline__ void						 Dz1Asn1DateW_dump(Dz1Asn1Date *p, int tab) { Dz1Asn1TimeW_dump(p, tab); }
static __inline__ void						 Dz1Asn1DateW_fdump(FILE *fp, Dz1Asn1Date *p, int tab) { Dz1Asn1TimeW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1Date_dump						Dz1Asn1DateW_dump
#define										 Dz1Asn1Date_fdump						Dz1Asn1DateW_fdump
#define										 Dz1Asn1Date_toStr						Dz1Asn1DateW_toStr
#else // UNICODE
#define										 Dz1Asn1Date_dump						Dz1Asn1DateA_dump
#define										 Dz1Asn1Date_fdump						Dz1Asn1DateA_fdump
#define										 Dz1Asn1Date_toStr						Dz1Asn1DateA_toStr
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Date_dump						Dz1Asn1DateA_dump
#define										 Dz1Asn1Date_fdump						Dz1Asn1DateA_fdump
#define										 Dz1Asn1Date_toStr						Dz1Asn1DateA_toStr
#endif
// ASN.1 DATE (31) : ISO-8601 Simple String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 TIME OF DAY (32) : ISO-8601 Simple String
typedef Dz1Asn1Time Dz1Asn1TimeOfDay;
// No new functions
#define										 Dz1Asn1TimeOfDay_gen(ep)				_Dz1Asn1TimeOfDay_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1TimeOfDay		   *_Dz1Asn1TimeOfDay_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1TimeOfDay		  *__Dz1Asn1TimeOfDay_gen(Dz1Error *err) { return Dz1Asn1TimeOfDay_gen(err); }
#define										 Dz1Asn1TimeOfDay_clone(sp, ep)			_Dz1Asn1TimeOfDay_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1TimeOfDay		   *_Dz1Asn1TimeOfDay_clone(Dz1Asn1TimeOfDay *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1TimeOfDay		  *__Dz1Asn1TimeOfDay_clone(Dz1Asn1TimeOfDay *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1TimeOfDay_del(Dz1Asn1TimeOfDay *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1TimeOfDay_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1TimeOfDay_cmp(Dz1Asn1TimeOfDay *a, Dz1Asn1TimeOfDay *b) { return Dz1Asn1OctetStr_cmp(a, b); }

static __inline__ Dz1Asn1TimeOfDay			*Dz1Asn1TimeOfDayA_newFromStr(str_t iso8601_tod_formatted_str, Dz1Error *err) { return Dz1Asn1TimeA_newFromStr(iso8601_tod_formatted_str, err); }
static __inline__ str_t						 Dz1Asn1TimeOfDayA_toStr(Dz1Asn1TimeOfDay *src, Dz1Error *err) { return Dz1Asn1TimeA_toStr(src, err); }
static __inline__ void						 Dz1Asn1TimeOfDayA_dump(Dz1Asn1TimeOfDay *p, int tab) { Dz1Asn1TimeA_dump(p, tab); }
static __inline__ void						 Dz1Asn1TimeOfDayA_fdump(FILE *fp, Dz1Asn1TimeOfDay *p, int tab) { Dz1Asn1TimeA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ Dz1Asn1TimeOfDay			*Dz1Asn1TimeOfDayW_newFromStr(wstr_t iso8601_tod_formatted_str, Dz1Error *err) { return Dz1Asn1TimeW_newFromStr(iso8601_tod_formatted_str, err); }
static __inline__ wstr_t					 Dz1Asn1TimeOfDayW_toStr(Dz1Asn1TimeOfDay *src, Dz1Error *err) { return Dz1Asn1TimeW_toStr(src, err); }
static __inline__ void						 Dz1Asn1TimeOfDayW_dump(Dz1Asn1TimeOfDay *p, int tab) { Dz1Asn1TimeW_dump(p, tab); }
static __inline__ void						 Dz1Asn1TimeOfDayW_fdump(FILE *fp, Dz1Asn1TimeOfDay *p, int tab) { Dz1Asn1TimeW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1TimeOfDay_dump					Dz1Asn1TimeOfDayW_dump
#define										 Dz1Asn1TimeOfDay_fdump					Dz1Asn1TimeOfDayW_fdump
#define										 Dz1Asn1TimeOfDay_toStr					Dz1Asn1TimeOfDayW_toStr
#else // UNICODE
#define										 Dz1Asn1TimeOfDay_dump					Dz1Asn1TimeOfDayA_dump
#define										 Dz1Asn1TimeOfDay_fdump					Dz1Asn1TimeOfDayA_fdump
#define										 Dz1Asn1TimeOfDay_toStr					Dz1Asn1TimeOfDayA_toStr
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1TimeOfDay_dump					Dz1Asn1TimeOfDayA_dump
#define										 Dz1Asn1TimeOfDay_fdump					Dz1Asn1TimeOfDayA_fdump
#define										 Dz1Asn1TimeOfDay_toStr					Dz1Asn1TimeOfDayA_toStr
#endif
// ASN.1 DATE (31) : ISO-8601 Simple String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 DATE TIME (33) : ISO-8601 Simple String
typedef Dz1Asn1Time Dz1Asn1DateTime;
// No new functions
#define										 Dz1Asn1DateTime_gen(ep)				_Dz1Asn1DateTime_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1DateTime		   *_Dz1Asn1DateTime_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1DateTime		  *__Dz1Asn1DateTime_gen(Dz1Error *err) { return Dz1Asn1DateTime_gen(err); }
#define										 Dz1Asn1DateTime_clone(sp, ep)			_Dz1Asn1DateTime_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1DateTime		   *_Dz1Asn1DateTime_clone(Dz1Asn1DateTime *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1DateTime		  *__Dz1Asn1DateTime_clone(Dz1Asn1DateTime *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1DateTime_del(Dz1Asn1DateTime *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1DateTime_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1DateTime_cmp(Dz1Asn1DateTime *a, Dz1Asn1DateTime *b) { return Dz1Asn1OctetStr_cmp(a, b); }

static __inline__ Dz1Asn1DateTime			*Dz1Asn1DateTimeA_newFromStr(str_t iso8601_datetime_formatted_str, Dz1Error *err) { return Dz1Asn1TimeA_newFromStr(iso8601_datetime_formatted_str, err); }
static __inline__ str_t						 Dz1Asn1DateTimeA_toStr(Dz1Asn1DateTime *src, Dz1Error *err) { return Dz1Asn1TimeA_toStr(src, err); }
static __inline__ void						 Dz1Asn1DateTimeA_dump(Dz1Asn1DateTime *p, int tab) { Dz1Asn1TimeA_dump(p, tab); }
static __inline__ void						 Dz1Asn1DateTimeA_fdump(FILE *fp, Dz1Asn1DateTime *p, int tab) { Dz1Asn1TimeA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ Dz1Asn1DateTime			*Dz1Asn1DateTimeW_newFromStr(wstr_t iso8601_datetime_formatted_str, Dz1Error *err) { return Dz1Asn1TimeW_newFromStr(iso8601_datetime_formatted_str, err); }
static __inline__ wstr_t					 Dz1Asn1DateTimeW_toStr(Dz1Asn1DateTime *src, Dz1Error *err) { return Dz1Asn1TimeW_toStr(src, err); }
static __inline__ void						 Dz1Asn1DateTimeW_dump(Dz1Asn1DateTime *p, int tab) { Dz1Asn1TimeW_dump(p, tab); }
static __inline__ void						 Dz1Asn1DateTimeW_fdump(FILE *fp, Dz1Asn1DateTime *p, int tab) { Dz1Asn1TimeW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1DateTime_dump					Dz1Asn1DateTimeW_dump
#define										 Dz1Asn1DateTime_fdump					Dz1Asn1DateTimeW_fdump
#define										 Dz1Asn1DateTime_toStr					Dz1Asn1DateTimeW_toStr
#else // UNICODE
#define										 Dz1Asn1DateTime_dump					Dz1Asn1DateTimeA_dump
#define										 Dz1Asn1DateTime_fdump					Dz1Asn1DateTimeA_fdump
#define										 Dz1Asn1DateTime_toStr					Dz1Asn1DateTimeA_toStr
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1DateTime_dump					Dz1Asn1DateTimeA_dump
#define										 Dz1Asn1DateTime_fdump					Dz1Asn1DateTimeA_fdump
#define										 Dz1Asn1DateTime_toStr					Dz1Asn1DateTimeA_toStr
#endif
// ASN.1 DATE TIME (33) : ISO-8601 Simple String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 DURATION (34) : ISO-8601 Simple String
typedef Dz1Asn1Time Dz1Asn1Duration;
// No new functions
#define										 Dz1Asn1Duration_gen(ep)				_Dz1Asn1Duration_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Duration		   *_Dz1Asn1Duration_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1Duration		  *__Dz1Asn1Duration_gen(Dz1Error *err) { return Dz1Asn1Duration_gen(err); }
#define										 Dz1Asn1Duration_clone(sp, ep)			_Dz1Asn1Duration_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Duration		   *_Dz1Asn1Duration_clone(Dz1Asn1Duration *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1Duration		  *__Dz1Asn1Duration_clone(Dz1Asn1Duration *src, Dz1Error *err) { return Dz1Asn1OctetStr_clone(src, err); }
static __inline__ void						 Dz1Asn1Duration_del(Dz1Asn1Duration *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1Duration_delAndSetNull			Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1Duration_cmp(Dz1Asn1Duration *a, Dz1Asn1Duration *b) { return Dz1Asn1OctetStr_cmp(a, b); }

static __inline__ Dz1Asn1Duration			*Dz1Asn1DurationA_newFromStr(str_t iso8601_dur_formatted_str, Dz1Error *err) { return Dz1Asn1TimeA_newFromStr(iso8601_dur_formatted_str, err); }
static __inline__ str_t						 Dz1Asn1DurationA_toStr(Dz1Asn1Duration *src, Dz1Error *err) { return Dz1Asn1TimeA_toStr(src, err); }
static __inline__ void						 Dz1Asn1DurationA_dump(Dz1Asn1Duration *p, int tab) { Dz1Asn1TimeA_dump(p, tab); }
static __inline__ void						 Dz1Asn1DurationA_fdump(FILE *fp, Dz1Asn1Duration *p, int tab) { Dz1Asn1TimeA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ Dz1Asn1Duration			*Dz1Asn1DurationW_newFromStr(wstr_t iso8601_dur_formatted_str, Dz1Error *err) { return Dz1Asn1TimeW_newFromStr(iso8601_dur_formatted_str, err); }
static __inline__ wstr_t					 Dz1Asn1DurationW_toStr(Dz1Asn1Duration *src, Dz1Error *err) { return Dz1Asn1TimeW_toStr(src, err); }
static __inline__ void						 Dz1Asn1DurationW_dump(Dz1Asn1Duration *p, int tab) { Dz1Asn1TimeW_dump(p, tab); }
static __inline__ void						 Dz1Asn1DurationW_fdump(FILE *fp, Dz1Asn1Duration *p, int tab) { Dz1Asn1TimeW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1Duration_dump					Dz1Asn1DurationW_dump
#define										 Dz1Asn1Duration_fdump					Dz1Asn1DurationW_fdump
#define										 Dz1Asn1Duration_toStr					Dz1Asn1DurationW_toStr
#else // UNICODE
#define										 Dz1Asn1Duration_dump					Dz1Asn1DurationA_dump
#define										 Dz1Asn1Duration_fdump					Dz1Asn1DurationA_fdump
#define										 Dz1Asn1Duration_toStr					Dz1Asn1DurationA_toStr
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Duration_dump					Dz1Asn1DurationA_dump
#define										 Dz1Asn1Duration_fdump					Dz1Asn1DurationA_fdump
#define										 Dz1Asn1Duration_toStr					Dz1Asn1DurationA_toStr
#endif
// ASN.1 DATE TIME (33) : ISO-8601 Simple String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 ANY
struct Dz1Asn1OctetStr;
typedef struct Dz1Asn1OctetStr Dz1Asn1Any;
#define										 Dz1Asn1Any_new(dp, sz, ep)				_Dz1Asn1Any_new(dp, sz, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Any			   *_Dz1Asn1Any_new(u8_t *data, u32_t size, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_new(data, size, err, __file, __line); }
#define										 Dz1Asn1Any_gen(ep)						_Dz1Asn1Any_gen(ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Any			   *_Dz1Asn1Any_gen(Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_gen(err, __file, __line); }
static __inline__ Dz1Asn1Any			  *__Dz1Asn1Any_gen(Dz1Error *err)			{ return Dz1Asn1Any_gen(err); }
#define										 Dz1Asn1Any_clone(sp, ep)				_Dz1Asn1Any_clone(sp, ep, __FILE__, __LINE__)
static __inline__ Dz1Asn1Any			   *_Dz1Asn1Any_clone(Dz1Asn1Any *src, Dz1Error *err, const char *__file, int __line) { return _Dz1Asn1OctetStr_clone(src, err, __file, __line); }
static __inline__ Dz1Asn1Any			  *__Dz1Asn1Any_clone(Dz1Asn1Any *src, Dz1Error *err) { return Dz1Asn1Any_clone(src, err); }
static __inline__ void						 Dz1Asn1Any_del(Dz1Asn1Any *p) { Dz1Asn1OctetStr_del(p); }
#define										 Dz1Asn1Any_delAndSetNull				Dz1Asn1OctetStr_delAndSetNull

static __inline__ int						 Dz1Asn1Any_cmp(Dz1Asn1Any *a, Dz1Asn1Any *b) { return Dz1Asn1OctetStr_cmp(a, b); }

static __inline__ void						 Dz1Asn1AnyA_dump(Dz1Asn1Any *p, int tab) { Dz1Asn1OctetStrA_dump(p, tab); }
static __inline__ void						 Dz1Asn1AnyA_fdump(FILE *fp, Dz1Asn1Any *p, int tab) { Dz1Asn1OctetStrA_fdump(fp, p, tab); }
#ifndef UNIX_SYSTEM
static __inline__ void						 Dz1Asn1AnyW_dump(Dz1Asn1Any *p, int tab) { Dz1Asn1OctetStrW_dump(p, tab); }
static __inline__ void						 Dz1Asn1AnyW_fdump(FILE *fp, Dz1Asn1Any *p, int tab) { Dz1Asn1OctetStrW_fdump(fp, p, tab); }
#ifdef UNICODE
#define										 Dz1Asn1Any_dump						Dz1Asn1OctetStrW_dump
#define										 Dz1Asn1Any_fdump						Dz1Asn1OctetStrW_fdump
#else // UNICODE
#define										 Dz1Asn1Any_dump						Dz1Asn1OctetStrA_dump
#define										 Dz1Asn1Any_fdump						Dz1Asn1OctetStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1Asn1Any_dump						Dz1Asn1OctetStrA_dump
#define										 Dz1Asn1Any_fdump						Dz1Asn1OctetStrA_fdump
#endif // UNIX_SYSTEM
// ASN.1 ANY
///////////////////////////////////////////////////////////////////////////////

#endif

