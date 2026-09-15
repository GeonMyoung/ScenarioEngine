#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include "publish_inner_array.h"
#include "publish_union_util.h"

static void _U_memb_assigne_code(FILE *fp, str_t dst, str_t dst_memb, str_t src, str_t src_memb)
{	
	if ((Dz1Str_isVoid(src) || strchr(src, '(') != NULL))
	{	// for NEW		  1           2     3    4 5
		fprintf(fp, "if (%s != NULL) %s->x.%s = %s%s;\n",
					src_memb, dst, dst_memb,	// 1 2 3
					src, src_memb);				// 4 5
	}
	else
	{	// for CLONE  1		2    3	   4
		fprintf(fp, "%s->x.%s = %s->x.%s;\n",
					dst, dst_memb,	// 1 2
					src, src_memb);	// 3 4
	}
}

static bool_t _U_memb_clone_with_api(FILE *fp, str_t dst, UnionMemberEntry *p, str_t src, str_t src_var, PublishSpec *spec, bool_t _else)
{
	char buf[1024];

	PublishPostFix *pfx = spec->postFix;
	PublishErrorSpec *error = spec->error;

	str_t e_tn = ObjectInfo_nameOf(p->type);
	str_t e_fx = ObjectInfo_prefixOf(p->type, spec);

	str_t _src		= (Dz1Str_isVoid(src) || src[0] == '(') ? "" : src;
	str_t _src_ptr	= (Dz1Str_isVoid(src) || src[0] == '(') ? "" : "->x.";

	//            1    2 3 4      5      7    8 9  A B C                   D
	fprintf(fp, "%sif (%s%s%s && (%s->x.%s = %s%s(%s%s%s, errp)) == NULL) %s;\n",
				_else ? "else " : "",		// 1
				_src, _src_ptr, src_var,	// 2 3 4
				dst, p->instance,			// 5 7
				e_fx, pfx->_clone,			// 8 9
				src, _src_ptr, src_var,		// A B C
				error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL)); // D
	_else = TRUE;
	return _else;
}

static bool_t _U_memb_copy_with_api(FILE *fp, str_t dst, UnionMemberEntry *p, str_t src, str_t src_var, PublishSpec *s, bool_t _else)
{
	char buf[1024];
	PublishPostFix *pfx = s->postFix;
	PublishErrorSpec *error = s->error;

	str_t e_tn = ObjectInfo_prefixOf(p->type, s);
	str_t _src_ptr = (Dz1Str_isVoid(src) || src[0] == '(') ? "" : "->x.";

	//			  1     2 3   4     6    7 8 9                   A
	fprintf(fp, "%sif (%s%s(&%s->x.%s, &%s%s%s, errp) == FALSE) %s;\n",
				_else ? "else " : "",		// 1
				e_tn, pfx->_copy,			// 2 3
				dst, p->instance,			// 4 6
				src, _src_ptr, src_var,		// 7 8 9
				error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL)); // A
	_else = TRUE;
	return _else;
}

