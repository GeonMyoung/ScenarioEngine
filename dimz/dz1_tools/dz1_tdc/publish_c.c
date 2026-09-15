#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_aatree.h>
#include <dz1_fifo.h>
#include <dz1_str.h>

//#include "module_info_list.h"
//#include "object_info_list.h"
#include "publish_c.h"
#include "publish_enum_c.h"
#include "publish_structure_c.h"
#include "publish_union_c.h"
#include "publish_list_array_c.h"
#include "publish_list_index_c.h"
#include "publish_asnconv.h"
#include "misc.h"

static int ObjectInfo_vars(FILE *fp, ObjectInfo *p, str_t instance, int comma);
static int ObjectInfo_args(FILE *fp, ObjectInfo *p, str_t type, str_t instance, int comma);

static void ObjectInfo_header(FILE *fp, PublishSpec *spec, ObjectInfo *p, int tab);
static void ObjectInfo_source(FILE *fp, PublishSpec *spec, ObjectInfo *p, int tab);


///////////////////////////////////////////////////////////////////////////////
// Primitive Type Helper
static int PrimitiveInfo_vars(FILE *fp, PrimitiveInfo *info, str_t instance, int comma)
{
	fprintf(fp, "%s%s", comma ? ", " : "", instance);
	return 1;
}

static int PrimitiveInfo_args(FILE *fp, PrimitiveInfo *info, str_t type, str_t instance, int comma)
{
	fprintf(fp, "%s%s %s%s", comma ? ", " : "", info->native, info->storage == NativeStorage_address ? "*" : "", instance);
	return 1;
}
// Primitive Type Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Defined Type Helper
int DefinedInfo_vars(FILE *fp, DefinedInfo *p, str_t instance, int comma)
{
	return ObjectInfo_vars(fp, p->origin, instance, comma);
}

int DefinedInfo_args(FILE *fp, DefinedInfo *p, str_t type, str_t instance, int comma)
{
	return ObjectInfo_args(fp, p->origin, type, instance, comma);
}
// Defined Type Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MACRO Type Helper
static void Macro_print(FILE *fp, PublishSpec *spec, u32_t t_api, str_t name, bool_t is_header, int tab)
{	// {macro_name}$HHHH
	char buf[64], *cp = NULL;
	strcpy(buf, name);
	if ((cp = strchr(buf, '$')) != NULL) *cp = 0;

	switch(t_api & 0xFFFF)
	{
	case 0x0001: TP(fp, tab); fprintf(fp, "#ifdef %s\n\n", buf); break;		// ifdef
	case 0x0003: TP(fp, tab); fprintf(fp, "#ifndef %s\n\n", buf); break;	// ifndef
	case 0x0000: TP(fp, tab); fprintf(fp, "#else // %s\n\n", buf); break;	// else
	case 0x0002: TP(fp, tab); fprintf(fp, "#endif // %s\n\n", buf); break;	// endif
	case 0x0004: if (is_header) { TP(fp, tab); fprintf(fp, "#define %s\n\n", buf); } break;	// define
	}
}
// MACRO Type Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Misc Helper
static int ObjectInfo_args(FILE *fp, ObjectInfo *p, str_t type, str_t instance, int comma)
{
	switch(p->type)
	{
		case ObjectType_primitive:
			return PrimitiveInfo_args(fp, (PrimitiveInfo *)p->info, type, instance, comma);
		case ObjectType_defined:
			return DefinedInfo_args(fp, (DefinedInfo *)p->info, type, instance, comma);
		case ObjectType_enumerate:
			fprintf(fp, "%s%s %s", comma ? ", " : "", type, instance);
			return 1;
#if 0
		case ObjectType_bits:
			BitsInfo_header(fp, p->name, (BitsInfo *)p->info, tab);
			break;
		case ObjectType_structure:
			return StructureInfo_args(fp, (StructureInfo *)p->info, comma);
		case ObjectType_union:
			fprintf(fp, "%s%sPresent present, void *ptr", comma ? ", " : "", p->name);
			return 1;
		case ObjectType_list:
			break;
#endif
		default:
			break;
	}
	return 0;
}

static int ObjectInfo_vars(FILE *fp, ObjectInfo *p, str_t instance, int comma)
{
	switch(p->type)
	{
		case ObjectType_primitive:
			return PrimitiveInfo_vars(fp, (PrimitiveInfo *)p->info, instance, comma);
		case ObjectType_enumerate:
			fprintf(fp, "%s%s", comma ? ", " : "", instance);
			return 1;
		case ObjectType_defined:
			return DefinedInfo_vars(fp, (DefinedInfo *)p->info, instance, comma);
#if 0
		case ObjectType_bits:
			BitsInfo_header(fp, p->name, (BitsInfo *)p->info, tab);
			break;
		case ObjectType_structure:
			return StructureInfo_vars(fp, (StructureInfo *)p->info, comma);
		case ObjectType_union:
			fprintf(fp, "%spresent, ptr", comma ? ", " : "");
			return 1;
		case ObjectType_list:
			break;
#endif
		default:
			break;
	}
	return 0;
}

