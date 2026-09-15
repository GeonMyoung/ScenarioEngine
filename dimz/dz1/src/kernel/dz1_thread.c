#include<dz1.h>
#ifdef UNIX_SYSTEM
#include <sys/time.h>
#else
#ifndef __BORLANDC__
#include <io.h>
#endif
#include <fcntl.h>
#endif

#include <dz1_cleanup.h>

#include <dz1_thread_stdio.h>
#include "dz1_thread.h"
#include "dz1_console.h"

pthread_mutex_t	 dz1DefConLock = PTHREAD_MUTEX_INITIALIZER;
Dz1Console		*dz1DefCon = NULL;
Dz1ConsoleMode	 dz1DefConMode = Dz1ConsoleMode_mbcs;

static void dz1DefCon_clean(void *ptr)
{
	if (dz1DefCon)
	{
		Dz1ConsoleTTY_sizeTraceOff(dz1DefCon);
		Dz1Console_del(dz1DefCon);
		dz1DefCon = NULL;
	}
}

static Dz1Console *dz1DefCon_init(void)
{
	pthread_mutex_lock(&dz1DefConLock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1DefConLock);

	if (dz1DefCon == NULL)
	{
#ifndef UNIX_SYSTEM
#ifdef __BORLANDC__
		int fd_in = 0;
		int fd_out = 1;
#else // __BORLANDC__
		int fd_in = _fileno(stdin);
		int fd_out = _fileno(stdout);
		int fd_err = _fileno(stderr);
		switch(dz1DefConMode)
		{
		case Dz1ConsoleMode_wide:
//			_setmode(fd_in, _O_U16TEXT);
			_setmode(fd_out, _O_U16TEXT);
			_setmode(fd_err, _O_U16TEXT);
			break;
		default:
		case Dz1ConsoleMode_mbcs:
			break;
		}
#endif // __BORLANDC__
#else // UNIX_SYSTEM
		int fd_in = fileno(stdin);
		int fd_out = fileno(stdout);
		//int fd_err = fileno(stderr);
#endif // UNIX_SYSTEM
		if ((dz1DefCon = Dz1ConsoleTTY_new(fd_in, fd_out, NULL)) == NULL) no_con_err_out("dz1DefCon_init", "TTY Creation fail");
		else
		{
			Dz1Error err = DZ1_ERROR_INITIALIZER;

			pthread_cleanup_push(Dz1Console_delAndSetNull, (void *)&dz1DefCon);

			if ((err = Dz1Cleanup_reg(dz1DefCon_clean, NULL)).code == 0)
				Dz1ConsoleTTY_sizeTraceOn(dz1DefCon);

			pthread_cleanup_pop(err.code); // (Dz1Console_delAndSetNull, (void *)&dz1DefCon);
		}
	}

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1DefConLock);

	return dz1DefCon;
}

Dz1ConsoleMode dz1DefCon_getMode(void)
{
	Dz1ConsoleMode ret = Dz1ConsoleMode_mbcs;
	pthread_mutex_lock(&dz1DefConLock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1DefConLock);
	ret = dz1DefConMode;
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1DefConLock);
	return ret;
}

void dz1DefCon_setMode(bool_t wide)
{
	pthread_mutex_lock(&dz1DefConLock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1DefConLock);
	if (wide) dz1DefConMode = Dz1ConsoleMode_wide;
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1DefConLock);
}

bool_t dz1DefCon_isWide(void)
{
	Dz1ConsoleMode mode = dz1DefCon_getMode();
	return mode == Dz1ConsoleMode_wide ? TRUE : FALSE;
}

static Dz1ThreadEntry *defTh = NULL;
Dz1Console *Dz1Thread_getOwnConsole(void)
{
	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *ret = e->con;
	if (ret == NULL)
	{
		if ((ret = dz1DefCon) == NULL)
			dz1DefCon = ret = dz1DefCon_init();
	}
	return ret;
}

