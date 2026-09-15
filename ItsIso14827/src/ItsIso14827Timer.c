////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Timer.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionTimer
ItsIso14827SessionTimer *ItsIso14827SessionTimer_new(ItsIso14827SessionKey *key, 
													 u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SessionTimer *__internal_ret = (ItsIso14827SessionTimer *)Dz1Calloc(sizeof(ItsIso14827SessionTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SessionTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->key = key;
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SessionTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SessionTimer_purge(ItsIso14827SessionTimer *p)
{
	if (p == NULL) return;
	ItsIso14827SessionKey_del(p->key);
}

void ItsIso14827SessionTimer_del(ItsIso14827SessionTimer *p)
{
	if (p == NULL) return;
	ItsIso14827SessionTimer_purge(p);
	Dz1Free(p);
}

void ItsIso14827SessionTimer_dump(ItsIso14827SessionTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("key = ")); ItsIso14827SessionKey_dump(p->key, tab); 
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827SessionTimer_cmp(ItsIso14827SessionTimer *a, ItsIso14827SessionTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->key == NULL && b->key == NULL) ret = 0;
	else if (a->key == NULL /*&& b->key != NULL*/) ret = -1;
	else if (/*a->key != NULL &&*/ b->key == NULL) ret = 1;
	else if ((ret = ItsIso14827SessionKey_cmp(a->key, b->key)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// ItsIso14827SessionTimer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTimer
ItsIso14827DomainTimer *ItsIso14827DomainTimer_new(ItsIso14827DomainKey *key, 
												   Dz1Asn1UTF8Str *peer, 
												   Dz1Asn1OctetStr *user, 
												   u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainTimer *__internal_ret = (ItsIso14827DomainTimer *)Dz1Calloc(sizeof(ItsIso14827DomainTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->key = key;
		__internal_ret->peer = peer;
		__internal_ret->user = user;
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainTimer_purge(ItsIso14827DomainTimer *p)
{
	if (p == NULL) return;
	ItsIso14827DomainKey_del(p->key);
	Dz1Asn1UTF8Str_del(p->peer);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainTimer_del(ItsIso14827DomainTimer *p)
{
	if (p == NULL) return;
	ItsIso14827DomainTimer_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainTimer_dump(ItsIso14827DomainTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("key = ")); ItsIso14827DomainKey_dump(p->key, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1Asn1UTF8Str_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827DomainTimer_cmp(ItsIso14827DomainTimer *a, ItsIso14827DomainTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->key == NULL && b->key == NULL) ret = 0;
	else if (a->key == NULL /*&& b->key != NULL*/) ret = -1;
	else if (/*a->key != NULL &&*/ b->key == NULL) ret = 1;
	else if ((ret = ItsIso14827DomainKey_cmp(a->key, b->key)) != 0) { }
	else if (a->peer == NULL && b->peer == NULL) ret = 0;
	else if (a->peer == NULL /*&& b->peer != NULL*/) ret = -1;
	else if (/*a->peer != NULL &&*/ b->peer == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->peer, b->peer)) != 0) { }
	else if (a->user == NULL && b->user == NULL) ret = 0;
	else if (a->user == NULL /*&& b->user != NULL*/) ret = -1;
	else if (/*a->user != NULL &&*/ b->user == NULL) ret = 1;
	else if ((ret = Dz1Asn1OctetStr_cmp(a->user, b->user)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// ItsIso14827DomainTimer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SubscriptionTimer
ItsIso14827SubscriptionTimer *ItsIso14827SubscriptionTimer_new(ItsIso14827DomainKey *key, 
															   Dz1Asn1UTF8Str *peer, 
															   Dz1Asn1OctetStr *user, 
															   u32_t subID, 
															   u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SubscriptionTimer *__internal_ret = (ItsIso14827SubscriptionTimer *)Dz1Calloc(sizeof(ItsIso14827SubscriptionTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SubscriptionTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->key = key;
		__internal_ret->peer = peer;
		__internal_ret->user = user;
		__internal_ret->subID = subID;
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SubscriptionTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SubscriptionTimer_purge(ItsIso14827SubscriptionTimer *p)
{
	if (p == NULL) return;
	ItsIso14827DomainKey_del(p->key);
	Dz1Asn1UTF8Str_del(p->peer);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827SubscriptionTimer_del(ItsIso14827SubscriptionTimer *p)
{
	if (p == NULL) return;
	ItsIso14827SubscriptionTimer_purge(p);
	Dz1Free(p);
}

void ItsIso14827SubscriptionTimer_dump(ItsIso14827SubscriptionTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("key = ")); ItsIso14827DomainKey_dump(p->key, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1Asn1UTF8Str_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827SubscriptionTimer_cmp(ItsIso14827SubscriptionTimer *a, ItsIso14827SubscriptionTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->key == NULL && b->key == NULL) ret = 0;
	else if (a->key == NULL /*&& b->key != NULL*/) ret = -1;
	else if (/*a->key != NULL &&*/ b->key == NULL) ret = 1;
	else if ((ret = ItsIso14827DomainKey_cmp(a->key, b->key)) != 0) { }
	else if (a->peer == NULL && b->peer == NULL) ret = 0;
	else if (a->peer == NULL /*&& b->peer != NULL*/) ret = -1;
	else if (/*a->peer != NULL &&*/ b->peer == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->peer, b->peer)) != 0) { }
	else if (a->user == NULL && b->user == NULL) ret = 0;
	else if (a->user == NULL /*&& b->user != NULL*/) ret = -1;
	else if (/*a->user != NULL &&*/ b->user == NULL) ret = 1;
	else if ((ret = Dz1Asn1OctetStr_cmp(a->user, b->user)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->subID, &b->subID)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// ItsIso14827SubscriptionTimer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827TimerPresent
static struct ItsIso14827TimerPresentMapA
{
	str_t str;
	ItsIso14827TimerPresent v;
} ItsIso14827TimerPresentMapA[] =
{
	{ (char *)"session", ItsIso14827TimerPresent_session },
	{ (char *)"domain", ItsIso14827TimerPresent_domain },
	{ (char *)"subscription", ItsIso14827TimerPresent_subscription },
	{ NULL, ItsIso14827TimerPresent_max }
};

str_t ItsIso14827TimerPresentStrA(ItsIso14827TimerPresent v)
{
	struct ItsIso14827TimerPresentMapA *i = NULL;
	for (i = ItsIso14827TimerPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827TimerPresent ItsIso14827TimerPresentFromStrA(str_t str)
{
	struct ItsIso14827TimerPresentMapA *i = NULL;
	for (i = ItsIso14827TimerPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827TimerPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827TimerPresentMapW
{
	wstr_t str;
	ItsIso14827TimerPresent v;
} ItsIso14827TimerPresentMapW[] =
{
	{ (wchar_t *)L"session", ItsIso14827TimerPresent_session },
	{ (wchar_t *)L"domain", ItsIso14827TimerPresent_domain },
	{ (wchar_t *)L"subscription", ItsIso14827TimerPresent_subscription },
	{ NULL, ItsIso14827TimerPresent_max }
};

wstr_t ItsIso14827TimerPresentStrW(ItsIso14827TimerPresent v)
{
	struct ItsIso14827TimerPresentMapW *i = NULL;
	for (i = ItsIso14827TimerPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827TimerPresent ItsIso14827TimerPresentFromStrW(wstr_t str)
{
	struct ItsIso14827TimerPresentMapW *i = NULL;
	for (i = ItsIso14827TimerPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827TimerPresent_max;
}
#endif // UNIX_SYSTEM

ItsIso14827TimerPresent *ItsIso14827TimerPresent_new(ItsIso14827TimerPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827TimerPresent *__internal_ret = (ItsIso14827TimerPresent *)Dz1Calloc(sizeof(ItsIso14827TimerPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ItsIso14827TimerPresent_dump(ItsIso14827TimerPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ItsIso14827TimerPresentStr(*v));
}

int ItsIso14827TimerPresent_cmp(ItsIso14827TimerPresent *a, ItsIso14827TimerPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// ItsIso14827TimerPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Timer
ItsIso14827Timer *ItsIso14827Timer_new(ItsIso14827TimerPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827Timer *ret = (ItsIso14827Timer *)Dz1Calloc(sizeof(ItsIso14827Timer), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827Timer_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ItsIso14827TimerPresent_session:
			// _U_cst_clone
			if (ptr != NULL) ret->x.session = (ItsIso14827SessionTimer *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827TimerPresent_domain:
			// _U_cst_clone
			if (ptr != NULL) ret->x.domain = (ItsIso14827DomainTimer *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827TimerPresent_subscription:
			// _U_cst_clone
			if (ptr != NULL) ret->x.subscription = (ItsIso14827SubscriptionTimer *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827TimerPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827Timer_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827Timer_purge(ItsIso14827Timer *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ItsIso14827TimerPresent_session:
		ItsIso14827SessionTimer_del(p->x.session);
		break;
	case ItsIso14827TimerPresent_domain:
		ItsIso14827DomainTimer_del(p->x.domain);
		break;
	case ItsIso14827TimerPresent_subscription:
		ItsIso14827SubscriptionTimer_del(p->x.subscription);
		break;
	default:
		break;
	}
}

void ItsIso14827Timer_del(ItsIso14827Timer *p)
{
	if (!p) return;
	ItsIso14827Timer_purge(p);
	Dz1Free(p);
}

void ItsIso14827Timer_dump(ItsIso14827Timer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ItsIso14827TimerPresent_session:
		Dz1Thread_printf(Dz1T("session = ")); ItsIso14827SessionTimer_dump(p->x.session, tab); 
		break;
	case ItsIso14827TimerPresent_domain:
		Dz1Thread_printf(Dz1T("domain = ")); ItsIso14827DomainTimer_dump(p->x.domain, tab); 
		break;
	case ItsIso14827TimerPresent_subscription:
		Dz1Thread_printf(Dz1T("subscription = ")); ItsIso14827SubscriptionTimer_dump(p->x.subscription, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int ItsIso14827Timer_cmp(ItsIso14827Timer *a, ItsIso14827Timer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL && b != NULL) ret = -1;
	else if (a != NULL && b == NULL) ret = 1;
	else if (a->present != b->present) ret = (int)(a->present - b->present);
	else
	{
		switch(a->present)
		{
		case ItsIso14827TimerPresent_session:
			if (a->x.session == NULL && b->x.session == NULL) ret = 0;
			else if (a->x.session == NULL /*&& b->x.session != NULL*/) ret = -1;
			else if (/*a->x.session != NULL &&*/ b->x.session == NULL) ret = 1;
			else if ((ret = ItsIso14827SessionTimer_cmp(a->x.session, b->x.session)) != 0) { }
			break;
		case ItsIso14827TimerPresent_domain:
			if (a->x.domain == NULL && b->x.domain == NULL) ret = 0;
			else if (a->x.domain == NULL /*&& b->x.domain != NULL*/) ret = -1;
			else if (/*a->x.domain != NULL &&*/ b->x.domain == NULL) ret = 1;
			else if ((ret = ItsIso14827DomainTimer_cmp(a->x.domain, b->x.domain)) != 0) { }
			break;
		case ItsIso14827TimerPresent_subscription:
			if (a->x.subscription == NULL && b->x.subscription == NULL) ret = 0;
			else if (a->x.subscription == NULL /*&& b->x.subscription != NULL*/) ret = -1;
			else if (/*a->x.subscription != NULL &&*/ b->x.subscription == NULL) ret = 1;
			else if ((ret = ItsIso14827SubscriptionTimer_cmp(a->x.subscription, b->x.subscription)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// ItsIso14827Timer
////////////////////////////////////////////////////////////////////////////////

