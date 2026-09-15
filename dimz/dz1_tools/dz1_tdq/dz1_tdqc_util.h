#ifndef DZ1_TDQC_UTIL_H
#define DZ1_TDQC_UTIL_H

#include "dz1_tdqc_def.h"

DZ1_CPPLINK Dz1TdqcShapeOptEntry	*Dz1TdqcShapeOptList_findByName(Dz1TdqcShapeOptList *list, Dz1Str instance);
DZ1_CPPLINK bool_t					 Dz1TdqcShapeOptList_appendOpt(Dz1TdqcShapeOptList *opts, Dz1Str instance, Dz1Str api_prefix, Dz1Error *err);
DZ1_CPPLINK ObjectInfo				*Dz1MdefcModuleList_findObject(Dz1MdefcModuleList *list, Dz1Str name);
DZ1_CPPLINK Dz1TdqTblShape			*Dz1TdqTblShape_genFromObj(Dz1Str name, ObjectInfo *src, Dz1TdqcShapeOptList *opts, Dz1Error *err);
DZ1_CPPLINK Dz1TdqTblShape			*Dz1TdqTblShape_genFromRef(Dz1Str name, ObjectInfo *src, Dz1TdqQryRow *sel, Dz1TdqcShapeOptList *ret_opts, Dz1TdqcShapeList *tdqc_shapes, Dz1Error *err);
DZ1_CPPLINK Dz1TdqTblShape			*Dz1TdqcShapeList_findShapeByName(Dz1TdqcShapeList *list, Dz1Str name);
DZ1_CPPLINK Dz1TdqcShape			*Dz1TdqcShapeList_findByName(Dz1TdqcShapeList *list, Dz1Str name);
DZ1_CPPLINK bool_t					 Dz1TdqcTarget_appendTbl(Dz1TdqcTarget *dst, Dz1TdqcTblInstance *tbl, Dz1Error *err);
DZ1_CPPLINK Dz1TdqcTblInstance		*Dz1TdqcTblInstanceList_findByName(Dz1TdqcTblInstanceList *list, Dz1Str name);
DZ1_CPPLINK Dz1TdqcTblInstance		*Dz1TdqcTarget_findTableByName(Dz1TdqcTarget *dst, Dz1Str name);
DZ1_CPPLINK Dz1TdqSqlTypeSpec		*Dz1TdqSqlTypeSpec_genFromInfo(StructMemberEntry *info, Dz1TdqcShapeOptEntry **ret_opt, Dz1Error *errp);
DZ1_CPPLINK bool_t					 Dz1TdqSqlTypeSpec_setSizeOpt(Dz1TdqSqlTypeSpec *dst, s64_t sz, Dz1Error *err);
DZ1_CPPLINK bool_t					 Dz1TdqcOrderList_appendShp(Dz1TdqcOrderList *dst, Dz1TdqcShape *shp, Dz1Error *err);
DZ1_CPPLINK bool_t					 Dz1TdqcOrderList_appendTbl(Dz1TdqcOrderList *dst, Dz1TdqcTblInstance *tbl, Dz1Error *err);
DZ1_CPPLINK bool_t					 Dz1TdqcOrderList_appendQry(Dz1TdqcOrderList *dst, Dz1TdqcQuery *qry, Dz1Error *err);
#endif
