#include "dz1_tdq_def_util.h"
#include "dz1_tdq_var_def_util.h"
#include "dz1_tdq_qry_def_util.h"

Dz1TdqQuery *Dz1TdqQueryList_findByName(Dz1TdqQueryList *list, Dz1Str name)
{
	Dz1TdqQuery *ret = NULL;
	if (list != NULL && name != NULL && name[0] != 0)
	{
		Dz1TdqQuery key = { name };
		ret = list->find(list, &key);
	}
	return ret;
}

static bool_t Dz1TdqQryTblCol_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQryTblCol *src, bool_t use_full_name, Dz1Error *errp)
{	// [{tbl_name|alias}.]{col_name}
	if (use_full_name)
	{
		Dz1TdqQueryTblName *tbl = src->tbl;
		if (Dz1Str_isVoid(tbl->alias) == TRUE)
		{	// {tbl_name}.{col_name}
			Dz1TdqTblInstance *i = tbl->instance;
			ELB_PUSH_STR(dst, i->name, errp);
		}
		else
		{	// {tbl_alias}.{col_name}
			ELB_PUSH_STR(dst, tbl->alias, errp);
		}
		ELB_PUSH_CHR(dst, Dz1Text('.'), errp);
	}
	ELB_PUSH_STR(dst, src->col_name, errp);
	return TRUE;
}

void Dz1TdqQryColumn_dump(Dz1TdqQryColumn *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else
	{
		Dz1TdqQryCol *src = NULL;
		if ((src = p->src) == NULL) Dz1Thread_tprintf(tab, Dz1T("src = NULL\n"));
		else
		{
			Dz1TdqSqlTypeSpec *type = NULL;
			Dz1TdqQryExprCol *ecol = NULL;
			Dz1TdqQryTblCol *tcol = NULL;
			Dz1TdqQueryTblName *tn = NULL;
			switch(src->present)
			{
			case Dz1TdqQryColPresent_tcol:
				tcol = src->x.tcol;
				tn = tcol->tbl;
				if (tn != NULL)
				{
					Dz1Str tbl_name = Dz1Str_isVoid(tn->alias) ? tn->instance->name : tn->alias;
					Dz1Thread_printf(Dz1T("%s.%s"), tbl_name, tcol->col_name);
				}
				else Dz1Thread_printf(Dz1T("%s"), tcol->col_name);
				break;
			case Dz1TdqQryColPresent_ecol:
				ecol = src->x.ecol;
				type = ecol->type;
				Dz1Thread_printf(Dz1T("%s(%s)"), Dz1TdqSqlTypeSpecPresentStr(type->present),ecol->expression);
				break;
			default:
				Dz1Thread_printf(Dz1T("unknown"));
			}
			if (Dz1Str_isVoid(p->alias) == FALSE) Dz1Thread_printf(Dz1T(" as %s"), p->alias);
			Dz1Thread_printf(Dz1T("\n"));
		}
	}
}

