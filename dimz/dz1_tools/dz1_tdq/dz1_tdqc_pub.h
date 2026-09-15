#ifndef DZ1_TDQC_PUB_TBL_H_LOCAL
#define DZ1_TDQC_PUB_TBL_H_LOCAL

#include <dz1_tdq.h>
#include "dz1_tdqc_def.h"

#define CRLF				"\r\n"

#define SHAPE_REG_POSTFIX			Dz1Text("_regShape")
#define SHAPE_SUP_SINGLE_POSTFIX	Dz1Text("_writeRow")
#define SHAPE_TAK_SINGLE_POSTFIX	Dz1Text("_readRow")
#define SHAPE_SUP_MULTI_POSTFIX		Dz1Text("_writeRows")

#define TABLE_REG_POSTFIX			Dz1Text("_regTable")

DZ1_CPPLINK void _mk_dcl_name(char *dst, char *src);
DZ1_CPPLINK void _get_mod_name(char dst[1024], str_t src);
DZ1_CPPLINK Dz1Error file_fix(Dz1Str dst_path, Dz1Str dst_name, Dz1Str dst_ext, Dz1Str script_path, Dz1Str script_name, Dz1Str script_ext);

typedef struct Dz1TdqcPubEnv
{
	FILE				*src_fp;
	FILE				*hdr_fp;
	Dz1TdqcShapeList	*shapes;
} Dz1TdqcPubEnv;

DZ1_CPPLINK Dz1TdqcPubEnv *Dz1TdqcPubEnv_new(Dz1TdqcArg *arg, Dz1TdqcShapeList *list_ref, Dz1Error *errp);
DZ1_CPPLINK void Dz1TdqcPubEnv_del(Dz1TdqcPubEnv *p);
static __inline__ void Dz1TdqcPubEnv_delAndSetNull(void *pptr)
{
	Dz1TdqcPubEnv **p = (Dz1TdqcPubEnv **)pptr;
	Dz1TdqcPubEnv_del(*p); *p = NULL;
}

typedef struct ColumnPubEnv
{
	Dz1TdqColumn	   **col;
	u32_t				 col_cnt;

	StructMemberEntry  **memb;
	u32_t				 memb_cnt;
} ColumnPubEnv;

DZ1_CPPLINK ColumnPubEnv *ColumnPubEnv_new(Dz1TdqColumnRefSeq *row_seq, StructMemberList *memb, Dz1Error *err);
DZ1_CPPLINK void ColumnPubEnv_del(ColumnPubEnv *p);
static __inline__ void ColumnPubEnv_delAndSetNull(void *pptr)
{
	ColumnPubEnv **p = (ColumnPubEnv **)pptr;
	ColumnPubEnv_del(*p); *p = NULL;
}

typedef struct ColumnPubSupplyApi
{
	Dz1TdqSqlTypeSpecPresent		 present;
	bool_t							(*pub)(FILE *fp, u32_t idx, Dz1TdqColumn *col, StructMemberEntry *memb, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp);
} ColumnPubSupplyApi;
DZ1_CPPLINK ColumnPubSupplyApi *ColumnPubSupplyApi_find(ColumnPubSupplyApi *tbl, Dz1TdqSqlTypeSpecPresent present);
DZ1_CPPLINK bool_t ColumnPubSupplyApi_pub(FILE *fp, ColumnPubEnv *env, ColumnPubSupplyApi *tbl, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp);

DZ1_CPPLINK bool_t Dz1TdqRowRef_pub_enumerate(FILE *fp, Dz1TdqRowRef *cols, Dz1Error *errp);

DZ1_CPPLINK bool_t _pubSrc_take(FILE *fp, Dz1TdqColumnRefSeq *row_seq, ObjectInfo *entry_obj, ObjectInfo *list_obj, Dz1TdqcShapeOptList *memb_opts, Dz1Error *err);
DZ1_CPPLINK bool_t _pubHdr_take(FILE *fp, ObjectInfo *entry_obj, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1TdqcShape_pubSrc(FILE *fp, Dz1TdqcShape *src, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqcShape_pubHdr(FILE *fp, Dz1TdqcShape *src, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1TdqcTblInstance_pubSrc(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShapeList *shp_list, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqcTblInstance_pubHdr(FILE *fp, Dz1TdqcTblInstance *src, Dz1TdqcShapeList *shp_list, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1TdqcQuery_pubSrc(FILE *fp, Dz1TdqcQuery *q, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqcQuery_pubHdr(FILE *fp, Dz1TdqcQuery *q, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1Tdqc_pub(Dz1TdqcTarget *tgt, Dz1TdqcArg *arg, Dz1Str script_path, Dz1Str script_name, Dz1Error *err);

#endif
