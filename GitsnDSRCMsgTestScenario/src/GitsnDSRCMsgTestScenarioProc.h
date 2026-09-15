#ifndef GITSN_DSRC_MSG_TEST_SCENARIO_PROC_H
#define GITSN_DSRC_MSG_TEST_SCENARIO_PROC_H


#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "GitsnDSRCMsgTestScenarioArg.h"
#include "GitsnDSRCMsgTestScenarioEnvUtil.h"
#include "GitsnDSRCMsgTestScenarioMsg.h"
#include "GitsnDSRCMsgTestScenarioTimerUtil.h"


typedef bool_t(*GitsnDSRCMsgTestScenarioF)(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, void* scenario, int ev, void* msg, Dz1Error* errp);

DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProc_triggerPost(void* tSelf, Dz1Error* err);

// ServerRole
//DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProcServerRole_start(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProcServerRole_trigger(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProcServerRole_sockProc(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenarioServerRole* s, int ev, void *msg, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProcServerRole_sockMsgInit(void* task, Dz1Error* err);
//DZ1_CPPLINK void   GitsnDSRCMsgTestScenarioProcServerRole_sockMsgClear(void* task);

// ClientRole
//DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProcClientRole_start(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenarioClientRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProcClientRole_sockProc(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenarioClientRole* s, int ev, void* msg, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProcClientRole_sockMsgInit(void* task, Dz1Error* err);
//DZ1_CPPLINK void   GitsnDSRCMsgTestScenarioProcClientRole_sockMsgClear(void* task);


DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProc_start(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProc_stop(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK void GitsnDSRCMsgTestScenarioProc_release(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Error* err);

DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProc_sockProc(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenario* s, GitsnDSRCMsgScenarioEvent ev, void *_msg, Dz1Error* err);

DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProc_sendToPeer(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Binary* src, Dz1Error* err);

DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProc_trigger(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProc_msgInit(void* task, Dz1Error* err);


DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioObu2Rsu_sockMsgInit(void* task, Dz1Error* err);
DZ1_CPPLINK void GitsnDSRCMsgTestScenarioObu2Rsu_sockMsgClear(void* task);



#endif // !GITSN_DSRC_MSG_TEST_SCENARIO_PROC_H
