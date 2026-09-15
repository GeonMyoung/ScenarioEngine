#ifndef _DZ1_TDC_SCENARIO_ENGINE_MSGS_H_
#define _DZ1_TDC_SCENARIO_ENGINE_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineDef.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineMsgDefault
typedef struct ScenarioEngineMsgDefault
{
	u32_t		*dummy;
} ScenarioEngineMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineMsgDefault *ScenarioEngineMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ ScenarioEngineMsgDefault *ScenarioEngineMsgDefault_gen(Dz1Error *err) { return ScenarioEngineMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineMsgDefault_purge(ScenarioEngineMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineMsgDefault_del(ScenarioEngineMsgDefault *p);
static __inline__ void ScenarioEngineMsgDefault_delAndSetNull(void *ptr)
{
	ScenarioEngineMsgDefault **p = (ScenarioEngineMsgDefault **)ptr;
	if (p) { ScenarioEngineMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineMsgDefault_dump(ScenarioEngineMsgDefault *p, int tab);
// ScenarioEngineMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif
