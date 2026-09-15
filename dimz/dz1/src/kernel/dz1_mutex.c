#include <dz1_malloc.h>

#include <dz1_thread.h>
#include <dz1_mutex.h>

Dz1Error Dz1Mutex_init(Dz1Mutex *m, pthread_mutexattr_t *attr)
{
	int code = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((code = pthread_mutex_init(m, attr)) != 0) Dz1Error_set(&err, code);
	return err;
}

Dz1Mutex *Dz1Mutex_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Mutex *ret = (Dz1Mutex *)Dz1Calloc(sizeof(Dz1Mutex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);

		if ((*errp = Dz1Mutex_init(ret, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1Mutex_destroy(pthread_mutex_t *m)
{
	int code = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((code = pthread_mutex_destroy(m)) != 0) Dz1Error_set(&err, code);
	return err;
}
void Dz1Mutex_del(Dz1Mutex *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (p == NULL) return;
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)p);

		if ((*errp = Dz1Mutex_destroy(p)).code) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)p);
	}
}


Dz1Error Dz1Mutex_lock(pthread_mutex_t *m)
{
	int code = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ThreadStatus old = Dz1Thread_getStatus();
	Dz1Thread_setStatus(Dz1ThreadStatus_locking);
	pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&old);

	if ((code = pthread_mutex_lock(m)) != 0) Dz1Error_set(&err, code);

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&old);

	return err;
}

Dz1Error Dz1Mutex_trylock(Dz1Mutex *m)
{
	int code = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ThreadStatus old = Dz1Thread_getStatus();
	Dz1Thread_setStatus(Dz1ThreadStatus_locking);
	pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&old);

	if ((code = pthread_mutex_trylock(m)) != 0) Dz1Error_set(&err, code);

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&old);

	return err;
}

Dz1Error Dz1Mutex_unlock(Dz1Mutex *m)
{
	int code = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((code = pthread_mutex_unlock(m)) != 0) Dz1Error_set(&err, code);
	return err;
}
