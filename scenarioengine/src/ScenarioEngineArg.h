#ifndef _DZ1_TDC_SCENARIO_ENGINE_ARG_H_
#define _DZ1_TDC_SCENARIO_ENGINE_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ScenarioEngineDef.h"
#include "dz1_asn1_support.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineArg
typedef struct ScenarioEngineArg
{
	Dz1Asn1UTF8Str				*ws_server;
	ScenarioEngineException		 exceptionProc;
	void						*exceptionArg;
} ScenarioEngineArg;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineArg *ScenarioEngineArg_new(Dz1Asn1UTF8Str *ws_server, 
																 ScenarioEngineException exceptionProc, 
																 void *exceptionArg, Dz1Error *err);
static __inline__ ScenarioEngineArg *ScenarioEngineArg_gen(Dz1Error *err) { return ScenarioEngineArg_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineArg_purge(ScenarioEngineArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineArg_del(ScenarioEngineArg *p);
static __inline__ void ScenarioEngineArg_delAndSetNull(void *ptr)
{
	ScenarioEngineArg **p = (ScenarioEngineArg **)ptr;
	if (p) { ScenarioEngineArg_del(*p); *p = NULL; }
}
// ScenarioEngineArg
////////////////////////////////////////////////////////////////////////////////

#endif
