#ifndef _DZ1_TDC_DZ1_TDC_INFO_PRIM_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_PRIM_TEST_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// MyStrUniqueTable
typedef struct MyStrUniqueTable
{
	void *storage;
	unsigned int (*count)(struct MyStrUniqueTable *p);
	Dz1Error (*travel)(struct MyStrUniqueTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelForward)(struct MyStrUniqueTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyStrUniqueTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	str_t *(*get_array)(struct MyStrUniqueTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyStrUniqueTable *p, str_t data);
	bool_t (*remove)(struct MyStrUniqueTable *p, str_t key);
	str_t (*extract)(struct MyStrUniqueTable *p, str_t key);
	str_t (*find)(struct MyStrUniqueTable *p, str_t key);
	str_t (*getHead)(struct MyStrUniqueTable *p);
	str_t (*getTail)(struct MyStrUniqueTable *p);
	int (*cmp)(str_t a, str_t b);
} MyStrUniqueTable;

DZ1_CPPLINK DZ1_DLLPORT MyStrUniqueTable *MyStrUniqueTable_new(Dz1Error *err);
static __inline__ MyStrUniqueTable *MyStrUniqueTable_gen(Dz1Error *err) { return MyStrUniqueTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyStrUniqueTable *MyStrUniqueTable_clone(MyStrUniqueTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyStrUniqueTable_purge(MyStrUniqueTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyStrUniqueTable_del(MyStrUniqueTable *p);
static __inline__ void MyStrUniqueTable_delAndSetNull(void *ptr)
{
	MyStrUniqueTable **p = (MyStrUniqueTable **)ptr;
	if (p != NULL) { MyStrUniqueTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyStrUniqueTableA_dump(MyStrUniqueTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyStrUniqueTableA_fdump(FILE *fp, MyStrUniqueTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyStrUniqueTableW_dump(MyStrUniqueTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyStrUniqueTableW_fdump(FILE *fp, MyStrUniqueTable *p, int tab);
#ifdef UNICODE
#define MyStrUniqueTable_dump MyStrUniqueTableW_dump
#define MyStrUniqueTable_fdump MyStrUniqueTableW_fdump
#else //  UNICODE
#define MyStrUniqueTable_dump MyStrUniqueTableA_dump
#define MyStrUniqueTable_fdump MyStrUniqueTableA_fdump
#endif //  UNICODE
static __inline__ void MyStrUniqueTableX_dump(MyStrUniqueTable *p, int tab) { DZ1_DUMP(MyStrUniqueTable, p, tab); }
static __inline__ void MyStrUniqueTableX_fdump(FILE *fp, MyStrUniqueTable *p, int tab) { DZ1_FDUMP(fp, MyStrUniqueTable, p, tab); }
#else // UNIX_SYSTEM
#define MyStrUniqueTable_dump MyStrUniqueTableA_dump
#define MyStrUniqueTableX_dump MyStrUniqueTableA_dump
#define MyStrUniqueTable_fdump MyStrUniqueTableA_fdump
#define MyStrUniqueTableX_fdump MyStrUniqueTableA_fdump
#endif // UNIX_SYSTEM

// MyStrUniqueTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStrOrderedTable
typedef struct MyStrOrderedTable
{
	void *storage;
	unsigned int (*count)(struct MyStrOrderedTable *p);
	Dz1Error (*travel)(struct MyStrOrderedTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelForward)(struct MyStrOrderedTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyStrOrderedTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	str_t *(*get_array)(struct MyStrOrderedTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyStrOrderedTable *p, str_t data);
	bool_t (*remove)(struct MyStrOrderedTable *p, str_t key);
	str_t (*extract)(struct MyStrOrderedTable *p, str_t key);
	str_t (*find)(struct MyStrOrderedTable *p, str_t key);
	str_t (*getHead)(struct MyStrOrderedTable *p);
	str_t (*getTail)(struct MyStrOrderedTable *p);
	int (*cmp)(str_t a, str_t b);
} MyStrOrderedTable;

DZ1_CPPLINK DZ1_DLLPORT MyStrOrderedTable *MyStrOrderedTable_new(Dz1Error *err);
static __inline__ MyStrOrderedTable *MyStrOrderedTable_gen(Dz1Error *err) { return MyStrOrderedTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyStrOrderedTable *MyStrOrderedTable_clone(MyStrOrderedTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyStrOrderedTable_purge(MyStrOrderedTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyStrOrderedTable_del(MyStrOrderedTable *p);
static __inline__ void MyStrOrderedTable_delAndSetNull(void *ptr)
{
	MyStrOrderedTable **p = (MyStrOrderedTable **)ptr;
	if (p != NULL) { MyStrOrderedTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyStrOrderedTableA_dump(MyStrOrderedTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyStrOrderedTableA_fdump(FILE *fp, MyStrOrderedTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyStrOrderedTableW_dump(MyStrOrderedTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyStrOrderedTableW_fdump(FILE *fp, MyStrOrderedTable *p, int tab);
#ifdef UNICODE
#define MyStrOrderedTable_dump MyStrOrderedTableW_dump
#define MyStrOrderedTable_fdump MyStrOrderedTableW_fdump
#else //  UNICODE
#define MyStrOrderedTable_dump MyStrOrderedTableA_dump
#define MyStrOrderedTable_fdump MyStrOrderedTableA_fdump
#endif //  UNICODE
static __inline__ void MyStrOrderedTableX_dump(MyStrOrderedTable *p, int tab) { DZ1_DUMP(MyStrOrderedTable, p, tab); }
static __inline__ void MyStrOrderedTableX_fdump(FILE *fp, MyStrOrderedTable *p, int tab) { DZ1_FDUMP(fp, MyStrOrderedTable, p, tab); }
#else // UNIX_SYSTEM
#define MyStrOrderedTable_dump MyStrOrderedTableA_dump
#define MyStrOrderedTableX_dump MyStrOrderedTableA_dump
#define MyStrOrderedTable_fdump MyStrOrderedTableA_fdump
#define MyStrOrderedTableX_fdump MyStrOrderedTableA_fdump
#endif // UNIX_SYSTEM

// MyStrOrderedTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStrTable
typedef struct MyStrTable
{
	void *storage;
	unsigned int (*count)(struct MyStrTable *p);
	Dz1Error (*travel)(struct MyStrTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelForward)(struct MyStrTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyStrTable *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	str_t *(*get_array)(struct MyStrTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyStrTable *p, str_t data);
	bool_t (*remove)(struct MyStrTable *p, str_t ptr);
	str_t (*extract)(struct MyStrTable *p, str_t ptr);
	str_t (*find)(struct MyStrTable *p, str_t key);
	str_t (*getHead)(struct MyStrTable *p);
	str_t (*getTail)(struct MyStrTable *p);
	int (*cmp)(str_t a, str_t b);
} MyStrTable;

DZ1_CPPLINK DZ1_DLLPORT MyStrTable *MyStrTable_new(Dz1Error *err);
static __inline__ MyStrTable *MyStrTable_gen(Dz1Error *err) { return MyStrTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyStrTable *MyStrTable_clone(MyStrTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyStrTable_purge(MyStrTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyStrTable_del(MyStrTable *p);
static __inline__ void MyStrTable_delAndSetNull(void *ptr)
{
	MyStrTable **p = (MyStrTable **)ptr;
	if (p != NULL) { MyStrTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyStrTableA_dump(MyStrTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyStrTableA_fdump(FILE *fp, MyStrTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyStrTableW_dump(MyStrTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyStrTableW_fdump(FILE *fp, MyStrTable *p, int tab);
#ifdef UNICODE
#define MyStrTable_dump MyStrTableW_dump
#define MyStrTable_fdump MyStrTableW_fdump
#else //  UNICODE
#define MyStrTable_dump MyStrTableA_dump
#define MyStrTable_fdump MyStrTableA_fdump
#endif //  UNICODE
static __inline__ void MyStrTableX_dump(MyStrTable *p, int tab) { DZ1_DUMP(MyStrTable, p, tab); }
static __inline__ void MyStrTableX_fdump(FILE *fp, MyStrTable *p, int tab) { DZ1_FDUMP(fp, MyStrTable, p, tab); }
#else // UNIX_SYSTEM
#define MyStrTable_dump MyStrTableA_dump
#define MyStrTableX_dump MyStrTableA_dump
#define MyStrTable_fdump MyStrTableA_fdump
#define MyStrTableX_fdump MyStrTableA_fdump
#endif // UNIX_SYSTEM

// MyStrTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyWStrUniqueTable
typedef struct MyWStrUniqueTable
{
	void *storage;
	unsigned int (*count)(struct MyWStrUniqueTable *p);
	Dz1Error (*travel)(struct MyWStrUniqueTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	Dz1Error (*travelForward)(struct MyWStrUniqueTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyWStrUniqueTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	wstr_t *(*get_array)(struct MyWStrUniqueTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyWStrUniqueTable *p, wstr_t data);
	bool_t (*remove)(struct MyWStrUniqueTable *p, wstr_t key);
	wstr_t (*extract)(struct MyWStrUniqueTable *p, wstr_t key);
	wstr_t (*find)(struct MyWStrUniqueTable *p, wstr_t key);
	wstr_t (*getHead)(struct MyWStrUniqueTable *p);
	wstr_t (*getTail)(struct MyWStrUniqueTable *p);
	int (*cmp)(wstr_t a, wstr_t b);
} MyWStrUniqueTable;

DZ1_CPPLINK DZ1_DLLPORT MyWStrUniqueTable *MyWStrUniqueTable_new(Dz1Error *err);
static __inline__ MyWStrUniqueTable *MyWStrUniqueTable_gen(Dz1Error *err) { return MyWStrUniqueTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyWStrUniqueTable *MyWStrUniqueTable_clone(MyWStrUniqueTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrUniqueTable_purge(MyWStrUniqueTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrUniqueTable_del(MyWStrUniqueTable *p);
static __inline__ void MyWStrUniqueTable_delAndSetNull(void *ptr)
{
	MyWStrUniqueTable **p = (MyWStrUniqueTable **)ptr;
	if (p != NULL) { MyWStrUniqueTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyWStrUniqueTableA_dump(MyWStrUniqueTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrUniqueTableA_fdump(FILE *fp, MyWStrUniqueTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyWStrUniqueTableW_dump(MyWStrUniqueTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrUniqueTableW_fdump(FILE *fp, MyWStrUniqueTable *p, int tab);
#ifdef UNICODE
#define MyWStrUniqueTable_dump MyWStrUniqueTableW_dump
#define MyWStrUniqueTable_fdump MyWStrUniqueTableW_fdump
#else //  UNICODE
#define MyWStrUniqueTable_dump MyWStrUniqueTableA_dump
#define MyWStrUniqueTable_fdump MyWStrUniqueTableA_fdump
#endif //  UNICODE
static __inline__ void MyWStrUniqueTableX_dump(MyWStrUniqueTable *p, int tab) { DZ1_DUMP(MyWStrUniqueTable, p, tab); }
static __inline__ void MyWStrUniqueTableX_fdump(FILE *fp, MyWStrUniqueTable *p, int tab) { DZ1_FDUMP(fp, MyWStrUniqueTable, p, tab); }
#else // UNIX_SYSTEM
#define MyWStrUniqueTable_dump MyWStrUniqueTableA_dump
#define MyWStrUniqueTableX_dump MyWStrUniqueTableA_dump
#define MyWStrUniqueTable_fdump MyWStrUniqueTableA_fdump
#define MyWStrUniqueTableX_fdump MyWStrUniqueTableA_fdump
#endif // UNIX_SYSTEM

// MyWStrUniqueTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyWStrOrderedTable
typedef struct MyWStrOrderedTable
{
	void *storage;
	unsigned int (*count)(struct MyWStrOrderedTable *p);
	Dz1Error (*travel)(struct MyWStrOrderedTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	Dz1Error (*travelForward)(struct MyWStrOrderedTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyWStrOrderedTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	wstr_t *(*get_array)(struct MyWStrOrderedTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyWStrOrderedTable *p, wstr_t data);
	bool_t (*remove)(struct MyWStrOrderedTable *p, wstr_t key);
	wstr_t (*extract)(struct MyWStrOrderedTable *p, wstr_t key);
	wstr_t (*find)(struct MyWStrOrderedTable *p, wstr_t key);
	wstr_t (*getHead)(struct MyWStrOrderedTable *p);
	wstr_t (*getTail)(struct MyWStrOrderedTable *p);
	int (*cmp)(wstr_t a, wstr_t b);
} MyWStrOrderedTable;

DZ1_CPPLINK DZ1_DLLPORT MyWStrOrderedTable *MyWStrOrderedTable_new(Dz1Error *err);
static __inline__ MyWStrOrderedTable *MyWStrOrderedTable_gen(Dz1Error *err) { return MyWStrOrderedTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyWStrOrderedTable *MyWStrOrderedTable_clone(MyWStrOrderedTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrOrderedTable_purge(MyWStrOrderedTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrOrderedTable_del(MyWStrOrderedTable *p);
static __inline__ void MyWStrOrderedTable_delAndSetNull(void *ptr)
{
	MyWStrOrderedTable **p = (MyWStrOrderedTable **)ptr;
	if (p != NULL) { MyWStrOrderedTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyWStrOrderedTableA_dump(MyWStrOrderedTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrOrderedTableA_fdump(FILE *fp, MyWStrOrderedTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyWStrOrderedTableW_dump(MyWStrOrderedTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrOrderedTableW_fdump(FILE *fp, MyWStrOrderedTable *p, int tab);
#ifdef UNICODE
#define MyWStrOrderedTable_dump MyWStrOrderedTableW_dump
#define MyWStrOrderedTable_fdump MyWStrOrderedTableW_fdump
#else //  UNICODE
#define MyWStrOrderedTable_dump MyWStrOrderedTableA_dump
#define MyWStrOrderedTable_fdump MyWStrOrderedTableA_fdump
#endif //  UNICODE
static __inline__ void MyWStrOrderedTableX_dump(MyWStrOrderedTable *p, int tab) { DZ1_DUMP(MyWStrOrderedTable, p, tab); }
static __inline__ void MyWStrOrderedTableX_fdump(FILE *fp, MyWStrOrderedTable *p, int tab) { DZ1_FDUMP(fp, MyWStrOrderedTable, p, tab); }
#else // UNIX_SYSTEM
#define MyWStrOrderedTable_dump MyWStrOrderedTableA_dump
#define MyWStrOrderedTableX_dump MyWStrOrderedTableA_dump
#define MyWStrOrderedTable_fdump MyWStrOrderedTableA_fdump
#define MyWStrOrderedTableX_fdump MyWStrOrderedTableA_fdump
#endif // UNIX_SYSTEM

// MyWStrOrderedTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyWStrTable
typedef struct MyWStrTable
{
	void *storage;
	unsigned int (*count)(struct MyWStrTable *p);
	Dz1Error (*travel)(struct MyWStrTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	Dz1Error (*travelForward)(struct MyWStrTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyWStrTable *p, Dz1Error (*func)(void *ptr, wstr_t entry), void *ptr);
	wstr_t *(*get_array)(struct MyWStrTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyWStrTable *p, wstr_t data);
	bool_t (*remove)(struct MyWStrTable *p, wstr_t ptr);
	wstr_t (*extract)(struct MyWStrTable *p, wstr_t ptr);
	wstr_t (*find)(struct MyWStrTable *p, wstr_t key);
	wstr_t (*getHead)(struct MyWStrTable *p);
	wstr_t (*getTail)(struct MyWStrTable *p);
	int (*cmp)(wstr_t a, wstr_t b);
} MyWStrTable;

DZ1_CPPLINK DZ1_DLLPORT MyWStrTable *MyWStrTable_new(Dz1Error *err);
static __inline__ MyWStrTable *MyWStrTable_gen(Dz1Error *err) { return MyWStrTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyWStrTable *MyWStrTable_clone(MyWStrTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrTable_purge(MyWStrTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrTable_del(MyWStrTable *p);
static __inline__ void MyWStrTable_delAndSetNull(void *ptr)
{
	MyWStrTable **p = (MyWStrTable **)ptr;
	if (p != NULL) { MyWStrTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyWStrTableA_dump(MyWStrTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrTableA_fdump(FILE *fp, MyWStrTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyWStrTableW_dump(MyWStrTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyWStrTableW_fdump(FILE *fp, MyWStrTable *p, int tab);
#ifdef UNICODE
#define MyWStrTable_dump MyWStrTableW_dump
#define MyWStrTable_fdump MyWStrTableW_fdump
#else //  UNICODE
#define MyWStrTable_dump MyWStrTableA_dump
#define MyWStrTable_fdump MyWStrTableA_fdump
#endif //  UNICODE
static __inline__ void MyWStrTableX_dump(MyWStrTable *p, int tab) { DZ1_DUMP(MyWStrTable, p, tab); }
static __inline__ void MyWStrTableX_fdump(FILE *fp, MyWStrTable *p, int tab) { DZ1_FDUMP(fp, MyWStrTable, p, tab); }
#else // UNIX_SYSTEM
#define MyWStrTable_dump MyWStrTableA_dump
#define MyWStrTableX_dump MyWStrTableA_dump
#define MyWStrTable_fdump MyWStrTableA_fdump
#define MyWStrTableX_fdump MyWStrTableA_fdump
#endif // UNIX_SYSTEM

// MyWStrTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyIntUniqueTable
typedef struct MyIntUniqueTable
{
	void *storage;
	unsigned int (*count)(struct MyIntUniqueTable *p);
	Dz1Error (*travel)(struct MyIntUniqueTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyIntUniqueTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyIntUniqueTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	s32_t *(*get_array)(struct MyIntUniqueTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyIntUniqueTable *p, s32_t data);
	bool_t (*remove)(struct MyIntUniqueTable *p, s32_t *key);
	s32_t *(*extract)(struct MyIntUniqueTable *p, s32_t *key);
	s32_t *(*find)(struct MyIntUniqueTable *p, s32_t key);
	s32_t *(*getHead)(struct MyIntUniqueTable *p);
	s32_t *(*getTail)(struct MyIntUniqueTable *p);
	int (*cmp)(s32_t *a, s32_t *b);
} MyIntUniqueTable;

DZ1_CPPLINK DZ1_DLLPORT MyIntUniqueTable *MyIntUniqueTable_new(Dz1Error *err);
static __inline__ MyIntUniqueTable *MyIntUniqueTable_gen(Dz1Error *err) { return MyIntUniqueTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyIntUniqueTable *MyIntUniqueTable_clone(MyIntUniqueTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyIntUniqueTable_purge(MyIntUniqueTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyIntUniqueTable_del(MyIntUniqueTable *p);
static __inline__ void MyIntUniqueTable_delAndSetNull(void *ptr)
{
	MyIntUniqueTable **p = (MyIntUniqueTable **)ptr;
	if (p != NULL) { MyIntUniqueTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyIntUniqueTableA_dump(MyIntUniqueTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyIntUniqueTableA_fdump(FILE *fp, MyIntUniqueTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyIntUniqueTableW_dump(MyIntUniqueTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyIntUniqueTableW_fdump(FILE *fp, MyIntUniqueTable *p, int tab);
#ifdef UNICODE
#define MyIntUniqueTable_dump MyIntUniqueTableW_dump
#define MyIntUniqueTable_fdump MyIntUniqueTableW_fdump
#else //  UNICODE
#define MyIntUniqueTable_dump MyIntUniqueTableA_dump
#define MyIntUniqueTable_fdump MyIntUniqueTableA_fdump
#endif //  UNICODE
static __inline__ void MyIntUniqueTableX_dump(MyIntUniqueTable *p, int tab) { DZ1_DUMP(MyIntUniqueTable, p, tab); }
static __inline__ void MyIntUniqueTableX_fdump(FILE *fp, MyIntUniqueTable *p, int tab) { DZ1_FDUMP(fp, MyIntUniqueTable, p, tab); }
#else // UNIX_SYSTEM
#define MyIntUniqueTable_dump MyIntUniqueTableA_dump
#define MyIntUniqueTableX_dump MyIntUniqueTableA_dump
#define MyIntUniqueTable_fdump MyIntUniqueTableA_fdump
#define MyIntUniqueTableX_fdump MyIntUniqueTableA_fdump
#endif // UNIX_SYSTEM

// MyIntUniqueTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyIntOrderedTable
typedef struct MyIntOrderedTable
{
	void *storage;
	unsigned int (*count)(struct MyIntOrderedTable *p);
	Dz1Error (*travel)(struct MyIntOrderedTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyIntOrderedTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyIntOrderedTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	s32_t *(*get_array)(struct MyIntOrderedTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyIntOrderedTable *p, s32_t data);
	bool_t (*remove)(struct MyIntOrderedTable *p, s32_t *key);
	s32_t *(*extract)(struct MyIntOrderedTable *p, s32_t *key);
	s32_t *(*find)(struct MyIntOrderedTable *p, s32_t key);
	s32_t *(*getHead)(struct MyIntOrderedTable *p);
	s32_t *(*getTail)(struct MyIntOrderedTable *p);
	int (*cmp)(s32_t *a, s32_t *b);
} MyIntOrderedTable;

DZ1_CPPLINK DZ1_DLLPORT MyIntOrderedTable *MyIntOrderedTable_new(Dz1Error *err);
static __inline__ MyIntOrderedTable *MyIntOrderedTable_gen(Dz1Error *err) { return MyIntOrderedTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyIntOrderedTable *MyIntOrderedTable_clone(MyIntOrderedTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyIntOrderedTable_purge(MyIntOrderedTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyIntOrderedTable_del(MyIntOrderedTable *p);
static __inline__ void MyIntOrderedTable_delAndSetNull(void *ptr)
{
	MyIntOrderedTable **p = (MyIntOrderedTable **)ptr;
	if (p != NULL) { MyIntOrderedTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyIntOrderedTableA_dump(MyIntOrderedTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyIntOrderedTableA_fdump(FILE *fp, MyIntOrderedTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyIntOrderedTableW_dump(MyIntOrderedTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyIntOrderedTableW_fdump(FILE *fp, MyIntOrderedTable *p, int tab);
#ifdef UNICODE
#define MyIntOrderedTable_dump MyIntOrderedTableW_dump
#define MyIntOrderedTable_fdump MyIntOrderedTableW_fdump
#else //  UNICODE
#define MyIntOrderedTable_dump MyIntOrderedTableA_dump
#define MyIntOrderedTable_fdump MyIntOrderedTableA_fdump
#endif //  UNICODE
static __inline__ void MyIntOrderedTableX_dump(MyIntOrderedTable *p, int tab) { DZ1_DUMP(MyIntOrderedTable, p, tab); }
static __inline__ void MyIntOrderedTableX_fdump(FILE *fp, MyIntOrderedTable *p, int tab) { DZ1_FDUMP(fp, MyIntOrderedTable, p, tab); }
#else // UNIX_SYSTEM
#define MyIntOrderedTable_dump MyIntOrderedTableA_dump
#define MyIntOrderedTableX_dump MyIntOrderedTableA_dump
#define MyIntOrderedTable_fdump MyIntOrderedTableA_fdump
#define MyIntOrderedTableX_fdump MyIntOrderedTableA_fdump
#endif // UNIX_SYSTEM

// MyIntOrderedTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyIntTable
typedef struct MyIntTable
{
	void *storage;
	unsigned int (*count)(struct MyIntTable *p);
	Dz1Error (*travel)(struct MyIntTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyIntTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyIntTable *p, Dz1Error (*func)(void *ptr, s32_t *entry), void *ptr);
	s32_t *(*get_array)(struct MyIntTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyIntTable *p, s32_t data);
	bool_t (*remove)(struct MyIntTable *p, s32_t *ptr);
	s32_t *(*extract)(struct MyIntTable *p, s32_t *ptr);
	s32_t *(*find)(struct MyIntTable *p, s32_t key);
	s32_t *(*getHead)(struct MyIntTable *p);
	s32_t *(*getTail)(struct MyIntTable *p);
	int (*cmp)(s32_t *a, s32_t *b);
} MyIntTable;

DZ1_CPPLINK DZ1_DLLPORT MyIntTable *MyIntTable_new(Dz1Error *err);
static __inline__ MyIntTable *MyIntTable_gen(Dz1Error *err) { return MyIntTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyIntTable *MyIntTable_clone(MyIntTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyIntTable_purge(MyIntTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyIntTable_del(MyIntTable *p);
static __inline__ void MyIntTable_delAndSetNull(void *ptr)
{
	MyIntTable **p = (MyIntTable **)ptr;
	if (p != NULL) { MyIntTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyIntTableA_dump(MyIntTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyIntTableA_fdump(FILE *fp, MyIntTable *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void MyIntTableW_dump(MyIntTable *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyIntTableW_fdump(FILE *fp, MyIntTable *p, int tab);
#ifdef UNICODE
#define MyIntTable_dump MyIntTableW_dump
#define MyIntTable_fdump MyIntTableW_fdump
#else //  UNICODE
#define MyIntTable_dump MyIntTableA_dump
#define MyIntTable_fdump MyIntTableA_fdump
#endif //  UNICODE
static __inline__ void MyIntTableX_dump(MyIntTable *p, int tab) { DZ1_DUMP(MyIntTable, p, tab); }
static __inline__ void MyIntTableX_fdump(FILE *fp, MyIntTable *p, int tab) { DZ1_FDUMP(fp, MyIntTable, p, tab); }
#else // UNIX_SYSTEM
#define MyIntTable_dump MyIntTableA_dump
#define MyIntTableX_dump MyIntTableA_dump
#define MyIntTable_fdump MyIntTableA_fdump
#define MyIntTableX_fdump MyIntTableA_fdump
#endif // UNIX_SYSTEM

// MyIntTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnum
typedef enum MyEnum
{
	MyEnum_first,
	MyEnum_second = 3,
	MyEnum_max
} MyEnum;

DZ1_CPPLINK str_t MyEnumStrA(MyEnum v);
DZ1_CPPLINK MyEnum MyEnumFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t MyEnumStrW(MyEnum v);
DZ1_CPPLINK MyEnum MyEnumFromStrW(wstr_t str);
#ifdef UNICODE
#define MyEnumStr MyEnumStrW
#define MyEnumFromStr MyEnumFromStrW
#else // UNICODE
#define MyEnumStr MyEnumStrA
#define MyEnumFromStr MyEnumFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define MyEnumStr MyEnumStrA
#define MyEnumFromStr MyEnumFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT MyEnum *MyEnum_new(MyEnum *src, Dz1Error *err);
static __inline__ MyEnum *MyEnum_gen(Dz1Error *err) { MyEnum v = MyEnum_max; return MyEnum_new(&v, err); }
static __inline__ void MyEnum_del(MyEnum *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void MyEnum_delAndSetNull(void *ptr)
{
	MyEnum **p = (MyEnum **)ptr;
	if (p != NULL) { MyEnum_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyEnumA_dump(MyEnum *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyEnum_cmp(MyEnum *a, MyEnum *b);
// MyEnum
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnumUniqueTable
typedef struct MyEnumUniqueTable
{
	void *storage;
	unsigned int (*count)(struct MyEnumUniqueTable *p);
	Dz1Error (*travel)(struct MyEnumUniqueTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyEnumUniqueTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyEnumUniqueTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	MyEnum *(*get_array)(struct MyEnumUniqueTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyEnumUniqueTable *p, MyEnum data);
	bool_t (*remove)(struct MyEnumUniqueTable *p, MyEnum *key);
	MyEnum *(*extract)(struct MyEnumUniqueTable *p, MyEnum *key);
	MyEnum *(*find)(struct MyEnumUniqueTable *p, MyEnum key);
	MyEnum *(*getHead)(struct MyEnumUniqueTable *p);
	MyEnum *(*getTail)(struct MyEnumUniqueTable *p);
	int (*cmp)(MyEnum *a, MyEnum *b);
} MyEnumUniqueTable;

DZ1_CPPLINK DZ1_DLLPORT MyEnumUniqueTable *MyEnumUniqueTable_new(Dz1Error *err);
static __inline__ MyEnumUniqueTable *MyEnumUniqueTable_gen(Dz1Error *err) { return MyEnumUniqueTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void MyEnumUniqueTable_purge(MyEnumUniqueTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyEnumUniqueTable_del(MyEnumUniqueTable *p);
static __inline__ void MyEnumUniqueTable_delAndSetNull(void *ptr)
{
	MyEnumUniqueTable **p = (MyEnumUniqueTable **)ptr;
	if (p != NULL) { MyEnumUniqueTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyEnumUniqueTable_dump(MyEnumUniqueTable *p, int tab);

// MyEnumUniqueTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnumOrderedTable
typedef struct MyEnumOrderedTable
{
	void *storage;
	unsigned int (*count)(struct MyEnumOrderedTable *p);
	Dz1Error (*travel)(struct MyEnumOrderedTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyEnumOrderedTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyEnumOrderedTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	MyEnum *(*get_array)(struct MyEnumOrderedTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyEnumOrderedTable *p, MyEnum data);
	bool_t (*remove)(struct MyEnumOrderedTable *p, MyEnum *key);
	MyEnum *(*extract)(struct MyEnumOrderedTable *p, MyEnum *key);
	MyEnum *(*find)(struct MyEnumOrderedTable *p, MyEnum key);
	MyEnum *(*getHead)(struct MyEnumOrderedTable *p);
	MyEnum *(*getTail)(struct MyEnumOrderedTable *p);
	int (*cmp)(MyEnum *a, MyEnum *b);
} MyEnumOrderedTable;

DZ1_CPPLINK DZ1_DLLPORT MyEnumOrderedTable *MyEnumOrderedTable_new(Dz1Error *err);
static __inline__ MyEnumOrderedTable *MyEnumOrderedTable_gen(Dz1Error *err) { return MyEnumOrderedTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void MyEnumOrderedTable_purge(MyEnumOrderedTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyEnumOrderedTable_del(MyEnumOrderedTable *p);
static __inline__ void MyEnumOrderedTable_delAndSetNull(void *ptr)
{
	MyEnumOrderedTable **p = (MyEnumOrderedTable **)ptr;
	if (p != NULL) { MyEnumOrderedTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyEnumOrderedTable_dump(MyEnumOrderedTable *p, int tab);

// MyEnumOrderedTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnumTable
typedef struct MyEnumTable
{
	void *storage;
	unsigned int (*count)(struct MyEnumTable *p);
	Dz1Error (*travel)(struct MyEnumTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyEnumTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyEnumTable *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	MyEnum *(*get_array)(struct MyEnumTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyEnumTable *p, MyEnum data);
	MyEnum *(*getHead)(struct MyEnumTable *p);
	MyEnum *(*getTail)(struct MyEnumTable *p);
	int (*cmp)(MyEnum *a, MyEnum *b);
} MyEnumTable;

DZ1_CPPLINK DZ1_DLLPORT MyEnumTable *MyEnumTable_new(Dz1Error *err);
static __inline__ MyEnumTable *MyEnumTable_gen(Dz1Error *err) { return MyEnumTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void MyEnumTable_purge(MyEnumTable *p);
DZ1_CPPLINK DZ1_DLLPORT void MyEnumTable_del(MyEnumTable *p);
static __inline__ void MyEnumTable_delAndSetNull(void *ptr)
{
	MyEnumTable **p = (MyEnumTable **)ptr;
	if (p != NULL) { MyEnumTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyEnumTable_dump(MyEnumTable *p, int tab);

// MyEnumTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyEnumIndex
typedef struct MyEnumIndex
{
	void *storage;
	unsigned int (*count)(struct MyEnumIndex *p);
	Dz1Error (*travel)(struct MyEnumIndex *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyEnumIndex *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyEnumIndex *p, Dz1Error (*func)(void *ptr, MyEnum *entry), void *ptr);
	MyEnum *(*get_array)(struct MyEnumIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyEnumIndex *p, MyEnum data);
	bool_t (*remove)(struct MyEnumIndex *p, MyEnum *key);
	MyEnum *(*extract)(struct MyEnumIndex *p, MyEnum *key);
	MyEnum *(*find)(struct MyEnumIndex *p, MyEnum key);
	MyEnum *(*getHead)(struct MyEnumIndex *p);
	MyEnum *(*getTail)(struct MyEnumIndex *p);
	int (*cmp)(MyEnum *a, MyEnum *b);
} MyEnumIndex;

DZ1_CPPLINK DZ1_DLLPORT MyEnumIndex *MyEnumIndex_new(Dz1Error *err);
static __inline__ MyEnumIndex *MyEnumIndex_gen(Dz1Error *err) { return MyEnumIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void MyEnumIndex_purge(MyEnumIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void MyEnumIndex_del(MyEnumIndex *p);
static __inline__ void MyEnumIndex_delAndSetNull(void *ptr)
{
	MyEnumIndex **p = (MyEnumIndex **)ptr;
	if (p != NULL) { MyEnumIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyEnumIndex_dump(MyEnumIndex *p, int tab);

// MyEnumIndex
////////////////////////////////////////////////////////////////////////////////

#endif
