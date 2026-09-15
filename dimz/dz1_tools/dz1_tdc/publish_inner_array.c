#include <dz1_str.h>
#include <dz1_thread_stdio.h>

#include "publish_util.h"
#include "publish_inner_array.h"

static bool_t _mk_condition(char *dst, size_t dst_sz, str_t src, bool_t pointer_mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t rpl = pointer_mode ? "(*ap)" : "ap";
	str_t temp = Dz1StrA_replace(src, "$$", rpl, errp);
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
		strncpy(dst, temp, dst_sz);
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// Array member delAndSetNull macro publish
static void _arr_macro_any_delAndSetNull(FILE *fp, str_t macro_prefix, str_t tn, str_t e_tn, str_t _ptr, str_t instance, str_t c_tn)
{
	fprintf(fp,	"// void %s_%s_delAndSetNull(void *ptr);\n", tn, instance);
	if (Dz1Str_isVoid(c_tn))	//		1				 2   3 4   5
		fprintf(fp, "static __inline__ %s_delAndSetNull(%s, %s%s, %s)\n",	  macro_prefix, tn, e_tn, _ptr, instance);
	else						//		1				 2   3 4   5   6
		fprintf(fp, "static __inline__ %s_delAndSetNull(%s, %s%s, %s, %s)\n", macro_prefix, tn, e_tn, _ptr, instance, c_tn);
}
// Array member delAndSetNull macro publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array member del macro publish
static void _arr_macro_x_del(FILE *fp, str_t macro_prefix, str_t tn, str_t e_tn, str_t _ptr, str_t instance, str_t c_tn, bool_t c_tn_is_cond, str_t del_api)
{	
	if (c_tn_is_cond)	//	  1  2      3  4    	   1   2         3     4
		fprintf(fp,	"// void %s_%s_del(%s %s*src);\n", tn, instance, e_tn, _ptr);
	else				//	  1  2      3  4       5		   1   2         3     4     5
		fprintf(fp,	"// void %s_%s_del(%s %s*src, %s cnt);\n", tn, instance, e_tn, _ptr, c_tn);

	if (Dz1Str_isVoid(del_api))	//		1      2   3 4   5   6
		fprintf(fp, "static __inline__ %s_del(%s, %s%s, %s, %s)\n",		macro_prefix, tn, e_tn, _ptr, instance, c_tn);
	else						//		1      2   3 4   5   6   7
		fprintf(fp, "static __inline__ %s_del(%s, %s%s, %s, %s, %s)\n", macro_prefix, tn, e_tn, _ptr, instance, c_tn, del_api);
}
// Array member del macro publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array member count macro publish
static void _arr_macro_nocnt_count(FILE *fp, str_t macro_prefix, str_t tn, str_t e_tn, str_t _ptr, str_t memb, str_t cond)
{	//							  1  2        3  4			 1   2         3     4
	fprintf(fp,	"// unsigned int %s_%s_count(%s %s*src);\n", tn, memb, e_tn, _ptr);
	//								1		 2   3 4   5   6
	fprintf(fp, "static __inline__ %s_count(%s, %s%s, %s, %s)\n", macro_prefix, tn, e_tn, _ptr, memb, cond);
}
// Array member count macro publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array member clone macro publish
static void _arr_macro_x_clone(FILE *fp, str_t macro_prefix, str_t tn, str_t e_type, str_t _ptr, str_t memb, 
							   str_t c_tn, bool_t c_tn_is_cond, str_t clone_api)
{
	if (c_tn_is_cond)	//	 1  2  3  4        5  6
		fprintf(fp,		"// %s %s*%s_%s_clone(%s %s*src, Dz1Error *err);\n", 
						e_type, _ptr, tn, memb,	// 1 2 3 4
						e_type, _ptr);			// 5 6
	else				//   1  2  3  4        5  6       7
		fprintf(fp,		"// %s %s*%s_%s_clone(%s %s*src, %s cnt, Dz1Error *err);\n", 
						e_type, _ptr, tn, memb,	// 1 2 3 4
						e_type, _ptr, c_tn);	// 5 6 7

	if (Dz1Str_isVoid(clone_api))	//	1		 2   3 4   5   6
		fprintf(fp, "static __inline__ %s_clone(%s, %s%s, %s, %s)\n",	  macro_prefix, tn, e_type, _ptr, memb, c_tn);
	else 			//					1		 2   3 4   5   6   7
		fprintf(fp, "static __inline__ %s_clone(%s, %s%s, %s, %s, %s)\n", macro_prefix, tn, e_type, _ptr, memb, c_tn, clone_api);
}
// Array member clone macro publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array member dump macro publish
static void __arr_macro_dump(FILE *fp, str_t macro_name, str_t _macro_AW, str_t _api, bool_t is_fdump, 
							 str_t tn, str_t _ptr, /*StructMemberEntry *p,*/ ObjectInfo *type, str_t memb, str_t bridge, 
							 str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	str_t e_tn = ObjectInfo_nameOf(type);
	str_t e_fx = ObjectInfo_prefixOf(type, s);

	bool_t e_fx_AW_sticky = ObjectInfo_getDumpApiSticky(type, s);
	str_t _fx_AW = e_fx_AW_sticky ? "" : _macro_AW;

	str_t _fppar = is_fdump ? "FILE *fp, " : "";

	// parent_type##_##member_name##_dump
	if (c_tn_is_cond)	//						  1  2 3 4  5 6   7                 1   2     3          4     5       6     7
		Dz1ThreadA_ftprintf(fp, tab,	"// void %s_%s%s%s(%s%s *%sp, int tab);\n", tn, memb, _macro_AW, _api, _fppar, e_tn, _ptr);
	else				//						  1  2 3 4  5 6   7    8					1   2     3          4     5       6     7     8
		Dz1ThreadA_ftprintf(fp, tab,	"// void %s_%s%s%s(%s%s *%sp, %s cnt, int tab);\n", tn, memb, _macro_AW, _api, _fppar, e_tn, _ptr, c_tn);
	//													1 2 3  4   5 6   7   8     9     A B C
	Dz1ThreadA_ftprintf(fp, tab,	"static __inline__ %s%s%s(%s, %s%s, %s, %s, \"%s\", %s%s%s)\n", 
									macro_name, _macro_AW, _api,	// 1 2 3
									tn, e_tn, _ptr,				// 4 5 6
									memb, c_tn, bridge,			// 7 8 9
									e_fx, _fx_AW, _api);			// A B C
}

void _arr_macro_dump(FILE *fp, str_t macro_name, str_t tn, u32_t t_api, 
					 str_t _ptr, /*StructMemberEntry *p,*/ ObjectInfo *type, str_t memb, str_t c_tn, bool_t c_tn_is_cond,
					 str_t bridge, PublishSpec *s, int tab)
{
	bool_t t_dump = (t_api & (OBJECT_API_DUMP | OBJECT_API_USER_DUMP)) ? TRUE : FALSE;
	bool_t t_fdump = (t_api & (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP)) ? TRUE : FALSE;

	PublishPostFix *pfx = s->postFix;

	if (t_dump || t_fdump)
	{	// parent 가 dump, fdump 를 지원하면
		int t_dmode = (t_api & (OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE));
		switch(t_dmode)
		{
		case 0:	// no mode				= Dz1StructArrayMemb_ptr_dump, SomeType
			if (t_dump) __arr_macro_dump(fp, macro_name, "", pfx->_dump, FALSE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			if (t_fdump) __arr_macro_dump(fp, macro_name, "", pfx->_fdump, TRUE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			break;
		case 1:	// OBJECT_API_DUMP_MBCS = Dz1StructArrayMemb_ptrA_dump, SomeTypeA
			if (t_dump) __arr_macro_dump(fp, macro_name, "A", pfx->_dump, FALSE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			if (t_fdump) __arr_macro_dump(fp, macro_name, "A", pfx->_fdump, TRUE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			break;
		case 2:	// OBJECT_API_DUMP_WIDE = Dz1StructArrayMemb_ptrW_dump, SomeTypeW
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (t_dump) __arr_macro_dump(fp, macro_name, "W", pfx->_dump, FALSE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			if (t_fdump) __arr_macro_dump(fp, macro_name, "W", pfx->_fdump, TRUE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		case 3:	// OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE = both, SomeType
			if (t_dump) __arr_macro_dump(fp, macro_name, "A", pfx->_dump, FALSE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			if (t_fdump) __arr_macro_dump(fp, macro_name, "A", pfx->_fdump, TRUE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#ifndef UNIX_SYSTEM\n");
			if (t_dump) __arr_macro_dump(fp, macro_name, "W", pfx->_dump, FALSE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			if (t_fdump) __arr_macro_dump(fp, macro_name, "W", pfx->_fdump, TRUE, tn, _ptr, type, memb, bridge, c_tn, c_tn_is_cond, s, tab);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) fprintf(fp, "#endif // UNIX_SYSTEM\n");
			break;
		}
		fputs("\n", fp);
	}
}
// Array member dump macro publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array member(Pointer) macro publish
static void _arr_macro_ptr(FILE *fp, str_t tn, u32_t t_api, str_t _ptr, ObjectInfo *type, str_t memb,
						   str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	char del_api[128], clone_api[128], _cond[256];
	PublishPostFix *postFix = s->postFix;

	str_t e_tn = ObjectInfo_nameOf(type);
	str_t e_fx = ObjectInfo_prefixOf(type, s);
	str_t macro_prefix = c_tn_is_cond ? "Dz1StructArrayMemb_ptr_nocnt" : "Dz1StructArrayMemb_ptr";

	// int *a, SomeType *b -> int **arr_a, SomeType **arr_b -> $$ = (*ap)
	str_t cnt_or_cond = c_tn_is_cond ? _cond : c_tn;
	if (c_tn_is_cond) _mk_condition(_cond, sizeof(_cond), c_tn, TRUE);

	_std_snprintfA(del_api,	  sizeof(del_api),   "%s%s", e_fx, postFix->_del);
	_std_snprintfA(clone_api, sizeof(clone_api), "%s%s", e_fx, postFix->_clone);

	_arr_macro_x_del(fp,					macro_prefix, tn, e_tn, _ptr, memb, cnt_or_cond, c_tn_is_cond, del_api);
	if (c_tn_is_cond)
	{
		_arr_macro_any_delAndSetNull(fp,	macro_prefix, tn, e_tn, _ptr, memb, NULL);
		_arr_macro_nocnt_count(fp,			macro_prefix, tn, e_tn, _ptr, memb, cnt_or_cond);
	}
	else _arr_macro_any_delAndSetNull(fp,	macro_prefix, tn, e_tn, _ptr, memb, cnt_or_cond);

	_arr_macro_x_clone(fp,					macro_prefix, tn, e_tn, _ptr, memb, cnt_or_cond, c_tn_is_cond, clone_api);

}
static void _arr_macro_ptr_dump(FILE *fp, str_t tn, u32_t t_api, str_t _ptr, ObjectInfo *type, str_t memb,  MemberDumpMode memb_dump,
								str_t c_tn, bool_t c_tn_is_cond, str_t bridge, PublishSpec *s, int tab)
{
	if (memb_dump != MemberDumpMode_omit) 
	{
		char _cond[256];
		str_t macro_prefix = c_tn_is_cond ? "Dz1StructArrayMemb_ptr_nocnt" : "Dz1StructArrayMemb_ptr";
		str_t cnt_or_cond = c_tn_is_cond ? _cond : c_tn;
		if (c_tn_is_cond) _mk_condition(_cond, sizeof(_cond), c_tn, TRUE);
		_arr_macro_dump(fp, macro_prefix, tn, t_api, _ptr, type, memb, cnt_or_cond, c_tn_is_cond, bridge, s, tab);
	}
}
// Array member(Pointer) macro publish
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Array member(Referenced Pointer) macro publish
static void _arr_macro_ptrref(FILE *fp, str_t tn, u32_t t_api, str_t _ptr, ObjectInfo *type, str_t memb,
							  str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	char _cond[256];
	PublishPostFix *postFix = s->postFix;

	str_t e_tn = ObjectInfo_nameOf(type);
	str_t e_fx = ObjectInfo_prefixOf(type, s);
	str_t macro_prefix = c_tn_is_cond ? "Dz1StructArrayMemb_ptrref_nocnt" : "Dz1StructArrayMemb_ptrref";

	// int *a, SomeType *b -> int **arr_a, SomeType **arr_b -> $$ = (*ap)
	str_t cnt_or_cond = c_tn_is_cond ? _cond : c_tn;
	if (c_tn_is_cond) _mk_condition(_cond, sizeof(_cond), c_tn, TRUE);

	_arr_macro_x_del(fp,			 macro_prefix, tn, e_tn, _ptr, memb, cnt_or_cond, c_tn_is_cond, NULL);
	_arr_macro_any_delAndSetNull(fp, macro_prefix, tn, e_tn, _ptr, memb, NULL);
	if (c_tn_is_cond)
		_arr_macro_nocnt_count(fp,	 macro_prefix, tn, e_tn, _ptr, memb, cnt_or_cond);
	_arr_macro_x_clone(fp,			 macro_prefix, tn, e_tn, _ptr, memb, cnt_or_cond, c_tn_is_cond, NULL);

}
static void _arr_macro_ptrref_dump(FILE *fp, str_t tn, u32_t t_api, str_t _ptr, ObjectInfo *type, str_t memb, MemberDumpMode memb_dump,
								   str_t c_tn, bool_t c_tn_is_cond, str_t bridge, PublishSpec *s, int tab)
{
	if (memb_dump != MemberDumpMode_omit)
	{
		char _cond[256];
		str_t macro_prefix = c_tn_is_cond ? "Dz1StructArrayMemb_ptrref_nocnt" : "Dz1StructArrayMemb_ptrref";
		str_t cnt_or_cond = c_tn_is_cond ? _cond : c_tn;
		if (c_tn_is_cond) _mk_condition(_cond, sizeof(_cond), c_tn, TRUE);
		_arr_macro_dump(fp, macro_prefix, tn, t_api, _ptr, type, memb, cnt_or_cond, c_tn_is_cond, bridge, s, tab);
	}
}
// Array member(Referenced Pointer) macro publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array member(Primitive Value) macro publish
static void _arr_macro_val_prim(FILE *fp, str_t tn, u32_t t_api, ObjectInfo *type, str_t memb, str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	char _cond[256];
	PublishPostFix *postFix = s->postFix;

	str_t e_tn = ObjectInfo_nameOf(type);
	str_t e_fx = ObjectInfo_prefixOf(type, s);
	str_t macro_prefix = c_tn_is_cond ? "Dz1StructArrayMemb_val_primitive_nocnt" : "Dz1StructArrayMemb_val_primitive";

	// int v; -> int *arr; $$ = (*ap)
	str_t cnt_or_cond = c_tn_is_cond ? _cond : c_tn;
	if (c_tn_is_cond) _mk_condition(_cond, sizeof(_cond), c_tn, TRUE);

	_arr_macro_x_del(fp,			 macro_prefix, tn, e_tn, "", memb, cnt_or_cond, c_tn_is_cond, NULL);
	_arr_macro_any_delAndSetNull(fp, macro_prefix, tn, e_tn, "", memb, NULL);
	if (c_tn_is_cond)
		_arr_macro_nocnt_count(fp,	 macro_prefix, tn, e_tn, "", memb, cnt_or_cond);
	_arr_macro_x_clone(fp,			 macro_prefix, tn, e_tn, "", memb, cnt_or_cond, c_tn_is_cond, NULL);
}
static void _arr_macro_val_prim_dump(FILE *fp, str_t tn, u32_t t_api, ObjectInfo *type, str_t memb, MemberDumpMode memb_dump, 
									 str_t c_tn, bool_t c_tn_is_cond, str_t bridge, PublishSpec *s, int tab)
{
	if (memb_dump != MemberDumpMode_omit)
	{
		char _cond[256];
		str_t macro_prefix = c_tn_is_cond ? "Dz1StructArrayMemb_val_primitive_nocnt" : "Dz1StructArrayMemb_val_primitive";
		str_t cnt_or_cond = c_tn_is_cond ? _cond : c_tn;
		if (c_tn_is_cond) _mk_condition(_cond, sizeof(_cond), c_tn, TRUE);
		_arr_macro_dump(fp, macro_prefix, tn, t_api, "", type, memb, cnt_or_cond, c_tn_is_cond, bridge, s, tab);
	}
}
// Array member(Primitive Value) macro publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array member(Construct) macro publish
static void _arr_macro_val_cst(FILE *fp, str_t tn, u32_t t_api, ObjectInfo *type, str_t memb, str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	char del_api[128], clone_api[128], _cond[256];
	PublishPostFix *postFix = s->postFix;
	str_t e_tn = ObjectInfo_nameOf(type);
	str_t e_fx = ObjectInfo_prefixOf(type, s);
	str_t macro_prefix = c_tn_is_cond ? "Dz1StructArrayMemb_val_construct_nocnt" : "Dz1StructArrayMemb_val_construct";

	str_t cnt_or_cond = c_tn_is_cond ? _cond : c_tn;
	if (c_tn_is_cond) _mk_condition(_cond, sizeof(_cond), c_tn, FALSE);

	_std_snprintfA(del_api, sizeof(del_api), "%s%s", e_fx, postFix->_purge);
	_std_snprintfA(clone_api, sizeof(clone_api), "%s%s", e_fx, postFix->_copy);

	_arr_macro_x_del(fp,				  macro_prefix, tn, e_tn, "", memb, cnt_or_cond, c_tn_is_cond, del_api);
	if (c_tn_is_cond)
	{
		_arr_macro_any_delAndSetNull(fp,  macro_prefix, tn, e_tn, "", memb, NULL);
		_arr_macro_nocnt_count(fp,		  macro_prefix, tn, e_tn, "", memb, cnt_or_cond);
	}
	else _arr_macro_any_delAndSetNull(fp, macro_prefix, tn, e_tn, "", memb, cnt_or_cond);

	_arr_macro_x_clone(fp,				  macro_prefix, tn, e_tn, "", memb, cnt_or_cond, c_tn_is_cond, clone_api);
}

static void _arr_macro_val_cst_dump(FILE *fp, str_t tn, u32_t t_api, ObjectInfo *type, str_t memb, MemberDumpMode memb_dump, 
									str_t c_tn, bool_t c_tn_is_cond, str_t bridge, PublishSpec *s, int tab)
{
	if (memb_dump != MemberDumpMode_omit) 
	{
		char _cond[256];
		str_t macro_prefix = c_tn_is_cond ? "Dz1StructArrayMemb_val_construct_nocnt" : "Dz1StructArrayMemb_val_construct";
		str_t cnt_or_cond = c_tn_is_cond ? _cond : c_tn;
		if (c_tn_is_cond) _mk_condition(_cond, sizeof(_cond), c_tn, FALSE);
		_arr_macro_dump(fp, macro_prefix, tn, t_api, "", type, memb, cnt_or_cond, c_tn_is_cond, bridge, s, tab);
	}
}
// Array member(Construct) macro publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIMITIVE Array macro
static void __primA_macro(FILE *fp, str_t tn, u32_t api, 
						  ObjectInfo *type, bool_t _is_ptr, str_t memb, u32_t memb_flag, MemberDumpMode memb_dump,
						  str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	ObjectInfo *o = ObjectInfo_getOrigin(type);
	PrimitiveInfo *info = (PrimitiveInfo *)o->info;
	if (_is_ptr)
	{
		switch(info->storage)
		{	// int *[], real *[], void *[]
		case NativeStorage_data: case NativeStorage_none:	// int *[], real *[]
			if (MemberFlag_isArrayElemRef(memb_flag) || info->storage == NativeStorage_none)
			{
				if (MemberFlag_isReferenced(memb_flag) == FALSE)
					_arr_macro_ptrref(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
				_arr_macro_ptrref_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
			}
			else
			{
				if (MemberFlag_isReferenced(memb_flag) == FALSE)
					_arr_macro_ptr(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
				_arr_macro_ptr_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
			}
			break;
		case NativeStorage_address: default:				// str *[] -> error
			Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(__primA_macro:0)\n", tn, memb);
			break;
		}
	}
	else
	{
		switch(info->storage)
		{	// int [], real [], void []
		case NativeStorage_data: 	// int [], real []
			_arr_macro_val_prim(fp, tn, api, type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_val_prim_dump(fp, tn, api, type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
			break;
		case NativeStorage_address:	// str []
			if (MemberFlag_isArrayElemRef(memb_flag))
			{
				if (MemberFlag_isReferenced(memb_flag) == FALSE)
					_arr_macro_ptrref(fp, tn, api, "", type, memb, c_tn, c_tn_is_cond, s, tab);
				_arr_macro_ptrref_dump(fp, tn, api, "", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
			}
			else
			{
				if (MemberFlag_isReferenced(memb_flag) == FALSE)
					_arr_macro_ptr(fp, tn, api, "", type, memb, c_tn, c_tn_is_cond, s, tab);
				_arr_macro_ptr_dump(fp, tn, api, "", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
			}
			break;
		case NativeStorage_none: default:	// void [] -> error;
			Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(__primA_macro:0)\n", tn, memb);
			break;
		}
	}
}
// PRIMITIVE Array macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ENUMERATE Array macro
static void __enumA_macro(FILE *fp, str_t tn, u32_t api,
						  ObjectInfo *type, bool_t _is_ptr, str_t memb, u32_t memb_flag, MemberDumpMode memb_dump,
						  str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	if (_is_ptr)
	{	// enum *[]
		if (MemberFlag_isArrayElemRef(memb_flag))
		{
			if (MemberFlag_isReferenced(memb_flag) == FALSE)
				_arr_macro_ptrref(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_ptrref_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
		}
		else
		{
			if (MemberFlag_isReferenced(memb_flag) == FALSE)
				_arr_macro_ptr(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_ptr_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
		}
	}
	else
	{	// enum []
		_arr_macro_val_prim(fp, tn, api, type, memb, c_tn, c_tn_is_cond, s, tab);
		_arr_macro_val_prim_dump(fp, tn, api, type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
	}
}
// ENUMERATE Array macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// FUNCTION Array macro
static void __funcA_macro(FILE *fp, str_t tn, u32_t api, ObjectInfo *type, bool_t _is_ptr, str_t memb, u32_t memb_flag, MemberDumpMode memb_dump,
						  str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	if (_is_ptr)
	{	// func *[] -> error
		Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(__funcA_macro:ptr)\n", tn, memb);
	}
	else
	{	// func []
		if (MemberFlag_isReferenced(memb_flag) == FALSE)
			_arr_macro_ptrref(fp, tn, api, "", type, memb, c_tn, c_tn_is_cond, s, tab);
		_arr_macro_ptrref_dump(fp, tn, api, "", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
	}
}
// FUNCTION Array macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STRUCT Array macro
static void __structA_macro(FILE *fp, str_t tn, u32_t api, ObjectInfo *type, bool_t _is_ptr, str_t memb, u32_t memb_flag, MemberDumpMode memb_dump,
							str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	if (_is_ptr)
	{	// struct *[]
		if (MemberFlag_isArrayElemRef(memb_flag))
		{
			if (MemberFlag_isReferenced(memb_flag) == FALSE)
				_arr_macro_ptrref(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_ptrref_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
		}
		else
		{
			if (MemberFlag_isReferenced(memb_flag) == FALSE)
				_arr_macro_ptr(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_ptr_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
		}
	}
	else
	{	// struct []
		_arr_macro_val_cst(fp, tn, api, type, memb, c_tn, c_tn_is_cond, s, tab);
		_arr_macro_val_cst_dump(fp, tn, api, type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
	}
}
// STRUCT Array macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UNION Array macro
static void __unionA_macro(FILE *fp, str_t tn, u32_t api, ObjectInfo *type, bool_t _is_ptr, str_t memb, u32_t memb_flag, MemberDumpMode memb_dump,
						   str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	if (_is_ptr)
	{	// union *[]
		if (MemberFlag_isArrayElemRef(memb_flag))
		{
			if (MemberFlag_isReferenced(memb_flag) == FALSE)
				_arr_macro_ptrref(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_ptrref_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, ".", s, tab);
		}
		else
		{
			if (MemberFlag_isReferenced(memb_flag) == FALSE)
				_arr_macro_ptr(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_ptr_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, ".", s, tab);
		}
	}
	else
	{	// union []
		_arr_macro_val_cst(fp, tn, api, type, memb, c_tn, c_tn_is_cond, s, tab);
		_arr_macro_val_cst_dump(fp, tn, api, type, memb, memb_dump, c_tn, c_tn_is_cond, ".", s, tab);
	}
}
// UNION Array macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// IMPORTS Array macro
static void __impA_macro(FILE *fp, str_t tn, u32_t api, ObjectInfo *type, bool_t _is_ptr, str_t memb, u32_t memb_flag, MemberDumpMode memb_dump,
						 str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab)
{
	ObjectInfo *o = ObjectInfo_getOrigin(type);
	ExternInfo *info = (ExternInfo *)o->info;
	str_t bridge = NULL;
	if (_is_ptr)
	{
		switch(info->isStatic)
		{
		case ExternInfoStatic_primitive_ptr:	// str_t *a[];	-> error
			Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(__impA_macro:ptr:primitive)\n", tn, memb);
			break;
		case ExternInfoStatic_primitive:				// int *a[]; real *b[];, void *c[]; ...
		case ExternInfoStatic_typical_union:			// union SomeType *a[];
		case ExternInfoStatic_construct:				// struct SomeType *a[];
			bridge = info->isStatic == ExternInfoStatic_typical_union ? "." : " = ";
			if (MemberFlag_isArrayElemRef(memb_flag))	// referenced
			{
				if (MemberFlag_isReferenced(memb_flag) == FALSE)
					_arr_macro_ptrref(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
				_arr_macro_ptrref_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, bridge, s, tab);
			}
			else
			{
				if (MemberFlag_isReferenced(memb_flag) == FALSE)
					_arr_macro_ptr(fp, tn, api, "*", type, memb, c_tn, c_tn_is_cond, s, tab);
				_arr_macro_ptr_dump(fp, tn, api, "*", type, memb, memb_dump, c_tn, c_tn_is_cond, bridge, s, tab);
			}
			break;
		default:
			Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(__impA_macro:ptr)\n", tn, memb);
			break;
		}
	}
	else
	{
		switch(info->isStatic)
		{
		case ExternInfoStatic_primitive:		// int a[]; real b[];, void c[]; ...
			_arr_macro_val_prim(fp, tn, api, type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_val_prim_dump(fp, tn, api, type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
			break;
		case ExternInfoStatic_primitive_ptr:	// str_t a[];
			if (MemberFlag_isReferenced(memb_flag) == FALSE)
				_arr_macro_ptr(fp, tn, api, "", type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_ptr_dump(fp, tn, api, "", type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
			break;
		case ExternInfoStatic_typical_union:	// union SomeType a[];
			_arr_macro_val_cst(fp, tn, api, type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_val_cst_dump(fp, tn, api, type, memb, memb_dump, c_tn, c_tn_is_cond, ".", s, tab);
			break;
		case ExternInfoStatic_construct:		// struct SomeType a[];
			_arr_macro_val_cst(fp, tn, api, type, memb, c_tn, c_tn_is_cond, s, tab);
			_arr_macro_val_cst_dump(fp, tn, api, type, memb, memb_dump, c_tn, c_tn_is_cond, " = ", s, tab);
			break;
		default:
			Dz1ThreadA_ftprintf(fp, tab, "#error Can't declare array api for %s->%s(__impA_macro)\n", tn, memb);
			break;
		}
	}
}
// IMPORTS Array macro
///////////////////////////////////////////////////////////////////////////////

static StructMemberArrayMacroAPI structMemberArrayMacroAPI[] =
{
	{ ObjectInstanceType_primitive,	__primA_macro },
	{ ObjectInstanceType_enumerate,	__enumA_macro },
	{ ObjectInstanceType_func,		__funcA_macro },

	{ ObjectInstanceType_structure,	__structA_macro },
	{ ObjectInstanceType_union,		__unionA_macro },
// 	{ ObjectInstanceType_array,		_not_support },
// 	{ ObjectInstanceType_index,		_not_support },

	{ ObjectInstanceType_extern,	__impA_macro },
	{ ObjectInstanceType_reference,	__impA_macro },

	StructMemberArrayMacroAPI_NULL
};

StructMemberArrayMacroAPI *StructMemberArrayMacroAPI_find(ObjectInstanceType t)
{
	StructMemberArrayMacroAPI *i;
	for (i = structMemberArrayMacroAPI; i->type != ObjectInstanceType_max; i++)
		if (i->type == t) return i;
	return NULL;
}

bool_t _array_memb_dump_code(FILE *fp, str_t tn, str_t var, str_t concat, str_t memb, str_t arr_opt,
							 MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
	if (Dz1Str_isVoid(arr_opt))
		Dz1ThreadA_ftprintf(fp, tab, "#error 'arr_cnt_name' is void\n");
	else
	{
		TP(fp, tab);
		if (needElse) fputs("elae { ", fp);

		if (tabbed)
			fprintf(fp,		"%s(%stab, %s\"%s = \"%s); ", ds->_ftprintf, ds->_fparg, ds->_TLb, memb, ds->_TLe);
		else fprintf(fp,	"%s(%s%s\"%s = \"%s); ", ds->_fprintf, ds->_fparg, ds->_TLb, memb, ds->_TLe);

		if (strstr(arr_opt, "$$") != NULL)	// no counter array type
		{	//				  2  3 4 5  6 7 8 9				SomeTypeA_membA_dump
			fprintf(fp,		"%s_%s%s%s(%s%s%s%s, tab);", 
							tn, memb, ds->_AW_origin, ds->_dump,	// 2 3 4 5
							ds->_fparg, var, concat, memb);			// 6 7 8 9
		}
		else if (Dz1StrA_isDigitStr(arr_opt))	// fixed size array type
		{	//				  2  3 4 5  6 7 8 9   A			[else 
			fprintf(fp,		"%s_%s%s%s(%s%s%s%s, %s, tab);", 
							tn, memb, ds->_AW_origin, ds->_dump,	// 2 3 4 5
							ds->_fparg, var, concat, memb,			// 6 7 8 9
							arr_opt);								// A
		}
		else													// counter size array type
		{	//				  2  3 4 5  6 7 8 9   A B C
			fprintf(fp,		"%s_%s%s%s(%s%s%s%s, %s%s%s, tab);", 
							tn, memb, ds->_AW_origin, ds->_dump,	// 2 3 4 5
							ds->_fparg, var, concat, memb,			// 6 7 8 9
							var, concat, arr_opt);					// A B C
		}

		if (needElse) fputs(" }", fp);
		fputs("\n", fp);
		needElse = FALSE;
	}
	*_else = needElse;
	return TRUE;
}
