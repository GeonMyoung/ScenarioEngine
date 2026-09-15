#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

static Dz1Error set_api_windows(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	Dz1Thread_printf(Dz1T("%s is WINDWOS Only\n"), ObjectInfo_nameOf(p->obj));
	p->obj->api |= OBJECT_API_WINDOWS_ONLY;

	return err;
}

static bool_t _set_obj_api_alternate(Dz1ParserToken *t, Dz1MdefcParserEnv *p)
{
	bool_t ret = TRUE;
	if (0) { }
	else if (strcmp(t->v, "usernew") == 0)		p->obj->api |=  (OBJECT_API_NEW | OBJECT_API_USER_NEW);
	else if (strcmp(t->v, "usergen") == 0)		p->obj->api |=  (OBJECT_API_GEN | OBJECT_API_USER_GEN);
	else if (strcmp(t->v, "userdel") == 0)		p->obj->api |=  (OBJECT_API_DEL | OBJECT_API_USER_DEL);

	else ret = FALSE;

	return ret;
}

/*
static bool_t _set__obj_api(Dz1ParserToken *t, Dz1MdefcParserEnv *p)
{
	bool_t ret = TRUE;
	if (0) { }
	else ret = FALSE;
	return ret;
}
*/
static bool_t _set_obj_api_foundation(Dz1ParserToken *t, Dz1MdefcParserEnv *p)
{
	bool_t ret = TRUE;
	if (0) { }
	else if (strcmp(t->v, "clone") == 0)		p->obj->api |= OBJECT_API_CLONE;
	else if (strcmp(t->v, "compare") == 0)		p->obj->api |= OBJECT_API_CMP;

	else if (strcmp(t->v, "dump") == 0)			p->obj->api |= OBJECT_API_DUMP;
	else if (strcmp(t->v, "dumpA") == 0)		p->obj->api |= (OBJECT_API_DUMP | OBJECT_API_DUMP_MBCS);
	else if (strcmp(t->v, "dumpW") == 0)		p->obj->api |= (OBJECT_API_DUMP | OBJECT_API_DUMP_WIDE);
	else if (strcmp(t->v, "dumpX") == 0)		p->obj->api |= (OBJECT_API_DUMP | OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE);

	else if (strcmp(t->v, "fdump") == 0)		p->obj->api |= OBJECT_API_FDUMP;
	else if (strcmp(t->v, "fdumpA") == 0)		p->obj->api |= (OBJECT_API_FDUMP | OBJECT_API_DUMP_MBCS);
	else if (strcmp(t->v, "fdumpW") == 0)		p->obj->api |= (OBJECT_API_FDUMP | OBJECT_API_DUMP_WIDE);
	else if (strcmp(t->v, "fdumpX") == 0)		p->obj->api |= (OBJECT_API_FDUMP | OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE);
	else ret = FALSE;
	return ret;
}

static bool_t _set_obj_api_rejectable(Dz1ParserToken *t, Dz1MdefcParserEnv *p)
{
	bool_t ret = TRUE;
	if (0) { }
	else if (strcmp(t->v, "nonew") == 0)		p->obj->api &= ~(OBJECT_API_NEW | OBJECT_API_USER_NEW);
	else if (strcmp(t->v, "nogen") == 0)		p->obj->api &= ~(OBJECT_API_GEN | OBJECT_API_USER_GEN);
	else if (strcmp(t->v, "nodel") == 0)		p->obj->api &= ~(OBJECT_API_DEL | OBJECT_API_USER_DEL);
	else ret = FALSE;
	return ret;
}

static bool_t _set_obj_api_optional(Dz1ParserToken *t, Dz1MdefcParserEnv *p)
{
	bool_t ret = TRUE;
	if (0) { }
	else if (strcmp(t->v, "userclone") == 0)	p->obj->api |= (OBJECT_API_CLONE | OBJECT_API_USER_CLONE);

	else if (strcmp(t->v, "usercmp") == 0)		p->obj->api |= (OBJECT_API_CMP | OBJECT_API_USER_CMP);

	else if (strcmp(t->v, "userdump") == 0)		p->obj->api |= (OBJECT_API_DUMP | OBJECT_API_USER_DUMP);
	else if (strcmp(t->v, "userdumpA") == 0)	p->obj->api |= (OBJECT_API_DUMP | OBJECT_API_USER_DUMP | OBJECT_API_DUMP_MBCS);
	else if (strcmp(t->v, "userdumpW") == 0)	p->obj->api |= (OBJECT_API_DUMP | OBJECT_API_USER_DUMP | OBJECT_API_DUMP_WIDE);
	else if (strcmp(t->v, "userdumpX") == 0)	p->obj->api |= (OBJECT_API_DUMP | OBJECT_API_USER_DUMP | OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE);

	else if (strcmp(t->v, "userfdump") == 0)	p->obj->api |= (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP);
	else if (strcmp(t->v, "userfdumpA") == 0)	p->obj->api |= (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP | OBJECT_API_DUMP_MBCS);
	else if (strcmp(t->v, "userfdumpW") == 0)	p->obj->api |= (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP | OBJECT_API_DUMP_WIDE);
	else if (strcmp(t->v, "userfdumpX") == 0)	p->obj->api |= (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP | OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE);

	else ret = FALSE;
	return ret;
}

