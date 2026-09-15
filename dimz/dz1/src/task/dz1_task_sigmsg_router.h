#ifndef DZ1_TASK_SIGMSG_ROUTER_H_LOCAL
#define DZ1_TASK_SIGMSG_ROUTER_H_LOCAL

#include <dz1_task.h>
#include "dz1_sigmsg.h"

DZ1_CPPLINK void *Dz1TaskSigRouter_new(Dz1Error *err);
DZ1_CPPLINK void  Dz1TaskSigRouter_del(void *p);
static __inline__ void Dz1TaskSigRouter_delAndSetNull(void *ptr)
{
	void **p = (void **)ptr;
	Dz1TaskSigRouter_del(*p); *p = NULL;
}

DZ1_CPPLINK Dz1Error			 Dz1TaskSigRouter_reg(void *ptr, u32_t type, u32_t mask, Dz1TaskSigMsgProcFunc func);
DZ1_CPPLINK void				 Dz1TaskSigRouter_dereg(void *ptr, u32_t type, u32_t mask);
DZ1_CPPLINK void				 Dz1TaskSigRouter_dump(void *p, int tab);
DZ1_CPPLINK Dz1TaskProcStatus	 Dz1TaskSigRouter_proc(void *ptr, void *user_arg, void *user_resource, void *timer, void **sig_msg, Dz1Error *err);

#endif
