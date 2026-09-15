#include <dz1_malloc.h>
#include <dz1_sync.h>

Dz1Sync *_Dz1Sync_new(Dz1Error *err, const char *__file__, int __line__)
{
	Dz1Sync *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((ret = (Dz1Sync *)_Dz1Malloc(sizeof(Dz1Sync), errp, __file__, __line__)) == NULL) ERR_OUT(errp);
	else Dz1Sync_init(ret);
	return ret;
}

void Dz1Sync_del(Dz1Sync *p)
{
	if (!p) return;
	Dz1Sync_destroy(p);
	Dz1Free(p);
}

Dz1Error Dz1Sync_wait(Dz1Sync *p, u64_t *wait_us, Dz1SyncCondFunc func, void *ptr)
{
	bool_t status = FALSE;
	int __code__ = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (wait_us)
	{
		u64_t _wait_us = *wait_us;
		struct timeval __tExpire__;
		struct timespec __expire__;
		Dz1ThreadStatus __oldStatus__ = Dz1Thread_getStatus();

		Dz1Thread_setStatus(Dz1ThreadStatus_waitting);
		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&__oldStatus__);

		__tExpire__ = Dz1TimeVal_get();
		__tExpire__ = Dz1TimeVal_addMicroSec(__tExpire__, _wait_us);
		__expire__ = Dz1TimeVal2Timespec(__tExpire__);

		while((err = func(ptr, &status)).code == 0 && status == FALSE)
		{
 			if ((__code__ = pthread_cond_timedwait(&p->cond, &p->lock, &__expire__)))
			{
				Dz1Error_set(&err, __code__);
				break;
			}
		}
		{
			struct timeval __tNow__ = Dz1TimeVal_get();
			struct timeval __tRemain__ = Dz1TimeVal_sub(__tExpire__, __tNow__);
			(*wait_us) = Dz1TimeVal2MicroSec(__tRemain__);
		}
 		pthread_cleanup_pop(1); /* ((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&__oldStatus__); */
	}
	else
	{
 		Dz1ThreadStatus __oldStatus__ = Dz1Thread_getStatus();
 		Dz1Thread_setStatus(Dz1ThreadStatus_waitting);
 		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&__oldStatus__);

		while((err = func(ptr, &status)).code == 0 && status == FALSE)
		{
 			if ((__code__ = pthread_cond_wait(&p->cond, &p->lock)))
			{
				Dz1Error_set(&err, __code__);
				break;
			}
		}
 		pthread_cleanup_pop(1); /* ((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&__oldStatus__); */
	}
	return err;
}

Dz1Error Dz1Sync_wait2(Dz1Sync *p, u64_t *wait_us)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int __code__ = 0;
	if (wait_us)
	{
		u64_t _wait_us = *wait_us;
		struct timeval __tExpire__, __tAfter__, __tRemain__;
		struct timespec __expire__;

		Dz1ThreadStatus __oldStatus__ = Dz1Thread_getStatus();
		Dz1Thread_setStatus(Dz1ThreadStatus_waitting);
		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&__oldStatus__);

		__tExpire__ = Dz1TimeVal_get();
		__tExpire__ = Dz1TimeVal_addMicroSec(__tExpire__, _wait_us);
		__expire__ = Dz1TimeVal2Timespec(__tExpire__);

		if ((__code__ = pthread_cond_timedwait(&p->cond, &p->lock, &__expire__))) Dz1Error_set(&err, __code__);

		__tAfter__ = Dz1TimeVal_get();
		__tRemain__ = Dz1TimeVal_sub(__tExpire__, __tAfter__);
		(*wait_us) = Dz1TimeVal2MicroSec(__tRemain__);

		pthread_cleanup_pop(1); /* ((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&__oldStatus__); */
		Dz1Error_set(errp, 0);
	}
	else
	{
 		Dz1ThreadStatus __oldStatus__ = Dz1Thread_getStatus();
 		Dz1Thread_setStatus(Dz1ThreadStatus_waitting);
 		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&__oldStatus__);

		if ((__code__ = pthread_cond_wait(&p->cond, &p->lock))) Dz1Error_set(&err, __code__);

		pthread_cleanup_pop(1); /* ((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&__oldStatus__); */
		Dz1Error_set(errp, 0);
	}
	return err;
}
