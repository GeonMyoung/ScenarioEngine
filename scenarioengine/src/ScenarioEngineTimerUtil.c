#include <dz1_task_timer.h>
#include "ScenarioEngineTimerUtil.h"

Dz1Error ScenarioEngineTimer_set(void *timer, ScenarioEngineTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)ScenarioEngineTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error ScenarioEngineTimer_update(void *timer, ScenarioEngineTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)ScenarioEngineTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void ScenarioEngineTimer_clr(void *timer, ScenarioEngineTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
