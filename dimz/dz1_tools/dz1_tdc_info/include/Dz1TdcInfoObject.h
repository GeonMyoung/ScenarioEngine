#ifndef OBJECT_INFO_H
#define OBJECT_INFO_H

#include "Dz1TdcInfoFunc.h"
#include "Dz1TdcInfoPrimitive.h"
#include "Dz1TdcInfoDefined.h"
#include "Dz1TdcInfoEnum.h"
#include "Dz1TdcInfoBits.h"
#include "Dz1TdcInfoUnion.h"
#include "Dz1TdcInfoStructure.h"
#include "Dz1TdcInfoArray.h"
#include "Dz1TdcInfoExtern.h"
#include "Dz1TdcInfoConstant.h"

struct PublishSpec;

typedef enum ObjectType
{
	ObjectType_primitive,				// PrimitiveInfo
	ObjectType_enumerate,				// EnumInfo

	ObjectType_defined,					// DefinedInfo			typedef {[union|struct]} {tgt_type} {src_type}...

	ObjectType_bits,					// BitsInfo

	ObjectType_structure,				// StructureInfo		typedef struct ? ...;
	ObjectType_union,					// UnionInfo			typedef union ? ...;
	ObjectType_array,					// ArrayInfo			typedef {table|array} ? ...;

	ObjectType_declare,					// str_t				{struct|union} ?;

	ObjectType_extern,					// ExternInfo			typedef entern ? ...;		<= type from include in header
	ObjectType_reference,				// ExternInfo			typedef reference ? ...;	<= type from include in source

	ObjectType_func,					// FunctionInfo			typedef func {ret_type} ? ...;
	ObjectType_index,					// IndexInfo			typedef indec ? ...;

	//////////////////////////////////////////////////////
	// Non-Variable
	ObjectType_constant,				// ConstantInfo			typedef constant ? ...;
	ObjectType_macro,					// {no data}			# {define|ifdef|ifndef|else|endif} ?;
	// Non-Variable
	//////////////////////////////////////////////////////

	ObjectType_max
} ObjectType;

typedef enum ObjectInstanceType
{
	ObjectInstanceType_primitive		= ObjectType_primitive,
	ObjectInstanceType_enumerate		= ObjectType_enumerate,
	ObjectInstanceType_func				= ObjectType_func,

	ObjectInstanceType_structure		= ObjectType_structure,
	ObjectInstanceType_union			= ObjectType_union,
	ObjectInstanceType_array			= ObjectType_array,
	ObjectInstanceType_index			= ObjectType_index,

	ObjectInstanceType_extern			= ObjectType_extern,
	ObjectInstanceType_reference		= ObjectType_reference,

	ObjectInstanceType_max				= ObjectType_max,
} ObjectInstanceType;

DZ1_CPPLINK str_t ObjectTypeStr(ObjectType v);

#define OBJECT_API_NONE						0x00000000

// Foundation API
#define OBJECT_API_NEW						0x80000000
#define OBJECT_API_DEL						0x40000000
#define OBJECT_API_DELANDSETNULL			0x20000000
// Optional API
#define OBJECT_API_CLONE					0x10000000
#define OBJECT_API_DUMP						0x08000000
#define OBJECT_API_CMP						0x04000000
//#define OBJECT_API_CODEC					0x02000000
#define OBJECT_API_FDUMP					0x01000000
#define OBJECT_API_GEN						0x00800000

#define OBJECT_API_ASN_CONV					0x00400000

#define OBJECT_API_USER_NEW					0x00080000
#define OBJECT_API_USER_DEL					0x00040000
//#define OBJECT_API_USER_DEL_AND_SET_NULL	0x00020000

#define OBJECT_API_USER_CLONE				0x00010000
#define OBJECT_API_USER_DUMP				0x00008000
#define OBJECT_API_USER_CMP					0x00004000
//#define OBJECT_API_USER_CODEC				0x00002000
#define OBJECT_API_USER_FDUMP				0x00001000
#define OBJECT_API_USER_GEN					0x00000800

#define OBJECT_API_USER_ASN_CONV			0x00000400

#define OBJECT_API_DUMP_MBCS				0x00000001
#define OBJECT_API_DUMP_WIDE				0x00000002
#define OBJECT_API_WINDOWS_ONLY				0x00000004

// No Dump API Set
#define OBJECT_API_BASE						(OBJECT_API_NEW | OBJECT_API_GEN | OBJECT_API_DEL | OBJECT_API_DELANDSETNULL)
//#define OBJECT_API_BASECMP				(OBJECT_API_BASE | OBJECT_API_CMP)
#define OBJECT_API_BASE_CLONE				(OBJECT_API_BASE | OBJECT_API_CLONE)

// Dump API Set
//#define OBJECT_API_BASE_DUMP				(OBJECT_API_BASE | OBJECT_API_DUMP)			// BASE + dump			 no fdump
//#define OBJECT_API_BASICMP				(OBJECT_API_BASE_DUMP | OBJECT_API_CMP)		// BASE + dump,cmp,		 no fdump
//#define OBJECT_API_BASICLONE				(OBJECT_API_BASE_DUMP | OBJECT_API_CLONE)	// BASE + dump,cmp,clone no fdump

