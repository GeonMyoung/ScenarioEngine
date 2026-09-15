#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_aatree.h>
#include <dz1_str.h>

#include "publish_c.h"
#include "publish_asnconv.h"
#include "publish_inner_array.h"
#include "publish_struct_util.h"
#include "publish_structure_c.h"

///////////////////////////////////////////////////////////////////////////////
// Member list publish API
typedef bool_t (*MemberFilterF)(StructMemberEntry *p);
static bool_t StructMemberList_clone_code(FILE *fp, MemberFilterF filter, str_t tn, str_t dst, str_t src, StructMemberList *p, PublishSpec *s, int tab, bool_t *_else)
{
	bool_t ret = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (filter == NULL || filter(e) == TRUE)
				{
					ObjectInfo *o = ObjectInfo_getOrigin(e->type);
					if (StructMemberEntry_clone_code(fp, tn, dst, src, e, o, s, tab, _else))
						ret = TRUE;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
static bool_t StructMemberList_alloc_code(FILE *fp, MemberFilterF filter, str_t tn, str_t dst, StructMemberList *p, PublishSpec *s, int tab, bool_t *_else)
{
	bool_t ret = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (filter == NULL || filter(e) == TRUE)
				{
					ObjectInfo *o = ObjectInfo_getOrigin(e->type);
					if (StructMemberEntry_alloc_code(fp, tn, dst, e, o, s, tab, _else))
						ret = TRUE;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
static bool_t StructMemberList_assign_code(FILE *fp, MemberFilterF filter, str_t tn, str_t dst, str_t src, StructMemberList *p, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (filter == NULL || filter(e) == TRUE)
				{
					ObjectInfo *o = ObjectInfo_getOrigin(e->type);
					if (StructMemberEntry_assign_code(fp, tn, dst, src, e, o, s, tab))
						ret = TRUE;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
static void StructMemberList_del_code(FILE *fp, MemberFilterF filter, str_t tn, str_t dst, StructMemberList *p, PublishSpec *s, int tab)
{
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (filter == NULL || filter(e) == TRUE)
				{
					ObjectInfo *o = ObjectInfo_getOrigin(e->type);
					StructMemberEntry_del_code(fp, tn, dst, e, o, s, tab);
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

static bool_t StructMemberList_cmp_code(FILE *fp, MemberFilterF filter, str_t tn, str_t l, str_t r, StructMemberList *p, PublishSpec *s, int tab, bool_t *_else)
{
	bool_t ret = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (filter == NULL || filter(e) == TRUE)
				{
					ObjectInfo *o = ObjectInfo_getOrigin(e->type);
					if (StructMemberEntry_cmp_code(fp, tn, l, r, e, o, s, tab, _else)) ret = TRUE;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}

typedef struct StructMemberCntArg
{
	MemberFilterF	 filter;
	u32_t			 cnt;
} StructMemberCntArg;

static Dz1Error _StructMemberList_filteredCount(void *ptr, StructMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StructMemberCntArg *arg = (StructMemberCntArg *)ptr;

	if (arg->filter == NULL) arg->cnt++;
	else if (arg->filter(p)) arg->cnt++;

	return err;
}

static u32_t StructMemberList_filteredCount(StructMemberList *p, MemberFilterF filter)
{
	u32_t ret = 0;
	if (p != NULL)
	{
		StructMemberCntArg arg = { filter, 0 };
		p->travel(p, _StructMemberList_filteredCount, (void *)&arg);
		ret = arg.cnt;
	}
	return ret;
}

static void StructMemberList_dump_code(FILE *fp, MemberFilterF filter, str_t tn, str_t var, StructMemberList *p, 
									   PublishSpec *s, MemberDumpSpec *ds, int tab)
{
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		bool_t _else = FALSE;
		StructMemberEntry *e = NULL;
		u32_t dump_cnt = StructMemberList_filteredCount(p, filter);

		pthread_cleanup_push(Dz1FifoCursor_del, c);

		if (dump_cnt == 0)
		{
			Dz1ThreadA_ftprintf(fp, tab,		"// %s has no dump element(s)\n", tn);
			//									  1  2 3           4		// fprintf(fp, Dz1T("{ }\n"));
			Dz1ThreadA_ftprintf(fp, tab,		"%s(%s%s\"{ }\\n\"%s);", ds->_fprintf, ds->_fparg, ds->_TLb, ds->_TLe);
		}
		else
		{
			bool_t many_memb = dump_cnt > 1 ? TRUE : FALSE;
			if (many_memb)	//					  1  2 3         4			// fprintf(fp, Dz1T("{\n")); tab++;
				Dz1ThreadA_ftprintf(fp, tab,	"%s(%s%s\"{\\n\"%s); tab++;\n", ds->_fprintf, ds->_fparg, ds->_TLb, ds->_TLe);

			for (Dz1FifoCursorForward(c))
			{
				if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				{
					if (filter == NULL || filter(e) == TRUE)
					{
						ObjectInfo *o = ObjectInfo_getOrigin(e->type);
						StructMemberEntry_dump_code(fp, tn, var, e, o, s, ds, many_memb, tab, &_else);
					}
				}
			}

			if (many_memb)	//					  1  2        3         4	// ftprintf(fp, --tab, Dz1T("}\n"));
				Dz1ThreadA_ftprintf(fp, tab,	"%s(%s--tab, %s\"}\\n\"%s);\n", ds->_ftprintf, ds->_fparg, ds->_TLb, ds->_TLe);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}
// Member list publish API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Filters
static bool_t _arg_involved_(StructMemberEntry *p)
{
	return StructMemberEntry_isArgInvolve(p);
}

static bool_t _arg_not_involved_(StructMemberEntry *p)
{
	return StructMemberEntry_isArgInvolve(p) ? FALSE : TRUE;
}

static bool_t _key_member_(StructMemberEntry *p)
{
	return StructMemberEntry_isIndex(p);
}

static bool_t _printable_memb_(StructMemberEntry *p)
{
	return p->dumpMode == MemberDumpMode_omit ? FALSE : TRUE;
}
// Filters
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// NEW
static bool_t StructureInfo_new_code(FILE *fp, str_t tn, StructureInfo *p, PublishSpec *s)
{
	int tab = 0;
	char buf[1204];
	bool_t _else = FALSE;
	u32_t front_space = 0;
	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;
	str_t dst = "__internal_ret";

	Dz1ThreadA_ftprintf(fp, tab,	"%s *%s%s(", tn, tn, postFix->_new);

	front_space += (tab * TAB_SIZE);
	front_space += (u32_t)strlen(tn);
	front_space++;	// ' '
	front_space++;	// '*'
	front_space += (u32_t)strlen(tn);
	front_space += (u32_t)strlen(postFix->_new);
	front_space++;	// '('

	if (StructureMemberList_args(fp, p->members, front_space, FALSE))
		Dz1ThreadA_fprintf(fp, ", ");
	Dz1ThreadA_fprintf(fp, "%s *err)\n", error->type);

	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s _err = %s, *errp = err ? err : &_err;\n", error->type, error->defaultVal);
	Dz1ThreadA_ftprintf(fp, tab,		"%s *%s = (%s *)%s(sizeof(%s), 1%s);\n", tn, dst, tn, mem->calloc, tn, mem->allocNeedErrorPtr ? ", errp" : "");
	Dz1ThreadA_ftprintf(fp, tab,		"if (%s == NULL) { %s; }\n", dst, error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "ENOMEM"));
	Dz1ThreadA_ftprintf(fp, tab,		"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	if (s->pthread)
	{
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_push(%s%s, (void *)&%s);\n", tn, postFix->_delAndSetNull, dst);
		Dz1ThreadA_ftprintf(fp, tab,		"\n");
	}

	StructMemberList_clone_code(fp, _arg_involved_, tn, dst, "", p->members, s, tab, &_else);	// clone or copy argument member
	StructMemberList_alloc_code(fp, _arg_not_involved_, tn, dst, p->members, s, tab, &_else);	// initialize other member

	if (_else)
	{
		Dz1ThreadA_ftprintf(fp, tab,		"else\n");
		Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	}

	StructMemberList_assign_code(fp, _arg_involved_, tn, dst, "", p->members, s, tab);			// assign argument member
	Dz1ThreadA_ftprintf(fp, tab, "%s;\n", error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL));

	if (_else)
		Dz1ThreadA_ftprintf(fp, --tab,		"}\n");

	if (s->pthread)
	{
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_pop(%s); // (%s%s, (void *)&%s)\n",
				error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL), tn, postFix->_delAndSetNull, dst);
	}
	else
	{
		Dz1ThreadA_ftprintf(fp, tab,		"if (%s) %s%s(&%s);\n", 
				error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL), tn, postFix->_delAndSetNull, dst);
	}
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return %s;\n", dst);
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");

	return TRUE;
}
// NEW
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CLONE
static bool_t StructureInfo_clone_code(FILE *fp, str_t tn, StructureInfo *p, PublishSpec *s)
{
	int tab = 0;
	char buf[1204];
	NativeTypeSpec *bool_sp = s->findPrimitive(s, BOOLTYPE_NAME);
	str_t bool_tn = bool_sp == NULL ? "int" : bool_sp->native;

	bool_t _else = TRUE;
	str_t src = "src", dst = "dst";
	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;
	// copy API
	Dz1ThreadA_ftprintf(fp,	tab,	"%s %s%s(%s *%s, %s *%s, %s *err)\n", bool_tn, tn, postFix->_copy, tn, dst, tn, src, error->type);
	Dz1ThreadA_ftprintf(fp,	tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"%s _err = %s, *errp = err ? err : &_err;\n", error->type, error->defaultVal);
	Dz1ThreadA_ftprintf(fp,	tab,		"if (%s == NULL || %s == NULL) { %s; }\n", dst, src, error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EINVAL"));

	StructMemberList_clone_code(fp, NULL, tn, dst, src, p->members, s, tab, &_else);	// clone

	Dz1ThreadA_ftprintf(fp,	tab,		"else\n");
	Dz1ThreadA_ftprintf(fp,	tab++,		"{\n");

	StructMemberList_assign_code(fp, NULL, tn, dst, src, p->members, s, tab);			// assign
	Dz1ThreadA_ftprintf(fp,	tab,			"%s;\n", error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL));

	Dz1ThreadA_ftprintf(fp,	--tab,		"}\n");

	Dz1ThreadA_ftprintf(fp,	tab,		"return %s ? FALSE : TRUE;\n", error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp,	--tab,	"}\n\n");

	// clone API
	Dz1ThreadA_ftprintf(fp,	tab,	"%s *%s%s(%s *%s, %s *err)\n", tn, tn, postFix->_clone, tn, src, error->type);
	Dz1ThreadA_ftprintf(fp,	tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"%s *%s = NULL;\n", tn, dst);
	Dz1ThreadA_ftprintf(fp,	tab,		"%s _err = %s, *errp = err ? err : &_err;\n", error->type, error->defaultVal);
	Dz1ThreadA_ftprintf(fp,	tab,		"if (%s == NULL) { %s; }\n", src, error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EINVAL"));

	Dz1ThreadA_ftprintf(fp,	tab,		"else if ((%s = (%s *)%s(sizeof(%s), 1%s)) == NULL) { %s; }\n", 
												dst, tn, mem->calloc, tn, mem->allocNeedErrorPtr ? ", errp" : "", 
												error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp,	tab,		"else\n");
	Dz1ThreadA_ftprintf(fp,	tab++,		"{\n");

	if (s->pthread)
		Dz1ThreadA_ftprintf(fp,	tab,		"pthread_cleanup_push(%s%s, (void *)&%s);\n", tn, postFix->_delAndSetNull, dst);
	Dz1ThreadA_ftprintf(fp,	tab,			"if (%s%s(%s, %s, errp) == FALSE) %s;\n", 
											tn, postFix->_copy, dst, src, 
											error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EINVAL"));
	Dz1ThreadA_ftprintf(fp,	tab,			"else %s;\n", error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL));

	if (s->pthread)
		Dz1ThreadA_ftprintf(fp,	tab,		"pthread_cleanup_pop(%s); // (%s%s, (void *)&%s);\n",
											error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL), tn, postFix->_delAndSetNull, dst);

	Dz1ThreadA_ftprintf(fp,	--tab,		"}\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"return %s;\n", dst);
	Dz1ThreadA_ftprintf(fp,	--tab,	"}\n\n");

	return TRUE;
}
// CLONE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DEL
static bool_t StructureInfo_del_code(FILE *fp, str_t tn, StructureInfo *p, PublishSpec *s)
{
	int tab = 0;
	str_t dst = "p";
	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;

	Dz1ThreadA_ftprintf(fp,	tab,	"void %s%s(%s *%s)\n", tn, postFix->_purge, tn, dst);
	Dz1ThreadA_ftprintf(fp,	tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"if (p == NULL) return;\n");
	StructMemberList_del_code(fp, NULL, tn, dst, p->members, s, tab);
	Dz1ThreadA_ftprintf(fp,	--tab,	"}\n\n");

	Dz1ThreadA_ftprintf(fp,	tab,	"void %s%s(%s *%s)\n", tn, postFix->_del, tn, dst);
	Dz1ThreadA_ftprintf(fp,	tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"if (p == NULL) return;\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"%s%s(%s);\n", tn, postFix->_purge, dst);
	Dz1ThreadA_ftprintf(fp,	tab,		"%s(p);\n", mem->free);
	Dz1ThreadA_ftprintf(fp,	--tab,	"}\n\n");
	return TRUE;
}
// DEL
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CMP
static bool_t StructureInfo_cmp_code(FILE *fp, str_t tn, StructureInfo *p, PublishSpec *s)
{
	int tab = 0;
	bool_t _else = TRUE;
	str_t l = "a", r = "b";
	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;

	Dz1ThreadA_ftprintf(fp,	tab,	"int %s%s(%s *%s, %s *%s)\n", tn, postFix->_cmp, tn, l, tn, r);
	Dz1ThreadA_ftprintf(fp,	tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"int ret = 0;\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"if (%s == NULL && %s == NULL) { }\n", l, r);
	Dz1ThreadA_ftprintf(fp,	tab,		"else if (%s == NULL /* && %s != NULL*/) ret = -1;\n", l, r);
	Dz1ThreadA_ftprintf(fp,	tab,		"else if (/*%s == NULL &&*/ %s == NULL) ret = 1;\n", l, r);

	StructMemberList_cmp_code(fp, _key_member_, tn, l, r, p->members, s, tab, &_else);

	Dz1ThreadA_ftprintf(fp, tab,	"return ret;\n");
	Dz1ThreadA_ftprintf(fp,	--tab, "}\n");

	return TRUE;
}
// CMP
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DUMP
static void StructureInfo_dump_code(FILE *fp, str_t tn, StructureInfo *p, PublishSpec *s, bool_t is_file_mode, int dump_mode, int tab)
{
	int printf_mode = dump_mode;
	PublishBasicSpec *base = s->base;
	PublishPostFix *postFix = s->postFix;
	str_t fptype_str = is_file_mode ? "FILE *" : "";
	MemberDumpSpec ds;
	MemberDumpSpec_init(&ds, is_file_mode, dump_mode, s);

//	Dz1Thread_printf(Dz1T("file_mode = %d, printf = %s, tprintf = %s\n"), is_file_mode, ds._fprintf, ds._ftprintf);
																											 
	TP(fp, tab); fprintf(fp, "void %s%s%s(%s%s%s *p, int tab)\n", tn, ds._AW, ds._dump, fptype_str, ds._fparg, tn);
	TP(fp, tab++); fprintf(fp, "{\n");
	TP(fp, tab); fprintf(fp, "if (!p) %s(%s%s\"NULL\\n\"%s);\n", ds._fprintf, ds._fparg, ds._TLb, ds._TLe);
	TP(fp, tab); fprintf(fp, "else\n");
	TP(fp, tab++); fprintf(fp, "{\n");
	StructMemberList_dump_code(fp, _printable_memb_, tn, "p", p->members, s, &ds, tab);
	TP(fp, --tab); fprintf(fp, "}\n");

	TP(fp, --tab); fprintf(fp, "}\n");
}
// DUMP
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// inner array member api
static bool_t _StructureMemberList_arrMembMacro(FILE *fp, str_t tn, u32_t t_api, StructMemberEntry *p, StructMemberList *list, PublishSpec *spec, int tab)
{
	bool_t ret = FALSE;
	ObjectInfo *o = ObjectInfo_getOrigin(p->type);
	StructMemberArrayMacroAPI *api = StructMemberArrayMacroAPI_find(o->type);
	if (api == NULL)
	{
		Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(_StructureMemberList_arrMembMacro:no_api)\n", tn, p->instance);
		ret = TRUE;
	}
	else if (api->code == NULL) { }
	else
	{
		StructMemberEntry *c = NULL;
		if (strstr(p->arr_cnt_name, "$$") != NULL)
			api->code(fp, tn, t_api, p->type, p->isPointer, p->instance, p->memb_flags, p->dumpMode, p->arr_cnt_name, TRUE, spec, tab);	// arrZ type
		else if (Dz1StrA_isDigitStr(p->arr_cnt_name))
			api->code(fp, tn, t_api, p->type, p->isPointer, p->instance, p->memb_flags, p->dumpMode, "unsigned int", FALSE, spec, tab);	// fixed size type
		else if ((c = list->find(list, p->arr_cnt_name)) == NULL)
			Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(_StructureMemberList_arrMembMacro:no_member)\n", tn, p->instance);
		else
		{
			str_t c_tn = ObjectInfo_nameOf(c->type);
			api->code(fp, tn, t_api, p->type, p->isPointer, p->instance, p->memb_flags, p->dumpMode, c_tn, FALSE, spec, tab);			// array with counter
		}

		ret = TRUE;
	}
	return ret;
}

static bool_t StructureMemberList_arrMembMacro(FILE *fp, str_t tn, u32_t api, StructMemberList *list, PublishSpec *spec, int tab)
{
	bool_t ret = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(list->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (StructMemberEntry_isArray(e))
				{
					if (_StructureMemberList_arrMembMacro(fp, tn, api, e, list, spec, tab))
						ret = TRUE;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
// inner array member api
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TARGET SOURCE V2
bool_t StructureInfo_source(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, StructureInfo *p, PublishSpec *s, int tab)
{
	bool_t printed = FALSE;
	bool_t p_dump = FALSE, p_fdump = FALSE;

	printed = StructureMemberList_arrMembMacro(fp, tn, t_api, p->members, s, tab);

	// New
	if (t_api & OBJECT_API_NEW)
	{
		if (t_api & OBJECT_API_USER_NEW) Dz1Thread_printf("@@@ User New API indicated\n");
		else printed = StructureInfo_new_code(fp, tn, p, s);
	}

	// Clone
	if (t_api & OBJECT_API_CLONE)
	{
		if (t_api & OBJECT_API_USER_CLONE) Dz1Thread_printf("@@@ User Clone API indicated\n");
		else printed = StructureInfo_clone_code(fp, tn, p, s);
	}

	// Del
	if (t_api & OBJECT_API_DEL)
	{
		if (t_api & OBJECT_API_USER_DEL) Dz1Thread_printf("@@@ User Del API indicated\n");
		else printed = StructureInfo_del_code(fp, tn, p, s);
	}

	// Dump
	if ((t_api & OBJECT_API_DUMP) && !(t_api & OBJECT_API_USER_DUMP)) p_dump = TRUE;
	if ((t_api & OBJECT_API_FDUMP) && !(t_api & OBJECT_API_USER_FDUMP)) p_fdump = TRUE;

	if (p_dump || p_fdump)
	{
		u8_t type = (t_api & (OBJECT_API_DUMP_WIDE | OBJECT_API_DUMP_MBCS));
		switch(type)
		{
		case 0:	// no mode
			if (p_dump) { StructureInfo_dump_code(fp, tn, p, s, FALSE, 0, tab); printed = TRUE; }
			if (p_fdump) { StructureInfo_dump_code(fp, tn, p, s, TRUE, 0, tab); printed = TRUE; }
			break;
		case 1:	// OBJECT_API_DUMP_MBCS
			if (p_dump) { StructureInfo_dump_code(fp, tn, p, s, FALSE, 3, tab); printed = TRUE; }
			if (p_fdump) { StructureInfo_dump_code(fp, tn, p, s, TRUE, 3, tab); printed = TRUE; }
			break;
		case 2:	// OBJECT_API_DUMP_WIDE
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) { fprintf(fp, "#ifndef UNIX_SYSTEM\n"); printed = TRUE; }
			if (p_dump) { StructureInfo_dump_code(fp, tn, p, s, FALSE, 4, tab); printed = TRUE; }
			if (p_fdump) { StructureInfo_dump_code(fp, tn, p, s, TRUE, 4, tab); printed = TRUE; }
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0){ fprintf(fp, "#endif // UNIX_SYSTEM\n"); printed = TRUE; }
			break;
		case 3:	// OBJECT_API_DUMP_WIDE | OBJECT_API_DUMP_MBCS
			if (p_dump) { StructureInfo_dump_code(fp, tn, p, s, FALSE, 1, tab); printed = TRUE; }
			if (p_fdump) { StructureInfo_dump_code(fp, tn, p, s, TRUE, 1, tab); printed = TRUE; }
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) { fprintf(fp, "#ifndef UNIX_SYSTEM\n"); printed = TRUE; }
			if (p_dump) { StructureInfo_dump_code(fp, tn, p, s, FALSE, 2, tab); printed = TRUE; }
			if (p_fdump) { StructureInfo_dump_code(fp, tn, p, s, TRUE, 2, tab); printed = TRUE; }
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) { fprintf(fp, "#endif // UNIX_SYSTEM\n"); printed = TRUE; }
			break;
		}
	}

	// Compare
	if ((t_api & OBJECT_API_CMP) && StructureInfo_comparable(p, s))
	{
		if (t_api & OBJECT_API_USER_CMP) { }
		else printed = StructureInfo_cmp_code(fp, tn, p, s);
	}
	return printed;
}
// TARGET SOURCE V2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TARGET HEADER : pre-declare (struct | union | enum)
static bool_t StructureMemberList_headerForward(FILE *fp, str_t name, StructMemberList *p, int tab)
{
	bool_t ret = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (e->isForwarded) 
				{ 
					Dz1ThreadA_ftprintf(fp, tab, "%s%s;\n", 
										forwardCaster(e->isForwarded),
										ObjectInfo_nameOf(e->type));
					ret = TRUE;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
// TARGET HEADER : pre-declare (struct | union | enum)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TARGET HEADER
static void StructureMemberList_header(FILE *fp, str_t name, StructMemberList *p, int tab)
{
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		MemberEntryNames info;

		char temp[1024];
		int type_len = 0, temp_len, type_tab, ptr_len = 0;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				MemberEntryNames_get(&info, e->isForwarded, e->type, e->isPointer, e->memb_flags, TRUE);
				if ((temp_len = (int)strlen(info.type)) > type_len) type_len = temp_len;		// max type length
				if ((temp_len = (int)strlen(info.ptrs_memb)) > ptr_len) ptr_len = temp_len;		// max ptr length
			}
		}

		if ((type_len % TAB_SIZE) == 0)
			type_tab = (type_len / TAB_SIZE) + 1;
		else type_tab = (type_len / TAB_SIZE) + 2;

		//							   1
		_std_snprintfA(temp, 1024, "%%%ds%%s;%%s\n", ptr_len);	// ptr print format
		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				int temp_tab;

				MemberEntryNames_get(&info, e->isForwarded, e->type, e->isPointer, e->memb_flags, TRUE);

				TP(fp, tab); fputs(info.type, fp);	// print type

				temp_len = (int)strlen(info.type);
				temp_tab = temp_len / TAB_SIZE;
				temp_tab = type_tab - temp_tab;
				TP(fp, temp_tab);					// print space

				//		 "%#s%s;%s"
				fprintf(fp, temp, info.ptrs_memb, e->instance, 
					StructMemberEntry_isAsnOptional(e) ? "\t// ASN OPTIONAL" : "");

			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

bool_t StructureInfo_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, StructureInfo *p, PublishSpec *s, int tab)
{
	bool_t p_dump = FALSE, p_fdump = FALSE;
	PublishBasicSpec *base = s->base;
	PublishErrorSpec *error = s->error;
	PublishPostFix *postFix = s->postFix;

	// Declare Forward
	if (StructureMemberList_headerForward(fp, tn, p->members, tab)) fputs("\n", fp);

	// Declare Structure
	Dz1ThreadA_ftprintf(fp, tab,		"typedef struct %s\n", tn);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	StructureMemberList_header(fp, tn, p->members, tab);
	Dz1ThreadA_ftprintf(fp, --tab,		"} %s;\n\n", tn);

	// Declare New(M)
	if (t_api & OBJECT_API_NEW)
	{
		str_t comment = (t_api & OBJECT_API_USER_NEW) ? "\t// User Customized" : "";
		u32_t front_space = 0;
		TP(fp, tab);
		Dz1ThreadA_ftprintf(fp, tab,	"%s %s %s *%s%s(", base->cpplink, base->dllport, tn, tn, postFix->_new);

		front_space += tab * TAB_SIZE;
		front_space += (u32_t)strlen(base->cpplink);
		front_space++;
		front_space += (u32_t)strlen(base->dllport);
		front_space++;
		front_space += (u32_t)strlen(tn);
		front_space++;	// ' '
		front_space++;	// '*'
		front_space += (u32_t)strlen(tn);
		front_space += (u32_t)strlen(postFix->_new);
		front_space++;	// '('

		if (StructureMemberList_args(fp, p->members, front_space, TRUE)) fputs(", ", fp);
		fprintf(fp, "%s *err);%s\n", error->type, comment);
	}

	if (t_api & OBJECT_API_GEN)
	{
		if (t_api & OBJECT_API_USER_GEN)//1  2  3   4 5  6
			Dz1ThreadA_ftprintf(fp,tab,	"%s %s %s *%s%s(%s *err);\t// User Customized\n", 
										base->cpplink, base->dllport,			// 1 2
										tn, tn, postFix->_gen, error->type);	// 3 4 5 6
		else
		{	//												1   2 3  4                 5 6
			Dz1ThreadA_ftprintf(fp,tab,	"static __inline__ %s *%s%s(%s *err) { return %s%s(",
										tn, tn, postFix->_gen, error->type,	// 1 2 3 4
										tn, postFix->_new);					// 5 6
			if (StructureMemberList_params(fp, p->members)) fputs(", ", fp);
			fprintf(fp, "err); }\n");
		}
	}


	// Declare Clone(O)
	if (t_api & OBJECT_API_CLONE)
	{	
		str_t comment = (t_api & OBJECT_API_USER_CLONE) ? "\t// User Customized" : "";
		//								   1  2         3 4  5        6        7
		Dz1ThreadA_ftprintf(fp, tab,	"%s %s bool_t %s%s(%s *dst, %s *src, %s *err);%s\n", 
										base->cpplink, base->dllport,	// 1 2
										tn, postFix->_copy, tn, tn,		// 3 4 5 6
										error->type, comment);			// 7
		//								   1  2  3   4 5  6        7
		Dz1ThreadA_ftprintf(fp, tab,	"%s %s %s *%s%s(%s *src, %s *err);%s\n", 
										base->cpplink, base->dllport,	// 1 2
										tn, tn, postFix->_clone,		// 3 4 5
										tn, error->type, comment);		// 6 7
	}

	// Declare Del(M)
	if (t_api & OBJECT_API_DEL)
	{
		str_t comment = (t_api & OBJECT_API_USER_DEL) ? "\t// User Customized" : "";
		//								  1  2       3 4  5			   1              2              3   4                5
		Dz1ThreadA_ftprintf(fp, tab,	"%s %s void %s%s(%s *p);%s\n", base->cpplink, base->dllport, tn, postFix->_purge, tn, comment);
		Dz1ThreadA_ftprintf(fp, tab,	"%s %s void %s%s(%s *p);%s\n", base->cpplink, base->dllport, tn, postFix->_del,   tn, comment);
	}

	// Declare DelAndSetNull(O)
	if (t_api & OBJECT_API_DELANDSETNULL)
	{
		Dz1ThreadA_ftprintf(fp, tab,	"static __inline__ void %s%s(void *ptr)\n", tn, postFix->_delAndSetNull);
		Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
		Dz1ThreadA_ftprintf(fp, tab,		"%s **p = (%s **)ptr;\n", tn, tn);
		Dz1ThreadA_ftprintf(fp, tab,		"if (p) { %s_del(*p); *p = NULL; }\n", tn);
		Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
	}

	_dump_api_header_publish(fp, tn, t_api, "*p", TRUE, s, tab);

	// Declare Compare(O)
	if (t_api & OBJECT_API_CMP)
	{
		if ((t_api & OBJECT_API_USER_CMP) || StructureInfo_comparable(p, s))
		{
			str_t comment = (t_api & OBJECT_API_USER_CMP) ? "\t// User Customized" : "";
			// Declare Compare				 1  2      3 4  5      6
			Dz1ThreadA_ftprintf(fp, tab,	"%s %s int %s%s(%s *a, %s *b); %s\n",
											base->cpplink, base->dllport,			// 1 2
											tn, postFix->_cmp, tn, tn, comment);	// 3 4 5 6
		}
		else Dz1ThreadA_ftprintf(fp, tab,	"#error : Can not comparable %s\n", tn);
	}
	return TRUE;
}
// TARGET HEADER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TARGET ASN CONV
bool_t StructureInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, StructureInfo *p, PublishSpec *s, int tab)
{
	bool_t printed = FALSE;
	printed = Publish_asnConvDeclare(fp, t_api, s, tn, tn_alt, tab);
	if (printed) fprintf(fp, "\n");
	return printed;
}
// TARGET ASN CONV
///////////////////////////////////////////////////////////////////////////////

#if 0
///////////////////////////////////////////////////////////////////////////////
// TARGET TEST
void StructureInfo_testSource(FILE *fp, PublishSpec *spec, u32_t api, str_t name, StructureInfo *p, int tab)
{
	char buf[1024];
	TP(fp, tab); fprintf(fp, "%s *%s_test(%s *src, %s *err)\n", name, name, name, spec->error->type);
	TP(fp, tab++); fprintf(fp, "{\n");
	TP(fp, tab); fprintf(fp, "%s _err, *errp = %s;\n", spec->error->type, spec->error->code(spec->error, buf, ErrorCodeGenType_init, "*err", "_err"));
	TP(fp, tab); fprintf(fp, "%s *dst = NULL;\n", name);
	TP(fp, tab); fprintf(fp, "unsigned char *buf = NULL;\n");
	TP(fp, tab); fprintf(fp, "int temp, size = %s%s(NULL, src);\n\n", name, spec->postFix->_enc);
	TP(fp, tab); fprintf(fp, "if (size == 0) %s;\n", spec->error->code(spec->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EFAULT"));
	TP(fp, tab); fprintf(fp, "else if ((buf = (unsigned char *)%s(size%s)) == NULL) %s;\n",
			spec->mem->malloc, spec->mem->allocNeedErrorPtr ? ", errp" : "",
			spec->error->code(spec->error, buf, ErrorCodeGenType_print, "*errp", NULL));
	TP(fp, tab); fprintf(fp, "else\n");
	TP(fp, tab++); fprintf(fp, "{\n");
	if (spec->pthread) { TP(fp, tab); fprintf(fp, "pthread_cleanup_push((void (*)(void *))%s, (void *)buf);\n\n", spec->mem->cancel); }
	TP(fp, tab); fprintf(fp, "if (%s%s(buf, src) == 0) %s;\n", name, spec->postFix->_enc,
			spec->error->code(spec->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EFAULT"));
	TP(fp, tab); fprintf(fp, "else if ((temp = %s%s(&dst, buf)) == 0) %s;\n", name, spec->postFix->_dec,
			spec->error->code(spec->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EFAULT"));
	TP(fp, tab); fprintf(fp, "else if (temp != size) %s;\n", spec->error->code(spec->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EFAULT"));
	// DZ1XXX : Element Check Code
	TP(fp, tab); fprintf(fp, "\n");
	if (spec->pthread) { TP(fp, tab); fprintf(fp, "pthread_cleanup_pop(1); // ((void (*)(void *))%s, (void *)buf);\n", spec->mem->cancel); }
	TP(fp, --tab); fprintf(fp, "}\n");
	TP(fp, tab); fprintf(fp, "return dst;\n");
	TP(fp, --tab); fprintf(fp, "}\n\n");
}

void StructureInfo_testHeader(FILE *fp, PublishSpec *spec, u32_t api, str_t name, StructureInfo *p, int tab)
{
	TP(fp, tab); fprintf(fp, "%s %s %s *%s_test(%s *src, %s *err);\n", spec->base->cpplink, spec->base->dllport, name, name, name, spec->error->type);
	fprintf(fp, "\n");
}
// TARGET TEST
///////////////////////////////////////////////////////////////////////////////
#endif
