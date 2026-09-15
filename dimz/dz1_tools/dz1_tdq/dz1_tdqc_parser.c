#include <dz1_parser.h>
#include <dz1_parser_init.h>
#include <Dz1ParserUtil.h>

#include <dz1_tdq.h>
#include <dz1_tdq_var_def_util.h>
#include <dz1_tdq_qry_def_util.h>
#include "dz1_tdqc_util.h"
#include "dz1_tdqc_parser.h"

#define My_PARSER_ENV_ID				0

typedef struct MyParserEnv
{
	Dz1TdqcTarget			*dst;
	Dz1ParserUtilPathArr	*incs;

	Dz1TdqcShape			*shp;
	Dz1TdqIndexEntry		*idx;
	Dz1TdqColumn			*col;		// is ref

	Dz1TdqcTblInstance		*tbl;
	Dz1TdqFKEntry			*fk;
	Dz1TdqNameList			*names;

	Dz1TdqcQuery			*query;
	Dz1TdqQueryTblName		*qtbl;		// is ref
	Dz1TdqQueryTblEntry		*qjoin;
	Dz1TdqQryColumn			*qcol;
} MyParserEnv;

static bool_t MyParserEnv_init(MyParserEnv *dst, Dz1TdqcArg *arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((dst->incs = Dz1ParserUtilPathArr_new(arg->mod_inc_path, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static void MyParserEnv_cleanup(MyParserEnv *p)
{
	if (p == NULL) return;
	Dz1ParserUtilPathArr_delAndSetNull(&p->incs);
	Dz1TdqcShape_delAndSetNull(&p->shp);
	Dz1TdqIndexEntry_delAndSetNull(&p->idx);
	Dz1TdqcTblInstance_delAndSetNull(&p->tbl);
	Dz1TdqFKEntry_delAndSetNull(&p->fk);
	Dz1TdqNameList_delAndSetNull(&p->names);
	Dz1TdqcQuery_delAndSetNull(&p->query);
	Dz1TdqQueryTblEntry_delAndSetNull(&p->qjoin);
	Dz1TdqQryColumn_delAndSetNull(&p->qcol);
}

static str_t syntax =
"main					=	<ModuleLoad> [<Includes>] [<ElementsDefine>]+ <done>;\n"
"\n"
"ModuleLoad				=	load module <ModuleName> [<ModuleNameMore>]* <semicolon>;\n"
"ModuleName				=	<symbol>=module_load ;\n"
"ModuleNameMore			=	<comma> <symbol>=module_load;\n"
"\n"
"Includes				=	include <IncludeName> [<IncludeNameMore>]* <semicolon>;\n"
"IncludeName			=	<symbol>=include_add;\n"
"IncludeNameMore		=	<comma> <symbol>=include_add;\n"
"\n"
"ElementsDefine			=	<TableShapeDefine>|<TableInstanceDefine>|<QueryDefine>;\n"
"\n"
"TableShapeDefine		=	shape define <symbol>=shp_create <liststart> <ShapeDefineOpt> <listend> <symbol>=shp_append <semicolon>;\n"
"ShapeDefineOpt			=	<ShapeSourceOpt> <ShapeLoadOpt> [<ShapeIndexOpt>];\n"
"ShapeSourceOpt			=	build from <symbol>=shp_set_source [<ShapeSourceMembOpts>] <semicolon>;\n"
"ShapeSourceMembOpts	=	<liststart> [<ShapeSourceMembOpt>]+ <listend>;\n"
"ShapeLoadOpt			=	load to <symbol>=shp_set_dst <semicolon>;\n"
"\n"
"ShapeSourceMembOpt		=	<symbol>=shp_find_member <equal> <ShapeMemberParam> <semicolon>;\n"
"ShapeMemberParam		=	<ShapeMemberSizeParam>|<ShapeMemberTimeParam>|<ShapeDefaultParam>|<ShapeMemberManualParam>;\n"
"ShapeMemberSizeParam	=	size <lbracket> <number>=shp_opt_size <rbracket>;\n"
"ShapeMemberTimeParam	=	ymd|hms|stamp=shp_opt_time;\n"
"ShapeDefaultParam		=	default <lbracket> <string>=shp_opt_default <rbracket>;\n"
"ShapeMemberManualParam	=	manual <lbracket> <symbol>=shp_opt_db_type [<ShapeMemberMParamOpt>] <rbracket>;\n"
"ShapeMemberMParamOpt	=	<comma> <symbol>=shp_opt_iof;\n"
"\n"
"ShapeIndexOpt			=	index <symbol>=shp_index_create <lbracket>=memb_enum_create <MemberNameEnumerate>=shp_index_take <rbracket> [unique=shp_index_unique] <semicolon>=shp_index_append ;\n"
"\n"
"TableInstanceDefine	=	table define <symbol>=tbl_create [<TableInstanceBody>] <symbol>=tbl_set_name as <symbol>=tbl_set_prefix <semicolon>=tbl_append;\n"
"TableInstanceBody		=	<liststart> [<TableInstanceOpt>]* <listend>;\n"
"TableInstanceOpt		=	foreign key <symbol>=tbl_fk_create <lbracket>=memb_enum_create <MemberNameEnumerate>=tbl_fk_take <rbracket> <equal>\n"
"										<at>|<symbol>=tbl_fk_set_peer [<PeerIndexName>] [<ForeignKeyOpt>] <semicolon>=tbl_fk_append;\n"
"PeerIndexName			=	<lbracket> <symbol>=tbl_fk_set_peer_idx <rbracket>;\n"
"ForeignKeyOpt			=	<colon> <lbracket> <symbol>=tbl_fk_update <comma> <symbol>=tbl_fk_delete <rbracket>;\n"
"\n"
"MemberNameEnumerate	=	<symbol>=memb_enum_append [<MemberNameEnumerateMore>]*;\n"
"MemberNameEnumerateMore=	<comma> <symbol>=memb_enum_append;\n"
"\n"
"QueryDefine			=	query define <symbol>=query_create <liststart> <QuerySource> [<QueryColumn>] <listend> <symbol>=query_append <semicolon>;\n"
"QuerySource			=	source=qtbl_bias_create <symbol>=qtbl_bias_name_create [<QuerySourceAlias>] [<QuerySourceJoinList>] <semicolon>;\n"
"QuerySourceJoinList	=	with <liststart> [<QuerySourceJoin>]+ <listend>;\n"
"QuerySourceJoin		=	join left|right|inner|outer=qtbl_join_create <symbol>=qtbl_join_name_create [<QuerySourceAlias>] on <string>=qtbl_join_match <semicolon>=qtbl_join_append;\n"
"QuerySourceAlias		=	as <symbol>=qtblname_alias;\n"
"\n"
"QueryColumn			=	column=qrow_create from <symbol>=qrow_source <liststart> [<QueryColumnMap>]+ <listend> to <symbol>=qrow_dest <semicolon>;\n"
"QueryColumnMap			=	<symbol>=qcol_create <equal> <QueryColumnSpec>=qcol_append <semicolon>;\n"
"QueryColumnSpec		=	<QueryColumnSpecRef>|<QueryColumnSpecExpr>;\n"
"QueryColumnSpecRef		=	<symbol>=qcol_set_ref [<QueryColumnSpecRefMore>];\n"
"QueryColumnSpecRefMore	=	<dot> <symbol>=qcol_ref_fix;\n"
"QueryColumnSpecExpr	=	<at> <lbracket> <string>=qcol_set_expr <rbracket> [<QueryColumnSpecManual>];\n"
"QueryColumnSpecManual	=	manual <lbracket> <symbol>=qcol_opt_type <comma> <symbol>=qcol_opt_iof <rbracket>;\n"
"\n";

static Dz1Error module_load(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR fn[1024] = { 0, };
	Dz1MdefcModule *module = NULL;

	Dz1ParserUtilPathArr *incs = NULL;
	Dz1TdqcTarget *dst = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((incs = env->incs) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = Dz1FileName_concatNameExt(Dz1ArrParam(char, fn), t->v, Dz1Text("tdo") )).code) ERR_OUT(errp);
	else if ((module = Dz1MdefcModule_iload(incs->arr, incs->cnt, fn, errp)) == NULL)
	{
		ERR_OUT(errp);
	}
	else
	{
		pthread_cleanup_push(Dz1MdefcModule_delAndSetNull, (void *)&module);
		if ((*errp = dst->src->add(dst->src, module)).code) ERR_OUT(errp);
		else
		{
			module = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MdefcModule_delAndSetNull, (void *)&module);
	}
	return err;
}

static Dz1Error include_add(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTarget *dst = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1TdqNameList_appendName(dst->incs, t->v, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->shp != NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((env->shp = Dz1TdqcShape_new(t->v, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_append(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcShape *shp = NULL;
	Dz1TdqcTarget *dst = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp = env->shp) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1STRCMP(shp->name, t->v) != 0)
	{
		Dz1Thread_printf("Name Mismatch %s != %s\n", shp->name, t->v);
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = dst->shapes->add(dst->shapes, env->shp)).code) ERR_OUT(errp);
	else
	{
		Dz1TdqcOrderList_appendShp(dst->ord, env->shp, NULL);
		env->shp = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _member_is_array(void *ptr, StructMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (StructMemberEntry_isArray(p))
	{
		bool_t *flag = (bool_t *)ptr;
		*flag = TRUE;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

static bool_t _struct_has_array_memb(StructureInfo *info)
{
	bool_t ret = FALSE;
	info->members->travel(info->members, _member_is_array, (void *)&ret);
	return ret;
}

static Dz1Error shp_set_source(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *obj = NULL, *ori = NULL;
	Dz1TdqcShape *shp = NULL;
	Dz1TdqcTarget *dst = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp = env->shp) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp->src_obj = obj = Dz1MdefcModuleList_findObject(dst->src, t->v)) == NULL)
	{
		Dz1Thread_printf("Object %s not found\n", t->v);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if ((ori = ObjectInfo_getOrigin(obj)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (ori->type != ObjectType_structure)
	{
		Dz1Thread_printf("Object %s is not structure\n", t->v);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if (_struct_has_array_memb((StructureInfo *)ori->info))
	{
		Dz1Thread_printf("Object %s has array type member\n", t->v);
		ERR_SET_OUT(errp, EPERM);
	}
	else if ((shp->target = Dz1TdqTblShape_genFromObj(shp->name, shp->src_obj, shp->memb_opt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_set_dst(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *obj = NULL, *ori = NULL;
	Dz1TdqcShape *shp = NULL;
	Dz1TdqcTarget *dst = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp = env->shp) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp->dst_obj = obj = Dz1MdefcModuleList_findObject(dst->src, t->v)) == NULL)
	{
		Dz1Thread_printf("Object %s not found\n", t->v);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if ((ori = ObjectInfo_getOrigin(obj)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (ori->type != ObjectType_array)
	{
		Dz1Thread_printf("Object %s is not array\n", t->v);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_find_member(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqTblShape *shape = NULL;
	Dz1TdqcShape *shp = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp = env->shp) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shape = shp->target) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((env->col = Dz1TdqRow_findByName(shape->row, t->v)) == NULL)
	{
		Dz1Thread_printf("%s is not found in %s\n", t->v, shape->name);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_opt_size(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqColumn *col = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((col = env->col) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		s64_t v = (s64_t)Dz1StrTo64(t->v);
		if (Dz1TdqSqlTypeSpec_setSizeOpt(col->sql_type, v, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1TdqSqlTypeSpecPresent _str_type_to_present(Dz1Str v)
{
	Dz1TdqSqlTypeSpecPresent ret = Dz1TdqSqlTypeSpecPresent_stamp;
	if (0) { }
	else if (Dz1STRCMP(v, Dz1Text("ymd")) == 0) ret = Dz1TdqSqlTypeSpecPresent_ymd;
	else if (Dz1STRCMP(v, Dz1Text("hms")) == 0) ret = Dz1TdqSqlTypeSpecPresent_hms;
	return ret;
}

static Dz1Error shp_opt_time(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqSqlTypeSpec *type = NULL;
	Dz1TdqColumn *col = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((col = env->col) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((type = col->sql_type) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (_category_of(type->present) != 0x03)
	{
		Dz1Thread_printf("%s is not time type\n", col->name);
		ERR_SET_OUT(errp, EINVAL);
	}
	else
	{
		type->present = _str_type_to_present(t->v);
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_opt_default(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqNullOpt *null_opt = NULL;
	Dz1TdqColumn *col = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((col = env->col) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((null_opt = Dz1TdqNullOpt_new(NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		null_opt->dflt_val = t->v; t->v = NULL;
		Dz1TdqNullOpt_delAndSetNull(&col->null_opt);
		col->null_opt = null_opt;
	}
	return err;
}

static Dz1Error shp_opt_db_type(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqSqlTypeSpec *sql_type = NULL;
	Dz1TdqType type = Dz1TdqType_max;
	Dz1TdqColumn *col = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((col = env->col) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((type = Dz1TdqTypeFromStr(t->v)) == Dz1TdqType_max)
	{
		Dz1Thread_printf("Unknown type %s\n", t->v);
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((sql_type = Dz1TdqSqlTypeSpec_new(type, NULL, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1TdqSqlTypeSpec_delAndSetNull(&col->sql_type);
		col->sql_type = sql_type;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_opt_iof(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcShapeOptEntry *opt = NULL;
	Dz1TdqcShape *shp = NULL;
	Dz1TdqColumn *col = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((col = env->col) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp = env->shp) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((opt = Dz1TdqcShapeOptList_findByName(shp->memb_opt, col->name)) != NULL)
	{
		Dz1Str_delAndSetNull(&opt->api_prefix);
		opt->api_prefix = t->v;
		t->v = NULL;
	}
	else if (Dz1TdqcShapeOptList_appendOpt(shp->memb_opt, col->name, t->v, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_index_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqIndexEntry *idx = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->idx != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((env->idx = idx = Dz1TdqIndexEntry_new(t->v, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqIndexEntry_delAndSetNull, (void *)&env->idx);
		if ((idx->own_cols = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqIndexEntry_delAndSetNull, (void *)&env->idx);
	}
	return err;
}

static Dz1Error shp_index_unique(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqIndexEntry *idx = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((idx = env->idx) == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		idx->unique = TRUE;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error shp_index_take(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqTblShape *shape = NULL;
	Dz1TdqcShape *shp = NULL;
	Dz1TdqNameList *names = NULL;
	Dz1TdqIndexEntry *idx = NULL;
	Dz1TdqRowRef *idx_cols = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((shp = env->shp) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shape = shp->target) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((idx = env->idx) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((idx_cols = idx->own_cols) == NULL) 
	{
		ERR_SET_OUT(errp, EFAULT);
	}

	else if ((names = env->names) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (names->count(names) == 0)
	{
		Dz1Thread_printf("No Index member : %s\n", idx->suffix_name);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1TdqNameEntry *e = NULL;
		while(errp->code == 0 && (e = names->getHead(names)) != NULL)
		{
			names->extract(names, e);
			pthread_cleanup_push(Dz1TdqNameEntry_delAndSetNull, (void *)&e);
			if (Dz1TdqRowRef_addCol(idx_cols, e->name, shape->row, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1TdqNameEntry_delAndSetNull, (void *)&e);
		}
	}
	return err;
}

static Dz1Error shp_index_append(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqIndexList *shp_idx = NULL;
	Dz1TdqTblShape *shape = NULL;
	Dz1TdqcShape *shp = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((shp = env->shp) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shape = shp->target) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp_idx = shape->indexes) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if (env->idx == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = shp_idx->add(shp_idx, env->idx)).code) ERR_OUT(errp);
	else
	{
		env->idx = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error tbl_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTblInstance *tbl = NULL;
	Dz1TdqcTarget *dst = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (env->tbl != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((env->tbl = tbl = Dz1TdqcTblInstance_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((tbl->shape = Dz1TdqcShapeList_findByName(dst->shapes, t->v)) == NULL)
	{
		Dz1Thread_printf("Shape %s is not found\n", t->v);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1Thread_printf("Table Create From %s\n", t->v);
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error tbl_set_name(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTblInstance * tbl = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((tbl = env->tbl) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		tbl->name = t->v; t->v = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error tbl_set_prefix(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTblInstance * tbl = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((tbl = env->tbl) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		tbl->prefix = t->v; t->v = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}


static Dz1Error tbl_append(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTblInstance * tbl = NULL;
	Dz1TdqcTarget *dst = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((tbl = env->tbl) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1TdqcTarget_appendTbl(dst, env->tbl, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1TdqcOrderList_appendTbl(dst->ord, env->tbl, NULL);
		env->tbl = NULL;
		Dz1Error_set(errp, 0);
		Dz1Thread_printf("@@@ Table Appended = %s\n", tbl->name);
	}
	return err;
}

static Dz1Error tbl_fk_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqFKEntry *fk = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->fk != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((env->fk = fk = Dz1TdqFKEntry_new(t->v, NULL, NULL, Dz1TdqForeignKeyMode_cascade, Dz1TdqForeignKeyMode_cascade, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqFKEntry_delAndSetNull, (void *)&env->fk);
		if ((fk->own_cols = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf("Foreign Key : %s\n", t->v);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqFKEntry_delAndSetNull, (void *)&env->fk);
	}
	return err;
}

static Dz1Error tbl_fk_set_peer(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqFKEntry *fk = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((fk = env->fk) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (t->t == DZ1_PARSER_TOKEN_AT)
	{
		fk->peer_tbl = (Dz1TdqTblInstance *)env->tbl;
		Dz1Error_set(errp, 0);
	}
	else if ((fk->peer_tbl = (Dz1TdqTblInstance *)Dz1TdqcTarget_findTableByName(env->dst, t->v)) == NULL)
	{
		Dz1Thread_printf("Reference Table %s is not found\n", t->v);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1Thread_printf("Peer Table : %s\n", t->v);
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error tbl_fk_take(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqNameList *names = NULL;
	Dz1TdqcShape *shape = NULL;
	Dz1TdqcTblInstance *tbl = NULL;
	Dz1TdqFKEntry *fk = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((tbl = env->tbl) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shape = tbl->shape) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((fk = env->fk) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((names = env->names) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (names->count(names) == 0)
	{
		Dz1Thread_printf("No Reference Column selected : %s\n", fk->suffix_name);
		ERR_SET_OUT(errp, EINVAL);
	}
	else
	{
		Dz1TdqTblShape *shp = shape->target;
		Dz1TdqNameEntry *e = NULL;
		while((e = names->getHead(names)) != NULL)
		{
			names->extract(names, e);
			pthread_cleanup_push(Dz1TdqNameEntry_delAndSetNull, (void *)&e);
			Dz1Thread_printf("FK Column : %s\n", e->name);

			if (Dz1TdqRowRef_addCol(fk->own_cols, e->name, shp->row, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1TdqNameEntry_delAndSetNull, (void *)&e);
		}
	}
	return err;
}

static Dz1Error tbl_fk_append(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTblInstance *tbl = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((tbl = env->tbl) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = tbl->fks->add(tbl->fks, env->fk)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf("FK Appended : %s\n", env->fk->suffix_name);
		env->fk = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error tbl_fk_update(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqFKEntry *fk = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((fk = env->fk) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((fk->on_update = Dz1TdqForeignKeyModeFromStr(t->v)) == Dz1TdqForeignKeyMode_max)
	{
		Dz1Thread_printf("%s is unknown\n", t->v);
		ERR_SET_OUT(errp, EINVAL);
	}
	else
	{
		Dz1Thread_printf("FK On Update: %s\n", t->v);
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error tbl_fk_delete(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqFKEntry *fk = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((fk = env->fk) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((fk->on_delete = Dz1TdqForeignKeyModeFromStr(t->v)) == Dz1TdqForeignKeyMode_max)
	{
		Dz1Thread_printf("%s is unknown\n", t->v);
		ERR_SET_OUT(errp, EINVAL);
	}
	else
	{
		Dz1Thread_printf("FK On Delete: %s\n", t->v);
		Dz1Error_set(errp, 0);
	}
	return err;
}


static Dz1Error tbl_fk_set_peer_idx(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqIndexEntry *idx = NULL;
	Dz1TdqcShape *shp = NULL;
	Dz1TdqTblShape *shape = NULL;
	Dz1TdqcTblInstance *tbl = NULL;
	Dz1TdqFKEntry *fk = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((fk = env->fk) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((tbl = (Dz1TdqcTblInstance *)fk->peer_tbl) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shp = tbl->shape) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((shape = shp->target) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((idx = Dz1TdqIndexList_findBySuffix(shape->indexes, t->v)) == NULL)
	{
		Dz1Thread_printf("Index %s not found in %s\n", t->v, tbl->name);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if (idx->unique == FALSE)
	{
		Dz1Thread_printf("Index %s not found in %s does not unique\n", t->v, tbl->name);
		ERR_SET_OUT(errp, EINVAL);
	}
	else
	{
		fk->peer_idx_suffix_opt = t->v;
		t->v = NULL;
		Dz1Thread_printf("FK Peer Index : %s\n", fk->peer_idx_suffix_opt);
		Dz1Error_set(errp, 0);
	}
	return err;
}


static Dz1Error memb_enum_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqNameList *names = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((names = Dz1TdqNameList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqNameList_delAndSetNull(&env->names);
		env->names = names;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error memb_enum_append(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqNameList *names = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((names = env->names) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1TdqNameList_appendName(names, t->v, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1TdqcQuery *Dz1TdqcQuery_create(Dz1Str name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcQuery *ret = Dz1TdqcQuery_new(name, NULL, NULL, NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcQuery_delAndSetNull, (void *)&ret);
		if ((ret->from = Dz1TdqQueryTblSpec_new(NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqcQuery_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error query_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->query != NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((env->query = Dz1TdqcQuery_create(t->v, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static bool_t _register_query_shape(Dz1TdqcTarget *dst, Dz1TdqcQuery *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ObjectInfo *src_obj = src->src_obj;
	Dz1TdqcShape *node = NULL;
	if ((node = Dz1TdqcShapeList_findByName(dst->shapes, src_obj->name)) != NULL)
	{
		if (node->src_obj != src->src_obj || node->dst_obj != src->dst_obj)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Different source or destination %s<->%s\n", src->name, node->name);
			ERR_SET_OUT(errp, EFAULT);
		}
		else 
		{
			Dz1Error_set(errp, 0);
		}
	}
	else if ((node = Dz1TdqcShape_new(src_obj->name, src_obj, src->dst_obj, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcShape_delAndSetNull, (void *)&node);
		node->is_qurty_shape = TRUE;
//		if ((node->target = Dz1TdqTblShape_genFromObj(node->name, node->src_obj, node->memb_opt, errp)) == NULL) ERR_OUT(errp);
		if ((node->target = Dz1TdqTblShape_genFromRef(node->name, node->src_obj, src->sel, node->memb_opt, dst->shapes, errp)) == NULL)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Shape generation fail : %s\n", node->name);
			ERR_OUT(errp);
		}
		else if ((*errp = dst->shapes->add(dst->shapes, node)).code) ERR_OUT(errp);
		else
		{
			Dz1TdqcOrderList_appendShp(dst->ord, node, NULL);
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqcShape_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error query_append(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTarget *dst = NULL;
	Dz1TdqcShape *shp = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->query == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (_register_query_shape(dst, env->query, errp) == FALSE) ERR_OUT(errp);
	else if ((*errp = dst->queries->add(dst->queries, env->query)).code) ERR_OUT(errp);
	else
	{
		Dz1TdqcOrderList_appendQry(dst->ord, env->query, NULL);
		env->query = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qtbl_bias_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQueryTblSpec *from = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((from = query->from) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (from->basis != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((from->basis = Dz1TdqQueryTblName_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		env->qtbl = from->basis;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qtbl_bias_name_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTarget *dst = NULL;
	Dz1TdqQueryTblName *basis = NULL;
	Dz1TdqQueryTblSpec *from = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((from = query->from) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((basis = from->basis) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((basis->instance = (Dz1TdqTblInstance *)Dz1TdqcTblInstanceList_findByName(dst->tables, t->v)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qtbl_join_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQueryTblJoin mode = Dz1TdqQueryTblJoin_max;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->qjoin != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((mode = Dz1TdqQueryTblJoinFromStrA(t->v)) == Dz1TdqQueryTblJoin_max) ERR_SET_OUT(errp, EINVAL);
	else if ((env->qjoin = Dz1TdqQueryTblEntry_new(NULL, mode, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qtbl_join_name_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTarget *dst = NULL;
	Dz1TdqQueryTblName *tblname = NULL;
	Dz1TdqQueryTblEntry *qjoin = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qjoin = env->qjoin) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qjoin->tbl = tblname = Dz1TdqQueryTblName_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((tblname->instance = (Dz1TdqTblInstance *)Dz1TdqcTblInstanceList_findByName(dst->tables, t->v)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		env->qtbl = tblname;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qtbl_join_match(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQueryTblEntry *qjoin = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qjoin = env->qjoin) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		qjoin->match_on = t->v;
		t->v = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qtbl_join_append(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
//	Dz1TdqQueryTblEntry *qjoin = NULL;
	Dz1TdqQueryTblSpec *from = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->qjoin == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((from = query->from) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = from->join_tbls->add(from->join_tbls, env->qjoin)).code) ERR_OUT(errp);
	else
	{
		env->qjoin = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qtblname_alias(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQueryTblName *qtbl = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qtbl = env->qtbl) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		qtbl->alias = t->v;
		t->v = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qrow_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query->sel = Dz1TdqQryRow_new(errp)) == NULL) ERR_OUT(errp);
	else 
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qrow_source(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTarget *dst = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query->src_obj = Dz1MdefcModuleList_findObject(dst->src, t->v)) == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Can't find object %s\n", t->v);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qrow_dest(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcTarget *dst = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query->dst_obj = Dz1MdefcModuleList_findObject(dst->src, t->v)) == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Unknown Object = %s\n", t->v);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static bool_t _is_exist_memb(ObjectInfo *obj, Dz1Str instance, Dz1Error *errp)
{
	ObjectInfo *ori = ObjectInfo_getOrigin(obj);
	if (ori->type != ObjectType_structure) ERR_SET_OUT(errp, EINVAL);
	else
	{
		StructureInfo *info = (StructureInfo *)ori->info;
		if (info->members->find(info->members, instance) == NULL) ERR_SET_OUT(errp, ENOENT);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error qcol_create(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQryRow *sel = NULL;
	ObjectInfo *obj = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((obj = query->src_obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((sel = query->sel) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->qcol != NULL) ERR_SET_OUT(errp, EFAULT);
	else if (_is_exist_memb(obj, t->v, errp) == FALSE)
	{
		Dz1Thread_printf("%s in not exist in %s\n", t->v, obj->name);
		ERR_OUT(errp);
	}
	else if ((env->qcol = Dz1TdqQryColumn_new(sel->count(sel), NULL, t->v, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static bool_t qcol_append_prechk(Dz1TdqQryColumn *qcol, Dz1TdqcQuery *query, Dz1TdqcTarget *dst, Dz1Error *errp)
{
	Dz1TdqQryCol *src = qcol->src;
	if (src->present == Dz1TdqQryColPresent_tcol)
	{
		Dz1TdqQryTblCol		*tcol	= src->x.tcol;
		Dz1TdqQueryTblName	*tn		= tcol->tbl;
		Dz1TdqTblInstance	*tbl	= tn->instance;
		Dz1TdqTblShape		*shp	= tbl->shape;
		Dz1TdqcShape		*shape	= Dz1TdqcShapeList_findByName(dst->shapes, shp->name);
		if (shape != NULL)
		{
			Dz1TdqTblShape *tdq_shape = shape->target;
			Dz1TdqRow *row = tdq_shape->row;
			if (Dz1TdqRow_findByName(row, tcol->col_name) == NULL)
			{
				Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! column name '%s' is not found in shape '%s'\n", tcol->col_name, tbl->name);
				ERR_SET_OUT(errp, EINVAL);
			}
			else
			{
				Dz1TdqcShapeOptEntry *opt = Dz1TdqcShapeOptList_findByName(shape->memb_opt, tcol->col_name);
				if (opt != NULL && Dz1TdqcShapeOptList_appendOpt(query->memb_opt, qcol->alias, opt->api_prefix, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error qcol_append(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQryRow *sel = NULL;
	Dz1TdqcQuery *query = NULL;
	Dz1TdqcTarget *dst = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if (env->qcol == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((sel = query->sel) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if (qcol_append_prechk(env->qcol, query, dst, errp) == FALSE) ERR_OUT(errp);
	else if ((*errp = sel->add(sel, env->qcol)).code)
	{
		ERR_OUT(errp);
	}
	else
	{
		env->qcol = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qcol_set_ref(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQueryTblSpec *from = NULL;
	Dz1TdqQryTblCol *tcol = NULL;
	Dz1TdqQryCol *src = NULL;
	Dz1TdqQryColumn *qcol = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((from = query->from) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qcol = env->qcol) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qcol->src = src = Dz1TdqQryCol_new( Dz1TdqQryColPresent_tcol, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((src->x.tcol = Dz1TdqQryTblCol_new(from->basis, t->v, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qcol_ref_fix(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQueryTblSpec *from = NULL;
	Dz1TdqQryTblCol *tcol = NULL;
	Dz1TdqQryCol *src = NULL;
	Dz1TdqQryColumn *qcol = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((from = query->from) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qcol = env->qcol) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((src = qcol->src) == NULL) ERR_OUT(errp);
	else if ((tcol = src->x.tcol) == NULL) ERR_OUT(errp);
	else if ((tcol->tbl = Dz1TdqQueryTblSpec_findTbl(from, tcol->col_name)) == NULL) 
	{
		Dz1Thread_printf("!!! tcol not found = ");Dz1TdqQryTblCol_dump(tcol, 0);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1Str_delAndSetNull(&tcol->col_name);
		tcol->col_name = t->v;
		t->v = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1TdqSqlTypeSpec *_resolve_and_gen_type(ObjectInfo *src_obj, Dz1Str instance, Dz1TdqcShapeOptList *opts, Dz1Error *errp)
{
	ObjectInfo *ori = ObjectInfo_getOrigin(src_obj);
	StructureInfo *info = (StructureInfo *)ori->info;
	StructMemberEntry *memb = info->members->find(info->members, instance);
	Dz1TdqcShapeOptEntry *opt = NULL;
	Dz1TdqSqlTypeSpec *ret = Dz1TdqSqlTypeSpec_genFromInfo(memb, &opt, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
		if (opt != NULL && (*errp = opts->add(opts, opt)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error qcol_set_expr(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqQueryTblSpec *from = NULL;
	Dz1TdqQryExprCol *ecol = NULL;
	Dz1TdqQryCol *src = NULL;
	Dz1TdqQryColumn *qcol = NULL;
	Dz1TdqcQuery *query = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((from = query->from) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qcol = env->qcol) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qcol->src = src = Dz1TdqQryCol_new( Dz1TdqQryColPresent_ecol, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((src->x.ecol = ecol = Dz1TdqQryExprCol_new(NULL, t->v, errp)) == NULL) ERR_OUT(errp);
	else if ((ecol->type = _resolve_and_gen_type(query->src_obj, qcol->alias, query->memb_opt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error qcol_opt_type(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqSqlTypeSpec *sql_type = NULL;
	Dz1TdqQryCol *src = NULL;
	Dz1TdqQryExprCol *ecol = NULL;
	Dz1TdqQryColumn *qcol = NULL;
	Dz1TdqSqlTypeSpecPresent type;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((type = Dz1TdqSqlTypeSpecPresentFromStrA(t->v)) == Dz1TdqSqlTypeSpecPresent_max) ERR_SET_OUT(errp, EINVAL);
	else if ((qcol = env->qcol) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((src = qcol->src) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (src->present != Dz1TdqQryColPresent_ecol) ERR_SET_OUT(errp, EINVAL);
	else if ((ecol = src->x.ecol) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((sql_type = Dz1TdqSqlTypeSpec_new(type, NULL, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1TdqSqlTypeSpec_delAndSetNull(&ecol->type);
		ecol->type = sql_type;
		Dz1Error_set(errp, 0);
	}
	return err;
}


static Dz1Error qcol_opt_iof(Dz1ParserToken *t, void *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcShapeOptEntry *opt = NULL;
	Dz1TdqcQuery *query = NULL;
	Dz1TdqQryColumn *qcol = NULL;
	MyParserEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, My_PARSER_ENV_ID);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (MyParserEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((qcol = env->qcol) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((query = env->query) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((opt = Dz1TdqcShapeOptList_findByName(query->memb_opt, qcol->alias)) != NULL)
	{
		Dz1Str_delAndSetNull(&opt->api_prefix);
		opt->api_prefix = t->v;
		t->v = NULL;
	}
	else if (Dz1TdqcShapeOptList_appendOpt(query->memb_opt, qcol->alias, t->v, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return err;
}

#define EMITTER_ENTRY(name)			{ #name, name }
static Dz1ParserUtilEmitterInfo __emitter_table__[] =
{
	EMITTER_ENTRY(module_load),
	EMITTER_ENTRY(include_add),
	EMITTER_ENTRY(shp_create),
	EMITTER_ENTRY(shp_append),
	EMITTER_ENTRY(shp_set_source),
	EMITTER_ENTRY(shp_set_dst),
	EMITTER_ENTRY(shp_find_member),
	EMITTER_ENTRY(shp_opt_size),
	EMITTER_ENTRY(shp_opt_time),
	EMITTER_ENTRY(shp_opt_default),
	EMITTER_ENTRY(shp_opt_db_type),
	EMITTER_ENTRY(shp_opt_iof),
	EMITTER_ENTRY(shp_index_create),
	EMITTER_ENTRY(shp_index_unique),
	EMITTER_ENTRY(shp_index_take),
	EMITTER_ENTRY(shp_index_append),
	EMITTER_ENTRY(tbl_create),
	EMITTER_ENTRY(tbl_set_name),
	EMITTER_ENTRY(tbl_set_prefix),
	EMITTER_ENTRY(tbl_append),
	EMITTER_ENTRY(tbl_fk_create),
	EMITTER_ENTRY(tbl_fk_take),
	EMITTER_ENTRY(tbl_fk_set_peer),
	EMITTER_ENTRY(tbl_fk_append),
	EMITTER_ENTRY(tbl_fk_set_peer_idx),
	EMITTER_ENTRY(tbl_fk_update),
	EMITTER_ENTRY(tbl_fk_delete),
	EMITTER_ENTRY(memb_enum_create),
	EMITTER_ENTRY(memb_enum_append),
	EMITTER_ENTRY(query_create),
	EMITTER_ENTRY(query_append),
	EMITTER_ENTRY(qtbl_bias_create),
	EMITTER_ENTRY(qtbl_bias_name_create),
	EMITTER_ENTRY(qtbl_join_create),
	EMITTER_ENTRY(qtbl_join_name_create),
	EMITTER_ENTRY(qtbl_join_match),
	EMITTER_ENTRY(qtbl_join_append),
	EMITTER_ENTRY(qtblname_alias),
	EMITTER_ENTRY(qrow_create),
	EMITTER_ENTRY(qrow_source),
	EMITTER_ENTRY(qrow_dest),
	EMITTER_ENTRY(qcol_create),
	EMITTER_ENTRY(qcol_append),
	EMITTER_ENTRY(qcol_set_ref),
	EMITTER_ENTRY(qcol_ref_fix),
	EMITTER_ENTRY(qcol_set_expr),
	EMITTER_ENTRY(qcol_opt_type),
	EMITTER_ENTRY(qcol_opt_iof),
	Dz1ParserUtilEmitterInfoLast
};

Dz1Error Dz1Tdqc_parse(Dz1TdqcTarget *dst, str_t src_text, Dz1TdqcArg *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MyParserEnv user_env = { dst, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	if (MyParserEnv_init(&user_env, arg, errp) == FALSE) ERR_OUT(errp);
	else
	{
		void *parser = NULL;
		pthread_cleanup_push(MyParserEnv_cleanup, (void *)&user_env);
		if ((parser = Dz1Parser_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			// Dz1ParserIPv4Env ipv4env;
			// Dz1ParserTcpListenAddrEnv listenAddrEnv;
			Dz1ParserUtilEnvEntry parse_env[] =
			{
			//	Dz1ParserIPv4Env_entry(&ipv4env),
			//	Dz1ParserTcpListenAddrEnv_entrp(&listenAddrEnv),
				{ My_PARSER_ENV_ID, &user_env },
				Dz1ParserEnvEntryLast
			};

			pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&parser);

			if ((*errp = Dz1ParserUtilEnv_check(parse_env)).code) ERR_OUT(errp);
			else if ((*errp = Dz1ParserUtil_addEmitter(parser, __emitter_table__)).code) ERR_OUT(errp);
			else if ((*errp = Dz1ParserInit_parse(parser, syntax)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Parser_prepare(parser, src_text)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Parser_process(parser, "main", (void *)parse_env, 0)).code)
			{
				Dz1Thread_printf("Dz1Tdq_parse() : Parse Fail at %u line\n", Dz1Parser_getLineNum(parser));
				ERR_OUT(errp);
			}
			pthread_cleanup_pop(1); // (Dz1Parser_delAndSetNull, (void *)&parser);
		}
		pthread_cleanup_pop(1); // (MyParserEnv_cleanup, (void *)&user_env);
	}
	return err;
}
