#include <dz1_task_timer.h>
#include "Dz1TcpSerialClientTimerUtil.h"

Dz1Error Dz1TcpSerialClientTimer_set(void *timer, Dz1TcpSerialClientTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)Dz1TcpSerialClientTimer_del, timeout, FALSE)).code) ERR_OUT(&err);
	return err;
}

Dz1Error Dz1TcpSerialClientTimer_update(void *timer, Dz1TcpSerialClientTimer **tmr, u64_t dur, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1TaskTimer_reg(timer, dur, (void **)tmr, (Dz1DelFunc)Dz1TcpSerialClientTimer_del, timeout, TRUE)).code) ERR_OUT(&err);
	return err;
}

void Dz1TcpSerialClientTimer_clr(void *timer, Dz1TcpSerialClientTimer *key)
{
	Dz1TaskTimer_dereg(timer, (void *)key);
}
