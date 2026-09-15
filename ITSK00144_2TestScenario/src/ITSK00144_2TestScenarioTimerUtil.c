#include <dz1_task_timer.h>
#include "ITSK00144_2TestScenarioTimerUtil.h"

Dz1Error ITSK001442TestScenarioTimer_set(void *timer, ITSK001442TestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)ITSK001442TestScenarioTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error ITSK001442TestScenarioTimer_update(void *timer, ITSK001442TestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)ITSK001442TestScenarioTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void ITSK001442TestScenarioTimer_clr(void *timer, ITSK001442TestScenarioTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
