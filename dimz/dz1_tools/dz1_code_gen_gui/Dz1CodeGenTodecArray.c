#include "Dz1CodeGenTodecArray.h"
/*
static ConstructMemberCodecList *ConstructMemberCodecList_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructMemberCodecList *ret = ConstructMemberCodecList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}
*/
///////////////////////////////////////////////////////////////////////////////
// Array Gen
Dz1Error ConstructCodecEntry_array_gen_publish(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *obj = p->parent_obj;
	str_t name = obj->name;
	Dz1Thread_ftprintf(fp, tab, "%s%s *%s_gen(Dz1Error *err)" NEW_LINE, (p->mode == ConstructCodecMode_public) ? "" : "static ", name, name);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_DECLARE(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "%s *ret = %s_new(errp);" NEW_LINE, name, name);
	Dz1Thread_ftprintf(fp, tab, "if (ret == NULL) ERR_OUT(errp);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return err;
}
// Array Gen
///////////////////////////////////////////////////////////////////////////////

/*
static Dz1Error _ConstructMemberCodecList_write(void *ptr, ConstructMemberCodecEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	ssize_t status = ConstructMemberCodecEntry_write(arg->stream, p, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else arg->ret += status;
	return err;
}
*/
///////////////////////////////////////////////////////////////////////////////
// Primitive Element Write
static Dz1Error _primitive_element_write(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PrimitiveInfo *pr_info = (PrimitiveInfo *)obj->info;
	s32_t target_size = _resolve_primitive_type_size(pr_info);
	if (info == NULL)
	{	// default code
		switch(target_size)
		{
		case 1: Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_write1(arg->stream, *p, errp);" NEW_LINE); break;
		case 2: Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_write2(arg->stream, *p, arg->ed, errp);" NEW_LINE); break;
		case 4: Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_write4(arg->stream, *p, arg->ed, errp);" NEW_LINE); break;
		case 8: Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_write8(arg->stream, *p, arg->ed, errp);" NEW_LINE); break;
		default:
			Dz1Thread_ftprintf(fp, tab, "ssize_t status = _user_defined_%s_write(arg->stream, p, arg->ed, arg->option, errp);" NEW_LINE, pr_info->native);
			break;
		}
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{	// 일부 바이트만
		ERR_SET_OUT(errp, ENOSYS);
// 		CodecPrimitiveByte *method = info->x.byte_of_primitive;
// 		u32_t cnt = method->byte_len - 1;
// 		target_size = CodecPrimitiveByte_getLeastSize(method);
// 		Dz1Thread_ftprintf(fp, tab, "u%u_t v%u = (u%u_t)(src->%s >> %u) & ((0x1 << %u) - 1);" NEW_LINE,
// 									target_size * 8, target_size * 8, target_size * 8,
// 									name, method->byte_sft * 8, method->byte_len * 8);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
	{	// 일부 비트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_write(arg->stream, p, arg->ed, arg->option, errp);" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Primitive Element Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Primitive Element Read
static Dz1Error _primitive_element_read(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	PrimitiveInfo *pr_info = (PrimitiveInfo *)obj->info;
	s32_t target_size = _resolve_primitive_type_size(pr_info);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "%s node = 0;" NEW_LINE, obj->name);
		switch(target_size)
		{
		case 1: Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_read1(&node, src, errp);" NEW_LINE); break;
		case 2: Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_read2(&node, src, ed, errp);" NEW_LINE); break;
		case 4: Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_read4(&node, src, ed, errp);" NEW_LINE); break;
		case 8: Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_read8(&node, src, ed, errp);" NEW_LINE); break;
		default:
			Dz1Thread_ftprintf(fp, tab, "ssize_t status = _user_defined_%s_read(&node, src, ed, param, errp);" NEW_LINE, pr_info->native);
			break;
		}
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{	// 일부 바이트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
	{	// 일부 비트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_read(&node, src, ed, param, errp);" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	Dz1Thread_ftprintf(fp, tab, "if (status < 0) ERR_OUT_RET(errp, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "node = NULL;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ret += status;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "Dz1Error_set(errp, 0);" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	return err;
}
// Primitive Element Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enum Element Write
static Dz1Error _enum_element_write(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_write4(arg->stream, (u32_t)*p, arg->ed, errp);" NEW_LINE);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{	// 일부 바이트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
	{	// 일부 비트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_write(arg->stream, p, arg->ed, arg->option, errp);" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Enum Element Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enum Element Read
static Dz1Error _enum_element_read(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab, "%s node;" NEW_LINE, obj->name);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "u32_t v32 = 0;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = Dz1Stream_read4(&v32, src, ed, errp); node = (%s)v32;" NEW_LINE, obj->name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{	// 일부 바이트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_bits_of_primitive)
	{	// 일부 비트만
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_read(&node, src, ed, param, errp);" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	Dz1Thread_ftprintf(fp, tab, "if (status < 0) ERR_OUT_RET(errp, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "node = NULL;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ret += status;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "Dz1Error_set(errp, 0);" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	return err;
}
// Enum Element Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Element Write
static Dz1Error _struct_element_write(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_write(arg->stream, p, arg->ed, arg->option, errp);" NEW_LINE, obj->name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_one_of_structure)
	{
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_write(arg->stream, p, arg->ed, arg->option, errp);" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Structure Element Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Element Read
static Dz1Error _struct_element_read(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab, "%s *node = %s_gen(errp);" NEW_LINE, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab, "if (node == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ssize_t status = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "pthread_cleanup_push(%s_delAndSetNull, (void *)&node)" NEW_LINE, obj->name);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "if ((status = %s_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }" NEW_LINE, obj->name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_one_of_structure)
	{
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "if ((status = %s_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	Dz1Thread_ftprintf(fp, tab, "else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "node = NULL;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ret += status;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "Dz1Error_set(errp, 0);" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "pthread_cleanup_pop(1); // (%s_delAndSetNull, (void *)&node)" NEW_LINE, obj->name);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	return err;
}
// Structure Element Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Element Write
static Dz1Error _union_element_write(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_write(arg->stream, p, arg->ed, arg->option, errp);" NEW_LINE, obj->name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_write(arg->stream, p, arg->ed, arg->option, errp);" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Union Element Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Element Read
static Dz1Error _union_element_read(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab, "%s *node = %s_gen(errp);" NEW_LINE, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab, "if (node == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ssize_t status = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "pthread_cleanup_push(%s_delAndSetNull, (void *)&node)" NEW_LINE, obj->name);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "if ((status = %s_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }" NEW_LINE, obj->name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "if ((status = %s_write(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	Dz1Thread_ftprintf(fp, tab, "else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "node = NULL;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ret += status;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "Dz1Error_set(errp, 0);" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "pthread_cleanup_pop(1); // (%s_delAndSetNull, (void *)&node)" NEW_LINE, obj->name);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	return err;
}
// Union Element Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Element Write
static Dz1Error _array_element_write(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_write(arg->stream, p, arg->ed, arg->option, errp);" NEW_LINE, obj->name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "ssize_t status = %s_write(arg->stream, p, aeg->ed, arg->option, errp);" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Array Element Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Element Read
static Dz1Error _array_element_read(FILE *fp, ObjectInfo *obj, ConstructMemberCodecInfo *info, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab, "%s *node = %s_gen(errp);" NEW_LINE, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab, "if (node == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ssize_t status = 0;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "pthread_cleanup_push(%s_delAndSetNull, (void *)&node)" NEW_LINE, obj->name);
	if (info == NULL)
	{	// default code
		Dz1Thread_ftprintf(fp, tab, "if ((status = %s_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }" NEW_LINE, obj->name);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_alternate)
	{	// 지정 함수 사용
		str_t func_prefix = info->x.alternate;
		Dz1Thread_ftprintf(fp, tab, "if ((status = %s_write(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }" NEW_LINE, func_prefix);
	}
	else ERR_SET_OUT(errp, EINVAL);
	Dz1Thread_ftprintf(fp, tab, "else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "node = NULL;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ret += status;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "Dz1Error_set(errp, 0);" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "pthread_cleanup_pop(1); // (%s_delAndSetNull, (void *)&node)" NEW_LINE, obj->name);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	return err;
}
// Array Element Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Element Write Helper
static Dz1Error _array_element_write_helper(FILE *fp, str_t name, ConstructMemberCodecEntry *element, ConstructPublishEnv *env)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *el_obj = element->obj;
	ObjectType type = ObjectInfo_typeOf(el_obj);
	Dz1Thread_ftprintf(fp, tab, "static Dz1Error _%s%s_write(void *ptr, %s *p)" NEW_LINE, name, env->suffix, el_obj->name);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_VAR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;" NEW_LINE);

	switch(type)
	{
	case ObjectType_primitive:				// PrimitiveInfo
		_primitive_element_write(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_enumerate:				// EnumInfo
		_enum_element_write(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_defined:				// DefinedInfo -> don't care
		break;
	case ObjectType_bits:					// BitsInfo
		// _bits_member_write();
		ERR_SET_OUT(errp, ENOSYS);
		break;
	case ObjectType_structure:				// StructureInfo
		_struct_element_write(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_union:					// UnionInfo
		_union_element_write(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_array:					// ArrayInfo
		_array_element_write(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_declare:				// 선행 정의용 -> don't care
		break;
	case ObjectType_extern:					// ExternInfo			외부 정의 타입 -> don't care
	case ObjectType_reference:				// ExternInfo			헤더에서 인클루드할 경우 -> don't care
											//						인클루드 순환이 발생하는 타입
		break;
	case ObjectType_func:					// FunctionInfo	-> don't care
		break;
	case ObjectType_index:					// IndexInfo
		_array_element_write(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_constant:				// don't care
		break;
	}
	Dz1Thread_ftprintf(fp, tab, "if (status < 0) ERR_OUT(errp);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else arg->ret += status;" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "return err;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return err;
}
// Element Write Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Element Read Helper
static Dz1Error _array_element_read_helper(FILE *fp, ConstructCodecEntry *p, ConstructMemberCodecEntry *element, ConstructPublishEnv *env)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *obj = p->parent_obj, *el_obj = element->obj;
	ObjectType type = ObjectInfo_typeOf(el_obj);
	Dz1Thread_ftprintf(fp, tab, "static ssize_t _%s%s_read(%s *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *errp)" NEW_LINE,
								obj->name, env->suffix, obj->name);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "ssize_t ret = 0;" NEW_LINE);

	switch(type)
	{
	case ObjectType_primitive:				// PrimitiveInfo
		_primitive_element_read(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_enumerate:				// EnumInfo
		_enum_element_read(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_defined:				// DefinedInfo -> don't care
		break;
	case ObjectType_bits:					// BitsInfo
		// _bits_member_write();
		ERR_SET_OUT(errp, ENOSYS);
		break;
	case ObjectType_structure:				// StructureInfo
		_struct_element_read(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_union:					// UnionInfo
		_union_element_read(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_array:					// ArrayInfo
		_array_element_read(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_declare:				// 선행 정의용 -> don't care
		break;
	case ObjectType_extern:					// ExternInfo			외부 정의 타입 -> don't care
	case ObjectType_reference:				// ExternInfo			헤더에서 인클루드할 경우 -> don't care
											//						인클루드 순환이 발생하는 타입
		break;
	case ObjectType_func:					// FunctionInfo	-> don't care
		break;
	case ObjectType_index:					// IndexInfo
		_array_element_read(fp, el_obj, element->info, env, tab);
		break;
	case ObjectType_constant:				// don't care
		break;
	}
	Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return err;
}
// Element Write Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Count Write
static Dz1Error _array_count_write(FILE *fp, ConstructMemberCodecEntry *p, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ConstructMemberCodecInfo *info = NULL;
	if ((info = p->info) == NULL)
	{	// default
		Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE2(dst, (u16_t)(cnt & 0xFFFF), ed, errp, ret);" NEW_LINE);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{
		CodecPrimitiveByte *bop = info->x.byte_of_primitive;
		if (bop->byte_sft == 0)
		{
			switch(bop->byte_len)
			{
			case 1:
				Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE1(dst, (u8_t(cnt & 0xFF), errp, ret);" NEW_LINE);
				break;
			case 2:
				Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE2(dst, (u16_t(cnt & 0xFFFF), ed, errp, ret);" NEW_LINE);
				break;
			case 4:
				Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_WRITE4(dst, cnt, ed, errp, ret);" NEW_LINE);
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
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_write(dst, cnt, ed, param, errp), errp);" NEW_LINE, info->x.alternate);
	}
	else ERR_SET_OUT(errp, ENOSYS);
	return err;
}
// Array Count Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Count Read
static Dz1Error _array_count_read(FILE *fp, ConstructMemberCodecEntry *codec, ConstructPublishEnv *env, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ConstructMemberCodecInfo *info = NULL;
	if ((info = codec->info) == NULL)
	{	// default
		Dz1Thread_ftprintf(fp, tab, "u16_t cnt, i;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ2(&cnt, src, ed, errp, ret);" NEW_LINE);
	}
	else if (info->present == ConstructMemberCodecInfoPresent_byte_of_primitive)
	{
		CodecPrimitiveByte *bop = info->x.byte_of_primitive;
		if (bop->byte_sft == 0)
		{
			switch(bop->byte_len)
			{
			case 1:
				Dz1Thread_ftprintf(fp, tab, "u8_t cnt, i;" NEW_LINE);
				Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ1(&cnt, src, errp, ret);" NEW_LINE);
				break;
			case 2:
				Dz1Thread_ftprintf(fp, tab, "u16_t cnt, i;" NEW_LINE);
				Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ2(&cnt, src, ed, errp, ret);" NEW_LINE);
				break;
			case 4:
				Dz1Thread_ftprintf(fp, tab, "u32_t cnt, i;" NEW_LINE);
				Dz1Thread_ftprintf(fp, tab, "DZ1_STREAM_READ4(&cnt, src, ed, errp, ret);" NEW_LINE);
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
		Dz1Thread_ftprintf(fp, tab, "u16_t cnt, i;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s_read(&cnt, src, ed, param, errp), errp);" NEW_LINE, info->x.alternate);
	}
	else ERR_SET_OUT(errp, ENOSYS);
	return err;
}
// Array Count Read
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Write
static Dz1Error _array_write(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *obj = p->parent_obj;
	str_t suffix = (p->opt_suffix != NULL && p->opt_suffix[0] != 0) ? p->opt_suffix : "";
	ConstructPublishEnv env = { obj->name, suffix, endian };
	ConstructMemberCodecEntry *count_codec = ConstructMemberCodecList_findByName(p->member_codec, INSTANCE_NAME_COUNT);
	ConstructMemberCodecEntry *element_codec = ConstructMemberCodecList_findByName(p->member_codec, INSTANCE_NAME_ELEMENT);
	if (count_codec == NULL || element_codec == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((*errp = _array_element_write_helper(fp, obj->name, element_codec, &env)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_ftprintf(fp, tab,   "%sssize_t %s%s_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)" NEW_LINE, (p->mode == ConstructCodecMode_public) ? "" : "static ", obj->name, suffix);
		Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,       "ssize_t ret = 0;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,       "DZ1_ERROR_SAFE_DECLARE(errp, err);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,       "%s *src = (%s *)_src;" NEW_LINE, obj->name, obj->name);
		Dz1Thread_ftprintf(fp, tab,       "if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,       "else" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab++,     "{" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,           "Dz1ListStreamArg arg = { dst, 0, ed, param };" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,           "u32_t cnt = src->count(src);" NEW_LINE);
		if ((*errp =						  _array_count_write(fp, count_codec, &env, tab)).code) ERR_OUT_RET(errp, err);
		Dz1Thread_ftprintf(fp, tab,           "if ((*errp = src->travel(src, _%s%s_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);" NEW_LINE, obj->name, suffix);
		Dz1Thread_ftprintf(fp, tab,           "else ret += arg.ret;" NEW_LINE);
		Dz1Thread_ftprintf(fp, --tab,     "}" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,       "return ret;" NEW_LINE);
		Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	}
	return err;
}
// Array Write
///////////////////////////////////////////////////////////////////////////////

/*
static ssize_t ConstructMemberCodecList_read(void *_dst, Dz1Stream *src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ConstructCodecEntry *entry = (ConstructCodecEntry *)param;
	ConstructMemberCodecList *dst = (ConstructMemberCodecList *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		u16_t cnt, i;
		ConstructMemberCodecEntry *node = NULL;
		DZ1_STREAM_READ2(&cnt, src, Dz1IOStreamEndian_big, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = ConstructMemberCodecEntry_gen(entry, errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(ConstructMemberCodecEntry_delAndSetNull, (void *)&node);
				if ((status = ConstructMemberCodecEntry_read(node, src, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					ret += status;
				}
				pthread_cleanup_pop(1); // (ConstructMemberCodecEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
*/

///////////////////////////////////////////////////////////////////////////////
// Array Read
static Dz1Error _array_read(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	ObjectInfo *obj = p->parent_obj;
	str_t suffix = (p->opt_suffix != NULL && p->opt_suffix[0] != 0) ? p->opt_suffix : "";
	ConstructPublishEnv env = { obj->name, suffix, endian };
	ConstructMemberCodecEntry *count_codec = ConstructMemberCodecList_findByName(p->member_codec, INSTANCE_NAME_COUNT);
	ConstructMemberCodecEntry *element_codec = ConstructMemberCodecList_findByName(p->member_codec, INSTANCE_NAME_ELEMENT);
	if (count_codec == NULL || element_codec == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((*errp = _array_element_read_helper(fp, p, element_codec, &env)).code) ERR_OUT(errp);
	else
	{
		ObjectInfo *el_obj = element_codec->obj;
		Dz1Thread_ftprintf(fp, tab, "%sssize_t %s%s_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)" NEW_LINE, (p->mode == ConstructCodecMode_public) ? "" : "static ", obj->name, suffix);
		Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "ssize_t ret = 0;" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_DECLARE(errp, err);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "%s *dst = (%s *)_dst;" NEW_LINE, obj->name, obj->name);
		Dz1Thread_ftprintf(fp, tab, "if (src == NULL || dst == NULL) ERR_SET_RET(errp, EINVAL, -1);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "else" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);

		if ((*errp = _array_count_read(fp, count_codec, &env, tab)).code) ERR_OUT_RET(errp, err);

		Dz1Thread_ftprintf(fp, tab++,     "for (i = 0; errp->code == 0 && i < cnt; i++)" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab--,	      "DZ1_IO_STREAM_FUNC(ret, _%s%s_read(dst, src, ed, param, errp), errp);" NEW_LINE, obj->name, suffix);
		Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
		Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE);
	}
	return err;
}
// Array Read
///////////////////////////////////////////////////////////////////////////////

Dz1Error ConstructCodecEntry_array_rw_publish(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = _array_write(fp, p, endian)).code) ERR_OUT(errp);
	else if ((*errp = _array_read(fp, p, endian)).code) ERR_OUT(errp);
	return err;
}
