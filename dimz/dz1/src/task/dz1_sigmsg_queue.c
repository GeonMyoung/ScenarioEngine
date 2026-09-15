#include <dz1_bits.h>
#include <dz1_sync.h>
#include <dz1_fifo.h>
#include <dz1_malloc.h>

#include "dz1_sigmsg_fifo.h"
#include "dz1_sigmsg_queue.h"

#define DZ1_SIGMSG_QUEUE_POOL_SIZE				DZ1_THREAD_MAX

#define DZ1_SIGMSG_QUEUE_BITS_ARRAY_SIZE		DZ1_BITS_UNIT_SIZE_ARRAY(DZ1_SIGMSG_QUEUE_POOL_SIZE)

typedef struct Dz1SigMsgQueuePool
{
	Dz1Sync			 sync;
	DZ1_BITS_UNIT	 alloc[DZ1_SIGMSG_QUEUE_BITS_ARRAY_SIZE];
	DZ1_BITS_UNIT	 inuse[DZ1_SIGMSG_QUEUE_BITS_ARRAY_SIZE];
	DZ1_BITS_UNIT	 pending[DZ1_SIGMSG_QUEUE_BITS_ARRAY_SIZE];
	Dz1SigMsgFifo	*fifo[DZ1_SIGMSG_QUEUE_POOL_SIZE];
} Dz1SigMsgQueuePool;

// for Not Allocated Index, Set Alloc And Inuse Bit
static u32_t Dz1SigMsgQueuePool_alloc(Dz1SigMsgQueuePool *p, Dz1Error *err)
{
	unsigned int i;
	for (i = 0; i < DZ1_SIGMSG_QUEUE_BITS_ARRAY_SIZE; i++)
	{
		if (!Dz1BitsUnit_isAllSet(p->alloc[i]))
		{
			unsigned int j;
			for (j = 0; j < DZ1_BITS_UNIT_SIZE_BIT; j++)
			{
				if (!Dz1BitsUnit_isSet(p->alloc[i], j))
				{
					p->alloc[i] = Dz1BitsUnit_set(p->alloc[i], j);
					p->inuse[i] = Dz1BitsUnit_set(p->inuse[i], j);
					return (i * DZ1_BITS_UNIT_SIZE_BIT) + j;
				}
			}
		}
	}
	return -1;
}

static void Dz1SigMsgQueuePool_free(Dz1SigMsgQueuePool *p, u32_t idx) { Dz1Bits_clr(p->alloc, idx); Dz1Bits_clr(p->inuse, idx); }

static bool_t Dz1SigMsgQueuePool_isInuse(Dz1SigMsgQueuePool *p, u32_t idx) { if (Dz1Bits_isSet(p->inuse, idx)) return TRUE; return FALSE; }
static void Dz1SigMsgQueuePool_setInuse(Dz1SigMsgQueuePool *p, u32_t idx) { Dz1Bits_set(p->inuse, idx); }
static void Dz1SigMsgQueuePool_setIdle(Dz1SigMsgQueuePool *p, u32_t idx) { Dz1Bits_clr(p->inuse, idx); }

static bool_t Dz1SigMsgQueuePool_isPending(Dz1SigMsgQueuePool *p, u32_t idx) { if (Dz1Bits_isSet(p->pending, idx)) return TRUE; return FALSE; }
static void Dz1SigMsgQueuePool_pendingStart(Dz1SigMsgQueuePool *p, u32_t idx) { Dz1Bits_set(p->pending, idx); }
static void Dz1SigMsgQueuePool_pendingStop(Dz1SigMsgQueuePool *p, u32_t idx) { Dz1Bits_clr(p->pending, idx); }

static Dz1SigMsgQueuePool pool =
{
	DZ1_SYNC_INITIALIZER,
	{ 0, },
	{ 0, },
	{ 0, },
	{ NULL, }
};

typedef struct Dz1SigMsgQueuePoolWaitArg
{
	Dz1SigMsgQueuePool *p;
	u32_t idx;
} Dz1SigMsgQueuePoolWaitArg;

static Dz1Error _Dz1SigMsgQueuePool_waitIdle(void *ptr, bool_t *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SigMsgQueuePoolWaitArg *arg = (Dz1SigMsgQueuePoolWaitArg *)ptr;

	if (Dz1SigMsgQueuePool_isInuse(arg->p, arg->idx)) *status = TRUE; else *status = FALSE;

	return err;
}

static Dz1Error Dz1SigMsgQueuePool_waitIdle(Dz1SigMsgQueuePool *p, u32_t idx, u64_t *wait_us)
{	// inuse bit가 0이 되길 기다리기
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SigMsgQueuePoolWaitArg arg;

	arg.p = p;
	arg.idx = idx;

	if ((err = Dz1Sync_wait(&pool.sync, wait_us, _Dz1SigMsgQueuePool_waitIdle, &arg)).code) { ERR_OUT(&err); }
	else if (!Dz1Bits_isSet(p->alloc, idx)) ERR_SET_OUT(&err, EINTR);
	return err;
}

