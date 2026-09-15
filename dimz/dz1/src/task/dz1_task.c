#include <dz1_malloc.h>
#include "../kernel/dz1_thread_stdio.h"
#include <dz1_usleep.h>
#include <dz1_str.h>
#include "dz1_sigmsg_queue.h"
#include "dz1_task_timer.h"
#include "dz1_task_sigmsg_router.h"

#include <dz1_task.h>

void Dz1TaskSigMsg_dump(Dz1TaskSigMsg *ptr, int tab) { Dz1SigMsg_dump((Dz1SigMsg *)ptr, tab); }

u32_t Dz1TaskSigMsg_getType(Dz1TaskSigMsg *ptr)
{
	u32_t ret = 0;
	Dz1SigMsg *sg = (Dz1SigMsg *)ptr;
	if (sg != NULL)
		ret = sg->type;
	return ret;
}

void Dz1TaskSigMsg_setType(Dz1TaskSigMsg *ptr, u32_t new_type)
{
	Dz1SigMsg *sg = (Dz1SigMsg *)ptr;
	if (sg != NULL)
		sg->type = new_type;
}

void *Dz1TaskSigMsg_getData(Dz1TaskSigMsg *ptr)
{
	void *ret = NULL;
	Dz1SigMsg *sg = (Dz1SigMsg *)ptr;
	if (sg != NULL)
		ret = sg->msg;
	return ret;
}

void *Dz1TaskSigMsg_extractData(Dz1TaskSigMsg *ptr, Dz1DelFunc *_del, Dz1DumpFunc *_dump)
{
	void *ret = NULL;
	Dz1SigMsg *sg = (Dz1SigMsg *)ptr;
	if (sg != NULL)
	{
		ret = sg->msg; sg->msg = NULL;
		if (_del) *_del = sg->del;
		if (_dump) *_dump = sg->dump;
	}
	return ret;
}

Dz1Error *Dz1TaskSigMsg_getErrPtr(Dz1TaskSigMsg *ptr) { return &((Dz1SigMsg *)ptr)->err; }

void _Dz1TaskSigMsg_setErr(Dz1TaskSigMsg *ptr, int errcode, const char *__file__, int __line__) { _Dz1Error_set(&((Dz1SigMsg *)ptr)->err, errcode, __file__, __line__); }
void Dz1TaskSigMsg_setError(Dz1TaskSigMsg *ptr, Dz1Error *err) { memcpy(&(((Dz1SigMsg *)ptr)->err), err, sizeof(Dz1Error)); }

void Dz1TaskSigMsg_terminate(Dz1TaskSigMsg **sig_msg)
{
	if (sig_msg == NULL || *sig_msg == NULL) return;
	Dz1SigMsg_finalize((Dz1SigMsg **)sig_msg, FALSE);
}

void Dz1TaskSigMsg_terminateAbnormal(Dz1TaskSigMsg **sig_msg)
{
	if (sig_msg == NULL || *sig_msg == NULL) return;
	Dz1SigMsg_finalize((Dz1SigMsg **)sig_msg, TRUE);
}

void Dz1TaskSigMsg_termDelAndSetNull(Dz1TaskSigMsg **sig_msg)
{
	if (sig_msg == NULL || *sig_msg == NULL) return;
	Dz1SigMsg_finalize((Dz1SigMsg **)sig_msg, FALSE);
	Dz1SigMsg_del((Dz1SigMsg *)*sig_msg);
	*sig_msg = NULL;
}

void Dz1TaskSigMsg_TermDelAndSetNull(Dz1TaskSigMsg **sig_msg)
{
	if (sig_msg == NULL || *sig_msg == NULL) return;
	Dz1SigMsg_finalize((Dz1SigMsg **)sig_msg, TRUE);
	Dz1SigMsg_del((Dz1SigMsg *)*sig_msg);
	*sig_msg = NULL;
}

void Dz1TaskSigMsg_termInterrupted(Dz1TaskSigMsg *sg)
{
	if (sg == NULL) return;
	else
	{
		Dz1Error *status = Dz1TaskSigMsg_getErrPtr(sg);
		Dz1Error_set(status, EINTR);
		Dz1SigMsg_finalize((Dz1SigMsg **)&sg, TRUE);
	}
}

