#ifndef TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_PROC_H
#define TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_PROC_H

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "TrafficSignalControllerTestScenarioArg.h"
#include "TrafficSignalControllerTestScenarioEnvUtil.h"
#include "TrafficSignalControllerTestScenarioMsg.h"
#include "TrafficSignalControllerTestScenarioTimer.h"

typedef bool_t(*TrafficSignalControllerF)(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, void* _scenario, int _ev, void* msg, Dz1Error* errp);

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioProc_triggerPost(void* tSelf, Dz1Error* err);


DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioProc_start(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioProc_stop(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK void TrafficSignalControllerTestScenarioProc_release(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, Dz1Error* err);

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioProc_trigger(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, Dz1Error* err);
DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioProc_sockProc(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, TrafficSignalControllerScenario* s, int ev, void* msg, Dz1Error* err);

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioProc_msgInit(void* task, Dz1Error* err);

#endif // !TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_PROC_H
