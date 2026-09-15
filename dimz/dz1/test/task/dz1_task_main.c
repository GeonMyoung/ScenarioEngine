#ifndef UNIX_SYSTEM
#ifdef CPP_BUILDER_WIN32
#include <stdio.h>
#pragma hdrstop
#endif // CPP_BUILDER_WIN32
#include <tchar.h>
#endif // UNIX_SYSTEM
#include <dz1_cleanup.h>
#include <dz1_time.h>
#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_shell.h>
#include <dz1_task.h>
#include <dz1_task_timer.h>

static FILE *logFP = NULL;
static void _memoryExport(void *ptr)
{
	if (logFP != NULL)
	{
		Dz1Mem_export(logFP, TRUE);
		fflush(logFP);
	}
}

static void _outputHook(void *ptr, u8_t *data, size_t size)
{
	if (logFP != NULL)
	{
		fwrite(data, size, 1, logFP);
		fflush(logFP);
	}
}

static int Dz1SigMsg_cmp(void *a, void *b)
{
	u32_t A = Dz1TaskSigMsg_getType(a);
	u32_t B = Dz1TaskSigMsg_getType(b);

	return (int)(A - B);
}

typedef struct TestEnv
{
	void *task;
} TestEnv;

static void arg_del(void *ptr) { Dz1Thread_printf(Dz1Text("arg_del() : called\n")); }

typedef struct TaskEnv
{
	void *sig_msg;
} TaskEnv;

static Dz1Error init(void **user_resource, void *tSelf, str_t name, u32_t my_queue_id, void *user_arg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (((*user_resource) = (void *)Dz1Calloc(sizeof(TaskEnv), 1, errp)) == NULL) ERR_OUT(errp);
	else Dz1Thread_printf(Dz1Text("init() : called(%p)\n"), *user_resource);
	return err;
}
static void except(void *user_arg, void *user_resource, void *timer, Dz1Error *reason)
{
	Dz1Thread_printf(Dz1Text("except() : called - user_arg = %p, user_resource = %p, timer = %p\n"), user_arg, user_resource, timer);
	ERR_OUT(reason);
}
static void cleanup(void *p)
{
	Dz1Thread_printf(Dz1Text("cleanup() : called(%p)\n"), p);
	if (!p) return;
	Dz1Free(p);
}

static Dz1TaskProcStatus exactMsgProc(void *arg, void *ptr, void *timer, void **sig_msg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	u32_t type = Dz1TaskSigMsg_getType(*sig_msg);

	Dz1TaskSigMsg_setErr(*sig_msg, EINVAL);
	Dz1Thread_printf(Dz1Text("exactMsgProc() : type = %08X\n"), type);

	return ret;
}

static Dz1TaskProcStatus callSignaller(void *user_arg, void *user_resource, void *timer, void **timer_data, Dz1Error *err)
{
	void *sig_msg = *timer_data;
	Dz1Thread_printf(Dz1Text("callSignaller() : called\n"));
	Dz1TaskSigMsg_setErr(sig_msg, E2BIG);
	Dz1TaskSigMsg_termDelAndSetNull(timer_data);
	return Dz1TaskProcStatus_processed;
}

static Dz1TaskProcStatus callDefferrer(void *arg, void *ptr, void *timer, void **sig_msg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	u32_t type = Dz1TaskSigMsg_getType(*sig_msg);

	Dz1Thread_printf(Dz1Text("callDefferrer() : type = %08X\n"), type);
#ifdef SINGLE_TIMER
	if ((*errp = Dz1TaskSingleTimer_set(timer, 2000000, 1, *sig_msg, NULL, callSignaller, FALSE)).code) ERR_OUT(errp);
	else *sig_msg = NULL;
#else
	if ((*errp = Dz1TaskTimer_reg(timer, 2000000, (void **)sig_msg, NULL, callSignaller, FALSE)).code) ERR_OUT(errp);
	else *sig_msg = NULL;
#endif
	Dz1Thread_printf(Dz1Text("callDefferrer() : *sig_msg = %p\n"), *sig_msg);

	return ret;
}

static Dz1TaskProcStatus mask0MsgProc(void *arg, void *ptr, void *timer, void **sig_msg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	u32_t type = Dz1TaskSigMsg_getType(*sig_msg);

	Dz1Thread_printf(Dz1Text("mask0MsgProc() : type = %08X\n"), type);

	return ret;
}

