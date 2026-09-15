////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827SessionDef.h"

#include "ItsIso14827DomainDef.h"
////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionEntry
ItsIso14827SessionEntry *ItsIso14827SessionEntry_new(ItsIso14827SessionKey *key, 
													 Dz1TcpClientSocket *sock, 
													 u32_t receiver, 
													 Dz1ElasticBuf *buf, 
													 Dz1Asn1Codec codecRule, 
													 ItsIso14827CRCCheck CRCCheck, 
													 void *initiator, 
													 void *uRsc, 
													 void *timer, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SessionEntry *__internal_ret = (ItsIso14827SessionEntry *)Dz1Calloc(sizeof(ItsIso14827SessionEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SessionEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->key = key;
		__internal_ret->sock = sock;
		__internal_ret->receiver = receiver;
		__internal_ret->buf = buf;
		__internal_ret->codecRule = codecRule;
		__internal_ret->CRCCheck = CRCCheck;
		__internal_ret->initiator = initiator;
		__internal_ret->uRsc = uRsc;
		__internal_ret->timer = timer;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SessionEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SessionEntry_purge(ItsIso14827SessionEntry *p)
{
	if (p == NULL) return;
	ItsIso14827SessionKey_del(p->key);
	Dz1TcpClientSocket_del(p->sock);
	Dz1ElasticBuf_del(p->buf);
	Dz1u32_del(p->rxSerial);
}

void ItsIso14827SessionEntry_del(ItsIso14827SessionEntry *p)
{
	if (p == NULL) return;
	ItsIso14827SessionEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827SessionEntry_dump(ItsIso14827SessionEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("key = ")); ItsIso14827SessionKey_dump(p->key, tab); 
		Dz1Thread_tprintf(tab, Dz1T("receiver = ")); Dz1u32_dump(&p->receiver, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("buf = ")); Dz1ElasticBuf_dump(p->buf, tab); 
		Dz1Thread_tprintf(tab, Dz1T("codecRule = %s(%d)\n"), Dz1Asn1CodecStr(p->codecRule), p->codecRule);
		Dz1Thread_tprintf(tab, Dz1T("CRCCheck = %s(%d)\n"), ItsIso14827CRCCheckStr(p->CRCCheck), p->CRCCheck);
		Dz1Thread_tprintf(tab, Dz1T("txSerial = ")); Dz1u32_dump(&p->txSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("rxSerial = ")); Dz1u32_dump(p->rxSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initiator = %p\n"), p->initiator);
		Dz1Thread_tprintf(tab, Dz1T("uRsc = %p\n"), p->uRsc);
		Dz1Thread_tprintf(tab, Dz1T("timer = %p\n"), p->timer);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827SessionEntry_cmp(ItsIso14827SessionEntry *a, ItsIso14827SessionEntry *b)
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
// ItsIso14827SessionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionList
static Dz1Error ItsIso14827SessionList_add(ItsIso14827SessionList *p, ItsIso14827SessionEntry *data)
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

static bool_t ItsIso14827SessionList_remove(ItsIso14827SessionList *p, ItsIso14827SessionEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827SessionEntry *ItsIso14827SessionList_extract(ItsIso14827SessionList *p, ItsIso14827SessionEntry *key)
{
	return (ItsIso14827SessionEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827SessionListMkArrArg
{
	ItsIso14827SessionEntry **arr;
	unsigned int idx;
} ItsIso14827SessionListMkArrArg;

static Dz1Error _ItsIso14827SessionList_get_array(void *ptr, ItsIso14827SessionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SessionListMkArrArg *arg = (ItsIso14827SessionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827SessionEntry **ItsIso14827SessionList_get_array(ItsIso14827SessionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827SessionEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827SessionEntry **)Dz1Calloc(sizeof(ItsIso14827SessionEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827SessionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827SessionList_get_array, (void *)&arg);
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

static Dz1Error ItsIso14827SessionList_travelForward(ItsIso14827SessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SessionEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827SessionList_travelBackward(ItsIso14827SessionList *p, Dz1Error (*func)(void *ptr, ItsIso14827SessionEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827SessionEntry *ItsIso14827SessionList_find(ItsIso14827SessionList *p, ItsIso14827SessionEntry *key)
{
	return (ItsIso14827SessionEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827SessionList_count(ItsIso14827SessionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827SessionList *ItsIso14827SessionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SessionList *ret = (ItsIso14827SessionList *)Dz1Calloc(sizeof(ItsIso14827SessionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827SessionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827SessionEntry_cmp,
				(Dz1DelFunc)ItsIso14827SessionEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827SessionList_count;
			ret->travel = ItsIso14827SessionList_travelForward;
			ret->travelForward = ItsIso14827SessionList_travelForward;
			ret->travelBackward = ItsIso14827SessionList_travelBackward;
			ret->get_array = ItsIso14827SessionList_get_array;
			ret->add = ItsIso14827SessionList_add;
			ret->remove = ItsIso14827SessionList_remove;
			ret->find = ItsIso14827SessionList_find;
			ret->extract = ItsIso14827SessionList_extract;
			ret->cmp = ItsIso14827SessionEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827SessionList_purge(ItsIso14827SessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827SessionList_del(ItsIso14827SessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827SessionList_dump(void *ptr, ItsIso14827SessionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827SessionEntry_dump(p, tab);
	return err;
}

void ItsIso14827SessionList_dump(ItsIso14827SessionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827SessionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827SessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827AcceptorEntry
ItsIso14827AcceptorEntry *ItsIso14827AcceptorEntry_new(Dz1SockAddr *server, 
													   u32_t thID, 
													   Dz1Asn1Codec initial, 
													   ItsIso14827CRCCheck CRCCheck, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827AcceptorEntry *__internal_ret = (ItsIso14827AcceptorEntry *)Dz1Calloc(sizeof(ItsIso14827AcceptorEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827AcceptorEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->server = server;
		__internal_ret->thID = thID;
		__internal_ret->initial = initial;
		__internal_ret->CRCCheck = CRCCheck;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827AcceptorEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827AcceptorEntry_purge(ItsIso14827AcceptorEntry *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->server);
}

void ItsIso14827AcceptorEntry_del(ItsIso14827AcceptorEntry *p)
{
	if (p == NULL) return;
	ItsIso14827AcceptorEntry_purge(p);
	Dz1Free(p);
}

void ItsIso14827AcceptorEntry_dump(ItsIso14827AcceptorEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("server = ")); Dz1SockAddr_dump(p->server, tab); 
		Dz1Thread_tprintf(tab, Dz1T("thID = ")); Dz1u32_dump(&p->thID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initial = %s(%d)\n"), Dz1Asn1CodecStr(p->initial), p->initial);
		Dz1Thread_tprintf(tab, Dz1T("CRCCheck = %s(%d)\n"), ItsIso14827CRCCheckStr(p->CRCCheck), p->CRCCheck);
		Dz1Thread_tprintf(tab, Dz1T("ref = ")); Dz1s32_dump(&p->ref, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ItsIso14827AcceptorEntry_cmp(ItsIso14827AcceptorEntry *a, ItsIso14827AcceptorEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->server == NULL && b->server == NULL) ret = 0;
	else if (a->server == NULL /*&& b->server != NULL*/) ret = -1;
	else if (/*a->server != NULL &&*/ b->server == NULL) ret = 1;
	else if ((ret = Dz1SockAddr_cmp(a->server, b->server)) != 0) { }
	return ret;
}
// ItsIso14827AcceptorEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827AcceptorList
static Dz1Error ItsIso14827AcceptorList_add(ItsIso14827AcceptorList *p, ItsIso14827AcceptorEntry *data)
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

static bool_t ItsIso14827AcceptorList_remove(ItsIso14827AcceptorList *p, ItsIso14827AcceptorEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ItsIso14827AcceptorEntry *ItsIso14827AcceptorList_extract(ItsIso14827AcceptorList *p, ItsIso14827AcceptorEntry *key)
{
	return (ItsIso14827AcceptorEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ItsIso14827AcceptorListMkArrArg
{
	ItsIso14827AcceptorEntry **arr;
	unsigned int idx;
} ItsIso14827AcceptorListMkArrArg;

static Dz1Error _ItsIso14827AcceptorList_get_array(void *ptr, ItsIso14827AcceptorEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827AcceptorListMkArrArg *arg = (ItsIso14827AcceptorListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ItsIso14827AcceptorEntry **ItsIso14827AcceptorList_get_array(ItsIso14827AcceptorList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ItsIso14827AcceptorEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ItsIso14827AcceptorEntry **)Dz1Calloc(sizeof(ItsIso14827AcceptorEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827AcceptorListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ItsIso14827AcceptorList_get_array, (void *)&arg);
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

static Dz1Error ItsIso14827AcceptorList_travelForward(ItsIso14827AcceptorList *p, Dz1Error (*func)(void *ptr, ItsIso14827AcceptorEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ItsIso14827AcceptorList_travelBackward(ItsIso14827AcceptorList *p, Dz1Error (*func)(void *ptr, ItsIso14827AcceptorEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ItsIso14827AcceptorEntry *ItsIso14827AcceptorList_find(ItsIso14827AcceptorList *p, ItsIso14827AcceptorEntry *key)
{
	return (ItsIso14827AcceptorEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int ItsIso14827AcceptorList_count(ItsIso14827AcceptorList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ItsIso14827AcceptorList *ItsIso14827AcceptorList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827AcceptorList *ret = (ItsIso14827AcceptorList *)Dz1Calloc(sizeof(ItsIso14827AcceptorList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827AcceptorList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ItsIso14827AcceptorEntry_cmp,
				(Dz1DelFunc)ItsIso14827AcceptorEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ItsIso14827AcceptorList_count;
			ret->travel = ItsIso14827AcceptorList_travelForward;
			ret->travelForward = ItsIso14827AcceptorList_travelForward;
			ret->travelBackward = ItsIso14827AcceptorList_travelBackward;
			ret->get_array = ItsIso14827AcceptorList_get_array;
			ret->add = ItsIso14827AcceptorList_add;
			ret->remove = ItsIso14827AcceptorList_remove;
			ret->find = ItsIso14827AcceptorList_find;
			ret->extract = ItsIso14827AcceptorList_extract;
			ret->cmp = ItsIso14827AcceptorEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827AcceptorList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827AcceptorList_purge(ItsIso14827AcceptorList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ItsIso14827AcceptorList_del(ItsIso14827AcceptorList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ItsIso14827AcceptorList_dump(void *ptr, ItsIso14827AcceptorEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ItsIso14827AcceptorEntry_dump(p, tab);
	return err;
}

void ItsIso14827AcceptorList_dump(ItsIso14827AcceptorList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ItsIso14827AcceptorList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827AcceptorList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionMgr
ItsIso14827SessionMgr *ItsIso14827SessionMgr_new(u32_t myQueueID, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SessionMgr *__internal_ret = (ItsIso14827SessionMgr *)Dz1Calloc(sizeof(ItsIso14827SessionMgr), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SessionMgr_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->listener = ItsIso14827AcceptorList_gen(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->sessions = ItsIso14827SessionList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->myQueueID = myQueueID;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SessionMgr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827SessionMgr_purge(ItsIso14827SessionMgr *p)
{
	if (p == NULL) return;
	ItsIso14827AcceptorList_del(p->listener);
	ItsIso14827SessionList_del(p->sessions);
}

void ItsIso14827SessionMgr_del(ItsIso14827SessionMgr *p)
{
	if (p == NULL) return;
	ItsIso14827SessionMgr_purge(p);
	Dz1Free(p);
}

void ItsIso14827SessionMgr_dump(ItsIso14827SessionMgr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("myQueueID = ")); Dz1u32_dump(&p->myQueueID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("listener = ")); ItsIso14827AcceptorList_dump(p->listener, tab); 
		Dz1Thread_tprintf(tab, Dz1T("allocSID = ")); Dz1u32_dump(&p->allocSID, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sessions = ")); ItsIso14827SessionList_dump(p->sessions, tab); 
		Dz1Thread_tprintf(tab, Dz1T("debug_dump = ")); Dz1Bool_dump(&p->debug_dump, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827SessionMgr
////////////////////////////////////////////////////////////////////////////////

