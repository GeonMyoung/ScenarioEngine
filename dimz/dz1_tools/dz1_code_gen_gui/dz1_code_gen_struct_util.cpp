#include "dz1_code_gen_struct_util.h"

static Dz1Error __append_child(void *ptr, StructMemberEntry *p)
{
	ListControlGenNode *parent = (ListControlGenNode *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	ListControlGenNode *node = ListControlGenNode_build(p->instance, p->type, parent, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ListControlGenNode_delAndSetNull, (void *)&node);
		if ((*errp = parent->childs->add(parent->childs, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ListControlGenNode_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error _append_child(ListControlGenNode *dst, StructureInfo *info)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = info->members->travel(info->members, __append_child, (void *)dst)).code) ERR_OUT(errp);
	return err;
}

ListControlGenNode *ListControlGenNode_build(str_t name, ObjectInfo *obj, ListControlGenNode *parent, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ListControlGenNode *ret = ListControlGenNode_new(name, obj, FALSE, parent, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ObjectInfo *origin = NULL;
		pthread_cleanup_push(ListControlGenNode_delAndSetNull, (void *)&ret);
		switch(obj->type)
		{
		case ObjectType_primitive:				// PrimitiveInfo
		case ObjectType_enumerate:				// EnumInfo
		case ObjectType_bits:					// BitsInfo
		case ObjectType_union:					// UnionInfo
			// 아이템으로 사용 가능, 자식 생성 불가
			ret->isItem = TRUE;
			break;
		case ObjectType_declare:				// str_t				선행 정의용
		case ObjectType_defined:				// DefinedInfo
			origin = ObjectInfo_getOrigin(obj);
			switch(origin->type)
			{
			case ObjectType_primitive:				// PrimitiveInfo
			case ObjectType_enumerate:				// EnumInfo
			case ObjectType_bits:					// BitsInfo
			case ObjectType_union:					// UnionInfo
				// 아이템으로 사용 가능, 자식 생성 불가
				ret->isItem = TRUE;
				break;
			case ObjectType_structure:				// StructureInfo
				// 아이템으로 사용 불가, 자식 생성 가능
				if ((*errp = _append_child(ret, (StructureInfo *)obj->info)).code) ERR_OUT(errp);
				break;
			case ObjectType_array:					// ArrayInfo
			case ObjectType_func:					// FunctionInfo
			case ObjectType_extern:					// ExternInfo			외부 정의 타입
			case ObjectType_reference:				// ExternInfo			외부 정의 타입, 하지만 헤더에서 인클루드할 경우
													//						인클루드 순환이 발생하는 타입
				// 아이템으로 사용 불가, 자식 생성 불가
				break;
			default:
				break;
			}
			break;
		case ObjectType_structure:				// StructureInfo
			// 아이템으로 사용 불가, 자식 생성 가능
			if ((*errp = _append_child(ret, (StructureInfo *)obj->info)).code) ERR_OUT(errp);
			break;
		case ObjectType_array:					// ArrayInfo
		case ObjectType_func:					// FunctionInfo
		case ObjectType_extern:					// ExternInfo			외부 정의 타입
		case ObjectType_reference:				// ExternInfo			외부 정의 타입, 하지만 헤더에서 인클루드할 경우
												//						인클루드 순환이 발생하는 타입
			// 아이템으로 사용 불가, 자식 생성 불가
			break;
		default:
			break;
		}
		pthread_cleanup_pop(errp->code); // (ListControlGenNode_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1CodeGenListColumn_setParent(Dz1CodeGenListColumn *dstChild, ListControlGenNode *itemParent)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (itemParent == NULL) dstChild->parent = NULL;
	else
	{
		ListControlGenNode *i = NULL;
		Dz1CodeGenListCtrlObjectParent **parent = &dstChild->parent;

		for (i = itemParent; i != NULL && errp->code == 0; i = i->parent)
		{
			if (((*parent) = Dz1CodeGenListCtrlObjectParent_new(NULL, itemParent->name, errp)) == NULL) ERR_OUT(errp);
			else parent = &((*parent)->p);
		}
	}
	return err;
}