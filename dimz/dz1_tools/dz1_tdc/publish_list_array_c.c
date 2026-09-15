#include <dz1_aatree.h>
#include <dz1_thread_stdio.h>
#include "publish_c.h"
#include "publish_util.h"
#include "publish_asnconv.h"
#include "publish_list_util.h"
#include "publish_list_array_c.h"

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo header
bool_t ArrayInfo_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, ArrayInfo *p, PublishSpec *s, int tab)
{
	u32_t e_api = ObjectInfo_apiOf(p->entry, s);
	bool_t e_cmp = (e_api & OBJECT_API_CMP) ? TRUE : FALSE;

	ListType_header(fp, tn, p->type, t_api, p->arrayApi, p->entry, p->isForward, e_cmp, s, tab);
	return TRUE;
}
// ArrayInfo header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo header : ASN Converter
bool_t ArrayInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t api, ArrayInfo *p, PublishSpec *spec, int tab)
{
	bool_t printed = FALSE;
	printed = Publish_asnConvDeclare(fp, api, spec, tn, "ASN1List", tab);
	if (printed) fprintf(fp, "\n");
	return printed;
}
// ArrayInfo header : ASN Converter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : NEW function
static void ArrayInfo_sourceNew(FILE *fp, str_t tn, u32_t t_api, ArrayInfo *p, PublishSpec *s, int tab)
{
	char buf[1024];
	PublishArraySpec *as = s->arraySpec[p->type];

	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;
	PublishCastSpec *cast = s->cast;
	str_t mem_arg = mem->allocNeedErrorPtr ? ", errp" : "";

	str_t e_tn = ObjectInfo_nameOf(p->entry);
	str_t e_fx = ObjectInfo_prefixOf(p->entry, s);
	u32_t e_api = ObjectInfo_apiOf(p->entry, s);

	Dz1ThreadA_ftprintf(fp, tab,	"%s *%s%s(%s *err)\n", tn, tn, postFix->_new, error->type);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s _err = %s, *errp = %s;\n", error->type, error->defaultVal, error->code(error, buf, ErrorCodeGenType_init, "*err", "_err"));
	Dz1ThreadA_ftprintf(fp, tab,		"%s *ret = (%s *)%s(sizeof(%s), 1%s);\n", tn, tn, mem->calloc, tn, mem_arg);
	Dz1ThreadA_ftprintf(fp, tab,		"if (ret == NULL) %s;\n", error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	if (s->pthread) 
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_push(%s%s, (void *)&ret);\n\n", tn, postFix->_delAndSetNull);
	if (p->type == ArrayType_ordered || p->type == ArrayType_unique)
	{	// ordered || unique
		if (ObjectInfo_isPrimitive(p->entry) || (ObjectInfo_apiOf(p->entry, s) & OBJECT_API_CMP))
		{
// 			Dz1Thread_printf("p->type[2] = %u, %s\n", p->type, tn);

			Dz1ThreadA_ftprintf(fp, tab,	"if ((ret->storage = %s(\n", as->apiName(as, buf, ArraySpecApiType_new, "*p->storage"));
			Dz1ThreadA_ftprintf(fp, tab,			"\t\t%s%s%s,\n", cast->cmp, e_fx, postFix->_cmp);	// cmp

			if (p->isReferenced) 
				Dz1ThreadA_ftprintf(fp, tab,		"\t\tNULL, ");										// del
			else
			{
				Dz1ThreadA_ftprintf(fp, tab,		"\t\t%s%s%s,\n", cast->del, e_fx, postFix->_del);	// del
				Dz1ThreadA_ftprintf(fp, tab,		"\t\t");											// next line TAB support
			}
			fprintf(fp,								"NULL, errp)) == NULL) %s;\n", error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));	// dump
		}
		else Dz1ThreadA_ftprintf(fp, tab,	"#error \"%s's API is not support compare, delete or dump\"\n", e_tn);
	}
	else if (p->type == ArrayType_normal)
	{	// array
		Dz1ThreadA_ftprintf(fp, tab,		"if ((ret->storage = %s(\n", as->apiName(as, buf, ArraySpecApiType_new, "*p->storage"));
											
		if (p->isReferenced)
			Dz1ThreadA_ftprintf(fp, tab,			"\t\tNULL, ");
		else
		{
			Dz1ThreadA_ftprintf(fp, tab,			"\t\t%s%s%s,\n", cast->del, e_fx, postFix->_del);
			Dz1ThreadA_ftprintf(fp, tab,			"\t\t");	// next line TAB support
		}
		fprintf(fp,									"NULL, errp)) == NULL) %s;\n", error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	}

	Dz1ThreadA_ftprintf(fp, tab,			"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,			"{\n");

	if (e_api & OBJECT_API_CMP)
	{
		_std_snprintfA(buf, sizeof(buf), "%s%s", e_fx, postFix->_cmp);
		ListType_source_newApi(fp, tn, p->type, p->arrayApi, buf, s, tab);
//		ArrayInfo_sourceNewApi(fp, s, as, api, tn, p, tab);
	}
	else ListType_source_newApi(fp, tn, p->type, p->arrayApi, NULL, s, tab);
//	else Dz1ThreadA_ftprintf(fp, tab,			"#error \"%s's API is not support compare, delete or dump\"\n", e_tn);

	Dz1ThreadA_ftprintf(fp, tab,				"%s;\n", error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, --tab,			"}\n");
	if (s->pthread)
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_pop(%s); // (%s%s, (void *)&ret);\n",
										error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL),
										tn, postFix->_delAndSetNull);
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// ArrayInfo source : NEW function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source
bool_t ArrayInfo_source(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, ArrayInfo *p, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
//	bool_t p_dump = FALSE, p_fdump = FALSE;
	PublishArraySpec *aSpec = s->arraySpec[p->type];

	// api = ObjectInfo_apiOf(p->entry);

	if (p->arrayApi & ARRAY_API_ADD)
	{ ListType_source_add(fp, tn, p->type, p->entry, s, tab);		ret = TRUE; }
	if (p->arrayApi & ARRAY_API_REMOVE)
	{ ListType_source_remove(fp, tn, p->type, p->entry, s, tab);	ret = TRUE; }
	if (p->arrayApi & ARRAY_API_EXTRACT)
	{ ListType_source_extract(fp, tn, p->type, p->entry, s, tab);	ret = TRUE; }
	if (p->arrayApi & ARRAY_API_ARRAY)
	{ ListType_source_array(fp, tn, p->type, p->entry, s, tab);		ret = TRUE; }
	if (p->arrayApi & ARRAY_API_TRAVEL)
	{ ListType_source_travel(fp, tn, p->type, p->entry, s, tab);	ret = TRUE; }
	if (p->arrayApi & ARRAY_API_FIND)
	{ ListType_source_find(fp, tn, p->type, p->entry, s, tab);		ret = TRUE; }
	if (p->arrayApi & ARRAY_API_GETHEAD)
	{ ListType_source_getHead(fp, tn, p->type, p->entry, s, tab);	ret = TRUE; }
	if (p->arrayApi & ARRAY_API_GETTAIL)
	{ ListType_source_getTail(fp, tn, p->type, p->entry, s, tab);	ret = TRUE; }
	if (p->arrayApi & ARRAY_API_COUNT)
	{ ListType_source_count(fp, tn, p->type, p->entry, s, tab);		ret = TRUE; }

	if (t_api & OBJECT_API_NEW)				{ ArrayInfo_sourceNew(fp, tn, t_api, p, s, tab);		ret = TRUE; }
	if (t_api & OBJECT_API_CLONE)			{ ListType_source_clone(fp, tn, p->type, p->entry, p->isReferenced, s, tab); ret = TRUE; }
	if (t_api & OBJECT_API_DEL)				{ ListType_source_del(fp, tn, p->type, s, tab);			ret = TRUE; }

	if (ListType_source_dump(fp, tn, p->type, p->arrayApi, p->dumpPrefix, p->entry, s, tab)) ret = TRUE;

	return ret;
}
// ArrayInfo source
///////////////////////////////////////////////////////////////////////////////

#if 0
void ArrayInfo_testHeader(FILE *fp, PublishSpec *spec, u32_t api, str_t name, ArrayInfo *p, int tab)
{
	TP(fp, tab); fprintf(fp, "%s %s %s *%s_test(%s *src, %s *err);\n",
			spec->base->cpplink, spec->base->dllport, name, name, name, spec->error->type);
	fprintf(fp, "\n");
}

void ArrayInfo_testSource(FILE *fp, PublishSpec *spec, u32_t api, str_t name, ArrayInfo *p, int tab)
{
	char buf[1024];
	TP(fp, tab); fprintf(fp, "%s *%s_test(%s *src, %s *err)\n", name, name, name, spec->error->type);
	TP(fp, tab++); fprintf(fp, "{\n");
	TP(fp, tab); fprintf(fp, "%s _err = %s, *errp = %s;\n", spec->error->type, spec->error->defaultVal, spec->error->code(spec->error, buf, ErrorCodeGenType_init, "*err", "_err"));
	TP(fp, tab); fprintf(fp, "%s *dst = %s%s(errp);\n", name, name, spec->postFix->_new);
	TP(fp, tab); fprintf(fp, "if (dst == NULL) %s;\n", spec->error->code(spec->error, buf, ErrorCodeGenType_print, "*errp", NULL));
	TP(fp, tab); fprintf(fp, "else\n");
	TP(fp, tab++); fprintf(fp, "{\n");
	TP(fp, tab); fprintf(fp, "int temp, size = 0;\n");
	TP(fp, tab); fprintf(fp, "unsigned char *buf = NULL;\n");
	if (spec->pthread) { TP(fp, tab); fprintf(fp, "pthread_cleanup_push((void (*)(void *))%s%s, (void *)dst);\n\n", name, spec->postFix->_del); }

	TP(fp, tab); fprintf(fp, "if ((size = %s%s(NULL, src)) == 0) %s;\n",name, spec->postFix->_enc,
		   	spec->error->code(spec->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EFAULT"));
	TP(fp, tab); fprintf(fp, "else if ((buf = (unsigned char *)%s(size%s)) == NULL) %s;\n",
			spec->mem->malloc, spec->mem->allocNeedErrorPtr ? ", errp" : "",
			spec->error->code(spec->error, buf, ErrorCodeGenType_print, "*errp", NULL));
	TP(fp, tab); fprintf(fp, "else\n");
	TP(fp, tab++); fprintf(fp, "{\n");
	if (spec->pthread) { TP(fp, tab); fprintf(fp, "pthread_cleanup_push((void (*)(void *))%s, (void *)buf);\n\n", spec->mem->cancel); }
	TP(fp, tab); fprintf(fp, "if (%s%s(buf, src) == 0) %s;\n", name, spec->postFix->_enc,
			spec->error->code(spec->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EFAULT"));
	TP(fp, tab); fprintf(fp, "else if ((temp = %s%s(dst, buf)) == 0) %s;\n", name, spec->postFix->_dec,
			spec->error->code(spec->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EFAULT"));
	TP(fp, tab); fprintf(fp, "else if (temp != size) %s;\n", spec->error->code(spec->error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EFAULT"));
	// DZ1XXX : Element Check Code
	TP(fp, tab); fprintf(fp, "\n");
	if (spec->pthread) { TP(fp, tab); fprintf(fp, "pthread_cleanup_pop(1); // ((void (*)(void *))%s, (void *)buf);\n", spec->mem->cancel); }
	TP(fp, --tab); fprintf(fp, "}\n");

	if (spec->pthread) { TP(fp, tab); fprintf(fp, "pthread_cleanup_pop(1); // ((void (*)(void *)%s%s, (void *)buf);\n", name, spec->postFix->_del); }
	TP(fp, --tab); fprintf(fp, "}\n");
	TP(fp, tab); fprintf(fp, "return dst;\n");
	TP(fp, --tab); fprintf(fp, "}\n\n");
}
#endif