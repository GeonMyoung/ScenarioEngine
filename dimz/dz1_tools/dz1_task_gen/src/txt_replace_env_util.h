#ifndef TXT_REPLATE_ENV_UTIL_H_LOCAL
#define TXT_REPLATE_ENV_UTIL_H_LOCAL

#include "dz1_task_gen_args.h"
#include "txt_replace_env.h"

DZ1_CPPLINK Dz1Error		 TxtReplaceEnv_addReplace(TxtReplaceEnv *dst, str_t symbol, str_t replace);
DZ1_CPPLINK TxtReplaceEntry *TxtReplaceEnv_find(TxtReplaceEnv *env, Dz1Str symbol);
DZ1_CPPLINK bool_t			 TxtReplaceEnv_do(TxtReplaceEnv *env, FILE *dst, str_t src[], Dz1GenTextMode txt_mode, Dz1Error *err);
DZ1_CPPLINK bool_t			 TxtReplaceEnv_doElb(TxtReplaceEnv *env, Dz1ElasticBuf *dst, str_t src[], Dz1GenTextMode txt_mode, Dz1Error *err);

#endif
