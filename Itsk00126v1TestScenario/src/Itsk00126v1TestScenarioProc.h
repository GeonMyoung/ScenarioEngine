#ifndef ITSK_00126_V1_TEST_SCENARIO_PROC_H
#define ITSK_00126_V1_TEST_SCENARIO_PROC_H


#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Itsk00126v1TestScenarioArg.h"
#include "Itsk00126v1TestScenarioEnvUtil.h"
#include "Itsk00126v1TestScenarioMsg.h"
#include "Itsk00126v1TestScenarioTimerUtil.h"


typedef bool_t(*Itsk00126v1TestScenarioF)(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, void* scenario, int ev, void* msg, Dz1Error* errp);

DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProc_triggerPost(void* tSelf, Dz1Error* err);

// ServerRole
DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProcServerRole_start(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Itsk00126v1ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProcServerRole_trigger(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Itsk00126v1ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProcServerRole_sockProc(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Itsk00126v1ScenarioServerRole* s, int ev, void *msg, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProcServerRole_sockMsgInit(void* task, Dz1Error* err);
DZ1_CPPLINK void   Itsk00126v1TestScenarioProcServerRole_sockMsgClear(void* task);

// ClientRole
//DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProcClientRole_start(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Itsk00126v1ScenarioClientRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProcClientRole_sockProc(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Itsk00126v1ScenarioClientRole* s, int ev, void* msg, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProcClientRole_sockMsgInit(void* task, Dz1Error* err);
//DZ1_CPPLINK void   Itsk00126v1TestScenarioProcClientRole_sockMsgClear(void* task);


DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProc_start(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProc_stop(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK void Itsk00126v1TestScenarioProc_release(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Dz1Error* err);

DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProc_sockProc(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, void *_msg, Dz1Error* err);

DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProc_sendToPeer(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Dz1Binary* src, Dz1Error* err);

DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProc_trigger(Itsk00126V1TestScenarioArg* arg, Itsk00126V1TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v1TestScenarioProc_msgInit(void* task, Dz1Error* err);
#endif // !ITSK_00126_V1_TEST_SCENARIO_PROC_H
