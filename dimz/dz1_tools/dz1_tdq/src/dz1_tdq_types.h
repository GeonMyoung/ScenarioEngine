#ifndef DZ1_TDQ_TYPES_H_LOCAL
#define DZ1_TDQ_TYPES_H_LOCAL

#include <dz1_tdq.h>

DZ1_CPPLINK bool_t Dz1TdqDbIface_sqlCmd_(Dz1TdqDbIface *dbe, Dz1Str query, Dz1TdqSqlVar **arr, u32_t cnt, bool_t commit, Dz1Error *errp);
DZ1_CPPLINK bool_t Dz1TdqDbIface_sqlCmd(Dz1TdqDbIface *dbe, Dz1Str query, Dz1TdqSqlVarArray *args, bool_t commit, Dz1Error *errp);
DZ1_CPPLINK bool_t Dz1TdqDbIface_insert(Dz1TdqDbIface *dbe, Dz1Str query, Dz1TdqColumnRefSeq *cols, Dz1TdqRowSupplyF row_supply, void *user_ptr, bool_t commot, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqDbIface_select(Dz1TdqDbIface *dbe, Dz1Str query, Dz1TdqQryRow *row_spec, Dz1TdqRow *alt_row_spec, Dz1TdqRowTakeF row_taker, void *user_data, Dz1TdqSqlVarArray *args, Dz1Error *errp);
DZ1_CPPLINK bool_t Dz1TdqDbIface_commit(Dz1TdqDbIface *dbe, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqDbIface_rollback(Dz1TdqDbIface *dbe, Dz1Error *err);

DZ1_CPPLINK Dz1Error Dz1TdqDbIface_tblExist(Dz1TdqDbIface *dbe, Dz1Str tbl_name, bool_t *ret_status);

#endif
