#include <dz1_malloc.h>
#include <dz1_fifo.h>
#include "dz1_sigmsg_fifo.h"

// Dz1SigMsg in Message FIFO should be abnormal terminated and deleted
static void Dz1SigMsgFifo_sigMsgTermAbnormalAndDel(Dz1SigMsg *msg)
{
	Dz1SigMsg_finalize(&msg, TRUE);
	Dz1SigMsg_del(msg);
}

Dz1SigMsgFifo *Dz1SigMsgFifo_new(size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SigMsgFifo *ret = (Dz1SigMsgFifo *)Dz1Calloc(sizeof(Dz1SigMsgFifo), 1, errp);
	if (ret == NULL) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		pthread_cleanup_push(Dz1SigMsgFifo_delAndSetNull, (void *)&ret);
		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)Dz1SigMsgFifo_sigMsgTermAbnormalAndDel,
									(Dz1DumpFunc)Dz1SigMsg_dump, (int)size, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			Dz1Sync_init(&ret->sync);
			ret->halted = FALSE;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SigMsgFifo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SigMsgFifo_del(Dz1SigMsgFifo *p)
{
	if (!p) return;
	Dz1Sync_destroy(&p->sync);

	if (p->fifo)
	{
		Dz1Fifo_del(p->fifo);
	}
	Dz1Free(p);
}

static Dz1Error _Dz1SigMsgFifo_waitSpace(void *ptr, bool_t *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SigMsgFifo *p = (Dz1SigMsgFifo *)ptr;

	*status = FALSE;

	if (p->halted == TRUE) Dz1Error_set(&err, EINTR);
	else if (!Dz1Fifo_isFull(p->fifo)) *status = TRUE;

	return err;
}

static Dz1Error Dz1SigMsgFifo_waitSpace(Dz1SigMsgFifo *p, u64_t *wait_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1Sync_wait(&p->sync,  wait_us, _Dz1SigMsgFifo_waitSpace, p)).code && err.code != ETIMEDOUT) ERR_OUT(&err);
	return err;
}

static Dz1Error _Dz1SigMsgFifo_waitData(void *ptr, bool_t *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SigMsgFifo *p = (Dz1SigMsgFifo *)ptr;

	*status = FALSE;

	if (p->halted == TRUE) Dz1Error_set(&err, EINTR);
	else if (!Dz1Fifo_isEmpty(p->fifo)) *status = TRUE;

	return err;
}

static Dz1Error Dz1SigMsgFifo_waitData(Dz1SigMsgFifo *p, u64_t *wait_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1Sync_wait(&p->sync, wait_us, _Dz1SigMsgFifo_waitData, p)).code && err.code != ETIMEDOUT) ERR_OUT(&err);
	return err;
}

Dz1Error Dz1SigMsgFifo_push(Dz1SigMsgFifo *p, Dz1SigMsg **msg, u64_t *wait_us)
{
	bool_t halted;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Sync_lock(&p->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&p->sync);

	if ((halted = p->halted) == TRUE) ERR_SET_OUT(&err, EBADF);
	else if ((err = Dz1SigMsgFifo_waitSpace(p, wait_us)).code) { ERR_OUT(&err); }
	else if ((err = Dz1Fifo_push(p->fifo, (*msg))).code) { ERR_OUT(&err); }
	else
	{
		(*msg)->ref++;
		if ((*msg)->ppt == Dz1SigMsgPostProcess_callback) *msg = NULL;
		Dz1Sync_signal(&p->sync);
	}
	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&p->sync);

	return err;
}

Dz1SigMsg *Dz1SigMsgFifo_pop(Dz1SigMsgFifo *p, u64_t *wait_us, Dz1Error *err)
{
	bool_t halted;
	Dz1SigMsg *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Sync_lock(&p->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&p->sync);

	if ((halted = p->halted) == TRUE) ERR_SET_OUT(errp, EBADF);
	else if ((*errp = Dz1SigMsgFifo_waitData(p, wait_us)).code && errp->code != ETIMEDOUT) { ERR_OUT(errp); }
	else if (errp->code == 0 && (ret = (Dz1SigMsg *)Dz1Fifo_pop(p->fifo, errp)) == NULL) { ERR_OUT(errp); }
	else Dz1Sync_signal(&p->sync);

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&p->sync);

	return ret;
}

void Dz1SigMsgFifo_halt(Dz1SigMsgFifo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1SigMsg *msg = NULL;

	Dz1Sync_lock(&p->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&p->sync);

	while(Dz1Fifo_isEmpty(p->fifo) == FALSE)
		if ((msg = (Dz1SigMsg *)Dz1Fifo_pop(p->fifo, &err)) != NULL)
			Dz1SigMsgFifo_sigMsgTermAbnormalAndDel(msg);

	p->halted = TRUE;
	Dz1Sync_signal(&p->sync);

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&p->sync);
}