void Dz1TaskSigMsg_termInterruptedAndDel(Dz1TaskSigMsg *sg)
{
	if (sg == NULL) return;
	else
	{
		Dz1TaskSigMsg_termInterrupted(sg);
		Dz1SigMsg_del((Dz1SigMsg *)sg);
	}
}

typedef u64_t *(*Dz1TaskTimerGetDurationFunc)(void *timer, u64_t *dst);
typedef Dz1TaskProcStatus (*Dz1TaskTimerTimeoutFunc)(void *user_arg, void *user_resource, void *timer, Dz1Error *err);

#define DZ1_TASK_JOIN_STATUS_JOINED			0
#define DZ1_TASK_JOIN_STATUS_WANT_JOIN		1
#define DZ1_TASK_JOIN_STATUS_JOINING		2

typedef struct Dz1TaskThreadHandle
{
	u32_t						 id;
	bool_t						 running;
	bool_t						 joinning;

	Dz1CmpFunc					 timerCmpFunc;

	str_t						 name;
	u32_t						 queue_id;
	void						*user_arg;
	Dz1DelFunc					 user_arg_del;

	Dz1TaskUserInitFunc			 init;
	Dz1TaskUserExceptionFunc	 except;
	Dz1TaskUserCleanupFunc		 cleanup;
	void						*router;
} Dz1TaskThreadHandle;

static void Dz1TaskThreadHandle_del(Dz1TaskThreadHandle *p)
{
	if (!p) return;
	if (p->name) Dz1StrA_del(p->name);
	if (p->queue_id != 0xFFFFFFFF) Dz1SigMsgQueue_del(p->queue_id);
	if (p->user_arg && p->user_arg_del) p->user_arg_del(p->user_arg);
	if (p->router) Dz1TaskSigRouter_del(p->router);
	Dz1Free(p);
}

static void Dz1TaskThreadHandle_delAndSetNull(void *ptr)
{
	Dz1TaskThreadHandle **p = (Dz1TaskThreadHandle **)ptr;
	Dz1TaskThreadHandle_del(*p); *p = NULL;
}

static Dz1TaskThreadHandle *Dz1TaskThreadHandle_new(str_t name, u32_t queue_size,
								void **user_arg, Dz1DelFunc user_arg_del,
								Dz1CmpFunc timerCmpFunc,
								Dz1TaskUserInitFunc init,
								Dz1TaskUserExceptionFunc except,
								Dz1TaskUserCleanupFunc cleanup,
								Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskThreadHandle *ret = (Dz1TaskThreadHandle *)Dz1Calloc(sizeof(Dz1TaskThreadHandle), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->user_arg_del = user_arg_del;
		ret->queue_id = ret->id = 0xFFFFFFFF; 

		pthread_cleanup_push(Dz1TaskThreadHandle_delAndSetNull, (void *)&ret);

		if ((ret->name = Dz1StrA_dup(name, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->queue_id = Dz1SigMsgQueue_new(queue_size, errp)) == 0xFFFFFFFF) ERR_OUT(errp);
		else if ((ret->router = Dz1TaskSigRouter_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (user_arg && *user_arg)
			{
				int state;
				pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state);
				ret->user_arg = (*user_arg);
				*user_arg = NULL;
				pthread_setcancelstate(state, NULL);
			}
			ret->timerCmpFunc = timerCmpFunc;
			ret->init = init;
			ret->except = except;
			ret->cleanup = cleanup;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TaskThreadHandle_delAndSetNull, (void *)&ret);
	}
	return ret;
}

typedef struct Dz1TaskThreadArg
{
	Dz1Sync sync;
	Dz1Error result;
	int flag;
	Dz1TaskThreadHandle *h;
} Dz1TaskThreadArg;

static void Dz1TaskThreadArg_signal(Dz1TaskThreadArg *p, Dz1Error *result)
{
	printf("Dz1TaskThreadArg_signal(%s) : Called\n", p->h->name);fflush(stdout);
	Dz1Sync_lock(&p->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&p->sync);

	p->result = *result;
	p->flag = 1;
	Dz1Sync_signal(&p->sync);

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&p->sync);
}

