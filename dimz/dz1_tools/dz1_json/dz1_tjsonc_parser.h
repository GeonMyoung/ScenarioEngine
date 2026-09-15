#ifndef DZ1_TJSONC_PARSER_H
#define DZ1_TJSONC_PARSER_H

#include <Dz1TdcInfoModule.h>
#include "dz1_tjsonc_def.h"

typedef struct Dz1JsonCompilerEnv
{
	Dz1Str						*incs;
	u32_t						 incs_cnt;
	Dz1MdefcModule				*src_module;
	Dz1Str						 module_name;
	Dz1JsonTargetObjects		*objs;
} Dz1JsonCompilerEnv;
DZ1_CPPLINK void		Dz1JsonCompilerEnv_del(Dz1JsonCompilerEnv *p);
static __inline__ void	Dz1JsonCompilerEnv_delAndSetNull(void *pptr)
{
	Dz1JsonCompilerEnv **p = (Dz1JsonCompilerEnv **)pptr;
	Dz1JsonCompilerEnv_del(*p); *p = NULL;
}

DZ1_CPPLINK Dz1JsonCompilerEnv *Dz1Tjsonc_parse(str_t src_text, Dz1JsonCompilerArg *args, Dz1Error *err);

#endif
