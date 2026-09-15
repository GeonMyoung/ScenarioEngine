#include "dz1_tdqc_util.h"
#include "dz1_tdqc_pub.h"

typedef struct ColumnPubRegApi
{
	Dz1TdqSqlTypeSpecPresent		 present;
	bool_t							 (*pub)(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp);
} ColumnPubRegApi;

static ColumnPubRegApi *ColumnPubRegApi_find(ColumnPubRegApi *tbl, Dz1TdqSqlTypeSpecPresent v)
{
	ColumnPubRegApi *i;
	for (i = tbl; i->present != Dz1TdqSqlTypeSpecPresent_max; i++)
		if (i->present == v) return i;
	return NULL;
}

static bool_t Dz1TdqPub_src_TblShape_nullOpt_col(FILE *fp, Dz1Str name, Dz1TdqNullOpt *opt, int tab, Dz1Error *errp)
{	// Dz1TdqNullOpt null_<name> = { \"...\" };\n"
	Dz1Thread_ftprintf(fp, tab, "Dz1TdqNullOpt null_%s = { \"%s\" };" CRLF, name, opt->dflt_val);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqPub_src_TblShape_nullOpt(FILE *fp, Dz1TdqRow *row, int tab, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqColumn **arr = row->seq->get_array(row->seq, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		Dz1TdqColumn *node = NULL;
		Dz1TdqNullOpt *null_opt = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; i < cnt; i++)
		{
			node = arr[i];
			if ((null_opt = node->null_opt) != NULL && Dz1Str_isVoid(null_opt->dflt_val) == FALSE)
			{
				if (Dz1TdqPub_src_TblShape_nullOpt_col(fp, node->name, null_opt, tab, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t mk_nul_str(char nul[64], Dz1TdqNullOpt *nul_opt, Dz1Str name)
{
	if (nul_opt == NULL) sprintf(nul, "NULL"); 
	else if (nul_opt->dflt_val == NULL) strcpy(nul, "not_null_no_default");
	else sprintf(nul, "&null_%s", name);
	return TRUE;
}

static bool_t _col_add_num(FILE *fp, Dz1TdqType type, Dz1TdqSqlNumSpec *spec, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	char spc[64] = { 0, }, nul[64] = { 0, };
	if (spec == NULL) sprintf(spc, "NULL"); else sprintf(spc, "&spec_%s", name);
	mk_nul_str(nul, nul_opt, name);

	Dz1Thread_ftprintf(fp, tab,	"else if (Dz1TdqRow_addNum(node->row, Dz1Text(\"%s\"), Dz1TdqType_%s, %s, %s, errp) == FALSE) ERR_OUT(errp);" CRLF,
																	name, Dz1TdqTypeStrA(type), spc, nul);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _col_add_s8(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_num(fp, type->present, type->x.num_s8, name, nul_opt, tab, errp);
}

static bool_t _col_add_u8(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_num(fp, type->present, type->x.num_u8, name, nul_opt, tab, errp);
}

static bool_t _col_add_s16(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_num(fp, type->present, type->x.num_s16, name, nul_opt, tab, errp);
}

static bool_t _col_add_u16(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_num(fp, type->present, type->x.num_u16, name, nul_opt, tab, errp);
}

static bool_t _col_add_s32(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_num(fp, type->present, type->x.num_s32, name, nul_opt, tab, errp);
}

static bool_t _col_add_u32(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_num(fp, type->present, type->x.num_u32, name, nul_opt, tab, errp);
}

static bool_t _col_add_s64(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_num(fp, type->present, type->x.num_s64, name, nul_opt, tab, errp);
}

static bool_t _col_add_u64(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_num(fp, type->present, type->x.num_u64, name, nul_opt, tab, errp);
}

static bool_t _col_add_r32(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	Dz1TdqSqlRealSpec *spec = type->x.num_r32;
	char nul[64] = { 0, };
	mk_nul_str(nul, nul_opt, name);
	Dz1Thread_ftprintf(fp, tab,		"else if (Dz1TdqRow_addReal(node->row, Dz1Text(\"%s\"), Dz1TdqType_num_r32, " DZ1_FMT64_A ", %s, errp) == FALSE) ERR_OUT(errp);" CRLF, name, spec->percision, nul);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _col_add_r64(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	Dz1TdqSqlRealSpec *spec = type->x.num_r64;
	char nul[64] = { 0, };
	mk_nul_str(nul, nul_opt, name);
	Dz1Thread_ftprintf(fp, tab,		"else if (Dz1TdqRow_addReal(node->row, Dz1Text(\"%s\"), Dz1TdqType_num_r64, " DZ1_FMT64_A ", %s, errp) == FALSE) ERR_OUT(errp);" CRLF, name, spec->percision, nul);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _col_add_string(FILE *fp, Dz1TdqType type, Dz1TdqSqlStrSpec *spec, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	char nul[64] = { 0, };
	mk_nul_str(nul, nul_opt, name);
	
	Dz1Thread_ftprintf(fp, tab,	"else if (Dz1TdqRow_addStr(node->row, Dz1Text(\"%s\"), Dz1TdqType_%s, "DZ1_FMT64_A", %s, errp) == FALSE) ERR_OUT(errp);" CRLF, name, Dz1TdqTypeStrA(type), spec->size, nul);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _col_add_str(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_string(fp, type->present, type->x.string, name, nul_opt, tab, errp);
}

static bool_t _col_add_vstr(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_string(fp, type->present, type->x.vstring, name, nul_opt, tab, errp);
}

static bool_t _col_add_tstr(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_string(fp, type->present, type->x.tstring, name, nul_opt, tab, errp);
}

static bool_t _col_add_vtstr(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_string(fp, type->present, type->x.vtstring, name, nul_opt, tab, errp);
}

static bool_t _col_add_bin(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_string(fp, type->present, type->x.binary, name, nul_opt, tab, errp);
}

static bool_t _col_add_vbin(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_string(fp, type->present, type->x.vbinary, name, nul_opt, tab, errp);
}

static bool_t _col_add_time(FILE *fp, Dz1TdqType type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	char nul[64] = { 0, };
	mk_nul_str(nul, nul_opt, name);
	Dz1Thread_ftprintf(fp, tab,	"else if (Dz1TdqRow_addTime(node->row, Dz1Text(\"%s\"), Dz1TdqType_%s, %s, errp) == FALSE) ERR_OUT(errp);" CRLF, name, Dz1TdqTypeStrA(type), nul);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _col_add_tmd(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_time(fp, type->present, name, nul_opt, tab, errp);
}

static bool_t _col_add_hms(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_time(fp, type->present, name, nul_opt, tab, errp);
}

static bool_t _col_add_stamp(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_time(fp, type->present, name, nul_opt, tab, errp);
}

static bool_t _col_add_largeobj(FILE *fp, Dz1TdqType type, Dz1TdqSqlBlobSpec spec, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	char nul[64] = { 0, };
	mk_nul_str(nul, nul_opt, name);
	Dz1Thread_ftprintf(fp, tab,	"else if (Dz1TdqRow_addBlob(node->row, Dz1Text(\"%s\"), Dz1TdqType_%s, Dz1TdqSqlBlobSpec_%s, %s, errp) == FALSE) ERR_OUT(errp);" CRLF,
																		 name, Dz1TdqTypeStrA(type), Dz1TdqSqlBlobSpecStrA(spec), nul);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _col_add_blob(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_largeobj(fp, type->present, type->x.blob, name, nul_opt, tab, errp);
}

static bool_t _col_add_blobL(FILE *fp, Dz1TdqSqlTypeSpec *type, Dz1Str name, Dz1TdqNullOpt *nul_opt, int tab, Dz1Error *errp)
{
	return _col_add_largeobj(fp, type->present, type->x.blobL, name, nul_opt, tab, errp);
}


static ColumnPubRegApi columnPubApi[] =
{
	{ Dz1TdqSqlTypeSpecPresent_num_s8,		_col_add_s8 },
	{ Dz1TdqSqlTypeSpecPresent_num_u8,		_col_add_u8 },
	{ Dz1TdqSqlTypeSpecPresent_num_s16,		_col_add_s16 },
	{ Dz1TdqSqlTypeSpecPresent_num_u16,		_col_add_u16 },
	{ Dz1TdqSqlTypeSpecPresent_num_s32,		_col_add_s32 },
	{ Dz1TdqSqlTypeSpecPresent_num_u32,		_col_add_u32 },
	{ Dz1TdqSqlTypeSpecPresent_num_s64,		_col_add_s64 },
	{ Dz1TdqSqlTypeSpecPresent_num_u64,		_col_add_u64 },
	{ Dz1TdqSqlTypeSpecPresent_num_r32,		_col_add_r32 },
	{ Dz1TdqSqlTypeSpecPresent_num_r64,		_col_add_r64 },
	{ Dz1TdqSqlTypeSpecPresent_string,		_col_add_str },
	{ Dz1TdqSqlTypeSpecPresent_vstring,		_col_add_vstr },
	{ Dz1TdqSqlTypeSpecPresent_tstring,		_col_add_tstr },
	{ Dz1TdqSqlTypeSpecPresent_vtstring,	_col_add_vtstr },
	{ Dz1TdqSqlTypeSpecPresent_binary,		_col_add_bin },
	{ Dz1TdqSqlTypeSpecPresent_vbinary,		_col_add_vbin },
	{ Dz1TdqSqlTypeSpecPresent_ymd,			_col_add_tmd },
	{ Dz1TdqSqlTypeSpecPresent_hms,			_col_add_hms },
	{ Dz1TdqSqlTypeSpecPresent_stamp,		_col_add_stamp },
	{ Dz1TdqSqlTypeSpecPresent_blob,		_col_add_blob },
	{ Dz1TdqSqlTypeSpecPresent_blobL,		_col_add_blobL },
	{ Dz1TdqSqlTypeSpecPresent_max }
};

static bool_t Dz1TdqPub_src_TblShape_col(FILE *fp, Dz1TdqColumn *col, int tab, Dz1Error *errp)
{
	Dz1TdqSqlTypeSpec *spec = col->sql_type;
	ColumnPubRegApi *api = ColumnPubRegApi_find(columnPubApi, spec->present);
	if (api == NULL) 
	{
		Dz1Thread_printf("!!! Dz1TdqPub_src_TblShape_col() : spec info of %s is not found(present = 0x%X)\n", col->name, spec->present);
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (api->pub(fp, spec, col->name, col->null_opt, tab, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqPub_src_TblShape_row(FILE *fp, Dz1TdqRow *row, int tab, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqColumn **arr = row->seq->get_array(row->seq, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; i < cnt; i++)
		{
			if (Dz1TdqPub_src_TblShape_col(fp, arr[i], tab, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqPub_src_TblShape_pk(FILE *fp, Dz1TdqRowRef *pk_cols, int tab, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqColumn **arr = pk_cols->seq->get_array(pk_cols->seq, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		if (cnt > 0)
		{
			u32_t i;
			Dz1Thread_fprintf(fp, CRLF);
			Dz1Thread_ftprintf(fp, tab, "else if ((node->pk = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);" CRLF);
			for (i = 0; i < cnt; i++)
				Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqRowRef_addCol(node->pk, Dz1Text(\"%s\"), node->row, errp) == FALSE) ERR_OUT(errp);" CRLF, arr[i]->name);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqPub_src_TblShape_index_entry(FILE *fp, Dz1TdqIndexEntry *idx, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "else if ((*errp = Dz1TdqIndexList_append(node->indexes, Dz1Text(\"%s\"), %s, node->row", idx->suffix_name, idx->unique ? "TRUE" : "FALSE");
	if (Dz1TdqRowRef_pub_enumerate(fp, idx->own_cols, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0);
	Dz1Thread_fprintf(fp, ", NULL)).code) ERR_OUT(errp);" CRLF);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqPub_src_TblShape_index(FILE *fp, Dz1TdqIndexList *list, int tab, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqIndexEntry **arr = list->get_array(list, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		if (cnt > 0) Dz1Thread_fprintf(fp, CRLF);
		for (i = 0; i < cnt; i++)
		{
			if (Dz1TdqPub_src_TblShape_index_entry(fp, arr[i], tab, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqShape_pubSrc_reg(FILE *fp, Dz1TdqTblShape *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int tab = 0;
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"static bool_t %s%s(Dz1TdqDbScheme *dst, Dz1Error *err)" CRLF, src->name, SHAPE_REG_POSTFIX);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"Dz1TdqTblShape *node = Dz1TdqTblShape_new(Dz1Text(\"%s\"), NULL, NULL, errp);" CRLF, src->name);
	Dz1Thread_ftprintf(fp, tab,			"if (node == NULL) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	// null_opt declare
	if (Dz1TdqPub_src_TblShape_nullOpt(fp, src->row, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&node);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"if ((node->row = Dz1TdqRow_new(errp)) == NULL) ERR_OUT(errp);" CRLF);

	if (Dz1TdqPub_src_TblShape_row(fp, src->row, tab, errp) == FALSE) 
	{
		Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "Shape %s publishing fail\n", src->name);
		ERR_OUT_RET(errp, FALSE);
	}
	else Dz1Error_set(errp, 0);
	if (Dz1TdqPub_src_TblShape_pk(fp, src->pk, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	if (Dz1TdqPub_src_TblShape_index(fp, src->indexes, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else if ((*errp = dst->shapes->add(dst->shapes, node)).code) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,					"node = NULL;" CRLF);
	Dz1Thread_ftprintf(fp, tab,					"Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(errp->code); // (Dz1TdqTblShape_delAndSetNull, (void *)&node);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,		"return errp->code == 0 ? TRUE : FALSE;;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqShape_pubHdr_reg(FILE *fp, Dz1TdqTblShape *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int tab = 0;
// 	Dz1Thread_fprintf(fp, CRLF);
// 	Dz1Thread_fprintf(fp, "DZ1_CPPLINK bool_t %s%s(Dz1TdqDbScheme *dst, Dz1Error *err);" CRLF, src->name, SHAPE_REG_POSTFIX);

	return errp->code == 0 ? TRUE : FALSE;
}
// Shape Reg
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Supply
static Dz1Error __has_blob_obj(void *ptr, Dz1TdqColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqSqlTypeSpec *spec = p->sql_type;
	u32_t category = (spec->present >> 4) & 0xF;
	if (category == 0x4)
	{
		bool_t *ret = (bool_t *)ptr;
		(*ret) = TRUE;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Number
// 	Dz1Thread_ftprintf(fp, tab,			"dst[0]->x.u64 = src->my_unum64;" CRLF);
static bool_t _col_pub_supply_num_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "dst[%u]->x.%s = src->%s;" CRLF, idx, nm, instance);
	return TRUE;
}

static bool_t _col_pub_supply_num_s8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("s8"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_num_u8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("u8"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_num_s16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("s16"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_num_u16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("u16"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_num_s32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("s32"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_num_u32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("u32"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_num_s64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("s64"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_num_u64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("u64"), memb->instance, tab, errp); }

// 	Dz1Thread_ftprintf(fp, tab,			"dst[8]->x.r64 = src->my_real;" CRLF);
static bool_t _col_pub_supply_num_r32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("r32"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_num_r64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_num_(fp, idx, Dz1Text("r64"), memb->instance, tab, errp); }
// Number
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// String
// 	Dz1Thread_ftprintf(fp, tab,			"if (Dz1Str_isVoid(src->my_str)) { dst[9]->present = Dz1TdqSqlVarPresent_nul; dst[9]->x.nul = Dz1TdqType_vtstring; }" CRLF);
// 	Dz1Thread_ftprintf(fp, tab,			"else Dz1STRNCPY(dst[9]->x.vtstring->text, src->my_str, (dst[9]->x.vtstring->alloc_byte / sizeof(TCHAR)) - 1);" CRLF);
static bool_t _col_pub_supply_str_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,	"if (Dz1Str_isVoid(src->%s)) Dz1TdqSqlVar_setNullValue(dst[%u]);" CRLF, instance, idx);
	Dz1Thread_ftprintf(fp, tab,	"else Dz1STRNCPY(dst[%u]->x.%s->text, src->%s, (dst[%u]->x.%s->alloc_byte / sizeof(TCHAR)) - 1);" CRLF, idx, nm, instance, idx, nm);
	return TRUE;
}

static bool_t _col_pub_supply_string(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_str_(fp, idx, Dz1Text("string"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_vstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_str_(fp, idx, Dz1Text("vstring"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_tstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_str_(fp, idx, Dz1Text("tstring"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_vtstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_str_(fp, idx, Dz1Text("vtstring"), memb->instance, tab, errp); }
// String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Binary
static bool_t _col_pub_supply_bin_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,	"if (src->%s == NULL || src->%s->data == NULL || src->%s->size == 0) Dz1TdqSqlVar_setNullValue(dst[%u]);" CRLF, instance, instance, instance, idx);
	Dz1Thread_ftprintf(fp, tab,	"else memcpy(dst[%u]->x.%s->data, src->%s->data, (dst[%u]->x.%s->size = src->%s->size));" CRLF, idx, nm, instance, idx, nm, instance);
	return TRUE;
}

static bool_t _col_pub_supply_binary(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_bin_(fp, idx, Dz1Text("binary"), memb->instance, tab, errp); }

static bool_t _col_pub_supply_vbinary(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_bin_(fp, idx, Dz1Text("vbinary"), memb->instance, tab, errp); }
// Binary
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Date & Time
static bool_t _col_pub_supply_time_(FILE *fp, u32_t idx, Dz1Str stnm, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_fprintf(fp, CRLF);
 	Dz1Thread_ftprintf(fp, tab, "if (src->%s == 0) Dz1TdqSqlVar_setNullValue(dst[%u]);" CRLF, instance, idx);
 	Dz1Thread_ftprintf(fp, tab, "else if (%s_setFromT(dst[%u]->x.%s, src->%s, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);" CRLF, stnm, idx, nm, instance);
	return TRUE;
}

// 	Dz1Thread_ftprintf(fp, tab,			"if (Dz1TdqSqlDate_setFromT(dst[10]->x.ymd, src->my_date, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);" CRLF);
static bool_t _col_pub_supply_ymd(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_time_(fp, idx, Dz1Text("Dz1TdqSqlDate"), Dz1Text("ymd"), memb->instance, tab, errp); }

// 	Dz1Thread_ftprintf(fp, tab,			"if (Dz1TdqSqlTime_setFromT(dst[11]->x.hms, src->my_clock, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);" CRLF);
static bool_t _col_pub_supply_hms(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_time_(fp, idx, Dz1Text("Dz1TdqSqlTime"), Dz1Text("hms"), memb->instance, tab, errp); }

// 	Dz1Thread_ftprintf(fp, tab,			"if (Dz1TdqSqlStamp_setFromT(dst[12]->x.stamp, src->my_stamp, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);" CRLF);
static bool_t _col_pub_supply_stamp(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_supply_time_(fp, idx, Dz1Text("Dz1TdqSqlStamp"), Dz1Text("stamp"), memb->instance, tab, errp); }
// Date & Time
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BLOB
static bool_t _col_pub_supply_blb_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{
	Dz1TdqcShapeOptEntry *opt = Dz1TdqcShapeOptList_findByName(opts, instance);
	if (opt == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab, "if (src->%s == NULL) Dz1TdqSqlVar_setNullValue(dst[%u]);" CRLF, instance, idx);
		Dz1Thread_ftprintf(fp, tab, "else if ((blob_write = %s_write(src->%s, errp)) == NULL) ERR_OUT_RET(errp, FALSE);" CRLF, opt->api_prefix, instance);
		Dz1Thread_ftprintf(fp, tab, "else { Dz1TdqSqlBlobToDB_delAndSetNull(&dst[%u]->x.%s->writeToDB); dst[%u]->x.%s->writeToDB = blob_write; Dz1Error_set(errp, 0); }" CRLF, idx, nm, idx, nm);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// 	Dz1Thread_ftprintf(fp, tab,			"if (src->my_blob == NULL) { dst[13]->present = Dz1TdqSqlVarPresent_nul; dst[13]->x.nul = Dz1TdqType_blob; }" CRLF);
// 	Dz1Thread_ftprintf(fp, tab,			"else if ((blob_write = Dz1BinaryBlobWrite_gen(src->my_blob, errp)) == NULL) ERR_OUT_RET(errp, FALSE);" CRLF);
// 	Dz1Thread_ftprintf(fp, tab,			"else { Dz1TdqSqlBlobToDB_delAndSetNull(&dst[13]->x.blob->writeToDB); dst[13]->x.blob->writeToDB = blob_write; Dz1Error_set(errp, 0); }" CRLF);
static bool_t _col_pub_supply_blob(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{	return _col_pub_supply_blb_(fp, idx, Dz1Text("blob"), memb->instance, opts, tab, errp); }

// 	Dz1Thread_ftprintf(fp, tab,			"if (src->my_blobl == NULL) { dst[14]->present = Dz1TdqSqlVarPresent_nul; dst[14]->x.nul = Dz1TdqType_blobL; }" CRLF);
// 	Dz1Thread_ftprintf(fp, tab,			"else if ((blob_write = Dz1BinaryBlobWrite_gen(src->my_blobl, errp)) == NULL) ERR_OUT_RET(errp, FALSE);" CRLF);
// 	Dz1Thread_ftprintf(fp, tab,			"else { Dz1TdqSqlBlobToDB_delAndSetNull(&dst[14]->x.blob->writeToDB); dst[14]->x.blob->writeToDB = blob_write; Dz1Error_set(errp, 0); }" CRLF);
static bool_t _col_pub_supply_blobL(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{	return _col_pub_supply_blb_(fp, idx, Dz1Text("blobL"), memb->instance, opts, tab, errp); }
// BLOB
///////////////////////////////////////////////////////////////////////////////

#define COL_PUB_SUP_API(name)			{ Dz1TdqSqlTypeSpecPresent_##name, _col_pub_supply_##name }
static ColumnPubSupplyApi columnPubSupplyApi[] =
{
	COL_PUB_SUP_API(num_s8),
	COL_PUB_SUP_API(num_u8),
	COL_PUB_SUP_API(num_s16),
	COL_PUB_SUP_API(num_u16),
	COL_PUB_SUP_API(num_s32),
	COL_PUB_SUP_API(num_u32),
	COL_PUB_SUP_API(num_s64),
	COL_PUB_SUP_API(num_u64),
 	COL_PUB_SUP_API(num_r32),
 	COL_PUB_SUP_API(num_r64),
	COL_PUB_SUP_API(string),
	COL_PUB_SUP_API(vstring),
	COL_PUB_SUP_API(tstring),
	COL_PUB_SUP_API(vtstring),
 	COL_PUB_SUP_API(binary),
 	COL_PUB_SUP_API(vbinary),
	COL_PUB_SUP_API(ymd),
	COL_PUB_SUP_API(hms),
	COL_PUB_SUP_API(stamp),
	COL_PUB_SUP_API(blob),
	COL_PUB_SUP_API(blobL),
	{ Dz1TdqSqlTypeSpecPresent_max, NULL }
};

static bool_t Dz1TdqPub_src_TblShape_supply_column(FILE *fp, Dz1TdqRow *row, StructureInfo *info, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{
	ColumnPubEnv *env = ColumnPubEnv_new(row->seq, info->members, errp);
	if (env == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		Dz1TdqColumn *col = NULL;
		StructMemberEntry *memb = NULL;
		ColumnPubSupplyApi *api = NULL;
		pthread_cleanup_push(ColumnPubEnv_delAndSetNull, (void *)&env);
		for (i = 0; errp->code == 0 && i < env->col_cnt; i++)
		{
			col = env->col[i];
			memb = env->memb[i];
			if ((api = ColumnPubSupplyApi_find(columnPubSupplyApi, col->sql_type->present)) == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if (api->pub(fp, i, col, memb, opts, tab, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ColumnPubEnv_delAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _has_blob_obj(Dz1TdqTblShape *shp)
{
	bool_t ret = FALSE;
	Dz1TdqRow *row = shp->row;
	row->seq->travel(row->seq, __has_blob_obj, (void *)&ret);
	return ret;
}

static bool_t Dz1TdqPub_src_TblShape_supply_unit(FILE *fp, Dz1TdqcShape *src, Dz1Error *errp)
{
	int tab = 0;
	Dz1TdqTblShape *shp = src->target;
	ObjectInfo *obj = src->src_obj, *ori = ObjectInfo_getOrigin(obj);
	StructureInfo *info = (StructureInfo *)ori->info;

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"static bool_t _%s%s(Dz1TdqSqlVar **dst, u32_t cnt, %s *src, Dz1Error *errp)" CRLF, obj->name, SHAPE_SUP_SINGLE_POSTFIX, obj->name);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	if (_has_blob_obj(src->target))
		Dz1Thread_ftprintf(fp, tab,		"Dz1TdqSqlBlobToDB *blob_write = NULL;" CRLF);

	if (Dz1TdqPub_src_TblShape_supply_column(fp, shp->row, info, src->memb_opt, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE);
	
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return errp->code == 0 ? TRUE : FALSE;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcShape_pubSrc_supply_single(FILE *fp, Dz1TdqcShape *src, Dz1Error *errp)
{
	int tab = 0;
	Dz1TdqTblShape *shp = src->target;
	ObjectInfo *obj = src->src_obj;

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"static Dz1TdqRowSupply %s%s(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp)" CRLF, obj->name, SHAPE_SUP_SINGLE_POSTFIX);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"Dz1TdqRowSupply ret = Dz1TdqRowSupply_end;" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"if (row_idx == 0)" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"if (_%s%s(dst, cnt, (%s *)ptr, errp) == FALSE) ret = Dz1TdqRowSupply_error;" CRLF, obj->name, SHAPE_SUP_SINGLE_POSTFIX, obj->name);
	Dz1Thread_ftprintf(fp, tab,				"else ret = Dz1TdqRowSupply_ok;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return ret;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcShape_pubSrc_supply_multi(FILE *fp, Dz1TdqcShape *src, Dz1Error *errp)
{
	int tab = 0;
	Dz1TdqTblShape *shp = src->target;
	ObjectInfo *obj = src->src_obj;

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"static Dz1TdqRowSupply %s%s(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp)" CRLF, obj->name, SHAPE_SUP_MULTI_POSTFIX);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"Dz1TdqRowSupply ret = Dz1TdqRowSupply_ok;" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"Dz1TdqSupplyArg *arg = (Dz1TdqSupplyArg *)ptr;" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"if (row_idx < arg->cnt)" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"%s **arr = (%s **)arg->arr;" CRLF, obj->name, obj->name);
	Dz1Thread_ftprintf(fp, tab,				"if (_%s%s(dst, cnt, arr[row_idx], errp) == FALSE) ret = Dz1TdqRowSupply_error;" CRLF, obj->name, SHAPE_SUP_SINGLE_POSTFIX);
	Dz1Thread_ftprintf(fp, tab,				"else ret = Dz1TdqRowSupply_ok;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else ret = Dz1TdqRowSupply_end;" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return ret;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcShape_pubSrc_supply(FILE *fp, Dz1TdqcShape *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1TdqPub_src_TblShape_supply_unit(fp, src, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcShape_pubSrc_supply_single(fp, src, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcShape_pubSrc_supply_multi(fp, src, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcShape_pubHdr_supply(FILE *fp, Dz1TdqcShape *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqTblShape *shp = src->target;
	ObjectInfo *obj = src->src_obj;

// 	Dz1Thread_fprintf(fp, CRLF);
// 	Dz1Thread_fprintf(fp, "DZ1_CPPLINK Dz1TdqRowSupply %s%s(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp);" CRLF, obj->name, SHAPE_SUP_SINGLE_POSTFIX);
// 	Dz1Thread_fprintf(fp, "DZ1_CPPLINK Dz1TdqRowSupply %s%s(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp);" CRLF, obj->name, SHAPE_SUP_MULTI_POSTFIX);

	return errp->code == 0 ? TRUE : FALSE;
}
// Supply
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Take
//	else if (Dz1TdqSqlVarGetStr(&node->my_str, src[9], errp) == FALSE) ERR_OUT(errp);
static bool_t _col_pub_talloc_str_(FILE *fp, u32_t idx, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab,	"else if (Dz1TdqSqlVarGetStr(&node->%s, src[%u], errp) == FALSE) ERR_OUT(errp);" CRLF, instance, idx);
	return TRUE;
}

static bool_t _col_pub_talloc_string(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_str_(fp, idx, memb->instance, tab, errp); }

static bool_t _col_pub_talloc_vstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_str_(fp, idx, memb->instance, tab, errp); }

static bool_t _col_pub_talloc_tstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_str_(fp, idx, memb->instance, tab, errp); }

static bool_t _col_pub_talloc_vtstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_str_(fp, idx, memb->instance, tab, errp); }

static bool_t _col_pub_talloc_bin_(FILE *fp, u32_t idx, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab,	"else if (Dz1TdqSqlVarGetBin(&node->%s, src[%u], src_stat[%u], errp) == FALSE) ERR_OUT(errp);" CRLF, instance, idx, idx);
	return TRUE;
}

static bool_t _col_pub_talloc_binary(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_bin_(fp, idx, memb->instance, tab, errp); }

static bool_t _col_pub_talloc_vbinary(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_bin_(fp, idx, memb->instance, tab, errp); }

// 			else if (Dz1TdqSqlVarGetDate(&node->my_date, src[10], errp) == FALSE) ERR_OUT(errp);
// 			else if (Dz1TdqSqlVarGetTime(&node->my_clock, src[11], errp) == FALSE) ERR_OUT(errp);
// 			else if (Dz1TdqSqlVarGetStamp(&node->my_stamp, src[12], errp) == FALSE) ERR_OUT(errp);
static bool_t _col_pub_talloc_time_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarGet%s(&node->%s, src[%u], errp) == FALSE) ERR_OUT(errp);" CRLF, nm, instance, idx);
	return TRUE;
}

// else if (Dz1TdqSqlVarGetDate(&node->my_date, src[10], errp) == FALSE) ERR_OUT(errp);
static bool_t _col_pub_talloc_ymd(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_time_(fp, idx, Dz1Text("Date"), memb->instance, tab, errp); }

// else if (Dz1TdqSqlVarGetTime(&node->my_clock, src[11], errp) == FALSE) ERR_OUT(errp);
static bool_t _col_pub_talloc_hms(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_time_(fp, idx, Dz1Text("Time"), memb->instance, tab, errp); }

// else if (Dz1TdqSqlVarGetStamp(&node->my_stamp, src[12], errp) == FALSE) ERR_OUT(errp);
static bool_t _col_pub_talloc_stamp(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_time_(fp, idx, Dz1Text("Stamp"), memb->instance, tab, errp); }

// else if (Dz1BinaryDB_read(&node->my_blob, src[13], errp) == FALSE) ERR_OUT(errp);
// else if (Dz1BinaryDB_read(&node->my_blobl, src[14], errp) == FALSE) ERR_OUT(errp);
static bool_t _col_pub_talloc_blb_(FILE *fp, u32_t idx, Dz1Str instance, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{
	Dz1TdqcShapeOptEntry *opt = Dz1TdqcShapeOptList_findByName(opts, instance);
	if (opt == NULL) 
	{
		Dz1Thread_printf("opts not found : %s\n", instance);
		ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		Dz1Thread_ftprintf(fp, tab, "else if (%s_read(&node->%s, src[%u], errp) == FALSE) ERR_OUT(errp);" CRLF, opt->api_prefix, instance, idx);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// else if (Dz1BinaryDB_read(&node->my_blob, src[13], errp) == FALSE) ERR_OUT(errp);
static bool_t _col_pub_talloc_blob(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_blb_(fp, idx, memb->instance, opts, tab, errp); }

// else if (Dz1BinaryDB_read(&node->my_blobl, src[14], errp) == FALSE) ERR_OUT(errp);
static bool_t _col_pub_talloc_blobL(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_talloc_blb_(fp, idx, memb->instance, opts, tab, errp); }

#define COL_PUB_TALLOC_API(name)			{ Dz1TdqSqlTypeSpecPresent_##name, _col_pub_talloc_##name }
static ColumnPubSupplyApi columnPubTakeAllocApi[] =
{
	COL_PUB_TALLOC_API(string),
	COL_PUB_TALLOC_API(vstring),
	COL_PUB_TALLOC_API(tstring),
	COL_PUB_TALLOC_API(vtstring),
	COL_PUB_TALLOC_API(binary),
	COL_PUB_TALLOC_API(vbinary),
	COL_PUB_TALLOC_API(ymd),
	COL_PUB_TALLOC_API(hms),
	COL_PUB_TALLOC_API(stamp),
	COL_PUB_TALLOC_API(blob),
	COL_PUB_TALLOC_API(blobL),
	{ Dz1TdqSqlTypeSpecPresent_max, NULL }
};

// node->my_unum64 = Dz1TdqSqlVarGetNum(src[0], u64, 0);
// node->my_num64  = Dz1TdqSqlVarGetNum(src[1], s64, 0);
// node->my_unum32 = Dz1TdqSqlVarGetNum(src[2], u32, 0);
// node->my_num32  = Dz1TdqSqlVarGetNum(src[3], s32, 0);
// node->my_unum16 = Dz1TdqSqlVarGetNum(src[4], u16, 0);
// node->my_num16  = Dz1TdqSqlVarGetNum(src[5], s16, 0);
// node->my_unum8	= Dz1TdqSqlVarGetNum(src[6], u8, 0);
// node->my_num8	= Dz1TdqSqlVarGetNum(src[7], s8, 0);
// node->my_real	= Dz1TdqSqlVarGetNum(src[8], r64, 0.0);
static bool_t _col_pub_tassign_num_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "node->%s = Dz1TdqSqlVarGetNum(src[%u], %s, 0);" CRLF, instance, idx, nm);
	return TRUE;
}

static bool_t _col_pub_tassign_num_s8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("s8"), memb->instance, tab, errp); }

static bool_t _col_pub_tassign_num_u8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("u8"), memb->instance, tab, errp); }

static bool_t _col_pub_tassign_num_s16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("s16"), memb->instance, tab, errp); }

static bool_t _col_pub_tassign_num_u16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("u16"), memb->instance, tab, errp); }

static bool_t _col_pub_tassign_num_s32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("s32"), memb->instance, tab, errp); }

static bool_t _col_pub_tassign_num_u32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("u32"), memb->instance, tab, errp); }

static bool_t _col_pub_tassign_num_s64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("s64"), memb->instance, tab, errp); }

static bool_t _col_pub_tassign_num_u64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("u64"), memb->instance, tab, errp); }

// 	Dz1Thread_ftprintf(fp, tab,			"dst[8]->x.r64 = src->my_real;" CRLF);
static bool_t _col_pub_tassign_num_r32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("r32"), memb->instance, tab, errp); }
static bool_t _col_pub_tassign_num_r64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_tassign_num_(fp, idx, Dz1Text("r64"), memb->instance, tab, errp); }

#define COL_PUB_TASSIGN_API(name)			{ Dz1TdqSqlTypeSpecPresent_##name, _col_pub_tassign_##name }
static ColumnPubSupplyApi columnPubTakeAssignApi[] =
{
	COL_PUB_TASSIGN_API(num_s8),
	COL_PUB_TASSIGN_API(num_u8),
	COL_PUB_TASSIGN_API(num_s16),
	COL_PUB_TASSIGN_API(num_u16),
	COL_PUB_TASSIGN_API(num_s32),
	COL_PUB_TASSIGN_API(num_u32),
	COL_PUB_TASSIGN_API(num_s64),
	COL_PUB_TASSIGN_API(num_u64),
 	COL_PUB_TASSIGN_API(num_r32),
 	COL_PUB_TASSIGN_API(num_r64),
	{ Dz1TdqSqlTypeSpecPresent_max, NULL }
};

bool_t _pubSrc_take(FILE *fp, Dz1TdqColumnRefSeq *row_seq, ObjectInfo *entry_obj, ObjectInfo *list_obj, Dz1TdqcShapeOptList *memb_opts, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ObjectInfo *entry_ori = ObjectInfo_getOrigin(entry_obj);
	StructureInfo *entry_info = (StructureInfo *)entry_ori->info;
	ColumnPubEnv *env = ColumnPubEnv_new(row_seq, entry_info->members, errp);

	if (env == NULL) ERR_OUT(errp);
	else
	{
		u32_t i, handled = 0;
		int tab = 0;
		ColumnPubSupplyApi *api = NULL;
		Dz1TdqColumn *col = NULL;
		StructMemberEntry *memb = NULL;
		pthread_cleanup_push(ColumnPubEnv_delAndSetNull, (void *)&env);
		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab,		"static void %s%s(void *ptr, u32_t idx, Dz1TdqSqlVar **src, SQLLEN *src_stat, u32_t cnt)" CRLF, entry_obj->name, SHAPE_TAK_SINGLE_POSTFIX);
		Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_VAR(errp, err);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"%s *dst = (%s *)ptr;" CRLF, list_obj->name, list_obj->name);
		Dz1Thread_ftprintf(fp, tab,			"%s *node = %s_gen(errp);" CRLF, entry_obj->name, entry_obj->name);
		Dz1Thread_ftprintf(fp, tab,			"if (node == NULL) ERR_OUT(errp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
		Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(%s_delAndSetNull, (void *)&node);" CRLF, entry_obj->name);
		Dz1Thread_ftprintf(fp, tab,				"if (0) { }" CRLF);

		for (i = 0; i < env->col_cnt; i++)
		{
			col = env->col[i];
			memb = env->memb[i];
			if ((api = ColumnPubSupplyApi_find(columnPubTakeAllocApi, col->sql_type->present)) == NULL)
			{
				if (ColumnPubSupplyApi_find(columnPubTakeAssignApi, col->sql_type->present) == NULL)
				{
					Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! column handler missing ="); Dz1TdqColumn_dump(col, 0);
					Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! memb_opt = "); Dz1TdqcShapeOptList_dump(memb_opts, 0);
					Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! rows = "); Dz1TdqColumnRefSeq_dump(row_seq, 0);
					ERR_SET_OUT(errp, EFAULT);
				}
			}
			else api->pub(fp, i, col, memb, memb_opts, tab, errp);
		}
		Dz1Thread_ftprintf(fp, tab,				"else" CRLF);
		Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);

		for (i = 0; i < env->col_cnt; i++)
		{
			col = env->col[i];
			memb = env->memb[i];
			if ((api = ColumnPubSupplyApi_find(columnPubTakeAssignApi, col->sql_type->present)) != NULL)
				api->pub(fp, i, col, memb, memb_opts, tab, errp);
		}
		Dz1Thread_ftprintf(fp, tab,					"if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"else" CRLF);
		Dz1Thread_ftprintf(fp, tab++,				"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,						"node = NULL;" CRLF);
		Dz1Thread_ftprintf(fp, tab,						"Dz1Error_set(errp, 0);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,				"}" CRLF);
		Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(1); // (MyStructAAAA_delAndSetNull, (void *)&node);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
		Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);
		pthread_cleanup_pop(1); // (ColumnPubEnv_delAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcShape_pubSrc_take(FILE *fp, Dz1TdqcShape *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqTblShape *shp = src->target;
	Dz1TdqRow *row = shp->row;
	if (_pubSrc_take(fp, row->seq, src->src_obj, src->dst_obj, src->memb_opt, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t _pubHdr_take(FILE *fp, ObjectInfo *entry_obj, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
//	Dz1Thread_fprintf(fp, "DZ1_CPPLINK void %s%s(void *ptr, u32_t idx, Dz1TdqSqlVar **src, long *src_stat, u32_t cnt);" CRLF, entry_obj->name, SHAPE_TAK_SINGLE_POSTFIX);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcShape_pubHdr_take(FILE *fp, Dz1TdqcShape *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (_pubHdr_take(fp, src->src_obj, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Take
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// nvGen
// 		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text(\"my_unum64\"), Dz1TdqSqlVarPresent_u64, &src->my_unum64, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text(\"my_num64\"),  Dz1TdqSqlVarPresent_s64, &src->my_num64, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text(\"my_unum32\"), Dz1TdqSqlVarPresent_u32, &src->my_unum32, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text(\"my_num32\"),  Dz1TdqSqlVarPresent_s32, &src->my_num32, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text(\"my_unum16\"), Dz1TdqSqlVarPresent_u16, &src->my_unum16, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text(\"my_num16\"),  Dz1TdqSqlVarPresent_s16, &src->my_num16, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text(\"my_unum8\"),  Dz1TdqSqlVarPresent_u8,  &src->my_unum8, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text(\"my_num8\"),   Dz1TdqSqlVarPresent_s8,  &src->my_num8, errp) == FALSE) ERR_OUT(errp);" CRLF);

static bool_t _col_pub_nvg_append_p4_(FILE *fp, u32_t idx, Dz1Str postfix, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlNamedVarList_add%s(ret, Dz1Text(\"%s\"), Dz1TdqSqlVarPresent_%s, src->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, postfix, instance, nm, instance);
	return TRUE;
}

static bool_t _col_pub_nvg_append_v4_(FILE *fp, u32_t idx, Dz1Str postfix, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlNamedVarList_add%s(ret, Dz1Text(\"%s\"), Dz1TdqSqlVarPresent_%s, &src->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, postfix, instance, nm, instance);
	return TRUE;
}

static bool_t _col_pub_nvg_append_num_s8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Num"), Dz1Text("s8"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_num_u8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Num"), Dz1Text("u8"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_num_s16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Num"), Dz1Text("s16"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_num_u16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Num"), Dz1Text("u16"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_num_s32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Num"), Dz1Text("s32"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_num_u32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Num"), Dz1Text("u32"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_num_s64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Num"), Dz1Text("s64"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_num_u64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Num"), Dz1Text("u64"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_num_r32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ 
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlNamedVarList_addReal(ret, Dz1Text(\"%s\"), Dz1TdqType_num_r32, &src->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, memb->instance, memb->instance);
	return TRUE ;
}

static bool_t _col_pub_nvg_append_num_r64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ 
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlNamedVarList_addReal(ret, Dz1Text(\"%s\"), Dz1TdqType_num_r64, &src->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, memb->instance, memb->instance);
	return TRUE ;
}

static bool_t _col_pub_nvg_append_string(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_p4_(fp, idx, Dz1Text("Str"), Dz1Text("string"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_vstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_p4_(fp, idx, Dz1Text("Str"), Dz1Text("vstring"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_tstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_p4_(fp, idx, Dz1Text("Str"), Dz1Text("tstring"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_vtstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_p4_(fp, idx, Dz1Text("Str"), Dz1Text("vtstring"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_binary(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_p4_(fp, idx, Dz1Text("Str"), Dz1Text("binary"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_vbinary(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_p4_(fp, idx, Dz1Text("Str"), Dz1Text("vbinary"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_ymd(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Time"), Dz1Text("ymd"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_hms(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Time"), Dz1Text("hms"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_stamp(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_v4_(fp, idx, Dz1Text("Time"), Dz1Text("stamp"), memb->instance, tab, errp); }

static bool_t _col_pub_nvg_append_b4_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{
	Dz1TdqcShapeOptEntry *opt = Dz1TdqcShapeOptList_findByName(opts, instance);
	if (opt == NULL) 
	{
		Dz1Thread_printf("OPTS = "); Dz1TdqcShapeOptList_dump(opts, 0);
		Dz1Thread_printf("blob api prefix of \"%s\" not found\n", instance);
		ERR_SET_OUT(errp, ENOENT);
	}
	else
	{
		Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlNamedVarList_addBlob(ret, Dz1Text(\"%s\"), Dz1TdqSqlVarPresent_%s, %s_write, src->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, instance, nm, opt->api_prefix, instance);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _col_pub_nvg_append_blob(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_b4_(fp, idx, Dz1Text("blob"), memb->instance, opts, tab, errp); }

static bool_t _col_pub_nvg_append_blobL(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_append_b4_(fp, idx, Dz1Text("blobL"), memb->instance, opts, tab, errp); }

#define COL_PUB_NVG_API(name)			{ Dz1TdqSqlTypeSpecPresent_##name, _col_pub_nvg_append_##name }
static ColumnPubSupplyApi nvgAppendApi[] =
{
	COL_PUB_NVG_API(num_s8),
	COL_PUB_NVG_API(num_u8),
	COL_PUB_NVG_API(num_s16),
	COL_PUB_NVG_API(num_u16),
	COL_PUB_NVG_API(num_s32),
	COL_PUB_NVG_API(num_u32),
	COL_PUB_NVG_API(num_s64),
	COL_PUB_NVG_API(num_u64),
 	COL_PUB_NVG_API(num_r32),
 	COL_PUB_NVG_API(num_r64),
	COL_PUB_NVG_API(string),
	COL_PUB_NVG_API(vstring),
	COL_PUB_NVG_API(tstring),
	COL_PUB_NVG_API(vtstring),
	COL_PUB_NVG_API(binary),
	COL_PUB_NVG_API(vbinary),
	COL_PUB_NVG_API(ymd),
	COL_PUB_NVG_API(hms),
	COL_PUB_NVG_API(stamp),
	COL_PUB_NVG_API(blob),
	COL_PUB_NVG_API(blobL),
	{ Dz1TdqSqlTypeSpecPresent_max, NULL }
};

//	Dz1Thread_ftprintf(fp, tab, "Dz1TdqSqlNamedVarList_removeByName(temp, Dz1Text("my_unum64"));" CRLF);
static bool_t _col_pub_nvg_remove_(FILE *fp, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "Dz1TdqSqlNamedVarList_removeByName(temp, Dz1Text(\"%s\"));" CRLF, instance);
	return TRUE;
}
static bool_t _col_pub_nvg_remove_num_s8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_u8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_s16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_u16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_s32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_u32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_s64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_u64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_r32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_num_r64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_string(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_vstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_tstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_vtstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_ymd(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_hms(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_stamp(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_blob(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

static bool_t _col_pub_nvg_remove_blobL(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_nvg_remove_(fp, memb->instance, tab, errp); }

#define COL_PUB_NVG_REMOVE_API(name)			{ Dz1TdqSqlTypeSpecPresent_##name, _col_pub_nvg_remove_##name }
static ColumnPubSupplyApi nvgRemoveApi[] =
{
	COL_PUB_NVG_REMOVE_API(num_s8),
	COL_PUB_NVG_REMOVE_API(num_u8),
	COL_PUB_NVG_REMOVE_API(num_s16),
	COL_PUB_NVG_REMOVE_API(num_u16),
	COL_PUB_NVG_REMOVE_API(num_s32),
	COL_PUB_NVG_REMOVE_API(num_u32),
	COL_PUB_NVG_REMOVE_API(num_s64),
	COL_PUB_NVG_REMOVE_API(num_u64),
 	COL_PUB_NVG_REMOVE_API(num_r32),
 	COL_PUB_NVG_REMOVE_API(num_r64),
	COL_PUB_NVG_REMOVE_API(string),
	COL_PUB_NVG_REMOVE_API(vstring),
	COL_PUB_NVG_REMOVE_API(tstring),
	COL_PUB_NVG_REMOVE_API(vtstring),
// 	COL_PUB_NVG_REMOVE_API(bin),
// 	COL_PUB_NVG_REMOVE_API(vbin),
	COL_PUB_NVG_REMOVE_API(ymd),
	COL_PUB_NVG_REMOVE_API(hms),
	COL_PUB_NVG_REMOVE_API(stamp),
	COL_PUB_NVG_REMOVE_API(blob),
	COL_PUB_NVG_REMOVE_API(blobL),
	{ Dz1TdqSqlTypeSpecPresent_max, NULL }
};

static bool_t _remove_key_col(FILE *fp, ColumnPubEnv *env, ColumnPubSupplyApi *tbl, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{
	u32_t i;
	ColumnPubSupplyApi *api = NULL;
	Dz1TdqColumn *col = NULL;
	StructMemberEntry *memb = NULL;
	for (i = 0; i < env->col_cnt; i++)
	{
		col = env->col[i];
		memb = env->memb[i];
//		if (memb->isIndex)
		if (StructMemberEntry_isIndex(memb))
		{
			if ((api = ColumnPubSupplyApi_find(tbl, col->sql_type->present)) == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if (api->pub(fp, i, col, memb, opts, tab, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcShape_pubSrc_nvg(FILE *fp, Dz1TdqcShape *src, Dz1Error *errp)
{
	int tab = 0;
	Dz1TdqTblShape *shape = src->target;
	Dz1TdqRow *row = shape->row;
	ObjectInfo *src_obj = src->src_obj, *ori = ObjectInfo_getOrigin(src_obj);
	StructureInfo *info = (StructureInfo *)ori->info;
	ColumnPubEnv *env = ColumnPubEnv_new(row->seq, info->members, errp);
	if (env == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ColumnPubEnv_delAndSetNull, (void *)&env);
		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab,		"static Dz1TdqSqlNamedVarList *_%s_nvListGen(%s *src, Dz1Error *errp)" CRLF, src_obj->name, src_obj->name);
		Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"Dz1TdqSqlNamedVarList *ret = NULL;" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"if (src == NULL) ERR_SET_OUT(errp, EINVAL);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"else if ((ret = Dz1TdqSqlNamedVarList_new(errp)) == NULL) ERR_OUT(errp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
		Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"if (0) { }" CRLF);
		if (ColumnPubSupplyApi_pub(fp, env, nvgAppendApi, src->memb_opt, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
		Dz1Thread_ftprintf(fp, tab,				"else Dz1Error_set(errp, 0);" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"return ret;" CRLF);
		Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);
		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab,		"static Dz1TdqSqlNamedVarList *%s_nvListGen(%s *src, Dz1Str comma_seprated_names, Dz1Error *err) // (names == NULL | ZeroLen) : All, (names == \"@\") : All except keys" CRLF, src_obj->name, src_obj->name);
		Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"Dz1TdqSqlNamedVarList *ret = NULL, *temp = NULL;" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"if (src == NULL) ERR_SET_OUT(errp, EINVAL);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"else if ((temp = _%s_nvListGen(src, errp)) == NULL) ERR_OUT(errp);" CRLF, src_obj->name);
		Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
		Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&temp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"if (Dz1Str_isVoid(comma_seprated_names) == TRUE)" CRLF);
		Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"ret = temp;" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"temp = NULL;" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"Dz1Error_set(errp, 0);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1STRCMP(Dz1Text(\"@\"), comma_seprated_names) == 0)" CRLF);
		Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);
		if (_remove_key_col(fp, env, nvgRemoveApi, src->memb_opt, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
		//Dz1Thread_ftprintf(fp, tab,					"Dz1TdqSqlNamedVarList_removeByName(temp, Dz1Text("my_unum64"));" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"ret = temp;" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"temp = NULL;" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"Dz1Error_set(errp, 0);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"else if ((ret = Dz1TdqSqlNamedVarList_collect(temp, comma_seprated_names, errp)) == NULL) ERR_OUT(errp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"else Dz1Error_set(errp, 0);" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&temp);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"return ret;" CRLF);
		Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

		pthread_cleanup_pop(1); // (ColumnPubEnv_delAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcShape_pubHdr_nvg(FILE *fp, Dz1TdqcShape *src, Dz1Error *errp)
{
	ObjectInfo *src_obj = src->src_obj, *ori = ObjectInfo_getOrigin(src_obj);
//	Dz1Thread_fprintf(fp, "DZ1_CPPLINK Dz1TdqSqlNamedVarList *%s_nvListGen(%s *src, Dz1Str comma_seprated_names, Dz1Error *err); // (names == NULL | ZeroLen) : All, (names == \"@\") : All except keys" CRLF, src_obj->name, src_obj->name);
	return TRUE;
}
// nvGen
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1TdqcShape_pubSrc(FILE *fp, Dz1TdqcShape *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) { }
	else if (src->is_qurty_shape == FALSE && Dz1TdqShape_pubSrc_reg(fp, src->target, errp) == FALSE) ERR_OUT(errp);
	else if (src->is_qurty_shape == FALSE && Dz1TdqcShape_pubSrc_supply(fp, src, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcShape_pubSrc_take(fp, src, errp) == FALSE) ERR_OUT(errp);
	else if (src->is_qurty_shape == FALSE && Dz1TdqcShape_pubSrc_nvg(fp, src, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqcShape_pubHdr(FILE *fp, Dz1TdqcShape *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) { }
	else if (src->is_qurty_shape == FALSE && Dz1TdqShape_pubHdr_reg(fp, src->target, errp) == FALSE) ERR_OUT(errp);
	else if (src->is_qurty_shape == FALSE && Dz1TdqcShape_pubHdr_supply(fp, src, errp) == FALSE) ERR_OUT(errp);
	else if (src->is_qurty_shape == FALSE && Dz1TdqcShape_pubHdr_take(fp, src, errp) == FALSE) ERR_OUT(errp);
	else if (src->is_qurty_shape == FALSE && Dz1TdqcShape_pubHdr_nvg(fp, src, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

