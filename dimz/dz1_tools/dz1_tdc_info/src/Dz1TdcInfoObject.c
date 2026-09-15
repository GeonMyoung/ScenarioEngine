#include <dz1_codec.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_aatree.h>
#include <dz1_str.h>

#include "Dz1TdcInfoModule.h"
#include "Dz1TdcInfoObject.h"

#include "Dz1TdcInfoPublishSpec.h"

static struct ObjectTypeMap
{
	str_t str;
	ObjectType val;
} ObjectTypeMap[] =
{
	{ "primitive",	ObjectType_primitive },
	{ "enumerate",	ObjectType_enumerate },
	{ "defined",	ObjectType_defined },
	{ "bits",		ObjectType_bits },
	{ "structure",	ObjectType_structure },
	{ "union",		ObjectType_union },
	{ "array",		ObjectType_array },
	{ "declare",	ObjectType_declare },
	{ "extern",		ObjectType_extern },
	{ "reference",	ObjectType_reference },
	{ "function",	ObjectType_func },
	{ "Index",		ObjectType_index},
	{ "constant",	ObjectType_constant},
	{ NULL, 0 }
};

static str_t ObjectType_unknown = "unknown";

str_t ObjectTypeStr(ObjectType v)
{
	struct ObjectTypeMap *i;
	for (i = ObjectTypeMap; i->str; i++)
		if (i->val == v) return i->str;
	return ObjectType_unknown;
}

ObjectInfo *ObjectInfo_new(ObjectType type, str_t name, str_t srcName, u32_t api, void *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo *ret = (ObjectInfo *)Dz1Malloc(sizeof(ObjectInfo), errp);
	if (name && strcmp(name, "Dz1ENUMERATED") == 0)
	{
		name = name;
	}

	if (ret == NULL) { }
	else
	{
		memset(ret, 0, sizeof(ObjectInfo));
		pthread_cleanup_push(ObjectInfo_delAndSetNull, (void *)&ret);

		if (name && (ret->name = Dz1Str_dup(name, errp)) == NULL) { }
		else if (srcName && (ret->srcName = Dz1Str_dup(srcName, errp)) == NULL) { }
		else
		{
			ret->api = api;
			ret->type = type;
			ret->info = info;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (ObjectInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ObjectInfo_del(ObjectInfo *p)
{
	if (!p) return;
	if (p->name) Dz1Free(p->name);
	if (p->srcName) Dz1Free(p->srcName);
	switch(p->type)
	{
		case ObjectType_primitive:
			PrimitiveInfo_del((PrimitiveInfo *)p->info);
			break;
		case ObjectType_defined:
			DefinedInfo_del((DefinedInfo *)p->info);
			break;
		case ObjectType_enumerate:
			EnumInfo_del((EnumInfo *)p->info);
			break;
		case ObjectType_bits:
			BitsInfo_del((BitsInfo *)p->info);
			break;
		case ObjectType_union:
			UnionInfo_del((UnionInfo *)p->info);
			break;
		case ObjectType_structure:
			StructureInfo_del((StructureInfo *)p->info);
			break;
		case ObjectType_array:
			ArrayInfo_del((ArrayInfo *)p->info);
			break;
		case ObjectType_extern:
		case ObjectType_reference:
			ExternInfo_del((ExternInfo *)p->info);
			break;
		case ObjectType_declare:
			Dz1Str_del((str_t)p->info);
			break;
		case ObjectType_func:
			FunctionInfo_del((FunctionInfo *)p->info);
			break;
		case ObjectType_index:
			IndexInfo_del((IndexInfo *)p->info);
			break;
		case ObjectType_constant:
			ConstantInfo_del((ConstantInfo *)p->info);
			break;
		default:
			break;
	}
	Dz1Free(p);
}

struct ObjectInfoApiMap
{
	str_t str;
	u32_t val;
};

static struct ObjectInfoApiMap ObjectInfoApiMap[] =
{
	{ "new",			OBJECT_API_NEW },
	{ "del",			OBJECT_API_DEL },
	{ "delAndSetNull",	OBJECT_API_DELANDSETNULL },
	{ "dump",			OBJECT_API_DUMP },
	{ "cmp",			OBJECT_API_CMP },
	{ "clone",			OBJECT_API_CLONE },
#ifdef USE_CODEC
	{ "codec",			OBJECT_API_CODEC },
#endif
//	{ "remove",			OBJECT_API_REMOVE },
//	{ "extract",		OBJECT_API_EXTRACT },
//	{ "find",			OBJECT_API_FIND },
//	{ "arr",			OBJECT_API_ARRAY },
//	{ "travel",			OBJECT_API_TRAVEL },
	{ NULL, 0 }
};

static str_t ObjectInfoApiStr(u32_t api, char dst[1024])
{
	int len = 0;
	char *cp = dst;
	struct ObjectInfoApiMap *i;
	dst[0] = '\0';
	for (i = ObjectInfoApiMap; i->str; i++)
	{
		if (api& i->val)
		{
			if (dst == cp) len = sprintf(cp, "%s", i->str);
			else len = sprintf(cp, ", %s", i->str);
			cp += len;
		}
	}
	return dst;
}

void ObjectInfo_dump(ObjectInfo *p, int tab)
{
	char buf[1024];
	if (!p) return;
	Dz1Thread_tprintf(tab, "%s(%s) %s ", ObjectTypeStr(p->type), ObjectInfoApiStr(ObjectInfo_apiOf(p, NULL), buf), p->name);
	switch(p->type)
	{
		case ObjectType_primitive:
			PrimitiveInfo_dump((PrimitiveInfo *)p->info, 0);
			break;
		case ObjectType_defined:
			DefinedInfo_dump((DefinedInfo *)p->info, 0);
			break;
		case ObjectType_enumerate:
			Dz1Thread_tprintf(tab, "\n{\n");
			EnumInfo_dump((EnumInfo *)p->info, tab + 1);
			Dz1Thread_tprintf(tab, "}\n");
			break;
		case ObjectType_bits:
			BitsInfo_dump((BitsInfo *)p->info, tab + 1);
			break;
		case ObjectType_union:
			Dz1Thread_tprintf(tab, "\n{\n");
			UnionInfo_dump((UnionInfo *)p->info, tab + 1);
			Dz1Thread_tprintf(tab, "}\n");
			break;
		case ObjectType_structure:
			Dz1Thread_tprintf(tab, "\n{\n");
			StructureInfo_dump((StructureInfo *)p->info, tab + 1);
			Dz1Thread_tprintf(tab, "}\n");
			break;
		case ObjectType_array:
			ArrayInfo_dump((ArrayInfo *)p->info, 0);
			break;
		case ObjectType_index:
			IndexInfo_dump((IndexInfo *)p->info, 0);
			break;
		case ObjectType_constant:
			ConstantInfo_dump((ConstantInfo *)p->info, 0);
			break;
		case ObjectType_extern:
		case ObjectType_reference:
			Dz1Thread_tprintf(tab, "\n{\n");
			if (p->info)
				ExternInfo_dump((ExternInfo *)p->info, tab + 1);
			Dz1Thread_tprintf(tab, "}\n");
			break;
		case ObjectType_declare:
			Dz1Thread_printf("as [%s]\n", (str_t)p->info);
			break;
		default:
			Dz1Thread_printf("\n");
			break;
	}
}

int ObjectInfo_cmp(ObjectInfo *a, ObjectInfo *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else return strcmp(a->name, b->name);
}

str_t ObjectInfo_nameOf(ObjectInfo *p)
{
	if (p->type == ObjectType_primitive) return ((PrimitiveInfo *)p->info)->native;
	//else if (p->type == ObjectType_extern || p->type == ObjectType_reference) return ((ExternInfo *)p->info)->publish_name;
	else return p->name;
}

str_t ObjectInfo_prefixOf(ObjectInfo *p, PublishSpec *spec)
{
	if (p->type == ObjectType_primitive) return ((PrimitiveInfo *)p->info)->prefix;
// 	else if (p->type == ObjectType_enumerate)
// 	{
// 		NativeTypeSpec s32key = { ENUMTYPE_NAME }, *s32 = (NativeTypeSpec *)Dz1AATree_find(spec->primitives, &s32key);
// 		return s32->prefix;
// 	}
	else if (p->type == ObjectType_extern || p->type == ObjectType_reference)
	{
		return (p->info && ((ExternInfo *)p->info)->prefix) ? ((ExternInfo *)p->info)->prefix : p->name;
	}
	else return p->name;
}

static u32_t _ObjectInfo_apiOfPrimitive(ObjectInfo *p, PublishSpec *spec)
{
	u32_t ret = OBJECT_API_FANCY;
	if (spec != NULL)
	{
		NativeTypeSpec key = { p->name }, *info = (NativeTypeSpec *)Dz1AATree_find(spec->primitives, &key);
		if (info != NULL)
			ret |= (info->attr_flag & (OBJECT_DUMP_API_ALL | OBJECT_CHSRSET_API_ALL));
		else ret |= (OBJECT_DUMP_API_ALL | OBJECT_CHSRSET_API_ALL);
	}
	return ret;
}

#define ARRAY_ELTRY_API_MASK	(OBJECT_API_CLONE | \
								 OBJECT_API_DUMP | \
								 OBJECT_API_FDUMP | \
								 OBJECT_API_DUMP_MBCS | \
								 OBJECT_API_DUMP_WIDE | \
								 OBJECT_API_WINDOWS_ONLY)

u32_t ObjectInfo_apiOf(ObjectInfo *p, PublishSpec *spec)
{
	u32_t ret = 0;
	if (p)
	{
		switch(p->type)
		{
			case ObjectType_primitive:
				ret = _ObjectInfo_apiOfPrimitive(p, spec);
				break;
			case ObjectType_enumerate:
				if (p->api == OBJECT_API_NONE)
					ret = OBJECT_API_BASE;
				else ret = p->api;
				break;
			case ObjectType_defined:
				ret = ObjectInfo_apiOf(((DefinedInfo *)p->info)->origin, spec);
				break;
			default:
			case ObjectType_structure:
			case ObjectType_union:
			case ObjectType_extern:
			case ObjectType_reference:
				ret = p->api;
				break;
			case ObjectType_array:
//				ret = _ObjectInfo_apiOf(((ArrayInfo *)p->info)->entry, spec);
				ret = p->api | (ObjectInfo_apiOf(((ArrayInfo *)p->info)->entry, spec) & ARRAY_ELTRY_API_MASK);	// root array api + entry api
				break;
			case ObjectType_index:
//				ret = _ObjectInfo_apiOf(((IndexInfo *)p->info)->entry, spec);
				ret = p->api | (ObjectInfo_apiOf(((IndexInfo *)p->info)->entry, spec) & ARRAY_ELTRY_API_MASK);	// root array api + entry api
				break;
			case ObjectType_func:
				//ret = OBJECT_API_DUMP;
				break;
		}
	}
	return ret;
}

// u32_t ObjectInfo_apiOf(ObjectInfo *p, PublishSpec *spec)
// {
// 	u32_t ret = 0;
// 	if (p)
// 	{
// 		switch(p->type)
// 		{
// 			case ObjectType_array:
// 				ret = p->api | (_ObjectInfo_apiOf(((ArrayInfo *)p->info)->entry, spec) & ARRAY_ELTRY_API_MASK);	// root array api + entry api
// 				break;
// 			case ObjectType_index:
// 				ret = p->api | (ObjectInfo_apiOf(((IndexInfo *)p->info)->entry, spec) & ARRAY_ELTRY_API_MASK);	// root array api + entry api
// 				break;
// 			default:
// 				ret = _ObjectInfo_apiOf(p, spec);
// 				break;
// 		}
// 	}
// 	return ret;
// }

int ObjectInfo_isPrimitive(ObjectInfo *p)
{
	int ret = FALSE;
	if (p)
	{
		switch(p->type)
		{
			case ObjectType_primitive:
			case ObjectType_enumerate:
				ret = TRUE;
				break;
			case ObjectType_defined:
				ret = ObjectInfo_isPrimitive(((DefinedInfo *)p->info)->origin);
				break;
			case ObjectType_extern:
			case ObjectType_reference:
				switch(((ExternInfo *)p->info)->isStatic)
				{
				case ExternInfoStatic_primitive:
				case ExternInfoStatic_primitive_ptr:
					ret = TRUE;
					break;
				default:
					break;
				}
				break;
			case ObjectType_func:	// JakeLim : 2024-03-07
				ret = TRUE;
				break;
			default:
				break;
		}
	}
	return ret;
}

static bool_t primitive_isNullScalar(PrimitiveInfo *p)
{	// case of Primitive Type can have null value
	bool_t ret = FALSE;
	if (Dz1STRCMP(p->native, Dz1Text("time_t")) == 0) ret = TRUE;
	return ret;
}

bool_t ObjectInfo_isNullScalar(ObjectInfo *p)
{
	int ret = FALSE;
	if (p)
	{
		switch(p->type)
		{
			case ObjectType_primitive:
				ret = primitive_isNullScalar((PrimitiveInfo *)p->info);
				// ret = ((PrimitiveInfo *)p->info)->storage == NativeStorage_data ? TRUE : FALSE;
				break;
			case ObjectType_defined:
				ret = ObjectInfo_isNullScalar(((DefinedInfo *)p->info)->origin);
				break;
// 			case ObjectType_extern:
// 			case ObjectType_reference:
// 				ret = ((ExternInfo *)p->info)->isStatic;
// 				break;
//			case ObjectType_enumerate:
//				break;
//			case ObjectType_structure:
//				ret = StructureInfo_isScalar((StructureInfo *)p->info);
//				break;
//			case ObjectType_union:
//				ret = UnionInfo_isScalar((UnionInfo *)p->info);
//				ret = TRUE;
//				break;
			default:
				break;
		}
	}
	return ret;
}

static int primitive_isScalr(PrimitiveInfo *p)
{
	switch(p->storage)
	{
	default:
	case NativeStorage_address:
	case NativeStorage_none:
		return FALSE;
	case NativeStorage_data:
		return TRUE;
	}
}

int ObjectInfo_isScalar(ObjectInfo *p)
{
	int ret = FALSE;
	if (p)
	{
		switch(p->type)
		{
			case ObjectType_primitive:
				ret = primitive_isScalr((PrimitiveInfo *)p->info);	// data storage only
				// ret = ((PrimitiveInfo *)p->info)->storage == NativeStorage_data ? TRUE : FALSE;
				break;
			case ObjectType_defined:
				ret = ObjectInfo_isScalar(((DefinedInfo *)p->info)->origin);
				break;
			case ObjectType_extern:
			case ObjectType_reference:
				switch( ((ExternInfo *)p->info)->isStatic)	// may change => ret = (ExternInfo *p)->isPtrType ? FALSE : TRUE;
				{
				case ExternInfoStatic_primitive:
				case ExternInfoStatic_typical_union:
				case ExternInfoStatic_construct:
					ret = TRUE;
				default:
					break;
				}
				break;
//			case ObjectType_enumerate:
//				break;
//			case ObjectType_structure:
//				ret = StructureInfo_isScalar((StructureInfo *)p->info);
//				break;
//			case ObjectType_union:
//				ret = UnionInfo_isScalar((UnionInfo *)p->info);
//				ret = TRUE;
//				break;
			default:
				ret = TRUE;
				break;
		}
	}
	return ret;
}

int ObjectInfo_isVoid(ObjectInfo *p)
{
	int ret = FALSE;
	if (p)
	{
		switch(p->type)
		{
			case ObjectType_primitive:
				ret = ((PrimitiveInfo *)p->info)->storage == NativeStorage_none ? TRUE : FALSE;
				break;
			default:
				break;
		}
	}
	return ret;
}

static int primitive_isStaticSize(PrimitiveInfo *p)
{
	switch(p->storage)
	{
	default:
	case NativeStorage_address:
	case NativeStorage_none:
		return FALSE;
	case NativeStorage_data:
		return TRUE;
	}
}

int ObjectInfo_isStaticSize(ObjectInfo *p)
{
	int ret = FALSE;
	if (p)
	{
		switch(p->type)
		{
			case ObjectType_primitive:
				ret = primitive_isStaticSize((PrimitiveInfo *)p->info);
				// ret = ((PrimitiveInfo *)p->info)->isPointer ? FALSE : TRUE;
				break;
			case ObjectType_defined:
				ret = ObjectInfo_isStaticSize(((DefinedInfo *)p->info)->origin);
				break;
			case ObjectType_enumerate:
				ret = TRUE;
				break;
			case ObjectType_structure:
				ret = StructureInfo_isStaticSize((StructureInfo *)p->info);
				break;
			case ObjectType_union:
				ret = UnionInfo_isStaticSize((UnionInfo *)p->info);
				break;
			case ObjectType_extern:
			case ObjectType_reference:
				ret = ((ExternInfo *)p->info)->isStatic;
				break;
			case ObjectType_func:
				ret = TRUE;
			default:
				break;
		}
	}
	return ret;
}

int ObjectInfo_isClonable(ObjectInfo *p, PublishSpec *spec)
{
	int ret = FALSE;
	if (p)
	{
		switch(p->type)
		{
			case ObjectType_primitive:
				ret = TRUE;
				break;
			default:
				ret = (ObjectInfo_apiOf(p, spec) & OBJECT_API_CLONE) ? TRUE : FALSE;
				break;
		}
	}
	return ret;

}

int ObjectInfo_isComparable(ObjectInfo *p, PublishSpec *spec)
{
	int ret = FALSE;
	if (p)
	{
		switch(p->type)
		{
			case ObjectType_primitive:
			case ObjectType_enumerate:
				ret = TRUE;
				break;
			case ObjectType_defined:
				ret = ObjectInfo_isComparable(((DefinedInfo *)p->info)->origin, spec);
				break;
			case ObjectType_structure:
				ret = StructureInfo_comparable((StructureInfo *)p->info, spec);
				break;
			case ObjectType_union:
				ret = UnionInfo_comparable((UnionInfo *)p->info, spec);
				break;
			case ObjectType_array:
			case ObjectType_index:
				ret = FALSE;
			case ObjectType_extern:
			case ObjectType_reference:
				if (p->api & OBJECT_API_CMP) ret = TRUE;
				break;
			default:
				break;
		}
	}
	return ret;

}

ObjectInfo *ObjectInfo_getOrigin(ObjectInfo *p)
{
	if (p != NULL)
	{
		if (p->type == ObjectType_defined)
			p = ObjectInfo_getOrigin(((DefinedInfo *)p->info)->origin);
	}
	return p;
}

////////////////////////////////////////////////////////////////////////////////
// ObjectInfo CODEC
ObjectInfo *ObjectInfo_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo *ret = ObjectInfo_new(0, NULL, NULL, 0, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

ssize_t ObjectInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo *src = (ObjectInfo *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->name, errp), errp);
		DZ1_ENCODE1(cp, size, (u8_t)src->type, errp, ret);
		DZ1_ENCODE1(cp, size, src->srcName != NULL && strlen(src->srcName) > 0 ? 1 : 0, errp, ret);
		if (src->srcName != NULL && strlen(src->srcName) > 0)
			DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, src->srcName, errp), errp);
		DZ1_ENCODE4(cp, size, src->api, errp, ret);
		switch(src->type)
		{
		case ObjectType_primitive:
			DZ1_CODEC_FUNC(cp, size, ret, PrimitiveInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_enumerate:
			DZ1_CODEC_FUNC(cp, size, ret, EnumInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_defined:
			DZ1_CODEC_FUNC(cp, size, ret, DefinedInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_bits:
			DZ1_CODEC_FUNC(cp, size, ret, BitsInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_structure:
			DZ1_CODEC_FUNC(cp, size, ret, StructureInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_union:
			DZ1_CODEC_FUNC(cp, size, ret, UnionInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_array:
			DZ1_CODEC_FUNC(cp, size, ret, ArrayInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_index:
			DZ1_CODEC_FUNC(cp, size, ret, IndexInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_declare:
			DZ1_CODEC_FUNC(cp, size, ret, _put16str(cp, size, (str_t)src->info, errp), errp);
			break;
		case ObjectType_extern:
		case ObjectType_reference:
			DZ1_CODEC_FUNC(cp, size, ret, ExternInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_func:
			DZ1_CODEC_FUNC(cp, size, ret, FunctionInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		case ObjectType_constant:
			DZ1_CODEC_FUNC(cp, size, ret, ConstantInfo_enc(cp, size, src->info, param, errp), errp);
			break;
		default:
			break;
		}
	}
	return ret;
}

ssize_t ObjectInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	//Dz1MdefcModule *module = (Dz1MdefcModule *)param;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ObjectInfo *dst = (ObjectInfo *)_dst;
	if (src == NULL || dst == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
//		u32_t v32 = 0;
		u8_t *cp = src, v;
		DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->name, errp), errp);
		DZ1_DECODE1(&v, cp, size, errp, ret); dst->type = (ObjectType)v;

		DZ1_DECODE1(&v, cp, size, errp, ret);
		if (v) { DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, &dst->srcName, errp), errp); }

		DZ1_DECODE4(&dst->api, cp, size, errp, ret);
		switch(dst->type)
		{
		case ObjectType_primitive:
			if ((dst->info = PrimitiveInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, PrimitiveInfo_dec(dst->info, cp, size, param, errp), errp);		
			break;
		case ObjectType_enumerate:
			if ((dst->info = EnumInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, EnumInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_defined:
			if ((dst->info = DefinedInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, DefinedInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_bits:
			if ((dst->info = BitsInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, BitsInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_structure:
			if ((dst->info = StructureInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, StructureInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_union:
			if ((dst->info = UnionInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, UnionInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_array:
			if ((dst->info = ArrayInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, ArrayInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_index:
			if ((dst->info = IndexInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, IndexInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_declare:
			DZ1_CODEC_FUNC(cp, size, ret, _get16str(cp, size, (str_t *)(&dst->info), errp), errp);
			break;
		case ObjectType_extern:
		case ObjectType_reference:
			if ((dst->info = ExternInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, ExternInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_func:
			if ((dst->info = FunctionInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, FunctionInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		case ObjectType_constant:
			if ((dst->info = ConstantInfo_gen(errp)) == NULL) DZ1_CODEC_ERR_RET(errp);
			else DZ1_CODEC_FUNC(cp, size, ret, ConstantInfo_dec(dst->info, cp, size, param, errp), errp);
			break;
		default:
			break;
		}
	}
	return ret;
}
// ObjectInfo CODEC
////////////////////////////////////////////////////////////////////////////////

