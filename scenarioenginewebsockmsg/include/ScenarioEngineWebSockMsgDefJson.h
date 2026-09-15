#ifndef SCENARIO_ENGINE_WEB_SOCK_MSG_DEF_JSON_H
#define SCENARIO_ENGINE_WEB_SOCK_MSG_DEF_JSON_H

#include <Dz1Json.h>
#include "ScenarioEngineWebSockMsgDef.h"

DZ1_CPPLINK bool_t ScenarioEngineWebSockMsgDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err);
DZ1_CPPLINK Dz1JsonSpec *ScenarioEngineWebSockMsgDef_genJsonSpec(Dz1Error *err);

#endif // SCENARIO_ENGINE_WEB_SOCK_MSG_DEF_JSON_H