static bool_t ObjectInfo_comment(FILE *fp, ObjectInfo *p, PublishSpec *spec, bool_t is_front)
{
	u32_t t_api = ObjectInfo_apiOf(p, spec);
	if (is_front)
	{
		if (t_api & OBJECT_API_WINDOWS_ONLY) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
		fprintf(fp, "////////////////////////////////////////////////////////////////////////////////\n");
		fprintf(fp, "// %s\n", ObjectInfo_nameOf(p));
	}
	else
	{
		fprintf(fp, "// %s\n", ObjectInfo_nameOf(p));
		fprintf(fp, "////////////////////////////////////////////////////////////////////////////////\n");
		if (t_api & OBJECT_API_WINDOWS_ONLY) fprintf(fp, "#endif // UNIX_SYSTEM\n");
		fprintf(fp, "\n");
	}
	return TRUE;
}
// Misc Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Defined Type header
static void DefinedInfo_headerApi(FILE *fp, PublishSpec *spec, u32_t t_api, str_t name, str_t srcName, DefinedInfo *p, int tab)
{
	bool_t printed = FALSE, p_dump = FALSE, p_fdump = FALSE;
	char fmt[128] = { 0, }, fmtA[128], fmtW[128];
	str_t prefix = ObjectInfo_prefixOf(p->origin, spec);

	// fmt = "#define %s%-0s %s%s\n"
	sprintf(fmt, "#define %%s%%-%ds %%s%%s\n", spec->postFix->lenMax + 4);
	sprintf(fmtA, "#define %%sA%%-%ds %%sA%%s\n", spec->postFix->lenMax + 3);
	sprintf(fmtW, "#define %%sW%%-%ds %%sW%%s\n", spec->postFix->lenMax + 3);

	if (t_api & OBJECT_API_NEW)
	{
		TP(fp, tab); fprintf(fp, fmt, name, spec->postFix->_new, prefix, spec->postFix->_new);
		printed = TRUE;
	}

	if (t_api & OBJECT_API_CLONE && ObjectInfo_isClonable(p->origin, spec))
	{
		TP(fp, tab); fprintf(fp, fmt, name, spec->postFix->_clone, prefix, spec->postFix->_clone);
		printed = TRUE;
	}

	if (t_api & OBJECT_API_DEL)
	{
		TP(fp, tab); fprintf(fp, fmt, name, spec->postFix->_del, prefix, spec->postFix->_del);
		printed = TRUE;
	}

	if (t_api & OBJECT_API_DELANDSETNULL)
	{
		TP(fp, tab); fprintf(fp, fmt, name, spec->postFix->_delAndSetNull, prefix, spec->postFix->_delAndSetNull);
		printed = TRUE;
	}

	/*
	if (t_api & (OBJECT_API_DUMP | OBJECT_API_USER_DUMP))
	{
		TP(fp, tab);
		fprintf(fp, fmt, name, spec->postFix->_dump, prefix, spec->postFix->_dump);
		printed = TRUE;
	}

	if (t_api & (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP))
	{
		TP(fp, tab);
		fprintf(fp, fmt, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump);
		printed = TRUE;
	}
	*/
	if (t_api & (OBJECT_API_DUMP | OBJECT_API_USER_DUMP)) p_dump = TRUE;
	if (t_api & (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP)) p_fdump = TRUE;

	if (p_dump || p_fdump)
	{
		char fmtAM[128], fmtWM[128];
		u8_t type = (t_api & (OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE));
		sprintf(fmtAM, "#define %%s%%-%ds %%sA%%s\n", spec->postFix->lenMax + 4);
		sprintf(fmtWM, "#define %%s%%-%ds %%sW%%s\n", spec->postFix->lenMax + 4);
		switch(type)
		{
		case 0:
			if (p_dump)	 { TP(fp, tab); fprintf(fp, fmt, name, spec->postFix->_dump, prefix, spec->postFix->_dump); }
			if (p_fdump) { TP(fp, tab); fprintf(fp, fmt, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump); }
			break;
		case 1:
			if (p_dump)	 { TP(fp, tab); fprintf(fp, fmtA, name, spec->postFix->_dump, prefix, spec->postFix->_dump); }
			if (p_fdump) { TP(fp, tab); fprintf(fp, fmtA, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump); }
			break;
		case 2:
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (p_dump)	 { TP(fp, tab); fprintf(fp, fmtW, name, spec->postFix->_dump, prefix, spec->postFix->_dump); }
			if (p_fdump) { TP(fp, tab); fprintf(fp, fmtW, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump); }
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		case 3:
			if (p_dump)	 { TP(fp, tab); fprintf(fp, fmtA, name, spec->postFix->_dump, prefix, spec->postFix->_dump); }
			if (p_fdump) { TP(fp, tab); fprintf(fp, fmtA, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump); }
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (p_dump)	 { TP(fp, tab); fprintf(fp, fmtW, name, spec->postFix->_dump, prefix, spec->postFix->_dump); }
			if (p_fdump) { TP(fp, tab); fprintf(fp, fmtW, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump); }
			fprintf(fp, "#ifdef UNICODE\n");
			if (p_dump)	 { TP(fp, tab); fprintf(fp, fmtWM, name, spec->postFix->_dump, prefix, spec->postFix->_dump); }
			if (p_fdump) { TP(fp, tab); fprintf(fp, fmtWM, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump); }
			fprintf(fp, "#else //  UNICODE\n");
			if (p_dump)	 { TP(fp, tab); fprintf(fp, fmtAM, name, spec->postFix->_dump, prefix, spec->postFix->_dump); }
			if (p_fdump) { TP(fp, tab); fprintf(fp, fmtAM, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump); }
			fprintf(fp, "#endif //  UNICODE\n");
			if (p_dump)  { TP(fp, tab); fprintf(fp, "static __inline__ void %sX%s(%s *p, int tab) { DZ1_DUMP(%s, p, tab); }\n", name, spec->postFix->_dump, name, name); }
			if (p_fdump) { TP(fp, tab); fprintf(fp, "static __inline__ void %sX%s(FILE *fp, %s *p, int tab) { DZ1_FDUMP(fp, %s, p, tab); }\n", name, spec->postFix->_fdump, name, name); }

			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0)
			{ 
				fprintf(fp, "#else // UNIX_SYSTEM\n");
				if (p_dump)	 { TP(fp, tab); fprintf(fp, fmtAM, name, spec->postFix->_dump, prefix, spec->postFix->_dump); }
				if (p_dump)  { TP(fp, tab); fprintf(fp, "#define %sX%s %sA%s\n", name, spec->postFix->_dump, name, spec->postFix->_dump); }
				if (p_fdump) { TP(fp, tab); fprintf(fp, fmtAM, name, spec->postFix->_fdump, prefix, spec->postFix->_fdump); }
				if (p_fdump) { TP(fp, tab); fprintf(fp, "#define %sX%s %sA%s\n", name, spec->postFix->_fdump, name, spec->postFix->_fdump); }
				fprintf(fp, "#endif // UNIX_SYSTEM\n");
			}
			break;
		}
		printed = TRUE;
	}

	if (t_api & OBJECT_API_CMP && ObjectInfo_isComparable(p->origin, spec))
	{
		TP(fp, tab);
		fprintf(fp, fmt, name, spec->postFix->_cmp, prefix, spec->postFix->_cmp);
		printed = TRUE;
	}
