#include <dz1_thread_stdio.h>
#include "dz1_mdefc_emit_util.h"

ObjectInfo *_emit_util_resolve_type(FORWARD_TYPE *_fwd, str_t type_name, int _is_ptr, str_t memb, u32_t memb_flags, ObjectInfo *papa, Dz1MdefcModule *module, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ObjectInfo *type = NULL, *origin = NULL;;
	if ((type = module->findObject(module, type_name)) == NULL)
	{	// type not found
		if (*_fwd != FORWARD_TYPE_NONE && (_is_ptr != 0 || MemberFlag_isArray(memb_flags) == TRUE))
		{	// explicit pointer type -> OK, associate with Unknown Type
			if ((type = module->regUnknownObject(module, type_name, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else
		{
			Dz1Thread_printf("Member Type Resolve : No Such type %s of %s\n", type_name, memb);
			ERR_SET_OUT(errp, ESRCH);
		}
	}
	else if ((origin = ObjectInfo_getOrigin(type)) == NULL)
	{
		Dz1Thread_printf("Member Type Resolve : Can't find origin type of %s\n", type->name);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if (origin->type == ObjectType_reference)
	{
		if (_is_ptr == 0 && MemberFlag_isArray(memb_flags) == FALSE)
		{
			Dz1Thread_printf("Type Resolve : Incomplete type %s of %s\n", type->name, memb);
			ERR_SET_OUT(errp, ENOENT);
		}
		else
		{
			FORWARD_TYPE origin_fwd = *_fwd;
			ExternInfo *info = (ExternInfo *)origin->info;
			ExternInfoStatic mode = (ExternInfoStatic)info->isStatic;


			switch(mode)
			{
			default:
			case ExternInfoStatic_primitive:
			case ExternInfoStatic_primitive_ptr:
				break;
			case ExternInfoStatic_typical_union:	*_fwd = FORWARD_TYPE_UNION;		break;
			case ExternInfoStatic_construct:		*_fwd = FORWARD_TYPE_STRUCT;	break;
//			case ExternInfoStatic_typical_enum:		*_fwd = FORWARD_TYPE_ENUM;		break;
			}
			if (origin_fwd != FORWARD_TYPE_NONE && origin_fwd != *_fwd)
				Dz1Thread_printf("### forward declaration %s %s in %s is modified(%s -> %s)\n", type->name, memb, papa->name,
															FORWARD_TYPE_StrA(origin_fwd), FORWARD_TYPE_StrA(*_fwd));
			Dz1Error_set(errp, 0);
		}
	}
	else if (origin->type == ObjectType_declare)
	{
		if (_is_ptr == 0 && MemberFlag_isArray(memb_flags) == FALSE)
		{
			Dz1Thread_printf("Type Resolve : Incomplete type %s of %s\n", type->name, memb);
			ERR_SET_OUT(errp, ENOENT);
		}
		else
		{
			FORWARD_TYPE old_fwd = *_fwd;
			str_t fwd = (str_t)origin->info;
			if (0) { }
			else if (strcmp(fwd, "union") == 0) *_fwd = FORWARD_TYPE_UNION;
			else if (strcmp(fwd, "struct") == 0) *_fwd = FORWARD_TYPE_STRUCT;
			else if (strcmp(fwd, "enum") == 0) *_fwd = FORWARD_TYPE_ENUM;
			else
			{
				Dz1Thread_printf("Type Resolve : Unknown forward type %s of %s\n", fwd, memb);
				ERR_SET_OUT(errp, EFAULT);
			}
		}
// 		if (*_fwd != FORWARD_TYPE_NONE && (_is_ptr != 0 || MemberFlag_isArray(memb_flags) == TRUE)) Dz1Error_set(errp, 0);
// 		else
// 		{
// 			Dz1Thread_printf("Member Type Resolve : Incomplete type %s\n", type->name);
// 			ERR_SET_OUT(errp, ENOENT);
// 		}
	}
	return type;
}
