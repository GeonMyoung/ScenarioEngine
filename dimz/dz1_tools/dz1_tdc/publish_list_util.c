#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include "publish_util.h"
#include "publish_list_util.h"

// is_primitive	: int real enum void str function
// is_address	:                    str
// is_data		: int real enum          function

// -------------+---------------+---------------+---------------+
// api argument	|   prim data	|   prim ptr	|   cstr data	|
// -------------+---------------+---------------+---------------+
// count		| -				| -				| -				|
// travel		| type *p		| type p		| type *p		|	primitive ptr or not
// get_array	| type *p		| type p		| type *p		|	primitive ptr or not
// add			| type data		| type data		| type *data	|	primitive or not
// -------------+---------------+---------------+---------------+
// remove		| type *ptr/key	| type ptr/key	| type *ptr/key	|	primitive ptr or not
// extract		| type *ptr/key	| type ptr/key	| type *ptr/key	|	primitive ptr or not
// find			| type key		| type key		| type *key		|	primitive or not
// getHead		| -				| -				| -				|
// getTail		| -				| -				| -				|
// cmp			| type *a/*b	| type a/b		| type *a/*b	|	primitive ptr or not
// -------------+---------------+---------------+---------------+

// -------------+-----------+-----------+-----------+
// api return	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// count		| -			| -			| -			|
// travel		| -			| -			| -			|
// get_array	| type *	| type *	| type **	|	primitive or not
// add			| -			| -			| -			|
// -------------+-----------+-----------+-----------+
// remove		| -			| -			| -			|
// extract		| type *	| type		| type *	|	primitive ptr or not
// find			| type *	| type		| type *	|	primitive ptr or not
// getHead		| type *	| type		| type *	|	primitive ptr or not
// getTail		| type *	| type		| type *	|	primitive ptr or not
// cmp			| -			| -			| -			|
// -------------+-----------+-----------+-----------+

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo header : Type publish
bool_t ListType_header_typedef(FILE *fp, str_t tn, ArrayType at, u32_t a_api, bool_t elem_fwd, ObjectInfo *elem, bool_t e_cmp, PublishSpec *s, int tab)
{
	PublishErrorSpec *error = s->error;
	PublishArraySpec *as = s->arraySpec[at];

	NativeTypeSpec *bool_sp = s->findPrimitive(s, BOOLTYPE_NAME);
	str_t bool_tn = bool_sp == NULL ? "int" : bool_sp->native;

	str_t e_tn = ObjectInfo_nameOf(elem);
	u32_t e_api = ObjectInfo_apiOf(elem, s);
	str_t e_fwd = elem_fwd ? "struct " : "";

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;
	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_arg = at == ArrayType_normal ? "ptr" : "key";
	str_t most_ptr = e_is_primptr ? "" : "*";

	Dz1ThreadA_ftprintf(fp, tab,		"typedef struct %s\n", tn);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"%s *storage;\n", "void");
	/////////////////////////////////////////////////////////////////////////////////////////
	if (a_api & ARRAY_API_COUNT)	//			                           1
		Dz1ThreadA_ftprintf(fp, tab,		"unsigned int (*count)(struct %s *p);\n", tn);
	if (a_api & ARRAY_API_TRAVEL)
	{	
		str_t e_trvl_ptr = e_is_primptr ? " " : " *";	//					  2      3                     4 5 6
		Dz1ThreadA_ftprintf(fp, tab,		"%s (*travel)"			"(struct %s *p, %s (*func)(void *ptr, %s%s%sentry), void *ptr);\n", 
											error->type, tn, error->type, e_fwd, e_tn, e_trvl_ptr);
		Dz1ThreadA_ftprintf(fp, tab,		"%s (*travelForward)"	"(struct %s *p, %s (*func)(void *ptr, %s%s%sentry), void *ptr);\n", 
											error->type, tn, error->type, e_fwd, e_tn, e_trvl_ptr);
		Dz1ThreadA_ftprintf(fp, tab,		"%s (*travelBackward)"	"(struct %s *p, %s (*func)(void *ptr, %s%s%sentry), void *ptr);\n", 
											error->type, tn, error->type, e_fwd, e_tn, e_trvl_ptr);
	}
	if (a_api & ARRAY_API_ARRAY)	//		  1 2 3                      4                             5
	{
		str_t ret_ptr = e_is_prim  ? "" : "*";
		Dz1ThreadA_ftprintf(fp, tab,		"%s%s *%s(*get_array)(struct %s *p, unsigned int *ret_cnt, %s *err);\n", 
											e_fwd, e_tn, ret_ptr, tn, error->type);	// 1 2 3 4 5
	}
	if (a_api & ARRAY_API_ADD)
	{
		str_t e_arg_ptr = e_is_prim ? "" : "*";	//             2      3 4  5		   1            2   3      4     5
		Dz1ThreadA_ftprintf(fp, tab,		"%s (*add)(struct %s *p, %s%s %sdata);\n", error->type, tn, e_fwd, e_tn, e_arg_ptr);
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	if (a_api & ARRAY_API_REMOVE)	//		 0						1      2 3  4 5	   0		1   2      3     4         5
		Dz1ThreadA_ftprintf(fp, tab,		"%s (*remove)(struct %s *p, %s%s %s%s);\n",bool_tn, tn, e_fwd, e_tn, most_ptr, e_arg);
	if (a_api & ARRAY_API_EXTRACT)
	{
		if (as->map[ArraySpecApiType_extract])
		{									//1 2  3                   4      5 6  7 8
			Dz1ThreadA_ftprintf(fp, tab,	"%s%s %s(*extract)(struct %s *p, %s%s %s%s);\n",
											e_fwd, e_tn, most_ptr, tn,		// 1 2 3 4
											e_fwd, e_tn, most_ptr, e_arg);	// 5 6 7 8
		}
		else Dz1ThreadA_ftprintf(fp, tab,	"#error Library not support 'extract' function\n");
	}
	if (a_api & ARRAY_API_FIND)
	{
		str_t e_arg_ptr = e_is_prim ? "" : "*";
		//                                    1 2  3                4      5 6  7
		Dz1ThreadA_ftprintf(fp, tab,		"%s%s %s(*find)(struct %s *p, %s%s %skey);\n",
											e_fwd, e_tn, most_ptr, tn,	// 1 2 3 4
											e_fwd, e_tn, e_arg_ptr);	// 5 6 7
	}
	if (a_api & ARRAY_API_GETHEAD)	//		  1 2  3                   4
		Dz1ThreadA_ftprintf(fp, tab,		"%s%s %s(*getHead)(struct %s *p);\n", e_fwd, e_tn, most_ptr, tn);
	if (a_api & ARRAY_API_GETTAIL)	//		  1 2  3                   4
		Dz1ThreadA_ftprintf(fp, tab,		"%s%s %s(*getTail)(struct %s *p);\n", e_fwd, e_tn, most_ptr, tn);
	/////////////////////////////////////////////////////////////////////////////////////////
	if (e_cmp)	//										 1 2  3    4 5  6
		Dz1ThreadA_ftprintf(fp, tab,		"int (*cmp)(%s%s %sa, %s%s %sb);\n", e_fwd, e_tn, most_ptr, e_fwd, e_tn, most_ptr);
	/////////////////////////////////////////////////////////////////////////////////////////
	Dz1ThreadA_ftprintf(fp, --tab,		"} %s;\n", tn);
	fprintf(fp, "\n");
	return TRUE;
}
// ArrayInfo header : Type publish
///////////////////////////////////////////////////////////////////////////////