#ifdef USE_CODEC
	if (t_api & OBJECT_API_CODEC)
	{
		TP(fp, tab); fprintf(fp, fmt, name, spec->postFix->_enc, prefix, spec->postFix->_enc);
		TP(fp, tab); fprintf(fp, fmt, name, spec->postFix->_dec, prefix, spec->postFix->_dec);
		printed = TRUE;
	}
#endif
	if (t_api & OBJECT_API_ASN_CONV)
	{
		TP(fp, tab); fprintf(fp, fmt, name, "_fromASN", prefix, "_fromASN");
		TP(fp, tab); fprintf(fp, fmt, name, "_newFromASN", prefix, "_newFromASN");
		TP(fp, tab); fprintf(fp, fmt, name, "_toASN", prefix, "_toASN");
		TP(fp, tab); fprintf(fp, fmt, name, "_toNewASN", prefix, "_toNewASN");
	}

	if (printed) fprintf(fp, "\n");
}

static bool_t DefinedInfo_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, DefinedInfo *p, PublishSpec *s, int tab)
{
	ObjectInfo *origin = ObjectInfo_getOrigin(p->origin);
	if (p->isForwarded) Dz1ThreadA_ftprintf(fp, tab, "%s%s;\n", forwardCaster(p->isForwarded), ObjectInfo_nameOf(origin));
	//									   1 2  3      1                                2                             3
	Dz1ThreadA_ftprintf(fp, tab, "typedef %s%s %s;\n", p->isForwarded ? "struct " : "", ObjectInfo_nameOf(p->origin), tn);
	fprintf(fp, "\n");

	if (origin->type == ObjectType_primitive && strcmp(ObjectInfo_nameOf(origin), "void") == 0) { }
	else DefinedInfo_headerApi(fp, s, t_api, tn, tn_alt, p, tab);
	return TRUE;
}
// Defined Type header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Defined Type header : ASN Converter
static void DefinedInfo_headerApiAsnConv(FILE *fp, PublishSpec *spec, u32_t t_api, str_t name, str_t srcName, DefinedInfo *p, int tab)
{
	bool_t printed = FALSE;
	char fmt[1024] = { 0, };
	str_t prefix = ObjectInfo_prefixOf(p->origin, spec);

	if (t_api & OBJECT_API_ASN_CONV)
	{
		TP(fp, tab); fprintf(fp, fmt, name, "_fromASN", prefix, "_fromASN");
		TP(fp, tab); fprintf(fp, fmt, name, "_newFromASN", prefix, "_newFromASN");
		TP(fp, tab); fprintf(fp, fmt, name, "_toASN", prefix, "_toASN");
		TP(fp, tab); fprintf(fp, fmt, name, "_toNewASN", prefix, "_toNewASN");
	}

	if (printed) fprintf(fp, "\n");
}

