#ifndef DZ1_TDQ_VAR_DEF_UTIL_H
#define DZ1_TDQ_VAR_DEF_UTIL_H

#include <dz1_tdq_def.h>

static __inline__ u32_t _category_of(Dz1TdqSqlTypeSpecPresent v) { return ((v >> 4) & 0xF); }

DZ1_CPPLINK bool_t Dz1TdqSqlDate_setFromT(Dz1TdqSqlDate *dst, time_t src, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlTime_setFromT(Dz1TdqSqlTime *dst, time_t src, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlStamp_setFromT(Dz1TdqSqlStamp *dst, time_t src, Dz1Error *err);

DZ1_CPPLINK void Dz1TdqSqlVar_setNullValue(Dz1TdqSqlVar *p);

#define				Dz1TdqSqlVarGetNum(ptr, memb, nullval)	((ptr)->present != Dz1TdqSqlVarPresent_nul ? (ptr)->x.##memb : nullval)
DZ1_CPPLINK bool_t	Dz1TdqSqlVarGetStr(Dz1Str *dst, Dz1TdqSqlVar *src, Dz1Error *err);
DZ1_CPPLINK bool_t	Dz1TdqSqlVarGetBin(Dz1Binary **dst, Dz1TdqSqlVar *src, long len, Dz1Error *err);
DZ1_CPPLINK bool_t	Dz1TdqSqlVarGetDate(time_t *dst, Dz1TdqSqlVar *src, Dz1Error *err);
DZ1_CPPLINK bool_t	Dz1TdqSqlVarGetTime(time_t *dst, Dz1TdqSqlVar *src, Dz1Error *err);
DZ1_CPPLINK bool_t	Dz1TdqSqlVarGetStamp(time_t *dst, Dz1TdqSqlVar *src, Dz1Error *err);

#define Dz1TdqSqlStr_isNULL(ptr)				((ptr)->present == Dz1TdqSqlVarPresent_nul || (ptr)->x.string == NULL || (ptr)->x.string->text == NULL)

DZ1_CPPLINK bool_t Dz1TdqSqlVarArray_addNum(Dz1TdqSqlVarArray *dst,  Dz1TdqSqlVarPresent num_type,  void *val_ptr, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlVarArray_addReal(Dz1TdqSqlVarArray *dst,								void *val_ptr, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlVarArray_addStr(Dz1TdqSqlVarArray *dst,  Dz1TdqSqlVarPresent str_type,  void *val_ptr, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlVarArray_addTime(Dz1TdqSqlVarArray *dst, Dz1TdqSqlVarPresent time_type, time_t *val_ptr,Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlVarArray_addBlob(Dz1TdqSqlVarArray *dst, Dz1TdqSqlVarPresent blob_type, Dz1Binary *val_ptr,Dz1Error *err);

DZ1_CPPLINK Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVarList_findByName(Dz1TdqSqlNamedVarList *list, Dz1Str name);

DZ1_CPPLINK bool_t Dz1TdqSqlNamedVarList_addNum(Dz1TdqSqlNamedVarList  *dst, Dz1Str name, Dz1TdqSqlVarPresent num_type,  void *val_ptr, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlNamedVarList_addReal(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent real_type, void *val_ptr, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlNamedVarList_addStr(Dz1TdqSqlNamedVarList  *dst, Dz1Str name, Dz1TdqSqlVarPresent str_type,  void *val_ptr, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlNamedVarList_addTime(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent time_type, time_t *val_ptr,Dz1Error *err);

typedef Dz1TdqSqlBlobToDB *(*Dz1TdqUserBlobWrite)(void *ptr, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1TdqSqlNamedVarList_addBlob(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent blob_type, Dz1TdqUserBlobWrite bw, void *bw_ptr, Dz1Error *err);
//DZ1_CPPLINK bool_t Dz1TdqSqlNamedVarList_addBlobR(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent blob_type, Dz1TdqSqlBlobFromDB *val_ptr, Dz1Error *err);

DZ1_CPPLINK void				   Dz1TdqSqlNamedVarList_removeByName(Dz1TdqSqlNamedVarList *list, Dz1Str name);
DZ1_CPPLINK Dz1TdqSqlNamedVarList *Dz1TdqSqlNamedVarList_collect(Dz1TdqSqlNamedVarList *src, Dz1Str comma_seprated_names, Dz1Error *err);

#endif
