////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827ServerDomainDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionState
static struct ItsIso14827SubscriptionStateMapA
{
	str_t str;
	ItsIso14827SubscriptionState v;
} ItsIso14827SubscriptionStateMapA[] =
{
	{ (char *)"waitAddConfirm", ItsIso14827SubscriptionState_waitAddConfirm },
	{ (char *)"established", ItsIso14827SubscriptionState_established },
	{ (char *)"waitUpdateConfirm", ItsIso14827SubscriptionState_waitUpdateConfirm },
	{ (char *)"waitDeleteConfirm", ItsIso14827SubscriptionState_waitDeleteConfirm },
	{ NULL, ItsIso14827SubscriptionState_max }
};

str_t ItsIso14827SubscriptionStateStrA(ItsIso14827SubscriptionState v)
{
	struct ItsIso14827SubscriptionStateMapA *i = NULL;
	for (i = ItsIso14827SubscriptionStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827SubscriptionState ItsIso14827SubscriptionStateFromStrA(str_t str)
{
	struct ItsIso14827SubscriptionStateMapA *i = NULL;
	for (i = ItsIso14827SubscriptionStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827SubscriptionState_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827SubscriptionStateMapW
{
	wstr_t str;
	ItsIso14827SubscriptionState v;
} ItsIso14827SubscriptionStateMapW[] =
{
	{ (wchar_t *)L"waitAddConfirm", ItsIso14827SubscriptionState_waitAddConfirm },
	{ (wchar_t *)L"established", ItsIso14827SubscriptionState_established },
	{ (wchar_t *)L"waitUpdateConfirm", ItsIso14827SubscriptionState_waitUpdateConfirm },
	{ (wchar_t *)L"waitDeleteConfirm", ItsIso14827SubscriptionState_waitDeleteConfirm },
	{ NULL, ItsIso14827SubscriptionState_max }
};

wstr_t ItsIso14827SubscriptionStateStrW(ItsIso14827SubscriptionState v)
{
	struct ItsIso14827SubscriptionStateMapW *i = NULL;
	for (i = ItsIso14827SubscriptionStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827SubscriptionState ItsIso14827SubscriptionStateFromStrW(wstr_t str)
{
	struct ItsIso14827SubscriptionStateMapW *i = NULL;
	for (i = ItsIso14827SubscriptionStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827SubscriptionState_max;
}
#endif // UNIX_SYSTEM

ItsIso14827SubscriptionState *ItsIso14827SubscriptionState_new(ItsIso14827SubscriptionState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionState *__internal_ret = (ItsIso14827SubscriptionState *)Dz1Calloc(sizeof(ItsIso14827SubscriptionState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827SubscriptionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionEvent
static struct ItsIso14827SubscriptionEventMapA
{
	str_t str;
	ItsIso14827SubscriptionEvent v;
} ItsIso14827SubscriptionEventMapA[] =
{
	{ (char *)"create", ItsIso14827SubscriptionEvent_create },
	{ (char *)"update", ItsIso14827SubscriptionEvent_update },
	{ (char *)"delete", ItsIso14827SubscriptionEvent_delete },
	{ (char *)"accept", ItsIso14827SubscriptionEvent_accept },
	{ (char *)"reject", ItsIso14827SubscriptionEvent_reject },
	{ (char *)"publication", ItsIso14827SubscriptionEvent_publication },
	{ (char *)"peerReject", ItsIso14827SubscriptionEvent_peerReject },
	{ NULL, ItsIso14827SubscriptionEvent_max }
};

str_t ItsIso14827SubscriptionEventStrA(ItsIso14827SubscriptionEvent v)
{
	struct ItsIso14827SubscriptionEventMapA *i = NULL;
	for (i = ItsIso14827SubscriptionEventMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827SubscriptionEvent ItsIso14827SubscriptionEventFromStrA(str_t str)
{
	struct ItsIso14827SubscriptionEventMapA *i = NULL;
	for (i = ItsIso14827SubscriptionEventMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827SubscriptionEvent_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827SubscriptionEventMapW
{
	wstr_t str;
	ItsIso14827SubscriptionEvent v;
} ItsIso14827SubscriptionEventMapW[] =
{
	{ (wchar_t *)L"create", ItsIso14827SubscriptionEvent_create },
	{ (wchar_t *)L"update", ItsIso14827SubscriptionEvent_update },
	{ (wchar_t *)L"delete", ItsIso14827SubscriptionEvent_delete },
	{ (wchar_t *)L"accept", ItsIso14827SubscriptionEvent_accept },
	{ (wchar_t *)L"reject", ItsIso14827SubscriptionEvent_reject },
	{ (wchar_t *)L"publication", ItsIso14827SubscriptionEvent_publication },
	{ (wchar_t *)L"peerReject", ItsIso14827SubscriptionEvent_peerReject },
	{ NULL, ItsIso14827SubscriptionEvent_max }
};

wstr_t ItsIso14827SubscriptionEventStrW(ItsIso14827SubscriptionEvent v)
{
	struct ItsIso14827SubscriptionEventMapW *i = NULL;
	for (i = ItsIso14827SubscriptionEventMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827SubscriptionEvent ItsIso14827SubscriptionEventFromStrW(wstr_t str)
{
	struct ItsIso14827SubscriptionEventMapW *i = NULL;
	for (i = ItsIso14827SubscriptionEventMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827SubscriptionEvent_max;
}
#endif // UNIX_SYSTEM

ItsIso14827SubscriptionEvent *ItsIso14827SubscriptionEvent_new(ItsIso14827SubscriptionEvent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionEvent *__internal_ret = (ItsIso14827SubscriptionEvent *)Dz1Calloc(sizeof(ItsIso14827SubscriptionEvent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827SubscriptionEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionReq
ItsIso14827SubscriptionReq *ItsIso14827SubscriptionReq_new(u32_t pktNbr, 
														   Iso14827SubscriptionData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionReq *__internal_ret = (ItsIso14827SubscriptionReq *)Dz1Calloc(sizeof(ItsIso14827SubscriptionReq), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SubscriptionReq_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->pktNbr = pktNbr;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscriptionReq_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SubscriptionReq_purge(ItsIso14827SubscriptionReq *p)
{
	if (p == NULL) return;
	Iso14827SubscriptionData_del(p->data);
}

void ItsIso14827SubscriptionReq_del(ItsIso14827SubscriptionReq *p)
{
	if (p == NULL) return;
	ItsIso14827SubscriptionReq_purge(p);
	Dz1Free(p);
}

// ItsIso14827SubscriptionReq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionOperPresent
static struct ItsIso14827SubscriptionOperPresentMapA
{
	str_t str;
	ItsIso14827SubscriptionOperPresent v;
} ItsIso14827SubscriptionOperPresentMapA[] =
{
	{ (char *)"create", ItsIso14827SubscriptionOperPresent_create },
	{ (char *)"update", ItsIso14827SubscriptionOperPresent_update },
	{ (char *)"terminate", ItsIso14827SubscriptionOperPresent_terminate },
	{ NULL, ItsIso14827SubscriptionOperPresent_max }
};

str_t ItsIso14827SubscriptionOperPresentStrA(ItsIso14827SubscriptionOperPresent v)
{
	struct ItsIso14827SubscriptionOperPresentMapA *i = NULL;
	for (i = ItsIso14827SubscriptionOperPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827SubscriptionOperPresent ItsIso14827SubscriptionOperPresentFromStrA(str_t str)
{
	struct ItsIso14827SubscriptionOperPresentMapA *i = NULL;
	for (i = ItsIso14827SubscriptionOperPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827SubscriptionOperPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827SubscriptionOperPresentMapW
{
	wstr_t str;
	ItsIso14827SubscriptionOperPresent v;
} ItsIso14827SubscriptionOperPresentMapW[] =
{
	{ (wchar_t *)L"create", ItsIso14827SubscriptionOperPresent_create },
	{ (wchar_t *)L"update", ItsIso14827SubscriptionOperPresent_update },
	{ (wchar_t *)L"terminate", ItsIso14827SubscriptionOperPresent_terminate },
	{ NULL, ItsIso14827SubscriptionOperPresent_max }
};

wstr_t ItsIso14827SubscriptionOperPresentStrW(ItsIso14827SubscriptionOperPresent v)
{
	struct ItsIso14827SubscriptionOperPresentMapW *i = NULL;
	for (i = ItsIso14827SubscriptionOperPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827SubscriptionOperPresent ItsIso14827SubscriptionOperPresentFromStrW(wstr_t str)
{
	struct ItsIso14827SubscriptionOperPresentMapW *i = NULL;
	for (i = ItsIso14827SubscriptionOperPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827SubscriptionOperPresent_max;
}
#endif // UNIX_SYSTEM

ItsIso14827SubscriptionOperPresent *ItsIso14827SubscriptionOperPresent_new(ItsIso14827SubscriptionOperPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionOperPresent *__internal_ret = (ItsIso14827SubscriptionOperPresent *)Dz1Calloc(sizeof(ItsIso14827SubscriptionOperPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827SubscriptionOperPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionOper
ItsIso14827SubscriptionOper *ItsIso14827SubscriptionOper_new(ItsIso14827SubscriptionOperPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionOper *ret = (ItsIso14827SubscriptionOper *)Dz1Calloc(sizeof(ItsIso14827SubscriptionOper), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SubscriptionOper_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ItsIso14827SubscriptionOperPresent_create:
			// _U_cst_clone
			if (ptr != NULL) ret->x.create = (ItsIso14827SubscriptionReq *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827SubscriptionOperPresent_update:
			// _U_cst_clone
			if (ptr != NULL) ret->x.update = (ItsIso14827SubscriptionReq *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827SubscriptionOperPresent_terminate:
			// _U_prim_clone
			if (ptr != NULL) ret->x.terminate = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827SubscriptionOperPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscriptionOper_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827SubscriptionOper_purge(ItsIso14827SubscriptionOper *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ItsIso14827SubscriptionOperPresent_create:
		ItsIso14827SubscriptionReq_del(p->x.create);
		break;
	case ItsIso14827SubscriptionOperPresent_update:
		ItsIso14827SubscriptionReq_del(p->x.update);
		break;
	case ItsIso14827SubscriptionOperPresent_terminate:
		break;
	default:
		break;
	}
}

void ItsIso14827SubscriptionOper_del(ItsIso14827SubscriptionOper *p)
{
	if (!p) return;
	ItsIso14827SubscriptionOper_purge(p);
	Dz1Free(p);
}

// ItsIso14827SubscriptionOper
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerSubscriptionFsmArg
ItsIso14827ServerSubscriptionFsmArg *ItsIso14827ServerSubscriptionFsmArg_new(ItsIso14827ServerDomain *server/*_ref*/, 
																			 ItsIso14827ServerDomainClientEntry *client/*_ref*/, 
																			 Dz1Asn1UTF8Str *domainName, 
																			 ItsIso14827SubscriptionEntry *subscription/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerSubscriptionFsmArg *__internal_ret = (ItsIso14827ServerSubscriptionFsmArg *)Dz1Calloc(sizeof(ItsIso14827ServerSubscriptionFsmArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerSubscriptionFsmArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->server = server;
		__internal_ret->client = client;
		__internal_ret->domainName = domainName;
		__internal_ret->subscription = subscription;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerSubscriptionFsmArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ServerSubscriptionFsmArg_purge(ItsIso14827ServerSubscriptionFsmArg *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	ItsIso14827SubscriptionOper_del(p->oper);
	ItsIso14827SubscriptionOper_del(p->retried);
}

void ItsIso14827ServerSubscriptionFsmArg_del(ItsIso14827ServerSubscriptionFsmArg *p)
{
	if (p == NULL) return;
	ItsIso14827ServerSubscriptionFsmArg_purge(p);
	Dz1Free(p);
}

// ItsIso14827ServerSubscriptionFsmArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionDate
ItsIso14827SubscriptionDate *ItsIso14827SubscriptionDate_new(u32_t year, 
															 u32_t mon, 
															 u32_t day, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionDate *__internal_ret = (ItsIso14827SubscriptionDate *)Dz1Calloc(sizeof(ItsIso14827SubscriptionDate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SubscriptionDate_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->year = year;
		__internal_ret->mon = mon;
		__internal_ret->day = day;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscriptionDate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SubscriptionDate_purge(ItsIso14827SubscriptionDate *p)
{
	if (p == NULL) return;
}

void ItsIso14827SubscriptionDate_del(ItsIso14827SubscriptionDate *p)
{
	if (p == NULL) return;
	ItsIso14827SubscriptionDate_purge(p);
	Dz1Free(p);
}

void ItsIso14827SubscriptionDate_dump(ItsIso14827SubscriptionDate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("year = ")); Dz1u32_dump(&p->year, tab); 
		Dz1Thread_tprintf(tab, Dz1T("mon = ")); Dz1u32_dump(&p->mon, tab); 
		Dz1Thread_tprintf(tab, Dz1T("day = ")); Dz1u32_dump(&p->day, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827SubscriptionDate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionEntry
ItsIso14827SubscriptionEntry *ItsIso14827SubscriptionEntry_new(u32_t serial, 
															   Dz1Fsm2 *fsm, 
															   u32_t pktNbr, 
															   Iso14827SubscriptionData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionEntry *__internal_ret = (ItsIso14827SubscriptionEntry *)Dz1Calloc(sizeof(ItsIso14827SubscriptionEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->serial = serial;
		__internal_ret->fsm = fsm;
		__internal_ret->pktNbr = pktNbr;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscriptionEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SubscriptionEntry_purge(ItsIso14827SubscriptionEntry *p)
{
	if (p == NULL) return;
	Dz1Fsm2_del(p->fsm);
	Iso14827SubscriptionData_del(p->data);
	ItsIso14827SubscriptionDate_del(p->daily);
}

void ItsIso14827SubscriptionEntry_del(ItsIso14827SubscriptionEntry *p)
{
	if (p == NULL) return;
	ItsIso14827SubscriptionEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827SubscriptionEntry_dump(ItsIso14827SubscriptionEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("fsm = %p\n"), p->fsm);
		Dz1Thread_tprintf(tab, Dz1T("pktNbr = ")); Dz1u32_dump(&p->pktNbr, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Iso14827SubscriptionData_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pubSerial = ")); Dz1u32_dump(&p->pubSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isActive = ")); Dz1Bool_dump(&p->isActive, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isPaused = ")); Dz1Bool_dump(&p->isPaused, tab); 
		Dz1Thread_tprintf(tab, Dz1T("start = ")); time_dump(&p->start, tab); 
		Dz1Thread_tprintf(tab, Dz1T("end = ")); time_dump(&p->end, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("daily = ")); ItsIso14827SubscriptionDate_dump(p->daily, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827SubscriptionEntry_cmp(ItsIso14827SubscriptionEntry *a, ItsIso14827SubscriptionEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->serial, &b->serial)) != 0) { }
	return ret;
}
// ItsIso14827SubscriptionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionList
static Dz1Error ItsIso14827SubscriptionList_add(ItsIso14827SubscriptionList *p, ItsIso14827SubscriptionEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t ItsIso14827SubscriptionList_remove(ItsIso14827SubscriptionList *p, ItsIso14827SubscriptionEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827SubscriptionEntry *ItsIso14827SubscriptionList_extract(ItsIso14827SubscriptionList *p, ItsIso14827SubscriptionEntry *key)
{
	return (ItsIso14827SubscriptionEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827SubscriptionListMkArrArg
{
	ItsIso14827SubscriptionEntry **arr;
	unsigned int idx;
} ItsIso14827SubscriptionListMkArrArg;

static Dz1Error _ItsIso14827SubscriptionList_get_array(void *ptr, ItsIso14827SubscriptionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SubscriptionListMkArrArg *arg = (ItsIso14827SubscriptionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827SubscriptionEntry **ItsIso14827SubscriptionList_get_array(ItsIso14827SubscriptionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827SubscriptionEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827SubscriptionEntry **)Dz1Calloc(sizeof(ItsIso14827SubscriptionEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827SubscriptionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827SubscriptionList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error ItsIso14827SubscriptionList_travelForward(ItsIso14827SubscriptionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscriptionEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827SubscriptionList_travelBackward(ItsIso14827SubscriptionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscriptionEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827SubscriptionEntry *ItsIso14827SubscriptionList_find(ItsIso14827SubscriptionList *p, ItsIso14827SubscriptionEntry *key)
{
	return (ItsIso14827SubscriptionEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827SubscriptionList_count(ItsIso14827SubscriptionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827SubscriptionList *ItsIso14827SubscriptionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionList *ret = (ItsIso14827SubscriptionList *)Dz1Calloc(sizeof(ItsIso14827SubscriptionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827SubscriptionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827SubscriptionEntry_cmp,
				(Dz1DelFunc)ItsIso14827SubscriptionEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827SubscriptionList_count;
			ret->travel = ItsIso14827SubscriptionList_travelForward;
			ret->travelForward = ItsIso14827SubscriptionList_travelForward;
			ret->travelBackward = ItsIso14827SubscriptionList_travelBackward;
			ret->get_array = ItsIso14827SubscriptionList_get_array;
			ret->add = ItsIso14827SubscriptionList_add;
			ret->remove = ItsIso14827SubscriptionList_remove;
			ret->find = ItsIso14827SubscriptionList_find;
			ret->extract = ItsIso14827SubscriptionList_extract;
			ret->cmp = ItsIso14827SubscriptionEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscriptionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827SubscriptionList_purge(ItsIso14827SubscriptionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827SubscriptionList_del(ItsIso14827SubscriptionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827SubscriptionList_dump(void *ptr, ItsIso14827SubscriptionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827SubscriptionEntry_dump(p, tab);
	return err;
}

void ItsIso14827SubscriptionList_dump(ItsIso14827SubscriptionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827SubscriptionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827SubscriptionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainClientState
static struct ItsIso14827ServerDomainClientStateMapA
{
	str_t str;
	ItsIso14827ServerDomainClientState v;
} ItsIso14827ServerDomainClientStateMapA[] =
{
	{ (char *)"waitLoginResult", ItsIso14827ServerDomainClientState_waitLoginResult },
	{ (char *)"established", ItsIso14827ServerDomainClientState_established },
	{ (char *)"terminated", ItsIso14827ServerDomainClientState_terminated },
	{ NULL, ItsIso14827ServerDomainClientState_max }
};

str_t ItsIso14827ServerDomainClientStateStrA(ItsIso14827ServerDomainClientState v)
{
	struct ItsIso14827ServerDomainClientStateMapA *i = NULL;
	for (i = ItsIso14827ServerDomainClientStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827ServerDomainClientState ItsIso14827ServerDomainClientStateFromStrA(str_t str)
{
	struct ItsIso14827ServerDomainClientStateMapA *i = NULL;
	for (i = ItsIso14827ServerDomainClientStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827ServerDomainClientState_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827ServerDomainClientStateMapW
{
	wstr_t str;
	ItsIso14827ServerDomainClientState v;
} ItsIso14827ServerDomainClientStateMapW[] =
{
	{ (wchar_t *)L"waitLoginResult", ItsIso14827ServerDomainClientState_waitLoginResult },
	{ (wchar_t *)L"established", ItsIso14827ServerDomainClientState_established },
	{ (wchar_t *)L"terminated", ItsIso14827ServerDomainClientState_terminated },
	{ NULL, ItsIso14827ServerDomainClientState_max }
};

wstr_t ItsIso14827ServerDomainClientStateStrW(ItsIso14827ServerDomainClientState v)
{
	struct ItsIso14827ServerDomainClientStateMapW *i = NULL;
	for (i = ItsIso14827ServerDomainClientStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827ServerDomainClientState ItsIso14827ServerDomainClientStateFromStrW(wstr_t str)
{
	struct ItsIso14827ServerDomainClientStateMapW *i = NULL;
	for (i = ItsIso14827ServerDomainClientStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827ServerDomainClientState_max;
}
#endif // UNIX_SYSTEM

ItsIso14827ServerDomainClientState *ItsIso14827ServerDomainClientState_new(ItsIso14827ServerDomainClientState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomainClientState *__internal_ret = (ItsIso14827ServerDomainClientState *)Dz1Calloc(sizeof(ItsIso14827ServerDomainClientState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827ServerDomainClientState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainClientEntry
ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomainClientEntry_new(Dz1Asn1UTF8Str *peer, 
																		   Dz1Asn1OctetStr *user, 
																		   ItsIso14827SessionKey *key, 
																		   ItsIso14827DomainTxFifo *txFifo, 
																		   u32_t heartBeadPeriod, 
																		   u32_t responseWaitTime, 
																		   u32_t loginPktNbr, 
																		   ItsIso14827ServerDomainCallback *cb/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomainClientEntry *__internal_ret = (ItsIso14827ServerDomainClientEntry *)Dz1Calloc(sizeof(ItsIso14827ServerDomainClientEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->subscriptions = ItsIso14827SubscriptionList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer = peer;
			__internal_ret->user = user;
			__internal_ret->key = key;
			__internal_ret->txFifo = txFifo;
			__internal_ret->heartBeadPeriod = heartBeadPeriod;
			__internal_ret->responseWaitTime = responseWaitTime;
			__internal_ret->loginPktNbr = loginPktNbr;
			__internal_ret->cb = cb;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainClientEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ServerDomainClientEntry_purge(ItsIso14827ServerDomainClientEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->peer);
	Dz1Asn1OctetStr_del(p->user);
	ItsIso14827SessionKey_del(p->key);
	ItsIso14827SubscriptionList_del(p->subscriptions);
	ItsIso14827DomainTxFifo_del(p->txFifo);
	Dz1u32_del(p->loginRetriedPktNbr);
	ItsIso14827ServerDomainViolatedPublication_del(p->violatedPub);
}

void ItsIso14827ServerDomainClientEntry_del(ItsIso14827ServerDomainClientEntry *p)
{
	if (p == NULL) return;
	ItsIso14827ServerDomainClientEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerDomainClientEntry_dump(ItsIso14827ServerDomainClientEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1Asn1UTF8Str_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("key = ")); ItsIso14827SessionKey_dump(p->key, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subscriptions = ")); ItsIso14827SubscriptionList_dump(p->subscriptions, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("txFifo = ")); ItsIso14827DomainTxFifo_dump(p->txFifo, tab); 
		Dz1Thread_tprintf(tab, Dz1T("heartBeadPeriod = ")); Dz1u32_dump(&p->heartBeadPeriod, tab); 
		Dz1Thread_tprintf(tab, Dz1T("responseWaitTime = ")); Dz1u32_dump(&p->responseWaitTime, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), ItsIso14827ServerDomainClientStateStr(p->state), p->state);
		Dz1Thread_tprintf(tab, Dz1T("loginPktNbr = ")); Dz1u32_dump(&p->loginPktNbr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("loginRetriedPktNbr = ")); Dz1u32_dump(p->loginRetriedPktNbr, tab); 
		// Normal member
		// ItsIso14827ServerDomainCallback : api = F0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("cb = %p\n"), p->cb);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("violatedPub = ")); ItsIso14827ServerDomainViolatedPublication_dump(p->violatedPub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827ServerDomainClientEntry_cmp(ItsIso14827ServerDomainClientEntry *a, ItsIso14827ServerDomainClientEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->peer == NULL && b->peer == NULL) ret = 0;
	else if (a->peer == NULL /*&& b->peer != NULL*/) ret = -1;
	else if (/*a->peer != NULL &&*/ b->peer == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->peer, b->peer)) != 0) { }
	else if (a->user == NULL && b->user == NULL) ret = 0;
	else if (a->user == NULL /*&& b->user != NULL*/) ret = -1;
	else if (/*a->user != NULL &&*/ b->user == NULL) ret = 1;
	else if ((ret = Dz1Asn1OctetStr_cmp(a->user, b->user)) != 0) { }
	return ret;
}
// ItsIso14827ServerDomainClientEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainClientList
static Dz1Error ItsIso14827ServerDomainClientList_add(ItsIso14827ServerDomainClientList *p, ItsIso14827ServerDomainClientEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t ItsIso14827ServerDomainClientList_remove(ItsIso14827ServerDomainClientList *p, ItsIso14827ServerDomainClientEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomainClientList_extract(ItsIso14827ServerDomainClientList *p, ItsIso14827ServerDomainClientEntry *key)
{
	return (ItsIso14827ServerDomainClientEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827ServerDomainClientListMkArrArg
{
	ItsIso14827ServerDomainClientEntry **arr;
	unsigned int idx;
} ItsIso14827ServerDomainClientListMkArrArg;

static Dz1Error _ItsIso14827ServerDomainClientList_get_array(void *ptr, ItsIso14827ServerDomainClientEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827ServerDomainClientListMkArrArg *arg = (ItsIso14827ServerDomainClientListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827ServerDomainClientEntry **ItsIso14827ServerDomainClientList_get_array(ItsIso14827ServerDomainClientList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827ServerDomainClientEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827ServerDomainClientEntry **)Dz1Calloc(sizeof(ItsIso14827ServerDomainClientEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827ServerDomainClientListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827ServerDomainClientList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error ItsIso14827ServerDomainClientList_travelForward(ItsIso14827ServerDomainClientList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainClientEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827ServerDomainClientList_travelBackward(ItsIso14827ServerDomainClientList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainClientEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827ServerDomainClientEntry *ItsIso14827ServerDomainClientList_find(ItsIso14827ServerDomainClientList *p, ItsIso14827ServerDomainClientEntry *key)
{
	return (ItsIso14827ServerDomainClientEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827ServerDomainClientList_count(ItsIso14827ServerDomainClientList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827ServerDomainClientList *ItsIso14827ServerDomainClientList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomainClientList *ret = (ItsIso14827ServerDomainClientList *)Dz1Calloc(sizeof(ItsIso14827ServerDomainClientList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainClientList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827ServerDomainClientEntry_cmp,
				(Dz1DelFunc)ItsIso14827ServerDomainClientEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827ServerDomainClientList_count;
			ret->travel = ItsIso14827ServerDomainClientList_travelForward;
			ret->travelForward = ItsIso14827ServerDomainClientList_travelForward;
			ret->travelBackward = ItsIso14827ServerDomainClientList_travelBackward;
			ret->get_array = ItsIso14827ServerDomainClientList_get_array;
			ret->add = ItsIso14827ServerDomainClientList_add;
			ret->remove = ItsIso14827ServerDomainClientList_remove;
			ret->find = ItsIso14827ServerDomainClientList_find;
			ret->extract = ItsIso14827ServerDomainClientList_extract;
			ret->cmp = ItsIso14827ServerDomainClientEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainClientList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827ServerDomainClientList_purge(ItsIso14827ServerDomainClientList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827ServerDomainClientList_del(ItsIso14827ServerDomainClientList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827ServerDomainClientList_dump(void *ptr, ItsIso14827ServerDomainClientEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827ServerDomainClientEntry_dump(p, tab);
	return err;
}

void ItsIso14827ServerDomainClientList_dump(ItsIso14827ServerDomainClientList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827ServerDomainClientList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerDomainClientList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainSessionEntry
ItsIso14827ServerDomainSessionEntry *ItsIso14827ServerDomainSessionEntry_new(Dz1Asn1UTF8Str *peer, 
																			 Dz1Asn1OctetStr *user, 
																			 ItsIso14827SessionKey *key, 
																			 ItsIso14827DomainTxFifo *txFifo, 
																			 u32_t heartBeadPeriod, 
																			 u32_t responseWaitTime, 
																			 u32_t loginPktNbr, 
																			 ItsIso14827ServerDomainCallback *cb/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomainSessionEntry *__internal_ret = (ItsIso14827ServerDomainSessionEntry *)Dz1Calloc(sizeof(ItsIso14827ServerDomainSessionEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainSessionEntry_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->subscriptions = ItsIso14827SubscriptionList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer = peer;
			__internal_ret->user = user;
			__internal_ret->key = key;
			__internal_ret->txFifo = txFifo;
			__internal_ret->heartBeadPeriod = heartBeadPeriod;
			__internal_ret->responseWaitTime = responseWaitTime;
			__internal_ret->loginPktNbr = loginPktNbr;
			__internal_ret->cb = cb;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainSessionEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ServerDomainSessionEntry_purge(ItsIso14827ServerDomainSessionEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->peer);
	Dz1Asn1OctetStr_del(p->user);
	ItsIso14827SessionKey_del(p->key);
	ItsIso14827SubscriptionList_del(p->subscriptions);
	ItsIso14827DomainTxFifo_del(p->txFifo);
	Dz1u32_del(p->loginRetriedPktNbr);
	ItsIso14827ServerDomainViolatedPublication_del(p->violatedPub);
}

void ItsIso14827ServerDomainSessionEntry_del(ItsIso14827ServerDomainSessionEntry *p)
{
	if (p == NULL) return;
	ItsIso14827ServerDomainSessionEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerDomainSessionEntry_dump(ItsIso14827ServerDomainSessionEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1Asn1UTF8Str_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("key = ")); ItsIso14827SessionKey_dump(p->key, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subscriptions = ")); ItsIso14827SubscriptionList_dump(p->subscriptions, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("txFifo = ")); ItsIso14827DomainTxFifo_dump(p->txFifo, tab); 
		Dz1Thread_tprintf(tab, Dz1T("heartBeadPeriod = ")); Dz1u32_dump(&p->heartBeadPeriod, tab); 
		Dz1Thread_tprintf(tab, Dz1T("responseWaitTime = ")); Dz1u32_dump(&p->responseWaitTime, tab); 
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), ItsIso14827ServerDomainClientStateStr(p->state), p->state);
		Dz1Thread_tprintf(tab, Dz1T("loginPktNbr = ")); Dz1u32_dump(&p->loginPktNbr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("loginRetriedPktNbr = ")); Dz1u32_dump(p->loginRetriedPktNbr, tab); 
		// Normal member
		// ItsIso14827ServerDomainCallback : api = F0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("cb = %p\n"), p->cb);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("violatedPub = ")); ItsIso14827ServerDomainViolatedPublication_dump(p->violatedPub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827ServerDomainSessionEntry_cmp(ItsIso14827ServerDomainSessionEntry *a, ItsIso14827ServerDomainSessionEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->key == NULL && b->key == NULL) ret = 0;
	else if (a->key == NULL /*&& b->key != NULL*/) ret = -1;
	else if (/*a->key != NULL &&*/ b->key == NULL) ret = 1;
	else if ((ret = ItsIso14827SessionKey_cmp(a->key, b->key)) != 0) { }
	return ret;
}
// ItsIso14827ServerDomainSessionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainSessionList
static Dz1Error ItsIso14827ServerDomainSessionList_add(ItsIso14827ServerDomainSessionList *p, ItsIso14827ServerDomainSessionEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t ItsIso14827ServerDomainSessionList_remove(ItsIso14827ServerDomainSessionList *p, ItsIso14827ServerDomainSessionEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827ServerDomainSessionEntry *ItsIso14827ServerDomainSessionList_extract(ItsIso14827ServerDomainSessionList *p, ItsIso14827ServerDomainSessionEntry *key)
{
	return (ItsIso14827ServerDomainSessionEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827ServerDomainSessionListMkArrArg
{
	ItsIso14827ServerDomainSessionEntry **arr;
	unsigned int idx;
} ItsIso14827ServerDomainSessionListMkArrArg;

static Dz1Error _ItsIso14827ServerDomainSessionList_get_array(void *ptr, ItsIso14827ServerDomainSessionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827ServerDomainSessionListMkArrArg *arg = (ItsIso14827ServerDomainSessionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827ServerDomainSessionEntry **ItsIso14827ServerDomainSessionList_get_array(ItsIso14827ServerDomainSessionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827ServerDomainSessionEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827ServerDomainSessionEntry **)Dz1Calloc(sizeof(ItsIso14827ServerDomainSessionEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827ServerDomainSessionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827ServerDomainSessionList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error ItsIso14827ServerDomainSessionList_travelForward(ItsIso14827ServerDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainSessionEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827ServerDomainSessionList_travelBackward(ItsIso14827ServerDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ServerDomainSessionEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827ServerDomainSessionEntry *ItsIso14827ServerDomainSessionList_find(ItsIso14827ServerDomainSessionList *p, ItsIso14827ServerDomainSessionEntry *key)
{
	return (ItsIso14827ServerDomainSessionEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827ServerDomainSessionList_count(ItsIso14827ServerDomainSessionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827ServerDomainSessionList *ItsIso14827ServerDomainSessionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomainSessionList *ret = (ItsIso14827ServerDomainSessionList *)Dz1Calloc(sizeof(ItsIso14827ServerDomainSessionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainSessionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827ServerDomainSessionEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827ServerDomainSessionList_count;
			ret->travel = ItsIso14827ServerDomainSessionList_travelForward;
			ret->travelForward = ItsIso14827ServerDomainSessionList_travelForward;
			ret->travelBackward = ItsIso14827ServerDomainSessionList_travelBackward;
			ret->get_array = ItsIso14827ServerDomainSessionList_get_array;
			ret->add = ItsIso14827ServerDomainSessionList_add;
			ret->remove = ItsIso14827ServerDomainSessionList_remove;
			ret->find = ItsIso14827ServerDomainSessionList_find;
			ret->extract = ItsIso14827ServerDomainSessionList_extract;
			ret->cmp = ItsIso14827ServerDomainSessionEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _ItsIso14827ServerDomainSessionList_clone(void *ptr, ItsIso14827ServerDomainSessionEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827ServerDomainSessionList *p = (ItsIso14827ServerDomainSessionList *)ptr;
	ItsIso14827ServerDomainSessionEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

ItsIso14827ServerDomainSessionList *ItsIso14827ServerDomainSessionList_clone(ItsIso14827ServerDomainSessionList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomainSessionList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ItsIso14827ServerDomainSessionList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainSessionList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_ItsIso14827ServerDomainSessionList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827ServerDomainSessionList_purge(ItsIso14827ServerDomainSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827ServerDomainSessionList_del(ItsIso14827ServerDomainSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827ServerDomainSessionList_dump(void *ptr, ItsIso14827ServerDomainSessionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827ServerDomainSessionEntry_dump(p, tab);
	return err;
}

void ItsIso14827ServerDomainSessionList_dump(ItsIso14827ServerDomainSessionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827ServerDomainSessionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerDomainSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainInitiatorWaitEntry
ItsIso14827DomainInitiatorWaitEntry *ItsIso14827DomainInitiatorWaitEntry_new(Dz1Asn1UTF8Str *peer, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainInitiatorWaitEntry *__internal_ret = (ItsIso14827DomainInitiatorWaitEntry *)Dz1Calloc(sizeof(ItsIso14827DomainInitiatorWaitEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainInitiatorWaitEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainInitiatorWaitEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainInitiatorWaitEntry_purge(ItsIso14827DomainInitiatorWaitEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->peer);
}

void ItsIso14827DomainInitiatorWaitEntry_del(ItsIso14827DomainInitiatorWaitEntry *p)
{
	if (p == NULL) return;
	ItsIso14827DomainInitiatorWaitEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainInitiatorWaitEntry_dump(ItsIso14827DomainInitiatorWaitEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_printf(Dz1T("peer = ")); Dz1Asn1UTF8Str_dump(p->peer, tab); 
	}
}
int ItsIso14827DomainInitiatorWaitEntry_cmp(ItsIso14827DomainInitiatorWaitEntry *a, ItsIso14827DomainInitiatorWaitEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->peer == NULL && b->peer == NULL) ret = 0;
	else if (a->peer == NULL /*&& b->peer != NULL*/) ret = -1;
	else if (/*a->peer != NULL &&*/ b->peer == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->peer, b->peer)) != 0) { }
	return ret;
}
// ItsIso14827DomainInitiatorWaitEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainInitiatorWaitList
static Dz1Error ItsIso14827DomainInitiatorWaitList_add(ItsIso14827DomainInitiatorWaitList *p, ItsIso14827DomainInitiatorWaitEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t ItsIso14827DomainInitiatorWaitList_remove(ItsIso14827DomainInitiatorWaitList *p, ItsIso14827DomainInitiatorWaitEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827DomainInitiatorWaitEntry *ItsIso14827DomainInitiatorWaitList_extract(ItsIso14827DomainInitiatorWaitList *p, ItsIso14827DomainInitiatorWaitEntry *key)
{
	return (ItsIso14827DomainInitiatorWaitEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827DomainInitiatorWaitListMkArrArg
{
	ItsIso14827DomainInitiatorWaitEntry **arr;
	unsigned int idx;
} ItsIso14827DomainInitiatorWaitListMkArrArg;

static Dz1Error _ItsIso14827DomainInitiatorWaitList_get_array(void *ptr, ItsIso14827DomainInitiatorWaitEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainInitiatorWaitListMkArrArg *arg = (ItsIso14827DomainInitiatorWaitListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827DomainInitiatorWaitEntry **ItsIso14827DomainInitiatorWaitList_get_array(ItsIso14827DomainInitiatorWaitList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827DomainInitiatorWaitEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827DomainInitiatorWaitEntry **)Dz1Calloc(sizeof(ItsIso14827DomainInitiatorWaitEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827DomainInitiatorWaitListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827DomainInitiatorWaitList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error ItsIso14827DomainInitiatorWaitList_travelForward(ItsIso14827DomainInitiatorWaitList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainInitiatorWaitEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827DomainInitiatorWaitList_travelBackward(ItsIso14827DomainInitiatorWaitList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainInitiatorWaitEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827DomainInitiatorWaitEntry *ItsIso14827DomainInitiatorWaitList_find(ItsIso14827DomainInitiatorWaitList *p, ItsIso14827DomainInitiatorWaitEntry *key)
{
	return (ItsIso14827DomainInitiatorWaitEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827DomainInitiatorWaitList_count(ItsIso14827DomainInitiatorWaitList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827DomainInitiatorWaitList *ItsIso14827DomainInitiatorWaitList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainInitiatorWaitList *ret = (ItsIso14827DomainInitiatorWaitList *)Dz1Calloc(sizeof(ItsIso14827DomainInitiatorWaitList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainInitiatorWaitList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827DomainInitiatorWaitEntry_cmp,
				(Dz1DelFunc)ItsIso14827DomainInitiatorWaitEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827DomainInitiatorWaitList_count;
			ret->travel = ItsIso14827DomainInitiatorWaitList_travelForward;
			ret->travelForward = ItsIso14827DomainInitiatorWaitList_travelForward;
			ret->travelBackward = ItsIso14827DomainInitiatorWaitList_travelBackward;
			ret->get_array = ItsIso14827DomainInitiatorWaitList_get_array;
			ret->add = ItsIso14827DomainInitiatorWaitList_add;
			ret->remove = ItsIso14827DomainInitiatorWaitList_remove;
			ret->find = ItsIso14827DomainInitiatorWaitList_find;
			ret->extract = ItsIso14827DomainInitiatorWaitList_extract;
			ret->cmp = ItsIso14827DomainInitiatorWaitEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainInitiatorWaitList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827DomainInitiatorWaitList_purge(ItsIso14827DomainInitiatorWaitList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827DomainInitiatorWaitList_del(ItsIso14827DomainInitiatorWaitList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827DomainInitiatorWaitList_dump(void *ptr, ItsIso14827DomainInitiatorWaitEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827DomainInitiatorWaitEntry_dump(p, tab);
	return err;
}

void ItsIso14827DomainInitiatorWaitList_dump(ItsIso14827DomainInitiatorWaitList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827DomainInitiatorWaitList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainInitiatorWaitList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomain
ItsIso14827ServerDomain *ItsIso14827ServerDomain_new(Dz1Asn1UTF8Str *name, 
													 u32_t maxClients, 
													 ItsIso14827CodecOIDMapList *codecOidMap, 
													 ItsIso14827ServerDomainCallback *callback, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomain *__internal_ret = (ItsIso14827ServerDomain *)Dz1Calloc(sizeof(ItsIso14827ServerDomain), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomain_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->clients = ItsIso14827ServerDomainClientList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->sessions = ItsIso14827ServerDomainSessionList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->initWaits = ItsIso14827DomainInitiatorWaitList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->name = name;
			__internal_ret->maxClients = maxClients;
			__internal_ret->codecOidMap = codecOidMap;
			__internal_ret->callback = callback;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomain_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ServerDomain_purge(ItsIso14827ServerDomain *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
	ItsIso14827CodecOIDMapList_del(p->codecOidMap);
	ItsIso14827ServerDomainClientList_del(p->clients);
	ItsIso14827ServerDomainSessionList_del(p->sessions);
	ItsIso14827DomainInitiatorWaitList_del(p->initWaits);
	ItsIso14827ServerDomainCallback_del(p->callback);
}

void ItsIso14827ServerDomain_del(ItsIso14827ServerDomain *p)
{
	if (p == NULL) return;
	ItsIso14827ServerDomain_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerDomain_dump(ItsIso14827ServerDomain *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Asn1UTF8Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("maxClients = ")); Dz1u32_dump(&p->maxClients, tab); 
		Dz1Thread_tprintf(tab, Dz1T("codecOidMap = ")); ItsIso14827CodecOIDMapList_dump(p->codecOidMap, tab); 
		Dz1Thread_tprintf(tab, Dz1T("clients = ")); ItsIso14827ServerDomainClientList_dump(p->clients, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sessions = ")); ItsIso14827ServerDomainSessionList_dump(p->sessions, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initWaits = ")); ItsIso14827DomainInitiatorWaitList_dump(p->initWaits, tab); 
		// Normal member
		// ItsIso14827ServerDomainCallback : api = F0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("callback = %p\n"), p->callback);
		Dz1Thread_tprintf(tab, Dz1T("hdr_opt_flag = ")); Dz1u32_dump(&p->hdr_opt_flag, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827ServerDomain_cmp(ItsIso14827ServerDomain *a, ItsIso14827ServerDomain *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// ItsIso14827ServerDomain
////////////////////////////////////////////////////////////////////////////////

