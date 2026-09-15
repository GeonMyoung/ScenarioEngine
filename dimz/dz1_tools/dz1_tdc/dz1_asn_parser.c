#include <ctype.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_aatree.h>
#include <dz1_parser.h>
#include <dz1_parser_init.h>
#include <dz1_fifo.h>

#include <Dz1TdcInfoModule.h>

#include "dz1_mdefc_parser.h"
#include "dz1_asn_parser.h"
#include "misc.h"

static int tab = 0;
//#define tValTake(dst)		do { (dst) = t->v; t->v = NULL; } while(0)
typedef struct Dz1Asn1ParserEntry
{
	struct Dz1Asn1ParserEntry *prev;
	ObjectInfo *target;
	ObjectInfo **objPtr;
	EnumEntry enumEntry;
	StructMemberEntry structEntry;
	UnionMemberEntry unionEntry;
	str_t memberSrcName;
} Dz1Asn1ParserEntry;

static void Dz1Asn1ParserEntry_del(Dz1Asn1ParserEntry *p)
{
	if (p == NULL) return;
	if (p->prev) Dz1Asn1ParserEntry_del(p->prev);
	if (p->target) ObjectInfo_del(p->target);
	if (p->enumEntry.name) Dz1Str_delAndSetNull(&p->enumEntry.name);
	if (p->enumEntry.valStr) Dz1Str_delAndSetNull(&p->enumEntry.valStr);
	if (p->structEntry.instance) Dz1Str_delAndSetNull(&p->structEntry.instance);
	if (p->unionEntry.instance) Dz1Str_delAndSetNull(&p->unionEntry.instance);
	if (p->memberSrcName) Dz1Str_delAndSetNull(&p->memberSrcName);
	Dz1Free(p);
}

static void Dz1Asn1ParserEntry_delAndSetNull(void *ptr)
{
	Dz1Asn1ParserEntry **p = (Dz1Asn1ParserEntry **)ptr;
	Dz1Asn1ParserEntry_del(*p); *p = NULL;
}

