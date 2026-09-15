#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>

#include "dz1_sigmsg.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1SigMsgSync
void Dz1SigMsgSync_lock(Dz1SigMsgSync *p)
{
//	Dz1Thread_log(DZ1_THREAD_LOG_WARN, "$$$ Dz1SigMsgSync_lock() %08X=>%p\n", Dz1Thread_self(), &p->sync);
	Dz1Sync_lock(&p->sync);
}

DZ1_CPPLINK void Dz1SigMsgSync_unlock(Dz1SigMsgSync *p)
{
//	Dz1Thread_log(DZ1_THREAD_LOG_WARN, "$$$ Dz1SigMsgSync_unlock() %08X=>%p\n", Dz1Thread_self(), &p->sync);
	Dz1Sync_unlock(&p->sync);
}

static Dz1Error _Dz1SigMsgSync_wait(void *ptr, bool_t *status)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SigMsgSync *p = (Dz1SigMsgSync *)ptr;

	if (p->status != Dz1SigMsgStatus_initiated) *status = TRUE;
	else *status = FALSE;

	return err;
}

Dz1Error Dz1SigMsgSync_wait(Dz1SigMsgSync *p, u64_t *wait_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
//	Dz1Thread_log(DZ1_THREAD_LOG_WARN, "$$$ Dz1SigMsgSync_wait() : %08X=>%p\n", Dz1Thread_self(), &p->sync);
	if ((err = Dz1Sync_wait(&p->sync, wait_us, _Dz1SigMsgSync_wait, p)).code) { ERR_OUT(&err); }
	return err;
}

void Dz1SigMsgSync_noLockSignal(Dz1SigMsgSync *p, Dz1SigMsgStatus status)
{
	if (!p) return;
	p->status = status;
//	Dz1Thread_log(DZ1_THREAD_LOG_WARN, "$$$ Dz1SigMsgSync_noLockSignal() : %08X=>%p\n", Dz1Thread_self(), &p->sync);
	Dz1Sync_signal(&p->sync);
}

void Dz1SigMsgSync_signal(Dz1SigMsgSync *p, Dz1SigMsgStatus status)
{
	if (!p) return;
	
	Dz1SigMsgSync_lock(p);
	pthread_cleanup_push(Dz1SigMsgSync_lockCancel, (void *)p);
	
	Dz1SigMsgSync_noLockSignal(p, status);

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)&p->sync->sync);

}
// Dz1SigMsgSync
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SigMsg
Dz1SigMsg *Dz1SigMsg_new(u32_t dst, u32_t src, u32_t type, void *msg, Dz1DelFunc del, Dz1DumpFunc dump,	Dz1Error *initialStatus, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SigMsg *ret = (Dz1SigMsg *)Dz1Calloc(sizeof(Dz1SigMsg), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		ret->dst = dst;
		ret->src = src;

		ret->type = type;

		ret->msg = msg;
		ret->del = del;
		ret->dump = dump;
		
		if (initialStatus) memcpy(&ret->err, initialStatus, sizeof(Dz1Error));

		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void _Dz1SigMsg_del(Dz1SigMsg *p)
{
	if (!p) return;

	if (p->msg && p->del) p->del(p->msg);
	if (p->ppt == Dz1SigMsgPostProcess_call)
		Dz1SigMsgSync_destroy(&p->x.sync);
	Dz1Free(p);
}

void Dz1SigMsg_del(Dz1SigMsg *p)
{
	int ref;

//	printf("sg = %p\n", p);fflush(stdout);
	if (!p) return;
	
	ref = --p->ref;
//	printf("ref = %d\n", ref); fflush(stdout);

	if (ref <= 0) _Dz1SigMsg_del(p);
}

void Dz1SigMsgA_dump(Dz1SigMsg *p, int tab)
{
	if (!p || !p->msg) return;
	Dz1ThreadA_printf("{\n");
	if (p->dump) { Dz1ThreadA_tprintf(tab, "msg = "); p->dump(p->msg, tab + 1); }
	else Dz1ThreadA_tprintf(tab, "msg = %p\n", p->msg);
	Dz1ThreadA_tprintf(tab, "error = "); Dz1ErrorA_dump(&p->err, tab);
	Dz1ThreadA_tprintf(tab - 1, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1SigMsgW_dump(Dz1SigMsg *p, int tab)
{
	if (!p || !p->msg) return;
	Dz1ThreadW_printf(L"{\n");
	if (p->dump) { Dz1ThreadW_tprintf(tab, L"msg = "); p->dump(p->msg, tab + 1); }
	else Dz1ThreadW_tprintf(tab, L"msg = %p\n", p->msg);
	Dz1ThreadW_tprintf(tab, L"error = "); Dz1ErrorW_dump(&p->err, tab);
	Dz1ThreadW_tprintf(tab - 1, L"}\n");
}
#endif

void Dz1SigMsg_finalize(Dz1SigMsg **p, bool_t isAbnormal)
{
	if (p == NULL || *p == NULL) return;

	if ((*p)->ppt == Dz1SigMsgPostProcess_call)
	{
		Dz1SigMsgSync *sync = &((*p)->x.sync);
		Dz1SigMsgSync_signal(sync, isAbnormal ? Dz1SigMsgStatus_aborted : Dz1SigMsgStatus_processed);
	}
	else if ((*p)->ppt == Dz1SigMsgPostProcess_callback)
	{
		Dz1SigMsgCallback *cb = &(*p)->x.cb;
		if (cb->callback) cb->callback(cb->param, (void **)p, isAbnormal);
	}
}

void Dz1SigMsg_signal(Dz1SigMsg **p, bool_t isAbnormal)
{
	if (p == NULL || *p == NULL) return;

	if ((*p)->ppt == Dz1SigMsgPostProcess_call)
	{
		Dz1SigMsgSync *sync = &((*p)->x.sync);
		Dz1SigMsgSync_noLockSignal(sync, isAbnormal ? Dz1SigMsgStatus_aborted : Dz1SigMsgStatus_processed);
	}
	else if ((*p)->ppt == Dz1SigMsgPostProcess_callback)
	{
		Dz1SigMsgCallback *cb = &(*p)->x.cb;
		if (cb->callback) cb->callback(cb->param, (void **)p, isAbnormal);
	}
}

void Dz1SigMsg_lock(Dz1SigMsg *p)
{
	if (!p) return;
	if (p->ppt == Dz1SigMsgPostProcess_call)
	{
		Dz1SigMsgSync *sync = &(p->x.sync);
		Dz1SigMsgSync_lock(sync);
	}
}

void Dz1SigMsg_unlock(Dz1SigMsg *p)
{
	if (!p) return;
	if (p->ppt == Dz1SigMsgPostProcess_call)
	{
		Dz1SigMsgSync *sync = &(p->x.sync);
		Dz1SigMsgSync_unlock(sync);
	}
}

void Dz1SigMsg_lockCancel(void *ptr)
{
	Dz1SigMsg *p = (Dz1SigMsg *)ptr;
	Dz1SigMsg_unlock(p);
}
// Dz1SigMsg
///////////////////////////////////////////////////////////////////////////////
