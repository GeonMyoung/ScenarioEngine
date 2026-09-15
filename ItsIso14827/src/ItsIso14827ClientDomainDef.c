////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827ClientDomainDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscribeEntry
ItsIso14827SubscribeEntry *ItsIso14827SubscribeEntry_new(u32_t serial, 
														 Iso14827SubscriptionData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscribeEntry *__internal_ret = (ItsIso14827SubscribeEntry *)Dz1Calloc(sizeof(ItsIso14827SubscribeEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SubscribeEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->serial = serial;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscribeEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SubscribeEntry_purge(ItsIso14827SubscribeEntry *p)
{
	if (p == NULL) return;
	Iso14827SubscriptionData_del(p->data);
	Dz1u32_del(p->pubSerial);
}

void ItsIso14827SubscribeEntry_del(ItsIso14827SubscribeEntry *p)
{
	if (p == NULL) return;
	ItsIso14827SubscribeEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827SubscribeEntry_dump(ItsIso14827SubscribeEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Iso14827SubscriptionData_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pubSerial = ")); Dz1u32_dump(p->pubSerial, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827SubscribeEntry_cmp(ItsIso14827SubscribeEntry *a, ItsIso14827SubscribeEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->serial, &b->serial)) != 0) { }
	return ret;
}
// ItsIso14827SubscribeEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscribeList
static Dz1Error ItsIso14827SubscribeList_add(ItsIso14827SubscribeList *p, ItsIso14827SubscribeEntry *data)
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

static bool_t ItsIso14827SubscribeList_remove(ItsIso14827SubscribeList *p, ItsIso14827SubscribeEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827SubscribeEntry *ItsIso14827SubscribeList_extract(ItsIso14827SubscribeList *p, ItsIso14827SubscribeEntry *key)
{
	return (ItsIso14827SubscribeEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827SubscribeListMkArrArg
{
	ItsIso14827SubscribeEntry **arr;
	unsigned int idx;
} ItsIso14827SubscribeListMkArrArg;

static Dz1Error _ItsIso14827SubscribeList_get_array(void *ptr, ItsIso14827SubscribeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SubscribeListMkArrArg *arg = (ItsIso14827SubscribeListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827SubscribeEntry **ItsIso14827SubscribeList_get_array(ItsIso14827SubscribeList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827SubscribeEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827SubscribeEntry **)Dz1Calloc(sizeof(ItsIso14827SubscribeEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827SubscribeListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827SubscribeList_get_array, (void *)&arg);
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

static Dz1Error ItsIso14827SubscribeList_travelForward(ItsIso14827SubscribeList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscribeEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827SubscribeList_travelBackward(ItsIso14827SubscribeList *p, Dz1Error (*func)(void *ptr, ItsIso14827SubscribeEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827SubscribeEntry *ItsIso14827SubscribeList_find(ItsIso14827SubscribeList *p, ItsIso14827SubscribeEntry *key)
{
	return (ItsIso14827SubscribeEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827SubscribeList_count(ItsIso14827SubscribeList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827SubscribeList *ItsIso14827SubscribeList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscribeList *ret = (ItsIso14827SubscribeList *)Dz1Calloc(sizeof(ItsIso14827SubscribeList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827SubscribeList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827SubscribeEntry_cmp,
				(Dz1DelFunc)ItsIso14827SubscribeEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827SubscribeList_count;
			ret->travel = ItsIso14827SubscribeList_travelForward;
			ret->travelForward = ItsIso14827SubscribeList_travelForward;
			ret->travelBackward = ItsIso14827SubscribeList_travelBackward;
			ret->get_array = ItsIso14827SubscribeList_get_array;
			ret->add = ItsIso14827SubscribeList_add;
			ret->remove = ItsIso14827SubscribeList_remove;
			ret->find = ItsIso14827SubscribeList_find;
			ret->extract = ItsIso14827SubscribeList_extract;
			ret->cmp = ItsIso14827SubscribeEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscribeList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827SubscribeList_purge(ItsIso14827SubscribeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827SubscribeList_del(ItsIso14827SubscribeList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827SubscribeList_dump(void *ptr, ItsIso14827SubscribeEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827SubscribeEntry_dump(p, tab);
	return err;
}

void ItsIso14827SubscribeList_dump(ItsIso14827SubscribeList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827SubscribeList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827SubscribeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainSessionState
static struct ItsIso14827ClientDomainSessionStateMapA
{
	str_t str;
	ItsIso14827ClientDomainSessionState v;
} ItsIso14827ClientDomainSessionStateMapA[] =
{
	{ (char *)"pending", ItsIso14827ClientDomainSessionState_pending },
	{ (char *)"established", ItsIso14827ClientDomainSessionState_established },
	{ NULL, ItsIso14827ClientDomainSessionState_max }
};

str_t ItsIso14827ClientDomainSessionStateStrA(ItsIso14827ClientDomainSessionState v)
{
	struct ItsIso14827ClientDomainSessionStateMapA *i = NULL;
	for (i = ItsIso14827ClientDomainSessionStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827ClientDomainSessionState ItsIso14827ClientDomainSessionStateFromStrA(str_t str)
{
	struct ItsIso14827ClientDomainSessionStateMapA *i = NULL;
	for (i = ItsIso14827ClientDomainSessionStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827ClientDomainSessionState_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827ClientDomainSessionStateMapW
{
	wstr_t str;
	ItsIso14827ClientDomainSessionState v;
} ItsIso14827ClientDomainSessionStateMapW[] =
{
	{ (wchar_t *)L"pending", ItsIso14827ClientDomainSessionState_pending },
	{ (wchar_t *)L"established", ItsIso14827ClientDomainSessionState_established },
	{ NULL, ItsIso14827ClientDomainSessionState_max }
};

wstr_t ItsIso14827ClientDomainSessionStateStrW(ItsIso14827ClientDomainSessionState v)
{
	struct ItsIso14827ClientDomainSessionStateMapW *i = NULL;
	for (i = ItsIso14827ClientDomainSessionStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827ClientDomainSessionState ItsIso14827ClientDomainSessionStateFromStrW(wstr_t str)
{
	struct ItsIso14827ClientDomainSessionStateMapW *i = NULL;
	for (i = ItsIso14827ClientDomainSessionStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827ClientDomainSessionState_max;
}
#endif // UNIX_SYSTEM

ItsIso14827ClientDomainSessionState *ItsIso14827ClientDomainSessionState_new(ItsIso14827ClientDomainSessionState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainSessionState *__internal_ret = (ItsIso14827ClientDomainSessionState *)Dz1Calloc(sizeof(ItsIso14827ClientDomainSessionState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827ClientDomainSessionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainWaitState
static struct ItsIso14827ClientDomainWaitStateMapA
{
	str_t str;
	ItsIso14827ClientDomainWaitState v;
} ItsIso14827ClientDomainWaitStateMapA[] =
{
	{ (char *)"none", ItsIso14827ClientDomainWaitState_none },
	{ (char *)"loginResultWait", ItsIso14827ClientDomainWaitState_loginResultWait },
	{ (char *)"singleSubscriptionResultWait", ItsIso14827ClientDomainWaitState_singleSubscriptionResultWait },
	{ (char *)"registeredSubscriptionResultWait", ItsIso14827ClientDomainWaitState_registeredSubscriptionResultWait },
	{ (char *)"subscriptionCancelResultWait", ItsIso14827ClientDomainWaitState_subscriptionCancelResultWait },
	{ (char *)"logoutResultWait", ItsIso14827ClientDomainWaitState_logoutResultWait },
	{ NULL, ItsIso14827ClientDomainWaitState_max }
};

str_t ItsIso14827ClientDomainWaitStateStrA(ItsIso14827ClientDomainWaitState v)
{
	struct ItsIso14827ClientDomainWaitStateMapA *i = NULL;
	for (i = ItsIso14827ClientDomainWaitStateMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827ClientDomainWaitState ItsIso14827ClientDomainWaitStateFromStrA(str_t str)
{
	struct ItsIso14827ClientDomainWaitStateMapA *i = NULL;
	for (i = ItsIso14827ClientDomainWaitStateMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827ClientDomainWaitState_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827ClientDomainWaitStateMapW
{
	wstr_t str;
	ItsIso14827ClientDomainWaitState v;
} ItsIso14827ClientDomainWaitStateMapW[] =
{
	{ (wchar_t *)L"none", ItsIso14827ClientDomainWaitState_none },
	{ (wchar_t *)L"loginResultWait", ItsIso14827ClientDomainWaitState_loginResultWait },
	{ (wchar_t *)L"singleSubscriptionResultWait", ItsIso14827ClientDomainWaitState_singleSubscriptionResultWait },
	{ (wchar_t *)L"registeredSubscriptionResultWait", ItsIso14827ClientDomainWaitState_registeredSubscriptionResultWait },
	{ (wchar_t *)L"subscriptionCancelResultWait", ItsIso14827ClientDomainWaitState_subscriptionCancelResultWait },
	{ (wchar_t *)L"logoutResultWait", ItsIso14827ClientDomainWaitState_logoutResultWait },
	{ NULL, ItsIso14827ClientDomainWaitState_max }
};

wstr_t ItsIso14827ClientDomainWaitStateStrW(ItsIso14827ClientDomainWaitState v)
{
	struct ItsIso14827ClientDomainWaitStateMapW *i = NULL;
	for (i = ItsIso14827ClientDomainWaitStateMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827ClientDomainWaitState ItsIso14827ClientDomainWaitStateFromStrW(wstr_t str)
{
	struct ItsIso14827ClientDomainWaitStateMapW *i = NULL;
	for (i = ItsIso14827ClientDomainWaitStateMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827ClientDomainWaitState_max;
}
#endif // UNIX_SYSTEM

ItsIso14827ClientDomainWaitState *ItsIso14827ClientDomainWaitState_new(ItsIso14827ClientDomainWaitState *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainWaitState *__internal_ret = (ItsIso14827ClientDomainWaitState *)Dz1Calloc(sizeof(ItsIso14827ClientDomainWaitState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ItsIso14827ClientDomainWaitState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainServerEntry
ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomainServerEntry_new(Dz1Asn1UTF8Str *peer, 
																		   Dz1Asn1OctetStr *user, 
																		   ItsIso14827SessionKey *key, 
																		   u32_t subscribeAlloc, 
																		   ItsIso14827DomainTxFifo *txFifo, 
																		   u32_t heartBeadPeriod, 
																		   u32_t responseWaitTime, 
																		   ItsIso14827ClientDomainCallback *cb/*_ref*/, 
																		   ItsIso14827ClientDomainViolatedSubscription *violatedSub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainServerEntry *__internal_ret = (ItsIso14827ClientDomainServerEntry *)Dz1Calloc(sizeof(ItsIso14827ClientDomainServerEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->subscribes = ItsIso14827SubscribeList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer = peer;
			__internal_ret->user = user;
			__internal_ret->key = key;
			__internal_ret->subscribeAlloc = subscribeAlloc;
			__internal_ret->txFifo = txFifo;
			__internal_ret->heartBeadPeriod = heartBeadPeriod;
			__internal_ret->responseWaitTime = responseWaitTime;
			__internal_ret->cb = cb;
			__internal_ret->violatedSub = violatedSub;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainServerEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ClientDomainServerEntry_purge(ItsIso14827ClientDomainServerEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->peer);
	Dz1Asn1OctetStr_del(p->user);
	ItsIso14827SessionKey_del(p->key);
	ItsIso14827SubscribeList_del(p->subscribes);
	ItsIso14827DomainTxFifo_del(p->txFifo);
	ItsIso14827ClientDomainViolatedSubscription_del(p->violatedSub);
}

void ItsIso14827ClientDomainServerEntry_del(ItsIso14827ClientDomainServerEntry *p)
{
	if (p == NULL) return;
	ItsIso14827ClientDomainServerEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClientDomainServerEntry_dump(ItsIso14827ClientDomainServerEntry *p, int tab)
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
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), ItsIso14827ClientDomainSessionStateStr(p->state), p->state);
		Dz1Thread_tprintf(tab, Dz1T("subscribeAlloc = ")); Dz1u32_dump(&p->subscribeAlloc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subscribes = ")); ItsIso14827SubscribeList_dump(p->subscribes, tab); 
		Dz1Thread_tprintf(tab, Dz1T("userWaitState = %s(%d)\n"), ItsIso14827ClientDomainWaitStateStr(p->userWaitState), p->userWaitState);
		Dz1Thread_tprintf(tab, Dz1T("userWait = %p\n"), p->userWait);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("txFifo = ")); ItsIso14827DomainTxFifo_dump(p->txFifo, tab); 
		Dz1Thread_tprintf(tab, Dz1T("heartBeadPeriod = ")); Dz1u32_dump(&p->heartBeadPeriod, tab); 
		Dz1Thread_tprintf(tab, Dz1T("responseWaitTime = ")); Dz1u32_dump(&p->responseWaitTime, tab); 
		// Normal member
		// ItsIso14827ClientDomainCallback : api = F0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("cb = %p\n"), p->cb);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("violatedSub = ")); ItsIso14827ClientDomainViolatedSubscription_dump(p->violatedSub, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ctrl_flags = ")); Dz1u32_dump(&p->ctrl_flags, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827ClientDomainServerEntry_cmp(ItsIso14827ClientDomainServerEntry *a, ItsIso14827ClientDomainServerEntry *b)
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
// ItsIso14827ClientDomainServerEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainServerList
static Dz1Error ItsIso14827ClientDomainServerList_add(ItsIso14827ClientDomainServerList *p, ItsIso14827ClientDomainServerEntry *data)
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

static bool_t ItsIso14827ClientDomainServerList_remove(ItsIso14827ClientDomainServerList *p, ItsIso14827ClientDomainServerEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomainServerList_extract(ItsIso14827ClientDomainServerList *p, ItsIso14827ClientDomainServerEntry *key)
{
	return (ItsIso14827ClientDomainServerEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827ClientDomainServerListMkArrArg
{
	ItsIso14827ClientDomainServerEntry **arr;
	unsigned int idx;
} ItsIso14827ClientDomainServerListMkArrArg;

static Dz1Error _ItsIso14827ClientDomainServerList_get_array(void *ptr, ItsIso14827ClientDomainServerEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827ClientDomainServerListMkArrArg *arg = (ItsIso14827ClientDomainServerListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827ClientDomainServerEntry **ItsIso14827ClientDomainServerList_get_array(ItsIso14827ClientDomainServerList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827ClientDomainServerEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827ClientDomainServerEntry **)Dz1Calloc(sizeof(ItsIso14827ClientDomainServerEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827ClientDomainServerListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827ClientDomainServerList_get_array, (void *)&arg);
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

static Dz1Error ItsIso14827ClientDomainServerList_travelForward(ItsIso14827ClientDomainServerList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainServerEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827ClientDomainServerList_travelBackward(ItsIso14827ClientDomainServerList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainServerEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827ClientDomainServerEntry *ItsIso14827ClientDomainServerList_find(ItsIso14827ClientDomainServerList *p, ItsIso14827ClientDomainServerEntry *key)
{
	return (ItsIso14827ClientDomainServerEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827ClientDomainServerList_count(ItsIso14827ClientDomainServerList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827ClientDomainServerList *ItsIso14827ClientDomainServerList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainServerList *ret = (ItsIso14827ClientDomainServerList *)Dz1Calloc(sizeof(ItsIso14827ClientDomainServerList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainServerList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827ClientDomainServerEntry_cmp,
				(Dz1DelFunc)ItsIso14827ClientDomainServerEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827ClientDomainServerList_count;
			ret->travel = ItsIso14827ClientDomainServerList_travelForward;
			ret->travelForward = ItsIso14827ClientDomainServerList_travelForward;
			ret->travelBackward = ItsIso14827ClientDomainServerList_travelBackward;
			ret->get_array = ItsIso14827ClientDomainServerList_get_array;
			ret->add = ItsIso14827ClientDomainServerList_add;
			ret->remove = ItsIso14827ClientDomainServerList_remove;
			ret->find = ItsIso14827ClientDomainServerList_find;
			ret->extract = ItsIso14827ClientDomainServerList_extract;
			ret->cmp = ItsIso14827ClientDomainServerEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainServerList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827ClientDomainServerList_purge(ItsIso14827ClientDomainServerList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827ClientDomainServerList_del(ItsIso14827ClientDomainServerList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827ClientDomainServerList_dump(void *ptr, ItsIso14827ClientDomainServerEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827ClientDomainServerEntry_dump(p, tab);
	return err;
}

void ItsIso14827ClientDomainServerList_dump(ItsIso14827ClientDomainServerList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827ClientDomainServerList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ClientDomainServerList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainSessionEntry
ItsIso14827ClientDomainSessionEntry *ItsIso14827ClientDomainSessionEntry_new(Dz1Asn1UTF8Str *peer, 
																			 Dz1Asn1OctetStr *user, 
																			 ItsIso14827SessionKey *key, 
																			 u32_t subscribeAlloc, 
																			 ItsIso14827DomainTxFifo *txFifo, 
																			 u32_t heartBeadPeriod, 
																			 u32_t responseWaitTime, 
																			 ItsIso14827ClientDomainCallback *cb/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainSessionEntry *__internal_ret = (ItsIso14827ClientDomainSessionEntry *)Dz1Calloc(sizeof(ItsIso14827ClientDomainSessionEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainSessionEntry_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->subscribes = ItsIso14827SubscribeList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer = peer;
			__internal_ret->user = user;
			__internal_ret->key = key;
			__internal_ret->subscribeAlloc = subscribeAlloc;
			__internal_ret->txFifo = txFifo;
			__internal_ret->heartBeadPeriod = heartBeadPeriod;
			__internal_ret->responseWaitTime = responseWaitTime;
			__internal_ret->cb = cb;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainSessionEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ClientDomainSessionEntry_purge(ItsIso14827ClientDomainSessionEntry *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->peer);
	Dz1Asn1OctetStr_del(p->user);
	ItsIso14827SessionKey_del(p->key);
	ItsIso14827SubscribeList_del(p->subscribes);
	ItsIso14827DomainTxFifo_del(p->txFifo);
}

void ItsIso14827ClientDomainSessionEntry_del(ItsIso14827ClientDomainSessionEntry *p)
{
	if (p == NULL) return;
	ItsIso14827ClientDomainSessionEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClientDomainSessionEntry_dump(ItsIso14827ClientDomainSessionEntry *p, int tab)
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
		Dz1Thread_tprintf(tab, Dz1T("state = %s(%d)\n"), ItsIso14827ClientDomainSessionStateStr(p->state), p->state);
		Dz1Thread_tprintf(tab, Dz1T("subscribeAlloc = ")); Dz1u32_dump(&p->subscribeAlloc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subscribes = ")); ItsIso14827SubscribeList_dump(p->subscribes, tab); 
		Dz1Thread_tprintf(tab, Dz1T("userWaitState = %s(%d)\n"), ItsIso14827ClientDomainWaitStateStr(p->userWaitState), p->userWaitState);
		Dz1Thread_tprintf(tab, Dz1T("userWait = %p\n"), p->userWait);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("txFifo = ")); ItsIso14827DomainTxFifo_dump(p->txFifo, tab); 
		Dz1Thread_tprintf(tab, Dz1T("heartBeadPeriod = ")); Dz1u32_dump(&p->heartBeadPeriod, tab); 
		Dz1Thread_tprintf(tab, Dz1T("responseWaitTime = ")); Dz1u32_dump(&p->responseWaitTime, tab); 
		// Normal member
		// ItsIso14827ClientDomainCallback : api = F0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("cb = %p\n"), p->cb);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827ClientDomainSessionEntry_cmp(ItsIso14827ClientDomainSessionEntry *a, ItsIso14827ClientDomainSessionEntry *b)
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
// ItsIso14827ClientDomainSessionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainSessionList
static Dz1Error ItsIso14827ClientDomainSessionList_add(ItsIso14827ClientDomainSessionList *p, ItsIso14827ClientDomainSessionEntry *data)
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

static bool_t ItsIso14827ClientDomainSessionList_remove(ItsIso14827ClientDomainSessionList *p, ItsIso14827ClientDomainSessionEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827ClientDomainSessionEntry *ItsIso14827ClientDomainSessionList_extract(ItsIso14827ClientDomainSessionList *p, ItsIso14827ClientDomainSessionEntry *key)
{
	return (ItsIso14827ClientDomainSessionEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827ClientDomainSessionListMkArrArg
{
	ItsIso14827ClientDomainSessionEntry **arr;
	unsigned int idx;
} ItsIso14827ClientDomainSessionListMkArrArg;

static Dz1Error _ItsIso14827ClientDomainSessionList_get_array(void *ptr, ItsIso14827ClientDomainSessionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827ClientDomainSessionListMkArrArg *arg = (ItsIso14827ClientDomainSessionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827ClientDomainSessionEntry **ItsIso14827ClientDomainSessionList_get_array(ItsIso14827ClientDomainSessionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827ClientDomainSessionEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827ClientDomainSessionEntry **)Dz1Calloc(sizeof(ItsIso14827ClientDomainSessionEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827ClientDomainSessionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827ClientDomainSessionList_get_array, (void *)&arg);
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

static Dz1Error ItsIso14827ClientDomainSessionList_travelForward(ItsIso14827ClientDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainSessionEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827ClientDomainSessionList_travelBackward(ItsIso14827ClientDomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827ClientDomainSessionEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827ClientDomainSessionEntry *ItsIso14827ClientDomainSessionList_find(ItsIso14827ClientDomainSessionList *p, ItsIso14827ClientDomainSessionEntry *key)
{
	return (ItsIso14827ClientDomainSessionEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827ClientDomainSessionList_count(ItsIso14827ClientDomainSessionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827ClientDomainSessionList *ItsIso14827ClientDomainSessionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainSessionList *ret = (ItsIso14827ClientDomainSessionList *)Dz1Calloc(sizeof(ItsIso14827ClientDomainSessionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainSessionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827ClientDomainSessionEntry_cmp,
				NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827ClientDomainSessionList_count;
			ret->travel = ItsIso14827ClientDomainSessionList_travelForward;
			ret->travelForward = ItsIso14827ClientDomainSessionList_travelForward;
			ret->travelBackward = ItsIso14827ClientDomainSessionList_travelBackward;
			ret->get_array = ItsIso14827ClientDomainSessionList_get_array;
			ret->add = ItsIso14827ClientDomainSessionList_add;
			ret->remove = ItsIso14827ClientDomainSessionList_remove;
			ret->find = ItsIso14827ClientDomainSessionList_find;
			ret->extract = ItsIso14827ClientDomainSessionList_extract;
			ret->cmp = ItsIso14827ClientDomainSessionEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _ItsIso14827ClientDomainSessionList_clone(void *ptr, ItsIso14827ClientDomainSessionEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827ClientDomainSessionList *p = (ItsIso14827ClientDomainSessionList *)ptr;
	ItsIso14827ClientDomainSessionEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

ItsIso14827ClientDomainSessionList *ItsIso14827ClientDomainSessionList_clone(ItsIso14827ClientDomainSessionList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainSessionList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ItsIso14827ClientDomainSessionList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainSessionList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_ItsIso14827ClientDomainSessionList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827ClientDomainSessionList_purge(ItsIso14827ClientDomainSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827ClientDomainSessionList_del(ItsIso14827ClientDomainSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827ClientDomainSessionList_dump(void *ptr, ItsIso14827ClientDomainSessionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827ClientDomainSessionEntry_dump(p, tab);
	return err;
}

void ItsIso14827ClientDomainSessionList_dump(ItsIso14827ClientDomainSessionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827ClientDomainSessionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ClientDomainSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomain
ItsIso14827ClientDomain *ItsIso14827ClientDomain_new(Dz1Asn1UTF8Str *name, 
													 ItsIso14827ClientDomainCallback *callback, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomain *__internal_ret = (ItsIso14827ClientDomain *)Dz1Calloc(sizeof(ItsIso14827ClientDomain), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomain_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->servers = ItsIso14827ClientDomainServerList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->sessions = ItsIso14827ClientDomainSessionList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->name = name;
			__internal_ret->callback = callback;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomain_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ClientDomain_purge(ItsIso14827ClientDomain *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
	ItsIso14827ClientDomainServerList_del(p->servers);
	ItsIso14827ClientDomainSessionList_del(p->sessions);
	ItsIso14827ClientDomainCallback_del(p->callback);
}

void ItsIso14827ClientDomain_del(ItsIso14827ClientDomain *p)
{
	if (p == NULL) return;
	ItsIso14827ClientDomain_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClientDomain_dump(ItsIso14827ClientDomain *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Asn1UTF8Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("servers = ")); ItsIso14827ClientDomainServerList_dump(p->servers, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sessions = ")); ItsIso14827ClientDomainSessionList_dump(p->sessions, tab); 
		// Normal member
		// ItsIso14827ClientDomainCallback : api = F0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("callback = %p\n"), p->callback);
		Dz1Thread_tprintf(tab, Dz1T("hdr_opt_flag = ")); Dz1u32_dump(&p->hdr_opt_flag, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827ClientDomain_cmp(ItsIso14827ClientDomain *a, ItsIso14827ClientDomain *b)
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
// ItsIso14827ClientDomain
////////////////////////////////////////////////////////////////////////////////

