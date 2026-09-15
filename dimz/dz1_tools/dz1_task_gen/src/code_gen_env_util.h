#ifndef CODE_GEN_ENV_UTIL_H_LOCAL
#define CODE_GEN_ENV_UTIL_H_LOCAL

#include "code_gen_env.h"
#include "txt_util.h"

DZ1_CPPLINK GenArgs2VisualStudioEntry *GenArgs2VisualStudioList_getProj(GenArgs2VisualStudioList *list, GenArgs2VisualStudioVer ver);
DZ1_CPPLINK GenEnv *GenEnv_generate(GenArgs2 *config, Dz1Error *err);

#endif
