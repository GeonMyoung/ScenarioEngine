////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827DefLocal.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CodecOIDMap
ItsIso14827CodecOIDMap *ItsIso14827CodecOIDMap_new(Dz1Asn1OID *oid, 
												   Dz1Asn1Codec mean, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827CodecOIDMap *__internal_ret = (ItsIso14827CodecOIDMap *)Dz1Calloc(sizeof(ItsIso14827CodecOIDMap), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827CodecOIDMap_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->oid = oid;
		__internal_ret->mean = mean;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827CodecOIDMap_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827CodecOIDMap_purge(ItsIso14827CodecOIDMap *p)
{
	if (p == NULL) return;
	Dz1Asn1OID_del(p->oid);
}

void ItsIso14827CodecOIDMap_del(ItsIso14827CodecOIDMap *p)
{
	if (p == NULL) return;
	ItsIso14827CodecOIDMap_purge(p);
	Dz1Free(p);
}

void ItsIso14827CodecOIDMap_dump(ItsIso14827CodecOIDMap *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("oid = ")); Dz1Asn1OID_dump(p->oid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("mean = %s(%d)\n"), Dz1Asn1CodecStr(p->mean), p->mean);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827CodecOIDMap_cmp(ItsIso14827CodecOIDMap *a, ItsIso14827CodecOIDMap *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->oid == NULL && b->oid == NULL) ret = 0;
	else if (a->oid == NULL /*&& b->oid != NULL*/) ret = -1;
	else if (/*a->oid != NULL &&*/ b->oid == NULL) ret = 1;
	else if ((ret = Dz1Asn1OID_cmp(a->oid, b->oid)) != 0) { }
	return ret;
}
// ItsIso14827CodecOIDMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827CodecOIDMapList
static Dz1Error ItsIso14827CodecOIDMapList_add(ItsIso14827CodecOIDMapList *p, ItsIso14827CodecOIDMap *data)
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

static bool_t ItsIso14827CodecOIDMapList_remove(ItsIso14827CodecOIDMapList *p, ItsIso14827CodecOIDMap *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827CodecOIDMap *ItsIso14827CodecOIDMapList_extract(ItsIso14827CodecOIDMapList *p, ItsIso14827CodecOIDMap *key)
{
	return (ItsIso14827CodecOIDMap *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827CodecOIDMapListMkArrArg
{
	ItsIso14827CodecOIDMap **arr;
	unsigned int idx;
} ItsIso14827CodecOIDMapListMkArrArg;

static Dz1Error _ItsIso14827CodecOIDMapList_get_array(void *ptr, ItsIso14827CodecOIDMap *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827CodecOIDMapListMkArrArg *arg = (ItsIso14827CodecOIDMapListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827CodecOIDMap **ItsIso14827CodecOIDMapList_get_array(ItsIso14827CodecOIDMapList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827CodecOIDMap **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827CodecOIDMap **)Dz1Calloc(sizeof(ItsIso14827CodecOIDMap *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827CodecOIDMapListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827CodecOIDMapList_get_array, (void *)&arg);
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

static Dz1Error ItsIso14827CodecOIDMapList_travelForward(ItsIso14827CodecOIDMapList *p, Dz1Error (*func)(void *ptr, ItsIso14827CodecOIDMap *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827CodecOIDMapList_travelBackward(ItsIso14827CodecOIDMapList *p, Dz1Error (*func)(void *ptr, ItsIso14827CodecOIDMap *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827CodecOIDMap *ItsIso14827CodecOIDMapList_find(ItsIso14827CodecOIDMapList *p, ItsIso14827CodecOIDMap *key)
{
	return (ItsIso14827CodecOIDMap *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827CodecOIDMapList_count(ItsIso14827CodecOIDMapList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827CodecOIDMapList *ItsIso14827CodecOIDMapList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827CodecOIDMapList *ret = (ItsIso14827CodecOIDMapList *)Dz1Calloc(sizeof(ItsIso14827CodecOIDMapList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827CodecOIDMapList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827CodecOIDMap_cmp,
				(Dz1DelFunc)ItsIso14827CodecOIDMap_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827CodecOIDMapList_count;
			ret->travel = ItsIso14827CodecOIDMapList_travelForward;
			ret->travelForward = ItsIso14827CodecOIDMapList_travelForward;
			ret->travelBackward = ItsIso14827CodecOIDMapList_travelBackward;
			ret->get_array = ItsIso14827CodecOIDMapList_get_array;
			ret->add = ItsIso14827CodecOIDMapList_add;
			ret->remove = ItsIso14827CodecOIDMapList_remove;
			ret->find = ItsIso14827CodecOIDMapList_find;
			ret->extract = ItsIso14827CodecOIDMapList_extract;
			ret->cmp = ItsIso14827CodecOIDMap_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827CodecOIDMapList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827CodecOIDMapList_purge(ItsIso14827CodecOIDMapList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827CodecOIDMapList_del(ItsIso14827CodecOIDMapList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827CodecOIDMapList_dump(void *ptr, ItsIso14827CodecOIDMap *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827CodecOIDMap_dump(p, tab);
	return err;
}

void ItsIso14827CodecOIDMapList_dump(ItsIso14827CodecOIDMapList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827CodecOIDMapList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827CodecOIDMapList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ServerDomainViolatedPublication
ItsIso14827ServerDomainViolatedPublication *ItsIso14827ServerDomainViolatedPublication_new(ItsIso14827CallbackPublication inform, 
																						   void *param, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ServerDomainViolatedPublication *__internal_ret = (ItsIso14827ServerDomainViolatedPublication *)Dz1Calloc(sizeof(ItsIso14827ServerDomainViolatedPublication), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainViolatedPublication_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->inform = inform;
		__internal_ret->param = param;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainViolatedPublication_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ServerDomainViolatedPublication_copy(ItsIso14827ServerDomainViolatedPublication *dst, ItsIso14827ServerDomainViolatedPublication *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->inform = src->inform;
		dst->param = src->param;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ServerDomainViolatedPublication *ItsIso14827ServerDomainViolatedPublication_clone(ItsIso14827ServerDomainViolatedPublication *src, Dz1Error *err)
{
	ItsIso14827ServerDomainViolatedPublication *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ServerDomainViolatedPublication *)Dz1Calloc(sizeof(ItsIso14827ServerDomainViolatedPublication), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ServerDomainViolatedPublication_delAndSetNull, (void *)&dst);
		if (ItsIso14827ServerDomainViolatedPublication_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ServerDomainViolatedPublication_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ServerDomainViolatedPublication_purge(ItsIso14827ServerDomainViolatedPublication *p)
{
	if (p == NULL) return;
}

void ItsIso14827ServerDomainViolatedPublication_del(ItsIso14827ServerDomainViolatedPublication *p)
{
	if (p == NULL) return;
	ItsIso14827ServerDomainViolatedPublication_purge(p);
	Dz1Free(p);
}

void ItsIso14827ServerDomainViolatedPublication_dump(ItsIso14827ServerDomainViolatedPublication *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("inform = %p\n"), p->inform);
		Dz1Thread_tprintf(tab, Dz1T("param = %p\n"), p->param);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ServerDomainViolatedPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClientDomainViolatedSubscription
ItsIso14827ClientDomainViolatedSubscription *ItsIso14827ClientDomainViolatedSubscription_new(ItsIso14827CallbackViolatedSubRcvd inform, 
																							 void *param, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClientDomainViolatedSubscription *__internal_ret = (ItsIso14827ClientDomainViolatedSubscription *)Dz1Calloc(sizeof(ItsIso14827ClientDomainViolatedSubscription), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainViolatedSubscription_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->inform = inform;
		__internal_ret->param = param;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainViolatedSubscription_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ItsIso14827ClientDomainViolatedSubscription_copy(ItsIso14827ClientDomainViolatedSubscription *dst, ItsIso14827ClientDomainViolatedSubscription *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->inform = src->inform;
		dst->param = src->param;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ItsIso14827ClientDomainViolatedSubscription *ItsIso14827ClientDomainViolatedSubscription_clone(ItsIso14827ClientDomainViolatedSubscription *src, Dz1Error *err)
{
	ItsIso14827ClientDomainViolatedSubscription *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ItsIso14827ClientDomainViolatedSubscription *)Dz1Calloc(sizeof(ItsIso14827ClientDomainViolatedSubscription), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClientDomainViolatedSubscription_delAndSetNull, (void *)&dst);
		if (ItsIso14827ClientDomainViolatedSubscription_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClientDomainViolatedSubscription_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ItsIso14827ClientDomainViolatedSubscription_purge(ItsIso14827ClientDomainViolatedSubscription *p)
{
	if (p == NULL) return;
}

void ItsIso14827ClientDomainViolatedSubscription_del(ItsIso14827ClientDomainViolatedSubscription *p)
{
	if (p == NULL) return;
	ItsIso14827ClientDomainViolatedSubscription_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClientDomainViolatedSubscription_dump(ItsIso14827ClientDomainViolatedSubscription *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("inform = %p\n"), p->inform);
		Dz1Thread_tprintf(tab, Dz1T("param = %p\n"), p->param);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ClientDomainViolatedSubscription
////////////////////////////////////////////////////////////////////////////////

