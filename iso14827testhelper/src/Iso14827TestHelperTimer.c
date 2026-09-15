////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Iso14827TestHelperTimer.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimerSession
Iso14827TestHelperTimerSession *Iso14827TestHelperTimerSession_new(Dz1Asn1UTF8Str *my_domain, 
																   Dz1Asn1UTF8Str *peer_domain, 
																   Dz1Asn1UTF8Str *user, 
																   u32_t identifier, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperTimerSession *__internal_ret = (Iso14827TestHelperTimerSession *)Dz1Calloc(sizeof(Iso14827TestHelperTimerSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperTimerSession_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_domain = my_domain;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->user = user;
		__internal_ret->identifier = identifier;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperTimerSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827TestHelperTimerSession_purge(Iso14827TestHelperTimerSession *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->my_domain);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	Dz1Asn1UTF8Str_del(p->user);
}

void Iso14827TestHelperTimerSession_del(Iso14827TestHelperTimerSession *p)
{
	if (p == NULL) return;
	Iso14827TestHelperTimerSession_purge(p);
	Dz1Free(p);
}

void Iso14827TestHelperTimerSession_dump(Iso14827TestHelperTimerSession *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Asn1UTF8Str_dump(p->my_domain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1UTF8Str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("identifier = ")); Dz1u32_dump(&p->identifier, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Iso14827TestHelperTimerSession_cmp(Iso14827TestHelperTimerSession *a, Iso14827TestHelperTimerSession *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->my_domain == NULL && b->my_domain == NULL) ret = 0;
	else if (a->my_domain == NULL /*&& b->my_domain != NULL*/) ret = -1;
	else if (/*a->my_domain != NULL &&*/ b->my_domain == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->my_domain, b->my_domain)) != 0) { }
	else if (a->peer_domain == NULL && b->peer_domain == NULL) ret = 0;
	else if (a->peer_domain == NULL /*&& b->peer_domain != NULL*/) ret = -1;
	else if (/*a->peer_domain != NULL &&*/ b->peer_domain == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->peer_domain, b->peer_domain)) != 0) { }
	else if (a->user == NULL && b->user == NULL) ret = 0;
	else if (a->user == NULL /*&& b->user != NULL*/) ret = -1;
	else if (/*a->user != NULL &&*/ b->user == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->user, b->user)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->identifier, &b->identifier)) != 0) { }
	return ret;
}
// Iso14827TestHelperTimerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimerDuo
Iso14827TestHelperTimerDuo *Iso14827TestHelperTimerDuo_new(ItsIso14827DomainType my_type, 
														   Dz1Asn1UTF8Str *my_domain, 
														   Dz1Asn1UTF8Str *peer_domain, 
														   Dz1Asn1OctetStr *user, 
														   u32_t identifier, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperTimerDuo *__internal_ret = (Iso14827TestHelperTimerDuo *)Dz1Calloc(sizeof(Iso14827TestHelperTimerDuo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperTimerDuo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->my_type = my_type;
		__internal_ret->my_domain = my_domain;
		__internal_ret->peer_domain = peer_domain;
		__internal_ret->user = user;
		__internal_ret->identifier = identifier;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperTimerDuo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827TestHelperTimerDuo_purge(Iso14827TestHelperTimerDuo *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->my_domain);
	Dz1Asn1UTF8Str_del(p->peer_domain);
	Dz1Asn1OctetStr_del(p->user);
}

void Iso14827TestHelperTimerDuo_del(Iso14827TestHelperTimerDuo *p)
{
	if (p == NULL) return;
	Iso14827TestHelperTimerDuo_purge(p);
	Dz1Free(p);
}

void Iso14827TestHelperTimerDuo_dump(Iso14827TestHelperTimerDuo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("my_type = %s(%d)\n"), ItsIso14827DomainTypeStr(p->my_type), p->my_type);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("my_domain = ")); Dz1Asn1UTF8Str_dump(p->my_domain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer_domain = ")); Dz1Asn1UTF8Str_dump(p->peer_domain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("identifier = ")); Dz1u32_dump(&p->identifier, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Iso14827TestHelperTimerDuo_cmp(Iso14827TestHelperTimerDuo *a, Iso14827TestHelperTimerDuo *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = (int)(a->my_type - b->my_type)) != 0) { }
	else if (a->my_domain == NULL && b->my_domain == NULL) ret = 0;
	else if (a->my_domain == NULL /*&& b->my_domain != NULL*/) ret = -1;
	else if (/*a->my_domain != NULL &&*/ b->my_domain == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->my_domain, b->my_domain)) != 0) { }
	else if (a->peer_domain == NULL && b->peer_domain == NULL) ret = 0;
	else if (a->peer_domain == NULL /*&& b->peer_domain != NULL*/) ret = -1;
	else if (/*a->peer_domain != NULL &&*/ b->peer_domain == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->peer_domain, b->peer_domain)) != 0) { }
	else if (a->user == NULL && b->user == NULL) ret = 0;
	else if (a->user == NULL /*&& b->user != NULL*/) ret = -1;
	else if (/*a->user != NULL &&*/ b->user == NULL) ret = 1;
	else if ((ret = Dz1Asn1OctetStr_cmp(a->user, b->user)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->identifier, &b->identifier)) != 0) { }
	return ret;
}
// Iso14827TestHelperTimerDuo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimerED
Iso14827TestHelperTimerED *Iso14827TestHelperTimerED_new(Dz1Asn1OctetStr *user, 
														 Dz1Str oidStr, 
														 u32_t subID, 
														 u32_t identifier, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperTimerED *__internal_ret = (Iso14827TestHelperTimerED *)Dz1Calloc(sizeof(Iso14827TestHelperTimerED), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperTimerED_delAndSetNull, (void *)&__internal_ret);
		
		if (oidStr && (__internal_ret->oidStr = Dz1Str_clone(oidStr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->user = user;
			__internal_ret->subID = subID;
			__internal_ret->identifier = identifier;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperTimerED_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Iso14827TestHelperTimerED_purge(Iso14827TestHelperTimerED *p)
{
	if (p == NULL) return;
	Dz1Asn1OctetStr_del(p->user);
	Dz1Str_del(p->oidStr);
}

void Iso14827TestHelperTimerED_del(Iso14827TestHelperTimerED *p)
{
	if (p == NULL) return;
	Iso14827TestHelperTimerED_purge(p);
	Dz1Free(p);
}

void Iso14827TestHelperTimerED_dump(Iso14827TestHelperTimerED *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("oidStr = ")); Dz1Str_dump(p->oidStr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("subID = ")); Dz1u32_dump(&p->subID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("identifier = ")); Dz1u32_dump(&p->identifier, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Iso14827TestHelperTimerED_cmp(Iso14827TestHelperTimerED *a, Iso14827TestHelperTimerED *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->user == NULL && b->user == NULL) ret = 0;
	else if (a->user == NULL /*&& b->user != NULL*/) ret = -1;
	else if (/*a->user != NULL &&*/ b->user == NULL) ret = 1;
	else if ((ret = Dz1Asn1OctetStr_cmp(a->user, b->user)) != 0) { }
	else if (a->oidStr == NULL && b->oidStr == NULL) ret = 0;
	else if (a->oidStr == NULL /*&& b->oidStr != NULL*/) ret = -1;
	else if (/*a->oidStr != NULL &&*/ b->oidStr == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->oidStr, b->oidStr)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->subID, &b->subID)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->identifier, &b->identifier)) != 0) { }
	return ret;
}
// Iso14827TestHelperTimerED
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimerPresent
static struct Iso14827TestHelperTimerPresentMapA
{
	str_t str;
	Iso14827TestHelperTimerPresent v;
} Iso14827TestHelperTimerPresentMapA[] =
{
	{ (char *)"general", Iso14827TestHelperTimerPresent_general },
	{ (char *)"ed", Iso14827TestHelperTimerPresent_ed },
	{ (char *)"client", Iso14827TestHelperTimerPresent_client },
	{ (char *)"duo", Iso14827TestHelperTimerPresent_duo },
	{ NULL, Iso14827TestHelperTimerPresent_max }
};

