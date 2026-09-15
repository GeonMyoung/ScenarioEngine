#ifndef DZ1_TASK_CONCURRENT_TIMER_H_LOCAL
#define DZ1_TASK_CONCURRENT_TIMER_H_LOCAL

#include <dz1_task_timer.h>

DZ1_CPPLINK void				*Dz1TaskTimer_new(Dz1CmpFunc timerDataCmp, Dz1Error *err);
DZ1_CPPLINK void				 Dz1TaskTimer_del(void *ptr);
DZ1_CPPLINK void				 Dz1TaskTimer_delAndSetNull(void *ptr);
DZ1_CPPLINK Dz1TaskProcStatus	 Dz1TaskTimer_timeout(void *user_arg, void *user_resource, void *timer, Dz1Error *err);

#endif
