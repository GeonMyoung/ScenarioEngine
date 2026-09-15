#include "dz1_thread.h"
#include "dz1_thread_pool.h"
#include "dz1_thread_log.h"

////////////////////////////////////////////////////////////////////////////////
// Thread LogOUT Related
////////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1Thread_setLogLevel(u32_t id, Dz1ThreadLogLevel level)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int idx = id & 0x0000FFFF;
	if (idx >= DZ1_THREAD_MAX) Dz1Error_set(&err, ESRCH);
	else
	{
		pthread_mutex_lock(&thread_pool->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

		if (Dz1ThreadPoolIndex_isAllocatedId(&thread_pool->index, id) && thread_pool->table[idx] && thread_pool->table[idx]->id == id)
			thread_pool->table[idx]->level = level | DZ1_THREAD_LOG_CRITICAL | DZ1_THREAD_LOG_ERROR;
		else Dz1Error_set(&err, ESRCH);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
	}
	return err;
}
Dz1Error Dz1Thread_clrLogLevel(u32_t id, Dz1ThreadLogLevel level)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int idx = id & 0x0000FFFF;
	if (idx >= DZ1_THREAD_MAX) Dz1Error_set(&err, ESRCH);
	else
	{
		level &= ~(DZ1_THREAD_LOG_CRITICAL | DZ1_THREAD_LOG_ERROR);	// don't clear this level

		pthread_mutex_lock(&thread_pool->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

		if (Dz1ThreadPoolIndex_isAllocatedId(&thread_pool->index, id) && thread_pool->table[idx] && thread_pool->table[idx]->id == id)
			thread_pool->table[idx]->level &= ~level;
		else Dz1Error_set(&err, ESRCH);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
	}
	return err;
}

void Dz1Thread_modLogLevelAll(bool_t is_set, Dz1ThreadLogLevel level)
{
	u32_t i;
	pthread_mutex_lock(&thread_pool->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
	for (i = 0; i < DZ1_THREAD_MAX; i++)
	{
		if (Dz1BitsUnit_isSet(thread_pool->index.alloc[i / DZ1_BITS_UNIT_SIZE_BIT], i))
		{
			u32_t dst = thread_pool->table[i]->level;
			dst = is_set ? (dst | level) : (dst & ~level);
			thread_pool->table[i]->level = dst;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
}


bool_t _Dz1Thread_getLogLevel(u32_t id, Dz1ThreadLogLevel *level, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int idx = id & 0x0000FFFF;
	if (idx >= DZ1_THREAD_MAX) Dz1Error_set(errp, ESRCH);
	else
	{
		pthread_mutex_lock(&thread_pool->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);

		if (Dz1ThreadPoolIndex_isAllocatedId(&thread_pool->index, id) && thread_pool->table[idx] && thread_pool->table[idx]->id == id)
		{
			*level = thread_pool->table[idx]->level;
			Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, ESRCH);

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&thread_pool->lock);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1Thread_getLogLevel(u32_t id, Dz1ThreadLogLevel *level)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1Thread_getLogLevel(id, level, errp) == FALSE) { }
	return err;
}

void _Dz1Thread_tlog(int tab, const char *fmt, ...)
{
	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	va_list ap;
	va_start(ap, fmt);
	Dz1Console_etvprintf(con, tab, fmt, ap);
	va_end(ap);
}

void Dz1Thread_tlog(Dz1ThreadLogLevel level, int tab, const char *fmt, ...)
{
	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	if ((e->level & level) == level)
	{
		va_list ap;
		va_start(ap, fmt);
		Dz1Console_etvprintf(con, tab, fmt, ap);
		va_end(ap);
	}
}

void _Dz1Thread_log(const char *fmt, ...)
{
	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	va_list ap;
	va_start(ap, fmt);
	Dz1Console_etvprintf(con, 0, fmt, ap);
	va_end(ap);
}

void Dz1Thread_log(Dz1ThreadLogLevel level, const char *fmt, ...)
{
	Dz1ThreadEntry *e = _Dz1Thread_self();
	Dz1Console *con = Dz1Thread_getOwnConsole();
	if ((e->level & level) == level)
	{
		va_list ap;
		va_start(ap, fmt);
		Dz1Console_etvprintf(con, 0, fmt, ap);
		va_end(ap);
	}
}
