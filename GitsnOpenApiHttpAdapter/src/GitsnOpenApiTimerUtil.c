#include <dz1_task_timer.h>
#include "GitsnOpenApiTimerUtil.h"

Dz1Error GitsnOpenApiTimer_set(void *timer, GitsnOpenApiTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)GitsnOpenApiTimer_del, timeout, FALSE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error GitsnOpenApiTimer_update(void *timer, GitsnOpenApiTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)GitsnOpenApiTimer_del, timeout, TRUE)).code) ERR_OUT(errp);
	return err;
}

void GitsnOpenApiTimer_clr(void *timer, GitsnOpenApiTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
