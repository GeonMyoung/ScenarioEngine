#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include "publish_c.h"
#include "publish_util.h"
#include "publish_asnconv.h"
#include "publish_enum_c.h"

///////////////////////////////////////////////////////////////////////////////
// ENUM Entry
static void EnumEntry_header(FILE *fp, str_t prefix, EnumEntry *p, int tab)
{	// header type member enumerate
	str_t val = "", eq = "";
	if (Dz1Str_isVoid(p->valStr) == FALSE)
	{
		val = p->valStr;
		eq = " = ";
	}
	Dz1ThreadA_ftprintf(fp, tab, "%s_%s%s%s,\n", prefix, p->name, eq, val);
}

static void EnumEntry_source(FILE *fp, str_t tn, EnumEntry *p, bool_t isUnicode, int tab)
{	// source type member enumerate
	str_t _L = isUnicode ? "(wchar_t *)L" : "(char *)";
	Dz1ThreadA_ftprintf(fp, tab, "{ %s\"%s\", %s_%s },\n", _L, p->name, tn, p->name);
}
// ENUM Entry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ENUM List
static void EnumList_header(FILE *fp, str_t prefix, EnumList *p, int tab)
{	// header type member enumerate
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		EnumEntry *e = NULL;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			e = (EnumEntry *)Dz1FifoCursor_data(c);
			EnumEntry_header(fp, prefix, e, tab);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	Dz1ThreadA_ftprintf(fp, tab, "%s_max\n", prefix);
}

static void EnumList_source(FILE *fp, str_t prefix, EnumList *p, bool_t isUnicode, int tab)
{	// source type member enumerate
	EnumEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			e = (EnumEntry *)Dz1FifoCursor_data(c);
			EnumEntry_source(fp, prefix, e, isUnicode, tab);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}
