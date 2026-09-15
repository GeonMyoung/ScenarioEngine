#ifndef MDEFC_COMMON_H
#define MDEFC_COMMON_H

#include <dz1_error.h>

#define TCHAR_NAME				"TCHAR"
#define TSTRING_NAME			"TString"

#define INT8TYPE_NAME			"int8"
#define INT16TYPE_NAME			"int16"
#define INT32TYPE_NAME			"int32"
#define INT64TYPE_NAME			"int64"

#define UINT8TYPE_NAME			"uint8"
#define UINT16TYPE_NAME			"uint16"
#define UINT32TYPE_NAME			"uint32"
#define UINT64TYPE_NAME			"uint64"

#define REALTYPE_NAME			"real"
#define REAL32TYPE_NAME			"real32"
#define REAL64TYPE_NAME			"real64"

#define BOOLTYPE_NAME			"bool"

#define STRTYPE_NAME			"str"
#define WSTRTYPE_NAME			"wstr"

#define TIMETYPE_NAME			"time"
#define IPv4TYPE_NAME			"Dz1IPv4"
#define VOIDTYPE_NAME			"void"

#define ENUMTYPE_NAME			"uint32"

typedef enum FORWARD_TYPE
{
	FORWARD_TYPE_NONE		= 0,
	FORWARD_TYPE_STRUCT		= 1,
	FORWARD_TYPE_UNION		= 2,
	FORWARD_TYPE_ENUM		= 3,
	FORWARD_TYPE_IMPORT		= 4
} FORWARD_TYPE;
#define  FORWARD_TYPE_max		5

DZ1_CPPLINK str_t	 FORWARD_TYPE_StrA(FORWARD_TYPE v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t	 FORWARD_TYPE_StrW(FORWARD_TYPE v);
#ifdef UNICODE
#define				 FORWARD_TYPE_Str		FORWARD_TYPE_StrW
#else // UNICODE
#define				 FORWARD_TYPE_Str		FORWARD_TYPE_StrA
#endif // UNICODE
#else	// UNIX_SYSTEM
#define				 FORWARD_TYPE_Str		FORWARD_TYPE_StrA
#endif	// UNIX_SYSTEM

static __inline__ str_t forwardCaster(FORWARD_TYPE type)
{
	switch(type)
	{
	case FORWARD_TYPE_NONE:		return "";			break;
	case FORWARD_TYPE_STRUCT:
	case FORWARD_TYPE_UNION:	return "struct ";	break;
	case FORWARD_TYPE_ENUM:		return "enum ";		break;
	case FORWARD_TYPE_IMPORT:
	default:
		printf("forwardCaster() : type = %d\n", type);
		return "#error !!forwardCaster!! ";
		break;
	}

// 	if (type == FORWARD_TYPE_NONE) return "";
// 	else if (type == FORWARD_TYPE_STRUCT) return "struct ";
// 	else if (type == FORWARD_TYPE_UNION) return "struct ";
// 	else if (type == FORWARD_TYPE_ENUM) return "enum ";
// 	else
// 	{
// 		printf("forwardCaster() : type = %d\n", type);
// 		return "#error !!forwardCaster!! ";
// 	}
}

typedef enum MemberDumpMode
{
	MemberDumpMode_normal,
	MemberDumpMode_value,					// API 를 통한 dump 금지
	MemberDumpMode_omit,					// dump 안함
	MemberDumpMode_cascade					// 재귀형 member 또는 LinkedList 유형 dump
} MemberDumpMode;

typedef struct MemberProperty
{
	struct ObjectInfo	*type;				// References
	str_t				 srcType;			// 타 스크립드에서 이 Member Type을 사용한 명칭
	int					 isForwarded;		// struct or union
	int					 isPointer;			// *
	int					 isReferenced;		// delete or not
	MemberDumpMode		 dumpMode;			// nodump, cascade 등
} MemberProperty;

#define MEMBER_FLAG_IS_REFERENCED			0x00000001
#define MEMBER_FLAG_ARG_INVOLVE				0x00000002
#define MEMBER_FLAG_IS_INDEX				0x00000004
#define MEMBER_FLAG_IS_ARRAY				0x00000008
#define MEMBER_FLAG_IS_ARRAY_REF_ELEM		0x00000010

#define MEMBER_FLAG_ASN_OPTIONAL			0x80000000

#define MemberFlag_isReferenced(flags)		((flags & MEMBER_FLAG_IS_REFERENCED) ? TRUE : FALSE)
#define MemberFlag_isArgInvolve(flags)		((flags & MEMBER_FLAG_ARG_INVOLVE) ? TRUE : FALSE)
#define MemberFlag_isIndex(flags)			((flags & MEMBER_FLAG_IS_INDEX) ? TRUE : FALSE)
#define MemberFlag_isArray(flags)			((flags & MEMBER_FLAG_IS_ARRAY) ? TRUE : FALSE)
#define MemberFlag_isArrayElemRef(flags)	((flags & MEMBER_FLAG_IS_ARRAY_REF_ELEM) ? TRUE : FALSE)

#define MemberFlag_isAsnOptional(flags)		((flags & MEMBER_FLAG_ASN_OPTIONAL) ? TRUE : FALSE)
#endif