static int *_U_prim = NULL;
///////////////////////////////////////////////////////////////////////////////
// PRIMITIVE
static bool_t _U_prim_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t needElse = *_else;

	PublishErrorSpec *error = s->error;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);

	str_t e_tn = ObjectInfo_nameOf(p->type);

	Dz1ThreadA_ftprintf(fp, tab, "// _U_prim_clone\n");
	if (Dz1Str_isVoid(src))
	{	// for new
		char caster[256];
		if (p->isPointer)
		{	// int *, real *, str *, void *
			switch(storage)
			{
			case NativeStorage_data:	// int *, real *	-> assign
				_std_snprintfA(caster, sizeof(caster), "(%s *)", e_tn);
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
				needElse = FALSE;
				break;
			case NativeStorage_none:	// void *			-> assign
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, "", "ptr");
				needElse = FALSE;
				break;
			case NativeStorage_address:			// str *, 	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		else
		{	// int, real, str, void
			switch(storage)
			{
			case NativeStorage_data:	// int, real	-> assign
				_std_snprintfA(caster, sizeof(caster), "*(%s *)", e_tn);
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
				needElse = FALSE;
				break;
			case NativeStorage_address:	// str			-> clone : not referenced only
				if (UnionMemberEntry_isReferenced(p) == FALSE)
				{								
					_std_snprintfA(caster, sizeof(caster), "(%s)", e_tn);
					TP(fp, tab); 
					needElse = _U_memb_clone_with_api(fp, dst, p, caster, "ptr", s, needElse);
				}
				else					// str			-> assign : referenced
				{						
					_std_snprintfA(caster, sizeof(caster), "(%s)", e_tn);
					TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
					needElse = FALSE;
				}
				break;
			case NativeStorage_none:				// void	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
	}
	else
	{	// for clone
		if (p->isPointer)
		{	// int *, real *, str *, void *
			switch(storage)
			{
			case NativeStorage_data:	// int *, real *	-> clone : not referenced only
				if (UnionMemberEntry_isReferenced(p) == FALSE)	
				{	// clone
					TP(fp, tab);
					needElse = _U_memb_clone_with_api(fp, dst, p, src, p->instance, s, needElse);
				}
				else
				{	// pointer assign
					TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
					needElse = FALSE;
				}
				break;
			case NativeStorage_none:	// void *			-> assign
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
				needElse = FALSE;
				break;
			case NativeStorage_address:			// str *, 	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		else
		{	// int, real, str, void
			switch(storage)
			{
			case NativeStorage_data:	// int, real	-> assign
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
				needElse = FALSE;
				break;
			case NativeStorage_address:	// str			-> clone : not referenced only
				if (UnionMemberEntry_isReferenced(p) == FALSE)
				{								
					TP(fp, tab);
					needElse = _U_memb_clone_with_api(fp, dst, p, src, p->instance, s, needElse);
				}
				else					// str			-> assign : referenced
				{						
					TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
					needElse = FALSE;
				}
				break;
			case NativeStorage_none:				// void	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
	}
	*_else = needElse;
	return TRUE;
}

static bool_t _U_prim_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// del 할때
	bool_t ret = FALSE;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (p->isPointer)
	{	// int *, real *, str *, void *
		switch(storage)
		{
		case NativeStorage_data:	
			if (UnionMemberEntry_isReferenced(p) == FALSE)
			{				// int *, real *	-> delete : not referenced only
				TP(fp, tab); _memb_del_with_api(fp, FALSE, var, p->type, p->instance, s);
				ret = TRUE;
			}
			break;
		case NativeStorage_none:	// void *	-> nop
			break;
		case NativeStorage_address:	// str *	-> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	else
	{
		switch(storage)
		{
		case NativeStorage_data:	// int, real	-> nop
			break;
		case NativeStorage_address:			// str	-> delete : not referenced only
			if (UnionMemberEntry_isReferenced(p) == FALSE)
			{
				TP(fp, tab); _memb_del_with_api(fp, FALSE, var, p->type, p->instance, s);
				ret = TRUE;
			}
			break;
		case NativeStorage_none:			// void	-> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	return ret;
}

static bool_t _U_prim_dump(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{	// dump 할때
	bool_t needElse = *_else;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (p->isPointer)
	{	// int *, real *, str *, void *
		switch(storage)
		{
		case NativeStorage_data:	// int *, real *	-> dump
			needElse = _dump_using_api(fp, FALSE, "", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			break;
		case NativeStorage_none:			// void *	-> address dump
			needElse = _dump_address(fp, FALSE, "", var, p->instance, ds, tabbed, tab, needElse);
			break;
		case NativeStorage_address:			// str *	-> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate dump code for %s\"\n", p->instance);
			break;
		}
	}
	else
	{
		switch(storage)
		{
		case NativeStorage_data:	// int, real	-> dump
			needElse = _dump_using_api(fp, FALSE, "&", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			break;
		case NativeStorage_address:			// str	-> dump
			needElse = _dump_using_api(fp, FALSE, "", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			break;
		case NativeStorage_none:			// void	-> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			break;
		}
	}
	needElse = FALSE;
	*_else = needElse;
	return TRUE;
}
// PRIMITIVE
///////////////////////////////////////////////////////////////////////////////

static int *_U_enum = NULL;
///////////////////////////////////////////////////////////////////////////////
// ENUMERATE
static bool_t _U_enum_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t needElse = *_else;
	str_t e_tn = ObjectInfo_nameOf(p->type);

	Dz1ThreadA_ftprintf(fp, tab, "// _U_enum_clone\n");
	if (Dz1Str_isVoid(src))
	{	// for new
		char caster[256];
		if (p->isPointer)
		{	// enum *	-> assign
			_std_snprintfA(caster, sizeof(caster), "(%s *)", e_tn);
			TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
			needElse = FALSE;
		}
		else
		{	// enum		-> assign
			_std_snprintfA(caster, sizeof(caster), "*(%s *)", e_tn);
			TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
			needElse = FALSE;
		}
	}
	else
	{	// for clone
		if (p->isPointer)
		{	// enum *	-> clone : not referenced only
			if (UnionMemberEntry_isReferenced(p) == FALSE)	
			{
				TP(fp, tab); 
				needElse = _U_memb_clone_with_api(fp, dst, p, src, p->instance, s, needElse);
			}
			else
			{
				TP(fp, tab); 
				_U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
				needElse = FALSE;
			}
		}
		else
		{	// enum		-> nop : assign
			TP(fp, tab); 
			_U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
			needElse = FALSE;
		}
	}
	*_else = needElse;
	return TRUE;
}
static bool_t _U_enum_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (p->isPointer)
	{	// enum *	-> delete : not referenced only
		if (UnionMemberEntry_isReferenced(p) == FALSE)
		{
			TP(fp, tab); _memb_del_with_api(fp, FALSE, var, p->type, p->instance, s);
			ret = TRUE;
		}
	}
	else
	{	// enum		-> nop
	}
	return ret;
}
static bool_t _U_enum_dump(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, 
						 PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
	needElse = _dump_enum(fp, FALSE, var, p->type, p->isPointer, p->instance, s, ds, tabbed, tab, needElse);
	*_else = needElse;
	return TRUE;
}
// ENUMERATE
///////////////////////////////////////////////////////////////////////////////

static int *_U_func = NULL;
///////////////////////////////////////////////////////////////////////////////
// FUNCTION
static bool_t _U_func_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t needElse = *_else;
	str_t e_tn = ObjectInfo_nameOf(p->type);

	Dz1ThreadA_ftprintf(fp, tab, "// _U_func_clone\n");
	if (Dz1Str_isVoid(src))
	{
		char caster[256];
		if (p->isPointer)
		{	// func *	-> error
			TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
		}
		else
		{	// func		-> assign
			_std_snprintfA(caster, sizeof(caster), "(%s)", e_tn);
			TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
			needElse = FALSE;
		}
	}
	else
	{
		if (p->isPointer)
		{	// func *	-> error
			TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
		}
		else
		{	// func		-> assign
			TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
			needElse = FALSE;
		}
	}
	*_else = needElse;
	return TRUE;
}
static bool_t _U_func_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	return FALSE;
}
static bool_t _U_func_dump(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
	needElse = _dump_address(fp, FALSE, "", var, p->instance, ds, tabbed, tab, needElse);
	*_else = needElse;
	return TRUE;
}
// FUNCTION
///////////////////////////////////////////////////////////////////////////////

static int *_U_cst = NULL;
///////////////////////////////////////////////////////////////////////////////
// CONSTRUCT
static bool_t _U_cst_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t needElse = *_else;
	str_t e_tn = ObjectInfo_nameOf(p->type);

	Dz1ThreadA_ftprintf(fp, tab, "// _U_cst_clone\n");
	if (Dz1Str_isVoid(src))
	{	// for new
		char caster[256];
		if (p->isPointer)
		{	// struct *, union *, array *, index *	-> assign
			_std_snprintfA(caster, sizeof(caster), "(%s *)", e_tn);
			TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
			needElse = FALSE;
		}
		else
		{	// struct, union, array, index
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct, union -> copy : ignore referenced flag
				_std_snprintfA(caster, sizeof(caster), "(%s *)", e_tn);
				TP(fp, tab); 
				needElse = _U_memb_copy_with_api(fp, dst, p, caster, "ptr", s, needElse);
				break;
			default:											// array, index -> error
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
	}
	else
	{	// for clone
		if (p->isPointer)
		{	// struct *, union *, array *, index *	-> clone : not referenced only
			if (UnionMemberEntry_isReferenced(p) == FALSE)	
			{
				TP(fp, tab);
				needElse = _U_memb_clone_with_api(fp, dst, p, src, p->instance, s, needElse);
			}
			else
			{
				TP(fp, tab); 
				_U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
				needElse = FALSE;
			}
		}
		else
		{	// struct, union, array, index
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct, union -> copy : ignore referenced flag
				TP(fp, tab); 
				needElse = _U_memb_copy_with_api(fp, dst, p, src, p->instance, s, needElse);
				break;
			default:											// array, index -> error
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
	}
	*_else = needElse;
	return TRUE;
}

static bool_t _U_cst_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (p->isPointer)
	{	// struct *, union *, array *, index *	-> delete : not referenced only
		if (UnionMemberEntry_isReferenced(p) == FALSE)	
		{
			TP(fp, tab); _memb_del_with_api(fp, FALSE, var, p->type, p->instance, s);
			ret = TRUE;
		}
	}
	else
	{	// struct, union, array, index
		switch(o->type)
		{
		case ObjectType_structure: case ObjectType_union:	// struct, union -> purge
			TP(fp, tab); _memb_purge_with_api(fp, FALSE, var, p->type, p->instance, s);
			ret = TRUE;
			break;
		case ObjectType_array: case ObjectType_index:		// array, index -> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	return ret;
}

static bool_t __U_cst_dump(FILE *fp, str_t tn, str_t prefix, str_t var, UnionMemberEntry *p, ObjectInfo *o, 
						 PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t needElse)
{
	bool_t dump_support = (ObjectInfo_apiOf(p->type, s) & (ds->support_flag)) ? TRUE : FALSE;
	switch(o->type)
	{
	case ObjectType_structure: 
		// struct a, *a;
		if (strcmp(ObjectInfo_nameOf(p->type), tn) == 0)
		{	// recursive member -> default = ptr dump, possible cascade
			if (p->dumpMode == MemberDumpMode_cascade && dump_support)
				needElse = _dump_using_api(fp, FALSE, prefix, var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			else needElse = _dump_address(fp, FALSE, prefix, var, p->instance, ds, tabbed, tab, needElse);
		}
		else
		{	// normal member -> default = api_dump, possible : valdump, cascade
			if (dump_support == FALSE || p->dumpMode == MemberDumpMode_value)
				needElse = _dump_address(fp, FALSE, prefix, var, p->instance, ds, tabbed, tab, needElse);
			// dump_support is always TRUE
			else if (p->dumpMode == MemberDumpMode_cascade)
				_dump_using_linked_api(fp, FALSE, prefix, var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			else needElse = _dump_using_api(fp, FALSE, prefix, var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
		}
		break;
	case ObjectType_union:
		// union b, *b; -> default = normal, possible val dump
		if (dump_support == FALSE || p->dumpMode == MemberDumpMode_value)
			needElse = _dump_address(fp, FALSE, prefix, var, p->instance, ds, tabbed, tab, needElse);
		else needElse = _dump_using_api(fp, FALSE, prefix, var, p->type, p->instance, ".", s, ds, tabbed, tab, needElse);
		break;
	case ObjectType_array: case ObjectType_index:
		// array a, *a, index b, *b -> default = api dump, possible val dump
		if (dump_support == FALSE || p->dumpMode == MemberDumpMode_value)
			needElse = _dump_address(fp, FALSE, prefix, var, p->instance, ds, tabbed, tab, needElse);
		else needElse = _dump_using_api(fp, FALSE, prefix, var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
		break;
	default:
		TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
		break;
	}
	return needElse;
}

static bool_t _U_cst_dump(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, 
						PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
//	bool_t dump_support = (ObjectInfo_apiOf(p->type) & (OBJECT_API_DUMP | OBJECT_API_USER_DUMP)) ? TRUE : FALSE;
	if (p->isPointer)
		needElse = __U_cst_dump(fp, tn, "", var, p, o, s, ds, tabbed, tab, needElse);	// struct *, union *, array *, index *
	else needElse = __U_cst_dump(fp, tn, "&", var, p, o, s, ds, tabbed, tab, needElse);	// struct, union, array, index
	*_else = needElse;
	return TRUE;
}
// CONSTRUCT
///////////////////////////////////////////////////////////////////////////////

static int *_U_imp = NULL;
///////////////////////////////////////////////////////////////////////////////
// IMPORT TYPE
static bool_t _U_imp_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_needElse)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_needElse;
	ExternInfo *info = (ExternInfo *)o->info;
	ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;

	str_t e_tn = ObjectInfo_prefixOf(p->type, s);

	Dz1ThreadA_ftprintf(fp, tab, "// _U_imp_clone\n");
	if (Dz1Str_isVoid(src))
	{	// for new
		char caster[256];
		if (p->isPointer)
		{	// native *, reference *
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:		// assign
				_std_snprintfA(caster, sizeof(caster), "(%s *)", e_tn);
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
				needElse = FALSE;
				ret = TRUE;
				break;
			case ExternInfoStatic_primitive_ptr:	// error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// native, reference
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:		// assign
				_std_snprintfA(caster, sizeof(caster), "*(%s *)", e_tn);
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
				needElse = FALSE;
				ret = TRUE;
				break;
			case ExternInfoStatic_primitive_ptr:	// assign
				_std_snprintfA(caster, sizeof(caster), "(%s *)", e_tn);
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, caster, "ptr");
				needElse = FALSE;
				ret = TRUE;
				break;
			case ExternInfoStatic_typical_union: case ExternInfoStatic_construct: // copy
				_std_snprintfA(caster, sizeof(caster), "(%s *)", e_tn);
				TP(fp, tab); needElse = _U_memb_copy_with_api(fp, dst, p, caster, "ptr", s, needElse);
				ret = TRUE;
				break;
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	else
	{	// for clone
		if (p->isPointer)
		{	// native *, reference *
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:
				if (UnionMemberEntry_isReferenced(p) == FALSE)	
				{
					TP(fp, tab);
					needElse = _U_memb_clone_with_api(fp, dst, p, src, p->instance, s, needElse);
				}
				else
				{
					TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
					needElse = FALSE;
				}
				ret = TRUE;
				break;
			case ExternInfoStatic_primitive_ptr:	// error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// native, reference
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:		// assign
				TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
				needElse = FALSE;
				break;
			case ExternInfoStatic_primitive_ptr:	// clone : not referenced
				if (UnionMemberEntry_isReferenced(p) == FALSE)	
				{
					TP(fp, tab);
					needElse = _U_memb_clone_with_api(fp, dst, p, src, p->instance, s, needElse);
				}
				else
				{
					TP(fp, tab); _U_memb_assigne_code(fp, dst, p->instance, src, p->instance);
					needElse = FALSE;
				}
				ret = TRUE;
				break;
			case ExternInfoStatic_typical_union: case ExternInfoStatic_construct: // copy
				TP(fp, tab); needElse = _U_memb_copy_with_api(fp, dst, p, src, p->instance, s, needElse);
				ret = TRUE;
				break;
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	*_needElse = needElse;
	return ret;
}

static bool_t _U_imp_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	ExternInfo *info = (ExternInfo *)o->info;
	ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;
	if (p->isPointer)
	{	// native *, reference *
		switch(origin_type)
		{
		case ExternInfoStatic_primitive:		// delete : not referenced only
		case ExternInfoStatic_typical_union:
		case ExternInfoStatic_construct:
			if (UnionMemberEntry_isReferenced(p) == FALSE)
			{
				TP(fp, tab); _memb_del_with_api(fp, FALSE, var, p->type, p->instance, s);
				ret = TRUE;
			}
			break;
		case ExternInfoStatic_primitive_ptr:	// error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	else
	{	// native, reference
		switch(origin_type)
		{
		case ExternInfoStatic_primitive:		// no action
			break;
		case ExternInfoStatic_primitive_ptr:	// delete : not referenced only
			if (UnionMemberEntry_isReferenced(p) == FALSE)	
			{
				TP(fp, tab);
				_memb_del_with_api(fp, FALSE, var, p->type, p->instance, s);
				ret = TRUE;
			}
			break;
		case ExternInfoStatic_typical_union:	// purge
		case ExternInfoStatic_construct:
			TP(fp, tab);
			_memb_purge_with_api(fp, FALSE, var, p->type, p->instance, s);
			ret = TRUE;
			break;
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	return ret;
}
static bool_t _U_imp_dump(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
	ExternInfo *info = (ExternInfo *)o->info;
	ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;
	bool_t dump_support = (ObjectInfo_apiOf(p->type, s) & (ds->support_flag)) ? TRUE : FALSE;
	if (p->isPointer)
	{	// native *, reference *
		switch(origin_type)
		{
		case ExternInfoStatic_typical_union:	// dump using api(union)
			if (dump_support == FALSE)
				needElse = _dump_address(fp, FALSE, "", var, p->instance, ds, tabbed, tab, needElse);
			else needElse = _dump_using_api(fp, FALSE, "", var, p->type, p->instance, ".", s, ds, tabbed, tab, needElse);
			break;
		case ExternInfoStatic_primitive:
		case ExternInfoStatic_construct:		// dump using api
			if (dump_support == FALSE)
				needElse = _dump_address(fp, FALSE, "", var, p->instance, ds, tabbed, tab, needElse);
			else needElse = _dump_using_api(fp, FALSE, "", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			break;
		case ExternInfoStatic_primitive_ptr:	// error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			break;
		}
	}
	else
	{	// native, reference
		switch(origin_type)
		{
		case ExternInfoStatic_typical_union:	// dump using api(union) + "&"
			if (dump_support == FALSE)
				needElse = _dump_address(fp, FALSE, "&", var, p->instance, ds, tabbed, tab, needElse);
			else needElse = _dump_using_api(fp, FALSE, "&", var, p->type, p->instance, ".", s, ds, tabbed, tab, needElse);
			break;
		case ExternInfoStatic_primitive:
		case ExternInfoStatic_construct:		// dump using api + "&"
			if (dump_support == FALSE)
				needElse = _dump_address(fp, FALSE, "&", var, p->instance, ds, tabbed, tab, needElse);
			else needElse = _dump_using_api(fp, FALSE, "&", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			break;
		case ExternInfoStatic_primitive_ptr:	// dump using api
			if (dump_support == FALSE)
				needElse = _dump_address(fp, FALSE, "", var, p->instance, ds, tabbed, tab, needElse);
			else needElse = _dump_using_api(fp, FALSE, "", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			break;
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			break;
		}
	}
	*_else = needElse;
	return TRUE;
}
// IMPORT TYPE
///////////////////////////////////////////////////////////////////////////////

typedef struct UnionMemberPublishAPI
{
	ObjectInstanceType	 type;
	bool_t				 (*clone_code)(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else);
	bool_t				 (*del_code)(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab);
	bool_t				 (*dump_code)(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else);
} UnionMemberPublishAPI;
#define UnionMemberPublishAPI_NULL				{ ObjectInstanceType_max, NULL, NULL, NULL }
#define UnionMemberPublishAPI_entry(type, pfx)	{ type, pfx##_clone, pfx##_del, pfx##_dump }
static UnionMemberPublishAPI *UnionMemberPublishAPI_find(UnionMemberPublishAPI *tbl, ObjectInstanceType t)
{
	UnionMemberPublishAPI *i;
	for (i = tbl; i->type != ObjectInstanceType_max; i++)
		if (i->type == t) return i;
	return NULL;
}

static UnionMemberPublishAPI unionMemberPublishAPI[] =
{
	UnionMemberPublishAPI_entry(ObjectInstanceType_primitive,	_U_prim),
	UnionMemberPublishAPI_entry(ObjectInstanceType_enumerate,	_U_enum),
	UnionMemberPublishAPI_entry(ObjectInstanceType_func,		_U_func),
	UnionMemberPublishAPI_entry(ObjectInstanceType_structure,	_U_cst),
	UnionMemberPublishAPI_entry(ObjectInstanceType_union,		_U_cst),
	UnionMemberPublishAPI_entry(ObjectInstanceType_array,		_U_cst),
	UnionMemberPublishAPI_entry(ObjectInstanceType_index,		_U_cst),

	UnionMemberPublishAPI_entry(ObjectInstanceType_extern,		_U_imp),
	UnionMemberPublishAPI_entry(ObjectInstanceType_reference,	_U_imp),
	UnionMemberPublishAPI_NULL
};


static void _U_array_assigne_code(FILE *fp, str_t dst, UnionMemberEntry *memb, str_t src)
{
	if (Dz1Str_isVoid(src))
	{	// for new
		char caster[256];
		str_t e_tn = ObjectInfo_nameOf(memb->type);
		_std_snprintfA(caster, sizeof(caster), "(%s %s*)", e_tn, memb->isPointer ? "*" : "");
		_U_memb_assigne_code(fp, dst, memb->instance, caster, "ptr");
	}
	else
	{	// for clone
		_U_memb_assigne_code(fp, dst, memb->instance, src, memb->instance);
	}
}

static bool_t _U_array_clone_code(FILE *fp, str_t tn, str_t dst, str_t _src, UnionMemberEntry *p, PublishSpec *s, bool_t needElse)
{
	char buf[1024], cnt[256] = "";;
	PublishErrorSpec *error = s->error;
	str_t src_var = Dz1Str_isVoid(_src) ? "ptr" : p->instance;
	str_t _ptr = Dz1Str_isVoid(_src) ? "" : "->x.";

	if (strstr(p->end_of_arr, "$$") != NULL)
	{	// arrZ type
	}
	else if (Dz1StrA_isDigitStr(p->end_of_arr))
	{	// fixed size type
		_std_snprintfA(cnt, sizeof(cnt), "%s, ", p->end_of_arr);
	}
	else
	{	// count variable type
	}

	//		 	  1     I J K              2     3    4  5        6 7 8   9                   A
	fprintf(fp, "%sif (%s%s%s != NULL && (%s->x.%s = %s_%s_clone(%s%s%s, %serrp)) == NULL) { %s; }\n", 
				needElse ? "else " : "",		// 1
				_src, _ptr, src_var,			// I J K
				dst, p->instance,				// 2 3
				tn, p->instance,				// 4 5
				_src, _ptr, src_var, cnt,		// 6 7 8 9
				error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));	// A
	needElse = TRUE;
	return needElse;
}

static void _U_array_del_code(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p)
{	
	char cnt[256] = "";
	if (strstr(p->end_of_arr, "$$") != NULL)
	{	// arrZ type
	}
	else if (Dz1StrA_isDigitStr(p->end_of_arr))
	{	// fixed size type
		_std_snprintfA(cnt, sizeof(cnt), ", %s", p->end_of_arr);
	}
	else
	{	// count variable type
	}
	//			  1  2      3     4 5
	fprintf(fp, "%s_%s_del(%s->x.%s%s);\n",
				tn, p->instance,		// 1 2
				var, p->instance, cnt);	// 3 4 5
}

static int *_U_primA = NULL;
///////////////////////////////////////////////////////////////////////////////
// PRIMITIVE Array
static bool_t _U_primA_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t needElse = *_else;
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		NativeStorage storage = ObjectInfo_getPrimStorage(o);

		if (p->isPointer)
		{	// int *[], real *[], str *[], void *[]
			switch(storage)
			{
			case NativeStorage_data:		// int *[], real *[] -> reference or storage array api
			case NativeStorage_none: 		// void *			 -> reference or storage array api
				TP(fp, tab);
				needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
				break;
			case NativeStorage_address:		// str *		 	 -> error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		else
		{	// int [], real [], str [], void []
			switch(storage)
			{
			case NativeStorage_data:	 	// int [], real [] -> reference array api
			case NativeStorage_address:		// str []		   -> reference or storage array api
				TP(fp, tab); needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
				break;
			case NativeStorage_none:		// void		 -> error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
	}
	else
	{
		TP(fp, tab); _U_array_assigne_code(fp, dst, p, src);
		needElse = FALSE;
	}
	*_else = needElse;
	return TRUE;
}

static bool_t _U_primA_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		NativeStorage storage = ObjectInfo_getPrimStorage(o);
		if (p->isPointer)
		{	// int *, real *, str *, void *
			switch(storage)
			{
			case NativeStorage_data:	// int *[], real *[]
			case NativeStorage_none:	// void *[]
				TP(fp, tab); _U_array_del_code(fp, tn, var, p);
				break;
			case NativeStorage_address:	// str *[]	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{
			switch(storage)
			{
			case NativeStorage_data:	// int [], real []
			case NativeStorage_address:	// str []
				TP(fp, tab); _U_array_del_code(fp, tn, var, p);
				break;
			case NativeStorage_none:			// void	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	return ret;
}
// PRIMITIVE Array
///////////////////////////////////////////////////////////////////////////////

static int *_U_enumA = NULL;
///////////////////////////////////////////////////////////////////////////////
// ENUMERATE Array
static bool_t _U_enumA_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		if (p->isPointer)
		{	// enum *[]
			TP(fp, tab);
			needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
		}
		else
		{	// enum	[]
			TP(fp, tab); needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
		}
		ret = TRUE;
	}
	else
	{
		TP(fp, tab); _U_array_assigne_code(fp, dst, p, src);
		needElse = FALSE;
	}
	*_else = needElse;
	return ret;
}

static bool_t _U_enumA_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		TP(fp, tab); 
		if (p->isPointer)
		{
			_U_array_del_code(fp, tn, var, p);	// enum *[]
		}
		else _U_array_del_code(fp, tn, var, p);	// enum []
	}
	return TRUE;
}
// ENUMERATE Array
///////////////////////////////////////////////////////////////////////////////

static int *_U_funcA = NULL;
///////////////////////////////////////////////////////////////////////////////
// FUNCTION Array
static bool_t _U_funcA_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		if (p->isPointer)	//	func *[] -> error
		{
			Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
			ret = TRUE;
		}
		else
		{	//					func []
			TP(fp, tab);
			needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
		}
		ret = TRUE;
	}
	else
	{
		TP(fp, tab); _U_array_assigne_code(fp, dst, p, src);
		needElse = FALSE;
	}
	*_else = needElse;
	return ret;
}

static bool_t _U_funcA_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (p->isPointer)	// func *[] -> error
		Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate del code for %s\"\n", p->instance);
	else				// func []
	{
		if (UnionMemberEntry_isReferenced(p) == FALSE)
		{
			TP(fp, tab);
			_U_array_del_code(fp, tn, var, p);
		}
	}

	return TRUE;
}
// FUNCTION Array
///////////////////////////////////////////////////////////////////////////////

static int *_U_cstA = NULL;
///////////////////////////////////////////////////////////////////////////////
// CONSTRUCT Array
static bool_t _U_cstA_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		if (p->isPointer)
		{	// struct *[], union *[], array *[], index *[]
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:
				// struct *[], union *[]
				TP(fp, tab);
				needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
				break;
			case ObjectType_array: case ObjectType_index:
			default:
				// array *[], index *[]	-> error
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		else
		{	// struct [], union [], array [], index []
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:
				// struct [], union []
				TP(fp, tab); needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
				break;
			case ObjectType_array: case ObjectType_index:
			default:
				// array [], index []	-> error
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		ret = TRUE;
	}
	else
	{
		TP(fp, tab); _U_array_assigne_code(fp, dst, p, src);
		needElse = FALSE;
	}
	*_else = needElse;
	return ret;
}

static bool_t _U_cstA_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		NativeStorage storage = ObjectInfo_getPrimStorage(o);
		if (p->isPointer)
		{	// struct *[], union *[], array *[], index *[]
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct *[], union *[]
				TP(fp, tab);
				_U_array_del_code(fp, tn, var, p);
				break;
			case ObjectType_array: case ObjectType_index:		// array *[], index *[]	-> error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate del code for %s\"\n", p->instance);
				break;
			}
		}
		else
		{	// struct [], union [], array [], index []
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct [], union []
				TP(fp, tab); _U_array_del_code(fp, tn, var, p);
				break;
			case ObjectType_array: case ObjectType_index:		// array [], index []	-> error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		ret = TRUE;
	}
	return ret;
}
// CONSTRUCT Array
///////////////////////////////////////////////////////////////////////////////

static int *_U_impA = NULL;
///////////////////////////////////////////////////////////////////////////////
// IMPORT Array
static bool_t _U_impA_clone(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		ExternInfo *info = (ExternInfo *)o->info;
		ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;

		if (p->isPointer)
		{	// native *, reference *
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:
				TP(fp, tab); needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
				break;
			case ExternInfoStatic_primitive_ptr:	// error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		else
		{	// native, reference
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_primitive_ptr:
			case ExternInfoStatic_typical_union: case ExternInfoStatic_construct: // copy
				TP(fp, tab); needElse = _U_array_clone_code(fp, tn, dst, src, p, s, needElse);
				break;
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		ret = TRUE;
	}
	else
	{
		TP(fp, tab); _U_array_assigne_code(fp, dst, p, src);
		needElse = FALSE;
	}
	*_else = needElse;
	return ret;
}

static bool_t _U_impA_del(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (UnionMemberEntry_isReferenced(p) == FALSE)
	{
		ExternInfo *info = (ExternInfo *)o->info;
		ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;

		if (p->isPointer)
		{	// native *, reference *
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:
				TP(fp, tab);
				_U_array_del_code(fp, tn, var, p);
				break;
			case ExternInfoStatic_primitive_ptr:	// error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate del code for %s\"\n", p->instance);
				break;
			}
		}
		else
		{	// native, reference
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_primitive_ptr:
			case ExternInfoStatic_typical_union: case ExternInfoStatic_construct: // copy
				TP(fp, tab); _U_array_del_code(fp, tn, var, p);
				break;
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate del code for %s\"\n", p->instance);
				break;
			}
		}
		ret = TRUE;
	}
	return ret;
}
// IMPORT Array
///////////////////////////////////////////////////////////////////////////////

#define UnionMemberPublishAPI_arr_entry(type, pfx)	{ type, pfx##_clone, pfx##_del, NULL }
static UnionMemberPublishAPI unionArrMemberPublishAPI[] =
{
	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_primitive,	_U_primA),
	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_enumerate,	_U_enumA),
	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_func,		_U_funcA),
	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_structure,	_U_cstA),
	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_union,		_U_cstA),
	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_array,		_U_cstA),
	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_index,		_U_cstA),

	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_extern,		_U_impA),
	UnionMemberPublishAPI_arr_entry(ObjectInstanceType_reference,	_U_impA),
	UnionMemberPublishAPI_NULL
};

bool_t UnionMemberEntry_clone_code(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{
	bool_t ret = FALSE;
	ObjectInfo *memb = p->type;
	bool_t needElse = *_else;
	UnionMemberPublishAPI *api = NULL;	
	if (StructMemberEntry_isArray(p))
		api = UnionMemberPublishAPI_find(unionArrMemberPublishAPI, o->type);
	else api = UnionMemberPublishAPI_find(unionMemberPublishAPI, o->type);

	if (api == NULL)
	{
		Dz1ThreadA_ftprintf(fp, tab,	"#error Unknown api for %s\n", memb->name);
		needElse = FALSE;
		ret = TRUE;
	}
	else if (api->clone_code == NULL) { }
	else ret = api->clone_code(fp, tn, dst, src, p, o, s, tab, &needElse);
	*_else = needElse;
	return ret;
}

void UnionMemberEntry_del_code(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	ObjectInfo *memb = p->type;
	UnionMemberPublishAPI *api = NULL;	
	if (StructMemberEntry_isArray(p))
		api = UnionMemberPublishAPI_find(unionArrMemberPublishAPI, o->type);
	else api = UnionMemberPublishAPI_find(unionMemberPublishAPI, o->type);

	if (api == NULL)
		Dz1ThreadA_ftprintf(fp, tab,	"#error Unknown api for %s\n", memb->name);
	else if (api->clone_code == NULL) { }
	else api->del_code(fp, tn, var, p, o, s, tab);
}

bool_t UnionMemberEntry_dump_code(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, int tab, bool_t *_else)
{
	bool_t ret = FALSE;
	ObjectInfo *memb = p->type;
	UnionMemberPublishAPI *api = NULL;
	if (UnionMemberEntry_isArray(p))
		ret = _array_memb_dump_code(fp, tn, var, "->x.", p->instance, p->end_of_arr, ds, FALSE, tab, _else);
	else if ((api = UnionMemberPublishAPI_find(unionMemberPublishAPI, o->type))  == NULL)
	{
		TP(fp, tab); fprintf(fp, "#error Unknown api for %s\n", memb->name);
	}
	else if (api->dump_code == NULL) { }
	else ret = api->dump_code(fp, tn, var, p, o, s, ds, FALSE, tab, _else);
	return ret;
}

bool_t UnionMemberEntry_cmp_code(FILE *fp, str_t tn, str_t l, str_t r, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{
	ObjectInfo *memb = p->type;
	bool_t needElse = *_else;
	bool_t type_is_ptr = ObjectInfo_isAddress(o);
	if (p->isPointer && type_is_ptr)		// double pointer -> error
		Dz1ThreadA_ftprintf(fp, tab, "#error Can't generate compare code for %s\n", memb->name);
	else if (UnionMemberEntry_isArray(p))	// Array -> error
		Dz1ThreadA_ftprintf(fp, tab, "#error Can't compare inner array type %s\n", memb->name);
	else if (!p->isPointer && !type_is_ptr)	// scalar -> compare with amp
	{
		if (o->type == ObjectType_enumerate)
		{
			Dz1ThreadA_ftprintf(fp, tab, "%sif ((ret = (int)(%s->x.%s - %s->x.%s)) != 0) { }\n", needElse ? "else " : "", l, p->instance, r, p->instance);
			needElse = TRUE;
		}
		else
		{
			TP(fp, tab); needElse = _memb_cmp_with_api(fp, FALSE, l, r, "&", p->type, p->instance, s, needElse);
		}
	}
	else
	{										// single pointer -> compare
		TP(fp, tab); fprintf(fp, "%sif (a->x.%s == NULL && b->x.%s == NULL) ret = 0;\n", needElse ? "else " : "", p->instance, p->instance);
		TP(fp, tab); fprintf(fp, "else if (a->x.%s == NULL /*&& b->x.%s != NULL*/) ret = -1;\n", p->instance, p->instance);
		TP(fp, tab); fprintf(fp, "else if (/*a->x.%s != NULL &&*/ b->x.%s == NULL) ret = 1;\n", p->instance, p->instance);
		if (o->type == ObjectType_enumerate)
		{
			Dz1ThreadA_ftprintf(fp, tab, "%sif ((ret = (int)(*%s->x.%s - *%s->x.%s)) != 0) { }\n", needElse ? "else " : "", l, p->instance, r, p->instance);
			needElse = TRUE;
		}
		else
		{
			needElse = TRUE;
			TP(fp, tab); needElse = _memb_cmp_with_api(fp, FALSE, l, r, "", p->type, p->instance, s, needElse);
		}
	}
	*_else = needElse;
	return TRUE;
}

