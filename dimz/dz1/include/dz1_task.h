#ifndef DZ1_TASK_H
#define DZ1_TASK_H

#include <dz1_thread.h>
//#include <dz1_task_timer.h>

#define DZ1_TASK_QUEUE_NONE			0xFFFFFFFF

#define DZ1_TASK_MSG_EXACT(id)	id, 0xFFFFFFFF
#define DZ1_TASK_MSG_DEFAULT	0x00000000, 0x00000000

#define DZ1_TASK_MSG_DBG_CATEGORY		0xDB600000

typedef void	Dz1TaskSigMsg;

DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_dump(Dz1TaskSigMsg *sig_msg, int tab);

DZ1_CPPLINK DZ1_DLLPORT u32_t			 Dz1TaskSigMsg_getType(Dz1TaskSigMsg *sig_msg);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_setType(Dz1TaskSigMsg *sig_msg, u32_t type);
DZ1_CPPLINK DZ1_DLLPORT void			*Dz1TaskSigMsg_getData(Dz1TaskSigMsg *sig_msg);
DZ1_CPPLINK DZ1_DLLPORT void			*Dz1TaskSigMsg_extractData(Dz1TaskSigMsg *sig_msg, Dz1DelFunc *_del, Dz1DumpFunc *_dump);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		*Dz1TaskSigMsg_getErrPtr(Dz1TaskSigMsg *sig_msg);

#define									 Dz1TaskSigMsg_setErr(sg_p, ecode)	_Dz1TaskSigMsg_setErr((sg_p), (ecode), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT void			_Dz1TaskSigMsg_setErr(Dz1TaskSigMsg *sig_msg, int errcode, const char *__file__, int __line__);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_setError(Dz1TaskSigMsg *p, Dz1Error *err);

//DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1TaskSigMsg_post(void *tDest, void *tSrc, u32_t type, Dz1TaskSigMsg **sg);

DZ1_CPPLINK DZ1_DLLPORT Dz1TaskSigMsg	*Dz1TaskSigMsg_dataWrapper(void **data, Dz1DelFunc dataDel, Dz1DumpFunc dataDump, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TaskSigMsg	*Dz1TaskSigMsg_dataWrapperWithType(u32_t type, void **data, Dz1DelFunc dataDel, Dz1DumpFunc dataDump, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_terminate(Dz1TaskSigMsg  **sig_msg);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_terminateAbnormal(Dz1TaskSigMsg **sig_msg);

DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_termDelAndSetNull(Dz1TaskSigMsg **sig_msg);	// Normal Termination deferred
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_TermDelAndSetNull(Dz1TaskSigMsg **sig_msg);	// Abnormal Termination

DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_termInterrupted(Dz1TaskSigMsg *sg);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1TaskSigMsg_termInterruptedAndDel(Dz1TaskSigMsg *sg);
#define									 Dz1TaskSigMsg_del			Dz1TaskSigMsg_termInterruptedAndDel

typedef enum
{
	Dz1TaskProcStatus_processed,	// Message Processed Successful
	Dz1TaskProcStatus_nohandle,		// Unknown Message
	Dz1TaskProcStatus_error,		// Message Processing is Failed (with err)
	Dz1TaskProcStatus_terminate,	// Message Request Termination of Called Thread
	Dz1TaskProcStatus_max
} Dz1TaskProcStatus;

typedef Dz1TaskProcStatus (*Dz1TaskSigMsgProcFunc)(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp);
typedef Dz1TaskProcStatus (*Dz1TaskTimeoutProcFunc)(void *uArg, void *uRsc, void *timer, void **timer_data, Dz1Error *errp);

typedef Dz1Error (*Dz1TaskUserInitFunc)(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *user_arg, void *timer);
typedef void (*Dz1TaskUserExceptionFunc)(void *uArg, void *uRsc, void *timer, Dz1Error *reason);
typedef Dz1CancelFunc Dz1TaskUserCleanupFunc;

typedef void Dz1Task;
DZ1_CPPLINK DZ1_DLLPORT Dz1Task		*Dz1Task_new(str_t name, u32_t queue_size,
												void **user_arg, Dz1DelFunc user_arg_del,
												Dz1CmpFunc timerCmpFunc,
												Dz1TaskUserInitFunc init,
												Dz1TaskUserExceptionFunc except,
												Dz1TaskUserCleanupFunc cleanup,
												Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Task_del(Dz1Task *ptr);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Task_delAndSetNull(void *pptr);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Task_regMsg(Dz1Task *t, u32_t type, u32_t mask, Dz1TaskSigMsgProcFunc func);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Task_deregMsg(Dz1Task *t, u32_t type, u32_t mask, Dz1TaskSigMsgProcFunc func);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Task_start(Dz1Task *t, Dz1ThreadLogLevel log_level);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Task_startCancel(void *t_ptr);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Task_stop(Dz1Task *t, bool_t detach);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Task_wait(Dz1Task *t, Dz1Error *result);


typedef void (*Dz1TaskSigMsgCallbackFunc)(void *param, void **msg, bool_t isAbnormal);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Task_post(Dz1Task *t, u32_t src_queue_id, u32_t type,
											  void **msg, Dz1DelFunc del, Dz1DumpFunc dump,
											  Dz1Error *initialStatus, Dz1TaskSigMsgCallbackFunc msgTerm, void *param);
#define Dz1Task_postSimple(tDst, srcQueueID, type) \
											  Dz1Task_post((tDst), (srcQueueID),\
														   (type), NULL, NULL, NULL,\
														   NULL, NULL, NULL)


DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Task_call(Dz1Task *t, u32_t src_queue_id,
											  u32_t type, void *msg, Dz1DumpFunc dump,
											  Dz1Error *initialStatus, u64_t *wait_us);
#define Dz1Task_callSimple(tDst, srcQueueID, type, wait_us64p) \
											  Dz1Task_call((tDst), (srcQueueID), \
														   (type), NULL, NULL,\
														   NULL, (wait_us64p))

DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Task_tossSigMsg(Dz1Task *ptr, Dz1TaskSigMsg **sg, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Task_getQueueID(Dz1Task *t);
DZ1_CPPLINK DZ1_DLLPORT str_t Dz1Task_getName(Dz1Task *t);	// for debug log
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Task_getThread(Dz1Task *t);


DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Task_queuePost(u32_t dst_queue_id, u32_t src_queue_id,
												   u32_t type, void **msg, Dz1DelFunc del, Dz1DumpFunc dump,
												   Dz1Error *initialStatus, Dz1TaskSigMsgCallbackFunc msgTerm, void *param);

#define Dz1Task_queuePostSimpleErr(dstQueueID, srcQueueID, type, initialERR) \
													Dz1Task_queuePost((dstQueueID), (srcQueueID), \
																	  (type), NULL, NULL, NULL, \
																	  (initialERR), NULL, NULL)

#define Dz1Task_queuePostSimple(dstQueueID, srcQueueID, type) \
													Dz1Task_queuePostSimpleErr(dstQueueID, srcQueueID, type, NULL)

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Task_queueCall(u32_t dst_queue_id, u32_t src_queue_id,
												   u32_t type, void *msg, Dz1DumpFunc dump,
												   Dz1Error *initialStatus, u64_t *wait_us);
#define Dz1Task_queueCallSimple(dstQueueID, srcQueueID, type, wait_us64p) \
													Dz1Task_queueCall((dstQueueID), (srcQueueID),\
																	  (type), NULL, NULL,\
																	  NULL, (wait_u64p))
#endif
