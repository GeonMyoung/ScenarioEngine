#include "dz1_tdq_tbl_def_util.h"
#include "dz1_tdq_qry_def_util.h"
#include "dz1_tdq_def_util.h"

Dz1TdqDbScheme *Dz1TdqDbScheme_new(Dz1TdqDbConnArg *arg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TdqDbScheme *__internal_ret = (Dz1TdqDbScheme *)Dz1Calloc(sizeof(Dz1TdqDbScheme), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TdqDbScheme_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->arg = Dz1TdqDbConnArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->dbh = Dz1TdqDbIface_new(__internal_ret->arg, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->shapes = Dz1TdqTblShapeList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else if ((__internal_ret->tables = Dz1TdqTblInstanceList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else if ((__internal_ret->tblseq = Dz1TdqTblInstanceSeq_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else if ((__internal_ret->queries = Dz1TdqQueryList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TdqDbScheme_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1TdqDbScheme_reconn(Dz1TdqDbScheme *scm, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (scm == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1TdqDbIface_reconn(scm->dbh, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

Dz1TdqTblInstance *Dz1TdqDbScheme_findInstance(Dz1TdqDbScheme *p, Dz1Str name)
{
	Dz1TdqTblInstance *ret = NULL;
	if (p != NULL)
		ret = Dz1TdqTblInstanceList_findByName(p->tables, name);
	return ret;
}

Dz1TdqQuery *Dz1TdqDbScheme_findQuery(Dz1TdqDbScheme *p, Dz1Str name)
{
	Dz1TdqQuery *ret = NULL;
	if (p != NULL)
		ret = Dz1TdqQueryList_findByName(p->queries, name);
	return ret;
}