static Dz1Error set_api_basic_obj(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	p = p;				// modified by gm 20231020 -- unused value p;
	if (0) { }
	else if (_set_obj_api_foundation(t, param) == TRUE) Dz1Error_set(errp, 0);
	else
	{
		Dz1Thread_printf(Dz1T("set_api_basic_obj() : Unknown API %s\n"), t->v);
		ERR_SET_OUT(errp, EINVAL);
	}

	return err;
}

static Dz1Error set_api_struct_obj(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	p = p;				// modified by gm 20231020 -- unused value p;
	if (0) { }
	else if (_set_obj_api_alternate(t, param) == TRUE) Dz1Error_set(errp, 0);
	else if (_set_obj_api_rejectable(t, param) == TRUE) Dz1Error_set(errp, 0);
	else if (_set_obj_api_foundation(t, param) == TRUE) Dz1Error_set(errp, 0);
	else if (_set_obj_api_optional(t, param) == TRUE) Dz1Error_set(errp, 0);
	else
	{
		Dz1Thread_printf(Dz1T("set_api_struct_obj() : Unknown API %s\n"), t->v);
		ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}

static Dz1Error set_api_union_obj(Dz1ParserToken *t, void *param)
{	// basic + "presentcmp"
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (0) { }
	else if (_set_obj_api_alternate(t, param) == TRUE) Dz1Error_set(errp, 0);
	else if (_set_obj_api_rejectable(t, param) == TRUE) Dz1Error_set(errp, 0);
	else if (_set_obj_api_foundation(t, param) == TRUE) Dz1Error_set(errp, 0);
	else if (_set_obj_api_optional(t, param) == TRUE) Dz1Error_set(errp, 0);
	// union only
	else if (strcmp(t->v, "presentcmp") == 0)
	{
		UnionInfo *info = (UnionInfo *)p->obj->info;
		p->obj->api |= OBJECT_API_CMP;
		info->comparePresentOnly = TRUE;
		Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1Thread_printf(Dz1T("set_api_union_obj() : Unknown API %s\n"), t->v);
		ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}

static Dz1Error set_api_array_obj(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *obj = NULL;
	ArrayInfo *info = NULL;
	if ((obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((info = (ArrayInfo *)obj->info) == NULL) ERR_SET_OUT(errp, EFAULT);
	// array only
	else if (strcmp(t->v, "dump") == 0)
	{
		if (info->arrayApi & (ARRAY_API_USER_DUMP | ARRAY_API_NO_DUMP)) ERR_SET_OUT(errp, EEXIST);
		else info->arrayApi |= (ARRAY_API_USER_DUMP | ARRAY_API_NO_DUMP);
	}
	else if (strcmp(t->v, "nodump") == 0)
	{
		if (info->arrayApi & (ARRAY_API_USER_DUMP | ARRAY_API_NO_DUMP)) ERR_SET_OUT(errp, EEXIST);
		else info->arrayApi |= ARRAY_API_NO_DUMP;
	}
	else if (strcmp(t->v, "userdump") == 0)
	{
		if (info->arrayApi & (ARRAY_API_USER_DUMP | ARRAY_API_NO_DUMP)) ERR_SET_OUT(errp, EEXIST);
		else info->arrayApi |= ARRAY_API_USER_DUMP;
	}
	//////////////////////////////////////////////////////
	else if (strcmp(t->v, "fdump") == 0)
	{
		if (info->arrayApi & (ARRAY_API_USER_FDUMP | ARRAY_API_NO_FDUMP)) ERR_SET_OUT(errp, EEXIST);
		else info->arrayApi |= (ARRAY_API_USER_FDUMP | ARRAY_API_NO_FDUMP);
	}
	else if (strcmp(t->v, "nofdump") == 0)
	{
		if (info->arrayApi & (ARRAY_API_USER_FDUMP | ARRAY_API_NO_FDUMP)) ERR_SET_OUT(errp, EEXIST);
		else info->arrayApi |= ARRAY_API_NO_FDUMP;
	}
	else if (strcmp(t->v, "userfdump") == 0)
	{
		if (info->arrayApi & (ARRAY_API_USER_FDUMP | ARRAY_API_NO_FDUMP)) ERR_SET_OUT(errp, EEXIST);
		else info->arrayApi |= ARRAY_API_USER_FDUMP;
	}
	else
	{
		Dz1Thread_printf(Dz1T("set_api_array_obj() : Unknown API %s\n"), t->v);
		ERR_SET_OUT(&err, EINVAL);
	}
	return err;
}

bool_t Dz1MdefcEmiter_InitApi(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_api_windows", set_api_windows)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_api_basic_obj", set_api_basic_obj)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_api_struct_obj", set_api_struct_obj)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_api_union_obj", set_api_union_obj)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_api_array_obj", set_api_array_obj)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
