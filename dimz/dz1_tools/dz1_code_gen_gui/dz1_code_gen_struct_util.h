#ifndef DZ1_CODE_GEN_STRUCT_UTIL_H
#define DZ1_CODE_GEN_STRUCT_UTIL_H

#include "Dz1CodeGenDef.h"
#include "dz1_code_gen_struct.h"

DZ1_CPPLINK ListControlGenNode *ListControlGenNode_build(str_t name, ObjectInfo *obj, ListControlGenNode *parent, Dz1Error *err);

DZ1_CPPLINK Dz1Error Dz1CodeGenListColumn_setParent(Dz1CodeGenListColumn *dstChild, ListControlGenNode *itemParent);

#endif