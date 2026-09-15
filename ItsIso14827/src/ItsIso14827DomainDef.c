////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827DomainDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainKey
ItsIso14827DomainKey *ItsIso14827DomainKey_new(ItsIso14827DomainType type, 
											   Dz1Asn1UTF8Str *name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainKey *__internal_ret = (ItsIso14827DomainKey *)Dz1Calloc(sizeof(ItsIso14827DomainKey), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainKey_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		__internal_ret->name = name;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainKey_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827DomainKey_copy(ItsIso14827DomainKey *dst, ItsIso14827DomainKey *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Asn1UTF8Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->type = src->type;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827DomainKey *ItsIso14827DomainKey_clone(ItsIso14827DomainKey *src, Dz1Error *err)
{
	ItsIso14827DomainKey *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827DomainKey *)Dz1Calloc(sizeof(ItsIso14827DomainKey), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainKey_delAndSetNull, (void *)&dst);
		if (ItsIso14827DomainKey_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainKey_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827DomainKey_purge(ItsIso14827DomainKey *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
}

void ItsIso14827DomainKey_del(ItsIso14827DomainKey *p)
{
	if (p == NULL) return;
	ItsIso14827DomainKey_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainKey_dump(ItsIso14827DomainKey *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("type = %s(%d)\n"), ItsIso14827DomainTypeStr(p->type), p->type);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Asn1UTF8Str_dump(p->name, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827DomainKey_cmp(ItsIso14827DomainKey *a, ItsIso14827DomainKey *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = (int)(a->type - b->type)) != 0) { }
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = Dz1Asn1UTF8Str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// ItsIso14827DomainKey
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainPresent
static struct ItsIso14827DomainPresentMapA
{
	str_t str;
	ItsIso14827DomainPresent v;
} ItsIso14827DomainPresentMapA[] =
{
	{ (char *)"server", ItsIso14827DomainPresent_server },
	{ (char *)"client", ItsIso14827DomainPresent_client },
	{ NULL, ItsIso14827DomainPresent_max }
};

str_t ItsIso14827DomainPresentStrA(ItsIso14827DomainPresent v)
{
	struct ItsIso14827DomainPresentMapA *i = NULL;
	for (i = ItsIso14827DomainPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827DomainPresent ItsIso14827DomainPresentFromStrA(str_t str)
{
	struct ItsIso14827DomainPresentMapA *i = NULL;
	for (i = ItsIso14827DomainPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827DomainPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ItsIso14827DomainPresentMapW
{
	wstr_t str;
	ItsIso14827DomainPresent v;
} ItsIso14827DomainPresentMapW[] =
{
	{ (wchar_t *)L"server", ItsIso14827DomainPresent_server },
	{ (wchar_t *)L"client", ItsIso14827DomainPresent_client },
	{ NULL, ItsIso14827DomainPresent_max }
};

wstr_t ItsIso14827DomainPresentStrW(ItsIso14827DomainPresent v)
{
	struct ItsIso14827DomainPresentMapW *i = NULL;
	for (i = ItsIso14827DomainPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ItsIso14827DomainPresent ItsIso14827DomainPresentFromStrW(wstr_t str)
{
	struct ItsIso14827DomainPresentMapW *i = NULL;
	for (i = ItsIso14827DomainPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ItsIso14827DomainPresent_max;
}
#endif // UNIX_SYSTEM

ItsIso14827DomainPresent *ItsIso14827DomainPresent_new(ItsIso14827DomainPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainPresent *__internal_ret = (ItsIso14827DomainPresent *)Dz1Calloc(sizeof(ItsIso14827DomainPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ItsIso14827DomainPresent_dump(ItsIso14827DomainPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ItsIso14827DomainPresentStr(*v));
}

int ItsIso14827DomainPresent_cmp(ItsIso14827DomainPresent *a, ItsIso14827DomainPresent *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else ret = (int)(*a - *b);
	return ret;
}
// ItsIso14827DomainPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Domain
ItsIso14827Domain *ItsIso14827Domain_new(ItsIso14827DomainPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827Domain *ret = (ItsIso14827Domain *)Dz1Calloc(sizeof(ItsIso14827Domain), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827Domain_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ItsIso14827DomainPresent_server:
			// _U_cst_clone
			if (ptr != NULL) ret->x.server = (ItsIso14827ServerDomain *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827DomainPresent_client:
			// _U_cst_clone
			if (ptr != NULL) ret->x.client = (ItsIso14827ClientDomain *)ptr;
			ERR_CLEAR(errp);
			break;
		case ItsIso14827DomainPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827Domain_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827Domain_purge(ItsIso14827Domain *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ItsIso14827DomainPresent_server:
		ItsIso14827ServerDomain_del(p->x.server);
		break;
	case ItsIso14827DomainPresent_client:
		ItsIso14827ClientDomain_del(p->x.client);
		break;
	default:
		break;
	}
}

void ItsIso14827Domain_del(ItsIso14827Domain *p)
{
	if (!p) return;
	ItsIso14827Domain_purge(p);
	Dz1Free(p);
}

void ItsIso14827Domain_dump(ItsIso14827Domain *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ItsIso14827DomainPresent_server:
		Dz1Thread_printf(Dz1T("server = ")); ItsIso14827ServerDomain_dump(p->x.server, tab); 
		break;
	case ItsIso14827DomainPresent_client:
		Dz1Thread_printf(Dz1T("client = ")); ItsIso14827ClientDomain_dump(p->x.client, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

int ItsIso14827Domain_cmp(ItsIso14827Domain *a, ItsIso14827Domain *b)
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
		case ItsIso14827DomainPresent_server:
			if (a->x.server == NULL && b->x.server == NULL) ret = 0;
			else if (a->x.server == NULL /*&& b->x.server != NULL*/) ret = -1;
			else if (/*a->x.server != NULL &&*/ b->x.server == NULL) ret = 1;
			else if ((ret = ItsIso14827ServerDomain_cmp(a->x.server, b->x.server)) != 0) { }
			break;
		case ItsIso14827DomainPresent_client:
			if (a->x.client == NULL && b->x.client == NULL) ret = 0;
			else if (a->x.client == NULL /*&& b->x.client != NULL*/) ret = -1;
			else if (/*a->x.client != NULL &&*/ b->x.client == NULL) ret = 1;
			else if ((ret = ItsIso14827ClientDomain_cmp(a->x.client, b->x.client)) != 0) { }
			break;
		default:
			ret = 0;
			break;
		}
	}
	return ret;
}

// ItsIso14827Domain
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainList
static Dz1Error ItsIso14827DomainList_add(ItsIso14827DomainList *p, ItsIso14827Domain *data)
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

static bool_t ItsIso14827DomainList_remove(ItsIso14827DomainList *p, ItsIso14827Domain *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827Domain *ItsIso14827DomainList_extract(ItsIso14827DomainList *p, ItsIso14827Domain *key)
{
	return (ItsIso14827Domain *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827DomainListMkArrArg
{
	ItsIso14827Domain **arr;
	unsigned int idx;
} ItsIso14827DomainListMkArrArg;

static Dz1Error _ItsIso14827DomainList_get_array(void *ptr, ItsIso14827Domain *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainListMkArrArg *arg = (ItsIso14827DomainListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827Domain **ItsIso14827DomainList_get_array(ItsIso14827DomainList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827Domain **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827Domain **)Dz1Calloc(sizeof(ItsIso14827Domain *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827DomainListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827DomainList_get_array, (void *)&arg);
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

static Dz1Error ItsIso14827DomainList_travelForward(ItsIso14827DomainList *p, Dz1Error (*func)(void *ptr, ItsIso14827Domain *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827DomainList_travelBackward(ItsIso14827DomainList *p, Dz1Error (*func)(void *ptr, ItsIso14827Domain *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827Domain *ItsIso14827DomainList_find(ItsIso14827DomainList *p, ItsIso14827Domain *key)
{
	return (ItsIso14827Domain *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827DomainList_count(ItsIso14827DomainList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827DomainList *ItsIso14827DomainList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainList *ret = (ItsIso14827DomainList *)Dz1Calloc(sizeof(ItsIso14827DomainList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827Domain_cmp,
				(Dz1DelFunc)ItsIso14827Domain_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827DomainList_count;
			ret->travel = ItsIso14827DomainList_travelForward;
			ret->travelForward = ItsIso14827DomainList_travelForward;
			ret->travelBackward = ItsIso14827DomainList_travelBackward;
			ret->get_array = ItsIso14827DomainList_get_array;
			ret->add = ItsIso14827DomainList_add;
			ret->remove = ItsIso14827DomainList_remove;
			ret->find = ItsIso14827DomainList_find;
			ret->extract = ItsIso14827DomainList_extract;
			ret->cmp = ItsIso14827Domain_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827DomainList_purge(ItsIso14827DomainList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827DomainList_del(ItsIso14827DomainList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827DomainList_dump(void *ptr, ItsIso14827Domain *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827Domain_dump(p, tab);
	return err;
}

void ItsIso14827DomainList_dump(ItsIso14827DomainList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827DomainList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainSessionEntry
ItsIso14827DomainSessionEntry *ItsIso14827DomainSessionEntry_new(ItsIso14827SessionKey *session, 
																 ItsIso14827DomainKey *domain, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainSessionEntry *__internal_ret = (ItsIso14827DomainSessionEntry *)Dz1Calloc(sizeof(ItsIso14827DomainSessionEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->session = session;
		__internal_ret->domain = domain;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainSessionEntry_purge(ItsIso14827DomainSessionEntry *p)
{
	if (p == NULL) return;
	ItsIso14827SessionKey_del(p->session);
	ItsIso14827DomainKey_del(p->domain);
}

void ItsIso14827DomainSessionEntry_del(ItsIso14827DomainSessionEntry *p)
{
	if (p == NULL) return;
	ItsIso14827DomainSessionEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainSessionEntry_dump(ItsIso14827DomainSessionEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("session = ")); ItsIso14827SessionKey_dump(p->session, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("domain = ")); ItsIso14827DomainKey_dump(p->domain, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827DomainSessionEntry_cmp(ItsIso14827DomainSessionEntry *a, ItsIso14827DomainSessionEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->session == NULL && b->session == NULL) ret = 0;
	else if (a->session == NULL /*&& b->session != NULL*/) ret = -1;
	else if (/*a->session != NULL &&*/ b->session == NULL) ret = 1;
	else if ((ret = ItsIso14827SessionKey_cmp(a->session, b->session)) != 0) { }
	return ret;
}
// ItsIso14827DomainSessionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainSessionList
static Dz1Error ItsIso14827DomainSessionList_add(ItsIso14827DomainSessionList *p, ItsIso14827DomainSessionEntry *data)
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

static bool_t ItsIso14827DomainSessionList_remove(ItsIso14827DomainSessionList *p, ItsIso14827DomainSessionEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827DomainSessionEntry *ItsIso14827DomainSessionList_extract(ItsIso14827DomainSessionList *p, ItsIso14827DomainSessionEntry *key)
{
	return (ItsIso14827DomainSessionEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827DomainSessionListMkArrArg
{
	ItsIso14827DomainSessionEntry **arr;
	unsigned int idx;
} ItsIso14827DomainSessionListMkArrArg;

static Dz1Error _ItsIso14827DomainSessionList_get_array(void *ptr, ItsIso14827DomainSessionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainSessionListMkArrArg *arg = (ItsIso14827DomainSessionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827DomainSessionEntry **ItsIso14827DomainSessionList_get_array(ItsIso14827DomainSessionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827DomainSessionEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827DomainSessionEntry **)Dz1Calloc(sizeof(ItsIso14827DomainSessionEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827DomainSessionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827DomainSessionList_get_array, (void *)&arg);
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

static Dz1Error ItsIso14827DomainSessionList_travelForward(ItsIso14827DomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainSessionEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827DomainSessionList_travelBackward(ItsIso14827DomainSessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827DomainSessionEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827DomainSessionEntry *ItsIso14827DomainSessionList_find(ItsIso14827DomainSessionList *p, ItsIso14827DomainSessionEntry *key)
{
	return (ItsIso14827DomainSessionEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827DomainSessionList_count(ItsIso14827DomainSessionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827DomainSessionList *ItsIso14827DomainSessionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainSessionList *ret = (ItsIso14827DomainSessionList *)Dz1Calloc(sizeof(ItsIso14827DomainSessionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainSessionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827DomainSessionEntry_cmp,
				(Dz1DelFunc)ItsIso14827DomainSessionEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827DomainSessionList_count;
			ret->travel = ItsIso14827DomainSessionList_travelForward;
			ret->travelForward = ItsIso14827DomainSessionList_travelForward;
			ret->travelBackward = ItsIso14827DomainSessionList_travelBackward;
			ret->get_array = ItsIso14827DomainSessionList_get_array;
			ret->add = ItsIso14827DomainSessionList_add;
			ret->remove = ItsIso14827DomainSessionList_remove;
			ret->find = ItsIso14827DomainSessionList_find;
			ret->extract = ItsIso14827DomainSessionList_extract;
			ret->cmp = ItsIso14827DomainSessionEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827DomainSessionList_purge(ItsIso14827DomainSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827DomainSessionList_del(ItsIso14827DomainSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827DomainSessionList_dump(void *ptr, ItsIso14827DomainSessionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827DomainSessionEntry_dump(p, tab);
	return err;
}

void ItsIso14827DomainSessionList_dump(ItsIso14827DomainSessionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827DomainSessionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainMgr
ItsIso14827DomainMgr *ItsIso14827DomainMgr_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainMgr *__internal_ret = (ItsIso14827DomainMgr *)Dz1Calloc(sizeof(ItsIso14827DomainMgr), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainMgr_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->domains = ItsIso14827DomainList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->sessions = ItsIso14827DomainSessionList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainMgr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainMgr_purge(ItsIso14827DomainMgr *p)
{
	if (p == NULL) return;
	ItsIso14827DomainList_del(p->domains);
	ItsIso14827DomainSessionList_del(p->sessions);
}

void ItsIso14827DomainMgr_del(ItsIso14827DomainMgr *p)
{
	if (p == NULL) return;
	ItsIso14827DomainMgr_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainMgr_dump(ItsIso14827DomainMgr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domains = ")); ItsIso14827DomainList_dump(p->domains, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sessions = ")); ItsIso14827DomainSessionList_dump(p->sessions, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainMgr
////////////////////////////////////////////////////////////////////////////////

