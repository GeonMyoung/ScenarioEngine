#ifndef DZ1_TDQ_VAT_DEF_UTIL_H_LOCAL
#define DZ1_TDQ_VAT_DEF_UTIL_H_LOCAL

#include "dz1_tdq_util.h"
#include "dz1_tdq_var_def.h"
#include "dz1_tdq_row_def.h"
#include "dz1_tdq_qry_def.h"
#include <dz1_tdq_var_def_util.h>

DZ1_CPPLINK Dz1TdqSqlStr *Dz1TdqSqlStr_newFromStr(Dz1Str str, Dz1Error *err);
DZ1_CPPLINK Dz1TdqSqlStr *Dz1TdqSqlStr_newFromBin(Dz1Binary *bin, Dz1Error *err);

DZ1_CPPLINK Dz1TdqSqlDate *Dz1TdqSqlDate_genFromTM(struct tm *p, Dz1Error *err);
DZ1_CPPLINK Dz1TdqSqlTime *Dz1TdqSqlTime_genFromTM(struct tm *p, Dz1Error *err);
DZ1_CPPLINK Dz1TdqSqlStamp *Dz1TdqSqlStamp_genFromTM(struct tm *p, Dz1Error *err);

DZ1_CPPLINK Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_genFromSpec(Dz1TdqColumnRefSeq *src, Dz1Error *err);
DZ1_CPPLINK Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_genFromSelSpec(Dz1TdqQryRow *src, Dz1Error *err);

DZ1_CPPLINK Dz1Error Dz1TdqSqlTypeSpec_isCompat(Dz1TdqSqlTypeSpec *basis, Dz1TdqSqlTypeSpec *compat, bool_t *ret_compat);
#endif
