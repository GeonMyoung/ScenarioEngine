#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

///////////////////////////////////////////////////////////////////////////////
// Macro
static u16_t macro_idx = 0;
static Dz1Error new_macro(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	
	if (p->obj) ObjectInfo_del(p->obj);
	
	if ((p->obj = ObjectInfo_new(ObjectType_macro, NULL, NULL, 0, NULL, &err)) == NULL) ERR_OUT(&err);
	else Dz1Error_set(errp, 0);
	
	return err;
}

static Dz1Error set_macro_type(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *obj = NULL;
	if ((obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Error_set(errp, 0);
		if (0) { }
		else if (strcmp(t->v, "define") == 0)	obj->api = 0x0004;
		else if (strcmp(t->v, "ifdef") == 0)	obj->api = 0x0001;
		else if (strcmp(t->v, "ifndef") == 0)	obj->api = 0x0003;
	}
	return err;
}

static Dz1Error set_macro_name(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *obj = NULL;
	if ((obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		char buf[128];
		snprintf(buf, 127, "%s$%04X", t->v, macro_idx);
		if ((obj->name = Dz1StrA_dup(buf, errp)) == NULL) ERR_OUT(errp);
		else
		{
			macro_idx++;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error set_macro_name_from_stk(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *obj = NULL;
	Dz1MdefcMacroStack *stk = NULL;
	if ((obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((stk = p->macro_stk) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		char temp[128], *cp = NULL, buf[134];				// modified by gm 20231020 -- change the size of buf 
		strcpy(temp, stk->name);
		if ((cp = strchr(temp, '$')) != NULL) *cp = 0;

		snprintf(buf, sizeof(buf), "%s$%04X", temp, macro_idx);

		if ((obj->name = Dz1StrA_dup(buf, errp)) == NULL) ERR_OUT(errp);
		else
		{
			macro_idx++;
			Dz1Error_set(errp, 0);
			if (strcmp(t->v, "endif") == 0)			obj->api = 0x0002;
			else if (strcmp(t->v, "else") == 0)		obj->api = 0x0000;
		}
	}
	return err;
}

static Dz1Error oper_macro_stack(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *obj = NULL;
	Dz1MdefcMacroStack *node = NULL;
	if ((obj = p->obj) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1MdefcParserEnv_addObject(p, errp) == FALSE) ERR_OUT(errp);
	else if (obj->api & 0x0001)
	{	// push
		if ((node = Dz1MdefcMacroStack_new(obj->name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MdefcMacroStack_delAndSetNull, (void *)&node);
			if (Dz1MdefcMacroStack_push(&p->macro_stk, node, errp) == FALSE) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MdefcMacroStack_delAndSetNull, (void *)&node);
		}
	}
	else if (obj->api & 0x0002)
	{	// pop
		if ((node = Dz1MdefcMacroStack_pop(&p->macro_stk, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MdefcMacroStack_delAndSetNull, (void *)&node);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MdefcMacroStack_delAndSetNull, (void *)&node);
		}
	}
	return err;
}
// Macro
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitMacro(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_macro", new_macro)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_macro_type", set_macro_type)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_macro_name", set_macro_name)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_macro_name_from_stk", set_macro_name_from_stk)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "oper_macro_stack", oper_macro_stack)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
