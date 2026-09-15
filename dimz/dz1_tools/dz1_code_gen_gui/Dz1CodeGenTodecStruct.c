#include "Dz1CodeGenTodecStruct.h"

static u32_t CodecPrimitiveByte_getLeastSize(CodecPrimitiveByte *p)
{
	if (p->byte_len > 4) return 8;
	else if (p->byte_len > 2) return 4;
	else return 1;
}

/*
static CodecPrimitiveBits *CodecPrimitiveBits_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CodecPrimitiveBits *ret = CodecPrimitiveBits_new(NULL, -1, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

*/

///////////////////////////////////////////////////////////////////////////////
// Structure Gen
Dz1Error ConstructCodecEntry_struct_gen_publish(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	u32_t cnt = 0;
	ObjectInfo *obj = p->parent_obj;
	StructureInfo *info = (StructureInfo *)obj->info;
	StructMemberList *list = info->members;
	StructMemberEntry **arr = list->get_array(list, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		StructMemberEntry *e = NULL;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);
		Dz1Thread_ftprintf(fp, tab, "%s%s *%s_gen(Dz1Error *err)" NEW_LINE, p->mode == ConstructCodecMode_public ? "" : "static ", obj->name, obj->name);
		Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_DECLARE(errp, err);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "%s *ret = %s_new(", obj->name, obj->name);
		for (i = 0; i < cnt; i++)
		{
			e = arr[i];
// 			if (e->argInvolve)
			if (StructMemberEntry_isArgInvolve(e))
			{
				if (e->isPointer) Dz1Thread_fprintf(fp, "NULL, ");
				else
				{
					ObjectInfo *obj = e->type;
					ObjectType type = ObjectInfo_typeOf(obj);
					switch(type)
					{
					case ObjectType_primitive:				// PrimitiveInfo
						{
							PrimitiveInfo *info = (PrimitiveInfo *)obj->info;
							if (info->storage == NativeStorage_address)
								Dz1Thread_fprintf(fp, "NULL, ");
							else if (info->storage == NativeStorage_data)
							{
								Dz1Thread_fprintf(fp, "0, ");
// 								switch(_resolve_primitive_type_size(info))
// 								{
// 								case 1: case 2: case 4: case 8:
// 									break;
// 								default:
// 									ERR_SET_OUT(errp, EINVAL);
// 									break;
// 								}
							}
							else ERR_SET_OUT(errp, EINVAL);
						}
						break;
					case ObjectType_enumerate:				// EnumInfo
						{
							EnumInfo *info = (EnumInfo *)obj->info;
							EnumList *enums = info->enums;
							EnumEntry *first = Dz1Fifo_getFirst(enums->fifo);
							Dz1Thread_fprintf(fp, "%s_%s, ", obj->name, first->name);
						}
						break;
					default:
					case ObjectType_defined:				// don't care : error
					case ObjectType_bits:					// error : pointer가 아니므로...
					case ObjectType_structure:				// error : pointer가 아니므로...
					case ObjectType_union:					// error : pointer가 아니므로...
					case ObjectType_array:					// error : pointer가 아니므로...
					case ObjectType_declare:				// don't care : error
						ERR_SET_OUT(errp, EINVAL);
						break;
					case ObjectType_extern:					// don't care : error
						{
							ExternInfo *exi = (ExternInfo *)obj->info;
							if (exi->isStatic) Dz1Thread_fprintf(fp, "0, ");
							else Dz1Thread_fprintf(fp, "NULL, ");
						}
						break;
					case ObjectType_reference:				// don't care : error
					case ObjectType_func:					// error
					case ObjectType_index:					// error
					case ObjectType_constant:				// error
						ERR_SET_OUT(errp, EINVAL);
						break;
					}
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&arr);
		Dz1Thread_fprintf(fp, "errp);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "if (ret == NULL) ERR_OUT(errp);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
		Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	}
	return err;
}
// Structure Gen
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Primitive Member Write
static Dz1Error _primitive_member_write(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PrimitiveInfo *pr_info = (PrimitiveInfo *)obj->info;
	s32_t target_size = _resolve_primitive_type_size(pr_info);
	if (info == NULL)
	{	// default code
		switch(target_size)
		{
		case 1:  Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE1(dst, src->%s, errp, ret);" NEW_LINE, name); break;
		case 2:  Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE2(dst, src->%s, ed, errp, ret);" NEW_LINE, name); break;
		case 4:  Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE4(dst, src->%s, ed, errp, ret);" NEW_LINE, name); break;
		case 8:  Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE8(dst, src->%s, ed, errp, ret);" NEW_LINE, name); break;
		default: Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, _user_defined_%s_write(dst, &src->%s, ed, param, errp), errp);" NEW_LINE, pr_info->native, name); break;
		}
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{	// 일부 바이트만
		CodecPrimitiveByte *bop = info->x.byte_of_primitive;
		if (bop->byte_sft == 0)
		{
			switch(bop->byte_len)
			{
			case 1: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE1(dst, (u8_t)(src->%s & 0xFF), errp, ret);" NEW_LINE, name); break;
			case 2: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE2(dst, (u16_t)(src->%s & 0xFFFF), ed, errp, ret);" NEW_LINE, name); break;
			case 4: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE4(dst, (u32_t)(src->%s & 0xFFFFFFFF), ed, errp, ret);" NEW_LINE, name); break;
			default: ERR_SET_OUT(errp, ENOSYS); break;
			}
		}
		else
		{
			u32_t sh = bop->byte_sft * 8;
			switch(bop->byte_len)
			{
			case 1: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE1(dst, (u8_t)((src->%s >> %d) & 0xFF), errp, ret);" NEW_LINE, name, sh); break;
			case 2: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE2(dst, (u16_t)((src->%s >> %u) & 0xFFFF), ed, errp, ret);" NEW_LINE, name, sh); break;
			case 4: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE4(dst, (u32_t)((src->%s >> %u) & 0xFFFFFFFF), ed, errp, ret);" NEW_LINE, name, sh); break;
			default: ERR_SET_OUT(errp, ENOSYS); break;
			}
		}
	}
	else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
	{	// 일부 비트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, &src->%s, ed, param, errp), errp);" NEW_LINE, info->x.alternate, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Primitive Member Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Primitive Member Read
static Dz1Error _primitive_member_read(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PrimitiveInfo *pr_info = (PrimitiveInfo *)obj->info;
	s32_t target_size = _resolve_primitive_type_size(pr_info);
	if (info == NULL)
	{	// default code
		switch(target_size)
		{
		case 1:  Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ1(&dst->%s, src, errp, ret);" NEW_LINE, name); break;
		case 2:  Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ2(&dst->%s, src, ed, errp, ret);" NEW_LINE, name); break;
		case 4:  Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ4(&dst->%s, src, ed, errp, ret);" NEW_LINE, name); break;
		case 8:  Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ8(&dst->%s, src, ed, errp, ret);" NEW_LINE, name); break;
		default: Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, _user_defined_%s_read(&dst->%s, src, ed, param, errp), errp);" NEW_LINE, pr_info->native, name); break;
		}
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{	// 일부 바이트만
		CodecPrimitiveByte *bop = info->x.byte_of_primitive;
		if (bop->byte_sft == 0)
		{
			switch(bop->byte_len)
			{
			case 1: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ1(&v8, src, errp, ret); dst->%s = (%s)v8;" NEW_LINE, name, obj->name); break;
			case 2: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ2(&v16, src, ed, errp, ret); dst->%s = (%s)v16;" NEW_LINE, name, obj->name); break;
			case 4: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->%s = (%s)v32;" NEW_LINE, name, obj->name); break;
			default: ERR_SET_OUT(errp, ENOSYS); break;
			}
		}
		else
		{
			u32_t sh = bop->byte_sft * 8;
			switch(bop->byte_len)
			{
			case 1: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ1(&v8, src, errp, ret); dst->%s = (%s)(v8 << %u);" NEW_LINE, name, obj->name, sh); break;
			case 2: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ2(&v16, src, ed, errp, ret); dst->%s = (%s)(v16 << %u);" NEW_LINE, name, obj->name, sh); break;
			case 4: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->%s = (%s)(v32 << %u);" NEW_LINE, name, obj->name, sh); break;
			default: ERR_SET_OUT(errp, ENOSYS); break;
			}
		}
	}
	else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
	{	// 일부 비트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_read(&dst->%s, src, ed, param, errp), errp);" NEW_LINE, info->x.alternate, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Primitive Member Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enumerate Member Write
static Dz1Error _enum_member_write(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE4(dst, (u32_t)src->%s, ed, errp, ret);" NEW_LINE, name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{	// 일부 바이트만
		CodecPrimitiveByte *bop = info->x.byte_of_primitive;
		if (bop->byte_sft == 0)
		{
			switch(bop->byte_len)
			{
			case 1: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE1(dst, (u8_t)(src->%s & 0xFF), errp, ret);" NEW_LINE, name); break;
			case 2: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE2(dst, (u16_t)(src->%s & 0xFFFF), ed, errp, ret);" NEW_LINE, name); break;
			case 4: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE4(dst, (u32_t)(src->%s & 0xFFFFFFFF), ed, errp, ret);" NEW_LINE, name); break;
			default: ERR_SET_OUT(errp, ENOSYS); break;
			}
		}
		else
		{
			u32_t sh = bop->byte_sft * 8;
			switch(bop->byte_len)
			{
			case 1: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE1(dst, (u8_t)((src->%s >> %d) & 0xFF), errp, ret);" NEW_LINE, name, sh); break;
			case 2: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE2(dst, (u16_t)((src->%s >> %u) & 0xFFFF), ed, errp, ret);" NEW_LINE, name, sh); break;
			case 4: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE4(dst, (u32_t)((src->%s >> %u) & 0xFFFFFFFF), ed, errp, ret);" NEW_LINE, name, sh); break;
			default: ERR_SET_OUT(errp, ENOSYS); break;
			}
		}
	}
	else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
	{	// 일부 비트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, &src->%s, ed, param, errp), errp);" NEW_LINE, func_prefix, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Enumerate Member Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enumerate Member Read
static Dz1Error _enum_member_read(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->%s = (%s)v32;" NEW_LINE, name, obj->name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{	// 일부 바이트만
		CodecPrimitiveByte *bop = info->x.byte_of_primitive;
		if (bop->byte_sft == 0)
		{
			switch(bop->byte_len)
			{
			case 1: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ1(&v8, src, errp, ret); dst->%s = (%s)v8;" NEW_LINE, name, obj->name); break;
			case 2: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ2(&v16, src, ed, errp, ret); dst->%s = (%s)v16;" NEW_LINE, name, obj->name); break;
			case 4: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->%s = (%s)v32;" NEW_LINE, name, obj->name); break;
			default: ERR_SET_OUT(errp, ENOSYS); break;
			}
		}
		else
		{
			u32_t sh = bop->byte_sft * 8;
			switch(bop->byte_len)
			{
			case 1: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ1(&v8, src, errp, ret); dst->%s = (%s)(v8 << %u);" NEW_LINE, name, obj->name, sh); break;
			case 2: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ2(&v16, src, ed, errp, ret); dst->%s = (%s)(v16 << %u);" NEW_LINE, name, obj->name, sh); break;
			case 4: Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ4(&v32, src, ed, errp, ret); dst->%s = (%s)(v32 << %u);" NEW_LINE, name, obj->name, sh); break;
			default: ERR_SET_OUT(errp, ENOSYS); break;
			}
		}
	}
	else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
	{	// 일부 비트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_read(&dst->%s, src, ed, param, errp), errp);" NEW_LINE, func_prefix, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Enumerate Member read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Member Write
static Dz1Error _struct_member_write(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, src->%s, ed, param, errp), errp);" NEW_LINE, obj->name, name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_one_of_structure)
	{
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, src->%s, ed, param, errp), errp);" NEW_LINE, func_prefix, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Structure Member Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Member Read
static Dz1Error _struct_member_read(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab, "if ((dst->%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE, name, obj->name);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "else DZ1_IO_STREAM_FUNC(ret, %s_read(dst->%s, src, ed, param, errp), errp);" NEW_LINE, obj->name, name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_one_of_structure)
	{
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "else DZ1_IO_STREAM_FUNC(ret, %s_read(dst, src->%s, ed, param, errp), errp);" NEW_LINE, func_prefix, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Structure Member Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Write
static Dz1Error _union_member_write(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, src->%s, ed, param, errp), errp);" NEW_LINE, obj->name, name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, src->%s, ed, param, errp), errp);" NEW_LINE, func_prefix, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Union Member Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member Read
static Dz1Error _union_member_read(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab, "if ((dst->%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE, name, obj->name);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "else DZ1_IO_STREAM_FUNC(ret, %s_read(dst->%s, src, ed, param, errp), errp);" NEW_LINE, obj->name, name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "else DZ1_IO_STREAM_FUNC(ret, %s_write(dst->%s, src, ed, param, errp), errp);" NEW_LINE, func_prefix, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Union Member Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Member Write
static Dz1Error _array_member_write(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, src->%s, ed, param, errp), errp);" NEW_LINE, obj->name, name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, src->%s, ed, param, errp), errp);" NEW_LINE, info->x.alternate, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Array Member Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Member Read
static Dz1Error _array_member_read(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab, "if (dst->%s == NULL && (dst->%s = %s_new(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE, name, name, obj->name);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "else DZ1_IO_STREAM_FUNC(ret, %s_read(dst->%s, src, ed, param, errp), errp);" NEW_LINE, obj->name, name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		Dz1Thread_ftprintf(fp, tab, "else DZ1_IO_STREAM_FUNC(ret, %s_read(dst->%s, src, ed, param, errp), errp);" NEW_LINE, info->x.alternate, name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Array Member Read
///////////////////////////////////////////////////////////////////////////////

static Dz1Error _external_member_write(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ExternInfo *exi = (ExternInfo *)obj->info;
	if (info == NULL)
	{
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, %ssrc->%s, ed, param, errp), errp);" NEW_LINE,
									obj->name, exi->isStatic ? "&" : "", name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, %ssrc->%s, ed, param, errp), errp);" NEW_LINE,
									info->x.alternate, exi->isStatic ? "&" : "", name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}

static Dz1Error _external_member_read(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t need_else = FALSE;
	ExternInfo *exi = (ExternInfo *)obj->info;
	if (exi->isStatic == FALSE)
	{
		Dz1Thread_ftprintf(fp, tab, "if (dst->%s == NULL && (dst->%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE, name, name, obj->name);
		need_else = TRUE;
	}

	if (info == NULL)
	{
		Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s_read(%sdst->%s, src, ed, param, errp), errp);" NEW_LINE,
									need_else ? "else " : "", obj->name, exi->isStatic ? "&" : "", name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{
		Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s_read(%sdst->%s, src, ed, param, errp), errp);" NEW_LINE,
									need_else ? "else " : "", info->x.alternate, exi->isStatic ? "&" : "", name);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Member List Write
static Dz1Error _structure_publish_member_write(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (name[0] == '@')
	{	// @pad only
		if (info == NULL || info->present != ConstructMemberCodecInfoPresent_padding) ERR_SET_OUT(errp, EFAULT);
		else
		{
			CodecPadding *padding = info->x.padding;
			u32_t bit_len = padding->bit_len;
			u32_t byte_len = bit_len >> 3;
			if (bit_len &= 0x7) ERR_SET_OUT(errp, E2BIG);
			else Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE_PAD(dst, %u, errp);" NEW_LINE, byte_len);
		}
	}
	else
	{	// obj + info
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
				_primitive_member_write(fp, name, obj, info, env, tab);
				break;
			case ObjectType_enumerate:				// EnumInfo
				_enum_member_write(fp, name, obj, info, env, tab);
				break;
			case ObjectType_defined:				// DefinedInfo -> don't care
				break;
			case ObjectType_bits:					// BitsInfo
				// _bits_member_write();
				ERR_SET_OUT(errp, ENOSYS);
				break;
			case ObjectType_structure:				// StructureInfo
				_struct_member_write(fp, name, obj, info, env, tab);
				break;
			case ObjectType_union:					// UnionInfo
				_union_member_write(fp, name, obj, info, env, tab);
				break;
			case ObjectType_array:					// ArrayInfo
				_array_member_write(fp, name, obj, info, env, tab);
				break;
			case ObjectType_declare:				// 선행 정의용 -> don't care
				break;
			case ObjectType_extern:					// ExternInfo			외부 정의 타입
				_external_member_write(fp, name, obj, info, env, tab);
				break;
			case ObjectType_reference:				// ExternInfo			헤더에서 인클루드할 경우 -> don't care
													//						인클루드 순환이 발생하는 타입
				break;
			case ObjectType_func:					// FunctionInfo	-> don't care
				break;
			case ObjectType_index:					// IndexInfo
				_array_member_write(fp, name, obj, info, env, tab);
				break;
			case ObjectType_constant:				// don't care
				break;
			}
		}
	}
	return err;
}

static Dz1Error _structure_members_publish_write(FILE *fp, ObjectInfo *obj, ConstructMemberCodecList *list, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t cnt = 0;
	ConstructMemberCodecEntry **arr = list->get_array(list, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);
		for (i = 0; i < cnt; i++)
		{
			_structure_publish_member_write(fp, arr[i]->instance_name, arr[i]->obj, arr[i]->info, env, tab);
		}
		pthread_cleanup_pop(1); // (ConstructMemberCodecEntry_delAndSetNull, (void *)&arr);
	}
	return err;
}
// Member List Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member List Read
static Dz1Error _structure_publish_member_read(FILE *fp, str_t name, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (name[0] == '@')
	{	// @pad only
		if (info == NULL || info->present != ConstructMemberCodecInfoPresent_padding) ERR_SET_OUT(errp, EFAULT);
		else
		{
			CodecPadding *padding = info->x.padding;
			u32_t bit_len = padding->bit_len;
			u32_t byte_len = bit_len >> 3;
			if (bit_len &= 0x7) ERR_SET_OUT(errp, E2BIG);
			else Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ_PAD(dst, %u, errp);" NEW_LINE, byte_len);
		}
	}
	else
	{	// obj + info
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
				_primitive_member_read(fp, name, obj, info, env, tab);
				break;
			case ObjectType_enumerate:				// EnumInfo
				_enum_member_read(fp, name, obj, info, env, tab);
				break;
			case ObjectType_defined:				// DefinedInfo -> don't care
				break;
			case ObjectType_bits:					// BitsInfo
				// _bits_member_write();
				ERR_SET_OUT(errp, ENOSYS);
				break;
			case ObjectType_structure:				// StructureInfo
				_struct_member_read(fp, name, obj, info, env, tab);
				break;
			case ObjectType_union:					// UnionInfo
				_union_member_read(fp, name, obj, info, env, tab);
				break;
			case ObjectType_array:					// ArrayInfo
				_array_member_read(fp, name, obj, info, env, tab);
				break;
			case ObjectType_declare:				// 선행 정의용 -> don't care
				break;
			case ObjectType_extern:					// ExternInfo			외부 정의 타입 -> don't care
				_external_member_read(fp, name, obj, info, env, tab);
				break;
			case ObjectType_reference:				// ExternInfo			헤더에서 인클루드할 경우 -> don't care
													//						인클루드 순환이 발생하는 타입
				break;
			case ObjectType_func:					// FunctionInfo	-> don't care
				break;
			case ObjectType_index:					// IndexInfo
				_array_member_read(fp, name, obj, info, env, tab);
				break;
			case ObjectType_constant:				// don't care
				break;
			}
		}
	}
	return err;
}

