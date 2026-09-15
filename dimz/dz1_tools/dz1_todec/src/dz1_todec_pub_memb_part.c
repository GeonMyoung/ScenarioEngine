#include "dz1_todec.h"

///////////////////////////////////////////////////////////////////////////////
// Primitive Partial
static Dz1Error _pub_primitive_part_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	StreamElementSimplePartial *part = (StreamElementSimplePartial *)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{	// Address Type -> Dont
		ERR_SET_OUT(errp, EPERM);
	}
	else if (info->storage == NativeStorage_data)
	{
		str_t var_prefix = var->var_is_ptr ? "*" : "";
		if (var->var_is_ptr && do_gen)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name, var_name, var->target->name);
			*need_else = TRUE;
		}

		if (*need_else)
			Dz1Thread_ftprintf(fp, tab, "else { ");
		else Dz1Thread_ftprintf(fp, tab, "");

		if (part->byte_sz == Dz1TodecUnitSize_Byte1)
		{
			Dz1Thread_fprintf(fp, "DZ1_STREAM_READ1(&v8, src, errp, ret);");
			if (part->shf)
				Dz1Thread_fprintf(fp, " %s%s = (%s)((v8 & %s) << %u);", var_prefix, var_name, ori->name, part->mask, part->shf);
			else Dz1Thread_fprintf(fp, " %s%s = (%s)(v8 & %s);", var_prefix, var_name, ori->name, part->mask);
		}
		else
		{
			Dz1Thread_fprintf(fp, "DZ1_STREAM_READ%d(&v%d, src, ed, errp, ret);", part->byte_sz, part->byte_sz * 8);
			if (part->shf)
				Dz1Thread_fprintf(fp, " %s%s = (%s)((v%d & %s) << %u);", var_prefix, var_name, ori->name, part->byte_sz * 8, part->mask, part->shf);
			else Dz1Thread_fprintf(fp, " %s%s = (%s)(v%d & %s);", var_prefix, var_name, ori->name, part->byte_sz * 8, part->mask);
		}

		if (*need_else) Dz1Thread_fprintf(fp, "}");
		Dz1Thread_fprintf(fp, NEW_LINE);
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}

static Dz1Error _pub_primitive_part_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	StreamElementSimplePartial *part = (StreamElementSimplePartial *)ptr;

	ObjectInfo *ori = var->origin;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{
		ERR_SET_OUT(errp, EPERM);
	}
	else if (info->storage == NativeStorage_data)
	{
		str_t var_prefix = var->var_is_ptr ? "*" : "";

		if (var->var_is_ptr && chk_ptr)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name);
			*need_else = TRUE;
		}

		if (*need_else)
			Dz1Thread_ftprintf(fp, tab, "else { ");
		else Dz1Thread_ftprintf(fp, tab, "");

		if (part->byte_sz == Dz1TodecUnitSize_Byte1)
		{
			if (part->shf)
				Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE1(dst, (%s)((%s%s >> %d) & %s), errp, ret);", part->byte_tp, var_prefix, var_name, part->shf, part->mask);
			else Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE1(dst, (%s)(%s%s & %s), errp, ret);", part->byte_tp, var_prefix, var_name, part->mask);
		}
		else
		{
			if (part->shf)
				Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE%d(dst, (%s)((%s%s >> %d) & %s), ed, errp, ret);", part->byte_sz, var_prefix, var_name, part->shf, part->mask);
			else Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE%d(dst, (%s)(%s%s & %s), ed, errp, ret);", part->byte_sz, var_prefix, var_name, part->mask);
		}

		if (*need_else) Dz1Thread_fprintf(fp, "}");
		Dz1Thread_fprintf(fp, NEW_LINE);
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}
// Primitive Partial
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enumerate Partial
static Dz1Error _pub_enum_part_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StreamElementSimplePartial *part = (StreamElementSimplePartial *)ptr;

	ObjectInfo *tgt = var->target;

	str_t var_prefix = var->var_is_ptr ? "*" : "";
	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name, var_name, var->target->name);
		*need_else = TRUE;
	}

	if (*need_else) Dz1Thread_ftprintf(fp, tab, "else { ");
	else Dz1Thread_ftprintf(fp, tab, "");

	if (part->byte_sz == Dz1TodecUnitSize_Byte1)
	{
		Dz1Thread_fprintf(fp, "DZ1_STREAM_READ1(&v8, src, errp, ret);");
		if (part->shf)
			Dz1Thread_fprintf(fp, " %s%s = (%s)((v8 & %s) << %u);", var_prefix, var_name, tgt->name, part->mask, part->shf);
		else Dz1Thread_fprintf(fp, " %s%s = (%s)(v8 & %s);", var_prefix, var_name, tgt->name, part->mask);
	}
	else
	{
		int bit_sz = part->byte_sz * 8;
		Dz1Thread_fprintf(fp, "DZ1_STREAM_READ%d(&v%d, src, ed, errp, ret);", part->byte_sz, bit_sz);
		if (part->shf)
			Dz1Thread_fprintf(fp, " %s%s = (%s)((v%d & %s) << %u);", var_prefix, var_name, tgt->name, bit_sz, part->mask, part->shf);
		else Dz1Thread_fprintf(fp, " %s%s = (%s)(v%d & %s);", var_prefix, var_name, tgt->name, bit_sz, part->mask);
	}

	if (*need_else) Dz1Thread_fprintf(fp, "}");
	Dz1Thread_fprintf(fp, NEW_LINE);

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_enum_part_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StreamElementSimplePartial *part = (StreamElementSimplePartial *)ptr;

	str_t var_prefix = var->var_is_ptr ? "*" : "";
	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	if (*need_else) Dz1Thread_ftprintf(fp, tab, "else { ");
	else Dz1Thread_ftprintf(fp, tab, "");

	if (part->byte_sz == Dz1TodecUnitSize_Byte1)
	{
		if (part->shf)
			Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE1(dst, (%s)((%s%s >> %d) & %s), errp, ret);", 
									part->byte_tp, var_prefix, var_name, part->shf, part->mask);
		else Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE1(dst, (%s)(%s%s & %s), errp, ret);", 
									part->byte_tp, var_prefix, var_name, part->mask);
	}
	else
	{
		if (part->shf)
			Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE%d(dst, (%s)((%s%s >> %d) & %s), ed, errp, ret);", 
									part->byte_sz, part->byte_tp, var_prefix, var_name, part->shf, part->mask);
		else Dz1Thread_fprintf(fp, "DZ1_STREAM_WRITE%d(dst, (%s)(%s%s & %s), ed, errp, ret);", 
									part->byte_sz, part->byte_tp, var_prefix, var_name, part->mask);
	}
	
	if (*need_else) Dz1Thread_fprintf(fp, "}");
	Dz1Thread_fprintf(fp, NEW_LINE);

	Dz1Error_set(errp, 0);
	return err;
}
// Enumerate Partial
///////////////////////////////////////////////////////////////////////////////