static bool_t Dz1TdqQryColumn_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQryColumn *col, bool_t use_full_name, Dz1Error *errp)
{	// <colname> [ AS {alias} ]
	Dz1TdqQryCol *src = col->src;
	switch(src->present)
	{
	case Dz1TdqQryColPresent_tcol:
		if (Dz1TdqQryTblCol_sqlEnumerate(dst, src->x.tcol, use_full_name, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			if (Dz1Str_isVoid(col->alias) == FALSE)
			{
				ELB_PUSH_STR(dst, Dz1Text(" AS "), errp);
				ELB_PUSH_STR(dst, col->alias, errp);
			}
			else Dz1Error_set(errp, 0);
		}
		break;
	case Dz1TdqQryColPresent_ecol:
		ELB_PUSH_STR(dst, src->x.ecol->expression, errp);
		if (Dz1Str_isVoid(col->alias) == FALSE)
		{
			ELB_PUSH_STR(dst, Dz1Text(" AS "), errp);
			ELB_PUSH_STR(dst, col->alias, errp);
		}
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqQryColumn_sqlEnumerateName(Dz1ElasticBuf *dst, Dz1TdqQryColumn *col, bool_t use_full_name, Dz1Error *errp)
{
	Dz1TdqQryCol *src = col->src;
	switch(src->present)
	{
	case Dz1TdqQryColPresent_tcol:
		if (Dz1Str_isVoid(col->alias) == FALSE)
			ELB_PUSH_STR(dst, col->alias, errp);
		else if (Dz1TdqQryTblCol_sqlEnumerate(dst, src->x.tcol, use_full_name, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1TdqQryColPresent_ecol:
		if (Dz1Str_isVoid(col->alias) == FALSE)
			ELB_PUSH_STR(dst, col->alias, errp);
		else ERR_SET_OUT(errp, EINVAL);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqQryRow_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQryRow *src, bool_t use_full_name, Dz1Error *err)
{	// <sel_column> [, <sel_colimn>]+
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = 0;
	Dz1TdqQryColumn **arr = src->get_array(src, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if (i > 0) ELB_PUSH_STR_(dst, Dz1Text(", "), errp);
			if (Dz1TdqQryColumn_sqlEnumerate(dst, arr[i], use_full_name, errp) == FALSE) ERR_OUT_RET(errp, FALSE);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

u32_t Dz1TdqQueryTblSpec_get_tblCnt(Dz1TdqQueryTblSpec *src)
{
	u32_t ret = 0;
	if (src != NULL)
	{
		if (src->basis != NULL) ret++;
		ret += src->join_tbls->count(src->join_tbls);
	}
	return ret;
}

static void _Dz1TdqQueryTblName_dump(Dz1TdqQueryTblName *p)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL")); return; }
	else
	{
		Dz1Thread_printf(Dz1T("%s"), p->instance->name);
		if (Dz1Str_isVoid(p->alias) == FALSE) Dz1Thread_printf(Dz1T(" as %s"), p->alias);
	}

}

void Dz1TdqQueryTblName_dump(Dz1TdqQueryTblName *p, int tab)
{
	_Dz1TdqQueryTblName_dump(p);
	Dz1Thread_printf(Dz1T("\n"));
}

static bool_t Dz1TdqQueryTblJoin_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQueryTblJoin src, Dz1Error *errp)
{	// [INNER|LEFT|RIGHT|OUTER] JOIN
	switch(src)
	{
	case Dz1TdqQueryTblJoin_inner:	ELB_PUSH_STR(dst, Dz1Text("INNER JOIN "), errp); break;
	case Dz1TdqQueryTblJoin_left:	ELB_PUSH_STR(dst, Dz1Text("LEFT JOIN "), errp); break;
	case Dz1TdqQueryTblJoin_right:	ELB_PUSH_STR(dst, Dz1Text("RIGHT JOIN "), errp); break;
	case Dz1TdqQueryTblJoin_outer:	ELB_PUSH_STR(dst, Dz1Text("OUTER JOIN "), errp); break;
	default: ERR_SET_OUT(errp, EINVAL);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqQueryTblName_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQueryTblName *name, bool_t _put_crlf, Dz1Error *errp)
{	// {tbl_name} [ AS {alias} ]
	Dz1TdqTblInstance *i = name->instance;
	ELB_PUSH_STR(dst, i->name, errp);
	if (Dz1Str_isVoid(name->alias) == FALSE)
	{
		ELB_PUSH_STR(dst, Dz1Text(" AS "), errp);
		ELB_PUSH_STR(dst, name->alias, errp);
	}
	if (_put_crlf) ELB_PUSH_CRLF(dst, errp);
	return TRUE;
}

void Dz1TdqQueryTblEntry_dump(Dz1TdqQueryTblEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }

	_Dz1TdqQueryTblName_dump(p->tbl);
	Dz1Thread_tprintf(tab, Dz1T(" %s join on (%s)\n"), Dz1TdqQueryTblJoinStr(p->mode), p->match_on);
}

static bool_t Dz1TdqQueryTblEntry_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQueryTblEntry *src, Dz1Error *errp)
{	// <Table> [ MATCH ON {matching} ]
	if (Dz1TdqQueryTblJoin_sqlEnumerate(dst, src->mode, errp) == FALSE) ERR_OUT(errp); // "[LEFT|RIGHT|INNER|OUTER} JOIN "
	else if (Dz1TdqQueryTblName_sqlEnumerate(dst, src->tbl, FALSE, errp) == FALSE) ERR_OUT(errp); // "{tbl_name} [ AS {alias} ]"
	else if (Dz1Str_isVoid(src->match_on) == FALSE)
	{
		ELB_PUSH_STR(dst, Dz1Text(" ON "), errp);
		ELB_PUSH_STR(dst, src->match_on, errp);
	}
	ELB_PUSH_CRLF(dst, errp);
	return TRUE;
}

bool_t Dz1TdqQueryTblSpec_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQueryTblSpec *src, Dz1Error *err)
{	// <TableSpec> [<MoreJoinTable>]*
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = 0;
	Dz1TdqQueryTblEntry **arr = NULL;
	if (Dz1TdqQueryTblName_sqlEnumerate(dst, src->basis, TRUE, errp) == FALSE) ERR_OUT(errp);
	else if ((arr = src->join_tbls->get_array(src->join_tbls, &cnt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if (Dz1TdqQueryTblEntry_sqlEnumerate(dst, arr[i], errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqQryRefCols_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQryRefCols *src, bool_t use_full_name, Dz1Error *err)
{	
	DZ1_ERROR_SAFE_PTR(errp, err);	u32_t cnt = 0;
	Dz1TdqQryColumn **arr = src->get_array(src, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if (Dz1TdqQryColumn_sqlEnumerateName(dst, arr[i], use_full_name, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

typedef struct TblSpecFindTblArg
{
	Dz1TdqQueryTblName *ret;
	Dz1Str str;
} TblSpecFindTblArg;

static Dz1Error _Dz1TdqQueryTblSpec_findTblByName(void *ptr, Dz1TdqQueryTblEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TblSpecFindTblArg *arg = (TblSpecFindTblArg *)ptr;
	Dz1TdqQueryTblName *name = p->tbl;
	Dz1TdqTblInstance *tbl = NULL;
	if (name != NULL && (tbl = name->instance) != NULL && Dz1STRCMP(tbl->name, arg->str) == 0)
	{
		arg->ret = name;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

Dz1TdqQueryTblName *Dz1TdqQueryTblSpec_findTblByName(Dz1TdqQueryTblSpec *spec, Dz1Str name)
{
	Dz1TdqQueryTblName *ret = NULL;
	if (spec != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqTblInstance *tbl = NULL;
		Dz1TdqQueryTblName *basis = spec->basis;
		if (basis != NULL && (tbl = basis->instance) != NULL && Dz1STRCMP(tbl->name, name) == 0) ret = basis;
		else 
		{
			TblSpecFindTblArg arg = { NULL, name };
			spec->join_tbls->travel(spec->join_tbls, _Dz1TdqQueryTblSpec_findTblByName, (void *)&arg);
			ret = arg.ret;
		}
	}
	return ret;
}

static Dz1Error _Dz1TdqQueryTblSpec_findTblByAlias(void *ptr, Dz1TdqQueryTblEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TblSpecFindTblArg *arg = (TblSpecFindTblArg *)ptr;
	Dz1TdqQueryTblName *name = p->tbl;
	if (name != NULL && Dz1Str_isVoid(name->alias) == FALSE&& Dz1STRCMP(name->alias, arg->str) == 0)
	{
		arg->ret = name;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

Dz1TdqQueryTblName *Dz1TdqQueryTblSpec_findTblByAlias(Dz1TdqQueryTblSpec *spec, Dz1Str alias)
{
	Dz1TdqQueryTblName *ret = NULL;
	if (spec != NULL && Dz1Str_isVoid(alias) == FALSE)
	{
		Dz1TdqTblInstance *tbl = NULL;
		Dz1TdqQueryTblName *basis = spec->basis;
		if (basis != NULL && Dz1Str_isVoid(basis->alias) == FALSE && Dz1STRCMP(basis->alias, alias) == 0) ret = basis;
		else 
		{
			TblSpecFindTblArg arg = { NULL, alias };
			spec->join_tbls->travel(spec->join_tbls, _Dz1TdqQueryTblSpec_findTblByAlias, (void *)&arg);
			ret = arg.ret;
		}
	}
	return ret;
}

Dz1TdqQueryTblName *Dz1TdqQueryTblSpec_findTbl(Dz1TdqQueryTblSpec *spec, Dz1Str name_or_alias)
{
	Dz1TdqQueryTblName *ret = NULL;
	if (Dz1Str_isVoid(name_or_alias)) ret = spec->basis;
	else if ((ret = Dz1TdqQueryTblSpec_findTblByName(spec, name_or_alias)) == NULL)
		ret = Dz1TdqQueryTblSpec_findTblByAlias(spec, name_or_alias);
	return ret;
}

bool_t Dz1TdqQueryTblSpec_setBiasTbl(Dz1TdqQueryTblSpec *dst, Dz1Str name, Dz1Str alias, Dz1TdqDbScheme *scm, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqQueryTblName *basis = NULL;
	if (dst == NULL || Dz1Str_isVoid(name) || scm == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->basis != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((dst->basis = basis = Dz1TdqQueryTblName_new(NULL, alias, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqQueryTblName_delAndSetNull, (void *)&dst->basis);
		if ((basis->instance = Dz1TdqDbScheme_findInstance(scm, name)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqQueryTblName_delAndSetNull, (void *)&dst->basis);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqQueryTblSpec_appendJoinTbl(Dz1TdqQueryTblSpec *dst, Dz1Str tblname, Dz1Str alias, Dz1TdqQueryTblJoin mode, Dz1Str matchon, Dz1TdqDbScheme *scm, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqQueryTblEntry *node = NULL;
	if (dst == NULL || Dz1Str_isVoid(tblname) || Dz1Str_isVoid(matchon) || scm == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqQueryTblEntry_new(NULL, mode, matchon, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQueryTblName *name = NULL;
		pthread_cleanup_push(Dz1TdqQueryTblEntry_delAndSetNull, (void *)&node);
		if ((node->tbl = name = Dz1TdqQueryTblName_new(NULL, alias, errp)) == NULL) ERR_OUT(errp);
		else if ((name->instance = Dz1TdqDbScheme_findInstance(scm, tblname)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else if ((*errp = dst->join_tbls->add(dst->join_tbls, node)).code) ERR_OUT(errp);
		else 
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqQueryTblEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqQryRow_appendTableCol(Dz1TdqQryRow *dst, Dz1Str col_name, Dz1Str tbl_name_or_alias_opt, Dz1Str col_alias, Dz1TdqQueryTblSpec *from, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqQryColumn *col = NULL;
	if (dst == NULL || Dz1Str_isVoid(col_name) || from == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((col = Dz1TdqQryColumn_new(dst->count(dst), NULL, col_alias, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQryCol *src = NULL;
		Dz1TdqQryTblCol *tcol = NULL;
		Dz1TdqQueryTblName *name = NULL;
		pthread_cleanup_push(Dz1TdqQryColumn_delAndSetNull, (void *)&col);
		if ((col->src = src = Dz1TdqQryCol_new(Dz1TdqQryColPresent_tcol, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((src->x.tcol = tcol = Dz1TdqQryTblCol_new(NULL, col_name, errp)) == NULL) ERR_OUT(errp);
		else if ((tcol->tbl = Dz1TdqQueryTblSpec_findTbl(from, tbl_name_or_alias_opt)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else if ((*errp = dst->add(dst, col)).code) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqQryColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqQryRow_appendExprColNum(Dz1TdqQryRow *dst, Dz1TdqType num_type, Dz1Str expr, Dz1Str col_alias, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqQryColumn *col = NULL;
	u32_t cat = _category_of(num_type);
	if (dst == NULL || (cat != 0x00 && cat != 0x01) || Dz1Str_isVoid(expr)) ERR_SET_OUT(errp, EINVAL);
	else if ((col = Dz1TdqQryColumn_new(dst->count(dst), NULL, col_alias, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQryCol *src = NULL;
		Dz1TdqQryExprCol *ecol = NULL;
		pthread_cleanup_push(Dz1TdqQryColumn_delAndSetNull, (void *)&col);
		if ((col->src = src = Dz1TdqQryCol_new(Dz1TdqQryColPresent_ecol, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((src->x.ecol = ecol = Dz1TdqQryExprCol_new(NULL, expr, errp)) == NULL) ERR_OUT(errp);
		else if ((ecol->type = Dz1TdqSqlTypeSpec_new(num_type, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, col)).code) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqQryColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqQryRow_appendExprColReal(Dz1TdqQryRow *dst, Dz1TdqType real_type, Dz1Str expr, Dz1Str col_alias, Dz1Error *err)
{ return Dz1TdqQryRow_appendExprColNum(dst, real_type, expr, col_alias, err); }

bool_t Dz1TdqQryRow_appendExprColStr(Dz1TdqQryRow *dst, Dz1TdqType str_type, Dz1Str expr, Dz1Str col_alias, u32_t max_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqQryColumn *col = NULL;
	u32_t cat = _category_of(str_type);
	if (dst == NULL || cat != 0x02 || Dz1Str_isVoid(expr)) ERR_SET_OUT(errp, EINVAL);
	else if ((col = Dz1TdqQryColumn_new(dst->count(dst), NULL, col_alias, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQryCol *src = NULL;
		Dz1TdqQryExprCol *ecol = NULL;
		Dz1TdqSqlTypeSpec *type = NULL;
		pthread_cleanup_push(Dz1TdqQryColumn_delAndSetNull, (void *)&col);
		if ((col->src = src = Dz1TdqQryCol_new(Dz1TdqQryColPresent_ecol, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((src->x.ecol = ecol = Dz1TdqQryExprCol_new(NULL, expr, errp)) == NULL) ERR_OUT(errp);
		else if ((ecol->type = type = Dz1TdqSqlTypeSpec_new(str_type, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((type->x.string = Dz1TdqSqlStrSpec_new((s64_t)max_size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, col)).code) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqQryColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqQryRow_appendExprColTime(Dz1TdqQryRow *dst, Dz1TdqType time_type, Dz1Str expr, Dz1Str col_alias, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqQryColumn *col = NULL;
	u32_t cat = _category_of(time_type);
	if (dst == NULL || cat != 0x03 || Dz1Str_isVoid(expr)) ERR_SET_OUT(errp, EINVAL);
	else if ((col = Dz1TdqQryColumn_new(dst->count(dst), NULL, col_alias, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqQryCol *src = NULL;
		Dz1TdqQryExprCol *ecol = NULL;
		pthread_cleanup_push(Dz1TdqQryColumn_delAndSetNull, (void *)&col);
		if ((col->src = src = Dz1TdqQryCol_new(Dz1TdqQryColPresent_ecol, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((src->x.ecol = ecol = Dz1TdqQryExprCol_new(NULL, expr, errp)) == NULL) ERR_OUT(errp);
		else if ((ecol->type = Dz1TdqSqlTypeSpec_new(time_type, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, col)).code) ERR_OUT(errp);
		else
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqQryColumn_delAndSetNull, (void *)&col);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