static Dz1TaskProcStatus mask1MsgProc(void *arg, void *ptr, void *timer, void **sig_msg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	u32_t type = Dz1TaskSigMsg_getType(*sig_msg);

	Dz1Thread_printf(Dz1Text("mask1MsgProc() : type = %08X\n"), type);

	return ret;
}

static Dz1TaskProcStatus mask2MsgProc(void *arg, void *ptr, void *timer, void **sig_msg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	u32_t type = Dz1TaskSigMsg_getType(*sig_msg);

	Dz1Thread_printf(Dz1Text("mask2MsgProc() : type = %08X\n"), type);

	return ret;
}

static Dz1TaskProcStatus defaultMsgProc(void *arg, void *ptr, void *timer, void **sig_msg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	u32_t type = Dz1TaskSigMsg_getType(*sig_msg);

	Dz1Thread_printf(Dz1Text("defaultMsgProc() : type = %08X\n"), type);

	return ret;
}

static void _msgTerm(void *ptr, void **msg, bool_t isAbnormal)
{
	Dz1Thread_printf(Dz1Text("_msgTerm() : ptr = %p, msg = %p\n"), ptr, msg);
	if (msg) Dz1Thread_printf(Dz1Text("_msgTerm() : *msg = %p\n"), *msg);
}

