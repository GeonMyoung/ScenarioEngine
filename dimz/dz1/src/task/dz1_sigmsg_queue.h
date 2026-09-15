#ifndef DZ1_SIGMSG_QUEUE_H_LOCAL
#define DZ1_SIGMSG_QUEUE_H_LOCAL

#include "dz1_sigmsg.h"

#define DZ1_TASK_COMMAND_STOP		0xFFFFFFFF
#define DZ1_TASK_COMMAND_NONE		0

typedef enum
{
	Dz1SigMsgQueuePostMode_async,
	Dz1SigMsgQueuePostMode_sync
} Dz1SigMsgQueuePostMode;

DZ1_CPPLINK u32_t Dz1SigMsgQueue_new(u32_t size, Dz1Error *err);
DZ1_CPPLINK void Dz1SigMsgQueue_del(u32_t dst);
static __inline__ void Dz1SigMsgQueue_cancel(void *ptr)
{
	u32_t *id = (u32_t *)ptr;
	Dz1SigMsgQueue_del(*id); *id = 0xFFFFFFFF;
}

DZ1_CPPLINK bool_t Dz1SigMsgQueue_toss(u32_t dst, Dz1SigMsg **msg, Dz1Error *err);
DZ1_CPPLINK Dz1Error Dz1SigMsgQueue_post(u32_t dst, u32_t src, u32_t type,
													 void **msg, Dz1DelFunc del, Dz1DumpFunc dump,
													 Dz1Error *initialStatus, Dz1TaskSigMsgCallbackFunc msgTerm, void *param);

//DZ1_CPPLINK Dz1Error Dz1SigMsgQueue_postSig(u32_t dst, u32_t src, u32_t type, void **sgptr);

//DZ1_CPPLINK Dz1Error _Dz1SigMsgQueue_post(u32_t dst, Dz1SigMsg **sg);

DZ1_CPPLINK Dz1Error Dz1SigMsgQueue_call(u32_t dst, u32_t src, u32_t type, void *msg, Dz1DumpFunc dump, Dz1Error *initialStatus, u64_t *wait_us);

DZ1_CPPLINK Dz1SigMsg *Dz1SigMsgQueue_pend(u32_t queue_id, u64_t *wait_us, Dz1Error *err);

DZ1_CPPLINK void Dz1SigMsgQueue_halt(u32_t dst);
static __inline__ void _Dz1SigMsgQueue_halt(void *ptr)
{
	u32_t *dst = (u32_t *)ptr;
	Dz1SigMsgQueue_halt(*dst);
}

#endif