static bool_t DefinedInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, DefinedInfo *p, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	ObjectInfo *origin = ObjectInfo_getOrigin(p->origin);
	if (origin->type == ObjectType_primitive && strcmp(ObjectInfo_nameOf(origin), VOIDTYPE_NAME) == 0) { }
	else
	{
		DefinedInfo_headerApiAsnConv(fp, s, t_api, tn, tn_alt, p, tab);
		ret = TRUE;
	}
	return ret;
}
// Defined Type header : ASN Converter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Declared Type
static bool_t DeclaredType_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, void *info, PublishSpec *spec, int tab)
{
	str_t decl_type = (str_t)info, decl = "struct";
	if (strcmp(decl_type, "enum") == 0) decl = "enum";
	Dz1ThreadA_ftprintf(fp, tab, "%s %s;\n", decl, tn_alt);
	return TRUE;
}
// Declared Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Reference Type
static bool_t ReferenceType_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, void *info, PublishSpec *spec, int tab)
{
	Dz1ThreadA_ftprintf(fp, tab, "struct %s;\n", tn);
	return TRUE;
}
// Reference Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function Type Header
static void FunctionInfoArg_header(FILE *fp, PublishSpec *spec, FunctionArg *p, bool_t isFirst, bool_t nl, int tab)
{
	if (!isFirst) fprintf(fp, ", ");
	if (nl) { fprintf(fp, "\n"); TP(fp, tab); }
	fprintf(fp, "%s%s", p->argForward == FUNCTION_RET_FORWARD_NONE ? "" :
			(p->argForward == FUNCTION_RET_FORWARD_STRUCT ? "struct " : "union "),
			ObjectInfo_nameOf(p->argType));
	if (p->argPtrCnt)
	{
		int cnt = p->argPtrCnt;
		fprintf(fp, " ");
		while(cnt--) fprintf(fp, "*");
	}
	if (p->instance) fprintf(fp, "%s%s", p->argPtrCnt ? "" : " ", p->instance);
//	if (nl) fprintf(fp, "\n");
}

static bool_t FunctionInfo_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, FunctionInfo *p, PublishSpec *s, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t ret = FALSE;
	FunctionArgs *args = p->args;
	void *cursor = Dz1FifoCursor_new(args->list, errp);
	if (cursor == NULL) ERR_OUT(errp);
	else
	{
		bool_t isFirst = TRUE, nl = FALSE;
		FunctionArg *arg = NULL;
		pthread_cleanup_push(Dz1FifoCursor_del, (void *)cursor);

		if (args->count(args) > 3) nl = TRUE;
		//                                1 2   3
		Dz1ThreadA_ftprintf(fp, tab,	"typedef %s ", ObjectInfo_nameOf(p->retType));
		if (p->retIsPointer > 0)
		{
			int i;
			for (i = 0; i < p->retIsPointer; i++) 
				fprintf(fp, "*");
		}
		fprintf(fp, "(*%s)(", tn);

		for (Dz1FifoCursorForward(cursor))
		{
			if ((arg = (FunctionArg *)Dz1FifoCursor_data(cursor)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else FunctionInfoArg_header(fp, s, arg, isFirst, nl, tab + 5);
			isFirst = FALSE;
		}
		if (nl) TP(fp, tab); 
		fprintf(fp, ");\n"); // modified by gm 20230602 

		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, (void *)cursor);
		ret = TRUE;
	}
	return ret;
}
// Function Type Header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constant Type
static bool_t ConstantType_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, void *info, PublishSpec *spec, int tab)
{
	Dz1ThreadA_ftprintf(fp, tab, "#define %s\t\t\t%s\n", tn, ((ConstantInfo *)info)->value);
	return TRUE;
}
// Constant Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MacroType Type
static bool_t MacroType_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, void *info, PublishSpec *spec, int tab)
{
	Macro_print(fp, spec, t_api, tn, TRUE, tab);
	return TRUE;
}

