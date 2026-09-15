#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"
#include "dz1_mdefc_emit_util.h"

static void _struct_member_entry_cleanup(StructMemberEntry *p)
{
	p->isForwarded = 0;
	p->type = NULL;
	Dz1Str_delAndSetNull(&p->srcType);
	Dz1Str_delAndSetNull(&p->instance);
	Dz1Str_delAndSetNull(&p->arr_cnt_name);
	p->isPointer = FALSE;
	p->memb_flags = 0;
	p->dumpMode = MemberDumpMode_normal;
}

///////////////////////////////////////////////////////////////////////////////
// Structure
static Dz1Error new_struct(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->obj) ObjectInfo_del(p->obj);

	if ((p->obj = ObjectInfo_new(ObjectType_structure, NULL, NULL, OBJECT_API_BASE, NULL, &err)) == NULL) ERR_OUT(&err);
	else if ((p->obj->info = StructureInfo_new(&err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error set_struct_member_forward(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	_struct_member_entry_cleanup(&p->structEntry);

	if (0) { }
	else if (strcmp(t->v, "struct") == 0)	p->structEntry.isForwarded = FORWARD_TYPE_STRUCT;
	else if (strcmp(t->v, "union") == 0)	p->structEntry.isForwarded = FORWARD_TYPE_UNION;
	else									p->structEntry.isForwarded = FORWARD_TYPE_ENUM;

	return err;
}

static Dz1Error set_struct_member_type(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	StructMemberEntry *tgt = &p->structEntry;

	Dz1StrA_delAndSetNull(&tgt->srcType);
	tValTake(tgt->srcType);

	////////////////////////////////////////////////////
	// Setup member defaults
	p->structEntry.isPointer = FALSE;
	p->structEntry.memb_flags = MEMBER_FLAG_ARG_INVOLVE;	// all members are arguments
	p->structEntry.dumpMode = MemberDumpMode_normal;
	// Setup member defaults
	////////////////////////////////////////////////////

	return err;
}

static Dz1Error set_struct_member_pointer(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	p->structEntry.isPointer = TRUE;

	return err;
}

static Dz1Error set_struct_member_instance(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	StructMemberEntry *tgt = &p->structEntry;
	ObjectInfo *papa = p->obj;

	tValTake(p->structEntry.instance);

	return err;
}

static Dz1Error set_struct_member_array(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	p->structEntry.memb_flags |= MEMBER_FLAG_IS_ARRAY;

	return err;
}

static Dz1Error set_struct_member_array_cnt(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (t->t == DZ1_PARSER_TOKEN_STRING)
	{
		if (strstr(t->v, "$$") == 0)
		{
			Dz1ThreadA_printf("!!! End of array condition is invalid\n");
			ERR_SET_OUT(errp, EINVAL);
			return err;
		}
	}

	tValTake(p->structEntry.arr_cnt_name);

	return err;
}

static Dz1Error set_struct_member_array_ref(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	p->structEntry.memb_flags |= MEMBER_FLAG_IS_ARRAY_REF_ELEM;

	return err;
}

static Dz1Error add_struct_member(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	StructMemberEntry *tgt = &p->structEntry;

	ObjectInfo *papa = p->obj;
	StructureInfo *info = (StructureInfo *)papa->info;
	StructMemberList *dst_list = info->members;

	////////////////////////////////////////////////////
	// Resolve Member Type
	if (strcmp(papa->name, tgt->srcType) == 0)
	{	// Same name with parent type -> Check Previous Forwarded Entry
		ObjectInfo *o = NULL;
		if ((o = p->module->findUnknownObject(p->module, tgt->srcType, errp)) == NULL)
		{	// No previous Forwarded Definition -> OK
			tgt->type = p->obj; // Entry Type is Same as itself
			tgt->isForwarded = TRUE;
			tgt->memb_flags |= MEMBER_FLAG_IS_REFERENCED;
			Dz1Error_set(errp, 0);
		}
		else tgt->type = o;
	}
	else
	{	// different name
		ObjectInfo *obj = NULL, *origin = NULL;;
		if ((tgt->type = _emit_util_resolve_type(&tgt->isForwarded, tgt->srcType, tgt->isPointer, tgt->instance, tgt->memb_flags, papa, p->module, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	// Set Member Type
	////////////////////////////////////////////////////

	if (errp->code != 0) { }
	else if ((err = dst_list->append(dst_list, tgt->isForwarded,
								tgt->type, NULL, tgt->isPointer, tgt->instance,
								tgt->memb_flags, tgt->dumpMode, tgt->arr_cnt_name)).code) ERR_OUT(&err);
	else Dz1Error_set(errp, 0);

	_struct_member_entry_cleanup(&p->structEntry);
	return err;
}

static Dz1Error set_struct_member_attr(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (0) { }
	else if (strcmp(t->v, "notarg") == 0)		p->structEntry.memb_flags &= ~MEMBER_FLAG_ARG_INVOLVE;
	else if (strcmp(t->v, "key")== 0)			p->structEntry.memb_flags |= MEMBER_FLAG_IS_INDEX;
	else if (strcmp(t->v, "ref")== 0)
	{
		if ((p->structEntry.memb_flags & MEMBER_FLAG_IS_ARRAY) && (p->structEntry.memb_flags & MEMBER_FLAG_IS_ARRAY_REF_ELEM))
			Dz1Thread_printf("set_struct_member_attr() : 'ref' on array element '%s' is ignored\n", p->structEntry.instance);
		p->structEntry.memb_flags |= MEMBER_FLAG_IS_REFERENCED;
	}

	else if (strcmp(t->v, "nodump")== 0)		p->structEntry.dumpMode = MemberDumpMode_omit;
	else if (strcmp(t->v, "valdump")== 0)		p->structEntry.dumpMode = MemberDumpMode_value;
	else if (strcmp(t->v, "cascadedump")== 0)	p->structEntry.dumpMode = MemberDumpMode_cascade;
	else
	{
		Dz1Thread_printf("set_struct_member_attr() : Unknown structure member attribute %s\n", t->v);
		ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}
// Structure
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitStruct(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_struct",					new_struct)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_struct_member_forward",	set_struct_member_forward)).code)	ERR_OUT(errp);
	else if ((*errp = Dz1Parser_addEmiter(p, "set_struct_member_type",		set_struct_member_type)).code)		ERR_OUT(errp);
	else if ((*errp = Dz1Parser_addEmiter(p, "set_struct_member_pointer",	set_struct_member_pointer)).code)	ERR_OUT(errp);
	else if ((*errp = Dz1Parser_addEmiter(p, "set_struct_member_instance",	set_struct_member_instance)).code)	ERR_OUT(errp);
	else if ((*errp = Dz1Parser_addEmiter(p, "set_struct_member_array",		set_struct_member_array)).code)		ERR_OUT(errp);
	else if ((*errp = Dz1Parser_addEmiter(p, "set_struct_member_array_cnt",	set_struct_member_array_cnt)).code)	ERR_OUT(errp);
	else if ((*errp = Dz1Parser_addEmiter(p, "set_struct_member_array_ref",	set_struct_member_array_ref)).code)	ERR_OUT(errp);
	else if ((*errp = Dz1Parser_addEmiter(p, "add_struct_member",			add_struct_member)).code)			ERR_OUT(errp);
	else if ((*errp = Dz1Parser_addEmiter(p, "set_struct_member_attr",		set_struct_member_attr)).code)		ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
