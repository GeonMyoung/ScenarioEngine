#ifndef _DZ1_TDC_DZ1_TDC_INFO_STRUCT_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_STRUCT_TEST_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"
#include "dz1_tdc_info_test_types.h"

////////////////////////////////////////////////////////////////////////////////
// TestExternalType
struct TestExternalType;
// TestExternalType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// _declare_MyDataEntry
struct MyDataEntry;
// _declare_MyDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataInfo
struct MyDataInfo;
struct MyDataEntry;
struct TestExternalType;

typedef struct MyDataInfo
{
	struct MyDataInfo			*next;
	struct MyDataEntry			*data;
	struct TestExternalType		*opt;
	TestTypeInfo				 info1;
	TestTypeInfo				*info2;
	TestTypeInfo				*info3;
} MyDataInfo;

DZ1_CPPLINK DZ1_DLLPORT MyDataInfo *MyDataInfo_new(struct MyDataInfo *next_ref, 
												   struct MyDataEntry *data, 
												   struct TestExternalType *opt, 
												   TestTypeInfo *info1, 
												   TestTypeInfo *info2, 
												   TestTypeInfo *info3_ref, Dz1Error *err);
static __inline__ MyDataInfo *MyDataInfo_gen(Dz1Error *err) { return MyDataInfo_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyDataInfo_copy(MyDataInfo *dst, MyDataInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyDataInfo *MyDataInfo_clone(MyDataInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataInfo_purge(MyDataInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataInfo_del(MyDataInfo *p);
static __inline__ void MyDataInfo_delAndSetNull(void *ptr)
{
	MyDataInfo **p = (MyDataInfo **)ptr;
	if (p) { MyDataInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataInfo_dump(MyDataInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataInfo_fdump(FILE *fp, MyDataInfo *p, int tab);
// MyDataInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataEntry
typedef struct MyDataEntry
{
	Dz1Asn1UTF8Str		*name;
	u32_t				 val;
} MyDataEntry;

DZ1_CPPLINK DZ1_DLLPORT MyDataEntry *MyDataEntry_new(Dz1Asn1UTF8Str *name, 
													 u32_t val, Dz1Error *err);
static __inline__ MyDataEntry *MyDataEntry_gen(Dz1Error *err) { return MyDataEntry_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyDataEntry_copy(MyDataEntry *dst, MyDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyDataEntry *MyDataEntry_clone(MyDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntry_purge(MyDataEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntry_del(MyDataEntry *p);
static __inline__ void MyDataEntry_delAndSetNull(void *ptr)
{
	MyDataEntry **p = (MyDataEntry **)ptr;
	if (p) { MyDataEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntry_dump(MyDataEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntry_fdump(FILE *fp, MyDataEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyDataEntry_cmp(MyDataEntry *a, MyDataEntry *b); 
// MyDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueList
typedef struct MyDataUniqueList
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueList *p);
	Dz1Error (*travel)(struct MyDataUniqueList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	MyDataEntry **(*get_array)(struct MyDataUniqueList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueList *p, MyDataEntry *data);
	bool_t (*remove)(struct MyDataUniqueList *p, MyDataEntry *key);
	MyDataEntry *(*extract)(struct MyDataUniqueList *p, MyDataEntry *key);
	MyDataEntry *(*find)(struct MyDataUniqueList *p, MyDataEntry *key);
	MyDataEntry *(*getHead)(struct MyDataUniqueList *p);
	MyDataEntry *(*getTail)(struct MyDataUniqueList *p);
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataUniqueList;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueList *MyDataUniqueList_new(Dz1Error *err);
static __inline__ MyDataUniqueList *MyDataUniqueList_gen(Dz1Error *err) { return MyDataUniqueList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueList *MyDataUniqueList_clone(MyDataUniqueList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueList_purge(MyDataUniqueList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueList_del(MyDataUniqueList *p);
static __inline__ void MyDataUniqueList_delAndSetNull(void *ptr)
{
	MyDataUniqueList **p = (MyDataUniqueList **)ptr;
	if (p != NULL) { MyDataUniqueList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueList_dump(MyDataUniqueList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueList_fdump(FILE *fp, MyDataUniqueList *p, int tab);

// MyDataUniqueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedList
typedef struct MyDataOrderedList
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedList *p);
	Dz1Error (*travel)(struct MyDataOrderedList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	MyDataEntry **(*get_array)(struct MyDataOrderedList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedList *p, MyDataEntry *data);
	bool_t (*remove)(struct MyDataOrderedList *p, MyDataEntry *key);
	MyDataEntry *(*extract)(struct MyDataOrderedList *p, MyDataEntry *key);
	MyDataEntry *(*find)(struct MyDataOrderedList *p, MyDataEntry *key);
	MyDataEntry *(*getHead)(struct MyDataOrderedList *p);
	MyDataEntry *(*getTail)(struct MyDataOrderedList *p);
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataOrderedList;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedList *MyDataOrderedList_new(Dz1Error *err);
static __inline__ MyDataOrderedList *MyDataOrderedList_gen(Dz1Error *err) { return MyDataOrderedList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedList *MyDataOrderedList_clone(MyDataOrderedList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedList_purge(MyDataOrderedList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedList_del(MyDataOrderedList *p);
static __inline__ void MyDataOrderedList_delAndSetNull(void *ptr)
{
	MyDataOrderedList **p = (MyDataOrderedList **)ptr;
	if (p != NULL) { MyDataOrderedList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedList_dump(MyDataOrderedList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedList_fdump(FILE *fp, MyDataOrderedList *p, int tab);

// MyDataOrderedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataList
typedef struct MyDataList
{
	void *storage;
	unsigned int (*count)(struct MyDataList *p);
	Dz1Error (*travel)(struct MyDataList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	MyDataEntry **(*get_array)(struct MyDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataList *p, MyDataEntry *data);
	bool_t (*remove)(struct MyDataList *p, MyDataEntry *ptr);
	MyDataEntry *(*extract)(struct MyDataList *p, MyDataEntry *ptr);
	MyDataEntry *(*find)(struct MyDataList *p, MyDataEntry *key);
	MyDataEntry *(*getHead)(struct MyDataList *p);
	MyDataEntry *(*getTail)(struct MyDataList *p);
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataList;

DZ1_CPPLINK DZ1_DLLPORT MyDataList *MyDataList_new(Dz1Error *err);
static __inline__ MyDataList *MyDataList_gen(Dz1Error *err) { return MyDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataList *MyDataList_clone(MyDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataList_purge(MyDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataList_del(MyDataList *p);
static __inline__ void MyDataList_delAndSetNull(void *ptr)
{
	MyDataList **p = (MyDataList **)ptr;
	if (p != NULL) { MyDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataList_dump(MyDataList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataList_fdump(FILE *fp, MyDataList *p, int tab);

// MyDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefList
typedef struct MyDataUniqueRefList
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueRefList *p);
	Dz1Error (*travel)(struct MyDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	MyDataEntry **(*get_array)(struct MyDataUniqueRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueRefList *p, MyDataEntry *data);
	bool_t (*remove)(struct MyDataUniqueRefList *p, MyDataEntry *key);
	MyDataEntry *(*extract)(struct MyDataUniqueRefList *p, MyDataEntry *key);
	MyDataEntry *(*find)(struct MyDataUniqueRefList *p, MyDataEntry *key);
	MyDataEntry *(*getHead)(struct MyDataUniqueRefList *p);
	MyDataEntry *(*getTail)(struct MyDataUniqueRefList *p);
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataUniqueRefList;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefList *MyDataUniqueRefList_new(Dz1Error *err);
static __inline__ MyDataUniqueRefList *MyDataUniqueRefList_gen(Dz1Error *err) { return MyDataUniqueRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefList *MyDataUniqueRefList_clone(MyDataUniqueRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefList_purge(MyDataUniqueRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefList_del(MyDataUniqueRefList *p);
static __inline__ void MyDataUniqueRefList_delAndSetNull(void *ptr)
{
	MyDataUniqueRefList **p = (MyDataUniqueRefList **)ptr;
	if (p != NULL) { MyDataUniqueRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefList_dump(MyDataUniqueRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefList_fdump(FILE *fp, MyDataUniqueRefList *p, int tab);

// MyDataUniqueRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefList
typedef struct MyDataOrderedRefList
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedRefList *p);
	Dz1Error (*travel)(struct MyDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	MyDataEntry **(*get_array)(struct MyDataOrderedRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedRefList *p, MyDataEntry *data);
	bool_t (*remove)(struct MyDataOrderedRefList *p, MyDataEntry *key);
	MyDataEntry *(*extract)(struct MyDataOrderedRefList *p, MyDataEntry *key);
	MyDataEntry *(*find)(struct MyDataOrderedRefList *p, MyDataEntry *key);
	MyDataEntry *(*getHead)(struct MyDataOrderedRefList *p);
	MyDataEntry *(*getTail)(struct MyDataOrderedRefList *p);
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataOrderedRefList;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefList *MyDataOrderedRefList_new(Dz1Error *err);
static __inline__ MyDataOrderedRefList *MyDataOrderedRefList_gen(Dz1Error *err) { return MyDataOrderedRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefList *MyDataOrderedRefList_clone(MyDataOrderedRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefList_purge(MyDataOrderedRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefList_del(MyDataOrderedRefList *p);
static __inline__ void MyDataOrderedRefList_delAndSetNull(void *ptr)
{
	MyDataOrderedRefList **p = (MyDataOrderedRefList **)ptr;
	if (p != NULL) { MyDataOrderedRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefList_dump(MyDataOrderedRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefList_fdump(FILE *fp, MyDataOrderedRefList *p, int tab);

// MyDataOrderedRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefList
typedef struct MyDataRefList
{
	void *storage;
	unsigned int (*count)(struct MyDataRefList *p);
	Dz1Error (*travel)(struct MyDataRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataRefList *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	MyDataEntry **(*get_array)(struct MyDataRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataRefList *p, MyDataEntry *data);
	bool_t (*remove)(struct MyDataRefList *p, MyDataEntry *ptr);
	MyDataEntry *(*extract)(struct MyDataRefList *p, MyDataEntry *ptr);
	MyDataEntry *(*find)(struct MyDataRefList *p, MyDataEntry *key);
	MyDataEntry *(*getHead)(struct MyDataRefList *p);
	MyDataEntry *(*getTail)(struct MyDataRefList *p);
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataRefList;

DZ1_CPPLINK DZ1_DLLPORT MyDataRefList *MyDataRefList_new(Dz1Error *err);
static __inline__ MyDataRefList *MyDataRefList_gen(Dz1Error *err) { return MyDataRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataRefList *MyDataRefList_clone(MyDataRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefList_purge(MyDataRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefList_del(MyDataRefList *p);
static __inline__ void MyDataRefList_delAndSetNull(void *ptr)
{
	MyDataRefList **p = (MyDataRefList **)ptr;
	if (p != NULL) { MyDataRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefList_dump(MyDataRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefList_fdump(FILE *fp, MyDataRefList *p, int tab);

// MyDataRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataIndex
typedef struct MyDataIndex
{
	void *storage;
	unsigned int (*count)(struct MyDataIndex *p);
	Dz1Error (*travel)(struct MyDataIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	MyDataEntry **(*get_array)(struct MyDataIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataIndex *p, MyDataEntry *data);
	bool_t (*remove)(struct MyDataIndex *p, MyDataEntry *key);
	MyDataEntry *(*extract)(struct MyDataIndex *p, MyDataEntry *key);
	MyDataEntry *(*find)(struct MyDataIndex *p, MyDataEntry *key);
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataIndex;

DZ1_CPPLINK DZ1_DLLPORT MyDataIndex *MyDataIndex_new(Dz1Error *err);
static __inline__ MyDataIndex *MyDataIndex_gen(Dz1Error *err) { return MyDataIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataIndex *MyDataIndex_clone(MyDataIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndex_purge(MyDataIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndex_del(MyDataIndex *p);
static __inline__ void MyDataIndex_delAndSetNull(void *ptr)
{
	MyDataIndex **p = (MyDataIndex **)ptr;
	if (p != NULL) { MyDataIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndex_dump(MyDataIndex *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndex_fdump(FILE *fp, MyDataIndex *p, int tab);

// MyDataIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefIndex
typedef struct MyDataRefIndex
{
	void *storage;
	unsigned int (*count)(struct MyDataRefIndex *p);
	Dz1Error (*travel)(struct MyDataRefIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataRefIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataRefIndex *p, Dz1Error (*func)(void *ptr, MyDataEntry *entry), void *ptr);
	MyDataEntry **(*get_array)(struct MyDataRefIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataRefIndex *p, MyDataEntry *data);
	bool_t (*remove)(struct MyDataRefIndex *p, MyDataEntry *key);
	MyDataEntry *(*extract)(struct MyDataRefIndex *p, MyDataEntry *key);
	MyDataEntry *(*find)(struct MyDataRefIndex *p, MyDataEntry *key);
	int (*cmp)(MyDataEntry *a, MyDataEntry *b);
} MyDataRefIndex;

DZ1_CPPLINK DZ1_DLLPORT MyDataRefIndex *MyDataRefIndex_new(Dz1Error *err);
static __inline__ MyDataRefIndex *MyDataRefIndex_gen(Dz1Error *err) { return MyDataRefIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataRefIndex *MyDataRefIndex_clone(MyDataRefIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndex_purge(MyDataRefIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndex_del(MyDataRefIndex *p);
static __inline__ void MyDataRefIndex_delAndSetNull(void *ptr)
{
	MyDataRefIndex **p = (MyDataRefIndex **)ptr;
	if (p != NULL) { MyDataRefIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndex_dump(MyDataRefIndex *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndex_fdump(FILE *fp, MyDataRefIndex *p, int tab);

// MyDataRefIndex
////////////////////////////////////////////////////////////////////////////////

#endif
