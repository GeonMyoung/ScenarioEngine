#include <dz1_thread_stdio.h>
#include "Dz1JsonStructUtil.h"
#include "Dz1JsonStringify.h"

static Dz1Str str_tab = Dz1Text("\t");
static Dz1Str str_comma = Dz1Text(",");
static Dz1Str str_nul = Dz1Text("null");
static Dz1Str str_lst_start1 = Dz1Text("{");
static Dz1Str str_lst_end1 = Dz1Text("}");
static Dz1Str str_lst_start2 = Dz1Text("{ ");
// static Dz1Str str_lst_end2 = Dz1Text(" }"); // modified by gm 20230605 - not used yet
static Dz1Str str_cotate = Dz1Text("\"");
static Dz1Str str_cotcol = Dz1Text("\":");

//static bool_t _stringify_tab(Dz1ElasticBuf *elb, u32_t tab, Dz1Error *err)
static bool_t _stringify_tab(Dz1ElasticBuf *elb, Dz1JsonNewLineInfo *nli, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (nli->len == 0) Dz1Error_set(errp, 0);
	else
	{
		u32_t tab = nli->tab;
		while(tab)
		{
			if (_Dz1ElasticBuf_push(elb, (u8_t *)str_tab, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				tab--;
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static bool_t _stringify_obj(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecEntry *spe, Dz1JsonNewLineInfo *nli, bool_t *ret_lf, Dz1Error *err);

static bool_t _convert_charset_push(Dz1JsonConv *h, Dz1ElasticBuf *dst, Dz1ElasticBuf *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	u8_t *temp = NULL;
	size_t t_sz = 0;
	if (h == NULL || dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(src, errp)) == NULL) ERR_OUT(errp);
	else if ((temp = (u8_t *)Dz1Malloc((t_sz = bin->size * 4), errp)) == NULL) ERR_OUT(errp);
	else
	{
		u8_t *dp = temp, *sp = bin->data;
		size_t s_sz = bin->size;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		if (Dz1JsonConv_do(h, &dp, &t_sz, &sp, &s_sz, errp) == FALSE) ERR_OUT(errp);
		else
		{
			size_t consume = (size_t)(sp - bin->data);
			size_t len = (size_t)(dp - temp);
			if (consume != bin->size) Dz1Thread_printf(Dz1T("!!! String may truncated\n"));

			if (_Dz1ElasticBuf_push(dst, temp, len, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Primitive Stringify
static bool_t Dz1JsonSpecPrimitive_stringify(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecPrimitive *spd, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (spd->stringify(obj, elb, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1JsonSpecPrimitive_stringify_root(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecPrimitive *spd, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Str lst_start = Dz1Text("{ ");
	Dz1Str lst_end = Dz1Text(" }");
	if (0) { }
	else if (_Dz1ElasticBuf_push(elb, (u8_t *)lst_start, sizeof(TCHAR) * 2, errp) == FALSE) ERR_OUT(errp);		// {
	else if (Dz1JsonSpecPrimitive_stringify(env, obj, elb, spd, errp) == FALSE) ERR_OUT(errp);					// value
	else if (_Dz1ElasticBuf_push(elb, (u8_t *)lst_end, sizeof(TCHAR) * 2, errp) == FALSE) ERR_OUT(errp);		// }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
// Primitive Stringify
///////////////////////////////////////////////////////////////////////////////

static bool_t Dz1JsonSpecStruct_stringify(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecConstruct *spd, Dz1JsonNewLineInfo *nli, bool_t *ret_lf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (_Dz1ElasticBuf_push(elb, (u8_t *)str_nul, sizeof(TCHAR) * 4, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		u32_t cnt = 0;
		Dz1JsonSpecChilds *childs = spd->childs;
		Dz1JsonSpecChild **arr = childs->get_array(childs, &cnt, errp);
		if (arr == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
			if (_Dz1ElasticBuf_push(elb, (u8_t *)str_lst_start1, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);				// {
			else if (_Dz1ElasticBuf_push(elb, (u8_t *)nli->str, sizeof(TCHAR) * nli->len, errp) == FALSE) ERR_OUT(errp);	// <NL>
			else
			{
				u32_t i, j;
				bool_t is_first = TRUE;
				bool_t line_feeded = FALSE;
				Dz1JsonSpecChild *node = NULL;

				(*ret_lf) = FALSE;
				nli->tab++;

				// sort by index
				for (i = 0; i < cnt; i++)
				{
					for (j = i + 1; j < cnt; j++)
					{
						if (arr[j]->index < arr[i]->index)
						{
							Dz1JsonSpecChild *temp = arr[i];
							arr[i] = arr[j]; arr[j] = temp;
						}
					}
				}

				for (i = 0; errp->code == 0 && i < cnt; i++)
				{
					if ((node = arr[i]) != NULL)
					{
						void *child_obj = spd->get_child(obj, &node, NULL);
						Dz1JsonSpecEntry *child_spe = Dz1JsonSpec_findType(env->spec, node->type);

						line_feeded = FALSE;
						if (is_first) is_first = FALSE;
						else
						{	// ",\n" for second element
							if (_Dz1ElasticBuf_push(elb, (u8_t *)str_comma, sizeof(TCHAR) * 1, errp) == FALSE) ERR_OUT(errp);							// ,
							else if (_Dz1ElasticBuf_push(elb, (u8_t *)nli->str, sizeof(TCHAR) * nli->len, errp) == FALSE) ERR_OUT(errp);				// <NL>
						}

						if (errp->code == 0)
						{
							if (_stringify_tab(elb, nli, errp) == FALSE) ERR_OUT(errp);																	// tabs
							else if (_Dz1ElasticBuf_push(elb, (u8_t *)str_cotate, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);							// "
							else if (_Dz1ElasticBuf_push(elb, (u8_t *)node->name, sizeof(TCHAR) * Dz1STRLEN(node->name), errp) == FALSE) ERR_OUT(errp);	// name
							else if (_Dz1ElasticBuf_push(elb, (u8_t *)str_cotcol, sizeof(TCHAR) * 2, errp) == FALSE) ERR_OUT(errp);						// ":
							else if (_stringify_obj(env, child_obj, elb, child_spe, nli, &line_feeded, errp) == FALSE) ERR_OUT(errp);					// {obj}
							else Dz1Error_set(errp, 0);
						}
					}
				}
				if (_Dz1ElasticBuf_push(elb, (u8_t *)nli->str, sizeof(TCHAR) * nli->len, errp) == FALSE) ERR_OUT(errp);									// <NL>

				nli->tab--;
				if (_stringify_tab(elb, nli, errp) == FALSE) ERR_OUT(errp);																		// tabs
				else if (_Dz1ElasticBuf_push(elb, (u8_t *)str_lst_end1, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);							// }
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1JsonSpecUnion_stringify(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecConstruct *spd, Dz1JsonNewLineInfo *nli, bool_t *ret_lf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (_Dz1ElasticBuf_push(elb, (u8_t *)str_nul, sizeof(TCHAR) * 4, errp) == FALSE) ERR_OUT(errp);										// null
		else Dz1Error_set(errp, 0);
	}
	else
	{
//		if (_Dz1ElasticBuf_push(elb, (u8_t *)str_lst_start2, sizeof(TCHAR) * 2, errp) == FALSE) ERR_OUT(errp);								// '{ ' <= printed at same line
		if (_Dz1ElasticBuf_push(elb, (u8_t *)str_lst_start1, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);				// {
		else if (_Dz1ElasticBuf_push(elb, (u8_t *)nli->str, sizeof(TCHAR) * nli->len, errp) == FALSE) ERR_OUT(errp);	// <NL>
		else
		{
			bool_t line_feeded = FALSE;
			Dz1JsonSpecChild *child = NULL;
			void *child_obj = spd->get_child(obj, &child, spd->childs);
			Dz1JsonSpecEntry *child_spe = Dz1JsonSpec_findType(env->spec, child->type);

			*ret_lf = FALSE;
			nli->tab++;

			if		(_stringify_tab(elb, nli, errp) == FALSE) ERR_OUT(errp);																// tabs
			else if (_Dz1ElasticBuf_push(elb, (u8_t *)str_cotate, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);								// "
			else if (_Dz1ElasticBuf_push(elb, (u8_t *)child->name, sizeof(TCHAR) * Dz1STRLEN(child->name), errp) == FALSE) ERR_OUT(errp);	// name <= is present
			else if (_Dz1ElasticBuf_push(elb, (u8_t *)str_cotcol, sizeof(TCHAR) * 2, errp) == FALSE) ERR_OUT(errp);							// ":
			else if (_stringify_obj(env, child_obj, elb, child_spe, nli, &line_feeded, errp) == FALSE) ERR_OUT(errp);						// {obj}
			else
			{
				if (_Dz1ElasticBuf_push(elb, (u8_t *)nli->str, sizeof(TCHAR) * nli->len, errp) == FALSE) ERR_OUT(errp);						// <NL>
				nli->tab--;
				if (_stringify_tab(elb, nli, errp) == FALSE) ERR_OUT(errp);																	// tabs
				else if (_Dz1ElasticBuf_push(elb, (u8_t *)str_lst_end1, sizeof(TCHAR), errp) == FALSE) ERR_OUT(errp);						// }
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1JsonSpecConstruct_stringify(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecConstruct *spd, Dz1JsonNewLineInfo *nli, bool_t *ret_lf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	switch(spd->type)
	{
	case Dz1JsonConstructType_struct:
		if (Dz1JsonSpecStruct_stringify(env, obj, elb, spd, nli, ret_lf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1JsonConstructType_union:
		if (Dz1JsonSpecUnion_stringify(env, obj, elb, spd, nli, ret_lf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

typedef struct ArrayStringifyArg
{
	Dz1JsonEnv *env;
	Dz1ElasticBuf *elb;
	Dz1JsonSpecEntry *spe;
	Dz1JsonNewLineInfo *nli;
	bool_t is_first;
	bool_t line_feeded;
} ArrayStringifyArg;

#ifndef UNIX_SYSTEM // modified by gm 20230605 - defined but not used, if the func is used, remove the condition
static Dz1Error _Dz1JsonSpecArray_stringify(void *ptr, void *node_obj)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ArrayStringifyArg *arg = (ArrayStringifyArg *)ptr;

	if (_stringify_obj(arg->env, node_obj, arg->elb, arg->spe, arg->nli, &arg->line_feeded, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
#endif // UNIX_SYSTEM
static Dz1Error _Dz1JsonSpecArray_stringify_nl(void *ptr, void *node_obj)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ArrayStringifyArg *arg = (ArrayStringifyArg *)ptr;
	Dz1JsonNewLineInfo *nli = arg->nli;

	if (arg->is_first) 
	{
		arg->is_first = FALSE;
		if (0) { }
		else if (_stringify_tab(arg->elb, nli, errp) == FALSE) ERR_OUT(errp);														// tabs...
		else if (_stringify_obj(arg->env, node_obj, arg->elb, arg->spe, nli, &arg->line_feeded, errp) == FALSE) ERR_OUT(errp);		// {obj}
		else Dz1Error_set(errp, 0);
	}
	else
	{
		if (0) { }
		else if (_Dz1ElasticBuf_push(arg->elb, (u8_t *)str_comma, sizeof(TCHAR) * 1, errp) == FALSE) ERR_OUT(errp);					// ,
		else if (_Dz1ElasticBuf_push(arg->elb, (u8_t *)nli->str, sizeof(TCHAR) * nli->len, errp) == FALSE) ERR_OUT(errp);			// <NL>

		else if (_stringify_tab(arg->elb, nli, errp) == FALSE) ERR_OUT(errp);														// tabs...
		else if (_stringify_obj(arg->env, node_obj, arg->elb, arg->spe, arg->nli, &arg->line_feeded, errp) == FALSE) ERR_OUT(errp);	// {obj}
		else Dz1Error_set(errp, 0);
	}
	arg->line_feeded = FALSE;
	return err;
}

static bool_t Dz1JsonSpecArray_stringify(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecArray *spd, Dz1JsonNewLineInfo *nli, bool_t *ret_lf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t cnt = 0;
	if (obj == NULL || (cnt = spd->count(obj)) == 0)
	{
		if (_Dz1ElasticBuf_push(elb, (u8_t *)str_nul, sizeof(TCHAR) * 4, errp) == FALSE) ERR_OUT(errp);						// null
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1JsonSpecEntry *node_spe = Dz1JsonSpec_findType(env->spec, spd->elem_type);
		if (node_spe == NULL)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! Can't Find type = %s\n", spd->elem_type);
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! JSON Spec = "); Dz1JsonSpec_dump(env->spec, 0);
			ERR_SET_OUT(errp, ENOENT);
		}
		/*
		else if (cnt == 1)
		{	// single element
			Dz1Str blk_start = Dz1Text("[ ");
			Dz1Str blk_end = Dz1Text(" ]");
			if (0) { }
			else if (_Dz1ElasticBuf_push(elb, (u8_t *)blk_start, sizeof(TCHAR) * 2, errp) == FALSE) ERR_OUT(errp);			// [
			else
			{
				ArrayStringifyArg arg = { env, elb, node_spe, nli, TRUE, FALSE };
				if ((*errp = spd->travel(obj, _Dz1JsonSpecArray_stringify, (void *)&arg)).code) ERR_OUT(errp);				// non NL { obj }
				else if (_Dz1ElasticBuf_push(elb, (u8_t *)blk_end, sizeof(TCHAR) * 2, errp) == FALSE) ERR_OUT(errp);		// ] at same line
				else 
				{
					if (arg.line_feeded) *ret_lf = TRUE;
					Dz1Error_set(errp, 0);
				}
			}
		}
		*/
		else
		{
			Dz1Str blk_start = Dz1Text("[");
			Dz1Str blk_end = Dz1Text("]");
			if (_Dz1ElasticBuf_push(elb, (u8_t *)blk_start, sizeof(TCHAR) * 1, errp) == FALSE) ERR_OUT(errp);						// [
			else if (_Dz1ElasticBuf_push(elb, (u8_t *)nli->str, sizeof(TCHAR) * nli->len, errp) == FALSE) ERR_OUT(errp);			// <NL>
			else
			{
				ArrayStringifyArg arg = { env, elb, node_spe, nli, TRUE, FALSE };

				*ret_lf = FALSE;
				nli->tab++;

				if ((*errp = spd->travel(obj, _Dz1JsonSpecArray_stringify_nl, (void *)&arg)).code) ERR_OUT(errp);					// {obj}, {obj}, ...
				else 
				{
//					if (arg.line_feeded) *ret_lf = TRUE;
					nli->tab--;

					if (0) { }
					else if (_Dz1ElasticBuf_push(elb, (u8_t *)nli->str, sizeof(TCHAR) * nli->len, errp) == FALSE) ERR_OUT(errp);	// <NL>
					else if (_stringify_tab(elb, nli, errp) == FALSE) ERR_OUT(errp);												// tabs
					else if (_Dz1ElasticBuf_push(elb, (u8_t *)blk_end, sizeof(TCHAR) * 1, errp) == FALSE) ERR_OUT(errp);			// ]	
					else Dz1Error_set(errp, 0);
				}
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _stringify_obj(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecEntry *spe, Dz1JsonNewLineInfo *nli, bool_t *ret_lf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpecData *spd = NULL;
	if (env == NULL || spe == NULL) 
		ERR_SET_OUT(errp, EINVAL);
	else if (obj == NULL)
	{
		if (_Dz1ElasticBuf_push(elb, (u8_t *)str_nul, sizeof(TCHAR) * 4, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((spd = spe->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		switch(spd->present)
		{
		case Dz1JsonSpecDataPresent_pr:
			if (Dz1JsonSpecPrimitive_stringify(env, obj, elb, spd->x.pr, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1JsonSpecDataPresent_cst:
			if (Dz1JsonSpecConstruct_stringify(env, obj, elb, spd->x.cst, nli, ret_lf, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1JsonSpecDataPresent_ar:
			if (Dz1JsonSpecArray_stringify(env, obj, elb, spd->x.ar, nli, ret_lf, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _stringify_obj_root(Dz1JsonEnv *env, void *obj, Dz1ElasticBuf *elb, Dz1JsonSpecEntry *spe, Dz1JsonNewLineInfo *nli, bool_t *ret_lf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpecData *spd = NULL;
	if (env == NULL || spe == NULL || obj == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((spd = spe->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		*ret_lf = FALSE;
		switch(spd->present)
		{
		case Dz1JsonSpecDataPresent_pr:
//			if (Dz1JsonSpecPrimitive_stringify_root(env, obj, elb, spd->x.pr, errp) == FALSE) ERR_OUT(errp);
			if (Dz1JsonSpecPrimitive_stringify(env, obj, elb, spd->x.pr, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1JsonSpecDataPresent_cst:
			if (Dz1JsonSpecConstruct_stringify(env, obj, elb, spd->x.cst, nli, ret_lf, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1JsonSpecDataPresent_ar:
			if (Dz1JsonSpecArray_stringify(env, obj, elb, spd->x.ar, nli, ret_lf, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Json_stringify(Dz1Json *h, Dz1Str type_name, void *obj, Dz1JsonNewLine nl_mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonEnv *env = (Dz1JsonEnv *)h;
	Dz1JsonSpecEntry *spe = NULL;
	Dz1JsonSpecData *spd = NULL;
	Dz1ElasticBuf *elb = NULL;
	if (env == NULL || Dz1Str_isVoid(type_name) || obj == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((spe = Dz1JsonSpec_findType(env->spec, type_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((spd = spe->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((elb = Dz1ElasticBuf_new(64, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		bool_t line_feeded = FALSE;
		NewLineMap *nl = Dz1Json_stringify_nl(nl_mode);
		Dz1JsonNewLineInfo nli = { nl->str, nl->len, 0 };
		NewLineMap *eof = Dz1Json_stringify_nl(Dz1JsonNewLine_crlf);
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

		if (_stringify_obj_root(env, obj, elb, spe, &nli, &line_feeded, errp) == FALSE) ERR_OUT(errp);
		else if (_Dz1ElasticBuf_push(elb, (u8_t *)eof->str, sizeof(TCHAR) * eof->len, errp) == FALSE) ERR_OUT(errp);
		else if (_convert_charset_push(env->stringify_conv, env->stringify_buf, elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1Json_squeeze(Dz1Json *h, u8_t *buf, size_t sz, Dz1Error *err)
{	// extract data from output buffer of Dz1Json Handle
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	Dz1JsonEnv *env = (Dz1JsonEnv *)h;
	if (env == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (buf == NULL && sz == 0) ret = Dz1ElasticBuf_getDataSize(env->stringify_buf, errp);
	else if (buf == NULL || sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1ElasticBuf_pop(env->stringify_buf, buf, sz, errp)) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

Dz1Str Dz1Json_stringified(Dz1Json *h, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str ret = NULL;
	Dz1JsonEnv *env = (Dz1JsonEnv *)h;
	if (env == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1ElasticBuf_flattenStrAndPurge(env->stringify_buf, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}