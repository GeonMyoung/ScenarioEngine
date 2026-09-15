#ifndef _DZ1_TDC_DZ1_TDC_INFO_UNION_A_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_UNION_A_TEST_H_

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
// MyUnionDataAPresent
typedef enum MyUnionDataAPresent
{
	MyUnionDataAPresent_name,
	MyUnionDataAPresent_val,
	MyUnionDataAPresent_max
} MyUnionDataAPresent;

DZ1_CPPLINK str_t MyUnionDataAPresentStrA(MyUnionDataAPresent v);
DZ1_CPPLINK MyUnionDataAPresent MyUnionDataAPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t MyUnionDataAPresentStrW(MyUnionDataAPresent v);
DZ1_CPPLINK MyUnionDataAPresent MyUnionDataAPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define MyUnionDataAPresentStr MyUnionDataAPresentStrW
#define MyUnionDataAPresentFromStr MyUnionDataAPresentFromStrW
#else // UNICODE
#define MyUnionDataAPresentStr MyUnionDataAPresentStrA
#define MyUnionDataAPresentFromStr MyUnionDataAPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define MyUnionDataAPresentStr MyUnionDataAPresentStrA
#define MyUnionDataAPresentFromStr MyUnionDataAPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataAPresent *MyUnionDataAPresent_new(MyUnionDataAPresent *src, Dz1Error *err);
static __inline__ MyUnionDataAPresent *MyUnionDataAPresent_gen(Dz1Error *err) { MyUnionDataAPresent v = MyUnionDataAPresent_max; return MyUnionDataAPresent_new(&v, err); }
#define MyUnionDataAPresent_clone             MyUnionDataAPresent_new
static __inline__ void MyUnionDataAPresent_del(MyUnionDataAPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void MyUnionDataAPresent_delAndSetNull(void *ptr)
{
	MyUnionDataAPresent **p = (MyUnionDataAPresent **)ptr;
	if (p != NULL) { MyUnionDataAPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataAPresent_dump(MyUnionDataAPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataAPresent_fdump(FILE *fp, MyUnionDataAPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyUnionDataAPresent_cmp(MyUnionDataAPresent *a, MyUnionDataAPresent *b);
// MyUnionDataAPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataA
typedef struct MyUnionDataA
{
	MyUnionDataAPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1UTF8Str		*name;
		u32_t				 val;
	} x;
} MyUnionDataA;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataA *MyUnionDataA_new(MyUnionDataAPresent present, void *ptr, Dz1Error *err);
static __inline__ MyUnionDataA *MyUnionDataA_gen(Dz1Error *err) { return MyUnionDataA_new(MyUnionDataAPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  MyUnionDataA_copy(MyUnionDataA *dst, MyUnionDataA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataA *MyUnionDataA_clone(MyUnionDataA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataA_purge(MyUnionDataA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataA_del(MyUnionDataA *p);
static __inline__ void MyUnionDataA_delAndSetNull(void *ptr)
{
	MyUnionDataA **p = (MyUnionDataA **)ptr;
	if (p != NULL) { MyUnionDataA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataA_dump(MyUnionDataA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataA_fdump(FILE *fp, MyUnionDataA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyUnionDataA_cmp(MyUnionDataA *a, MyUnionDataA *b);
// MyUnionDataA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueListA
typedef struct MyUnionDataUniqueListA
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataUniqueListA *p);
	Dz1Error (*travel)(struct MyUnionDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataUniqueListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	MyUnionDataA **(*get_array)(struct MyUnionDataUniqueListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataUniqueListA *p, MyUnionDataA *data);
	bool_t (*remove)(struct MyUnionDataUniqueListA *p, MyUnionDataA *key);
	MyUnionDataA *(*extract)(struct MyUnionDataUniqueListA *p, MyUnionDataA *key);
	MyUnionDataA *(*find)(struct MyUnionDataUniqueListA *p, MyUnionDataA *key);
	MyUnionDataA *(*getHead)(struct MyUnionDataUniqueListA *p);
	MyUnionDataA *(*getTail)(struct MyUnionDataUniqueListA *p);
	int (*cmp)(MyUnionDataA *a, MyUnionDataA *b);
} MyUnionDataUniqueListA;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueListA *MyUnionDataUniqueListA_new(Dz1Error *err);
static __inline__ MyUnionDataUniqueListA *MyUnionDataUniqueListA_gen(Dz1Error *err) { return MyUnionDataUniqueListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueListA *MyUnionDataUniqueListA_clone(MyUnionDataUniqueListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueListA_purge(MyUnionDataUniqueListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueListA_del(MyUnionDataUniqueListA *p);
static __inline__ void MyUnionDataUniqueListA_delAndSetNull(void *ptr)
{
	MyUnionDataUniqueListA **p = (MyUnionDataUniqueListA **)ptr;
	if (p != NULL) { MyUnionDataUniqueListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueListA_dump(MyUnionDataUniqueListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueListA_fdump(FILE *fp, MyUnionDataUniqueListA *p, int tab);

// MyUnionDataUniqueListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedListA
typedef struct MyUnionDataOrderedListA
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataOrderedListA *p);
	Dz1Error (*travel)(struct MyUnionDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataOrderedListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	MyUnionDataA **(*get_array)(struct MyUnionDataOrderedListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataOrderedListA *p, MyUnionDataA *data);
	bool_t (*remove)(struct MyUnionDataOrderedListA *p, MyUnionDataA *key);
	MyUnionDataA *(*extract)(struct MyUnionDataOrderedListA *p, MyUnionDataA *key);
	MyUnionDataA *(*find)(struct MyUnionDataOrderedListA *p, MyUnionDataA *key);
	MyUnionDataA *(*getHead)(struct MyUnionDataOrderedListA *p);
	MyUnionDataA *(*getTail)(struct MyUnionDataOrderedListA *p);
	int (*cmp)(MyUnionDataA *a, MyUnionDataA *b);
} MyUnionDataOrderedListA;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedListA *MyUnionDataOrderedListA_new(Dz1Error *err);
static __inline__ MyUnionDataOrderedListA *MyUnionDataOrderedListA_gen(Dz1Error *err) { return MyUnionDataOrderedListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedListA *MyUnionDataOrderedListA_clone(MyUnionDataOrderedListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedListA_purge(MyUnionDataOrderedListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedListA_del(MyUnionDataOrderedListA *p);
static __inline__ void MyUnionDataOrderedListA_delAndSetNull(void *ptr)
{
	MyUnionDataOrderedListA **p = (MyUnionDataOrderedListA **)ptr;
	if (p != NULL) { MyUnionDataOrderedListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedListA_dump(MyUnionDataOrderedListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedListA_fdump(FILE *fp, MyUnionDataOrderedListA *p, int tab);

// MyUnionDataOrderedListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataListA
typedef struct MyUnionDataListA
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataListA *p);
	Dz1Error (*travel)(struct MyUnionDataListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	MyUnionDataA **(*get_array)(struct MyUnionDataListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataListA *p, MyUnionDataA *data);
	bool_t (*remove)(struct MyUnionDataListA *p, MyUnionDataA *ptr);
	MyUnionDataA *(*extract)(struct MyUnionDataListA *p, MyUnionDataA *ptr);
	MyUnionDataA *(*find)(struct MyUnionDataListA *p, MyUnionDataA *key);
	MyUnionDataA *(*getHead)(struct MyUnionDataListA *p);
	MyUnionDataA *(*getTail)(struct MyUnionDataListA *p);
	int (*cmp)(MyUnionDataA *a, MyUnionDataA *b);
} MyUnionDataListA;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataListA *MyUnionDataListA_new(Dz1Error *err);
static __inline__ MyUnionDataListA *MyUnionDataListA_gen(Dz1Error *err) { return MyUnionDataListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataListA *MyUnionDataListA_clone(MyUnionDataListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataListA_purge(MyUnionDataListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataListA_del(MyUnionDataListA *p);
static __inline__ void MyUnionDataListA_delAndSetNull(void *ptr)
{
	MyUnionDataListA **p = (MyUnionDataListA **)ptr;
	if (p != NULL) { MyUnionDataListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataListA_dump(MyUnionDataListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataListA_fdump(FILE *fp, MyUnionDataListA *p, int tab);

// MyUnionDataListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueRefListA
typedef struct MyUnionDataUniqueRefListA
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataUniqueRefListA *p);
	Dz1Error (*travel)(struct MyUnionDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataUniqueRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	MyUnionDataA **(*get_array)(struct MyUnionDataUniqueRefListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataUniqueRefListA *p, MyUnionDataA *data);
	bool_t (*remove)(struct MyUnionDataUniqueRefListA *p, MyUnionDataA *key);
	MyUnionDataA *(*extract)(struct MyUnionDataUniqueRefListA *p, MyUnionDataA *key);
	MyUnionDataA *(*find)(struct MyUnionDataUniqueRefListA *p, MyUnionDataA *key);
	MyUnionDataA *(*getHead)(struct MyUnionDataUniqueRefListA *p);
	MyUnionDataA *(*getTail)(struct MyUnionDataUniqueRefListA *p);
	int (*cmp)(MyUnionDataA *a, MyUnionDataA *b);
} MyUnionDataUniqueRefListA;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueRefListA *MyUnionDataUniqueRefListA_new(Dz1Error *err);
static __inline__ MyUnionDataUniqueRefListA *MyUnionDataUniqueRefListA_gen(Dz1Error *err) { return MyUnionDataUniqueRefListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueRefListA *MyUnionDataUniqueRefListA_clone(MyUnionDataUniqueRefListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefListA_purge(MyUnionDataUniqueRefListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefListA_del(MyUnionDataUniqueRefListA *p);
static __inline__ void MyUnionDataUniqueRefListA_delAndSetNull(void *ptr)
{
	MyUnionDataUniqueRefListA **p = (MyUnionDataUniqueRefListA **)ptr;
	if (p != NULL) { MyUnionDataUniqueRefListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefListA_dump(MyUnionDataUniqueRefListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefListA_fdump(FILE *fp, MyUnionDataUniqueRefListA *p, int tab);

// MyUnionDataUniqueRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedRefListA
typedef struct MyUnionDataOrderedRefListA
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataOrderedRefListA *p);
	Dz1Error (*travel)(struct MyUnionDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataOrderedRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	MyUnionDataA **(*get_array)(struct MyUnionDataOrderedRefListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataOrderedRefListA *p, MyUnionDataA *data);
	bool_t (*remove)(struct MyUnionDataOrderedRefListA *p, MyUnionDataA *key);
	MyUnionDataA *(*extract)(struct MyUnionDataOrderedRefListA *p, MyUnionDataA *key);
	MyUnionDataA *(*find)(struct MyUnionDataOrderedRefListA *p, MyUnionDataA *key);
	MyUnionDataA *(*getHead)(struct MyUnionDataOrderedRefListA *p);
	MyUnionDataA *(*getTail)(struct MyUnionDataOrderedRefListA *p);
	int (*cmp)(MyUnionDataA *a, MyUnionDataA *b);
} MyUnionDataOrderedRefListA;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedRefListA *MyUnionDataOrderedRefListA_new(Dz1Error *err);
static __inline__ MyUnionDataOrderedRefListA *MyUnionDataOrderedRefListA_gen(Dz1Error *err) { return MyUnionDataOrderedRefListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedRefListA *MyUnionDataOrderedRefListA_clone(MyUnionDataOrderedRefListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefListA_purge(MyUnionDataOrderedRefListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefListA_del(MyUnionDataOrderedRefListA *p);
static __inline__ void MyUnionDataOrderedRefListA_delAndSetNull(void *ptr)
{
	MyUnionDataOrderedRefListA **p = (MyUnionDataOrderedRefListA **)ptr;
	if (p != NULL) { MyUnionDataOrderedRefListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefListA_dump(MyUnionDataOrderedRefListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefListA_fdump(FILE *fp, MyUnionDataOrderedRefListA *p, int tab);

// MyUnionDataOrderedRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataRefListA
typedef struct MyUnionDataRefListA
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataRefListA *p);
	Dz1Error (*travel)(struct MyUnionDataRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataRefListA *p, Dz1Error (*func)(void *ptr, MyUnionDataA *entry), void *ptr);
	MyUnionDataA **(*get_array)(struct MyUnionDataRefListA *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataRefListA *p, MyUnionDataA *data);
	bool_t (*remove)(struct MyUnionDataRefListA *p, MyUnionDataA *ptr);
	MyUnionDataA *(*extract)(struct MyUnionDataRefListA *p, MyUnionDataA *ptr);
	MyUnionDataA *(*find)(struct MyUnionDataRefListA *p, MyUnionDataA *key);
	MyUnionDataA *(*getHead)(struct MyUnionDataRefListA *p);
	MyUnionDataA *(*getTail)(struct MyUnionDataRefListA *p);
	int (*cmp)(MyUnionDataA *a, MyUnionDataA *b);
} MyUnionDataRefListA;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataRefListA *MyUnionDataRefListA_new(Dz1Error *err);
static __inline__ MyUnionDataRefListA *MyUnionDataRefListA_gen(Dz1Error *err) { return MyUnionDataRefListA_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataRefListA *MyUnionDataRefListA_clone(MyUnionDataRefListA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefListA_purge(MyUnionDataRefListA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefListA_del(MyUnionDataRefListA *p);
static __inline__ void MyUnionDataRefListA_delAndSetNull(void *ptr)
{
	MyUnionDataRefListA **p = (MyUnionDataRefListA **)ptr;
	if (p != NULL) { MyUnionDataRefListA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefListA_dump(MyUnionDataRefListA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefListA_fdump(FILE *fp, MyUnionDataRefListA *p, int tab);

// MyUnionDataRefListA
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataInfoA
typedef struct MyUnionDataInfoA
{
	MyUnionDataA	**obj_ptr_arr;
	u32_t			  obj_ptr_cnt;
	MyUnionDataA	 *obj_arr;
	u32_t			  obj_cnt;
	u64_t			 *prims_arr;
	u32_t			  prims_cnt;
	u64_t			**primptrs_arr;
	u32_t			  primptrs_cnt;
	s32_t			 *i_val;
} MyUnionDataInfoA;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataInfoA *MyUnionDataInfoA_new(MyUnionDataA **obj_ptr_arr_e_clone, 
															   u32_t obj_ptr_cnt, 
															   MyUnionDataA *obj_arr_e_copy, 
															   u32_t obj_cnt, 
															   u64_t *prims_arr_e_copy, 
															   u32_t prims_cnt, 
															   u64_t **primptrs_arr_e_clone, 
															   u32_t primptrs_cnt, 
															   s32_t *i_val_ref, Dz1Error *err);
static __inline__ MyUnionDataInfoA *MyUnionDataInfoA_gen(Dz1Error *err) { return MyUnionDataInfoA_new(NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyUnionDataInfoA_copy(MyUnionDataInfoA *dst, MyUnionDataInfoA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataInfoA *MyUnionDataInfoA_clone(MyUnionDataInfoA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfoA_purge(MyUnionDataInfoA *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfoA_del(MyUnionDataInfoA *p);
static __inline__ void MyUnionDataInfoA_delAndSetNull(void *ptr)
{
	MyUnionDataInfoA **p = (MyUnionDataInfoA **)ptr;
	if (p) { MyUnionDataInfoA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfoA_dump(MyUnionDataInfoA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfoA_fdump(FILE *fp, MyUnionDataInfoA *p, int tab);
// MyUnionDataInfoA
////////////////////////////////////////////////////////////////////////////////

#endif
