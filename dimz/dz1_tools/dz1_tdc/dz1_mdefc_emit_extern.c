#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

///////////////////////////////////////////////////////////////////////////////
// Extern & Referenced
static Dz1Error new_extern(Dz1ParserToken *t, void *param)
{	// for extern type
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->obj) ObjectInfo_del(p->obj);

	if ((p->obj = ObjectInfo_new(ObjectType_extern, t->v, NULL, OBJECT_API_BASE, NULL, &err)) == NULL) ERR_OUT(&err);
	else if ((p->obj->info = ExternInfo_new(p->boolean, NULL, t->v, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error new_reference(Dz1ParserToken *t, void *param)
{	// for reference type
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->obj) ObjectInfo_del(p->obj);

	if ((p->obj = ObjectInfo_new(ObjectType_reference, t->v, NULL, OBJECT_API_BASE, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		char temp[1024] = { 0, };
		sprintf(temp, "struct %s", t->v);
		if ((p->obj->info = ExternInfo_new(p->boolean, NULL, temp, NULL, &err)) == NULL) ERR_OUT(&err);
	}

	return err;
}

static Dz1Error set_extern_cons(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	p->boolean = (bool_t)ExternInfoStatic_construct;

	return err;
}

static Dz1Error set_extern_flag(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (strcmp(t->v, "static") == 0 || strcmp(t->v, "simple") == 0)	p->boolean = (bool_t)ExternInfoStatic_primitive;
	else if (strcmp(t->v, "ptr") == 0)								p->boolean = (bool_t)ExternInfoStatic_primitive_ptr;
	else if (strcmp(t->v, "union") == 0)							p->boolean = (bool_t)ExternInfoStatic_typical_union;
	else if (strcmp(t->v, "struct") == 0)							p->boolean = (bool_t)ExternInfoStatic_construct;
	else p->boolean = TRUE;

	return err;
}

static Dz1Error add_module_incl(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ExternInfo *info = (ExternInfo *)p->obj->info;

	if (p->module->findModule(p->module, t->v) == NULL)
	{
		Dz1MdefcModule *module;
		if ((module = Dz1MdefcModule_new(t->v, "tdc", p->spec, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1MdefcModule_del, module);

			module->includeStatus = ModuleIncludeStatus_natived;
			if ((err = p->module->addModule(p->module, module)).code) ERR_OUT(&err);

			pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1MdefcModule_del, module);
		}
	}

	tValTake(info->module_name);

	return err;
}

static Dz1Error add_module_ref(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ExternInfo *info = (ExternInfo *)p->obj->info;

	if (p->module->findModule(p->module, t->v) == NULL)
	{
		Dz1MdefcModule *module;
		if ((module = Dz1MdefcModule_new(t->v, "tdc", p->spec, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1MdefcModule_del, module);

			module->includeStatus = ModuleIncludeStatus_referenced;
			if ((err = p->module->addModule(p->module, module)).code) ERR_OUT(&err);

			pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1MdefcModule_del, module);
		}
	}

	tValTake(info->module_name);
	return err;
}

static Dz1Error set_extern_info(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	ExternInfo *info = (ExternInfo *)p->obj->info;

	tValTake(info->prefix);

	return err;
}
// Extern & Referenced
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitExtern(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_extern", new_extern)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_reference", new_reference)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_extern_cons", set_extern_cons)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_extern_flag", set_extern_flag)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "add_module_incl", add_module_incl)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "add_module_ref",  add_module_ref)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_extern_info", set_extern_info)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
