#include <dz1_str.h>
#include <dz1_aatree.h>
#include <dz1_thread_stdio.h>
#include "publish_c.h"
#include "publish_asnconv.h"
#include "publish_struct_util.h"
#include "publish_list_util.h"
#include "publish_list_index_c.h"

///////////////////////////////////////////////////////////////////////////////
// IndexInfo header
bool_t IndexInfo_header(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, IndexInfo *p, PublishSpec *s, int tab)
{
	ListType_header(fp, tn, ArrayType_unique, t_api, p->indexApi, p->entry, p->isForward, TRUE, s, tab);
	return TRUE;
}
// IndexInfo header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// IndexInfo header : ASN Converter
bool_t IndexInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_ant, u32_t api, IndexInfo *p, PublishSpec *s, int tab)
{
	bool_t printed = FALSE;
	printed = Publish_asnConvDeclare(fp, api, s, tn, "ASN1List", tab);
	if (printed) fprintf(fp, "\n");
	return printed;
}
// IndexInfo header : ASN Converter
///////////////////////////////////////////////////////////////////////////////

static bool_t _prepare_compare(FILE *fp, str_t tn, IndexInfo *p, char *e_cmp_fn, size_t e_cmp_fn_sz, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	str_t e_tn = ObjectInfo_nameOf(p->entry);
	PublishPostFix *postFix = s->postFix;
	bool_t use_local_cmp = p->keys.valid == 0 ? FALSE : TRUE;
	//////////////////////////////////////////////
	// Prepare compare function
	if (use_local_cmp)
	{

		bool_t e_is_prim = ObjectInfo_isPrimitive(p->entry);
		bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(p->entry) ? TRUE : FALSE;

		ObjectType _t_ = ObjectInfo_typeOf(p->entry);

		if (_t_ != ObjectType_structure) 
			Dz1ThreadA_ftprintf(fp, tab,	"#error \"%s is not structure\"\n", e_tn);
		else
		{
			bool_t needElse = TRUE;
			str_t e_cmp_ptr = e_is_primptr ? "" : "*";

			int i;
			IndexInfoKey *keys = &p->keys;
			ObjectInfo *origin = ObjectInfo_getOrigin(p->entry);
			StructureInfo *si = origin->info;
			StructMemberEntry *entry = NULL;

			_std_snprintfA(e_cmp_fn, e_cmp_fn_sz, "_%s%s", tn, postFix->_cmp);

			Dz1ThreadA_ftprintf(fp, tab,	"static int %s(%s %sa, %s %sb)\n", e_cmp_fn, e_tn, e_cmp_ptr, e_tn, e_cmp_ptr);
			Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
			Dz1ThreadA_ftprintf(fp, tab,		"int ret = 0;\n");
			Dz1ThreadA_ftprintf(fp, tab,		"if (a == NULL && b == NULL) ret = 0;\n");
			Dz1ThreadA_ftprintf(fp, tab,		"else if (a == NULL /* && b == NULL*/) ret = -1;\n");
			Dz1ThreadA_ftprintf(fp, tab,		"else if (/*a == NULL &&*/ b == NULL) ret = 1;\n");
			for (i = 0; i < keys->valid; i++)
			{
				if ((entry = StructMemberList_find(si->members, keys->names[i])) == NULL) 
					Dz1ThreadA_ftprintf(fp, tab,"#error \"%s member %s not exist \"\n", e_tn, keys->names[i]);
				else StructMemberEntry_cmp_code(fp, tn, "a", "b", entry, ObjectInfo_getOrigin(entry->type), s, tab, &needElse);
			}
			Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
			Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
			ret = TRUE;
		}
	}
	else if (ObjectInfo_apiOf(p->entry, s) & OBJECT_API_CMP)
	{
		str_t e_fx = ObjectInfo_prefixOf(p->entry, s);
		_std_snprintfA(e_cmp_fn, e_cmp_fn_sz, "%s%s", e_fx, postFix->_cmp);
		ret = TRUE;
	}
	else Dz1ThreadA_ftprintf(fp, tab,	"#error \"%s is not has compare API\"\n", e_tn);
	// Prepare compare function
	//////////////////////////////////////////////
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// IndexInfo source : NEW function
static void IndexInfo_sourceNew(FILE *fp, str_t tn, IndexInfo *p, PublishSpec *s, int tab)
{
	char buf[1024], e_cmp_fn[1024] = { 0, };
	PublishCastSpec *cast = s->cast;
	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;
	str_t mem_arg = mem->allocNeedErrorPtr ? ", errp" : "";

	PublishArraySpec *as = s->arraySpec[ArrayType_unique];

	str_t e_tn = ObjectInfo_nameOf(p->entry);
	str_t e_fx = ObjectInfo_prefixOf(p->entry, s);

	_prepare_compare(fp, tn, p, e_cmp_fn, sizeof(e_cmp_fn), s, tab);

	Dz1ThreadA_ftprintf(fp, tab,		"%s *%s%s(%s *err)\n", tn, tn, postFix->_new, error->type);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"%s _err = %s, *errp = %s;\n", error->type, error->defaultVal, error->code(error, buf, ErrorCodeGenType_init, "*err", "_err"));
	Dz1ThreadA_ftprintf(fp, tab,			"%s *ret = (%s *)%s(sizeof(%s), 1%s);\n", tn, tn, mem->calloc, tn, mem_arg);
	Dz1ThreadA_ftprintf(fp, tab,			"if (ret == NULL) %s;\n", error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,			"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,			"{\n");
	if (s->pthread) 
		Dz1ThreadA_ftprintf(fp, tab,			"pthread_cleanup_push(%s%s, (void *)&ret);\n\n", tn, postFix->_delAndSetNull);

	if (Dz1Str_isVoid(e_cmp_fn) == FALSE)
	{
		Dz1ThreadA_ftprintf(fp, tab,			"if ((ret->storage = %s(%s%s, ", as->apiName(as, buf, ArraySpecApiType_new, "*p->storage"), s->cast->cmp, e_cmp_fn);
		if (p->isReferenced)	fprintf(fp,									 "NULL, ");
		else					fprintf(fp,									 "%s%s%s, ", cast->del, e_fx, postFix->_del);
		fprintf(fp,																	 "NULL, errp)) == NULL) %s;\n",
												error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	}
	else Dz1ThreadA_ftprintf(fp, tab,			"#error \"%s's API is not support compare, delete or dump\"\n", e_tn);

	Dz1ThreadA_ftprintf(fp, tab,				"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,				"{\n");

	ListType_source_newApi(fp, tn, ArrayType_unique, p->indexApi, e_cmp_fn, s, tab);

	Dz1ThreadA_ftprintf(fp, tab,					"%s;\n", error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, --tab,				"}\n");
	if (s->pthread)
	{
		TP(fp, tab);
		Dz1ThreadA_ftprintf(fp, tab,			"pthread_cleanup_pop(%s); // (%s%s, (void *)&ret);\n",
												error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL), tn, postFix->_delAndSetNull);
	}
	Dz1ThreadA_ftprintf(fp, --tab,			"}\n");
	Dz1ThreadA_ftprintf(fp, tab,			"return ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n\n");
}
// IndexInfo source : NEW function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// IndexInfo source
bool_t IndexInfo_source(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, IndexInfo *p, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;

	if (p->indexApi & ARRAY_API_ADD)		{ ListType_source_add(fp, tn, ArrayType_unique, p->entry, s, tab);		ret = TRUE; }
	if (p->indexApi & ARRAY_API_REMOVE)		{ ListType_source_remove(fp, tn, ArrayType_unique, p->entry, s, tab);	ret = TRUE; }
	if (p->indexApi & ARRAY_API_EXTRACT)	{ ListType_source_extract(fp, tn, ArrayType_unique, p->entry, s, tab);	ret = TRUE; }
	if (p->indexApi & ARRAY_API_ARRAY)		{ ListType_source_array(fp, tn, ArrayType_unique, p->entry, s, tab);	ret = TRUE; }
	if (p->indexApi & ARRAY_API_TRAVEL)		{ ListType_source_travel(fp, tn, ArrayType_unique, p->entry, s, tab);	ret = TRUE; }
	if (p->indexApi & ARRAY_API_FIND)		{ ListType_source_find(fp, tn, ArrayType_unique, p->entry, s, tab);		ret = TRUE; }
	if (p->indexApi & ARRAY_API_GETHEAD)	{ ListType_source_getHead(fp, tn, ArrayType_unique, p->entry, s, tab);	ret = TRUE; }
	if (p->indexApi & ARRAY_API_GETTAIL)	{ ListType_source_getTail(fp, tn, ArrayType_unique, p->entry, s, tab);	ret = TRUE; }
	if (p->indexApi & ARRAY_API_COUNT)		{ ListType_source_count(fp, tn, ArrayType_unique, p->entry, s, tab);	ret = TRUE; }

	if (t_api & OBJECT_API_NEW)				{ IndexInfo_sourceNew(fp, tn, p, s, tab);	ret = TRUE; }
	if (t_api & OBJECT_API_CLONE)			{ ListType_source_clone(fp, tn, ArrayType_unique, p->entry, p->isReferenced, s, tab); ret = TRUE; }
	if (t_api & OBJECT_API_DEL)				{ ListType_source_del(fp, tn, ArrayType_unique, s, tab);	ret = TRUE; }

	if (ListType_source_dump(fp, tn, ArrayType_unique, p->indexApi, p->dumpPrefix, p->entry, s, tab)) ret = TRUE;

	return ret;
}
// IndexInfo source
///////////////////////////////////////////////////////////////////////////////
