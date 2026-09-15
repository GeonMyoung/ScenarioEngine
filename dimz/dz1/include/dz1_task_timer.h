#ifndef DZ1_TASK_CONCURRENT_TIMER_H
#define DZ1_TASK_CONCURRENT_TIMER_H

#include <dz1_error.h>
#include <dz1_task.h>

/*
* u64_t duration_us maximum
*		584942 year 152 days 8 hour 2 min 49 sec
*			  213503982 days 8 hour 2 min 49 sec
*					5124095576 hour 2 min 49 sec
*						 307445734562 min 49 sec
*							  18446744073709 sec
*/

/*
* Dz1TaskTimer_reg : Register or Update TASK Timer
*	timer			: task timer ptr
*	duration_us		: timeout time in micro second
*	timer_data		: address of timer data ptr
*	timer_data_del	: delete timer_data function
*	timeout			: timeout function when timer is expired
*	overwrite		: TRUE = update duration & timer_data if exist, FALSE = error return if exist
* 
*	remark - if "timer_data_del" is not NULL, "timer_data" ptr set to NULL (*timer_data = NULL is performed)
*/
DZ1_CPPLINK DZ1_DLLPORT Dz1Error			 Dz1TaskTimer_reg(void *timer, u64_t duration_us,
															  void **timer_data, Dz1DelFunc timer_data_del,
															  Dz1TaskTimeoutProcFunc timeout, bool_t overwrite);

/*
* Dz1TaskTimer_regStatic : Register or Update TASK Timer
*	timer			: task timer ptr
*	duration_us		: timeout time in micro second
*	timer_data		: timer data ptr
*	timeout			: timeout function when timer is expired
*	overwrite		: TRUE = update duration & timer_data if exist, FALSE = error return if exist
* 
*	remark - "timer_data" should be valid until timed-out or unregistered.
*/
static __inline__ Dz1Error			 		Dz1TaskTimer_regStatic(void *ptr, u64_t duration_us, void *timer_data,
																   Dz1TaskTimeoutProcFunc timeout, bool_t overwrite)
{
	void **_timer_data = &timer_data;
	return Dz1TaskTimer_reg(ptr, duration_us, _timer_data, NULL, timeout, overwrite);
}

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1TaskTimer_dereg(void *ptr, void *timer_key);
DZ1_CPPLINK DZ1_DLLPORT void				*Dz1TaskTimer_extract(void *ptr, void *timer_key);
DZ1_CPPLINK	DZ1_DLLPORT void				*Dz1TaskTimer_find(void *ptr, void *timer_key);
DZ1_CPPLINK DZ1_DLLPORT u64_t				*Dz1TaskTimer_getDuration(void *ptr, u64_t *dst_us);

DZ1_CPPLINK DZ1_DLLPORT void				 Dz1TaskTimer_dump(void *timer, int tab);
#endif