static bool_t MacroType_source(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, void *info, PublishSpec *spec, int tab)
{
	Macro_print(fp, spec, t_api, tn, FALSE, tab);
	return TRUE;
}
// MacroType Type
///////////////////////////////////////////////////////////////////////////////

static ObjectType prev_obj = ObjectType_max;

typedef struct ObjectInfoPubluishAPI
{
	ObjectType	 type;
	bool_t		 (*header)(	   FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, void *info, PublishSpec *spec, int tab);
	bool_t		 (*header_asn)(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, void *info, PublishSpec *spec, int tab);
	bool_t		 (*source)(	   FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, void *info, PublishSpec *spec, int tab);
} ObjectInfoPubluishAPI;

#define ObjectInfoPubluishAPI_NULL	{ ObjectType_max, NULL, NULL, NULL }

static ObjectInfoPubluishAPI *ObjectInfoPubluishAPI_find(ObjectInfoPubluishAPI *tbl, ObjectType t)
{
	ObjectInfoPubluishAPI *i;
	for (i = tbl; i != NULL && i->type != ObjectType_max; i++)
		if (i->type == t) return i;
	return NULL;
}

static ObjectInfoPubluishAPI objectInfoPubluishAPI[] =
{
	{ ObjectType_primitive,	NULL,					NULL,							NULL },
	{ ObjectType_enumerate,	EnumInfo_header,		EnumInfo_headerAsnConv,			EnumInfo_source },	// typedef enum ?...

	{ ObjectType_defined,	DefinedInfo_header,		DefinedInfo_headerAsnConv,		NULL },				// typedef {[union|struct]} {tgt_type} {src_type}...

//	{ ObjectType_bits,		NULL,					NULL,							NULL },

	{ ObjectType_structure,	StructureInfo_header,	StructureInfo_headerAsnConv,	StructureInfo_source },	// typedef struct ? ...;
	{ ObjectType_union,		UnionInfo_header,		UnionInfo_headerAsnConv,		UnionInfo_source },		// typedef union ? ...;
	{ ObjectType_array,		ArrayInfo_header,		ArrayInfo_headerAsnConv,		ArrayInfo_source },		// typedef {table|array} ? ...;

	{ ObjectType_declare,	DeclaredType_header,	NULL,							NULL },					// {struct|union} ?;

	{ ObjectType_extern,	NULL,					NULL,							NULL },					// typedef entern ? ...;	header include
	{ ObjectType_reference,	ReferenceType_header,	NULL,							NULL },					// typedef reference ? ...;	source include

	{ ObjectType_func,		FunctionInfo_header,	NULL,							NULL },					// typedef func {ret_type} ? ...;
	{ ObjectType_index,		IndexInfo_header,		NULL,							IndexInfo_source, },	// typedef indec ? ...;

	//////////////////////////////////////////////////////
	// Non-Variable
	{ ObjectType_constant,	ConstantType_header,	NULL,							NULL },					// typedef constant ? ...;
	{ ObjectType_macro,		MacroType_header,		NULL,							MacroType_source },		// # {define|ifdef|ifndef|else|endif} ?;	ObjectInfoPubluishAPI_NULL;
	// Non-Variable
	//////////////////////////////////////////////////////
	ObjectInfoPubluishAPI_NULL
};

