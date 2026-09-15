#ifndef GITSN_DSRC_MSG_TEST_SCENARIO_ENV_UTIL_H
#define GITSN_DSRC_MSG_TEST_SCENARIO_ENV_UTIL_H

#include "GitsnDSRCMsgTestScenarioEnv.h"

	
#define GITSN_DSRC_MSG_DEFAULT_SCENARIO			Dz1T("MainScenario")
#define GITSN_DSRC_MSG_SENDER_AGENT				Dz1T("시험 시스템")
#define GITSN_DSRC_MSG_SENDER_SUT				Dz1T("시험 대상 시스템")	

DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_sendUIConfigure(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyState(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyError(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testName, GitsnDSRCMsgProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, GitsnDSRCMsgProcessStatusCode code, Dz1Error* err);


DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyStateToMain(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgNotifyStateArg* arg, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyInfoToMain(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgNotifyInfoArg* arg, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyErrorToMain(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgNotifyErrorArg* arg, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_validateRequestToMain(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgValidateContextArg* arg, Dz1Error* err);

DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioEnvUtil_insertDataFrame(GitsnDSRCMsgTestScenarioEnv* env, Dz1Binary* src, bool_t* ret_is_complete_df, Dz1Error* err);
#endif // GITSN_DSRC_MSG_TEST_SCENARIO_ENV_UTIL_H
