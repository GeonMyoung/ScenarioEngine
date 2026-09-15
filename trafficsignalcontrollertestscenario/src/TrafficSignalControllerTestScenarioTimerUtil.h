#ifndef TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_TIMER_UTIL_H_LOCAL
#define TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "TrafficSignalControllerTestScenarioTimer.h"

DZ1_CPPLINK Dz1Error TrafficSignalControllerTestScenarioTimer_set(void *timer, TrafficSignalControllerTestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error TrafficSignalControllerTestScenarioTimer_update(void *timer, TrafficSignalControllerTestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void TrafficSignalControllerTestScenarioTimer_clr(void *timer, TrafficSignalControllerTestScenarioTimer *key);

#endif	// TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_TIMER_UTIL_H_LOCAL
