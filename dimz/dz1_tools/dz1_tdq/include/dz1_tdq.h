#ifndef DZ1_TDQ_H
#define DZ1_TDQ_H

#include <dz1_tdq_def.h>

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqRow Utility
DZ1_CPPLINK extern Dz1TdqNullOpt *not_null_no_default;
DZ1_CPPLINK Dz1TdqColumn *Dz1TdqRow_findByName(Dz1TdqRow *row, Dz1Str name);
DZ1_CPPLINK bool_t		  Dz1TdqRow_appendCol(Dz1TdqRow *dst, Dz1TdqColumn *col, Dz1Error *err);
DZ1_CPPLINK bool_t		  Dz1TdqRow_addNum(Dz1TdqRow *dst,  Dz1Str name, Dz1TdqType num_type,	Dz1TdqSqlNumSpec *spec, Dz1TdqNullOpt *null_opt, Dz1Error *err);
DZ1_CPPLINK bool_t		  Dz1TdqRow_addReal(Dz1TdqRow *dst, Dz1Str name, Dz1TdqType real_type,	s64_t percision,		Dz1TdqNullOpt *null_opt, Dz1Error *err);
DZ1_CPPLINK bool_t		  Dz1TdqRow_addStr(Dz1TdqRow *dst,  Dz1Str name, Dz1TdqType str_type,	s64_t max_len,			Dz1TdqNullOpt *null_opt, Dz1Error *err);
DZ1_CPPLINK bool_t		  Dz1TdqRow_addTime(Dz1TdqRow *dst, Dz1Str name, Dz1TdqType time_type,							Dz1TdqNullOpt *null_opt, Dz1Error *err);
DZ1_CPPLINK bool_t		  Dz1TdqRow_addBlob(Dz1TdqRow *dst, Dz1Str name, Dz1TdqType blob_type,  Dz1TdqSqlBlobSpec spec, Dz1TdqNullOpt *null_opt, Dz1Error *err);

DZ1_CPPLINK bool_t		  Dz1TdqRowRef_append(Dz1TdqRowRef *dst, Dz1TdqColumn *col_ref, Dz1Error *err);
DZ1_CPPLINK Dz1TdqColumn *Dz1TdqRowRef_addCol(Dz1TdqRowRef *dst, Dz1Str name, Dz1TdqRow *row, Dz1Error *err);
// Dz1TdqRow Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqIndexList Utility
DZ1_CPPLINK Dz1TdqIndexEntry	*Dz1TdqIndexList_findBySuffix(Dz1TdqIndexList *list, Dz1Str suffix);
DZ1_CPPLINK Dz1Error			 Dz1TdqIndexList_append(Dz1TdqIndexList *dst, Dz1Str idx_suffix, bool_t is_unique, Dz1TdqRow *src_row, ...);
// Dz1TdqIndexList Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblShape Utility
DZ1_CPPLINK Dz1TdqTblShape		*Dz1TdqTblShape_generate(Dz1Str name, Dz1Error *err);
DZ1_CPPLINK Dz1TdqTblShape		*Dz1TdqTblShapeList_findByName(Dz1TdqTblShapeList *list, Dz1Str name);
// Dz1TdqTblShape Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqNameList Utility
DZ1_CPPLINK bool_t				 Dz1TdqNameList_appendName(Dz1TdqNameList *dst, Dz1Str name, Dz1Error *err);
// Dz1TdqNameList Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblInstance Utility
DZ1_CPPLINK Dz1Error			 Dz1TdqFKList_append(Dz1TdqFKList *dst, Dz1Str fk_suffix, Dz1Str peer_tbl_name, Dz1Str peer_idx_suffix_opt, 
													 Dz1TdqForeignKeyMode ou, Dz1TdqForeignKeyMode od, Dz1TdqRow *own_rows, Dz1TdqTblInstanceList *tbls, ...);
DZ1_CPPLINK Dz1Error			 Dz1TdqFKList_append_self(Dz1TdqFKList *dst, Dz1Str fk_suffix, Dz1TdqTblInstance *self, Dz1Str peer_tbl_idx_suffix_opt,
														  Dz1TdqForeignKeyMode ou, Dz1TdqForeignKeyMode od, Dz1TdqRow *own_rows, ...);
