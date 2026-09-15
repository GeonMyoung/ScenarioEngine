#include "dz1_tdqc_util.h"
#include "dz1_tdqc_pub.h"

static bool_t Dz1TdqPub_src_TblInstance_fk_ocol(FILE *fp, Dz1TdqRowRef *cols, int tab, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqColumn **arr = cols->seq->get_array(cols->seq, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; i < cnt; i++)
			Dz1Thread_ftprintf(fp, tab,	"else if (DBHColDefRefList_addCol(node->own_cols, \"%s\", row_spec, errp) == FALSE) ERR_OUT(errp);" CRLF, arr[i]->name);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqPub_src_TblInstance_fks1(FILE *fp, Dz1Str tbl_name, Dz1TdqFKList *fks, int tab, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqFKEntry **arr = fks->get_array(fks, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		char peer_idx_suffix_opt[64] = { 0, };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; i < cnt; i++)
		{
			if (arr[i]->peer_idx_suffix_opt != NULL && arr[i]->peer_idx_suffix_opt[0] != 0)
				sprintf(peer_idx_suffix_opt, "Dz1Text(\"%s\")", arr[i]->peer_idx_suffix_opt);
			else strcpy(peer_idx_suffix_opt, "NULL");

			if (Dz1STRCMP(tbl_name, arr[i]->peer_tbl->name) == 0)
			{
			{
				Dz1Thread_ftprintf(fp, tab, "else if ((*errp = Dz1TdqFKList_append_self(node->fks, Dz1Text(\"%s\"), node, %s, Dz1TdqForeignKeyMode_%s, Dz1TdqForeignKeyMode_%s, shp->row",
																						arr[i]->suffix_name, peer_idx_suffix_opt, 
																						Dz1TdqForeignKeyModeStrA(arr[i]->on_update), 
																						Dz1TdqForeignKeyModeStrA(arr[i]->on_delete));
			}
			}
			else
			{
				Dz1Thread_ftprintf(fp, tab, "else if ((*errp = Dz1TdqFKList_append(node->fks, Dz1Text(\"%s\"), Dz1Text(\"%s\"), %s, Dz1TdqForeignKeyMode_%s, Dz1TdqForeignKeyMode_%s, shp->row, dst->tables",
																						arr[i]->suffix_name, arr[i]->peer_tbl->name, peer_idx_suffix_opt, 
																						Dz1TdqForeignKeyModeStrA(arr[i]->on_update), 
																						Dz1TdqForeignKeyModeStrA(arr[i]->on_delete));
			}
			if (Dz1TdqRowRef_pub_enumerate(fp, arr[i]->own_cols, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0);
			Dz1Thread_fprintf(fp, ", NULL)).code) ERR_OUT(errp);" CRLF);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubSrc_front(FILE *fp, Dz1TdqcTblInstance *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

// 	Dz1Thread_fprintf(fp, CRLF);
// 	Dz1Thread_fprintf(fp, "static Dz1TdqTblInstance *%s = NULL;" CRLF, src->name);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubSrc_reg(FILE *fp, Dz1TdqcTblInstance *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int tab = 0;
	bool_t is_fks = src->fks->count(src->fks) > 0 ? TRUE : FALSE;

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"static bool_t %s%s(Dz1TdqDbScheme *dst, Dz1Error *err)" CRLF, src->prefix, TABLE_REG_POSTFIX);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"Dz1TdqTblInstance *node = Dz1TdqTblInstance_new(Dz1Text(\"%s\"), NULL, errp);" CRLF, src->name);
	Dz1Thread_ftprintf(fp, tab,			"if (node == NULL) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	if (is_fks) Dz1Thread_ftprintf(fp, tab, "Dz1TdqTblShape *shp = NULL;" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(Dz1TdqTblInstance_delAndSetNull, (void *)&node);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"if (0) { }" CRLF);

	if (is_fks) 
		Dz1Thread_ftprintf(fp, tab,			"else if ((node->shape = shp = Dz1TdqTblShapeList_findByName(dst->shapes, Dz1Text(\"%s\") )) == NULL) ERR_SET_OUT(errp, ENOENT);" CRLF, src->shape->name);
	else Dz1Thread_ftprintf(fp, tab,		"else if ((node->shape = Dz1TdqTblShapeList_findByName(dst->shapes, Dz1Text(\"%s\") )) == NULL) ERR_SET_OUT(errp, ENOENT);" CRLF, src->shape->name);
	if (Dz1TdqPub_src_TblInstance_fks1(fp, src->name, src->fks, tab, errp) == FALSE) ERR_OUT(errp);

	Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqDbScheme_appendInstance(dst, node, errp) == FALSE) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqDbScheme_regSimpleQuery(dst, node, errp) == FALSE) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);
//	Dz1Thread_ftprintf(fp, tab,					"%s = node;" CRLF, src->name);
	Dz1Thread_ftprintf(fp, tab,					"node = NULL;" CRLF);
	Dz1Thread_ftprintf(fp, tab,					"Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(errp->code); // (Dz1TdqTblInstance_delAndSetNull, (void *)&ret);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,		"return errp->code == 0 ? TRUE : FALSE;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF CRLF);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubSrc_ins(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShape *shp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int tab = 0;
	ObjectInfo *src_obj = shp->src_obj;
	ObjectInfo *list_obj = shp->dst_obj;

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"bool_t %s_insert(Dz1TdqDbScheme *scm, %s *row, bool_t commit, Dz1Error *err)" CRLF, src->prefix, src_obj->name);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"if (scm == NULL || row == NULL) ERR_SET_OUT(errp, EINVAL);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else if (Dz1TdqDbScheme_insert(scm, Dz1Text(\"%s\"), NULL, %s_writeRow, row, commit, errp) == FALSE) ERR_OUT(errp);" CRLF, src->name, src_obj->name);
	Dz1Thread_ftprintf(fp, tab,			"else Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return errp->code == 0 ? TRUE : FALSE;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"bool_t %s_insertA(Dz1TdqDbScheme *scm, %s **arr, u32_t cnt, bool_t commit, Dz1Error *err)" CRLF, src->prefix, src_obj->name);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"if (scm == NULL || arr == NULL || cnt == 0) ERR_SET_OUT(errp, EINVAL);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"Dz1TdqSupplyArg arg = { arr, cnt };" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"if (Dz1TdqDbScheme_insert(scm, Dz1Text(\"%s\"), NULL, %s_writeRows, (void *)&arg, commit, errp) == FALSE) ERR_OUT(errp);" CRLF, src->name, src_obj->name);
	Dz1Thread_ftprintf(fp, tab,				"else Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return errp->code == 0 ? TRUE : FALSE;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"bool_t %s_insertL(Dz1TdqDbScheme *scm, %s *rows, bool_t commit, Dz1Error *err)" CRLF, src->prefix, list_obj->name);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"u32_t cnt = 0;" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"%s **arr = NULL;" CRLF, src_obj->name);
	Dz1Thread_ftprintf(fp, tab,			"if (scm == NULL || rows == NULL || rows->count(rows) == 0) ERR_SET_OUT(errp, EINVAL);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else if ((arr = rows->get_array(rows, &cnt, errp)) == NULL) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"if (%s_insertA(scm, arr, cnt, commit, errp) == FALSE) ERR_OUT(errp);" CRLF, src->prefix);
	Dz1Thread_ftprintf(fp, tab,				"else Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return errp->code == 0 ? TRUE : FALSE;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubHdr_ins(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShape *shp, Dz1Error *err)
{
	ObjectInfo *src_obj = shp->src_obj;
	ObjectInfo *list_obj = shp->dst_obj;
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK bool_t %s_insert(Dz1TdqDbScheme *scm, %s *row, bool_t commit, Dz1Error *err);" CRLF, src->prefix, src_obj->name);
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK bool_t %s_insertA(Dz1TdqDbScheme *scm, %s **arr, u32_t cnt, bool_t commit, Dz1Error *err);" CRLF, src->prefix, src_obj->name);
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK bool_t %s_insertL(Dz1TdqDbScheme *scm, %s *rows, bool_t commit, Dz1Error *err);" CRLF, src->prefix, list_obj->name);
	return TRUE;
}

// Dz1Thread_ftprintf(fp, tab,			"Dz1Str whr = Dz1Text(\"my_unum64=?\");		// {key_col_name}=? [AND {key_col_name}=?]" CRLF);
static bool_t TblInstance_pubSrc_insWhr(FILE *fp, ColumnPubEnv *env, int tab, Dz1Error *errp)
{
	u32_t i;
	bool_t is_first = TRUE;
	StructMemberEntry *memb = NULL;
	Dz1Thread_ftprintf(fp, tab, "Dz1Str whr = Dz1Text(\"");
	for (i = 0; i < env->col_cnt; i++)
	{
		memb = env->memb[i];
//		if (memb->isIndex) 
		if (StructMemberEntry_isIndex(memb))
		{
			Dz1Thread_fprintf(fp, "%s%s=?", is_first ? "" : " AND ", memb->instance);
			is_first = FALSE;
		}
	}
	Dz1Thread_fprintf(fp, "\");" CRLF);
	return errp->code == 0 ? TRUE : FALSE;
}

// Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);" CRLF);
static bool_t _col_pub_keyreg_num_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_%s, &key->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, nm, instance);
	return TRUE;
}

static bool_t _col_pub_keyreg_num_s8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("s8"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_num_u8(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("u8"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_num_s16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("s16"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_num_u16(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("u16"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_num_s32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("s32"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_num_u32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("u32"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_num_s64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("s64"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_num_u64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("u64"), memb->instance, tab, errp); }

// 	Dz1Thread_ftprintf(fp, tab,			"dst[8]->x.r64 = src->my_real;" CRLF);
static bool_t _col_pub_keyreg_num_r32(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("r32"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_num_r64(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_num_(fp, idx, Dz1Text("r64"), memb->instance, tab, errp); }

//	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addStr(args, Dz1TdqSqlVarPresent_vtstring, key->my_str, errp) == FALSE) ERR_OUT(errp);" CRLF);
static bool_t _col_pub_keyreg_str_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addStr(args, Dz1TdqSqlVarPresent_%s, key->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, nm, instance);
	return TRUE;
}

static bool_t _col_pub_keyreg_string(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_str_(fp, idx, Dz1Text("string"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_vstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_str_(fp, idx, Dz1Text("vstring"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_tstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_str_(fp, idx, Dz1Text("tstring"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_vtstring(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_str_(fp, idx, Dz1Text("vtstring"), memb->instance, tab, errp); }

//	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addTime(args, Dz1TdqSqlVarPresent_yhd, key->my_date, errp) == FALSE) ERR_OUT(errp);" CRLF);
static bool_t _col_pub_keyreg_time_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addTime(args, Dz1TdqSqlVarPresent_%s, &key->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, nm, instance);
	return TRUE;
}

static bool_t _col_pub_keyreg_ymd(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_time_(fp, idx, Dz1Text("ymd"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_hms(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_time_(fp, idx, Dz1Text("hms"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_stamp(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{ return _col_pub_keyreg_time_(fp, idx, Dz1Text("stamp"), memb->instance, tab, errp); }

//	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addBlob(args, Dz1TdqSqlVarPresent_blob, key->my_blob, errp) == FALSE) ERR_OUT(errp);" CRLF);
static bool_t _col_pub_keyreg_blb_(FILE *fp, u32_t idx, Dz1Str nm, Dz1Str instance, int tab, Dz1Error *errp)
{
	Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addBlob(args, Dz1TdqSqlVarPresent_%s, key->%s, errp) == FALSE) ERR_OUT(errp);" CRLF, nm, instance);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _col_pub_keyreg_blob(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{	return _col_pub_keyreg_blb_(fp, idx, Dz1Text("blob"), memb->instance, tab, errp); }

static bool_t _col_pub_keyreg_blobL(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{	return _col_pub_keyreg_blb_(fp, idx, Dz1Text("blobL"), memb->instance, tab, errp); }

#define COL_PUB_KEY_REG_API(name)			{ Dz1TdqSqlTypeSpecPresent_##name, _col_pub_keyreg_##name }
static ColumnPubSupplyApi keyRegPubApi[] =
{
	COL_PUB_KEY_REG_API(num_s8),
	COL_PUB_KEY_REG_API(num_u8),
	COL_PUB_KEY_REG_API(num_s16),
	COL_PUB_KEY_REG_API(num_u16),
	COL_PUB_KEY_REG_API(num_s32),
	COL_PUB_KEY_REG_API(num_u32),
	COL_PUB_KEY_REG_API(num_s64),
	COL_PUB_KEY_REG_API(num_u64),
 	COL_PUB_KEY_REG_API(num_r32),
 	COL_PUB_KEY_REG_API(num_r64),
	COL_PUB_KEY_REG_API(string),
	COL_PUB_KEY_REG_API(vstring),
	COL_PUB_KEY_REG_API(tstring),
	COL_PUB_KEY_REG_API(vtstring),
	COL_PUB_KEY_REG_API(ymd),
	COL_PUB_KEY_REG_API(hms),
	COL_PUB_KEY_REG_API(stamp),
	{ Dz1TdqSqlTypeSpecPresent_max, NULL }
};

// Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);" CRLF);
static bool_t TblInstance_pubSrc_insArgs(FILE *fp, ColumnPubEnv *env, int tab, Dz1Error *errp)
{
	u32_t i;
	Dz1TdqColumn *col = NULL;
	StructMemberEntry *memb = NULL;
	for (i = 0; errp->code == 0 && i < env->col_cnt; i++)
	{
		col = env->col[i];
		memb = env->memb[i];
//		if (memb->isIndex) 
		if (StructMemberEntry_isIndex(memb))
		{
			ColumnPubSupplyApi *api = ColumnPubSupplyApi_find(keyRegPubApi, col->sql_type->present);
			if (api == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if (api->pub(fp, i, col, memb, NULL, tab, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubSrc_upt(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShape *shp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int tab = 0;
	Dz1TdqTblShape *shape = shp->target;
	Dz1TdqRow *row = shape->row;
	ObjectInfo *src_obj = shp->src_obj, *ori = ObjectInfo_getOrigin(src_obj);
	StructureInfo *info = (StructureInfo *)ori->info;
	ColumnPubEnv *env = ColumnPubEnv_new(row->seq, info->members, errp);
	if (env == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ColumnPubEnv_delAndSetNull, (void *)&env);
		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab,		"bool_t %s_update(Dz1TdqDbScheme *scm, %s *key, %s *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err)" CRLF, src->prefix, src_obj->name, src_obj->name);
		Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);

		if (TblInstance_pubSrc_insWhr(fp, env, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

		Dz1Thread_ftprintf(fp, tab,			"Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"if (args == NULL) ERR_OUT(errp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
		Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"Dz1TdqSqlNamedVarList *update_vars = NULL;" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);" CRLF);
		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab,				"if (0) { }" CRLF);
		Dz1Thread_fprintf(fp, CRLF);

		if (TblInstance_pubSrc_insArgs(fp, env, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab,				"else if ((update_vars = %s_nvListGen(row, update_cols_str, errp)) == NULL) ERR_OUT(errp);" CRLF, src_obj->name);
		Dz1Thread_ftprintf(fp, tab,				"else " CRLF);
		Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&update_vars);" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"if (Dz1TdqDbScheme_update(scm, Dz1Text(\"%s\"), update_vars, whr, args, commit, errp) == FALSE) ERR_OUT(errp);" CRLF, src->name);
		Dz1Thread_ftprintf(fp, tab,					"else Dz1Error_set(errp, 0);" CRLF);
		Dz1Thread_ftprintf(fp, tab,					"pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)update_vars);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"return errp->code == 0 ? TRUE : FALSE;" CRLF);
		Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);
		pthread_cleanup_pop(1); // (ColumnPubEnv_delAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubHdr_upt(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShape *shp, Dz1Error *err)
{
	ObjectInfo *src_obj = shp->src_obj;
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK bool_t %s_update(Dz1TdqDbScheme *scm, %s *key, %s *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err);" CRLF, src->prefix, src_obj->name, src_obj->name);
	return TRUE;
}

static bool_t Dz1TdqcTblInstance_pubSrc_del(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShape *shp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int tab = 0;
	Dz1TdqTblShape *shape = shp->target;
	Dz1TdqRow *row = shape->row;
	ObjectInfo *src_obj = shp->src_obj, *ori = ObjectInfo_getOrigin(src_obj);
	StructureInfo *info = (StructureInfo *)ori->info;
	ColumnPubEnv *env = ColumnPubEnv_new(row->seq, info->members, errp);
	if (env == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ColumnPubEnv_delAndSetNull, (void *)&env);

		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab,		"bool_t %s_delete(Dz1TdqDbScheme *scm, %s *key, bool_t commit, Dz1Error *err)" CRLF, src->prefix, src_obj->name);
		Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
		// Dz1Thread_ftprintf(fp, tab,		"Dz1Str whr = Dz1Text("my_unum64=?");		// {key_col_name}=? [AND {key_col_name}=?]" CRLF);
		if (TblInstance_pubSrc_insWhr(fp, env, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
		Dz1Thread_ftprintf(fp, tab,			"Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"if (args == NULL) ERR_OUT(errp);" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
		Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"Dz1TdqSqlVar *my_unum64 = NULL;" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"if (0) { }" CRLF);
		Dz1Thread_fprintf(fp, CRLF);
		//Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);" CRLF);
		if (TblInstance_pubSrc_insArgs(fp, env, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
		Dz1Thread_fprintf(fp, CRLF);
		Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqDbScheme_delete(scm, Dz1Text(\"%s\"), whr, args, commit, errp) == FALSE) ERR_OUT(errp);" CRLF, src->name);
		Dz1Thread_ftprintf(fp, tab,				"else Dz1Error_set(errp, 0);" CRLF);
		Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);" CRLF);
		Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
		Dz1Thread_ftprintf(fp, tab,			"return errp->code == 0 ? TRUE : FALSE;" CRLF);
		Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

		pthread_cleanup_pop(1); // (ColumnPubEnv_delAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubHdr_del(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShape *shp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ObjectInfo *src_obj = shp->src_obj;
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK bool_t %s_delete(Dz1TdqDbScheme *scm, %s *key, bool_t commit, Dz1Error *err);" CRLF, src->prefix, src_obj->name);
	return TRUE;
}

static bool_t Dz1TdqcTblInstance_pubSrc_sel(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShape *shp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int tab = 0;
	ObjectInfo *src_obj = shp->src_obj;
	ObjectInfo *dst_obj = shp->dst_obj;
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"%s *%s_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)" CRLF, dst_obj->name, src->prefix);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"%s *ret = %s_gen(errp);" CRLF, dst_obj->name, dst_obj->name);
	Dz1Thread_ftprintf(fp, tab,			"if (ret == NULL) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(%s_delAndSetNull, (void *)&ret);" CRLF, dst_obj->name);
	Dz1Thread_ftprintf(fp, tab,				"if (Dz1TdqDbScheme_select(scm, Dz1Text(\"%s\"), %s_readRow, (void *)ret, whr, args, paging, errp) == FALSE)" CRLF, src->name, src_obj->name);
	Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,					"if (errp->code != ENOENT) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(errp->code); // (MyStructAAAAList_delAndSetNull, (void *)&ret);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return ret;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubHdr_sel(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShape *shp, Dz1Error *err)
{
	ObjectInfo *dst_obj = shp->dst_obj;
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK %s *%s_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);" CRLF, dst_obj->name, src->prefix);
	return TRUE;
}

bool_t Dz1TdqcTblInstance_pubSrc(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShapeList *shp_list, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcShape *shp = src->shape;
//	Dz1TdqcShape *shp = NULL;
	if (0) { }
//	else if ((shp = Dz1TdqcShapeList_findByName(shp_list, shape->name)) == NULL) ERR_OUT(errp);
	else if (Dz1TdqcTblInstance_pubSrc_front(fp, src, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcTblInstance_pubSrc_reg(fp, src, errp) == FALSE) ERR_OUT(errp);
 	else if (Dz1TdqcTblInstance_pubSrc_ins(fp, src, shp, errp) == FALSE) ERR_OUT(errp);
 	else if (Dz1TdqcTblInstance_pubSrc_upt(fp, src, shp, errp) == FALSE) ERR_OUT(errp);
 	else if (Dz1TdqcTblInstance_pubSrc_del(fp, src, shp, errp) == FALSE) ERR_OUT(errp);
 	else if (Dz1TdqcTblInstance_pubSrc_sel(fp, src, shp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcTblInstance_pubHdr_reg(FILE *fp, Dz1TdqcTblInstance *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

//	Dz1Thread_fprintf(fp, "DZ1_CPPLINK bool_t %s%s(Dz1TdqDbScheme *dst, Dz1Error *err);" CRLF, src->name, TABLE_REG_POSTFIX);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqcTblInstance_pubHdr(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShapeList *shp_list, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcShape *shp = src->shape;

	Dz1Thread_fprintf(fp, CRLF);
	if (0) { }
	else if (Dz1TdqcTblInstance_pubHdr_reg(fp, src, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcTblInstance_pubHdr_ins(fp, src, shp, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcTblInstance_pubHdr_upt(fp, src, shp, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcTblInstance_pubHdr_del(fp, src, shp, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcTblInstance_pubHdr_sel(fp, src, shp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
