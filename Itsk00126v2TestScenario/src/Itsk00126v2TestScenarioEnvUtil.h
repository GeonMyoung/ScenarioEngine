#ifndef ITSK_00126_V1_TEST_SCENARIO_ENV_UTIL_H
#define ITSK_00126_V1_TEST_SCENARIO_ENV_UTIL_H

#include "Itsk00126v2TestScenarioEnv.h"

	
#define ITSK_00126_V1_DEFAULT_SCENARIO			Dz1T("MainScenario")
#define ITSK_00126_V1_SENDER_AGENT				Dz1T("시험 시스템")
#define ITSK_00126_V1_SENDER_SUT				Dz1T("시험 대상 시스템")	

DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_sendUIConfigure(Itsk00126V2TestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_notifyState(Itsk00126V2TestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_notifyInfo(Itsk00126V2TestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_notifyError(Itsk00126V2TestScenarioEnv* env, Dz1Str testName, Itsk00126v2ProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_validateRequest(Itsk00126V2TestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, Itsk00126v2ProcessStatusCode code, Dz1Error* err);


DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_notifyStateToMain(Itsk00126V2TestScenarioEnv* env, Itsk00126v2NotifyStateArg* arg, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_notifyInfoToMain(Itsk00126V2TestScenarioEnv* env, Itsk00126v2NotifyInfoArg* arg, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_notifyErrorToMain(Itsk00126V2TestScenarioEnv* env, Itsk00126v2NotifyErrorArg* arg, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126V2TestScenarioEnvUtil_validateRequestToMain(Itsk00126V2TestScenarioEnv* env, Itsk00126v2ValidateContextArg* arg, Dz1Error* err);

#endif // ITSK_00126_V1_TEST_SCENARIO_ENV_UTIL_H