static Dz1Asn1ParserEntry *Dz1Asn1ParserEntry_new(str_t name, str_t srcName, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1ParserEntry *ret = NULL;
	if ((ret = (Dz1Asn1ParserEntry *)Dz1Calloc(sizeof(Dz1Asn1ParserEntry), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1ParserEntry_delAndSetNull, (void *)&ret);
		if ((ret->target = ObjectInfo_new((ObjectType)-1, name, srcName, OBJECT_API_BASE_CLONE | OBJECT_API_DUMP | OBJECT_API_FDUMP | OBJECT_API_ASN_CONV, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->objPtr = &ret->target;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1ParserEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

typedef void Dz1Asn1ForwardTree;
//static __inline__ int ObjectInfo_cmp(ObjectInfo *a, ObjectInfo *b) { return strcmp(a->name, b->name); }
static Dz1Asn1ForwardTree *Dz1Asn1ForwardTree_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1ForwardTree *ret = Dz1AATree_new((Dz1CmpFunc)ObjectInfo_cmp, (Dz1DelFunc)ObjectInfo_del, (Dz1DumpFunc)ObjectInfo_dump, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ObjectInfo *Dz1Asn1ForwardTree_add(Dz1Asn1ForwardTree *p, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo *node = ObjectInfo_new(ObjectType_max, name, NULL, -1, NULL, errp), *ret = NULL;
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&node);

		if ((*errp = Dz1AATree_insert(p, (void *)node)).code) ERR_OUT(errp);
		else { ret = node; node = NULL; }

		pthread_cleanup_pop(1); // (ObjectInfo_delAndSetNull, (void *)&node);
	}
	return ret;
}

static ObjectInfo *Dz1Asn1ForwardTree_find(Dz1Asn1ForwardTree *p, str_t name)
{
	ObjectInfo key;
	key.name = name;
	return (ObjectInfo *)Dz1AATree_find(p, (void *)&key);
}

static ObjectInfo *Dz1Asn1ForwardTree_extract(Dz1Asn1ForwardTree *p, str_t name)
{
	ObjectInfo key;
	key.name = name;
	return (ObjectInfo *)Dz1AATree_extract(p, (void *)&key);
}

static void Dz1Asn1ForwardTree_del(Dz1Asn1ForwardTree *p)
{
	if (p == NULL) return;
	Dz1AATree_del(p);
}

/*
static void Dz1Asn1ForwardTree_delAndSetNull(void *ptr)
{
	Dz1Asn1ForwardTree **p = (Dz1Asn1ForwardTree **)ptr;
	Dz1Asn1ForwardTree_del(*p); *p = NULL;
}
*/

typedef struct Dz1Asn1ParserEnv
{
	str_t filename;
	PublishSpec *spec;
	IncludeSpec *inc;

	str_t include;

	Dz1Asn1ForwardTree *forwardTree;
	Dz1MdefcModule *module;

	Dz1Asn1ParserEntry *current;
	ObjectInfo *refObj;
	str_t refName;

	bool_t integer_restrict_range;

	bool_t integer_value_set;

	bool_t integer_min_minus_signed;
	u64_t integer_min;

	bool_t integer_max_minus_signed;
	u64_t integer_max;

} Dz1Asn1ParserEnv;

static Dz1Error _push_entry(Dz1Asn1ParserEnv *dst, Dz1Asn1ParserEntry *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || e == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		e->prev = dst->current;
		dst->current = e;
	}
	return err;
}

static Dz1Asn1ParserEntry *_pop_entry(Dz1Asn1ParserEnv *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1ParserEntry *ret = src->current;
	if (ret == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		src->current = ret->prev;
		ret->prev = NULL;
	}
	return ret;
}

/*
static void _push_entry_cancel(void *ptr)
{
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)env;
	_pop_entry(env, NULL);
}
*/

static void Dz1Asn1ParserEnv_clean(Dz1Asn1ParserEnv *p)
{
	if (p->module) Dz1MdefcModule_del(p->module);
	if (p->current) Dz1Asn1ParserEntry_del(p->current);
	if (p->forwardTree) Dz1Asn1ForwardTree_del(p->forwardTree);
	if (p->include) Dz1Str_delAndSetNull(&p->include);
	if (p->refName) Dz1Str_delAndSetNull(&p->refName);
}

static str_t syntax = ""
"main = <symbol>=new_module [<AsnOIDValue>] DEFINITIONS [<AsnTag>] <assign> BEGIN [<AsnImport>]* [<SYMBOLS>]+ END <done>;\n"
"\n"
"AsnOIDValue=<liststart> [<AsnOIDValueElement>]+ <listend>;\n"
"AsnOIDValueElement=<number>|<AsnOIDNamedValue>;\n"
"AsnOIDNamedValue=<symbol> <lbracket> <number> <rbracket>;\n"
"\n"
"AsnTag = AUTOMATIC TAGS;\n"
"\n"
"AsnImport = IMPORTS <AsnImportNames> FROM <symbol>=set_include [<AsnOIDValue>] <semicolon>=do_asn_include;\n"
"AsnImportNames = <symbol> [<AsnImportNameMore>]*;\n"
"AsnImportNameMore = <comma> <symbol>;\n"
"\n"
"SYMBOLS = <symbol>=new_target_with_name <assign> <AsnTypes>=add_target_to_module;\n"
"\n"
"AsnTypes = <AsnSimpleType>|<AsnEnum>|<AsnSequence>|<AsnChoice>|<AsnClass>|<AsnSymbol>;\n"
"\n"
"AsnSimpleType = <AsnSingleWordType>|<AsnInteger>|<AsnReal>|<AsnString>|<AsnBitString>|<AsnRef>|<AsnOID>;\n"
"AsnSingleWordType = BOOLEAN|GeneralizedTime|NULL=set_obj_type;\n"
"\n"
"AsnGeneralExt = <comma> <dotdotdot>;\n"
"\n"
"AsnGeneralEnumSpec = <liststart> <AsnGeneralEnumSpecElements> <listend>;\n"
"AsnGeneralEnumSpecElements = <AsnGeneralEnumSpecElement> [<AsnGeneralEnumSpecElementMore>]* [<AsnGeneralExt>];\n"
"AsnGeneralEnumSpecElement = <symbol> [<AsnGeneralEnumSpecElementValue>];\n"
"AsnGeneralEnumSpecElementValue = <lbracket> <number> <rbracket>;\n"
"AsnGeneralEnumSpecElementMore = <comma> <AsnGeneralEnumSpecElement>;\n"
"\n" // AsnInteger
"AsnInteger = INTEGER=set_obj_type [<AsnGeneralEnumSpec>] [<AsnIntegerSpec>];\n"
"AsnIntegerSpec = <lbracket>=set_integer_restrict_prepare <number>=set_integer_value [<AsnIntegerRange>] <rbracket>=change_object_type;\n"
"AsnIntegerRange = <dotdot> <number>=set_integer_value [<AsnGeneralExt>];\n"
"\n" // AsnReal
"AsnReal = REAL=set_obj_type [<AsnRealSpec>];\n"
"AsnRealSpec = <lbracket> <number> [<AsnRealRange>] <rbracket>;\n"
"AsnRealRange = <dotdot> <number>;\n"
"\n" // SIZE Spec
"AsnSizeSpec = SIZE <lbracket> <number> [<AsnSizeSpecMore>] [<AsnGeneralExt>] <rbracket>;\n"
"AsnSizeSpecMore = <dotdot> <number>;\n"
"\n" // AsnString
"AsnString = <AsnOctetStr>|<AsnStringNames> [<AsnStringSpec>];\n"
"AsnOctetStr = OCTET STRING=set_obj_type_bin;\n"
"AsnStringNames = UTF8String|UniversalString|PrintableString|VisibleString=set_obj_type;\n"
"AsnStringSpec = <lbracket> <AsnSizeSpec> <rbracket>;\n"
//"AsnStringSpec = <lbracket> SIZE <lbracket> <number> [<AsnStringSizeMore>] [<AsnStringSizeExt>] <rbracket> <rbracket>;\n"
//"AsnStringSizeMore = <dotdot> <number>;\n"
//"AsnStringSizeExt = <comma> <dotdotdot>;\n"
"\n" // AsnOID
"AsnOID = OBJECT IDENTIFIER=set_obj_type_oid;\n"
"\n" // AsnRef
"AsnRef = <symbol>=find_struct_object <dot> <and> <symbol>=set_obj_type_from_ref;\n"
"\n"
"AsnSymbol = <symbol>=set_obj_type_symbol;\n"
"\n" // AsnEnum
"AsnEnum = ENUMERATED=set_obj_type <liststart>=prepare_enum <AsnEnumElements> <listend>;\n"
"AsnEnumElements = <AsnEnumElement>=add_to_enums [<AsnEnumElementMore>]* [<AsnEnumElementFinal>];\n"
"AsnEnumElement = <symbol>=set_enum_name [<AsnEnumElementValue>];\n"
"AsnEnumElementValue = <lbracket> <number>=set_enum_val <rbracket>;\n"
"AsnEnumElementMore = <comma> <AsnEnumElement>=add_to_enums;\n"
"AsnEnumElementFinal = <comma> <dotdotdot>;\n"
"\n" // AsnBitString
"AsnBitString = BIT STRING=set_obj_type_bits [<AsnBitStringEnumSpec>] [<AsnBitStringSpec>];\n"
"AsnBitStringEnumSpec = <liststart> <AsnBitsElements> <listend>;\n"
"AsnBitsElements = <AsnBitsElement> [<AsnBitsElementMore>]* [<AsnGeneralExt>];\n"
"AsnBitsElement = <symbol>=show_token <lbracket> <number>=show_token <rbracket>=new_line;\n"
"AsnBitsElementMore = <comma> <AsnBitsElement>;\n"
//"AsnBitsElementFinal = <comma> <dotdotdot>;\n"
"AsnBitStringSpec = <lbracket> SIZE <lbracket> <number> <rbracket> <rbracket>;\n"
"\n" // AsnSequence
"AsnSequence = SEQUENCE|SET=set_obj_type <AsnStruct>|<AsnList>;\n"
"\n" // AsnChoice
"AsnChoice = CHOICE=set_obj_type <AsnUnion>|<AsnList>;\n"
"\n" // AsnStruct
"AsnStruct = <liststart>=prepare_struct <AsnStructMembers> <listend>;\n"
"AsnStructMembers = <AsnStructMember>=add_to_struct_members [<AsnStructMemberMore>]* [<AsnGeneralExt>];\n"
"AsnStructMember = <symbol>=set_struct_member_instance <AsnMemberType>=correct_member_pointer [<AsnStrucMemberSpec>];\n"
"AsnStructMemberMore = <comma> <AsnStructMember>=add_to_struct_members;\n"
//"AsnStructMemberLast = <comma> <dotdotdot>;\n"
"AsnStrucMemberSpec = <AsnStructMemberOptional>|<AsnStructMemberDefault>;\n"
"AsnStructMemberOptional = OPTIONAL=set_struct_member_optional;\n"
"AsnStructMemberDefault = DEFAULT <number>|<symbol>;\n"
"\n" // AsnUnion
"AsnUnion = <liststart>=prepare_union <AsnUnionMembers> <listend>;\n"
"AsnUnionMembers = <AsnUnionMember>=add_to_union_members [<AsnUnionMemberMore>]*;\n"
"AsnUnionMember = <dotdotdot>|<AsnUnionMemberInstance>;\n"
"AsnUnionMemberInstance = <symbol>=set_union_member_instance [<AsnMemberTag>] <AsnMemberType>=correct_member_pointer;\n"
"AsnUnionMemberMore = <comma> <AsnUnionMember>=add_to_union_members;\n"
//"AsnUnionMemberLast = <comma> <dotdotdot>;\n"
"\n" // AsnList
"AsnList = [<AsnListSizeSpec>] OF=set_obj_type_list_prepare <AsnMemberType>=correct_member_pointer;\n"
"AsnListSizeSpec = <lbracket> <AsnSizeSpec> <rbracket>;\n"
"\n"
"AsnMemberTag = <blockstart> <number>=set_union_member_present <blockend>;\n"
"\n" // AsnMember
"AsnMemberType = <AsnSimpleType>|<AsnMemberUnnamedType>|<AsnSymbol>;\n"
"AsnMemberUnnamedType = <AsnUnnamedType>=set_member_type_named;\n"
"\n"
"AsnUnnamedType = <AsnUnnamedEnum>|<AsnUnnamedSequence>|<AsnUnnamedChoice>=add_target_to_module;\n"
"\n"
"AsnUnnamedEnum = ENUMERATED=new_target_named_enum <liststart>=prepare_enum <AsnEnumElements> <listend>;\n"
"\n"
"AsnUnnamedSequence = SEQUENCE=new_target_named_struct <AsnStruct>|<AsnList>;\n"
"\n"
"AsnUnnamedChoice = CHOICE=new_target_named_union <AsnUnion>|<AsnList>;\n"
"\n"
"AsnClass = CLASS=set_obj_type <liststart>=prepare_struct <AsnClassMembers> <listend> WITH SYNTAX <liststart> [<AsnClassSyntax>]+ <listend>;\n"
"AsnClassMembers = <AsnClassMember>=add_to_struct_members [<AsnClassMemberMore>]*;\n"
"AsnClassMember = <and> <symbol>=set_struct_member_instance [<AsnMemberType>=correct_member_pointer] [OPTIONAL];\n"
"AsnClassMemberMore = <comma> <AsnClassMember>=add_to_struct_members;\n"
"\n"
"AsnClassSyntax= <AsnClassSyntaxMandatory>|<AsnClassSyntaxOptional>;\n"
"AsnClassSyntaxMandatory = <symbol> <and> <symbol>;\n"
"AsnClassSyntaxOptional = <blockstart> <AsnClassSyntaxMandatory> <blockend>;\n"
"";

static Dz1Error show_token(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Thread_tprintf(tab, "Token = %s\n", t->v);

	return err;
}

static Dz1Error new_line(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Thread_printf("\n");

	return err;
}

static u32_t _getSignedMinusSize(s64_t v)
{
	u32_t ret = 0;
	if		(v >= DZ1INT64(0xFFFFFFFFFFFFFF80)) ret = 8;
	else if (v >= DZ1INT64(0xFFFFFFFFFFFF8000)) ret = 16;
	else if (v >= DZ1INT64(0xFFFFFFFF80000000)) ret = 32;
	else ret = 64;
	return ret;
}

static u32_t _getSignedPlusSize(s64_t v)
{
	u32_t ret = 0;
	if (v <= DZ1INT64(0x7F)) ret = 8;
	else if (v <= DZ1INT64(0x7FFF)) ret = 16;
	else if (v <= DZ1INT64(0x7FFFFFFF)) ret = 32;
	else ret = 64;
	return ret;
}

static u32_t _getUnsignedSize(u64_t v)
{
	u32_t ret = 0;
	if (v <= DZ1UINT64(0xFF)) ret = 8;
	else if (v <= DZ1UINT64(0xFFFF)) ret = 16;
	else if (v <= DZ1UINT64(0xFFFFFFFF)) ret = 32;
	else ret = 64;
	return ret;
}

static Dz1Error change_object_type(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	bool_t isMember = (*p->objPtr == p->target) ? FALSE : TRUE;
	ObjectInfo *origin = NULL;

	char name[32];

	bool_t needSigned = FALSE;
	u32_t size = 0;
	{	// size selection by range
		u32_t sizeMin = 0, sizeMax = 0;
		if (env->integer_min_minus_signed || env->integer_max_minus_signed) needSigned = TRUE;

		if (needSigned)
		{
			if (env->integer_min_minus_signed) sizeMin = _getSignedMinusSize(-(s64_t)env->integer_min);
			else sizeMin = _getSignedPlusSize((s64_t)env->integer_min);

			if (env->integer_max_minus_signed) sizeMax = _getSignedMinusSize(-(s64_t)env->integer_max);
			else sizeMax = _getSignedPlusSize((s64_t)env->integer_max);
		}
		else
		{
			sizeMin = _getUnsignedSize(env->integer_min);
			sizeMax = _getUnsignedSize(env->integer_max);
		}
		size = sizeMin > sizeMax ? sizeMin : sizeMax;
	}

	sprintf(name, "%s%u", needSigned ? "int" : "uint", size);

	if ((origin = env->module->findObject(env->module, name)) == NULL)
	{
		ERR_SET_OUT(&err, ENOENT);
	}
	else
	{
		if (isMember) *(p->objPtr) = origin;
		else
		{
			DefinedInfo *info = (DefinedInfo *)p->target->info;
			info->origin = origin;
		}
	}
	return err;
}

static Dz1Error set_integer_restrict_prepare(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	env->integer_value_set = FALSE;
	env->integer_min_minus_signed = FALSE;
	env->integer_min = 0;
	env->integer_max_minus_signed = FALSE;
	env->integer_max = 0;
	return err;
}

static void _setMinValue(Dz1Asn1ParserEnv *env, bool_t isMinus, u64_t v)
{
	if (isMinus)
	{	// 음수
		s64_t b = -(s64_t)v;
		if (env->integer_min_minus_signed)
		{	// 최소값도 음수 -> 비교해서 더 작은거
			s64_t a = -(s64_t)env->integer_min;
			env->integer_min = (u64_t)(a < b ? env->integer_min : v);
		}
		else
		{	// 최소값이 양수 -> 바로 대입
			env->integer_min_minus_signed = TRUE;
			env->integer_min = v;
		}
	}
	else
	{	// 양수
		u64_t b = v;
		if (env->integer_min_minus_signed)
		{	// 최소값이 음수 -> 짤없음
		}
		else
		{	// 최소값이 양수 -> 비교해서 더 작은거
			u64_t a = env->integer_min;
			env->integer_min = (a < b ? env->integer_min : v);
		}
	}
}

static void _setMaxValue(Dz1Asn1ParserEnv *env, bool_t isMinus, u64_t v)
{
	if (isMinus)
	{	// 음수
		s64_t b = -(s64_t)v;
		if (env->integer_max_minus_signed)
		{	// 최대값도 음수 -> 비교해서 더 킁거
			s64_t a = -(s64_t)env->integer_max;
			env->integer_max = (u64_t)(a > b ? env->integer_max : v);
		}
		else
		{	// 최대값이 양수 -> 짤없음
		}
	}
	else
	{	// 양수
		u64_t b = v;
		if (env->integer_max_minus_signed)
		{	// 최대값이 음수 -> 바로 대입
			env->integer_max_minus_signed = FALSE;
			env->integer_max = v;
		}
		else
		{	// 최소대값이 양수 -> 비교해서 더 킁거
			u64_t a = env->integer_max;
			env->integer_max = (a > b ? env->integer_max : v);
		}
	}
}

static Dz1Error set_integer_value(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;

	char *cp = t->v;

	if (env->integer_value_set == FALSE)
	{
		env->integer_value_set = TRUE;
		if (*cp == '-')
		{
			env->integer_min_minus_signed = TRUE;
			env->integer_max_minus_signed = TRUE;
			cp++;
		}
		else
		{
			env->integer_min_minus_signed = FALSE;
			env->integer_max_minus_signed = FALSE;
		}
		env->integer_min = env->integer_max = Dz1Ato64(cp);
	}
	else
	{
		u64_t v = 0;
		bool_t isMinus = FALSE;
		if (*cp == '-')
		{
			isMinus = TRUE;
			cp++;
		}
		v = Dz1Ato64(cp);
		_setMinValue(env, isMinus, v);
		_setMaxValue(env, isMinus, v);
	}
	return err;
}

/*
static Dz1Error set_integer_max(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;

	if (t->v[0] == '-') env->integer_max_minus_signed = TRUE; else env->integer_max_minus_signed = FALSE;
	env->integer_max = Dz1Ato64(t->v);
	return err;
}
*/
static Dz1Error new_module(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	if ((env->module = Dz1MdefcModule_new(env->filename, "asn", env->spec, &err)) == NULL) ERR_OUT(&err);
	else if ((err = Dz1MdefcModule_includeTDC(env->module, env->spec, env->inc, "libdz1_support")).code)
	{
		Dz1Thread_printf("!!! When compile ASN file, need \"libdz1_support.tdc\"\n");
		Dz1Thread_printf("!!! please set include path to load that file\n");
		ERR_OUT(&err);
	}
	else if ((err = Dz1MdefcModule_includeTDC(env->module, env->spec, env->inc, "dz1_asn1_support")).code)
	{
		Dz1Thread_printf("!!! When compile ASN file, need \"dz1_asn1_support.tdc\"\n");
		Dz1Thread_printf("!!! please set include path to load that file\n");
		ERR_OUT(&err);
	}
	return err;
}

static Dz1Error new_target_with_name(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;

	Dz1Asn1ParserEntry *e = NULL;
	char name[4096];

	if (strncmp(t->v, "Dz1", 3) == 0)
	{
		t->v = t->v;
	}
	sprintf(name, "Dz1%s", t->v);

	// Dz1Thread_tprintf(tab++, "New Type = %s\n", name);
	if ((e = Dz1Asn1ParserEntry_new(name, t->v, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Asn1ParserEntry_delAndSetNull, (void *)&e);
		if ((err = _push_entry(env, e)).code) ERR_OUT(&err);
		pthread_cleanup_pop(err.code); // (Dz1Asn1ParserEntry_delAndSetNull, (void *)&e);
	}
	return err;
}

static void _assignObjectInfo(ObjectInfo *dst, ObjectInfo *src)
{
	Dz1Str_delAndSetNull(&dst->name);
	Dz1Str_delAndSetNull(&dst->srcName);
	memcpy(dst, src, sizeof(ObjectInfo));
	memset(src, 0, sizeof(ObjectInfo));
}

static Dz1Error add_target_to_module(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *cur = _pop_entry(env, &err);
	if (cur == NULL) ERR_OUT(&err);
	else
	{
		ObjectInfo *fwd = NULL;
		ObjectInfo *target = cur->target;
		pthread_cleanup_push(Dz1Asn1ParserEntry_delAndSetNull, (void *)&cur);
		if ((fwd = Dz1Asn1ForwardTree_extract(env->forwardTree, target->name)) != NULL)
		{
			_assignObjectInfo(fwd, target); // copy member value and zero set target
//			Dz1Thread_tprintf(--tab, "Add Type : %s(%s)\n", fwd->name, fwd->srcName);
			if ((*errp = ParserHelp_addPresentObj(env->module, fwd)).code) ERR_OUT(errp);
			else if ((env->module->addObject(env->module, fwd)).code) ERR_OUT(&err);
		}
		else
		{
//			Dz1Thread_tprintf(--tab, "Add Type : %s(%s)\n", target->name, target->srcName);
			if ((*errp = ParserHelp_addPresentObj(env->module, target)).code) ERR_OUT(errp);
			else if ((env->module->addObject(env->module, cur->target)).code) ERR_OUT(&err);
			else cur->target = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1Asn1ParserEntry_delAndSetNull, (void *)&cur);
	}
	return err;
}

static Dz1Error set_obj_type(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *cur = env->current;
	ObjectInfo *chk = *cur->objPtr;
	bool_t isMember = ((chk == cur->target) ? FALSE : TRUE);
	if (strcmp(t->v, "BOOLEAN") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "bool");
		if (isMember) 
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "REAL") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "real");
		if (isMember)
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "GeneralizedTime") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "Dz1TimeVal");
		if (isMember)
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "INTEGER") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "int64");
		if (isMember)
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "NULL") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "Dz1Asn1Null");
		if (isMember)
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "UTF8String") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "Dz1Asn1UTF8Str");
		if (isMember)
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "VisibleString") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "Dz1Asn1VisibleStr");
		if (isMember)
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "UniversalString") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "Dz1Asn1UniversalStr");
		if (isMember)
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "PrintableString") == 0)
	{
		ObjectInfo *origin = env->module->findObject(env->module, "Dz1Asn1OctetStr");
		if (isMember)
		{
			*(cur->objPtr) = origin;
			Dz1Str_delAndSetNull(&cur->memberSrcName);
			cur->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *cur->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}
	else if (strcmp(t->v, "ENUMERATED") == 0)
	{	// always isMember == FALSE
		ObjectInfo *target = *cur->objPtr;
		target->type = ObjectType_enumerate;
	}
	else if (strcmp(t->v, "SEQUENCE") == 0 || strcmp(t->v, "SET") == 0)
	{	// always isMember == FALSE
		ObjectInfo *target = *cur->objPtr;
		target->type = ObjectType_structure;
	}
	else if (strcmp(t->v, "CHOICE") == 0)
	{	// always isMember == FALSE
		ObjectInfo *target = *cur->objPtr;
		target->type = ObjectType_union;
	}
	else if (strcmp(t->v, "CLASS") == 0)
	{	// always isMember == FALSE
		ObjectInfo *target = *cur->objPtr;
		target->type = ObjectType_structure;
	}
	else if (strcmp(t->v, "OF") == 0)
	{	// always isMember == FALSE
		ObjectInfo *target = *cur->objPtr;
		target->type = ObjectType_array;
		// target->api |= OBJECT_API_ASN_CONV;
	}
	else
	{
		Dz1Error_set(&err, ENOENT);
		return err;
	}

	return err;
}

