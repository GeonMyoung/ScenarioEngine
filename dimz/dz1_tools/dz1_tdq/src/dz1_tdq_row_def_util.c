#include "dz1_tdq_util.h"
#include "dz1_tdq_row_def_util.h"
#include "dz1_tdq_var_def_util.h"

static Dz1TdqNullOpt _not_null_no_default = { NULL };
Dz1TdqNullOpt *not_null_no_default = &_not_null_no_default;

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnList
Dz1TdqColumn *Dz1TdqColumnList_findByName(Dz1TdqColumnList *list, Dz1Str name)
{
	Dz1TdqColumn *ret = NULL;
	if (list != NULL && name != NULL && name[0] != 0)
	{
		Dz1TdqColumn key = { name };
		ret = list->find(list, &key);
	}
	return ret;
}

void Dz1TdqColumnList_addCancel(void *ptr)
{
	Dz1ListAddCancelArg *arg = (Dz1ListAddCancelArg *)ptr;
	Dz1TdqColumnList *list = arg->list;
	Dz1TdqColumn **node = (Dz1TdqColumn **)arg->node;
	if (list != NULL && node != NULL && *node != NULL) list->extract(list, *node);
}
// Dz1TdqColumnList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnRefList
void Dz1TdqColumnRefList_addCancel(void *ptr)
{
	Dz1ListAddCancelArg *arg = (Dz1ListAddCancelArg *)ptr;
	Dz1TdqColumnRefList *list = (Dz1TdqColumnRefList *)arg->list;
	Dz1TdqColumn **node = (Dz1TdqColumn **)arg->node;
	if (list != NULL && node != NULL && *node != NULL) list->extract(list, *node);
}
// Dz1TdqColumnRefList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnRefSeq : Enumerate Column Names
typedef struct RefSeqEnumNamesArg
{
	Dz1ElasticBuf *dst;
	bool_t first;
} RefSeqEnumNamesArg;

static Dz1Error RefSeq_enumNames(void *ptr, Dz1TdqColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	RefSeqEnumNamesArg *arg = (RefSeqEnumNamesArg *)ptr;
	if (arg->first) arg->first = FALSE;
	else ELB_PUSH_CHRe(arg->dst, Dz1Text(','), errp);
	ELB_PUSH_STRe(arg->dst, p->name, errp);
	return err;
}

