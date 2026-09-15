#ifndef DZ1_TJSONC_UTIL_H
#define DZ1_TJSONC_UTIL_H

#include <Dz1TdcInfoModule.h>
#include "dz1_tjsonc_def.h"

DZ1_CPPLINK bool_t Dz1JsonTargetObjects_append(Dz1JsonTargetObjects *dst, ObjectInfo *src, bool_t cascade, Dz1MdefcModule *module, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JsonCompileIncs_appendPath(Dz1JsonCompileIncs *dst, Dz1Str arg_str, Dz1Error *err);

#endif
