#ifndef ITSK00144_2_TEST_SCENARIO_TIMER_UTIL_H_LOCAL
#define ITSK00144_2_TEST_SCENARIO_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "ITSK00144_2TestScenarioTimer.h"

#define ITSK_00144_2_TEST_SCENARIO_KEEPALIVE_TIMER		0x00000001

DZ1_CPPLINK Dz1Error ITSK001442TestScenarioTimer_set(void *timer, ITSK001442TestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error ITSK001442TestScenarioTimer_update(void *timer, ITSK001442TestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void ITSK001442TestScenarioTimer_clr(void *timer, ITSK001442TestScenarioTimer *key);

#endif	// ITSK00144_2_TEST_SCENARIO_TIMER_UTIL_H_LOCAL