static Dz1Error set_obj_type_bin(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *cur = env->current;
	bool_t isMember = (*cur->objPtr) == cur->target ? FALSE : TRUE;

	ObjectInfo *origin = env->module->findObject(env->module, "Dz1Asn1OctetStr");
	if (isMember)
	{
		*(cur->objPtr) = origin;
		Dz1Str_delAndSetNull(&cur->memberSrcName);
		if ((cur->memberSrcName = Dz1Str_dup("OCTETSTRING", &err)) == NULL) ERR_OUT(&err);
	}
	else
	{
		ObjectInfo *target = *cur->objPtr;
		target->type = ObjectType_defined;
		if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
	}
	
	return err;
}

static Dz1Error set_obj_type_bits(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *cur = env->current;
	bool_t isMember = (*cur->objPtr) == cur->target ? FALSE : TRUE;

	ObjectInfo *origin = env->module->findObject(env->module, "Dz1Asn1BitStr");
	if (isMember)
	{
		*(cur->objPtr) = origin;
		Dz1Str_delAndSetNull(&cur->memberSrcName);
		if ((cur->memberSrcName = Dz1Str_dup("BITSTRING", &err)) == NULL) ERR_OUT(&err);
	}
	else
	{
		ObjectInfo *target = *cur->objPtr;
		target->type = ObjectType_defined;
		if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
	}
	
	return err;
}