bool_t Dz1TdqColumnRefSeq_enumNames(Dz1ElasticBuf *dst, Dz1TdqColumnRefSeq *cols, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	RefSeqEnumNamesArg arg = { dst, TRUE };
	if ((*errp = cols->travel(cols, RefSeq_enumNames, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1TdqColumnRefSeq : Enumerate Column Names
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqRow
void Dz1TdqRow_dump(Dz1TdqRow *p, int tab)
{
	if (p == NULL || p->seq == NULL) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else Dz1TdqColumnRefSeq_dump(p->seq, tab);
}

Dz1TdqColumn *Dz1TdqRow_findByName(Dz1TdqRow *row, Dz1Str name)
{
	Dz1TdqColumn *ret = NULL;
	if (row != NULL && name != NULL && name[0] != 0)
		ret = Dz1TdqColumnList_findByName(row->index, name);
	return ret;
}

bool_t Dz1TdqRow_appendCol(Dz1TdqRow *dst, Dz1TdqColumn *col, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || col == NULL) 
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else 
	{
		Dz1TdqColumnList *idx = dst->index;
		Dz1TdqColumnRefSeq *seq = dst->seq;
		if ((*errp = idx->add(idx, col)).code) ERR_OUT(errp);
		else
		{
			Dz1ListAddCancelArg arg = { idx, &col };
			pthread_cleanup_push(Dz1TdqColumnList_addCancel, (void *)&arg);
			if ((*errp = seq->add(seq, col)).code) ERR_OUT(errp);
			else
			{
				col = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (_idx_add_cancel, (void *)&arg);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _is_num_type(Dz1TdqType type)
{
	bool_t ret = FALSE;
	int cat = (type & 0xF0) >> 4;
	if (cat == 0) ret = TRUE;
	return ret;
}

bool_t Dz1TdqRow_addNum(Dz1TdqRow *dst, Dz1Str name, Dz1TdqType num_type, Dz1TdqSqlNumSpec *spec, Dz1TdqNullOpt *null_opt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqColumn *col = NULL;
	if (dst == NULL || name == NULL || name[0] == 0 || _is_num_type(num_type) == FALSE) 
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((col = Dz1TdqColumn_new(name, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnList *idx = dst->index;
		Dz1TdqColumnRefSeq *seq = dst->seq;
		Dz1TdqSqlTypeSpec *p = NULL;
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);

		if ((col->sql_type = p = Dz1TdqSqlTypeSpec_new((Dz1TdqSqlTypeSpecPresent)num_type, NULL, errp)) == NULL) ERR_OUT(errp);
		else if (spec != NULL && (p->x.__ptr__ = Dz1TdqSqlNumSpec_clone(spec, errp)) == NULL) ERR_OUT(errp);
		else if (null_opt != NULL && (col->null_opt = Dz1TdqNullOpt_clone(null_opt, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqRow_appendCol(dst, col, errp) == FALSE) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqRow_addReal(Dz1TdqRow *dst, Dz1Str name, Dz1TdqType real_type, s64_t percision, Dz1TdqNullOpt *null_opt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqColumn *col = NULL;
	if (dst == NULL || name == NULL || name[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((col = Dz1TdqColumn_new(name, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnList *idx = dst->index;
		Dz1TdqColumnRefSeq *seq = dst->seq;
		Dz1TdqSqlTypeSpec *p = NULL;
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);
		if ((col->sql_type = p = Dz1TdqSqlTypeSpec_new(real_type, NULL, errp)) == NULL) ERR_OUT(errp);
		else if (percision != DZ1INT64(-1) && (p->x.num_r64 = Dz1TdqSqlRealSpec_new(percision, errp)) == NULL) ERR_OUT(errp);
		else if (null_opt != NULL && (col->null_opt = Dz1TdqNullOpt_clone(null_opt, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqRow_appendCol(dst, col, errp) == FALSE) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _is_str_type(Dz1TdqType type)
{
	bool_t ret = FALSE;
	int cat = (type & 0xF0) >> 4;
	if (cat == 2) ret = TRUE;
	return ret;
}

bool_t Dz1TdqRow_addStr(Dz1TdqRow *dst, Dz1Str name, Dz1TdqType str_type, s64_t max_len, Dz1TdqNullOpt *null_opt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqColumn *col = NULL;
	if (dst == NULL || name == NULL || name[0] == 0 || _is_str_type(str_type) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else if ((col = Dz1TdqColumn_new(name, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnList *idx = dst->index;
		Dz1TdqColumnRefSeq *seq = dst->seq;
		Dz1TdqSqlTypeSpec *p = NULL;
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);
		if ((col->sql_type = p = Dz1TdqSqlTypeSpec_new((Dz1TdqSqlTypeSpecPresent)str_type, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((p->x.string = Dz1TdqSqlStrSpec_new(max_len, errp)) == NULL) ERR_OUT(errp);
		else if (null_opt != NULL && (col->null_opt = Dz1TdqNullOpt_clone(null_opt, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqRow_appendCol(dst, col, errp) == FALSE) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _is_time_type(Dz1TdqType type)
{
	bool_t ret = FALSE;
	int cat = (type & 0xF0) >> 4;
	if (cat == 3) ret = TRUE;
	return ret;
}

bool_t Dz1TdqRow_addTime(Dz1TdqRow *dst, Dz1Str name, Dz1TdqType time_type, Dz1TdqNullOpt *null_opt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqColumn *col = NULL;
	if (dst == NULL || name == NULL || name[0] == 0 || _is_time_type(time_type) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else if ((col = Dz1TdqColumn_new(name, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnList *idx = dst->index;
		Dz1TdqColumnRefSeq *seq = dst->seq;
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);
		if ((col->sql_type = Dz1TdqSqlTypeSpec_new((Dz1TdqSqlTypeSpecPresent)time_type, NULL, errp)) == NULL) ERR_OUT(errp);
		else if (null_opt != NULL && (col->null_opt = Dz1TdqNullOpt_clone(null_opt, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqRow_appendCol(dst, col, errp) == FALSE) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _is_blob_type(Dz1TdqType type)
{
	bool_t ret = FALSE;
	int cat = (type & 0xF0) >> 4;
	if (cat == 4) ret = TRUE;
	return ret;
}

bool_t Dz1TdqRow_addBlob(Dz1TdqRow *dst, Dz1Str name, Dz1TdqType blob_type, Dz1TdqSqlBlobSpec spec, Dz1TdqNullOpt *null_opt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqColumn *col = NULL;
	if (dst == NULL || name == NULL || name[0] == 0 || _is_blob_type(blob_type) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else if ((col = Dz1TdqColumn_new(name, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnList *idx = dst->index;
		Dz1TdqColumnRefSeq *seq = dst->seq;
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);
		if ((col->sql_type = Dz1TdqSqlTypeSpec_new((Dz1TdqSqlTypeSpecPresent)blob_type, &spec, errp)) == NULL) ERR_OUT(errp);
		else if (null_opt != NULL && (col->null_opt = Dz1TdqNullOpt_clone(null_opt, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqRow_appendCol(dst, col, errp) == FALSE) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqRowRef_append(Dz1TdqRowRef *dst, Dz1TdqColumn *col_ref, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqColumnRefList *idx = NULL;
	Dz1TdqColumnRefSeq *seq = NULL;
	if (dst == NULL || col_ref == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((idx = dst->index) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((seq = dst->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = idx->add(idx, col_ref)).code) ERR_OUT(errp);
	else
	{
		Dz1ListAddCancelArg arg = { idx, &col_ref };
		pthread_cleanup_push(Dz1TdqColumnRefList_addCancel, (void *)&arg);
		if ((*errp = seq->add(seq, col_ref)).code) ERR_OUT(errp);
		else
		{
			col_ref = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqColumnRefList_addCancel, (void *)&arg);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1TdqColumn *Dz1TdqRowRef_addCol(Dz1TdqRowRef *dst, Dz1Str name, Dz1TdqRow *row, Dz1Error *err)
{
	Dz1TdqColumn *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || name == NULL || row == NULL) 
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else
	{
		Dz1TdqColumn *col = Dz1TdqColumnList_findByName(row->index, name);
		if (col == NULL)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! column '%s' is not found\n", name);
			Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Index = "); Dz1TdqColumnList_dump(row->index, 0);
			ERR_SET_OUT(errp, ENOENT);
		}
		else if (Dz1TdqRowRef_append(dst, col, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			ret = col;
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}
// Dz1TdqRow
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqRowRef
void Dz1TdqRowRef_dump(Dz1TdqRowRef *p, int tab)
{
	if (p == NULL || p->seq == NULL) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else Dz1TdqColumnRefSeq_dump(p->seq, tab);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

bool_t Dz1TdqRowRef_isEmpty(Dz1TdqRowRef *p)
{
	bool_t ret = TRUE;
	if (p != NULL)
	{
		u32_t cnt = 0;
		if ((cnt = p->index->count(p->index)) > 0)
		{
			ret = FALSE;
			if (p->seq->count(p->seq) != cnt)
				Dz1Thread_printf(Dz1T("Dz1TdqRowRef_isEmpty() : Member Count mismatch\n"));
		}
	}
	return ret;
}
// Dz1TdqRowRef
///////////////////////////////////////////////////////////////////////////////

/*
typedef struct Dz1TdqColumn
{
	Dz1Str             name;
	Dz1TdqSqlTypeSpec *sql_type;
	Dz1TdqNullOpt     *null_opt;
} Dz1TdqColumn;
*/
Dz1Error Dz1TdqColumn_isCompat(Dz1TdqColumn *basis, Dz1TdqColumn *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t type_compat = FALSE;

	*ret_compat = FALSE;

	if (basis == NULL || compat == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1STRCMP(basis->name, compat->name) != 0) { }

	else if ((*errp = Dz1TdqSqlTypeSpec_isCompat(basis->sql_type, compat->sql_type, &type_compat)).code) ERR_OUT(errp);
	else if (type_compat == FALSE) { }

	else 
	{
		*ret_compat = TRUE;
		Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1Error Dz1TdqColumnRefSeq_isCompat(Dz1TdqColumnRefSeq *basis, Dz1TdqColumnRefSeq *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqColumn **b_arr = NULL;
	u32_t b_cnt = 0;

	*ret_compat = FALSE;

	if (basis == NULL || compat == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((b_arr = basis->get_array(basis, &b_cnt, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		Dz1TdqColumn **c_arr = NULL;
		u32_t c_cnt = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)b_arr);
		if ((c_arr = compat->get_array(compat, &c_cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Memory_cancel, (void *)c_arr);
			if (b_cnt != c_cnt) { }
			else
			{
				bool_t c_compat = FALSE, r_compat = TRUE;
				u32_t i, cnt = b_cnt;
				for (i = 0; errp->code == 0 && i < cnt; i++)
				{
					c_compat = FALSE;
					if ((*errp = Dz1TdqColumn_isCompat(b_arr[i], c_arr[i], &c_compat)).code) ERR_OUT(errp);
					else if (c_compat == FALSE) 
					{ 
						r_compat = FALSE; 
						Dz1Error_set(errp, 0);
						break; 
					}
				}

				if (errp->code == 0) *ret_compat = r_compat;
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)c_arr);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)b_arr);
	}
	return err;
}

/*
typedef struct Dz1TdqRow
{
	Dz1TdqColumnList   *index;
	Dz1TdqColumnRefSeq *seq;
} Dz1TdqRow;
*/
Dz1Error Dz1TdqRow_isCompat(Dz1TdqRow *basis, Dz1TdqRow *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t seq_compat = FALSE;

	*ret_compat = FALSE;

	if (basis == NULL || compat == NULL) { }
	else if ((*errp = Dz1TdqColumnRefSeq_isCompat(basis->seq, compat->seq, &seq_compat)).code) ERR_OUT(errp);
	else if (seq_compat == TRUE)
	{
		*ret_compat = TRUE;
		Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1Error Dz1TdqRowRef_isCompat(Dz1TdqRowRef *basis, Dz1TdqRowRef *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t seq_compat = FALSE;

	*ret_compat = FALSE;

	if (basis == NULL || compat == NULL) { }
	else if ((*errp = Dz1TdqColumnRefSeq_isCompat(basis->seq, compat->seq, &seq_compat)).code) ERR_OUT(errp);
	else if (seq_compat == TRUE)
	{
		*ret_compat = TRUE;
		Dz1Error_set(errp, 0);
	}
	return err;
}