#ifndef _DZ1_TDC_DZ1_TDC_INFO_UNION_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_UNION_TEST_H_

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
// MyUnionDataPresent
typedef enum MyUnionDataPresent
{
	MyUnionDataPresent_name,
	MyUnionDataPresent_val,
	MyUnionDataPresent_max
} MyUnionDataPresent;

DZ1_CPPLINK str_t MyUnionDataPresentStrA(MyUnionDataPresent v);
DZ1_CPPLINK MyUnionDataPresent MyUnionDataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t MyUnionDataPresentStrW(MyUnionDataPresent v);
DZ1_CPPLINK MyUnionDataPresent MyUnionDataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define MyUnionDataPresentStr MyUnionDataPresentStrW
#define MyUnionDataPresentFromStr MyUnionDataPresentFromStrW
#else // UNICODE
#define MyUnionDataPresentStr MyUnionDataPresentStrA
#define MyUnionDataPresentFromStr MyUnionDataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define MyUnionDataPresentStr MyUnionDataPresentStrA
#define MyUnionDataPresentFromStr MyUnionDataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataPresent *MyUnionDataPresent_new(MyUnionDataPresent *src, Dz1Error *err);
static __inline__ MyUnionDataPresent *MyUnionDataPresent_gen(Dz1Error *err) { MyUnionDataPresent v = MyUnionDataPresent_max; return MyUnionDataPresent_new(&v, err); }
#define MyUnionDataPresent_clone             MyUnionDataPresent_new
static __inline__ void MyUnionDataPresent_del(MyUnionDataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void MyUnionDataPresent_delAndSetNull(void *ptr)
{
	MyUnionDataPresent **p = (MyUnionDataPresent **)ptr;
	if (p != NULL) { MyUnionDataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataPresent_dump(MyUnionDataPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataPresent_fdump(FILE *fp, MyUnionDataPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyUnionDataPresent_cmp(MyUnionDataPresent *a, MyUnionDataPresent *b);
// MyUnionDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionData
typedef struct MyUnionData
{
	MyUnionDataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1UTF8Str		*name;
		u32_t				 val;
	} x;
} MyUnionData;

DZ1_CPPLINK DZ1_DLLPORT MyUnionData *MyUnionData_new(MyUnionDataPresent present, void *ptr, Dz1Error *err);
static __inline__ MyUnionData *MyUnionData_gen(Dz1Error *err) { return MyUnionData_new(MyUnionDataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  MyUnionData_copy(MyUnionData *dst, MyUnionData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnionData *MyUnionData_clone(MyUnionData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionData_purge(MyUnionData *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionData_del(MyUnionData *p);
static __inline__ void MyUnionData_delAndSetNull(void *ptr)
{
	MyUnionData **p = (MyUnionData **)ptr;
	if (p != NULL) { MyUnionData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionData_dump(MyUnionData *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionData_fdump(FILE *fp, MyUnionData *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyUnionData_cmp(MyUnionData *a, MyUnionData *b);
// MyUnionData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueList
typedef struct MyUnionDataUniqueList
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataUniqueList *p);
	Dz1Error (*travel)(struct MyUnionDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataUniqueList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	MyUnionData **(*get_array)(struct MyUnionDataUniqueList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataUniqueList *p, MyUnionData *data);
	bool_t (*remove)(struct MyUnionDataUniqueList *p, MyUnionData *key);
	MyUnionData *(*extract)(struct MyUnionDataUniqueList *p, MyUnionData *key);
	MyUnionData *(*find)(struct MyUnionDataUniqueList *p, MyUnionData *key);
	MyUnionData *(*getHead)(struct MyUnionDataUniqueList *p);
	MyUnionData *(*getTail)(struct MyUnionDataUniqueList *p);
	int (*cmp)(MyUnionData *a, MyUnionData *b);
} MyUnionDataUniqueList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueList *MyUnionDataUniqueList_new(Dz1Error *err);
static __inline__ MyUnionDataUniqueList *MyUnionDataUniqueList_gen(Dz1Error *err) { return MyUnionDataUniqueList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueList *MyUnionDataUniqueList_clone(MyUnionDataUniqueList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueList_purge(MyUnionDataUniqueList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueList_del(MyUnionDataUniqueList *p);
static __inline__ void MyUnionDataUniqueList_delAndSetNull(void *ptr)
{
	MyUnionDataUniqueList **p = (MyUnionDataUniqueList **)ptr;
	if (p != NULL) { MyUnionDataUniqueList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueList_dump(MyUnionDataUniqueList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueList_fdump(FILE *fp, MyUnionDataUniqueList *p, int tab);

// MyUnionDataUniqueList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedList
typedef struct MyUnionDataOrderedList
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataOrderedList *p);
	Dz1Error (*travel)(struct MyUnionDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataOrderedList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	MyUnionData **(*get_array)(struct MyUnionDataOrderedList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataOrderedList *p, MyUnionData *data);
	bool_t (*remove)(struct MyUnionDataOrderedList *p, MyUnionData *key);
	MyUnionData *(*extract)(struct MyUnionDataOrderedList *p, MyUnionData *key);
	MyUnionData *(*find)(struct MyUnionDataOrderedList *p, MyUnionData *key);
	MyUnionData *(*getHead)(struct MyUnionDataOrderedList *p);
	MyUnionData *(*getTail)(struct MyUnionDataOrderedList *p);
	int (*cmp)(MyUnionData *a, MyUnionData *b);
} MyUnionDataOrderedList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedList *MyUnionDataOrderedList_new(Dz1Error *err);
static __inline__ MyUnionDataOrderedList *MyUnionDataOrderedList_gen(Dz1Error *err) { return MyUnionDataOrderedList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedList *MyUnionDataOrderedList_clone(MyUnionDataOrderedList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedList_purge(MyUnionDataOrderedList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedList_del(MyUnionDataOrderedList *p);
static __inline__ void MyUnionDataOrderedList_delAndSetNull(void *ptr)
{
	MyUnionDataOrderedList **p = (MyUnionDataOrderedList **)ptr;
	if (p != NULL) { MyUnionDataOrderedList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedList_dump(MyUnionDataOrderedList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedList_fdump(FILE *fp, MyUnionDataOrderedList *p, int tab);

// MyUnionDataOrderedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataList
typedef struct MyUnionDataList
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataList *p);
	Dz1Error (*travel)(struct MyUnionDataList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	MyUnionData **(*get_array)(struct MyUnionDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataList *p, MyUnionData *data);
	bool_t (*remove)(struct MyUnionDataList *p, MyUnionData *ptr);
	MyUnionData *(*extract)(struct MyUnionDataList *p, MyUnionData *ptr);
	MyUnionData *(*find)(struct MyUnionDataList *p, MyUnionData *key);
	MyUnionData *(*getHead)(struct MyUnionDataList *p);
	MyUnionData *(*getTail)(struct MyUnionDataList *p);
	int (*cmp)(MyUnionData *a, MyUnionData *b);
} MyUnionDataList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataList *MyUnionDataList_new(Dz1Error *err);
static __inline__ MyUnionDataList *MyUnionDataList_gen(Dz1Error *err) { return MyUnionDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataList *MyUnionDataList_clone(MyUnionDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataList_purge(MyUnionDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataList_del(MyUnionDataList *p);
static __inline__ void MyUnionDataList_delAndSetNull(void *ptr)
{
	MyUnionDataList **p = (MyUnionDataList **)ptr;
	if (p != NULL) { MyUnionDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataList_dump(MyUnionDataList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataList_fdump(FILE *fp, MyUnionDataList *p, int tab);

// MyUnionDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataUniqueRefList
typedef struct MyUnionDataUniqueRefList
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataUniqueRefList *p);
	Dz1Error (*travel)(struct MyUnionDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataUniqueRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	MyUnionData **(*get_array)(struct MyUnionDataUniqueRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataUniqueRefList *p, MyUnionData *data);
	bool_t (*remove)(struct MyUnionDataUniqueRefList *p, MyUnionData *key);
	MyUnionData *(*extract)(struct MyUnionDataUniqueRefList *p, MyUnionData *key);
	MyUnionData *(*find)(struct MyUnionDataUniqueRefList *p, MyUnionData *key);
	MyUnionData *(*getHead)(struct MyUnionDataUniqueRefList *p);
	MyUnionData *(*getTail)(struct MyUnionDataUniqueRefList *p);
	int (*cmp)(MyUnionData *a, MyUnionData *b);
} MyUnionDataUniqueRefList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueRefList *MyUnionDataUniqueRefList_new(Dz1Error *err);
static __inline__ MyUnionDataUniqueRefList *MyUnionDataUniqueRefList_gen(Dz1Error *err) { return MyUnionDataUniqueRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataUniqueRefList *MyUnionDataUniqueRefList_clone(MyUnionDataUniqueRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefList_purge(MyUnionDataUniqueRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefList_del(MyUnionDataUniqueRefList *p);
static __inline__ void MyUnionDataUniqueRefList_delAndSetNull(void *ptr)
{
	MyUnionDataUniqueRefList **p = (MyUnionDataUniqueRefList **)ptr;
	if (p != NULL) { MyUnionDataUniqueRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefList_dump(MyUnionDataUniqueRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataUniqueRefList_fdump(FILE *fp, MyUnionDataUniqueRefList *p, int tab);

// MyUnionDataUniqueRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataOrderedRefList
typedef struct MyUnionDataOrderedRefList
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataOrderedRefList *p);
	Dz1Error (*travel)(struct MyUnionDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataOrderedRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	MyUnionData **(*get_array)(struct MyUnionDataOrderedRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataOrderedRefList *p, MyUnionData *data);
	bool_t (*remove)(struct MyUnionDataOrderedRefList *p, MyUnionData *key);
	MyUnionData *(*extract)(struct MyUnionDataOrderedRefList *p, MyUnionData *key);
	MyUnionData *(*find)(struct MyUnionDataOrderedRefList *p, MyUnionData *key);
	MyUnionData *(*getHead)(struct MyUnionDataOrderedRefList *p);
	MyUnionData *(*getTail)(struct MyUnionDataOrderedRefList *p);
	int (*cmp)(MyUnionData *a, MyUnionData *b);
} MyUnionDataOrderedRefList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedRefList *MyUnionDataOrderedRefList_new(Dz1Error *err);
static __inline__ MyUnionDataOrderedRefList *MyUnionDataOrderedRefList_gen(Dz1Error *err) { return MyUnionDataOrderedRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataOrderedRefList *MyUnionDataOrderedRefList_clone(MyUnionDataOrderedRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefList_purge(MyUnionDataOrderedRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefList_del(MyUnionDataOrderedRefList *p);
static __inline__ void MyUnionDataOrderedRefList_delAndSetNull(void *ptr)
{
	MyUnionDataOrderedRefList **p = (MyUnionDataOrderedRefList **)ptr;
	if (p != NULL) { MyUnionDataOrderedRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefList_dump(MyUnionDataOrderedRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataOrderedRefList_fdump(FILE *fp, MyUnionDataOrderedRefList *p, int tab);

// MyUnionDataOrderedRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataRefList
typedef struct MyUnionDataRefList
{
	void *storage;
	unsigned int (*count)(struct MyUnionDataRefList *p);
	Dz1Error (*travel)(struct MyUnionDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionDataRefList *p, Dz1Error (*func)(void *ptr, MyUnionData *entry), void *ptr);
	MyUnionData **(*get_array)(struct MyUnionDataRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionDataRefList *p, MyUnionData *data);
	bool_t (*remove)(struct MyUnionDataRefList *p, MyUnionData *ptr);
	MyUnionData *(*extract)(struct MyUnionDataRefList *p, MyUnionData *ptr);
	MyUnionData *(*find)(struct MyUnionDataRefList *p, MyUnionData *key);
	MyUnionData *(*getHead)(struct MyUnionDataRefList *p);
	MyUnionData *(*getTail)(struct MyUnionDataRefList *p);
	int (*cmp)(MyUnionData *a, MyUnionData *b);
} MyUnionDataRefList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataRefList *MyUnionDataRefList_new(Dz1Error *err);
static __inline__ MyUnionDataRefList *MyUnionDataRefList_gen(Dz1Error *err) { return MyUnionDataRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataRefList *MyUnionDataRefList_clone(MyUnionDataRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefList_purge(MyUnionDataRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefList_del(MyUnionDataRefList *p);
static __inline__ void MyUnionDataRefList_delAndSetNull(void *ptr)
{
	MyUnionDataRefList **p = (MyUnionDataRefList **)ptr;
	if (p != NULL) { MyUnionDataRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefList_dump(MyUnionDataRefList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataRefList_fdump(FILE *fp, MyUnionDataRefList *p, int tab);

// MyUnionDataRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionDataInfo
typedef struct MyUnionDataInfo
{
	MyUnionData		**obj_ptr_arr;
	u32_t			  obj_ptr_cnt;
	MyUnionData		 *obj_arr;
	u32_t			  obj_cnt;
	u64_t			 *prims_arr;
	u32_t			  prims_cnt;
	u64_t			**primptrs_arr;
	u32_t			  primptrs_cnt;
	s32_t			 *i_val;
} MyUnionDataInfo;

DZ1_CPPLINK DZ1_DLLPORT MyUnionDataInfo *MyUnionDataInfo_new(MyUnionData **obj_ptr_arr_e_clone, 
															 u32_t obj_ptr_cnt, 
															 MyUnionData *obj_arr_e_copy, 
															 u32_t obj_cnt, 
															 u64_t *prims_arr_e_copy, 
															 u32_t prims_cnt, 
															 u64_t **primptrs_arr_e_clone, 
															 u32_t primptrs_cnt, 
															 s32_t *i_val_ref, Dz1Error *err);
static __inline__ MyUnionDataInfo *MyUnionDataInfo_gen(Dz1Error *err) { return MyUnionDataInfo_new(NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyUnionDataInfo_copy(MyUnionDataInfo *dst, MyUnionDataInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnionDataInfo *MyUnionDataInfo_clone(MyUnionDataInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfo_purge(MyUnionDataInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfo_del(MyUnionDataInfo *p);
static __inline__ void MyUnionDataInfo_delAndSetNull(void *ptr)
{
	MyUnionDataInfo **p = (MyUnionDataInfo **)ptr;
	if (p) { MyUnionDataInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfo_dump(MyUnionDataInfo *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionDataInfo_fdump(FILE *fp, MyUnionDataInfo *p, int tab);
// MyUnionDataInfo
////////////////////////////////////////////////////////////////////////////////

#endif
