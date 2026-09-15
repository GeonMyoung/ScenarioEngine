#ifndef ITSK_00144_2_TEST_SCENARIO_PROC_H
#define ITSK_00144_2_TEST_SCENARIO_PROC_H


#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "ITSK00144_2TestScenarioArg.h"
#include "ITSK00144_2TestScenarioEnvUtil.h"
#include "ITSK00144_2TestScenarioMsg.h"
#include "ITSK00144_2TestScenarioTimerUtil.h"


#define ITSK_00144_2_DEFAULT_SCENARIO			Dz1T("MainScenario")
#define ITSK_00144_2_SENDER_AGENT				Dz1T("시험 시스템")
#define ITSK_00144_2_SENDER_SUT					Dz1T("시험 대상 시스템")	


typedef bool_t(*ITSK00144_2TestScenarioF)(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* scenario, int ev, void* msg, Dz1Error* errp);

DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProc_triggerPost(void* tSelf, Dz1Error* err);

// ServerRole
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProcServerRole_start(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProcServerRole_trigger(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProcServerRole_sockProc(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, int ev, void *msg, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProcServerRole_sockMsgInit(void* task, Dz1Error* err);
DZ1_CPPLINK void   ITSK00144_2TestScenarioProcServerRole_sockMsgClear(void* task);

// LinkUnitRole
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProcLinkUnitRole_start(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioLinkUnitRole* s, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProcLinkUnitRole_sockProc(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioLinkUnitRole* s, int ev, void* msg, bool_t* ret_is_copmplete, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProcLinkUnitRole_sockMsgInit(void* task, Dz1Error* err);
DZ1_CPPLINK void   ITSK00144_2TestScenarioProcLinkUnitRole_sockMsgClear(void* task);


DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProc_start(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProc_stop(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK void ITSK00144_2TestScenarioProc_release(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* err);

DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProc_sockProc(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void *_msg, Dz1Error* err);

DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProc_sendToPeer(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Binary* src, Dz1Error* err);

DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProc_trigger(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProc_msgInit(void* task, Dz1Error* err);
#endif // !ITSK_00144_2_TEST_SCENARIO_PROC_H
