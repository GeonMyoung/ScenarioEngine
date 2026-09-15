#include <dz1_thread_stdio.h>
#include "dz1_tjsonc_util.h"

typedef struct ListAddCancelArg
{
	void				*list;
	void				**src;
} ListAddCancelArg;

static void _list_add_cancel(void *ptr)
{
	ListAddCancelArg *arg = (ListAddCancelArg *)ptr;
	ObjectInfoIndex *list = (ObjectInfoIndex *)arg->list;
	ObjectInfo **node = (ObjectInfo **)arg->src;
	if (*node != NULL) list->extract(list, *node);
}

static bool_t _Dz1JsonTargetObjects_add(Dz1JsonTargetObjects *dst, ObjectInfo *src, Dz1Error *errp)
{
	ObjectInfoIndex *index = dst->index;
	ObjectInfoSeq *seq = dst->seq;
	if (index->find(index, src) != NULL) { }
	else if ((*errp = index->add(index, src)).code) ERR_OUT(errp);
	else
	{
		ListAddCancelArg arg = { index, (void **)&src };
		pthread_cleanup_push(_list_add_cancel, (void *)&arg);
		if ((*errp = seq->add(seq, src)).code) ERR_OUT(errp);
		else
		{
			src = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (_list_add_cancel, (void *)&arg);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Structure add
static bool_t _struct_member_add(Dz1JsonTargetObjects *dst, StructMemberList *membs, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
	u32_t cnt = 0;
	StructMemberEntry **arr = membs->get_array(membs, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		StructMemberEntry *node = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i =0; errp->code == 0 && i < cnt; i++)
		{
			node = arr[i] ;
			if (Dz1JsonTargetObjects_append(dst, node->type, cascade, module, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1JsonTargetObjects_addStruct(Dz1JsonTargetObjects *dst, ObjectInfo *obj, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
	StructureInfo *info = (StructureInfo *)obj->info;
	if (cascade && _struct_member_add(dst, info->members, cascade, module, errp) == FALSE) ERR_OUT(errp);
	else if (_Dz1JsonTargetObjects_add(dst, obj, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Structure add
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union add
static bool_t _union_member_add(Dz1JsonTargetObjects *dst, UnionMemberList *membs, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
	u32_t cnt = 0;
	UnionMemberEntry **arr = membs->get_array(membs, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		UnionMemberEntry *node = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i =0; errp->code == 0 && i < cnt; i++)
		{
			node = arr[i] ;
			if (Dz1JsonTargetObjects_append(dst, node->type, cascade, module, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1JsonTargetObjects_addUnion(Dz1JsonTargetObjects *dst, ObjectInfo *obj, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
	UnionInfo *info = (UnionInfo *)obj->info;
	if (cascade && _union_member_add(dst, info->members, cascade, module, errp) == FALSE) ERR_OUT(errp);
	else if (_Dz1JsonTargetObjects_add(dst, obj, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Union add
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Add
static bool_t _Dz1JsonTargetObjects_addConstruct(Dz1JsonTargetObjects *dst, ObjectInfo *obj, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
	switch(obj->type)
	{
	case ObjectType_structure:				// StructureInfo
		if (_Dz1JsonTargetObjects_addStruct(dst, obj, cascade, module, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ObjectType_union:					// UnionInfo
		if (_Dz1JsonTargetObjects_addUnion(dst, obj, cascade, module, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Construct Add
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array Add
static bool_t _Dz1JsonTargetObjects_addArr(Dz1JsonTargetObjects *dst, ObjectInfo *obj, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
	ArrayInfo *info = (ArrayInfo *)obj->info;
	if (cascade && Dz1JsonTargetObjects_append(dst, info->entry, cascade, module, errp) == FALSE) ERR_OUT(errp);
	else if (_Dz1JsonTargetObjects_add(dst, obj, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1JsonTargetObjects_addIdx(Dz1JsonTargetObjects *dst, ObjectInfo *obj, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
	IndexInfo *info = (IndexInfo *)obj->info;
	if (cascade && Dz1JsonTargetObjects_append(dst, info->entry, cascade, module, errp) == FALSE) ERR_OUT(errp);
	else if (_Dz1JsonTargetObjects_add(dst, obj, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1JsonTargetObjects_addArray(Dz1JsonTargetObjects *dst, ObjectInfo *obj, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
	switch(obj->type)
	{
	case ObjectType_array:					// ArrayInfo
		if (_Dz1JsonTargetObjects_addArr(dst, obj, cascade, module, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ObjectType_index:					// IndexInfo
		if (_Dz1JsonTargetObjects_addIdx(dst, obj, cascade, module, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Array Add
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Extern Add
static bool_t _Dz1JsonTargetObjects_addExtern(Dz1JsonTargetObjects *dst, ObjectInfo *obj, bool_t cascade, Dz1MdefcModule *module, Dz1Error *errp)
{
//	ExternInfo *info = (ExternInfo *)obj->info;

	if (0) { }
// 	else if (info->isStatic == FALSE)
// 	{
// 		Dz1Thread_printf("!!! Cause = %s is not static\n", obj->name);
// 		ERR_SET_OUT(errp, ENOSYS);
// 	}
	else if (_Dz1JsonTargetObjects_add(dst, obj, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
// Extern Add
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1JsonTargetObjects_append(Dz1JsonTargetObjects *dst, ObjectInfo *src, bool_t cascade, Dz1MdefcModule *module, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ObjectInfo *obj = ObjectInfo_getOrigin(src);
	switch(obj->type)
	{
	case ObjectType_primitive:				// PrimitiveInfo = no need to append
		break;
	case ObjectType_enumerate:				// EnumInfo
		if (_Dz1JsonTargetObjects_add(dst, src, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ObjectType_structure:				// StructureInfo
	case ObjectType_union:					// UnionInfo
		if (_Dz1JsonTargetObjects_addConstruct(dst, src, cascade, module, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ObjectType_array:					// ArrayInfo
	case ObjectType_index:					// IndexInfo
		if (_Dz1JsonTargetObjects_addArray(dst, src, cascade, module, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ObjectType_extern:					// ExternInfo(typedef native)
		if (_Dz1JsonTargetObjects_addExtern(dst, src, cascade, module, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
	case ObjectType_defined:				// DefinedInfo = don't care
	case ObjectType_bits:					// BitsInfo = not support
	case ObjectType_declare:				// str_t				선행 정의용
	case ObjectType_reference:				// ExternInfo
	case ObjectType_func:					// FunctionInfo
	case ObjectType_constant:
		ERR_SET_OUT(errp, ENOSYS);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void Dz1JsonCompileIncs_appendCancel(void *ptr)
{
	ListAddCancelArg *arg = (ListAddCancelArg *)ptr;
	Dz1JsonCompileIncIndex *idx = (Dz1JsonCompileIncIndex *)arg->list;
	Dz1Str *node = (Dz1Str *)arg->src;
	if (*node != NULL) idx->extract(idx, *node);
}

static bool_t Dz1JsonCompileIncs_append(Dz1JsonCompileIncs *dst, Dz1Str *str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonCompileIncIndex *idx = dst->index;
	Dz1JsonCompileIncSeq *seq = dst->seq;
	Dz1Str node = *str;
	if ((*errp = idx->add(idx, node)).code) ERR_OUT(errp);
	else
	{
		ListAddCancelArg arg = { idx, (void **)&node };
		pthread_cleanup_push(Dz1JsonCompileIncs_appendCancel, (void *)&arg);
		if ((*errp = seq->add(seq, node)).code) ERR_OUT(errp);
		else
		{
			*str = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1JsonCompileIncs_appendCancel, (void *)&arg);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _partial_copy_and_append(Dz1JsonCompileIncs *dst, TCHAR *startp, TCHAR *endp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str str = NULL;
	size_t len = (size_t)(endp - startp);
	if (len == 0) { }
	else if ((str = Dz1Calloc(sizeof(TCHAR), len + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TCHAR *dp = str;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&str);
		while(*startp && startp < endp) *dp++ = *startp++; *dp = 0;
		if (Dz1JsonCompileIncs_append(dst, &str, errp) == FALSE) ERR_OUT(errp);
		else
		{
			str = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&str);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1JsonCompileIncs_appendPath(Dz1JsonCompileIncs *dst, Dz1Str arg_str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		TCHAR *semi = NULL, *sp = arg_str;
		while(errp->code == 0 && (semi = Dz1STRCHR(sp, Dz1Text(';') )) != NULL)
		{
			if (_partial_copy_and_append(dst, sp, semi, errp) == FALSE) ERR_OUT(errp);
			else
			{
				sp = semi + 1;
				Dz1Error_set(errp, 0);
			}
		}
		if (errp->code == 0)
		{
			if (*sp)
			{
				if (Dz1JsonCompileIncs_append(dst, &sp, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
