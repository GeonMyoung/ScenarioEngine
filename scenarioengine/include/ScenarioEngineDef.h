#ifndef _DZ1_TDC_SCENARIO_ENGINE_DEF_H_
#define _DZ1_TDC_SCENARIO_ENGINE_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineException
typedef void (*ScenarioEngineException)(void *exceptionArg, Dz1Error *reason);
// ScenarioEngineException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineDef
typedef struct ScenarioEngineDef
{
	s32_t		dummy;
} ScenarioEngineDef;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineDef *ScenarioEngineDef_new(s32_t dummy, Dz1Error *err);
static __inline__ ScenarioEngineDef *ScenarioEngineDef_gen(Dz1Error *err) { return ScenarioEngineDef_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineDef_purge(ScenarioEngineDef *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineDef_del(ScenarioEngineDef *p);
static __inline__ void ScenarioEngineDef_delAndSetNull(void *ptr)
{
	ScenarioEngineDef **p = (ScenarioEngineDef **)ptr;
	if (p) { ScenarioEngineDef_del(*p); *p = NULL; }
}
// ScenarioEngineDef
////////////////////////////////////////////////////////////////////////////////

#endif