typedef struct Dz1TaskThreadEnv
{
	void						*timer;
	Dz1TaskTimerGetDurationFunc	 timerGetDuration;
	Dz1TaskTimerTimeoutFunc		 timerTimeout;
	Dz1DelFunc					 timerDel;

	Dz1TaskUserCleanupFunc		 cleanup;
	void						*user_resource;

	str_t						 name;
} Dz1TaskThreadEnv;

// Timer Initialize
static Dz1Error _Dz1TaskThreadEnv_new(Dz1TaskThreadEnv *ret, Dz1CmpFunc timerDataCmp)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((ret->timer = Dz1TaskTimer_new(timerDataCmp, &err)) == NULL) ERR_OUT(&err);
	else
	{
		ret->timerGetDuration = Dz1TaskTimer_getDuration;
		ret->timerTimeout = Dz1TaskTimer_timeout;
		ret->timerDel = Dz1TaskTimer_del;
	}

	return err;
}

static void Dz1TaskThreadEnv_del(Dz1TaskThreadEnv *env)
{
	if (env->cleanup && env->user_resource)
	{
		Dz1Thread_stackTrace_PUSH((DZ1_THREAD_CALL_ARG, "Task(%s) : User Resource Cleanup", env->name));
		env->cleanup(env->user_resource);
		Dz1Thread_stackTrace_pop();
	}
	if (env->timer && env->timerDel)
	{
		Dz1Thread_stackTrace_PUSH((DZ1_THREAD_CALL_ARG, "Task(%s) : Timer Cleanup", env->name));
		env->timerDel(env->timer);
		Dz1Thread_stackTrace_pop();
	}
	Dz1Free(env);
}

static void Dz1TaskThreadEnv_delAndSetNull(void *ptr)
{
	Dz1TaskThreadEnv **p = (Dz1TaskThreadEnv **)ptr;
	Dz1TaskThreadEnv_del(*p); *p = NULL;
}

