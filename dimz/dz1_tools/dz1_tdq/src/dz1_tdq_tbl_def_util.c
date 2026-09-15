#include "dz1_tdq_row_def_util.h"
#include "dz1_tdq_tbl_def_util.h"
#include <dz1_tdq.h>

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumn_dump
typedef struct SqlTypeStrMap
{
	Dz1TdqSqlTypeSpecPresent present;
	Dz1Str					 name;
	void					(*spec_print)(void *ptr);
} SqlTypeStrMap;

static void _num_spec_print(void *ptr)
{
	Dz1TdqSqlNumSpec *p = (Dz1TdqSqlNumSpec *)ptr;
	if (p != NULL && (p->size != -1 || p->auto_inc)) 
	{
		bool_t comma = FALSE;
		Dz1Thread_printf(Dz1T("("));
		if (p->size != -1) { Dz1Thread_printf(DZ1_FMT64, p->size); comma = TRUE; }
		if (p->auto_inc)
		{
			if (comma) Dz1Thread_printf(Dz1T(","));
			Dz1Thread_printf(Dz1T("AUTO"));
		}
		Dz1Thread_printf(Dz1T("%s)"));
	}
}

static void _real_spec_print(void *ptr)
{
	Dz1TdqSqlRealSpec *p = (Dz1TdqSqlRealSpec *)ptr;
	if (p != NULL && p->percision != -1) Dz1Thread_printf(Dz1T("(") DZ1_FMT64 Dz1T(")"), p->percision);
}

static void _str_spec_print(void *ptr)
{
	Dz1TdqSqlStrSpec *p = (Dz1TdqSqlStrSpec *)ptr;
	if (p != NULL && p->size != -1) Dz1Thread_printf(Dz1T("(") DZ1_FMT64 Dz1T(")"), p->size);
}

static void _blob_spec_print(void *ptr)
{
	Dz1TdqSqlBlobSpec v = (Dz1TdqSqlBlobSpec)ptr;
	Dz1Thread_printf(Dz1T("(%s)"), Dz1TdqSqlBlobSpecStr(v));
}

static SqlTypeStrMap sqlTypeStrMap[] =
{
	{ Dz1TdqSqlTypeSpecPresent_num_s8,		Dz1Text("TINYINT"),				_num_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_u8,		Dz1Text("UNSIGNED TINYINT"),	_num_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_s16,		Dz1Text("SMALLINT"),			_num_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_u16,		Dz1Text("UNSIGNED SMALLINT"),	_num_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_s32,		Dz1Text("INTEGER"),				_num_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_u32,		Dz1Text("UNSIGNED INTEGER"),	_num_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_s64,		Dz1Text("BIGINT"),				_num_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_u64,		Dz1Text("UNSIGNED BIGINT"),		_num_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_r32,		Dz1Text("FLOAT"),				_real_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_num_r64,		Dz1Text("REAL"),				_real_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_string,		Dz1Text("STRING"),				_str_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_vstring,		Dz1Text("VARIABLE STRING"),		_str_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_tstring,		Dz1Text("TSTRING"),				_str_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_vtstring,	Dz1Text("VARIABLE TSTRING"),	_str_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_binary,		Dz1Text("BINARY"),				_str_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_vbinary,		Dz1Text("VARIABLE BINARY"),		_str_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_ymd,			Dz1Text("DATE"),				NULL },
	{ Dz1TdqSqlTypeSpecPresent_hms,			Dz1Text("TIME"),				NULL },
	{ Dz1TdqSqlTypeSpecPresent_stamp,		Dz1Text("DATETIME"),			NULL },
	{ Dz1TdqSqlTypeSpecPresent_blob,		Dz1Text("BLOB"),				_blob_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_blobL,		Dz1Text("LONG BLOB"),			_blob_spec_print },
	{ Dz1TdqSqlTypeSpecPresent_max,			Dz1Text("UNKNOWN"),				NULL }
};

static SqlTypeStrMap *SqlTypeStrMap_find(SqlTypeStrMap *tbl, Dz1TdqSqlTypeSpecPresent v)
{
	SqlTypeStrMap *i;
	for (i = tbl; i->present != Dz1TdqSqlTypeSpecPresent_max; i++)
		if (i->present == v) break;
	return i;
}

