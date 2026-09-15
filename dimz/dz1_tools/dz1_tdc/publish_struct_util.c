#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include "publish_inner_array.h"
#include "publish_struct_util.h"

///////////////////////////////////////////////////////////////////////////////
// Member parameter publish
void StructMemberEntry_default_value(FILE *fp, StructMemberEntry *p, bool_t print_comma)
{
	str_t comma = print_comma ? ", " : "";
	if (p->isPointer || StructMemberEntry_isArray(p)) fprintf(fp, "%sNULL", comma);
	else
	{	// 포인터나 어레이가 아닌 경우
		ObjectInfo *memb = p->type;
		ObjectInfo *tgt = ObjectInfo_getOrigin(memb);
		PrimitiveInfo *pr_info = NULL;
		ExternInfo *ext_info = NULL;
		switch(tgt->type)
		{
		case ObjectType_primitive:														// PrimitiveInfo
			pr_info = (PrimitiveInfo *)tgt->info;
			switch(pr_info->storage)
			{
			case NativeStorage_address: fprintf(fp, "%sNULL", comma); break;				// address primitive
			case NativeStorage_data: fprintf(fp, "%s0", comma); break;						// data primitive
			case NativeStorage_none: break;													// void
			default:
				fprintf(fp, "%s#error %s %s is %s", comma, memb->name, p->instance, ObjectTypeStr(tgt->type)); // don't care
				break;
			}
			break;
		case ObjectType_enumerate: fprintf(fp, "%s%s_max", comma, tgt->name); break;	// EnumInfo				typedef enum ? ...
		case ObjectType_structure:														// StructureInfo		typedef struct ...
		case ObjectType_union:															// UnionInfo			typedef union ...
		case ObjectType_func: fprintf(fp, "%sNULL", comma); break;						// FunctionInfo			typedef func {ret_type} ? ...
		case ObjectType_extern:															// ExternInfo			typedef native ?...
		case ObjectType_reference:														// ExternInfo			typedef reference ...
			ext_info = (ExternInfo *)tgt->info;
			switch(ext_info->isStatic)
			{
			case ExternInfoStatic_primitive: fprintf(fp, "%s0", comma); break;
			case ExternInfoStatic_primitive_ptr:
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct: fprintf(fp, "%sNULL", comma); break;
			default:
				fprintf(fp, "%s#error %s %s is %s", comma, memb->name, p->instance, ObjectTypeStr(tgt->type));
				break;
			}
			break;
		case ObjectType_defined:	// DefinedInfo	[p]		typedef {[struct|union]} {tgt_type} {src_type}...
		case ObjectType_declare:	// str_t		[p]		struct|union|enum ?;
		case ObjectType_constant:	// ConstantInfo	[p]		typedef constant ? ...;
		case ObjectType_macro:		// {no info}	[p]		# {if|ifdef|ifndef|else|elif|endif} ...
		case ObjectType_bits:		// BitsInfo		[x]
		case ObjectType_array:		// ArrayInfo	[e]		typedef {[unique] table|array} ...
		case ObjectType_index:		// IndexInfo	[e]		typedef index ? ...
		default:
			fprintf(fp, "%s#error %s %s is %s", comma, memb->name, p->instance, ObjectTypeStr(tgt->type));
			break;
		}
	}
}
// Member parameter publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member argument publish
ssize_t StructMemberEntry_argPrint(FILE *fp, bool_t print_comma, bool_t print_nl, int front_space, StructMemberEntry *p, bool_t isHeader)
{
	ssize_t ret = 0;
	char buf[1024], *cp = buf;
	size_t sz = sizeof(buf);
	ssize_t n;

	MemberEntryNames info;
	MemberEntryNames_get(&info, p->isForwarded, p->type, p->isPointer, p->memb_flags, isHeader);

	if (print_comma)	{ strcpy(cp, ", "); cp += 2; ret += 2; sz -= 2; }
	if (print_nl)		{ *cp++ = '\n'; ret++; sz--; }
	if (front_space)
	{
		int tab = front_space / TAB_SIZE;
		int spc = front_space % TAB_SIZE;

		while(tab--) { *cp++ = '\t'; ret += TAB_SIZE; sz += TAB_SIZE; }
		while(spc--) { *cp++ = ' '; ret++; sz++; }
	}
	n = _std_snprintfA(cp, sz, "%s %s%s%s", info.type, info.ptrs_args, p->instance, info.name_postfix);
	cp += n; ret += n; sz -= n;
	*cp = 0;
	if (fp != NULL) fputs(buf, fp);
#if 0
	if (fp != NULL)
	{
		if (print_comma)	ret += fprintf(fp, ", ");
		if (print_nl)		ret += fprintf(fp, "\n");
		if (front_space)
		{
			int tab = front_space / TAB_SIZE;
			int spc = front_space % TAB_SIZE;

			TP(fp, tab);
			while(spc--) Dz1Thread_fprintf(fp, " ");

			ret += front_space;
		}
		ret += fprintf(fp, "%s %s%s", info.type, info.ptrs, info.name);
	}
	else
	{
		char buf[1024];
		if (print_comma)	ret += 2;
		if (print_nl)		ret++;
		if (front_space)	ret += front_space;
		ret = _std_snprintfA(buf, sizeof(buf), "%s %s%s", info.type, info.ptrs, info.name);
	}
#endif
	return ret;
}
// Member argument publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member list argument publish
bool_t StructureMemberList_args(FILE *fp, StructMemberList *p, u32_t front_space, bool_t isHeader)
{
	bool_t ret = FALSE;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(p->fifo, NULL);
	if (c)
	{
		ssize_t arg_len = 0;
		bool_t comma = FALSE;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				if (StructMemberEntry_isArgInvolve(e))
				{
					arg_len += StructMemberEntry_argPrint(NULL, comma, FALSE, 0, e, isHeader);
					comma = TRUE;
				}
			}
		}

		if (arg_len > 0)
		{
			bool_t isFirst = TRUE, print_nl = TRUE;
			if (front_space + arg_len < 80) { print_nl = FALSE; front_space = 0; }

			for (Dz1FifoCursorForward(c))
			{
				if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				{
					if (StructMemberEntry_isArgInvolve(e))
					{
						if (isFirst)
						{
							if (StructMemberEntry_argPrint(fp, FALSE, FALSE, 0, e, isHeader) > 0)
								isFirst = FALSE;
						}
						else StructMemberEntry_argPrint(fp, TRUE, print_nl, front_space, e, isHeader);
					}
				}
			}
			ret = TRUE;
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
// Member list argument publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member list parameter publish
bool_t StructureMemberList_params(FILE *fp, StructMemberList *p)
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
				if (StructMemberEntry_isArgInvolve(e))
				{
					StructMemberEntry_default_value(fp, e, ret);
					ret = TRUE;
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}
// Member list parameter publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Member primitive code
static bool_t _S_memb_clone_with_api(FILE *fp, str_t dst, str_t src, StructMemberEntry *p, PublishSpec *spec, bool_t _else)
{
	char buf[1024];
	PublishPostFix *pfx = spec->postFix;
	PublishErrorSpec *error = spec->error;

	str_t e_tn = ObjectInfo_nameOf(p->type);
	str_t e_fx = ObjectInfo_prefixOf(p->type, spec);

	str_t _src_ptr = Dz1Str_isVoid(src) ? "" : "->";
	str_t _src_var = p->instance;

	//            1    2 3 4      5    7    8 9  A B C                   D
	fprintf(fp, "%sif (%s%s%s && (%s->%s = %s%s(%s%s%s, errp)) == NULL) %s;\n",
				_else ? "else " : "",		// 1
				src, _src_ptr, _src_var,	// 2 3 4
				dst, p->instance,			// 5 7
				e_fx, pfx->_clone,			// 8 9
				src, _src_ptr, _src_var,	// A B C
				error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL)); // D
	_else = TRUE;
	return _else;
}

