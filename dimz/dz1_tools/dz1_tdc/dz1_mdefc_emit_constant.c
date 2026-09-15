#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

///////////////////////////////////////////////////////////////////////////////
// Constant Emitter
static Dz1Error new_constant(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	
	// Dz1Thread_printf("@@@ New Constant\n");

	if (p->obj) ObjectInfo_del(p->obj);
	
	if ((p->obj = ObjectInfo_new(ObjectType_constant, NULL, NULL, 0, NULL, &err)) == NULL) ERR_OUT(&err);
	else if ((p->obj->info = ConstantInfo_new(NULL, &err)) == NULL) ERR_OUT(&err);
	
	return err;
}

static Dz1Error set_constant_data(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	
	ObjectInfo *obj = p->obj;
	ConstantInfo *info = (ConstantInfo *)obj->info;

	if (t->t == DZ1_PARSER_TOKEN_STRING)
	{
		char *cp = NULL;
		size_t len = strlen(t->v);;
		if ((info->value = cp = Dz1Calloc(sizeof(char), len + 3, errp)) == NULL) ERR_OUT(errp);
		else
		{
			*cp++ = '\"';
			strcpy(cp, t->v); cp += len;
			*cp++ = '\"';
			*cp++ = 0;
		}
	}
	else
	{
		info->value = t->v;
		t->v = NULL;
	}
	// Dz1Thread_printf("@@@ Constant %s = %s\n", obj->name, info->value);

	return err;
}

static Dz1Error set_constant_data_expr(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	
	ObjectInfo *obj = p->obj;
	ConstantInfo *info = (ConstantInfo *)obj->info;

	info->value = t->v;
	t->v = NULL;

	return err;
}
// Constant Emitter
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitConstant(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_constant", new_constant)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_constant_data", set_constant_data)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_constant_data_expr", set_constant_data_expr)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
