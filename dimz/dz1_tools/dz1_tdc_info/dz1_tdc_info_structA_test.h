#ifndef _DZ1_TDC_DZ1_TDC_INFO_STRUCT_A_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_STRUCT_A_TEST_H_

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
// MyDataEntryA
typedef struct MyDataEntryA
{
	str_t		name;
	u32_t		val;
} MyDataEntryA;

DZ1_CPPLINK DZ1_DLLPORT MyDataEntryA *MyDataEntryA_new(str_t name, u32_t val, Dz1Error *err);
static __inline__ MyDataEntryA *MyDataEntryA_gen(Dz1Error *err) { return MyDataEntryA_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyDataEntryA_copy(MyDataEntryA *dst, MyDataEntryA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyDataEntryA *MyDataEntryA_clone(MyDataEntryA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntryA_purge(MyDataEntryA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntryA_del(MyDataEntryA *p);
static __inline__ void MyDataEntryA_delAndSetNull(void *ptr)
{
	MyDataEntryA **p = (MyDataEntryA **)ptr;
	if (p) { MyDataEntryA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntryA_dump(MyDataEntryA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntryA_fdump(FILE *fp, MyDataEntryA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyDataEntryA_cmp(MyDataEntryA *a, MyDataEntryA *b); 
// MyDataEntryA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueListA
typedef struct MyDataUniqueListA
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueListA *p);
	Dz1Error (*travel)(struct MyDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataUniqueListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueListA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataUniqueListA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataUniqueListA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataUniqueListA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataUniqueListA *p);
	MyDataEntryA *(*getTail)(struct MyDataUniqueListA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataUniqueListA;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueListA *MyDataUniqueListA_new(Dz1Error *err);
static __inline__ MyDataUniqueListA *MyDataUniqueListA_gen(Dz1Error *err) { return MyDataUniqueListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueListA *MyDataUniqueListA_clone(MyDataUniqueListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueListA_purge(MyDataUniqueListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueListA_del(MyDataUniqueListA *p);
static __inline__ void MyDataUniqueListA_delAndSetNull(void *ptr)
{
	MyDataUniqueListA **p = (MyDataUniqueListA **)ptr;
	if (p != NULL) { MyDataUniqueListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueListA_dump(MyDataUniqueListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueListA_fdump(FILE *fp, MyDataUniqueListA *p, int tab);

// MyDataUniqueListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefListA
typedef struct MyDataUniqueRefListA
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueRefListA *p);
	Dz1Error (*travel)(struct MyDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataUniqueRefListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueRefListA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataUniqueRefListA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataUniqueRefListA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataUniqueRefListA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataUniqueRefListA *p);
	MyDataEntryA *(*getTail)(struct MyDataUniqueRefListA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataUniqueRefListA;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefListA *MyDataUniqueRefListA_new(Dz1Error *err);
static __inline__ MyDataUniqueRefListA *MyDataUniqueRefListA_gen(Dz1Error *err) { return MyDataUniqueRefListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefListA *MyDataUniqueRefListA_clone(MyDataUniqueRefListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefListA_purge(MyDataUniqueRefListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefListA_del(MyDataUniqueRefListA *p);
static __inline__ void MyDataUniqueRefListA_delAndSetNull(void *ptr)
{
	MyDataUniqueRefListA **p = (MyDataUniqueRefListA **)ptr;
	if (p != NULL) { MyDataUniqueRefListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefListA_dump(MyDataUniqueRefListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefListA_fdump(FILE *fp, MyDataUniqueRefListA *p, int tab);

// MyDataUniqueRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedListA
typedef struct MyDataOrderedListA
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedListA *p);
	Dz1Error (*travel)(struct MyDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataOrderedListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedListA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataOrderedListA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataOrderedListA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataOrderedListA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataOrderedListA *p);
	MyDataEntryA *(*getTail)(struct MyDataOrderedListA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataOrderedListA;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedListA *MyDataOrderedListA_new(Dz1Error *err);
static __inline__ MyDataOrderedListA *MyDataOrderedListA_gen(Dz1Error *err) { return MyDataOrderedListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedListA *MyDataOrderedListA_clone(MyDataOrderedListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedListA_purge(MyDataOrderedListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedListA_del(MyDataOrderedListA *p);
static __inline__ void MyDataOrderedListA_delAndSetNull(void *ptr)
{
	MyDataOrderedListA **p = (MyDataOrderedListA **)ptr;
	if (p != NULL) { MyDataOrderedListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedListA_dump(MyDataOrderedListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedListA_fdump(FILE *fp, MyDataOrderedListA *p, int tab);

// MyDataOrderedListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefListA
typedef struct MyDataOrderedRefListA
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedRefListA *p);
	Dz1Error (*travel)(struct MyDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataOrderedRefListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedRefListA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataOrderedRefListA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataOrderedRefListA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataOrderedRefListA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataOrderedRefListA *p);
	MyDataEntryA *(*getTail)(struct MyDataOrderedRefListA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataOrderedRefListA;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefListA *MyDataOrderedRefListA_new(Dz1Error *err);
static __inline__ MyDataOrderedRefListA *MyDataOrderedRefListA_gen(Dz1Error *err) { return MyDataOrderedRefListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefListA *MyDataOrderedRefListA_clone(MyDataOrderedRefListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefListA_purge(MyDataOrderedRefListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefListA_del(MyDataOrderedRefListA *p);
static __inline__ void MyDataOrderedRefListA_delAndSetNull(void *ptr)
{
	MyDataOrderedRefListA **p = (MyDataOrderedRefListA **)ptr;
	if (p != NULL) { MyDataOrderedRefListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefListA_dump(MyDataOrderedRefListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefListA_fdump(FILE *fp, MyDataOrderedRefListA *p, int tab);

// MyDataOrderedRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataListA
typedef struct MyDataListA
{
	void *storage;
	unsigned int (*count)(struct MyDataListA *p);
	Dz1Error (*travel)(struct MyDataListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataListA *p, MyDataEntryA *data);
	MyDataEntryA *(*extract)(struct MyDataListA *p, MyDataEntryA *ptr);
	MyDataEntryA *(*find)(struct MyDataListA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataListA *p);
	MyDataEntryA *(*getTail)(struct MyDataListA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataListA;

DZ1_CPPLINK DZ1_DLLPORT MyDataListA *MyDataListA_new(Dz1Error *err);
static __inline__ MyDataListA *MyDataListA_gen(Dz1Error *err) { return MyDataListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataListA *MyDataListA_clone(MyDataListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataListA_purge(MyDataListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataListA_del(MyDataListA *p);
static __inline__ void MyDataListA_delAndSetNull(void *ptr)
{
	MyDataListA **p = (MyDataListA **)ptr;
	if (p != NULL) { MyDataListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataListA_dump(MyDataListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataListA_fdump(FILE *fp, MyDataListA *p, int tab);

// MyDataListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefListA
typedef struct MyDataRefListA
{
	void *storage;
	unsigned int (*count)(struct MyDataRefListA *p);
	Dz1Error (*travel)(struct MyDataRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataRefListA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataRefListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataRefListA *p, MyDataEntryA *data);
	MyDataEntryA *(*extract)(struct MyDataRefListA *p, MyDataEntryA *ptr);
	MyDataEntryA *(*find)(struct MyDataRefListA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataRefListA *p);
	MyDataEntryA *(*getTail)(struct MyDataRefListA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataRefListA;

DZ1_CPPLINK DZ1_DLLPORT MyDataRefListA *MyDataRefListA_new(Dz1Error *err);
static __inline__ MyDataRefListA *MyDataRefListA_gen(Dz1Error *err) { return MyDataRefListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataRefListA *MyDataRefListA_clone(MyDataRefListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefListA_purge(MyDataRefListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefListA_del(MyDataRefListA *p);
static __inline__ void MyDataRefListA_delAndSetNull(void *ptr)
{
	MyDataRefListA **p = (MyDataRefListA **)ptr;
	if (p != NULL) { MyDataRefListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefListA_dump(MyDataRefListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefListA_fdump(FILE *fp, MyDataRefListA *p, int tab);

// MyDataRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueArrayA
typedef struct MyDataUniqueArrayA
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueArrayA *p);
	Dz1Error (*travel)(struct MyDataUniqueArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataUniqueArrayA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueArrayA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataUniqueArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataUniqueArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataUniqueArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataUniqueArrayA *p);
	MyDataEntryA *(*getTail)(struct MyDataUniqueArrayA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataUniqueArrayA;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueArrayA *MyDataUniqueArrayA_new(Dz1Error *err);
static __inline__ MyDataUniqueArrayA *MyDataUniqueArrayA_gen(Dz1Error *err) { return MyDataUniqueArrayA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueArrayA *MyDataUniqueArrayA_clone(MyDataUniqueArrayA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueArrayA_purge(MyDataUniqueArrayA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueArrayA_del(MyDataUniqueArrayA *p);
static __inline__ void MyDataUniqueArrayA_delAndSetNull(void *ptr)
{
	MyDataUniqueArrayA **p = (MyDataUniqueArrayA **)ptr;
	if (p != NULL) { MyDataUniqueArrayA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueArrayA_dump(MyDataUniqueArrayA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueArrayA_fdump(FILE *fp, MyDataUniqueArrayA *p, int tab);

// MyDataUniqueArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefArrayA
typedef struct MyDataUniqueRefArrayA
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueRefArrayA *p);
	Dz1Error (*travel)(struct MyDataUniqueRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataUniqueRefArrayA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueRefArrayA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataUniqueRefArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataUniqueRefArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataUniqueRefArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataUniqueRefArrayA *p);
	MyDataEntryA *(*getTail)(struct MyDataUniqueRefArrayA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataUniqueRefArrayA;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefArrayA *MyDataUniqueRefArrayA_new(Dz1Error *err);
static __inline__ MyDataUniqueRefArrayA *MyDataUniqueRefArrayA_gen(Dz1Error *err) { return MyDataUniqueRefArrayA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefArrayA *MyDataUniqueRefArrayA_clone(MyDataUniqueRefArrayA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefArrayA_purge(MyDataUniqueRefArrayA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefArrayA_del(MyDataUniqueRefArrayA *p);
static __inline__ void MyDataUniqueRefArrayA_delAndSetNull(void *ptr)
{
	MyDataUniqueRefArrayA **p = (MyDataUniqueRefArrayA **)ptr;
	if (p != NULL) { MyDataUniqueRefArrayA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefArrayA_dump(MyDataUniqueRefArrayA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefArrayA_fdump(FILE *fp, MyDataUniqueRefArrayA *p, int tab);

// MyDataUniqueRefArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedArrayA
typedef struct MyDataOrderedArrayA
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedArrayA *p);
	Dz1Error (*travel)(struct MyDataOrderedArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataOrderedArrayA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedArrayA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataOrderedArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataOrderedArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataOrderedArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataOrderedArrayA *p);
	MyDataEntryA *(*getTail)(struct MyDataOrderedArrayA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataOrderedArrayA;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedArrayA *MyDataOrderedArrayA_new(Dz1Error *err);
static __inline__ MyDataOrderedArrayA *MyDataOrderedArrayA_gen(Dz1Error *err) { return MyDataOrderedArrayA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedArrayA *MyDataOrderedArrayA_clone(MyDataOrderedArrayA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedArrayA_purge(MyDataOrderedArrayA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedArrayA_del(MyDataOrderedArrayA *p);
static __inline__ void MyDataOrderedArrayA_delAndSetNull(void *ptr)
{
	MyDataOrderedArrayA **p = (MyDataOrderedArrayA **)ptr;
	if (p != NULL) { MyDataOrderedArrayA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedArrayA_dump(MyDataOrderedArrayA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedArrayA_fdump(FILE *fp, MyDataOrderedArrayA *p, int tab);

// MyDataOrderedArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefArrayA
typedef struct MyDataOrderedRefArrayA
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedRefArrayA *p);
	Dz1Error (*travel)(struct MyDataOrderedRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataOrderedRefArrayA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedRefArrayA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataOrderedRefArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataOrderedRefArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataOrderedRefArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataOrderedRefArrayA *p);
	MyDataEntryA *(*getTail)(struct MyDataOrderedRefArrayA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataOrderedRefArrayA;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefArrayA *MyDataOrderedRefArrayA_new(Dz1Error *err);
static __inline__ MyDataOrderedRefArrayA *MyDataOrderedRefArrayA_gen(Dz1Error *err) { return MyDataOrderedRefArrayA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefArrayA *MyDataOrderedRefArrayA_clone(MyDataOrderedRefArrayA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefArrayA_purge(MyDataOrderedRefArrayA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefArrayA_del(MyDataOrderedRefArrayA *p);
static __inline__ void MyDataOrderedRefArrayA_delAndSetNull(void *ptr)
{
	MyDataOrderedRefArrayA **p = (MyDataOrderedRefArrayA **)ptr;
	if (p != NULL) { MyDataOrderedRefArrayA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefArrayA_dump(MyDataOrderedRefArrayA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefArrayA_fdump(FILE *fp, MyDataOrderedRefArrayA *p, int tab);

// MyDataOrderedRefArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataArrayA
typedef struct MyDataArrayA
{
	void *storage;
	unsigned int (*count)(struct MyDataArrayA *p);
	Dz1Error (*travel)(struct MyDataArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataArrayA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataArrayA *p, MyDataEntryA *data);
	MyDataEntryA *(*extract)(struct MyDataArrayA *p, MyDataEntryA *ptr);
	MyDataEntryA *(*find)(struct MyDataArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataArrayA *p);
	MyDataEntryA *(*getTail)(struct MyDataArrayA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataArrayA;

DZ1_CPPLINK DZ1_DLLPORT MyDataArrayA *MyDataArrayA_new(Dz1Error *err);
static __inline__ MyDataArrayA *MyDataArrayA_gen(Dz1Error *err) { return MyDataArrayA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataArrayA *MyDataArrayA_clone(MyDataArrayA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataArrayA_purge(MyDataArrayA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataArrayA_del(MyDataArrayA *p);
static __inline__ void MyDataArrayA_delAndSetNull(void *ptr)
{
	MyDataArrayA **p = (MyDataArrayA **)ptr;
	if (p != NULL) { MyDataArrayA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataArrayA_dump(MyDataArrayA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataArrayA_fdump(FILE *fp, MyDataArrayA *p, int tab);

// MyDataArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefArrayA
typedef struct MyDataRefArrayA
{
	void *storage;
	unsigned int (*count)(struct MyDataRefArrayA *p);
	Dz1Error (*travel)(struct MyDataRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataRefArrayA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataRefArrayA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataRefArrayA *p, MyDataEntryA *data);
	MyDataEntryA *(*extract)(struct MyDataRefArrayA *p, MyDataEntryA *ptr);
	MyDataEntryA *(*find)(struct MyDataRefArrayA *p, MyDataEntryA *key);
	MyDataEntryA *(*getHead)(struct MyDataRefArrayA *p);
	MyDataEntryA *(*getTail)(struct MyDataRefArrayA *p);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataRefArrayA;

DZ1_CPPLINK DZ1_DLLPORT MyDataRefArrayA *MyDataRefArrayA_new(Dz1Error *err);
static __inline__ MyDataRefArrayA *MyDataRefArrayA_gen(Dz1Error *err) { return MyDataRefArrayA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataRefArrayA *MyDataRefArrayA_clone(MyDataRefArrayA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefArrayA_purge(MyDataRefArrayA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefArrayA_del(MyDataRefArrayA *p);
static __inline__ void MyDataRefArrayA_delAndSetNull(void *ptr)
{
	MyDataRefArrayA **p = (MyDataRefArrayA **)ptr;
	if (p != NULL) { MyDataRefArrayA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefArrayA_dump(MyDataRefArrayA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefArrayA_fdump(FILE *fp, MyDataRefArrayA *p, int tab);

// MyDataRefArrayA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataIndexA
typedef struct MyDataIndexA
{
	void *storage;
	unsigned int (*count)(struct MyDataIndexA *p);
	Dz1Error (*travel)(struct MyDataIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataIndexA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataIndexA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataIndexA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataIndexA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataIndexA *p, MyDataEntryA *key);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataIndexA;

DZ1_CPPLINK DZ1_DLLPORT MyDataIndexA *MyDataIndexA_new(Dz1Error *err);
static __inline__ MyDataIndexA *MyDataIndexA_gen(Dz1Error *err) { return MyDataIndexA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataIndexA *MyDataIndexA_clone(MyDataIndexA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndexA_purge(MyDataIndexA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndexA_del(MyDataIndexA *p);
static __inline__ void MyDataIndexA_delAndSetNull(void *ptr)
{
	MyDataIndexA **p = (MyDataIndexA **)ptr;
	if (p != NULL) { MyDataIndexA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndexA_dump(MyDataIndexA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndexA_fdump(FILE *fp, MyDataIndexA *p, int tab);

// MyDataIndexA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyDataRefIndexA
typedef struct MyDataRefIndexA
{
	void *storage;
	unsigned int (*count)(struct MyDataRefIndexA *p);
	Dz1Error (*travel)(struct MyDataRefIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataRefIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataRefIndexA *p, Dz1Error (*func)(void *ptr, MyDataEntryA *entry), void *ptr);
	MyDataEntryA **(*get_array)(struct MyDataRefIndexA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataRefIndexA *p, MyDataEntryA *data);
	bool_t (*remove)(struct MyDataRefIndexA *p, MyDataEntryA *key);
	MyDataEntryA *(*extract)(struct MyDataRefIndexA *p, MyDataEntryA *key);
	MyDataEntryA *(*find)(struct MyDataRefIndexA *p, MyDataEntryA *key);
	int (*cmp)(MyDataEntryA *a, MyDataEntryA *b);
} MyDataRefIndexA;

DZ1_CPPLINK DZ1_DLLPORT MyDataRefIndexA *MyDataRefIndexA_new(Dz1Error *err);
static __inline__ MyDataRefIndexA *MyDataRefIndexA_gen(Dz1Error *err) { return MyDataRefIndexA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataRefIndexA *MyDataRefIndexA_clone(MyDataRefIndexA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndexA_purge(MyDataRefIndexA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndexA_del(MyDataRefIndexA *p);
static __inline__ void MyDataRefIndexA_delAndSetNull(void *ptr)
{
	MyDataRefIndexA **p = (MyDataRefIndexA **)ptr;
	if (p != NULL) { MyDataRefIndexA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndexA_dump(MyDataRefIndexA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndexA_fdump(FILE *fp, MyDataRefIndexA *p, int tab);

// MyDataRefIndexA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberTypeA
typedef struct ArrayMemberTypeA
{
	MyDataEntryA	**obj_ptr_arr;
	u32_t			  obj_ptr_cnt;
	MyDataEntryA	 *obj_arr;
	u32_t			  obj_cnt;
	u64_t			 *prims_arr;
	u32_t			  prims_cnt;
	u64_t			**primptrs_arr;
	u32_t			  primptrs_cnt;
	str_t			 *str_arr;
	u32_t			  str_cnt;
	s32_t			 *i_val;
} ArrayMemberTypeA;

DZ1_CPPLINK DZ1_DLLPORT ArrayMemberTypeA *ArrayMemberTypeA_new(MyDataEntryA **obj_ptr_arr_e_clone, 
															   u32_t obj_ptr_cnt, 
															   MyDataEntryA *obj_arr_e_copy, 
															   u32_t obj_cnt, 
															   u64_t *prims_arr_e_copy, 
															   u32_t prims_cnt, 
															   u64_t **primptrs_arr_e_clone, 
															   u32_t primptrs_cnt, 
															   str_t *str_arr_e_clone, 
															   u32_t str_cnt, 
															   s32_t *i_val_ref, Dz1Error *err);
static __inline__ ArrayMemberTypeA *ArrayMemberTypeA_gen(Dz1Error *err) { return ArrayMemberTypeA_new(NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ArrayMemberTypeA_copy(ArrayMemberTypeA *dst, ArrayMemberTypeA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberTypeA *ArrayMemberTypeA_clone(ArrayMemberTypeA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberTypeA_purge(ArrayMemberTypeA *p);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberTypeA_del(ArrayMemberTypeA *p);
static __inline__ void ArrayMemberTypeA_delAndSetNull(void *ptr)
{
	ArrayMemberTypeA **p = (ArrayMemberTypeA **)ptr;
	if (p) { ArrayMemberTypeA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberTypeA_dump(ArrayMemberTypeA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberTypeA_fdump(FILE *fp, ArrayMemberTypeA *p, int tab);
// ArrayMemberTypeA
////////////////////////////////////////////////////////////////////////////////

#endif
