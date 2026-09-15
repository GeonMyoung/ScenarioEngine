#include "dz1_todec.h"

///////////////////////////////////////////////////////////////////////////////
// Pseudo Object Info
static PrimitiveInfo pseudo_prim_data_inf =
{
	"u32_t",
	NativeStorage_data,
	"u32_t"
};

static ObjectInfo _pseudo_obj_u32 = 
{
	ObjectType_primitive,
	"pseudo_32",
	NULL,
	0,
	&pseudo_prim_data_inf
};
ObjectInfo *pseudo_obj_u32 = &_pseudo_obj_u32;

static PrimitiveInfo pseudo_prim_void_inf =
{
	"void",
	NativeStorage_none,
	"void"
};


static ObjectInfo _pseudo_obj_void = 
{
	ObjectType_primitive,
	"pseudo_void",
	NULL,
	0,
	&pseudo_prim_void_inf
};
ObjectInfo *pseudo_obj_void = &_pseudo_obj_void;
// Pseudo Object Info
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Append Pointer Node
static Dz1Error PointerNodeList_append(PointerNodeList *dst, ObjectInfo *obj, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || name == NULL || name[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t cnt = dst->count(dst);
		PointerNodeEntry *node = PointerNodeEntry_new(cnt, obj, name, errp);
		if (node == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(PointerNodeEntry_delAndSetNull, (void *)&node);
			if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (PointerNodeEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}
// Append Pointer Node
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Child Resolver
static ObjectInfo *_structure_child_obj(ObjectInfo *obj, str_t name, bool_t *ret_is_ptr, Dz1Error *err)
{
	ObjectInfo *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	StructureInfo *info = (StructureInfo *)obj->info;
	StructMemberList *members = info->members;
	StructMemberEntry *memb = members->find(members, name);
	if (memb == NULL)
	{
		Dz1Thread_printf("!!! No such member [%s] on %s\n", name, obj->name);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		ret = memb->type;
		(*ret_is_ptr) = memb->isPointer;
	}
	return ret;
}

static ObjectInfo *_union_child_obj(ObjectInfo *obj, str_t name, bool_t *ret_is_ptr, Dz1Error *err)
{
	ObjectInfo *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (strcmp(name, PSEUDO_NAME_PRESENT) == 0)
	{
		*ret_is_ptr = FALSE;
		ret = pseudo_obj_u32;
	}
	else if (strcmp(name, PSEUDO_NAME_SWITCHED) == 0)
	{
		*ret_is_ptr = TRUE;
		ret = pseudo_obj_void;
	}
	else
	{
		UnionInfo *info = (UnionInfo *)obj->info;
		UnionMemberList *members = info->members;
		UnionMemberEntry *memb = members->find(members, name);
		if (memb == NULL)
		{
			Dz1Thread_printf(Dz1T("!!! member '%s' is not exist\n"), name);
			Dz1Thread_printf(Dz1T("!!! in ")); ObjectInfo_dump(obj, 0);
			ERR_SET_OUT(errp, ENOENT);
		}
		else
		{
			ret = memb->type;
			(*ret_is_ptr) = memb->isPointer;
		}
	}
	return ret;
}

static ObjectInfo *_array_child_obj(ObjectInfo *obj, str_t name, bool_t *ret_is_ptr, Dz1Error *err)
{
	ObjectInfo *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (strcmp(name, PSEUDO_NAME_COUNT) == 0)
	{
		*ret_is_ptr = FALSE;
		ret = pseudo_obj_u32;
	}
	else if (strcmp(name, PSEUDO_NAME_BODY) == 0)
	{
		*ret_is_ptr = TRUE;
		ret = pseudo_obj_void;
	}
	else ERR_SET_OUT(errp, ENOENT);
	return ret;
}

static ObjectInfo *_resolve_child_obj(ObjectInfo *parent_obj, str_t child_name, bool_t *ret_is_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	bool_t _is_ptr = FALSE, *is_ptr = ret_is_ptr != NULL ? ret_is_ptr : &_is_ptr;
	switch(parent_obj->type)
	{
	case ObjectType_structure:	return _structure_child_obj(parent_obj, child_name, is_ptr, errp);
	case ObjectType_union:		return _union_child_obj(parent_obj, child_name, is_ptr, errp);
	case ObjectType_array:
	case ObjectType_index:		return _array_child_obj(parent_obj, child_name, is_ptr, errp);
	default: ERR_SET_OUT(errp, EINVAL); return NULL;
	}
}
// Child Resolver
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Build-up Stream Element Variable
// typedef struct FillUpEnv
// {
// 	char			*name;
// 	size_t			 name_sz;
// 	void			*target_descr;
// } FillUpEnv;

static ssize_t _parse_name(char *dst, size_t dst_sz, str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (src == NULL || src[0] == 0) return 0;
	else if (dst == NULL || dst_sz == 0) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		ssize_t ret = 0;
		char *cp = src, *dp = dst;

		while(*cp && *cp != '.' && dst_sz > 0) { *dp++ = *cp++; dst_sz--; ret++;}
		if (dst_sz == 0) ERR_SET_OUT_RET(errp, ENOMEM, -1); else *dp++ = 0;

		if (*cp == '.') { cp++; ret++; }
		return ret;
	}
}

ssize_t _var_fill_up_from_string(StreamElementVariable *dst, str_t name, ObjectInfo *parent_obj_ori, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t sz, ret = 0;

	size_t var_sz = 2048;
	char *cp = name, buf[1024], var_name[2048] = { 0 };

	ObjectInfo *parent_obj = parent_obj_ori;
	ObjectInfo *child_obj = NULL, *child_ori = NULL;
	bool_t child_is_ptr = FALSE;

	while((sz = _parse_name(buf, 1024, cp, errp)) > 0)
	{
		cp += sz;
		if ((child_obj = _resolve_child_obj(parent_obj, buf, &child_is_ptr, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else if ((child_ori = ObjectInfo_getOrigin(child_obj)) == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
		else
		{
			if (parent_obj->type == ObjectType_union)
			{
				if (var_sz > 2)
				{
					strcat(var_name, "x.");
					var_sz -= 2;
					ret += 2;
				} 
				else ERR_SET_OUT_RET(errp, ENOMEM, -1);
			}

			if (var_sz > (size_t)sz)
			{
				strcat(var_name, buf);
				var_sz -= sz;
				ret += sz;
			} 
			else ERR_SET_OUT_RET(errp, ENOMEM, -1);

			if (*cp == 0)
			{	// last symbol
				dst->target = child_obj;
				dst->origin = child_ori;
				dst->var_is_ptr = child_is_ptr;

				if ((dst->variable = Dz1Str_dup(var_name, errp)) == NULL) ERR_OUT_RET(errp, -1);
				else if ((dst->instance = Dz1Str_dup(buf, errp)) == NULL) ERR_OUT_RET(errp, -1);
				else Dz1Error_set(errp, 0);

				break;
			}
			else if (child_is_ptr)
			{
				if ((*errp = PointerNodeList_append(dst->ptrs, child_obj, var_name)).code) ERR_OUT_RET(errp, -1);
				else if (var_sz <= 2) ERR_SET_OUT_RET(errp, ENOMEM, -1);
				else
				{
					strcat(var_name, "->");
					var_sz -= 2; 
					ret += 2;
					Dz1Error_set(errp, 0);
				}
			}
			else if (var_sz <= 1) ERR_SET_OUT_RET(errp, ENOMEM, -1);
			else
			{
				strcat(var_name, ".");
				var_sz -= 1;
				ret += 1;
				Dz1Error_set(errp, 0);
			}
		}
		parent_obj = child_obj;
		child_obj = child_ori = NULL;
	}
	return ret;
}

static StreamElementVariable *StreamElementVariable_genFromSingle(/*Dz1TodecSingleSource *p*/ str_t memb_name, ObjectInfo *parent_obj_ori, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementVariable *ret = StreamElementVariable_new(NULL, NULL, parent_obj_ori, NULL, FALSE, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamElementVariable_delAndSetNull, (void *)&ret);

		if (_var_fill_up_from_string(ret, memb_name, parent_obj_ori, errp) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (StreamElementVariable_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Build-up Stream Element Variable
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Size-Type-Mask Mapper
typedef struct SizedTypeAndMask
{
	Dz1TodecUnitSize		sz;
	str_t					tp;
	str_t					mask;
} SizedTypeAndMask;

static SizedTypeAndMask sizedTypeAndMask[] =
{
	{ Dz1TodecUnitSize_Byte1, "u8_t",  "0xFF" },
	{ Dz1TodecUnitSize_Byte2, "u16_t", "0xFFFF" },
	{ Dz1TodecUnitSize_Byte4, "u32_t", "0xFFFFFFFF" },
	{ Dz1TodecUnitSize_Byte8, "u64_t", "0xFFFFFFFFFFFFFFFF" },
	{ Dz1TodecUnitSize_max }
};

static SizedTypeAndMask *SizedTypeAndMask_find(Dz1TodecUnitSize sz)
{
	SizedTypeAndMask *i;
	for (i = sizedTypeAndMask; i->sz != Dz1TodecUnitSize_max; i++)
		if (i->sz == sz) return i;
	return NULL;
}
// Size-Type-Mask Mapper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 1:1 Method Converter
// static s32_t _calc_shf(Dz1TodecByteDescr *descr, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	s32_t shf = 0, total_b = descr->cast_size * 8;
// 	if (descr->origin == Dz1TodecOrigin_MSB) 
// 	{	// 0 1 2 3
// 		s32_t pos_offset_b = descr->byte_num * 8;
// 		shf = total_b - pos_offset_b - (descr->byte_size * 8);
// 	}
// 	else if (descr->origin == Dz1TodecOrigin_LSB)
// 	{	// 3 2 1 0
// 		s32_t pos_offset_b = (descr->cast_size - descr->byte_num) * 8;
// 		shf = total_b - pos_offset_b - (descr->byte_size * 8);
// 	}
// 	else ERR_SET_OUT_RET(errp, EINVAL, -1);
// 	return shf;
// }

static StreamElementSimplePartial *StreamElementSimplePartial_generate(Dz1TodecByteDescr *descr, str_t dst_tp, 
																	   u32_t *r_flag, u32_t *w_flag, Dz1Error *err)
{	// (dst_tp)((@@@ >> shf) & mask) <-> ((src_tp)$$$ & mask) << shf)
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementSimplePartial *ret = NULL;

	s32_t shf = 0;
	SizedTypeAndMask *ou = NULL;

	if (descr == NULL || dst_tp == NULL || dst_tp[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ou = SizedTypeAndMask_find(descr->byte_take)) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = StreamElementSimplePartial_new(ou->tp, descr->byte_take, dst_tp, ou->mask, shf, errp)) == NULL) ERR_OUT(errp);
	else
	{
		(*r_flag) |= descr->byte_take;
		Dz1Error_set(errp, 0);
	}

	return ret;
}

static StreamElementSimpleMethod *StreamElementSimpleMethod_generate(Dz1TodecSingleDescr *descr, ObjectInfo *tgt, u32_t *r_flag, u32_t *w_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementSimpleMethod *ret = StreamElementSimpleMethod_new(StreamElementSimpleMethodPresent_def, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamElementSimpleMethod_delAndSetNull, (void *)&ret);
		if (descr != NULL)
		{
			switch(descr->present)
			{
			case Dz1TodecSingleDescrPresent_partial_byte:
				ret->present = StreamElementSimpleMethodPresent_part;
				if ((ret->x.part = StreamElementSimplePartial_generate(descr->x.partial_byte, tgt->name, r_flag, w_flag, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1TodecSingleDescrPresent_restricted:
				ret->present = StreamElementSimpleMethodPresent_restricted;
				if ((ret->x.restricted = Dz1TodecRestrictDescr_clone(descr->x.restricted, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1TodecSingleDescrPresent_alter_codec:
				ret->present = StreamElementSimpleMethodPresent_alter;
				if ((ret->x.alter = Dz1Str_dup(descr->x.alter_codec, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			default:
				ERR_SET_OUT(errp, EFAULT);
				break;
			}
		}
		else
		{
			ObjectInfo *ori = ObjectInfo_getOrigin(tgt);
			if (ori->type == ObjectType_enumerate)
				(*r_flag) |= Dz1TodecUnitSize_Byte4;
			else if (ori->type == ObjectType_primitive)
			{
				PrimitiveInfo *info = (PrimitiveInfo *)ori->info;
				Dz1TodecUnitSize sz = _resolve_prim_size(info, NULL);
				if (info->storage == NativeStorage_data && sz == Dz1TodecUnitSize_max) 
				{
					(*w_flag) |= Dz1TodecUnitSize_Byte4;
					(*r_flag) |= Dz1TodecUnitSize_Byte4;
				}
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (StreamElementSimpleMethod_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// 1:1 Method Converter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 1:1 Element Converter 
static StreamElementSimple *StreamElementSimple_generate(Dz1TodecSingleSource *p, ObjectInfo *parent_obj_ori, u32_t *r_flag, u32_t *w_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementSimple *ret = StreamElementSimple_new(NULL, NULL, p->nul_flag, p->postfix, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
//		char name[2048] = { 0, };
		StreamElementVariable *var = NULL;

		pthread_cleanup_push(StreamElementSimple_delAndSetNull, (void *)&ret);

		if (p->nul_flag != Dz1TodecUnitSize_max) (*r_flag) |= p->nul_flag;

		if ((ret->var = var = StreamElementVariable_genFromSingle(p->src_name, parent_obj_ori, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->met = StreamElementSimpleMethod_generate(p->src_descr, var->target, r_flag, w_flag, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (StreamElementSimple_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// 1:1 Element Converter 
///////////////////////////////////////////////////////////////////////////////

static StreamElementConditional *StreamElementConditional_generate(Dz1TodecConditionalSource *p, ObjectInfo *parent_obj_ori, u32_t *r_flag, u32_t *w_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementConditional *ret = StreamElementConditional_new(NULL, p->decider, NULL, p->postfix, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		StreamElementVariable *var = NULL;

		pthread_cleanup_push(StreamElementSimple_delAndSetNull, (void *)&ret);

		if ((ret->var = var = StreamElementVariable_genFromSingle(p->src_name, parent_obj_ori, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->met = StreamElementSimpleMethod_generate(p->src_descr, var->target, r_flag, w_flag, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (StreamElementSimple_delAndSetNull, (void *)&ret);
	}
	return ret;
}
///////////////////////////////////////////////////////////////////////////////
// Resolve Target Object & name from Bits
// ssize_t _fill_up_fromBunch(StreamElementVariable *dst, Dz1TodecBunchDataEntry *p, ObjectInfo *parent_obj_ori, FillUpEnv *env, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ssize_t ret = 0;
// 	bool_t child_is_ptr = FALSE;
// 	ObjectInfo *child_obj = _resolve_child_obj(parent_obj_ori, p->src_name, &child_is_ptr, errp);
// 	if (child_obj == NULL) ERR_OUT_RET(errp, -1);
// 	else
// 	{
// 		ssize_t len = (ssize_t)strlen(p->src_name);
// 		Dz1TodecBunchEntryDescr *descr = p->src_descr;
// 		if (env->name_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, -1); else
// 		{
// 			strcat(env->name, p->src_name);
// 			env->name_sz -= len;
// 			ret += len;
// 		}
// 
// 		if (descr != NULL && descr->present == Dz1TodecBunchEntryDescrPresent_nested)
// 		{
// 			if (child_is_ptr)
// 			{
// 				if ((*errp = PointerNodeList_append(dst->ptrs, child_obj, env->name)).code) ERR_OUT_RET(errp, -1);
// 				else if (env->name_sz <= 2) ERR_SET_OUT_RET(errp, E2BIG, -1);
// 				else
// 				{
// 					strcat(env->name, "->");
// 					env->name_sz -= 2;
// 					ret += 2;
// 				}
// 			}
// 			else if (env->name_sz <= 1) ERR_SET_OUT_RET(errp, E2BIG, -1);
// 			else
// 			{
// 				strcat(env->name, ".");
// 				env->name_sz -= 1;
// 				ret += 1;
// 			}
// 
// 			if ((len = _fill_up_fromBunch(dst, descr->x.nested, ObjectInfo_getOrigin(child_obj), env, errp)) < 0) ERR_OUT_RET(errp, -1);
// 			else { env->name_sz -= len; ret += len; }
// 		}
// 		else
// 		{
// 			env->target_descr = descr == NULL ? NULL : descr->x.partial_bits;
// 
// 			dst->target = child_obj;
// 			dst->origin = ObjectInfo_getOrigin(dst->target);
// 			dst->mother = parent_obj_ori;
// 			dst->var_is_ptr = child_is_ptr;
// 
// 			if ((dst->variable = Dz1Str_dup(env->name, errp)) == NULL) ERR_OUT_RET(errp, -1);
// 			else Dz1Error_set(errp, 0);
// 		}
// 	}
// 	return ret;
// }

static StreamElementVariable *StreamElementVariable_genFromBunch(Dz1TodecBunchDataEntry *p, ObjectInfo *parent_obj_ori, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementVariable *ret = StreamElementVariable_new(NULL, NULL, NULL, NULL, FALSE, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamElementVariable_delAndSetNull, (void *)&ret);
		if (_var_fill_up_from_string(ret, p->src_name, parent_obj_ori, errp) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (StreamElementVariable_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Resolve Target Object & name from Bits
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 1:n Converter : BitInfo from BunchDataEntry
static Dz1TodecBitDescr *Dz1TodecBitDescr_generate(Dz1TodecBitDescr *p, ObjectInfo *obj, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TodecBitDescr *ret = Dz1TodecBitDescr_clone(p, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static StreamElementBitInfo *StreamElementBitInfo_generate(Dz1TodecBunchDataEntry *p, ObjectInfo *obj, Dz1Error *err)
{	// %%% |= ((out_tp)((@@@ >> shf) & mask) << pos) <-> $$$ = (dst_tp)((%%% >> pos) & mask) << shf)
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementBitInfo *ret = StreamElementBitInfo_new(NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
//		char name[2048] = { 0, };
//		FillUpEnv env = { name, 2048, NULL };
		StreamElementVariable *var = NULL;
		pthread_cleanup_push(StreamElementBitInfo_delAndSetNull, (void *)&ret);
		if ((ret->var = var = StreamElementVariable_genFromBunch(p, obj, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->met = Dz1TodecBitDescr_generate(p->src_descr, var->target, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (StreamElementBitInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static StreamElementBit *StreamElementBit_generate(Dz1TodecBunchEntry *p, ObjectInfo *obj, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementBit *ret = NULL;
	switch(p->present)
	{
	case Dz1TodecBunchEntryPresent_data_bits:
		if ((ret = StreamElementBit_new(StreamElementBitPresent_data, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamElementBit_delAndSetNull, (void *)&ret);
			if ((ret->x.data = StreamElementBitInfo_generate(p->x.data_bits, obj, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (StreamElementBit_delAndSetNull, (void *)&ret);
		}
		break;
	case Dz1TodecBunchEntryPresent_pad_bits:
		if ((ret = StreamElementBit_new(StreamElementBitPresent_pad, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->x.pad = p->x.pad_bits;
			Dz1Error_set(errp, 0);
		}
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return ret;
}
// 1:n Converter : BitInfo from BunchDataEntry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 1:n Converter : Complex from BunchOfSource
static StreamElementComplex *StreamElementComplex_generate(Dz1TodecBunchOfSource *p, ObjectInfo *obj, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementComplex *ret = NULL;
	if ((ret = StreamElementComplex_new(p->target_sz, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t cnt = 0;
		Dz1TodecBunchEntry **arr = NULL;
		pthread_cleanup_push(StreamElementComplex_delAndSetNull, (void *)&ret);

		if ((arr = p->seq->get_array(p->seq, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			StreamElementBits *dst = ret->seq;
			StreamElementBit *node = NULL;

			u32_t i;
			Dz1TodecBunchEntry *e = NULL;

			pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
			for (i = 0; i < cnt; i++)
			{
				e = arr[i];
				if ((node = StreamElementBit_generate(e, obj, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(StreamElementBit_delAndSetNull, (void *)&node);
					if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
					else
					{
						node = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (StreamElementBit_delAndSetNull, (void *)&node);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
		}
		pthread_cleanup_pop(errp->code); // (StreamElementComplex_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// 1:n Converter : Complex from BunchOfSource
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Element Converter
static StreamElementInfo *StreamElementInfo_generate(Dz1TodecStreamEntry *e, ObjectInfo *ori, u32_t *r_flag, u32_t *w_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementInfo *node = NULL;
	switch(e->present)
	{
	case Dz1TodecStreamEntryPresent_bunch:
		if ((node = StreamElementInfo_new(StreamElementInfoPresent_complex, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamElementInfo_delAndSetNull, (void *)&node);

			if ((node->x.complex = StreamElementComplex_generate(e->x.bunch, ori, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (StreamElementInfo_delAndSetNull, (void *)&node);
		}
		break;
	case Dz1TodecStreamEntryPresent_single:
		if ((node = StreamElementInfo_new(StreamElementInfoPresent_simple, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamElementInfo_delAndSetNull, (void *)&node);

			if ((node->x.simple = StreamElementSimple_generate(e->x.single, ori, r_flag, w_flag, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (StreamElementInfo_delAndSetNull, (void *)&node);
		}
		break;
	case Dz1TodecStreamEntryPresent_conditional:
		if ((node = StreamElementInfo_new(StreamElementInfoPresent_conditional, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamElementInfo_delAndSetNull, (void *)&node);

			if ((node->x.conditional = StreamElementConditional_generate(e->x.conditional, ori, r_flag, w_flag, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (StreamElementInfo_delAndSetNull, (void *)&node);
		}
		break;
	case Dz1TodecStreamEntryPresent_pad:
		if ((node = StreamElementInfo_new(StreamElementInfoPresent_pad, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			node->x.pad = e->x.pad;
			Dz1Error_set(errp, 0);
		}
		break;
	case Dz1TodecStreamEntryPresent_value:
		if ((node = StreamElementInfo_new( StreamElementInfoPresent_value, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(StreamElementInfo_delAndSetNull, (void *)&node);

			if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(e->x.value, errp)) == NULL) ERR_OUT(errp);
			else if ((node->x.value = Dz1Binary_clone(bin, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (StreamElementInfo_delAndSetNull, (void *)&node);
		}
		break;
	case Dz1TodecStreamEntryPresent_omit:
		if ((node = StreamElementInfo_new(StreamElementInfoPresent_omit, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamElementInfo_delAndSetNull, (void *)&node);

			if ((node->x.omit = StreamElementVariable_genFromSingle(e->x.omit, ori, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (StreamElementInfo_delAndSetNull, (void *)&node->x.omit);
		}
		break;
	default:
		Dz1Thread_printf("!!! cause = "); Dz1TodecStreamEntry_dump(e, 0);
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return node;
}
// Element Converter
///////////////////////////////////////////////////////////////////////////////

/*
static StreamElementSimpleMethod *StreamElementSimpleMethod_genFromAttrDescr(Dz1TodecTargetCodecAttrDescr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamElementSimpleMethod *ret = NULL;

	if ((ret = StreamElementSimpleMethod_new(StreamElementSimpleMethodPresent_def, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamElementSimpleMethod_delAndSetNull, (void *)&ret);
		pthread_cleanup_pop(errp->code); // (StreamElementSimpleMethod_delAndSetNull, (void *)&ret);
	}
	return ret;
}
*/

static Dz1Error StreamElementSimple_setFromAttrDescr(StreamElementSimple **dst, Dz1TodecTargetCodecAttrDescr *src,
													 ObjectInfo *tgt, ObjectInfo *obj, str_t name, bool_t is_ptr,
													 u32_t *r_flag, u32_t *w_flag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StreamElementSimple *p = NULL;
	StreamElementSimpleMethod *met = NULL;
	switch(src->present)
	{
	case Dz1TodecTargetCodecAttrDescrPresent_omit:
		StreamElementSimple_delAndSetNull(dst);
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_def:
		if (( (*dst) = p = StreamElementSimple_new(NULL, NULL, Dz1TodecUnitSize_max, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamElementSimple_delAndSetNull, (void *)dst);
			if ((p->var = StreamElementVariable_new(tgt, ObjectInfo_getOrigin(tgt), obj, name, is_ptr, name, errp)) == NULL) ERR_OUT(errp);
			else if ((p->met = StreamElementSimpleMethod_new(StreamElementSimpleMethodPresent_def, NULL, errp)) == NULL) ERR_OUT(errp);
			else 
			{
				if (r_flag) *r_flag |= Dz1TodecUnitSize_Byte4;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (StreamElementSimple_delAndSetNull, (void *)dst);
		}
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_partial_byte:
		if (( (*dst) = p = StreamElementSimple_new(NULL, NULL, Dz1TodecUnitSize_max, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamElementSimple_delAndSetNull, (void *)dst);
			if ((p->var = StreamElementVariable_new(tgt, ObjectInfo_getOrigin(tgt), obj, name, is_ptr, name, errp)) == NULL) ERR_OUT(errp);
			else if ((p->met = met = StreamElementSimpleMethod_new(StreamElementSimpleMethodPresent_part, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((met->x.part = StreamElementSimplePartial_generate(src->x.partial_byte, tgt->name, r_flag, w_flag, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (StreamElementSimple_delAndSetNull, (void *)dst);
		}
		break;
	case Dz1TodecTargetCodecAttrDescrPresent_alter_codec:
		if (( (*dst) = p = StreamElementSimple_new(NULL, NULL, Dz1TodecUnitSize_max, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamElementSimple_delAndSetNull, (void *)dst);
			if ((p->var = StreamElementVariable_new(tgt, ObjectInfo_getOrigin(tgt), obj, name, is_ptr, name, errp)) == NULL) ERR_OUT(errp);
			else if ((p->met = met = StreamElementSimpleMethod_new(StreamElementSimpleMethodPresent_alter, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((met->x.alter = Dz1Str_dup(src->x.alter_codec, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (StreamElementSimple_delAndSetNull, (void *)dst);
		}
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return err;
}

static StreamObjectAttrArray *StreamObjectAttrArray_generate(Dz1TodecTargetCodecAttrArray *src, ObjectInfo *etr, ObjectInfo *array_ori, u32_t *r_flag, u32_t *w_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamObjectAttrArray *ret = NULL;
	if ((ret = StreamObjectAttrArray_new(NULL, NULL, src->postfix, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamObjectAttrArray_delAndSetNull, (void *)&ret);
		if ((*errp = StreamElementSimple_setFromAttrDescr(&ret->cnt, src->cnt, pseudo_obj_u32, NULL, "cnt", FALSE, r_flag, w_flag)).code) ERR_OUT(errp);
		else if ((*errp = StreamElementSimple_setFromAttrDescr(&ret->etr, src->body, etr, NULL, "node", TRUE, r_flag, w_flag)).code) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (StreamObjectAttrArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static StreamObjectAttrUnion *StreamObjectAttrUnion_generate(Dz1TodecTargetCodecAttrUnion *src, ObjectInfo *union_ori, u32_t *r_flag, u32_t *w_flag, Dz1MdefcModule *module, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamObjectAttrUnion *ret = NULL;
	if ((ret = StreamObjectAttrUnion_new(NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char temp[1024];
		ObjectInfo *present_obj = NULL;
		pthread_cleanup_push(StreamObjectAttrArray_delAndSetNull, (void *)&ret);

		strcpy(temp, union_ori->name);
		strcat(temp, "Present");
		if ((present_obj = module->findObject(module, temp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((*errp = StreamElementSimple_setFromAttrDescr(&ret->pr, src->pr, present_obj, union_ori, "present", FALSE, r_flag, w_flag)).code) ERR_OUT(errp);
		else
		{
		//	if (ret->pr != NULL) (*r_flag) |= Dz1TodecUnitSize_Byte4;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (StreamObjectAttrArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static StreamObjectAttr *Dz1TodecTargetCodecAttr_analysis(Dz1TodecTargetCodecAttr *attr, ObjectInfo *obj,
														  u32_t *r_flag, u32_t *w_flag, 
														  Dz1MdefcModule *module, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamObjectAttr *ret = NULL;
	if (obj->type == ObjectType_array)
	{
		ArrayInfo *info = (ArrayInfo *)obj->info;
		if (attr->present != Dz1TodecTargetCodecAttrPresent_ar) ERR_SET_OUT(errp, EINVAL);
		else if ((ret = StreamObjectAttr_new(StreamObjectAttrPresent_ar, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamObjectAttr_delAndSetNull, (void *)&ret);
			if ((ret->x.ar = StreamObjectAttrArray_generate(attr->x.ar, info->entry, obj, r_flag, w_flag, errp)) == NULL) ERR_OUT(errp);
			pthread_cleanup_pop(errp->code); // (StreamObjectAttr_delAndSetNull, (void *)&ret);
		}
	}
	else if (obj->type == ObjectType_index)
	{
		IndexInfo *info = (IndexInfo *)obj->info;
		if (attr->present != Dz1TodecTargetCodecAttrPresent_ar) ERR_SET_OUT(errp, EINVAL);
		else if ((ret = StreamObjectAttr_new(StreamObjectAttrPresent_ar, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamObjectAttr_delAndSetNull, (void *)&ret);
			if ((ret->x.ar = StreamObjectAttrArray_generate(attr->x.ar, info->entry, obj, r_flag, w_flag, errp)) == NULL) ERR_OUT(errp);
			pthread_cleanup_pop(errp->code); // (StreamObjectAttr_delAndSetNull, (void *)&ret);
		}
	}
	else if (obj->type == ObjectType_structure)
	{
		if (attr == NULL)
		{
			if ((ret = StreamObjectAttr_new(StreamObjectAttrPresent_st, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (attr->present != Dz1TodecTargetCodecAttrPresent_st) ERR_SET_OUT(errp, EINVAL);
		else if ((ret = StreamObjectAttr_new(StreamObjectAttrPresent_st, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (obj->type == ObjectType_union)
	{
		if (attr->present != Dz1TodecTargetCodecAttrPresent_un) ERR_SET_OUT(errp, EINVAL);
		else if ((ret = StreamObjectAttr_new(StreamObjectAttrPresent_un, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(StreamObjectAttr_delAndSetNull, (void *)&ret);
			if ((ret->x.un = StreamObjectAttrUnion_generate(attr->x.un, obj, r_flag, w_flag, module, errp)) == NULL) ERR_OUT(errp);
			pthread_cleanup_pop(errp->code); // (StreamObjectAttr_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// CODEC
static Dz1Error _Dz1TodecTargetCodecEntry_analysis(StreamInfo *dst, Dz1TodecTargetCodecEntry *codec, ObjectInfo *src, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *ori = NULL;
	
	u32_t cnt = 0;
	StreamElementList *el_seq = dst->seq;
	Dz1TodecStreamList *cd_seq = codec->seq;
	Dz1TodecStreamEntry **arr = NULL;

	if (codec == NULL || cd_seq == NULL || src == NULL)
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((ori = ObjectInfo_getOrigin(src)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst->attr = Dz1TodecTargetCodecAttr_analysis(codec->attr, ori, &dst->read_var, &dst->write_var, module, errp)) == NULL) ERR_OUT(errp);
	else if ((arr = cd_seq->get_array(cd_seq, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		Dz1TodecStreamEntry *e;
		StreamElementInfo *node = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);

		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			e = arr[i];
			if ((node = StreamElementInfo_generate(e, ori, &dst->read_var, &dst->write_var, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(StreamElementInfo_delAndSetNull, (void *)&node);
				if ((*errp = el_seq->add(el_seq, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (StreamElementInfo_delAndSetNull, (void *)&node);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return err;
}

StreamInfo *Dz1TodecTargetCodecEntry_analysis(Dz1TodecTargetCodecEntry *codec, ObjectInfo *src, Dz1MdefcModule *module, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamInfo *ret = StreamInfo_new(0, 0, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamInfo_delAndSetNull, (void *)&ret);
		if ((*errp = _Dz1TodecTargetCodecEntry_analysis(ret, codec, src, module)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (StreamInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CODEC List Analysis
typedef struct CodecAnalysisArg
{
	StreamList *dst;
	ObjectInfo *obj;
	Dz1MdefcModule *module;
} CodecAnalysisArg;

static Dz1Error _Dz1TodecTargetCodecList_analysis(void *ptr, Dz1TodecTargetCodecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecAnalysisArg *arg = (CodecAnalysisArg *)ptr;
	StreamList *dst = arg->dst;
	StreamInfo *node = NULL;
	if ((node = Dz1TodecTargetCodecEntry_analysis(p, arg->obj, arg->module, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(StreamInfo_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (StreamInfo_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error Dz1TodecTargetCodecList_analysis(StreamList *dst, Dz1TodecTargetCodecList *src, ObjectInfo *obj, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecAnalysisArg arg = { dst, obj, module };
	if ((*errp = src->travel(src, _Dz1TodecTargetCodecList_analysis, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// CODEC List Analysis
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Each Object Analysis
typedef struct TargetAnalysisArg
{
	Dz1MdefcModule *module;
	StreamList *dst;
} TargetAnalysisArg;

static Dz1Error _Dz1TodecTargetList_analysis(void *ptr, Dz1TodecTarget *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TargetAnalysisArg *arg = (TargetAnalysisArg *)ptr;
	Dz1MdefcModule *module = arg->module;
	ObjectInfo *obj = module->findObject(module, p->src_name);
	if (obj == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((*errp = Dz1TodecTargetCodecList_analysis(arg->dst, p->codecs, obj, arg->module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static StreamList *Dz1TodecTargetList_analysis(Dz1TodecTargetList *list, Dz1MdefcModule *module, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamList *ret = StreamList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		TargetAnalysisArg arg = { module, ret };
		pthread_cleanup_push(StreamList_delAndSetNull, (void *)&ret);

		if ((*errp = list->travel(list, _Dz1TodecTargetList_analysis, (void *)&arg)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (StreamList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

StreamList *Dz1Todec_analysis(Dz1Todec *todec, Dz1MdefcModule *module, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamList *ret = NULL;
	if (todec == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TodecTargetList_analysis(todec->list, module, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
// Each Object Analysis
///////////////////////////////////////////////////////////////////////////////