static Dz1TaskThreadEnv *Dz1TaskThreadEnv_new(str_t name, Dz1CmpFunc timerCmpFunc, Dz1TaskUserCleanupFunc cleanup, void *user_resource, Dz1Error *errp)
{
	Dz1TaskThreadEnv *ret = (Dz1TaskThreadEnv *)Dz1Calloc(sizeof(Dz1TaskThreadEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TaskThreadEnv_delAndSetNull, (void *)&ret);

		if ((*errp = _Dz1TaskThreadEnv_new(ret, timerCmpFunc)).code) ERR_OUT(errp);
		else
		{
			ret->cleanup = cleanup;
			ret->user_resource = user_resource;
			ret->name = name;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1TaskThreadEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void setIdleState(void *ptr)
{
	bool_t *running = (bool_t *)ptr;
	*running = FALSE;
}

static void Dz1TaskThread_sigMsgTermAbnormal(Dz1SigMsg **msg) { Dz1SigMsg_signal(msg, TRUE); }
static void Dz1Task_sigMsgCleanup(Dz1SigMsg **msg)
{
	if (!msg || !*msg) return;
	else
	{
		Dz1SigMsg *sg = *msg;
		Dz1SigMsg_del(sg);
		*msg = NULL;
	}
}

static Dz1Error Dz1TaskThread(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskThreadArg *arg = (Dz1TaskThreadArg *)ptr;
	Dz1TaskThreadHandle *h = arg->h;

	Dz1TaskThreadEnv *env = Dz1TaskThreadEnv_new(h->name, h->timerCmpFunc, h->cleanup, NULL, &err);

	if (env == NULL) { Dz1TaskThreadArg_signal(arg, &err); ERR_OUT(&err); }
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1TaskThreadEnv_del, (void *)env);

		h->running = 1;
		h->joinning = DZ1_TASK_JOIN_STATUS_WANT_JOIN;
		pthread_cleanup_push(setIdleState, (void *)&h->running);

		if (h->init && (err = h->init(&env->user_resource, h, h->name, h->queue_id, h->user_arg, env->timer)).code)
		{
			Dz1TaskThreadArg_signal(arg, &err);
			ERR_OUT(&err);
		}
		else
		{
			Dz1TaskProcStatus status = Dz1TaskProcStatus_processed;

			Dz1SigMsg *sg = NULL;
			u64_t *delay = NULL, _delay = 0;

			Dz1TaskThreadArg_signal(arg, &err);

			pthread_cleanup_push(_Dz1SigMsgQueue_halt, (void *)&h->queue_id);
			while(status == Dz1TaskProcStatus_processed)
			{
				Dz1Thread_stackTrace_PUSH((DZ1_THREAD_CALL_ARG, "TaskLoop(%s) : Message Pending Loop", env->name));
				delay = env->timerGetDuration(env->timer, &_delay);

				sg = Dz1SigMsgQueue_pend(h->queue_id, delay, &err);	// sg->ref is increased when Dz1SigMsgQueue_push
				pthread_cleanup_push((Dz1CancelFunc)Dz1Task_sigMsgCleanup, (void *)&sg);

				if (sg == NULL)
				{
					if (err.code == ETIMEDOUT) Dz1Error_set(&err, 0);
					else { status = Dz1TaskProcStatus_error; }
				}

				if (status == Dz1TaskProcStatus_processed)
				{	// Timeout Processing
					Dz1Thread_stackTrace_PUSH((DZ1_THREAD_CALL_ARG, "TaskLoop(%s) Timeout Processing", h->name));

					status = env->timerTimeout(h->user_arg, env->user_resource, env->timer, &err);

					if (status == Dz1TaskProcStatus_error) ERR_OUT(&err);
					else if (status == Dz1TaskProcStatus_terminate) { }
					else if (sg)
					{
						u32_t type = sg->type;

// 						Dz1SigMsg_lock(sg);
// 						pthread_cleanup_push(Dz1SigMsg_lockCancel, (void *)sg);
// 						pthread_cleanup_push((Dz1CancelFunc)Dz1TaskThread_sigMsgTermAbnormal, (void *)&sg);	// using noLockSignal

						pthread_cleanup_push(Dz1TaskSigMsg_terminateAbnormal, (void *)&sg);
						Dz1Thread_stackTrace_PUSH((DZ1_THREAD_CALL_ARG, "TaskLoop(%s) Message(0x%08X) Processing", h->name, type));

						if (type == DZ1_TASK_COMMAND_STOP)
						{	// User Data Free
							Dz1Thread_log(DZ1_THREAD_LOG_TASK_DEBUG, "TaskLoop(%s) : Task Termination\n", h->name, type);
							status = Dz1TaskProcStatus_terminate;
						}
						else if (type == DZ1_TASK_COMMAND_NONE)
						{	// Ignore Message
							Dz1Thread_log(DZ1_THREAD_LOG_TASK_DEBUG, "TaskLoop(%s) : Message Canceled\n", h->name, type);
							status = Dz1TaskProcStatus_processed;
						}
						else
						{
							// Set Initial Error Status from SigMsg
							memcpy(&err, &sg->err, sizeof(Dz1Error));

							// Do Message Processing
							status = Dz1TaskSigRouter_proc(h->router, h->user_arg, env->user_resource, env->timer, (void **)&sg, &err);

							// Result Handling
							if (status == Dz1TaskProcStatus_error)
							{
								Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "TaskLoop(%s) : Error occur while processing msg 0x%08X\n", h->name, type);
								ERR_OUT(&err);
							}
							else if (status == Dz1TaskProcStatus_nohandle)
							{
								u32_t my_log_level = 0;
								Dz1Thread_getLogLevel(h->id, &my_log_level);
								Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "TaskLoop(%s) : msg 0x%08X is ignored\n", h->name, type);

								if (my_log_level & DZ1_THREAD_LOG_TASK_DEBUG)
								{	// print debugging info
									if (sg != NULL && sg->dump != NULL)
									{
										Dz1Thread_eprintf("TaskLoop(%s) : msg 0x%08X = ", h->name, type);
										sg->dump(sg->msg, 0);
										Dz1Thread_eprintf("is ignored\n", type);
									}
									Dz1Thread_eprintf("TaskLoop(%s) : msg map =", h->name);
									Dz1TaskSigRouter_dump(h->router, 1);
								}

								status = Dz1TaskProcStatus_processed;
								Dz1Error_set(&sg->err, ESRCH);
								Dz1TaskSigMsg_terminateAbnormal(&sg);
							}
							else
							{	// processed, terminate
								Dz1Thread_log(DZ1_THREAD_LOG_TASK_DEBUG, "TaskLoop(%s) : msg 0x%08X processing successful\n", h->name, type);

								// Apply Error from Processed SigMsg
								if (sg)
								{
									memcpy(&sg->err, &err, sizeof(Dz1Error));
									Dz1TaskSigMsg_terminate(&sg);
								}
							}
//							if (sg) Dz1SigMsg_signal(&sg, FALSE);	// using noLockSignal
						}
						Dz1Thread_stackTrace_pop(); // ((DZ1_THREAD_CALL_ARG, "Task(%s) Message(0x%08X) Processing", h->name, type));
						pthread_cleanup_pop(status == Dz1TaskProcStatus_error); // (Dz1TaskSigMsg_terminateAbnormal, (void *)&sg);

// 						pthread_cleanup_pop(status == Dz1TaskProcStatus_error); // ((Dz1CancelFunc)Dz1TaskThread_sigMsgTermAbnormal, (void *)&sg);
// 						pthread_cleanup_pop(1); // (Dz1SigMsg_lockCancel, (void *)sg);
					}
					Dz1Thread_stackTrace_pop(); // ((DZ1_THREAD_CALL_ARG, "Task(%s) Timeout Processing", h->name));
				}
				pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1Task_sigMsgCleanup, (void *)&sg);

				Dz1Thread_stackTrace_pop(); // ((DZ1_THREAD_CALL_ARG, "Task(%s) : Message Pending Loop", env->name));
			}
			pthread_cleanup_pop(1); // (_Dz1SigMsgQueue_halt, (void *)&h->queue_id);
			if (status == Dz1TaskProcStatus_error && h->except)
			{
				Dz1Thread_PROC(h->except(h->user_arg, env->user_resource, env->timer, &err), 
								(DZ1_THREAD_CALL_ARG, "TaskLoop(%s) Exception Handling", h->name));
			}
//			h->except(h->user_arg, env->user_resource, env->timer, &err);
			else Dz1Thread_log(DZ1_THREAD_LOG_TASK_DEBUG, "TaskLoop(%s) : exit status = %d\n", h->name, status);
		}
		pthread_cleanup_pop(1); // (setIdleState, (void *)&h->running);
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1TaskThreadEnv_del, (void *)env);
	}
	return err;
}