static Dz1Error set_obj_type_oid(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *cur = env->current;
	bool_t isMember = (*cur->objPtr) == cur->target ? FALSE : TRUE;

	ObjectInfo *origin = env->module->findObject(env->module, "Dz1Asn1OID");
	if (isMember)
	{
		*(cur->objPtr) = origin;
		Dz1Str_delAndSetNull(&cur->memberSrcName);
		if ((cur->memberSrcName = Dz1Str_dup("OBJECTIDENTIFIER", &err)) == NULL) ERR_OUT(&err);
	}
	else
	{
		ObjectInfo *target = *cur->objPtr;
		target->type = ObjectType_defined;
		if ((target->info = DefinedInfo_new(FALSE, origin, &err)) == NULL) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error prepare_enum(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	ObjectInfo *target = *(p->objPtr);

	if ((target->info = EnumInfo_new(FALSE, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error add_to_enums(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	ObjectInfo *target = p->target;
	EnumInfo *info = (EnumInfo *)target->info;
	if ((err = info->enums->add(info->enums, p->enumEntry.name, p->enumEntry.valStr, &p->enumEntry.value)).code) ERR_OUT(&err);
	else
	{
		Dz1Str_delAndSetNull(&p->enumEntry.name);
		Dz1Str_delAndSetNull(&p->enumEntry.valStr);
	}
	return err;
}

static Dz1Error set_enum_name(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	p->enumEntry.name = t->v; t->v = NULL;
	return err;
}

static Dz1Error set_enum_val(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;

	p->enumEntry.valStr = t->v; t->v = NULL;
	p->enumEntry.value = Dz1Ato32(p->enumEntry.valStr);

	return err;
}

static Dz1Error prepare_struct(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	ObjectInfo *target = p->target;

	if ((target->info = StructureInfo_new(&err)) == NULL) ERR_OUT(&err);
	else p->objPtr = &p->structEntry.type;

	return err;
}

static Dz1Error add_to_struct_members(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	ObjectInfo *target = p->target;
	StructureInfo *info = (StructureInfo *)target->info;

	if (info == NULL)
	{
		ERR_SET_OUT(&err, EFAULT);
	}
	else
	{
//		if (p->structEntry.isAsnOptional)
		if (StructMemberEntry_isAsnOptional(&p->structEntry))
		{
			if (ObjectInfo_isScalar(p->structEntry.type))
				p->structEntry.isPointer = TRUE;
//			p->structEntry.argInvolve = FALSE;
			p->structEntry.memb_flags &= ~MEMBER_FLAG_ARG_INVOLVE;
		}
		else
		{
//			p->structEntry.argInvolve = TRUE;
			p->structEntry.memb_flags |= MEMBER_FLAG_ARG_INVOLVE;
			if (p->structEntry.isForwarded)
				p->structEntry.isPointer = TRUE;
		}

//		Dz1Thread_tprintf(tab, "@@@ Add Structure Member %s(%s)\n", p->structEntry.type->name, p->structEntry.srcType);
		if ((err = info->members->append(info->members, p->structEntry.isForwarded,
									p->structEntry.type, p->structEntry.srcType,
									p->structEntry.isPointer,
									p->structEntry.instance,
//									p->structEntry.isReferenced, 
									p->structEntry.memb_flags, 
									p->structEntry.dumpMode,
//									p->structEntry.argInvolve, p->structEntry.isIndex, p->structEntry.isAsnOptional,
									p->structEntry.arr_cnt_name)).code)
		{
			ERR_OUT(&err);
		}
		else
		{
			Dz1Str_delAndSetNull(&p->structEntry.instance); //p->structEntry.instance = NULL;
			Dz1Str_delAndSetNull(&p->structEntry.srcType); //p->structEntry.instance = NULL;
			p->structEntry.isPointer = FALSE;
			memset(&p->structEntry, 0, sizeof(StructMemberEntry));
			p = p;
		}
	}
	return err;
}

static ObjectInfo *_getOrigin(Dz1Asn1ParserEnv *env, str_t name, FORWARD_TYPE *fwd, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo *origin = NULL;
	if ((origin = env->module->findObject(env->module, name)) == NULL)
	{
		(*fwd) = FORWARD_TYPE_STRUCT;
		if ((origin = Dz1Asn1ForwardTree_find(env->forwardTree, name)) == NULL)
		{
			if ((origin = Dz1Asn1ForwardTree_add(env->forwardTree, name, errp)) == NULL)
				ERR_OUT(errp);
		}
	}
	return origin;
}

static str_t collisionNames[] =
{
	"auto",
//	"time",
	NULL
};

static bool_t isCollisionName(str_t src)
{
	str_t *i;
	for (i = collisionNames; *i != NULL; i++)
		if (strcmp(src, *i) == 0) return TRUE;
	return FALSE;
}

static str_t _chkMemberNameCollision(char dst[4096], str_t src)
{
	char temp[4096];
	if (isCollisionName(src))
	{
		sprintf(temp, "_%s", src);
		return _chkMemberNameCollision(dst, temp);
	}
	else
	{
		strcpy(dst, src);
		return dst;
	}
}

static Dz1Error set_struct_member_instance(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;

	//bool_t fwd = FALSE;

	char name[4096];
	_chkMemberNameCollision(name, t->v);
//	Dz1Thread_tprintf(tab, "* Structure Member Instance = %s\n", name);
	if ((p->structEntry.instance = Dz1Str_dup(name, &err)) == NULL) ERR_OUT(&err);
	else
	{
		p->structEntry.type = _getOrigin(env, "Dz1Asn1Any", &p->structEntry.isForwarded, &err);
		p->structEntry.isPointer = TRUE;
	}
	return err;
}

static bool_t _checkPointerRef(ObjectInfo *p)
{
	bool_t ret = FALSE;
	ExternInfo *info = (ExternInfo *)p->info;
	if (info->isStatic == FALSE) ret = TRUE;
	return ret;
}

static bool_t _checkPointer(ObjectInfo *p)
{
	bool_t ret = FALSE;
	ObjectType type = ObjectInfo_typeOf(p);
	switch(type)
	{
	default:
		type = type;
		break;
	case ObjectType_primitive:
	case ObjectType_enumerate:
	case ObjectType_func:
		break;
	case ObjectType_bits:
	case ObjectType_structure:
	case ObjectType_union:
	case ObjectType_array:
	case ObjectType_extern:
		ret = TRUE;
		break;
	case ObjectType_reference:
		ret = _checkPointerRef(p);
		break;
	}
	return ret;
}

static void _setMemberPointer(Dz1Asn1ParserEntry *p, bool_t isPointer)
{
	ObjectInfo *target = p->target;
	switch(target->type)
	{
	case ObjectType_structure:
		p->structEntry.isPointer = isPointer;
		break;
	case ObjectType_union:
		p->unionEntry.isPointer = isPointer;
		break;
	default:
		break;
	}
}

static void _moveMemberSrcName(Dz1Asn1ParserEntry *p)
{
	ObjectInfo *target = p->target;
	switch(target->type)
	{
	case ObjectType_structure:
		p->structEntry.srcType = p->memberSrcName;
		p->memberSrcName = NULL;
		break;
	case ObjectType_union:
		p->unionEntry.srcType = p->memberSrcName;
		p->memberSrcName = NULL;
		break;
	case ObjectType_array:
		{
			ArrayInfo *info = (ArrayInfo *)target->info;
			info->entrySrcType = p->memberSrcName;
			p->memberSrcName = NULL;
		}
		break;
	default:
		break;
	}
}

static Dz1Error correct_member_pointer(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	ObjectInfo *member = *p->objPtr; // member
	bool_t isPointer = FALSE;
	/*
	if (strcmp(member->name, "Dz1Initialisation_Response") == 0)
	{
		p = p;
	}
	*/
	isPointer = _checkPointer(member);
	_setMemberPointer(p, isPointer);

	_moveMemberSrcName(p);

	return err;
}

static Dz1Error set_struct_member_optional(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;

//	p->structEntry.isAsnOptional = TRUE;
	p->structEntry.memb_flags |= MEMBER_FLAG_ASN_OPTIONAL;

	return err;
}

static Dz1Error prepare_union(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	ObjectInfo *target = *p->objPtr;

	if ((target->info = UnionInfo_new(&err)) == NULL) ERR_OUT(&err);
	else p->objPtr = &p->unionEntry.type;

	return err;
}

static Dz1Error add_to_union_members(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	UnionMemberEntry *e = &p->unionEntry;
	ObjectInfo *target = p->target;
	UnionInfo *info = (UnionInfo *)target->info;

	if (info == NULL)
	{
		ERR_SET_OUT(errp, EFAULT);
	}
	else if (e->type != NULL)
	{
		if (e->isForwarded) e->isPointer = TRUE;

//		Dz1Thread_tprintf(tab, "@@@ Add Union Member %s(%s)\n", e->type->name, e->srcType);
		if ((*errp = info->members->add(info->members,
										e->isForwarded, e->type, e->presentStr,
										e->srcType, e->isPointer, e->instance,
										e->memb_flags, e->dumpMode, e->end_of_arr)).code) ERR_OUT(&err);
		else
		{
			UnionMemberEntry_purge(&p->unionEntry);
			Dz1Error_set(errp, 0);
		}
	}

	return err;
}

static Dz1Error set_union_member_instance(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;

	char name[4096]; // modified by gm 20230602 - size 4095 -> 4096
	_chkMemberNameCollision(name, t->v);
//	Dz1Thread_tprintf(tab, "- Union Member Instance = %s\n", name);
	if ((p->unionEntry.instance = Dz1Str_dup(name, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_union_member_present(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;

	if (p->unionEntry.presentStr != NULL) Dz1StrA_del(p->unionEntry.presentStr);
	p->unionEntry.presentStr = t->v;
	t->v = NULL;

// 	u32_t num = atoi(t->v);
// 	p->unionEntry.presentNum = num;

	return err;
}

static Dz1Error set_obj_type_list_prepare(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	ObjectInfo *target = *p->objPtr;
	ArrayInfo *info = NULL;

	target->type = ObjectType_array;

	if ((target->info = info = ArrayInfo_new(ARRAY_API_BASE|ARRAY_API_COUNT, NULL, NULL, FALSE, FALSE, ArrayType_normal, &err)) == NULL) ERR_OUT(&err);
	else p->objPtr = &info->entry;

	return err;
}

static str_t __static_list_instance = "Entry";
static str_t _getInstanceName(Dz1Asn1ParserEntry *p, Dz1Error *err)
{
	str_t ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Error_set(errp, 0);
	switch(p->target->type)
	{
	case ObjectType_structure:
		if ((ret = p->structEntry.instance) == NULL) ERR_SET_OUT(errp, EFAULT);
		break;
	case ObjectType_union:
		if ((ret =  p->unionEntry.instance) == NULL) ERR_SET_OUT(errp, EFAULT);
		break;
	case ObjectType_array:
		ret =  __static_list_instance;
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return ret;
}

static str_t __static_list_asn_instance = "element";
static str_t _getSrcInstanceName(Dz1Asn1ParserEntry *p, Dz1Error *err)
{
	str_t ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Error_set(errp, 0);
	switch(p->target->type)
	{
	case ObjectType_structure:
		if ((ret = p->structEntry.instance) == NULL) ERR_SET_OUT(errp, EFAULT);
		break;
	case ObjectType_union:
		if ((ret =  p->unionEntry.instance) == NULL) ERR_SET_OUT(errp, EFAULT);
		break;
	case ObjectType_array:
		ret =  __static_list_asn_instance;
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return ret;
}

static Dz1Error set_member_type_named(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	str_t instance = _getInstanceName(p, &err);
	if (instance == NULL) ERR_OUT(&err);
	else
	{
		char name[4096];
		ObjectInfo *target = p->target;
		sprintf(name, "%s_%s", target->name, instance);
		if ((*p->objPtr = env->module->findObject(env->module, name)) == NULL)
		{
			ERR_SET_OUT(&err, ENOENT);
		}
	}
	return err;
}

static void _setListMemberIsForward(ObjectInfo *p, FORWARD_TYPE flag)
{
	ArrayInfo *info = (ArrayInfo *)p->info;
	info->isForward = flag;
}

static void _setMemberIsForwarded(Dz1Asn1ParserEntry *p, FORWARD_TYPE flag)
{
	ObjectInfo *target = p->target;
	switch(target->type)
	{
	case ObjectType_structure:
		p->structEntry.isForwarded = flag;
		break;
	case ObjectType_union:
		p->unionEntry.isForwarded = flag;
		break;
	case ObjectType_array:
		_setListMemberIsForward(target, flag);
		break;
	default:
		break;
	}
}

static Dz1Error set_obj_type_symbol(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;
	ObjectInfo *origin = NULL;
	FORWARD_TYPE isFwd = FORWARD_TYPE_NONE;

	char name[4096];
	sprintf(name, "Dz1%s", t->v);

	if ((origin = _getOrigin(env, name, &isFwd, &err)) == NULL) ERR_OUT(&err);
	else
	{
		bool_t isMember = ((*p->objPtr == p->target) ? FALSE : TRUE);
		if (isMember)
		{
			*p->objPtr = origin;
			_setMemberIsForwarded(p, isFwd);

			Dz1Str_delAndSetNull(&p->memberSrcName);
			p->memberSrcName = t->v; t->v = NULL;
		}
		else
		{
			ObjectInfo *target = *p->objPtr;
			target->type = ObjectType_defined;
			if ((target->info = DefinedInfo_new(isFwd, origin, &err)) == NULL) ERR_OUT(&err);
		}
	}

	return err;
}

static Dz1Error new_target_named(Dz1Asn1ParserEnv *env, str_t name, str_t srcName, ObjectType type)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEntry *node = NULL;
	if (strncmp(name, "Dz1", 3) != 0)
	{
		name = name;
	}

//	Dz1Thread_tprintf(tab++, "New Unnamed Type = %s\n", name);
//	Dz1Thread_tprintf(tab++, "New Unnamed Type = %s(%s)\n", name);
	if ((node = Dz1Asn1ParserEntry_new(name, srcName, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Asn1ParserEntry_delAndSetNull, (void *)&node);

		if ((err = _push_entry(env, node)).code) ERR_OUT(&err);
		else
		{
			ObjectInfo *target = *node->objPtr;
			target->type = type;
			if (target->type == ObjectType_enumerate)
				target->api &= ~OBJECT_API_ASN_CONV;
			node = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1Asn1ParserEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error new_target_named_enum(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;

	Dz1Asn1ParserEntry *p = env->current;
	str_t instance = _getInstanceName(p, &err);
	str_t srcInstance = _getSrcInstanceName(p, &err);
	if (instance == NULL || srcInstance == NULL) ERR_OUT(&err);
	else
	{
		char name[4096], srcName[4096];
		ObjectInfo *target = p->target;
		sprintf(name, "%s_%s", target->name, instance);
		sprintf(srcName, "%s_%s", target->srcName, srcInstance);

		if ((err = new_target_named(env, name, srcName, ObjectType_enumerate)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error new_target_named_struct(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;

	Dz1Asn1ParserEntry *p = env->current;//, *node = NULL;
	str_t instance = _getInstanceName(p, &err);
	str_t srcInstance = _getSrcInstanceName(p, &err);
	if (instance == NULL && srcInstance == NULL) ERR_OUT(&err);
	else
	{
		char name[4096], srcName[4096];
		ObjectInfo *target = p->target;
		sprintf(name, "%s_%s", target->name, instance);
		sprintf(srcName, "%s_%s", target->srcName, srcInstance);

		// Check Later
		if ((err = new_target_named(env, name, srcName, ObjectType_structure)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error new_target_named_union(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;

	Dz1Asn1ParserEntry *p = env->current;//, *node = NULL;
	str_t instance = _getInstanceName(p, &err);
	str_t srcInstance = _getSrcInstanceName(p, &err);
	if (instance == NULL && srcInstance == NULL) ERR_OUT(&err);
	else
	{
		char name[4096], srcName[4096];
		ObjectInfo *target = p->target;
		sprintf(name, "%s_%s", target->name, instance);
		sprintf(srcName, "%s_%s", target->srcName, srcInstance);

		// Check later
		if ((err = new_target_named(env, name, srcName, ObjectType_union)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error find_struct_object(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	//Dz1Asn1ParserEntry *p = env->current;

	char name[4096];
	sprintf(name, "Dz1%s", t->v);
	env->refObj = env->module->findObject(env->module, name);
	Dz1Str_delAndSetNull(&env->refName);
	env->refName = t->v; t->v = NULL;

	return err;
}

static Dz1Error set_obj_type_from_ref(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;

	if (env->refObj == NULL)
	{
		Dz1Thread_tprintf(tab, "!!! Can not find Reference Object %s\n", env->refName ? env->refName : "");
		Dz1MdefcModule_dump(env->module, 0);
		ERR_SET_OUT(&err, ENOENT);
	}
	else if (env->refObj->type != ObjectType_structure)
	{
		Dz1Thread_tprintf(tab, "!!! Object %s can't be referenced\n", env->refObj->name);
		ERR_SET_OUT(&err, EFAULT);
	}
	else
	{
		StructureInfo *info = (StructureInfo *)env->refObj->info;
		StructMemberEntry *e = info->members->find(info->members, t->v);
		if (e == NULL)
		{
			Dz1Thread_tprintf(tab, "!!! No such instance %s in %s\n", t->v, env->refObj->name);
			ERR_SET_OUT(&err, ENOENT);
		}
		else
		{
			bool_t isMember = (*p->objPtr == p->target) ? FALSE : TRUE;
			if (isMember)
			{
				*p->objPtr = e->type;
				Dz1Str_delAndSetNull(&p->memberSrcName);
				if ((p->memberSrcName = Dz1Str_dup(e->srcType, &err)) == NULL) ERR_OUT(&err);
			}
			else
			{
				ObjectInfo *target = *p->objPtr;
				target->type = ObjectType_defined;
				if ((target->info = DefinedInfo_new(FALSE, e->type, &err)) == NULL) ERR_OUT(&err);
			}
		}
	}

	Dz1Str_delAndSetNull(&env->refName);
	return err;
}

static Dz1Error set_include(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	//Dz1Asn1ParserEntry *p = env->current;

	env->include = t->v; t->v = NULL;

	return err;
}

static Dz1Error do_asn_include(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	//Dz1Asn1ParserEntry *p = env->current;

	if (env->include == NULL) ERR_SET_OUT(&err, EFAULT);
	else
	{
		if ((err = Dz1MdefcModule_includeASN(env->module, env->spec, env->inc, env->include)).code) ERR_OUT(&err);
		Dz1Str_delAndSetNull(&env->include);
	}
	return err;
}

/*
static Dz1Error (Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1ParserEnv *env = (Dz1Asn1ParserEnv *)ptr;
	Dz1Asn1ParserEntry *p = env->current;

	return err;
}
*/

static Dz1Error Dz1Asn1Parser_emiterInit(void *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = Dz1Parser_addEmiter(p, "new_module", new_module)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "new_target_with_name", new_target_with_name)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "add_target_to_module", add_target_to_module)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_obj_type", set_obj_type)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_obj_type_bin", set_obj_type_bin)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_obj_type_bits", set_obj_type_bits)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_obj_type_oid", set_obj_type_oid)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "prepare_enum", prepare_enum)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "add_to_enums", add_to_enums)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_enum_name", set_enum_name)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_enum_val", set_enum_val)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "prepare_struct", prepare_struct)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "add_to_struct_members", add_to_struct_members)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_struct_member_instance", set_struct_member_instance)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_struct_member_optional", set_struct_member_optional)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "prepare_union", prepare_union)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "add_to_union_members", add_to_union_members)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_union_member_instance", set_union_member_instance)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_union_member_present", set_union_member_present)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_obj_type_list_prepare", set_obj_type_list_prepare)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_member_type_named", set_member_type_named)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_obj_type_symbol", set_obj_type_symbol)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "new_target_named_enum", new_target_named_enum)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "new_target_named_struct", new_target_named_struct)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "new_target_named_union", new_target_named_union)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "correct_member_pointer", correct_member_pointer)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "change_object_type", change_object_type)).code) ERR_OUT(&err);
//	else if ((err = Dz1Parser_addEmiter(p, "set_integer_restrict_range", set_integer_restrict_range)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_integer_restrict_prepare", set_integer_restrict_prepare)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_integer_value", set_integer_value)).code) ERR_OUT(&err);
//	else if ((err = Dz1Parser_addEmiter(p, "set_integer_max", set_integer_max)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "find_struct_object", find_struct_object)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_obj_type_from_ref", set_obj_type_from_ref)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "set_include", set_include)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "do_asn_include", do_asn_include)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "show_token", show_token)).code) ERR_OUT(&err);
	else if ((err = Dz1Parser_addEmiter(p, "new_line", new_line)).code) ERR_OUT(&err);
//	else if ((err = Dz1Parser_addEmiter(p, "", )).code) ERR_OUT(&err);
	return err;
}

static void *Dz1Asn1Parser_new(Dz1Error *err)
{
	void *p = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((p = Dz1Parser_new(errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&p);

		if ((*errp = Dz1Asn1Parser_emiterInit(p)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1ParserInit_parse(p, syntax)).code) { ERR_OUT(errp); }
//		else Dz1Parser_dump(p, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Parser_delAndSetNull, (void *)&p);
	}
	return p;
}

static Dz1Error _chkUndefined(void *ptr, void *entry)
{
	ObjectInfo *p = (ObjectInfo *)entry;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Thread_printf("Undefined Type %s\n", p->name);
	ERR_SET_OUT(&err, ENOENT);

	return err;
}

/*
#define FORWARD_TYPE_NONE		0
#define FORWARD_TYPE_STRUCT		1
#define FORWARD_TYPE_UNION		2
*/

static Dz1Error _correctFwdInfo(ObjectInfo **p, u32_t *fwd)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ObjectInfo *origin = ObjectInfo_getOrigin(*p);
	switch(origin->type)
	{
	case ObjectType_defined:	// don't care
		break;
	case ObjectType_func:		// can't
	case ObjectType_reference:	// can't
		Dz1Thread_printf("!!! %s type can't forward declare to %s\n", (*p)->name, origin->name);
		ERR_SET_OUT(&err, EFAULT);
		break;
	case ObjectType_extern:		// change
	case ObjectType_primitive:	// change it's type to primitive
		(*fwd) = 0;
		(*p) = origin;
		break;
	case ObjectType_enumerate:	// fix forward flag enum
		(*fwd) = FORWARD_TYPE_ENUM;
		break;
	default:
		err = err;
	case ObjectType_bits:		// fix forward flag struct
	case ObjectType_structure:	// fix forward flag struct
	case ObjectType_array:		// fix forward flag struct
		(*fwd) = FORWARD_TYPE_STRUCT;
		break;
	case ObjectType_union:		// fix forward flag union
		(*fwd) = FORWARD_TYPE_UNION;
		break;
	}
	return err;
}

static Dz1Error _chkFwdDrfined(ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DefinedInfo *info = (DefinedInfo *)p->info;
	if (info->isForwarded)
	{	// 사전에 정의할 수 있는 타입인가?
		if ((err = _correctFwdInfo(&info->origin, (u32_t *)&info->isForwarded)).code) ERR_OUT(&err);
	}
	return err;
}

static bool_t _chkPointerInDefined(ObjectInfo *memberType)
{
	bool_t ret = FALSE;
	ObjectInfo *obj = memberType;
	obj = ObjectInfo_getOrigin(obj);
	switch(obj->type)
	{
	default:
	case ObjectType_func:
	case ObjectType_declare:
	case ObjectType_primitive:
	case ObjectType_enumerate:
		break;
	case ObjectType_bits:
	case ObjectType_structure:
	case ObjectType_union:
	case ObjectType_array:
		ret = TRUE;
		break;
	case ObjectType_extern:
		{
			ExternInfo *ei = (ExternInfo *)obj->info;
			if (ei->isStatic == FALSE)
				ret = TRUE;
		}
		break;
	case ObjectType_reference:
		break;
	}
	return ret;
}

static Dz1Error _chkFwdStructureMember(StructMemberEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (p->isForwarded)
	{
		if ((err = _correctFwdInfo(&p->type, (u32_t *)&p->isForwarded)).code) ERR_OUT(&err);
	}
	else if (p->type->type == ObjectType_defined && p->isPointer == FALSE)
	{
		p->isPointer = _chkPointerInDefined(p->type);
	}

	if (ObjectInfo_getOrigin(p->type)->type == ObjectType_array) 
//		p->argInvolve = FALSE;
		p->memb_flags &= ~MEMBER_FLAG_ARG_INVOLVE;

	return err;
}

static Dz1Error _chkFwdStructure(ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	StructureInfo *info = (StructureInfo *)p->info;
	StructMemberEntry *e = NULL;
	void *c = NULL;
	
	if ((c = Dz1FifoCursor_new(info->members->fifo, NULL)) != NULL)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if ((err = _chkFwdStructureMember(e)).code)
				{
					ERR_OUT(&err);
					break;
				}
				else if (e->type->type == ObjectType_primitive || e->type->type == ObjectType_enumerate)
				{
//					if (e->isAsnOptional) 
					if (StructMemberEntry_isAsnOptional(e)) 
						e->isPointer = TRUE;
					else e->isPointer = FALSE;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return err;
}

static Dz1Error _chkFwdUnionMember(UnionMemberEntry *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (e->isForwarded)
	{
		if ((err = _correctFwdInfo(&e->type, (u32_t *)&e->isForwarded)).code) ERR_OUT(&err);
	}
	else if (e->type->type == ObjectType_defined && e->isPointer == FALSE)
	{
		e->isPointer = _chkPointerInDefined(e->type);
	}
	return err;
}

static Dz1Error _chkFwdUnion(ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	UnionInfo *info = (UnionInfo *)p->info;
	void *c = Dz1FifoCursor_new(info->members->fifo, NULL);
	if (c)
	{
		UnionMemberEntry *e = NULL;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if ((err = _chkFwdUnionMember(e)).code)
				{
					ERR_OUT(&err);
					break;
				}
				else if (e->type->type == ObjectType_primitive || e->type->type == ObjectType_enumerate)
					e->isPointer = FALSE;
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return err;
}

static Dz1Error _chkFwdArray(ObjectInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ArrayInfo *info = (ArrayInfo *)p->info;
	if (info->isForward)
	{
		if ((err = _correctFwdInfo(&info->entry, (u32_t *)&info->isForward)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error _chkForward(void *ptr, void *entry)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ObjectInfo *p = (ObjectInfo *)entry;

	if (strcmp(p->name, "Dz1T_APDUs") == 0)
	{
		p = p;
	}

	switch(p->type)
	{
	default:
	case ObjectType_func:
	case ObjectType_primitive:
	case ObjectType_reference:
	case ObjectType_extern:
	case ObjectType_bits:
	case ObjectType_enumerate:
		// no need to check
		break;
	case ObjectType_defined:
		if ((err = _chkFwdDrfined(p)).code) ERR_OUT(&err);
		break;
	case ObjectType_structure:
		if ((err = _chkFwdStructure(p)).code) ERR_OUT(&err);
		break;
	case ObjectType_union:
		if ((err = _chkFwdUnion(p)).code) ERR_OUT(&err);
		break;
	case ObjectType_array:
		if ((err = _chkFwdArray(p)).code) ERR_OUT(&err);
		break;
	}
	return err;
}

static Dz1MdefcModule *Dz1MdefcModule_proc(void *parser, PublishSpec *spec, IncludeSpec *inc, str_t filename, str_t text, Dz1Error *err)
{
	Dz1MdefcModule *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1ParserEnv env =
	{
		NULL,		// filename
		NULL,		// spec
		NULL,		// inc

		NULL,		// include

		NULL,		// forwardTree
		NULL,		// module

		NULL,		// current
		NULL,		// refObj
		NULL,		// refName
	};

	env.filename = filename;
	env.spec = spec;
	env.inc = inc;
	if ((env.forwardTree = Dz1Asn1ForwardTree_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Asn1ParserEnv_clean, (void *)&env);

		if ((*errp = Dz1Parser_prepare(parser, text)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Parser_process(parser, "main", &env, 0)).code)
		{
			Dz1Thread_printf("Expression Compile Fail (line %d)\n", Dz1Parser_getLineNum(parser) + 1);
			ERR_OUT(errp);
		}
		else
		{
			Dz1Thread_printf("--- Parse Done\n");
			if ((*errp = Dz1AATree_travel(env.forwardTree, _chkUndefined, NULL)).code) ERR_OUT(errp);
			else if ((*errp = Dz1AATree_travel(env.module->objTree, _chkForward, NULL)).code) ERR_OUT(errp);
			else { ret = env.module; env.module= NULL; }
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Asn1ParserEnv_clean, (void *)&env);
	}
	return ret;
}

Dz1MdefcModule *Dz1MdefcModule_compileASN(PublishSpec *spec, IncludeSpec *inc, str_t filename, str_t text, Dz1Error *err)
{
	void *p = NULL;
	Dz1MdefcModule *module = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((p = Dz1Asn1Parser_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Parser_del, p);

		if ((module = Dz1MdefcModule_proc(p, spec, inc, filename, text, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1Parser_del, p);
	}
	return module;
}

Dz1Error Dz1MdefcModule_includeASN(Dz1MdefcModule *p, PublishSpec *spec, IncludeSpec *inc, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p->findModule(p, name) == NULL)
	{
		str_t text;
		char fn[1024];
		sprintf(fn, "%s.asn", name);

		if ((text = inc->load(inc, fn, &err)) == NULL)
		{
			Dz1Thread_printf("!!! ASN Include : No such file %s\n", fn);
			Dz1Thread_printf("!!! please correct name between \"real file name\" and \"IMPORTS FROM clause name\"\n", fn);
			ERR_OUT(&err);
		}
		else
		{
			Dz1MdefcModule *module = NULL;
			pthread_cleanup_push((Dz1DelFunc)Dz1Str_del, (void *)text);

			if ((module = Dz1MdefcModule_compileASN(spec, inc, name, text, &err)) == NULL)
			{
				Dz1Thread_printf("!!! ASN Include : Compile Failed : %s\n", fn);
				ERR_OUT(&err);
			}
			else
			{
				pthread_cleanup_push((Dz1DelFunc)Dz1MdefcModule_del, (void *)module);

				if ((err = p->addModule(p, module)).code) ERR_OUT(&err);

				pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1MdefcModule_del, (void *)module);
			}
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Str_del, (void *)text);
		}
	}
	return err;
}

