#ifndef DZ1_TDQ_QRY_DEF_UTIL_H
#define DZ1_TDQ_QRY_DEF_UTIL_H

#include <dz1_tdq_qry_def.h>

DZ1_CPPLINK Dz1TdqQueryTblName *Dz1TdqQueryTblSpec_findTblByName(Dz1TdqQueryTblSpec *spec, Dz1Str name);
DZ1_CPPLINK Dz1TdqQueryTblName *Dz1TdqQueryTblSpec_findTblByAlias(Dz1TdqQueryTblSpec *spec, Dz1Str alias);
DZ1_CPPLINK Dz1TdqQueryTblName *Dz1TdqQueryTblSpec_findTbl(Dz1TdqQueryTblSpec *spec, Dz1Str name);

DZ1_CPPLINK bool_t Dz1TdqQueryTblSpec_setBiasTbl(Dz1TdqQueryTblSpec *dst, Dz1Str name, Dz1Str alias, Dz1TdqDbScheme *scm, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqQueryTblSpec_appendJoinTbl(Dz1TdqQueryTblSpec *dst, Dz1Str name, Dz1Str alias, Dz1TdqQueryTblJoin mode, Dz1Str matchon, Dz1TdqDbScheme *scm, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1TdqQryRow_appendTableCol(Dz1TdqQryRow *dst, Dz1Str name, Dz1Str tbl_name_or_alias_opt, Dz1Str col_alias, Dz1TdqQueryTblSpec *from, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqQryRow_appendExprColNum(Dz1TdqQryRow *dst, Dz1TdqType num_type, Dz1Str expr, Dz1Str col_alias, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqQryRow_appendExprColReal(Dz1TdqQryRow *dst, Dz1TdqType real_type, Dz1Str expr, Dz1Str col_alias, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqQryRow_appendExprColStr(Dz1TdqQryRow *dst, Dz1TdqType str_type, Dz1Str expr, Dz1Str col_alias, u32_t max_size, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqQryRow_appendExprColTime(Dz1TdqQryRow *dst, Dz1TdqType time_type, Dz1Str expr, Dz1Str col_alias, Dz1Error *err);

#endif
