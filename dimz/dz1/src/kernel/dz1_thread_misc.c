#include <dz1_thread.h>

// pthread_setcancelstate :: 0 or EINVAL = state is not PTHREAD_CANCEL_ENABLE or PTHREAD_CANCEL_DISABLE
Dz1Error Dz1Thread_setCancelState(int state, int *oldp)
{
	int code;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((code = pthread_setcancelstate(state, oldp))) Dz1Error_set(&err, code);
	return err;
}

// pthread_setcanceltype :: 0 or EINVAL = type is not PTHREAD_CANCEL_DEFERRED or PTHREAD_CANCEL_IMMEDICATE
Dz1Error Dz1Thread_setCancelType(int type, int *oldp)
{
	int code;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((code = pthread_setcanceltype(type, oldp))) Dz1Error_set(&err, code);
	return err;
}


