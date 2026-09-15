#ifndef ITSK_00144_2_TEST_SCENARIO_ENV_UTIL_H
#define ITSK_00144_2_TEST_SCENARIO_ENV_UTIL_H

#include "ITSK00144_2TestScenarioEnv.h"

	


DZ1_CPPLINK bool_t ITSK00144_2TestScenarioEnvUtil_sendUIConfigure(ITSK001442TestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err);

DZ1_CPPLINK bool_t ITSK00144_2TestScenarioEnvUtil_notifyState(ITSK001442TestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioEnvUtil_notifyInfo(ITSK001442TestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioEnvUtil_notifyError(ITSK001442TestScenarioEnv* env, Dz1Str testName, ITSK00144_2ProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err);

DZ1_CPPLINK bool_t ITSK00144_2TestScenarioEnvUtil_validateRequest(ITSK001442TestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, ITSK00144_2ProcessStatusCode code, Dz1Error* err);

#endif // ITSK_00144_2_TEST_SCENARIO_ENV_UTIL_H
