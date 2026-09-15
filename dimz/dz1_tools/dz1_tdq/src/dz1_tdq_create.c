#include "dz1_tdq_def_util.h"
#include "dz1_tdq_row_def_util.h"
#include "dz1_tdq_tbl_def_util.h"
#include "dz1_tdq_create.h"
#include "dz1_tdq_types.h"

static bool_t _tbl_create_null_opt(Dz1ElasticBuf *dst, Dz1TdqNullOpt *null_opt, Dz1Error *errp)
{
	if (null_opt != NULL)
	{
		if (Dz1Str_isVoid(null_opt->dflt_val))
			ELB_PUSH_STR(dst, Dz1Text(" NOT NULL"), errp);
		else
		{
			ELB_PUSH_STR(dst, Dz1Text(" NOT NULL DEFAULT "), errp);
			ELB_PUSH_STR(dst, null_opt->dflt_val, errp);
		}
	}
	else ELB_PUSH_STR(dst, Dz1Text(" NULL"), errp);
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// INTEGER Type
static Dz1Str _dbh_int_type_[] =
{
	DBH_TYPE_INT8,
	DBH_TYPE_INT16,
	DBH_TYPE_INT32,
	DBH_TYPE_INT64
};

static bool_t _create_table_column_define_build_query_num(Dz1ElasticBuf *dst, Dz1TdqSqlTypeSpec *desc, Dz1TdqNullOpt *null_opt, Dz1Error *errp)
{
	Dz1Str ret = NULL;
	Dz1TdqSqlNumSpec *param = (Dz1TdqSqlNumSpec *)desc->x.__ptr__;

	u32_t type_idx = (desc->present >> 1) & 0x7;
	Dz1Str type = _dbh_int_type_[type_idx];

	bool_t unsigned_flag = (desc->present & 0x1) ? TRUE : FALSE;

	s64_t size_limit = (param != NULL && param->size > 0) ? param->size : -1;
	bool_t auto_inc = (param != NULL) ? param->auto_inc : FALSE;

	ELB_PUSH_STR(dst, type, errp);													// {type}

	if (size_limit != -1)
	{
		TCHAR digits[32] = { 0, };
		Dz1Str_fromS64(digits, 32, size_limit);

		ELB_PUSH_CHR(dst, Dz1Text('('), errp);										// (
		ELB_PUSH_STR(dst, digits, errp);
		ELB_PUSH_CHR(dst, Dz1Text(')'), errp);										// )
	}

	///////////////////////////////////////////////////
	// UNSIGNED
	if (unsigned_flag) ELB_PUSH_STR(dst, Dz1Text(" UNSIGNED"), errp);
	///////////////////////////////////////////////////

	///////////////////////////////////////////////////
	// [NOT] NULL
	if (_tbl_create_null_opt(dst, null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	///////////////////////////////////////////////////

	///////////////////////////////////////////////////
	// AUTO_INCREMENT
	if (auto_inc)
	{
#if DBH_ENGINE == DBH_ENGINE_MY_SQL
		Dz1Str ac = Dz1Text(" AUTO_INCREMENT");
#elif DBH_ENGINE == DBH_ENGINE_MS_SQL
		Dz1Str ac = Dz1Text(" IDENTITY(1,1)");
#endif
		ELB_PUSH_STR(dst, ac, errp);
	}
	///////////////////////////////////////////////////
	return errp->code == 0 ? TRUE : FALSE;
}
// INTEGER Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// REAL Type
static Dz1Str _dbh_float_type_[] =
{
	DBH_TYPE_FLOAT32,
	DBH_TYPE_FLOAT64
};

static bool_t _create_table_column_define_build_query_real(Dz1ElasticBuf *dst, Dz1TdqSqlTypeSpec *desc, Dz1TdqNullOpt *null_opt, Dz1Error *errp)
{
	Dz1Str ret = NULL;
	Dz1TdqSqlRealSpec *param = (Dz1TdqSqlRealSpec *)desc->x.__ptr__;

	u32_t type_idx = (desc->present >> 1) & 0x7;
	Dz1Str type = _dbh_float_type_[type_idx];

	s64_t percision = (param != NULL) ? param->percision : -1;

	ELB_PUSH_STR(dst, type, errp);											// {type}

	if (percision != -1)
	{
		TCHAR digits[32] = { 0, };
		Dz1Str_fromS64(digits, 32, percision);

		ELB_PUSH_CHR(dst, Dz1Text('('), errp);								// (
		ELB_PUSH_STR(dst, digits, errp);
		ELB_PUSH_CHR(dst, Dz1Text(')'), errp);								// )
	}

	///////////////////////////////////////////////////
	// [NOT] NULL
	if (_tbl_create_null_opt(dst, null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	///////////////////////////////////////////////////

	return errp->code == 0 ? TRUE : FALSE;
}
// REAL Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STRING Type
static Dz1Str _dbh_str_type_[] =
{
	DBH_TYPE_STRING,
	DBH_TYPE_VSTRING,
	DBH_TYPE_NSTRING,
	DBH_TYPE_NVSTRING,
	DBH_TYPE_BINARY,
	DBH_TYPE_VBINARY
};

static bool_t _create_table_column_define_build_query_str(Dz1ElasticBuf *dst, Dz1TdqSqlTypeSpec *desc, Dz1TdqNullOpt *null_opt, Dz1Error *errp)
{
	Dz1Str ret = NULL;
	Dz1TdqSqlStrSpec *param = (Dz1TdqSqlStrSpec *)desc->x.__ptr__;

	u32_t type_idx = (desc->present & 0x7);
	Dz1Str type = _dbh_str_type_[type_idx];

	ELB_PUSH_STR(dst, type, errp);											// {type}

	if (param != NULL)
	{
		ELB_PUSH_CHR(dst, Dz1Text('('), errp);								// (
		if (param->size == -1)
			ELB_PUSH_STR(dst, Dz1Text("MAX"), errp);
		else
		{
			TCHAR digits[32] = { 0, };
			Dz1Str_fromS64(digits, 32, param->size);
			ELB_PUSH_STR(dst, digits, errp);
		}
		ELB_PUSH_CHR(dst, Dz1Text(')'), errp);								// )
	}

	///////////////////////////////////////////////////
	// [NOT] NULL
	if (_tbl_create_null_opt(dst, null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	///////////////////////////////////////////////////

	return errp->code == 0 ? TRUE : FALSE;
}
// STRING Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DATE & TIME Type
static Dz1Str _dbh_dt_type_[] =
{
	DBH_TYPE_DATE,
	DBH_TYPE_TIME,
	DBH_TYPE_DATETIME
};

static bool_t _create_table_column_define_build_query_dt(Dz1ElasticBuf *dst, Dz1TdqSqlTypeSpec *desc, Dz1TdqNullOpt *null_opt, Dz1Error *errp)
{
	Dz1Str ret = NULL;

	u32_t type_idx = (desc->present & 0x7);
	Dz1Str type = _dbh_dt_type_[type_idx];

	ELB_PUSH_STR(dst, type, errp);											// {type}

	///////////////////////////////////////////////////
	// [NOT] NULL
	if (_tbl_create_null_opt(dst, null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	///////////////////////////////////////////////////

	return errp->code == 0 ? TRUE : FALSE;
}
// DATE & TIME Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BLOB Type
static Dz1Str _dbh_blob_type_[] =
{
	DBH_TYPE_BLOB16M,
	DBH_TYPE_BLOB
};

static bool_t _create_table_column_define_build_query_blob(Dz1ElasticBuf *dst, Dz1TdqSqlTypeSpec *desc, Dz1TdqNullOpt *null_opt, Dz1Error *errp)
{
	Dz1Str ret = NULL;

	u32_t type_idx = (desc->present & 0x7);
	Dz1Str type = _dbh_blob_type_[type_idx];

	ELB_PUSH_STR(dst, type, errp);											// {type}

	///////////////////////////////////////////////////
	// [NOT] NULL
	if (_tbl_create_null_opt(dst, null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	///////////////////////////////////////////////////

	return errp->code == 0 ? TRUE : FALSE;
}
// BLOB Type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Table Create SQL : Columns
static bool_t Dz1TdqColumn_tblCreateSql(Dz1ElasticBuf *dst, Dz1TdqColumn *src, bool_t put_comma, Dz1Error *errp)
{	// name {type} ( {sz}|{total}|{low},{high} ) [UNSIGNED] [NOT NULL | NULL] [ DEFAULT {val} ]
	Dz1TdqSqlTypeSpec *spec = src->sql_type;

	u8_t category = ((spec->present & 0xF0) >> 4);

	if (put_comma) ELB_PUSH_CHR(dst, Dz1Text(','), errp);
	ELB_PUSH_CRLF(dst, errp);
	ELB_PUSH_CHR(dst, Dz1Text('\t'), errp);

	ELB_PUSH_STR(dst, src->name, errp);										// name
	ELB_PUSH_CHR(dst, Dz1Text(' '), errp);

	switch(category)
	{
	case 0:	// number
		if (_create_table_column_define_build_query_num(dst, spec, src->null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); 
		else Dz1Error_set(errp, 0);
		break;
	case 1:	// real
		if (_create_table_column_define_build_query_real(dst, spec, src->null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); 
		else Dz1Error_set(errp, 0);
		break;
	case 2:	// string
		if (_create_table_column_define_build_query_str(dst, spec, src->null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); 
		else Dz1Error_set(errp, 0);
		break;
	case 3:	// date & time
		if (_create_table_column_define_build_query_dt(dst, spec, src->null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); 
		else Dz1Error_set(errp, 0);
		break;
	case 4:	// blob
		if (_create_table_column_define_build_query_blob(dst, spec, src->null_opt, errp) == FALSE) ERR_OUT_RET(errp, FALSE); 
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
		break;
	}

	return errp->code == 0 ? TRUE : FALSE;;
}

static bool_t Dz1TdqColumnRefSeq_tblCreateSql(Dz1ElasticBuf *dst, Dz1TdqColumnRefSeq *cols, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqColumn **arr = cols->get_array(cols, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if (Dz1TdqColumn_tblCreateSql(dst, arr[i], i == 0 ? FALSE : TRUE, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Table Create SQL : Columns
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Table Create SQL : Primary Key
static bool_t Dz1TdqTblShape_tblCreatePkSql(Dz1ElasticBuf *dst, Dz1TdqRowRef *pk_cols, Dz1Str tbl_name, Dz1Error *errp)
{
	Dz1TdqColumnRefSeq *pks = NULL;
	if (pk_cols != NULL && (pks = pk_cols->seq) != NULL && pks->count(pks) > 0)
	{	// // CONSTRAINT {table_name}_PK PRIMARY KEY(col1, col2, ...)
		ELB_PUSH_CHR(dst, Dz1Text(','), errp);
		ELB_PUSH_CRLF(dst, errp);
		ELB_PUSH_CHR(dst, Dz1Text('\t'), errp);

		ELB_PUSH_STR(dst, Dz1Text("CONSTRAINT "), errp);					// CONSTARAINT
		ELB_PUSH_STR(dst, tbl_name, errp);									// {table_name}	
		ELB_PUSH_STR(dst, Dz1Text("_PK PRIMARY KEY("), errp);				// _PK PRIMARY KEY(

		if (Dz1TdqColumnRefSeq_enumNames(dst, pks, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

		ELB_PUSH_CHR(dst, Dz1Text(')'), errp);								// )
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Table Create SQL : Primary Key
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Table Create SQL : Index
static bool_t Dz1TdqIndexEntry_tblCreateIdxSql(Dz1ElasticBuf *dst, Dz1TdqIndexEntry *src, Dz1Str tbl_name, Dz1Error *errp)
{	// [UNIQUE] INDEX '{cons_name}' (col1, col2, ...)

	ELB_PUSH_CHR(dst, Dz1Text(','), errp);
	ELB_PUSH_CRLF(dst, errp);
	ELB_PUSH_CHR(dst, Dz1Text('\t'), errp);

	if (src->unique)
		ELB_PUSH_STR(dst, Dz1Text("UNIQUE "), errp);								// 'UNIQUE '
	ELB_PUSH_STR(dst, Dz1Text("INDEX "), errp);										// 'INDEX '

	ELB_PUSH_STR(dst, tbl_name, errp); ELB_PUSH_STR(dst, src->suffix_name, errp);	// '{tbl_name}{suffix_name}'

	ELB_PUSH_CHR(dst, Dz1Text('('), errp);											// (
	if (Dz1TdqColumnRefSeq_enumNames(dst, src->own_cols->seq, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	ELB_PUSH_CHR(dst, Dz1Text(')'), errp);											// )

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqIndexList_tblCreateIdxSql(Dz1ElasticBuf *dst, Dz1TdqIndexList *src, Dz1Str tbl_name, Dz1Error *errp)
{
	if (src != NULL && src->count(src) > 0)
	{
		u32_t cnt = 0;
		Dz1TdqIndexEntry **arr = src->get_array(src, &cnt, errp);
		if (arr == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
			for (i = 0; errp->code == 0 && i < cnt; i++)
			{
				if (Dz1TdqIndexEntry_tblCreateIdxSql(dst, arr[i], tbl_name, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Table Create SQL : Index
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Table Create SQL : Columns & Primary Key, Index
static bool_t Dz1TdqTblShape_tblCreateSql(Dz1ElasticBuf *dst, Dz1TdqTblShape *src, Dz1Str tbl_name, Dz1Error *errp)
{
	Dz1TdqRow *cols_spec = src->row;
	Dz1TdqColumnRefSeq *cols = cols_spec->seq;
	if (cols == NULL || cols->count(cols) == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (Dz1TdqColumnRefSeq_tblCreateSql(dst, cols, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

		// CONSTRAINT {table_name}_PK PRIMARY KEY(col1, col2,...)
		if (Dz1TdqTblShape_tblCreatePkSql(dst, src->pk, tbl_name, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

		// [UNIQUE] INDEX '{cnstr_name}'(col1, col2, ...)
		if (Dz1TdqIndexList_tblCreateIdxSql(dst, src->indexes, tbl_name, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Table Create SQL : Columns & Primary Key, Index
///////////////////////////////////////////////////////////////////////////////

static Dz1TdqColumnRefSeq *_find_peer_columns(Dz1TdqTblShape *shp, Dz1Str name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqColumnRefSeq *ret = NULL;
	Dz1TdqIndexEntry *idx = NULL;
	if (Dz1Str_isVoid(name))
	{
		ret = shp->pk->seq;
		Dz1Error_set(errp, 0);
	}
	else if ((idx = Dz1TdqIndexList_findBySuffix(shp->indexes, name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else 
	{
		ret = idx->own_cols->seq;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

typedef struct ForeignKeyModeStrMap
{
	Dz1TdqForeignKeyMode		 mode;
	Dz1Str						 str;
} ForeignKeyModeStrMap;

static ForeignKeyModeStrMap foreignKeyModeStrMap[] =
{
	{ Dz1TdqForeignKeyMode_no_action,	Dz1Text("NO ACTION") },
	{ Dz1TdqForeignKeyMode_cascade,		Dz1Text("CASCADE") },
	{ Dz1TdqForeignKeyMode_set_null,	Dz1Text("SET NULL") },
	{ Dz1TdqForeignKeyMode_set_default,	Dz1Text("SET DEFAULT") },
	{ Dz1TdqForeignKeyMode_restrict,	Dz1Text("RESTRICT") },
	{ Dz1TdqForeignKeyMode_max,			Dz1Text("RESTRICT") }
};

static Dz1Str Dz1TdqForeignKeyMode_getQueryStr(Dz1TdqForeignKeyMode src)
{
	ForeignKeyModeStrMap *i;
	for (i = foreignKeyModeStrMap; i->mode != Dz1TdqForeignKeyMode_max; i++)
		if (i->mode == src) return i->str;
	return NULL;
}

static bool_t Dz1TdqFKEntry_tblCreateSql(Dz1ElasticBuf *dst, Dz1TdqFKEntry *src, Dz1Str tbl_name, Dz1Error *errp)
{	// CONSTRAINT {cons_name} FOREIGN KEY(o_col1, o_col2) REFERENCES {peer_table_name}(p_col1, p_col2,...)
	Dz1TdqTblInstance *peer_tbl = src->peer_tbl;
	Dz1TdqTblShape *shp = peer_tbl->shape;
	Dz1TdqColumnRefSeq *peer_cols = _find_peer_columns(shp, src->peer_idx_suffix_opt, errp);
	if (peer_cols == NULL) ERR_OUT(errp);
	else
	{
		ELB_PUSH_CHR(dst, Dz1Text(','), errp);
		ELB_PUSH_CRLF(dst, errp);
		ELB_PUSH_CHR(dst, Dz1Text('\t'), errp);

		ELB_PUSH_STR(dst, Dz1Text("CONSTRAINT "), errp);								// CONSTARAINT
		ELB_PUSH_STR(dst, tbl_name, errp);ELB_PUSH_STR(dst, src->suffix_name, errp);	// {table_name}{suffix_name}
		ELB_PUSH_STR(dst, Dz1Text(" FOREIGN KEY("), errp);								// FOREIGN KEY
		if (Dz1TdqColumnRefSeq_enumNames(dst, src->own_cols->seq, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
		ELB_PUSH_STR(dst, Dz1Text(") REFERENCES "), errp);								// ) REFERENCES
		ELB_PUSH_STR(dst, src->peer_tbl->name, errp);									// {peer_table_name}
		ELB_PUSH_CHR(dst, Dz1Text('('), errp);											// (

		// find peer_tbl->shape->pk or peer_tbl->shape->indexes
		if (Dz1TdqColumnRefSeq_enumNames(dst, peer_cols, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
		ELB_PUSH_CHR(dst, Dz1Text(')'), errp);											// )

		if (src->on_update != Dz1TdqForeignKeyMode_max)
		{
			ELB_PUSH_STR(dst, Dz1Text(" ON UPDATE "), errp);
			ELB_PUSH_STR(dst, Dz1TdqForeignKeyMode_getQueryStr(src->on_update), errp);
		}

		if (src->on_update != Dz1TdqForeignKeyMode_max)
		{
			ELB_PUSH_STR(dst, Dz1Text(" ON DELETE "), errp);
			ELB_PUSH_STR(dst, Dz1TdqForeignKeyMode_getQueryStr(src->on_delete), errp);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqFKList_tblCreateFkSql(Dz1ElasticBuf *dst, Dz1TdqFKList *src, Dz1Str tbl_name, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqFKEntry **arr = NULL;
	if (src->count(src) == 0) { }
	else if ((arr = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if (Dz1TdqFKEntry_tblCreateSql(dst, arr[i], tbl_name, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqTblInstance_tblCreateSql(Dz1ElasticBuf *dst, Dz1TdqTblInstance *def, Dz1Error *errp)
{
	Dz1TdqTblShape *shape = def->shape;

	ELB_PUSH_STR(dst, Dz1Text("CREATE TABLE "), errp);							// CREATE TABLE
	ELB_PUSH_STR(dst, def->name, errp);											// {table_name}
	ELB_PUSH_STR(dst, Dz1Text(" ("), errp);										// (

	if (Dz1TdqTblShape_tblCreateSql(dst, shape, def->name, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

	if (Dz1TdqFKList_tblCreateFkSql(dst, def->fks, def->name, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

	ELB_PUSH_CRLF(dst, errp);
	ELB_PUSH_CHR(dst, Dz1Text(')'), errp);										// )
	ELB_PUSH_EOS(dst, errp);

	return TRUE;
}

static bool_t _Dz1TdqDbScheme_create(Dz1TdqDbIface *dbh, Dz1TdqTblInstance *tbl, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	bool_t tbl_status = FALSE;
	Dz1ElasticBuf *elb = NULL;
	if (dbh == NULL || tbl == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1TdqDbIface_tblExist(dbh, tbl->name, &tbl_status)).code) ERR_OUT(errp);
	else if (tbl_status)
	{	// Same Table is Exist
		Dz1Error_set(errp, EEXIST);
	}
// 	else if (tbl_status == -1)
// 	{	// Table is Exist but not same
// 	}
	else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if (Dz1TdqTblInstance_tblCreateSql(elb, tbl, errp) == FALSE) ERR_OUT(errp);
		else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(elb, errp)) == NULL) ERR_OUT(errp);
		else if (commit == -1)
		{
			Dz1Thread_printf(Dz1T("Query = ")); Dz1Str_dump((Dz1Str)bin->data, 0);
			Dz1Error_set(errp, 0);
		}
		else if (Dz1TdqDbIface_sqlCmd(dbh, (Dz1Str)bin->data, NULL, commit, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1) // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_create(Dz1TdqDbScheme *scm, Dz1Str tbl_name, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *elb = NULL;
	Dz1TdqTblInstance *tbl = NULL;
	if (scm == NULL || Dz1Str_isVoid(tbl_name)) ERR_SET_OUT(errp, EINVAL);
	else if ((tbl = Dz1TdqDbScheme_findInstance(scm, tbl_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (_Dz1TdqDbScheme_create(scm->dbh, tbl, commit, errp) == FALSE) 
	{
		if (errp->code != EEXIST) ERR_OUT(errp);
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_buildDB(Dz1TdqDbScheme *scm, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = 0;
	Dz1TdqTblInstance **arr = NULL;
	if (scm == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((arr = scm->tblseq->get_array(scm->tblseq, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		bool_t loop_commit = commit == -1 ? -1 : FALSE;
		u32_t i = 0;
		Dz1TdqTblInstance *node = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			node = arr[i];
			if (_Dz1TdqDbScheme_create(scm->dbh, node, loop_commit, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

		if (errp->code == 0)
		{
			if (commit == TRUE) 
				Dz1TdqDbIface_commit(scm->dbh, NULL);
		}
		else Dz1TdqDbIface_rollback(scm->dbh, NULL);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

