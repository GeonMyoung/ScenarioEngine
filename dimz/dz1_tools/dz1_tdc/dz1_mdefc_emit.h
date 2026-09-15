#ifndef DZ1_MDEFC_EMIT_H_LOCAL
#define DZ1_MDEFC_EMIT_H_LOCAL

#include <dz1_error.h>

#define tValTake(dst)		do { (dst) = t->v; t->v = NULL; } while(0)

DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitStruct(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitUnion(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitArray(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitIndex(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitFunc(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitDefined(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitExtern(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitEnum(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitConstant(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitMacro(void *p, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1MdefcEmiter_InitApi(void *p, Dz1Error *err);

#endif