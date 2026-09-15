#ifndef DZ1_TDQ_QRY_DEF_UTIL_H_LOCAL
#define DZ1_TDQ_QRY_DEF_UTIL_H_LOCAL

#include "dz1_tdq_util.h"
#include "dz1_tdq_qry_def.h"
#include <dz1_tdq_qry_def_util.h>

DZ1_CPPLINK Dz1TdqQuery *Dz1TdqQueryList_findByName(Dz1TdqQueryList *list, Dz1Str name);

DZ1_CPPLINK bool_t		 Dz1TdqQryRow_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQryRow *src, bool_t use_full_name, Dz1Error *err);
DZ1_CPPLINK u32_t		 Dz1TdqQueryTblSpec_get_tblCnt(Dz1TdqQueryTblSpec *src);
DZ1_CPPLINK bool_t		 Dz1TdqQueryTblSpec_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQueryTblSpec *src, Dz1Error *err);
DZ1_CPPLINK bool_t		 Dz1TdqQryRefCols_sqlEnumerate(Dz1ElasticBuf *dst, Dz1TdqQryRefCols *src, bool_t use_full_name, Dz1Error *err);

#endif