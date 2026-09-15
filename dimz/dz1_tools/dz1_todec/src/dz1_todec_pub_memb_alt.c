#include "dz1_todec.h"

///////////////////////////////////////////////////////////////////////////////
// Primitive Alternated
static Dz1Error _pub_primitive_alt_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	str_t prefix_name = info->prefix;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (info->storage == NativeStorage_address)
	{
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s%s_read(&%s, src, ed, param, errp), errp);" NEW_LINE,
								*need_else ? "else " : "", prefix_name, alt_name, var_name);
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		if (var->var_is_ptr && do_gen)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, var->target->name);
			*need_else = TRUE;
		}

		Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s%s_read(%s%s, src, ed, param, errp), errp);" NEW_LINE,
							*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}

static Dz1Error _pub_primitive_alt_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	str_t prefix_name = info->prefix;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (info->storage == NativeStorage_address)
	{
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s%s_write(dst, %s, ed, param, errp), errp);" NEW_LINE,
								*need_else ? "else " : "", prefix_name, alt_name, var_name);
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		if (var->var_is_ptr && chk_ptr)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name);
			*need_else = TRUE;
		}

		Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s%s_write(dst, %s%s, ed, param, errp), errp);" NEW_LINE,
							*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}
// Primitive Alternated
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enumerate Alternated
static Dz1Error _pub_enum_alt_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;
	ObjectInfo *tgt = var->target;

	str_t prefix_name = tgt->name;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name, var_name, tgt->name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s%s_read(%s%s, src, ed, param, errp), errp);" NEW_LINE,
						*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_enum_alt_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;
	ObjectInfo *tgt = var->target;

	str_t prefix_name = tgt->name;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s%s_write(dst, %s%s, ed, param, errp), errp);" NEW_LINE,
						*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);

	Dz1Error_set(errp, 0);
	return err;
}
// Enumerate Alternated
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Alternated
static Dz1Error _pub_construct_alt_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;
	ObjectInfo *tgt = var->target;

	str_t prefix_name = tgt->name;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name, var_name, tgt->name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s%s_read(%s%s, src, ed, param, errp), errp);" NEW_LINE,
						*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_construct_alt_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;
	ObjectInfo *tgt = var->target;

	str_t prefix_name = tgt->name;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sDZ1_IO_STREAM_FUNC(ret, %s%s_write(dst, %s%s, ed, param, errp), errp);" NEW_LINE,
						*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);

	Dz1Error_set(errp, 0);
	return err;
}
// Construct Alternated
///////////////////////////////////////////////////////////////////////////////

ObjectTypeMembPublishApi membAltPublishApi[] =
{
	{ ObjectType_primitive,	_pub_primitive_alt_read,	_pub_primitive_alt_write },
	{ ObjectType_enumerate,	_pub_enum_alt_read,			_pub_enum_alt_write },
	{ ObjectType_structure,	_pub_construct_alt_read,	_pub_construct_alt_write },
	{ ObjectType_union,		_pub_construct_alt_read,	_pub_construct_alt_write },
	{ ObjectType_extern,	_pub_construct_alt_read,	_pub_construct_alt_write },
	{ ObjectType_array,		_pub_construct_alt_read,	_pub_construct_alt_write },
	{ ObjectType_index,		_pub_construct_alt_read,	_pub_construct_alt_write },
	{ ObjectType_max }
};

///////////////////////////////////////////////////////////////////////////////
// Primitive Alternated (sz IO)
static Dz1Error _pub_primitive_alt_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	str_t prefix_name = info->prefix;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (info->storage == NativeStorage_address)
	{
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{	//							  1           2 3        4
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%s_read(&%s, src, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
										*need_else ? "else " : "", prefix_name, alt_name, var_name);
			*need_else = TRUE;
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		if (var->var_is_ptr && do_gen)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, var->target->name);
			*need_else = TRUE;
		}
		//							  1           2 3       4 5
		Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%s_read(%s%s, src, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
									*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);
		*need_else = TRUE;
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}

static Dz1Error _pub_primitive_alt_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	str_t prefix_name = info->prefix;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (info->storage == NativeStorage_address)
	{
		if (var->var_is_ptr) ERR_SET_OUT(errp, EPERM);
		else
		{
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%s_write(dst, %s, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
								*need_else ? "else " : "", prefix_name, alt_name, var_name);
			*need_else = TRUE;
		}
	}
	else if (info->storage == NativeStorage_data)
	{
		if (var->var_is_ptr && chk_ptr)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name);
			*need_else = TRUE;
		}

		Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%s_write(dst, %s%s, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
							*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);
		*need_else = TRUE;
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}
// Primitive Alternated (sz IO)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enumerate Alternated (sz IO)
static Dz1Error _pub_enum_alt_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;
	ObjectInfo *tgt = var->target;

	str_t prefix_name = tgt->name;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name, var_name, tgt->name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%s_read(%s%s, src, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
						*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);
	*need_else = TRUE;

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_enum_alt_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;
	ObjectInfo *tgt = var->target;

	str_t prefix_name = tgt->name;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%s_write(dst, %s%s, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
						*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);
	*need_else = TRUE;

	Dz1Error_set(errp, 0);
	return err;
}
// Enumerate Alternated (sz IO)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Alternated (sz IO)
static Dz1Error _pub_construct_alt_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;
	ObjectInfo *tgt = var->target;

	str_t prefix_name = tgt->name;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name, var_name, tgt->name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%s_read(%s%s, src, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
						*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);
	*need_else = TRUE;

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_construct_alt_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	str_t alt_name = (str_t)ptr;
	ObjectInfo *tgt = var->target;

	str_t prefix_name = tgt->name;
	char var_name[1024] = "";

	// var_name
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	// alter_name
	if (alt_name[0] == '@')
	{
		prefix_name = "";
		alt_name++;
	} 

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	Dz1Thread_ftprintf(fp, tab, "%sif ((sz = %s%s_write(dst, %s%s, ed, param, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
						*need_else ? "else " : "", prefix_name, alt_name, var->var_is_ptr ? "" : "&", var_name);
	*need_else = TRUE;

	Dz1Error_set(errp, 0);
	return err;
}
// Construct Alternated (sz IO)
///////////////////////////////////////////////////////////////////////////////

ObjectTypeMembPublishApi membAltSzPublishApi[] =
{
	{ ObjectType_primitive,	_pub_primitive_alt_sz_read,	_pub_primitive_alt_sz_write },
	{ ObjectType_enumerate,	_pub_enum_alt_sz_read,		_pub_enum_alt_sz_write },
	{ ObjectType_structure,	_pub_construct_alt_sz_read,	_pub_construct_alt_sz_write },
	{ ObjectType_union,		_pub_construct_alt_sz_read,	_pub_construct_alt_sz_write },
	{ ObjectType_array,		_pub_construct_alt_sz_read,	_pub_construct_alt_sz_write },
	{ ObjectType_index,		_pub_construct_alt_sz_read,	_pub_construct_alt_sz_write },
	{ ObjectType_max }
};

