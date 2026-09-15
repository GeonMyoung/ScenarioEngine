#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser_init.h>
#include <dz1_parser_token.h>

#include "publish_spec_parser.h"

typedef struct PublishSpecParserEnv
{
	PublishSpec *spec;
	NativeTypeSpec primitive;

	str_t errorEntryName;
	PublishErrorSpecEntry *errorEntry;

	PublishArraySpec *arraySpec;
	ArraySpecApiType arrayEntryType;
	PublishArraySpecApiMap arrayEntry;
} PublishSpecParserEnv;

static void PublishSpecParserEnv_clean(PublishSpecParserEnv *p)
{
	if (!p) return;
	if (p->spec) PublishSpec_del(p->spec);
	if (p->primitive.name) Dz1Str_del(p->primitive.name);
	if (p->primitive.native) Dz1Str_del(p->primitive.native);
	if (p->primitive.prefix) Dz1Str_del(p->primitive.prefix);
	if (p->errorEntryName) Dz1Str_del(p->errorEntryName);
	if (p->errorEntry) PublishErrorSpecEntry_del(p->errorEntry);
	if (p->arrayEntry.name) Dz1Str_del(p->arrayEntry.name);
}

static str_t syntax =
"main = publish spec definition=new_spec\n"															// 1
"           <liststart>\n"
"               pthread <equal> yes|no=set_spec_pthread <semicolon>\n"
"               [<Primitive>]+\n"
"               <BasicSpec>\n"
"               <ErrorSpec>\n"
"               <CastSpec>\n"
"               <MemorySpec>\n"
"               <PostFixSpec>\n"
"               <NormalArraySpec>\n"
"               <OrderedArraySpec>\n"																// 11
"				<UniqueArraySpec>\n"
"               <HeaderIncludeSpec>\n"
"               <SourceIncludeSpec>\n"
"           <listend><done>;\n"
"\n"
"Primitive = primitive <symbol>=set_primitive_name\n"
"                as [pointer|sizeless=set_primitive_pointer] <symbol>=set_primitive_native [<mul>=concat_primitive_native]\n"
"                with prefix <symbol>=set_primitive_prefix [<PrimitiveAttr>] <semicolon>=add_primitive;\n"
"PrimitiveAttr = with api <lbracket> <PrimitiveAttrs> <rbracket>;\n"
"PrimitiveAttrs = <symbol>=set_primitive_attr [<PrimitiveAttrMore>]*;\n"
"PrimitiveAttrMore = <comma> <symbol>=set_primitive_attr;"
"\n"
"BasicSpec = basic=new_basic <liststart> <BasicSpecBody> <listend>;\n"
"BasicSpecBody = cplusplus <equal> <symbol>=set_basic_cpplink <semicolon>\n"						// 22
"                dllport <equal> <symbol>=set_basic_dllport <semicolon>\n"
"                printf <equal> <symbol>=set_basic_printf <semicolon>\n"
"                printfA <equal> <symbol>=set_basic_printfA <semicolon>\n"
"                printfW <equal> <symbol>=set_basic_printfW <semicolon>\n"
"                tabprintf <equal> <symbol>=set_baseic_tprintf <semicolon>\n"
"                tabprintfA <equal> <symbol>=set_baseic_tprintfA <semicolon>\n"
"                tabprintfW <equal> <symbol>=set_baseic_tprintfW <semicolon>\n"
"                fprintf <equal> <symbol>=set_baseic_fprintf <semicolon>\n"
"                fprintfA <equal> <symbol>=set_baseic_fprintfA <semicolon>\n"
"                fprintfW <equal> <symbol>=set_baseic_fprintfW <semicolon>\n"
"                ftabprintf <equal> <symbol>=set_baseic_ftprintf <semicolon>\n"
"                ftabprintfA <equal> <symbol>=set_baseic_ftprintfA <semicolon>\n"
"                ftabprintfW <equal> <symbol>=set_baseic_ftprintfW <semicolon>;\n"
"\n"
"ErrorSpec = error=new_error <liststart> <ErrorSpecBody> <listend>;\n"
"ErrorSpecBody = type <equal> <symbol>=set_error_type <semicolon>\n"
"                default <equal> <symbol>=set_error_default <semicolon>\n"
"                set=new_error_entry <equal> <ErrorSpecEntry> <semicolon>=add_error_entry\n"
"                print=new_error_entry <equal> <ErrorSpecEntry> <semicolon>=add_error_entry\n"
"                setAndPrint=new_error_entry <equal> <ErrorSpecEntry> <semicolon>=add_error_entry\n"
"                probe=new_error_entry <equal> <ErrorSpecEntry> <semicolon>=add_error_entry\n"		// 32
"                clean=new_error_entry <equal> <ErrorSpecEntry> <semicolon>=add_error_entry;\n"
"ErrorSpecEntry = <symbol>=set_error_entry_name <lbracket> [<mul>=set_err_entry_ptr] <rbracket>;\n"
"\n"
"CastSpec = cast=new_cast <liststart> <CastSpecBody> <listend>;\n"
"CastSpecBody = del <equal> <lbracket> <symbol>=set_cast_del <rbracket> <semicolon>\n"
"               cmp <equal> <lbracket> <symbol>=set_cast_cmp <rbracket> <semicolon>\n"
"               dump <equal> <lbracket> <symbol>=set_cast_dump <rbracket> <semicolon>;\n"
"\n"
"MemorySpec = memory=new_memory <liststart> <MemorySpecBody> <listend>;\n"
"MemorySpecBody = error <equal> include|exclude=set_memory_error <semicolon>\n"						// 42
"                 malloc <equal> <symbol>=set_memory_malloc <semicolon>\n"
"                 calloc <equal> <symbol>=set_memory_calloc <semicolon>\n"
"                 free <equal> <symbol>=set_memory_free <semicolon>\n"
"                 cancel <equal> <symbol>=set_memory_cancel <semicolon>;\n"
"\n"
"PostFixSpec = postfix=new_postfix <liststart> <PostFixSpecBody> <listend>=fix_postfix_len;\n"
"PostFixSpecBody = new <equal> <symbol>=set_postfix_new <semicolon>\n"
"                  gen <equal> <symbol>=set_postfix_gen <semicolon>\n"
"                  purge <equal> <symbol>=set_postfix_purge <semicolon>\n"
"                  del <equal> <symbol>=set_postfix_del <semicolon>\n"
"                  delAndSetNull <equal> <symbol>=set_postfix_delAndSetNull <semicolon>\n"			// 52
"                  dump <equal> <symbol>=set_postfix_dump <semicolon>\n"
"                  fdump <equal> <symbol>=set_postfix_fdump <semicolon>\n"
"                  compare <equal> <symbol>=set_postfix_cmp <semicolon>\n"
"                  clone <equal> <symbol>=set_postfix_clone <semicolon>\n"
"                  copy <equal> <symbol>=set_postfix_copy <semicolon>\n"
"                  encode <equal> <symbol>=set_postfix_enc <semicolon>\n"
"                  decode <equal> <symbol>=set_postfix_dec <semicolon>;\n"
"\n"
"NormalArraySpec  = array=new_normal_array    <symbol>=set_array_name <liststart> <ArraySpecBody> <listend>;\n"
"OrderedArraySpec = ordered=new_ordered_array <symbol>=set_array_name <liststart> <ArraySpecBody> <listend>;\n"
"UniqueArraySpec  = unique=new_unique_array	  <symbol>=set_array_name <liststart> <ArraySpecBody> <listend>;\n"
"\n"																								// 62
"ArraySpecBody = travelFuncCast <equal> <lbracket> <symbol>=set_array_travelFuncCast <rbracket> <semicolon>\n"
"                new=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>\n"
"                purge=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>\n"
"                del=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>\n"
"                delAndSetNull=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>\n"
"                add=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>\n"
"                remove=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>\n"
"                travelForward=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>\n"
"                travelBackward=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>\n"
"                optional <liststart> [<ArraySpecBodyOptional>]+ <listend>;\n"
"ArraySpecBodyOptional = count|clone|extract|find|gethead|gettail=set_array_map_type <equal> <ArraySpecBodyEntry>=add_array_map <semicolon>;\n"
"\n"																								// 72
"ArraySpecBodyEntry = <ArraySpecBodyEntryMethod>|<ArraySpecBodyEntryApi>;\n"
"ArraySpecBodyEntryMethod = <lbracket> <symbol>=set_array_map_name <rbracket>=set_array_map_method;\n"
"ArraySpecBodyEntryApi = <symbol>=set_array_map_name;\n"
"\n"
"HeaderIncludeSpec = header include <liststart> <HeaderIncludeBody> <listend>;\n"
"HeaderIncludeBody = <symbol>=add_header_include [<HeaderIncludeBodys>]*;\n"
"HeaderIncludeBodys = <comma> <symbol>=add_header_include;\n"
"\n"
"SourceIncludeSpec = source include <liststart> <SourceIncludeBody> <listend>;\n"
"SourceIncludeBody = <symbol>=add_source_include [<SourceIncludeBodys>]*;\n"						// 82
"SourceIncludeBodys = <comma> <symbol>=add_source_include;\n";
static Dz1Error new_spec(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if (p->spec) ERR_SET_OUT(&err, EEXIST);
	else if ((p->spec = PublishSpec_new(FALSE, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_spec_pthread(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if (strcmp(t->v, "yes") == 0) p->spec->pthread = TRUE;

	return err;
}

#define tValTake(dst)	do { (dst) = t->v; t->v= NULL; } while(0)
static Dz1Error set_primitive_name(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->primitive.name);
	p->primitive.storage = NativeStorage_data;
	p->primitive.attr_flag = 0;

	return err;
}

static Dz1Error set_primitive_pointer(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if (strcmp(t->v, "pointer") == 0)
		p->primitive.storage = NativeStorage_address;
	else if (strcmp(t->v, "sizeless") == 0)
		p->primitive.storage = NativeStorage_none;
	else ERR_SET_OUT(errp, EINVAL);

	return err;
}

static Dz1Error set_primitive_native(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->primitive.native);

	return err;
}

static Dz1Error concat_primitive_native(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	char temp[1024];

	sprintf(temp, "%s *", p->primitive.native);
	Dz1Str_del(p->primitive.native);

	if ((p->primitive.native = Dz1Str_dup(temp, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_primitive_prefix(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->primitive.prefix);

	return err;
}

static Dz1Error set_primitive_attr(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if (0) { }
	else if (strcmp(t->v, "dump") == 0)		p->primitive.attr_flag |= OBJECT_API_DUMP;
	else if (strcmp(t->v, "fdump") == 0)	p->primitive.attr_flag |= OBJECT_API_FDUMP;
	else if (strcmp(t->v, "dumpA") == 0)	p->primitive.attr_flag |= (OBJECT_API_DUMP  | OBJECT_API_DUMP_MBCS);
	else if (strcmp(t->v, "fdumpA") == 0)	p->primitive.attr_flag |= (OBJECT_API_FDUMP | OBJECT_API_DUMP_MBCS);
	else if (strcmp(t->v, "dumpW") == 0)	p->primitive.attr_flag |= (OBJECT_API_DUMP  | OBJECT_API_DUMP_WIDE);
	else if (strcmp(t->v, "fdumpW") == 0)	p->primitive.attr_flag |= (OBJECT_API_FDUMP | OBJECT_API_DUMP_WIDE);
	else if (strcmp(t->v, "dumpX") == 0)	p->primitive.attr_flag |= (OBJECT_API_DUMP  | OBJECT_API_DUMP_WIDE | OBJECT_API_DUMP_MBCS);
	else if (strcmp(t->v, "fdumpX") == 0)	p->primitive.attr_flag |= (OBJECT_API_FDUMP | OBJECT_API_DUMP_WIDE | OBJECT_API_DUMP_MBCS);
	else
	{
		Dz1Thread_printf("!!! not support attribute %s\n", t->v);
		ERR_SET_OUT(errp, EINVAL);
		return err;
	}
	return err;
}

static Dz1Error add_primitive(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PublishSpecParserEnv *env = (PublishSpecParserEnv *)param;
	PublishSpec *spec = env->spec;
	NativeTypeSpec *prim = &env->primitive;
	// char chunk[4] = { 0, }; // modified by gm 20230602 - unused var chnuk
	// void *temp = NULL; // modified by gm 20230602 - unused var temp

	if (prim->attr_flag == 0)
		prim->attr_flag = (OBJECT_API_DUMP | OBJECT_API_FDUMP | OBJECT_API_DUMP_WIDE | OBJECT_API_DUMP_MBCS);

// 	if ((*errp = spec->regPrimitive(spec, primitive->name, primitive->native, primitive->storage, primitive->prefix)).code) ERR_OUT(errp);
	if (spec->regPrimitive(spec, prim->name, prim->native, prim->storage, prim->prefix, prim->attr_flag, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Str_del(prim->name); prim->name = NULL;
		Dz1Str_del(prim->native); prim->native = NULL;
		Dz1Str_del(prim->prefix); prim->prefix = NULL;
		prim->attr_flag = 0;
	}
	return err;
}

static Dz1Error new_basic(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->spec->base = PublishBasicSpec_new(NULL, NULL, 
											NULL, NULL, NULL, 
											NULL, NULL, NULL, 
											NULL, NULL, NULL,
											NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_basic_cpplink(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->cpplink);

	return err;
}

static Dz1Error set_basic_dllport(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->dllport);

	return err;
}

static Dz1Error set_basic_printf(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->printf[0]);

	return err;
}

static Dz1Error set_basic_printfA(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->printf[1]);

	return err;
}

static Dz1Error set_basic_printfW(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->printf[2]);

	return err;
}

static Dz1Error set_baseic_tprintf(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->tprintf[0]);

	return err;
}

static Dz1Error set_baseic_tprintfA(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->tprintf[1]);

	return err;
}

static Dz1Error set_baseic_tprintfW(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->tprintf[2]);

	return err;
}

