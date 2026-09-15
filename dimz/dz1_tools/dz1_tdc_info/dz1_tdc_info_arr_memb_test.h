#ifndef _DZ1_TDC_DZ1_TDC_INFO_ARR_MEMB_TEST_H_
#define _DZ1_TDC_DZ1_TDC_INFO_ARR_MEMB_TEST_H_

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
// TestDataType
typedef struct TestDataType
{
	s32_t		id;
} TestDataType;

DZ1_CPPLINK DZ1_DLLPORT TestDataType *TestDataType_new(s32_t id, Dz1Error *err);
static __inline__ TestDataType *TestDataType_gen(Dz1Error *err) { return TestDataType_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TestDataType_copy(TestDataType *dst, TestDataType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TestDataType *TestDataType_clone(TestDataType *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TestDataType_purge(TestDataType *p);
DZ1_CPPLINK DZ1_DLLPORT void TestDataType_del(TestDataType *p);
static __inline__ void TestDataType_delAndSetNull(void *ptr)
{
	TestDataType **p = (TestDataType **)ptr;
	if (p) { TestDataType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TestDataTypeA_dump(TestDataType *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void TestDataTypeA_fdump(FILE *fp, TestDataType *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void TestDataTypeW_dump(TestDataType *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void TestDataTypeW_fdump(FILE *fp, TestDataType *p, int tab);
#ifdef UNICODE
#define TestDataType_dump TestDataTypeW_dump
#define TestDataType_fdump TestDataTypeW_fdump
#else //  UNICODE
#define TestDataType_dump TestDataTypeA_dump
#define TestDataType_fdump TestDataTypeA_fdump
#endif //  UNICODE
static __inline__ void TestDataTypeX_dump(TestDataType *p, int tab) { DZ1_DUMP(TestDataType, p, tab); }
static __inline__ void TestDataTypeX_fdump(FILE *fp, TestDataType *p, int tab) { DZ1_FDUMP(fp, TestDataType, p, tab); }
#else // UNIX_SYSTEM
#define TestDataType_dump TestDataTypeA_dump
#define TestDataTypeX_dump TestDataTypeA_dump
#define TestDataType_fdump TestDataTypeA_fdump
#define TestDataTypeX_fdump TestDataTypeA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int TestDataType_cmp(TestDataType *a, TestDataType *b); 
// TestDataType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData0
typedef struct ArrayMemberData0
{
	u32_t		*int_arr1;
} ArrayMemberData0;

DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData0 *ArrayMemberData0_new(u32_t *int_arr1_e_copy, Dz1Error *err);
static __inline__ ArrayMemberData0 *ArrayMemberData0_gen(Dz1Error *err) { return ArrayMemberData0_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ArrayMemberData0_copy(ArrayMemberData0 *dst, ArrayMemberData0 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData0 *ArrayMemberData0_clone(ArrayMemberData0 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData0_purge(ArrayMemberData0 *p);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData0_del(ArrayMemberData0 *p);
static __inline__ void ArrayMemberData0_delAndSetNull(void *ptr)
{
	ArrayMemberData0 **p = (ArrayMemberData0 **)ptr;
	if (p) { ArrayMemberData0_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData0_dump(ArrayMemberData0 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData0_fdump(FILE *fp, ArrayMemberData0 *p, int tab);
// ArrayMemberData0
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData1
typedef struct ArrayMemberData1
{
	u32_t				 *int_arr1;
	u32_t				  int_cnt1;
	u32_t				**int_arr2;
	u32_t				  int_cnt2;
	u32_t				**int_arr3;
	u32_t				  int_cnt3;
	u32_t				**int_arr4;
	u32_t				  int_cnt4;
	u32_t				**int_arr5;
	u32_t				  int_cnt5;
	TestDataType		 *data_arr1;
	u32_t				  data_cnt1;
	TestDataType		**data_arr2;
	u32_t				  data_cnt2;
	TestDataType		**data_arr3;
	u32_t				  data_cnt3;
	TestDataType		**data_arr4;
	u32_t				  data_cnt4;
	TestDataType		**data_arr5;
	u32_t				  data_cnt5;
	Dz1Asn1UTF8Str		 *utf8_arr1;
	u32_t				  utf8_cnt1;
	Dz1Asn1UTF8Str		**utf8_arr2;
	u32_t				  utf8_cnt2;
	Dz1Asn1UTF8Str		**utf8_arr3;
	u32_t				  utf8_cnt3;
	Dz1Asn1UTF8Str		**utf8_arr4;
	u32_t				  utf8_cnt4;
	Dz1Asn1UTF8Str		**utf8_arr5;
	u32_t				  utf8_cnt5;
} ArrayMemberData1;

DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData1 *ArrayMemberData1_new(u32_t *int_arr1_e_copy, 
															   u32_t int_cnt1, 
															   u32_t **int_arr2_e_clone, 
															   u32_t int_cnt2, 
															   u32_t **int_arr3_e_ref, 
															   u32_t int_cnt3, 
															   u32_t **int_arr4_ref, 
															   u32_t int_cnt4, 
															   u32_t **int_arr5_ref, 
															   u32_t int_cnt5, 
															   TestDataType *data_arr1_e_copy, 
															   u32_t data_cnt1, 
															   TestDataType **data_arr2_e_clone, 
															   u32_t data_cnt2, 
															   TestDataType **data_arr3_e_ref, 
															   u32_t data_cnt3, 
															   TestDataType **data_arr4_ref, 
															   u32_t data_cnt4, 
															   TestDataType **data_arr5_ref, 
															   u32_t data_cnt5, 
															   Dz1Asn1UTF8Str *utf8_arr1_e_copy, 
															   u32_t utf8_cnt1, 
															   Dz1Asn1UTF8Str **utf8_arr2_e_clone, 
															   u32_t utf8_cnt2, 
															   Dz1Asn1UTF8Str **utf8_arr3_e_ref, 
															   u32_t utf8_cnt3, 
															   Dz1Asn1UTF8Str **utf8_arr4_ref, 
															   u32_t utf8_cnt4, 
															   Dz1Asn1UTF8Str **utf8_arr5_ref, 
															   u32_t utf8_cnt5, Dz1Error *err);
static __inline__ ArrayMemberData1 *ArrayMemberData1_gen(Dz1Error *err) { return ArrayMemberData1_new(NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ArrayMemberData1_copy(ArrayMemberData1 *dst, ArrayMemberData1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData1 *ArrayMemberData1_clone(ArrayMemberData1 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData1_purge(ArrayMemberData1 *p);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData1_del(ArrayMemberData1 *p);
static __inline__ void ArrayMemberData1_delAndSetNull(void *ptr)
{
	ArrayMemberData1 **p = (ArrayMemberData1 **)ptr;
	if (p) { ArrayMemberData1_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData1A_dump(ArrayMemberData1 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData1A_fdump(FILE *fp, ArrayMemberData1 *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData1W_dump(ArrayMemberData1 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData1W_fdump(FILE *fp, ArrayMemberData1 *p, int tab);
#ifdef UNICODE
#define ArrayMemberData1_dump ArrayMemberData1W_dump
#define ArrayMemberData1_fdump ArrayMemberData1W_fdump
#else //  UNICODE
#define ArrayMemberData1_dump ArrayMemberData1A_dump
#define ArrayMemberData1_fdump ArrayMemberData1A_fdump
#endif //  UNICODE
static __inline__ void ArrayMemberData1X_dump(ArrayMemberData1 *p, int tab) { DZ1_DUMP(ArrayMemberData1, p, tab); }
static __inline__ void ArrayMemberData1X_fdump(FILE *fp, ArrayMemberData1 *p, int tab) { DZ1_FDUMP(fp, ArrayMemberData1, p, tab); }
#else // UNIX_SYSTEM
#define ArrayMemberData1_dump ArrayMemberData1A_dump
#define ArrayMemberData1X_dump ArrayMemberData1A_dump
#define ArrayMemberData1_fdump ArrayMemberData1A_fdump
#define ArrayMemberData1X_fdump ArrayMemberData1A_fdump
#endif // UNIX_SYSTEM
// ArrayMemberData1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData2
typedef struct ArrayMemberData2
{
	u32_t				 *int_arr1;
	u32_t				**int_arr2;
	u32_t				**int_arr3;
	u32_t				**int_arr4;
	u32_t				**int_arr5;
	TestDataType		 *data_arr1;
	TestDataType		**data_arr2;
	TestDataType		**data_arr3;
	TestDataType		**data_arr4;
	TestDataType		**data_arr5;
	Dz1Asn1UTF8Str		 *u8_arr1;
	Dz1Asn1UTF8Str		**u8_arr2;
	Dz1Asn1UTF8Str		**u8_arr3;
	Dz1Asn1UTF8Str		**u8_arr4;
	Dz1Asn1UTF8Str		**u8_arr5;
} ArrayMemberData2;

DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData2 *ArrayMemberData2_new(u32_t *int_arr1_e_copy, 
															   u32_t **int_arr2_e_clone, 
															   u32_t **int_arr3_e_ref, 
															   u32_t **int_arr4_ref, 
															   u32_t **int_arr5_ref, 
															   TestDataType *data_arr1_e_copy, 
															   TestDataType **data_arr2_e_clone, 
															   TestDataType **data_arr3_e_ref, 
															   TestDataType **data_arr4_ref, 
															   TestDataType **data_arr5_ref, 
															   Dz1Asn1UTF8Str *u8_arr1_e_copy, 
															   Dz1Asn1UTF8Str **u8_arr2_e_clone, 
															   Dz1Asn1UTF8Str **u8_arr3_e_ref, 
															   Dz1Asn1UTF8Str **u8_arr4_ref, 
															   Dz1Asn1UTF8Str **u8_arr5_ref, Dz1Error *err);
static __inline__ ArrayMemberData2 *ArrayMemberData2_gen(Dz1Error *err) { return ArrayMemberData2_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ArrayMemberData2_copy(ArrayMemberData2 *dst, ArrayMemberData2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData2 *ArrayMemberData2_clone(ArrayMemberData2 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData2_purge(ArrayMemberData2 *p);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData2_del(ArrayMemberData2 *p);
static __inline__ void ArrayMemberData2_delAndSetNull(void *ptr)
{
	ArrayMemberData2 **p = (ArrayMemberData2 **)ptr;
	if (p) { ArrayMemberData2_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData2A_dump(ArrayMemberData2 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData2A_fdump(FILE *fp, ArrayMemberData2 *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData2W_dump(ArrayMemberData2 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData2W_fdump(FILE *fp, ArrayMemberData2 *p, int tab);
#ifdef UNICODE
#define ArrayMemberData2_dump ArrayMemberData2W_dump
#define ArrayMemberData2_fdump ArrayMemberData2W_fdump
#else //  UNICODE
#define ArrayMemberData2_dump ArrayMemberData2A_dump
#define ArrayMemberData2_fdump ArrayMemberData2A_fdump
#endif //  UNICODE
static __inline__ void ArrayMemberData2X_dump(ArrayMemberData2 *p, int tab) { DZ1_DUMP(ArrayMemberData2, p, tab); }
static __inline__ void ArrayMemberData2X_fdump(FILE *fp, ArrayMemberData2 *p, int tab) { DZ1_FDUMP(fp, ArrayMemberData2, p, tab); }
#else // UNIX_SYSTEM
#define ArrayMemberData2_dump ArrayMemberData2A_dump
#define ArrayMemberData2X_dump ArrayMemberData2A_dump
#define ArrayMemberData2_fdump ArrayMemberData2A_fdump
#define ArrayMemberData2X_fdump ArrayMemberData2A_fdump
#endif // UNIX_SYSTEM
// ArrayMemberData2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData3
typedef struct ArrayMemberData3
{
	u32_t				 *int_arr1;
	u32_t				**int_arr2;
	u32_t				**int_arr3;
	u32_t				**int_arr4;
	u32_t				**int_arr5;
	TestDataType		 *data_arr1;
	TestDataType		**data_arr2;
	TestDataType		**data_arr3;
	TestDataType		**data_arr4;
	TestDataType		**data_arr5;
	Dz1Asn1UTF8Str		 *u8_arr1;
	Dz1Asn1UTF8Str		**u8_arr2;
	Dz1Asn1UTF8Str		**u8_arr3;
	Dz1Asn1UTF8Str		**u8_arr4;
	Dz1Asn1UTF8Str		**u8_arr5;
} ArrayMemberData3;

DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData3 *ArrayMemberData3_new(u32_t *int_arr1_e_copy, 
															   u32_t **int_arr2_e_clone, 
															   u32_t **int_arr3_e_ref, 
															   u32_t **int_arr4_ref, 
															   u32_t **int_arr5_ref, 
															   TestDataType *data_arr1_e_copy, 
															   TestDataType **data_arr2_e_clone, 
															   TestDataType **data_arr3_e_ref, 
															   TestDataType **data_arr4_ref, 
															   TestDataType **data_arr5_ref, 
															   Dz1Asn1UTF8Str *u8_arr1_e_copy, 
															   Dz1Asn1UTF8Str **u8_arr2_e_clone, 
															   Dz1Asn1UTF8Str **u8_arr3_e_ref, 
															   Dz1Asn1UTF8Str **u8_arr4_ref, 
															   Dz1Asn1UTF8Str **u8_arr5_ref, Dz1Error *err);
static __inline__ ArrayMemberData3 *ArrayMemberData3_gen(Dz1Error *err) { return ArrayMemberData3_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ArrayMemberData3_copy(ArrayMemberData3 *dst, ArrayMemberData3 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData3 *ArrayMemberData3_clone(ArrayMemberData3 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData3_purge(ArrayMemberData3 *p);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData3_del(ArrayMemberData3 *p);
static __inline__ void ArrayMemberData3_delAndSetNull(void *ptr)
{
	ArrayMemberData3 **p = (ArrayMemberData3 **)ptr;
	if (p) { ArrayMemberData3_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData3A_dump(ArrayMemberData3 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData3A_fdump(FILE *fp, ArrayMemberData3 *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData3W_dump(ArrayMemberData3 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData3W_fdump(FILE *fp, ArrayMemberData3 *p, int tab);
#ifdef UNICODE
#define ArrayMemberData3_dump ArrayMemberData3W_dump
#define ArrayMemberData3_fdump ArrayMemberData3W_fdump
#else //  UNICODE
#define ArrayMemberData3_dump ArrayMemberData3A_dump
#define ArrayMemberData3_fdump ArrayMemberData3A_fdump
#endif //  UNICODE
static __inline__ void ArrayMemberData3X_dump(ArrayMemberData3 *p, int tab) { DZ1_DUMP(ArrayMemberData3, p, tab); }
static __inline__ void ArrayMemberData3X_fdump(FILE *fp, ArrayMemberData3 *p, int tab) { DZ1_FDUMP(fp, ArrayMemberData3, p, tab); }
#else // UNIX_SYSTEM
#define ArrayMemberData3_dump ArrayMemberData3A_dump
#define ArrayMemberData3X_dump ArrayMemberData3A_dump
#define ArrayMemberData3_fdump ArrayMemberData3A_fdump
#define ArrayMemberData3X_fdump ArrayMemberData3A_fdump
#endif // UNIX_SYSTEM
// ArrayMemberData3
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData4Present
typedef enum ArrayMemberData4Present
{
	ArrayMemberData4Present_int_arr1,
	ArrayMemberData4Present_int_arr2,
	ArrayMemberData4Present_int_arr3,
	ArrayMemberData4Present_int_arr4,
	ArrayMemberData4Present_int_arr5,
	ArrayMemberData4Present_int_arr6,
	ArrayMemberData4Present_data_arr1,
	ArrayMemberData4Present_data_arr2,
	ArrayMemberData4Present_data_arr3,
	ArrayMemberData4Present_data_arr4,
	ArrayMemberData4Present_data_arr5,
	ArrayMemberData4Present_u8_arr1,
	ArrayMemberData4Present_u8_arr2,
	ArrayMemberData4Present_u8_arr3,
	ArrayMemberData4Present_u8_arr4,
	ArrayMemberData4Present_u8_arr5,
	ArrayMemberData4Present_max
} ArrayMemberData4Present;

DZ1_CPPLINK str_t ArrayMemberData4PresentStrA(ArrayMemberData4Present v);
DZ1_CPPLINK ArrayMemberData4Present ArrayMemberData4PresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ArrayMemberData4PresentStrW(ArrayMemberData4Present v);
DZ1_CPPLINK ArrayMemberData4Present ArrayMemberData4PresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ArrayMemberData4PresentStr ArrayMemberData4PresentStrW
#define ArrayMemberData4PresentFromStr ArrayMemberData4PresentFromStrW
#else // UNICODE
#define ArrayMemberData4PresentStr ArrayMemberData4PresentStrA
#define ArrayMemberData4PresentFromStr ArrayMemberData4PresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ArrayMemberData4PresentStr ArrayMemberData4PresentStrA
#define ArrayMemberData4PresentFromStr ArrayMemberData4PresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData4Present *ArrayMemberData4Present_new(ArrayMemberData4Present *src, Dz1Error *err);
static __inline__ ArrayMemberData4Present *ArrayMemberData4Present_gen(Dz1Error *err) { ArrayMemberData4Present v = ArrayMemberData4Present_max; return ArrayMemberData4Present_new(&v, err); }
#define ArrayMemberData4Present_clone             ArrayMemberData4Present_new
static __inline__ void ArrayMemberData4Present_del(ArrayMemberData4Present *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ArrayMemberData4Present_delAndSetNull(void *ptr)
{
	ArrayMemberData4Present **p = (ArrayMemberData4Present **)ptr;
	if (p != NULL) { ArrayMemberData4Present_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4PresentA_dump(ArrayMemberData4Present *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4PresentA_fdump(FILE *fp, ArrayMemberData4Present *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4PresentW_dump(ArrayMemberData4Present *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4PresentW_fdump(FILE *fp, ArrayMemberData4Present *v, int tab);
#ifdef UNICODE
#define ArrayMemberData4Present_dump ArrayMemberData4PresentW_dump
#define ArrayMemberData4Present_fdump ArrayMemberData4PresentW_fdump
#else //  UNICODE
#define ArrayMemberData4Present_dump ArrayMemberData4PresentA_dump
#define ArrayMemberData4Present_fdump ArrayMemberData4PresentA_fdump
#endif //  UNICODE
static __inline__ void ArrayMemberData4PresentX_dump(ArrayMemberData4Present *p, int tab) { DZ1_DUMP(ArrayMemberData4Present, p, tab); }
static __inline__ void ArrayMemberData4PresentX_fdump(FILE *fp, ArrayMemberData4Present *p, int tab) { DZ1_FDUMP(fp, ArrayMemberData4Present, p, tab); }
#else // UNIX_SYSTEM
#define ArrayMemberData4Present_dump ArrayMemberData4PresentA_dump
#define ArrayMemberData4PresentX_dump ArrayMemberData4PresentA_dump
#define ArrayMemberData4Present_fdump ArrayMemberData4PresentA_fdump
#define ArrayMemberData4PresentX_fdump ArrayMemberData4PresentA_fdump
#endif // UNIX_SYSTEM
// ArrayMemberData4Present
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData4
typedef struct ArrayMemberData4
{
	ArrayMemberData4Present present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t				 *int_arr1;
		u32_t				 *int_arr2;
		u32_t				**int_arr3;
		u32_t				**int_arr4;
		u32_t				**int_arr5;
		u32_t				**int_arr6;
		TestDataType		 *data_arr1;
		TestDataType		**data_arr2;
		TestDataType		**data_arr3;
		TestDataType		**data_arr4;
		TestDataType		**data_arr5;
		Dz1Asn1UTF8Str		 *u8_arr1;
		Dz1Asn1UTF8Str		**u8_arr2;
		Dz1Asn1UTF8Str		**u8_arr3;
		Dz1Asn1UTF8Str		**u8_arr4;
		Dz1Asn1UTF8Str		**u8_arr5;
	} x;
} ArrayMemberData4;

DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData4 *ArrayMemberData4_new(ArrayMemberData4Present present, void *ptr, Dz1Error *err);
static __inline__ ArrayMemberData4 *ArrayMemberData4_gen(Dz1Error *err) { return ArrayMemberData4_new(ArrayMemberData4Present_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ArrayMemberData4_copy(ArrayMemberData4 *dst, ArrayMemberData4 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData4 *ArrayMemberData4_clone(ArrayMemberData4 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4_purge(ArrayMemberData4 *p);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4_del(ArrayMemberData4 *p);
static __inline__ void ArrayMemberData4_delAndSetNull(void *ptr)
{
	ArrayMemberData4 **p = (ArrayMemberData4 **)ptr;
	if (p != NULL) { ArrayMemberData4_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4A_dump(ArrayMemberData4 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4A_fdump(FILE *fp, ArrayMemberData4 *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4W_dump(ArrayMemberData4 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData4W_fdump(FILE *fp, ArrayMemberData4 *p, int tab);
#ifdef UNICODE
#define ArrayMemberData4_dump ArrayMemberData4W_dump
#define ArrayMemberData4_fdump ArrayMemberData4W_fdump
#else //  UNICODE
#define ArrayMemberData4_dump ArrayMemberData4A_dump
#define ArrayMemberData4_fdump ArrayMemberData4A_fdump
#endif //  UNICODE
static __inline__ void ArrayMemberData4X_dump(ArrayMemberData4 *p, int tab) { DZ1_DUMP(ArrayMemberData4, p, tab); }
static __inline__ void ArrayMemberData4X_fdump(FILE *fp, ArrayMemberData4 *p, int tab) { DZ1_FDUMP(fp, ArrayMemberData4, p, tab); }
#else // UNIX_SYSTEM
#define ArrayMemberData4_dump ArrayMemberData4A_dump
#define ArrayMemberData4X_dump ArrayMemberData4A_dump
#define ArrayMemberData4_fdump ArrayMemberData4A_fdump
#define ArrayMemberData4X_fdump ArrayMemberData4A_fdump
#endif // UNIX_SYSTEM
// ArrayMemberData4
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData5Present
typedef enum ArrayMemberData5Present
{
	ArrayMemberData5Present_int_arr1,
	ArrayMemberData5Present_int_arr2,
	ArrayMemberData5Present_int_arr3,
	ArrayMemberData5Present_int_arr4,
	ArrayMemberData5Present_int_arr5,
	ArrayMemberData5Present_data_arr1,
	ArrayMemberData5Present_data_arr2,
	ArrayMemberData5Present_data_arr3,
	ArrayMemberData5Present_data_arr4,
	ArrayMemberData5Present_data_arr5,
	ArrayMemberData5Present_u8_arr1,
	ArrayMemberData5Present_u8_arr2,
	ArrayMemberData5Present_u8_arr3,
	ArrayMemberData5Present_u8_arr4,
	ArrayMemberData5Present_u8_arr5,
	ArrayMemberData5Present_max
} ArrayMemberData5Present;

DZ1_CPPLINK str_t ArrayMemberData5PresentStrA(ArrayMemberData5Present v);
DZ1_CPPLINK ArrayMemberData5Present ArrayMemberData5PresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ArrayMemberData5PresentStrW(ArrayMemberData5Present v);
DZ1_CPPLINK ArrayMemberData5Present ArrayMemberData5PresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ArrayMemberData5PresentStr ArrayMemberData5PresentStrW
#define ArrayMemberData5PresentFromStr ArrayMemberData5PresentFromStrW
#else // UNICODE
#define ArrayMemberData5PresentStr ArrayMemberData5PresentStrA
#define ArrayMemberData5PresentFromStr ArrayMemberData5PresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ArrayMemberData5PresentStr ArrayMemberData5PresentStrA
#define ArrayMemberData5PresentFromStr ArrayMemberData5PresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData5Present *ArrayMemberData5Present_new(ArrayMemberData5Present *src, Dz1Error *err);
static __inline__ ArrayMemberData5Present *ArrayMemberData5Present_gen(Dz1Error *err) { ArrayMemberData5Present v = ArrayMemberData5Present_max; return ArrayMemberData5Present_new(&v, err); }
#define ArrayMemberData5Present_clone             ArrayMemberData5Present_new
static __inline__ void ArrayMemberData5Present_del(ArrayMemberData5Present *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ArrayMemberData5Present_delAndSetNull(void *ptr)
{
	ArrayMemberData5Present **p = (ArrayMemberData5Present **)ptr;
	if (p != NULL) { ArrayMemberData5Present_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5PresentA_dump(ArrayMemberData5Present *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5PresentA_fdump(FILE *fp, ArrayMemberData5Present *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5PresentW_dump(ArrayMemberData5Present *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5PresentW_fdump(FILE *fp, ArrayMemberData5Present *v, int tab);
#ifdef UNICODE
#define ArrayMemberData5Present_dump ArrayMemberData5PresentW_dump
#define ArrayMemberData5Present_fdump ArrayMemberData5PresentW_fdump
#else //  UNICODE
#define ArrayMemberData5Present_dump ArrayMemberData5PresentA_dump
#define ArrayMemberData5Present_fdump ArrayMemberData5PresentA_fdump
#endif //  UNICODE
static __inline__ void ArrayMemberData5PresentX_dump(ArrayMemberData5Present *p, int tab) { DZ1_DUMP(ArrayMemberData5Present, p, tab); }
static __inline__ void ArrayMemberData5PresentX_fdump(FILE *fp, ArrayMemberData5Present *p, int tab) { DZ1_FDUMP(fp, ArrayMemberData5Present, p, tab); }
#else // UNIX_SYSTEM
#define ArrayMemberData5Present_dump ArrayMemberData5PresentA_dump
#define ArrayMemberData5PresentX_dump ArrayMemberData5PresentA_dump
#define ArrayMemberData5Present_fdump ArrayMemberData5PresentA_fdump
#define ArrayMemberData5PresentX_fdump ArrayMemberData5PresentA_fdump
#endif // UNIX_SYSTEM
// ArrayMemberData5Present
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ArrayMemberData5
typedef struct ArrayMemberData5
{
	ArrayMemberData5Present present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t				 *int_arr1;
		u32_t				**int_arr2;
		u32_t				**int_arr3;
		u32_t				**int_arr4;
		u32_t				**int_arr5;
		TestDataType		 *data_arr1;
		TestDataType		**data_arr2;
		TestDataType		**data_arr3;
		TestDataType		**data_arr4;
		TestDataType		**data_arr5;
		Dz1Asn1UTF8Str		 *u8_arr1;
		Dz1Asn1UTF8Str		**u8_arr2;
		Dz1Asn1UTF8Str		**u8_arr3;
		Dz1Asn1UTF8Str		**u8_arr4;
		Dz1Asn1UTF8Str		**u8_arr5;
	} x;
} ArrayMemberData5;

DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData5 *ArrayMemberData5_new(ArrayMemberData5Present present, void *ptr, Dz1Error *err);
static __inline__ ArrayMemberData5 *ArrayMemberData5_gen(Dz1Error *err) { return ArrayMemberData5_new(ArrayMemberData5Present_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ArrayMemberData5_copy(ArrayMemberData5 *dst, ArrayMemberData5 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ArrayMemberData5 *ArrayMemberData5_clone(ArrayMemberData5 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5_purge(ArrayMemberData5 *p);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5_del(ArrayMemberData5 *p);
static __inline__ void ArrayMemberData5_delAndSetNull(void *ptr)
{
	ArrayMemberData5 **p = (ArrayMemberData5 **)ptr;
	if (p != NULL) { ArrayMemberData5_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5A_dump(ArrayMemberData5 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5A_fdump(FILE *fp, ArrayMemberData5 *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5W_dump(ArrayMemberData5 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void ArrayMemberData5W_fdump(FILE *fp, ArrayMemberData5 *p, int tab);
#ifdef UNICODE
#define ArrayMemberData5_dump ArrayMemberData5W_dump
#define ArrayMemberData5_fdump ArrayMemberData5W_fdump
#else //  UNICODE
#define ArrayMemberData5_dump ArrayMemberData5A_dump
#define ArrayMemberData5_fdump ArrayMemberData5A_fdump
#endif //  UNICODE
static __inline__ void ArrayMemberData5X_dump(ArrayMemberData5 *p, int tab) { DZ1_DUMP(ArrayMemberData5, p, tab); }
static __inline__ void ArrayMemberData5X_fdump(FILE *fp, ArrayMemberData5 *p, int tab) { DZ1_FDUMP(fp, ArrayMemberData5, p, tab); }
#else // UNIX_SYSTEM
#define ArrayMemberData5_dump ArrayMemberData5A_dump
#define ArrayMemberData5X_dump ArrayMemberData5A_dump
#define ArrayMemberData5_fdump ArrayMemberData5A_fdump
#define ArrayMemberData5X_fdump ArrayMemberData5A_fdump
#endif // UNIX_SYSTEM
// ArrayMemberData5
////////////////////////////////////////////////////////////////////////////////

#endif
