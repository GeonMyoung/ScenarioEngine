#include "Dz1CodeGenTodecUnion.h"

///////////////////////////////////////////////////////////////////////////////
// Union Gen
Dz1Error ConstructCodecEntry_union_gen_publish(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *obj = p->parent_obj;
	StructureInfo *info = (StructureInfo *)obj->info;
	int tab = 0;
	Dz1Thread_ftprintf(fp, tab, "%s%s *%s_gen(Dz1Error *err)" NEW_LINE, p->mode == ConstructCodecMode_public ? "" : "static ", obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_PTR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "%s *ret = %s_new(%sPresent_max, NULL, errp);" NEW_LINE, obj->name, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab, "if (ret == NULL) ERR_OUT(errp);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return err;
}
// Union Gen
///////////////////////////////////////////////////////////////////////////////

static Dz1Error _union_member_map_primitive(FILE *fp, str_t name, ObjectInfo *obj, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PrimitiveInfo *info = (PrimitiveInfo *)obj->info;
	switch(info->storage)
	{
	case NativeStorage_address:
	case NativeStorage_data:
		Dz1Thread_ftprintf(fp, tab, "Dz1StreamIoMap_VAR(%s, %sPresent_%s, _user_defined_%s, %s)," NEW_LINE,
							env->construct_name, env->construct_name, name, info->native, name);
		break;
	case NativeStorage_none:
		Dz1Thread_ftprintf(fp, tab, "Dz1StreamIoMap_VOID(%s, %sPresent_%s, %s)," NEW_LINE, env->construct_name, env->construct_name, name, name);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return err;
}
///////////////////////////////////////////////////////////////////////////////
// Union Member Map
static Dz1Error _union_member_map_publish(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info,
											ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (name[0] == '@') { }
	else if (info != NULL)
	{
		switch(info->present)
		{
		case ConstructMemberCodecInfoPresent_void_member:
			Dz1Thread_ftprintf(fp, tab, "Dz1StreamIoMap_VOID(%s, %sPresent_%s, %s)," NEW_LINE, env->construct_name, env->construct_name, name, name);
			break;
		case ConstructMemberCodecInfoPresent_alternate:
			Dz1Thread_ftprintf(fp, tab, "Dz1StreamIoMap_STRUCT(%s, %sPresent_%s, %s, %s)," NEW_LINE,
							env->construct_name, env->construct_name, name, info->x.alternate, name);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	else
	{
		if (obj == NULL)
		{
			Dz1Thread_ftprintf(fp, tab, "#error unresolved member [%s]" NEW_LINE, name);
		}
		else
		{
			ObjectType type = ObjectInfo_typeOf(obj);
			switch(type)
			{
			case ObjectType_primitive:				// PrimitiveInfo
				if ((*errp = _union_member_map_primitive(fp, name, obj, env, tab)).code) ERR_OUT(errp);
				break;
			case ObjectType_enumerate:				// EnumInfo
				break;
			case ObjectType_defined:				// DefinedInfo -> don't care
				break;
			case ObjectType_bits:					// BitsInfo -> not support yet
				ERR_SET_OUT(errp, ENOSYS);
				break;
			case ObjectType_structure:				// StructureInfo
			case ObjectType_union:					// UnionInfo
			case ObjectType_array:					// ArrayInfo
			case ObjectType_index:					// IndexInfo
				//Dz1StreamIoMap_STRUCT(ConstructMemberCodecInfo, ConstructMemberCodecInfoPresent_one_of_structure,	CodecOneOfConstruct,  one_of_structure),
				Dz1Thread_ftprintf(fp, tab, "Dz1StreamIoMap_STRUCT(%s, %sPresent_%s, %s, %s)," NEW_LINE,
								env->construct_name, env->construct_name, name, obj->name, name);
				break;
			case ObjectType_declare:				// 선행 정의용 -> don't care
				break;
			case ObjectType_extern:					// ExternInfo			외부 정의 타입 -> don't care
			case ObjectType_reference:				// ExternInfo			헤더에서 인클루드할 경우 -> don't care
													//						인클루드 순환이 발생하는 타입
				break;
			case ObjectType_func:					// FunctionInfo	-> don't care
				break;
			case ObjectType_constant:				// don't care
				break;
			}
		}
	}
	return err;
}
// Union Member Map
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// API Map
static Dz1Error _union_map_publish(FILE *fp, ConstructCodecEntry *p, ConstructMemberCodecList *list, ConstructMemberCodecEntry **ret_present)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	u32_t cnt = 0;
	ObjectInfo *obj = p->parent_obj;
	ConstructMemberCodecEntry **arr = NULL;

	(*ret_present) = NULL;
	if ((arr = list->get_array(list, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		str_t suffix = (p->opt_suffix != NULL && p->opt_suffix[0] != 0) ? p->opt_suffix : "";
		ConstructPublishEnv env = { obj->name, suffix, NULL };
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);
		Dz1Thread_ftprintf(fp, tab++, "static Dz1StreamIoMap %s%sCodecMap[] = {" NEW_LINE, obj->name, suffix);

		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if (arr[i]->instance_name[0] == '@')
			{
				if (Dz1STRCMP(arr[i]->instance_name, INSTANCE_NAME_PRESENT) == 0) (*ret_present) = arr[i];
				else ERR_SET_OUT(errp, EINVAL);
			}
			else if ((*errp = _union_member_map_publish(fp, arr[i]->instance_name, arr[i]->obj, arr[i]->info, &env, tab)).code) ERR_OUT(errp);
		}
		Dz1Thread_ftprintf(fp, tab, "Dz1StreamIoMapEntry_last" NEW_LINE);
		Dz1Thread_ftprintf(fp, --tab, "};" NEW_LINE NEW_LINE);
		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&arr);
	}
	return err;
}
// API Map
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Write
static Dz1Error _union_write_publish(FILE *fp, ConstructCodecEntry *p, ConstructMemberCodecEntry *present, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *obj = p->parent_obj;
	str_t suffix = (p->opt_suffix != NULL && p->opt_suffix[0] != 0) ? p->opt_suffix : "";
	Dz1Thread_ftprintf(fp, tab, "%sssize_t %s%s_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)" NEW_LINE, p->mode == ConstructCodecMode_public ? "" : "static ", obj->name, suffix);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ssize_t ret = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_PTR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "%s *src = (%s *)_src;" NEW_LINE, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab, "if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);

	if (present != NULL)
	{	// include present
		ConstructMemberCodecInfo *info = NULL;
		if ((info = present->info) == NULL)
		{	// default union
			Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_write(dst, src, ed, param, %s%sCodecMap, 4, errp), errp);" NEW_LINE, obj->name, suffix);
		}
		else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
		{
			ERR_SET_OUT(errp, ENOSYS);
		}
		else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
		{
			CodecPrimitiveByte *bop = info->x.byte_of_primitive;
			if (bop->byte_sft == 0)
			{
				if (bop->byte_len > 4) ERR_SET_OUT(errp, EPERM);
				else
				{
					switch(bop->byte_len)
					{
					case 1:
						Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_write(dst, src, ed, param, %s%sCodecMap, 1, errp), errp);" NEW_LINE,
											obj->name, suffix);
						break;
					case 2:
						Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_write(dst, src, ed, param, %s%sCodecMap, 2, errp), errp);" NEW_LINE,
											obj->name, suffix);
						break;
					case 4:
						Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_write(dst, src, ed, param, %s%sCodecMap, 4, errp), errp);" NEW_LINE,
											obj->name, suffix);
						break;
					default:
						ERR_SET_OUT(errp, ENOSYS);
						break;
					}
				}
			}
			else
			{
				ERR_SET_OUT(errp, ENOSYS);
			}
		}
		else if (info->present == ConstructMemberCodecInfoPresent_alternate)
		{
			Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, src->present, ed, param, errp), errp);" NEW_LINE, info->x.alternate);
			Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_writeB(dst, src, ed, param, %s%sCodecMap, errp), errp);" NEW_LINE, obj->name, suffix);
		}
		else if (info->present == ConstructMemberCodecInfoPresent_void_member)
		{	// body only
			Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_writeB(dst, src, ed, param, %s%sCodecMap, errp), errp);" NEW_LINE, obj->name, suffix);
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	else
	{	// body only
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_writeB(dst, src, ed, param, %s%sCodecMap, errp), errp);" NEW_LINE, obj->name, suffix);
	}

	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return err;
}
// Union Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Read
static Dz1Error _union_read_publish(FILE *fp, ConstructCodecEntry *p, ConstructMemberCodecEntry *present, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *obj = p->parent_obj;
	str_t suffix = (p->opt_suffix != NULL && p->opt_suffix[0] != 0) ? p->opt_suffix : "";
	Dz1Thread_ftprintf(fp, tab, "%sssize_t %s%s_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)" NEW_LINE, p->mode == ConstructCodecMode_public ? "" : "static ", obj->name, suffix);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ssize_t ret = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_PTR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "%s *dst = (%s *)_dst;" NEW_LINE, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab, "if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);

	if (present != NULL)
	{
		ConstructMemberCodecInfo *info = present->info;
		if (info == NULL)
		{	// default read
			Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_read(dst, src, ed, param, %s%sCodecMap, 4, errp), errp);" NEW_LINE, obj->name, suffix);
		}
		else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
		{
			CodecPrimitiveByte *bop = info->x.byte_of_primitive;
			if (bop->byte_sft == 0)
			{
				switch(bop->byte_len)
				{
				case 1:
					Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_read(dst, src, ed, param, %s%sCodecMap, 1, errp), errp);" NEW_LINE, obj->name, suffix);
					break;
				case 2:
					Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_read(dst, src, ed, param, %s%sCodecMap, 2, errp), errp);" NEW_LINE, obj->name, suffix);
					break;
				case 4:
					Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_read(dst, src, ed, param, %s%sCodecMap, 4, errp), errp);" NEW_LINE, obj->name, suffix);
					break;
				default:
					ERR_SET_OUT(errp, ENOSYS);
					break;
				}
			}
			else ERR_SET_OUT(errp, ENOSYS);
		}
		else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
		{
			ERR_SET_OUT(errp, ENOSYS);
		}
		else if (info->present == ConstructMemberCodecInfoPresent_alternate)
		{
			Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_read(&dst->present, src, ed, param, errp), errp);" NEW_LINE, info->x.alternate);
			Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_readB(dst, src, ed, param, %s%sCodecMap, errp), errp);" NEW_LINE, obj->name, suffix);
		}
		else if (info->present == ConstructMemberCodecInfoPresent_void_member)
		{	// Body Only
			Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_readB(dst, src, ed, param, %s%sCodecMap, errp), errp);" NEW_LINE, obj->name, suffix);
		}
		else ERR_SET_OUT(errp, ENOSYS);
	}
	else
	{	// Body Only
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, Dz1StreamUnion_readB(dst, src, ed, param, %s%sCodecMap, errp), errp);" NEW_LINE, obj->name, suffix);
	}
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	return err;
}
// Union Read
///////////////////////////////////////////////////////////////////////////////

Dz1Error ConstructCodecEntry_union_rw_publish(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ConstructMemberCodecEntry *present = NULL;
	if ((*errp = _union_map_publish(fp, p, p->member_codec, &present)).code) ERR_OUT(errp);
	else if ((*errp = _union_write_publish(fp, p, present, endian)).code) ERR_OUT(errp);
	else if ((*errp = _union_read_publish(fp, p, present, endian)).code) ERR_OUT(errp);
	return err;
}
