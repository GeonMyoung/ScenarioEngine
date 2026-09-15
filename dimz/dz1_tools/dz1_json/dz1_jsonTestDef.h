#ifndef _DZ1_TDC_DZ1_JSON_TEST_DEF_H_
#define _DZ1_TDC_DZ1_JSON_TEST_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_jsonTestTypes.h"

////////////////////////////////////////////////////////////////////////////////
// MyEnum
typedef enum MyEnum
{
	MyEnum_abc,
	MyEnum_bcd,
	MyEnum_cde,
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
// MyEnum
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStruct
typedef struct MyStruct
{
	u8_t		a;
	u16_t		b;
	u32_t		c;
	u64_t		d;
	Dz1Str		e;
} MyStruct;

DZ1_CPPLINK DZ1_DLLPORT MyStruct *MyStruct_new(u8_t a, 
											   u16_t b, 
											   u32_t c, 
											   u64_t d, 
											   Dz1Str e, Dz1Error *err);
static __inline__ MyStruct *MyStruct_gen(Dz1Error *err) { return MyStruct_new(0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyStruct_copy(MyStruct *dst, MyStruct *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyStruct *MyStruct_clone(MyStruct *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyStruct_purge(MyStruct *p);
DZ1_CPPLINK DZ1_DLLPORT void MyStruct_del(MyStruct *p);
static __inline__ void MyStruct_delAndSetNull(void *ptr)
{
	MyStruct **p = (MyStruct **)ptr;
	if (p) { MyStruct_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyStruct_dump(MyStruct *p, int tab);
// MyStruct
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyStructList
typedef struct MyStructList
{
	void *storage;
	unsigned int (*count)(struct MyStructList *p);
	Dz1Error (*travel)(struct MyStructList *p, Dz1Error (*func)(void *ptr, MyStruct *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyStructList *p, Dz1Error (*func)(void *ptr, MyStruct *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyStructList *p, Dz1Error (*func)(void *ptr, MyStruct *entry), void *ptr);
	MyStruct **(*get_array)(struct MyStructList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyStructList *p, MyStruct *data);
} MyStructList;

DZ1_CPPLINK DZ1_DLLPORT MyStructList *MyStructList_new(Dz1Error *err);
static __inline__ MyStructList *MyStructList_gen(Dz1Error *err) { return MyStructList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyStructList *MyStructList_clone(MyStructList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyStructList_purge(MyStructList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyStructList_del(MyStructList *p);
static __inline__ void MyStructList_delAndSetNull(void *ptr)
{
	MyStructList **p = (MyStructList **)ptr;
	if (p != NULL) { MyStructList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyStructList_dump(MyStructList *p, int tab);

// MyStructList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionPresent
typedef enum MyUnionPresent
{
	MyUnionPresent_a,
	MyUnionPresent_b,
	MyUnionPresent_c,
	MyUnionPresent_d,
	MyUnionPresent_e,
	MyUnionPresent_f,
	MyUnionPresent_g,
	MyUnionPresent_h,
	MyUnionPresent_i,
	MyUnionPresent_j,
	MyUnionPresent_max
} MyUnionPresent;

DZ1_CPPLINK str_t MyUnionPresentStrA(MyUnionPresent v);
DZ1_CPPLINK MyUnionPresent MyUnionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t MyUnionPresentStrW(MyUnionPresent v);
DZ1_CPPLINK MyUnionPresent MyUnionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define MyUnionPresentStr MyUnionPresentStrW
#define MyUnionPresentFromStr MyUnionPresentFromStrW
#else // UNICODE
#define MyUnionPresentStr MyUnionPresentStrA
#define MyUnionPresentFromStr MyUnionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define MyUnionPresentStr MyUnionPresentStrA
#define MyUnionPresentFromStr MyUnionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT MyUnionPresent *MyUnionPresent_new(MyUnionPresent *src, Dz1Error *err);
static __inline__ MyUnionPresent *MyUnionPresent_gen(Dz1Error *err) { MyUnionPresent v = MyUnionPresent_max; return MyUnionPresent_new(&v, err); }
#define MyUnionPresent_clone             MyUnionPresent_new
static __inline__ void MyUnionPresent_del(MyUnionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void MyUnionPresent_delAndSetNull(void *ptr)
{
	MyUnionPresent **p = (MyUnionPresent **)ptr;
	if (p != NULL) { MyUnionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionPresent_dump(MyUnionPresent *v, int tab);
// MyUnionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnion
typedef struct MyUnion
{
	MyUnionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u8_t			 a;
		u16_t			 b;
		u32_t			 c;
		u64_t			 d;
		Dz1Str			 e;
		MyStructList	*f;
		real64_t		 g;
		real32_t		 h;
		MyEnum			 i;
		MyExternHz		 j;
	} x;
} MyUnion;

DZ1_CPPLINK DZ1_DLLPORT MyUnion *MyUnion_new(MyUnionPresent present, void *ptr, Dz1Error *err);
static __inline__ MyUnion *MyUnion_gen(Dz1Error *err) { return MyUnion_new(MyUnionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  MyUnion_copy(MyUnion *dst, MyUnion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyUnion *MyUnion_clone(MyUnion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnion_purge(MyUnion *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnion_del(MyUnion *p);
static __inline__ void MyUnion_delAndSetNull(void *ptr)
{
	MyUnion **p = (MyUnion **)ptr;
	if (p != NULL) { MyUnion_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnion_dump(MyUnion *p, int tab);
// MyUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyUnionList
typedef struct MyUnionList
{
	void *storage;
	unsigned int (*count)(struct MyUnionList *p);
	Dz1Error (*travel)(struct MyUnionList *p, Dz1Error (*func)(void *ptr, MyUnion *entry), void *ptr);
	Dz1Error (*travelForward)(struct MyUnionList *p, Dz1Error (*func)(void *ptr, MyUnion *entry), void *ptr);
	Dz1Error (*travelBackward)(struct MyUnionList *p, Dz1Error (*func)(void *ptr, MyUnion *entry), void *ptr);
	MyUnion **(*get_array)(struct MyUnionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct MyUnionList *p, MyUnion *data);
} MyUnionList;

DZ1_CPPLINK DZ1_DLLPORT MyUnionList *MyUnionList_new(Dz1Error *err);
static __inline__ MyUnionList *MyUnionList_gen(Dz1Error *err) { return MyUnionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT MyUnionList *MyUnionList_clone(MyUnionList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionList_purge(MyUnionList *p);
DZ1_CPPLINK DZ1_DLLPORT void MyUnionList_del(MyUnionList *p);
static __inline__ void MyUnionList_delAndSetNull(void *ptr)
{
	MyUnionList **p = (MyUnionList **)ptr;
	if (p != NULL) { MyUnionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyUnionList_dump(MyUnionList *p, int tab);

// MyUnionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// MyComponent
typedef struct MyComponent
{
	u32_t			 a;
	MyStruct		*b;
	MyUnion			*c;
	MyStructList	*d;
	MyUnionList		*e;
	real64_t		 f;
	real32_t		 g;
	MyEnum			 h;
	MyExternHz		 i;
} MyComponent;

DZ1_CPPLINK DZ1_DLLPORT MyComponent *MyComponent_new(u32_t a, 
													 MyStruct *b, 
													 MyUnion *c, 
													 real64_t f, 
													 real32_t g, 
													 MyEnum h, 
													 MyExternHz i, Dz1Error *err);
static __inline__ MyComponent *MyComponent_gen(Dz1Error *err) { return MyComponent_new(0, NULL, NULL, 0, 0, MyEnum_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t MyComponent_copy(MyComponent *dst, MyComponent *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT MyComponent *MyComponent_clone(MyComponent *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void MyComponent_purge(MyComponent *p);
DZ1_CPPLINK DZ1_DLLPORT void MyComponent_del(MyComponent *p);
static __inline__ void MyComponent_delAndSetNull(void *ptr)
{
	MyComponent **p = (MyComponent **)ptr;
	if (p) { MyComponent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void MyComponent_dump(MyComponent *p, int tab);
// MyComponent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// StringList
typedef struct StringList
{
	void *storage;
	unsigned int (*count)(struct StringList *p);
	Dz1Error (*travel)(struct StringList *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Error (*travelForward)(struct StringList *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Error (*travelBackward)(struct StringList *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Str *(*get_array)(struct StringList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct StringList *p, Dz1Str data);
	int (*cmp)(Dz1Str a, Dz1Str b);
} StringList;

DZ1_CPPLINK DZ1_DLLPORT StringList *StringList_new(Dz1Error *err);
static __inline__ StringList *StringList_gen(Dz1Error *err) { return StringList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT StringList *StringList_clone(StringList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void StringList_purge(StringList *p);
DZ1_CPPLINK DZ1_DLLPORT void StringList_del(StringList *p);
static __inline__ void StringList_delAndSetNull(void *ptr)
{
	StringList **p = (StringList **)ptr;
	if (p != NULL) { StringList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void StringList_dump(StringList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void StringList_fdump(FILE *fp, StringList *p, int tab);

// StringList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaDataList
typedef struct Asn1MetaDataList
{
	void *storage;
	unsigned int (*count)(struct Asn1MetaDataList *p);
	Dz1Error (*travel)(struct Asn1MetaDataList *p, Dz1Error (*func)(void *ptr, struct Asn1MetaData *entry), void *ptr);
	Dz1Error (*travelForward)(struct Asn1MetaDataList *p, Dz1Error (*func)(void *ptr, struct Asn1MetaData *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Asn1MetaDataList *p, Dz1Error (*func)(void *ptr, struct Asn1MetaData *entry), void *ptr);
	struct Asn1MetaData **(*get_array)(struct Asn1MetaDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Asn1MetaDataList *p, struct Asn1MetaData *data);
} Asn1MetaDataList;

DZ1_CPPLINK DZ1_DLLPORT Asn1MetaDataList *Asn1MetaDataList_new(Dz1Error *err);
static __inline__ Asn1MetaDataList *Asn1MetaDataList_gen(Dz1Error *err) { return Asn1MetaDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaDataList_purge(Asn1MetaDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaDataList_del(Asn1MetaDataList *p);
static __inline__ void Asn1MetaDataList_delAndSetNull(void *ptr)
{
	Asn1MetaDataList **p = (Asn1MetaDataList **)ptr;
	if (p != NULL) { Asn1MetaDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaDataList_dump(Asn1MetaDataList *p, int tab);

// Asn1MetaDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaData
typedef struct Asn1MetaData
{
	Dz1Str				 name;
	Dz1Str				 value;
	Asn1MetaDataList	*elements;
} Asn1MetaData;

DZ1_CPPLINK DZ1_DLLPORT Asn1MetaData *Asn1MetaData_new(Dz1Str name, 
													   Dz1Str value, Dz1Error *err);
static __inline__ Asn1MetaData *Asn1MetaData_gen(Dz1Error *err) { return Asn1MetaData_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaData_purge(Asn1MetaData *p);
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaData_del(Asn1MetaData *p);
static __inline__ void Asn1MetaData_delAndSetNull(void *ptr)
{
	Asn1MetaData **p = (Asn1MetaData **)ptr;
	if (p) { Asn1MetaData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaData_dump(Asn1MetaData *p, int tab);
// Asn1MetaData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Asn1MetaDataModule
typedef struct Asn1MetaDataModule
{
	Dz1Str				 name;
	Asn1MetaDataList	*elements;
} Asn1MetaDataModule;

DZ1_CPPLINK DZ1_DLLPORT Asn1MetaDataModule *Asn1MetaDataModule_new(Dz1Str name, Dz1Error *err);
static __inline__ Asn1MetaDataModule *Asn1MetaDataModule_gen(Dz1Error *err) { return Asn1MetaDataModule_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaDataModule_purge(Asn1MetaDataModule *p);
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaDataModule_del(Asn1MetaDataModule *p);
static __inline__ void Asn1MetaDataModule_delAndSetNull(void *ptr)
{
	Asn1MetaDataModule **p = (Asn1MetaDataModule **)ptr;
	if (p) { Asn1MetaDataModule_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Asn1MetaDataModule_dump(Asn1MetaDataModule *p, int tab);
// Asn1MetaDataModule
////////////////////////////////////////////////////////////////////////////////

#endif
