////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Env.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Env
ItsIso14827Env *ItsIso14827Env_new(void *tSelf, 
								   ItsIso14827SessionMgr *sessionMgr, 
								   ItsIso14827DomainMgr *domainMgr, 
								   u32_t pktDumpFlag, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827Env *__internal_ret = (ItsIso14827Env *)Dz1Calloc(sizeof(ItsIso14827Env), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827Env_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tSelf = tSelf;
		__internal_ret->sessionMgr = sessionMgr;
		__internal_ret->domainMgr = domainMgr;
		__internal_ret->pktDumpFlag = pktDumpFlag;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827Env_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827Env_purge(ItsIso14827Env *p)
{
	if (p == NULL) return;
	ItsIso14827SessionMgr_del(p->sessionMgr);
	ItsIso14827DomainMgr_del(p->domainMgr);
}

void ItsIso14827Env_del(ItsIso14827Env *p)
{
	if (p == NULL) return;
	ItsIso14827Env_purge(p);
	Dz1Free(p);
}

void ItsIso14827Env_dump(ItsIso14827Env *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("sessionMgr = ")); ItsIso14827SessionMgr_dump(p->sessionMgr, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("domainMgr = ")); ItsIso14827DomainMgr_dump(p->domainMgr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pktDumpFlag = ")); Dz1u32_dump(&p->pktDumpFlag, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827Env
////////////////////////////////////////////////////////////////////////////////

