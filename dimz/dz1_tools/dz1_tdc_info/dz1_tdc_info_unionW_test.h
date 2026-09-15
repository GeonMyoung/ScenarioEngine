#ifndef _DZ1_TDC_DZ1_TDC_INFO_UNION_W_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_UNION_W_TEST_H_

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
// MyUnionDataWPresent
typedef enum MyUnionDataWPresent
{
	MyUnionDataWPresent_name,
	MyUnionDataWPresent_val,
	MyUnionDataWPresent_max
} MyUnionDataWPresent;

DZ1_CPPLINK str_t MyUnionDataWPresentStrA(MyUnionDataWPresent v);
DZ1_CPPLINK MyUnionDataWPresent MyUnionDataWPresentFromStrA(str_t str);
DZ1_CPPLINK wstr_t MyUnionDataWPresentStrW(MyUnionDataWPresent v);
DZ1_CPPLINK MyUnionDataWPresent MyUnionDataWPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define MyUnionDataWPresentStr MyUnionDataWPresentStrW
#define MyUnionDataWPresentFromStr MyUnionDataWPresentFromStrW
#else // UNICODE
#define MyUnionDataWPresentStr MyUnionDataWPresentStrA
#define MyUnionDataWPresentFromStr MyUnionDataWPresentFromStrA
#endif // UNICODE
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataWPresent *MyUnionDataWPresent_new(MyUnionDataWPresent *src, Dz1Error *err);
static __inline__ MyUnionDataWPresent *MyUnionDataWPresent_gen(Dz1Error *err) { MyUnionDataWPresent v = MyUnionDataWPresent_max; return MyUnionDataWPresent_new(&v, err); }
#define MyUnionDataWPresent_clone             MyUnionDataWPresent_new
static __inline__ void MyUnionDataWPresent_del(MyUnionDataWPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void MyUnionDataWPresent_delAndSetNull(void *ptr)
{
	MyUnionDataWPresent **p = (MyUnionDataWPresent **)ptr;
	if (p != NULL) { MyUnionDataWPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataWPresentW_dump(MyUnionDataWPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataWPresentW_fdump(FILE *fp, MyUnionDataWPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyUnionDataWPresent_cmp(MyUnionDataWPresent *a, MyUnionDataWPresent *b);
// MyUnionDataWPresent
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataW
typedef struct MyUnionDataW
{
	MyUnionDataWPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1UTF8Str		*name;
		u32_t				 val;
	} x;
} MyUnionDataW;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataW *MyUnionDataW_new(MyUnionDataWPresent present, void *ptr, Dz1Error *err);
static __inline__ MyUnionDataW *MyUnionDataW_gen(Dz1Error *err) { return MyUnionDataW_new(MyUnionDataWPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  MyUnionDataW_copy(MyUnionDataW *dst, MyUnionDataW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataW *MyUnionDataW_clone(MyUnionDataW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataW_purge(MyUnionDataW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataW_del(MyUnionDataW *p);
static __inline__ void MyUnionDataW_delAndSetNull(void *ptr)
{
	MyUnionDataW **p = (MyUnionDataW **)ptr;
	if (p != NULL) { MyUnionDataW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataW_dump(MyUnionDataW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataW_fdump(FILE *fp, MyUnionDataW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyUnionDataW_cmp(MyUnionDataW *a, MyUnionDataW *b);
// MyUnionDataW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueListW
typedef struct MyUnionDataUniqueListW
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataUniqueListW *p);
	Dz1Error (*travel)(struct MyUnionDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataUniqueListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	MyUnionDataW **(*get_array)(struct MyUnionDataUniqueListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataUniqueListW *p, MyUnionDataW *data);
	bool_t (*remove)(struct MyUnionDataUniqueListW *p, MyUnionDataW *key);
	MyUnionDataW *(*extract)(struct MyUnionDataUniqueListW *p, MyUnionDataW *key);
	MyUnionDataW *(*find)(struct MyUnionDataUniqueListW *p, MyUnionDataW *key);
	MyUnionDataW *(*getHead)(struct MyUnionDataUniqueListW *p);
	MyUnionDataW *(*getTail)(struct MyUnionDataUniqueListW *p);
	int (*cmp)(MyUnionDataW *a, MyUnionDataW *b);
} MyUnionDataUniqueListW;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueListW *MyUnionDataUniqueListW_new(Dz1Error *err);
static __inline__ MyUnionDataUniqueListW *MyUnionDataUniqueListW_gen(Dz1Error *err) { return MyUnionDataUniqueListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueListW *MyUnionDataUniqueListW_clone(MyUnionDataUniqueListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueListW_purge(MyUnionDataUniqueListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueListW_del(MyUnionDataUniqueListW *p);
static __inline__ void MyUnionDataUniqueListW_delAndSetNull(void *ptr)
{
	MyUnionDataUniqueListW **p = (MyUnionDataUniqueListW **)ptr;
	if (p != NULL) { MyUnionDataUniqueListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueListW_dump(MyUnionDataUniqueListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueListW_fdump(FILE *fp, MyUnionDataUniqueListW *p, int tab);

// MyUnionDataUniqueListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedListW
typedef struct MyUnionDataOrderedListW
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataOrderedListW *p);
	Dz1Error (*travel)(struct MyUnionDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataOrderedListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	MyUnionDataW **(*get_array)(struct MyUnionDataOrderedListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataOrderedListW *p, MyUnionDataW *data);
	bool_t (*remove)(struct MyUnionDataOrderedListW *p, MyUnionDataW *key);
	MyUnionDataW *(*extract)(struct MyUnionDataOrderedListW *p, MyUnionDataW *key);
	MyUnionDataW *(*find)(struct MyUnionDataOrderedListW *p, MyUnionDataW *key);
	MyUnionDataW *(*getHead)(struct MyUnionDataOrderedListW *p);
	MyUnionDataW *(*getTail)(struct MyUnionDataOrderedListW *p);
	int (*cmp)(MyUnionDataW *a, MyUnionDataW *b);
} MyUnionDataOrderedListW;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedListW *MyUnionDataOrderedListW_new(Dz1Error *err);
static __inline__ MyUnionDataOrderedListW *MyUnionDataOrderedListW_gen(Dz1Error *err) { return MyUnionDataOrderedListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedListW *MyUnionDataOrderedListW_clone(MyUnionDataOrderedListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedListW_purge(MyUnionDataOrderedListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedListW_del(MyUnionDataOrderedListW *p);
static __inline__ void MyUnionDataOrderedListW_delAndSetNull(void *ptr)
{
	MyUnionDataOrderedListW **p = (MyUnionDataOrderedListW **)ptr;
	if (p != NULL) { MyUnionDataOrderedListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedListW_dump(MyUnionDataOrderedListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedListW_fdump(FILE *fp, MyUnionDataOrderedListW *p, int tab);

// MyUnionDataOrderedListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataListW
typedef struct MyUnionDataListW
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataListW *p);
	Dz1Error (*travel)(struct MyUnionDataListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	MyUnionDataW **(*get_array)(struct MyUnionDataListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataListW *p, MyUnionDataW *data);
	bool_t (*remove)(struct MyUnionDataListW *p, MyUnionDataW *ptr);
	MyUnionDataW *(*extract)(struct MyUnionDataListW *p, MyUnionDataW *ptr);
	MyUnionDataW *(*find)(struct MyUnionDataListW *p, MyUnionDataW *key);
	MyUnionDataW *(*getHead)(struct MyUnionDataListW *p);
	MyUnionDataW *(*getTail)(struct MyUnionDataListW *p);
	int (*cmp)(MyUnionDataW *a, MyUnionDataW *b);
} MyUnionDataListW;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataListW *MyUnionDataListW_new(Dz1Error *err);
static __inline__ MyUnionDataListW *MyUnionDataListW_gen(Dz1Error *err) { return MyUnionDataListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataListW *MyUnionDataListW_clone(MyUnionDataListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataListW_purge(MyUnionDataListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataListW_del(MyUnionDataListW *p);
static __inline__ void MyUnionDataListW_delAndSetNull(void *ptr)
{
	MyUnionDataListW **p = (MyUnionDataListW **)ptr;
	if (p != NULL) { MyUnionDataListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataListW_dump(MyUnionDataListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataListW_fdump(FILE *fp, MyUnionDataListW *p, int tab);

// MyUnionDataListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueRefListW
typedef struct MyUnionDataUniqueRefListW
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataUniqueRefListW *p);
	Dz1Error (*travel)(struct MyUnionDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataUniqueRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	MyUnionDataW **(*get_array)(struct MyUnionDataUniqueRefListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataUniqueRefListW *p, MyUnionDataW *data);
	bool_t (*remove)(struct MyUnionDataUniqueRefListW *p, MyUnionDataW *key);
	MyUnionDataW *(*extract)(struct MyUnionDataUniqueRefListW *p, MyUnionDataW *key);
	MyUnionDataW *(*find)(struct MyUnionDataUniqueRefListW *p, MyUnionDataW *key);
	MyUnionDataW *(*getHead)(struct MyUnionDataUniqueRefListW *p);
	MyUnionDataW *(*getTail)(struct MyUnionDataUniqueRefListW *p);
	int (*cmp)(MyUnionDataW *a, MyUnionDataW *b);
} MyUnionDataUniqueRefListW;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueRefListW *MyUnionDataUniqueRefListW_new(Dz1Error *err);
static __inline__ MyUnionDataUniqueRefListW *MyUnionDataUniqueRefListW_gen(Dz1Error *err) { return MyUnionDataUniqueRefListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueRefListW *MyUnionDataUniqueRefListW_clone(MyUnionDataUniqueRefListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefListW_purge(MyUnionDataUniqueRefListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefListW_del(MyUnionDataUniqueRefListW *p);
static __inline__ void MyUnionDataUniqueRefListW_delAndSetNull(void *ptr)
{
	MyUnionDataUniqueRefListW **p = (MyUnionDataUniqueRefListW **)ptr;
	if (p != NULL) { MyUnionDataUniqueRefListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefListW_dump(MyUnionDataUniqueRefListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefListW_fdump(FILE *fp, MyUnionDataUniqueRefListW *p, int tab);

// MyUnionDataUniqueRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedRefListW
typedef struct MyUnionDataOrderedRefListW
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataOrderedRefListW *p);
	Dz1Error (*travel)(struct MyUnionDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataOrderedRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	MyUnionDataW **(*get_array)(struct MyUnionDataOrderedRefListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataOrderedRefListW *p, MyUnionDataW *data);
	bool_t (*remove)(struct MyUnionDataOrderedRefListW *p, MyUnionDataW *key);
	MyUnionDataW *(*extract)(struct MyUnionDataOrderedRefListW *p, MyUnionDataW *key);
	MyUnionDataW *(*find)(struct MyUnionDataOrderedRefListW *p, MyUnionDataW *key);
	MyUnionDataW *(*getHead)(struct MyUnionDataOrderedRefListW *p);
	MyUnionDataW *(*getTail)(struct MyUnionDataOrderedRefListW *p);
	int (*cmp)(MyUnionDataW *a, MyUnionDataW *b);
} MyUnionDataOrderedRefListW;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedRefListW *MyUnionDataOrderedRefListW_new(Dz1Error *err);
static __inline__ MyUnionDataOrderedRefListW *MyUnionDataOrderedRefListW_gen(Dz1Error *err) { return MyUnionDataOrderedRefListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedRefListW *MyUnionDataOrderedRefListW_clone(MyUnionDataOrderedRefListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefListW_purge(MyUnionDataOrderedRefListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefListW_del(MyUnionDataOrderedRefListW *p);
static __inline__ void MyUnionDataOrderedRefListW_delAndSetNull(void *ptr)
{
	MyUnionDataOrderedRefListW **p = (MyUnionDataOrderedRefListW **)ptr;
	if (p != NULL) { MyUnionDataOrderedRefListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefListW_dump(MyUnionDataOrderedRefListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefListW_fdump(FILE *fp, MyUnionDataOrderedRefListW *p, int tab);

// MyUnionDataOrderedRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataRefListW
typedef struct MyUnionDataRefListW
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataRefListW *p);
	Dz1Error (*travel)(struct MyUnionDataRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataRefListW *p, Dz1Error (*func)(void *ptr, MyUnionDataW *entry), void *ptr);
	MyUnionDataW **(*get_array)(struct MyUnionDataRefListW *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataRefListW *p, MyUnionDataW *data);
	bool_t (*remove)(struct MyUnionDataRefListW *p, MyUnionDataW *ptr);
	MyUnionDataW *(*extract)(struct MyUnionDataRefListW *p, MyUnionDataW *ptr);
	MyUnionDataW *(*find)(struct MyUnionDataRefListW *p, MyUnionDataW *key);
	MyUnionDataW *(*getHead)(struct MyUnionDataRefListW *p);
	MyUnionDataW *(*getTail)(struct MyUnionDataRefListW *p);
	int (*cmp)(MyUnionDataW *a, MyUnionDataW *b);
} MyUnionDataRefListW;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataRefListW *MyUnionDataRefListW_new(Dz1Error *err);
static __inline__ MyUnionDataRefListW *MyUnionDataRefListW_gen(Dz1Error *err) { return MyUnionDataRefListW_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataRefListW *MyUnionDataRefListW_clone(MyUnionDataRefListW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefListW_purge(MyUnionDataRefListW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefListW_del(MyUnionDataRefListW *p);
static __inline__ void MyUnionDataRefListW_delAndSetNull(void *ptr)
{
	MyUnionDataRefListW **p = (MyUnionDataRefListW **)ptr;
	if (p != NULL) { MyUnionDataRefListW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefListW_dump(MyUnionDataRefListW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefListW_fdump(FILE *fp, MyUnionDataRefListW *p, int tab);

// MyUnionDataRefListW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// MyUnionDataInfoW
typedef struct MyUnionDataInfoW
{
	MyUnionDataW	**obj_ptr_arr;
	u32_t			  obj_ptr_cnt;
	MyUnionDataW	 *obj_arr;
	u32_t			  obj_cnt;
	u64_t			 *prims_arr;
	u32_t			  prims_cnt;
	u64_t			**primptrs_arr;
	u32_t			  primptrs_cnt;
	s32_t			 *i_val;
} MyUnionDataInfoW;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataInfoW *MyUnionDataInfoW_new(MyUnionDataW **obj_ptr_arr_e_clone, 
															   u32_t obj_ptr_cnt, 
															   MyUnionDataW *obj_arr_e_copy, 
															   u32_t obj_cnt, 
															   u64_t *prims_arr_e_copy, 
															   u32_t prims_cnt, 
															   u64_t **primptrs_arr_e_clone, 
															   u32_t primptrs_cnt, 
															   s32_t *i_val_ref, Dz1Error *err);
static __inline__ MyUnionDataInfoW *MyUnionDataInfoW_gen(Dz1Error *err) { return MyUnionDataInfoW_new(NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyUnionDataInfoW_copy(MyUnionDataInfoW *dst, MyUnionDataInfoW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataInfoW *MyUnionDataInfoW_clone(MyUnionDataInfoW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfoW_purge(MyUnionDataInfoW *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfoW_del(MyUnionDataInfoW *p);
static __inline__ void MyUnionDataInfoW_delAndSetNull(void *ptr)
{
	MyUnionDataInfoW **p = (MyUnionDataInfoW **)ptr;
	if (p) { MyUnionDataInfoW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfoW_dump(MyUnionDataInfoW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfoW_fdump(FILE *fp, MyUnionDataInfoW *p, int tab);
// MyUnionDataInfoW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#endif
