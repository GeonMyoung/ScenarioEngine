#include <dz1_tdq.h>
#include "dz1_tdqc_util.h"

void Dz1TdqcTblInstance_dump(Dz1TdqcTblInstance *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	else
	{
		Dz1Thread_printf("%s(%s) = {\n", p->name, p->prefix); tab++;

		if (p->shape == NULL) Dz1Thread_tprintf(tab, "shape = NULL\n");
		else Dz1Thread_tprintf(tab, "shape = %s\n", p->shape->name);

		if (p->fks != NULL && p->fks->count(p->fks) > 0)
		{ 
			Dz1Thread_tprintf(tab, "fks = "); 
			Dz1TdqFKList_dump(p->fks, tab);
		}

		Dz1Thread_tprintf(--tab, "}\n");
	}
}

Dz1TdqcShapeOptEntry *Dz1TdqcShapeOptList_findByName(Dz1TdqcShapeOptList *list, Dz1Str instance)
{
	Dz1TdqcShapeOptEntry *ret = NULL;
	if (list != NULL && Dz1Str_isVoid(instance) == FALSE)
	{
		Dz1TdqcShapeOptEntry key = { instance };
		ret = list->find(list, &key);
	}
	return ret;
}

bool_t Dz1TdqcShapeOptList_appendOpt(Dz1TdqcShapeOptList *opts, Dz1Str instance, Dz1Str api_prefix, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcShapeOptEntry *node = Dz1TdqcShapeOptEntry_new(instance, api_prefix, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&node);
		if ((*errp = opts->add(opts, node)).code) ERR_OUT(errp);
		else 
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// FindObject from Modules
typedef struct ModuleListFindObjectArg
{
	ObjectInfo *ret;
	Dz1Str name;
} ModuleListFindObjectArg;

static Dz1Error ModuleList_findObject(void *ptr, Dz1MdefcModule *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ModuleListFindObjectArg *arg = (ModuleListFindObjectArg *)ptr;
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "@@@ find object %s from %s...", arg->name, p->name);
	if ((arg->ret = p->findObject(p, arg->name)) != NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW,"found");
		Dz1Error_set(errp, EEXIST);
	}
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW,"\n");
	return err;
}

ObjectInfo *Dz1MdefcModuleList_findObject(Dz1MdefcModuleList *list, Dz1Str name)
{
	ObjectInfo *ret = NULL;
	if (list != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		ModuleListFindObjectArg arg = { NULL, name };
		list->travel(list, ModuleList_findObject, (void *)&arg);
		ret = arg.ret;
	}
	return ret;
}
// FindObject from Modules
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Table Append
static void Target_appendTblCancel(void *ptr)
{
	Dz1ListAddCancelArg *arg = (Dz1ListAddCancelArg *)ptr;
	Dz1TdqTblInstanceList *list = (Dz1TdqTblInstanceList *)arg->list;
	Dz1TdqTblInstance **node = (Dz1TdqTblInstance **)arg->node;
	if (list && node && *node) list->extract(list, *node);
}

