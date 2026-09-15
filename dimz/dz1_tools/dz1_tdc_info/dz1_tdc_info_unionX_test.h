#ifndef _DZ1_TDC_DZ1_TDC_INFO_UNION_X_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_UNION_X_TEST_H_

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
// MyUnionXDataPresent
typedef enum MyUnionXDataPresent
{
	MyUnionXDataPresent_name,
	MyUnionXDataPresent_val,
	MyUnionXDataPresent_max
} MyUnionXDataPresent;

DZ1_CPPLINK str_t MyUnionXDataPresentStrA(MyUnionXDataPresent v);
DZ1_CPPLINK MyUnionXDataPresent MyUnionXDataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t MyUnionXDataPresentStrW(MyUnionXDataPresent v);
DZ1_CPPLINK MyUnionXDataPresent MyUnionXDataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define MyUnionXDataPresentStr MyUnionXDataPresentStrW
#define MyUnionXDataPresentFromStr MyUnionXDataPresentFromStrW
#else // UNICODE
#define MyUnionXDataPresentStr MyUnionXDataPresentStrA
#define MyUnionXDataPresentFromStr MyUnionXDataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define MyUnionXDataPresentStr MyUnionXDataPresentStrA
#define MyUnionXDataPresentFromStr MyUnionXDataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataPresent *MyUnionXDataPresent_new(MyUnionXDataPresent *src, Dz1Error *err);
static __inline__ MyUnionXDataPresent *MyUnionXDataPresent_gen(Dz1Error *err) { MyUnionXDataPresent v = MyUnionXDataPresent_max; return MyUnionXDataPresent_new(&v, err); }
#define MyUnionXDataPresent_clone             MyUnionXDataPresent_new
static __inline__ void MyUnionXDataPresent_del(MyUnionXDataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void MyUnionXDataPresent_delAndSetNull(void *ptr)
{
	MyUnionXDataPresent **p = (MyUnionXDataPresent **)ptr;
	if (p != NULL) { MyUnionXDataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataPresentA_dump(MyUnionXDataPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataPresentA_fdump(FILE *fp, MyUnionXDataPresent *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataPresentW_dump(MyUnionXDataPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataPresentW_fdump(FILE *fp, MyUnionXDataPresent *v, int tab);
#ifdef UNICODE
#define MyUnionXDataPresent_dump MyUnionXDataPresentW_dump
#define MyUnionXDataPresent_fdump MyUnionXDataPresentW_fdump
#else //  UNICODE
#define MyUnionXDataPresent_dump MyUnionXDataPresentA_dump
#define MyUnionXDataPresent_fdump MyUnionXDataPresentA_fdump
#endif //  UNICODE
static __inline__ void MyUnionXDataPresentX_dump(MyUnionXDataPresent *p, int tab) { DZ1_DUMP(MyUnionXDataPresent, p, tab); }
static __inline__ void MyUnionXDataPresentX_fdump(FILE *fp, MyUnionXDataPresent *p, int tab) { DZ1_FDUMP(fp, MyUnionXDataPresent, p, tab); }
#else // UNIX_SYSTEM
#define MyUnionXDataPresent_dump MyUnionXDataPresentA_dump
#define MyUnionXDataPresentX_dump MyUnionXDataPresentA_dump
#define MyUnionXDataPresent_fdump MyUnionXDataPresentA_fdump
#define MyUnionXDataPresentX_fdump MyUnionXDataPresentA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int MyUnionXDataPresent_cmp(MyUnionXDataPresent *a, MyUnionXDataPresent *b);
// MyUnionXDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXData
typedef struct MyUnionXData
{
	MyUnionXDataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1UTF8Str		*name;
		u32_t				 val;
	} x;
} MyUnionXData;

DZ1_CPPLINK DZ1_DLLPORT MyUnionXData *MyUnionXData_new(MyUnionXDataPresent present, void *ptr, Dz1Error *err);
static __inline__ MyUnionXData *MyUnionXData_gen(Dz1Error *err) { return MyUnionXData_new(MyUnionXDataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  MyUnionXData_copy(MyUnionXData *dst, MyUnionXData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnionXData *MyUnionXData_clone(MyUnionXData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXData_purge(MyUnionXData *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXData_del(MyUnionXData *p);
static __inline__ void MyUnionXData_delAndSetNull(void *ptr)
{
	MyUnionXData **p = (MyUnionXData **)ptr;
	if (p != NULL) { MyUnionXData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataA_dump(MyUnionXData *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataA_fdump(FILE *fp, MyUnionXData *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataW_dump(MyUnionXData *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataW_fdump(FILE *fp, MyUnionXData *p, int tab);
#ifdef UNICODE
#define MyUnionXData_dump MyUnionXDataW_dump
#define MyUnionXData_fdump MyUnionXDataW_fdump
#else //  UNICODE
#define MyUnionXData_dump MyUnionXDataA_dump
#define MyUnionXData_fdump MyUnionXDataA_fdump
#endif //  UNICODE
static __inline__ void MyUnionXDataX_dump(MyUnionXData *p, int tab) { DZ1_DUMP(MyUnionXData, p, tab); }
static __inline__ void MyUnionXDataX_fdump(FILE *fp, MyUnionXData *p, int tab) { DZ1_FDUMP(fp, MyUnionXData, p, tab); }
#else // UNIX_SYSTEM
#define MyUnionXData_dump MyUnionXDataA_dump
#define MyUnionXDataX_dump MyUnionXDataA_dump
#define MyUnionXData_fdump MyUnionXDataA_fdump
#define MyUnionXDataX_fdump MyUnionXDataA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int MyUnionXData_cmp(MyUnionXData *a, MyUnionXData *b);
// MyUnionXData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataUniqueList
typedef struct MyUnionXDataUniqueList
{
	void *storage;
	unsigned int (*count)(struct MyUnionXDataUniqueList *p);
	Dz1Error (*travel)(struct MyUnionXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionXDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	MyUnionXData **(*get_array)(struct MyUnionXDataUniqueList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionXDataUniqueList *p, MyUnionXData *data);
	bool_t (*remove)(struct MyUnionXDataUniqueList *p, MyUnionXData *key);
	MyUnionXData *(*extract)(struct MyUnionXDataUniqueList *p, MyUnionXData *key);
	MyUnionXData *(*find)(struct MyUnionXDataUniqueList *p, MyUnionXData *key);
	MyUnionXData *(*getHead)(struct MyUnionXDataUniqueList *p);
	MyUnionXData *(*getTail)(struct MyUnionXDataUniqueList *p);
	int (*cmp)(MyUnionXData *a, MyUnionXData *b);
} MyUnionXDataUniqueList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataUniqueList *MyUnionXDataUniqueList_new(Dz1Error *err);
static __inline__ MyUnionXDataUniqueList *MyUnionXDataUniqueList_gen(Dz1Error *err) { return MyUnionXDataUniqueList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataUniqueList *MyUnionXDataUniqueList_clone(MyUnionXDataUniqueList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueList_purge(MyUnionXDataUniqueList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueList_del(MyUnionXDataUniqueList *p);
static __inline__ void MyUnionXDataUniqueList_delAndSetNull(void *ptr)
{
	MyUnionXDataUniqueList **p = (MyUnionXDataUniqueList **)ptr;
	if (p != NULL) { MyUnionXDataUniqueList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueListA_dump(MyUnionXDataUniqueList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueListA_fdump(FILE *fp, MyUnionXDataUniqueList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueListW_dump(MyUnionXDataUniqueList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueListW_fdump(FILE *fp, MyUnionXDataUniqueList *p, int tab);
#ifdef UNICODE
#define MyUnionXDataUniqueList_dump MyUnionXDataUniqueListW_dump
#define MyUnionXDataUniqueList_fdump MyUnionXDataUniqueListW_fdump
#else //  UNICODE
#define MyUnionXDataUniqueList_dump MyUnionXDataUniqueListA_dump
#define MyUnionXDataUniqueList_fdump MyUnionXDataUniqueListA_fdump
#endif //  UNICODE
static __inline__ void MyUnionXDataUniqueListX_dump(MyUnionXDataUniqueList *p, int tab) { DZ1_DUMP(MyUnionXDataUniqueList, p, tab); }
static __inline__ void MyUnionXDataUniqueListX_fdump(FILE *fp, MyUnionXDataUniqueList *p, int tab) { DZ1_FDUMP(fp, MyUnionXDataUniqueList, p, tab); }
#else // UNIX_SYSTEM
#define MyUnionXDataUniqueList_dump MyUnionXDataUniqueListA_dump
#define MyUnionXDataUniqueListX_dump MyUnionXDataUniqueListA_dump
#define MyUnionXDataUniqueList_fdump MyUnionXDataUniqueListA_fdump
#define MyUnionXDataUniqueListX_fdump MyUnionXDataUniqueListA_fdump
#endif // UNIX_SYSTEM

// MyUnionXDataUniqueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataOrderedList
typedef struct MyUnionXDataOrderedList
{
	void *storage;
	unsigned int (*count)(struct MyUnionXDataOrderedList *p);
	Dz1Error (*travel)(struct MyUnionXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionXDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	MyUnionXData **(*get_array)(struct MyUnionXDataOrderedList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionXDataOrderedList *p, MyUnionXData *data);
	bool_t (*remove)(struct MyUnionXDataOrderedList *p, MyUnionXData *key);
	MyUnionXData *(*extract)(struct MyUnionXDataOrderedList *p, MyUnionXData *key);
	MyUnionXData *(*find)(struct MyUnionXDataOrderedList *p, MyUnionXData *key);
	MyUnionXData *(*getHead)(struct MyUnionXDataOrderedList *p);
	MyUnionXData *(*getTail)(struct MyUnionXDataOrderedList *p);
	int (*cmp)(MyUnionXData *a, MyUnionXData *b);
} MyUnionXDataOrderedList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataOrderedList *MyUnionXDataOrderedList_new(Dz1Error *err);
static __inline__ MyUnionXDataOrderedList *MyUnionXDataOrderedList_gen(Dz1Error *err) { return MyUnionXDataOrderedList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataOrderedList *MyUnionXDataOrderedList_clone(MyUnionXDataOrderedList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedList_purge(MyUnionXDataOrderedList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedList_del(MyUnionXDataOrderedList *p);
static __inline__ void MyUnionXDataOrderedList_delAndSetNull(void *ptr)
{
	MyUnionXDataOrderedList **p = (MyUnionXDataOrderedList **)ptr;
	if (p != NULL) { MyUnionXDataOrderedList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedListA_dump(MyUnionXDataOrderedList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedListA_fdump(FILE *fp, MyUnionXDataOrderedList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedListW_dump(MyUnionXDataOrderedList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedListW_fdump(FILE *fp, MyUnionXDataOrderedList *p, int tab);
#ifdef UNICODE
#define MyUnionXDataOrderedList_dump MyUnionXDataOrderedListW_dump
#define MyUnionXDataOrderedList_fdump MyUnionXDataOrderedListW_fdump
#else //  UNICODE
#define MyUnionXDataOrderedList_dump MyUnionXDataOrderedListA_dump
#define MyUnionXDataOrderedList_fdump MyUnionXDataOrderedListA_fdump
#endif //  UNICODE
static __inline__ void MyUnionXDataOrderedListX_dump(MyUnionXDataOrderedList *p, int tab) { DZ1_DUMP(MyUnionXDataOrderedList, p, tab); }
static __inline__ void MyUnionXDataOrderedListX_fdump(FILE *fp, MyUnionXDataOrderedList *p, int tab) { DZ1_FDUMP(fp, MyUnionXDataOrderedList, p, tab); }
#else // UNIX_SYSTEM
#define MyUnionXDataOrderedList_dump MyUnionXDataOrderedListA_dump
#define MyUnionXDataOrderedListX_dump MyUnionXDataOrderedListA_dump
#define MyUnionXDataOrderedList_fdump MyUnionXDataOrderedListA_fdump
#define MyUnionXDataOrderedListX_fdump MyUnionXDataOrderedListA_fdump
#endif // UNIX_SYSTEM

// MyUnionXDataOrderedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataList
typedef struct MyUnionXDataList
{
	void *storage;
	unsigned int (*count)(struct MyUnionXDataList *p);
	Dz1Error (*travel)(struct MyUnionXDataList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionXDataList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionXDataList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	MyUnionXData **(*get_array)(struct MyUnionXDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionXDataList *p, MyUnionXData *data);
	bool_t (*remove)(struct MyUnionXDataList *p, MyUnionXData *ptr);
	MyUnionXData *(*extract)(struct MyUnionXDataList *p, MyUnionXData *ptr);
	MyUnionXData *(*find)(struct MyUnionXDataList *p, MyUnionXData *key);
	MyUnionXData *(*getHead)(struct MyUnionXDataList *p);
	MyUnionXData *(*getTail)(struct MyUnionXDataList *p);
	int (*cmp)(MyUnionXData *a, MyUnionXData *b);
} MyUnionXDataList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataList *MyUnionXDataList_new(Dz1Error *err);
static __inline__ MyUnionXDataList *MyUnionXDataList_gen(Dz1Error *err) { return MyUnionXDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataList *MyUnionXDataList_clone(MyUnionXDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataList_purge(MyUnionXDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataList_del(MyUnionXDataList *p);
static __inline__ void MyUnionXDataList_delAndSetNull(void *ptr)
{
	MyUnionXDataList **p = (MyUnionXDataList **)ptr;
	if (p != NULL) { MyUnionXDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataListA_dump(MyUnionXDataList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataListA_fdump(FILE *fp, MyUnionXDataList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataListW_dump(MyUnionXDataList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataListW_fdump(FILE *fp, MyUnionXDataList *p, int tab);
#ifdef UNICODE
#define MyUnionXDataList_dump MyUnionXDataListW_dump
#define MyUnionXDataList_fdump MyUnionXDataListW_fdump
#else //  UNICODE
#define MyUnionXDataList_dump MyUnionXDataListA_dump
#define MyUnionXDataList_fdump MyUnionXDataListA_fdump
#endif //  UNICODE
static __inline__ void MyUnionXDataListX_dump(MyUnionXDataList *p, int tab) { DZ1_DUMP(MyUnionXDataList, p, tab); }
static __inline__ void MyUnionXDataListX_fdump(FILE *fp, MyUnionXDataList *p, int tab) { DZ1_FDUMP(fp, MyUnionXDataList, p, tab); }
#else // UNIX_SYSTEM
#define MyUnionXDataList_dump MyUnionXDataListA_dump
#define MyUnionXDataListX_dump MyUnionXDataListA_dump
#define MyUnionXDataList_fdump MyUnionXDataListA_fdump
#define MyUnionXDataListX_fdump MyUnionXDataListA_fdump
#endif // UNIX_SYSTEM

// MyUnionXDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataUniqueRefList
typedef struct MyUnionXDataUniqueRefList
{
	void *storage;
	unsigned int (*count)(struct MyUnionXDataUniqueRefList *p);
	Dz1Error (*travel)(struct MyUnionXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionXDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	MyUnionXData **(*get_array)(struct MyUnionXDataUniqueRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionXDataUniqueRefList *p, MyUnionXData *data);
	bool_t (*remove)(struct MyUnionXDataUniqueRefList *p, MyUnionXData *key);
	MyUnionXData *(*extract)(struct MyUnionXDataUniqueRefList *p, MyUnionXData *key);
	MyUnionXData *(*find)(struct MyUnionXDataUniqueRefList *p, MyUnionXData *key);
	MyUnionXData *(*getHead)(struct MyUnionXDataUniqueRefList *p);
	MyUnionXData *(*getTail)(struct MyUnionXDataUniqueRefList *p);
	int (*cmp)(MyUnionXData *a, MyUnionXData *b);
} MyUnionXDataUniqueRefList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataUniqueRefList *MyUnionXDataUniqueRefList_new(Dz1Error *err);
static __inline__ MyUnionXDataUniqueRefList *MyUnionXDataUniqueRefList_gen(Dz1Error *err) { return MyUnionXDataUniqueRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataUniqueRefList *MyUnionXDataUniqueRefList_clone(MyUnionXDataUniqueRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueRefList_purge(MyUnionXDataUniqueRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueRefList_del(MyUnionXDataUniqueRefList *p);
static __inline__ void MyUnionXDataUniqueRefList_delAndSetNull(void *ptr)
{
	MyUnionXDataUniqueRefList **p = (MyUnionXDataUniqueRefList **)ptr;
	if (p != NULL) { MyUnionXDataUniqueRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueRefListA_dump(MyUnionXDataUniqueRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueRefListA_fdump(FILE *fp, MyUnionXDataUniqueRefList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueRefListW_dump(MyUnionXDataUniqueRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataUniqueRefListW_fdump(FILE *fp, MyUnionXDataUniqueRefList *p, int tab);
#ifdef UNICODE
#define MyUnionXDataUniqueRefList_dump MyUnionXDataUniqueRefListW_dump
#define MyUnionXDataUniqueRefList_fdump MyUnionXDataUniqueRefListW_fdump
#else //  UNICODE
#define MyUnionXDataUniqueRefList_dump MyUnionXDataUniqueRefListA_dump
#define MyUnionXDataUniqueRefList_fdump MyUnionXDataUniqueRefListA_fdump
#endif //  UNICODE
static __inline__ void MyUnionXDataUniqueRefListX_dump(MyUnionXDataUniqueRefList *p, int tab) { DZ1_DUMP(MyUnionXDataUniqueRefList, p, tab); }
static __inline__ void MyUnionXDataUniqueRefListX_fdump(FILE *fp, MyUnionXDataUniqueRefList *p, int tab) { DZ1_FDUMP(fp, MyUnionXDataUniqueRefList, p, tab); }
#else // UNIX_SYSTEM
#define MyUnionXDataUniqueRefList_dump MyUnionXDataUniqueRefListA_dump
#define MyUnionXDataUniqueRefListX_dump MyUnionXDataUniqueRefListA_dump
#define MyUnionXDataUniqueRefList_fdump MyUnionXDataUniqueRefListA_fdump
#define MyUnionXDataUniqueRefListX_fdump MyUnionXDataUniqueRefListA_fdump
#endif // UNIX_SYSTEM

// MyUnionXDataUniqueRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataOrderedRefList
typedef struct MyUnionXDataOrderedRefList
{
	void *storage;
	unsigned int (*count)(struct MyUnionXDataOrderedRefList *p);
	Dz1Error (*travel)(struct MyUnionXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionXDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	MyUnionXData **(*get_array)(struct MyUnionXDataOrderedRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionXDataOrderedRefList *p, MyUnionXData *data);
	bool_t (*remove)(struct MyUnionXDataOrderedRefList *p, MyUnionXData *key);
	MyUnionXData *(*extract)(struct MyUnionXDataOrderedRefList *p, MyUnionXData *key);
	MyUnionXData *(*find)(struct MyUnionXDataOrderedRefList *p, MyUnionXData *key);
	MyUnionXData *(*getHead)(struct MyUnionXDataOrderedRefList *p);
	MyUnionXData *(*getTail)(struct MyUnionXDataOrderedRefList *p);
	int (*cmp)(MyUnionXData *a, MyUnionXData *b);
} MyUnionXDataOrderedRefList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataOrderedRefList *MyUnionXDataOrderedRefList_new(Dz1Error *err);
static __inline__ MyUnionXDataOrderedRefList *MyUnionXDataOrderedRefList_gen(Dz1Error *err) { return MyUnionXDataOrderedRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataOrderedRefList *MyUnionXDataOrderedRefList_clone(MyUnionXDataOrderedRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedRefList_purge(MyUnionXDataOrderedRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedRefList_del(MyUnionXDataOrderedRefList *p);
static __inline__ void MyUnionXDataOrderedRefList_delAndSetNull(void *ptr)
{
	MyUnionXDataOrderedRefList **p = (MyUnionXDataOrderedRefList **)ptr;
	if (p != NULL) { MyUnionXDataOrderedRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedRefListA_dump(MyUnionXDataOrderedRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedRefListA_fdump(FILE *fp, MyUnionXDataOrderedRefList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedRefListW_dump(MyUnionXDataOrderedRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataOrderedRefListW_fdump(FILE *fp, MyUnionXDataOrderedRefList *p, int tab);
#ifdef UNICODE
#define MyUnionXDataOrderedRefList_dump MyUnionXDataOrderedRefListW_dump
#define MyUnionXDataOrderedRefList_fdump MyUnionXDataOrderedRefListW_fdump
#else //  UNICODE
#define MyUnionXDataOrderedRefList_dump MyUnionXDataOrderedRefListA_dump
#define MyUnionXDataOrderedRefList_fdump MyUnionXDataOrderedRefListA_fdump
#endif //  UNICODE
static __inline__ void MyUnionXDataOrderedRefListX_dump(MyUnionXDataOrderedRefList *p, int tab) { DZ1_DUMP(MyUnionXDataOrderedRefList, p, tab); }
static __inline__ void MyUnionXDataOrderedRefListX_fdump(FILE *fp, MyUnionXDataOrderedRefList *p, int tab) { DZ1_FDUMP(fp, MyUnionXDataOrderedRefList, p, tab); }
#else // UNIX_SYSTEM
#define MyUnionXDataOrderedRefList_dump MyUnionXDataOrderedRefListA_dump
#define MyUnionXDataOrderedRefListX_dump MyUnionXDataOrderedRefListA_dump
#define MyUnionXDataOrderedRefList_fdump MyUnionXDataOrderedRefListA_fdump
#define MyUnionXDataOrderedRefListX_fdump MyUnionXDataOrderedRefListA_fdump
#endif // UNIX_SYSTEM

// MyUnionXDataOrderedRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataRefList
typedef struct MyUnionXDataRefList
{
	void *storage;
	unsigned int (*count)(struct MyUnionXDataRefList *p);
	Dz1Error (*travel)(struct MyUnionXDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionXDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionXDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionXData *entry), void *ptr);
	MyUnionXData **(*get_array)(struct MyUnionXDataRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionXDataRefList *p, MyUnionXData *data);
	bool_t (*remove)(struct MyUnionXDataRefList *p, MyUnionXData *ptr);
	MyUnionXData *(*extract)(struct MyUnionXDataRefList *p, MyUnionXData *ptr);
	MyUnionXData *(*find)(struct MyUnionXDataRefList *p, MyUnionXData *key);
	MyUnionXData *(*getHead)(struct MyUnionXDataRefList *p);
	MyUnionXData *(*getTail)(struct MyUnionXDataRefList *p);
	int (*cmp)(MyUnionXData *a, MyUnionXData *b);
} MyUnionXDataRefList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataRefList *MyUnionXDataRefList_new(Dz1Error *err);
static __inline__ MyUnionXDataRefList *MyUnionXDataRefList_gen(Dz1Error *err) { return MyUnionXDataRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataRefList *MyUnionXDataRefList_clone(MyUnionXDataRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataRefList_purge(MyUnionXDataRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataRefList_del(MyUnionXDataRefList *p);
static __inline__ void MyUnionXDataRefList_delAndSetNull(void *ptr)
{
	MyUnionXDataRefList **p = (MyUnionXDataRefList **)ptr;
	if (p != NULL) { MyUnionXDataRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataRefListA_dump(MyUnionXDataRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataRefListA_fdump(FILE *fp, MyUnionXDataRefList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataRefListW_dump(MyUnionXDataRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataRefListW_fdump(FILE *fp, MyUnionXDataRefList *p, int tab);
#ifdef UNICODE
#define MyUnionXDataRefList_dump MyUnionXDataRefListW_dump
#define MyUnionXDataRefList_fdump MyUnionXDataRefListW_fdump
#else //  UNICODE
#define MyUnionXDataRefList_dump MyUnionXDataRefListA_dump
#define MyUnionXDataRefList_fdump MyUnionXDataRefListA_fdump
#endif //  UNICODE
static __inline__ void MyUnionXDataRefListX_dump(MyUnionXDataRefList *p, int tab) { DZ1_DUMP(MyUnionXDataRefList, p, tab); }
static __inline__ void MyUnionXDataRefListX_fdump(FILE *fp, MyUnionXDataRefList *p, int tab) { DZ1_FDUMP(fp, MyUnionXDataRefList, p, tab); }
#else // UNIX_SYSTEM
#define MyUnionXDataRefList_dump MyUnionXDataRefListA_dump
#define MyUnionXDataRefListX_dump MyUnionXDataRefListA_dump
#define MyUnionXDataRefList_fdump MyUnionXDataRefListA_fdump
#define MyUnionXDataRefListX_fdump MyUnionXDataRefListA_fdump
#endif // UNIX_SYSTEM

// MyUnionXDataRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionXDataInfo
typedef struct MyUnionXDataInfo
{
	MyUnionXData	**obj_ptr_arr;
	u32_t			  obj_ptr_cnt;
	MyUnionXData	 *obj_arr;
	u32_t			  obj_cnt;
	u64_t			 *prims_arr;
	u32_t			  prims_cnt;
	u64_t			**primptrs_arr;
	u32_t			  primptrs_cnt;
	s32_t			 *i_val;
} MyUnionXDataInfo;

DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataInfo *MyUnionXDataInfo_new(MyUnionXData **obj_ptr_arr_e_clone, 
															   u32_t obj_ptr_cnt, 
															   MyUnionXData *obj_arr_e_copy, 
															   u32_t obj_cnt, 
															   u64_t *prims_arr_e_copy, 
															   u32_t prims_cnt, 
															   u64_t **primptrs_arr_e_clone, 
															   u32_t primptrs_cnt, 
															   s32_t *i_val_ref, Dz1Error *err);
static __inline__ MyUnionXDataInfo *MyUnionXDataInfo_gen(Dz1Error *err) { return MyUnionXDataInfo_new(NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyUnionXDataInfo_copy(MyUnionXDataInfo *dst, MyUnionXDataInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnionXDataInfo *MyUnionXDataInfo_clone(MyUnionXDataInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataInfo_purge(MyUnionXDataInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataInfo_del(MyUnionXDataInfo *p);
static __inline__ void MyUnionXDataInfo_delAndSetNull(void *ptr)
{
	MyUnionXDataInfo **p = (MyUnionXDataInfo **)ptr;
	if (p) { MyUnionXDataInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataInfo_dump(MyUnionXDataInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionXDataInfo_fdump(FILE *fp, MyUnionXDataInfo *p, int tab);
// MyUnionXDataInfo
////////////////////////////////////////////////////////////////////////////////

#endif