// ENUM List
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ENUM header type
static void EnumInfo_header_type(FILE *fp, str_t tn, EnumInfo *p, int tab)
{	// enum header type define
	TP(fp, tab); fprintf(fp, "typedef enum %s\n", tn);
	TP(fp, tab); fprintf(fp, "{\n");
	EnumList_header(fp, tn, p->enums, tab + 1);
	TP(fp, tab); fprintf(fp, "} %s;\n\n", tn);

}
// ENUM header type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ENUM header str function
static void EnumInfo_header_str_function(FILE *fp, str_t tn, u32_t t_api, EnumInfo *p, PublishSpec *s, int tab)
{	// header {tn}"Str"{A|W} Function declare
	PublishBasicSpec *base = s->base;

	NativeTypeSpec strkey =  { STRTYPE_NAME },	*str =  (NativeTypeSpec *)Dz1AATree_find(s->primitives, &strkey);
	NativeTypeSpec wstrkey = { WSTRTYPE_NAME }, *wstr = (NativeTypeSpec *)Dz1AATree_find(s->primitives, &wstrkey);

	str_t a_sp = str->native[strlen(str->native) - 1] == '*' ? "" : " ";
	str_t w_sp = wstr->native[strlen(wstr->native) - 1] == '*' ? "" : " ";

	TP(fp, tab); fprintf(fp, "%s %s%s%sStrA(%s v);\n", base->cpplink, str->native, a_sp, tn, tn);		// DZ1_CPPLINK str_t MyEnumStrA(MyEnum v);
	TP(fp, tab); fprintf(fp, "%s %s%s%sFromStrA(%s str);\n", base->cpplink, tn, a_sp, tn, str->native);	// DZ1_CPPLINK str_t MyEnumFromStrA(MyEnum v);

	if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
	TP(fp, tab); fprintf(fp, "%s %s%s%sStrW(%s v);\n", base->cpplink, wstr->native, w_sp, tn, tn);		// DZ1_CPPLINK wstr_t MyEnumStrW(MyEnum v);
	TP(fp, tab); fprintf(fp, "%s %s%s%sFromStrW(%s str);\n", base->cpplink, tn, w_sp, tn, wstr->native);// DZ1_CPPLINK wstr_t MyEnumFromStrW(MyEnum v);
	TP(fp, tab); fprintf(fp, "#ifdef UNICODE\n");
	TP(fp, tab); fprintf(fp, "#define %sStr %sStrW\n", tn, tn);				// #define MyEnumStr		MyEnumStrW
	TP(fp, tab); fprintf(fp, "#define %sFromStr %sFromStrW\n", tn, tn);		// #define MyEnumFromStr	MyEnumFromStrW
	TP(fp, tab); fprintf(fp, "#else // UNICODE\n");
	TP(fp, tab); fprintf(fp, "#define %sStr %sStrA\n", tn, tn);				// #define MyEnumStr		MyEnumStrA
	TP(fp, tab); fprintf(fp, "#define %sFromStr %sFromStrA\n", tn, tn);		// #define MyEnumFromStr	MyEnumFromStrW
	TP(fp, tab); fprintf(fp, "#endif // UNICODE\n");
	if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) 
	{
		fprintf(fp, "#else // UNIX_SYSTEM\n");
		TP(fp, tab); fprintf(fp, "#define %sStr %sStrA\n", tn, tn);			// #define MyEnumStr		MyEnumStrA
		TP(fp, tab); fprintf(fp, "#define %sFromStr %sFromStrA\n", tn, tn);	// #define MyEnumFromStr	MyEnumFromStrW
		fprintf(fp, "#endif // UNIX_SYSTEM\n");
	}
}
// ENUM header str function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ENUM source str function
static void _enum_source_str_function(FILE *fp, str_t tn, bool_t is_unicode, EnumInfo *p, NativeTypeSpec *str_spec, PublishSpec *s, int tab)
{	// source {tn}"Str"{A|W} Function code
	str_t _AW = is_unicode ? "W" : "A";
	PublishPostFix *pfx = s->postFix;
	str_t spc = str_spec->native[strlen(str_spec->native)-1] == '*' ? "" : " ";

	Dz1ThreadA_ftprintf(fp, tab,	"static struct %sMap%s\n", tn, _AW);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s%sstr;\n", str_spec->native, spc);
	Dz1ThreadA_ftprintf(fp, tab,		"%s v;\n", tn);
	Dz1ThreadA_ftprintf(fp, --tab,	"} %sMap%s[] =\n", tn, _AW);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	EnumList_source(fp, tn, p->enums, is_unicode, tab);
	Dz1ThreadA_ftprintf(fp, tab,		"{ NULL, %s_max }\n", tn);
	Dz1ThreadA_ftprintf(fp, --tab,	"};\n");
	Dz1ThreadA_ftprintf(fp, tab,	"\n");

	// Value to String
	Dz1ThreadA_ftprintf(fp, tab,	"%s%s%sStr%s(%s v)\n", str_spec->native, spc, tn, _AW, tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"struct %sMap%s *i = NULL;\n", tn, _AW);
	Dz1ThreadA_ftprintf(fp, tab++,		"for (i = %sMap%s; i->str; i++)\n", tn, _AW);
	Dz1ThreadA_ftprintf(fp, tab--,			"if (i->v == v) return i->str;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return NULL;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
	Dz1ThreadA_ftprintf(fp, tab,	"\n");
	
	// String to Value                1  2        3  4
	Dz1ThreadA_ftprintf(fp, tab,	"%s %sFromStr%s(%s str)\n", tn, tn, _AW, str_spec->native);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"struct %sMap%s *i = NULL;\n", tn, _AW);
	Dz1ThreadA_ftprintf(fp, tab++,		"for (i = %sMap%s; i->str; i++)\n", tn, _AW);
	Dz1ThreadA_ftprintf(fp, tab--,			"if (%s%s(i->str, str) == 0) return i->v;\n", str_spec->prefix, pfx->_cmp);
	Dz1ThreadA_ftprintf(fp, tab,		"return %s_max;\n", tn);
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
}
// ENUM source str function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ENUM header
bool_t EnumInfo_header(FILE *fp, str_t tn, str_t tn_alt, u32_t api, EnumInfo *p, PublishSpec *spec, int tab)
{
	char fmt[1024] = { 0, };
	PublishMemFuncSpec *mem = spec->mem;
	PublishBasicSpec *base = spec->base;
	PublishErrorSpec *error = spec->error;
	PublishPostFix *postFix = spec->postFix;
 	NativeTypeSpec enumkey = { ENUMTYPE_NAME }, *word = (NativeTypeSpec *)Dz1AATree_find(spec->primitives, &enumkey);

	EnumInfo_header_type(fp, tn, p, tab);
	EnumInfo_header_str_function(fp, tn, api, p, spec, tab);

	if (api & OBJECT_API_NEW)
		Dz1ThreadA_ftprintf(fp, tab, "%s %s %s *%s%s(%s *src, %s *err);\n",
			base->cpplink, base->dllport, tn, tn, postFix->_new, tn, error->type);

	if (api & OBJECT_API_GEN)
		Dz1ThreadA_ftprintf(fp, tab, "static __inline__ %s *%s%s(%s *err) { %s v = %s_max; return %s%s(&v, err); }\n",
			tn, tn, postFix->_gen, error->type, tn, tn, tn, postFix->_new);
	//							 1														1   2  3 4
	sprintf(fmt, "#define %%s%%-%ds %%s%%s\n", spec->postFix->lenMax + 4); // "#define %s%-#s %s%s\n"

	if (api & OBJECT_API_CLONE)			Dz1ThreadA_ftprintf(fp, tab, fmt, tn, spec->postFix->_clone,	tn, postFix->_new);
	if (api & OBJECT_API_DEL)	//							  1 2  3                       4
		Dz1ThreadA_ftprintf(fp, tab, "static __inline__ void %s%s(%s *p) { if (p != NULL) %s(p); }\n", tn, postFix->_del, tn, mem->free);
	if (api & OBJECT_API_DELANDSETNULL) Type_header_delAndSetNull(fp, tn, FALSE, spec, tab);

	_dump_api_header_publish(fp, tn, api, "*v", FALSE, spec, tab);

	if (api & OBJECT_API_CMP) Dz1ThreadA_ftprintf(fp, tab, "%s %s int %s%s(%s *a, %s *b);\n", base->cpplink, base->dllport, tn, postFix->_cmp, tn, tn);
	return TRUE;
}
// ENUM header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ENUM header ASN Converter
bool_t EnumInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, EnumInfo *p, PublishSpec *s, int tab)
{
	bool_t printed = FALSE;
	printed = Publish_asnConvDeclare(fp, t_api, s, tn, tn_alt, tab);
	if (printed) fprintf(fp, "\n");
	return printed;
}
// ENUM header ASN Converter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ENUM source dump function
static void __enum_source_dump_function(FILE *fp, str_t tn, bool_t file_mode, int dump_mode, PublishSpec *s, int tab)
{
	PublishBasicSpec *base = s->base;
	PublishPostFix *postFix = s->postFix;
	str_t _AW = NULL, _Tb = NULL, _Te = NULL;
	str_t _fparg = file_mode ? "fp, " : "";
	str_t *_print_api = file_mode ? base->fprintf : base->printf;
	switch(dump_mode)
	{
	case 0:	// none
		_AW = "";
		_Tb = "Dz1T(";
		_Te = ")";
		break;
	case 1:	// OBJECT_API_DUMP_MBCS
		_AW = "A";
		_Tb = "";
		_Te = "";
		break;
	case 2:	// OBJECT_API_DUMP_WIDE
		_AW = "W";
		_Tb = "L";
		_Te = "";
		break;
	}
	_dump_api_declare(fp, tn, _AW, "*v", file_mode, s, FALSE, tab);
	TP(fp, tab++); fprintf(fp, "{\n");
	TP(fp, tab); fprintf(fp, "if (v == NULL) %s(%s%s\"NULL\\n\"%s);\n", _print_api[dump_mode], _fparg, _Tb, _Te);
	TP(fp, tab); fprintf(fp, "else %s(%s%s\"%%s\\n\"%s, %sStr%s(*v));\n", _print_api[dump_mode], _fparg, _Tb, _Te, tn, _AW);
	TP(fp, --tab); fprintf(fp, "}\n");
}

