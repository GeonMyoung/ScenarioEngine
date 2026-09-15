#ifndef SCENARIO_ENGINE_ENV_UTIL_H
#define SCENARIO_ENGINE_ENV_UTIL_H

#include "ScenarioEngineEnv.h"
#include <ScenarioEngineWebSockMsg.h>
#include <dz1_asn1.h>


DZ1_CPPLINK bool_t ScenarioEngineEnv_establishWS(ScenarioEngineEnv* env, Dz1Asn1UTF8Str* ws_server_uri, Dz1Error* err);
DZ1_CPPLINK bool_t ScenarioEngineEnv_sendDescribe(ScenarioEngineEnv* env, Dz1Error* err);
DZ1_CPPLINK bool_t ScenarioEngineEnv_sendTeardown(ScenarioEngineEnv* env, Dz1Error* err);
DZ1_CPPLINK bool_t ScenarioEngineEnv_jsonParseWS(ScenarioEngineEnv* env, void* timer, Dz1WebSockMsg* ws_msg, Dz1Error* errp);



DZ1_CPPLINK bool_t ScenarioEngineEnv_responseToServer(ScenarioEngineEnv* env, u32_t seq, Dz1Error* err);
DZ1_CPPLINK bool_t ScenarioEngineEnvUtil_sendUIConfigureToServer(ScenarioEngineEnv* env, ScenarioEngineRequestMessageUIConfigure* ui_conf, Dz1Error* err);
DZ1_CPPLINK bool_t ScenarioEngineEnv_notifyToServer(ScenarioEngineEnv* env, ScenarioEngineRequestMessageNotify* notify, Dz1Error* err);
DZ1_CPPLINK bool_t ScenarioEngineEnv_ValidateRequestToServer(ScenarioEngineEnv* env, ScenarioEngineRequestMessageValidate* validate, Dz1Error* err);

#endif // !SCENARIO_ENGINE_ENV_UTIL_H

