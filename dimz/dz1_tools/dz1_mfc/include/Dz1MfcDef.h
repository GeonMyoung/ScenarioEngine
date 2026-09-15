#ifndef _DZ1_TDC_DZ1_MFC_DEF_H_
#define _DZ1_TDC_DZ1_MFC_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_stdio_support.h"
#include "dz1_logics_def.h"
#include "dz1_stdio.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcKeyboardEvent
typedef enum Dz1MfcKeyboardEvent
{
	Dz1MfcKeyboardEvent_Pressed,
	Dz1MfcKeyboardEvent_Repeated,
	Dz1MfcKeyboardEvent_Released,
	Dz1MfcKeyboardEvent_max
} Dz1MfcKeyboardEvent;

DZ1_CPPLINK str_t Dz1MfcKeyboardEventStrA(Dz1MfcKeyboardEvent v);
DZ1_CPPLINK Dz1MfcKeyboardEvent Dz1MfcKeyboardEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MfcKeyboardEventStrW(Dz1MfcKeyboardEvent v);
DZ1_CPPLINK Dz1MfcKeyboardEvent Dz1MfcKeyboardEventFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MfcKeyboardEventStr Dz1MfcKeyboardEventStrW
#define Dz1MfcKeyboardEventFromStr Dz1MfcKeyboardEventFromStrW
#else // UNICODE
#define Dz1MfcKeyboardEventStr Dz1MfcKeyboardEventStrA
#define Dz1MfcKeyboardEventFromStr Dz1MfcKeyboardEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MfcKeyboardEventStr Dz1MfcKeyboardEventStrA
#define Dz1MfcKeyboardEventFromStr Dz1MfcKeyboardEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcKeyboardEvent *Dz1MfcKeyboardEvent_new(Dz1MfcKeyboardEvent *src, Dz1Error *err);
static __inline__ Dz1MfcKeyboardEvent *Dz1MfcKeyboardEvent_gen(Dz1Error *err) { Dz1MfcKeyboardEvent v = Dz1MfcKeyboardEvent_max; return Dz1MfcKeyboardEvent_new(&v, err); }
static __inline__ void Dz1MfcKeyboardEvent_del(Dz1MfcKeyboardEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MfcKeyboardEvent_delAndSetNull(void *ptr)
{
	Dz1MfcKeyboardEvent **p = (Dz1MfcKeyboardEvent **)ptr;
	if (p != NULL) { Dz1MfcKeyboardEvent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcKeyboardEvent_cmp(Dz1MfcKeyboardEvent *a, Dz1MfcKeyboardEvent *b);
// Dz1MfcKeyboardEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcKeyboardKeyEntry
typedef struct Dz1MfcKeyboardKeyEntry
{
	Dz1MfcKeyboardEvent		event;
	bool_t					isExtKey;
	u32_t					code;
	s32_t					cmd;
	s32_t					arg;
} Dz1MfcKeyboardKeyEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyEntry_new(Dz1MfcKeyboardEvent event, 
																		   bool_t isExtKey, 
																		   u32_t code, 
																		   s32_t cmd, 
																		   s32_t arg, Dz1Error *err);
static __inline__ Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyEntry_gen(Dz1Error *err) { return Dz1MfcKeyboardKeyEntry_new(Dz1MfcKeyboardEvent_max, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcKeyboardKeyEntry_copy(Dz1MfcKeyboardKeyEntry *dst, Dz1MfcKeyboardKeyEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyEntry_clone(Dz1MfcKeyboardKeyEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcKeyboardKeyEntry_purge(Dz1MfcKeyboardKeyEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcKeyboardKeyEntry_del(Dz1MfcKeyboardKeyEntry *p);
static __inline__ void Dz1MfcKeyboardKeyEntry_delAndSetNull(void *ptr)
{
	Dz1MfcKeyboardKeyEntry **p = (Dz1MfcKeyboardKeyEntry **)ptr;
	if (p) { Dz1MfcKeyboardKeyEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcKeyboardKeyEntry_dump(Dz1MfcKeyboardKeyEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcKeyboardKeyEntry_cmp(Dz1MfcKeyboardKeyEntry *a, Dz1MfcKeyboardKeyEntry *b); 
// Dz1MfcKeyboardKeyEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcKeyboardKeyList
typedef struct Dz1MfcKeyboardKeyList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcKeyboardKeyList *p);
	Dz1Error (*travel)(struct Dz1MfcKeyboardKeyList *p, Dz1Error (*func)(void *ptr, Dz1MfcKeyboardKeyEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcKeyboardKeyList *p, Dz1Error (*func)(void *ptr, Dz1MfcKeyboardKeyEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcKeyboardKeyList *p, Dz1Error (*func)(void *ptr, Dz1MfcKeyboardKeyEntry *entry), void *ptr);
	Dz1MfcKeyboardKeyEntry **(*get_array)(struct Dz1MfcKeyboardKeyList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcKeyboardKeyList *p, Dz1MfcKeyboardKeyEntry *data);
	bool_t (*remove)(struct Dz1MfcKeyboardKeyList *p, Dz1MfcKeyboardKeyEntry *key);
	Dz1MfcKeyboardKeyEntry *(*extract)(struct Dz1MfcKeyboardKeyList *p, Dz1MfcKeyboardKeyEntry *key);
	Dz1MfcKeyboardKeyEntry *(*find)(struct Dz1MfcKeyboardKeyList *p, Dz1MfcKeyboardKeyEntry *key);
	int (*cmp)(Dz1MfcKeyboardKeyEntry *a, Dz1MfcKeyboardKeyEntry *b);
} Dz1MfcKeyboardKeyList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcKeyboardKeyList *Dz1MfcKeyboardKeyList_new(Dz1Error *err);
static __inline__ Dz1MfcKeyboardKeyList *Dz1MfcKeyboardKeyList_gen(Dz1Error *err) { return Dz1MfcKeyboardKeyList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcKeyboardKeyList *Dz1MfcKeyboardKeyList_clone(Dz1MfcKeyboardKeyList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcKeyboardKeyList_purge(Dz1MfcKeyboardKeyList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcKeyboardKeyList_del(Dz1MfcKeyboardKeyList *p);
static __inline__ void Dz1MfcKeyboardKeyList_delAndSetNull(void *ptr)
{
	Dz1MfcKeyboardKeyList **p = (Dz1MfcKeyboardKeyList **)ptr;
	if (p != NULL) { Dz1MfcKeyboardKeyList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcKeyboardKeyList_dump(Dz1MfcKeyboardKeyList *p, int tab);

// Dz1MfcKeyboardKeyList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcLanManPathEntry
typedef struct Dz1MfcLanManPathEntry
{
	Dz1Str		name;
} Dz1MfcLanManPathEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcLanManPathEntry *Dz1MfcLanManPathEntry_new(Dz1Str name, Dz1Error *err);
static __inline__ Dz1MfcLanManPathEntry *Dz1MfcLanManPathEntry_gen(Dz1Error *err) { return Dz1MfcLanManPathEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcLanManPathEntry_copy(Dz1MfcLanManPathEntry *dst, Dz1MfcLanManPathEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcLanManPathEntry *Dz1MfcLanManPathEntry_clone(Dz1MfcLanManPathEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcLanManPathEntry_purge(Dz1MfcLanManPathEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcLanManPathEntry_del(Dz1MfcLanManPathEntry *p);
static __inline__ void Dz1MfcLanManPathEntry_delAndSetNull(void *ptr)
{
	Dz1MfcLanManPathEntry **p = (Dz1MfcLanManPathEntry **)ptr;
	if (p) { Dz1MfcLanManPathEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcLanManPathEntry_dump(Dz1MfcLanManPathEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcLanManPathEntry_cmp(Dz1MfcLanManPathEntry *a, Dz1MfcLanManPathEntry *b); 
// Dz1MfcLanManPathEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcLanManPathList
typedef struct Dz1MfcLanManPathList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcLanManPathList *p);
	Dz1Error (*travel)(struct Dz1MfcLanManPathList *p, Dz1Error (*func)(void *ptr, Dz1MfcLanManPathEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcLanManPathList *p, Dz1Error (*func)(void *ptr, Dz1MfcLanManPathEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcLanManPathList *p, Dz1Error (*func)(void *ptr, Dz1MfcLanManPathEntry *entry), void *ptr);
	Dz1MfcLanManPathEntry **(*get_array)(struct Dz1MfcLanManPathList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcLanManPathList *p, Dz1MfcLanManPathEntry *data);
	bool_t (*remove)(struct Dz1MfcLanManPathList *p, Dz1MfcLanManPathEntry *key);
	Dz1MfcLanManPathEntry *(*extract)(struct Dz1MfcLanManPathList *p, Dz1MfcLanManPathEntry *key);
	Dz1MfcLanManPathEntry *(*find)(struct Dz1MfcLanManPathList *p, Dz1MfcLanManPathEntry *key);
	int (*cmp)(Dz1MfcLanManPathEntry *a, Dz1MfcLanManPathEntry *b);
} Dz1MfcLanManPathList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcLanManPathList *Dz1MfcLanManPathList_new(Dz1Error *err);
static __inline__ Dz1MfcLanManPathList *Dz1MfcLanManPathList_gen(Dz1Error *err) { return Dz1MfcLanManPathList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcLanManPathList *Dz1MfcLanManPathList_clone(Dz1MfcLanManPathList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcLanManPathList_purge(Dz1MfcLanManPathList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcLanManPathList_del(Dz1MfcLanManPathList *p);
static __inline__ void Dz1MfcLanManPathList_delAndSetNull(void *ptr)
{
	Dz1MfcLanManPathList **p = (Dz1MfcLanManPathList **)ptr;
	if (p != NULL) { Dz1MfcLanManPathList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcLanManPathList_dump(Dz1MfcLanManPathList *p, int tab);

// Dz1MfcLanManPathList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterValueRangeSigned
typedef struct Dz1MfcListFilterValueRangeSigned
{
	s64_t		lowValue;
	s64_t		highValue;
} Dz1MfcListFilterValueRangeSigned;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterValueRangeSigned *Dz1MfcListFilterValueRangeSigned_new(s64_t lowValue, 
																							   s64_t highValue, Dz1Error *err);
static __inline__ Dz1MfcListFilterValueRangeSigned *Dz1MfcListFilterValueRangeSigned_gen(Dz1Error *err) { return Dz1MfcListFilterValueRangeSigned_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcListFilterValueRangeSigned_copy(Dz1MfcListFilterValueRangeSigned *dst, Dz1MfcListFilterValueRangeSigned *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterValueRangeSigned *Dz1MfcListFilterValueRangeSigned_clone(Dz1MfcListFilterValueRangeSigned *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValueRangeSigned_purge(Dz1MfcListFilterValueRangeSigned *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValueRangeSigned_del(Dz1MfcListFilterValueRangeSigned *p);
static __inline__ void Dz1MfcListFilterValueRangeSigned_delAndSetNull(void *ptr)
{
	Dz1MfcListFilterValueRangeSigned **p = (Dz1MfcListFilterValueRangeSigned **)ptr;
	if (p) { Dz1MfcListFilterValueRangeSigned_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValueRangeSigned_dump(Dz1MfcListFilterValueRangeSigned *p, int tab);
// Dz1MfcListFilterValueRangeSigned
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterValueRangeUnsigned
typedef struct Dz1MfcListFilterValueRangeUnsigned
{
	u64_t		lowValue;
	u64_t		highValue;
} Dz1MfcListFilterValueRangeUnsigned;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterValueRangeUnsigned *Dz1MfcListFilterValueRangeUnsigned_new(u64_t lowValue, 
																								   u64_t highValue, Dz1Error *err);
static __inline__ Dz1MfcListFilterValueRangeUnsigned *Dz1MfcListFilterValueRangeUnsigned_gen(Dz1Error *err) { return Dz1MfcListFilterValueRangeUnsigned_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcListFilterValueRangeUnsigned_copy(Dz1MfcListFilterValueRangeUnsigned *dst, Dz1MfcListFilterValueRangeUnsigned *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterValueRangeUnsigned *Dz1MfcListFilterValueRangeUnsigned_clone(Dz1MfcListFilterValueRangeUnsigned *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValueRangeUnsigned_purge(Dz1MfcListFilterValueRangeUnsigned *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValueRangeUnsigned_del(Dz1MfcListFilterValueRangeUnsigned *p);
static __inline__ void Dz1MfcListFilterValueRangeUnsigned_delAndSetNull(void *ptr)
{
	Dz1MfcListFilterValueRangeUnsigned **p = (Dz1MfcListFilterValueRangeUnsigned **)ptr;
	if (p) { Dz1MfcListFilterValueRangeUnsigned_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValueRangeUnsigned_dump(Dz1MfcListFilterValueRangeUnsigned *p, int tab);
// Dz1MfcListFilterValueRangeUnsigned
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterValuePresent
typedef enum Dz1MfcListFilterValuePresent
{
	Dz1MfcListFilterValuePresent_sNum,
	Dz1MfcListFilterValuePresent_uNum,
	Dz1MfcListFilterValuePresent_sRange,
	Dz1MfcListFilterValuePresent_uRange,
	Dz1MfcListFilterValuePresent_txtValue,
	Dz1MfcListFilterValuePresent_txtList,
	Dz1MfcListFilterValuePresent_max
} Dz1MfcListFilterValuePresent;

DZ1_CPPLINK str_t Dz1MfcListFilterValuePresentStrA(Dz1MfcListFilterValuePresent v);
DZ1_CPPLINK Dz1MfcListFilterValuePresent Dz1MfcListFilterValuePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MfcListFilterValuePresentStrW(Dz1MfcListFilterValuePresent v);
DZ1_CPPLINK Dz1MfcListFilterValuePresent Dz1MfcListFilterValuePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MfcListFilterValuePresentStr Dz1MfcListFilterValuePresentStrW
#define Dz1MfcListFilterValuePresentFromStr Dz1MfcListFilterValuePresentFromStrW
#else // UNICODE
#define Dz1MfcListFilterValuePresentStr Dz1MfcListFilterValuePresentStrA
#define Dz1MfcListFilterValuePresentFromStr Dz1MfcListFilterValuePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MfcListFilterValuePresentStr Dz1MfcListFilterValuePresentStrA
#define Dz1MfcListFilterValuePresentFromStr Dz1MfcListFilterValuePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterValuePresent *Dz1MfcListFilterValuePresent_new(Dz1MfcListFilterValuePresent *src, Dz1Error *err);
static __inline__ Dz1MfcListFilterValuePresent *Dz1MfcListFilterValuePresent_gen(Dz1Error *err) { Dz1MfcListFilterValuePresent v = Dz1MfcListFilterValuePresent_max; return Dz1MfcListFilterValuePresent_new(&v, err); }
#define Dz1MfcListFilterValuePresent_clone             Dz1MfcListFilterValuePresent_new
static __inline__ void Dz1MfcListFilterValuePresent_del(Dz1MfcListFilterValuePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MfcListFilterValuePresent_delAndSetNull(void *ptr)
{
	Dz1MfcListFilterValuePresent **p = (Dz1MfcListFilterValuePresent **)ptr;
	if (p != NULL) { Dz1MfcListFilterValuePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValuePresent_dump(Dz1MfcListFilterValuePresent *v, int tab);
// Dz1MfcListFilterValuePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterValue
typedef struct Dz1MfcListFilterValue
{
	Dz1MfcListFilterValuePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		s64_t									 sNum;
		u64_t									 uNum;
		Dz1MfcListFilterValueRangeSigned		*sRange;
		Dz1MfcListFilterValueRangeUnsigned		*uRange;
		Dz1Str									 txtValue;
		Dz1LogicStringArr						*txtList;
	} x;
} Dz1MfcListFilterValue;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterValue *Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1MfcListFilterValue *Dz1MfcListFilterValue_gen(Dz1Error *err) { return Dz1MfcListFilterValue_new(Dz1MfcListFilterValuePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1MfcListFilterValue_copy(Dz1MfcListFilterValue *dst, Dz1MfcListFilterValue *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterValue *Dz1MfcListFilterValue_clone(Dz1MfcListFilterValue *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValue_purge(Dz1MfcListFilterValue *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValue_del(Dz1MfcListFilterValue *p);
static __inline__ void Dz1MfcListFilterValue_delAndSetNull(void *ptr)
{
	Dz1MfcListFilterValue **p = (Dz1MfcListFilterValue **)ptr;
	if (p != NULL) { Dz1MfcListFilterValue_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterValue_dump(Dz1MfcListFilterValue *p, int tab);
// Dz1MfcListFilterValue
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterEntry
typedef struct Dz1MfcListFilterEntry
{
	s32_t						 col;
	Dz1LogicMatchType			 mode;
	Dz1MfcListFilterValue		*value;
} Dz1MfcListFilterEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterEntry *Dz1MfcListFilterEntry_new(s32_t col, 
																		 Dz1LogicMatchType mode, 
																		 Dz1MfcListFilterValue *value, Dz1Error *err);
static __inline__ Dz1MfcListFilterEntry *Dz1MfcListFilterEntry_gen(Dz1Error *err) { return Dz1MfcListFilterEntry_new(0, Dz1LogicMatchType_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcListFilterEntry_copy(Dz1MfcListFilterEntry *dst, Dz1MfcListFilterEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterEntry *Dz1MfcListFilterEntry_clone(Dz1MfcListFilterEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterEntry_purge(Dz1MfcListFilterEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterEntry_del(Dz1MfcListFilterEntry *p);
static __inline__ void Dz1MfcListFilterEntry_delAndSetNull(void *ptr)
{
	Dz1MfcListFilterEntry **p = (Dz1MfcListFilterEntry **)ptr;
	if (p) { Dz1MfcListFilterEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterEntry_dump(Dz1MfcListFilterEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcListFilterEntry_cmp(Dz1MfcListFilterEntry *a, Dz1MfcListFilterEntry *b); 
// Dz1MfcListFilterEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcListFilterList
typedef struct Dz1MfcListFilterList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcListFilterList *p);
	Dz1Error (*travel)(struct Dz1MfcListFilterList *p, Dz1Error (*func)(void *ptr, Dz1MfcListFilterEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcListFilterList *p, Dz1Error (*func)(void *ptr, Dz1MfcListFilterEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcListFilterList *p, Dz1Error (*func)(void *ptr, Dz1MfcListFilterEntry *entry), void *ptr);
	Dz1MfcListFilterEntry **(*get_array)(struct Dz1MfcListFilterList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcListFilterList *p, Dz1MfcListFilterEntry *data);
	bool_t (*remove)(struct Dz1MfcListFilterList *p, Dz1MfcListFilterEntry *key);
	Dz1MfcListFilterEntry *(*extract)(struct Dz1MfcListFilterList *p, Dz1MfcListFilterEntry *key);
	Dz1MfcListFilterEntry *(*find)(struct Dz1MfcListFilterList *p, Dz1MfcListFilterEntry *key);
	int (*cmp)(Dz1MfcListFilterEntry *a, Dz1MfcListFilterEntry *b);
} Dz1MfcListFilterList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterList *Dz1MfcListFilterList_new(Dz1Error *err);
static __inline__ Dz1MfcListFilterList *Dz1MfcListFilterList_gen(Dz1Error *err) { return Dz1MfcListFilterList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcListFilterList *Dz1MfcListFilterList_clone(Dz1MfcListFilterList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterList_purge(Dz1MfcListFilterList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterList_del(Dz1MfcListFilterList *p);
static __inline__ void Dz1MfcListFilterList_delAndSetNull(void *ptr)
{
	Dz1MfcListFilterList **p = (Dz1MfcListFilterList **)ptr;
	if (p != NULL) { Dz1MfcListFilterList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcListFilterList_dump(Dz1MfcListFilterList *p, int tab);

// Dz1MfcListFilterList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcProgInfoArgEntry
typedef struct Dz1MfcProgInfoArgEntry
{
	u32_t		idx;
	Dz1Str		str;
} Dz1MfcProgInfoArgEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcProgInfoArgEntry *Dz1MfcProgInfoArgEntry_new(u32_t idx, 
																		   Dz1Str str, Dz1Error *err);
static __inline__ Dz1MfcProgInfoArgEntry *Dz1MfcProgInfoArgEntry_gen(Dz1Error *err) { return Dz1MfcProgInfoArgEntry_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcProgInfoArgEntry_copy(Dz1MfcProgInfoArgEntry *dst, Dz1MfcProgInfoArgEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcProgInfoArgEntry *Dz1MfcProgInfoArgEntry_clone(Dz1MfcProgInfoArgEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfoArgEntry_purge(Dz1MfcProgInfoArgEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfoArgEntry_del(Dz1MfcProgInfoArgEntry *p);
static __inline__ void Dz1MfcProgInfoArgEntry_delAndSetNull(void *ptr)
{
	Dz1MfcProgInfoArgEntry **p = (Dz1MfcProgInfoArgEntry **)ptr;
	if (p) { Dz1MfcProgInfoArgEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfoArgEntry_dump(Dz1MfcProgInfoArgEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcProgInfoArgEntry_cmp(Dz1MfcProgInfoArgEntry *a, Dz1MfcProgInfoArgEntry *b); 
// Dz1MfcProgInfoArgEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcProgInfoArgList
typedef struct Dz1MfcProgInfoArgList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcProgInfoArgList *p);
	Dz1Error (*travel)(struct Dz1MfcProgInfoArgList *p, Dz1Error (*func)(void *ptr, Dz1MfcProgInfoArgEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcProgInfoArgList *p, Dz1Error (*func)(void *ptr, Dz1MfcProgInfoArgEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcProgInfoArgList *p, Dz1Error (*func)(void *ptr, Dz1MfcProgInfoArgEntry *entry), void *ptr);
	Dz1MfcProgInfoArgEntry **(*get_array)(struct Dz1MfcProgInfoArgList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcProgInfoArgList *p, Dz1MfcProgInfoArgEntry *data);
	bool_t (*remove)(struct Dz1MfcProgInfoArgList *p, Dz1MfcProgInfoArgEntry *key);
	Dz1MfcProgInfoArgEntry *(*extract)(struct Dz1MfcProgInfoArgList *p, Dz1MfcProgInfoArgEntry *key);
	Dz1MfcProgInfoArgEntry *(*find)(struct Dz1MfcProgInfoArgList *p, Dz1MfcProgInfoArgEntry *key);
	int (*cmp)(Dz1MfcProgInfoArgEntry *a, Dz1MfcProgInfoArgEntry *b);
} Dz1MfcProgInfoArgList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcProgInfoArgList *Dz1MfcProgInfoArgList_new(Dz1Error *err);
static __inline__ Dz1MfcProgInfoArgList *Dz1MfcProgInfoArgList_gen(Dz1Error *err) { return Dz1MfcProgInfoArgList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcProgInfoArgList *Dz1MfcProgInfoArgList_clone(Dz1MfcProgInfoArgList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfoArgList_purge(Dz1MfcProgInfoArgList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfoArgList_del(Dz1MfcProgInfoArgList *p);
static __inline__ void Dz1MfcProgInfoArgList_delAndSetNull(void *ptr)
{
	Dz1MfcProgInfoArgList **p = (Dz1MfcProgInfoArgList **)ptr;
	if (p != NULL) { Dz1MfcProgInfoArgList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfoArgList_dump(Dz1MfcProgInfoArgList *p, int tab);

// Dz1MfcProgInfoArgList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcProgInfo
typedef struct Dz1MfcProgInfo
{
	Dz1Str						 cmd_line;
	Dz1Str						 path_name_ext;
	Dz1Str						 path;
	Dz1Str						 name_ext;
	Dz1Str						 name;
	Dz1Str						 ext;
	Dz1MfcProgInfoArgList		*args;
} Dz1MfcProgInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcProgInfo *Dz1MfcProgInfo_new(Dz1Str cmd_line, 
														   Dz1Str path_name_ext, 
														   Dz1Str path, 
														   Dz1Str name_ext, 
														   Dz1Str name, 
														   Dz1Str ext, Dz1Error *err);
static __inline__ Dz1MfcProgInfo *Dz1MfcProgInfo_gen(Dz1Error *err) { return Dz1MfcProgInfo_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcProgInfo_copy(Dz1MfcProgInfo *dst, Dz1MfcProgInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcProgInfo *Dz1MfcProgInfo_clone(Dz1MfcProgInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfo_purge(Dz1MfcProgInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfo_del(Dz1MfcProgInfo *p);
static __inline__ void Dz1MfcProgInfo_delAndSetNull(void *ptr)
{
	Dz1MfcProgInfo **p = (Dz1MfcProgInfo **)ptr;
	if (p) { Dz1MfcProgInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcProgInfo_dump(Dz1MfcProgInfo *p, int tab);
// Dz1MfcProgInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DirCatalogACache
typedef struct Dz1DirCatalogACache
{
	void *storage;
	unsigned int (*count)(struct Dz1DirCatalogACache *p);
	Dz1Error (*travel)(struct Dz1DirCatalogACache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogA *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1DirCatalogACache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1DirCatalogACache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogA *entry), void *ptr);
	Dz1DirCatalogA **(*get_array)(struct Dz1DirCatalogACache *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1DirCatalogACache *p, Dz1DirCatalogA *data);
	bool_t (*remove)(struct Dz1DirCatalogACache *p, Dz1DirCatalogA *key);
	Dz1DirCatalogA *(*extract)(struct Dz1DirCatalogACache *p, Dz1DirCatalogA *key);
	Dz1DirCatalogA *(*find)(struct Dz1DirCatalogACache *p, Dz1DirCatalogA *key);
	int (*cmp)(Dz1DirCatalogA *a, Dz1DirCatalogA *b);
} Dz1DirCatalogACache;

DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogACache *Dz1DirCatalogACache_new(Dz1Error *err);
static __inline__ Dz1DirCatalogACache *Dz1DirCatalogACache_gen(Dz1Error *err) { return Dz1DirCatalogACache_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1DirCatalogACache_purge(Dz1DirCatalogACache *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DirCatalogACache_del(Dz1DirCatalogACache *p);
static __inline__ void Dz1DirCatalogACache_delAndSetNull(void *ptr)
{
	Dz1DirCatalogACache **p = (Dz1DirCatalogACache **)ptr;
	if (p != NULL) { Dz1DirCatalogACache_del(*p); *p = NULL; }
}

// Dz1DirCatalogACache
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DirCatalogWCache
typedef struct Dz1DirCatalogWCache
{
	void *storage;
	unsigned int (*count)(struct Dz1DirCatalogWCache *p);
	Dz1Error (*travel)(struct Dz1DirCatalogWCache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogW *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1DirCatalogWCache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1DirCatalogWCache *p, Dz1Error (*func)(void *ptr, Dz1DirCatalogW *entry), void *ptr);
	Dz1DirCatalogW **(*get_array)(struct Dz1DirCatalogWCache *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1DirCatalogWCache *p, Dz1DirCatalogW *data);
	bool_t (*remove)(struct Dz1DirCatalogWCache *p, Dz1DirCatalogW *key);
	Dz1DirCatalogW *(*extract)(struct Dz1DirCatalogWCache *p, Dz1DirCatalogW *key);
	Dz1DirCatalogW *(*find)(struct Dz1DirCatalogWCache *p, Dz1DirCatalogW *key);
	int (*cmp)(Dz1DirCatalogW *a, Dz1DirCatalogW *b);
} Dz1DirCatalogWCache;

DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogWCache *Dz1DirCatalogWCache_new(Dz1Error *err);
static __inline__ Dz1DirCatalogWCache *Dz1DirCatalogWCache_gen(Dz1Error *err) { return Dz1DirCatalogWCache_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1DirCatalogWCache_purge(Dz1DirCatalogWCache *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1DirCatalogWCache_del(Dz1DirCatalogWCache *p);
static __inline__ void Dz1DirCatalogWCache_delAndSetNull(void *ptr)
{
	Dz1DirCatalogWCache **p = (Dz1DirCatalogWCache **)ptr;
	if (p != NULL) { Dz1DirCatalogWCache_del(*p); *p = NULL; }
}

// Dz1DirCatalogWCache
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcPathTreeNodeList
typedef struct Dz1MfcPathTreeNodeList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcPathTreeNodeList *p);
	Dz1Error (*travel)(struct Dz1MfcPathTreeNodeList *p, Dz1Error (*func)(void *ptr, struct Dz1MfcPathTreeNode *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcPathTreeNodeList *p, Dz1Error (*func)(void *ptr, struct Dz1MfcPathTreeNode *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcPathTreeNodeList *p, Dz1Error (*func)(void *ptr, struct Dz1MfcPathTreeNode *entry), void *ptr);
	struct Dz1MfcPathTreeNode **(*get_array)(struct Dz1MfcPathTreeNodeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcPathTreeNodeList *p, struct Dz1MfcPathTreeNode *data);
	bool_t (*remove)(struct Dz1MfcPathTreeNodeList *p, struct Dz1MfcPathTreeNode *key);
	struct Dz1MfcPathTreeNode *(*extract)(struct Dz1MfcPathTreeNodeList *p, struct Dz1MfcPathTreeNode *key);
	struct Dz1MfcPathTreeNode *(*find)(struct Dz1MfcPathTreeNodeList *p, struct Dz1MfcPathTreeNode *key);
	int (*cmp)(struct Dz1MfcPathTreeNode *a, struct Dz1MfcPathTreeNode *b);
} Dz1MfcPathTreeNodeList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcPathTreeNodeList *Dz1MfcPathTreeNodeList_new(Dz1Error *err);
static __inline__ Dz1MfcPathTreeNodeList *Dz1MfcPathTreeNodeList_gen(Dz1Error *err) { return Dz1MfcPathTreeNodeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcPathTreeNodeList *Dz1MfcPathTreeNodeList_clone(Dz1MfcPathTreeNodeList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcPathTreeNodeList_purge(Dz1MfcPathTreeNodeList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcPathTreeNodeList_del(Dz1MfcPathTreeNodeList *p);
static __inline__ void Dz1MfcPathTreeNodeList_delAndSetNull(void *ptr)
{
	Dz1MfcPathTreeNodeList **p = (Dz1MfcPathTreeNodeList **)ptr;
	if (p != NULL) { Dz1MfcPathTreeNodeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcPathTreeNodeList_dump(Dz1MfcPathTreeNodeList *p, int tab);

// Dz1MfcPathTreeNodeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcPathTreeNode
struct Dz1MfcPathTreeNode;

typedef struct Dz1MfcPathTreeNode
{
	Dz1Str							 name;
	struct Dz1MfcPathTreeNode		*parent;
	Dz1MfcPathTreeNodeList			*childs;
} Dz1MfcPathTreeNode;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcPathTreeNode *Dz1MfcPathTreeNode_new(Dz1Str name, 
																   struct Dz1MfcPathTreeNode *parent, Dz1Error *err);
static __inline__ Dz1MfcPathTreeNode *Dz1MfcPathTreeNode_gen(Dz1Error *err) { return Dz1MfcPathTreeNode_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcPathTreeNode_copy(Dz1MfcPathTreeNode *dst, Dz1MfcPathTreeNode *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcPathTreeNode *Dz1MfcPathTreeNode_clone(Dz1MfcPathTreeNode *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcPathTreeNode_purge(Dz1MfcPathTreeNode *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcPathTreeNode_del(Dz1MfcPathTreeNode *p);
static __inline__ void Dz1MfcPathTreeNode_delAndSetNull(void *ptr)
{
	Dz1MfcPathTreeNode **p = (Dz1MfcPathTreeNode **)ptr;
	if (p) { Dz1MfcPathTreeNode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcPathTreeNode_dump(Dz1MfcPathTreeNode *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcPathTreeNode_cmp(Dz1MfcPathTreeNode *a, Dz1MfcPathTreeNode *b); 
// Dz1MfcPathTreeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlParseEnv
typedef struct Dz1MfcHtmlParseEnv
{
	Dz1Str		src;
	Dz1Str		lex_ptr;
} Dz1MfcHtmlParseEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlParseEnv *Dz1MfcHtmlParseEnv_new(Dz1Str src, 
																   Dz1Str lex_ptr, Dz1Error *err);
static __inline__ Dz1MfcHtmlParseEnv *Dz1MfcHtmlParseEnv_gen(Dz1Error *err) { return Dz1MfcHtmlParseEnv_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcHtmlParseEnv_copy(Dz1MfcHtmlParseEnv *dst, Dz1MfcHtmlParseEnv *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlParseEnv *Dz1MfcHtmlParseEnv_clone(Dz1MfcHtmlParseEnv *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlParseEnv_purge(Dz1MfcHtmlParseEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlParseEnv_del(Dz1MfcHtmlParseEnv *p);
static __inline__ void Dz1MfcHtmlParseEnv_delAndSetNull(void *ptr)
{
	Dz1MfcHtmlParseEnv **p = (Dz1MfcHtmlParseEnv **)ptr;
	if (p) { Dz1MfcHtmlParseEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlParseEnv_dump(Dz1MfcHtmlParseEnv *p, int tab);
// Dz1MfcHtmlParseEnv
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlTokenType
typedef enum Dz1MfcHtmlTokenType
{
	Dz1MfcHtmlTokenType_undef,
	Dz1MfcHtmlTokenType_space,
	Dz1MfcHtmlTokenType_new_line,
	Dz1MfcHtmlTokenType_start,
	Dz1MfcHtmlTokenType_stop,
	Dz1MfcHtmlTokenType_term,
	Dz1MfcHtmlTokenType_equal,
	Dz1MfcHtmlTokenType_string,
	Dz1MfcHtmlTokenType_symbol,
	Dz1MfcHtmlTokenType_max
} Dz1MfcHtmlTokenType;

DZ1_CPPLINK str_t Dz1MfcHtmlTokenTypeStrA(Dz1MfcHtmlTokenType v);
DZ1_CPPLINK Dz1MfcHtmlTokenType Dz1MfcHtmlTokenTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MfcHtmlTokenTypeStrW(Dz1MfcHtmlTokenType v);
DZ1_CPPLINK Dz1MfcHtmlTokenType Dz1MfcHtmlTokenTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MfcHtmlTokenTypeStr Dz1MfcHtmlTokenTypeStrW
#define Dz1MfcHtmlTokenTypeFromStr Dz1MfcHtmlTokenTypeFromStrW
#else // UNICODE
#define Dz1MfcHtmlTokenTypeStr Dz1MfcHtmlTokenTypeStrA
#define Dz1MfcHtmlTokenTypeFromStr Dz1MfcHtmlTokenTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MfcHtmlTokenTypeStr Dz1MfcHtmlTokenTypeStrA
#define Dz1MfcHtmlTokenTypeFromStr Dz1MfcHtmlTokenTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlTokenType *Dz1MfcHtmlTokenType_new(Dz1MfcHtmlTokenType *src, Dz1Error *err);
static __inline__ Dz1MfcHtmlTokenType *Dz1MfcHtmlTokenType_gen(Dz1Error *err) { Dz1MfcHtmlTokenType v = Dz1MfcHtmlTokenType_max; return Dz1MfcHtmlTokenType_new(&v, err); }
static __inline__ void Dz1MfcHtmlTokenType_del(Dz1MfcHtmlTokenType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MfcHtmlTokenType_delAndSetNull(void *ptr)
{
	Dz1MfcHtmlTokenType **p = (Dz1MfcHtmlTokenType **)ptr;
	if (p != NULL) { Dz1MfcHtmlTokenType_del(*p); *p = NULL; }
}
// Dz1MfcHtmlTokenType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlToken
typedef struct Dz1MfcHtmlToken
{
	Dz1MfcHtmlTokenType		type;
	Dz1Str					value;
} Dz1MfcHtmlToken;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlToken *Dz1MfcHtmlToken_new(Dz1MfcHtmlTokenType type, 
															 Dz1Str value, Dz1Error *err);
static __inline__ Dz1MfcHtmlToken *Dz1MfcHtmlToken_gen(Dz1Error *err) { return Dz1MfcHtmlToken_new(Dz1MfcHtmlTokenType_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcHtmlToken_copy(Dz1MfcHtmlToken *dst, Dz1MfcHtmlToken *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlToken *Dz1MfcHtmlToken_clone(Dz1MfcHtmlToken *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlToken_purge(Dz1MfcHtmlToken *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlToken_del(Dz1MfcHtmlToken *p);
static __inline__ void Dz1MfcHtmlToken_delAndSetNull(void *ptr)
{
	Dz1MfcHtmlToken **p = (Dz1MfcHtmlToken **)ptr;
	if (p) { Dz1MfcHtmlToken_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlToken_dump(Dz1MfcHtmlToken *p, int tab);
// Dz1MfcHtmlToken
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlTagAttr
typedef struct Dz1MfcHtmlTagAttr
{
	Dz1Str		id;
	Dz1Str		value;
} Dz1MfcHtmlTagAttr;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlTagAttr *Dz1MfcHtmlTagAttr_new(Dz1Str id, 
																 Dz1Str value, Dz1Error *err);
static __inline__ Dz1MfcHtmlTagAttr *Dz1MfcHtmlTagAttr_gen(Dz1Error *err) { return Dz1MfcHtmlTagAttr_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcHtmlTagAttr_copy(Dz1MfcHtmlTagAttr *dst, Dz1MfcHtmlTagAttr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlTagAttr *Dz1MfcHtmlTagAttr_clone(Dz1MfcHtmlTagAttr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTagAttr_purge(Dz1MfcHtmlTagAttr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTagAttr_del(Dz1MfcHtmlTagAttr *p);
static __inline__ void Dz1MfcHtmlTagAttr_delAndSetNull(void *ptr)
{
	Dz1MfcHtmlTagAttr **p = (Dz1MfcHtmlTagAttr **)ptr;
	if (p) { Dz1MfcHtmlTagAttr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTagAttr_dump(Dz1MfcHtmlTagAttr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcHtmlTagAttr_cmp(Dz1MfcHtmlTagAttr *a, Dz1MfcHtmlTagAttr *b); 
// Dz1MfcHtmlTagAttr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlTagAttrList
typedef struct Dz1MfcHtmlTagAttrList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcHtmlTagAttrList *p);
	Dz1Error (*travel)(struct Dz1MfcHtmlTagAttrList *p, Dz1Error (*func)(void *ptr, Dz1MfcHtmlTagAttr *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcHtmlTagAttrList *p, Dz1Error (*func)(void *ptr, Dz1MfcHtmlTagAttr *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcHtmlTagAttrList *p, Dz1Error (*func)(void *ptr, Dz1MfcHtmlTagAttr *entry), void *ptr);
	Dz1MfcHtmlTagAttr **(*get_array)(struct Dz1MfcHtmlTagAttrList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcHtmlTagAttrList *p, Dz1MfcHtmlTagAttr *data);
	bool_t (*remove)(struct Dz1MfcHtmlTagAttrList *p, Dz1MfcHtmlTagAttr *key);
	Dz1MfcHtmlTagAttr *(*extract)(struct Dz1MfcHtmlTagAttrList *p, Dz1MfcHtmlTagAttr *key);
	Dz1MfcHtmlTagAttr *(*find)(struct Dz1MfcHtmlTagAttrList *p, Dz1MfcHtmlTagAttr *key);
	int (*cmp)(Dz1MfcHtmlTagAttr *a, Dz1MfcHtmlTagAttr *b);
} Dz1MfcHtmlTagAttrList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlTagAttrList *Dz1MfcHtmlTagAttrList_new(Dz1Error *err);
static __inline__ Dz1MfcHtmlTagAttrList *Dz1MfcHtmlTagAttrList_gen(Dz1Error *err) { return Dz1MfcHtmlTagAttrList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlTagAttrList *Dz1MfcHtmlTagAttrList_clone(Dz1MfcHtmlTagAttrList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTagAttrList_purge(Dz1MfcHtmlTagAttrList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTagAttrList_del(Dz1MfcHtmlTagAttrList *p);
static __inline__ void Dz1MfcHtmlTagAttrList_delAndSetNull(void *ptr)
{
	Dz1MfcHtmlTagAttrList **p = (Dz1MfcHtmlTagAttrList **)ptr;
	if (p != NULL) { Dz1MfcHtmlTagAttrList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTagAttrList_dump(Dz1MfcHtmlTagAttrList *p, int tab);

// Dz1MfcHtmlTagAttrList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcHtmlTag
typedef struct Dz1MfcHtmlTag
{
	Dz1Str						 tag_name;
	Dz1MfcHtmlTagAttrList		*attr;
} Dz1MfcHtmlTag;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlTag *Dz1MfcHtmlTag_new(Dz1Str tag_name, Dz1Error *err);
static __inline__ Dz1MfcHtmlTag *Dz1MfcHtmlTag_gen(Dz1Error *err) { return Dz1MfcHtmlTag_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcHtmlTag_copy(Dz1MfcHtmlTag *dst, Dz1MfcHtmlTag *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcHtmlTag *Dz1MfcHtmlTag_clone(Dz1MfcHtmlTag *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTag_purge(Dz1MfcHtmlTag *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTag_del(Dz1MfcHtmlTag *p);
static __inline__ void Dz1MfcHtmlTag_delAndSetNull(void *ptr)
{
	Dz1MfcHtmlTag **p = (Dz1MfcHtmlTag **)ptr;
	if (p) { Dz1MfcHtmlTag_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcHtmlTag_dump(Dz1MfcHtmlTag *p, int tab);
// Dz1MfcHtmlTag
////////////////////////////////////////////////////////////////////////////////

#endif
