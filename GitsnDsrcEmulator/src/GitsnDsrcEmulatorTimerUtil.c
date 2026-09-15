#include <dz1_task_timer.h>
#include "GitsnDsrcEmulatorTimerUtil.h"

Dz1Error GitsnDsrcEmulatorTimer_set(void *timer, GitsnDsrcEmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)GitsnDsrcEmulatorTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error GitsnDsrcEmulatorTimer_update(void *timer, GitsnDsrcEmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)GitsnDsrcEmulatorTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void GitsnDsrcEmulatorTimer_clr(void *timer, GitsnDsrcEmulatorTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