void *Dz1Task_new(str_t name, u32_t queue_size,
					void **user_arg, Dz1DelFunc user_arg_del,
					Dz1CmpFunc timerCmpFunc,
					Dz1TaskUserInitFunc init,
					Dz1TaskUserExceptionFunc except,
					Dz1TaskUserCleanupFunc cleanup,
					Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskThreadHandle *h = Dz1TaskThreadHandle_new(name, queue_size, user_arg, user_arg_del, timerCmpFunc, init, except, cleanup, errp);
	if (h == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0);
	return h;
}

static bool_t Dz1Task_isStopped(Dz1TaskThreadHandle *h)
{
	bool_t ret = FALSE;

	if (h->running)
	{
		if (h->id == 0xFFFFFFFF) ret = TRUE;
	}

	return ret;
}

static bool_t Dz1Task_isJoined(Dz1TaskThreadHandle *h)
{
	bool_t ret = FALSE;

	if (h->id == 0xFFFFFFFF) ret = TRUE;
	else if (h->joinning == DZ1_TASK_JOIN_STATUS_JOINED) ret = TRUE;
	return ret;
}

Dz1Error Dz1Task_del(Dz1Task *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;

	if (h == NULL) return err;

	if (!Dz1Task_isStopped(h) && (err = Dz1Task_stop(h, FALSE)).code) { }
	else if (!Dz1Task_isJoined(h) && (err = Dz1Task_wait(h, NULL)).code) ERR_OUT(&err);
	else Dz1TaskThreadHandle_del(h);

	return err;
}

void Dz1Task_delAndSetNull(void *pptr)
{
	Dz1TaskThreadHandle **h = (Dz1TaskThreadHandle **)pptr;
	Dz1Task_del(*h); *h = NULL;
}

