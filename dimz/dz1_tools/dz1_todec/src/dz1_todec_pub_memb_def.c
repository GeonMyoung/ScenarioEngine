#include "dz1_todec.h"

///////////////////////////////////////////////////////////////////////////////
// Primitive Default
static Dz1Error _pub_primitive_def_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s_read(&%s, src, ed, param, errp), errp);" NEW_LINE,
								*need_else ? "else " : "", info->prefix, var_name);
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		bool_t casted = FALSE;
		Dz1TodecUnitSize dst_sz = _resolve_prim_size(info, errp);

		if (dst_sz == Dz1TodecUnitSize_max)
		{
			Dz1Thread_printf("Variable = "); StreamElementVariable_dump(var, 0);
			Dz1Thread_printf("Info(%s) = ", var->instance); PrimitiveInfo_dump(info, 0);
			Dz1Thread_printf("!!! Warning : unknown data size(%s) -> Byte4\n", info->native);
			casted = TRUE;
			Dz1Error_set(errp, 0);
		}

		if (var->var_is_ptr && do_gen)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, var->target->name);
			*need_else = TRUE;
		}

		if (casted)
		{
			if (*need_else) Dz1Thread_ftprintf(fp, tab, "else { "); else Dz1Thread_ftprintf(fp, tab, "");

			Dz1Thread_fprintf(fp, "DZ1_STREAM_READ4(&v32, src, ed, errp, ret); %s%s = (%s)v32;",
									var->var_is_ptr ? "*" : "", var_name, info->native);

			if (*need_else) Dz1Thread_fprintf(fp, "}" NEW_LINE); else Dz1Thread_fprintf(fp, NEW_LINE);
		}
		else
		{
			if (dst_sz == Dz1TodecUnitSize_Byte1)
			{
				Dz1Thread_ftprintf(fp, tab, "%sDZ1_STREAM_READ1(%s%s, src, errp, ret);" NEW_LINE, 
								   *need_else ? "else " : "", var->var_is_ptr ? "" : "&", var_name);
			}
			else
			{
				Dz1Thread_ftprintf(fp, tab, "%sDZ1_STREAM_READ%d(%s%s, src, ed, errp, ret);" NEW_LINE, 
								   *need_else ? "else " : "", dst_sz, var->var_is_ptr ? "" : "&", var_name);
			}
		}
	}
	else
	{	// void
		if (var->var_is_ptr)
		{
			// No Output
		}
		else
		{
			Dz1Thread_printf("Variable = "); StreamElementVariable_dump(var, 0);
			Dz1Thread_printf("!!! Primitive Info = "); PrimitiveInfo_dump(info, 0);
			ERR_SET_OUT(errp, EPERM);
		}
	}

	return err;
}