u32_t Dz1Thread_init(Dz1ThreadLogLevel level, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1ThreadEntry *e = NULL;

	if ((defTh = e = Dz1ThreadPool_reg(thread_pool, level, NULL, (str_t)"(system)", NULL, NULL, errp)) == NULL)
		no_con_err_out("Dz1Thread_init", "thread_registration fail");

	if (e) ret = e->id;

	return ret;
}

void Dz1Thread_clean(void)
{
	if (defTh) Dz1ThreadPool_dereg(thread_pool, defTh);
}

typedef enum
{
	Dz1ThreadMainStatus_initialized,
	Dz1ThreadMainStatus_success,
	Dz1ThreadMainStatus_fail
} Dz1ThreadMainStatus;

typedef struct Dz1ThreadArg
{
	pthread_mutex_t lock;
	pthread_cond_t cond;
	Dz1ThreadMainStatus status;

	Dz1ThreadLogLevel level;
	Dz1Console *con;
	str_t name;
	Dz1ThreadFunc func;
	void *arg;

	u32_t id;
} Dz1ThreadArg;

static void Dz1ThreadPool_regCancel(void *arg)
{
	Dz1ThreadEntry *e = (Dz1ThreadEntry *)arg;
	Dz1ThreadPool_dereg(thread_pool, e);
}

static void Dz1ThreadEntry_setIntrErr(void *ptr)
{
	Dz1Error *err = (Dz1Error *)ptr;
	Dz1Error_set(err, EINTR);
}

static void _Dz1ThreadBarrier_init(Dz1ThreadBarrier *barrier)
{
	if (barrier != NULL)
	{
		Dz1ThreadInitEntry *i = NULL;
		for (i = barrier->head; i != NULL; i = i->next)
			if (i->init != NULL) i->init();
	}
}

static void _Dz1ThreadBarrier_cleanup(void *ptr)
{
	Dz1ThreadBarrier *barrier = (Dz1ThreadBarrier *)ptr;
	if (barrier != NULL)
	{
		Dz1ThreadCleanupEntry *i;
		for (i = barrier->tail; i != NULL; i = i->prev)
			if (i->cleanup != NULL) i->cleanup();
	}
}

