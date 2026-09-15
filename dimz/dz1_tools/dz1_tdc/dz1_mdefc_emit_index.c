#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

///////////////////////////////////////////////////////////////////////////////
// Index
static Dz1Error new_index(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *env = (Dz1MdefcParserEnv *)param;

	if (env->obj) ObjectInfo_del(env->obj);

	if ((env->obj = ObjectInfo_new(ObjectType_index, NULL, NULL, OBJECT_API_BASE, NULL, &err)) == NULL) ERR_OUT(&err);
	else if ((env->obj->info = IndexInfo_new(INDEX_API_BASE, NULL, NULL, FALSE, FALSE, env->indexUnique, &err)) == NULL) ERR_OUT(&err);
	else env->arrayType = ArrayType_normal;

	return err;
}

static Dz1Error set_index_unique(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *env = (Dz1MdefcParserEnv *)param;

	env->indexUnique = TRUE;

	return err;
}

static Dz1Error set_index_api(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	IndexInfo *info = (IndexInfo *)p->obj->info;

//	Dz1Thread_printf("set_array_api() : %s\n", t->v);
	if (0) { }
	else if (strcmp(t->v, "gethead") == 0) info->indexApi |= ARRAY_API_GETHEAD;
	else if (strcmp(t->v, "gettail") == 0) info->indexApi |= ARRAY_API_GETTAIL;
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}
static Dz1Error set_index_ref(Dz1ParserToken *t, void *param)
{	// &
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	IndexInfo *info = (IndexInfo *)p->obj->info;

	info->isReferenced = TRUE;

	return err;
}

static Dz1Error set_index_forward(Dz1ParserToken *t, void *param)
{	// union | struct | enum
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	IndexInfo *info = (IndexInfo *)p->obj->info;

	if (strcmp(t->v, "struct") == 0) info->isForward = FORWARD_TYPE_STRUCT;
	else if (strcmp(t->v, "union") == 0) info->isForward = FORWARD_TYPE_UNION;
	else if (strcmp(t->v, "enum") == 0) info->isForward = FORWARD_TYPE_ENUM;
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}

static Dz1Error set_index_entry(Dz1ParserToken *t, void *param)
{	// element type
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *arr_obj = NULL;
	ObjectInfo *elem_obj = NULL;
	IndexInfo *info = NULL;

	if ((arr_obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((info = (IndexInfo *)arr_obj->info) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((info->entry = elem_obj = Dz1MdefcParserEnv_getObject(p, t->v, info->isForward, &err)) == NULL)
	{
		Dz1Thread_printf("set_index_entry() : No Such type %s\n", t->v);
		ERR_SET_OUT(&err, ESRCH);
	}
	else 
	{
		Dz1Error_set(errp, 0);
		if (elem_obj->type == ObjectType_reference) info->isForward = TRUE;
	}

	return err;
}

static Dz1Error add_index_key(Dz1ParserToken *t, void *param)
{	// (ket1, key2, ... )
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	IndexInfo *info = (IndexInfo *)p->obj->info;

	if ((*errp = IndexInfoKey_appendName(&info->keys, t->v)).code) ERR_OUT(errp);

	return err;
}

static Dz1Error set_index_dump(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *arr_obj = NULL;
	ObjectInfo *elem_obj = NULL;
	IndexInfo *info = NULL;
	
	if ((arr_obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((info = (IndexInfo *)arr_obj->info) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Str_isVoid(t->v))
	{
		if ((info->dumpPrefix = (str_t)Dz1Calloc(sizeof(char), 1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		info->dumpPrefix = t->v; t->v = NULL;
		Dz1Error_set(errp, 0);
	}

	//Dz1Thread_printf("@@@ Array Entry is "); ObjectInfo_dump(obj, 0);
	//Dz1Thread_printf("\n");

	return err;
}
// Index
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitIndex(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_index",			new_index)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_index_unique",	set_index_unique)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_index_api",		set_index_api)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_index_ref",		set_index_ref)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_index_forward",	set_index_forward)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_index_entry",		set_index_entry)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "add_index_key",		add_index_key)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_index_dump",		set_index_dump)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