bool_t ListType_header(FILE *fp, str_t tn, ArrayType a_type, u32_t t_api, u32_t l_api, ObjectInfo *elem, bool_t elem_is_fwd, bool_t elem_has_cmp, PublishSpec *s, int tab)
{
	PublishBasicSpec *base = s->base;
	PublishPostFix *postFix = s->postFix;
	PublishErrorSpec *error = s->error;
	PublishArraySpec *aSpec = s->arraySpec[a_type];

	ListType_header_typedef(fp, tn, a_type, l_api, elem_is_fwd, elem, elem_has_cmp, s, tab);

	if (t_api & OBJECT_API_NEW)		Dz1ThreadA_ftprintf(fp, tab,	"%s %s %s *%s%s(%s *err);\n", base->cpplink, base->dllport, tn, tn, postFix->_new, error->type);
	if (t_api & OBJECT_API_GEN)		Dz1ThreadA_ftprintf(fp, tab,	"static __inline__ %s *%s%s(%s *err) { return %s%s(err); }\n", tn, tn, postFix->_gen, error->type, tn, postFix->_new);
	if (t_api & OBJECT_API_CLONE)	Dz1ThreadA_ftprintf(fp, tab,	"%s %s %s *%s%s(%s *src, %s *err);\n", base->cpplink, base->dllport, tn, tn, postFix->_clone, tn, error->type);
	if (t_api & OBJECT_API_DEL)
	{
		Dz1ThreadA_ftprintf(fp, tab,	"%s %s void %s%s(%s *p);\n", base->cpplink, base->dllport, tn, postFix->_purge, tn);
		Dz1ThreadA_ftprintf(fp, tab,	"%s %s void %s%s(%s *p);\n", base->cpplink, base->dllport, tn, postFix->_del, tn);
	}
	if (t_api & OBJECT_API_DELANDSETNULL) Type_header_delAndSetNull(fp, tn, FALSE, s, tab);

	// t_api는 ARRAY_ELTRY_API_MASK에 할당된 entry api 값을 가져온 상태
	switch(l_api & (ARRAY_API_USER_DUMP | ARRAY_API_NO_DUMP))
	{	// dump related flag is set
	case (ARRAY_API_USER_DUMP | ARRAY_API_NO_DUMP):					// dump is set
		t_api &= ~(OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE);	// -> ignore entry's MBCS or WIDE
		break;		
	case ARRAY_API_NO_DUMP:											// nodump is set
		t_api &= ~(OBJECT_API_DUMP | OBJECT_API_USER_DUMP);			// -> clear entry's dump related flag
		break;			
	case ARRAY_API_USER_DUMP:										// userdump is set
		t_api |= (OBJECT_API_DUMP | OBJECT_API_USER_DUMP);			// -> make sure userdump
		break;
	default:														// no option
		break;														// -> inherit entry's flags
	}

	switch(l_api & (ARRAY_API_USER_FDUMP | ARRAY_API_NO_FDUMP))
	{	// fdump related flag is set
	case (ARRAY_API_USER_FDUMP | ARRAY_API_NO_FDUMP):				// fdump is set
		t_api &= ~(OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE);	// -> ignore entry's MBCS or WIDE
		break;
	case ARRAY_API_NO_FDUMP:										// fnodump is set
		t_api &= ~(OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP);		// -> clear entry's fdump related flag
		break;		
	case ARRAY_API_USER_FDUMP:										// userdump is set
		t_api |= (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP);		// -> make sure userdump
		break;
	default:														// no option
		break;														// -> inherit entry's flags
	}

	_dump_api_header_publish(fp, tn, t_api, "*p", TRUE, s, tab);
	fprintf(fp, "\n");

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : COUNT function
static void _ListType_source_count(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024], fn[1024];
	PublishCastSpec *cast = s->cast;
	PublishErrorSpec *error = s->error;
	PublishArraySpec *as = s->arraySpec[a_type];

	str_t e_tn = ObjectInfo_nameOf(elem);

	sprintf(fn, "_%s_count", tn);
	Dz1ThreadA_ftprintf(fp, tab,	"static %s %s(void *ptr, %s *data)\n", error->type, fn, e_tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s err = %s, *errp = &err;\n", error->type, error->code(error, buf, ErrorCodeGenType_init, "err", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"int *p = (int *)ptr;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"(*p)++;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return err;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");

	Dz1ThreadA_ftprintf(fp, tab,	"static int %s_count(%s *p)\n", tn, tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"int ret = 0;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s err = %s;\n", error->type, 
										as->code(as, cast, buf, ArraySpecApiType_travelForward, "*p->storage", fn, "(void *)&ret", NULL, NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"if (%s) ", error->code(error, buf, ErrorCodeGenType_probe, "err", NULL));
									fprintf(fp, "%s;\n", error->code(error, buf, ErrorCodeGenType_print, "err", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}

void ListType_source_count(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	PublishArraySpec *as = s->arraySpec[a_type];
	if (as->map[ArraySpecApiType_cnt] == NULL) 
		_ListType_source_count(fp, tn, a_type, elem, s, tab);
	else
	{
		char buf[1024];
		Dz1ThreadA_ftprintf(fp, tab,	"static unsigned int %s_count(%s *p)\n", tn, tn);
		Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
		Dz1ThreadA_ftprintf(fp, tab,		"unsigned int ret = %s;\n", 
											as->code(as, s->cast, buf, ArraySpecApiType_cnt, "*p->storage", NULL, NULL, NULL, NULL));
		Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
		Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
	}
}
// ArrayInfo source : COUNT function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : TRAVEL function
// -------------+---------------+---------------+---------------+
// api argument	|   prim data	|   prim ptr	|   cstr data	|
// -------------+---------------+---------------+---------------+
// travel		| type *p		| type p		| type *p		|	primitive ptr or not
void ListType_source_travel(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024];

	PublishArraySpec *as = s->arraySpec[a_type];

	PublishErrorSpec *error = s->error;
	PublishCastSpec *cast = s->cast;

	str_t e_tn = ObjectInfo_nameOf(elem);

	bool_t e_is_primptr = ObjectInfo_isPrimitive(elem) && ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_ptr = e_is_primptr ? "" : "*";
	//										 1  2                3      4                     5  6
	Dz1ThreadA_ftprintf(fp, tab,	"static %s %s_travelForward(%s *p, %s (*func)(void *ptr, %s %sdata), void *ptr)\n", 
									error->type, tn, tn, error->type, e_tn, e_ptr);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");

	Dz1ThreadA_ftprintf(fp, tab,		"return %s;\n", 
										as->code(as, cast, buf, ArraySpecApiType_travelForward, "*p->storage", "func", "ptr", NULL, NULL));
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
	//										 1  2                 3      4                     5  6
	Dz1ThreadA_ftprintf(fp, tab,	"static %s %s_travelBackward(%s *p, %s (*func)(void *ptr, %s %sdata), void *ptr)\n",
									error->type, tn, tn, error->type, e_tn, e_ptr);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return %s;\n", 
										as->code(as, cast, buf, ArraySpecApiType_travelBackward, "*p->storage", "func", "ptr", NULL, NULL));
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// ArrayInfo source : TRAVEL function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : ARRAY function
// -------------+---------------+---------------+---------------+
// api argument	|   prim data	|   prim ptr	|   cstr data	|
// -------------+---------------+---------------+---------------+
// get_array	| type *p		| type p		| type *p		|	primitive ptr or not

// -------------+-----------+-----------+-----------+
// api return	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// get_array	| type *	| type *	| type **	|	primitive or not
void ListType_source_array(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024];
	str_t e_tn = ObjectInfo_nameOf(elem);

	PublishErrorSpec *error = s->error;
	PublishMemFuncSpec *mem = s->mem;
	str_t mem_arg = mem->allocNeedErrorPtr ? ", errp" : "";

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = (e_is_prim && ObjectInfo_isAddress(elem)) ? TRUE : FALSE;
	bool_t e_is_primdata = (e_is_prim && !ObjectInfo_isAddress(elem)) ? TRUE : FALSE;

	str_t e_ret_ptr = e_is_prim ? "" : "*";
	str_t e_asgn_ptr = e_is_primdata ? "*" : "";
	str_t e_arg_ptr = e_is_primptr ? "" : "*";

	Dz1ThreadA_ftprintf(fp, tab,	"typedef struct %sMkArrArg\n", tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s *%sarr;\n", e_tn, e_ret_ptr);
	Dz1ThreadA_ftprintf(fp, tab,		"unsigned int idx;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"} %sMkArrArg;\n\n", tn);
	Dz1ThreadA_ftprintf(fp, tab,	"static %s _%s_get_array(void *ptr, %s %sp)\n", error->type, tn, e_tn, e_arg_ptr);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s err = %s;\n", error->type, error->code(error, buf, ErrorCodeGenType_init, "errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"%sMkArrArg *arg = (%sMkArrArg *)ptr;\n", tn, tn);
 	Dz1ThreadA_ftprintf(fp, tab,		"arg->arr[arg->idx++] = %sp;\n", e_asgn_ptr);
	Dz1ThreadA_ftprintf(fp, tab,		"return err;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
	//										 1   2 3            4                             5           1     2      3   4   5
	Dz1ThreadA_ftprintf(fp, tab,	"static %s *%s%s_get_array(%s *p, unsigned int *ret_cnt, %s *err)\n", e_tn, e_ret_ptr, tn, tn, error->type);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s _err = %s, *errp = err == NULL ? &_err : err;\n", error->type, error->code(error, buf, ErrorCodeGenType_init, "errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"%s *%sret = NULL;\n", e_tn, e_ret_ptr);
	Dz1ThreadA_ftprintf(fp, tab,		"unsigned int cnt = 0;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"if (p == NULL) %s;\n", error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EINVAL"));
	Dz1ThreadA_ftprintf(fp, tab,		"else if ((ret = (%s *%s)%s(sizeof(%s *), (cnt = p->count(p)) + 1%s)) == NULL) %s;\n",
										e_tn, e_ret_ptr, mem->calloc, e_tn, mem_arg, error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"%sMkArrArg arg = { ret, 0 };\n", tn);
	if (s->pthread)
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_push(%s, (void *)ret);\n\n", s->mem->cancel);
	Dz1ThreadA_ftprintf(fp, tab,			"*errp = p->travel(p, _%s_get_array, (void *)&arg);\n", tn);
	Dz1ThreadA_ftprintf(fp, tab,			"if (%s) ", error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL));
												fprintf(fp, "%s;\n", error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));	// avoid but overwrite
	Dz1ThreadA_ftprintf(fp, tab,			"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,			"{\n");
	Dz1ThreadA_ftprintf(fp, tab,				"if (ret_cnt) (*ret_cnt) = cnt;\n");
	Dz1ThreadA_ftprintf(fp, tab,				"%s;\n", error->code(error, buf, ErrorCodeGenType_clear, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, --tab,			"}\n");
	if (s->pthread)
		Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_pop(%s); // (%s, (void *)ret);\n", error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL), mem->cancel);
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	Dz1ThreadA_ftprintf(fp, tab,		"if (%s) ret = NULL;\n", error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"return ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// ArrayInfo source : ARRAY function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : ADD function
// -------------+---------------+---------------+---------------+
// api argument	|   prim data	|   prim ptr	|   cstr data	|
// -------------+---------------+---------------+---------------+
// add			| type data		| type data		| type *data	|	primitive or not
void ListType_source_add(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024];

	PublishArraySpec *as = s->arraySpec[a_type];

	PublishErrorSpec *error = s->error;
	PublishCastSpec *cast = s->cast;
	PublishMemFuncSpec *mem = s->mem;
	PublishPostFix *postFix = s->postFix;
	str_t mem_arg = mem->allocNeedErrorPtr ? ", &err" : "";

	str_t e_tn = ObjectInfo_nameOf(elem);
	str_t e_fx = ObjectInfo_prefixOf(elem, s);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_ptr = e_is_prim ? "" : "*";
	//										 1  2      3      4  5          1            2   3   4     5
	Dz1ThreadA_ftprintf(fp, tab,		"static %s %s_add(%s *p, %s %sdata)\n", error->type, tn, tn, e_tn, e_ptr);

	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"%s err = %s;\n", error->type, error->code(error, buf, ErrorCodeGenType_init, "err", NULL));
	if (e_is_primdata)
	{	// primitive data
		bool_t _else = FALSE;
		Dz1ThreadA_ftprintf(fp, tab,		"%s *temp = NULL;\n", e_tn);
		if (a_type == ArrayType_unique)
		{	// Unique -> find first
			Dz1ThreadA_ftprintf(fp, tab,	"if (%s) ", as->code(as, cast, buf, ArraySpecApiType_find, "*p->storage", "(void *)&data", NULL, NULL, NULL));
										fprintf(fp, "%s;\n", error->code(error, buf, ErrorCodeGenType_setAndPrint, "err", "EEXIST"));
			_else = TRUE;
		}
		Dz1ThreadA_ftprintf(fp, tab,		"%sif ((temp = (%s *)%s(sizeof(%s), 1%s)) == NULL) %s;\n",
											_else ? "else " : "",				// 1
											e_tn, mem->calloc, e_tn, mem_arg,	// 2 3 4 5
											error->code(error, buf, ErrorCodeGenType_print, "err", NULL));
		Dz1ThreadA_ftprintf(fp, tab,		"else\n");
		Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
		if (s->pthread)
			Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_push((void (*)(void *))%s%s, (void *)temp);\n\n", e_fx, postFix->_del);
		Dz1ThreadA_ftprintf(fp, tab,			"memcpy(temp, &data, sizeof(%s));\n", e_tn);
		Dz1ThreadA_ftprintf(fp, tab,			"err = %s;\n", as->code(as, cast, buf, ArraySpecApiType_add, "*p->storage", "temp", NULL, NULL, NULL));

		Dz1ThreadA_ftprintf(fp, tab,			"if (%s) ", error->code(error, buf, ErrorCodeGenType_probe, "err", NULL));
											fprintf(fp, "%s;\n", error->code(error, buf, ErrorCodeGenType_print, "err", NULL));
		if (s->pthread)
		{
			fprintf(fp, "\n");
			Dz1ThreadA_ftprintf(fp, tab,		"pthread_cleanup_pop(%s); // ((void (*)(void *))%s%s, (void *)temp);\n\n",
												error->code(error, buf, ErrorCodeGenType_probe, "err", NULL), e_fx, postFix->_del);
		}
		Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	}
	else
	{	// primitive ptr or else data
		if (a_type == ArrayType_unique)
		{	// Unique _______________
			Dz1ThreadA_ftprintf(fp, tab,	"if (%s) ", as->code(as, cast, buf, ArraySpecApiType_find, "*p->storage", "data", NULL, NULL, NULL));
										fprintf(fp, "%s;\n", error->code(error, buf, ErrorCodeGenType_setAndPrint, "err", "EEXIST"));
			Dz1ThreadA_ftprintf(fp, tab,	"else\n");
			Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
		}

		Dz1ThreadA_ftprintf(fp, tab,		"err = %s;\n", as->code(as, cast, buf, ArraySpecApiType_add, "*p->storage", "data", NULL, NULL, NULL));
		Dz1ThreadA_ftprintf(fp, tab,		"if (%s) ", error->code(error, buf, ErrorCodeGenType_probe, "err", NULL));
										fprintf(fp, "%s;\n", error->code(error, buf, ErrorCodeGenType_print, "err", NULL));

		if (a_type == ArrayType_unique)
		{	// Unique ^^^^^^^^^^^^^^^
			Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
		}
	}
	Dz1ThreadA_ftprintf(fp, tab,			"return err;\n");
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n\n");
}
// ArrayInfo source : ADD function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : REMOVE function
// -------------+---------------+---------------+---------------+
// api argument	|   prim data	|   prim ptr	|   cstr data	|
// -------------+---------------+---------------+---------------+
// remove		| type *ptr|key	| type ptr/key	| type *ptr/key	|	primitive or not
void ListType_source_remove(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024];

	NativeTypeSpec *bool_sp = s->findPrimitive(s, BOOLTYPE_NAME);
	str_t bool_tn = bool_sp == NULL ? "int" : bool_sp->native;

	PublishArraySpec *as = s->arraySpec[a_type];

   	str_t e_param = (a_type == ArrayType_unique || a_type == ArrayType_ordered) ? "key" : "ptr";
// 	str_t codeParam = NULL;
	str_t e_tn = ObjectInfo_nameOf(elem);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;
	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_arg_ptr = e_is_primptr ? "" : "*";
	//										 1  2         3      4  5 6      1        2   3     4          5   6
	Dz1ThreadA_ftprintf(fp, tab,	"static %s %s_remove(%s *p, %s %s%s)\n", bool_tn, tn, tn, e_tn, e_arg_ptr, e_param);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");

	Dz1ThreadA_ftprintf(fp, tab,		"return %s;\n", 
										as->code(as, s->cast, buf, ArraySpecApiType_remove, "*p->storage", e_param, NULL, NULL, NULL));
// 	if (a_type == ArrayType_ordered || a_type == ArrayType_unique)
// 	{	// comparable entry
// 		codeParam = e_is_primdata ? "&key" : e_param;
// 		Dz1ThreadA_ftprintf(fp, tab,	"%s;\n", as->code(as, s->cast, buf, ArraySpecApiType_remove, "*p->storage", codeParam, NULL, NULL, NULL));
// 	}
// 	else
// 	{
// 		Dz1ThreadA_ftprintf(fp, tab,	"%s;\n", as->code(as, s->cast, buf, ArraySpecApiType_remove, "*p->storage", "ptr", NULL, NULL, NULL));
// 	}
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// ArrayInfo source : REMOVE function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : EXTRACT function
// -------------+---------------+---------------+---------------+
// api argument	|   prim data	|   prim ptr	|   cstr data	|
// -------------+---------------+---------------+---------------+
// extract		| type *ptr/key	| type data/key	| type*data/key	|	primitive ptr or not

// -------------+-----------+-----------+-----------+
// api return	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// extract		| type *	| type		| type *	|	primitive ptr or not

void ListType_source_extract(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024];

	PublishArraySpec *as = s->arraySpec[a_type];

	str_t e_tn = ObjectInfo_nameOf(elem);

	str_t e_param = (a_type == ArrayType_unique || a_type == ArrayType_ordered) ? "key" : "ptr";

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem) ? TRUE : FALSE;
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem);
	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem);

	str_t _ptr = e_is_primptr ? "" : "*";
	str_t _ptr_sp = e_is_primptr ? " " : " *";
	str_t codeParam = NULL;
	//										 1  2 3          4      5  6 7      1     2     3   4   5     6     7
	Dz1ThreadA_ftprintf(fp, tab,	"static %s %s%s_extract(%s *p, %s %s%s)\n", e_tn, _ptr, tn, tn, e_tn, _ptr, e_param);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");

	Dz1ThreadA_ftprintf(fp, tab,		"return (%s%s)%s;\n", e_tn, _ptr_sp,
										as->code(as, s->cast, buf, ArraySpecApiType_extract, "*p->storage", e_param, NULL, NULL, NULL));
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// ArrayInfo source : EXTRACT function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Find&Search with API
// -------------+-----------+-----------+-----------+
// api argument	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// find			| type key	| type key	| type *key	|	primitive or not

