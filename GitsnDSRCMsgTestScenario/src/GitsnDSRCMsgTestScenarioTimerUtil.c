#include <dz1_task_timer.h>
#include "GitsnDSRCMsgTestScenarioTimerUtil.h"

Dz1Error GitsnDSRCMsgTestScenarioTimer_set(void *timer, GitsnDSRCMsgTestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)GitsnDSRCMsgTestScenarioTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error GitsnDSRCMsgTestScenarioTimer_update(void *timer, GitsnDSRCMsgTestScenarioTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)GitsnDSRCMsgTestScenarioTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void GitsnDSRCMsgTestScenarioTimer_clr(void *timer, GitsnDSRCMsgTestScenarioTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
