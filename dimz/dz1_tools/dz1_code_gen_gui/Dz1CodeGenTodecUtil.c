#include "Dz1CodeGenTodecUtil.h"

///////////////////////////////////////////////////////////////////////////////
// Load Module
static Dz1Error _ConstructCodec_appendObj(ConstructCodec *dst, ObjectInfo *obj)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ConstructObjectEntry *node = ConstructObjectEntry_new(obj->name, obj, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ConstructObjectEntry_delAndSetNull, (void *)&node);

		if ((*errp = dst->objs->add(dst->objs, node)).code) Dz1Error_set(errp, 0);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ConstructObjectEntry_delAndSetNull, (void *)&node);
	}


	return err;
}

static Dz1Error ConstructCodec_appendObj(ConstructCodec *dst, ObjectInfo *obj)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectType type = ObjectInfo_typeOf(obj);
	switch (type)
	{
	case ObjectType_structure:
	case ObjectType_union:
	case ObjectType_array:
		if ((*errp = _ConstructCodec_appendObj(dst, obj)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		break;
	}
	return err;
}

Dz1Error ConstructCodec_initSrc(ConstructCodec *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcModule *module = NULL;
	if ((module = dst->module) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		void *c = NULL;
		if ((c = Dz1FifoCursor_new(module->objFifo, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ObjectInfo *obj;
			pthread_cleanup_push(Dz1FifoCursor_delAndSetNull, (void *)&c);

			for (Dz1FifoCursorForward(c))
			{
				if ((obj = Dz1FifoCursor_data(c)) != NULL)
				{
					if ((*errp = ConstructCodec_appendObj(dst, obj)).code) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1FifoCursor_delAndSetNull, (void *)&c);
		}
	}
	return err;
}
// Load Module
///////////////////////////////////////////////////////////////////////////////

static ConstructMemberCodecEntry *ConstructMemberCodecList_addEntry(ConstructMemberCodecList *list,
																	ConstructCodecEntry *parent,
																	u32_t order, Dz1Str name, ObjectInfo *obj,
																	ConstructMemberCodecInfo *info, Dz1Error *errp)
{
	ConstructMemberCodecEntry *ret = NULL;
	ConstructMemberCodecEntry *entry = ConstructMemberCodecEntry_new(parent, order, name, obj, info, errp);
	if (entry == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ConstructMemberCodecEntry_delAndSetNull, (void *)&entry);
		if ((*errp = list->add(list, entry)).code) ERR_OUT(errp);
		else
		{
			ret = entry;
			entry = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ConstructMemberCodecEntry_delAndSetNull, (void *)&entry);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Array INIT
static bool_t ConstructMemberCodecList_initArray(ConstructMemberCodecList *list, ObjectInfo *obj, ConstructCodecEntry *parent, Dz1Error *errp)
{
	bool_t ret = FALSE;
	if (ConstructMemberCodecList_addEntry(list, parent, 10, INSTANCE_NAME_COUNT, NULL, NULL, errp) == NULL) ERR_OUT(errp);
	else
	{
		ArrayInfo *info = obj->info;
		ObjectInfo *element = info->entry;
		if (ConstructMemberCodecList_addEntry(list, parent, 20, INSTANCE_NAME_ELEMENT, element, NULL, errp) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = TRUE;
		}
	}
	return ret;
}
// Array INIT
///////////////////////////////////////////////////////////////////////////////

typedef struct ListInitArg
{
	ConstructMemberCodecList	*list;
	ConstructCodecEntry			*parent;
	u32_t						 order;
} ListInitArg;

///////////////////////////////////////////////////////////////////////////////
// Structure INIT
static Dz1Error List_initStruct(void *ptr, StructMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ListInitArg *arg = (ListInitArg *)ptr;

	if (ConstructMemberCodecList_addEntry(arg->list, arg->parent, arg->order * 10, p->instance, p->type, NULL, errp) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
		arg->order++;
	}

	return err;
}

static bool_t ConstructMemberCodecList_initStruct(ConstructMemberCodecList *list, ObjectInfo *obj, ConstructCodecEntry *parent, Dz1Error *errp)
{
	bool_t ret = FALSE;
	StructureInfo *info = (StructureInfo *)obj->info;
	StructMemberList *members = info->members;

	ListInitArg arg = { list, parent, 1 };
	if ((*errp = members->travel(members, List_initStruct, (void *)&arg)).code) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
		ret = TRUE;
	}
	return ret;
}
// Structure INIT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union INIT
static Dz1Error List_initUnion(void *ptr, UnionMemberEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ListInitArg *arg = (ListInitArg *)ptr;

	if (ConstructMemberCodecList_addEntry(arg->list, arg->parent, arg->order * 10, p->instance, p->type, NULL, errp) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
		arg->order++;
	}

	return err;
}
static bool_t ConstructMemberCodecList_initUnion(ConstructMemberCodecList *list, ObjectInfo *obj, ConstructCodecEntry *parent, Dz1Error *errp)
{
	bool_t ret = FALSE;
	UnionInfo *info = (UnionInfo *)obj->info;
	UnionMemberList *members = info->members;

	ListInitArg arg = { list, parent, 2 };
	if (ConstructMemberCodecList_addEntry(list, parent, 10, INSTANCE_NAME_PRESENT, NULL, NULL, errp) == NULL) ERR_OUT(errp);
	else if ((*errp = members->travel(members, List_initUnion, (void *)&arg)).code) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
		ret = TRUE;
	}
	return ret;
}
// Union INIT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Append TODEC
static ConstructCodecEntry *ConstructCodecEntry_generate(ObjectInfo *obj, str_t _opt_suffix, bool_t is_public, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t opt_suffix = _opt_suffix == NULL || _opt_suffix[0] == 0 ? NULL : _opt_suffix;
	ConstructCodecEntry *node = ConstructCodecEntry_new(opt_suffix, obj, is_public, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ConstructCodecEntry_delAndSetNull, (void *)&node);

		switch(obj->type)
		{
		case ObjectType_array:
			if (ConstructMemberCodecList_initArray(node->member_codec, obj, node, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case ObjectType_structure:
			if (ConstructMemberCodecList_initStruct(node->member_codec, obj, node, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case ObjectType_union:
			if (ConstructMemberCodecList_initUnion(node->member_codec, obj, node, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(errp->code); // (ConstructCodecEntry_delAndSetNull, (void *)&node);
	}
	return node;
}

static bool_t _ConstructCodec_addTodec(ConstructObjectEntry *dst, str_t opt_suffix, bool_t is_public, Dz1MdefcModule *module, Dz1Error *errp)
{
	bool_t ret = FALSE;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ConstructCodecEntry *node = ConstructCodecEntry_generate(dst->obj, opt_suffix, is_public, errp);
		if (node == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructCodecEntry_delAndSetNull, (void *)&node);
			if ((*errp = ConstructCodecEntry_resolve(node, module)).code) ERR_OUT(errp);
			else if ((*errp = dst->codecs->add(dst->codecs, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
				ret = TRUE;
			}
			pthread_cleanup_pop(1); // (ConstructCodecEntry_delAndSetNull, (void *)&node);
		}
	}
	return ret;
}

Dz1Error ConstructCodec_addTodecByName(ConstructCodec *p, Dz1Str name, str_t opt_suffix, bool_t is_public)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL || name == NULL || name[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ConstructObjectEntry key = { name }, *node = p->objs->find(p->objs, &key);
		if (node == NULL) ERR_SET_OUT(errp, ENOENT);
		else if (_ConstructCodec_addTodec(node, opt_suffix, is_public, p->module, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1Error ConstructCodec_addTodecByObj(ConstructCodec *p, ObjectInfo *src, str_t opt_suffix, bool_t is_public)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ConstructObjectEntry key = { src->name }, *node = p->objs->find(p->objs, &key);
		if (node == NULL) ERR_SET_OUT(errp, ENOENT);
		else if (_ConstructCodec_addTodec(node, opt_suffix, is_public, p->module, errp) == FALSE) ERR_OUT(errp);
		else
		{
			p->is_dirty = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Append TODEC
///////////////////////////////////////////////////////////////////////////////

// ConstructCodecEntry *ConstructCodec_findByName(ConstructCodec *p, Dz1Str name, str_t _opt_suffix)
// {
// 	str_t opt_suffix = _opt_suffix == NULL || _opt_suffix[0] == 0 ? NULL : _opt_suffix;
// 	ConstructCodecEntry key = { name, opt_suffix };
// 	return p->dsts->find(p->dsts, &key);
// }

///////////////////////////////////////////////////////////////////////////////
// Remove TODEC
static bool_t ConstructObjectEntry_removeTodec(ConstructObjectEntry *node, str_t opt_suffix)
{
	bool_t ret = FALSE;
	ConstructCodecList *list = node->codecs;
	ConstructCodecEntry key = { opt_suffix };
	ConstructCodecEntry *entry = list->extract(list, &key);
	if (entry != NULL) 
	{
		ConstructCodecEntry_delAndSetNull(&entry);
		ret = TRUE;
	}
	return ret;
}

void ConstructCodec_removeTodecByName(ConstructCodec *p, Dz1Str name, str_t opt_suffix)
{
	ConstructObjectEntry key = { name }, *node = p->objs->find(p->objs, &key);
	if (node != NULL)
	{
		if (ConstructObjectEntry_removeTodec(node, opt_suffix)) p->is_dirty = TRUE;
	}
}

void ConstructCodec_removeTodecByObj(ConstructCodec *p, ObjectInfo *obj, str_t opt_suffix)
{
	ConstructObjectEntry key = { obj->name }, *node = p->objs->find(p->objs, &key);
	if (node != NULL)
	{
		if (ConstructObjectEntry_removeTodec(node, opt_suffix)) p->is_dirty = TRUE;
	}
}

// void ConstructCodec_removeTodecByEntry(ConstructCodec *p, ConstructCodecEntry *key)
// {
// 	ConstructCodecList *list = p->dsts;
// 	list->remove(p->dsts, key);
// }
// Remove TODEC
///////////////////////////////////////////////////////////////////////////////

static Dz1Error ObjectList_resolve(void *ptr, ConstructObjectEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcModule *module = (Dz1MdefcModule *)ptr;
	if ((*errp = ConstructObjectEntry_resolve(p, module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error ConstructObjectList_resolve(ConstructObjectList *list, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = list->travel(list, ObjectList_resolve, (void *)module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error ConstructCodec_resolve(ConstructCodec *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || dst->module == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = ConstructObjectList_resolve(dst->objs, dst->module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Resolve CODEC List
typedef struct CodecListResolvArg
{
	ObjectInfo				*obj;
	Dz1MdefcModule			*module;
} CodecListResolvArg;

static Dz1Error CodecList_resolve(void *ptr, ConstructCodecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecListResolvArg *arg = (CodecListResolvArg *)ptr;
	p->parent_obj = arg->obj;
	if ((*errp = ConstructCodecEntry_resolve(p, arg->module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error ConstructCodecList_resolve(ConstructCodecList *list, ObjectInfo *obj, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (list == NULL || obj == NULL || module == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		CodecListResolvArg arg = { obj, module };
		if ((*errp = list->travel(list, CodecList_resolve, (void *)&arg)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
// Resolve CODEC List
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Resolve Object Entry
Dz1Error ConstructObjectEntry_resolve(ConstructObjectEntry *p, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL || module == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->obj == NULL)
	{
		if ((p->obj = module->findObject(module, p->obj_name)) == NULL) { Dz1Error_set(errp, 0); }
		else if ((*errp = ConstructCodecList_resolve(p->codecs, p->obj, module)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((*errp = ConstructCodecList_resolve(p->codecs, p->obj, module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Resolve Object Entry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member List Resolve
static Dz1Error MemberCodecList_resolve(void *ptr, ConstructMemberCodecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcModule *module = (Dz1MdefcModule *)ptr;

	if ((*errp = ConstructMemberCodecEntry_resolve(p, module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error ConstructMemberCodecList_resolve(ConstructMemberCodecList *list, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = list->travel(list, MemberCodecList_resolve, (void *)module)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Member List Resolve
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Resolve CODEC Entry
Dz1Error ConstructCodecEntry_resolve(ConstructCodecEntry *p, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL || module == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->parent_obj == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((*errp = ConstructMemberCodecList_resolve(p->member_codec, module)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
// Resolve CODEC Entry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member Find By Name
typedef struct MemberCodecListFindByNameArg
{
	str_t name;
	ConstructMemberCodecEntry *ret;
} MemberCodecListFindByNameArg;

static Dz1Error MemberCodecList_findByName(void *ptr, ConstructMemberCodecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MemberCodecListFindByNameArg *arg = (MemberCodecListFindByNameArg *)ptr;
	if (Dz1STRCMP(arg->name, p->instance_name) == 0)
	{
		arg->ret = p;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

ConstructMemberCodecEntry *ConstructMemberCodecList_findByName(ConstructMemberCodecList *list, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ConstructMemberCodecEntry *ret = NULL;
	if (list != NULL && name != NULL && name[0] != 0)
	{
		MemberCodecListFindByNameArg arg = { name, NULL };
		list->travel(list, MemberCodecList_findByName, (void *)&arg);
		ret = arg.ret;
	}
	return ret;
}
// Member Find By Name
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member Set Info
Dz1Error ConstructMemberCodecEntry_setInfo(ConstructMemberCodecEntry *dst, ConstructMemberCodecInfo *info)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ConstructMemberCodecInfo_delAndSetNull(&dst->info);
		dst->info;
	}
	return err;
}
// Member Set Info
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Get Description
typedef struct CodecInfoGetDescriptMap
{
	int										 present;
	Dz1Error								(*GetDescript)(void *ptr, Dz1Str buf, size_t sz);
} CodecInfoGetDescriptMap;
static CodecInfoGetDescriptMap *CodecInfoGetDescriptMap_find(CodecInfoGetDescriptMap *table, int present)
{
	CodecInfoGetDescriptMap *i;
	for (i = table; i->GetDescript != NULL; i++)
		if (i->present == present) return i;
	return i;
}

static Dz1Error CodecPrimitiveByte_getDescript(void *ptr, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecPrimitiveByte *p = (CodecPrimitiveByte *)ptr;
	u64_t v = 0;
	u32_t len = p->byte_len;
	u32_t sft = p->byte_sft;
	while(len)
	{
		v = (v << 8) | 0xFF;
		len--;
	}									// 0xFF			pos = 0
	while(sft) { v <<= 8; sft--; }		// 0xFF0000		pos = 0
	snprintf(buf, sz, DZ1_FMT64X Dz1T(">>%u"), v, p->byte_sft << 3);
	return err;
}

static Dz1Error CodecPrimitiveBits_getDescript(void *ptr, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecPrimitiveBits *p = (CodecPrimitiveBits *)ptr;
	u64_t v = 0;
	u32_t len = p->bit_len;
	u32_t sft = p->bit_sft;
	while(len)
	{
		v = (v << 1) | 0x1;
		len--;
	}									// 0xFF			pos = 0
	while(sft) { v <<= 1; sft--; }		// 0xFF0000		pos = 0
	snprintf(buf, sz, DZ1_FMT64X  Dz1T(">>%u"), v, p->bit_sft);
	return err;
}

static Dz1Error alt_getDescript(void *ptr, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Str alt_name = (Dz1Str)ptr;
	snprintf(buf, sz, "Read/Write via %s_*", alt_name);
	return err;
}

static CodecInfoGetDescriptMap codecInfoLimitedGetDescriptMap[] =
{
	{ ConstructMemberCodecLimitedInfoPresent_byte_of_primitive,	CodecPrimitiveByte_getDescript },
	{ ConstructMemberCodecLimitedInfoPresent_bits_of_primitive,	CodecPrimitiveBits_getDescript },
	{ ConstructMemberCodecLimitedInfoPresent_alternate,			alt_getDescript },
	{ ConstructMemberCodecLimitedInfoPresent_max, NULL }
};

static Dz1Error ConstructMemberCodecLimitedInfo_getDescript(ConstructMemberCodecLimitedInfo *p, Dz1Str instance, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecInfoGetDescriptMap *map = CodecInfoGetDescriptMap_find(codecInfoLimitedGetDescriptMap, p->present);
	if (map == NULL) snprintf(buf, sz, "#error");
	else if ((*errp = map->GetDescript(p->x.__ptr__, buf, sz)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;	
}

static Dz1Error CodecOneOfConstruct_getDescript(void *ptr, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *obj = NULL;
	ConstructMemberCodecLimitedInfo *info = NULL;
	CodecOneOfConstruct *p = (CodecOneOfConstruct *)ptr;
	if ((info = p->info) != NULL)
		ConstructMemberCodecLimitedInfo_getDescript(info, p->instance_name, buf, sz);
	else if ((obj = p->obj) != NULL)
		snprintf(buf, sz, "Read/Write of %s", obj->name);
	else snprintf(buf, sz, "#invalid");
	return err;	
}

static Dz1Error void_getDescript(void *ptr, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	snprintf(buf, sz, "no read/write");
	return err;
}

static Dz1Error CodecPadding_getDescript(void *ptr, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecPadding *p = (CodecPadding *)ptr;
	if ((p->bit_len & 0x7) == 0)
		snprintf(buf, sz, "padding %u byte", p->bit_len >> 3);
	else snprintf(buf, sz, "padding %u bit", p->bit_len);
	return err;
}

static CodecInfoGetDescriptMap codecInfoGetDescriptMap[] =
{
	{ ConstructMemberCodecInfoPresent_one_of_structure,  CodecOneOfConstruct_getDescript },
	{ ConstructMemberCodecInfoPresent_byte_of_primitive, CodecPrimitiveByte_getDescript },
	{ ConstructMemberCodecInfoPresent_bits_of_primitive, CodecPrimitiveBits_getDescript },
	{ ConstructMemberCodecInfoPresent_void_member,		 void_getDescript },
	{ ConstructMemberCodecInfoPresent_alternate,		 alt_getDescript },
	{ ConstructMemberCodecInfoPresent_padding,			 CodecPadding_getDescript },
	{ ConstructMemberCodecInfoPresent_max, NULL }
};

static Dz1Error ConstructMemberCodecInfo_getDescript(ConstructMemberCodecInfo *p, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	CodecInfoGetDescriptMap *map = CodecInfoGetDescriptMap_find(codecInfoGetDescriptMap, p->present);
	if (map == NULL) snprintf(buf, sz, "#error");
	else if ((*errp = map->GetDescript(p->x.__ptr__, buf, sz)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

Dz1Error ConstructMemberCodecEntry_getDescript(ConstructMemberCodecEntry *p, Dz1Str endian, Dz1Str buf, size_t sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ObjectInfo *obj = NULL;
	ConstructMemberCodecInfo *info = NULL;
	if (p == NULL) snprintf(buf, sz, "NULL");
	else if ((info = p->info) != NULL)
	{
		if ((*errp = ConstructMemberCodecInfo_getDescript(info, buf, sz)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	// *** info == NULL ***
	else if ((obj = p->obj) != NULL)
	{	// Read/Write of obj_name
		PrimitiveInfo *pfx_info = NULL;
		ObjectType type = ObjectInfo_typeOf(obj);
		switch(type)
		{
		case ObjectType_primitive:				// PrimitiveInfo
			if ((pfx_info = (PrimitiveInfo *)obj->info) == NULL)
				snprintf(buf, sz, "#invalid:%s", obj->name);
			else if (pfx_info->storage == NativeStorage_address)
			{
				if (pfx_info->prefix != NULL && pfx_info->prefix[0] != 0)
					snprintf(buf, sz, "DZ1_IO_STREAM_FUNC(ret, %s_read(&dst->%s, src, param, errp), errp);", pfx_info->prefix, p->instance_name);
				else snprintf(buf, sz, "DZ1_IO_STREAM_FUNC(ret, %s_read(&dst->%s, src, param, errp), errp);", pfx_info->native, p->instance_name);
			}
			else if (Dz1STRSTR(pfx_info->native, Dz1Text("64") )) snprintf(buf, sz, "DZ1_STREAM_READ8(&dst->%s, src, %s, errp), errp);", p->instance_name, endian);
			else if (Dz1STRSTR(pfx_info->native, Dz1Text("32") )) snprintf(buf, sz, "DZ1_STREAM_READ4(&dst->%s, src, %s, errp), errp);", p->instance_name, endian);
			else if (Dz1STRSTR(pfx_info->native, Dz1Text("16") )) snprintf(buf, sz, "DZ1_STREAM_READ2(&dst->%s, src, %s, errp), errp);", p->instance_name, endian);
			else if (Dz1STRSTR(pfx_info->native, Dz1Text("8") )) snprintf(buf, sz, "DZ1_STREAM_READ1(&dst->%s, src, %s, errp), errp);", p->instance_name, endian);
			else snprintf(buf, sz, "DZ1_IO_STREAM_FUNC(ret, %s_read(&dst->%s, src, param, errp), errp);", pfx_info->native, p->instance_name);
			break;
		case ObjectType_enumerate:				// EnumInfo
			if (p->info != NULL)
			{
				if ((*errp = ConstructMemberCodecInfo_getDescript(p->info, buf, sz)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			else snprintf(buf, sz, "DZ1_STREAM_READ4(&v32, src, param, errp); dst->%s = (%s)v32", p->instance_name, obj->name);
			break;
		case ObjectType_defined:				// DefinedInfo
			snprintf(buf, sz, "not support(defined)");
			break;
		case ObjectType_bits:					// BitsInfo
			snprintf(buf, sz, "not support(bits)");
			break;
		case ObjectType_structure:				// StructureInfo
		case ObjectType_union:					// UnionInfo
			snprintf(buf, sz, "if ((dst->%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1); else DZ1_IO_STREAM_FUNC(ret, %s_read(dst->%s, src, param, errp), errp);",
					p->instance_name, obj->name, obj->name, p->instance_name);
			break;
		case ObjectType_array:					// ArrayInfo
			snprintf(buf, sz, "DZ1_IO_STREAM_FUNC(ret, %s_read(dst->%s, src, param, errp), errp);", obj->name, p->instance_name);
			break;
		case ObjectType_declare:				// str_t				선행 정의용
			snprintf(buf, sz, "not support(declare:%s %s)", obj->name, p->instance_name);
			break;
		case ObjectType_extern:					// ExternInfo			외부 정의 타입
		case ObjectType_reference:				// ExternInfo			헤더에서 인클루드할 경우
												//						인클루드 순환이 발생하는 타입
			snprintf(buf, sz, "if ((dst->%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1); else DZ1_IO_STREAM_FUNC(ret, %s_read(dst->%s, src, param, errp), errp);",
					p->instance_name, ((ExternInfo *)obj->info)->prefix, ((ExternInfo *)obj->info)->prefix, p->instance_name);
			Dz1Error_set(errp, 0);
			break;
		case ObjectType_func:					// FunctionInfo
		case ObjectType_index:					// IndexInfo
			snprintf(buf, sz, "not support(%s:%s %s)", ObjectTypeStr(type), obj->name, p->instance_name);
			break;
		default:
			snprintf(buf, sz, "unknown(%s(%d):%s %s)", ObjectTypeStr(type), type, obj->name, p->instance_name);
			break;
		}
		Dz1Error_set(errp, 0);
	}
	// *** info == NULL && obj == NULL ***
	else if (p->instance_name == NULL) snprintf(buf, sz, "#invalid");
	else if (Dz1STRCMP(p->instance_name, INSTANCE_NAME_PRESENT) == 0)
	{
		snprintf(buf, sz, "DZ1_STREAM_READ4(&v32, src, param, errp); dst->present = (%sPresent)v32", obj->name);
	}
	else if (Dz1STRCMP(p->instance_name, INSTANCE_NAME_COUNT) == 0)
	{
		snprintf(buf, sz, "Read/Write 4Byte(32bit)");
	}
	else if (Dz1STRCMP(p->instance_name, INSTANCE_NAME_ELEMENT) == 0)
	{
		snprintf(buf, sz, "#invalid");
	}
	else snprintf(buf, sz, "#unknown");
	return err;
}
// Get Description
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member Object Resolve
static Dz1Error CodecEntry_resolvObject(ConstructMemberCodecEntry *p, Dz1MdefcModule *module, bool_t *need_resolv_info)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ConstructCodecEntry *parent = p->parent;
	ObjectInfo *pObj = parent->parent_obj;
	if (pObj == NULL)
	pObj = ObjectInfo_getOrigin(pObj);

	if (p->instance_name[0] == Dz1Text('@'))
	{
		if (Dz1STRCMP(p->instance_name, INSTANCE_NAME_PRESENT) == 0)
		{
			if (pObj->type != ObjectType_union)
			{
				p->obj = NULL;
				Dz1Error_set(errp, 0);
				// ERR_SET_OUT(errp, EINVAL);
			}
			else if ((p->obj = module->findObject(module, Dz1Text("int32") )) == NULL) ERR_SET_OUT(errp, ENOENT);
			else
			{
				*need_resolv_info = FALSE;
				Dz1Error_set(errp, 0);
			}
		}
		else if (Dz1STRCMP(p->instance_name, INSTANCE_NAME_ELEMENT) == 0)
		{
			if (pObj->type != ObjectType_array)
			{
				p->obj = NULL;
				Dz1Error_set(errp, 0);
				// ERR_SET_OUT(errp, EINVAL);
			}
			else
			{
				ArrayInfo *info = (ArrayInfo *)pObj->info;
				if ((p->obj = info->entry) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{	// list element type은 info에 One of Construct을 사용 할 수 없음
					*need_resolv_info = FALSE;
					Dz1Error_set(errp, 0);
				}
			}
		}
		else if (Dz1STRCMP(p->instance_name, INSTANCE_NAME_COUNT) == 0)
		{
			if (pObj->type != ObjectType_array)
			{
				p->obj = NULL;
				Dz1Error_set(errp, 0);
				// ERR_SET_OUT(errp, EINVAL);
			}
			else if ((p->obj = module->findObject(module, Dz1Text("uint32") )) == NULL) ERR_SET_OUT(errp, ENOENT);
			else
			{
				*need_resolv_info = FALSE;
				Dz1Error_set(errp, 0);
			}
		}
		else if (Dz1STRCMP(p->instance_name, INSTANCE_NAME_PAD) == 0)
		{
			if ((p->obj = module->findObject(module, Dz1Text("uint8") )) == NULL) ERR_SET_OUT(errp, ENOENT);
			else
			{
				*need_resolv_info = FALSE;
				Dz1Error_set(errp, 0);
			}
		}
	}
	// member of construct
	else if (pObj->type == ObjectType_structure)
	{
		StructureInfo *info = (StructureInfo *)pObj->info;
		StructMemberList *members = info->members;
		StructMemberEntry *member = members->find(members, p->instance_name);
		if (member == NULL)
		{
			p->obj = NULL;
			(*need_resolv_info) = FALSE;
		}
		else if ((p->obj = member->type) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ObjectInfo *instance_obj = ObjectInfo_getOrigin(p->obj);
			if (instance_obj->type == ObjectType_structure) (*need_resolv_info) = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	else if (pObj->type == ObjectType_union)
	{
		UnionInfo *info = (UnionInfo *)pObj->info;
		UnionMemberList *members = info->members;
		UnionMemberEntry *member = members->find(members, p->instance_name);
		if (member == NULL)
		{
			p->obj = NULL;
			(*need_resolv_info) = FALSE;
		}
		else if ((p->obj = member->type) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ObjectInfo *instance_obj = ObjectInfo_getOrigin(p->obj);
			if (instance_obj->type == ObjectType_structure) (*need_resolv_info) = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}
// Member Object Resolve
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member Info Resolve
static Dz1Error CodecEntry_resolvInfo(ConstructMemberCodecInfo *p, Dz1MdefcModule *module, ObjectInfo *obj)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->present == ConstructMemberCodecInfoPresent_one_of_structure)
	{
		CodecOneOfConstruct *dst = p->x.one_of_structure;
		if (obj->type == ObjectType_structure)
		{
			StructureInfo *info = (StructureInfo *)obj->info;
			StructMemberList *members = info->members;
			StructMemberEntry *member = members->find(members, dst->instance_name);
			if ((dst->obj = member->type) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (obj->type == ObjectType_union)
		{
			UnionInfo *info = (UnionInfo *)obj->info;
			UnionMemberList *members = info->members;
			UnionMemberEntry *member = members->find(members, dst->instance_name);
			if ((dst->obj = member->type) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}
// Member Info Resolve
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member Resolve
Dz1Error ConstructMemberCodecEntry_resolve(ConstructMemberCodecEntry *p, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t need_resolv_info = FALSE;
	if ((*errp = CodecEntry_resolvObject(p, module, &need_resolv_info)).code) ERR_OUT(errp);
	else if (need_resolv_info && p->info != NULL)
	{
		if ((*errp = CodecEntry_resolvInfo(p->info, module, p->obj)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);
	return err;
}
// Member Resolve
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Set Parent
static Dz1Error CodecOneOfConstruct_setParent(void *ptr, ConstructMemberCodecEntry *entry)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecOneOfConstruct *p = (CodecOneOfConstruct *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		p->parent = entry;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error CodecPrimitiveByte_setParent(void *ptr, ConstructMemberCodecEntry *entry)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecPrimitiveByte *p = (CodecPrimitiveByte *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		p->parent = entry;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error CodecPrimitiveBits_setParent(void *ptr, ConstructMemberCodecEntry *entry)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecPrimitiveBits *p = (CodecPrimitiveBits *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		p->parent = entry;
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error CodecPadding_setParent(void *ptr, ConstructMemberCodecEntry *entry)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecPadding *p = (CodecPadding *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		p->parent = entry;
		Dz1Error_set(errp, 0);
	}
	return err;
}

typedef struct InfoSetParentMap
{
	ConstructMemberCodecInfoPresent		 present;
	Dz1Error (*setParent)(void *ptr, ConstructMemberCodecEntry *entry);
} InfoSetParentMap;

static InfoSetParentMap infoSetParentMap[] = 
{
	{ ConstructMemberCodecInfoPresent_one_of_structure,		CodecOneOfConstruct_setParent },
	{ ConstructMemberCodecInfoPresent_byte_of_primitive,	CodecPrimitiveByte_setParent },
	{ ConstructMemberCodecInfoPresent_bits_of_primitive,	CodecPrimitiveBits_setParent },
	{ ConstructMemberCodecInfoPresent_padding,				CodecPadding_setParent },
	{ ConstructMemberCodecInfoPresent_max, NULL }
};

static InfoSetParentMap *InfoSetParentMap_find(ConstructMemberCodecInfoPresent v)
{
	InfoSetParentMap *i = NULL;
	for (i = infoSetParentMap; i->present != ConstructMemberCodecInfoPresent_max; i++)
		if (i->present == v) return i;
	return NULL;
}

Dz1Error ConstructMemberCodecInfo_setParent(ConstructMemberCodecInfo *p, ConstructMemberCodecEntry *entry)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	InfoSetParentMap *map = NULL;
	if (p == NULL || entry == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((map = InfoSetParentMap_find(p->present)) != NULL)
	{
		if ((*errp = map->setParent(p->x.__ptr__, entry)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
// Set Parent
///////////////////////////////////////////////////////////////////////////////


