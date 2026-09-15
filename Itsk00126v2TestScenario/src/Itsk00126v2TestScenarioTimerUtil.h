#ifndef ITSK00126_V2_TEST_SCENARIO_TIMER_UTIL_H_LOCAL
#define ITSK00126_V2_TEST_SCENARIO_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "Itsk00126v2TestScenarioTimer.h"

DZ1_CPPLINK Dz1Error Itsk00126V2TestScenarioTimer_set(void *timer, Itsk00126V2TestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error Itsk00126V2TestScenarioTimer_update(void *timer, Itsk00126V2TestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void Itsk00126V2TestScenarioTimer_clr(void *timer, Itsk00126V2TestScenarioTimer *key);

#endif	// ITSK00126_V2_TEST_SCENARIO_TIMER_UTIL_H_LOCAL
