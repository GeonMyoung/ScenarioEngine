#include "dz1_todec.h"

/*
static Dz1Error _publish_structure_gen_src(FILE *fp, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int tab = 0;
	str_t name = tgt->name;
	str_t str_mode = mode == Dz1TodecTargetCodecMode_private ? "static " : "";

	u32_t cnt = 0;
	StructureInfo *info = (StructureInfo *)tgt->info;
	StructMemberList *list = info->members;
	StructMemberEntry **arr = list->get_array(list, &cnt, errp);

	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		StructMemberEntry *e = NULL;

		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);

		Dz1Thread_ftprintf(fp, tab, "%s%s *%s_gen(Dz1Error *err)" NEW_LINE, str_mode, name, name);
		Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_DECLARE(errp, err);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "%s *ret = %s_new(", name, name);
		for (i = 0; i < cnt; i++)
		{
			e = arr[i];
			if (e->argInvolve)
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
		Dz1Thread_ftprintf(fp, tab, "else Dz1Error_set(errp, 0);" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
		Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	}
	return err;
}

static Dz1Error _publish_union_gen_src(FILE *fp, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	str_t name = tgt->name;
	str_t str_mode = mode == Dz1TodecTargetCodecMode_public ? "" : "static ";
	Dz1Thread_ftprintf(fp, tab, "%s%s *%s_gen(Dz1Error *err)" NEW_LINE, str_mode, name, name);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_PTR(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "%s *ret = %s_new(%sPresent_max, NULL, errp);" NEW_LINE, name, name, name);
	Dz1Thread_ftprintf(fp, tab, "if (ret == NULL) ERR_OUT(errp);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else Dz1Error_set(errp, 0);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return err;
}

static Dz1Error _publish_array_gen_src(FILE *fp, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	str_t name = tgt->name;
	str_t str_mode = mode == Dz1TodecTargetCodecMode_public ? "" : "static ";
	Dz1Thread_ftprintf(fp, tab, "%s%s *%s_gen(Dz1Error *err)" NEW_LINE, str_mode, name, name);
	Dz1Thread_ftprintf(fp, tab++, "{" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "DZ1_ERROR_SAFE_DECLARE(errp, err);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "%s *ret = %s_new(errp);" NEW_LINE, name, name);
	Dz1Thread_ftprintf(fp, tab, "if (ret == NULL) ERR_OUT(errp);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "else Dz1Error_set(errp, 0);" NEW_LINE);
	Dz1Thread_ftprintf(fp, tab, "return ret;" NEW_LINE);
	Dz1Thread_ftprintf(fp, --tab, "}" NEW_LINE NEW_LINE);
	return err;
}

static Dz1Error _publish_gen_hdr(FILE *fp, Dz1TodecTargetCodecMode mode, ObjectInfo *tgt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (mode == Dz1TodecTargetCodecMode_public)
	{
		str_t name = tgt->name;
		Dz1Thread_fprintf(fp, "DZ1_CPPLINK %s *%s_gen(Dz1Error *err);" NEW_LINE, name, name);
	}
	return err;
}

static ObjectTypeGenPublishApi objectTypeGenPublishApi[] =
{
	{ ObjectType_structure, _publish_structure_gen_src, _publish_gen_hdr },
	{ ObjectType_union,		_publish_union_gen_src,		_publish_gen_hdr },
	{ ObjectType_array,		_publish_array_gen_src,		_publish_gen_hdr },
	{ ObjectType_index,		_publish_array_gen_src,		_publish_gen_hdr },
	{ ObjectType_max, NULL },
};

ObjectTypeGenPublishApi *ObjectTypeGenPublishApi_find(ObjectType type)
{
	ObjectTypeGenPublishApi *i;
	for (i = objectTypeGenPublishApi; i->type != ObjectType_max; i++)
		if (i->type == type) return i;
	return NULL;
}
*/

int dz1_todec_pub_gen_avoid_no_symbol_warning = 0;
