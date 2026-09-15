#ifndef ITSK_00126_V1_TEST_SCENARIO_PROC_H
#define ITSK_00126_V1_TEST_SCENARIO_PROC_H


#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Itsk00126v2TestScenarioArg.h"
#include "Itsk00126v2TestScenarioEnvUtil.h"
#include "Itsk00126v2TestScenarioMsg.h"
#include "Itsk00126v2TestScenarioTimerUtil.h"


typedef bool_t(*Itsk00126v2TestScenarioF)(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, void* scenario, int ev, void* msg, Dz1Error* errp);

DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProc_triggerPost(void* tSelf, Dz1Error* err);

// ServerRole
DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProcServerRole_start(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProcServerRole_trigger(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProcServerRole_sockProc(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, int ev, void *msg, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProcServerRole_sockMsgInit(void* task, Dz1Error* err);
DZ1_CPPLINK void   Itsk00126v2TestScenarioProcServerRole_sockMsgClear(void* task);

// ClientRole
//DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProcClientRole_start(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioClientRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProcClientRole_sockProc(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioClientRole* s, int ev, void* msg, bool_t* ret_is_copmplete, Dz1Error* err);
//DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProcClientRole_sockMsgInit(void* task, Dz1Error* err);
//DZ1_CPPLINK void   Itsk00126v2TestScenarioProcClientRole_sockMsgClear(void* task);


DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProc_start(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProc_stop(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK void Itsk00126v2TestScenarioProc_release(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Error* err);

DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProc_sockProc(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, void *_msg, Dz1Error* err);

DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProc_sendToPeer(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Binary* src, Dz1Error* err);

DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProc_trigger(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProc_msgInit(void* task, Dz1Error* err);
#endif // !ITSK_00126_V1_TEST_SCENARIO_PROC_H
