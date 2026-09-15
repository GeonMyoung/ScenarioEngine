#ifndef _DZ1_TDC_DZ1_JSON_DEF_H_
#define _DZ1_TDC_DZ1_JSON_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_io_stream_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonNewLine
typedef enum Dz1JsonNewLine
{
	Dz1JsonNewLine_continuous,
	Dz1JsonNewLine_cr,
	Dz1JsonNewLine_lf,
	Dz1JsonNewLine_crlf,
	Dz1JsonNewLine_max
} Dz1JsonNewLine;

DZ1_CPPLINK str_t Dz1JsonNewLineStrA(Dz1JsonNewLine v);
DZ1_CPPLINK Dz1JsonNewLine Dz1JsonNewLineFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonNewLineStrW(Dz1JsonNewLine v);
DZ1_CPPLINK Dz1JsonNewLine Dz1JsonNewLineFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonNewLineStr Dz1JsonNewLineStrW
#define Dz1JsonNewLineFromStr Dz1JsonNewLineFromStrW
#else // UNICODE
#define Dz1JsonNewLineStr Dz1JsonNewLineStrA
#define Dz1JsonNewLineFromStr Dz1JsonNewLineFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonNewLineStr Dz1JsonNewLineStrA
#define Dz1JsonNewLineFromStr Dz1JsonNewLineFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonNewLine *Dz1JsonNewLine_new(Dz1JsonNewLine *src, Dz1Error *err);
static __inline__ Dz1JsonNewLine *Dz1JsonNewLine_gen(Dz1Error *err) { Dz1JsonNewLine v = Dz1JsonNewLine_max; return Dz1JsonNewLine_new(&v, err); }
static __inline__ void Dz1JsonNewLine_del(Dz1JsonNewLine *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonNewLine_delAndSetNull(void *ptr)
{
	Dz1JsonNewLine **p = (Dz1JsonNewLine **)ptr;
	if (p != NULL) { Dz1JsonNewLine_del(*p); *p = NULL; }
}
// Dz1JsonNewLine
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonNewLineInfo
typedef struct Dz1JsonNewLineInfo
{
	Dz1Str		str;
	size_t		len;
	u32_t		tab;
} Dz1JsonNewLineInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonNewLineInfo *Dz1JsonNewLineInfo_new(Dz1Str str, 
																   size_t len, 
																   u32_t tab, Dz1Error *err);
static __inline__ Dz1JsonNewLineInfo *Dz1JsonNewLineInfo_gen(Dz1Error *err) { return Dz1JsonNewLineInfo_new(NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonNewLineInfo_purge(Dz1JsonNewLineInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonNewLineInfo_del(Dz1JsonNewLineInfo *p);
static __inline__ void Dz1JsonNewLineInfo_delAndSetNull(void *ptr)
{
	Dz1JsonNewLineInfo **p = (Dz1JsonNewLineInfo **)ptr;
	if (p) { Dz1JsonNewLineInfo_del(*p); *p = NULL; }
}
// Dz1JsonNewLineInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonObjGenF
typedef void *(*Dz1JsonObjGenF)(Dz1Error *err);
// Dz1JsonObjGenF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonObjDelF
typedef void (*Dz1JsonObjDelF)(void *obj_ptr);
// Dz1JsonObjDelF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonTokenType
typedef enum Dz1JsonTokenType
{
	Dz1JsonTokenType_comma,
	Dz1JsonTokenType_dot,
	Dz1JsonTokenType_white_space,
	Dz1JsonTokenType_lst_start,
	Dz1JsonTokenType_lst_end,
	Dz1JsonTokenType_blk_start,
	Dz1JsonTokenType_blk_end,
	Dz1JsonTokenType_colon,
	Dz1JsonTokenType_plus,
	Dz1JsonTokenType_minus,
	Dz1JsonTokenType_number,
	Dz1JsonTokenType_string,
	Dz1JsonTokenType_nul,
	Dz1JsonTokenType_symbol,
	Dz1JsonTokenType_max
} Dz1JsonTokenType;

DZ1_CPPLINK str_t Dz1JsonTokenTypeStrA(Dz1JsonTokenType v);
DZ1_CPPLINK Dz1JsonTokenType Dz1JsonTokenTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonTokenTypeStrW(Dz1JsonTokenType v);
DZ1_CPPLINK Dz1JsonTokenType Dz1JsonTokenTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonTokenTypeStr Dz1JsonTokenTypeStrW
#define Dz1JsonTokenTypeFromStr Dz1JsonTokenTypeFromStrW
#else // UNICODE
#define Dz1JsonTokenTypeStr Dz1JsonTokenTypeStrA
#define Dz1JsonTokenTypeFromStr Dz1JsonTokenTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonTokenTypeStr Dz1JsonTokenTypeStrA
#define Dz1JsonTokenTypeFromStr Dz1JsonTokenTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonTokenType *Dz1JsonTokenType_new(Dz1JsonTokenType *src, Dz1Error *err);
static __inline__ Dz1JsonTokenType *Dz1JsonTokenType_gen(Dz1Error *err) { Dz1JsonTokenType v = Dz1JsonTokenType_max; return Dz1JsonTokenType_new(&v, err); }
static __inline__ void Dz1JsonTokenType_del(Dz1JsonTokenType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonTokenType_delAndSetNull(void *ptr)
{
	Dz1JsonTokenType **p = (Dz1JsonTokenType **)ptr;
	if (p != NULL) { Dz1JsonTokenType_del(*p); *p = NULL; }
}
// Dz1JsonTokenType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonToken
typedef struct Dz1JsonToken
{
	Dz1JsonTokenType	t;
	Dz1Str				v;
} Dz1JsonToken;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonToken *Dz1JsonToken_new(Dz1JsonTokenType t, 
													   Dz1Str v, Dz1Error *err);
static __inline__ Dz1JsonToken *Dz1JsonToken_gen(Dz1Error *err) { return Dz1JsonToken_new(Dz1JsonTokenType_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonToken_copy(Dz1JsonToken *dst, Dz1JsonToken *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonToken *Dz1JsonToken_clone(Dz1JsonToken *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonToken_purge(Dz1JsonToken *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonToken_del(Dz1JsonToken *p);
static __inline__ void Dz1JsonToken_delAndSetNull(void *ptr)
{
	Dz1JsonToken **p = (Dz1JsonToken **)ptr;
	if (p) { Dz1JsonToken_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonToken_dump(Dz1JsonToken *p, int tab);
// Dz1JsonToken
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// _declare_Dz1JsonVarBind
struct Dz1JsonVarBind;
// _declare_Dz1JsonVarBind
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecPrimitiveStringifyF
typedef bool_t (*Dz1JsonSpecPrimitiveStringifyF)(void *obj, Dz1ElasticBuf *buf, Dz1Error *err);
// Dz1JsonSpecPrimitiveStringifyF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecPrimitiveLoaderF
typedef bool_t (*Dz1JsonSpecPrimitiveLoaderF)(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err);
// Dz1JsonSpecPrimitiveLoaderF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecPrimitive
struct Dz1JsonSpecEntry;

typedef struct Dz1JsonSpecPrimitive
{
	struct Dz1JsonSpecEntry				*owner;
	Dz1JsonSpecPrimitiveLoaderF			 loader;
	Dz1JsonSpecPrimitiveStringifyF		 stringify;
} Dz1JsonSpecPrimitive;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecPrimitive *Dz1JsonSpecPrimitive_new(struct Dz1JsonSpecEntry *owner_ref, 
																	   Dz1JsonSpecPrimitiveLoaderF loader, 
																	   Dz1JsonSpecPrimitiveStringifyF stringify, Dz1Error *err);
static __inline__ Dz1JsonSpecPrimitive *Dz1JsonSpecPrimitive_gen(Dz1Error *err) { return Dz1JsonSpecPrimitive_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonSpecPrimitive_copy(Dz1JsonSpecPrimitive *dst, Dz1JsonSpecPrimitive *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecPrimitive *Dz1JsonSpecPrimitive_clone(Dz1JsonSpecPrimitive *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecPrimitive_purge(Dz1JsonSpecPrimitive *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecPrimitive_del(Dz1JsonSpecPrimitive *p);
static __inline__ void Dz1JsonSpecPrimitive_delAndSetNull(void *ptr)
{
	Dz1JsonSpecPrimitive **p = (Dz1JsonSpecPrimitive **)ptr;
	if (p) { Dz1JsonSpecPrimitive_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecPrimitive_dump(Dz1JsonSpecPrimitive *p, int tab);
// Dz1JsonSpecPrimitive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecChild
typedef struct Dz1JsonSpecChild
{
	Dz1Str		name;
	Dz1Str		type;
	u32_t		index;
} Dz1JsonSpecChild;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecChild *Dz1JsonSpecChild_new(Dz1Str name, 
															   Dz1Str type, 
															   u32_t index, Dz1Error *err);
static __inline__ Dz1JsonSpecChild *Dz1JsonSpecChild_gen(Dz1Error *err) { return Dz1JsonSpecChild_new(NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonSpecChild_copy(Dz1JsonSpecChild *dst, Dz1JsonSpecChild *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecChild *Dz1JsonSpecChild_clone(Dz1JsonSpecChild *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecChild_purge(Dz1JsonSpecChild *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecChild_del(Dz1JsonSpecChild *p);
static __inline__ void Dz1JsonSpecChild_delAndSetNull(void *ptr)
{
	Dz1JsonSpecChild **p = (Dz1JsonSpecChild **)ptr;
	if (p) { Dz1JsonSpecChild_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecChild_dump(Dz1JsonSpecChild *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1JsonSpecChild_cmp(Dz1JsonSpecChild *a, Dz1JsonSpecChild *b); 
// Dz1JsonSpecChild
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecChilds
typedef struct Dz1JsonSpecChilds
{
	void *storage;
	unsigned int (*count)(struct Dz1JsonSpecChilds *p);
	Dz1Error (*travel)(struct Dz1JsonSpecChilds *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecChild *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1JsonSpecChilds *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecChild *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1JsonSpecChilds *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecChild *entry), void *ptr);
	Dz1JsonSpecChild **(*get_array)(struct Dz1JsonSpecChilds *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1JsonSpecChilds *p, Dz1JsonSpecChild *data);
	bool_t (*remove)(struct Dz1JsonSpecChilds *p, Dz1JsonSpecChild *key);
	Dz1JsonSpecChild *(*extract)(struct Dz1JsonSpecChilds *p, Dz1JsonSpecChild *key);
	Dz1JsonSpecChild *(*find)(struct Dz1JsonSpecChilds *p, Dz1JsonSpecChild *key);
	int (*cmp)(Dz1JsonSpecChild *a, Dz1JsonSpecChild *b);
} Dz1JsonSpecChilds;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecChilds *Dz1JsonSpecChilds_new(Dz1Error *err);
static __inline__ Dz1JsonSpecChilds *Dz1JsonSpecChilds_gen(Dz1Error *err) { return Dz1JsonSpecChilds_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecChilds *Dz1JsonSpecChilds_clone(Dz1JsonSpecChilds *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecChilds_purge(Dz1JsonSpecChilds *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecChilds_del(Dz1JsonSpecChilds *p);
static __inline__ void Dz1JsonSpecChilds_delAndSetNull(void *ptr)
{
	Dz1JsonSpecChilds **p = (Dz1JsonSpecChilds **)ptr;
	if (p != NULL) { Dz1JsonSpecChilds_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecChilds_dump(Dz1JsonSpecChilds *p, int tab);

// Dz1JsonSpecChilds
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonConstructType
typedef enum Dz1JsonConstructType
{
	Dz1JsonConstructType_struct,
	Dz1JsonConstructType_union,
	Dz1JsonConstructType_max
} Dz1JsonConstructType;

DZ1_CPPLINK str_t Dz1JsonConstructTypeStrA(Dz1JsonConstructType v);
DZ1_CPPLINK Dz1JsonConstructType Dz1JsonConstructTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonConstructTypeStrW(Dz1JsonConstructType v);
DZ1_CPPLINK Dz1JsonConstructType Dz1JsonConstructTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonConstructTypeStr Dz1JsonConstructTypeStrW
#define Dz1JsonConstructTypeFromStr Dz1JsonConstructTypeFromStrW
#else // UNICODE
#define Dz1JsonConstructTypeStr Dz1JsonConstructTypeStrA
#define Dz1JsonConstructTypeFromStr Dz1JsonConstructTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonConstructTypeStr Dz1JsonConstructTypeStrA
#define Dz1JsonConstructTypeFromStr Dz1JsonConstructTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonConstructType *Dz1JsonConstructType_new(Dz1JsonConstructType *src, Dz1Error *err);
static __inline__ Dz1JsonConstructType *Dz1JsonConstructType_gen(Dz1Error *err) { Dz1JsonConstructType v = Dz1JsonConstructType_max; return Dz1JsonConstructType_new(&v, err); }
static __inline__ void Dz1JsonConstructType_del(Dz1JsonConstructType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonConstructType_delAndSetNull(void *ptr)
{
	Dz1JsonConstructType **p = (Dz1JsonConstructType **)ptr;
	if (p != NULL) { Dz1JsonConstructType_del(*p); *p = NULL; }
}
// Dz1JsonConstructType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonConstructSetChildF
typedef bool_t (*Dz1JsonConstructSetChildF)(void *parent_ptr, struct Dz1JsonVarBind *info, Dz1Error *err);
// Dz1JsonConstructSetChildF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonConstructGetChildF
typedef void *(*Dz1JsonConstructGetChildF)(void *parent_ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists);
// Dz1JsonConstructGetChildF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecConstruct
struct Dz1JsonSpecEntry;

typedef struct Dz1JsonSpecConstruct
{
	struct Dz1JsonSpecEntry			*owner;
	Dz1JsonSpecChilds				*childs;
	Dz1JsonConstructType			 type;
	Dz1JsonConstructSetChildF		 set_child;
	Dz1JsonConstructGetChildF		 get_child;
} Dz1JsonSpecConstruct;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecConstruct *Dz1JsonSpecConstruct_new(struct Dz1JsonSpecEntry *owner_ref, 
																	   Dz1JsonConstructType type, 
																	   Dz1JsonConstructSetChildF set_child, 
																	   Dz1JsonConstructGetChildF get_child, Dz1Error *err);
static __inline__ Dz1JsonSpecConstruct *Dz1JsonSpecConstruct_gen(Dz1Error *err) { return Dz1JsonSpecConstruct_new(NULL, Dz1JsonConstructType_max, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonSpecConstruct_copy(Dz1JsonSpecConstruct *dst, Dz1JsonSpecConstruct *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecConstruct *Dz1JsonSpecConstruct_clone(Dz1JsonSpecConstruct *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecConstruct_purge(Dz1JsonSpecConstruct *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecConstruct_del(Dz1JsonSpecConstruct *p);
static __inline__ void Dz1JsonSpecConstruct_delAndSetNull(void *ptr)
{
	Dz1JsonSpecConstruct **p = (Dz1JsonSpecConstruct **)ptr;
	if (p) { Dz1JsonSpecConstruct_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecConstruct_dump(Dz1JsonSpecConstruct *p, int tab);
// Dz1JsonSpecConstruct
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonArrayAppendF
typedef bool_t (*Dz1JsonArrayAppendF)(void *dst, struct Dz1JsonVarBind *var, Dz1Error *err);
// Dz1JsonArrayAppendF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonArrayCountF
typedef u32_t (*Dz1JsonArrayCountF)(void *obj);
// Dz1JsonArrayCountF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonArrayEntryF
typedef Dz1Error (*Dz1JsonArrayEntryF)(void *arg, void *node_obj);
// Dz1JsonArrayEntryF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonArrayTravelF
typedef Dz1Error (*Dz1JsonArrayTravelF)(void *obj, Dz1JsonArrayEntryF f, void *arg);
// Dz1JsonArrayTravelF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecArray
struct Dz1JsonSpecEntry;

typedef struct Dz1JsonSpecArray
{
	struct Dz1JsonSpecEntry		*owner;
	Dz1Str						 elem_type;
	Dz1JsonArrayAppendF			 append;
	Dz1JsonArrayCountF			 count;
	Dz1JsonArrayTravelF			 travel;
} Dz1JsonSpecArray;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecArray *Dz1JsonSpecArray_new(struct Dz1JsonSpecEntry *owner_ref, 
															   Dz1Str elem_type, 
															   Dz1JsonArrayAppendF append, 
															   Dz1JsonArrayCountF count, 
															   Dz1JsonArrayTravelF travel, Dz1Error *err);
static __inline__ Dz1JsonSpecArray *Dz1JsonSpecArray_gen(Dz1Error *err) { return Dz1JsonSpecArray_new(NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonSpecArray_copy(Dz1JsonSpecArray *dst, Dz1JsonSpecArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecArray *Dz1JsonSpecArray_clone(Dz1JsonSpecArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecArray_purge(Dz1JsonSpecArray *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecArray_del(Dz1JsonSpecArray *p);
static __inline__ void Dz1JsonSpecArray_delAndSetNull(void *ptr)
{
	Dz1JsonSpecArray **p = (Dz1JsonSpecArray **)ptr;
	if (p) { Dz1JsonSpecArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecArray_dump(Dz1JsonSpecArray *p, int tab);
// Dz1JsonSpecArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecDataPresent
typedef enum Dz1JsonSpecDataPresent
{
	Dz1JsonSpecDataPresent_pr,
	Dz1JsonSpecDataPresent_cst,
	Dz1JsonSpecDataPresent_ar,
	Dz1JsonSpecDataPresent_max
} Dz1JsonSpecDataPresent;

DZ1_CPPLINK str_t Dz1JsonSpecDataPresentStrA(Dz1JsonSpecDataPresent v);
DZ1_CPPLINK Dz1JsonSpecDataPresent Dz1JsonSpecDataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonSpecDataPresentStrW(Dz1JsonSpecDataPresent v);
DZ1_CPPLINK Dz1JsonSpecDataPresent Dz1JsonSpecDataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonSpecDataPresentStr Dz1JsonSpecDataPresentStrW
#define Dz1JsonSpecDataPresentFromStr Dz1JsonSpecDataPresentFromStrW
#else // UNICODE
#define Dz1JsonSpecDataPresentStr Dz1JsonSpecDataPresentStrA
#define Dz1JsonSpecDataPresentFromStr Dz1JsonSpecDataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonSpecDataPresentStr Dz1JsonSpecDataPresentStrA
#define Dz1JsonSpecDataPresentFromStr Dz1JsonSpecDataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecDataPresent *Dz1JsonSpecDataPresent_new(Dz1JsonSpecDataPresent *src, Dz1Error *err);
static __inline__ Dz1JsonSpecDataPresent *Dz1JsonSpecDataPresent_gen(Dz1Error *err) { Dz1JsonSpecDataPresent v = Dz1JsonSpecDataPresent_max; return Dz1JsonSpecDataPresent_new(&v, err); }
#define Dz1JsonSpecDataPresent_clone             Dz1JsonSpecDataPresent_new
static __inline__ void Dz1JsonSpecDataPresent_del(Dz1JsonSpecDataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonSpecDataPresent_delAndSetNull(void *ptr)
{
	Dz1JsonSpecDataPresent **p = (Dz1JsonSpecDataPresent **)ptr;
	if (p != NULL) { Dz1JsonSpecDataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecDataPresent_dump(Dz1JsonSpecDataPresent *v, int tab);
// Dz1JsonSpecDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecData
typedef struct Dz1JsonSpecData
{
	Dz1JsonSpecDataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1JsonSpecPrimitive	*pr;
		Dz1JsonSpecConstruct	*cst;
		Dz1JsonSpecArray		*ar;
	} x;
} Dz1JsonSpecData;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecData *Dz1JsonSpecData_new(Dz1JsonSpecDataPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1JsonSpecData *Dz1JsonSpecData_gen(Dz1Error *err) { return Dz1JsonSpecData_new(Dz1JsonSpecDataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1JsonSpecData_copy(Dz1JsonSpecData *dst, Dz1JsonSpecData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecData *Dz1JsonSpecData_clone(Dz1JsonSpecData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecData_purge(Dz1JsonSpecData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecData_del(Dz1JsonSpecData *p);
static __inline__ void Dz1JsonSpecData_delAndSetNull(void *ptr)
{
	Dz1JsonSpecData **p = (Dz1JsonSpecData **)ptr;
	if (p != NULL) { Dz1JsonSpecData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecData_dump(Dz1JsonSpecData *p, int tab);
// Dz1JsonSpecData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecEntry
typedef struct Dz1JsonSpecEntry
{
	Dz1Str				 name;
	Dz1JsonObjGenF		 gen;
	Dz1JsonObjDelF		 del;
	Dz1JsonSpecData		*data;
} Dz1JsonSpecEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecEntry *Dz1JsonSpecEntry_new(Dz1Str name, 
															   Dz1JsonObjGenF gen, 
															   Dz1JsonObjDelF del, 
															   Dz1JsonSpecData *data, Dz1Error *err);
static __inline__ Dz1JsonSpecEntry *Dz1JsonSpecEntry_gen(Dz1Error *err) { return Dz1JsonSpecEntry_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonSpecEntry_copy(Dz1JsonSpecEntry *dst, Dz1JsonSpecEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecEntry *Dz1JsonSpecEntry_clone(Dz1JsonSpecEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecEntry_purge(Dz1JsonSpecEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecEntry_del(Dz1JsonSpecEntry *p);
static __inline__ void Dz1JsonSpecEntry_delAndSetNull(void *ptr)
{
	Dz1JsonSpecEntry **p = (Dz1JsonSpecEntry **)ptr;
	if (p) { Dz1JsonSpecEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecEntry_dump(Dz1JsonSpecEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1JsonSpecEntry_cmp(Dz1JsonSpecEntry *a, Dz1JsonSpecEntry *b); 
// Dz1JsonSpecEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecList
typedef struct Dz1JsonSpecList
{
	void *storage;
	unsigned int (*count)(struct Dz1JsonSpecList *p);
	Dz1Error (*travel)(struct Dz1JsonSpecList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1JsonSpecList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1JsonSpecList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *entry), void *ptr);
	Dz1JsonSpecEntry **(*get_array)(struct Dz1JsonSpecList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1JsonSpecList *p, Dz1JsonSpecEntry *data);
	bool_t (*remove)(struct Dz1JsonSpecList *p, Dz1JsonSpecEntry *key);
	Dz1JsonSpecEntry *(*extract)(struct Dz1JsonSpecList *p, Dz1JsonSpecEntry *key);
	Dz1JsonSpecEntry *(*find)(struct Dz1JsonSpecList *p, Dz1JsonSpecEntry *key);
	int (*cmp)(Dz1JsonSpecEntry *a, Dz1JsonSpecEntry *b);
} Dz1JsonSpecList;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecList *Dz1JsonSpecList_new(Dz1Error *err);
static __inline__ Dz1JsonSpecList *Dz1JsonSpecList_gen(Dz1Error *err) { return Dz1JsonSpecList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecList *Dz1JsonSpecList_clone(Dz1JsonSpecList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecList_purge(Dz1JsonSpecList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecList_del(Dz1JsonSpecList *p);
static __inline__ void Dz1JsonSpecList_delAndSetNull(void *ptr)
{
	Dz1JsonSpecList **p = (Dz1JsonSpecList **)ptr;
	if (p != NULL) { Dz1JsonSpecList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecList_dump(Dz1JsonSpecList *p, int tab);

// Dz1JsonSpecList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec
typedef struct Dz1JsonSpec
{
	Dz1JsonSpecList		*types;
} Dz1JsonSpec;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpec *Dz1JsonSpec_new(Dz1Error *err);
static __inline__ Dz1JsonSpec *Dz1JsonSpec_gen(Dz1Error *err) { return Dz1JsonSpec_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpec_purge(Dz1JsonSpec *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpec_del(Dz1JsonSpec *p);
static __inline__ void Dz1JsonSpec_delAndSetNull(void *ptr)
{
	Dz1JsonSpec **p = (Dz1JsonSpec **)ptr;
	if (p) { Dz1JsonSpec_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpec_dump(Dz1JsonSpec *p, int tab);
// Dz1JsonSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonVarBind
typedef struct Dz1JsonVarBind
{
	Dz1JsonSpecChild	*id;
	Dz1JsonSpecEntry	*type;
	void				*data;
} Dz1JsonVarBind;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonVarBind *Dz1JsonVarBind_new(Dz1JsonSpecChild *id_ref, 
														   Dz1JsonSpecEntry *type_ref, 
														   void *data, Dz1Error *err);
static __inline__ Dz1JsonVarBind *Dz1JsonVarBind_gen(Dz1Error *err) { return Dz1JsonVarBind_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonVarBind_purge(Dz1JsonVarBind *p);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonVarBind_del(Dz1JsonVarBind *p);	// User Customized
static __inline__ void Dz1JsonVarBind_delAndSetNull(void *ptr)
{
	Dz1JsonVarBind **p = (Dz1JsonVarBind **)ptr;
	if (p) { Dz1JsonVarBind_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonVarBind_dump(Dz1JsonVarBind *p, int tab);
// Dz1JsonVarBind
////////////////////////////////////////////////////////////////////////////////

#endif