static void testfunc_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <create|start|stop|wait|post|call|calltest|del>\n"), n); }
static Dz1ShellCmdReturn testfunc(void *ptr, int argc, TCHAR *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv *env = (TestEnv *)ptr, *_env = env;
	if (argc < 2) testfunc_usage(argv[0]);
	else if (Dz1STRCMP(argv[1], Dz1Text("create"))==0 || Dz1STRCMP(argv[1], Dz1Text("c"))==0)
	{
		if (env->task) Dz1Thread_printf(Dz1Text("Already Created\n"));
		else if ((env->task = Dz1Task_new("Test", 16, (void **)&_env, arg_del, Dz1SigMsg_cmp, init, except, cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&env->task);
			if (0) { }
			else if ((err = Dz1Task_regMsg(env->task, DZ1_TASK_MSG_EXACT(0x00000001), exactMsgProc)).code) ERR_OUT(errp);
			else if ((err = Dz1Task_regMsg(env->task, DZ1_TASK_MSG_EXACT(0x00000002), exactMsgProc)).code) ERR_OUT(errp);
			else if ((err = Dz1Task_regMsg(env->task, DZ1_TASK_MSG_EXACT(0x00000003), callDefferrer)).code) ERR_OUT(errp);
			else if ((err = Dz1Task_regMsg(env->task, 0xFFFFFF00, 0xFFFFFF00, mask0MsgProc)).code) ERR_OUT(errp);
			else if ((err = Dz1Task_regMsg(env->task, 0xFFFF0000, 0xFFFF0000, mask1MsgProc)).code) ERR_OUT(errp);
			else if ((err = Dz1Task_regMsg(env->task, 0xFF000000, 0xFF000000, mask2MsgProc)).code) ERR_OUT(errp);
			else if ((err = Dz1Task_regMsg(env->task, DZ1_TASK_MSG_DEFAULT, defaultMsgProc)).code) ERR_OUT(errp);
			else Dz1Thread_printf(Dz1Text("Success\n"));
			pthread_cleanup_pop(err.code); // (Dz1Task_delAndSetNull, (void *)&env->task);
		}
	}
	else if (Dz1STRCMP(argv[1], Dz1Text("start"))==0 || Dz1STRCMP(argv[1], Dz1Text("s"))==0)
	{
		if (env->task == NULL) Dz1Thread_printf(Dz1Text("Not Created\n"));
		else if ((err = Dz1Task_start(env->task, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(errp);
		else Dz1Thread_printf(Dz1Text("Success\n"));
	}
	else if (Dz1STRCMP(argv[1], Dz1Text("stop"))==0 || Dz1STRCMP(argv[1], Dz1Text("x"))==0)
	{
		if (env->task == NULL) Dz1Thread_printf(Dz1Text("Not Created\n"));
		else if ((err = Dz1Task_stop(env->task, FALSE)).code) ERR_OUT(errp);
		else Dz1Thread_printf(Dz1Text("Success\n"));
	}
	else if (Dz1STRCMP(argv[1], Dz1Text("wait"))==0 || Dz1STRCMP(argv[1], Dz1Text("w"))==0)
	{
		Dz1Error result = DZ1_ERROR_INITIALIZER;
		if (env->task == NULL) Dz1Thread_printf(Dz1Text("Not Created\n"));
		else if ((err = Dz1Task_wait(env->task, &result)).code) ERR_OUT(errp);
		else Dz1Thread_printf(Dz1Text("Success\n"));
	}
	else if (Dz1STRCMP(argv[1], Dz1Text("del"))==0 || Dz1STRCMP(argv[1], Dz1Text("d"))==0)
	{
		if (env->task == NULL) Dz1Thread_printf(Dz1Text("Not Created\n"));
		else if ((err = Dz1Task_del(env->task)).code) ERR_OUT(errp);
		else
		{
			env->task = NULL;
			Dz1Thread_printf(Dz1Text("Done\n"));
		}
	}
	else if (Dz1STRCMP(argv[1], Dz1Text("post"))==0 || Dz1STRCMP(argv[1], Dz1Text("p"))==0)
	{
		if (argc!= 3) Dz1Thread_printf(Dz1Text("Usage] %s post <msg_type>\n)"), argv[0]);
		else
		{
			u32_t msg_type = Dz1StrTo32(argv[2]);
			Dz1Thread_printf(Dz1Text("msg_type = %s->%08X\n"), argv[2], msg_type);
			if ((err = Dz1Task_post(env->task, DZ1_TASK_QUEUE_NONE, msg_type, NULL, NULL, NULL, NULL, _msgTerm, (void *)env)).code) ERR_OUT(errp);
		}
	}
	else if (Dz1STRCMP(argv[1], Dz1Text("call"))==0 || Dz1STRCMP(argv[1], Dz1Text("a"))==0)
	{
		if (argc!= 3) Dz1Thread_printf(Dz1Text("Usage] %s call <msg_type>\n"), argv[0]);
		else
		{
			u32_t msg_type = Dz1StrTo32(argv[2]);
			Dz1Thread_printf(Dz1Text("msg_type = %08X\n"), msg_type);
			if ((err = Dz1Task_call(env->task, DZ1_TASK_QUEUE_NONE, msg_type, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		}
	}
	else if (Dz1STRCMP(argv[1], Dz1Text("calltest"))==0 || Dz1STRCMP(argv[1], Dz1Text("t"))==0)
	{
		u64_t wait_us = 1000000;
		if ((err = Dz1Task_call(env->task, DZ1_TASK_QUEUE_NONE, 0x00000003, NULL, NULL, NULL, &wait_us)).code) ERR_OUT(errp);
	}
	else testfunc_usage(argv[0]);

	return Dz1ShellCmdReturn_ok;
}

static Dz1ShellCmdReturn timefunc(void *ptr, int argc, Dz1Str argv[])
{
	struct tm tm;
	tm.tm_year = (1999 - 1900);
	tm.tm_mon = 0;
	tm.tm_mday = 1;
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	{
		time_t _t = mktime(&tm);
		struct timeval t = { (long)_t, 0 };
		settimeofday(&t, NULL);
	}
	return Dz1ShellCmdReturn_ok;
}

static Dz1ShellCmdReturn mutexFunc(void *ptr, int argc, Dz1Str argv[])
{
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&m);

	pthread_mutex_unlock(&m);

	pthread_mutex_destroy(&m);

	return Dz1ShellCmdReturn_ok;
}
#ifndef UNIX_SYSTEM
int _tmain(int argc, TCHAR *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_init();
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logFP = Dz1FileStream_open3(Dz1T("."), basename(argv[0]), Dz1T("log.txt"), Dz1T("wb"), errp)) == NULL) ERR_OUT(errp);
	else 
	{
		void *sh = NULL;
		TestEnv env = { NULL };
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
		if ((sh = Dz1Shell_new(Dz1T("win32crt"), DZ1_SHELL_CMD_ALL, 16, Dz1T("root"), Dz1T("embedded"), errp)) == NULL) ERR_OUT(errp);
#else
		if ((sh = Dz1Shell_new(Dz1T("xterm"), DZ1_SHELL_CMD_ALL, 16, Dz1T("root"), Dz1T("embedded"), errp)) == NULL) ERR_OUT(errp);
#endif
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);

			if ((err = Dz1Shell_cmdReg(sh, Dz1T("t"), testfunc, &env, Dz1T("Task Function Test Command") )).code) ERR_OUT(errp);
			else if ((err = Dz1Shell_cmdReg(sh, Dz1T("time"), timefunc, &env, Dz1T("Time Set Func") )).code) ERR_OUT(errp);
			else if ((err = Dz1Shell_cmdReg(sh, Dz1T("l"), mutexFunc, &env, Dz1T("Mutex Test") )).code) ERR_OUT(errp);
			else Dz1Shell_start(sh, NULL);

			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		}
	}
	return err.code;
}