bool_t Dz1TdqcTarget_appendTbl(Dz1TdqcTarget *dst, Dz1TdqcTblInstance *tbl, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcTblInstanceList *tables = NULL;
	Dz1TdqcTblInstanceSeq *tblseq = NULL;
	if (dst == NULL || tbl == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((tables = dst->tables) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((tblseq = dst->tblseq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = tables->add(tables, tbl)).code) ERR_OUT(errp);
	else
	{
		Dz1ListAddCancelArg arg = { tables, &tbl };
		pthread_cleanup_push(Target_appendTblCancel, (void *)&arg);
		if ((*errp = tblseq->add(tblseq, tbl)).code) ERR_OUT(errp);
		else
		{
			tbl = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Target_appendTblCancel, (void *)&arg);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Table Append
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Find Utility
Dz1TdqcShape *Dz1TdqcShapeList_findByName(Dz1TdqcShapeList *list, Dz1Str name)
{
	Dz1TdqcShape *ret = NULL;
	if (list != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqcShape key = { name };
		ret = list->find(list, &key);
	}
	return ret;
}

Dz1TdqTblShape *Dz1TdqcShapeList_findShapeByName(Dz1TdqcShapeList *list, Dz1Str name)
{
	Dz1TdqTblShape *ret = NULL;
	Dz1TdqcShape *node = Dz1TdqcShapeList_findByName(list, name);
	if (node != NULL) ret = node->target;
	return ret;
}

Dz1TdqcTblInstance *Dz1TdqcTblInstanceList_findByName(Dz1TdqcTblInstanceList *list, Dz1Str name)
{
	Dz1TdqcTblInstance *ret = NULL;
	if (list != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqcTblInstance key = { name };
		ret = list->find(list, &key);
	}
	return ret;
}

Dz1TdqcTblInstance *Dz1TdqcTarget_findTableByName(Dz1TdqcTarget *dst, Dz1Str name)
{
	Dz1TdqcTblInstance *ret = NULL;
	if (dst != NULL)
		ret = Dz1TdqcTblInstanceList_findByName(dst->tables, name);
	return ret;
}
// Find Utility
///////////////////////////////////////////////////////////////////////////////

typedef void *(*opt_clone_func)(void *src, Dz1Error *err);
typedef struct Dz1TdqSqlTypeSpecMap
{
	Dz1Str							 native;
	Dz1TdqSqlTypeSpecPresent		 present;
	void							*opt;
	opt_clone_func					 opt_clone; 
} Dz1TdqSqlTypeSpecMap;

static Dz1TdqSqlTypeSpecMap *Dz1TdqSqlTypeSpecMap_find(Dz1TdqSqlTypeSpecMap *tbl, Dz1Str native)
{
	Dz1TdqSqlTypeSpecMap *i;
	for (i = tbl; i->native != NULL; i++)
		if (Dz1STRCMP(native, i->native) == 0) return i;
	return NULL;
}

// static Dz1TdqSqlNumSpec _def_num_spec = { DZ1INT64(-1), FALSE };
static Dz1TdqSqlRealSpec _def_real_spec = { DZ1INT64(-1) };
static Dz1TdqSqlStrSpec _def_str_spec = { 127 };
static Dz1TdqSqlTypeSpecMap prim_map[] =
{
	{ Dz1Text("s8_t"),		Dz1TdqSqlTypeSpecPresent_num_s8, NULL, NULL },
	{ Dz1Text("u8_t"),		Dz1TdqSqlTypeSpecPresent_num_u8, NULL, NULL },
	{ Dz1Text("int8"),		Dz1TdqSqlTypeSpecPresent_num_s8, NULL, NULL },
	{ Dz1Text("uint8"),		Dz1TdqSqlTypeSpecPresent_num_u8, NULL, NULL },

	{ Dz1Text("s16_t"),		Dz1TdqSqlTypeSpecPresent_num_s16, NULL, NULL },
	{ Dz1Text("u16_t"),		Dz1TdqSqlTypeSpecPresent_num_u16, NULL, NULL },
	{ Dz1Text("int16"),		Dz1TdqSqlTypeSpecPresent_num_s16, NULL, NULL },
	{ Dz1Text("uint16"),	Dz1TdqSqlTypeSpecPresent_num_u16, NULL, NULL },

	{ Dz1Text("s32_t"),		Dz1TdqSqlTypeSpecPresent_num_s32, NULL, NULL },
	{ Dz1Text("u32_t"),		Dz1TdqSqlTypeSpecPresent_num_u32, NULL, NULL },
	{ Dz1Text("int32"),		Dz1TdqSqlTypeSpecPresent_num_s32, NULL, NULL },
	{ Dz1Text("uint32"),	Dz1TdqSqlTypeSpecPresent_num_u32, NULL, NULL },
	{ Dz1Text("bool_t"),	Dz1TdqSqlTypeSpecPresent_num_u32, NULL, NULL },

	{ Dz1Text("s64_t"),		Dz1TdqSqlTypeSpecPresent_num_s64, NULL, NULL },
	{ Dz1Text("u64_t"),		Dz1TdqSqlTypeSpecPresent_num_u64, NULL, NULL },
	{ Dz1Text("int64"),		Dz1TdqSqlTypeSpecPresent_num_s64, NULL, NULL },
	{ Dz1Text("uint64"),	Dz1TdqSqlTypeSpecPresent_num_u64, NULL, NULL },

	{ Dz1Text("real"),		Dz1TdqSqlTypeSpecPresent_num_r64, &_def_real_spec, (opt_clone_func)Dz1TdqSqlRealSpec_clone },
	{ Dz1Text("real64"),	Dz1TdqSqlTypeSpecPresent_num_r64, &_def_real_spec, (opt_clone_func)Dz1TdqSqlRealSpec_clone },
	{ Dz1Text("real64_t"),	Dz1TdqSqlTypeSpecPresent_num_r64, &_def_real_spec, (opt_clone_func)Dz1TdqSqlRealSpec_clone },
	{ Dz1Text("float"),		Dz1TdqSqlTypeSpecPresent_num_r32, &_def_real_spec, (opt_clone_func)Dz1TdqSqlRealSpec_clone },

	{ Dz1Text("time"),		Dz1TdqSqlTypeSpecPresent_stamp, NULL, NULL },
	{ Dz1Text("time_t"),	Dz1TdqSqlTypeSpecPresent_stamp, NULL, NULL },

	{ Dz1Text("str"),		Dz1TdqSqlTypeSpecPresent_vstring, &_def_str_spec, (opt_clone_func)Dz1TdqSqlStrSpec_clone },
	{ Dz1Text("TString"),	Dz1TdqSqlTypeSpecPresent_vtstring, &_def_str_spec, (opt_clone_func)Dz1TdqSqlStrSpec_clone },
	{ Dz1Text("Dz1Str"),	Dz1TdqSqlTypeSpecPresent_vtstring, &_def_str_spec, (opt_clone_func)Dz1TdqSqlStrSpec_clone },

	{ NULL, Dz1TdqSqlTypeSpecPresent_max }
};

static Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_genFromPrimitive(ObjectInfo *tgt, ObjectInfo *ori, Dz1Error *errp)
{
	Dz1TdqSqlTypeSpec *ret = NULL;
	PrimitiveInfo *info =  (PrimitiveInfo *)ori->info;
	Dz1TdqSqlTypeSpecMap *map = NULL;
	if ((map = Dz1TdqSqlTypeSpecMap_find(prim_map, info->native)) == NULL) 
	{
		Dz1Thread_printf("!!! %s does not support\n", info->native);
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if ((ret = Dz1TdqSqlTypeSpec_new(map->present, NULL, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		pthread_cleanup_push(Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
		if (map->opt_clone != NULL && (ret->x.__ptr__ = map->opt_clone(map->opt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_genFromEnumerate(ObjectInfo *tgt, ObjectInfo *ori, Dz1Error *errp)
{
	Dz1TdqSqlTypeSpec *ret = NULL;
	if ((ret = Dz1TdqSqlTypeSpec_new(Dz1TdqSqlTypeSpecPresent_num_s64, NULL, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		Dz1Error_set(errp, 0);
// 		pthread_cleanup_push(Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
// 		if ((ret->x.__ptr__ = Dz1TdqSqlNumSpec_clone(&_def_num_spec, errp)) == NULL) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1TdqSqlBlobSpec _def_blob_spec = Dz1TdqSqlBlobSpec_embedded;
static Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_genFromExtern(ObjectInfo *tgt, ObjectInfo *ori, Dz1Str instance, Dz1TdqcShapeOptEntry **ret_opt, Dz1Error *errp)
{
	Dz1TdqSqlTypeSpec *ret = NULL;
	ExternInfo *info =  (ExternInfo *)ori->info;
	Dz1Str bin_name = Dz1Text("Dz1Binary");
	if (Dz1STRNCMP(ori->name, bin_name, Dz1STRLEN(bin_name)) == 0)
	{	// blob
		if ((ret = Dz1TdqSqlTypeSpec_new(Dz1TdqSqlTypeSpecPresent_blob, &_def_blob_spec, errp)) == NULL) ERR_OUT(errp);
		else 
		{
			pthread_cleanup_push(Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
			if (( (*ret_opt) = Dz1TdqcShapeOptEntry_new(instance, Dz1Text("Dz1BinaryDB"), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1TdqSqlTypeSpec_delAndSetNull, (void *)&ret);
		}
	}
	else
	{	// Free Type
		if ((ret = Dz1TdqSqlTypeSpec_new(Dz1TdqSqlTypeSpecPresent_max, NULL, errp)) == NULL) ERR_OUT(errp);
		else  Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1TdqSqlTypeSpec *Dz1TdqSqlTypeSpec_genFromInfo(StructMemberEntry *info, Dz1TdqcShapeOptEntry **ret_opt, Dz1Error *errp)
{
	Dz1TdqSqlTypeSpec *ret = NULL;
	ObjectInfo *ori = ObjectInfo_getOrigin(info->type);
	switch(ori->type)
	{
	case ObjectType_primitive:				// PrimitiveInfo
		if (info->isPointer)
		{
			Dz1Thread_printf("Primitive type Pointer Member : %s\n", info->instance);
			ERR_SET_OUT(errp, EINVAL);
		}
		else if ((ret = Dz1TdqSqlTypeSpec_genFromPrimitive(info->type, ori, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ObjectType_enumerate:				// EnumInfo
		if (info->isPointer)
		{
			Dz1Thread_printf("Enumerate type Pointer Member : %s\n", info->instance);
			ERR_SET_OUT(errp, EINVAL);
		}
		else if ((ret = Dz1TdqSqlTypeSpec_genFromEnumerate(info->type, ori, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ObjectType_extern:					// ExternInfo			외부 정의 타입
		if (0) { }
		else if ((ret = Dz1TdqSqlTypeSpec_genFromExtern(info->type, ori, info->instance, ret_opt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ObjectType_structure:				// StructureInfo : Free Type
	case ObjectType_union:					// UnionInfo : Free Type
		if ((ret = Dz1TdqSqlTypeSpec_new(Dz1TdqSqlTypeSpecPresent_max, NULL, errp)) == NULL) ERR_OUT(errp);
		else  Dz1Error_set(errp, 0);
		break;
	case ObjectType_defined:				// DefinedInfo	-> don't care
	case ObjectType_bits:					// BitsInfo		
	case ObjectType_array:					// ArrayInfo
	case ObjectType_declare:				// str_t				선행 정의용
	case ObjectType_reference:				// ExternInfo			헤더에서 인클루드할 경우 인클루드 순환이 발생하는 타입
	case ObjectType_func:					// FunctionInfo
	case ObjectType_index:					// IndexInfo
	case ObjectType_constant:
		Dz1Thread_printf("Can't convertible type %s\n", ObjectTypeStr(ori->type));
		ERR_SET_OUT(errp, EINVAL);
		break;
	default:
		Dz1Thread_printf("Unknown type %d\n", ori->type);
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return ret;
}

static bool_t Dz1TdqColumn_setNullOpt(Dz1TdqColumn *dst, StructMemberEntry *info, Dz1Error *errp)
{
//	if (info->argInvolve || info->isIndex)
// 	if (info->argInvolve || 
// 		info->isIndex || 
// 		(info->isPointer == FALSE && ObjectInfo_isScalar(info->type) && ObjectInfo_isNullScalar(info->type) == FALSE))
	if (StructMemberEntry_isArgInvolve(info) ||
		StructMemberEntry_isIndex(info) ||
 		(info->isPointer == FALSE && ObjectInfo_isScalar(info->type) && ObjectInfo_isNullScalar(info->type) == FALSE))
	{
		if ((dst->null_opt = Dz1TdqNullOpt_new(NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqColumn *Dz1TdqColumn_genFromInfo(StructMemberEntry *info, Dz1TdqcShapeOptEntry **ret_opt, Dz1Error *errp)
{
	Dz1TdqColumn *ret = Dz1TdqColumn_new(info->instance, NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&ret);
		if ((ret->sql_type = Dz1TdqSqlTypeSpec_genFromInfo(info, ret_opt, errp)) == NULL) ERR_OUT(errp);
		else 
		{
			pthread_cleanup_push(Dz1TdqcShapeOptEntry_delAndSetNull, ret_opt);
			if (Dz1TdqColumn_setNullOpt(ret, info, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1TdqcShapeOptEntry_delAndSetNull, ret_opt);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqColumn_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1TdqTblShape *Dz1TdqTblShape_genFromObj(Dz1Str name, ObjectInfo *src, Dz1TdqcShapeOptList *opts, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqTblShape *ret = NULL;
	StructureInfo *info = NULL;
	if (Dz1Str_isVoid(name) || src == NULL || (info = (StructureInfo *)src->info) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqTblShape_new(name, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		StructMemberList *memb_list = info->members;
		StructMemberEntry **memb_arr = NULL; u32_t cnt = 0, i;
		pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&ret);

		if ((ret->row = Dz1TdqRow_new(errp)) == NULL) ERR_OUT(errp);
		else if ((ret->pk = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
		else if ((memb_arr = memb_list->get_array(memb_list, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1TdqcShapeOptEntry *opt = NULL;
			Dz1TdqColumn *col = NULL;
			StructMemberEntry *memb = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)memb_arr);
			for (i = 0; i < cnt; i++)
			{
				memb = memb_arr[i];
				if ((col = Dz1TdqColumn_genFromInfo(memb, &opt, errp)) == NULL) ERR_OUT(errp);
				else 
				{
					pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);
					pthread_cleanup_push(Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&opt);
					if (Dz1TdqRow_appendCol(ret->row, col, errp) == FALSE) ERR_OUT(errp);
					else 
					{
						col = NULL;
//						if (memb->isIndex)
						if (StructMemberEntry_isIndex(memb))
							Dz1TdqRowRef_addCol(ret->pk, memb->instance, ret->row, NULL);
						if (opt != NULL) 
						{
							Dz1Error status = DZ1_ERROR_INITIALIZER;
							if ((status = opts->add(opts, opt)).code) 
								ERR_OUT(&status);
							else opt = NULL;
						}
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&opt);
					pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)memb_arr);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqTblShape_delAndSetNull, (void *)&ret);
	}
	return ret;
}

typedef struct Dz1TdqQryRowFindByAliasArg
{
	Dz1TdqQryColumn *ret;
	Dz1Str			 key;
} Dz1TdqQryRowFindByAliasArg;

static Dz1Error _Dz1TdqQryRow_findByAlias(void *ptr, Dz1TdqQryColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1TdqQryRowFindByAliasArg *arg = (Dz1TdqQryRowFindByAliasArg *)ptr;
	if (Dz1Str_isVoid(p->alias) == FALSE)
	{
		if (Dz1STRCMP(p->alias, arg->key) == 0)
		{
			arg->ret = p;
			Dz1Error_set(errp, EEXIST);
		}
	}
	return err;
}

Dz1TdqQryColumn *Dz1TdqQryRow_findByAlias(Dz1TdqQryRow *row, Dz1Str name)
{
	Dz1TdqQryColumn *ret = NULL;

	if (row != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqQryRowFindByAliasArg arg = { NULL, name };
		row->travel(row, _Dz1TdqQryRow_findByAlias, (void *)&arg);
		ret = arg.ret;
	}
	return ret;
}

static bool_t Dz1TdqTblShape_insertSelectedColumn(Dz1TdqTblShape *dst_shp, Dz1TdqColumn **_col, 
												  Dz1TdqcShapeOptList *dst_opts, Dz1TdqcShapeOptEntry **_opt, 
												  StructMemberEntry *memb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1TdqRow_appendCol(dst_shp->row, *_col, errp) == FALSE) ERR_OUT(errp);
	else 
	{
		*_col = NULL;
		if (_opt != NULL && *_opt != NULL) 
		{
			Dz1Error status = DZ1_ERROR_INITIALIZER;
			if ((status = dst_opts->add(dst_opts, *_opt)).code) 
				ERR_OUT(&status);
			else *_opt = NULL;
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqColumn *Dz1TdqTblShape_findByName(Dz1TdqTblShape *shp, Dz1Str name)
{
	Dz1TdqColumn *ret = NULL;
	if (shp != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqRow *row = shp->row;
		ret = Dz1TdqRow_findByName(row, name);
	}
	return ret;
}

static Dz1TdqColumn *Dz1TdqcShape_findColumn(Dz1TdqcShape *c_shp, Dz1Str name)
{
	Dz1TdqColumn *ret = NULL;
	if (c_shp != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqTblShape *shp = c_shp->target;
		ret = Dz1TdqTblShape_findByName(shp, name);
	}
	return ret;
}

Dz1TdqTblShape *Dz1TdqTblShape_genFromRef(Dz1Str name, ObjectInfo *src, Dz1TdqQryRow *sel, Dz1TdqcShapeOptList *ret_opts, Dz1TdqcShapeList *tdqc_shapes, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqTblShape *ret = NULL;
	StructureInfo *info = NULL;
	if (Dz1Str_isVoid(name) || src == NULL || (info = (StructureInfo *)src->info) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqTblShape_new(name, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		StructMemberList *memb_list = info->members;
		StructMemberEntry **memb_arr = NULL; u32_t cnt = 0, i;
		pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&ret);
		if ((ret->row = Dz1TdqRow_new(errp)) == NULL) ERR_OUT(errp);
		else if ((ret->pk = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
		else if ((memb_arr = memb_list->get_array(memb_list, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1TdqcShapeOptEntry *opt = NULL;
			Dz1TdqColumn *col = NULL;
			Dz1TdqQryColumn *sel_col = NULL;
			Dz1TdqQryCol *sel_src = NULL;
			StructMemberEntry *memb = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)memb_arr);
			for (i = 0; i < cnt; i++)
			{
				memb = memb_arr[i];
				if ((sel_col = Dz1TdqQryRow_findByAlias(sel, memb->instance)) == NULL)
				{
					Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Can't find '%s' from query '%s'\n", memb->instance, name);
					ERR_SET_OUT(errp, EINVAL);
				}
				else if ((sel_src = sel_col->src) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (sel_src->present == Dz1TdqQryColPresent_ecol)
				{	// generate from object data
					if ((col = Dz1TdqColumn_genFromInfo(memb, &opt, errp)) == NULL) ERR_OUT(errp);	// default option may generated
					else 
					{
						pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);
						pthread_cleanup_push(Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&opt);

						if (Dz1TdqTblShape_insertSelectedColumn(ret, &col, ret_opts, &opt, memb, errp) == FALSE)
						{
							Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Column shape generation fail = %s\n", name);
							ERR_OUT(errp);
						}
						else Dz1Error_set(errp, 0);

						pthread_cleanup_pop(1); // (Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&opt);
						pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
					}
				}
				else if (sel_src->present == Dz1TdqQryColPresent_tcol)
				{	// copy from src column
					Dz1TdqQryTblCol *tcol = sel_src->x.tcol;
					Dz1TdqQueryTblName *tn = tcol->tbl;
					Dz1TdqTblInstance *tbl = tn->instance;
					Dz1TdqTblShape *tbl_shape = tbl->shape;
					Dz1TdqcShape *c_shape = NULL;
					Dz1TdqColumn *col_src = NULL;
					if (0) { }
					else if ((c_shape = Dz1TdqcShapeList_findByName(tdqc_shapes, tbl_shape->name)) == NULL)
					{
						Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Can't find shape '%s' from parsed shapes\n", tbl_shape->name);
						ERR_SET_OUT(errp, EINVAL);
					}
					else if ((col_src = Dz1TdqcShape_findColumn(c_shape, tcol->col_name)) == NULL)
					{
						Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Can't find '%s' from table '%s'\n", tcol->col_name, tbl->name);
						ERR_SET_OUT(errp, EINVAL);
					}
					else if ((col = Dz1TdqColumn_clone(col_src, errp)) == NULL) ERR_OUT(errp);
					else
					{
						Dz1TdqcShapeOptEntry *opt_src = NULL;
						pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);
						if ((opt_src = Dz1TdqcShapeOptList_findByName(c_shape->memb_opt, tcol->col_name)) != NULL && (opt = Dz1TdqcShapeOptEntry_clone(opt_src, errp)) == NULL) ERR_OUT(errp);
						else
						{
							pthread_cleanup_push(Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&opt);

							if (Dz1TdqTblShape_insertSelectedColumn(ret, &col, ret_opts, &opt, memb, errp) == FALSE)
							{
								Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Column shape generation fail = %s\n", name);
								ERR_OUT(errp);
							}
							else Dz1Error_set(errp, 0);

							pthread_cleanup_pop(1); // (Dz1TdqcShapeOptEntry_delAndSetNull, (void *)&opt);
						}
						pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
					}
				}
				else ERR_SET_OUT(errp, EFAULT);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)memb_arr);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqTblShape_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static bool_t Dz1TdqSqlNumSpec_setSize(Dz1TdqSqlTypeSpec *dst, s64_t sz, Dz1Error *errp)
{
	Dz1TdqSqlNumSpec *spec = NULL;
	if ((spec = (Dz1TdqSqlNumSpec *)dst->x.__ptr__) == NULL)
	{
		if ((dst->x.__ptr__ = Dz1TdqSqlNumSpec_new(sz, FALSE, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		spec->size = sz;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqSqlStrSpec_setSize(Dz1TdqSqlTypeSpec *dst, s64_t sz, Dz1Error *errp)
{
	Dz1TdqSqlStrSpec *spec = NULL;
	if ((spec = (Dz1TdqSqlStrSpec *)dst->x.__ptr__) == NULL)
	{
		if ((dst->x.__ptr__ = Dz1TdqSqlStrSpec_new(sz, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		spec->size = sz;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqSqlTypeSpec_setSizeOpt(Dz1TdqSqlTypeSpec *dst, s64_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || sz == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t cat = (dst->present >> 4) & 0x0F;
		switch(cat)
		{
		case 0:	if (Dz1TdqSqlNumSpec_setSize(dst, sz, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;	// number
		case 2:	if (Dz1TdqSqlStrSpec_setSize(dst, sz, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;	// string
		default:
		case 1:	
			ERR_SET_OUT(errp, EINVAL); 
			break;																		// real
		case 3:	ERR_SET_OUT(errp, EINVAL); break;																		// date & time
		case 4: /*ERR_SET_OUT(errp, EINVAL);*/ 																			// blob
			Dz1TdqSqlBlobSpec_delAndSetNull(&dst->x.blob);
			if ((dst->x.vbinary = Dz1TdqSqlStrSpec_new(sz, errp)) == NULL) ERR_OUT(errp);
			else
			{
				dst->present = Dz1TdqSqlTypeSpecPresent_vbinary;
				Dz1Error_set(errp, 0);
			}
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcOrderList_append(Dz1TdqcOrderList *dst, Dz1TdqcOrderEntry **node, Dz1Error *errp)
{
	if ((*errp = dst->add(dst, *node)).code) ERR_OUT(errp);
	else
	{
		*node = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqcOrderList_appendShp(Dz1TdqcOrderList *dst, Dz1TdqcShape *shp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcOrderEntry *node = NULL;
	if (dst == NULL || shp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqcOrderEntry_new( Dz1TdqcOrderEntryPresent_shp, shp, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcOrderEntry_delAndSetNull, (void *)&node);
		if (Dz1TdqcOrderList_append(dst, &node, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1TdqcOrderEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqcOrderList_appendTbl(Dz1TdqcOrderList *dst, Dz1TdqcTblInstance *tbl, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcOrderEntry *node = NULL;
	if (dst == NULL || tbl == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqcOrderEntry_new(Dz1TdqcOrderEntryPresent_tbl, tbl, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcOrderEntry_delAndSetNull, (void *)&node);
		if (Dz1TdqcOrderList_append(dst, &node, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1TdqcOrderEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqcOrderList_appendQry(Dz1TdqcOrderList *dst, Dz1TdqcQuery *qry, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcOrderEntry *node = NULL;
	if (dst == NULL || qry == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqcOrderEntry_new(Dz1TdqcOrderEntryPresent_qry, qry, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcOrderEntry_delAndSetNull, (void *)&node);
		if (Dz1TdqcOrderList_append(dst, &node, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1TdqcOrderEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

