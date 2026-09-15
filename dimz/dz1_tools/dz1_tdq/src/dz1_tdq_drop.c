#include "dz1_tdq_util.h"
#include "dz1_tdq_def_util.h"
#include "dz1_tdq_types.h"
#include "dz1_tdq_drop.h"

static bool_t _drop_table_sql_build(Dz1ElasticBuf *elb, Dz1TdqTblInstance *tbl, Dz1Error *errp)
{
	ELB_PUSH_STR(elb, Dz1Text("DROP TABLE "), errp);
	ELB_PUSH_STR(elb, tbl->name, errp);
	ELB_PUSH_EOS(elb, errp);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1TdqDbScheme_drop(Dz1TdqDbIface *dbh, Dz1TdqTblInstance *tbl, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *elb = NULL;
	if (dbh == NULL || tbl == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((elb = Dz1ElasticBuf_new(64, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if (_drop_table_sql_build(elb, tbl, errp) == FALSE) ERR_OUT(errp);
		else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(elb, errp)) == NULL) ERR_OUT(errp);
		else if (commit == -1)
		{
			Dz1Thread_printf(Dz1T("Query = ")); Dz1Str_dump((Dz1Str)bin->data, 0);
			Dz1Error_set(errp, 0);
		}
		else if (Dz1TdqDbIface_sqlCmd(dbh, (Dz1Str)bin->data, NULL, commit, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_drop(Dz1TdqDbScheme *scm, Dz1Str tbl_name, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqDbIface *dbh = NULL;
	Dz1ElasticBuf *elb = NULL;
	Dz1TdqTblInstance *tbl = NULL;
	if (scm == NULL || Dz1Str_isVoid(tbl_name)) ERR_SET_OUT(errp, EINVAL);
	else if ((dbh = scm->dbh) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((tbl = Dz1TdqDbScheme_findInstance(scm, tbl_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (_Dz1TdqDbScheme_drop(scm->dbh, tbl, commit, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_breakDB(Dz1TdqDbScheme *scm, bool_t commit, Dz1Error *err)
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
		for (i = cnt; i > 0; i--)
		{
			node = arr[i - 1];
			_Dz1TdqDbScheme_drop(scm->dbh, node, loop_commit, NULL);
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
