////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "TechnicalRegulation2Def.h"

////////////////////////////////////////////////////////////////////////////////
// NetworkInfoEntry
NetworkInfoEntry *NetworkInfoEntry_new(Dz1Str ipAddress, 
									   u16_t servicePort, 
									   Dz1Str provideServiceContext, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	NetworkInfoEntry *__internal_ret = (NetworkInfoEntry *)Dz1Calloc(sizeof(NetworkInfoEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(NetworkInfoEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (ipAddress && (__internal_ret->ipAddress = Dz1Str_clone(ipAddress, errp)) == NULL) ERR_OUT(errp);
		else if (provideServiceContext && (__internal_ret->provideServiceContext = Dz1Str_clone(provideServiceContext, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->servicePort = servicePort;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (NetworkInfoEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t NetworkInfoEntry_copy(NetworkInfoEntry *dst, NetworkInfoEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ipAddress && (dst->ipAddress = Dz1Str_clone(src->ipAddress, errp)) == NULL) ERR_OUT(errp);
	else if (src->provideServiceContext && (dst->provideServiceContext = Dz1Str_clone(src->provideServiceContext, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->servicePort = src->servicePort;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

NetworkInfoEntry *NetworkInfoEntry_clone(NetworkInfoEntry *src, Dz1Error *err)
{
	NetworkInfoEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (NetworkInfoEntry *)Dz1Calloc(sizeof(NetworkInfoEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(NetworkInfoEntry_delAndSetNull, (void *)&dst);
		if (NetworkInfoEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (NetworkInfoEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void NetworkInfoEntry_purge(NetworkInfoEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->ipAddress);
	Dz1Str_del(p->provideServiceContext);
}

void NetworkInfoEntry_del(NetworkInfoEntry *p)
{
	if (p == NULL) return;
	NetworkInfoEntry_purge(p);
	Dz1Free(p);
}

void NetworkInfoEntry_dump(NetworkInfoEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ipAddress = ")); Dz1Str_dump(p->ipAddress, tab); 
		Dz1Thread_tprintf(tab, Dz1T("servicePort = ")); Dz1u16_dump(&p->servicePort, tab); 
		Dz1Thread_tprintf(tab, Dz1T("provideServiceContext = ")); Dz1Str_dump(p->provideServiceContext, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int NetworkInfoEntry_cmp(NetworkInfoEntry *a, NetworkInfoEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->ipAddress == NULL && b->ipAddress == NULL) ret = 0;
	else if (a->ipAddress == NULL /*&& b->ipAddress != NULL*/) ret = -1;
	else if (/*a->ipAddress != NULL &&*/ b->ipAddress == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->ipAddress, b->ipAddress)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->servicePort, &b->servicePort)) != 0) { }
	return ret;
}
// NetworkInfoEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// NetworkInfoList
static Dz1Error NetworkInfoList_add(NetworkInfoList *p, NetworkInfoEntry *data)
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

static bool_t NetworkInfoList_remove(NetworkInfoList *p, NetworkInfoEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static NetworkInfoEntry *NetworkInfoList_extract(NetworkInfoList *p, NetworkInfoEntry *key)
{
	return (NetworkInfoEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct NetworkInfoListMkArrArg
{
	NetworkInfoEntry **arr;
	unsigned int idx;
} NetworkInfoListMkArrArg;

static Dz1Error _NetworkInfoList_get_array(void *ptr, NetworkInfoEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	NetworkInfoListMkArrArg *arg = (NetworkInfoListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static NetworkInfoEntry **NetworkInfoList_get_array(NetworkInfoList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	NetworkInfoEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (NetworkInfoEntry **)Dz1Calloc(sizeof(NetworkInfoEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		NetworkInfoListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _NetworkInfoList_get_array, (void *)&arg);
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

static Dz1Error NetworkInfoList_travelForward(NetworkInfoList *p, Dz1Error (*func)(void *ptr, NetworkInfoEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error NetworkInfoList_travelBackward(NetworkInfoList *p, Dz1Error (*func)(void *ptr, NetworkInfoEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static NetworkInfoEntry *NetworkInfoList_find(NetworkInfoList *p, NetworkInfoEntry *key)
{
	return (NetworkInfoEntry *)Dz1AATree_find(p->storage, key);
}

static NetworkInfoEntry *NetworkInfoList_getHead(NetworkInfoList *p)
{
	return (NetworkInfoEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int NetworkInfoList_count(NetworkInfoList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

NetworkInfoList *NetworkInfoList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	NetworkInfoList *ret = (NetworkInfoList *)Dz1Calloc(sizeof(NetworkInfoList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(NetworkInfoList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)NetworkInfoEntry_cmp,
				(Dz1DelFunc)NetworkInfoEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = NetworkInfoList_count;
			ret->travel = NetworkInfoList_travelForward;
			ret->travelForward = NetworkInfoList_travelForward;
			ret->travelBackward = NetworkInfoList_travelBackward;
			ret->get_array = NetworkInfoList_get_array;
			ret->add = NetworkInfoList_add;
			ret->remove = NetworkInfoList_remove;
			ret->find = NetworkInfoList_find;
			ret->extract = NetworkInfoList_extract;
			ret->getHead = NetworkInfoList_getHead;
			ret->cmp = NetworkInfoEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (NetworkInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _NetworkInfoList_clone(void *ptr, NetworkInfoEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	NetworkInfoList *p = (NetworkInfoList *)ptr;
	NetworkInfoEntry *cloned = NetworkInfoEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

NetworkInfoList *NetworkInfoList_clone(NetworkInfoList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	NetworkInfoList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = NetworkInfoList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(NetworkInfoList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_NetworkInfoList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (NetworkInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void NetworkInfoList_purge(NetworkInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void NetworkInfoList_del(NetworkInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _NetworkInfoList_dump(void *ptr, NetworkInfoEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); NetworkInfoEntry_dump(p, tab);
	return err;
}

void NetworkInfoList_dump(NetworkInfoList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _NetworkInfoList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// NetworkInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommTxPDUEntry
CommTxPDUEntry *CommTxPDUEntry_new(u32_t idx, 
								   u32_t psid, 
								   u8_t priority, 
								   u8_t channel, 
								   u16_t txInterval, 
								   time_t deliveryStart, 
								   time_t deliveryStop, 
								   Dz1Binary *payload, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CommTxPDUEntry *__internal_ret = (CommTxPDUEntry *)Dz1Calloc(sizeof(CommTxPDUEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CommTxPDUEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->idx = idx;
		__internal_ret->psid = psid;
		__internal_ret->priority = priority;
		__internal_ret->channel = channel;
		__internal_ret->txInterval = txInterval;
		__internal_ret->deliveryStart = deliveryStart;
		__internal_ret->deliveryStop = deliveryStop;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CommTxPDUEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CommTxPDUEntry_copy(CommTxPDUEntry *dst, CommTxPDUEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->ipAddress && (dst->ipAddress = Dz1Str_clone(src->ipAddress, errp)) == NULL) ERR_OUT(errp);
	else if (src->provideServiceContext && (dst->provideServiceContext = Dz1Str_clone(src->provideServiceContext, errp)) == NULL) ERR_OUT(errp);
	else if (src->payload && (dst->payload = Dz1Binary_clone(src->payload, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->idx = src->idx;
		dst->psid = src->psid;
		dst->priority = src->priority;
		dst->channel = src->channel;
		dst->txInterval = src->txInterval;
		dst->servicePort = src->servicePort;
		dst->deliveryStart = src->deliveryStart;
		dst->deliveryStop = src->deliveryStop;
		dst->signature = src->signature;
		dst->payloadType = src->payloadType;
		dst->txPower = src->txPower;
		dst->txDataRate = src->txDataRate;
		dst->channelNumberHdrExt = src->channelNumberHdrExt;
		dst->dataRateHdrExt = src->dataRateHdrExt;
		dst->txPowerHdrExt = src->txPowerHdrExt;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CommTxPDUEntry *CommTxPDUEntry_clone(CommTxPDUEntry *src, Dz1Error *err)
{
	CommTxPDUEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CommTxPDUEntry *)Dz1Calloc(sizeof(CommTxPDUEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CommTxPDUEntry_delAndSetNull, (void *)&dst);
		if (CommTxPDUEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CommTxPDUEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CommTxPDUEntry_purge(CommTxPDUEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->ipAddress);
	Dz1Str_del(p->provideServiceContext);
	Dz1Binary_del(p->payload);
}

void CommTxPDUEntry_del(CommTxPDUEntry *p)
{
	if (p == NULL) return;
	CommTxPDUEntry_purge(p);
	Dz1Free(p);
}

void CommTxPDUEntry_dump(CommTxPDUEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("idx = ")); Dz1u32_dump(&p->idx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("psid = ")); Dz1u32_dump(&p->psid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("priority = ")); Dz1u8_dump(&p->priority, tab); 
		Dz1Thread_tprintf(tab, Dz1T("channel = ")); Dz1u8_dump(&p->channel, tab); 
		Dz1Thread_tprintf(tab, Dz1T("txInterval = ")); Dz1u16_dump(&p->txInterval, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ipAddress = ")); Dz1Str_dump(p->ipAddress, tab); 
		Dz1Thread_tprintf(tab, Dz1T("servicePort = ")); Dz1u16_dump(&p->servicePort, tab); 
		Dz1Thread_tprintf(tab, Dz1T("provideServiceContext = ")); Dz1Str_dump(p->provideServiceContext, tab); 
		Dz1Thread_tprintf(tab, Dz1T("deliveryStart = ")); time_dump(&p->deliveryStart, tab); 
		Dz1Thread_tprintf(tab, Dz1T("deliveryStop = ")); time_dump(&p->deliveryStop, tab); 
		Dz1Thread_tprintf(tab, Dz1T("signature = ")); Dz1Bool_dump(&p->signature, tab); 
		Dz1Thread_tprintf(tab, Dz1T("payloadType = ")); Dz1s64_dump(&p->payloadType, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("payload = ")); Dz1Binary_dump(p->payload, tab); 
		Dz1Thread_tprintf(tab, Dz1T("txPower = ")); Dz1s8_dump(&p->txPower, tab); 
		Dz1Thread_tprintf(tab, Dz1T("txDataRate = ")); Dz1u8_dump(&p->txDataRate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("channelNumberHdrExt = ")); Dz1Bool_dump(&p->channelNumberHdrExt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dataRateHdrExt = ")); Dz1Bool_dump(&p->dataRateHdrExt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("txPowerHdrExt = ")); Dz1Bool_dump(&p->txPowerHdrExt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int CommTxPDUEntry_cmp(CommTxPDUEntry *a, CommTxPDUEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->idx, &b->idx)) != 0) { }
	return ret;
}
// CommTxPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommTxPDUList
static Dz1Error CommTxPDUList_add(CommTxPDUList *p, CommTxPDUEntry *data)
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

static bool_t CommTxPDUList_remove(CommTxPDUList *p, CommTxPDUEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static CommTxPDUEntry *CommTxPDUList_extract(CommTxPDUList *p, CommTxPDUEntry *key)
{
	return (CommTxPDUEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct CommTxPDUListMkArrArg
{
	CommTxPDUEntry **arr;
	unsigned int idx;
} CommTxPDUListMkArrArg;

static Dz1Error _CommTxPDUList_get_array(void *ptr, CommTxPDUEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CommTxPDUListMkArrArg *arg = (CommTxPDUListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static CommTxPDUEntry **CommTxPDUList_get_array(CommTxPDUList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	CommTxPDUEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (CommTxPDUEntry **)Dz1Calloc(sizeof(CommTxPDUEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		CommTxPDUListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _CommTxPDUList_get_array, (void *)&arg);
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

static Dz1Error CommTxPDUList_travelForward(CommTxPDUList *p, Dz1Error (*func)(void *ptr, CommTxPDUEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error CommTxPDUList_travelBackward(CommTxPDUList *p, Dz1Error (*func)(void *ptr, CommTxPDUEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static CommTxPDUEntry *CommTxPDUList_find(CommTxPDUList *p, CommTxPDUEntry *key)
{
	return (CommTxPDUEntry *)Dz1AATree_find(p->storage, key);
}

static CommTxPDUEntry *CommTxPDUList_getHead(CommTxPDUList *p)
{
	return (CommTxPDUEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int CommTxPDUList_count(CommTxPDUList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

CommTxPDUList *CommTxPDUList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CommTxPDUList *ret = (CommTxPDUList *)Dz1Calloc(sizeof(CommTxPDUList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CommTxPDUList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)CommTxPDUEntry_cmp,
				(Dz1DelFunc)CommTxPDUEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = CommTxPDUList_count;
			ret->travel = CommTxPDUList_travelForward;
			ret->travelForward = CommTxPDUList_travelForward;
			ret->travelBackward = CommTxPDUList_travelBackward;
			ret->get_array = CommTxPDUList_get_array;
			ret->add = CommTxPDUList_add;
			ret->remove = CommTxPDUList_remove;
			ret->find = CommTxPDUList_find;
			ret->extract = CommTxPDUList_extract;
			ret->getHead = CommTxPDUList_getHead;
			ret->cmp = CommTxPDUEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CommTxPDUList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _CommTxPDUList_clone(void *ptr, CommTxPDUEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CommTxPDUList *p = (CommTxPDUList *)ptr;
	CommTxPDUEntry *cloned = CommTxPDUEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

CommTxPDUList *CommTxPDUList_clone(CommTxPDUList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CommTxPDUList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = CommTxPDUList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CommTxPDUList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_CommTxPDUList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (CommTxPDUList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void CommTxPDUList_purge(CommTxPDUList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void CommTxPDUList_del(CommTxPDUList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _CommTxPDUList_dump(void *ptr, CommTxPDUEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); CommTxPDUEntry_dump(p, tab);
	return err;
}

void CommTxPDUList_dump(CommTxPDUList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _CommTxPDUList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CommTxPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommRxPDUEntry
CommRxPDUEntry *CommRxPDUEntry_new(u32_t psid, 
								   u8_t channel, 
								   u8_t rcpi, 
								   Dz1Binary *payload, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CommRxPDUEntry *__internal_ret = (CommRxPDUEntry *)Dz1Calloc(sizeof(CommRxPDUEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CommRxPDUEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->psid = psid;
		__internal_ret->channel = channel;
		__internal_ret->rcpi = rcpi;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CommRxPDUEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CommRxPDUEntry_copy(CommRxPDUEntry *dst, CommRxPDUEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->peerAddress && (dst->peerAddress = Dz1Str_clone(src->peerAddress, errp)) == NULL) ERR_OUT(errp);
	else if (src->payload && (dst->payload = Dz1Binary_clone(src->payload, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->psid = src->psid;
		dst->channel = src->channel;
		dst->rcpi = src->rcpi;
		dst->sign = src->sign;
		dst->payloadType = src->payloadType;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CommRxPDUEntry *CommRxPDUEntry_clone(CommRxPDUEntry *src, Dz1Error *err)
{
	CommRxPDUEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CommRxPDUEntry *)Dz1Calloc(sizeof(CommRxPDUEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CommRxPDUEntry_delAndSetNull, (void *)&dst);
		if (CommRxPDUEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CommRxPDUEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CommRxPDUEntry_purge(CommRxPDUEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->peerAddress);
	Dz1Binary_del(p->payload);
}

void CommRxPDUEntry_del(CommRxPDUEntry *p)
{
	if (p == NULL) return;
	CommRxPDUEntry_purge(p);
	Dz1Free(p);
}

void CommRxPDUEntry_dump(CommRxPDUEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("psid = ")); Dz1u32_dump(&p->psid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("channel = ")); Dz1u8_dump(&p->channel, tab); 
		Dz1Thread_tprintf(tab, Dz1T("rcpi = ")); Dz1u8_dump(&p->rcpi, tab); 
		Dz1Thread_tprintf(tab, Dz1T("peerAddress = ")); Dz1Str_dump(p->peerAddress, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sign = ")); Dz1Bool_dump(&p->sign, tab); 
		Dz1Thread_tprintf(tab, Dz1T("payloadType = ")); Dz1s64_dump(&p->payloadType, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("payload = ")); Dz1Binary_dump(p->payload, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int CommRxPDUEntry_cmp(CommRxPDUEntry *a, CommRxPDUEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->psid, &b->psid)) != 0) { }
	return ret;
}
// CommRxPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommRxPDUList
static Dz1Error CommRxPDUList_add(CommRxPDUList *p, CommRxPDUEntry *data)
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

static bool_t CommRxPDUList_remove(CommRxPDUList *p, CommRxPDUEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static CommRxPDUEntry *CommRxPDUList_extract(CommRxPDUList *p, CommRxPDUEntry *key)
{
	return (CommRxPDUEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct CommRxPDUListMkArrArg
{
	CommRxPDUEntry **arr;
	unsigned int idx;
} CommRxPDUListMkArrArg;

static Dz1Error _CommRxPDUList_get_array(void *ptr, CommRxPDUEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CommRxPDUListMkArrArg *arg = (CommRxPDUListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static CommRxPDUEntry **CommRxPDUList_get_array(CommRxPDUList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	CommRxPDUEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (CommRxPDUEntry **)Dz1Calloc(sizeof(CommRxPDUEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		CommRxPDUListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _CommRxPDUList_get_array, (void *)&arg);
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

static Dz1Error CommRxPDUList_travelForward(CommRxPDUList *p, Dz1Error (*func)(void *ptr, CommRxPDUEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error CommRxPDUList_travelBackward(CommRxPDUList *p, Dz1Error (*func)(void *ptr, CommRxPDUEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static CommRxPDUEntry *CommRxPDUList_find(CommRxPDUList *p, CommRxPDUEntry *key)
{
	return (CommRxPDUEntry *)Dz1AATree_find(p->storage, key);
}

static CommRxPDUEntry *CommRxPDUList_getHead(CommRxPDUList *p)
{
	return (CommRxPDUEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int CommRxPDUList_count(CommRxPDUList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

CommRxPDUList *CommRxPDUList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CommRxPDUList *ret = (CommRxPDUList *)Dz1Calloc(sizeof(CommRxPDUList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CommRxPDUList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)CommRxPDUEntry_cmp,
				(Dz1DelFunc)CommRxPDUEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = CommRxPDUList_count;
			ret->travel = CommRxPDUList_travelForward;
			ret->travelForward = CommRxPDUList_travelForward;
			ret->travelBackward = CommRxPDUList_travelBackward;
			ret->get_array = CommRxPDUList_get_array;
			ret->add = CommRxPDUList_add;
			ret->remove = CommRxPDUList_remove;
			ret->find = CommRxPDUList_find;
			ret->extract = CommRxPDUList_extract;
			ret->getHead = CommRxPDUList_getHead;
			ret->cmp = CommRxPDUEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CommRxPDUList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _CommRxPDUList_clone(void *ptr, CommRxPDUEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CommRxPDUList *p = (CommRxPDUList *)ptr;
	CommRxPDUEntry *cloned = CommRxPDUEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

CommRxPDUList *CommRxPDUList_clone(CommRxPDUList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CommRxPDUList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = CommRxPDUList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CommRxPDUList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_CommRxPDUList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (CommRxPDUList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void CommRxPDUList_purge(CommRxPDUList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void CommRxPDUList_del(CommRxPDUList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _CommRxPDUList_dump(void *ptr, CommRxPDUEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); CommRxPDUEntry_dump(p, tab);
	return err;
}

void CommRxPDUList_dump(CommRxPDUList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _CommRxPDUList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CommRxPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2_EamPresent
static struct TechnicalRegulation2_EamPresentMapA
{
	str_t str;
	TechnicalRegulation2_EamPresent v;
} TechnicalRegulation2_EamPresentMapA[] =
{
	{ (char *)"comm_tx_pdu", TechnicalRegulation2_EamPresent_comm_tx_pdu },
	{ (char *)"comm_rx_pdu", TechnicalRegulation2_EamPresent_comm_rx_pdu },
	{ NULL, TechnicalRegulation2_EamPresent_max }
};

str_t TechnicalRegulation2_EamPresentStrA(TechnicalRegulation2_EamPresent v)
{
	struct TechnicalRegulation2_EamPresentMapA *i = NULL;
	for (i = TechnicalRegulation2_EamPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TechnicalRegulation2_EamPresent TechnicalRegulation2_EamPresentFromStrA(str_t str)
{
	struct TechnicalRegulation2_EamPresentMapA *i = NULL;
	for (i = TechnicalRegulation2_EamPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TechnicalRegulation2_EamPresent_max;
}
#ifndef UNIX_SYSTEM
static struct TechnicalRegulation2_EamPresentMapW
{
	wstr_t str;
	TechnicalRegulation2_EamPresent v;
} TechnicalRegulation2_EamPresentMapW[] =
{
	{ (wchar_t *)L"comm_tx_pdu", TechnicalRegulation2_EamPresent_comm_tx_pdu },
	{ (wchar_t *)L"comm_rx_pdu", TechnicalRegulation2_EamPresent_comm_rx_pdu },
	{ NULL, TechnicalRegulation2_EamPresent_max }
};

wstr_t TechnicalRegulation2_EamPresentStrW(TechnicalRegulation2_EamPresent v)
{
	struct TechnicalRegulation2_EamPresentMapW *i = NULL;
	for (i = TechnicalRegulation2_EamPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TechnicalRegulation2_EamPresent TechnicalRegulation2_EamPresentFromStrW(wstr_t str)
{
	struct TechnicalRegulation2_EamPresentMapW *i = NULL;
	for (i = TechnicalRegulation2_EamPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TechnicalRegulation2_EamPresent_max;
}
#endif // UNIX_SYSTEM

TechnicalRegulation2_EamPresent *TechnicalRegulation2_EamPresent_new(TechnicalRegulation2_EamPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation2_EamPresent *__internal_ret = (TechnicalRegulation2_EamPresent *)Dz1Calloc(sizeof(TechnicalRegulation2_EamPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TechnicalRegulation2_EamPresent_dump(TechnicalRegulation2_EamPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TechnicalRegulation2_EamPresentStr(*v));
}
// TechnicalRegulation2_EamPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2_Eam
TechnicalRegulation2_Eam *TechnicalRegulation2_Eam_new(TechnicalRegulation2_EamPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation2_Eam *ret = (TechnicalRegulation2_Eam *)Dz1Calloc(sizeof(TechnicalRegulation2_Eam), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2_Eam_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case TechnicalRegulation2_EamPresent_comm_tx_pdu:
			// _U_cst_clone
			if (ptr != NULL) ret->x.comm_tx_pdu = (CommTxPDUList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation2_EamPresent_comm_rx_pdu:
			// _U_cst_clone
			if (ptr != NULL) ret->x.comm_rx_pdu = (CommRxPDUList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation2_EamPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2_Eam_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TechnicalRegulation2_Eam_copy(TechnicalRegulation2_Eam *ret, TechnicalRegulation2_Eam *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case TechnicalRegulation2_EamPresent_comm_tx_pdu:
			// _U_cst_clone
			if (src->x.comm_tx_pdu && (ret->x.comm_tx_pdu = CommTxPDUList_clone(src->x.comm_tx_pdu, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation2_EamPresent_comm_rx_pdu:
			// _U_cst_clone
			if (src->x.comm_rx_pdu && (ret->x.comm_rx_pdu = CommRxPDUList_clone(src->x.comm_rx_pdu, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation2_Eam *TechnicalRegulation2_Eam_clone(TechnicalRegulation2_Eam *src, Dz1Error *err)
{
	TechnicalRegulation2_Eam *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (TechnicalRegulation2_Eam *)Dz1Calloc(sizeof(TechnicalRegulation2_Eam), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation2_Eam_delAndSetNull, (void *)&ret);
		if (TechnicalRegulation2_Eam_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation2_Eam_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TechnicalRegulation2_Eam_purge(TechnicalRegulation2_Eam *p)
{
	if (!p) return;
	switch(p->present)
	{
	case TechnicalRegulation2_EamPresent_comm_tx_pdu:
		CommTxPDUList_del(p->x.comm_tx_pdu);
		break;
	case TechnicalRegulation2_EamPresent_comm_rx_pdu:
		CommRxPDUList_del(p->x.comm_rx_pdu);
		break;
	default:
		break;
	}
}

void TechnicalRegulation2_Eam_del(TechnicalRegulation2_Eam *p)
{
	if (!p) return;
	TechnicalRegulation2_Eam_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation2_Eam_dump(TechnicalRegulation2_Eam *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case TechnicalRegulation2_EamPresent_comm_tx_pdu:
		Dz1Thread_printf(Dz1T("comm_tx_pdu = ")); CommTxPDUList_dump(p->x.comm_tx_pdu, tab); 
		break;
	case TechnicalRegulation2_EamPresent_comm_rx_pdu:
		Dz1Thread_printf(Dz1T("comm_rx_pdu = ")); CommRxPDUList_dump(p->x.comm_rx_pdu, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// TechnicalRegulation2_Eam
////////////////////////////////////////////////////////////////////////////////

