#include <dz1_str.h>
// #include <dz1_aatree.h>
// #include <dz1_fifo.h>
#include <dz1_thread_stdio.h>

#include "publish_c.h"
#include "publish_util.h"
#include "publish_asnconv.h"
#include "publish_inner_array.h"
#include "publish_union_util.h"
#include "publish_union_c.h"

///////////////////////////////////////////////////////////////////////////////
// UnionMemberEntry : HEADER
// static void UnionMemberEntry_header(FILE *fp, PublishSpec *spec, str_t tn, UnionMemberEntry *p, int tab)
// {
// 	str_t _ptr = p->isPointer ? "*" : "";
// 	str_t e_tn = ObjectInfo_nameOf(p->type);
// 	Dz1ThreadA_ftprintf(fp, tab,		"%s%s %s%s;\n", forwardCaster(p->isForwarded), e_tn, _ptr, p->instance);
// }

static void UnionMemberEntry_headerForward(FILE *fp, PublishSpec *spec, str_t tn, UnionMemberEntry *p, int tab)
{
	if (p->isForwarded)
		Dz1ThreadA_ftprintf(fp, tab,	"%s%s;\n", forwardCaster(p->isForwarded), ObjectInfo_nameOf(p->type));
}

static void UnionMemberEntry_headerPresent(FILE *fp, PublishSpec *spec, str_t prefix, UnionMemberEntry *p, int tab)
{
	if (p->presentStr == NULL)
		Dz1ThreadA_ftprintf(fp, tab,	"%sPresent_%s,\n", prefix, p->instance);
	else Dz1ThreadA_ftprintf(fp, tab,	"%sPresent_%s = %s,\t\n", prefix, p->instance, p->presentStr);
}
// UnionMemberEntry : HEADER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UnionMemberEntry : SOURCE
static void UnionMemberEntry_srcPresent(FILE *fp, PublishSpec *spec, str_t tn, UnionMemberEntry *p, int tab)
{
	Dz1ThreadA_ftprintf(fp, tab,		"{ \"%s\", %sPresent_%s },\n", p->instance, tn, p->instance);
}

static void UnionMemberEntry_srcNew(FILE *fp, PublishSpec *spec, str_t tn, UnionMemberEntry *p, int tab)
{
	char buf[1024];

 	PublishErrorSpec *error = spec->error;

	bool_t needElse = FALSE;
	ObjectInfo *o = ObjectInfo_getOrigin(p->type);

	Dz1ThreadA_ftprintf(fp, tab++,	"case %sPresent_%s:\n", tn, p->instance);
	UnionMemberEntry_clone_code(fp, tn, "ret", "", p, o, spec, tab, &needElse);
	Dz1ThreadA_ftprintf(fp, tab,	"%s%s;%s\n", 
									needElse ? "else {" : "", 
									error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL),
									needElse ? " }" : "");
	Dz1ThreadA_ftprintf(fp, tab--, "break;\n");
}

static void UnionMemberEntry_srcClone(FILE *fp, PublishSpec *s, str_t tn, UnionMemberEntry *p, int tab)
{
	char buf[1024];

 	PublishErrorSpec *error = s->error;

	bool_t needElse = FALSE;
	ObjectInfo *o = ObjectInfo_getOrigin(p->type);

	Dz1ThreadA_ftprintf(fp, tab++,	"case %sPresent_%s:\n", tn, p->instance);
	UnionMemberEntry_clone_code(fp, tn, "ret", "src", p, o, s, tab, &needElse);
	Dz1ThreadA_ftprintf(fp, tab,	"%s%s;%s\n", 
									needElse ? "else {" : "", 
									error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL),
									needElse ? " }" : "");
	Dz1ThreadA_ftprintf(fp, tab--, "break;\n");
}

static void UnionMemberEntry_srcDel(FILE *fp, PublishSpec *s, str_t tn, UnionMemberEntry *p, int tab)
{
	ObjectInfo *o = ObjectInfo_getOrigin(p->type);

	Dz1ThreadA_ftprintf(fp, tab++, "case %sPresent_%s:\n", tn, p->instance);
	UnionMemberEntry_del_code(fp, tn, "p", p, o, s, tab);
	Dz1ThreadA_ftprintf(fp, tab--,		"break;\n");
}

