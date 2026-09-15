#ifndef SCENARIO_ENGINE_H
#define SCENARIO_ENGINE_H

#include <ScenarioEngineDef.h>
#include <dz1_asn1.h>

DZ1_CPPLINK void *ScenarioEngine_new(Dz1Asn1UTF8Str *server_uri, ScenarioEngineException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void ScenarioEngine_del(void *task);

#endif // SCENARIO_ENGINE
