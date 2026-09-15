#include <ctype.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_aatree.h>
#include <dz1_parser.h>
#include <dz1_parser_init.h>

#include <Dz1TdcInfoModule.h>

#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"
#include "dz1_mdefc_parser.h"
#include "misc.h"

#define tValTake(dst)		do { (dst) = t->v; t->v = NULL; } while(0)

//static __inline__ int ObjectInfo_cmp(ObjectInfo *a, ObjectInfo *b) { return strcmp(a->name, b->name); }

/*
static bool_t isDigitStr(str_t str)
{
	if (*str == '-' || *str == '+') str++;

	if (*str == '\0') return FALSE;
	else
	{
		while(*str)
			if (!isdigit(*str++)) return FALSE;
	}
	return TRUE;
}
*/

static void Dz1MdefcParserEnv_clean(Dz1MdefcParserEnv *p)
{
	Dz1MdefcMacroStack *node = NULL;

	if (p->module) Dz1MdefcModule_del(p->module);
	if (p->obj) ObjectInfo_del(p->obj);
//	if (p->undefObjects) Dz1AATree_del(p->undefObjects);

	if (p->enumEntry.name) Dz1Str_del(p->enumEntry.name);
	if (p->enumEntry.valStr) Dz1Str_del(p->enumEntry.valStr);

	if (p->structEntry.instance) Dz1Str_del(p->structEntry.instance);

	if (p->unionEntry.instance) Dz1Str_del(p->unionEntry.instance);

	if (p->include) Dz1Str_del(p->include);

	while(p->macro_stk != NULL)
	{
		if ((node = Dz1MdefcMacroStack_pop(&p->macro_stk, NULL)) != NULL)
			Dz1MdefcMacroStack_del(node);
	}
}