static void UnionMemberEntry_srcCmp(FILE *fp, PublishSpec *s, str_t tn, UnionMemberEntry *p, int tab)
{
	bool_t needElse = FALSE;
	ObjectInfo *o = ObjectInfo_getOrigin(p->type);

	Dz1ThreadA_ftprintf(fp, tab++,	"case %sPresent_%s:\n", tn, p->instance);
	UnionMemberEntry_cmp_code(fp, tn, "a", "b", p, o, s, tab, &needElse);
	Dz1ThreadA_ftprintf(fp, tab--,		"break;\n");
}

static void UnionMemberEntry_srcDump(FILE *fp, str_t tn, UnionMemberEntry *p, MemberDumpSpec *ds, PublishSpec *s, int tab)
{
	bool_t needElse = FALSE;
	ObjectInfo *o = ObjectInfo_getOrigin(p->type);

	Dz1ThreadA_ftprintf(fp, tab++,	"case %sPresent_%s:\n", tn, p->instance);
	UnionMemberEntry_dump_code(fp, tn, "p", p, o, s, ds, tab, &needElse);
	Dz1ThreadA_ftprintf(fp, tab--,	"break;\n");
}
// UnionMemberEntry : SOURCE
///////////////////////////////////////////////////////////////////////////////

static void UnionMemberList_loop(FILE *fp, PublishSpec *s, str_t tn, UnionMemberList *p, int tab,
								void (*func)(FILE *fp, PublishSpec *s, str_t tn, UnionMemberEntry *p, int tab))
{
	UnionMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL) func(fp, s, tn, e, tab);

		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

///////////////////////////////////////////////////////////////////////////////
// UnionMemberList : HEADER
static void UnionMemberList_headerForward(FILE *fp, PublishSpec *spec, UnionMemberList *p, int tab)
{ UnionMemberList_loop(fp, spec, NULL, p, tab, UnionMemberEntry_headerForward); }

static void UnionMemberList_header(FILE *fp, PublishSpec *spec, UnionMemberList *p, int tab)
//{ UnionMemberList_loop(fp, spec, NULL, p, tab, UnionMemberEntry_header); }
{
	UnionMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		MemberEntryNames info;

		char temp[1024];
		int type_len = 0, temp_len, type_tab, ptr_len = 0;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
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
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
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
// UnionMemberList : HEADER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UnionMemberList : SOURCE
static void UnionMemberList_srcNew(FILE *fp, PublishSpec *spec, str_t prefix, UnionMemberList *p, int tab)
{ UnionMemberList_loop(fp, spec, prefix, p, tab, UnionMemberEntry_srcNew); }

static void UnionMemberList_srcClone(FILE *fp, PublishSpec *spec, str_t prefix, UnionMemberList *p, int tab)
{ UnionMemberList_loop(fp, spec, prefix, p, tab, UnionMemberEntry_srcClone); }

static void UnionMemberList_srcDel(FILE *fp, PublishSpec *spec, str_t prefix, UnionMemberList *p, int tab)
{ UnionMemberList_loop(fp, spec, prefix, p, tab, UnionMemberEntry_srcDel); }

static void UnionMemberList_srcCmp(FILE *fp, PublishSpec *spec, str_t prefix, UnionMemberList *p, int tab)
{ UnionMemberList_loop(fp, spec, prefix, p, tab, UnionMemberEntry_srcCmp); }

static void UnionMemberList_loopDump(FILE *fp, str_t tn, UnionMemberList *p, MemberDumpSpec *ds, PublishSpec *s, int tab,
									 void (*func)(FILE *fp, str_t tn, UnionMemberEntry *p, MemberDumpSpec *ds, PublishSpec *s, int tab))
{
	UnionMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL) func(fp, tn, e, ds, s, tab);

		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}

