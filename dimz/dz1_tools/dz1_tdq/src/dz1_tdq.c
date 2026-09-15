#include <dz1_tdq.h>
#include "dz1_tdq_types.h"

static void _instance_add_cancel(void *ptr)
{
	Dz1ListAddCancelArg *arg = (Dz1ListAddCancelArg *)ptr;
	Dz1TdqTblInstanceList *list = (Dz1TdqTblInstanceList *)arg->list;
	Dz1TdqTblInstance **node = (Dz1TdqTblInstance **)arg->node;
	if (list != NULL && node != NULL && *node != NULL) list->extract(list, *node);
}

bool_t Dz1TdqDbScheme_appendInstance(Dz1TdqDbScheme *dst, Dz1TdqTblInstance *node, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || node == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->tables->add(dst->tables, node)).code) ERR_OUT(errp);
	else
	{
		Dz1ListAddCancelArg arg = { dst->tables, &node };
		pthread_cleanup_push(_instance_add_cancel, (void *)&arg);
		if ((*errp = dst->tblseq->add(dst->tblseq, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (_instance_add_cancel, (void *)&arg);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_regSimpleQuery(Dz1TdqDbScheme *dst, Dz1TdqTblInstance *tbl, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqQuery *node = Dz1TdqQuery_new(tbl->name, NULL, NULL, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQueryTblSpec *p = NULL;
		pthread_cleanup_push(Dz1TdqQuery_delAndSetNull, (void *)&node);
		if ((node->from = p = Dz1TdqQueryTblSpec_new(NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((p->basis = Dz1TdqQueryTblName_new(tbl, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->queries->add(dst->queries, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqQuery_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_createDB(Dz1TdqDbScheme *scm, Dz1Str db_name, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR query[1024] = Dz1Text("CREATE SCHEMA ");
	Dz1TdqTblInstance *tbl = NULL;
	if (scm == NULL || Dz1Str_isVoid(db_name)) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1STRLEN(db_name) >= (1023 - Dz1STRLEN(query))) ERR_SET_OUT(errp, E2BIG);
	else
	{
		Dz1STRCAT(query, db_name);
		if (commit == -1)
		{
			Dz1Thread_printf(Dz1T("Query = ")); Dz1Str_dump(query, 0);
			Dz1Error_set(errp, 0);
		}
		else if (Dz1TdqDbIface_sqlCmd(scm->dbh, query, NULL, commit, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_selectDB(Dz1TdqDbScheme *scm, Dz1Str db_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str dbn = NULL;
	if (scm == NULL || Dz1Str_isVoid(db_name) == TRUE) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1STRLEN(db_name) >= 1019) ERR_SET_OUT(errp, E2BIG);
	else if ((dbn = Dz1Str_dup(db_name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TCHAR query[1024] = Dz1Text("USE ");
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&dbn);

		Dz1STRCAT(query, dbn);
		if (Dz1TdqDbIface_sqlCmd(scm->dbh, query, NULL, FALSE, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			Dz1Str_delAndSetNull(&scm->arg->dbn_opt);
			scm->arg->dbn_opt = dbn;
			dbn = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&dbn);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_destroyDB(Dz1TdqDbScheme *scm, Dz1Str db_name, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR query[1024] = Dz1Text("DROP SCHEMA ");
	Dz1TdqTblInstance *tbl = NULL;
	if (scm == NULL || Dz1Str_isVoid(db_name)) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1STRLEN(db_name) >= (1023 - Dz1STRLEN(query))) ERR_SET_OUT(errp, E2BIG);
	else
	{
		Dz1STRCAT(query, db_name);
		if (commit == -1)
		{
			Dz1Thread_printf(Dz1T("Query = ")); Dz1Str_dump(query, 0);
			Dz1Error_set(errp, 0);
		}
		else if (Dz1TdqDbIface_sqlCmd(scm->dbh, query, NULL, commit, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbScheme_JobDone(Dz1TdqDbScheme *scm, Dz1TdqDbSchemeJobDone mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (scm == NULL) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		switch(mode)
		{
		case Dz1TdqDbSchemeJobDone_commit:
			if (Dz1TdqDbIface_commit(scm->dbh, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1TdqDbSchemeJobDone_rollback:
			if (Dz1TdqDbIface_rollback(scm->dbh, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}