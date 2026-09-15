#include <dz1_tdq_var_def_util.h>
#include "dz1_tdqc_util.h"
#include "dz1_tdqc_pub.h"

// 	Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqQueryTblSpec_setBiasTbl(from, Dz1Text(\"TableA\"), Dz1Text(\"A\"), scm, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 	Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqQueryTblSpec_appendJoinTbl(from, Dz1Text(\"TableB\"), Dz1Text(\"B\"), Dz1TdqQueryTblJoin_left, Dz1Text("B.my_unum64=A.my_unum64"), scm, errp) == FALSE) ERR_OUT(errp);" CRLF);
// 	Dz1Thread_ftprintf(fp, tab,				"else if (Dz1TdqQueryTblSpec_appendJoinTbl(from, Dz1Text(\"TableC\"), Dz1Text(\"C\"), Dz1TdqQueryTblJoin_left, Dz1Text("C.my_unum64=A.my_unum64"), scm, errp) == FALSE) ERR_OUT(errp);" CRLF);
static bool_t Dz1TdqQueryTblSpec_pubSrc_reg(FILE *fp, Dz1TdqQueryTblSpec *src, int tab, Dz1Error *errp)
{
	Dz1TdqQueryTblName *name = src->basis;
	Dz1TdqQueryTblSeq *joins = src->join_tbls;
	if (Dz1Str_isVoid(name->alias) == TRUE)
		Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQueryTblSpec_setBiasTbl(from, Dz1Text(\"%s\"), NULL, scm, errp) == FALSE) ERR_OUT(errp);" CRLF, name->instance->name);
	else Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQueryTblSpec_setBiasTbl(from, Dz1Text(\"%s\"), Dz1Text(\"%s\"), scm, errp) == FALSE) ERR_OUT(errp);" CRLF, name->instance->name, name->alias);

	if (joins->count(joins) > 0)
	{
		u32_t cnt, i;
		Dz1TdqQueryTblEntry **arr = joins->get_array(joins, &cnt, errp);
		if (arr == NULL) ERR_OUT(errp);
		else
		{
			Dz1Str str_mode;
			Dz1TdqQueryTblEntry *node = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
			for (i = 0; i < cnt; i++)
			{
				node = arr[i];
				str_mode = Dz1TdqQueryTblJoinStrA(node->mode);
				name = node->tbl;
				if (Dz1Str_isVoid(name->alias) == TRUE)
					Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQueryTblSpec_appendJoinTbl(from, Dz1Text(\"%s\"), NULL, Dz1TdqQueryTblJoin_%s, Dz1Text(\"%s\"), scm, errp) == FALSE) ERR_OUT(errp);" CRLF, name->instance->name, str_mode, node->match_on);
				else Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQueryTblSpec_appendJoinTbl(from, Dz1Text(\"%s\"), Dz1Text(\"%s\"), Dz1TdqQueryTblJoin_%s, Dz1Text(\"%s\"), scm, errp) == FALSE) ERR_OUT(errp);" CRLF, name->instance->name, name->alias, str_mode, node->match_on);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *arr);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqQryTblCol_pubSrc_reg(FILE *fp, Dz1TdqQryTblCol *src, Dz1Str alias, int tab, Dz1Error *errp)
{
	Dz1TdqQueryTblName *name = src->tbl;
	Dz1Str tblname = Dz1Str_isVoid(name->alias) ? name->instance->name : name->alias;
	if (Dz1Str_isVoid(alias))
		Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text(\"%s\"), Dz1Text(\"%s\"), NULL, from, errp) == FALSE) ERR_OUT(errp);" CRLF, src->col_name, tblname);
	else Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text(\"%s\"), Dz1Text(\"%s\"), Dz1Text(\"%s\"), from, errp) == FALSE) ERR_OUT(errp);" CRLF, src->col_name, tblname, alias);
	return TRUE;
}

static bool_t Dz1TdqQryExprCol_pubSrc_reg(FILE *fp, Dz1TdqQryExprCol *src, Dz1Str alias, int tab, Dz1Error *errp)
{
	Dz1TdqSqlTypeSpec *type = src->type;
	u32_t cat = _category_of(type->present);
	Dz1Str str_type = Dz1TdqSqlTypeSpecPresentStr(type->present);
	Dz1TdqSqlStrSpec *str_spec = NULL;
	switch(cat)
	{
	case 0:	// number
		if (Dz1Str_isVoid(alias))
			Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendExprColNum(sel, Dz1TdqType_%s, Dz1Text(\"%s\"), NULL, errp) == FALSE) ERR_OUT(errp);" CRLF, str_type, src->expression);
		else Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendExprColNum(sel, Dz1TdqType_%s, Dz1Text(\"%s\"), Dz1Text(\"%s\"), errp) == FALSE) ERR_OUT(errp);" CRLF, str_type, src->expression, alias);
		break;
	case 1:	// real
		if (Dz1Str_isVoid(alias))
			Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendExprColReal(sel, Dz1Text(\"%s\"), NULL, errp) == FALSE) ERR_OUT(errp);" CRLF, src->expression);
		else Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendExprColReal(sel, Dz1Text(\"%s\"), Dz1Text(\"%s\"), errp) == FALSE) ERR_OUT(errp);" CRLF, src->expression, alias);
		break;
	case 2:	// string
		if ((str_spec = type->x.string) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (Dz1Str_isVoid(alias))
			Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendExprColStr(sel, Dz1TdqType_%s, Dz1Text(\"%s\"), NULL, %u, errp) == FALSE) ERR_OUT(errp);" CRLF, str_type, src->expression, str_spec->size);
		else Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendExprColStr(sel, Dz1TdqType_%s, Dz1Text(\"%s\"), Dz1Text(\"%s\"), %u, errp) == FALSE) ERR_OUT(errp);" CRLF, str_type, src->expression, alias, str_spec->size);
		break;
	case 3:	// date
		if (Dz1Str_isVoid(alias))
			Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendExprColTime(sel, Dz1TdqType_%s, Dz1Text(\"%s\"), NULL, errp) == FALSE) ERR_OUT(errp);" CRLF, str_type, src->expression);
		else Dz1Thread_ftprintf(fp, tab, "else if (Dz1TdqQryRow_appendExprColTime(sel, Dz1TdqType_%s, Dz1Text(\"%s\"), Dz1Text(\"%s\"), errp) == FALSE) ERR_OUT(errp);" CRLF, str_type, src->expression, alias);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqQryCol_pubSrc_reg(FILE *fp, Dz1TdqQryCol *src, Dz1Str alias, int tab, Dz1Error *errp)
{
	switch(src->present)
	{
	case Dz1TdqQryColPresent_tcol:
		if (Dz1TdqQryTblCol_pubSrc_reg(fp, src->x.tcol, alias, tab, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1TdqQryColPresent_ecol:
		if (Dz1TdqQryExprCol_pubSrc_reg(fp, src->x.ecol, alias, tab, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqQryRow_pubSrc_reg(FILE *fp, Dz1TdqQryRow *src, int tab, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqQryColumn **arr = src->get_array(src, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		Dz1TdqQryColumn *node = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; i < cnt; i++)
		{
			node = arr[i];
			if (Dz1TdqQryCol_pubSrc_reg(fp, node->src, node->alias, tab, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcQuery_pubSrc_reg(FILE *fp, Dz1TdqcQuery *src, Dz1Error *errp)
{
	int tab = 0;

	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"static bool_t %s_queryReg(Dz1TdqDbScheme *scm, Dz1Error *err)" CRLF, src->name);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,			"Dz1TdqQuery *node = Dz1TdqQuery_new(Dz1Text(\"%s\"), NULL, NULL, errp);" CRLF, src->name);
	Dz1Thread_ftprintf(fp, tab,			"if (node == NULL) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"Dz1TdqQryRow *sel = NULL;" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"Dz1TdqQueryTblSpec *from = NULL;" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(Dz1TdqQuery_delAndSetNull, (void *)&node);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"if (0) { }" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else if ((node->from = from = Dz1TdqQueryTblSpec_new(NULL, errp)) == NULL) ERR_OUT(errp);" CRLF);
	if (Dz1TdqQueryTblSpec_pubSrc_reg(fp, src->from, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else if ((node->sel = sel = Dz1TdqQryRow_new(errp)) == NULL) ERR_OUT(errp);" CRLF);
	if (Dz1TdqQryRow_pubSrc_reg(fp, src->sel, tab, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

	Dz1Thread_ftprintf(fp, tab,				"else if ((*errp = scm->queries->add(scm->queries, node)).code) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,					"node = NULL;" CRLF);
	Dz1Thread_ftprintf(fp, tab,					"Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(1); // (Dz1TdqQuery_delAndSetNull, (void *)&node);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return errp->code == 0 ? TRUE : FALSE;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqSqlTypeSpec *Dz1TdqQryTblCol_getType(Dz1TdqQryTblCol *src, Dz1Error *errp)
{
	Dz1TdqSqlTypeSpec *ret = NULL;
	Dz1TdqQueryTblName *name = src->tbl;
	Dz1TdqcTblInstance *tbl = (Dz1TdqcTblInstance *)name->instance;
	Dz1TdqcShape *shape = tbl->shape;
	Dz1TdqTblShape *shp = shape->target;
	Dz1TdqColumn *col = Dz1TdqRow_findByName(shp->row, src->col_name);
	if (col == NULL) ERR_SET_OUT(errp, ENOENT);
	else ret = col->sql_type;
	return ret;
}

static Dz1TdqSqlTypeSpec *Dz1TdqQryCol_getType(Dz1TdqQryCol *src, Dz1Error *errp)
{
	switch(src->present)
	{
	case Dz1TdqQryColPresent_tcol:	return Dz1TdqQryTblCol_getType(src->x.tcol, errp);
	case Dz1TdqQryColPresent_ecol: return src->x.ecol->type;
	default: ERR_SET_OUT(errp, EFAULT); return NULL;
	}
}

static Dz1Error __build_row_seq(void *ptr, Dz1TdqQryColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqRow *row = (Dz1TdqRow *)ptr;
	Dz1TdqColumn *col = Dz1TdqColumn_new(p->alias, NULL, NULL, errp);
	if (col == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqSqlTypeSpec *type = NULL;
		pthread_cleanup_push(Dz1TdqColumn_delAndSetNull, (void *)&col);
		if ((type = Dz1TdqQryCol_getType(p->src, errp)) == NULL) ERR_OUT(errp);
		else if ((col->sql_type = Dz1TdqSqlTypeSpec_clone(type, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TdqRow_appendCol(row, col, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			col = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqColumn_delAndSetNull, (void *)&col);
	}
	return err;
}

static Dz1TdqRow *_build_row(Dz1TdqQryRow *src, Dz1Error *errp)
{
	Dz1TdqRow *ret = Dz1TdqRow_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqRow_delAndSetNull, (void *)&ret);
		if ((*errp = src->travel(src, __build_row_seq, (void *)ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqRow_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static bool_t Dz1TdqcQuery_pubSrc_take(FILE *fp, Dz1TdqcQuery *q, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqRow *row = _build_row(q->sel, errp);
	if (row == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqRow_delAndSetNull, (void *)&row);
		if (_pubSrc_take(fp, row->seq, q->src_obj, q->dst_obj, q->memb_opt, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1TdqRow_delAndSetNull, (void *)&row);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcQuery_pubHdr_take(FILE *fp, Dz1TdqcQuery *q, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (_pubHdr_take(fp, q->src_obj, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcQuery_pubSrc_sel(FILE *fp, Dz1TdqcQuery *q, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int tab = 0;
	ObjectInfo *list_obj = q->dst_obj, *entry_obj = q->src_obj;
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"%s *%s_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)" CRLF, list_obj->name, q->name);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"%s *ret = %s_gen(errp);" CRLF, list_obj->name, list_obj->name);
	Dz1Thread_ftprintf(fp, tab,			"if (ret == NULL) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else" CRLF);
	Dz1Thread_ftprintf(fp, tab++,		"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_push(%s_delAndSetNull, (void *)&ret);" CRLF, list_obj->name);
	Dz1Thread_ftprintf(fp, tab,				"if (Dz1TdqDbScheme_select(scm, Dz1Text(\"%s\"), %s_readRow, (void *)ret, whr, args, paging, errp) == FALSE)" CRLF, q->name, entry_obj->name);
	Dz1Thread_ftprintf(fp, tab++,			"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,					"if (errp->code != ENOENT) ERR_OUT(errp);" CRLF);
	Dz1Thread_ftprintf(fp, --tab,			"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"else Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, tab,				"pthread_cleanup_pop(errp->code); // (%s_delAndSetNull, (void *)&ret);" CRLF, list_obj->name);
	Dz1Thread_ftprintf(fp, --tab,		"}" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return ret;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqcQuery_pubHdr_sel(FILE *fp, Dz1TdqcQuery *q, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ObjectInfo *list_obj = q->dst_obj;
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK %s *%s_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);" CRLF, list_obj->name, q->name);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqcQuery_pubSrc(FILE *fp, Dz1TdqcQuery *q, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) { }
	else if (Dz1TdqcQuery_pubSrc_reg(fp, q, errp) == FALSE) ERR_OUT(errp);
//	else if (Dz1TdqcQuery_pubSrc_take(fp, q, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcQuery_pubSrc_sel(fp, q, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqcQuery_pubHdr(FILE *fp, Dz1TdqcQuery *q, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
//	Dz1Thread_fprintf(fp, CRLF);
	if (0) { }
	else if (Dz1TdqcQuery_pubHdr_take(fp, q, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1TdqcQuery_pubHdr_sel(fp, q, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
