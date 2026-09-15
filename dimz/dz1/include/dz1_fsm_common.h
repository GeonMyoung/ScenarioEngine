#ifndef DZ1_FSM_COMMON_H
#define DZ1_FSM_COMMON_H

#include <dz1_error.h>

typedef enum Dz1FsmReturn
{
	Dz1FsmReturn_continue,
	Dz1FsmReturn_terminate,
	Dz1FsmReturn_error
} Dz1FsmReturn;

#define FSM_ERR_OUT(ret, errp)					do { ret = Dz1FsmReturn_error; ERR_OUT(errp); } while(0)
#define FSM_ERR_SET_OUT(ret, errp, val)			do { ret = Dz1FsmReturn_error; ERR_SET_OUT(errp, val); } while(0)

#endif