///////////////////////////////////////////////////////////////////////////////
// OBJECT Header
static void ObjectInfo_header(FILE *fp, PublishSpec *spec, ObjectInfo *p, int tab)
{
//	ObjectInfo *o = ObjectInfo_getOrigin(p);
	ObjectInfoPubluishAPI *pub_api = ObjectInfoPubluishAPI_find(objectInfoPubluishAPI, p->type);

	prev_obj = p->type;

	if (pub_api == NULL) Dz1ThreadA_ftprintf(fp, tab, "#error %s has no publish API\n", ObjectInfo_nameOf(p));
	else if (pub_api->header == NULL) { }
	else
	{
		bool_t commented = ObjectInfo_comment(fp, p, spec, TRUE);
		pub_api->header(fp, p->name, p->srcName, ObjectInfo_apiOf(p, spec), p->info, spec, tab);
		if (commented) ObjectInfo_comment(fp, p, spec, FALSE);
	}
#if 0
	u32_t t_api = ObjectInfo_apiOf(p, spec);
	switch(p->type)
	{
		case ObjectType_enumerate:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			EnumInfo_header(fp, p->name, p->srcName, t_api, (EnumInfo *)p->info, spec, tab);
			break;
		case ObjectType_defined:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			DefinedInfo_header(fp, p->name, p->srcName, t_api, (DefinedInfo *)p->info, spec, tab);
			break;
// 		case ObjectType_bits:
// 			BitsInfo_header(fp, spec, ObjectInfo_apiOf(p), p->name, (BitsInfo *)p->info, tab);
// 			break;
		case ObjectType_structure:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			StructureInfo_header(fp, p->name, p->srcName, t_api, (StructureInfo *)p->info, spec, tab);
			break;
		case ObjectType_union:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			UnionInfo_header(fp, p->name, p->srcName, t_api, (UnionInfo *)p->info, spec, tab);
			break;
		case ObjectType_array:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			ArrayInfo_header(fp, p->name, p->srcName, t_api, (ArrayInfo *)p->info, spec, tab);
			break;
		case ObjectType_declare:	// struct|union ?
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			DeclaredType_header(fp, p->name, p->srcName, t_api, p->info, spec, tab);
// 			TP(fp, tab); fprintf(fp, "struct %s;\n", (str_t)p->info);
			break;
		case ObjectType_extern: break;	// typedef native ?...
		case ObjectType_reference:	// typedef reference ?...
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			TP(fp, tab); fprintf(fp, "struct %s;\n", p->name);
			break;
		case ObjectType_func:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			FunctionInfo_header(fp, p->name, p->srcName, OBJECT_API_NONE, (FunctionInfo *)p->info, spec, tab);
			break;
		case ObjectType_index:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			IndexInfo_header(fp, p->name, p->srcName, t_api, (IndexInfo *)p->info, spec, tab);
			break;
		case ObjectType_constant:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			TP(fp, tab); fprintf(fp, "#define %s\t\t\t%s\n", p->name, ((ConstantInfo *)p->info)->value);
			break;
		case ObjectType_macro:
			Macro_print(fp, spec, p->api, p->name, TRUE, tab);
			break;
		default:
			break;
	}
	if (commented) ObjectInfo_comment(fp, p, spec, FALSE);
#endif
}
// OBJECT Header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// OBJECT header : ASN Converter
static void ObjectInfo_headerAsnConv(FILE *fp, PublishSpec *spec, ObjectInfo *p, int tab)
{
	ObjectInfo *o = ObjectInfo_getOrigin(p);
	ObjectInfoPubluishAPI *pub_api = ObjectInfoPubluishAPI_find(objectInfoPubluishAPI, o->type);

	if (pub_api == NULL) Dz1ThreadA_ftprintf(fp, tab, "#error %s has no publish API\n", ObjectInfo_nameOf(p));
	else if (pub_api->header_asn == NULL) { }
	else pub_api->header_asn(fp, p->name, p->srcName, ObjectInfo_apiOf(p, spec), p->info, spec, tab);

#if 0
	u32_t t_api = ObjectInfo_apiOf(p, spec);
	switch(p->type)
	{
		case ObjectType_enumerate:
			EnumInfo_headerAsnConv(fp, p->name, p->srcName, t_api, (EnumInfo *)p->info, spec, tab);
			break;
		case ObjectType_defined:
			DefinedInfo_headerAsnConv(fp, p->name, p->srcName, t_api, (DefinedInfo *)p->info, spec, tab);
			break;
// 		case ObjectType_bits:
// 			BitsInfo_headerAsnConv(fp, spec, ObjectInfo_apiOf(p), p->name, (BitsInfo *)p->info, tab);
// 			break;
		case ObjectType_structure:
			StructureInfo_headerAsnConv(fp, p->name, p->srcName, t_api, (StructureInfo *)p->info, spec, tab);
			break;
		case ObjectType_union:
			UnionInfo_headerAsnConv(fp, p->name, p->srcName, t_api, (UnionInfo *)p->info, spec, tab);
			break;
		case ObjectType_array:
			ArrayInfo_headerAsnConv(fp, p->name, p->srcName, t_api | OBJECT_API_ASN_CONV, (ArrayInfo *)p->info, spec, tab);
			break;
		case ObjectType_extern:
			break;
		case ObjectType_reference:
			break;
		case ObjectType_declare:
			break;
		case ObjectType_func:
			break;
		default:
			break;
	}
#endif
}
// OBJECT Header : ASN Converter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// OBJECT Source
static void ObjectInfo_source(FILE *fp, PublishSpec *spec, ObjectInfo *p, int tab)
{
//	ObjectInfo *o = ObjectInfo_getOrigin(p);
	ObjectInfoPubluishAPI *pub_api = ObjectInfoPubluishAPI_find(objectInfoPubluishAPI, p->type);

	prev_obj = p->type;

	if (pub_api == NULL) Dz1ThreadA_ftprintf(fp, tab, "#error %s has no publish API\n", ObjectInfo_nameOf(p));
	else if (pub_api->source == NULL) { }
	else
	{
		bool_t commented = ObjectInfo_comment(fp, p, spec, TRUE);
		pub_api->source(fp, p->name, p->srcName, ObjectInfo_apiOf(p, spec), p->info, spec, tab);
		Publish_asnConvImple(fp, spec, p, tab);
		if (commented) ObjectInfo_comment(fp, p, spec, FALSE);
	}
#if 0
	bool_t commented = FALSE;
	u32_t t_api = ObjectInfo_apiOf(p, spec);
	switch(p->type)
	{
		case ObjectType_enumerate:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			EnumInfo_source(fp, p->name, p->srcName, t_api, (EnumInfo *)p->info, spec, tab);
			break;
// 		case ObjectType_bits:
// 			BitsInfo_source(fp, spec, t_api, p->name, (BitsInfo *)p->info, tab);
// 			break;
		case ObjectType_structure:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			StructureInfo_source(fp, p->name, p->srcName, t_api, (StructureInfo *)p->info, spec, tab);
			break;
		case ObjectType_union:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			UnionInfo_source(fp, p->name, p->srcName, t_api, (UnionInfo *)p->info, spec, tab);
			break;
		case ObjectType_array:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			ArrayInfo_source(fp, p->name, p->srcName, t_api, (ArrayInfo *)p->info, spec, tab);
			break;
		case ObjectType_index:
			commented = ObjectInfo_comment(fp, p, spec, TRUE);
			IndexInfo_source(fp, p->name, p->srcName, t_api, (IndexInfo *)p->info, spec, tab);
			break;
		case ObjectType_macro:
			Macro_print(fp, spec, p->api, p->name, FALSE, tab);
		default:
			break;
	}
	Publish_asnConvImple(fp, spec, p, tab);
	if (commented) ObjectInfo_comment(fp, p, spec, FALSE);
#endif
}
// OBJECT Source
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Module utility
static void ObjectInfoList_emit(FILE *fp, PublishSpec *spec, void *fifo, void (*emit)(FILE *fp, PublishSpec *spec, ObjectInfo *p, int tab))
{
	ObjectInfo *e = NULL;
	void *c = Dz1FifoCursor_new(fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (ObjectInfo *)Dz1FifoCursor_data(c)) != NULL)
				emit(fp, spec, e, 0);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

