#ifndef _DZ1_TDC_SCENARIO_ENGINE_ENV_H_
#define _DZ1_TDC_SCENARIO_ENGINE_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineDef.h"
#include "Dz1JsonDef.h"
#include "dz1_web_socket_def.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineEnv
typedef struct ScenarioEngineEnv
{
	void					*tSelf;
	void					*tScenario;
	Dz1JsonSpec				*spec;
	Dz1WebSocket			*wsock;
	Dz1WebSockMsgList		*ws_msgs;
	u32_t					 seq;
	u32_t					 test_done_seq;
} ScenarioEngineEnv;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineEnv *ScenarioEngineEnv_new(void *tSelf, 
																 void *tScenario, 
																 Dz1JsonSpec *spec, 
																 Dz1WebSocket *wsock, 
																 u32_t seq, 
																 u32_t test_done_seq, Dz1Error *err);
static __inline__ ScenarioEngineEnv *ScenarioEngineEnv_gen(Dz1Error *err) { return ScenarioEngineEnv_new(NULL, NULL, NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineEnv_purge(ScenarioEngineEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineEnv_del(ScenarioEngineEnv *p);
static __inline__ void ScenarioEngineEnv_delAndSetNull(void *ptr)
{
	ScenarioEngineEnv **p = (ScenarioEngineEnv **)ptr;
	if (p) { ScenarioEngineEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineEnv_dump(ScenarioEngineEnv *p, int tab);
// ScenarioEngineEnv
////////////////////////////////////////////////////////////////////////////////

#endif
