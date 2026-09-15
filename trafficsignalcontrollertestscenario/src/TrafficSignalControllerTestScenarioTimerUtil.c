#include <dz1_task_timer.h>
#include "TrafficSignalControllerTestScenarioTimerUtil.h"

Dz1Error TrafficSignalControllerTestScenarioTimer_set(void *timer, TrafficSignalControllerTestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)TrafficSignalControllerTestScenarioTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error TrafficSignalControllerTestScenarioTimer_update(void *timer, TrafficSignalControllerTestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)TrafficSignalControllerTestScenarioTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void TrafficSignalControllerTestScenarioTimer_clr(void *timer, TrafficSignalControllerTestScenarioTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
