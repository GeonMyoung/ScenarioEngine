#ifndef SCENARIO_ENGINE_TIMER_UTIL_H_LOCAL
#define SCENARIO_ENGINE_TIMER_UTIL_H_LOCAL

#include <dz1_task.h>
#include "ScenarioEngineTimer.h"

DZ1_CPPLINK Dz1Error ScenarioEngineTimer_set(void *timer, ScenarioEngineTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK Dz1Error ScenarioEngineTimer_update(void *timer, ScenarioEngineTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout);
DZ1_CPPLINK void ScenarioEngineTimer_clr(void *timer, ScenarioEngineTimer *key);

#endif	// SCENARIO_ENGINE_TIMER_UTIL_H_LOCAL