//#define OBJECT_API_LOCAL					(OBJECT_API_BASIC | OBJECT_API_CMP | OBJECT_API_CLONE)

// (new gen del delAndSetNull) clone cmp
#define OBJECT_API_FANCY					(OBJECT_API_BASE_CLONE | OBJECT_API_CLONE | OBJECT_API_CMP)

// Fifo/Lifo API
// API:
// 	push, pop

#define OBJECT_DUMP_API_ALL					(OBJECT_API_DUMP | OBJECT_API_FDUMP)
#define OBJECT_CHSRSET_API_ALL				(OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE)

#define OBJECT_API_TDC_FULL					(OBJECT_API_FANCY | OBJECT_DUMP_API_ALL | OBJECT_CHSRSET_API_ALL)

#define PRIMITIVE_TYPE_API					(OBJECT_API_TDC_FULL | OBJECT_API_ASN_CONV)									// + asn_conv

// (0xFFFFFFFF & ~(OBJECT_API_USER_DUMP | OBJECT_API_USER_FDUMP))

typedef struct ObjectInfo
{
	ObjectType type;
	str_t name;					// Object의 이름
	str_t srcName;				// 타 스크립트에서 정의된 이 Object의 이름(예를 들면 asn같은..)
	u32_t api;					// 이 Object에 대하여 생성 할 API( bit flags )
	void *info;
} ObjectInfo;

DZ1_CPPLINK ObjectInfo *ObjectInfo_new(ObjectType type, str_t name,	str_t srcName, u32_t api, void *info, /* int imported, */Dz1Error *err);
DZ1_CPPLINK void ObjectInfo_del(ObjectInfo *p);
DZ1_CPPLINK void ObjectInfo_dump(ObjectInfo *p, int tab);
static __inline__ void ObjectInfo_delAndSetNull(void *ptr)
{
	ObjectInfo **p = (ObjectInfo **)ptr;
	ObjectInfo_del(*p); *p = NULL;
}
DZ1_CPPLINK int ObjectInfo_cmp(ObjectInfo *a, ObjectInfo *b);

DZ1_CPPLINK str_t ObjectInfo_nameOf(ObjectInfo *p);					// primitive type인 경우 원본 정의의 이름, 아니면 p->name

DZ1_CPPLINK str_t ObjectInfo_prefixOf(ObjectInfo *p,				// primitive type인 경우 원본 정의의 prefix
									  struct PublishSpec *spec);	// enumerate type인 경우 사용자 설정에 따른 enum prefix
																	// 외부 정의 터입 또는 후행정의 타입의 경우 ExtInfo의 prefix
																	// 그 외의 경우 자신의 name을 prefix로 사용

DZ1_CPPLINK u32_t ObjectInfo_apiOf(ObjectInfo *p,					// primitive type인 경우 모든 API
								   struct PublishSpec *spec);		// enum type인 경우 bit flags가 모두 0이면 모든 API, 아니면 bit flags사용
																	// array type인 경우 element의 bit flags
																	// defined type인 경우 원본 type의 bit flags
																	// 그 외에는 자신의 api bit flags

DZ1_CPPLINK int ObjectInfo_isPrimitive(ObjectInfo *p);				// primitive, enumerate type의 경우 TRUE
																	// defined type의 경우 원본에 따라 TRUE | FALSE
																	// 그 외에는 모두 FALSE

DZ1_CPPLINK bool_t ObjectInfo_isNullScalar(ObjectInfo *p);			// primitive type이면서 NULL을 의미하는 값이 있는 경우 TRUE

DZ1_CPPLINK int ObjectInfo_isScalar(ObjectInfo *p);					// primitive type인 경우 storage 속성에 따라 TRUE | FALSE
																	// 외부 정의(native), 또는 후행정의(referenced) type인 경우 ExternInfo의 isStatic값
																	// 그 외에는 모두 TRUE

DZ1_CPPLINK int ObjectInfo_isVoid(ObjectInfo *p);					// primitive type인 경우 storage 속성에 따라 TRUE | FALSE
																	// 그 외에는 모두 FALSE

DZ1_CPPLINK int ObjectInfo_isClonable(ObjectInfo *p,				// primitive type인 경우 TRUE
									  struct PublishSpec *spec);	// 그 외에는 api bit flags에 따라 TRUE | FALSE

DZ1_CPPLINK int ObjectInfo_isStaticSize(ObjectInfo *p);				// 고정길이 인가?

DZ1_CPPLINK int ObjectInfo_isComparable(ObjectInfo *p,				// 비교 가능한가?
										struct PublishSpec *spec);
DZ1_CPPLINK ObjectInfo *ObjectInfo_getOrigin(ObjectInfo *p);		// defined type인 경우 원본의 정보
																	// 그 외에는 자기 자신

static __inline__ ObjectType ObjectInfo_typeOf(ObjectInfo *p)
{
	ObjectInfo *origin = ObjectInfo_getOrigin(p);
	return origin ? origin->type : ObjectType_max;
}

//int ObjectInfo_asPrimitive(ObjectInfo *p);
DZ1_CPPLINK ObjectInfo *ObjectInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t ObjectInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t ObjectInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