static void _enum_source_dump(FILE *fp, str_t name, u32_t t_api, PublishSpec *spec, int tab)
{
	bool_t p_dump = FALSE, p_fdump = FALSE;
	if ((t_api & OBJECT_API_DUMP) && !(t_api & OBJECT_API_USER_DUMP)) p_dump = TRUE;
	if ((t_api & OBJECT_API_FDUMP) && !(t_api & OBJECT_API_USER_FDUMP)) p_fdump = TRUE;

	if (p_dump || p_fdump)
	{
		u8_t type = (t_api & (OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE));
		Dz1ThreadA_ftprintf(fp, tab, "\n");
		switch(type)
		{
		case 0:
		case 1:
			if (p_dump) __enum_source_dump_function(fp, name, FALSE, type, spec, tab);
			if (p_fdump) __enum_source_dump_function(fp, name, TRUE, type, spec, tab);
			break;
		case 2:
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (p_dump) __enum_source_dump_function(fp, name, FALSE, type, spec, tab);
			if (p_fdump) __enum_source_dump_function(fp, name, TRUE, type, spec, tab);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		case 3:
			if (p_dump) __enum_source_dump_function(fp, name, FALSE, 1, spec, tab);
			if (p_fdump) __enum_source_dump_function(fp, name, TRUE, 1, spec, tab);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (p_dump) __enum_source_dump_function(fp, name, FALSE, 2, spec, tab);
			if (p_fdump) __enum_source_dump_function(fp, name, TRUE, 2, spec, tab);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		}
	}
}
// ENUM source dump function
///////////////////////////////////////////////////////////////////////////////

