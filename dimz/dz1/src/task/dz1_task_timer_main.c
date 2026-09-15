#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include "dz1_task_timer.h"

static int _timerCmp(void *a, void *b)
{
	u32_t A = *(u32_t *)a;
	u32_t B = *(u32_t *)b;

//	Dz1Thread_printf("_timerCmp() : A = %d(%p), B = %d(%p)\n", A, a, B, b);

	return (int)(A - B);
}

static __inline__ void _del(void *p) { if (p) Dz1Free(p); }

static Dz1TaskProcStatus timeout(void *arg, void *resource, void *timer, void **timer_data, Dz1Error *err)
{
	void *_timer_data = *timer_data;
	u32_t timer_id = *(u32_t *)_timer_data;
	Dz1Thread_printf("Timedout:%d\n", timer_id);
	return Dz1TaskProcStatus_processed;
}

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	void *timer = Dz1TaskTimer_new(_timerCmp, &err);
	if (timer == NULL) ERR_OUT(&err);
	else
	{
#if 0
		int _a = 1, _b = 2, _c = 3, _d = 4;
		int *a = &_a, *b = &_b, *c = &_c, *d = &_d;
#else
		int a = 1, b = 2, c = 3, d = 4;
#endif

		pthread_cleanup_push(Dz1TaskTimer_del, timer);

		Dz1Thread_printf("Initialized\n");
#if 0
		if ((err = Dz1TaskTimer_reg(timer, 1000000, (void **)&a, NULL, timeout, TRUE)).code) ERR_OUT(&err);
		else if ((err = Dz1TaskTimer_reg(timer, 2000000, (void **)&b, NULL, timeout, TRUE)).code) ERR_OUT(&err);
		else if ((err = Dz1TaskTimer_reg(timer, 4000000, (void **)&c, NULL, timeout, TRUE)).code) ERR_OUT(&err);
		else if ((err = Dz1TaskTimer_reg(timer, 2500000, (void **)&d, NULL, timeout, TRUE)).code) ERR_OUT(&err);
#else
		if ((err = Dz1TaskTimer_regStatic(timer, 1000000, (void *)&a, timeout, TRUE)).code) ERR_OUT(&err);
		else if ((err = Dz1TaskTimer_regStatic(timer, 2000000, (void *)&b, timeout, TRUE)).code) ERR_OUT(&err);
		else if ((err = Dz1TaskTimer_regStatic(timer, 4000000, (void *)&c, timeout, TRUE)).code) ERR_OUT(&err);
		else if ((err = Dz1TaskTimer_regStatic(timer, 2500000, (void *)&d, timeout, TRUE)).code) ERR_OUT(&err);
#endif
		else
		{
			u64_t *delay, _delay, val = 3;
			Dz1TaskProcStatus status;
			Dz1TaskTimer_dereg(timer, &val);
			Dz1Thread_printf("Registered %p, %p, %p, %p\n", a, b, c, d);
			Dz1TaskTimer_dump(timer, 1);
			while((delay = Dz1TaskTimer_getDuration(timer, &_delay)))
			{
				Dz1Thread_printf("Sleep : %.3fms\n", (double)_delay / 1000.0);
				usleep(_delay);
				if ((status = Dz1TaskTimer_timeout(NULL, NULL, timer, &err)) == Dz1TaskProcStatus_error) ERR_OUT(&err);
				else Dz1Thread_printf("Status = %d\n", status);
			}
		}
		pthread_cleanup_pop(1); // (Dz1TaskTimer_del, timer);
	}
	return err.code;
}
