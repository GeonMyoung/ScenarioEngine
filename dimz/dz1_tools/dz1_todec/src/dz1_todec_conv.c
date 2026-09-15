#include "dz1_todec.h"

static Dz1Error Dz1TodecStreamList_appendSingleDefault(Dz1TodecStreamList *dst, Dz1Str name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecStreamEntry *node = Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent_single, NULL, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecSingleSource *p = NULL;
		pthread_cleanup_push(Dz1TodecStreamEntry_delAndSetNull, (void *)&node);
		if ((node->x.single = p = Dz1TodecSingleSource_new(name, NULL, Dz1TodecUnitSize_max, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TodecStreamEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error _appendFromStruct(void *ptr, StructMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecStreamList *dst = (Dz1TodecStreamList *)ptr;
	if ((*errp = Dz1TodecStreamList_appendSingleDefault(dst, p->instance)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error Dz1TodecStreamList_appendFromStruct(Dz1TodecStreamList *dst, StructureInfo *info)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StructMemberList *memb = info->members;
	if ((*errp = memb->travel(memb, _appendFromStruct, (void *)dst)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _appendFromUnion(void *ptr, UnionMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecStreamList *dst = (Dz1TodecStreamList *)ptr;
	if ((*errp = Dz1TodecStreamList_appendSingleDefault(dst, p->instance)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error Dz1TodecStreamList_appendFromUnion(Dz1TodecStreamList *dst, UnionInfo *info)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	UnionMemberList *memb = info->members;
	if ((*errp = memb->travel(memb, _appendFromUnion, (void *)dst)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1TodecTargetCodecEntry *Dz1TodecTargetCodecEntry_genFromObj(ObjectInfo *tgt, ObjectInfo *ori, Dz1TodecTargetCodecMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TodecTargetCodecEntry *ret = Dz1TodecTargetCodecEntry_new(NULL, mode, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1TodecTargetCodecAttr *attr = NULL;
		pthread_cleanup_push(Dz1TodecTargetCodecEntry_delAndSetNull, (void *)&ret);
		switch(ori->type)
		{
		case ObjectType_array:
		case ObjectType_index:
			if ((ret->attr = attr = Dz1TodecTargetCodecAttr_new(Dz1TodecTargetCodecAttrPresent_ar, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1TodecTargetCodecAttrArray *ar = NULL;
				if ((attr->x.ar = ar = Dz1TodecTargetCodecAttrArray_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((ar->cnt = Dz1TodecTargetCodecAttrDescr_new(Dz1TodecTargetCodecAttrDescrPresent_def, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((ar->body = Dz1TodecTargetCodecAttrDescr_new(Dz1TodecTargetCodecAttrDescrPresent_def, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			break;
		case ObjectType_structure:
			if ((ret->attr = attr = Dz1TodecTargetCodecAttr_new(Dz1TodecTargetCodecAttrPresent_st, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = Dz1TodecStreamList_appendFromStruct(ret->seq, (StructureInfo *)ori->info)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case ObjectType_union:
			if ((ret->attr = attr = Dz1TodecTargetCodecAttr_new(Dz1TodecTargetCodecAttrPresent_un, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1TodecTargetCodecAttrUnion *un = NULL;
				if ((attr->x.un = un = Dz1TodecTargetCodecAttrUnion_new(NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((un->pr = Dz1TodecTargetCodecAttrDescr_new(Dz1TodecTargetCodecAttrDescrPresent_def, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((*errp = Dz1TodecStreamList_appendFromUnion(ret->seq, (UnionInfo *)ori->info)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			break;
		default:
			break;
		}
		pthread_cleanup_pop(errp->code); // (Dz1TodecTargetCodecEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error Dz1TodecTarget_addDefaultCodec(Dz1TodecTarget *dst, ObjectInfo *tgt, ObjectInfo *ori, Dz1TodecTargetCodecMode mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecTargetCodecEntry *node = Dz1TodecTargetCodecEntry_genFromObj(tgt, ori, mode, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTargetCodecEntry_delAndSetNull, (void *)&node);
		if ((*errp = dst->codecs->add(dst->codecs, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TodecTargetCodecEntry_delAndSetNull, (voi d*)&node);
	}
	return err;
}

static Dz1TodecTarget *Dz1TodecTarget_convFromObj(ObjectInfo *tgt, ObjectInfo *ori, Dz1TodecTargetCodecMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TodecTarget *ret = NULL;
	if (tgt == NULL || ori == NULL) ERR_OUT(errp);
	else if ((ret = Dz1TodecTarget_new(tgt->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTarget_delAndSetNull, (void *)&ret);
		if ((*errp = Dz1TodecTarget_addDefaultCodec(ret, tgt, ori, mode)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TodecTarget_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error Dz1Todec_convFromObj(Dz1Todec *dst, ObjectInfo *src, ObjectInfo *ori, Dz1TodecTargetCodecMode mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecTarget *tgt = Dz1TodecTarget_convFromObj(src, ori, mode, errp);
	if (tgt == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecTarget_delAndSetNull, (void *)&tgt);
		if ((*errp = Dz1Todec_addTarget(dst, tgt)).code) ERR_OUT(errp);
		else
		{
			tgt = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TodecTarget_delAndSetNull, (void *)&tgt);
	}
	return err;
}

static Dz1Error Dz1Todec_convObj(Dz1Todec *dst, ObjectInfo *src, Dz1TodecTargetCodecMode mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *ori = ObjectInfo_getOrigin(src);
	switch(ori->type)
	{
	case ObjectType_array:
	case ObjectType_index:
	case ObjectType_structure:
	case ObjectType_union:
		if ((*errp = Dz1Todec_convFromObj(dst, src, ori, mode)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Error_set(errp, 0);
		break;
	}
	return err;
}

typedef struct TodecConvArg
{
	Dz1Todec				*dst;
	Dz1TodecTargetCodecMode  mode;
	str_t					 suffix;
} TodecConvArg;

static Dz1Error _Dz1Todec_inc_conv(void *ptr, void *_dp)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	TodecConvArg *arg = (TodecConvArg *)ptr;
	Dz1Todec *dst = arg->dst;

	Dz1MdefcModule *p = (Dz1MdefcModule *)_dp;

	char name[1024], *bn = strrchr(p->name, DIR_SEP);
	if (bn == NULL) bn = p->name; else bn++;
	strcpy(name, bn);
	strcat(name, arg->suffix);

	Dz1Thread_printf("@@@ include convert = %s\n", name);
	if ((*errp = Dz1TodecInclude_append(dst->incl, name)).code)
	{
		if (errp->code != EEXIST) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	return err;
}

static Dz1Error _Dz1Todec_obj_conv(void *ptr, void *_dp)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	TodecConvArg *arg = (TodecConvArg *)ptr;
	Dz1Todec *dst = arg->dst;
	ObjectInfo *p = (ObjectInfo *)_dp;
	if ((*errp = Dz1Todec_convObj(dst, p, arg->mode)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Todec *Dz1Todec_conv(Dz1MdefcModule *src, str_t suffix, Dz1TodecTargetCodecMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Todec *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1Todec_new(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TodecConvArg arg = { ret, mode, suffix };
		pthread_cleanup_push(Dz1Todec_delAndSetNull, (void *)&ret);
		if ((*errp = Dz1AATree_travel(src->moduleTree, _Dz1Todec_inc_conv, (void *)&arg)).code) ERR_OUT(errp);
		if ((*errp = Dz1Fifo_travel(src->objFifo, _Dz1Todec_obj_conv, (void *)&arg)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code);//(Dz1Todec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1Todec_convert(Dz1Str mod_path, Dz1Str mod_name, Dz1TodecTargetCodecMode mode, Dz1Str out_path, Dz1Str oSuffix, Dz1Str iSuffix)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcModule *mod = Dz1MdefcModule_load3(mod_path, mod_name, "tdo", errp);
	if (mod == NULL) ERR_OUT(errp);
	else
	{
		Dz1Todec *todec = NULL;
		pthread_cleanup_push(Dz1MdefcModule_delAndSetNull, (void *)&mod);
		if ((todec = Dz1Todec_conv(mod, iSuffix, mode, errp)) == NULL) ERR_OUT(errp);
		else
		{
			FILE *fp = NULL;
			char out_name_ext[1024];
			pthread_cleanup_push(Dz1Todec_delAndSetNull, (void *)&todec);

			strcpy(out_name_ext, mod_name);
			strcat(out_name_ext, oSuffix);
			strcat(out_name_ext, ".todec");

			if ((fp = Dz1FileStream_open2(out_path, out_name_ext, "wb", errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
				if ((*errp = Dz1Todec_gen_src(fp, todec, mod)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
			}
			pthread_cleanup_pop(1); // (Dz1Todec_delAndSetNull, (void *)&todec);
		}
		pthread_cleanup_pop(1); // (Dz1MdefcModule_delAndSetNull, (void *)&mod);
	}
	return err;
}
