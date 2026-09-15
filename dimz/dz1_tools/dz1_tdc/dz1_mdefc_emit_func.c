#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

///////////////////////////////////////////////////////////////////////////////
// Function
static Dz1Error new_func(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	
	if (p->obj) ObjectInfo_del(p->obj);
	
	if ((p->obj = ObjectInfo_new(ObjectType_func, NULL, NULL, OBJECT_API_BASE, NULL, &err)) == NULL) ERR_OUT(&err);
	else if ((p->obj->info = FunctionInfo_new(NULL, FALSE, FUNCTION_RET_FORWARD_NONE, &err)) == NULL) ERR_OUT(&err);
	else memset(&p->funcArg, 0, sizeof(FunctionArg));
	
	return err;
}

static Dz1Error set_func_ret_forward(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	FunctionInfo *info = (FunctionInfo *)p->obj->info;
	if (strcmp(t->v, "union") == 0)	info->retForward = FUNCTION_RET_FORWARD_UNION;
	else if (strcmp(t->v, "struct") == 0) info->retForward = FUNCTION_RET_FORWARD_STRUCT;
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}

static Dz1Error set_func_ret_type(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	
	ObjectInfo *obj = NULL;
	FunctionInfo *info = (FunctionInfo *)p->obj->info;

	if ((info->retType = obj = Dz1MdefcParserEnv_getObject(p, t->v, info->retForward != FUNCTION_RET_FORWARD_NONE, &err)) == NULL)
	{
		Dz1Thread_printf("set_func_ret_type() : No such object %s\n", t->v);
		ERR_SET_OUT(&err, ESRCH);
	}
	else if (obj->type == ObjectType_reference)
		info->retForward = TRUE;

	return err;
}

static Dz1Error set_func_ret_ptr(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	
	FunctionInfo *info = (FunctionInfo *)p->obj->info;
	
	info->retIsPointer++;
	
	return err;
}

static Dz1Error add_func_arg(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	
	FunctionInfo *info = (FunctionInfo *)p->obj->info;
	
	if ((err = info->args->add(info->args, p->funcArg.argType, p->funcArg.argForward, p->funcArg.argPtrCnt, p->funcArg.instance)).code) ERR_OUT(&err);
	else p->funcArg.argForward = 0;
	
	return err;
}

static Dz1Error set_func_arg_forward(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (strcmp(t->v, "union") == 0)	p->funcArg.argForward = FUNCTION_RET_FORWARD_UNION;
	else if (strcmp(t->v, "struct") == 0)	p->funcArg.argForward = FUNCTION_RET_FORWARD_STRUCT;
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}

static Dz1Error set_func_arg_type(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ObjectInfo *obj = NULL;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if ((p->funcArg.argType = obj = Dz1MdefcParserEnv_getObject(p, t->v, p->funcArg.argForward != FUNCTION_RET_FORWARD_NONE, &err)) == NULL)
	{
		Dz1Thread_printf("set_func_arg_type() : No such object %s\n", t->v);
		ERR_SET_OUT(&err, ESRCH);
	}
	else if (obj->type == ObjectType_reference)
		p->funcArg.argForward = TRUE;

	p->funcArg.argPtrCnt = 0;
	return err;
}

static Dz1Error inc_func_arg_ptr(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	p->funcArg.argPtrCnt++;

	return err;
}

static Dz1Error set_func_arg_instance(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	p->funcArg.instance = t->v;
	t->v = NULL;

	return err;
}
// Function
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitFunc(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_func", new_func)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_func_ret_forward", set_func_ret_forward)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_func_ret_type", set_func_ret_type)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_func_ret_ptr", set_func_ret_ptr)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "add_func_arg", add_func_arg)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_func_arg_forward", set_func_arg_forward)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_func_arg_type", set_func_arg_type)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "inc_func_arg_ptr", inc_func_arg_ptr)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_func_arg_instance", set_func_arg_instance)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
