#include "dz1_todec.h"

static void _declare_var(FILE *fp, int tab, u32_t flag)
{
	if (flag)
	{
		while(tab--) Dz1Thread_fprintf(fp, "\t");
		if (flag & Dz1TodecUnitSize_Byte1) Dz1Thread_fprintf(fp, "u8_t v8; ");
		if (flag & Dz1TodecUnitSize_Byte2) Dz1Thread_fprintf(fp, "u16_t v16; ");
		if (flag & Dz1TodecUnitSize_Byte4) Dz1Thread_fprintf(fp, "u32_t v32; ");
		if (flag & Dz1TodecUnitSize_Byte8) Dz1Thread_fprintf(fp, "u64_t v64; ");
		Dz1Thread_fprintf(fp, NEW_LINE);
		Dz1Thread_fprintf(fp, NEW_LINE);
	}
}

static void _const_value_print(FILE *fp, Dz1Binary *value)
{
	u32_t i;
	for (i = 0; i < value->size; i++)
		Dz1Thread_fprintf(fp, "\\x%02X", value->data[i]);
}

///////////////////////////////////////////////////////////////////////////////
// Stream Element Publish
static Dz1Error StreamElementInfo_pub_read(FILE *fp, StreamElementInfo *info, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	switch(info->present)
	{
	case StreamElementInfoPresent_complex:
		// XXX : Complex Read
		break;
	case StreamElementInfoPresent_simple:
		if ((*errp = StreamElementSimple_pub_read(fp, info->x.simple, need_else, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case StreamElementInfoPresent_conditional:
		if ((*errp = StreamElementConditional_pub_read(fp, info->x.conditional, need_else, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case StreamElementInfoPresent_pad:
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1Stream_readPad(src, %u, errp), errp);" NEW_LINE, info->x.pad);
		Dz1Error_set(errp, 0);
		break;
	case StreamElementInfoPresent_value:
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1Stream_readConst(src, %u, (u8_t *)\"", info->x.value->size);
		_const_value_print(fp, info->x.value);
		Dz1Thread_fprintf(fp, "\", errp), errp);" NEW_LINE);
		break;
	case StreamElementInfoPresent_omit:
		Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return err;
}

static Dz1Error StreamElementInfo_pub_write_value(FILE *fp, Dz1Binary *value, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE(dst, (u8_t *)\"");
	_const_value_print(fp, value);
	Dz1Thread_fprintf(fp,"\", %u, errp, ret);" NEW_LINE, value->size);

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error StreamElementInfo_pub_write(FILE *fp, StreamElementInfo *info, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	switch(info->present)
	{
	case StreamElementInfoPresent_complex:
		// XXX : Complex Write
		break;
	case StreamElementInfoPresent_simple:
		if ((*errp = StreamElementSimple_pub_write(fp, info->x.simple, need_else, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case StreamElementInfoPresent_conditional:
		if ((*errp = StreamElementConditional_pub_write(fp, info->x.conditional, need_else, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case StreamElementInfoPresent_pad:
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1Stream_writePad(dst, %u, errp), errp);" NEW_LINE, info->x.pad);
		Dz1Error_set(errp, 0);
		break;
	case StreamElementInfoPresent_value:
		if ((*errp = StreamElementInfo_pub_write_value(fp, info->x.value, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case StreamElementInfoPresent_omit:
		Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return err;
}
// Stream Element Publish
///////////////////////////////////////////////////////////////////////////////

static Dz1Error pub_target_hdr(FILE *fp, str_t alter_name, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt, u32_t flags)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Str str_param = (flags & TODEC_FLAGS_USE_STACK) ? "Dz1StreamCallStk *param" : "void *param";
	str_t suffix = (alter_name == NULL || alter_name[0] == 0) ? "" : alter_name;
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK ssize_t %s%s_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, %s, Dz1Error *err);" NEW_LINE,
					   tgt->name, suffix, str_param);
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK ssize_t %s%s_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);" NEW_LINE,
					   tgt->name, suffix);
	Dz1Error_set(errp, 0);
	return err;
}

static int _pub_read_front(FILE *fp, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt, str_t suffix, u32_t flags, int tab)
{
	Dz1Str str_param = (flags & TODEC_FLAGS_USE_STACK) ? "Dz1StreamCallStk *_parent" : "void *param";
	Dz1Thread_ftprintf(fp, tab,   "%sssize_t %s%s_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, %s, Dz1Error *err)" NEW_LINE,
								   mode == Dz1TodecTargetCodecMode_public ? "" : "static ", tgt->name, suffix, str_param);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "ssize_t ret = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "DZ1_ERROR_SAFE_PTR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "%s *dst = (%s *)_dst;" NEW_LINE, tgt->name, tgt->name);
	Dz1Thread_ftprintf(fp, tab,       "if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++,     "{" NEW_LINE);

	if (flags & TODEC_FLAGS_USE_STACK)
		Dz1Thread_ftprintf(fp, tab,	      "Dz1StreamCallStk __param = { _parent, dst, _parent->user_ptr }, *param = &__param;" NEW_LINE);
	return tab;
}

static int _pub_write_front(FILE *fp, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt, str_t suffix, u32_t flags, int tab)
{
	Dz1Thread_ftprintf(fp, tab,   "%sssize_t %s%s_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)" NEW_LINE,
								   mode == Dz1TodecTargetCodecMode_public ? "" : "static ", tgt->name, suffix);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "ssize_t ret = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "DZ1_ERROR_SAFE_PTR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "%s *src = (%s *)_src;" NEW_LINE, tgt->name, tgt->name);
	Dz1Thread_ftprintf(fp, tab,       "if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++,     "{" NEW_LINE);

	return tab;
}

static int _pub_func_rear(FILE *fp, u32_t flags, int tab)
{
	Dz1Thread_ftprintf(fp, --tab,     "}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return tab;
}

///////////////////////////////////////////////////////////////////////////////
// Structure Type Gen & Read & Write
static Dz1Error pub_structure_src(FILE *fp, Dz1TodecTargetCodecEntry *codec, ObjectInfo *tgt, StreamInfo *info, u32_t flags)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int tab = 0;

	str_t alter_name = codec->alter_codec;
	Dz1TodecTargetCodecMode mode = codec->mode;

	u32_t cnt;
	StreamElementList *list = info->seq;
	StreamElementInfo **arr = NULL;
	if ((arr = list->get_array(list, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		bool_t need_else = FALSE;
		str_t suffix = (alter_name == NULL || alter_name[0] == 0) ? "" : alter_name;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);

		////////////////////////////////////////
		// Read
		tab = _pub_read_front(fp, mode, tgt, suffix, flags, tab);

		_declare_var(fp, tab, info->read_var);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			need_else = FALSE;
			if ((*errp = StreamElementInfo_pub_read(fp, arr[i], &need_else, tab)).code) ERR_OUT(errp);

			if (need_else) Dz1Thread_fprintf(fp, NEW_LINE);
		}

		if (Dz1Str_isVoid(codec->postfix) == FALSE)
		{
			if (codec->postfix[0] == '@')
			{
				str_t func_name = codec->postfix + 1;
				Dz1Thread_ftprintf(fp, tab,		"if (%s(dst, param, errp) == FALSE) ERR_OUT(errp); // use func name" NEW_LINE, func_name);
			}
			else Dz1Thread_ftprintf(fp, tab,	"if (%s_%s(dst, param, errp) == FALSE) ERR_OUT(errp); // use postfix" NEW_LINE, tgt->name, codec->postfix);
		}
		_pub_func_rear(fp, flags, tab);
		// Read
		////////////////////////////////////////

		////////////////////////////////////////
		// Write
		need_else = FALSE; tab = 0;
		tab = _pub_write_front(fp, mode, tgt, suffix, flags, tab);

		_declare_var(fp, tab, info->write_var);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			need_else = FALSE;
			if ((*errp = StreamElementInfo_pub_write(fp, arr[i], &need_else, tab)).code) ERR_OUT(errp);

			if (need_else) Dz1Thread_fprintf(fp, NEW_LINE);
		}
		_pub_func_rear(fp, flags, tab);
		// Write
		////////////////////////////////////////

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return err;
}

// Structure Type Gen & Read & Write
///////////////////////////////////////////////////////////////////////////////

static Dz1Error StreamObjectAttrUnion_read(FILE *fp, StreamObjectAttrUnion *p, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (p != NULL && p->pr != NULL)
	{
		if ((*errp = StreamElementSimple_pub_read(fp, p->pr, need_else, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error StreamObjectAttrUnion_write(FILE *fp, StreamObjectAttrUnion *p, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (p != NULL && p->pr != NULL)
	{
		if ((*errp = StreamElementSimple_pub_write(fp, p->pr, need_else, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

typedef struct FindByInstanceArg
{
	StreamElementInfo *ret;
	str_t name;
} FindByInstanceArg;

static Dz1Error _StreamElementList_findByInstance(void *ptr, StreamElementInfo *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FindByInstanceArg *arg = (FindByInstanceArg *)ptr;
	if (p->present == StreamElementInfoPresent_simple)
	{
		StreamElementSimple *simple = p->x.simple;
		StreamElementVariable *var = simple->var;
		if (strcmp(var->instance, arg->name) == 0)
		{
			arg->ret = p;
			Dz1Error_set(errp, EEXIST);
		}
	}
	else if (p->present == StreamElementInfoPresent_omit)
	{
		StreamElementVariable *var = p->x.omit;
		if (strcmp(var->instance, arg->name) == 0)
		{
			arg->ret = p;
			Dz1Error_set(errp, EEXIST);
		}
	}
	return err;
}

static StreamElementInfo *StreamElementList_findByInstance(StreamElementList *list, str_t name)
{
	FindByInstanceArg arg = { NULL, name };
	list->travel(list, _StreamElementList_findByInstance, (void *)&arg);
	return arg.ret;
}

///////////////////////////////////////////////////////////////////////////////
// Union Type Gen & Read & Write
static Dz1Error pub_union_src(FILE *fp, Dz1TodecTargetCodecEntry *codec, ObjectInfo *tgt, StreamInfo *info, u32_t flags)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int tab = 0;

	str_t alter_name = codec->alter_codec;
	Dz1TodecTargetCodecMode mode = codec->mode;

	ObjectInfo *ori = ObjectInfo_getOrigin(tgt);
	UnionInfo *obj_inf = NULL;
	UnionMemberList *obj_membs = NULL;

	u32_t cnt;
	StreamElementList *stream_seq = info->seq;
	StreamElementInfo **stream_arr = NULL;

	if (ori == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((obj_inf = (UnionInfo *)ori->info) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((obj_membs = obj_inf->members) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((stream_arr = stream_seq->get_array(stream_seq, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		bool_t need_else = FALSE;
		UnionMemberEntry *mb_tgt = NULL;
		StreamElementInfo *el_tgt = NULL;
		u32_t i, m_cnt = obj_membs->count(obj_membs);
		str_t suffix = (alter_name == NULL || alter_name[0] == 0) ? "" : alter_name;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)stream_arr);

		if (cnt != m_cnt) 
		{
			Dz1Thread_printf("!!! %s : element count(%u) != member count(%u)\n", tgt->name, cnt, m_cnt);
			if (cnt < m_cnt)
			{
				UnionMemberEntry **m_arr = obj_membs->get_array(obj_membs, NULL, NULL);
				if (m_arr != NULL)
				{
					pthread_cleanup_push(Dz1Memory_cancel, (void *)m_arr);
					for (i = 0; i < m_cnt; i++)
					{
						mb_tgt = m_arr[i];
						if (StreamElementList_findByInstance(stream_seq, mb_tgt->instance) == NULL)
							Dz1Thread_tprintf(1, "%s is not handled\n", mb_tgt->instance);
					}
					pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)m_arr);
				}
			}
		}

		////////////////////////////////////////
		// Read
		need_else = FALSE; tab = 0;
		tab = _pub_read_front(fp, mode, tgt, suffix, flags, tab);

		_declare_var(fp, tab, info->read_var);
		// {read_code}(src->present)
		StreamObjectAttrUnion_read(fp, info->attr->x.un, &need_else, tab);

		Dz1Thread_ftprintf(fp, tab,			"switch(dst->present)" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,			"{" NEW_LINE);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			// body
			el_tgt = stream_arr[i];
			switch(el_tgt->present)
			{
			case StreamElementInfoPresent_simple:
				{
					StreamElementSimple *simple = el_tgt->x.simple;
					StreamElementVariable *var = simple->var;
					if ((mb_tgt = obj_membs->find(obj_membs, var->instance)) == NULL) 
					{
						Dz1Thread_printf("Member not found \"%s\"\n", var->instance);
						ERR_SET_OUT(errp, ENOENT);
					}
					else
					{
						need_else = FALSE;
						Dz1Thread_ftprintf(fp, tab++,	"case %sPresent_%s:" NEW_LINE, tgt->name, mb_tgt->instance);
						if ((*errp = StreamElementInfo_pub_read(fp, el_tgt, &need_else, tab)).code) ERR_OUT(errp);
						Dz1Thread_ftprintf(fp, tab--,		"break;" NEW_LINE);
					}
				}
				break;
			case StreamElementInfoPresent_omit:
				{
					StreamElementVariable *var = el_tgt->x.omit;
					if ((mb_tgt = obj_membs->find(obj_membs, var->instance)) == NULL) 
					{
						Dz1Thread_printf("Member not found \"%s\"\n", var->instance);
						ERR_SET_OUT(errp, ENOENT);
					}
					else
					{
						need_else = FALSE;
						Dz1Thread_ftprintf(fp, tab,	"case %sPresent_%s: break;" NEW_LINE, tgt->name, mb_tgt->instance);
					}
				}
				break;
			default:
			case StreamElementInfoPresent_complex:
			case StreamElementInfoPresent_conditional:
			case StreamElementInfoPresent_pad:
			case StreamElementInfoPresent_value:
				ERR_SET_OUT(errp, EPERM);
				break;
			}
		}

		Dz1Thread_ftprintf(fp, tab++,		"default:" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,				"ERR_SET_OUT_RET(errp, EINVAL, -1);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab--,			"break;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,			"}" NEW_LINE);

		if (Dz1Str_isVoid(codec->postfix) == FALSE)
		{
			if (codec->postfix[0] == '@')
			{
				str_t func_name = codec->postfix + 1;
				Dz1Thread_ftprintf(fp, tab,	"if (%s(dst, param, errp) == FALSE) ERR_OUT(errp); // use func name" NEW_LINE, func_name);
			}
			else Dz1Thread_ftprintf(fp, tab,"if (%s_%s(dst, param, errp) == FALSE) ERR_OUT(errp); // use postfix" NEW_LINE, tgt->name, codec->postfix);
		}
		_pub_func_rear(fp, flags, tab);
		// Read
		////////////////////////////////////////

		////////////////////////////////////////
		// Write
		need_else = FALSE; tab = 0;
		tab = _pub_write_front(fp, mode, tgt, suffix, flags, tab);

		_declare_var(fp, tab, info->write_var);
		StreamObjectAttrUnion_write(fp, info->attr->x.un, &need_else, tab);

		Dz1Thread_ftprintf(fp, tab,			"switch(src->present)" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,			"{" NEW_LINE);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			// body
			el_tgt = stream_arr[i];
			switch(el_tgt->present)
			{
			case StreamElementInfoPresent_simple:
				{
					StreamElementSimple *simple = el_tgt->x.simple;
					StreamElementVariable *var = simple->var;
					if ((mb_tgt = obj_membs->find(obj_membs, var->instance)) == NULL) ERR_SET_OUT(errp, ENOENT);
					else
					{
						need_else = FALSE;
						Dz1Thread_ftprintf(fp, tab++,	"case %sPresent_%s:" NEW_LINE, tgt->name, mb_tgt->instance);
						if ((*errp = StreamElementInfo_pub_write(fp, el_tgt, &need_else, tab)).code) ERR_OUT(errp);
						Dz1Thread_ftprintf(fp, tab--,		"break;" NEW_LINE);
					}
				}
				break;
			case StreamElementInfoPresent_omit:
				{
					StreamElementVariable *var = el_tgt->x.omit;
					if ((mb_tgt = obj_membs->find(obj_membs, var->instance)) == NULL) 
					{
						Dz1Thread_printf("Member not found \"%s\"\n", var->instance);
						ERR_SET_OUT(errp, ENOENT);
					}
					else
					{
						need_else = FALSE;
						Dz1Thread_ftprintf(fp, tab,	"case %sPresent_%s: break;" NEW_LINE, tgt->name, mb_tgt->instance);
					}
				}
				break;
			default:
			case StreamElementInfoPresent_complex:
			case StreamElementInfoPresent_conditional:
			case StreamElementInfoPresent_pad:
			case StreamElementInfoPresent_value:
				ERR_SET_OUT(errp, EPERM);
				break;
			}
		}
		Dz1Thread_ftprintf(fp, tab++,		"default:" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,				"ERR_SET_OUT_RET(errp, EINVAL, -1);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab--,			"break;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,			"}" NEW_LINE);

		_pub_func_rear(fp, flags, tab);
		// Write
		////////////////////////////////////////
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)stream_arr);
	}
	return err;
}
// Union Type Gen & Read & Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Type Gen & Read & Write
static int _pub_array_hlp(FILE *fp, ObjectInfo *tgt, ObjectInfo *etr, str_t suffix,
						  StreamObjectAttrArray *attr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t need_else = FALSE;
	Dz1Thread_ftprintf(fp, tab,		"static Dz1Error _%s%s_write(void *ptr, %s *node)" NEW_LINE, tgt->name, suffix, etr->name);
	Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_VAR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,			"Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,			"Dz1Stream *dst = arg->stream;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,			"Dz1IOStreamEndian ed = arg->ed;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,			"void *param = arg->option;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,			"ssize_t sz = 0;" NEW_LINE);
	//								//	"if ((sz = %s_write(dst, p, ed, param, errp)) < 0) ERR_OUT(errp);"
	if ((*errp = StreamElementSimple_pub_sz_write(fp, attr->etr, &need_else, FALSE, tab)).code) ERR_OUT(errp);

	Dz1Thread_ftprintf(fp, tab,			"else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++,		"{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,				"arg->ret += sz;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,				"Dz1Error_set(errp, 0);" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab,		"}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,			"return err;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab,	"}" NEW_LINE);

	return tab;
}

static Dz1Error pub_array_src(FILE *fp, Dz1TodecTargetCodecEntry *codec, ObjectInfo *tgt, StreamInfo *info, u32_t flags)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alter_name = codec->alter_codec;
	Dz1TodecTargetCodecMode mode = codec->mode;

	ObjectInfo *ori = NULL, *etr = NULL;
	ArrayInfo *obj_info = NULL;
	StreamObjectAttr *attr = NULL;
	StreamObjectAttrArray *atar = NULL;
	if ((ori = ObjectInfo_getOrigin(tgt)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((obj_info = (ArrayInfo *)ori->info) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((etr = obj_info->entry) == NULL) ERR_SET_OUT(errp, EFAULT);

	else if ((attr = info->attr) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (attr->present != StreamObjectAttrPresent_ar) ERR_SET_OUT(errp, EINVAL);
	else if ((atar = attr->x.ar) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		int tab = 0;
		bool_t need_else = FALSE;
		str_t suffix = (alter_name == NULL || alter_name[0] == 0) ? "" : alter_name;

		tab = _pub_array_hlp(fp, tgt, etr, suffix, atar, tab);
		////////////////////////////////////////
		// Read
		need_else = FALSE; tab = 0;
		tab = _pub_read_front(fp, mode, tgt, suffix, flags, tab);

		Dz1Thread_ftprintf(fp, tab,		"u32_t i, cnt = 0;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,		"%s *node = NULL;" NEW_LINE, etr->name);
		//								"DZ1_STREAM_READ?(&cnt, src, ed, errp, ret);
		StreamElementSimple_pub_read(fp, atar->cnt, &need_else, tab);

		Dz1Thread_ftprintf(fp, tab,		"for (i = 0; errp->code == 0 && i < cnt; i++)" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,			"if ((node = %s_gen(errp)) == NULL) ERR_OUT(errp);" NEW_LINE, etr->name);
		Dz1Thread_ftprintf(fp, tab,			"else" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab++,		"{" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,				"ssize_t sz;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(%s_delAndSetNull, (void *)&node);" NEW_LINE, etr->name);

		need_else = FALSE;				//		"if ((sz = %s_read(node, src, ed, param, errp)) < 0) ERR_OUT(errp);"
		if ((*errp = StreamElementSimple_pub_sz_read(fp, atar->etr, &need_else, FALSE, tab)).code) ERR_OUT(errp);
		if (Dz1Str_isVoid(atar->postfix) == FALSE)
		{
			if (atar->postfix[0] == '@')
			{
				str_t func_name = atar->postfix + 1;
				Dz1Thread_ftprintf(fp, tab,		"else if (%s(node, param, errp) == FALSE) ERR_OUT(errp); // use func name" NEW_LINE, func_name);
			}
			else Dz1Thread_ftprintf(fp, tab,	"else if (%s_%s(node, param, errp) == FALSE) ERR_OUT(errp); // use postfix" NEW_LINE, tgt->name, atar->postfix);
		}
		Dz1Thread_ftprintf(fp, tab,				"else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,				"else" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab++,			"{" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,					"node = NULL;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,					"ret += sz;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,					"Dz1Error_set(errp, 0);" NEW_LINE);
		Dz1Thread_ftprintf(fp, --tab,			"}" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(1); // (%s_delAndSetNull, (void *)&node);" NEW_LINE, etr->name);
		Dz1Thread_ftprintf(fp, --tab,		"}" NEW_LINE);
		Dz1Thread_ftprintf(fp, --tab,	"}" NEW_LINE);
		_pub_func_rear(fp, flags, tab);
		// Read
		////////////////////////////////////////

		////////////////////////////////////////
		// Write
		need_else = FALSE; tab = 0;
		tab = _pub_write_front(fp, mode, tgt, suffix, flags, tab);

		Dz1Thread_ftprintf(fp, tab,		"Dz1ListStreamArg arg = { dst, 0, ed, param };" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,		"u32_t cnt = src->count(src);" NEW_LINE);
		//								"DZ1_STREAM_WRITE?(dst, &cnt, ed, errp, ret);
		StreamElementSimple_pub_write(fp, atar->cnt, &need_else, tab);
		Dz1Thread_ftprintf(fp, tab,		"if ((*errp = src->travel(src, _%s%s_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);" NEW_LINE, tgt->name, suffix);
		Dz1Thread_ftprintf(fp, tab,		"else { Dz1Error_set(errp, 0); ret += arg.ret; }" NEW_LINE);

		_pub_func_rear(fp, flags, tab);
		// Write
		////////////////////////////////////////

	}
	return err;
}

// Structure Type Gen & Read & Write
///////////////////////////////////////////////////////////////////////////////

typedef struct ObjectTypePublishApi
{
	ObjectType		 type;											   
	Dz1Error		 (*pub_src)(FILE *fp, Dz1TodecTargetCodecEntry *codec, ObjectInfo *tgt, StreamInfo *info, u32_t flags);
	Dz1Error		 (*pub_hdr)(FILE *fp, str_t alter_name, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt, u32_t flags);
} ObjectTypePublishApi;

static ObjectTypePublishApi *ObjectTypePublishApi_find(ObjectTypePublishApi *tbl, ObjectType type)
{
	ObjectTypePublishApi *i;
	for (i = tbl; i->type != ObjectType_max; i++)
		if (i->type == type) return i;
	return NULL;
}

static ObjectTypePublishApi objectTypePublishApi[] =
{
	{ ObjectType_structure,	pub_structure_src,	pub_target_hdr },
	{ ObjectType_union,		pub_union_src,		pub_target_hdr },
	{ ObjectType_array,		pub_array_src,		pub_target_hdr },
	{ ObjectType_index,		pub_array_src,		pub_target_hdr },
	{ ObjectType_max,		NULL, NULL }
};

///////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecEntry publish
static Dz1Error Dz1TodecTargetCodecEntry_publish(Dz1TodecTargetCodecEntry *p, ObjectInfo *tgt_obj, ObjectInfo *ori_obj, 
												 PublishEnv *env, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StreamInfo *info = NULL;
	ObjectTypePublishApi *api = ObjectTypePublishApi_find(objectTypePublishApi, ori_obj->type);
	if (api == NULL)
	{
		Dz1Thread_printf(Dz1T("!!! No API = ")); ObjectInfo_dump(ori_obj, 0);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if ((info = Dz1TodecTargetCodecEntry_analysis(p, ori_obj, module, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamInfo_delAndSetNull, (void *)&info);

		if (0) { }
		else if (p->mode != Dz1TodecTargetCodecMode_header && (*errp = api->pub_src(env->fp_src, p, tgt_obj, info, env->flags)).code) ERR_OUT(errp);
		else if (p->mode != Dz1TodecTargetCodecMode_private && (*errp = api->pub_hdr(env->fp_hdr, p->alter_codec, p->mode, tgt_obj, env->flags)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (StreamInfo_delAndSetNull, (void *)&seq);
	}
	return err;
}
// Dz1TodecTargetCodecEntry publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecList publish
static Dz1Error Dz1TodecTargetCodecList_publish(ObjectInfo *tgt, ObjectInfo *ori, Dz1TodecTargetCodecList *codecs,
												PublishEnv *env, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	u32_t cnt = 0;
	Dz1TodecTargetCodecEntry **arr = NULL;
	if ((arr = codecs->get_array(codecs, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		bool_t has_public = FALSE;

		u32_t i;
		Dz1TodecTargetCodecEntry *codec = NULL;

		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);

		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			codec = arr[i];
			if (codec->mode == Dz1TodecTargetCodecMode_public) has_public = TRUE;
			if ((*errp = Dz1TodecTargetCodecEntry_publish(codec, tgt, ori, env, module)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

		if (env->fp_hdr != NULL && has_public) Dz1Thread_fprintf(env->fp_hdr, NEW_LINE);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return err;
}
// Dz1TodecTargetCodecList publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TodecTarget publish
static Dz1Error Dz1TodecTarget_publish(Dz1TodecTarget *p, PublishEnv *env, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

//	ObjectTypeGenPublishApi *gen_api = NULL;
	ObjectInfo *tgt = NULL, *ori = NULL;

	if ((tgt = module->findObject(module, p->src_name)) == NULL)
	{
		Dz1Thread_printf("!!! Unknown Object %s\n", p->src_name);
		Dz1Thread_printf("!!! Module Name = %s\n", module->name);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if ((ori = ObjectInfo_getOrigin(tgt)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = Dz1TodecTargetCodecList_publish(tgt, ori, p->codecs, env, module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
// Dz1TodecTarget publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetList publish
typedef struct ListPubArg
{
	PublishEnv *env;
	Dz1MdefcModule *module;
} ListPubArg;

static Dz1Error _Dz1TodecTargetList_publish(void *ptr, Dz1TodecTarget *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ListPubArg *arg = (ListPubArg *)ptr;

	if ((*errp = Dz1TodecTarget_publish(p, arg->env, arg->module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;

}

static Dz1Error Dz1TodecTargetList_publish(Dz1TodecTargetList *list, PublishEnv *env, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ListPubArg arg = { env, module };
	if ((*errp = list->travel(list, _Dz1TodecTargetList_publish, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
// Dz1TodecTargetList publish
///////////////////////////////////////////////////////////////////////////////

static Dz1Error _base_pub_src_incl(FILE *fp, Dz1TodecInclude *incl)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t cnt = 0;
	Dz1TodecIncList *seq = incl->seq;
	Dz1TodecIncEntry **arr = seq->get_array(seq, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		Dz1TodecIncEntry *node = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; i < cnt; i++)
		{
			node = arr[i];
			Dz1Thread_fprintf(fp, "#include \"%s.h\"" NEW_LINE, node->name);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return err;
}

static void _base_pub_src(FILE *fp, Dz1TodecInclude *incl, str_t name, str_t output_suffix)
{
	if (fp != NULL)
	{
		str_t suffix = Dz1Str_isVoid(output_suffix) ? "" : output_suffix;
		_base_pub_src_incl(fp, incl);
		Dz1Thread_fprintf(fp, "#include \"%s%s.h\"" NEW_LINE NEW_LINE, name, suffix);
	}
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
static void _mk_dcl_name(char *dst, char *src)
{
	LetterFlag prev_flag = LetterFlag_none, flag = LetterFlag_none;
	char *dp = dst, *cp = src;
	while(*cp)
	{
		flag = _get_flag(*cp);
		if (ins_arr[prev_flag][flag]) *dp++ = '_';
		*dp++ = Dz1Letter_ucase(*cp);
		prev_flag = flag;
		cp++;
	}
	*dp++ = 0;
}

static void _base_pub_hdr_head(FILE *fp, str_t name, str_t mod_name)
{
	if (fp != NULL)
	{
		char dcl_name[1024] = { 0, };
		_mk_dcl_name(dcl_name, name);
		Dz1Thread_fprintf(fp, "#ifndef %s" NEW_LINE, dcl_name);
		Dz1Thread_fprintf(fp, "#define %s" NEW_LINE NEW_LINE, dcl_name);
		Dz1Thread_fprintf(fp, "#include <dz1_io_stream.h>" NEW_LINE);
		Dz1Thread_fprintf(fp, "#include \"%s.h\"" NEW_LINE, mod_name);
	}
}

static void _base_pub_hdr_tail(FILE *fp, str_t name, str_t mod_name)
{
	if (fp != NULL)
	{
		char dcl_name[1024] = { 0, };
		_mk_dcl_name(dcl_name, name);
		Dz1Thread_fprintf(fp, "#endif // %s" NEW_LINE, dcl_name);
	}
}

static void _get_mod_name(char dst[1024], str_t src)
{
	char *cp = strrchr(src, DIR_SEP_A);
	if (cp == NULL) strcpy(dst, src);
	else
	{
		cp++;
		strcpy(dst, cp);
		if ((cp = strrchr(dst, '.')) != NULL) *cp = 0;
	}
}

static Dz1Error _file_fix(str_t dest_fn, str_t temp_fn, str_t basis_fn, bool_t doTouch)
{	// todec은 항상 파일을 갱신한다.
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	unlink(dest_fn);
	if (rename(temp_fn, dest_fn) < 0)
	{	// 신규파일 이름변경 실패 -> 진행 불가
		unlink(temp_fn);
		ERR_SET_OUT(&err, errno);
	}
	return err;
}

static Dz1Error file_fix(Dz1Str dst_path, Dz1Str dst_name, Dz1Str dst_ext, Dz1Str src_path, Dz1Str src_name, Dz1Str src_ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char dest_fn[1024], temp_fn[1024], src_fn[1024];
	if		((*errp = Dz1FileName_concatPathNameExt(Dz1ArrParam(char, dest_fn), dst_path, dst_name, dst_ext)).code) ERR_OUT(errp);				// 출력 파일
	else if ((*errp = Dz1FileName_concatPathNameExt(Dz1ArrParam(char, temp_fn), dst_path, TEMPORARY_FILE_NAME, dst_ext)).code) ERR_OUT(errp);	// 임시 출력
	else if ((*errp = Dz1FileName_concatPathNameExt(Dz1ArrParam(char, src_fn), src_path, src_name, src_ext)).code) ERR_OUT(errp);				// 원본 스크립트
	else if ((*errp = _file_fix(dest_fn, temp_fn, src_fn, TRUE)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error _Dz1Todec_publish(str_t path, str_t name, str_t ext, Dz1TodecPubArg *arg, str_t output_suffix)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	PublishEnv *env = PublishEnv_new(path, name, ext, arg, errp);
	if (env == NULL) ERR_OUT(errp);
	else
	{
		Dz1Todec *p = NULL;
		pthread_cleanup_push(PublishEnv_delAndSetNull, (void *)&env);
		if ((p = Dz1Todec_parse(env->text, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MdefcModule *module = NULL;
			pthread_cleanup_push(Dz1Todec_delAndSetNull, (void *)&p);
			if ((module = Dz1MdefcModule_iload(env->inc_path, env->inc_path_cnt, p->mod_name, errp)) == NULL) ERR_OUT(errp);
			else
			{
				char mod_name[1024];
				pthread_cleanup_push(Dz1MdefcModule_delAndSetNull, (void *)&module);

				_get_mod_name(mod_name, module->name);
				_base_pub_src(env->fp_src, p->incl, name, output_suffix);
				_base_pub_hdr_head(env->fp_hdr, name, mod_name);
				if ((*errp = Dz1TodecTargetList_publish(p->list, env, module)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				_base_pub_hdr_tail(env->fp_hdr, name, mod_name);

				pthread_cleanup_pop(1); // (Dz1MdefcModule_delAndSetNull, (void *)&module);
			}
			pthread_cleanup_pop(1); // (Dz1Todec_delAndSetNull, (void *)&p);
		}
		pthread_cleanup_pop(1); // (PublishEnv_delAndSetNull, (void *)&env);
	}
	return err;
}

Dz1Error Dz1Todec_publish(str_t src_path, str_t src_name, str_t src_ext, Dz1TodecPubArg *arg, str_t output_suffix)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char dst_name[512] = { 0, };
	Dz1TodecPubArg local_arg = {
		arg->mod_inc_path, 
		(arg->dst_path_c == NULL || arg->dst_path_c[0] == 0) ? src_path : arg->dst_path_c,
		(arg->dst_path_h == NULL || arg->dst_path_h[0] == 0) ? src_path : arg->dst_path_h,
		arg->output_src,
		arg->output_hdr,
		arg->flags
	};
	
	strcpy(dst_name, src_name);
	if (output_suffix != NULL && output_suffix[0] != 0) strcat(dst_name, output_suffix);

	if ((*errp = _Dz1Todec_publish(src_path, src_name, src_ext, &local_arg, output_suffix)).code) ERR_OUT(errp);
	else if ((*errp = file_fix(local_arg.dst_path_c, dst_name, "c", src_path, src_name, src_ext)).code) ERR_OUT(errp);
	else if ((*errp = file_fix(local_arg.dst_path_h, dst_name, "h", src_path, src_name, src_ext)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