Dz1Error Dz1Task_regMsg(Dz1Task *ptr, u32_t type, u32_t mask, Dz1TaskSigMsgProcFunc func)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;

	if (type == DZ1_TASK_COMMAND_STOP) ERR_SET_OUT(&err, EINVAL);
	else if (type == DZ1_TASK_COMMAND_NONE) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Dz1TaskSigRouter_reg(h->router, type, mask, func)).code) ERR_OUT(&err);

	return err;
}

void Dz1Task_deregMsg(Dz1Task *ptr, u32_t type, u32_t mask, Dz1TaskSigMsgProcFunc func)
{
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;

	Dz1TaskSigRouter_dereg(h->router, type, mask);
}

static Dz1Error _Dz1Task_start(void *ptr, bool_t *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskThreadArg *arg = (Dz1TaskThreadArg *)ptr;

	if (arg->flag == 1) *status = TRUE; else *status = FALSE;

	return err;
}

Dz1Error Dz1Task_start(Dz1Task *ptr, Dz1ThreadLogLevel log_level)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;

	if (h->running) ERR_SET_OUT(&err, EEXIST);
	else
	{
		Dz1TaskThreadArg arg = { DZ1_SYNC_INITIALIZER, DZ1_ERROR_INITIALIZER, 0 };

		pthread_cleanup_push((Dz1DelFunc)Dz1Sync_destroy, (void *)&arg.sync);

		arg.h = h;
		Dz1Sync_lock(&arg.sync);
		pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&arg.sync);

		if ((err = _Dz1Thread_create(&h->id, h->name, Dz1TaskThread, (void *)&arg, log_level)).code) ERR_OUT(&err);
		else if ((err = Dz1Sync_wait(&arg.sync, NULL, _Dz1Task_start, &arg)).code) ERR_OUT(&err);
		else if ((err = arg.result).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&arg.sync);

		pthread_cleanup_pop(1); // (Dz1Sync_destroy, (void *)&arg.sync);
	}

	return err;
}

void Dz1Task_startCancel(void *task)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1Task_stop(task, FALSE)).code) ERR_OUT(&err);
	else Dz1Task_wait(task, NULL);
}

Dz1Error Dz1Task_stop(Dz1Task *ptr, bool_t detach)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;

	if (h == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (h->running)
	{
		if (h->id == 0xFFFFFFFF) Dz1Error_set(errp, ENOSYS);	// Never Started
		else
		{
			Dz1Thread_eprintf("Dz1Task_stop() : Stopping Task = %s\n", h->name);
			if ((*errp = Dz1Task_post(ptr, DZ1_TASK_QUEUE_NONE, DZ1_TASK_COMMAND_STOP, NULL, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
			else
			{
				while(h->running) Dz1Thread_usleep(1000);
				Dz1Error_set(errp, 0);
			}
		}
	}
	return err;
}

Dz1Error Dz1Task_wait(Dz1Task *ptr, Dz1Error *result)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;

	if (h->id == 0xFFFFFFFF)
	{	// Not Started
		Dz1Thread_eprintf("TaskWait(%s) is not running\n", h->name);
		Dz1Error_set(errp, 0);
	}
	else if (h->joinning != DZ1_TASK_JOIN_STATUS_WANT_JOIN)
	{
		if (h->joinning == DZ1_TASK_JOIN_STATUS_JOINED)
		{
			Dz1Thread_eprintf("TaskWait(%s) is Already Joined\n", h->name);
			Dz1Error_set(errp, 0);
		}
		else
		{
			if (h->joinning == DZ1_TASK_JOIN_STATUS_JOINING)
			{
			//	Dz1Thread_eprintf("TaskWait(%s) is Waited by other thread\n", h->name);
			}
			else Dz1Thread_eprintf("TaskWait(%s) : Unknown Join Status = %d\n", h->name, h->joinning);
			Dz1Error_set(&err, EAGAIN); // Some Other Thread waiting
		}
	}
	else
	{
		Dz1Error _result, *resultp = result ? result : &_result;

		h->joinning = DZ1_TASK_JOIN_STATUS_JOINING;
		if ((err = Dz1Thread_wait(h->id, resultp)).code) ERR_OUT(&err);
		else
		{
			h->id = 0xFFFFFFFF;
			Dz1Thread_eprintf("TaskWait(%s) is joined\n", h->name);
		}
		h->joinning = DZ1_TASK_JOIN_STATUS_JOINED;
	}

	return err;
}

u32_t Dz1Task_getQueueID(Dz1Task *t)
{
	u32_t ret = -1;
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)t;
	if (h) ret = h->queue_id;
	return ret;
}

str_t Dz1Task_getName(Dz1Task *t)
{	// for debug log
	str_t ret = NULL;
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)t;
	if (h) ret = h->name;
	return ret;
}