static void *Dz1SigMsgQueue_get(u32_t idx, u64_t *wait_us, Dz1Error *errp)
{
	void *ret = NULL;

	Dz1Sync_lock(&pool.sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&pool.sync);

	if (idx >= DZ1_SIGMSG_QUEUE_POOL_SIZE)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! invalid task idx = %u(0x%08X)\n", idx, idx);
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (!Dz1Bits_isSet(pool.alloc, idx)) ERR_SET_OUT(errp, ESRCH);
	else if ((*errp = Dz1SigMsgQueuePool_waitIdle(&pool, idx, wait_us)).code) { ERR_OUT(errp); }
	else
	{
		Dz1SigMsgQueuePool_setInuse(&pool, idx);
		if ((ret = pool.fifo[idx]) == NULL)
		{
			Dz1SigMsgQueuePool_setIdle(&pool, idx);
			ERR_SET_OUT(errp, ESRCH);
		}
		else Dz1Error_set(errp, 0);
	}

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&pool.sync);

	return ret;
}

static void Dz1SigMsgQueue_put(u32_t idx)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Sync_lock(&pool.sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&pool.sync);

	if (idx >= DZ1_SIGMSG_QUEUE_POOL_SIZE) ERR_SET_OUT(&err, EINVAL);
	else if (!Dz1Bits_isSet(pool.alloc, idx)) ERR_SET_OUT(&err, ESRCH);
	else
	{
		Dz1SigMsgQueuePool_setIdle(&pool, idx);
		Dz1Sync_signal(&pool.sync);
	}

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&pool.sync);
}

static void Dz1SigMsgQueue_getCancel(void *ptr)
{
	u32_t idx = *(u32_t *)ptr;
	Dz1SigMsgQueue_put(idx);
}

static Dz1Error _Dz1SigMsgQueuePool_waitPendingIdle(void *ptr, bool_t *status)
{	// pending flag가 0이되길 기다리기
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SigMsgQueuePoolWaitArg *arg = (Dz1SigMsgQueuePoolWaitArg *)ptr;

	if (!Dz1SigMsgQueuePool_isPending(arg->p, arg->idx)) *status = TRUE; else *status = FALSE;

	return err;
}

static Dz1Error Dz1SigMsgQueuePool_waitPendingIdle(Dz1SigMsgQueuePool *p, u32_t idx, u64_t *wait_us)
{	// pending flag가 0이되길 기다리기
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SigMsgQueuePoolWaitArg arg;

	arg.p = p;
	arg.idx = idx;

	if ((err = Dz1Sync_wait(&pool.sync, wait_us, _Dz1SigMsgQueuePool_waitPendingIdle, &arg)).code) { ERR_OUT(&err); }
	else if (!Dz1Bits_isSet(p->alloc, idx)) ERR_SET_OUT(&err, EINTR);
	return err;
}


static void *Dz1SigMsgQueue_pendingStart(u32_t idx, u64_t *wait_us, Dz1Error *errp)
{	// pending flag가 0이되길 기다렸다가 1로 만듬
	void *ret = NULL;

	if (idx >= DZ1_SIGMSG_QUEUE_POOL_SIZE) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1Sync_lock(&pool.sync);
		pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&pool.sync);

		if (!Dz1Bits_isSet(pool.alloc, idx)) ERR_SET_OUT(errp, ESRCH);
		else if ((*errp = Dz1SigMsgQueuePool_waitPendingIdle(&pool, idx, wait_us)).code) { ERR_OUT(errp); }
		else
		{
			Dz1SigMsgQueuePool_pendingStart(&pool, idx);
			ret = pool.fifo[idx];
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&pool.sync);
	}

	return ret;
}

static void Dz1SigMsgQueue_pendingEnd(u32_t idx)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (idx >= DZ1_SIGMSG_QUEUE_POOL_SIZE) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1Sync_lock(&pool.sync);
		pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&pool.sync);

		if (!Dz1Bits_isSet(pool.alloc, idx)) ERR_SET_OUT(&err, ESRCH);
		else
		{
			Dz1SigMsgQueuePool_pendingStop(&pool, idx);
			Dz1Sync_signal(&pool.sync);
		}

		pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&pool.sync);
	}
}

static void Dz1SigMsgQueue_pendingStartCancel(void *ptr)
{
	u32_t idx = *(u32_t *)ptr;
	Dz1SigMsgQueue_pendingEnd(idx);
}