static Dz1Error _pub_primitive_def_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

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
			Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s_write(dst, %s, ed, param, errp), errp);" NEW_LINE,
								*need_else ? "else " : "", info->prefix, var_name);
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		bool_t casted = FALSE;
		Dz1TodecUnitSize dst_sz = _resolve_prim_size(info, errp);

		if (dst_sz == Dz1TodecUnitSize_max)
		{
			Dz1Thread_printf("Variable = "); StreamElementVariable_dump(var, 0);
			Dz1Thread_printf("Info(%s) = ", var->instance); PrimitiveInfo_dump(info, 0);
			Dz1Thread_printf("!!! Warning : unknown data size(%s) -> Byte4\n", info->native);
			casted = TRUE;
			Dz1Error_set(errp, 0);
		}

		if (casted)
		{
			if (*need_else) Dz1Thread_ftprintf(fp, tab, "%s { "); else Dz1Thread_ftprintf(fp, tab, "");
			Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE4(dst, (v32 = (u32_t)%s%s), ed, errp, ret);", 
									var->var_is_ptr ? "*" : "", var_name);
			if (*need_else) Dz1Thread_fprintf(fp, "}" NEW_LINE); else Dz1Thread_fprintf(fp, NEW_LINE);
		}
		else
		{
			if (var->var_is_ptr && chk_ptr)
			{	// Gen Target
				Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
									*need_else ? "else " : "", var_name);
				*need_else = TRUE;
			}

			if (dst_sz == Dz1TodecUnitSize_Byte1)
			{
				Dz1Thread_ftprintf(fp, tab, "%sDZ1_STREAM_WRITE1(dst, %s%s, errp, ret);" NEW_LINE, 
								   *need_else ? "else " : "", var->var_is_ptr ? "*" : "", var_name);
			}
			else
			{
				if (dst_sz >= Dz1TodecUnitSize_Byte4 && strstr(info->native, "real") != NULL)
					Dz1Thread_ftprintf(fp, tab, "%sDZ1_STREAM_WRITE%d(dst, *(u%u_t *)%s%s, ed, errp, ret);" NEW_LINE, 
									   *need_else ? "else " : "", dst_sz, 
										dst_sz * 8,
										var->var_is_ptr ? "" : "&",
										var_name);
				else
					Dz1Thread_ftprintf(fp, tab, "%sDZ1_STREAM_WRITE%d(dst, %s%s, ed, errp, ret);" NEW_LINE, 
									   *need_else ? "else " : "", dst_sz, var->var_is_ptr ? "*" : "", var_name);
			}
		}
	}
	else
	{	// void
		if (var->var_is_ptr)
		{
			// No Output
		}
		else
		{
			Dz1Thread_printf("Variable = "); StreamElementVariable_dump(var, 0);
			Dz1Thread_printf("!!! Primitive Info = "); PrimitiveInfo_dump(info, 0);
			ERR_SET_OUT(errp, EPERM);
		}
	}

	return err;
}
// Primitive Default
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enumerate Default
static Dz1Error _pub_enum_def_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name, var_name, var->target->name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sDZ1_STREAM_READ4(&v32, src, ed, errp, ret); %s%s = (%s)v32;" NEW_LINE, 
					   *need_else ? "else " : "", var->var_is_ptr ? "*" : "", var_name, var->target->name);

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_enum_def_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sDZ1_STREAM_WRITE4(dst, (u32_t)%s%s, ed, errp, ret);" NEW_LINE, 
					   *need_else ? "else " : "", var->var_is_ptr ? "*" : "", var_name);
	
	Dz1Error_set(errp, 0);
	return err;
}
// Enumerate Default
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Default
static Dz1Error _pub_construct_def_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *tgt = var->target;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		ObjectInfo *ori = var->origin;
		if (ori->type == ObjectType_union)
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_new(%sPresent_max, NULL, errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, tgt->name, tgt->name);
		else if (ori->type == ObjectType_array || ori->type == ObjectType_index)
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_new(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, tgt->name);
		else
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, tgt->name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s_read(%s%s, src, ed, param, errp), errp);" NEW_LINE, 
					   *need_else ? "else " : "", tgt->name, var->var_is_ptr ? "" : "&", var_name);

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_construct_def_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *tgt = var->target;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s_write(dst, %s%s, ed, param, errp), errp);" NEW_LINE, 
					   *need_else ? "else " : "", tgt->name, var->var_is_ptr ? "" : "&", var_name);
	
	Dz1Error_set(errp, 0);
	return err;
}
// Construct Default
///////////////////////////////////////////////////////////////////////////////

ObjectTypeMembPublishApi membDefPublishApi[] =
{
	{ ObjectType_primitive,	_pub_primitive_def_read,	_pub_primitive_def_write },
	{ ObjectType_enumerate,	_pub_enum_def_read,			_pub_enum_def_write },
	{ ObjectType_structure,	_pub_construct_def_read,	_pub_construct_def_write },
	{ ObjectType_union,		_pub_construct_def_read,	_pub_construct_def_write },
	{ ObjectType_extern,	_pub_construct_def_read,	_pub_construct_def_write },
	{ ObjectType_array,		_pub_construct_def_read,	_pub_construct_def_write },
	{ ObjectType_index,		_pub_construct_def_read,	_pub_construct_def_write },
	{ ObjectType_reference,	_pub_construct_def_read,	_pub_construct_def_write },
	{ ObjectType_max }
};

