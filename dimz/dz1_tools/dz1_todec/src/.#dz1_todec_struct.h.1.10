#ifndef _DZ1_TDC_DZ1_TODEC_STRUCT_H_
#define _DZ1_TDC_DZ1_TODEC_STRUCT_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_todecDef.h"
#include "Dz1TdcInfoModule.h"

////////////////////////////////////////////////////////////////////////////////
// PointerNodeEntry
typedef struct PointerNodeEntry
{
	u32_t			 idx;
	ObjectInfo		*obj;
	str_t			 name;
} PointerNodeEntry;

DZ1_CPPLINK DZ1_DLLPORT PointerNodeEntry *PointerNodeEntry_new(u32_t idx, 
															   ObjectInfo *obj_ref, 
															   str_t name, Dz1Error *err);
static __inline__ PointerNodeEntry *PointerNodeEntry_gen(Dz1Error *err) { return PointerNodeEntry_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t PointerNodeEntry_copy(PointerNodeEntry *dst, PointerNodeEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT PointerNodeEntry *PointerNodeEntry_clone(PointerNodeEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PointerNodeEntry_purge(PointerNodeEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void PointerNodeEntry_del(PointerNodeEntry *p);
static __inline__ void PointerNodeEntry_delAndSetNull(void *ptr)
{
	PointerNodeEntry **p = (PointerNodeEntry **)ptr;
	if (p) { PointerNodeEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PointerNodeEntry_dump(PointerNodeEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int PointerNodeEntry_cmp(PointerNodeEntry *a, PointerNodeEntry *b); 
// PointerNodeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PointerNodeList
typedef struct PointerNodeList
{
	void *storage;
	unsigned int (*count)(struct PointerNodeList *p);
	Dz1Error (*travel)(struct PointerNodeList *p, Dz1Error (*func)(void *ptr, PointerNodeEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct PointerNodeList *p, Dz1Error (*func)(void *ptr, PointerNodeEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct PointerNodeList *p, Dz1Error (*func)(void *ptr, PointerNodeEntry *entry), void *ptr);
	PointerNodeEntry **(*get_array)(struct PointerNodeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct PointerNodeList *p, PointerNodeEntry *data);
	bool_t (*remove)(struct PointerNodeList *p, PointerNodeEntry *key);
	PointerNodeEntry *(*extract)(struct PointerNodeList *p, PointerNodeEntry *key);
	PointerNodeEntry *(*find)(struct PointerNodeList *p, PointerNodeEntry *key);
	int (*cmp)(PointerNodeEntry *a, PointerNodeEntry *b);
} PointerNodeList;

DZ1_CPPLINK DZ1_DLLPORT PointerNodeList *PointerNodeList_new(Dz1Error *err);
static __inline__ PointerNodeList *PointerNodeList_gen(Dz1Error *err) { return PointerNodeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT PointerNodeList *PointerNodeList_clone(PointerNodeList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void PointerNodeList_purge(PointerNodeList *p);
DZ1_CPPLINK DZ1_DLLPORT void PointerNodeList_del(PointerNodeList *p);
static __inline__ void PointerNodeList_delAndSetNull(void *ptr)
{
	PointerNodeList **p = (PointerNodeList **)ptr;
	if (p != NULL) { PointerNodeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void PointerNodeList_dump(PointerNodeList *p, int tab);

// PointerNodeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementSimplePartial
typedef struct StreamElementSimplePartial
{
	str_t				byte_tp;
	Dz1TodecUnitSize	byte_sz;
	str_t				dst_tp;
	str_t				mask;
	s32_t				shf;
} StreamElementSimplePartial;

DZ1_CPPLINK DZ1_DLLPORT StreamElementSimplePartial *StreamElementSimplePartial_new(str_t byte_tp, 
																				   Dz1TodecUnitSize byte_sz, 
																				   str_t dst_tp, 
																				   str_t mask, 
																				   s32_t shf, Dz1Error *err);
static __inline__ StreamElementSimplePartial *StreamElementSimplePartial_gen(Dz1Error *err) { return StreamElementSimplePartial_new(NULL, Dz1TodecUnitSize_max, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamElementSimplePartial_copy(StreamElementSimplePartial *dst, StreamElementSimplePartial *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementSimplePartial *StreamElementSimplePartial_clone(StreamElementSimplePartial *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimplePartial_purge(StreamElementSimplePartial *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimplePartial_del(StreamElementSimplePartial *p);
static __inline__ void StreamElementSimplePartial_delAndSetNull(void *ptr)
{
	StreamElementSimplePartial **p = (StreamElementSimplePartial **)ptr;
	if (p) { StreamElementSimplePartial_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimplePartial_dump(StreamElementSimplePartial *p, int tab);
// StreamElementSimplePartial
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementSimpleMethodPresent
typedef enum StreamElementSimpleMethodPresent
{
	StreamElementSimpleMethodPresent_def,
	StreamElementSimpleMethodPresent_part,
	StreamElementSimpleMethodPresent_restricted,
	StreamElementSimpleMethodPresent_alter,
	StreamElementSimpleMethodPresent_max
} StreamElementSimpleMethodPresent;

DZ1_CPPLINK str_t StreamElementSimpleMethodPresentStrA(StreamElementSimpleMethodPresent v);
DZ1_CPPLINK StreamElementSimpleMethodPresent StreamElementSimpleMethodPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t StreamElementSimpleMethodPresentStrW(StreamElementSimpleMethodPresent v);
DZ1_CPPLINK StreamElementSimpleMethodPresent StreamElementSimpleMethodPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define StreamElementSimpleMethodPresentStr StreamElementSimpleMethodPresentStrW
#define StreamElementSimpleMethodPresentFromStr StreamElementSimpleMethodPresentFromStrW
#else // UNICODE
#define StreamElementSimpleMethodPresentStr StreamElementSimpleMethodPresentStrA
#define StreamElementSimpleMethodPresentFromStr StreamElementSimpleMethodPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define StreamElementSimpleMethodPresentStr StreamElementSimpleMethodPresentStrA
#define StreamElementSimpleMethodPresentFromStr StreamElementSimpleMethodPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT StreamElementSimpleMethodPresent *StreamElementSimpleMethodPresent_new(StreamElementSimpleMethodPresent *src, Dz1Error *err);
static __inline__ StreamElementSimpleMethodPresent *StreamElementSimpleMethodPresent_gen(Dz1Error *err) { StreamElementSimpleMethodPresent v = StreamElementSimpleMethodPresent_max; return StreamElementSimpleMethodPresent_new(&v, err); }
#define StreamElementSimpleMethodPresent_clone             StreamElementSimpleMethodPresent_new
static __inline__ void StreamElementSimpleMethodPresent_del(StreamElementSimpleMethodPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void StreamElementSimpleMethodPresent_delAndSetNull(void *ptr)
{
	StreamElementSimpleMethodPresent **p = (StreamElementSimpleMethodPresent **)ptr;
	if (p != NULL) { StreamElementSimpleMethodPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimpleMethodPresent_dump(StreamElementSimpleMethodPresent *v, int tab);
// StreamElementSimpleMethodPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementSimpleMethod
typedef struct StreamElementSimpleMethod
{
	StreamElementSimpleMethodPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t							*def;
		StreamElementSimplePartial		*part;
		Dz1TodecRestrictDescr			*restricted;
		str_t							 alter;
	} x;
} StreamElementSimpleMethod;

DZ1_CPPLINK DZ1_DLLPORT StreamElementSimpleMethod *StreamElementSimpleMethod_new(StreamElementSimpleMethodPresent present, void *ptr, Dz1Error *err);
static __inline__ StreamElementSimpleMethod *StreamElementSimpleMethod_gen(Dz1Error *err) { return StreamElementSimpleMethod_new(StreamElementSimpleMethodPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  StreamElementSimpleMethod_copy(StreamElementSimpleMethod *dst, StreamElementSimpleMethod *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementSimpleMethod *StreamElementSimpleMethod_clone(StreamElementSimpleMethod *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimpleMethod_purge(StreamElementSimpleMethod *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimpleMethod_del(StreamElementSimpleMethod *p);
static __inline__ void StreamElementSimpleMethod_delAndSetNull(void *ptr)
{
	StreamElementSimpleMethod **p = (StreamElementSimpleMethod **)ptr;
	if (p != NULL) { StreamElementSimpleMethod_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimpleMethod_dump(StreamElementSimpleMethod *p, int tab);
// StreamElementSimpleMethod
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementVariable
typedef struct StreamElementVariable
{
	ObjectInfo			*target;
	ObjectInfo			*origin;
	ObjectInfo			*mother;
	PointerNodeList		*ptrs;
	str_t				 variable;
	bool_t				 var_is_ptr;
	str_t				 instance;
} StreamElementVariable;

DZ1_CPPLINK DZ1_DLLPORT StreamElementVariable *StreamElementVariable_new(ObjectInfo *target_ref, 
																		 ObjectInfo *origin_ref, 
																		 ObjectInfo *mother_ref, 
																		 str_t variable, 
																		 bool_t var_is_ptr, 
																		 str_t instance, Dz1Error *err);
static __inline__ StreamElementVariable *StreamElementVariable_gen(Dz1Error *err) { return StreamElementVariable_new(NULL, NULL, NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamElementVariable_copy(StreamElementVariable *dst, StreamElementVariable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementVariable *StreamElementVariable_clone(StreamElementVariable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementVariable_purge(StreamElementVariable *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementVariable_del(StreamElementVariable *p);
static __inline__ void StreamElementVariable_delAndSetNull(void *ptr)
{
	StreamElementVariable **p = (StreamElementVariable **)ptr;
	if (p) { StreamElementVariable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementVariable_dump(StreamElementVariable *p, int tab);
// StreamElementVariable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementSimple
typedef struct StreamElementSimple
{
	StreamElementVariable			*var;
	StreamElementSimpleMethod		*met;
	Dz1TodecUnitSize				 nul_flag;
	str_t							 postfix;
} StreamElementSimple;

DZ1_CPPLINK DZ1_DLLPORT StreamElementSimple *StreamElementSimple_new(StreamElementVariable *var, 
																	 StreamElementSimpleMethod *met, 
																	 Dz1TodecUnitSize nul_flag, 
																	 str_t postfix, Dz1Error *err);
static __inline__ StreamElementSimple *StreamElementSimple_gen(Dz1Error *err) { return StreamElementSimple_new(NULL, NULL, Dz1TodecUnitSize_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamElementSimple_copy(StreamElementSimple *dst, StreamElementSimple *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementSimple *StreamElementSimple_clone(StreamElementSimple *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimple_purge(StreamElementSimple *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimple_del(StreamElementSimple *p);
static __inline__ void StreamElementSimple_delAndSetNull(void *ptr)
{
	StreamElementSimple **p = (StreamElementSimple **)ptr;
	if (p) { StreamElementSimple_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementSimple_dump(StreamElementSimple *p, int tab);
// StreamElementSimple
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementConditional
typedef struct StreamElementConditional
{
	StreamElementVariable			*var;
	str_t							 decider;
	StreamElementSimpleMethod		*met;
	str_t							 postfix;
} StreamElementConditional;

DZ1_CPPLINK DZ1_DLLPORT StreamElementConditional *StreamElementConditional_new(StreamElementVariable *var, 
																			   str_t decider, 
																			   StreamElementSimpleMethod *met, 
																			   str_t postfix, Dz1Error *err);
static __inline__ StreamElementConditional *StreamElementConditional_gen(Dz1Error *err) { return StreamElementConditional_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamElementConditional_copy(StreamElementConditional *dst, StreamElementConditional *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementConditional *StreamElementConditional_clone(StreamElementConditional *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementConditional_purge(StreamElementConditional *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementConditional_del(StreamElementConditional *p);
static __inline__ void StreamElementConditional_delAndSetNull(void *ptr)
{
	StreamElementConditional **p = (StreamElementConditional **)ptr;
	if (p) { StreamElementConditional_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementConditional_dump(StreamElementConditional *p, int tab);
// StreamElementConditional
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementBitInfo
typedef struct StreamElementBitInfo
{
	StreamElementVariable		*var;
	Dz1TodecBitDescr			*met;
} StreamElementBitInfo;

DZ1_CPPLINK DZ1_DLLPORT StreamElementBitInfo *StreamElementBitInfo_new(StreamElementVariable *var, 
																	   Dz1TodecBitDescr *met, Dz1Error *err);
static __inline__ StreamElementBitInfo *StreamElementBitInfo_gen(Dz1Error *err) { return StreamElementBitInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamElementBitInfo_copy(StreamElementBitInfo *dst, StreamElementBitInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementBitInfo *StreamElementBitInfo_clone(StreamElementBitInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBitInfo_purge(StreamElementBitInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBitInfo_del(StreamElementBitInfo *p);
static __inline__ void StreamElementBitInfo_delAndSetNull(void *ptr)
{
	StreamElementBitInfo **p = (StreamElementBitInfo **)ptr;
	if (p) { StreamElementBitInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBitInfo_dump(StreamElementBitInfo *p, int tab);
// StreamElementBitInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementBitPresent
typedef enum StreamElementBitPresent
{
	StreamElementBitPresent_data,
	StreamElementBitPresent_pad,
	StreamElementBitPresent_max
} StreamElementBitPresent;

DZ1_CPPLINK str_t StreamElementBitPresentStrA(StreamElementBitPresent v);
DZ1_CPPLINK StreamElementBitPresent StreamElementBitPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t StreamElementBitPresentStrW(StreamElementBitPresent v);
DZ1_CPPLINK StreamElementBitPresent StreamElementBitPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define StreamElementBitPresentStr StreamElementBitPresentStrW
#define StreamElementBitPresentFromStr StreamElementBitPresentFromStrW
#else // UNICODE
#define StreamElementBitPresentStr StreamElementBitPresentStrA
#define StreamElementBitPresentFromStr StreamElementBitPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define StreamElementBitPresentStr StreamElementBitPresentStrA
#define StreamElementBitPresentFromStr StreamElementBitPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT StreamElementBitPresent *StreamElementBitPresent_new(StreamElementBitPresent *src, Dz1Error *err);
static __inline__ StreamElementBitPresent *StreamElementBitPresent_gen(Dz1Error *err) { StreamElementBitPresent v = StreamElementBitPresent_max; return StreamElementBitPresent_new(&v, err); }
#define StreamElementBitPresent_clone             StreamElementBitPresent_new
static __inline__ void StreamElementBitPresent_del(StreamElementBitPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void StreamElementBitPresent_delAndSetNull(void *ptr)
{
	StreamElementBitPresent **p = (StreamElementBitPresent **)ptr;
	if (p != NULL) { StreamElementBitPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBitPresent_dump(StreamElementBitPresent *v, int tab);
// StreamElementBitPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementBit
typedef struct StreamElementBit
{
	StreamElementBitPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		StreamElementBitInfo	*data;
		u8_t					 pad;
	} x;
} StreamElementBit;

DZ1_CPPLINK DZ1_DLLPORT StreamElementBit *StreamElementBit_new(StreamElementBitPresent present, void *ptr, Dz1Error *err);
static __inline__ StreamElementBit *StreamElementBit_gen(Dz1Error *err) { return StreamElementBit_new(StreamElementBitPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  StreamElementBit_copy(StreamElementBit *dst, StreamElementBit *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementBit *StreamElementBit_clone(StreamElementBit *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBit_purge(StreamElementBit *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBit_del(StreamElementBit *p);
static __inline__ void StreamElementBit_delAndSetNull(void *ptr)
{
	StreamElementBit **p = (StreamElementBit **)ptr;
	if (p != NULL) { StreamElementBit_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBit_dump(StreamElementBit *p, int tab);
// StreamElementBit
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementBits
typedef struct StreamElementBits
{
	void *storage;
	unsigned int (*count)(struct StreamElementBits *p);
	Dz1Error (*travel)(struct StreamElementBits *p, Dz1Error (*func)(void *ptr, StreamElementBit *entry), void *ptr);
	Dz1Error (*travelForward)(struct StreamElementBits *p, Dz1Error (*func)(void *ptr, StreamElementBit *entry), void *ptr);
	Dz1Error (*travelBackward)(struct StreamElementBits *p, Dz1Error (*func)(void *ptr, StreamElementBit *entry), void *ptr);
	StreamElementBit **(*get_array)(struct StreamElementBits *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct StreamElementBits *p, StreamElementBit *data);
} StreamElementBits;

DZ1_CPPLINK DZ1_DLLPORT StreamElementBits *StreamElementBits_new(Dz1Error *err);
static __inline__ StreamElementBits *StreamElementBits_gen(Dz1Error *err) { return StreamElementBits_new(err); }
DZ1_CPPLINK DZ1_DLLPORT StreamElementBits *StreamElementBits_clone(StreamElementBits *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBits_purge(StreamElementBits *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBits_del(StreamElementBits *p);
static __inline__ void StreamElementBits_delAndSetNull(void *ptr)
{
	StreamElementBits **p = (StreamElementBits **)ptr;
	if (p != NULL) { StreamElementBits_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementBits_dump(StreamElementBits *p, int tab);

// StreamElementBits
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementComplex
typedef struct StreamElementComplex
{
	Dz1TodecUnitSize		 stream_sz;
	StreamElementBits		*seq;
} StreamElementComplex;

DZ1_CPPLINK DZ1_DLLPORT StreamElementComplex *StreamElementComplex_new(Dz1TodecUnitSize stream_sz, Dz1Error *err);
static __inline__ StreamElementComplex *StreamElementComplex_gen(Dz1Error *err) { return StreamElementComplex_new(Dz1TodecUnitSize_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamElementComplex_copy(StreamElementComplex *dst, StreamElementComplex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementComplex *StreamElementComplex_clone(StreamElementComplex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementComplex_purge(StreamElementComplex *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementComplex_del(StreamElementComplex *p);
static __inline__ void StreamElementComplex_delAndSetNull(void *ptr)
{
	StreamElementComplex **p = (StreamElementComplex **)ptr;
	if (p) { StreamElementComplex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementComplex_dump(StreamElementComplex *p, int tab);
// StreamElementComplex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementInfoPresent
typedef enum StreamElementInfoPresent
{
	StreamElementInfoPresent_complex,
	StreamElementInfoPresent_simple,
	StreamElementInfoPresent_conditional,
	StreamElementInfoPresent_pad,
	StreamElementInfoPresent_value,
	StreamElementInfoPresent_omit,
	StreamElementInfoPresent_max
} StreamElementInfoPresent;

DZ1_CPPLINK str_t StreamElementInfoPresentStrA(StreamElementInfoPresent v);
DZ1_CPPLINK StreamElementInfoPresent StreamElementInfoPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t StreamElementInfoPresentStrW(StreamElementInfoPresent v);
DZ1_CPPLINK StreamElementInfoPresent StreamElementInfoPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define StreamElementInfoPresentStr StreamElementInfoPresentStrW
#define StreamElementInfoPresentFromStr StreamElementInfoPresentFromStrW
#else // UNICODE
#define StreamElementInfoPresentStr StreamElementInfoPresentStrA
#define StreamElementInfoPresentFromStr StreamElementInfoPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define StreamElementInfoPresentStr StreamElementInfoPresentStrA
#define StreamElementInfoPresentFromStr StreamElementInfoPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT StreamElementInfoPresent *StreamElementInfoPresent_new(StreamElementInfoPresent *src, Dz1Error *err);
static __inline__ StreamElementInfoPresent *StreamElementInfoPresent_gen(Dz1Error *err) { StreamElementInfoPresent v = StreamElementInfoPresent_max; return StreamElementInfoPresent_new(&v, err); }
#define StreamElementInfoPresent_clone             StreamElementInfoPresent_new
static __inline__ void StreamElementInfoPresent_del(StreamElementInfoPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void StreamElementInfoPresent_delAndSetNull(void *ptr)
{
	StreamElementInfoPresent **p = (StreamElementInfoPresent **)ptr;
	if (p != NULL) { StreamElementInfoPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementInfoPresent_dump(StreamElementInfoPresent *v, int tab);
// StreamElementInfoPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementInfo
typedef struct StreamElementInfo
{
	StreamElementInfoPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		StreamElementComplex		*complex;
		StreamElementSimple			*simple;
		StreamElementConditional	*conditional;
		u16_t						 pad;
		Dz1Binary					*value;
		StreamElementVariable		*omit;
	} x;
} StreamElementInfo;

DZ1_CPPLINK DZ1_DLLPORT StreamElementInfo *StreamElementInfo_new(StreamElementInfoPresent present, void *ptr, Dz1Error *err);
static __inline__ StreamElementInfo *StreamElementInfo_gen(Dz1Error *err) { return StreamElementInfo_new(StreamElementInfoPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  StreamElementInfo_copy(StreamElementInfo *dst, StreamElementInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamElementInfo *StreamElementInfo_clone(StreamElementInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementInfo_purge(StreamElementInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementInfo_del(StreamElementInfo *p);
static __inline__ void StreamElementInfo_delAndSetNull(void *ptr)
{
	StreamElementInfo **p = (StreamElementInfo **)ptr;
	if (p != NULL) { StreamElementInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementInfo_dump(StreamElementInfo *p, int tab);
// StreamElementInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamElementList
typedef struct StreamElementList
{
	void *storage;
	unsigned int (*count)(struct StreamElementList *p);
	Dz1Error (*travel)(struct StreamElementList *p, Dz1Error (*func)(void *ptr, StreamElementInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct StreamElementList *p, Dz1Error (*func)(void *ptr, StreamElementInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct StreamElementList *p, Dz1Error (*func)(void *ptr, StreamElementInfo *entry), void *ptr);
	StreamElementInfo **(*get_array)(struct StreamElementList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct StreamElementList *p, StreamElementInfo *data);
} StreamElementList;

DZ1_CPPLINK DZ1_DLLPORT StreamElementList *StreamElementList_new(Dz1Error *err);
static __inline__ StreamElementList *StreamElementList_gen(Dz1Error *err) { return StreamElementList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT StreamElementList *StreamElementList_clone(StreamElementList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementList_purge(StreamElementList *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamElementList_del(StreamElementList *p);
static __inline__ void StreamElementList_delAndSetNull(void *ptr)
{
	StreamElementList **p = (StreamElementList **)ptr;
	if (p != NULL) { StreamElementList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamElementList_dump(StreamElementList *p, int tab);

// StreamElementList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamObjectAttrUnion
typedef struct StreamObjectAttrUnion
{
	StreamElementSimple		*pr;
} StreamObjectAttrUnion;

DZ1_CPPLINK DZ1_DLLPORT StreamObjectAttrUnion *StreamObjectAttrUnion_new(StreamElementSimple *pr, Dz1Error *err);
static __inline__ StreamObjectAttrUnion *StreamObjectAttrUnion_gen(Dz1Error *err) { return StreamObjectAttrUnion_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamObjectAttrUnion_copy(StreamObjectAttrUnion *dst, StreamObjectAttrUnion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamObjectAttrUnion *StreamObjectAttrUnion_clone(StreamObjectAttrUnion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttrUnion_purge(StreamObjectAttrUnion *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttrUnion_del(StreamObjectAttrUnion *p);
static __inline__ void StreamObjectAttrUnion_delAndSetNull(void *ptr)
{
	StreamObjectAttrUnion **p = (StreamObjectAttrUnion **)ptr;
	if (p) { StreamObjectAttrUnion_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttrUnion_dump(StreamObjectAttrUnion *p, int tab);
// StreamObjectAttrUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamObjectAttrArray
typedef struct StreamObjectAttrArray
{
	StreamElementSimple		*cnt;
	StreamElementSimple		*etr;
	str_t					 postfix;
} StreamObjectAttrArray;

DZ1_CPPLINK DZ1_DLLPORT StreamObjectAttrArray *StreamObjectAttrArray_new(StreamElementSimple *cnt, 
																		 StreamElementSimple *etr, 
																		 str_t postfix, Dz1Error *err);
static __inline__ StreamObjectAttrArray *StreamObjectAttrArray_gen(Dz1Error *err) { return StreamObjectAttrArray_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamObjectAttrArray_copy(StreamObjectAttrArray *dst, StreamObjectAttrArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamObjectAttrArray *StreamObjectAttrArray_clone(StreamObjectAttrArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttrArray_purge(StreamObjectAttrArray *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttrArray_del(StreamObjectAttrArray *p);
static __inline__ void StreamObjectAttrArray_delAndSetNull(void *ptr)
{
	StreamObjectAttrArray **p = (StreamObjectAttrArray **)ptr;
	if (p) { StreamObjectAttrArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttrArray_dump(StreamObjectAttrArray *p, int tab);
// StreamObjectAttrArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamObjectAttrPresent
typedef enum StreamObjectAttrPresent
{
	StreamObjectAttrPresent_st,
	StreamObjectAttrPresent_un,
	StreamObjectAttrPresent_ar,
	StreamObjectAttrPresent_max
} StreamObjectAttrPresent;

DZ1_CPPLINK str_t StreamObjectAttrPresentStrA(StreamObjectAttrPresent v);
DZ1_CPPLINK StreamObjectAttrPresent StreamObjectAttrPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t StreamObjectAttrPresentStrW(StreamObjectAttrPresent v);
DZ1_CPPLINK StreamObjectAttrPresent StreamObjectAttrPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define StreamObjectAttrPresentStr StreamObjectAttrPresentStrW
#define StreamObjectAttrPresentFromStr StreamObjectAttrPresentFromStrW
#else // UNICODE
#define StreamObjectAttrPresentStr StreamObjectAttrPresentStrA
#define StreamObjectAttrPresentFromStr StreamObjectAttrPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define StreamObjectAttrPresentStr StreamObjectAttrPresentStrA
#define StreamObjectAttrPresentFromStr StreamObjectAttrPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT StreamObjectAttrPresent *StreamObjectAttrPresent_new(StreamObjectAttrPresent *src, Dz1Error *err);
static __inline__ StreamObjectAttrPresent *StreamObjectAttrPresent_gen(Dz1Error *err) { StreamObjectAttrPresent v = StreamObjectAttrPresent_max; return StreamObjectAttrPresent_new(&v, err); }
#define StreamObjectAttrPresent_clone             StreamObjectAttrPresent_new
static __inline__ void StreamObjectAttrPresent_del(StreamObjectAttrPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void StreamObjectAttrPresent_delAndSetNull(void *ptr)
{
	StreamObjectAttrPresent **p = (StreamObjectAttrPresent **)ptr;
	if (p != NULL) { StreamObjectAttrPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttrPresent_dump(StreamObjectAttrPresent *v, int tab);
// StreamObjectAttrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamObjectAttr
typedef struct StreamObjectAttr
{
	StreamObjectAttrPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t						*st;
		StreamObjectAttrUnion		*un;
		StreamObjectAttrArray		*ar;
	} x;
} StreamObjectAttr;

DZ1_CPPLINK DZ1_DLLPORT StreamObjectAttr *StreamObjectAttr_new(StreamObjectAttrPresent present, void *ptr, Dz1Error *err);
static __inline__ StreamObjectAttr *StreamObjectAttr_gen(Dz1Error *err) { return StreamObjectAttr_new(StreamObjectAttrPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  StreamObjectAttr_copy(StreamObjectAttr *dst, StreamObjectAttr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamObjectAttr *StreamObjectAttr_clone(StreamObjectAttr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttr_purge(StreamObjectAttr *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttr_del(StreamObjectAttr *p);
static __inline__ void StreamObjectAttr_delAndSetNull(void *ptr)
{
	StreamObjectAttr **p = (StreamObjectAttr **)ptr;
	if (p != NULL) { StreamObjectAttr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamObjectAttr_dump(StreamObjectAttr *p, int tab);
// StreamObjectAttr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamInfo
typedef struct StreamInfo
{
	u32_t					 read_var;
	u32_t					 write_var;
	StreamObjectAttr		*attr;
	StreamElementList		*seq;
} StreamInfo;

DZ1_CPPLINK DZ1_DLLPORT StreamInfo *StreamInfo_new(u32_t read_var, 
												   u32_t write_var, 
												   StreamObjectAttr *attr, Dz1Error *err);
static __inline__ StreamInfo *StreamInfo_gen(Dz1Error *err) { return StreamInfo_new(0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StreamInfo_copy(StreamInfo *dst, StreamInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StreamInfo *StreamInfo_clone(StreamInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamInfo_purge(StreamInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamInfo_del(StreamInfo *p);
static __inline__ void StreamInfo_delAndSetNull(void *ptr)
{
	StreamInfo **p = (StreamInfo **)ptr;
	if (p) { StreamInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamInfo_dump(StreamInfo *p, int tab);
// StreamInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StreamList
typedef struct StreamList
{
	void *storage;
	unsigned int (*count)(struct StreamList *p);
	Dz1Error (*travel)(struct StreamList *p, Dz1Error (*func)(void *ptr, StreamInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct StreamList *p, Dz1Error (*func)(void *ptr, StreamInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct StreamList *p, Dz1Error (*func)(void *ptr, StreamInfo *entry), void *ptr);
	StreamInfo **(*get_array)(struct StreamList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct StreamList *p, StreamInfo *data);
} StreamList;

DZ1_CPPLINK DZ1_DLLPORT StreamList *StreamList_new(Dz1Error *err);
static __inline__ StreamList *StreamList_gen(Dz1Error *err) { return StreamList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT StreamList *StreamList_clone(StreamList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StreamList_purge(StreamList *p);
DZ1_CPPLINK DZ1_DLLPORT void StreamList_del(StreamList *p);
static __inline__ void StreamList_delAndSetNull(void *ptr)
{
	StreamList **p = (StreamList **)ptr;
	if (p != NULL) { StreamList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StreamList_dump(StreamList *p, int tab);

// StreamList
////////////////////////////////////////////////////////////////////////////////

#endif
