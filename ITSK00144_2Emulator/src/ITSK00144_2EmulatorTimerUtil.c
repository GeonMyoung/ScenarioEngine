#include <dz1_task_timer.h>
#include "ITSK00144_2EmulatorTimerUtil.h"

Dz1Error ITSK001442EmulatorTimer_set(void *timer, ITSK001442EmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)ITSK001442EmulatorTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error ITSK001442EmulatorTimer_update(void *timer, ITSK001442EmulatorTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)ITSK001442EmulatorTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void ITSK001442EmulatorTimer_clr(void *timer, ITSK001442EmulatorTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