bool_t Dz1ThreadBarrier_reg(Dz1ThreadInitEntry *init, Dz1ThreadCleanupEntry *clean, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (init == NULL || clean == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1ThreadPool_addBarrier(thread_pool, init, clean, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static void *Dz1Thread_main(void *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = NULL;
	Dz1ThreadArg *p = (Dz1ThreadArg *)arg;
	Dz1ThreadBarrier barrier = { NULL, NULL };

	int old_cancel_state;

	Dz1ThreadEntry *e = NULL;
	Dz1ThreadFunc func = NULL;
	void *func_arg = NULL;

	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	pthread_mutex_lock(&p->lock);

	func = p->func;
	func_arg = p->arg;
	if ((e = Dz1ThreadPool_reg(thread_pool, p->level, p->con, p->name, p->func, &barrier, &err)) == NULL) p->status = Dz1ThreadMainStatus_fail;
	else
	{
		errp = e->err;
		memset(errp, 0, sizeof(Dz1Error));

		p->id = e->id;
		p->status = Dz1ThreadMainStatus_success;
	}

	pthread_cond_signal(&p->cond);							// destroy p(=Dz1ThreadArg)

	pthread_mutex_unlock(&p->lock);
	pthread_setcancelstate(old_cancel_state, NULL);

	pthread_cleanup_push(Dz1ThreadPool_regCancel, (void *)e); // De-register Thread Entry & Clean Allocate Bit of Thread Pool

	_Dz1ThreadBarrier_init(&barrier);
	pthread_cleanup_push(_Dz1ThreadBarrier_cleanup, (void *)&barrier);

	Dz1Error_set(errp, 0);
	pthread_cleanup_push(Dz1ThreadEntry_setIntrErr, (void *)errp);	// Set EINTR when Thread Canceled

	if (e)
	{
		pthread_testcancel();

		*errp = func(func_arg);

		pthread_testcancel();
	}

	pthread_cleanup_pop(0); // (Dz1ThreadEntry_setIntrErr, (void *)errp);

	pthread_cleanup_pop(1); //  (_Dz1ThreadBarrier_cleanup, (void *)&p->barrier);

	pthread_cleanup_pop(1); // (Dz1ThreadPool_regCancel, (void *)e);

	pthread_exit(NULL);

	return NULL;
}

Dz1ThreadEntry *_Dz1Thread_self(void)
{
	Dz1ThreadEntry key, *ret = NULL;
	key.th = pthread_self();

	if (dz1DefCon == NULL) dz1DefCon = dz1DefCon_init();
	if (defTh == NULL) Dz1Thread_init(DZ1_THREAD_LOG_BASIS, NULL);

	pthread_mutex_lock(&thread_pool->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

	ret = Dz1ThreadHash_find(&thread_pool->hash, &key);

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

	if (ret == NULL) ret = defTh;

// 	if (ret != NULL)
// 	{
// 		if (ret-> con == NULL) no_con_err_out("_Dz1Thread_self", "con == NULL");
// 	}

	return ret == NULL ? defTh : ret;
}

// static Dz1Console *getMyConsole(void)
// {
// 	Dz1ThreadEntry *e = _Dz1Thread_self();
// 
// 	return e ? e-> con : NULL;
// }

// pthread_create :: 0 or EAGAIN = Not enough resource or too many thread
Dz1Error _Dz1Thread_create(u32_t *id, const char *name, Dz1ThreadFunc func, void *func_arg, Dz1ThreadLogLevel level)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	pthread_t th;
	Dz1ThreadArg arg = 
	{
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_COND_INITIALIZER,
		Dz1ThreadMainStatus_initialized,

		0,
		NULL,
		NULL,
		NULL,
		NULL,

		DZ1_THREAD_INVALID
	};

	int old_cancel_state, code;

	pthread_cleanup_push((Dz1DelFunc)pthread_mutex_destroy, (void *)&arg.lock);
	pthread_cleanup_push((Dz1DelFunc)pthread_cond_destroy, (void *)&arg.cond);

	arg.level = level;
//	arg.con = getMyConsole();
	arg.name = (char *)name;
	arg.func = func;
	arg.arg = func_arg;

	pthread_mutex_lock(&arg.lock);
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);

	if ((code = pthread_create(&th, NULL, Dz1Thread_main, (void *)&arg))) Dz1Error_set(&err, code);
	else
	{
		while(arg.status == Dz1ThreadMainStatus_initialized)
			pthread_cond_wait(&arg.cond, &arg.lock);
	}

	if (arg.status == Dz1ThreadMainStatus_success)
	{
		*id = arg.id;
		Dz1Error_set(&err, 0);
	}
	else Dz1Error_set(&err, EAGAIN);

	pthread_setcancelstate(old_cancel_state, NULL);
	pthread_mutex_unlock(&arg.lock);

	pthread_cleanup_pop(1); // (pthread_cond_destroy, (void *)&arg.cond);
	pthread_cleanup_pop(1); // (pthread_mutex_destroy, (void *)&arg.lock);

	pthread_testcancel();

	return err;
}

// pthread_self :: thread id
u32_t Dz1Thread_self(void)
{
	u32_t ret = DZ1_THREAD_INVALID;
	Dz1ThreadEntry *e = _Dz1Thread_self();

	ret = e ? e->id : DZ1_THREAD_INVALID;

	return ret;
}

static Dz1Error get_pthreadAllocated(u32_t id, pthread_t *th)
{
	int idx = id & 0x0000FFFF;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	pthread_mutex_lock(&thread_pool->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

//	if (Dz1ThreadPoolIndex_isAllocatedId(&thread_pool->index, id) && (thread_pool->table[idx]->id == id)) (*th) = thread_pool->table[idx]->th;
	if (Dz1ThreadPoolIndex_isAllocatedId(&thread_pool->index, id)) (*th) = thread_pool->threads[idx];
	else Dz1Error_set(&err, ESRCH);

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

	return err;
}

// pthread_cancel :: 0 or ESRCH = No Such Thread ID
Dz1Error Dz1Thread_stop(u32_t id, int detach)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	pthread_t th;

	// Thread what be Canceled should be allocated
	if ((err = get_pthreadAllocated(id, &th)).code == 0)
	{
		int code = 0;
		if ((code = pthread_cancel(th))) Dz1Error_set(&err, code);
		else if (detach)
		{
			pthread_mutex_lock(&thread_pool->lock);
			pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

			pthread_detach(th);
			Dz1ThreadPoolIndex_deactivate(&thread_pool->index, id); // POOL Active Bit Clear

			pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
		}
	}

	return err;
}

static Dz1Error get_pthreadActivated(u32_t id, pthread_t *th)
{
	int idx = id & 0x0000FFFF;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	pthread_mutex_lock(&thread_pool->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

	if (Dz1ThreadPoolIndex_isActivatedId(&thread_pool->index, id)) (*th) = thread_pool->threads[idx];
	else Dz1Error_set(&err, ESRCH);

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

	return err;
}

Dz1Error Dz1Thread_wait(u32_t id, Dz1Error *result)
{
	u32_t idx = id & 0xFFFF;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Error _result, *resultp = result ? result : &_result;
	pthread_t th;

	// Thread that be joined should be activated
	if ((err = get_pthreadActivated(id, &th)).code == 0)
	{	// Active
		int code = 0;
		Dz1ThreadStatus oldStatus = Dz1Thread_getStatus();
		Dz1Thread_setStatus(Dz1ThreadStatus_joinning);
		pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&oldStatus);

		if ((code = pthread_join(th, NULL))) Dz1Error_set(&err, code);
		else
		{
			pthread_mutex_lock(&thread_pool->lock);
			pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

			*resultp = thread_pool->ret[idx];
			Dz1ThreadPoolIndex_deactivate(&thread_pool->index, id);

			pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
		}

		pthread_cleanup_pop(1); // ((Dz1CalceFunc)Dz1Thread_setStatusCleanup, (void *)&oldStatus);
	}
	else if (err.code != ESRCH) ERR_OUT(&err);

	return err;
}

static void _Dz1ThreadA_dumpEntry(Dz1Console *con, int tab)
{
	u32_t i;
	for (i = 0; i < DZ1_THREAD_MAX; i++)
	{
		if (Dz1BitsUnit_isSet(thread_pool->index.alloc[i / DZ1_BITS_UNIT_SIZE_BIT], i))
			Dz1ThreadEntryA_dump(con, thread_pool->table[i], tab);
	}
}

static void _Dz1ThreadA_dumpPool(Dz1Console *con, int tab)
{
	u32_t i;
	for (i = 0; i < DZ1_THREAD_MAX / DZ1_BITS_UNIT_SIZE_BIT; i++)
	{
		Dz1ConsoleA_tprintf(con, tab, "0x%08X ", thread_pool->index.active[i]);
		if ((i + 1) % 4 == 0) Dz1ConsoleA_tprintf(con, 0, "\n");
	}
	Dz1ThreadA_tprintf(tab, "[Balance Ratio : %.3f]\n", Dz1ThreadHash_analysis(&thread_pool->hash) * 100);
}

void _Dz1ThreadA_dump(bool_t dump_pool, int tab)
{
	Dz1Console *con = Dz1Thread_getOwnConsole();
	pthread_mutex_lock(&thread_pool->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
	_Dz1ThreadA_dumpEntry(con, tab);
	if (dump_pool) _Dz1ThreadA_dumpPool(con, tab);
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
}
#ifndef UNIX_SYSTEM
static void _Dz1ThreadW_dumpEntry(Dz1Console *con, int tab)
{
	u32_t i;
	for (i = 0; i < DZ1_THREAD_MAX; i++)
	{
		if (Dz1BitsUnit_isSet(thread_pool->index.alloc[i / DZ1_BITS_UNIT_SIZE_BIT], i))
			Dz1ThreadEntryW_dump(con, thread_pool->table[i], tab);
	}
}

static void _Dz1ThreadW_dumpPool(Dz1Console *con, int tab)
{
	u32_t i;
	for (i = 0; i < DZ1_THREAD_MAX / DZ1_BITS_UNIT_SIZE_BIT; i++)
	{
		Dz1ConsoleW_tprintf(con, tab, L"0x%08X ", thread_pool->index.active[i]);
		if ((i + 1) % 4 == 0) Dz1ConsoleW_tprintf(con, 0, L"\n");
	}
	Dz1ThreadA_tprintf(tab, "[Balance Ratio : %.3f]\n", Dz1ThreadHash_analysis(&thread_pool->hash) * 100);
}

void _Dz1ThreadW_dump(bool_t dump_pool, int tab)
{
	Dz1Console *con = Dz1Thread_getOwnConsole();
	pthread_mutex_lock(&thread_pool->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
	_Dz1ThreadW_dumpEntry(con, tab);
	if (dump_pool) _Dz1ThreadW_dumpPool(con, tab);
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
}
#endif

Dz1ThreadStatus Dz1Thread_getStatus(void)
{
	Dz1ThreadStatus ret = Dz1ThreadStatus_max;
	Dz1ThreadEntry *e = _Dz1Thread_self();

	ret = e ? e->status : Dz1ThreadStatus_max;

	return ret;
}

void Dz1Thread_setStatus(Dz1ThreadStatus status)
{
	Dz1ThreadEntry *e = _Dz1Thread_self();

	if (e) e->status = status;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1Thread_setConsole
bool_t Dz1Thread_setConsole(Dz1ThreadConsolPrompt prompt, 
							void *priv, Dz1DelFunc priv_del, 
							Dz1ThreadIOWaitF wait,
							Dz1ThreadIOGetChF getch,
							Dz1ThreadIOWriteF write,
							Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Console *new_con = Dz1Console_new((Dz1ConsolePromptMode)prompt, NULL, errp);
	if (new_con == NULL) { }
	else
	{
		Dz1ConsolePlatform *pf = NULL;
		pthread_cleanup_push(Dz1Console_delAndSetNull, (void *)&new_con);
#ifndef UNIX_SYSTEM
		new_con->cr = Dz1ConsoleCR_CRLF;
#endif
		if ((new_con->platform = pf = Dz1ConsolePlatform_new(priv, priv_del, wait, getch, write, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1ThreadEntry *e = _Dz1Thread_self();
			if (e->con != NULL) Dz1Console_delAndSetNull(&e->con);
			e->con = new_con;
			new_con = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Console_delAndSetNull, (void *)&new_con);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1Thread_setConsole
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Thread Stack Trace API
///////////////////////////////////////////////////////////////////////////////
#ifdef DZ1_THREAD_STACK_TRACE
bool_t Dz1Thread_stackPush(Dz1ThreadStack *p)
{
	bool_t ret = FALSE;

	Dz1ThreadEntry *e = _Dz1Thread_self();

	if (e)
	{
		p->next = e->stack;
		e->stack = p;
		ret = TRUE;
	}

	return ret;
}

void Dz1Thread_stackPop(void *ptr)
{
	Dz1ThreadEntry *e = _Dz1Thread_self();

	if (e) e->stack = e->stack ? e->stack->next : NULL;
}
#endif

