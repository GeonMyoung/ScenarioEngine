//#include <malloc.h>
//#include <stdio.h>

#ifdef CPP_BUILDER_WIN32
#pragma hdrstop
#endif

#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_usleep.h>
#include <dz1_malloc.h>
#include <dz1_thread.h>
#include <dz1_thread_stdio.h>
#include <dz1_sync.h>

#define TEST_CANCEL

typedef struct MyThreadArg
{
	Dz1Sync *sync;
	int status;
} MyThreadArg;

static Dz1Error testWorker(void *ptr)
{
	MyThreadArg *p = (MyThreadArg *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Thread_proc(Dz1Thread_usleep(1500000));

	Dz1Sync_lock(p->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)p->sync);

	p->status = 1;
	Dz1Sync_signal(p->sync);

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)p->sync);

	Dz1Thread_proc(Dz1Thread_usleep(1500000));

	return err;
}

static Dz1Error __testWaitor(void *ptr, bool_t *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	MyThreadArg *arg = (MyThreadArg *)ptr;
	if (arg->status != 0) *status = TRUE; else *status = FALSE;

	return err;
}

static Dz1Error _testWaitor(MyThreadArg *arg, u64_t *wait_us)
{
	return Dz1Sync_wait(arg->sync, wait_us, __testWaitor, arg);
}

Dz1Sync _sync = DZ1_SYNC_INITIALIZER;
MyThreadArg _arg = { &_sync, 0 };

static Dz1Error testWaitor(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, errWorker = DZ1_ERROR_INITIALIZER;

	u32_t id = DZ1_THREAD_INVALID;
	Dz1Sync_lock(&_sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)&_sync);

	if ((err = Dz1Thread_create(&id, testWorker, (void *)&_arg, DZ1_THREAD_LOG_BASIS)).code) Dz1Error_print(&err, 0);
	else
	{
		u64_t wait_us = 20000000;
#if 1
		Dz1Thread_call(err, _testWaitor(&_arg, &wait_us) );
		if (err.code) ERR_OUT(&err);
#else
		if ((err = Dz1Sync_timedWait(&sync, arg.status != 0, wait_us, &err)).code) Dz1Error_print(&err, 0);
#endif
		else if ((err = Dz1Thread_wait(id, &errWorker)).code) Dz1Error_print(&err, 0);
		else if (errWorker.code) { Dz1Thread_printf("testWaitor() : Worker return error\n"); Dz1Error_print(&errWorker, 1); }
		else Dz1Thread_printf("testWaitor() : Worker return success\n");
	}
	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&sync);

	return err;
}

static __inline__ void Dz1SyncTest(void)
{
	u32_t id = -1;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1Thread_create(&id, testWaitor, NULL, DZ1_THREAD_LOG_BASIS)).code) Dz1Error_print(&err, 0);
	else
	{
		Dz1Error errSync = DZ1_ERROR_INITIALIZER;
		Dz1Thread_usleep(100000);
		Dz1Thread_printf("\nDz1SyncTest() : Thread Status\n");
		Dz1Thread_dump(1);
#ifdef TEST_CANCEL
		Dz1Thread_usleep(1000000);
		if ((err = Dz1Thread_stop(id, FALSE)).code) Dz1Error_print(&err, 0); else
#endif
		if ((err = Dz1Thread_wait(id, &errSync)).code) Dz1Error_print(&err, 0);
		else if (errSync.code != 0)
		{
			Dz1Thread_printf("Dz1SyncTest() : Thread Return Error\n");
			Dz1Error_print(&errSync, 1);
		}
		else
			Dz1Thread_printf("Dz1SyncTest() : Success\n");
	}
	Dz1Thread_printf("Dz1SyncTest() : After Test\n");
	Dz1Thread_dump(1);
}

static Dz1Error testLocker(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	pthread_mutex_t *lock = (pthread_mutex_t *)ptr;
	Dz1Mutex_lock(lock);
	pthread_cleanup_push(Dz1Mutex_cancel, lock);

	Dz1Thread_usleep(1000000);

	pthread_cleanup_pop(1); // (Dz1Mutex_cancel, lock);

	return err;
}

static void testLockerCancel(void *ptr)
{
	u32_t id = *(u32_t *)ptr;
	Dz1Thread_stop(id, FALSE);
}

