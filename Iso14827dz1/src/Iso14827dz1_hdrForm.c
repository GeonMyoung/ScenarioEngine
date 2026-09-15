////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827dz1_hdrForm.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827HdrForm
Iso14827HdrForm *Iso14827HdrForm_new(bool_t originDomainPresent, 
									 bool_t originAddrPresent, 
									 bool_t senderDomainPresent, 
									 bool_t senderAddrPresent, 
									 bool_t destDomainPresent, 
									 bool_t destAddrPresent, 
									 str_t currency/*_ref*/, 
									 s32_t factor, 
									 u8_t timeFlag, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827HdrForm *__internal_ret = (Iso14827HdrForm *)Dz1Calloc(sizeof(Iso14827HdrForm), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827HdrForm_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->originDomainPresent = originDomainPresent;
		__internal_ret->originAddrPresent = originAddrPresent;
		__internal_ret->senderDomainPresent = senderDomainPresent;
		__internal_ret->senderAddrPresent = senderAddrPresent;
		__internal_ret->destDomainPresent = destDomainPresent;
		__internal_ret->destAddrPresent = destAddrPresent;
		__internal_ret->currency = currency;
		__internal_ret->factor = factor;
		__internal_ret->timeFlag = timeFlag;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827HdrForm_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827HdrForm_purge(Iso14827HdrForm *p)
{
	if (p == NULL) return;
}

void Iso14827HdrForm_del(Iso14827HdrForm *p)
{
	if (p == NULL) return;
	Iso14827HdrForm_purge(p);
	Dz1Free(p);
}

void Iso14827HdrForm_dump(Iso14827HdrForm *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("originDomainPresent = ")); Dz1Bool_dump(&p->originDomainPresent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("originAddrPresent = ")); Dz1Bool_dump(&p->originAddrPresent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("senderDomainPresent = ")); Dz1Bool_dump(&p->senderDomainPresent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("senderAddrPresent = ")); Dz1Bool_dump(&p->senderAddrPresent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("destDomainPresent = ")); Dz1Bool_dump(&p->destDomainPresent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("destAddrPresent = ")); Dz1Bool_dump(&p->destAddrPresent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("currency = ")); dz1_built_in_str_dump(p->currency, tab); 
		Dz1Thread_tprintf(tab, Dz1T("factor = ")); Dz1s32_dump(&p->factor, tab); 
		Dz1Thread_tprintf(tab, Dz1T("timeFlag = ")); Dz1u8_dump(&p->timeFlag, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Iso14827HdrForm
////////////////////////////////////////////////////////////////////////////////

