#ifndef _DZ1_TDC_SCENARIO_ENGINE_TIMER_H_
#define _DZ1_TDC_SCENARIO_ENGINE_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineDef.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineTimer
typedef struct ScenarioEngineTimer
{
	u32_t		id;
} ScenarioEngineTimer;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineTimer *ScenarioEngineTimer_new(u32_t id, Dz1Error *err);
static __inline__ ScenarioEngineTimer *ScenarioEngineTimer_gen(Dz1Error *err) { return ScenarioEngineTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineTimer_purge(ScenarioEngineTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineTimer_del(ScenarioEngineTimer *p);
static __inline__ void ScenarioEngineTimer_delAndSetNull(void *ptr)
{
	ScenarioEngineTimer **p = (ScenarioEngineTimer **)ptr;
	if (p) { ScenarioEngineTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineTimer_dump(ScenarioEngineTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ScenarioEngineTimer_cmp(ScenarioEngineTimer *a, ScenarioEngineTimer *b); 
// ScenarioEngineTimer
////////////////////////////////////////////////////////////////////////////////

#endif
