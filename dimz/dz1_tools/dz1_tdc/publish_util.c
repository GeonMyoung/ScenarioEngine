#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include "publish_util.h"

bool_t ObjectInfo_isAddress(ObjectInfo *p)
{
	bool_t ret = FALSE;
	PrimitiveInfo *p_info = NULL;
	switch(p->type)
	{
	case ObjectType_primitive:	
		ret = ((PrimitiveInfo *)p->info)->storage == NativeStorage_address ? TRUE : FALSE; 
		break;
	case ObjectType_defined:
		ret = ObjectInfo_isAddress(((DefinedInfo *)p->info)->origin);
		break;
	case ObjectType_extern: 
	case ObjectType_reference:
		ret = ((ExternInfo *)p->info)->isStatic == ExternInfoStatic_primitive_ptr ? TRUE : FALSE; break;
	// ObjectType_enumerate = not address
	// ObjectType_bits		= deprecated
	// ObjectType_structure	= not address
	// ObjectType_union		= not address
	// ObjectType_array		= not address
	// ObjectType_declare	= don't care (anyway it redirect to actual type)
	// ObjectType_func		= not address: address treat as value. so this is not address
	// ObjectType_index		= not address
	// ObjectType_constant	= don't care (this is don't have any API)
	// ObjectType_macro		= don't care (this is don't have any API)
	default:
		break;
	}
	return ret;
}

NativeStorage ObjectInfo_getPrimStorage(ObjectInfo *p)
{
	NativeStorage ret = NativeStorage_none;
	PrimitiveInfo *info = NULL;
	switch(p->type)
	{
	case ObjectType_primitive:
		info = (PrimitiveInfo *)p->info;
		ret = info->storage;
		break;
	case ObjectType_defined:
		ret = ObjectInfo_isPrimitive(((DefinedInfo *)p->info)->origin);
		break;
	default:
		break;
	}
	return ret;
}

bool_t ObjectInfo_getDumpApiSticky(ObjectInfo *p, PublishSpec *sp)
{
	bool_t ret = FALSE;
	u32_t api = ObjectInfo_apiOf(p, sp);
	switch(api & (OBJECT_API_DUMP_WIDE | OBJECT_API_DUMP_MBCS))
	{
	default:
	case 0:
	case (OBJECT_API_DUMP_WIDE | OBJECT_API_DUMP_MBCS):
		break;
	case OBJECT_API_DUMP_WIDE:
	case OBJECT_API_DUMP_MBCS:
		ret = TRUE;
		break;
	}
	return ret;
}