static str_t syntax =
"main = message=new_module set definition <liststart>\n"
"		[<Includes>]*\n"
"		[<Definitions>]+\n"
"		<listend><done>;\n"
"\n"
"\n"	// TDC Include
"Includes = include <symbol>=set_include_name <semicolon>=do_tdc_include;\n"
"\n"
"\n"	// Element declare
"Definitions = <Predeclare>|<Definition>|<Macro>;\n"
"\n"
"\n"	// Pre-Declation Type	: struct|union {TypeName};
"Predeclare = struct|union|enum=new_declare <symbol>=set_declare_name <semicolon>=add_object;\n"
"\n"
"\n"	// Object Definition
"Definition = typedef <Native>|<Reference>|<EnumType>|<StructType>|<UnionType>|<ArrayType>|<IndexType>|<FuncType>|<ConstantType>|<DefinedType>=add_object;\n"
"\n"
"\n"	// Native/Reference	: typedef native|reference [static|simple|ptr|union|struct] {TdcTypeName} [with prefix {ApiPrefix}] from {HeaderName}; // with api ...
"Native		= native=set_extern_cons	[static|simple|ptr|union|struct=set_extern_flag] <symbol>=new_extern	[<NativePrefix>] from <string>|<symbol>=add_module_incl	<semicolon> [<BasicSupportApis>];\n"
"Reference	= reference=set_extern_cons	[static|simple|ptr|union|struct=set_extern_flag] <symbol>=new_reference	[<NativePrefix>] from <symbol>=add_module_ref			<semicolon> [<BasicSupportApis>];\n"
"NativePrefix = with prefix <symbol>=set_extern_info;\n"
"\n"
"\n"	// Defined		: typedef [struct|union] SourceType DestinationType;	// with api ...
"DefinedType = [union|struct=set_defined_forward] <symbol>=new_defined <symbol>=set_obj_name <semicolon> [<BasicSupportApis>];\n"
"\n"
"\n"	// Enumerate
"EnumType = enum=new_enum [<symbol>=set_obj_name] <liststart> <EnumTypeBody> <listend> <symbol>=chk_and_set_obj_name <semicolon> [<BasicSupportApis>];\n"
"EnumTypeBody = <EnumTypeBodyEntry>=add_enum_entry [<EnumTypeBodyEntries>]*;\n"
"EnumTypeBodyEntry = <symbol>|<number>=set_enum_entry_name [<EnumTypeBodyEntryDefault>];\n"
"EnumTypeBodyEntries = <comma> <EnumTypeBodyEntry>=add_enum_entry;\n"
"EnumTypeBodyEntryDefault = <equal> <symbol>|<number>|<string>=set_enum_entry_valStr;\n"
"\n"
"\n"	// Structure
"StructType = struct=new_struct [<symbol>=set_obj_name] <liststart> [<StructTypeBody>=add_struct_member]* <listend> <symbol>=chk_and_set_obj_name <semicolon> [<StructSupportApis>];\n"
"StructTypeBody = [union|struct|enum=set_struct_member_forward] <symbol>=set_struct_member_type\n"
"                 [<mul>=set_struct_member_pointer] <symbol>=set_struct_member_instance [<StructMemberArray>] <semicolon> [<StructTypeBodyOpt>];\n"
"\n"
"StructMemberArray = <blockstart>=set_struct_member_array <symbol>|<number>|<string>=set_struct_member_array_cnt [<StructMemberArrayRef>] <blockend>;\n"
"StructMemberArrayRef = <comma> ref=set_struct_member_array_ref;\n"
"\n"
"StructTypeBodyOpt = <div><div> is <StructTypeBodyOptAttrs>;\n"
"StructTypeBodyOptAttrs = <StructTypeBodyOptAttr> [<StructTypeBodyOptAttrMode>]*;\n"
"StructTypeBodyOptAttr = notarg|key|ref|nodump|valdump|cascadedump=set_struct_member_attr;\n"
"StructTypeBodyOptAttrMode = <comma> <StructTypeBodyOptAttr>;\n"
"\n"
"StructSupportApis = <div><div> with [windows=set_api_windows] api <StructSupportApi> [<StructSupportApiMore>]*;\n"
"StructSupportApi = <symbol>=set_api_struct_obj;\n"
"StructSupportApiMore = <comma> <StructSupportApi>;\n"
"\n"
"\n"	// Union
"UnionType = union=new_union [<symbol>=set_obj_name] <liststart> [<UnionTypeBody>=add_union_member]* <listend> <symbol>=chk_and_set_obj_name <semicolon> [<UnionSupportApis>];\n"
"UnionTypeBody = <UnionTypeBodyImport>|<UnionTypeBodyMember>;\n"
"UnionTypeBodyImport = <blockstart>=set_union_member_forward <symbol>=set_union_member_type <blockend> <semicolon>;"
"UnionTypeBodyMember = [union|struct|enum=set_union_member_forward] <symbol>=set_union_member_type [<UnionPresent>]\n"
"						[<mul>=set_union_member_pointer] <symbol>=set_union_member_instance [<UnionMemberArray>] <semicolon> [<UnionMemberOpt>];\n"
"\n"
"UnionPresent		 = <blockstart> <number>|<symbol>|<string>=set_union_member_present <blockend>;\n"
"\n"
"UnionMemberArray	 = <blockstart>=set_union_member_array <number>|<string>=set_union_member_array_end [<UnionMemberArrayRef>] <blockend>;\n"
"UnionMemberArrayRef = <comma> ref=set_union_member_array_ref;\n"
"\n"
"UnionMemberOpt		 = <div><div> is <UnionMemberOptAttrs>;\n"
"UnionMemberOptAttrs = <UnionMemberOptAttr> [<UnionMemberOptAttrMore>]*;\n"
"UnionMemberOptAttr	 = ref|nodump|valdump|cascadedump=set_union_member_attr;\n"
"UnionMemberOptAttrMore = <comma> <UnionMemberOptAttr>;\n"
"\n"
"UnionSupportApis = <div><div> with [windows=set_api_windows] api <UnionSupportApi> [<UnionSupportApiMore>]*;\n"
"UnionSupportApi = <symbol>=set_api_union_obj;\n"
"UnionSupportApiMore = <comma> <UnionSupportApi>;\n"
"\n"
"\n"	// Array/Table
"ArrayType =	[unique|ordered=set_array_unique] array|table=new_array <symbol>=set_obj_name [<ArrayOperApis>] <blockstart>\n"
"					[<and>=set_array_ref] [struct|union=set_array_forward] <symbol>=set_array_entry\n"
"				<blockend> [<string>=set_array_dump] <semicolon> [<ListSupportApis>];\n"
"\n"
"ArrayOperApis = <lbracket> <ArrayOperApi> [<ArrayOperApiMore>]* <rbracket>;\n"
"ArrayOperApi = count|remove|find|extract|gethead|gettail=set_array_api;\n"
"ArrayOperApiMore = <comma> <ArrayOperApi>;\n"
"\n"
"\n"	// Index : typedef [unique] index {TypeName}(gethead, gettail) [SomeEntry(key1, key2)]
"IndexType =	[unique=set_index_unique] index=new_index <symbol>=set_obj_name [<IndexOperApis>] <blockstart>\n"
"					[<and>=set_index_ref] [struct|union=set_index_forward] <symbol>=set_index_entry [<IndexKeyDef>]\n"
"				<blockend> [<string>=set_index_dump] <semicolon> [<ListSupportApis>];\n"
"\n"
"IndexOperApis = <lbracket> <IndexOperApi> [<IndexOperApiMore>]* <rbracket>;\n"
"IndexOperApi = gethead|gettail=set_index_api;\n"
"IndexOperApiMore = <comma> <IndexOperApi>;\n"
"\n"
"IndexKeyDef = <lbracket> <IndexKeyName> [<IndexKeyNameMore>]* <rbracket>;\n"
"IndexKeyName = <symbol>=add_index_key;\n"
"IndexKeyNameMore = <comma> <IndexKeyName>;\n"
"\n"
"\n"	// Array/Table/Index support API
"ListSupportApis = <div><div> with [windows=set_api_windows] api <ListSupportApi> [<ListSupportApiMore>]*;\n"
"ListSupportApi = <symbol>=set_api_array_obj;\n"
"ListSupportApiMore = <comma> <ListSupportApi>;\n"
"\n"
"\n"	// extern/reference/defined/enumerated support API
"BasicSupportApis = <div><div> with [windows=set_api_windows] api <BasicSupportApi> [<BasicSupportApiMore>]*;\n"
"BasicSupportApi = <symbol>=set_api_basic_obj;\n"
"BasicSupportApiMore = <comma> <BasicSupportApi>;\n"
"\n"
"\n"	// Function		: typedef func {RetType} [*]{FuncTypeName}([struct|union] ArgType1 [*]arg1, ...);
"FuncType =		func=new_func [union|struct=set_func_ret_forward] <symbol>=set_func_ret_type [<mul>=set_func_ret_ptr]* <symbol>=set_obj_name\n"
"					<lbracket> <FuncTypeArg> <rbracket> <semicolon>;\n"
"\n"
"FuncTypeArg = <FuncTypeArgOne>=add_func_arg [<FuncTypeArgMore>]*;\n"
"FuncTypeArgOne = [struct|union=set_func_arg_forward] <symbol>=set_func_arg_type [<mul>=inc_func_arg_ptr]* [<symbol>=set_func_arg_instance];\n"
"FuncTypeArgMore = <comma> <FuncTypeArgOne>=add_func_arg;\n"
"\n"
"\n"	// Constant		: #define {DefineName} {ReplaceText}
"ConstantType = constant=new_constant <symbol>=set_obj_name <ConstantData> <semicolon>;\n"
"ConstantData = <ConstantSimple>|<ConstantExpr>;\n"
"ConstantSimple = <number>|<symbol>|<string>=set_constant_data;\n"
"ConstantExpr = <lbracket> <string>=set_constant_data_expr <rbracket>;\n"
"\n"
"\n"	// Macro		: #define, #ifdef, #ifndef, #else, #endif
"Macro = <hash>=new_macro <MacroIfdef>|<MacroElseEnd>=oper_macro_stack;\n"
"MacroIfdef = define|ifdef|ifndef=set_macro_type <symbol>=set_macro_name;\n"
"MacroElseEnd = else|endif=set_macro_name_from_stk;\n"
"";

