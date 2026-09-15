#ifndef _DZ1_TDC_DZ1_TDC_INFO_STRUCT_W_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_STRUCT_W_TEST_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataEntryW
typedef struct MyDataEntryW
{
	wstr_t		name;
	u32_t		val;
} MyDataEntryW;

DZ1_CPPLINK DZ1_DLLPORT MyDataEntryW *MyDataEntryW_new(wstr_t name, u32_t val, Dz1Error *err);
static __inline__ MyDataEntryW *MyDataEntryW_gen(Dz1Error *err) { return MyDataEntryW_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyDataEntryW_copy(MyDataEntryW *dst, MyDataEntryW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyDataEntryW *MyDataEntryW_clone(MyDataEntryW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntryW_purge(MyDataEntryW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntryW_del(MyDataEntryW *p);
static __inline__ void MyDataEntryW_delAndSetNull(void *ptr)
{
	MyDataEntryW **p = (MyDataEntryW **)ptr;
	if (p) { MyDataEntryW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntryW_dump(MyDataEntryW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataEntryW_fdump(FILE *fp, MyDataEntryW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyDataEntryW_cmp(MyDataEntryW *a, MyDataEntryW *b); 
// MyDataEntryW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueListW
typedef struct MyDataUniqueListW
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueListW *p);
	Dz1Error (*travel)(struct MyDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataUniqueListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueListW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataUniqueListW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataUniqueListW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataUniqueListW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataUniqueListW *p);
	MyDataEntryW *(*getTail)(struct MyDataUniqueListW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataUniqueListW;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueListW *MyDataUniqueListW_new(Dz1Error *err);
static __inline__ MyDataUniqueListW *MyDataUniqueListW_gen(Dz1Error *err) { return MyDataUniqueListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueListW *MyDataUniqueListW_clone(MyDataUniqueListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueListW_purge(MyDataUniqueListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueListW_del(MyDataUniqueListW *p);
static __inline__ void MyDataUniqueListW_delAndSetNull(void *ptr)
{
	MyDataUniqueListW **p = (MyDataUniqueListW **)ptr;
	if (p != NULL) { MyDataUniqueListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueListW_dump(MyDataUniqueListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueListW_fdump(FILE *fp, MyDataUniqueListW *p, int tab);

// MyDataUniqueListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefListW
typedef struct MyDataUniqueRefListW
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueRefListW *p);
	Dz1Error (*travel)(struct MyDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataUniqueRefListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueRefListW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataUniqueRefListW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataUniqueRefListW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataUniqueRefListW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataUniqueRefListW *p);
	MyDataEntryW *(*getTail)(struct MyDataUniqueRefListW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataUniqueRefListW;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefListW *MyDataUniqueRefListW_new(Dz1Error *err);
static __inline__ MyDataUniqueRefListW *MyDataUniqueRefListW_gen(Dz1Error *err) { return MyDataUniqueRefListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefListW *MyDataUniqueRefListW_clone(MyDataUniqueRefListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefListW_purge(MyDataUniqueRefListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefListW_del(MyDataUniqueRefListW *p);
static __inline__ void MyDataUniqueRefListW_delAndSetNull(void *ptr)
{
	MyDataUniqueRefListW **p = (MyDataUniqueRefListW **)ptr;
	if (p != NULL) { MyDataUniqueRefListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefListW_dump(MyDataUniqueRefListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefListW_fdump(FILE *fp, MyDataUniqueRefListW *p, int tab);

// MyDataUniqueRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedListW
typedef struct MyDataOrderedListW
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedListW *p);
	Dz1Error (*travel)(struct MyDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataOrderedListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedListW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataOrderedListW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataOrderedListW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataOrderedListW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataOrderedListW *p);
	MyDataEntryW *(*getTail)(struct MyDataOrderedListW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataOrderedListW;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedListW *MyDataOrderedListW_new(Dz1Error *err);
static __inline__ MyDataOrderedListW *MyDataOrderedListW_gen(Dz1Error *err) { return MyDataOrderedListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedListW *MyDataOrderedListW_clone(MyDataOrderedListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedListW_purge(MyDataOrderedListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedListW_del(MyDataOrderedListW *p);
static __inline__ void MyDataOrderedListW_delAndSetNull(void *ptr)
{
	MyDataOrderedListW **p = (MyDataOrderedListW **)ptr;
	if (p != NULL) { MyDataOrderedListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedListW_dump(MyDataOrderedListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedListW_fdump(FILE *fp, MyDataOrderedListW *p, int tab);

// MyDataOrderedListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefListW
typedef struct MyDataOrderedRefListW
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedRefListW *p);
	Dz1Error (*travel)(struct MyDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataOrderedRefListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedRefListW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataOrderedRefListW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataOrderedRefListW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataOrderedRefListW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataOrderedRefListW *p);
	MyDataEntryW *(*getTail)(struct MyDataOrderedRefListW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataOrderedRefListW;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefListW *MyDataOrderedRefListW_new(Dz1Error *err);
static __inline__ MyDataOrderedRefListW *MyDataOrderedRefListW_gen(Dz1Error *err) { return MyDataOrderedRefListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefListW *MyDataOrderedRefListW_clone(MyDataOrderedRefListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefListW_purge(MyDataOrderedRefListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefListW_del(MyDataOrderedRefListW *p);
static __inline__ void MyDataOrderedRefListW_delAndSetNull(void *ptr)
{
	MyDataOrderedRefListW **p = (MyDataOrderedRefListW **)ptr;
	if (p != NULL) { MyDataOrderedRefListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefListW_dump(MyDataOrderedRefListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefListW_fdump(FILE *fp, MyDataOrderedRefListW *p, int tab);

// MyDataOrderedRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataListW
typedef struct MyDataListW
{
	void *storage;
	unsigned int (*count)(struct MyDataListW *p);
	Dz1Error (*travel)(struct MyDataListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataListW *p, MyDataEntryW *data);
	MyDataEntryW *(*extract)(struct MyDataListW *p, MyDataEntryW *ptr);
	MyDataEntryW *(*find)(struct MyDataListW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataListW *p);
	MyDataEntryW *(*getTail)(struct MyDataListW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataListW;

DZ1_CPPLINK DZ1_DLLPORT MyDataListW *MyDataListW_new(Dz1Error *err);
static __inline__ MyDataListW *MyDataListW_gen(Dz1Error *err) { return MyDataListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataListW *MyDataListW_clone(MyDataListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataListW_purge(MyDataListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataListW_del(MyDataListW *p);
static __inline__ void MyDataListW_delAndSetNull(void *ptr)
{
	MyDataListW **p = (MyDataListW **)ptr;
	if (p != NULL) { MyDataListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataListW_dump(MyDataListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataListW_fdump(FILE *fp, MyDataListW *p, int tab);

// MyDataListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataRefListW
typedef struct MyDataRefListW
{
	void *storage;
	unsigned int (*count)(struct MyDataRefListW *p);
	Dz1Error (*travel)(struct MyDataRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataRefListW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataRefListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataRefListW *p, MyDataEntryW *data);
	MyDataEntryW *(*extract)(struct MyDataRefListW *p, MyDataEntryW *ptr);
	MyDataEntryW *(*find)(struct MyDataRefListW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataRefListW *p);
	MyDataEntryW *(*getTail)(struct MyDataRefListW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataRefListW;

DZ1_CPPLINK DZ1_DLLPORT MyDataRefListW *MyDataRefListW_new(Dz1Error *err);
static __inline__ MyDataRefListW *MyDataRefListW_gen(Dz1Error *err) { return MyDataRefListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataRefListW *MyDataRefListW_clone(MyDataRefListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefListW_purge(MyDataRefListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefListW_del(MyDataRefListW *p);
static __inline__ void MyDataRefListW_delAndSetNull(void *ptr)
{
	MyDataRefListW **p = (MyDataRefListW **)ptr;
	if (p != NULL) { MyDataRefListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefListW_dump(MyDataRefListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefListW_fdump(FILE *fp, MyDataRefListW *p, int tab);

// MyDataRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueArrayW
typedef struct MyDataUniqueArrayW
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueArrayW *p);
	Dz1Error (*travel)(struct MyDataUniqueArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataUniqueArrayW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueArrayW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataUniqueArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataUniqueArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataUniqueArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataUniqueArrayW *p);
	MyDataEntryW *(*getTail)(struct MyDataUniqueArrayW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataUniqueArrayW;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueArrayW *MyDataUniqueArrayW_new(Dz1Error *err);
static __inline__ MyDataUniqueArrayW *MyDataUniqueArrayW_gen(Dz1Error *err) { return MyDataUniqueArrayW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueArrayW *MyDataUniqueArrayW_clone(MyDataUniqueArrayW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueArrayW_purge(MyDataUniqueArrayW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueArrayW_del(MyDataUniqueArrayW *p);
static __inline__ void MyDataUniqueArrayW_delAndSetNull(void *ptr)
{
	MyDataUniqueArrayW **p = (MyDataUniqueArrayW **)ptr;
	if (p != NULL) { MyDataUniqueArrayW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueArrayW_dump(MyDataUniqueArrayW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueArrayW_fdump(FILE *fp, MyDataUniqueArrayW *p, int tab);

// MyDataUniqueArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataUniqueRefArrayW
typedef struct MyDataUniqueRefArrayW
{
	void *storage;
	unsigned int (*count)(struct MyDataUniqueRefArrayW *p);
	Dz1Error (*travel)(struct MyDataUniqueRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataUniqueRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataUniqueRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataUniqueRefArrayW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataUniqueRefArrayW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataUniqueRefArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataUniqueRefArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataUniqueRefArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataUniqueRefArrayW *p);
	MyDataEntryW *(*getTail)(struct MyDataUniqueRefArrayW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataUniqueRefArrayW;

DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefArrayW *MyDataUniqueRefArrayW_new(Dz1Error *err);
static __inline__ MyDataUniqueRefArrayW *MyDataUniqueRefArrayW_gen(Dz1Error *err) { return MyDataUniqueRefArrayW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataUniqueRefArrayW *MyDataUniqueRefArrayW_clone(MyDataUniqueRefArrayW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefArrayW_purge(MyDataUniqueRefArrayW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefArrayW_del(MyDataUniqueRefArrayW *p);
static __inline__ void MyDataUniqueRefArrayW_delAndSetNull(void *ptr)
{
	MyDataUniqueRefArrayW **p = (MyDataUniqueRefArrayW **)ptr;
	if (p != NULL) { MyDataUniqueRefArrayW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefArrayW_dump(MyDataUniqueRefArrayW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataUniqueRefArrayW_fdump(FILE *fp, MyDataUniqueRefArrayW *p, int tab);

// MyDataUniqueRefArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedArrayW
typedef struct MyDataOrderedArrayW
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedArrayW *p);
	Dz1Error (*travel)(struct MyDataOrderedArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataOrderedArrayW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedArrayW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataOrderedArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataOrderedArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataOrderedArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataOrderedArrayW *p);
	MyDataEntryW *(*getTail)(struct MyDataOrderedArrayW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataOrderedArrayW;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedArrayW *MyDataOrderedArrayW_new(Dz1Error *err);
static __inline__ MyDataOrderedArrayW *MyDataOrderedArrayW_gen(Dz1Error *err) { return MyDataOrderedArrayW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedArrayW *MyDataOrderedArrayW_clone(MyDataOrderedArrayW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedArrayW_purge(MyDataOrderedArrayW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedArrayW_del(MyDataOrderedArrayW *p);
static __inline__ void MyDataOrderedArrayW_delAndSetNull(void *ptr)
{
	MyDataOrderedArrayW **p = (MyDataOrderedArrayW **)ptr;
	if (p != NULL) { MyDataOrderedArrayW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedArrayW_dump(MyDataOrderedArrayW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedArrayW_fdump(FILE *fp, MyDataOrderedArrayW *p, int tab);

// MyDataOrderedArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataOrderedRefArrayW
typedef struct MyDataOrderedRefArrayW
{
	void *storage;
	unsigned int (*count)(struct MyDataOrderedRefArrayW *p);
	Dz1Error (*travel)(struct MyDataOrderedRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataOrderedRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataOrderedRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataOrderedRefArrayW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataOrderedRefArrayW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataOrderedRefArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataOrderedRefArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataOrderedRefArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataOrderedRefArrayW *p);
	MyDataEntryW *(*getTail)(struct MyDataOrderedRefArrayW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataOrderedRefArrayW;

DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefArrayW *MyDataOrderedRefArrayW_new(Dz1Error *err);
static __inline__ MyDataOrderedRefArrayW *MyDataOrderedRefArrayW_gen(Dz1Error *err) { return MyDataOrderedRefArrayW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataOrderedRefArrayW *MyDataOrderedRefArrayW_clone(MyDataOrderedRefArrayW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefArrayW_purge(MyDataOrderedRefArrayW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefArrayW_del(MyDataOrderedRefArrayW *p);
static __inline__ void MyDataOrderedRefArrayW_delAndSetNull(void *ptr)
{
	MyDataOrderedRefArrayW **p = (MyDataOrderedRefArrayW **)ptr;
	if (p != NULL) { MyDataOrderedRefArrayW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefArrayW_dump(MyDataOrderedRefArrayW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataOrderedRefArrayW_fdump(FILE *fp, MyDataOrderedRefArrayW *p, int tab);

// MyDataOrderedRefArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataArrayW
typedef struct MyDataArrayW
{
	void *storage;
	unsigned int (*count)(struct MyDataArrayW *p);
	Dz1Error (*travel)(struct MyDataArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataArrayW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataArrayW *p, MyDataEntryW *data);
	MyDataEntryW *(*extract)(struct MyDataArrayW *p, MyDataEntryW *ptr);
	MyDataEntryW *(*find)(struct MyDataArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataArrayW *p);
	MyDataEntryW *(*getTail)(struct MyDataArrayW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataArrayW;

DZ1_CPPLINK DZ1_DLLPORT MyDataArrayW *MyDataArrayW_new(Dz1Error *err);
static __inline__ MyDataArrayW *MyDataArrayW_gen(Dz1Error *err) { return MyDataArrayW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataArrayW *MyDataArrayW_clone(MyDataArrayW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataArrayW_purge(MyDataArrayW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataArrayW_del(MyDataArrayW *p);
static __inline__ void MyDataArrayW_delAndSetNull(void *ptr)
{
	MyDataArrayW **p = (MyDataArrayW **)ptr;
	if (p != NULL) { MyDataArrayW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataArrayW_dump(MyDataArrayW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataArrayW_fdump(FILE *fp, MyDataArrayW *p, int tab);

// MyDataArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataRefArrayW
typedef struct MyDataRefArrayW
{
	void *storage;
	unsigned int (*count)(struct MyDataRefArrayW *p);
	Dz1Error (*travel)(struct MyDataRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataRefArrayW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataRefArrayW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataRefArrayW *p, MyDataEntryW *data);
	MyDataEntryW *(*extract)(struct MyDataRefArrayW *p, MyDataEntryW *ptr);
	MyDataEntryW *(*find)(struct MyDataRefArrayW *p, MyDataEntryW *key);
	MyDataEntryW *(*getHead)(struct MyDataRefArrayW *p);
	MyDataEntryW *(*getTail)(struct MyDataRefArrayW *p);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataRefArrayW;

DZ1_CPPLINK DZ1_DLLPORT MyDataRefArrayW *MyDataRefArrayW_new(Dz1Error *err);
static __inline__ MyDataRefArrayW *MyDataRefArrayW_gen(Dz1Error *err) { return MyDataRefArrayW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataRefArrayW *MyDataRefArrayW_clone(MyDataRefArrayW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefArrayW_purge(MyDataRefArrayW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefArrayW_del(MyDataRefArrayW *p);
static __inline__ void MyDataRefArrayW_delAndSetNull(void *ptr)
{
	MyDataRefArrayW **p = (MyDataRefArrayW **)ptr;
	if (p != NULL) { MyDataRefArrayW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefArrayW_dump(MyDataRefArrayW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefArrayW_fdump(FILE *fp, MyDataRefArrayW *p, int tab);

// MyDataRefArrayW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataIndexW
typedef struct MyDataIndexW
{
	void *storage;
	unsigned int (*count)(struct MyDataIndexW *p);
	Dz1Error (*travel)(struct MyDataIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataIndexW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataIndexW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataIndexW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataIndexW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataIndexW *p, MyDataEntryW *key);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataIndexW;

DZ1_CPPLINK DZ1_DLLPORT MyDataIndexW *MyDataIndexW_new(Dz1Error *err);
static __inline__ MyDataIndexW *MyDataIndexW_gen(Dz1Error *err) { return MyDataIndexW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataIndexW *MyDataIndexW_clone(MyDataIndexW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndexW_purge(MyDataIndexW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndexW_del(MyDataIndexW *p);
static __inline__ void MyDataIndexW_delAndSetNull(void *ptr)
{
	MyDataIndexW **p = (MyDataIndexW **)ptr;
	if (p != NULL) { MyDataIndexW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndexW_dump(MyDataIndexW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataIndexW_fdump(FILE *fp, MyDataIndexW *p, int tab);

// MyDataIndexW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyDataRefIndexW
typedef struct MyDataRefIndexW
{
	void *storage;
	unsigned int (*count)(struct MyDataRefIndexW *p);
	Dz1Error (*travel)(struct MyDataRefIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyDataRefIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyDataRefIndexW *p, Dz1Error (*func)(void *ptr, MyDataEntryW *entry), void *ptr);
	MyDataEntryW **(*get_array)(struct MyDataRefIndexW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyDataRefIndexW *p, MyDataEntryW *data);
	bool_t (*remove)(struct MyDataRefIndexW *p, MyDataEntryW *key);
	MyDataEntryW *(*extract)(struct MyDataRefIndexW *p, MyDataEntryW *key);
	MyDataEntryW *(*find)(struct MyDataRefIndexW *p, MyDataEntryW *key);
	int (*cmp)(MyDataEntryW *a, MyDataEntryW *b);
} MyDataRefIndexW;

DZ1_CPPLINK DZ1_DLLPORT MyDataRefIndexW *MyDataRefIndexW_new(Dz1Error *err);
static __inline__ MyDataRefIndexW *MyDataRefIndexW_gen(Dz1Error *err) { return MyDataRefIndexW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyDataRefIndexW *MyDataRefIndexW_clone(MyDataRefIndexW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndexW_purge(MyDataRefIndexW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndexW_del(MyDataRefIndexW *p);
static __inline__ void MyDataRefIndexW_delAndSetNull(void *ptr)
{
	MyDataRefIndexW **p = (MyDataRefIndexW **)ptr;
	if (p != NULL) { MyDataRefIndexW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndexW_dump(MyDataRefIndexW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyDataRefIndexW_fdump(FILE *fp, MyDataRefIndexW *p, int tab);

// MyDataRefIndexW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// ArrayMemberTypeW
typedef struct ArrayMemberTypeW
{
	MyDataEntryW	**obj_ptr_arr;
	u32_t			  obj_ptr_cnt;
	MyDataEntryW	 *obj_arr;
	u32_t			  obj_cnt;
	u64_t			 *prims_arr;
	u32_t			  prims_cnt;
	u64_t			**primptrs_arr;
	u32_t			  primptrs_cnt;
	wstr_t			 *str_arr;
	u32_t			  str_cnt;
	s32_t			 *i_val;
} ArrayMemberTypeW;

DZ1_CPPLINK DZ1_DLLPORT ArrayMemberTypeW *ArrayMemberTypeW_new(MyDataEntryW **obj_ptr_arr_e_clone, 
															   u32_t obj_ptr_cnt, 
															   MyDataEntryW *obj_arr_e_copy, 
															   u32_t obj_cnt, 
															   u64_t *prims_arr_e_copy, 
															   u32_t prims_cnt, 
															   u64_t **primptrs_arr_e_clone, 
															   u32_t primptrs_cnt, 
															   wstr_t *str_arr_e_clone, 
															   u32_t str_cnt, 
															   s32_t *i_val_ref, Dz1Error *err);
static __inline__ ArrayMemberTypeW *ArrayMemberTypeW_gen(Dz1Error *err) { return ArrayMemberTypeW_new(NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ArrayMemberTypeW_copy(ArrayMemberTypeW *dst, ArrayMemberTypeW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberTypeW *ArrayMemberTypeW_clone(ArrayMemberTypeW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberTypeW_purge(ArrayMemberTypeW *p);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberTypeW_del(ArrayMemberTypeW *p);
static __inline__ void ArrayMemberTypeW_delAndSetNull(void *ptr)
{
	ArrayMemberTypeW **p = (ArrayMemberTypeW **)ptr;
	if (p) { ArrayMemberTypeW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberTypeW_dump(ArrayMemberTypeW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberTypeW_fdump(FILE *fp, ArrayMemberTypeW *p, int tab);
// ArrayMemberTypeW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#endif