/*
Dz1Error Dz1SigMsgQueue_postSig(u32_t dst, u32_t src, u32_t type, void **sgptr)
{
	u32_t idx = dst & 0xFFFF;
	
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	void *fifo = NULL;
	Dz1SigMsg *sg = (Dz1SigMsg *)(*sgptr);

	pthread_cleanup_push(Dz1SigMsg_delAndSetNull, (void *)sgptr);
	
	sg->dst = dst;
	sg->src = src;
	sg->type = type;

	if ((fifo = Dz1SigMsgQueue_get(idx, NULL, &err)) == NULL) { ERR_OUT(&err); }
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);
		
		// sg will be NULL in Dz1SigMsgFifo_push function if success
		if ((err = Dz1SigMsgFifo_push(fifo, (Dz1SigMsg **)sgptr, NULL)).code) ERR_OUT(&err);
		
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);
	}
	pthread_cleanup_pop(1); // ((Dz1SigMsg_delAndSetNull, (void *)sgptr);
	return err;
}
*/

bool_t Dz1SigMsgQueue_toss(u32_t dst, Dz1SigMsg **_msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	void *fifo = NULL;
	u32_t idx = dst & 0xFFFF;

	if ((fifo = Dz1SigMsgQueue_get(idx, NULL, errp)) == NULL) { ERR_OUT(errp); }				// inuse bit set
	else
	{
		Dz1SigMsg *msg = *_msg;
		pthread_cleanup_push((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);

		//pthread_cleanup_push(Dz1SigMsg_del, msg);						// origin code
		pthread_cleanup_push(Dz1SigMsg_delAndSetNull, (void *)&msg);	// modified by gm 20231019

		if ((*errp = Dz1SigMsgFifo_push((Dz1SigMsgFifo *)fifo, _msg, NULL)).code) ERR_OUT(errp);	// ref is increased
		else
		{
			*_msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1SigMsg_del, msg);											// decrease ref

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);
	}

	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1SigMsgQueue_post(u32_t dst, u32_t src, u32_t type,
							 void **msg, Dz1DelFunc del, Dz1DumpFunc dump,
							 Dz1Error *initialStatus, Dz1TaskSigMsgCallbackFunc callback, void *param)
{
	u32_t idx = dst & 0xFFFF;

	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1SigMsg *sg = Dz1SigMsg_new(dst, src, type, msg ? *msg : NULL, del, dump, initialStatus, &err);
	if (sg == NULL) { ERR_OUT(&err); }
	else
	{
		void *fifo = NULL;

		// printf("Dz1SigMsgQueue_post() : *msg = %p\n", msg ? *msg : NULL); fflush(stdout);
		if (del && msg) *msg = NULL;

		pthread_cleanup_push(Dz1SigMsg_delAndSetNull, (void *)&sg);

		sg->ppt = Dz1SigMsgPostProcess_callback;
		sg->x.cb.callback = callback;
		sg->x.cb.param = param;
		
		if ((fifo = Dz1SigMsgQueue_get(idx, NULL, &err)) == NULL) { ERR_OUT(&err); }				// inuse bit set
		else
		{
			pthread_cleanup_push((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);

			// sg will be NULL in Dz1SigMsgFifo_push function if success
			if ((err = Dz1SigMsgFifo_push((Dz1SigMsgFifo *)fifo, &sg, NULL)).code) ERR_OUT(&err);

			pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);
		}
		pthread_cleanup_pop(1); // ((Dz1SigMsg_delAndSetNull, (void *)&sg);
	}
	return err;
}

Dz1Error Dz1SigMsgQueue_call(u32_t dst, u32_t src, u32_t type, void *msg, Dz1DumpFunc dump, Dz1Error *initialStatus, u64_t *wait_us)
{
	u32_t idx = dst & 0xFFFF;

	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1SigMsg *sg = NULL;


	if ((sg = Dz1SigMsg_new(dst, src, type, msg, NULL, dump, initialStatus, &err)) == NULL) ERR_OUT(&err);
	else
	{
		void *fifo = NULL;

		pthread_cleanup_push((Dz1DelFunc)Dz1SigMsg_del, (void *)sg);

		sg->ref++;
		sg->ppt = Dz1SigMsgPostProcess_call;
		Dz1SigMsgSync_init(&sg->x.sync);

		Dz1SigMsgSync_lock(&sg->x.sync);
		pthread_cleanup_push(Dz1SigMsgSync_lockCancel, (void *)&sg->x.sync);

		if ((fifo = Dz1SigMsgQueue_get(idx, wait_us, &err)) == NULL) { ERR_OUT(&err); }
		else
		{
			pthread_cleanup_push((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);

			if ((err = Dz1SigMsgFifo_push((Dz1SigMsgFifo *)fifo, &sg, wait_us)).code) ERR_OUT(&err);

			pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);

			if (err.code == 0)
			{
				if ((err = Dz1SigMsgSync_wait(&sg->x.sync, wait_us)).code)
				{
					ERR_OUT(&err);
					if (err.code == ETIMEDOUT)
					{
						sg->type = DZ1_TASK_COMMAND_NONE;
						sg->msg = NULL;
					}
				}
				else if (sg->x.sync.status == Dz1SigMsgStatus_aborted) ERR_SET_OUT(&err, EINTR);
				else if (sg->x.sync.status != Dz1SigMsgStatus_processed) ERR_SET_OUT(&err, EFAULT);
				else { memcpy(&err, &sg->err, sizeof(Dz1Error)); }
			}
		}
		pthread_cleanup_pop(1); // (Dz1SigMsgSync_lockCancel, (void *)&sg->x.sync);
		pthread_cleanup_pop(1); // ((Dz1SigMsg_del, (void *)sg);
	}
	return err;
}

Dz1SigMsg *Dz1SigMsgQueue_pend(u32_t dst, u64_t *wait_us, Dz1Error *err)
{
	Dz1SigMsg *ret = NULL;

	u32_t idx = dst & 0xFFFF;

	DZ1_ERROR_SAFE_DECLARE(errp, err);

	void *fifo = NULL;

	if ((fifo = Dz1SigMsgQueue_pendingStart(idx, wait_us, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SigMsgQueue_pendingStartCancel, (void *)&idx);

		if ((ret = Dz1SigMsgFifo_pop((Dz1SigMsgFifo *)fifo, wait_us, errp)) == NULL && errp->code != ETIMEDOUT) ERR_OUT(errp);	// Data POP

		pthread_cleanup_pop(1); // (Dz1SigMsgQueue_pendingStartCancel, (void *)&idx);
	}

	return ret;
}

static void Dz1SigMsgQueue_free(void *ptr)
{
	u32_t idx = *(u32_t *)ptr;
	Dz1SigMsgQueuePool_free(&pool, idx);
}

static u16_t spin = 0;
u32_t Dz1SigMsgQueue_new(u32_t size, Dz1Error *err)
{
	u32_t idx = -1, ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Sync_lock(&pool.sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&pool.sync);

	if ((idx = Dz1SigMsgQueuePool_alloc(&pool, errp)) == (u32_t)-1) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SigMsgQueue_free, (void *)&idx);

		if ((pool.fifo[idx] = Dz1SigMsgFifo_new(size, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			Dz1SigMsgQueuePool_setIdle(&pool, idx);
			ret = (u32_t)spin++ << 16 | idx;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SigMsgQueue_del, (void *)&idx);
	}
	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&pool.sync);
	
	return ret;
}

void Dz1SigMsgQueue_del(u32_t dst)
{
	u32_t idx = dst & 0xFFFF;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (idx >= DZ1_SIGMSG_QUEUE_POOL_SIZE) ERR_SET_OUT(&err, EINVAL);
	else
	{
		void *fifo = NULL;

		if ((fifo = Dz1SigMsgQueue_get(idx, NULL, &err)) == NULL) ERR_OUT(&err);				// inuse bit 설정
		else
		{	// allocated, inuse 
			pthread_cleanup_push((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx);

			if (Dz1SigMsgQueue_pendingStart(idx, NULL, &err) == NULL) { ERR_OUT(&err); }		// pending bit 설정
			else
			{
				Dz1SigMsgFifo *fifo = NULL;
				pthread_cleanup_push(Dz1SigMsgQueue_pendingStartCancel, (void *)&idx);

				Dz1SigMsgQueuePool_free(&pool, idx);											// alloc bit 해제
				fifo = pool.fifo[idx];

				Dz1Sync_lock(&fifo->sync);
				pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&fifo->sync);
				fifo->halted = TRUE;
				pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&fifo->sync);

				Dz1SigMsgFifo_del(pool.fifo[idx]);
				pool.fifo[idx] = NULL;


				pthread_cleanup_pop(1); // (Dz1SigMsgQueue_pendingStartCancel, (void *)&idx);	// penging bit 해제
			}
			pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1SigMsgQueue_getCancel, (void *)&idx); // inuse bit 해제
		}
	}
}

void Dz1SigMsgQueue_halt(u32_t dst)
{
	u32_t idx = dst & 0xFFFF;

	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	void *fifo = NULL;

	if ((fifo = Dz1SigMsgQueue_pendingStart(idx, NULL, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SigMsgQueue_pendingStartCancel, (void *)&idx);

		Dz1SigMsgFifo_halt((Dz1SigMsgFifo *)fifo);

		pthread_cleanup_pop(1); // (Dz1SigMsgQueue_pendingStartCancel, (void *)&idx);
	}

	return;
}