str_t Iso14827TestHelperTimerPresentStrA(Iso14827TestHelperTimerPresent v)
{
	struct Iso14827TestHelperTimerPresentMapA *i = NULL;
	for (i = Iso14827TestHelperTimerPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestHelperTimerPresent Iso14827TestHelperTimerPresentFromStrA(str_t str)
{
	struct Iso14827TestHelperTimerPresentMapA *i = NULL;
	for (i = Iso14827TestHelperTimerPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestHelperTimerPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Iso14827TestHelperTimerPresentMapW
{
	wstr_t str;
	Iso14827TestHelperTimerPresent v;
} Iso14827TestHelperTimerPresentMapW[] =
{
	{ (wchar_t *)L"general", Iso14827TestHelperTimerPresent_general },
	{ (wchar_t *)L"ed", Iso14827TestHelperTimerPresent_ed },
	{ (wchar_t *)L"client", Iso14827TestHelperTimerPresent_client },
	{ (wchar_t *)L"duo", Iso14827TestHelperTimerPresent_duo },
	{ NULL, Iso14827TestHelperTimerPresent_max }
};

wstr_t Iso14827TestHelperTimerPresentStrW(Iso14827TestHelperTimerPresent v)
{
	struct Iso14827TestHelperTimerPresentMapW *i = NULL;
	for (i = Iso14827TestHelperTimerPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Iso14827TestHelperTimerPresent Iso14827TestHelperTimerPresentFromStrW(wstr_t str)
{
	struct Iso14827TestHelperTimerPresentMapW *i = NULL;
	for (i = Iso14827TestHelperTimerPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Iso14827TestHelperTimerPresent_max;
}
#endif // UNIX_SYSTEM

Iso14827TestHelperTimerPresent *Iso14827TestHelperTimerPresent_new(Iso14827TestHelperTimerPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperTimerPresent *__internal_ret = (Iso14827TestHelperTimerPresent *)Dz1Calloc(sizeof(Iso14827TestHelperTimerPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Iso14827TestHelperTimerPresent_dump(Iso14827TestHelperTimerPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Iso14827TestHelperTimerPresentStr(*v));
}

int Iso14827TestHelperTimerPresent_cmp(Iso14827TestHelperTimerPresent *a, Iso14827TestHelperTimerPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// Iso14827TestHelperTimerPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestHelperTimer
Iso14827TestHelperTimer *Iso14827TestHelperTimer_new(Iso14827TestHelperTimerPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Iso14827TestHelperTimer *ret = (Iso14827TestHelperTimer *)Dz1Calloc(sizeof(Iso14827TestHelperTimer), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Iso14827TestHelperTimer_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Iso14827TestHelperTimerPresent_general:
			// _U_prim_clone
			if (ptr != NULL) ret->x.general = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestHelperTimerPresent_ed:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ed = (Iso14827TestHelperTimerED *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestHelperTimerPresent_client:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client = (Iso14827TestHelperTimerSession *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestHelperTimerPresent_duo:
			// _U_cst_clone
			if (ptr != NULL) ret->x.duo = (Iso14827TestHelperTimerDuo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Iso14827TestHelperTimerPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Iso14827TestHelperTimer_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Iso14827TestHelperTimer_purge(Iso14827TestHelperTimer *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Iso14827TestHelperTimerPresent_general:
		break;
	case Iso14827TestHelperTimerPresent_ed:
		Iso14827TestHelperTimerED_del(p->x.ed);
		break;
	case Iso14827TestHelperTimerPresent_client:
		Iso14827TestHelperTimerSession_del(p->x.client);
		break;
	case Iso14827TestHelperTimerPresent_duo:
		Iso14827TestHelperTimerDuo_del(p->x.duo);
		break;
	default:
		break;
	}
}

void Iso14827TestHelperTimer_del(Iso14827TestHelperTimer *p)
{
	if (!p) return;
	Iso14827TestHelperTimer_purge(p);
	Dz1Free(p);
}

void Iso14827TestHelperTimer_dump(Iso14827TestHelperTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Iso14827TestHelperTimerPresent_general:
		Dz1Thread_printf(Dz1T("general = ")); Dz1u32_dump(&p->x.general, tab); 
		break;
	case Iso14827TestHelperTimerPresent_ed:
		Dz1Thread_printf(Dz1T("ed = ")); Iso14827TestHelperTimerED_dump(p->x.ed, tab); 
		break;
	case Iso14827TestHelperTimerPresent_client:
		Dz1Thread_printf(Dz1T("client = ")); Iso14827TestHelperTimerSession_dump(p->x.client, tab); 
		break;
	case Iso14827TestHelperTimerPresent_duo:
		Dz1Thread_printf(Dz1T("duo = ")); Iso14827TestHelperTimerDuo_dump(p->x.duo, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int Iso14827TestHelperTimer_cmp(Iso14827TestHelperTimer *a, Iso14827TestHelperTimer *b)
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
		case Iso14827TestHelperTimerPresent_general:
			if ((ret = Dz1u32_cmp(&a->x.general, &b->x.general)) != 0) { }
			break;
		case Iso14827TestHelperTimerPresent_ed:
			if (a->x.ed == NULL && b->x.ed == NULL) ret = 0;
			else if (a->x.ed == NULL /*&& b->x.ed != NULL*/) ret = -1;
			else if (/*a->x.ed != NULL &&*/ b->x.ed == NULL) ret = 1;
			else if ((ret = Iso14827TestHelperTimerED_cmp(a->x.ed, b->x.ed)) != 0) { }
			break;
		case Iso14827TestHelperTimerPresent_client:
			if (a->x.client == NULL && b->x.client == NULL) ret = 0;
			else if (a->x.client == NULL /*&& b->x.client != NULL*/) ret = -1;
			else if (/*a->x.client != NULL &&*/ b->x.client == NULL) ret = 1;
			else if ((ret = Iso14827TestHelperTimerSession_cmp(a->x.client, b->x.client)) != 0) { }
			break;
		case Iso14827TestHelperTimerPresent_duo:
			if (a->x.duo == NULL && b->x.duo == NULL) ret = 0;
			else if (a->x.duo == NULL /*&& b->x.duo != NULL*/) ret = -1;
			else if (/*a->x.duo != NULL &&*/ b->x.duo == NULL) ret = 1;
			else if ((ret = Iso14827TestHelperTimerDuo_cmp(a->x.duo, b->x.duo)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// Iso14827TestHelperTimer
////////////////////////////////////////////////////////////////////////////////

