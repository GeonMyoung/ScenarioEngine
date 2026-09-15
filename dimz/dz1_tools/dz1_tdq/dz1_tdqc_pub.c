#include "dz1_tdqc_pub.h"
//#include "dz1_tdqc_pub_util.h"

//////////////////////////////////////////////
// Front
static Dz1Error _pubHdrFront_module(void *ptr, Dz1MdefcModule *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = (FILE *)ptr;
	char mod_name[1024] = { 0, };
	_get_mod_name(mod_name, p->name);
	Dz1Thread_fprintf(fp, "#include \"%s.h\"" CRLF, mod_name);
	return err;
}

static bool_t Dz1Tdqc_pubHdrFront(FILE *fp, Dz1TdqcTarget *tgt, Dz1Str output_name, Dz1Error *errp)
{
	char dcl_name[1024] = { 0, };
	_mk_dcl_name(dcl_name, output_name);
	Dz1Thread_fprintf(fp, "#ifndef %s_H" CRLF, dcl_name);
	Dz1Thread_fprintf(fp, "#define %s_H" CRLF CRLF, dcl_name);

	Dz1Thread_fprintf(fp, "#include <dz1_tdq.h>" CRLF CRLF);
	// module include
	tgt->src->travel(tgt->src, _pubHdrFront_module, (void *)fp);
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error Tdqc_pubSrcFront(void *ptr, Dz1TdqNameEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = (FILE *)ptr;
	Dz1Thread_fprintf(fp, "#include \"%s.h\"" CRLF, p->name);
	return err;
}

static bool_t Dz1Tdqc_pubSrcFront(FILE *fp, Dz1TdqcTarget *tgt, Dz1Str output_name, Dz1Error *errp)
{
	Dz1Thread_fprintf(fp, "#include <dz1_tdq_util.h>" CRLF);
	Dz1Thread_fprintf(fp, "#include <dz1_tdq_qry_def_util.h>" CRLF CRLF);
	Dz1Thread_fprintf(fp, "#include <dz1_tdq_var_def_util.h>" CRLF CRLF);
	Dz1Thread_fprintf(fp, "#include \"%s.h\"" CRLF, output_name);

	tgt->incs->travel(tgt->incs, Tdqc_pubSrcFront, (void *)fp);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1Tdqc_pubFront(Dz1TdqcPubEnv *env, Dz1TdqcTarget *tgt, Dz1Str output_name, Dz1Error *errp)
{
	if (0) { }
	else if (env->hdr_fp != NULL && Dz1Tdqc_pubHdrFront(env->hdr_fp, tgt, output_name, errp) == FALSE) ERR_OUT(errp);
	else if (env->src_fp != NULL && Dz1Tdqc_pubSrcFront(env->src_fp, tgt, output_name, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Front
//////////////////////////////////////////////

//////////////////////////////////////////////
// Shape
static bool_t Dz1TdqcShape_pub(Dz1TdqcShape *p, Dz1TdqcPubEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) { }
	else if (env->src_fp != NULL && Dz1TdqcShape_pubSrc(env->src_fp, p, errp) == FALSE) ERR_OUT(errp);
	else if (env->hdr_fp != NULL && Dz1TdqcShape_pubHdr(env->hdr_fp, p, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

// static Dz1Error ShapeList_pub(void *ptr, Dz1TdqcShape *p)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	Dz1TdqcPubEnv *env = (Dz1TdqcPubEnv *)ptr;
// 	if (Dz1TdqcShape_pub(p, env, errp) == FALSE) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 	return err;
// }
// 
// static bool_t Dz1TdqcShapeList_pub(Dz1TdqcShapeList *list, Dz1TdqcPubEnv *env, Dz1Error *errp)
// {
// 	if ((*errp = list->travel(list, ShapeList_pub, (void *)env)).code) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 	return errp->code == 0 ? TRUE : FALSE;
// }
// Shape
//////////////////////////////////////////////

//////////////////////////////////////////////
// Table
static bool_t Dz1TdqcTblInstance_pub(Dz1TdqcTblInstance *p, Dz1TdqcPubEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) { }
	else if (env->src_fp != NULL && Dz1TdqcTblInstance_pubSrc(env->src_fp, p, env->shapes, errp) == FALSE) ERR_OUT(errp);
	else if (env->hdr_fp != NULL && Dz1TdqcTblInstance_pubHdr(env->hdr_fp, p, env->shapes, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

// static Dz1Error InstanceSeq_pub(void *ptr, Dz1TdqcTblInstance *p)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	Dz1TdqcPubEnv *env = (Dz1TdqcPubEnv *)ptr;
// 	if (Dz1TdqcTblInstance_pub(p, env, errp) == FALSE) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 	return err;
// }
// 
// static bool_t Dz1TdqcTblInstanceSeq_pub(Dz1TdqcTblInstanceSeq *list, Dz1TdqcPubEnv *env, Dz1Error *errp)
// {
// 	if ((*errp = list->travel(list, InstanceSeq_pub, (void *)env)).code) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 	return errp->code == 0 ? TRUE : FALSE;
// }
// Table
//////////////////////////////////////////////

//////////////////////////////////////////////
// Query
static bool_t Dz1TdqcQuery_pub(Dz1TdqcQuery *p, Dz1TdqcPubEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) { }
	else if (env->src_fp != NULL && Dz1TdqcQuery_pubSrc(env->src_fp, p, errp) == FALSE) ERR_OUT(errp);
	else if (env->hdr_fp != NULL && Dz1TdqcQuery_pubHdr(env->hdr_fp, p, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

// static Dz1Error QueryList_pub(void *ptr, Dz1TdqcQuery *p)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	Dz1TdqcPubEnv *env = (Dz1TdqcPubEnv *)ptr;
// 	if (Dz1TdqcQuery_pub(p, env, errp) == FALSE) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 	return err;
// }
// 
// static bool_t Dz1TdqQueryList_pub(Dz1TdqcQueryList *list, Dz1TdqcPubEnv *env, Dz1Error *errp)
// {
// 	if (env->hdr_fp != NULL) Dz1Thread_fprintf(env->hdr_fp, CRLF);
// 	if (env->src_fp != NULL) Dz1Thread_fprintf(env->hdr_fp, CRLF);
// 
// 	if ((*errp = list->travel(list, QueryList_pub, (void *)env)).code) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 	return errp->code == 0 ? TRUE : FALSE;
// }
// Query
//////////////////////////////////////////////

//////////////////////////////////////////////
// Bottom
static Dz1Error _Dz1Tdqc_pubSrcBottom_shp(void *ptr, Dz1TdqcShape *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = (FILE *)ptr;
	if (p->is_qurty_shape == FALSE) 
		Dz1Thread_ftprintf(fp, 1, "else if (%s_regShape(scm, errp) == FALSE) ERR_OUT(errp);" CRLF, p->name);
	return err;
}

static Dz1Error _Dz1Tdqc_pubSrcBottom_tbl(void *ptr, Dz1TdqcTblInstance *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = (FILE *)ptr;
 	Dz1Thread_ftprintf(fp, 1, "else if (%s_regTable(scm, errp) == FALSE) ERR_OUT(errp);" CRLF, p->prefix);
	return err;
}

static Dz1Error _Dz1Tdqc_pubSrcBottom_qry(void *ptr, Dz1TdqcQuery *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = (FILE *)ptr;
	Dz1Thread_ftprintf(fp, 1, "else if (%s_queryReg(scm, errp) == FALSE) ERR_OUT(errp);" CRLF, p->name);
	return err;
}

static bool_t Dz1Tdqc_pubSrcBottom(FILE *fp, Dz1TdqcTarget *tgt, Dz1Str output_name, Dz1Error *errp)
{
	int tab = 0;
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,		"bool_t %s_init(Dz1TdqDbScheme *scm, Dz1Error *err)" CRLF, output_name);
	Dz1Thread_ftprintf(fp, tab++,	"{" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"DZ1_ERROR_SAFE_PTR(errp, err);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"if (0) { }" CRLF);
	tgt->shapes->travel(tgt->shapes, _Dz1Tdqc_pubSrcBottom_shp, (void *)fp);
	Dz1Thread_fprintf(fp, CRLF);
	tgt->tblseq->travel(tgt->tblseq, _Dz1Tdqc_pubSrcBottom_tbl, (void *)fp);
	Dz1Thread_fprintf(fp, CRLF);
	tgt->queries->travel(tgt->queries, _Dz1Tdqc_pubSrcBottom_qry, (void *)fp);
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_ftprintf(fp, tab,			"else Dz1Error_set(errp, 0);" CRLF);
	Dz1Thread_ftprintf(fp, tab,			"return errp->code == 0 ? TRUE : FALSE;" CRLF);
	Dz1Thread_ftprintf(fp, --tab,	"}" CRLF);

	return errp->code == 0 ? TRUE : FALSE;
}

// Header Bottom
static bool_t Dz1Tdqc_pubHdrBottom(FILE *fp, Dz1TdqcTarget *tgt, Dz1Str output_name, Dz1Error *errp)
{
	char dcl_name[1024] = { 0, };
	_mk_dcl_name(dcl_name, output_name);
	Dz1Thread_fprintf(fp, CRLF);
	Dz1Thread_fprintf(fp, "DZ1_CPPLINK bool_t %s_init(Dz1TdqDbScheme *scm, Dz1Error *err);" CRLF, output_name);
	Dz1Thread_fprintf(fp, CRLF "#endif // %s_H" CRLF, dcl_name);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1Tdqc_pubBottom(Dz1TdqcPubEnv *env, Dz1TdqcTarget *tgt, Dz1Str output_name, Dz1Error *errp)
{
	if (0) { }
	else if (env->hdr_fp != NULL && Dz1Tdqc_pubHdrBottom(env->hdr_fp, tgt, output_name, errp) == FALSE) ERR_OUT(errp);
	else if (env->src_fp != NULL && Dz1Tdqc_pubSrcBottom(env->src_fp, tgt, output_name, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Bottom
//////////////////////////////////////////////

static Dz1Error _Dz1TdqcOrderList_pub(void *ptr, Dz1TdqcOrderEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqcPubEnv *env = (Dz1TdqcPubEnv *)ptr;
	switch(p->present)
	{
	case Dz1TdqcOrderEntryPresent_shp: if (Dz1TdqcShape_pub(p->x.shp, env, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	case Dz1TdqcOrderEntryPresent_tbl: if (Dz1TdqcTblInstance_pub(p->x.tbl, env, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	case Dz1TdqcOrderEntryPresent_qry: if (Dz1TdqcQuery_pub(p->x.qry, env, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	default: ERR_SET_OUT(errp, EINVAL); break;
	}
	return err;
}

static bool_t Dz1TdqcOrderList_pub(Dz1TdqcOrderList *list, Dz1TdqcPubEnv *env, Dz1Error *errp)
{
	if ((*errp = list->travel(list, _Dz1TdqcOrderList_pub, (void *)env)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Tdqc_pub(Dz1TdqcTarget *tgt, Dz1TdqcArg *arg, Dz1Str script_path, Dz1Str script_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqcPubEnv *env = Dz1TdqcPubEnv_new(arg, tgt->shapes, errp);
	if (env == NULL) ERR_OUT(errp);
	else
	{
		TCHAR dst_name[2048] = { 0, };
		pthread_cleanup_push(Dz1TdqcPubEnv_delAndSetNull, (void *)&env);

		Dz1STRCPY(dst_name, script_name);
		Dz1STRCAT(dst_name, arg->fn_postfix);

		if (0) { }
		else if (Dz1Tdqc_pubFront(env, tgt, dst_name, errp) == FALSE) ERR_OUT(errp);

// 		else if (Dz1TdqcShapeList_pub(tgt->shapes, env, errp) == FALSE) ERR_OUT(errp);
//		else if (Dz1TdqcTblInstanceSeq_pub(tgt->tblseq, env, errp) == FALSE) ERR_OUT(errp);
//		else if (Dz1TdqQueryList_pub(tgt->queries, env, errp) == FALSE) ERR_OUT(errp);

		else if (Dz1TdqcOrderList_pub(tgt->ord, env, errp) == FALSE) ERR_OUT(errp);

		else if (Dz1Tdqc_pubBottom(env, tgt, dst_name, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1TdqcPubEnv_delAndSetNull, (void *)&env);

		if (errp->code == 0)
		{
			if (0) { }
			else if ((*errp = file_fix(arg->dst_path_c, dst_name, Dz1Text("c"), script_path, script_name, Dz1Text("tdq") )).code) ERR_OUT(errp);
			else if ((*errp = file_fix(arg->dst_path_h, dst_name, Dz1Text("h"), script_path, script_name, Dz1Text("tdq"))).code) ERR_OUT(errp);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
