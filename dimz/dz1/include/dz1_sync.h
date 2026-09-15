#ifndef DZ1_SYNC_H
#define DZ1_SYNC_H

#include <dz1_timeval.h>
//#include <dz1_thread.h>
#include <dz1_mutex.h>

typedef struct Dz1Sync
{
	pthread_mutex_t lock;
	pthread_cond_t cond;
} Dz1Sync;
#define DZ1_SYNC_INITIALIZER		{ PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER }

#define								 Dz1Sync_new(errp)	_Dz1Sync_new((errp), __FILE__, __LINE__)
DZ1_CPPLINK Dz1Sync				   *_Dz1Sync_new(Dz1Error *err, const char *__file__, int __line__);
DZ1_CPPLINK void					 Dz1Sync_del(Dz1Sync *p);
static __inline__ void				 Dz1Sync_delAndSetNull(void *ptr)
{
	Dz1Sync **p = (Dz1Sync **)ptr;
	Dz1Sync_del(*p); *p = NULL;
}

static __inline__ void				 Dz1Sync_init(Dz1Sync *p)
{
	if (!p) return;
	pthread_mutex_init(&p->lock, NULL);
	pthread_cond_init(&p->cond, NULL);
}

static __inline__ void				 Dz1Sync_destroy(Dz1Sync *p)
{
	if (!p) return;
	pthread_mutex_destroy(&p->lock);
	pthread_cond_destroy(&p->cond);
}

typedef Dz1Error (*Dz1SyncCondFunc)(void *ptr, bool_t *wakeup);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Sync_wait(Dz1Sync *p, u64_t *wait_us, Dz1SyncCondFunc func, void *ptr);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Sync_wait2(Dz1Sync *p, u64_t *wait_us);

#define Dz1Sync_lock(syncp)			 Dz1Mutex_lock(&(syncp)->lock);
#define Dz1Sync_unlock(syncp)		 Dz1Mutex_unlock(&(syncp)->lock);
static __inline__ void				 Dz1Sync_cancel(void *ptr)
{
	Dz1Sync *p = (Dz1Sync *)ptr;
	if (p) Dz1Sync_unlock(p);
}

#define								 Dz1Sync_signal(syncp)		pthread_cond_signal(&(syncp)->cond);
static __inline__ void				 Dz1Sync_lockCancel(void *ptr) { Dz1Sync *sync = (Dz1Sync *)ptr; Dz1Sync_unlock(sync); }

#endif
