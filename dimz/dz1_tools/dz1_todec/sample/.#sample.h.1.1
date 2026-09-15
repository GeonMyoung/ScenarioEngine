#ifndef _DZ1_TDC_SAMPLE_H_
#define _DZ1_TDC_SAMPLE_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// EnumSample
typedef enum EnumSample
{
	EnumSample_value0,
	EnumSample_value1,
	EnumSample_value2,
	EnumSample_max
} EnumSample;

DZ1_CPPLINK str_t EnumSampleStrA(EnumSample v);
DZ1_CPPLINK EnumSample EnumSampleFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t EnumSampleStrW(EnumSample v);
DZ1_CPPLINK EnumSample EnumSampleFromStrW(wstr_t str);
#ifdef UNICODE
#define EnumSampleStr EnumSampleStrW
#define EnumSampleFromStr EnumSampleFromStrW
#else // UNICODE
#define EnumSampleStr EnumSampleStrA
#define EnumSampleFromStr EnumSampleFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define EnumSampleStr EnumSampleStrA
#define EnumSampleFromStr EnumSampleFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT EnumSample *EnumSample_new(EnumSample *src, Dz1Error *err);
static __inline__ EnumSample *EnumSample_gen(Dz1Error *err) { EnumSample v = EnumSample_max; return EnumSample_new(&v, err); }
static __inline__ void EnumSample_del(EnumSample *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void EnumSample_delAndSetNull(void *ptr)
{
	EnumSample **p = (EnumSample **)ptr;
	if (p != NULL) { EnumSample_del(*p); *p = NULL; }
}
// EnumSample
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyData
typedef struct MyData
{
	u32_t		data1;
	u16_t		data2;
	u8_t		data3;
} MyData;

DZ1_CPPLINK DZ1_DLLPORT MyData *MyData_new(u32_t data1, u16_t data2, u8_t data3, Dz1Error *err);
static __inline__ MyData *MyData_gen(Dz1Error *err) { return MyData_new(0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyData_copy(MyData *dst, MyData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyData *MyData_clone(MyData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyData_purge(MyData *p);
DZ1_CPPLINK DZ1_DLLPORT void MyData_del(MyData *p);
static __inline__ void MyData_delAndSetNull(void *ptr)
{
	MyData **p = (MyData **)ptr;
	if (p) { MyData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyData_dump(MyData *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int MyData_cmp(MyData *a, MyData *b); 
// MyData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StructSample
typedef struct StructSample
{
	u32_t			 data1;
	u16_t			 data2;
	u8_t			 data3;
	EnumSample		 data4;
	MyData			*data5;
} StructSample;

DZ1_CPPLINK DZ1_DLLPORT StructSample *StructSample_new(u32_t data1, 
													   u16_t data2, 
													   u8_t data3, 
													   EnumSample data4, 
													   MyData *data5, Dz1Error *err);
static __inline__ StructSample *StructSample_gen(Dz1Error *err) { return StructSample_new(0, 0, 0, EnumSample_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t StructSample_copy(StructSample *dst, StructSample *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT StructSample *StructSample_clone(StructSample *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StructSample_purge(StructSample *p);
DZ1_CPPLINK DZ1_DLLPORT void StructSample_del(StructSample *p);
static __inline__ void StructSample_delAndSetNull(void *ptr)
{
	StructSample **p = (StructSample **)ptr;
	if (p) { StructSample_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StructSample_dump(StructSample *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int StructSample_cmp(StructSample *a, StructSample *b); 
// StructSample
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StructSampleList
typedef struct StructSampleList
{
	void *storage;
	unsigned int (*count)(struct StructSampleList *p);
	Dz1Error (*travel)(struct StructSampleList *p, Dz1Error (*func)(void *ptr, StructSample *entry), void *ptr);
	Dz1Error (*travelForward)(struct StructSampleList *p, Dz1Error (*func)(void *ptr, StructSample *entry), void *ptr);
	Dz1Error (*travelBackward)(struct StructSampleList *p, Dz1Error (*func)(void *ptr, StructSample *entry), void *ptr);
	StructSample **(*get_array)(struct StructSampleList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct StructSampleList *p, StructSample *data);
	bool_t (*remove)(struct StructSampleList *p, StructSample *key);
	StructSample *(*extract)(struct StructSampleList *p, StructSample *key);
	StructSample *(*find)(struct StructSampleList *p, StructSample *key);
	int (*cmp)(StructSample *a, StructSample *b);
} StructSampleList;

DZ1_CPPLINK DZ1_DLLPORT StructSampleList *StructSampleList_new(Dz1Error *err);
static __inline__ StructSampleList *StructSampleList_gen(Dz1Error *err) { return StructSampleList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT StructSampleList *StructSampleList_clone(StructSampleList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StructSampleList_purge(StructSampleList *p);
DZ1_CPPLINK DZ1_DLLPORT void StructSampleList_del(StructSampleList *p);
static __inline__ void StructSampleList_delAndSetNull(void *ptr)
{
	StructSampleList **p = (StructSampleList **)ptr;
	if (p != NULL) { StructSampleList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StructSampleList_dump(StructSampleList *p, int tab);

// StructSampleList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UnionSamplePresent
typedef enum UnionSamplePresent
{
	UnionSamplePresent_data1,
	UnionSamplePresent_data2,
	UnionSamplePresent_data3,
	UnionSamplePresent_data4,
	UnionSamplePresent_data5,
	UnionSamplePresent_max
} UnionSamplePresent;

DZ1_CPPLINK str_t UnionSamplePresentStrA(UnionSamplePresent v);
DZ1_CPPLINK UnionSamplePresent UnionSamplePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t UnionSamplePresentStrW(UnionSamplePresent v);
DZ1_CPPLINK UnionSamplePresent UnionSamplePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define UnionSamplePresentStr UnionSamplePresentStrW
#define UnionSamplePresentFromStr UnionSamplePresentFromStrW
#else // UNICODE
#define UnionSamplePresentStr UnionSamplePresentStrA
#define UnionSamplePresentFromStr UnionSamplePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define UnionSamplePresentStr UnionSamplePresentStrA
#define UnionSamplePresentFromStr UnionSamplePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT UnionSamplePresent *UnionSamplePresent_new(UnionSamplePresent *src, Dz1Error *err);
static __inline__ UnionSamplePresent *UnionSamplePresent_gen(Dz1Error *err) { UnionSamplePresent v = UnionSamplePresent_max; return UnionSamplePresent_new(&v, err); }
#define UnionSamplePresent_clone             UnionSamplePresent_new
static __inline__ void UnionSamplePresent_del(UnionSamplePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void UnionSamplePresent_delAndSetNull(void *ptr)
{
	UnionSamplePresent **p = (UnionSamplePresent **)ptr;
	if (p != NULL) { UnionSamplePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void UnionSamplePresent_dump(UnionSamplePresent *v, int tab);
// UnionSamplePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UnionSample
typedef struct UnionSample
{
	UnionSamplePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t			 data1;
		u16_t			 data2;
		u8_t			 data3;
		EnumSample		 data4;
		MyData			*data5;
	} x;
} UnionSample;

DZ1_CPPLINK DZ1_DLLPORT UnionSample *UnionSample_new(UnionSamplePresent present, void *ptr, Dz1Error *err);
static __inline__ UnionSample *UnionSample_gen(Dz1Error *err) { return UnionSample_new(UnionSamplePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  UnionSample_copy(UnionSample *dst, UnionSample *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT UnionSample *UnionSample_clone(UnionSample *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void UnionSample_purge(UnionSample *p);
DZ1_CPPLINK DZ1_DLLPORT void UnionSample_del(UnionSample *p);
static __inline__ void UnionSample_delAndSetNull(void *ptr)
{
	UnionSample **p = (UnionSample **)ptr;
	if (p != NULL) { UnionSample_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void UnionSample_dump(UnionSample *p, int tab);
// UnionSample
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UnionSampleList
typedef struct UnionSampleList
{
	void *storage;
	unsigned int (*count)(struct UnionSampleList *p);
	Dz1Error (*travel)(struct UnionSampleList *p, Dz1Error (*func)(void *ptr, UnionSample *entry), void *ptr);
	Dz1Error (*travelForward)(struct UnionSampleList *p, Dz1Error (*func)(void *ptr, UnionSample *entry), void *ptr);
	Dz1Error (*travelBackward)(struct UnionSampleList *p, Dz1Error (*func)(void *ptr, UnionSample *entry), void *ptr);
	UnionSample **(*get_array)(struct UnionSampleList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct UnionSampleList *p, UnionSample *data);
} UnionSampleList;

DZ1_CPPLINK DZ1_DLLPORT UnionSampleList *UnionSampleList_new(Dz1Error *err);
static __inline__ UnionSampleList *UnionSampleList_gen(Dz1Error *err) { return UnionSampleList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT UnionSampleList *UnionSampleList_clone(UnionSampleList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void UnionSampleList_purge(UnionSampleList *p);
DZ1_CPPLINK DZ1_DLLPORT void UnionSampleList_del(UnionSampleList *p);
static __inline__ void UnionSampleList_delAndSetNull(void *ptr)
{
	UnionSampleList **p = (UnionSampleList **)ptr;
	if (p != NULL) { UnionSampleList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void UnionSampleList_dump(UnionSampleList *p, int tab);

// UnionSampleList
////////////////////////////////////////////////////////////////////////////////

#endif