static Dz1Error _structure_members_publish_read(FILE *fp, ObjectInfo *obj, ConstructMemberCodecList *list, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t cnt = 0;
	ConstructMemberCodecEntry **arr = list->get_array(list, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);
		for (i = 0; i < cnt; i++)
		{
			_structure_publish_member_read(fp, arr[i]->instance_name, arr[i]->obj, arr[i]->info, env, tab);
		}
		pthread_cleanup_pop(1); // (ConstructMemberCodecEntry_delAndSetNull, (void *)&arr);
	}
	return err;
}
// Member List Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Write
static Dz1Error _struct_write_publish(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *obj = p->parent_obj;
	str_t suffix = p->opt_suffix != NULL && p->opt_suffix[0] != 0 ? p->opt_suffix : "";
	ConstructPublishEnv env = { obj->name, suffix, endian };
	Dz1Thread_ftprintf(fp, tab,   "%sssize_t %s%s_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)" NEW_LINE, p->mode == ConstructCodecMode_public ? "" : "static ", obj->name, suffix);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "ssize_t ret = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "DZ1_ERROR_SAFE_PTR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "%s *src = (%s *)_src;" NEW_LINE, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab,       "if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++,     "{" NEW_LINE);
	if ((*errp =					      _structure_members_publish_write(fp, p->parent_obj, p->member_codec, &env, tab)).code) ERR_OUT(errp);
	Dz1Thread_ftprintf(fp, --tab,     "}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return err;
}
// Structure Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Write
static Dz1Error _struct_read_publish(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *obj = p->parent_obj;
	str_t suffix = p->opt_suffix != NULL && p->opt_suffix[0] != 0 ? p->opt_suffix : "";
	ConstructPublishEnv env = { obj->name, suffix, endian };
	Dz1Thread_ftprintf(fp, tab,   "%sssize_t %s%s_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)" NEW_LINE, p->mode == ConstructCodecMode_public ? "" : "static ", obj->name, suffix);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "ssize_t ret = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "DZ1_ERROR_SAFE_PTR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "%s *dst = (%s *)_dst;" NEW_LINE, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab,       "if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++,     "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,           "u8_t v8 = 0; u16_t v16 = 0; u32_t v32 = 0;" NEW_LINE);
	if ((*errp =						  _structure_members_publish_read(fp, p->parent_obj, p->member_codec, &env, tab)).code) ERR_OUT(errp);
	Dz1Thread_ftprintf(fp, --tab,     "}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab,       "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	return err;
}
// Structure Write
///////////////////////////////////////////////////////////////////////////////

Dz1Error ConstructCodecEntry_struct_rw_publish(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ConstructMemberCodecEntry *present = NULL;
	if		((*errp = _struct_write_publish(fp, p, endian)).code) ERR_OUT(errp);
	else if ((*errp = _struct_read_publish(fp, p, endian)).code) ERR_OUT(errp);
	return err;
}
