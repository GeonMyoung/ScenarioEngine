#include <dz1_parser_init.h>
#include <Dz1ParserUtil.h>
#include "dz1_tjsonc_util.h"
#include "dz1_tjsonc_parser.h"
/*
JSON interface generate from "dz1_jsonTestDef.tdo"
{
	object MyComponent
}
*/

static str_t __syntax_str__ = ""
"Main				= JSON interface generate from <symbol>=module_load <liststart> <JsonObjectList> <listend>;\n"
"JsonObjectList		= [<JsonObject>]+;\n"
"JsonObject			= object <symbol>=obj_name_set [cascade=obj_add_cascade_set] <semicolon>=obj_add;\n"
//"JsonObjectMore		= <comma> <JsonObject>;"
"";

#define TJSONC_PARSE_ENV			0
static Dz1JsonCompilerEnv *Dz1JsonCompilerEnv_new(Dz1JsonCompilerArg *arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonCompilerEnv *ret = NULL;
	
	Dz1JsonCompileIncs *incs = NULL;
	Dz1JsonCompileIncSeq *inc_seq = NULL;
	if (arg == NULL || (incs = arg->src_module_inc) == NULL || (inc_seq = incs->seq) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1JsonCompilerEnv *)Dz1Calloc(sizeof(Dz1JsonCompilerEnv), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonCompilerEnv_delAndSetNull, (void *)&ret);
		if ((ret->incs = inc_seq->get_array(inc_seq, &ret->incs_cnt, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->objs = Dz1JsonTargetObjects_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1JsonCompilerEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1JsonCompilerEnv_del(Dz1JsonCompilerEnv *p)
{
	if (p != NULL)
	{
		Dz1MdefcModule_delAndSetNull(&p->src_module);
		Dz1Str_delAndSetNull(&p->module_name);
		if (p->incs) Dz1Free(p->incs);
		Dz1JsonTargetObjects_delAndSetNull(&p->objs);
		p->incs = NULL;
		Dz1Free(p);
	}
}

typedef struct TjsoncParseEnv
{
	Dz1JsonCompilerEnv			*c_env;
	ObjectInfo					*obj;					// is ref
	bool_t						 obj_add_cascade;
} TjsoncParseEnv;
static void TjsoncParseEnv_cleanup(void *ptr)
{
	TjsoncParseEnv *env = (TjsoncParseEnv *)ptr;
	if (env->c_env) Dz1JsonCompilerEnv_delAndSetNull(&env->c_env);
}

static Dz1Error module_load(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	TCHAR name_ext[2048] = { 0 };

	TjsoncParseEnv *env = NULL;
	Dz1JsonCompilerEnv *c_env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TJSONC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (TjsoncParseEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((c_env = env->c_env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (c_env->src_module != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((*errp = Dz1FileName_concatNameExt(Dz1ArrParam(TCHAR, name_ext), t->v, Dz1Text("tdo") )).code) ERR_OUT(errp);
	else if (c_env->module_name != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((c_env->src_module = Dz1MdefcModule_iload(c_env->incs, c_env->incs_cnt, name_ext, errp)) == NULL) ERR_OUT(errp);
	else
	{
		c_env->module_name = t->v; t->v = NULL;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error obj_name_set(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	TjsoncParseEnv *env = NULL;
	Dz1JsonCompilerEnv *c_env = NULL;
	Dz1MdefcModule *module = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TJSONC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (TjsoncParseEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((c_env = env->c_env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((module = c_env->src_module) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->obj != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((env->obj = module->findObject(module, t->v)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error obj_add_cascade_set(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	TjsoncParseEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TJSONC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (TjsoncParseEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->obj == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->obj_add_cascade = TRUE;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error obj_add(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	TjsoncParseEnv *env = NULL;
	Dz1JsonCompilerEnv *c_env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TJSONC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (TjsoncParseEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((c_env = env->c_env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->obj == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1JsonTargetObjects_append(c_env->objs, env->obj, env->obj_add_cascade, c_env->src_module, errp) == FALSE) ERR_OUT(errp);
	else
	{
		env->obj = NULL;
		env->obj_add_cascade = FALSE;
		Dz1Error_set(errp, 0);
	}
	return err;
}

#define EMITTER_ENTRY(name)			{ #name, name }
static Dz1ParserUtilEmitterInfo __emitter_table__[] =
{
	EMITTER_ENTRY(module_load),
	EMITTER_ENTRY(obj_name_set),
	EMITTER_ENTRY(obj_add_cascade_set),
	EMITTER_ENTRY(obj_add),
	Dz1ParserUtilEmitterInfoLast
};

Dz1JsonCompilerEnv *Dz1Tjsonc_parse(str_t src_text, Dz1JsonCompilerArg *args, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonCompilerEnv *ret = NULL;
	void *parser = Dz1Parser_new(errp);
	if (parser == NULL) ERR_OUT(errp);
	else
	{
		// Dz1ParserIPv4Env ipv4env;
		// Dz1ParserTcpListenAddrEnv listenAddrEnv;
		Dz1JsonCompilerEnv *c_env = NULL;
		TjsoncParseEnv user_env = { NULL, NULL, FALSE };
		Dz1ParserUtilEnvEntry parse_env[] =
		{
		//	Dz1ParserIPv4Env_entry(&ipv4env),
		//	Dz1ParserTcpListenAddrEnv_entrp(&listenAddrEnv),
			{ TJSONC_PARSE_ENV, &user_env },
			Dz1ParserEnvEntryLast
		};

		pthread_cleanup_push(TjsoncParseEnv_cleanup, (void *)&user_env);
		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&parser);

		if (0) { }
		else if ((user_env.c_env = c_env = Dz1JsonCompilerEnv_new(args, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1ParserUtilEnv_check(parse_env)).code) ERR_OUT(errp);
		else if ((*errp = Dz1ParserUtil_addEmitter(parser, __emitter_table__)).code) ERR_OUT(errp);
		else if ((*errp = Dz1ParserInit_parse(parser, __syntax_str__)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Parser_prepare(parser, src_text)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Parser_process(parser, "Main", (void *)parse_env, 0)).code)
		{
			Dz1Thread_printf("Dz1ParserHandle_parse() : Parse Fail at %u line\n", Dz1Parser_getLineNum(parser));
			ERR_OUT(errp);
		}
		else
		{
			ret = user_env.c_env;
			user_env.c_env = NULL;
		}
		pthread_cleanup_pop(1); // (TjsoncParseEnv_delAndSetNull, (void *)&parser);
		pthread_cleanup_pop(1); // (TodecParseEnv_cleanup, (void *)&user_env);
	}
	return ret;
}
