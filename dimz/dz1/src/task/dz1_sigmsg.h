#ifndef DZ1_SIGMSG_H_LOCAL
#define DZ1_SIGMSG_H_LOCAL

#include <dz1_sync.h>
#include <dz1_task.h>

typedef enum
{
	Dz1SigMsgStatus_initiated,
	Dz1SigMsgStatus_processed,
	Dz1SigMsgStatus_aborted
} Dz1SigMsgStatus;

typedef struct Dz1SigMsgSync
{
	Dz1Sync sync;
	Dz1SigMsgStatus status;
} Dz1SigMsgSync;

static __inline__ void Dz1SigMsgSync_init(Dz1SigMsgSync *p)
{
	Dz1Sync_init(&p->sync);
	p->status = Dz1SigMsgStatus_initiated;
}

static __inline__ void Dz1SigMsgSync_destroy(Dz1SigMsgSync *p)
{
	Dz1Sync_destroy(&p->sync);
}

DZ1_CPPLINK void Dz1SigMsgSync_lock(Dz1SigMsgSync *p);
DZ1_CPPLINK void Dz1SigMsgSync_unlock(Dz1SigMsgSync *p);
static __inline__ void Dz1SigMsgSync_lockCancel(void *ptr)
{
	Dz1SigMsgSync *p = (Dz1SigMsgSync *)ptr;
	Dz1SigMsgSync_unlock(p);
}
DZ1_CPPLINK Dz1Error Dz1SigMsgSync_wait(Dz1SigMsgSync *p, u64_t *wait_us);
//DZ1_CPPLINK void Dz1SigMsgSync_signal(Dz1SigMsg *p, Dz1SigMsgStatus status);

#define DZ1_SIG_MSG_SYNC_INITIALIZER { DZ1_SYNC_INITIALIZER, Dz1SigMsgStatus_initiated }

typedef struct Dz1SigMsgCallback
{
	Dz1TaskSigMsgCallbackFunc callback;
	void *param;
} Dz1SigMsgCallback;

typedef enum Dz1SigMsgPostProcess
{
	Dz1SigMsgPostProcess_none,
	Dz1SigMsgPostProcess_call,
	Dz1SigMsgPostProcess_callback
} Dz1SigMsgPostProcess;

typedef struct Dz1SigMsg
{
	u32_t dst;
	u32_t src;

	u32_t type;

	void *msg;
	Dz1DelFunc del;
	Dz1DumpFunc dump;

	Dz1Error err;

	Dz1SigMsgPostProcess ppt;

	union Dz1SigMsgPostProcessInfo
	{
		Dz1SigMsgSync sync;
		Dz1SigMsgCallback cb;
	} x;

	int ref;
} Dz1SigMsg;

DZ1_CPPLINK Dz1SigMsg *Dz1SigMsg_new(u32_t dst, u32_t src, u32_t type, void *msg, Dz1DelFunc del, Dz1DumpFunc dump, Dz1Error *initialStatus, Dz1Error *err);
DZ1_CPPLINK void Dz1SigMsg_del(Dz1SigMsg *p);
static __inline__ void Dz1SigMsg_delAndSetNull(void *ptr)
{
	Dz1SigMsg **p = (Dz1SigMsg **)ptr;
	Dz1SigMsg_del(*p); *p = NULL;
}
DZ1_CPPLINK void Dz1SigMsgA_dump(Dz1SigMsg *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void Dz1SigMsgW_dump(Dz1SigMsg *p, int tab);
#ifdef UNICODE
#define						 Dz1SigMsg_dump			Dz1SigMsgW_dump
#else // UNICODE
#define						 Dz1SigMsg_dump			Dz1SigMsgA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1SigMsg_dump			Dz1SigMsgA_dump
#endif // UNIX_SYSTEM

DZ1_CPPLINK void Dz1SigMsg_finalize(Dz1SigMsg **p, bool_t isAbnormal);

DZ1_CPPLINK void Dz1SigMsg_signal(Dz1SigMsg **p, bool_t isAbnormal);
DZ1_CPPLINK void Dz1SigMsg_lock(Dz1SigMsg *p);
DZ1_CPPLINK void Dz1SigMsg_unlock(Dz1SigMsg *p);
DZ1_CPPLINK void Dz1SigMsg_lockCancel(void *ptr);


#endif
