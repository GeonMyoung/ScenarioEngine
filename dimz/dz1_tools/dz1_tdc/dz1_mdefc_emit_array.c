#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

///////////////////////////////////////////////////////////////////////////////
// Array
static Dz1Error new_array(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *env = (Dz1MdefcParserEnv *)param;
	u32_t list_mode_api = (env->arrayType == ArrayType_ordered || env->arrayType == ArrayType_unique) ? ARRAY_API_REMOVE : 0;

	if (env->obj) ObjectInfo_del(env->obj);

	if ((env->obj = ObjectInfo_new(ObjectType_array, NULL, NULL, OBJECT_API_BASE, NULL, &err)) == NULL) ERR_OUT(&err);
	else if ((env->obj->info = ArrayInfo_new(ARRAY_API_BASE | list_mode_api, NULL, NULL, FALSE, FALSE, env->arrayType, &err)) == NULL) ERR_OUT(&err);
	else env->arrayType = ArrayType_normal;

	return err;
}

static Dz1Error set_array_unique(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (strcmp(t->v, "unique") == 0) p->arrayType = ArrayType_unique;
	else if (strcmp(t->v, "ordered") == 0) p->arrayType = ArrayType_ordered;

	return err;
}


static Dz1Error set_array_api(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	ArrayInfo *info = (ArrayInfo *)p->obj->info;
	if (0) { }
	else if (strcmp(t->v, "count") == 0)
	{
		Dz1Thread_printf("@@@ array type api \"count\" is deprecated. this type always support \"count\"\n");
		info->arrayApi |= ARRAY_API_COUNT;
	}
	else if (strcmp(t->v, "remove") == 0)	info->arrayApi |= ARRAY_API_REMOVE;
	else if (strcmp(t->v, "extract") == 0)	info->arrayApi |= ARRAY_API_EXTRACT;
	else if (strcmp(t->v, "find") == 0)		info->arrayApi |= ARRAY_API_FIND;
	else if (strcmp(t->v, "gethead") == 0)	info->arrayApi |= ARRAY_API_GETHEAD;
	else if (strcmp(t->v, "gettail") == 0)	info->arrayApi |= ARRAY_API_GETTAIL;
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}
static Dz1Error set_array_ref(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	ArrayInfo *info = (ArrayInfo *)p->obj->info;

	info->isReferenced = TRUE;
	p->obj->api |= OBJECT_API_CLONE;

	return err;
}

static Dz1Error set_array_forward(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	ArrayInfo *info = (ArrayInfo *)p->obj->info;

	if (strcmp(t->v, "struct") == 0) info->isForward = FORWARD_TYPE_STRUCT;
	else if (strcmp(t->v, "union") == 0) info->isForward = FORWARD_TYPE_UNION;
	else if (strcmp(t->v, "enum") == 0) info->isForward = FORWARD_TYPE_ENUM;
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}

static Dz1Error set_array_entry(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *arr_obj = NULL;
	ObjectInfo *elem_obj = NULL;
	ArrayInfo *info = NULL;
	
	if ((arr_obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((info = (ArrayInfo *)arr_obj->info) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((info->entry = elem_obj = Dz1MdefcParserEnv_getObject(p, t->v, info->isForward, &err)) == NULL)
	{
		Dz1Thread_printf("set_array_entry() : No Such type %s\n", t->v);
		ERR_SET_OUT(errp, ESRCH);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (elem_obj->type == ObjectType_reference) info->isForward = TRUE;
	}

	//Dz1Thread_printf("@@@ Array Entry is "); ObjectInfo_dump(obj, 0);
	//Dz1Thread_printf("\n");

	return err;
}

static Dz1Error set_array_dump(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *arr_obj = NULL;
	ObjectInfo *elem_obj = NULL;
	ArrayInfo *info = NULL;
	
	if ((arr_obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((info = (ArrayInfo *)arr_obj->info) == NULL) ERR_SET_OUT(errp, EFAULT);
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
// Array
///////////////////////////////////////////////////////////////////////////////


bool_t Dz1MdefcEmiter_InitArray(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_array",			new_array)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_array_unique",	set_array_unique)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_array_api",		set_array_api)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_array_ref",		set_array_ref)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_array_forward",	set_array_forward)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_array_entry",		set_array_entry)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_array_dump",		set_array_dump)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
