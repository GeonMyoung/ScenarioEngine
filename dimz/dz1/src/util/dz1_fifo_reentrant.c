#include <dz1_malloc.h>
#include <dz1_sync.h>

#include <dz1_fifo.h>
#include <dz1_fifo_reentrant.h>

typedef struct Dz1FifoReentrant
{
	void *fifo;
	Dz1Sync sync;
} Dz1FifoReentrant;

void *Dz1FifoReentrant_new(Dz1DelFunc del, Dz1DumpFunc dump, int size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1FifoReentrant *ret = (Dz1FifoReentrant *)Dz1Calloc(sizeof(Dz1FifoReentrant), 1, errp);
	if (ret)
	{
		pthread_cleanup_push(Dz1FifoReentrant_delAndSetNull, (void *)&ret);
		if ((ret->fifo = Dz1Fifo_new(del, dump, size, errp)))
		{
			Dz1Sync_init(&ret->sync);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1FifoReentrant_delAndSetNull, (void *)&ret);
	}
	return (void *)ret;
}

void Dz1FifoReentrant_del(void *ptr)
{
	Dz1FifoReentrant *p = (Dz1FifoReentrant *)ptr;
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	Dz1Sync_destroy(&p->sync);
	Dz1Free(p);
}

static Dz1Error _Dz1FifoReentrant_push(void *ptr, bool_t *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1FifoReentrant *p = (Dz1FifoReentrant *)ptr;

	if (!Dz1Fifo_isFull(p->fifo)) *status = TRUE; else *status = FALSE;

	return err;
}

Dz1Error Dz1FifoReentrant_push(void *ptr, void *data, s64_t wait_usec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1FifoReentrant *p = (Dz1FifoReentrant *)ptr;
	if (!p) Dz1Error_set(&err, EINVAL);
	else
	{
		Dz1Sync_lock(&p->sync);
		pthread_cleanup_push(Dz1Sync_cancel, (void *)&p->sync);

		if (wait_usec == 0) err = Dz1Fifo_push(p->fifo, data);
		else if (wait_usec < 0)
		{
#if 0
			if ((err = Dz1Sync_wait(&p->sync, !Dz1Fifo_isFull(p->fifo), &err)).code == 0)
#else
			if ((err = Dz1Sync_wait(&p->sync, NULL, _Dz1FifoReentrant_push, p)).code == 0)
#endif
				err = Dz1Fifo_push(p->fifo, data);
		}
		else
		{
#if 0
			if ((err = Dz1Sync_timedWait(&p->sync, !Dz1Fifo_isFull(p->fifo), wait_usec, &err)).code == 0)
#else
			if ((err = Dz1Sync_wait(&p->sync, (u64_t *)&wait_usec, _Dz1FifoReentrant_push, p)).code == 0)
#endif
				err = Dz1Fifo_push(p->fifo, data);
		}

		pthread_cleanup_pop(1); // (Dz1Sync_cancel, (void *)&p->sync);
	}
	return err;
}

static Dz1Error _Dz1FifoReentrant_pop(void *ptr, bool_t *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1FifoReentrant *p = (Dz1FifoReentrant *)ptr;

	if (!Dz1Fifo_isEmpty(p)) *status = TRUE; else *status = FALSE;

	return err;
}

void *Dz1FifoReentrant_pop(void *ptr, s64_t wait_us, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1FifoReentrant *p = (Dz1FifoReentrant *)ptr;

	if (!p) Dz1Error_set(errp, EINVAL);
	else
	{
		Dz1Sync_lock(&p->sync);
		pthread_cleanup_push(Dz1Sync_cancel, (void *)&p->sync);

		if (wait_us == 0) ret = Dz1Fifo_pop(p->fifo, errp);
		else if (wait_us < 0)
		{
#if 0
			if ((*errp = Dz1Sync_wait(&p->sync, !Dz1Fifo_isEmpty(p->fifo), errp)).code == 0)
#else
			if ((*errp = Dz1Sync_wait(&p->sync, NULL, _Dz1FifoReentrant_pop, p)).code == 0)
#endif
				ret = Dz1Fifo_pop(p->fifo, errp);
		}
		else
		{
#if 0
			if ((*errp = Dz1Sync_timedWait(&p->sync, !Dz1Fifo_isEmpty(p->fifo), wait_us, errp)).code == 0)
#else
			if ((*errp = Dz1Sync_wait(&p->sync, (u64_t *)&wait_us, _Dz1FifoReentrant_pop, p)).code == 0)
#endif
				ret = Dz1Fifo_pop(p->fifo, errp);
		}

		pthread_cleanup_pop(1); // (Dz1Sync_cancel, (void *)&p->sync);
	}
	return ret;
}

void Dz1FifoReentrant_dump(void *ptr, int tab)
{
	Dz1FifoReentrant *p = (Dz1FifoReentrant *)ptr;
	if (!p) return;
	else
	{
		Dz1Sync_lock(&p->sync);
		pthread_cleanup_push(Dz1Sync_cancel, (void *)&p->sync);

		Dz1Fifo_dump(p->fifo, tab);

		pthread_cleanup_pop(1); // (Dz1Sync_cancel, (void *)&p->sync);
	}
}