static void UnionMemberList_srcDump(FILE *fp, PublishSpec *s, str_t tn, UnionMemberList *p, MemberDumpSpec *ds, int tab)
{ UnionMemberList_loopDump(fp, tn, p, ds, s, tab, UnionMemberEntry_srcDump); }
// UnionMemberList : SOURCE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UnionInfo : HEADER
bool_t UnionInfo_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, UnionInfo *p, PublishSpec *s, int tab)
{
	NativeTypeSpec *bool_sp = s->findPrimitive(s, BOOLTYPE_NAME);
	str_t bool_tn = bool_sp == NULL ? "int" : bool_sp->native;

	PublishBasicSpec *base = s->base;
	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;

	bool_t p_dump = FALSE, p_fdump = FALSE;

	// Forward Declare
	UnionMemberList_headerForward(fp, s, p->members, tab);

	// Declare Structure
	Dz1ThreadA_ftprintf(fp, tab,	"typedef struct %s\n", tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%sPresent present;\n", tn);
	Dz1ThreadA_ftprintf(fp, tab,		"union\n");
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"void *__ptr__;\n");
	Dz1ThreadA_ftprintf(fp, tab,			"unsigned char b1[1];\n");
	Dz1ThreadA_ftprintf(fp, tab,			"unsigned char b2[2];\n");
	Dz1ThreadA_ftprintf(fp, tab,			"unsigned char b4[4];\n");
	UnionMemberList_header(fp, s, p->members, tab);
	Dz1ThreadA_ftprintf(fp, --tab,		"} x;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"} %s;\n\n", tn);

	if (t_api & OBJECT_API_NEW)
		Dz1ThreadA_ftprintf(fp, tab,		"%s %s %s *%s%s(%sPresent present, void *ptr, %s *err);\n", base->cpplink, base->dllport, tn, tn, postFix->_new, tn, error->type);
	if (t_api & OBJECT_API_GEN)
	{
		if (t_api & OBJECT_API_USER_GEN)
			Dz1ThreadA_ftprintf(fp, tab,	"%s %s %s *%s%s(%s *err);\n", base->cpplink, base->dllport, tn, tn, postFix->_gen, error->type);
		else Dz1ThreadA_ftprintf(fp, tab,	"static __inline__ %s *%s%s(%s *err) { return %s%s(%sPresent_max, NULL, err); }\n", tn, tn, postFix->_gen, error->type, tn, postFix->_new, tn);
	}
	if (t_api & OBJECT_API_CLONE)
	{
		Dz1ThreadA_ftprintf(fp, tab,		"%s %s %s  %s%s(%s *dst, %s *src, %s *err);\n", 
											base->cpplink, base->dllport, 
											bool_tn, tn, postFix->_copy, tn, tn, error->type);
		Dz1ThreadA_ftprintf(fp, tab,		"%s %s %s *%s%s(%s *src, %s *err);\n", 
											base->cpplink, base->dllport, 
											tn, tn, postFix->_clone, tn, error->type);
	}
	if (t_api & OBJECT_API_DEL)
	{
		Dz1ThreadA_ftprintf(fp, tab,		"%s %s void %s%s(%s *p);\n", base->cpplink, base->dllport, tn, postFix->_purge, tn);
		Dz1ThreadA_ftprintf(fp, tab,		"%s %s void %s%s(%s *p);\n", base->cpplink, base->dllport, tn, postFix->_del, tn);
	}

	// Declare DelAndSetNull
	if (t_api & OBJECT_API_DELANDSETNULL)	Type_header_delAndSetNull(fp, tn, FALSE, s, tab);

	_dump_api_header_publish(fp, tn, t_api, "*p", TRUE, s, tab);

	// Declare Compare
	if (t_api & OBJECT_API_CMP)
		Dz1ThreadA_ftprintf(fp, tab,		"%s %s int %s%s(%s *a, %s *b);\n", base->cpplink, base->dllport, tn, postFix->_cmp, tn, tn);
	return TRUE;
}
// UnionInfo : HEADER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UnionInfo : HEADER ASN Converter
bool_t UnionInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t api, UnionInfo *p, PublishSpec *s, int tab)
{
	return Publish_asnConvDeclare(fp, api, s, tn, tn_alt, tab);
}
// UnionInfo : HEADER ASN Converter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UnionInfo : SOURCE
static void _print_union_new(FILE *fp, str_t tn, UnionInfo *p, PublishSpec *s, int tab)
{
	char buf[1024];

	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;
	str_t mem_arg = mem->allocNeedErrorPtr ? ", errp" : "";

	Dz1ThreadA_ftprintf(fp, tab,	"%s *%s%s(%sPresent present, void *ptr, %s *err)\n", tn, tn, postFix->_new, tn, error->type);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s _err = %s, *errp = err ? err : &_err;\n", error->type, error->defaultVal);
	Dz1ThreadA_ftprintf(fp, tab,		"%s *ret = (%s *)%s(sizeof(%s), 1%s);\n", tn, tn, mem->calloc, tn, mem_arg);
	Dz1ThreadA_ftprintf(fp, tab,		"if (ret == NULL) { %s; }\n", error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "ENOMEM"));
	Dz1ThreadA_ftprintf(fp, tab,		"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	if (s->pthread) 
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_push(%s%s, (void *)&ret);\n\n", tn, postFix->_delAndSetNull);
	Dz1ThreadA_ftprintf(fp, tab,			"ret->present = present;\n");
	Dz1ThreadA_ftprintf(fp, tab,			"switch(ret->present)\n");
	Dz1ThreadA_ftprintf(fp, tab,			"{\n");
	UnionMemberList_srcNew(fp, s, tn, p->members, tab);
	Dz1ThreadA_ftprintf(fp, tab++,			"case %sPresent_max:\n", tn);
	Dz1ThreadA_ftprintf(fp, tab--,				"break;\n");
	Dz1ThreadA_ftprintf(fp, tab++,			"default:\n");
	Dz1ThreadA_ftprintf(fp, tab,				"%s;\n", error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EINVAL"));
	Dz1ThreadA_ftprintf(fp, tab--,				"break;\n");
	Dz1ThreadA_ftprintf(fp, tab,			"}\n");
	if (s->pthread) 
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_pop(%s); // (%s%s, (void *)&ret);\n", 
											error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL), tn, postFix->_delAndSetNull);
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}