static Dz1Error set_baseic_fprintf(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->fprintf[0]);

	return err;
}

static Dz1Error set_baseic_fprintfA(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->fprintf[1]);

	return err;
}

static Dz1Error set_baseic_fprintfW(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->fprintf[2]);

	return err;
}

static Dz1Error set_baseic_ftprintf(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->ftprintf[0]);

	return err;
}

static Dz1Error set_baseic_ftprintfA(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->ftprintf[1]);

	return err;
}

static Dz1Error set_baseic_ftprintfW(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->base->ftprintf[2]);

	return err;
}

static Dz1Error new_error(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->spec->error = PublishErrorSpec_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_error_type(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->error->type);

	return err;
}

static Dz1Error set_error_default(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->error->defaultVal);

	return err;
}

static Dz1Error new_error_entry(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->errorEntryName);
	if ((p->errorEntry = PublishErrorSpecEntry_new(NULL, FALSE, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error add_error_entry(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if (strcmp(p->errorEntryName, "set") == 0) { p->spec->error->set = p->errorEntry; p->errorEntry = NULL; }
	else if (strcmp(p->errorEntryName, "print") == 0) { p->spec->error->print = p->errorEntry; p->errorEntry = NULL; }
	else if (strcmp(p->errorEntryName, "setAndPrint") == 0) { p->spec->error->setAndPrint = p->errorEntry; p->errorEntry = NULL; }
	else if (strcmp(p->errorEntryName, "probe") == 0) { p->spec->error->probe = p->errorEntry; p->errorEntry = NULL; }
	else if (strcmp(p->errorEntryName, "clean") == 0) { p->spec->error->clear = p->errorEntry; p->errorEntry = NULL; }
	else ERR_SET_OUT(&err, ESRCH);

	Dz1Str_del(p->errorEntryName); p->errorEntryName = NULL;

	return err;
}

static Dz1Error set_error_entry_name(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->errorEntry->name);

	return err;
}

static Dz1Error set_err_entry_ptr(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	p->errorEntry->argIsPtr = TRUE;

	return err;
}

static Dz1Error new_cast(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->spec->cast = PublishCastSpec_new(NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_cast_del(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	char buf[1024];
	sprintf(buf, "(%s)", t->v);

	if ((p->spec->cast->del = Dz1Str_dup(buf, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_cast_cmp(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	char buf[1024];
	sprintf(buf, "(%s)", t->v);

	if ((p->spec->cast->cmp = Dz1Str_dup(buf, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_cast_dump(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	char buf[1024];
	sprintf(buf, "(%s)", t->v);

	if ((p->spec->cast->dump = Dz1Str_dup(buf, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error new_memory(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->spec->mem = PublishMemFuncSpec_new(FALSE, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_memory_error(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if (strcmp(t->v, "include") == 0)
		p->spec->mem->allocNeedErrorPtr = TRUE;
	else p->spec->mem->allocNeedErrorPtr = FALSE;

	return err;
}

static Dz1Error set_memory_malloc(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->mem->malloc);

	return err;
}

static Dz1Error set_memory_calloc(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->mem->calloc);

	return err;
}

static Dz1Error set_memory_free(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->mem->free);

	return err;
}

static Dz1Error set_memory_cancel(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->mem->cancel);

	return err;
}

static Dz1Error new_postfix(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->spec->postFix = PublishPostFix_new(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error fix_postfix_len(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	PublishPostFix_lengthFix(p->spec->postFix);

	return err;
}

static Dz1Error set_postfix_new(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_new);

	return err;
}

static Dz1Error set_postfix_gen(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_gen);

	return err;
}

static Dz1Error set_postfix_purge(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_purge);

	return err;
}

static Dz1Error set_postfix_del(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_del);

	return err;
}

static Dz1Error set_postfix_delAndSetNull(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_delAndSetNull);

	return err;
}

static Dz1Error set_postfix_dump(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_dump);

	return err;
}

static Dz1Error set_postfix_fdump(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_fdump);

	return err;
}

static Dz1Error set_postfix_cmp(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_cmp);

	return err;
}

static Dz1Error set_postfix_clone(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_clone);

	return err;
}

static Dz1Error set_postfix_copy(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_copy);

	return err;
}

static Dz1Error set_postfix_enc(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_enc);

	return err;
}

static Dz1Error set_postfix_dec(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->spec->postFix->_dec);

	return err;
}

static Dz1Error new_normal_array(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->arraySpec = p->spec->arraySpec[ArrayType_normal] = PublishArraySpec_new(NULL, FALSE, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error new_ordered_array(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->arraySpec = p->spec->arraySpec[ArrayType_ordered] = PublishArraySpec_new(NULL, TRUE, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error new_unique_array(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->arraySpec = p->spec->arraySpec[ArrayType_unique] = PublishArraySpec_new(NULL, TRUE, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_array_name(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->arraySpec->name);

	return err;
}

static Dz1Error set_array_travelFuncCast(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	char buf[1024];
	sprintf(buf, "(%s)", t->v);

	if ((p->arraySpec->travelFuncCast = Dz1Str_dup(buf, &err)) == NULL) ERR_OUT(&err);

	return err;
}

/*
static struct ArraySpecApiTypeMap
{
	ArraySpecApiType type;
	str_t name;
} ArraySpecApiTypeMap[] =
{
	{ ArraySpecApiType_new,				"new" },
	{ ArraySpecApiType_purge,			"purge" },
	{ ArraySpecApiType_del,				"del" },
	{ ArraySpecApiType_delAndSetNull,	"delAndSetNull" },
//	{ ArraySpecApiType_dump,			"dump" },
	{ ArraySpecApiType_clone,			"clone" },
	{ ArraySpecApiType_add,				"add" },
	{ ArraySpecApiType_remove,			"remove" },
	{ ArraySpecApiType_travelForward,	"travelForward" },
	{ ArraySpecApiType_travelBackward,	"travelBackward" },
	{ ArraySpecApiType_cnt,				"count" },
	{ ArraySpecApiType_extract,			"extract" },
	{ ArraySpecApiType_find,			"find" },
	{ ArraySpecApiType_gethead,			"gethead" },
	{ ArraySpecApiType_gettail,			"gettail" },
	{ ArraySpecApiType_max,				NULL },
};

static ArraySpecApiType ArraySpecCallTypeFromStr(str_t str)
{
	struct ArraySpecApiTypeMap *i;
	for (i = ArraySpecApiTypeMap; i->name; i++)
		if (strcmp(i->name, str) == 0) break;
	return i->type;
}
*/

static Dz1Error set_array_map_type(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	if ((p->arrayEntryType = ArraySpecApiTypeFromStr(t->v)) == ArraySpecApiType_max) ERR_SET_OUT(&err, EINVAL);
	else p->arrayEntry.type = ArraySpecCallType_func;

	return err;
}

static Dz1Error add_array_map(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	PublishSpecParserEnv *env = (PublishSpecParserEnv *)param;
	PublishArraySpec *arraySpec = env->arraySpec;
	PublishArraySpecApiMap *arrayEntry = &env->arrayEntry;

	// void *temp = (void *)-1; // modified by gm 20230602 - unused var temp

//	if ((err = arraySpec->addMap(arraySpec, env->arrayEntryType, arrayEntry->type, arrayEntry->name)).code) ERR_OUT(&err);
	if (arraySpec->addMap(arraySpec, env->arrayEntryType, arrayEntry->type, arrayEntry->name, errp) == FALSE) ERR_OUT(&err);
	else
	{ 
		Dz1Str_delAndSetNull(&arrayEntry->name);
		Dz1Error_set(errp, 0);
	}

	return err;
}

static Dz1Error set_array_map_name(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	tValTake(p->arrayEntry.name);

	return err;
}

static Dz1Error set_array_map_method(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	p->arrayEntry.type = ArraySpecCallType_method;

	return err;
}

static Dz1Error add_header_include(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	char buf[1024];
	sprintf(buf, "%s.h", t->v);

	if ((err = p->spec->regHeaderInc(p->spec, buf)).code) ERR_OUT(&err);

	return err;
}

static Dz1Error add_source_include(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	char buf[1024];
	sprintf(buf, "%s.h", t->v);

	if ((err = p->spec->regSourceInc(p->spec, buf)).code) ERR_OUT(&err);

	return err;
}

static Dz1Error PublishSpec_emiterInit(void *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (0) { }
	else if ((err = Dz1Parser_addEmiter(p, "new_spec", new_spec)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_spec_pthread", set_spec_pthread)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_primitive_name", set_primitive_name)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_primitive_pointer", set_primitive_pointer)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_primitive_native", set_primitive_native)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "concat_primitive_native", concat_primitive_native)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_primitive_prefix", set_primitive_prefix)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_primitive_attr", set_primitive_attr)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "add_primitive", add_primitive)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "new_basic", new_basic)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_basic_cpplink", set_basic_cpplink)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_basic_dllport", set_basic_dllport)).code) { ERR_OUT(&err); }

	else if ((err = Dz1Parser_addEmiter(p, "set_basic_printf", set_basic_printf)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_basic_printfA", set_basic_printfA)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_basic_printfW", set_basic_printfW)).code) { ERR_OUT(&err); }

	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_tprintf", set_baseic_tprintf)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_tprintfA", set_baseic_tprintfA)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_tprintfW", set_baseic_tprintfW)).code) { ERR_OUT(&err); }

	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_fprintf", set_baseic_fprintf)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_fprintfA", set_baseic_fprintfA)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_fprintfW", set_baseic_fprintfW)).code) { ERR_OUT(&err); }

	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_ftprintf", set_baseic_ftprintf)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_ftprintfA", set_baseic_ftprintfA)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_baseic_ftprintfW", set_baseic_ftprintfW)).code) { ERR_OUT(&err); }

	else if ((err = Dz1Parser_addEmiter(p, "new_error", new_error)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_error_type", set_error_type)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_error_default", set_error_default)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "new_error_entry", new_error_entry)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "add_error_entry", add_error_entry)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_error_entry_name", set_error_entry_name)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_err_entry_ptr", set_err_entry_ptr)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "new_cast", new_cast)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_cast_del", set_cast_del)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_cast_cmp", set_cast_cmp)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_cast_dump", set_cast_dump)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "new_memory", new_memory)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_memory_error", set_memory_error)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_memory_malloc", set_memory_malloc)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_memory_calloc", set_memory_calloc)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_memory_free", set_memory_free)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_memory_cancel", set_memory_cancel)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "new_postfix", new_postfix)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "fix_postfix_len", fix_postfix_len)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_new", set_postfix_new)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_gen", set_postfix_gen)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_purge", set_postfix_purge)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_del", set_postfix_del)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_delAndSetNull", set_postfix_delAndSetNull)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_dump", set_postfix_dump)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_fdump", set_postfix_fdump)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_cmp", set_postfix_cmp)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_clone", set_postfix_clone)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_copy", set_postfix_copy)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_enc", set_postfix_enc)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_postfix_dec", set_postfix_dec)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "new_normal_array", new_normal_array)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "new_ordered_array", new_ordered_array)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "new_unique_array", new_unique_array)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_array_name", set_array_name)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_array_travelFuncCast", set_array_travelFuncCast)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_array_map_type", set_array_map_type)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "add_array_map", add_array_map)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_array_map_name", set_array_map_name)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "set_array_map_method", set_array_map_method)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "add_header_include", add_header_include)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Parser_addEmiter(p, "add_source_include", add_source_include)).code) { ERR_OUT(&err); }

	return err;
}