///////////////////////////////////////////////////////////////////////////////
// Primitive Default (sz IO)
static Dz1Error _pub_primitive_def_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{	// if ((sz = Dz1Stream_read?(src, &{dst}, ed, errp)) < 0) ERR_OUT(errp);
	DZ1_ERROR_SAFE_VAR(errp, err);

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{	// Pointer type Primitive
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			Dz1Thread_ftprintf(fp, tab, "%if ((sz = %s_read(&%s, src, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
								*need_else ? "else " : "", info->prefix, var_name);
			*need_else = TRUE;
		}
	}
	else if (info->storage == NativeStorage_data)
	{	// Scalar type Primitive
		Dz1TodecUnitSize dst_sz = _resolve_prim_size(info, errp);

		if (dst_sz == Dz1TodecUnitSize_max) ERR_OUT_RET(errp, err);

		if (var->var_is_ptr && do_gen)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT(errp);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, var->target->name);
			*need_else = TRUE;
		}

		if (dst_sz == Dz1TodecUnitSize_Byte1)
		{
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_read1(%s%s, src, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
							   *need_else ? "else " : "", var->var_is_ptr ? "" : "&", var_name);
		}
		else
		{
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_read%d(%s%s, src, ed, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
							   *need_else ? "else " : "", dst_sz, var->var_is_ptr ? "" : "&", var_name);
		}
		*need_else = TRUE;
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}

static Dz1Error _pub_primitive_def_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

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
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s_write(dst, %s, ed, param, errp) < 0) ERR_OUT(errp);" NEW_LINE,
								*need_else ? "else " : "", info->prefix, var_name);
			*need_else = TRUE;
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		Dz1TodecUnitSize dst_sz = _resolve_prim_size(info, errp);

		if (dst_sz == Dz1TodecUnitSize_max) ERR_OUT_RET(errp, err);

		if (var->var_is_ptr && chk_ptr)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name);
			*need_else = TRUE;
		}

		if (dst_sz == Dz1TodecUnitSize_Byte1)
		{
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_write1(dst, %s%s, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
							   *need_else ? "else " : "", var->var_is_ptr ? "*" : "", var_name);
		}
		else
		{
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_write%d(dst, %s%s, ed, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
							   *need_else ? "else " : "", dst_sz, var->var_is_ptr ? "*" : "", var_name);
		}
		*need_else = TRUE;
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}
// Primitive Default (sz IO)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enumerate Default (sz IO)
static Dz1Error _pub_enum_def_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name, var_name, var->target->name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_read4(&v32, src, ed, errp, ret)) < 0) ERR_OUT(errp);" NEW_LINE, 
					   *need_else ? "else " : "", var->var_is_ptr ? "*" : "", var_name, var->target->name);
	*need_else = TRUE;

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_enum_def_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_write4(dst, (u32_t)%s%s, ed, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
					   *need_else ? "else " : "", var->var_is_ptr ? "*" : "", var_name);
	*need_else = TRUE;
	
	Dz1Error_set(errp, 0);
	return err;
}
// Enumerate Default (sz IO)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Default (sz IO)
static Dz1Error _pub_construct_def_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *tgt = var->target;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		ObjectInfo *ori = var->origin;
		if (ori->type == ObjectType_union)
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_new(%sPresent_max, NULL, errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, tgt->name, tgt->name);
		else if (ori->type == ObjectType_array || ori->type == ObjectType_index)
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_new(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, tgt->name);
		else
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, tgt->name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s_read(%s%s, src, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
					   *need_else ? "else " : "", tgt->name, var->var_is_ptr ? "" : "&", var_name);
	*need_else = TRUE;

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_construct_def_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *tgt = var->target;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s_write(dst, %s%s, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
					   *need_else ? "else " : "", tgt->name, var->var_is_ptr ? "" : "&", var_name);
	*need_else = TRUE;
	
	Dz1Error_set(errp, 0);
	return err;
}
// Construct Default (sz IO)
///////////////////////////////////////////////////////////////////////////////

ObjectTypeMembPublishApi membDefSzPublishApi[] =
{
	{ ObjectType_primitive,	_pub_primitive_def_sz_read,	_pub_primitive_def_sz_write },
	{ ObjectType_enumerate,	_pub_enum_def_sz_read,		_pub_enum_def_sz_write },
	{ ObjectType_structure,	_pub_construct_def_sz_read,	_pub_construct_def_sz_write },
	{ ObjectType_union,		_pub_construct_def_sz_read,	_pub_construct_def_sz_write },
	{ ObjectType_array,		_pub_construct_def_sz_read,	_pub_construct_def_sz_write },
	{ ObjectType_index,		_pub_construct_def_sz_read,	_pub_construct_def_sz_write },
	{ ObjectType_max }
};