static __inline__ str_t mkDependantName(char dst[1024], str_t src)
{
	char *dp = dst, *sp = src;
	int len = sprintf(dp, "_DZ1_TDC_");
	dp += len;
	*dp++ = upper(*sp++);
	while(*sp)
	{
		if (isUpper(*sp)) *dp++ = '_';
		*dp++ = upper(*sp++);
	}
	*dp++ = '_';
	*dp++ = 'H';
	*dp++ = '_';
	*dp++ = '\0';

	return dst;
}

static __inline__ str_t mkTestDependantName(char dst[1024], str_t src)
{
	char *dp = dst, *sp = src;
	int len = sprintf(dp, "_DZ1_TDC_TEST_");
	dp += len;
	*dp++ = upper(*sp++);
	while(*sp)
	{
		if (isUpper(*sp)) *dp++ = '_';
		*dp++ = upper(*sp++);
	}
	*dp++ = '_';
	*dp++ = 'H';
	*dp++ = '_';
	*dp++ = '\0';

	return dst;
}

static void _print_include(FILE *fp, Dz1MdefcModule *p, bool_t flag, Dz1AATree *included)
{
	if (flag == FALSE)
	{	// print include not referenced object
		if (p->includeStatus != ModuleIncludeStatus_referenced)
		{
			if (Dz1AATree_find(included, (void *)p->name) == NULL)
			{
				Dz1TdcStringList_add(included, p->name, NULL);
				fprintf(fp, "#include \"%s.h\"\n", p->name);
			}
		}
	}
	else
	{	// print include only referenced object
		if (p->includeStatus == ModuleIncludeStatus_referenced)
		{
			if (Dz1AATree_find(included, (void *)p->name) == NULL)
			{
				Dz1TdcStringList_add(included, p->name, NULL);
				fprintf(fp, "#include \"%s.h\"\n", p->name);
			}
		}
	}
}
// Module utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Object Inclusion
typedef struct HeaderInclusionArg
{
	Dz1AATree			*included;
	FILE				*fp;
} HeaderInclusionArg;

static Dz1Error _Dz1MdefcModule_headerInclude(void *ptr, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	HeaderInclusionArg *arg = (HeaderInclusionArg *)ptr;
	_print_include(arg->fp, (Dz1MdefcModule *)data, FALSE, arg->included);
	return err;
}