static bool_t _S_memb_alloc_with_api(FILE *fp, str_t var, StructMemberEntry *p, PublishSpec *s, bool_t _else)
{
	char buf[1024];
	PublishPostFix *pfx = s->postFix;
	PublishErrorSpec *error = s->error;

	str_t e_tn = ObjectInfo_prefixOf(p->type, s);

	//            1      2   4    5 6                  7
	fprintf(fp, "%sif ((%s->%s = %s%s(errp)) == NULL) %s;\n",
				_else ? "else " : "",	// 1
				var, p->instance,		// 2 4
				e_tn, pfx->_gen,		// 5 6
				error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL)); // 7
	_else = TRUE;
	return _else;
}

static bool_t _S_memb_copy_with_api(FILE *fp, str_t dst, str_t src, StructMemberEntry *p, PublishSpec *s, bool_t _else)
{
	char buf[1024];
	PublishPostFix *pfx = s->postFix;
	PublishErrorSpec *error = s->error;

	str_t e_tn = ObjectInfo_prefixOf(p->type, s);
	str_t _src_ptr = Dz1Str_isVoid(src) ? "" : "->";
	str_t _src_amp = Dz1Str_isVoid(src) ? "" : "&";

	//			  1     2 3   4   6   7 8 9 A                   B
	fprintf(fp, "%sif (%s%s(&%s->%s, %s%s%s%s, errp) == FALSE) %s;\n",
				_else ? "else " : "",					// 1
				e_tn, pfx->_copy, dst, p->instance,		// 2 3 4 6
				_src_amp, src, _src_ptr, p->instance,	// 7 8 9 A
				error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL)); // B
	_else = TRUE;
	return _else;
}

static void _S_memb_assigne_code(FILE *fp, str_t dst, str_t src, str_t instance)
{	
	str_t _src_ptr = Dz1Str_isVoid(src) ? "" : "->";
	str_t _src_var = instance;

	//            1   3    4 5 6
	fprintf(fp, "%s->%s = %s%s%s;\n",
				dst, instance,				// 1 3
				src, _src_ptr, _src_var);	// 4 5 6
}
// Structure Member primitive code
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// StructMemberPublishAPI
typedef struct StructMemberPublishAPI
{
	ObjectInstanceType	 type;
	bool_t (*clone_code)(	FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else);
	bool_t (*alloc_code)(	FILE *fp, str_t tn, str_t var,			  StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else);
	bool_t (*assign_code)(	FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab);
	bool_t (*init_code)(	FILE *fp, str_t tn, str_t var,			  StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab);
	bool_t (*del_code)(		FILE *fp, str_t tn, str_t var,			  StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab);
	bool_t (*dump_code)(	FILE *fp, str_t tn, str_t var,			  StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else);
} StructMemberPublishAPI;
#define MemberPublishAPI_NULL	{ ObjectType_max, NULL, NULL, NULL, NULL }

static StructMemberPublishAPI *StructMemberPublishAPI_find(StructMemberPublishAPI *tbl, ObjectInstanceType t)
{
	StructMemberPublishAPI *i;
	for (i = tbl; i->type != ObjectInstanceType_max; i++)
		if (i->type == t) return i;
	return NULL;
}
// StructMemberPublishAPI
///////////////////////////////////////////////////////////////////////////////

