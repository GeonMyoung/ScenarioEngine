#include "dz1_tdq_types.h"
#include "dz1_tdq_row_def_util.h"
#include "dz1_tdq_def_util.h"
#include "dz1_tdq_insert.h"

static bool_t _insert_row_query_build(Dz1ElasticBuf *dst, Dz1Str tbl_name, Dz1TdqColumnRefSeq *cols, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Str ret = NULL;

	u32_t cnt = 0;
	if (cols == NULL || (cnt = cols->count(cols)) == 0) ERR_SET_OUT(errp, ENOENT);
	else
	{
		u32_t i;

		ELB_PUSH_STR(dst, Dz1Text("INSERT INTO "), errp);					// INSERT INTO
		ELB_PUSH_STR(dst, tbl_name, errp);									// {table_name}

		ELB_PUSH_CHR(dst, Dz1Text('('), errp);								// (
		if (Dz1TdqColumnRefSeq_enumNames(dst, cols, errp) == FALSE) ERR_OUT_RET(errp, FALSE);	// col1, col2,...
		else Dz1Error_set(errp, 0);
		ELB_PUSH_CHR(dst, Dz1Text(')'), errp);								// )

		ELB_PUSH_CHR(dst, Dz1Text(' '), errp);
		ELB_PUSH_STR(dst, Dz1Text("VALUES"), errp);							// VALUES

		ELB_PUSH_CRLF(dst, errp);
		ELB_PUSH_CHR(dst, Dz1Text('('), errp);								// (
		for (i = 0; i < cnt; i++)
		{
			if (i > 0) ELB_PUSH_CHR(dst, Dz1Text(','), errp);				// [,] ?
			ELB_PUSH_CHR(dst, Dz1Text('?'), errp);
		}
		ELB_PUSH_CHR(dst, Dz1Text(')'), errp);								// )
	}
	ELB_PUSH_EOS(dst, errp);
	return TRUE;
}

static Dz1Error _build_insert_spec(void *ptr, Dz1TdqColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqColumnRefSeq *dst = (Dz1TdqColumnRefSeq *)ptr;
	if ((*errp = dst->add(dst, p)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1TdqColumnRefSeq *build_insert_spec(Dz1TdqNameList *supply_cols_opt, Dz1TdqRow *row, Dz1Error *errp)
{
	Dz1TdqColumnRefSeq *ret = Dz1TdqColumnRefSeq_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqColumnRefSeq_delAndSetNull, (void *)&ret);
		if (supply_cols_opt != NULL && supply_cols_opt->count(supply_cols_opt) > 0)
		{
			u32_t cnt = 0;
			Dz1TdqNameEntry **arr = supply_cols_opt->get_array(supply_cols_opt, &cnt, errp);
			if (arr == NULL) ERR_OUT(errp);
			else
			{
				u32_t i = 0;
				Dz1TdqColumn *col = NULL;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
				for (i = 0; errp->code == 0 && i < cnt; i++)
				{
					if ((col = Dz1TdqRow_findByName(row, arr[i]->name)) == NULL) ERR_SET_OUT(errp, ENOENT);
					else if ((*errp = ret->add(ret, col)).code) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
			}
		}
		else if ((*errp = row->seq->travel(row->seq, _build_insert_spec, (void *)ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqColumnRefSeq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqDbScheme_insert(Dz1TdqDbScheme *scm, Dz1Str tbl_name, Dz1TdqNameList *supply_cols_opt, Dz1TdqRowSupplyF row_supply, void *user_ptr, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1TdqDbIface *dbh = NULL;
	Dz1TdqTblInstance *tbl = NULL;
	Dz1TdqTblShape *shp = NULL;
	Dz1TdqColumnRefSeq *cols = NULL;
	if (scm == NULL || Dz1Str_isVoid(tbl_name) || row_supply == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((dbh = scm->dbh) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((tbl = Dz1TdqDbScheme_findInstance(scm, tbl_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((shp = tbl->shape) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((cols = build_insert_spec(supply_cols_opt, shp->row, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ElasticBuf *buf = NULL;
		pthread_cleanup_push(Dz1TdqColumnRefSeq_delAndSetNull, (void *)&cols);
		if (cols->count(cols) == 0) ERR_SET_OUT(errp, ENOENT);
		else if ((buf = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&buf);

			if (_insert_row_query_build(buf, tbl->name, cols, errp) == FALSE) ERR_OUT(errp);
			else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(buf, errp)) == NULL) ERR_OUT(errp);
			else if (commit == -1)
			{
				Dz1Thread_printf(Dz1T("Query = ")); Dz1Str_dump((Dz1Str)bin->data, 0);
				Dz1Error_set(errp, 0);
			}
			else if (Dz1TdqDbIface_insert(dbh, (Dz1Str)bin->data, cols, row_supply, user_ptr, commit, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1) // (Dz1ElasticBuf_delAndSetNull, (void *)&buf);
		}
		pthread_cleanup_pop(1); // (Dz1TdqColumnRefSeq_delAndSetNull, (void *)&cols);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

