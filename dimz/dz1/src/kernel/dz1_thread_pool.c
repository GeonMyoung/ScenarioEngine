#include "dz1_thread_pool.h"

static Dz1ThreadPool pool =
{
	PTHREAD_MUTEX_INITIALIZER,			// lock
	{ NULL, NULL },						// barrier
	{ { NULL, } },						// hash
	{ 0, { 0, }, { 0, } },				// index
	{ NULL, }							// table
};
Dz1ThreadPool *thread_pool = &pool;

///////////////////////////////////////////////////////////////////////////////
// DZ1 Thread Pool Bits Index
///////////////////////////////////////////////////////////////////////////////
static u32_t Dz1ThreadPoolIndex_get(Dz1ThreadPoolIndex *index)
{
	u32_t i, idx;
	for (i = 0, idx = 0; i < DZ1_THREAD_INDEX_SIZE && idx < DZ1_THREAD_MAX; i++, idx += DZ1_BITS_UNIT_SIZE_BIT)
	{
		if (!Dz1BitsUnit_isAllSet(index->alloc[i] | index->active[i]))
		{	// Not Allocated, Not Activated
			u32_t j, bitNo;
			for (j = 0, bitNo = idx; j < DZ1_BITS_UNIT_SIZE_BIT && bitNo < DZ1_THREAD_MAX; j++, bitNo++)
			{
				if (!Dz1BitsUnit_isSet(index->alloc[i] | index->active[i], bitNo))
				{
					index->alloc[i] = Dz1BitsUnit_set(index->alloc[i], bitNo);
					index->active[i] = Dz1BitsUnit_set(index->active[i], bitNo);
					return (index->spin++ << 16) | (bitNo & 0xFFFF);
				}
			}
		}
	}
	return -1;
}

static void Dz1ThreadPoolIndex_putId(Dz1ThreadPoolIndex *index, u32_t id)
{
	u32_t idx = id & 0xFFFF;
	if (idx > DZ1_THREAD_MAX) return;
	index->alloc[idx / DZ1_BITS_UNIT_SIZE_BIT] = Dz1BitsUnit_clr(index->alloc[idx / DZ1_BITS_UNIT_SIZE_BIT], idx);
}

int Dz1ThreadPoolIndex_isAllocatedId(Dz1ThreadPoolIndex *index, u32_t id)
{
	u32_t idx = id & 0xFFFF;
	if (idx >= DZ1_THREAD_MAX) return FALSE;
	return Dz1BitsUnit_isSet(index->alloc[idx / DZ1_BITS_UNIT_SIZE_BIT], idx);
}

int Dz1ThreadPoolIndex_isActivatedId(Dz1ThreadPoolIndex *index, u32_t id)
{
	u32_t idx = id & 0xFFFF;
	if (idx >= DZ1_THREAD_MAX) return FALSE;
	return Dz1BitsUnit_isSet(index->active[idx / DZ1_BITS_UNIT_SIZE_BIT], idx);
}

void Dz1ThreadPoolIndex_deactivate(Dz1ThreadPoolIndex *index, u32_t id)
{
	u32_t idx = id & 0xFFFF;
	if (idx > DZ1_THREAD_MAX) return;
	index->active[idx / DZ1_BITS_UNIT_SIZE_BIT] = Dz1BitsUnit_clr(index->active[idx / DZ1_BITS_UNIT_SIZE_BIT], idx);
}

typedef struct Dz1ThreadPoolIndexCleanupArg
{
	Dz1ThreadPoolIndex *index;
	u32_t id;
} Dz1ThreadPoolIndexCleanupArg;

static void Dz1ThreadPoolIndex_cancel(void *ptr)
{
	Dz1ThreadPoolIndexCleanupArg *p = (Dz1ThreadPoolIndexCleanupArg *)ptr;
	Dz1ThreadPoolIndex_putId(p->index, p->id);
}

///////////////////////////////////////////////////////////////////////////////
// DZ1 Thread Pool
///////////////////////////////////////////////////////////////////////////////
Dz1ThreadEntry *Dz1ThreadPool_reg(Dz1ThreadPool *p, Dz1ThreadLogLevel level, Dz1Console *con,
								  str_t name, Dz1ThreadFunc func, Dz1ThreadBarrier *barrier, Dz1Error *err)
{
	u32_t id = -1;
	Dz1ThreadEntry *e = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Error_set(errp, 0);

	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

	if ((id = Dz1ThreadPoolIndex_get(&p->index)) == DZ1_THREAD_INVALID)
	{
		Dz1Error_set(errp, ENOSPC); // POOL Bit Set
	}
	else
	{
		u32_t idx = id & 0xFFFF;
		Dz1ThreadPoolIndexCleanupArg cleanupData;
		cleanupData.index = &p->index;
		cleanupData.id = id;
		pthread_cleanup_push(Dz1ThreadPoolIndex_cancel, (void *)&cleanupData);

		if ((e = Dz1ThreadHash_add(&p->hash, id, level, con, name, func, &p->ret[idx], errp)) != NULL)
		{
			int idx = id & 0x0000FFFF;
			p->table[idx] = e;
			p->threads[idx] = e->th;

			if (barrier != NULL)
			{
				barrier->head = p->barrier.head;
				barrier->tail = p->barrier.tail;
			}
			Dz1Error_set(errp, 0);
		}
		else
		{
			Dz1Error_set(errp, ENOSPC); // POOL Bit Set
		}

		pthread_cleanup_pop(errp->code); // (Dz1ThreadPoolIndex_cancel, (void *)&cleanupData);
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
	return e;
}

void Dz1ThreadPool_dereg(Dz1ThreadPool *p, Dz1ThreadEntry *e)
{
	int idx = e->id & 0x0000FFFF;

	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

	if (Dz1ThreadPoolIndex_isAllocatedId(&p->index, e->id))
	{
		p->table[idx] = NULL;
		Dz1ThreadPoolIndex_putId(&p->index, e->id);	// Clear Allocate bit
	}
	Dz1ThreadHash_remove(&p->hash, e);

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);
}

bool_t Dz1ThreadPool_addBarrier(Dz1ThreadPool *p, Dz1ThreadInitEntry *init, Dz1ThreadCleanupEntry *clean, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ThreadBarrier *barrier = NULL;

	Dz1ThreadInitEntry *tail = NULL;

	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

	barrier = &p->barrier;

	if ((tail = barrier->head) == NULL)
		barrier->head = init;
	else
	{
		while (tail->next != NULL) tail = tail->next;
		tail->next = init;
	}
	init->next = NULL;

	clean->prev = barrier->tail;
	barrier->tail = clean;

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&p->lock);

	return errp->code == 0 ? TRUE : FALSE;
}
