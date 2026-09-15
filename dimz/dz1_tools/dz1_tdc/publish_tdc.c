// #include <dz1_thread_stdio.h>
// #include <dz1_malloc.h>
// #include <dz1_aatree.h>
// #include <dz1_fifo.h>
// #include <dz1_str.h>
// 
// #include "publish_tdc.h"
// #include "misc.h"
// 
// static void _print_include(FILE *fp, Dz1MdefcModule *p, bool_t flag)
// {
// 	if (p->includeStatus == ModuleIncludeStatus_included)
// 		Dz1Thread_ftprintf(fp, 1, "include %s;\n", p->name);
// }
// 
// static Dz1Error _Dz1MdefcModule_tdcInclude(void *ptr, void *data)
// {
// 	Dz1Error err = DZ1_ERROR_INITIALIZER;
// 	_print_include((FILE *)ptr, (Dz1MdefcModule *)data, FALSE);
// 	return err;
// }
// 
// /*
// #define OBJECT_API_DUMP						0x08000000
// #define OBJECT_API_FDUMP					0x01000000
// #define OBJECT_API_USER_DUMP				0x00800000
// #define OBJECT_API_USER_FDUMP				0x00400000
// #define OBJECT_API_CMP						0x04000000
// #define OBJECT_API_CLONE					0x10000000
// #define OBJECT_API_CODEC					0x02000000
// */
// 
// typedef struct ApiNameMap
// {
// 	u32_t v;
// 	str_t name;
// } ApiNameMap;
// static ApiNameMap apiNameMap [] = 
// {
// 	{ OBJECT_API_DUMP, "dump" },
// 	{ OBJECT_API_FDUMP, "fdump" },
// 	{ OBJECT_API_USER_DUMP, "userdump" },
// 	{ OBJECT_API_USER_FDUMP, "userfdump" },
// 	{ OBJECT_API_CMP, "compare" },
// 	{ OBJECT_API_CLONE, "clone" },
// #ifdef USE_CODEC
// 	{ OBJECT_API_CODEC, "codec" },
// #endif
// 	{ OBJECT_API_NONE }
// };
// 
// #define API_BASE_STRING	"\t// with api "
// static ssize_t _getApiStr(char buf[1024], u32_t api)
// {
// 	char *cp = buf;
// 	if (api != OBJECT_API_NONE)
// 	{
// 		bool_t prev = FALSE;
// 		ApiNameMap *i;
// 		strcpy(cp, API_BASE_STRING);
// 		cp += strlen(API_BASE_STRING);
// 		for (i = apiNameMap; i->v != OBJECT_API_NONE; i++)
// 		{
// 			if (api & i->v)
// 			{
// 				if (prev)
// 				{
// 					*cp++ = ',';
// 					*cp++ = ' ';
// 				} else prev = TRUE;
// 				strcpy(cp, i->name);
// 				cp += strlen(i->name);
// 			}
// 		}
// 	}
// 	*cp = '\0';
// 	return (ssize_t)(cp - buf);
// }
// 
// static void DefinedInfo_tdc(FILE *fp, ObjectInfo *p, int tab)
// {
// 	DefinedInfo *info = (DefinedInfo *)p->info;
// 	ObjectInfo *origin = info->origin;
// 	char apiStr[1024];
// 	u32_t api = p->api == OBJECT_API_NONE ? ObjectInfo_apiOf(p) : p->api;
// 	_getApiStr(apiStr, api);
// 
// 	Dz1Thread_ftprintf(fp, tab, "typedef %s%s %s;%s\n\n", info->isForwarded ? "struct " : "", origin->name, p->name, apiStr);
// }
// 
// static void EnumEntry_tdc(FILE *fp, str_t prefix, EnumEntry *p, bool_t isLast, int tab)
// {
// 	//                           1 2 3 4
// 	Dz1Thread_ftprintf(fp, tab, "%s%s%s%s\n",
// 					p->name,
// 					p->valStr ? " = " : "",
// 					p->valStr ? p->valStr : "",
// 					isLast ? "" : ",");
// }
// 
// static void EnumList_tdc(FILE *fp, str_t prefix, EnumList *p, int tab)
// {
// 	EnumEntry *e = NULL;
// 	void *c = Dz1FifoCursor_new(p->fifo, NULL);
// 	if (c)
// 	{
// 		pthread_cleanup_push(Dz1FifoCursor_del, c);
// 
// 		for (Dz1FifoCursorForward(c))
// 		{
// 			e = (EnumEntry *)Dz1FifoCursor_data(c);
// 			EnumEntry_tdc(fp, prefix, e, Dz1FifoCursor_isLast(c), tab);
// 		}
// 		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
// 	}
// }
// 
// static void EnumInfo_tdc(FILE *fp, ObjectInfo *p, int tab)
// {
// 	EnumInfo *info = (EnumInfo *)p->info;
// 
// 	if (info->isGenerated == FALSE)
// 	{
// 		char apiStr[1024];
// 		u32_t api = p->api == OBJECT_API_NONE ? ObjectInfo_apiOf(p) : p->api;
// 		_getApiStr(apiStr, api);
// 
// 		Dz1Thread_ftprintf(fp, tab, "typedef enum %s\n", p->name);
// 		Dz1Thread_ftprintf(fp, tab++, "{\n");
// 		EnumList_tdc(fp, p->name, info->enums, tab);
// 		Dz1Thread_ftprintf(fp, --tab, "} %s;%s\n\n", p->name, apiStr);
// 	}
// }
// 
// static __inline__ str_t tdcForwardCaster(int type)
// {
// 	if (type == FORWARD_TYPE_NONE) return "";
// 	else if (type == FORWARD_TYPE_STRUCT) return "struct ";
// 	else if (type == FORWARD_TYPE_UNION) return "union ";
// 	else if (type == FORWARD_TYPE_ENUM) return "enum ";
// 	else
// 	{
// 		printf("forwardCaster() : type = %d\n", type);
// 		return "#error !!forwardCaster!! ";
// 	}
// }
// 
// #define OPT_STR_BASE	"\t// is "
// #define OPT_STR_CHK_BASE(base, cp)		do { if ((base) == FALSE) { strcpy(cp, OPT_STR_BASE); cp += strlen(OPT_STR_BASE); (base) = TRUE; } } while(0)
// #define STR_CAT_AND_MOVE(cp, str, prev)			do { if ((prev) == FALSE) (prev) = TRUE; else { *cp++ = ','; *cp++ = ' '; } strcpy(cp, str); cp += strlen(str); } while(0)
// 
// static ssize_t _getStructMemberOptStr(char buf[1024], StructMemberEntry *p)
// {
// 	char *cp = buf;
// 	bool_t base = FALSE;
// 	bool_t prev = FALSE;
// 
// 	buf[0] = '\0';
// 
// 	if (p->argInvolve == FALSE)			// TRUE="", FALSE="notarg"
// 	{
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "notarg", prev);
// 	}
// 
// 	if (p->isIndex)				// TRUE="key", FALSE=""
// 	{
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "key", prev);
// 	}
// 	
// 	if (p->isReferenced)		// TRUE="ref", FALSE=""
// 	{
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "ref", prev);
// 	}
// 
// 	switch(p->mode)
// 	{
// 	case MemberDumpMode_normal:
// 		break;
// 	case MemberDumpMode_value:
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "valdump", prev);
// 		break;
// 	case MemberDumpMode_omit:
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "nodump", prev);
// 		break;
// 	case MemberDumpMode_cascade:
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "cascadedump", prev);
// 		break;
// 	default:
// 		break;
// 	}
// 
// 	prev = FALSE;
// 	if (p->isAsnOptional)		// TRUE="-- ASN OPTIONAL", FALSE=""
// 	{
// 		STR_CAT_AND_MOVE(cp, "\t-- ASN OPTIONAL", prev);
// 	}
// 
// 	return (ssize_t)(cp - buf);
// }
// 
// static void StructureMemberEntry_size(StructMemberEntry *p, size_t *tl, size_t *il)
// {
// 	char temp[1024];
// 	size_t _tl;
// 	size_t _il = strlen(p->instance) + 1;
// 
// 	sprintf(temp, "%s%s", tdcForwardCaster(p->isForwarded), p->type->name);
// 	_tl = strlen(temp);
// 
// 	(*tl) = (_tl > (*tl) ? _tl : *tl);
// 	(*il) = (_il > (*il) ? _il : *il);
// }
// 
// static void StructureMemberEntry_tdc(FILE *fp, str_t name, StructMemberEntry *p, size_t tl, size_t il, int tab)
// {
// 	char optStr[1024], type[1024], fmt[1024];
// 	size_t _il = strlen(p->instance) + 1, pad = il - _il;
// 	_getStructMemberOptStr(optStr, p);
// 
// 	sprintf(type, "%s%s",tdcForwardCaster(p->isForwarded), p->type->name);
// 
// 	// "%-14s %s%s"
// 	sprintf(fmt, "%%-%us %%s%%s;", (u32_t)tl); // type, pointer, name
// 	TP(fp, tab); fprintf(fp, fmt, type, p->isPointer ? "*" : " ", p->instance);
// 	if (optStr[0] != '\0')
// 	{
// 		while(pad--) fprintf(fp, " ");
// 		fprintf(fp, "%s\n", optStr);
// 	}
// 	else fprintf(fp, "\n");
// }
// 
// static void StructureMemberList_size(StructMemberList *p, size_t *tl, size_t *il)
// {
// 	StructMemberEntry *e = NULL;
// 	void *c = Dz1FifoCursor_new(p->fifo, NULL);
// 	if (c)
// 	{
// 		pthread_cleanup_push(Dz1FifoCursor_del, c);
// 
// 		for (Dz1FifoCursorForward(c))
// 		{
// 			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
// 				StructureMemberEntry_size(e, tl, il);
// 		}
// 		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
// 	}
// }
// 
// static void StructureMemberList_tdc(FILE *fp, str_t name, StructMemberList *p, size_t tl, size_t il, int tab)
// {
// 	StructMemberEntry *e = NULL;
// 	void *c = Dz1FifoCursor_new(p->fifo, NULL);
// 	if (c)
// 	{
// 		pthread_cleanup_push(Dz1FifoCursor_del, c);
// 
// 		for (Dz1FifoCursorForward(c))
// 		{
// 			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
// 				StructureMemberEntry_tdc(fp, name, e, tl, il, tab);
// 		}
// 		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
// 	}
// }
// 
// void StructureInfo_tdc(FILE *fp, u32_t api, str_t name, StructureInfo *p, int tab)
// {
// 	bool_t printed = FALSE;
// 
// 	size_t tl = 0, il = 0;
// 
// 	char apiStr[1024];
// 	_getApiStr(apiStr, api);
// 
// 	// Declare Structure
// 	TP(fp, tab); fprintf(fp, "typedef struct %s\n", name);
// 	TP(fp, tab++); fprintf(fp, "{\n");
// 	StructureMemberList_size(p->members, &tl, &il);
// 	StructureMemberList_tdc(fp, name, p->members, tl, il, tab);
// 	TP(fp, --tab); fprintf(fp, "} %s;%s\n\n", name, apiStr);
// 
// 	// Declare New(M)
// 
// 	if (printed) fprintf(fp, "\n");
// }
// 
// static ssize_t _getUnionMemberOptStr(char buf[1024], UnionMemberEntry *p)
// {
// 	char *cp = buf;
// 	bool_t base = FALSE;
// 	bool_t prev = FALSE;
// 
// 	if (p->isReferenced)		// TRUE="ref", FALSE=""
// 	{
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "ref", prev);
// 	}
// 
// 	switch(p->dumpMode)
// 	{
// 	case MemberDumpMode_normal:
// 		break;
// 	case MemberDumpMode_value:
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "valdump", prev);
// 		break;
// 	case MemberDumpMode_omit:
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "nodump", prev);
// 		break;
// 	case MemberDumpMode_cascade:
// 		OPT_STR_CHK_BASE(base, cp);
// 		STR_CAT_AND_MOVE(cp, "cascadedump", prev);
// 		break;
// 	default:
// 		break;
// 	}
// 	*cp = '\0';
// 	return (ssize_t)(cp - buf);
// }
// 
// static void UnionMemberEntry_tdc(FILE *fp, UnionMemberEntry *p, int tab)
// {
// 	char optStr[1024];
// 	_getUnionMemberOptStr(optStr, p);
// 	//                        1 2 3 4  5
// 	TP(fp, tab); fprintf(fp, "%s%s%s%s;%s\n",
// 						tdcForwardCaster(p->isForwarded),
// 						p->type->name,
// 						p->isPointer ? " *" : " ",
// 						p->instance, optStr);
// }
// 
// static void UnionMemberList_loop(FILE *fp, UnionMemberList *p, int tab,
// 								void (*func)(FILE *fp, UnionMemberEntry *p, int tab))
// {
// 	UnionMemberEntry *e = NULL;
// 	void *c = Dz1FifoCursor_new(p->fifo, NULL);
// 	if (c)
// 	{
// 		pthread_cleanup_push(Dz1FifoCursor_del, c);
// 
// 		for (Dz1FifoCursorForward(c))
// 			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL) func(fp, e, tab);
// 
// 		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
// 	}
// }
// 
// static void UnionMemberList_tdc(FILE *fp, UnionMemberList *p, int tab)
// { UnionMemberList_loop(fp, p, tab, UnionMemberEntry_tdc); }
// 
// static void UnionInfo_tdc(FILE *fp, u32_t api, str_t name, UnionInfo *p, int tab)
// {
// 	char apiStr[1024];
// 	_getApiStr(apiStr, api);
// 
// 	TP(fp, tab); fprintf(fp, "typedef union %s\n", name);
// 	TP(fp, tab++); fprintf(fp, "{\n");
// 	UnionMemberList_tdc(fp, p->members, tab);
// 	TP(fp, --tab); fprintf(fp, "} %s;%s\n\n", name, apiStr);
// }
// 
// static str_t _getArrayModeStr(ArrayType type)
// {
// 	str_t ret = NULL;
// 	switch(type)
// 	{
// 	default:
// 	case ArrayType_normal:
// 		ret = "array";
// 		break;
// 	case ArrayType_ordered:
// 		ret = "ordered table";
// 		break;
// 	case ArrayType_unique:
// 		ret = "unique table";
// 		break;
// 	}
// 	return ret;
// }
// 
// typedef struct ArrApiMap
// {
// 	u32_t v;
// 	str_t name;
// } ArrApiMap;
// static ArrApiMap arrApiMap[] =
// {
// 	{ ARRAY_API_REMOVE, "remove" },
// 	{ ARRAY_API_EXTRACT, "extract" },
// 	{ ARRAY_API_FIND, "find" },
// 	{ ARRAY_API_GETHEAD, "gethead" },
// 	{ ARRAY_API_GETTAIL, "gettail" },
// 	{ ARRAY_API_COUNT, "count" },
// 	{ 0 }
// };
// 
// static ssize_t _getArrayApiStr(char buf[1024], u32_t api)
// {
// 	char *cp = buf;
// 	bool_t prev = FALSE;
// 	ArrApiMap *i;
// 	if (api & 0x3Fffffff)
// 	{
// 		*cp++ = '(';
// 		for (i = arrApiMap; i->v != 0; i++)
// 		{
// 			if (api & i->v)
// 			{
// 				if (prev)
// 				{
// 					*cp++ = ',';
// 					*cp++ = ' ';
// 				}
// 				else prev = TRUE;
// 				strcpy(cp, i->name); cp += strlen(i->name);
// 			}
// 		}
// 		*cp++ = ')';
// 	}
// 	*cp = '\0';
// 	return (ssize_t)(cp - buf);
// }
// 
// void ArrayInfo_tdc(FILE *fp, u32_t api, str_t name, ArrayInfo *p, int tab)
// {
// 	char arrayApiStr[1024];
// 	_getArrayApiStr(arrayApiStr, p->arrayApi);
// 	// Structure Declare              1  2 3   4 5
// 	TP(fp, tab); fprintf(fp, "typedef %s %s%s [%s%s%s];\n\n",
// 						_getArrayModeStr(p->type),
// 						name,
// 						arrayApiStr,				// (find, extract, ...)
// 						p->isReferenced ? "&" : "",
// 						tdcForwardCaster(p->isForward),
// 						p->entry->name);
// }
// 
// static void ExternInfo_tdc(FILE *fp, u32_t api, str_t name, ExternInfo *info, int tab)
// {
// 	char nativePrefixStr[1024];
// 	char apiStr[1024];
// 	_getApiStr(apiStr, api);
// 
// 	if (info->prefix != NULL)
// 		sprintf(nativePrefixStr, " with prefix %s", info->prefix);
// 	else nativePrefixStr[0] = '\0';
// 
// 	//                                          1 2 3       4  5
// 	Dz1Thread_ftprintf(fp, tab, "typedef native %s%s%s from %s;%s\n\n",
// 		info->isStatic ? "static " : "",
// 		name,
// 		nativePrefixStr,
// 		info->module_name,
// 		apiStr);
// }
// 
// static void Reference_tdc(FILE *fp, u32_t api, str_t name, ExternInfo *info, int tab)
// {
// 	char nativePrefixStr[1024];
// 	char apiStr[1024];
// 	_getApiStr(apiStr, api);
// 
// 	if (info->prefix != NULL)
// 		sprintf(nativePrefixStr, " with prefix %s", info->prefix);
// 	else nativePrefixStr[0] = '\0';
// 
// 	//                                             1 2 3       4  5
// 	Dz1Thread_ftprintf(fp, tab, "typedef reference %s%s%s from %s;%s\n\n",
// 		info->isStatic ? "static " : "",
// 		name,
// 		nativePrefixStr,
// 		info->module_name,
// 		apiStr);
// }
// 
// static void FunctionInfoArg_tdc(FILE *fp, FunctionArg *p, bool_t isFirst, bool_t nl, int tab)
// {
// 	if (!isFirst) fprintf(fp, ", ");
// 	if (nl) { fprintf(fp, "\n"); TP(fp, tab); }
// 	fprintf(fp, "%s%s ", tdcForwardCaster(p->argForward),
// 						p->argType->name);
// 	if (p->argPtrCnt)
// 	{
// 		int cnt = p->argPtrCnt;
// 		while(cnt--) fprintf(fp, "*");
// 	}
// 	if (p->instance) fprintf(fp, "%s", p->instance);
// }
// 
// static void FunctionArgs_tdc(FILE *fp, FunctionArgs *args, int tab)
// {
// 	bool_t isFirst = FALSE;
// 	bool_t nl = FALSE;
// 	Dz1Error err = DZ1_ERROR_INITIALIZER;
// 	FunctionArg *arg = NULL;
// 	void *cursor = Dz1FifoCursor_new(args->list, &err);
// 
// 	if (args->count(args) > 3) nl = TRUE;
// 
// 	for (Dz1FifoCursorForward(cursor))
// 	{
// 		if ((arg = (FunctionArg *)Dz1FifoCursor_data(cursor)) == NULL) ERR_SET_OUT(&err, EFAULT);
// 		else FunctionInfoArg_tdc(fp, arg, isFirst, nl, tab + 5);
// 		isFirst = FALSE;
// 	}
// }
// 
// static void FunctionInfo_tdc(FILE *fp, u32_t api, str_t name, FunctionInfo *info, int tab)
// {
// 	//                                        1 2  3 4
// 	Dz1Thread_ftprintf(fp, tab, "typedef func %s%s %s%s(",
// 						tdcForwardCaster(info->retForward),
// 						info->retType->name,
// 						info->retIsPointer ? "*" : "",
// 						name);
// 	FunctionArgs_tdc(fp, info->args, tab);
// 	Dz1Thread_fprintf(fp, ");\n\n");
// }
// 
// static void ObjectInfo_tdc(FILE *fp, ObjectInfo *p, int tab)
// {
// 	switch(p->type)
// 	{
// 		case ObjectType_defined:
// 			DefinedInfo_tdc(fp, p, tab);
// 			break;
// 		case ObjectType_enumerate:
// 			EnumInfo_tdc(fp, p, tab);
// 			break;
// #if 0
// 		case ObjectType_bits:
// 			BitsInfo_header(fp, spec, ObjectInfo_apiOf(p), p->name, (BitsInfo *)p->info, tab);
// 			break;
// #endif
// 		case ObjectType_structure:
// 			StructureInfo_tdc(fp, ObjectInfo_apiOf(p), p->name, (StructureInfo *)p->info, tab);
// 			break;
// 		case ObjectType_union:
// 			UnionInfo_tdc(fp, ObjectInfo_apiOf(p), p->name, (UnionInfo *)p->info, tab);
// 			break;
// 		case ObjectType_array:
// 			ArrayInfo_tdc(fp, ObjectInfo_apiOf(p), p->name, (ArrayInfo *)p->info, tab);
// 			break;
// 		case ObjectType_extern:
// 			ExternInfo_tdc(fp, ObjectInfo_apiOf(p), p->name, (ExternInfo *)p->info, tab);
// 			break;
// 		case ObjectType_reference:
// 			Reference_tdc(fp, ObjectInfo_apiOf(p), p->name, (ExternInfo *)p->info, tab);
// 			break;
// 		case ObjectType_declare:
// 			TP(fp, tab); fprintf(fp, "struct %s;\n\n", p->name);
// 			break;
// 		case ObjectType_func:
// 			FunctionInfo_tdc(fp, OBJECT_API_NONE, p->name, (FunctionInfo *)p->info, tab);
// 			break;
// 		default:
// 			break;
// 	}
// }
// 
// static void ObjectInfoList_emit(FILE *fp, void *fifo, void (*emit)(FILE *fp, ObjectInfo *p, int tab))
// {
// 	ObjectInfo *e = NULL;
// 	void *c = Dz1FifoCursor_new(fifo, NULL);
// 	if (c)
// 	{
// 		pthread_cleanup_push(Dz1FifoCursor_del, c);
// 
// 		for (Dz1FifoCursorForward(c))
// 		{
// 			if ((e = (ObjectInfo *)Dz1FifoCursor_data(c)) != NULL)
// 				emit(fp, e, 1);
// 		}
// 		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
// 	}
// }
// 
// static void ObjectInfoList_tdc(FILE *fp, void *fifo) { ObjectInfoList_emit(fp, fifo, ObjectInfo_tdc); }
// 
// void Dz1MdefcModule_tdc(FILE *fp, Dz1MdefcModule *module)
// {
// 	char basename[1024];
// 	Dz1Error err = DZ1_ERROR_INITIALIZER;
// 	mkBaseName(basename, module->name);
// 
// 	fprintf(fp, "message set definition {\n");
// 
// 	if ((err = Dz1AATree_travel(module->moduleTree, _Dz1MdefcModule_tdcInclude, (void *)fp)).code) ERR_OUT(&err);
// 
// 	fprintf(fp, "\n");
// 
// 	ObjectInfoList_tdc(fp, module->objFifo);
// 
// 	fprintf(fp, "}\n");
// }
// 