DZ1_CPPLINK Dz1TdqTblInstance	*Dz1TdqTblInstanceList_findByName(Dz1TdqTblInstanceList *list, Dz1Str name);
// Dz1TdqTblInstance Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqDbScheme
DZ1_CPPLINK bool_t Dz1TdqDbScheme_reconn(Dz1TdqDbScheme *scm, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1TdqDbScheme_appendInstance(Dz1TdqDbScheme *dst, Dz1TdqTblInstance *node, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqDbScheme_regSimpleQuery(Dz1TdqDbScheme *dst, Dz1TdqTblInstance *tbl, Dz1Error *err);

typedef enum Dz1TdqRowSupply
{
	Dz1TdqRowSupply_error = -1,
	Dz1TdqRowSupply_ok,
	Dz1TdqRowSupply_end
} Dz1TdqRowSupply;

typedef struct Dz1TdqSupplyArg
{
	void **arr;
	u32_t cnt;
} Dz1TdqSupplyArg;

typedef Dz1TdqRowSupply	 (*Dz1TdqRowSupplyF)(void *user_ptr, u32_t row_idx, Dz1TdqSqlVar **dst_cols, u32_t col_cnt, Dz1Error *errp);
typedef void			 (*Dz1TdqRowTakeF)(void *user_ptr, u32_t row_idx, Dz1TdqSqlVar **src_arr, SQLLEN *src_stat_arr, u32_t src_cnt);

// Select or Change Database
DZ1_CPPLINK bool_t Dz1TdqDbScheme_createDB(Dz1TdqDbScheme *scm, Dz1Str db_name, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqDbScheme_selectDB(Dz1TdqDbScheme *scm, Dz1Str db_name, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqDbScheme_destroyDB(Dz1TdqDbScheme *scm, Dz1Str db_name, bool_t commit, Dz1Error *err);

// Create Table
DZ1_CPPLINK bool_t Dz1TdqDbScheme_create(Dz1TdqDbScheme *scm, Dz1Str tbl_name, bool_t commit, Dz1Error *err);	// create single table
DZ1_CPPLINK bool_t Dz1TdqDbScheme_buildDB(Dz1TdqDbScheme *scm, bool_t commit, Dz1Error *err);					// create all tables

// Drop Table
DZ1_CPPLINK bool_t Dz1TdqDbScheme_drop(Dz1TdqDbScheme *scm, Dz1Str tbl_name, bool_t commit, Dz1Error *err);	// drop single table
DZ1_CPPLINK bool_t Dz1TdqDbScheme_breakDB(Dz1TdqDbScheme *scm, bool_t commit, Dz1Error *err);				// drop all tables

// Table Data Manipulate
DZ1_CPPLINK bool_t Dz1TdqDbScheme_insert(Dz1TdqDbScheme *scm, Dz1Str tbl_name, Dz1TdqNameList *supply_cols_opt, Dz1TdqRowSupplyF row_supply, void *user_ptr, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqDbScheme_delete(Dz1TdqDbScheme *scm, Dz1Str tbl_name, Dz1Str whr, Dz1TdqSqlVarArray *args, bool_t commit, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqDbScheme_update(Dz1TdqDbScheme *scm, Dz1Str tbl_name, Dz1TdqSqlNamedVarList *update_vars, Dz1Str whr, Dz1TdqSqlVarArray *whr_args, bool_t commit, Dz1Error *err);

// Query Execute
DZ1_CPPLINK bool_t Dz1TdqDbScheme_select(Dz1TdqDbScheme *scm, Dz1Str q_name, Dz1TdqRowTakeF row_take, void *user_ptr, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err);

// Commit
typedef enum Dz1TdqDbSchemeJobDone
{
	Dz1TdqDbSchemeJobDone_rollback,
	Dz1TdqDbSchemeJobDone_commit
} Dz1TdqDbSchemeJobDone;

DZ1_CPPLINK bool_t		 Dz1TdqDbScheme_JobDone(Dz1TdqDbScheme *scm, Dz1TdqDbSchemeJobDone mode, Dz1Error *err);
static __inline__ void	 Dz1TdqDbScheme_JobRollback(void *ptr)
{
	Dz1TdqDbScheme *scm = (Dz1TdqDbScheme *)ptr;
	Dz1TdqDbScheme_JobDone(scm, Dz1TdqDbSchemeJobDone_rollback, NULL);
}
// Dz1TdqDbScheme
///////////////////////////////////////////////////////////////////////////////

#endif