// -------------+-----------+-----------+-----------+
// api return	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// find			| type *	| type		| type *	|	primitive ptr or not
static void ListType_source_findWithAPI(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, str_t e_param, PublishSpec *s, int tab)
{
	char buf[1024], arg[256];

	PublishCastSpec *cast = s->cast;
	PublishArraySpec *as = s->arraySpec[a_type];

	str_t e_tn = ObjectInfo_nameOf(elem);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;
	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_ptr = e_is_prim ? "" : "*";
	str_t ret_ptr = e_is_primptr ? " " : " *";

	if (!e_is_primdata) strcpy(arg, e_param);
	else _std_snprintfA(arg, sizeof(arg), "&%s", e_param);

	//										 1 2 3       4      5  6 7
	Dz1ThreadA_ftprintf(fp, tab,	"static %s%s%s_find(%s *p, %s %s%s)\n", e_tn, ret_ptr, tn, tn, e_tn, e_ptr, e_param);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return (%s%s)%s;\n", e_tn, ret_ptr,
										as->code(as, cast, buf, ArraySpecApiType_find, "*p->storage", arg, NULL, NULL, NULL));
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// Find&Search with API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Find&Search without API
//	typedef struct SomeTypeFindArg
//	{
//		SomeType *scalar_primitive_key | SomeType pointer_primitive_key | SomeType *construct_key
//		SomeType *scalar_primitive_ret | SomeType pointer_primitive_ret | SomeType *construct_ret
//	} SomeTypeFindArg;
static void _sourceFindWithoutAPIParam(FILE *fp, str_t tn, ObjectInfo *elem, int tab)
{
	str_t e_tn = ObjectInfo_nameOf(elem);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t _ptr = e_is_primptr ? "" : "*";

	Dz1ThreadA_ftprintf(fp, tab,	"typedef struct %sFindArg\n", tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s %skey;\n", e_tn, _ptr);	// always should be pointer
	Dz1ThreadA_ftprintf(fp, tab,		"%s %sret;\n", e_tn, _ptr);	// always should be pointer
	Dz1ThreadA_ftprintf(fp, tab,		"int (*cmp)(%s %sa, %s %sb);\n", e_tn, _ptr, e_tn, _ptr);
	Dz1ThreadA_ftprintf(fp, --tab,	"} %sFindArg;\n\n", tn);
}
//	static SomeType [*]_SomeType_file(void *ptr, SomeType [*]p)
//	{
//		<ErrorTypeDeclare(errp, err)>
//		SomeTypeFindArg *arg = (SomeTypeFindArg *)ptr;
//		if (arg->cmp(arg->key, p) == 0) { arg->ret = p; <ErrorSetCode(errp, EEXIST)>; }
//		return err;
//	}
//	[*] = scalar primitive or construct
static void _sourceFindWithoutAPIHelperFunc(FILE *fp, str_t tn, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024];
	PublishErrorSpec *error = s->error;

	str_t e_tn = ObjectInfo_nameOf(elem);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_ptr = e_is_primptr ? "" : "*";

	Dz1ThreadA_ftprintf(fp, tab,	"static %s _%s_find(void *ptr, %s %sp)\n", error->type, tn, e_tn, e_ptr);	// "data" should be pointer
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s err = %s, *errp = &err;\n", error->type, error->code(error, buf, ErrorCodeGenType_init, "err", NULL));
	Dz1ThreadA_ftprintf(fp, tab,		"%sFindArg *arg = (%sFindArg *)ptr;\n", tn, tn);
	Dz1ThreadA_ftprintf(fp, tab,		"if (arg->cmp(arg->key, p) == 0) { arg->ret = p; %s; }\n",
										error->code(error, buf, ErrorCodeGenType_set, "err", "EEXIST"));
	Dz1ThreadA_ftprintf(fp, tab,		"return  err;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}

// -------------+-----------+-----------+-----------+
// api argument	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// find			| type key	| type key	| type *key	|	primitive or not

// -------------+-----------+-----------+-----------+
// api return	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// find			| type *	| type		| type *	|	primitive ptr or not
static void ListType_source_findWithoutAPI(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, str_t e_param, PublishSpec *s, int tab)
{
	PublishArraySpec *as = s->arraySpec[a_type];

	PublishPostFix *postFix = s->postFix;

	str_t e_tn = ObjectInfo_nameOf(elem);
	str_t e_fx = ObjectInfo_prefixOf(elem, s);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;
	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_ptr = e_is_prim ? "" : "*";

	str_t ret_ptr		= e_is_primptr ? "" : "*";
	str_t e_param_amp	= e_is_primdata ? "&" : "";

	_sourceFindWithoutAPIParam(fp, tn, elem, tab);
	_sourceFindWithoutAPIHelperFunc(fp, tn, elem, s, tab);

	//										 1  2 3       4      5  6 7      1     2        3   4   5     6      7
	Dz1ThreadA_ftprintf(fp, tab,	"static %s %s%s_find(%s *p, %s %s%s)\n", e_tn, ret_ptr, tn, tn, e_tn, e_ptr, e_param);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%sFindArg arg = { NULL, NULL };\n", tn);
	Dz1ThreadA_ftprintf(fp, tab,		"arg.key = %s%s;\n", e_param_amp, e_param);
	Dz1ThreadA_ftprintf(fp, tab,		"arg.cmp = p->cmp;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"p->travel(p, _%s_find, (void *)&arg);\n", tn);
	Dz1ThreadA_ftprintf(fp, tab,		"return arg.ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// Find&Search without API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : FIND function
// -------------+-----------+-----------+-----------+
// api argument	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// find			| type key	| type key	| type *key	|	primitive or not

// -------------+-----------+-----------+-----------+
// api return	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// find			| type *	| type		| type *	|	primitive ptr or not
void ListType_source_find(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	PublishArraySpec *as = s->arraySpec[a_type];
	if (as->map[ArraySpecApiType_find])
		ListType_source_findWithAPI(fp, tn, a_type, elem, "key", s, tab);
	else ListType_source_findWithoutAPI(fp, tn, a_type, elem, "key", s, tab);
}
// ArrayInfo source : FIND function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : GETHEAD function
// -------------+-----------+-----------+-----------+
// api return	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// getHead		| type *	| type		| type *	|	primitive or not
void ListType_source_getHead(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024];

	PublishCastSpec *cast = s->cast;
	PublishArraySpec *as = s->arraySpec[a_type];

	str_t e_tn = ObjectInfo_nameOf(elem);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;
//	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem) ? TRUE : FALSE;

// 	str_t e_ptr = e_is_prim ? "" : "*";
// 	str_t e_ptr_sp = e_is_prim ? " " : " *";

	str_t e_ptr = e_is_primptr ? " " : " *";

	Dz1ThreadA_ftprintf(fp, tab,	"static %s%s%s_getHead(%s *p)\n", e_tn, e_ptr, tn, tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return (%s%s)%s;\n", e_tn, e_ptr,
										as->code(as, cast, buf, ArraySpecApiType_gethead, "*p->storage", NULL, NULL, NULL, NULL));
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// ArrayInfo source : GETHEAD function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : GETTAIL function
// -------------+-----------+-----------+-----------+
// api return	| prim data	| prim ptr	| cstr data	|
// -------------+-----------+-----------+-----------+
// getTail		| type *	| type		| type *	|	primitive or not
void ListType_source_getTail(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab)
{
	char buf[1024];
	PublishArraySpec *as = s->arraySpec[a_type];
	PublishCastSpec *cast = s->cast;

	str_t e_tn = ObjectInfo_nameOf(elem);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;
//	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem) ? TRUE : FALSE;

// 	str_t e_ptr = e_is_prim ? "" : "*";
// 	str_t e_ptr_sp = e_is_prim ? " " : " *";

	str_t e_ptr = e_is_primptr ? " " : " *";

	Dz1ThreadA_ftprintf(fp, tab,	"static %s%s%s_getTail(%s *p)\n", e_tn, e_ptr, tn, tn);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"return (%s%s)%s;\n", e_tn, e_ptr,
										as->code(as, cast, buf, ArraySpecApiType_gettail, "*p->storage", NULL, NULL, NULL, NULL));
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n\n");
}
// ArrayInfo source : GETTAIL function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : NEW : API Assignment
void ListType_source_newApi(FILE *fp, str_t tn, ArrayType a_type, u32_t a_api, str_t e_cmp_fn, PublishSpec *s, int tab)
{
	PublishPostFix *postFix = s->postFix;
	PublishArraySpec *as = s->arraySpec[a_type];

	if (a_api & ARRAY_API_COUNT) Dz1ThreadA_ftprintf(fp, tab, "ret->count = %s_count;\n", tn);
	if (a_api & ARRAY_API_TRAVEL)
	{
		Dz1ThreadA_ftprintf(fp, tab, "ret->travel = %s_travelForward;\n", tn);
		Dz1ThreadA_ftprintf(fp, tab, "ret->travelForward = %s_travelForward;\n", tn);
		Dz1ThreadA_ftprintf(fp, tab, "ret->travelBackward = %s_travelBackward;\n", tn);
	}
	if (a_api & ARRAY_API_ARRAY)	Dz1ThreadA_ftprintf(fp, tab, "ret->get_array = %s_get_array;\n", tn); // modified by gm 20230602 
	if (a_api & ARRAY_API_ADD)		Dz1ThreadA_ftprintf(fp, tab, "ret->add = %s_add;\n", tn);
	if (a_api & ARRAY_API_REMOVE)	Dz1ThreadA_ftprintf(fp, tab, "ret->remove = %s_remove;\n", tn);
	if (a_api & ARRAY_API_FIND)		Dz1ThreadA_ftprintf(fp, tab, "ret->find = %s_find;\n", tn);
	if (a_api & ARRAY_API_EXTRACT)	Dz1ThreadA_ftprintf(fp, tab, "ret->extract = %s_extract;\n", tn);
	if (a_api & ARRAY_API_GETHEAD)	Dz1ThreadA_ftprintf(fp, tab, "ret->getHead = %s_getHead;\n", tn);
	if (a_api & ARRAY_API_GETTAIL)	Dz1ThreadA_ftprintf(fp, tab, "ret->getTail = %s_getTail;\n", tn);
	if (Dz1Str_isVoid(e_cmp_fn) == FALSE) Dz1ThreadA_ftprintf(fp, tab, "ret->cmp = %s;\n", e_cmp_fn);
}
// ArrayInfo source : NEW : API Assignment
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : CLONE function
void ListType_source_clone(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, bool_t elem_is_ref, PublishSpec *s, int tab)
{
	char buf[1024], func[1024];
	PublishArraySpec *as = s->arraySpec[a_type];

	PublishErrorSpec *error = s->error;
	PublishPostFix *postFix = s->postFix;
	PublishCastSpec *cast = s->cast;

	str_t e_tn = ObjectInfo_nameOf(elem);
	str_t e_fx = ObjectInfo_prefixOf(elem, s);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;
	bool_t e_is_primdata = e_is_prim && !ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_arg_mk_ptr = e_is_primptr ? "" : "*";

	// _<name>_clone                             1   2 3             4  5          1            2   3                4     5
	Dz1ThreadA_ftprintf(fp, tab,		"static %s _%s%s(void *ptr, %s %sdata)\n", error->type, tn, postFix->_clone, e_tn, e_arg_mk_ptr);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"%s err = %s;\n", error->type, error->code(error, buf, ErrorCodeGenType_init, "err", NULL));
	Dz1ThreadA_ftprintf(fp, tab,			"%s *p = (%s *)ptr;\n", tn, tn);
	if (e_is_primdata)
	{	//									  1  2          3 4
		Dz1ThreadA_ftprintf(fp, tab,		"%s %scloned = %s%s(data, &err);\n", e_tn, e_arg_mk_ptr, e_fx, postFix->_clone);
//		Dz1ThreadA_ftprintf(fp, tab,		"err = %s; // primdata\n",	as->code(as, cast, buf, ArraySpecApiType_add, "*p->storage", "cloned", NULL, NULL, NULL));
	}
	else if (elem_is_ref)
			Dz1ThreadA_ftprintf(fp, tab,	"%s %scloned = data; // ref\n", e_tn, e_arg_mk_ptr);
	else Dz1ThreadA_ftprintf(fp, tab,		"%s %scloned = %s%s(data, &err); // normal\n", e_tn, e_arg_mk_ptr, e_fx, postFix->_clone);

	Dz1ThreadA_ftprintf(fp, tab,			"err = %s; // chk\n",		as->code(as, cast, buf, ArraySpecApiType_add, "*p->storage", "cloned", NULL, NULL, NULL));
	Dz1ThreadA_ftprintf(fp, tab,			"if (%s) ", error->code(error, buf, ErrorCodeGenType_probe, "err", NULL));
										fprintf(fp, "%s;\n", error->code(error, buf, ErrorCodeGenType_print, "err", NULL));
	Dz1ThreadA_ftprintf(fp, tab,			"return err;\n");
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n\n");

	// <name>_clone
	Dz1ThreadA_ftprintf(fp, tab,		"%s *%s%s(%s *src, %s *err)\n", tn, tn, postFix->_clone, tn, error->type);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"%s _err = %s, *errp = %s;\n", error->type, error->defaultVal, error->code(error, buf, ErrorCodeGenType_init, "*err", "_err"));
	Dz1ThreadA_ftprintf(fp, tab,			"%s *ret = NULL;\n", tn);
	Dz1ThreadA_ftprintf(fp, tab,			"if (src == NULL) %s;\n", error->code(error, buf, ErrorCodeGenType_setAndPrint, "*errp", "EINVAL"));
	Dz1ThreadA_ftprintf(fp, tab,			"else if ((ret = %s%s(errp)) == NULL) %s;\n", tn, postFix->_new, error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));
	Dz1ThreadA_ftprintf(fp, tab,			"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,			"{\n");
	if (s->pthread) 
		Dz1ThreadA_ftprintf(fp, tab,			"pthread_cleanup_push(%s%s, (void *)&ret);\n\n", tn, postFix->_delAndSetNull);

	sprintf(func, "_%s%s", tn, postFix->_clone);
	Dz1ThreadA_ftprintf(fp, tab,				"*errp = %s;\n", as->code(as, cast, buf, ArraySpecApiType_travelForward, "*src->storage", func, "(void *)ret", NULL, NULL));
	fprintf(fp, "\n");

	if (s->pthread)
		Dz1ThreadA_ftprintf(fp, tab,			"pthread_cleanup_pop(%s); // (%s%s, (void *)&ret);\n",
												error->code(error, buf, ErrorCodeGenType_probe, "*errp", NULL),
												tn, postFix->_delAndSetNull);
	Dz1ThreadA_ftprintf(fp, --tab,			"}\n");
	Dz1ThreadA_ftprintf(fp, tab,			"return ret;\n");
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n\n");
}
// ArrayInfo source : CLONE function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : DEL function
void ListType_source_del(FILE *fp, str_t tn, ArrayType a_type, PublishSpec *s, int tab)
{
	char buf[1024];
	PublishCastSpec *cast = s->cast;
	PublishPostFix *postFix = s->postFix;
	PublishArraySpec *as = s->arraySpec[a_type];

	Dz1ThreadA_ftprintf(fp, tab,		"void %s%s(%s *p)\n", tn, postFix->_purge, tn);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"if (!p) return;\n");
	Dz1ThreadA_ftprintf(fp, tab,			"if (p->storage) %s;\n", 
											as->code(as, cast, buf, ArraySpecApiType_purge, "*p->storage", NULL, NULL, NULL, NULL));
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n\n");

	Dz1ThreadA_ftprintf(fp, tab,		"void %s%s(%s *p)\n", tn, postFix->_del, tn);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"if (!p) return;\n");
	Dz1ThreadA_ftprintf(fp, tab,			"if (p->storage) %s;\n", 
											as->code(as, cast, buf, ArraySpecApiType_del, "*p->storage", NULL, NULL, NULL, NULL));
	Dz1ThreadA_ftprintf(fp, tab,			"%s(p);\n", s->mem->free);
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n\n");
}
// ArrayInfo source : DEL function
///////////////////////////////////////////////////////////////////////////////

// static void _ListType_source_fdump_arg(FILE *fp, str_t tn, int tab)
// {
// 	Dz1ThreadA_ftprintf(fp, tab,	"typedef struct %sFDumpArg\n", tn);
// 	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
// 	Dz1ThreadA_ftprintf(fp, tab,		"FILE *fp;\n");
// 	Dz1ThreadA_ftprintf(fp, tab,		"int tab;\n");
// 	Dz1ThreadA_ftprintf(fp, --tab,	"} %sFDumpArg;\n\n", tn);
// }

///////////////////////////////////////////////////////////////////////////////
// ArrayInfo source : DUMP function
static void _ListType_source_dump(FILE *fp, str_t tn, ArrayType a_type, str_t dumpPrefix, ObjectInfo *elem, bool_t f_mode, int d_mode, PublishSpec *s, int tab)
{
	PublishErrorSpec *error = s->error;
	PublishPostFix *postFix = s->postFix;
	PublishBasicSpec *base = s->base;

	PublishArraySpec *as = s->arraySpec[a_type];

	str_t e_tn = ObjectInfo_nameOf(elem);
	str_t e_fx = ObjectInfo_prefixOf(elem, s);

	bool_t e_is_prim = ObjectInfo_isPrimitive(elem);
	bool_t e_is_primptr = e_is_prim && ObjectInfo_isAddress(elem) ? TRUE : FALSE;

	str_t e_arg_to_ptr = e_is_primptr ? "" : "*";

	str_t _fp_param = f_mode ? "FILE *fp, " : "";
//	str_t _tab = f_mode ? "arg->tab" : "tab";
	str_t _fppar = f_mode ? "arg->fp, " : "";
	str_t prefix = (dumpPrefix != NULL) ? prefix = dumpPrefix : "entry = ";
	MemberDumpSpec ds;
	MemberDumpSpec_init(&ds, f_mode, d_mode, s);

	///////////////////////////////////////////////////////////////////////////
	// _dump_helper
	//											 1   2 3 4             5  6       1            2   3       4         5     6
	Dz1ThreadA_ftprintf(fp, tab,		"static %s _%s%s%s(void *ptr, %s %sp)\n", error->type, tn, ds._AW, ds._dump, e_tn, e_arg_to_ptr);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	Dz1ThreadA_ftprintf(fp, tab,			"%s err = %s;\n", error->type, error->defaultVal);
	Dz1ThreadA_ftprintf(fp, tab,			"Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;\n");
	if (f_mode) Dz1ThreadA_ftprintf(fp, tab,"FILE *fp = arg->fp;\n");			
	Dz1ThreadA_ftprintf(fp, tab,			"int tab = *(int *)arg->tab;\n");

	if (ObjectInfo_typeOf(elem) == ObjectType_enumerate)
		// ENUMERATE						  1  2      3   4              5   6    7               1             2       3        4       5        6     7
		Dz1ThreadA_ftprintf(fp, tab,		"%s(%stab, %s\"%s%%s(%%d)\\n\"%s, %sStr%s(*p), *p);\n", ds._ftprintf, _fppar, ds._TLb, prefix, ds._TLe, e_tn, ds._AW);
	else
	{	// ELSE							
		if (Dz1Str_isVoid(prefix))	//				   1 2     3
			Dz1ThreadA_ftprintf(fp, tab,	"Dz1Thread%s%stab(%stab); ", ds._AW, ds._dump, _fppar);
		else	//							  1  2      3   4   5       1             2       3        4       5
			Dz1ThreadA_ftprintf(fp, tab,	"%s(%stab, %s\"%s\"%s); ", ds._ftprintf, _fppar, ds._TLb, prefix, ds._TLe);
		//									  1 2 3  4             1     2       3         4
		Dz1ThreadA_fprintf(fp,				"%s%s%s(%sp, tab);\n", e_fx, ds._AW, ds._dump, _fppar);
	}	
	Dz1ThreadA_ftprintf(fp, tab,			"return err;\n");
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n\n");
	// _dump_helper
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// _dump
	//										   1 2 3  4 5                  1   2       3         4          5
	Dz1ThreadA_ftprintf(fp, tab,		"void %s%s%s(%s%s *p, int tab)\n", tn, ds._AW, ds._dump, _fp_param, tn);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");//       1  2 3          4
	Dz1ThreadA_ftprintf(fp, tab,			"if (!p) %s(%s%s\"NULL\\n\"%s);\n", ds._fprintf, ds._fparg, ds._TLb, ds._TLe);
	Dz1ThreadA_ftprintf(fp, tab,			"else\n");
	Dz1ThreadA_ftprintf(fp, tab++,			"{\n");
												//1  2 3         4
	if (f_mode) Dz1ThreadA_ftprintf(fp, tab,	"Dz1ListFDumpArg2 arg = { %s &tab };\n", ds._fparg);
	else Dz1ThreadA_ftprintf(fp, tab,			"Dz1ListFDumpArg2 arg = { NULL, &tab };\n");
	Dz1ThreadA_ftprintf(fp, tab,				"%s(%stab, %s\"{\\n\"%s); tab++;\n", ds._ftprintf, ds._fparg, ds._TLb, ds._TLe);
	Dz1ThreadA_ftprintf(fp, tab,				"p->travel(p, _%s%s%s, (void *)&arg);\n", tn, ds._AW, ds._dump);
												//1  2        3         4
	Dz1ThreadA_ftprintf(fp, tab,				"%s(%s--tab, %s\"}\\n\"%s);\n", ds._ftprintf, ds._fparg, ds._TLb, ds._TLe);
	Dz1ThreadA_ftprintf(fp, --tab,			"}\n");
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	// _dump
	///////////////////////////////////////////////////////////////////////////
}
// ArrayInfo source : DUMP function
///////////////////////////////////////////////////////////////////////////////

bool_t ListType_source_dump(FILE *fp, str_t tn, ArrayType a_type, u32_t a_api, str_t dumpPrefix, ObjectInfo *elem, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	u32_t e_api = ObjectInfo_apiOf(elem, s);
	bool_t p_dump = FALSE, p_fdump = FALSE;

	///////////////////////////////////////////////////////////////
	// Modify e_api's dump flags
	switch(a_api & (ARRAY_API_USER_DUMP | ARRAY_API_NO_DUMP))
	{
	case ARRAY_API_USER_DUMP | ARRAY_API_NO_DUMP:
		e_api &= ~(OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE);	// erase elem_api's char-set flags
		break;
	case ARRAY_API_USER_DUMP:
	case ARRAY_API_NO_DUMP: 
		e_api &= ~(OBJECT_API_DUMP | OBJECT_API_USER_DUMP);			// erase elem_api's dump flags
		break;
	default: break;													// nothing to do
	}

	switch(a_api & (ARRAY_API_USER_FDUMP | ARRAY_API_NO_FDUMP))
	{
	case (ARRAY_API_USER_FDUMP | ARRAY_API_NO_FDUMP):
		e_api &= ~(OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE);	// erase elem_api's char-set flags
		break;	
	case ARRAY_API_USER_FDUMP: 
	case ARRAY_API_NO_FDUMP:
		e_api &= ~(OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP);		// erase elem_api's dump flags
		break;		
	default: break;													// nothing to do
	}
	// Modify e_api's dump flags
	///////////////////////////////////////////////////////////////

	if (e_api & (OBJECT_API_DUMP | OBJECT_API_USER_DUMP)) p_dump = TRUE;
	if (e_api & (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP)) p_fdump = TRUE;

	if (p_dump || p_fdump)
	{
		u8_t type = (e_api & (OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE));
//		if (p_fdump) _ListType_source_fdump_arg(fp, tn, tab);
		switch(type)
		{
		case 0:
			if (p_dump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, FALSE, 0, s, tab);
			if (p_fdump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, TRUE, 0, s, tab);
			break;
		case 1:
			if (p_dump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, FALSE, 3, s, tab);
			if (p_fdump)_ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, TRUE, 3, s, tab);
			break;
		case 2:
			if ((e_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (p_dump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, FALSE, 4, s, tab);
			if (p_fdump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, TRUE, 4, s, tab);
			if ((e_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		case 3:
			if (p_dump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, FALSE, 1, s, tab);
			if (p_fdump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, TRUE, 1, s, tab);
			if ((e_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (p_dump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, FALSE, 2, s, tab);
			if (p_fdump) _ListType_source_dump(fp, tn, a_type, dumpPrefix, elem, TRUE, 2, s, tab);
			if ((e_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		}
		ret = TRUE;
	}
	return ret;
}