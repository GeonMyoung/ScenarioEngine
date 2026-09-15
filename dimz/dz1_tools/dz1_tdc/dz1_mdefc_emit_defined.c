#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

///////////////////////////////////////////////////////////////////////////////
// Defined
static Dz1Error set_defined_forward(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (strcmp(t->v, "struct") == 0) p->definedForwarded = FORWARD_TYPE_STRUCT;
	else p->definedForwarded = FORWARD_TYPE_UNION;

	return err;
}

static Dz1Error new_defined(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->obj) ObjectInfo_del(p->obj);

	if ((p->obj = ObjectInfo_new(ObjectType_defined, NULL, NULL, OBJECT_API_NONE, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ObjectInfo *origin_obj = NULL;
		DefinedInfo *info = NULL;
		pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&p->obj);

		if ((p->obj->info = info = DefinedInfo_new(p->definedForwarded, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((info->origin = origin_obj = Dz1MdefcParserEnv_getObject(p, t->v, info->isForwarded, errp)) == NULL)
		{
			Dz1Thread_printf("new_defined() : No such object %s\n", t->v);
			ERR_SET_OUT(errp, ESRCH);
		}
		else
		{
			Dz1Error_set(errp, 0);
			if (origin_obj->type == ObjectType_reference) info->isForwarded = TRUE;
		}
		pthread_cleanup_pop(err.code); // (ObjectInfo_delAndSetNull, (void *)&p->obj);
	}

	return err;
}
// Defined
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitDefined(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_defined", new_defined)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_defined_forward", set_defined_forward)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
