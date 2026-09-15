#include <dz1_thread_stdio.h>
#include "dz1_tjsonc_parser.h"
#include "dz1_tjsonc_publish.h"

static bool_t json_chk_primitive_isScalar(ObjectInfo *ori)
{
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;
	switch(info->storage)
	{
	case NativeStorage_data:
	case NativeStorage_none:
		return TRUE;
	default:
	case NativeStorage_address:
		return FALSE;
	}
}

static Dz1Str json_resolve_name(ObjectInfo *src, bool_t *ret_is_scalar, Dz1Error *err)
{
	Dz1Str name = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ObjectInfo *ori = ObjectInfo_getOrigin(src);
		name = src->name;
		switch(ori->type)
		{
		case ObjectType_primitive:
			if (ret_is_scalar != NULL) *ret_is_scalar = json_chk_primitive_isScalar(ori);
			name = ((PrimitiveInfo *)ori->info)->native;
			break;
		case ObjectType_enumerate:
			if (ret_is_scalar != NULL) *ret_is_scalar = TRUE;
			break;
		case ObjectType_structure:
		case ObjectType_union:
		case ObjectType_array:
		case ObjectType_index:
			if (ret_is_scalar != NULL) *ret_is_scalar = TRUE;
			break;
		case ObjectType_extern:
		case ObjectType_reference:
			if (ret_is_scalar != NULL) *ret_is_scalar = ObjectInfo_isPrimitive(ori) ? ObjectInfo_isScalar(ori) : TRUE;
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return name;
}

#define CRLF		Dz1Text("\n")
typedef struct ReplaceEntry
{
	Dz1Str				 find_target;
	Dz1Str				 replace_str;
} ReplaceEntry;

static Dz1Str _replated_write_preproc(Dz1Str src, ReplaceEntry rpls[], Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str sp = Dz1Str_dup(src, errp);
	if (sp == NULL) ERR_OUT(errp);
	else
	{
		Dz1Str np = NULL;
		ReplaceEntry *i;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&sp);
		for (i = rpls; errp->code == 0 && i->find_target != NULL; i++)
		{
			if ((np = Dz1Str_replace(sp, i->find_target, i->replace_str, errp)) == NULL) { }
			else
			{
				Dz1Str_delAndSetNull(&sp);
				sp = np; np = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Str_delAndSetNull, (void *)&sp);
	}
	return sp;
}

static bool_t _replated_write_line(FILE *dst, Dz1Str src, ReplaceEntry rpls[], Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str str = _replated_write_preproc(src, rpls, errp);
	if (str == NULL) ERR_OUT(errp);
	else 
	{
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&str);
		fwrite(str, sizeof(TCHAR), Dz1STRLEN(str), dst);
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&str);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _replated_write(FILE *dst, Dz1Str lines[], ReplaceEntry rpls[], Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str *i;
	for (i = lines; errp->code == 0 && *i != NULL; i++)
	{
		if (_replated_write_line(dst, *i, rpls, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _publish_enum_type_src(FILE *dst, Dz1Str type_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str src_lines[] = {
		Dz1Text("static bool_t $enum_type$_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)") CRLF,
		Dz1Text("{") CRLF,
		Dz1Text("	DZ1_ERROR_SAFE_PTR(errp, err);") CRLF,
		Dz1Text("	$enum_type$ v = $enum_type$_max;") CRLF,
		Dz1Text("	switch(tok->t)") CRLF,
		Dz1Text("	{") CRLF,
		Dz1Text("	case Dz1JsonTokenType_number:") CRLF,
		Dz1Text("		v = ($enum_type$)Dz1StrTo32(tok->v);") CRLF,
		Dz1Text("		break;") CRLF,
		Dz1Text("	case Dz1JsonTokenType_string:") CRLF,
		Dz1Text("		if ((v = $enum_type$FromStr(tok->v)) == $enum_type$_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);") CRLF,
		Dz1Text("		break;") CRLF,
		Dz1Text("	default: ERR_SET_RET(errp, EPERM, FALSE);") CRLF,
		Dz1Text("	}") CRLF,
		CRLF,
		Dz1Text("	if ((dst_obj->data = $enum_type$_new(&v, errp)) == NULL) ERR_OUT(errp);") CRLF,
		Dz1Text("	else Dz1Error_set(errp, 0);") CRLF,
		CRLF,
		Dz1Text("	return errp->code == 0 ? TRUE : FALSE;") CRLF,
		Dz1Text("}") CRLF,
		CRLF,
		Dz1Text("static bool_t $enum_type$_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)") CRLF,
		Dz1Text("{") CRLF,
		Dz1Text("	DZ1_ERROR_SAFE_PTR(errp, err);") CRLF,
		Dz1Text("	if (obj == NULL)") CRLF,
		Dz1Text("	{") CRLF,
		Dz1Text("		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);") CRLF,
		Dz1Text("		else Dz1Error_set(errp, 0);") CRLF,
		Dz1Text("	}") CRLF,
		Dz1Text("	else") CRLF,
		Dz1Text("	{") CRLF,
		Dz1Text("		$enum_type$ v = *($enum_type$ *)obj;") CRLF,
		Dz1Text("		Dz1Str str_v = $enum_type$Str(v);") CRLF,
		Dz1Text("		if (str_v == NULL)") CRLF,
		Dz1Text("		{") CRLF,
		Dz1Text("			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);") CRLF,
		Dz1Text("			else Dz1Error_set(errp, 0);") CRLF,
		Dz1Text("		}") CRLF,
		Dz1Text("		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);") CRLF,
		Dz1Text("		else Dz1Error_set(errp, 0);") CRLF,
		Dz1Text("	}") CRLF,
		Dz1Text("	return errp->code == 0 ? TRUE : FALSE;") CRLF,
		Dz1Text("}") CRLF,
		NULL
	};
	ReplaceEntry rpl_ent[] = {
		{ Dz1Text("$enum_type$"), type_name },
		{ NULL, NULL }
	};

	if (_replated_write(dst, src_lines, rpl_ent, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

/*
	case 0: p->a = *(u8_t *)info->data; break;
	case 1: p->b = *(u16_t *)info->data; break;
	case 2: p->c = *(u32_t *)info->data; break;
	case 3: p->d = *(u64_t *)info->data; break;
	case 4: p->e = (Dz1Str)info->data; info->data = NULL; break;
*/
typedef bool_t (*struct_memb_writer_f)(FILE *dst, int idx, bool_t type_scalar, Dz1Str type, bool_t ptr_instance, Dz1Str instance, Dz1Error *errp);
static bool_t _structure_member_set_write(FILE *dst, int idx, bool_t type_scalar, Dz1Str type, bool_t ptr_instance, Dz1Str instance, Dz1Error *errp)
{
	Dz1Str astr = Dz1Text(" *"), nullifier = Dz1Text("info->data = NULL; ");
	TCHAR clean_str[1024] = Dz1Text("");
	Dz1Str value_astr = Dz1Text("");
	Dz1Str cast_astr = Dz1Text("");
	Dz1Str set_null = Dz1Text("");
	if (type_scalar)
	{	// value type
		cast_astr = astr;
		if (ptr_instance)
		{
			Dz1SNPRINTF(clean_str, 1024, Dz1T("%s_delAndSetNull(&p->%s); "), type, instance);
			set_null = nullifier;	// p->a = (type *)info->data; info->data = NULL;
		}
		else value_astr = astr;					// p->a = *(type *)info->data
	}
	else
	{	// ptr_type
		if (ptr_instance) 
		{
			Dz1Thread_printf("!!! Object = %s %s, type_scalar = %d, ptr_instance = %d\n", type, instance, type_scalar, ptr_instance);
			ERR_SET_OUT(errp, EPERM);		// Dz1Str *a; -> don't
		}
		else
		{
			Dz1SNPRINTF(clean_str, 1024, Dz1T("%s_delAndSetNull(&p->%s); "), type, instance);
			set_null = nullifier;						// Dz1Str  a; -> p->a = (Dz1Str)info->data; info->data = NULL;
		}
	}

	if (errp->code == 0)
		fprintf(dst, "	case %d: %sp->%s = %s(%s%s)info->data; %sbreak; // type_scalar = %d, ptr_instance = %d" CRLF, idx, clean_str, instance, value_astr, type, cast_astr, set_null, type_scalar, ptr_instance);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
	case 0: return &p->a;
	case 1: return &p->b;
	case 2: return &p->c;
	case 3: return &p->d;
	case 4: return p->e;
	default: return NULL;
*/
static bool_t _structure_member_get_write(FILE *dst, int idx, bool_t type_scalar, Dz1Str type, bool_t ptr_instance, Dz1Str instance, Dz1Error *errp)
{
	Dz1Str amp = Dz1Text("&");
	Dz1Str addr_amp = Dz1Text("");

	if (type_scalar)
	{
		if (ptr_instance) { }	// u32_t *a -> return p->a;
		else addr_amp = amp;	// u32_t  a -> return &p->a;
	}
	else
	{	// ptr_type
		if (ptr_instance) ERR_SET_OUT(errp, EPERM);		// Dz1Str *a; -> don't
		else { }										// Dz1Str  a; -> return p->a;
	}

	if (errp->code == 0)
		fprintf(dst, "	case %d: return %sp->%s;" CRLF, idx, addr_amp, instance);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
	{ Dz1Text("a"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("b"), Dz1Text("u16_t"), 1 },
	{ Dz1Text("c"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("d"), Dz1Text("u64_t"), 3 },
	{ Dz1Text("e"), Dz1Text("Dz1Str"), 4 },
*/
static bool_t _structure_member_spec_write(FILE *dst, int idx, bool_t type_scalar, Dz1Str type, bool_t ptr_instance, Dz1Str instance, Dz1Error *errp)
{
	fprintf(dst, Dz1Text("	{ Dz1Text(\"%s\"), Dz1Text(\"%s\"), %d },") CRLF, instance, type, idx);
	return TRUE;
}

static bool_t _struct_child_loop(FILE *dst, StructMemberEntry **arr, u32_t cnt, struct_memb_writer_f wr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t i;
	StructMemberEntry *node = NULL;
	ObjectInfo *m_obj = NULL, *m_ori = NULL;
	bool_t scalar_type = FALSE;
	Dz1Str name = NULL;
	for (i = 0; i < cnt; i++)
	{
		node = arr[i];
		m_obj = node->type;
		if (StructMemberEntry_isArray(node))
		{
			fprintf(dst, Dz1Text("#error Array type member not support yet\n"));
		}
		else if ((name = json_resolve_name(m_obj, &scalar_type, errp)) == NULL) ERR_OUT(errp);
		else if (wr(dst, i, scalar_type, name, node->isPointer, node->instance, errp) == FALSE)
		{
			ERR_OUT(errp);
		}
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _publish_struct_type_src(FILE *dst, Dz1Str type_name, StructMemberList *list, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str src_lines0[] = {
		Dz1Text("static bool_t $type_name$_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)") CRLF,
		Dz1Text("{") CRLF,
		Dz1Text("	DZ1_ERROR_SAFE_PTR(errp, err);") CRLF,
		Dz1Text("	$type_name$ *p = ($type_name$ *)ptr;") CRLF,
		CRLF,
		Dz1Text("	Dz1JsonSpecChild *id = info->id;") CRLF,
		Dz1Text("	switch(id->index)") CRLF,
		Dz1Text("	{") CRLF,
		NULL
	};
	Dz1Str src_lines1[] = {
		Dz1Text("	default: ERR_SET_OUT(errp, ENOENT); break;") CRLF,
		Dz1Text("	}") CRLF,
		Dz1Text("	return errp->code == 0 ? TRUE : FALSE;") CRLF,
		Dz1Text("}") CRLF,
		CRLF,
		Dz1Text("static void *$type_name$_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)") CRLF,
		Dz1Text("{") CRLF,
		Dz1Text("	$type_name$ *p = ($type_name$ *)ptr;") CRLF,
		Dz1Text("	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;") CRLF,
		Dz1Text("	switch(id->index)") CRLF,
		Dz1Text("	{") CRLF,
		NULL
	};
	Dz1Str src_lines2[] ={
		Dz1Text("	default: return NULL;") CRLF,
		Dz1Text("	}") CRLF,
		Dz1Text("}") CRLF,
		CRLF,
		Dz1Text("static Dz1JsonSpecChild $type_name$_membs[] =") CRLF,
		Dz1Text("{") CRLF,
		NULL
	};
	Dz1Str src_lines3[] = {
		Dz1Text("	{ NULL, NULL, -1 }") CRLF,
		Dz1Text("};") CRLF,
		NULL
	};
	ReplaceEntry rpl_ent[] = {
		{ Dz1Text("$type_name$"), type_name },
		{ NULL, NULL }
	};
	u32_t cnt = 0;
	StructMemberEntry **arr = list->get_array(list, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		if (0) { }
		else if (_replated_write(dst, src_lines0, rpl_ent, errp) == FALSE) ERR_OUT(errp);

		else if (_struct_child_loop(dst, arr, cnt, _structure_member_set_write, errp) == FALSE) ERR_OUT(errp);

		else if (_replated_write(dst, src_lines1, rpl_ent, errp) == FALSE) ERR_OUT(errp);

		else if (_struct_child_loop(dst, arr, cnt, _structure_member_get_write, errp) == FALSE) ERR_OUT(errp);

		else if (_replated_write(dst, src_lines2, rpl_ent, errp) == FALSE) ERR_OUT(errp);

		else if (_struct_child_loop(dst, arr, cnt, _structure_member_spec_write, errp) == FALSE) ERR_OUT(errp);

		else if (_replated_write(dst, src_lines3, rpl_ent, errp) == FALSE) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// >>>set_child
//	case $type_name$Present_%s: p->x.a = *(u8_t *)info->data; break;
// 	case 1: p->x.b = *(u16_t *)info->data; break;
// 	case 2: p->x.c = *(u32_t *)info->data; break;
// 	case 3: p->x.d = *(u64_t *)info->data; break;
// 	case 4: p->x.e = (Dz1Str)info->data; info->data = NULL; break;
static bool_t _union_member_set_write(FILE *dst, Dz1Str parent_type, bool_t type_scalar, Dz1Str type, bool_t ptr_instance, Dz1Str instance, Dz1Error *errp)
{
	Dz1Str astr = Dz1Text(" *"), nullifier = Dz1Text("info->data = NULL; ");
	TCHAR clean_str[1024] = Dz1Text("");
	Dz1Str value_astr = Dz1Text("");
	Dz1Str cast_astr = Dz1Text("");
	Dz1Str set_null = Dz1Text("");
	if (type_scalar)
	{	// pointer type
		cast_astr = astr;
		if (ptr_instance) 
		{
			Dz1SNPRINTF(clean_str, 1024, Dz1T("%s_delAndSetNull(&p->x.%s); "), type, instance);
			set_null = nullifier;	// p->a = (type *)info->data; info->data = NULL;
		}
		else value_astr = astr;					// p->a = *(type *)info->data
	}
	else
	{	// ptr_type
		if (ptr_instance) 
		{
			Dz1Thread_printf("!!! object = %s %s\n", type, instance);
			ERR_SET_OUT(errp, EPERM);		// Dz1Str *a; -> don't
		}
		else 
		{
			Dz1SNPRINTF(clean_str, 1024, Dz1T("%s_delAndSetNull(&p->x.%s); "), type, instance);
			set_null = nullifier;						// Dz1Str  a; -> p->a = (Dz1Str)info->data; info->data = NULL;
		}
	}

	if (errp->code == 0)
		fprintf(dst, "	case %sPresent_%s: %sp->x.%s =%s(%s%s)info->data; %sbreak;" CRLF, 
						parent_type, instance, clean_str, instance, value_astr, type, cast_astr, set_null);
	return errp->code == 0 ? TRUE : FALSE;
}


// >>>get_child
//		case $type_name$Present_%s: return &p->x.a;
// 		case MyUnionPresent_b: return &p->x.b;
// 		case MyUnionPresent_c: return &p->x.c;
// 		case MyUnionPresent_d: return &p->x.d;
// 		case MyUnionPresent_e: return p->x.e;
static bool_t _union_member_get_write(FILE *dst, Dz1Str p_type, bool_t type_scalar, Dz1Str type, bool_t ptr_instance, Dz1Str instance, Dz1Error *errp)
{
	Dz1Str amp = Dz1Text("&");
	Dz1Str addr_amp = Dz1Text("");

	if (type_scalar)
	{
		if (ptr_instance) { }	// u32_t *a -> return p->a;
		else addr_amp = amp;	// u32_t  a -> return &p->a;
	}
	else
	{	// ptr_type
		if (ptr_instance) ERR_SET_OUT(errp, EPERM);		// Dz1Str *a; -> don't
		else { }										// Dz1Str  a; -> return p->a;
	}

	if (errp->code == 0)
		fprintf(dst, "		case %sPresent_%s: return %sp->x.%s;" CRLF, p_type, instance, addr_amp, instance);
	return errp->code == 0 ? TRUE : FALSE;
}

// >>>memb
// 	{ Dz1Text("a"), Dz1Text("u8_t"), MyUnionPresent_a },
// 	{ Dz1Text("b"), Dz1Text("u16_t"), MyUnionPresent_b },
// 	{ Dz1Text("c"), Dz1Text("u32_t"), MyUnionPresent_c },
// 	{ Dz1Text("d"), Dz1Text("u64_t"), MyUnionPresent_d },
// 	{ Dz1Text("e"), Dz1Text("Dz1Str"), MyUnionPresent_e },
static bool_t _union_member_spec_write(FILE *dst, Dz1Str p_type, bool_t type_scalar, Dz1Str type, bool_t ptr_instance, Dz1Str instance, Dz1Error *errp)
{
	fprintf(dst, Dz1Text("	{ Dz1Text(\"%s\"), Dz1Text(\"%s\"), %sPresent_%s },") CRLF, instance, type, p_type, instance);
	return TRUE;
}

typedef bool_t (*union_memb_writer_f)(FILE *dst, str_t p_type, bool_t type_scalar, Dz1Str type, bool_t ptr_instance, Dz1Str instance, Dz1Error *errp);
static bool_t _union_child_loop(FILE *dst, str_t p_type, UnionMemberEntry **arr, u32_t cnt, union_memb_writer_f wr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t i;
	UnionMemberEntry *node = NULL;
	ObjectInfo *m_obj = NULL, *m_ori = NULL;
	bool_t scalar_type = FALSE;
	Dz1Str name = NULL;
	for (i = 0; i < cnt; i++)
	{
		node = arr[i];
		m_obj = node->type;
		if ((name = json_resolve_name(m_obj, &scalar_type, errp)) == NULL) ERR_OUT(errp);
		else if (wr(dst, p_type, scalar_type, name, node->isPointer, node->instance, errp) == FALSE)
		{
			Dz1Thread_printf("!!! belongs to %s\n", p_type);
			ERR_OUT(errp);
		}
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _publish_union_type_src(FILE *dst, Dz1Str type_name, UnionMemberList *list, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str src_lines0[] = {
		Dz1Text("static bool_t $type_name$_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)") CRLF,
		Dz1Text("{") CRLF,
		Dz1Text("	DZ1_ERROR_SAFE_PTR(errp, err);") CRLF,
		Dz1Text("	$type_name$ *p = ($type_name$ *)ptr;") CRLF,
		CRLF,
		Dz1Text("	Dz1JsonSpecChild *id = info->id;") CRLF,
		Dz1Text("	switch(id->index)") CRLF,
		Dz1Text("	{") CRLF,
		NULL
	};
	Dz1Str src_lines1[] = {
		Dz1Text("	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);") CRLF,
		Dz1Text("	}") CRLF,
		Dz1Text("	p->present = ($type_name$Present)id->index;") CRLF,
		Dz1Text("	return errp->code == 0 ? TRUE : FALSE;") CRLF,
		Dz1Text("}") CRLF,
		CRLF,
		Dz1Text("static void *$type_name$_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)") CRLF,
		Dz1Text("{") CRLF,
//		Dz1Text("	void *ret = NULL;") CRLF,
		Dz1Text("	$type_name$ *p = ($type_name$ *)ptr;") CRLF,
		Dz1Text("	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);") CRLF,
		Dz1Text("	if (id != NULL)") CRLF,
		Dz1Text("	{") CRLF,
		Dz1Text("		switch(p->present)") CRLF,
		Dz1Text("		{") CRLF,
		NULL
	};
	Dz1Str src_lines2[] = {
		Dz1Text("		default: return NULL;") CRLF,
		Dz1Text("		}") CRLF,
		Dz1Text("	}") CRLF,
		Dz1Text("	else return NULL;") CRLF,
		Dz1Text("}") CRLF,
		CRLF,
		Dz1Text("static Dz1JsonSpecChild $type_name$_membs[] =") CRLF,
		Dz1Text("{") CRLF,
		NULL
	};
	Dz1Str src_lines3[] = {
		Dz1Text("	{ NULL, NULL, -1 }") CRLF,
		Dz1Text("};") CRLF,
		NULL
	};
	ReplaceEntry rpl_ent[] = {
		{ Dz1Text("$type_name$"), type_name },
		{ NULL, NULL }
	};
	u32_t cnt = 0;
	UnionMemberEntry **arr = list->get_array(list, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		if (0) { }
		else if (_replated_write(dst, src_lines0, rpl_ent, errp) == FALSE) ERR_OUT(errp);
		else if (_union_child_loop(dst, type_name, arr, cnt, _union_member_set_write, errp) == FALSE) ERR_OUT(errp);
		else if (_replated_write(dst, src_lines1, rpl_ent, errp) == FALSE) ERR_OUT(errp);
		else if (_union_child_loop(dst, type_name, arr, cnt, _union_member_get_write, errp) == FALSE) ERR_OUT(errp);
		else if (_replated_write(dst, src_lines2, rpl_ent, errp) == FALSE) ERR_OUT(errp);
		else if (_union_child_loop(dst, type_name, arr, cnt, _union_member_spec_write, errp) == FALSE) ERR_OUT(errp);
		else if (_replated_write(dst, src_lines3, rpl_ent, errp) == FALSE) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static str_t _resolve_obj_type_name(ObjectInfo *obj)
{
	str_t ret = NULL;
	ObjectInfo *ori = ObjectInfo_getOrigin(obj);
	switch(ori->type)
	{
	case ObjectType_primitive:
		ret = ((PrimitiveInfo *)ori->info)->native;
		break;
	case ObjectType_enumerate:
	case ObjectType_structure:
	case ObjectType_union:
	case ObjectType_array:
	case ObjectType_index:
	case ObjectType_extern:
	case ObjectType_reference:
	default:
		ret = obj->name;
		break;
	}
	return ret;
}

static bool_t _publish_array_type_src(FILE *dst, Dz1Str array_type_name, ObjectInfo *node_obj, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str src_lines[] = {
		Dz1Text("static bool_t $list_type$_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)") CRLF,
		Dz1Text("{") CRLF,
		Dz1Text("	DZ1_ERROR_SAFE_PTR(errp, err);") CRLF,
		Dz1Text("	$list_type$ *dst = ($list_type$ *)dst_ptr;") CRLF,
		Dz1Text("	$member_type$$member_rcv_ptr$node = NULL;") CRLF,
		Dz1Text("	if (dst == NULL || var == NULL || (node = ($member_type$$member_rcv_ptr$)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);") CRLF,
		Dz1Text("	else if ((*errp = dst->add(dst, $member_add_ptr$node)).code) ERR_OUT(errp);") CRLF,
		Dz1Text("	else") CRLF,
		Dz1Text("	{") CRLF,
		Dz1Text("		$member_comment$var->data = NULL;") CRLF,
		Dz1Text("		Dz1Error_set(errp, 0);") CRLF,
		Dz1Text("	}") CRLF,
		Dz1Text("	return errp->code == 0 ? TRUE : FALSE;") CRLF,
		Dz1Text("}") CRLF,
		CRLF,
		Dz1Text("static u32_t $list_type$_cnt(void *ptr)") CRLF,
		Dz1Text("{") CRLF,
		Dz1Text("	u32_t ret = 0;") CRLF,
		Dz1Text("	$list_type$ *list = ($list_type$ *)ptr;") CRLF,
		Dz1Text("	if (list != NULL) ret = list->count(list);") CRLF,
		Dz1Text("	return ret;") CRLF,
		Dz1Text("}") CRLF,
		CRLF,		
		Dz1Text("static Dz1Error $list_type$_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)") CRLF,
		Dz1Text("{") CRLF,
		Dz1Text("	DZ1_ERROR_SAFE_VAR(errp, err);") CRLF,
		Dz1Text("	$list_type$ *list = ($list_type$ *)obj;") CRLF,
		Dz1Text("	if (list == NULL) ERR_SET_OUT(errp, EINVAL);") CRLF,
		Dz1Text("	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);") CRLF,
		Dz1Text("	else Dz1Error_set(errp, 0);") CRLF,
		Dz1Text("	return err;") CRLF,
		Dz1Text("}") CRLF,
		NULL
	};
	str_t type_name = _resolve_obj_type_name(node_obj);
	// u32_t *node = NULL;			// isScalar = TRUE
	// Dz1Str node = NULL;			// isScalar = FALSE
	// SomeStruct *node = NULL;		// isScalar = TRUE;
	// --------------------------------------------------
	// node = (u32_t *)var->data;		// u32_t element : isScalar = TRUE;		isPrimitive = TRUE
	// node = (Dz1Str)var->data;		// Dz1Str element: isScalar = FALSE;	isPrimitive = TRUE
	// node = (SomeStruct *)var->data	// Some Structure: isScalar = TRUE;		isPrimitive = FALSE
	// --------------------------------------------------
	// dst->add(dst, *node);		// u32_t element : isScalar = TRUE;		isPrimitive = TRUE
	// dst->add(dst, node);			// Dz1Str element: isScalar = FALSE;	isPrimitive = TRUE
	// dst->add(dst, node);			// Some Structure: isScalar = TRUE;		isPrimitive = FALSE
	// --------------------------------------------------
	ReplaceEntry rpl_ent[] = {
		{ Dz1Text("$list_type$"), array_type_name },
		{ Dz1Text("$member_type$"), type_name },
		{ Dz1Text("$member_rcv_ptr$"), ObjectInfo_isScalar(node_obj) ? Dz1Text(" *") : Dz1Text(" ") },
		{ Dz1Text("$member_add_ptr$"), ObjectInfo_isPrimitive(node_obj) && ObjectInfo_isScalar(node_obj) ? Dz1Text("*") :  Dz1Text("") },
		{ Dz1Text("$member_comment$"), ObjectInfo_isPrimitive(node_obj) && ObjectInfo_isScalar(node_obj) ? Dz1Text("// ") : Dz1Text("") },
		{ NULL, NULL }
	};

	if (_replated_write(dst, src_lines, rpl_ent, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

typedef struct PublishEnv
{
	Dz1Str			 output_name;
	Dz1Str			 module_name;

	FILE			*header;
	FILE			*source;

	ObjectInfoSeq	*primitives;
	ObjectInfoSeq	*constructs;
	ObjectInfoSeq	*arraies;
} PublishEnv;
static void PublishEnv_cleanup(void *ptr)
{
	PublishEnv *p = (PublishEnv *)ptr;
	Dz1FileStream_closeAndSetNull(&p->header);
	Dz1FileStream_closeAndSetNull(&p->source);

	ObjectInfoSeq_delAndSetNull(&p->primitives);
	ObjectInfoSeq_delAndSetNull(&p->constructs);
	ObjectInfoSeq_delAndSetNull(&p->arraies);
}

static bool_t _append_obj(ObjectInfoSeq *list, ObjectInfo *node, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = list->add(list, node)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error _Dz1JsonTargetObjects_publish(void *ptr, ObjectInfo *obj)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PublishEnv *env = (PublishEnv *)ptr;
	ObjectInfo *ori = ObjectInfo_getOrigin(obj);
	fprintf(env->source, Dz1Text("////////////////////////////////////////////////////////////////////////////////\n"));
	fprintf(env->source, Dz1Text("// %s\n"), obj->name);
	switch(ori->type)
	{
	case ObjectType_enumerate:				// EnumInfo
		if (_publish_enum_type_src(env->source, obj->name, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			if (_append_obj(env->primitives, obj, NULL) == FALSE) ERR_OUT(errp);
			Dz1Error_set(errp, 0);
		}
		break;
	case ObjectType_extern:					// ExternInfo(typedef native)
		fprintf(env->source, Dz1Text("// extern type\n"));
		break;
	case ObjectType_reference:
		fprintf(env->source, Dz1Text("// reference type\n"));
		break;
// 		if (ObjectInfo_isPrimitive(ori))
// 		{
// 			Dz1Thread_printf("External Type %s Append to Primitives =", obj->name); ObjectInfo_dump(obj, 0);
// 			if (_append_obj(env->primitives, obj, errp) == FALSE) ERR_OUT(errp);
// 			Dz1Error_set(errp, 0);
// 		}
// 		else 
// 		{
// 			Dz1Thread_printf("External Type %s Append to Construct\n", obj->name);
// 			if (_append_obj(env->constructs, obj, errp) == FALSE) ERR_OUT(errp);
// 			else Dz1Error_set(errp, 0);
// 		}
		break;
	case ObjectType_structure:				// StructureInfo
		if (_publish_struct_type_src(env->source, obj->name, ((StructureInfo *)obj->info)->members, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			if (_append_obj(env->constructs, obj, errp) == FALSE) ERR_OUT(errp);
			Dz1Error_set(errp, 0);
		}
		break;
	case ObjectType_union:					// UnionInfo
		if (_publish_union_type_src(env->source, obj->name, ((UnionInfo *)obj->info)->members, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			if (_append_obj(env->constructs, obj, errp) == FALSE) ERR_OUT(errp);
			Dz1Error_set(errp, 0);
		}
		break;
	case ObjectType_array:					// ArrayInfo
		if (_publish_array_type_src(env->source, obj->name, ((ArrayInfo *)obj->info)->entry, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			if (_append_obj(env->arraies, obj, errp) == FALSE) ERR_OUT(errp);
			Dz1Error_set(errp, 0);
		}
		break;
	case ObjectType_index:					// IndexInfo
		if (_publish_array_type_src(env->source, obj->name, ((IndexInfo *)obj->info)->entry, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			if (_append_obj(env->arraies, obj, errp) == FALSE) ERR_OUT(errp);
			Dz1Error_set(errp, 0);
		}
		break;
	default:
		ERR_SET_OUT(errp, ENOSYS);
		break;
	}
	if (errp->code == 0)
	{
		fprintf(env->source, Dz1Text("// %s\n"), obj->name);
		fprintf(env->source, Dz1Text("////////////////////////////////////////////////////////////////////////////////\n\n"));
	}
	return err;
}

/*
Dz1JsonSpec *$module_name$_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (0) { }

		else if ((*errp = Dz1JsonSpec_add_primitive(ret,	_primitive_arg(MyEnum) )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(ret,	_construct_arg(MyStruct), Dz1JsonConstructType_struct )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(ret,	_construct_arg(MyUnion), Dz1JsonConstructType_union )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(ret,	_construct_arg(MyComponent), Dz1JsonConstructType_struct )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(ret,		_array_arg(MyStructList, MyStruct) )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(ret,		_array_arg(MyUnionList, MyUnion) )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(ret,		_array_arg(StringList, Dz1Str) )).code) ERR_OUT(errp);

		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
*/


static Dz1Error _pub_prim_adder(void *ptr, ObjectInfo *p)
{	//\t\telse if ((*errp = Dz1JsonSpec_add_primitive(ret,	_primitive_arg(MyEnum) )).code) ERR_OUT(errp);
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *dst = (FILE *)ptr;
	fprintf(dst, Dz1Text("		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text(\"%s\"), %s_gen, %s_del, %s_load, %s_stringify)).code) ERR_OUT(errp);") CRLF,
						p->name, p->name, p->name, p->name, p->name);
	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_cons_adder(void *ptr, ObjectInfo *p)
{	//\t\telse if ((*errp = Dz1JSonSpec_add_construct(ret,	_construct_arg(MyStruct), Dz1JsonConstructType_struct )).code) ERR_OUT(errp);
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *ori = ObjectInfo_getOrigin(p);
	FILE *dst = (FILE *)ptr;
	Dz1Str tp_str = NULL, op_str = p->name;
	if (ori->type == ObjectType_structure) tp_str = Dz1Text("Dz1JsonConstructType_struct");
	else if (ori->type == ObjectType_union) tp_str = Dz1Text("Dz1JsonConstructType_union");
// 	else if (ori->type == ObjectType_extern || ori->type == ObjectType_reference)
// 	{
// 		ExternInfo *info = (ExternInfo *)ori->info;
// 		switch(info->isStatic)
// 		{
// 		case ExternInfoStatic_primitive:
// 		case ExternInfoStatic_primitive_ptr:
// 			ERR_SET_OUT(errp, EFAULT);
// 			break;
// 		case ExternInfoStatic_typical_union:
// 			tp_str = Dz1Text("Dz1JsonConstructType_union");
// 			op_str = Dz1Str_isVoid(info->prefix) ? p->name : info->prefix;
// 			break;
// 		default:
// 		case ExternInfoStatic_construct:
// 			tp_str = Dz1Text("Dz1JsonConstructType_struct");
// 			op_str = Dz1Str_isVoid(info->prefix) ? p->name : info->prefix;
// 			break;
// 		}
// 	}
	else Dz1Error_set(errp, EFAULT);

	if (errp->code == 0)
	{
		fprintf(dst, Dz1Text("		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text(\"%s\"), ")
											Dz1Text("%s_gen, %s_del, %s_setChild, %s_getChild, ")
											Dz1Text("%s_membs, %s)).code) ERR_OUT(errp);") CRLF,
				op_str, op_str, op_str, op_str, op_str, op_str, tp_str);
	}
	return err;
}

static Dz1Str _get_member_type_name(ObjectInfo *arr_obj, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str ret = NULL;
	if (arr_obj->type == ObjectType_array)
	{
		ArrayInfo *inf = (ArrayInfo *)arr_obj->info;
		ObjectInfo *memb_obj = inf->entry;
//		ret = memb_obj->name;
		if ((ret = json_resolve_name(memb_obj, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (arr_obj->type == ObjectType_index)
	{
		IndexInfo *inf = (IndexInfo *)arr_obj->info;
		ObjectInfo *memb_obj = inf->entry;
//		ret = memb_obj->name;
		if ((ret = json_resolve_name(memb_obj, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else ERR_SET_OUT(errp, EFAULT);
	return ret;
}

static Dz1Error _pub_arr_adder(void *ptr, ObjectInfo *p)
{	//\t\telse if ((*errp = Dz1JSonSpec_add_array(ret,		_array_arg(MyStructList, MyStruct) )).code) ERR_OUT(errp);
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *dst = (FILE *)ptr;
	ObjectInfo *ori = ObjectInfo_getOrigin(p);
	Dz1Str memb_type = _get_member_type_name(ori, errp);
	if (memb_type == NULL) ERR_OUT(errp);
	else
	{
		fprintf(dst, Dz1Text("		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text(\"%s\"), %s_gen, %s_del, %s_append, %s_cnt, %s_tlv, Dz1Text(\"%s\") )).code) ERR_OUT(errp);") CRLF,
											p->name, p->name, p->name, p->name, p->name, p->name, memb_type);
	}
	return err;
}

static bool_t _publish_spec_initializer(PublishEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	fprintf(env->source, Dz1Text("////////////////////////////////////////////////////////////////////////////////\n"));
	fprintf(env->source, Dz1Text("// Dz1JsonSpec Initializer\n"));
	fprintf(env->source, Dz1Text("bool_t %s_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)") CRLF, env->module_name);
	fprintf(env->source, Dz1Text("{") CRLF);
	fprintf(env->source, Dz1Text("	DZ1_ERROR_SAFE_PTR(errp, err);") CRLF);
//	fprintf(env->source, Dz1Text("	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);") CRLF);
	fprintf(env->source, Dz1Text("	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);") CRLF);
	fprintf(env->source, Dz1Text("	else") CRLF);
	fprintf(env->source, Dz1Text("	{") CRLF);
//	fprintf(env->source, Dz1Text("		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);") CRLF);
//	fprintf(env->source, CRLF);
	fprintf(env->source, Dz1Text("		if (0) { }") CRLF);

	if ((*errp = env->primitives->travel(env->primitives, _pub_prim_adder, (void *)env->source)).code) ERR_OUT(errp);
	if ((*errp = env->constructs->travel(env->constructs, _pub_cons_adder, (void *)env->source)).code) ERR_OUT(errp);
	if ((*errp = env->arraies->travel(env->arraies, _pub_arr_adder, (void *)env->source)).code) ERR_OUT(errp);

//	fprintf(env->source, CRLF);
	fprintf(env->source, Dz1Text("		else Dz1Error_set(errp, 0);") CRLF);
//	fprintf(env->source, CRLF);
//	fprintf(env->source, Dz1Text("		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);") CRLF);
	fprintf(env->source, Dz1Text("	}") CRLF);
	fprintf(env->source, Dz1Text("	return errp->code == 0 ? TRUE : FALSE;") CRLF);;
	fprintf(env->source, Dz1Text("}") CRLF);


	fprintf(env->source, Dz1Text("Dz1JsonSpec *%s_genJsonSpec(Dz1Error *err)") CRLF, env->module_name);
	fprintf(env->source, Dz1Text("{") CRLF);
	fprintf(env->source, Dz1Text("	DZ1_ERROR_SAFE_PTR(errp, err);") CRLF);
	fprintf(env->source, Dz1Text("	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);") CRLF);
	fprintf(env->source, Dz1Text("	if (ret == NULL) ERR_OUT(errp);") CRLF);
	fprintf(env->source, Dz1Text("	else") CRLF);
	fprintf(env->source, Dz1Text("	{") CRLF);
	fprintf(env->source, Dz1Text("		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);") CRLF);
	fprintf(env->source, CRLF);
	fprintf(env->source, Dz1Text("		if (%s_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);") CRLF, env->module_name);
	fprintf(env->source, Dz1Text("		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);") CRLF);
	fprintf(env->source, Dz1Text("		else Dz1Error_set(errp, 0);") CRLF);
	fprintf(env->source, CRLF);
	fprintf(env->source, Dz1Text("		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);") CRLF);
	fprintf(env->source, Dz1Text("	}") CRLF);
	fprintf(env->source, Dz1Text("	return ret;") CRLF);;
	fprintf(env->source, Dz1Text("}") CRLF);

	fprintf(env->source, Dz1Text("// Dz1JsonSpec Initializer\n"));
	fprintf(env->source, Dz1Text("////////////////////////////////////////////////////////////////////////////////\n"));

	return errp->code == 0 ? TRUE : FALSE;
}

typedef enum LetterFlag
{
	LetterFlag_none,
	LetterFlag_alphaU,
	LetterFlag_alphaL,
	LetterFlag_digit,
	LetterFlag_underbar,
	LetterFlag_else
} LetterFlag;

static LetterFlag _get_flag(char c)
{
	LetterFlag ret = LetterFlag_none;
	if (isdigit(c)) ret = LetterFlag_digit;
	else if (isalpha(c))
	{
		if (c >= 'a' && c <= 'z') ret = LetterFlag_alphaL;
		else ret = LetterFlag_alphaU;
	}
	else if (c == '_') ret = LetterFlag_underbar;
	else ret = LetterFlag_else;
	return ret;
}

static bool_t ins_arr[6][6] = 
{//	  N  U  L  D  B  E
	{ 0, 0, 0, 0, 0, 0 },	// None
	{ 0, 0, 0, 1, 0, 1 },	// Upper
	{ 0, 1, 0, 1, 0, 1 },	// Lower
	{ 0, 1, 1, 0, 0, 1 },	// Digit
	{ 0, 0, 0, 0, 0, 0 },	// underBar
	{ 0, 1, 1, 1, 0, 0 }	// Else
};

static void _mk_dcl_name(TCHAR *dst, TCHAR *src)
{
	LetterFlag prev_flag = LetterFlag_none, flag = LetterFlag_none;
	TCHAR *dp = dst, *cp = src;
	while(*cp)
	{
		flag = _get_flag(*cp);
		if (ins_arr[prev_flag][flag]) *dp++ = Dz1Text('_');
		*dp++ = Dz1Letter_ucase(*cp);
		prev_flag = flag;
		cp++;
	}
	*dp++ = 0;
}

/*
#ifndef {some_header_signiture}
#define {some_header_signiture}

#include <Dz1Json.h>
#include <{module_def_header}>

DZ1_CPPLINK bool_t <module_name>_jsonSpecGen(Dz1Error *err);

#endif
*/
static bool_t _publish_header(PublishEnv *env, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *dst = env->header;

	TCHAR dcl_name[256];
	_mk_dcl_name(dcl_name, env->output_name);

	fprintf(dst, Dz1Text("#ifndef %s_H") CRLF, dcl_name);
	fprintf(dst, Dz1Text("#define %s_H") CRLF, dcl_name);
	fprintf(dst, CRLF);
	fprintf(dst, Dz1Text("#include <Dz1Json.h>") CRLF);
	fprintf(dst, Dz1Text("#include \"%s.h\"") CRLF, env->module_name);
	fprintf(dst, CRLF);
	fprintf(dst, Dz1Text("DZ1_CPPLINK bool_t %s_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);") CRLF, env->module_name);
	fprintf(dst, Dz1Text("DZ1_CPPLINK Dz1JsonSpec *%s_genJsonSpec(Dz1Error *err);") CRLF, env->module_name);
	fprintf(dst, CRLF);
	fprintf(dst, Dz1Text("#endif // %s_H") CRLF, dcl_name);

	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error _header_stream_init(PublishEnv *dst, Dz1JsonCompilerArg *arg, Dz1Str name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (arg->hdr_out)
	{
		if ((dst->header = Dz1FileStream_open3(arg->hdr_out_path, name, Dz1Text("h"), Dz1Text("wb"), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _source_stream_init(PublishEnv *dst, Dz1JsonCompilerArg *arg, Dz1Str name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (arg->src_out)
	{
		if ((dst->source = Dz1FileStream_open3(arg->src_out_path, name, Dz1Text("c"), Dz1Text("wb"), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _source_publish(Dz1JsonTargetObjects *objs, PublishEnv *pub_env)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (pub_env->source != NULL)
	{
		ObjectInfoSeq *obj_seq = objs->seq;
		fprintf(pub_env->source, Dz1Text("#include \"%s.h\"") CRLF CRLF,pub_env->output_name);
		if ((*errp = obj_seq->travel(obj_seq, _Dz1JsonTargetObjects_publish, (void *)pub_env)).code) ERR_OUT(errp);
		else if (_publish_spec_initializer(pub_env, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _header_publish(PublishEnv *pub_env, Dz1Str name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (pub_env->header != NULL)
	{
		if (_publish_header(pub_env, name, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

bool_t Dz1JsonTargetObjects_publish(Dz1JsonCompilerEnv *env, Dz1JsonCompilerArg *arg, Dz1Str name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonTargetObjects *objs = NULL;
	ObjectInfoSeq *obj_seq = NULL;
	if (env == NULL || (objs = env->objs) == NULL || (obj_seq = objs->seq) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (name == NULL || name[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		PublishEnv pub_env = { arg->output_name, env->module_name, NULL, NULL };
		pthread_cleanup_push(PublishEnv_cleanup, (void *)&pub_env);
		if (0) { }
		else if ((*errp = _header_stream_init(&pub_env, arg, name)).code) ERR_OUT(errp);
		else if ((*errp = _source_stream_init(&pub_env, arg, name)).code) ERR_OUT(errp);
		else if ((pub_env.primitives = ObjectInfoSeq_new(errp)) == NULL) ERR_OUT(errp);
		else if ((pub_env.constructs = ObjectInfoSeq_new(errp)) == NULL) ERR_OUT(errp);
		else if ((pub_env.arraies = ObjectInfoSeq_new(errp)) == NULL) ERR_OUT(errp);

		else if ((*errp = _source_publish(env->objs, &pub_env)).code) ERR_OUT(errp);
		else if ((*errp = _header_publish(&pub_env, name)).code) ERR_OUT(errp);

		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (PublishEnv_cleanup, (void *)&pub_env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
