#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"
#include "dz1_mdefc_emit_util.h"

///////////////////////////////////////////////////////////////////////////////
// Union
static Dz1Error new_union(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->obj) ObjectInfo_del(p->obj);

	if ((p->obj = ObjectInfo_new(ObjectType_union, NULL, NULL, OBJECT_API_BASE, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((p->obj->info = UnionInfo_new(errp)) == NULL) ERR_OUT(errp);

	return err;
}
// Union
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Forward
static Dz1Error set_union_member_forward(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;

	if (t->t == DZ1_PARSER_TOKEN_BLOCKSTART)
	{
		// Dz1Thread_printf("@@@ Union Member Import\n");
		e->isForwarded = FORWARD_TYPE_IMPORT;
	}
	else if (strcmp(t->v, "struct") == 0)	e->isForwarded = FORWARD_TYPE_STRUCT;
	else if (strcmp(t->v, "union") == 0)	e->isForwarded = FORWARD_TYPE_UNION;
	else									e->isForwarded = FORWARD_TYPE_ENUM;

	return err;
}
// Union Member Forward
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Type
static Dz1Error set_union_member_type(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;

	tValTake(e->srcType);

	e->isPointer = FALSE;
	e->memb_flags = 0;

	return err;
}
// Union Member Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Present Name
static Dz1Error set_union_member_present(Dz1ParserToken *t, void *param)
{	// alternative present value
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;

	if (e->presentStr != NULL) Dz1StrA_delAndSetNull(&e->presentStr);
	tValTake(e->presentStr);

	return err;
}
// Union Member Present Name
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member pointer
static Dz1Error set_union_member_pointer(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;

	e->isPointer = TRUE;

	return err;
}
// Union Member pointer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member name
static Dz1Error set_union_member_instance(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;

	tValTake(e->instance);

	return err;
}
// Union Member name
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member inner array
static Dz1Error set_union_member_array(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;

	e->memb_flags |= MEMBER_FLAG_IS_ARRAY;

	return err;
}

static Dz1Error set_union_member_array_end(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;

	if (t->t == DZ1_PARSER_TOKEN_STRING)
	{
		if (strstr(t->v, "$$") == 0)
		{
			Dz1ThreadA_printf("!!! End of array condition is invalid\n");
			ERR_SET_OUT(errp, EINVAL);
			return err;
		}
	}
	else if (Dz1StrA_isDigitStr(t->v) == FALSE)
	{
		Dz1ThreadA_printf("!!! Array size is invalid\n");
		ERR_SET_OUT(errp, EINVAL);
		return err;
	}

	tValTake(e->end_of_arr);

	return err;
}

static Dz1Error set_union_member_array_ref(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;

	e->memb_flags |= MEMBER_FLAG_IS_ARRAY_REF_ELEM;

	return err;
}
// Union Member inner array
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Attribute
static Dz1Error set_union_member_attr(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	UnionMemberEntry *e = &p->unionEntry;
	if (strcmp(t->v, "ref") == 0)
	{
		if ((e->memb_flags & MEMBER_FLAG_IS_ARRAY) && (e->memb_flags & MEMBER_FLAG_IS_ARRAY_REF_ELEM))
			Dz1Thread_printf("set_union_member_attr() : 'ref' on array element '%s' is ignored\n", e->instance);
		e->memb_flags |= MEMBER_FLAG_IS_REFERENCED;
	}
	else if (strcmp(t->v, "nodump") == 0) e->dumpMode = MemberDumpMode_omit;
	else if (strcmp(t->v, "valdump") == 0) e->dumpMode = MemberDumpMode_value;
	else if (strcmp(t->v, "cascadedump") == 0) e->dumpMode = MemberDumpMode_cascade;

//	Dz1Thread_printf("set_union_member_attr() : attr = %s\n", t->v);
	return err;
}
// Union Member Attribute
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Add
static Dz1Error add_union_member(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	ObjectInfo *papa = p->obj;
	UnionInfo *info = (UnionInfo *)papa->info;

	UnionMemberEntry *e = &p->unionEntry;

	ObjectInfo *origin = NULL, *src_obj = NULL;

	if (e->isForwarded == FORWARD_TYPE_IMPORT)
	{	// copy other union type's members
		if ((src_obj = p->module->findObject(p->module, e->srcType)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else if ((origin = ObjectInfo_getOrigin(src_obj)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else if (origin->type != ObjectType_union) ERR_SET_OUT(errp, EINVAL);
		else
		{
			UnionInfo		*src_info  = (UnionInfo *)src_obj->info;
			UnionMemberList *src_membs = src_info->members;
			UnionMemberList *dst_membs = info->members;
			if ((*errp = UnionMemberList_merge(dst_membs, src_membs)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	else
	{
		if ((e->type = _emit_util_resolve_type(&e->isForwarded, e->srcType, e->isPointer, e->instance, e->memb_flags, papa, p->module, errp)) == NULL) ERR_OUT(errp);
		else
		{	// single append
			UnionMemberList *members = info->members;
			if ((err = members->add(members, e->isForwarded, e->type, e->presentStr, NULL,
									e->isPointer, e->instance, e->memb_flags, e->dumpMode,
									e->end_of_arr)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);;
		}
	}
	UnionMemberEntry_purge(&p->unionEntry);
	return err;
}
// Union Member Add
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitUnion(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_union", new_union)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_forward", set_union_member_forward)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_type", set_union_member_type)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_present", set_union_member_present)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_pointer", set_union_member_pointer)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_instance", set_union_member_instance)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_array", set_union_member_array)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_array_end", set_union_member_array_end)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_array_ref", set_union_member_array_ref)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_union_member_attr", set_union_member_attr)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "add_union_member", add_union_member)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