static void _print_union_clone(FILE *fp, str_t tn, UnionInfo *p, PublishSpec *s, int tab)
{
	char buf[1024];
	NativeTypeSpec *bool_sp = s->findPrimitive(s, BOOLTYPE_NAME);
	str_t bool_tn = bool_sp == NULL ? "int" : bool_sp->native;

	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;
	str_t mem_arg = mem->allocNeedErrorPtr ? ", errp" : "";



	Dz1ThreadA_ftprintf(fp, tab,	"%s %s%s(%s *ret, %s *src, %s *err)\n", bool_tn, tn, postFix->_copy, tn, tn, error->type);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s _err = %s, *errp = err ? err : &_err;\n", s->error->type, s->error->defaultVal);
	Dz1ThreadA_ftprintf(fp, tab,		"if (src == NULL || ret == NULL) { errp->code = EINVAL; %s; }\n", error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"ret->present = src->present;\n");
	Dz1ThreadA_ftprintf(fp, tab,			"switch(src->present)\n");
	Dz1ThreadA_ftprintf(fp, tab,			"{\n");
	UnionMemberList_srcClone(fp, s, tn, p->members, tab);
	Dz1ThreadA_ftprintf(fp, tab++,			"default:\n");
	Dz1ThreadA_ftprintf(fp, tab,				"%s;\n", error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EINVAL"));
	Dz1ThreadA_ftprintf(fp, tab--,				"break;\n");
	Dz1ThreadA_ftprintf(fp, tab,			"}\n");
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	Dz1ThreadA_ftprintf(fp,	tab,		"return %s ? FALSE : TRUE;\n", error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");


	Dz1ThreadA_ftprintf(fp, tab,	"%s *%s%s(%s *src, %s *err)\n", tn, tn, postFix->_clone, tn, error->type);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s *ret = NULL;\n", tn);
	Dz1ThreadA_ftprintf(fp, tab,		"%s _err = %s, *errp = err ? err : &_err;\n", error->type, error->defaultVal);
	Dz1ThreadA_ftprintf(fp, tab,		"if (src == NULL) { errp->code = EINVAL; %s; }\n", error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"else if ((ret = (%s *)%s(sizeof(%s), 1%s)) == NULL) { %s; }\n",
										tn, mem->calloc, tn, mem_arg, error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));

	Dz1ThreadA_ftprintf(fp, tab,		"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	if (s->pthread)
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_push(%s%s, (void *)&ret);\n", tn, postFix->_delAndSetNull);
	Dz1ThreadA_ftprintf(fp, tab,			"if (%s%s(ret, src, errp) == FALSE) { %s; }\n", tn, postFix->_copy, error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,			"else %s;\n", error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL));
	if (s->pthread)
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_pop(%s); // (%s%s, (void *)&ret);\n",
											error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL), tn, postFix->_delAndSetNull);
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}

