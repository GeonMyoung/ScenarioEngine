#ifndef DZ1_THREAD_STATUS_H
#define DZ1_THREAD_STATUS_H

#include <dz1.h>

typedef enum
{
	Dz1ThreadStatus_run,
	Dz1ThreadStatus_sleep,
	Dz1ThreadStatus_locking,
	Dz1ThreadStatus_waitting,
	Dz1ThreadStatus_joinning,
	Dz1ThreadStatus_max
} Dz1ThreadStatus;

/*
 * Dz1Thread_getStatus : Get my thread status
 *
 * return my thread status
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1ThreadStatus Dz1Thread_getStatus(void);

/*
 * Dz1Thread_setStatus : Set my thread status
 *
 * @status : Dz1ThreadStatus
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1Thread_setStatus(Dz1ThreadStatus status);

static __inline__ void Dz1Thread_setStatusCleanup(Dz1ThreadStatus *status) { Dz1Thread_setStatus(*status); }

#endif
