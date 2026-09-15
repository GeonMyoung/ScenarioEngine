#include "dz1_todec.h"

///////////////////////////////////////////////////////////////////////////////
// member Check & Generate
static Dz1Error _pub_read_ptr_generator(FILE *fp, PointerNodeList *ptrs, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (ptrs->count(ptrs) > 0)
	{	// Gen Code
		u32_t cnt = 0;
		PointerNodeEntry **arr = ptrs->get_array(ptrs, &cnt, errp);
		if (arr == NULL) ERR_OUT_RET(errp, err);
		else
		{
			u32_t i;
			PointerNodeEntry *e = NULL;
			ObjectInfo *o = NULL;
			for (i = 0; i < cnt; i++)
			{
				e = arr[i];
				o =  e->obj;
				Dz1Thread_ftprintf(fp, tab, "%sif (dst->%s == NULL && (dst->%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
									*need_else ? "else " : "", e->name, e->name, o->name);
				*need_else = TRUE;
			}
		}
	}
	return err;
}

static Dz1Error _pub_write_ptr_checker(FILE *fp, PointerNodeList *ptrs, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (ptrs->count(ptrs) > 0)
	{	// Gen Code
		u32_t cnt = 0;
		PointerNodeEntry **arr = ptrs->get_array(ptrs, &cnt, errp);
		if (arr == NULL) ERR_OUT_RET(errp, err);
		else
		{
			u32_t i;
			PointerNodeEntry *e = NULL;
//			ObjectInfo *o = NULL;
			for (i = 0; i < cnt; i++)
			{
				e = arr[i];
//				o = e->obj;
				Dz1Thread_ftprintf(fp, tab, "%sif (src->%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
									*need_else ? "else " : "", e->name);
				*need_else = TRUE;
			}
		}
	}
	return err;
}
// member Check & Generate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stream Simple Element Alternated Publish
static Dz1Error _pub_read_by_mode(FILE *fp, StreamElementVariable *var, ObjectTypeMembPublishApi *tbl, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ObjectInfo *ori = var->origin;
	ObjectTypeMembPublishApi *api = ObjectTypeMembPublishApi_find(tbl, ori->type);
	if (api == NULL)
	{
		Dz1Thread_printf("Np API = "); ObjectInfo_dump(ori, 0);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if (api->pub_read == NULL) ERR_SET_OUT(errp, EPERM);
	else
	{
		if (do_gen && (*errp = _pub_read_ptr_generator(fp, var->ptrs, need_else, tab)).code) ERR_OUT(errp);
		else if ((*errp = api->pub_read(fp, var, ptr, need_else, do_gen, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _pub_write_by_mode(FILE *fp, StreamElementVariable *var, ObjectTypeMembPublishApi *tbl, void *ptr, bool_t *need_else, bool_t ptr_chk, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ObjectInfo *ori = var->origin;
	ObjectTypeMembPublishApi *api = ObjectTypeMembPublishApi_find(tbl, ori->type);
	if (api == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (api->pub_write == NULL) ERR_SET_OUT(errp, EPERM);
	else
	{
/*
	if (dst->xxx == NULL) ERR_OUT_RET(errp. -1);
	else if (dst->xxx->yyy == NULL) ERR_OUT_RET(errp, -1);
*/
		if (ptr_chk && (*errp = _pub_write_ptr_checker(fp, var->ptrs, need_else, tab)).code) ERR_OUT(errp);
/*
	else if (dst->xxx->yyy->zzz == NULL) ERR_OUT_RET(errp. -1);
	else DZ1_STREAM_WRITEn(dst, src->xxx->yyy->zzz, ed, errp, ret);
	else DZ1_IO_STREAM_FUNC(ret, some_write(dst, src->xxx->yyy->zzz, ed, param, errp), errp);
*/
		else if ((*errp = api->pub_write(fp, var, ptr, need_else, ptr_chk, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
// Stream Simple Element Alternated Publish
///////////////////////////////////////////////////////////////////////////////

static bool_t _chk_nul_flagable(StreamElementVariable *var)
{
	bool_t ret = FALSE;
	if (var != NULL)
	{
		if (var->var_is_ptr) ret = TRUE;
		else
		{
			ObjectInfo *obj = var->origin;
			if (obj->type == ObjectType_primitive)
			{
				PrimitiveInfo *info = (PrimitiveInfo *)obj->info;
				if (info->storage == NativeStorage_address) ret = TRUE;
			}
		}
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Stream Simple Element Publish
Dz1Error StreamElementSimple_pub_read(FILE *fp, StreamElementSimple *p, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	StreamElementVariable *var = p->var;
	StreamElementSimpleMethod *met = p->met;
	if (met == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		char var_name[512] = { 0 };
		bool_t backup_else, do_gen = TRUE;
		bool_t nullflagable = _chk_nul_flagable(var);

		if (var->mother == NULL) strcpy(var_name, var->variable); else { strcpy(var_name, "dst->"); strcat(var_name, var->variable); }

		if (nullflagable && p->nul_flag != Dz1TodecUnitSize_max)
		{
			if (*need_else)
			{
				Dz1Thread_ftprintf(fp, tab,		"else" NEW_LINE);
				Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);
			}

			switch(p->nul_flag)
			{
			case Dz1TodecUnitSize_Byte1:
				Dz1Thread_ftprintf(fp, tab,	"DZ1_STREAM_READ1(&v%d, src, errp, ret); // Flag" NEW_LINE, p->nul_flag * 8);
				break;
			default:
				Dz1Thread_ftprintf(fp, tab,	"DZ1_STREAM_READ%d(&v%d, src, ed, errp, ret); // Flag" NEW_LINE, p->nul_flag, p->nul_flag * 8);
				break;
			}

			Dz1Thread_ftprintf(fp, tab,	"if (v%d)" NEW_LINE, p->nul_flag * 8);
			Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);

			backup_else = *need_else;
			*need_else = FALSE;
			// do_gen = FALSE;
		}

		switch(met->present)
		{
		case StreamElementSimpleMethodPresent_def:
			if ((*errp = _pub_read_by_mode(fp, p->var, membDefPublishApi, NULL, need_else, do_gen, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case StreamElementSimpleMethodPresent_restricted:
			if ((*errp = _pub_read_by_mode(fp, p->var, membRstrPublishApi, met->x.restricted, need_else, do_gen, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case StreamElementSimpleMethodPresent_part:
			if ((*errp = _pub_read_by_mode(fp, p->var, membPartPublishApi, met->x.part, need_else, do_gen, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case StreamElementSimpleMethodPresent_alter:
			if ((*errp = _pub_read_by_mode(fp, p->var, membAltPublishApi, met->x.alter, need_else, do_gen, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}

		if (Dz1Str_isVoid(p->postfix) == FALSE)
		{
			Dz1Str addr_str = var->var_is_ptr ? "" : "&";
			if (p->postfix[0] == '@')
			{
				str_t func_name = p->postfix;
				func_name++;
				Dz1Thread_ftprintf(fp, tab, "if (%s(%s%s, param, errp) == FALSE) ERR_OUT_RET(errp, -1);" NEW_LINE, func_name, addr_str, var_name);
			}
			else
			{
				ObjectInfo *tgt = var->target;
				Dz1Thread_ftprintf(fp, tab, "if (%s_%s(%s%s, param, errp) == FALSE) ERR_OUT_RET(errp, -1);" NEW_LINE, ObjectInfo_nameOf(tgt), p->postfix, addr_str, var_name);
			}
		}

		if (nullflagable && p->nul_flag != Dz1TodecUnitSize_max)
		{
			Dz1Thread_ftprintf(fp, --tab,	"}" NEW_LINE);
			*need_else = backup_else;
			if (*need_else) Dz1Thread_ftprintf(fp, --tab,	"}" NEW_LINE);
		}
	}
	return err;
}

Dz1Error StreamElementSimple_pub_write(FILE *fp, StreamElementSimple *p, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	StreamElementVariable *var = p->var;
	StreamElementSimpleMethod *met = p->met;
	if (met == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		char var_name[512] = { 0 };
		bool_t backup_else, chk_ptr = TRUE;
		bool_t nullflagable = _chk_nul_flagable(var);

		if (var->mother == NULL) strcpy(var_name, var->variable); else { strcpy(var_name, "src->"); strcat(var_name, var->variable); }

		if (nullflagable && p->nul_flag != Dz1TodecUnitSize_max)
		{
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ", *need_else ? "else " : "", var_name);
			switch(p->nul_flag)
			{
			case Dz1TodecUnitSize_Byte1:
				Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE1(dst, 0, errp, ret);" NEW_LINE);
				break;
			default:
				Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE%d(dst, 0, ed, errp, ret);" NEW_LINE, p->nul_flag);
				break;
			}
			Dz1Thread_ftprintf(fp, tab, "else" NEW_LINE);
			Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
			switch(p->nul_flag)
			{
			case Dz1TodecUnitSize_Byte1:
				Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE1(dst, 1, errp, ret);" NEW_LINE);
				break;
			default:
				Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE%d(dst, 1, ed, errp, ret);" NEW_LINE, p->nul_flag);
				break;
			}
			backup_else = *need_else;
			*need_else = FALSE;
			chk_ptr = FALSE;
		}

		switch(met->present)
		{
		case StreamElementSimpleMethodPresent_def:
			if ((*errp = _pub_write_by_mode(fp, p->var, membDefPublishApi, NULL, need_else, chk_ptr, tab)).code) ERR_OUT(errp);
			break;
		case StreamElementSimpleMethodPresent_restricted:
			if ((*errp = _pub_write_by_mode(fp, p->var, membRstrPublishApi, met->x.restricted, need_else, chk_ptr, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case StreamElementSimpleMethodPresent_part:
			if ((*errp = _pub_write_by_mode(fp, p->var, membPartPublishApi, met->x.part, need_else, chk_ptr, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case StreamElementSimpleMethodPresent_alter:
			if ((*errp = _pub_write_by_mode(fp, p->var, membAltPublishApi, met->x.alter, need_else, chk_ptr, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}

		if (nullflagable && p->nul_flag != Dz1TodecUnitSize_max)
		{
			Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
			*need_else = backup_else;
		}

	}
	return err;
}
// Stream Simple Element Publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stream Simple Element count Publish
Dz1Error StreamElementSimple_pub_sz_read(FILE *fp, StreamElementSimple *p, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	StreamElementSimpleMethod *met = p->met;
	if (met == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		switch(met->present)
		{
		case StreamElementSimpleMethodPresent_def:
			if ((*errp = _pub_read_by_mode(fp, p->var, membDefSzPublishApi, NULL, need_else, do_gen, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case StreamElementSimpleMethodPresent_part:
			if ((*errp = _pub_read_by_mode(fp, p->var, membPartSzPublishApi, met->x.part, need_else, do_gen, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case StreamElementSimpleMethodPresent_alter:
			if ((*errp = _pub_read_by_mode(fp, p->var, membAltSzPublishApi, met->x.alter, need_else, do_gen, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}

Dz1Error StreamElementSimple_pub_sz_write(FILE *fp, StreamElementSimple *p, bool_t *need_else, bool_t ptr_chk, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	StreamElementSimpleMethod *met = p->met;
	if (met == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		switch(met->present)
		{
		case StreamElementSimpleMethodPresent_def:
			if ((*errp = _pub_write_by_mode(fp, p->var, membDefSzPublishApi, NULL, need_else, ptr_chk, tab)).code) ERR_OUT(errp);
			break;
		case StreamElementSimpleMethodPresent_part:
			if ((*errp = _pub_write_by_mode(fp, p->var, membPartSzPublishApi, met->x.part, need_else, ptr_chk, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case StreamElementSimpleMethodPresent_alter:
			if ((*errp = _pub_write_by_mode(fp, p->var, membAltSzPublishApi, met->x.alter, need_else, ptr_chk, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}
// Stream Simple Element count Publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// StreamElementConditional
Dz1Error StreamElementConditional_pub_read(FILE *fp, StreamElementConditional *p, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t decider = NULL;
	StreamElementVariable *var = p->var;
	StreamElementSimpleMethod *met = p->met;
	if (met == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((decider = Dz1Str_replace(p->decider, "$$", "dst", errp)) == NULL) ERR_OUT(errp);
	else
	{
		char var_name[512] = { 0 };
		StreamElementSimple simple = { p->var, p->met, Dz1TodecUnitSize_max, p->postfix };
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&decider);

		if (var->mother == NULL) strcpy(var_name, var->variable); else { strcpy(var_name, "dst->"); strcat(var_name, var->variable); }

		Dz1Thread_ftprintf(fp, tab,		"%sif (%s)" NEW_LINE, *need_else ? "else " : "", decider);
		Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);

		*need_else = FALSE;
		if ((*errp = StreamElementSimple_pub_read(fp, &simple, need_else, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_ftprintf(fp, --tab,	"}" NEW_LINE);

		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&decider);
	}
	return err;
}

Dz1Error StreamElementConditional_pub_write(FILE *fp, StreamElementConditional *p, bool_t *need_else, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t decider = NULL;
	StreamElementVariable *var = p->var;
	StreamElementSimpleMethod *met = p->met;
	if (met == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((decider = Dz1Str_replace(p->decider, "$$", "src", errp)) == NULL) ERR_OUT(errp);
	else
	{
		char var_name[512] = { 0 };
		StreamElementSimple simple = { p->var, p->met, Dz1TodecUnitSize_max, p->postfix };
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&decider);

		if (var->mother == NULL) strcpy(var_name, var->variable); else { strcpy(var_name, "dst->"); strcat(var_name, var->variable); }

		Dz1Thread_ftprintf(fp, tab,		"%sif (%s)" NEW_LINE, *need_else ? "else " : "", decider);
		Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);

		*need_else = FALSE;
		if ((*errp = StreamElementSimple_pub_write(fp, &simple, need_else, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_ftprintf(fp, --tab,	"}" NEW_LINE);

		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&decider);
	}
	return err;
}
// StreamElementConditional
///////////////////////////////////////////////////////////////////////////////