static void _print_union_del(FILE *fp, str_t tn, UnionInfo *p, PublishSpec *s, int tab)
{
	PublishPostFix *postFix = s->postFix;
	PublishMemFuncSpec *mem = s->mem;

	Dz1ThreadA_ftprintf(fp, tab,	"void %s%s(%s *p)\n", tn, postFix->_purge, tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"if (!p) return;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"switch(p->present)\n");
	Dz1ThreadA_ftprintf(fp, tab,		"{\n");
	UnionMemberList_srcDel(fp, s, tn, p->members, tab);
	Dz1ThreadA_ftprintf(fp, tab++,		"default:\n");
	Dz1ThreadA_ftprintf(fp, tab--,			"break;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"}\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");

	Dz1ThreadA_ftprintf(fp, tab,	"void %s%s(%s *p)\n", tn, postFix->_del, tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"if (!p) return;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s%s(p);\n", tn, postFix->_purge);
	Dz1ThreadA_ftprintf(fp, tab,		"%s(p);\n", mem->free);
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
static void _print_union_dump(FILE *fp, PublishSpec *s, str_t tn, UnionInfo *p, int d_mode, bool_t f_mode, int tab)
{
	int printf_mode = d_mode;

	PublishBasicSpec *base = s->base;
	PublishPostFix *postFix = s->postFix;

	str_t fptype_str = f_mode ? "FILE *" : "";

	MemberDumpSpec ds;
	MemberDumpSpec_init(&ds, f_mode, d_mode, s);

	Dz1ThreadA_ftprintf(fp, tab,	"void %s%s%s(%s%s%s *p, int tab)\n", tn, ds._AW, ds._dump, fptype_str, ds._fparg, tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"if (!p) %s(%s%s\"NULL\\n\"%s);\n", ds._fprintf, ds._fparg, ds._TLb, ds._TLe);
	Dz1ThreadA_ftprintf(fp, tab,		"else switch(p->present)\n");
	Dz1ThreadA_ftprintf(fp, tab,		"{\n");
	UnionMemberList_srcDump(fp, s, tn, p->members, &ds, tab);
	Dz1ThreadA_ftprintf(fp, tab++,		"default:\n");
	Dz1ThreadA_ftprintf(fp, tab,			"%s(%stab, %s\"??? = %%d\\n\"%s, p->present);\n", ds._ftprintf, ds._fparg, ds._TLb, ds._TLe);
	Dz1ThreadA_ftprintf(fp, tab--,			"break;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"}\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
}

static void _print_union_cmp(FILE *fp, str_t tn, UnionInfo *p, PublishSpec *s, int tab)
{
	PublishPostFix *postFix = s->postFix;

	Dz1ThreadA_ftprintf(fp, tab,	"int %s%s(%s *a, %s *b)\n", tn, postFix->_cmp, tn, tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"int ret = 0;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"if (a == NULL && b == NULL) ret = 0;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"else if (a == NULL && b != NULL) ret = -1;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"else if (a != NULL && b == NULL) ret = 1;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"else if (a->present != b->present) ret = (int)(a->present - b->present);\n");
	if (p->comparePresentOnly == FALSE)
	{
		Dz1ThreadA_ftprintf(fp, tab,	"else\n");
		Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
		Dz1ThreadA_ftprintf(fp, tab,		"switch(a->present)\n");
		Dz1ThreadA_ftprintf(fp, tab,		"{\n");
		UnionMemberList_srcCmp(fp, s, tn, p->members, tab);
		Dz1ThreadA_ftprintf(fp, tab++,		"default:\n");
		Dz1ThreadA_ftprintf(fp, tab,			"ret = 0;\n");
		Dz1ThreadA_ftprintf(fp, tab--,			"break;\n");
		Dz1ThreadA_ftprintf(fp, tab,		"}\n");
		Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
	}
	else Dz1ThreadA_ftprintf(fp, tab,	"else ret = 0;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}

///////////////////////////////////////////////////////////////////////////////
// inner array member api
static bool_t _UnionMemberList_arrMembMacro(FILE *fp, str_t tn, u32_t t_api, UnionMemberEntry *p, UnionMemberList *list, PublishSpec *spec, int tab)
{
	bool_t ret = FALSE;
	ObjectInfo *o = ObjectInfo_getOrigin(p->type);
	StructMemberArrayMacroAPI *api = StructMemberArrayMacroAPI_find(o->type);
	if (api == NULL)
	{
		Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(_UnionMemberList_arrMembMacro:no_api)\n", tn, p->instance);
		ret = TRUE;
	}
	else if (api->code == NULL) { }
	else
	{
		StructMemberEntry *c = NULL;
		if (strstr(p->end_of_arr, "$$") != NULL)
			api->code(fp, tn, t_api, p->type, p->isPointer, p->instance, p->memb_flags, p->dumpMode, p->end_of_arr, TRUE, spec, tab);	// arrZ type
		else if (Dz1StrA_isDigitStr(p->end_of_arr))
			api->code(fp, tn, t_api, p->type, p->isPointer, p->instance, p->memb_flags, p->dumpMode, "unsigned int", FALSE, spec, tab);	// fixed size type
		else Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(_UnionMemberList_arrMembMacro:no_member)\n", tn, p->instance);
		ret = TRUE;
	}
	return ret;
}

static bool_t UnionMemberList_arrMembMacro(FILE *fp, str_t tn, u32_t api, UnionMemberList *list, PublishSpec *spec, int tab)
{
	bool_t ret = FALSE;
	UnionMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(list->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (UnionMemberEntry_isArray(e))
				{
					if (_UnionMemberList_arrMembMacro(fp, tn, api, e, list, spec, tab))
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

bool_t UnionInfo_source(FILE *fp, str_t tn, str_t tn_alt, u32_t api, UnionInfo *p, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	bool_t p_dump = FALSE, p_fdump = FALSE;

	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;
	str_t mem_arg = mem->allocNeedErrorPtr ? ", errp" : "";

	if (UnionMemberList_arrMembMacro(fp, tn, api, p->members, s, tab)) ret = TRUE;

	if ((api & OBJECT_API_NEW) && !(api & OBJECT_API_USER_NEW))		{ _print_union_new(fp, tn, p, s, tab);		ret = TRUE; }
	if ((api & OBJECT_API_CLONE) && !(api & OBJECT_API_USER_CLONE)) { _print_union_clone(fp, tn, p, s, tab);	ret = TRUE; }
	if ((api & OBJECT_API_DEL) && !(api & OBJECT_API_USER_DEL))		{ _print_union_del(fp, tn, p, s, tab);		ret = TRUE; }

	// Dump
	if ((api & OBJECT_API_DUMP) && !(api & OBJECT_API_USER_DUMP)) p_dump = TRUE;
	if ((api & OBJECT_API_FDUMP) && !(api & OBJECT_API_USER_FDUMP)) p_fdump = TRUE;

	if (p_dump || p_fdump)
	{
		u8_t type = (api & (OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE));
		switch(type)
		{
		case 0:
			if (p_dump) _print_union_dump(fp, s, tn, p, 0, FALSE, tab);
			if (p_fdump) _print_union_dump(fp, s, tn, p, 0, TRUE, tab);
			break;
		case 1:
			if (p_dump) _print_union_dump(fp, s, tn, p, 3, FALSE, tab);
			if (p_fdump) _print_union_dump(fp, s, tn, p, 3, TRUE, tab);
			break;
		case 2:
			if ((api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (p_dump) _print_union_dump(fp, s, tn, p, 4, FALSE, tab);
			if (p_fdump) _print_union_dump(fp, s, tn, p, 4, TRUE, tab);
			if ((api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		case 3:
			if (p_dump) _print_union_dump(fp, s, tn, p, 1, FALSE, tab);
			if (p_fdump) _print_union_dump(fp, s, tn, p, 1, TRUE, tab);
			if ((api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (p_dump) _print_union_dump(fp, s, tn, p, 2, FALSE, tab);
			if (p_fdump) _print_union_dump(fp, s, tn, p, 2, TRUE, tab);
			if ((api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		}
		fprintf(fp, "\n");
		ret = TRUE;
	}

	// Compare
	if ((api & OBJECT_API_CMP) && !(api & OBJECT_API_USER_CMP)) { _print_union_cmp(fp, tn, p, s, tab); ret = TRUE; }

	return ret;
}
// UnionInfo : SOURCE
///////////////////////////////////////////////////////////////////////////////

/*
void UnionInfo_testHeader(FILE *fp, PublishSpec *spec, u32_t api, str_t name,  UnionInfo *p, int tab)
{
	TP(fp, tab); fprintf(fp, "%s %s %s *%s_test(%s *src, %s *err);\n", spec->base->cpplink, spec->base->dllport, name, name, name, spec->error->type);
	fprintf(fp, "\n");
}

void UnionInfo_testSource(FILE *fp, PublishSpec *spec, u32_t api, str_t name,  UnionInfo *p, int tab)
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
*/
