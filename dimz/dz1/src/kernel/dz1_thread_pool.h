#ifndef DZ1_THREAD_POOL_H_LOCAL
#define DZ1_THREAD_POOL_H_LOCAL

#include <pthread.h>
#include "dz1_thread_hash.h"

typedef struct Dz1ThreadPoolIndex
{
	u16_t spin;
	DZ1_BITS_UNIT alloc[DZ1_THREAD_INDEX_SIZE];
	DZ1_BITS_UNIT active[DZ1_THREAD_INDEX_SIZE];
} Dz1ThreadPoolIndex;

DZ1_CPPLINK int Dz1ThreadPoolIndex_isAllocatedId(Dz1ThreadPoolIndex *index, u32_t id);
DZ1_CPPLINK int Dz1ThreadPoolIndex_isActivatedId(Dz1ThreadPoolIndex *index, u32_t id);
DZ1_CPPLINK void Dz1ThreadPoolIndex_deactivate(Dz1ThreadPoolIndex *index, u32_t id);

typedef struct Dz1ThreadBarrier
{
	Dz1ThreadInitEntry				*head;
	Dz1ThreadCleanupEntry			*tail;
} Dz1ThreadBarrier;

typedef struct Dz1ThreadPool
{
	pthread_mutex_t lock;
	Dz1ThreadBarrier barrier;
	Dz1ThreadHash hash;
	Dz1ThreadPoolIndex index;
	Dz1ThreadEntry *table[DZ1_THREAD_MAX];
	pthread_t threads[DZ1_THREAD_MAX];
	Dz1Error ret[DZ1_THREAD_MAX];
} Dz1ThreadPool;

DZ1_CPPLINK_VAR Dz1ThreadPool *thread_pool;

DZ1_CPPLINK Dz1ThreadEntry	*Dz1ThreadPool_reg(Dz1ThreadPool *p, Dz1ThreadLogLevel level, Dz1Console *con, str_t name, Dz1ThreadFunc func, Dz1ThreadBarrier *barrier, Dz1Error *err);
DZ1_CPPLINK void			 Dz1ThreadPool_dereg(Dz1ThreadPool *p, Dz1ThreadEntry *e);

DZ1_CPPLINK bool_t			 Dz1ThreadPool_addBarrier(Dz1ThreadPool *p, Dz1ThreadInitEntry *init, Dz1ThreadCleanupEntry *clean, Dz1Error *err);

#endif