/*
 * j8yykkkpwwi <- copy and paste in command mode
static Dz1Error (Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSpecParserEnv *p = (PublishSpecParserEnv *)param;

	return err;
}

*/

void *PublishSpecParser_new(Dz1Error *err)
{
	void *p = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((p = Dz1Parser_new(errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&p);

		if ((*errp = PublishSpec_emiterInit(p)).code) { ERR_OUT(errp); }
		else if ((*errp = Dz1ParserInit_parse(p, syntax)).code) { ERR_OUT(errp); }
//		else Dz1Parser_dump( p, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Parser_delAndSetNull, (void *)&p);
	}
	return p;
}

PublishSpec *PublishSpecParser_proc(void *parser, str_t text, Dz1Error *err)
{
	PublishSpec *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishSpecParserEnv env =
	{
		NULL,
		{
			NULL,					// name
			NULL,					// native
			FALSE,					// storage
			NULL					// api prefix
		},
		NULL,
		NULL,
		NULL,
		ArraySpecApiType_max,
		{
			ArraySpecCallType_func,
			NULL
		}
	};
	
	pthread_cleanup_push((Dz1DelFunc)PublishSpecParserEnv_clean, (void *)&env);

	if ((*errp = Dz1Parser_prepare(parser, text)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Parser_process(parser, "main", &env, 0)).code)
	{
		Dz1Thread_printf("Expression Compile Fail (line %d)\n", Dz1Parser_getLineNum(parser) + 1);
		ERR_OUT(errp);
	}
	else { ret = env.spec; env.spec = NULL; }

	pthread_cleanup_pop(1); // ((Dz1DelFunc)PublishSpecParserEnv_clean, (void *)&env);
	return ret;
}