static int _prim = 0;
///////////////////////////////////////////////////////////////////////////////
// PRIMITIVE
static bool_t _prim_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (Dz1Str_isVoid(src))
	{	// called from new
		if (p->isPointer)
		{	// int *, real *, str *, void *
			switch(storage)
			{
			case NativeStorage_data: break;		// int *, real * -> assign no matter referenced or not
			case NativeStorage_none: break;		// void *		 -> assign
			case NativeStorage_address:			// str *, 		 -> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// int, real, str, void
			switch(storage)
			{
			case NativeStorage_data: break;		// int, real -> assign
			case NativeStorage_address:			// str		 -> clone if not referenced
				if (StructMemberEntry_isReferenced(p) == FALSE)
				{
					TP(fp, tab); needElse = _S_memb_clone_with_api(fp, dst, src, p, s, needElse);
					ret = TRUE;
				}
				break;
			case NativeStorage_none:			// void		 -> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	else
	{
		if (p->isPointer)
		{	// int *, real *, str *, void *
			switch(storage)
			{
			case NativeStorage_data:	// int *, real *	-> clone : not referenced only
				if (StructMemberEntry_isReferenced(p) == FALSE)	
				{
					TP(fp, tab); needElse = _S_memb_clone_with_api(fp, dst, src, p, s, needElse);
					ret = TRUE;
				}
				break;
			case NativeStorage_none: break;		// void *	-> no clone: assign code will be published
			case NativeStorage_address:			// str *, 	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// int, real, str, void
			switch(storage)
			{
			case NativeStorage_data: break;	// int, real	-> no clone: assign code will be published
			case NativeStorage_address:				// str	-> clone : not referenced only
				if (StructMemberEntry_isReferenced(p) == FALSE)
				{								
					TP(fp, tab); needElse = _S_memb_clone_with_api(fp, dst, src, p, s, needElse);
					ret = TRUE;
				}
				break;
			case NativeStorage_none:				// void	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	*_else = needElse;
	return ret;
}

static bool_t _prim_alloc(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (p->isPointer)
	{	// int *, real *, str *, void *
		switch(storage)
		{
		case NativeStorage_data:	// int *, real *	-> no alloc
			break;
		case NativeStorage_none:			// void *	-> no alloc
			break;
		case NativeStorage_address:			// str *	-> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate init code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	else
	{
		switch(storage)
		{
		case NativeStorage_data:	// int, real, enum	-> no alloc
			break;
		case NativeStorage_address:				// str	-> no alloc
			break;
		case NativeStorage_none:				// void	-> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate init code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	*_else = needElse;
	return ret;
}

static bool_t _prim_init(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우
	bool_t ret = FALSE;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (p->isPointer)
	{	// int *, real *, str *, void *
		switch(storage)
		{
		case NativeStorage_data:	// int *, real * -> no init
		case NativeStorage_none:	// void *		 -> no init
			break;
		case NativeStorage_address:	// str *		 -> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate init code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	else
	{
		switch(storage)
		{
		case NativeStorage_data:	// int, real, enum	-> no init
		case NativeStorage_address:	// str				-> no init
			break;
		case NativeStorage_none:	// void				-> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate init code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	return ret;
}

static bool_t _prim_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (Dz1Str_isVoid(src))
	{	// called from new
		if (p->isPointer)
		{	// int *, real *, str *, void *
			switch(storage)
			{
			case NativeStorage_data:	// int *, real * -> assign
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
				break;
			case NativeStorage_none:	// void *		 -> assign
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
				break;
			case NativeStorage_address:	// str *		 -> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// int, real, enum, str, void
			switch(storage)
			{
			case NativeStorage_data:		// int, real	-> assgin
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
			case NativeStorage_address:		// str			-> assign if referenced
				if (StructMemberEntry_isReferenced(p))
				{
					TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
					ret = TRUE;
				}
				break;
			case NativeStorage_none:		// void			-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	else
	{	// called from clone
		if (p->isPointer)
		{	// int *, real *, str *, void *
			switch(storage)
			{
			case NativeStorage_data:	// int *, real * -> assign : only referenced
				if (StructMemberEntry_isReferenced(p))	
				{
					TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
					ret = TRUE;
				}
				break;
			case NativeStorage_none:	// void *		 -> assign
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
				break;
			case NativeStorage_address:	// str *		 -> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// int, real, enum, str, void
			switch(storage)
			{
			case NativeStorage_data:		// int, real	-> assgin
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
				break;
			case NativeStorage_address:				// str	-> assign : only referenced
				if (StructMemberEntry_isReferenced(p))
				{											
					TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
					ret = TRUE;
				}
				break;
			case NativeStorage_none:				// void	-> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	return ret;
}

static bool_t _prim_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// del 할때
	bool_t ret = FALSE;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (p->isPointer)
	{	// int *, real *, str *, void *
		switch(storage)
		{
		case NativeStorage_data:	
			if (StructMemberEntry_isReferenced(p) == FALSE)
			{						// int *, real * -> delete : not referenced only
				TP(fp, tab); _memb_del_with_api(fp, TRUE, var, p->type, p->instance, s);
				ret = TRUE;
			}
			break;
		case NativeStorage_none:	// void *		 -> nop
			break;
		case NativeStorage_address:	// str *		 -> error
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
		case NativeStorage_address:	// str			-> delete : not referenced only
			if (StructMemberEntry_isReferenced(p) == FALSE)
			{
				TP(fp, tab); _memb_del_with_api(fp, TRUE, var, p->type, p->instance, s);
				ret = TRUE;
			}
			break;
		case NativeStorage_none:	// void			-> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	return ret;
}

static bool_t _prim_dump(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, 
						 PublishSpec *spec, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{	// dump 할때
	bool_t needElse = *_else;
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (p->isPointer)
	{	// int *, real *, str *, void *
		switch(storage)
		{
		case NativeStorage_data:	// int *, real *	-> dump
			needElse = _dump_using_api(fp, TRUE, "", var, p->type, p->instance, " = ", spec, ds, tabbed, tab, needElse);
			break;
		case NativeStorage_none:			// void *	-> address dump
			needElse = _dump_address(fp, TRUE, "", var, p->instance, ds, tabbed, tab, needElse);
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
			needElse = _dump_using_api(fp, TRUE, "&", var, p->type, p->instance, " = ", spec, ds, tabbed, tab, needElse);
			break;
		case NativeStorage_address:			// str	-> dump
			needElse = _dump_using_api(fp, TRUE, "", var, p->type, p->instance, " = ", spec, ds, tabbed, tab, needElse);
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

static int _enum = 0;
///////////////////////////////////////////////////////////////////////////////
// ENUMERATE
static bool_t _enum_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (Dz1Str_isVoid(src))
	{
		if (p->isPointer)
		{	// enum *	-> nop : assign
		}
		else
		{	// enum		-> nop : assign
		}
	}
	else
	{
		if (p->isPointer)
		{	// enum *	-> clone : not referenced only
			if (StructMemberEntry_isReferenced(p) == FALSE)	
			{
				TP(fp, tab); needElse = _S_memb_clone_with_api(fp, dst, src, p, s, needElse);
				ret = TRUE;
			}
		}
		else
		{	// enum		-> nop : assign
		}
		*_else = needElse;
	}
	return ret;
}
static bool_t _enum_alloc(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (p->isPointer)
	{	// enum *	-> no alloc
	}
	else
	{	// enum		-> nop
	}
	*_else = needElse;
	return ret;
}
static bool_t _enum_init(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우
	bool_t ret = FALSE;
	if (p->isPointer)
	{	// enum *	-> no init
	}
	else
	{	// enum		-> default
		str_t _ptr = Dz1Str_isVoid(var) ? "" : "->";
		TP(fp, tab); fprintf(fp, "%s%s%s = %s_max;\n", var, _ptr, p->instance, ObjectInfo_nameOf(p->type));
		ret = TRUE;
	}
	return ret;
}

static bool_t _enum_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	if (Dz1Str_isVoid(src))
	{
		if (p->isPointer)
		{	// enum *	-> assign
			TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
			ret = TRUE;
		}
		else
		{	// enum		-> assign
			TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
			ret = TRUE;
		}
	}
	else
	{
		if (p->isPointer)
		{	// enum *	-> assign : referenced only
			if (StructMemberEntry_isReferenced(p))	
			{
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
			}
		}
		else
		{	// enum		-> assign
			TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
			ret = TRUE;
		}
	}
	return ret;
}
static bool_t _enum_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (p->isPointer)
	{	// enum *	-> delete : not referenced only
		if (StructMemberEntry_isReferenced(p) == FALSE)
		{
			TP(fp, tab); _memb_del_with_api(fp, TRUE, var, p->type, p->instance, s);
			ret = TRUE;
		}
	}
	else
	{	// enum		-> nop
	}
	return ret;
}
static bool_t _enum_dump(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, 
						 PublishSpec *spec, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
	needElse = _dump_enum(fp, TRUE, var, p->type, p->isPointer, p->instance, spec, ds, tabbed, tab, needElse);
	*_else = needElse;
	return TRUE;
}
// ENUMERATE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// FUNCTION
// no clone
// no alloc
// no init
static bool_t _func_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	if (Dz1Str_isVoid(src))
	{	// for new
		if (p->isPointer)
		{	// function *	-> error
			TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
		}
		else
		{	// function		-> assign
			TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
		}
	}
	else
	{	// for clone
		if (p->isPointer)
		{	// function *	-> error
			TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
		}
		else
		{	// function		-> assign
			TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
		}
	}
	return TRUE;
}
// no del
static bool_t _func_dump(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o,
						 PublishSpec *spec, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
	needElse = _dump_address(fp, TRUE, "", var, p->instance, ds, tabbed, tab, needElse);
	*_else = needElse;
	return TRUE;
}
// FUNCTION
///////////////////////////////////////////////////////////////////////////////

static int _cst = 0;
///////////////////////////////////////////////////////////////////////////////
// CONSTRUCT
static bool_t _cst_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_needElse)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_needElse;
	if (Dz1Str_isVoid(src))
	{	// for NEW
		if (p->isPointer)
		{	// struct *, union *, array *, index *	-> nop : assign
		}
		else
		{	// struct, union, array, index
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct, union -> copy : ignore referenced flag
				TP(fp, tab); needElse = _S_memb_copy_with_api(fp, dst, src, p, s, needElse);
				break;
			default:											// array, index -> error
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
			ret = TRUE;
		}
	}
	else
	{
		if (p->isPointer)
		{	// struct *, union *, array *, index *	-> clone : not referenced only
			if (StructMemberEntry_isReferenced(p) == FALSE)	
			{
				TP(fp, tab); needElse = _S_memb_clone_with_api(fp, dst, src, p, s, needElse);
				ret = TRUE;
			}
		}
		else
		{	// struct, union, array, index
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct, union -> copy : ignore referenced flag
				TP(fp, tab); needElse = _S_memb_copy_with_api(fp, dst, src, p, s, needElse);
				break;
			default:											// array, index -> error
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
			ret = TRUE;
		}
	}
	*_needElse = needElse;
	return ret;
}
static bool_t _cst_alloc(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_needElse)
{	// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우
	bool_t ret = FALSE;
	bool_t needElse = *_needElse;
	if (p->isPointer)
	{	// struct *, union *, array *, index *	-> clone : not referenced only
		switch(o->type)
		{
		case ObjectType_structure: case ObjectType_union:	// struct *, union * -> nop : already be NULL by calloc
			break;
		case ObjectType_array: case ObjectType_index:		// array *, index * -> alloc
			TP(fp, tab); needElse = _S_memb_alloc_with_api(fp, var, p, s, needElse);
			ret = TRUE;
			break;
		}
	}
	else
	{	// struct, union, array, index
		switch(o->type)
		{
		case ObjectType_structure: case ObjectType_union:	// struct, union -> nop : already be cleaned by calloc
			break;
		case ObjectType_array: case ObjectType_index:		// array, index -> error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate alloc code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	*_needElse = needElse;
	return ret;
}
static bool_t _cst_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	if (Dz1Str_isVoid(src))
	{
		if (p->isPointer)
		{	// struct *, union *, array *, index *	-> assign
			TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
			ret = TRUE;
		}
		else
		{	// struct, union, array, index
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct, union -> nop : already copy code published
				break;
			case ObjectType_array: case ObjectType_index:		// array, index -> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	else
	{
		if (p->isPointer)
		{	// struct *, union *, array *, index *	-> assign : referenced only
			if (StructMemberEntry_isReferenced(p))	
			{
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
			}
		}
		else
		{	// struct, union, array, index
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct, union -> nop : already copy code published
				break;
			case ObjectType_array: case ObjectType_index:		// array, index -> error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	return ret;
}
static bool_t _cst_init(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우
	bool_t ret = FALSE;
	if (p->isPointer)
	{	// struct *, union *, array *, index *	-> nop : already be NULL by calloc
	}
	else
	{	// struct, union, array, index -> nop : already cleaned by calloc
	}
	return ret;
}
static bool_t _cst_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (p->isPointer)
	{	// struct *, union *, array *, index *	-> delete : not referenced only
		if (StructMemberEntry_isReferenced(p) == FALSE)	
		{
			TP(fp, tab); _memb_del_with_api(fp, TRUE, var, p->type, p->instance, s);
			ret = TRUE;
		}
	}
	else
	{	// struct, union, array, index
		switch(o->type)
		{
		case ObjectType_structure: case ObjectType_union:	// struct, union -> purge
			TP(fp, tab); _memb_purge_with_api(fp, TRUE, var, p->type, p->instance, s);
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

static bool_t __cst_dump(FILE *fp, str_t tn, str_t prefix, str_t var, StructMemberEntry *p, ObjectInfo *o, 
						 PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t needElse)
{
	u32_t e_api = ObjectInfo_apiOf(p->type, s);
	bool_t dump_support = (e_api & ds->support_flag) ? TRUE : FALSE;
	switch(o->type)
	{
	case ObjectType_structure: 
		// struct a, *a;
		if (strcmp(ObjectInfo_nameOf(p->type), tn) == 0)
		{	// recursive member -> default = ptr dump, possible cascade
			Dz1ThreadA_ftprintf(fp, tab, "// Recursive member\n");
			if (dump_support && p->dumpMode == MemberDumpMode_cascade)
			{
				Dz1ThreadA_ftprintf(fp, tab, "// Cascade dump\n");
				_dump_using_linked_api(fp, TRUE, prefix, var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
				needElse = FALSE;
			}
			else
			{
				Dz1ThreadA_ftprintf(fp, tab, "// Recursive but address dump\n");
				needElse = _dump_address(fp, TRUE, prefix, var, p->instance, ds, tabbed, tab, needElse);
			}
		}
		else
		{	// normal member -> default = api_dump, possible : valdump, cascade
			Dz1ThreadA_ftprintf(fp, tab, "// Normal member\n");
			if (dump_support == FALSE || p->dumpMode == MemberDumpMode_value)
			{
				Dz1ThreadA_ftprintf(fp, tab, "// %s : api = %08X, ds = %08X\n", o->name, e_api, ds->support_flag);
				needElse = _dump_address(fp, TRUE, prefix, var, p->instance, ds, tabbed, tab, needElse);
			}
			// dump_support is always TRUE
			else needElse = _dump_using_api(fp, TRUE, prefix, var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
		}
		break;
	case ObjectType_union:
		// union b, *b; -> default = normal, possible val dump
		if (dump_support == FALSE || p->dumpMode == MemberDumpMode_value)
			needElse = _dump_address(fp, TRUE, prefix, var, p->instance, ds, tabbed, tab, needElse);
		else needElse = _dump_using_api(fp, TRUE, prefix, var, p->type, p->instance, ".", s, ds, tabbed, tab, needElse);
		break;
	case ObjectType_array: case ObjectType_index:
		// array a, *a, index b, *b -> default = api dump, possible val dump
		if (dump_support == FALSE || p->dumpMode == MemberDumpMode_value)
			needElse = _dump_address(fp, TRUE, prefix, var, p->instance, ds, tabbed, tab, needElse);
		else needElse = _dump_using_api(fp, TRUE, prefix, var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
		break;
	default:
		TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
		break;
	}
	return needElse;
}

static bool_t _cst_dump(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, 
						PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
	if (p->isPointer)
		needElse = __cst_dump(fp, tn, "", var, p, o, s, ds, tabbed, tab, needElse);		// struct *, union *, array *, index *
	else needElse = __cst_dump(fp, tn, "&", var, p, o, s, ds, tabbed, tab, needElse);	// struct, union, array, index
	*_else = needElse;
	return TRUE;
}
// CONSTRUCT
///////////////////////////////////////////////////////////////////////////////

static int _imp = 0;
///////////////////////////////////////////////////////////////////////////////
// IMPORT TYPE
static bool_t _imp_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_needElse)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_needElse;
	ExternInfo *info = (ExternInfo *)o->info;
	ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;

	if (Dz1Str_isVoid(src))
	{
		if (p->isPointer)
		{	// native *, reference *
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:		// no action : assign code will be published
				break;
			case ExternInfoStatic_primitive_ptr:	// error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// native, reference
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:		// no action : assign code will be published
			case ExternInfoStatic_primitive_ptr:	// no action : assign code will be published
				break;
			case ExternInfoStatic_typical_union: case ExternInfoStatic_construct: // copy
				TP(fp, tab); needElse = _S_memb_copy_with_api(fp, dst, src, p, s, needElse);
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
	{
		if (p->isPointer)
		{	// native *, reference *
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:
				if (StructMemberEntry_isReferenced(p) == FALSE)	
				{
					TP(fp, tab); needElse = _S_memb_clone_with_api(fp, dst, src, p, s, needElse);
					ret = TRUE;
				}
				break;
			case ExternInfoStatic_primitive_ptr:	// error
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// native, reference
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:		// no action : assign code will be published
				break;
			case ExternInfoStatic_primitive_ptr:	// clone : not referenced
				if (StructMemberEntry_isReferenced(p) == FALSE)	
				{
					TP(fp, tab); needElse = _S_memb_clone_with_api(fp, dst, src, p, s, needElse);
					ret = TRUE;
				}
				break;
			case ExternInfoStatic_typical_union: case ExternInfoStatic_construct: // copy
				TP(fp, tab); needElse = _S_memb_copy_with_api(fp, dst, src, p, s, needElse);
				ret = TRUE;
				break;
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	*_needElse = needElse;
	return ret;
}

static bool_t _imp_alloc(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_needElse)
{	// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우
	bool_t ret = FALSE;
	bool_t needElse = *_needElse;
	ExternInfo *info = (ExternInfo *)o->info;
	ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;
	if (p->isPointer)
	{	// native *, reference *
		switch(origin_type)
		{
		case ExternInfoStatic_primitive:		// no action : already be NULL by calloc
		case ExternInfoStatic_typical_union:
		case ExternInfoStatic_construct:
			break;
		case ExternInfoStatic_primitive_ptr:	// error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate alloc code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	else
	{	// native, reference
		switch(origin_type)
		{
		case ExternInfoStatic_primitive:		// no action : already be 0 by calloc
		case ExternInfoStatic_primitive_ptr:	// no action : already be NULL by calloc
		case ExternInfoStatic_typical_union:	// no action : already be cleaned by calloc
		case ExternInfoStatic_construct:
			break;
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate alloc code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	*_needElse = needElse;
	return ret;
}
static bool_t _imp_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	ExternInfo *info = (ExternInfo *)o->info;
	ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;
	if (Dz1Str_isVoid(src))
	{
		if (p->isPointer)
		{	// native *, reference *
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:		// assign
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
				break;
			case ExternInfoStatic_primitive_ptr:	// error 
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// native, reference
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:		// assign
			case ExternInfoStatic_primitive_ptr:	// assign
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
				break;
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:		// no action : copy code already published
				break;
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	else
	{
		if (p->isPointer)
		{	// native *, reference *
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:		// assign : referenced only
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:
				if (StructMemberEntry_isReferenced(p))	
				{
					TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
					ret = TRUE;
				}
				break;
			case ExternInfoStatic_primitive_ptr:	// error 
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
		else
		{	// native, reference
			switch(origin_type)
			{
			case ExternInfoStatic_primitive:		// assign
				TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
				ret = TRUE;
				break;
			case ExternInfoStatic_primitive_ptr:	// assign : reference only
				if (StructMemberEntry_isReferenced(p))	
				{
					TP(fp, tab); _S_memb_assigne_code(fp, dst, src, p->instance);
					ret = TRUE;
				}
				break;
			case ExternInfoStatic_typical_union:
			case ExternInfoStatic_construct:		// no action : copy code already published
				break;
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
				ret = TRUE;
				break;
			}
		}
	}
	return ret;
}
static bool_t _imp_init(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우
	bool_t ret = FALSE;
	ExternInfo *info = (ExternInfo *)o->info;
	ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;
	if (p->isPointer)
	{	// native *, reference *
		switch(origin_type)
		{
		case ExternInfoStatic_primitive:		// no action : already be 0 or cleaned by calloc
		case ExternInfoStatic_typical_union:
		case ExternInfoStatic_construct:
			break;
		case ExternInfoStatic_primitive_ptr:	// error 
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	else
	{	// native, reference
		switch(origin_type)
		{
		case ExternInfoStatic_primitive:		// no action : already be 0 or cleaned by calloc
		case ExternInfoStatic_primitive_ptr:	// no action : already be NULL by calloc
		case ExternInfoStatic_typical_union:
		case ExternInfoStatic_construct:		// no action : already be cleaned by calloc
			break;
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate assign code for %s\"\n", p->instance);
			ret = TRUE;
			break;
		}
	}
	return ret;
}
static bool_t _imp_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
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
			if (StructMemberEntry_isReferenced(p) == FALSE)
			{
				TP(fp, tab); _memb_del_with_api(fp, TRUE, var, p->type, p->instance, s);
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
			if (StructMemberEntry_isReferenced(p) == FALSE)	
			{
				TP(fp, tab); _memb_del_with_api(fp, TRUE, var, p->type, p->instance, s);
				ret = TRUE;
			}
			break;
		case ExternInfoStatic_typical_union:	// purge
		case ExternInfoStatic_construct:
			TP(fp, tab); _memb_purge_with_api(fp, TRUE, var, p->type, p->instance, s);
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
static bool_t _imp_dump(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, 
						PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t needElse = *_else;
	ExternInfo *info = (ExternInfo *)o->info;
	ExternInfoStatic origin_type = (ExternInfoStatic)info->isStatic;
	bool_t dump_support = (ObjectInfo_apiOf(p->type, s) & ds->support_flag) ? TRUE : FALSE;
	Dz1ThreadA_ftprintf(fp, tab, "// _imp_dump\n");
	if (p->isPointer)
	{	// native *, reference *
		Dz1ThreadA_ftprintf(fp, tab, "// _imp_dump : pointer\n");
		switch(origin_type)
		{
		case ExternInfoStatic_typical_union:	// dump using api(union)
			if (dump_support == FALSE)
			{
				Dz1ThreadA_ftprintf(fp, tab, "// _imp_dump : pointer : union : no dump api\n");
				needElse = _dump_address(fp, TRUE, "", var, p->instance, ds, tabbed, tab, needElse);
			}
			else needElse = _dump_using_api(fp, TRUE, "", var, p->type, p->instance, ".", s, ds, tabbed, tab, needElse);
			break;
		case ExternInfoStatic_primitive:
		case ExternInfoStatic_construct:		// dump using api
			if (dump_support == FALSE)
			{
				Dz1ThreadA_ftprintf(fp, tab, "// _imp_dump : pointer : prim/construct : no dump api\n");
				needElse = _dump_address(fp, TRUE, "", var, p->instance, ds, tabbed, tab, needElse);
			}
			else needElse = _dump_using_api(fp, TRUE, "", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			break;
		case ExternInfoStatic_primitive_ptr:	// error
		default:
			TP(fp, tab); fprintf(fp, "#error \"Can't generate delete code for %s\"\n", p->instance);
			break;
		}
	}
	else
	{	// native, reference
		Dz1ThreadA_ftprintf(fp, tab, "// _imp_dump : scalar\n");
		switch(origin_type)
		{
		case ExternInfoStatic_typical_union:	// dump using api(union) + "&"
			if (dump_support == FALSE)
			{
				Dz1ThreadA_ftprintf(fp, tab, "// _imp_dump : scalar : union : no dump api\n");
				needElse = _dump_address(fp, TRUE, "&", var, p->instance, ds, tabbed, tab, needElse);
			}
			else needElse = _dump_using_api(fp, TRUE, "&", var, p->type, p->instance, ".", s, ds, tabbed, tab, needElse);
			break;
		case ExternInfoStatic_primitive:
		case ExternInfoStatic_construct:		// dump using api + "&"
			if (dump_support == FALSE)
			{
				Dz1ThreadA_ftprintf(fp, tab, "// _imp_dump : scalar : prim/construct : no dump api\n");
				needElse = _dump_address(fp, TRUE, "&", var, p->instance, ds, tabbed, tab, needElse);
			}
			else needElse = _dump_using_api(fp, TRUE, "&", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
			break;
		case ExternInfoStatic_primitive_ptr:	// dump using api
			if (dump_support == FALSE)
			{
				Dz1ThreadA_ftprintf(fp, tab, "// _imp_dump : scalar : prim ptr : no dump api\n");
				needElse = _dump_address(fp, TRUE, "", var, p->instance, ds, tabbed, tab, needElse);
			}
			else needElse = _dump_using_api(fp, TRUE, "", var, p->type, p->instance, " = ", s, ds, tabbed, tab, needElse);
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

///////////////////////////////////////////////////////////////////////////////
// Member Publish Table
#define _no_code_			NULL
#define MemberPublishAPI_entry(inst_type, func_prefix) \
{ inst_type, func_prefix##_clone, func_prefix##_alloc, func_prefix##_assign, func_prefix##_init, func_prefix##_del, func_prefix##_dump }
static StructMemberPublishAPI objectPublishAPI[] =
{
	MemberPublishAPI_entry(ObjectInstanceType_primitive,	_prim),
	MemberPublishAPI_entry(ObjectInstanceType_enumerate,	_enum),
	{ ObjectInstanceType_func, _no_code_, _no_code_, _func_assign, _no_code_, _no_code_, _func_dump },
	MemberPublishAPI_entry(ObjectInstanceType_structure,	_cst),
	MemberPublishAPI_entry(ObjectInstanceType_union,		_cst),
	MemberPublishAPI_entry(ObjectInstanceType_array,		_cst),
	MemberPublishAPI_entry(ObjectInstanceType_index,		_cst),

	MemberPublishAPI_entry(ObjectInstanceType_extern,		_imp),
	MemberPublishAPI_entry(ObjectInstanceType_reference,	_imp),

	MemberPublishAPI_NULL
};
// Member Publish Table
///////////////////////////////////////////////////////////////////////////////

static bool_t _array_clone_code(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, PublishSpec *s, bool_t needElse)
{
	char buf[1024], cnt[256] = "";;
	PublishErrorSpec *error = s->error;
	str_t _ptr = Dz1Str_isVoid(src) ? "" : "->";

	if (strstr(p->arr_cnt_name, "$$") != NULL)
	{	// arrZ type
	}
	else if (Dz1StrA_isDigitStr(p->arr_cnt_name))
	{	// fixed size type
		_std_snprintfA(cnt, sizeof(cnt), "%s, ", p->arr_cnt_name);
	}
	else
	{	// count variable type
		_std_snprintfA(cnt, sizeof(cnt), "%s%s%s, ", src, _ptr, p->arr_cnt_name);
	}

	//		 	  1     I J K              2   3    4  5        6 7 8   9                   A
	fprintf(fp, "%sif (%s%s%s != NULL && (%s->%s = %s_%s_clone(%s%s%s, %serrp)) == NULL) { %s; }\n", 
				needElse ? "else " : "",		// 1
				src, _ptr, p->instance,			// I J K
				dst, p->instance,				// 2 3
				tn, p->instance,				// 4 5
				src, _ptr, p->instance, cnt,	// 6 7 8 9
				error->code(error, buf, ErrorCodeGenType_print, "*errp", NULL));	// A
	needElse = TRUE;
	return needElse;
}

static void _array_del_code(FILE *fp, str_t tn, str_t var, StructMemberEntry *p)
{	
	char cnt[256] = "";
	if (strstr(p->arr_cnt_name, "$$") != NULL)
	{	// arrZ type
	}
	else if (Dz1StrA_isDigitStr(p->arr_cnt_name))
	{	// fixed size type
		_std_snprintfA(cnt, sizeof(cnt), ", %s", p->arr_cnt_name);
	}
	else
	{	// count variable type
		_std_snprintfA(cnt, sizeof(cnt), ", %s->%s", var, p->arr_cnt_name);
	}
	//			  1  2      3   4 5
	fprintf(fp, "%s_%s_del(%s->%s%s);\n",
				tn, p->instance,		// 1 2
				var, p->instance, cnt);	// 3 4 5
}

static int _struct_primA = 0;
///////////////////////////////////////////////////////////////////////////////
// PRIMITIVE Array
static bool_t _struct_primA_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (StructMemberEntry_isReferenced(p) == FALSE)
	{
		NativeStorage storage = ObjectInfo_getPrimStorage(o);

		if (p->isPointer)
		{	// int *[], real *[], str *[], void *[]
			switch(storage)
			{
			case NativeStorage_data:		// int *[], real *[] -> reference or storage array api
			case NativeStorage_none: 		// void *			 -> reference or storage array api
				TP(fp, tab);
				needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
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
				TP(fp, tab); needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
				break;
			case NativeStorage_none:		// void		 -> error
			default:
				Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		ret = TRUE;
	}
	*_else = needElse;
	return ret;
}

// no alloc		// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우

static bool_t _struct_primA_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// no assign	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	if (StructMemberEntry_isReferenced(p))
	{
		TP(fp, tab);
		_S_memb_assigne_code(fp, dst, src, p->instance);
		ret = TRUE;
	}
	return ret;
}

// no init		// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우

static bool_t _struct_primA_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (StructMemberEntry_isReferenced(p) == FALSE)
	{
		NativeStorage storage = ObjectInfo_getPrimStorage(o);
		if (p->isPointer)
		{	// int *, real *, str *, void *
			switch(storage)
			{
			case NativeStorage_data:	// int *[], real *[]
			case NativeStorage_none:	// void *[]
				TP(fp, tab); _array_del_code(fp, tn, var, p);
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
				TP(fp, tab); _array_del_code(fp, tn, var, p);
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

// no dump
// 
// PRIMITIVE Array
///////////////////////////////////////////////////////////////////////////////

static int _struct_enumA = 0;
///////////////////////////////////////////////////////////////////////////////
// ENUMERATE Array
static bool_t _struct_enumA_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (StructMemberEntry_isReferenced(p) == FALSE)
	{
		if (p->isPointer)
		{	// enum *[]
			TP(fp, tab);
			needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
		}
		else
		{	// enum	[]
			TP(fp, tab); needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
		}
		ret = TRUE;
	}
	*_else = needElse;
	return ret;
}

// no alloc		// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우

static bool_t _struct_enumA_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// no assign	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	if (StructMemberEntry_isReferenced(p))
	{
		TP(fp, tab);
		_S_memb_assigne_code(fp, dst, src, p->instance);
		ret = TRUE;
	}
	return ret;
}

// no init		// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우

static bool_t _struct_enumA_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (StructMemberEntry_isReferenced(p) == FALSE)
	{
		TP(fp, tab); 
		if (p->isPointer)
		{
			_array_del_code(fp, tn, var, p);	// enum *[]
		}
		else _array_del_code(fp, tn, var, p);	// enum []
	}
	return TRUE;
}
// no dump
// ENUMERATE Array
///////////////////////////////////////////////////////////////////////////////

static int _struct_funcA = 0;
///////////////////////////////////////////////////////////////////////////////
// FUNCTION Array
static bool_t _struct_funcA_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (StructMemberEntry_isReferenced(p) == FALSE)
	{
		if (p->isPointer)	//	func *[] -> error
		{
			Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate clone code for %s\"\n", p->instance);
			ret = TRUE;
		}
		else
		{	//					func []
			TP(fp, tab);
			needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
		}
		ret = TRUE;
	}
	*_else = needElse;
	return ret;
}
// no alloc		// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우

static bool_t _struct_funcA_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// no assign	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	if (StructMemberEntry_isReferenced(p))
	{
		TP(fp, tab);
		_S_memb_assigne_code(fp, dst, src, p->instance);
		ret = TRUE;
	}
	return ret;
}

// no init		// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우

static bool_t _struct_funcA_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	NativeStorage storage = ObjectInfo_getPrimStorage(o);
	if (p->isPointer)	// func *[] -> error
		Dz1ThreadA_ftprintf(fp, tab, "#error \"Can't generate del code for %s\"\n", p->instance);
	else				// func []
	{
		if (StructMemberEntry_isReferenced(p) == FALSE)
		{
			TP(fp, tab);
			_array_del_code(fp, tn, var, p);
		}
	}

	return TRUE;
}
// no dump
// FUNCTION Array
///////////////////////////////////////////////////////////////////////////////

static int _struct_cstA = 0;
///////////////////////////////////////////////////////////////////////////////
// CONSTRUCT Array
static bool_t _struct_cstA_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (StructMemberEntry_isReferenced(p) == FALSE)
	{
		if (p->isPointer)
		{	// struct *[], union *[], array *[], index *[]
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:
				// struct *[], union *[]
				TP(fp, tab);
				needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
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
				TP(fp, tab); needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
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
	*_else = needElse;
	return ret;
}

// no alloc		// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우

static bool_t _struct_cstA_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// no assign	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	if (StructMemberEntry_isReferenced(p))
	{
		TP(fp, tab);
		_S_memb_assigne_code(fp, dst, src, p->instance);
		ret = TRUE;
	}
	return ret;
}

// no init		// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우
static bool_t _struct_cstA_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (StructMemberEntry_isReferenced(p) == FALSE)
	{
		NativeStorage storage = ObjectInfo_getPrimStorage(o);
		if (p->isPointer)
		{	// struct *[], union *[], array *[], index *[]
			switch(o->type)
			{
			case ObjectType_structure: case ObjectType_union:	// struct *[], union *[]
				TP(fp, tab);
				_array_del_code(fp, tn, var, p);
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
				TP(fp, tab); _array_del_code(fp, tn, var, p);
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
// no dump
// FUNCTION Array
///////////////////////////////////////////////////////////////////////////////

static int _struct_impA = 0;
///////////////////////////////////////////////////////////////////////////////
// IMPORT Array
static bool_t _struct_impA_clone(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{	// new 할때 argument 로 주어지거나, clone 할때
	bool_t ret = FALSE;
	bool_t needElse = *_else;
	if (StructMemberEntry_isReferenced(p) == FALSE)
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
				needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
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
				TP(fp, tab); needElse = _array_clone_code(fp, tn, dst, src, p, s, needElse);
				break;
			default:
				TP(fp, tab); fprintf(fp, "#error \"Can't generate clone code for %s\"\n", p->instance);
				break;
			}
		}
		ret = TRUE;
	}
	*_else = needElse;
	return ret;
}

// no alloc		// new 할때 argument 가 아닌 맴버가 예외를 유발하는 초기화를 하는 경우

static bool_t _struct_impA_assign(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{	// no assign	// new 할때 argument 로 주어지거나, clone 할때 예외 없이 대입하는 경우
	bool_t ret = FALSE;
	if (StructMemberEntry_isReferenced(p))
	{
		TP(fp, tab);
		_S_memb_assigne_code(fp, dst, src, p->instance);
		ret = TRUE;
	}
	return ret;
}

// no init		// new 할때 argument 가 아닌 맴버가 예외없는 초기화를 하는 경우
static bool_t _struct_impA_del(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	if (StructMemberEntry_isReferenced(p) == FALSE)
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
				_array_del_code(fp, tn, var, p);
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
				TP(fp, tab); _array_del_code(fp, tn, var, p);
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
// no dump
// IMPORT Array
///////////////////////////////////////////////////////////////////////////////

#define MemberPublishAPI_Aentry(inst_type, func_prefix) \
{ inst_type, func_prefix##_clone, _no_code_, func_prefix##_assign, _no_code_, func_prefix##_del, _no_code_ }
static StructMemberPublishAPI objectArrPublishAPI[] =
{
	MemberPublishAPI_Aentry(ObjectInstanceType_primitive,	_struct_primA),
	MemberPublishAPI_Aentry(ObjectInstanceType_enumerate,	_struct_enumA),
	MemberPublishAPI_Aentry(ObjectInstanceType_func,		_struct_funcA),
	MemberPublishAPI_Aentry(ObjectInstanceType_structure,	_struct_cstA),
	MemberPublishAPI_Aentry(ObjectInstanceType_union,		_struct_cstA),
	MemberPublishAPI_Aentry(ObjectInstanceType_array,		_struct_cstA),
	MemberPublishAPI_Aentry(ObjectInstanceType_index,		_struct_cstA),

	MemberPublishAPI_Aentry(ObjectInstanceType_extern,		_struct_impA),
	MemberPublishAPI_Aentry(ObjectInstanceType_reference,	_struct_impA),

	MemberPublishAPI_NULL
};

///////////////////////////////////////////////////////////////////////////////
// Member publish API 
bool_t StructMemberEntry_clone_code(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{
	bool_t ret = FALSE;
	ObjectInfo *memb = p->type;
	bool_t needElse = *_else;
	StructMemberPublishAPI *api = NULL;
	if (StructMemberEntry_isArray(p))
		api = StructMemberPublishAPI_find(objectArrPublishAPI, o->type);
	else api = StructMemberPublishAPI_find(objectPublishAPI, o->type);

	if (api == NULL)
	{
		Dz1ThreadA_ftprintf(fp, tab, "#error Unknown api for %s\n", memb->name);
		needElse = FALSE;
		ret = TRUE;
	}
	else if (api->clone_code == NULL) { }
	else ret = api->clone_code(fp, tn, dst, src, p, o, s, tab, &needElse);
	*_else = needElse;
	return ret;
}

bool_t StructMemberEntry_alloc_code(FILE *fp, str_t tn, str_t dst, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{
	bool_t ret = FALSE;
	ObjectInfo *memb = p->type;
	StructMemberPublishAPI *api = NULL;
	if (StructMemberEntry_isArray(p))
		api = StructMemberPublishAPI_find(objectArrPublishAPI, o->type);
	else api = StructMemberPublishAPI_find(objectPublishAPI, o->type);

	if (api  == NULL)
	{
		TP(fp, tab); fprintf(fp, "#error Unknown api for %s\n", memb->name);
		ret = TRUE;
	}
	else if (api->alloc_code == NULL) { }
	else ret = api->alloc_code(fp, tn, dst, p, o, s, tab, _else);
	return ret;
}

bool_t StructMemberEntry_assign_code(FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	bool_t ret = FALSE;
	ObjectInfo *memb = p->type;
	StructMemberPublishAPI *api = NULL;
	if (StructMemberEntry_isArray(p))
		api = StructMemberPublishAPI_find(objectArrPublishAPI, o->type);
	else api = StructMemberPublishAPI_find(objectPublishAPI, o->type);

	if (api  == NULL)
	{
		TP(fp, tab); fprintf(fp, "#error Unknown api for %s\n", memb->name);
		ret = TRUE;
	}
	else if (api->assign_code == NULL) { }
	else ret = api->assign_code(fp, tn, dst, src, p, o, s, tab);
	return ret;
}

void StructMemberEntry_del_code(FILE *fp, str_t tn, str_t dst, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab)
{
	ObjectInfo *memb = p->type;
	StructMemberPublishAPI *api = NULL;
	if (StructMemberEntry_isArray(p))
		api = StructMemberPublishAPI_find(objectArrPublishAPI, o->type);
	else api = StructMemberPublishAPI_find(objectPublishAPI, o->type);

	if (api  == NULL)
		Dz1ThreadA_ftprintf(fp, tab, "#error Unknown api for %s\n", memb->name);
	else if (api->del_code == NULL) { }
	else api->del_code(fp, tn, dst, p, o, s, tab);
}

bool_t StructMemberEntry_dump_code(FILE *fp, str_t tn, str_t var, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else)
{
	bool_t ret = FALSE;
	ObjectInfo *memb = p->type;
	StructMemberPublishAPI *api = NULL;
	if (StructMemberEntry_isArray(p))
		ret = _array_memb_dump_code(fp, tn, var, "->", p->instance, p->arr_cnt_name, ds, tabbed, tab, _else);
	else if ((api = StructMemberPublishAPI_find(objectPublishAPI, o->type))  == NULL)
		Dz1ThreadA_ftprintf(fp, tab, "#error Unknown api for %s\n", memb->name);
	else if (api->dump_code == NULL) { }
	else ret = api->dump_code(fp, tn, var, p, o, s, ds, tabbed, tab, _else);

	return ret;
}

bool_t StructMemberEntry_cmp_code(FILE *fp, str_t tn, str_t l, str_t r, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else)
{
	ObjectInfo *memb = p->type;
	bool_t needElse = *_else;
	bool_t type_is_ptr = ObjectInfo_isAddress(o);
	if (p->isPointer && type_is_ptr)		// double pointer -> error
		Dz1ThreadA_ftprintf(fp, tab, "#error Can't generate compare code for %s\n", memb->name);
	else if (StructMemberEntry_isArray(p))	// Array -> error
		Dz1ThreadA_ftprintf(fp, tab, "#error Can't compare inner array type %s\n", memb->name);
	else if (!p->isPointer && !type_is_ptr)	// scalar -> compare with amp
	{
		if (o->type == ObjectType_enumerate)
		{
			Dz1ThreadA_ftprintf(fp, tab, "%sif ((ret = (int)(%s->%s - %s->%s)) != 0) { }\n", needElse ? "else " : "", l, p->instance, r, p->instance);
			needElse = TRUE;
		}
		else
		{
			TP(fp, tab); needElse = _memb_cmp_with_api(fp, TRUE, l, r, "&", p->type, p->instance, s, needElse);
		}
	}
	else
	{										// single pointer -> compare
		TP(fp, tab); fprintf(fp, "%sif (%s->%s == NULL && %s->%s == NULL) ret = 0;\n", needElse ? "else " : "", l, p->instance, r, p->instance);
		TP(fp, tab); fprintf(fp, "else if (%s->%s == NULL /*&& %s->%s != NULL*/) ret = -1;\n", l, p->instance, r, p->instance);
		TP(fp, tab); fprintf(fp, "else if (/*%s->%s != NULL &&*/ %s->%s == NULL) ret = 1;\n", l, p->instance, r, p->instance);
		if (o->type == ObjectType_enumerate)
		{
			Dz1ThreadA_ftprintf(fp, tab, "%sif ((ret = (int)(*%s->%s - *%s->%s)) != 0) { }\n", needElse ? "else " : "", l, p->instance, r, p->instance);
			needElse = TRUE;
		}
		else
		{
			needElse = TRUE;
			TP(fp, tab); needElse = _memb_cmp_with_api(fp, TRUE, l, r, "", p->type, p->instance, s, needElse);
		}
	}
	*_else = needElse;
	return TRUE;
}
// Member publish API 
///////////////////////////////////////////////////////////////////////////////