static void _nul_opt_println(Dz1TdqNullOpt *p)
{
	if (p != NULL)
	{
		Dz1Thread_printf(Dz1T(" NOT NULL"));
		if (Dz1Str_isVoid(p->dflt_val) == FALSE) 
			Dz1Thread_printf(Dz1T(" DEFAULT(%s)"), p->dflt_val);
	}
	Dz1Thread_printf(Dz1T("\n"));
}

void Dz1TdqColumn_dump(Dz1TdqColumn *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else
	{	// <type> name 
		Dz1TdqSqlTypeSpec *type = p->sql_type;
		SqlTypeStrMap *map = SqlTypeStrMap_find(sqlTypeStrMap, type->present);
		Dz1Thread_printf(Dz1T("%s %s"), p->name, map->name);
		if (map->spec_print != NULL) map->spec_print(type->x.__ptr__);
		_nul_opt_println(p->null_opt);
	}
}
// Dz1TdqColumn_dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqIndexEntry_dump
static Dz1Error _Dz1TdqIndexEntry_dump(void *ptr, Dz1TdqColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t *is_first = (bool_t *)ptr;
	if (*is_first) (*is_first) = FALSE;
	else Dz1Thread_printf(Dz1T(", "));
	Dz1Thread_printf(Dz1T("%s"), p->name);
	return err;
}

void Dz1TdqIndexEntry_dump(Dz1TdqIndexEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else
	{
		bool_t is_first = TRUE;
		Dz1TdqRowRef *cols = p->own_cols;
		Dz1Thread_printf(Dz1T("%s("), p->suffix_name);
		cols->seq->travel(cols->seq, _Dz1TdqIndexEntry_dump, (void *)&is_first);
		Dz1Thread_printf(Dz1T(")%s\n"), p->unique ? Dz1T(" unique") : Dz1T(""));
	}
}
// Dz1TdqIndexEntry_dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqFKEntry_dump
void Dz1TdqFKEntry_dump(Dz1TdqFKEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else
	{
		bool_t is_first = TRUE;
		Dz1TdqRowRef *cols = p->own_cols;
		Dz1TdqTblInstance *tbl = p->peer_tbl;
		Dz1Thread_printf(Dz1T("%s("), p->suffix_name);
		cols->seq->travel(cols->seq, _Dz1TdqIndexEntry_dump, (void *)&is_first);
		Dz1Thread_printf(Dz1T(")->%s"), tbl->name);
		if (Dz1Str_isVoid(p->peer_idx_suffix_opt) == FALSE) Dz1Thread_printf(Dz1T("(%s)"), p->peer_idx_suffix_opt);
		Dz1Thread_printf(Dz1T(":(%s,%s)\n"), Dz1TdqForeignKeyModeStr(p->on_update), Dz1TdqForeignKeyModeStr(p->on_update));
	}
}
// Dz1TdqFKEntry_dump
///////////////////////////////////////////////////////////////////////////////

