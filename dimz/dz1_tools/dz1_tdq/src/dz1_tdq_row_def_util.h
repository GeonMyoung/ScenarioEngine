#ifndef DZ1_TDQ_ROW_DEF_UTIL_H_LOCAL
#define DZ1_TDQ_ROW_DEF_UTIL_H_LOCAL

#include <dz1_tdq.h>
#include "dz1_tdq_util.h"
#include "dz1_tdq_row_def.h"


DZ1_CPPLINK Dz1TdqColumn	*Dz1TdqColumnList_findByName(Dz1TdqColumnList *list, Dz1Str name);
DZ1_CPPLINK void			 Dz1TdqColumnList_addCancel(void *ptr);

DZ1_CPPLINK void			 Dz1TdqColumnRefList_addCancel(void *ptr);

DZ1_CPPLINK bool_t			 Dz1TdqColumnRefSeq_enumNames(Dz1ElasticBuf *dst, Dz1TdqColumnRefSeq *cols, Dz1Error *err);

DZ1_CPPLINK bool_t			 Dz1TdqRowRef_isEmpty(Dz1TdqRowRef *p);

DZ1_CPPLINK Dz1Error		 Dz1TdqRow_isCompat(Dz1TdqRow *basis, Dz1TdqRow *compat, bool_t *ret_compat);
DZ1_CPPLINK Dz1Error		 Dz1TdqRowRef_isCompat(Dz1TdqRowRef *basis, Dz1TdqRowRef *compat, bool_t *ret_compat);

#endif
