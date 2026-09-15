#ifndef TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_H
#define TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_H

#include <TrafficSignalControllerTestScenarioDef.h>
#include <TrafficSignalControllerTestMsg.h>

// DZ1_CPPLINK void* TrafficSignalControllerTestScenario_new(void* tMain, TrafficSignalControllerScenarioArgument* sc_arg, TrafficSignalControllerTestScenarioException exceptionProc, void* exceptionArg, Dz1Error* err);
DZ1_CPPLINK void *TrafficSignalControllerTestScenario_new(void *tMain, Dz1Str testScenario, TrafficSignalControllerTestScenarioException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void TrafficSignalControllerTestScenario_del(void *task);

#endif // TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO
