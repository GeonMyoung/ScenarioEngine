#ifndef DZ1_MUTEX_H
#define DZ1_MUTEX_H

#include <pthread.h>
#include <dz1_error.h>

typedef pthread_mutexattr_t Dz1MutexAttr;

typedef pthread_mutex_t Dz1Mutex;
#define Dz1Mutex_initializer			PTHREAD_MUTEX_INITIALIZER

typedef pthread_cond_t Dz1Cond;

/*
 * Dz1Mutex_init : Initialize Dz1Mutex structure
 *
 * @m : Address of Dz1Mutex
 * @attr : Address of Dz1MutexAttr
 *
 * return : Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error  Dz1Mutex_init(Dz1Mutex *m, Dz1MutexAttr *attr);
DZ1_CPPLINK DZ1_DLLPORT Dz1Mutex *Dz1Mutex_new(Dz1Error *err);

/*
 * Dz1Mutex_destroy : Destroy Dz1Mutex structure
 *
 * @m : Address of Dz1Mutex
 *
 * return : Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Mutex_destroy(Dz1Mutex *m);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Mutex_del(Dz1Mutex *p);

/*
 * Dz1Mutex_lock : Lock mutex
 *
 * @m : Address of Dz1Mutex
 *
 * return : Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Mutex_lock(Dz1Mutex *m);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Mutex_trylock(Dz1Mutex *m);

/*
 * Dz1Mutex_unlock : Unlock mutex
 *
 * @m : Address of Dz1Mutex
 *
 * return : Dz1Error structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Mutex_unlock(Dz1Mutex *m);

static __inline__ void			 Dz1Mutex_lockCancel(void *ptr) { Dz1Mutex *m = (Dz1Mutex *)ptr; if (m) Dz1Mutex_unlock(m); }
#define							 Dz1Mutex_cancel				Dz1Mutex_lockCancel

#endif
