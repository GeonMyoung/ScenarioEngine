#ifndef _DZ1_TDC_DZ1_ASN1_TYPES_DEF_H_
#define _DZ1_TDC_DZ1_ASN1_TYPES_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_io_stream_support.h"
#include "dz1_asn1_support.h"
#include "dz1_asn1_codec_stream.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescr
struct Dz1Asn1TypeDescr;
// Dz1Asn1TypeDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TagClass
typedef enum Dz1Asn1TagClass
{
	Dz1Asn1TagClass_universal,
	Dz1Asn1TagClass_application,
	Dz1Asn1TagClass_context_specific,
	Dz1Asn1TagClass_privated,
	Dz1Asn1TagClass_max
} Dz1Asn1TagClass;

DZ1_CPPLINK str_t Dz1Asn1TagClassStrA(Dz1Asn1TagClass v);
DZ1_CPPLINK Dz1Asn1TagClass Dz1Asn1TagClassFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1TagClassStrW(Dz1Asn1TagClass v);
DZ1_CPPLINK Dz1Asn1TagClass Dz1Asn1TagClassFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1TagClassStr Dz1Asn1TagClassStrW
#define Dz1Asn1TagClassFromStr Dz1Asn1TagClassFromStrW
#else // UNICODE
#define Dz1Asn1TagClassStr Dz1Asn1TagClassStrA
#define Dz1Asn1TagClassFromStr Dz1Asn1TagClassFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1TagClassStr Dz1Asn1TagClassStrA
#define Dz1Asn1TagClassFromStr Dz1Asn1TagClassFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1TagClass *Dz1Asn1TagClass_new(Dz1Asn1TagClass *src, Dz1Error *err);
static __inline__ Dz1Asn1TagClass *Dz1Asn1TagClass_gen(Dz1Error *err) { Dz1Asn1TagClass v = Dz1Asn1TagClass_max; return Dz1Asn1TagClass_new(&v, err); }
static __inline__ void Dz1Asn1TagClass_del(Dz1Asn1TagClass *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1TagClass_delAndSetNull(void *ptr)
{
	Dz1Asn1TagClass **p = (Dz1Asn1TagClass **)ptr;
	if (p != NULL) { Dz1Asn1TagClass_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagClassA_dump(Dz1Asn1TagClass *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagClassA_fdump(FILE *fp, Dz1Asn1TagClass *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagClassW_dump(Dz1Asn1TagClass *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagClassW_fdump(FILE *fp, Dz1Asn1TagClass *v, int tab);
#ifdef UNICODE
#define Dz1Asn1TagClass_dump Dz1Asn1TagClassW_dump
#define Dz1Asn1TagClass_fdump Dz1Asn1TagClassW_fdump
#else //  UNICODE
#define Dz1Asn1TagClass_dump Dz1Asn1TagClassA_dump
#define Dz1Asn1TagClass_fdump Dz1Asn1TagClassA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1TagClassX_dump(Dz1Asn1TagClass *p, int tab) { DZ1_DUMP(Dz1Asn1TagClass, p, tab); }
static __inline__ void Dz1Asn1TagClassX_fdump(FILE *fp, Dz1Asn1TagClass *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1TagClass, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1TagClass_dump Dz1Asn1TagClassA_dump
#define Dz1Asn1TagClassX_dump Dz1Asn1TagClassA_dump
#define Dz1Asn1TagClass_fdump Dz1Asn1TagClassA_fdump
#define Dz1Asn1TagClassX_fdump Dz1Asn1TagClassA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1TagClass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TagFlag
typedef enum Dz1Asn1TagFlag
{
	Dz1Asn1TagFlag_variable = -1,
	Dz1Asn1TagFlag_primitive,
	Dz1Asn1TagFlag_construct,
	Dz1Asn1TagFlag_max
} Dz1Asn1TagFlag;

DZ1_CPPLINK str_t Dz1Asn1TagFlagStrA(Dz1Asn1TagFlag v);
DZ1_CPPLINK Dz1Asn1TagFlag Dz1Asn1TagFlagFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1TagFlagStrW(Dz1Asn1TagFlag v);
DZ1_CPPLINK Dz1Asn1TagFlag Dz1Asn1TagFlagFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1TagFlagStr Dz1Asn1TagFlagStrW
#define Dz1Asn1TagFlagFromStr Dz1Asn1TagFlagFromStrW
#else // UNICODE
#define Dz1Asn1TagFlagStr Dz1Asn1TagFlagStrA
#define Dz1Asn1TagFlagFromStr Dz1Asn1TagFlagFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1TagFlagStr Dz1Asn1TagFlagStrA
#define Dz1Asn1TagFlagFromStr Dz1Asn1TagFlagFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1TagFlag *Dz1Asn1TagFlag_new(Dz1Asn1TagFlag *src, Dz1Error *err);
static __inline__ Dz1Asn1TagFlag *Dz1Asn1TagFlag_gen(Dz1Error *err) { Dz1Asn1TagFlag v = Dz1Asn1TagFlag_max; return Dz1Asn1TagFlag_new(&v, err); }
static __inline__ void Dz1Asn1TagFlag_del(Dz1Asn1TagFlag *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1TagFlag_delAndSetNull(void *ptr)
{
	Dz1Asn1TagFlag **p = (Dz1Asn1TagFlag **)ptr;
	if (p != NULL) { Dz1Asn1TagFlag_del(*p); *p = NULL; }
}
// Dz1Asn1TagFlag
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Tag
typedef struct Dz1Asn1Tag
{
	Dz1Asn1TagClass		cls;
	Dz1Asn1TagFlag		flag;
	u64_t				numb;
} Dz1Asn1Tag;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Tag *Dz1Asn1Tag_new(Dz1Asn1TagClass cls, 
												   Dz1Asn1TagFlag flag, 
												   u64_t numb, Dz1Error *err);
static __inline__ Dz1Asn1Tag *Dz1Asn1Tag_gen(Dz1Error *err) { return Dz1Asn1Tag_new(Dz1Asn1TagClass_max, Dz1Asn1TagFlag_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Asn1Tag_copy(Dz1Asn1Tag *dst, Dz1Asn1Tag *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1Tag *Dz1Asn1Tag_clone(Dz1Asn1Tag *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1Tag_purge(Dz1Asn1Tag *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1Tag_del(Dz1Asn1Tag *p);
static __inline__ void Dz1Asn1Tag_delAndSetNull(void *ptr)
{
	Dz1Asn1Tag **p = (Dz1Asn1Tag **)ptr;
	if (p) { Dz1Asn1Tag_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagA_dump(Dz1Asn1Tag *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagA_fdump(FILE *fp, Dz1Asn1Tag *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagW_dump(Dz1Asn1Tag *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagW_fdump(FILE *fp, Dz1Asn1Tag *p, int tab);
#ifdef UNICODE
#define Dz1Asn1Tag_dump Dz1Asn1TagW_dump
#define Dz1Asn1Tag_fdump Dz1Asn1TagW_fdump
#else //  UNICODE
#define Dz1Asn1Tag_dump Dz1Asn1TagA_dump
#define Dz1Asn1Tag_fdump Dz1Asn1TagA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1TagX_dump(Dz1Asn1Tag *p, int tab) { DZ1_DUMP(Dz1Asn1Tag, p, tab); }
static __inline__ void Dz1Asn1TagX_fdump(FILE *fp, Dz1Asn1Tag *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1Tag, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1Tag_dump Dz1Asn1TagA_dump
#define Dz1Asn1TagX_dump Dz1Asn1TagA_dump
#define Dz1Asn1Tag_fdump Dz1Asn1TagA_fdump
#define Dz1Asn1TagX_fdump Dz1Asn1TagA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1Asn1Tag_cmp(Dz1Asn1Tag *a, Dz1Asn1Tag *b); 
// Dz1Asn1Tag
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TagOpt
typedef enum Dz1Asn1TagOpt
{
	Dz1Asn1TagOpt_implicit,
	Dz1Asn1TagOpt_explicit,
	Dz1Asn1TagOpt_max
} Dz1Asn1TagOpt;

DZ1_CPPLINK str_t Dz1Asn1TagOptStrA(Dz1Asn1TagOpt v);
DZ1_CPPLINK Dz1Asn1TagOpt Dz1Asn1TagOptFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1TagOptStrW(Dz1Asn1TagOpt v);
DZ1_CPPLINK Dz1Asn1TagOpt Dz1Asn1TagOptFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1TagOptStr Dz1Asn1TagOptStrW
#define Dz1Asn1TagOptFromStr Dz1Asn1TagOptFromStrW
#else // UNICODE
#define Dz1Asn1TagOptStr Dz1Asn1TagOptStrA
#define Dz1Asn1TagOptFromStr Dz1Asn1TagOptFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1TagOptStr Dz1Asn1TagOptStrA
#define Dz1Asn1TagOptFromStr Dz1Asn1TagOptFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1TagOpt *Dz1Asn1TagOpt_new(Dz1Asn1TagOpt *src, Dz1Error *err);
static __inline__ Dz1Asn1TagOpt *Dz1Asn1TagOpt_gen(Dz1Error *err) { Dz1Asn1TagOpt v = Dz1Asn1TagOpt_max; return Dz1Asn1TagOpt_new(&v, err); }
static __inline__ void Dz1Asn1TagOpt_del(Dz1Asn1TagOpt *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1TagOpt_delAndSetNull(void *ptr)
{
	Dz1Asn1TagOpt **p = (Dz1Asn1TagOpt **)ptr;
	if (p != NULL) { Dz1Asn1TagOpt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagOptA_dump(Dz1Asn1TagOpt *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagOptA_fdump(FILE *fp, Dz1Asn1TagOpt *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagOptW_dump(Dz1Asn1TagOpt *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1TagOptW_fdump(FILE *fp, Dz1Asn1TagOpt *v, int tab);
#ifdef UNICODE
#define Dz1Asn1TagOpt_dump Dz1Asn1TagOptW_dump
#define Dz1Asn1TagOpt_fdump Dz1Asn1TagOptW_fdump
#else //  UNICODE
#define Dz1Asn1TagOpt_dump Dz1Asn1TagOptA_dump
#define Dz1Asn1TagOpt_fdump Dz1Asn1TagOptA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1TagOptX_dump(Dz1Asn1TagOpt *p, int tab) { DZ1_DUMP(Dz1Asn1TagOpt, p, tab); }
static __inline__ void Dz1Asn1TagOptX_fdump(FILE *fp, Dz1Asn1TagOpt *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1TagOpt, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1TagOpt_dump Dz1Asn1TagOptA_dump
#define Dz1Asn1TagOptX_dump Dz1Asn1TagOptA_dump
#define Dz1Asn1TagOpt_fdump Dz1Asn1TagOptA_fdump
#define Dz1Asn1TagOptX_fdump Dz1Asn1TagOptA_fdump
#endif // UNIX_SYSTEM
// Dz1Asn1TagOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenTypeEntry
struct Dz1Asn1WipOpenType;

typedef struct Dz1Asn1WipOpenTypeEntry
{
	u32_t							 order;
	struct Dz1Asn1WipOpenType		*data;
} Dz1Asn1WipOpenTypeEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOpenTypeEntry *Dz1Asn1WipOpenTypeEntry_new(u32_t order, 
																			 struct Dz1Asn1WipOpenType *data, Dz1Error *err);
static __inline__ Dz1Asn1WipOpenTypeEntry *Dz1Asn1WipOpenTypeEntry_gen(Dz1Error *err) { return Dz1Asn1WipOpenTypeEntry_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeEntry_purge(Dz1Asn1WipOpenTypeEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeEntry_del(Dz1Asn1WipOpenTypeEntry *p);
static __inline__ void Dz1Asn1WipOpenTypeEntry_delAndSetNull(void *ptr)
{
	Dz1Asn1WipOpenTypeEntry **p = (Dz1Asn1WipOpenTypeEntry **)ptr;
	if (p) { Dz1Asn1WipOpenTypeEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeEntryA_dump(Dz1Asn1WipOpenTypeEntry *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeEntryW_dump(Dz1Asn1WipOpenTypeEntry *p, int tab);
#ifdef UNICODE
#define Dz1Asn1WipOpenTypeEntry_dump Dz1Asn1WipOpenTypeEntryW_dump
#else //  UNICODE
#define Dz1Asn1WipOpenTypeEntry_dump Dz1Asn1WipOpenTypeEntryA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipOpenTypeEntryX_dump(Dz1Asn1WipOpenTypeEntry *p, int tab) { DZ1_DUMP(Dz1Asn1WipOpenTypeEntry, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipOpenTypeEntry_dump Dz1Asn1WipOpenTypeEntryA_dump
#define Dz1Asn1WipOpenTypeEntryX_dump Dz1Asn1WipOpenTypeEntryA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1Asn1WipOpenTypeEntry_cmp(Dz1Asn1WipOpenTypeEntry *a, Dz1Asn1WipOpenTypeEntry *b); 
// Dz1Asn1WipOpenTypeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenTypeList
typedef struct Dz1Asn1WipOpenTypeList
{
	void *storage;
	unsigned int (*count)(struct Dz1Asn1WipOpenTypeList *p);
	Dz1Error (*travel)(struct Dz1Asn1WipOpenTypeList *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOpenTypeEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1Asn1WipOpenTypeList *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOpenTypeEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1Asn1WipOpenTypeList *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOpenTypeEntry *entry), void *ptr);
	Dz1Asn1WipOpenTypeEntry **(*get_array)(struct Dz1Asn1WipOpenTypeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1Asn1WipOpenTypeList *p, Dz1Asn1WipOpenTypeEntry *data);
	bool_t (*remove)(struct Dz1Asn1WipOpenTypeList *p, Dz1Asn1WipOpenTypeEntry *key);
	Dz1Asn1WipOpenTypeEntry *(*extract)(struct Dz1Asn1WipOpenTypeList *p, Dz1Asn1WipOpenTypeEntry *key);
	Dz1Asn1WipOpenTypeEntry *(*find)(struct Dz1Asn1WipOpenTypeList *p, Dz1Asn1WipOpenTypeEntry *key);
	int (*cmp)(Dz1Asn1WipOpenTypeEntry *a, Dz1Asn1WipOpenTypeEntry *b);
} Dz1Asn1WipOpenTypeList;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOpenTypeList *Dz1Asn1WipOpenTypeList_new(Dz1Error *err);
static __inline__ Dz1Asn1WipOpenTypeList *Dz1Asn1WipOpenTypeList_gen(Dz1Error *err) { return Dz1Asn1WipOpenTypeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeList_purge(Dz1Asn1WipOpenTypeList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeList_del(Dz1Asn1WipOpenTypeList *p);
static __inline__ void Dz1Asn1WipOpenTypeList_delAndSetNull(void *ptr)
{
	Dz1Asn1WipOpenTypeList **p = (Dz1Asn1WipOpenTypeList **)ptr;
	if (p != NULL) { Dz1Asn1WipOpenTypeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeListA_dump(Dz1Asn1WipOpenTypeList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeListW_dump(Dz1Asn1WipOpenTypeList *p, int tab);
#ifdef UNICODE
#define Dz1Asn1WipOpenTypeList_dump Dz1Asn1WipOpenTypeListW_dump
#else //  UNICODE
#define Dz1Asn1WipOpenTypeList_dump Dz1Asn1WipOpenTypeListA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipOpenTypeListX_dump(Dz1Asn1WipOpenTypeList *p, int tab) { DZ1_DUMP(Dz1Asn1WipOpenTypeList, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipOpenTypeList_dump Dz1Asn1WipOpenTypeListA_dump
#define Dz1Asn1WipOpenTypeListX_dump Dz1Asn1WipOpenTypeListA_dump
#endif // UNIX_SYSTEM

// Dz1Asn1WipOpenTypeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenDataPresent
typedef enum Dz1Asn1WipOpenDataPresent
{
	Dz1Asn1WipOpenDataPresent_primitive,
	Dz1Asn1WipOpenDataPresent_construct,
	Dz1Asn1WipOpenDataPresent_max
} Dz1Asn1WipOpenDataPresent;

DZ1_CPPLINK str_t Dz1Asn1WipOpenDataPresentStrA(Dz1Asn1WipOpenDataPresent v);
DZ1_CPPLINK Dz1Asn1WipOpenDataPresent Dz1Asn1WipOpenDataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1WipOpenDataPresentStrW(Dz1Asn1WipOpenDataPresent v);
DZ1_CPPLINK Dz1Asn1WipOpenDataPresent Dz1Asn1WipOpenDataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1WipOpenDataPresentStr Dz1Asn1WipOpenDataPresentStrW
#define Dz1Asn1WipOpenDataPresentFromStr Dz1Asn1WipOpenDataPresentFromStrW
#else // UNICODE
#define Dz1Asn1WipOpenDataPresentStr Dz1Asn1WipOpenDataPresentStrA
#define Dz1Asn1WipOpenDataPresentFromStr Dz1Asn1WipOpenDataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1WipOpenDataPresentStr Dz1Asn1WipOpenDataPresentStrA
#define Dz1Asn1WipOpenDataPresentFromStr Dz1Asn1WipOpenDataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOpenDataPresent *Dz1Asn1WipOpenDataPresent_new(Dz1Asn1WipOpenDataPresent *src, Dz1Error *err);
static __inline__ Dz1Asn1WipOpenDataPresent *Dz1Asn1WipOpenDataPresent_gen(Dz1Error *err) { Dz1Asn1WipOpenDataPresent v = Dz1Asn1WipOpenDataPresent_max; return Dz1Asn1WipOpenDataPresent_new(&v, err); }
static __inline__ void Dz1Asn1WipOpenDataPresent_del(Dz1Asn1WipOpenDataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1WipOpenDataPresent_delAndSetNull(void *ptr)
{
	Dz1Asn1WipOpenDataPresent **p = (Dz1Asn1WipOpenDataPresent **)ptr;
	if (p != NULL) { Dz1Asn1WipOpenDataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenDataPresentA_dump(Dz1Asn1WipOpenDataPresent *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenDataPresentW_dump(Dz1Asn1WipOpenDataPresent *v, int tab);
#ifdef UNICODE
#define Dz1Asn1WipOpenDataPresent_dump Dz1Asn1WipOpenDataPresentW_dump
#else //  UNICODE
#define Dz1Asn1WipOpenDataPresent_dump Dz1Asn1WipOpenDataPresentA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipOpenDataPresentX_dump(Dz1Asn1WipOpenDataPresent *p, int tab) { DZ1_DUMP(Dz1Asn1WipOpenDataPresent, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipOpenDataPresent_dump Dz1Asn1WipOpenDataPresentA_dump
#define Dz1Asn1WipOpenDataPresentX_dump Dz1Asn1WipOpenDataPresentA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1WipOpenDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenData
typedef struct Dz1Asn1WipOpenData
{
	Dz1Asn1WipOpenDataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1ElasticBuf				*primitive;
		Dz1Asn1WipOpenTypeList		*construct;
	} x;
} Dz1Asn1WipOpenData;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOpenData *Dz1Asn1WipOpenData_new(Dz1Asn1WipOpenDataPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1Asn1WipOpenData *Dz1Asn1WipOpenData_gen(Dz1Error *err) { return Dz1Asn1WipOpenData_new(Dz1Asn1WipOpenDataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenData_purge(Dz1Asn1WipOpenData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenData_del(Dz1Asn1WipOpenData *p);
static __inline__ void Dz1Asn1WipOpenData_delAndSetNull(void *ptr)
{
	Dz1Asn1WipOpenData **p = (Dz1Asn1WipOpenData **)ptr;
	if (p != NULL) { Dz1Asn1WipOpenData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenDataA_dump(Dz1Asn1WipOpenData *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenDataW_dump(Dz1Asn1WipOpenData *p, int tab);
#ifdef UNICODE
#define Dz1Asn1WipOpenData_dump Dz1Asn1WipOpenDataW_dump
#else //  UNICODE
#define Dz1Asn1WipOpenData_dump Dz1Asn1WipOpenDataA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipOpenDataX_dump(Dz1Asn1WipOpenData *p, int tab) { DZ1_DUMP(Dz1Asn1WipOpenData, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipOpenData_dump Dz1Asn1WipOpenDataA_dump
#define Dz1Asn1WipOpenDataX_dump Dz1Asn1WipOpenDataA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1WipOpenData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenType
typedef struct Dz1Asn1WipOpenType
{
	Dz1Asn1TagClass			 cls;
	u64_t					 number;
	u64_t					 len;
	Dz1Asn1WipOpenData		*contents;
} Dz1Asn1WipOpenType;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOpenType *Dz1Asn1WipOpenType_new(Dz1Asn1TagClass cls, 
																   u64_t number, 
																   u64_t len, 
																   Dz1Asn1WipOpenData *contents, Dz1Error *err);
static __inline__ Dz1Asn1WipOpenType *Dz1Asn1WipOpenType_gen(Dz1Error *err) { return Dz1Asn1WipOpenType_new(Dz1Asn1TagClass_max, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenType_purge(Dz1Asn1WipOpenType *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenType_del(Dz1Asn1WipOpenType *p);
static __inline__ void Dz1Asn1WipOpenType_delAndSetNull(void *ptr)
{
	Dz1Asn1WipOpenType **p = (Dz1Asn1WipOpenType **)ptr;
	if (p) { Dz1Asn1WipOpenType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeA_dump(Dz1Asn1WipOpenType *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOpenTypeW_dump(Dz1Asn1WipOpenType *p, int tab);
#ifdef UNICODE
#define Dz1Asn1WipOpenType_dump Dz1Asn1WipOpenTypeW_dump
#else //  UNICODE
#define Dz1Asn1WipOpenType_dump Dz1Asn1WipOpenTypeA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipOpenTypeX_dump(Dz1Asn1WipOpenType *p, int tab) { DZ1_DUMP(Dz1Asn1WipOpenType, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipOpenType_dump Dz1Asn1WipOpenTypeA_dump
#define Dz1Asn1WipOpenTypeX_dump Dz1Asn1WipOpenTypeA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1WipOpenType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipBitString
typedef struct Dz1Asn1WipBitString
{
	Dz1ElasticBuf		*elb;
	u32_t				 trim_bits;
} Dz1Asn1WipBitString;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipBitString *Dz1Asn1WipBitString_new(Dz1ElasticBuf *elb, 
																	 u32_t trim_bits, Dz1Error *err);
static __inline__ Dz1Asn1WipBitString *Dz1Asn1WipBitString_gen(Dz1Error *err) { return Dz1Asn1WipBitString_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipBitString_purge(Dz1Asn1WipBitString *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipBitString_del(Dz1Asn1WipBitString *p);
static __inline__ void Dz1Asn1WipBitString_delAndSetNull(void *ptr)
{
	Dz1Asn1WipBitString **p = (Dz1Asn1WipBitString **)ptr;
	if (p) { Dz1Asn1WipBitString_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipBitStringA_dump(Dz1Asn1WipBitString *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipBitStringW_dump(Dz1Asn1WipBitString *p, int tab);
#ifdef UNICODE
#define Dz1Asn1WipBitString_dump Dz1Asn1WipBitStringW_dump
#else //  UNICODE
#define Dz1Asn1WipBitString_dump Dz1Asn1WipBitStringA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipBitStringX_dump(Dz1Asn1WipBitString *p, int tab) { DZ1_DUMP(Dz1Asn1WipBitString, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipBitString_dump Dz1Asn1WipBitStringA_dump
#define Dz1Asn1WipBitStringX_dump Dz1Asn1WipBitStringA_dump
#endif // UNIX_SYSTEM
// Dz1Asn1WipBitString
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOidArc
typedef struct Dz1Asn1WipOidArc
{
	u32_t		ord;
	u32_t		num;
} Dz1Asn1WipOidArc;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOidArc *Dz1Asn1WipOidArc_new(u32_t ord, 
															   u32_t num, Dz1Error *err);
static __inline__ Dz1Asn1WipOidArc *Dz1Asn1WipOidArc_gen(Dz1Error *err) { return Dz1Asn1WipOidArc_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Asn1WipOidArc_copy(Dz1Asn1WipOidArc *dst, Dz1Asn1WipOidArc *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOidArc *Dz1Asn1WipOidArc_clone(Dz1Asn1WipOidArc *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOidArc_purge(Dz1Asn1WipOidArc *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOidArc_del(Dz1Asn1WipOidArc *p);
static __inline__ void Dz1Asn1WipOidArc_delAndSetNull(void *ptr)
{
	Dz1Asn1WipOidArc **p = (Dz1Asn1WipOidArc **)ptr;
	if (p) { Dz1Asn1WipOidArc_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOidArcA_dump(Dz1Asn1WipOidArc *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOidArcW_dump(Dz1Asn1WipOidArc *p, int tab);
#ifdef UNICODE
#define Dz1Asn1WipOidArc_dump Dz1Asn1WipOidArcW_dump
#else //  UNICODE
#define Dz1Asn1WipOidArc_dump Dz1Asn1WipOidArcA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipOidArcX_dump(Dz1Asn1WipOidArc *p, int tab) { DZ1_DUMP(Dz1Asn1WipOidArc, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipOidArc_dump Dz1Asn1WipOidArcA_dump
#define Dz1Asn1WipOidArcX_dump Dz1Asn1WipOidArcA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1Asn1WipOidArc_cmp(Dz1Asn1WipOidArc *a, Dz1Asn1WipOidArc *b); 
// Dz1Asn1WipOidArc
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOid
typedef struct Dz1Asn1WipOid
{
	void *storage;
	unsigned int (*count)(struct Dz1Asn1WipOid *p);
	Dz1Error (*travel)(struct Dz1Asn1WipOid *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOidArc *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1Asn1WipOid *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOidArc *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1Asn1WipOid *p, Dz1Error (*func)(void *ptr, Dz1Asn1WipOidArc *entry), void *ptr);
	Dz1Asn1WipOidArc **(*get_array)(struct Dz1Asn1WipOid *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1Asn1WipOid *p, Dz1Asn1WipOidArc *data);
	bool_t (*remove)(struct Dz1Asn1WipOid *p, Dz1Asn1WipOidArc *key);
	Dz1Asn1WipOidArc *(*extract)(struct Dz1Asn1WipOid *p, Dz1Asn1WipOidArc *key);
	Dz1Asn1WipOidArc *(*find)(struct Dz1Asn1WipOid *p, Dz1Asn1WipOidArc *key);
	Dz1Asn1WipOidArc *(*getHead)(struct Dz1Asn1WipOid *p);
	Dz1Asn1WipOidArc *(*getTail)(struct Dz1Asn1WipOid *p);
	int (*cmp)(Dz1Asn1WipOidArc *a, Dz1Asn1WipOidArc *b);
} Dz1Asn1WipOid;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOid *Dz1Asn1WipOid_new(Dz1Error *err);
static __inline__ Dz1Asn1WipOid *Dz1Asn1WipOid_gen(Dz1Error *err) { return Dz1Asn1WipOid_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipOid *Dz1Asn1WipOid_clone(Dz1Asn1WipOid *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOid_purge(Dz1Asn1WipOid *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOid_del(Dz1Asn1WipOid *p);
static __inline__ void Dz1Asn1WipOid_delAndSetNull(void *ptr)
{
	Dz1Asn1WipOid **p = (Dz1Asn1WipOid **)ptr;
	if (p != NULL) { Dz1Asn1WipOid_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOidA_dump(Dz1Asn1WipOid *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipOidW_dump(Dz1Asn1WipOid *p, int tab);
#ifdef UNICODE
#define Dz1Asn1WipOid_dump Dz1Asn1WipOidW_dump
#else //  UNICODE
#define Dz1Asn1WipOid_dump Dz1Asn1WipOidA_dump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipOidX_dump(Dz1Asn1WipOid *p, int tab) { DZ1_DUMP(Dz1Asn1WipOid, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipOid_dump Dz1Asn1WipOidA_dump
#define Dz1Asn1WipOidX_dump Dz1Asn1WipOidA_dump
#endif // UNIX_SYSTEM

// Dz1Asn1WipOid
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipExtOrInstPresent
typedef enum Dz1Asn1WipExtOrInstPresent
{
	Dz1Asn1WipExtOrInstPresent_external,
	Dz1Asn1WipExtOrInstPresent_instance_of,
	Dz1Asn1WipExtOrInstPresent_max
} Dz1Asn1WipExtOrInstPresent;

DZ1_CPPLINK str_t Dz1Asn1WipExtOrInstPresentStrA(Dz1Asn1WipExtOrInstPresent v);
DZ1_CPPLINK Dz1Asn1WipExtOrInstPresent Dz1Asn1WipExtOrInstPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1WipExtOrInstPresentStrW(Dz1Asn1WipExtOrInstPresent v);
DZ1_CPPLINK Dz1Asn1WipExtOrInstPresent Dz1Asn1WipExtOrInstPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1WipExtOrInstPresentStr Dz1Asn1WipExtOrInstPresentStrW
#define Dz1Asn1WipExtOrInstPresentFromStr Dz1Asn1WipExtOrInstPresentFromStrW
#else // UNICODE
#define Dz1Asn1WipExtOrInstPresentStr Dz1Asn1WipExtOrInstPresentStrA
#define Dz1Asn1WipExtOrInstPresentFromStr Dz1Asn1WipExtOrInstPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1WipExtOrInstPresentStr Dz1Asn1WipExtOrInstPresentStrA
#define Dz1Asn1WipExtOrInstPresentFromStr Dz1Asn1WipExtOrInstPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipExtOrInstPresent *Dz1Asn1WipExtOrInstPresent_new(Dz1Asn1WipExtOrInstPresent *src, Dz1Error *err);
static __inline__ Dz1Asn1WipExtOrInstPresent *Dz1Asn1WipExtOrInstPresent_gen(Dz1Error *err) { Dz1Asn1WipExtOrInstPresent v = Dz1Asn1WipExtOrInstPresent_max; return Dz1Asn1WipExtOrInstPresent_new(&v, err); }
#define Dz1Asn1WipExtOrInstPresent_clone             Dz1Asn1WipExtOrInstPresent_new
static __inline__ void Dz1Asn1WipExtOrInstPresent_del(Dz1Asn1WipExtOrInstPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1WipExtOrInstPresent_delAndSetNull(void *ptr)
{
	Dz1Asn1WipExtOrInstPresent **p = (Dz1Asn1WipExtOrInstPresent **)ptr;
	if (p != NULL) { Dz1Asn1WipExtOrInstPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInstPresentA_dump(Dz1Asn1WipExtOrInstPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInstPresentA_fdump(FILE *fp, Dz1Asn1WipExtOrInstPresent *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInstPresentW_dump(Dz1Asn1WipExtOrInstPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInstPresentW_fdump(FILE *fp, Dz1Asn1WipExtOrInstPresent *v, int tab);
#ifdef UNICODE
#define Dz1Asn1WipExtOrInstPresent_dump Dz1Asn1WipExtOrInstPresentW_dump
#define Dz1Asn1WipExtOrInstPresent_fdump Dz1Asn1WipExtOrInstPresentW_fdump
#else //  UNICODE
#define Dz1Asn1WipExtOrInstPresent_dump Dz1Asn1WipExtOrInstPresentA_dump
#define Dz1Asn1WipExtOrInstPresent_fdump Dz1Asn1WipExtOrInstPresentA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipExtOrInstPresentX_dump(Dz1Asn1WipExtOrInstPresent *p, int tab) { DZ1_DUMP(Dz1Asn1WipExtOrInstPresent, p, tab); }
static __inline__ void Dz1Asn1WipExtOrInstPresentX_fdump(FILE *fp, Dz1Asn1WipExtOrInstPresent *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1WipExtOrInstPresent, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipExtOrInstPresent_dump Dz1Asn1WipExtOrInstPresentA_dump
#define Dz1Asn1WipExtOrInstPresentX_dump Dz1Asn1WipExtOrInstPresentA_dump
#define Dz1Asn1WipExtOrInstPresent_fdump Dz1Asn1WipExtOrInstPresentA_fdump
#define Dz1Asn1WipExtOrInstPresentX_fdump Dz1Asn1WipExtOrInstPresentA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1Asn1WipExtOrInstPresent_cmp(Dz1Asn1WipExtOrInstPresent *a, Dz1Asn1WipExtOrInstPresent *b);
// Dz1Asn1WipExtOrInstPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipExtOrInst
typedef struct Dz1Asn1WipExtOrInst
{
	Dz1Asn1WipExtOrInstPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1External			*external;
		Dz1Asn1InstanceOf		*instance_of;
	} x;
} Dz1Asn1WipExtOrInst;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipExtOrInst *Dz1Asn1WipExtOrInst_new(Dz1Asn1WipExtOrInstPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1Asn1WipExtOrInst *Dz1Asn1WipExtOrInst_gen(Dz1Error *err) { return Dz1Asn1WipExtOrInst_new(Dz1Asn1WipExtOrInstPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1Asn1WipExtOrInst_copy(Dz1Asn1WipExtOrInst *dst, Dz1Asn1WipExtOrInst *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipExtOrInst *Dz1Asn1WipExtOrInst_clone(Dz1Asn1WipExtOrInst *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInst_purge(Dz1Asn1WipExtOrInst *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInst_del(Dz1Asn1WipExtOrInst *p);
static __inline__ void Dz1Asn1WipExtOrInst_delAndSetNull(void *ptr)
{
	Dz1Asn1WipExtOrInst **p = (Dz1Asn1WipExtOrInst **)ptr;
	if (p != NULL) { Dz1Asn1WipExtOrInst_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInstA_dump(Dz1Asn1WipExtOrInst *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInstA_fdump(FILE *fp, Dz1Asn1WipExtOrInst *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInstW_dump(Dz1Asn1WipExtOrInst *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipExtOrInstW_fdump(FILE *fp, Dz1Asn1WipExtOrInst *p, int tab);
#ifdef UNICODE
#define Dz1Asn1WipExtOrInst_dump Dz1Asn1WipExtOrInstW_dump
#define Dz1Asn1WipExtOrInst_fdump Dz1Asn1WipExtOrInstW_fdump
#else //  UNICODE
#define Dz1Asn1WipExtOrInst_dump Dz1Asn1WipExtOrInstA_dump
#define Dz1Asn1WipExtOrInst_fdump Dz1Asn1WipExtOrInstA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1WipExtOrInstX_dump(Dz1Asn1WipExtOrInst *p, int tab) { DZ1_DUMP(Dz1Asn1WipExtOrInst, p, tab); }
static __inline__ void Dz1Asn1WipExtOrInstX_fdump(FILE *fp, Dz1Asn1WipExtOrInst *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1WipExtOrInst, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1WipExtOrInst_dump Dz1Asn1WipExtOrInstA_dump
#define Dz1Asn1WipExtOrInstX_dump Dz1Asn1WipExtOrInstA_dump
#define Dz1Asn1WipExtOrInst_fdump Dz1Asn1WipExtOrInstA_fdump
#define Dz1Asn1WipExtOrInstX_fdump Dz1Asn1WipExtOrInstA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1Asn1WipExtOrInst_cmp(Dz1Asn1WipExtOrInst *a, Dz1Asn1WipExtOrInst *b);
// Dz1Asn1WipExtOrInst
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipReal
typedef struct Dz1Asn1WipReal
{
	Dz1Asn1Real			 value;
	Dz1ElasticBuf		*elb;
} Dz1Asn1WipReal;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipReal *Dz1Asn1WipReal_new(Dz1ElasticBuf *elb, Dz1Error *err);
static __inline__ Dz1Asn1WipReal *Dz1Asn1WipReal_gen(Dz1Error *err) { return Dz1Asn1WipReal_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipReal_purge(Dz1Asn1WipReal *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipReal_del(Dz1Asn1WipReal *p);
static __inline__ void Dz1Asn1WipReal_delAndSetNull(void *ptr)
{
	Dz1Asn1WipReal **p = (Dz1Asn1WipReal **)ptr;
	if (p) { Dz1Asn1WipReal_del(*p); *p = NULL; }
}
// Dz1Asn1WipReal
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipCst
struct Dz1Asn1TypeDescr;

typedef struct Dz1Asn1WipCst
{
	Dz1Asn1Custom				*storage;
	Dz1Asn1WipOpenTypeList		*unknowns;
	struct Dz1Asn1TypeDescr		*indirect;
} Dz1Asn1WipCst;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipCst *Dz1Asn1WipCst_new(Dz1Asn1Custom *storage, 
														 struct Dz1Asn1TypeDescr *indirect, Dz1Error *err);
static __inline__ Dz1Asn1WipCst *Dz1Asn1WipCst_gen(Dz1Error *err) { return Dz1Asn1WipCst_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipCst_purge(Dz1Asn1WipCst *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipCst_del(Dz1Asn1WipCst *p);
static __inline__ void Dz1Asn1WipCst_delAndSetNull(void *ptr)
{
	Dz1Asn1WipCst **p = (Dz1Asn1WipCst **)ptr;
	if (p) { Dz1Asn1WipCst_del(*p); *p = NULL; }
}
// Dz1Asn1WipCst
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipValuePresent
typedef enum Dz1Asn1WipValuePresent
{
	Dz1Asn1WipValuePresent_any = 0,
	Dz1Asn1WipValuePresent_boolean = Dz1Asn1Type_boolean,
	Dz1Asn1WipValuePresent_number = Dz1Asn1Type_integer,
	Dz1Asn1WipValuePresent_bit_str = Dz1Asn1Type_bit_str,
	Dz1Asn1WipValuePresent_octet_str = Dz1Asn1Type_octet_str,
	Dz1Asn1WipValuePresent_nul = Dz1Asn1Type_nul,
	Dz1Asn1WipValuePresent_oid = Dz1Asn1Type_oid,
	Dz1Asn1WipValuePresent_ext_or_inst = Dz1Asn1Type_external,
	Dz1Asn1WipValuePresent_realnum = Dz1Asn1Type_realnum,
	Dz1Asn1WipValuePresent_enumerated = Dz1Asn1Type_enumerated,
	Dz1Asn1WipValuePresent_embPDV = Dz1Asn1Type_embPDV,
	Dz1Asn1WipValuePresent_cst_seq = Dz1Asn1Type_set,
	Dz1Asn1WipValuePresent_cst_set = Dz1Asn1Type_seq,
	Dz1Asn1WipValuePresent_char_str = Dz1Asn1Type_char_str,
	Dz1Asn1WipValuePresent_max
} Dz1Asn1WipValuePresent;

DZ1_CPPLINK str_t Dz1Asn1WipValuePresentStrA(Dz1Asn1WipValuePresent v);
DZ1_CPPLINK Dz1Asn1WipValuePresent Dz1Asn1WipValuePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1Asn1WipValuePresentStrW(Dz1Asn1WipValuePresent v);
DZ1_CPPLINK Dz1Asn1WipValuePresent Dz1Asn1WipValuePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1Asn1WipValuePresentStr Dz1Asn1WipValuePresentStrW
#define Dz1Asn1WipValuePresentFromStr Dz1Asn1WipValuePresentFromStrW
#else // UNICODE
#define Dz1Asn1WipValuePresentStr Dz1Asn1WipValuePresentStrA
#define Dz1Asn1WipValuePresentFromStr Dz1Asn1WipValuePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Asn1WipValuePresentStr Dz1Asn1WipValuePresentStrA
#define Dz1Asn1WipValuePresentFromStr Dz1Asn1WipValuePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipValuePresent *Dz1Asn1WipValuePresent_new(Dz1Asn1WipValuePresent *src, Dz1Error *err);
static __inline__ Dz1Asn1WipValuePresent *Dz1Asn1WipValuePresent_gen(Dz1Error *err) { Dz1Asn1WipValuePresent v = Dz1Asn1WipValuePresent_max; return Dz1Asn1WipValuePresent_new(&v, err); }
static __inline__ void Dz1Asn1WipValuePresent_del(Dz1Asn1WipValuePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1Asn1WipValuePresent_delAndSetNull(void *ptr)
{
	Dz1Asn1WipValuePresent **p = (Dz1Asn1WipValuePresent **)ptr;
	if (p != NULL) { Dz1Asn1WipValuePresent_del(*p); *p = NULL; }
}
// Dz1Asn1WipValuePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipValue
typedef struct Dz1Asn1WipValue
{
	Dz1Asn1WipValuePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1WipOpenType		*any;
		Dz1Asn1Bool				 boolean;
		Dz1Asn1Int				 number;
		Dz1Asn1WipBitString		*bit_str;
		Dz1ElasticBuf			*octet_str;
		Dz1Asn1Null				 nul;
		Dz1Asn1WipOid			*oid;
		Dz1Asn1WipExtOrInst		*ext_or_inst;
		Dz1Asn1WipReal			*realnum;
		Dz1Asn1Enum				 enumerated;
		Dz1Asn1EmbPdv			*embPDV;
		Dz1Asn1WipCst			*cst_seq;
		Dz1Asn1WipCst			*cst_set;
		Dz1Asn1CharStr			*char_str;
	} x;
} Dz1Asn1WipValue;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1WipValue *Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1Asn1WipValue *Dz1Asn1WipValue_gen(Dz1Error *err) { return Dz1Asn1WipValue_new(Dz1Asn1WipValuePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipValue_purge(Dz1Asn1WipValue *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1WipValue_del(Dz1Asn1WipValue *p);
static __inline__ void Dz1Asn1WipValue_delAndSetNull(void *ptr)
{
	Dz1Asn1WipValue **p = (Dz1Asn1WipValue **)ptr;
	if (p != NULL) { Dz1Asn1WipValue_del(*p); *p = NULL; }
}
// Dz1Asn1WipValue
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1GetChildF
typedef void *(*Dz1Asn1GetChildF)(void *struct_ptr, struct Dz1Asn1TypeDescr **opt_ret_type);
// Dz1Asn1GetChildF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ApplyChildF
typedef bool_t (*Dz1Asn1ApplyChildF)(
					Dz1Asn1WipValue *parent_wip, 
					struct Dz1Asn1TypeDescr *type, 
					Dz1Asn1WipValue *data, 
					u32_t opt_order, 
					Dz1Error *errp);
// Dz1Asn1ApplyChildF
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1MetaDataRange
typedef struct Dz1Asn1MetaDataRange
{
	Dz1Asn1Int		low;
	Dz1Asn1Int		high;
} Dz1Asn1MetaDataRange;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1MetaDataRange *Dz1Asn1MetaDataRange_new(Dz1Asn1Int low, 
																	   Dz1Asn1Int high, Dz1Error *err);
static __inline__ Dz1Asn1MetaDataRange *Dz1Asn1MetaDataRange_gen(Dz1Error *err) { return Dz1Asn1MetaDataRange_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRange_purge(Dz1Asn1MetaDataRange *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRange_del(Dz1Asn1MetaDataRange *p);
static __inline__ void Dz1Asn1MetaDataRange_delAndSetNull(void *ptr)
{
	Dz1Asn1MetaDataRange **p = (Dz1Asn1MetaDataRange **)ptr;
	if (p) { Dz1Asn1MetaDataRange_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRangeA_dump(Dz1Asn1MetaDataRange *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRangeA_fdump(FILE *fp, Dz1Asn1MetaDataRange *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRangeW_dump(Dz1Asn1MetaDataRange *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRangeW_fdump(FILE *fp, Dz1Asn1MetaDataRange *p, int tab);
#ifdef UNICODE
#define Dz1Asn1MetaDataRange_dump Dz1Asn1MetaDataRangeW_dump
#define Dz1Asn1MetaDataRange_fdump Dz1Asn1MetaDataRangeW_fdump
#else //  UNICODE
#define Dz1Asn1MetaDataRange_dump Dz1Asn1MetaDataRangeA_dump
#define Dz1Asn1MetaDataRange_fdump Dz1Asn1MetaDataRangeA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1MetaDataRangeX_dump(Dz1Asn1MetaDataRange *p, int tab) { DZ1_DUMP(Dz1Asn1MetaDataRange, p, tab); }
static __inline__ void Dz1Asn1MetaDataRangeX_fdump(FILE *fp, Dz1Asn1MetaDataRange *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1MetaDataRange, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1MetaDataRange_dump Dz1Asn1MetaDataRangeA_dump
#define Dz1Asn1MetaDataRangeX_dump Dz1Asn1MetaDataRangeA_dump
#define Dz1Asn1MetaDataRange_fdump Dz1Asn1MetaDataRangeA_fdump
#define Dz1Asn1MetaDataRangeX_fdump Dz1Asn1MetaDataRangeA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1Asn1MetaDataRange_cmp(Dz1Asn1MetaDataRange *a, Dz1Asn1MetaDataRange *b); 	// User Customized
// Dz1Asn1MetaDataRange
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1MetaDataRealRange
typedef struct Dz1Asn1MetaDataRealRange
{
	Dz1Asn1Real		low;
	Dz1Asn1Real		high;
} Dz1Asn1MetaDataRealRange;

DZ1_CPPLINK DZ1_DLLPORT Dz1Asn1MetaDataRealRange *Dz1Asn1MetaDataRealRange_new(Dz1Asn1Real low, 
																			   Dz1Asn1Real high, Dz1Error *err);
static __inline__ Dz1Asn1MetaDataRealRange *Dz1Asn1MetaDataRealRange_gen(Dz1Error *err) { return Dz1Asn1MetaDataRealRange_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRealRange_purge(Dz1Asn1MetaDataRealRange *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRealRange_del(Dz1Asn1MetaDataRealRange *p);
static __inline__ void Dz1Asn1MetaDataRealRange_delAndSetNull(void *ptr)
{
	Dz1Asn1MetaDataRealRange **p = (Dz1Asn1MetaDataRealRange **)ptr;
	if (p) { Dz1Asn1MetaDataRealRange_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRealRangeA_dump(Dz1Asn1MetaDataRealRange *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRealRangeA_fdump(FILE *fp, Dz1Asn1MetaDataRealRange *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRealRangeW_dump(Dz1Asn1MetaDataRealRange *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Asn1MetaDataRealRangeW_fdump(FILE *fp, Dz1Asn1MetaDataRealRange *p, int tab);
#ifdef UNICODE
#define Dz1Asn1MetaDataRealRange_dump Dz1Asn1MetaDataRealRangeW_dump
#define Dz1Asn1MetaDataRealRange_fdump Dz1Asn1MetaDataRealRangeW_fdump
#else //  UNICODE
#define Dz1Asn1MetaDataRealRange_dump Dz1Asn1MetaDataRealRangeA_dump
#define Dz1Asn1MetaDataRealRange_fdump Dz1Asn1MetaDataRealRangeA_fdump
#endif //  UNICODE
static __inline__ void Dz1Asn1MetaDataRealRangeX_dump(Dz1Asn1MetaDataRealRange *p, int tab) { DZ1_DUMP(Dz1Asn1MetaDataRealRange, p, tab); }
static __inline__ void Dz1Asn1MetaDataRealRangeX_fdump(FILE *fp, Dz1Asn1MetaDataRealRange *p, int tab) { DZ1_FDUMP(fp, Dz1Asn1MetaDataRealRange, p, tab); }
#else // UNIX_SYSTEM
#define Dz1Asn1MetaDataRealRange_dump Dz1Asn1MetaDataRealRangeA_dump
#define Dz1Asn1MetaDataRealRangeX_dump Dz1Asn1MetaDataRealRangeA_dump
#define Dz1Asn1MetaDataRealRange_fdump Dz1Asn1MetaDataRealRangeA_fdump
#define Dz1Asn1MetaDataRealRangeX_fdump Dz1Asn1MetaDataRealRangeA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1Asn1MetaDataRealRange_cmp(Dz1Asn1MetaDataRealRange *a, Dz1Asn1MetaDataRealRange *b); 	// User Customized
// Dz1Asn1MetaDataRealRange
////////////////////////////////////////////////////////////////////////////////

#endif
