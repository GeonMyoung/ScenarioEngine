#ifndef ARRAY_INFO_H
#define ARRAY_INFO_H

#include "dz1_error.h"

// Array/Table API
// Normal = LinkedList
// 	API:
// 		Add(dp), Remove(dp), Extract(dp), Travel(func, arg)
// Ordered = AATree
// 	API:
// 		Add(dp), Remove(dp), Extract(keyp), Travel(func, arg)
// 		Find(keyp), GetHead(), GetTail()
//
// Normal + Unique: -> if have Ordered. this type is same as Ordered + Unique
//	Require Compare API
//	Publishing Source:
//		Find Entry before calling Add
//
// Ordered + Unique:
//	Require Compare API
//	Publishing Source:
//		Find Entry before calling Add
//
//
//        | no Unique | Unique   |
//	------+-----------+----------+
//	Array | List      | List+    |
//	Table | AATable   | AATable+ |
//	------+-----------+----------+
//
//										   Array    	  	Table			Generatable
//#define OBJECT_API_CLONE                 clone			clone			travel+
//#define OBJECT_API_DUMP				   dump				dump			travel+
//#define OBJECT_API_CMP				   -				-				- (array type is can't comparable)
//#define OBJECT_API_CODEC				   -				-				travel+
//-----------------------------------------------------------------------------------
#define ARRAY_API_ADD			0x80000000	// push 	      	insert			X
#define ARRAY_API_TRAVEL		0x40000000	// travel			trave			X
//-----------------------------------------------------------------------------------
#define ARRAY_API_REMOVE		0x20000000	// remove			remove			X
#define ARRAY_API_EXTRACT		0x10000000	// extract			extract			X
#define ARRAY_API_FIND			0x08000000	// find				find			travel+
#define ARRAY_API_GETHEAD		0x04000000	// gethead			gethead			travel+
#define ARRAY_API_GETTAIL		0x02000000	// gettail			gettail	        travel+
#define ARRAY_API_COUNT			0x01000000  // count            count           travel+
#define ARRAY_API_ARRAY			0x00800000	// get/put array	get/put array	travel+
#define ARRAY_API_BASE			(ARRAY_API_COUNT | ARRAY_API_TRAVEL | ARRAY_API_ARRAY | ARRAY_API_ADD)
#define ARRAY_API_FULL			0xFFFFFFF0
#define INDEX_API_BASE			(ARRAY_API_ADD | ARRAY_API_TRAVEL | ARRAY_API_REMOVE | ARRAY_API_EXTRACT | ARRAY_API_FIND | ARRAY_API_COUNT | ARRAY_API_ARRAY )

#define ARRAY_API_NO_DUMP		0x00000001
#define ARRAY_API_USER_DUMP		0x00000002
#define ARRAY_API_NO_FDUMP		0x00000004
#define ARRAY_API_USER_FDUMP	0x00000008

struct ObjectInfo;
typedef enum
{
	ArrayType_normal,
	ArrayType_ordered,
	ArrayType_unique,
	ArrayType_max
} ArrayType;

typedef struct ArrayInfo
{
	u32_t arrayApi;
	struct ObjectInfo *entry;
	str_t entrySrcType;
	bool_t isReferenced;
	FORWARD_TYPE isForward;
	ArrayType type;
	str_t dumpPrefix;
} ArrayInfo;

DZ1_CPPLINK ArrayInfo *ArrayInfo_new(u32_t arrayApi, struct ObjectInfo *entry, str_t entrySrcType,
									 bool_t isReferenced, FORWARD_TYPE isForward, ArrayType type, Dz1Error *err);
DZ1_CPPLINK void ArrayInfo_del(ArrayInfo *p);
DZ1_CPPLINK void ArrayInfo_dump(ArrayInfo *p, int tab);
static __inline__ void ArrayInfo_delAndSetNull(void *ptr)
{
	ArrayInfo **p = (ArrayInfo **)ptr;
	ArrayInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK void *ArrayInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t ArrayInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t ArrayInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

typedef struct IndexInfoKey
{
	int valid;
	str_t names[64];
} IndexInfoKey;
DZ1_CPPLINK Dz1Error IndexInfoKey_appendName(IndexInfoKey *p, str_t name);
DZ1_CPPLINK void IndexInfoKey_clear(IndexInfoKey *p);

typedef struct IndexInfo
{
	u32_t indexApi;
	struct ObjectInfo *entry;
	str_t entrySrcType;
	bool_t isReferenced;
	bool_t isForward;
	bool_t indexUnique;
	IndexInfoKey keys;
	str_t dumpPrefix;
} IndexInfo;

DZ1_CPPLINK IndexInfo *IndexInfo_new(u32_t indexApi, struct ObjectInfo *entry, str_t entrySrcType,
									 bool_t isReferenced, FORWARD_TYPE isForward, bool_t indexUnique,
									 Dz1Error *err);
DZ1_CPPLINK void IndexInfo_del(IndexInfo *p);
DZ1_CPPLINK void IndexInfo_dump(IndexInfo *p, int tab);
static __inline__ void IndexInfo_delAndSetNull(void *pptr)
{
	IndexInfo **p = (IndexInfo **)pptr;
	IndexInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK IndexInfo *IndexInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t IndexInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t IndexInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
