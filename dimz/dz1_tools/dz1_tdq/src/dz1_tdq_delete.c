#include "dz1_tdq_util.h"
#include "dz1_tdq_def_util.h"
#include "dz1_tdq_delete.h"
#include "dz1_tdq_types.h"

static bool_t sql_delete_build(Dz1ElasticBuf *dst, Dz1TdqTblInstance *tbl, Dz1Str whr, Dz1Error *errp)
{	// DELETE from {table_name} WHERE ...

	ELB_PUSH_STR(dst, Dz1Text("DELETE FROM "), errp);	// 'DELETE FROM '
	ELB_PUSH_STR(dst, tbl->name, errp);					// {table_name}

	if (whr != NULL)
	{
		ELB_PUSH_STR(dst, Dz1Text(" WHERE "), errp);	// ' WHERE '
		ELB_PUSH_STR(dst, whr, errp);					// [{user condition sql}]
	}
	ELB_PUSH_EOS(dst, errp);
	return TRUE;
}

bool_t Dz1TdqDbScheme_delete(Dz1TdqDbScheme *scm, Dz1Str inst_name, Dz1Str whr, Dz1TdqSqlVarArray *args, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	size_t sz = 4096;
	Dz1ElasticBuf *elb = NULL;
	Dz1TdqTblInstance *tbl = NULL;
	if (scm == NULL || Dz1Str_isVoid(inst_name)) ERR_SET_OUT(errp, EINVAL);
	else if ((tbl = Dz1TdqDbScheme_findInstance(scm, inst_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Str query = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

		if (sql_delete_build(elb, tbl, whr, errp) == FALSE) ERR_OUT(errp);
		else if ((query = Dz1ElasticBuf_flattenStr(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (commit == -1)
			{
				Dz1Thread_printf(Dz1T("@@@ Query = ")); Dz1Str_dump(query, 0);
				Dz1Error_set(errp, 0);
			}
			else if (Dz1TdqDbIface_sqlCmd(scm->dbh, query, args, commit, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;;
}