void Dz1TdqTblInstance_dump(Dz1TdqTblInstance *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else
	{
		Dz1Thread_printf(Dz1T("%s = {\n"), p->name); tab++;

		if (p->shape == NULL) Dz1Thread_tprintf(tab, Dz1T("shape = NULL\n"));
		else Dz1Thread_tprintf(tab, Dz1T("shape = %s\n"), p->shape->name);

		if (p->fks != NULL && p->fks->count(p->fks) > 0)
		{ 
			Dz1Thread_tprintf(tab, Dz1T("fks = ")); 
			Dz1TdqFKList_dump(p->fks, tab);
		}

		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}



Dz1TdqIndexEntry *Dz1TdqIndexList_findBySuffix(Dz1TdqIndexList *list, Dz1Str suffix)
{
	Dz1TdqIndexEntry *ret = NULL;
	if (list != NULL && Dz1Str_isVoid(suffix) == FALSE)
	{
		Dz1TdqIndexEntry key = { suffix };
		ret = list->find(list, &key);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblShape
Dz1TdqTblShape *Dz1TdqTblShape_generate(Dz1Str name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqTblShape *ret = NULL;
	if (name == NULL || name[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqTblShape_new(name, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&ret);
		if ((ret->row = Dz1TdqRow_new(errp)) == NULL) ERR_OUT(errp);
		else if ((ret->pk = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqTblShape_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1TdqTblShape
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblShapeList
Dz1TdqTblShape *Dz1TdqTblShapeList_findByName(Dz1TdqTblShapeList *list, Dz1Str name)
{
	Dz1TdqTblShape *ret = NULL;
	if (list != NULL && name != NULL && name[0] != 0)
	{
		Dz1TdqTblShape key = { name };
		ret = list->find(list, &key);
	}
	return ret;
}
// Dz1TdqTblShapeList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqNameList
bool_t Dz1TdqNameList_appendName(Dz1TdqNameList *dst, Dz1Str name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(name) == TRUE) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t order = dst->count(dst);
		Dz1TdqNameEntry *node = Dz1TdqNameEntry_new(order, name, errp);
		if (node == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TdqNameEntry_delAndSetNull, (void *)&node);
			if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TdqNameEntry_delAndSetNull, (void *)&node);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1TdqNameList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Index Append
static Dz1Error _ownColAppend(Dz1TdqRowRef *dst, Dz1TdqRow *src_row, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Str col_name = NULL;
	Dz1TdqColumn *col = NULL;
	while(errp->code == 0 && (col_name = va_arg(ap, Dz1Str)) != NULL)
	{
		if ((col = Dz1TdqRow_findByName(src_row, col_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else if ((*errp = dst->index->add(dst->index, col)).code) ERR_OUT(errp);
		else 
		{
			Dz1ListAddCancelArg arg = { dst->index, &col };
			pthread_cleanup_push(Dz1TdqColumnRefList_addCancel, (void *)&arg);
			if ((*errp = dst->seq->add(dst->seq, col)).code) ERR_OUT(errp);
			else
			{
				col = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TdqColumnRefList_addCancel, (void *)&arg);
		}
	}
	return err;
}

static Dz1Error _Dz1TdqIndexList_append(Dz1TdqIndexList *dst, Dz1Str idx_suffix, bool_t is_unique, Dz1TdqRow *src_row, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	size_t len = 0;
	if (dst == NULL || idx_suffix == NULL || (len = Dz1STRLEN(idx_suffix)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if (len + 1 >= 256) ERR_SET_OUT(errp, E2BIG);
	else
	{
		Dz1TdqIndexEntry *idx_node = NULL;

		if ((idx_node = Dz1TdqIndexEntry_new(idx_suffix, is_unique, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1TdqRowRef *cols = NULL;
			pthread_cleanup_push(Dz1TdqIndexEntry_delAndSetNull, (void *)&idx_node);

			if ((idx_node->own_cols = cols = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = _ownColAppend(cols, src_row, ap)).code) ERR_OUT(errp);
			else if ((*errp = dst->add(dst, idx_node)).code) ERR_OUT(errp);
			else
			{
				idx_node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TdqIndexEntry_delAndSetNull, (void *)&idx_node);
		}
	}
	return err;
}

Dz1Error Dz1TdqIndexList_append(Dz1TdqIndexList *dst, Dz1Str idx_suffix, bool_t is_unique, Dz1TdqRow *src_row, ...)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	va_list ap;
	va_start(ap, src_row);

	if ((*errp = _Dz1TdqIndexList_append(dst, idx_suffix, is_unique, src_row, ap)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	va_end(ap);

	return err;
}
// Index Append
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Foreign Key Append
static Dz1Error _Dz1TdqFKList_append(Dz1TdqFKList *dst, Dz1Str fk_suffix, Dz1Str peer_tbl_name, Dz1Str peer_tbl_idx_suffix_opt, 
									 Dz1TdqForeignKeyMode ou, Dz1TdqForeignKeyMode od, Dz1TdqRow *own_rows, Dz1TdqTblInstanceList *tbls, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	size_t len = 0;
	Dz1TdqTblInstance *peer_tbl = NULL;
	if (dst == NULL || fk_suffix == NULL || (len = Dz1STRLEN(fk_suffix)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if (len + 1 >= 256) ERR_SET_OUT(errp, E2BIG);
	else if ((peer_tbl = Dz1TdqTblInstanceList_findByName(tbls, peer_tbl_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1TdqFKEntry *fk_node = NULL;

		if ((fk_node = Dz1TdqFKEntry_new(fk_suffix, peer_tbl, peer_tbl_idx_suffix_opt, ou, od, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1TdqRowRef *cols = NULL;
			pthread_cleanup_push(Dz1TdqFKEntry_delAndSetNull, (void *)&fk_node);

			if ((fk_node->own_cols = cols = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = _ownColAppend(cols, own_rows, ap)).code) ERR_OUT(errp);
			else if ((*errp = dst->add(dst, fk_node)).code) ERR_OUT(errp);
			else
			{
				fk_node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TdqFKEntry_delAndSetNull, (void *)&fk_node);
		}
	}
	return err;
}

Dz1Error Dz1TdqFKList_append(Dz1TdqFKList *dst, Dz1Str fk_suffix, Dz1Str peer_tbl_name, Dz1Str peer_tbl_idx_suffix_opt, 
							 Dz1TdqForeignKeyMode ou, Dz1TdqForeignKeyMode od, Dz1TdqRow *own_rows, Dz1TdqTblInstanceList *tbls, ...)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	va_list ap;
	va_start(ap, tbls);

	if ((*errp = _Dz1TdqFKList_append(dst, fk_suffix, peer_tbl_name, peer_tbl_idx_suffix_opt, ou, od, own_rows, tbls, ap)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	va_end(ap);

	return err;
}

static Dz1Error _Dz1TdqFKList_append_self(Dz1TdqFKList *dst, Dz1Str fk_suffix, Dz1TdqTblInstance *self, Dz1Str peer_tbl_idx_suffix_opt, 
									 Dz1TdqForeignKeyMode ou, Dz1TdqForeignKeyMode od, Dz1TdqRow *own_rows, va_list ap)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	size_t len = 0;
	Dz1TdqTblInstance *peer_tbl = self;
	if (dst == NULL || fk_suffix == NULL || (len = Dz1STRLEN(fk_suffix)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if (len + 1 >= 256) ERR_SET_OUT(errp, E2BIG);
	else
	{
		Dz1TdqFKEntry *fk_node = NULL;

		if ((fk_node = Dz1TdqFKEntry_new(fk_suffix, peer_tbl, peer_tbl_idx_suffix_opt, ou, od, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1TdqRowRef *cols = NULL;
			pthread_cleanup_push(Dz1TdqFKEntry_delAndSetNull, (void *)&fk_node);

			if ((fk_node->own_cols = cols = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = _ownColAppend(cols, own_rows, ap)).code) ERR_OUT(errp);
			else if ((*errp = dst->add(dst, fk_node)).code) ERR_OUT(errp);
			else
			{
				fk_node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TdqFKEntry_delAndSetNull, (void *)&fk_node);
		}
	}
	return err;
}

Dz1Error Dz1TdqFKList_append_self(Dz1TdqFKList *dst, Dz1Str fk_suffix, Dz1TdqTblInstance *self, Dz1Str peer_tbl_idx_suffix_opt,
								  Dz1TdqForeignKeyMode ou, Dz1TdqForeignKeyMode od, Dz1TdqRow *own_rows, ...)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	va_list ap;
	va_start(ap, own_rows);

	if ((*errp = _Dz1TdqFKList_append_self(dst, fk_suffix, self, peer_tbl_idx_suffix_opt, ou, od, own_rows, ap)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	va_end(ap);

	return err;
}
// Foreign Key Append
///////////////////////////////////////////////////////////////////////////////

Dz1TdqTblInstance *Dz1TdqTblInstanceList_findByName(Dz1TdqTblInstanceList *list, Dz1Str name)
{
	Dz1TdqTblInstance *ret = NULL;
	if (list != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqTblInstance key = { name };
		ret = list->find(list, &key);
	}
	return ret;
}

/*
typedef struct Dz1TdqTblShape
{
	Dz1Str           name;
	Dz1TdqRow       *row;
	Dz1TdqRowRef    *pk;
	Dz1TdqIndexList *indexes;
} Dz1TdqTblShape;
*/
Dz1Error Dz1TdqTblShape_isCompat(Dz1TdqTblShape *basis, Dz1TdqTblShape *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t temp = FALSE;
	*ret_compat = FALSE;

	if (basis == NULL || compat == NULL) { }
	else if ((*errp = Dz1TdqRow_isCompat(basis->row, compat->row, &temp)).code) ERR_OUT(errp);
	else if (temp == FALSE) Dz1Error_set(errp, 0);

	else if ((*errp = Dz1TdqRowRef_isCompat(basis->pk, compat->pk, &temp)).code) ERR_OUT(errp);
	else if (temp == FALSE) Dz1Error_set(errp, 0);

	else
	{
		*ret_compat = TRUE;
		Dz1Error_set(errp, 0);
	}
	return err;
}

/*
typedef struct Dz1TdqFKEntry
{
	Dz1Str                    suffix_name;
	Dz1TdqRowRef             *own_cols;
	struct Dz1TdqTblInstance *peer_tbl;
	Dz1Str                    peer_idx_suffix_opt;
	Dz1TdqForeignKeyMode      on_update;
	Dz1TdqForeignKeyMode      on_delete;
} Dz1TdqFKEntry;
*/
Dz1Error Dz1TdqFKEntry_isCompat(Dz1TdqFKEntry *basis, Dz1TdqFKEntry *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	
	bool_t temp = FALSE;

	*ret_compat = FALSE;

	if (basis == NULL || compat == NULL) ERR_SET_OUT(errp, EINVAL);

	else if ((*errp = Dz1TdqRowRef_isCompat(basis->own_cols, compat->own_cols, &temp)).code) ERR_OUT(errp);
	else if (temp == FALSE) { }

	else if (basis->on_update != compat->on_update) { }
	else if (basis->on_delete != compat->on_delete) { }

	else 
	{
		*ret_compat = TRUE;
		Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1Error Dz1TdqFKList_isCompat(Dz1TdqFKList *basis, Dz1TdqFKList *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqFKEntry **b_arr = NULL;
	u32_t b_cnt = 0;

	*ret_compat = FALSE;

	if (basis == NULL && compat == NULL) *ret_compat = TRUE;
	else if (basis == NULL || compat == NULL) { }
	else if ((b_arr = basis->get_array(basis, &b_cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqFKEntry **c_arr = NULL;
		u32_t c_cnt = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)b_arr);
		if ((c_arr = compat->get_array(compat, &c_cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)c_arr);
			if (b_cnt != c_cnt) { }
			else
			{
				bool_t a_compat, r_compat = TRUE;
				u32_t i, cnt = b_cnt;
				for (i = 0; errp->code == 0 && r_compat == TRUE && i < cnt; i++)
				{
					a_compat = FALSE;
					if ((*errp = Dz1TdqFKEntry_isCompat(b_arr[i], c_arr[i], &a_compat)).code) ERR_OUT(errp);
					else 
					{
						if (a_compat == FALSE) r_compat = FALSE;
						Dz1Error_set(errp, 0);
					}
				}

				if (errp->code == 0) *ret_compat = r_compat;
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)b_arr);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)b_arr);
	}
	return err;
}

/*
typedef struct Dz1TdqTblInstance
{
	Dz1Str          name;
	Dz1TdqTblShape *shape;
	Dz1TdqFKList   *fks;
} Dz1TdqTblInstance;
*/
Dz1Error Dz1TdqTblInstance_isCompat(Dz1TdqTblInstance *basis, Dz1TdqTblInstance *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t temp = FALSE;

	*ret_compat = FALSE;

	if (basis == NULL || compat == NULL) Dz1Error_set(errp, 0);
	else if (Dz1STRCMP(basis->name, compat->name) != 0) Dz1Error_set(errp, 0);

	else if ((*errp = Dz1TdqTblShape_isCompat(basis->shape, compat->shape, &temp)).code) ERR_OUT(errp);
	else if (temp == FALSE) Dz1Error_set(errp, 0);

	else if ((*errp = Dz1TdqFKList_isCompat(basis->fks, compat->fks, &temp)).code) ERR_OUT(errp);
	else if (temp == FALSE) Dz1Error_set(errp, 0);

	else 
	{
		*ret_compat = TRUE;
		Dz1Error_set(errp, 0);
	}

	return err;
}