///////////////////////////////////////////////////////////////////////////////
// Misc
static Dz1Error set_false(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	p->boolean = FALSE;

	return err;
}

static Dz1Error set_true(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	p->boolean = TRUE;

	return err;
}
// Misc
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Module
static Dz1Error new_module(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if ((p->module = Dz1MdefcModule_new(p->filename, "tdc", p->spec, &err)) == NULL) ERR_OUT(&err);
	else
	{
	}

	return err;
}
// Module
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Include
/*
typedef linked list MyDoubleLinkedList(double, unique)
{
	typedef struct MyDoubleLinkedEntry
	{ 
		uint32			data1;		// is notarg
		str				data2;		// is ref, nodump
	} MyDoubleLinkedEntry;			// with api dump, compare
};
"LinkedList = [double=set_list_type] linked list <symbol>=set_list_name [<LinkedListOpt>] <liststart> <LinkedListEntry> <listend> <semicolon>=build_list;\n"
"LinkedListOpt = <lbracket> <LinkedListOptOne> [<LinkedListOptMore>]* <rbracket>;\n
"LinkedListOptOne = double|unique;\n"
"LinkedListOptMore = <comma> <LinkedListOptOne>;\n"
"LinkedListEntry = typedef struct=new_struct [<symbol>=set_obj_name] <liststart>\n"
"                  [<StructTypeBody>=add_struct_member]* <listend>=add_struct_member_ptr\n"
"                  <symbol>=chk_and_set_obj_name <semicolon>=set_list_entry_and_add_object [<SupportApis>];\n"
*/
static Dz1Error set_include_name(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->module->findModule(p->module, t->v) == NULL) tValTake(p->include);

	return err;
}

