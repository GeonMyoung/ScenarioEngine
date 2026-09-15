#include "dz1_todec.h"

///////////////////////////////////////////////////////////////////////////////
// Primitive Partial
static Dz1Error _pub_primitive_rstr_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1TodecRestrictDescr *rstr = (Dz1TodecRestrictDescr *)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{	// Address Type
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			switch(rstr->present)
			{
			case Dz1TodecRestrictDescrPresent_fixed:
				Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %sX_read(&%s, src, %u, ed, param, errp), errp);" NEW_LINE,
											info->prefix, var_name, rstr->x.fixed);
				break;
			case Dz1TodecRestrictDescrPresent_dynamic:
				Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s%u_read(&%s, src, ed, param, errp), errp);" NEW_LINE,
											info->prefix, rstr->x.dynamic * 8, var_name);
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
			}
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		ERR_SET_OUT(errp, EPERM);
	}
	else
	{	// NativeStorage_none
		if (var->var_is_ptr == FALSE) ERR_SET_OUT(errp, ENOSYS);
		else Dz1Error_set(errp, 0);
	}

	return err;
}

static Dz1Error _pub_primitive_rstr_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecRestrictDescr *rstr = (Dz1TodecRestrictDescr *)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			switch(rstr->present)
			{
			case Dz1TodecRestrictDescrPresent_fixed:
				Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %sX_write(dst, %s, %u, ed, param, errp), errp);" NEW_LINE,
											info->prefix, var_name, rstr->x.fixed);
				break;
			case Dz1TodecRestrictDescrPresent_dynamic:
				Dz1Thread_ftprintf(fp, tab, "DZ1_IO_STREAM_FUNC(ret, %s%u_write(dst, %s, ed, param, errp), errp);" NEW_LINE,
											info->prefix, rstr->x.dynamic * 8, var_name);
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
			}
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		ERR_SET_OUT(errp, EPERM);
	}
	else
	{
		if (var->var_is_ptr == FALSE) ERR_SET_OUT(errp, EPERM);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
// Primitive Partial
///////////////////////////////////////////////////////////////////////////////


ObjectTypeMembPublishApi membRstrPublishApi[] =
{	// primitive(data_storage), enumerate only
 	{ ObjectType_primitive,	_pub_primitive_rstr_read,	_pub_primitive_rstr_write },
	{ ObjectType_max }
};

///////////////////////////////////////////////////////////////////////////////
// Primitive Partial (sz IO)
static Dz1Error _pub_primitive_rstr_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{	// if ((sz = Dz1Stream_read?(src, &{dst}, ed, errp)) < 0) ERR_OUT(errp);
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1TodecRestrictDescr *rstr = (Dz1TodecRestrictDescr *)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{	// Address Type
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			switch(rstr->present)
			{
			case Dz1TodecRestrictDescrPresent_fixed:
				Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %sX_read(&%s, src, %u, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
											(*need_else) ? "else " : "", info->prefix, var_name, rstr->x.fixed);
				(*need_else) = TRUE;
				break;
			case Dz1TodecRestrictDescrPresent_dynamic:
				Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%u_read(&%s, src, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
											(*need_else) ? "else " : "", info->prefix, rstr->x.dynamic * 8, var_name);
				(*need_else) = TRUE;
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
			}
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		ERR_SET_OUT(errp, EPERM);
	}
	else
	{	// NativeStorage_none
		if (var->var_is_ptr == FALSE) ERR_SET_OUT(errp, ENOSYS);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _pub_primitive_rstr_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecRestrictDescr *rstr = (Dz1TodecRestrictDescr *)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			switch(rstr->present)
			{
			case Dz1TodecRestrictDescrPresent_fixed:
				Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %sX_write(dst, %s, %u, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
											(*need_else) ? "else " : "", info->prefix, var_name, rstr->x.fixed);
				break;
			case Dz1TodecRestrictDescrPresent_dynamic:
				Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%u_write(dst, %s, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
											(*need_else) ? "else " : "", info->prefix, rstr->x.dynamic * 8, var_name);
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
			}
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		ERR_SET_OUT(errp, EPERM);
	}
	else
	{
		if (var->var_is_ptr == FALSE) ERR_SET_OUT(errp, EPERM);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
// Primitive Partial (sz IO)
///////////////////////////////////////////////////////////////////////////////

ObjectTypeMembPublishApi membRstrSzPublishApi[] =
{
 	{ ObjectType_primitive,	_pub_primitive_rstr_sz_read,	_pub_primitive_rstr_sz_write },
	{ ObjectType_max }
};