u32_t Dz1Task_getThread(Dz1Task *t)
{
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)t;
	return h->id;
}

bool_t Dz1Task_tossSigMsg(Dz1Task *ptr, Dz1TaskSigMsg **_sg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;
	Dz1SigMsg **sg = (Dz1SigMsg **)_sg;
	if (Dz1SigMsgQueue_toss(h->queue_id, sg, errp) == FALSE) ERR_OUT(errp);
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1Task_post(Dz1Task *ptr, u32_t src_queue_id, u32_t type, void **msg, Dz1DelFunc del, Dz1DumpFunc dump,
					  Dz1Error *initialStatus, Dz1TaskSigMsgCallbackFunc msgTerm, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;

	if ((err = Dz1Task_queuePost(h->queue_id, src_queue_id, type, msg, del, dump, initialStatus, msgTerm, param)).code) ERR_OUT(&err);

	return err;
}

Dz1Error Dz1Task_call(Dz1Task *ptr, u32_t src_queue_id, u32_t type, void *msg, Dz1DumpFunc dump, Dz1Error *initialStatus, u64_t *wait_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskThreadHandle *h = (Dz1TaskThreadHandle *)ptr;

	if ((err = Dz1Task_queueCall(h->queue_id, src_queue_id, type, msg, dump, initialStatus, wait_us)).code) ERR_OUT(&err);

	return err;
}

Dz1Error Dz1Task_queuePost(u32_t dst_queue_id, u32_t src_queue_id,
						   u32_t type, void **msg, Dz1DelFunc del, Dz1DumpFunc dump,
						   Dz1Error *initialStatus, Dz1TaskSigMsgCallbackFunc msgTerm, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1SigMsgQueue_post(dst_queue_id, src_queue_id,
								   type, msg, del, dump,
								   initialStatus, msgTerm, param)).code) ERR_OUT(&err);
	return err;
}

Dz1Error Dz1Task_queueCall(u32_t dst_queue_id, u32_t src_queue_id,
						   u32_t type, void *msg, Dz1DumpFunc dump,
						   Dz1Error *initialStatus, u64_t *wait_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1SigMsgQueue_call(dst_queue_id, src_queue_id,
								   type, msg, dump,
								   initialStatus, wait_us)).code) ERR_OUT(&err);
	return err;
}

/*
Dz1Error Dz1TaskSigMsg_post(void *tDest, void *tSrc, u32_t type, Dz1TaskSigMsg **sg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskThreadHandle *dst = (Dz1TaskThreadHandle *)tDest;
	Dz1TaskThreadHandle *src = (Dz1TaskThreadHandle *)tSrc;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Dz1SigMsgQueue_postSig(dst->queue_id, src == NULL ? (u32_t)-1 : src->queue_id, type, sg)).code) ERR_OUT(&err);
	return err;
}
*/

Dz1TaskSigMsg *Dz1TaskSigMsg_dataWrapper(void **data, Dz1DelFunc dataDel, Dz1DumpFunc dataDump, Dz1Error *err)
{
	Dz1SigMsg *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (data == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1SigMsg_new(-1, -1, -1, (*data), dataDel, dataDump, NULL, errp)) == NULL) ERR_OUT(errp);
	else (*data) = NULL;

	return ret;
}

Dz1TaskSigMsg *Dz1TaskSigMsg_dataWrapperWithType(u32_t type, void **data, Dz1DelFunc dataDel, Dz1DumpFunc dataDump, Dz1Error *err)
{
	Dz1SigMsg *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (data == NULL)
	{
		if ((ret = Dz1SigMsg_new(-1, -1, type, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	}
	else
	{
		if ((ret = Dz1SigMsg_new(-1, -1, type, (*data), dataDel, dataDump, NULL, errp)) == NULL) ERR_OUT(errp);
		else if (dataDel != NULL) (*data) = NULL;
	}

	return ret;
}