ObjectTypeMembPublishApi membPartPublishApi[] =
{	// primitive(data_storage), enumerate only
 	{ ObjectType_primitive,	_pub_primitive_part_read,	_pub_primitive_part_write },
 	{ ObjectType_enumerate,	_pub_enum_part_read,		_pub_enum_part_write },
	{ ObjectType_max }
};

///////////////////////////////////////////////////////////////////////////////
// Primitive Partial (sz IO)
static Dz1Error _pub_primitive_part_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{	// if ((sz = Dz1Stream_read?(src, &{dst}, ed, errp)) < 0) ERR_OUT(errp);
	DZ1_ERROR_SAFE_VAR(errp, err);
	StreamElementSimplePartial *part = (StreamElementSimplePartial *)ptr;

	ObjectInfo *ori = var->origin;
	ObjectInfo *tgt = var->target;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{	// Pointer type Primitive
		ERR_SET_OUT(errp, EPERM);
	}
	else if (info->storage == NativeStorage_data)
	{	// Scalar type Primitive
		str_t var_prefix = var->var_is_ptr ? "*" : "";
		Dz1TodecUnitSize dst_sz = _resolve_prim_size(info, errp);

		if (dst_sz == Dz1TodecUnitSize_max) ERR_OUT_RET(errp, err);

		if (var->var_is_ptr && do_gen)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT(errp);" NEW_LINE, *need_else ? "else " : "", var_name, var_name, var->target->name);
			*need_else = TRUE;
		}

		if (part->byte_sz == Dz1TodecUnitSize_Byte1)
		{
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_read1(&v8, src, errp)) < 0) ERR_OUT(errp);" NEW_LINE, *need_else ? "else " : "");
			Dz1Thread_ftprintf(fp, tab, "else %s%s = (%s)((v8 & %s) << %d);" NEW_LINE, var_prefix, var_name, tgt->name, part->mask, part->shf);
		}
		else
		{
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_read%d(&v%u, src, ed, errp)) < 0) ERR_OUT(errp);" NEW_LINE,
											*need_else ? "else " : "", part->byte_sz, part->byte_sz * 8);
			Dz1Thread_ftprintf(fp, tab, "else %s%s = (%s)((v%u & %s) << %d);" NEW_LINE, 
											var_prefix, var_name, tgt->name, part->byte_sz * 8, part->mask, part->shf);
		}
		*need_else = FALSE;
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}

