#ifndef DZ1_JSON_STRUCT_UTIL_H_LOCAL
#define DZ1_JSON_STRUCT_UTIL_H_LOCAL

#include "Dz1JsonStructDef.h"

static __inline__ void _set_null(void *pptr)
{
	void **p = (void **)pptr;
	(*p) = NULL;
}


DZ1_CPPLINK void				 Dz1JsonOutputFifo_push(Dz1JsonOutputFifo *p, Dz1JsonOutputEntry **node);
DZ1_CPPLINK Dz1JsonOutputEntry	*Dz1JsonOutputFifo_pop(Dz1JsonOutputFifo *p, Dz1Error *err);
DZ1_CPPLINK bool_t				 Dz1JsonOutputFifo_isEmpty(Dz1JsonOutputFifo *p);

DZ1_CPPLINK Dz1JsonSpecEntry	*Dz1JsonSpec_findType(Dz1JsonSpec *spec, Dz1Str type_name);
DZ1_CPPLINK Dz1JsonSpecChild	*Dz1JsonSpecChilds_findByName(Dz1JsonSpecChilds *list, Dz1Str name);

DZ1_CPPLINK bool_t Dz1JsonConstruct_apply_child_data(Dz1JsonVarBind *own, Dz1JsonVarBind *child, Dz1Error *err);

DZ1_CPPLINK NewLineMap *Dz1Json_stringify_nl(Dz1JsonNewLine mode);	// never fail func

#endif
