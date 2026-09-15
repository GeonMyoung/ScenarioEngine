#include "dz1_tdq_types.h"
#include "dz1_tdq_qry_def_util.h"
#include "dz1_tdq_def_util.h"
#include "dz1_tdq_select.h"
// Query -> SQL -> call Dz1TdqDbIface_select()

static bool_t Dz1TdqQuery_buildSql(Dz1ElasticBuf *dst, Dz1TdqQuery *q, Dz1Str whr, Dz1TdqPageSpec *paging, Dz1Error *errp)
{
	u32_t tbl_cnt = Dz1TdqQueryTblSpec_get_tblCnt(q->from);
	if (tbl_cnt == 0) ERR_SET_OUT(errp, ENOENT);
	else
	{
		bool_t use_full_name = (tbl_cnt == 1 ? FALSE : TRUE);
		
		ELB_PUSH_CRLF(dst, errp);
		ELB_PUSH_STR(dst, Dz1Text("SELECT "), errp);
		if (q->sel == NULL || q->sel->count(q->sel) == 0) ELB_PUSH_STR(dst, Dz1Text("*"), errp);
		else if (Dz1TdqQryRow_sqlEnumerate(dst, q->sel, use_full_name, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
		ELB_PUSH_CRLF(dst, errp);
		ELB_PUSH_STR(dst, Dz1Text("FROM "), errp);

		if (Dz1TdqQueryTblSpec_sqlEnumerate(dst, q->from, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

		if (Dz1Str_isVoid(whr) == FALSE)
		{
			ELB_PUSH_STR(dst, Dz1Text(" WHERE "), errp);
			ELB_PUSH_STR(dst, whr, errp);
			ELB_PUSH_CRLF(dst, errp);
		}

		if (q->groupby != NULL && q->groupby->count(q->groupby) > 0)
		{
			ELB_PUSH_STR(dst, Dz1Text(" GROUP BY "), errp);
			if (Dz1TdqQryRefCols_sqlEnumerate(dst, q->groupby, use_full_name, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
		}

		if (paging != NULL)
		{
			if (Dz1TdqDbIface_sqlPaging(dst, paging, errp) == FALSE) ERR_OUT_RET(errp, FALSE);
			else Dz1Error_set(errp, 0);
		}
		ELB_PUSH_EOS(dst, errp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqRow *_get_row_spec(Dz1TdqQueryTblSpec *from, Dz1Error *errp)
{
	Dz1TdqRow *ret = NULL;
	if (from == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1TdqTblShape *shp = NULL;
		Dz1TdqTblInstance *tbl = NULL;
		Dz1TdqQueryTblName *basis = NULL;
		if (from->join_tbls->count(from->join_tbls) > 0) ERR_SET_OUT(errp, EINVAL);
		else if ((basis = from->basis) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((tbl = basis->instance) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((shp = tbl->shape) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = shp->row) == NULL) ERR_SET_OUT(errp, EINVAL);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

bool_t Dz1TdqDbScheme_select(Dz1TdqDbScheme *scm, Dz1Str q_name, Dz1TdqRowTakeF row_take, void *user_ptr, 
							 Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqDbIface *dbh = NULL;
	Dz1TdqQuery *q = NULL;
	Dz1ElasticBuf *elb = NULL;
	if (scm == NULL || Dz1Str_isVoid(q_name) || row_take == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((dbh = scm->dbh) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((q = Dz1TdqDbScheme_findQuery(scm, q_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Str query = NULL;
		Dz1TdqRow *row_spec = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

		if (q->sel == NULL && (row_spec = _get_row_spec(q->from, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqQuery_buildSql(elb, q, whr, paging, errp) == FALSE) ERR_OUT(errp);
		else if ((query = Dz1ElasticBuf_flattenStr(elb, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqDbIface_select(dbh, query, q->sel, row_spec, row_take, user_ptr, args, errp) == FALSE) 
		{
			if (errp->code != ENOENT) 
			{
				ERR_OUT(errp);
				Dz1Thread_printf(Dz1T("@@@ Query = ")); Dz1Str_dump(query, 0);
				Dz1Thread_printf(Dz1T("@@@ Args = ")); Dz1TdqSqlVarArray_dump(args, 0);
			}
		}
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