static Dz1Error do_tdc_include(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->include)
	{
		Dz1MdefcModule *module_root = p->module;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&p->include);

		if (0) { }
//		else if (module_root->findModule(module_root, p->include) != NULL) Dz1Error_set(errp, 0);
		else if ((*errp = Dz1MdefcModule_includeTDC(p->module, p->spec, p->inc, p->include)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull(&p->include);
	}
	return err;
}
// Include
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Common
static Dz1Error set_obj_name(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	tValTake(p->obj->name);

	return err;
}

static Dz1Error chk_and_set_obj_name(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->obj->name)
	{
		if (strcmp(p->obj->name, t->v) != 0)
		{
			Dz1Thread_printf("chk_and_set_obj_name() : Structure Name and Type Name are mismatch %s:%s\n", p->obj->name, t->v);
			ERR_SET_OUT(&err, EINVAL);
		}
	}
	else tValTake(p->obj->name);

	return err;
}

static Dz1Error add_object(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (Dz1MdefcParserEnv_addObject(p, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
// Common
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// General
/*
 * j8yykkkpwwi <- copy and paste in command mode
static Dz1Error (Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	return err;
}
*/
static Dz1Error new_declare(Dz1ParserToken *t, void *param)
{	// t->v = union | struct | enum
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	if (p->obj) ObjectInfo_del(p->obj);

	if ((p->obj = ObjectInfo_new(ObjectType_declare, NULL, NULL, OBJECT_API_BASE, t->v, &err)) == NULL) ERR_OUT(&err);
	else { t->v = NULL; }

	return err;
}

static Dz1Error set_declare_name(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *obj = p->obj;

	char name[4096] = { 0, };

	_std_snprintfA(name, sizeof(name), "_declare_%s", t->v);
	if ((obj->name = Dz1StrA_dup(name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		tValTake(obj->srcName);
		Dz1Error_set(errp, 0);
	}

	return err;
}
// General
///////////////////////////////////////////////////////////////////////////////


static Dz1Error Dz1MdefcParser_emiterInit(void *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (0) { }
	else if ((err = Dz1Parser_addEmiter(p, "new_module", new_module)).code) { ERR_OUT(&err); }

	else if ((err = Dz1Parser_addEmiter(p, "set_false", set_false)).code) { ERR_OUT(&err); }	// unused
	else if ((err = Dz1Parser_addEmiter(p, "set_true", set_true)).code) { ERR_OUT(&err); }		// unused

	else if ((err = Dz1Parser_addEmiter(p, "set_include_name", set_include_name)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "do_tdc_include", do_tdc_include)).code) { ERR_OUT(&err); }


	///////////////////////////////////////
	// Common
	else if ((err = Dz1Parser_addEmiter(p, "set_obj_name", set_obj_name)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "chk_and_set_obj_name", chk_and_set_obj_name)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "add_object", add_object)).code) { ERR_OUT(&err); }
	// Common
	///////////////////////////////////////

	else if ((err = Dz1Parser_addEmiter(p, "new_declare", new_declare)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_declare_name", set_declare_name)).code) { ERR_OUT(&err); }

	else if (Dz1MdefcEmiter_InitExtern(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitDefined(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitEnum(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitStruct(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitUnion(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitArray(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitIndex(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitFunc(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitConstant(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitMacro(p, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1MdefcEmiter_InitApi(p, errp) == FALSE) ERR_OUT(errp);

	/*
	else if ((err = Dz1Parser_addEmiter(p, "", )).code) { ERR_OUT(&err); }
	
	*/

	return err;
}

static void *Dz1MdefcParser_new(Dz1Error *err)
{
	void *p = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((p = Dz1Parser_new(errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&p);

		if ((*errp = Dz1MdefcParser_emiterInit(p)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1ParserInit_parse(p, syntax)).code) { ERR_OUT(errp); }
//		else Dz1Parser_dump(p, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Parser_delAndSetNull, (void *)&p);
	}
	return p;
}

/*
static Dz1Error _chkUndefined(void *ptr, void *entry)
{
	ObjectInfo *p = (ObjectInfo *)entry;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Thread_printf("Undefined Type %s\n", p->name);
	ERR_SET_OUT(&err, EEXIST);

	return err;
}
*/

static Dz1MdefcModule *Dz1MdefcModule_proc(void *parser, PublishSpec *spec, IncludeSpec *inc, str_t filename, str_t text, Dz1Error *err)
{
	Dz1MdefcModule *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MdefcParserEnv env =
	{
		NULL,																					// filename
		NULL,																					// spec
		NULL,																					// inc
		NULL,																					// module
		NULL,																					// obj

		{ NULL, NULL, 0 },																		// enumEntry
		FALSE,																					// definedForwarded

//		{ FALSE, NULL, NULL, FALSE, NULL, TRUE, MemberDumpMode_normal, FALSE, FALSE, FALSE },	// structEntry
		{ FALSE, NULL, NULL, FALSE, NULL, TRUE, MemberDumpMode_normal, NULL },					// structEntry
		{ FALSE, NULL, NULL, FALSE, NULL, FALSE, MemberDumpMode_normal, NULL },					// unionEntry
		{ NULL, 0, 0, NULL },																	// funcArg

		ArrayType_normal,																		// arrayType
		FALSE,																					// indexUnique

		NULL,																					// include

		FALSE,																					// boolean

		NULL																					// macro_stk
	};

	env.filename = filename;
	env.spec = spec;
	env.inc = inc;
//	env.undefObjects = Dz1AATree_new((Dz1CmpFunc)ObjectInfo_cmp, (Dz1DelFunc)ObjectInfo_del, (Dz1DumpFunc)ObjectInfo_dump, errp);
//	if (env.undefObjects == NULL) ERR_OUT(errp);
//	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1MdefcParserEnv_clean, (void *)&env);

		if ((*errp = Dz1Parser_prepare(parser, text)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Parser_process(parser, "main", &env, 0)).code)
		{
			Dz1Thread_printf("Expression Compile Fail (line %d)\n", Dz1Parser_getLineNum(parser) + 1);
			ERR_OUT(errp);
		}
		else
		{
			if (Dz1MdefcModule_isUnknownExist(env.module))
			{
				Dz1Thread_printf("!!! Unknown Object = ");
				Dz1AATree_dump(env.module->objUnknown, 0);
				ERR_SET_OUT(errp, EFAULT);
			}
			else if ((*errp = Dz1MdefcModule_fixupDefinedEnums(env.module)).code) ERR_OUT(errp);
			else if (env.macro_stk != NULL)
			{
				Dz1Thread_printf("Macro is not complete\n");
				ERR_SET_OUT(errp, EINVAL);
			}
			else { ret = env.module; env.module= NULL; }
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1MdefcParserEnv_clean, (void *)&env);
	}
	return ret;
}

Dz1MdefcModule *Dz1MdefcModule_compile(PublishSpec *spec, IncludeSpec *inc, str_t filename, str_t text, Dz1Error *err)
{
	void *p = NULL;
	Dz1MdefcModule *module = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((p = Dz1MdefcParser_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Parser_del, p);

		if ((module = Dz1MdefcModule_proc(p, spec, inc, filename, text, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1Parser_del, p);
	}
	return module;
}

Dz1Error Dz1MdefcModule_includeTDC(Dz1MdefcModule *p, PublishSpec *spec, IncludeSpec *inc, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p->findModule(p, name) == NULL)
	{
		str_t text;
		char fn[1024];
		sprintf(fn, "%s.tdc", name);

		if ((text = inc->load(inc, fn, &err)) == NULL)
		{
			Dz1Thread_printf("!!! Include TDC : No such file %s\n", fn);
			ERR_OUT(&err);
		}
		else
		{
			Dz1MdefcModule *module = NULL;
			pthread_cleanup_push((Dz1DelFunc)Dz1Str_del, (void *)text);

			if ((module = Dz1MdefcModule_compile(spec, inc, name, text, &err)) == NULL)
			{
				Dz1Thread_printf("!!! Include TDC : Compile Failed : %s\n", fn);
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

