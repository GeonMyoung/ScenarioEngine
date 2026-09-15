#ifndef _DZ1_TDC_DZ1_TDC_INFO_STRUCT_X_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_STRUCT_X_TEST_H_

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
// MyXDataEntry
typedef struct MyXDataEntry
{
	Dz1Asn1UTF8Str		*name;
	u32_t				 val;
} MyXDataEntry;

DZ1_CPPLINK DZ1_DLLPORT MyXDataEntry *MyXDataEntry_new(Dz1Asn1UTF8Str *name, 
													   u32_t val, Dz1Error *err);
static __inline__ MyXDataEntry *MyXDataEntry_gen(Dz1Error *err) { return MyXDataEntry_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyXDataEntry_copy(MyXDataEntry *dst, MyXDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyXDataEntry *MyXDataEntry_clone(MyXDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataEntry_purge(MyXDataEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataEntry_del(MyXDataEntry *p);
static __inline__ void MyXDataEntry_delAndSetNull(void *ptr)
{
	MyXDataEntry **p = (MyXDataEntry **)ptr;
	if (p) { MyXDataEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataEntryA_dump(MyXDataEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataEntryA_fdump(FILE *fp, MyXDataEntry *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataEntryW_dump(MyXDataEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataEntryW_fdump(FILE *fp, MyXDataEntry *p, int tab);
#ifdef UNICODE
#define MyXDataEntry_dump MyXDataEntryW_dump
#define MyXDataEntry_fdump MyXDataEntryW_fdump
#else //  UNICODE
#define MyXDataEntry_dump MyXDataEntryA_dump
#define MyXDataEntry_fdump MyXDataEntryA_fdump
#endif //  UNICODE
static __inline__ void MyXDataEntryX_dump(MyXDataEntry *p, int tab) { DZ1_DUMP(MyXDataEntry, p, tab); }
static __inline__ void MyXDataEntryX_fdump(FILE *fp, MyXDataEntry *p, int tab) { DZ1_FDUMP(fp, MyXDataEntry, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataEntry_dump MyXDataEntryA_dump
#define MyXDataEntryX_dump MyXDataEntryA_dump
#define MyXDataEntry_fdump MyXDataEntryA_fdump
#define MyXDataEntryX_fdump MyXDataEntryA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int MyXDataEntry_cmp(MyXDataEntry *a, MyXDataEntry *b); 
// MyXDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataUniqueList
typedef struct MyXDataUniqueList
{
	void *storage;
	unsigned int (*count)(struct MyXDataUniqueList *p);
	Dz1Error (*travel)(struct MyXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	MyXDataEntry **(*get_array)(struct MyXDataUniqueList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyXDataUniqueList *p, MyXDataEntry *data);
	bool_t (*remove)(struct MyXDataUniqueList *p, MyXDataEntry *key);
	MyXDataEntry *(*extract)(struct MyXDataUniqueList *p, MyXDataEntry *key);
	MyXDataEntry *(*find)(struct MyXDataUniqueList *p, MyXDataEntry *key);
	MyXDataEntry *(*getHead)(struct MyXDataUniqueList *p);
	MyXDataEntry *(*getTail)(struct MyXDataUniqueList *p);
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataUniqueList;

DZ1_CPPLINK DZ1_DLLPORT MyXDataUniqueList *MyXDataUniqueList_new(Dz1Error *err);
static __inline__ MyXDataUniqueList *MyXDataUniqueList_gen(Dz1Error *err) { return MyXDataUniqueList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyXDataUniqueList *MyXDataUniqueList_clone(MyXDataUniqueList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueList_purge(MyXDataUniqueList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueList_del(MyXDataUniqueList *p);
static __inline__ void MyXDataUniqueList_delAndSetNull(void *ptr)
{
	MyXDataUniqueList **p = (MyXDataUniqueList **)ptr;
	if (p != NULL) { MyXDataUniqueList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueListA_dump(MyXDataUniqueList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueListA_fdump(FILE *fp, MyXDataUniqueList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueListW_dump(MyXDataUniqueList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueListW_fdump(FILE *fp, MyXDataUniqueList *p, int tab);
#ifdef UNICODE
#define MyXDataUniqueList_dump MyXDataUniqueListW_dump
#define MyXDataUniqueList_fdump MyXDataUniqueListW_fdump
#else //  UNICODE
#define MyXDataUniqueList_dump MyXDataUniqueListA_dump
#define MyXDataUniqueList_fdump MyXDataUniqueListA_fdump
#endif //  UNICODE
static __inline__ void MyXDataUniqueListX_dump(MyXDataUniqueList *p, int tab) { DZ1_DUMP(MyXDataUniqueList, p, tab); }
static __inline__ void MyXDataUniqueListX_fdump(FILE *fp, MyXDataUniqueList *p, int tab) { DZ1_FDUMP(fp, MyXDataUniqueList, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataUniqueList_dump MyXDataUniqueListA_dump
#define MyXDataUniqueListX_dump MyXDataUniqueListA_dump
#define MyXDataUniqueList_fdump MyXDataUniqueListA_fdump
#define MyXDataUniqueListX_fdump MyXDataUniqueListA_fdump
#endif // UNIX_SYSTEM

// MyXDataUniqueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataOrderedList
typedef struct MyXDataOrderedList
{
	void *storage;
	unsigned int (*count)(struct MyXDataOrderedList *p);
	Dz1Error (*travel)(struct MyXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	MyXDataEntry **(*get_array)(struct MyXDataOrderedList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyXDataOrderedList *p, MyXDataEntry *data);
	bool_t (*remove)(struct MyXDataOrderedList *p, MyXDataEntry *key);
	MyXDataEntry *(*extract)(struct MyXDataOrderedList *p, MyXDataEntry *key);
	MyXDataEntry *(*find)(struct MyXDataOrderedList *p, MyXDataEntry *key);
	MyXDataEntry *(*getHead)(struct MyXDataOrderedList *p);
	MyXDataEntry *(*getTail)(struct MyXDataOrderedList *p);
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataOrderedList;

DZ1_CPPLINK DZ1_DLLPORT MyXDataOrderedList *MyXDataOrderedList_new(Dz1Error *err);
static __inline__ MyXDataOrderedList *MyXDataOrderedList_gen(Dz1Error *err) { return MyXDataOrderedList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyXDataOrderedList *MyXDataOrderedList_clone(MyXDataOrderedList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedList_purge(MyXDataOrderedList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedList_del(MyXDataOrderedList *p);
static __inline__ void MyXDataOrderedList_delAndSetNull(void *ptr)
{
	MyXDataOrderedList **p = (MyXDataOrderedList **)ptr;
	if (p != NULL) { MyXDataOrderedList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedListA_dump(MyXDataOrderedList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedListA_fdump(FILE *fp, MyXDataOrderedList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedListW_dump(MyXDataOrderedList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedListW_fdump(FILE *fp, MyXDataOrderedList *p, int tab);
#ifdef UNICODE
#define MyXDataOrderedList_dump MyXDataOrderedListW_dump
#define MyXDataOrderedList_fdump MyXDataOrderedListW_fdump
#else //  UNICODE
#define MyXDataOrderedList_dump MyXDataOrderedListA_dump
#define MyXDataOrderedList_fdump MyXDataOrderedListA_fdump
#endif //  UNICODE
static __inline__ void MyXDataOrderedListX_dump(MyXDataOrderedList *p, int tab) { DZ1_DUMP(MyXDataOrderedList, p, tab); }
static __inline__ void MyXDataOrderedListX_fdump(FILE *fp, MyXDataOrderedList *p, int tab) { DZ1_FDUMP(fp, MyXDataOrderedList, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataOrderedList_dump MyXDataOrderedListA_dump
#define MyXDataOrderedListX_dump MyXDataOrderedListA_dump
#define MyXDataOrderedList_fdump MyXDataOrderedListA_fdump
#define MyXDataOrderedListX_fdump MyXDataOrderedListA_fdump
#endif // UNIX_SYSTEM

// MyXDataOrderedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataList
typedef struct MyXDataList
{
	void *storage;
	unsigned int (*count)(struct MyXDataList *p);
	Dz1Error (*travel)(struct MyXDataList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyXDataList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyXDataList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	MyXDataEntry **(*get_array)(struct MyXDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyXDataList *p, MyXDataEntry *data);
	MyXDataEntry *(*extract)(struct MyXDataList *p, MyXDataEntry *ptr);
	MyXDataEntry *(*find)(struct MyXDataList *p, MyXDataEntry *key);
	MyXDataEntry *(*getHead)(struct MyXDataList *p);
	MyXDataEntry *(*getTail)(struct MyXDataList *p);
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataList;

DZ1_CPPLINK DZ1_DLLPORT MyXDataList *MyXDataList_new(Dz1Error *err);
static __inline__ MyXDataList *MyXDataList_gen(Dz1Error *err) { return MyXDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyXDataList *MyXDataList_clone(MyXDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataList_purge(MyXDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataList_del(MyXDataList *p);
static __inline__ void MyXDataList_delAndSetNull(void *ptr)
{
	MyXDataList **p = (MyXDataList **)ptr;
	if (p != NULL) { MyXDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataListA_dump(MyXDataList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataListA_fdump(FILE *fp, MyXDataList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataListW_dump(MyXDataList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataListW_fdump(FILE *fp, MyXDataList *p, int tab);
#ifdef UNICODE
#define MyXDataList_dump MyXDataListW_dump
#define MyXDataList_fdump MyXDataListW_fdump
#else //  UNICODE
#define MyXDataList_dump MyXDataListA_dump
#define MyXDataList_fdump MyXDataListA_fdump
#endif //  UNICODE
static __inline__ void MyXDataListX_dump(MyXDataList *p, int tab) { DZ1_DUMP(MyXDataList, p, tab); }
static __inline__ void MyXDataListX_fdump(FILE *fp, MyXDataList *p, int tab) { DZ1_FDUMP(fp, MyXDataList, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataList_dump MyXDataListA_dump
#define MyXDataListX_dump MyXDataListA_dump
#define MyXDataList_fdump MyXDataListA_fdump
#define MyXDataListX_fdump MyXDataListA_fdump
#endif // UNIX_SYSTEM

// MyXDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataUniqueRefList
typedef struct MyXDataUniqueRefList
{
	void *storage;
	unsigned int (*count)(struct MyXDataUniqueRefList *p);
	Dz1Error (*travel)(struct MyXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	MyXDataEntry **(*get_array)(struct MyXDataUniqueRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyXDataUniqueRefList *p, MyXDataEntry *data);
	bool_t (*remove)(struct MyXDataUniqueRefList *p, MyXDataEntry *key);
	MyXDataEntry *(*extract)(struct MyXDataUniqueRefList *p, MyXDataEntry *key);
	MyXDataEntry *(*find)(struct MyXDataUniqueRefList *p, MyXDataEntry *key);
	MyXDataEntry *(*getHead)(struct MyXDataUniqueRefList *p);
	MyXDataEntry *(*getTail)(struct MyXDataUniqueRefList *p);
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataUniqueRefList;

DZ1_CPPLINK DZ1_DLLPORT MyXDataUniqueRefList *MyXDataUniqueRefList_new(Dz1Error *err);
static __inline__ MyXDataUniqueRefList *MyXDataUniqueRefList_gen(Dz1Error *err) { return MyXDataUniqueRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyXDataUniqueRefList *MyXDataUniqueRefList_clone(MyXDataUniqueRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueRefList_purge(MyXDataUniqueRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueRefList_del(MyXDataUniqueRefList *p);
static __inline__ void MyXDataUniqueRefList_delAndSetNull(void *ptr)
{
	MyXDataUniqueRefList **p = (MyXDataUniqueRefList **)ptr;
	if (p != NULL) { MyXDataUniqueRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueRefListA_dump(MyXDataUniqueRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueRefListA_fdump(FILE *fp, MyXDataUniqueRefList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueRefListW_dump(MyXDataUniqueRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataUniqueRefListW_fdump(FILE *fp, MyXDataUniqueRefList *p, int tab);
#ifdef UNICODE
#define MyXDataUniqueRefList_dump MyXDataUniqueRefListW_dump
#define MyXDataUniqueRefList_fdump MyXDataUniqueRefListW_fdump
#else //  UNICODE
#define MyXDataUniqueRefList_dump MyXDataUniqueRefListA_dump
#define MyXDataUniqueRefList_fdump MyXDataUniqueRefListA_fdump
#endif //  UNICODE
static __inline__ void MyXDataUniqueRefListX_dump(MyXDataUniqueRefList *p, int tab) { DZ1_DUMP(MyXDataUniqueRefList, p, tab); }
static __inline__ void MyXDataUniqueRefListX_fdump(FILE *fp, MyXDataUniqueRefList *p, int tab) { DZ1_FDUMP(fp, MyXDataUniqueRefList, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataUniqueRefList_dump MyXDataUniqueRefListA_dump
#define MyXDataUniqueRefListX_dump MyXDataUniqueRefListA_dump
#define MyXDataUniqueRefList_fdump MyXDataUniqueRefListA_fdump
#define MyXDataUniqueRefListX_fdump MyXDataUniqueRefListA_fdump
#endif // UNIX_SYSTEM

// MyXDataUniqueRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataOrderedRefList
typedef struct MyXDataOrderedRefList
{
	void *storage;
	unsigned int (*count)(struct MyXDataOrderedRefList *p);
	Dz1Error (*travel)(struct MyXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	MyXDataEntry **(*get_array)(struct MyXDataOrderedRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyXDataOrderedRefList *p, MyXDataEntry *data);
	bool_t (*remove)(struct MyXDataOrderedRefList *p, MyXDataEntry *key);
	MyXDataEntry *(*extract)(struct MyXDataOrderedRefList *p, MyXDataEntry *key);
	MyXDataEntry *(*find)(struct MyXDataOrderedRefList *p, MyXDataEntry *key);
	MyXDataEntry *(*getHead)(struct MyXDataOrderedRefList *p);
	MyXDataEntry *(*getTail)(struct MyXDataOrderedRefList *p);
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataOrderedRefList;

DZ1_CPPLINK DZ1_DLLPORT MyXDataOrderedRefList *MyXDataOrderedRefList_new(Dz1Error *err);
static __inline__ MyXDataOrderedRefList *MyXDataOrderedRefList_gen(Dz1Error *err) { return MyXDataOrderedRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyXDataOrderedRefList *MyXDataOrderedRefList_clone(MyXDataOrderedRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedRefList_purge(MyXDataOrderedRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedRefList_del(MyXDataOrderedRefList *p);
static __inline__ void MyXDataOrderedRefList_delAndSetNull(void *ptr)
{
	MyXDataOrderedRefList **p = (MyXDataOrderedRefList **)ptr;
	if (p != NULL) { MyXDataOrderedRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedRefListA_dump(MyXDataOrderedRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedRefListA_fdump(FILE *fp, MyXDataOrderedRefList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedRefListW_dump(MyXDataOrderedRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataOrderedRefListW_fdump(FILE *fp, MyXDataOrderedRefList *p, int tab);
#ifdef UNICODE
#define MyXDataOrderedRefList_dump MyXDataOrderedRefListW_dump
#define MyXDataOrderedRefList_fdump MyXDataOrderedRefListW_fdump
#else //  UNICODE
#define MyXDataOrderedRefList_dump MyXDataOrderedRefListA_dump
#define MyXDataOrderedRefList_fdump MyXDataOrderedRefListA_fdump
#endif //  UNICODE
static __inline__ void MyXDataOrderedRefListX_dump(MyXDataOrderedRefList *p, int tab) { DZ1_DUMP(MyXDataOrderedRefList, p, tab); }
static __inline__ void MyXDataOrderedRefListX_fdump(FILE *fp, MyXDataOrderedRefList *p, int tab) { DZ1_FDUMP(fp, MyXDataOrderedRefList, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataOrderedRefList_dump MyXDataOrderedRefListA_dump
#define MyXDataOrderedRefListX_dump MyXDataOrderedRefListA_dump
#define MyXDataOrderedRefList_fdump MyXDataOrderedRefListA_fdump
#define MyXDataOrderedRefListX_fdump MyXDataOrderedRefListA_fdump
#endif // UNIX_SYSTEM

// MyXDataOrderedRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataRefList
typedef struct MyXDataRefList
{
	void *storage;
	unsigned int (*count)(struct MyXDataRefList *p);
	Dz1Error (*travel)(struct MyXDataRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyXDataRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyXDataRefList *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	MyXDataEntry **(*get_array)(struct MyXDataRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyXDataRefList *p, MyXDataEntry *data);
	MyXDataEntry *(*extract)(struct MyXDataRefList *p, MyXDataEntry *ptr);
	MyXDataEntry *(*find)(struct MyXDataRefList *p, MyXDataEntry *key);
	MyXDataEntry *(*getHead)(struct MyXDataRefList *p);
	MyXDataEntry *(*getTail)(struct MyXDataRefList *p);
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataRefList;

DZ1_CPPLINK DZ1_DLLPORT MyXDataRefList *MyXDataRefList_new(Dz1Error *err);
static __inline__ MyXDataRefList *MyXDataRefList_gen(Dz1Error *err) { return MyXDataRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyXDataRefList *MyXDataRefList_clone(MyXDataRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefList_purge(MyXDataRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefList_del(MyXDataRefList *p);
static __inline__ void MyXDataRefList_delAndSetNull(void *ptr)
{
	MyXDataRefList **p = (MyXDataRefList **)ptr;
	if (p != NULL) { MyXDataRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefListA_dump(MyXDataRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefListA_fdump(FILE *fp, MyXDataRefList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefListW_dump(MyXDataRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefListW_fdump(FILE *fp, MyXDataRefList *p, int tab);
#ifdef UNICODE
#define MyXDataRefList_dump MyXDataRefListW_dump
#define MyXDataRefList_fdump MyXDataRefListW_fdump
#else //  UNICODE
#define MyXDataRefList_dump MyXDataRefListA_dump
#define MyXDataRefList_fdump MyXDataRefListA_fdump
#endif //  UNICODE
static __inline__ void MyXDataRefListX_dump(MyXDataRefList *p, int tab) { DZ1_DUMP(MyXDataRefList, p, tab); }
static __inline__ void MyXDataRefListX_fdump(FILE *fp, MyXDataRefList *p, int tab) { DZ1_FDUMP(fp, MyXDataRefList, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataRefList_dump MyXDataRefListA_dump
#define MyXDataRefListX_dump MyXDataRefListA_dump
#define MyXDataRefList_fdump MyXDataRefListA_fdump
#define MyXDataRefListX_fdump MyXDataRefListA_fdump
#endif // UNIX_SYSTEM

// MyXDataRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataIndex
typedef struct MyXDataIndex
{
	void *storage;
	unsigned int (*count)(struct MyXDataIndex *p);
	Dz1Error (*travel)(struct MyXDataIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyXDataIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyXDataIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	MyXDataEntry **(*get_array)(struct MyXDataIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyXDataIndex *p, MyXDataEntry *data);
	bool_t (*remove)(struct MyXDataIndex *p, MyXDataEntry *key);
	MyXDataEntry *(*extract)(struct MyXDataIndex *p, MyXDataEntry *key);
	MyXDataEntry *(*find)(struct MyXDataIndex *p, MyXDataEntry *key);
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataIndex;

DZ1_CPPLINK DZ1_DLLPORT MyXDataIndex *MyXDataIndex_new(Dz1Error *err);
static __inline__ MyXDataIndex *MyXDataIndex_gen(Dz1Error *err) { return MyXDataIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyXDataIndex *MyXDataIndex_clone(MyXDataIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataIndex_purge(MyXDataIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataIndex_del(MyXDataIndex *p);
static __inline__ void MyXDataIndex_delAndSetNull(void *ptr)
{
	MyXDataIndex **p = (MyXDataIndex **)ptr;
	if (p != NULL) { MyXDataIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataIndexA_dump(MyXDataIndex *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataIndexA_fdump(FILE *fp, MyXDataIndex *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataIndexW_dump(MyXDataIndex *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataIndexW_fdump(FILE *fp, MyXDataIndex *p, int tab);
#ifdef UNICODE
#define MyXDataIndex_dump MyXDataIndexW_dump
#define MyXDataIndex_fdump MyXDataIndexW_fdump
#else //  UNICODE
#define MyXDataIndex_dump MyXDataIndexA_dump
#define MyXDataIndex_fdump MyXDataIndexA_fdump
#endif //  UNICODE
static __inline__ void MyXDataIndexX_dump(MyXDataIndex *p, int tab) { DZ1_DUMP(MyXDataIndex, p, tab); }
static __inline__ void MyXDataIndexX_fdump(FILE *fp, MyXDataIndex *p, int tab) { DZ1_FDUMP(fp, MyXDataIndex, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataIndex_dump MyXDataIndexA_dump
#define MyXDataIndexX_dump MyXDataIndexA_dump
#define MyXDataIndex_fdump MyXDataIndexA_fdump
#define MyXDataIndexX_fdump MyXDataIndexA_fdump
#endif // UNIX_SYSTEM

// MyXDataIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataRefIndex
typedef struct MyXDataRefIndex
{
	void *storage;
	unsigned int (*count)(struct MyXDataRefIndex *p);
	Dz1Error (*travel)(struct MyXDataRefIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyXDataRefIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyXDataRefIndex *p, Dz1Error (*func)(void *ptr, MyXDataEntry *entry), void *ptr);
	MyXDataEntry **(*get_array)(struct MyXDataRefIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyXDataRefIndex *p, MyXDataEntry *data);
	bool_t (*remove)(struct MyXDataRefIndex *p, MyXDataEntry *key);
	MyXDataEntry *(*extract)(struct MyXDataRefIndex *p, MyXDataEntry *key);
	MyXDataEntry *(*find)(struct MyXDataRefIndex *p, MyXDataEntry *key);
	int (*cmp)(MyXDataEntry *a, MyXDataEntry *b);
} MyXDataRefIndex;

DZ1_CPPLINK DZ1_DLLPORT MyXDataRefIndex *MyXDataRefIndex_new(Dz1Error *err);
static __inline__ MyXDataRefIndex *MyXDataRefIndex_gen(Dz1Error *err) { return MyXDataRefIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyXDataRefIndex *MyXDataRefIndex_clone(MyXDataRefIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefIndex_purge(MyXDataRefIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefIndex_del(MyXDataRefIndex *p);
static __inline__ void MyXDataRefIndex_delAndSetNull(void *ptr)
{
	MyXDataRefIndex **p = (MyXDataRefIndex **)ptr;
	if (p != NULL) { MyXDataRefIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefIndexA_dump(MyXDataRefIndex *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefIndexA_fdump(FILE *fp, MyXDataRefIndex *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefIndexW_dump(MyXDataRefIndex *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataRefIndexW_fdump(FILE *fp, MyXDataRefIndex *p, int tab);
#ifdef UNICODE
#define MyXDataRefIndex_dump MyXDataRefIndexW_dump
#define MyXDataRefIndex_fdump MyXDataRefIndexW_fdump
#else //  UNICODE
#define MyXDataRefIndex_dump MyXDataRefIndexA_dump
#define MyXDataRefIndex_fdump MyXDataRefIndexA_fdump
#endif //  UNICODE
static __inline__ void MyXDataRefIndexX_dump(MyXDataRefIndex *p, int tab) { DZ1_DUMP(MyXDataRefIndex, p, tab); }
static __inline__ void MyXDataRefIndexX_fdump(FILE *fp, MyXDataRefIndex *p, int tab) { DZ1_FDUMP(fp, MyXDataRefIndex, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataRefIndex_dump MyXDataRefIndexA_dump
#define MyXDataRefIndexX_dump MyXDataRefIndexA_dump
#define MyXDataRefIndex_fdump MyXDataRefIndexA_fdump
#define MyXDataRefIndexX_fdump MyXDataRefIndexA_fdump
#endif // UNIX_SYSTEM

// MyXDataRefIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyXDataInfo
typedef struct MyXDataInfo
{
	MyXDataEntry	**obj_ptr_arr;
	u32_t			  obj_ptr_cnt;
	MyXDataEntry	 *obj_arr;
	u32_t			  obj_cnt;
	u64_t			 *prims_arr;
	u32_t			  prims_cnt;
	u64_t			**primptrs_arr;
	u32_t			  primptrs_cnt;
	s32_t			 *i_val;
} MyXDataInfo;

DZ1_CPPLINK DZ1_DLLPORT MyXDataInfo *MyXDataInfo_new(MyXDataEntry **obj_ptr_arr_e_clone, 
													 u32_t obj_ptr_cnt, 
													 MyXDataEntry *obj_arr_e_copy, 
													 u32_t obj_cnt, 
													 u64_t *prims_arr_e_copy, 
													 u32_t prims_cnt, 
													 u64_t **primptrs_arr_e_clone, 
													 u32_t primptrs_cnt, 
													 s32_t *i_val_ref, Dz1Error *err);
static __inline__ MyXDataInfo *MyXDataInfo_gen(Dz1Error *err) { return MyXDataInfo_new(NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyXDataInfo_copy(MyXDataInfo *dst, MyXDataInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyXDataInfo *MyXDataInfo_clone(MyXDataInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataInfo_purge(MyXDataInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataInfo_del(MyXDataInfo *p);
static __inline__ void MyXDataInfo_delAndSetNull(void *ptr)
{
	MyXDataInfo **p = (MyXDataInfo **)ptr;
	if (p) { MyXDataInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyXDataInfoA_dump(MyXDataInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataInfoA_fdump(FILE *fp, MyXDataInfo *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyXDataInfoW_dump(MyXDataInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyXDataInfoW_fdump(FILE *fp, MyXDataInfo *p, int tab);
#ifdef UNICODE
#define MyXDataInfo_dump MyXDataInfoW_dump
#define MyXDataInfo_fdump MyXDataInfoW_fdump
#else //  UNICODE
#define MyXDataInfo_dump MyXDataInfoA_dump
#define MyXDataInfo_fdump MyXDataInfoA_fdump
#endif //  UNICODE
static __inline__ void MyXDataInfoX_dump(MyXDataInfo *p, int tab) { DZ1_DUMP(MyXDataInfo, p, tab); }
static __inline__ void MyXDataInfoX_fdump(FILE *fp, MyXDataInfo *p, int tab) { DZ1_FDUMP(fp, MyXDataInfo, p, tab); }
#else // UNIX_SYSTEM
#define MyXDataInfo_dump MyXDataInfoA_dump
#define MyXDataInfoX_dump MyXDataInfoA_dump
#define MyXDataInfo_fdump MyXDataInfoA_fdump
#define MyXDataInfoX_fdump MyXDataInfoA_fdump
#endif // UNIX_SYSTEM
// MyXDataInfo
////////////////////////////////////////////////////////////////////////////////

#endif
