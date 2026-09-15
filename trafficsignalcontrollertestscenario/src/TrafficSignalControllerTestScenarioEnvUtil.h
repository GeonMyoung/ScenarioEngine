#ifndef TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_ENG_UTIL_H
#define TRAFFIC_SIGNAL_CONTROLLER_TEST_SCEANRIO_ENV_UTIL_H
#include "TrafficSignalControllerTestScenarioEnv.h"

#define TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO	Dz1T("MainScenario")
#define TRAFFIC_SIGNAL_CONTROLLER_SENDER_AGENT		Dz1T("시험시스템")
#define TRAFFIC_SIGNAL_CONTROLLER_SENDER_SUT		Dz1T("시험대상시스템")

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_sendUIConfigure(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err);

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyState(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyError(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, TrafficSignalControllerProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err);

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_validateRequest(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, TrafficSignalControllerProcessStatusCode code, Dz1Error* err);


DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyState(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyError(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, TrafficSignalControllerProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err);

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyStateToMain(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerNotifyStateArg* arg, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyInfoToMain(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerNotifyInfoArg* arg, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyErrorToMain(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerNotifyErrorArg* arg, Dz1Error* err);

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_sendUIConfigure(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err);

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_validateRequest(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, TrafficSignalControllerProcessStatusCode code, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioEnvUtil_validateRequestToMain(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerValidateContextArg* arg, Dz1Error* err);

#endif // !TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_ENG_UTIL_H