static Dz1Error _pub_primitive_part_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StreamElementSimplePartial *part = (StreamElementSimplePartial *)ptr;

	ObjectInfo *ori = var->origin;
//	ObjectInfo *tgt = var->target;
	PrimitiveInfo *info = (PrimitiveInfo *)ori->info;

	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (info->storage == NativeStorage_address)
	{
		ERR_SET_OUT(errp, EPERM);
	}
	else if (info->storage == NativeStorage_data)
	{
		str_t var_prefix = var->var_is_ptr ? "*" : "";

		if (var->var_is_ptr && chk_ptr)
		{	// Gen Target
			Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
								*need_else ? "else " : "", var_name);
			*need_else = TRUE;
		}

		if (part->byte_sz == Dz1TodecUnitSize_Byte1)
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_write1(dst, (%s)((%s%s & %s) >> %d), errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
							   *need_else ? "else " : "", part->byte_tp, var_prefix, var_name, part->mask, part->shf);
		else
			Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_write%d(dst, (%s)((%s%s & %s) >> %d), errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
							   *need_else ? "else " : "", part->byte_sz, part->byte_tp, var_prefix, var_name, part->mask, part->shf);
		*need_else = TRUE;
	}
	else ERR_SET_OUT(errp, EPERM);

	return err;
}
// Primitive Partial (sz IO)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enumerate Partial (sz IO)
static Dz1Error _pub_enum_part_sz_read(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t do_gen, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StreamElementSimplePartial *part = (StreamElementSimplePartial *)ptr;

	ObjectInfo *tgt = var->target;

	str_t var_prefix = var->var_is_ptr ? "*" : "";
	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "dst->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && do_gen)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL && (%s = %s_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name, var_name, var->target->name);
		*need_else = TRUE;
	}

	if (part->byte_sz == Dz1TodecUnitSize_Byte1)
	{
		Dz1Thread_ftprintf(fp, tab, "%sif((sz = Dz1Stream_read1(&v8, src, ed, errp, ret)) < 0) ERR_OUT(errp);" NEW_LINE,  *need_else ? "else " : "");
		Dz1Thread_ftprintf(fp, tab, "else %s%s = (%s)((v8 & %s) << %u);" NEW_LINE, var_prefix, var_name, tgt->name, part->mask, part->shf);
	}
	else
	{
		Dz1Thread_ftprintf(fp, tab, "%sif((sz = Dz1Stream_read%u(&v%u, src, ed, errp, ret)) < 0) ERR_OUT(errp);" NEW_LINE,  *need_else ? "else " : "", part->byte_sz, part->byte_sz * 8);
		Dz1Thread_ftprintf(fp, tab, "else %s%s = (%s)((v%u & %s) << %u);" NEW_LINE, var_prefix, var_name, tgt->name, part->byte_sz * 8, part->mask, part->shf);
	}
	*need_else = FALSE;

	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _pub_enum_part_sz_write(FILE *fp, StreamElementVariable *var, void *ptr, bool_t *need_else, bool_t chk_ptr, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	StreamElementSimplePartial *part = (StreamElementSimplePartial *)ptr;

	str_t var_prefix = var->var_is_ptr ? "*" : "";
	char var_name[1024] = "";
	if (var->mother != NULL) strcat(var_name, "src->");
	strcat(var_name, var->variable);

	if (var->var_is_ptr && chk_ptr)
	{	// Gen Target
		Dz1Thread_ftprintf(fp, tab, "%sif (%s == NULL) ERR_OUT_RET(errp, -1);" NEW_LINE,
							*need_else ? "else " : "", var_name);
		*need_else = TRUE;
	}

	if (part->byte_sz == Dz1TodecUnitSize_Byte1)
		Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_write1(dst, (%s)((%s%s >> %u) & %s), ed, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
									*need_else ? "else " : "", part->byte_tp, var_prefix, var_name, part->shf, part->mask);
	else
		Dz1Thread_ftprintf(fp, tab, "%sif ((sz = Dz1Stream_write%u(dst, (%s)((%s%s >> %u) & %s), ed, errp)) < 0) ERR_OUT(errp);" NEW_LINE, 
									*need_else ? "else " : "", part->byte_sz, part->byte_tp, var_prefix, var_name, part->shf, part->mask);
	Dz1Error_set(errp, 0);
	return err;
}
// Enumerate Partial (sz IO)
///////////////////////////////////////////////////////////////////////////////

ObjectTypeMembPublishApi membPartSzPublishApi[] =
{
	// XXX : Implement it
 	{ ObjectType_primitive,	_pub_primitive_part_sz_read,	_pub_primitive_part_sz_write },
 	{ ObjectType_enumerate,	_pub_enum_part_sz_read,			_pub_enum_part_sz_write },
	{ ObjectType_max }
};