static bool_t Dz1MdefcModule_headerInclusion(FILE *fp, Dz1MdefcModule *module, Dz1Error *errp)
{
	Dz1AATree *included = Dz1TdcStringList_new(errp);
	if (included == NULL) ERR_OUT(errp);
	else
	{
		HeaderInclusionArg arg = { included, fp };
		pthread_cleanup_push(Dz1AATree_delAndSetNull, (void *)&included);
		if ((*errp = Dz1AATree_travel(module->moduleTree, _Dz1MdefcModule_headerInclude, (void *)&arg)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1AATree_delAndSetNull, (void *)&included);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error _Dz1MdefcModule_sourceInclude(void *ptr, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	HeaderInclusionArg *arg = (HeaderInclusionArg *)ptr;
	_print_include(arg->fp, (Dz1MdefcModule *)data, TRUE, arg->included);
	return err;
}

static bool_t Dz1MdefcModule_sourceInclusion(FILE *fp, Dz1MdefcModule *module, Dz1Error *errp)
{
	Dz1AATree *included = Dz1TdcStringList_new(errp);
	if (included == NULL) ERR_OUT(errp);
	else
	{
		HeaderInclusionArg arg = { included, fp };
		pthread_cleanup_push(Dz1AATree_delAndSetNull, (void *)&included);
		if ((*errp = Dz1AATree_travel(module->moduleTree, _Dz1MdefcModule_sourceInclude, (void *)&arg)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1AATree_delAndSetNull, (void *)&included);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Object Inclusion
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MODULE header
static int PublishSpec_include(FILE *fp, void *p)
{
	int ret = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	void *c = Dz1FifoCursor_new(p, &err);
	if (c == NULL) ERR_OUT(&err);
	else
	{
		str_t fn;
		pthread_cleanup_push(Dz1FifoCursor_del, c);
		fprintf(fp, "////////////////////////////////////////////////////////////////////////////////\n");
		for(Dz1FifoCursorForward(c))
		{
			if ((fn = (str_t)Dz1FifoCursor_data(c)) != NULL)
			{
				fprintf(fp, "#include <%s>\n", fn);
				ret = 1;
			}
		}
		fprintf(fp, "////////////////////////////////////////////////////////////////////////////////\n");
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}

void Dz1MdefcModule_header(FILE *fp, PublishSpec *spec, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char basename[1024];
	char dependentName[1024];

	mkBaseName(basename, module->name);
	mkDependantName(dependentName, basename);

	fprintf(fp, "#ifndef %s\n", dependentName);
	fprintf(fp, "#define %s\n", dependentName);
	fprintf(fp, "\n");

	if (PublishSpec_include(fp, spec->headerInclude)) fprintf(fp, "\n");

	//if ((*errp = Dz1AATree_travel(module->moduleTree, _Dz1MdefcModule_headerInclude, (void *)fp)).code) ERR_OUT(errp);
	if (Dz1MdefcModule_headerInclusion(fp, module, errp) == FALSE) ERR_OUT(errp);

	fprintf(fp, "\n");

	ObjectInfoList_emit(fp, spec, module->objFifo, ObjectInfo_header);

	fprintf(fp, "#endif\n");
}
// MODULE header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MODULE header : ASN Converter
void Dz1MdefcModule_headerAsnConv(FILE *fp, PublishSpec *spec, Dz1MdefcModule *module)
{
	char basename[1024];
	char dependentName[1024];
	// Dz1Error err = DZ1_ERROR_INITIALIZER;
	mkBaseName(basename, module->name);
	mkDependantName(dependentName, basename);

	fprintf(fp, "#ifndef %s_ASN_CONV\n", dependentName);
	fprintf(fp, "#define %s_ASN_CONV\n", dependentName);
	fprintf(fp, "\n");

	fprintf(fp, "#include <%s.h>\n", basename);
	fprintf(fp, "#include \"%s_NewAsn.h\"\n\n", basename);
	fprintf(fp, "\n");
	if (strcmp(module->ext, "asn")==0)
	{
		fprintf(fp, "#include \"dz1_gasn_support.h\"\n\n");
	}
	ObjectInfoList_emit(fp, spec, module->objFifo, ObjectInfo_headerAsnConv);

	fprintf(fp, "#endif\n");
}
// MODULE header : ASN Converter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MODULE source
void Dz1MdefcModule_source(FILE *fp, PublishSpec *spec, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char basename[1024];
	mkBaseName(basename, module->name);

	if (PublishSpec_include(fp, spec->sourceInclude)) fprintf(fp, "\n");

	fprintf(fp, "#include \"%s.h\"\n\n", basename);

//	Dz1AATree_travel(module->moduleTree, _Dz1MdefcModule_sourceInclude, (void *)fp);
	if (Dz1MdefcModule_sourceInclusion(fp, module, errp) == FALSE) ERR_OUT(errp);

	ObjectInfoList_emit(fp, spec, module->objFifo, ObjectInfo_source);
}
// MODULE source
///////////////////////////////////////////////////////////////////////////////
