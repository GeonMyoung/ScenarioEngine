#include "dz1_tdq_types.h"
#include "dz1_tdq_def_util.h"
#include "dz1_tdq_update.h"
#include "dz1_tdq_row_def_util.h"
#include "dz1_tdq_var_def_util.h"
typedef struct AddTgtColArg
{
	Dz1TdqRowRef			*dst;
	Dz1TdqSqlNamedVarList	*update_vars;
} AddTgtColArg;

static bool_t _is_same_type(Dz1TdqSqlTypeSpec *col_type, Dz1TdqSqlVar *value)
{
	Dz1TdqSqlVarPresent val_type = value->present == Dz1TdqSqlVarPresent_nul ? value->x.nul : value->present;
	return col_type->present == val_type ? TRUE : FALSE;
}

static Dz1Error _add_tgt_col_by_name(void *ptr, Dz1TdqColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	AddTgtColArg *arg = (AddTgtColArg *)ptr;
	Dz1TdqSqlNamedVar *var = NULL;
	if ((var = Dz1TdqSqlNamedVarList_findByName(arg->update_vars, p->name)) != NULL)
	{
		Dz1TdqSqlTypeSpec *type = p->sql_type;
		Dz1TdqSqlVar *val = var->val;
		if (_is_same_type(type, val) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else if (Dz1TdqRowRef_append(arg->dst, p, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1TdqRowRef *_tgt_cols_gen(Dz1TdqSqlNamedVarList *update_vars, Dz1TdqRow *row, Dz1Error *errp)
{
	Dz1TdqRowRef *ret = Dz1TdqRowRef_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqColumnRefSeq *seq = row->seq;
		AddTgtColArg arg = { ret, update_vars };
		pthread_cleanup_push(Dz1TdqRowRef_delAndSetNull, (void *)&ret);

		if ((*errp = seq->travel(seq, _add_tgt_col_by_name, (void *)&arg)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1TdqRowRef_delAndSetNull, (void *)&ret);
	}
	return ret;
}


typedef struct MergeValueArg
{
	Dz1TdqSqlVarRefArray	*dst;
	Dz1TdqSqlNamedVarList	*update_vars;
} MergeValueArg;

static Dz1Error _namedval_array_append(void *ptr, Dz1TdqColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	MergeValueArg *arg = (MergeValueArg *)ptr;
	Dz1TdqSqlNamedVar *var = Dz1TdqSqlNamedVarList_findByName(arg->update_vars, p->name);
	if (var == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = arg->dst->add(arg->dst, var->val)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _val_array_append(void *ptr, Dz1TdqSqlVar *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqSqlVarRefArray *dst = (Dz1TdqSqlVarRefArray *)ptr;
	if ((*errp = dst->add(dst, p)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1TdqSqlVarRefArray *_vals_args_merge(Dz1TdqRowRef *tgt_cols, Dz1TdqSqlNamedVarList *update_vars, Dz1TdqSqlVarArray *whr_args, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVarRefArray *ret = Dz1TdqSqlVarRefArray_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		MergeValueArg arg = { ret, update_vars };
		Dz1TdqColumnRefSeq *seq = tgt_cols->seq;
		pthread_cleanup_push(Dz1TdqSqlVarRefArray_delAndSetNull, (void *)&ret);

		if ((*errp = seq->travel(seq, _namedval_array_append, (void *)&arg)).code) ERR_OUT(errp);
		else if (whr_args != NULL && (*errp = whr_args->travel(whr_args, _val_array_append, (void *)ret)).code) ERR_OUT(errp);

		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlVarRefArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}

typedef struct Dz1TdqUpdateEnv
{
	Dz1TdqRowRef *tgt_cols;
	Dz1TdqSqlVarRefArray *vals_args;
	Dz1TdqSqlVar **val_arg_arr;
	u32_t val_arg_cnt;
} Dz1TdqUpdateEnv;

static void Dz1TdqUpdateEnv_del(Dz1TdqUpdateEnv *p)
{
	if (p != NULL)
	{
		Dz1TdqRowRef_delAndSetNull(&p->tgt_cols);
		Dz1TdqSqlVarRefArray_delAndSetNull(&p->vals_args);
		Dz1Memory_freeAndSetNull(&p->val_arg_arr);
		Dz1Free(p);
	}
}

static void Dz1TdqUpdateEnv_delAndSetNull(void **pptr)
{
	Dz1TdqUpdateEnv **p = (Dz1TdqUpdateEnv **)pptr;
	Dz1TdqUpdateEnv_del(*p); *p = NULL;
}

static Dz1TdqUpdateEnv *Dz1TdqUpdateEnv_new(Dz1TdqSqlNamedVarList *update_vars, Dz1TdqRow *row, Dz1TdqSqlVarArray *whr_args, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqUpdateEnv *ret = (Dz1TdqUpdateEnv *)Dz1Calloc(sizeof(Dz1TdqUpdateEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqUpdateEnv_delAndSetNull, (void *)&ret);
		if ((ret->tgt_cols = _tgt_cols_gen(update_vars, row, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqRowRef_isEmpty(ret->tgt_cols) == TRUE) 
			ERR_SET_OUT(errp, ENOENT);
		else if ((ret->vals_args = _vals_args_merge(ret->tgt_cols, update_vars, whr_args, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->val_arg_arr = ret->vals_args->get_array(ret->vals_args, &ret->val_arg_cnt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqUpdateEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

typedef struct ColQueryBuildArg
{
	Dz1ElasticBuf *dst;
	bool_t first;
} ColQueryBuildArg;

static Dz1Error _col_query_build(void *ptr, Dz1TdqColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	ColQueryBuildArg *arg = (ColQueryBuildArg *)ptr;
	Dz1ElasticBuf *dst = arg->dst;
	size_t eqq_sz = 4;
	if (arg->first) arg->first = FALSE;
	else ELB_PUSH_STRe(arg->dst, Dz1Text(", "), errp);
	ELB_PUSH_STRe(arg->dst, p->name, errp);
	ELB_PUSH_STRe(arg->dst, Dz1Text(" = ?"), errp);
	return err;
}

static bool_t _row_update_col_query_build(Dz1ElasticBuf *dst, Dz1TdqRowRef *col_sepc, Dz1Error *errp)
{
	ColQueryBuildArg arg = { dst, TRUE };
	Dz1TdqColumnRefSeq *seq = col_sepc->seq;
	if ((*errp = seq->travel(seq, _col_query_build, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _row_update_query_build(Dz1ElasticBuf *dst, Dz1Str tbl_name, Dz1TdqRowRef *col_sepc, Dz1Str cond, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ELB_PUSH_STR(dst, Dz1Text("UPDATE "), errp);
	ELB_PUSH_STR(dst, tbl_name, errp);
	ELB_PUSH_STR(dst, Dz1Text(" SET "), errp);
	if (_row_update_col_query_build(dst, col_sepc, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

	if (Dz1Str_isVoid(cond) == FALSE)
	{
		ELB_PUSH_STR(dst, Dz1Text(" WHERE "), errp);
		ELB_PUSH_STR(dst, cond, errp);
	}
	ELB_PUSH_EOS(dst, errp);
	return TRUE;
}

bool_t Dz1TdqDbScheme_update(Dz1TdqDbScheme *scm, Dz1Str tbl_name, Dz1TdqSqlNamedVarList *update_vars,
							 Dz1Str whr, Dz1TdqSqlVarArray *whr_args, bool_t commit, Dz1Error *err)
{	// UPDATE {tableName} SET {col=? [, {col}=?] [ WHERE {col}=? ]
	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t col_cnt = 0;
	Dz1TdqTblInstance *tbl = NULL;
	Dz1TdqTblShape *shape = NULL;
	Dz1TdqUpdateEnv *env = NULL;
	if (scm == NULL || Dz1Str_isVoid(tbl_name)) ERR_SET_OUT(errp, EINVAL);
	else if (update_vars == NULL || update_vars->count(update_vars) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((tbl = Dz1TdqDbScheme_findInstance(scm, tbl_name)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if ((shape = tbl->shape) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((env = Dz1TdqUpdateEnv_new(update_vars, shape->row, whr_args, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		Dz1ElasticBuf *elb = NULL;
		pthread_cleanup_push(Dz1TdqUpdateEnv_delAndSetNull, (void *)&env);
		if ((elb = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Str query = NULL;
			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

			if (_row_update_query_build(elb, tbl->name, env->tgt_cols, whr, errp) == FALSE) ERR_OUT(errp);
			else if ((query = Dz1ElasticBuf_flattenStr(elb, errp)) == NULL) ERR_OUT(errp);
			else
			{
				if (commit == -1)
				{
					Dz1Thread_printf(Dz1T("@@@ Query = ")); Dz1Str_dump(query, 0);
					Dz1Thread_printf(Dz1T("Args = ")); Dz1TdqSqlVarRefArray_dump(env->vals_args, 0);
					Dz1Error_set(errp, 0);
				}
				else if (Dz1TdqDbIface_sqlCmd_(scm->dbh, query, env->val_arg_arr, env->val_arg_cnt, commit, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		}
		pthread_cleanup_pop(1); // (Dz1TdqUpdateEnv_delAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
