#include <dz1_task_timer.h>
#include "Itsk00126v1TestScenarioTimerUtil.h"

Dz1Error Itsk00126V1TestScenarioTimer_set(void *timer, Itsk00126V1TestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)Itsk00126V1TestScenarioTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Itsk00126V1TestScenarioTimer_update(void *timer, Itsk00126V1TestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)Itsk00126V1TestScenarioTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void Itsk00126V1TestScenarioTimer_clr(void *timer, Itsk00126V1TestScenarioTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