bool_t Type_header_delAndSetNull(FILE *fp, str_t tn, bool_t t_is_primptr, PublishSpec *s, int tab)
{
	PublishPostFix *postFix = s->postFix;
	str_t _ptr = t_is_primptr ? "" : "*";
	Dz1ThreadA_ftprintf(fp, tab,	"static __inline__ void %s%s(void *ptr)\n", tn, postFix->_delAndSetNull);
	Dz1ThreadA_ftprintf(fp, tab++,	"{\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s *%sp = (%s *%s)ptr;\n", tn, _ptr, tn, _ptr);
	Dz1ThreadA_ftprintf(fp, tab,		"if (p != NULL) { %s%s(*p); *p = NULL; }\n", tn, postFix->_del);
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Member Publish API version 2
void _memb_del_with_api(FILE *fp, bool_t parent_struct, str_t var, ObjectInfo *memb, str_t instance, PublishSpec *s)
{
	PublishPostFix *pfx = s->postFix;
	str_t e_tn = ObjectInfo_prefixOf(memb, s);
	str_t _ptr = parent_struct ? "->" : "->x.";
	//			  1 2  3 4 5       1     2          3    4     5
	fprintf(fp, "%s%s(%s%s%s);\n", e_tn, pfx->_del, var, _ptr, instance);	
}

void _memb_purge_with_api(FILE *fp, bool_t parent_struct, str_t var, ObjectInfo *memb, str_t instance, PublishSpec *s)
{
	PublishPostFix *pfx = s->postFix;
	str_t e_tn = ObjectInfo_prefixOf(memb, s);
	str_t _ptr = parent_struct ? "->" : "->x.";
	//			  1 2  3 4 5
	fprintf(fp, "%s%s(&%s%s%s);\n",
				e_tn, pfx->_purge,		// 1 2
				var, _ptr, instance);	// 3 4 5
}

bool_t _memb_cmp_with_api(FILE *fp, bool_t parent_struct, str_t l, str_t r, str_t _amp, ObjectInfo *memb, str_t instance, PublishSpec *s, bool_t _else)
{
	PublishPostFix *postFix = s->postFix;
	str_t e_tn = ObjectInfo_prefixOf(memb, s);
	str_t _l_ptr = "", _r_ptr = "";
	if (Dz1Str_isVoid(l) == FALSE) _l_ptr = parent_struct ? "->" : "->x.";
	if (Dz1Str_isVoid(r) == FALSE) _r_ptr = parent_struct ? "->" : "->x.";

	//			  1            2 3  4 5 6 7   8 9 A B
	fprintf(fp, "%sif ((ret = %s%s(%s%s%s%s, %s%s%s%s)) != 0) { }\n",
				_else ? "else " : "",		// 1
				e_tn, postFix->_cmp,		// 2 3
				_amp, l, _l_ptr, instance,	// 4 5 6 7
				_amp, r, _r_ptr, instance);	// 8 9 A B
	_else = TRUE;
	return _else;
}
// Member Publish API version 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member Dump Spec
static str_t _none = "";
static str_t _fparg = "fp, ";
static str_t _Dz1Tb = "Dz1T(";
static str_t _Dz1Te = ")";
static str_t _Dz1TL = "L";
static str_t _AW_A	= "A";
static str_t _AW_W	= "W";

void MemberDumpSpec_init(MemberDumpSpec *dst, bool_t is_file_mode, int dump_mode, PublishSpec *s)
{
	int printf_mode = dump_mode;
	PublishBasicSpec *base = s->base;
	PublishPostFix *postFix = s->postFix;

	dst->support_flag = is_file_mode ? (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP) : (OBJECT_API_DUMP | OBJECT_API_USER_DUMP);
	dst->_dump = is_file_mode ? postFix->_fdump : postFix->_dump;
	dst->_fparg = is_file_mode ? _fparg : _none;

	switch(dump_mode)
	{
	case 0:
		dst->_AW = _none;
		dst->_AW_origin = _none;
		dst->_TLb = _Dz1Tb;
		dst->_TLe = _Dz1Te;
		break;
	case 1:					// MBCS
		dst->_AW = _AW_A;
		dst->_AW_origin = _AW_A;
		dst->_TLb = _none;
		dst->_TLe = _none;
		break;
	case 2:					// WIDE
		dst->_AW = _AW_W;
		dst->_AW_origin = _AW_W;
		dst->_TLb = _Dz1TL;
		dst->_TLe = _none;
		break;
	case 3:					// sticky MBCS
		dst->_AW = _none;
		dst->_AW_origin = _AW_A;
		dst->_TLb = _none;
		dst->_TLe = _none;
		printf_mode -= 2;	// 1
		break;
	case 4:					// sticky WIDE
		dst->_AW = _none;
		dst->_AW_origin = _AW_W;
		dst->_TLb = _Dz1TL;
		dst->_TLe = _none;
		printf_mode -= 2;	// 2
		break;
	}

	if (is_file_mode)
	{
		dst->_fprintf = base->fprintf[printf_mode];
		dst->_ftprintf = base->ftprintf[printf_mode];
	}
	else
	{
		dst->_fprintf = base->printf[printf_mode];
		dst->_ftprintf = base->tprintf[printf_mode];
	}
}
// Member Dump Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Publish dump API
bool_t _dump_if_ptr_null(FILE *fp, bool_t parent_struct, str_t var, ObjectInfo *memb, str_t instance, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else)
{	
	str_t _ptr = parent_struct ? "->" : "->x.";
	if (tabbed)						// 1     2 3 4           5  6      7   8             9
		Dz1ThreadA_ftprintf(fp, tab, "%sif (%s%s%s == NULL) %s(%stab, %s\"%s = NULL\\n\"%s);\n", 
									_else ? "else " : "",				// 1
									var, _ptr, instance,				// 2 3 4
									ds->_ftprintf, ds->_fparg,	// 5 6
									ds->_TLb, instance, ds->_TLe);		// 7 8 9
	else							// 1     2 3 4           5  6 7   8             9
		Dz1ThreadA_ftprintf(fp, tab, "%sif (%s%s%s == NULL) %s(%s%s\"%s = NULL\\n\"%s);\n", 
									_else ? "else " : "",				// 1
									var, _ptr, instance,				// 2 3 4
									ds->_fprintf, ds->_fparg,		// 5 6
									ds->_TLb, instance, ds->_TLe);		// 7 8 9
	_else = TRUE;
	return _else;
}

bool_t _dump_address(FILE *fp, bool_t parent_struct, str_t prefix, str_t var, str_t instance, 
					 MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else)
{
	str_t _ptr = parent_struct ? "->" : "->x.";
	if (tabbed)						// 1 2  3      4   5            6   7 8 9 A
		Dz1ThreadA_ftprintf(fp, tab, "%s%s(%stab, %s\"%s = %%p\\n\"%s, %s%s%s%s);\n", 
									_else ? "else " : "",				// 1
									ds->_ftprintf, ds->_fparg,	// 2 3
									ds->_TLb, instance, ds->_TLe,		// 4 5 6
									prefix, var, _ptr, instance);		// 7 8 9 A
	else							// 1 2  3 4   5            6   7 8 9 A
		Dz1ThreadA_ftprintf(fp, tab, "%s%s(%s%s\"%s = %%p\\n\"%s, %s%s%s%s);\n", 
									_else ? "else " : "",				// 1
									ds->_fprintf, ds->_fparg,		// 2 3
									ds->_TLb, instance, ds->_TLe,		// 4 5 6
									prefix, var, _ptr, instance);		// 7 8 9 A
	_else = FALSE;
	return _else;
}

bool_t _dump_enum(FILE *fp, bool_t parent_struct, str_t var, ObjectInfo *memb, bool_t memb_ptr, str_t instance, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else)
{	//	XXX : spec->postFix->_toStr
	str_t _ptr = parent_struct ? "->" : "->x.";
	str_t star_letter = memb_ptr ? "*" : "";
	if (tabbed)
	{	
		if (memb_ptr)
		{	//						      1     2 3 4           5  6      7   8             9
			Dz1ThreadA_ftprintf(fp, tab,"%sif (%s%s%s == NULL) %s(%stab, %s\"%s = NULL\\n\"%s);\n",
										_else ? "else " : "",				// 1
										var, _ptr, instance,				// 2 3 4
										ds->_ftprintf, ds->_fparg,	// 5 6
										ds->_TLb, instance, ds->_TLe);		// 7 8 9
			_else = TRUE;
		}
		//								  1 2  3      4   5                 6   7 8 9  A B C D    E F G H
		Dz1ThreadA_ftprintf(fp, tab,	"%s%s(%stab, %s\"%s = %%s(%%d)\\n\"%s, %s%s%s(%s%s%s%s), %s%s%s%s);\n",
										_else ? "else " : "",				// 1
										ds->_ftprintf, ds->_fparg,	// 2 3
										ds->_TLb, instance, ds->_TLe,		// 4 5 6
										memb->name, "Str", ds->_AW,			// 7 8 9
										star_letter, var, _ptr, instance,	// A B C D
										star_letter, var, _ptr, instance);	// E F G H
	}
	else
	{	
		if (memb_ptr)
		{	//							  1     2 3 4           5  6 7   8             9
			Dz1ThreadA_ftprintf(fp, tab,"%sif (%s%s%s == NULL) %s(%s%s\"%s = NULL\\n\"%s);\n",
										_else ? "else " : "",				// 1
										var, _ptr, instance,				// 2 3 4
										ds->_fprintf, ds->_fparg,		// 5 6
										ds->_TLb, instance, ds->_TLe);		// 7 8 9
			_else = TRUE;
		}
		//								  1 2  3 4   5                 6   7 8 9  A B C D    E F G H
		Dz1ThreadA_ftprintf(fp, tab,	"%s%s(%s%s\"%s = %%s(%%d)\\n\"%s, %s%s%s(%s%s%s%s), %s%s%s%s);\n",
										_else ? "else " : "",				// 1
										ds->_fprintf, ds->_fparg,		// 2 3
										ds->_TLb, instance, ds->_TLe,		// 4 5 6
										memb->name, "Str", ds->_AW,			// 7 8 9
										star_letter, var, _ptr, instance,	// A B C D
										star_letter, var, _ptr, instance);	// E F G H
	}
	_else = FALSE;
	return _else;
}

bool_t _dump_using_api(FILE *fp, bool_t parent_struct, str_t prefix, str_t var, ObjectInfo *memb, str_t instance, str_t bridge, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else)
{
	str_t _ptr = parent_struct ? "->" : "->x.";
	bool_t _sticky = ObjectInfo_getDumpApiSticky(memb, s);
	str_t _api_AW = _sticky ? "" : ds->_AW;
	str_t e_fx = ObjectInfo_prefixOf(memb, s);
	TP(fp, tab);
	if (_else) fprintf(fp,	"else {");
	if (tabbed)
	{	//			  1  2      3   4 5   6				ftprintf(fp, tab, L"name = ");
		fprintf(fp, "%s(%stab, %s\"%s%s\"%s); ",
					ds->_ftprintf, ds->_fparg,		// 1 2 
					ds->_TLb, instance, bridge, ds->_TLe);	// 3 4 5 6
		//			  1 2 3  4 5 6 7 8
		fprintf(fp,	"%s%s%s(%s%s%s%s%s, tab); ",	//	ApiPrefixW_fdump(fp, &p->name, tab);
					e_fx, _api_AW, ds->_dump,						// 1 2 3
					ds->_fparg, prefix, var, _ptr, instance);	// 4 5 6 7 8
	}
	else
	{	//            1  2 3   4 5   6					fprintf(fp, L"name = ");
		fprintf(fp, "%s(%s%s\"%s%s\"%s); ",
					ds->_fprintf, ds->_fparg,			// 1 2
					ds->_TLb, instance, bridge, ds->_TLe);	// 3 4 5 6
		//			  1 2 3  4 5 6 7 8
		fprintf(fp, "%s%s%s(%s%s%s%s%s, tab); ",	//	ApiPrefixW_fdump(fp, &p->name, tab);
					e_fx, _api_AW, ds->_dump,						// 1 2 3
					ds->_fparg, prefix, var, _ptr, instance);	// 4 5 6 7 8
	}
	if (_else) fputs("}", fp);
	fputs("\n", fp);
	_else = FALSE;
	return _else;
}

void _dump_using_linked_api(FILE *fp, bool_t parent_struct, str_t prefix, str_t var, ObjectInfo *memb, str_t instance, str_t bridge, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else)
{
	str_t _ptr = parent_struct ? "->" : "->x.";
	str_t e_fx = ObjectInfo_prefixOf(memb, s);
	str_t e_tn = ObjectInfo_nameOf(memb);

	Dz1ThreadA_ftprintf(fp, tab++,	"%s{\t// cascade dump\n", _else ? "else " : "");
	Dz1ThreadA_ftprintf(fp, tab,		"int _cnt;\n");
	Dz1ThreadA_ftprintf(fp, tab,		"%s *i = NULL;\n", e_tn);

	TP(fp, tab); 
	if (tabbed)
		fprintf(fp,						"%s(%stab++, %s\"cascade {\\n\"%s);\n",			//	ftprintf(fp, tab++, Dz1T("cascade {\n"));
										ds->_ftprintf, ds->_fparg, ds->_TLb, ds->_TLe);
	else fprintf(fp,					"%s(%s%s\"cascade {\\n\"%s); tab++;\n",			//	fprintf(fp, Dz1T("cascade {\n")); tab++;
										ds->_fprintf, ds->_fparg, ds->_TLb, ds->_TLe);

	Dz1ThreadA_ftprintf(fp, tab,		"for (i = %s%s%s%s, _cnt = 1; i; i = i->next, _cnt++)\n", prefix, var, _ptr, instance);
	Dz1ThreadA_ftprintf(fp, tab++,		"{\n");
	//										  1  2      3   4      5   6					ftprintf(fp, tab, Dz1T("name[0] = "));
	Dz1ThreadA_ftprintf(fp, tab,			"%s(%stab, %s\"%s[%%d]%s\"%s, _cnt);\n", 
											ds->_ftprintf, ds->_fparg,	// 1 2
											ds->_TLb, instance,			// 3 4
											bridge, ds->_TLe);			// 5 6
	//										  1 2 3  4
	Dz1ThreadA_ftprintf(fp, tab,			"%s%s%s(%si, tab);\n",						//	ApiPrefixW_fdump(fp, i, tab);
											e_fx, ds->_AW, ds->_dump, ds->_fparg); // 1 2 3 4
	Dz1ThreadA_ftprintf(fp, --tab,		"}\n");
	//									  1  2        3         4
	Dz1ThreadA_ftprintf(fp, tab,		"%s(%s--tab, %s\"}\\n\"%s);\n",			//	ftprintf(fp, --tab, Dz1T("}\n"));
										ds->_ftprintf, ds->_fparg, ds->_TLb, ds->_TLe);
	Dz1ThreadA_ftprintf(fp, --tab,	"}\n");
}
// Publish dump API
///////////////////////////////////////////////////////////////////////////////

void _dump_api_declare(FILE *fp, str_t tn, str_t _AW, str_t var, bool_t file_mode, PublishSpec *s, bool_t is_header, int tab)
{
	PublishBasicSpec *base = s->base;
	PublishPostFix *postFix = s->postFix;
	str_t _fparg = file_mode ? "FILE *fp, " : "";
	str_t _api = file_mode ? postFix->_fdump : postFix->_dump;
	if (is_header)	//				   1  2       3 4 5  6 7  8
		Dz1ThreadA_ftprintf(fp, tab, "%s %s void %s%s%s(%s%s %s, int tab);\n",
									base->cpplink, base->dllport,	// 1 2
									tn, _AW, _api,					// 3 4 5
									_fparg, tn, var);				// 6 7 8
	else			//						1 2 3  4 5  6
		Dz1ThreadA_ftprintf(fp, tab, "void %s%s%s(%s%s %s, int tab)\n",
									tn, _AW, _api,		// 1 2 3
									_fparg, tn, var);	// 4 5 6
}

void _dump_api_header_publish(FILE *fp, str_t tn, u32_t t_api, str_t var, bool_t is_construct, PublishSpec *s, int tab)
{
	str_t sticky_AW = "";
	PublishPostFix *postFix = s->postFix;
	bool_t p_dump = FALSE, p_fdump = FALSE;
	// Declare Dump(O) & FDump(O)
	if (t_api & (OBJECT_API_DUMP  | OBJECT_API_USER_DUMP))  p_dump = TRUE;
	if (t_api & (OBJECT_API_FDUMP | OBJECT_API_USER_FDUMP)) p_fdump = TRUE;

	if (p_dump || p_fdump)
	{
		u8_t type = (t_api & (OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE));
		switch(type)
		{
		case 0:	// none
			if (p_dump)  _dump_api_declare(fp, tn, "", var, FALSE, s, TRUE, tab);
			if (p_fdump) _dump_api_declare(fp, tn, "", var, TRUE, s, TRUE, tab);
			break;
		case 1:	// OBJECT_API_DUMP_MBCS
			sticky_AW = is_construct ? "" : "A";	// A is already attached to "tn" if type is construct
			if (p_dump)  _dump_api_declare(fp, tn, sticky_AW, var, FALSE, s, TRUE, tab);	
			if (p_fdump) _dump_api_declare(fp, tn, sticky_AW, var, TRUE, s, TRUE, tab);
			break;
		case 2:	// OBJECT_API_DUMP_WIDE
			sticky_AW = is_construct ? "" : "W";	// W is already attached to "tn" if type is construct
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) 
				fprintf(fp,								  "#ifndef UNIX_SYSTEM // dump mode 2\n");
			if (p_dump)  _dump_api_declare(fp, tn, sticky_AW, var, FALSE, s, TRUE, tab);
			if (p_fdump) _dump_api_declare(fp, tn, sticky_AW, var, TRUE, s, TRUE, tab);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) 
				fprintf(fp,								  "#endif // UNIX_SYSTEM\n");
			break;
		case 3:	// OBJECT_API_DUMP_MBCS | OBJECT_API_DUMP_WIDE
			if (p_dump)  _dump_api_declare(fp, tn, "A", var, FALSE, s, TRUE, tab);
			if (p_fdump) _dump_api_declare(fp, tn, "A", var, TRUE, s, TRUE, tab);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0) 
				fprintf(fp,								  "#ifndef UNIX_SYSTEM // dump mode 3\n");
			if (p_dump)  _dump_api_declare(fp, tn, "W", var, FALSE, s, TRUE, tab);
			if (p_fdump) _dump_api_declare(fp, tn, "W", var, TRUE, s, TRUE, tab);
			fprintf(fp,									  "#ifdef UNICODE\n");
			if (p_dump)  Dz1ThreadA_ftprintf(fp, tab,	  "#define %s%s %sW%s\n", tn, postFix->_dump, tn, postFix->_dump);
			if (p_fdump) Dz1ThreadA_ftprintf(fp, tab,	  "#define %s%s %sW%s\n", tn, postFix->_fdump, tn, postFix->_fdump);
			fprintf(fp,									  "#else //  UNICODE\n");
			if (p_dump)  Dz1ThreadA_ftprintf(fp, tab,	  "#define %s%s %sA%s\n", tn, postFix->_dump, tn, postFix->_dump);
			if (p_fdump) Dz1ThreadA_ftprintf(fp, tab,	  "#define %s%s %sA%s\n", tn, postFix->_fdump, tn, postFix->_fdump);
			fprintf(fp,									  "#endif //  UNICODE\n");
			if (p_dump)  Dz1ThreadA_ftprintf(fp, tab,	  "static __inline__ void %sX%s(%s *p, int tab) { DZ1_DUMP(%s, p, tab); }\n", tn, postFix->_dump, tn, tn);
			if (p_fdump) Dz1ThreadA_ftprintf(fp, tab,	  "static __inline__ void %sX%s(FILE *fp, %s *p, int tab) { DZ1_FDUMP(fp, %s, p, tab); }\n", tn, postFix->_fdump, tn, tn);
			if ((t_api & OBJECT_API_WINDOWS_ONLY) == 0)
			{
				fprintf(fp,								  "#else // UNIX_SYSTEM\n");
				if (p_dump)  Dz1ThreadA_ftprintf(fp, tab, "#define %s%s %sA%s\n", tn, postFix->_dump, tn, postFix->_dump);
				if (p_dump)  Dz1ThreadA_ftprintf(fp, tab, "#define %sX%s %sA%s\n", tn, postFix->_dump, tn, postFix->_dump);
				if (p_fdump) Dz1ThreadA_ftprintf(fp, tab, "#define %s%s %sA%s\n", tn, postFix->_fdump, tn, postFix->_fdump);
				if (p_fdump) Dz1ThreadA_ftprintf(fp, tab, "#define %sX%s %sA%s\n", tn, postFix->_fdump, tn, postFix->_fdump);
				fprintf(fp,								  "#endif // UNIX_SYSTEM\n");
			}
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Member print spec
bool_t MemberEntryNames_get(MemberEntryNames *dst, int FORWARD_TYPE, ObjectInfo *type, bool_t _is_ptr, u32_t memb_flag, bool_t isHeader)
{
	char *cp = NULL;
	bool_t postfix = FALSE;
	cp = dst->name_postfix;

	// dst->name_postfix
	if (isHeader == FALSE) { *cp++ = '/'; *cp++ = '*'; } // source 의 경우
	if (MemberFlag_isArray(memb_flag))
	{	// inner array 인 경우
		if (MemberFlag_isReferenced(memb_flag)) { strcpy(cp, "_ref"); cp += 4; postfix = TRUE; }				// array not deleted(pointer assign)
		else if (_is_ptr || ObjectInfo_isAddress(type))
		{	// pointer 가 붙어있거나 address 유형이고
			if (MemberFlag_isArrayElemRef(memb_flag))	{ strcpy(cp, "_e_ref"); cp += 6; postfix = TRUE; }		// element not deleted(element pointer assign)
			else										{ strcpy(cp, "_e_clone"); cp += 8; postfix = TRUE; }	// element will be deleted(element pointer clone)
		}
		else											{ strcpy(cp, "_e_copy"); cp += 7; postfix = TRUE; }		// element will be purged(element context copy)
	}
	else if (_is_ptr || ObjectInfo_isAddress(type))
	{	// pointer 가 붙어있거나 address 유형이고
		if (MemberFlag_isReferenced(memb_flag))			 { strcpy(cp, "_ref"); cp += 4; postfix = TRUE; }		// pointer not deleted(pointer assign)
	}

	if (isHeader == FALSE) { *cp++ = '*'; *cp++ = '/'; }
	*cp = 0;
	if (postfix == FALSE) dst->name_postfix[0] = 0;

	// dst->type
	_std_snprintfA(dst->type, sizeof(dst->type), "%s%s",
				isHeader ? forwardCaster(FORWARD_TYPE) : "",	// header 의 경우, "struct " | "enum " | "" : prefix 추가
				ObjectInfo_nameOf(type));						// "typename"

	// dst->ptrs_memb
	cp = dst->ptrs_memb;
	if (_is_ptr || MemberFlag_isArray(memb_flag))
	{
		if (_is_ptr) *cp++ = '*';						// pointer 면 '*' 추가
		if (MemberFlag_isArray(memb_flag)) *cp++ = '*';	// inner array 면 '*' 추가
	}
	*cp = 0;

	// dst->ptrs_args
	cp = dst->ptrs_args;
	if (_is_ptr || MemberFlag_isArray(memb_flag))
	{
		if (_is_ptr ) *cp++ = '*';						// pointer 면 '*' 추가
		if (MemberFlag_isArray(memb_flag)) *cp++ = '*';	// inner array 면 '*' 추가
	}
	else if (ObjectInfo_isAddress(type)) { /* type 자체가 Address 인 경우 안붙임 */ }
	else
	{	// pointer 설정도 없고, type 자체가 Address 유형도 아님
		ExternInfo *ext_info = NULL;
		ObjectInfo *o = ObjectInfo_getOrigin(type);
		switch((ObjectInstanceType)o->type)
		{
		default:
		case ObjectInstanceType_primitive:
		case ObjectInstanceType_enumerate:
		case ObjectInstanceType_func:
			break;
		case ObjectInstanceType_structure:			//
		case ObjectInstanceType_union:				// argument must be pointer
			*cp++ = '*';
			break;
		case ObjectInstanceType_array:				//
		case ObjectInstanceType_index:				// don't care
			break;
		case ObjectInstanceType_extern:
		case ObjectInstanceType_reference:
			ext_info = (ExternInfo *)o->info;
			switch(ext_info->isStatic)
			{
			case ExternInfoStatic_typical_union:	//
			case ExternInfoStatic_construct:		// argument must be pointer
				*cp++ = '*';
				break;
			default:
			case ExternInfoStatic_primitive:		//
			case ExternInfoStatic_primitive_ptr:	// don't care
				break;
			}
			break;
		}
	}
	*cp = 0;
	return TRUE;
}
// Member print spec
///////////////////////////////////////////////////////////////////////////////