static __inline__ void Dz1MutexTest(void)
{
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	u32_t id0 = DZ1_THREAD_INVALID, id1 = DZ1_THREAD_INVALID;
	Dz1Error err = DZ1_ERROR_INITIALIZER, err0 = DZ1_ERROR_INITIALIZER, err1 = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1Thread_create(&id0, testLocker, (void *)&lock, DZ1_THREAD_LOG_BASIS)).code) Dz1Error_print(&err, 0);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)testLockerCancel, (void *)&id0);
		if ((err = Dz1Thread_create(&id1, testLocker, (void *)&lock, DZ1_THREAD_LOG_BASIS)).code) Dz1Error_print(&err, 0);
		else
		{
			Dz1Thread_usleep(100000);

			Dz1Thread_printf("\nDz1MutexTest() : Thread Status\n");
			Dz1Thread_dump(1);

			if ((err = Dz1Thread_wait(id1, &err1)).code) Dz1Error_print(&err, 0);
			else if (err1.code) { Dz1Thread_printf("Dz1MutexTest() : testLocker1 return error\n"); Dz1Error_print(&err1, 1); }
			else Dz1Thread_printf("Dz1MutexTest() : testLocker1 return success\n");

			Dz1Error_set(&err, 0);
		}
		pthread_cleanup_pop(err.code); // ((Dz1CancelFunc)testLockerCancel, (void *)&id0);
		if ((err = Dz1Thread_wait(id0, &err0)).code) Dz1Error_print(&err, 0);
		else if (err0.code) { Dz1Thread_printf("Dz1MutexTest() : testLocker0 return error\n"); Dz1Error_print(&err0, 1); }
		else Dz1Thread_printf("Dz1MutexTest() : testLocker0 return success\n");
	}
	Dz1Thread_printf("Dz1MutexTest() : After Test\n");
	Dz1Thread_dump(1);
}

static Dz1Error _test_th(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	return err;
}

static __inline__ void _test_th_loop(void)
{
	u32_t cnt = 0;
	u32_t th;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	while(1)
	{
		Dz1Thread_printf("Cnt = %u\n", cnt++);
		if ((*errp = Dz1Thread_create(&th, _test_th, NULL, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(errp);
		else
		{
			if ((err = Dz1Thread_stop(th, FALSE)).code) { }
			Dz1Thread_wait(th, NULL);
		}
	}
}

static void init_func_1(void)
{
	Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "INIT 1\n");
}

static void clean_func_1(void)
{
	Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "CLEAN 1\n");
}

static void init_func_2(void)
{
	Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "INIT 2\n");
}

static void clean_func_2(void)
{
	Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "CLEAN 2\n");
}

static Dz1ThreadInitEntry		_th_init_1	= Dz1ThreadInitEntryInit(init_func_1);
static Dz1ThreadCleanupEntry	_th_clean_1 = Dz1ThreadCleanupEntryInit(clean_func_1);

static Dz1ThreadInitEntry		_th_init_2 = Dz1ThreadInitEntryInit(init_func_2);
static Dz1ThreadCleanupEntry	_th_clean_2 = Dz1ThreadCleanupEntryInit(clean_func_2);

int main(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	void *sh = NULL;
	u32_t id = DZ1_THREAD_INVALID;

	int infd = fileno(stdin);
	int outfd = fileno(stdout);

	printf("in = %d, out = %d\n", infd, outfd);

	Dz1Cleanup_init();

	if (0) {}
	else if (Dz1ThreadBarrier_reg(&_th_init_1, &_th_clean_1, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1ThreadBarrier_reg(&_th_init_2, &_th_clean_2, errp) == FALSE) ERR_OUT(errp);
	else if ((id = Dz1Thread_init(DZ1_THREAD_LOG_BASIS, &err)) == DZ1_THREAD_INVALID) Dz1Error_print(&err, 0);
	else
	{
		Dz1SyncTest();
		Dz1MutexTest();
//		_test_th_loop();
#ifdef UNIX_SYSTEM
		if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 3, "root", "embedded", &err)) == NULL) ERR_OUT(&err);
#else
		if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 3, "root", "embedded", &err)) == NULL) ERR_OUT(&err);
#endif
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);

			Dz1Shell_start(sh, NULL);

			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		}
	}

	return err.code;
}

