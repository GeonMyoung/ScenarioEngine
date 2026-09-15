////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827DomainTxFifoDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTxStatus
static struct ItsIso14827DomainTxStatusMapA
{
	str_t str;
	ItsIso14827DomainTxStatus v;
} ItsIso14827DomainTxStatusMapA[] =
{
	{ (char *)"none", ItsIso14827DomainTxStatus_none },
	{ (char *)"sent", ItsIso14827DomainTxStatus_sent },
	{ (char *)"final", ItsIso14827DomainTxStatus_final },
	{ NULL, ItsIso14827DomainTxStatus_max }
};

str_t ItsIso14827DomainTxStatusStrA(ItsIso14827DomainTxStatus v)
{
	struct ItsIso14827DomainTxStatusMapA *i = NULL;
	for (i = ItsIso14827DomainTxStatusMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827DomainTxStatus ItsIso14827DomainTxStatusFromStrA(str_t str)
{
	struct ItsIso14827DomainTxStatusMapA *i = NULL;
	for (i = ItsIso14827DomainTxStatusMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827DomainTxStatus_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827DomainTxStatusMapW
{
	wstr_t str;
	ItsIso14827DomainTxStatus v;
} ItsIso14827DomainTxStatusMapW[] =
{
	{ (wchar_t *)L"none", ItsIso14827DomainTxStatus_none },
	{ (wchar_t *)L"sent", ItsIso14827DomainTxStatus_sent },
	{ (wchar_t *)L"final", ItsIso14827DomainTxStatus_final },
	{ NULL, ItsIso14827DomainTxStatus_max }
};

wstr_t ItsIso14827DomainTxStatusStrW(ItsIso14827DomainTxStatus v)
{
	struct ItsIso14827DomainTxStatusMapW *i = NULL;
	for (i = ItsIso14827DomainTxStatusMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827DomainTxStatus ItsIso14827DomainTxStatusFromStrW(wstr_t str)
{
	struct ItsIso14827DomainTxStatusMapW *i = NULL;
	for (i = ItsIso14827DomainTxStatusMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827DomainTxStatus_max;
}
#endif // UNIX_SYSTEM

ItsIso14827DomainTxStatus *ItsIso14827DomainTxStatus_new(ItsIso14827DomainTxStatus *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainTxStatus *__internal_ret = (ItsIso14827DomainTxStatus *)Dz1Calloc(sizeof(ItsIso14827DomainTxStatus), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827DomainTxStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTxEntry
ItsIso14827DomainTxEntry *ItsIso14827DomainTxEntry_new(Iso14827C2CAuthMsg *c2c, 
													   u32_t *status, 
													   ItsIso14827DomainTxFail sendFail, 
													   u32_t hdr_opt_flag, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainTxEntry *__internal_ret = (ItsIso14827DomainTxEntry *)Dz1Calloc(sizeof(ItsIso14827DomainTxEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainTxEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->c2c = c2c;
		__internal_ret->status = status;
		__internal_ret->sendFail = sendFail;
		__internal_ret->hdr_opt_flag = hdr_opt_flag;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainTxEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainTxEntry_purge(ItsIso14827DomainTxEntry *p)
{
	if (p == NULL) return;
	Iso14827C2CAuthMsg_del(p->c2c);
	Dz1u32_del(p->status);
}

void ItsIso14827DomainTxEntry_del(ItsIso14827DomainTxEntry *p)
{
	if (p == NULL) return;
	ItsIso14827DomainTxEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainTxEntry_dump(ItsIso14827DomainTxEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("c2c = ")); Iso14827C2CAuthMsg_dump(p->c2c, tab); 
		Dz1Thread_tprintf(tab, Dz1T("status = ")); Dz1u32_dump(p->status, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sendFail = %p\n"), p->sendFail);
		Dz1Thread_tprintf(tab, Dz1T("hdr_opt_flag = ")); Dz1u32_dump(&p->hdr_opt_flag, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827DomainTxEntry_cmp(ItsIso14827DomainTxEntry *a, ItsIso14827DomainTxEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->c2c == NULL && b->c2c == NULL) ret = 0;
	else if (a->c2c == NULL /*&& b->c2c != NULL*/) ret = -1;
	else if (/*a->c2c != NULL &&*/ b->c2c == NULL) ret = 1;
	else if ((ret = Iso14827C2CAuthMsg_cmp(a->c2c, b->c2c)) != 0) { }
	return ret;
}
// ItsIso14827DomainTxEntry
////////////////////////////////////////////////////////////////////////////////

