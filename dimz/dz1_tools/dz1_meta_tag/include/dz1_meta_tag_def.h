#ifndef _DZ1_TDC_DZ1_META_TAG_DEF_H_
#define _DZ1_TDC_DZ1_META_TAG_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValuePresent
typedef enum Dz1MetaTagValuePresent
{
	Dz1MetaTagValuePresent_data8,
	Dz1MetaTagValuePresent_data16,
	Dz1MetaTagValuePresent_data32,
	Dz1MetaTagValuePresent_data64,
	Dz1MetaTagValuePresent_binary,
	Dz1MetaTagValuePresent_max
} Dz1MetaTagValuePresent;

DZ1_CPPLINK str_t Dz1MetaTagValuePresentStrA(Dz1MetaTagValuePresent v);
DZ1_CPPLINK Dz1MetaTagValuePresent Dz1MetaTagValuePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MetaTagValuePresentStrW(Dz1MetaTagValuePresent v);
DZ1_CPPLINK Dz1MetaTagValuePresent Dz1MetaTagValuePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MetaTagValuePresentStr Dz1MetaTagValuePresentStrW
#define Dz1MetaTagValuePresentFromStr Dz1MetaTagValuePresentFromStrW
#else // UNICODE
#define Dz1MetaTagValuePresentStr Dz1MetaTagValuePresentStrA
#define Dz1MetaTagValuePresentFromStr Dz1MetaTagValuePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MetaTagValuePresentStr Dz1MetaTagValuePresentStrA
#define Dz1MetaTagValuePresentFromStr Dz1MetaTagValuePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagValuePresent *Dz1MetaTagValuePresent_new(Dz1MetaTagValuePresent *src, Dz1Error *err);
static __inline__ Dz1MetaTagValuePresent *Dz1MetaTagValuePresent_gen(Dz1Error *err) { Dz1MetaTagValuePresent v = Dz1MetaTagValuePresent_max; return Dz1MetaTagValuePresent_new(&v, err); }
#define Dz1MetaTagValuePresent_clone             Dz1MetaTagValuePresent_new
static __inline__ void Dz1MetaTagValuePresent_del(Dz1MetaTagValuePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MetaTagValuePresent_delAndSetNull(void *ptr)
{
	Dz1MetaTagValuePresent **p = (Dz1MetaTagValuePresent **)ptr;
	if (p != NULL) { Dz1MetaTagValuePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagValuePresent_dump(Dz1MetaTagValuePresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MetaTagValuePresent_cmp(Dz1MetaTagValuePresent *a, Dz1MetaTagValuePresent *b);
// Dz1MetaTagValuePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValue
typedef struct Dz1MetaTagValue
{
	Dz1MetaTagValuePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u8_t			 data8;
		u16_t			 data16;
		u32_t			 data32;
		u64_t			 data64;
		Dz1Binary		*binary;
	} x;
} Dz1MetaTagValue;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagValue *Dz1MetaTagValue_new(Dz1MetaTagValuePresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1MetaTagValue *Dz1MetaTagValue_gen(Dz1Error *err) { return Dz1MetaTagValue_new(Dz1MetaTagValuePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1MetaTagValue_copy(Dz1MetaTagValue *dst, Dz1MetaTagValue *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagValue *Dz1MetaTagValue_clone(Dz1MetaTagValue *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagValue_purge(Dz1MetaTagValue *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagValue_del(Dz1MetaTagValue *p);
static __inline__ void Dz1MetaTagValue_delAndSetNull(void *ptr)
{
	Dz1MetaTagValue **p = (Dz1MetaTagValue **)ptr;
	if (p != NULL) { Dz1MetaTagValue_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagValue_dump(Dz1MetaTagValue *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MetaTagValue_cmp(Dz1MetaTagValue *a, Dz1MetaTagValue *b);
// Dz1MetaTagValue
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValueList
typedef struct Dz1MetaTagValueList
{
	void *storage;
	unsigned int (*count)(struct Dz1MetaTagValueList *p);
	Dz1Error (*travel)(struct Dz1MetaTagValueList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagValue *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MetaTagValueList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagValue *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MetaTagValueList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagValue *entry), void *ptr);
	Dz1MetaTagValue **(*get_array)(struct Dz1MetaTagValueList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MetaTagValueList *p, Dz1MetaTagValue *data);
	bool_t (*remove)(struct Dz1MetaTagValueList *p, Dz1MetaTagValue *key);
	Dz1MetaTagValue *(*extract)(struct Dz1MetaTagValueList *p, Dz1MetaTagValue *key);
	Dz1MetaTagValue *(*find)(struct Dz1MetaTagValueList *p, Dz1MetaTagValue *key);
	Dz1MetaTagValue *(*getHead)(struct Dz1MetaTagValueList *p);
	Dz1MetaTagValue *(*getTail)(struct Dz1MetaTagValueList *p);
	int (*cmp)(Dz1MetaTagValue *a, Dz1MetaTagValue *b);
} Dz1MetaTagValueList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagValueList *Dz1MetaTagValueList_new(Dz1Error *err);
static __inline__ Dz1MetaTagValueList *Dz1MetaTagValueList_gen(Dz1Error *err) { return Dz1MetaTagValueList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagValueList *Dz1MetaTagValueList_clone(Dz1MetaTagValueList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagValueList_purge(Dz1MetaTagValueList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagValueList_del(Dz1MetaTagValueList *p);
static __inline__ void Dz1MetaTagValueList_delAndSetNull(void *ptr)
{
	Dz1MetaTagValueList **p = (Dz1MetaTagValueList **)ptr;
	if (p != NULL) { Dz1MetaTagValueList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagValueList_dump(Dz1MetaTagValueList *p, int tab);

// Dz1MetaTagValueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataEntry
typedef struct Dz1MetaTagDataEntry
{
	u32_t					 id;
	Dz1MetaTagValueList		*values;
} Dz1MetaTagDataEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDataEntry *Dz1MetaTagDataEntry_new(u32_t id, Dz1Error *err);
static __inline__ Dz1MetaTagDataEntry *Dz1MetaTagDataEntry_gen(Dz1Error *err) { return Dz1MetaTagDataEntry_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MetaTagDataEntry_copy(Dz1MetaTagDataEntry *dst, Dz1MetaTagDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDataEntry *Dz1MetaTagDataEntry_clone(Dz1MetaTagDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDataEntry_purge(Dz1MetaTagDataEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDataEntry_del(Dz1MetaTagDataEntry *p);
static __inline__ void Dz1MetaTagDataEntry_delAndSetNull(void *ptr)
{
	Dz1MetaTagDataEntry **p = (Dz1MetaTagDataEntry **)ptr;
	if (p) { Dz1MetaTagDataEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDataEntry_dump(Dz1MetaTagDataEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MetaTagDataEntry_cmp(Dz1MetaTagDataEntry *a, Dz1MetaTagDataEntry *b); 
// Dz1MetaTagDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataList
typedef struct Dz1MetaTagDataList
{
	void *storage;
	unsigned int (*count)(struct Dz1MetaTagDataList *p);
	Dz1Error (*travel)(struct Dz1MetaTagDataList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MetaTagDataList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MetaTagDataList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDataEntry *entry), void *ptr);
	Dz1MetaTagDataEntry **(*get_array)(struct Dz1MetaTagDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MetaTagDataList *p, Dz1MetaTagDataEntry *data);
	bool_t (*remove)(struct Dz1MetaTagDataList *p, Dz1MetaTagDataEntry *key);
	Dz1MetaTagDataEntry *(*extract)(struct Dz1MetaTagDataList *p, Dz1MetaTagDataEntry *key);
	Dz1MetaTagDataEntry *(*find)(struct Dz1MetaTagDataList *p, Dz1MetaTagDataEntry *key);
	int (*cmp)(Dz1MetaTagDataEntry *a, Dz1MetaTagDataEntry *b);
} Dz1MetaTagDataList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDataList *Dz1MetaTagDataList_new(Dz1Error *err);
static __inline__ Dz1MetaTagDataList *Dz1MetaTagDataList_gen(Dz1Error *err) { return Dz1MetaTagDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDataList *Dz1MetaTagDataList_clone(Dz1MetaTagDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDataList_purge(Dz1MetaTagDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDataList_del(Dz1MetaTagDataList *p);
static __inline__ void Dz1MetaTagDataList_delAndSetNull(void *ptr)
{
	Dz1MetaTagDataList **p = (Dz1MetaTagDataList **)ptr;
	if (p != NULL) { Dz1MetaTagDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDataList_dump(Dz1MetaTagDataList *p, int tab);

// Dz1MetaTagDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagData
typedef struct Dz1MetaTagData
{
	u32_t					 target_type;
	Dz1MetaTagDataList		*tags;
} Dz1MetaTagData;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagData *Dz1MetaTagData_new(u32_t target_type, Dz1Error *err);
static __inline__ Dz1MetaTagData *Dz1MetaTagData_gen(Dz1Error *err) { return Dz1MetaTagData_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MetaTagData_copy(Dz1MetaTagData *dst, Dz1MetaTagData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagData *Dz1MetaTagData_clone(Dz1MetaTagData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagData_purge(Dz1MetaTagData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagData_del(Dz1MetaTagData *p);
static __inline__ void Dz1MetaTagData_delAndSetNull(void *ptr)
{
	Dz1MetaTagData **p = (Dz1MetaTagData **)ptr;
	if (p) { Dz1MetaTagData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagData_dump(Dz1MetaTagData *p, int tab);
// Dz1MetaTagData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeEntry
typedef struct Dz1MetaTargetTypeEntry
{
	u32_t				 type;
	Dz1Asn1UTF8Str		*name;
	wstr_t				 name_w;
} Dz1MetaTargetTypeEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeEntry_new(u32_t type, 
																		   Dz1Asn1UTF8Str *name, Dz1Error *err);
static __inline__ Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeEntry_gen(Dz1Error *err) { return Dz1MetaTargetTypeEntry_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MetaTargetTypeEntry_copy(Dz1MetaTargetTypeEntry *dst, Dz1MetaTargetTypeEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTargetTypeEntry *Dz1MetaTargetTypeEntry_clone(Dz1MetaTargetTypeEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTargetTypeEntry_purge(Dz1MetaTargetTypeEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTargetTypeEntry_del(Dz1MetaTargetTypeEntry *p);
static __inline__ void Dz1MetaTargetTypeEntry_delAndSetNull(void *ptr)
{
	Dz1MetaTargetTypeEntry **p = (Dz1MetaTargetTypeEntry **)ptr;
	if (p) { Dz1MetaTargetTypeEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTargetTypeEntry_dump(Dz1MetaTargetTypeEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MetaTargetTypeEntry_cmp(Dz1MetaTargetTypeEntry *a, Dz1MetaTargetTypeEntry *b); 
// Dz1MetaTargetTypeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeList
typedef struct Dz1MetaTargetTypeList
{
	void *storage;
	unsigned int (*count)(struct Dz1MetaTargetTypeList *p);
	Dz1Error (*travel)(struct Dz1MetaTargetTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTargetTypeEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MetaTargetTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTargetTypeEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MetaTargetTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTargetTypeEntry *entry), void *ptr);
	Dz1MetaTargetTypeEntry **(*get_array)(struct Dz1MetaTargetTypeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MetaTargetTypeList *p, Dz1MetaTargetTypeEntry *data);
	bool_t (*remove)(struct Dz1MetaTargetTypeList *p, Dz1MetaTargetTypeEntry *key);
	Dz1MetaTargetTypeEntry *(*extract)(struct Dz1MetaTargetTypeList *p, Dz1MetaTargetTypeEntry *key);
	Dz1MetaTargetTypeEntry *(*find)(struct Dz1MetaTargetTypeList *p, Dz1MetaTargetTypeEntry *key);
	Dz1MetaTargetTypeEntry *(*getTail)(struct Dz1MetaTargetTypeList *p);
	int (*cmp)(Dz1MetaTargetTypeEntry *a, Dz1MetaTargetTypeEntry *b);
} Dz1MetaTargetTypeList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTargetTypeList *Dz1MetaTargetTypeList_new(Dz1Error *err);
static __inline__ Dz1MetaTargetTypeList *Dz1MetaTargetTypeList_gen(Dz1Error *err) { return Dz1MetaTargetTypeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTargetTypeList *Dz1MetaTargetTypeList_clone(Dz1MetaTargetTypeList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTargetTypeList_purge(Dz1MetaTargetTypeList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTargetTypeList_del(Dz1MetaTargetTypeList *p);
static __inline__ void Dz1MetaTargetTypeList_delAndSetNull(void *ptr)
{
	Dz1MetaTargetTypeList **p = (Dz1MetaTargetTypeList **)ptr;
	if (p != NULL) { Dz1MetaTargetTypeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTargetTypeList_dump(Dz1MetaTargetTypeList *p, int tab);

// Dz1MetaTargetTypeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagRestrictMode
typedef enum Dz1MetaTagRestrictMode
{
	Dz1MetaTagRestrictMode_accept,
	Dz1MetaTagRestrictMode_reject,
	Dz1MetaTagRestrictMode_max
} Dz1MetaTagRestrictMode;

DZ1_CPPLINK str_t Dz1MetaTagRestrictModeStrA(Dz1MetaTagRestrictMode v);
DZ1_CPPLINK Dz1MetaTagRestrictMode Dz1MetaTagRestrictModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MetaTagRestrictModeStrW(Dz1MetaTagRestrictMode v);
DZ1_CPPLINK Dz1MetaTagRestrictMode Dz1MetaTagRestrictModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MetaTagRestrictModeStr Dz1MetaTagRestrictModeStrW
#define Dz1MetaTagRestrictModeFromStr Dz1MetaTagRestrictModeFromStrW
#else // UNICODE
#define Dz1MetaTagRestrictModeStr Dz1MetaTagRestrictModeStrA
#define Dz1MetaTagRestrictModeFromStr Dz1MetaTagRestrictModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MetaTagRestrictModeStr Dz1MetaTagRestrictModeStrA
#define Dz1MetaTagRestrictModeFromStr Dz1MetaTagRestrictModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagRestrictMode *Dz1MetaTagRestrictMode_new(Dz1MetaTagRestrictMode *src, Dz1Error *err);
static __inline__ Dz1MetaTagRestrictMode *Dz1MetaTagRestrictMode_gen(Dz1Error *err) { Dz1MetaTagRestrictMode v = Dz1MetaTagRestrictMode_max; return Dz1MetaTagRestrictMode_new(&v, err); }
static __inline__ void Dz1MetaTagRestrictMode_del(Dz1MetaTagRestrictMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MetaTagRestrictMode_delAndSetNull(void *ptr)
{
	Dz1MetaTagRestrictMode **p = (Dz1MetaTagRestrictMode **)ptr;
	if (p != NULL) { Dz1MetaTagRestrictMode_del(*p); *p = NULL; }
}
// Dz1MetaTagRestrictMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagRestrict
typedef struct Dz1MetaTagRestrict
{
	Dz1MetaTagRestrictMode		 mode;
	Dz1MetaTargetTypeList		*list;
} Dz1MetaTagRestrict;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagRestrict *Dz1MetaTagRestrict_new(Dz1MetaTagRestrictMode mode, Dz1Error *err);
static __inline__ Dz1MetaTagRestrict *Dz1MetaTagRestrict_gen(Dz1Error *err) { return Dz1MetaTagRestrict_new(Dz1MetaTagRestrictMode_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MetaTagRestrict_copy(Dz1MetaTagRestrict *dst, Dz1MetaTagRestrict *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagRestrict *Dz1MetaTagRestrict_clone(Dz1MetaTagRestrict *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagRestrict_purge(Dz1MetaTagRestrict *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagRestrict_del(Dz1MetaTagRestrict *p);
static __inline__ void Dz1MetaTagRestrict_delAndSetNull(void *ptr)
{
	Dz1MetaTagRestrict **p = (Dz1MetaTagRestrict **)ptr;
	if (p) { Dz1MetaTagRestrict_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagRestrict_dump(Dz1MetaTagRestrict *p, int tab);
// Dz1MetaTagRestrict
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrNum
typedef enum Dz1MetaTagDescrNum
{
	Dz1MetaTagDescrNum_signed,
	Dz1MetaTagDescrNum_unsigned,
	Dz1MetaTagDescrNum_hex,
	Dz1MetaTagDescrNum_binary,
	Dz1MetaTagDescrNum_max
} Dz1MetaTagDescrNum;

DZ1_CPPLINK str_t Dz1MetaTagDescrNumStrA(Dz1MetaTagDescrNum v);
DZ1_CPPLINK Dz1MetaTagDescrNum Dz1MetaTagDescrNumFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MetaTagDescrNumStrW(Dz1MetaTagDescrNum v);
DZ1_CPPLINK Dz1MetaTagDescrNum Dz1MetaTagDescrNumFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MetaTagDescrNumStr Dz1MetaTagDescrNumStrW
#define Dz1MetaTagDescrNumFromStr Dz1MetaTagDescrNumFromStrW
#else // UNICODE
#define Dz1MetaTagDescrNumStr Dz1MetaTagDescrNumStrA
#define Dz1MetaTagDescrNumFromStr Dz1MetaTagDescrNumFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MetaTagDescrNumStr Dz1MetaTagDescrNumStrA
#define Dz1MetaTagDescrNumFromStr Dz1MetaTagDescrNumFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrNum *Dz1MetaTagDescrNum_new(Dz1MetaTagDescrNum *src, Dz1Error *err);
static __inline__ Dz1MetaTagDescrNum *Dz1MetaTagDescrNum_gen(Dz1Error *err) { Dz1MetaTagDescrNum v = Dz1MetaTagDescrNum_max; return Dz1MetaTagDescrNum_new(&v, err); }
static __inline__ void Dz1MetaTagDescrNum_del(Dz1MetaTagDescrNum *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MetaTagDescrNum_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrNum **p = (Dz1MetaTagDescrNum **)ptr;
	if (p != NULL) { Dz1MetaTagDescrNum_del(*p); *p = NULL; }
}
// Dz1MetaTagDescrNum
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrNumber
typedef struct Dz1MetaTagDescrNumber
{
	Dz1MetaTagDescrNum		type;
} Dz1MetaTagDescrNumber;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrNumber *Dz1MetaTagDescrNumber_new(Dz1MetaTagDescrNum type, Dz1Error *err);
static __inline__ Dz1MetaTagDescrNumber *Dz1MetaTagDescrNumber_gen(Dz1Error *err) { return Dz1MetaTagDescrNumber_new(Dz1MetaTagDescrNum_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrNumber_purge(Dz1MetaTagDescrNumber *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrNumber_del(Dz1MetaTagDescrNumber *p);
static __inline__ void Dz1MetaTagDescrNumber_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrNumber **p = (Dz1MetaTagDescrNumber **)ptr;
	if (p) { Dz1MetaTagDescrNumber_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrNumber_dump(Dz1MetaTagDescrNumber *p, int tab);
// Dz1MetaTagDescrNumber
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrFloat
typedef struct Dz1MetaTagDescrFloat
{
	s32_t		precision;
} Dz1MetaTagDescrFloat;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrFloat *Dz1MetaTagDescrFloat_new(s32_t precision, Dz1Error *err);
static __inline__ Dz1MetaTagDescrFloat *Dz1MetaTagDescrFloat_gen(Dz1Error *err) { return Dz1MetaTagDescrFloat_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrFloat_purge(Dz1MetaTagDescrFloat *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrFloat_del(Dz1MetaTagDescrFloat *p);
static __inline__ void Dz1MetaTagDescrFloat_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrFloat **p = (Dz1MetaTagDescrFloat **)ptr;
	if (p) { Dz1MetaTagDescrFloat_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrFloat_dump(Dz1MetaTagDescrFloat *p, int tab);
// Dz1MetaTagDescrFloat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrGrade
typedef struct Dz1MetaTagDescrGrade
{
	u32_t				 max_grade;
	Dz1Asn1UTF8Str		*grade_unit;
	wstr_t				 grade_unit_w;
} Dz1MetaTagDescrGrade;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrGrade *Dz1MetaTagDescrGrade_new(u32_t max_grade, 
																	   Dz1Asn1UTF8Str *grade_unit, Dz1Error *err);
static __inline__ Dz1MetaTagDescrGrade *Dz1MetaTagDescrGrade_gen(Dz1Error *err) { return Dz1MetaTagDescrGrade_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrGrade_purge(Dz1MetaTagDescrGrade *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrGrade_del(Dz1MetaTagDescrGrade *p);
static __inline__ void Dz1MetaTagDescrGrade_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrGrade **p = (Dz1MetaTagDescrGrade **)ptr;
	if (p) { Dz1MetaTagDescrGrade_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrGrade_dump(Dz1MetaTagDescrGrade *p, int tab);
// Dz1MetaTagDescrGrade
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrString
typedef struct Dz1MetaTagDescrString
{
	str_t		charset;
} Dz1MetaTagDescrString;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrString *Dz1MetaTagDescrString_new(str_t charset, Dz1Error *err);
static __inline__ Dz1MetaTagDescrString *Dz1MetaTagDescrString_gen(Dz1Error *err) { return Dz1MetaTagDescrString_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrString_purge(Dz1MetaTagDescrString *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrString_del(Dz1MetaTagDescrString *p);
static __inline__ void Dz1MetaTagDescrString_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrString **p = (Dz1MetaTagDescrString **)ptr;
	if (p) { Dz1MetaTagDescrString_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrString_dump(Dz1MetaTagDescrString *p, int tab);
// Dz1MetaTagDescrString
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumEntry
typedef struct Dz1MetaTagDescrEnumEntry
{
	u32_t				 value;
	Dz1Asn1UTF8Str		*string;
	wstr_t				 str_w;
} Dz1MetaTagDescrEnumEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumEntry_new(u32_t value, 
																			   Dz1Asn1UTF8Str *string, Dz1Error *err);
static __inline__ Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumEntry_gen(Dz1Error *err) { return Dz1MetaTagDescrEnumEntry_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MetaTagDescrEnumEntry_copy(Dz1MetaTagDescrEnumEntry *dst, Dz1MetaTagDescrEnumEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnumEntry_clone(Dz1MetaTagDescrEnumEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumEntry_purge(Dz1MetaTagDescrEnumEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumEntry_del(Dz1MetaTagDescrEnumEntry *p);
static __inline__ void Dz1MetaTagDescrEnumEntry_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrEnumEntry **p = (Dz1MetaTagDescrEnumEntry **)ptr;
	if (p) { Dz1MetaTagDescrEnumEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumEntry_dump(Dz1MetaTagDescrEnumEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MetaTagDescrEnumEntry_cmp(Dz1MetaTagDescrEnumEntry *a, Dz1MetaTagDescrEnumEntry *b); 
// Dz1MetaTagDescrEnumEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumList
typedef struct Dz1MetaTagDescrEnumList
{
	void *storage;
	unsigned int (*count)(struct Dz1MetaTagDescrEnumList *p);
	Dz1Error (*travel)(struct Dz1MetaTagDescrEnumList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MetaTagDescrEnumList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MetaTagDescrEnumList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumEntry *entry), void *ptr);
	Dz1MetaTagDescrEnumEntry **(*get_array)(struct Dz1MetaTagDescrEnumList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MetaTagDescrEnumList *p, Dz1MetaTagDescrEnumEntry *data);
	bool_t (*remove)(struct Dz1MetaTagDescrEnumList *p, Dz1MetaTagDescrEnumEntry *key);
	Dz1MetaTagDescrEnumEntry *(*extract)(struct Dz1MetaTagDescrEnumList *p, Dz1MetaTagDescrEnumEntry *key);
	Dz1MetaTagDescrEnumEntry *(*find)(struct Dz1MetaTagDescrEnumList *p, Dz1MetaTagDescrEnumEntry *key);
	Dz1MetaTagDescrEnumEntry *(*getTail)(struct Dz1MetaTagDescrEnumList *p);
	int (*cmp)(Dz1MetaTagDescrEnumEntry *a, Dz1MetaTagDescrEnumEntry *b);
} Dz1MetaTagDescrEnumList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnumList *Dz1MetaTagDescrEnumList_new(Dz1Error *err);
static __inline__ Dz1MetaTagDescrEnumList *Dz1MetaTagDescrEnumList_gen(Dz1Error *err) { return Dz1MetaTagDescrEnumList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnumList *Dz1MetaTagDescrEnumList_clone(Dz1MetaTagDescrEnumList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumList_purge(Dz1MetaTagDescrEnumList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumList_del(Dz1MetaTagDescrEnumList *p);
static __inline__ void Dz1MetaTagDescrEnumList_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrEnumList **p = (Dz1MetaTagDescrEnumList **)ptr;
	if (p != NULL) { Dz1MetaTagDescrEnumList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumList_dump(Dz1MetaTagDescrEnumList *p, int tab);

// Dz1MetaTagDescrEnumList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumIndex
typedef struct Dz1MetaTagDescrEnumIndex
{
	u32_t				 value;
	Dz1Asn1UTF8Str		*string;
	wstr_t				 str_w;
} Dz1MetaTagDescrEnumIndex;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnumIndex *Dz1MetaTagDescrEnumIndex_new(u32_t value, 
																			   Dz1Asn1UTF8Str *string, Dz1Error *err);
static __inline__ Dz1MetaTagDescrEnumIndex *Dz1MetaTagDescrEnumIndex_gen(Dz1Error *err) { return Dz1MetaTagDescrEnumIndex_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MetaTagDescrEnumIndex_copy(Dz1MetaTagDescrEnumIndex *dst, Dz1MetaTagDescrEnumIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnumIndex *Dz1MetaTagDescrEnumIndex_clone(Dz1MetaTagDescrEnumIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumIndex_purge(Dz1MetaTagDescrEnumIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumIndex_del(Dz1MetaTagDescrEnumIndex *p);
static __inline__ void Dz1MetaTagDescrEnumIndex_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrEnumIndex **p = (Dz1MetaTagDescrEnumIndex **)ptr;
	if (p) { Dz1MetaTagDescrEnumIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumIndex_dump(Dz1MetaTagDescrEnumIndex *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MetaTagDescrEnumIndex_cmp(Dz1MetaTagDescrEnumIndex *a, Dz1MetaTagDescrEnumIndex *b); 
// Dz1MetaTagDescrEnumIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumTable
typedef struct Dz1MetaTagDescrEnumTable
{
	void *storage;
	unsigned int (*count)(struct Dz1MetaTagDescrEnumTable *p);
	Dz1Error (*travel)(struct Dz1MetaTagDescrEnumTable *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumIndex *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MetaTagDescrEnumTable *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumIndex *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MetaTagDescrEnumTable *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEnumIndex *entry), void *ptr);
	Dz1MetaTagDescrEnumIndex **(*get_array)(struct Dz1MetaTagDescrEnumTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MetaTagDescrEnumTable *p, Dz1MetaTagDescrEnumIndex *data);
	bool_t (*remove)(struct Dz1MetaTagDescrEnumTable *p, Dz1MetaTagDescrEnumIndex *key);
	Dz1MetaTagDescrEnumIndex *(*extract)(struct Dz1MetaTagDescrEnumTable *p, Dz1MetaTagDescrEnumIndex *key);
	Dz1MetaTagDescrEnumIndex *(*find)(struct Dz1MetaTagDescrEnumTable *p, Dz1MetaTagDescrEnumIndex *key);
	int (*cmp)(Dz1MetaTagDescrEnumIndex *a, Dz1MetaTagDescrEnumIndex *b);
} Dz1MetaTagDescrEnumTable;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnumTable *Dz1MetaTagDescrEnumTable_new(Dz1Error *err);
static __inline__ Dz1MetaTagDescrEnumTable *Dz1MetaTagDescrEnumTable_gen(Dz1Error *err) { return Dz1MetaTagDescrEnumTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnumTable *Dz1MetaTagDescrEnumTable_clone(Dz1MetaTagDescrEnumTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumTable_purge(Dz1MetaTagDescrEnumTable *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumTable_del(Dz1MetaTagDescrEnumTable *p);
static __inline__ void Dz1MetaTagDescrEnumTable_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrEnumTable **p = (Dz1MetaTagDescrEnumTable **)ptr;
	if (p != NULL) { Dz1MetaTagDescrEnumTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnumTable_dump(Dz1MetaTagDescrEnumTable *p, int tab);

// Dz1MetaTagDescrEnumTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumsAdd
typedef Dz1Error (*Dz1MetaTagDescrEnumsAdd)(struct Dz1MetaTagDescrEnums *dst, Dz1MetaTagDescrEnumEntry *node);
// Dz1MetaTagDescrEnumsAdd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumsFind
typedef Dz1MetaTagDescrEnumEntry *(*Dz1MetaTagDescrEnumsFind)(struct Dz1MetaTagDescrEnums *src, Dz1MetaTagDescrEnumEntry *key);
// Dz1MetaTagDescrEnumsFind
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumsExtract
typedef Dz1MetaTagDescrEnumEntry *(*Dz1MetaTagDescrEnumsExtract)(struct Dz1MetaTagDescrEnums *src, Dz1MetaTagDescrEnumEntry *key);
// Dz1MetaTagDescrEnumsExtract
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumsGetArray
typedef Dz1MetaTagDescrEnumEntry **(*Dz1MetaTagDescrEnumsGetArray)(struct Dz1MetaTagDescrEnums *src, u32_t *ret_cnt, Dz1Error *err);
// Dz1MetaTagDescrEnumsGetArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumsGetLast
typedef Dz1MetaTagDescrEnumEntry *(*Dz1MetaTagDescrEnumsGetLast)(struct Dz1MetaTagDescrEnums *src);
// Dz1MetaTagDescrEnumsGetLast
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnums
typedef struct Dz1MetaTagDescrEnums
{
	Dz1MetaTagDescrEnumList			*values;
	Dz1MetaTagDescrEnumTable		*strings;
	Dz1MetaTagDescrEnumsAdd			 add;
	Dz1MetaTagDescrEnumsFind		 find;
	Dz1MetaTagDescrEnumsExtract		 extract;
	Dz1MetaTagDescrEnumsGetArray	 get_array;
	Dz1MetaTagDescrEnumsGetLast		 getTail;
} Dz1MetaTagDescrEnums;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnums *Dz1MetaTagDescrEnums_new(Dz1MetaTagDescrEnumsAdd add, 
																	   Dz1MetaTagDescrEnumsFind find, 
																	   Dz1MetaTagDescrEnumsExtract extract, 
																	   Dz1MetaTagDescrEnumsGetArray get_array, 
																	   Dz1MetaTagDescrEnumsGetLast getTail, Dz1Error *err);
static __inline__ Dz1MetaTagDescrEnums *Dz1MetaTagDescrEnums_gen(Dz1Error *err) { return Dz1MetaTagDescrEnums_new(NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MetaTagDescrEnums_copy(Dz1MetaTagDescrEnums *dst, Dz1MetaTagDescrEnums *src, Dz1Error *err);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEnums *Dz1MetaTagDescrEnums_clone(Dz1MetaTagDescrEnums *src, Dz1Error *err);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnums_purge(Dz1MetaTagDescrEnums *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnums_del(Dz1MetaTagDescrEnums *p);
static __inline__ void Dz1MetaTagDescrEnums_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrEnums **p = (Dz1MetaTagDescrEnums **)ptr;
	if (p) { Dz1MetaTagDescrEnums_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEnums_dump(Dz1MetaTagDescrEnums *p, int tab);
// Dz1MetaTagDescrEnums
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrDate8Mode
typedef enum Dz1MetaTagDescrDate8Mode
{
	Dz1MetaTagDescrDate8Mode_even,
	Dz1MetaTagDescrDate8Mode_odd,
	Dz1MetaTagDescrDate8Mode_max
} Dz1MetaTagDescrDate8Mode;

DZ1_CPPLINK str_t Dz1MetaTagDescrDate8ModeStrA(Dz1MetaTagDescrDate8Mode v);
DZ1_CPPLINK Dz1MetaTagDescrDate8Mode Dz1MetaTagDescrDate8ModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MetaTagDescrDate8ModeStrW(Dz1MetaTagDescrDate8Mode v);
DZ1_CPPLINK Dz1MetaTagDescrDate8Mode Dz1MetaTagDescrDate8ModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MetaTagDescrDate8ModeStr Dz1MetaTagDescrDate8ModeStrW
#define Dz1MetaTagDescrDate8ModeFromStr Dz1MetaTagDescrDate8ModeFromStrW
#else // UNICODE
#define Dz1MetaTagDescrDate8ModeStr Dz1MetaTagDescrDate8ModeStrA
#define Dz1MetaTagDescrDate8ModeFromStr Dz1MetaTagDescrDate8ModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MetaTagDescrDate8ModeStr Dz1MetaTagDescrDate8ModeStrA
#define Dz1MetaTagDescrDate8ModeFromStr Dz1MetaTagDescrDate8ModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrDate8Mode *Dz1MetaTagDescrDate8Mode_new(Dz1MetaTagDescrDate8Mode *src, Dz1Error *err);
static __inline__ Dz1MetaTagDescrDate8Mode *Dz1MetaTagDescrDate8Mode_gen(Dz1Error *err) { Dz1MetaTagDescrDate8Mode v = Dz1MetaTagDescrDate8Mode_max; return Dz1MetaTagDescrDate8Mode_new(&v, err); }
static __inline__ void Dz1MetaTagDescrDate8Mode_del(Dz1MetaTagDescrDate8Mode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MetaTagDescrDate8Mode_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrDate8Mode **p = (Dz1MetaTagDescrDate8Mode **)ptr;
	if (p != NULL) { Dz1MetaTagDescrDate8Mode_del(*p); *p = NULL; }
}
// Dz1MetaTagDescrDate8Mode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrDate
typedef struct Dz1MetaTagDescrDate
{
	Dz1MetaTagDescrDate8Mode	date8;
} Dz1MetaTagDescrDate;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrDate *Dz1MetaTagDescrDate_new(Dz1MetaTagDescrDate8Mode date8, Dz1Error *err);
static __inline__ Dz1MetaTagDescrDate *Dz1MetaTagDescrDate_gen(Dz1Error *err) { return Dz1MetaTagDescrDate_new(Dz1MetaTagDescrDate8Mode_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MetaTagDescrDate_copy(Dz1MetaTagDescrDate *dst, Dz1MetaTagDescrDate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrDate *Dz1MetaTagDescrDate_clone(Dz1MetaTagDescrDate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrDate_purge(Dz1MetaTagDescrDate *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrDate_del(Dz1MetaTagDescrDate *p);
static __inline__ void Dz1MetaTagDescrDate_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrDate **p = (Dz1MetaTagDescrDate **)ptr;
	if (p) { Dz1MetaTagDescrDate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrDate_dump(Dz1MetaTagDescrDate *p, int tab);
// Dz1MetaTagDescrDate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrAlias
struct Dz1MetaTagDescriptor;

typedef struct Dz1MetaTagDescrAlias
{
	u32_t							 origin_descr_id;
	struct Dz1MetaTagDescriptor		*origin_descr;
} Dz1MetaTagDescrAlias;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrAlias *Dz1MetaTagDescrAlias_new(u32_t origin_descr_id, Dz1Error *err);
static __inline__ Dz1MetaTagDescrAlias *Dz1MetaTagDescrAlias_gen(Dz1Error *err) { return Dz1MetaTagDescrAlias_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrAlias_purge(Dz1MetaTagDescrAlias *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrAlias_del(Dz1MetaTagDescrAlias *p);
static __inline__ void Dz1MetaTagDescrAlias_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrAlias **p = (Dz1MetaTagDescrAlias **)ptr;
	if (p) { Dz1MetaTagDescrAlias_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrAlias_dump(Dz1MetaTagDescrAlias *p, int tab);
// Dz1MetaTagDescrAlias
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescriptorUser
typedef struct Dz1MetaTagDescriptorUser
{
	u32_t		userHandlingType;
} Dz1MetaTagDescriptorUser;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescriptorUser *Dz1MetaTagDescriptorUser_new(u32_t userHandlingType, Dz1Error *err);
static __inline__ Dz1MetaTagDescriptorUser *Dz1MetaTagDescriptorUser_gen(Dz1Error *err) { return Dz1MetaTagDescriptorUser_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescriptorUser_purge(Dz1MetaTagDescriptorUser *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescriptorUser_del(Dz1MetaTagDescriptorUser *p);
static __inline__ void Dz1MetaTagDescriptorUser_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescriptorUser **p = (Dz1MetaTagDescriptorUser **)ptr;
	if (p) { Dz1MetaTagDescriptorUser_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescriptorUser_dump(Dz1MetaTagDescriptorUser *p, int tab);
// Dz1MetaTagDescriptorUser
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescriptorPresent
typedef enum Dz1MetaTagDescriptorPresent
{
	Dz1MetaTagDescriptorPresent_no_data,
	Dz1MetaTagDescriptorPresent_number,
	Dz1MetaTagDescriptorPresent_floating,
	Dz1MetaTagDescriptorPresent_grade,
	Dz1MetaTagDescriptorPresent_enumerate,
	Dz1MetaTagDescriptorPresent_date,
	Dz1MetaTagDescriptorPresent_tim,
	Dz1MetaTagDescriptorPresent_date_time,
	Dz1MetaTagDescriptorPresent_string,
	Dz1MetaTagDescriptorPresent_web_url,
	Dz1MetaTagDescriptorPresent_binary,
	Dz1MetaTagDescriptorPresent_user,
	Dz1MetaTagDescriptorPresent_alias,
	Dz1MetaTagDescriptorPresent_max
} Dz1MetaTagDescriptorPresent;

DZ1_CPPLINK str_t Dz1MetaTagDescriptorPresentStrA(Dz1MetaTagDescriptorPresent v);
DZ1_CPPLINK Dz1MetaTagDescriptorPresent Dz1MetaTagDescriptorPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MetaTagDescriptorPresentStrW(Dz1MetaTagDescriptorPresent v);
DZ1_CPPLINK Dz1MetaTagDescriptorPresent Dz1MetaTagDescriptorPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MetaTagDescriptorPresentStr Dz1MetaTagDescriptorPresentStrW
#define Dz1MetaTagDescriptorPresentFromStr Dz1MetaTagDescriptorPresentFromStrW
#else // UNICODE
#define Dz1MetaTagDescriptorPresentStr Dz1MetaTagDescriptorPresentStrA
#define Dz1MetaTagDescriptorPresentFromStr Dz1MetaTagDescriptorPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MetaTagDescriptorPresentStr Dz1MetaTagDescriptorPresentStrA
#define Dz1MetaTagDescriptorPresentFromStr Dz1MetaTagDescriptorPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescriptorPresent *Dz1MetaTagDescriptorPresent_new(Dz1MetaTagDescriptorPresent *src, Dz1Error *err);
static __inline__ Dz1MetaTagDescriptorPresent *Dz1MetaTagDescriptorPresent_gen(Dz1Error *err) { Dz1MetaTagDescriptorPresent v = Dz1MetaTagDescriptorPresent_max; return Dz1MetaTagDescriptorPresent_new(&v, err); }
static __inline__ void Dz1MetaTagDescriptorPresent_del(Dz1MetaTagDescriptorPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MetaTagDescriptorPresent_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescriptorPresent **p = (Dz1MetaTagDescriptorPresent **)ptr;
	if (p != NULL) { Dz1MetaTagDescriptorPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescriptorPresent_dump(Dz1MetaTagDescriptorPresent *v, int tab);
// Dz1MetaTagDescriptorPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescriptor
typedef struct Dz1MetaTagDescriptor
{
	Dz1MetaTagDescriptorPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t						*no_data;
		Dz1MetaTagDescrNumber		*number;
		Dz1MetaTagDescrFloat		*floating;
		Dz1MetaTagDescrGrade		*grade;
		Dz1MetaTagDescrEnums		*enumerate;
		Dz1MetaTagDescrDate			*date;
		u32_t						*tim;
		u32_t						*date_time;
		Dz1MetaTagDescrString		*string;
		u32_t						*web_url;
		u32_t						*binary;
		Dz1MetaTagDescriptorUser	*user;
		Dz1MetaTagDescrAlias		*alias;
	} x;
} Dz1MetaTagDescriptor;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescriptor *Dz1MetaTagDescriptor_new(Dz1MetaTagDescriptorPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1MetaTagDescriptor *Dz1MetaTagDescriptor_gen(Dz1Error *err) { return Dz1MetaTagDescriptor_new(Dz1MetaTagDescriptorPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescriptor_purge(Dz1MetaTagDescriptor *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescriptor_del(Dz1MetaTagDescriptor *p);
static __inline__ void Dz1MetaTagDescriptor_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescriptor **p = (Dz1MetaTagDescriptor **)ptr;
	if (p != NULL) { Dz1MetaTagDescriptor_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescriptor_dump(Dz1MetaTagDescriptor *p, int tab);
// Dz1MetaTagDescriptor
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataMode
typedef enum Dz1MetaTagDataMode
{
	Dz1MetaTagDataMode_Array,
	Dz1MetaTagDataMode_Single,
	Dz1MetaTagDataMode_Void,
	Dz1MetaTagDataMode_max
} Dz1MetaTagDataMode;

DZ1_CPPLINK str_t Dz1MetaTagDataModeStrA(Dz1MetaTagDataMode v);
DZ1_CPPLINK Dz1MetaTagDataMode Dz1MetaTagDataModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MetaTagDataModeStrW(Dz1MetaTagDataMode v);
DZ1_CPPLINK Dz1MetaTagDataMode Dz1MetaTagDataModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MetaTagDataModeStr Dz1MetaTagDataModeStrW
#define Dz1MetaTagDataModeFromStr Dz1MetaTagDataModeFromStrW
#else // UNICODE
#define Dz1MetaTagDataModeStr Dz1MetaTagDataModeStrA
#define Dz1MetaTagDataModeFromStr Dz1MetaTagDataModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MetaTagDataModeStr Dz1MetaTagDataModeStrA
#define Dz1MetaTagDataModeFromStr Dz1MetaTagDataModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDataMode *Dz1MetaTagDataMode_new(Dz1MetaTagDataMode *src, Dz1Error *err);
static __inline__ Dz1MetaTagDataMode *Dz1MetaTagDataMode_gen(Dz1Error *err) { Dz1MetaTagDataMode v = Dz1MetaTagDataMode_max; return Dz1MetaTagDataMode_new(&v, err); }
static __inline__ void Dz1MetaTagDataMode_del(Dz1MetaTagDataMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MetaTagDataMode_delAndSetNull(void *ptr)
{
	Dz1MetaTagDataMode **p = (Dz1MetaTagDataMode **)ptr;
	if (p != NULL) { Dz1MetaTagDataMode_del(*p); *p = NULL; }
}
// Dz1MetaTagDataMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEntry
typedef struct Dz1MetaTagDescrEntry
{
	u32_t					 id;
	Dz1Asn1UTF8Str			*name;
	wstr_t					 name_w;
	Dz1MetaTagRestrict		*status;
	Dz1MetaTagDescriptor	*descr;
	Dz1MetaTagDataMode		 mode;
	bool_t					 mandatory;
} Dz1MetaTagDescrEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrEntry *Dz1MetaTagDescrEntry_new(u32_t id, 
																	   Dz1Asn1UTF8Str *name, 
																	   Dz1MetaTagDescriptor *descr, 
																	   bool_t mandatory, Dz1Error *err);
static __inline__ Dz1MetaTagDescrEntry *Dz1MetaTagDescrEntry_gen(Dz1Error *err) { return Dz1MetaTagDescrEntry_new(0, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEntry_purge(Dz1MetaTagDescrEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEntry_del(Dz1MetaTagDescrEntry *p);
static __inline__ void Dz1MetaTagDescrEntry_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrEntry **p = (Dz1MetaTagDescrEntry **)ptr;
	if (p) { Dz1MetaTagDescrEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrEntry_dump(Dz1MetaTagDescrEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MetaTagDescrEntry_cmp(Dz1MetaTagDescrEntry *a, Dz1MetaTagDescrEntry *b); 
// Dz1MetaTagDescrEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrList
typedef struct Dz1MetaTagDescrList
{
	void *storage;
	unsigned int (*count)(struct Dz1MetaTagDescrList *p);
	Dz1Error (*travel)(struct Dz1MetaTagDescrList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MetaTagDescrList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MetaTagDescrList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagDescrEntry *entry), void *ptr);
	Dz1MetaTagDescrEntry **(*get_array)(struct Dz1MetaTagDescrList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MetaTagDescrList *p, Dz1MetaTagDescrEntry *data);
	bool_t (*remove)(struct Dz1MetaTagDescrList *p, Dz1MetaTagDescrEntry *key);
	Dz1MetaTagDescrEntry *(*extract)(struct Dz1MetaTagDescrList *p, Dz1MetaTagDescrEntry *key);
	Dz1MetaTagDescrEntry *(*find)(struct Dz1MetaTagDescrList *p, Dz1MetaTagDescrEntry *key);
	Dz1MetaTagDescrEntry *(*getTail)(struct Dz1MetaTagDescrList *p);
	int (*cmp)(Dz1MetaTagDescrEntry *a, Dz1MetaTagDescrEntry *b);
} Dz1MetaTagDescrList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDescrList *Dz1MetaTagDescrList_new(Dz1Error *err);
static __inline__ Dz1MetaTagDescrList *Dz1MetaTagDescrList_gen(Dz1Error *err) { return Dz1MetaTagDescrList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrList_purge(Dz1MetaTagDescrList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrList_del(Dz1MetaTagDescrList *p);
static __inline__ void Dz1MetaTagDescrList_delAndSetNull(void *ptr)
{
	Dz1MetaTagDescrList **p = (Dz1MetaTagDescrList **)ptr;
	if (p != NULL) { Dz1MetaTagDescrList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDescrList_dump(Dz1MetaTagDescrList *p, int tab);

// Dz1MetaTagDescrList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagUserTypeEntry
typedef struct Dz1MetaTagUserTypeEntry
{
	u32_t				 userType;
	Dz1Asn1UTF8Str		*userTypeName;
	wstr_t				 userTypeNameW;
	void				*resource;
	Dz1DelFunc			 resource_del;
	Dz1DumpFunc			 resource_dump;
	void				*userData;
	Dz1DelFunc			 userDataDel;
	Dz1DumpFunc			 userDataDump;
} Dz1MetaTagUserTypeEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagUserTypeEntry *Dz1MetaTagUserTypeEntry_new(u32_t userType, 
																			 Dz1Asn1UTF8Str *userTypeName, 
																			 void *resource, 
																			 Dz1DelFunc resource_del, 
																			 Dz1DumpFunc resource_dump, 
																			 void *userData, 
																			 Dz1DelFunc userDataDel, 
																			 Dz1DumpFunc userDataDump, Dz1Error *err);
static __inline__ Dz1MetaTagUserTypeEntry *Dz1MetaTagUserTypeEntry_gen(Dz1Error *err) { return Dz1MetaTagUserTypeEntry_new(0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagUserTypeEntry_purge(Dz1MetaTagUserTypeEntry *p);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagUserTypeEntry_del(Dz1MetaTagUserTypeEntry *p);	// User Customized
static __inline__ void Dz1MetaTagUserTypeEntry_delAndSetNull(void *ptr)
{
	Dz1MetaTagUserTypeEntry **p = (Dz1MetaTagUserTypeEntry **)ptr;
	if (p) { Dz1MetaTagUserTypeEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagUserTypeEntry_dump(Dz1MetaTagUserTypeEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MetaTagUserTypeEntry_cmp(Dz1MetaTagUserTypeEntry *a, Dz1MetaTagUserTypeEntry *b); 
// Dz1MetaTagUserTypeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagUserTypeList
typedef struct Dz1MetaTagUserTypeList
{
	void *storage;
	unsigned int (*count)(struct Dz1MetaTagUserTypeList *p);
	Dz1Error (*travel)(struct Dz1MetaTagUserTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagUserTypeEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MetaTagUserTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagUserTypeEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MetaTagUserTypeList *p, Dz1Error (*func)(void *ptr, Dz1MetaTagUserTypeEntry *entry), void *ptr);
	Dz1MetaTagUserTypeEntry **(*get_array)(struct Dz1MetaTagUserTypeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MetaTagUserTypeList *p, Dz1MetaTagUserTypeEntry *data);
	bool_t (*remove)(struct Dz1MetaTagUserTypeList *p, Dz1MetaTagUserTypeEntry *key);
	Dz1MetaTagUserTypeEntry *(*extract)(struct Dz1MetaTagUserTypeList *p, Dz1MetaTagUserTypeEntry *key);
	Dz1MetaTagUserTypeEntry *(*find)(struct Dz1MetaTagUserTypeList *p, Dz1MetaTagUserTypeEntry *key);
	int (*cmp)(Dz1MetaTagUserTypeEntry *a, Dz1MetaTagUserTypeEntry *b);
} Dz1MetaTagUserTypeList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagUserTypeList *Dz1MetaTagUserTypeList_new(Dz1Error *err);
static __inline__ Dz1MetaTagUserTypeList *Dz1MetaTagUserTypeList_gen(Dz1Error *err) { return Dz1MetaTagUserTypeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagUserTypeList_purge(Dz1MetaTagUserTypeList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagUserTypeList_del(Dz1MetaTagUserTypeList *p);
static __inline__ void Dz1MetaTagUserTypeList_delAndSetNull(void *ptr)
{
	Dz1MetaTagUserTypeList **p = (Dz1MetaTagUserTypeList **)ptr;
	if (p != NULL) { Dz1MetaTagUserTypeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagUserTypeList_dump(Dz1MetaTagUserTypeList *p, int tab);

// Dz1MetaTagUserTypeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDB
typedef struct Dz1MetaTagDB
{
	Dz1MetaTargetTypeList		*types;
	Dz1MetaTagDescrList			*table;
	Dz1MetaTagUserTypeList		*userTypes;
} Dz1MetaTagDB;

DZ1_CPPLINK DZ1_DLLPORT Dz1MetaTagDB *Dz1MetaTagDB_new(Dz1Error *err);
static __inline__ Dz1MetaTagDB *Dz1MetaTagDB_gen(Dz1Error *err) { return Dz1MetaTagDB_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDB_purge(Dz1MetaTagDB *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDB_del(Dz1MetaTagDB *p);
static __inline__ void Dz1MetaTagDB_delAndSetNull(void *ptr)
{
	Dz1MetaTagDB **p = (Dz1MetaTagDB **)ptr;
	if (p) { Dz1MetaTagDB_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MetaTagDB_dump(Dz1MetaTagDB *p, int tab);
// Dz1MetaTagDB
////////////////////////////////////////////////////////////////////////////////

#endif
