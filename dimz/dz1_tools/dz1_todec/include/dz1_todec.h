#ifndef DZ1_TODEC_H
#define DZ1_TODEC_H

#include <dz1_todecDef.h>

DZ1_CPPLINK Dz1Error Dz1Todec_convert(Dz1Str mod_path, Dz1Str mod_name, Dz1TodecTargetCodecMode mode, Dz1Str out_path, Dz1Str oSuffix, Dz1Str iSuffix);
DZ1_CPPLINK Dz1Error Dz1Todec_publish(str_t path, str_t name, str_t ext, Dz1TodecPubArg *arg, str_t output_suffix);
DZ1_CPPLINK void Dz1Todec_syntax_dump(void);

typedef void TodecAnalysisData;
DZ1_CPPLINK TodecAnalysisData	*TodecAnalysisData_gen(Dz1Todec *src, Dz1MdefcModule *module, Dz1Error *err);
DZ1_CPPLINK void				 TodecAnalysisData_del(TodecAnalysisData *p);
static __inline__ void			 TodecAnalysisData_delAndSetNull(void *pptr)
{
	TodecAnalysisData **p = (TodecAnalysisData **)pptr;
	TodecAnalysisData_del(*p); *p = NULL;
}
DZ1_CPPLINK void				 TodecAnalysisData_dump(TodecAnalysisData *p, int tab);

#endif