#ifndef SAMPLE_TDQ_H
#define SAMPLE_TDQ_H

#include <dz1_tdq.h>

#include "sample.h"

DZ1_CPPLINK bool_t MyDataTbl_insert(Dz1TdqDbScheme *scm, MyDataRow *row, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyDataTbl_insertA(Dz1TdqDbScheme *scm, MyDataRow **arr, u32_t cnt, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyDataTbl_insertL(Dz1TdqDbScheme *scm, MyDataTbl *rows, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyDataTbl_update(Dz1TdqDbScheme *scm, MyDataRow *key, MyDataRow *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyDataTbl_delete(Dz1TdqDbScheme *scm, MyDataRow *key, bool_t commit, Dz1Error *err);
DZ1_CPPLINK MyDataTbl *MyDataTbl_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);

DZ1_CPPLINK bool_t MyTableA_insert(Dz1TdqDbScheme *scm, MyStructAAAA *row, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableA_insertA(Dz1TdqDbScheme *scm, MyStructAAAA **arr, u32_t cnt, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableA_insertL(Dz1TdqDbScheme *scm, MyStructAAAAList *rows, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableA_update(Dz1TdqDbScheme *scm, MyStructAAAA *key, MyStructAAAA *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableA_delete(Dz1TdqDbScheme *scm, MyStructAAAA *key, bool_t commit, Dz1Error *err);
DZ1_CPPLINK MyStructAAAAList *MyTableA_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);

DZ1_CPPLINK bool_t MyTableB_insert(Dz1TdqDbScheme *scm, MyStructBBBB *row, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableB_insertA(Dz1TdqDbScheme *scm, MyStructBBBB **arr, u32_t cnt, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableB_insertL(Dz1TdqDbScheme *scm, MyStructBBBBList *rows, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableB_update(Dz1TdqDbScheme *scm, MyStructBBBB *key, MyStructBBBB *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableB_delete(Dz1TdqDbScheme *scm, MyStructBBBB *key, bool_t commit, Dz1Error *err);
DZ1_CPPLINK MyStructBBBBList *MyTableB_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);

DZ1_CPPLINK bool_t MyTableC_insert(Dz1TdqDbScheme *scm, MyStructBBBB *row, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableC_insertA(Dz1TdqDbScheme *scm, MyStructBBBB **arr, u32_t cnt, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableC_insertL(Dz1TdqDbScheme *scm, MyStructBBBBList *rows, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableC_update(Dz1TdqDbScheme *scm, MyStructBBBB *key, MyStructBBBB *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t MyTableC_delete(Dz1TdqDbScheme *scm, MyStructBBBB *key, bool_t commit, Dz1Error *err);
DZ1_CPPLINK MyStructBBBBList *MyTableC_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);
DZ1_CPPLINK CentralList *CentralData2_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);
DZ1_CPPLINK CentralList *CentralData_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);

DZ1_CPPLINK bool_t sample_tdq_init(Dz1TdqDbScheme *scm, Dz1Error *err);

#endif // SAMPLE_TDQ_H