bool_t EnumInfo_source(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, EnumInfo *p, PublishSpec *s, int tab)
{
	char buf[1024];
	PublishMemFuncSpec *mem = s->mem;
	PublishErrorSpec *error = s->error;
	PublishPostFix *postFix = s->postFix;

	NativeTypeSpec strkey = { STRTYPE_NAME }, *a_str = (NativeTypeSpec *)Dz1AATree_find(s->primitives, &strkey);
	NativeTypeSpec wstrkey = { WSTRTYPE_NAME }, *w_str = (NativeTypeSpec *)Dz1AATree_find(s->primitives, &wstrkey);
	// NativeTypeSpec enumkey = { ENUMTYPE_NAME }, *word = (NativeTypeSpec *)Dz1AATree_find(spec->primitives, &enumkey);

	_enum_source_str_function(fp, tn, FALSE, p, a_str, s, tab);
	if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
	_enum_source_str_function(fp, tn, TRUE, p, w_str, s, tab);
	if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
	
	if (t_api & OBJECT_API_NEW)
	{
		str_t alloc_err_arg = mem->allocNeedErrorPtr ? ", errp" : "";
		Dz1ThreadA_ftprintf(fp, tab,	"\n");

		Dz1ThreadA_ftprintf(fp, tab,	"%s *%s%s(%s *src, %s *err)", tn, tn, postFix->_new, tn, error->type);
		Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
		Dz1ThreadA_ftprintf(fp, tab,		"%s _err = %s, *errp = err ? err : &_err;\n", error->type, error->defaultVal);
		Dz1ThreadA_ftprintf(fp, tab,		"%s *__internal_ret = (%s *)%s(sizeof(%s), 1%s);\n", tn, tn, mem->calloc, tn, alloc_err_arg);
		Dz1ThreadA_ftprintf(fp, tab,		"if (__internal_ret == NULL) { %s; }\n", error->code(s->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "ENOMEM"));
		Dz1ThreadA_ftprintf(fp, tab,		"else\n");
		Dz1ThreadA_ftprintf(fp, tab++,		"{\n");

		Dz1ThreadA_ftprintf(fp, tab,			"*__internal_ret = *src;\n");
		Dz1ThreadA_ftprintf(fp, tab,			"%s;\n", error->code(s->error, buf, ErrorCodeGenType_clear, "*errp", NULL));

		Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
		Dz1ThreadA_ftprintf(fp, tab,		"return __internal_ret;\n");
		Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
	}

	_enum_source_dump(fp, tn, t_api, s, tab);

	if (t_api & OBJECT_API_CMP)
	{
		Dz1ThreadA_ftprintf(fp, tab,	"\n");

		Dz1ThreadA_ftprintf(fp, tab,	"int %s%s(%s *a, %s *b)\n", tn, postFix->_cmp, tn, tn);
		Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
		Dz1ThreadA_ftprintf(fp,	tab,		"int ret = 0;\n");
		Dz1ThreadA_ftprintf(fp,	tab,		"if (a == NULL && b == NULL) { }\n");
		Dz1ThreadA_ftprintf(fp,	tab,		"else if (a == NULL /* && b != NULL*/) ret = -1;\n");
		Dz1ThreadA_ftprintf(fp,	tab,		"else if (/*a == NULL &&*/ b == NULL) ret = 1;\n");
		Dz1ThreadA_ftprintf(fp, tab,		"else ret = (int)(*a - *b);\n");
		Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
		Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
	}
	return TRUE;
}
