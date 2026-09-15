#ifndef ISO14827_TEST_HELPER_SCENARIO_H
#define ISO14827_TEST_HELPER_SCENARIO_H

#include "Iso14827TestHelperArg.h"
#include "Iso14827TestHelperEnvUtil.h"
#include "Iso14827TestHelperTimer.h"
#include <Iso14827TestHelperDefUtil.h>

#include <ItsIso14827.h>
#include <Iso14827dz1.h>

typedef bool_t(*Iso14827TestHelperScenarioF)(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* msg, Dz1Error* errp);
DZ1_CPPLINK bool_t				Iso14827TestScenario_triggerPost(void* tSelf, Dz1Error* err);


///////////////////////////////////////////////////////////////////////////////////////////////////////
// CLIENT1
DZ1_CPPLINK bool_t				Iso14827TestClient1Scenario_check(Iso14827TestClientRole1* s, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1Scenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Iso14827TestClientEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Iso14827TestHelperTimer* tmr, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* err); // pause
DZ1_CPPLINK bool_t				Iso14827TestClient1Scenario_validateReceived(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, void* msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK void				Iso14827TestClient1Scenario_reset(Iso14827TestClientRole1* s, Iso14827TestHelperEnv* env);	// back to prepared status
DZ1_CPPLINK void				Iso14827TestClient1Scenario_release(Iso14827TestClientRole1* s, Iso14827TestHelperEnv* env);	// release resource
DZ1_CPPLINK void				Iso14827TestClientRole1_status(Iso14827TestClientRole1* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
// CLIENT1
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
// CLIENT2
DZ1_CPPLINK bool_t				Iso14827TestClient2Scenario_check(Iso14827TestClientRole2* s, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient2Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient2Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient2Scenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient2Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Iso14827TestClientEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient2Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient2Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* err); // pause
DZ1_CPPLINK void				Iso14827TestClient2Scenario_reset(Iso14827TestClientRole2* s, Iso14827TestHelperEnv* env);	// back to prepared status
DZ1_CPPLINK void				Iso14827TestClient2Scenario_release(Iso14827TestClientRole2* s, Iso14827TestHelperEnv* env);	// release resource
DZ1_CPPLINK void				Iso14827TestClientRole2_status(Iso14827TestClientRole2* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
// CLIENT2
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
// SERVER1
DZ1_CPPLINK bool_t Iso14827TestServer1Scenario_check(Iso14827TestServerRole1* s, Iso14827TestMsgStructAPI* mst_tbl, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer1Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Dz1Error* errp);
DZ1_CPPLINK bool_t Iso14827TestServer1Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer1Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Iso14827TestServerEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer1Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer1Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Dz1Error* err);
DZ1_CPPLINK void   Iso14827TestServer1Scenario_reset(Iso14827TestServerRole1* s, Iso14827TestHelperEnv* env);		// back to prepared status
DZ1_CPPLINK void   Iso14827TestServer1Scenario_release(Iso14827TestServerRole1* s, Iso14827TestHelperEnv* env);	// release resource
DZ1_CPPLINK void   Iso14827TestServerRole1_status(Iso14827TestServerRole1* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
// SERVER1
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
// SERVER2
DZ1_CPPLINK bool_t Iso14827TestServer2Scenario_check(Iso14827TestServerRole2* s, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer2Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Error* errp);
DZ1_CPPLINK bool_t Iso14827TestServer2Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer2Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Iso14827TestServerEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer2Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer2Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Error* err);
DZ1_CPPLINK void   Iso14827TestServer2Scenario_reset(Iso14827TestServerRole2* s, Iso14827TestHelperEnv* env);		// back to prepared status
DZ1_CPPLINK void   Iso14827TestServer2Scenario_release(Iso14827TestServerRole2* s, Iso14827TestHelperEnv* env);	// release resource
DZ1_CPPLINK void   Iso14827TestServerRole2_status(Iso14827TestServerRole2* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
// SERVER2
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
// SERVER3
DZ1_CPPLINK bool_t Iso14827TestServer3Scenario_check(Iso14827TestServerRole3* s, Iso14827TestMsgStructAPI* mst_tbl, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer3Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Error* errp);
DZ1_CPPLINK bool_t Iso14827TestServer3Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer3Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Iso14827TestServerEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer3Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestServer3Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Error* err);
DZ1_CPPLINK void   Iso14827TestServer3Scenario_reset(Iso14827TestServerRole3* s, Iso14827TestHelperEnv* env);		// back to prepared status
DZ1_CPPLINK void   Iso14827TestServer3Scenario_release(Iso14827TestServerRole3* s, Iso14827TestHelperEnv* env);	// release resource
DZ1_CPPLINK void   Iso14827TestServerRole3_status(Iso14827TestServerRole3* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
// SERVER3
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
// DUO CLIENT
DZ1_CPPLINK bool_t					Iso14827TestDuoClientScenario_check(Iso14827TestDuoClientRole* s, Dz1Error* err);
DZ1_CPPLINK bool_t					Iso14827TestDuoClientScenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* err);
DZ1_CPPLINK bool_t					Iso14827TestDuoClientScenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t					Iso14827TestDuoClientScenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t					Iso14827TestDuoClientScenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Iso14827TestClientEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t					Iso14827TestDuoClientScenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t					Iso14827TestDuoClientScenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* err); // pause
DZ1_CPPLINK void					Iso14827TestDuoClientScenario_reset(Iso14827TestDuoClientRole* s, Iso14827TestHelperEnv* env);	// back to prepared status
DZ1_CPPLINK void					Iso14827TestDuoClientScenario_release(Iso14827TestDuoClientRole* s, Iso14827TestHelperEnv* env);	// release resource
DZ1_CPPLINK void					Iso14827TestDuoClientRole_status(Iso14827TestDuoClientRole* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
// DUO CLIENT
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
// DUO SESSION
DZ1_CPPLINK bool_t Iso14827TestDuoSessionScenario_check(Iso14827TestDuoSessionRole* s, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestDuoSessionScenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Error* errp);
DZ1_CPPLINK bool_t Iso14827TestDuoSessionScenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestDuoSessionScenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestDuoSessionScenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Iso14827TestDuoSessionEvent ev, void* t147827msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestDuoSessionScenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Iso14827TestHelperTimer* tmr, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestDuoSessionScenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Error* err);
DZ1_CPPLINK void Iso14827TestDuoSessionScenario_reset(Iso14827TestDuoSessionRole* s, Iso14827TestHelperEnv* env);
DZ1_CPPLINK void Iso14827TestDuoSessionScenario_release(Iso14827TestDuoSessionRole* s, Iso14827TestHelperEnv* env);
DZ1_CPPLINK void Iso14827TestDuoSessionRole_status(Iso14827TestDuoSessionRole* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
// DUO SESSION
///////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////
// CLIENT1 - TECHNICAL_REGULATION
DZ1_CPPLINK bool_t				Iso14827TestClient1ScenarioTR_check(Iso14827TestClientRole1TR* s, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1ScenarioTR_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1TR* s, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1ScenarioTR_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1TR* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1ScenarioTR_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1TR* s, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1ScenarioTR_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1TR* s, Iso14827TestClientEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1ScenarioTR_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1TR* s, Iso14827TestHelperTimer* tmr, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestClient1ScenarioTR_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1TR* s, Dz1Error* err); // pause
DZ1_CPPLINK bool_t				Iso14827TestClient1ScenarioTR_validateReceived(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1TR* s, void* msg, bool_t* ret_is_complete, Dz1Error* err);
DZ1_CPPLINK void				Iso14827TestClient1ScenarioTR_reset(Iso14827TestClientRole1TR* s, Iso14827TestHelperEnv* env);	// back to prepared status
DZ1_CPPLINK void				Iso14827TestClient1ScenarioTR_release(Iso14827TestClientRole1TR* s, Iso14827TestHelperEnv* env);	// release resource
DZ1_CPPLINK void				Iso14827TestClientRole1TR_status(Iso14827TestClientRole1TR* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
// CLIENT1 - TECHNICAL_REGULATION
// CLIENT1
///////////////////////////////////////////////////////////////////////////////////////////////////////



DZ1_CPPLINK bool_t				Iso14827TestScenario_check(Iso14827TestScenario* s, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestScenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err);								//	switch error check
DZ1_CPPLINK bool_t				Iso14827TestScenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err);								//	switch error check
DZ1_CPPLINK bool_t				Iso14827TestScenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestScenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, int ev, void* t14827msg, Dz1Error* err);		//	switch error check

DZ1_CPPLINK Dz1TaskProcStatus	Iso14827TestScenario_timeout(void* uArg, void* uRsc, void* timer, void** tData, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestScenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestScenario_reset(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestScenario_release(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t				Iso14827TestScenario_msgInit(void* task, Dz1Error* err);

DZ1_CPPLINK bool_t				Iso14827TestScenario_validateReceived(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestScenario* s, void* _msg, Dz1Error* err);		


DZ1_CPPLINK void				Iso14827TestHelperScenario_status(Iso14827TestScenario* s, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env);
#endif // !ISO14827_TEST_HELPER_SCENARIO_H
