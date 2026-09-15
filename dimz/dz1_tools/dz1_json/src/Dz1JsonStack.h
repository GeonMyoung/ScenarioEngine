#ifndef DZ1_JSON_STACK_H_LOCAL
#define DZ1_JSON_STACK_H_LOCAL

#include "Dz1JsonStructDef.h"

//DZ1_CPPLINK Dz1JsonStackData *Dz1JsonStackData_generate(Dz1JsonSpecData *td, Dz1JsonSpec *g_spec, Dz1Error *err);
DZ1_CPPLINK Dz1JsonStackData *Dz1JsonStackData_generate(Dz1JsonSpecData *td, Dz1Error *err);
DZ1_CPPLINK Dz1JsonStackData *Dz1JsonStackData_gen_primitive(Dz1JsonSpecEntry *spe, Dz1Error *err);
DZ1_CPPLINK Dz1JsonStackData *Dz1JsonStackData_gen_obj(Dz1JsonSpecEntry *spe, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1JsonEnv_stack_pushPair(Dz1JsonEnv *psr, Dz1JsonSpecEntry *p_spe, void *p_dst, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JsonEnv_stack_gen_push_pair(Dz1JsonEnv *psr, Dz1JsonVarBind *var, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JsonEnv_stack_push(Dz1JsonEnv *psr, Dz1JsonSpecEntry *spe, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JsonEnv_stack_pop(Dz1JsonEnv *psr, Dz1Error *err);

#endif
